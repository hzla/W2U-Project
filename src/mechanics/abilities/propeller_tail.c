/* Propeller Tail, Stalwart (Gen 8): the holder's moves ignore redirection (Follow Me, Rage Powder, Lightning Rod,
 * Storm Drain, W2U's Spotlight). The engine's redirection checks ask for the ability directly: those calls are
 * wrapped in the resident core (megab2w2/mb_resident.cpp) and Spotlight checks it itself (w2u_moves.cpp). So the
 * table only registers the ability; its handler does nothing. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerPropellerTailNone(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)monId;
    (void)work;
}

W2U_HANDLER_TABLE(PropellerTailHandlers) = {
    { EVENT_MOVE_END, HandlerPropellerTailNone },
};
W2U_MECHANIC(ABILITY, ABIL_PROPELLER_TAIL, PropellerTailHandlers);
W2U_MECHANIC(ABILITY, ABIL_STALWART, PropellerTailHandlers);
