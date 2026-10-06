"""Multi ownership and hit-history oracles reject mislabeled doubles/results."""
from copy import deepcopy
import importlib.util
from pathlib import Path
import unittest

spec=importlib.util.spec_from_file_location("multi_runner",Path(__file__).resolve().parents[1]/"scripts/test-move-handlers.py")
runner=importlib.util.module_from_spec(spec)
spec.loader.exec_module(runner)


class MultiOracleTests(unittest.TestCase):
    def test_native_party_choice_tracks_identity_after_reordering(self):
        self.assertEqual(runner.multi_party_choice([0,1],1),1)
        self.assertEqual(runner.multi_party_choice([1,0],0),1)
        self.assertEqual(runner.multi_party_choice([1,0],1),0)
        for party,choice in (([0,0],0),([1],0)):
            with self.assertRaises(AssertionError):runner.multi_party_choice(party,choice)

    def test_exact_named_case_filter_does_not_mutate_manifest(self):
        variants=[{"name":"one","cases":[{"id":"a"},{"id":"b"}]},
                  {"name":"two","cases":[{"id":"c"}]}]
        self.assertEqual(runner.select_cases(variants,["b"]),[{"name":"one","cases":[{"id":"b"}]}])
        self.assertEqual(len(variants[0]["cases"]),2)
        for names in (["missing"],["b","b"]):
            with self.assertRaises(AssertionError):runner.select_cases(variants,names)

    def fixture(self):
        user={"slot":0,"species":151,"hp":200,"level":100,"stats":[236]*5,"types":[13,13],
              "moves":[{"id":889,"pp":10}],"turnFlags":0,"previousMoveId":0}
        target={"slot":18,"species":442,"hp":241,"stats":[236]*5}
        before={"attacker":user,"ally":{"slot":6},"defender":{"slot":12},"defenderAlly":target}
        after=deepcopy(before)
        after["attacker"].update(moves=[{"id":889,"pp":9}],turnFlags=2,previousMoveId=889)
        after["ally"]["previousMoveId"]=150
        after["defender"]["previousMoveId"]=129
        after["defenderAlly"].update(previousMoveId=150,hp=204)
        call={"attacker":user,"defender":target,"powerRewrites":[],"databasePower":50,
              "category":1,"critical":0,"targetDamageRatio":4096,"preModifierDamage":37,"calculatedDamage":37}
        return {"id":"fresh","expectedMultiPower":50},{"before":before,"after":after,"finished":True,
            "fullTurnValidated":True,"damageCalls":[call],"setup":[],"battleSetup":{
                "rule":1,"multiMode":3,"partyCounts":[2,1,1,1],"partyPointers":[100,200,300,400]}},{"battleType":"Multi"}

    def test_native_multi_contract(self):
        self.assertTrue(runner.verify_multi(*self.fixture())["passed"])

    def test_mislabeled_doubles_and_false_damage_fail(self):
        for mutate in (lambda r:r["battleSetup"].update(multiMode=0),
                       lambda r:r["battleSetup"].update(partyCounts=[2,2,0,0]),
                       lambda r:r["battleSetup"].update(partyPointers=[100,200,100,400]),
                       lambda r:r["before"]["ally"].update(slot=1),
                       lambda r:r["damageCalls"][0].update(powerRewrites=[100]),
                       lambda r:r["damageCalls"][0].update(calculatedDamage=38),
                       lambda r:r["after"]["defenderAlly"].update(hp=241),
                       lambda r:r.update(fullTurnValidated=False)):
            case,result,variant=self.fixture()
            mutate(result)
            with self.assertRaises(AssertionError): runner.verify_multi(case,result,variant)

    def test_other_party_substitute_and_self_hits_do_not_count(self):
        case,result,variant=self.fixture()
        result["setup"]=[{"hitEvents":[
            {"attacker":12,"defender":6,"damage":10,"substitute":False},
            {"attacker":12,"defender":0,"damage":10,"substitute":True},
            {"attacker":0,"defender":0,"damage":10,"substitute":False}]}]
        self.assertTrue(runner.verify_multi(case,result,variant)["passed"])
        result["setup"][0]["hitEvents"].append({"attacker":12,"defender":0,"damage":10,"substitute":False})
        with self.assertRaises(AssertionError):runner.verify_multi(case,result,variant)

    def test_partner_isolation_requires_a_real_partner_hit(self):
        case,result,variant=self.fixture()
        case["expectedPartnerHits"]=True
        with self.assertRaises(AssertionError):runner.verify_multi(case,result,variant)
        result["setup"]=[{"hitEvents":[{"attacker":12,"defender":6,"damage":3,"substitute":False}]}]
        self.assertTrue(runner.verify_multi(case,result,variant)["passed"])

    def test_revival_uses_stable_identity_not_active_first_party_order(self):
        case,result,variant=self.fixture()
        case.update(expectedRevivedOriginal=True,expectedMultiPower=150)
        result["damageCalls"][0].update(powerRewrites=[150],preModifierDamage=108,calculatedDamage=108)
        result["after"]["defenderAlly"]["hp"]=133
        result["setup"]=[{"partyAfter":[{"slot":1,"hp":323},{"slot":0,"hp":0}],
                            "hitEvents":[{"attacker":12,"defender":0,"damage":1,"substitute":False}]},
                         {"partyAfter":[{"slot":1,"hp":320},{"slot":0,"hp":100,"maxHp":200}],
                            "hitEvents":[],"partySelections":[{"mode":3,"finished":True}]},
                         {"hitEvents":[{"attacker":12,"defender":0,"damage":3,"substitute":False}]}]
        self.assertTrue(runner.verify_multi(case,result,variant)["passed"])
        for mutate in (lambda r:r["setup"][0]["partyAfter"][1].update(hp=1),
                       lambda r:r["setup"][1]["partyAfter"][1].update(hp=101),
                       lambda r:r["setup"][1]["partySelections"][0].update(mode=1)):
            wrong=deepcopy(result)
            mutate(wrong)
            with self.assertRaises(AssertionError):runner.verify_multi(case,wrong,variant)


if __name__=="__main__":unittest.main()
