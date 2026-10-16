/* Wind Rider (Gen 9): wind moves used on the holder by others don't affect it and raise its Attack by 1 instead;
 * Tailwind starting on its side raises its Attack by 1, as does entering (or gaining the ability) while Tailwind
 * blows there. Mold Breaker ignores the immunity (IsMoldBreakerAffectedAbility in w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MOVE_TAILWIND 366

static void HandlerWindRiderNoEffect(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Defender() != monId || W2U_Attacker() == monId) {
        return;
    }
    if (!W2U_MoveHasFlag(W2U_Move(), MOVE_FLAG_WIND) || !BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) {
        return;
    }
    CommonTypeNoEffectRankUp(flow, monId, STATSTAGE_ATTACK, 1);
}

/* Tailwind: whether it was blowing is noted when the move starts (work[0]); a new Tailwind boosts when it ends,
 * before the move's own messages */
static void HandlerWindRiderTailwindStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    work[0] = SideEffect_IsActive(GetSideFromMonID(monId), SIDE_EFFECT_TAILWIND);
}

static void HandlerWindRiderTailwind(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    if (W2U_Move() != MOVE_TAILWIND || !W2U_IsAlly(monId, W2U_Attacker())) {
        return;
    }
    if (work[0] || !SideEffect_IsActive(GetSideFromMonID(monId), SIDE_EFFECT_TAILWIND)) {
        return;
    }
    W2U_ChangeStatStage(flow, monId, monId, STATSTAGE_ATTACK, 1, 1);
}

static void HandlerWindRiderStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Subject() != monId || !SideEffect_IsActive(GetSideFromMonID(monId), SIDE_EFFECT_TAILWIND)) {
        return;
    }
    W2U_ChangeStatStage(flow, monId, monId, STATSTAGE_ATTACK, 1, 1);
}

W2U_HANDLER_TABLE(WindRiderHandlers) = {
    { EVENT_CHECK_NO_EFFECT, HandlerWindRiderNoEffect },
    { EVENT_MOVE_START, HandlerWindRiderTailwindStart },
    { EVENT_MOVE_END, HandlerWindRiderTailwind },
    { EVENT_SWITCH_IN, HandlerWindRiderStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerWindRiderStart },
};
W2U_MECHANIC(ABILITY, ABIL_WIND_RIDER, WindRiderHandlers);
