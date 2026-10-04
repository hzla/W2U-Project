#!/usr/bin/env python3
"""Build an empty KO-threshold move learnset NARC.

Members use the retail learnset entry shape: little-endian ``u16 move`` plus
``u16 threshold``.  The threshold is a KO count instead of a level, and every
member ends with ``0xffff, 0xffff``.  Pokeweb can subsequently edit individual
members without changing the archive's personal-data indexing.
"""

from __future__ import annotations

import argparse
from pathlib import Path

from build_ancestry_narc import build_narc, parse_narc, write_if_changed


EMPTY_MEMBER = b"\xff\xff\xff\xff"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--learnset-members", nargs="+", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--stamp", required=True, type=Path)
    args = parser.parse_args()

    member_count = len(args.learnset_members)
    if not 1 <= member_count <= 0xFFFF:
        raise ValueError(f"invalid KO learnset member count: {member_count}")

    members = [EMPTY_MEMBER] * member_count
    output = build_narc(members)
    if parse_narc(output) != members:
        raise RuntimeError("generated KO learnset NARC failed round-trip validation")
    write_if_changed(args.output, output)
    write_if_changed(
        args.stamp,
        f"KO learnset members: {member_count}\narchive bytes: {len(output)}\n".encode(),
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
