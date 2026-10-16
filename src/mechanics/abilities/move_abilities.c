/* Abilities that change how the holder's own moves work (Showdown), with the resident core's help:
 *   Mycelium Might  status moves go last in their priority bracket (EVENT_SPECIAL_PRIORITY, VAR_SPECIAL_PRIORITY 0;
 *                   the move from the resident core, as Quick Draw) and ignore the target's ability (vanilla Mold
 *                   Breaker's start / end handlers, for status moves only)
 *   Mega Sol        the holder's moves act as if the sun were out (Fire x1.5, Water x0.5, one-turn Solar Beam, Fire
 *                   Weather Ball, Synthesis 2/3, Thunder / Hurricane 50 %...): while its move runs, the resident
 *                   ServerEvent_GetWeather answers sun. Everything that reads the weather during that move sees sun
 *                   (a target's Leaf Guard too); Showdown limits this to the holder.
 * Poison Puppeteer, once in the same MegaB2W2 file: abilities/poison_puppeteer.c. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MYCELIUM_MIGHT_LAST 0
#define MEGA_SOL_NONE 0xFF

static void HandlerMyceliumMightPriority(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u16 move;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    move = W2U_MB_PendingMove(flow, monId);
    if (move && W2U_IsStatusMove(move)) {
        BattleEventVar_RewriteValue(VAR_SPECIAL_PRIORITY, MYCELIUM_MIGHT_LAST);
    }
}

/* work[1] = 1: Mold Breaker's skip check is on for this move */
static void HandlerMyceliumMightMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    if (W2U_Attacker() != monId || !W2U_IsStatusMove(W2U_Move()) || work[1]) {
        return;
    }
    HandlerMoldBreakerStart(item, flow, monId, work);
    work[1] = 1;
}

static void HandlerMyceliumMightMoveEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    if (!work[1]) {
        return;
    }
    work[1] = 0;
    HandlerMoldBreakerEnd(item, flow, monId, work);
}

static void HandlerMyceliumMightTurnEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    W2U_MB_ClearPendingMove(monId);
}

static void HandlerMegaSolMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId) {
        W2U_MB_SetMegaSolAttacker(monId);
    }
}

static void HandlerMegaSolMoveEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId) {
        W2U_MB_SetMegaSolAttacker(MEGA_SOL_NONE);
    }
}

W2U_HANDLER_TABLE(MyceliumMightHandlers) = {
    { EVENT_SPECIAL_PRIORITY, HandlerMyceliumMightPriority },
    { EVENT_MOVE_START, HandlerMyceliumMightMoveStart },
    { EVENT_MOVE_END, HandlerMyceliumMightMoveEnd },
    { EVENT_TURN_CHECK, HandlerMyceliumMightTurnEnd },
};
W2U_MECHANIC(ABILITY, ABIL_MYCELIUM_MIGHT, MyceliumMightHandlers);

W2U_HANDLER_TABLE(MegaSolHandlers) = {
    { EVENT_MOVE_START, HandlerMegaSolMoveStart },
    { EVENT_MOVE_END, HandlerMegaSolMoveEnd },
};
W2U_MECHANIC(ABILITY, ABIL_MEGA_SOL, MegaSolHandlers);
