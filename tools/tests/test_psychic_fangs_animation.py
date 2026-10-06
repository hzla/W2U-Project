"""Pin the reviewed donor animation without redistributing the donor ROM."""
import hashlib
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[2]


class PsychicFangsAnimation(unittest.TestCase):
    def test_donor_script_and_dependency_operands(self):
        mapping = json.loads((ROOT / "data/graphics/move_animations/import_maps/vw2qol-psychic-fangs.json").read_text())
        verified = mapping["verification"]
        script = (ROOT / "data/graphics/move_animations/5_00000706.bin").read_bytes()
        self.assertEqual(mapping["replacementMap"], {"Egg Bomb": "Psychic Fangs"})
        self.assertEqual(len(script), verified["scriptBytes"])
        self.assertEqual(hashlib.sha256(script).hexdigest(), verified["scriptSha256"])
        self.assertEqual(verified["sourceMember"], 121)
        self.assertEqual(verified["targetMember"], 706)
        spa = verified["particles"][0]
        word = struct.pack("<I", spa["id"])
        offsets = [i for i in range(len(script) - 3) if script[i:i + 4] == word]
        self.assertEqual(offsets, spa["scriptReferenceOffsets"])
        # All five Emit operands use valid resource IDs 0..4 (after the SPA word).
        self.assertEqual([struct.unpack_from("<I", script, i + 4)[0] for i in offsets[1:]], list(range(spa["resources"])))
        self.assertFalse((ROOT / "data/graphics/move_spas/6_00000326.bin").exists())

    def test_shared_geomancy_and_laser_focus_particles_are_unchanged(self):
        for id, expected in ((748, "04ec419c2ff10ba525a08976e2fa408ee10087c0a49aafaeada5b3f9ddbf383a"),
                             (798, "9f12c4cafc7fbcc6fc6e1f96fb760590220b8acfe6c389ed37919d792c2217b6")):
            data = (ROOT / f"data/graphics/move_spas/6_{id:08d}.bin").read_bytes()
            self.assertEqual(hashlib.sha256(data).hexdigest(), expected)


if __name__ == "__main__":
    unittest.main()
