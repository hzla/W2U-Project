#if defined(W2U_TARGET_B2)
#include "b2_baseline/w2u_moves.cpp.inc"
#else
#include "w2u_moves.h"
#include "w2u_battle_module_api.h"
#include "w2u_battle_module_loader.h"
#include "w2u_field_effects.h"
#include "w2u_terrain_texture.h"
#include "type_constants.h"
#include "w2u_platform.h"
#include "w2u_weather.h"

#define W2U_MOVE_EVENT_TABLE ((MoveEventAddTable*)W2U_ADDR_MOVE_EVENT_TABLE)
#define W2U_MOVE_EVENT_TABLE_COUNT 258u
#define W2U_POS_EVENT_TABLE ((PosEffectEventAddTable*)W2U_ADDR_POS_EVENT_TABLE)
#define W2U_POS_EVENT_TABLE_COUNT 5u
#define W2U_POS_EVENT_CAN_REGISTER ((PosEffectEventCanRegisterFunc)W2U_ADDR_POS_EVENT_CAN_REGISTER)

#define W2U_FIRST_BATTLE_ANIMATION_ID 561u
#define W2U_BATTLE_ANIMATIONS_COUNT 115u
#define W2U_PSYCHIC_TERRAIN_ANIMATION_ID 624u
#define W2U_NULL_BATTLE_POS 6u
#define W2U_SIDE_COUNT 2u
#define W2U_SIDE_SLOT_COUNT 3u
#define W2U_TERRAIN_TURNS 5u
#define W2U_TERRAIN_POWER_RATIO 5325
#define W2U_RECOVER_RATIO_TWO_THIRDS 2732
#define W2U_RATIO_HALF 2048
#define W2U_ALL_BATTLE_SLOT_FLAGS 0x7FFFFFFFu
#define W2U_ASH_GRENINJA_FORM 2u

#define W2U_FLDEFF_GRAVITY 2u
#define W2U_FLDEFF_IMPRISON 3u
#define W2U_FLDEFF_TRANSIENT_MOVE_STATE 11u
#define W2U_FLDEFF_SPOTLIGHT 12u

#define W2U_EFFECTIVENESS_1_4 1u
#define W2U_EFFECTIVENESS_4 5u
#define W2U_EFFECTIVENESS_1_8 6u
#define W2U_EFFECTIVENESS_8 7u
#define W2U_EFFECTIVENESS_16 8u

#define W2U_EFFECT_COUNTER ((BattleHandlerEffect)0x26)
#define W2U_COUNTER_PROTECT 0x03u
#define W2U_BATTLE_EVENT_ITEM_SUB_ID_OFFSET 0x38u
#define W2U_BATTLE_ACTION_FIGHT 1u
#define W2U_WIDE_GUARD_BLOCK_MSGID 797u
#define W2U_QUICK_GUARD_BLOCK_MSGID 800u

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
typedef b32 (*PosEffectEventCanRegisterFunc)(POS_EFFECT posEffect, u32 targetPos);

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

