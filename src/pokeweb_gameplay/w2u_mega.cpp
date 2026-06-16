#include "w2u_battle.h"
#include "w2u_abilities.h"
#include "w2u_field_effects.h"
#include "w2u_moves.h"
#include "w2u_mega_native_button_assets.h"
#include "Personal.h"

#define W2U_ENABLE_MEGA_EVOLUTION 1
#define W2U_KEY_START 0x8
#define W2U_MEGA_VISUAL_STATE_MAGIC 0x53564D57u
#define W2U_MEGA_VISUAL_STATE_VERSION 1u
#define W2U_MEGA_NATIVE_BG0CNT_SUB ((volatile u16 *)0x04001008)
#define W2U_MEGA_NATIVE_BG0HOFS_SUB ((volatile u16 *)0x04001010)
#define W2U_MEGA_NATIVE_BG0VOFS_SUB ((volatile u16 *)0x04001012)
#define W2U_MEGA_NATIVE_BG1CNT_SUB ((volatile u16 *)0x0400100A)
#define W2U_MEGA_NATIVE_BG1HOFS_SUB ((volatile u16 *)0x04001014)
#define W2U_MEGA_NATIVE_BG1VOFS_SUB ((volatile u16 *)0x04001016)
#define W2U_MEGA_NATIVE_BG2CNT_SUB ((volatile u16 *)0x0400100C)
#define W2U_MEGA_NATIVE_BG2HOFS_SUB ((volatile u16 *)0x04001018)
#define W2U_MEGA_NATIVE_BG2VOFS_SUB ((volatile u16 *)0x0400101A)
#define W2U_MEGA_NATIVE_BG_SCREEN_BASE ((volatile u16 *)0x06200000)
#define W2U_MEGA_NATIVE_BG_PALETTE_BASE ((volatile u16 *)0x05000400)
#define W2U_MEGA_NATIVE_BG_LAYER_COUNT 3u
#define W2U_MEGA_NATIVE_BG_VISIBLE_LAYER 2u
#define W2U_MEGA_NATIVE_BUTTON_INDEX 6u
#define W2U_MEGA_NATIVE_BUTTON_EXIST_OFFSET 0x2DEu
#define W2U_MEGA_NATIVE_HIT_NONE 0xFFFFFFFFu
#define W2U_MEGA_NATIVE_WAZA_INFO_MASK 0x8000u
#define W2U_MEGA_NATIVE_CHECK_KEY 0x021EECFDu
#define W2U_MEGA_NATIVE_INPUT_TABLE_NORMAL_US 0x021F3644u
#define W2U_MEGA_NATIVE_INPUT_TABLE_TRIPLE_US 0x021F3650u
#define W2U_GFL_UI_TP_HIT_TRG 0x0203DA39u
#define W2U_SEQ_SE_DECIDE2 1357u
#define W2U_SEQ_SE_CANCEL2 1362u

#if W2U_ENABLE_MEGA_EVOLUTION

extern "C" u8 W2U_CanMegaEvolve(BattleMon* battleMon);
extern "C" void W2U_BattleAction_SetMegaEvolution(BattleActionParam* actionParam, u8 form);
extern "C" void W2U_BattleAction_ResetMegaEvolution(BattleActionParam* actionParam);
extern "C" u8 W2U_BattleAction_CheckMegaEvolution(const BattleActionParam* actionParam);
extern "C" u32 PML_PersonalGetParamSingle(u32 species, u32 form, u32 field);
extern "C" void GFL_SndSEPlay(u32 soundIdx);

