// Command-screen weather / terrain indicators. Merged from MegaB2W2 (WeatherView.cpp, TerrainView.cpp) on top of
// White2Upgrade's terrain indicator (own CLACT unit, created after the native Weather indicator).
//
// Art: tools/graphics/build_command_indicators.py (battgra 420-423 + member 941). The sprite sheet holds one slot
// per indicator; the current strong weather's / terrain's frames are copied into it from member 941 when the panel
// appears (sub-OBJ VRAM is shared with the Double Battle party icons).
//
// WEATHER panel (native, ov168 0x21EE748, called from 0x21EACD0): for a strong weather on screen the panel gets a
// weather value its 5-entry tables accept (strong winds: 5, whose sequence 0x13 now shows the winds icon; heavy rain
// / harsh sun: rain / sun) and, for heavy rain / harsh sun, its sequence call (0x21EE7FE) is redirected to their
// icons (sequences 21 / 22).
// TERRAIN panel: an animated label + box (sequence 23, palette 15) in this file's own CLACT unit, under the WEATHER
// panel when there is weather, else in its place, sliding in with it (8 px a frame from the input's task list).
#include "w2u_moves.h"
#include "w2u_platform.h"
#if !defined(W2U_TARGET_B2)
#include "w2u_strong_weather.h"
#endif

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

const ClactUnitCreateFn ClactUnitCreate = (ClactUnitCreateFn)W2U_ADDR_CLACT_UNIT_CREATE;
const ClactUnitDeleteFn ClactUnitDelete = (ClactUnitDeleteFn)W2U_ADDR_CLACT_UNIT_DELETE;
const ClactWorkCreateFn ClactWorkCreate = (ClactWorkCreateFn)W2U_ADDR_CLACT_WORK_CREATE;
const ClactWorkRemoveFn ClactWorkRemove = (ClactWorkRemoveFn)W2U_ADDR_CLACT_WORK_REMOVE;
const ClactWorkSetPosFn ClactWorkSetPos = (ClactWorkSetPosFn)W2U_ADDR_CLACT_WORK_SET_POS;
const ClactWorkSetFlagFn ClactWorkSetAutoAnimation =
    (ClactWorkSetFlagFn)W2U_ADDR_CLACT_WORK_SET_AUTO_ANIMATION;
const ClactWorkSetSequenceFn ClactWorkSetSequence =
    (ClactWorkSetSequenceFn)W2U_ADDR_CLACT_WORK_SET_SEQUENCE;

const u32 W2U_BTLV_INPUT_CHARACTER_ID_OFFSET = 0x104u;
const u32 W2U_BTLV_INPUT_PALETTE_ID_OFFSET = 0x108u;
const u32 W2U_BTLV_INPUT_CELL_ANIMATION_ID_OFFSET = 0x10Cu;
const u32 W2U_BTLV_INPUT_ANIM_FLAGS_OFFSET = 0x68u;   // bits 1-3: slide tasks running (as the native panel)
const u32 W2U_BTLV_INPUT_HEAP_ID_OFFSET = 0x2C4u;
const u32 W2U_CLACT_RENDER_SUB = 1u;

// Must match tools/graphics/build_command_indicators.py.
const u32 W2U_INDICATOR_ART_MEMBER = 941u;
const u32 W2U_BATTGRA_ARC = 11u;
const u32 W2U_INDICATOR_FRAME_BYTES = 15u * 32u;
const u32 W2U_WEATHER_SLOT_FRAMES = 3u;
const u32 W2U_WEATHER_SLOT_TILE = 314u;
const u32 W2U_TERRAIN_SLOT_TILE = 364u;
const u32 W2U_TERRAIN_FRAMES = 2u;
const u32 W2U_TERRAIN_SEQUENCE = 23u;
const u32 W2U_TERRAIN_PALETTE = 15u;
const u32 W2U_TERRAIN_ART_OFFSET = 3u * W2U_WEATHER_SLOT_FRAMES * W2U_INDICATOR_FRAME_BYTES;
const u32 W2U_TERRAIN_PALETTES_OFFSET = W2U_TERRAIN_ART_OFFSET + 4u * W2U_TERRAIN_FRAMES * W2U_INDICATOR_FRAME_BYTES;
// The input sprite set's character data starts 16 tiles into sub-OBJ VRAM.
const u32 W2U_SUB_OBJ_VRAM = 0x06600000u;
const u32 W2U_SUB_OBJ_PALETTE = 0x05000600u;
const u32 W2U_INPUT_SHEET_VRAM_TILE = 16u;

