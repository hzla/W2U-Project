/* Quick Draw (Gen 8; Showdown): 30 % of the time the holder moves first in its priority bracket, for damaging moves
 * only. Quick Claw's mechanism (EVENT_SPECIAL_PRIORITY: VAR_SPECIAL_PRIORITY 2 = first in its bracket). The event
 * carries no move: the holder's pending move comes from the resident core (W2U_MB_PendingMove, noted at the
 * action-order sorts). The order can be computed more than once a turn, so the roll is made once per turn and kept;
 * the message comes with the first activation. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define QUICK_DRAW_FIRST 2

/* Per Pokémon this turn: 0 not rolled, 1 failed, 2 succeeded */
static u8 sQuickDrawRoll[BATTLE_MAX_MON_ID];

static void HandlerQuickDrawPriority(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID || W2U_IsSimulating(flow)) {
        return;
    }
    if (!sQuickDrawRoll[monId]) {
        u16 move = W2U_MB_PendingMove(flow, monId);
        b32 ok = move && !W2U_IsStatusMove(move) && AbilityEvent_RollEffectChance(flow, 30);
        sQuickDrawRoll[monId] = ok ? 2 : 1;
        if (ok) {
            W2U_PopupMessage(flow, monId, BTLMSG_SET_QUICK_DRAW);
        }
    }
    if (sQuickDrawRoll[monId] == 2) {
        BattleEventVar_RewriteValue(VAR_SPECIAL_PRIORITY, QUICK_DRAW_FIRST);
    }
}

static void HandlerQuickDrawTurnEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    sQuickDrawRoll[monId] = 0;
    W2U_MB_ClearPendingMove(monId);
}

W2U_HANDLER_TABLE(QuickDrawHandlers) = {
    { EVENT_SPECIAL_PRIORITY, HandlerQuickDrawPriority },
    { EVENT_TURN_CHECK, HandlerQuickDrawTurnEnd },
};
W2U_MECHANIC(ABILITY, ABIL_QUICK_DRAW, QuickDrawHandlers);
