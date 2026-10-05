#ifndef __W2U_MOVES_H
#define __W2U_MOVES_H

#include "w2u_abilities.h"

// Resolve native tables from this game's resident anchors, never child symbols.
typedef BattleEventHandlerTableEntry* (*W2UNativeMoveGetter)(u32* count);
extern "C" W2UNativeMoveGetter W2U_FindNativeMoveGetter(MOVE_ID nativeMove);
extern "C" bool W2U_MoveIsRestrictedNpcAttack(MOVE_ID moveID);

extern "C" void W2U_MoveState_ResetBattleState();
extern "C" void W2U_MoveState_BeginBattleTracking(u32 fallbackPokemonSlot);
extern "C" bool W2U_MoveState_EnsureTransientEvent(u32 pokemonSlot);
extern "C" bool W2U_MoveState_DidLastMoveFailForStomping(u32 pokemonSlot);
// Applied changes only, after Contrary/Simple/prevention. Stage replacement
// (Haze, Transform, Topsy-Turvy) does not set this turn's history.
extern "C" bool W2U_MoveState_HadStatChangeThisTurn(u32 pokemonSlot, bool raised);
// Native battle IDs identify party members, including benched members.
// These histories last for the whole battle, including revival.
extern "C" u32 W2U_MoveState_RageFistPower(u32 pokemonSlot);
// Zero denotes unsupported multi-trainer ownership, not ordinary 50 power.
extern "C" u32 W2U_MoveState_LastRespectsPower(ServerFlow* flow, u32 pokemonSlot);
// Resident asynchronous party-choice transaction, with no child pointers.
extern "C" void W2U_Revival_Reset();
extern "C" u32 W2U_GetBattlePartyOwner(ServerFlow* flow, u32 pokemonSlot);
extern "C" bool W2U_Revival_CanUse(ServerFlow* flow, u32 pokemonSlot);
extern "C" bool W2U_Revival_Begin(ServerFlow* flow, u32 pokemonSlot);
extern "C" void W2U_MoveState_RecordDisguiseHit(ServerFlow* flow, u32 pokemonSlot);
extern "C" void W2U_CopyTransformMoveState(BattleMon* user, BattleMon* target);
// Opaque transaction: children never see native/custom side-state layouts.
extern "C" bool W2U_MoveState_CourtChange(ServerFlow* flow);
// Calling status move origin; direct Dragon Darts never receives this immunity.
extern "C" bool W2U_DragonDartsHasPranksterOrigin(ServerFlow* flow, u32 slot);
// Native HP/berry/Substitute display transaction and source-only exit filter.
// Mutable transfer state stays resident through both server and client copies.
extern "C" bool W2U_MoveState_CreateShedTailSub(ServerFlow* flow, u32 slot);
extern "C" void W2U_MoveState_PrepareShedTailExit(BattleMon* mon);
// Action-scoped category/contact, with a separate damaging-history category.
extern "C" void W2U_MoveState_SetShellSideArmCategory(u32 slot, u32 category);
extern "C" u32 W2U_MoveState_ShellSideArmCategory(u32 slot);
extern "C" bool W2U_MoveState_ApplyTarShot(u32 pokemonSlot);
extern "C" bool W2U_MoveState_HasTarShot(u32 pokemonSlot);
extern "C" bool W2U_MoveState_TryNoRetreat(u32 pokemonSlot);
extern "C" bool W2U_MoveState_HasNoRetreat(u32 pokemonSlot);
extern "C" void W2U_MoveState_StartGlaiveRush(u32 pokemonSlot);
extern "C" bool W2U_MoveState_EnsureAuxEvent(u16 fieldId, u32 owner);
extern "C" bool W2U_MoveState_StartPersistentEffect(MOVE_ID move, u32 source, u32 target);
extern "C" bool W2U_MoveState_HasPersistentEffect(MOVE_ID move, u32 target);
extern "C" u32 W2U_MoveState_PersistentSource(MOVE_ID move, u32 target);
extern "C" void W2U_MoveState_TickPersistentEffect(MOVE_ID move, u32 target);
// Same scoped protection-break decision used by the resident protection pass.
// Child handlers may query it before native immunity filtering removes targets.
extern "C" u32 W2U_CheckProtectBreak(
    ServerFlow* serverFlow, u32 attackingSlot, u32 defendingSlot, u32 category);

