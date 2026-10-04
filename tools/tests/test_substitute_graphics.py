#!/usr/bin/env python3
"""Regression checks for native Substitute resources in expanded pokegra."""

import struct
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "graphics"))
import build_pokegra_battle as graphics


class SubstituteGraphicsTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for offset, (magic, compressed) in enumerate(graphics.SUBSTITUTE_RESOURCE_LAYOUT):
            if magic is None:
                data = struct.pack("<I", 1) + bytes(60)
            else:
                data = magic + struct.pack("<HHIHH", 0xFEFF, 0x100, 16, 16, 0)
            if compressed:
                data = graphics.lz11_compress(data)
            (self.root / str(graphics.SUBSTITUTE_GRAPHICS_START + offset)).write_bytes(data)

    def test_accepts_front_back_and_shared_palette(self):
        graphics.validate_substitute_graphics(self.root)

    def test_rejects_original_crash_wrong_resource_as_texture(self):
        # The old back-sprite ID selected an uncompressed RCMN file; its first
        # word was interpreted as a 0x4e4d43-byte heap allocation request.
        (self.root / "17946").write_bytes((self.root / "17943").read_bytes())
        with self.assertRaisesRegex(ValueError, "17946: expected LZ11"):
            graphics.validate_substitute_graphics(self.root)

    def test_rejects_oversized_decompression_before_allocating(self):
        (self.root / "17940").write_bytes(struct.pack("<I", (0x4E4D43 << 8) | 0x11))
        with self.assertRaisesRegex(ValueError, "17940: invalid expanded size"):
            graphics.validate_substitute_graphics(self.root)

    def test_rejects_wrong_palette_type(self):
        (self.root / "17952").write_bytes((self.root / "17941").read_bytes())
        with self.assertRaisesRegex(ValueError, "17952: invalid RLCN"):
            graphics.validate_substitute_graphics(self.root)


if __name__ == "__main__":
    unittest.main()
