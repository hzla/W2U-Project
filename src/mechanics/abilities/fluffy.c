/* Fluffy, Ice Scales, Aura Guard: the damage the holder takes is multiplied when the hit matches a row
 * (EVENT_DAMAGE_RATIO; Showdown's onSourceModifyDamage). The rows that match multiply together:
 *   Fluffy      contact x0.5, Fire x2 (a contact Fire move: x1)
 *   Ice Scales  special x0.5
 *   Aura Guard  contact x0.5 (Legends: Z-A)
 * Mold Breaker ignores them (W2U_IsLaterIgnorableAbility, resident/mold_breaker.c). One table serves all three.
 * Black 2 keeps its baseline copy of Fluffy (b2_baseline/w2u_abilities.cpp.inc). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

enum { MATCH_CONTACT, MATCH_TYPE, MATCH_SPECIAL };

typedef struct {
    u16 ability;
    u8 match;
    u8 type;
    u16 ratio;
} FluffyRow;

static const FluffyRow sFluffyRows[] = {
    { ABIL_FLUFFY, MATCH_CONTACT, 0, 2048 },
    { ABIL_FLUFFY, MATCH_TYPE, TYPE_FIRE, 8192 },
    { ABIL_ICE_SCALES, MATCH_SPECIAL, 0, 2048 },
    { ABIL_AURA_GUARD, MATCH_CONTACT, 0, 2048 },
};

static b32 FluffyRowMatches(const FluffyRow *row, BtlServerFlow *flow, u16 move)
{
    /* if, not switch: switch jump tables need a libgcc helper the ESDB lacks */
    if (row->match == MATCH_CONTACT) {
        return W2U_MakesContact(flow, move);
    }
    if (row->match == MATCH_TYPE) {
        return W2U_MoveType() == row->type;
    }
    return W2U_MoveCategory(move) == MOVE_CATEGORY_SPECIAL;
}

static void HandlerFluffyDamageRatio(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u16 ability, move;
    u32 ratio = W2U_RATIO_ONE, i;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId) {
        return;
    }
    ability = W2U_HolderAbility(flow, monId);
    move = W2U_Move();
    for (i = 0; i < NELEMS(sFluffyRows); ++i) {
        if (sFluffyRows[i].ability == ability && FluffyRowMatches(&sFluffyRows[i], flow, move)) {
            ratio = W2U_RatioMul(ratio, sFluffyRows[i].ratio);
        }
    }
    if (ratio != W2U_RATIO_ONE) {           /* no row, or rows cancelling out */
        W2U_MulRatio((s32)ratio);
    }
}

W2U_HANDLER_TABLE(FluffyHandlers) = {
    { EVENT_DAMAGE_RATIO, HandlerFluffyDamageRatio },
};
W2U_MECHANIC(ABILITY, ABIL_FLUFFY, FluffyHandlers);
W2U_MECHANIC(ABILITY, ABIL_ICE_SCALES, FluffyHandlers);
W2U_MECHANIC(ABILITY, ABIL_AURA_GUARD, FluffyHandlers);
