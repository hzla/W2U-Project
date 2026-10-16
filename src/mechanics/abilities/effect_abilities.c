/* Abilities that react to handler effects being carried out (Gen 8, 9; Showdown). The effect dispatcher's calls (use
 * held item, recover HP, damage, stat change, force use item) are wrapped in the resident core
 * (megab2w2/mb_resident.cpp), which does the part that has to happen inside those calls; these are the holders'
 * handlers.
 *   Ripen        a Berry's HP restored, stat boosts and damage to the attacker (Jaboca, Rowap) are doubled (the
 *                resident wrappers); the popup when the item is used. Damage-halving Berries (Occa...) aren't doubled.
 *   Opportunist  a foe's stat raises (as applied: moves and effects) are copied by the holder after the move, the
 *                action, a switch-in or the turn's end (Showdown's onFoeAfterBoost + onAnyAfterMove). Its own copies
 *                aren't copied back: the resident stat change wrapper runs them with a flag set.
 *   Cud Chew     a Berry the holder ate (noted by the resident use-item wrapper) is eaten again at the end of the
 *                next turn (the force-use-item effect, as Bug Bite eats). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

/* ---- Ripen ---- */

static void HandlerRipenUseItem(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Subject() != monId || !W2U_IsBerry(GetBattleMonHeldItem(GetBattleMon(flow, monId)))) {
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

/* ---- Opportunist ---- */

/* Per holder and stat: the raises waiting to be copied */
static s8 sOpportunistBoost[BATTLE_MAX_MON_ID][8];

static void OpportunistApply(BtlServerFlow *flow, u8 monId)
{
    b32 popup = 0;
    u32 stat;

    if (monId >= BATTLE_MAX_MON_ID || !W2U_OnField(flow, monId) || W2U_IsFainted(flow, monId)) {
        return;
    }
    for (stat = STATSTAGE_ATTACK; stat <= STATSTAGE_EVASION; ++stat) {
        s32 stages = sOpportunistBoost[monId][stat];
        if (stages <= 0) {
            continue;
        }
        sOpportunistBoost[monId][stat] = 0;
        if (!popup) {
            popup = 1;
            BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
        }
        W2U_MB_OpportunistCopyQueued(monId);       /* before the push: the effect may run at once */
        W2U_ChangeStatStage(flow, monId, monId, stat, stages > 6 ? 6 : stages, 0);
    }
    if (popup) {
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    }
}

static void HandlerOpportunistAny(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    OpportunistApply(flow, monId);
}

/* VAR_MON_ID's VAR_STAT changed by VAR_STAT_CHANGE, as applied: moves and effects alike */
static void HandlerOpportunistStatApplied(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 target = W2U_Subject();
    u32 stat = BattleEventVar_GetValue(VAR_STAT);
    s32 stages = (s32)BattleEventVar_GetValue(VAR_STAT_CHANGE);
    s32 total;

    (void)item;
    (void)flow;
    (void)work;
    if (W2U_MB_OpportunistCopying() || stages <= 0 || target == monId || target >= BATTLE_MAX_MON_ID
        || W2U_IsAlly(monId, target)) {
        return;
    }
    if (stat < STATSTAGE_ATTACK || stat > STATSTAGE_EVASION || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    total = sOpportunistBoost[monId][stat] + stages;
    sOpportunistBoost[monId][stat] = (s8)(total > 12 ? 12 : total);
}

/* ---- Cud Chew ---- */

static void HandlerCudChewTurnEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerForceUseItemParam *param;
    u16 berry;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    if (W2U_IsFainted(flow, monId)) {
        W2U_MB_CudChewForget(monId);
        return;
    }
    berry = W2U_MB_CudChewTurnEnd(monId);
    if (!berry) {
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    param = (BattleHandlerForceUseItemParam *)BattleHandler_PushWork(flow, HANDLER_CMD_FORCE_USE_ITEM, monId);
    param->checkPrevResult = 1;         /* bit 24, which MegaB2W2 and PW2Code set as "eat, not held" */
    param->monIndex = monId;
    param->item = berry;
    BattleHandler_PopWork(flow, param);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

W2U_HANDLER_TABLE(RipenHandlers) = {
    { EVENT_USE_ITEM, HandlerRipenUseItem },
};
W2U_MECHANIC(ABILITY, ABIL_RIPEN, RipenHandlers);

W2U_HANDLER_TABLE(OpportunistHandlers) = {
    { EVENT_STAT_CHANGE_APPLIED, HandlerOpportunistStatApplied },
    { EVENT_MOVE_END, HandlerOpportunistAny },
    { EVENT_ACTION_END, HandlerOpportunistAny },
    { EVENT_SWITCH_IN, HandlerOpportunistAny },
    { EVENT_TURN_CHECK_END, HandlerOpportunistAny },
};
W2U_MECHANIC(ABILITY, ABIL_OPPORTUNIST, OpportunistHandlers);

W2U_HANDLER_TABLE(CudChewHandlers) = {
    { EVENT_TURN_CHECK_END, HandlerCudChewTurnEnd },
};
W2U_MECHANIC(ABILITY, ABIL_CUD_CHEW, CudChewHandlers);
