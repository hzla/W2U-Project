// MegaB2W2's terrain interface (terrain::) for the ported logic files, on W2U's own terrain (w2u_moves.cpp):
// same IDs (W2U TERRAIN_ELECTRIC / GRASSY / MISTY / PSYCHIC = 1-4), the state and visuals stay W2U's. See
// docs/megab2w2-integration.md (wave B).
#pragma once
#include "swantypes.h"

struct ServerFlow;

extern "C" u32 W2U_MoveState_GetTerrain();
extern "C" bool W2U_MoveState_SetTerrainFromAbility(ServerFlow* sf, u32 pokeID, u32 terrain, u32 msgID, u32 animMove);
extern "C" bool W2U_MoveState_SetTerrainFromAbilityNamed(ServerFlow* sf, u32 pokeID, u32 terrain, u32 msgID,
                                                         u32 animMove);

namespace terrain {
enum : u8 { NONE = 0, ELECTRIC = 1, GRASSY = 2, MISTY = 3, PSYCHIC = 4 };

inline u8 Current() { return (u8)W2U_MoveState_GetTerrain(); }

// the terrain's type (Mimicry): Electric, Grass, Fairy, Psychic
inline u8 TypeOf(u8 t) {
    switch (t) {
        case ELECTRIC: return 12;
        case GRASSY: return 11;
        case MISTY: return 17;
        case PSYCHIC: return 13;
        default: return 0;
    }
}

// W2U's terrain start messages (bank 18, no argument) and the terrain moves whose animation plays (Black 2 only)
constexpr u16 START_MSG[5] = { 0, 1292, 1295, 1298, 1313 };
constexpr u16 ANIM_MOVE[5] = { 0, 604, 580, 581, 678 };   // Electric / Grassy / Misty / Psychic Terrain

// Start terrain t under pokeID's ability popup (W2U's Surge path: popup, then the start message, with which the
// terrain fades in - no move animation on White 2; W2U fires its after-terrain-change event). Nothing if t is already up. The ported files only set terrain
// from abilities (Seed Sower; Hadron Engine uses SetNamed).
inline bool Set(ServerFlow* sf, u32 pokeID, u8 t, bool /*popup: always, as W2U's Surges*/) {
    return t && t <= PSYCHIC && W2U_MoveState_SetTerrainFromAbility(sf, pokeID, t, START_MSG[t], ANIM_MOVE[t]);
}
// The same with an ability's own message naming pokeID instead of the terrain's start message.
inline bool SetNamed(ServerFlow* sf, u32 pokeID, u8 t, u16 msg) {
    return t && t <= PSYCHIC && W2U_MoveState_SetTerrainFromAbilityNamed(sf, pokeID, t, msg, ANIM_MOVE[t]);
}
}
