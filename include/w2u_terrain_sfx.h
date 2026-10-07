#ifndef W2U_TERRAIN_SFX_H
#define W2U_TERRAIN_SFX_H

// Terrain sounds (docs/megab2w2-integration.md, "Terrain sounds"): sequences appended to the sound archive by
// tools/audio/terrain_sfx/build_terrain_sfx.py, which checks these IDs against its recipes (and the move scripts'
// take-1 PlaySound IDs). Take 2 ("the terrain is applied") is played by w2u_terrain_texture.cpp at the terrain's
// start message: up to three layers at once on sound handles 1 / 2 / 4 (players SE_1 / SE_2 / SE_3); 0 = no layer.

#define W2U_TERRAIN_SFX_ELECTRIC_APPLY_0 2435u
#define W2U_TERRAIN_SFX_ELECTRIC_APPLY_1 2436u
#define W2U_TERRAIN_SFX_ELECTRIC_APPLY_2 2437u
#define W2U_TERRAIN_SFX_GRASSY_APPLY_0 2429u
#define W2U_TERRAIN_SFX_GRASSY_APPLY_1 2430u
#define W2U_TERRAIN_SFX_GRASSY_APPLY_2 2431u
#define W2U_TERRAIN_SFX_MISTY_APPLY_0 2423u
#define W2U_TERRAIN_SFX_MISTY_APPLY_1 2424u
#define W2U_TERRAIN_SFX_MISTY_APPLY_2 2425u
#define W2U_TERRAIN_SFX_PSYCHIC_APPLY_0 2418u
#define W2U_TERRAIN_SFX_PSYCHIC_APPLY_1 2419u
#define W2U_TERRAIN_SFX_PSYCHIC_APPLY_2 0u

#define W2U_TERRAIN_SFX_HANDLE_0 1u
#define W2U_TERRAIN_SFX_HANDLE_1 2u
#define W2U_TERRAIN_SFX_HANDLE_2 4u

#endif
