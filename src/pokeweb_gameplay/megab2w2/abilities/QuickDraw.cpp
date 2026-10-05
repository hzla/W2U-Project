// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/QuickDraw.cpp); see docs/megab2w2-integration.md.
// Quick Draw (Gen 8; Gen 9 / Showdown): 30% of the time the holder moves first in its priority bracket, for damaging
// moves only. Quick Claw's mechanism (item 217, ov167 0x21C3C64): event 0x0F (special priority: VAR_MON_ID; var 0x11
// = 1 normal, 2 = first in its bracket). The event carries no move: the holder's pending move comes from the
// resident core (W2U_MB_PendingMove, noted at the action-order sorts). The order can be computed more than once a
// turn, so the roll is made once per turn and kept; the message comes with the first activation.
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_resident.h"

namespace {
constexpr u32 QD_EVENT_SPECIAL_PRIORITY = 0x0F, QD_VAR_SPECIAL_PRIORITY = 0x11, QD_FIRST = 2;
u8 g_quickDraw[ability::MAX_POKE_ID];   // 0 = not rolled this turn, 1 = failed, 2 = succeeded

void HandlerQuickDrawPriority(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || pokeID >= ability::MAX_POKE_ID || ability::Simulating(sf)) return;
    if (!g_quickDraw[pokeID]) {
        u16 move = W2U_MB_PendingMove(sf, pokeID);
        bool ok = move && !ability::IsStatusMove(move) && AbilityEvent_RollEffectChance(sf, 30);
        g_quickDraw[pokeID] = ok ? 2 : 1;
        if (ok) {
            ability::PopupSetMessage(sf, pokeID, BTLMSG_SET_QUICK_DRAW);
            MLOG("[ABIL] Quick Draw: poke %d moves first (move %d)", pokeID, move);
        }
    }
    if (g_quickDraw[pokeID] == 2) BattleEventVar_RewriteValue(QD_VAR_SPECIAL_PRIORITY, QD_FIRST);
}
void HandlerQuickDrawTurnEnd(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (pokeID >= ability::MAX_POKE_ID) return;
    g_quickDraw[pokeID] = 0;
    W2U_MB_ClearPendingMove(pokeID);
}

const BattleEventHandlerTableEntry QUICK_DRAW_HANDLERS[] = {
    { QD_EVENT_SPECIAL_PRIORITY, HandlerQuickDrawPriority },
    { EVENT_TURN_CHECK, HandlerQuickDrawTurnEnd },
};
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_QuickDrawHandlers[2] = {QUICK_DRAW_HANDLERS[0], QUICK_DRAW_HANDLERS[1]};
static_assert(sizeof(QUICK_DRAW_HANDLERS) / sizeof(QUICK_DRAW_HANDLERS[0]) == 2, "MB_QuickDrawHandlers");
