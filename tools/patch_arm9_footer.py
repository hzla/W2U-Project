#!/usr/bin/env python3
import argparse
import struct
from pathlib import Path


ARM9_ROM_OFFSET_HEADER_OFFSET = 0x20
DEFAULT_FOOTER_OFFSET = 0x0FC4


def read_u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    parser = argparse.ArgumentParser(description="Restore the staged ARM9 footer word after ROMBuilder.")
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--arm9", type=Path, required=True)
    parser.add_argument("--offset", type=lambda value: int(value, 0), default=DEFAULT_FOOTER_OFFSET)
    args = parser.parse_args()

    rom = bytearray(args.rom.read_bytes())
    arm9 = args.arm9.read_bytes()

    if args.offset + 4 > len(arm9):
        raise ValueError(f"ARM9 footer offset 0x{args.offset:x} is outside {args.arm9}")

    arm9_rom_offset = read_u32(rom, ARM9_ROM_OFFSET_HEADER_OFFSET)
    rom_footer_offset = arm9_rom_offset + args.offset
    if rom_footer_offset + 4 > len(rom):
        raise ValueError(f"ROM ARM9 footer offset 0x{rom_footer_offset:x} is outside {args.rom}")

    footer = arm9[args.offset : args.offset + 4]
    if rom[rom_footer_offset : rom_footer_offset + 4] != footer:
        rom[rom_footer_offset : rom_footer_offset + 4] = footer
        args.rom.write_bytes(rom)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
