#!/usr/bin/env python3
"""Verify that an RPM is scoped only to its assigned unloadable overlays."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


RESIDENT_MODULES = {"ARM9", "ARM7"}


def read_u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def read_u16(data: bytes, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def read_extern_modules(data: bytes) -> list[str]:
    exec_offset = read_u32(data, 8)
    if data[exec_offset : exec_offset + 4] != b"DLXH":
        raise RuntimeError("DLXH header not found")

    info_offset = exec_offset + read_u32(data, exec_offset + 8)
    if data[info_offset : info_offset + 4] != b"INFO":
        raise RuntimeError("INFO section not found")

    strings_offset = exec_offset + read_u32(data, info_offset + 12)
    if data[strings_offset : strings_offset + 4] != b"STR0":
        raise RuntimeError("STR0 section not found")
    strings_base = strings_offset + 4

    rel_offset = exec_offset + read_u32(data, info_offset + 8)
    if data[rel_offset : rel_offset + 4] != b"REL0":
        raise RuntimeError("REL0 section not found")

    extern_modules_offset = exec_offset + read_u32(data, rel_offset + 0x14)
    extern_count = read_u16(data, extern_modules_offset)
    modules = []
    for index in range(extern_count):
        string_offset = read_u16(data, extern_modules_offset + 2 + index * 2)
        start = strings_base + string_offset
        end = data.find(b"\0", start)
        if end < 0:
            raise RuntimeError("unterminated external module name")
        modules.append(data[start:end].decode("ascii"))
    return modules


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dll", type=Path)
    parser.add_argument(
        "--expect",
        help="Comma-separated overlay IDs that this RPM must depend on.",
    )
    args = parser.parse_args()

    path = args.dll
    modules = read_extern_modules(path.read_bytes())
    resident = sorted(RESIDENT_MODULES.intersection(modules))
    if resident:
        raise RuntimeError(
            "RPM unexpectedly became resident through: " + ", ".join(resident)
        )
    if not modules or any(not module.isdecimal() for module in modules):
        raise RuntimeError(
            "RPM must depend only on numeric overlay modules; found: "
            + repr(modules)
        )

    if len(modules) != len(set(modules)):
        raise RuntimeError("RPM contains duplicate overlay dependencies: " + repr(modules))

    if args.expect is not None:
        expected = [module for module in args.expect.split(",") if module]
        if not expected or any(not module.isdecimal() for module in expected):
            raise RuntimeError("Invalid expected overlay list: " + repr(args.expect))
        if len(expected) != len(set(expected)):
            raise RuntimeError("Expected overlay list contains duplicates: " + repr(expected))
        if set(modules) != set(expected):
            raise RuntimeError(
                "RPM overlay scope mismatch; expected "
                + repr(expected)
                + ", found "
                + repr(modules)
            )

    print(
        f"[+] {path.name} is non-resident; overlay dependencies: "
        + ", ".join(modules)
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
