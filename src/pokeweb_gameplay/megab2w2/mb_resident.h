// MegaB2W2's resident half (mb_resident.cpp, mb_mega_extras.cpp; White2Upgrade.dll, White 2 only): what W2U's own
// C++ (w2u_mega.cpp) calls. The functions the C mechanics share with the resident core (W2U_MB_PendingMove, Cud
// Chew, Opportunist, Mega Sol) are declared with the engine interface's W2U extensions (include/w2u/battle_api.h).
// See docs/megab2w2-integration.md (wave C).
#pragma once
#include "swantypes.h"

extern "C" {
// Battle exit (W2U_BattleState_OnBattleExit): clear the per-battle state.
void W2U_MB_ResetBattleState();

// Mega extras (mb_mega_extras.cpp): the Mega's cry with a reverb tail, cued from W2U's Mega animation wait.
void W2U_MB_MegaCryBegin(u32 species, u32 form, u32 viewPos, u32 swapFrame);
void W2U_MB_MegaCryFrame(u32 frame);
void W2U_MB_MegaCryEnd();
// Mega glyph (mb_mega_extras.cpp): armed at W2U's sprite refresh; W2U's Mega wait holds while it is shown.
void W2U_MB_MegaGlyphArm(u32 viewPos, u32 species, u32 form);
bool W2U_MB_MegaGlyphBusy();
void W2U_MB_CacheSpritePlaces();
// The cry and the glyph stop (W2U_MB_ResetBattleState calls it).
void W2U_MB_MegaExtrasReset();
}
