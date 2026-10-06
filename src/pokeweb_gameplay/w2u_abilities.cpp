#include "w2u_abilities.h"
#include "w2u_battle_module_api.h"
#include "w2u_battle_module_loader.h"
#include "w2u_field_effects.h"
#include "w2u_moves.h"
#include "w2u_platform.h"
#include "w2u_strong_weather.h"
#if !defined(W2U_TARGET_B2)
#include "megab2w2/mb_ability_tables.h"   // ported MegaB2W2 ability tables (White 2 only)
#endif

#define W2U_ABILITY_POWER_RATIO_1_2X 4915
#define W2U_ABILITY_POWER_RATIO_1_3_DECIMAL 5325
#define W2U_ABILITY_POWER_RATIO_1_3X 5461
#define W2U_ABILITY_POWER_RATIO_1_5X 6144
#define W2U_ABILITY_POWER_RATIO_2X 8192
#define W2U_ABILITY_POWER_RATIO_3_4X 3072
#define W2U_ABILITY_RATIO_HALF 2048
#define W2U_ABILITY_MEGA_LAUNCHER_HEAL_RATIO 3072
#define W2U_ABILITY_EFFECTIVENESS_2X 4u
#define W2U_BULLETPROOF_MSG_NARC 2u
#define W2U_BULLETPROOF_MSG_ID 210u
#define W2U_MAGICIAN_MSG_NARC 2u
#define W2U_MAGICIAN_MSG_ID 1057u
#define W2U_CHEEK_POUCH_MSG_NARC 2u
#define W2U_CHEEK_POUCH_MSG_ID 387u
#define W2U_CHEEK_POUCH_RECOVER_DENOMINATOR 3u
#define W2U_INNARDS_OUT_MSG_NARC 2u
#define W2U_INNARDS_OUT_MSG_ID 402u
#define W2U_RECEIVER_MSG_NARC 2u
#define W2U_RECEIVER_MSG_ID 619u
#define W2U_WATER_BUBBLE_FAIL_MSG_NARC 1u
#define W2U_WATER_BUBBLE_FAIL_MSG_ID 68u
#define W2U_NULL_BATTLE_POS 6u
#define W2U_ITSTAT_USE_PARAM 2u
#define W2U_BATTLE_BOND_ASH_FORM 2u
#define W2U_FORCE_FAIL_MESSAGE 2
#define W2U_SERVERFLOW_SET_TARGET_ORIGINAL_OFFSET 0x850u
#define W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET 0x38u
#define W2U_ACTION_ORDER_PRIO_OFFSET 7
#define W2U_ACTION_ORDER_SPECIAL_PRIO_OFFSET 1
#define W2U_BATTLE_MON_CONDITION_COUNT 36u
#define W2U_CONDITION_STATUS_MASK 0x7u
#define W2U_MINIOR_METEOR_FORM_COUNT 7u
#define W2U_MINIOR_CORE_FORM_START 7u
#define W2U_MINIOR_FORM_COUNT 14u
#define W2U_WISHIWASHI_SOLO_FORM 0u
#define W2U_WISHIWASHI_SCHOOL_FORM 1u
#define W2U_SCHOOLING_MIN_LEVEL 20u
#define W2U_ZYGARDE_50_FORM 0u
#define W2U_ZYGARDE_10_FORM 1u
#define W2U_ZYGARDE_COMPLETE_FORM 2u
#define W2U_VANILLA_ABILITY_EVENT_TABLE ((AbilityEventAddTable*)W2U_ADDR_ABILITY_EVENT_TABLE)
#define W2U_VANILLA_ABILITY_EVENT_TABLE_COUNT 158u

extern "C" void THUMB_BRANCH_ServerEvent_GetMoveParam(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    BattleMon* battleMon,
    MoveParam* moveParam);

extern "C" void W2U_Mega_ProcessActionOrderBeforeMoves(ServerFlow* serverFlow, u32 startActionIdx);

static ConditionData W2U_GetStoredMoveCondition(BattleMon* battleMon, CONDITION condition)
{
    if (!battleMon || condition >= W2U_BATTLE_MON_CONDITION_COUNT) {
        return 0;
    }

    const u8* slot = &battleMon->conditions[condition * sizeof(ConditionData)];
    return (ConditionData)slot[0] |
        ((ConditionData)slot[1] << 8) |
        ((ConditionData)slot[2] << 16) |
        ((ConditionData)slot[3] << 24);
}

static void W2U_SetStoredMoveCondition(
    BattleMon* battleMon,
    CONDITION condition,
    ConditionData value)
{
    if (!battleMon || condition >= W2U_BATTLE_MON_CONDITION_COUNT) {
        return;
    }

    u8* slot = &battleMon->conditions[condition * sizeof(ConditionData)];
    slot[0] = (u8)value;
    slot[1] = (u8)(value >> 8);
    slot[2] = (u8)(value >> 16);
    slot[3] = (u8)(value >> 24);
}

static bool W2U_BattleMonHasMoveCondition(BattleMon* battleMon, CONDITION condition)
{
    return (W2U_GetStoredMoveCondition(battleMon, condition) & W2U_CONDITION_STATUS_MASK) != 0;
}

extern "C" u32 THUMB_BRANCH_SAFESTACK_ServerControl_AddConditionCheckFail(
    ServerFlow* serverFlow,
    BattleMon* defendingMon,
    BattleMon* attackingMon,
    CONDITION condition,
    ConditionData condData,
    u8 overrideMode,
    u32 almost)
{
    u32 failStatus = AddConditionCheckFailOverwrite(
        serverFlow,
        defendingMon,
        condition,
        condData,
        overrideMode);

    if (condition == CONDITION_POISON &&
        failStatus == 2 &&
        attackingMon &&
        BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_CORROSION) {
        failStatus = 0;
    }

    if ((condition < CONDITION_CONFUSION || condition == CONDITION_YAWN) &&
        defendingMon &&
        defendingMon->currentAbility == ABIL_COMATOSE) {
        failStatus = 3;
    }

    if (failStatus) {
        if (almost) {
            AddConditionCheckFailStandard(serverFlow, defendingMon, failStatus, condition);
        }
        return 1;
    }

    u32 HEID = HEManager_PushState(&serverFlow->HEManager);
    u32 failFlag = ServerEvent_MoveConditionCheckFail(
        serverFlow,
        attackingMon,
        defendingMon,
        condition);
    if ((failFlag && almost) || failFlag == W2U_FORCE_FAIL_MESSAGE) {
        ServerEvent_AddConditionFailed(serverFlow, defendingMon, attackingMon, condition);
        serverFlow->field_78A |= 0x10u;
    }
    HEManager_PopState(&serverFlow->HEManager, HEID);
    return failFlag;
}

extern "C" b32 THUMB_BRANCH_BattleMon_CheckIfMoveCondition(BattleMon* battleMon, CONDITION condition)
{
    if (battleMon &&
        condition == CONDITION_SLEEP &&
        BattleMon_GetValue(battleMon, VALUE_EFFECTIVE_ABILITY) == ABIL_COMATOSE) {
        return 1;
    }

    return W2U_BattleMonHasMoveCondition(battleMon, condition);
}

extern "C" void THUMB_BRANCH_HandlerHex(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;

    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* defendingMon =
        Handler_GetBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (!defendingMon) {
        return;
    }

    if (BattleMon_CheckIfMoveCondition(defendingMon, CONDITION_PARALYSIS) ||
        BattleMon_CheckIfMoveCondition(defendingMon, CONDITION_SLEEP) ||
        BattleMon_CheckIfMoveCondition(defendingMon, CONDITION_FREEZE) ||
        BattleMon_CheckIfMoveCondition(defendingMon, CONDITION_BURN) ||
        BattleMon_CheckIfMoveCondition(defendingMon, CONDITION_POISON) ||
        BattleMon_CheckIfMoveCondition(defendingMon, CONDITION_PARALYSIS)) {
        u32 power = (u32)BattleEventVar_GetValue(VAR_MOVE_POWER);
        BattleEventVar_RewriteValue(VAR_MOVE_POWER, power * 2);
    }
}

extern "C" void THUMB_BRANCH_CommonStatusReaction(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    CONDITION condition)
{
    BattleMon* currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
    if (currentMon && currentMon->currentAbility == ABIL_COMATOSE) {
        return;
    }

    CONDITION conditionCopy = condition;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        (!BattleEventVar_GetValueIfExist(VAR_ITEM_REACTION, &conditionCopy) ||
            conditionCopy == CONDITION_FREEZE ||
            conditionCopy == CONDITION_NONE) &&
        CommonConditionCodeMatch(serverFlow, pokemonSlot, condition)) {
        ItemEvent_PushRun(item, serverFlow, pokemonSlot);
    }
}

typedef ActionOrderWork W2UExtraActionOrderArray[
    W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork)];
typedef u8 W2UExtraActionKindArray[
    W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork)];
typedef u8 W2USendLastSlotArray[
    W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork)];
typedef u32 W2UBattleSlotWordArray[BATTLE_MAX_SLOTS];

enum W2UExtraActionKind : u8 {
    W2U_EXTRA_ACTION_NONE = 0,
    W2U_EXTRA_ACTION_DANCER = 1,
    W2U_EXTRA_ACTION_INSTRUCT = 2,
};

#if !defined(W2U_BATTLE_CHILD)
struct W2UAbilitySharedState {
    W2UExtraActionOrderArray extraActionOrder;
    W2UExtraActionKindArray extraActionKind;
    u8 extraActionFlag;
    u8 interruptActionFlag;
    u8 emergencyExitEndTurnSwitchFlag;
    u8 reserved;
    u32 emergencyExitPendingSlots;
    W2UBattleSlotWordArray emergencyExitSubstituteDamage;
    W2UBattleSlotWordArray emergencyExitSimpleBeforeHP;
    u32 stakeoutInitialSlots;
    u32 extraActionNaturalResetSlots;
    W2USendLastSlotArray sendLastSlots;
    bool parentalBondActive;
    u8 parentalBondPowerHit;
};
#endif

#if defined(W2U_BATTLE_CHILD)
extern "C" W2UExtraActionOrderArray* W2U_AbilityState_ExtraActionOrderStorage();
extern "C" W2UExtraActionKindArray* W2U_AbilityState_ExtraActionKindStorage();
extern "C" u8* W2U_AbilityState_ExtraActionFlagStorage();
extern "C" u8* W2U_AbilityState_InterruptActionFlagStorage();
extern "C" u8* W2U_AbilityState_EmergencyExitEndTurnStorage();
extern "C" u32* W2U_AbilityState_EmergencyExitPendingStorage();
extern "C" W2UBattleSlotWordArray* W2U_AbilityState_SubstituteDamageStorage();
extern "C" W2UBattleSlotWordArray* W2U_AbilityState_SimpleBeforeHPStorage();
extern "C" u32* W2U_AbilityState_StakeoutInitialSlotsStorage();
extern "C" u32* W2U_AbilityState_ExtraActionNaturalResetStorage();
extern "C" W2USendLastSlotArray* W2U_AbilityState_SendLastSlotsStorage();
extern "C" bool* W2U_AbilityState_ParentalBondActiveStorage();
extern "C" u8* W2U_AbilityState_ParentalBondPowerHitStorage();
#else
static W2UAbilitySharedState sAbilitySharedState = {
    {},
    {},
    0,
    0,
    0,
    0,
    0,
    {},
    {},
    0,
    0,
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    false,
    0,
};

#define W2U_ABILITY_STATE_STORAGE(type, name, field) \
    extern "C" type* name() { return &sAbilitySharedState.field; }

W2U_ABILITY_STATE_STORAGE(
    W2UExtraActionOrderArray, W2U_AbilityState_ExtraActionOrderStorage, extraActionOrder)
W2U_ABILITY_STATE_STORAGE(
    W2UExtraActionKindArray, W2U_AbilityState_ExtraActionKindStorage, extraActionKind)
W2U_ABILITY_STATE_STORAGE(
    u8, W2U_AbilityState_ExtraActionFlagStorage, extraActionFlag)
W2U_ABILITY_STATE_STORAGE(
    u8, W2U_AbilityState_InterruptActionFlagStorage, interruptActionFlag)
W2U_ABILITY_STATE_STORAGE(
    u8, W2U_AbilityState_EmergencyExitEndTurnStorage, emergencyExitEndTurnSwitchFlag)
W2U_ABILITY_STATE_STORAGE(
    u32, W2U_AbilityState_EmergencyExitPendingStorage, emergencyExitPendingSlots)
W2U_ABILITY_STATE_STORAGE(
    W2UBattleSlotWordArray, W2U_AbilityState_SubstituteDamageStorage, emergencyExitSubstituteDamage)
W2U_ABILITY_STATE_STORAGE(
    W2UBattleSlotWordArray, W2U_AbilityState_SimpleBeforeHPStorage, emergencyExitSimpleBeforeHP)
W2U_ABILITY_STATE_STORAGE(
    u32, W2U_AbilityState_StakeoutInitialSlotsStorage, stakeoutInitialSlots)
W2U_ABILITY_STATE_STORAGE(
    u32, W2U_AbilityState_ExtraActionNaturalResetStorage, extraActionNaturalResetSlots)
W2U_ABILITY_STATE_STORAGE(
    W2USendLastSlotArray, W2U_AbilityState_SendLastSlotsStorage, sendLastSlots)
W2U_ABILITY_STATE_STORAGE(
    bool, W2U_AbilityState_ParentalBondActiveStorage, parentalBondActive)
W2U_ABILITY_STATE_STORAGE(
    u8, W2U_AbilityState_ParentalBondPowerHitStorage, parentalBondPowerHit)

#undef W2U_ABILITY_STATE_STORAGE
#endif

#define sExtraActionOrder (*W2U_AbilityState_ExtraActionOrderStorage())
#define sExtraActionKind (*W2U_AbilityState_ExtraActionKindStorage())
#define sExtraActionFlag (*W2U_AbilityState_ExtraActionFlagStorage())
#define sInterruptActionFlag (*W2U_AbilityState_InterruptActionFlagStorage())
#define sEmergencyExitEndTurnSwitchFlag (*W2U_AbilityState_EmergencyExitEndTurnStorage())
#define sEmergencyExitPendingSlots (*W2U_AbilityState_EmergencyExitPendingStorage())
#define sEmergencyExitSubstituteDamage (*W2U_AbilityState_SubstituteDamageStorage())
#define sEmergencyExitSimpleBeforeHP (*W2U_AbilityState_SimpleBeforeHPStorage())
#define sStakeoutInitialSlots (*W2U_AbilityState_StakeoutInitialSlotsStorage())
#define sExtraActionNaturalResetSlots (*W2U_AbilityState_ExtraActionNaturalResetStorage())
#define sSendLastSlots (*W2U_AbilityState_SendLastSlotsStorage())
#define sParentalBondActive (*W2U_AbilityState_ParentalBondActiveStorage())
#define sParentalBondPowerHit (*W2U_AbilityState_ParentalBondPowerHitStorage())

static int W2U_DecodeActionPriority(const ActionOrderWork* actionOrder)
{
    int priority =
        (int)((actionOrder->speed >> 16) & 0x3Fu) - W2U_ACTION_ORDER_PRIO_OFFSET;
    int specialPriority =
        (int)((actionOrder->speed >> 13) & 0x7u) - W2U_ACTION_ORDER_SPECIAL_PRIO_OFFSET;
    return priority + specialPriority;
}

extern "C" int W2U_GetQueuedMovePriority(ServerFlow* serverFlow, BattleMon* attackingMon)
{
    if (!serverFlow || !attackingMon) {
        return 0;
    }

    if (sExtraActionFlag &&
        sExtraActionOrder[0].battleMon == attackingMon &&
        sExtraActionKind[0] != W2U_EXTRA_ACTION_NONE) {
        return W2U_DecodeActionPriority(&sExtraActionOrder[0]);
    }

    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(serverFlow->actionOrderWork); ++idx) {
        ActionOrderWork* actionOrder = &serverFlow->actionOrderWork[idx];
        if (actionOrder->battleMon == attackingMon) {
            return W2U_DecodeActionPriority(actionOrder);
        }
    }

    return (int)BattleEventVar_GetValue(VAR_MOVE_PRIORITY);
}

extern "C" void W2U_AbilityState_ResetBattleState()
{
    sEmergencyExitEndTurnSwitchFlag = 0;
    sEmergencyExitPendingSlots = 0;
    sStakeoutInitialSlots = 0;
    sExtraActionNaturalResetSlots = 0;
    for (u32 pokemonSlot = 0; pokemonSlot < BATTLE_MAX_SLOTS; ++pokemonSlot) {
        sEmergencyExitSubstituteDamage[pokemonSlot] = 0;
        sEmergencyExitSimpleBeforeHP[pokemonSlot] = 0;
    }
}

extern "C" void W2U_AbilityState_RecordInitialMon(
    ServerFlow* serverFlow,
    u32 clientID,
    u32 partySlot)
{
    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    BattleParty* battleParty = PokeCon_GetBattleParty(serverFlow->pokeCon, clientID);
    BattleMon* battleMon = battleParty
        ? BattleParty_GetPartyMember(battleParty, partySlot)
        : 0;
    if (battleMon && battleMon->battleSlot < BATTLE_MAX_SLOTS) {
        sStakeoutInitialSlots |= 1u << battleMon->battleSlot;
    }
}

bool W2U_SwitchedInThisTurn(ServerFlow* serverFlow, BattleMon* battleMon)
{
    if (!serverFlow || !battleMon || battleMon->battleSlot >= BATTLE_MAX_SLOTS) {
        return false;
    }

    if (serverFlow->turnCount == 0 &&
        (sStakeoutInitialSlots & (1u << battleMon->battleSlot))) {
        return false;
    }
    return battleMon->turnCount == 0;
}