struct W2UVanillaMoveAlias {
    u16 moveID;
    u16 vanillaMoveID;
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

#if !defined(W2U_BATTLE_CHILD)
struct StickyWebSideState {
    BattleEventItem* item;
    bool active;
};

struct AuroraVeilSideState {
    BattleEventItem* item;
    u8 turns;
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
    AuroraVeilSideState auroraVeil[W2U_SIDE_COUNT];
    TerrainState terrain;
    BattleEventItem* transientItem;
    u32 consumedBerryFlags;
    u32 electrifiedFlags;
    u32 beakBlastChargingFlags;
    u32 beakBlastChargeCueFlags;
    u32 shellTrapArmedFlags;
    u32 shellTrapTriggeredFlags;
    u32 matBlockProtectedFlags;
    u32 powderedFlags;
    u32 spikyShieldFlags;
    u32 spikyShieldDamagedFlags;
    u32 banefulBunkerFlags;
    u32 banefulBunkerPoisonedFlags;
    bool ionDelugeActive;
    u32 matBlockFreshFlags;
    u32 matBlockEnteredThisTurnFlags;
    bool matBlockActive[W2U_SIDE_COUNT];
    bool craftyShieldActive[W2U_SIDE_COUNT];
    u8 matBlockOwner[W2U_SIDE_COUNT];
    u8 craftyShieldOwner[W2U_SIDE_COUNT];
    u8 extraTypes[BATTLE_MAX_SLOTS];
    u8 laserFocusTurns[BATTLE_MAX_SLOTS];
    u8 dragonCheerBoost[BATTLE_MAX_SLOTS];
    u8 throatChopTurns[BATTLE_MAX_SLOTS];
    u32 photonGeyserCategoryValidFlags;
    u32 photonGeyserPhysicalFlags;
    u32 shellSideArmCategoryValidFlags;
    u32 shellSideArmPhysicalFlags;
    u32 shellSideArmRecordedValidFlags;
    u32 shellSideArmRecordedPhysicalFlags;
    u32 stompingFailureLastTurnFlags;
    u32 stompingFailureThisTurnFlags;
    u32 stompingProtectedThisMoveFlags;
    u32 statsRaisedThisTurnFlags;
    u32 statsLoweredThisTurnFlags;
    u32 tarShotFlags;
    u32 noRetreatFlags;
    u32 glaiveRushFlags;
    u32 shedTailTransferFlags;
    u32 redirectedTargetFlags;
    u32 calledDartsFlags;
    u16 lastSuccessfulSelectedMove[BATTLE_MAX_SLOTS];
    u8 directHitsReceived[24];
    u8 faintEvents[4]; // Battle-long counts, including repeated revived faints.
    u32 persistentFlags[3];
    u8 persistentSources[3][BATTLE_MAX_SLOTS];
    u8 persistentTurns[3][BATTLE_MAX_SLOTS];
    BattleEventItem* auxItems[2];
    bool battleTrackingActive;
    BattleEventItem* spotlightItem;
    PartyPkm* spotlightTargetParty;
    u8 spotlightTargetSlot;
};
#endif

extern "C" b32 MoveEvent_CanEffectBeRegistered(u32 pokemonSlot, MOVE_ID moveID, u8* alreadyRegistered);
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
extern "C" BattleEventHandlerTableEntry* EventAddReflect(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddLightScreen(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddFalseSwipe(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddBind(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddSuperFang(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddReturn(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddStoredPower(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddHex(u32* handlerAmount);
extern "C" BattleEventHandlerTableEntry* EventAddHealBell(u32* handlerAmount);
extern "C" void HandlerMoldBreakerStart(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerMoldBreakerEnd(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" b32 SideEffectEvent_IsActive(u32 side, SIDE_EFFECT sideEffect)
    __attribute__((long_call));
#if !defined(W2U_BATTLE_CHILD)
// Overlay 169 lives in VRAM, beyond a Thumb BL's range from PMC's heap.
// Force an absolute indirect call; an RPM-relocated short call would wrap.
extern "C" BattleEventItem* SideEffectEvent_AddItem(u32 side, SIDE_EFFECT effect, ConditionData condition)
    __attribute__((long_call));
struct NativeSideEffectRecord {
    BattleEventItem* item;
    ConditionData condition;
    u32 elapsed;
    u32 layers;
};
static_assert(sizeof(NativeSideEffectRecord) == 16, "Native side-state layout changed");

static NativeSideEffectRecord (*GetNativeSideState())[14]
{
    // Reviewed clean-US W2/B2 IsActive has the same PC-relative state literal
    // at entry + 0x18. Resolve from the mapped game function, not a child or
    // a second region-specific BSS address. Reject an altered native anchor.
    const u16* code = (const u16*)((u32)SideEffectEvent_IsActive & ~1u);
    if (code[0] != 0x22E0 || code[2] != 0x4804) return 0;
    return (NativeSideEffectRecord (*)[14])*(const u32*)((const u8*)code + 0x18);
}
#endif
extern "C" void CommonScreenEffect(ServerFlow* serverFlow, u32 side, u32 screenKind)
    __attribute__((long_call));
extern "C" void HandlerBrickBreakStart(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerBrickBreakEnd(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);
extern "C" void HandlerBrickBreakCheck(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);

extern "C" void Condition_CheckUnaffectedByType(ServerFlow* serverFlow, BattleMon* defendingMon);
extern "C" b32 Move_IsUsable(BattleMon* battleMon, MOVE_ID moveID);
#if !defined(W2U_TARGET_B2)
extern "C" b32 CanMonUseHeldItem(BtlClientWk* client, BattleMon* battleMon);
#endif
extern "C" b32 BattleField_CheckImprison(PokeCon* pokeCon, BattleMon* battleMon, MOVE_ID moveID);
extern "C" MOVE_ID BattleMon_GetPreviousMove(BattleMon* battleMon);
extern "C" MOVE_ID BattleMon_GetPreviousMoveID(BattleMon* battleMon);
extern "C" MOVE_ID BattleMon_GetConditionAffectedMove(BattleMon* battleMon, CONDITION condition);
extern "C" void Btlv_StringParam_Setup(Btlv_StringParam* strParam, u8 narcIdx, u16 msgIdx);
extern "C" void Btlv_StringParam_AddArg(Btlv_StringParam* strParam, u32 value);
namespace {

b32 IsAffectedBySheerForceIncludingCustomMoves(MOVE_ID moveID);

#if defined(W2U_BATTLE_CHILD)
extern "C" BattleEventItem** W2U_MoveState_StickyWebItemStorage(u32 side);
extern "C" bool* W2U_MoveState_StickyWebActiveStorage(u32 side);
extern "C" BattleEventItem** W2U_MoveState_AuroraVeilItemStorage(u32 side);
extern "C" u8* W2U_MoveState_AuroraVeilTurnsStorage(u32 side);
extern "C" bool* W2U_MoveState_AuroraVeilActiveStorage(u32 side);
extern "C" BattleEventItem** W2U_MoveState_TerrainItemStorage();
extern "C" TERRAIN* W2U_MoveState_TerrainTypeStorage();
extern "C" u8* W2U_MoveState_TerrainTurnsStorage();
extern "C" bool* W2U_MoveState_TerrainActiveStorage();
extern "C" BattleEventItem** W2U_MoveState_TransientItemStorage();
extern "C" u32* W2U_MoveState_ConsumedBerryFlagsStorage();
extern "C" u32* W2U_MoveState_ElectrifiedFlagsStorage();
extern "C" u32* W2U_MoveState_BeakBlastChargeCueFlagsStorage();
extern "C" u32* W2U_MoveState_MatBlockProtectedFlagsStorage();
extern "C" u32* W2U_MoveState_PowderedFlagsStorage();
extern "C" u32* W2U_MoveState_SpikyShieldFlagsStorage();
extern "C" u32* W2U_MoveState_SpikyShieldDamagedFlagsStorage();
extern "C" u32* W2U_MoveState_BanefulBunkerFlagsStorage();
extern "C" u32* W2U_MoveState_BanefulBunkerPoisonedFlagsStorage();
extern "C" u32* W2U_MoveState_KingsShieldFlagsStorage();
extern "C" u32* W2U_MoveState_KingsShieldLoweredFlagsStorage();
extern "C" bool* W2U_MoveState_IonDelugeActiveStorage();
extern "C" u32* W2U_MoveState_MatBlockFreshFlagsStorage();
extern "C" u32* W2U_MoveState_MatBlockEnteredFlagsStorage();
extern "C" bool* W2U_MoveState_MatBlockActiveStorage(u32 side);
extern "C" bool* W2U_MoveState_CraftyShieldActiveStorage(u32 side);
extern "C" u8* W2U_MoveState_MatBlockOwnerStorage(u32 side);
extern "C" u8* W2U_MoveState_CraftyShieldOwnerStorage(u32 side);
extern "C" u8* W2U_MoveState_ExtraTypeStorage(u32 pokemonSlot);
extern "C" u32* W2U_MoveState_StompingFailureLastTurnStorage();
extern "C" u32* W2U_MoveState_StompingFailureThisTurnStorage();
extern "C" u32* W2U_MoveState_StompingProtectedThisMoveStorage();
extern "C" bool* W2U_MoveState_BattleTrackingActiveStorage();
#else
MoveState sMoveState;

#define W2U_MOVE_STATE_SCALAR_STORAGE(type, name, expression) \
    extern "C" type* name() { return &(expression); }
#define W2U_MOVE_STATE_INDEXED_STORAGE(type, name, expression) \
    extern "C" type* name(u32 index) { return &(expression); }

W2U_MOVE_STATE_INDEXED_STORAGE(
    BattleEventItem*, W2U_MoveState_StickyWebItemStorage, sMoveState.stickyWeb[index].item)
W2U_MOVE_STATE_INDEXED_STORAGE(
    bool, W2U_MoveState_StickyWebActiveStorage, sMoveState.stickyWeb[index].active)
W2U_MOVE_STATE_INDEXED_STORAGE(
    BattleEventItem*, W2U_MoveState_AuroraVeilItemStorage, sMoveState.auroraVeil[index].item)
W2U_MOVE_STATE_INDEXED_STORAGE(
    u8, W2U_MoveState_AuroraVeilTurnsStorage, sMoveState.auroraVeil[index].turns)
W2U_MOVE_STATE_INDEXED_STORAGE(
    bool, W2U_MoveState_AuroraVeilActiveStorage, sMoveState.auroraVeil[index].active)
W2U_MOVE_STATE_SCALAR_STORAGE(
    BattleEventItem*, W2U_MoveState_TerrainItemStorage, sMoveState.terrain.item)
W2U_MOVE_STATE_SCALAR_STORAGE(
    TERRAIN, W2U_MoveState_TerrainTypeStorage, sMoveState.terrain.terrain)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u8, W2U_MoveState_TerrainTurnsStorage, sMoveState.terrain.turns)
W2U_MOVE_STATE_SCALAR_STORAGE(
    bool, W2U_MoveState_TerrainActiveStorage, sMoveState.terrain.active)
W2U_MOVE_STATE_SCALAR_STORAGE(
    BattleEventItem*, W2U_MoveState_TransientItemStorage, sMoveState.transientItem)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_ConsumedBerryFlagsStorage, sMoveState.consumedBerryFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_ElectrifiedFlagsStorage, sMoveState.electrifiedFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_BeakBlastChargeCueFlagsStorage, sMoveState.beakBlastChargeCueFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_MatBlockProtectedFlagsStorage, sMoveState.matBlockProtectedFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_PowderedFlagsStorage, sMoveState.powderedFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_SpikyShieldFlagsStorage, sMoveState.spikyShieldFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_SpikyShieldDamagedFlagsStorage, sMoveState.spikyShieldDamagedFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_BanefulBunkerFlagsStorage, sMoveState.banefulBunkerFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_BanefulBunkerPoisonedFlagsStorage, sMoveState.banefulBunkerPoisonedFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    bool, W2U_MoveState_IonDelugeActiveStorage, sMoveState.ionDelugeActive)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_MatBlockFreshFlagsStorage, sMoveState.matBlockFreshFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_MatBlockEnteredFlagsStorage, sMoveState.matBlockEnteredThisTurnFlags)
W2U_MOVE_STATE_INDEXED_STORAGE(
    bool, W2U_MoveState_MatBlockActiveStorage, sMoveState.matBlockActive[index])
W2U_MOVE_STATE_INDEXED_STORAGE(
    bool, W2U_MoveState_CraftyShieldActiveStorage, sMoveState.craftyShieldActive[index])
W2U_MOVE_STATE_INDEXED_STORAGE(
    u8, W2U_MoveState_MatBlockOwnerStorage, sMoveState.matBlockOwner[index])
W2U_MOVE_STATE_INDEXED_STORAGE(
    u8, W2U_MoveState_CraftyShieldOwnerStorage, sMoveState.craftyShieldOwner[index])
W2U_MOVE_STATE_INDEXED_STORAGE(
    u8, W2U_MoveState_ExtraTypeStorage, sMoveState.extraTypes[index])
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_StompingFailureLastTurnStorage, sMoveState.stompingFailureLastTurnFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_StompingFailureThisTurnStorage, sMoveState.stompingFailureThisTurnFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    u32, W2U_MoveState_StompingProtectedThisMoveStorage, sMoveState.stompingProtectedThisMoveFlags)
W2U_MOVE_STATE_SCALAR_STORAGE(
    bool, W2U_MoveState_BattleTrackingActiveStorage, sMoveState.battleTrackingActive)

#undef W2U_MOVE_STATE_INDEXED_STORAGE
#undef W2U_MOVE_STATE_SCALAR_STORAGE
#endif

#define sStickyWebItem(side) (*W2U_MoveState_StickyWebItemStorage(side))
#define sStickyWebActive(side) (*W2U_MoveState_StickyWebActiveStorage(side))
#define sAuroraVeilItem(side) (*W2U_MoveState_AuroraVeilItemStorage(side))
#define sAuroraVeilTurns(side) (*W2U_MoveState_AuroraVeilTurnsStorage(side))
#define sAuroraVeilActive(side) (*W2U_MoveState_AuroraVeilActiveStorage(side))
#define sTerrainItem (*W2U_MoveState_TerrainItemStorage())
#define sTerrainType (*W2U_MoveState_TerrainTypeStorage())
#define sTerrainTurns (*W2U_MoveState_TerrainTurnsStorage())
#define sTerrainActive (*W2U_MoveState_TerrainActiveStorage())
#define sTransientItem (*W2U_MoveState_TransientItemStorage())
#define sConsumedBerryFlags (*W2U_MoveState_ConsumedBerryFlagsStorage())
#define sElectrifiedFlags (*W2U_MoveState_ElectrifiedFlagsStorage())
#define sBeakBlastChargeCueFlags (*W2U_MoveState_BeakBlastChargeCueFlagsStorage())
#define sMatBlockProtectedFlags (*W2U_MoveState_MatBlockProtectedFlagsStorage())
#define sPowderedFlags (*W2U_MoveState_PowderedFlagsStorage())
#define sSpikyShieldFlags (*W2U_MoveState_SpikyShieldFlagsStorage())
#define sSpikyShieldDamagedFlags (*W2U_MoveState_SpikyShieldDamagedFlagsStorage())
#define sBanefulBunkerFlags (*W2U_MoveState_BanefulBunkerFlagsStorage())
#define sBanefulBunkerPoisonedFlags (*W2U_MoveState_BanefulBunkerPoisonedFlagsStorage())
#define sIonDelugeActive (*W2U_MoveState_IonDelugeActiveStorage())
#define sMatBlockFreshFlags (*W2U_MoveState_MatBlockFreshFlagsStorage())
#define sMatBlockEnteredThisTurnFlags (*W2U_MoveState_MatBlockEnteredFlagsStorage())
#define sMatBlockActive(side) (*W2U_MoveState_MatBlockActiveStorage(side))
#define sCraftyShieldActive(side) (*W2U_MoveState_CraftyShieldActiveStorage(side))
#define sMatBlockOwner(side) (*W2U_MoveState_MatBlockOwnerStorage(side))
#define sCraftyShieldOwner(side) (*W2U_MoveState_CraftyShieldOwnerStorage(side))
#define sExtraType(slot) (*W2U_MoveState_ExtraTypeStorage(slot))
#define sStompingFailureLastTurnFlags (*W2U_MoveState_StompingFailureLastTurnStorage())
#define sStompingFailureThisTurnFlags (*W2U_MoveState_StompingFailureThisTurnStorage())
#define sStompingProtectedThisMoveFlags (*W2U_MoveState_StompingProtectedThisMoveStorage())
#define sBattleTrackingActive (*W2U_MoveState_BattleTrackingActiveStorage())

#if !defined(W2U_BATTLE_CHILD)
void ClearMoveState()
{
    W2U_Weather_Reset();
    W2U_Revival_Reset();
    volatile u8* bytes = (volatile u8*)&sMoveState;
    for (u32 idx = 0; idx < sizeof(sMoveState); ++idx) {
        bytes[idx] = 0;
    }
}

void InitExtraTypes()
{
    for (u32 idx = 0; idx < BATTLE_MAX_SLOTS; ++idx) {
        sExtraType(idx) = TYPE_NULL;
    }
}

void InitLocalMoveState()
{
    InitExtraTypes();
    sMatBlockFreshFlags = W2U_ALL_BATTLE_SLOT_FLAGS;
    sMoveState.spotlightTargetSlot = BATTLE_MAX_SLOTS;
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        sMatBlockOwner(side) = BATTLE_MAX_SLOTS;
        sCraftyShieldOwner(side) = BATTLE_MAX_SLOTS;
    }
}
#endif

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

void SetSlotFlag(u32& flags, u32 pokemonSlot, bool enabled)
{
    const u32 mask = SlotMask(pokemonSlot);
    if (!mask) {
        return;
    }
    if (enabled) {
        flags |= mask;
    } else {
        flags &= ~mask;
    }
}

void MarkStompingProtection(u32 attackingSlot)
{
    SetSlotFlag(sStompingProtectedThisMoveFlags, attackingSlot, true);
}

void ClearStompingOutcomeState(u32 pokemonSlot)
{
    SetSlotFlag(sStompingFailureLastTurnFlags, pokemonSlot, false);
    SetSlotFlag(sStompingFailureThisTurnFlags, pokemonSlot, false);
    SetSlotFlag(sStompingProtectedThisMoveFlags, pokemonSlot, false);
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
    // BATTLE_MAX_SLOTS is the event sentinel/bitmask limit (31), not the
    // native battler-array length (24). End-of-turn history scans visit the
    // sentinel range; never let slots 24..30 read beyond PokeCon's array.
    if (!serverFlow || !serverFlow->pokeCon ||
        pokemonSlot >= W2U_ARRAY_COUNT(serverFlow->pokeCon->activeBattleMon)) {
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
    case MOVE_BANEFUL_BUNKER:
    case MOVE_KINGS_SHIELD:
    case MOVE_SPIKY_SHIELD:
    case MOVE_OBSTRUCT:
    case MOVE_SILK_TRAP:
    case MOVE_BURNING_BULWARK:
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
    // Protect-family chaining follows the last move that actually executed,
    // rather than the last selected/original move.  This matches native
    // Protect and PW2Code's expanded Protect handler, including forced-move
    // cases where those two histories can differ.
    if (!currentMon || IsProtectCounterMove(BattleMon_GetPreviousMoveID(currentMon))) {
        return;
    }

    ResetProtectCounter(serverFlow, pokemonSlot);
}

// Native Protect/Detect/Endure/Wide Guard/Quick Guard share this start
// handler. Extend their previous-move whitelist too, so chaining works in
// both directions without loading a child for an otherwise vanilla battle.
#if !defined(W2U_BATTLE_CHILD)
extern "C" void THUMB_BRANCH_HandlerProtectStart(
    BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        StartProtectCounterMove(serverFlow, pokemonSlot);
    }
}
#endif

bool TryApplySpikyShieldDamage(ServerFlow* serverFlow, u32 defendingSlot, u32 attackingSlot, MOVE_ID moveID)
{
    if (!(sSpikyShieldFlags & SlotMask(defendingSlot)) ||
        !IsValidSlot(attackingSlot) ||
        MainModule_IsAllyMonID(attackingSlot, defendingSlot) ||
        !W2U_MoveMakesContact(serverFlow, moveID, attackingSlot) ||
        (sSpikyShieldDamagedFlags & SlotMask(attackingSlot))) {
        return false;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (!attackingMon || BattleMon_IsFainted(attackingMon)) {
        return false;
    }

    sSpikyShieldDamagedFlags |= SlotMask(attackingSlot);
    PushDamage(
        serverFlow,
        defendingSlot,
        attackingSlot,
        DivideMaxHPZeroCheck(attackingMon, 8),
        BATTLE_SPIKY_SHIELD_DAMAGE_MSGID,
        attackingSlot);
    return true;
}

bool TryApplyBanefulBunkerPoison(
    ServerFlow* serverFlow,
    u32 defendingSlot,
    u32 attackingSlot,
    MOVE_ID moveID)
{
    if (!(sBanefulBunkerFlags & SlotMask(defendingSlot)) ||
        !IsValidSlot(attackingSlot) ||
        MainModule_IsAllyMonID(attackingSlot, defendingSlot) ||
        !W2U_MoveMakesContact(serverFlow, moveID, attackingSlot) ||
        (sBanefulBunkerPoisonedFlags & SlotMask(attackingSlot))) {
        return false;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (!attackingMon || BattleMon_IsFainted(attackingMon)) {
        return false;
    }

    HandlerParam_AddCondition* addCondition =
        (HandlerParam_AddCondition*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_ADD_CONDITION,
            defendingSlot);
    if (!addCondition) {
        return false;
    }

    sBanefulBunkerPoisonedFlags |= SlotMask(attackingSlot);
    addCondition->condition = CONDITION_POISON;
    addCondition->condData = MakeBasicStatus(CONDITION_POISON);
    addCondition->almost = 0;
    addCondition->pokeID = (u8)attackingSlot;
    BattleHandler_PopWork(serverFlow, addCondition);
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

void CureMoveCondition(
    ServerFlow* serverFlow,
    u32 sourceSlot,
    u32 targetSlot,
    CONDITION condition)
{
    HandlerParam_CureCondition* cure =
        (HandlerParam_CureCondition*)BattleHandler_PushWork(serverFlow, EFFECT_CURE_STATUS, sourceSlot);
    cure->condition = condition;
    cure->pokeCount = 1;
    cure->pokeID[0] = (u8)targetSlot;
    BattleHandler_PopWork(serverFlow, cure);
}

void CureMoveCondition(ServerFlow* serverFlow, u32 pokemonSlot, CONDITION condition)
{
    CureMoveCondition(serverFlow, pokemonSlot, pokemonSlot, condition);
}

bool IsPurifiableStatus(CONDITION condition)
{
    switch (condition) {
    case CONDITION_PARALYSIS:
    case CONDITION_SLEEP:
    case CONDITION_FREEZE:
    case CONDITION_BURN:
    case CONDITION_POISON:
        return true;
    default:
        return false;
    }
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
    if (side >= W2U_SIDE_COUNT || !sStickyWebActive(side)) {
        return false;
    }

    if (sStickyWebItem(side)) {
        BattleEventItem_Remove(sStickyWebItem(side));
    }
    sStickyWebItem(side) = 0;
    sStickyWebActive(side) = false;

    if (showMessage) {
        PushMessage(serverFlow, pokemonSlot, 1u, BATTLE_STICKY_WEB_REMOVE_MSGID + side);
    }
    return true;
}

bool RemoveAuroraVeilSide(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32 side,
    bool showMessage)
{
    if (side >= W2U_SIDE_COUNT || !sAuroraVeilActive(side)) {
        return false;
    }

    if (sAuroraVeilItem(side)) {
        BattleEventItem_Remove(sAuroraVeilItem(side));
    }
    sAuroraVeilItem(side) = 0;
    sAuroraVeilTurns(side) = 0;
    sAuroraVeilActive(side) = false;

    if (showMessage && serverFlow) {
        PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_AURORA_VEIL_END_MSGID);
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
    if (checkedEffectiveness == W2U_EFFECTIVENESS_16) return damage * 16;
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
    if (effectiveness == W2U_EFFECTIVENESS_16) return 128;
    return 0xFFFFFFFFu;
}

BattleEventItem* AddTransientMoveStateEvent(u32 pokemonSlot);
BattleEventItem* AddTerrainEvent(u32 pokemonSlot);
BattleEventItem* AddSpotlightEvent();

bool RemoveTerrainState(ServerFlow* serverFlow, bool showEndMessage, bool requestTextureReset = true)
{
    if (!sTerrainActive) {
        return false;
    }

    if (sTerrainItem) {
        BattleEventItem_Remove(sTerrainItem);
    }

    sTerrainItem = 0;
    sTerrainType = TERRAIN_NULL;
    sTerrainTurns = 0;
    sTerrainActive = false;

    if (requestTextureReset) {
        if (showEndMessage && serverFlow) {
            W2U_TerrainTexture_DeferResetUntilMessage(BATTLE_TERRAIN_END_MSGID);
        } else {
            W2U_TerrainTexture_Request(TERRAIN_NULL);
        }
    }

    if (showEndMessage && serverFlow) {
        PushMessage(serverFlow, BATTLE_MAX_SLOTS, 2u, BATTLE_TERRAIN_END_MSGID);
    }
    return true;
}

u8 ResolveTerrainTurnCount(ServerFlow* serverFlow, u32 pokemonSlot, TERRAIN terrain)
{
    if (!serverFlow) {
        return W2U_TERRAIN_TURNS;
    }

    // PW2Code exposes the weather turn-count event to Terrain Extender using
    // a terrain-specific new-event payload. Item handlers contribute only
    // the number of extra turns, keeping the five-turn base in the core.
    BattleEventVar_Push();
    SetupNewEvent();
    BattleEventVar_SetConstValue(NEW_VAR_ATTACKING_MON, pokemonSlot);
    BattleEventVar_SetConstValue(VAR_WEATHER, terrain);
    BattleEventVar_SetValue(VAR_EFFECT_TURN_COUNT, 0);
    BattleEvent_CallHandlers(serverFlow, EVENT_MOVE_TERRAIN_TURN_COUNT);
    const u32 extraTurns = (u32)BattleEventVar_GetValue(VAR_EFFECT_TURN_COUNT);
    BattleEventVar_Pop();

    const u32 totalTurns = W2U_TERRAIN_TURNS + extraTurns;
    return (u8)(totalTurns > 0xFFu ? 0xFFu : totalTurns);
}

bool SetTerrainState(ServerFlow* serverFlow, u32 pokemonSlot, TERRAIN terrain)
{
    if (sTerrainActive && sTerrainType == terrain) {
        return false;
    }

    // Replacing one terrain with another does not show the generic expiry
    // message between the old and new terrain announcements.
    RemoveTerrainState(0, false, false);

    BattleEventItem* item = AddTerrainEvent(pokemonSlot);
    if (!item) {
        W2U_TerrainTexture_Request(TERRAIN_NULL);
        return false;
    }

    sTerrainItem = item;
    sTerrainType = terrain;
    sTerrainTurns = ResolveTerrainTurnCount(serverFlow, pokemonSlot, terrain);
    sTerrainActive = true;
    W2U_TerrainTexture_Request(terrain);

    return true;
}

void NotifyTerrainChanged(ServerFlow* serverFlow, TERRAIN terrain)
{
    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    // Mirror PW2Code's post-change terrain event: every active, non-fainted
    // battler receives one new-event payload. Item handlers use this to
    // activate Terrain Seeds immediately when a move or Surge sets terrain.
    for (u32 index = 0; index < 24u; ++index) {
        BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, index);
        if (!battleMon || BattleMon_IsFainted(battleMon)) {
            continue;
        }

        const u32 pokemonSlot = BattleMon_GetID(battleMon);
        if (!IsValidSlot(pokemonSlot) ||
            Handler_PokeIDToPokePos(serverFlow, pokemonSlot) >= W2U_NULL_BATTLE_POS) {
            continue;
        }

        const u32 HEID = HEManager_PushState(&serverFlow->HEManager);
        BattleEventVar_Push();
        SetupNewEvent();
        BattleEventVar_SetConstValue(NEW_VAR_MON_ID, pokemonSlot);
        BattleEventVar_SetConstValue(VAR_WEATHER, terrain);
        BattleEvent_CallHandlers(serverFlow, EVENT_AFTER_TERRAIN_CHANGE);
        BattleEventVar_Pop();
        HEManager_PopState(&serverFlow->HEManager, HEID);
    }
}

bool SetTerrain(ServerFlow* serverFlow, u32 pokemonSlot, TERRAIN terrain, u32 msgID)
{
    if (!SetTerrainState(serverFlow, pokemonSlot, terrain)) {
        return false;
    }

    PushMessage(serverFlow, pokemonSlot, 2u, msgID);
    NotifyTerrainChanged(serverFlow, terrain);
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
    sMatBlockProtectedFlags = 0;
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        sMatBlockActive(side) = false;
        sMatBlockOwner(side) = BATTLE_MAX_SLOTS;
    }
}

void ClearCraftyShieldState()
{
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        sCraftyShieldActive(side) = false;
        sCraftyShieldOwner(side) = BATTLE_MAX_SLOTS;
    }
}

void SetMatBlockFresh(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMatBlockFreshFlags |= mask;
        sMatBlockEnteredThisTurnFlags |= mask;
    }
}

bool IsMatBlockFresh(ServerFlow* serverFlow, u32 pokemonSlot)
{
    BattleMon* battleMon = GetBattleMon(serverFlow, pokemonSlot);
    return serverFlow && battleMon && battleMon->appearedTurn == (u16)serverFlow->turnCount;
}

void ClearEndOfTurnMoveState()
{
#if !defined(W2U_BATTLE_CHILD)
    sMoveState.statsRaisedThisTurnFlags = 0;
    sMoveState.statsLoweredThisTurnFlags = 0;
#endif
    ClearMatBlockState();
    ClearCraftyShieldState();
    W2U_MoveState_ClearElectrified();
    W2U_MoveState_ClearAllBeakBlast();
    sBeakBlastChargeCueFlags = 0;
    W2U_MoveState_ClearAllShellTraps();
    sPowderedFlags = 0;
    sSpikyShieldFlags = 0;
    sSpikyShieldDamagedFlags = 0;
    sBanefulBunkerFlags = 0;
    sBanefulBunkerPoisonedFlags = 0;
    sIonDelugeActive = false;
    sMatBlockFreshFlags &= sMatBlockEnteredThisTurnFlags;
    sMatBlockEnteredThisTurnFlags = 0;
}

bool HasTransientMoveState()
{
    if (sBattleTrackingActive ||
        sElectrifiedFlags ||
        W2U_MoveState_HasLaserFocus() ||
        W2U_MoveState_HasThroatChop() ||
        W2U_MoveState_HasBeakBlastCharging() ||
        sBeakBlastChargeCueFlags ||
        W2U_MoveState_HasShellTrap() ||
        sMatBlockProtectedFlags ||
        sPowderedFlags ||
        sSpikyShieldFlags ||
        sBanefulBunkerFlags ||
        sIonDelugeActive) {
        return true;
    }
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        if (sMatBlockActive(side) || sCraftyShieldActive(side)) {
            return true;
        }
    }
    return false;
}

bool IsTerrainActive(TERRAIN terrain)
{
    return sTerrainActive && sTerrainType == terrain;
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
    // This routine lives in battle overlay 169 at 0x0689xxxx, outside the
    // range of a Thumb BL from the resident W2U module.  Keep the target in a
    // volatile function pointer so the compiler emits an absolute BLX instead
    // of a wrapped PC-relative branch.
    PosEffectEventCanRegisterFunc volatile canRegister = W2U_POS_EVENT_CAN_REGISTER;
    if (!handlers || handlerAmount == 0 || !canRegister(posEffect, targetPos)) {
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

#if !defined(W2U_BATTLE_CHILD)
extern "C" bool W2U_MoveState_EnsureTransientEvent(u32 pokemonSlot)
{
    if (sTransientItem) {
        return true;
    }

    sTransientItem = AddTransientMoveStateEvent(pokemonSlot);
    return sTransientItem != 0;
}
#endif

void RemoveTransientMoveStateEvent()
{
    if (sTransientItem) {
        BattleEventItem_Remove(sTransientItem);
    }
    sTransientItem = 0;
}

void SetMatBlockForActiveSide(ServerFlow* serverFlow, u32 ownerSlot, u32 side)
{
    if (!serverFlow || !serverFlow->pokeCon) {
        return;
    }

    sMatBlockActive(side) = true;
    sMatBlockOwner(side) = (u8)ownerSlot;

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
            sMatBlockProtectedFlags |= SlotMask(allySlot);
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

#if !defined(W2U_BATTLE_CHILD)
extern "C" void W2U_MoveState_ResetBattleState()
{
    ClearMoveState();
    InitLocalMoveState();
    W2U_TerrainTexture_Request(TERRAIN_NULL);
}

extern "C" void W2U_MoveState_BeginBattleTracking(u32 fallbackPokemonSlot)
{
    // Prefer an ownerless field event so switching the first battler cannot
    // retire the tracker.  Some setup states reject the sentinel dependency;
    // after SwitchInCore/MoveEvent registration we can safely retry with the
    // actual battler as a compatibility fallback.
    sBattleTrackingActive =
        W2U_MoveState_EnsureTransientEvent(BATTLE_MAX_SLOTS) ||
        (IsValidSlot(fallbackPokemonSlot) &&
            W2U_MoveState_EnsureTransientEvent(fallbackPokemonSlot));
}

extern "C" void FaintRecord_Add(FaintRecord*, u32 slot);
extern "C" void W2U_RecordCommittedFaint(FaintRecord* record, u32 slot, ServerFlow* flow)
{
    // Called only after native CheckFainted has changed its dead latch 0->1.
    // Do not count notify-dead events: the engine also emits those on switches.
    FaintRecord_Add(record, slot);
    if (flow && !flow->simulationCounter && slot < 24) {
        const u32 party = W2U_GetBattlePartyOwner(flow, slot);
        if (party >= 4) return;
        u8& count = sMoveState.faintEvents[party];
        if (count < 100) ++count;
    }
}

extern "C" u32 W2U_MoveState_LastRespectsPower(ServerFlow* flow, u32 slot)
{
    if (!flow || !flow->pokeCon || slot >= 24 ||
        flow->pokeCon->party[2].memberCount || flow->pokeCon->party[3].memberCount)
        return 0; // Multi-trainer semantics deliberately excluded for now.
    const u32 party = W2U_GetBattlePartyOwner(flow, slot);
    if (party >= 4) return 0;
    return 50u + 50u * sMoveState.faintEvents[party];
}

extern "C" bool W2U_MoveState_DidLastMoveFailForStomping(u32 pokemonSlot)
{
    const u32 mask = SlotMask(pokemonSlot);
    return mask && (sStompingFailureLastTurnFlags & mask);
}

extern "C" bool W2U_MoveState_HadStatChangeThisTurn(u32 pokemonSlot, bool raised)
{
    if (!IsValidSlot(pokemonSlot)) return false;
    return ((raised ? sMoveState.statsRaisedThisTurnFlags :
        sMoveState.statsLoweredThisTurnFlags) & SlotMask(pokemonSlot)) != 0;
}

extern "C" bool W2U_MoveState_CreateShedTailSub(ServerFlow* flow, u32 slot)
{
    if (!flow || flow->simulationCounter || !IsValidSlot(slot)) return false;
    BattleMon* mon = GetBattleMon(flow, slot);
    const u32 pos = Handler_PokeIDToPokePos(flow, slot);
    if (!mon || BattleMon_IsFainted(mon) || BattleMon_IsSubstituteActive(mon) ||
        pos >= W2U_NULL_BATTLE_POS) return false;
    const u32 maximum = BattleMon_GetValue(mon, VALUE_MAX_HP);
    const u32 cost = (maximum + 1) / 2;
    const u32 doll = maximum / 4;
    if (!doll || BattleMon_GetValue(mon, VALUE_CURRENT_HP) <= cost ||
        !W2U_MoveState_EnsureTransientEvent(slot)) return false;

    // Same order as native Substitute, with Shed Tail's different payment.
    // SimpleHP is direct payment, not damage/recoil; HP berries react before
    // the doll is created or the mandatory replacement request is issued.
    ServerDisplay_SimpleHP(flow, mon, -(s32)cost, true);
    ServerControl_CheckItemReaction(flow, mon, 1);
    BattleMon_CreateSubstitute(mon, (u16)doll);
    ServerDisplay_AddCommon(flow->serverCommandQueue, SCID_CreateSubstitute, slot, doll);
    ServerDisplay_AddCommon(flow->serverCommandQueue, SCID_SubstituteAppear, pos);
    ServerDisplay_AddMessageImpl(flow->serverCommandQueue, SCID_SetMessage, 785, slot, 0xFFFF0000);
    sMoveState.shedTailTransferFlags |= SlotMask(slot);
    return true;
}

extern "C" void W2U_MoveState_PrepareShedTailExit(BattleMon* mon)
{
    if (!mon || !(sMoveState.shedTailTransferFlags & SlotMask(mon->battleSlot)) ||
        !BattleMon_GetConditionFlag(mon, CONDITIONFLAG_BATONPASS)) return;
    // Called by the existing native exit replacement on both server and
    // client copies, before Baton Pass tests Gastro Acid or copies state.
    // Keep the doll and Baton flag only. Major status is not cured.
    ClearMoveStatusWork(mon, false);
    ResetStatStages(&mon->statStageParam);
    BattleMon_ResetConditionFlag(mon, 9);  // Focus Energy
    BattleMon_ResetConditionFlag(mon, 10); // Power Trick
    // Do not clear the resident marker here: the delayed client still needs
    // it. The source's next real action (including ordinary Baton Pass)
    // retires it; battle teardown clears the entire resident state.
}

static void RecordPartyMemberDirectHit(u32 slot)
{
    if (slot < W2U_ARRAY_COUNT(sMoveState.directHitsReceived) &&
        sMoveState.directHitsReceived[slot] < 6) ++sMoveState.directHitsReceived[slot];
}

extern "C" u32 W2U_MoveState_RageFistPower(u32 slot)
{
    return 50u + 50u * (slot < W2U_ARRAY_COUNT(sMoveState.directHitsReceived)
        ? sMoveState.directHitsReceived[slot] : 0);
}

extern "C" void W2U_MoveState_RecordDisguiseHit(ServerFlow* flow, u32 slot)
{
    // Disguise's zero-damage strike never reaches the ordinary positive-HP
    // test. Its real-execution callback records it once, before form work.
    if (flow && !flow->simulationCounter &&
        slot == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) < 24 &&
        (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) != slot)
        RecordPartyMemberDirectHit(slot);
}

extern "C" void W2U_CopyTransformMoveState(BattleMon* user, BattleMon* target)
{
    W2U_CopyCriticalBoost(user, target);
    if (user && target && user->battleSlot < 24 && target->battleSlot < 24)
        sMoveState.directHitsReceived[user->battleSlot] = sMoveState.directHitsReceived[target->battleSlot];
}

extern "C" bool W2U_MoveState_CourtChange(ServerFlow* flow)
{
    if (!flow || flow->simulationCounter) return false;
    NativeSideEffectRecord (*native)[14] = GetNativeSideState();
    if (!native) return false;
    const u16 customIds[] = { SIDEEFF_STICKY_WEB, SIDEEFF_AURORA_VEIL };
    const W2UBattleHandlerExport* customApis[2] = {};
    for (u32 i = 0; i < 2; ++i) {
        const bool active = i ? (sMoveState.auroraVeil[0].active || sMoveState.auroraVeil[1].active)
                             : (sMoveState.stickyWeb[0].active || sMoveState.stickyWeb[1].active);
        if (!active) continue;
#if defined(W2U_DYNAMIC_BATTLE_CORE)
        customApis[i] = W2U_BattleModules_FindLoaded(W2U_MECHANIC_SIDE, customIds[i]);
#else
        customApis[i] = W2U_BattleStatic_Resolve(W2U_MECHANIC_SIDE, customIds[i]);
#endif
        if (!customApis[i]) return false;
    }
    // This turn's Wide/Quick/Mat Block/Crafty Shield are not swappable.
    // Native layers, original duration and elapsed turns travel
    // together; recreating ownership does not re-run Light Clay or entry work.
    const u8 effects[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13 };
    bool changed = false;
    for (u32 i = 0; i < W2U_ARRAY_COUNT(effects); ++i) {
        const u32 effect = effects[i];
        const NativeSideEffectRecord old[2] = { native[0][effect], native[1][effect] };
        if (!old[0].item && !old[1].item) continue;
        changed = true;
        for (u32 side = 0; side < 2; ++side) {
            if (native[side][effect].item) BattleEventItem_Remove(native[side][effect].item);
            native[side][effect].item = 0;
            native[side][effect].layers = 0;
        }
        for (u32 side = 0; side < 2; ++side) {
            const NativeSideEffectRecord& incoming = old[1 - side];
            if (!incoming.item) continue;
            BattleEventItem* item = SideEffectEvent_AddItem(side, effect, incoming.condition);
            if (!item) continue; // no stale pointer if native registration fails
            native[side][effect].elapsed = incoming.elapsed;
            native[side][effect].layers = incoming.layers;
        }
    }
    for (u32 i = 0; i < 2; ++i) {
        if (!customApis[i]) continue;
        const bool active[2] = { i ? sMoveState.auroraVeil[0].active : sMoveState.stickyWeb[0].active,
                                i ? sMoveState.auroraVeil[1].active : sMoveState.stickyWeb[1].active };
        const u8 turns[2] = { sMoveState.auroraVeil[0].turns, sMoveState.auroraVeil[1].turns };
        for (u32 side = 0; side < 2; ++side) {
            BattleEventItem* item = i ? sMoveState.auroraVeil[side].item : sMoveState.stickyWeb[side].item;
            if (item) BattleEventItem_Remove(item);
        }
        for (u32 side = 0; side < 2; ++side) {
            BattleEventItem* item = active[1 - side] ? BattleEvent_AddItem(EVENTITEM_SIDE,
                customIds[i], EVENTPRI_SIDE_DEFAULT, 0, side, customApis[i]->handlers, customApis[i]->handlerCount) : 0;
            if (i) {
                sMoveState.auroraVeil[side].item = item;
                sMoveState.auroraVeil[side].active = item != 0;
                sMoveState.auroraVeil[side].turns = item ? turns[1 - side] : 0;
            } else {
                sMoveState.stickyWeb[side].item = item;
                sMoveState.stickyWeb[side].active = item != 0;
            }
        }
        changed = true;
    }
    return changed;
}

extern "C" void W2U_MoveState_SetShellSideArmCategory(u32 slot, u32 category)
{
    const u32 mask = SlotMask(slot);
    if (!mask) return;
    sMoveState.shellSideArmCategoryValidFlags |= mask;
    if (category == SPLIT_PHYSICAL) sMoveState.shellSideArmPhysicalFlags |= mask;
    else sMoveState.shellSideArmPhysicalFlags &= ~mask;
}

extern "C" u32 W2U_MoveState_ShellSideArmCategory(u32 slot)
{
    const u32 mask = SlotMask(slot);
    return (mask && (sMoveState.shellSideArmCategoryValidFlags & mask) &&
        (sMoveState.shellSideArmPhysicalFlags & mask)) ? SPLIT_PHYSICAL : SPLIT_SPECIAL;
}

extern "C" bool W2U_MoveState_ApplyTarShot(u32 slot)
{
    if (!IsValidSlot(slot)) return false;
    const bool changed = !(sMoveState.tarShotFlags & SlotMask(slot));
    sMoveState.tarShotFlags |= SlotMask(slot);
    return changed;
}

extern "C" bool W2U_MoveState_HasTarShot(u32 slot)
{
    return IsValidSlot(slot) && (sMoveState.tarShotFlags & SlotMask(slot));
}

extern "C" bool W2U_MoveState_HasNoRetreat(u32 slot)
{
    return IsValidSlot(slot) && (sMoveState.noRetreatFlags & SlotMask(slot));
}

extern "C" bool W2U_MoveState_TryNoRetreat(u32 slot)
{
    if (!IsValidSlot(slot) || W2U_MoveState_HasNoRetreat(slot)) return false;
    sMoveState.noRetreatFlags |= SlotMask(slot);
    return true;
}

static int PersistentEffectIndex(MOVE_ID move)
{
    return move == MOVE_OCTOLOCK ? 0 : move == MOVE_SALT_CURE ? 1 :
        move == MOVE_SYRUP_BOMB ? 2 : -1;
}

extern "C" void W2U_MoveState_StartGlaiveRush(u32 slot)
{
    sMoveState.glaiveRushFlags |= SlotMask(slot);
}

extern "C" bool W2U_MoveState_EnsureAuxEvent(u16 fieldId, u32 owner)
{
    (void)owner;
    if (fieldId < 13 || fieldId > 14) return false;
    BattleEventItem*& item = sMoveState.auxItems[fieldId - 13];
    if (item) return true;
#if defined(W2U_DYNAMIC_BATTLE_CORE)
    const W2UBattleHandlerExport* entry = W2U_BattleModules_FindLoaded(W2U_MECHANIC_FIELD, fieldId);
#else
    const W2UBattleHandlerExport* entry = W2U_BattleStatic_Resolve(W2U_MECHANIC_FIELD, fieldId);
#endif
    if (!entry) return false;
    item = BattleEvent_AddItem(EVENTITEM_FIELD, fieldId, EVENTPRI_ABILITY_STALL,
        0, BATTLE_MAX_SLOTS, entry->handlers, entry->handlerCount);
    // A battle-long cached event must not depend on a departing battler.
    return item != 0;
}

extern "C" bool W2U_MoveState_HasPersistentEffect(MOVE_ID move, u32 target)
{
    const int index = PersistentEffectIndex(move);
    return index >= 0 && IsValidSlot(target) &&
        (sMoveState.persistentFlags[index] & SlotMask(target));
}

extern "C" bool W2U_MoveState_StartPersistentEffect(MOVE_ID move, u32 source, u32 target)
{
    const int index = PersistentEffectIndex(move);
    if (index < 0 || !IsValidSlot(source) || !IsValidSlot(target) ||
        W2U_MoveState_HasPersistentEffect(move, target)) return false;
    sMoveState.persistentSources[index][target] = (u8)source;
    sMoveState.persistentTurns[index][target] = move == MOVE_SYRUP_BOMB ? 3 : 255;
    sMoveState.persistentFlags[index] |= SlotMask(target);
    return true;
}

extern "C" u32 W2U_MoveState_PersistentSource(MOVE_ID move, u32 target)
{
    return W2U_MoveState_HasPersistentEffect(move, target)
        ? sMoveState.persistentSources[PersistentEffectIndex(move)][target] : BATTLE_MAX_SLOTS;
}

extern "C" void W2U_MoveState_TickPersistentEffect(MOVE_ID move, u32 target)
{
    const int index = PersistentEffectIndex(move);
    if (index >= 0 && W2U_MoveState_HasPersistentEffect(move, target) &&
        sMoveState.persistentTurns[index][target] != 255 &&
        --sMoveState.persistentTurns[index][target] == 0)
        sMoveState.persistentFlags[index] &= ~SlotMask(target);
}

extern "C" void W2U_MoveState_SetConsumedBerryFlag(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sConsumedBerryFlags |= mask;
    }
}

extern "C" bool W2U_MoveState_HasConsumedBerryFlag(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    return mask && (sConsumedBerryFlags & mask);
}

extern "C" void W2U_MoveState_SetExtraType(u32 pokemonSlot, u32 pokeType)
{
    if (IsValidSlot(pokemonSlot)) {
        sExtraType(pokemonSlot) = (u8)pokeType;
    }
}

extern "C" void W2U_MoveState_ClearExtraType(u32 pokemonSlot)
{
    if (IsValidSlot(pokemonSlot)) {
        sExtraType(pokemonSlot) = TYPE_NULL;
    }
}

extern "C" u32 W2U_MoveState_GetExtraType(u32 pokemonSlot)
{
    if (!IsValidSlot(pokemonSlot)) {
        return TYPE_NULL;
    }
    return sExtraType(pokemonSlot);
}

extern "C" u32 W2U_ResolveRevelationDanceType(BattleMon* battleMon)
{
    if (!battleMon) {
        return TYPE_NULL;
    }

    u32 primaryType = battleMon->Type1;
    u32 secondaryType = battleMon->Type2;

    // The native type-pair getter turns a pure Flying Pokemon into Normal
    // while Roost is active. Reproduce that rule without using the getter,
    // because it would also incorrectly turn Burn Up's typeless pair Normal.
    if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_ROOST)) {
        bool removedFlyingType =
            primaryType == TYPE_FLYING || secondaryType == TYPE_FLYING;
        if (primaryType == TYPE_FLYING) {
            primaryType = TYPE_NULL;
        }
        if (secondaryType == TYPE_FLYING) {
            secondaryType = TYPE_NULL;
        }
        if (primaryType >= TYPE_NULL && secondaryType < TYPE_NULL) {
            return secondaryType;
        }
        if (primaryType >= TYPE_NULL && removedFlyingType) {
            return TYPE_NORMAL;
        }
    }

    if (primaryType < TYPE_NULL) {
        return primaryType;
    }
    if (secondaryType < TYPE_NULL) {
        return secondaryType;
    }

    // Forest's Curse and Trick-or-Treat are stored as a separate added type.
    // They become Revelation Dance's only available type after a pure Fire
    // user burns itself out, but never replace Roost's pure-Flying fallback.
    u32 extraType = W2U_MoveState_GetExtraType(battleMon->battleSlot);
    return extraType < TYPE_NULL ? extraType : TYPE_NULL;
}

extern "C" void W2U_MoveState_StartLaserFocus(u32 pokemonSlot)
{
    if (IsValidSlot(pokemonSlot)) {
        // The current turn consumes one count at turn end; the second keeps
        // the effect active through the end of the user's next turn.
        sMoveState.laserFocusTurns[pokemonSlot] = 2;
    }
}

extern "C" bool W2U_MoveState_ApplyDragonCheer(ServerFlow* flow, u32 slot)
{
    BattleMon* mon = GetBattleMon(flow, slot);
    if (!IsValidSlot(slot) || !mon || BattleMon_GetConditionFlag(mon, 9)) return false;
    if (!W2U_MoveState_EnsureTransientEvent(slot)) return false;
    sMoveState.dragonCheerBoost[slot] = HasTypeWithExtra(mon, TYPE_DRAGON) ? 2 : 1;
    ServerDisplay_SetConditionFlag(flow, mon, 9);
    return true;
}

extern "C" void W2U_CopyCriticalBoost(BattleMon* user, BattleMon* target)
{
    if (!user || !target || !IsValidSlot(user->battleSlot) || !IsValidSlot(target->battleSlot)) return;
    sMoveState.dragonCheerBoost[user->battleSlot] =
        BattleMon_GetConditionFlag(target, 9) ? sMoveState.dragonCheerBoost[target->battleSlot] : 0;
    // Native Transform clears persistent flags after copying the surface.
    // This routine also runs for its client BattleMon, so update each local
    // flag through the native primitive rather than a server-only command.
    if (BattleMon_GetConditionFlag(target, 9)) BattleMon_SetConditionFlag(user, 9);
    else BattleMon_ResetConditionFlag(user, 9);
}

extern "C" bool W2U_MoveState_IsLaserFocused(u32 pokemonSlot)
{
    // Extra actions on the activation turn also receive the guarantee. The
    // two turn-end ticks expire it at the end of the following turn.
    return IsValidSlot(pokemonSlot) && sMoveState.laserFocusTurns[pokemonSlot] != 0;
}

extern "C" bool W2U_MoveState_HasLaserFocus()
{
    for (u32 pokemonSlot = 0; pokemonSlot < BATTLE_MAX_SLOTS; ++pokemonSlot) {
        if (sMoveState.laserFocusTurns[pokemonSlot] != 0) {
            return true;
        }
    }
    return false;
}

extern "C" void W2U_MoveState_TickLaserFocus(u32 pokemonSlot)
{
    if (IsValidSlot(pokemonSlot) && sMoveState.laserFocusTurns[pokemonSlot] != 0) {
        --sMoveState.laserFocusTurns[pokemonSlot];
    }
}

extern "C" void W2U_MoveState_ClearLaserFocus(u32 pokemonSlot)
{
    if (IsValidSlot(pokemonSlot)) {
        sMoveState.laserFocusTurns[pokemonSlot] = 0;
    }
}

extern "C" bool W2U_MoveState_StartThroatChop(u32 pokemonSlot)
{
    if (!IsValidSlot(pokemonSlot) || sMoveState.throatChopTurns[pokemonSlot] != 0) {
        return false;
    }

    // The application turn consumes the first count at turn end. The second
    // keeps sound moves disabled through the end of the following turn.
    sMoveState.throatChopTurns[pokemonSlot] = 2;
    return true;
}

extern "C" bool W2U_MoveState_IsThroatChopped(u32 pokemonSlot)
{
    return IsValidSlot(pokemonSlot) && sMoveState.throatChopTurns[pokemonSlot] != 0;
}

extern "C" bool W2U_MoveState_HasThroatChop()
{
    for (u32 pokemonSlot = 0; pokemonSlot < BATTLE_MAX_SLOTS; ++pokemonSlot) {
        if (sMoveState.throatChopTurns[pokemonSlot] != 0) {
            return true;
        }
    }
    return false;
}

extern "C" bool W2U_MoveState_TickThroatChop(u32 pokemonSlot)
{
    if (!IsValidSlot(pokemonSlot) || sMoveState.throatChopTurns[pokemonSlot] == 0) {
        return false;
    }
    --sMoveState.throatChopTurns[pokemonSlot];
    return sMoveState.throatChopTurns[pokemonSlot] == 0;
}

extern "C" void W2U_MoveState_ClearThroatChop(u32 pokemonSlot)
{
    if (IsValidSlot(pokemonSlot)) {
        sMoveState.throatChopTurns[pokemonSlot] = 0;
    }
}

extern "C" void W2U_MoveState_SetElectrified(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sElectrifiedFlags |= mask;
    }
}

extern "C" bool W2U_MoveState_IsElectrified(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    return mask && (sElectrifiedFlags & mask);
}

extern "C" bool W2U_MoveState_IsIonDelugeActive()
{
    return sIonDelugeActive;
}

extern "C" void W2U_MoveState_ClearElectrifiedSlot(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sElectrifiedFlags &= ~mask;
    }
}

extern "C" void W2U_MoveState_ClearElectrified()
{
    sElectrifiedFlags = 0;
}

extern "C" bool W2U_MoveState_StartBeakBlast(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (!mask || !W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
        return false;
    }

    sMoveState.beakBlastChargingFlags |= mask;
    return true;
}

extern "C" bool W2U_MoveState_IsBeakBlastCharging(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    return mask && (sMoveState.beakBlastChargingFlags & mask);
}

extern "C" void W2U_MoveState_ClearBeakBlast(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMoveState.beakBlastChargingFlags &= ~mask;
    }
}

extern "C" void W2U_MoveState_ClearAllBeakBlast()
{
    sMoveState.beakBlastChargingFlags = 0;
}

extern "C" bool W2U_MoveState_HasBeakBlastCharging()
{
    return sMoveState.beakBlastChargingFlags != 0;
}

extern "C" bool W2U_MoveState_StartShellTrap(u32 pokemonSlot)
{
    const u32 mask = SlotMask(pokemonSlot);
    if (!mask || !W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
        return false;
    }

    sMoveState.shellTrapArmedFlags |= mask;
    sMoveState.shellTrapTriggeredFlags &= ~mask;
    return true;
}

extern "C" bool W2U_MoveState_IsShellTrapWaiting(u32 pokemonSlot)
{
    const u32 mask = SlotMask(pokemonSlot);
    return mask &&
        (sMoveState.shellTrapArmedFlags & mask) &&
        !(sMoveState.shellTrapTriggeredFlags & mask);
}

extern "C" bool W2U_MoveState_IsShellTrapTriggered(u32 pokemonSlot)
{
    const u32 mask = SlotMask(pokemonSlot);
    return mask && (sMoveState.shellTrapTriggeredFlags & mask);
}

extern "C" bool W2U_MoveState_TriggerShellTrap(u32 pokemonSlot)
{
    if (!W2U_MoveState_IsShellTrapWaiting(pokemonSlot)) {
        return false;
    }
    sMoveState.shellTrapTriggeredFlags |= SlotMask(pokemonSlot);
    return true;
}

extern "C" void W2U_MoveState_ClearShellTrap(u32 pokemonSlot)
{
    const u32 mask = SlotMask(pokemonSlot);
    if (mask) {
        sMoveState.shellTrapArmedFlags &= ~mask;
        sMoveState.shellTrapTriggeredFlags &= ~mask;
    }
}

extern "C" void W2U_MoveState_ClearAllShellTraps()
{
    sMoveState.shellTrapArmedFlags = 0;
    sMoveState.shellTrapTriggeredFlags = 0;
}

extern "C" bool W2U_MoveState_HasShellTrap()
{
    return sMoveState.shellTrapArmedFlags != 0 ||
        sMoveState.shellTrapTriggeredFlags != 0;
}

extern "C" void W2U_MoveState_PrepareBeakBlastCharges(
    ServerFlow* serverFlow,
    u32 startActionIdx)
{
    if (!serverFlow || !serverFlow->serverCommandQueue) {
        return;
    }

    u32 actionCount = serverFlow->numActOrder;
    if (actionCount > W2U_ARRAY_COUNT(serverFlow->actionOrderWork)) {
        actionCount = W2U_ARRAY_COUNT(serverFlow->actionOrderWork);
    }

    for (u32 actionIdx = startActionIdx; actionIdx < actionCount; ++actionIdx) {
        ActionOrderWork* actionOrder = &serverFlow->actionOrderWork[actionIdx];
        BattleMon* battleMon = actionOrder->battleMon;
        if (actionOrder->done || !battleMon || BattleMon_IsFainted(battleMon) ||
            BattleAction_GetAction(&actionOrder->action) != 1 ||
            (MOVE_ID)actionOrder->action.baFight.moveID != MOVE_BEAK_BLAST) {
            continue;
        }

        const u32 pokemonSlot = BattleMon_GetID(battleMon);
        const u32 pokemonMask = SlotMask(pokemonSlot);
        if (!pokemonMask) {
            continue;
        }

        const bool cueAlreadyShown =
            (sBeakBlastChargeCueFlags & pokemonMask) != 0;

#if defined(W2U_DYNAMIC_BATTLE_CORE)
        // Match scproc_BeforeFirstFight's registration contract: do not show a
        // charge cue when the child module is unavailable or invalid.
        if (!W2U_BattleModules_Resolve(W2U_MECHANIC_MOVE, MOVE_BEAK_BLAST)) {
            continue;
        }
#elif defined(W2U_BATTLE_STATIC_GROUPS)
        if (!W2U_BattleStatic_Resolve(W2U_MECHANIC_MOVE, MOVE_BEAK_BLAST)) {
            continue;
        }
#endif

        // Keep the burn window armed if action-order processing revisits this
        // battler, but never replay the visible charge cue in the same turn.
        if (!W2U_MoveState_IsBeakBlastCharging(pokemonSlot) &&
            !W2U_MoveState_StartBeakBlast(pokemonSlot)) {
            continue;
        }

        if (cueAlreadyShown) {
            continue;
        }

        const u32 pokePos = Handler_PokeIDToPokePos(serverFlow, pokemonSlot);
        if (pokePos >= W2U_NULL_BATTLE_POS) {
            W2U_MoveState_ClearBeakBlast(pokemonSlot);
            continue;
        }

        sBeakBlastChargeCueFlags |= pokemonMask;

        // 0xFF is an internal one-command marker. The viewer hook translates
        // it to variant 0, while all ordinary Beak Blast commands use variant
        // 1. This prevents a default phase-0 command from replaying the charge
        // immediately before the actual attack.
        ServerDisplay_AddCommon(
            serverFlow->serverCommandQueue,
            SCID_MoveAnim,
            pokePos,
            pokePos,
            MOVE_BEAK_BLAST,
            0xFFu);
        ServerDisplay_AddMessageImpl(
            serverFlow->serverCommandQueue,
            SCID_SetMessage,
            BATTLE_BEAK_BLAST_CHARGE_MSGID,
            pokemonSlot,
            0xFFFF0000u);
    }
}

extern "C" void W2U_MoveState_PrepareShellTraps(
    ServerFlow* serverFlow,
    u32 startActionIdx)
{
    if (!serverFlow || !serverFlow->serverCommandQueue) {
        return;
    }

    u32 actionCount = serverFlow->numActOrder;
    if (actionCount > W2U_ARRAY_COUNT(serverFlow->actionOrderWork)) {
        actionCount = W2U_ARRAY_COUNT(serverFlow->actionOrderWork);
    }

    for (u32 actionIdx = startActionIdx; actionIdx < actionCount; ++actionIdx) {
        ActionOrderWork* actionOrder = &serverFlow->actionOrderWork[actionIdx];
        BattleMon* battleMon = actionOrder->battleMon;
        if (actionOrder->done || !battleMon || BattleMon_IsFainted(battleMon) ||
            BattleAction_GetAction(&actionOrder->action) != 1 ||
            (MOVE_ID)actionOrder->action.baFight.moveID != MOVE_SHELL_TRAP) {
            continue;
        }

        const u32 pokemonSlot = BattleMon_GetID(battleMon);
        if (!SlotMask(pokemonSlot) ||
            W2U_MoveState_IsShellTrapWaiting(pokemonSlot) ||
            W2U_MoveState_IsShellTrapTriggered(pokemonSlot)) {
            continue;
        }
#if defined(W2U_DYNAMIC_BATTLE_CORE)
        if (!W2U_BattleModules_Resolve(W2U_MECHANIC_MOVE, MOVE_SHELL_TRAP)) {
            continue;
        }
#elif defined(W2U_BATTLE_STATIC_GROUPS)
        if (!W2U_BattleStatic_Resolve(W2U_MECHANIC_MOVE, MOVE_SHELL_TRAP)) {
            continue;
        }
#endif
        if (!W2U_MoveState_StartShellTrap(pokemonSlot)) {
            continue;
        }

        const u32 pokePos = Handler_PokeIDToPokePos(serverFlow, pokemonSlot);
        if (pokePos >= W2U_NULL_BATTLE_POS) {
            W2U_MoveState_ClearShellTrap(pokemonSlot);
            continue;
        }

        // The viewer maps this internal marker to animation variant 0. The
        // ordinary move command maps to variant 1 only when the trap triggers.
        ServerDisplay_AddCommon(
            serverFlow->serverCommandQueue,
            SCID_MoveAnim,
            pokePos,
            pokePos,
            MOVE_SHELL_TRAP,
            0xFFu);

        ServerDisplay_AddMessageImpl(
            serverFlow->serverCommandQueue,
            SCID_SetMessage,
            BATTLE_SHELL_TRAP_SET_MSGID,
            pokemonSlot,
            0xFFFF0000u);
    }
}

extern "C" TERRAIN W2U_MoveState_GetTerrain()
{
    // Reset and removal both clear the type to TERRAIN_NULL. The type is
    // already the public active-terrain discriminator; no second flag read
    // is needed by the resident and child callers.
    return sTerrainType;
}

extern "C" bool W2U_MoveState_RemoveTerrain(ServerFlow* serverFlow)
{
    return RemoveTerrainState(serverFlow, true);
}

static bool SetTerrainFromAbilityCore(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    TERRAIN terrain,
    u32 msgID,
    MOVE_ID animationMoveID,
    bool messageNamesMon)
{
    BattleMon* battleMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!serverFlow || !serverFlow->serverCommandQueue || !battleMon ||
        !SetTerrainState(serverFlow, pokemonSlot, terrain)) {
        return false;
    }

