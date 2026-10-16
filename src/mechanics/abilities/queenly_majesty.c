/* Queenly Majesty, Dazzling, Armor Tail (Gen 7, 9; Showdown): a foe's move with priority above 0 (after Prankster,
 * Gale Wings, Triage) aimed at the holder or its ally fails: the holder's popup and "X cannot use Y!", as in the games.
 * The priority is the move's own (ServerEvent_GetMovePriority), not its place in the turn order: Quick Claw and
 * Lagging Tail don't count. Showdown stops the move in TryMove; the engine's move-execution check carries no
 * target, so here each target the rule covers is not affected (EVENT_CHECK_NO_EFFECT), which ends the same way for
 * the moves it covers, moves aimed at Pokémon. The message comes once per move: a spread move's other targets are
 * stopped without one. Not covered: Prankster field moves (Haze), which have no target to check. Mold Breaker ignores
 * it (IsMoldBreakerAffectedAbility in w2u_abilities.cpp).
 * One table for all three (registry name QueenlyMajestyHandlers, one module, so the once-per-move note is shared;
 * Black 2's baseline copy keeps W2U's earlier popup-less block). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define PRIORITY_ZERO 7                 /* ServerEvent_GetMovePriority returns priority + 7 */
#define MSG_SET_CANNOT_USE 905          /* bank 18: "{0} cannot use {1}!" (move) */

/* The current move was stopped already (module state, cleared when any move starts) */
static b32 sQueenlyMajestyStopped;

static void HandlerQueenlyMajestyMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)monId;
    (void)work;
    sQueenlyMajestyStopped = 0;
}

static void HandlerQueenlyMajestyNoEffect(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerMessageParam *message;
    u8 defender = W2U_Defender(), attacker = W2U_Attacker();
    u16 move;

    (void)item;
    (void)work;
    if (!W2U_IsAlly(monId, defender) || W2U_IsAlly(monId, attacker)) {
        return;                         /* the holder's side, a foe's move */
    }
    move = W2U_Move();
    if (!W2U_TargetsPokemon(move)) {
        return;
    }
    if (ServerEvent_GetMovePriority(flow, move, GetBattleMon(flow, attacker)) <= PRIORITY_ZERO) {
        return;
    }
    if (!BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) {
        return;
    }
    if (sQueenlyMajestyStopped) {
        BattleEventVar_RewriteValue(VAR_NO_DEFAULT_MESSAGE, 1);
        return;
    }
    sQueenlyMajestyStopped = 1;
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    message = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
    BattleHandler_StrSetup(&message->string, HANDLER_STR_SET, MSG_SET_CANNOT_USE);
    BattleHandler_AddArg(&message->string, attacker);
    BattleHandler_AddArg(&message->string, move);
    BattleHandler_PopWork(flow, message);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

W2U_HANDLER_TABLE(QueenlyMajestyHandlers) = {
    { EVENT_MOVE_START, HandlerQueenlyMajestyMoveStart },
    { EVENT_CHECK_NO_EFFECT, HandlerQueenlyMajestyNoEffect },
};
W2U_MECHANIC(ABILITY, ABIL_QUEENLY_MAJESTY, QueenlyMajestyHandlers);
W2U_MECHANIC(ABILITY, ABIL_DAZZLING, QueenlyMajestyHandlers);
W2U_MECHANIC(ABILITY, ABIL_ARMOR_TAIL, QueenlyMajestyHandlers);
