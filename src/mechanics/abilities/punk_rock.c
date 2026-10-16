/* Punk Rock (Gen 8): the holder's sound moves get x1.3 power, and sound moves deal it half damage (Gen 9). Sound is
 * the move record's flag (Hyper Voice, Bug Buzz, Snarl, Round...). Mold Breaker ignores the defensive half
 * (IsMoldBreakerAffectedAbility in w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerPunkRockMovePower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId && W2U_MoveHasFlag(W2U_Move(), MOVE_FLAG_SOUND)) {
        W2U_MulMovePower(5325);         /* x1.3 */
    }
}

static void HandlerPunkRockDamageRatio(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Defender() == monId && W2U_Attacker() != monId && W2U_MoveHasFlag(W2U_Move(), MOVE_FLAG_SOUND)) {
        W2U_MulRatio(2048);             /* x0.5 */
    }
}

W2U_HANDLER_TABLE(PunkRockHandlers) = {
    { EVENT_MOVE_POWER, HandlerPunkRockMovePower },
    { EVENT_DAMAGE_RATIO, HandlerPunkRockDamageRatio },
};
W2U_MECHANIC(ABILITY, ABIL_PUNK_ROCK, PunkRockHandlers);
