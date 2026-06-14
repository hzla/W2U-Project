#!/usr/bin/env python3
"""Pack loose PWAN runtime assets as a sparse, numeric NARC."""

from __future__ import annotations

import argparse
import re
import struct
from pathlib import Path

from pwan_config import PWAN_RUNTIME_MAX_TIMELINE, parse_config


PWAN_NAME_RE = re.compile(r"^(\d+)_(front|back)\.pwan$")


def member_id_for_pwan(path: Path) -> int | None:
    match = PWAN_NAME_RE.match(path.name)
    if not match:
        return None
    asset_index = int(match.group(1))
    side = match.group(2)
    asset_id = asset_index * 2 + (1 if side == "back" else 0)
    return asset_id + 1


def collect_members(src_dir: Path) -> list[bytes]:
    config = src_dir / "config.bin"
    if not config.exists():
        raise FileNotFoundError(config)

    entries, max_timeline = parse_config(config)
    if max_timeline > PWAN_RUNTIME_MAX_TIMELINE:
        raise ValueError(
            f"{config} max timeline {max_timeline} exceeds runtime cap "
            f"{PWAN_RUNTIME_MAX_TIMELINE}"
        )

    members: dict[int, Path] = {0: config}
    for path in sorted(src_dir.glob("*.pwan")):
        member_id = member_id_for_pwan(path)
        if member_id is not None:
            members[member_id] = path

    max_member = max(members)
    files = []
    for member_id in range(max_member + 1):
        src = members.get(member_id)
        files.append(src.read_bytes() if src is not None else b"")

    if not entries:
        raise ValueError(f"{config} does not contain any PWAN override entries")
    return files


def align4(value: int) -> int:
    return (value + 3) & ~3


def build_knarc_style_narc(files: list[bytes]) -> bytes:
    """Build the no-FNT NARC layout emitted by the old Makefile's knarc tool."""
    if len(files) > 0xFFFF:
        raise ValueError(f"too many PWAN NARC members: {len(files)}")

    fat_entries: list[tuple[int, int]] = []
    cursor = 0
    for data in files:
        start = align4(cursor)
        end = start + len(data)
        fat_entries.append((start, end))
        cursor = end

    fat_chunk_size = 12 + len(fat_entries) * 8
    fnt_chunk_size = 16
    fimg_data_size = align4(cursor)
    fimg_chunk_size = 8 + fimg_data_size
    file_size = 16 + fat_chunk_size + fnt_chunk_size + fimg_chunk_size

    out = bytearray()
    out += struct.pack("<IHHIHH", 0x4352414E, 0xFFFE, 0x0100, file_size, 16, 3)
    out += struct.pack("<IIHH", 0x46415442, fat_chunk_size, len(fat_entries), 0)
    for start, end in fat_entries:
        out += struct.pack("<II", start, end)

    out += struct.pack("<II", 0x464E5442, fnt_chunk_size)
    out += struct.pack("<IHH", 4, 0, 1)
    out += struct.pack("<II", 0x46494D47, fimg_chunk_size)

    data_start = len(out)
    for data, (start, _end) in zip(files, fat_entries, strict=True):
        while len(out) - data_start < start:
            out.append(0xFF)
        out += data

    while len(out) - data_start < fimg_data_size:
        out.append(0xFF)

    if len(out) != file_size:
        raise AssertionError(f"PWAN NARC size mismatch: built {len(out)}, expected {file_size}")
    return bytes(out)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--src", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--stamp", required=True, type=Path)
    args = parser.parse_args()

    files = collect_members(args.src)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(build_knarc_style_narc(files))
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text(f"{args.output}\n{len(files)} files\n")
    print(f"[+] Packed {len(files)} PWAN NARC members into {args.output}")


if __name__ == "__main__":
    main()
