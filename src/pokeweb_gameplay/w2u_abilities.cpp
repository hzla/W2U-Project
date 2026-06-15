#include "w2u_abilities.h"
#include "w2u_field_effects.h"
#include "w2u_moves.h"

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
#define W2U_RECEIVER_MSG_NARC 2u
#define W2U_RECEIVER_MSG_ID 619u
#define W2U_FORCE_FAIL_MESSAGE 2
#define W2U_SERVERFLOW_SET_TARGET_ORIGINAL_OFFSET 0x850u
#define W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET 0x38u
#define W2U_ACTION_ORDER_PRIO_OFFSET 7
#define W2U_ACTION_ORDER_SPECIAL_PRIO_OFFSET 1
#define W2U_VANILLA_ABILITY_EVENT_TABLE ((AbilityEventAddTable*)0x021D7F38)
#define W2U_VANILLA_ABILITY_EVENT_TABLE_COUNT 158u

extern "C" void THUMB_BRANCH_ServerEvent_GetMoveParam(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    BattleMon* battleMon,
    MoveParam* moveParam);

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

namespace {

typedef BattleEventHandlerTableEntry* (*AbilityEventAddFunc)(u32* handlerAmount);

bool sParentalBondActive = false;
u8 sParentalBondPowerHit = 0;

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

void RewriteNormalMoveType(u32 pokemonSlot, u32 newType)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL) {
        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, newType);
    }
}

void BoostConvertedMove(u32 pokemonSlot, u32 convertedType)
{
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
        return true;
    default:
        return false;
    }
}

int GetQueuedMovePriority(ServerFlow* serverFlow, BattleMon* attackingMon)
{
    if (!serverFlow || !attackingMon) {
        return 0;
    }

    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(serverFlow->actionOrderWork); ++idx) {
        ActionOrderWork* actionOrder = &serverFlow->actionOrderWork[idx];
        if (actionOrder->battleMon == attackingMon) {
            int priority = (int)((actionOrder->speed >> 16) & 0x3FFFFF) - W2U_ACTION_ORDER_PRIO_OFFSET;
            int specialPriority =
                (int)((actionOrder->speed >> 13) & 0x7) - W2U_ACTION_ORDER_SPECIAL_PRIO_OFFSET;
            return priority + specialPriority;
        }
    }

    return (int)BattleEventVar_GetValue(VAR_MOVE_PRIORITY);
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
        HandlerCommon_IsUnremovableItem(giveMon, giveItem) ||
        HandlerCommon_IsUnremovableItem(receiveMon, giveItem)) {
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
    THUMB_BRANCH_ServerEvent_GetMoveParam(serverFlow, moveID, attackingMon, &moveParam);
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
        BattleEventVar_RewriteValue(VAR_CRIT_STAGE, 4);
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
    (void)serverFlow;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        return;
    }

    u32 ratio = 4096;
    if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_FIRE) {
        ratio *= 2;
    }

    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (getMoveFlag(moveID, MOVE_FLAG_INDEX_CONTACT)) {
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
    if (GetQueuedMovePriority(serverFlow, attackingMon) > 0) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry QueenlyMajestyHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, HandlerQueenlyMajesty},
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


extern "C" void HandlerEmergencyExitDamageCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!IsTargetSlotInCurrentDamageEvent(pokemonSlot) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) {
        return;
    }

    BattleMon* currentMon = GetAbilityBattleMon(serverFlow, pokemonSlot);
    if (!DamageCrossedBelowHalfHP(currentMon, (u32)BattleEventVar_GetValue(VAR_DAMAGE)) ||
        !Handler_GetFightEnableBenchPokeNum(serverFlow, pokemonSlot)) {
        return;
    }

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_ADD, pokemonSlot);

    HandlerParam_Switch* switchOut =
        (HandlerParam_Switch*)BattleHandler_PushWork(serverFlow, EFFECT_SWITCH, pokemonSlot);
    switchOut->pokeID = (u8)pokemonSlot;
    BattleHandler_PopWork(serverFlow, switchOut);

    BattleHandler_PushRun(serverFlow, EFFECT_ABILITY_POPUP_REMOVE, pokemonSlot);
}

BattleEventHandlerTableEntry EmergencyExitHandlers[] = {
    {EVENT_DAMAGE_PROCESSING_END_HIT_2, HandlerEmergencyExitDamageCheck},
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
    if (!getMoveFlag(moveID, MOVE_FLAG_INDEX_CONTACT)) {
        return;
    }

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
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
    u32 power = (u32)BattleEventVar_GetValue(VAR_MOVE_POWER);
    if (sParentalBondPowerHit == 2) {
        sParentalBondPowerHit = 0;
        power /= 2;
    }

    BattleEventVar_RewriteValue(VAR_MOVE_POWER, power);
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

    MoveParam params;
    THUMB_BRANCH_ServerEvent_GetMoveParam(
        serverFlow,
        (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID),
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


namespace {

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
    W2U_ABILITY_EVENT(ABIL_WIMP_OUT, EmergencyExitHandlers),
    W2U_ABILITY_EVENT(ABIL_EMERGENCY_EXIT, EmergencyExitHandlers),
    W2U_ABILITY_EVENT(ABIL_WATER_COMPACTION, WaterCompactionHandlers),
    W2U_ABILITY_EVENT(ABIL_MERCILESS, MercilessHandlers),
    W2U_ABILITY_EVENT(ABIL_STEELWORKER, SteelworkerHandlers),
    W2U_ABILITY_EVENT(ABIL_BERSERK, BerserkHandlers),
    W2U_ABILITY_EVENT(ABIL_SLUSH_RUSH, SlushRushHandlers),
    W2U_ABILITY_EVENT(ABIL_GALVANIZE, NormalMoveConversionHandlers),
    W2U_ABILITY_EVENT(ABIL_SURGE_SURFER, SurgeSurferHandlers),
    W2U_ABILITY_EVENT(ABIL_QUEENLY_MAGESTY, QueenlyMajestyHandlers),
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

#define W2U_VANILLA_ABILITY_ALIAS(ability, vanillaAbility) { (u16)ability, (u16)vanillaAbility }

W2UVanillaAbilityAliasEventAddTable sVanillaAbilityAliasEventAddTable[] = {
    W2U_VANILLA_ABILITY_ALIAS(ABIL_FULL_METAL_BODY, 29), // Clear Body
    W2U_VANILLA_ABILITY_ALIAS(ABIL_SHADOW_SHIELD, 136), // Multiscale
};

#undef W2U_VANILLA_ABILITY_ALIAS

} // namespace

extern "C" BattleEventItem* THUMB_BRANCH_AbilityEvent_AddItem(BattleMon* battleMon)
{
    ABILITY ability = BattleMon_GetValue(battleMon, VALUE_ABILITY);

    for (u32 i = 0; i < W2U_ARRAY_COUNT(sAbilityEventAddTable); ++i) {
        W2UAbilityEventAddTable* eventAdd = &sAbilityEventAddTable[i];
        if (ability == eventAdd->ability) {
            return AddAbilityEvent(battleMon, ability, eventAdd->handlers, eventAdd->handlerAmount);
        }
    }

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
