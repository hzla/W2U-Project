#!/usr/bin/env python3

from __future__ import annotations

import argparse
import hashlib
import struct
from dataclasses import dataclass
from pathlib import Path


HEADER_SIZE = 0x1000
NTR_TWL_ALIGNMENT = 0x80000
STANDARD_DS_ROM_LIMIT = 0x20000000
# CTRMap tracks output positions with signed Java ints. Keep the final byte
# address representable even though the DS card protocol itself uses u32.
MAX_SUPPORTED_ROM_SIZE = 0x7FFFFFFF
OVERSIZE_DEVICE_CAPACITY = 0x0E

HEADER_DEVICE_CAPACITY = 0x14
HEADER_ARM9_ROM_OFFSET = 0x20
HEADER_FAT_OFFSET = 0x48
HEADER_FAT_LENGTH = 0x4C
HEADER_SECURE_AREA_CRC = 0x6C
HEADER_USED_ROM_SIZE = 0x80
HEADER_NTR_REGION_END = 0x90
HEADER_TWL_REGION_START = 0x92
HEADER_LOGO_CRC = 0x15C
HEADER_CRC = 0x15E
HEADER_ARM9I_OFFSET = 0x1C0
HEADER_ARM9I_SIZE = 0x1CC
HEADER_ARM7I_OFFSET = 0x1D0
HEADER_ARM7I_SIZE = 0x1DC
HEADER_DIGEST_NTR_OFFSET = 0x1E0
HEADER_DIGEST_NTR_LENGTH = 0x1E4
HEADER_DIGEST_TWL_OFFSET = 0x1E8
HEADER_DIGEST_TWL_LENGTH = 0x1EC
HEADER_DIGEST_SECTOR_OFFSET = 0x1F0
HEADER_DIGEST_SECTOR_LENGTH = 0x1F4
HEADER_DIGEST_BLOCK_OFFSET = 0x1F8
HEADER_DIGEST_BLOCK_LENGTH = 0x1FC
HEADER_TOTAL_USED_ROM_SIZE = 0x210
HEADER_SIGNATURE_OFFSET = 0xF80
HEADER_SIGNATURE_SIZE = 0x80


@dataclass(frozen=True)
class RomLayout:
    file_size: int
    device_capacity: int
    used_rom_size: int
    ntr_twl_boundary: int
    total_used_rom_size: int
    max_fat_end: int


