#include "w2u_moves.h"

namespace {

typedef void* (*ClactUnitCreateFn)(u32 count, u32 mode, u32 heapID);
typedef void (*ClactUnitDeleteFn)(void* unit);
typedef void* (*ClactWorkCreateFn)(
    void* unit,
    u32 characterID,
    u32 paletteID,
    u32 cellAnimationID,
    const void* workData,
    u32 renderScreen,
    u32 heapID);
typedef void (*ClactWorkRemoveFn)(void* work);
typedef void (*ClactWorkSetPosFn)(void* work, const void* position, u32 renderScreen);
typedef void (*ClactWorkSetFlagFn)(void* work, u32 enabled);
typedef void (*ClactWorkSetSequenceFn)(void* work, u32 sequence);

const ClactUnitCreateFn ClactUnitCreate = (ClactUnitCreateFn)0x0204BF49u;
const ClactUnitDeleteFn ClactUnitDelete = (ClactUnitDeleteFn)0x0204BFC5u;
const ClactWorkCreateFn ClactWorkCreate = (ClactWorkCreateFn)0x0204C06Du;
const ClactWorkRemoveFn ClactWorkRemove = (ClactWorkRemoveFn)0x0204C135u;
const ClactWorkSetPosFn ClactWorkSetPos = (ClactWorkSetPosFn)0x0204C16Du;
const ClactWorkSetFlagFn ClactWorkSetAutoAnimation = (ClactWorkSetFlagFn)0x0204C54Du;
const ClactWorkSetSequenceFn ClactWorkSetSequence = (ClactWorkSetSequenceFn)0x0204C4B5u;

const u32 W2U_BTLV_INPUT_CHARACTER_ID_OFFSET = 0x104u;
const u32 W2U_BTLV_INPUT_PALETTE_ID_OFFSET = 0x108u;
const u32 W2U_BTLV_INPUT_CELL_ANIMATION_ID_OFFSET = 0x10Cu;
const u32 W2U_BTLV_INPUT_HEAP_ID_OFFSET = 0x2C4u;
const u32 W2U_TERRAIN_SEQUENCE_BASE = 20u;
const u32 W2U_CLACT_RENDER_SUB = 1u;

struct ClactPosition {
    s16 x;
    s16 y;
};

struct ClactWorkData {
    s16 x;
    s16 y;
    u8 animation;
    u8 priority;
    u8 bgPriority;
    u8 padding;
};

const ClactWorkData kTerrainWorkData = {0, 0, 0, 0, 0, 0};
void* sTerrainUnit;
void* sTerrainWork;
void* sTerrainBiw;

u32 ReadWord(const void* base, u32 offset)
{
    return *(const u32*)((const u8*)base + offset);
}

u32 ReadHalfWord(const void* base, u32 offset)
{
    return *(const u16*)((const u8*)base + offset);
}

void HideTerrainIndicator()
{
    if (sTerrainWork) {
        ClactWorkRemove(sTerrainWork);
        sTerrainWork = 0;
    }
}

} // namespace

extern "C" void W2U_TerrainIndicator_Hide()
{
    HideTerrainIndicator();
}

extern "C" void W2U_TerrainIndicator_Term()
{
    HideTerrainIndicator();
    if (sTerrainUnit) {
        ClactUnitDelete(sTerrainUnit);
        sTerrainUnit = 0;
    }
    sTerrainBiw = 0;
}

extern "C" void W2U_TerrainIndicator_Create(void* biw)
{
    if (!biw) {
        return;
    }
    if (sTerrainBiw && sTerrainBiw != biw) {
        // The previous battle heap has already gone away if its normal exit
        // hook was skipped, so discard stale handles without dereferencing them.
        sTerrainUnit = 0;
        sTerrainWork = 0;
    }
    sTerrainBiw = biw;
    HideTerrainIndicator();

    const u32 terrain = (u32)W2U_MoveState_GetTerrain();
    if (terrain < TERRAIN_ELECTRIC || terrain > TERRAIN_PSYCHIC) {
        return;
    }
    const u32 heapID = ReadHalfWord(biw, W2U_BTLV_INPUT_HEAP_ID_OFFSET);
    if (!sTerrainUnit) {
        sTerrainUnit = ClactUnitCreate(1, 2, heapID);
        if (!sTerrainUnit) {
            return;
        }
    }
    sTerrainWork = ClactWorkCreate(
        sTerrainUnit,
        ReadWord(biw, W2U_BTLV_INPUT_CHARACTER_ID_OFFSET),
        ReadWord(biw, W2U_BTLV_INPUT_PALETTE_ID_OFFSET),
        ReadWord(biw, W2U_BTLV_INPUT_CELL_ANIMATION_ID_OFFSET),
        &kTerrainWorkData,
        W2U_CLACT_RENDER_SUB,
        heapID);
    if (!sTerrainWork) {
        return;
    }
    const ClactPosition position = {32, 32};
    ClactWorkSetPos(sTerrainWork, &position, W2U_CLACT_RENDER_SUB);
    // Each terrain sequence is a single static cell; no animation task is
    // needed for the indicator artwork.
    ClactWorkSetAutoAnimation(sTerrainWork, 0);
    ClactWorkSetSequence(sTerrainWork, W2U_TERRAIN_SEQUENCE_BASE + terrain);
}
