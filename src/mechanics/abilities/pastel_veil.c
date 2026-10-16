/* Pastel Veil (Gen 8): the holder and its allies can't be poisoned (bad poison too; any source, Showdown); on entering
 * it cures poisoned Pokémon on its side, and an ally entering poisoned. The status check is the vanilla one
 * (EVENT_ADD_CONDITION_CHECK, VAR_FAIL_FLAG; Insomnia's pattern); the message (the holder's popup and the line naming
 * the protected Pokémon) is pushed right there, since some paths never raise EVENT_ADD_CONDITION_FAILED (Toxic Orb).
 * Mold Breaker ignores it (IsMoldBreakerAffectedAbility in w2u_abilities.cpp).
 * MegaB2W2's Veil table also had Aroma, Flower and Sweet Veil rows, which keep W2U's own handlers: they were never
 * reached, nor were its Yawn and stat drop handlers, which only those rows used. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

/* The holder's veil covers target: its side, and on the field (or the holder itself) */
static b32 PastelVeilCovers(BtlServerFlow *flow, u8 holder, u8 target)
{
    if (target >= BATTLE_MAX_MON_ID || !W2U_IsAlly(holder, target)) {
        return 0;
    }
    return target == holder || W2U_OnField(flow, target);
}

/* work[0] = 1: a block happened (EVENT_ADD_CONDITION_FAILED then has nothing more to say) */
static void HandlerPastelVeilConditionCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 target = W2U_Defender();

    (void)item;
    if (W2U_HolderAbility(flow, monId) != ABIL_PASTEL_VEIL
        || BattleEventVar_GetValue(VAR_CONDITION) != CONDITION_POISON || !PastelVeilCovers(flow, monId, target)) {
        return;
    }
    if (BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) {
        work[0] = 1;
        W2U_PopupMessageAbout(flow, monId, BTLMSG_SET_PASTEL_VEIL, target);
    }
}

static void HandlerPastelVeilConditionFailed(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)monId;
    work[0] = 0;                        /* the message is out already */
}

/* Cures target's poison (CommonAbilityCureStatusCore's effect, for any Pokémon on the holder's side) */
static void PastelVeilCure(BtlServerFlow *flow, u8 holder, u8 target, b32 *popup)
{
    BattleHandlerCureConditionParam *param;

    if (!CheckCondition(GetBattleMon(flow, target), CONDITION_POISON)) {
        return;
    }
    if (!*popup) {
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, holder);
        *popup = 1;
    }
    param = (BattleHandlerCureConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CURE_CONDITION, holder);
    param->condition = CONDITION_POISON;
    param->monIds[0] = target;
    param->count = 1;
    BattleHandler_PopWork(flow, param);
}

static void HandlerPastelVeilSwitchIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 who, id;
    b32 popup = 0;

    (void)item;
    (void)work;
    if (W2U_HolderAbility(flow, monId) != ABIL_PASTEL_VEIL) {
        return;
    }
    who = W2U_Subject();
    if (who == monId) {                 /* the holder enters: every poisoned Pokémon on its side */
        for (id = 0; id < BATTLE_MAX_MON_ID; ++id) {
            if (W2U_OnFieldAlive(flow, id) && W2U_IsAlly(monId, id)) {
                PastelVeilCure(flow, monId, id, &popup);
            }
        }
    } else if (W2U_IsAlly(monId, who) && W2U_OnField(flow, monId)) {
        PastelVeilCure(flow, monId, who, &popup);
    }
    if (popup) {
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    }
}

W2U_HANDLER_TABLE(PastelVeilHandlers) = {
    { EVENT_ADD_CONDITION_CHECK, HandlerPastelVeilConditionCheck },
    { EVENT_ADD_CONDITION_FAILED, HandlerPastelVeilConditionFailed },
    { EVENT_SWITCH_IN, HandlerPastelVeilSwitchIn },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerPastelVeilSwitchIn },
};
W2U_MECHANIC(ABILITY, ABIL_PASTEL_VEIL, PastelVeilHandlers);