    ServerDisplay_AbilityPopupAdd(serverFlow, battleMon);

#if defined(W2U_TARGET_B2)
    // Black 2 (no terrain fades yet): the terrain move's animation between the
    // popup and the message, as PW2Code's terrain field-effect handler does.
    u32 pokePos = Handler_PokeIDToPokePos(serverFlow, pokemonSlot);
    ServerDisplay_AddCommon(
        serverFlow->serverCommandQueue,
        SCID_MoveAnim,
        pokePos,
        pokePos,
        animationMoveID,
        0,
        0);
#else
    // An ability plays no move animation (the terrain moves keep theirs): the
    // terrain fades in as its start message appears.
    (void)animationMoveID;
    W2U_TerrainTexture_DeferStartUntilMessage(msgID);
#endif

    HandlerParam_StrParams terrainMessage = {};
    BattleHandler_StrSetup(&terrainMessage, 2u, (u16)msgID);
    if (messageNamesMon) {
        BattleHandler_AddArg(&terrainMessage, pokemonSlot);
    }
    BattleHandler_SetString(serverFlow, &terrainMessage);

    ServerDisplay_AbilityPopupRemove(serverFlow, battleMon);
    NotifyTerrainChanged(serverFlow, terrain);
    return true;
}

extern "C" bool W2U_MoveState_SetTerrainFromAbility(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    TERRAIN terrain,
    u32 msgID,
    MOVE_ID animationMoveID)
{
    return SetTerrainFromAbilityCore(serverFlow, pokemonSlot, terrain, msgID, animationMoveID, false);
}

// The same, with the setter as the message's argument (Hadron Engine: "X turned the ground into Electric Terrain...").
extern "C" bool W2U_MoveState_SetTerrainFromAbilityNamed(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    TERRAIN terrain,
    u32 msgID,
    MOVE_ID animationMoveID)
{
    return SetTerrainFromAbilityCore(serverFlow, pokemonSlot, terrain, msgID, animationMoveID, true);
}

extern "C" bool W2U_MoveState_RemoveStickyWebSide(u32 side)
{
    return RemoveStickyWebSide(0, BATTLE_MAX_SLOTS, side, false);
}

extern "C" bool W2U_MoveState_RemoveAuroraVeilSide(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32 side,
    bool showMessage)
{
    return RemoveAuroraVeilSide(serverFlow, pokemonSlot, side, showMessage);
}
#endif

static u32 ResolveRuntimeMoveCategory(MOVE_ID moveID, BattleMon* attackingMon)
{
    if (moveID == MOVE_SHELL_SIDE_ARM && attackingMon)
        return W2U_MoveState_ShellSideArmCategory(BattleMon_GetID(attackingMon));
    if (moveID == MOVE_PHOTON_GEYSER && attackingMon) {
        // These values include the stored stat stages but precede held-item
        // and ability event modifiers. Ties are special.
        u32 attack = BattleMon_GetValue(attackingMon, VALUE_ATTACK_STAT);
        u32 specialAttack = BattleMon_GetValue(attackingMon, VALUE_SPECIAL_ATTACK_STAT);
        const u32 category = attack > specialAttack ? SPLIT_PHYSICAL : SPLIT_SPECIAL;
#if !defined(W2U_BATTLE_CHILD)
        // Counter and Mirror Coat retain only the damaging move's ID. Keep the
        // category chosen for the attack so their later history lookup does
        // not fall back to Photon Geyser's database category.
        const u32 slotMask = SlotMask(BattleMon_GetID(attackingMon));
        if (slotMask) {
            sMoveState.photonGeyserCategoryValidFlags |= slotMask;
            if (category == SPLIT_PHYSICAL) {
                sMoveState.photonGeyserPhysicalFlags |= slotMask;
            } else {
                sMoveState.photonGeyserPhysicalFlags &= ~slotMask;
            }
        }
#endif
        return category;
    }
    return PML_MoveGetCategory(moveID);
}

#if !defined(W2U_DYNAMIC_BATTLE_CORE)
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

static void HandlerMortalSpin(BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    BattleMon* user = GetBattleMon(flow, slot);
    // Successful sequence notification follows contact/item reactions.
    if (!user || BattleMon_IsFainted(user) ||
        Handler_PokeIDToPokePos(flow, slot) >= W2U_NULL_BATTLE_POS) return;
    HandlerRapidSpin(item, flow, slot, work);
}

static BattleEventHandlerTableEntry MortalSpinHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerMortalSpin },
};

static void HandlerExpandingForceTarget(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        W2U_MoveState_GetTerrain() == TERRAIN_PSYCHIC && IsGrounded(flow, GetBattleMon(flow, slot)))
        BattleEventVar_RewriteValue(VAR_TARGET_TYPE, TARGET_ENEMY_ALL);
}

static void HandlerExpandingForcePower(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_GetTerrain() == TERRAIN_PSYCHIC && IsGrounded(flow, GetBattleMon(flow, slot)))
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 3 / 2);
}

static BattleEventHandlerTableEntry ExpandingForceHandlers[] = {
    { EVENT_W2U_MOVE_PARAM_FINAL, HandlerExpandingForceTarget },
    { EVENT_MOVE_BASE_POWER, HandlerExpandingForcePower },
};

static bool IsMoveRecipientHidden(BattleMon* mon)
{
    for (u32 flag = CONDITIONFLAG_FLY; flag <= CONDITIONFLAG_SHADOW_FORCE; ++flag)
        if (BattleMon_GetConditionFlag(mon, flag)) return true;
    return BattleMon_CheckIfMoveCondition(mon, CONDITION_SKYDROP);
}

static void HandlerDecorate(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    BattleMon* target = GetBattleMon(flow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    // Boosts use native target-stat data: retain Substitute/Contrary/caps.
    if (target && IsMoveRecipientHidden(target))
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
}

static BattleEventHandlerTableEntry DecorateHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerDecorate },
};

static void HandlerSnipeShotRedirection(BattleEventItem*, ServerFlow*, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON))
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
}

static BattleEventHandlerTableEntry SnipeShotHandlers[] = {
    { EVENT_W2U_REDIRECTION_CHECK, HandlerSnipeShotRedirection },
};

static void HandlerDragonDartsTargets(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    // Request an additional foe only after native redirection/dead-target
    // correction. Immunity, hiding, protection and accuracy remain native.
    if ((u32)BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_DRAGON_DARTS &&
        slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BtlSetup_GetBattleStyle(flow->mainModule) == BTL_STYLE_DOUBLE &&
        !BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG) &&
        !MainModule_IsAllyMonID(slot, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)))
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
}

static void HandlerDragonDartsPrankster(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    const u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if ((u32)BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_DRAGON_DARTS &&
        slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        !MainModule_IsAllyMonID(slot, target) &&
        HasTypeWithExtra(GetBattleMon(flow, target), TYPE_DARK) &&
        W2U_DragonDartsHasPranksterOrigin(flow, slot))
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
}

static BattleEventHandlerTableEntry DragonDartsHandlers[] = {
    { EVENT_W2U_TARGET_PARAM_FINAL, HandlerDragonDartsTargets },
    { EVENT_NOEFFECT_CHECK, HandlerDragonDartsPrankster },
};

static void HandlerDragonCheer(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    for (u32 index = 0; index < W2U_ARRAY_COUNT(flow->pokeCon->activeBattleMon); ++index) {
        BattleMon* mon = flow->pokeCon->activeBattleMon[index];
        if (!mon) continue;
        const u32 ally = BattleMon_GetID(mon);
        const u32 userPos = Handler_PokeIDToPokePos(flow, slot);
        const u32 allyPos = ally < BATTLE_MAX_SLOTS ? Handler_PokeIDToPokePos(flow, ally) : W2U_NULL_BATTLE_POS;
        if (ally == slot || ally >= BATTLE_MAX_SLOTS || !MainModule_IsAllyMonID(slot, ally) ||
            allyPos >= W2U_NULL_BATTLE_POS ||
            // Native positions interleave the two sides (0,2,4 / 1,3,5).
            // Only same-side opposite corners are nonadjacent in triples.
            (allyPos > userPos ? allyPos - userPos : userPos - allyPos) > 2 ||
            BattleMon_IsFainted(mon) || IsMoveRecipientHidden(mon)) continue;
        if (W2U_MoveState_ApplyDragonCheer(flow, ally)) {
            PushMessageArg(flow, slot, 2u, 1041u, ally);
            BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
        }
    }
}

static BattleEventHandlerTableEntry DragonCheerHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerDragonCheer },
};

static void HandlerAllyHealing(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    const MOVE_ID move = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    for (u32 index = 0; index < W2U_ARRAY_COUNT(flow->pokeCon->activeBattleMon); ++index) {
        BattleMon* mon = flow->pokeCon->activeBattleMon[index];
        if (!mon) continue;
        const u32 recipient = BattleMon_GetID(mon);
        if (recipient >= BATTLE_MAX_SLOTS) continue;
        if (Handler_PokeIDToPokePos(flow, recipient) >= W2U_NULL_BATTLE_POS ||
            BattleMon_IsFainted(mon) || !MainModule_IsAllyMonID(slot, recipient) ||
            IsMoveRecipientHidden(mon)) continue;
        if (move == MOVE_LIFE_DEW && recipient != slot) {
            // Native Water immunity/absorption, in its own complete scope.
            // Storm Drain boosts rather than heals; Water Absorb/Dry Skin
            // perform their own quarter recovery, never an additional one.
            HandlerParam_StrParams message = {};
            BattleEventVar_Push();
            BattleEventVar_SetConstValue(VAR_ATTACKING_MON, slot);
            BattleEventVar_SetConstValue(VAR_DEFENDING_MON, recipient);
            BattleEventVar_SetConstValue(VAR_MOVE_ID, move);
            BattleEventVar_SetConstValue(VAR_MOVE_TYPE, TYPE_WATER);
            BattleEventVar_SetConstValue(VAR_MAGIC_COAT_FLAG, 0);
            BattleEventVar_SetConstValue(VAR_WORK_ADDRESS, (int)&message);
            BattleEventVar_SetConstValue(VAR_TYPE_EFFECTIVENESS, 3);
            BattleEventVar_SetRewriteOnceValue(VAR_NO_EFFECT_FLAG, 0);
            BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);
            BattleEvent_CallHandlers(flow, EVENT_ABILITY_CHECK_NO_EFFECT);
            const bool immune = BattleEventVar_GetValue(VAR_NO_EFFECT_FLAG);
            BattleEventVar_Pop();
            if (immune) continue;
        }
        const CONDITION status = (CONDITION)BattleMon_GetStatus(mon);
        if (move != MOVE_LIFE_DEW && status != CONDITION_NONE)
            CureMoveCondition(flow, recipient, status);
        if (BattleMon_GetValue(mon, VALUE_CURRENT_HP) < BattleMon_GetValue(mon, VALUE_MAX_HP)) {
            HandlerParam_RecoverHP* heal = (HandlerParam_RecoverHP*)
                BattleHandler_PushWork(flow, EFFECT_RECOVER_HP, slot);
            heal->recoverHP = (u16)DivideMaxHPZeroCheck(mon, 4);
            heal->pokeID = (u8)recipient;
            heal->failCheckThru = false;
            BattleHandler_StrSetup(&heal->exStr, 2u, 387u);
            BattleHandler_AddArg(&heal->exStr, recipient);
            BattleHandler_PopWork(flow, heal);
        }
    }
}

static BattleEventHandlerTableEntry AllyHealingHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerAllyHealing },
};

static void HandlerMakeItRainCoins(BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) || flow->simulationCounter) return;
    ++work[0];
    // Pay Day owns native limits and payout bookkeeping (including items).
    W2UNativeMoveGetter getter = W2U_FindNativeMoveGetter(MOVE_PAY_DAY);
    if (!getter) return;
    u32 count = 0;
    BattleEventHandlerTableEntry* table = getter(&count);
    for (u32 i = 0; table && i < count; ++i)
        if (table[i].eventType == EVENT_DETERMINE_MOVE_DAMAGE)
            table[i].handler(item, flow, slot, work);
}

static void HandlerMakeItRainReset(BattleEventItem*, ServerFlow*, u32 slot, u32* work)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_MON_ID)) work[0] = 0;
}

static void HandlerMakeItRainDrop(BattleEventItem*, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) || !work[0] || flow->simulationCounter) return;
    work[0] = 0;
    ApplyStatChange(flow, slot, slot, STATSTAGE_SPECIAL_ATTACK, -1, false);
}

static BattleEventHandlerTableEntry MakeItRainHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerMakeItRainReset },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerMakeItRainCoins },
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerMakeItRainDrop },
};

static void HandlerMatchaReset(BattleEventItem*, ServerFlow*, u32 slot, u32* work)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_MON_ID))
        for (u32 i = 0; i < 7; ++i) work[i] = 0;
}

static void HandlerMatchaRecord(BattleEventItem*, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) || flow->simulationCounter ||
        work[0] >= 6) return;
    const u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    const u32 damage = (u32)BattleEventVar_GetValue(VAR_DAMAGE);
    BattleMon* mon = GetBattleMon(flow, target);
    if (!mon || !damage) return;
    // Seven native work words: count and six packed (amount, target, Ooze)
    // records. Record actual damage, including Substitute and HP clipping.
    const u32 amount = damage / 2 ? damage / 2 : 1;
    const u32 ooze = BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY) == ABIL_LIQUID_OOZE;
    work[++work[0]] = amount | (target << 16) | (ooze << 24);
}

static void HandlerMatchaDrain(BattleEventItem*, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) || flow->simulationCounter) return;
    BattleMon* user = GetBattleMon(flow, slot);
    if (!user || BattleMon_IsFainted(user)) { work[0] = 0; return; }
    // Process every reversal before any recovery. Native drain work applies
    // Big Root, Liquid Ooze, Heal Block and the no-revival check itself.
    for (u32 phase = 1; ; --phase) {
        for (u32 i = 1; i <= work[0] && i <= 6; ++i) {
            const u32 record = work[i];
            if ((record >> 24) != phase) continue;
            HandlerParam_Drain* drain = (HandlerParam_Drain*)
                BattleHandler_PushWork(flow, EFFECT_DRAIN, slot);
            drain->recoverHP = (u16)record;
            drain->recipientSlot = (u8)slot;
            drain->damageSourceSlot = (u8)(record >> 16);
            BattleHandler_StrSetup(&drain->exStr, 2u, 387u);
            BattleHandler_AddArg(&drain->exStr, slot);
            BattleHandler_PopWork(flow, drain);
        }
        if (!phase) break;
    }
    work[0] = 0;
}

static BattleEventHandlerTableEntry MatchaGotchaHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerMatchaReset },
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerMatchaRecord },
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerMatchaDrain },
};

static void HandlerRageFistPower(BattleEventItem*, ServerFlow*, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON))
        BattleEventVar_RewriteValue(VAR_MOVE_POWER, W2U_MoveState_RageFistPower(slot));
}

static BattleEventHandlerTableEntry RageFistHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerRageFistPower },
};

static void HandlerLastRespectsCheck(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        !W2U_MoveState_LastRespectsPower(flow, slot))
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
}

static void HandlerLastRespectsPower(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    const u32 power = W2U_MoveState_LastRespectsPower(flow, slot);
    if (power) BattleEventVar_RewriteValue(VAR_MOVE_POWER, power);
}

static BattleEventHandlerTableEntry LastRespectsHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerLastRespectsCheck },
    { EVENT_MOVE_BASE_POWER, HandlerLastRespectsPower },
};

static void HandlerRevivalBlessingCheck(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        !W2U_Revival_CanUse(flow, slot))
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
}

static void HandlerRevivalBlessing(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    BattleMon* user = GetBattleMon(flow, slot);
    if (user && !BattleMon_CheckIfMoveCondition(user, CONDITION_HEALBLOCK))
        W2U_Revival_Begin(flow, slot);
}

static BattleEventHandlerTableEntry RevivalBlessingHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerRevivalBlessingCheck },
    { EVENT_UNCATEGORIZED_MOVE, HandlerRevivalBlessing },
};

static void HandlerCourtChange(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_CourtChange(flow))
        BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
}

static BattleEventHandlerTableEntry CourtChangeHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerCourtChange },
};

static void HandlerSnowscape(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_Weather_QueueSnow(flow, slot))
        BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
}

static BattleEventHandlerTableEntry SnowscapeHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerSnowscape },
};

static void HandlerChillyReception(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (!flow || flow->simulationCounter ||
        slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    bool success = W2U_Weather_QueueSnow(flow, slot);
    // Pivot even if snow is already active (or weather cannot be replaced).
    // Native switching owns recipient selection, Pursuit and entry hazards.
    if (Handler_GetFightEnableBenchPokeNum(flow, slot) &&
        Handler_CheckReservedMemberChangeAction(flow)) {
        HandlerParam_Switch* pivot = (HandlerParam_Switch*)
            BattleHandler_PushWork(flow, EFFECT_SWITCH, slot);
        if (pivot) {
            pivot->pokeID = (u8)slot;
            pivot->intrDisable = false;
            BattleHandler_StrClear(&pivot->preStr);
            BattleHandler_StrClear(&pivot->exStr);
            BattleHandler_PopWork(flow, pivot);
            success = true;
        }
    }
    if (success) BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
}

static BattleEventHandlerTableEntry ChillyReceptionHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerChillyReception },
};

static void HandlerTidyUp(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)work;
    if (!flow || flow->simulationCounter ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) return;
    BattleMon* user = GetBattleMon(flow, pokemonSlot);
    if (!user || BattleMon_IsFainted(user)) return;
    bool cleaned = false;
    for (u32 slot = 0; slot < W2U_ARRAY_COUNT(flow->pokeCon->activeBattleMon); ++slot) {
        BattleMon* mon = GetBattleMon(flow, slot);
        if (mon && !BattleMon_IsFainted(mon) &&
            Handler_PokeIDToPokePos(flow, slot) < W2U_NULL_BATTLE_POS &&
            BattleMon_IsSubstituteActive(mon)) {
            BattleMon_RemoveSubstitute(mon);
            cleaned = true;
        }
    }
    const SIDE_EFFECT hazards[] = {
        SIDEEFF_SPIKES, SIDEEFF_TOXIC_SPIKES, SIDEEFF_STEALTH_ROCK, SIDEEFF_STICKY_WEB
    };
    for (u32 side = 0; side < W2U_SIDE_COUNT; ++side) {
        bool active = false;
        for (u32 index = 0; index < W2U_ARRAY_COUNT(hazards); ++index)
            if (SideEffectEvent_IsActive(side, hazards[index])) active = true;
        if (active) {
            RemoveSideEffects(flow, pokemonSlot, side, hazards, W2U_ARRAY_COUNT(hazards));
            cleaned = true;
        }
        if (RemoveStickyWebSide(flow, pokemonSlot, side, true)) cleaned = true;
    }
    const s8 direction = BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == 126u ? -1 : 1;
    if (BattleMon_IsStatChangeValid(user, STATSTAGE_ATTACK, direction) ||
        BattleMon_IsStatChangeValid(user, STATSTAGE_SPEED, direction)) {
        ApplyStatChange(flow, pokemonSlot, pokemonSlot, STATSTAGE_ATTACK, 1, true);
        ApplyStatChange(flow, pokemonSlot, pokemonSlot, STATSTAGE_SPEED, 1, true);
    }
    if (cleaned) BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, pokemonSlot);
}

static BattleEventHandlerTableEntry TidyUpHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerTidyUp },
};

static void HandlerDamagingHazard(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_DAMAGE) <= 0) {
        return;
    }
    BattleMon* user = GetBattleMon(serverFlow, pokemonSlot);
    if (!user || BattleMon_IsFainted(user) ||
        BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE) {
        return;
    }
    const bool spikes = BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_CEASELESS_EDGE;
    const u32 side = GetSideFromOpposingMonID(pokemonSlot);
    if (side >= W2U_SIDE_COUNT) return;

    // Port PW2Code's native side-effect work rather than its loader/animation
    // hook. This per-hit event includes Substitute and runs after retaliation:
    // two Parental Bond hits add two Spikes layers, a fainted user adds none.
    // Native side registration enforces three layers / one Stealth Rock and
    // emits the announcement only when an additional layer is accepted.
    HandlerParam_AddSideEffect* effect = (HandlerParam_AddSideEffect*)
        BattleHandler_PushWork(serverFlow, EFFECT_ADD_SIDE_EFFECT, pokemonSlot);
    effect->sideEffect = spikes ? SIDEEFF_SPIKES : SIDEEFF_STEALTH_ROCK;
    effect->side = (u8)side;
    // Native permanent condition: continuation kind 1, all other bits zero.
    // Avoid a new game-address import for this constant constructor.
    effect->condData = 1u;
    BattleHandler_StrSetup(&effect->exStr, 1u, spikes ? 148u : 152u);
    BattleHandler_AddArg(&effect->exStr, side);
    BattleHandler_PopWork(serverFlow, effect);
}

static BattleEventHandlerTableEntry DamagingHazardHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerDamagingHazard },
};


static bool QueueSourceTrap(ServerFlow* flow, u32 source, u32 target)
{
    BattleMon* mon = GetBattleMon(flow, target);
    if (!mon || BattleMon_IsFainted(mon) || HasTypeWithExtra(mon, TYPE_GHOST)) return false;
    if (BattleMon_CheckIfMoveCondition(mon, CONDITION_ESCAPE_PREVENTION)) return false;
    HandlerParam_AddCondition* effect = (HandlerParam_AddCondition*)
        BattleHandler_PushWork(flow, EFFECT_ADD_CONDITION, source);
    if (!effect) return false;
    effect->condition = CONDITION_ESCAPE_PREVENTION;
    // Native Spider Web: poke-dependent kind 3, source in bits 3-8.
    effect->condData = 3u | (source << 3);
    effect->pokeID = (u8)target;
    effect->almost = 0;
    BattleHandler_StrSetup(&effect->exStr, 2, 872);
    BattleHandler_AddArg(&effect->exStr, target);
    BattleHandler_PopWork(flow, effect);
    return true;
}

extern "C" void HandlerAnchorShot(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) {
        return;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, pokemonSlot);
    if (attackingMon &&
        BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE) {
        return;
    }

    (void)item;
    (void)work;
    // The direct-hit notification owns the real recipient list. The later
    // side-effect phase does not retain Spider Web's single-target context.
    // Use the shared native condition encoding, preserving source departure
    // cleanup and all native switch-item / forced-switch bypasses.
    const u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        const u32 target = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        if (target != pokemonSlot) QueueSourceTrap(serverFlow, pokemonSlot, target);
    }
}

BattleEventHandlerTableEntry AnchorShotHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerAnchorShot },
};

static void HandlerNoRetreat(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT) || flow->simulationCounter ||
        W2U_MoveState_HasNoRetreat(slot)) return;
    BattleMon* user = GetBattleMon(flow, slot);
    if (!user) return;
    const bool alreadyTrapped = BattleMon_CheckIfMoveCondition(user, CONDITION_ESCAPE_PREVENTION);
    if (!alreadyTrapped) {
        if (!W2U_MoveState_TryNoRetreat(slot)) return;
        QueueSourceTrap(flow, slot, slot);
        BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
    }
    for (u32 stat = STATSTAGE_ATTACK; stat <= STATSTAGE_SPEED; ++stat)
        ApplyStatChange(flow, slot, slot, (StatStage)stat, 1, true);
}

static BattleEventHandlerTableEntry NoRetreatHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerNoRetreat },
};

static bool HasNativeTrap(BattleMon* mon)
{
    return BattleMon_CheckIfMoveCondition(mon, CONDITION_ESCAPE_PREVENTION) ||
        BattleMon_CheckIfMoveCondition(mon, CONDITION_BIND) ||
        BattleMon_CheckIfMoveCondition(mon, (CONDITION)20); // Ingrain.
}

static void HandlerJawLock(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        flow->simulationCounter || BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) return;
    const u32 target = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* user = GetBattleMon(flow, slot);
    BattleMon* foe = GetBattleMon(flow, target);
    if (!user || !foe || BattleMon_IsFainted(user) || BattleMon_IsFainted(foe) ||
        HasNativeTrap(user) || HasNativeTrap(foe)) return;
    QueueSourceTrap(flow, slot, target);
    QueueSourceTrap(flow, target, slot);
}

static BattleEventHandlerTableEntry JawLockHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerJawLock },
};

static void HandlerOctolock(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT) || flow->simulationCounter) return;
    const u32 target = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* mon = GetBattleMon(flow, target);
    if (!mon || BattleMon_IsFainted(mon) || HasTypeWithExtra(mon, TYPE_GHOST) ||
        !W2U_MoveState_EnsureAuxEvent(13, slot) ||
        !W2U_MoveState_StartPersistentEffect(MOVE_OCTOLOCK, slot, target)) return;
    QueueSourceTrap(flow, slot, target);
    BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
}

static void HandlerOctolockResidual(BattleEventItem*, ServerFlow* flow, u32, u32*)
{
    const u32 target = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if (flow->simulationCounter || !W2U_MoveState_HasPersistentEffect(MOVE_OCTOLOCK, target)) return;
    BattleMon* mon = GetBattleMon(flow, target);
    const u32 source = W2U_MoveState_PersistentSource(MOVE_OCTOLOCK, target);
    BattleMon* user = GetBattleMon(flow, source);
    if (!mon || !user || BattleMon_IsFainted(mon) || BattleMon_IsFainted(user) ||
        Handler_PokeIDToPokePos(flow, source) >= W2U_NULL_BATTLE_POS) return;
    ApplyStatChange(flow, source, target, STATSTAGE_DEFENSE, -1, false);
    ApplyStatChange(flow, source, target, STATSTAGE_SPECIAL_DEFENSE, -1, false);
}

static BattleEventHandlerTableEntry OctolockHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerOctolock },
};
static BattleEventHandlerTableEntry FieldOctolockResidualHandlers[] = {
    { EVENT_TURN_CHECK_END, HandlerOctolockResidual },
};

static void HandlerPersistentSecondary(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) || flow->simulationCounter ||
        BattleEventVar_GetValue(VAR_DAMAGE) <= 0 || BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) return;
    BattleMon* user = GetBattleMon(flow, slot);
    const u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* mon = GetBattleMon(flow, target);
    if (!user || !mon || BattleMon_IsFainted(mon) ||
        BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE) return;
    const MOVE_ID move = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (W2U_MoveState_EnsureAuxEvent(14, slot))
        W2U_MoveState_StartPersistentEffect(move, slot, target);
}

static void HandlerPersistentResidual(BattleEventItem*, ServerFlow* flow, u32, u32*)
{
    const u32 target = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    BattleMon* mon = GetBattleMon(flow, target);
    if (!mon || BattleMon_IsFainted(mon) || flow->simulationCounter ||
        Handler_PokeIDToPokePos(flow, target) >= W2U_NULL_BATTLE_POS) return;
    if (W2U_MoveState_HasPersistentEffect(MOVE_SALT_CURE, target)) {
        HandlerParam_Damage* damage = (HandlerParam_Damage*)
            BattleHandler_PushWork(flow, EFFECT_DAMAGE, target);
        if (damage) {
            const u32 divisor = HasTypeWithExtra(mon, TYPE_WATER) ||
                HasTypeWithExtra(mon, TYPE_STEEL) ? 4 : 8;
            damage->damage = (u16)DivideMaxHPZeroCheck(mon, divisor);
            damage->pokeID = (u8)target;
            BattleHandler_PopWork(flow, damage);
        }
    }
    if (W2U_MoveState_HasPersistentEffect(MOVE_SYRUP_BOMB, target)) {
        const u32 source = W2U_MoveState_PersistentSource(MOVE_SYRUP_BOMB, target);
        BattleMon* user = GetBattleMon(flow, source);
        if (user && !BattleMon_IsFainted(user) &&
            Handler_PokeIDToPokePos(flow, source) < W2U_NULL_BATTLE_POS)
            ApplyStatChange(flow, source, target, STATSTAGE_SPEED, -1, false);
        W2U_MoveState_TickPersistentEffect(MOVE_SYRUP_BOMB, target);
    }
}

static BattleEventHandlerTableEntry PersistentSecondaryHandlers[] = {
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerPersistentSecondary },
};

static void HandlerGlaiveRush(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    // Clean W2/B2 side-after dispatch publishes attacker (3), not mon (2).
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) && !flow->simulationCounter)
        W2U_MoveState_StartGlaiveRush(slot);
}

static BattleEventHandlerTableEntry GlaiveRushHandlers[] = {
    // The native successful-sequence callback includes Substitute hits, and
    // runs before slower attacks in the same turn. No secondary suppression.
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerGlaiveRush },
};
static BattleEventHandlerTableEntry FieldPersistentResidualHandlers[] = {
    { EVENT_TURN_CHECK_END, HandlerPersistentResidual },
};


extern "C" void HandlerSappySeedConditionParam(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_CONDITION_ID) != CONDITION_LEECHSEED) {
        return;
    }

    const u32 sourcePos = Handler_PokeIDToPokePos(serverFlow, pokemonSlot);
    if (sourcePos == W2U_NULL_BATTLE_POS) {
        return;
    }

    // This is BPP_SICKCONT_MakePermanentParam(sourcePos), matching native
    // Leech Seed: continuation type 1 occupies bits 0-2 and its 16-bit
    // parameter begins at bit 9. The position identifies who receives drain.
    const ConditionData leechSeedData = 1u | ((sourcePos & 0xFFFFu) << 9);
    BattleEventVar_RewriteValue(VAR_CONDITION_DATA, leechSeedData);
}

BattleEventHandlerTableEntry SappySeedHandlers[] = {
    { EVENT_MOVE_CONDITION_PARAM, HandlerSappySeedConditionParam },
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
    W2U_MoveState_RemoveAuroraVeilSide(serverFlow, pokemonSlot, enemySide, true);
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

static void HandlerMinimizeDamage(BattleEventItem*, ServerFlow*, u32, u32*);
static void HandlerMinimizeAccuracy(BattleEventItem*, ServerFlow*, u32, u32*);

BattleEventHandlerTableEntry FlyingPressHandlers[] = {
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerFlyingPress },
    { EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerMinimizeDamage },
    { EVENT_SKIP_TARGET_ACCURACY_CHECK, HandlerMinimizeAccuracy },
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
    if (side >= W2U_SIDE_COUNT || !W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
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
    const bool needsGrounding = BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_FLOWER_SHIELD;
    if (!defendingMon || !HasTypeWithExtra(defendingMon, TYPE_GRASS) || (needsGrounding && !IsGrounded(serverFlow, defendingMon))) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry RototillerHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerRototiller },
};

// Never boost the user or foe if a called move or invalid target reaches the
// ordinary effect pipeline. Protection/substitute eligibility stays in data.
static void HandlerCoaching(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    u32 attacker = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (pokemonSlot != attacker) return;
    u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if (target == attacker || !MainModule_IsAllyMonID(attacker, target) ||
        !GetBattleMon(serverFlow, target)) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

static void HandlerCoachingApply(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT)) return;
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* target = GetBattleMon(flow, targetSlot);
    if (!target || BattleMon_IsFainted(target) || targetSlot == slot ||
        !MainModule_IsAllyMonID(slot, targetSlot)) return;
    // MUST_HIT status moves are not excluded by native accuracy's hiding
    // checks. Coaching explicitly cannot reach a semi-invulnerable partner.
    for (u32 flag = CONDITIONFLAG_FLY; flag <= CONDITIONFLAG_SHADOW_FORCE; ++flag) {
        if (BattleMon_GetConditionFlag(target, flag)) return;
    }
    if (BattleMon_CheckIfMoveCondition(target, CONDITION_SKYDROP)) return;
    const s8 direction = BattleMon_GetValue(target, VALUE_EFFECTIVE_ABILITY) == 126u ? -1 : 1; // Native Contrary.
    if (!BattleMon_IsStatChangeValid(target, STATSTAGE_ATTACK, direction) &&
        !BattleMon_IsStatChangeValid(target, STATSTAGE_DEFENSE, direction)) return;
    // Native direct target-stat effects reject Substitute a second time even
    // when bit 13 allowed the target. Attribute the cooperative boosts to the
    // recipient, like self-boost work: bypass that check without removing the
    // doll or overwriting stages. Native work still owns caps, Simple, Contrary,
    // messages and aggregate move success. No resident hook is necessary.
    ApplyStatChange(flow, targetSlot, targetSlot, STATSTAGE_ATTACK, 1, false);
    ApplyStatChange(flow, targetSlot, targetSlot, STATSTAGE_DEFENSE, 1, false);
}

static BattleEventHandlerTableEntry CoachingHandlers[] = {
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerCoaching },
    { EVENT_UNCATEGORIZED_MOVE, HandlerCoachingApply },
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
    if (side >= W2U_SIDE_COUNT || sStickyWebActive(side)) {
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

    sStickyWebItem(side) = sideItem;
    sStickyWebActive(side) = true;
    PushMessage(serverFlow, pokemonSlot, 1u, BATTLE_STICKY_WEB_USE_MSGID + side);
}

BattleEventHandlerTableEntry StickyWebHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE_NO_TARGET, HandlerStickyWeb },
};


extern "C" void HandlerBaddyBad(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    // Baddy Bad applies the ordinary Reflect side effect after a successful
    // damaging hit. Reuse Reflect's native handler so duration, Light Clay,
    // side-effect messages, removal, and non-stacking behavior stay native.
    u32 handlerCount = 0;
    BattleEventHandlerTableEntry* handlers = EventAddReflect(&handlerCount);
    for (u32 idx = 0; handlers && idx < handlerCount; ++idx) {
        if (handlers[idx].eventType == EVENT_UNCATEGORIZED_MOVE_NO_TARGET &&
            handlers[idx].handler) {
            handlers[idx].handler(item, serverFlow, pokemonSlot, work);
            return;
        }
    }
}