const s16 W2U_PANEL_START_X = 0x131;
const s16 W2U_PANEL_END_X = 0xE1;
const s16 W2U_PANEL_Y_ALONE = 24;
const s16 W2U_PANEL_Y_UNDER_WEATHER = 24 + 36;
const s16 W2U_PANEL_STEP = 8;

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
u32 sPanelWeather;         // the weather value the native panel got this time (0: no WEATHER panel)
u16 sTerrainPalette[16];

extern "C" void GFL_ArcSysReadRange(void* destination, u32 arcID, u32 dataID, u32 offset, u32 size);
extern "C" void* GFL_HeapAllocate(u32 heapID, u32 size, u32 clear, const char* file, u32 line);
extern "C" void GFL_HeapFree(void* memory);

u32 ReadWord(const void* base, u32 offset)
{
    return *(const u32*)((const u8*)base + offset);
}

u32 ReadHalfWord(const void* base, u32 offset)
{
    return *(const u16*)((const u8*)base + offset);
}

// Copy `frames` frames of member 941 (from `offset`) into the sheet's tiles starting at `tile`. Each frame is read
// into a scratch frame on the battle input's game heap (`biw`'s heap, freed again here; not PMC's), then copied in
// 32-bit words (VRAM ignores the byte writes a file read would make).
void CopyFramesToVram(void* biw, u32 offset, u32 frames, u32 tile)
{
    const u32 heapID = ReadHalfWord(biw, W2U_BTLV_INPUT_HEAP_ID_OFFSET);
    u32* buffer = (u32*)GFL_HeapAllocate((heapID & 0x7FFF) | 0x8000, W2U_INDICATOR_FRAME_BYTES, 0, "", 0);
    if (!buffer) {
        return;                                  // (no memory: the slot keeps its previous frames)
    }
    for (u32 f = 0; f < frames; ++f) {
        GFL_ArcSysReadRange(buffer, W2U_BATTGRA_ARC, W2U_INDICATOR_ART_MEMBER,
            offset + f * W2U_INDICATOR_FRAME_BYTES, W2U_INDICATOR_FRAME_BYTES);
        volatile u32* destination = (volatile u32*)(W2U_SUB_OBJ_VRAM +
            (W2U_INPUT_SHEET_VRAM_TILE + tile) * 32u + f * W2U_INDICATOR_FRAME_BYTES);
        for (u32 i = 0; i < W2U_INDICATOR_FRAME_BYTES / 4; ++i) {
            destination[i] = buffer[i];
        }
    }
    GFL_HeapFree(buffer);
}

void UploadTerrainPalette()
{
    volatile u16* palette = (volatile u16*)(W2U_SUB_OBJ_PALETTE + W2U_TERRAIN_PALETTE * 32u);
    for (u32 i = 0; i < 16; ++i) {
        palette[i] = sTerrainPalette[i];
    }
}

void HideTerrainIndicator()
{
    if (sTerrainWork) {
        ClactWorkRemove(sTerrainWork);
        sTerrainWork = 0;
    }
}

#if !defined(W2U_TARGET_B2)
// Slide-in task in the input's task list (ov168 sub_21EF400 add / sub_21EF430 end; the end frees the work).
typedef void* (*TcbAddFn)(void* manager, void (*func)(void*, void*), void* work, u32 priority);
typedef void (*InputTaskAddFn)(void* input, void* tcb, void (*end)(void*));
typedef void (*InputTaskEndFn)(void* input, void* tcb);
extern "C" void* GFL_TCBMgrAddTask(void* manager, void (*func)(void*, void*), void* work, u32 priority);
const InputTaskAddFn InputTaskAdd = (InputTaskAddFn)0x021EF401u;
const InputTaskEndFn InputTaskEnd = (InputTaskEndFn)0x021EF431u;

struct SlideWork {
    void* input;
    void* work;
    s16 x;
    s16 y;
};

void SlideCount(void* input, int delta)
{
    u32* flags = (u32*)((u8*)input + W2U_BTLV_INPUT_ANIM_FLAGS_OFFSET);
    u32 count = ((*flags >> 1) & 7u) + delta;
    *flags = (*flags & ~0xEu) | ((count & 7u) << 1);
}

void SlideEnd(void*)
{
    if (sTerrainBiw) {
        SlideCount(sTerrainBiw, -1);
    }
}

void SlideTask(void* tcb, void* data)
{
    SlideWork* slide = (SlideWork*)data;
    if (slide->work != sTerrainWork) {   // the panel was taken down mid-slide
        InputTaskEnd(slide->input, tcb);
        return;
    }
    UploadTerrainPalette();
    if (slide->x > W2U_PANEL_END_X) {
        slide->x = (s16)(slide->x - W2U_PANEL_STEP < W2U_PANEL_END_X ? W2U_PANEL_END_X : slide->x - W2U_PANEL_STEP);
        const ClactPosition position = {slide->x, slide->y};
        ClactWorkSetPos(slide->work, &position, W2U_CLACT_RENDER_SUB);
    }
    if (slide->x <= W2U_PANEL_END_X) {
        InputTaskEnd(slide->input, tcb);
    }
}

