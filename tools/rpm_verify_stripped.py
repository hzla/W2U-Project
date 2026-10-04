#!/usr/bin/env python3
"""Verify that a packaged RPM no longer stores human-readable symbol names."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


def read_u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def read_u16(data: bytes, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def read_symbol_name_offsets(data: bytes) -> list[int]:
    exec_offset = read_u32(data, 8)
    if data[exec_offset : exec_offset + 4] != b"DLXH":
        raise RuntimeError("DLXH header not found")

    info_offset = exec_offset + read_u32(data, exec_offset + 8)
    if data[info_offset : info_offset + 4] != b"INFO":
        raise RuntimeError("INFO section not found")

    symbols_offset = exec_offset + read_u32(data, info_offset + 4)
    if data[symbols_offset : symbols_offset + 4] != b"SYM0":
        raise RuntimeError("SYM0 section not found")

    symbol_count = read_u32(data, symbols_offset + 20)
    symbols_start = symbols_offset + 24
    symbols_end = symbols_start + symbol_count * 12
    if symbols_end > len(data):
        raise RuntimeError("symbol table extends beyond the RPM image")

    return [
        read_u16(data, symbols_start + index * 12)
        for index in range(symbol_count)
    ]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dll", type=Path)
    args = parser.parse_args()

    path = args.dll
    name_offsets = read_symbol_name_offsets(path.read_bytes())
    named_count = sum(offset != 0 for offset in name_offsets)
    if named_count:
        raise RuntimeError(
            f"RPM still contains {named_count} named symbols out of "
            f"{len(name_offsets)}"
        )

    print(f"[+] {path.name} is stripped; retained symbols: {len(name_offsets)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
