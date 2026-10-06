"""Fail-closed contracts for byte-identical production cold-boot tests."""
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
spec = importlib.util.spec_from_file_location("normal_boot", ROOT / "tools/test_normal_boot.py")
boot = importlib.util.module_from_spec(spec)
spec.loader.exec_module(boot)


class NormalBoot(unittest.TestCase):
    def fixture(self, directory, *, skip=False, stale=False):
        image = bytearray(0x8000)
        image[0x0C:0x10] = b"IRDO"
        struct.pack_into("<I", image, 0x20, 0x4000)
        struct.pack_into("<I", image, 0x2C, 0x2000)
        offset = 0x4000 + boot.DEFAULT_FOOTER_OFFSET
        image[offset + 8:offset + 16] = boot.MODULE_PARAMS_MAGIC
        struct.pack_into("<I", image, offset, 0x020776CC if stale else 0)
        file = b"MainMenuSkip(1).dll" if skip else b"White2Upgrade.dll"
        fnt = struct.pack("<IHHIHH", 16, 0, 2, 27, 0, 0xF000)
        fnt += b"\x87patches\x01\xf0\0" + bytes([len(file)]) + file + b"\0"
        struct.pack_into("<II", image, 0x40, 0x2000, len(fnt))
        image[0x2000:0x2000 + len(fnt)] = fnt
        path = Path(directory) / "release.nds"
        path.write_bytes(image)
        return path

    def test_accepts_normal_release_and_does_not_modify_it(self):
        with tempfile.TemporaryDirectory() as directory:
            path = self.fixture(directory)
            before = path.read_bytes()
            self.assertEqual(boot.validate_release_startup(path),
                             {"compressed_static_end": 0, "main_menu_skip_staged": False})
            self.assertEqual(path.read_bytes(), before)

    def test_rejects_stale_flag_or_test_skip(self):
        for fault in ("stale", "skip"):
            with self.subTest(fault=fault), tempfile.TemporaryDirectory() as directory:
                path = self.fixture(directory, **{fault: True})
                before = path.read_bytes()
                with self.assertRaises(ValueError):
                    boot.validate_release_startup(path)
                self.assertEqual(path.read_bytes(), before)

    def test_rejects_invalid_ranges_and_wrong_game(self):
        for offset in (0x0C, 0x20, 0x40):
            with self.subTest(offset=offset), tempfile.TemporaryDirectory() as directory:
                path = self.fixture(directory)
                data = bytearray(path.read_bytes())
                struct.pack_into("<I", data, offset, 0xFFFFFFFF)
                path.write_bytes(data)
                with self.assertRaises(ValueError):
                    boot.validate_release_startup(path)

    def test_truncation_and_directory_cycles_fail(self):
        cyclic = struct.pack("<IHH", 8, 0, 1) + b"\x81x\x00\xf0\0"
        for data in (b"", b"\0" * 7, cyclic, struct.pack("<IHH", 8, 0, 1) + b"\x04ab"):
            with self.subTest(data=data), self.assertRaises(ValueError):
                boot.file_names(data)


if __name__ == "__main__":
    unittest.main()
