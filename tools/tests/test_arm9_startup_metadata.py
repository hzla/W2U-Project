"""Unmodified release bootstrap must not decompress an expanded ARM9 twice."""
import importlib.util
from pathlib import Path
import struct
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location("arm9_startup", ROOT / "tools/patch_arm9_footer.py")
startup = importlib.util.module_from_spec(spec)
spec.loader.exec_module(startup)


class Arm9Startup(unittest.TestCase):
    def fixture(self, directory):
        arm9 = bytearray(0x2000)
        offset = startup.DEFAULT_FOOTER_OFFSET
        struct.pack_into("<I", arm9, offset, 0x020776CC)
        arm9[offset + 8:offset + 16] = startup.MODULE_PARAMS_MAGIC
        stage = Path(directory) / "arm9.bin"
        stage.write_bytes(arm9)
        image = bytearray(0x8000)
        struct.pack_into("<I", image, 0x20, 0x4000)
        struct.pack_into("<I", image, 0x2C, len(arm9))
        image[0x4000:0x6000] = arm9
        rom = Path(directory) / "release.nds"
        rom.write_bytes(image)
        return stage, rom, bytes(image)

    def test_stale_flag_zeroed_only_in_rom_and_idempotent(self):
        with tempfile.TemporaryDirectory() as directory:
            stage, rom, before = self.fixture(directory)
            startup.patch_uncompressed_arm9(rom, stage)
            expected = bytearray(before)
            offset = 0x4000 + startup.DEFAULT_FOOTER_OFFSET
            expected[offset:offset + 4] = b"\0" * 4
            self.assertEqual(rom.read_bytes(), expected)
            self.assertEqual(startup.read_u32(stage.read_bytes(), startup.DEFAULT_FOOTER_OFFSET), 0x020776CC)
            startup.patch_uncompressed_arm9(rom, stage)
            self.assertEqual(rom.read_bytes(), expected)

    def test_wrong_magic_rejected_without_rom_mutation(self):
        with tempfile.TemporaryDirectory() as directory:
            stage, rom, before = self.fixture(directory)
            arm9 = bytearray(stage.read_bytes())
            arm9[startup.DEFAULT_FOOTER_OFFSET + 8] ^= 1
            stage.write_bytes(arm9)
            with self.assertRaisesRegex(ValueError, "magic"):
                startup.patch_uncompressed_arm9(rom, stage)
            self.assertEqual(rom.read_bytes(), before)

    def test_wrong_binary_or_length_rejected_without_mutation(self):
        for field in (0x2C, 0x4000 + 0x1800):
            with self.subTest(field=field), tempfile.TemporaryDirectory() as directory:
                stage, rom, before = self.fixture(directory)
                image = bytearray(before)
                image[field] ^= 1
                rom.write_bytes(image)
                with self.assertRaises(ValueError):
                    startup.patch_uncompressed_arm9(rom, stage)
                self.assertEqual(rom.read_bytes(), image)

    def test_staged_pmc_binary_identifies_the_supported_compression_field(self):
        arm9 = (ROOT / "pmc/ARM9PMC.bin").read_bytes()
        offset = startup.DEFAULT_FOOTER_OFFSET
        self.assertEqual(arm9[offset + 8:offset + 16], startup.MODULE_PARAMS_MAGIC)


if __name__ == "__main__":
    unittest.main()
