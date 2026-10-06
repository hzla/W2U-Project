"""Per-sprite stream payload bounds do not conflate game and PMC heaps."""
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import audit_w2anim_game_heap as audit


def archive():
    data = bytearray(100)
    struct.pack_into("<4sHHII", data, 0, b"W2AS", 1, 0, 1, 16)
    struct.pack_into("<HHIII", data, 16, 4, 1, 0, 32, 0)
    struct.pack_into("<4s6H3I", data, 32, b"MANI", 2, 2, 96, 96, 1, 1, 28, 32, 0)
    struct.pack_into("<HH", data, 60, 0, 1)
    struct.pack_into("<II", data, 64, 40, 5)
    data[72:77] = b"\x10\x00\x12\x00\x00"
    return data


class StreamGameHeap(unittest.TestCase):
    def test_exact_payloads_and_distinct_heap(self):
        result = audit.inspect(archive())
        maximum = result["max_per_sprite"]
        self.assertEqual(maximum["metadata_bytes"], 12)
        self.assertEqual(maximum["compressed_buffer_bytes"], 8)
        self.assertEqual(maximum["staging_bytes"], 4608)
        self.assertEqual(result["four_sprite_payload_upper_bound"], 4 * 4628)
        self.assertEqual(result["eight_slot_payload_upper_bound"], 8 * 4628)
        self.assertEqual(result["pmc_heap_bytes"], 0)
        self.assertEqual(result["allocations_per_sprite"], 3)

    def test_truncated_counts_and_unsupported_dimensions_are_rejected(self):
        for offset, fmt, value in ((4,"H",2), (12,"I",104), (40,"H",258),
                                   (42,"H",129), (44,"H",65535), (64,"I",100),
                                   (68,"I",21000)):
            bad = archive()
            struct.pack_into("<" + fmt, bad, offset, value)
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                audit.inspect(bad)
        for length in range(77):
            with self.subTest(length=length), self.assertRaises(ValueError):
                audit.inspect(archive()[:length])

    def test_packaged_archive_payload_budget(self):
        result = audit.inspect((ROOT / "vfs/data/w2anim/streams.bin").read_bytes())
        self.assertEqual(result["entry_count"], 1147)
        self.assertEqual(result["max_per_sprite"]["payload_bytes"], 8084)
        self.assertEqual(result["eight_slot_payload_upper_bound"], 64672)


if __name__ == "__main__":
    unittest.main()
