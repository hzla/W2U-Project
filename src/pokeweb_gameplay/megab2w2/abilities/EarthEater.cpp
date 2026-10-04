// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/EarthEater.cpp); see docs/megab2w2-integration.md.
// Earth Eater (Gen 9; data/abilities.yml EARTH_EATER): Ground moves don't affect the holder and heal it 1/4 instead.
// Volt Absorb with Ground: the same two vanilla helpers. Mold Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
void HandlerEarthEaterCheckNoEffect(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (!CommonDamageRecoverCheck(sf, pokeID, TYPE_GROUND)) return;
    CommonTypeRecoverHP(sf, pokeID, 4);
    MLOG("[ABIL] Earth Eater: poke %d absorbs move %d", pokeID, ability::Move());
}

constexpr BattleEventHandlerTableEntry EARTH_EATER_HANDLERS[] = {
    { EVENT_CHECK_NO_EFFECT, HandlerEarthEaterCheckNoEffect },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddEarthEater(u32* packed) {
    *packed = sizeof(EARTH_EATER_HANDLERS) / sizeof(EARTH_EATER_HANDLERS[0]);
    return EARTH_EATER_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_EarthEaterHandlers[1] = {EARTH_EATER_HANDLERS[0]};
static_assert(sizeof(EARTH_EATER_HANDLERS) / sizeof(EARTH_EATER_HANDLERS[0]) == 1, "MB_EarthEaterHandlers");