static void W2U_ServerEvent_SimpleDamageReaction(
    ServerFlow* serverFlow,
    BattleMon* battleMon,
    u32 damage,
    u32 beforeHP)
{
    if (!serverFlow || !battleMon) {
        return;
    }

    u32 pokemonSlot = BattleMon_GetID(battleMon);
    if (pokemonSlot >= BATTLE_MAX_SLOTS) {
        return;
    }

    sEmergencyExitSimpleBeforeHP[pokemonSlot] = beforeHP;
    u32 HEID = HEManager_PushState(&serverFlow->HEManager);
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_MON_ID, -1);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, -1);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, -1);
    BattleEventVar_SetConstValue(NEW_VAR_MON_ID, pokemonSlot);
    BattleEventVar_SetConstValue(VAR_DAMAGE, damage);
    BattleEvent_CallHandlers(serverFlow, EVENT_SIMPLE_DAMAGE_REACTION);
    BattleEventVar_Pop();
    HEManager_PopState(&serverFlow->HEManager, HEID);
    sEmergencyExitSimpleBeforeHP[pokemonSlot] = 0;
}

extern "C" b32 THUMB_BRANCH_ServerControl_SimpleDamageCore(
    ServerFlow* serverFlow,
    BattleMon* battleMon,
    int damage,
    HandlerParam_StrParams* str)
{
    int damageToDeal = -damage;
    if (!damageToDeal) {
        return 0;
    }

    u32 beforeHP = battleMon ? battleMon->currentHP : 0;
    ServerDisplay_SimpleHP(serverFlow, battleMon, damageToDeal, 1);
    TurnFlag_Set(battleMon, TURNFLAG_DAMAGED);
    if (str) {
        BattleHandler_SetString(serverFlow, str);
        BattleHandler_StrClear(str);
    }

    ServerControl_CheckItemReaction(serverFlow, battleMon, 1);
    W2U_ServerEvent_SimpleDamageReaction(serverFlow, battleMon, (u32)damage, beforeHP);
    if (ServerControl_CheckFainted(serverFlow, battleMon)) {
        ServerControl_CheckMatchup(serverFlow);
    }

    return 1;
}

extern "C" b32 THUMB_BRANCH_BattleMon_AddSubstituteDamage(BattleMon* battleMon, u32* damage)
{
    if (!battleMon || !damage) {
        return 0;
    }

    b32 substituteBroken = 0;
    if (battleMon->substituteHP > *damage) {
        battleMon->substituteHP = (u16)(battleMon->substituteHP - *damage);
    } else {
        *damage = battleMon->substituteHP;
        battleMon->substituteHP = 0;
        substituteBroken = 1;
    }

    if (battleMon->battleSlot < BATTLE_MAX_SLOTS) {
        sEmergencyExitSubstituteDamage[battleMon->battleSlot] += *damage;
    }
    return substituteBroken;
}

static void W2U_ClearActionOrderWork(ActionOrderWork* actionOrder)
{
    if (!actionOrder) {
        return;
    }

    actionOrder->battleMon = nullptr;
    actionOrder->action.baDefault.cmd = 0;
    actionOrder->action.baDefault.param = 0;
    actionOrder->speed = 0;
    actionOrder->partyID = 0;
    actionOrder->done = 0;
    actionOrder->field_E = 0;
    actionOrder->field_F = 0;
}

static void W2U_CopyActionOrderWork(ActionOrderWork* dst, const ActionOrderWork* src)
{
    if (!dst || !src) {
        return;
    }

    dst->battleMon = src->battleMon;
    dst->action = src->action;
    dst->speed = src->speed;
    dst->partyID = src->partyID;
    dst->done = src->done;
    dst->field_E = src->field_E;
    dst->field_F = src->field_F;
}

extern "C" void ShiftExtraActionOrders()
{
    for (u32 i = W2U_ARRAY_COUNT(sExtraActionOrder) - 1; i > 0; --i) {
        W2U_CopyActionOrderWork(&sExtraActionOrder[i], &sExtraActionOrder[i - 1]);
        sExtraActionKind[i] = sExtraActionKind[i - 1];
    }
    W2U_ClearActionOrderWork(&sExtraActionOrder[0]);
    sExtraActionKind[0] = W2U_EXTRA_ACTION_NONE;
}

static void W2U_AdvanceExtraActionOrders()
{
    for (u32 i = 0; i + 1 < W2U_ARRAY_COUNT(sExtraActionOrder); ++i) {
        W2U_CopyActionOrderWork(&sExtraActionOrder[i], &sExtraActionOrder[i + 1]);
        sExtraActionKind[i] = sExtraActionKind[i + 1];
    }
    W2U_ClearActionOrderWork(&sExtraActionOrder[W2U_ARRAY_COUNT(sExtraActionOrder) - 1]);
    sExtraActionKind[W2U_ARRAY_COUNT(sExtraActionKind) - 1] = W2U_EXTRA_ACTION_NONE;
}

extern "C" ActionOrderWork* GetExtraActionOrder(u32 actionIdx)
{
    if (actionIdx >= W2U_ARRAY_COUNT(sExtraActionOrder)) {
        return nullptr;
    }
    return &sExtraActionOrder[actionIdx];
}

extern "C" b32 CheckExtraActionFlag()
{
    return sExtraActionFlag;
}

static bool W2U_IsValidExtraAction(
    ActionOrderWork* actionOrder,
    W2UExtraActionKind kind)
{
    if (!actionOrder ||
        !actionOrder->battleMon ||
        BattleMon_IsFainted(actionOrder->battleMon) ||
        BattleAction_GetAction(&actionOrder->action) != 1) {
        return false;
    }

    MOVE_ID moveID = (MOVE_ID)actionOrder->action.baFight.moveID;
    if (moveID == MOVE_NONE) {
        return false;
    }

    if (kind == W2U_EXTRA_ACTION_DANCER) {
        return getMoveFlag(moveID, MOVE_FLAG_INDEX_DANCE) != 0;
    }
    return kind == W2U_EXTRA_ACTION_INSTRUCT;
}

static bool W2U_IsActiveExtraActionKind(W2UExtraActionKind kind)
{
    return sExtraActionFlag && sExtraActionKind[0] == kind;
}

static bool W2U_IsQueuedExtraFight(BattleMon* battleMon, MOVE_ID moveID)
{
    if (!battleMon || moveID == MOVE_NONE) {
        return false;
    }

    for (u32 i = 0; i < W2U_ARRAY_COUNT(sExtraActionOrder); ++i) {
        ActionOrderWork* actionOrder = &sExtraActionOrder[i];
        if (actionOrder->battleMon == battleMon &&
            BattleAction_GetAction(&actionOrder->action) == 1 &&
            (MOVE_ID)actionOrder->action.baFight.moveID == moveID) {
            return true;
        }
    }

    return false;
}

static u8 W2U_GetActionOrderCount(ServerFlow* serverFlow)
{
    if (!serverFlow) {
        return 0;
    }

    u8 count = serverFlow->numActOrder;
    u8 maxCount = (u8)W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork);
    return count > maxCount ? maxCount : count;
}

static BattleMon* W2U_GetActiveBattleMon(ServerFlow* serverFlow, u32 pokemonSlot)
{
    if (!serverFlow || pokemonSlot >= BATTLE_MAX_SLOTS ||
        Handler_PokeIDToPokePos(serverFlow, pokemonSlot) == W2U_NULL_BATTLE_POS) {
        return nullptr;
    }
    return Handler_GetBattleMon(serverFlow, pokemonSlot);
}

extern "C" bool W2U_ExtraAction_GetLastMove(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    MOVE_ID* moveID,
    u32* targetPos)
{
    BattleMon* battleMon = W2U_GetActiveBattleMon(serverFlow, pokemonSlot);
    if (!battleMon || !moveID || !targetPos || battleMon->previousMoveID == MOVE_NONE) {
        return false;
    }

    // Instruct repeats the move that actually executed, rather than the
    // originally selected move.  These differ for called or replaced moves.
    *moveID = (MOVE_ID)battleMon->previousMoveID;
    *targetPos = battleMon->prevTargetPos;
    return true;
}

extern "C" MOVE_ID W2U_ExtraAction_GetPendingMove(
    ServerFlow* serverFlow,
    u32 pokemonSlot)
{
    BattleMon* battleMon = W2U_GetActiveBattleMon(serverFlow, pokemonSlot);
    if (!battleMon) {
        return MOVE_NONE;
    }

    const u8 actionCount = W2U_GetActionOrderCount(serverFlow);
    for (u32 idx = 0; idx < actionCount; ++idx) {
        ActionOrderWork* actionOrder = &serverFlow->actionOrderWork[idx];
        if (actionOrder->battleMon == battleMon && !actionOrder->done &&
            BattleAction_GetAction(&actionOrder->action) == 1) {
            return (MOVE_ID)actionOrder->action.baFight.moveID;
        }
    }
    return MOVE_NONE;
}

extern "C" bool W2U_ExtraAction_HasMoveWithPP(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    MOVE_ID moveID)
{
    BattleMon* battleMon = W2U_GetActiveBattleMon(serverFlow, pokemonSlot);
    if (!battleMon || moveID == MOVE_NONE) {
        return false;
    }

    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(battleMon->moves); ++idx) {
        const MoveCore* move = &battleMon->moves[idx].surface;
        if ((MOVE_ID)move->moveID == moveID) {
            return move->currentPP != 0;
        }
    }
    return false;
}

static u8 W2U_CalculateMoveOrderPriority(
    ServerFlow* serverFlow,
    BattleMon* battleMon,
    MOVE_ID moveID)
{
    int rawPriority = (int)(signed char)PML_MoveGetParam(moveID, MVDATA_PRIORITY);
    int encodedPriority = rawPriority + W2U_ACTION_ORDER_PRIO_OFFSET;

    u32 HEID = HEManager_PushState(&serverFlow->HEManager);
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_MON_ID, battleMon->battleSlot);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, battleMon->battleSlot);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, moveID);
    BattleEventVar_SetValue(VAR_MOVE_PRIORITY, encodedPriority);
    BattleEvent_CallHandlers(serverFlow, EVENT_GET_MOVE_PRIORITY);
    encodedPriority = BattleEventVar_GetValue(VAR_MOVE_PRIORITY);
    BattleEventVar_Pop();
    HEManager_PopState(&serverFlow->HEManager, HEID);

    if (encodedPriority < 0) {
        return 0;
    }
    if (encodedPriority > 0x3F) {
        return 0x3F;
    }
    return (u8)encodedPriority;
}

extern "C" bool W2U_ExtraAction_QueueInstruct(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    MOVE_ID moveID,
    u32 targetPos)
{
    BattleMon* battleMon = W2U_GetActiveBattleMon(serverFlow, pokemonSlot);
    if (!battleMon || BattleMon_IsFainted(battleMon) ||
        !W2U_ExtraAction_HasMoveWithPP(serverFlow, pokemonSlot, moveID) ||
        targetPos > W2U_NULL_BATTLE_POS) {
        return false;
    }

    ActionOrderWork nextExtraAction;
    W2U_ClearActionOrderWork(&nextExtraAction);
    nextExtraAction.battleMon = battleMon;
    nextExtraAction.action.baFight.cmd = 1;
    nextExtraAction.action.baFight.targetPos = targetPos;
    nextExtraAction.action.baFight.moveID = moveID;

    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(serverFlow->actionOrderWork); ++idx) {
        ActionOrderWork* naturalAction = &serverFlow->actionOrderWork[idx];
        if (naturalAction->battleMon == battleMon) {
            nextExtraAction.partyID = naturalAction->partyID;
            nextExtraAction.speed = naturalAction->speed & 0x1FFFu;
            break;
        }
    }

    const u32 movePriority = W2U_CalculateMoveOrderPriority(serverFlow, battleMon, moveID);
    nextExtraAction.speed |= movePriority << 16;
    nextExtraAction.speed |= W2U_ACTION_ORDER_SPECIAL_PRIO_OFFSET << 13;

    ShiftExtraActionOrders();
    W2U_CopyActionOrderWork(&sExtraActionOrder[0], &nextExtraAction);
    sExtraActionKind[0] = W2U_EXTRA_ACTION_INSTRUCT;
    return true;
}

extern "C" void SetExtraActionFlag()
{
    sExtraActionFlag = 1;
}

extern "C" void ResetExtraActionFlag()
{
    sExtraActionFlag = 0;
}

extern "C" u32 CommonGetAllyPos(ServerFlow* serverFlow, u32 battlePos)
{
    BattleStyle battleStyle = BtlSetup_GetBattleStyle(serverFlow->mainModule);
    if (battleStyle != BTL_STYLE_DOUBLE && battleStyle != BTL_STYLE_TRIPLE) {
        return 6;
    }

    u8 isEnemy = (u8)(battlePos & 1u);
    if (isEnemy) {
        battlePos -= 1;
    }

    u32 allyPos = 0;
    if (battleStyle != BTL_STYLE_TRIPLE) {
        allyPos = battlePos == 0 ? 2 : 0;
    } else if (IsCenterInTripleBattle(battlePos)) {
        allyPos = BattleRandom(2) * 4;
    } else {
        allyPos = 2;
    }

    return allyPos + isEnemy;
}

static MOVE_ID W2U_GetBattleEventItemSubID(BattleEventItem* item)
{
    if (!item) {
        return 0;
    }
    return (MOVE_ID)*(u16*)((u8*)item + W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET);
}

static void W2U_ClearExtraActionTurnFlags(BattleMon* battleMon)
{
    Turnflag_Clear(battleMon, TURNFLAG_ACTIONSTART);
    Turnflag_Clear(battleMon, TURNFLAG_ACTIONDONE);
    Turnflag_Clear(battleMon, TURNFLAG_MOVEPROCDONE);
    Turnflag_Clear(battleMon, TURNFLAG_MOVED);
    Turnflag_Clear(battleMon, TURNFLAG_USINGFLING);
}

static bool W2U_HasPendingNaturalAction(ServerFlow* serverFlow, BattleMon* battleMon)
{
    if (!serverFlow || !battleMon) {
        return false;
    }
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(serverFlow->actionOrderWork); ++idx) {
        ActionOrderWork* actionOrder = &serverFlow->actionOrderWork[idx];
        if (actionOrder->battleMon == battleMon && !actionOrder->done) {
            return true;
        }
    }
    return false;
}

struct W2ULastMoveSnapshot {
    u16 previousMove;
    u16 previousMoveID;
    u16 consecutiveMoveCounter;
    u8 previousMoveType;
    u8 previousTargetPos;
};

static u32 W2U_ProcessExtraAction(
    ServerFlow* serverFlow,
    ActionOrderWork* actionOrder,
    W2UExtraActionKind kind)
{
    BattleMon* battleMon = actionOrder->battleMon;
    const u32 pokemonSlot = battleMon->battleSlot;
    const bool hasPendingNaturalAction = W2U_HasPendingNaturalAction(serverFlow, battleMon);

    ConditionData savedEncore = 0;
    W2ULastMoveSnapshot lastMove = {};
    if (kind == W2U_EXTRA_ACTION_INSTRUCT) {
        // scproc_Fight rewrites a selected move to Encore's move before any
        // event handlers run. Instruct explicitly repeats the recorded move,
        // so hide Encore only for this one immediate action.
        savedEncore = W2U_GetStoredMoveCondition(battleMon, CONDITION_ENCORE);
        W2U_SetStoredMoveCondition(battleMon, CONDITION_ENCORE, 0);
    }
    else if (kind == W2U_EXTRA_ACTION_DANCER) {
        // Dancer copies are real actions, but they are not the user's most
        // recent move for Instruct (or Encore/Torment) purposes.
        lastMove.previousMove = battleMon->previousMove;
        lastMove.previousMoveID = battleMon->previousMoveID;
        lastMove.consecutiveMoveCounter = battleMon->consecutiveMoveCounter;
        lastMove.previousMoveType = battleMon->prevMoveType;
        lastMove.previousTargetPos = battleMon->prevTargetPos;
    }

    W2U_ClearExtraActionTurnFlags(battleMon);
    SetExtraActionFlag();
    u32 procAction = ActionOrder_Proc(serverFlow, actionOrder);
    ResetExtraActionFlag();

    BattleMon* activeMon = W2U_GetActiveBattleMon(serverFlow, pokemonSlot);
    if (activeMon == battleMon && !BattleMon_IsFainted(battleMon)) {
        if (kind == W2U_EXTRA_ACTION_INSTRUCT) {
            W2U_SetStoredMoveCondition(battleMon, CONDITION_ENCORE, savedEncore);
        }
        else if (kind == W2U_EXTRA_ACTION_DANCER) {
            battleMon->previousMove = lastMove.previousMove;
            battleMon->previousMoveID = lastMove.previousMoveID;
            battleMon->consecutiveMoveCounter = lastMove.consecutiveMoveCounter;
            battleMon->prevMoveType = lastMove.previousMoveType;
            battleMon->prevTargetPos = lastMove.previousTargetPos;
        }

        if (hasPendingNaturalAction && pokemonSlot < BATTLE_MAX_SLOTS) {
            sExtraActionNaturalResetSlots |= 1u << pokemonSlot;
        }
    }
    return procAction;
}

static void W2U_ClearAllExtraActionOrders()
{
    for (u32 i = 0; i < W2U_ARRAY_COUNT(sExtraActionOrder); ++i) {
        W2U_ClearActionOrderWork(&sExtraActionOrder[i]);
        sExtraActionKind[i] = W2U_EXTRA_ACTION_NONE;
    }
    sExtraActionNaturalResetSlots = 0;
}

static void W2U_SetDancerCopiedTarget(
    ServerFlow* serverFlow,
    BattleAction_Fight* fight,
    u32 dancerSlot,
    u32 currentSlot)
{
    volatile u32 moveTarget = PML_MoveGetParam((MOVE_ID)fight->moveID, MVDATA_TARGET);
    if (moveTarget == TARGET_OTHER_SELECT ||
        moveTarget == TARGET_ENEMY_SELECT ||
        moveTarget == TARGET_ENEMY_RANDOM) {
        if (!MainModule_IsAllyMonID(dancerSlot, currentSlot)) {
            fight->targetPos = Handler_PokeIDToPokePos(serverFlow, currentSlot);
        }
        return;
    }

    if (moveTarget == TARGET_FRIEND_AND_USER) {
        fight->targetPos = Handler_PokeIDToPokePos(serverFlow, dancerSlot);
        return;
    }

    if (moveTarget == TARGET_FRIEND_SELECT) {
        fight->targetPos = CommonGetAllyPos(serverFlow, Handler_PokeIDToPokePos(serverFlow, dancerSlot));
        return;
    }

    fight->targetPos = 6;
}

