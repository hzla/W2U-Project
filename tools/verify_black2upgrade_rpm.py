#!/usr/bin/env python3
from __future__ import annotations

import argparse
import struct
from pathlib import Path


def u16(data: bytes, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("rpm", type=Path)
    parser.add_argument("--priority", required=True, type=int)
    args = parser.parse_args()
    data = args.rpm.read_bytes()
    if data[:4] != b"DLXF":
        raise SystemExit(f"{args.rpm} is not a DLXF module")
    header = u32(data, 8)
    info = header + u32(data, header + 8)
    strings = header + u32(data, info + 12)
    metadata = header + u32(data, info + 32)
    if data[strings:strings + 4] != b"STR0" or data[metadata:metadata + 4] != b"META":
        raise SystemExit(f"{args.rpm} is missing required STR0/META sections")

    def string_ref(offset: int) -> str:
        ref = u16(data, offset)
        start = strings + 4 + ref
        end = data.index(0, start)
        return data[start:end].decode("utf-8")

    values: dict[str, str | int] = {}
    count = u32(data, metadata + 4)
    offset = metadata + 8
    for _ in range(count):
        name = string_ref(offset)
        values[name] = string_ref(offset + 4) if data[offset + 2] == 0 else u32(data, offset + 4)
        offset += 8
    expected = {
        "PMCGameID": "B2",
        "Black2UpgradeRuntimeABI": 1,
        "Black2UpgradeDataVersion": 1,
        "PMCModulePriority": args.priority,
    }
    if any(values.get(key) != value for key, value in expected.items()):
        raise SystemExit(f"{args.rpm} metadata mismatch: expected {expected}, got {values}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
