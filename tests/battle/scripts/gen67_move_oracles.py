"""Independent assertions for the non-Z Generation 6/7 native audit."""


def stage_stat(value, stage):
    return value * (2 + max(0, stage - 6)) // (2 + max(0, 6 - stage))


def verify(case, result, variant, api):
    check, completed = api["check"], api["verify_completed"]
    expected = case["audit"]
    before, after = result["before"], result["after"]
    for role, wanted in expected.get("beforeStatuses", {}).items():
        check(api["active_status"](before[role]) == ([wanted] if wanted else []), "Missing native status precondition")
    for role, wanted in expected.get("beforeItems", {}).items():
        check(before[role]["item"] == wanted["held"] and before[role]["consumedItem"] == wanted["consumed"], "Missing native item-consumption precondition")
    for role, wanted in expected.get("beforeSubstitute", {}).items():
        check(bool(before[role]["substituteHp"]) == wanted, "Missing native Substitute precondition")
    if case.get("completeTurn") and not expected.get("selectionRejected"):
        check(result.get("fullTurnValidated"), "Native turn did not return to a command menu")
    if variant.get("battleType") == "Doubles":
        check(set(before) == set(after) == {"attacker", "ally", "defender", "defenderAlly"}, "Missing doubles battler")
        setup = result["battleSetup"]
        check(setup["rule"] == 1 and min(setup["playerCount"], setup["trainerCount"]) >= 2, "Not a native doubles battle")
    if expected.get("selectionRejected"):
        check(result.get("selectionRejected"), "Move selection was not rejected")
        check(before["attacker"]["moves"] == after["attacker"]["moves"], "Rejected selection consumed PP")
    else:
        completion_result = result
        if case.get("sourceExit"):
            check(after["attacker"]["slot"] != before["attacker"]["slot"], "Trapping source never left the field")
            completion_result = {**result, "after":{**after,"attacker":result["completion"]}}
        completed(completion_result, case.get("selectedMoveId", variant["moveId"]), case.get("ppSpent", 1),
                  case.get("expectedExecutedMove", variant["moveId"]))
    calls = result["damageCalls"]
    if expected.get("extraUserMove"):
        check(calls and all(call["moveId"] == expected["extraUserMove"] for call in calls),
              "Missing required same-turn called attack")
    if expected.get("noDamage"):
        check(not calls, "Move unexpectedly reached damage calculation")
    if "powers" in expected:
        check(len(calls) == len(expected["powers"]), f"Wrong native strike count: {len(calls)} != {len(expected['powers'])}")
        for index, (call, power) in enumerate(zip(calls, expected["powers"])):
            user, target = call["attacker"], call["defender"]
            category = expected.get("category", variant["category"])
            check(call["category"] == category, f"Wrong category: {call['category']} != {category}")
            move_type = expected.get("type", variant["type"])
            check(call["moveType"] == move_type, f"Wrong resolved type: {call['moveType']} != {move_type}")
            observed_power = call["powerRewrites"][-1] if call["powerRewrites"] else call["databasePower"]
            check(observed_power == power, f"Wrong power: {observed_power} != {power}")
            physical = category == 1
            ai, di = (0, 1) if physical else (2, 3)
            critical = expected.get("critical", 0)
            check(call["critical"] == critical, f"Wrong critical result: {call['critical']} != {critical}")
            # Spectral Thief steals stages inside CalcDamage, after its entry
            # snapshot. Its independent oracle supplies the expected stages.
            a_stage = expected.get("damageUserStages", user["statStages"])[ai]
            d_stage = target["statStages"][di]
            if critical:
                a_stage, d_stage = max(6, a_stage), min(6, d_stage)
            if expected.get("ignoreDefenseStages"):
                d_stage = 6
            attack = stage_stat(user["stats"][ai], a_stage)
            defense = stage_stat(target["stats"][di], d_stage)
            effective = expected.get("effectivePowers", expected["powers"])[index]
            damage = ((2 * user["level"] // 5 + 2) * effective * attack // defense) // 50 + 2
            if expected.get("spread"):
                check(call["targetDamageRatio"] == 3072, "Missing native doubles spread reduction")
                damage = (damage * 3072 + 2047) // 4096
            if critical:
                damage *= 2  # This repo retains the native BW2 critical multiplier.
            damage = damage * 85 // 100
            if move_type in user["types"]:
                damage = (damage * 6144 + 2047) // 4096
            damage = damage * expected.get("typeRatio", 4096) // 4096
            if physical and user["conditions"][4] & 7:
                damage = (damage * 2048 + 2047) // 4096
            check(call["preModifierDamage"] == damage, f"Wrong independent damage: {call['preModifierDamage']} != {damage}")
            ratio = expected.get("finalRatio", 4096)
            check(call["damageRatio"] == ratio, f"Wrong final modifier: {call['damageRatio']} != {ratio}")
            check(call["calculatedDamage"] == max(1, (damage * ratio + 2047) // 4096), "Wrong final damage rounding")
        # Check real HP/doll application separately from CalcDamage. End-turn
        # poison/burn/Leech Seed checks are asserted below, not inferred here.
        # The action checkpoint precedes residual damage/healing. Never count
        # a successful calculation alone as proof that it damaged the target.
        # A Dancer attack occurs after Laser Focus's own action checkpoint.
        # Measure at turn end and include the ally attack that triggered it;
        # the copied attack's category/critical/damage remain independently
        # asserted above, and required ally calls are asserted below.
        application = after if expected.get("extraUserMove") else result.get("actionAfter", after)
        application_calls = calls + (result["incomingDamageCalls"] if expected.get("extraUserMove") else [])
        application_calls.sort(key=lambda call: call.get("frame", 0))
        if calls:
            for role in ("defender", "ally", "defenderAlly"):
                if role not in before:
                    continue
                hp, doll = before[role]["hp"], before[role]["substituteHp"]
                for call in application_calls:
                    if call["defender"]["slot"] != before[role]["slot"]:
                        continue
                    if doll and not case.get("bypassSubstitute"):
                        doll = max(0, doll - call["calculatedDamage"])
                    else:
                        hp = max(0, hp - call["calculatedDamage"])
                check(application[role]["hp"] == hp and application[role]["substituteHp"] == doll, f"Wrong damage application for {role}")
    for field, actual in (("stages", "statStages"), ("types", "types")):
        for role, wanted in expected.get(field, {}).items():
            check(after[role][actual] == wanted, f"Wrong {role} {field}: {after[role][actual]} != {wanted}")
    for role, wanted in expected.get("statuses", {}).items():
        actual = api["active_status"](after[role])
        check(actual == ([wanted] if wanted else []), f"Wrong {role} status: {actual} != {wanted}")
    for role, wanted in expected.get("items", {}).items():
        check(after[role]["item"] == wanted, f"Wrong {role} held item")
    for role, fields in expected.get("conditions", {}).items():
        for field, wanted in fields.items():
            check(bool(after[role][field] & 7) == wanted, f"Wrong {role} {field}: {after[role][field]} != {wanted}")
    for role, masks in expected.get("conditionFlags", {}).items():
        flags=after[role]["conditionFlags"]
        check(flags & masks.get("set",0) == masks.get("set",0), "Missing native condition flag")
        check(not flags & masks.get("clear",0), "Native semi-invulnerability was not cancelled")
    if "trapSource" in expected:
        target = after["defender"]["trapCondition"]
        check(target & 7 == 3 and (target >> 3) & 63 == before["attacker"]["slot"], "Wrong trapping source battler")
    for role, amount in expected.get("hpChange", {}).items():
        check(after[role]["hp"] - before[role]["hp"] == amount, f"Wrong HP change for {role}")
    if "healing" in expected:
        healing = expected["healing"]
        role = healing["role"]
        mon = before[role]
        if healing.get("targetAttack"):
            target = before["defender"]
            amount = stage_stat(target["stats"][0], target["statStages"][0])
        else:
            amount = mon["maxHp"] * healing["ratio"] // 4096
        # A description that omits integer rounding cannot justify declaring
        # a one-HP discrepancy a bug. Still reject any larger fraction error.
        amounts = [amount]
        if healing.get("rounding") == "unspecified":
            amounts.append((mon["maxHp"] * healing["ratio"] + 4095) // 4096)
        allowed = {min(mon["maxHp"]-mon["hp"], max(1, value)) for value in amounts}
        healed = after if healing.get("atTurnEnd") else result.get("actionAfter", after)
        check(healed[role]["hp"] - mon["hp"] in allowed,
              f"Wrong native healing for {role}: {healed[role]['hp']-mon['hp']} != {amount}")
    if "incomingHits" in expected:
        incoming = result["incomingDamageCalls"]
        check(len(incoming) == expected["incomingHits"], f"Wrong incoming hit count: {len(incoming)} != {expected['incomingHits']}")
        if "incomingType" in expected:
            check(all(call["moveType"] == expected["incomingType"] for call in incoming), "Incoming move did not get its required type")
    for wanted in expected.get("incomingTargets", []):
        calls_to_target = [c for c in result["incomingDamageCalls"] if c["moveId"] == wanted["move"] and
                           c["attacker"]["slot"] == before[wanted["source"]]["slot"] and
                           c["defender"]["slot"] == before[wanted["target"]]["slot"]]
        check(len(calls_to_target) == wanted["count"], "Wrong native instructed/redirected target or action count")
    if "accuracyThreshold" in expected and expected["accuracyThreshold"]:
        check(result["accuracyRolls"] and all(r["threshold"] == expected["accuracyThreshold"] for r in result["accuracyRolls"]), "Wrong native accuracy threshold")
    if expected.get("accuracyThreshold") == 0:
        check(not result["accuracyRolls"], "Guaranteed hit still rolled accuracy")
    for key, result_key in (("screens", "afterSideEffects"), ("beforeScreens", "beforeSideEffects"), ("actionScreens", "actionSideEffects")):
        for side, wanted in enumerate(expected.get(key, [])):
            for effect in ("0", "1"):
                check(result[result_key][side][effect]["layers"] == wanted.get(effect, 0), "Wrong Reflect/Light Screen state")
    if "switchBlocked" in expected:
        checks = result.get("switchChecks", [])
        check(checks, "Missing native switch-prohibition observation")
        check((checks[-1]["result"] != 4) == expected["switchBlocked"], "Wrong native Fairy Lock switch prohibition")
    for key, result_key in (("customSides", "afterCustomSides"), ("beforeCustomSides", "beforeCustomSides"), ("actionCustomSides", "actionCustomSides")):
        if key in expected:
            check(result[result_key] == expected[key], f"Wrong custom side state: {result[result_key]}")
    if "moneyDouble" in expected:
        check(result["moneyDouble"] == expected["moneyDouble"], "Happy Hour did not set the prize-money flag")
    if "terrain" in expected:
        check(any(r["terrain"] == expected["terrain"] for r in result["terrainReads"]), "Required terrain was not observed through the resident getter")
    if "hpLossFraction" in expected:
        cost = expected["hpLossFraction"]
        mon = before[cost["role"]]
        amount = (mon["maxHp"] + (cost["divisor"]-1 if cost.get("roundUp") else 0)) // cost["divisor"]
        check(after[cost["role"]]["hp"] == max(0, mon["hp"] - amount), "Wrong maximum-HP payment")
    if variant["moveId"] == 683:
        check(after["attacker"]["stats"][4] == before["defender"]["stats"][4] and
              after["defender"]["stats"][4] == before["attacker"]["stats"][4], "Speed Swap did not swap raw Speed")
    if "followup" in case:
        followup = case["followup"]
        verify(followup["case"], result["followup"], {**variant, **{key: followup[key] for key in ("moveId", "power", "category", "type")}}, api)
    return {"case": case["id"], "passed": True, "moveId": variant["moveId"],
            "hpBefore": before["defender"]["hp"], "hpAfter": after["defender"]["hp"]}
