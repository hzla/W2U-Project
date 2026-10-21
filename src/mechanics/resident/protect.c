/* The protection check of a move's targets (the engine's flowsub_CheckNoEffect_Protect, decomp ServerControl_RemoveNoEffectTargets):
 * W2U asks every target, with the attacker, the target, the move's category and the move, whether the protection
 * holds (W2U_CheckProtectBreak, EVENT_PROTECT_BREAK_CHECK: VAR_BREAK_PROTECT 0 it holds, 1 broken as Feint does,
 * 2 the move goes through and the protection stays: Unseen Fist, Piercing Drill). The engine asked only Feint's
 * yes / no, and only for moves Protect blocks. When it holds, "X protected itself!" and W2U's EVENT_PROTECT_SUCCESS
 * (the damage shields: Spiky Shield, Baneful Bunker...); when broken, EVENT_PROTECT_BROKEN.
 * The injection build replaces the whole function (w2u_moves.cpp) and its protect loop asks W2U_ProtectBlocks; a
 * decomp build's loop does the same. */
#include "w2u/resident.h"

#define MSG_PROTECTED_ITSELF 523        /* bank 18: "X protected itself!" */
#define MSG_ARGUMENT_END 0xFFFF0000     /* the message's argument list ends */

u32 W2U_CheckProtectBreak(BtlServerFlow *flow, u32 attacker, u32 defender, u32 category, u16 move)
{
    u32 result;

    /* The engine raises the event with the attacker only; the damage shields also need the target and the category,
     * Unseen Fist the move (contact) */
    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, (s32)attacker);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, (s32)defender);
    BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, (s32)category);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, move);
    BattleEventVar_SetValue(VAR_BREAK_PROTECT, 0);
    BattleEvent_CallHandlers(flow, EVENT_PROTECT_BREAK_CHECK);
    result = BattleEventVar_GetValue(VAR_BREAK_PROTECT);
    BattleEventVar_Pop(__LINE__);
    return result;
}

/* W2U's new events about the protection: the engine's handlers of the reused ID see no Pokémon (-1) */
static void ProtectEvent(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u16 move, u32 event)
{
    u32 level = W2U_PushHandlerState(flow);

    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetConstValue(VAR_MON_ID, -1);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, -1);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, -1);
    BattleEventVar_SetConstValue(NEW_VAR_ATTACKING_MON, GetMonID(attacker));
    BattleEventVar_SetConstValue(NEW_VAR_DEFENDING_MON, GetMonID(target));
    BattleEventVar_SetConstValue(VAR_MOVE_ID, move);
    BattleEvent_CallHandlers(flow, event);
    BattleEventVar_Pop(__LINE__);
    W2U_PopHandlerState(flow, level);
}

b32 W2U_ProtectBlocks(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u16 move)
{
    b32 protectedNow = GetTurnFlag(target, TURN_FLAG_PROTECT) && getMoveFlag(move, MOVE_FLAG_INDEX_PROTECT);

    switch (W2U_CheckProtectBreak(flow, GetMonID(attacker), GetMonID(target), W2U_MoveCategory(move), move)) {
    case 0:
        if (protectedNow) {
            ServerDisplay_AddMessageImpl(W2U_ServerQueue(flow), SERVER_CMD_SET_MESSAGE, MSG_PROTECTED_ITSELF,
                                         GetMonID(target), MSG_ARGUMENT_END);
            ProtectEvent(flow, attacker, target, move, EVENT_PROTECT_SUCCESS);
            return 1;
        }
        return 0;
    case 1:
        ProtectEvent(flow, attacker, target, move, EVENT_PROTECT_BROKEN);
        return 0;
    default:
        return 0;
    }
}

/* Moves that share Protect's consecutive-use counter: vanilla's five (Protect, Detect, Endure, Wide Guard, Quick Guard)
 * and W2U's damage shields (King's Shield, Spiky Shield, Baneful Bunker, Obstruct, Silk Trap, Burning Bulwark) */
static const u16 sProtectCounterMoves[] = {
    182,                                /* Protect */
    197,                                /* Detect */
    203,                                /* Endure */
    469,                                /* Wide Guard */
    501,                                /* Quick Guard */
    588,                                /* King's Shield */
    596,                                /* Spiky Shield */
    661,                                /* Baneful Bunker */
    792,                                /* Obstruct */
    852,                                /* Silk Trap */
    908,                                /* Burning Bulwark */
};

b32 W2U_IsProtectCounterMove(u16 move)
{
    u32 i;

    for (i = 0; i < NELEMS(sProtectCounterMoves); ++i) {
        if (sProtectCounterMoves[i] == move) {
            return 1;
        }
    }
    return 0;
}

void W2U_StartProtectCounterMove(BtlServerFlow *flow, u32 monId)
{
    BattleMon *mon = GetBattleMon(flow, (u8)monId);
    BattleHandlerSetCounterParam *param;

    if (!mon || W2U_IsProtectCounterMove(GetPreviousMoveID(mon))) {
        return;
    }
    param = (BattleHandlerSetCounterParam *)BattleHandler_PushWork(flow, HANDLER_CMD_SET_COUNTER, monId);
    param->monIndex = (u8)monId;
    param->counter = COUNTER_PROTECT;
    param->value = 0;
    BattleHandler_PopWork(flow, param);
}
