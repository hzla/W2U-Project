// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/PurifyingSalt.cpp); see docs/megab2w2-integration.md.
// Purifying Salt (Gen 9; data/abilities.yml PURIFYING_SALT): the holder can't get a non-volatile status (paralysis,
// sleep - Rest and Yawn's drowsiness included - freeze, burn, poison) and Ghost moves against it use half the attacker's attacking
// stat. Status: Water Veil's pattern for every status with the vanilla helpers (HandlerCommonGuardStatus / the cures),
// Yawn as Insomnia (HandlerInsomniaYawnCheck). Mold Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
constexpr u32 COND_YAWN = 14;   // "next-turn sleep" (Yawn's drowsiness): its own status, checked like the others
constexpr u32 SALT_CONDITIONS[] = { COND_PARALYSIS, COND_SLEEP, COND_FREEZE, COND_BURN, COND_POISON, COND_YAWN };
void HandlerPurifyingSaltAttackingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Attacker() == pokeID || ability::MoveType() != TYPE_GHOST) return;
    ability::MulRatio(2048);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Purifying Salt: poke %d takes Ghost move %d x0.5", pokeID, ability::Move());
}
void HandlerPurifyingSaltGuard(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    for (u32 c : SALT_CONDITIONS)
        if ((work[0] = HandlerCommonGuardStatus(sf, pokeID, c)) != 0) {
            MLOG("[ABIL] Purifying Salt: poke %d blocks status %d", pokeID, c);
            return;
        }
}
void HandlerPurifyingSaltCure(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    for (u32 c : SALT_CONDITIONS) CommonAbilityCureStatus(sf, pokeID, c);
}
void HandlerPurifyingSaltActionEnd(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    for (u32 c : SALT_CONDITIONS) CommonAbilityCureStatusCore(sf, pokeID, c);
}

constexpr BattleEventHandlerTableEntry PURIFYING_SALT_HANDLERS[] = {
    { EVENT_ATTACKING_STAT, HandlerPurifyingSaltAttackingStat },
    { EVENT_ADD_CONDITION_CHECK, HandlerPurifyingSaltGuard },
    { EVENT_ADD_CONDITION_FAILED, HandlerAddStatusFailedCommon },
    { EVENT_YAWN_CHECK, HandlerInsomniaYawnCheck },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerPurifyingSaltCure },
    { EVENT_SWITCH_IN, HandlerPurifyingSaltCure },
    { EVENT_ACTION_END, HandlerPurifyingSaltActionEnd },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddPurifyingSalt(u32* packed) {
    *packed = sizeof(PURIFYING_SALT_HANDLERS) / sizeof(PURIFYING_SALT_HANDLERS[0]);
    return PURIFYING_SALT_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_PurifyingSaltHandlers[7] = {PURIFYING_SALT_HANDLERS[0], PURIFYING_SALT_HANDLERS[1], PURIFYING_SALT_HANDLERS[2], PURIFYING_SALT_HANDLERS[3], PURIFYING_SALT_HANDLERS[4], PURIFYING_SALT_HANDLERS[5], PURIFYING_SALT_HANDLERS[6]};
static_assert(sizeof(PURIFYING_SALT_HANDLERS) / sizeof(PURIFYING_SALT_HANDLERS[0]) == 7, "MB_PurifyingSaltHandlers");