namespace {

const u8 W2U_MEGA_NO_SLOT = 0xFF;
const u8 W2U_MEGA_NO_FORM = 0;
const u16 W2U_MEGA_NO_ABILITY = 0xFFFF;

enum MegaSkipReason : u32 {
    MEGA_SKIP_NONE = 0,
    MEGA_SKIP_NULL_MON = 1,
    MEGA_SKIP_FAINTED = 2,
    MEGA_SKIP_TRANSFORMED = 3,
    MEGA_SKIP_ALREADY_FORMED = 4,
    MEGA_SKIP_SIDE_USED = 5,
    MEGA_SKIP_NO_ENTRY = 6,
    MEGA_SKIP_ACTION_SIDE_USED = 7,
    MEGA_SKIP_NOT_FIGHT = 8,
    MEGA_SKIP_CHANGE_FORM_REJECTED = 9,
    MEGA_SKIP_ACTION_ORDER_NO_COMMIT = 10,
    MEGA_SKIP_NULL_SERVER_FLOW = 11,
};

enum MegaToggleSource : u32 {
    MEGA_TOGGLE_SOURCE_NONE = 0,
    MEGA_TOGGLE_SOURCE_START = 1,
    MEGA_TOGGLE_SOURCE_TOUCH = 2,
};

struct MegaEvolutionEntry {
    SPECIES species;
    ITEM item;
    u8 form;
};

struct MegaUiState {
    u8 visible;
    u8 enabled;
    u8 selected;
    u8 form;
    u32 skipReason;
};

struct MegaBattleState {
    u8 usedSideMask;
    u8 committedSideMask;
    u8 selectedSlot;
    u8 selectedForm;
    u8 committedFormBySide[2];
    u8 committedSlotBySide[2];
    u16 originalAbilityBySide[2];
};

struct NativeTouchHitRect {
    u8 up;
    u8 down;
    u8 left;
    u8 right;
};

struct NativeInputHitTable {
    const NativeTouchHitRect* hitTbl;
    const u32* cancel;
    const int* buttonPltt;
};

typedef u32 (*NativeInputCheckKeyFn)(
    void* biw,
    const NativeInputHitTable* touchTable,
    const void* keyTable,
    const void* moveTable,
    u32 hit,
    u32 henshinFlag);

typedef u32 (*NativeTouchHitTriggerFn)(const NativeTouchHitRect* hitTable);

struct MegaVisualState {
    u32 magic;
    u32 version;
    u32 structSize;
    u32 usedSideMask;
    u32 clientChangeFormPokeID;
    u32 clientChangeFormForm;
    u32 visualOverrideReady;
    u32 species;
    u32 form;
    u32 mirroredPartyAbility;
    u32 mirroredPartyMaxHP;
    u32 mirroredPartyAttack;
    u32 mirroredPartyDefense;
    u32 mirroredPartySpAttack;
    u32 mirroredPartySpDefense;
    u32 mirroredPartySpeed;
};

struct MegaButtonBgLayerState {
    u16 originalBgBlock[W2U_MEGA_NATIVE_BUTTON_TILE_W * W2U_MEGA_NATIVE_BUTTON_TILE_H];
    u16 originalBgScreenBase;
    u8 originalBgValid;
    u8 originalBgMapWidth;
    u8 originalBgMapHeight;
    u8 originalBgTileX;
    u8 originalBgTileY;
    u8 bgLastMode;
};

MegaBattleState gMegaState = {
    0,
    0,
    W2U_MEGA_NO_SLOT,
    W2U_MEGA_NO_FORM,
    {W2U_MEGA_NO_FORM, W2U_MEGA_NO_FORM},
    {W2U_MEGA_NO_SLOT, W2U_MEGA_NO_SLOT},
    {W2U_MEGA_NO_ABILITY, W2U_MEGA_NO_ABILITY},
};

MegaUiState gMegaUiState = {
    0,
    0,
    0,
    W2U_MEGA_NO_FORM,
    MEGA_SKIP_NONE,
};

BtlvCore* gMegaActiveBtlCore = nullptr;
MegaButtonBgLayerState gMegaButtonBgLayers[W2U_MEGA_NATIVE_BG_LAYER_COUNT] = {
    {{0}, 0xFFFFu, 0, 0, 0, 0, 0, 0xFFu},
    {{0}, 0xFFFFu, 0, 0, 0, 0, 0, 0xFFu},
    {{0}, 0xFFFFu, 0, 0, 0, 0, 0, 0xFFu},
};

const NativeTouchHitRect W2U_MEGA_NATIVE_NORMAL_HIT_TABLE[] = {
    {0x04u * 8u, 0x0Au * 8u, 0x00u * 8u, 0x10u * 8u},
    {0x04u * 8u, 0x0Au * 8u, 0x10u * 8u, 255u},
    {0x0Au * 8u, 0x10u * 8u, 0x00u * 8u, 0x10u * 8u},
    {0x0Au * 8u, 0x10u * 8u, 0x10u * 8u, 255u},
    {0x12u * 8u, 0x18u * 8u, 0x16u * 8u, 255u},
    {0u, 0u, 0u, 0u},
    {W2U_MEGA_NATIVE_BUTTON_TOUCH_UP,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_DOWN,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_LEFT,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_RIGHT},
    {255u, 0u, 0u, 0u},
};

const u32 W2U_MEGA_NATIVE_NORMAL_CANCEL[] = {
    0u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0u,
};

const int W2U_MEGA_NATIVE_NORMAL_PLTT[] = {
    1 << 9,
    1 << 10,
    1 << 11,
    1 << 12,
    1 << 4,
    0,
    1 << 3,
};

const NativeTouchHitRect W2U_MEGA_NATIVE_TRIPLE_HIT_TABLE[] = {
    {0x04u * 8u, 0x0Au * 8u, 0x00u * 8u, 0x10u * 8u},
    {0x04u * 8u, 0x0Au * 8u, 0x10u * 8u, 255u},
    {0x0Au * 8u, 0x10u * 8u, 0x00u * 8u, 0x10u * 8u},
    {0x0Au * 8u, 0x10u * 8u, 0x10u * 8u, 255u},
    {0x12u * 8u, 0x18u * 8u, 0x16u * 8u, 255u},
    {0x12u * 8u, 0x18u * 8u, 0x00u * 8u, 0x0Au * 8u},
    {W2U_MEGA_NATIVE_BUTTON_TOUCH_UP,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_DOWN,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_LEFT,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_RIGHT},
    {255u, 0u, 0u, 0u},
};

const u32 W2U_MEGA_NATIVE_TRIPLE_CANCEL[] = {
    0u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0u,
};

const int W2U_MEGA_NATIVE_TRIPLE_PLTT[] = {
    1 << 9,
    1 << 10,
    1 << 11,
    1 << 12,
    1 << 4,
    1 << 2,
    1 << 3,
};

const NativeInputHitTable W2U_MEGA_NATIVE_NORMAL_TOUCH_TABLE = {
    W2U_MEGA_NATIVE_NORMAL_HIT_TABLE,
    W2U_MEGA_NATIVE_NORMAL_CANCEL,
    W2U_MEGA_NATIVE_NORMAL_PLTT,
};

const NativeInputHitTable W2U_MEGA_NATIVE_TRIPLE_TOUCH_TABLE = {
    W2U_MEGA_NATIVE_TRIPLE_HIT_TABLE,
    W2U_MEGA_NATIVE_TRIPLE_CANCEL,
    W2U_MEGA_NATIVE_TRIPLE_PLTT,
};

const NativeTouchHitRect W2U_MEGA_DIRECT_TOUCH_TABLE[] = {
    {W2U_MEGA_NATIVE_BUTTON_TOUCH_UP,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_DOWN,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_LEFT,
     W2U_MEGA_NATIVE_BUTTON_TOUCH_RIGHT},
    {255u, 0u, 0u, 0u},
};

const MegaEvolutionEntry W2U_MEGA_TABLE[] = {
    {SPECIES_VENUSAUR, ITEM_VENUSAURITE, 1},
    {SPECIES_CHARIZARD, ITEM_CHARIZARDITE_X, 1},
    {SPECIES_CHARIZARD, ITEM_CHARIZARDITE_Y, 2},
    {SPECIES_BLASTOISE, ITEM_BLASTOISINITE, 1},
    {SPECIES_BEEDRILL, ITEM_BEEDRILLITE, 1},
    {SPECIES_PIDGEOT, ITEM_PIDGEOTITE, 1},
    {SPECIES_ALAKAZAM, ITEM_ALAKAZITE, 1},
    {SPECIES_SLOWBRO, ITEM_SLOWBRONITE, 1},
    {SPECIES_GENGAR, ITEM_GENGARITE, 1},
    {SPECIES_KANGASKHAN, ITEM_KANGASKHANITE, 1},
    {SPECIES_PINSIR, ITEM_PINSIRITE, 1},
    {SPECIES_GYARADOS, ITEM_GYARADOSITE, 1},
    {SPECIES_AERODACTYL, ITEM_AERODACTYLITE, 1},
    {SPECIES_MEWTWO, ITEM_MEWTWONITE_X, 1},
    {SPECIES_MEWTWO, ITEM_MEWTWONITE_Y, 2},
    {SPECIES_AMPHAROS, ITEM_AMPHAROSITE, 1},
    {SPECIES_STEELIX, ITEM_STEELIXITE, 1},
    {SPECIES_SCIZOR, ITEM_SCIZORITE, 1},
    {SPECIES_HERACROSS, ITEM_HERACRONITE, 1},
    {SPECIES_HOUNDOOM, ITEM_HOUNDOOMINITE, 1},
    {SPECIES_TYRANITAR, ITEM_TYRANITARITE, 1},
    {SPECIES_SCEPTILE, ITEM_SCEPTILITE, 1},
    {SPECIES_BLAZIKEN, ITEM_BLAZIKENITE, 1},
    {SPECIES_SWAMPERT, ITEM_SWAMPERTITE, 1},
    {SPECIES_GARDEVOIR, ITEM_GARDEVOIRITE, 1},
    {SPECIES_SABLEYE, ITEM_SABLENITE, 1},
    {SPECIES_MAWILE, ITEM_MAWILITE, 1},
    {SPECIES_AGGRON, ITEM_AGGRONITE, 1},
    {SPECIES_MEDICHAM, ITEM_MEDICHAMITE, 1},
    {SPECIES_MANECTRIC, ITEM_MANECTITE, 1},
    {SPECIES_SHARPEDO, ITEM_SHARPEDONITE, 1},
    {SPECIES_CAMERUPT, ITEM_CAMERUPTITE, 1},
    {SPECIES_ALTARIA, ITEM_ALTARIANITE, 1},
    {SPECIES_BANETTE, ITEM_BANETTITE, 1},
    {SPECIES_ABSOL, ITEM_ABSOLITE, 1},
    {SPECIES_GLALIE, ITEM_GLALITITE, 1},
    {SPECIES_SALAMENCE, ITEM_SALAMENCITE, 1},
    {SPECIES_METAGROSS, ITEM_METAGROSSITE, 1},
    {SPECIES_LATIAS, ITEM_LATIASITE, 1},
    {SPECIES_LATIOS, ITEM_LATIOSITE, 1},
    {SPECIES_LOPUNNY, ITEM_LOPUNNITE, 1},
    {SPECIES_GARCHOMP, ITEM_GARCHOMPITE, 1},
    {SPECIES_LUCARIO, ITEM_LUCARIONITE, 1},
    {SPECIES_ABOMASNOW, ITEM_ABOMASITE, 1},
    {SPECIES_GALLADE, ITEM_GALLADITE, 1},
    {SPECIES_AUDINO, ITEM_AUDINITE, 1},
};

const u32 W2U_BATTLE_SUMMARY_CACHE_KNOWN_ADDRESS = 0x022C4760u;
const u8 W2U_TYPE_DRAGON = 15u;

extern "C" {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
volatile MegaVisualState W2U_MegaVisualState = {
    W2U_MEGA_VISUAL_STATE_MAGIC,
    W2U_MEGA_VISUAL_STATE_VERSION,
    sizeof(MegaVisualState),
};
#pragma GCC diagnostic pop
}

void ClearMegaVisualClientState()
{
    W2U_MegaVisualState.clientChangeFormPokeID = 0;
    W2U_MegaVisualState.clientChangeFormForm = 0;
    W2U_MegaVisualState.visualOverrideReady = 0;
}

void ClearMegaVisualState()
{
    ClearMegaVisualClientState();
    W2U_MegaVisualState.usedSideMask = 0;
    W2U_MegaVisualState.species = 0;
    W2U_MegaVisualState.form = 0;
    W2U_MegaVisualState.mirroredPartyAbility = 0;
    W2U_MegaVisualState.mirroredPartyMaxHP = 0;
    W2U_MegaVisualState.mirroredPartyAttack = 0;
    W2U_MegaVisualState.mirroredPartyDefense = 0;
    W2U_MegaVisualState.mirroredPartySpAttack = 0;
    W2U_MegaVisualState.mirroredPartySpDefense = 0;
    W2U_MegaVisualState.mirroredPartySpeed = 0;
}

void RecordMegaVisualBattleMon(const BattleMon* battleMon)
{
    if (!battleMon) {
        W2U_MegaVisualState.species = 0;
        W2U_MegaVisualState.form = 0;
        return;
    }

    W2U_MegaVisualState.species = battleMon->species;
    W2U_MegaVisualState.form = battleMon->form;
}

void RecordMegaVisualStats(const BattleMon* battleMon)
{
    if (!battleMon) {
        return;
    }

    W2U_MegaVisualState.mirroredPartyAbility = battleMon->ability;
    W2U_MegaVisualState.mirroredPartyMaxHP = battleMon->maxHP;
    W2U_MegaVisualState.mirroredPartyAttack = battleMon->attack;
    W2U_MegaVisualState.mirroredPartyDefense = battleMon->defense;
    W2U_MegaVisualState.mirroredPartySpAttack = battleMon->specialAttack;
    W2U_MegaVisualState.mirroredPartySpDefense = battleMon->specialDefense;
    W2U_MegaVisualState.mirroredPartySpeed = battleMon->speed;
}

void ClearMegaButtonState(u32 skipReason)
{
    gMegaUiState.visible = 0;
    gMegaUiState.enabled = 0;
    gMegaUiState.selected = 0;
    gMegaUiState.form = W2U_MEGA_NO_FORM;
    gMegaUiState.skipReason = skipReason;
}

void NativeBgMapSize(u16 bgCnt, u32* widthOut, u32* heightOut)
{
    const u32 screenSize = (bgCnt >> 14) & 3u;
    if (widthOut) {
        *widthOut = (screenSize & 1u) ? 64u : 32u;
    }
    if (heightOut) {
        *heightOut = (screenSize & 2u) ? 64u : 32u;
    }
}

volatile u16* NativeBgScreenMapForBase(u32 screenBase)
{
    return W2U_MEGA_NATIVE_BG_SCREEN_BASE + screenBase * 0x400u;
}

void NativeBgRegsForLayer(
    u32 layer,
    volatile u16** bgCntOut,
    volatile u16** hofsOut,
    volatile u16** vofsOut)
{
    if (layer == 0u) {
        *bgCntOut = W2U_MEGA_NATIVE_BG0CNT_SUB;
        *hofsOut = W2U_MEGA_NATIVE_BG0HOFS_SUB;
        *vofsOut = W2U_MEGA_NATIVE_BG0VOFS_SUB;
        return;
    }

    if (layer == 1u) {
        *bgCntOut = W2U_MEGA_NATIVE_BG1CNT_SUB;
        *hofsOut = W2U_MEGA_NATIVE_BG1HOFS_SUB;
        *vofsOut = W2U_MEGA_NATIVE_BG1VOFS_SUB;
        return;
    }

    *bgCntOut = W2U_MEGA_NATIVE_BG2CNT_SUB;
    *hofsOut = W2U_MEGA_NATIVE_BG2HOFS_SUB;
    *vofsOut = W2U_MEGA_NATIVE_BG2VOFS_SUB;
}

volatile u16* NativeBgScreenMap(
    u32 layer,
    u32* screenBaseOut,
    u32* mapWidthOut,
    u32* mapHeightOut,
    u32* bgCntOut,
    u32* hofsOut,
    u32* vofsOut)
{
    volatile u16* bgCntReg = nullptr;
    volatile u16* hofsReg = nullptr;
    volatile u16* vofsReg = nullptr;
    NativeBgRegsForLayer(layer, &bgCntReg, &hofsReg, &vofsReg);

    const u16 bgCnt = *bgCntReg;
    const u32 screenBase = (bgCnt >> 8) & 0x1Fu;
    const u32 hofs = *hofsReg & 0x1FFu;
    const u32 vofs = *vofsReg & 0x1FFu;
    u32 mapWidth = 0;
    u32 mapHeight = 0;
    NativeBgMapSize(bgCnt, &mapWidth, &mapHeight);
    if (bgCntOut) {
        *bgCntOut = bgCnt;
    }
    if (screenBaseOut) {
        *screenBaseOut = screenBase;
    }
    if (mapWidthOut) {
        *mapWidthOut = mapWidth;
    }
    if (mapHeightOut) {
        *mapHeightOut = mapHeight;
    }
    if (hofsOut) {
        *hofsOut = hofs;
    }
    if (vofsOut) {
        *vofsOut = vofs;
    }
    return NativeBgScreenMapForBase(screenBase);
}

void NativeMegaButtonMapOrigin(
    u32 mapWidth,
    u32 mapHeight,
    u32 hofs,
    u32 vofs,
    u32* xOut,
    u32* yOut)
{
    *xOut = ((W2U_MEGA_NATIVE_BUTTON_TOUCH_LEFT + hofs) >> 3) & (mapWidth - 1u);
    *yOut = ((W2U_MEGA_NATIVE_BUTTON_TOUCH_UP + vofs) >> 3) & (mapHeight - 1u);
}

u32 NativeBgScreenIndex(u32 tileX, u32 tileY, u32 mapWidth)
{
    const u32 blocksPerRow = mapWidth >> 5;
    const u32 blockX = tileX >> 5;
    const u32 blockY = tileY >> 5;
    return (blockY * blocksPerRow + blockX) * 1024u +
        (tileY & 31u) * 32u + (tileX & 31u);
}

bool NativeBgEntryIsMegaButton(u16 entry)
{
    const u16 tile = entry & 0x03FFu;
    return (tile >= W2U_MEGA_NATIVE_BUTTON_TILE_BASE_NORMAL &&
            tile < W2U_MEGA_NATIVE_BUTTON_TILE_BASE_NORMAL +
                W2U_MEGA_NATIVE_BUTTON_TILE_W * W2U_MEGA_NATIVE_BUTTON_TILE_H) ||
        (tile >= W2U_MEGA_NATIVE_BUTTON_TILE_BASE_ARMED &&
         tile < W2U_MEGA_NATIVE_BUTTON_TILE_BASE_ARMED +
             W2U_MEGA_NATIVE_BUTTON_TILE_W * W2U_MEGA_NATIVE_BUTTON_TILE_H);
}

void CaptureMegaButtonOriginalBgBlock(
    MegaButtonBgLayerState* layerState,
    volatile u16* screenMap,
    u32 screenBase,
    u32 mapWidth,
    u32 mapHeight,
    u32 buttonTileX,
    u32 buttonTileY)
{
    if (!screenMap || mapWidth == 0 || mapHeight == 0) {
        return;
    }

    bool containsMegaTiles = false;
    for (u32 row = 0; row < W2U_MEGA_NATIVE_BUTTON_TILE_H; ++row) {
        for (u32 col = 0; col < W2U_MEGA_NATIVE_BUTTON_TILE_W; ++col) {
            const u32 tileX = (buttonTileX + col) & (mapWidth - 1u);
            const u32 tileY = (buttonTileY + row) & (mapHeight - 1u);
            const u16 entry =
                screenMap[NativeBgScreenIndex(tileX, tileY, mapWidth)];
            containsMegaTiles = containsMegaTiles || NativeBgEntryIsMegaButton(entry);
        }
    }
    if (containsMegaTiles && layerState->originalBgValid) {
        return;
    }

    for (u32 row = 0; row < W2U_MEGA_NATIVE_BUTTON_TILE_H; ++row) {
        for (u32 col = 0; col < W2U_MEGA_NATIVE_BUTTON_TILE_W; ++col) {
            const u32 tileX = (buttonTileX + col) & (mapWidth - 1u);
            const u32 tileY = (buttonTileY + row) & (mapHeight - 1u);
            layerState->originalBgBlock[row * W2U_MEGA_NATIVE_BUTTON_TILE_W + col] =
                screenMap[NativeBgScreenIndex(tileX, tileY, mapWidth)];
        }
    }
    layerState->originalBgScreenBase = (u16)screenBase;
    layerState->originalBgMapWidth = (u8)mapWidth;
    layerState->originalBgMapHeight = (u8)mapHeight;
    layerState->originalBgTileX = (u8)buttonTileX;
    layerState->originalBgTileY = (u8)buttonTileY;
    layerState->originalBgValid = 1u;
}

bool MegaButtonBgTargetChanged(
    const MegaButtonBgLayerState* layerState,
    u32 screenBase,
    u32 mapWidth,
    u32 mapHeight,
    u32 buttonTileX,
    u32 buttonTileY)
{
    return layerState->originalBgValid &&
        (layerState->originalBgScreenBase != screenBase ||
         layerState->originalBgMapWidth != mapWidth ||
         layerState->originalBgMapHeight != mapHeight ||
         layerState->originalBgTileX != buttonTileX ||
         layerState->originalBgTileY != buttonTileY);
}

void RestoreMegaButtonOriginalBgBlock(
    MegaButtonBgLayerState* layerState,
    volatile u16* screenMap,
    u32 mapWidth,
    u32 mapHeight,
    u32 buttonTileX,
    u32 buttonTileY)
{
    if (!screenMap || !layerState->originalBgValid) {
        return;
    }

    for (u32 row = 0; row < W2U_MEGA_NATIVE_BUTTON_TILE_H; ++row) {
        for (u32 col = 0; col < W2U_MEGA_NATIVE_BUTTON_TILE_W; ++col) {
            const u32 tileX = (buttonTileX + col) & (mapWidth - 1u);
            const u32 tileY = (buttonTileY + row) & (mapHeight - 1u);
            screenMap[NativeBgScreenIndex(tileX, tileY, mapWidth)] =
                layerState->originalBgBlock[row * W2U_MEGA_NATIVE_BUTTON_TILE_W + col];
        }
    }
}

void RestoreStoredMegaButtonOriginalBgBlock(MegaButtonBgLayerState* layerState)
{
    if (!layerState->originalBgValid) {
        return;
    }

    RestoreMegaButtonOriginalBgBlock(
        layerState,
        NativeBgScreenMapForBase(layerState->originalBgScreenBase),
        layerState->originalBgMapWidth,
        layerState->originalBgMapHeight,
        layerState->originalBgTileX,
        layerState->originalBgTileY);
    layerState->originalBgValid = 0u;
}

void WriteMegaButtonBgTiles(
    volatile u16* screenMap,
    u32 mapWidth,
    u32 mapHeight,
    u32 buttonTileX,
    u32 buttonTileY,
    u32 tileBase)
{
    const u16 paletteBits = (u16)(W2U_MEGA_NATIVE_BUTTON_PALETTE << 12);
    for (u32 row = 0; row < W2U_MEGA_NATIVE_BUTTON_TILE_H; ++row) {
        for (u32 col = 0; col < W2U_MEGA_NATIVE_BUTTON_TILE_W; ++col) {
            const u32 mapX = (buttonTileX + col) & (mapWidth - 1u);
            const u32 mapY = (buttonTileY + row) & (mapHeight - 1u);
            const u16 tile = (u16)(tileBase + row * W2U_MEGA_NATIVE_BUTTON_TILE_W + col);
            screenMap[NativeBgScreenIndex(mapX, mapY, mapWidth)] =
                (u16)(tile | paletteBits);
        }
    }
}

void CopyMegaButtonTilesToBgVram(u32 bgCnt)
{
    const u32 charBase = (bgCnt >> 2) & 0xFu;
    const u32 dstOffset =
        charBase * 0x4000u + W2U_MEGA_NATIVE_BUTTON_TILE_BASE_NORMAL * 32u;
    volatile u16* dst =
        (volatile u16*)((u32)W2U_MEGA_NATIVE_BG_SCREEN_BASE + dstOffset);

    for (u32 idx = 0; idx < W2U_MEGA_NATIVE_BUTTON_TILE_BYTES_SIZE; idx += 2u) {
        dst[idx >> 1] =
            (u16)(W2U_MEGA_NATIVE_BUTTON_TILE_BYTES[idx] |
                  (W2U_MEGA_NATIVE_BUTTON_TILE_BYTES[idx + 1u] << 8));
    }

}

void CopyMegaButtonPaletteToSubBgPltt()
{
    volatile u16* dst =
        W2U_MEGA_NATIVE_BG_PALETTE_BASE + W2U_MEGA_NATIVE_BUTTON_PALETTE * 16u;

    for (u32 idx = 0; idx < W2U_MEGA_NATIVE_BUTTON_PALETTE_COLORS_SIZE; ++idx) {
        dst[idx] = W2U_MEGA_NATIVE_BUTTON_PALETTE_COLORS[idx];
    }
}

void UpdateMegaButtonBgLayer(u32 layer, u8 mode)
{
    MegaButtonBgLayerState* layerState = &gMegaButtonBgLayers[layer];
    u32 screenBase = 0;
    u32 mapWidth = 0;
    u32 mapHeight = 0;
    u32 bgCnt = 0;
    u32 hofs = 0;
    u32 vofs = 0;
    volatile u16* screenMap =
        NativeBgScreenMap(layer, &screenBase, &mapWidth, &mapHeight, &bgCnt, &hofs, &vofs);
    if (!screenMap || mapWidth == 0 || mapHeight == 0) {
        return;
    }

    u32 buttonTileX = 0;
    u32 buttonTileY = 0;
    NativeMegaButtonMapOrigin(mapWidth, mapHeight, hofs, vofs, &buttonTileX, &buttonTileY);

    const u32 firstIndex = NativeBgScreenIndex(buttonTileX, buttonTileY, mapWidth);

    CopyMegaButtonTilesToBgVram(bgCnt);

    if (!mode) {
        if (layerState->originalBgValid) {
            RestoreStoredMegaButtonOriginalBgBlock(layerState);
        }
        layerState->bgLastMode = 0u;
        return;
    }

    if (MegaButtonBgTargetChanged(layerState, screenBase, mapWidth, mapHeight, buttonTileX, buttonTileY)) {
        RestoreStoredMegaButtonOriginalBgBlock(layerState);
        layerState->bgLastMode = 0xFFu;
    }

    if (!layerState->originalBgValid) {
        CaptureMegaButtonOriginalBgBlock(
            layerState,
            screenMap,
            screenBase,
            mapWidth,
            mapHeight,
            buttonTileX,
            buttonTileY);
        layerState->bgLastMode = 0xFFu;
    }

    const u32 tileBase =
        (mode == 1u) ? W2U_MEGA_NATIVE_BUTTON_TILE_BASE_NORMAL :
                       W2U_MEGA_NATIVE_BUTTON_TILE_BASE_ARMED;
    const u16 expectedFirstEntry =
        (u16)(tileBase | (W2U_MEGA_NATIVE_BUTTON_PALETTE << 12));
    if (mode == layerState->bgLastMode && screenMap[firstIndex] == expectedFirstEntry) {
        return;
    }

    if (mode == 1u) {
        WriteMegaButtonBgTiles(
            screenMap,
            mapWidth,
            mapHeight,
            buttonTileX,
            buttonTileY,
            tileBase);
    } else {
        WriteMegaButtonBgTiles(
            screenMap,
            mapWidth,
            mapHeight,
            buttonTileX,
            buttonTileY,
            tileBase);
    }

    layerState->bgLastMode = mode;
}

void UpdateMegaButtonBg()
{
    u8 mode = 0u;
    if (gMegaUiState.visible) {
        mode = gMegaUiState.selected ? 2u : 1u;
    }
    if (mode) {
        CopyMegaButtonPaletteToSubBgPltt();
    }

    UpdateMegaButtonBgLayer(W2U_MEGA_NATIVE_BG_VISIBLE_LAYER, mode);
}

void ClearStringParam(HandlerParam_StrParams* str)
{
    str->ID = 0;
    str->flags = 0;
    str->subProcID = 0;
    for (u32 i = 0; i < W2U_ARRAY_COUNT(str->args); ++i) {
        str->args[i] = 0;
    }
}

bool StringParamIsEnabled(const HandlerParam_StrParams* str)
{
    return str->flags != 0;
}

bool IsMegaMawileServerStateReady()
{
    return W2U_MegaVisualState.species == SPECIES_MAWILE &&
           W2U_MegaVisualState.form == 1 &&
           (W2U_MegaVisualState.usedSideMask & 1u) != 0;
}

u8 MegaTrainerClientForSlot(u8 pokemonSlot)
{
    return pokemonSlot & 1u;
}

const MegaEvolutionEntry* FindMegaEntry(SPECIES species, ITEM item)
{
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_MEGA_TABLE); ++idx) {
        const MegaEvolutionEntry* mega = &W2U_MEGA_TABLE[idx];
        if (mega->species == species && mega->item == item) {
            return mega;
        }
    }
    return nullptr;
}

