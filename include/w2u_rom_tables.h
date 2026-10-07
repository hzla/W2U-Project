#ifndef W2U_ROM_TABLES_H
#define W2U_ROM_TABLES_H

// Read-only tables kept in ROM files instead of the resident core (docs/megab2w2-integration.md, "Tables in ROM
// files"): looked up once where they are needed (outside VBlank), so they cost no PMC heap. The files are built from
// the same generated .inc data by src/pokeweb_gameplay/w2u_rom_tables_data.cpp (compiled with the core's flags, so
// the records have the core's layout) and staged as sidecars in the filesystem root (data/meson.build). White 2
// only; Black 2 keeps its tables resident.

#include "swantypes.h"

// w2u_terrain_texture.cpp: a battle background's terrain textures (w2u_terrain_texture_mappings.inc).
#define W2U_TERRAIN_NITRO_NAME_LENGTH 16u
struct W2UTerrainTextureMapping {
    u16 fieldMember;
    // The generated Electric/Grassy/Misty/Psychic resources are always four
    // consecutive archive members. Store only the first member so expanding
    // background coverage does not waste resident PMC heap on redundant IDs.
    u16 terrainTextureBaseMember;
    u16 floorAnimationMember;
    char floorMaterial[W2U_TERRAIN_NITRO_NAME_LENGTH];
    // The backdrop's (batt_sky*) palette range in colours; Grassy / Misty clones replace that sky (0: none).
    u16 skyPaletteFirst;
    u16 skyPaletteCount;
};
static_assert(sizeof(W2UTerrainTextureMapping) == 26, "terrain mapping record layout");

// mb_mega_extras.cpp: where the Mega glyph sits above each Mega's sprite (mb_mega_glyph_heights.inc).
struct W2UMegaGlyphPlace {
    u16 species;
    u8 form, frontTop, frontCx, backTop, backCx;
};
static_assert(sizeof(W2UMegaGlyphPlace) == 8, "Mega glyph place record layout");

#define W2U_PATH_TERRAIN_TEXTURE_MAPPINGS "w2u_terrain_texture_mappings.bin"
#define W2U_PATH_MEGA_GLYPH_PLACES "w2u_mega_glyph_places.bin"

// Copies the first record of the file at path (recordSize bytes each) for which match(record, key) holds into out;
// false if there is none or the file cannot be read. Reads a few records at a time into a small stack buffer.
extern "C" bool W2U_RomTable_Find(
    const char* path, u32 recordSize, bool (*match)(const void* record, u32 key), u32 key, void* out);

#endif
