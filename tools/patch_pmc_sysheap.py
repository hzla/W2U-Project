#!/usr/bin/env python3

from __future__ import annotations

import argparse
import shutil
from pathlib import Path


PMC_OVERLAY_HEAP_KIB_IMMEDIATE_OFFSET = 0x2BA
OLD_SYSHEAP_KIB = 160
DEFAULT_SYSHEAP_KIB = 164

# The bundled PMC overlay was built with an older HeapArea::Realloc that uses
# `old_size - new_size - 24` when splitting a shrunken allocation. Its block
# header is 16 bytes, so every shrink permanently loses 8 bytes. A non-resident
# RPM is expanded, fixed (shrunk), and freed on every use; without this fix its
# allocation can be eight bytes too small for the very next reload.
PMC_REALLOC_SHRINK_INSTRUCTION_OFFSET = 0x804
BROKEN_REALLOC_SHRINK_INSTRUCTION = bytes.fromhex("18 3b")  # subs r3, #24
FIXED_REALLOC_SHRINK_INSTRUCTION = bytes.fromhex("10 3b")  # subs r3, #16


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
        if current != OLD_SYSHEAP_KIB:
            raise SystemExit(
                "Unexpected PMC system heap immediate at "
                f"overlay 344 offset 0x{offset:x}: found {current}, "
                f"expected {OLD_SYSHEAP_KIB} or {args.kib}."
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
