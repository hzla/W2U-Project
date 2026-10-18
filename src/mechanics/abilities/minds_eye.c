/* Mind's Eye (Gen 9): Scrappy and Keen Eye, Gen 9 style. Its Normal and Fighting moves hit Ghost types (Scrappy's
 * vanilla handler), its accuracy can't be lowered (Keen Eye's vanilla check and message), and it ignores the
 * target's evasion stages (Gen 6+ Keen Eye: the evasion stage rewritten to neutral). Mold Breaker ignores it
 * (W2U_IsLaterIgnorableAbility, resident/mold_breaker.c). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerMindsEyeAccuracyStage(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId) {
        BattleEventVar_RewriteValue(VAR_EVASION_STAGE, STATSTAGE_NEUTRAL);
    }
}

W2U_HANDLER_TABLE(MindsEyeHandlers) = {
    { EVENT_ACCURACY_STAGE, HandlerMindsEyeAccuracyStage },
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerScrappy },
    { EVENT_STAT_CHANGE_CHECK, HandlerKeenEyeCheck },
    { EVENT_STAT_CHANGE_GUARD, HandlerKeenEyeGuard },
};
W2U_MECHANIC(ABILITY, ABIL_MINDS_EYE, MindsEyeHandlers);
