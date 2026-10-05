// MegaB2W2 wave C: the resident half (mb_resident.cpp, White2Upgrade.dll, White 2 only). Engine call-site hooks and
// the state they share with the abilities in battle module abilities/mb_hooked: modules import these W2U_MB_*
// functions from the resident core. See docs/megab2w2-integration.md (wave C).
#pragma once
#include "swantypes.h"

struct ServerFlow;

extern "C" {
// Battle exit (W2U_BattleState_OnBattleExit): clear the per-battle state.
void W2U_MB_ResetBattleState();

// The move pokeID's fight action will use this turn, for event 0x0F (special priority), which carries no move:
// noted at the action-order sorts' ServerEvent_GetMovePriority calls. 0: not a fight action, or it has acted.
u16 W2U_MB_PendingMove(ServerFlow* sf, u32 pokeID);
// Turn end: forget pokeID's noted move (a switch or item next turn notes none).
void W2U_MB_ClearPendingMove(u32 pokeID);

// Cud Chew: the effect dispatcher notes a Berry a holder ate. At each turn end (the holder's handler) this counts down
// and returns the Berry to chew again at the end of the next turn (0: nothing yet); the second bite is not noted.
u16 W2U_MB_CudChewTurnEnd(u32 pokeID);
void W2U_MB_CudChewForget(u32 pokeID);

// Opportunist: a copy the holder queued (one stat change, matched at the dispatcher's StatChange call, which runs it
// with the copying flag set: event 0x5D inside it is not recorded again).
void W2U_MB_OpportunistCopyQueued(u32 pokeID);
bool W2U_MB_OpportunistCopying();

// Mega Sol: the Pokemon whose move is running (0xFF: none); ServerEvent_GetWeather answers sun during it.
void W2U_MB_SetMegaSolAttacker(u32 pokeID);

// Mega extras (mb_mega_extras.cpp): the Mega's cry with a reverb tail, cued from W2U's Mega animation wait.
void W2U_MB_MegaCryBegin(u32 species, u32 form, u32 viewPos, u32 swapFrame);
void W2U_MB_MegaCryFrame(u32 frame);
void W2U_MB_MegaCryEnd();
// Mega glyph (mb_mega_extras.cpp): armed at W2U's sprite refresh; W2U's Mega wait holds while it is shown.
void W2U_MB_MegaGlyphArm(u32 viewPos, u32 species, u32 form);
bool W2U_MB_MegaGlyphBusy();
void W2U_MB_CacheSpritePlaces();
}