void ResetPendingMega()
{
    gMegaState.selectedSlot = W2U_MEGA_NO_SLOT;
    gMegaState.selectedForm = W2U_MEGA_NO_FORM;
}

void ResetMegaBattleState()
{
    gMegaState.usedSideMask = 0;
    gMegaState.committedSideMask = 0;
    gMegaState.selectedSlot = W2U_MEGA_NO_SLOT;
    gMegaState.selectedForm = W2U_MEGA_NO_FORM;
    gMegaState.committedFormBySide[0] = W2U_MEGA_NO_FORM;
    gMegaState.committedFormBySide[1] = W2U_MEGA_NO_FORM;
    gMegaState.committedSlotBySide[0] = W2U_MEGA_NO_SLOT;
    gMegaState.committedSlotBySide[1] = W2U_MEGA_NO_SLOT;
    gMegaState.originalAbilityBySide[0] = W2U_MEGA_NO_ABILITY;
    gMegaState.originalAbilityBySide[1] = W2U_MEGA_NO_ABILITY;
    ClearMegaVisualState();
    ClearMegaButtonState(MEGA_SKIP_NONE);
}

u8 MegaSideForSlot(u8 battleSlot)
{
    return battleSlot & 1;
}

u8 MegaSideMaskForSlot(u8 battleSlot)
{
    return 1u << MegaSideForSlot(battleSlot);
}

