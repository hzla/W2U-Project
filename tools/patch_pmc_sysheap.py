#!/usr/bin/env python3

from __future__ import annotations

import argparse
import shutil
from pathlib import Path


PMC_OVERLAY_HEAP_KIB_IMMEDIATE_OFFSET = 0x2BA
OLD_SYSHEAP_KIB = 160
# 200 KiB (MegaB2W2's value): the heap is the top of ARM9 arena region 0 (it ends at 0x023E0000). The game takes
# its heaps from that region once at boot and never again; measured in a W2U battle, the region's free part is
# 0x023AC104-0x023B7000 below a 164 KiB heap (44,796 bytes), so 200 KiB (start 0x023AE000) leaves 7,932 bytes.
DEFAULT_SYSHEAP_KIB = 200

# The bundled PMC overlay was built with an older HeapArea::Realloc that uses
# `old_size - new_size - 24` when splitting a shrunken allocation. Its block
# header is 16 bytes, so every shrink permanently loses 8 bytes. A non-resident
# RPM is expanded, fixed (shrunk), and freed on every use; without this fix its
# allocation can be eight bytes too small for the very next reload.
PMC_REALLOC_SHRINK_INSTRUCTION_OFFSET = 0x804
BROKEN_REALLOC_SHRINK_INSTRUCTION = bytes.fromhex("18 3b")  # subs r3, #24
FIXED_REALLOC_SHRINK_INSTRUCTION = bytes.fromhex("10 3b")  # subs r3, #16

# DSi mode: the bundled PMC takes its heap from the top of whatever arena the OS reports, which on a DSi is
# 0x02F80000, about 15 MB above the ARM9 program. W2U's code is built with -mno-long-calls, and Thumb BL reaches
# +-4 MB, so PMC's hooks into that heap wrap around (getSizeofPokedexData's BL to the resident core lands at
# 0x01F4F63C, an ITCM mirror) and the game takes a data abort at boot. This replaces the heap setup routine
# (overlay 0x2BA-0x2F0, the system heap cap stays its first immediate) with one that clamps the arena's top at the
# DS one, 0x023E0000: on a DS nothing changes; on a DSi the heap is 0x023AE000-0x023E0000, inside the 0x021FD0C0-
# 0x02700000 hole the DSi mode's arena leaves below its LTD module (in range of everything), and the OS arena is
# not touched (the new top goes to the routine's own literal). The arena's low end is above that top on a DSi, so
# the free size underflows and the heap takes the full cap. Newer PMC builds (Pokeweb's) do the same with
# OS_IsRunOnTwl. The original's `bics #7` on the size is dropped for room: the size is the cap, a multiple of 1 KiB.
PMC_HEAP_SETUP_OFFSET = 0x2BA
PMC_HEAP_SETUP_ORIGINAL = bytes.fromhex(
    "a0 20 09 4b 0a 4a 19 68 12 68 10 b5 8a 1a 80 02 82 42 00 d9 02 00 07 20 82 43 81 43"
    " 89 1a 04 48 19 60 00 f0 d4 f9 10 bd c0 46 c4 fd ff 02 a0 fd ff 02 8a e8 1f 02"
)
PMC_HEAP_SETUP_DSI = bytes.fromhex(
    "a0 20 08 4b 19 68 0a 4a 91 42 01 d9 11 1c 08 a3 06 4a 12 68 8a 1a 80 02 82 42 00 d9"
    " 02 1c 89 1a 03 48 19 60 d3 e1 c4 fd ff 02 a0 fd ff 02 8a e8 1f 02 00 00 3e 02"
)


