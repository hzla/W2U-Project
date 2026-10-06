"""Independent Gen 6/7 ability/item outcomes; never consult handler source."""
import importlib.util
from pathlib import Path

_spec = importlib.util.spec_from_file_location("mechanic_stage_oracle", Path(__file__).with_name("gen67_move_oracles.py"))
_stages = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_stages)
stage_stat = _stages.stage_stat

# Native move metadata is validated by the fixture builder before emulation.
# Keep power/category/type expectations here independent of native observations.
MOVES = {33:(50,1,0),129:(60,2,0),52:(40,2,9),53:(90,2,9),7:(75,1,9),
         44:(60,1,16),55:(40,2,10),58:(90,2,14),245:(80,1,0),247:(80,2,7),
         352:(60,2,10),585:(95,2,17),253:(90,2,0),497:(40,2,0),17:(60,1,2),232:(50,1,8),87:(110,2,12),153:(250,1,0),369:(70,1,6),24:(30,1,1),69:(1,1,1)}
RESIDENT_ABILITIES = {203,212,213,230,231}  # Hooks or deliberately native aliases.


def fixed(value, ratio):
    return (value * ratio + 2047) // 4096


def verify(case, result, variant, api):
    check = api["check"]
    expected = case["mechanicAudit"]
    before, after = result["before"], result["after"]
    if case.get("selectionRejected"):
        check(result.get("selectionRejected"), "Status move was not rejected at selection")
        check(before["attacker"]["moves"] == after["attacker"]["moves"], "Rejected command spent PP")
    else:
        check(result.get("fullTurnValidated"), "Battle did not complete a native turn")
        completion_record=result
        if expected.get("expectedPivot"):
            check(result.get("departingAttacker") is not None,"Missing native pre-switch action checkpoint")
            completion_record={**result,"after":{**after,"attacker":result["departingAttacker"]["attacker"]}}
        api["verify_completed"](completion_record, case.get("selectedMoveId", variant["moveId"]), case.get("ppSpent", 1),
                                case.get("expectedExecutedMove", variant["moveId"]))
        for role in ("defender","defenderAlly"):
            if role not in before:continue
            actor = result.get("departingDefender",after[role]) if role=="defender" else after[role]
            foe_before, foe_after = before[role]["moves"][0], actor["moves"][0]
            uses = expected.get("foeActions",{}).get(role,1)
            check(foe_after["id"] == foe_before["id"] and foe_after["pp"] == foe_before["pp"] - uses,
                  f"Opponent did not attempt its fixture move exactly {uses} time(s): {role}")
        if "ally" in before:
            index=case.get("allyMoveSlot",0)
            check(after["ally"]["moves"][index]["pp"] == before["ally"]["moves"][index]["pp"] - 1,
                  "Ally did not spend exactly one PP on its selected move")
    if variant.get("mechanic"):
        telemetry = result.get("moduleTelemetry")
        check(telemetry is not None and telemetry["failureCount"] == telemetry["failedModuleMask"] == 0,
              "Child DLL registration failed")
        check(0 <= telemetry["loadedModuleCount"] <= 24 and telemetry["currentChildBytes"] <= telemetry["peakChildBytes"],
              "Invalid module telemetry")
        mechanic=variant["mechanic"]
        if mechanic["kind"]=="ability":
            present=mechanic["id"] in [variant.get(key) for key in
                ("playerAbilityId","abilityId","allyAbilityId","defenderAllyAbilityId")]
            requires_child=present and mechanic["id"] not in RESIDENT_ABILITIES
        else:
            requires_child=mechanic["id"] in [variant.get("player",{}).get("itemId"),variant.get("defenderItemId")]
        if requires_child:
            check(telemetry["loadedModuleCount"]>0 and telemetry["currentChildBytes"]>0,"Required mechanic child never loaded")
    for role, stages in expected.get("beforeStages", {}).items():
        check(before[role]["statStages"] == stages, "Missing switch-in stat precondition")
    for role, item in expected.get("beforeItems", {}).items():
        check(before[role]["item"] == item, "Missing native item precondition")
    for role, form in expected.get("beforeForms", {}).items():
        check(before[role]["form"] == form, "Missing native form precondition")
    all_calls = []
    for direction, field in (("outgoing", "damageCalls"), ("incoming", "incomingDamageCalls")):
        calls, wanted = result.get(field, []), expected.get(direction, [])
        check(len(calls) == len(wanted), f"Wrong {direction} strike count: {len(calls)} != {len(wanted)}")
        for call, rule in zip(calls, wanted):
            power, category, move_type = MOVES[rule["move"]]
            move_type = rule.get("type", move_type)
            check(call["moveId"] == rule["move"] and call["category"] == category and call["moveType"] == move_type,
                  "Wrong native move/category/type")
            user, target = call["attacker"], call["defender"]
            for actor,key in ((user,"userRole"),(target,"targetRole")):
                if key in rule:check(actor["slot"]==before[rule[key]]["slot"],"Wrong native damage actor/target")
            if rule.get("fixedByLevel"):
                check(rule["move"]==69 and call["calculatedDamage"]==user["level"],"Fixed-damage strike was reduced or modified")
                all_calls.append(call)
                continue
            check(call["databasePower"] == power and all(value == power for value in call["powerRewrites"]), "Unexpected move base-power rewrite")
            critical = rule.get("critical", 0)
            check(call["critical"] == critical, "Wrong critical-hit outcome")
            a, d = (0, 1) if category == 1 else (2, 3)
            a_stage, d_stage = user["statStages"][a], target["statStages"][d]
            if critical:
                a_stage, d_stage = max(6, a_stage), min(6, d_stage)
            attack = fixed(stage_stat(user["stats"][a], a_stage), rule.get("attackRatio", 4096))
            defense = fixed(stage_stat(target["stats"][d], d_stage), rule.get("defenseRatio", 4096))
            power = fixed(power, rule.get("powerRatio", 4096))
            damage = ((2 * user["level"] // 5 + 2) * power * attack // defense) // 50 + 2
            if rule.get("spread"):
                check(call["targetDamageRatio"] == 3072, "Missing native spread modifier")
                damage = fixed(damage,3072)
            if critical:
                damage *= 2  # This project retains BW2 critical damage.
            damage = damage * 85 // 100
            types = expected.get("damageTypes", user["types"]) if direction == "outgoing" else user["types"]
            if move_type in types:
                damage = fixed(damage, 6144)
            damage = damage * rule.get("typeRatio", 4096) // 4096
            if category == 1 and user["conditions"][4] & 7:
                damage = fixed(damage, 2048)
            damage = max(1, damage)
            check(call["preModifierDamage"] == damage,
                  f"Wrong independent {direction} damage: {call['preModifierDamage']} != {damage}")
            ratio = rule.get("finalRatio", 4096)
            check(call["damageRatio"] == ratio, f"Wrong final modifier: {call['damageRatio']} != {ratio}")
            final = 0 if rule.get("absorbed") else max(1, fixed(damage, ratio))
            check(call["calculatedDamage"] == final, "Wrong final damage or rounding")
            all_calls.append(call)
    # Real HP and Substitute application are distinct from successful calculation.
    # Use each strike's entry HP, so healing/reactions between strikes are not hidden.
    # Healing/retaliation is accounted for only when explicitly authored.
    for role, mon in before.items():
        target_slot=after[role]["slot"] if role=="defender" and expected.get("replacementThisTurn") else mon["slot"]
        calls = [c for c in all_calls if c["defender"]["slot"] == target_slot]
        if calls or role in expected.get("directLoss",{}):
            if role=="defender" and expected.get("replacementThisTurn"):
                check(calls[0]["defender"]["species"]==variant["incomingSpecies"],"Stakeout did not hit the native replacement")
                mon=calls[0]["defender"]
            hp, doll = mon["hp"], mon["substituteHp"]
            if role=="attacker" and expected.get("healHalfBeforeHit"):
                # Recover rounds its half-HP healing up in Generations V-VII.
                hp=min(mon["maxHp"],hp+(mon["maxHp"]+1)//2)
                check(calls and calls[0]["defender"]["hp"]==hp,"Healing did not precede the priority attack")
            for call in sorted(calls, key=lambda c:c["frame"]):
                check(call["defender"]["hp"]==hp and call["defender"]["substituteHp"]==doll,
                      "Strike did not observe preceding real damage/healing")
                if doll:
                    doll = max(0, doll - call["calculatedDamage"])
                else:
                    hp = max(0, hp - call["calculatedDamage"])
            if role == "attacker" and expected.get("berryPouchHealing"):
                check(mon["item"] == 158 and hp <= mon["maxHp"] // 2, "Missing native Sitrus activation precondition")
                hp = min(mon["maxHp"], hp + mon["maxHp"] // 4 + mon["maxHp"] // 3)
            hp=max(0,hp-expected.get("directLoss",{}).get(role,0))
            if role in expected.get("terrainHealing",[]):hp=min(mon["maxHp"],hp+max(1,mon["maxHp"]//16))
            # Poison/burn fixture residuals do not alter the attack checkpoint.
            player_strikes=all(c["attacker"]["slot"]==before["attacker"]["slot"] for c in calls)
            applied = result.get("actionAfter", after) if role == "defender" and player_strikes else after
            if role=="attacker" and expected.get("expectedPivot"):applied=result.get("departingAttacker")
            check(applied is not None,"No pre-departure HP checkpoint")
            check(applied[role]["hp"] == hp and applied[role]["substituteHp"] == doll,
                  f"Wrong real damage application for {role}: {applied[role]['hp']} != {hp}")
    for role, stages in expected.get("stages", {}).items():
        check(after[role]["statStages"] == stages, f"Wrong {role} stat stages: {after[role]['statStages']} != {stages}")
    for role, types in expected.get("types", {}).items():
        check(after[role]["types"] == types, f"Wrong {role} typing")
    for role, status in expected.get("statuses", {}).items():
        check(api["active_status"](after[role]) == ([status] if status else []), f"Wrong {role} status")
    for field,native in (("forms","form"),("abilities","currentAbility"),("hpExact","hp")):
        for role,value in expected.get(field,{}).items():
            check(after[role][native]==value,f"Wrong {role} {native}: {after[role][native]} != {value}")
    if "hpPoolGrowth" in expected:
        role=expected["hpPoolGrowth"];old,new=before[role],after[role]
        check(new["maxHp"]>old["maxHp"] and new["hp"]-old["hp"]==new["maxHp"]-old["maxHp"],"Form change did not preserve damage while increasing HP pool")
    if "expectedPivot" in expected:
        check(bool(result.get("partySelections"))==expected["expectedPivot"],"Wrong forced replacement flow")
        if expected["expectedPivot"]:
            incoming=result.get("incomingAttacker")
            check(incoming is not None and incoming["species"]==variant["incomingAttackerSpecies"] and incoming["slot"]==case["pivotChoice"],"No correct native replacement")
    if "replacementThisTurn" in expected:
        events=result.get("switchInEvents",[])
        check(len(events)==int(expected["replacementThisTurn"]),"Wrong native replacement timing")
        check(after["defender"]["species"]==variant["incomingSpecies"],"Missing replacement battler")
        if not expected["replacementThisTurn"]:
            check(before["defender"]["species"]==variant["incomingSpecies"],"Replacement was not already present before the turn")
    for role,moves in expected.get("actions",{}).items():
        actions=[e for e in result.get("mechanicActions",[]) if e["slot"]==before[role]["slot"]]
        for move,count in moves.items():
            check(sum(e["move"]==int(move) for e in actions)==count,f"Wrong native action count for {role} move {move}: {actions}")
    if expected.get("symbiosisSubstitute"):
        user=before["attacker"];cost=max(1,user["maxHp"]//4)
        hp=user["hp"]-cost+user["maxHp"]//4
        if expected["items"]["attacker"]==234:hp=min(user["maxHp"],hp+max(1,user["maxHp"]//16))
        check(after["attacker"]["hp"]==hp and after["attacker"]["substituteHp"]==cost,"Native berry/transfer healing or Substitute payment wrong")
    for role, fields in expected.get("conditions", {}).items():
        for field, active in fields.items():
            check(bool(after[role][field] & 7) == active, f"Wrong {role} {field}")
    for field, native in (("items", "item"), ("consumed", "consumedItem")):
        for role, item in expected.get(field, {}).items():
            check(after[role][native] == item, f"Wrong {role} {field}: {after[role][native]} != {item}")
    if "terrain" in expected:
        observed = result.get("terrainState")
        check(observed is not None and observed["active"] == 1 and observed["type"] == expected["terrain"],
              f"Missing required active terrain: {observed} != {expected['terrain']}")
    if "terrainTimeline" in expected:
        turns = [result, *result.get("laterTurns", [])]
        check(len(turns) == len(expected["terrainTimeline"]), "Missing duration-check turns")
        for turn, remaining in zip(turns, expected["terrainTimeline"]):
            observed = turn.get("terrainState")
            check(turn.get("fullTurnValidated") and observed is not None, "Missing native terrain checkpoint")
            check(observed == {"type":1 if remaining else 0,"turns":remaining,"active":int(remaining > 0)},
                  f"Wrong terrain countdown: {observed} != {remaining}")
    if "order" in expected:
        outgoing, incoming = result["damageCalls"], result["incomingDamageCalls"]
        check(outgoing and incoming, "No attacks to prove action order")
        check((outgoing[0]["frame"] < incoming[0]["frame"]) == (expected["order"] == "user-first"), "Wrong native action order")
    if expected.get("weatherImmune"):
        check(after["attacker"]["hp"] == before["attacker"]["hp"], "Weather damaged protected holder")
    if "followup" in case:
        followup=case["followup"]
        verify(followup["case"],result["followup"],{**variant,"moveId":followup["moveId"]},api)
    return {"case":case["id"],"passed":True,"mechanic":variant.get("mechanic"),
            "variant":variant.get("name"),
            "hpBefore":before["defender"]["hp"],"hpAfter":after["defender"]["hp"],
            "outgoingStrikes":len(expected.get("outgoing",[])),"incomingStrikes":len(expected.get("incoming",[]))}
