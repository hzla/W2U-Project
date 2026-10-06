"""Incomplete retries, provenance drift and later failures stay unaccepted."""
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import summarize_w2_integration_regressions as summary


class NativeSummary(unittest.TestCase):
    def test_retries_preserve_failed_attempts_and_require_complete_provenance(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            def batch(name, good=True, complete=True, digest="first"):
                data = {"passed":good,"completeSuite":complete,"inputRomSha256":digest,
                        "cases":[{"passed":good}],"fullTurnValidated":good}
                (root / name).write_text(json.dumps(data))
                return {"selectedSuites":["move"],"inputRomSha256":digest,"results":[
                    {"suite":"move","report":name,"exitCode":0 if good else 1,"passed":good}]}
            failed = batch("failed.json",good=False)
            retry = batch("retry.json",digest="final")
            result = summary.reconcile([failed,retry],root)
            self.assertTrue(result["passed"])
            self.assertEqual(len(result["failed_or_incomplete_attempts"]),1)
            self.assertEqual(result["accepted_rom_sha256s"],["final"])
            for later in (batch("partial.json",complete=False),batch("later-failure.json",good=False)):
                self.assertFalse(summary.reconcile([retry,later],root)["passed"])
            retry["inputRomSha256"]="wrong"
            self.assertFalse(summary.reconcile([failed,retry],root)["passed"])

    def test_missing_suites_and_path_escape_fail_closed(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory)
            empty={"selectedSuites":["move"],"inputRomSha256":"rom","results":[]}
            self.assertEqual(summary.reconcile([empty],root)["missing_suites"],["move"])
            bad={**empty,"results":[{"suite":"move","report":"../outside.json"}]}
            with self.assertRaises(ValueError):summary.reconcile([bad],root)


if __name__ == "__main__":
    unittest.main()
