#!/usr/bin/env python3
import argparse
import struct
from pathlib import Path


ARM9_ROM_OFFSET_HEADER_OFFSET = 0x20
DEFAULT_FOOTER_OFFSET = 0x0FC4
MODULE_PARAMS_MAGIC = bytes.fromhex("2106c0de dec00621")


def read_u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def patch_uncompressed_arm9(rom_path: Path, arm9_path: Path,
                            offset: int = DEFAULT_FOOTER_OFFSET) -> None:
    """Normalize startup metadata for the expanded PMC ARM9 staged by this build.

    The old staged binary retains retail's compressedStaticEnd. Restoring that
    nonzero word makes the native bootstrap decode already-expanded instructions
    as BLZ data. Pokeweb-exported fixtures repair it, masking a raw-release boot
    failure. Never copy that stale flag into the standalone ROM.
    """
    arm9 = arm9_path.read_bytes()
    if offset < 0 or offset + 16 > len(arm9):
        raise ValueError(f"ARM9 compression field offset 0x{offset:x} is outside {arm9_path}")
    if arm9[offset + 8:offset + 16] != MODULE_PARAMS_MAGIC:
        raise ValueError("ARM9 compression field is not backed by the expected module-parameter magic")

    with rom_path.open("r+b") as rom:
        header = rom.read(0x40)
        if len(header) != 0x40:
            raise ValueError(f"{rom_path} is too small to contain a Nintendo DS header")
        arm9_rom_offset = read_u32(header, ARM9_ROM_OFFSET_HEADER_OFFSET)
        if read_u32(header, 0x2C) != len(arm9):
            raise ValueError("ROM ARM9 size does not match the staged expanded binary")
        rom_footer_offset = arm9_rom_offset + offset
        rom.seek(0, 2)
        rom_size = rom.tell()
        if arm9_rom_offset < len(header) or arm9_rom_offset + len(arm9) > rom_size:
            raise ValueError(
                f"ROM ARM9 range is outside {rom_path}"
            )
        rom.seek(arm9_rom_offset)
        built = rom.read(len(arm9))
        # Only the compression field may differ after ROMBuilder. Fail before
        # writing if the wrong staged binary or a compressed output was supplied.
        if built[:offset] != arm9[:offset] or built[offset + 4:] != arm9[offset + 4:]:
            raise ValueError("ROM ARM9 differs from the staged expanded binary outside its compression field")
        if built[offset:offset + 4] != b"\0" * 4:
            rom.seek(rom_footer_offset)
            rom.write(b"\0" * 4)


def main() -> int:
    parser = argparse.ArgumentParser(description="Clear stale ARM9 compression metadata after ROMBuilder.")
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--arm9", type=Path, required=True)
    parser.add_argument("--offset", type=lambda value: int(value, 0), default=DEFAULT_FOOTER_OFFSET)
    args = parser.parse_args()
    patch_uncompressed_arm9(args.rom, args.arm9, args.offset)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
