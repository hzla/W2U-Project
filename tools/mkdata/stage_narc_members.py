#!/usr/bin/env python3
"""Stage a retail NARC as a CTRMap NARC-entry overlay with some members replaced.

Copies every member of the clean archive (--base, from IRDO_Extracted) into the vfs/ overlay folder and replaces the
members given with --replace INDEX=FILE, so the overlay stands on its own whatever the base holds.
"""
from __future__ import annotations

import argparse
import shutil
from pathlib import Path

from ndspy import narc


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", type=Path, required=True, help="the clean NARC file")
    parser.add_argument("--output", type=Path, required=True, help="the vfs/ overlay folder for that archive")
    parser.add_argument("--replace", action="append", default=[], metavar="INDEX=FILE")
    parser.add_argument("--stamp", type=Path, required=True)
    args = parser.parse_args()

    members = list(narc.NARC(args.base.read_bytes()).files)
    for item in args.replace:
        index, path = item.split("=", 1)
        index = int(index)
        if not 0 <= index < len(members):
            raise SystemExit(f"--replace {item}: {args.base} has {len(members)} members")
        members[index] = Path(path).read_bytes()

    if args.output.is_dir():
        shutil.rmtree(args.output)
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / ".arc").write_text(".arc\ncompress default auto\n")
    for index, data in enumerate(members):
        (args.output / str(index)).write_bytes(data)

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text(f"{args.output}\n{len(members)} files, replaced {', '.join(args.replace) or 'none'}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