void ReleaseCommittedMegaForm(u8 form)
{
    if (!form) {
        return;
    }

    for (u32 side = 0; side < W2U_ARRAY_COUNT(gMegaState.committedFormBySide); ++side) {
        if (gMegaState.committedFormBySide[side] == form) {
            gMegaState.committedFormBySide[side] = W2U_MEGA_NO_FORM;
            gMegaState.committedSlotBySide[side] = W2U_MEGA_NO_SLOT;
            gMegaState.committedSideMask &= ~(1u << side);
        }
    }
}

void ReleaseCommittedMegaSide(u8 side)
{
    if (side >= W2U_ARRAY_COUNT(gMegaState.committedFormBySide)) {
        return;
    }

    gMegaState.committedFormBySide[side] = W2U_MEGA_NO_FORM;
    gMegaState.committedSlotBySide[side] = W2U_MEGA_NO_SLOT;
    gMegaState.committedSideMask &= ~(1u << side);
}

bool IsMegaSideAvailable(u8 battleSlot)
{
    u8 sideMask = MegaSideMaskForSlot(battleSlot);
    return (gMegaState.usedSideMask & sideMask) == 0 &&
        (gMegaState.committedSideMask & sideMask) == 0;
}

bool CanSelectMegaCore(BattleMon* battleMon, u8* formOut, u32* skipReasonOut)
{
    if (!battleMon) {
        *skipReasonOut = MEGA_SKIP_NULL_MON;
        return false;
    }
    if (BattleMon_IsFainted(battleMon)) {
        *skipReasonOut = MEGA_SKIP_FAINTED;
        return false;
    }
    if (BattleMon_TransformCheck(battleMon)) {
        *skipReasonOut = MEGA_SKIP_TRANSFORMED;
        return false;
    }
    if (battleMon->form != 0) {
        *skipReasonOut = MEGA_SKIP_ALREADY_FORMED;
        return false;
    }
    if (!IsMegaSideAvailable(battleMon->battleSlot)) {
        *skipReasonOut = MEGA_SKIP_SIDE_USED;
        return false;
    }

    u8 form = W2U_CanMegaEvolve(battleMon);
    if (!form) {
        *skipReasonOut = MEGA_SKIP_NO_ENTRY;
        return false;
    }

    *formOut = form;
    *skipReasonOut = MEGA_SKIP_NONE;
    return true;
}

