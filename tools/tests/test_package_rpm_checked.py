"""Packaging errors must not silently preserve a successful stale output."""
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import package_rpm_checked as packager


class CheckedPackaging(unittest.TestCase):
    def test_exit_zero_without_output_fails_and_preserves_previous(self):
        with tempfile.TemporaryDirectory() as root:
            output = Path(root) / "core.dll"
            output.write_bytes(b"previous")
            with patch.object(packager.subprocess, "run"):
                with self.assertRaisesRegex(RuntimeError, "invalid RPM header"):
                    packager.package(Path("tool.jar"), output, ["--fourcc", "DLXF"])
            self.assertEqual(output.read_bytes(), b"previous")
            self.assertEqual(list(Path(root).iterdir()), [output])

    def test_valid_fresh_output_replaces_previous_and_cleans_temporary(self):
        data = bytearray(80)
        data[:4] = b"DLXF"
        struct.pack_into("<II", data, 4, 80, 24)
        data[24:28] = b"DLXH"
        struct.pack_into("<I", data, 32, 20)
        data[44:48] = b"INFO"
        def generate(command, **kwargs):
            Path(command[-1]).write_bytes(data)
        with tempfile.TemporaryDirectory() as root:
            output = Path(root) / "core.dll"
            output.write_bytes(b"previous")
            with patch.object(packager.subprocess, "run", side_effect=generate):
                packager.package(Path("tool.jar"), output, ["--fourcc", "DLXF"])
            self.assertEqual(output.read_bytes(), data)
            self.assertEqual(list(Path(root).iterdir()), [output])


if __name__ == "__main__":
    unittest.main()