BattleEventHandlerTableEntry BaddyBadHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerBaddyBad },
};


extern "C" void HandlerGlitzyGlow(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    // Glitzy Glow applies the ordinary Light Screen side effect after a
    // successful damaging hit. Reusing the native handler preserves duration,
    // Light Clay, messages, removal, and non-stacking behavior.
    u32 handlerCount = 0;
    BattleEventHandlerTableEntry* handlers = EventAddLightScreen(&handlerCount);
    for (u32 idx = 0; handlers && idx < handlerCount; ++idx) {
        if (handlers[idx].eventType == EVENT_UNCATEGORIZED_MOVE_NO_TARGET &&
            handlers[idx].handler) {
            handlers[idx].handler(item, serverFlow, pokemonSlot, work);
            return;
        }
    }
}

BattleEventHandlerTableEntry GlitzyGlowHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerGlitzyGlow },
};


extern "C" void HandlerSideAuroraVeilGuard(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 side,
    u32* work)
{
    (void)item;
    (void)work;
    if (side >= W2U_SIDE_COUNT || !sAuroraVeilActive(side)) {
        return;
    }
    // The native Brick Break skip callback knows only Reflect/Light Screen.
    // These attacks also ignore Veil during calculation, before queued removal.
    const MOVE_ID move = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (move == MOVE_BRICK_BREAK || move == MOVE_RAGING_BULL) return;

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (attackingMon &&
        BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_INFILTRATOR) {
        return;
    }

    u32 moveCategory = (u32)BattleEventVar_GetValue(VAR_MOVE_CATEGORY);
    u32 screenKind = 0;
    SIDE_EFFECT nativeScreen = SIDEEFF_REFLECT;
    if (moveCategory == SPLIT_PHYSICAL) {
        screenKind = 1;
    } else if (moveCategory == SPLIT_SPECIAL) {
        screenKind = 2;
        nativeScreen = SIDEEFF_LIGHT_SCREEN;
    } else {
        return;
    }

    // Aurora Veil may coexist with the ordinary screens, but their damage
    // reductions do not stack. Let the native event supply the reduction when
    // the matching screen is already active; otherwise reuse its common math.
    if (!SideEffectEvent_IsActive(side, nativeScreen)) {
        CommonScreenEffect(serverFlow, side, screenKind);
    }
}

extern "C" void HandlerSideAuroraVeilTurnCheckDone(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 side,
    u32* work)
{
    (void)item;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MON_ID) != BATTLE_MAX_SLOTS ||
        side >= W2U_SIDE_COUNT ||
        !sAuroraVeilActive(side)) {
        return;
    }

    if (sAuroraVeilTurns(side) > 0) {
        --sAuroraVeilTurns(side);
    }
    if (sAuroraVeilTurns(side) == 0) {
        W2U_MoveState_RemoveAuroraVeilSide(serverFlow, BATTLE_MAX_SLOTS, side, true);
    }
}

BattleEventHandlerTableEntry SideAuroraVeilHandlers[] = {
    // CommonScreenEffect multiplies the final damage ratio. Calling it during
    // defense-stat calculation instead lowers Defense and increases damage.
    { EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerSideAuroraVeilGuard },
    { EVENT_TURN_CHECK_DONE, HandlerSideAuroraVeilTurnCheckDone },
};

extern "C" void HandlerAuroraVeilCheckFail(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    u32 side = GetSideFromMonID(pokemonSlot);
    if (ServerEvent_GetWeather(serverFlow) != WEATHER_HAIL ||
        side >= W2U_SIDE_COUNT ||
        sAuroraVeilActive(side)) {
        u32 failed = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        if (work) {
            work[0] = failed;
        }
    }
}

extern "C" void HandlerAuroraVeil(
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

    u32 side = GetSideFromMonID(pokemonSlot);
    if (ServerEvent_GetWeather(serverFlow) != WEATHER_HAIL ||
        side >= W2U_SIDE_COUNT || sAuroraVeilActive(side)) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    BattleEventItem* sideItem = BattleEvent_AddItem(
        EVENTITEM_SIDE,
        SIDEEFF_AURORA_VEIL,
        EVENTPRI_SIDE_DEFAULT,
        0,
        side,
        SideAuroraVeilHandlers,
        (u16)W2U_ARRAY_COUNT(SideAuroraVeilHandlers));
    if (!sideItem) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, pokemonSlot);
    sAuroraVeilItem(side) = sideItem;
    sAuroraVeilTurns(side) =
        currentMon &&
            BattleMon_GetHeldItem(currentMon) == ITEM_LIGHT_CLAY &&
            W2U_BattleMonCanUseHeldItem(currentMon)
        ? 8
        : 5;
    sAuroraVeilActive(side) = true;
    PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_AURORA_VEIL_START_MSGID);
}

BattleEventHandlerTableEntry AuroraVeilHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerAuroraVeilCheckFail },
    { EVENT_UNCATEGORIZED_MOVE_NO_TARGET, HandlerAuroraVeil },
};

extern "C" void HandlerBrickBreakAuroraVeil(
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

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if (defendingSlot < BATTLE_MAX_SLOTS) {
        W2U_MoveState_RemoveAuroraVeilSide(
            serverFlow,
            pokemonSlot,
            GetSideFromMonID(defendingSlot),
            true);
    }
}

BattleEventHandlerTableEntry BrickBreakAuroraVeilHandlers[] = {
    { EVENT_MOVE_DAMAGE_PROCESSING_1, HandlerBrickBreakStart },
    { EVENT_MOVE_DAMAGE_PROCESSING_END, HandlerBrickBreakEnd },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerBrickBreakCheck },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerBrickBreakAuroraVeil },
};

static void HandlerRagingBullType(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_MON_ID) ||
        BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_RAGING_BULL) return;
    BattleMon* user = GetBattleMon(flow, slot);
    if (!user) return;
    const u32 species = user->flags & 0x20 ? user->transformedSpecies : user->species;
    u32 type = TYPE_NORMAL;
    if (species == SPECIES_TAUROS) {
        switch (user->form) {
        case 1: type = TYPE_FIGHTING; break;
        case 2: type = TYPE_FIRE; break;
        case 3: type = TYPE_WATER; break;
        }
    }
    BattleEventVar_RewriteValue(VAR_MOVE_TYPE, type);
}

static BattleEventHandlerTableEntry RagingBullHandlers[] = {
    { EVENT_W2U_MOVE_PARAM_BASE, HandlerRagingBullType },
    { EVENT_MOVE_DAMAGE_PROCESSING_1, HandlerBrickBreakStart },
    { EVENT_MOVE_DAMAGE_PROCESSING_END, HandlerBrickBreakEnd },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerBrickBreakCheck },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerBrickBreakAuroraVeil },
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

static void HandlerTakeHeart(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!serverFlow || serverFlow->simulationCounter ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }
    BattleMon* user = GetBattleMon(serverFlow, pokemonSlot);
    if (!user || BattleMon_IsFainted(user)) {
        return;
    }

    // Native work owns Simple/Contrary and the individual messages. Do not
    // enqueue a wholly ineffective pair, which otherwise reports success.
    // Snatch registers this move on the actual executing user before this event.
    const s8 direction = BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == 126u ? -1 : 1;
    if (BattleMon_IsStatChangeValid(user, STATSTAGE_SPECIAL_ATTACK, direction) ||
        BattleMon_IsStatChangeValid(user, STATSTAGE_SPECIAL_DEFENSE, direction)) {
        ApplyStatChange(serverFlow, pokemonSlot, pokemonSlot, STATSTAGE_SPECIAL_ATTACK, 1, true);
        ApplyStatChange(serverFlow, pokemonSlot, pokemonSlot, STATSTAGE_SPECIAL_DEFENSE, 1, true);
    }
    const CONDITION status = BattleMon_GetStatus(user);
    if (IsPurifiableStatus(status)) {
        CureMoveCondition(serverFlow, pokemonSlot, status);
    }
}

static BattleEventHandlerTableEntry TakeHeartHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerTakeHeart },
};

static u32 HpCostBoostPayment(u32 maximum, bool soul)
{
    if (!soul) return maximum > 1 ? maximum / 2 : 1;
    // Maximum HP is a native u16. Bounded division avoids adding a compiler
    // runtime import to the static B2 build; the full u16 range is host-tested.
    u32 scaled = maximum * 33, cost = 0;
    for (u32 bit = 1u << 14; bit; bit >>= 1) {
        const u32 portion = bit * 100;
        if (scaled >= portion) {
            scaled -= portion;
            cost |= bit;
        }
    }
    return cost ? cost : 1;
}

static void HandlerHpCostBoost(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) return;
    BattleMon* user = GetBattleMon(serverFlow, pokemonSlot);
    if (!user || BattleMon_IsFainted(user)) return;
    const u32 move = BattleEventVar_GetValue(VAR_MOVE_ID);
    if (move != MOVE_CLANGOROUS_SOUL && move != MOVE_FILLET_AWAY) return;
    const bool soul = move == MOVE_CLANGOROUS_SOUL;
    const u32 maximum = BattleMon_GetValue(user, VALUE_MAX_HP);
    // Soul's conventional turn-based payment is 33%, not integer maxHP/3.
    const u32 cost = HpCostBoostPayment(maximum, soul);
    const s8 boost = soul ? 1 : 2;
    const int direction = BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == 126 ? -boost : boost;
    bool canChange = false;
    for (u32 stat = STATSTAGE_ATTACK; stat <= STATSTAGE_SPEED; ++stat) {
        if (!soul && (stat == STATSTAGE_DEFENSE || stat == STATSTAGE_SPECIAL_DEFENSE)) continue;
        if (BattleMon_IsStatChangeValid(user, (StatStage)stat, direction)) canChange = true;
    }
    if (BattleMon_GetValue(user, VALUE_CURRENT_HP) <= cost || !canChange) {
        // This native event has no VAR_MOVE_FAIL_FLAG. With no successful
        // work the engine supplies the ordinary failure and its message.
        return;
    }

    // Same native transaction as Belly Drum: pay without damage abilities,
    // queue all stat work, then allow HP berries to react to the final state.
    HandlerParam_ShiftHP* payment = (HandlerParam_ShiftHP*)
        BattleHandler_PushWork(serverFlow, EFFECT_SHIFT_HP, pokemonSlot);
    if (!payment) return;
    payment->pokeCount = 1;
    payment->effectDisable = 0;
    payment->itemReactionDisable = 1;
    payment->pokeID[0] = (u8)pokemonSlot;
    payment->volume[0] = -(s32)cost;
    BattleHandler_PopWork(serverFlow, payment);
    for (u32 stat = STATSTAGE_ATTACK; stat <= STATSTAGE_SPEED; ++stat) {
        if (!soul && (stat == STATSTAGE_DEFENSE || stat == STATSTAGE_SPECIAL_DEFENSE)) continue;
        ApplyStatChange(serverFlow, pokemonSlot, pokemonSlot, (StatStage)stat, boost, true);
    }
    HandlerParam_CheckItem* reaction = (HandlerParam_CheckItem*)
        BattleHandler_PushWork(serverFlow, EFFECT_CHECK_ITEM, pokemonSlot);
    if (reaction) {
        reaction->pokeID = (u8)pokemonSlot;
        reaction->reactionType = 1; // native HP reaction
        BattleHandler_PopWork(serverFlow, reaction);
    }
}

static BattleEventHandlerTableEntry HpCostBoostHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerHpCostBoost },
};

static void HandlerStuffCheeksCheck(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        BattleMon* user = GetBattleMon(flow, slot);
        if (!user || !PML_ItemIsBerry(BattleMon_GetHeldItem(user)))
            BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
    }
}

static void HandlerStuffCheeks(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT) || flow->simulationCounter) return;
    BattleMon* user = GetBattleMon(flow, slot);
    const ITEM berry = user ? BattleMon_GetHeldItem(user) : ITEM_NULL;
    const int direction = user && BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == 126 ? -2 : 2;
    if (!user || !PML_ItemIsBerry(berry) ||
        !BattleMon_IsStatChangeValid(user, STATSTAGE_DEFENSE, direction)) return;
    ApplyStatChange(flow, slot, slot, STATSTAGE_DEFENSE, 2, true);
    // Remove the held-item factor before creating the temporary one; otherwise
    // the same berry could receive the forced-use event twice. Consumption
    // goes through the resident native transaction (Recycle/Belch/Cheek Pouch).
    HandlerParam_ConsumeItem* consume = (HandlerParam_ConsumeItem*)
        BattleHandler_PushWork(flow, EFFECT_CONSUME_ITEM, slot);
    if (!consume) return;
    consume->dontUse = 0;
    BattleHandler_PopWork(flow, consume);
    HandlerParam_UseTempItem* effect = (HandlerParam_UseTempItem*)
        BattleHandler_PushWork(flow, EFFECT_USE_TEMP_ITEM, slot);
    if (!effect) return;
    effect->pokeID = (u8)slot;
    effect->itemID = (u16)berry;
    // Pluck's reviewed fail-skip bit: full HP/no matching status must not turn
    // the already-successful Defense boost and berry consumption into failure.
    effect->header.flags |= 1u << 24;
    BattleHandler_PopWork(flow, effect);
}

static BattleEventHandlerTableEntry StuffCheeksHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerStuffCheeksCheck },
    { EVENT_UNCATEGORIZED_MOVE, HandlerStuffCheeks },
};

static void HandlerTeatime(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (!flow || flow->simulationCounter ||
        slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    // Snapshot eligible recipients, not their items. Native target filtering
    // has already dispatched converted-type immunities (including absorbers).
    // Each synchronous PopWork completes consumption/Symbiosis before the next
    // recipient is examined; an item transferred away cannot be eaten twice.
    u8 recipients[6];
    u32 count = 0;
    const u32 targets = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    if (targets > W2U_ARRAY_COUNT(recipients)) return;
    for (u32 i = 0; i < targets; ++i) {
        const u32 target = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + i));
        BattleMon* mon = GetBattleMon(flow, target);
        if (!mon || BattleMon_IsFainted(mon) || IsMoveRecipientHidden(mon) ||
            Handler_PokeIDToPokePos(flow, target) >= W2U_NULL_BATTLE_POS ||
            !PML_ItemIsBerry(BattleMon_GetHeldItem(mon))) continue;
        bool duplicate = false;
        for (u32 j = 0; j < count; ++j) if (recipients[j] == target) duplicate = true;
        if (!duplicate) recipients[count++] = (u8)target;
    }
    for (u32 i = 0; i < count; ++i) {
        BattleMon* mon = GetBattleMon(flow, recipients[i]);
        const ITEM berry = BattleMon_GetHeldItem(mon);
        if (!PML_ItemIsBerry(berry)) continue;
        HandlerParam_ConsumeItem* consume = (HandlerParam_ConsumeItem*)
            BattleHandler_PushWork(flow, EFFECT_CONSUME_ITEM, recipients[i]);
        if (!consume) continue;
        consume->dontUse = 0;
        BattleHandler_PopWork(flow, consume);
        HandlerParam_UseTempItem* effect = (HandlerParam_UseTempItem*)
            BattleHandler_PushWork(flow, EFFECT_USE_TEMP_ITEM, slot);
        if (!effect) continue;
        effect->pokeID = recipients[i];
        effect->itemID = (u16)berry;
        effect->header.flags |= 1u << 24;
        BattleHandler_PopWork(flow, effect);
        // Consumption is success even when the berry had no useful effect.
        BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
    }
}

static BattleEventHandlerTableEntry TeatimeHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerTeatime },
};

static void HandlerShedTail(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (!flow || flow->simulationCounter || slot >= BATTLE_MAX_SLOTS ||
        slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT)) return;
    BattleMon* user = GetBattleMon(flow, slot);
    const u32 maximum = user ? BattleMon_GetValue(user, VALUE_MAX_HP) : 0;
    const u32 pos = Handler_PokeIDToPokePos(flow, slot);
    if (!user || BattleMon_IsFainted(user) || BattleMon_IsSubstituteActive(user) ||
        maximum < 4 || BattleMon_GetValue(user, VALUE_CURRENT_HP) <= (maximum + 1) / 2 ||
        pos >= W2U_NULL_BATTLE_POS || !Handler_GetFightEnableBenchPokeNum(flow, slot) ||
        !Handler_CheckReservedMemberChangeAction(flow) ||
        !W2U_MoveState_CreateShedTailSub(flow, slot)) return;

    // Native Baton Pass's position event owns the delayed replacement copy.
    // The resident exit filter makes that copy Substitute-only, including
    // the delayed client, without adding child pointers to battle state.
    HandlerParam_AddPosEffect* transfer = (HandlerParam_AddPosEffect*)
        BattleHandler_PushWork(flow, EFFECT_ADD_POS_EFFECT, slot);
    transfer->posEffect = 4; // native Baton Pass
    transfer->targetPos = pos;
    transfer->workToCopy[0] = slot;
    transfer->workCount = 1;
    BattleHandler_PopWork(flow, transfer);
    ServerDisplay_SetConditionFlag(flow, user, CONDITIONFLAG_BATONPASS);
    HandlerParam_Switch* pivot = (HandlerParam_Switch*)BattleHandler_PushWork(flow, EFFECT_SWITCH, slot);
    pivot->header.flags |= 1u << 24; // native fail-skip ordering
    pivot->pokeID = (u8)slot;
    pivot->intrDisable = true;
    BattleHandler_StrClear(&pivot->preStr);
    BattleHandler_StrClear(&pivot->exStr);
    BattleHandler_PopWork(flow, pivot);
}

static BattleEventHandlerTableEntry ShedTailHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerShedTail },
};

static void HandlerBodyPressStat(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)flow; (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_BODY_PRESS) {
        // Raw/staged/critical-aware native readers all use selector 9 for
        // Defense. Attack-side ability/item multipliers still run afterwards.
        BattleEventVar_RewriteValue(VAR_ATTACK_STAT_SELECTOR, 9);
    }
}

static BattleEventHandlerTableEntry BodyPressHandlers[] = {
    { EVENT_W2U_ATTACK_STAT_SELECTOR, HandlerBodyPressStat },
};

static void HandlerScaleShotEnd(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }
    BattleMon* user = GetBattleMon(serverFlow, pokemonSlot);
    if (!user || BattleMon_IsFainted(user)) {
        return;
    }
    // This event runs once after the whole successful damage sequence and
    // includes Substitute hits. Ordinary self-stat metadata runs per hit.
    ApplyStatChange(serverFlow, pokemonSlot, pokemonSlot, STATSTAGE_SPEED, 1, false);
    ApplyStatChange(serverFlow, pokemonSlot, pokemonSlot, STATSTAGE_DEFENSE, -1, false);
}

static BattleEventHandlerTableEntry ScaleShotHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_1, HandlerScaleShotEnd },
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

static u16 AuraWheelCurrentSpecies(const BattleMon* user)
{
    // Native core species remains the original species during Transform.
    // The resident success hook fills the otherwise unused base-param word.
    return user->flags & 0x20 ? user->transformedSpecies : user->species;
}

static void HandlerAuraWheelCheck(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID) ||
        BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_AURA_WHEEL) {
        return;
    }
    const BattleMon* user = GetBattleMon(serverFlow, pokemonSlot);
    if (!user || AuraWheelCurrentSpecies(user) != SPECIES_877 || user->form > 1) {
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
    }
}

static void HandlerAuraWheelType(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID) ||
        BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_AURA_WHEEL) {
        return;
    }
    BattleMon* user = GetBattleMon(serverFlow, pokemonSlot);
    if (!user || AuraWheelCurrentSpecies(user) != SPECIES_877 || user->form > 1) {
        return;
    }
    // Ability/position events precede move events in this engine. Preserve
    // Normalize (and an Ion Deluge conversion of that Normal move) and the
    // position's Electrify rather than overwriting their resolved type.
    if (BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == ABIL_NORMALIZE ||
        W2U_MoveState_IsElectrified(pokemonSlot)) {
        return;
    }
    BattleEventVar_RewriteValue(VAR_MOVE_TYPE,
        user->form == 1 ? TYPE_DARK : TYPE_ELECTRIC);
}

static BattleEventHandlerTableEntry AuraWheelHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerAuraWheelCheck },
    { EVENT_MOVE_PARAM, HandlerAuraWheelType },
};

static void HandlerMagicPowderGrassImmunity(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_MAGIC_POWDER &&
        HasTypeWithExtra(GetBattleMon(serverFlow,
            (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)), TYPE_GRASS)) {
        // Type immunity must not be bypassed by Mold Breaker's ability skip.
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    }
}

static void HandlerMagicPowderChangeType(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    const u16 psychic = PokeTypePair_MakeMonotype(TYPE_PSYCHIC);
    for (u32 idx = 0; idx < (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT); ++idx) {
        const u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* target = GetBattleMon(serverFlow, targetSlot);
        if (!target || BattleMon_IsFainted(target)) continue;
        const u32 extraType = W2U_MoveState_GetExtraType(targetSlot);
        if ((BattleMon_GetPokeType(target) == psychic &&
             (extraType == TYPE_NULL || extraType == TYPE_PSYCHIC)) ||
            target->species == SPECIES_ARCEUS ||
            BattleMon_GetValue(target, VALUE_EFFECTIVE_ABILITY) == ABIL_MULTITYPE ||
            BattleMon_GetValue(target, VALUE_EFFECTIVE_ABILITY) == ABIL_RKS_SYSTEM) {
            continue;
        }
        HandlerParam_ChangeType* change = (HandlerParam_ChangeType*)BattleHandler_PushWork(
            serverFlow, EFFECT_CHANGE_TYPE, pokemonSlot);
        if (!change) continue;
        change->pokeType = psychic;
        change->pokeID = (u8)targetSlot;
        change->field_7 = 0; // Native type-change message and switch restoration.
        W2U_MoveState_ClearExtraType(targetSlot);
        BattleHandler_PopWork(serverFlow, change);
    }
}

static BattleEventHandlerTableEntry MagicPowderHandlers[] = {
    { EVENT_NOEFFECT_CHECK, HandlerMagicPowderGrassImmunity },
    { EVENT_UNCATEGORIZED_MOVE, HandlerMagicPowderChangeType },
};


// Double Shock follows the same execution and type-loss path as Burn Up.
// Keep the prerequisite independent of the move's later resolved attack type.
u16 TypeConsumedByMove(MOVE_ID moveID)
{
    return moveID == MOVE_DOUBLE_SHOCK ? TYPE_ELECTRIC : TYPE_FIRE;
}

extern "C" void HandlerBurnUpCheckFail(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, pokemonSlot);
    const u16 consumedType = TypeConsumedByMove(
        (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID));
    if (!currentMon ||
        (currentMon->Type1 != consumedType && currentMon->Type2 != consumedType)) {
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
    }
}

extern "C" void HandlerBurnUpTypeLoss(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!currentMon) {
        return;
    }

    const MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    const u16 consumedType = TypeConsumedByMove(moveID);
    u16 remainingType;
    if (currentMon->Type1 == consumedType) {
        remainingType = currentMon->Type2 == consumedType
            ? TYPE_NULL
            : currentMon->Type2;
    } else if (currentMon->Type2 == consumedType) {
        remainingType = currentMon->Type1;
    } else {
        return;
    }

    HandlerParam_ChangeType* changeType =
        (HandlerParam_ChangeType*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_CHANGE_TYPE,
            pokemonSlot);
    changeType->pokeType = PokeTypePair_MakeMonotype(remainingType);
    changeType->pokeID = (u8)pokemonSlot;
    changeType->field_7 = 1;
    BattleHandler_PopWork(serverFlow, changeType);

    PushMessageArg(
        serverFlow,
        pokemonSlot,
        2u,
        moveID == MOVE_DOUBLE_SHOCK ? BATTLE_DOUBLE_SHOCK_MSGID : BATTLE_BURN_UP_MSGID,
        pokemonSlot);
}

BattleEventHandlerTableEntry BurnUpHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerBurnUpCheckFail },
    { EVENT_MOVE_EXECUTE_EFFECTIVE, HandlerBurnUpTypeLoss },
};


extern "C" void HandlerRevelationDanceType(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    u32 moveType = W2U_ResolveRevelationDanceType(
        GetBattleMon(serverFlow, pokemonSlot));

    // This final parameter phase runs after native type-changing abilities.
    // Retain the permitted Electrify / Normal-type Ion Deluge conversions
    // while overriding Normalize and the -ate abilities.
    if (W2U_MoveState_IsElectrified(pokemonSlot) ||
        (moveType == TYPE_NORMAL && W2U_MoveState_IsIonDelugeActive())) {
        moveType = TYPE_ELECTRIC;
    }

    BattleEventVar_RewriteValue(VAR_MOVE_TYPE, moveType);
}

BattleEventHandlerTableEntry RevelationDanceHandlers[] = {
    { EVENT_W2U_MOVE_PARAM_FINAL, HandlerRevelationDanceType },
};


namespace {

// ConditionData stores its continuation kind in the low three bits. Both B2
// and W2 use value 1 for a permanent condition; spelling it here avoids a
// game-specific import for the otherwise identical one-instruction helper.
constexpr ConditionData PERMANENT_CONDITION_DATA = 1u;

bool IsCoreEnforcerUnsuppressibleAbility(u32 ability)
{
    switch (ability) {
    case ABIL_MULTITYPE:
    case ABIL_STANCE_CHANGE:
    case ABIL_SCHOOLING:
    case ABIL_COMATOSE:
    case ABIL_SHIELDS_DOWN:
    case ABIL_DISGUISE:
    case ABIL_RKS_SYSTEM:
    case ABIL_BATTLE_BOND:
    case ABIL_POWER_CONSTRUCT:
    case ABIL_AS_ONE_ICE_RIDER:
    case ABIL_AS_ONE_SHADOW_RIDER:
    case ABIL_GULP_MISSILE:
    case ABIL_ICE_FACE:
    case ABIL_ZERO_TO_HERO:
        return true;
    default:
        return false;
    }
}

} // namespace

extern "C" void HandlerCoreEnforcer(
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

    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot =
            (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (!targetMon || BattleMon_IsFainted(targetMon) ||
            !BattleMon_GetTurnFlag(targetMon, TURNFLAG_ACTIONDONE) ||
            BattleMon_CheckIfMoveCondition(targetMon, CONDITION_GASTROACID) ||
            IsCoreEnforcerUnsuppressibleAbility(targetMon->currentAbility)) {
            continue;
        }

        HandlerParam_AddCondition* addCondition =
            (HandlerParam_AddCondition*)BattleHandler_PushWork(
                serverFlow,
                EFFECT_ADD_CONDITION,
                pokemonSlot);
        if (!addCondition) {
            continue;
        }

        addCondition->condition = CONDITION_GASTROACID;
        addCondition->condData = PERMANENT_CONDITION_DATA;
        addCondition->almost = 0;
        addCondition->pokeID = (u8)targetSlot;
        BattleHandler_StrSetup(&addCondition->exStr, 2u, 565u);
        BattleHandler_AddArg(&addCondition->exStr, targetSlot);
        BattleHandler_PopWork(serverFlow, addCondition);
    }
}

BattleEventHandlerTableEntry CoreEnforcerHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_1, HandlerCoreEnforcer },
};


extern "C" void HandlerAbilityIgnoringMoveStart(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        // Moongeist Beam and Sunsteel Strike use the engine's Mold Breaker
        // window so every ability lookup made while resolving the move,
        // including ally effects such as Friend Guard, follows the normal
        // ignore rules.
        HandlerMoldBreakerStart(item, serverFlow, pokemonSlot, work);
    }
}

extern "C" void HandlerAbilityIgnoringMoveEnd(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    // Always give the native handler the matching sequence-end event. It
    // checks its own work flag, making failed and interrupted moves safe.
    HandlerMoldBreakerEnd(item, serverFlow, pokemonSlot, work);
}

BattleEventHandlerTableEntry MoongeistBeamHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerAbilityIgnoringMoveStart },
    { EVENT_MOVE_SEQUENCE_END, HandlerAbilityIgnoringMoveEnd },
};


extern "C" void HandlerPhotonGeyserCategory(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!attackingMon) {
        return;
    }

    BattleEventVar_RewriteValue(
        VAR_MOVE_CATEGORY,
        ResolveRuntimeMoveCategory(MOVE_PHOTON_GEYSER, attackingMon));
}

BattleEventHandlerTableEntry PhotonGeyserHandlers[] = {
    { EVENT_MOVE_PARAM, HandlerPhotonGeyserCategory },
    { EVENT_MOVE_SEQUENCE_START, HandlerAbilityIgnoringMoveStart },
    { EVENT_MOVE_SEQUENCE_END, HandlerAbilityIgnoringMoveEnd },
};

// The reviewed native EABI divmod returns the quotient in r0. Naming the
// existing import avoids a separate toolchain-specific uidiv dependency.
extern "C" u32 W2U_UnsignedQuotient(u32 numerator, u32 denominator) __asm__("__aeabi_uidivmod");
static u32 ShellSideArmStagedStat(BattleMon* mon, BattleMonValue stat, BattleMonValue stage)
{
    const u32 raw = BattleMon_GetRealStat(mon, stat);
    const u32 rank = BattleMon_GetValue(mon, stage);
    return rank >= 6 ? raw * (2 + rank - 6) / 2 : W2U_UnsignedQuotient(raw * 2, 2 + 6 - rank);
}

static void HandlerShellSideArmReset(BattleEventItem*, ServerFlow* flow, u32 slot, u32* work)
{
    if (!flow->simulationCounter && work && slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON))
        work[0] = 0;
}

static void HandlerShellSideArmCategory(BattleEventItem*, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    BattleMon* user = GetBattleMon(flow, slot);
    BattleMon* target = GetBattleMon(flow, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (!user || !target) return;
    u32 category;
    if (!flow->simulationCounter && work && work[0]) category = work[0];
    else {
        // Wonder Room exchanges the Defense ranks in this forecast, not the
        // raw defensive stats. Items/abilities/screens/weather are excluded.
        const bool room = BattleField_CheckEffect(6u);
        const u32 attack = ShellSideArmStagedStat(user, VALUE_ATTACK_STAT, VALUE_ATTACK_STAGE);
        const u32 specialAttack = ShellSideArmStagedStat(user, VALUE_SPECIAL_ATTACK_STAT, VALUE_SPECIAL_ATTACK_STAGE);
        // Native raw readers already exchange their selectors in Wonder Room;
        // invert that selector here to keep the original raw forecast stat.
        const u32 defense = ShellSideArmStagedStat(target, room ? VALUE_SPECIAL_DEFENSE_STAT : VALUE_DEFENSE_STAT,
            room ? VALUE_SPECIAL_DEFENSE_STAGE : VALUE_DEFENSE_STAGE);
        const u32 specialDefense = ShellSideArmStagedStat(target, room ? VALUE_DEFENSE_STAT : VALUE_SPECIAL_DEFENSE_STAT,
            room ? VALUE_DEFENSE_STAGE : VALUE_SPECIAL_DEFENSE_STAGE);
        const u32 factor = W2U_UnsignedQuotient(2u * user->level, 5u) + 2u;
        const u32 physical = W2U_UnsignedQuotient(W2U_UnsignedQuotient(factor * 90u * attack, defense ? defense : 1u), 50u);
        const u32 special = W2U_UnsignedQuotient(W2U_UnsignedQuotient(factor * 90u * specialAttack, specialDefense ? specialDefense : 1u), 50u);
        category = physical > special || (physical == special &&
            !flow->simulationCounter && BattleRandom(2u) == 0u) ? SPLIT_PHYSICAL : SPLIT_SPECIAL;
        if (!flow->simulationCounter && work) work[0] = category;
    }
    BattleEventVar_RewriteValue(VAR_MOVE_CATEGORY, category);
    if (!flow->simulationCounter) W2U_MoveState_SetShellSideArmCategory(slot, category);
}

static BattleEventHandlerTableEntry ShellSideArmHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerShellSideArmReset },
    { EVENT_W2U_TARGET_PARAM_FINAL, HandlerShellSideArmCategory },
};

// Validate the complete Doodle transaction before any native ability work is
// queued. Ability-change work owns removal/re-registration, client updates,
// switch-in callbacks and restoration on switch; no child pointers are shared.
static bool IsDoodleProtectedAbility(ABILITY ability)
{
    switch (ability) {
    case ABIL_MULTITYPE:
    case 161: // Zen Mode
    case ABIL_STANCE_CHANGE:
    case ABIL_SHIELDS_DOWN:
    case ABIL_SCHOOLING:
    case ABIL_DISGUISE:
    case ABIL_BATTLE_BOND:
    case ABIL_POWER_CONSTRUCT:
    case ABIL_COMATOSE:
    case ABIL_RKS_SYSTEM:
    case ABIL_GULP_MISSILE:
    case ABIL_ICE_FACE:
    case ABIL_AS_ONE_ICE_RIDER:
    case ABIL_AS_ONE_SHADOW_RIDER:
    case ABIL_PROTOSYNTHESIS:
    case ABIL_QUARK_DRIVE:
    case ABIL_ZERO_TO_HERO:
    case ABIL_COMMANDER:
    case ABIL_POISON_PUPPETEER:
        return true;
    default:
        return false;
    }
}