bool CanSelectMega(BattleMon* battleMon, u8* formOut)
{
    u32 skipReason = MEGA_SKIP_NONE;
    if (!CanSelectMegaCore(battleMon, formOut, &skipReason)) {
        return false;
    }

    return true;
}

bool IsSelectedMegaFor(BattleMon* battleMon)
{
    return battleMon &&
        gMegaState.selectedSlot == battleMon->battleSlot &&
        gMegaState.selectedForm != W2U_MEGA_NO_FORM;
}

bool IsActiveMonMegaForm(BattleMon* battleMon, u8* formOut)
{
    if (!battleMon) {
        return false;
    }

    const u8 megaForm = W2U_CanMegaEvolve(battleMon);
    if (megaForm == 0 || battleMon->form != megaForm) {
        return false;
    }

    if (formOut) {
        *formOut = megaForm;
    }
    return true;
}

void SelectMega(BattleMon* battleMon, u8 form)
{
    gMegaState.selectedSlot = battleMon->battleSlot;
    gMegaState.selectedForm = form;
}

void PlayMegaToggleSe(bool selected)
{
    GFL_SndSEPlay(selected ? W2U_SEQ_SE_DECIDE2 : W2U_SEQ_SE_CANCEL2);
}

void ToggleMegaSelectionForActiveMon(BtlvCore* btlCore, MegaToggleSource source)
{
    (void)source;

    BattleMon* activeMon = btlCore ? btlCore->activeMon : nullptr;
    if (IsActiveMonMegaForm(activeMon, nullptr)) {
        if (IsSelectedMegaFor(activeMon)) {
            ResetPendingMega();
        }
        return;
    }
    if (IsSelectedMegaFor(activeMon)) {
        ResetPendingMega();
        PlayMegaToggleSe(false);
        return;
    }

    u8 form = W2U_MEGA_NO_FORM;
    if (CanSelectMega(activeMon, &form)) {
        SelectMega(activeMon, form);
        PlayMegaToggleSe(true);
    }
}

void RefreshMegaButtonState(BtlvCore* btlCore)
{
    BattleMon* activeMon = btlCore ? btlCore->activeMon : nullptr;
    u8 form = W2U_MEGA_NO_FORM;
    if (IsActiveMonMegaForm(activeMon, &form)) {
        if (IsSelectedMegaFor(activeMon)) {
            ResetPendingMega();
        }
        gMegaUiState.visible = 1;
        gMegaUiState.enabled = 0;
        gMegaUiState.selected = 1;
        gMegaUiState.form = form;
        gMegaUiState.skipReason = MEGA_SKIP_ALREADY_FORMED;
        return;
    }

    u32 skipReason = MEGA_SKIP_NONE;
    if (!CanSelectMegaCore(activeMon, &form, &skipReason)) {
        if (IsSelectedMegaFor(activeMon)) {
            ResetPendingMega();
        }
        ClearMegaButtonState(skipReason);
        return;
    }

    gMegaUiState.visible = 1;
    gMegaUiState.enabled = 1;
    gMegaUiState.selected = IsSelectedMegaFor(activeMon) ? 1u : 0u;
    gMegaUiState.form = form;
    gMegaUiState.skipReason = MEGA_SKIP_NONE;
}

void SetMegaNativeButtonExist(void* biw)
{
    if (!biw) {
        return;
    }

    const u8 exists = (gMegaUiState.visible && gMegaUiState.enabled) ? 1u : 0u;
    u8* bytes = (u8*)biw;
    bytes[W2U_MEGA_NATIVE_BUTTON_EXIST_OFFSET + W2U_MEGA_NATIVE_BUTTON_INDEX] = exists;
}

const NativeInputHitTable* MegaNativeTouchTableFor(const NativeInputHitTable* touchTable)
{
    const u32 ptr = (u32)touchTable;
    if (ptr == W2U_MEGA_NATIVE_INPUT_TABLE_NORMAL_US) {
        return &W2U_MEGA_NATIVE_NORMAL_TOUCH_TABLE;
    }
    if (ptr == W2U_MEGA_NATIVE_INPUT_TABLE_TRIPLE_US) {
        return &W2U_MEGA_NATIVE_TRIPLE_TOUCH_TABLE;
    }

    return touchTable;
}

bool NativeHitIsMegaButton(u32 hit)
{
    return (hit & ~W2U_MEGA_NATIVE_WAZA_INFO_MASK) == W2U_MEGA_NATIVE_BUTTON_INDEX;
}

bool PollMegaButtonTouch(BtlvCore* btlCore)
{
    if (!gMegaUiState.visible || !gMegaUiState.enabled) {
        return false;
    }

    NativeTouchHitTriggerFn hitTrg =
        reinterpret_cast<NativeTouchHitTriggerFn>(W2U_GFL_UI_TP_HIT_TRG);
    const u32 hit = hitTrg(W2U_MEGA_DIRECT_TOUCH_TABLE);

    if (hit != 0u) {
        return false;
    }

    ToggleMegaSelectionForActiveMon(btlCore, MEGA_TOGGLE_SOURCE_TOUCH);
    RefreshMegaButtonState(btlCore);
    return true;
}

void CommitSelectedMegaAction(BattleActionParam* actionParam)
{
    if (gMegaState.selectedSlot == W2U_MEGA_NO_SLOT ||
        gMegaState.selectedForm == W2U_MEGA_NO_FORM) {
        return;
    }

    u8 side = MegaSideForSlot(gMegaState.selectedSlot);
    u8 sideMask = 1u << side;
    if ((gMegaState.usedSideMask & sideMask) != 0 ||
        (gMegaState.committedSideMask & sideMask) != 0) {
        ResetPendingMega();
        return;
    }

    W2U_BattleAction_SetMegaEvolution(actionParam, gMegaState.selectedForm);
    gMegaState.committedSideMask |= sideMask;
    gMegaState.committedFormBySide[side] = gMegaState.selectedForm;
    gMegaState.committedSlotBySide[side] = gMegaState.selectedSlot;
    ResetPendingMega();
}

ABILITY GetMegaFormAbility(const BattleMon* battleMon)
{
    return PML_PersonalGetParamSingle(battleMon->species, battleMon->form, Personal_Abil1);
}

u16 GetBaseAbilityForRestore(const BattleMon* battleMon, u16 ability)
{
    if (!battleMon || battleMon->species != SPECIES_MAWILE) {
        return ability;
    }

    const u8 megaForm = W2U_CanMegaEvolve((BattleMon*)battleMon);
    if (megaForm == 0) {
        return ability;
    }

    const u16 megaAbility =
        (u16)PML_PersonalGetParamSingle(battleMon->species, megaForm, Personal_Abil1);
    if (ability != megaAbility) {
        return ability;
    }

    return (u16)PML_PersonalGetParamSingle(battleMon->species, 0, Personal_Abil1);
}

