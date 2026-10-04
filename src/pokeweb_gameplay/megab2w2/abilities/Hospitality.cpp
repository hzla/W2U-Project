// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Hospitality.cpp); see docs/megab2w2-integration.md.
// Hospitality (Gen 9; data/abilities.yml HOSPITALITY): on entering (or gaining the ability) it restores 1/4 of its
// allies' max HP (Gen 9 / Showdown: adjacent allies; full-HP allies are skipped, no popup when nobody heals). The
// allies come from Plus / Minus' lookup (Battle_ExpandPos, the holder's whole side - in triples that includes the
// far ally); the heal is CommonTypeRecoverHP's effect with the holder's popup and "X's HP was restored." (Gen 9's
// matcha line does not exist here).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
void HandlerHospitalityStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    u32 pos = Battle_GetMonPos(sf, pokeID);
    if (pos == ability::POS_NONE) return;
    u8 ids[8];
    u32 count = Battle_ExpandPos(sf, (u16)(ability::POS_RANGE_FULL_FRIENDS << 8 | pos), ids);
    bool popup = false;
    for (u32 i = 0; i < count; ++i) {
        u32 ally = ids[i];
        if (ally == pokeID) continue;
        BattleMon* bm = GetBattleMon(sf, ally);
        if (BattleMon_IsFainted(bm) || IsMonFullHP(bm)) continue;
        if (!popup) { BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID); popup = true; }
        auto* p = (HandlerParam_RecoverHP*)BattleHandler_PushWork(sf, EFFECT_RECOVER_HP, pokeID);
        p->amount = (u16)DivideMaxHPZeroCheck(bm, 4);
        p->pokeID = (u8)ally;
        BattleHandler_StrSetup(&p->exStr, ability::STRTYPE_SET, ability::MSG_SET_HP_RESTORED);
        BattleHandler_AddArg(&p->exStr, ally);
        BattleHandler_PopWork(sf, p);
        MLOG("[ABIL] Hospitality: poke %d heals poke %d by %d", pokeID, ally, p->amount);
    }
    if (popup) BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}

constexpr BattleEventHandlerTableEntry HOSPITALITY_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerHospitalityStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerHospitalityStart },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddHospitality(u32* packed) {
    *packed = sizeof(HOSPITALITY_HANDLERS) / sizeof(HOSPITALITY_HANDLERS[0]);
    return HOSPITALITY_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_HospitalityHandlers[2] = {HOSPITALITY_HANDLERS[0], HOSPITALITY_HANDLERS[1]};
static_assert(sizeof(HOSPITALITY_HANDLERS) / sizeof(HOSPITALITY_HANDLERS[0]) == 2, "MB_HospitalityHandlers");