static void HandlerDoodle(BattleEventItem*, ServerFlow* flow, u32 owner, u32*)
{
    if (owner != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) != 1) return;
    BattleMon* target = GetBattleMon(flow, BattleEventVar_GetValue(VAR_TARGET_MON_ID));
    BattleMon* user = GetBattleMon(flow, owner);
    if (!target || !user || BattleMon_IsFainted(target) || BattleMon_IsFainted(user)) return;
    const ABILITY ability = BattleMon_GetValue(target, VALUE_ABILITY);
    if (IsDoodleProtectedAbility(ability) || ability == ABIL_RECEIVER) return;

    u8 recipients[W2U_SIDE_SLOT_COUNT];
    u32 count = 0;
    for (u32 slot = 0; slot < 24; ++slot) {
        BattleMon* mon = GetBattleMon(flow, slot);
        if (!mon || BattleMon_IsFainted(mon) || !MainModule_IsAllyMonID(owner, slot) ||
            Handler_PokeIDToPokePos(flow, slot) >= W2U_NULL_BATTLE_POS) continue;
        const ABILITY old = BattleMon_GetValue(mon, VALUE_ABILITY);
        if (IsDoodleProtectedAbility(old)) return;
        if (old == ability) continue;
        if (count == W2U_ARRAY_COUNT(recipients)) return;
        recipients[count++] = (u8)slot;
    }
    for (u32 i = 0; i < count; ++i) {
        HandlerParam_ChangeAbility* change = (HandlerParam_ChangeAbility*)
            BattleHandler_PushWork(flow, EFFECT_CHANGE_ABILITY, owner);
        change->ability = (u16)ability;
        change->pokeID = recipients[i];
        change->sameAbilityEffective = 0;
        change->skipSwitchInEvent = 0;
        BattleHandler_StrSetup(&change->exStr, 2u, 463u);
        BattleHandler_AddArg(&change->exStr, recipients[i]);
        BattleHandler_AddArg(&change->exStr, ability);
        BattleHandler_PopWork(flow, change);
    }
}

static BattleEventHandlerTableEntry DoodleHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerDoodle },
};


extern "C" void HandlerWaterShurikenBasePower(
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

    BattleMon* attackingMon = GetBattleMon(serverFlow, pokemonSlot);
    if (attackingMon &&
        attackingMon->species == SPECIES_GRENINJA &&
        BattleMon_GetValue(attackingMon, VALUE_FORM) == W2U_ASH_GRENINJA_FORM) {
        BattleEventVar_RewriteValue(
            VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) + 5);
    }
}

extern "C" void HandlerWaterShurikenHitCount(
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

    BattleMon* attackingMon = GetBattleMon(serverFlow, pokemonSlot);
    if (attackingMon &&
        attackingMon->species == SPECIES_GRENINJA &&
        BattleMon_GetValue(attackingMon, VALUE_FORM) == W2U_ASH_GRENINJA_FORM) {
        BattleEventVar_RewriteValue(VAR_HIT_COUNT, 3);
    }
}

BattleEventHandlerTableEntry WaterShurikenHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerWaterShurikenBasePower },
    { EVENT_MOVE_HIT_COUNT, HandlerWaterShurikenHitCount },
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
        if (!W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
            BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            return;
        }
        sIonDelugeActive = true;
        PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_ION_DELUGE_MSGID);
    }
}

BattleEventHandlerTableEntry IonDelugeHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerIonDeluge },
};


extern "C" void HandlerPlasmaFists(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
        return;
    }

    sIonDelugeActive = true;
    PushMessage(serverFlow, pokemonSlot, 2u, BATTLE_ION_DELUGE_MSGID);
}

BattleEventHandlerTableEntry PlasmaFistsHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerPlasmaFists },
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


extern "C" void HandlerStompingTantrumBasePower(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_DidLastMoveFailForStomping(pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_POWER, 150);
    }
}

static void HandlerBarbBarrageBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        IsPoisoned(GetBattleMon(serverFlow,
            (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)))) {
        // Ordinary and bad poison share CONDITION_POISON. Other major
        // statuses deliberately do not qualify under the SV ruleset.
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 2);
    }
}

static BattleEventHandlerTableEntry BarbBarrageHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerBarbBarrageBasePower },
};

static void HandlerUnactedTargetBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }
    BattleMon* target = GetBattleMon(serverFlow,
        (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (target && !BattleMon_GetTurnFlag(target, TURNFLAG_ACTIONDONE)) {
        // Query at damage execution, not selection/order construction. A
        // failed action still sets ACTIONDONE, while a new switch-in has not
        // acted. Extra actions must re-evaluate the same native state.
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 2);
    }
}

static BattleEventHandlerTableEntry UnactedTargetPowerHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerUnactedTargetBasePower },
};

static void HandlerHardPressBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }
    BattleMon* target = GetBattleMon(serverFlow,
        (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (!target) {
        return;
    }
    const u32 maximumHP = BattleMon_GetValue(target, VALUE_MAX_HP);
    if (!maximumHP) {
        return;
    }
    // Read at execution so damage/healing before the action is reflected.
    const u32 scaledHP = 100u * BattleMon_GetValue(target, VALUE_CURRENT_HP);
    // Bounded integer quotient, avoiding a new compiler division-runtime
    // import on either game. Seven comparisons produce floor(scaledHP/maxHP).
    u32 power = 0;
    for (u32 step = 64u; step; step >>= 1) {
        const u32 candidate = power + step;
        if (candidate <= 100u && candidate * maximumHP <= scaledHP) {
            power = candidate;
        }
    }
    if (power < 1u) power = 1u;
    if (power > 100u) power = 100u;
    BattleEventVar_RewriteValue(VAR_MOVE_POWER, power);
}

static BattleEventHandlerTableEntry HardPressHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerHardPressBasePower },
};

static void HandlerGravAppleBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleField_CheckEffect(W2U_FLDEFF_GRAVITY)) {
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 3 / 2);
    }
}

static BattleEventHandlerTableEntry GravAppleHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerGravAppleBasePower },
};

static void HandlerTarShot(BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT) || flow->simulationCounter) return;
    const u32 target = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    ApplyStatChange(flow, slot, target, STATSTAGE_SPEED, -1, true);
    if (W2U_MoveState_ApplyTarShot(target)) {
        PushMessageArg(flow, slot, 2u, 1457u, target);
        // New tar still succeeds at a stat cap or through Clear Body. Neither
        // speed reductions nor the Fire multiplier can accumulate the tar.
        BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
    }
}

static BattleEventHandlerTableEntry TarShotHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerTarShot },
};

static void HandlerPsybladeBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_GetTerrain() == TERRAIN_ELECTRIC) {
        // Neither battler's grounding gates this move-specific bonus.
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 3 / 2);
    }
}

static BattleEventHandlerTableEntry PsybladeHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerPsybladeBasePower },
};

static void HandlerRisingVoltageBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_GetTerrain() == TERRAIN_ELECTRIC &&
        IsGrounded(serverFlow, GetBattleMon(serverFlow,
            (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)))) {
        // Target grounding controls this bonus. The terrain's separate power
        // ratio handler still checks the user's grounding in the usual way.
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 2);
    }
}

static BattleEventHandlerTableEntry RisingVoltageHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerRisingVoltageBasePower },
};

static u32 TerrainPulseType(ServerFlow* flow, u32 pokemonSlot)
{
    if (!IsGrounded(flow, GetBattleMon(flow, pokemonSlot))) return TYPE_NORMAL;
    switch (W2U_MoveState_GetTerrain()) {
    case TERRAIN_ELECTRIC: return TYPE_ELECTRIC;
    case TERRAIN_GRASSY: return TYPE_GRASS;
    case TERRAIN_MISTY: return TYPE_FAIRY;
    case TERRAIN_PSYCHIC: return TYPE_PSYCHIC;
    default: return TYPE_NORMAL;
    }
}

static void HandlerTerrainPulseType(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID) ||
        BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_TERRAIN_PULSE) return;
    u32 type = TerrainPulseType(flow, pokemonSlot);
    // The final parameter phase runs after ability/position parameters. Restore the
    // terrain-derived type over Normalize/-ates, but retain allowed volatile
    // conversions. The power callback independently checks grounding/terrain.
    if (W2U_MoveState_IsElectrified(pokemonSlot) ||
        (type == TYPE_NORMAL && W2U_MoveState_IsIonDelugeActive())) {
        type = TYPE_ELECTRIC;
    }
    BattleEventVar_RewriteValue(VAR_MOVE_TYPE, type);
}

static void HandlerTerrainPulsePower(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_TERRAIN_PULSE &&
        TerrainPulseType(flow, pokemonSlot) != TYPE_NORMAL) {
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 2);
    }
}

static BattleEventHandlerTableEntry TerrainPulseHandlers[] = {
    { EVENT_W2U_MOVE_PARAM_FINAL, HandlerTerrainPulseType },
    { EVENT_MOVE_BASE_POWER, HandlerTerrainPulsePower },
};

static void HandlerSteelRollerCheckTerrain(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        W2U_MoveState_GetTerrain() == TERRAIN_NULL) {
        // Check at execution, not selection: another action can replace or
        // remove terrain before this battler moves.
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
    }
}

static void HandlerSteelRollerRemoveTerrain(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        // L1 runs once after successful damage, including Substitute, but not
        // a miss/protection/immunity. The resident service clears both backend
        // terrain state and the existing deferred graphics-reset request.
        W2U_MoveState_RemoveTerrain(serverFlow);
    }
}

static BattleEventHandlerTableEntry SteelRollerHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerSteelRollerCheckTerrain },
    { EVENT_DAMAGE_PROCESSING_END_HIT_1, HandlerSteelRollerRemoveTerrain },
};

static void HandlerIceSpinnerRemoveTerrain(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (!work || !work[0] ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) return;
    work[0] = 0;
    BattleMon* user = GetBattleMon(flow, pokemonSlot);
    // Sequence end is after contact/item reactions. SV does not clear
    // terrain if those reactions faint or eject the user. Substitute counts
    // as a hit, and neither a terrain prerequisite nor a grounding test applies.
    if (user && !BattleMon_IsFainted(user) &&
        Handler_PokeIDToPokePos(flow, pokemonSlot) < W2U_NULL_BATTLE_POS) {
        W2U_MoveState_RemoveTerrain(flow);
    }
}

static void HandlerIceSpinnerMarkHit(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (work && !flow->simulationCounter &&
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_DAMAGE) > 0) work[0] = 1;
}

static void HandlerIceSpinnerReset(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)flow;
    if (work && pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) work[0] = 0;
}

static BattleEventHandlerTableEntry IceSpinnerHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerIceSpinnerReset },
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerIceSpinnerMarkHit },
    { EVENT_MOVE_SEQUENCE_END, HandlerIceSpinnerRemoveTerrain },
};

static void HandlerStormRainAccuracy(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        ServerEvent_GetWeather(serverFlow) == WEATHER_RAIN) {
        // Skip the normal accuracy/evasion calculation, not protection or
        // semi-invulnerability. Unlike Thunder, storms do not hit Fly users
        // or reduce their normal accuracy in sun.
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

static BattleEventHandlerTableEntry StormRainAccuracyHandlers[] = {
    { EVENT_SKIP_ACCURACY_CHECK, HandlerStormRainAccuracy },
};

static void HandlerHydroSteamDamageWeather(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_HYDRO_STEAM &&
        BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER &&
        BattleEventVar_GetValue(VAR_WEATHER) == WEATHER_SUN) {
        // Only the damage calculation sees rain's Water multiplier. Real
        // weather, power, suppression and native rounding remain untouched.
        BattleEventVar_RewriteValue(VAR_WEATHER, WEATHER_RAIN);
    }
}

static BattleEventHandlerTableEntry HydroSteamHandlers[] = {
    { EVENT_W2U_DAMAGE_WEATHER, HandlerHydroSteamDamageWeather },
};

static void InvokeNativeMoveEvent(
    MOVE_ID move, BattleEventType event, BattleEventItem* item,
    ServerFlow* flow, u32 slot, u32* work)
{
    u32 count = 0;
    W2UNativeMoveGetter getter = W2U_FindNativeMoveGetter(move);
    if (!getter) return;
    const BattleEventHandlerTableEntry* table = getter(&count);
    for (u32 i = 0; i < count; ++i) {
        if (table[i].eventType == event) {
            table[i].handler(item, flow, slot, work);
            return;
        }
    }
}

static void HandlerMistyExplosionPower(
    BattleEventItem*, ServerFlow* flow, u32 slot, u32*)
{
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_GetTerrain() == TERRAIN_MISTY &&
        IsGrounded(flow, GetBattleMon(flow, slot))) {
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 3 / 2);
    }
}

#define W2U_EXPLOSION_DELEGATE(name, event) \
static void name(BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work) \
{ InvokeNativeMoveEvent(MOVE_EXPLOSION, event, item, flow, slot, work); }
W2U_EXPLOSION_DELEGATE(HandlerMistyExplosionStart, (BattleEventType)0x24)
W2U_EXPLOSION_DELEGATE(HandlerMistyExplosionDamage, EVENT_DETERMINE_MOVE_DAMAGE)
W2U_EXPLOSION_DELEGATE(HandlerMistyExplosionEnd, EVENT_MOVE_EXECUTE_END)
#undef W2U_EXPLOSION_DELEGATE

static BattleEventHandlerTableEntry MistyExplosionHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerMistyExplosionPower },
    { (BattleEventType)0x24, HandlerMistyExplosionStart },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerMistyExplosionDamage },
    { EVENT_MOVE_EXECUTE_END, HandlerMistyExplosionEnd },
};

static void HandlerSupercellSlamCrash(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    InvokeNativeMoveEvent(MOVE_HI_JUMP_KICK,
        EVENT_MOVE_EXECUTE_NOEFFECT, item, flow, slot, work);
}

static void HandlerTripleAxelPower(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    (void)item;
    (void)flow;
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_TRIPLE_AXEL) {
        // Triple Kick's event-owned scratch counter is zeroed by native move
        // registration for each action, including called/repeated moves.
        // No child-owned history survives an action or needs core storage.
        ++work[0];
        BattleEventVar_RewriteValue(VAR_MOVE_POWER, work[0] * 20u);
    }
}

static void HandlerTripleAxelHitCount(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    // Reuse Triple Kick's per-strike accuracy flag. Native hit-count setup
    // gives Skill Link precedence and disables later checks after one hit.
    InvokeNativeMoveEvent(MOVE_TRIPLE_KICK,
        EVENT_MOVE_HIT_COUNT, item, flow, slot, work);
}

static BattleEventHandlerTableEntry TripleAxelHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerTripleAxelPower },
    { EVENT_MOVE_HIT_COUNT, HandlerTripleAxelHitCount },
};

static void HandlerPopulationBombHitCount(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    BattleMon* user = GetBattleMon(flow, slot);
    if (!user) return;
    // Ten fixed strikes come from move data. Unlike native 2–5-hit moves,
    // the engine's Skill Link shortcut does not cover a maximum above five.
    // Leaving the per-strike flag unset explicitly gives Skill Link its one
    // initial accuracy check; ordinary users reuse Triple Kick's stop-on-miss.
    if (BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) != ABIL_SKILL_LINK)
        InvokeNativeMoveEvent(MOVE_TRIPLE_KICK,
            EVENT_MOVE_HIT_COUNT, item, flow, slot, work);
}

static BattleEventHandlerTableEntry PopulationBombHandlers[] = {
    { EVENT_MOVE_HIT_COUNT, HandlerPopulationBombHitCount },
};

static void HandlerMinimizeDamage(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    InvokeNativeMoveEvent(MOVE_STOMP,
        EVENT_MOVE_DAMAGE_PROCESSING_2, item, flow, slot, work);
}

static void HandlerMinimizeAccuracy(
    BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    (void)item;
    (void)work;
    if (slot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        BattleMon* target = GetBattleMon(flow,
            (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON));
        if (target && BattleMon_GetConditionFlag(target, CONDITIONFLAG_MINIMIZED)) {
            // The native skip-accuracy event does not bypass Protect or the
            // separate semi-invulnerability check.
            BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
        }
    }
}

static BattleEventHandlerTableEntry SupercellSlamHandlers[] = {
    { EVENT_MOVE_EXECUTE_NOEFFECT, HandlerSupercellSlamCrash },
    { EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerMinimizeDamage },
    // Unlike the attacker-only weather shortcut (0x32), 0x1C exposes both
    // battlers. Target-dependent Minimize checks must use this scope.
    { EVENT_SKIP_TARGET_ACCURACY_CHECK, HandlerMinimizeAccuracy },
};

static void HandlerDireClaw(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_DAMAGE) <= 0 ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) {
        return;
    }
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* target = GetBattleMon(serverFlow, targetSlot);
    if (!target || BattleMon_IsFainted(target)) return;

    // Use the native secondary-chance event for Serene Grace, rainbow,
    // Shield Dust and Sheer Force. Metadata marks this as damage + status
    // (including the native Sheer Force boost), but leaves status NONE so
    // the ordinary pipeline cannot apply an extra, fixed status.
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, pokemonSlot);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, targetSlot);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, MOVE_DIRE_CLAW);
    BattleEventVar_SetValue(VAR_CONDITION_ID, CONDITION_POISON);
    BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
    BattleEventVar_SetValue(VAR_ADDED_EFFECT_CHANCE, 50);
    BattleEvent_CallHandlers(serverFlow, EVENT_ADDED_STATUS_CHANCE);
    const u32 chance = (u32)BattleEventVar_GetValue(VAR_ADDED_EFFECT_CHANCE);
    const bool failed = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG) != 0;
    BattleEventVar_Pop();
    if (failed || !chance || (chance < 100 && BattleRandom(100) >= chance)) return;

    // Activation first, then one uniform choice. Never reroll an immune
    // status; native condition work supplies ability/terrain/status checks.
    static const CONDITION statuses[] = {
        CONDITION_POISON, CONDITION_PARALYSIS, CONDITION_SLEEP,
    };
    const CONDITION status = statuses[BattleRandom(W2U_ARRAY_COUNT(statuses))];
    // BW2 predates the modern Electric-type paralysis immunity.
    if (status == CONDITION_PARALYSIS && HasTypeWithExtra(target, TYPE_ELECTRIC)) return;
    HandlerParam_AddCondition* effect = (HandlerParam_AddCondition*)
        BattleHandler_PushWork(serverFlow, EFFECT_ADD_CONDITION, pokemonSlot);
    if (!effect) return;
    effect->condition = status;
    effect->condData = MakeBasicStatus(status);
    effect->almost = 0;
    effect->pokeID = (u8)targetSlot;
    BattleHandler_PopWork(serverFlow, effect);
}

static BattleEventHandlerTableEntry DireClawHandlers[] = {
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerDireClaw },
};

static void HandlerLashOutPower(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)flow; (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        W2U_MoveState_HadStatChangeThisTurn(pokemonSlot, false)) {
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 2);
    }
}

static BattleEventHandlerTableEntry LashOutHandlers[] = {
    { EVENT_MOVE_BASE_POWER, HandlerLashOutPower },
};

static void HandlerStatRiseStatusReset(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)flow;
    if (work && pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON))
        work[0] = 0;
}

static void HandlerStatRiseStatusSnapshot(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || !flow || flow->simulationCounter ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    const u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    // Freeze eligibility before damage reactions can activate Weakness Policy
    // or a reactive ability. Later reactions cannot qualify this same hit.
    SetSlotFlag(work[0], target, W2U_MoveState_HadStatChangeThisTurn(target, true));
}

static void HandlerStatRiseStatusApply(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item;
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    const MOVE_ID move = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!work || !flow || flow->simulationCounter ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !(work[0] & SlotMask(targetSlot)) || BattleEventVar_GetValue(VAR_DAMAGE) <= 0 ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) return;
    BattleMon* target = GetBattleMon(flow, targetSlot);
    if (!target || BattleMon_IsFainted(target)) return;
    const CONDITION status = move == MOVE_ALLURING_VOICE ?
        CONDITION_CONFUSION : CONDITION_BURN;
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, pokemonSlot);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, targetSlot);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, move);
    BattleEventVar_SetValue(VAR_CONDITION_ID, status);
    BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
    BattleEventVar_SetValue(VAR_ADDED_EFFECT_CHANCE, 100);
    BattleEvent_CallHandlers(flow, EVENT_ADDED_STATUS_CHANCE);
    const bool failed = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG) != 0 ||
        BattleEventVar_GetValue(VAR_ADDED_EFFECT_CHANCE) == 0;
    BattleEventVar_Pop();
    if (failed) return;
    HandlerParam_AddCondition* effect = (HandlerParam_AddCondition*)
        BattleHandler_PushWork(flow, EFFECT_ADD_CONDITION, pokemonSlot);
    if (!effect) return;
    effect->condition = status;
    if (status == CONDITION_CONFUSION) MakeCondition(status, target, &effect->condData);
    else effect->condData = MakeBasicStatus(status);
    effect->almost = 0;
    effect->pokeID = (u8)targetSlot;
    BattleHandler_PopWork(flow, effect);
}

static BattleEventHandlerTableEntry BurningJealousyHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerStatRiseStatusReset },
    { EVENT_MOVE_DAMAGE_PROCESSING_1, HandlerStatRiseStatusSnapshot },
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerStatRiseStatusApply },
};

static BattleEventHandlerTableEntry AlluringVoiceHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerStatRiseStatusReset },
    { EVENT_MOVE_DAMAGE_PROCESSING_1, HandlerStatRiseStatusSnapshot },
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerStatRiseStatusApply },
    { EVENT_BYPASS_SUBSTITUTE, HandlerBypassSubstitute },
};

static void HandlerEerieSpellPP(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)work;
    if (!flow || flow->simulationCounter ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_DAMAGE) <= 0 ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) return;
    BattleMon* user = GetBattleMon(flow, pokemonSlot);
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* target = GetBattleMon(flow, targetSlot);
    if (!user || !target || BattleMon_IsFainted(target) ||
        BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE) return;
    // Spite's native history getter and surface-slot lookup remain valid for
    // Transform/Mimic. A replaced or absent move must not drain another slot.
    const MOVE_ID previous = BattleMon_GetPreviousMove(target);
    if (previous == MOVE_NONE || previous == MOVE_STRUGGLE) return;
    for (u32 slot = 0; slot < W2U_ARRAY_COUNT(target->moves); ++slot) {
        const MoveCore& move = target->moves[slot].surface;
        if (move.moveID != previous) continue;
        const u8 amount = move.currentPP < 3 ? move.currentPP : 3;
        if (!amount) return;
        HandlerParam_ReducePP* effect = (HandlerParam_ReducePP*)
            BattleHandler_PushWork(flow, EFFECT_REDUCE_PP, pokemonSlot);
        if (!effect) return;
        effect->amount = amount;
        effect->pokeID = (u8)targetSlot;
        effect->moveSlot = (u8)slot;
        // Reuse Spite's existing target/move/amount message, not a new text ID.
        BattleHandler_StrSetup(&effect->exStr, 2u, 641u);
        BattleHandler_AddArg(&effect->exStr, targetSlot);
        BattleHandler_AddArg(&effect->exStr, previous);
        BattleHandler_AddArg(&effect->exStr, amount);
        BattleHandler_PopWork(flow, effect);
        return;
    }
}

static BattleEventHandlerTableEntry EerieSpellHandlers[] = {
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerEerieSpellPP },
    { EVENT_BYPASS_SUBSTITUTE, HandlerBypassSubstitute },
};

static void HandlerCorrosiveGas(BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT) || flow->simulationCounter) return;
    // The reviewed native Knock Off callback only queues non-consumption
    // item removal. Its item-set validation preserves Sticky Hold and the
    // resident protected-form-item predicate, without recording an eaten item.
    InvokeNativeMoveEvent(MOVE_KNOCK_OFF, EVENT_DAMAGE_PROCESSING_END_HIT_REAL, item, flow, slot, work);
}

static BattleEventHandlerTableEntry CorrosiveGasHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerCorrosiveGas },
};

static void HandlerSuperEffectiveDamageBonus(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    const u32 effectiveness = (u32)BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS);
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        (effectiveness == RESULT_SUPER_EFFECTIVE ||
         effectiveness == W2U_EFFECTIVENESS_4 || effectiveness == W2U_EFFECTIVENESS_8 ||
         effectiveness == W2U_EFFECTIVENESS_16)) {
        // Collision Course / Electro Drift modify final damage, not power
        // or the type chart. Native fixed-point chaining supplies rounding.
        BattleEventVar_MulValue(VAR_RATIO, 5461);
    }
}

static BattleEventHandlerTableEntry SuperEffectiveDamageHandlers[] = {
    { EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerSuperEffectiveDamageBonus },
};

static void HandlerFickleBeamReset(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (work && pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        work[0] = 0;
    }
}

static void HandlerFickleBeamBasePower(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (!work || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }
    // Event-owned scratch lasts for this action, including additional hits
    // and repeated power queries. A new action (including Instruct) resets it.
    // Delay the draw until actual power calculation; blocked moves don't roll.
    if (!work[0]) {
        work[0] = BattleRandom(100) < 30u ? 2u : 1u;
    }
    if (work[0] == 2u) {
        BattleEventVar_RewriteValue(VAR_MOVE_POWER,
            BattleEventVar_GetValue(VAR_MOVE_POWER) * 2);
    }
}

static BattleEventHandlerTableEntry FickleBeamHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerFickleBeamReset },
    { EVENT_MOVE_BASE_POWER, HandlerFickleBeamBasePower },
};

BattleEventHandlerTableEntry StompingTantrumHandlers[] = {
    // Temper Flare shares the same 75 -> 150 rule and resident outcome history.
    { EVENT_MOVE_BASE_POWER, HandlerStompingTantrumBasePower },
};

// The native bit-13 flag bypasses Substitute for status moves, not damage.
// Reuse the native callback for damaging sound moves; boosts stay in data.
BattleEventHandlerTableEntry SoundDamageBypassHandlers[] = {
    { EVENT_BYPASS_SUBSTITUTE, HandlerBypassSubstitute },
};

static void HandlerPoltergeistReset(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    if (work && pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        work[0] = 0;
        work[1] = 0;
    }
}

static void HandlerPoltergeistCheckItem(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if ((work[0] & 0x10000u) && work[1] == targetSlot) {
        // A berry or reactive item may disappear on the first hit. Eligibility
        // lasts for this action, not for every subsequent Parental Bond hit.
        return;
    }
    BattleMon* target = GetBattleMon(serverFlow, targetSlot);
    const u32 heldItem = target ? BattleMon_GetHeldItem(target) : 0u;
    if (heldItem) {
        // Held, not usable: Embargo/Magic Room/Klutz do not invalidate it.
        work[0] = heldItem | 0x10000u;
        work[1] = targetSlot;
    } else if (BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        HandlerParam_StrParams* str =
            (HandlerParam_StrParams*)BattleEventVar_GetValue(VAR_WORK_ADDRESS);
        if (str) BattleHandler_StrSetup(str, 1u, 71u); // Native "But it failed!"
    }
}

static void HandlerPoltergeistAnnounceItem(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    if (!work || !serverFlow || serverFlow->simulationCounter ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !(work[0] & 0x10000u) || (work[0] & 0x20000u) ||
        work[1] != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) {
        return;
    }
    // Actual damage calculation follows immunity, Protect and accuracy. This
    // also covers Substitute, before damage/item reactions, but not AI previews.
    work[0] |= 0x20000u;
    PushMessageArgs(serverFlow, pokemonSlot, 2u, 1349u, work[1], work[0] & 0xFFFFu);
}

static BattleEventHandlerTableEntry PoltergeistHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerPoltergeistReset },
    // Unlike L1, L2 is called even when either battler has No Guard.
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerPoltergeistCheckItem },
    { EVENT_MOVE_DAMAGE_PROCESSING_1, HandlerPoltergeistAnnounceItem },
};


static void HandlerMindBlownReset(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    if (work && pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        work[0] = 0;
    }
}

static void HandlerMindBlownMarkAttempt(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    if (work && pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        // Both successful hits and target-level no-effect results count as
        // attacking. A sequence with no target reaches neither event.
        work[0] = 1;
    }
}

static void HandlerChloroblastMarkHit(
    BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    // Real damage determination includes Substitute and zero-damage Disguise
    // hits, but not misses, immunity, protection or AI damage estimates.
    if (work && serverFlow && !serverFlow->simulationCounter &&
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        work[0] = 1;
    }
}

static void HandlerMindBlownRecoil(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    if (!work || work[0] == 0 ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    work[0] = 0;
    BattleMon* currentMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!currentMon || BattleMon_IsFainted(currentMon)) {
        return;
    }
    if (BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_CHLOROBLAST &&
        BattleMon_GetValue(currentMon, VALUE_EFFECTIVE_ABILITY) == 69u) {
        // Only Chloroblast honors Rock Head. Gastro Acid removes this veto.
        return;
    }

    // Use simple damage so native Magic Guard applies while Rock Head does
    // not. The sequence-end timing also makes this happen once after every
    // target in a spread battle has finished resolving.
    const u32 halfMaximumHP = (BattleMon_GetValue(currentMon, VALUE_MAX_HP) + 1u) / 2u;
    PushDamage(
        serverFlow,
        pokemonSlot,
        pokemonSlot,
        halfMaximumHP ? halfMaximumHP : 1u,
        BATTLE_RECOIL_MSGID,
        pokemonSlot);
}

static BattleEventHandlerTableEntry MindBlownHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerMindBlownReset },
    { EVENT_MOVE_EXECUTE_EFFECTIVE, HandlerMindBlownMarkAttempt },
    { EVENT_MOVE_EXECUTE_NOEFFECT, HandlerMindBlownMarkAttempt },
    { EVENT_MOVE_SEQUENCE_END, HandlerMindBlownRecoil },
};

static BattleEventHandlerTableEntry ChloroblastHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerMindBlownReset },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerChloroblastMarkHit },
    { EVENT_MOVE_SEQUENCE_END, HandlerMindBlownRecoil },
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
        (!MainModule_IsAllyMonID(attackingSlot, defendingSlot) ||
            BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_DECORATE) &&
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
        if (side < W2U_SIDE_COUNT && W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
            sCraftyShieldActive(side) = true;
            sCraftyShieldOwner(side) = (u8)pokemonSlot;
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


extern "C" void HandlerFloralHealingRatio(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_FLORAL_HEALING &&
        W2U_MoveState_GetTerrain() == TERRAIN_GRASSY) {
        BattleEventVar_RewriteValue(VAR_RATIO, W2U_RECOVER_RATIO_TWO_THIRDS);
    }
}

BattleEventHandlerTableEntry FloralHealingHandlers[] = {
    { EVENT_RECOVER_HP, HandlerFloralHealingRatio },
};


extern "C" void HandlerShoreUpRatio(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_SHORE_UP) {
        BattleEventVar_RewriteValue(VAR_RATIO,
            ServerEvent_GetWeather(serverFlow) == WEATHER_SANDSTORM
                ? W2U_RECOVER_RATIO_TWO_THIRDS : W2U_RATIO_HALF);
    }
}

BattleEventHandlerTableEntry ShoreUpHandlers[] = {
    { EVENT_RECOVER_HP, HandlerShoreUpRatio },
};


extern "C" void HandlerSolarBladeChargeSkip(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        ServerEvent_GetWeather(serverFlow) == WEATHER_SUN) {
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

extern "C" void HandlerSolarBladeChargeStart(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        PushMessageArg(
            serverFlow,
            pokemonSlot,
            2u,
            BATTLE_SOLAR_BEAM_CHARGE_MSGID,
            pokemonSlot);
    }
}

extern "C" void HandlerSolarBladeWeatherPower(
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

    const WEATHER weather = ServerEvent_GetWeather(serverFlow);
    if (weather == WEATHER_RAIN ||
        weather == WEATHER_HAIL ||
        weather == WEATHER_SANDSTORM) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_RATIO_HALF);
    }
}

BattleEventHandlerTableEntry SolarBladeHandlers[] = {
    { EVENT_CHECK_CHARGE_UP_SKIP, HandlerSolarBladeChargeSkip },
    { EVENT_CHARGE_UP_START, HandlerSolarBladeChargeStart },
    { EVENT_MOVE_POWER, HandlerSolarBladeWeatherPower },
};

extern "C" void HandlerEnergyChargeStart(
    BattleEventItem*, ServerFlow* flow, u32 pokemonSlot, u32*)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        PushMessageArg(flow, pokemonSlot, 2u, BATTLE_ENERGY_CHARGE_MSGID, pokemonSlot);
    }
}

extern "C" void HandlerEnergyChargeBoost(
    BattleEventItem*, ServerFlow* flow, u32 pokemonSlot, u32*)
{
    // Native confirmed-charge dispatch runs once on the initial turn, even
    // when weather or Power Herb skips the wait. It does not run on release.
    if (!flow->simulationCounter &&
        pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        ApplyStatChange(flow, pokemonSlot, pokemonSlot, STATSTAGE_SPECIAL_ATTACK, 1, true);
    }
}

