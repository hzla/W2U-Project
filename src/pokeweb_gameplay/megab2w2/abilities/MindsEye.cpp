// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/MindsEye.cpp); see docs/megab2w2-integration.md.
// Mind's Eye (Gen 9; data/abilities.yml MINDS_EYE): Scrappy + Keen Eye, Gen 9 style: its Normal / Fighting moves hit
// Ghost types (Scrappy's vanilla handler), its accuracy can't be lowered (Keen Eye's vanilla check + message), and it
// ignores the target's evasion stages (Gen 6+ Keen Eye; Unaware's attacker half: VAR_EVASION_STAGE = 6). Mold
// Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
void HandlerMindsEyeAccuracyStage(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    if (BattleEventVar_GetValue(VAR_EVASION_STAGE) > 6 && !ability::Simulating(sf))
        MLOG("[ABIL] Mind's Eye: poke %d ignores evasion %d", pokeID, BattleEventVar_GetValue(VAR_EVASION_STAGE) - 6);
    BattleEventVar_RewriteValue(VAR_EVASION_STAGE, 6);
}

constexpr BattleEventHandlerTableEntry MINDS_EYE_HANDLERS[] = {
    { EVENT_ACCURACY_STAGE, HandlerMindsEyeAccuracyStage },
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerScrappy },
    { EVENT_STAT_CHANGE_CHECK, HandlerKeenEyeCheck },
    { EVENT_STAT_CHANGE_GUARD, HandlerKeenEyeGuard },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddMindsEye(u32* packed) {
    *packed = sizeof(MINDS_EYE_HANDLERS) / sizeof(MINDS_EYE_HANDLERS[0]);
    return MINDS_EYE_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_MindsEyeHandlers[4] = {MINDS_EYE_HANDLERS[0], MINDS_EYE_HANDLERS[1], MINDS_EYE_HANDLERS[2], MINDS_EYE_HANDLERS[3]};
static_assert(sizeof(MINDS_EYE_HANDLERS) / sizeof(MINDS_EYE_HANDLERS[0]) == 4, "MB_MindsEyeHandlers");
