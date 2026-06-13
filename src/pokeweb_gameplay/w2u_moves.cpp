#include "w2u_moves.h"
#include "w2u_field_effects.h"
#include "Types.h"

#define W2U_MOVE_EVENT_TABLE ((MoveEventAddTable*)0x021DA0F4)
#define W2U_MOVE_EVENT_TABLE_COUNT 258u
#define W2U_POS_EVENT_TABLE ((PosEffectEventAddTable*)0x0689D850)
#define W2U_POS_EVENT_TABLE_COUNT 5u

#define W2U_FIRST_BATTLE_ANIMATION_ID 561u
#define W2U_BATTLE_ANIMATIONS_COUNT 115u
#define W2U_NULL_BATTLE_POS 6u
#define W2U_SIDE_COUNT 2u
#define W2U_SIDE_SLOT_COUNT 3u
#define W2U_TERRAIN_TURNS 5u
#define W2U_TERRAIN_POWER_RATIO 5325
#define W2U_RATIO_HALF 2048
#define W2U_ALL_BATTLE_SLOT_FLAGS 0x7FFFFFFFu

#define W2U_FLDEFF_GRAVITY 2u
#define W2U_FLDEFF_IMPRISON 3u
#define W2U_FLDEFF_TRANSIENT_MOVE_STATE 11u

#define W2U_EFFECTIVENESS_1_4 1u
#define W2U_EFFECTIVENESS_4 5u
#define W2U_EFFECTIVENESS_1_8 6u
#define W2U_EFFECTIVENESS_8 7u

#define W2U_EFFECT_COUNTER ((BattleHandlerEffect)0x26)
#define W2U_COUNTER_PROTECT 0x03u
#define W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET 0x38u

struct Btlv_StringParam {
    u16 strID;
    u8 wait;
    u8 strTypeAndArgCount;
    u32 args[8];
};

struct BtlClientWk {
    MainModule* mainModule;
    PokeCon* pokeCon;
};

typedef BattleEventHandlerTableEntry* (*MoveEventAddFunc)(u32* handlerAmount);
typedef BattleEventHandlerTableEntry* (*PosEffectEventAddFunc)(u32* handlerAmount);

struct MoveEventAddTable {
    MOVE_ID moveID;
    MoveEventAddFunc func;
};

struct PosEffectEventAddTable {
    POS_EFFECT posEffect;
    PosEffectEventAddFunc func;
};

struct W2UMoveEventAddTable {
    u16 handlerAmount;
    u16 moveID;
    BattleEventHandlerTableEntry* handlers;
};

struct W2UMoveEventAliasTable {
    u16 moveID;
    MoveEventAddFunc func;
};

struct W2UPosEffectEventAddTable {
    u8 handlerAmount;
    u8 priority;
    u16 posEffect;
    BattleEventHandlerTableEntry* handlers;
};

struct HandlerParam_SetCounter {
    HandlerParam_Header header;
    u8 pokeID;
    u8 counterID;
    u8 value;
};

struct StickyWebSideState {
    BattleEventItem* item;
    bool active;
};

struct TerrainState {
    BattleEventItem* item;
    TERRAIN terrain;
    u8 turns;
    bool active;
};

struct MoveState {
    StickyWebSideState stickyWeb[W2U_SIDE_COUNT];
    TerrainState terrain;
    BattleEventItem* transientItem;
    u32 consumedBerryFlags;
    u32 electrifiedFlags;
    u32 matBlockProtectedFlags;
    u32 powderedFlags;
    u32 spikyShieldFlags;
    u32 spikyShieldDamagedFlags;
    u32 kingsShieldFlags;
    u32 kingsShieldLoweredFlags;
    bool ionDelugeActive;
    u32 matBlockFreshFlags;
    u32 matBlockEnteredThisTurnFlags;
    bool matBlockActive[W2U_SIDE_COUNT];
    bool craftyShieldActive[W2U_SIDE_COUNT];
    u8 matBlockOwner[W2U_SIDE_COUNT];
    u8 craftyShieldOwner[W2U_SIDE_COUNT];
    u8 extraTypes[BATTLE_MAX_SLOTS];
};

extern "C" b32 MoveEvent_CanEffectBeRegistered(u32 pokemonSlot, MOVE_ID moveID, u8* alreadyRegistered);
extern "C" b32 PosEffectEvent_CanEffectBeRegistered(POS_EFFECT posEffect, u32 targetPos);
extern "C" void BattleEventItem_SetWorkValue(BattleEventItem* item, u32 idx, u32 value);
extern "C" u32 MainModule_BattlePosToViewPos(MainModule* mainModule, u32 battlePos);
extern "C" void CMD_ACT_MoveAnimStart(
    BtlvScu* btlvScu,
    u32 attackingViewPos,
    u32 targetViewPos,
    u16 moveID,
    u32 moveTarget,
    u8 effectIndex,
    u8 zero);

