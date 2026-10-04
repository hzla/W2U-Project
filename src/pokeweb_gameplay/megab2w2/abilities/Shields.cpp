// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Shields.cpp); see docs/megab2w2-integration.md.
// Shield abilities (Gen 7-9), one file, three logic names (Gen 9 / Showdown):
//   `logic: Disguise`   The first damaging hit from another Pokémon does no damage ("Its disguise served it as a
//                       decoy!"); then the holder loses 1/8 of its max HP and the disguise is busted for the rest of
//                       the battle ("X's disguise was busted!"). (Mimikyu's form change: Mimikyu is not in the game.)
//                       EVENT_DAMAGE_RATIO x0 (not in the AI's simulations), the chip + messages at the hit reaction.
//   `logic: Comatose`   "X is drowsing!" on entry; no major status, no drowsiness (blocked with "It doesn't affect
//                       X..."); Hex treats it as statused (x2). (Being "asleep" for Sleep Talk / Snore / Dream
//                       Eater would need the engine's sleep checks: not modelled.)
//   `logic: TeraShell`  At full HP, every hit from another Pokémon does not-very-effective damage: the hit's
//                       effectiveness (VAR_TYPE_EFFECTIVENESS at EVENT_DAMAGE_RATIO) is scaled to x0.5 overall
//                       ("X made its shell gleam! It's distorting type matchups!" once per move). The engine's own
//                       effectiveness text is unchanged.
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

namespace {
constexpr u16 SHIELD_HEX = 506;
struct HandlerParam_DamageS { HandlerParam_Header header; u16 amount; u8 pokeID; u8 flags; u32 _8; HandlerParam_StrParams exStr; };
bool g_disguiseBusted[ability::MAX_POKE_ID], g_disguiseHit[ability::MAX_POKE_ID], g_teraShellShown[ability::MAX_POKE_ID];

// ---- Disguise ----------------------------------------------------------------------------------------------
void HandlerDisguiseDamage(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Attacker() == pokeID || pokeID >= ability::MAX_POKE_ID) return;
    if (g_disguiseBusted[pokeID]) return;
    ability::MulRatio(0);
    if (ability::Simulating(sf)) return;
    g_disguiseHit[pokeID] = true;
    g_disguiseBusted[pokeID] = true;
    MLOG("[ABIL] Disguise: poke %d takes the hit", pokeID);
}
void HandlerDisguiseReaction(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || pokeID >= ability::MAX_POKE_ID || !g_disguiseHit[pokeID]) return;
    g_disguiseHit[pokeID] = false;
    BattleMon* bm = GetBattleMon(sf, pokeID);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, BTL_STRTYPE_STD, BTLMSG_STD_DISGUISE_DECOY);
    BattleHandler_PopWork(sf, m);
    auto* d = (HandlerParam_DamageS*)BattleHandler_PushWork(sf, 7, pokeID);   // EFFECT_DAMAGE (Aftermath's)
    u32 chip = DivideMaxHPZeroCheck(bm, 8);   // the decoyed hit still did the engine's minimum 1 damage
    d->amount = (u16)(chip > 1 ? chip - 1 : 1);
    d->pokeID = (u8)pokeID;
    d->flags = (d->flags & ~1) | 1;
    BattleHandler_PopWork(sf, d);
    auto* m2 = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m2->str, ability::STRTYPE_SET, BTLMSG_SET_DISGUISE_BUSTED);
    BattleHandler_AddArg(&m2->str, pokeID);
    BattleHandler_PopWork(sf, m2);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}
constexpr BattleEventHandlerTableEntry DISGUISE_HANDLERS[] = {
    { EVENT_DAMAGE_RATIO, HandlerDisguiseDamage },
    { EVENT_AFTER_DAMAGE_REACTION, HandlerDisguiseReaction },
};

