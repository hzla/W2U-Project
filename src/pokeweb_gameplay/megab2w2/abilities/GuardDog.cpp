// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/GuardDog.cpp); see docs/megab2w2-integration.md.
// Guard Dog (Gen 9; data/abilities.yml GUARD_DOG): Intimidate raises its Attack by 1 instead of lowering it, and it
// can't be forced out (Suction Cups' vanilla handler). Intimidate's stat drop has no mark of its source, so ability 22
// runs through EventAddIntimidateTracked (AbilityEvents.cpp): the vanilla handler with g_intimidator set while it
// runs; EVENT_STAT_CHANGE_CHECK blocks a drop from that Pokémon and pushes Attack +1. Mold Breaker ignores it.
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
constexpr u32 NO_POKE = 0xFF;
u32 g_intimidator = NO_POKE;
void HandlerIntimidateTracked(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work) {
    g_intimidator = pokeID;
    HandlerIntimidateMemberIn(item, sf, pokeID, work);
    g_intimidator = NO_POKE;
}
constexpr BattleEventHandlerTableEntry INTIMIDATE_TRACKED_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerIntimidateTracked },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerIntimidateTracked },
};
void HandlerGuardDogStatChangeCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || g_intimidator == NO_POKE || ability::Attacker() != g_intimidator) return;
    if (BattleEventVar_GetValue(VAR_STAT) != ability::STAT_ATK || BattleEventVar_GetValue(VAR_STAT_CHANGE) >= 0) return;
    if (!BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) return;
    ability::ChangeStatStage(sf, pokeID, pokeID, ability::STAT_ATK, 1, true);
    MLOG("[ABIL] Guard Dog: poke %d turns poke %d's Intimidate into Attack +1", pokeID, g_intimidator);
}

constexpr BattleEventHandlerTableEntry GUARD_DOG_HANDLERS[] = {
    { EVENT_STAT_CHANGE_CHECK, HandlerGuardDogStatChangeCheck },
    { EVENT_FORCE_OUT_CHECK, HandlerSuctionCups },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddGuardDog(u32* packed) {
    *packed = sizeof(GUARD_DOG_HANDLERS) / sizeof(GUARD_DOG_HANDLERS[0]);
    return GUARD_DOG_HANDLERS;
}

extern "C" const BattleEventHandlerTableEntry* EventAddIntimidateTracked(u32* packed) {
    *packed = sizeof(INTIMIDATE_TRACKED_HANDLERS) / sizeof(INTIMIDATE_TRACKED_HANDLERS[0]);
    return INTIMIDATE_TRACKED_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_GuardDogHandlers[2] = {GUARD_DOG_HANDLERS[0], GUARD_DOG_HANDLERS[1]};
static_assert(sizeof(GUARD_DOG_HANDLERS) / sizeof(GUARD_DOG_HANDLERS[0]) == 2, "MB_GuardDogHandlers");