extern "C" void W2U_MoveState_SetConsumedBerryFlag(u32 pokemonSlot);
extern "C" bool W2U_MoveState_HasConsumedBerryFlag(u32 pokemonSlot);

extern "C" void W2U_MoveState_SetExtraType(u32 pokemonSlot, u32 pokeType);
extern "C" void W2U_MoveState_ClearExtraType(u32 pokemonSlot);
extern "C" u32 W2U_MoveState_GetExtraType(u32 pokemonSlot);

extern "C" void W2U_MoveState_SetElectrified(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsElectrified(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearElectrifiedSlot(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearElectrified();
extern "C" bool W2U_MoveState_IsIonDelugeActive();

// Resolve Revelation Dance from the user's current ordered types. This keeps
// Burn Up's typeless/added-type state distinct from Roost's pure-Flying
// Normal fallback.
extern "C" u32 W2U_ResolveRevelationDanceType(BattleMon* battleMon);

extern "C" void W2U_MoveState_StartLaserFocus(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsLaserFocused(u32 pokemonSlot);
extern "C" bool W2U_MoveState_HasLaserFocus();
extern "C" bool W2U_MoveState_ApplyDragonCheer(ServerFlow* flow, u32 slot);
extern "C" void W2U_CopyCriticalBoost(BattleMon* user, BattleMon* target);
extern "C" void W2U_MoveState_TickLaserFocus(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearLaserFocus(u32 pokemonSlot);

extern "C" bool W2U_MoveState_StartThroatChop(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsThroatChopped(u32 pokemonSlot);
extern "C" bool W2U_MoveState_HasThroatChop();
extern "C" bool W2U_MoveState_TickThroatChop(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearThroatChop(u32 pokemonSlot);

extern "C" bool W2U_MoveState_StartBeakBlast(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsBeakBlastCharging(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearBeakBlast(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearAllBeakBlast();
extern "C" bool W2U_MoveState_HasBeakBlastCharging();
extern "C" void W2U_MoveState_PrepareBeakBlastCharges(
    ServerFlow* serverFlow,
    u32 startActionIdx);

extern "C" bool W2U_MoveState_StartShellTrap(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsShellTrapWaiting(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsShellTrapTriggered(u32 pokemonSlot);
extern "C" bool W2U_MoveState_TriggerShellTrap(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearShellTrap(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearAllShellTraps();
extern "C" bool W2U_MoveState_HasShellTrap();
extern "C" void W2U_MoveState_PrepareShellTraps(
    ServerFlow* serverFlow,
    u32 startActionIdx);

// Spotlight is registered from the moves/flow child, but its redirection
// state and event must remain resident after that move event is removed.
extern "C" bool W2U_MoveState_SetSpotlightTarget(
    ServerFlow* serverFlow,
    u32 targetSlot);

// Resident services used by dynamically loaded move modules that schedule a
// complete, immediate battle action (currently Instruct).  Keep the action
// queue and BattleMon layout private to the resident core.
extern "C" bool W2U_ExtraAction_GetLastMove(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    MOVE_ID* moveID,
    u32* targetPos);
extern "C" MOVE_ID W2U_ExtraAction_GetPendingMove(
    ServerFlow* serverFlow,
    u32 pokemonSlot);
extern "C" bool W2U_ExtraAction_HasMoveWithPP(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    MOVE_ID moveID);
// Pending damaging-move eligibility uses the queued move-priority bracket,
// not Quick Claw/Custap's within-bracket ordering bonus.
extern "C" bool W2U_ExtraAction_GetPendingMovePriority(
    ServerFlow*, u32 pokemonSlot, MOVE_ID* moveID, int* priority);
extern "C" bool W2U_ExtraAction_QueueInstruct(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    MOVE_ID moveID,
    u32 targetPos);

extern "C" TERRAIN W2U_MoveState_GetTerrain();
extern "C" bool W2U_MoveState_SetTerrainFromAbility(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    TERRAIN terrain,
    u32 msgID,
    MOVE_ID animationMoveID);
extern "C" bool W2U_MoveState_RemoveTerrain(ServerFlow* serverFlow);
extern "C" bool W2U_MoveState_RemoveStickyWebSide(u32 side);
extern "C" bool W2U_MoveState_RemoveAuroraVeilSide(
    ServerFlow* serverFlow,
    u32 pokemonSlot,
    u32 side,
    bool showMessage);

#endif