extern "C" void HandlerProtectCheckFail(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerProtectResetCounter(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerProtectStart(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerProtect(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void IncrementProtectCounter(ServerFlow* serverFlow, u32 pokemonSlot, u32 checkFail);
extern "C" void HandlerBypassSubstitute(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerPosTurnCheckDone(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work);
extern "C" void HandlerPosProtectBroken(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work);
extern "C" BattleEventHandlerTableEntry* EventAddShadowForce(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddSpiderWeb(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddFalseSwipe(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddBind(u32* handlerAmount);

extern "C" void Condition_CheckUnaffectedByType(ServerFlow* serverFlow, BattleMon* defendingMon);
extern "C" b32 Move_IsUsable(BattleMon* battleMon, MOVE_ID moveID);
extern "C" b32 BattleField_CheckEffect(FIELD_EFFECT fieldEffect);
extern "C" b32 BattleField_CheckImprison(PokeCon* pokeCon, BattleMon* battleMon, MOVE_ID moveID);
extern "C" MOVE_ID BattleMon_GetPreviousMove(BattleMon* battleMon);
extern "C" MOVE_ID BattleMon_GetConditionAffectedMove(BattleMon* battleMon, CONDITION condition);
extern "C" void Btlv_StringParam_Setup(Btlv_StringParam* strParam, u8 narcIdx, u16 msgIdx);
extern "C" void Btlv_StringParam_AddArg(Btlv_StringParam* strParam, u32 value);

namespace {

MoveState sMoveState;

void ClearMoveState()
{
    volatile u8* bytes = (volatile u8*)&sMoveState;
    for (u32 idx = 0; idx < sizeof(sMoveState); ++idx) {
        bytes[idx] = 0;
    }
}

void InitExtraTypes()
{
    volatile u8* extraTypes = (volatile u8*)sMoveState.extraTypes;
    for (u32 idx = 0; idx < BATTLE_MAX_SLOTS; ++idx) {
        extraTypes[idx] = TYPE_NULL;
    }
}

void InitLocalMoveState()
{
    InitExtraTypes();
    sMoveState.matBlockFreshFlags = W2U_ALL_BATTLE_SLOT_FLAGS;
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        sMoveState.matBlockOwner[side] = BATTLE_MAX_SLOTS;
        sMoveState.craftyShieldOwner[side] = BATTLE_MAX_SLOTS;
    }
}

bool IsValidSlot(u32 pokemonSlot)
{
    return pokemonSlot < BATTLE_MAX_SLOTS;
}

u32 SlotMask(u32 pokemonSlot)
{
    if (pokemonSlot >= 32u) {
        return 0;
    }
    return 1u << pokemonSlot;
}

bool IsNotNewEvent()
{
    return BattleEventVar_GetValue(VAR_MON_ID) != -1 ||
        BattleEventVar_GetValue(VAR_ATTACKING_MON) != -1 ||
        BattleEventVar_GetValue(VAR_DEFENDING_MON) != -1;
}

void SetupNewEvent()
{
    BattleEventVar_SetConstValue(VAR_MON_ID, -1);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, -1);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, -1);
}

BattleMon* GetBattleMon(ServerFlow* serverFlow, u32 pokemonSlot)
{
    if (!serverFlow || !serverFlow->pokeCon || !IsValidSlot(pokemonSlot)) {
        return 0;
    }
    return PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonSlot);
}

bool IsGrounded(ServerFlow* serverFlow, BattleMon* battleMon)
{
    return battleMon && !ServerControl_CheckFloating(serverFlow, battleMon, 1);
}

bool HasTypeWithExtra(BattleMon* battleMon, u32 pokeType)
{
    if (!battleMon || pokeType == TYPE_NULL) {
        return false;
    }

    return battleMon->Type1 == pokeType ||
        battleMon->Type2 == pokeType ||
        W2U_MoveState_GetExtraType(battleMon->battleSlot) == pokeType;
}

bool IsDamagingMove(MOVE_ID moveID)
{
    u32 category = PML_MoveGetCategory(moveID);
    return category == SPLIT_PHYSICAL || category == SPLIT_SPECIAL;
}

void PushMessage(ServerFlow* serverFlow, u32 pokemonSlot, u32 narcID, u32 msgID)
{
    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, narcID, msgID);
    BattleHandler_PopWork(serverFlow, message);
}

void PushMessageArg(ServerFlow* serverFlow, u32 pokemonSlot, u32 narcID, u32 msgID, u32 arg)
{
    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, narcID, msgID);
    BattleHandler_AddArg(&message->str, arg);
    BattleHandler_PopWork(serverFlow, message);
}

void PushMessageArgs(ServerFlow* serverFlow, u32 pokemonSlot, u32 narcID, u32 msgID, u32 arg1, u32 arg2)
{
    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, narcID, msgID);
    BattleHandler_AddArg(&message->str, arg1);
    BattleHandler_AddArg(&message->str, arg2);
    BattleHandler_PopWork(serverFlow, message);
}

void PushDamage(ServerFlow* serverFlow, u32 sourceSlot, u32 targetSlot, u32 damageAmount, u32 msgID, u32 arg)
{
    HandlerParam_Damage* damage =
        (HandlerParam_Damage*)BattleHandler_PushWork(serverFlow, EFFECT_DAMAGE, sourceSlot);
    damage->damage = (u16)damageAmount;
    damage->pokeID = (u8)targetSlot;
    if (msgID) {
        BattleHandler_StrSetup(&damage->exStr, 2u, msgID);
        BattleHandler_AddArg(&damage->exStr, arg);
    }
    BattleHandler_PopWork(serverFlow, damage);
}

MOVE_ID GetEventItemMove(BattleEventItem* item)
{
    if (!item) {
        return MOVE_NONE;
    }
    return (MOVE_ID)*(u16*)((u8*)item + W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET);
}

void SetNoEffectMessageArg(u32 msgID, u32 arg)
{
    HandlerParam_StrParams* str =
        (HandlerParam_StrParams*)BattleEventVar_GetValue(VAR_WORK_ADDRESS);
    if (!str) {
        return;
    }

    BattleHandler_StrSetup(str, 2u, msgID);
    BattleHandler_AddArg(str, arg);
}

bool IsPoisoned(BattleMon* battleMon)
{
    return battleMon && BattleMon_GetStatus(battleMon) == CONDITION_POISON;
}

bool HasPlusMinusAbility(BattleMon* battleMon)
{
    if (!battleMon) {
        return false;
    }

    u32 ability = BattleMon_GetValue(battleMon, VALUE_EFFECTIVE_ABILITY);
    return ability == ABIL_PLUS || ability == ABIL_MINUS;
}

bool IsProtectCounterMove(MOVE_ID moveID)
{
    switch (moveID) {
    case MOVE_PROTECT:
    case MOVE_DETECT:
    case MOVE_ENDURE:
    case MOVE_WIDE_GUARD:
    case MOVE_QUICK_GUARD:
    case MOVE_KINGS_SHIELD:
    case MOVE_SPIKY_SHIELD:
        return true;
    default:
        return false;
    }
}

void ResetProtectCounter(ServerFlow* serverFlow, u32 pokemonSlot)
{
    HandlerParam_SetCounter* setCounter =
        (HandlerParam_SetCounter*)BattleHandler_PushWork(serverFlow, W2U_EFFECT_COUNTER, pokemonSlot);
    setCounter->pokeID = (u8)pokemonSlot;
    setCounter->counterID = W2U_COUNTER_PROTECT;
    setCounter->value = 0;
    BattleHandler_PopWork(serverFlow, setCounter);
}

void StartProtectCounterMove(ServerFlow* serverFlow, u32 pokemonSlot)
{
    BattleMon* currentMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!currentMon || IsProtectCounterMove(BattleMon_GetPreviousMove(currentMon))) {
        return;
    }

    ResetProtectCounter(serverFlow, pokemonSlot);
}

bool TryApplySpikyShieldDamage(ServerFlow* serverFlow, u32 defendingSlot, u32 attackingSlot, MOVE_ID moveID)
{
    if (!(sMoveState.spikyShieldFlags & SlotMask(defendingSlot)) ||
        !IsValidSlot(attackingSlot) ||
        MainModule_IsAllyMonID(attackingSlot, defendingSlot) ||
        !getMoveFlag(moveID, MOVE_FLAG_INDEX_CONTACT) ||
        (sMoveState.spikyShieldDamagedFlags & SlotMask(attackingSlot))) {
        return false;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (!attackingMon || BattleMon_IsFainted(attackingMon)) {
        return false;
    }

    sMoveState.spikyShieldDamagedFlags |= SlotMask(attackingSlot);
    PushDamage(
        serverFlow,
        defendingSlot,
        attackingSlot,
        DivideMaxHPZeroCheck(attackingMon, 8),
        BATTLE_SPIKY_SHIELD_DAMAGE_MSGID,
        attackingSlot);
    return true;
}

void SetHappyHourMoneyDouble(MainModule* mainModule)
{
    if (!mainModule) {
        return;
    }

    // fMoneyDblUp is bit 6 of the flag byte in BTL_MAIN_MODULE.
    ((u8*)mainModule)[0x473] |= 0x40;
}

void CureMoveCondition(ServerFlow* serverFlow, u32 pokemonSlot, CONDITION condition)
{
    HandlerParam_CureCondition* cure =
        (HandlerParam_CureCondition*)BattleHandler_PushWork(serverFlow, EFFECT_CURE_STATUS, pokemonSlot);
    cure->condition = condition;
    cure->pokeCount = 1;
    cure->pokeID[0] = (u8)pokemonSlot;
    BattleHandler_PopWork(serverFlow, cure);
}

void SetRemoveSideEffectFlag(SIDE_EFFECT sideEffect, u8* flags)
{
    flags[(sideEffect >> 3) + 1] |= 1 << (sideEffect & 7);
}

void RemoveSideEffects(ServerFlow* serverFlow, u32 pokemonSlot, u32 side, const SIDE_EFFECT* effects, u32 effectCount)
{
    HandlerParam_RemoveSideEffect* removeSide =
        (HandlerParam_RemoveSideEffect*)BattleHandler_PushWork(serverFlow, EFFECT_REMOVE_SIDE_EFFECT, pokemonSlot);
    removeSide->flags[0] = 3;
    removeSide->flags[1] = 0;
    removeSide->flags[2] = 0;
    removeSide->side = (u8)side;
    for (u32 idx = 0; idx < effectCount; ++idx) {
        SetRemoveSideEffectFlag(effects[idx], removeSide->flags);
    }
    BattleHandler_PopWork(serverFlow, removeSide);
}

bool RemoveStickyWebSide(ServerFlow* serverFlow, u32 pokemonSlot, u32 side, bool showMessage)
{
    if (side >= W2U_SIDE_COUNT || !sMoveState.stickyWeb[side].active) {
        return false;
    }

    if (sMoveState.stickyWeb[side].item) {
        BattleEventItem_Remove(sMoveState.stickyWeb[side].item);
    }
    sMoveState.stickyWeb[side].item = 0;
    sMoveState.stickyWeb[side].active = false;

    if (showMessage) {
        PushMessage(serverFlow, pokemonSlot, 1u, BATTLE_STICKY_WEB_REMOVE_MSGID + side);
    }
    return true;
}

u32 EffectivenessPowerMod(u32 damage, u32 effectiveness)
{
    volatile u32 checkedEffectiveness = effectiveness;
    if (checkedEffectiveness == RESULT_NOT_EFFECTIVE) {
        return 0;
    }
    if (checkedEffectiveness == W2U_EFFECTIVENESS_1_8) {
        return damage >> 3;
    }
    if (checkedEffectiveness == W2U_EFFECTIVENESS_1_4) {
        return damage >> 2;
    }
    if (checkedEffectiveness == RESULT_NOT_VERY_EFFECTIVE) {
        return damage >> 1;
    }
    if (checkedEffectiveness == RESULT_SUPER_EFFECTIVE) {
        return damage * 2;
    }
    if (checkedEffectiveness == W2U_EFFECTIVENESS_4) {
        return damage * 4;
    }
    if (checkedEffectiveness == W2U_EFFECTIVENESS_8) {
        return damage * 8;
    }
    return damage;
}

u32 EffectivenessScaledMultiplier(u32 effectiveness)
{
    if (effectiveness == RESULT_NOT_EFFECTIVE) {
        return 0;
    }
    if (effectiveness == W2U_EFFECTIVENESS_1_8) {
        return 1;
    }
    if (effectiveness == W2U_EFFECTIVENESS_1_4) {
        return 2;
    }
    if (effectiveness == RESULT_NOT_VERY_EFFECTIVE) {
        return 4;
    }
    if (effectiveness == RESULT_EFFECTIVE) {
        return 8;
    }
    if (effectiveness == RESULT_SUPER_EFFECTIVE) {
        return 16;
    }
    if (effectiveness == W2U_EFFECTIVENESS_4) {
        return 32;
    }
    if (effectiveness == W2U_EFFECTIVENESS_8) {
        return 64;
    }
    return 0xFFFFFFFFu;
}

BattleEventItem* AddTransientMoveStateEvent(u32 pokemonSlot);
BattleEventItem* AddTerrainEvent(u32 pokemonSlot);
bool SetTerrain(ServerFlow* serverFlow, u32 pokemonSlot, TERRAIN terrain, u32 msgID)
{
    if (sMoveState.terrain.active && sMoveState.terrain.terrain == terrain) {
        return false;
    }

    W2U_MoveState_RemoveTerrain(serverFlow);

    BattleEventItem* item = AddTerrainEvent(pokemonSlot);
    if (!item) {
        return false;
    }

    sMoveState.terrain.item = item;
    sMoveState.terrain.terrain = terrain;
    sMoveState.terrain.turns = W2U_TERRAIN_TURNS;
    sMoveState.terrain.active = true;

    PushMessage(serverFlow, pokemonSlot, 2u, msgID);
    return true;
}

void CommonTerrainMove(ServerFlow* serverFlow, u32 pokemonSlot, TERRAIN terrain, u32 msgID)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        SetTerrain(serverFlow, pokemonSlot, terrain, msgID);
    }
}

void CommonExtraType(ServerFlow* serverFlow, u32 pokemonSlot, u32 pokeType)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (targetMon && !BattleMon_IsFainted(targetMon) && !HasTypeWithExtra(targetMon, pokeType)) {
            W2U_MoveState_SetExtraType(targetSlot, pokeType);
            PushMessageArgs(serverFlow, pokemonSlot, 2u, BATTLE_EXTRA_TYPE_MSGID, pokeType, targetSlot);
        }
    }
}

s8 ReverseStatStageValue(BattleMon* battleMon, BattleMonValue statStage)
{
    return (s8)(12 - (s8)BattleMon_GetValue(battleMon, statStage));
}

void PushReverseStatStages(ServerFlow* serverFlow, u32 sourceSlot, u32 targetSlot, BattleMon* targetMon)
{
    HandlerParam_SetStatStage* setStages =
        (HandlerParam_SetStatStage*)BattleHandler_PushWork(serverFlow, EFFECT_SET_STAT_STAGE, sourceSlot);
    setStages->pokeID = (u8)targetSlot;
    setStages->attack = ReverseStatStageValue(targetMon, VALUE_ATTACK_STAGE);
    setStages->defense = ReverseStatStageValue(targetMon, VALUE_DEFENSE_STAGE);
    setStages->specialAttack = ReverseStatStageValue(targetMon, VALUE_SPECIAL_ATTACK_STAGE);
    setStages->specialDefense = ReverseStatStageValue(targetMon, VALUE_SPECIAL_DEFENSE_STAGE);
    setStages->speed = ReverseStatStageValue(targetMon, VALUE_SPEED_STAGE);
    setStages->accuracy = ReverseStatStageValue(targetMon, VALUE_ACCURACY_STAGE);
    setStages->evasion = ReverseStatStageValue(targetMon, VALUE_EVASION_STAGE);
    BattleHandler_PopWork(serverFlow, setStages);
}

void ClearMatBlockState()
{
    sMoveState.matBlockProtectedFlags = 0;
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        sMoveState.matBlockActive[side] = false;
        sMoveState.matBlockOwner[side] = BATTLE_MAX_SLOTS;
    }
}

void ClearCraftyShieldState()
{
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        sMoveState.craftyShieldActive[side] = false;
        sMoveState.craftyShieldOwner[side] = BATTLE_MAX_SLOTS;
    }
}

void SetMatBlockFresh(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMoveState.matBlockFreshFlags |= mask;
        sMoveState.matBlockEnteredThisTurnFlags |= mask;
    }
}

