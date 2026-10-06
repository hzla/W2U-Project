"""Independent oracles for the primary arena, bootstrap and work-area budget."""
import ast
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import audit_white2upgrade_battle_heap as audit


class HeapAccounting(unittest.TestCase):
    def test_budget_includes_primary_allocations_not_work_suballocations_twice(self):
        self.assertEqual(audit.PMC_ROOT_OBJECT_BYTES, 32)
        self.assertEqual(audit.PMC_WORK_AREA_BYTES, (32 + 16) + (4096 + 16))
        self.assertGreaterEqual(audit.PMC_BOOKKEEPING_AND_FRAGMENTATION_RESERVE, 16)
        menu = audit.module_record(ROOT / "assets/testing/MainMenuSkipW2.dll")
        self.assertEqual(menu["allocated_payload_bytes"] + 16, 320)

    def test_production_does_not_stage_or_budget_testing_menu_skip(self):
        self.assertFalse((ROOT / "vfs/data/patches/MainMenuSkip(1).dll").exists())
        for path in (ROOT / "meson.build", ROOT / "src/meson.build"):
            self.assertNotIn("main_menu_skip_patch", path.read_text())

    def test_native_inspector_excludes_constructor_overstatement_and_cycles(self):
        tree = ast.parse((ROOT / "tests/battle/scripts/test-animation-completion.py").read_text())
        observer = next(node for node in tree.body if isinstance(node, ast.ClassDef) and node.name == "Observer")
        method = next(node for node in observer.body if isinstance(node, ast.FunctionDef) and node.name == "pmc_heap_state")
        module = ast.fix_missing_locations(ast.Module(body=[method], type_ignores=[]))
        namespace = {}
        exec(compile(module, "native-inspector", "exec"), namespace)
        area = 0x023ae000
        base = area + 32
        limit = area + 200 * 1024
        values = {area + 4: base, area + 8: 200 * 1024 + 32, area + 12: base,
                  base: 200 * 1024 + 16, base + 4: 0}
        class Memory:
            def read_long(self, address):
                return values.get(address, 0)
        class Inspector:
            pmc_heap_area = area
            emu = type("Emulator", (), {"memory": Memory()})()
        state = namespace["pmc_heap_state"](Inspector())
        self.assertEqual(state["excludedOutOfArenaBytes"], 64)
        self.assertEqual(state["freePayloadBytes"], limit - base - 16)
        values[base + 4] = base
        self.assertIsNone(namespace["pmc_heap_state"](Inspector()))
        values[base + 4] = 0
        values[area + 8] -= 1
        self.assertIsNone(namespace["pmc_heap_state"](Inspector()))


if __name__ == "__main__":
    unittest.main()