bool StartSlide(void* biw, s16 y, u32 heapID)
{
    SlideWork* slide = (SlideWork*)GFL_HeapAllocate((heapID & 0x7FFF) | 0x8000, sizeof(SlideWork), 0, "", 0);
    if (!slide) {
        return false;
    }
    slide->input = biw;
    slide->work = sTerrainWork;
    slide->x = W2U_PANEL_START_X;
    slide->y = y;
    void* tcb = GFL_TCBMgrAddTask(*(void**)biw, SlideTask, slide, 0);
    InputTaskAdd(biw, tcb, SlideEnd);
    SlideCount(biw, 1);
    return true;
}

// Strong weather on screen -> the weather value / icon the native panel shows.
u32 sPanelSequenceFrom;    // native sequence to redirect (weather + 0xE), 0 = none
u32 sPanelSequenceTo;
#endif

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

// Called before the native WEATHER panel: returns the weather value it gets, and prepares a strong weather's icon.
extern "C" u32 W2U_CommandIndicators_WeatherForPanel(void* biw, u32 weather)
{
#if !defined(W2U_TARGET_B2)
    sPanelSequenceFrom = 0;
    sPanelSequenceTo = 0;
    const u32 shown = W2U_StrongWeather_ShownView();
    u32 kind = 0;   // 1 winds, 2 heavy rain, 3 harsh sun
    if (shown == W2U_WEATHER_VIEW_STRONG_WINDS && weather == 0) {
        weather = 5;   // sequence 0x13: the winds icon
        kind = 1;
    } else if (shown == W2U_WEATHER_VIEW_HEAVY_RAIN && weather == 2) {
        kind = 2;
        sPanelSequenceFrom = 2 + 0xE;
        sPanelSequenceTo = 21;
    } else if (shown == W2U_WEATHER_VIEW_EXTREME_SUN && weather == 1) {
        kind = 3;
        sPanelSequenceFrom = 1 + 0xE;
        sPanelSequenceTo = 22;
    }
    if (kind && biw) {
        CopyFramesToVram(biw, (kind - 1) * W2U_WEATHER_SLOT_FRAMES * W2U_INDICATOR_FRAME_BYTES,
            W2U_WEATHER_SLOT_FRAMES, W2U_WEATHER_SLOT_TILE);
    }
#else
    (void)biw;
#endif
    sPanelWeather = weather;
    return weather;
}

#if !defined(W2U_TARGET_B2)
// The native panel's icon sequence call (ov168 0x21EE7FE: SetAnmSeq(work, weather + 0xE)).
extern "C" void THUMB_BRANCH_LINK_168_0x21EE7FE(void* work, u16 sequence)
{
    if (sPanelSequenceTo && sequence == sPanelSequenceFrom) {
        sequence = (u16)sPanelSequenceTo;
    }
    ClactWorkSetSequence(work, sequence);
}
#endif

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
    const u32 index = terrain - TERRAIN_ELECTRIC;
    CopyFramesToVram(biw, W2U_TERRAIN_ART_OFFSET + index * W2U_TERRAIN_FRAMES * W2U_INDICATOR_FRAME_BYTES,
        W2U_TERRAIN_FRAMES, W2U_TERRAIN_SLOT_TILE);
    GFL_ArcSysReadRange(sTerrainPalette, W2U_BATTGRA_ARC, W2U_INDICATOR_ART_MEMBER,
        W2U_TERRAIN_PALETTES_OFFSET + index * 32u, sizeof(sTerrainPalette));
    UploadTerrainPalette();

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
    const s16 y = sPanelWeather ? W2U_PANEL_Y_UNDER_WEATHER : W2U_PANEL_Y_ALONE;
    ClactWorkSetAutoAnimation(sTerrainWork, 1);
    ClactWorkSetSequence(sTerrainWork, W2U_TERRAIN_SEQUENCE);
#if !defined(W2U_TARGET_B2)
    const ClactPosition start = {W2U_PANEL_START_X, y};
    ClactWorkSetPos(sTerrainWork, &start, W2U_CLACT_RENDER_SUB);
    if (StartSlide(biw, y, heapID)) {
        return;
    }
#endif
    const ClactPosition position = {W2U_PANEL_END_X, y};   // no slide (Black 2, or no task memory)
    ClactWorkSetPos(sTerrainWork, &position, W2U_CLACT_RENDER_SUB);
}