bool IsMatBlockFresh(ServerFlow* serverFlow, u32 pokemonSlot)
{
    BattleMon* battleMon = GetBattleMon(serverFlow, pokemonSlot);
    return serverFlow && battleMon && battleMon->appearedTurn == (u16)serverFlow->turnCount;
}

void ClearEndOfTurnMoveState()
{
    ClearMatBlockState();
    ClearCraftyShieldState();
    W2U_MoveState_ClearElectrified();
    sMoveState.powderedFlags = 0;
    sMoveState.spikyShieldFlags = 0;
    sMoveState.spikyShieldDamagedFlags = 0;
    sMoveState.kingsShieldFlags = 0;
    sMoveState.kingsShieldLoweredFlags = 0;
    sMoveState.ionDelugeActive = false;
    sMoveState.matBlockFreshFlags &= sMoveState.matBlockEnteredThisTurnFlags;
    sMoveState.matBlockEnteredThisTurnFlags = 0;
}

bool HasTransientMoveState()
{
    if (sMoveState.electrifiedFlags ||
        sMoveState.matBlockProtectedFlags ||
        sMoveState.powderedFlags ||
        sMoveState.spikyShieldFlags ||
        sMoveState.kingsShieldFlags ||
        sMoveState.ionDelugeActive) {
        return true;
    }
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        if (sMoveState.matBlockActive[side] || sMoveState.craftyShieldActive[side]) {
            return true;
        }
    }
    return false;
}

bool IsTerrainActive(TERRAIN terrain)
{
    return sMoveState.terrain.active && sMoveState.terrain.terrain == terrain;
}

void TerrainCureSleep(ServerFlow* serverFlow, u32 pokemonSlot)
{
    BattleMon* battleMon = GetBattleMon(serverFlow, pokemonSlot);
    if (IsTerrainActive(TERRAIN_ELECTRIC) &&
        battleMon &&
        BattleMon_CheckIfMoveCondition(battleMon, CONDITION_SLEEP) &&
        IsGrounded(serverFlow, battleMon)) {
        CureMoveCondition(serverFlow, pokemonSlot, CONDITION_SLEEP);
    }
}

BattleEventPriority PosEffect_GetPriority(u32* handlerAmount)
{
    u16 eventPriority = (u16)((*handlerAmount & 0xFFFF0000) >> 16);
    if (eventPriority != 0) {
        *handlerAmount &= 0x0000FFFF;
        return (BattleEventPriority)eventPriority;
    }
    return EVENTPRI_POS_DEFAULT;
}

BattleEventItem* AddMoveEvent(
    BattleMon* battleMon,
    MOVE_ID moveID,
    u32 speed,
    BattleEventHandlerTableEntry* handlers,
    u32 handlerAmount)
{
    if (!battleMon || !handlers || handlerAmount == 0) {
        return 0;
    }

    u32 battleSlot = BattleMon_GetID(battleMon);
    u8 alreadyRegistered = 0;
    if (!MoveEvent_CanEffectBeRegistered(battleSlot, moveID, &alreadyRegistered)) {
        return 0;
    }

    return BattleEvent_AddItem(
        EVENTITEM_MOVE,
        (u16)moveID,
        EVENTPRI_MOVE_DEFAULT,
        speed,
        battleSlot,
        handlers,
        (u16)handlerAmount);
}

BattleEventItem* GetMoveEvent(BattleMon* battleMon, MOVE_ID moveID, u32 speed, MoveEventAddFunc func)
{
    if (!func) {
        return 0;
    }

    u32 handlerAmount = 0;
    BattleEventHandlerTableEntry* handlers = func(&handlerAmount);
    return AddMoveEvent(battleMon, moveID, speed, handlers, handlerAmount);
}

BattleEventItem* AddPosEffectEvent(
    POS_EFFECT posEffect,
    u32 targetPos,
    BattleEventHandlerTableEntry* handlers,
    u32 handlerAmount,
    BattleEventPriority mainPriority,
    u8 workCount,
    u32* work)
{
    if (!handlers || handlerAmount == 0 || !PosEffectEvent_CanEffectBeRegistered(posEffect, targetPos)) {
        return 0;
    }

    BattleEventItem* item = BattleEvent_AddItem(
        EVENTITEM_POS,
        (u16)posEffect,
        mainPriority,
        0,
        targetPos,
        handlers,
        (u16)handlerAmount);
    if (!item) {
        return 0;
    }

    for (u32 idx = 0; idx < workCount; ++idx) {
        BattleEventItem_SetWorkValue(item, idx, work ? work[idx] : 0);
    }
    return item;
}

BattleEventItem* GetPosEffectEvent(
    POS_EFFECT posEffect,
    u32 targetPos,
    PosEffectEventAddFunc func,
    u8 workCount,
    u32* work)
{
    if (!func) {
        return 0;
    }

    u32 handlerAmount = 0;
    BattleEventHandlerTableEntry* handlers = func(&handlerAmount);
    BattleEventPriority mainPriority = PosEffect_GetPriority(&handlerAmount);
    return AddPosEffectEvent(posEffect, targetPos, handlers, handlerAmount, mainPriority, workCount, work);
}

bool EnsureTransientMoveStateEvent(u32 pokemonSlot)
{
    if (sMoveState.transientItem) {
        return true;
    }

    sMoveState.transientItem = AddTransientMoveStateEvent(pokemonSlot);
    return sMoveState.transientItem != 0;
}

void RemoveTransientMoveStateEvent()
{
    if (sMoveState.transientItem) {
        BattleEventItem_Remove(sMoveState.transientItem);
    }
    sMoveState.transientItem = 0;
}

void SetMatBlockForActiveSide(ServerFlow* serverFlow, u32 ownerSlot, u32 side)
{
    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    sMoveState.matBlockActive[side] = true;
    sMoveState.matBlockOwner[side] = (u8)ownerSlot;

    for (u32 idx = 0; idx < 24u; ++idx) {
        BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, idx);
        if (!battleMon || BattleMon_IsFainted(battleMon)) {
            continue;
        }

        u32 allySlot = BattleMon_GetID(battleMon);
        if (allySlot >= BATTLE_MAX_SLOTS || GetSideFromMonID(allySlot) != side) {
            continue;
        }

        u32 allyPos = Handler_PokeIDToPokePos(serverFlow, allySlot);
        if (allyPos < W2U_NULL_BATTLE_POS) {
            sMoveState.matBlockProtectedFlags |= SlotMask(allySlot);
        }
    }
}

void ApplyStatChange(ServerFlow* serverFlow, u32 currentSlot, u32 targetSlot, StatStage stat, s8 volume, bool moveAnimation)
{
    HandlerParam_ChangeStatStage* statChange =
        (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_STAT_STAGE, currentSlot);
    statChange->pokeCount = 1;
    statChange->pokeID[0] = (u8)targetSlot;
    statChange->stat = stat;
    statChange->volume = volume;
    statChange->moveAnimation = moveAnimation ? 1 : 0;
    BattleHandler_PopWork(serverFlow, statChange);
}

bool TryApplyKingsShieldAttackDrop(ServerFlow* serverFlow, u32 defendingSlot, u32 attackingSlot, MOVE_ID moveID)
{
    if (!(sMoveState.kingsShieldFlags & SlotMask(defendingSlot)) ||
        !IsValidSlot(attackingSlot) ||
        MainModule_IsAllyMonID(attackingSlot, defendingSlot) ||
        !getMoveFlag(moveID, MOVE_FLAG_INDEX_CONTACT) ||
        (sMoveState.kingsShieldLoweredFlags & SlotMask(attackingSlot))) {
        return false;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (!attackingMon ||
        BattleMon_IsFainted(attackingMon) ||
        !BattleMon_IsStatChangeValid(attackingMon, STATSTAGE_ATTACK, -1)) {
        return false;
    }

    sMoveState.kingsShieldLoweredFlags |= SlotMask(attackingSlot);
    ApplyStatChange(serverFlow, defendingSlot, attackingSlot, STATSTAGE_ATTACK, -2, true);
    return true;
}

void ApplyStatChangeToTargets(
    ServerFlow* serverFlow,
    u32 currentSlot,
    StatStage stat,
    s8 volume,
    bool moveAnimation,
    const u8* targetSlots,
    u8 targetCount)
{
    if (!targetCount) {
        return;
    }

    HandlerParam_ChangeStatStage* statChange =
        (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_STAT_STAGE, currentSlot);
    statChange->pokeCount = targetCount;
    for (u8 idx = 0; idx < targetCount; ++idx) {
        statChange->pokeID[idx] = targetSlots[idx];
    }
    statChange->stat = stat;
    statChange->volume = volume;
    statChange->moveAnimation = moveAnimation ? 1 : 0;
    BattleHandler_PopWork(serverFlow, statChange);
}

u8 GetActivePlusMinusAllies(ServerFlow* serverFlow, u32 pokemonSlot, u8* targetSlots, u8 targetSlotCapacity)
{
    if (!serverFlow || !serverFlow->pokeCon || !targetSlots || !targetSlotCapacity) {
        return 0;
    }

    u32 side = GetSideFromMonID(pokemonSlot);
    u8 targetCount = 0;
    for (u32 idx = 0; idx < 24u && targetCount < targetSlotCapacity; ++idx) {
        BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, idx);
        if (!battleMon || BattleMon_IsFainted(battleMon) || !HasPlusMinusAbility(battleMon)) {
            continue;
        }

        u32 allySlot = BattleMon_GetID(battleMon);
        if (allySlot >= BATTLE_MAX_SLOTS || GetSideFromMonID(allySlot) != side) {
            continue;
        }

        u32 allyPos = Handler_PokeIDToPokePos(serverFlow, allySlot);
        if (allyPos < W2U_NULL_BATTLE_POS) {
            targetSlots[targetCount++] = (u8)allySlot;
        }
    }
    return targetCount;
}

void SetTurnFlag(ServerFlow* serverFlow, u32 currentSlot, u32 targetSlot, TURN_FLAG flag, BattleHandlerEffect effect)
{
    HandlerParam_SetTurnFlag* setTurnFlag =
        (HandlerParam_SetTurnFlag*)BattleHandler_PushWork(serverFlow, effect, currentSlot);
    setTurnFlag->pokeID = (u8)targetSlot;
    setTurnFlag->flag = flag;
    BattleHandler_PopWork(serverFlow, setTurnFlag);
}

} // namespace

extern "C" void W2U_MoveState_ResetBattleState()
{
    ClearMoveState();
    InitLocalMoveState();
}

extern "C" void W2U_MoveState_SetConsumedBerryFlag(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMoveState.consumedBerryFlags |= mask;
    }
}