def parse_int(value: str) -> int:
    return int(value, 0)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Patch the PMC system heap cap and realloc shrink accounting in overlay 344."
    )
    parser.add_argument(
        "overlay",
        nargs="?",
        help="Overlay 344 binary to patch in place. Prefer --input/--output for Meson builds.",
    )
    parser.add_argument("--input", type=Path, help="Source overlay 344 binary.")
    parser.add_argument("--output", type=Path, help="Patched overlay 344 output path.")
    parser.add_argument(
        "--kib",
        type=parse_int,
        default=DEFAULT_SYSHEAP_KIB,
        help=f"New PMC system heap cap in KiB. Default: {DEFAULT_SYSHEAP_KIB}.",
    )
    parser.add_argument("--stamp", type=Path, help="Optional stamp file to write after patching.")
    args = parser.parse_args()

    if not 0 <= args.kib <= 0xFF:
        raise SystemExit(f"Heap cap must fit the Thumb movs immediate: {args.kib}")

    overlay_path = prepare_overlay_path(args)
    data = bytearray(overlay_path.read_bytes())
    offset = PMC_OVERLAY_HEAP_KIB_IMMEDIATE_OFFSET
    current = data[offset]
    patched = args.kib
    changed = False

    if current == patched:
        print(
            f"[+] PMC system heap cap already patched to {args.kib} KiB "
            f"at overlay 344 offset 0x{offset:x}."
        )
    else:
        if current not in (OLD_SYSHEAP_KIB, 164):
            raise SystemExit(
                "Unexpected PMC system heap immediate at "
                f"overlay 344 offset 0x{offset:x}: found {current}, "
                f"expected {OLD_SYSHEAP_KIB}, 164 or {args.kib}."
            )
        data[offset] = patched
        changed = True
        print(
            f"[+] Patched PMC system heap cap: {OLD_SYSHEAP_KIB} KiB -> "
            f"{args.kib} KiB at overlay 344 offset 0x{offset:x}."
        )

    realloc_offset = PMC_REALLOC_SHRINK_INSTRUCTION_OFFSET
    current_instruction = bytes(
        data[realloc_offset : realloc_offset + len(BROKEN_REALLOC_SHRINK_INSTRUCTION)]
    )
    if current_instruction == FIXED_REALLOC_SHRINK_INSTRUCTION:
        print(
            "[+] PMC realloc shrink accounting already fixed "
            f"at overlay 344 offset 0x{realloc_offset:x}."
        )
    elif current_instruction == BROKEN_REALLOC_SHRINK_INSTRUCTION:
        data[
            realloc_offset : realloc_offset + len(FIXED_REALLOC_SHRINK_INSTRUCTION)
        ] = FIXED_REALLOC_SHRINK_INSTRUCTION
        changed = True
        print(
            "[+] Fixed PMC realloc shrink accounting: subtracted block-header size "
            f"24 -> 16 at overlay 344 offset 0x{realloc_offset:x}."
        )
    else:
        raise SystemExit(
            "Unexpected PMC realloc shrink instruction at "
            f"overlay 344 offset 0x{realloc_offset:x}: found "
            f"{current_instruction.hex(' ')}, expected "
            f"{BROKEN_REALLOC_SHRINK_INSTRUCTION.hex(' ')} or "
            f"{FIXED_REALLOC_SHRINK_INSTRUCTION.hex(' ')}."
        )

    # Compared without the first byte, the system heap cap patched above
    setup_start = PMC_HEAP_SETUP_OFFSET
    setup_end = setup_start + len(PMC_HEAP_SETUP_ORIGINAL)
    current_setup = bytes(data[setup_start + 1 : setup_end])
    if current_setup == PMC_HEAP_SETUP_DSI[1:]:
        print(f"[+] PMC heap setup already DSi-aware at overlay 344 offset 0x{setup_start:x}.")
    elif current_setup == PMC_HEAP_SETUP_ORIGINAL[1:]:
        data[setup_start + 1 : setup_end] = PMC_HEAP_SETUP_DSI[1:]
        changed = True
        print(
            "[+] PMC heap setup made DSi-aware (arena top clamped to 0x023E0000) "
            f"at overlay 344 offset 0x{setup_start:x}."
        )
    else:
        raise SystemExit(
            f"Unexpected PMC heap setup at overlay 344 offset 0x{setup_start:x}: found "
            f"{current_setup.hex(' ')}."
        )

    if changed:
        overlay_path.write_bytes(data)

    if args.stamp is not None:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.write_text(f"{args.kib}\n", encoding="ascii")
    return 0


def prepare_overlay_path(args: argparse.Namespace) -> Path:
    if args.input is not None or args.output is not None:
        if args.input is None or args.output is None:
            raise SystemExit("--input and --output must be provided together.")
        args.output.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(args.input, args.output)
        return args.output
    if args.overlay is None:
        return Path("build/IRDO/exefs/overlay/overlay_0344.bin")
    return Path(args.overlay)


if __name__ == "__main__":
    raise SystemExit(main())
