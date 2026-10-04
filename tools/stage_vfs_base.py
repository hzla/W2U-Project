#!/usr/bin/env python3
"""Generate White 2's base VFS overlay from a clean US IRDO extraction."""

from __future__ import annotations

import argparse
import hashlib
import struct
from pathlib import Path

from ndspy import narc


OVERLAY_TABLE_SHA256 = "128dc82249c43000d47c7cab03832f06ac6c912183e8a171221f708227fb3717"
ZONE_DATA_SHA256 = "7d5b81b7c8b69cf1a1ccf113c209852d54ada6a30cba6b0c603339a293a33f43"
PMC_OVERLAY_ID = 344
PMC_ADDRESS = 0x021FD0C0
ARC_MARKER = b".arc\ncompress default auto\n"

# Preserve the project's existing zone flag changes as edits to the user's ROM.
ZONE_FLAG_OFFSETS = tuple(range(0x36D5, 0x3A06, 0x30)) + (0x3F15,)


def checked_input(data: bytes, expected_digest: str, label: str) -> bytes:
    if hashlib.sha256(data).hexdigest() != expected_digest:
        raise ValueError(f"{label}: expected the clean US White 2 (IRDO) input")
    return data


def overlay_table(base: bytes, pmc_size: int) -> bytes:
    if len(base) != PMC_OVERLAY_ID * 32:
        raise ValueError("expected 344 retail ARM9 overlay entries")
    if any(struct.unpack_from("<I", base, i * 32)[0] != i for i in range(PMC_OVERLAY_ID)):
        raise ValueError("retail ARM9 overlay IDs are out of order")
    return base + struct.pack(
        "<8I", PMC_OVERLAY_ID, PMC_ADDRESS, pmc_size, 0,
        PMC_ADDRESS, PMC_ADDRESS, PMC_OVERLAY_ID, 0x02000000,
    )


def zone_data(base: bytes) -> bytes:
    patched = bytearray(base)
    for offset in ZONE_FLAG_OFFSETS:
        if offset >= len(patched) or patched[offset] != 0xDF:
            raise ValueError(f"zone flag at 0x{offset:x} does not match the retail input")
        patched[offset] = 0xFF
    return bytes(patched)


def write_if_changed(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_bytes() != data:
        path.write_bytes(data)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--pmc-overlay", required=True, type=Path)
    parser.add_argument("--main-menu-patch", type=Path)
    parser.add_argument("--stamp", required=True, type=Path)
    args = parser.parse_args()

    # Validate every input before creating any output. Retail files not changed
    # by this overlay are supplied directly by CTRMap's VFSBase.
    table = checked_input((args.base / "y9.bin").read_bytes(), OVERLAY_TABLE_SHA256, "y9.bin")
    zones = checked_input(
        narc.NARC.fromFile(args.base / "data/a/0/1/2").files[0],
        ZONE_DATA_SHA256, "zone data",
    )
    outputs = {
        "y9.bin": overlay_table(table, args.pmc_overlay.stat().st_size),
        "data/a/0/1/2/.arc": ARC_MARKER,
        "data/a/0/1/2/0": zone_data(zones),
    }
    if args.main_menu_patch is not None:
        outputs["data/patches/MainMenuSkip(1).dll"] = args.main_menu_patch.read_bytes()
    for name, data in outputs.items():
        write_if_changed(args.output / name, data)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text("US IRDO VFS base staged\n", encoding="ascii")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
