// The data of the read-only tables kept in ROM files (include/w2u_rom_tables.h). Never linked: compiled with the
// core's flags into an object whose sections tools/stage_w2u_rom_tables.py copies out as the sidecar files, one
// section per file (the records hold no pointers, so the bytes need no relocation).
#include "w2u_rom_tables.h"

#define W2U_ROM_TABLE(name) __attribute__((section(name), used, aligned(4)))

extern const W2UTerrainTextureMapping W2U_ROM_TERRAIN_TEXTURE_MAPPINGS[]
    W2U_ROM_TABLE(".w2u_rom.terrain_texture_mappings") = {
#include "w2u_terrain_texture_mappings.inc"
};

extern const W2UMegaGlyphPlace W2U_ROM_MEGA_GLYPH_PLACES[] W2U_ROM_TABLE(".w2u_rom.mega_glyph_places") = {
#include "megab2w2/mb_mega_glyph_heights.inc"
};
