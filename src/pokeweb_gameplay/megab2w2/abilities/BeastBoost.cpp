// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/BeastBoost.cpp); see docs/megab2w2-integration.md.
// Beast Boost (Gen 7; data/abilities.yml BEAST_BOOST): each target its move KOs raises its highest stat by 1 (Gen 9 /
// Showdown: the raw stat, ties in the order Attack, Defense, Sp. Atk, Sp. Def, Speed). Moxie's shape (EVENT_AFTER_KO:
// the targets in VAR_TARGET0.., one boost per fainted one).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
void HandlerBeastBoostAfterKO(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    u32 n = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 i = 0; i < n; ++i) {
        if (!BattleMon_IsFainted(GetBattleMon(sf, (u32)BattleEventVar_GetValue(VAR_TARGET0 + i)))) continue;
        u32 stat = ability::BestStat(GetBattleMon(sf, pokeID));
        ability::ChangeStatStage(sf, pokeID, pokeID, stat, 1, true);
        MLOG("[ABIL] Beast Boost: poke %d stat %d +1", pokeID, stat);
    }
}

constexpr BattleEventHandlerTableEntry BEAST_BOOST_HANDLERS[] = {
    { EVENT_AFTER_KO, HandlerBeastBoostAfterKO },
};
// Eelevate (Legends Z-A; data/abilities.yml EELEVATE): Levitate (its three vanilla handlers: floating, the Ground
// immunity popup, the per-turn reset) + Beast Boost.
constexpr BattleEventHandlerTableEntry EELEVATE_HANDLERS[] = {
    { EVENT_CHECK_FLOATING, HandlerLevitate },
    { EVENT_CHECK_NO_EFFECT_TYPE, HandlerLevitateAddImmunity },
    { EVENT_TURN_CHECK, HandlerLevitateTurnCheck },
    { EVENT_AFTER_KO, HandlerBeastBoostAfterKO },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddBeastBoost(u32* packed) {
    *packed = sizeof(BEAST_BOOST_HANDLERS) / sizeof(BEAST_BOOST_HANDLERS[0]);
    return BEAST_BOOST_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddEelevate(u32* packed) {
    *packed = sizeof(EELEVATE_HANDLERS) / sizeof(EELEVATE_HANDLERS[0]);
    return EELEVATE_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_EelevateHandlers[4] = {EELEVATE_HANDLERS[0], EELEVATE_HANDLERS[1], EELEVATE_HANDLERS[2], EELEVATE_HANDLERS[3]};
static_assert(sizeof(EELEVATE_HANDLERS) / sizeof(EELEVATE_HANDLERS[0]) == 4, "MB_EelevateHandlers");
