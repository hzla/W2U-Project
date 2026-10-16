/* Gorilla Tactics (Gen 8): Attack x1.5, and locked into the first move it uses: Choice Band as an ability, with the
 * Choice items' handlers (the attacking stat x1.5 for physical moves; after a move, the Choice lock with the move,
 * not for Struggle; switching out clears it). Losing the ability (Skill Swap, Gastro Acid...) cures the lock, as the
 * items do when the item changes, unless a Choice item still holds it.
 * The move menu enforces the lock in W2U's IsUnselectableMove (w2u_moves.cpp), with Encore's "X can use only Y!". */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MOVE_STRUGGLE 165
#define ITEM_CHOICE_BAND 220
#define ITEM_CHOICE_SCARF 287
#define ITEM_CHOICE_SPECS 297

static void HandlerGorillaTacticsAttackingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId && W2U_MoveCategory(W2U_Move()) == MOVE_CATEGORY_PHYSICAL) {
        W2U_MulRatio(6144);             /* x1.5 */
    }
}

static void HandlerGorillaTacticsLock(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerAddConditionParam *param;
    u16 move;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId) {
        return;
    }
    move = W2U_Move();
    if (move == MOVE_STRUGGLE) {
        return;
    }
    param = (BattleHandlerAddConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_CONDITION, monId);
    param->condition = CONDITION_CHOICE_LOCK;
    param->value = MakeConditionParamPermanent(move);
    param->targetIndex = monId;
    param->overwrite = 2;               /* as the Choice items lock */
    BattleHandler_PopWork(flow, param);
}

static void HandlerGorillaTacticsEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerCureConditionParam *param;
    u32 held;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    held = GetBattleMonHeldItem(GetBattleMon(flow, monId));
    if (held == ITEM_CHOICE_BAND || held == ITEM_CHOICE_SCARF || held == ITEM_CHOICE_SPECS) {
        return;
    }
    param = (BattleHandlerCureConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CURE_CONDITION, monId);
    param->condition = CONDITION_CHOICE_LOCK;
    param->monIds[0] = monId;
    param->count = 1;
    param->useString = 1;
    BattleHandler_PopWork(flow, param);
}

W2U_HANDLER_TABLE(GorillaTacticsHandlers) = {
    { EVENT_ATTACKING_STAT, HandlerGorillaTacticsAttackingStat },
    { EVENT_AFTER_MOVE_USE, HandlerGorillaTacticsLock },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerGorillaTacticsEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerGorillaTacticsEnd },
};
W2U_MECHANIC(ABILITY, ABIL_GORILLA_TACTICS, GorillaTacticsHandlers);
