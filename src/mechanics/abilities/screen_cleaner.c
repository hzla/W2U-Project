/* Screen Cleaner (Gen 8): on entering, or on gaining the ability, it removes Reflect and Light Screen from both sides
 * (Showdown; Aurora Veil doesn't exist here). The popup shows only when there is something to remove. The removal is
 * Brick Break's handler effect; the engine shows the "wore off" messages. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static b32 ScreenCleanerHasScreens(u32 side)
{
    return IsSideEffectSet(side, SIDE_EFFECT_REFLECT) || IsSideEffectSet(side, SIDE_EFFECT_LIGHT_SCREEN);
}

static void HandlerScreenCleanerStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    b32 sides[BATTLE_SIDES];
    b32 any = 0;
    u32 side;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    for (side = 0; side < BATTLE_SIDES; ++side) {
        any |= (sides[side] = ScreenCleanerHasScreens(side));
    }
    if (!any) {
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    for (side = 0; side < BATTLE_SIDES; ++side) {
        BattleHandlerRemoveSideEffectParam *param;
        if (!sides[side]) {
            continue;
        }
        param = (BattleHandlerRemoveSideEffectParam *)BattleHandler_PushWork(flow, HANDLER_CMD_REMOVE_SIDE_EFFECT,
                                                                             monId);
        param->effects[0] = 3;
        param->effects[1] = (1 << SIDE_EFFECT_REFLECT) | (1 << SIDE_EFFECT_LIGHT_SCREEN);
        param->effects[2] = 0;
        param->side = (u8)side;
        BattleHandler_PopWork(flow, param);
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

W2U_HANDLER_TABLE(ScreenCleanerHandlers) = {
    { EVENT_SWITCH_IN, HandlerScreenCleanerStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerScreenCleanerStart },
};
W2U_MECHANIC(ABILITY, ABIL_SCREEN_CLEANER, ScreenCleanerHandlers);
