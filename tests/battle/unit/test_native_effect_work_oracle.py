"""No-benefit status actions have no queued work and must report failure."""
import ast
from copy import deepcopy
from pathlib import Path
import unittest


class NativeEffectWorkOracle(unittest.TestCase):
    def test_tidy_up_and_take_heart_do_not_require_work_for_failed_actions(self):
        source = Path(__file__).resolve().parents[1] / "scripts/test-move-handlers.py"
        tree = ast.parse(source.read_text())
        def check(value, message):
            if not value:
                raise AssertionError(message)
        namespace = {"verify_completed": lambda *args: None, "check": check,
                     "active_status": lambda mon: mon.get("status", [])}
        for name in ("verify_tidy_up", "verify_take_heart"):
            function = next(node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name == name)
            exec(compile(ast.fix_missing_locations(ast.Module(body=[function], type_ignores=[])), "oracle", "exec"), namespace)
        user = {"slot": 0, "statStages": [12]*7, "hp": 175, "substituteHp": 0}
        target = {"slot": 12, "statStages": [6]*7, "hp": 235, "substituteHp": 0}
        result = {"before": {"attacker": user, "defender": target},
                  "after": {"attacker": deepcopy(user), "defender": deepcopy(target)},
                  "damageCalls": [], "takeHeartEvents": [{"executingSlot": 0, "used": False,
                   "success": False, "after": {"attacker": deepcopy(user)}}],
                  "afterSideEffects": [{str(effect): {"layers": 0} for effect in (6,7,8)} for _ in range(2)]}
        case = {"id": "capped", "userStages": [12]*7, "expectedUserStages": [12]*7,
                "nativeSuccess": False, "takeHeartSuccess": False}
        for name in ("verify_tidy_up", "verify_take_heart"):
            verify = namespace[name]
            verify(case, result, {})
            for bad in ("false-success", "unexpected-work", "wrong-owner", "wrong-stage"):
                changed = deepcopy(result)
                if bad == "false-success":
                    changed["takeHeartEvents"][0]["success"] = True
                elif bad == "unexpected-work":
                    changed["takeHeartEvents"][0]["used"] = True
                elif bad == "wrong-owner":
                    changed["takeHeartEvents"][0]["executingSlot"] = 12
                else:
                    changed["after"]["attacker"]["statStages"][0] = 11
                with self.subTest(oracle=name, mutation=bad), self.assertRaises(AssertionError):
                    verify(case, changed, {})


if __name__ == "__main__":
    unittest.main()
