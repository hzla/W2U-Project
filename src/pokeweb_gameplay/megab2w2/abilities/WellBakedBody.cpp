// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/WellBakedBody.cpp); see docs/megab2w2-integration.md.
// Well-Baked Body (Gen 9; data/abilities.yml WELL_BAKED_BODY): Fire moves don't affect the holder and raise its
// Defense by 2. Sap Sipper with Fire / Defense +2: the same vanilla helpers. Mold Breaker ignores it (`breakable`).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
void HandlerWellBakedBodyCheckNoEffect(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (!CommonDamageRecoverCheck(sf, pokeID, TYPE_FIRE)) return;
    CommonTypeNoEffectRankUp(sf, pokeID, ability::STAT_DEF, 2);
    MLOG("[ABIL] Well-Baked Body: poke %d absorbs move %d", pokeID, ability::Move());
}

constexpr BattleEventHandlerTableEntry WELL_BAKED_BODY_HANDLERS[] = {
    { EVENT_CHECK_NO_EFFECT, HandlerWellBakedBodyCheckNoEffect },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddWellBakedBody(u32* packed) {
    *packed = sizeof(WELL_BAKED_BODY_HANDLERS) / sizeof(WELL_BAKED_BODY_HANDLERS[0]);
    return WELL_BAKED_BODY_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_WellBakedBodyHandlers[1] = {WELL_BAKED_BODY_HANDLERS[0]};
static_assert(sizeof(WELL_BAKED_BODY_HANDLERS) / sizeof(WELL_BAKED_BODY_HANDLERS[0]) == 1, "MB_WellBakedBodyHandlers");
