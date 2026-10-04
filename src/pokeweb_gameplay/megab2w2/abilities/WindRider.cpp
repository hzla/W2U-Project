// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/WindRider.cpp); see docs/megab2w2-integration.md.
// Wind Rider (Gen 9; data/abilities.yml WIND_RIDER): wind moves (move flag `wind`) from another Pokémon don't affect
// the holder and raise its Attack by 1 (Sap Sipper's pattern: CommonTypeNoEffectRankUp shows the popup and the
// boost, or "doesn't affect" at +6); Tailwind starting on its side, or already blowing when it enters, raises its
// Attack too (Gen 9 / Showdown). Mold Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u16 WIND_RIDER_TAILWIND = 366;
constexpr u32 WIND_RIDER_SIDE_TAILWIND = 4;   // SideEffect_IsActive id (Tailwind's handler adds side effect 4)

void HandlerWindRiderNoEffect(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Attacker() == pokeID) return;
    u16 move = ability::Move();
    if (!moves::HasFlag(move, MOVE_FLAG_WIND)) return;
    if (!BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) return;
    CommonTypeNoEffectRankUp(sf, pokeID, ability::STAT_ATK, 1);
    MLOG("[ABIL] Wind Rider: poke %d absorbs wind move %d", pokeID, move);
}
// Tailwind: whether it was blowing is noted at the move's start (work[0]); at its end a new Tailwind boosts
// (EVENT_AFTER_MOVE_USE comes before the move's own messages)
void HandlerWindRiderTailwindStart(BattleEventItem*, ServerFlow*, u32 pokeID, u32* work) {
    work[0] = SideEffect_IsActive(GetSideFromMonID(pokeID), WIND_RIDER_SIDE_TAILWIND);
}
void HandlerWindRiderTailwind(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    if (ability::Move() != WIND_RIDER_TAILWIND || !ability::SameSide(pokeID, ability::Attacker())) return;
    if (work[0] || !SideEffect_IsActive(GetSideFromMonID(pokeID), WIND_RIDER_SIDE_TAILWIND)) return;
    ability::ChangeStatStage(sf, pokeID, pokeID, ability::STAT_ATK, 1, true);
    MLOG("[ABIL] Wind Rider: poke %d Tailwind boost", pokeID);
}
void HandlerWindRiderStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || !SideEffect_IsActive(GetSideFromMonID(pokeID), WIND_RIDER_SIDE_TAILWIND)) return;
    ability::ChangeStatStage(sf, pokeID, pokeID, ability::STAT_ATK, 1, true);
    MLOG("[ABIL] Wind Rider: poke %d enters into Tailwind", pokeID);
}

constexpr BattleEventHandlerTableEntry WIND_RIDER_HANDLERS[] = {
    { EVENT_CHECK_NO_EFFECT, HandlerWindRiderNoEffect },
    { EVENT_MOVE_START, HandlerWindRiderTailwindStart },
    { EVENT_MOVE_END, HandlerWindRiderTailwind },
    { EVENT_SWITCH_IN, HandlerWindRiderStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerWindRiderStart },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddWindRider(u32* packed) {
    *packed = sizeof(WIND_RIDER_HANDLERS) / sizeof(WIND_RIDER_HANDLERS[0]);
    return WIND_RIDER_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_WindRiderHandlers[5] = {WIND_RIDER_HANDLERS[0], WIND_RIDER_HANDLERS[1], WIND_RIDER_HANDLERS[2], WIND_RIDER_HANDLERS[3], WIND_RIDER_HANDLERS[4]};
static_assert(sizeof(WIND_RIDER_HANDLERS) / sizeof(WIND_RIDER_HANDLERS[0]) == 5, "MB_WindRiderHandlers");
