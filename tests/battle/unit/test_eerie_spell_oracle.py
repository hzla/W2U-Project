"""The PP oracle retains strict work/amount checks across a native turn reset."""
import ast
from copy import deepcopy
from pathlib import Path
import unittest


class EerieSpellOracle(unittest.TestCase):
    def test_slow_action_pp_is_not_confused_with_custom_drain(self):
        source = Path(__file__).resolve().parents[1] / "scripts/test-move-handlers.py"
        tree = ast.parse(source.read_text())
        function = next(node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name == "verify_eerie_spell")
        def check(value, message):
            if not value:
                raise AssertionError(message)
        namespace = {"verify_power": lambda *args: {}, "check": check}
        exec(compile(ast.fix_missing_locations(ast.Module(body=[function], type_ignores=[])), "oracle", "exec"), namespace)
        target = {"previousMove": 0, "turnFlags": 0, "slot": 12, "moves": [{"id": 150, "pp": 40}]}
        after = {"previousMoveId": 150, "turnFlags": 0, "moves": [{"id": 150, "pp": 39}]}
        result = {"damageCalls": [{"defender": target}], "after": {"defender": after}, "ppWork": [], "fullTurnValidated": True}
        case = {"expectedLastMove": 0, "expectedPpDrain": 0, "id": "no-history"}
        verify = namespace["verify_eerie_spell"]
        verify(case, result, {"trainerMove": 150})
        for bad in ("extra-drain", "unobserved-move", "unexpected-work"):
            changed = deepcopy(result)
            if bad == "extra-drain":
                changed["after"]["defender"]["moves"][0]["pp"] = 38
            elif bad == "unobserved-move":
                changed["after"]["defender"]["previousMoveId"] = 0
            else:
                changed["ppWork"] = [{"target": 12, "slot": 0, "amount": 1}]
            with self.assertRaises(AssertionError):
                verify(case, changed, {"trainerMove": 150})


if __name__ == "__main__":
    unittest.main()