extern "C" void HandlerElectroShotChargeSkip(
    BattleEventItem*, ServerFlow* flow, u32 pokemonSlot, u32*)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) &&
        ServerEvent_GetWeather(flow) == WEATHER_RAIN) {
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

BattleEventHandlerTableEntry MeteorBeamHandlers[] = {
    { EVENT_CHARGE_UP_START, HandlerEnergyChargeStart },
    { EVENT_CHARGE_UP_START_DONE, HandlerEnergyChargeBoost },
};

BattleEventHandlerTableEntry ElectroShotHandlers[] = {
    { EVENT_CHECK_CHARGE_UP_SKIP, HandlerElectroShotChargeSkip },
    { EVENT_CHARGE_UP_START, HandlerEnergyChargeStart },
    { EVENT_CHARGE_UP_START_DONE, HandlerEnergyChargeBoost },
};


extern "C" void HandlerPollenPuffDamageToRecoverCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    if (!work || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    work[0] = 0;
    const u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    const u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    // EVENT_CHECK_DAMAGE_TO_RECOVER does not publish VAR_MOVE_ID. This handler
    // is dispatched from Pollen Puff's move-scoped event item, matching how
    // vanilla Present identifies its recovery branch.
    if (MainModule_IsAllyMonID(attackingSlot, defendingSlot)) {
        work[0] = 1;
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

extern "C" void HandlerPollenPuffDamageToRecover(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    if (!work || !work[0] ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    // The damage executor removes this ally from its damage target set before
    // dispatching this event, just as it does for Present's recovery branch.
    // Queue the recovery through HandEx so the move still gets the normal
    // impact/effect synchronization commands expected by its animation VM.
    work[0] = 0;
    const u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* defendingMon = GetBattleMon(serverFlow, defendingSlot);
    if (!defendingMon) {
        return;
    }

    if (defendingMon->currentHP >= defendingMon->maxHP) {
        PushMessageArg(serverFlow, pokemonSlot, 2u, 523u, defendingSlot);
        return;
    }

    HandlerParam_RecoverHP* recover =
        (HandlerParam_RecoverHP*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_RECOVER_HP,
            pokemonSlot);
    recover->pokeID = (u8)defendingSlot;
    recover->recoverHP = (u16)DivideMaxHPZeroCheck(defendingMon, 2);
    BattleHandler_StrSetup(&recover->exStr, 2u, 387u);
    BattleHandler_AddArg(&recover->exStr, defendingSlot);
    BattleHandler_PopWork(serverFlow, recover);
}

BattleEventHandlerTableEntry PollenPuffHandlers[] = {
    { EVENT_CHECK_DAMAGE_TO_RECOVER, HandlerPollenPuffDamageToRecoverCheck },
    { EVENT_DAMAGE_TO_RECOVER, HandlerPollenPuffDamageToRecover },
};


extern "C" void HandlerPurify(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    if (!work || pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    // This move event persists between uses. Clear a stale completion marker
    // before evaluating the current target so failed uses cannot heal later.
    work[0] = 0;

    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (!targetMon || BattleMon_IsFainted(targetMon)) {
        return;
    }

    // Read the target's actual major status rather than its effective ability.
    // Comatose therefore remains CONDITION_NONE and does not make Purify succeed.
    const CONDITION status = BattleMon_GetStatus(targetMon);
    if (!IsPurifiableStatus(status)) {
        return;
    }

    work[0] = 1;
    CureMoveCondition(serverFlow, pokemonSlot, targetSlot, status);
}

extern "C" void HandlerPurifyRecover(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    if (!work || work[0] == 0 ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    work[0] = 0;

    BattleMon* userMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!userMon || BattleMon_IsFainted(userMon) ||
        BattleMon_GetValue(userMon, VALUE_CURRENT_HP) >=
            BattleMon_GetValue(userMon, VALUE_MAX_HP)) {
        return;
    }

    HandlerParam_RecoverHP* recover =
        (HandlerParam_RecoverHP*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_RECOVER_HP,
            pokemonSlot);
    recover->pokeID = (u8)pokemonSlot;
    recover->recoverHP = (u16)DivideMaxHPZeroCheck(userMon, 2);
    BattleHandler_StrSetup(&recover->exStr, 2u, 387u);
    BattleHandler_AddArg(&recover->exStr, pokemonSlot);
    BattleHandler_PopWork(serverFlow, recover);
}

BattleEventHandlerTableEntry PurifyHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerPurify },
    { EVENT_MOVE_SEQUENCE_END, HandlerPurifyRecover },
};


static void HandlerSparklySwirl(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    // Sparkly Swirl deals damage normally and then performs Heal Bell's full
    // party cure. Reusing only Heal Bell's effect handler preserves native
    // traversal of the user's party and an allied trainer's party while
    // avoiding Heal Bell's status-move accuracy and targeting handlers.
    u32 handlerCount = 0;
    BattleEventHandlerTableEntry* handlers = EventAddHealBell(&handlerCount);
    for (u32 idx = 0; handlers && idx < handlerCount; ++idx) {
        if (handlers[idx].eventType == EVENT_UNCATEGORIZED_MOVE_NO_TARGET &&
            handlers[idx].handler) {
            handlers[idx].handler(item, serverFlow, pokemonSlot, work);
            return;
        }
    }
}

BattleEventHandlerTableEntry SparklySwirlHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerSparklySwirl },
};


static void HandlerSparklingAria(
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

    // This event exposes only battlers that the move actually hit directly;
    // protected, immune, Soundproof, and substitute-only targets are absent.
    // Sparkling Aria is a spread move, so cure every burned entry rather than
    // relying on the single-defender event variable.
    const u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        const u32 targetSlot =
            (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (targetMon && !BattleMon_IsFainted(targetMon) &&
            BattleMon_GetStatus(targetMon) == CONDITION_BURN) {
            CureMoveCondition(
                serverFlow,
                pokemonSlot,
                targetSlot,
                CONDITION_BURN);
        }
    }
}

BattleEventHandlerTableEntry SparklingAriaHandlers[] = {
    { EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerSparklingAria },
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


extern "C" void HandlerPsychicTerrain(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    CommonTerrainMove(serverFlow, pokemonSlot, TERRAIN_PSYCHIC, BATTLE_PSYCHIC_TERRAIN_MSGID);
}

BattleEventHandlerTableEntry PsychicTerrainHandlers[] = {
    { EVENT_CALL_FIELD_EFFECT, HandlerPsychicTerrain },
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
        W2U_MoveState_ClearElectrifiedSlot(pokemonSlot);
        BattleEventItem_Remove(item);
    }
}

BattleEventHandlerTableEntry PosElectrifyHandlers[] = {
    { EVENT_MOVE_PARAM, HandlerPosElectrify },
    { EVENT_MOVE_SEQUENCE_END, HandlerPosElectrifyMoveSequenceEnd },
    { EVENT_TURN_CHECK_DONE, HandlerPosTurnCheckDone },
};
#endif

#if !defined(W2U_BATTLE_CHILD)
extern "C" u32 fixed_round(u32 value, u32 ratio);
extern "C" u32 MultiplyValueByRatio(u32 value, u32 ratio);

extern "C" b32 W2U_CheckDamagingSubstitute(BattleMon* target, const MoveParam* move)
{
    // This query is scoped to the native hit-damage classifier, not a global
    // replacement of IsSubstituteActive. The actual doll is never modified.
    if (move && (getMoveFlag((MOVE_ID)move->moveID, MOVE_FLAG_INDEX_SOUND) ||
                 getMoveFlag((MOVE_ID)move->moveID, 13u))) return false;
    return BattleMon_IsSubstituteActive(target);
}

extern "C" bool W2U_MoveIsRestrictedNpcAttack(MOVE_ID moveID)
{
    return moveID >= MOVE_BLAZING_TORQUE && moveID <= MOVE_MAGICAL_TORQUE;
}

extern "C" b32 BattleMove_AssistIsForbidden(MOVE_ID);
extern "C" b32 BattleMove_SleepTalkIsForbidden(MOVE_ID);
extern "C" b32 BattleMove_MeFirstIsForbidden(MOVE_ID);
extern "C" b32 BattleMove_CopycatIsForbidden(MOVE_ID);

#define W2U_NPC_CALL_POLICY(hook, native) \
    extern "C" b32 hook(MOVE_ID moveID) { \
        return W2U_MoveIsRestrictedNpcAttack(moveID) || native(moveID); \
    }
W2U_NPC_CALL_POLICY(THUMB_BRANCH_LINK_167_0x21CC4DC, BattleMove_AssistIsForbidden)
W2U_NPC_CALL_POLICY(THUMB_BRANCH_LINK_167_0x21CC5A2, BattleMove_SleepTalkIsForbidden)
W2U_NPC_CALL_POLICY(THUMB_BRANCH_LINK_167_0x21CC754, BattleMove_MeFirstIsForbidden)
W2U_NPC_CALL_POLICY(THUMB_BRANCH_LINK_167_0x21CC7D6, BattleMove_CopycatIsForbidden)
#undef W2U_NPC_CALL_POLICY

extern "C" void THUMB_BRANCH_LINK_167_0x21A5542(
    ServerFlow* flow, const MoveParam* move, BattleMon* attacker, PokeSet* targets)
{
    // Reuse the native post-secondary thaw pass and its actual-hit target set.
    // The fire classification is local to this pass; damage/type/STAB and the
    // original move context remain Ground (or their already-resolved type).
    if (move->moveID == MOVE_SCORCHING_SANDS || move->moveID == MOVE_MATCHA_GOTCHA) {
        MoveParam thaw = *move;
        thaw.moveType = TYPE_FIRE;
        ServerControl_ThawHitTargets(flow, &thaw, attacker, targets);
    } else {
        ServerControl_ThawHitTargets(flow, move, attacker, targets);
    }
}

// Preserve the native Damp factor's five callbacks, including Mold Breaker
// skip handling and its ability popup. Only expand its execution predicate.
extern "C" void THUMB_BRANCH_HandlerDampCheck(
    BattleEventItem*, ServerFlow*, u32, u32* work)
{
    const MOVE_ID move = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    work[0] = 0;
    if ((move == MOVE_EXPLOSION || move == MOVE_SELFDESTRUCT ||
         move == MOVE_MISTY_EXPLOSION || move == MOVE_MIND_BLOWN) &&
        BattleEventVar_GetValue(VAR_FAIL_CAUSE) == MOVE_FAIL_NULL) {
        work[0] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 0x13);
        work[1] = move;
    }
}

// Replace the bind-local import veneer, not its BL call. Overlay 169 lives
// outside Thumb BL range of the PMC heap; an eight-byte absolute branch is
// required. Clean W2/B2 both call this veneer only from bind residual.
extern "C" u32 W2U_BindResidualQuotient(BattleMon* mon, u32 divisor)
{
    const MOVE_ID move = (MOVE_ID)Condition_GetParam(
        BattleMon_GetMoveCondition(mon, CONDITION_BIND));
    // The native bind record snapshots Binding Band when the trap is set.
    // This call site is bind residual only, not poison, burn or item damage.
    if (move == MOVE_SNAP_TRAP || move == MOVE_THUNDER_CAGE)
        divisor = divisor == 8 ? 6u : 8u;
    return DivideMaxHPZeroCheck(mon, divisor);
}

extern "C" W2UNativeMoveGetter W2U_FindNativeMoveGetter(MOVE_ID nativeMove)
{
    for (u32 i = 0; i < W2U_MOVE_EVENT_TABLE_COUNT; ++i) {
        if (W2U_MOVE_EVENT_TABLE[i].moveID == nativeMove) {
            return W2U_MOVE_EVENT_TABLE[i].func;
        }
    }
    return 0;
}

extern "C" u32 W2U_DispatchAttackStatSelector(
    ServerFlow* flow, BattleEventType nativeEvent, MoveParam* move, u32 selector)
{
    BattleEvent_CallHandlers(flow, nativeEvent);
    // A nested scope preserves the native Foul Play/Unaware context and does
    // not leave duplicate ID/value labels when native calculation continues.
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_MOVE_ID, move->moveID);
    BattleEventVar_SetValue(VAR_ATTACK_STAT_SELECTOR, selector);
    BattleEvent_CallHandlers(flow, EVENT_W2U_ATTACK_STAT_SELECTOR);
    const u32 result = BattleEventVar_GetValue(VAR_ATTACK_STAT_SELECTOR);
    BattleEventVar_Pop();
    return result;
}

extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x86(
    BattleMon* mon, BattleMonValue selector)
{
    if (selector != VALUE_DEFENSE_STAT) return BattleMon_GetCriticalStat(mon, selector);
    // The native critical reader treats Defense as a defending stat and
    // ignores positive stages. Here it is offensive: ignore negative stages,
    // retain boosts. Unaware already takes the separate raw-stat branch.
    return BattleMon_GetValue(mon, VALUE_DEFENSE_STAGE) < 6
        ? BattleMon_GetRealStat(mon, selector) : BattleMon_GetValue(mon, selector);
}

extern "C" void W2U_DispatchFinalMoveDamage(
    ServerFlow* flow, BattleEventType event, u32* damage)
{
    u32 existing;
    // Normal damage already owns this free variable; fixed damage skips its
    // creation. Never duplicate labels or introduce a separate event scope.
    if (BattleEventVar_GetValueIfExist(VAR_DAMAGE, &existing)) {
        BattleEventVar_RewriteValue(VAR_DAMAGE, *damage);
    } else {
        BattleEventVar_SetValue(VAR_DAMAGE, *damage);
    }
    BattleEvent_CallHandlers(flow, event);
    *damage = (u32)BattleEventVar_GetValue(VAR_DAMAGE);
}

// US W2 0x021A5A36 / B2 0x021A59F6: just the damage-weather getter.
// The native multiplier/rounding, critical, random, STAB and final modifiers
// stay in the original engine. No child function pointer is retained here.
extern "C" WEATHER THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0xDE(ServerFlow* flow)
{
    WEATHER weather = ServerEvent_GetWeather(flow);
    if (weather != WEATHER_SUN) return weather;
    // Extend the active damage scope (which already owns ID/type/attacker).
    // Native CalcDamage pops the whole scope, including this extra variable.
    // Weather-check events use their own nested scope and do not read this.
    BattleEventVar_SetValue(VAR_WEATHER, weather);
    BattleEvent_CallHandlers(flow, EVENT_W2U_DAMAGE_WEATHER);
    return BattleEventVar_GetValue(VAR_WEATHER);
}

// The original damage engine rereads the database category in three places
// after EVENT_MOVE_PARAM has already populated MoveParam::category. These
// hooks must remain in the resident core: putting them in Photon Geyser's
// child module would leave no resident hook symbol for PMC to install.
extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x10(
    MOVE_ID moveID,
    BattleMon* attackingMon)
{
    const u32 category = ResolveRuntimeMoveCategory(moveID, attackingMon);
    if (moveID == MOVE_SHELL_SIDE_ARM && attackingMon) {
        const u32 mask = SlotMask(BattleMon_GetID(attackingMon));
        if (sMoveState.shellSideArmCategoryValidFlags & mask) {
            sMoveState.shellSideArmRecordedValidFlags |= mask;
            if (category == SPLIT_PHYSICAL) sMoveState.shellSideArmRecordedPhysicalFlags |= mask;
            else sMoveState.shellSideArmRecordedPhysicalFlags &= ~mask;
        }
    }
    return category;
}

// RegisterTargets' +0xBA call corrects dead/replaced targets after ordinary
// redirection. Its existing entry hook belongs to Battle Log and stays intact.
extern "C" b32 ServerControl_CorrectTargetDead(ServerFlow*, u32, BattleMon*, const MoveParam*, u32, PokeSet*);
extern "C" b32 THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(
    ServerFlow* flow, u32 rule, BattleMon* user, MoveParam* params, u32 position, PokeSet* targets)
{
    // The retail helper returns zero when no replacement was made, including
    // the ordinary live-target path. The final set, not that return value,
    // determines whether category forecasting has a valid target.
    const b32 corrected = ServerControl_CorrectTargetDead(flow, rule, user, params, position, targets);
    if (user && params && params->moveID == MOVE_DRAGON_DARTS) {
        // Native called-move parameters retain the selected original move and
        // bit 2 (fReqWaza). Never infer this from previous-turn history.
        SetSlotFlag(sMoveState.calledDartsFlags, BattleMon_GetID(user),
            (params->flags & 4) && params->originalMoveID &&
            !PML_MoveIsDamaging(params->originalMoveID));
    }
    if (!user || !params || (params->moveID != MOVE_SHELL_SIDE_ARM && params->moveID != MOVE_DRAGON_DARTS) ||
        !targets || targets->count != 1 || !targets->battleMon[0]) return corrected;
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_MOVE_ID, params->moveID);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, BattleMon_GetID(user));
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, BattleMon_GetID(targets->battleMon[0]));
    BattleEventVar_SetValue(VAR_MOVE_CATEGORY, params->category);
    BattleEventVar_SetConstValue(VAR_MOVE_FAIL_FLAG,
        !!(sMoveState.redirectedTargetFlags & SlotMask(BattleMon_GetID(user))));
    BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);
    BattleEvent_CallHandlers(flow, EVENT_W2U_TARGET_PARAM_FINAL);
    params->category = (u32)BattleEventVar_GetValue(VAR_MOVE_CATEGORY);
    const bool expandTargets = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG) != 0;
    BattleEventVar_Pop();
    if (expandTargets && params->moveID == MOVE_DRAGON_DARTS) {
        for (u32 index = 0; index < W2U_ARRAY_COUNT(flow->pokeCon->activeBattleMon); ++index) {
            BattleMon* other = flow->pokeCon->activeBattleMon[index];
            if (!other || other == targets->battleMon[0] || BattleMon_IsFainted(other)) continue;
            const u32 otherSlot = BattleMon_GetID(other);
            if (MainModule_IsAllyMonID(BattleMon_GetID(user), otherSlot) ||
                Handler_PokeIDToPokePos(flow, otherSlot) >= W2U_NULL_BATTLE_POS) continue;
            // Native PokeSet::Add contract, for the sole second doubles foe.
            const u32 at = targets->count;
            targets->battleMon[at] = other;
            targets->damage[at] = targets->substituteDamage[at] = 0;
            targets->damageType[at] = 0;
            targets->count = targets->countMax = at + 1;
            break;
        }
    }
    return corrected;
}

extern "C" bool W2U_DragonDartsHasPranksterOrigin(ServerFlow* flow, u32 slot)
{
    if (!(sMoveState.calledDartsFlags & SlotMask(slot))) return false;
    BattleMon* user = GetBattleMon(flow, slot);
    return user && BattleMon_GetValue(user, VALUE_EFFECTIVE_ABILITY) == ABIL_PRANKSTER;
}

// DamageRoot has already filtered the expanded set exactly once. A single
// surviving foe takes the ordinary two-hit path; two foes each take one hit.
// Keep the original target count intact for Pressure and all other moves.
extern "C" u32 W2U_GetFilteredMultiHitTargetCount(const PokeSet* targets, const MoveParam* params)
{
    return params->moveID == MOVE_DRAGON_DARTS ? targets->count : targets->countMax;
}

// Splitting the two darts does not make this a spread-damage move. Override
// only the native ratio selector, before any damage rounding or modifiers.
extern "C" u32 W2U_GetDamageSpreadTargetCount(const PokeSet* targets, const MoveParam* params)
{
    return params->moveID == MOVE_DRAGON_DARTS ? 1 : targets->countMax;
}

extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0xC(
    MOVE_ID moveID,
    BattleMon* attackingMon)
{
    return ResolveRuntimeMoveCategory(moveID, attackingMon);
}

extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_GetTargetDefenses_0xE(
    MOVE_ID moveID,
    BattleMon* attackingMon)
{
    return ResolveRuntimeMoveCategory(moveID, attackingMon);
}

namespace {

// BPP_WAZADMG_REC places the attacking slot at byte 5. The native Counter
// helper has the copied record in r4 when it asks for the move category.
extern "C" __attribute__((noinline)) u32 W2U_ResolveCounterRecordedMoveCategory(
    MOVE_ID moveID,
    const u8* damageRecord)
{
    if (moveID == MOVE_SHELL_SIDE_ARM && damageRecord) {
        const u32 mask = SlotMask(damageRecord[5]);
        if (mask && (sMoveState.shellSideArmRecordedValidFlags & mask))
            return (sMoveState.shellSideArmRecordedPhysicalFlags & mask) ? SPLIT_PHYSICAL : SPLIT_SPECIAL;
    }
    if (moveID == MOVE_PHOTON_GEYSER && damageRecord) {
        const u32 slotMask = SlotMask(damageRecord[5]);
        if (slotMask && (sMoveState.photonGeyserCategoryValidFlags & slotMask)) {
            return (sMoveState.photonGeyserPhysicalFlags & slotMask)
                ? SPLIT_PHYSICAL
                : SPLIT_SPECIAL;
        }
    }
    return PML_MoveGetCategory(moveID);
}

} // namespace

extern "C" __attribute__((naked)) u32 THUMB_BRANCH_LINK_CommonCounterGetRecord_0x36(
    MOVE_ID moveID)
{
    asm volatile(
        "push {r3, lr}\n"
        "mov r1, r4\n"
        "bl W2U_ResolveCounterRecordedMoveCategory\n"
        "pop {r3, pc}\n");
}

extern "C" b32 THUMB_BRANCH_BTL_CALC_CheckCritical(u8 rank)
{
    // scEvent_CheckCritical runs ability and side-effect handlers before this
    // roll. Battle Armor, Shell Armor, and Lucky Chant therefore still veto
    // the critical hit through the native failure flag before we are called.
    const u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    // Native code clamps the argument to rank four, but retains the event's
    // forced-critical request. Ability/side prevention runs before this roll.
    if (BattleEventVar_GetValue(VAR_CRIT_STAGE) == 5 || W2U_MoveState_IsLaserFocused(attackingSlot)) {
        return 1;
    }
    // Merciless: the native caller clamps the stage it passes to 4, so a
    // guaranteed hit is read from the event variable it came from.
    if (BattleEventVar_GetValue(VAR_CRIT_STAGE) >= W2U_CRIT_STAGE_ALWAYS) {
        return 1;
    }

    static const u8 criticalRankTable[] = { 16, 8, 4, 3, 2 };
    if (rank >= W2U_ARRAY_COUNT(criticalRankTable)) {
        return 0;
    }
    return BattleRandom(criticalRankTable[rank]) == 0;
}

extern "C" u32 THUMB_BRANCH_BattleMon_GetCriticalRank(BattleMon* mon)
{
    u32 rank = mon->critStage;
    if (BattleMon_GetConditionFlag(mon, 9)) {
        const u32 slot = mon->battleSlot;
        const u32 boost = IsValidSlot(slot) ? sMoveState.dragonCheerBoost[slot] : 0;
        rank = (u8)(rank + (boost ? boost : 2));
        if (rank > 4) rank = 4;
    }
    return rank;
}

extern "C" void THUMB_BRANCH_LINK_167_0x21AEDCE(ServerFlow* flow, BattleEventType event)
{
    BattleEvent_CallHandlers(flow, event);
    const u32 mask = SlotMask((u32)BattleEventVar_GetValue(VAR_ATTACKING_MON));
    sMoveState.redirectedTargetFlags &= ~mask;
    if ((u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) < BATTLE_MAX_SLOTS)
        sMoveState.redirectedTargetFlags |= mask;
}

extern "C" void THUMB_BRANCH_LINK_167_0x21AEE28(ServerFlow* flow, BattleEventType event)
{
    // Query the loaded move table before redirection, not target immunities.
    BattleEventVar_SetValue(VAR_MOVE_FAIL_FLAG, 0);
    BattleEvent_CallHandlers(flow, EVENT_W2U_REDIRECTION_CHECK);
    if (!BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG)) BattleEvent_CallHandlers(flow, event);
    if ((u32)BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_DRAGON_DARTS) {
        // TEMPT_TARGET starts with the ordinary selected target, unlike the
        // earlier query's null ID. After all handlers finish, a no-op write
        // distinguishes an untouched rewrite-once variable from one already
        // claimed by Follow Me/Rage Powder (even the selected center itself).
        // This cannot alter its value or preempt any handler: the only remaining
        // native operations are GetValue, Pop, and comparison with the input.
        const u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (!BattleEventVar_RewriteValue(VAR_DEFENDING_MON, target))
            sMoveState.redirectedTargetFlags |= SlotMask((u32)BattleEventVar_GetValue(VAR_ATTACKING_MON));
    }
}

// White 2's original recovery calculation does not expose EVENT_RECOVER_HP.
// Keep this general dispatch in the resident core so dynamically loaded move
// and ability modules can adjust healing without the core knowing mechanics.
extern "C" u32 THUMB_BRANCH_ServerEvent_CalcMoveHealAmount(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    BattleMon* currentMon)
{
    const u32 healParam = PML_MoveGetParam(moveID, MVDATA_HEAL);
    const u32 currentSlot = BattleMon_GetID(currentMon);

    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_MON_ID, currentSlot);
    BattleEventVar_SetValue(VAR_RATIO, 0);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, moveID);
    BattleEvent_CallHandlers(serverFlow, EVENT_RECOVER_HP);
    const u32 ratio = (u32)BattleEventVar_GetValue(VAR_RATIO);
    BattleEventVar_Pop();

    const u32 maxHP = BattleMon_GetValue(currentMon, VALUE_MAX_HP);
    // Shore Up floors its exact fraction, unlike the native recovery helper's
    // nearest-integer rounding. Avoid a Q12 approximation of 2/3 here too.
    const u32 finalHeal = moveID == MOVE_SHORE_UP
        ? (ratio == W2U_RECOVER_RATIO_TWO_THIRDS ? (u32)((u64)maxHP * 2u / 3u) : maxHP / 2u)
        : (ratio ? fixed_round(maxHP, ratio) : MultiplyValueByRatio(maxHP, healParam));

    if (finalHeal == 0) {
        return 1;
    }
    return finalHeal > maxHP ? maxHP : finalHeal;
}

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
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (MainModule_IsAllyMonID(attackingSlot, defendingSlot) && moveID != MOVE_DECORATE) {
        return;
    }
    BattleMon* defendingMon = GetBattleMon(serverFlow, defendingSlot);
    if (((sSpikyShieldFlags | sBanefulBunkerFlags) & SlotMask(defendingSlot)) &&
        defendingMon &&
        BattleMon_GetTurnFlag(defendingMon, TURNFLAG_PROTECT) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT) &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        MarkStompingProtection(attackingSlot);
        SetNoEffectMessageArg(523u, defendingSlot);
        TryApplySpikyShieldDamage(serverFlow, defendingSlot, attackingSlot, moveID);
        TryApplyBanefulBunkerPoison(serverFlow, defendingSlot, attackingSlot, moveID);
        return;
    }

    if ((sMatBlockProtectedFlags & SlotMask(defendingSlot)) &&
        IsDamagingMove(moveID) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT) &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        MarkStompingProtection(attackingSlot);
        SetNoEffectMessageArg(523u, defendingSlot);
        return;
    }

    u32 defendingSide = GetSideFromMonID(defendingSlot);
    if (defendingSide < W2U_SIDE_COUNT &&
        sCraftyShieldActive(defendingSide) &&
        PML_MoveGetCategory(moveID) == SPLIT_STATUS &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        MarkStompingProtection(attackingSlot);
        SetNoEffectMessageArg(BATTLE_CRAFTY_SHIELD_EFFECT_MSGID, defendingSlot);
    }
}

extern "C" void HandlerFieldTransientMoveStateNativeSideProtection(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

    // Wide Guard and Quick Guard are native side handlers. By field priority,
    // their successful rewrite and message have already been installed when
    // this resident tracker runs.
    HandlerParam_StrParams* str =
        (HandlerParam_StrParams*)BattleEventVar_GetValue(VAR_WORK_ADDRESS);
    if (str &&
        (str->ID == W2U_WIDE_GUARD_BLOCK_MSGID ||
            str->ID == W2U_QUICK_GUARD_BLOCK_MSGID)) {
        MarkStompingProtection(
            (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON));
    }
}

static void HandlerFieldTransientMoveStateMovePriority(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;

    // Native action sorting asks for priority before it registers the
    // selected move's temporary event. Use the already-live resident field
    // tracker, whose owner can be the sentinel rather than the move user.
    if (BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE_GRASSY_GLIDE &&
        W2U_MoveState_GetTerrain() == TERRAIN_GRASSY &&
        IsGrounded(serverFlow, GetBattleMon(serverFlow,
            (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)))) {
        BattleEventVar_RewriteValue(VAR_MOVE_PRIORITY,
            BattleEventVar_GetValue(VAR_MOVE_PRIORITY) + 1);
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
    } else if (sIonDelugeActive && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL) {
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
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (W2U_MoveState_IsThroatChopped(currentSlot) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_SOUND)) {
        u32 failed = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_NO_REACTION);
        if (work) {
            work[0] = failed;
        }
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        PushMessageArgs(
            serverFlow,
            currentSlot,
            2u,
            905u,
            currentSlot,
            moveID);
        return;
    }

    if (!(sPowderedFlags & SlotMask(currentSlot))) {
        return;
    }

    BattleMon* currentMon = GetBattleMon(serverFlow, currentSlot);
    if (!currentMon) {
        return;
    }

    MoveParam params;
    THUMB_BRANCH_ServerEvent_GetMoveParam(serverFlow, moveID, currentMon, &params);
    if (params.moveType != TYPE_FIRE) {
        return;
    }

    u32 failed = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_NO_REACTION);
    if (work) {
        work[0] = failed;
    }

    sPowderedFlags &= ~SlotMask(currentSlot);
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
    MarkStompingProtection(attackingSlot);
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    TryApplySpikyShieldDamage(serverFlow, defendingSlot, attackingSlot, moveID);
    TryApplyBanefulBunkerPoison(serverFlow, defendingSlot, attackingSlot, moveID);
}

extern "C" void HandlerFieldTransientMoveStateBeakBlastContact(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if (!W2U_MoveState_IsBeakBlastCharging(defendingSlot)) {
        return;
    }

    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!IsValidSlot(attackingSlot) || attackingSlot == defendingSlot ||
        !W2U_MoveMakesContact(serverFlow, moveID, attackingSlot)) {
        return;
    }

    HandlerParam_AddCondition* addCondition =
        (HandlerParam_AddCondition*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_ADD_CONDITION,
            defendingSlot);
    if (!addCondition) {
        return;
    }

    addCondition->condition = CONDITION_BURN;
    addCondition->condData = MakeBasicStatus(CONDITION_BURN);
    addCondition->almost = 0;
    addCondition->pokeID = (u8)attackingSlot;
    BattleHandler_PopWork(serverFlow, addCondition);
}

extern "C" void HandlerFieldTransientMoveStateShellTrapHit(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;

    const u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    const u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (!W2U_MoveState_IsShellTrapWaiting(defendingSlot) ||
        !IsValidSlot(attackingSlot) ||
        attackingSlot == defendingSlot ||
        MainModule_IsAllyMonID(attackingSlot, defendingSlot) ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_MOVE_CATEGORY) != SPLIT_PHYSICAL) {
        return;
    }

    BattleMon* defendingMon = GetBattleMon(serverFlow, defendingSlot);
    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    const MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!defendingMon || !attackingMon ||
        BattleMon_IsFainted(defendingMon) ||
        BattleMon_GetTurnFlag(defendingMon, TURNFLAG_ACTIONDONE) ||
        (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE &&
            IsAffectedBySheerForceIncludingCustomMoves(moveID))) {
        return;
    }

    if (!W2U_MoveState_TriggerShellTrap(defendingSlot)) {
        return;
    }

    HandlerParam_InterruptPoke* interrupt =
        (HandlerParam_InterruptPoke*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_INTERRUPT_ACTION,
            defendingSlot);
    if (!interrupt) {
        W2U_MoveState_ClearShellTrap(defendingSlot);
        return;
    }

    interrupt->pokeID = (u8)defendingSlot;
    BattleHandler_StrClear(&interrupt->exStr);
    BattleHandler_PopWork(serverFlow, interrupt);
}

extern "C" void HandlerFieldTransientMoveStateDamageReaction(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
#if !defined(W2U_BATTLE_CHILD)
    if (serverFlow && !serverFlow->simulationCounter &&
        !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_DAMAGE) > 0) {
        const u32 attacker = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
        const u32 target = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
        // This native reaction is per strike and includes allies/fatal hits.
        // Confusion, recoil and residual HP work do not emit this payload.
        if (attacker < 24 && attacker != target) RecordPartyMemberDirectHit(target);
    }
#endif
    // The native event dispatcher stops after the first matching event type
    // in a factor's handler table. Keep the two independent reactions behind
    // one table entry so Shell Trap is not shadowed by Beak Blast.
    HandlerFieldTransientMoveStateBeakBlastContact(
        item,
        serverFlow,
        pokemonSlot,
        work);
    HandlerFieldTransientMoveStateShellTrapHit(
        item,
        serverFlow,
        pokemonSlot,
        work);
}

static void ClearPreparedMovesForEventMon()
{
    u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    W2U_MoveState_ClearBeakBlast(currentSlot);
    // Shell Trap is different from an ordinary charge window: once a
    // physical hit reserves the user's action as an interrupt, nested action
    // processing may emit ACTPROC_END before that reserved action is run.
    // Keep its armed/triggered latch until Shell Trap's own move-sequence end
    // (or the switch/faint/turn-end guards below), otherwise the execute check
    // sees an untriggered trap and the preparation pass can replay its setup.
    if (!HasTransientMoveState()) {
        RemoveTransientMoveStateEvent();
    }
}