static u8 W2U_GetEncodedActionPriority(ActionOrderWork* actionOrder, u32 actionIdx)
{
    return (u8)((actionOrder[actionIdx].speed >> 16) & 0x3FFFFF);
}

static u8 W2U_GetEncodedSpecialPriority(ActionOrderWork* actionOrder, u32 actionIdx)
{
    return (u8)((actionOrder[actionIdx].speed >> 13) & 0x7);
}

static u16 W2U_GetEncodedActionSpeed(ActionOrderWork* actionOrder, u32 actionIdx)
{
    return (u16)(actionOrder[actionIdx].speed & 0x1FFF);
}

static void W2U_SwapActionOrder(
    ActionOrderWork* actionOrder,
    u16* speedStats,
    u8* priority,
    u8* eventPriority,
    u8 slowIdx,
    u8 fastIdx)
{
    if (slowIdx == fastIdx) {
        return;
    }

    ActionOrderWork actionOrderBuffer = actionOrder[fastIdx];
    actionOrder[fastIdx] = actionOrder[slowIdx];
    actionOrder[slowIdx] = actionOrderBuffer;

    u16 speedBuffer = speedStats[fastIdx];
    speedStats[fastIdx] = speedStats[slowIdx];
    speedStats[slowIdx] = speedBuffer;

    u8 priorityBuffer = priority[fastIdx];
    priority[fastIdx] = priority[slowIdx];
    priority[slowIdx] = priorityBuffer;

    u8 eventPriorityBuffer = eventPriority[fastIdx];
    eventPriority[fastIdx] = eventPriority[slowIdx];
    eventPriority[slowIdx] = eventPriorityBuffer;
}

static void W2U_SortBySpeedDynamic(
    ServerFlow* serverFlow,
    ActionOrderWork* actionOrder,
    u8 firstIdx,
    bool turnStart)
{
    u8 actionCount = W2U_GetActionOrderCount(serverFlow);
    if (!serverFlow || !actionOrder || firstIdx >= actionCount) {
        return;
    }

    u8 startIdx = firstIdx;
    if (!turnStart) {
        ++startIdx;
    }

    if (startIdx == 0) {
        for (u32 i = 0; i < W2U_ARRAY_COUNT(sSendLastSlots); ++i) {
            sSendLastSlots[i] = 0xFF;
        }
    }

    if (startIdx >= actionCount) {
        return;
    }

    u8 pokeAmount = (u8)(actionCount - startIdx);
    if (pokeAmount <= 1) {
        return;
    }

    u16 speedStats[W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork)];
    u8 priority[W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork)];
    u8 eventPriority[W2U_ARRAY_COUNT(((ServerFlow*)0)->actionOrderWork)];
    for (u32 i = 0; i < W2U_ARRAY_COUNT(eventPriority); ++i) {
        ((volatile u16*)speedStats)[i] = 0;
        ((volatile u8*)priority)[i] = 0;
        ((volatile u8*)eventPriority)[i] = 7;
    }

    for (u8 i = startIdx; i < actionCount; ++i) {
        BattleMon* battleMon = actionOrder[i].battleMon;
        if (battleMon && !BattleMon_IsFainted(battleMon)) {
            speedStats[i] = (u16)ServerEvent_CalculateSpeed(serverFlow, battleMon, 1);
            priority[i] = W2U_GetEncodedActionPriority(actionOrder, i);
            priority[i] += W2U_GetEncodedSpecialPriority(actionOrder, i) - W2U_ACTION_ORDER_SPECIAL_PRIO_OFFSET;

            for (u8 j = 0; j < W2U_ARRAY_COUNT(sSendLastSlots); ++j) {
                if (sSendLastSlots[j] == 0xFF) {
                    break;
                }

                if (sSendLastSlots[j] == battleMon->battleSlot) {
                    eventPriority[i] = 6 - j;
                }
            }

            if (BattleAction_GetAction(&actionOrder[i].action) == 4) {
                eventPriority[i] = 8;
            }
        }
        else {
            priority[i] = 0xFF;
        }
    }

    for (u8 i = startIdx; i < actionCount; ++i) {
        u8 randomSpot = startIdx + (u8)BattleRandom(pokeAmount);
        W2U_SwapActionOrder(actionOrder, speedStats, priority, eventPriority, i, randomSpot);
    }

    for (u8 i = startIdx; i + 1 < actionCount; ++i) {
        if (priority[i] == 0xFF) {
            continue;
        }

        u8 bestIdx = i;
        for (u8 j = i + 1; j < actionCount; ++j) {
            if (priority[j] == 0xFF) {
                continue;
            }

            bool shouldComeFirst = eventPriority[j] > eventPriority[bestIdx];
            if (eventPriority[j] == eventPriority[bestIdx]) {
                shouldComeFirst = priority[j] > priority[bestIdx];
                if (priority[j] == priority[bestIdx]) {
                    shouldComeFirst = speedStats[j] > speedStats[bestIdx];
                }
            }

            if (shouldComeFirst) {
                bestIdx = j;
            }
        }

        if (bestIdx != i) {
            W2U_SwapActionOrder(actionOrder, speedStats, priority, eventPriority, i, bestIdx);
        }
    }
}

extern "C" u32 THUMB_BRANCH_BattleHandler_InterruptAction(
    ServerFlow* serverFlow,
    HandlerParam_InterruptPoke* params)
{
    if (!serverFlow || !params || !ActionOrder_InterruptReserve(serverFlow, params->pokeID)) {
        return 0;
    }

    BattleHandler_SetString(serverFlow, &params->exStr);
    sInterruptActionFlag = 1;
    return 1;
}

extern "C" u32 THUMB_BRANCH_BattleHandler_SendLast(ServerFlow* serverFlow, HandlerParam_SendLast* params)
{
    if (!serverFlow || !params || !ActionOrder_SendToLast(serverFlow, params->pokeID)) {
        return 0;
    }

    BattleHandler_SetString(serverFlow, &params->exStr);

    for (u32 i = 0; i < W2U_ARRAY_COUNT(sSendLastSlots); ++i) {
        if (sSendLastSlots[i] == 0xFF) {
            sSendLastSlots[i] = params->pokeID;
            break;
        }
    }

    return 1;
}

extern "C" int THUMB_BRANCH_ServerFlow_ActOrderProcMain(ServerFlow* serverFlow, u32 currentActionIdx)
{
    if (!serverFlow) {
        return 0;
    }

    u32 procAction = 0;
    ActionOrderWork* actionOrderWork = serverFlow->actionOrderWork;

    // A switch or other flow interruption can re-enter this routine at a
    // nonzero action index. Preserve any queued immediate actions and the
    // per-action reset marker across that continuation.
    if (currentActionIdx == 0) {
        W2U_ClearAllExtraActionOrders();
    }
    ResetExtraActionFlag();

    W2U_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, true);
    W2U_Mega_ProcessActionOrderBeforeMoves(serverFlow, currentActionIdx);

    while (currentActionIdx < W2U_GetActionOrderCount(serverFlow) || sExtraActionOrder[0].battleMon) {
        ActionOrderWork* currentActionOrder = nullptr;
        bool isExtraAction = false;

        if (sExtraActionOrder[0].battleMon) {
            if (!W2U_IsValidExtraAction(
                    &sExtraActionOrder[0],
                    (W2UExtraActionKind)sExtraActionKind[0])) {
                W2U_AdvanceExtraActionOrders();
                ResetExtraActionFlag();
                continue;
            }

            isExtraAction = true;
            currentActionOrder = &sExtraActionOrder[0];
        }
        else {
            currentActionOrder = &actionOrderWork[currentActionIdx];
            u32 pokemonSlot = currentActionOrder->battleMon
                ? currentActionOrder->battleMon->battleSlot
                : BATTLE_MAX_SLOTS;
            if (pokemonSlot < BATTLE_MAX_SLOTS &&
                (sExtraActionNaturalResetSlots & (1u << pokemonSlot))) {
                W2U_ClearExtraActionTurnFlags(currentActionOrder->battleMon);
                sExtraActionNaturalResetSlots &= ~(1u << pokemonSlot);
            }
        }

        if (!isExtraAction) {
            u32 action = BattleAction_GetAction(&currentActionOrder->action);
            if (procAction == 6 && action != 6) {
                ServerControl_CheckActivation(serverFlow);
                u8 actionCount = W2U_GetActionOrderCount(serverFlow);
                SortActionOrderBySpeed(
                    serverFlow,
                    currentActionOrder,
                    (u32)actionCount - currentActionIdx);
            }

            if (action == 1) {
                // Beak Blast and Shell Trap arm at the same boundary where
                // native ActionOrder_Proc is about to run Focus Punch's
                // scproc_BeforeFirstFight pass. Keep client command enqueueing
                // outside the event-manager callback itself.
                W2U_MoveState_PrepareBeakBlastCharges(serverFlow, currentActionIdx);
                W2U_MoveState_PrepareShellTraps(serverFlow, currentActionIdx);
            }
        }

        if (isExtraAction) {
            procAction = W2U_ProcessExtraAction(
                serverFlow,
                currentActionOrder,
                (W2UExtraActionKind)sExtraActionKind[0]);
        }
        else {
            procAction = ActionOrder_Proc(serverFlow, currentActionOrder);
        }

        if (serverFlow->flowResult == 5) {
            if (isExtraAction) {
                W2U_AdvanceExtraActionOrders();
                ResetExtraActionFlag();
            }
            return isExtraAction ? (int)currentActionIdx : (int)(currentActionIdx + 1);
        }

        bool shouldSortAfterAction = sInterruptActionFlag != 1;
        sInterruptActionFlag = 0;

        if (isExtraAction) {
            W2U_AdvanceExtraActionOrders();
            ResetExtraActionFlag();
        }

        if (shouldSortAfterAction) {
            W2U_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, isExtraAction);
        }

        u32 getExp = ServerControl_CheckExpGet(serverFlow);
        b32 matchup = ServerControl_CheckMatchup(serverFlow);
        if (matchup) {
            serverFlow->flowResult = 4;
            return isExtraAction ? (int)currentActionIdx : (int)(currentActionIdx + 1);
        }

        if (serverFlow->flowResult == 6 || serverFlow->flowResult == 1) {
            return isExtraAction ? (int)currentActionIdx : (int)(currentActionIdx + 1);
        }

        if (getExp) {
            serverFlow->flowResult = 3;
            return isExtraAction ? (int)currentActionIdx : (int)(currentActionIdx + 1);
        }

        if (!isExtraAction) {
            ++currentActionIdx;
        }
    }

    if (!serverFlow->flowResult) {
        u32 turnCheck = ServerControl_TurnCheck(serverFlow);
        if (serverFlow->flowResult == 5) {
            return serverFlow->numActOrder;
        }
        if (ServerControl_CheckMatchup(serverFlow)) {
            serverFlow->flowResult = 4;
            return serverFlow->numActOrder;
        }

        if (turnCheck) {
            serverFlow->flowResult = 3;
            return serverFlow->numActOrder;
        }

        if (sEmergencyExitEndTurnSwitchFlag) {
            sEmergencyExitEndTurnSwitchFlag = 0;
            serverFlow->turnCheckSeq = 7;
            serverFlow->flowResult = 1;
            return serverFlow->numActOrder;
        }

        u32 faintedCount = j_j_FaintRecord_GetCount_1(&serverFlow->faintRecord, 0);
        if (Handler_IsPosOpenForRevivedMon(serverFlow) || faintedCount) {
            ServerFlow_ReqChangePokeForServer(serverFlow, &serverFlow->field_4CE);
            ServerDisplay_IllusionSet(serverFlow, &serverFlow->field_4CE);
            serverFlow->flowResult = 2;
            return serverFlow->numActOrder;
        }

        serverFlow->flowResult = 0;
    }

    return serverFlow->numActOrder;
}

extern "C" void THUMB_BRANCH_HandlerThrash(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (!work || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    BattleMon* currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
    MOVE_ID moveID = W2U_GetBattleEventItemSubID(item);

    if (W2U_IsActiveExtraActionKind(W2U_EXTRA_ACTION_DANCER)) {
        MoveEvent_ForceRemoveItemFromBattleMon(currentMon, moveID);
        return;
    }

    if (!BattleMon_CheckIfMoveCondition(currentMon, CONDITION_MOVELOCK) && !work[6]) {
        u32 maxTurns = BattleRandom(2u) + 2u;

        HandlerParam_AddCondition* addCondition =
            (HandlerParam_AddCondition*)BattleHandler_PushWork(serverFlow, EFFECT_ADD_CONDITION, pokemonSlot);
        addCondition->condition = CONDITION_MOVELOCK;
        addCondition->condData = Condition_MakeTurnParam(maxTurns, moveID);
        addCondition->almost = 0;
        addCondition->pokeID = (u8)pokemonSlot;
        BattleHandler_PopWork(serverFlow, addCondition);
        work[6] = 1;
        *work = maxTurns;
    }
}

extern "C" void THUMB_BRANCH_HandlerThrashEnd(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (!work || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID) || !work[6]) {
        return;
    }

    BattleMon* currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
    b32 finished = 0;

    if (*work && !W2U_IsActiveExtraActionKind(W2U_EXTRA_ACTION_DANCER)) {
        --*work;
    }

    if (!BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG)) {
        HandlerParam_CureCondition* cureCondition =
            (HandlerParam_CureCondition*)BattleHandler_PushWork(serverFlow, EFFECT_CURE_STATUS, pokemonSlot);
        cureCondition->condition = CONDITION_MOVELOCK;
        cureCondition->pokeCount = 1;
        cureCondition->pokeID[0] = (u8)pokemonSlot;
        BattleHandler_PopWork(serverFlow, cureCondition);

        finished = 1;
    }

    if (!*work) {
        HandlerParam_AddCondition* addCondition =
            (HandlerParam_AddCondition*)BattleHandler_PushWork(serverFlow, EFFECT_ADD_CONDITION, pokemonSlot);
        addCondition->condition = CONDITION_CONFUSION;
        MakeCondition(CONDITION_CONFUSION, currentMon, &addCondition->condData);
        addCondition->reserved = 1;
        addCondition->pokeID = (u8)pokemonSlot;
        BattleHandler_StrSetup(&addCondition->exStr, 2u, 360u);
        BattleHandler_AddArg(&addCondition->exStr, pokemonSlot);
        BattleHandler_PopWork(serverFlow, addCondition);

        finished = 1;
    }

    if (finished) {
        MoveEvent_ForceRemoveItemFromBattleMon(currentMon, W2U_GetBattleEventItemSubID(item));
    }
}

namespace {

typedef BattleEventHandlerTableEntry* (*AbilityEventAddFunc)(u32* handlerAmount);

struct W2UAbilityEventAddTable {
    u16 handlerAmount;
    u16 ability;
    BattleEventHandlerTableEntry* handlers;
};

struct W2UVanillaAbilityAliasEventAddTable {
    u16 ability;
    u16 vanillaAbility;
};

ABILITY GetEventItemAbility(BattleEventItem* item)
{
    if (!item) {
        return 0;
    }
    return (ABILITY)*(u16*)((u8*)item + W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET);
}

u32 GetNormalMoveConversionType(ABILITY ability)
{
    switch (ability) {
    case ABIL_AERILATE:
        return TYPE_FLYING;
    case ABIL_PIXILATE:
        return TYPE_FAIRY;
    case ABIL_REFRIGERATE:
        return TYPE_ICE;
    case ABIL_GALVANIZE:
        return TYPE_ELECTRIC;
    case ABIL_DRAGONIZE:
        return TYPE_DRAGON;
    default:
        return TYPE_NULL;
    }
}

bool GetMoveFlagPowerBoost(ABILITY ability, u32* flagIndex, u32* powerRatio)
{
    switch (ability) {
    case ABIL_STRONG_JAW:
        *flagIndex = MOVE_FLAG_INDEX_BITE;
        *powerRatio = W2U_ABILITY_POWER_RATIO_1_5X;
        return true;
    case ABIL_TOUGH_CLAWS:
        *flagIndex = MOVE_FLAG_INDEX_CONTACT;
        *powerRatio = W2U_ABILITY_POWER_RATIO_1_3X;
        return true;
    case ABIL_MEGA_LAUNCHER:
        *flagIndex = MOVE_FLAG_INDEX_PULSE;
        *powerRatio = W2U_ABILITY_POWER_RATIO_1_5X;
        return true;
    default:
        return false;
    }
}

FIELD_EFFECT GetAuraFamilyFieldEffect(ABILITY ability)
{
    switch (ability) {
    case ABIL_DARK_AURA:
        return FLDEFF_DARK_AURA;
    case ABIL_FAIRY_AURA:
        return FLDEFF_FAIRY_AURA;
    default:
        return 0;
    }
}

u32 GetAuraFamilyMessageID(ABILITY ability)
{
    switch (ability) {
    case ABIL_DARK_AURA:
        return BATTLE_DARK_AURA_MSGID;
    case ABIL_FAIRY_AURA:
        return BATTLE_FAIRY_AURA_MSGID;
    case ABIL_AURA_BREAK:
        return BATTLE_AURA_BREAK_MSGID;
    default:
        return 0;
    }
}

bool AddAuraFamilyOwner(ServerFlow* serverFlow, u32 pokemonSlot, ABILITY ability)
{
    FIELD_EFFECT fieldEffect = GetAuraFamilyFieldEffect(ability);
    if (fieldEffect) {
        return W2U_AuraField_AddEffectOwner(serverFlow, pokemonSlot, fieldEffect);
    }
    if (ability == ABIL_AURA_BREAK) {
        return W2U_AuraField_AddAuraBreakMon(pokemonSlot);
    }
    return false;
}

bool RemoveAuraFamilyOwner(u32 pokemonSlot, ABILITY ability)
{
    FIELD_EFFECT fieldEffect = GetAuraFamilyFieldEffect(ability);
    if (fieldEffect) {
        return W2U_AuraField_RemoveEffectOwner(pokemonSlot, fieldEffect);
    }
    if (ability == ABIL_AURA_BREAK) {
        return W2U_AuraField_RemoveAuraBreakMon(pokemonSlot);
    }
    return false;
}

// Moves whose type is decided elsewhere keep it (Showdown's noModifyType, plus
// Struggle and Hidden Power, Normal in this generation's data): an -ate
// ability does not convert them, e.g. Weather Ball with no weather stays Normal.
static bool KeepsOwnType(u32 moveID)
{
    switch (moveID) {
    case MOVE_STRUGGLE:
    case MOVE_HIDDEN_POWER:
    case MOVE_WEATHER_BALL:
    case MOVE_NATURAL_GIFT:
    case MOVE_JUDGMENT:
    case MOVE_TECHNO_BLAST:
    case MOVE_MULTIATTACK:
    case MOVE_REVELATION_DANCE:
    case MOVE_TERRAIN_PULSE:
        return true;
    default:
        return false;
    }
}

void RewriteNormalMoveType(u32 pokemonSlot, u32 newType)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        !KeepsOwnType((u32)BattleEventVar_GetValue(VAR_MOVE_ID)) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, newType);
    }
}

