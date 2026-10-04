#!/usr/bin/env python3
"""Restrict a child RPM's public export window to its versioned API getter."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


API_SYMBOL = "W2U_GetBattleModuleApi"


def u16(data: bytearray, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def fnv1a(name: str) -> int:
    value = 0x811C9DC5
    for byte in name.encode("ascii"):
        value = ((value ^ byte) * 16777619) & 0xFFFFFFFF
    return value


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("rpm", type=Path)
    args = parser.parse_args()

    data = bytearray(args.rpm.read_bytes())
    if len(data) < 24 or data[:4] != b"DLXF":
        raise RuntimeError(f"{args.rpm}: invalid RPM header")
    exec_offset = u32(data, 8)
    if exec_offset + 20 > len(data) or data[exec_offset : exec_offset + 4] != b"DLXH":
        raise RuntimeError(f"{args.rpm}: invalid executable header")
    info_offset = exec_offset + u32(data, exec_offset + 8)
    if info_offset + 36 > len(data) or data[info_offset : info_offset + 4] != b"INFO":
        raise RuntimeError(f"{args.rpm}: invalid INFO section")
    symbols_offset = exec_offset + u32(data, info_offset + 4)
    if symbols_offset + 24 > len(data) or data[symbols_offset : symbols_offset + 4] != b"SYM0":
        raise RuntimeError(f"{args.rpm}: invalid symbol section")

    first_export = u16(data, symbols_offset + 8)
    export_count = u16(data, symbols_offset + 10)
    hash_relative = u32(data, symbols_offset + 16)
    hash_offset = exec_offset + hash_relative
    hash_end = hash_offset + export_count * 4
    if not export_count or not hash_relative or hash_end > len(data):
        raise RuntimeError(f"{args.rpm}: invalid export hash table")

    hashes = list(struct.unpack_from(f"<{export_count}I", data, hash_offset))
    api_hash = fnv1a(API_SYMBOL)
    matches = [index for index, value in enumerate(hashes) if value == api_hash]
    if len(matches) != 1:
        raise RuntimeError(
            f"{args.rpm}: expected one API hash, found {len(matches)}"
        )
    api_index = matches[0]

    struct.pack_into("<H", data, symbols_offset + 8, first_export + api_index)
    struct.pack_into("<H", data, symbols_offset + 10, 1)
    struct.pack_into("<I", data, symbols_offset + 16, hash_relative + api_index * 4)
    args.rpm.write_bytes(data)
    print(
        f"[+] {args.rpm.name}: public export window restricted "
        f"{export_count} -> 1"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
