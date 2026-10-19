/* Parental Bond: the holder's single-target moves hit twice (DamageRoot: resident/parental_bond.c decides and sets
 * the state); the second hit does a quarter of the damage. Each hit's EVENT_MOVE_POWER counts it, and on the second
 * EVENT_DAMAGE_RATIO cuts it to x0.25 (the damage, not the power; fixed-damage moves skip both events). */
#include "w2u/battle_api.h"
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define PARENTAL_BOND_SECOND_HIT 1024   /* x0.25 */

static void HandlerParentalBondPower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_ParentalBondActive() && W2U_Attacker() == monId) {
        W2U_ParentalBondCountHit();
    }
}

static void HandlerParentalBondDamage(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_ParentalBondActive() && W2U_ParentalBondHit() == 2 && W2U_Attacker() == monId) {
        W2U_MulRatio(PARENTAL_BOND_SECOND_HIT);
    }
}

W2U_HANDLER_TABLE(ParentalBondHandlers) = {
    { EVENT_MOVE_POWER, HandlerParentalBondPower },
    { EVENT_DAMAGE_RATIO, HandlerParentalBondDamage },
};
W2U_MECHANIC(ABILITY, ABIL_PARENTAL_BOND, ParentalBondHandlers);
