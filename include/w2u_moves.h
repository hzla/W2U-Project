#ifndef __W2U_MOVES_H
#define __W2U_MOVES_H

#include "w2u_abilities.h"

// Resolve native tables from this game's resident anchors, never child symbols.
typedef BattleEventHandlerTableEntry* (*W2UNativeMoveGetter)(u32* count);
extern "C" W2UNativeMoveGetter W2U_FindNativeMoveGetter(MOVE_ID nativeMove);

extern "C" void W2U_MoveState_ResetBattleState();
extern "C" void W2U_MoveState_BeginBattleTracking(u32 fallbackPokemonSlot);
extern "C" bool W2U_MoveState_EnsureTransientEvent(u32 pokemonSlot);
extern "C" bool W2U_MoveState_DidLastMoveFailForStomping(u32 pokemonSlot);
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
