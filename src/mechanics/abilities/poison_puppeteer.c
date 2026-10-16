/* Poison Puppeteer (Gen 9): a Pokémon the holder poisons (or badly poisons) also becomes confused (the status was
 * inflicted; Confuse Ray's condition value; not if it is already confused). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MOVE_CONFUSE_RAY 109

static void HandlerPoisonPuppeteerStatus(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerAddConditionParam *param;
    BattleMon *mon;
    u8 target;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId || BattleEventVar_GetValue(VAR_CONDITION) != CONDITION_POISON) {
        return;
    }
    target = W2U_Defender();
    if (target == monId || target >= BATTLE_MAX_MON_ID) {
        return;
    }
    mon = GetBattleMon(flow, target);
    if (IsFainted(mon) || CheckCondition(mon, CONDITION_CONFUSION)) {
        return;
    }
    param = (BattleHandlerAddConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_CONDITION, monId);
    param->popup = 1;
    param->condition = CONDITION_CONFUSION;
    BtlCalc_BuildMoveCondition(PML_MoveGetConditionParam(MOVE_CONFUSE_RAY), GetBattleMon(flow, monId), &param->value);
    param->targetIndex = target;
    BattleHandler_PopWork(flow, param);
}

W2U_HANDLER_TABLE(PoisonPuppeteerHandlers) = {
    { EVENT_STATUS_INFLICTED, HandlerPoisonPuppeteerStatus },
};
W2U_MECHANIC(ABILITY, ABIL_POISON_PUPPETEER, PoisonPuppeteerHandlers);