static void ClearSwitchedOrFaintedTransientState()
{
    const u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
#if !defined(W2U_BATTLE_CHILD)
    sMoveState.statsRaisedThisTurnFlags &= ~SlotMask(currentSlot);
    sMoveState.statsLoweredThisTurnFlags &= ~SlotMask(currentSlot);
    sMoveState.tarShotFlags &= ~SlotMask(currentSlot);
    sMoveState.noRetreatFlags &= ~SlotMask(currentSlot);
    sMoveState.glaiveRushFlags &= ~SlotMask(currentSlot);
    sMoveState.shellSideArmCategoryValidFlags &= ~SlotMask(currentSlot);
    sMoveState.shellSideArmRecordedValidFlags &= ~SlotMask(currentSlot);
    sMoveState.calledDartsFlags &= ~SlotMask(currentSlot);
    if (IsValidSlot(currentSlot)) {
        sMoveState.dragonCheerBoost[currentSlot] = 0;
        sMoveState.lastSuccessfulSelectedMove[currentSlot] = MOVE_NONE;
    }
    for (u32 index = 0; index < 3; ++index) {
        sMoveState.persistentFlags[index] &= ~SlotMask(currentSlot);
        if (index == 1) continue; // Salt Cure does not depend on its source.
        for (u32 target = 0; target < BATTLE_MAX_SLOTS; ++target)
            if (sMoveState.persistentSources[index][target] == currentSlot)
                sMoveState.persistentFlags[index] &= ~SlotMask(target);
    }
#endif
    ClearStompingOutcomeState(currentSlot);
    W2U_MoveState_ClearBeakBlast(currentSlot);
    W2U_MoveState_ClearShellTrap(currentSlot);
    W2U_MoveState_ClearLaserFocus(currentSlot);
    W2U_MoveState_ClearThroatChop(currentSlot);
    if (!HasTransientMoveState()) {
        RemoveTransientMoveStateEvent();
    }
}

extern "C" void HandlerFieldTransientMoveStateActionEnd(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

    const u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    if ((u32)BattleEventVar_GetValue(VAR_ACTION) != W2U_BATTLE_ACTION_FIGHT) {
        SetSlotFlag(sStompingFailureThisTurnFlags, currentSlot, false);
        SetSlotFlag(sStompingProtectedThisMoveFlags, currentSlot, false);
    }
    ClearPreparedMovesForEventMon();
}

extern "C" void HandlerFieldTransientMoveStateMoveSequenceStart(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;

#if !defined(W2U_BATTLE_CHILD)
    if (!serverFlow->simulationCounter)
        sMoveState.shellSideArmCategoryValidFlags &= ~SlotMask((u32)BattleEventVar_GetValue(VAR_ATTACKING_MON));
#endif

    SetSlotFlag(
        sStompingProtectedThisMoveFlags,
        (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON),
        false);
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

    // Native WAZASEQ_END publishes the move user through POKEID/MON_ID; it
    // does not populate POKEID_ATK/ATTACKING_MON. Reading the latter resolves
    // to an unrelated/default slot and can clear another battler's pending
    // state (notably a triggered Shell Trap owned by slot 0).
    const u32 currentSlot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    const u32 currentMask = SlotMask(currentSlot);
#if !defined(W2U_BATTLE_CHILD)
    if (currentMask && serverFlow && !serverFlow->simulationCounter) {
        BattleMon* user = GetBattleMon(serverFlow, currentSlot);
        // Native history has already been updated here. Record the selected
        // move, not a Sleep Talk payload. Failed/inhibited actions clear the
        // rule without altering native counters or last-move bookkeeping.
        sMoveState.lastSuccessfulSelectedMove[currentSlot] =
            user && BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG)
                ? user->previousMove : MOVE_NONE;
    }
#endif
    if (currentMask) {
        const bool moveFailed = !BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG) &&
            !(sStompingProtectedThisMoveFlags & currentMask);
        SetSlotFlag(sStompingFailureThisTurnFlags, currentSlot, moveFailed);
        SetSlotFlag(sStompingProtectedThisMoveFlags, currentSlot, false);
    }
    W2U_MoveState_ClearElectrifiedSlot(currentSlot);
#if !defined(W2U_BATTLE_CHILD)
    sMoveState.shellSideArmCategoryValidFlags &= ~currentMask;
    sMoveState.calledDartsFlags &= ~currentMask;
#endif
    W2U_MoveState_ClearBeakBlast(currentSlot);
    W2U_MoveState_ClearShellTrap(currentSlot);
    sPowderedFlags &= ~SlotMask(currentSlot);
    sSpikyShieldDamagedFlags &= ~SlotMask(currentSlot);
    sBanefulBunkerPoisonedFlags &= ~SlotMask(currentSlot);
    if (!HasTransientMoveState()) {
        RemoveTransientMoveStateEvent();
    }
}

extern "C" void HandlerFieldTransientMoveStateSwitchOrFaint(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    ClearSwitchedOrFaintedTransientState();
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
        W2U_Weather_EndTurn();
        for (u32 slot = 0; slot < BATTLE_MAX_SLOTS; ++slot) {
            BattleMon* battleMon = GetBattleMon(serverFlow, slot);
            if (battleMon && BattleMon_CheckIfMoveCondition(battleMon, CONDITION_SKYDROP)) {
                SetSlotFlag(sStompingFailureThisTurnFlags, slot, false);
            }
        }
        sStompingFailureLastTurnFlags = sStompingFailureThisTurnFlags;
        sStompingFailureThisTurnFlags = 0;
        sStompingProtectedThisMoveFlags = 0;
        ClearEndOfTurnMoveState();
        for (u32 slot = 0; slot < BATTLE_MAX_SLOTS; ++slot) {
            W2U_MoveState_TickLaserFocus(slot);
            if (W2U_MoveState_TickThroatChop(slot)) {
                PushMessageArg(
                    serverFlow,
                    slot,
                    2u,
                    BATTLE_THROAT_CHOP_END_MSGID,
                    slot);
            }
        }
        if (!HasTransientMoveState()) {
            RemoveTransientMoveStateEvent();
        }
    }
}

#if !defined(W2U_BATTLE_CHILD)
static void HandlerFieldAppliedStatHistory(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    (void)item; (void)pokemonSlot; (void)work;
    if (!flow || flow->simulationCounter) return;
    const u32 slot = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    const int volume = BattleEventVar_GetValue(VAR_VOLUME);
    if (!IsValidSlot(slot) || !volume) return;
    (volume > 0 ? sMoveState.statsRaisedThisTurnFlags :
        sMoveState.statsLoweredThisTurnFlags) |= SlotMask(slot);
}

static void HandlerFieldGlaiveRushActionStart(BattleEventItem*, ServerFlow* flow, u32, u32*)
{
    if (!flow->simulationCounter) {
        sMoveState.glaiveRushFlags &= ~SlotMask((u32)BattleEventVar_GetValue(VAR_MON_ID));
        sMoveState.shedTailTransferFlags &= ~SlotMask((u32)BattleEventVar_GetValue(VAR_MON_ID));
    }
}

static void HandlerFieldGlaiveRushAccuracy(BattleEventItem*, ServerFlow*, u32, u32*)
{
    if (sMoveState.glaiveRushFlags & SlotMask((u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)))
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
}

static void HandlerFieldGlaiveRushDamage(BattleEventItem*, ServerFlow*, u32, u32*)
{
    // Only the ordinary native damage calculation emits this ratio phase;
    // fixed damage and OHKO transactions do not receive the multiplier.
    if (sMoveState.glaiveRushFlags & SlotMask((u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)))
        BattleEventVar_MulValue(VAR_RATIO, 8192);
}
#endif

static BattleEventHandlerTableEntry FieldTransientMoveStateHandlers[] = {
#if !defined(W2U_BATTLE_CHILD)
    { EVENT_DEFENDER_GUARD, W2U_Weather_Defense },
    { EVENT_AFTER_WEATHER_CHANGE, W2U_Weather_AfterChange },
    { (BattleEventType)1, HandlerFieldGlaiveRushActionStart },
    { EVENT_SKIP_TARGET_ACCURACY_CHECK, HandlerFieldGlaiveRushAccuracy },
    { EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerFieldGlaiveRushDamage },
    { EVENT_STAT_STAGE_CHANGE_APPLIED, HandlerFieldAppliedStatHistory },
#endif
    { EVENT_ACTION_PROCESSING_END, HandlerFieldTransientMoveStateActionEnd },
    { EVENT_GET_MOVE_PRIORITY, HandlerFieldTransientMoveStateMovePriority },
    { EVENT_MOVE_SEQUENCE_START, HandlerFieldTransientMoveStateMoveSequenceStart },
    { EVENT_MOVE_PARAM, HandlerFieldTransientMoveStateMoveParam },
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerFieldTransientMoveStateMoveExecuteCheck },
    { EVENT_NOEFFECT_CHECK, HandlerFieldTransientMoveStateNativeSideProtection },
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerFieldTransientMoveStateNoEffect },
    { EVENT_PROTECT_SUCCESS, HandlerFieldTransientMoveStateProtectSuccess },
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerFieldTransientMoveStateDamageReaction },
    { EVENT_MOVE_SEQUENCE_END, HandlerFieldTransientMoveStateMoveSequenceEnd },
    { EVENT_SWITCH_OUT_END, HandlerFieldTransientMoveStateSwitchOrFaint },
    { EVENT_NOTIFY_FAINTED, HandlerFieldTransientMoveStateSwitchOrFaint },
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

namespace {

void ClearSpotlightState()
{
    BattleEventItem* item = sMoveState.spotlightItem;
    sMoveState.spotlightItem = 0;
    sMoveState.spotlightTargetParty = 0;
    sMoveState.spotlightTargetSlot = BATTLE_MAX_SLOTS;
    if (item) {
        BattleEventItem_Remove(item);
    }
}

// Propeller Tail / Stalwart: the user's moves are not redirected (the native
// Follow Me / Lightning Rod checks are wrapped in megab2w2/mb_resident.cpp).
bool IgnoresRedirection(BattleMon* attackingMon)
{
    if (!attackingMon) {
        return false;
    }
    const u32 ability = BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY);
    return ability == ABIL_PROPELLER_TAIL || ability == ABIL_STALWART;
}

bool IsSpotlightTargetActive(ServerFlow* serverFlow)
{
    BattleMon* targetMon = GetBattleMon(serverFlow, sMoveState.spotlightTargetSlot);
    return targetMon &&
        !BattleMon_IsFainted(targetMon) &&
        targetMon->partySrc == sMoveState.spotlightTargetParty &&
        Handler_PokeIDToPokePos(serverFlow, sMoveState.spotlightTargetSlot) < W2U_NULL_BATTLE_POS;
}

bool IsSpotlightTargetInRange(ServerFlow* serverFlow, u32 attackingSlot, MOVE_ID moveID)
{
    if (BtlSetup_GetBattleStyle(serverFlow->mainModule) != BTL_STYLE_TRIPLE ||
        getMoveFlag(moveID, MOVE_FLAG_INDEX_TRIPLE_FAR)) {
        return true;
    }

    const u32 attackingPos = Handler_PokeIDToPokePos(serverFlow, attackingSlot);
    const u32 targetPos =
        Handler_PokeIDToPokePos(serverFlow, sMoveState.spotlightTargetSlot);
    // In triples, only the two opposite corner pairs are out of range. Moves
    // carrying the native TripleFar flag were accepted above.
    return !((attackingPos == 0u && targetPos == 1u) ||
        (attackingPos == 1u && targetPos == 0u) ||
        (attackingPos == 4u && targetPos == 5u) ||
        (attackingPos == 5u && targetPos == 4u));
}

} // namespace

extern "C" void HandlerFieldSpotlightRedirect(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (!IsSpotlightTargetActive(serverFlow)) {
        ClearSpotlightState();
        return;
    }

    const u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    const MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!IsValidSlot(attackingSlot) ||
        MainModule_IsAllyMonID(attackingSlot, sMoveState.spotlightTargetSlot) ||
        IgnoresRedirection(GetBattleMon(serverFlow, attackingSlot)) ||
        moveID == MOVE_SKY_DROP ||
        BattleMon_CheckIfMoveCondition(
            GetBattleMon(serverFlow, sMoveState.spotlightTargetSlot), CONDITION_SKYDROP) ||
        !IsSpotlightTargetInRange(serverFlow, attackingSlot, moveID)) {
        return;
    }

    // Native Follow Me, Rage Powder, Storm Drain, and Lightning Rod use a
    // rewrite-once event variable. Spotlight runs last at move priority zero
    // and deliberately adds a fresh value so it supersedes every earlier
    // redirect, including redirection affected by Ally Switch positions.
    BattleEventVar_SetValue(VAR_DEFENDING_MON, (int)sMoveState.spotlightTargetSlot);
}

extern "C" void HandlerFieldSpotlightSwitchOrFaint(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    if ((u32)BattleEventVar_GetValue(VAR_MON_ID) == sMoveState.spotlightTargetSlot) {
        ClearSpotlightState();
    }
}

extern "C" void HandlerFieldSpotlightTurnCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    ClearSpotlightState();
}

BattleEventHandlerTableEntry FieldSpotlightHandlers[] = {
    { EVENT_REDIRECT_TARGET, HandlerFieldSpotlightRedirect },
    { EVENT_SWITCH_OUT_END, HandlerFieldSpotlightSwitchOrFaint },
    { EVENT_NOTIFY_FAINTED, HandlerFieldSpotlightSwitchOrFaint },
    { EVENT_TURN_CHECK_BEGIN, HandlerFieldSpotlightTurnCheck },
};

namespace {

BattleEventItem* AddSpotlightEvent()
{
    return BattleEvent_AddItem(
        EVENTITEM_FIELD,
        W2U_FLDEFF_SPOTLIGHT,
        EVENTPRI_MOVE_DEFAULT,
        0,
        BATTLE_MAX_SLOTS,
        FieldSpotlightHandlers,
        (u16)W2U_ARRAY_COUNT(FieldSpotlightHandlers));
}

} // namespace

extern "C" bool W2U_MoveState_SetSpotlightTarget(
    ServerFlow* serverFlow,
    u32 targetSlot)
{
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (!targetMon || BattleMon_IsFainted(targetMon) ||
        Handler_PokeIDToPokePos(serverFlow, targetSlot) >= W2U_NULL_BATTLE_POS) {
        return false;
    }

    if (!sMoveState.spotlightItem) {
        sMoveState.spotlightItem = AddSpotlightEvent();
        if (!sMoveState.spotlightItem) {
            return false;
        }
    }

    // A later Spotlight replaces the earlier target. Party identity guards
    // against accidentally carrying the state to a replacement battler.
    sMoveState.spotlightTargetSlot = (u8)targetSlot;
    sMoveState.spotlightTargetParty = targetMon->partySrc;
    return true;
}

extern "C" void HandlerEncoreShellTrapAware(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* target = GetBattleMon(serverFlow, targetSlot);
    if (W2U_MoveState_IsShellTrapWaiting(targetSlot) ||
        (target && (BattleMon_GetPreviousMove(target) == MOVE_DYNAMAX_CANNON ||
                    W2U_MoveIsRestrictedNpcAttack(BattleMon_GetPreviousMove(target))))) {
        // Leaving the handler-extension result empty makes the normal
        // uncategorized-move path display "But it failed!".
        return;
    }

    // Reuse the reviewed native getter service rather than retaining another
    // copy of the game's table scan in the resident core.
    W2UNativeMoveGetter getter = W2U_FindNativeMoveGetter(MOVE_ENCORE);
    u32 handlerCount = 0;
    BattleEventHandlerTableEntry* handlers = getter ? getter(&handlerCount) : 0;
    for (u32 idx = 0; handlers && idx < handlerCount; ++idx) {
        if (handlers[idx].eventType == EVENT_UNCATEGORIZED_MOVE && handlers[idx].handler) {
            handlers[idx].handler(item, serverFlow, pokemonSlot, work);
            return;
        }
    }
}

BattleEventHandlerTableEntry ShellTrapAwareEncoreHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerEncoreShellTrapAware },
};

BattleEventHandlerTableEntry* EventAddShellTrapAwareEncore(u32* handlerAmount)
{
    if (handlerAmount) {
        *handlerAmount = W2U_ARRAY_COUNT(ShellTrapAwareEncoreHandlers);
    }
    return ShellTrapAwareEncoreHandlers;
}

static void HandlerNativeCopyRestricted(
    BattleEventItem* item, ServerFlow* flow, u32 pokemonSlot, u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        !BattleEventVar_GetValue(VAR_TARGET_COUNT)) return;
    BattleMon* target = GetBattleMon(flow, (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID));
    if (target && GetEventItemMove(item) == MOVE_SKETCH &&
        (BattleMon_GetPreviousMove(target) == MOVE_REVIVAL_BLESSING ||
         BattleMon_GetPreviousMoveID(target) == MOVE_REVIVAL_BLESSING)) return;
    if (target && (W2U_MoveIsRestrictedNpcAttack(BattleMon_GetPreviousMove(target)) ||
                   W2U_MoveIsRestrictedNpcAttack(BattleMon_GetPreviousMoveID(target)))) return;
    W2UNativeMoveGetter getter = W2U_FindNativeMoveGetter(GetEventItemMove(item));
    u32 count = 0;
    BattleEventHandlerTableEntry* handlers = getter ? getter(&count) : 0;
    for (u32 i = 0; handlers && i < count; ++i) {
        if (handlers[i].eventType == EVENT_UNCATEGORIZED_MOVE && handlers[i].handler) {
            handlers[i].handler(item, flow, pokemonSlot, work);
            return;
        }
    }
}

static BattleEventHandlerTableEntry NativeCopyRestrictedHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerNativeCopyRestricted },
};

static void HandlerPsychUpCritical(BattleEventItem* item, ServerFlow* flow, u32 slot, u32* work)
{
    if (slot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) || !BattleEventVar_GetValue(VAR_TARGET_COUNT)) return;
    W2UNativeMoveGetter getter = W2U_FindNativeMoveGetter(MOVE_PSYCH_UP);
    u32 count = 0;
    BattleEventHandlerTableEntry* table = getter ? getter(&count) : 0;
    for (u32 i = 0; table && i < count; ++i)
        if (table[i].eventType == EVENT_UNCATEGORIZED_MOVE) table[i].handler(item, flow, slot, work);
    BattleMon* user = GetBattleMon(flow, slot);
    BattleMon* target = GetBattleMon(flow, (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID));
    if (user && target && BattleMon_GetConditionFlag(target, 9)) {
        ServerDisplay_SetConditionFlag(flow, user, 9);
        W2U_CopyCriticalBoost(user, target);
        BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
    } else if (user && target) {
        ServerDisplay_ResetConditionFlag(flow, user, 9);
        W2U_CopyCriticalBoost(user, target);
    }
}

static BattleEventHandlerTableEntry PsychUpCriticalHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerPsychUpCritical },
};
#endif

#if !defined(W2U_DYNAMIC_BATTLE_CORE)
extern "C" void HandlerBeakBlastAttackAnimation(
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

    // The normal -3 priority action supplies the target and damage timing.
    // Select effect index 1 so it plays Beak Blast's attack script; move-VM
    // variant 0 was queued separately during the early charge phase above.
    HandlerParam_SetAnimationID* animation =
        (HandlerParam_SetAnimationID*)BattleHandler_PushWork(
            serverFlow,
            EFFECT_SET_ANIMATION_ID,
            pokemonSlot);
    if (!animation) {
        return;
    }
    animation->effectIndex = 1;
    BattleHandler_PopWork(serverFlow, animation);
}

BattleEventHandlerTableEntry BeakBlastHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerBeakBlastAttackAnimation },
};


extern "C" void HandlerShellTrapExecuteCheck(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_MON_ID) &&
        !W2U_MoveState_IsShellTrapTriggered(pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
    }
}

BattleEventHandlerTableEntry ShellTrapHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerShellTrapExecuteCheck },
};


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
        if (W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
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


extern "C" void HandlerLaserFocusStart(
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

    if (!W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }
    W2U_MoveState_StartLaserFocus(pokemonSlot);
    PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_LASER_FOCUS_MSGID, pokemonSlot);
}

BattleEventHandlerTableEntry LaserFocusHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerLaserFocusStart },
};


extern "C" void HandlerThroatChop(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_THROAT_CHOP ||
        BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) ||
        BattleEventVar_GetValue(VAR_SHIELD_DUST_FLAG)) {
        return;
    }

    BattleMon* attackingMon = GetBattleMon(serverFlow, pokemonSlot);
    if (attackingMon &&
        BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL_SHEER_FORCE) {
        return;
    }

    // DAMAGE_REACTION_1 exposes the battler that actually took this hit as
    // DEFENDING_MON. Applying here makes the restriction visible before the
    // battle server begins the next queued action in the same turn.
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (!targetMon || BattleMon_IsFainted(targetMon) ||
        W2U_MoveState_IsThroatChopped(targetSlot)) {
        return;
    }

    if (W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
        W2U_MoveState_StartThroatChop(targetSlot);
    }
}

BattleEventHandlerTableEntry ThroatChopHandlers[] = {
    { EVENT_MOVE_DAMAGE_REACTION_1, HandlerThroatChop },
};


extern "C" void HandlerProtectLikeShield(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    MOVE_ID moveID = GetEventItemMove(item);
    if (moveID == MOVE_BANEFUL_BUNKER) {
        if (W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
            sBanefulBunkerFlags |= SlotMask(pokemonSlot);
        }
    } else if (moveID == MOVE_SPIKY_SHIELD) {
        if (W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
            sSpikyShieldFlags |= SlotMask(pokemonSlot);
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

// Damage-only shields keep their callbacks in this module. The native
// position event's work words carry IDs, never pointers or shared layouts.
static void HandlerPosDamageShieldStatus(
    BattleEventItem*, ServerFlow*, u32, u32* work)
{
    if (work[1] == (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) &&
        BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == SPLIT_STATUS &&
        BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG) == 0) {
        // 2 bypasses Protect without breaking it; Feint's 1 takes precedence.
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 2);
    }
}

static void HandlerPosDamageShieldSequenceStart(
    BattleEventItem*, ServerFlow*, u32, u32* work)
{
    work[2] = (u32)BattleEventVar_GetValue(VAR_MOVE_ID) |
        ((u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) << 16);
}

static void HandlerPosDamageShieldSequenceEnd(
    BattleEventItem*, ServerFlow*, u32, u32* work)
{
    work[2] = 0;
}

static void HandlerPosDamageShieldTypeImmunity(
    BattleEventItem*, ServerFlow* serverFlow, u32, u32* work)
{
    const u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    const MOVE_ID moveID = (MOVE_ID)(work[2] & 0xFFFFu);
    if (work[1] != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) ||
        attackingSlot != (work[2] >> 16) || !moveID ||
        GetTypeEffectiveness((u32)BattleEventVar_GetValue(VAR_MOVE_TYPE),
            (u32)BattleEventVar_GetValue(VAR_POKE_TYPE)) != RESULT_NOT_EFFECTIVE ||
        !getMoveFlag(moveID, MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT)) {
        return;
    }
    BattleMon* protectedMon = GetBattleMon(serverFlow, work[1]);
    if (protectedMon && BattleMon_GetTurnFlag(protectedMon, TURNFLAG_PROTECT) &&
        W2U_CheckProtectBreak(serverFlow, attackingSlot, work[1], PML_MoveGetCategory(moveID), moveID) == 0) {
        // Native BW2 discards type-immune targets before its protection pass.
        // Keep this *blocked* target until that pass emits PROTECT_SUCCESS;
        // no damaging calculation can use the temporary immunity override.
        // Bypass moves keep their real immunity and never retaliate.
        BattleEventVar_RewriteValue(VAR_NO_TYPE_EFFECTIVENESS, 1);
    }
}

static void HandlerPosDamageShieldContact(
    BattleEventItem*, ServerFlow* serverFlow, u32, u32* work)
{
    if (IsNotNewEvent() ||
        work[1] != (u32)BattleEventVar_GetValue(NEW_VAR_DEFENDING_MON)) {
        return;
    }
    const u32 attackingSlot = (u32)BattleEventVar_GetValue(NEW_VAR_ATTACKING_MON);
    const MOVE_ID incomingMove = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!IsValidSlot(attackingSlot) ||
        !W2U_MoveMakesContact(serverFlow, incomingMove, attackingSlot)) {
        return;
    }
    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (!attackingMon || BattleMon_IsFainted(attackingMon)) {
        return;
    }
    if (work[0] == MOVE_BURNING_BULWARK) {
        HandlerParam_AddCondition* burn = (HandlerParam_AddCondition*)
            BattleHandler_PushWork(serverFlow, EFFECT_ADD_CONDITION, work[1]);
        burn->condition = CONDITION_BURN;
        burn->condData = MakeBasicStatus(CONDITION_BURN);
        burn->pokeID = (u8)attackingSlot;
        burn->almost = 0;
        BattleHandler_PopWork(serverFlow, burn);
    } else {
        const StatStage stat = work[0] == MOVE_OBSTRUCT ? STATSTAGE_DEFENSE :
            work[0] == MOVE_SILK_TRAP ? STATSTAGE_SPEED : STATSTAGE_ATTACK;
        const s8 stages = work[0] == MOVE_SILK_TRAP ? -1 : -2;
        // Native stat work applies Contrary/Simple and ability prevention.
        ApplyStatChange(serverFlow, work[1], attackingSlot, stat, stages, true);
    }
}

static void HandlerPosDamageShieldEnd(
    BattleEventItem* item, ServerFlow*, u32, u32*)
{
    if (BattleEventVar_GetValue(VAR_MON_ID) == BATTLE_MAX_SLOTS) {
        BattleEventItem_Remove(item);
    }
}

static void HandlerPosDamageShieldBroken(
    BattleEventItem* item, ServerFlow*, u32, u32* work)
{
    if (!IsNotNewEvent() &&
        work[1] == (u32)BattleEventVar_GetValue(NEW_VAR_DEFENDING_MON)) {
        BattleEventItem_Remove(item);
    }
}

static void HandlerPosDamageShieldSwitchOut(
    BattleEventItem* item, ServerFlow*, u32, u32* work)
{
    if (work[1] == (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        BattleEventItem_Remove(item);
    }
}

static BattleEventHandlerTableEntry PosDamageShieldHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerPosDamageShieldSequenceStart },
    { EVENT_MOVE_SEQUENCE_END, HandlerPosDamageShieldSequenceEnd },
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerPosDamageShieldTypeImmunity },
    { EVENT_CHECK_PROTECT_BREAK, HandlerPosDamageShieldStatus },
    { EVENT_PROTECT_SUCCESS, HandlerPosDamageShieldContact },
    { EVENT_PROTECT_BROKEN, HandlerPosDamageShieldBroken },
    { EVENT_TURN_CHECK_DONE, HandlerPosDamageShieldEnd },
    { EVENT_SWITCH_OUT_END, HandlerPosDamageShieldSwitchOut },
};

static void HandlerDamageShieldStart(
    BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        StartProtectCounterMove(serverFlow, pokemonSlot);
    }
}

static void HandlerDamageShield(
    BattleEventItem* moveItem, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }
    // Register directly: these transient position events do not occupy the
    // native five-entry persistent PosEffect storage. Failure must not grant
    // a shield with unavailable retaliation/status-filter callbacks.
    BattleEventItem* shield = BattleEvent_AddItem(EVENTITEM_POS,
        POSEFF_DAMAGE_SHIELD, EVENTPRI_POS_DEFAULT, 0,
        Handler_PokeIDToPokePos(serverFlow, pokemonSlot),
        PosDamageShieldHandlers, sizeof(PosDamageShieldHandlers) / sizeof(*PosDamageShieldHandlers));
    if (!shield) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }
    BattleEventItem_SetWorkValue(shield, 0, GetEventItemMove(moveItem));
    BattleEventItem_SetWorkValue(shield, 1, pokemonSlot);
    BattleEventItem_SetWorkValue(shield, 2, 0);
    HandlerProtect(moveItem, serverFlow, pokemonSlot, work);
}

static BattleEventHandlerTableEntry DamageShieldHandlers[] = {
    { EVENT_MOVE_SEQUENCE_START, HandlerDamageShieldStart },
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerProtectCheckFail },
    { EVENT_MOVE_EXECUTE_FAIL, HandlerProtectResetCounter },
    { EVENT_UNCATEGORIZED_MOVE, HandlerDamageShield },
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
    { EVENT_UNCATEGORIZED_MOVE_NO_TARGET, HandlerHappyHour },
};


extern "C" void HandlerFirstImpressionCheckFail(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_MON_ID)) {
        return;
    }

    BattleMon* battleMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!battleMon || battleMon->turnCount != 0) {
        BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_OTHER);
    }
}

BattleEventHandlerTableEntry FirstImpressionHandlers[] = {
    { EVENT_MOVE_EXECUTE_CHECK2, HandlerFirstImpressionCheckFail },
};


static void HandlerUpperHandEligibility(
    BattleEventItem*, ServerFlow* flow, u32 pokemonSlot, u32*)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    MOVE_ID pending = MOVE_NONE;
    int priority = 0;
    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    if ((!W2U_ExtraAction_GetPendingMovePriority(flow, targetSlot, &pending, &priority) ||
         priority < 1 || priority > 3 || !PML_MoveIsDamaging(pending)) &&
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1)) {
        HandlerParam_StrParams* message = (HandlerParam_StrParams*)BattleEventVar_GetValue(VAR_WORK_ADDRESS);
        if (message) BattleHandler_StrSetup(message, 1u, 71u);
    }
}

static BattleEventHandlerTableEntry UpperHandHandlers[] = {
    { EVENT_NOEFFECT_CHECK, HandlerUpperHandEligibility },
};

static bool IsInstructForbiddenMove(MOVE_ID moveID)
{
    if (W2U_MoveIsRestrictedNpcAttack(moveID)) return true;
    if (moveID == MOVE_NONE ||
        getMoveFlag(moveID, MOVE_FLAG_INDEX_REQUIRES_CHARGE) ||
        getMoveFlag(moveID, MOVE_FLAG_INDEX_RECHARGE_TURN)) {
        return true;
    }

    switch (moveID) {
    case MOVE_INSTRUCT:
    case MOVE_BIDE:
    case MOVE_FOCUS_PUNCH:
    case MOVE_BEAK_BLAST:
    case MOVE_SHELL_TRAP:
    case MOVE_SKETCH:
    case MOVE_TRANSFORM:
    case MOVE_MIMIC:
    case MOVE_KINGS_SHIELD:
    case MOVE_STRUGGLE:
    case MOVE_OBSTRUCT:
        // Moves that call another move do not have a common engine flag.
    case MOVE_METRONOME:
    case MOVE_ASSIST:
    case MOVE_COPYCAT:
    case MOVE_ME_FIRST:
    case MOVE_MIRROR_MOVE:
    case MOVE_NATURE_POWER:
    case MOVE_SLEEP_TALK:
        // Multi-turn moves that lock the user into consecutive actions.
    case MOVE_ROLLOUT:
    case MOVE_ICE_BALL:
    case MOVE_OUTRAGE:
    case MOVE_RAGING_FURY:
    case MOVE_PETAL_DANCE:
    case MOVE_THRASH:
    case MOVE_UPROAR:
        return true;
    default:
        return false;
    }
}

static bool CanInstructTarget(
    ServerFlow* serverFlow,
    u32 targetSlot,
    MOVE_ID* instructedMove,
    u32* instructedTargetPos)
{
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (!targetMon || BattleMon_IsFainted(targetMon) ||
        BattleMon_CheckIfMoveCondition(targetMon, CONDITION_SKYDROP) ||
        BattleMon_CheckIfMoveCondition(targetMon, CONDITION_MOVELOCK) ||
        BattleMon_CheckIfMoveCondition(targetMon, CONDITION_CHARGELOCK) ||
        W2U_MoveState_IsBeakBlastCharging(targetSlot)) {
        return false;
    }

    MOVE_ID pendingMove = W2U_ExtraAction_GetPendingMove(serverFlow, targetSlot);
    if (pendingMove == MOVE_BIDE || pendingMove == MOVE_FOCUS_PUNCH ||
        pendingMove == MOVE_BEAK_BLAST || pendingMove == MOVE_SHELL_TRAP) {
        return false;
    }

    MOVE_ID moveID = MOVE_NONE;
    u32 targetPos = W2U_NULL_BATTLE_POS;
    if (!W2U_ExtraAction_GetLastMove(serverFlow, targetSlot, &moveID, &targetPos) ||
        IsInstructForbiddenMove(moveID) ||
        !W2U_ExtraAction_HasMoveWithPP(serverFlow, targetSlot, moveID)) {
        return false;
    }

    if (instructedMove) {
        *instructedMove = moveID;
    }
    if (instructedTargetPos) {
        *instructedTargetPos = targetPos;
    }
    return true;
}

extern "C" void HandlerInstructExecute(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    MOVE_ID moveID = MOVE_NONE;
    u32 targetPos = W2U_NULL_BATTLE_POS;
    if (CanInstructTarget(serverFlow, targetSlot, &moveID, &targetPos) &&
        W2U_ExtraAction_QueueInstruct(serverFlow, targetSlot, moveID, targetPos)) {
        // An uncategorized status move is considered successful only if its
        // handler enqueues an engine effect.  This message both matches
        // Instruct's visible cue and prevents the generic "But it failed!"
        // fallback before the immediate extra action is processed.
        PushMessageArg(serverFlow, pokemonSlot, 2u, BATTLE_INSTRUCT_MSGID, targetSlot);
    }
}

BattleEventHandlerTableEntry InstructHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerInstructExecute },
};


static void HandlerSpotlightExecute(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    if (W2U_MoveState_SetSpotlightTarget(serverFlow, targetSlot)) {
        // Reuse Follow Me's existing three-way message set. The target is the
        // actor here because Spotlight places it, rather than the user, at
        // the center of attention.
        PushMessageArg(
            serverFlow,
            targetSlot,
            2u,
            BATTLE_SPOTLIGHT_MSGID,
            targetSlot);
    }
}

BattleEventHandlerTableEntry SpotlightHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerSpotlightExecute },
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


