#include "w2u_abilities.h"
#include "Types.h"

namespace {

constexpr u32 W2U_ITEM_EVENT_TABLE = 0x021D8F68;
constexpr u32 W2U_ITEM_EVENT_TABLE_COUNT = 172;
constexpr u32 W2U_ASSAULT_VEST_SPDEF_RATIO = 6144;
constexpr u32 W2U_EFFECTIVENESS_2 = 4;

typedef BattleEventHandlerTableEntry* (*ItemEventAddFunc)(u32* handlerAmount);

struct ItemEventAddTable {
    ITEM itemID;
    ItemEventAddFunc func;
};

struct W2UItemEventAddTable {
    ITEM itemID;
    ItemEventAddFunc func;
};

bool IsEventDefender(u32 pokemonSlot)
{
    return pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(VAR_DEFENDING_MON));
}

bool IsDefenderWithoutSubstitute(u32 pokemonSlot)
{
    return IsEventDefender(pokemonSlot) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG);
}

bool CanBoostStat(ServerFlow* serverFlow, u32 pokemonSlot, StatStage stat, int volume)
{
    if (!serverFlow) {
        return false;
    }

    BattleMon* battleMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
    return battleMon && BattleMon_IsStatChangeValid(battleMon, stat, volume);
}

void TryPushDefenderStatBoostItem(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    StatStage stat)
{
    if (IsDefenderWithoutSubstitute(pokemonSlot) &&
        CanBoostStat(serverFlow, pokemonSlot, stat, 1)) {
        ItemEvent_PushRun(item, serverFlow, pokemonSlot);
    }
}

void PushStatStageChange(ServerFlow* serverFlow, u32 pokemonSlot, StatStage stat, s8 volume)
{
    if (!serverFlow) {
        return;
    }

    HandlerParam_ChangeStatStage* statChange =
        static_cast<HandlerParam_ChangeStatStage*>(
            BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_STAT_STAGE, pokemonSlot));
    if (!statChange) {
        return;
    }
    statChange->pokeCount = 1;
    statChange->pokeID[0] = static_cast<u8>(pokemonSlot);
    statChange->stat = stat;
    statChange->volume = volume;
    BattleHandler_PopWork(serverFlow, statChange);
}

void HandlerAssaultVestDefense(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;

    if (IsEventDefender(pokemonSlot) &&
        BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == SPLIT_SPECIAL) {
        BattleEventVar_MulValue(VAR_RATIO, W2U_ASSAULT_VEST_SPDEF_RATIO);
    }
}

BattleEventHandlerTableEntry AssaultVestHandlers[] = {
    {EVENT_DEFENDER_GUARD, HandlerAssaultVestDefense},
};

BattleEventHandlerTableEntry* EventAddAssaultVest(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(AssaultVestHandlers);
    return AssaultVestHandlers;
}

void HandlerLuminousMossDamageReaction(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;

    if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER) {
        TryPushDefenderStatBoostItem(item, serverFlow, pokemonSlot, STATSTAGE_SPECIAL_DEFENSE);
    }
}

void HandlerStatBoostItemUse(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work,
    StatStage stat)
{
    (void)item;
    (void)work;

    if (pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(VAR_MON_ID))) {
        PushStatStageChange(serverFlow, pokemonSlot, stat, 1);
    }
}

void HandlerLuminousMossUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_SPECIAL_DEFENSE);
}

BattleEventHandlerTableEntry LuminousMossHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerLuminousMossDamageReaction},
    {EVENT_USE_ITEM, HandlerLuminousMossUse},
};

BattleEventHandlerTableEntry* EventAddLuminousMoss(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(LuminousMossHandlers);
    return LuminousMossHandlers;
}

void HandlerSnowballDamageReaction(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;

    if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ICE) {
        TryPushDefenderStatBoostItem(item, serverFlow, pokemonSlot, STATSTAGE_ATTACK);
    }
}

void HandlerSnowballUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_ATTACK);
}

BattleEventHandlerTableEntry SnowballHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerSnowballDamageReaction},
    {EVENT_USE_ITEM, HandlerSnowballUse},
};

BattleEventHandlerTableEntry* EventAddSnowball(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(SnowballHandlers);
    return SnowballHandlers;
}

void HandlerWeaknessPolicyDamageReaction(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;

    if (IsDefenderWithoutSubstitute(pokemonSlot) &&
        static_cast<u32>(BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS)) >= W2U_EFFECTIVENESS_2 &&
        (CanBoostStat(serverFlow, pokemonSlot, STATSTAGE_ATTACK, 1) ||
            CanBoostStat(serverFlow, pokemonSlot, STATSTAGE_SPECIAL_ATTACK, 1))) {
        ItemEvent_PushRun(item, serverFlow, pokemonSlot);
    }
}

void HandlerWeaknessPolicyUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;

    if (pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(VAR_MON_ID))) {
        PushStatStageChange(serverFlow, pokemonSlot, STATSTAGE_ATTACK, 2);
        PushStatStageChange(serverFlow, pokemonSlot, STATSTAGE_SPECIAL_ATTACK, 2);
    }
}

BattleEventHandlerTableEntry WeaknessPolicyHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerWeaknessPolicyDamageReaction},
    {EVENT_USE_ITEM, HandlerWeaknessPolicyUse},
};

