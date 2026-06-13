#!/usr/bin/env python3
"""Pack loose PWAN runtime assets as a sparse, numeric NARC."""

from __future__ import annotations

import argparse
import re
from pathlib import Path

import ndspy.narc

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


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--src", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--stamp", required=True, type=Path)
    args = parser.parse_args()

    files = collect_members(args.src)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    ndspy.narc.NARC.fromFilesAndNames(files).saveToFile(args.output)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text(f"{args.output}\n{len(files)} files\n")
    print(f"[+] Packed {len(files)} PWAN NARC members into {args.output}")


if __name__ == "__main__":
    main()
