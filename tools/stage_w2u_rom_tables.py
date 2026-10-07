#!/usr/bin/env python3
"""Stage the read-only tables kept in ROM files (include/w2u_rom_tables.h) into the VFS: each named section of the
compiled w2u_rom_tables_data.cpp object becomes one file, byte for byte. The sections must hold no relocations
(records without pointers) and divide into whole records."""

from __future__ import annotations

import argparse
import subprocess
import tempfile
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, required=True)
    parser.add_argument("--table", action="append", default=[], required=True,
                        help="SECTION:RECORD_SIZE:DESTINATION")
    parser.add_argument("--stamp", type=Path, required=True)
    args = parser.parse_args()

    relocations = subprocess.run(["arm-none-eabi-readelf", "-rW", str(args.object)], check=True,
                                 capture_output=True, text=True).stdout
    for spec in args.table:
        section, record_size, destination = spec.split(":", 2)
        if f".rel{section}" in relocations or f".rela{section}" in relocations:
            raise RuntimeError(f"{section} has relocations; ROM table records must not hold pointers")
        with tempfile.TemporaryDirectory() as scratch:
            extracted = Path(scratch) / "table.bin"
            subprocess.run(["arm-none-eabi-objcopy", "-O", "binary", f"--only-section={section}",
                            str(args.object), str(extracted)], check=True)
            data = extracted.read_bytes() if extracted.exists() else b""
        if not data or len(data) % int(record_size):
            raise RuntimeError(f"{section}: {len(data)} bytes is not a whole number of {record_size}-byte records")
        output = Path(destination)
        output.parent.mkdir(parents=True, exist_ok=True)
        if not output.exists() or output.read_bytes() != data:
            output.write_bytes(data)
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