extern "C" bool W2U_MoveState_HasConsumedBerryFlag(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    return mask && (sMoveState.consumedBerryFlags & mask);
}

extern "C" void W2U_MoveState_SetExtraType(u32 pokemonSlot, u32 pokeType)
{
    if (IsValidSlot(pokemonSlot)) {
        sMoveState.extraTypes[pokemonSlot] = (u8)pokeType;
    }
}

extern "C" void W2U_MoveState_ClearExtraType(u32 pokemonSlot)
{
    if (IsValidSlot(pokemonSlot)) {
        sMoveState.extraTypes[pokemonSlot] = TYPE_NULL;
    }
}

extern "C" u32 W2U_MoveState_GetExtraType(u32 pokemonSlot)
{
    if (!IsValidSlot(pokemonSlot)) {
        return TYPE_NULL;
    }
    return sMoveState.extraTypes[pokemonSlot];
}

extern "C" void W2U_MoveState_SetElectrified(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMoveState.electrifiedFlags |= mask;
    }
}

extern "C" bool W2U_MoveState_IsElectrified(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    return mask && (sMoveState.electrifiedFlags & mask);
}

void ClearElectrifiedSlot(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMoveState.electrifiedFlags &= ~mask;
    }
}

extern "C" void W2U_MoveState_ClearElectrified()
{
    sMoveState.electrifiedFlags = 0;
}

extern "C" TERRAIN W2U_MoveState_GetTerrain()
{
    return sMoveState.terrain.active ? sMoveState.terrain.terrain : TERRAIN_NULL;
}

extern "C" bool W2U_MoveState_RemoveTerrain(ServerFlow* serverFlow)
{
    if (!sMoveState.terrain.active) {
        return false;
    }

    if (sMoveState.terrain.item) {
        BattleEventItem_Remove(sMoveState.terrain.item);
    }

    sMoveState.terrain.item = 0;
    sMoveState.terrain.terrain = TERRAIN_NULL;
    sMoveState.terrain.turns = 0;
    sMoveState.terrain.active = false;

    if (serverFlow) {
        PushMessage(serverFlow, BATTLE_MAX_SLOTS, 2u, BATTLE_TERRAIN_END_MSGID);
    }
    return true;
}

extern "C" bool W2U_MoveState_RemoveStickyWebSide(u32 side)
{
    return RemoveStickyWebSide(0, BATTLE_MAX_SLOTS, side, false);
}

extern "C" void HandlerRapidSpin(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!currentMon) {
        return;
    }

    if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_LEECHSEED)) {
        CureMoveCondition(serverFlow, pokemonSlot, CONDITION_LEECHSEED);
    }
    if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_BIND)) {
        CureMoveCondition(serverFlow, pokemonSlot, CONDITION_BIND);
    }

    SIDE_EFFECT hazards[] = { SIDEEFF_SPIKES, SIDEEFF_TOXIC_SPIKES, SIDEEFF_STEALTH_ROCK, SIDEEFF_STICKY_WEB };
    u32 side = GetSideFromMonID(pokemonSlot);
    RemoveSideEffects(serverFlow, pokemonSlot, side, hazards, W2U_ARRAY_COUNT(hazards));
    RemoveStickyWebSide(serverFlow, pokemonSlot, side, true);
}

BattleEventHandlerTableEntry RapidSpinHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerRapidSpin },
};


extern "C" void HandlerDefog(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (targetMon && !BattleMon_IsSubstituteActive(targetMon)) {
        ApplyStatChange(serverFlow, pokemonSlot, targetSlot, STATSTAGE_EVASION, -1, true);
    }

    SIDE_EFFECT allyHazards[] = { SIDEEFF_SPIKES, SIDEEFF_TOXIC_SPIKES, SIDEEFF_STEALTH_ROCK, SIDEEFF_STICKY_WEB };
    SIDE_EFFECT enemyEffects[] = {
        SIDEEFF_REFLECT,
        SIDEEFF_LIGHT_SCREEN,
        SIDEEFF_SAFEGUARD,
        SIDEEFF_MIST,
        SIDEEFF_SPIKES,
        SIDEEFF_TOXIC_SPIKES,
        SIDEEFF_STEALTH_ROCK,
        SIDEEFF_STICKY_WEB,
    };

    u32 allySide = GetSideFromMonID(pokemonSlot);
    u32 enemySide = targetSlot < BATTLE_MAX_SLOTS ? GetSideFromMonID(targetSlot) : (allySide ^ 1);
    RemoveSideEffects(serverFlow, pokemonSlot, allySide, allyHazards, W2U_ARRAY_COUNT(allyHazards));
    RemoveSideEffects(serverFlow, pokemonSlot, enemySide, enemyEffects, W2U_ARRAY_COUNT(enemyEffects));
    RemoveStickyWebSide(serverFlow, pokemonSlot, allySide, true);
    RemoveStickyWebSide(serverFlow, pokemonSlot, enemySide, true);
    W2U_MoveState_RemoveTerrain(serverFlow);

    HandlerParam_RemoveFieldEffect* removeField =
        (HandlerParam_RemoveFieldEffect*)BattleHandler_PushWork(serverFlow, EFFECT_REMOVE_FIELD_EFFECT, pokemonSlot);
    removeField->effect = FLDEFF_TERRAIN;
    BattleHandler_PopWork(serverFlow, removeField);
}

BattleEventHandlerTableEntry DefogHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerDefog },
    { EVENT_BYPASS_SUBSTITUTE, HandlerBypassSubstitute },
};


extern "C" void HandlerFlyingPress(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        u32 effectiveness = GetTypeEffectiveness(TYPE_FLYING, (u32)BattleEventVar_GetValue(VAR_POKE_TYPE));
        BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, COMPOUND_EFFECTIVENESS + effectiveness);
    }
}

BattleEventHandlerTableEntry FlyingPressHandlers[] = {
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerFlyingPress },
};


extern "C" void HandlerMatBlock(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    if (!IsMatBlockFresh(serverFlow, pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    u32 side = GetSideFromMonID(pokemonSlot);
    if (side >= W2U_SIDE_COUNT || !EnsureTransientMoveStateEvent(pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    SetMatBlockForActiveSide(serverFlow, pokemonSlot, side);
    PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_MAT_BLOCK_MSGID, pokemonSlot);
}

extern "C" void HandlerMatBlockCheckFail(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        !IsMatBlockFresh(serverFlow, pokemonSlot)) {
        u32 failed = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        if (work) {
            *work = failed;
        }
    }
}

extern "C" void HandlerPosMatBlock(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)item;
    (void)work;
    u32 pokemonSlot = Handler_PokePosToPokeID(serverFlow, targetPos);
    if (pokemonSlot >= BATTLE_MAX_SLOTS) {
        return;
    }

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (defendingSlot == pokemonSlot &&
        defendingSlot != attackingSlot &&
        !MainModule_IsAllyMonID(attackingSlot, defendingSlot) &&
        IsDamagingMove(moveID) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT) &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        PushMessageArg(serverFlow, pokemonSlot, 2u, 523u, defendingSlot);
    }
}

extern "C" void HandlerMatBlockSwitchIn(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    SetMatBlockFresh((u32)BattleEventVar_GetValue(VAR_MON_ID));
}

extern "C" void HandlerMatBlockTurnCheckDone(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MON_ID) == BATTLE_MAX_SLOTS) {
        ClearEndOfTurnMoveState();
    }
}

extern "C" void HandlerMatBlockProtectBroken(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (IsNotNewEvent()) {
        return;
    }

    u32 defendingSlot = (u32)BattleEventVar_GetValue(NEW_VAR_DEFENDING_MON);
    if (MainModule_IsAllyMonID(pokemonSlot, defendingSlot)) {
        SetTurnFlag(serverFlow, pokemonSlot, defendingSlot, TURNFLAG_PROTECT, EFFECT_RESET_TURN_FLAG);
        PushMessageArg(serverFlow, pokemonSlot, 2u, 526u, defendingSlot);
    }
}

BattleEventHandlerTableEntry MatBlockHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerMatBlockCheckFail },
    { EVENT_UNCATEGORIZED_MOVE_NO_TARGET, HandlerMatBlock },
};


BattleEventHandlerTableEntry PosMatBlockHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerPosMatBlock },
    { EVENT_TURN_CHECK_DONE, HandlerPosTurnCheckDone },
    { EVENT_PROTECT_BROKEN, HandlerPosProtectBroken },
};


extern "C" void HandlerRototiller(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* defendingMon = GetBattleMon(serverFlow, defendingSlot);
    if (!defendingMon || !HasTypeWithExtra(defendingMon, TYPE_GRASS) || !IsGrounded(serverFlow, defendingMon)) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry RototillerHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerRototiller },
};


extern "C" void HandlerSideStickyWeb(BattleEventItem* item, ServerFlow* serverFlow, u32 side, u32* work)
{
    (void)item;
    (void)work;
    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (side != GetSideFromMonID(currentSlot)) {
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, currentSlot);
    if (!IsGrounded(serverFlow, currentMon)) {
        return;
    }

    PushMessageArg(serverFlow, currentSlot, 2u, BATTLE_STICKY_WEB_EFFECT_MSGID, currentSlot);
    ApplyStatChange(serverFlow, currentSlot, currentSlot, STATSTAGE_SPEED, -1, true);
}

BattleEventHandlerTableEntry SideStickyWebHandlers[] = {
    { EVENT_SWITCH_IN, HandlerSideStickyWeb },
};

extern "C" void HandlerStickyWeb(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 side = GetSideFromOpposingMonID(pokemonSlot);
    if (side >= W2U_SIDE_COUNT || sMoveState.stickyWeb[side].active) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    BattleEventItem* sideItem = BattleEvent_AddItem(
        EVENTITEM_SIDE,
        SIDEEFF_STICKY_WEB,
        EVENTPRI_SIDE_DEFAULT,
        0,
        side,
        SideStickyWebHandlers,
        (u16)W2U_ARRAY_COUNT(SideStickyWebHandlers));
    if (!sideItem) {
        return;
    }

    sMoveState.stickyWeb[side].item = sideItem;
    sMoveState.stickyWeb[side].active = true;
    PushMessage(serverFlow, pokemonSlot, 1u, BATTLE_STICKY_WEB_USE_MSGID + side);
}

BattleEventHandlerTableEntry StickyWebHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE_NO_TARGET, HandlerStickyWeb },
};


extern "C" void HandlerFellStinger(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (targetMon && BattleMon_IsFainted(targetMon)) {
            ApplyStatChange(serverFlow, pokemonSlot, pokemonSlot, STATSTAGE_ATTACK, 2, false);
            return;
        }
    }
}

BattleEventHandlerTableEntry FellStingerHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerFellStinger },
};


