#include "w2u_abilities.h"
#include "w2u_battle_module_api.h"
#include "w2u_battle_module_loader.h"
#include "type_constants.h"
#include "w2u_moves.h"
#include "w2u_platform.h"

namespace {

constexpr u32 W2U_ITEM_EVENT_TABLE = W2U_ADDR_ITEM_EVENT_TABLE;
constexpr u32 W2U_ITEM_EVENT_TABLE_COUNT = 172;
constexpr u32 W2U_ASSAULT_VEST_SPDEF_RATIO = 6144;
constexpr u32 W2U_EFFECTIVENESS_2 = 4;
constexpr u32 W2U_ITSTAT_USE_PARAM = 2;

typedef BattleEventHandlerTableEntry* (*ItemEventAddFunc)(u32* handlerAmount);

struct ItemEventAddTable {
    ITEM itemID;
    ItemEventAddFunc func;
};

struct W2UItemEventAddTable {
    ITEM itemID;
    ItemEventAddFunc func;
};

#if !defined(W2U_DYNAMIC_BATTLE_CORE)
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

void HandlerTerrainExtenderTurnCount(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)serverFlow;
    (void)work;

    // Port PW2Code's terrain-specific payload on the native weather duration
    // event. NEW_VAR_ATTACKING_MON keeps this from extending actual weather.
    if (pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(NEW_VAR_ATTACKING_MON)) &&
        BattleEventVar_GetValue(VAR_WEATHER) != TERRAIN_NULL) {
        BattleEventVar_RewriteValue(
            VAR_EFFECT_TURN_COUNT,
            static_cast<int>(CommonGetItemParam(item, W2U_ITSTAT_USE_PARAM)));
    }
}

BattleEventHandlerTableEntry TerrainExtenderHandlers[] = {
    {EVENT_MOVE_TERRAIN_TURN_COUNT, HandlerTerrainExtenderTurnCount},
};

BattleEventHandlerTableEntry* EventAddTerrainExtender(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(TerrainExtenderHandlers);
    return TerrainExtenderHandlers;
}

bool IsNewEventForPokemon(u32 pokemonSlot)
{
    return BattleEventVar_GetValue(VAR_MON_ID) == -1 &&
        BattleEventVar_GetValue(VAR_ATTACKING_MON) == -1 &&
        BattleEventVar_GetValue(VAR_DEFENDING_MON) == -1 &&
        pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(NEW_VAR_MON_ID));
}

void TryPushTerrainSeed(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work,
    TERRAIN terrain,
    StatStage stat)
{
    // Terrain Seeds intentionally do not require the holder to be grounded.
    // This matches the original mechanic and permits airborne Unburden users.
    if ((!work || work[0] == 0) &&
        W2U_MoveState_GetTerrain() == terrain &&
        CanBoostStat(serverFlow, pokemonSlot, stat, 1)) {
        if (work) {
            // A Surge can dispatch the terrain-change event from inside the
            // outer switch-in event. Keep that pair from queuing two uses.
            work[0] = 1;
        }
        ItemEvent_PushRun(item, serverFlow, pokemonSlot);
    }
}

void TryPushTerrainSeedOnSwitchOrItemCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work,
    TERRAIN terrain,
    StatStage stat)
{
    if (pokemonSlot == static_cast<u32>(BattleEventVar_GetValue(VAR_MON_ID))) {
        TryPushTerrainSeed(item, serverFlow, pokemonSlot, work, terrain, stat);
    }
}

void TryPushTerrainSeedAfterTerrainChange(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work,
    TERRAIN terrain,
    StatStage stat)
{
    // EVENT_AFTER_TERRAIN_CHANGE shares its native event ID with
    // EVENT_AFTER_ABILITY_CHANGE, so require the new-event terrain payload.
    if (IsNewEventForPokemon(pokemonSlot) &&
        BattleEventVar_GetValue(VAR_WEATHER) == terrain) {
        TryPushTerrainSeed(item, serverFlow, pokemonSlot, work, terrain, stat);
    }
}

void HandlerElectricSeedCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedOnSwitchOrItemCheck(
        item, serverFlow, pokemonSlot, work, TERRAIN_ELECTRIC, STATSTAGE_DEFENSE);
}

