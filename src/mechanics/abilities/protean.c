/* Protean, Libero (Gen 6, 8; the Gen 9 rule, Showdown): before it uses a move, the holder becomes that move's type
 * (its final type: -ate abilities, Weather Ball), once per switch-in, only when the type actually changes. Not for
 * Struggle, a move that calls another (Metronome, Sleep Talk...: the called move counts) or a future attack (Future
 * Sight, Doom Desire); Burn Up and Double Shock need their type already, so they fail as they would without it.
 * Conversion's type change with the popup; the engine shows "X transformed into the Y type!". One table for both
 * abilities (registry name ProteanHandlers; Black 2's baseline copy keeps W2U's earlier every-move Protean). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static const u16 sProteanSkippedMoves[] = {
    165,                                /* Struggle */
    118,                                /* Metronome */
    119,                                /* Mirror Move */
    214,                                /* Sleep Talk */
    267,                                /* Nature Power */
    274,                                /* Assist */
    382,                                /* Me First */
    383,                                /* Copycat */
    248,                                /* Future Sight */
    353,                                /* Doom Desire */
};

#define PROTEAN_MOVE_BURN_UP 682
#define PROTEAN_MOVE_DOUBLE_SHOCK 892

/* Used since the Pokémon's switch-in (module state, as MegaB2W2 kept it) */
static b32 sProteanUsed[BATTLE_MAX_MON_ID];

static void HandlerProteanSwitchIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() == monId && monId < BATTLE_MAX_MON_ID) {
        sProteanUsed[monId] = 0;
    }
}

static void HandlerProteanMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerChangeTypeParam *param;
    PokeTypePair pair, current;
    u16 move;
    u32 i;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID || sProteanUsed[monId]) {
        return;
    }
    move = W2U_Move();
    for (i = 0; i < NELEMS(sProteanSkippedMoves); ++i) {
        if (move == sProteanSkippedMoves[i]) {
            return;
        }
    }
    current = GetPokeType(GetBattleMon(flow, monId));
    if ((move == PROTEAN_MOVE_BURN_UP && !PokeTypePair_HasType(current, TYPE_FIRE))
        || (move == PROTEAN_MOVE_DOUBLE_SHOCK && !PokeTypePair_HasType(current, TYPE_ELECTRIC))) {
        return;
    }
    pair = PokeTypePair_MakeMonotype(W2U_FinalMoveType(flow, move, monId));
    if (current == pair) {
        return;
    }
    sProteanUsed[monId] = 1;
    param = (BattleHandlerChangeTypeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_TYPE, monId);
    W2U_WorkPopup(param);
    param->type = pair;
    param->monIndex = monId;
    BattleHandler_PopWork(flow, param);
}

W2U_HANDLER_TABLE(ProteanHandlers) = {
    { EVENT_SWITCH_IN, HandlerProteanSwitchIn },
    { EVENT_MOVE_START, HandlerProteanMoveStart },
};
W2U_MECHANIC(ABILITY, ABIL_PROTEAN, ProteanHandlers);
W2U_MECHANIC(ABILITY, ABIL_LIBERO, ProteanHandlers);
