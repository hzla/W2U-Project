#!/usr/bin/env python3

from __future__ import annotations

import argparse
import re
import shutil
from pathlib import Path

from ndspy import narc


PREFIXED_BIN_RE = re.compile(r"^.+_(\d{8})\.bin$")
PLAIN_BIN_RE = re.compile(r"^(\d+)\.bin$")


def member_id(path: Path) -> int | None:
    if path.name.isdigit():
        return int(path.name)
    match = PREFIXED_BIN_RE.match(path.name) or PLAIN_BIN_RE.match(path.name)
    if match:
        return int(match.group(1))
    return None


def main() -> int:
    parser = argparse.ArgumentParser(description="Stage binary archive members into CTRMap VFS layout.")
    parser.add_argument("--src", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--base-archive", type=Path)
    parser.add_argument("--arc-text", default=".arc\ncompress default auto\n")
    parser.add_argument("--stamp", type=Path, required=True)
    args = parser.parse_args()

    if not args.src.is_dir():
        raise NotADirectoryError(args.src)

    if args.output_dir.exists():
        shutil.rmtree(args.output_dir)
    args.output_dir.mkdir(parents=True, exist_ok=True)

    staged = 0
    if args.base_archive is not None:
        base = narc.NARC.fromFile(args.base_archive)
        for index, data in enumerate(base.files):
            (args.output_dir / str(index)).write_bytes(data)
            staged += 1

    for source in sorted(path for path in args.src.iterdir() if path.is_file()):
        index = member_id(source)
        if index is None:
            continue
        shutil.copy2(source, args.output_dir / str(index))
        if index >= staged:
            staged = index + 1

    (args.output_dir / ".arc").write_text(args.arc_text, encoding="utf-8")
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text(f"{staged}\n", encoding="ascii")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
