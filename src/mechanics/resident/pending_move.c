/* The move each fight action will use this turn (W2U_MB_PendingMove; Quick Draw, Mycelium Might): EVENT_SPECIAL_PRIORITY
 * carries no move. Noted at the two ServerEvent_GetMovePriority calls of the action-order sorts (the turn's first
 * order, before its special-priority check, and SortActionOrderBySpeed); afterwards the action order has it. */
#include "w2u/resident.h"

static u16 sSortMove[BATTLE_MAX_MON_ID];   /* the move of each fight action at the last action-order sort */

u8 W2U_GetMovePriority(BtlServerFlow *flow, u16 move, BattleMon *mon)
{
    u32 id = GetMonID(mon);

    if (id < BATTLE_MAX_MON_ID) {
        sSortMove[id] = move;
    }
    return ServerEvent_GetMovePriority(flow, move, mon);
}

u16 W2U_MB_PendingMove(BtlServerFlow *flow, u32 monId)
{
    ActionOrderEntry *order = W2U_ActionOrder(flow);
    u32 count = W2U_ActionOrderCount(flow);
    u32 i;

    for (i = 0; i < count; ++i) {
        if (order[i].done || !order[i].mon || GetMonID(order[i].mon) != monId) {
            continue;
        }
        return W2U_ActionMove(order[i].action);
    }
    /* The turn's first order runs before the action order is filled in: the move just noted for this Pokémon */
    return monId < BATTLE_MAX_MON_ID ? sSortMove[monId] : 0;
}

void W2U_MB_ClearPendingMove(u32 monId)
{
    if (monId < BATTLE_MAX_MON_ID) {
        sSortMove[monId] = 0;
    }
}

void W2U_Resident_ResetPendingMoves(void)
{
    u32 i;

    for (i = 0; i < BATTLE_MAX_MON_ID; ++i) {
        sSortMove[i] = 0;
    }
}
