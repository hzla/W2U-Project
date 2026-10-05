// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/PropellerTail.cpp); see docs/megab2w2-integration.md.
// Propeller Tail / Stalwart (Gen 8; Gen 9 / Showdown): the holder's moves ignore redirection - Follow Me / Rage
// Powder, Lightning Rod / Storm Drain, and W2U's Spotlight. The engine asks Battle_IsRedirectBlocked first; those
// calls are wrapped in the resident core (mb_resident.cpp), Spotlight checks the abilities itself (w2u_moves.cpp).
// The handler table is empty: the ability's presence is the whole effect.
#include "../ability_api.h"

namespace {
void HandlerPropellerTailNone(BattleEventItem*, ServerFlow*, u32, u32*) {}
const BattleEventHandlerTableEntry PROPELLER_TAIL_HANDLERS[] = {
    { EVENT_MOVE_END, HandlerPropellerTailNone },
};
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_PropellerTailHandlers[1] = {PROPELLER_TAIL_HANDLERS[0]};
static_assert(sizeof(PROPELLER_TAIL_HANDLERS) / sizeof(PROPELLER_TAIL_HANDLERS[0]) == 1, "MB_PropellerTailHandlers");
