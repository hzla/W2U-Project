#!/usr/bin/env python3
import struct
import sys
from pathlib import Path


def read_u32(data: bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def read_u16(data: bytearray, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: pwan_mark_resident.py <PokewebPwanW2.dll>", file=sys.stderr)
        return 2

    path = Path(sys.argv[1])
    data = bytearray(path.read_bytes())

    exec_offset = read_u32(data, 8)
    if data[exec_offset:exec_offset + 4] != b"DLXH":
        raise RuntimeError("DLXH header not found")

    info_offset = exec_offset + read_u32(data, exec_offset + 8)
    if data[info_offset:info_offset + 4] != b"INFO":
        raise RuntimeError("INFO section not found")

    strings_offset = exec_offset + read_u32(data, info_offset + 12)
    if data[strings_offset:strings_offset + 4] != b"STR0":
        raise RuntimeError("STR0 section not found")

    strings_base = strings_offset + 4
    anchor_offset = data.find(b"SVC_WaitByLoop\x00", strings_base)
    if anchor_offset < 0:
        anchor_offset = data.find(b"ARM9\x00", strings_base)
    if anchor_offset < 0:
        raise RuntimeError("resident anchor string not found")
    anchor_string_offset = anchor_offset - strings_base

    rel_offset = exec_offset + read_u32(data, info_offset + 8)
    if data[rel_offset:rel_offset + 4] != b"REL0":
        raise RuntimeError("REL0 section not found")

    extern_modules_offset = exec_offset + read_u32(data, rel_offset + 0x14)
    extern_count = read_u16(data, extern_modules_offset)

    existing = []
    for index in range(extern_count):
        string_offset = read_u16(data, extern_modules_offset + 2 + index * 2)
        end = data.find(b"\x00", strings_base + string_offset)
        existing.append(bytes(data[strings_base + string_offset:end]).decode("ascii"))

    if "ARM9" not in existing:
        insert_offset = extern_modules_offset + 2 + extern_count * 2
        if data[insert_offset:insert_offset + 2] != b"\x00\x00":
            raise RuntimeError("no aligned padding available for ARM9 module entry")

        struct.pack_into("<H", data, extern_modules_offset, extern_count + 1)
        struct.pack_into("<H", data, insert_offset, anchor_string_offset)

    data[anchor_offset:anchor_offset + 5] = b"ARM9\x00"
    path.write_bytes(data)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