def read_u16(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def read_u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def write_u16(data: bytearray, offset: int, value: int) -> None:
    struct.pack_into("<H", data, offset, value)


def crc16_nintendo(data: bytes | bytearray) -> int:
    crc = 0xFFFF
    for value in data:
        crc ^= value
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if crc & 1 else crc >> 1
    return crc & 0xFFFF


def ctrmap_header_signature(header: bytes | bytearray) -> bytes:
    digest = hashlib.sha1(header[:0xE00]).digest()
    return b"\x00\x01" + b"\xFF" * 105 + b"\x00" + digest


def checked_range(label: str, offset: int, length: int, file_size: int) -> None:
    if offset < 0 or length < 0 or offset > file_size or length > file_size - offset:
        raise ValueError(
            f"{label} range 0x{offset:x}..0x{offset + length:x} is outside "
            f"the 0x{file_size:x}-byte ROM"
        )


def read_header(rom_path: Path) -> bytearray:
    with rom_path.open("rb") as file:
        header = bytearray(file.read(HEADER_SIZE))
    if len(header) != HEADER_SIZE:
        raise ValueError(f"{rom_path} is too small to contain an extended Nintendo DS header")
    return header


def read_fat_entries(rom_path: Path, header: bytes | bytearray) -> list[tuple[int, int]]:
    file_size = rom_path.stat().st_size
    fat_offset = read_u32(header, HEADER_FAT_OFFSET)
    fat_length = read_u32(header, HEADER_FAT_LENGTH)
    if fat_length == 0 or fat_length % 8:
        raise ValueError(f"invalid FAT length 0x{fat_length:x}")
    checked_range("FAT", fat_offset, fat_length, file_size)
    with rom_path.open("rb") as file:
        file.seek(fat_offset)
        fat = file.read(fat_length)
    return [struct.unpack_from("<II", fat, offset) for offset in range(0, fat_length, 8)]


def validate_rom_layout(
    rom_path: Path,
    *,
    verify_integrity: bool = True,
    verify_capacity: bool = True,
) -> RomLayout:
    header = read_header(rom_path)
    file_size = rom_path.stat().st_size
    if file_size > MAX_SUPPORTED_ROM_SIZE:
        raise ValueError(
            f"ROM size 0x{file_size:x} reaches or exceeds CTRMap's signed 2 GiB limit"
        )
    if not header[0x12] & 0x02:
        raise ValueError("White 2 output is expected to contain a TWL-extended header")

    ntr_end_units = read_u16(header, HEADER_NTR_REGION_END)
    twl_start_units = read_u16(header, HEADER_TWL_REGION_START)
    if ntr_end_units != twl_start_units:
        raise ValueError(
            "NTR/TWL boundary mismatch: "
            f"header[0x90]=0x{ntr_end_units:x}, header[0x92]=0x{twl_start_units:x}"
        )
    boundary = twl_start_units * NTR_TWL_ALIGNMENT
    used_rom_size = read_u32(header, HEADER_USED_ROM_SIZE)
    total_used_rom_size = read_u32(header, HEADER_TOTAL_USED_ROM_SIZE)
    if used_rom_size > boundary or boundary - used_rom_size >= NTR_TWL_ALIGNMENT:
        raise ValueError(
            f"NTR used end 0x{used_rom_size:x} is inconsistent with boundary 0x{boundary:x}"
        )
    if total_used_rom_size < boundary or total_used_rom_size > file_size:
        raise ValueError(
            f"total used size 0x{total_used_rom_size:x} is inconsistent with "
            f"boundary 0x{boundary:x} and file size 0x{file_size:x}"
        )

    fat_entries = read_fat_entries(rom_path, header)
    for file_id, (start, end) in enumerate(fat_entries):
        if start > end:
            raise ValueError(f"FAT file {file_id} has reversed range 0x{start:x}..0x{end:x}")
        checked_range(f"FAT file {file_id}", start, end - start, file_size)
    max_fat_end = max((end for _, end in fat_entries), default=0)

    digest_ntr_offset = read_u32(header, HEADER_DIGEST_NTR_OFFSET)
    digest_ntr_length = read_u32(header, HEADER_DIGEST_NTR_LENGTH)
    digest_sector_offset = read_u32(header, HEADER_DIGEST_SECTOR_OFFSET)
    digest_sector_length = read_u32(header, HEADER_DIGEST_SECTOR_LENGTH)
    digest_block_offset = read_u32(header, HEADER_DIGEST_BLOCK_OFFSET)
    digest_block_length = read_u32(header, HEADER_DIGEST_BLOCK_LENGTH)
    if digest_ntr_offset + digest_ntr_length != digest_sector_offset:
        raise ValueError("NTR digest region does not end at the sector hash table")
    if max_fat_end > digest_sector_offset:
        raise ValueError(
            f"FAT payload ends at 0x{max_fat_end:x}, after the NTR file-data limit "
            f"0x{digest_sector_offset:x}"
        )
    checked_range("digest sector hash table", digest_sector_offset, digest_sector_length, file_size)
    checked_range("digest block hash table", digest_block_offset, digest_block_length, file_size)
    if digest_sector_offset + digest_sector_length > used_rom_size:
        raise ValueError("digest sector hash table extends past the NTR used end")
    if digest_block_offset + digest_block_length > used_rom_size:
        raise ValueError("digest block hash table extends past the NTR used end")

    arm9i_offset = read_u32(header, HEADER_ARM9I_OFFSET)
    arm9i_size = read_u32(header, HEADER_ARM9I_SIZE)
    arm7i_offset = read_u32(header, HEADER_ARM7I_OFFSET)
    arm7i_size = read_u32(header, HEADER_ARM7I_SIZE)
    digest_twl_offset = read_u32(header, HEADER_DIGEST_TWL_OFFSET)
    digest_twl_length = read_u32(header, HEADER_DIGEST_TWL_LENGTH)
    for label, offset, length in (
        ("ARM9i", arm9i_offset, arm9i_size),
        ("ARM7i", arm7i_offset, arm7i_size),
        ("TWL digest region", digest_twl_offset, digest_twl_length),
    ):
        if offset < boundary:
            raise ValueError(f"{label} starts before the NTR/TWL boundary")
        checked_range(label, offset, length, total_used_rom_size)

    device_capacity = header[HEADER_DEVICE_CAPACITY]
    if (
        verify_capacity
        and file_size > STANDARD_DS_ROM_LIMIT
        and device_capacity != OVERSIZE_DEVICE_CAPACITY
    ):
        raise ValueError(
            f"oversized ROM advertises device capacity 0x{device_capacity:02x}; "
            f"expected tested 2 GiB value 0x{OVERSIZE_DEVICE_CAPACITY:02x}"
        )

    if verify_integrity:
        arm9_offset = read_u32(header, HEADER_ARM9_ROM_OFFSET)
        if arm9_offset > 0x8000:
            raise ValueError(f"ARM9 offset 0x{arm9_offset:x} is past the secure-area CRC end")
        with rom_path.open("rb") as file:
            file.seek(arm9_offset)
            secure_area = file.read(0x8000 - arm9_offset)
        expected_secure_crc = crc16_nintendo(secure_area)
        if read_u16(header, HEADER_SECURE_AREA_CRC) != expected_secure_crc:
            raise ValueError("secure-area CRC is stale")
        if read_u16(header, HEADER_LOGO_CRC) != crc16_nintendo(header[0xC0:0x15C]):
            raise ValueError("Nintendo logo CRC is stale")
        if read_u16(header, HEADER_CRC) != crc16_nintendo(header[:HEADER_CRC]):
            raise ValueError("header CRC is stale")
        signature = header[
            HEADER_SIGNATURE_OFFSET : HEADER_SIGNATURE_OFFSET + HEADER_SIGNATURE_SIZE
        ]
        if signature != ctrmap_header_signature(header):
            raise ValueError("CTRMap DSi header signature digest is stale")

    return RomLayout(
        file_size=file_size,
        device_capacity=device_capacity,
        used_rom_size=used_rom_size,
        ntr_twl_boundary=boundary,
        total_used_rom_size=total_used_rom_size,
        max_fat_end=max_fat_end,
    )


def finalize_rom(rom_path: Path) -> RomLayout:
    # Validate placement before changing metadata. A stale boundary cannot be
    # repaired safely here because the TWL binaries and digest tables must be
    # emitted after all NTR files by ROMBuilder.
    validate_rom_layout(rom_path, verify_integrity=False, verify_capacity=False)

    with rom_path.open("r+b") as file:
        header = bytearray(file.read(HEADER_SIZE))
        if rom_path.stat().st_size > STANDARD_DS_ROM_LIMIT:
            header[HEADER_DEVICE_CAPACITY] = OVERSIZE_DEVICE_CAPACITY

        arm9_offset = read_u32(header, HEADER_ARM9_ROM_OFFSET)
        if arm9_offset > 0x8000:
            raise ValueError(f"ARM9 offset 0x{arm9_offset:x} is past the secure-area CRC end")
        file.seek(arm9_offset)
        secure_area = file.read(0x8000 - arm9_offset)
        write_u16(header, HEADER_SECURE_AREA_CRC, crc16_nintendo(secure_area))
        write_u16(header, HEADER_LOGO_CRC, crc16_nintendo(header[0xC0:0x15C]))
        write_u16(header, HEADER_CRC, crc16_nintendo(header[:HEADER_CRC]))
        header[
            HEADER_SIGNATURE_OFFSET : HEADER_SIGNATURE_OFFSET + HEADER_SIGNATURE_SIZE
        ] = ctrmap_header_signature(header)

        file.seek(0)
        file.write(header)

    return validate_rom_layout(rom_path, verify_integrity=True)


def main() -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Finalize and validate CTRMap's White 2 NTR/TWL ROM layout, including "
            "the tested post-512-MiB capacity metadata."
        )
    )
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument(
        "--verify-only",
        action="store_true",
        help="Validate without changing capacity or integrity fields.",
    )
    args = parser.parse_args()

    if not args.rom.is_file():
        raise FileNotFoundError(args.rom)
    layout = (
        validate_rom_layout(args.rom, verify_integrity=True)
        if args.verify_only
        else finalize_rom(args.rom)
    )
    print(
        f"ROM layout OK: size=0x{layout.file_size:x}, "
        f"NTR/TWL=0x{layout.ntr_twl_boundary:x}, "
        f"NTR-used=0x{layout.used_rom_size:x}, "
        f"TWL-used=0x{layout.total_used_rom_size:x}, "
        f"capacity=0x{layout.device_capacity:02x}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
