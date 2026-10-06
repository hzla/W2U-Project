"""Unknown move labels must stop the build rather than silently become zero."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MoveMetadataLabels(unittest.TestCase):
    def test_real_record_and_unknown_quality_target_flag(self):
        original = (ROOT / "data/pml/moves/882.toml").read_text()
        cases = (None, ('"EFFECT_OTHERS"', '"UNDEFINED_QUALITY"'),
                 ('"TARGET_USER"', '"UNDEFINED_TARGET"'),
                 ('Flags = "', 'Flags = "UNDEFINED_FLAG | '))
        with tempfile.TemporaryDirectory(prefix="w2u-move-labels-") as directory:
            source, output = Path(directory) / "move.toml", Path(directory) / "move.bin"
            for replacement in cases:
                with self.subTest(replacement=replacement):
                    text = original
                    if replacement:
                        self.assertIn(replacement[0], text)
                        text = text.replace(*replacement)
                    source.write_text(text)
                    result = subprocess.run([sys.executable, str(ROOT / "tools/mkdata/mkdata.py"),
                        "generic", str(source), str(output), "format", "moves"],
                        text=True, capture_output=True)
                    if replacement:
                        self.assertNotEqual(result.returncode, 0)
                        self.assertIn("not defined", result.stderr)
                    else:
                        self.assertEqual(result.returncode, 0, result.stderr)
                        self.assertEqual(len(output.read_bytes()), 36)


if __name__ == "__main__":
    unittest.main()