u16 GetOriginalAbilityForSide(u8 side, BattleMon* battleMon, PartyPkm* partyPkm)
{
    u16 ability;
    if (side < W2U_ARRAY_COUNT(gMegaState.originalAbilityBySide) &&
        gMegaState.originalAbilityBySide[side] != W2U_MEGA_NO_ABILITY) {
        ability = gMegaState.originalAbilityBySide[side];
    } else {
        ability = (u16)PokeParty_GetParam(partyPkm, PF_Ability, nullptr);
    }
    return GetBaseAbilityForRestore(battleMon, ability);
}

void RepairLeakedBaseMegaAbility(BattleMon* battleMon)
{
    if (!battleMon ||
        battleMon->species != SPECIES_MAWILE ||
        battleMon->form != 0 ||
        !battleMon->partySrc) {
        return;
    }

    const u16 megaAbility =
        (u16)PML_PersonalGetParamSingle(battleMon->species, 1, Personal_Abil1);
    if (battleMon->ability != megaAbility &&
        (u16)PokeParty_GetParam(battleMon->partySrc, PF_Ability, nullptr) != megaAbility) {
        return;
    }

    const u16 baseAbility =
        (u16)PML_PersonalGetParamSingle(battleMon->species, 0, Personal_Abil1);
    battleMon->Type1 =
        (u8)PML_PersonalGetParamSingle(battleMon->species, 0, Personal_Type1);
    battleMon->Type2 =
        (u8)PML_PersonalGetParamSingle(battleMon->species, 0, Personal_Type2);
    battleMon->ability = baseAbility;
    battleMon->currentAbility = baseAbility;
    PokeParty_SetParam(battleMon->partySrc, PF_Forme, 0);
    PokeParty_SetParam(battleMon->partySrc, PF_Ability, baseAbility);
    PokeParty_RecalcStats(battleMon->partySrc);
}

void RepairLeakedBaseMegaAbilities(PokeCon* pokeCon)
{
    if (!pokeCon) {
        return;
    }

    for (u32 i = 0; i < W2U_ARRAY_COUNT(pokeCon->activeBattleMon); ++i) {
        RepairLeakedBaseMegaAbility(pokeCon->activeBattleMon[i]);
    }
}

void MirrorMegaFormToParty(BattleMon* battleMon)
{
    PartyPkm* partyPkm = battleMon->partySrc;
    if (!partyPkm) {
        return;
    }

    const u8 side = MegaSideForSlot(battleMon->battleSlot);
    if (side < W2U_ARRAY_COUNT(gMegaState.originalAbilityBySide) &&
        gMegaState.originalAbilityBySide[side] == W2U_MEGA_NO_ABILITY) {
        gMegaState.originalAbilityBySide[side] =
            (u16)PokeParty_GetParam(partyPkm, PF_Ability, nullptr);
    }

    PokeParty_SetParam(partyPkm, PF_Forme, battleMon->form);
    PokeParty_SetParam(partyPkm, PF_Ability, battleMon->ability);
    PokeParty_RecalcStats(partyPkm);
    if (battleMon->currentHP) {
        PokeParty_SetParam(partyPkm, PF_NowHP, battleMon->currentHP);
    }

    battleMon->maxHP = (u16)PokeParty_GetParam(partyPkm, PF_MaxHP, nullptr);
    if (battleMon->currentHP > battleMon->maxHP) {
        battleMon->currentHP = battleMon->maxHP;
        PokeParty_SetParam(partyPkm, PF_NowHP, battleMon->currentHP);
    }
    battleMon->attack = (u16)PokeParty_GetParam(partyPkm, PF_Attack, nullptr);
    battleMon->defense = (u16)PokeParty_GetParam(partyPkm, PF_Defense, nullptr);
    battleMon->speed = (u16)PokeParty_GetParam(partyPkm, PF_Speed, nullptr);
    battleMon->specialAttack = (u16)PokeParty_GetParam(partyPkm, PF_SpAttack, nullptr);
    battleMon->specialDefense = (u16)PokeParty_GetParam(partyPkm, PF_SpDefense, nullptr);

    RecordMegaVisualStats(battleMon);
}

void MirrorFormToParty(BattleMon* battleMon)
{
    PartyPkm* partyPkm = battleMon->partySrc;
    if (!partyPkm) {
        return;
    }

    PokeParty_SetParam(partyPkm, PF_Forme, battleMon->form);
    PokeParty_SetParam(partyPkm, PF_Ability, battleMon->ability);
    PokeParty_RecalcStats(partyPkm);
    if (battleMon->currentHP) {
        PokeParty_SetParam(partyPkm, PF_NowHP, battleMon->currentHP);
    }

    battleMon->maxHP = (u16)PokeParty_GetParam(partyPkm, PF_MaxHP, nullptr);
    if (battleMon->currentHP > battleMon->maxHP) {
        battleMon->currentHP = battleMon->maxHP;
        PokeParty_SetParam(partyPkm, PF_NowHP, battleMon->currentHP);
    }
    battleMon->attack = (u16)PokeParty_GetParam(partyPkm, PF_Attack, nullptr);
    battleMon->defense = (u16)PokeParty_GetParam(partyPkm, PF_Defense, nullptr);
    battleMon->speed = (u16)PokeParty_GetParam(partyPkm, PF_Speed, nullptr);
    battleMon->specialAttack = (u16)PokeParty_GetParam(partyPkm, PF_SpAttack, nullptr);
    battleMon->specialDefense = (u16)PokeParty_GetParam(partyPkm, PF_SpDefense, nullptr);

    RecordMegaVisualStats(battleMon);
}

void RestorePartyBaseForm(BattleMon* battleMon, u8 form)
{
    PartyPkm* partyPkm = battleMon->partySrc;
    if (!partyPkm) {
        return;
    }

    const u8 side = MegaSideForSlot(battleMon->battleSlot);
    const u16 ability = GetOriginalAbilityForSide(side, battleMon, partyPkm);
    PokeParty_SetParam(partyPkm, PF_Forme, form);
    PokeParty_SetParam(partyPkm, PF_Ability, ability);
    PokeParty_RecalcStats(partyPkm);

}

void ApplyMegaFormBattleData(BattleMon* battleMon)
{
    battleMon->Type1 = (u8)PML_PersonalGetParamSingle(battleMon->species, battleMon->form, Personal_Type1);
    battleMon->Type2 = (u8)PML_PersonalGetParamSingle(battleMon->species, battleMon->form, Personal_Type2);
    battleMon->ability = (u16)GetMegaFormAbility(battleMon);
    MirrorMegaFormToParty(battleMon);
    RecordMegaVisualBattleMon(battleMon);
}

void ApplyFormBattleData(BattleMon* battleMon)
{
    battleMon->Type1 =
        (u8)PML_PersonalGetParamSingle(battleMon->species, battleMon->form, Personal_Type1);
    battleMon->Type2 =
        (u8)PML_PersonalGetParamSingle(battleMon->species, battleMon->form, Personal_Type2);
    battleMon->ability =
        (u16)PML_PersonalGetParamSingle(battleMon->species, battleMon->form, Personal_Abil1);
    MirrorFormToParty(battleMon);
    RecordMegaVisualBattleMon(battleMon);
}

bool IsMegaMawileSummaryCacheCandidate(u16* entry)
{
    if (!entry || entry[0] != SPECIES_MAWILE) {
        return false;
    }

    if (entry[1] == 0 || entry[2] == 0 || entry[3] == 0 ||
        entry[4] == 0 || entry[5] == 0 || entry[7] == 0 ||
        entry[1] > 999 || entry[2] > 999 || entry[3] > 999 ||
        entry[4] > 999 || entry[5] > 999 || entry[7] > 999 ||
        entry[6] > entry[7]) {
        return false;
    }

    return true;
}

