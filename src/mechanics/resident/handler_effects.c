/* Ripen, Cud Chew, Opportunist, consumed items: around the handler-effect dispatcher's commands (BattleHandler_Execute)
 * and ServerControl_ChangeHeldItem. A held item's effects run inside its UseHeldItem / ForceUseItem, so a "this Ripen
 * holder is eating a Berry" flag around that call sees the Berry's own heal, damage and stat effects. Each function
 * returns the command's result. The mechanics read the state through W2U_MB_CudChew* and W2U_MB_Opportunist*
 * (abilities/effect_abilities.c, move_abilities.c). W2U_ItemConsumed notes a Berry eaten (consume != 2, from
 * BattleHandler_ConsumeItem's 1 + skipDisplay: Belch) and raises EVENT_CONSUME_ITEM (Cheek Pouch, Symbiosis). The state
 * is zero when empty: monIds are kept + 1. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

static u8 sRipenEater;                      /* a Ripen holder eating a Berry + 1 (its UseHeldItem / ForceUseItem runs) */
static u8 sCudChewer;                       /* a Cud Chew holder whose second bite runs + 1 */
static u16 sCudBerry[BATTLE_MAX_MON_ID];
static u8 sCudCounter[BATTLE_MAX_MON_ID];
static u8 sOppPendingCopies[BATTLE_MAX_MON_ID];
static u8 sOppCopying;
static u32 sConsumedBerryFlags;             /* bit per Pokémon ID: ate a Berry this battle (Belch) */

/* The Pokémon a command was pushed for: bits 8-12 of its work's first word (BattleHandlerHeader's monId) */
static u32 CommandMonId(const void *work)
{
    return (*(const u32 *)work >> 8) & 0x1F;
}

/* A held item used: Ripen doubles the Berry's effects meanwhile; Cud Chew notes the Berry, to chew it again */
static u8 UseHeldItemAround(BtlServerFlow *flow, u32 monId, u16 item, BattleHandlerUseHeldItemParam *held,
                            BattleHandlerForceUseItemParam *forced)
{
    BattleMon *mon = monId < BATTLE_MAX_MON_ID ? GetBattleMon(flow, (u8)monId) : 0;
    u8 prev = sRipenEater;
    u8 result;

    if (mon && W2U_IsBerry(item) && W2U_HasActiveAbility(mon, ABIL_RIPEN)) {
        sRipenEater = (u8)(monId + 1);
    }
    result = forced ? BattleHandler_ForceUseItem(flow, forced) : BattleHandler_UseHeldItem(flow, held);
    sRipenEater = prev;
    if (mon && W2U_IsBerry(item) && sCudChewer != monId + 1 && W2U_HasActiveAbility(mon, ABIL_CUD_CHEW)) {
        sCudBerry[monId] = item;
        sCudCounter[monId] = 2;             /* the end of this turn, then the next: chewed again */
    }
    return result;
}

u8 W2U_HandlerUseHeldItem(BtlServerFlow *flow, BattleHandlerUseHeldItemParam *param)
{
    u32 monId = CommandMonId(param);
    BattleMon *mon = monId < BATTLE_MAX_MON_ID ? GetBattleMon(flow, (u8)monId) : 0;

    return UseHeldItemAround(flow, monId, mon ? (u16)GetBattleMonHeldItem(mon) : 0, param, 0);
}

u8 W2U_HandlerForceUseItem(BtlServerFlow *flow, BattleHandlerForceUseItemParam *param)
{
    u8 result = UseHeldItemAround(flow, param->monIndex, param->item, 0, param);

    sCudChewer = 0;
    return result;
}

/* Sitrus, Oran... for the Ripen holder */
u8 W2U_HandlerRecoverHP(BtlServerFlow *flow, BattleHandlerRecoverHPParam *param, u16 itemId)
{
    if (sRipenEater && param->targetIndex == sRipenEater - 1) {
        param->amount = (u16)(param->amount * 2);
    }
    return BattleHandler_RecoverHP(flow, param, itemId);
}