void BoostConvertedMove(u32 pokemonSlot, u32 convertedType)
{
    const u32 move = BattleEventVar_GetValue(VAR_MOVE_ID);
    if (move == MOVE_REVELATION_DANCE || move == MOVE_TERRAIN_PULSE) {
        return;
    }
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == (int)convertedType) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_ABILITY_POWER_RATIO_1_2X);
    }
}

bool IsEventMon(u32 pokemonSlot)
{
    return pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID);
}

bool IsNewEvent()
{
    return BattleEventVar_GetValue(VAR_MON_ID) == -1 &&
        BattleEventVar_GetValue(VAR_ATTACKING_MON) == -1 &&
        BattleEventVar_GetValue(VAR_DEFENDING_MON) == -1;
}

void SetupNewEventMonAndItem(u32 pokemonSlot, ITEM itemID)
{
    BattleEventVar_SetConstValue(VAR_MON_ID, -1);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, -1);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, -1);
    BattleEventVar_SetConstValue(NEW_VAR_MON_ID, pokemonSlot);
    BattleEventVar_SetValue(VAR_ITEM, itemID);
}

void PushAbilityMessage(ServerFlow* serverFlow, u32 pokemonSlot, u32 msgID)
{
    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, 2u, msgID);
    BattleHandler_AddArg(&message->str, pokemonSlot);
    BattleHandler_PopWork(serverFlow, message);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

BattleMon* GetAbilityBattleMon(ServerFlow* serverFlow, u32 pokemonSlot)
{
    if (!serverFlow || !serverFlow->pokeCon || pokemonSlot >= BATTLE_MAX_SLOTS) {
        return 0;
    }
    return PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
}

bool PushAbilityStatStageChange(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    StatStage stat,
    s8 volume)
{
    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon ||
        BattleMon_IsFainted(currentMon) ||
        !BattleMon_IsStatChangeValid(currentMon, stat, volume)) {
        return false;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_ChangeStatStage* statChange =
        (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_STAT_STAGE,
            pokemonSlot);
    statChange->pokeCount = 1;
    statChange->pokeID[0] = (u8)pokemonSlot;
    statChange->moveAnimation = 1;
    statChange->stat = stat;
    statChange->volume = volume;
    BattleHandler_PopWork(serverFlow, statChange);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    return true;
}

bool DamageCrossedBelowHalfHP(BattleMon* battleMon, u32 damage)
{
    if (!battleMon || battleMon->maxHP == 0 || BattleMon_IsFainted(battleMon)) {
        return false;
    }

    u32 currentHP = battleMon->currentHP;
    u32 beforeDamageHP = currentHP + damage;
    if (beforeDamageHP > battleMon->maxHP) {
        beforeDamageHP = battleMon->maxHP;
    }

    return beforeDamageHP * 2 >= battleMon->maxHP && currentHP * 2 < battleMon->maxHP;
}

bool DamageCrossedBelowHalfHPFromBefore(BattleMon* battleMon, u32 beforeDamageHP)
{
    if (!battleMon || battleMon->maxHP == 0 || BattleMon_IsFainted(battleMon)) {
        return false;
    }

    if (beforeDamageHP > battleMon->maxHP) {
        beforeDamageHP = battleMon->maxHP;
    }
    return beforeDamageHP * 2 >= battleMon->maxHP &&
        (u32)battleMon->currentHP * 2 < battleMon->maxHP;
}

StatStage GetHighestStatStage(BattleMon* battleMon)
{
    StatStage stat = STATSTAGE_ATTACK;
    u16 highest = battleMon ? battleMon->attack : 0;

    if (battleMon && highest < battleMon->defense) {
        highest = battleMon->defense;
        stat = STATSTAGE_DEFENSE;
    }
    if (battleMon && highest < battleMon->specialAttack) {
        highest = battleMon->specialAttack;
        stat = STATSTAGE_SPECIAL_ATTACK;
    }
    if (battleMon && highest < battleMon->specialDefense) {
        highest = battleMon->specialDefense;
        stat = STATSTAGE_SPECIAL_DEFENSE;
    }
    if (battleMon && highest < battleMon->speed) {
        stat = STATSTAGE_SPEED;
    }

    return stat;
}

bool IsTargetSlotInCurrentDamageEvent(u32 pokemonSlot)
{
    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        if (pokemonSlot == (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx))) {
            return true;
        }
    }
    return false;
}

bool IsReceiverFailAbility(ABILITY ability)
{
    switch (ability) {
    case 25: // Wonder Guard
    case 36: // Trace
    case 59: // Forecast
    case 121: // Multitype
    case 122: // Flower Gift
    case 149: // Illusion
    case 150: // Imposter
    case 161: // Zen Mode
    case ABIL_STANCE_CHANGE:
    case ABIL_SHIELDS_DOWN:
    case ABIL_SCHOOLING:
    case ABIL_DISGUISE:
    case ABIL_BATTLE_BOND:
    case ABIL_POWER_CONSTRUCT:
    case ABIL_COMATOSE:
    case ABIL_RECEIVER:
    case ABIL_POWER_OF_ALCHEMY:
    case ABIL_RKS_SYSTEM:
    // Generation VIII / IX form abilities (Showdown's `noreceiver` flag)
    case ABIL_GULP_MISSILE:
    case ABIL_ICE_FACE:
    case ABIL_HUNGER_SWITCH:
    case ABIL_ZERO_TO_HERO:
    case ABIL_COMMANDER:
        return true;
    default:
        return false;
    }
}

bool EventMonIsFainted(ServerFlow* serverFlow, u32 pokemonSlot)
{
    if (!serverFlow || !serverFlow->pokeCon) {
        return false;
    }

    BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    return battleMon && BattleMon_IsFainted(battleMon);
}

bool IsAromaVeilBlockedCondition(CONDITION condition)
{
    switch (condition) {
    case CONDITION_HEALBLOCK:
    case CONDITION_DISABLE:
    case CONDITION_ATTRACT:
    case CONDITION_TAUNT:
    case CONDITION_ENCORE:
    case CONDITION_TORMENT:
        return true;
    default:
        return false;
    }
}

bool AromaVeilProtectsTarget(u32 pokemonSlot)
{
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    return pokemonSlot == defendingSlot || MainModule_IsAllyMonID(pokemonSlot, defendingSlot);
}

bool SweetVeilProtectsTarget(u32 pokemonSlot)
{
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    return pokemonSlot == defendingSlot || MainModule_IsAllyMonID(pokemonSlot, defendingSlot);
}

bool BattleMonHasType(BattleMon* battleMon, u32 type)
{
    return battleMon && (battleMon->Type1 == type || battleMon->Type2 == type);
}

bool IsFlowerVeilBlockedCondition(CONDITION condition)
{
    switch (condition) {
    case CONDITION_PARALYSIS:
    case CONDITION_SLEEP:
    case CONDITION_FREEZE:
    case CONDITION_BURN:
    case CONDITION_POISON:
    case CONDITION_CONFUSION:
    case CONDITION_YAWN:
        return true;
    default:
        return false;
    }
}

bool FlowerVeilProtectsSlot(ServerFlow* serverFlow, u32 pokemonSlot, u32 protectedSlot)
{
    if (!serverFlow || !serverFlow->pokeCon) {
        return false;
    }

    BattleMon* protectedMon = PokeCon_GetBattleMon(serverFlow->pokeCon, protectedSlot);
    return (pokemonSlot == protectedSlot || MainModule_IsAllyMonID(pokemonSlot, protectedSlot)) &&
        BattleMonHasType(protectedMon, TYPE_GRASS);
}

bool IsDamageReductionBerry(ITEM itemID)
{
    switch (itemID) {
    case ITEM_OCCA_BERRY:
    case ITEM_PASSHO_BERRY:
    case ITEM_WACAN_BERRY:
    case ITEM_RINDO_BERRY:
    case ITEM_YACHE_BERRY:
    case ITEM_CHOPLE_BERRY:
    case ITEM_KEBIA_BERRY:
    case ITEM_SHUCA_BERRY:
    case ITEM_COBA_BERRY:
    case ITEM_PAYAPA_BERRY:
    case ITEM_TANGA_BERRY:
    case ITEM_CHARTI_BERRY:
    case ITEM_KASIB_BERRY:
    case ITEM_HABAN_BERRY:
    case ITEM_COLBUR_BERRY:
    case ITEM_BABIRI_BERRY:
    case ITEM_CHILAN_BERRY:
    case ITEM_ROSELI_BERRY:
        return true;
    default:
        return false;
    }
}

void SymbiosisChangeItem(ServerFlow* serverFlow, u32 pokemonSlot, u32 receiveSlot)
{
    if (!serverFlow ||
        !serverFlow->pokeCon ||
        pokemonSlot == receiveSlot ||
        !MainModule_IsAllyMonID(pokemonSlot, receiveSlot)) {
        return;
    }

    BattleMon* receiveMon = PokeCon_GetBattleMon(serverFlow->pokeCon, receiveSlot);
    if (!receiveMon || BattleMon_GetHeldItem(receiveMon) != ITEM_NULL) {
        return;
    }

    BattleMon* giveMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    ITEM giveItem = giveMon ? BattleMon_GetHeldItem(giveMon) : ITEM_NULL;
    if (giveItem == ITEM_NULL ||
        PML_ItemIsMail(giveItem) ||
        HandlerCommon_IsUnremovableItem(giveMon->species, giveItem) ||
        HandlerCommon_IsUnremovableItem(receiveMon->species, giveItem)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_SwapItem* swapItem =
        (HandlerParam_SwapItem*)BattleHandler_PushWork(serverFlow, EFFECT_SWAP_ITEM, pokemonSlot);
    swapItem->pokeID = (u8)receiveSlot;
    BattleHandler_StrSetup(&swapItem->exStr, 2u, BATTLE_SYMBIOSIS_MSGID);
    BattleHandler_AddArg(&swapItem->exStr, pokemonSlot);
    BattleHandler_StrSetup(&swapItem->exSubStr1, 2u, 685);
    BattleHandler_AddArg(&swapItem->exSubStr1, receiveSlot);
    BattleHandler_AddArg(&swapItem->exSubStr1, giveItem);
    BattleHandler_PopWork(serverFlow, swapItem);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

void ResetParentalBondFlag()
{
    sParentalBondActive = false;
    sParentalBondPowerHit = 0;
}

void SetParentalBondFlag()
{
    sParentalBondActive = true;
    sParentalBondPowerHit = 0;
}

PokeSet* GetServerFlowTargetOriginal(ServerFlow* serverFlow)
{
    return *(PokeSet**)((u8*)serverFlow + W2U_SERVERFLOW_SET_TARGET_ORIGINAL_OFFSET);
}

bool MoveIgnoresParentalBond(MOVE_ID moveID)
{
    switch (moveID) {
    case MOVE_FLING:
    case MOVE_SELFDESTRUCT:
    case MOVE_EXPLOSION:
    case MOVE_FINAL_GAMBIT:
    case MOVE_UPROAR:
    case MOVE_ROLLOUT:
    case MOVE_ICE_BALL:
    case MOVE_ENDEAVOR:
        return true;
    default:
        return false;
    }
}

bool ParentalBondCheck(ServerFlow* serverFlow, MOVE_ID moveID, BattleMon* attackingMon, PokeSet* targetSet)
{
    if (!serverFlow ||
        !attackingMon ||
        !targetSet ||
        moveID == MOVE_NONE ||
        BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL_PARENTAL_BOND ||
        targetSet->count != 1) {
        return false;
    }

    MoveParam moveParam;
    W2U_ServerEvent_GetMoveParam(serverFlow, moveID, attackingMon, &moveParam);
    if (moveParam.targetType == TARGET_USER ||
        moveParam.targetType == TARGET_FIELD ||
        moveParam.targetType == TARGET_FIELD_SIDE_ENEMY ||
        moveParam.targetType == TARGET_FIELD_SIDE_FRIEND ||
        getMoveFlag(moveParam.moveID, MOVE_FLAG_INDEX_REQUIRES_CHARGE) ||
        MoveIgnoresParentalBond(moveParam.moveID)) {
        return false;
    }

    return true;
}

BattleEventItem* AddAbilityEvent(
    BattleMon* battleMon,
    ABILITY ability,
    BattleEventHandlerTableEntry* handlers,
    u32 handlerAmount)
{
    if (!battleMon || !handlers || handlerAmount == 0) {
        return 0;
    }

    BattleEventPriority mainPriority = GetHandlerMainPriority(&handlerAmount);
    u32 subPriority = AbilityEvent_GetSubPriority(battleMon);
    u32 pokemonSlot = BattleMon_GetID(battleMon);
    return BattleEvent_AddItem(
        EVENTITEM_ABILITY,
        (u16)ability,
        mainPriority,
        subPriority,
        pokemonSlot,
        handlers,
        (u16)handlerAmount);
}

BattleEventItem* GetAbilityEvent(BattleMon* battleMon, ABILITY ability, AbilityEventAddFunc func)
{
    if (!func) {
        return 0;
    }

    u32 handlerAmount = 0;
    BattleEventHandlerTableEntry* handlers = func(&handlerAmount);
    return AddAbilityEvent(battleMon, ability, handlers, handlerAmount);
}

} // namespace

extern "C" b32 W2U_BattleMonCanUseHeldItem(BattleMon* battleMon)
{
    constexpr FIELD_EFFECT kMagicRoom = 0x07;

    if (!battleMon ||
        BattleField_CheckEffect(kMagicRoom) ||
        BattleMon_GetValue(battleMon, VALUE_EFFECTIVE_ABILITY) == ABIL_KLUTZ ||
        BattleMon_CheckIfMoveCondition(battleMon, CONDITION_BLOCK_ITEM) ||
        BattleMon_GetTurnFlag(battleMon, TURNFLAG_CANTUSEITEM)) {
        return 0;
    }

    return 1;
}

extern "C" b32 W2U_MoveMakesContact(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    u32 attackingSlot)
{
    if (!getMoveFlag(moveID, MOVE_FLAG_INDEX_CONTACT)) {
        return 0;
    }

    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!attackingMon) {
        return 1;
    }

    if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_LONG_REACH) {
        return 0;
    }

    if (BattleMon_GetHeldItem(attackingMon) == ITEM_PROTECTIVE_PADS &&
        W2U_BattleMonCanUseHeldItem(attackingMon)) {
        return 0;
    }

    return 1;
}

extern "C" void THUMB_BRANCH_SAFESTACK_CommonContactStatusAbility(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    CONDITION condition,
    ConditionData condData,
    u8 effectChance)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot) ||
        !AbilityEvent_RollEffectChance(serverFlow, effectChance)) {
        return;
    }

    HandlerParam_AddCondition* addCondition =
        (HandlerParam_AddCondition*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_ADD_CONDITION,
            pokemonSlot);
    addCondition->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    addCondition->condition = condition;
    addCondition->condData = condData;
    addCondition->almost = 0;
    addCondition->pokeID = (u8)attackingSlot;
    BattleHandler_PopWork(serverFlow, addCondition);
}

extern "C" void THUMB_BRANCH_HandlerRoughSkin(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        return;
    }

    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!attackingMon || BattleMon_IsFainted(attackingMon)) {
        return;
    }

    HandlerParam_Damage* damage =
        (HandlerParam_Damage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_DAMAGE,
            pokemonSlot);
    damage->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    damage->pokeID = (u8)attackingSlot;
    damage->damage = (u16)DivideMaxHPZeroCheck(attackingMon, 8u);
    BattleHandler_StrSetup(&damage->exStr, 2u, 430u);
    BattleHandler_AddArg(&damage->exStr, attackingSlot);
    BattleHandler_PopWork(serverFlow, damage);
}

extern "C" void THUMB_BRANCH_HandlerAftermath(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        return;
    }

    BattleMon* defendingMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!defendingMon || !BattleMon_IsFainted(defendingMon)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        return;
    }

    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!attackingMon) {
        return;
    }

    HandlerParam_Damage* damage =
        (HandlerParam_Damage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_DAMAGE,
            pokemonSlot);
    damage->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    damage->pokeID = (u8)attackingSlot;
    damage->damage = (u16)DivideMaxHPZeroCheck(attackingMon, 4u);
    damage->flags = (u8)((damage->flags & 0xFEu) | 1u);
    BattleHandler_StrSetup(&damage->exStr, 2u, 402u);
    BattleHandler_AddArg(&damage->exStr, attackingSlot);
    BattleHandler_PopWork(serverFlow, damage);
}

extern "C" void THUMB_BRANCH_HandlerPickpocket(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (!HandlerCommon_CheckTargetMonID(pokemonSlot)) {
        return;
    }

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (HandlerCommon_CheckIfCanStealPokeItem(serverFlow, pokemonSlot, attackingSlot)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        return;
    }

    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!currentMon || !attackingMon ||
        BattleMon_GetHeldItem(currentMon) != ITEM_NULL) {
        return;
    }

    ITEM heldItem = BattleMon_GetHeldItem(attackingMon);
    if (heldItem == ITEM_NULL) {
        return;
    }

    HandlerParam_SwapItem* swapItem =
        (HandlerParam_SwapItem*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_SWAP_ITEM,
            pokemonSlot);
    swapItem->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    swapItem->pokeID = (u8)attackingSlot;
    BattleHandler_StrSetup(&swapItem->exStr, 2u, 460u);
    BattleHandler_AddArg(&swapItem->exStr, attackingSlot);
    BattleHandler_AddArg(&swapItem->exStr, heldItem);
    BattleHandler_PopWork(serverFlow, swapItem);
}

