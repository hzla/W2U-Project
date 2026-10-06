"""Guard the unchanged full-resident-set memory acceptance thresholds."""
import importlib.util
from pathlib import Path
import sys
import struct
import tempfile
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

    def test_post_fix_size_retains_bss(self):
        data=bytearray(160)
        def word(offset,value):struct.pack_into("<I",data,offset,value)
        data[:4]=b"DLXF";word(4,224);word(8,24)
        data[24:28]=b"DLXH";word(32,20);word(36,64)
        data[44:48]=b"INFO";word(52,80)
        data[104:108]=b"REL0";word(112,120)
        with tempfile.TemporaryDirectory(prefix="w2u-rpm-bss-") as directory:
            path=Path(directory)/"fixture.dll";path.write_bytes(data)
            self.assertEqual((224,208),audit.rpm_sizes(path))
            word(36,100);path.write_bytes(data)
            with self.assertRaises(RuntimeError):audit.rpm_sizes(path)


if __name__ == "__main__":
    unittest.main()
