/* Libero (Gen 8), MegaB2W2's Protean rule: before it uses a move, the holder becomes that move's type (its final type: -ate
 * abilities, Weather Ball). Showdown, Gen 9: once per switch-in, only when the type actually changes, not for Struggle
 * or a move that calls another (Metronome, Sleep Talk...: the called move counts). Conversion's type change with the
 * popup; the engine shows "X transformed into the Y type!".
 * Protean itself keeps W2U's own handler (w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static const u16 sLiberoSkippedMoves[] = {
    165,                                /* Struggle */
    118,                                /* Metronome */
    119,                                /* Mirror Move */
    214,                                /* Sleep Talk */
    267,                                /* Nature Power */
    274,                                /* Assist */
    382,                                /* Me First */
    383,                                /* Copycat */
};

/* Used since the Pokémon's switch-in (module state, as MegaB2W2 kept it) */
static b32 sLiberoUsed[BATTLE_MAX_MON_ID];

static void HandlerLiberoSwitchIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() == monId && monId < BATTLE_MAX_MON_ID) {
        sLiberoUsed[monId] = 0;
    }
}

static void HandlerLiberoMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerChangeTypeParam *param;
    PokeTypePair pair;
    u16 move;
    u32 i;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID || sLiberoUsed[monId]) {
        return;
    }
    move = W2U_Move();
    for (i = 0; i < NELEMS(sLiberoSkippedMoves); ++i) {
        if (move == sLiberoSkippedMoves[i]) {
            return;
        }
    }
    pair = PokeTypePair_MakeMonotype(W2U_FinalMoveType(flow, move, monId));
    if (GetPokeType(GetBattleMon(flow, monId)) == pair) {
        return;
    }
    sLiberoUsed[monId] = 1;
    param = (BattleHandlerChangeTypeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_TYPE, monId);
    param->popup = 1;
    param->type = pair;
    param->monIndex = monId;
    BattleHandler_PopWork(flow, param);
}

W2U_HANDLER_TABLE(LiberoHandlers) = {
    { EVENT_SWITCH_IN, HandlerLiberoSwitchIn },
    { EVENT_MOVE_START, HandlerLiberoMoveStart },
};
W2U_MECHANIC(ABILITY, ABIL_LIBERO, LiberoHandlers);