extern "C" void HandlerTrickOrTreat(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    CommonExtraType(serverFlow, pokemonSlot, TYPE_GHOST);
}

BattleEventHandlerTableEntry TrickOrTreatHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerTrickOrTreat },
};


extern "C" void HandlerForestsCurse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    CommonExtraType(serverFlow, pokemonSlot, TYPE_GRASS);
}

BattleEventHandlerTableEntry ForestsCurseHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerForestsCurse },
};


extern "C" void HandlerPosIonDeluge(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)targetPos;
    (void)work;
    if (IsNotNewEvent() && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ELECTRIC);
    }
}

extern "C" void HandlerPosTurnCheckDone(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)serverFlow;
    (void)targetPos;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MON_ID) == BATTLE_MAX_SLOTS) {
        W2U_MoveState_ClearElectrified();
        BattleEventItem_Remove(item);
    }
}

BattleEventHandlerTableEntry PosIonDelugeHandlers[] = {
    { EVENT_MOVE_PARAM, HandlerPosIonDeluge },
    { EVENT_TURN_CHECK_DONE, HandlerPosTurnCheckDone },
};


extern "C" void HandlerIonDeluge(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        if (!EnsureTransientMoveStateEvent(pokemonSlot)) {
            BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            return;
        }
        sMoveState.ionDelugeActive = true;
        PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_ION_DELUGE_MSGID);
    }
}

BattleEventHandlerTableEntry IonDelugeHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerIonDeluge },
};


extern "C" void HandlerFreezeDry(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_POKE_TYPE) == TYPE_WATER) {
        BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, OVERRIDE_EFFECTIVENESS_2);
    }
}

BattleEventHandlerTableEntry FreezeDryHandlers[] = {
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerFreezeDry },
};


extern "C" void HandlerPartingShotCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        BattleEventVar_RewriteValue(VAR_PARTING_SHOT_FLAG, 1);
    }
}

extern "C" void HandlerPartingShotApply(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        work[0] = 1;
    }
}

extern "C" void HandlerPartingShotFail(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    if (BattleEventVar_GetValue(VAR_PARTING_SHOT_FLAG) &&
        BattleEventVar_GetValue(VAR_MIRROR_ARMOR_FLAG)) {
        work[0] = 1;
    }
}

extern "C" void HandlerPartingShot(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        work[0] == 1 &&
        Handler_GetFightEnableBenchPokeNum(serverFlow, pokemonSlot) &&
        Handler_CheckReservedMemberChangeAction(serverFlow)) {
        HandlerParam_Switch* switchOut =
            (HandlerParam_Switch*)BattleHandler_PushWork(serverFlow, EFFECT_SWITCH, pokemonSlot);
        switchOut->pokeID = (u8)pokemonSlot;
        BattleHandler_PopWork(serverFlow, switchOut);
    }
}

BattleEventHandlerTableEntry PartingShotHandlers[] = {
    { EVENT_STAT_STAGE_CHANGE_LAST_CHECK, HandlerPartingShotCheck },
    { EVENT_STAT_STAGE_CHANGE_APPLIED, HandlerPartingShotApply },
    { EVENT_STAT_STAGE_CHANGE_FAIL, HandlerPartingShotFail },
    { EVENT_MOVE_SEQUENCE_END, HandlerPartingShot },
};


extern "C" void HandlerTopsyTurvy(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (targetMon && !BattleMon_IsFainted(targetMon)) {
            PushReverseStatStages(serverFlow, pokemonSlot, targetSlot, targetMon);
            PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_TOPSY_TURVY_MSGID);
        }
    }
}

BattleEventHandlerTableEntry TopsyTurvyHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerTopsyTurvy },
};


extern "C" void HandlerPosProtectBroken(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)work;
    if (IsNotNewEvent()) {
        return;
    }

    u32 pokemonSlot = Handler_PokePosToPokeID(serverFlow, targetPos);
    u32 defendingSlot = (u32)BattleEventVar_GetValue(NEW_VAR_DEFENDING_MON);
    if (MainModule_IsAllyMonID(pokemonSlot, defendingSlot)) {
        BattleEventItem_Remove(item);
    }
}

extern "C" void HandlerPosCraftyShield(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)item;
    (void)work;
    u32 pokemonSlot = Handler_PokePosToPokeID(serverFlow, targetPos);
    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (defendingSlot != attackingSlot &&
        !MainModule_IsAllyMonID(attackingSlot, defendingSlot) &&
        MainModule_IsAllyMonID(pokemonSlot, defendingSlot) &&
        PML_MoveGetCategory((MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID)) == SPLIT_STATUS) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
        PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_CRAFTY_SHIELD_EFFECT_MSGID, defendingSlot);
    }
}

BattleEventHandlerTableEntry PosCraftyShieldHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerPosCraftyShield },
    { EVENT_TURN_CHECK_DONE, HandlerPosTurnCheckDone },
    { EVENT_PROTECT_BROKEN, HandlerPosProtectBroken },
};


extern "C" void HandlerCraftyShield(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        u32 side = GetSideFromMonID(pokemonSlot);
        if (side < W2U_SIDE_COUNT && EnsureTransientMoveStateEvent(pokemonSlot)) {
            sMoveState.craftyShieldActive[side] = true;
            sMoveState.craftyShieldOwner[side] = (u8)pokemonSlot;
        }
        PushMessage(serverFlow, pokemonSlot, 1u, BATTLE_CRAFTY_SHIELD_USE_MSGID + side);
    }
}

BattleEventHandlerTableEntry CraftyShieldHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE_NO_TARGET, HandlerCraftyShield },
};


extern "C" void HandlerGrassyTerrain(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    CommonTerrainMove(serverFlow, pokemonSlot, TERRAIN_GRASSY, BATTLE_GRASSY_TERRAIN_MSGID);
}

BattleEventHandlerTableEntry GrassyTerrainHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerGrassyTerrain },
};


extern "C" void HandlerMistyTerrain(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    CommonTerrainMove(serverFlow, pokemonSlot, TERRAIN_MISTY, BATTLE_MISTY_TERRAIN_MSGID);
}

BattleEventHandlerTableEntry MistyTerrainHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerMistyTerrain },
};


extern "C" void HandlerPosElectrify(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)item;
    (void)work;
    u32 pokemonSlot = Handler_PokePosToPokeID(serverFlow, targetPos);
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ELECTRIC);
    }
}

extern "C" void HandlerPosElectrifyMoveSequenceEnd(BattleEventItem* item, ServerFlow* serverFlow, u32 targetPos, u32* work)
{
    (void)work;
    u32 pokemonSlot = Handler_PokePosToPokeID(serverFlow, targetPos);
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        ClearElectrifiedSlot(pokemonSlot);
        BattleEventItem_Remove(item);
    }
}

BattleEventHandlerTableEntry PosElectrifyHandlers[] = {
    { EVENT_MOVE_PARAM, HandlerPosElectrify },
    { EVENT_MOVE_SEQUENCE_END, HandlerPosElectrifyMoveSequenceEnd },
    { EVENT_TURN_CHECK_DONE, HandlerPosTurnCheckDone },
};


extern "C" void HandlerFieldTransientMoveStateNoEffect(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!IsValidSlot(defendingSlot) || !IsValidSlot(attackingSlot) || attackingSlot == defendingSlot) {
        return;
    }
    if (MainModule_IsAllyMonID(attackingSlot, defendingSlot)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    BattleMon* defendingMon = GetBattleMon(serverFlow, defendingSlot);
    if ((sMoveState.spikyShieldFlags & SlotMask(defendingSlot)) &&
        defendingMon &&
        BattleMon_GetTurnFlag(defendingMon, TURNFLAG_PROTECT) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT) &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        SetNoEffectMessageArg(523u, defendingSlot);
        TryApplySpikyShieldDamage(serverFlow, defendingSlot, attackingSlot, moveID);
        return;
    }

    if ((sMoveState.matBlockProtectedFlags & SlotMask(defendingSlot)) &&
        IsDamagingMove(moveID) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT) &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        SetNoEffectMessageArg(523u, defendingSlot);
        return;
    }

    u32 defendingSide = GetSideFromMonID(defendingSlot);
    if (defendingSide < W2U_SIDE_COUNT &&
        sMoveState.craftyShieldActive[defendingSide] &&
        PML_MoveGetCategory(moveID) == SPLIT_STATUS &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        SetNoEffectMessageArg(BATTLE_CRAFTY_SHIELD_EFFECT_MSGID, defendingSlot);
    }
}

extern "C" void HandlerFieldTransientMoveStateMoveParam(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (W2U_MoveState_IsElectrified(currentSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ELECTRIC);
    } else if (sMoveState.ionDelugeActive && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ELECTRIC);
    }
}

extern "C" void HandlerFieldTransientMoveStateMoveExecuteCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;

    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (!(sMoveState.powderedFlags & SlotMask(currentSlot))) {
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, currentSlot);
    if (!currentMon) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    MoveParam params;
    THUMB_BRANCH_ServerEvent_GetMoveParam(serverFlow, moveID, currentMon, &params);
    if (params.moveType != TYPE_FIRE) {
        return;
    }

    u32 failed = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_NO_REACTION);
    if (work) {
        work[0] = failed;
    }

    sMoveState.powderedFlags &= ~SlotMask(currentSlot);
    BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    PushDamage(
        serverFlow,
        currentSlot,
        currentSlot,
        DivideMaxHPZeroCheck(currentMon, 4),
        BATTLE_POWDER_EXPLODE_MSGID,
        currentSlot);
}

extern "C" void HandlerFieldTransientMoveStateProtectSuccess(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (IsNotNewEvent()) {
        return;
    }

    u32 defendingSlot = (u32)BattleEventVar_GetValue(NEW_VAR_DEFENDING_MON);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(NEW_VAR_ATTACKING_MON);
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    TryApplySpikyShieldDamage(serverFlow, defendingSlot, attackingSlot, moveID);
    TryApplyKingsShieldAttackDrop(serverFlow, defendingSlot, attackingSlot, moveID);
}

extern "C" void HandlerFieldTransientMoveStateMoveSequenceEnd(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    ClearElectrifiedSlot(attackingSlot);
    sMoveState.powderedFlags &= ~SlotMask(attackingSlot);
    sMoveState.spikyShieldDamagedFlags &= ~SlotMask(attackingSlot);
    sMoveState.kingsShieldLoweredFlags &= ~SlotMask(attackingSlot);
    if (!HasTransientMoveState()) {
        RemoveTransientMoveStateEvent();
    }
}

extern "C" void HandlerFieldTransientMoveStateTurnCheckDone(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

    if (BattleEventVar_GetValue(VAR_MON_ID) == BATTLE_MAX_SLOTS) {
        ClearEndOfTurnMoveState();
        RemoveTransientMoveStateEvent();
    }
}

