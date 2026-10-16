/* Guard Dog (Gen 9): Intimidate raises the holder's Attack by 1 instead of lowering it, and it can't be forced out
 * (Suction Cups' vanilla guard). The stat drop has to be known to come from Intimidate, so this module also
 * registers Intimidate itself: vanilla's handler, with its user recorded while it runs (same events as vanilla
 * Intimidate; battles without this module keep vanilla Intimidate). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define ABIL_INTIMIDATE 22              /* vanilla (w2u_abilities.h has it as a C++ enumerator) */
#define GUARD_DOG_NO_MON 0xFF

/* The Pokémon whose Intimidate is running, while it runs */
static u32 sGuardDogIntimidator = GUARD_DOG_NO_MON;

static void HandlerGuardDogIntimidateTracked(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    sGuardDogIntimidator = monId;
    HandlerIntimidateMemberIn(item, flow, monId, work);
    sGuardDogIntimidator = GUARD_DOG_NO_MON;
}

static void HandlerGuardDogStatChangeCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Subject() != monId || sGuardDogIntimidator == GUARD_DOG_NO_MON
        || W2U_Attacker() != sGuardDogIntimidator) {
        return;
    }
    if (BattleEventVar_GetValue(VAR_STAT) != STATSTAGE_ATTACK || (s32)BattleEventVar_GetValue(VAR_STAT_CHANGE) >= 0) {
        return;
    }
    if (BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) {
        W2U_ChangeStatStage(flow, monId, monId, STATSTAGE_ATTACK, 1, 1);
    }
}

W2U_HANDLER_TABLE(GuardDogHandlers) = {
    { EVENT_STAT_CHANGE_CHECK, HandlerGuardDogStatChangeCheck },
    { EVENT_FORCE_OUT_CHECK, HandlerSuctionCups },
};
W2U_MECHANIC(ABILITY, ABIL_GUARD_DOG, GuardDogHandlers);

W2U_HANDLER_TABLE(IntimidateTrackedHandlers) = {
    { EVENT_SWITCH_IN, HandlerGuardDogIntimidateTracked },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerGuardDogIntimidateTracked },
};
W2U_MECHANIC(ABILITY, ABIL_INTIMIDATE, IntimidateTrackedHandlers);
