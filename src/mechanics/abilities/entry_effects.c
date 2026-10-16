/* Entry abilities (Gen 8, 9; Showdown):
 *   Curious Medicine  on entering, its allies' stat changes are reset (Clear Smog's effect, "X's stat changes were
 *                     removed!" per ally, inside the popup; nothing if none had changes)
 *   Costar            on entering, it copies an ally's stat changes (Psych Up's effect, "X copied Y's stat
 *                     changes!"); nothing without an ally on the field
 *   Supersweet Syrup  on its first entry in a battle, its foes' evasion drops by 1 ("A supersweet aroma is wafting
 *                     from the syrup covering X!" and the drops; Clear Body and the like apply)
 * "First entry in a battle" is this module's state, fresh every battle (docs/engine-interface.md). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MSG_SET_STATS_REMOVED 195       /* bank 18: "{0}'s stat changes were removed!" (Clear Smog's) */
#define MSG_SET_COPIED_STATS 1047       /* bank 18: "{0} copied {1}'s stat changes!" (Psych Up's) */
#define ENTRY_NO_MON 0xFF

static b32 sSupersweetSyrupUsed[BATTLE_MAX_MON_ID];

static b32 EntryHasStatChanges(BattleMon *mon)
{
    u32 stat;

    for (stat = STATSTAGE_ATTACK; stat <= STATSTAGE_EVASION; ++stat) {
        if (GetBattleMonStat(mon, stat) != STATSTAGE_NEUTRAL) {
            return 1;
        }
    }
    return 0;
}

static void HandlerCuriousMedicineStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerResetStatStageParam *param;
    u8 ids[6], id;
    u32 count = 0, i;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    for (id = 0; id < BATTLE_MAX_MON_ID; ++id) {
        if (W2U_OnFieldAlive(flow, id) && id != monId && count < 6 && W2U_IsAlly(monId, id)
            && EntryHasStatChanges(GetBattleMon(flow, id))) {
            ids[count++] = id;
        }
    }
    if (!count) {
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    param = (BattleHandlerResetStatStageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_RESET_STAT_STAGES, monId);
    param->count = (u8)count;
    for (i = 0; i < count; ++i) {
        param->monIndices[i] = ids[i];
    }
    BattleHandler_PopWork(flow, param);
    for (i = 0; i < count; ++i) {
        BattleHandlerMessageParam *message =
            (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
        BattleHandler_StrSetup(&message->string, HANDLER_STR_SET, MSG_SET_STATS_REMOVED);
        BattleHandler_AddArg(&message->string, ids[i]);
        BattleHandler_PopWork(flow, message);
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerCostarStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerSetStatStageParam *param;
    BattleHandlerMessageParam *message;
    BattleMon *source;
    u8 ally = ENTRY_NO_MON, id;
    u32 i;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    for (id = 0; id < BATTLE_MAX_MON_ID; ++id) {
        if (W2U_OnFieldAlive(flow, id) && ally == ENTRY_NO_MON && id != monId && W2U_IsAlly(monId, id)) {
            ally = id;
        }
    }
    if (ally == ENTRY_NO_MON) {
        return;
    }
    source = GetBattleMon(flow, ally);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    param = (BattleHandlerSetStatStageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_SET_STAT_STAGES, monId);
    param->monIndex = monId;
    for (i = 0; i < 7; ++i) {
        param->stages[i] = (u8)GetBattleMonStat(source, STATSTAGE_ATTACK + i);
    }
    BattleHandler_PopWork(flow, param);
    message = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
    BattleHandler_StrSetup(&message->string, HANDLER_STR_SET, MSG_SET_COPIED_STATS);
    BattleHandler_AddArg(&message->string, monId);
    BattleHandler_AddArg(&message->string, ally);
    BattleHandler_PopWork(flow, message);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerSupersweetSyrupStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 id;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID || sSupersweetSyrupUsed[monId]) {
        return;
    }
    sSupersweetSyrupUsed[monId] = 1;
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    W2U_Message(flow, monId, BTLMSG_SET_SUPERSWEET_SYRUP);
    for (id = 0; id < BATTLE_MAX_MON_ID; ++id) {
        if (W2U_OnFieldAlive(flow, id) && !W2U_IsAlly(monId, id)) {
            W2U_ChangeStatStage(flow, monId, id, STATSTAGE_EVASION, -1, 0);
        }
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

W2U_HANDLER_TABLE(CuriousMedicineHandlers) = {
    { EVENT_SWITCH_IN, HandlerCuriousMedicineStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerCuriousMedicineStart },
};
W2U_MECHANIC(ABILITY, ABIL_CURIOUS_MEDICINE, CuriousMedicineHandlers);

W2U_HANDLER_TABLE(CostarHandlers) = {
    { EVENT_SWITCH_IN, HandlerCostarStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerCostarStart },
};
W2U_MECHANIC(ABILITY, ABIL_COSTAR, CostarHandlers);

W2U_HANDLER_TABLE(SupersweetSyrupHandlers) = {
    { EVENT_SWITCH_IN, HandlerSupersweetSyrupStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerSupersweetSyrupStart },
};
W2U_MECHANIC(ABILITY, ABIL_SUPERSWEET_SYRUP, SupersweetSyrupHandlers);
