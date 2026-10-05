"""The scoped completion ledger must account for every reference move."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MoveProgressInventory(unittest.TestCase):
    def test_every_reference_entry_has_a_status(self):
        reference = (ROOT / "docs/gen8-gen9-move-handler-reference.md").read_text()
        progress = (ROOT / "docs/gen8-gen9-move-handler-progress.md").read_text()
        names = re.findall(r'^\| \[([^\]]+)\]\(#', reference, re.M)
        self.assertEqual(len(names), 159)
        self.assertEqual(len(set(names)), 159)
        deferred = progress.split("## Deferred and dependencies", 1)[1].split("Related systems", 1)[0]
        excluded = [name for name in names if name in deferred]
        # Incidental dependent-system names are not indexed move names.
        self.assertEqual(len(excluded), 6)
        implementation = progress.split("## Deferred and dependencies", 1)[0]
        self.assertEqual(len([name for name in names if name in implementation]), 153)
        for name in names:
            with self.subTest(move=name):
                self.assertIn(name, progress)


if __name__ == "__main__":
    unittest.main()
