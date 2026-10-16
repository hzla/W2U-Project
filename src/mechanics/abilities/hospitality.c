/* Hospitality (Gen 9): on entering, or on gaining the ability, it restores 1/4 of its allies' max HP (Showdown:
 * adjacent allies; full-HP allies are skipped, no popup when nobody heals). The allies come from Plus and Minus'
 * lookup (the holder's whole side: in triples that includes the far ally); the heal is CommonTypeRecoverHP's effect
 * with the holder's popup and "X's HP was restored." */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MSG_SET_HP_RESTORED 0x183       /* bank 18: "{0}'s HP was restored." */

static void HandlerHospitalityStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 ids[8];
    u32 position, count, i;
    b32 popup = 0;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    position = Handler_PokeIDToPokePos(flow, monId);
    if (position == BATTLE_POS_NONE) {
        return;
    }
    count = HandlerGetAlivePartyCount(flow, (u16)(BATTLE_RANGE_FULL_FRIENDS << 8 | position), ids);
    for (i = 0; i < count; ++i) {
        u8 ally = ids[i];
        BattleMon *mon;
        BattleHandlerRecoverHPParam *param;
        if (ally == monId) {
            continue;
        }
        mon = GetBattleMon(flow, ally);
        if (IsFainted(mon) || IsMonFullHP(mon)) {
            continue;
        }
        if (!popup) {
            BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
            popup = 1;
        }
        param = (BattleHandlerRecoverHPParam *)BattleHandler_PushWork(flow, HANDLER_CMD_RECOVER_HP, monId);
        param->amount = (u16)DivideMaxHPZeroCheck(mon, 4);
        param->targetIndex = ally;
        BattleHandler_StrSetup(&param->string, HANDLER_STR_SET, MSG_SET_HP_RESTORED);
        BattleHandler_AddArg(&param->string, ally);
        BattleHandler_PopWork(flow, param);
    }
    if (popup) {
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    }
}

W2U_HANDLER_TABLE(HospitalityHandlers) = {
    { EVENT_SWITCH_IN, HandlerHospitalityStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerHospitalityStart },
};
W2U_MECHANIC(ABILITY, ABIL_HOSPITALITY, HospitalityHandlers);