extern "C" void THUMB_BRANCH_HandlerPoisonTouch(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (pokemonSlot != attackingSlot ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot) ||
        !AbilityEvent_RollEffectChance(serverFlow, 30u)) {
        return;
    }

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    HandlerParam_AddCondition* addCondition =
        (HandlerParam_AddCondition*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_ADD_CONDITION,
            pokemonSlot);
    addCondition->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    addCondition->pokeID = (u8)defendingSlot;
    addCondition->condition = CONDITION_POISON;
    addCondition->condData = MakeBasicStatus(CONDITION_POISON);
    BattleHandler_StrSetup(&addCondition->exStr, 2u, 472u);
    BattleHandler_AddArg(&addCondition->exStr, defendingSlot);
    BattleHandler_PopWork(serverFlow, addCondition);
}

extern "C" void THUMB_BRANCH_HandlerMummy(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        Handler_CheckMatchup(serverFlow)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        return;
    }

    BattleMon* defendingMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!defendingMon || !attackingMon) {
        return;
    }

    ABILITY ability = BattleMon_GetValue(defendingMon, VALUE_ABILITY);
    if (BattleMon_GetValue(attackingMon, VALUE_ABILITY) == ability) {
        return;
    }

    HandlerParam_ChangeAbility* changeAbility =
        (HandlerParam_ChangeAbility*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_ABILITY,
            pokemonSlot);
    changeAbility->ability = (u16)ability;
    changeAbility->pokeID = (u8)attackingSlot;
    BattleHandler_StrSetup(&changeAbility->exStr, 2u, 463u);
    BattleHandler_AddArg(&changeAbility->exStr, attackingSlot);
    BattleHandler_AddArg(&changeAbility->exStr, ability);
    if (!MainModule_IsAllyMonID(pokemonSlot, attackingSlot)) {
        changeAbility->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    }
    BattleHandler_PopWork(serverFlow, changeAbility);
}

extern "C" void THUMB_BRANCH_HandlerStickyBarbDamageReaction(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot) ||
        !attackingMon ||
        BattleMon_GetHeldItem(attackingMon) != ITEM_NULL) {
        return;
    }

    HandlerParam_SwapItem* swapItem =
        (HandlerParam_SwapItem*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_SWAP_ITEM,
            pokemonSlot);
    swapItem->pokeID = (u8)attackingSlot;
    BattleHandler_PopWork(serverFlow, swapItem);
}

extern "C" void THUMB_BRANCH_HandlerRockyHelmet(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot) || !attackingMon) {
        return;
    }

    u8 itemUseParam = (u8)CommonGetItemParam(item, W2U_ITSTAT_USE_PARAM);
    HandlerParam_Damage* damage =
        (HandlerParam_Damage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_DAMAGE,
            pokemonSlot);
    damage->pokeID = (u8)attackingSlot;
    damage->damage = (u16)DivideMaxHPZeroCheck(attackingMon, itemUseParam);
    BattleHandler_StrSetup(&damage->exStr, 2u, 424u);
    BattleHandler_AddArg(&damage->exStr, attackingSlot);
    BattleHandler_PopWork(serverFlow, damage);
}

extern "C" void THUMB_BRANCH_ServerEvent_GetMoveParam(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    BattleMon* battleMon,
    MoveParam* moveParam)
{
    BattleEventVar_Push();

    u32 currentSlot = BattleMon_GetID(battleMon);
    BattleEventVar_SetConstValue(VAR_MON_ID, currentSlot);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, moveID);
    BattleEventVar_SetValue(VAR_MOVE_TYPE, PML_MoveGetType(moveID));
    BattleEventVar_SetValue(VAR_USER_TYPE, BattleMon_GetPokeType(battleMon));
    BattleEventVar_SetValue(VAR_MOVE_CATEGORY, PML_MoveGetCategory(moveID));
    BattleEventVar_SetValue(VAR_TARGET_TYPE, PML_MoveGetParam(moveID, MVDATA_TARGET));
    BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);

    BattleEvent_CallHandlers(serverFlow, EVENT_MOVE_PARAM);
    // Native type-conversion abilities can run after ordinary move entries.
    // Give exceptional move types a final, module-owned parameter phase;
    // keep the same live context and allow no native conversion afterward.
    BattleEvent_CallHandlers(serverFlow, EVENT_W2U_MOVE_PARAM_FINAL);

    u32 moveType = BattleEventVar_GetValue(VAR_MOVE_TYPE);
    u32 category = BattleEventVar_GetValue(VAR_MOVE_CATEGORY);

    moveParam->moveID = (u16)moveID;
    moveParam->originalMoveID = (u16)moveID;
    moveParam->userType = (u16)BattleEventVar_GetValue(VAR_USER_TYPE);
    moveParam->moveType = (u8)moveType;
    moveParam->damageType = (u8)moveType;
    moveParam->category = category;
    moveParam->targetType = BattleEventVar_GetValue(VAR_TARGET_TYPE);
    moveParam->flags = 0;

    if (BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS)) {
        moveParam->moveType = TYPE_NULL;
    }

    BattleEventVar_Pop();
}

#if !defined(W2U_BATTLE_CHILD)
extern "C" void W2U_ServerEvent_GetMoveParam(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    BattleMon* battleMon,
    MoveParam* moveParam)
{
    THUMB_BRANCH_ServerEvent_GetMoveParam(serverFlow, moveID, battleMon, moveParam);
}
#endif

extern "C" u32 THUMB_BRANCH_ServerEvent_CheckDamageToRecover(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    BattleMon* defendingMon,
    MoveParam* moveParam)
{
    BattleEventVar_Push();

    u32 attackingSlot = BattleMon_GetID(attackingMon);
    u32 defendingSlot = BattleMon_GetID(defendingMon);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, attackingSlot);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, defendingSlot);
    BattleEventVar_SetConstValue(VAR_MOVE_TYPE, moveParam->moveType);
    BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, moveParam->category);
    BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);

    BattleEvent_CallHandlers(serverFlow, EVENT_CHECK_DAMAGE_TO_RECOVER);
    u32 generalFlag = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);

    BattleEventVar_Pop();
    return generalFlag;
}

extern "C" void THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x36(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    MOVE_ID moveID,
    HitCheckParam* hitCheckParam)
{
    ServerEvent_CheckMultihitHits(serverFlow, attackingMon, moveID, hitCheckParam);
    ResetParentalBondFlag();

    if (!serverFlow || !hitCheckParam || hitCheckParam->multiHitMove) {
        return;
    }

    if (ParentalBondCheck(serverFlow, moveID, attackingMon, GetServerFlowTargetOriginal(serverFlow))) {
        hitCheckParam->countMax = 2;
        hitCheckParam->checkEveryTime = 0;
        hitCheckParam->multiHitMove = 1;
        SetParentalBondFlag();
    }
}

#if !defined(W2U_DYNAMIC_BATTLE_CORE)
extern "C" void HandlerNormalMoveConversionTypeChange(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)serverFlow;
    (void)work;
    u32 convertedType = GetNormalMoveConversionType(GetEventItemAbility(item));
    if (convertedType != TYPE_NULL) {
        RewriteNormalMoveType(pokemonSlot, convertedType);
    }
}

extern "C" void HandlerAromaVeilPreventConditions(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (!work ||
        !AromaVeilProtectsTarget(pokemonSlot) ||
        !IsAromaVeilBlockedCondition((CONDITION)BattleEventVar_GetValue(VAR_CONDITION_ID))) {
        return;
    }

    *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, W2U_FORCE_FAIL_MESSAGE);
}

extern "C" void HandlerAromaVeilFailMessage(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || !*work || !AromaVeilProtectsTarget(pokemonSlot)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, 2u, BATTLE_AROMA_VEIL_MSGID);
    BattleHandler_AddArg(&message->str, BattleEventVar_GetValue(VAR_DEFENDING_MON));
    BattleHandler_PopWork(serverFlow, message);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    *work = 0;
}

BattleEventHandlerTableEntry AromaVeilHandlers[] = {
    {EVENT_ADD_CONDITION_CHECK_FAIL, HandlerAromaVeilPreventConditions},
    {EVENT_ADD_CONDITION_FAIL, HandlerAromaVeilFailMessage},
};


extern "C" void HandlerFlowerVeilPreventStatus(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if (!work ||
        !FlowerVeilProtectsSlot(serverFlow, pokemonSlot, defendingSlot) ||
        !IsFlowerVeilBlockedCondition((CONDITION)BattleEventVar_GetValue(VAR_CONDITION_ID))) {
        return;
    }

    *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, W2U_FORCE_FAIL_MESSAGE);
}

extern "C" void HandlerFlowerVeilStatusFailMessage(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if (!work || !*work || !FlowerVeilProtectsSlot(serverFlow, pokemonSlot, defendingSlot)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, 2u, BATTLE_FLOWER_VEIL_MSGID);
    BattleHandler_AddArg(&message->str, defendingSlot);
    BattleHandler_PopWork(serverFlow, message);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    *work = 0;
}

extern "C" void HandlerFlowerVeilStatCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (!work ||
        !FlowerVeilProtectsSlot(serverFlow, pokemonSlot, currentSlot) ||
        currentSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_VOLUME) > 0) {
        return;
    }

    *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
}

extern "C" void HandlerFlowerVeilStatFailMessage(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (!work || !*work || !FlowerVeilProtectsSlot(serverFlow, pokemonSlot, currentSlot)) {
        return;
    }

    u32 moveSerial = (u32)BattleEventVar_GetValue(VAR_MOVE_SERIAL);
    if (!moveSerial || work[1] != moveSerial) {
        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

        HandlerParam_Message* message =
            (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
        BattleHandler_StrSetup(&message->str, 2u, BATTLE_FLOWER_VEIL_MSGID);
        BattleHandler_AddArg(&message->str, currentSlot);
        BattleHandler_PopWork(serverFlow, message);

        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
        work[1] = moveSerial;
    }

    *work = 0;
}

BattleEventHandlerTableEntry FlowerVeilHandlers[] = {
    {EVENT_ADD_CONDITION_CHECK_FAIL, HandlerFlowerVeilPreventStatus},
    {EVENT_ADD_CONDITION_FAIL, HandlerFlowerVeilStatusFailMessage},
    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, HandlerFlowerVeilStatCheck},
    {EVENT_STAT_STAGE_CHANGE_FAIL, HandlerFlowerVeilStatFailMessage},
};


extern "C" void HandlerSweetVeilPreventSleep(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (!work ||
        !SweetVeilProtectsTarget(pokemonSlot) ||
        BattleEventVar_GetValue(VAR_CONDITION_ID) != CONDITION_SLEEP) {
        return;
    }

    *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, W2U_FORCE_FAIL_MESSAGE);
}

extern "C" void HandlerSweetVeilFailMessage(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || !*work || !SweetVeilProtectsTarget(pokemonSlot)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, 2u, BATTLE_SWEET_VEIL_MSGID);
    BattleHandler_AddArg(&message->str, BattleEventVar_GetValue(VAR_DEFENDING_MON));
    BattleHandler_PopWork(serverFlow, message);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    *work = 0;
}

BattleEventHandlerTableEntry SweetVeilHandlers[] = {
    {EVENT_ADD_CONDITION_CHECK_FAIL, HandlerSweetVeilPreventSleep},
    {EVENT_ADD_CONDITION_FAIL, HandlerSweetVeilFailMessage},
};


extern "C" void HandlerStanceChange(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!serverFlow ||
        !serverFlow->pokeCon ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* currentMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    if (!currentMon || currentMon->species != SPECIES_AEGISLASH) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 currentForm = BattleMon_GetValue(currentMon, VALUE_FORM);
    u32 newForm = currentForm;
    u32 msgID = 0;

    if (moveID == MOVE_KINGS_SHIELD && currentForm != 0) {
        newForm = 0;
        msgID = BATTLE_SHIELD_FORME_MSGID;
    } else if (currentForm == 0) {
        u32 category = PML_MoveGetCategory(moveID);
        if (category == SPLIT_PHYSICAL || category == SPLIT_SPECIAL) {
            newForm = 1;
            msgID = BATTLE_BLADE_FORME_MSGID;
        }
    }

    if (newForm == currentForm) {
        return;
    }

    HandlerParam_ChangeForm* changeForm =
        (HandlerParam_ChangeForm*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
    changeForm->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    changeForm->pokeID = (u8)pokemonSlot;
    changeForm->newForm = (u8)newForm;
    changeForm->dontResetOnSwitch = 0;
    BattleHandler_StrSetup(&changeForm->exStr, 2u, msgID);
    BattleHandler_AddArg(&changeForm->exStr, pokemonSlot);
    BattleHandler_PopWork(serverFlow, changeForm);
}

BattleEventHandlerTableEntry StanceChangeHandlers[] = {
    {EVENT_MOVE_SEQUENCE_START, HandlerStanceChange},
};


extern "C" void HandlerShieldsDown(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon ||
        currentMon->species != SPECIES_774 ||
        BattleMon_IsFainted(currentMon) ||
        BattleMon_TransformCheck(currentMon)) {
        return;
    }

    u32 currentForm = BattleMon_GetValue(currentMon, VALUE_FORM);
    if (currentForm >= W2U_MINIOR_FORM_COUNT) {
        return;
    }

    // Forms 0-6 retain Minior's red-through-violet color identity while its
    // shell is up. Forms 7-13 are the matching exposed cores.
    bool belowHalf = (u32)currentMon->currentHP * 2u < (u32)currentMon->maxHP;
    u32 newForm = currentForm;
    if (belowHalf && currentForm < W2U_MINIOR_METEOR_FORM_COUNT) {
        newForm = currentForm + W2U_MINIOR_CORE_FORM_START;
    } else if (!belowHalf && currentForm >= W2U_MINIOR_CORE_FORM_START) {
        newForm = currentForm - W2U_MINIOR_CORE_FORM_START;
    }

    if (newForm == currentForm) {
        return;
    }

    HandlerParam_ChangeForm* changeForm =
        (HandlerParam_ChangeForm*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_FORM,
            pokemonSlot);
    changeForm->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    changeForm->pokeID = (u8)pokemonSlot;
    changeForm->newForm = (u8)newForm;
    changeForm->dontResetOnSwitch = 0;
    HandlerParam_StrParams emptyString = {};
    changeForm->exStr = emptyString;
    BattleHandler_PopWork(serverFlow, changeForm);
}

BattleEventHandlerTableEntry ShieldsDownHandlers[] = {
    // Waiting until the action ends prevents a multi-hit move from exposing
    // the core between hits. The simple-damage event covers poison, weather,
    // recoil, and other damage paths outside an ordinary move action.
    {EVENT_ACTION_PROCESSING_END, HandlerShieldsDown},
    {EVENT_SIMPLE_DAMAGE_REACTION, HandlerShieldsDown},
    {EVENT_TURN_CHECK_END, HandlerShieldsDown},
    {EVENT_SWITCH_IN, HandlerShieldsDown},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerShieldsDown},
};


extern "C" void HandlerSchooling(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon ||
        currentMon->species != SPECIES_746 ||
        BattleMon_IsFainted(currentMon) ||
        BattleMon_TransformCheck(currentMon) ||
        currentMon->maxHP == 0) {
        return;
    }

    u32 currentForm = BattleMon_GetValue(currentMon, VALUE_FORM);
    if (currentForm > W2U_WISHIWASHI_SCHOOL_FORM) {
        return;
    }

    // School Form is active only from level 20 onward and strictly above
    // one quarter HP. At exactly 25% HP Wishiwashi is Solo Form.
    bool shouldSchool =
        currentMon->level >= W2U_SCHOOLING_MIN_LEVEL &&
        (u32)currentMon->currentHP * 4u > (u32)currentMon->maxHP;
    u32 newForm = shouldSchool ?
        W2U_WISHIWASHI_SCHOOL_FORM : W2U_WISHIWASHI_SOLO_FORM;
    if (newForm == currentForm) {
        return;
    }

    HandlerParam_ChangeForm* changeForm =
        (HandlerParam_ChangeForm*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_FORM,
            pokemonSlot);
    changeForm->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    changeForm->pokeID = (u8)pokemonSlot;
    changeForm->newForm = (u8)newForm;
    changeForm->dontResetOnSwitch = 0;
    HandlerParam_StrParams emptyString = {};
    changeForm->exStr = emptyString;
    BattleHandler_PopWork(serverFlow, changeForm);
}

BattleEventHandlerTableEntry SchoolingHandlers[] = {
    {EVENT_ACTION_PROCESSING_END, HandlerSchooling},
    {EVENT_SIMPLE_DAMAGE_REACTION, HandlerSchooling},
    {EVENT_TURN_CHECK_END, HandlerSchooling},
    {EVENT_SWITCH_IN, HandlerSchooling},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerSchooling},
};


extern "C" void HandlerPowerConstruct(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon ||
        currentMon->species != SPECIES_ZYGARDE ||
        BattleMon_IsFainted(currentMon) ||
        BattleMon_TransformCheck(currentMon) ||
        currentMon->maxHP == 0) {
        return;
    }

    const u32 currentForm = BattleMon_GetValue(currentMon, VALUE_FORM);
    if (currentForm != W2U_ZYGARDE_10_FORM &&
        currentForm != W2U_ZYGARDE_50_FORM) {
        return;
    }

    // The project rule is a strict drop below half HP. Complete Form is
    // one-way for the remainder of the battle and reverts on switch-out.
    if ((u32)currentMon->currentHP * 2u >= (u32)currentMon->maxHP) {
        return;
    }

    HandlerParam_ChangeForm* changeForm =
        (HandlerParam_ChangeForm*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_FORM,
            pokemonSlot);
    changeForm->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    changeForm->pokeID = (u8)pokemonSlot;
    changeForm->newForm = W2U_ZYGARDE_COMPLETE_FORM;
    changeForm->dontResetOnSwitch = 0;
    HandlerParam_StrParams emptyString = {};
    changeForm->exStr = emptyString;
    BattleHandler_PopWork(serverFlow, changeForm);
}