BattleEventHandlerTableEntry FieldTransientMoveStateHandlers[] = {
    { EVENT_MOVE_PARAM, HandlerFieldTransientMoveStateMoveParam },
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerFieldTransientMoveStateMoveExecuteCheck },
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerFieldTransientMoveStateNoEffect },
    { EVENT_PROTECT_SUCCESS, HandlerFieldTransientMoveStateProtectSuccess },
    { EVENT_MOVE_SEQUENCE_END, HandlerFieldTransientMoveStateMoveSequenceEnd },
    { EVENT_TURN_CHECK_DONE, HandlerFieldTransientMoveStateTurnCheckDone },
};

namespace {

BattleEventItem* AddTransientMoveStateEvent(u32 pokemonSlot)
{
    return BattleEvent_AddItem(
        EVENTITEM_FIELD,
        W2U_FLDEFF_TRANSIENT_MOVE_STATE,
        EVENTPRI_ABILITY_STALL,
        0,
        pokemonSlot,
        FieldTransientMoveStateHandlers,
        (u16)W2U_ARRAY_COUNT(FieldTransientMoveStateHandlers));
}

} // namespace

extern "C" void HandlerElectrify(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (targetMon && !BattleMon_GetTurnFlag(targetMon, TURNFLAG_MOVEPROCDONE)) {
        if (EnsureTransientMoveStateEvent(pokemonSlot)) {
            W2U_MoveState_SetElectrified(targetSlot);
            PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_ELECTRIFY_MSGID, targetSlot);
        }
    }
}

extern "C" void HandlerElectrifyTurnCheckDone(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MON_ID) == BATTLE_MAX_SLOTS) {
        W2U_MoveState_ClearElectrified();
    }
}

BattleEventHandlerTableEntry ElectrifyHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerElectrify },
    { EVENT_TURN_CHECK_DONE, HandlerElectrifyTurnCheckDone },
};


extern "C" void HandlerProtectLikeShield(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    MOVE_ID moveID = GetEventItemMove(item);
    if (moveID == MOVE_KINGS_SHIELD) {
        if (EnsureTransientMoveStateEvent(pokemonSlot)) {
            sMoveState.kingsShieldFlags |= SlotMask(pokemonSlot);
        }
    } else if (moveID == MOVE_SPIKY_SHIELD) {
        if (EnsureTransientMoveStateEvent(pokemonSlot)) {
            sMoveState.spikyShieldFlags |= SlotMask(pokemonSlot);
        }
    }

    StartProtectCounterMove(serverFlow, pokemonSlot);
}

BattleEventHandlerTableEntry ProtectLikeShieldHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerProtectLikeShield },
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerProtectCheckFail },
    { EVENT_MOVE_EXECUTE_FAIL, HandlerProtectResetCounter },
    { EVENT_UNCATEGORIZED_MOVE, HandlerProtect },
};


extern "C" void HandlerElectricTerrain(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    CommonTerrainMove(serverFlow, pokemonSlot, TERRAIN_ELECTRIC, BATTLE_ELECTRIC_TERRAIN_MSGID);
}

BattleEventHandlerTableEntry ElectricTerrainHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerElectricTerrain },
};


extern "C" void HandlerGeomancyChargeStart(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_GEOMANCY_MSGID, pokemonSlot);
    }
}

BattleEventHandlerTableEntry GeomancyHandlers[] = {
    { EVENT_CHARGE_UP_START, HandlerGeomancyChargeStart },
};


extern "C" void HandlerHappyHour(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        SetHappyHourMoneyDouble(serverFlow ? serverFlow->mainModule : 0);
        PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_HAPPY_HOUR_MSGID);
    }
}

BattleEventHandlerTableEntry HappyHourHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerHappyHour },
};


extern "C" void HandlerMagneticFlux(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* defendingMon = GetBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (!HasPlusMinusAbility(defendingMon)) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

extern "C" void HandlerMagneticFluxApply(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u8 targetSlots[6];
    u8 boostTargetCount = GetActivePlusMinusAllies(serverFlow, pokemonSlot, targetSlots, W2U_ARRAY_COUNT(targetSlots));
    if (!boostTargetCount) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    ApplyStatChangeToTargets(serverFlow, pokemonSlot, STATSTAGE_DEFENSE, 1, true, targetSlots, boostTargetCount);
    ApplyStatChangeToTargets(serverFlow, pokemonSlot, STATSTAGE_SPECIAL_DEFENSE, 1, true, targetSlots, boostTargetCount);
}

BattleEventHandlerTableEntry MagneticFluxHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerMagneticFluxApply },
};


extern "C" void HandlerPowder(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    if (!EnsureTransientMoveStateEvent(pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    bool covered = false;
    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (targetMon && !BattleMon_IsFainted(targetMon)) {
            sMoveState.powderedFlags |= SlotMask(targetSlot);
            PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_POWDER_COVER_MSGID, targetSlot);
            covered = true;
        }
    }

    if (!covered) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    }
}

BattleEventHandlerTableEntry PowderHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerPowder },
};


extern "C" void HandlerVenomDrench(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    BattleMon* defendingMon = GetBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (!IsPoisoned(defendingMon)) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry VenomDrenchHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerVenomDrench },
};


extern "C" void HandlerTerrainPreventStatus(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    TERRAIN terrain = W2U_MoveState_GetTerrain();
    if (terrain != TERRAIN_ELECTRIC && terrain != TERRAIN_MISTY) {
        return;
    }

    BattleMon* defendingMon = GetBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (!IsGrounded(serverFlow, defendingMon)) {
        return;
    }

    CONDITION condition = (CONDITION)BattleEventVar_GetValue(VAR_CONDITION_ID);
    bool blocked = false;
    if (terrain == TERRAIN_ELECTRIC) {
        blocked = condition == CONDITION_SLEEP || condition == CONDITION_YAWN;
    } else if (terrain == TERRAIN_MISTY) {
        blocked = condition == CONDITION_PARALYSIS ||
            condition == CONDITION_SLEEP ||
            condition == CONDITION_FREEZE ||
            condition == CONDITION_BURN ||
            condition == CONDITION_POISON ||
            condition == CONDITION_CONFUSION ||
            condition == CONDITION_YAWN;
    }

    if (blocked) {
        work[0] = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    }
}

extern "C" void HandlerTerrainStatusFailMessage(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    if (!work[0]) {
        return;
    }

    TERRAIN terrain = W2U_MoveState_GetTerrain();
    u32 msgID = terrain == TERRAIN_MISTY ? BATTLE_MISTY_TERRAIN_STATUS_MSGID : BATTLE_ELECTRIC_TERRAIN_STATUS_MSGID;
    PushMessageArg(serverFlow, BATTLE_MAX_SLOTS, 2u, msgID, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
}

extern "C" void HandlerElectricTerrainCheckSleep(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (IsTerrainActive(TERRAIN_ELECTRIC) &&
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        IsGrounded(serverFlow, GetBattleMon(serverFlow, pokemonSlot))) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    }
}

extern "C" void HandlerElectricTerrainSwitchIn(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    TerrainCureSleep(serverFlow, (u32)BattleEventVar_GetValue(VAR_MON_ID));
}

extern "C" void HandlerElectricTerrainNewMon(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (!IsNotNewEvent()) {
        TerrainCureSleep(serverFlow, (u32)BattleEventVar_GetValue(NEW_VAR_MON_ID));
    }
}

extern "C" void HandlerGrassyTerrainHeal(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (!IsTerrainActive(TERRAIN_GRASSY)) {
        return;
    }

    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    BattleMon* currentMon = GetBattleMon(serverFlow, currentSlot);
    if (currentMon && IsGrounded(serverFlow, currentMon) && currentMon->currentHP < currentMon->maxHP) {
        HandlerParam_RecoverHP* recover =
            (HandlerParam_RecoverHP*)BattleHandler_PushWork(serverFlow, EFFECT_RECOVER_HP, currentSlot);
        recover->pokeID = (u8)currentSlot;
        recover->recoverHP = DivideMaxHPZeroCheck(currentMon, 16);
        BattleHandler_StrSetup(&recover->exStr, 2u, 387u);
        BattleHandler_AddArg(&recover->exStr, currentSlot);
        BattleHandler_PopWork(serverFlow, recover);
    }
}

extern "C" void HandlerGrassyTerrainQuakeMoves(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (!IsTerrainActive(TERRAIN_GRASSY)) {
        return;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (moveID == MOVE_EARTHQUAKE || moveID == MOVE_MAGNITUDE || moveID == MOVE_BULLDOZE) {
        BattleMon* defendingMon = GetBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
        if (IsGrounded(serverFlow, defendingMon)) {
            BattleEventVar_RewriteValue(VAR_MOVE_POWER, BattleEventVar_GetValue(VAR_MOVE_POWER) / 2);
        }
    }
}

extern "C" void HandlerTerrainPower(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    TERRAIN terrain = W2U_MoveState_GetTerrain();
    u32 moveType = (u32)BattleEventVar_GetValue(VAR_MOVE_TYPE);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (!IsGrounded(serverFlow, attackingMon)) {
        return;
    }

    if ((terrain == TERRAIN_ELECTRIC && moveType == TYPE_ELECTRIC) ||
        (terrain == TERRAIN_GRASSY && moveType == TYPE_GRASS)) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_TERRAIN_POWER_RATIO);
    }
}

extern "C" void HandlerMistyTerrainDragonGuard(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (!IsTerrainActive(TERRAIN_MISTY) || BattleEventVar_GetValue(VAR_MOVE_TYPE) != TYPE_DRAGON) {
        return;
    }

    BattleMon* defendingMon = GetBattleMon(serverFlow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (IsGrounded(serverFlow, defendingMon)) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_RATIO_HALF);
    }
}

extern "C" void HandlerTerrainTurnCheckDone(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MON_ID) != BATTLE_MAX_SLOTS || !sMoveState.terrain.active) {
        return;
    }

    if (sMoveState.terrain.turns > 0) {
        --sMoveState.terrain.turns;
    }
    if (sMoveState.terrain.turns == 0) {
        W2U_MoveState_RemoveTerrain(serverFlow);
    }
}

