// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/PunkRock.cpp); see docs/megab2w2-integration.md.
// Punk Rock (Gen 8; data/abilities.yml PUNK_ROCK): the holder's sound moves get 1.3x power; sound moves deal it half
// damage (Gen 9). Sound = the move record's flag (Hyper Voice, Bug Buzz, Snarl, Round, Disarming Voice ...). The
// defensive half is ignored by Mold Breaker (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
void HandlerPunkRockMovePower(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || !getMoveFlag(ability::Move(), MOVE_FLAG_SOUND)) return;
    BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);        // x1.3
    if (!ability::Simulating(sf)) MLOG("[ABIL] Punk Rock: poke %d move %d x1.3", pokeID, ability::Move());
}
void HandlerPunkRockDamageRatio(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Attacker() == pokeID) return;
    if (!getMoveFlag(ability::Move(), MOVE_FLAG_SOUND)) return;
    ability::MulRatio(2048);                                    // x0.5
    if (!ability::Simulating(sf)) MLOG("[ABIL] Punk Rock: poke %d takes move %d x0.5", pokeID, ability::Move());
}

constexpr BattleEventHandlerTableEntry PUNK_ROCK_HANDLERS[] = {
    { EVENT_MOVE_POWER, HandlerPunkRockMovePower },
    { EVENT_DAMAGE_RATIO, HandlerPunkRockDamageRatio },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddPunkRock(u32* packed) {
    *packed = sizeof(PUNK_ROCK_HANDLERS) / sizeof(PUNK_ROCK_HANDLERS[0]);
    return PUNK_ROCK_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_PunkRockHandlers[2] = {PUNK_ROCK_HANDLERS[0], PUNK_ROCK_HANDLERS[1]};
static_assert(sizeof(PUNK_ROCK_HANDLERS) / sizeof(PUNK_ROCK_HANDLERS[0]) == 2, "MB_PunkRockHandlers");
