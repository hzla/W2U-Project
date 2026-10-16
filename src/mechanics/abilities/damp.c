/* Damp (W2U fix): no Pokémon can use a self-destructing move while the holder is on the field (Showdown: Explosion,
 * Self-Destruct, Mind Blown, Misty Explosion). Vanilla Damp's move check compares the move with Explosion and
 * Self-Destruct only, so the newer moves went off. This is vanilla Damp's table with that check replaced: on a listed
 * move it sets fail cause 0x13 (if there is no cause yet) and keeps the cause and the move in work[0] / work[1] for
 * vanilla's message handler (the popup and "X cannot use Y!"); vanilla's other handlers are used as they are. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define ABIL_DAMP 6                     /* vanilla (w2u_abilities.h has it as a C++ enumerator) */

#define DAMP_FAIL_CAUSE 0x13

static const u16 sDampMoves[] = {
    120,                                /* Self-Destruct */
    153,                                /* Explosion */
    720,                                /* Mind Blown */
    802,                                /* Misty Explosion */
};

static void HandlerDampMoveCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u16 move = W2U_Move();
    b32 listed = 0;
    u32 i;

    (void)item;
    (void)flow;
    (void)monId;
    work[0] = 0;
    for (i = 0; i < NELEMS(sDampMoves); ++i) {
        listed |= sDampMoves[i] == move;
    }
    if (!listed || BattleEventVar_GetValue(VAR_FAIL_CAUSE) != 0) {
        return;
    }
    work[0] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, DAMP_FAIL_CAUSE);
    work[1] = move;
}

W2U_HANDLER_TABLE(DampHandlers) = {
    { EVENT_DAMP_MOVE_CHECK, HandlerDampMoveCheck },
    { EVENT_DAMP_FAIL_MESSAGE, HandlerDampEffective },
    { EVENT_MOVE_START, HandlerDampStart },
    { EVENT_MOVE_END, HandlerDampMoveEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerDampEnd },
};
W2U_MECHANIC(ABILITY, ABIL_DAMP, DampHandlers);