BattleEventHandlerTableEntry FieldTerrainHandlers[] = {
    { EVENT_ADD_CONDITION_CHECK_FAIL, HandlerTerrainPreventStatus },
    { EVENT_ADD_CONDITION_FAIL, HandlerTerrainStatusFailMessage },
    { EVENT_CHECK_SLEEP, HandlerElectricTerrainCheckSleep },
    { EVENT_AFTER_TERRAIN_CHANGE, HandlerElectricTerrainNewMon },
    { EVENT_SWITCH_IN, HandlerElectricTerrainSwitchIn },
    { EVENT_ACTION_PROCESSING_END, HandlerElectricTerrainSwitchIn },
    { EVENT_ITEM_REWRITE_DONE, HandlerElectricTerrainSwitchIn },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerElectricTerrainSwitchIn },
    { EVENT_GROUNDED_BY_GRAVITY, HandlerElectricTerrainNewMon },
    { EVENT_TURN_CHECK_BEGIN, HandlerGrassyTerrainHeal },
    { EVENT_MOVE_BASE_POWER, HandlerGrassyTerrainQuakeMoves },
    { EVENT_MOVE_POWER, HandlerTerrainPower },
    { EVENT_DEFENDER_GUARD, HandlerMistyTerrainDragonGuard },
    { EVENT_TURN_CHECK_DONE, HandlerTerrainTurnCheckDone },
};

namespace {

BattleEventItem* AddTerrainEvent(u32 pokemonSlot)
{
    return BattleEvent_AddItem(
        EVENTITEM_FIELD,
        FLDEFF_TERRAIN,
        EVENTPRI_FIELD_DEFAULT,
        0,
        pokemonSlot,
        FieldTerrainHandlers,
        (u16)W2U_ARRAY_COUNT(FieldTerrainHandlers));
}

#define W2U_MOVE_EVENT(move, handlers) { (u16)W2U_ARRAY_COUNT(handlers), (u16)move, handlers }
#define W2U_POS_EVENT(posEffect, handlers, priority) \
    { (u8)W2U_ARRAY_COUNT(handlers), (u8)priority, (u16)posEffect, handlers }

const W2UMoveEventAddTable W2U_MOVE_EVENT_ADD_TABLE[] = {
    W2U_MOVE_EVENT(MOVE_RAPID_SPIN, RapidSpinHandlers),
    W2U_MOVE_EVENT(MOVE_DEFOG, DefogHandlers),
    W2U_MOVE_EVENT(MOVE_FLYING_PRESS, FlyingPressHandlers),
    W2U_MOVE_EVENT(MOVE_MAT_BLOCK, MatBlockHandlers),
    W2U_MOVE_EVENT(MOVE_ROTOTILLER, RototillerHandlers),
    W2U_MOVE_EVENT(MOVE_STICKY_WEB, StickyWebHandlers),
    W2U_MOVE_EVENT(MOVE_FELL_STINGER, FellStingerHandlers),
    W2U_MOVE_EVENT(MOVE_TRICKORTREAT, TrickOrTreatHandlers),
    W2U_MOVE_EVENT(MOVE_ION_DELUGE, IonDelugeHandlers),
    W2U_MOVE_EVENT(MOVE_FORESTS_CURSE, ForestsCurseHandlers),
    W2U_MOVE_EVENT(MOVE_FREEZEDRY, FreezeDryHandlers),
    W2U_MOVE_EVENT(MOVE_PARTING_SHOT, PartingShotHandlers),
    W2U_MOVE_EVENT(MOVE_TOPSYTURVY, TopsyTurvyHandlers),
    W2U_MOVE_EVENT(MOVE_CRAFTY_SHIELD, CraftyShieldHandlers),
    W2U_MOVE_EVENT(MOVE_FLOWER_SHIELD, RototillerHandlers),
    W2U_MOVE_EVENT(MOVE_GRASSY_TERRAIN, GrassyTerrainHandlers),
    W2U_MOVE_EVENT(MOVE_MISTY_TERRAIN, MistyTerrainHandlers),
    W2U_MOVE_EVENT(MOVE_SPIKY_SHIELD, ProtectLikeShieldHandlers),
    W2U_MOVE_EVENT(MOVE_VENOM_DRENCH, VenomDrenchHandlers),
    W2U_MOVE_EVENT(MOVE_POWDER, PowderHandlers),
    W2U_MOVE_EVENT(MOVE_GEOMANCY, GeomancyHandlers),
    W2U_MOVE_EVENT(MOVE_MAGNETIC_FLUX, MagneticFluxHandlers),
    W2U_MOVE_EVENT(MOVE_HAPPY_HOUR, HappyHourHandlers),
    W2U_MOVE_EVENT(MOVE_ELECTRIFY, ElectrifyHandlers),
    W2U_MOVE_EVENT(MOVE_KINGS_SHIELD, ProtectLikeShieldHandlers),
    W2U_MOVE_EVENT(MOVE_ELECTRIC_TERRAIN, ElectricTerrainHandlers),
};

const W2UMoveEventAliasTable W2U_MOVE_EVENT_ALIAS_TABLE[] = {
    { MOVE_PHANTOM_FORCE, EventAddShadowForce },
    { MOVE_FAIRY_LOCK, EventAddSpiderWeb },
    { MOVE_HOLD_BACK, EventAddFalseSwipe },
    { MOVE_INFESTATION, EventAddBind },
};

const W2UPosEffectEventAddTable W2U_POS_EFFECT_EVENT_ADD_TABLE[] = {
    W2U_POS_EVENT(POSEFF_ION_DELUGE, PosIonDelugeHandlers, EVENTPRI_ABILITY_STALL),
    W2U_POS_EVENT(POSEFF_MAT_BLOCK, PosMatBlockHandlers, EVENTPRI_POS_DEFAULT),
    W2U_POS_EVENT(POSEFF_CRAFTY_SHIELD, PosCraftyShieldHandlers, EVENTPRI_POS_DEFAULT),
    W2U_POS_EVENT(POSEFF_ELECTRIFY, PosElectrifyHandlers, EVENTPRI_POS_DEFAULT),
};

#undef W2U_POS_EVENT
#undef W2U_MOVE_EVENT

} // namespace

extern "C" void ServerEvent_ProtectSuccess(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    BattleMon* defendingMon,
    MOVE_ID moveID)
{
    BattleEventVar_Push();
    SetupNewEvent();
    BattleEventVar_SetConstValue(NEW_VAR_ATTACKING_MON, BattleMon_GetID(attackingMon));
    BattleEventVar_SetConstValue(NEW_VAR_DEFENDING_MON, BattleMon_GetID(defendingMon));
    BattleEventVar_SetConstValue(VAR_MOVE_ID, moveID);
    BattleEvent_CallHandlers(serverFlow, EVENT_PROTECT_SUCCESS);
    BattleEventVar_Pop();
}

extern "C" void ServerEvent_ProtectBroken(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    BattleMon* defendingMon,
    MOVE_ID moveID)
{
    BattleEventVar_Push();
    SetupNewEvent();
    BattleEventVar_SetConstValue(NEW_VAR_ATTACKING_MON, BattleMon_GetID(attackingMon));
    BattleEventVar_SetConstValue(NEW_VAR_DEFENDING_MON, BattleMon_GetID(defendingMon));
    BattleEventVar_SetConstValue(VAR_MOVE_ID, moveID);
    BattleEvent_CallHandlers(serverFlow, EVENT_PROTECT_BROKEN);
    BattleEventVar_Pop();
}

extern "C" void THUMB_BRANCH_SAFESTACK_flowsub_CheckNoEffect_Protect(
    ServerFlow* serverFlow,
    u16* moveID,
    BattleMon* attackingMon,
    PokeSet* targetSet,
    int dmgAffRec)
{
    PokeSet_SeekStart(targetSet);
    for (BattleMon* targetMon = PokeSet_SeekNext(targetSet); targetMon; targetMon = PokeSet_SeekNext(targetSet)) {
        if (!ServerControl_IsGuaranteedHit(serverFlow, attackingMon, targetMon) &&
            ServerControl_CheckNoEffectCore(
                serverFlow,
                moveID,
                attackingMon,
                targetMon,
                dmgAffRec,
                EVENT_REDIRECT_TARGETEND)) {
            PokeSet_Remove(targetSet, targetMon);
        }
    }

    PokeSet_SeekStart(targetSet);
    for (BattleMon* targetMon = PokeSet_SeekNext(targetSet); targetMon; targetMon = PokeSet_SeekNext(targetSet)) {
        if (ServerControl_CheckNoEffectCore(
                serverFlow,
                moveID,
                attackingMon,
                targetMon,
                dmgAffRec,
                EVENT_NOEFFECT_CHECK)) {
            PokeSet_Remove(targetSet, targetMon);
        }
    }

    PokeSet_SeekStart(targetSet);
    for (BattleMon* targetMon = PokeSet_SeekNext(targetSet); targetMon; targetMon = PokeSet_SeekNext(targetSet)) {
        bool targetIsProtected =
            BattleMon_GetTurnFlag(targetMon, TURNFLAG_PROTECT) &&
            getMoveFlag(*moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT);
        u32 breakProtect = ServerEvent_CheckProtectBreak(serverFlow, attackingMon);
        switch (breakProtect) {
        case 0:
            if (targetIsProtected) {
                PokeSet_Remove(targetSet, targetMon);
                u32 targetSlot = BattleMon_GetID(targetMon);
                ServerDisplay_AddMessageImpl(serverFlow->serverCommandQueue, SCID_SetMessage, 523, targetSlot, 0xFFFF0000);

                u32 HEID = HEManager_PushState(&serverFlow->HEManager);
                ServerEvent_ProtectSuccess(serverFlow, attackingMon, targetMon, *moveID);
                HEManager_PopState(&serverFlow->HEManager, HEID);
            }
            break;
        case 1: {
            u32 HEID = HEManager_PushState(&serverFlow->HEManager);
            ServerEvent_ProtectBroken(serverFlow, attackingMon, targetMon, *moveID);
            HEManager_PopState(&serverFlow->HEManager, HEID);
            break;
        }
        default:
            break;
        }
    }

    PokeSet_SeekStart(targetSet);
    for (BattleMon* targetMon = PokeSet_SeekNext(targetSet); targetMon; targetMon = PokeSet_SeekNext(targetSet)) {
        if (ServerControl_CheckNoEffectCore(
                serverFlow,
                moveID,
                attackingMon,
                targetMon,
                dmgAffRec,
                EVENT_ABILITY_CHECK_NO_EFFECT)) {
            PokeSet_Remove(targetSet, targetMon);
        }
    }
}

extern "C" void THUMB_BRANCH_SAFESTACK_BattleViewCmd_MoveEffect_Start(
    BtlvCore* btlCore,
    u32 attackingPos,
    u32 targetPos,
    u16 moveID,
    u32 moveTarget,
    u32 effectIndex,
    u8 zero)
{
    u32 attackingViewPos = MainModule_BattlePosToViewPos(btlCore->mainModule, attackingPos);
    u32 targetViewPos = 255;
    if (targetPos != W2U_NULL_BATTLE_POS) {
        targetViewPos = MainModule_BattlePosToViewPos(btlCore->mainModule, targetPos);
    }

    u16 animMoveID = moveID;
    if (animMoveID >= W2U_FIRST_BATTLE_ANIMATION_ID) {
        animMoveID += W2U_BATTLE_ANIMATIONS_COUNT;
    }
    CMD_ACT_MoveAnimStart(
        btlCore->btlvScu,
        attackingViewPos,
        targetViewPos,
        animMoveID,
        moveTarget,
        (u8)effectIndex,
        zero);
}