/* Jaboca / Rowap: to the attacker, from the Ripen holder */
u8 W2U_HandlerDamage(BtlServerFlow *flow, BattleHandlerDamageParam *param)
{
    if (sRipenEater && param->targetIndex != sRipenEater - 1) {
        param->amount = (u16)(param->amount * 2);
    }
    return BattleHandler_Damage(flow, param);
}

/* Liechi, Salac... for the Ripen holder; an Opportunist copy runs with the copying flag set */
u8 W2U_HandlerStatChange(BtlServerFlow *flow, BattleHandlerStatChangeParam *param, u16 context)
{
    b32 single = param->change > 0 && param->count == 1 && param->monIds[0] < BATTLE_MAX_MON_ID;
    b32 copy = single && sOppPendingCopies[param->monIds[0]] > 0;
    u8 prev = sOppCopying;
    u8 result;

    if (copy) {
        --sOppPendingCopies[param->monIds[0]];
    }
    if (single && sRipenEater && param->monIds[0] == sRipenEater - 1) {
        param->change = (s8)(param->change * 2 > 6 ? 6 : param->change * 2);
    }
    if (copy) {
        sOppCopying = 1;
    }
    result = BattleHandler_StatChange(flow, param, context);
    sOppCopying = prev;
    return result;
}

/* At each turn end: counts down, and returns the Berry to chew again at the end of the next turn (0: nothing yet);
 * the second bite is not noted again */
u16 W2U_MB_CudChewTurnEnd(u32 monId)
{
    u16 item;

    if (monId >= BATTLE_MAX_MON_ID || !sCudBerry[monId] || --sCudCounter[monId]) {
        return 0;
    }
    item = sCudBerry[monId];
    sCudBerry[monId] = 0;
    sCudChewer = (u8)(monId + 1);           /* cleared when the bite has run (ForceUseItem) */
    return item;
}

void W2U_MB_CudChewForget(u32 monId)
{
    if (monId < BATTLE_MAX_MON_ID) {
        sCudBerry[monId] = 0;
    }
}

void W2U_MB_OpportunistCopyQueued(u32 monId)
{
    if (monId < BATTLE_MAX_MON_ID) {
        ++sOppPendingCopies[monId];
    }
}

u8 W2U_MB_OpportunistCopying(void)
{
    return sOppCopying;
}

void W2U_MoveState_SetConsumedBerryFlag(u32 monId)
{
    if (monId < BATTLE_MAX_MON_ID) {
        sConsumedBerryFlags |= 1u << monId;
    }
}

b32 W2U_MoveState_HasConsumedBerryFlag(u32 monId)
{
    return monId < BATTLE_MAX_MON_ID && (sConsumedBerryFlags & (1u << monId));
}

void W2U_ItemConsumed(BtlServerFlow *flow, u32 monId, u16 item, b32 consume)
{
    u32 level;

    if (!flow || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    if (consume != 2 && W2U_IsBerry(item)) {
        W2U_MoveState_SetConsumedBerryFlag(monId);
    }
    level = W2U_PushHandlerState(flow);
    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetConstValue(VAR_MON_ID, -1);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, -1);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, -1);
    BattleEventVar_SetConstValue(NEW_VAR_MON_ID, (s32)monId);
    BattleEventVar_SetConstValue(VAR_ITEM, item);
    BattleEvent_CallHandlers(flow, EVENT_CONSUME_ITEM);
    BattleEventVar_Pop(__LINE__);
    W2U_PopHandlerState(flow, level);
}

void W2U_Resident_ResetHandlerEffects(void)
{
    u32 i;

    sRipenEater = sCudChewer = sOppCopying = 0;
    sConsumedBerryFlags = 0;
    for (i = 0; i < BATTLE_MAX_MON_ID; ++i) {
        sCudBerry[i] = 0;
        sCudCounter[i] = 0;
        sOppPendingCopies[i] = 0;
    }
}
