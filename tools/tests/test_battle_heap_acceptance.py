"""Guard the unchanged full-resident-set memory acceptance thresholds."""
import importlib.util
from pathlib import Path
import sys
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
spec = importlib.util.spec_from_file_location("battle_heap", TOOLS / "audit_white2upgrade_battle_heap.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class BattleHeapAcceptance(unittest.TestCase):
    def test_exact_boundaries(self):
        self.assertEqual([], audit.acceptance_failures(103300, 103300 - 8192,
                                                       103300 - 4096, 167936 - 12288))

    def test_each_scenario_fails_closed(self):
        cases = ((103300 - 8191, 103300 - 4096, 100000),
                 (90000, 103300 - 4095, 100000),
                 (90000, 95000, 167936 - 12287))
        for values in cases:
            self.assertEqual(1, len(audit.acceptance_failures(103300, *values)))

    def test_includes_resident_cost_not_just_core(self):
        # A lean core does not excuse other residents exceeding the budget.
        self.assertTrue(audit.acceptance_failures(103300, 103300, 103300, 100000))
        self.assertEqual([], audit.acceptance_failures(103300, 65000, 70000, 111000))


if __name__ == "__main__":
    unittest.main()
