"""Positive/negative controls for the Gen 6/7 audit, without an emulator."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


runner = load("gen67_runner", "test-move-handlers.py")
oracle = load("gen67_oracle", "gen67_move_oracles.py")


class Gen67AuditTests(unittest.TestCase):
    def fixture(self):
        user = {"moveId": 573, "moves": [{"id": 573, "pp": 10}], "hp": 175,
                "maxHp": 175, "slot": 0, "level": 50, "types": [13, 13],
                "stats": [100]*5, "statStages": [6]*7, "conditions": [0]*7,
                "substituteHp": 0}
        target = {**deepcopy(user), "slot": 12, "types": [0, 0], "hp": 235, "maxHp": 235}
        after_user = {**deepcopy(user), "moves": [{"id": 573, "pp": 9}], "turnFlags": 2, "previousMoveId": 573}
        after_target = {**deepcopy(target), "hp": 208}
        result = {"finished": True, "fullTurnValidated": True,
                  "before": {"attacker": user, "defender": target},
                  "after": {"attacker": after_user, "defender": after_target},
                  "damageCalls": [{"attacker": deepcopy(user), "defender": deepcopy(target),
                    "category": 2, "moveType": 14, "powerRewrites": [], "databasePower": 70,
                    "critical": 0, "preModifierDamage": 27, "damageRatio": 4096, "calculatedDamage": 27}]}
        return {"id": "neutral", "completeTurn": True, "audit": {"powers": [70]}}, result, {
            "moveId": 573, "category": 2, "type": 14}

    def verify(self, case, result, variant):
        return oracle.verify(case, result, variant, vars(runner))

    def test_fixture_selection_uses_the_actual_selected_slot(self):
        result = {"selectedMoveSlot": 1, "before": {"attacker": {
            "moveId": 712, "pp": 10, "moves": [{"id": 712, "pp": 10}, {"id": 33, "pp": 35}]}}}
        self.assertEqual(runner.selected_fixture_move(result), {"id": 33, "pp": 35})
        result["selectedMoveSlot"] = 0
        self.assertEqual(runner.selected_fixture_move(result), {"id": 712, "pp": 10})

    def test_called_attack_damage_is_measured_after_triggering_ally(self):
        case, result, variant = self.fixture()
        variant["battleType"] = "Doubles"
        result["battleSetup"] = {"rule": 1, "playerCount": 2, "trainerCount": 2}
        for phase in ("before", "after"):
            result[phase]["ally"] = {**deepcopy(result[phase]["attacker"]), "slot": 1}
            result[phase]["defenderAlly"] = {**deepcopy(result[phase]["defender"]), "slot": 13, "hp": 235}
        result["actionAfter"] = deepcopy(result["before"])
        result["after"]["defender"]["hp"] -= 10
        result["damageCalls"][0]["moveId"] = 573
        result["incomingDamageCalls"] = [{"attacker": result["before"]["ally"],
            "defender": result["before"]["defender"], "moveId": 573, "calculatedDamage": 10}]
        case["audit"].update(extraUserMove=573, incomingTargets=[
            {"source": "ally", "target": "defender", "move": 573, "count": 1}])
        self.assertTrue(self.verify(case, result, variant)["passed"])
        result["after"]["defender"]["hp"] += 1
        with self.assertRaises(AssertionError):
            self.verify(case, result, variant)

    def test_real_completion_damage_and_type_are_required(self):
        case, result, variant = self.fixture()
        self.assertTrue(self.verify(case, result, variant)["passed"])
        for mutate in (
            lambda r: r.update(finished=False),
            lambda r: r.update(fullTurnValidated=False),
            lambda r: r["after"]["attacker"]["moves"][0].update(pp=10),
            lambda r: r["after"]["attacker"].update(previousMoveId=150),
            lambda r: r["after"]["defender"].update(hp=235),
            lambda r: r["damageCalls"][0].update(moveType=0),
            lambda r: r["damageCalls"][0].update(category=1),
            lambda r: r["damageCalls"][0].update(preModifierDamage=28),
            lambda r: r["damageCalls"][0].update(critical=1),
            lambda r: r.update(damageCalls=[]),
        ):
            case, result, variant = self.fixture()
            mutate(result)
            with self.assertRaises(AssertionError):
                self.verify(case, result, variant)

    def test_stolen_stages_affect_damage_before_attack(self):
        case, result, variant = self.fixture()
        case["audit"]["damageUserStages"] = [6, 6, 8, 6, 6, 6, 6]
        result["damageCalls"][0].update(preModifierDamage=53, calculatedDamage=53)
        result["after"]["defender"]["hp"] = 182
        self.assertTrue(self.verify(case, result, variant)["passed"])
        result["damageCalls"][0].update(preModifierDamage=27, calculatedDamage=27)
        with self.assertRaises(AssertionError):
            self.verify(case, result, variant)

    def test_repeated_base_power_has_per_strike_effective_power(self):
        case, result, variant = self.fixture()
        case["audit"].update(powers=[70,70], effectivePowers=[70,140])
        second = deepcopy(result["damageCalls"][0])
        second.update(preModifierDamage=53, calculatedDamage=53)
        result["damageCalls"].append(second)
        result["after"]["defender"]["hp"] = 155
        self.assertTrue(self.verify(case, result, variant)["passed"])

    def test_target_stage_reset_is_not_inferred_from_damage(self):
        case, result, variant = self.fixture()
        case["audit"]["stages"] = {"defender": [6]*7}
        self.assertTrue(self.verify(case, result, variant)["passed"])
        result["after"]["defender"]["statStages"][0] = 8
        with self.assertRaises(AssertionError):
            self.verify(case, result, variant)

    def test_healing_checkpoint_and_unspecified_rounding_are_explicit(self):
        case, result, variant = self.fixture()
        case["audit"] = {"noDamage": True, "healing": {"role": "defender", "ratio": 2048, "rounding": "unspecified"}}
        result["damageCalls"] = []
        result["before"]["defender"]["hp"] = 1
        result["after"]["defender"]["hp"] = 133  # Includes a later residual heal.
        result["actionAfter"] = deepcopy(result["after"])
        result["actionAfter"]["defender"]["hp"] = 119
        self.assertTrue(self.verify(case, result, variant)["passed"])
        result["actionAfter"]["defender"]["hp"] = 118
        self.assertTrue(self.verify(case, result, variant)["passed"])
        result["actionAfter"]["defender"]["hp"] = 120
        with self.assertRaises(AssertionError):
            self.verify(case, result, variant)

    def test_doubles_requires_real_four_battler_setup(self):
        case, result, variant = self.fixture()
        variant["battleType"] = "Doubles"
        with self.assertRaises(AssertionError):
            self.verify(case, result, variant)

    def test_portable_inventory_and_coverage(self):
        inventory = json.loads((ROOT / "gen67-move-inventory.json").read_text())
        moves = inventory["moves"] + inventory["residentMoves"]
        self.assertEqual(len({move["id"] for move in moves}), len(moves))
        self.assertEqual(len(inventory["moves"]), 61)
        self.assertTrue(inventory["zMovesExcluded"])
        excluded = set(range(622,659)) | set(range(695,704)) | {719} | set(range(723,729))
        self.assertFalse(excluded & {move["id"] for move in moves})
        text = (ROOT / "scripts/move-handler-gen67-fixtures.ts").read_text()
        covered = {int(move) for move in re.findall(r"add\((\d+),", text)}
        # These only reproduce native Solar Beam/charge-stat data behavior.
        self.assertEqual({move["id"] for move in moves} - covered, {601,669})
        self.assertNotIn(str(ROOT), json.dumps(inventory))


if __name__ == "__main__":
    unittest.main()