extern "C" void W2U_Mega_PatchKnownSummaryCache()
{
    if (W2U_MegaVisualState.species != SPECIES_MAWILE ||
        W2U_MegaVisualState.form != 1 ||
        W2U_MegaVisualState.visualOverrideReady == 0 ||
        W2U_MegaVisualState.mirroredPartyAttack == 0 ||
        W2U_MegaVisualState.mirroredPartyDefense == 0 ||
        W2U_MegaVisualState.mirroredPartySpeed == 0 ||
        W2U_MegaVisualState.mirroredPartySpAttack == 0 ||
        W2U_MegaVisualState.mirroredPartySpDefense == 0) {
        return;
    }

    u16* entry = (u16*)W2U_BATTLE_SUMMARY_CACHE_KNOWN_ADDRESS;
    if (!IsMegaMawileSummaryCacheCandidate(entry)) {
        return;
    }

    entry[1] = (u16)W2U_MegaVisualState.mirroredPartyAttack;
    entry[2] = (u16)W2U_MegaVisualState.mirroredPartyDefense;
    entry[3] = (u16)W2U_MegaVisualState.mirroredPartySpeed;
    entry[4] = (u16)W2U_MegaVisualState.mirroredPartySpAttack;
    entry[5] = (u16)W2U_MegaVisualState.mirroredPartySpDefense;
    if (W2U_MegaVisualState.mirroredPartyMaxHP != 0) {
        entry[7] = (u16)W2U_MegaVisualState.mirroredPartyMaxHP;
        if (entry[6] > entry[7]) {
            entry[6] = entry[7];
        }
    }
    entry[8] = ((u16)W2U_TYPE_DRAGON) | (((u16)W2U_TYPE_DRAGON) << 8);
    const u16 ability = (u16)W2U_MegaVisualState.mirroredPartyAbility;
    if (ability != 0) {
        entry[10] = ability;
        entry[0x30] = ability;
        entry[0x56] = ability;
    }
}

void ApplyMegaAbilityChange(ServerFlow* serverFlow, BattleMon* battleMon, u8 pokeID)
{
    ABILITY prevAbility = BattleMon_GetValue(battleMon, VALUE_ABILITY);
    ABILITY ability = GetMegaFormAbility(battleMon);

    u32 HEID = HEManager_PushState(&serverFlow->HEManager);
    ServerEvent_ChangeAbilityBefore(serverFlow, battleMon->battleSlot, prevAbility, ability);
    HEManager_PopState(&serverFlow->HEManager, HEID);

    AbilityEvent_RemoveItem(battleMon);
    battleMon->ability = (u16)ability;
    BattleMon_ChangeAbility(battleMon, (u16)ability);
    ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_ChangeAbility, pokeID, ability);
    AbilityEvent_AddItem(battleMon);

    HEID = HEManager_PushState(&serverFlow->HEManager);
    ServerEvent_ChangeAbilityAfter(serverFlow, battleMon->battleSlot);
    HEManager_PopState(&serverFlow->HEManager, HEID);

    if (!BattleMon_CheckIfMoveCondition(battleMon, CONDITION_GASTROACID) && prevAbility == ABIL_KLUTZ) {
        ServerControl_CheckItemReaction(serverFlow, battleMon, 0);
    }
}

bool ProcessMegaActionWork(ServerFlow* serverFlow, ActionOrderWork* actionWork)
{
    if (!serverFlow || !actionWork) {
        return false;
    }

    BattleActionParam* actionParam = &actionWork->action;
    if (BattleAction_GetAction(actionParam) != 1) {
        return false;
    }

    BattleMon* battleMon = actionWork->battleMon;
    u8 megaForm = W2U_BattleAction_CheckMegaEvolution(actionParam);
    if (!megaForm && battleMon) {
        u8 side = MegaSideForSlot(battleMon->battleSlot);
        u8 sideMask = 1u << side;
        if ((gMegaState.committedSideMask & sideMask) != 0 &&
            gMegaState.committedSlotBySide[side] == battleMon->battleSlot) {
            megaForm = gMegaState.committedFormBySide[side];
        }
    }
    if (!megaForm) {
        return false;
    }

    if (!battleMon ||
        BattleMon_IsFainted(battleMon) ||
        BattleMon_TransformCheck(battleMon) ||
        battleMon->form != 0 ||
        W2U_CanMegaEvolve(battleMon) != megaForm ||
        (gMegaState.usedSideMask & MegaSideMaskForSlot(battleMon->battleSlot)) != 0) {
        if (battleMon) {
            ReleaseCommittedMegaSide(MegaSideForSlot(battleMon->battleSlot));
        } else {
            ReleaseCommittedMegaForm(megaForm);
        }
        W2U_BattleAction_ResetMegaEvolution(actionParam);
        return false;
    }

    u8 pokemonSlot = battleMon->battleSlot;
    u8 sideMask = MegaSideMaskForSlot(pokemonSlot);
    gMegaState.usedSideMask |= sideMask;
    gMegaState.committedSideMask &= ~sideMask;
    gMegaState.committedFormBySide[MegaSideForSlot(pokemonSlot)] = W2U_MEGA_NO_FORM;
    gMegaState.committedSlotBySide[MegaSideForSlot(pokemonSlot)] = W2U_MEGA_NO_SLOT;
    W2U_MegaVisualState.usedSideMask = gMegaState.usedSideMask;

    HandlerParam_Message* syncMessage =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&syncMessage->str, 2u, BATTLE_MEGA_SYNC_MSGID);
    BattleHandler_AddArg(&syncMessage->str, pokemonSlot);
    BattleHandler_AddArg(&syncMessage->str, BattleMon_GetHeldItem(battleMon));
    BattleHandler_AddArg(&syncMessage->str, MegaTrainerClientForSlot(pokemonSlot));
    BattleHandler_PopWork(serverFlow, syncMessage);

    HandlerParam_Message* evolveMessage =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&evolveMessage->str, 2u, BATTLE_MEGA_EVOLVE_MSGID);
    BattleHandler_AddArg(&evolveMessage->str, pokemonSlot);
    BattleHandler_PopWork(serverFlow, evolveMessage);

    HandlerParam_ChangeForm* changeForm = (HandlerParam_ChangeForm*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
    changeForm->pokeID = pokemonSlot;
    changeForm->newForm = megaForm;
    ClearStringParam(&changeForm->exStr);
    BattleHandler_PopWork(serverFlow, changeForm);

    W2U_BattleAction_ResetMegaEvolution(actionParam);
    return true;
}

}

extern "C" u8 W2U_CanMegaEvolve(BattleMon* battleMon)
{
    if (!battleMon) {
        return 0;
    }

    const MegaEvolutionEntry* mega = FindMegaEntry(battleMon->species, battleMon->heldItem);
    return mega ? mega->form : 0;
}

extern "C" u32 W2U_Mega_WrapNativeInputCheckKey(
    void* biw,
    const NativeInputHitTable* touchTable,
    const void* keyTable,
    const void* moveTable,
    u32 hit,
    u32 henshinFlag)
{
    RefreshMegaButtonState(gMegaActiveBtlCore);
    SetMegaNativeButtonExist(biw);

    NativeInputCheckKeyFn checkKey =
        reinterpret_cast<NativeInputCheckKeyFn>(W2U_MEGA_NATIVE_CHECK_KEY);
    return checkKey(
        biw,
        MegaNativeTouchTableFor(touchTable),
        keyTable,
        moveTable,
        hit,
        henshinFlag);
}

extern "C" u32 W2U_Mega_OnNativeMoveSelectInputAfter(
    void*,
    u8* wazaInfoModeOut,
    u32* hitOut,
    u32 result)
{
    if (!result || !hitOut) {
        return result;
    }

    const u32 hit = *hitOut;
    if (!NativeHitIsMegaButton(hit)) {
        return result;
    }

    *hitOut = W2U_MEGA_NATIVE_HIT_NONE;
    if (wazaInfoModeOut) {
        *wazaInfoModeOut = 0;
    }

    if (gMegaUiState.visible && gMegaUiState.enabled) {
        ToggleMegaSelectionForActiveMon(gMegaActiveBtlCore, MEGA_TOGGLE_SOURCE_TOUCH);
        RefreshMegaButtonState(gMegaActiveBtlCore);
        UpdateMegaButtonBg();
    }

    return 0u;
}

extern "C" bool W2U_Mega_OnActionOrderHook()
{
    if (gMegaState.committedSideMask == 0) {
        return false;
    }

    return true;
}

extern "C" void W2U_Mega_ProcessCurrentAction(ServerFlow* serverFlow, ActionOrderWork* actionWork)
{
    if (gMegaState.committedSideMask == 0) {
        return;
    }

    ProcessMegaActionWork(serverFlow, actionWork);
}

extern "C" ITEM W2U_GetMegaStone(SPECIES species)
{
    for (u32 idx = 0; idx < W2U_ARRAY_COUNT(W2U_MEGA_TABLE); ++idx) {
        if (W2U_MEGA_TABLE[idx].species == species) {
            return W2U_MEGA_TABLE[idx].item;
        }
    }
    return ITEM_NULL;
}

extern "C" void W2U_BattleAction_SetMegaEvolution(BattleActionParam* actionParam, u8 form)
{
    actionParam->baFight.pad = form;
}

extern "C" void W2U_BattleAction_ResetMegaEvolution(BattleActionParam* actionParam)
{
    actionParam->baFight.pad = 0;
}

extern "C" u8 W2U_BattleAction_CheckMegaEvolution(const BattleActionParam* actionParam)
{
    return actionParam->baFight.pad;
}