static void HandlerSpeedSwap(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* userMon = GetBattleMon(serverFlow, pokemonSlot);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (!userMon || !targetMon || BattleMon_IsFainted(userMon) ||
        BattleMon_IsFainted(targetMon)) {
        return;
    }

    // GetRealStat returns the stored stat before rank, ability, item, status,
    // field, and other battle modifiers. Queue both writes through the native
    // set-status effect so the server and battle client remain synchronized.
    const u16 userSpeed = (u16)BattleMon_GetRealStat(userMon, VALUE_SPEED_STAT);
    const u16 targetSpeed = (u16)BattleMon_GetRealStat(targetMon, VALUE_SPEED_STAT);
    const u8 speedEnableFlag = 1u << 4;

    HandlerParam_SetBaseStats* setTarget =
        (HandlerParam_SetBaseStats*)BattleHandler_PushWork(
            serverFlow, EFFECT_SET_BASE_STATS, pokemonSlot);
    setTarget->speed = userSpeed;
    setTarget->pokeID = (u8)targetSlot;
    setTarget->enableFlags = speedEnableFlag;
    BattleHandler_PopWork(serverFlow, setTarget);

    HandlerParam_SetBaseStats* setUser =
        (HandlerParam_SetBaseStats*)BattleHandler_PushWork(
            serverFlow, EFFECT_SET_BASE_STATS, pokemonSlot);
    setUser->speed = targetSpeed;
    setUser->pokeID = (u8)pokemonSlot;
    setUser->enableFlags = speedEnableFlag;
    BattleHandler_StrSetup(&setUser->exStr, 2u, BATTLE_SPEED_SWAP_MSGID);
    BattleHandler_AddArg(&setUser->exStr, pokemonSlot);
    BattleHandler_PopWork(serverFlow, setUser);
}

BattleEventHandlerTableEntry SpeedSwapHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerSpeedSwap },
};


static void HandlerStrengthSap(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_TARGET_MON_ID);
    BattleMon* userMon = GetBattleMon(serverFlow, pokemonSlot);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    if (!userMon || !targetMon || BattleMon_IsFainted(userMon) ||
        BattleMon_IsFainted(targetMon)) {
        return;
    }

    // Strength Sap's only intrinsic failure condition is an Attack stage that
    // is already at -6. In particular, do not use IsStatChangeValid here:
    // Mist, Hyper Cutter, Contrary at +6, and similar blockers stop only the
    // stat drop and must not prevent the drain attempt.
    if ((s8)BattleMon_GetValue(targetMon, VALUE_ATTACK_STAGE) == 0) {
        return;
    }

    // Capture the stage-adjusted Attack before applying the drop. This is the
    // battle stat itself, excluding separate ability/item damage multipliers.
    const u16 recoverHP = (u16)BattleMon_GetValue(targetMon, VALUE_ATTACK_STAT);

    ApplyStatChange(
        serverFlow,
        pokemonSlot,
        targetSlot,
        STATSTAGE_ATTACK,
        -1,
        true);

    // Native drain processing supplies Big Root and Liquid Ooze behavior and
    // caps ordinary recovery at the user's missing HP. damageSourceSlot is kept
    // as the target so Liquid Ooze can identify whose ability reverses it.
    HandlerParam_Drain* drain =
        (HandlerParam_Drain*)BattleHandler_PushWork(
            serverFlow, EFFECT_DRAIN, pokemonSlot);
    drain->recoverHP = recoverHP;
    drain->recipientSlot = (u8)pokemonSlot;
    drain->damageSourceSlot = (u8)targetSlot;
    BattleHandler_StrSetup(&drain->exStr, 2u, 387u);
    BattleHandler_AddArg(&drain->exStr, pokemonSlot);
    BattleHandler_PopWork(serverFlow, drain);

    // If the stat drop is blocked and recovery is unnecessary, the move still
    // succeeded. Prevent the uncategorized-move dispatcher from adding a
    // misleading generic failure message in that case.
    BattleHandler_PushRun(serverFlow, EFFECT_FORCE_MOVE_SUCCESS, pokemonSlot);
}

BattleEventHandlerTableEntry StrengthSapHandlers[] = {
    { EVENT_UNCATEGORIZED_MOVE, HandlerStrengthSap },
};


static void HandlerDarkestLariatIgnoreDefense(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        // Request the defender's unmodified base Defense.  Later modifiers,
        // including Reflect and ability/field multipliers, still apply.
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

static void HandlerDarkestLariatIgnoreEvasion(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)work;
    if (pokemonSlot == (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        // Neutralize only the defender's Evasion stage; the attacker's
        // Accuracy stage remains part of the hit calculation.
        BattleEventVar_RewriteValue(VAR_FLAT_FLAG, 1);
    }
}

BattleEventHandlerTableEntry DarkestLariatHandlers[] = {
    { EVENT_BEFORE_DEFENDER_GUARD, HandlerDarkestLariatIgnoreDefense },
    { EVENT_MOVE_ACCURACY_STAGE, HandlerDarkestLariatIgnoreEvasion },
};


static void HandlerFreezyFrost(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) {
        return;
    }

    // Freezy Frost deals damage normally, then applies Haze to every active
    // battler. Calling the native handler preserves Haze's target expansion
    // and standard stat-reset message without replacing the damaging move's
    // normal execution path.
    W2UNativeMoveGetter getter = W2U_FindNativeMoveGetter(MOVE_HAZE);
    u32 handlerCount = 0;
    BattleEventHandlerTableEntry* handlers = getter ? getter(&handlerCount) : 0;
    for (u32 idx = 0; handlers && idx < handlerCount; ++idx) {
        if (handlers[idx].eventType == EVENT_CALL_FIELD_EFFECT && handlers[idx].handler) {
            handlers[idx].handler(item, serverFlow, pokemonSlot, work);
            return;
        }
    }
}

BattleEventHandlerTableEntry FreezyFrostHandlers[] = {
    { EVENT_MOVE_DAMAGE_SIDE_AFTER, HandlerFreezyFrost },
};


static s8 SpectralThiefResetStage(BattleMon* targetMon, BattleMonValue stage)
{
    const s8 value = (s8)BattleMon_GetValue(targetMon, stage);
    return value > 6 ? 6 : value;
}

static void HandlerSpectralThief(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)work;
    if (!serverFlow || serverFlow->simulationCounter != 0 ||
        pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_SPECTRAL_THIEF) {
        return;
    }

    const u32 targetSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
    BattleMon* attackingMon = GetBattleMon(serverFlow, pokemonSlot);
    if (!targetMon || !attackingMon || BattleMon_IsFainted(targetMon) ||
        BattleMon_IsFainted(attackingMon)) {
        return;
    }

    static const BattleMonValue stageValues[] = {
        VALUE_ATTACK_STAGE,
        VALUE_DEFENSE_STAGE,
        VALUE_SPECIAL_ATTACK_STAGE,
        VALUE_SPECIAL_DEFENSE_STAGE,
        VALUE_SPEED_STAGE,
        VALUE_ACCURACY_STAGE,
        VALUE_EVASION_STAGE,
    };
    static const StatStage statStages[] = {
        STATSTAGE_ATTACK,
        STATSTAGE_DEFENSE,
        STATSTAGE_SPECIAL_ATTACK,
        STATSTAGE_SPECIAL_DEFENSE,
        STATSTAGE_SPEED,
        STATSTAGE_ACCURACY,
        STATSTAGE_EVASION,
    };

    s8 stolenStages[W2U_ARRAY_COUNT(stageValues)];
    bool hasBoost = false;
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(stageValues); ++idx) {
        const s8 value = (s8)BattleMon_GetValue(targetMon, stageValues[idx]);
        stolenStages[idx] = value > 6 ? (s8)(value - 6) : 0;
        hasBoost = hasBoost || stolenStages[idx] != 0;
    }
    if (!hasBoost) {
        return;
    }

    // The native move effect owns a queue position reserved before damage
    // processing. Select Spectral Thief's internal no-op variant for that
    // reserved command, then append the conditional cue, message, and real
    // attack in their required order. With no boosts, the ordinary command
    // remains variant 0 and plays the main animation exactly once.
    // Me First already animates energy travelling from defender to attacker.
    if (serverFlow->serverCommandQueue) {
        const u32 attackingPos = Handler_PokeIDToPokePos(serverFlow, pokemonSlot);
        const u32 targetPos = Handler_PokeIDToPokePos(serverFlow, targetSlot);
        if (attackingPos < W2U_NULL_BATTLE_POS && targetPos < W2U_NULL_BATTLE_POS) {
            HandlerParam_SetAnimationID* reservedAnimation =
                (HandlerParam_SetAnimationID*)BattleHandler_PushWork(
                    serverFlow,
                    EFFECT_SET_ANIMATION_ID,
                    pokemonSlot);
            if (reservedAnimation) {
                reservedAnimation->effectIndex = 2u;
                BattleHandler_PopWork(serverFlow, reservedAnimation);
                ServerDisplay_AddCommon(
                    serverFlow->serverCommandQueue,
                    SCID_MoveAnim,
                    attackingPos,
                    targetPos,
                    MOVE_ME_FIRST,
                    0u);
                // Use the direct display command so the message stays between
                // the two directly queued animations; handler-effect messages
                // are flushed after the current event finishes.
                ServerDisplay_AddMessageImpl(
                    serverFlow->serverCommandQueue,
                    SCID_SetMessage,
                    BATTLE_SPECTRAL_THIEF_STEAL_MSGID,
                    targetSlot,
                    0xFFFF0000u);
                ServerDisplay_AddCommon(
                    serverFlow->serverCommandQueue,
                    SCID_MoveAnim,
                    attackingPos,
                    targetPos,
                    MOVE_SPECTRAL_THIEF,
                    0u);
            }
        }
    }

    // Absolute stage assignment is intentional: stealing boosts is not a stat
    // drop, so Clear Body, White Smoke, Hyper Cutter, Defiant, and similar
    // effects must not intercept the target's reset.
    HandlerParam_SetStatStage* resetTarget =
        (HandlerParam_SetStatStage*)BattleHandler_PushWork(
            serverFlow, EFFECT_SET_STAT_STAGE, pokemonSlot);
    resetTarget->pokeID = (u8)targetSlot;
    resetTarget->attack = SpectralThiefResetStage(targetMon, VALUE_ATTACK_STAGE);
    resetTarget->defense = SpectralThiefResetStage(targetMon, VALUE_DEFENSE_STAGE);
    resetTarget->specialAttack = SpectralThiefResetStage(targetMon, VALUE_SPECIAL_ATTACK_STAGE);
    resetTarget->specialDefense = SpectralThiefResetStage(targetMon, VALUE_SPECIAL_DEFENSE_STAGE);
    resetTarget->speed = SpectralThiefResetStage(targetMon, VALUE_SPEED_STAGE);
    resetTarget->accuracy = SpectralThiefResetStage(targetMon, VALUE_ACCURACY_STAGE);
    resetTarget->evasion = SpectralThiefResetStage(targetMon, VALUE_EVASION_STAGE);
    BattleHandler_PopWork(serverFlow, resetTarget);

    // Apply the stolen volumes through the normal rank-effect path. This lets
    // the user's Simple double them and Contrary reverse them while normal
    // stage limits cap only the user; the target has already lost every boost.
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(statStages); ++idx) {
        if (stolenStages[idx] != 0) {
            ApplyStatChange(
                serverFlow,
                pokemonSlot,
                pokemonSlot,
                statStages[idx],
                stolenStages[idx],
                false);
        }
    }
}

BattleEventHandlerTableEntry SpectralThiefHandlers[] = {
    // This point is after hit/no-effect checks but before Attack and Defense
    // are read, so stolen offensive stages affect Spectral Thief's own damage.
    { EVENT_MOVE_DAMAGE_PROCESSING_1, HandlerSpectralThief },
};


extern "C" void HandlerPowder(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)work;
    if (pokemonSlot != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON) ||
        BattleEventVar_GetValue(VAR_TARGET_COUNT) == 0) {
        return;
    }

    if (!W2U_MoveState_EnsureTransientEvent(pokemonSlot)) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        return;
    }

    bool covered = false;
    u32 targetCount = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 idx = 0; idx < targetCount; ++idx) {
        u32 targetSlot = (u32)BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + idx));
        BattleMon* targetMon = GetBattleMon(serverFlow, targetSlot);
        if (targetMon && !BattleMon_IsFainted(targetMon)) {
            sPowderedFlags |= SlotMask(targetSlot);
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
        (terrain == TERRAIN_GRASSY && moveType == TYPE_GRASS) ||
        (terrain == TERRAIN_PSYCHIC && moveType == TYPE_PSYCHIC)) {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, W2U_TERRAIN_POWER_RATIO);
    }

    // Move-specific terrain multipliers belong to their on-demand handlers.
}

extern "C" void HandlerPsychicTerrainPriorityGuard(
    BattleEventItem* item,
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32* work)
{
    (void)item;
    (void)pokemonSlot;
    (void)work;
    if (!IsTerrainActive(TERRAIN_PSYCHIC)) {
        return;
    }

    u32 defendingSlot = (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON);
    u32 attackingSlot = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    if (defendingSlot == attackingSlot || MainModule_IsAllyMonID(attackingSlot, defendingSlot)) {
        return;
    }

    BattleMon* defendingMon = GetBattleMon(serverFlow, defendingSlot);
    BattleMon* attackingMon = GetBattleMon(serverFlow, attackingSlot);
    if (IsGrounded(serverFlow, defendingMon) &&
        W2U_GetQueuedMovePriority(serverFlow, attackingMon) > 0) {
        BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
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
    if (BattleEventVar_GetValue(VAR_MON_ID) != BATTLE_MAX_SLOTS || !sTerrainActive) {
        return;
    }

    if (sTerrainTurns > 0) {
        --sTerrainTurns;
    }
    if (sTerrainTurns == 0) {
        W2U_MoveState_RemoveTerrain(serverFlow);
    }
}

BattleEventHandlerTableEntry FieldTerrainHandlers[] = {
    { EVENT_ADD_CONDITION_CHECK_FAIL, HandlerTerrainPreventStatus },
    { EVENT_ADD_CONDITION_FAIL, HandlerTerrainStatusFailMessage },
    { EVENT_TURN_CHECK_BEGIN, HandlerGrassyTerrainHeal },
    { EVENT_RECOVER_HP, HandlerFloralHealingRatio },
    { EVENT_MOVE_BASE_POWER, HandlerGrassyTerrainQuakeMoves },
    { EVENT_MOVE_POWER, HandlerTerrainPower },
    { EVENT_ABILITY_CHECK_NO_EFFECT, HandlerPsychicTerrainPriorityGuard },
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
#endif

#if defined(W2U_DYNAMIC_BATTLE_CORE)
namespace {

BattleEventItem* AddTerrainEvent(u32 pokemonSlot)
{
    const W2UBattleHandlerExport* entry =
        W2U_BattleModules_FindLoaded(W2U_MECHANIC_FIELD, FLDEFF_TERRAIN);
    if (!entry) {
        return 0;
    }
    return BattleEvent_AddItem(
        EVENTITEM_FIELD,
        FLDEFF_TERRAIN,
        entry->priority == W2U_BATTLE_MODULE_DEFAULT_PRIORITY
            ? EVENTPRI_FIELD_DEFAULT
            : (BattleEventPriority)entry->priority,
        0,
        pokemonSlot,
        entry->handlers,
        entry->handlerCount);
}
#endif

#if !defined(W2U_DYNAMIC_BATTLE_CORE) && !defined(W2U_BATTLE_STATIC_GROUPS)
#define W2U_MOVE_EVENT(move, handlers) { (u16)W2U_ARRAY_COUNT(handlers), (u16)move, handlers }
#define W2U_POS_EVENT(posEffect, handlers, priority) \
    { (u8)W2U_ARRAY_COUNT(handlers), (u8)priority, (u16)posEffect, handlers }

const W2UMoveEventAddTable W2U_MOVE_EVENT_ADD_TABLE[] = {
    W2U_MOVE_EVENT(MOVE_RAPID_SPIN, RapidSpinHandlers),
    W2U_MOVE_EVENT(MOVE_DEFOG, DefogHandlers),
    W2U_MOVE_EVENT(MOVE_FLYING_PRESS, FlyingPressHandlers),
    W2U_MOVE_EVENT(MOVE_MAGIC_POWDER, MagicPowderHandlers),
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
    W2U_MOVE_EVENT(MOVE_BANEFUL_BUNKER, ProtectLikeShieldHandlers),
    W2U_MOVE_EVENT(MOVE_VENOM_DRENCH, VenomDrenchHandlers),
    W2U_MOVE_EVENT(MOVE_POWDER, PowderHandlers),
    W2U_MOVE_EVENT(MOVE_GEOMANCY, GeomancyHandlers),
    W2U_MOVE_EVENT(MOVE_MAGNETIC_FLUX, MagneticFluxHandlers),
    W2U_MOVE_EVENT(MOVE_HAPPY_HOUR, HappyHourHandlers),
    W2U_MOVE_EVENT(MOVE_ELECTRIFY, ElectrifyHandlers),
    W2U_MOVE_EVENT(MOVE_KINGS_SHIELD, ProtectLikeShieldHandlers),
    W2U_MOVE_EVENT(MOVE_ELECTRIC_TERRAIN, ElectricTerrainHandlers),
    W2U_MOVE_EVENT(MOVE_PSYCHIC_TERRAIN, PsychicTerrainHandlers),
};
#endif

// Resolve getters from each game's native table rather than introducing new
// game-address imports. Only the getter is aliased: event identity, move data,
// damage type, PP, animation and move history retain the expanded move ID.
const W2UVanillaMoveAlias W2U_VANILLA_MOVE_ALIASES[] = {
    { MOVE_PHANTOM_FORCE, MOVE_SHADOW_FORCE },
    { MOVE_FAIRY_LOCK, MOVE_SPIDER_WEB },
    { MOVE_HOLD_BACK, MOVE_FALSE_SWIPE },
    { MOVE_INFESTATION, MOVE_BIND },
    { MOVE_SNAP_TRAP, MOVE_BIND },
    { MOVE_THUNDER_CAGE, MOVE_BIND },
    { MOVE_NATURES_MADNESS, MOVE_SUPER_FANG },
    { MOVE_RUINATION, MOVE_SUPER_FANG },
    { MOVE_PIKA_PAPOW, MOVE_RETURN },
    { MOVE_VEEVEE_VOLLEY, MOVE_RETURN },
    { MOVE_POWER_TRIP, MOVE_STORED_POWER },
    // Hex supplies any-major-status doubling; the record supplies burn chance.
    { MOVE_INFERNAL_PARADE, MOVE_HEX },
    { MOVE_FLIP_TURN, MOVE_UTURN },
    { MOVE_POWER_SHIFT, MOVE_POWER_TRICK },
    { MOVE_RAGING_FURY, MOVE_OUTRAGE },
    { MOVE_THUNDERCLAP, MOVE_SUCKER_PUNCH },
    { MOVE_COMEUPPANCE, MOVE_METAL_BURST },
    { MOVE_AXE_KICK, MOVE_HI_JUMP_KICK },
    { MOVE_DRAGON_ENERGY, MOVE_ERUPTION },
};

#if !defined(W2U_DYNAMIC_BATTLE_CORE) && !defined(W2U_BATTLE_STATIC_GROUPS)
const W2UPosEffectEventAddTable W2U_POS_EFFECT_EVENT_ADD_TABLE[] = {
    W2U_POS_EVENT(POSEFF_ION_DELUGE, PosIonDelugeHandlers, EVENTPRI_ABILITY_STALL),
    W2U_POS_EVENT(POSEFF_MAT_BLOCK, PosMatBlockHandlers, EVENTPRI_POS_DEFAULT),
    W2U_POS_EVENT(POSEFF_CRAFTY_SHIELD, PosCraftyShieldHandlers, EVENTPRI_POS_DEFAULT),
    W2U_POS_EVENT(POSEFF_ELECTRIFY, PosElectrifyHandlers, EVENTPRI_POS_DEFAULT),
};

#undef W2U_POS_EVENT
#undef W2U_MOVE_EVENT
#endif

} // namespace

namespace {

b32 IsAffectedBySheerForceIncludingCustomMoves(MOVE_ID moveID)
{
    return moveID == MOVE_ANCHOR_SHOT ||
        moveID == MOVE_SPIRIT_SHACKLE ||
        moveID == MOVE_THROAT_CHOP ||
        moveID == MOVE_CEASELESS_EDGE ||
        moveID == MOVE_STONE_AXE ||
        moveID == MOVE_BURNING_JEALOUSY ||
        moveID == MOVE_ALLURING_VOICE ||
        moveID == MOVE_EERIE_SPELL ||
        moveID == MOVE_SALT_CURE || moveID == MOVE_SYRUP_BOMB ||
        moveID == MOVE_ELECTRO_SHOT ||
        IsAffectedBySheerForce(moveID);
}

} // namespace

// Route every vanilla Sheer Force predicate through the expanded move list so
// power boosts, failure checks and effect suppression remain synchronized.
extern "C" b32 THUMB_BRANCH_LINK_HandlerSheerForcePower_0x18(MOVE_ID moveID)
{
    return IsAffectedBySheerForceIncludingCustomMoves(moveID);
}

extern "C" b32 THUMB_BRANCH_LINK_HandlerSheerForceCheckFail_0x18(MOVE_ID moveID)
{
    return IsAffectedBySheerForceIncludingCustomMoves(moveID);
}

extern "C" b32 THUMB_BRANCH_LINK_HandlerSheerForceHitCheck_0x18(MOVE_ID moveID)
{
    return IsAffectedBySheerForceIncludingCustomMoves(moveID);
}

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

#if !defined(W2U_BATTLE_CHILD)
extern "C" u32 W2U_CheckProtectBreak(
    ServerFlow* serverFlow, u32 attackingSlot, u32 defendingSlot, u32 category, MOVE_ID moveID)
{
    // Native BW2 supplies only ATTACKING_MON. Damage-only shields also need
    // the current target and damage/status category in this scoped event;
    // Unseen Fist / Piercing Drill need the move (contact).
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, attackingSlot);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, defendingSlot);
    BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, category);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, moveID);
    BattleEventVar_SetValue(VAR_GENERAL_USE_FLAG, 0);
    BattleEvent_CallHandlers(serverFlow, EVENT_CHECK_PROTECT_BREAK);
    u32 result = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);
    BattleEventVar_Pop();
    return result;
}
#endif

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
        u32 breakProtect = W2U_CheckProtectBreak(serverFlow, BattleMon_GetID(attackingMon),
            BattleMon_GetID(targetMon), PML_MoveGetCategory(*moveID), *moveID);
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
    // Keep the logical ID for viewer-side effects that must begin with the
    // move animation.  This runs before Gen 7-9 animation-member remapping.
    W2U_TerrainTexture_OnMoveAnimationStart(moveID);

    u32 attackingViewPos = MainModule_BattlePosToViewPos(btlCore->mainModule, attackingPos);
    u32 targetViewPos = 255;
    if (targetPos != W2U_NULL_BATTLE_POS) {
        targetViewPos = MainModule_BattlePosToViewPos(btlCore->mainModule, targetPos);
    }

    if (moveID == MOVE_POLLEN_PUFF && targetPos != W2U_NULL_BATTLE_POS) {
        // Cascade White's imported Pollen Puff member contains two animation
        // tables in the opposite order from Present: variant 0 is recovery and
        // variant 1 is damage. Select explicitly for both sides because the
        // ordinary damage command arrives with effect index 0 by default.
        const bool targetIsAlly = ((attackingPos ^ targetPos) & 1u) == 0;
        effectIndex = targetIsAlly ? 0u : 1u;
    }

    if (moveID == MOVE_BEAK_BLAST || moveID == MOVE_SHELL_TRAP) {
        // Resident pre-action cues use 0xFF as a wire marker for variant 0.
        // Every ordinary move command is the release/attack variant, even if
        // an upstream path left the default effect index at zero.
        effectIndex = ((u8)effectIndex == 0xFFu) ? 0u : 1u;
    }

    u16 animMoveID = moveID;
    if (animMoveID == MOVE_PSYCHIC_TERRAIN) {
        // Psychic Terrain keeps its existing animation in reserved member 624
        // instead of using its logical move member 678.
        animMoveID = W2U_PSYCHIC_TERRAIN_ANIMATION_ID +
            W2U_BATTLE_ANIMATIONS_COUNT;
    } else if (animMoveID >= W2U_FIRST_BATTLE_ANIMATION_ID &&
               animMoveID < MOVE_END_MSG) {
        // Every expanded move has a corresponding a/0/6/5 member. Encode the
        // logical move ID above the fixed battle-animation range; the loader
        // hook removes this offset and reads the same-numbered move member.
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
    if (moveID >= MOVE_END_MSG) {
        return false;
    }

#if !defined(W2U_BATTLE_CHILD)
    // This hook runs while each active battler's move table is registered,
    // after the native BattleEvent storage exists and before turn-one move
    // execution.  It is a reliable fallback if the earlier battle-setup hook
    // could not yet allocate the permanent outcome tracker.
    if (battleMon) {
        W2U_MoveState_BeginBattleTracking(BattleMon_GetID(battleMon));
    }
#endif

#if defined(W2U_DYNAMIC_BATTLE_CORE)
    if (W2U_BattleModules_IsManaged(W2U_MECHANIC_MOVE, (u16)moveID)) {
        const W2UBattleHandlerExport* entry =
            W2U_BattleModules_Resolve(W2U_MECHANIC_MOVE, (u16)moveID);
        return entry
            ? AddMoveEvent(
                battleMon,
                moveID,
                speed,
                const_cast<BattleEventHandlerTableEntry*>(entry->handlers),
                entry->handlerCount) != 0
            : false;
    }
#elif defined(W2U_BATTLE_STATIC_GROUPS)
    const W2UBattleHandlerExport* entry =
        W2U_BattleStatic_Resolve(W2U_MECHANIC_MOVE, (u16)moveID);
    if (entry) {
        return AddMoveEvent(
            battleMon,
            moveID,
            speed,
            const_cast<BattleEventHandlerTableEntry*>(entry->handlers),
            entry->handlerCount) != 0;
    }
#else
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_MOVE_EVENT_ADD_TABLE); ++idx) {
        const W2UMoveEventAddTable* addEvent = &W2U_MOVE_EVENT_ADD_TABLE[idx];
        if (moveID == addEvent->moveID) {
            return AddMoveEvent(battleMon, moveID, speed, addEvent->handlers, addEvent->handlerAmount) != 0;
        }
    }
#endif

#if !defined(W2U_BATTLE_CHILD)
    if (moveID == MOVE_ENCORE) {
        return GetMoveEvent(battleMon, moveID, speed, EventAddShellTrapAwareEncore) != 0;
    }
    if (moveID == MOVE_MIMIC || moveID == MOVE_SKETCH) {
        return AddMoveEvent(battleMon, moveID, speed, NativeCopyRestrictedHandlers,
            W2U_ARRAY_COUNT(NativeCopyRestrictedHandlers)) != 0;
    }
    if (moveID == MOVE_PSYCH_UP) {
        return AddMoveEvent(battleMon, moveID, speed, PsychUpCriticalHandlers,
            W2U_ARRAY_COUNT(PsychUpCriticalHandlers)) != 0;
    }
#endif

    MOVE_ID vanillaMoveID = moveID;
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_VANILLA_MOVE_ALIASES); ++idx) {
        if (moveID == W2U_VANILLA_MOVE_ALIASES[idx].moveID) {
            vanillaMoveID = (MOVE_ID)W2U_VANILLA_MOVE_ALIASES[idx].vanillaMoveID;
            break;
        }
    }
    W2UNativeMoveGetter nativeGetter = W2U_FindNativeMoveGetter(vanillaMoveID);
    if (nativeGetter) return GetMoveEvent(battleMon, moveID, speed, nativeGetter) != 0;
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
#if defined(W2U_DYNAMIC_BATTLE_CORE)
    if (W2U_BattleModules_IsManaged(W2U_MECHANIC_POSITION, (u16)posEffect)) {
        const W2UBattleHandlerExport* entry =
            W2U_BattleModules_FindLoaded(W2U_MECHANIC_POSITION, (u16)posEffect);
        if (!entry) {
            return 0;
        }
        const BattleEventPriority priority =
            entry->priority == W2U_BATTLE_MODULE_DEFAULT_PRIORITY
                ? EVENTPRI_POS_DEFAULT
                : (BattleEventPriority)entry->priority;
        return AddPosEffectEvent(
            posEffect,
            targetPos,
            const_cast<BattleEventHandlerTableEntry*>(entry->handlers),
            entry->handlerCount,
            priority,
            workCount,
            work);
    }
#elif defined(W2U_BATTLE_STATIC_GROUPS)
    const W2UBattleHandlerExport* entry =
        W2U_BattleStatic_Resolve(W2U_MECHANIC_POSITION, (u16)posEffect);
    if (entry) {
        const BattleEventPriority priority =
            entry->priority == W2U_BATTLE_MODULE_DEFAULT_PRIORITY
                ? EVENTPRI_POS_DEFAULT
                : (BattleEventPriority)entry->priority;
        return AddPosEffectEvent(
            posEffect,
            targetPos,
            const_cast<BattleEventHandlerTableEntry*>(entry->handlers),
            entry->handlerCount,
            priority,
            workCount,
            work);
    }
#else
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
#endif

    for (u32 idx = 0; idx < W2U_POS_EVENT_TABLE_COUNT; ++idx) {
        PosEffectEventAddTable* addEvent = &W2U_POS_EVENT_TABLE[idx];
        if (posEffect == addEvent->posEffect) {
            return GetPosEffectEvent(posEffect, targetPos, addEvent->func, workCount, work);
        }
    }
    return 0;
}

#define W2U_BATTLE_API_SOURCE_MOVES
#include "w2u_battle_module_api_entries.inc"
#undef W2U_BATTLE_API_SOURCE_MOVES

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
    if (multiplier == 256) return W2U_EFFECTIVENESS_16;
    return RESULT_EFFECTIVE;
}

extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_CheckMoveDamageEffectiveness_0x32(
    ServerFlow* serverFlow,
    BattleMon* attackingMon,
    BattleMon* defendingMon,
    u32 moveType,
    u8 pokemonType)
{
    u32 effectiveness = THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(
        serverFlow,
        attackingMon,
        defendingMon,
        moveType,
        pokemonType);

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

    // This adapter runs once on the first native type, before the engine
    // combines the second type and checks Wonder Guard/ability immunity.
    // Added types are included above. Never apply the factor once per type.
    if (moveType == TYPE_FIRE && W2U_MoveState_HasTarShot(defendingMon->battleSlot))
        effectiveness = THUMB_BRANCH_GetTypeEffectivenessMultiplier(effectiveness, RESULT_SUPER_EFFECTIVE);

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

#if !defined(W2U_TARGET_B2)
    // Gorilla Tactics (White 2: battle module abilities/mb_hooked) locks its
    // holder through the Choice lock condition without a Choice item: word it
    // as Encore does, whatever it holds.
    if (BattleMon_GetValue(battleMon, VALUE_EFFECTIVE_ABILITY) == ABIL_GORILLA_TACTICS &&
        BattleMon_CheckIfMoveCondition(battleMon, CONDITION_CHOICELOCK)) {
        ITEM heldItem = BattleMon_GetHeldItem(battleMon);
        // Choice Band 220, Choice Scarf 287, Choice Specs 297: a usable one keeps the item's wording.
        bool choiceItem = (heldItem == 220 || heldItem == 287 || heldItem == 297) &&
            CanMonUseHeldItem(client, battleMon);
        MOVE_ID lockedMove = Condition_GetParam(BattleMon_GetMoveCondition(battleMon, CONDITION_CHOICELOCK));
        if (!choiceItem && lockedMove != moveID && Move_IsUsable(battleMon, lockedMove)) {
            if (strparam) {
                Btlv_StringParam_Setup(strparam, 1, 100);
                Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
                Btlv_StringParam_AddArg(strparam, lockedMove);
            }
            return 1;
        }
    }
#endif

#if !defined(W2U_BATTLE_CHILD)
    // This is selection-only: Instruct/Sleep Talk and a faster Encore's
    // already-queued action rewrite may repeat the move. At the next command
    // menu native no-usable-move handling supplies Struggle when locked.
    const u32 slot = BattleMon_GetID(battleMon);
    if ((moveID == MOVE_BLOOD_MOON || moveID == MOVE_GIGATON_HAMMER) &&
        IsValidSlot(slot) && sMoveState.lastSuccessfulSelectedMove[slot] == moveID) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 580);
            Btlv_StringParam_AddArg(strparam, slot);
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }
#endif

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
        getMoveFlag(moveID, MOVE_FLAG_INDEX_HEALING_MOVE)) {
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

    if (moveID == MOVE_STUFF_CHEEKS && !PML_ItemIsBerry(BattleMon_GetHeldItem(battleMon))) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 905);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (moveID == MOVE_FIRST_IMPRESSION && battleMon->turnCount != 0) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 905);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    if (W2U_MoveState_IsThroatChopped(BattleMon_GetID(battleMon)) &&
        getMoveFlag(moveID, MOVE_FLAG_INDEX_SOUND)) {
        if (strparam) {
            Btlv_StringParam_Setup(strparam, 2, 905);
            Btlv_StringParam_AddArg(strparam, BattleMon_GetID(battleMon));
            Btlv_StringParam_AddArg(strparam, moveID);
        }
        return 1;
    }

    return 0;
}

#endif // White 2 integration; Black 2 remains at 4369e8a47.