BattleEventHandlerTableEntry PowerConstructHandlers[] = {
    // Resolve after the complete action so multi-hit attacks cannot trigger
    // the form change between hits. The remaining events cover residual
    // damage and ability changes outside a normal move action.
    {EVENT_ACTION_PROCESSING_END, HandlerPowerConstruct},
    {EVENT_SIMPLE_DAMAGE_REACTION, HandlerPowerConstruct},
    {EVENT_TURN_CHECK_END, HandlerPowerConstruct},
    {EVENT_SWITCH_IN, HandlerPowerConstruct},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerPowerConstruct},
};


static BattleMon* DisguiseIntactTarget(ServerFlow* serverFlow, u32 pokemonSlot)
{
    if (!serverFlow || !serverFlow->pokeCon ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) return 0;
    BattleMon* mon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    return mon && mon->species == SPECIES_778 &&
        BattleMon_GetValue(mon, VALUE_FORM) == 0 &&
        !BattleMon_IsSubstituteActive(mon) ? mon : 0;
}

static void HandlerDisguisePreventDamage(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    // Pure damage-estimation callback: suppress this strike, not the target
    // or whole sequence. No form/HP work is queued by AI calculations.
    if (DisguiseIntactTarget(serverFlow, pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_DAMAGE, 0);
    }
}

static void HandlerDisguiseBreak(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    BattleMon* currentMon = DisguiseIntactTarget(serverFlow, pokemonSlot);
    if (!currentMon) return;
    // Native damage determination runs for real execution after the first
    // calculated strike, including zero damage, but not AI simulation.

    HandlerParam_ChangeForm* changeForm =
        (HandlerParam_ChangeForm*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
    changeForm->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    changeForm->pokeID = (u8)pokemonSlot;
    changeForm->newForm = 1;
    changeForm->dontResetOnSwitch = 1;
    HandlerParam_StrParams emptyString = {};
    changeForm->exStr = emptyString;
    BattleHandler_PopWork(serverFlow, changeForm);

    // Keep the announcement as a separate work item so it is displayed after
    // the instant client-side form refresh and before Disguise's HP cost.
    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, 2u, BATTLE_DISGUISE_MSGID);
    BattleHandler_AddArg(&message->str, pokemonSlot);
    BattleHandler_PopWork(serverFlow, message);

    // Generation VIII onward: busting Disguise also costs 1/8 of Mimikyu's
    // maximum HP. DivideMaxHPZeroCheck keeps the damage at a minimum of 1.
    HandlerParam_Damage* damage =
        (HandlerParam_Damage*)BattleHandler_PushWork(serverFlow, EFFECT_DAMAGE, pokemonSlot);
    damage->pokeID = (u8)pokemonSlot;
    damage->damage = (u16)DivideMaxHPZeroCheck(currentMon, 8u);
    BattleHandler_PopWork(serverFlow, damage);
}

BattleEventHandlerTableEntry DisguiseHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_END, HandlerDisguisePreventDamage},
    {EVENT_DETERMINE_MOVE_DAMAGE, HandlerDisguiseBreak},
};


extern "C" void HandlerBattleBond(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work ||
        work[0] ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!attackingMon ||
        attackingMon->species != SPECIES_GRENINJA ||
        BattleMon_IsFainted(attackingMon) ||
        BattleMon_TransformCheck(attackingMon) ||
        BattleMon_GetValue(attackingMon, VALUE_FORM) != 0) {
        return;
    }

    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetAbilityBattleMon(serverFlow, targetSlot);
        if (!targetMon ||
            targetSlot == pokemonSlot ||
            MainModule_IsAllyMonID(pokemonSlot, targetSlot) ||
            !BattleMon_IsFainted(targetMon)) {
            continue;
        }

        // Mark the event item before queuing the form change so spread and
        // multi-hit moves can never enqueue Battle Bond more than once.
        work[0] = 1;

        HandlerParam_ChangeForm* changeForm =
            (HandlerParam_ChangeForm*)BattleHandler_PushWork(
                serverFlow,
                EFFECT_CHANGE_FORM,
                pokemonSlot);
        changeForm->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
        changeForm->pokeID = (u8)pokemonSlot;
        changeForm->newForm = W2U_BATTLE_BOND_ASH_FORM;
        changeForm->dontResetOnSwitch = 1;
        BattleHandler_StrSetup(&changeForm->exStr, 2u, BATTLE_BATTLE_BOND_MSGID);
        BattleHandler_AddArg(&changeForm->exStr, pokemonSlot);
        BattleHandler_PopWork(serverFlow, changeForm);
        return;
    }
}

BattleEventHandlerTableEntry BattleBondHandlers[] = {
    {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerBattleBond},
};


extern "C" void HandlerNormalMoveConversionPower(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)serverFlow;
    (void)work;
    u32 convertedType = GetNormalMoveConversionType(GetEventItemAbility(item));
    if (convertedType != TYPE_NULL) {
        BoostConvertedMove(pokemonSlot, convertedType);
    }
}

BattleEventHandlerTableEntry NormalMoveConversionHandlers[] = {
    {EVENT_MOVE_PARAM, HandlerNormalMoveConversionTypeChange},
    {EVENT_MOVE_POWER, HandlerNormalMoveConversionPower},
};


extern "C" void HandlerLiquidVoice(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        getMoveFlag(
            (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID),
            MOVE_FLAG_INDEX_SOUND)) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_WATER);
    }
}

BattleEventHandlerTableEntry LiquidVoiceHandlers[] = {
    {EVENT_MOVE_PARAM, HandlerLiquidVoice},
};


extern "C" void HandlerTriage(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        (getMoveFlag(moveID, MOVE_FLAG_INDEX_HEALING_MOVE) ||
         getMoveFlag(moveID, MOVE_FLAG_INDEX_HEALING_PROPERTY))) {
        BattleEventVar_RewriteValue(
            VAR_MOVE_PRIORITY,
            BattleEventVar_GetValue(VAR_MOVE_PRIORITY) + 3);
    }
}

BattleEventHandlerTableEntry TriageHandlers[] = {
    {EVENT_GET_MOVE_PRIORITY, HandlerTriage},
};


extern "C" void HandlerStakeout(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* defendingMon = GetAbilityBattleMon(
        serverFlow,
        (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (W2U_SwitchedInThisTurn(serverFlow, defendingMon)) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_ABILITY_POWER_RATIO_2X);
    }
}

BattleEventHandlerTableEntry StakeoutHandlers[] = {
    {EVENT_MOVE_POWER, HandlerStakeout},
};


extern "C" void HandlerWaterBubblePreventBurn(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    if (work &&
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_BURN) {
        *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, W2U_FORCE_FAIL_MESSAGE);
    }
}

extern "C" void HandlerWaterBubbleBurnFailMessage(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if (!work || !*work || pokemonSlot != defendingSlot) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(
        &message->str,
        W2U_WATER_BUBBLE_FAIL_MSG_NARC,
        W2U_WATER_BUBBLE_FAIL_MSG_ID);
    BattleHandler_AddArg(&message->str, defendingSlot);
    BattleHandler_PopWork(serverFlow, message);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    *work = 0;
}

extern "C" void HandlerWaterBubbleCureBurn(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon || BattleMon_GetStatus(currentMon) != CONDITION_BURN) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_CureCondition* cureCondition =
        (HandlerParam_CureCondition*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CURE_STATUS,
            pokemonSlot);
    cureCondition->condition = CONDITION_BURN;
    cureCondition->pokeCount = 1;
    cureCondition->pokeID[0] = (u8)pokemonSlot;
    BattleHandler_PopWork(serverFlow, cureCondition);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

extern "C" void HandlerWaterBubbleFireResistance(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_FIRE) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_ABILITY_RATIO_HALF);
    }
}

extern "C" void HandlerWaterBubbleWaterPower(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_ABILITY_POWER_RATIO_2X);
    }
}

BattleEventHandlerTableEntry WaterBubbleHandlers[] = {
    {EVENT_ADD_CONDITION_CHECK_FAIL, HandlerWaterBubblePreventBurn},
    {EVENT_ADD_CONDITION_FAIL, HandlerWaterBubbleBurnFailMessage},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerWaterBubbleCureBurn},
    {EVENT_ACTION_PROCESSING_END, HandlerWaterBubbleCureBurn},
    {EVENT_ATTACKER_POWER, HandlerWaterBubbleFireResistance},
    {EVENT_MOVE_POWER, HandlerWaterBubbleWaterPower},
};


extern "C" void HandlerStamina(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        PushAbilityStatStageChange(serverFlow, pokemonSlot, STATSTAGE_DEFENSE, 1);
    }
}

BattleEventHandlerTableEntry StaminaHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerStamina},
};


extern "C" void HandlerWaterCompaction(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER) {
        PushAbilityStatStageChange(serverFlow, pokemonSlot, STATSTAGE_DEFENSE, 2);
    }
}

BattleEventHandlerTableEntry WaterCompactionHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerWaterCompaction},
};


extern "C" void HandlerMerciless(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* defendingMon = GetAbilityBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (defendingMon && BattleMon_GetStatus(defendingMon) == CONDITION_POISON) {
        // Always a critical hit (Showdown). Stage 4 is only 1/2 with this
        // generation's table: BTL_CALC_CheckCritical reads this sentinel.
        BattleEventVar_RewriteValue(VAR_CRIT_STAGE, W2U_CRIT_STAGE_ALWAYS);
    }
}

BattleEventHandlerTableEntry MercilessHandlers[] = {
    {EVENT_CRITICAL_CHECK, HandlerMerciless},
};


extern "C" void HandlerSteelworker(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_STEEL) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_ABILITY_POWER_RATIO_1_5X);
    }
}

BattleEventHandlerTableEntry SteelworkerHandlers[] = {
    {EVENT_MOVE_POWER, HandlerSteelworker},
};


extern "C" void HandlerBerserk(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!IsTargetSlotInCurrentDamageEvent(pokemonSlot) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (DamageCrossedBelowHalfHP(currentMon, (u32)BattleEventVar_GetValue(VAR_DAMAGE))) {
        PushAbilityStatStageChange(serverFlow, pokemonSlot, STATSTAGE_SPECIAL_ATTACK, 1);
    }
}

BattleEventHandlerTableEntry BerserkHandlers[] = {
    {EVENT_DAMAGE_PROCESSING_END_HIT_2, HandlerBerserk},
};


extern "C" void HandlerSlushRush(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        ServerEvent_GetWeather(serverFlow) == WEATHER_HAIL) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_ABILITY_POWER_RATIO_2X);
    }
}

BattleEventHandlerTableEntry SlushRushHandlers[] = {
    {EVENT_CALC_SPEED, HandlerSlushRush},
};


extern "C" void HandlerSurgeSurfer(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        W2U_MoveState_GetTerrain() == TERRAIN_ELECTRIC) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_ABILITY_POWER_RATIO_2X);
    }
}

BattleEventHandlerTableEntry SurgeSurferHandlers[] = {
    {EVENT_CALC_SPEED, HandlerSurgeSurfer},
};

static bool GetTerrainSurgeParams(
    ABILITY ability,
    TERRAIN* terrain,
    u32* msgID,
    MOVE_ID* animationMoveID)
{
    // Use indexed data rather than a switch. GCC's Thumb-1 switch lowering
    // calls __gnu_thumb1_case_uqi, which the runtime DLL linker cannot resolve.
    static const TERRAIN terrains[] = {
        TERRAIN_ELECTRIC,
        TERRAIN_PSYCHIC,
        TERRAIN_MISTY,
        TERRAIN_GRASSY,
    };
    static const u32 messageIDs[] = {
        BATTLE_ELECTRIC_TERRAIN_MSGID,
        BATTLE_PSYCHIC_TERRAIN_MSGID,
        BATTLE_MISTY_TERRAIN_MSGID,
        BATTLE_GRASSY_TERRAIN_MSGID,
    };
    static const MOVE_ID animationMoveIDs[] = {
        MOVE_ELECTRIC_TERRAIN,
        MOVE_PSYCHIC_TERRAIN,
        MOVE_MISTY_TERRAIN,
        MOVE_GRASSY_TERRAIN,
    };

    u32 index = (u32)ability - (u32)ABIL_ELECTRIC_SURGE;
    if (index >= 4) {
        return false;
    }

    *terrain = terrains[index];
    *msgID = messageIDs[index];
    *animationMoveID = animationMoveIDs[index];
    return true;
}

extern "C" void HandlerTerrainSurge(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    TERRAIN terrain = TERRAIN_NULL;
    u32 msgID = 0;
    MOVE_ID animationMoveID = MOVE_NONE;
    if (GetTerrainSurgeParams(
            GetEventItemAbility(item),
            &terrain,
            &msgID,
            &animationMoveID)) {
        W2U_MoveState_SetTerrainFromAbility(
            serverFlow,
            pokemonSlot,
            terrain,
            msgID,
            animationMoveID);
    }
}

BattleEventHandlerTableEntry TerrainSurgeHandlers[] = {
    {EVENT_SWITCH_IN, HandlerTerrainSurge},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerTerrainSurge},
};


extern "C" void HandlerBattery(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (pokemonSlot != attackingSlot &&
        MainModule_IsAllyMonID(pokemonSlot, attackingSlot) &&
        BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == SPLIT_SPECIAL) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_ABILITY_POWER_RATIO_1_3_DECIMAL);
    }
}

BattleEventHandlerTableEntry BatteryHandlers[] = {
    {EVENT_ATTACKER_POWER, HandlerBattery},
};


extern "C" void HandlerFluffy(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        return;
    }

    u32 ratio = 4096;
    if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_FIRE) {
        ratio *= 2;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        ratio /= 2;
    }

    BattleEventVar_MulValue(VAR_RATIO, ratio);
}

BattleEventHandlerTableEntry FluffyHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerFluffy},
};


extern "C" void HandlerSoulHeart(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    u32 faintedSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (pokemonSlot != faintedSlot && EventMonIsFainted(serverFlow, faintedSlot)) {
        PushAbilityStatStageChange(serverFlow, pokemonSlot, STATSTAGE_SPECIAL_ATTACK, 1);
    }
}

BattleEventHandlerTableEntry SoulHeartHandlers[] = {
    {EVENT_NOTIFY_FAINTED, HandlerSoulHeart},
};


extern "C" void HandlerBeastBoost(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!attackingMon || BattleMon_IsFainted(attackingMon)) {
        return;
    }

    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetAbilityBattleMon(serverFlow, targetSlot);
        if (targetMon && BattleMon_IsFainted(targetMon)) {
            PushAbilityStatStageChange(serverFlow, pokemonSlot, GetHighestStatStage(attackingMon), 1);
        }
    }
}

BattleEventHandlerTableEntry BeastBoostHandlers[] = {
    {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerBeastBoost},
};


extern "C" void HandlerPrismArmor(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        (u32)BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS) >= W2U_ABILITY_EFFECTIVENESS_2X) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_ABILITY_POWER_RATIO_3_4X);
    }
}

BattleEventHandlerTableEntry PrismArmorHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerPrismArmor},
};


extern "C" void HandlerQueenlyMajesty(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if ((pokemonSlot != defendingSlot && !MainModule_IsAllyMonID(pokemonSlot, defendingSlot)) ||
        defendingSlot == attackingSlot) {
        return;
    }

    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    if (W2U_GetQueuedMovePriority(serverFlow, attackingMon) > 0) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry QueenlyMajestyHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, HandlerQueenlyMajesty},
};


extern "C" void HandlerInnardsOut(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (!serverFlow ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        return;
    }

    BattleMon* defendingMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!defendingMon || !BattleMon_IsFainted(defendingMon)) {
        return;
    }

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (attackingSlot >= BATTLE_MAX_SLOTS ||
        Handler_PokeIDToPokePos(serverFlow, attackingSlot) == W2U_NULL_BATTLE_POS) {
        return;
    }

    u32 beforeDamageHP =
        (u32)BattleMon_GetValue(defendingMon, VALUE_CURRENT_HP) +
        (u32)BattleEventVar_GetValue(VAR_DAMAGE);
    if (!beforeDamageHP) {
        return;
    }

    HandlerParam_Damage* damage =
        (HandlerParam_Damage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_DAMAGE,
            pokemonSlot);
    damage->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    damage->pokeID = (u8)attackingSlot;
    damage->damage = (u16)beforeDamageHP;
    damage->flags = (u8)((damage->flags & 0xFEu) | 1u);
    BattleHandler_StrSetup(
        &damage->exStr,
        W2U_INNARDS_OUT_MSG_NARC,
        W2U_INNARDS_OUT_MSG_ID);
    BattleHandler_AddArg(&damage->exStr, attackingSlot);
    BattleHandler_PopWork(serverFlow, damage);
}

BattleEventHandlerTableEntry InnardsOutHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerInnardsOut},
};


extern "C" void HandlerDancerCheckMove(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (CheckExtraActionFlag()) {
        return;
    }

    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (pokemonSlot == currentSlot || !getMoveFlag(moveID, MOVE_FLAG_INDEX_DANCE)) {
        return;
    }

    BattleMon* dancerMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
    if (!dancerMon ||
        BattleMon_CheckIfMoveCondition(dancerMon, CONDITION_SKYDROP) ||
        BattleMon_CheckIfMoveCondition(dancerMon, CONDITION_CHARGELOCK)) {
        return;
    }

    BattleMon* currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
    ActionOrderWork nextExtraAction;
    W2U_ClearActionOrderWork(&nextExtraAction);
    nextExtraAction.battleMon = dancerMon;

    bool foundAction = false;
    for (u32 orderIdx = 0; orderIdx < W2U_ARRAY_COUNT(serverFlow->actionOrderWork); ++orderIdx) {
        if (serverFlow->actionOrderWork[orderIdx].battleMon != currentMon) {
            continue;
        }

        BattleActionParam copiedAction = serverFlow->actionOrderWork[orderIdx].action;
        if (BattleAction_GetAction(&copiedAction) != 1 || copiedAction.baFight.moveID != moveID) {
            continue;
        }

        nextExtraAction.action = copiedAction;
        nextExtraAction.speed = serverFlow->actionOrderWork[orderIdx].speed;
        nextExtraAction.partyID = serverFlow->actionOrderWork[orderIdx].partyID;

        BattleAction_Fight* fight = &nextExtraAction.action.baFight;
        W2U_SetDancerCopiedTarget(serverFlow, fight, pokemonSlot, currentSlot);

        foundAction = true;
        break;
    }

    if (!foundAction ||
        !W2U_IsValidExtraAction(&nextExtraAction, W2U_EXTRA_ACTION_DANCER) ||
        W2U_IsQueuedExtraFight(dancerMon, moveID)) {
        return;
    }

    nextExtraAction.done = 0;
    nextExtraAction.field_E = 0;
    nextExtraAction.field_F = 0;

    ShiftExtraActionOrders();
    ActionOrderWork* extraActionOrder = GetExtraActionOrder(0);
    W2U_CopyActionOrderWork(extraActionOrder, &nextExtraAction);
    sExtraActionKind[0] = W2U_EXTRA_ACTION_DANCER;
}