void HandlerElectricSeedTerrainChange(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedAfterTerrainChange(
        item, serverFlow, pokemonSlot, work, TERRAIN_ELECTRIC, STATSTAGE_DEFENSE);
}

void HandlerElectricSeedUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    if (work) {
        work[0] = 0;
    }
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_DEFENSE);
}

BattleEventHandlerTableEntry ElectricSeedHandlers[] = {
    {EVENT_SWITCH_IN, HandlerElectricSeedCheck},
    {EVENT_CHECK_ITEM_REACTION, HandlerElectricSeedCheck},
    {EVENT_AFTER_TERRAIN_CHANGE, HandlerElectricSeedTerrainChange},
    {EVENT_USE_ITEM, HandlerElectricSeedUse},
};

BattleEventHandlerTableEntry* EventAddElectricSeed(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(ElectricSeedHandlers);
    return ElectricSeedHandlers;
}

void HandlerGrassySeedCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedOnSwitchOrItemCheck(
        item, serverFlow, pokemonSlot, work, TERRAIN_GRASSY, STATSTAGE_DEFENSE);
}

void HandlerGrassySeedTerrainChange(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedAfterTerrainChange(
        item, serverFlow, pokemonSlot, work, TERRAIN_GRASSY, STATSTAGE_DEFENSE);
}

void HandlerGrassySeedUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    if (work) {
        work[0] = 0;
    }
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_DEFENSE);
}

BattleEventHandlerTableEntry GrassySeedHandlers[] = {
    {EVENT_SWITCH_IN, HandlerGrassySeedCheck},
    {EVENT_CHECK_ITEM_REACTION, HandlerGrassySeedCheck},
    {EVENT_AFTER_TERRAIN_CHANGE, HandlerGrassySeedTerrainChange},
    {EVENT_USE_ITEM, HandlerGrassySeedUse},
};

BattleEventHandlerTableEntry* EventAddGrassySeed(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(GrassySeedHandlers);
    return GrassySeedHandlers;
}

void HandlerPsychicSeedCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedOnSwitchOrItemCheck(
        item, serverFlow, pokemonSlot, work, TERRAIN_PSYCHIC, STATSTAGE_SPECIAL_DEFENSE);
}

void HandlerPsychicSeedTerrainChange(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedAfterTerrainChange(
        item, serverFlow, pokemonSlot, work, TERRAIN_PSYCHIC, STATSTAGE_SPECIAL_DEFENSE);
}

void HandlerPsychicSeedUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    if (work) {
        work[0] = 0;
    }
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_SPECIAL_DEFENSE);
}

BattleEventHandlerTableEntry PsychicSeedHandlers[] = {
    {EVENT_SWITCH_IN, HandlerPsychicSeedCheck},
    {EVENT_CHECK_ITEM_REACTION, HandlerPsychicSeedCheck},
    {EVENT_AFTER_TERRAIN_CHANGE, HandlerPsychicSeedTerrainChange},
    {EVENT_USE_ITEM, HandlerPsychicSeedUse},
};

BattleEventHandlerTableEntry* EventAddPsychicSeed(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(PsychicSeedHandlers);
    return PsychicSeedHandlers;
}

void HandlerMistySeedCheck(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedOnSwitchOrItemCheck(
        item, serverFlow, pokemonSlot, work, TERRAIN_MISTY, STATSTAGE_SPECIAL_DEFENSE);
}

void HandlerMistySeedTerrainChange(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    TryPushTerrainSeedAfterTerrainChange(
        item, serverFlow, pokemonSlot, work, TERRAIN_MISTY, STATSTAGE_SPECIAL_DEFENSE);
}

void HandlerMistySeedUse(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    if (work) {
        work[0] = 0;
    }
    HandlerStatBoostItemUse(item, serverFlow, pokemonSlot, work, STATSTAGE_SPECIAL_DEFENSE);
}

BattleEventHandlerTableEntry MistySeedHandlers[] = {
    {EVENT_SWITCH_IN, HandlerMistySeedCheck},
    {EVENT_CHECK_ITEM_REACTION, HandlerMistySeedCheck},
    {EVENT_AFTER_TERRAIN_CHANGE, HandlerMistySeedTerrainChange},
    {EVENT_USE_ITEM, HandlerMistySeedUse},
};

