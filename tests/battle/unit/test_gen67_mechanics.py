"""Independent oracle fault injection; a missing mechanic must not pass."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import unittest

SCRIPTS = Path(__file__).resolve().parents[1] / "scripts"


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, SCRIPTS / filename)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


runner = load("mechanic_runner", "test-move-handlers.py")
oracle = load("mechanic_oracle", "gen67_mechanic_oracles.py")


class Gen67MechanicTests(unittest.TestCase):
    def fixture(self):
        user = {"moveId":150,"moves":[{"id":150,"pp":40}],"hp":175,"maxHp":175,
                "slot":0,"level":50,"types":[13,13],"stats":[100]*5,"statStages":[6]*7,
                "conditions":[0]*7,"substituteHp":0,"item":0,"consumedItem":0}
        foe = {**deepcopy(user),"slot":12,"types":[0,0],"hp":235,"maxHp":235,"moves":[{"id":33,"pp":35}]}
        after_foe = {**deepcopy(foe),"moves":[{"id":33,"pp":34}]}
        after_user = {**deepcopy(user),"hp":160,"moves":[{"id":150,"pp":39}],
                      "turnFlags":2,"previousMoveId":150}
        call = {"attacker":deepcopy(foe),"defender":deepcopy(user),"frame":20,"moveId":33,
                "category":1,"moveType":0,"databasePower":50,"powerRewrites":[],"critical":0,
                "preModifierDamage":30,"damageRatio":2048,"calculatedDamage":15}
        case = {"id":"fluffy","mechanicAudit":{"outgoing":[],"incoming":[{"move":33,"finalRatio":2048}]}}
        result = {"finished":True,"fullTurnValidated":True,"before":{"attacker":user,"defender":foe},
                  "after":{"attacker":after_user,"defender":after_foe},
                  "damageCalls":[],"incomingDamageCalls":[call]}
        return case,result,{"moveId":150}

    def verify(self, case, result, variant):
        return oracle.verify(case,result,variant,vars(runner))

    def test_requires_contact_reduction_and_real_hp_loss(self):
        case,result,variant=self.fixture()
        self.assertTrue(self.verify(case,result,variant)["passed"])
        for mutate in (
            lambda r:r["incomingDamageCalls"][0].update(damageRatio=4096,calculatedDamage=30),
            lambda r:r["after"]["attacker"].update(hp=175),
            lambda r:r["incomingDamageCalls"][0].update(preModifierDamage=31),
            lambda r:r["incomingDamageCalls"][0].update(moveType=9),
            lambda r:r["incomingDamageCalls"][0].update(category=2),
            lambda r:r.update(incomingDamageCalls=[]),
            lambda r:r.update(fullTurnValidated=False),
            lambda r:r["after"]["defender"]["moves"][0].update(pp=35),
        ):
            case,result,variant=self.fixture();mutate(result)
            with self.assertRaises(AssertionError):self.verify(case,result,variant)

    def test_item_consumption_and_boost_are_separate_assertions(self):
        case,result,variant=self.fixture()
        case["mechanicAudit"].update(stages={"attacker":[6,6,6,7,6,6,6]},
                                    items={"attacker":0},consumed={"attacker":122})
        result["after"]["attacker"].update(statStages=[6,6,6,7,6,6,6],consumedItem=122)
        self.assertTrue(self.verify(case,result,variant)["passed"])
        for field,value in (("statStages",[6]*7),("item",122),("consumedItem",0)):
            broken=deepcopy(result);broken["after"]["attacker"][field]=value
            with self.assertRaises(AssertionError):self.verify(case,broken,variant)

    def test_priority_requires_actual_order(self):
        case,result,variant=self.fixture()
        attack=deepcopy(result["incomingDamageCalls"][0])
        attack.update(attacker=deepcopy(result["before"]["attacker"]),defender=deepcopy(result["before"]["defender"]),
                      frame=10,preModifierDamage=20,damageRatio=4096,calculatedDamage=20)
        result["damageCalls"]=[attack];result["after"]["defender"]["hp"]-=20
        case["mechanicAudit"].update(outgoing=[{"move":33}],order="user-first")
        self.assertTrue(self.verify(case,result,variant)["passed"])
        attack["frame"]=30
        with self.assertRaises(AssertionError):self.verify(case,result,variant)

    def test_stat_and_power_modifier_rounding_are_distinct(self):
        self.assertEqual(oracle.fixed(101,2048),50)
        self.assertEqual(oracle.fixed(50,4915),60)
        self.assertEqual(oracle.fixed(50,5325),65)
        self.assertEqual(oracle.fixed(95,2048),47)

    def test_form_copy_hp_pool_and_native_actions_are_not_optional(self):
        case,result,variant=self.fixture()
        for checkpoint in ("before","after"):
            result[checkpoint]["attacker"].update(form=0,currentAbility=222)
        case["mechanicAudit"].update(beforeForms={"attacker":0},forms={"attacker":2},
            abilities={"attacker":50},hpPoolGrowth="attacker",actions={"attacker":{"150":1}})
        result["after"]["attacker"].update(form=2,currentAbility=50,maxHp=275,hp=275)
        # This checkpoint tests the form/HP rule, separately from strike damage.
        case["mechanicAudit"]["incoming"]=[];result["incomingDamageCalls"]=[]
        result["mechanicActions"]=[{"slot":0,"move":150,"frame":10}]
        self.assertTrue(self.verify(case,result,variant)["passed"])
        for mutate in (
            lambda r:r["after"]["attacker"].update(form=0),
            lambda r:r["before"]["attacker"].update(form=1),
            lambda r:r["after"]["attacker"].update(currentAbility=222),
            lambda r:r["after"]["attacker"].update(hp=274),
            lambda r:r["after"]["attacker"].update(maxHp=175,hp=175),
            lambda r:r.update(mechanicActions=[]),
            lambda r:r["mechanicActions"].append({"slot":0,"move":150,"frame":11}),
        ):
            broken=deepcopy(result);mutate(broken)
            with self.assertRaises(AssertionError):self.verify(case,broken,variant)

    def test_recover_rounds_up_and_must_precede_the_hit(self):
        case,result,variant=self.fixture()
        case["mechanicAudit"]["healHalfBeforeHit"]=True
        result["before"]["attacker"]["hp"]=60
        result["incomingDamageCalls"][0]["defender"]["hp"]=148
        result["after"]["attacker"]["hp"]=133
        self.assertTrue(self.verify(case,result,variant)["passed"])
        for observed in (60,147):
            broken=deepcopy(result);broken["incomingDamageCalls"][0]["defender"]["hp"]=observed
            with self.assertRaises(AssertionError):self.verify(case,broken,variant)

    def test_gen7_parental_bond_requires_quarter_final_damage_not_half_power(self):
        case,result,variant=self.fixture();variant["moveId"]=33
        result["before"]["attacker"]["moves"]=[{"id":33,"pp":35}]
        result["after"]["attacker"].update(hp=175,moves=[{"id":33,"pp":34}],previousMoveId=33)
        calls=[]
        for hp,ratio,damage in ((235,4096,20),(215,1024,5)):
            call=deepcopy(result["incomingDamageCalls"][0])
            call.update(attacker=deepcopy(result["before"]["attacker"]),defender=deepcopy(result["before"]["defender"]),
                        preModifierDamage=20,damageRatio=ratio,calculatedDamage=damage)
            call["defender"]["hp"]=hp;calls.append(call)
        result.update(damageCalls=calls,incomingDamageCalls=[])
        result["after"]["defender"]["hp"]=210
        case["mechanicAudit"].update(outgoing=[{"move":33},{"move":33,"finalRatio":1024}],incoming=[])
        self.assertTrue(self.verify(case,result,variant)["passed"])
        for mutate in (
            lambda r:r["damageCalls"][1].update(preModifierDamage=11),
            lambda r:r["damageCalls"][1].update(damageRatio=2048),
            lambda r:r["damageCalls"][1]["defender"].update(hp=235),
            lambda r:r["after"]["defender"].update(hp=205),
        ):
            broken=deepcopy(result);mutate(broken)
            with self.assertRaises(AssertionError):self.verify(case,broken,variant)

    def test_forced_replacement_requires_native_party_selection_and_source_pp(self):
        case,result,variant=self.fixture()
        case.update(pivotChoice=1)
        case["mechanicAudit"]["expectedPivot"]=True
        variant["incomingAttackerSpecies"]=149
        result["departingAttacker"]=deepcopy(result["after"])
        result["incomingAttacker"]={"species":149,"slot":1}
        result["partySelections"]=[{"selectedIndex":1,"finished":True}]
        result["after"]["attacker"].update(previousMoveId=0,moves=[{"id":150,"pp":40}],hp=166,slot=1)
        self.assertTrue(self.verify(case,result,variant)["passed"])
        for mutate in (
            lambda r:r.update(partySelections=[]),
            lambda r:r["incomingAttacker"].update(species=151),
            lambda r:r["departingAttacker"]["attacker"]["moves"][0].update(pp=40),
            lambda r:r.update(departingAttacker=None),
        ):
            broken=deepcopy(result);mutate(broken)
            with self.assertRaises(AssertionError):self.verify(case,broken,variant)

    def test_duration_does_not_pass_from_just_setting_terrain(self):
        case,result,variant=self.fixture()
        case["mechanicAudit"]["terrainTimeline"]=[1,0]
        result["terrainState"]={"type":1,"turns":1,"active":1}
        result["laterTurns"]=[{"fullTurnValidated":True,"terrainState":{"type":0,"turns":0,"active":0}}]
        self.assertTrue(self.verify(case,result,variant)["passed"])
        result["laterTurns"][0]["terrainState"]={"type":1,"turns":5,"active":1}
        with self.assertRaises(AssertionError):self.verify(case,result,variant)

    def test_unavailable_child_is_not_a_valid_negative_case(self):
        case,result,variant=self.fixture()
        variant["mechanic"]={"kind":"ability","id":218}
        variant["playerAbilityId"]=218
        result["moduleTelemetry"]={"failureCount":0,"failedModuleMask":0,"loadedModuleCount":1,
                                   "currentChildBytes":1000,"peakChildBytes":1000}
        self.assertTrue(self.verify(case,result,variant)["passed"])
        result["moduleTelemetry"]["failureCount"]=1
        with self.assertRaises(AssertionError):self.verify(case,result,variant)
        result["moduleTelemetry"].update(failureCount=0,loadedModuleCount=0,currentChildBytes=0)
        with self.assertRaises(AssertionError):self.verify(case,result,variant)

    def test_selection_rejection_still_reads_validated_loader_telemetry(self):
        from types import SimpleNamespace
        from unittest.mock import MagicMock
        base, offset, pointer = 0x02200000, 128, 0x02201000
        memory = MagicMock()
        memory.unsigned.__getitem__.return_value = bytes.fromhex("00487047")
        memory.read_long.side_effect = lambda address: pointer if address == base + offset + 4 else 0
        observer = runner.Observer(SimpleNamespace(memory=memory,frame_count=0),
                                   {"coreOffsets":{"W2U_BattleModules_GetTelemetry":offset}})
        observer.probe_addresses = {"move_registration":0x021c5b44}
        observer.move_registration = MagicMock(side_effect=lambda *args:setattr(observer,"core_base",base))
        self.assertEqual(observer.module_telemetry()["failureCount"],0)
        observer.move_registration.assert_called_once_with(None,0x021c5b44)
        memory.unsigned.__getitem__.return_value = b"bad!"
        with self.assertRaises(AssertionError):observer.module_telemetry()

    def test_cli_routes_new_suites_to_shared_native_runner(self):
        from unittest.mock import patch
        from types import SimpleNamespace
        cli=load("mechanic_cli","../../../tools/test_battle.py")
        for suite,move in (("ability","gen67-abilities"),("item","gen67-items")):
            with patch.object(cli.sys,"argv",["test_battle.py",suite,"--suite","gen67","--help"]), \
                 patch.object(cli.subprocess,"run",return_value=SimpleNamespace(returncode=0)) as run:
                self.assertEqual(cli.main(),0)
                self.assertEqual(run.call_args.args[0][-3:],["--move",move,"--help"])

    def test_inventory_does_not_hide_uncovered_abilities(self):
        inventory=json.loads((SCRIPTS.parent/"gen67-mechanic-inventory.json").read_text())
        covered=inventory["coveredAbilityIds"]
        pending=[entry["id"] for entry in inventory["pendingAbilities"]]
        self.assertEqual(sorted(covered+pending),list(range(165,233)))
        self.assertEqual(len(covered),len(set(covered)))
        items=[entry["id"] for entry in inventory["coveredItems"]]
        self.assertEqual(set(items),{114,115,121,122,123,126,127,128,129,485,486,487,488})
        import re
        constants=(SCRIPTS.parents[2]/"include/Items.h").read_text()
        self.assertEqual(int(re.search(r"#define ITEM_PROTECTIVE_PADS (\d+)",constants).group(1)),114)
        self.assertNotIn(125,items)

    def test_summary_keeps_missing_changed_and_failed_cases_visible(self):
        import tempfile
        summary=load("mechanic_summary","summarize-gen67-mechanics.py")
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory)
            (root/"fixtures").mkdir();(root/"trials").mkdir()
            case={"id":"current","mechanicAudit":{"incoming":[]}}
            variant={"name":"fixture","mechanic":{"kind":"ability","id":218},"cases":[case]}
            manifest={"move":"gen67-abilities","variants":[variant]}
            report={"inputRomSha256":"same","selectedVariants":["fixture"]}
            (root/"result.json").write_text(json.dumps(report))
            (root/"fixtures/suite.json").write_text(json.dumps(manifest))
            (root/"trials/fixture-batch.json").write_text(json.dumps({"snapshotReleased":True}))
            (root/"trials/fixture-current.json").write_text("{}")
            result=summary.summarize([root],lambda *args:None)
            self.assertTrue(result["passed"] and result["complete"])
            def failing(*args):raise AssertionError("bad damage")
            self.assertFalse(summary.summarize([root],failing)["passed"])
            # A later catalog adds a case that was never run: not green.
            manifest["variants"][0]["cases"].append({"id":"unrun"})
            report["selectedVariants"]=[]
            (root/"fixtures/suite.json").write_text(json.dumps(manifest))
            (root/"result.json").write_text(json.dumps(report))
            missing=summary.summarize([root],lambda *args:None)
            self.assertFalse(missing["passed"] or missing["complete"])
            self.assertEqual(missing["caseCount"],2)

    def test_summary_semantics_pin_party_not_trainer_numbers(self):
        summary=load("semantic_summary","summarize-gen67-mechanics.py")
        first={"trainerId":1,"player":{"speciesId":151,"itemId":0},"moveId":33}
        later={**deepcopy(first),"trainerId":6,"coreOffsets":{"getter":42}}
        self.assertEqual(summary.semantic_variant(first),summary.semantic_variant(later))
        later["player"]["itemId"]=124
        self.assertNotEqual(summary.semantic_variant(first),summary.semantic_variant(later))
        later=deepcopy(first);later["trainerBagItems"]=[0,0,0,0]
        self.assertNotEqual(summary.semantic_variant(first),summary.semantic_variant(later))

    def test_audit_fixtures_clear_inherited_trainer_bag(self):
        fixtures=(SCRIPTS/"gen67-mechanic-fixtures.ts").read_text()
        builder=(SCRIPTS/"build-move-handler-fixtures.ts").read_text()
        self.assertIn("trainerBagItems:[0,0,0,0]",fixtures)
        self.assertIn('trainer[`item_${slot + 1}`] = item',builder)
        self.assertIn('markDirty(project, "trdata", variant.trainerId)',builder)


if __name__ == "__main__":unittest.main()