extern "C" void HandlerDancerPopUp(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (W2U_IsActiveExtraActionKind(W2U_EXTRA_ACTION_DANCER) &&
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);
        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    }
}

extern "C" void HandlerDancerMoveFail(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (!W2U_IsActiveExtraActionKind(W2U_EXTRA_ACTION_DANCER) || pokemonSlot != currentSlot) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    BattleMon* currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
    if (!currentMon) {
        return;
    }

    if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_ENCORE)) {
        ActionOrderWork* extraActionOrder = nullptr;
        for (u32 actionIdx = 0; actionIdx < W2U_ARRAY_COUNT(sExtraActionOrder); ++actionIdx) {
            if (GetExtraActionOrder(actionIdx)->battleMon == currentMon) {
                extraActionOrder = GetExtraActionOrder(actionIdx);
                break;
            }
        }

        if (extraActionOrder && extraActionOrder->action.baFight.moveID != moveID) {
            BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_MOVELOCK);
            return;
        }
    }

    if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_MOVELOCK) ||
        BattleMon_CheckIfMoveCondition(currentMon, CONDITION_CHOICELOCK)) {
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_MOVELOCK);
    }
}

BattleEventHandlerTableEntry DancerHandlers[] = {
    {EVENT_MOVE_EXECUTE_EFFECTIVE, HandlerDancerCheckMove},
    {EVENT_MOVE_EXECUTE_NOEFFECT, HandlerDancerCheckMove},
    {EVENT_MOVE_SEQUENCE_START, HandlerDancerPopUp},
    {EVENT_MOVE_EXECUTE_CHECK1, HandlerDancerMoveFail},
};


extern "C" void HandlerReceiver(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    u32 faintedSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (pokemonSlot == faintedSlot ||
        !MainModule_IsAllyMonID(pokemonSlot, faintedSlot) ||
        !EventMonIsFainted(serverFlow, faintedSlot)) {
        return;
    }

    BattleMon* faintedMon = GetAbilityBattleMon(serverFlow, faintedSlot);
    ABILITY ability = faintedMon ? BattleMon_GetValue(faintedMon, VALUE_ABILITY) : 0;
    if (ability == 0 || IsReceiverFailAbility(ability)) {
        return;
    }

    HandlerParam_ChangeAbility* changeAbility =
        (HandlerParam_ChangeAbility*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_ABILITY,
            pokemonSlot);
    changeAbility->pokeID = (u8)pokemonSlot;
    changeAbility->ability = (u16)ability;
    changeAbility->sameAbilityEffective = 0;
    changeAbility->skipSwitchInEvent = 0;
    BattleHandler_StrSetup(&changeAbility->exStr, W2U_RECEIVER_MSG_NARC, W2U_RECEIVER_MSG_ID);
    BattleHandler_AddArg(&changeAbility->exStr, pokemonSlot);
    BattleHandler_AddArg(&changeAbility->exStr, faintedSlot);
    BattleHandler_AddArg(&changeAbility->exStr, ability);
    BattleHandler_PopWork(serverFlow, changeAbility);
}

BattleEventHandlerTableEntry ReceiverHandlers[] = {
    {EVENT_NOTIFY_FAINTED, HandlerReceiver},
};


bool IsEmergencyExitBlockedByMoveAbility(ServerFlow* serverFlow)
{
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    BattleMon* attackingMon = GetAbilityBattleMon(serverFlow, attackingSlot);
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    return attackingMon &&
        BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE &&
        IsAffectedBySheerForce(moveID);
}

bool QueueEmergencyExit(ServerFlow* serverFlow, u32 pokemonSlot, bool duringEndTurn)
{
    if (!serverFlow || !serverFlow->mainModule) {
        return false;
    }

    if (MainModule_GetBattleType(serverFlow->mainModule) == BTL_TYPE_WILD) {
        // A Red Card/Eject Button or an already-reserved switch resolves first.
        if (serverFlow->field_78A & 8u) {
            return false;
        }

        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);
        BattleHandler_PushRun(serverFlow, EFFECT_QUIT_BATTLE, pokemonSlot);
        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
        return true;
    }

    if (!Handler_GetFightEnableBenchPokeNum(serverFlow, pokemonSlot) ||
        !Handler_CheckReservedMemberChangeAction(serverFlow)) {
        return false;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);
    HandlerParam_Switch* switchOut =
        (HandlerParam_Switch*)BattleHandler_PushWork(serverFlow, EFFECT_SWITCH, pokemonSlot);
    switchOut->pokeID = (u8)pokemonSlot;
    BattleHandler_PopWork(serverFlow, switchOut);
    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);

    if (duringEndTurn) {
        sEmergencyExitEndTurnSwitchFlag = 1;
    }
    return true;
}

extern "C" void HandlerEmergencyExitDamageCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (!IsTargetSlotInCurrentDamageEvent(pokemonSlot)) {
        return;
    }

    u32 substituteDamage = 0;
    if (pokemonSlot < BATTLE_MAX_SLOTS) {
        substituteDamage = sEmergencyExitSubstituteDamage[pokemonSlot];
        sEmergencyExitSubstituteDamage[pokemonSlot] = 0;
    }
    if (BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon ||
        BattleMon_CheckIfMoveCondition(currentMon, CONDITION_SKYDROP) ||
        IsEmergencyExitBlockedByMoveAbility(serverFlow)) {
        return;
    }

    u32 damage = (u32)BattleEventVar_GetValue(VAR_DAMAGE);
    damage = damage > substituteDamage ? damage - substituteDamage : 0;
    u32 beforeDamageHP = (u32)currentMon->currentHP + damage;
    if (DamageCrossedBelowHalfHPFromBefore(currentMon, beforeDamageHP)) {
        QueueEmergencyExit(serverFlow, pokemonSlot, false);
    }
}

extern "C" void HandlerEmergencyExitSimpleDamageCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (!IsNewEvent() ||
        pokemonSlot != (u32)BattleEventVar_GetValue(NEW_VAR_MON_ID) ||
        pokemonSlot >= BATTLE_MAX_SLOTS) {
        return;
    }

    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!currentMon || BattleMon_CheckIfMoveCondition(currentMon, CONDITION_SKYDROP)) {
        return;
    }

    if (DamageCrossedBelowHalfHPFromBefore(
            currentMon,
            sEmergencyExitSimpleBeforeHP[pokemonSlot])) {
        sEmergencyExitPendingSlots |= 1u << pokemonSlot;
    }
}

extern "C" void HandlerEmergencyExitTurnCheckEnd(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot >= BATTLE_MAX_SLOTS ||
        !(sEmergencyExitPendingSlots & (1u << pokemonSlot))) {
        return;
    }

    sEmergencyExitPendingSlots &= ~(1u << pokemonSlot);
    QueueEmergencyExit(serverFlow, pokemonSlot, true);
}

// Wimp Out and Emergency Exit are mechanically identical. Keep both abilities
// on one handler table so fixes to either activation path cannot diverge.
BattleEventHandlerTableEntry EmergencyExitAndWimpOutHandlers[] = {
    {EVENT_DAMAGE_PROCESSING_END_HIT_2, HandlerEmergencyExitDamageCheck},
    {EVENT_SIMPLE_DAMAGE_REACTION, HandlerEmergencyExitSimpleDamageCheck},
    {EVENT_TURN_CHECK_END, HandlerEmergencyExitTurnCheckEnd},
};


extern "C" void HandlerMoveFlagPowerBoost(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)serverFlow;
    (void)work;
    u32 flagIndex = 0;
    u32 powerRatio = 0;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !GetMoveFlagPowerBoost(GetEventItemAbility(item), &flagIndex, &powerRatio)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (getMoveFlag(moveID, flagIndex)) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, powerRatio);
    }
}

BattleEventHandlerTableEntry MoveFlagPowerBoostHandlers[] = {
    {EVENT_MOVE_POWER, HandlerMoveFlagPowerBoost},
};


extern "C" void HandlerGooey(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        return;
    }

    BattleMon* attackingMon = PokeCon_GetBattleMon(serverFlow->pokeCon, attackingSlot);
    if (!attackingMon ||
        BattleMon_IsFainted(attackingMon) ||
        !BattleMon_IsStatChangeValid(attackingMon, STATSTAGE_SPEED, -1)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_ChangeStatStage* statChange =
        (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_STAT_STAGE,
            pokemonSlot);
    statChange->pokeCount = 1;
    statChange->pokeID[0] = attackingSlot;
    statChange->moveAnimation = 1;
    statChange->stat = STATSTAGE_SPEED;
    statChange->volume = -1;
    BattleHandler_PopWork(serverFlow, statChange);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

BattleEventHandlerTableEntry GooeyHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerGooey},
};


extern "C" void HandlerParentalBondPower(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (!sParentalBondActive || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    ++sParentalBondPowerHit;
    if (sParentalBondPowerHit == 2) {
        sParentalBondPowerHit = 0;
        // Base power is rewrite-once. A move such as Fickle Beam may already
        // own that rewrite; this later event is the multiplicative-power stage.
        // Keep the project's half-power rule and compose with move power.
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_ABILITY_RATIO_HALF);
    }
}

BattleEventHandlerTableEntry ParentalBondHandlers[] = {
    {EVENT_MOVE_POWER, HandlerParentalBondPower},
};


extern "C" void HandlerMegaLauncherHealBoost(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        getMoveFlag((MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID), MOVE_FLAG_INDEX_PULSE)) {
        BattleEventVar_RewriteValue(VAR_RATIO, W2U_ABILITY_MEGA_LAUNCHER_HEAL_RATIO);
    }
}

BattleEventHandlerTableEntry MegaLauncherHandlers[] = {
    {EVENT_MOVE_POWER, HandlerMoveFlagPowerBoost},
    {EVENT_RECOVER_HP, HandlerMegaLauncherHealBoost},
};


extern "C" void HandlerFurCoat(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
        if (PML_MoveGetCategory(moveID) == SPLIT_PHYSICAL) {
            BattleEventVar_MulValue(VAR_RATIO, W2U_ABILITY_RATIO_HALF);
        }
    }
}

BattleEventHandlerTableEntry FurCoatHandlers[] = {
    {EVENT_ATTACKER_POWER, HandlerFurCoat},
};


extern "C" void HandlerBulletProof(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!getMoveFlag(moveID, MOVE_FLAG_INDEX_BULLET)) {
        return;
    }

    if (BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

        HandlerParam_Message* message =
            (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
        BattleHandler_StrSetup(&message->str, W2U_BULLETPROOF_MSG_NARC, W2U_BULLETPROOF_MSG_ID);
        BattleHandler_AddArg(&message->str, pokemonSlot);
        BattleHandler_PopWork(serverFlow, message);

        BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
    }
}

BattleEventHandlerTableEntry BulletProofHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, HandlerBulletProof},
};

// PW2Code's updated Overcoat: preserve the native weather handler and let
// native ability-event skipping (Mold Breaker, etc.) govern powder immunity.
static void HandlerOvercoatPowderMoves(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        getMoveFlag((MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID), MOVE_FLAG_INDEX_POWDER)) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

static BattleEventHandlerTableEntry OvercoatUpdatedHandlers[] = {
    { EVENT_WEATHER_REACTION, HandlerOvercoat },
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerOvercoatPowderMoves },
};


extern "C" void HandlerCompetitive(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!IsEventMon(pokemonSlot)) {
        return;
    }

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (MainModule_IsAllyMonID(pokemonSlot, attackingSlot) ||
        BattleEventVar_GetValue(VAR_VOLUME) >= 0) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_ChangeStatStage* statStageChange =
        (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_STAT_STAGE,
            pokemonSlot);
    statStageChange->stat = STATSTAGE_SPECIAL_ATTACK;
    statStageChange->volume = 2;
    statStageChange->moveAnimation = 1;
    statStageChange->pokeCount = 1;
    statStageChange->pokeID[0] = pokemonSlot;
    BattleHandler_PopWork(serverFlow, statStageChange);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

BattleEventHandlerTableEntry CompetitiveHandlers[] = {
    {EVENT_STAT_STAGE_CHANGE_APPLIED, HandlerCompetitive},
};


extern "C" void HandlerGaleWings(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    if (!battleMon || battleMon->currentHP != battleMon->maxHP) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (moveID && PML_MoveGetType(moveID) == TYPE_FLYING) {
        BattleEventVar_RewriteValue(
            VAR_MOVE_PRIORITY,
            BattleEventVar_GetValue(VAR_MOVE_PRIORITY) + 1);
    }
}

BattleEventHandlerTableEntry GaleWingsHandlers[] = {
    {EVENT_GET_MOVE_PRIORITY, HandlerGaleWings},
};


extern "C" void HandlerCheekPouch(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!IsNewEvent() || pokemonSlot != (u32)BattleEventVar_GetValue(NEW_VAR_MON_ID)) {
        return;
    }

    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    BattleMon* currentMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    ITEM itemID = (ITEM)BattleEventVar_GetValue(VAR_ITEM);
    if (!currentMon ||
        itemID == ITEM_NULL ||
        !PML_ItemIsBerry(itemID) ||
        BattleMon_CheckIfMoveCondition(currentMon, CONDITION_HEALBLOCK) ||
        currentMon->currentHP >= currentMon->maxHP) {
        return;
    }

    HandlerParam_RecoverHP* recoverHP =
        (HandlerParam_RecoverHP*)BattleHandler_PushWork(serverFlow, EFFECT_RECOVER_HP, pokemonSlot);
    recoverHP->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    recoverHP->pokeID = (u8)pokemonSlot;
    recoverHP->recoverHP =
        (u16)DivideMaxHPZeroCheck(currentMon, W2U_CHEEK_POUCH_RECOVER_DENOMINATOR);
    BattleHandler_StrSetup(&recoverHP->exStr, W2U_CHEEK_POUCH_MSG_NARC, W2U_CHEEK_POUCH_MSG_ID);
    BattleHandler_AddArg(&recoverHP->exStr, pokemonSlot);
    BattleHandler_PopWork(serverFlow, recoverHP);
}

BattleEventHandlerTableEntry CheekPouchHandlers[] = {
    {EVENT_CONSUME_ITEM, HandlerCheekPouch},
    {EVENT_USE_TEMP_ITEM_AFTER, HandlerCheekPouch},
};


extern "C" void HandlerSymbiosis(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || !IsNewEvent()) {
        return;
    }

    *work = 0;

    u32 receiveSlot = (u32)BattleEventVar_GetValue(NEW_VAR_MON_ID);
    ITEM itemID = (ITEM)BattleEventVar_GetValue(VAR_ITEM);
    if (IsDamageReductionBerry(itemID)) {
        *work = receiveSlot + 1;
        return;
    }

    SymbiosisChangeItem(serverFlow, pokemonSlot, receiveSlot);
}

extern "C" void HandlerSymbiosisDelayed(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || !*work) {
        return;
    }

    u32 receiveSlot = *work - 1;
    *work = 0;
    if (receiveSlot < BATTLE_MAX_SLOTS) {
        SymbiosisChangeItem(serverFlow, pokemonSlot, receiveSlot);
    }
}

BattleEventHandlerTableEntry SymbiosisHandlers[] = {
    {EVENT_CONSUME_ITEM, HandlerSymbiosis},
    {EVENT_USE_TEMP_ITEM_AFTER, HandlerSymbiosis},
    {EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerSymbiosisDelayed},
};