BattleEventHandlerTableEntry* EventAddMistySeed(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(MistySeedHandlers);
    return MistySeedHandlers;
}
#endif

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

#if !defined(W2U_DYNAMIC_BATTLE_CORE) && !defined(W2U_BATTLE_STATIC_GROUPS)
W2UItemEventAddTable sItemEventAddTable[] = {
    {ITEM_ASSAULT_VEST, EventAddAssaultVest},
    {ITEM_LUMINOUS_MOSS, EventAddLuminousMoss},
    {ITEM_SNOWBALL, EventAddSnowball},
    {ITEM_WEAKNESS_POLICY, EventAddWeaknessPolicy},
    {ITEM_MARANGA_BERRY, EventAddMarangaBerry},
    {ITEM_FAIRY_FEATHER, EventAddFairyFeather},
    {ITEM_ROSELI_BERRY, EventAddRoseliBerry},
    {ITEM_SAFETY_GOGGLES, EventAddSafetyGoggles},
    {ITEM_TERRAIN_EXTENDER, EventAddTerrainExtender},
    {ITEM_ELECTRIC_SEED, EventAddElectricSeed},
    {ITEM_GRASSY_SEED, EventAddGrassySeed},
    {ITEM_PSYCHIC_SEED, EventAddPsychicSeed},
    {ITEM_MISTY_SEED, EventAddMistySeed},
};
#endif

} // namespace

extern "C" BattleEventItem* THUMB_BRANCH_ItemEvent_AddItemCore(BattleMon* battleMon, ITEM itemID)
{
#if defined(W2U_DYNAMIC_BATTLE_CORE)
    if (W2U_BattleModules_IsManaged(W2U_MECHANIC_ITEM, (u16)itemID)) {
        const W2UBattleHandlerExport* entry =
            W2U_BattleModules_Resolve(W2U_MECHANIC_ITEM, (u16)itemID);
        if (!entry || !battleMon) {
            return 0;
        }
        return BattleEvent_AddItem(
            EVENTITEM_ITEM,
            (u16)itemID,
            entry->priority == W2U_BATTLE_MODULE_DEFAULT_PRIORITY
                ? EVENTPRI_ITEM_DEFAULT
                : (BattleEventPriority)entry->priority,
            BattleMon_GetRealStat(battleMon, VALUE_SPEED_STAT),
            BattleMon_GetID(battleMon),
            entry->handlers,
            entry->handlerCount);
    }
#elif defined(W2U_BATTLE_STATIC_GROUPS)
    const W2UBattleHandlerExport* entry =
        W2U_BattleStatic_Resolve(W2U_MECHANIC_ITEM, (u16)itemID);
    if (entry && battleMon) {
        return BattleEvent_AddItem(
            EVENTITEM_ITEM,
            (u16)itemID,
            entry->priority == W2U_BATTLE_MODULE_DEFAULT_PRIORITY
                ? EVENTPRI_ITEM_DEFAULT
                : (BattleEventPriority)entry->priority,
            BattleMon_GetRealStat(battleMon, VALUE_SPEED_STAT),
            BattleMon_GetID(battleMon),
            entry->handlers,
            entry->handlerCount);
    }
#else
    for (u32 i = 0; i < W2U_ARRAY_COUNT(sItemEventAddTable); ++i) {
        W2UItemEventAddTable* eventAdd = &sItemEventAddTable[i];
        if (itemID == eventAdd->itemID) {
            return GetItemEvent(battleMon, itemID, eventAdd->func);
        }
    }
#endif

    ItemEventAddTable* vanillaTable = reinterpret_cast<ItemEventAddTable*>(W2U_ITEM_EVENT_TABLE);
    for (u32 i = 0; i < W2U_ITEM_EVENT_TABLE_COUNT; ++i) {
        ItemEventAddTable* eventAdd = &vanillaTable[i];
        if (itemID == eventAdd->itemID) {
            return GetItemEvent(battleMon, itemID, eventAdd->func);
        }
    }

    return 0;
}

#define W2U_BATTLE_API_SOURCE_ITEMS
#include "w2u_battle_module_api_entries.inc"
#undef W2U_BATTLE_API_SOURCE_ITEMS