extern "C" void W2U_Mega_OnActionSelectRoot(BattleActionParam* actionParam)
{
    ReleaseCommittedMegaForm(W2U_BattleAction_CheckMegaEvolution(actionParam));
    ResetPendingMega();
    ClearMegaButtonState(MEGA_SKIP_NONE);
    UpdateMegaButtonBg();
}

extern "C" void W2U_Mega_OnActionSelectFightWait(BtlvCore* btlCore)
{
    gMegaActiveBtlCore = btlCore;
    if ((GCTX_HIDGetPressedKeys() & W2U_KEY_START) == W2U_KEY_START) {
        ToggleMegaSelectionForActiveMon(btlCore, MEGA_TOGGLE_SOURCE_START);
    }
    RefreshMegaButtonState(btlCore);
}

extern "C" void W2U_Mega_OnActionSelectFightPostWait(BtlvCore* btlCore)
{
    gMegaActiveBtlCore = btlCore;
    RefreshMegaButtonState(btlCore);
    PollMegaButtonTouch(btlCore);
    UpdateMegaButtonBg();
}

extern "C" void W2U_Mega_OnActionSelected(BattleActionParam* actionParam, u32 action)
{
    if (action == 1) {
        CommitSelectedMegaAction(actionParam);
    } else if (action) {
        ResetPendingMega();
    }
    ClearMegaButtonState(MEGA_SKIP_NONE);
    UpdateMegaButtonBg();
    gMegaActiveBtlCore = nullptr;
}

extern "C" void W2U_DISABLED_THUMB_BRANCH_BattleAction_SetFightParam(BattleActionParam* actionParam, u32 moveID, u32 targetPos)
{
    u8 megaForm = W2U_BattleAction_CheckMegaEvolution(actionParam);
    actionParam->baFight.cmd = 1;
    actionParam->baFight.targetPos = targetPos;
    actionParam->baFight.moveID = moveID;
    W2U_BattleAction_SetMegaEvolution(actionParam, megaForm);
}

extern "C" bool THUMB_BRANCH_BattleHandler_ChangeForm(ServerFlow* serverFlow, HandlerParam_ChangeForm* params)
{
    BattleMon* battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, params->pokeID);
    if (!battleMon ||
        BattleMon_IsFainted(battleMon) ||
        BattleMon_TransformCheck(battleMon) ||
        BattleMon_GetValue(battleMon, VALUE_FORM) == params->newForm) {
        return false;
    }

    if ((params->header.flags & HANDLER_ABILITY_POPUP_FLAG) != 0) {
        ServerDisplay_AbilityPopupAdd(serverFlow, battleMon);
    }

    BattleMon_ChangeForm(battleMon, params->newForm);
    u8 megaForm = W2U_CanMegaEvolve(battleMon);
    bool changedToMegaForm = megaForm && megaForm == battleMon->form;
    if (changedToMegaForm) {
        ApplyMegaFormBattleData(battleMon);
    } else {
        ApplyFormBattleData(battleMon);
    }
    ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_ChangeForm, params->pokeID, params->newForm);
    if (StringParamIsEnabled(&params->exStr)) {
        BattleHandler_SetString(serverFlow, &params->exStr);
    }

    if ((params->header.flags & HANDLER_ABILITY_POPUP_FLAG) != 0) {
        ServerDisplay_AbilityPopupRemove(serverFlow, battleMon);
    }

    if (changedToMegaForm) {
        ApplyMegaAbilityChange(serverFlow, battleMon, params->pokeID);
    }

    return true;
}

extern "C" void W2U_Mega_OnClientChangeFormStart(const u32* args, u32 viewPos)
{
    (void)viewPos;
    ClearMegaVisualClientState();

    if (!args) {
        return;
    }

    const u32 pokeID = args[0] & 0xffu;
    const u32 form = args[1] & 0xffu;
    W2U_MegaVisualState.clientChangeFormPokeID = pokeID;
    W2U_MegaVisualState.clientChangeFormForm = form;
}

extern "C" void W2U_Mega_OnClientChangeFormWait(const u32* args, u32 waitResult)
{
    if (waitResult == 0 || !args) {
        return;
    }

    const u32 pokeID = args[0] & 0xffu;
    const u32 form = args[1] & 0xffu;
    W2U_MegaVisualState.clientChangeFormPokeID = pokeID;
    W2U_MegaVisualState.clientChangeFormForm = form;

    if (IsMegaMawileServerStateReady()) {
        W2U_MegaVisualState.visualOverrideReady = 1u;
    }
}

extern "C" void W2U_Mega_ProcessActionOrder(ServerFlow* serverFlow)
{
    if (!serverFlow) {
        return;
    }

    for (u32 actionIdx = 0; actionIdx < serverFlow->numActOrder; ++actionIdx) {
        ProcessMegaActionWork(serverFlow, &serverFlow->actionOrderWork[actionIdx]);
    }
}

extern "C" void THUMB_BRANCH_LINK_ServerFlow_SetupBeforeFirstTurn_0x6E(
    ServerFlow* serverFlow,
    u32 clientID,
    u32 switchInSlot,
    u32 switchOutSlot)
{
    ResetMegaBattleState();
    W2U_AuraField_ResetBattleState();
    W2U_MoveState_ResetBattleState();
    RepairLeakedBaseMegaAbilities(serverFlow ? serverFlow->pokeCon : nullptr);
    ServerControl_SwitchInCore(serverFlow, clientID, switchInSlot, switchOutSlot);
    RepairLeakedBaseMegaAbilities(serverFlow ? serverFlow->pokeCon : nullptr);
}

extern "C" void THUMB_BRANCH_BattleMon_UpdateData(BattleMon* battleMon, bool resetForm)
{
    PartyPkm* partyPkm = battleMon->partySrc;
    PokeParty_SetParam(battleMon->partySrc, PF_Experience, battleMon->experience);
    PokeParty_SetParam(partyPkm, PF_NowHP, battleMon->currentHP);

    u32 status = 0;
    if (battleMon->currentHP) {
        status = BattleMon_GetStatus(battleMon);
    }
    PokeParty_SetParam(partyPkm, PF_StatusCond, status);

    BattleMon_SetMovesAndPP(battleMon);

    u8 form = battleMon->form;
    const u8 megaForm = W2U_CanMegaEvolve(battleMon);
    if ((megaForm != 0 && form == megaForm) ||
        (battleMon->flags & 0x20) != 0 ||
        resetForm) {
        form = battleMon->flags & 0x1F;
        RestorePartyBaseForm(battleMon, form);
    } else {
        PokeParty_SetParam(partyPkm, PF_Forme, form);
        PokeParty_RecalcStats(partyPkm);
    }
    PokeParty_SetParam(partyPkm, PF_Item, battleMon->heldItem);
    W2U_MoveState_ClearExtraType(battleMon->battleSlot);
}

static bool W2U_AbilityPreservesFormOnSwitchOut(ABILITY ability)
{
    return ability == ABIL_DISGUISE;
}

extern "C" void THUMB_BRANCH_BattleMon_ClearForSwitchOut(BattleMon* battleMon)
{
    sys_memset(battleMon->turnFlag, 0, 2u);
    W2U_MoveState_ClearExtraType(battleMon->battleSlot);
    BattleMon_ClearTransformChange(battleMon);
    MoveWork_ClearSurface(battleMon);
    BattleMon_ClearUsedMoveFlag(battleMon);
    ClearCounter(battleMon);
    BattleMon_ClearComboMoveData(battleMon);
    BattleMon_IllusionBreak(battleMon);
    if (!BattleMon_GetConditionFlag(battleMon, CONDITIONFLAG_BATONPASS)) {
        BattleMon_RemoveSubstitute(battleMon);
        ClearMoveStatusWork(battleMon, false);
        ResetStatStages(&battleMon->statStageParam);
        sys_memset(battleMon->conditionFlag, 0, 2u);
    }

    u8 megaForm = W2U_CanMegaEvolve(battleMon);
    if (!W2U_AbilityPreservesFormOnSwitchOut(battleMon->currentAbility) &&
        (!megaForm || megaForm != battleMon->form)) {
        battleMon->form = battleMon->flags & 0x1F;
        battleMon->currentAbility = battleMon->ability;
    } else {
        battleMon->currentAbility = PokeParty_GetParam(battleMon->partySrc, PF_Ability, nullptr);
    }

    RestorePartyBaseForm(battleMon, battleMon->form);
}

extern "C" bool THUMB_BRANCH_HandlerCommon_IsUnremovableItem(BattleMon* battleMon, ITEM itemID)
{
    if (GiratinaArceusGenesectItemCheck(battleMon, itemID)) {
        return true;
    }

    ITEM megaStone = W2U_GetMegaStone(battleMon->species);
    return megaStone != ITEM_NULL && megaStone == itemID;
}

#endif
