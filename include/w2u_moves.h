#ifndef __W2U_MOVES_H
#define __W2U_MOVES_H

#include "w2u_abilities.h"

extern "C" void W2U_MoveState_ResetBattleState();

extern "C" void W2U_MoveState_SetConsumedBerryFlag(u32 pokemonSlot);
extern "C" bool W2U_MoveState_HasConsumedBerryFlag(u32 pokemonSlot);

extern "C" void W2U_MoveState_SetExtraType(u32 pokemonSlot, u32 pokeType);
extern "C" void W2U_MoveState_ClearExtraType(u32 pokemonSlot);
extern "C" u32 W2U_MoveState_GetExtraType(u32 pokemonSlot);

extern "C" void W2U_MoveState_SetElectrified(u32 pokemonSlot);
extern "C" bool W2U_MoveState_IsElectrified(u32 pokemonSlot);
extern "C" void W2U_MoveState_ClearElectrified();

extern "C" TERRAIN W2U_MoveState_GetTerrain();
extern "C" bool W2U_MoveState_RemoveTerrain(ServerFlow* serverFlow);
extern "C" bool W2U_MoveState_RemoveStickyWebSide(u32 side);

#endif
