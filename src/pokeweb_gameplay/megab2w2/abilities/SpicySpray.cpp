// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/SpicySpray.cpp); see docs/megab2w2-integration.md.
// Spicy Spray (Legends: Z-A; data/abilities.yml SPICY_SPRAY): when the holder is hit by a damaging move, the
// attacker is burned - every time, contact or not. Flame Body's effect without its contact / 30% checks (ov167
// 0x21BF670: EFFECT_ADD_CONDITION {burn, the default burn continuation sub_21BD56C(4), the attacker}, popup); the
// engine applies the usual immunities (Fire types, Water Veil, an existing status).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u32 SPICY_BURN = 4;

void HandlerSpicySprayHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) || sub_21ABF54(sf)) return;
    u32 attacker = ability::Attacker();
    if (attacker == pokeID || attacker >= ability::MAX_POKE_ID) return;
    if (BattleMon_IsFainted(GetBattleMon(sf, attacker)) || GetBattleMonStatus(GetBattleMon(sf, attacker))) return;
    auto* p = (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->condition = SPICY_BURN;
    p->cont = sub_21BD56C(SPICY_BURN);
    p->_c[0] = 0;
    p->pokeID = (u8)attacker;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Spicy Spray: poke %d burns poke %d", pokeID, attacker);
}

constexpr BattleEventHandlerTableEntry SPICY_SPRAY_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerSpicySprayHit },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddSpicySpray(u32* packed) {
    *packed = sizeof(SPICY_SPRAY_HANDLERS) / sizeof(SPICY_SPRAY_HANDLERS[0]);
    return SPICY_SPRAY_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_SpicySprayHandlers[1] = {SPICY_SPRAY_HANDLERS[0]};
static_assert(sizeof(SPICY_SPRAY_HANDLERS) / sizeof(SPICY_SPRAY_HANDLERS[0]) == 1, "MB_SpicySprayHandlers");
