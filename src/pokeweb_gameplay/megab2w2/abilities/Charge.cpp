// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Charge.cpp); see docs/megab2w2-integration.md.
// Charge family (`logic: Charge`; data/abilities.yml ELECTROMORPHOSIS, WIND_POWER): the holder becomes charged - its
// next Electric move has double power (Gen 9 Charge: it lasts until the holder uses an Electric move or leaves).
//   Electromorphosis: hit by any damaging move.  Wind Power: hit by a damaging wind move (move flag `wind`), or
//   Tailwind starting on its side.
// The charge is this file's own state (the engine's Charge condition is the Gen 5 one-turn version), shown with
// the Charge move's "X began charging power!" under the holder's popup. Power: EVENT_MOVE_POWER x2 for the holder's
// Electric moves; it ends at EVENT_MOVE_END of an Electric move, when the holder enters (it left meanwhile) and at
// battle start (Charge_ResetForBattle).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u16 CHARGE_MSG_BEGAN = 664;          // bank 18: "{0} began charging power!" (the Charge move's)
constexpr u32 CHARGE_TYPE_ELECTRIC = 12;
constexpr u16 CHARGE_TAILWIND = 366;
constexpr u32 CHARGE_SIDE_TAILWIND = 4;
bool g_charged[ability::MAX_POKE_ID];

void ChargeUp(ServerFlow* sf, u32 pokeID, const char* why) {
    g_charged[pokeID] = true;
    ability::PopupSetMessage(sf, pokeID, CHARGE_MSG_BEGAN);
    MLOG("[ABIL] Charge: poke %d charged (%s)", pokeID, why);
}
void HandlerChargeHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || pokeID >= ability::MAX_POKE_ID || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT))
        return;
    if (BattleMon_IsFainted(GetBattleMon(sf, pokeID))) return;
    u16 move = ability::Move();
    if (ability::HolderAbility(sf, pokeID) == ABIL_WIND_POWER && !moves::HasFlag(move, MOVE_FLAG_WIND)) return;
    ChargeUp(sf, pokeID, "hit");
}
// Tailwind starting on its side (noted at the move's start in work[0]; checked at its end, after Tailwind's messages)
void HandlerChargeTailwindStart(BattleEventItem*, ServerFlow*, u32 pokeID, u32* work) {
    work[0] = SideEffect_IsActive(GetSideFromMonID(pokeID), CHARGE_SIDE_TAILWIND);
}
void HandlerChargeTailwind(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    if (pokeID >= ability::MAX_POKE_ID || ability::Move() != CHARGE_TAILWIND || work[0]) return;
    if (ability::HolderAbility(sf, pokeID) != ABIL_WIND_POWER || !ability::SameSide(pokeID, ability::Attacker())) return;
    if (!SideEffect_IsActive(GetSideFromMonID(pokeID), CHARGE_SIDE_TAILWIND)) return;
    ChargeUp(sf, pokeID, "Tailwind");
}
void HandlerChargePower(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID || !g_charged[pokeID]) return;
    if (ability::MoveType() != CHARGE_TYPE_ELECTRIC) return;
    BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Charge: poke %d move %d power x2", pokeID, ability::Move());
}
void HandlerChargeMoveEnd(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work) {
    HandlerChargeTailwind(item, sf, pokeID, work);
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID || !g_charged[pokeID]) return;
    if (ability::FinalMoveType(sf, ability::Move(), pokeID) != CHARGE_TYPE_ELECTRIC) return;
    g_charged[pokeID] = false;
    MLOG("[ABIL] Charge: poke %d used its charge", pokeID);
}
void HandlerChargeSwitchIn(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Subject() == pokeID && pokeID < ability::MAX_POKE_ID) g_charged[pokeID] = false;
}

constexpr BattleEventHandlerTableEntry CHARGE_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerChargeHit },
    { EVENT_MOVE_START, HandlerChargeTailwindStart },
    { EVENT_MOVE_POWER, HandlerChargePower },
    { EVENT_MOVE_END, HandlerChargeMoveEnd },
    { EVENT_SWITCH_IN, HandlerChargeSwitchIn },
};
} // namespace

void Charge_ResetForBattle() {
    for (bool& c : g_charged) c = false;
}

extern "C" const BattleEventHandlerTableEntry* EventAddCharge(u32* packed) {
    *packed = sizeof(CHARGE_HANDLERS) / sizeof(CHARGE_HANDLERS[0]);
    return CHARGE_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_ChargeHandlers[5] = {CHARGE_HANDLERS[0], CHARGE_HANDLERS[1], CHARGE_HANDLERS[2], CHARGE_HANDLERS[3], CHARGE_HANDLERS[4]};
static_assert(sizeof(CHARGE_HANDLERS) / sizeof(CHARGE_HANDLERS[0]) == 5, "MB_ChargeHandlers");
