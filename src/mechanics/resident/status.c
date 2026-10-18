/* Status conditions as W2U applies them:
 *   Comatose     the holder counts as asleep (CheckCondition), can't get a major status or drowsiness, and its
 *                status-curing items don't react;
 *   Corrosion    the holder poisons Steel and Poison types (the type immunity is lifted for it);
 *   Hex          doubles against any major status, as CheckCondition sees it (so against a Comatose holder too);
 *   a status check a handler fails with W2U_FORCE_FAIL_MESSAGE shows its fail message even when the move didn't ask.
 * W2U replaces ServerControl_AddConditionCheckFail, CheckCondition, HandlerHex and CommonStatusReaction whole
 * (w2u_abilities.cpp); a decomp build changes only their tests. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define W2U_FORCE_FAIL_MESSAGE 2        /* a status check's fail value that forces the message (w2u_abilities.cpp) */
#define FAIL_CAUSE_TYPE 2               /* AddConditionCheckFailOverwrite: the target's type is immune */
#define FAIL_CAUSE_NO_EFFECT 3          /* it doesn't affect the target */

/* Comatose can't be suppressed: the raw ability */
b32 W2U_IsComatose(BattleMon *mon)
{
    return mon && GetBattleMonStat(mon, BMV_ABILITY) == ABIL_COMATOSE;
}

b32 W2U_ComatoseAsleep(BattleMon *mon, u32 condition)
{
    return mon && condition == CONDITION_SLEEP && GetBattleMonStat(mon, BMV_EFFECTIVE_ABILITY) == ABIL_COMATOSE;
}

u32 W2U_ConditionFailCause(BattleMon *target, BattleMon *attacker, u32 condition, u32 cause)
{
    if (condition == CONDITION_POISON && cause == FAIL_CAUSE_TYPE && attacker &&
        GetBattleMonStat(attacker, BMV_EFFECTIVE_ABILITY) == ABIL_CORROSION) {
        cause = 0;
    }
    if ((condition < CONDITION_CONFUSION || condition == CONDITION_YAWN) && W2U_IsComatose(target)) {
        cause = FAIL_CAUSE_NO_EFFECT;
    }
    return cause;
}

b32 W2U_ConditionFailForcesMessage(u32 failed)
{
    return failed == W2U_FORCE_FAIL_MESSAGE;
}

b32 W2U_HasMajorStatus(BattleMon *mon)
{
    return mon && (CheckCondition(mon, CONDITION_PARALYSIS) || CheckCondition(mon, CONDITION_SLEEP) ||
                   CheckCondition(mon, CONDITION_FREEZE) || CheckCondition(mon, CONDITION_BURN) ||
                   CheckCondition(mon, CONDITION_POISON));
}
