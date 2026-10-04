// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/GoodAsGold.cpp); see docs/megab2w2-integration.md.
// Good as Gold (Gen 9, Gholdengo; data/abilities.yml GOOD_AS_GOLD): status moves used by any other Pokémon - foes
// and allies alike - don't affect the holder. Pokémon Showdown's rule: blocked when the status move targets
// Pokémon (one, several or all adjacent foes) and its user is not the holder. Not blocked: damaging moves and
// their secondary effects (Scald's burn), the holder's own moves, field / side moves (entry hazards, screens) and
// moves aimed at every Pokémon at once (Haze, Perish Song). Mold Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
void HandlerGoodAsGoldNoEffect(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || ability::Attacker() == pokeID) return;
    u16 move = ability::Move();
    if (!ability::IsStatusMove(move) || !ability::TargetsPokemon(move)) return;
    if (ability::BlockMove(sf, pokeID))
        MLOG("[ABIL] Good as Gold: poke %d blocks move %d from poke %d", pokeID, move, ability::Attacker());
}

constexpr BattleEventHandlerTableEntry GOOD_AS_GOLD_HANDLERS[] = {
    { EVENT_CHECK_NO_EFFECT, HandlerGoodAsGoldNoEffect },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddGoodAsGold(u32* packed) {
    *packed = sizeof(GOOD_AS_GOLD_HANDLERS) / sizeof(GOOD_AS_GOLD_HANDLERS[0]);
    return GOOD_AS_GOLD_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_GoodAsGoldHandlers[1] = {GOOD_AS_GOLD_HANDLERS[0]};
static_assert(sizeof(GOOD_AS_GOLD_HANDLERS) / sizeof(GOOD_AS_GOLD_HANDLERS[0]) == 1, "MB_GoodAsGoldHandlers");
