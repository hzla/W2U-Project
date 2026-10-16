/* Purifying Salt (Gen 9): the holder can't get a major status (paralysis, sleep, freeze, burn, poison) nor Yawn's
 * drowsiness, and Ghost moves against it use half the attacker's attacking stat. The statuses: Water Veil's pattern
 * for every status with the vanilla helpers, Yawn as Insomnia. Mold Breaker ignores it (IsMoldBreakerAffectedAbility
 * in w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static const u32 sPurifyingSaltConditions[] = {
    CONDITION_PARALYSIS, CONDITION_SLEEP, CONDITION_FREEZE, CONDITION_BURN, CONDITION_POISON, CONDITION_YAWN,
};

static void HandlerPurifyingSaltAttackingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Defender() == monId && W2U_Attacker() != monId && W2U_MoveType() == TYPE_GHOST) {
        W2U_MulRatio(2048);             /* x0.5 */
    }
}

static void HandlerPurifyingSaltGuard(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 i;

    (void)item;
    for (i = 0; i < NELEMS(sPurifyingSaltConditions); ++i) {
        if ((work[0] = HandlerCommonGuardStatus(flow, monId, sPurifyingSaltConditions[i])) != 0) {
            return;
        }
    }
}

static void HandlerPurifyingSaltCure(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 i;

    (void)item;
    (void)work;
    for (i = 0; i < NELEMS(sPurifyingSaltConditions); ++i) {
        CommonAbilityCureStatus(flow, monId, sPurifyingSaltConditions[i]);
    }
}

static void HandlerPurifyingSaltActionEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 i;

    (void)item;
    (void)work;
    for (i = 0; i < NELEMS(sPurifyingSaltConditions); ++i) {
        CommonAbilityCureStatusCore(flow, monId, sPurifyingSaltConditions[i]);
    }
}

W2U_HANDLER_TABLE(PurifyingSaltHandlers) = {
    { EVENT_ATTACKING_STAT, HandlerPurifyingSaltAttackingStat },
    { EVENT_ADD_CONDITION_CHECK, HandlerPurifyingSaltGuard },
    { EVENT_ADD_CONDITION_FAILED, HandlerAddStatusFailedCommon },
    { EVENT_YAWN_CHECK, HandlerInsomniaYawnCheck },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerPurifyingSaltCure },
    { EVENT_SWITCH_IN, HandlerPurifyingSaltCure },
    { EVENT_ACTION_END, HandlerPurifyingSaltActionEnd },
};
W2U_MECHANIC(ABILITY, ABIL_PURIFYING_SALT, PurifyingSaltHandlers);