extern "C" bool THUMB_BRANCH_MoveEvent_AddItem(BattleMon* battleMon, MOVE_ID moveID, u32 speed)
{
    if (moveID > MOVE_HYPERSPACE_FURY) {
        return false;
    }

    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_MOVE_EVENT_ADD_TABLE); ++idx) {
        const W2UMoveEventAddTable* addEvent = &W2U_MOVE_EVENT_ADD_TABLE[idx];
        if (moveID == addEvent->moveID) {
            return AddMoveEvent(battleMon, moveID, speed, addEvent->handlers, addEvent->handlerAmount) != 0;
        }
    }

    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_MOVE_EVENT_ALIAS_TABLE); ++idx) {
        const W2UMoveEventAliasTable* addEvent = &W2U_MOVE_EVENT_ALIAS_TABLE[idx];
        if (moveID == addEvent->moveID) {
            return GetMoveEvent(battleMon, moveID, speed, addEvent->func) != 0;
        }
    }

    for (u32 idx = 0; idx < W2U_MOVE_EVENT_TABLE_COUNT; ++idx) {
        MoveEventAddTable* addEvent = &W2U_MOVE_EVENT_TABLE[idx];
        if (moveID == addEvent->moveID) {
            return GetMoveEvent(battleMon, moveID, speed, addEvent->func) != 0;
        }
    }
    return false;
}

extern "C" BattleEventItem* THUMB_BRANCH_SAFESTACK_PosEffectEvent_AddItem(
    POS_EFFECT posEffect,
    u32 targetPos,
    u32 pokemonSlot,
    u32* work,
    u8 workCount)
{
    (void)pokemonSlot;
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_POS_EFFECT_EVENT_ADD_TABLE); ++idx) {
        const W2UPosEffectEventAddTable* addEvent = &W2U_POS_EFFECT_EVENT_ADD_TABLE[idx];
        if (posEffect == addEvent->posEffect) {
            return AddPosEffectEvent(
                posEffect,
                targetPos,
                addEvent->handlers,
                addEvent->handlerAmount,
                (BattleEventPriority)addEvent->priority,
                workCount,
                work);
        }
    }

    for (u32 idx = 0; idx < W2U_POS_EVENT_TABLE_COUNT; ++idx) {
        PosEffectEventAddTable* addEvent = &W2U_POS_EVENT_TABLE[idx];
        if (posEffect == addEvent->posEffect) {
            return GetPosEffectEvent(posEffect, targetPos, addEvent->func, workCount, work);
        }
    }
    return 0;
}

extern "C" u32 THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    BattleMon* defendingMon,
    u32 moveType,
    u8 pokemonType)
{
    BattleEventVar_Push();
    u32 attackingSlot = BattleMon_GetID(attackingMon);
    u32 defendingSlot = BattleMon_GetID(defendingMon);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, attackingSlot);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, defendingSlot);
    BattleEventVar_SetConstValue(VAR_POKE_TYPE, pokemonType);
    BattleEventVar_SetConstValue(VAR_MOVE_TYPE, moveType);
    BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);
    BattleEventVar_SetRewriteOnceValue(VAR_SET_TYPE_EFFECTIVENESS, DONT_OVERRIDE_EFFECTIVENESS);
    Condition_CheckUnaffectedByType(serverFlow, defendingMon);
    BattleEvent_CallHandlers(serverFlow, EVENT_CHECK_TYPE_EFFECTIVENESS);
    b32 overrideImmunity = BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS);
    u32 overrideEffectiveness = (u32)BattleEventVar_GetValue(VAR_SET_TYPE_EFFECTIVENESS);
    BattleEventVar_Pop();

    u32 effectiveness = GetTypeEffectiveness(moveType, pokemonType);
    if (effectiveness == RESULT_NOT_EFFECTIVE && overrideImmunity) {
        effectiveness = RESULT_EFFECTIVE;
    }

    if (effectiveness != RESULT_NOT_EFFECTIVE) {
        if (overrideEffectiveness == OVERRIDE_EFFECTIVENESS_1_2) {
            return RESULT_NOT_VERY_EFFECTIVE;
        }
        if (overrideEffectiveness == OVERRIDE_EFFECTIVENESS_1) {
            return RESULT_EFFECTIVE;
        }
        if (overrideEffectiveness == OVERRIDE_EFFECTIVENESS_2) {
            return RESULT_SUPER_EFFECTIVE;
        }
        if (overrideEffectiveness >= COMPOUND_EFFECTIVENESS) {
            effectiveness = GetTypeEffectivenessMultiplier(effectiveness, overrideEffectiveness - COMPOUND_EFFECTIVENESS);
        }
    }

    return effectiveness;
}

extern "C" u32 THUMB_BRANCH_GetTypeEffectivenessMultiplier(u32 effectiveness1, u32 effectiveness2)
{
    u32 multiplier1 = EffectivenessScaledMultiplier(effectiveness1);
    u32 multiplier2 = EffectivenessScaledMultiplier(effectiveness2);
    if (multiplier1 == 0xFFFFFFFFu || multiplier2 == 0xFFFFFFFFu) {
        return RESULT_EFFECTIVE;
    }

    volatile u32 multiplier = (multiplier1 * multiplier2) / 4;
    if (multiplier == 0) {
        return RESULT_NOT_EFFECTIVE;
    }
    if (multiplier == 2) {
        return W2U_EFFECTIVENESS_1_8;
    }
    if (multiplier == 4) {
        return W2U_EFFECTIVENESS_1_4;
    }
    if (multiplier == 8) {
        return RESULT_NOT_VERY_EFFECTIVE;
    }
    if (multiplier == 32) {
        return RESULT_SUPER_EFFECTIVE;
    }
    if (multiplier == 64) {
        return W2U_EFFECTIVENESS_4;
    }
    if (multiplier == 128) {
        return W2U_EFFECTIVENESS_8;
    }
    return RESULT_EFFECTIVE;
}

extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_CheckMoveDamageEffectiveness_0x32(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    BattleMon* defendingMon,
    u32 moveType)
{
    u32 effectiveness = THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(
        serverFlow,
        attackingMon,
        defendingMon,
        moveType,
        defendingMon->Type1);

    u32 extraType = W2U_MoveState_GetExtraType(defendingMon->battleSlot);
    if (extraType != TYPE_NULL) {
        u32 extraEffectiveness = THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(
            serverFlow,
            attackingMon,
            defendingMon,
            moveType,
            (u8)extraType);
        effectiveness = THUMB_BRANCH_GetTypeEffectivenessMultiplier(effectiveness, extraEffectiveness);
    }

    return effectiveness;
}

extern "C" u32 THUMB_BRANCH_TypeEffectivenessPowerMod(u32 damage, u32 effectiveness)
{
    return EffectivenessPowerMod(damage, effectiveness);
}

extern "C" b32 THUMB_BRANCH_BattleMon_HasType(BattleMon* battleMon, u32 pokeType)
{
    return HasTypeWithExtra(battleMon, pokeType) ? 1 : 0;
}

extern "C" b32 THUMB_BRANCH_SAFESTACK_IsUnselectableMove(
    BtlClientWk* client,
    BattleMon* battleMon,
    MOVE_ID moveID,
    Btlv_StringParam* strparam)
{
    if (moveID == MOVE_STRUGGLE) {
        return 0;
    }

    if (BattleMon_GetHeldItem(battleMon) &&
        BattleMon_CheckIfMoveCondition(battleMon, CONDITION_CHOICELOCK)) {
        ConditionData choiceLock = BattleMon_GetMoveCondition(battleMon, CONDITION_CHOICELOCK);
        MOVE_ID choicedMove = Condition_GetParam(choiceLock);
        if (Move_IsUsable(battleMon, choicedMove) && choicedMove != moveID) {
            if (strparam) {
                Btlv_StringParam_Setup(strparam, 1, 99);
                Btlv_StringParam_AddArg(strparam, BattleMon_GetHeldItem(battleMon));
                Btlv_StringParam_AddArg(strparam, choicedMove);
            }
            return 1;
        }
    }

    if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_ENCORE)) {
        ConditionData encore = BattleMon_GetMoveCondition(battleMon, CONDITION_ENCORE);
        MOVE_ID previousMove = Condition_GetParam(encore);
        if (moveID != previousMove) {
            if (strparam) {
                Btlv_StringParam_Setup(strparam, 1, 100);
                Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
                Btlv_StringParam_AddArg(strparam, previousMove);
            }
            return 1;
        }
    }

    if (!PML_MoveIsDamaging(moveID)) {
#if W2U_ENABLE_GEN6_BATTLE_ITEMS
        ITEM heldItem = BattleMon_GetHeldItem(battleMon);
        if (heldItem == ITEM_ASSAULT_VEST) {
            if (strparam) {
                Btlv_StringParam_Setup(strparam, 1, BATTLE_ASSAULTVEST_MSGID);
                Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
                Btlv_StringParam_AddArg(strparam, heldItem);
            }
            return 1;
        }
#endif

        if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_TAUNT)) {
            if (strparam) {
                Btlv_StringParam_Setup(strparam, 2, 571);
                Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            }
            return 1;
        }
    }

    if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_TORMENT) &&
        moveID == BattleMon_GetPreviousMove(battleMon)) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 580);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_DISABLE) &&
        moveID == BattleMon_GetConditionAffectedMove(battleMon, CONDITION_DISABLE) &&
        moveID != MOVE_STRUGGLE) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 595);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_HEALBLOCK) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_HEALING)) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 890);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (client &&
        BattleField_CheckEffect(W2U_FLDEFF_IMPRISON) &&
        BattleField_CheckImprison(client->pokeCon, battleMon, moveID)) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 589);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (BattleField_CheckEffect(W2U_FLDEFF_GRAVITY) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_GROUNDED_BY_GRAVITY)) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 1086);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (moveID == MOVE_BELCH) {
        u32 battleSlot = BattleMon_GetID(battleMon);
        if (!W2U_MoveState_HasConsumedBerryFlag(battleSlot)) {
            if (strparam) {
                Btlv_StringParam_Setup(strparam, 1, BATTLE_BELCH_MSGID);
                Btlv_StringParam_AddArg(strparam, battleSlot);
            }
            return 1;
        }
    }

    return 0;
}