extern "C" void HandlerProtean(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    BattleMon* currentMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    if (!currentMon) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    // Ability events run before move events. Type-consuming moves must fail
    // before Protean can supply the typing that their prerequisite requires.
    const u16 requiredType = moveID == MOVE_DOUBLE_SHOCK ? TYPE_ELECTRIC : TYPE_FIRE;
    if ((moveID == MOVE_BURN_UP || moveID == MOVE_DOUBLE_SHOCK) &&
        currentMon->Type1 != requiredType &&
        currentMon->Type2 != requiredType) {
        return;
    }

    MoveParam params;
    W2U_ServerEvent_GetMoveParam(
        serverFlow,
        moveID,
        currentMon,
        &params);

    if (params.moveType >= TYPE_NULL) {
        return;
    }

    u16 newType = PokeTypePair_MakeMonotype(params.moveType);
    if (newType == BattleMon_GetPokeType(currentMon)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_ChangeType* changeType =
        (HandlerParam_ChangeType*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_TYPE, pokemonSlot);
    changeType->pokeType = newType;
    changeType->pokeID = (u8)pokemonSlot;
    BattleHandler_PopWork(serverFlow, changeType);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

BattleEventHandlerTableEntry ProteanHandlers[] = {
    {EVENT_MOVE_EXECUTE_CHECK2, HandlerProtean},
};


extern "C" void HandlerMagician(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    if (!serverFlow || !serverFlow->pokeCon || !work || *work) {
        return;
    }

    BattleMon* currentMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
    if (!currentMon || BattleMon_GetHeldItem(currentMon) != ITEM_NULL) {
        return;
    }

    u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    if (targetSlot == BATTLE_MAX_SLOTS) {
        return;
    }

    BattleMon* targetMon = PokeCon_GetBattleMon(serverFlow->pokeCon, targetSlot);
    if (!targetMon) {
        return;
    }

    ITEM heldItem = BattleMon_GetHeldItem(targetMon);
    if (heldItem == ITEM_NULL ||
        HandlerCommon_CheckIfCanStealPokeItem(serverFlow, pokemonSlot, targetSlot)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_SwapItem* swapItem =
        (HandlerParam_SwapItem*)BattleHandler_PushWork(serverFlow, EFFECT_SWAP_ITEM, pokemonSlot);
    swapItem->pokeID = (u8)targetSlot;
    BattleHandler_StrSetup(&swapItem->exStr, W2U_MAGICIAN_MSG_NARC, W2U_MAGICIAN_MSG_ID);
    BattleHandler_AddArg(&swapItem->exStr, pokemonSlot);
    BattleHandler_AddArg(&swapItem->exStr, targetSlot);
    BattleHandler_AddArg(&swapItem->exStr, heldItem);
    BattleHandler_PopWork(serverFlow, swapItem);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

BattleEventHandlerTableEntry MagicianHandlers[] = {
    {EVENT_DAMAGE_PROCESSING_START, HandlerThiefStart},
    {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerMagician},
};


extern "C" void HandlerAuraFamilyAdd(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;
    ABILITY ability = GetEventItemAbility(item);
    if (IsEventMon(pokemonSlot) && AddAuraFamilyOwner(serverFlow, pokemonSlot, ability)) {
        PushAbilityMessage(serverFlow, pokemonSlot, GetAuraFamilyMessageID(ability));
    }
}

extern "C" void HandlerAuraFamilyRemove(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)serverFlow;
    (void)work;
    if (IsEventMon(pokemonSlot)) {
        RemoveAuraFamilyOwner(pokemonSlot, GetEventItemAbility(item));
    }
}

extern "C" void HandlerAuraFamilyRemoveFainted(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;
    if (IsEventMon(pokemonSlot) && EventMonIsFainted(serverFlow, pokemonSlot)) {
        RemoveAuraFamilyOwner(pokemonSlot, GetEventItemAbility(item));
    }
}

BattleEventHandlerTableEntry AuraFamilyHandlers[] = {
    {EVENT_SWITCH_IN, HandlerAuraFamilyAdd},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerAuraFamilyAdd},
    {EVENT_SWITCH_OUT_END, HandlerAuraFamilyRemove},
    {EVENT_BEFORE_ABILITY_CHANGE, HandlerAuraFamilyRemove},
    {EVENT_ABILITY_NULLIFIED, HandlerAuraFamilyRemove},
    {EVENT_NOTIFY_FAINTED, HandlerAuraFamilyRemoveFainted},
};
#endif

#if !defined(W2U_BATTLE_CHILD)
// Resident hooks: these were inside the module-only block above, so the White 2
// dynamic core never installed them (child modules drop unreferenced hooks at
// link time) and EVENT_CONSUME_ITEM never fired there: Cheek Pouch and
// Symbiosis did nothing for a used-up item. Black 2's static build is unchanged.
extern "C" int THUMB_BRANCH_BattleHandler_ConsumeItem(
    ServerFlow* serverFlow,
    HandlerParam_ConsumeItem* params)
{
    u32 pokemonSlot = (params->header.flags >> 8) & 0x1F;
    BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);

    if (!params->dontUse) {
        ServerDisplay_UseHeldItem(serverFlow, battleMon);
        BattleHandler_SetString(serverFlow, &params->exStr);
    }

    ServerControl_ChangeHeldItem(serverFlow, battleMon, ITEM_NULL, 1 + params->dontUse);

    return 1;
}

extern "C" void THUMB_BRANCH_ServerControl_ChangeHeldItem(
    ServerFlow* serverFlow,
    BattleMon* battleMon,
    ITEM itemID,
    b32 consumeItem)
{
    u32 pokemonSlot = BattleMon_GetID(battleMon);
    ITEM usedItem = BattleMon_GetHeldItem(battleMon);

    u32 HEID = HEManager_PushState(&serverFlow->HEManager);
    ServerEvent_ItemSetDecide(serverFlow, battleMon, itemID);
    HEManager_PopState(&serverFlow->HEManager, HEID);

    if (itemID == ITEM_NULL) {
        ServerDisplay_SetConditionFlag(serverFlow, battleMon, CONDITIONFLAG_NULL);
    }

    ItemEvent_RemoveItem(battleMon);
    ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_SetItem, pokemonSlot, itemID);
    BattleMon_SetItem(battleMon, itemID);
    if (itemID != ITEM_NULL) {
        ItemEvent_AddItem(battleMon);
    }

    HEID = HEManager_PushState(&serverFlow->HEManager);
    ServerEvent_ItemRewriteDone(serverFlow, battleMon);
    HEManager_PopState(&serverFlow->HEManager, HEID);

    if (consumeItem) {
        if (consumeItem != 2 && PML_ItemIsBerry(usedItem)) {
            W2U_MoveState_SetConsumedBerryFlag(pokemonSlot);
        }

        BattleMon_ConsumeItem(battleMon, usedItem);
        ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_ConsumeItem, pokemonSlot, usedItem);
        ServerDisplay_SetTurnFlag(serverFlow, battleMon, TURNFLAG_ITEMCONSUMED);

        HEID = HEManager_PushState(&serverFlow->HEManager);
        BattleEventVar_Push();
        SetupNewEventMonAndItem(pokemonSlot, usedItem);
        BattleEvent_CallHandlers(serverFlow, EVENT_CONSUME_ITEM);
        BattleEventVar_Pop();
        HEManager_PopState(&serverFlow->HEManager, HEID);
    }
}
#endif


namespace {

bool IsW2UIgnorableAbility(ABILITY ability)
{
    switch (ability) {
    // Generation VI
    case ABIL_OVERCOAT: // Its powder immunity was added after the native table.
    case ABIL_AURA_BREAK:
    case ABIL_AROMA_VEIL:
    case ABIL_BULLETPROOF:
    case ABIL_DARK_AURA:
    case ABIL_FAIRY_AURA:
    case ABIL_FLOWER_VEIL:
    case ABIL_FUR_COAT:
    case ABIL_GRASS_PELT:
    case ABIL_SWEET_VEIL:
    // Generation VII
    case ABIL_DAZZLING:
    case ABIL_DISGUISE:
    case ABIL_FLUFFY:
    case ABIL_QUEENLY_MAGESTY:
    case ABIL_WATER_BUBBLE:
    // Generation VIII / IX (ported from MegaB2W2; Showdown's `breakable` flag)
    case ABIL_ICE_FACE:
    case ABIL_MIRROR_ARMOR:
    case ABIL_PUNK_ROCK:
    case ABIL_ICE_SCALES:
    case ABIL_PASTEL_VEIL:
    case ABIL_THERMAL_EXCHANGE:
    case ABIL_PURIFYING_SALT:
    case ABIL_WELL_BAKED_BODY:
    case ABIL_WIND_RIDER:
    case ABIL_GUARD_DOG:
    case ABIL_GOOD_AS_GOLD:
    case ABIL_ARMOR_TAIL:
    case ABIL_EARTH_EATER:
    case ABIL_MINDS_EYE:
    case ABIL_TERA_SHELL:
    // MegaB2W2 custom
    case ABIL_AURA_GUARD:
        return true;
    default:
        return false;
    }
}

} // namespace

extern "C" b32 IsMoldBreakerAffectedAbility(ABILITY ability);

extern "C" b32 THUMB_BRANCH_SAFESTACK_HandlerMoldBreakerSkipCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 factorType,
    u32 eventType,
    u32 subID)
{
    (void)item;
    (void)serverFlow;
    (void)eventType;

    // Preserve the native Generation IV/V table and extend it with every
    // implemented later-generation ability that the games define as
    // ignorable. This path is shared by Mold Breaker, Teravolt, Turboblaze,
    // Moongeist Beam, and future moves that reuse the same native window.
    return factorType == 4u &&
        (IsMoldBreakerAffectedAbility((ABILITY)subID) ||
         IsW2UIgnorableAbility((ABILITY)subID));
}


namespace {

#if !defined(W2U_DYNAMIC_BATTLE_CORE) && !defined(W2U_BATTLE_STATIC_GROUPS)
#define W2U_ABILITY_EVENT(ability, handlers) { (u16)W2U_ARRAY_COUNT(handlers), (u16)ability, handlers }

W2UAbilityEventAddTable sAbilityEventAddTable[] = {
    W2U_ABILITY_EVENT(ABIL_AROMA_VEIL, AromaVeilHandlers),
    W2U_ABILITY_EVENT(ABIL_FLOWER_VEIL, FlowerVeilHandlers),
    W2U_ABILITY_EVENT(ABIL_SWEET_VEIL, SweetVeilHandlers),
    W2U_ABILITY_EVENT(ABIL_DARK_AURA, AuraFamilyHandlers),
    W2U_ABILITY_EVENT(ABIL_FAIRY_AURA, AuraFamilyHandlers),
    W2U_ABILITY_EVENT(ABIL_AURA_BREAK, AuraFamilyHandlers),
    W2U_ABILITY_EVENT(ABIL_CHEEK_POUCH, CheekPouchHandlers),
    W2U_ABILITY_EVENT(ABIL_FUR_COAT, FurCoatHandlers),
    W2U_ABILITY_EVENT(ABIL_BULLETPROOF, BulletProofHandlers),
    W2U_ABILITY_EVENT(ABIL_OVERCOAT, OvercoatUpdatedHandlers),
    W2U_ABILITY_EVENT(ABIL_COMPETITIVE, CompetitiveHandlers),
    W2U_ABILITY_EVENT(ABIL_GALE_WINGS, GaleWingsHandlers),
    W2U_ABILITY_EVENT(ABIL_GOOEY, GooeyHandlers),
    W2U_ABILITY_EVENT(ABIL_MAGICIAN, MagicianHandlers),
    W2U_ABILITY_EVENT(ABIL_PARENTAL_BOND, ParentalBondHandlers),
    W2U_ABILITY_EVENT(ABIL_PROTEAN, ProteanHandlers),
    W2U_ABILITY_EVENT(ABIL_SYMBIOSIS, SymbiosisHandlers),
    W2U_ABILITY_EVENT(ABIL_STRONG_JAW, MoveFlagPowerBoostHandlers),
    W2U_ABILITY_EVENT(ABIL_REFRIGERATE, NormalMoveConversionHandlers),
    W2U_ABILITY_EVENT(ABIL_STANCE_CHANGE, StanceChangeHandlers),
    W2U_ABILITY_EVENT(ABIL_MEGA_LAUNCHER, MegaLauncherHandlers),
    W2U_ABILITY_EVENT(ABIL_TOUGH_CLAWS, MoveFlagPowerBoostHandlers),
    W2U_ABILITY_EVENT(ABIL_PIXILATE, NormalMoveConversionHandlers),
    W2U_ABILITY_EVENT(ABIL_AERILATE, NormalMoveConversionHandlers),
    W2U_ABILITY_EVENT(ABIL_STAMINA, StaminaHandlers),
    W2U_ABILITY_EVENT(ABIL_WIMP_OUT, EmergencyExitAndWimpOutHandlers),
    W2U_ABILITY_EVENT(ABIL_EMERGENCY_EXIT, EmergencyExitAndWimpOutHandlers),
    W2U_ABILITY_EVENT(ABIL_WATER_COMPACTION, WaterCompactionHandlers),
    W2U_ABILITY_EVENT(ABIL_MERCILESS, MercilessHandlers),
    W2U_ABILITY_EVENT(ABIL_SHIELDS_DOWN, ShieldsDownHandlers),
    W2U_ABILITY_EVENT(ABIL_SCHOOLING, SchoolingHandlers),
    W2U_ABILITY_EVENT(ABIL_POWER_CONSTRUCT, PowerConstructHandlers),
    W2U_ABILITY_EVENT(ABIL_STAKEOUT, StakeoutHandlers),
    W2U_ABILITY_EVENT(ABIL_WATER_BUBBLE, WaterBubbleHandlers),
    W2U_ABILITY_EVENT(ABIL_STEELWORKER, SteelworkerHandlers),
    W2U_ABILITY_EVENT(ABIL_BERSERK, BerserkHandlers),
    W2U_ABILITY_EVENT(ABIL_SLUSH_RUSH, SlushRushHandlers),
    W2U_ABILITY_EVENT(ABIL_LIQUID_VOICE, LiquidVoiceHandlers),
    W2U_ABILITY_EVENT(ABIL_TRIAGE, TriageHandlers),
    W2U_ABILITY_EVENT(ABIL_GALVANIZE, NormalMoveConversionHandlers),
    W2U_ABILITY_EVENT(ABIL_DRAGONIZE, NormalMoveConversionHandlers),
    W2U_ABILITY_EVENT(ABIL_SURGE_SURFER, SurgeSurferHandlers),
    W2U_ABILITY_EVENT(ABIL_ELECTRIC_SURGE, TerrainSurgeHandlers),
    W2U_ABILITY_EVENT(ABIL_PSYCHIC_SURGE, TerrainSurgeHandlers),
    W2U_ABILITY_EVENT(ABIL_MISTY_SURGE, TerrainSurgeHandlers),
    W2U_ABILITY_EVENT(ABIL_GRASSY_SURGE, TerrainSurgeHandlers),
    W2U_ABILITY_EVENT(ABIL_DISGUISE, DisguiseHandlers),
    W2U_ABILITY_EVENT(ABIL_BATTLE_BOND, BattleBondHandlers),
    W2U_ABILITY_EVENT(ABIL_QUEENLY_MAGESTY, QueenlyMajestyHandlers),
    W2U_ABILITY_EVENT(ABIL_INNARDS_OUT, InnardsOutHandlers),
    W2U_ABILITY_EVENT(ABIL_DANCER, DancerHandlers),
    W2U_ABILITY_EVENT(ABIL_BATTERY, BatteryHandlers),
    W2U_ABILITY_EVENT(ABIL_FLUFFY, FluffyHandlers),
    W2U_ABILITY_EVENT(ABIL_DAZZLING, QueenlyMajestyHandlers),
    W2U_ABILITY_EVENT(ABIL_SOUL_HEART, SoulHeartHandlers),
    W2U_ABILITY_EVENT(ABIL_TANGLING_HAIR, GooeyHandlers),
    W2U_ABILITY_EVENT(ABIL_RECEIVER, ReceiverHandlers),
    W2U_ABILITY_EVENT(ABIL_POWER_OF_ALCHEMY, ReceiverHandlers),
    W2U_ABILITY_EVENT(ABIL_BEAST_BOOST, BeastBoostHandlers),
    W2U_ABILITY_EVENT(ABIL_PRISM_ARMOR, PrismArmorHandlers),
};

#undef W2U_ABILITY_EVENT
#endif

#define W2U_VANILLA_ABILITY_ALIAS(ability, vanillaAbility) { (u16)ability, (u16)vanillaAbility }

W2UVanillaAbilityAliasEventAddTable sVanillaAbilityAliasEventAddTable[] = {
    W2U_VANILLA_ABILITY_ALIAS(ABIL_FULL_METAL_BODY, 29), // Clear Body
    W2U_VANILLA_ABILITY_ALIAS(ABIL_SHADOW_SHIELD, 136), // Multiscale
    W2U_VANILLA_ABILITY_ALIAS(ABIL_CHILLING_NEIGH, 153), // Moxie (Attack +1 after a KO; phase 6)
};

#undef W2U_VANILLA_ABILITY_ALIAS

} // namespace

extern "C" BattleEventItem* THUMB_BRANCH_AbilityEvent_AddItem(BattleMon* battleMon)
{
    ABILITY ability = BattleMon_GetValue(battleMon, VALUE_ABILITY);

#if defined(W2U_DYNAMIC_BATTLE_CORE)
    if (W2U_BattleModules_IsManaged(W2U_MECHANIC_ABILITY, (u16)ability)) {
        const W2UBattleHandlerExport* entry =
            W2U_BattleModules_Resolve(W2U_MECHANIC_ABILITY, (u16)ability);
        if (entry) {
            return AddAbilityEvent(
                battleMon,
                ability,
                const_cast<BattleEventHandlerTableEntry*>(entry->handlers),
                entry->handlerCount);
        }
        // Resolve already logs/caches the failure. Overcoat is an explicit
        // native upgrade: preserve its original weather protection if the
        // child is unavailable. Never fall through for a custom numeric ID.
        if (ability != ABIL_OVERCOAT) return 0;
    }
#elif defined(W2U_BATTLE_STATIC_GROUPS)
    const W2UBattleHandlerExport* entry =
        W2U_BattleStatic_Resolve(W2U_MECHANIC_ABILITY, (u16)ability);
    if (entry) {
        return AddAbilityEvent(
            battleMon,
            ability,
            const_cast<BattleEventHandlerTableEntry*>(entry->handlers),
            entry->handlerCount);
    }
#else
    for (u32 i = 0; i < W2U_ARRAY_COUNT(sAbilityEventAddTable); ++i) {
        W2UAbilityEventAddTable* eventAdd = &sAbilityEventAddTable[i];
        if (ability == eventAdd->ability) {
            return AddAbilityEvent(battleMon, ability, eventAdd->handlers, eventAdd->handlerAmount);
        }
    }
#endif

    AbilityEventAddTable* vanillaTable = W2U_VANILLA_ABILITY_EVENT_TABLE;
    for (u32 aliasIdx = 0; aliasIdx < W2U_ARRAY_COUNT(sVanillaAbilityAliasEventAddTable); ++aliasIdx) {
        W2UVanillaAbilityAliasEventAddTable* alias = &sVanillaAbilityAliasEventAddTable[aliasIdx];
        if (ability != alias->ability) {
            continue;
        }

        for (u32 i = 0; i < W2U_VANILLA_ABILITY_EVENT_TABLE_COUNT; ++i) {
            AbilityEventAddTable* eventAdd = &vanillaTable[i];
            if (alias->vanillaAbility == eventAdd->ability) {
                return GetAbilityEvent(battleMon, ability, eventAdd->func);
            }
        }
    }

    for (u32 i = 0; i < W2U_VANILLA_ABILITY_EVENT_TABLE_COUNT; ++i) {
        AbilityEventAddTable* eventAdd = &vanillaTable[i];
        if (ability == eventAdd->ability) {
            return GetAbilityEvent(battleMon, ability, eventAdd->func);
        }
    }

    return 0;
}

#define W2U_BATTLE_API_SOURCE_ABILITIES
#include "w2u_battle_module_api_entries.inc"
#undef W2U_BATTLE_API_SOURCE_ABILITIES
