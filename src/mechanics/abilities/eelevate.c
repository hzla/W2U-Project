/* Eelevate (Legends: Z-A): Levitate (its three vanilla handlers) and Beast Boost: each target its move KOs raises the
 * holder's highest stat by 1, one boost per fainted target (EVENT_AFTER_KO, the targets in VAR_TARGET0..).
 * The highest stat is compared without stat stages, as Beast Boost (w2u_abilities.cpp) and Showdown do. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerEelevateAfterKO(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 count, i;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId) {
        return;
    }
    count = BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (i = 0; i < count; ++i) {
        if (W2U_IsFainted(flow, (u8)BattleEventVar_GetValue(VAR_TARGET0 + i))) {
            W2U_ChangeStatStage(flow, monId, monId, W2U_BestRawStat(flow, monId), 1, 1);
        }
    }
}

W2U_HANDLER_TABLE(EelevateHandlers) = {
    { EVENT_CHECK_FLOATING, HandlerLevitate },
    { EVENT_CHECK_NO_EFFECT_TYPE, HandlerLevitateAddImmunity },
    { EVENT_TURN_CHECK, HandlerLevitateTurnCheck },
    { EVENT_AFTER_KO, HandlerEelevateAfterKO },
};
W2U_MECHANIC(ABILITY, ABIL_EELEVATE, EelevateHandlers);