BattleEventHandlerTableEntry* EventAddWeaknessPolicy(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(WeaknessPolicyHandlers);
    return WeaknessPolicyHandlers;
}

void HandlerMarangaBerryDamageReaction(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;

    if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == SPLIT_SPECIAL) {
        TryPushDefenderStatBoostItem(item, serverFlow, pokemonSlot, STATSTAGE_SPECIAL_DEFENSE);
    }
}

void HandlerMarangaBerryUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_SPECIAL_DEFENSE);
}

BattleEventHandlerTableEntry MarangaBerryHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, HandlerMarangaBerryDamageReaction},
    {EVENT_USE_ITEM, HandlerMarangaBerryUse},
    {EVENT_USE_ITEM_TEMP, HandlerMarangaBerryUse},
};

BattleEventHandlerTableEntry* EventAddMarangaBerry(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(MarangaBerryHandlers);
    return MarangaBerryHandlers;
}

void HandlerFairyFeather(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;
    CommonTypeBoostingItem(item, serverFlow, pokemonSlot, TYPE_FAIRY);
}

BattleEventHandlerTableEntry FairyFeatherHandlers[] = {
    {EVENT_MOVE_POWER, HandlerFairyFeather},
};

BattleEventHandlerTableEntry* EventAddFairyFeather(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(FairyFeatherHandlers);
    return FairyFeatherHandlers;
}

void HandlerRoseliBerry(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    CommonResistBerry(item, serverFlow, pokemonSlot, work, TYPE_FAIRY, 0);
}

BattleEventHandlerTableEntry RoseliBerryHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerRoseliBerry},
    {EVENT_AFTER_DAMAGE_REACTION, HandlerCommonResistBerryDamageAfter},
};

BattleEventHandlerTableEntry* EventAddRoseliBerry(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(RoseliBerryHandlers);
    return RoseliBerryHandlers;
}

void HandlerSafetyGogglesPowderMoves(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;

    if (pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(VAR_DEFENDING_MON)) &&
        pokemonSlot != static_cast<u32>(BattleEventVar_GetValue(VAR_ATTACKING_MON)) &&
        getMoveFlag(static_cast<MOVE_ID>(BattleEventVar_GetValue(VAR_MOVE_ID)), MOVE_FLAG_INDEX_POWDER)) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry SafetyGogglesHandlers[] = {
    {EVENT_WEATHER_REACTION, HandlerOvercoat},
    {EVENT_ABILITY_CHECK_NO_EFFECT, HandlerSafetyGogglesPowderMoves},
};

BattleEventHandlerTableEntry* EventAddSafetyGoggles(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(SafetyGogglesHandlers);
    return SafetyGogglesHandlers;
}

BattleEventItem* GetItemEvent(BattleMon* battleMon, ITEM itemID, ItemEventAddFunc func)
{
    if (!battleMon || !func) {
        return 0;
    }

    u32 handlerAmount = 0;
    BattleEventHandlerTableEntry* handlers = func(&handlerAmount);
    if (handlerAmount == 0 || !handlers) {
        return 0;
    }

    const u32 pokemonSlot = BattleMon_GetID(battleMon);
    const u32 speed = BattleMon_GetRealStat(battleMon, VALUE_SPEED_STAT);
    return BattleEvent_AddItem(
        EVENTITEM_ITEM,
        static_cast<u16>(itemID),
        EVENTPRI_ITEM_DEFAULT,
        speed,
        pokemonSlot,
        handlers,
        static_cast<u16>(handlerAmount));
}

W2UItemEventAddTable sItemEventAddTable[] = {
    {ITEM_ASSAULT_VEST, EventAddAssaultVest},
    {ITEM_LUMINOUS_MOSS, EventAddLuminousMoss},
    {ITEM_SNOWBALL, EventAddSnowball},
    {ITEM_WEAKNESS_POLICY, EventAddWeaknessPolicy},
    {ITEM_MARANGA_BERRY, EventAddMarangaBerry},
    {ITEM_FAIRY_FEATHER, EventAddFairyFeather},
    {ITEM_ROSELI_BERRY, EventAddRoseliBerry},
    {ITEM_SAFETY_GOGGLES, EventAddSafetyGoggles},
};

} // namespace

extern "C" BattleEventItem* THUMB_BRANCH_ItemEvent_AddItemCore(BattleMon* battleMon, ITEM itemID)
{
    for (u32 i = 0; i < W2U_ARRAY_COUNT(sItemEventAddTable); ++i) {
        W2UItemEventAddTable* eventAdd = &sItemEventAddTable[i];
        if (itemID == eventAdd->itemID) {
            return GetItemEvent(battleMon, itemID, eventAdd->func);
        }
    }

    ItemEventAddTable* vanillaTable = reinterpret_cast<ItemEventAddTable*>(W2U_ITEM_EVENT_TABLE);
    for (u32 i = 0; i < W2U_ITEM_EVENT_TABLE_COUNT; ++i) {
        ItemEventAddTable* eventAdd = &vanillaTable[i];
        if (itemID == eventAdd->itemID) {
            return GetItemEvent(battleMon, itemID, eventAdd->func);
        }
    }

    return 0;
}