// ---- Comatose ----------------------------------------------------------------------------------------------
void HandlerComatoseStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() == pokeID) ability::PopupSetMessage(sf, pokeID, BTLMSG_SET_COMATOSE);
}
void HandlerComatoseCondition(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    u32 cond = (u32)BattleEventVar_GetValue(VAR_CONDITION);
    if (ability::Defender() != pokeID || !((cond >= 1 && cond <= 5) || cond == 14)) return;
    if (BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) {
        work[0] = 1;
        ability::PopupSetMessage(sf, pokeID, ability::MSG_SET_DOESNT_AFFECT);
        MLOG("[ABIL] Comatose: poke %d blocks condition %d", pokeID, cond);
    }
}
void HandlerComatoseYawn(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    if (ability::Subject() != pokeID || !BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) return;
    work[0] = 1;
    ability::PopupSetMessage(sf, pokeID, ability::MSG_SET_DOESNT_AFFECT);
}
void HandlerComatoseFailed(BattleEventItem*, ServerFlow*, u32, u32* work) { work[0] = 0; }
void HandlerComatoseHex(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Move() != SHIELD_HEX) return;
    if (GetBattleMonStatus(GetBattleMon(sf, pokeID))) return;   // a real status already doubles it
    BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
}
constexpr BattleEventHandlerTableEntry COMATOSE_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerComatoseStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerComatoseStart },
    { EVENT_ADD_CONDITION_CHECK, HandlerComatoseCondition },
    { EVENT_YAWN_CHECK, HandlerComatoseYawn },
    { EVENT_ADD_CONDITION_FAILED, HandlerComatoseFailed },
    { EVENT_MOVE_POWER, HandlerComatoseHex },
};

// ---- Tera Shell --------------------------------------------------------------------------------------------
void HandlerTeraShellMoveStart(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (pokeID < ability::MAX_POKE_ID) g_teraShellShown[pokeID] = false;
}
void HandlerTeraShellDamage(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Attacker() == pokeID || pokeID >= ability::MAX_POKE_ID) return;
    if (!IsMonFullHP(GetBattleMon(sf, pokeID))) return;
    u32 eff = (u32)BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS);
    int ratio = eff == EFF_NEUTRAL ? 2048 : eff == EFF_DOUBLE ? 1024 : eff == EFF_QUAD ? 512 : 4096;
    if (ratio == 4096) return;
    ability::MulRatio(ratio);
    if (ability::Simulating(sf) || g_teraShellShown[pokeID]) return;
    g_teraShellShown[pokeID] = true;
    ability::PopupSetMessage(sf, pokeID, BTLMSG_SET_TERA_SHELL);
    MLOG("[ABIL] Tera Shell: poke %d effectiveness %d -> not very effective", pokeID, eff);
}
constexpr BattleEventHandlerTableEntry TERA_SHELL_HANDLERS[] = {
    { EVENT_MOVE_START, HandlerTeraShellMoveStart },
    { EVENT_DAMAGE_RATIO, HandlerTeraShellDamage },
};
} // namespace

void Shields_ResetForBattle() {
    for (u32 i = 0; i < ability::MAX_POKE_ID; ++i) g_disguiseBusted[i] = g_disguiseHit[i] = g_teraShellShown[i] = false;
}

extern "C" const BattleEventHandlerTableEntry* EventAddDisguise(u32* packed) {
    *packed = sizeof(DISGUISE_HANDLERS) / sizeof(DISGUISE_HANDLERS[0]);
    return DISGUISE_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddComatose(u32* packed) {
    *packed = sizeof(COMATOSE_HANDLERS) / sizeof(COMATOSE_HANDLERS[0]);
    return COMATOSE_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddTeraShell(u32* packed) {
    *packed = sizeof(TERA_SHELL_HANDLERS) / sizeof(TERA_SHELL_HANDLERS[0]);
    return TERA_SHELL_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_TeraShellHandlers[2] = {TERA_SHELL_HANDLERS[0], TERA_SHELL_HANDLERS[1]};
static_assert(sizeof(TERA_SHELL_HANDLERS) / sizeof(TERA_SHELL_HANDLERS[0]) == 2, "MB_TeraShellHandlers");
