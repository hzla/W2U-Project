#!/usr/bin/env python3

from __future__ import annotations

import struct
import sys
import tempfile
import unittest
from pathlib import Path


TOOLS_DIR = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS_DIR))

import finalize_white2_rom as finalizer


class FinalizeWhite2RomTest(unittest.TestCase):
    def make_rom(self, path: Path, *, boundary: int, file_size: int) -> None:
        header = bytearray(finalizer.HEADER_SIZE)
        header[0x12] = 0x02
        header[finalizer.HEADER_DEVICE_CAPACITY] = 0x0C
        struct.pack_into("<I", header, finalizer.HEADER_ARM9_ROM_OFFSET, 0x4000)
        struct.pack_into("<II", header, finalizer.HEADER_FAT_OFFSET, 0x1000, 8)
        struct.pack_into("<I", header, finalizer.HEADER_USED_ROM_SIZE, boundary - 0x200)
        struct.pack_into("<HH", header, finalizer.HEADER_NTR_REGION_END, boundary >> 19, boundary >> 19)

        arm9i_offset = boundary + 0x3000
        arm7i_offset = boundary + 0x4000
        total_used = boundary + 0x5000
        struct.pack_into("<II", header, finalizer.HEADER_ARM9I_OFFSET, arm9i_offset, 0)
        struct.pack_into("<I", header, finalizer.HEADER_ARM9I_SIZE, 0x1000)
        struct.pack_into("<I", header, finalizer.HEADER_ARM7I_OFFSET, arm7i_offset)
        struct.pack_into("<I", header, finalizer.HEADER_ARM7I_SIZE, 0x1000)
        struct.pack_into("<II", header, finalizer.HEADER_DIGEST_NTR_OFFSET, 0x4000, 0x14000)
        struct.pack_into("<II", header, finalizer.HEADER_DIGEST_TWL_OFFSET, arm9i_offset, 0x2000)
        struct.pack_into("<II", header, finalizer.HEADER_DIGEST_SECTOR_OFFSET, 0x18000, 0x200)
        struct.pack_into("<II", header, finalizer.HEADER_DIGEST_BLOCK_OFFSET, 0x18200, 0x200)
        struct.pack_into("<I", header, finalizer.HEADER_TOTAL_USED_ROM_SIZE, total_used)

        with path.open("wb") as file:
            file.write(header)
            file.write(struct.pack("<II", 0x10000, 0x11000))
            file.truncate(file_size)

    def test_oversize_rom_gets_tested_capacity_and_valid_integrity(self) -> None:
        with tempfile.TemporaryDirectory() as temp_dir:
            rom = Path(temp_dir) / "oversize.nds"
            boundary = 0x20100000
            self.make_rom(rom, boundary=boundary, file_size=boundary + 0x6000)

            layout = finalizer.finalize_rom(rom)
            self.assertEqual(layout.device_capacity, 0x0E)
            self.assertEqual(layout.ntr_twl_boundary, boundary)
            finalizer.validate_rom_layout(rom, verify_integrity=True)

    def test_standard_rom_keeps_original_capacity(self) -> None:
        with tempfile.TemporaryDirectory() as temp_dir:
            rom = Path(temp_dir) / "standard.nds"
            boundary = 0x100000
            self.make_rom(rom, boundary=boundary, file_size=boundary + 0x6000)

            layout = finalizer.finalize_rom(rom)
            self.assertEqual(layout.device_capacity, 0x0C)

    def test_rejects_ntr_file_after_twl_boundary(self) -> None:
        with tempfile.TemporaryDirectory() as temp_dir:
            rom = Path(temp_dir) / "bad-layout.nds"
            boundary = 0x100000
            self.make_rom(rom, boundary=boundary, file_size=boundary + 0x20000)
            with rom.open("r+b") as file:
                file.seek(0x1000)
                file.write(struct.pack("<II", boundary + 0x1000, boundary + 0x2000))

            with self.assertRaisesRegex(ValueError, "FAT payload ends"):
                finalizer.finalize_rom(rom)


if __name__ == "__main__":
    unittest.main()
