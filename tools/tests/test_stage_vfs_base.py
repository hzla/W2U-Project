#!/usr/bin/env python3
"""Check generated VFS bootstrap data without requiring a retail ROM."""

import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import stage_vfs_base as stage


class VfsBaseTest(unittest.TestCase):
    def test_overlay_table_preserves_retail_entries_and_appends_pmc(self):
        retail = b"".join(struct.pack("<8I", i, 0, 0, 0, 0, 0, i, 0) for i in range(344))
        result = stage.overlay_table(retail, 12288)
        self.assertEqual(result[:-32], retail)
        self.assertEqual(struct.unpack("<8I", result[-32:]),
                         (344, 0x021FD0C0, 12288, 0, 0x021FD0C0, 0x021FD0C0, 344, 0x02000000))

    def test_overlay_table_rejects_an_already_patched_table(self):
        with self.assertRaises(ValueError):
            stage.overlay_table(bytes(345 * 32), 12288)

    def test_zone_patch_changes_only_the_existing_nineteen_flags(self):
        retail = bytes([0xDF]) * 29520
        result = stage.zone_data(retail)
        differences = [i for i, (a, b) in enumerate(zip(retail, result)) if a != b]
        self.assertEqual(differences, list(range(0x36D5, 0x3A06, 0x30)) + [0x3F15])
        self.assertEqual(len(differences), 19)
        self.assertTrue(all(result[i] == 0xFF for i in differences))

    def test_zone_patch_rejects_an_unexpected_input(self):
        with self.assertRaises(ValueError):
            stage.zone_data(bytes(29520))


if __name__ == "__main__":
    unittest.main()
