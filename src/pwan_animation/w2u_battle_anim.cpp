#include "Species.h"
#include "nds/fs.h"
#include "pwan_types.h"
#include "string.h"
#include "w2u_pwan_archive.h"

#define W2U_PWAN_MAGIC 0x4E415750u
#define W2U_FRAME_BYTES 0x1200u
#define W2U_MCSS_TEX_BYTES 0x4000u
#define W2U_MCSS_TEX_WIDTH 256u
#define W2U_MCSS_TEX_STRIDE_BYTES (W2U_MCSS_TEX_WIDTH / 2u)
#define W2U_VISIBLE_TEX_WIDTH 96u
#define W2U_VISIBLE_TEX_HEIGHT 96u
#define W2U_VISIBLE_TEX_ROW_BYTES (W2U_VISIBLE_TEX_WIDTH / 2u)
#define W2U_VISIBLE_TEX_ROW_HALFWORDS (W2U_VISIBLE_TEX_ROW_BYTES / 2u)
#define W2U_VISIBLE_TEX_BYTES (W2U_VISIBLE_TEX_ROW_BYTES * W2U_VISIBLE_TEX_HEIGHT)
#define W2U_STAGING_TEX_BYTES (W2U_MCSS_TEX_STRIDE_BYTES * W2U_VISIBLE_TEX_HEIGHT)
#define W2U_LEGACY_TEX_BYTES_AVOIDED (W2U_MCSS_TEX_BYTES - W2U_VISIBLE_TEX_BYTES)
#define W2U_MCSS_TEX_BASE 0x24000u
#define W2U_MCSS_TEX_SLOT_BYTES 0x4000u
#define W2U_MCSS_TEX_SLOT_COUNT 8u
#define W2U_PWAN_PLTT_BASE 0x1800u
#define W2U_MCSS_PLTT_SLOT_BYTES 0x20u
#define W2U_LCDC_TEX_VRAM ((volatile u16 *)0x06800000)
#define W2U_LCDC_TEX_PLTT ((volatile u16 *)0x06890000)
#define W2U_OBJ_OAM ((volatile u16 *)0x07000000)
#define W2U_OBJ_VRAM ((volatile u16 *)0x06400000)
#define W2U_OBJ_PLTT ((volatile u16 *)0x05000200)
#define W2U_REG_DISPCNT ((volatile u32 *)0x04000000)
#define W2U_VRAMCNT_A ((volatile u8 *)0x04000240)
#define W2U_VRAMCNT_B ((volatile u8 *)0x04000241)
#define W2U_VRAMCNT_C ((volatile u8 *)0x04000242)
#define W2U_VRAMCNT_D ((volatile u8 *)0x04000243)
#define W2U_VRAMCNT_E ((volatile u8 *)0x04000244)
#define W2U_VRAMCNT_F ((volatile u8 *)0x04000245)
#define W2U_VRAMCNT_G ((volatile u8 *)0x04000246)
#define W2U_VRAM_LCDC_ENABLE 0x80u
#define W2U_VRAMCNT_ENABLE 0x80u
#define W2U_VRAMCNT_MST_MAIN_OBJ 0x02u
#define W2U_DISPCNT_OBJ_ENABLE (1u << 12)
#define W2U_DISPCNT_OBJ_1D_MAP (1u << 4)
#define W2U_REG_VCOUNT ((volatile u16 *)0x04000006)
#define W2U_MCSS_VCOUNT_LOW 192u
#define W2U_MCSS_VCOUNT_HIGH 200u
#define W2U_OBJ_1D_64K_BLOCK_BYTES 64u
#define W2U_OBJ_FRAME_VRAM_OFFSET 0x7000u
#define W2U_OBJ_TILE_BASE (W2U_OBJ_FRAME_VRAM_OFFSET / W2U_OBJ_1D_64K_BLOCK_BYTES)
#define W2U_OBJ_PLT 15u
#define W2U_OBJ_PRIORITY 1u
#define W2U_BATTLE_OBJ_INDEX 124u
#define W2U_BATTLE_OBJ_X 44u
#define W2U_BATTLE_OBJ_Y 74u
#define W2U_BTLV_BEW_PTR ((void **)0x021F4280)
#define W2U_BATTLE_SPRITE_SYSTEM_OFFSET 0x190u
#define W2U_BATTLE_SUMMARY_CACHE_KNOWN_ADDRESS 0x022C4760u
#define W2U_BATTLE_SUMMARY_CACHE_SCAN_START 0x022C0000u
#define W2U_BATTLE_SUMMARY_CACHE_SCAN_END 0x022E0000u
#define W2U_BATTLE_SUMMARY_CACHE_SCAN_COOLDOWN 16u
#define W2U_BTLV_POS_AA 0
#define W2U_BTLV_POS_BB 1
#define W2U_BTLV_POS_A 2
#define W2U_BTLV_POS_B 3
#define W2U_BTLV_POS_C 4
#define W2U_BTLV_POS_D 5
#define W2U_BTLV_POS_E 6
#define W2U_BTLV_POS_F 7
#define W2U_BATTLE_PROFILE_MAGIC 0x46525042u
#define W2U_BATTLE_PROFILE_VERSION 18u
#define W2U_BATTLE_DIRECT_OBJ_MAWILE 0u
#define W2U_BATTLE_ACTOR_ENTRY_BASE 0x08u
#define W2U_BATTLE_ACTOR_ENTRY_BYTES 0x5cu
#define W2U_BATTLE_ACTOR_SPECIES_OFFSET 0x2cu
#define W2U_BATTLE_ACTOR_FORM_OFFSET 0x30u
#define W2U_BATTLE_SPECIES_FORM_MASK 0x7ffu
#define W2U_MEGA_VISUAL_STATE_MAGIC 0x53564D57u
#define W2U_MEGA_VISUAL_STATE_VERSION 1u
#define W2U_MEGA_VISUAL_STATE_MAX_SIZE 128u
#define W2U_MCSS_BASE_PLTT_DATA_OFFSET 0xd4u
#define W2U_MCSS_FADE_PLTT_DATA_OFFSET 0xd8u
#define W2U_MCSS_PLTT_DATA_SIZE_OFFSET 0xdcu
#define W2U_MCSS_PALETTE_PROXY_VRAM_OFFSET 0xc8u
#define W2U_MAIN_RAM_START 0x02000000u
#define W2U_MAIN_RAM_END 0x02400000u
#define W2U_MAWILE_MEGA_SPECIES 303u
#define W2U_MAWILE_MEGA_FORM 1u
#define W2U_MAWILE_BASE_SPRITE_INDEX 303u
#define W2U_MAWILE_MEGA_FORM_SPRITE_INDEX 783u
#define W2U_MAWILE_MEGA_FORM_SPRITE_BASE (W2U_MAWILE_MEGA_FORM_SPRITE_INDEX * 20u)
#define W2U_MAWILE_MEGA_PACKED_MONS (W2U_MAWILE_MEGA_SPECIES | (W2U_MAWILE_MEGA_FORM << 11))
#define W2U_TYPE_STEEL 8u
#define W2U_TYPE_DRAGON 15u
#define W2U_TYPE_FAIRY 17u
#define W2U_MEGA_VISUAL_SETTLE_FRAMES 0u
#define W2U_MEGA_VISUAL_REVEAL_HOLD_FRAMES 0u
#define W2U_MEGA_PWAN_STREAM_DELAY_FRAMES 3u

namespace w2u {
namespace battle_anim {

struct PwanHeader {
    u32 magic;
    u16 version;
    u16 width;
    u16 height;
    u16 bpp;
    u16 frameCount;
    u16 timelineCount;
    u32 totalTicks;
    u32 frameBytes;
    u32 paletteColors;
    u32 paletteOffset;
    u32 timelineOffset;
    u32 frameOffset;
};

struct PwanTimelineEntry {
    u16 frame;
    u16 ticks;
};

struct RuntimeTimelineEntry {
    u8 frame;
    u8 ticks;
};

#define W2U_PWAN_MAX_OVERRIDES 500u
#define W2U_PWAN_MAX_ASSET_INDEX 1094u
#define W2U_PWAN_ASSET_COUNT ((W2U_PWAN_MAX_ASSET_INDEX + 1u) * 2u)
#define W2U_PWAN_MAX_TIMELINE 192u

typedef W2U_PwanConfigHeader PwanConfigHeader;
typedef W2U_PwanConfigEntry PwanConfigEntry;

struct BattleActorIdentity {
    s32 rawMonsNo;
    u16 species;
    u16 form;
};

struct McssAddWork {
    u32 arcID;
    u32 ncbr;
    u32 nclr;
    u32 ncer;
    u32 nanr;
    u32 nmcr;
    u32 nmar;
    u32 ncec;
    u32 heapLow;
};

struct MegaVisualStateMirror {
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

enum ActorId {
    ACTOR_SINGLE_PLAYER_BACK = 0,
    ACTOR_SINGLE_ENEMY_FRONT = 1,
    ACTOR_MULTI_PLAYER_0_BACK = 2,
    ACTOR_MULTI_ENEMY_0_FRONT = 3,
    ACTOR_MULTI_PLAYER_1_BACK = 4,
    ACTOR_MULTI_ENEMY_1_FRONT = 5,
    ACTOR_MULTI_PLAYER_2_BACK = 6,
    ACTOR_MULTI_ENEMY_2_FRONT = 7,
    ACTOR_COUNT = 8,
};

enum BattleAssetId {
    ASSET_NONE = 0xffffu,
};

#define ASSET_COUNT W2U_PWAN_ASSET_COUNT

struct ActorConfig {
    u8 position;
};

struct Asset {
    b32 loaded;
    u32 assetId;
    PwanHeader header;
    RuntimeTimelineEntry timeline[W2U_PWAN_MAX_TIMELINE];
    u16 palette[16];
};

struct ActorState {
    b32 active;
    b32 directObj;
    b32 textureDirty;
    b32 paletteDirty;
    u32 tick;
    u16 copiedFrame;
    u16 pendingFrame;
    s16 mcssIndex;
    u16 species;
    u16 form;
    u16 assetId;
    b32 mcssMawPatched;
    void *mcss;
};

#if !W2U_PWAN_DIAGNOSTICS
#define u32 w2u::pwan_profile::SinkWord
#define s32 w2u::pwan_profile::SinkWord
#endif
struct BattleAnimProfile {
    u32 magic;
    u32 version;
    u32 structSize;
    u32 drawCalls;
    u32 waitCalls;
    u32 waitSpinIterations;
    u32 maxWaitSpinIterations;
    u32 textureUploadCalls;
    u32 textureUploadActors;
    u32 textureBytesUploaded;
    u32 legacyTextureBytesAvoided;
    u32 lastUploadBytes;
    u32 lastUploadActors;
    u32 lastVcountBeforeWait;
    u32 lastVcountAfterWait;
    u32 updateCalls;
    u32 nullBewCount;
    u32 nullBmwCount;
    u32 lastBew;
    u32 lastBmw;
    u32 mcssIndexCalls;
    u32 mcssIndexValid;
    u32 mcssIndexInvalid;
    u32 lastMcssIndexPosition;
    s32 lastMcssIndexResult;
    u32 monsReadCalls;
    u32 entryNullCount;
    u32 monsInvalidCount;
    u32 lastEntry;
    u32 lastEntryMcss;
    s32 lastEntryMons;
    u32 loadFailCount;
    u32 stageFailCount;
    u32 lastLoadFailActor;
    u32 lastLoadFailAsset;
    u32 lastStageFailActor;
    u32 lastStageFailAsset;
    u32 lastStageFailFrame;
    u32 lastActiveMask;
    u32 lastTextureDirtyMask;
    u32 actorPosition[ACTOR_COUNT];
    s32 actorMcssIndex[ACTOR_COUNT];
    u32 actorSpecies[ACTOR_COUNT];
    u32 actorForm[ACTOR_COUNT];
    s32 actorRawMons[ACTOR_COUNT];
    u32 actorAsset[ACTOR_COUNT];
    u32 actorFrame[ACTOR_COUNT];
    u32 paletteUploadCalls;
    u32 paletteCpuCopyCalls;
    u32 paletteCpuCopyFailCount;
    u32 lastPaletteActor;
    u32 lastPaletteAsset;
    u32 lastPaletteMcss;
    u32 lastPaletteBase;
    u32 lastPaletteFade;
    u32 lastPaletteSize;
    u32 lastConfigVersion;
    u32 lastConfigMatchMode;
    u32 lastDecodedSpecies;
    u32 lastDecodedForm;
    u32 megaProfileScanCalls;
    u32 megaProfileFound;
    u32 megaProfileAddress;
    u32 megaOverrideCalls;
    u32 megaOverrideMatches;
    u32 objDrawCalls;
    u32 objHideCalls;
    u32 objFrameCopyCalls;
    u32 objFrameReadFailCount;
    u32 nativeHideCalls;
    u32 nativeRestoreCalls;
    u32 directActor;
    u32 directAsset;
    u32 directFrame;
    u32 lastObjDispcnt;
    u32 lastObjVramcntE;
    u32 lastOamAttr0[4];
    u32 lastOamAttr1[4];
    u32 lastOamAttr2[4];
    u32 actorIdentityPatchCalls;
    u32 actorIdentityPatchMatches;
    u32 lastActorIdentityPatchPosition;
    u32 lastActorIdentityPatchOldRaw;
    u32 lastActorIdentityPatchNewRaw;
    u32 mawPatchCalls;
    u32 mawPatchMatches;
    u32 lastMawPatchPosition;
    u32 lastMawPatchOldNcbr;
    u32 lastMawPatchNewNcbr;
    u32 megaVisualSettleFrames;
    u32 megaVisualSettleReady;
    u32 megaVisualSuppressCalls;
    u32 megaVisualRestoreCalls;
    u32 megaVisualFirstFrameUploaded;
    u32 megaVisualRevealHoldFrames;
    u32 megaPwanStreamDelayFrames;
    u32 megaPwanStreamingReady;
    u32 megaStaticMawPatchCalls;
    u32 megaStaticMawPatchMatches;
    u32 megaSummaryCachePatchCalls;
    u32 megaSummaryCachePatchMatches;
    u32 megaSummaryCacheScanCalls;
    u32 megaSummaryCacheAddress;
    u32 megaSummaryCacheLastSpecies;
    u32 megaSummaryCacheLastAttack;
    u32 megaSummaryCacheLastDefense;
    u32 megaSummaryCacheLastSpeed;
    u32 megaSummaryCacheLastSpAttack;
    u32 megaSummaryCacheLastSpDefense;
    u32 megaSummaryCacheLastCurrentHP;
    u32 megaSummaryCacheLastMaxHP;
    u32 megaSummaryCacheLastTypeWord;
    u32 megaSummaryCacheLastAbilityWord;
};
#if !W2U_PWAN_DIAGNOSTICS
#undef s32
#undef u32
#endif

struct State {
    Asset asset[ACTOR_COUNT];
    ActorState actor[ACTOR_COUNT];
    u8 nextUploadActor;
    b32 savedVramcntEValid;
    u8 savedVramcntE;
    u8 megaVisualSettleFrames;
    u8 megaVisualRevealHoldFrames;
    u8 megaPwanStreamDelayFrames;
    b32 megaVisualReadyObserved;
    b32 megaVisualFirstFrameUploaded;
    b32 megaPwanStreamingReady;
    b32 megaVisualSuppressed;
    void *megaVisualSuppressedMcss;
    u32 megaSummaryCacheAddress;
    u8 megaSummaryCacheScanCooldown;
};

#if W2U_PWAN_DIAGNOSTICS
extern "C" {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
volatile BattleAnimProfile W2U_BattleAnim_Profile = {
    W2U_BATTLE_PROFILE_MAGIC,
    W2U_BATTLE_PROFILE_VERSION,
    sizeof(BattleAnimProfile),
};
#pragma GCC diagnostic pop
}
#else
static BattleAnimProfile W2U_BattleAnim_Profile;
#endif

static const ActorConfig kActorConfig[ACTOR_COUNT] = {
    {W2U_BTLV_POS_AA},
    {W2U_BTLV_POS_BB},
    {W2U_BTLV_POS_A},
    {W2U_BTLV_POS_B},
    {W2U_BTLV_POS_C},
    {W2U_BTLV_POS_D},
    {W2U_BTLV_POS_E},
    {W2U_BTLV_POS_F},
};

static State sState;
static u8 *const sFrameScratch = W2U_PwanFrameScratch;
static u8 *const sTextureScratch = W2U_PwanTextureScratch;
static volatile MegaVisualStateMirror *sMegaVisualState;

typedef s32 (*McssGetIndexFn)(void *bmw, int position);
typedef void (*McssFlagFn)(void *mcss);
typedef void (*McssShadowVanishFn)(void *mcss, u8 flag);
typedef void (*McssOverwriteMawFn)(void *bmw, int position, const McssAddWork *maw);

static b32 IsSafeMcssTextureIndex(s32 mcssIndex);
static void HideOam();
static void RestoreNativeVramMapping();

static McssGetIndexFn const BattleSpriteGetIndex_Fn = (McssGetIndexFn)0x021E97D5u;
static McssFlagFn const MCSS_SetVanishFlag_Fn = (McssFlagFn)0x0201ADA9u;
static McssFlagFn const MCSS_ResetVanishFlag_Fn = (McssFlagFn)0x0201ADB9u;
static McssShadowVanishFn const MCSS_SetShadowVanishFlag_Fn =
    (McssShadowVanishFn)0x0201AEF9u;
static McssOverwriteMawFn const BattleSpriteOverwriteMaw_Fn =
    (McssOverwriteMawFn)0x021E7FBDu;
extern "C" void W2U_BattleAnim_Term(void);

static b32 ReadRange(BattleAssetId assetId, u32 offset, void *buffer, u32 size)
{
    if ((u32)assetId >= ASSET_COUNT) return false;
    return w2u::pwan_archive::ReadMemberRange(
        w2u::pwan_archive::MemberIdForAsset((u32)assetId), offset, buffer, size);
}

static b32 ReadConfigRange(u32 offset, void *buffer, u32 size)
{
    return w2u::pwan_archive::ReadMemberRange(W2U_PWAN_CONFIG_MEMBER_ID, offset, buffer, size);
}

static b32 LoadAsset(ActorId actor, BattleAssetId assetId)
{
    if (assetId >= ASSET_COUNT) {
        return false;
    }

    Asset *asset = &sState.asset[actor];
    if (asset->loaded && asset->assetId == (u32)assetId) {
        return true;
    }
    asset->loaded = false;
    asset->assetId = (u32)assetId;

    if (!ReadRange(assetId, 0, &asset->header, sizeof(asset->header))) {
        return false;
    }
    if (asset->header.magic != W2U_PWAN_MAGIC ||
        asset->header.version != 1 ||
        asset->header.width != 96 ||
        asset->header.height != 96 ||
        asset->header.bpp != 4 ||
        asset->header.frameBytes != W2U_FRAME_BYTES ||
        asset->header.paletteColors != 16 ||
        asset->header.timelineCount > W2U_PWAN_MAX_TIMELINE) {
        return false;
    }

    if (!ReadRange(assetId, asset->header.paletteOffset, asset->palette, sizeof(asset->palette))) {
        return false;
    }
    PwanTimelineEntry fileTimeline[W2U_PWAN_MAX_TIMELINE];
    if (!ReadRange(assetId, asset->header.timelineOffset, fileTimeline,
                   asset->header.timelineCount * sizeof(fileTimeline[0]))) {
        return false;
    }
    for (u32 i = 0; i < asset->header.timelineCount; ++i) {
        if (fileTimeline[i].frame > 0xffu || fileTimeline[i].ticks > 0xffu) {
            return false;
        }
        asset->timeline[i].frame = (u8)fileTimeline[i].frame;
        asset->timeline[i].ticks = (u8)fileTimeline[i].ticks;
    }

    asset->loaded = true;
    return true;
}

static b32 IsLikelyMainRamPointer(const void *ptr)
{
    const u32 value = (u32)ptr;
    return value >= W2U_MAIN_RAM_START && value < W2U_MAIN_RAM_END;
}

static void *GetMcssPointerByIndex(void *bmw, s32 mcssIndex)
{
    if (!bmw || !IsSafeMcssTextureIndex(mcssIndex)) {
        return 0;
    }
    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)mcssIndex * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    return *(void **)entry;
}

static void CopyPaletteToLiveMcss(ActorId actor)
{
    const BattleAssetId assetId = (BattleAssetId)sState.actor[actor].assetId;
    if (assetId >= ASSET_COUNT) {
        return;
    }

    Asset *asset = &sState.asset[actor];
    void *mcss = sState.actor[actor].mcss;
    W2U_BattleAnim_Profile.lastPaletteActor = (u32)actor;
    W2U_BattleAnim_Profile.lastPaletteAsset = (u32)assetId;
    W2U_BattleAnim_Profile.lastPaletteMcss = (u32)mcss;

    if (!IsLikelyMainRamPointer(mcss)) {
        W2U_BattleAnim_Profile.paletteCpuCopyFailCount =
            W2U_BattleAnim_Profile.paletteCpuCopyFailCount + 1u;
        return;
    }

    u16 *base = *(u16 **)((u8 *)mcss + W2U_MCSS_BASE_PLTT_DATA_OFFSET);
    u16 *fade = *(u16 **)((u8 *)mcss + W2U_MCSS_FADE_PLTT_DATA_OFFSET);
    const u32 size = *(u32 *)((u8 *)mcss + W2U_MCSS_PLTT_DATA_SIZE_OFFSET);
    W2U_BattleAnim_Profile.lastPaletteBase = (u32)base;
    W2U_BattleAnim_Profile.lastPaletteFade = (u32)fade;
    W2U_BattleAnim_Profile.lastPaletteSize = size;

    if (!IsLikelyMainRamPointer(base) || !IsLikelyMainRamPointer(fade) ||
        size < W2U_MCSS_PLTT_SLOT_BYTES || size > 0x200u) {
        W2U_BattleAnim_Profile.paletteCpuCopyFailCount =
            W2U_BattleAnim_Profile.paletteCpuCopyFailCount + 1u;
        return;
    }

    for (u32 i = 0; i < 16; ++i) {
        base[i] = asset->palette[i];
        fade[i] = asset->palette[i];
    }
    W2U_BattleAnim_Profile.paletteCpuCopyCalls =
        W2U_BattleAnim_Profile.paletteCpuCopyCalls + 1u;
}

static u32 GetPwanPaletteBase(s32 mcssIndex)
{
    if (!IsSafeMcssTextureIndex(mcssIndex)) {
        return W2U_PWAN_PLTT_BASE;
    }
    return W2U_PWAN_PLTT_BASE + W2U_MCSS_PLTT_SLOT_BYTES * (u32)mcssIndex;
}

static void SetMcssPaletteBase(void *mcss, u32 paletteBase)
{
    if (IsLikelyMainRamPointer(mcss)) {
        *(u32 *)((u8 *)mcss + W2U_MCSS_PALETTE_PROXY_VRAM_OFFSET) = paletteBase;
    }
}

static b32 LiveMcssPaletteMatches(ActorId actor)
{
    const BattleAssetId assetId = (BattleAssetId)sState.actor[actor].assetId;
    if (assetId >= ASSET_COUNT) {
        return true;
    }

    Asset *asset = &sState.asset[actor];
    void *mcss = sState.actor[actor].mcss;
    if (!IsLikelyMainRamPointer(mcss)) {
        return true;
    }

    u16 *base = *(u16 **)((u8 *)mcss + W2U_MCSS_BASE_PLTT_DATA_OFFSET);
    u16 *fade = *(u16 **)((u8 *)mcss + W2U_MCSS_FADE_PLTT_DATA_OFFSET);
    const u32 size = *(u32 *)((u8 *)mcss + W2U_MCSS_PLTT_DATA_SIZE_OFFSET);
    if (!IsLikelyMainRamPointer(base) || !IsLikelyMainRamPointer(fade) ||
        size < W2U_MCSS_PLTT_SLOT_BYTES || size > 0x200u) {
        return true;
    }

    for (u32 i = 0; i < 16; ++i) {
        if (base[i] != asset->palette[i] || fade[i] != asset->palette[i]) {
            return false;
        }
    }
    return true;
}

static void SetTextureBanksLcdc(u8 *a, u8 *b, u8 *c, u8 *d)
{
    *a = *W2U_VRAMCNT_A;
    *b = *W2U_VRAMCNT_B;
    *c = *W2U_VRAMCNT_C;
    *d = *W2U_VRAMCNT_D;

    *W2U_VRAMCNT_A = W2U_VRAM_LCDC_ENABLE;
    *W2U_VRAMCNT_B = W2U_VRAM_LCDC_ENABLE;
    *W2U_VRAMCNT_C = W2U_VRAM_LCDC_ENABLE;
    *W2U_VRAMCNT_D = W2U_VRAM_LCDC_ENABLE;
}

static void RestoreTextureBanks(u8 a, u8 b, u8 c, u8 d)
{
    *W2U_VRAMCNT_A = a;
    *W2U_VRAMCNT_B = b;
    *W2U_VRAMCNT_C = c;
    *W2U_VRAMCNT_D = d;
}

static void SetTexturePaletteBanksLcdc(u8 *e, u8 *f, u8 *g)
{
    *e = *W2U_VRAMCNT_E;
    *f = *W2U_VRAMCNT_F;
    *g = *W2U_VRAMCNT_G;

    *W2U_VRAMCNT_E = W2U_VRAM_LCDC_ENABLE;
    *W2U_VRAMCNT_F = W2U_VRAM_LCDC_ENABLE;
    *W2U_VRAMCNT_G = W2U_VRAM_LCDC_ENABLE;
}

static void RestoreTexturePaletteBanks(u8 e, u8 f, u8 g)
{
    *W2U_VRAMCNT_E = e;
    *W2U_VRAMCNT_F = f;
    *W2U_VRAMCNT_G = g;
}

static void RestoreNativeVramMapping()
{
    if (sState.savedVramcntEValid) {
        *W2U_VRAMCNT_E = sState.savedVramcntE;
    }
}

static void PrepareObjDisplay()
{
    *W2U_REG_DISPCNT = *W2U_REG_DISPCNT | W2U_DISPCNT_OBJ_ENABLE | W2U_DISPCNT_OBJ_1D_MAP;
    if (!sState.savedVramcntEValid) {
        sState.savedVramcntE = *W2U_VRAMCNT_E;
        sState.savedVramcntEValid = true;
    }
    *W2U_VRAMCNT_E = W2U_VRAMCNT_ENABLE | W2U_VRAMCNT_MST_MAIN_OBJ;
    W2U_BattleAnim_Profile.lastObjDispcnt = *W2U_REG_DISPCNT;
    W2U_BattleAnim_Profile.lastObjVramcntE = *W2U_VRAMCNT_E;
}

static void HideOam()
{
    W2U_BattleAnim_Profile.objHideCalls = W2U_BattleAnim_Profile.objHideCalls + 1u;
    for (u32 i = 0; i < 4u; ++i) {
        volatile u16 *oam = W2U_OBJ_OAM + ((W2U_BATTLE_OBJ_INDEX + i) * 4u);
        oam[0] = 192u;
        oam[1] = 0;
        oam[2] = 0;
        oam[3] = 0;
        W2U_BattleAnim_Profile.lastOamAttr0[i] = oam[0];
        W2U_BattleAnim_Profile.lastOamAttr1[i] = oam[1];
        W2U_BattleAnim_Profile.lastOamAttr2[i] = oam[2];
    }
}

static void HideNativeMcss(void *mcss)
{
    if (!IsLikelyMainRamPointer(mcss)) {
        return;
    }
    MCSS_SetVanishFlag_Fn(mcss);
    MCSS_SetShadowVanishFlag_Fn(mcss, true);
    W2U_BattleAnim_Profile.nativeHideCalls =
        W2U_BattleAnim_Profile.nativeHideCalls + 1u;
}

static void RestoreNativeMcss(void *mcss)
{
    if (!IsLikelyMainRamPointer(mcss)) {
        return;
    }
    MCSS_ResetVanishFlag_Fn(mcss);
    MCSS_SetShadowVanishFlag_Fn(mcss, false);
    W2U_BattleAnim_Profile.nativeRestoreCalls =
        W2U_BattleAnim_Profile.nativeRestoreCalls + 1u;
}

static void CopyObjPalette(ActorId actor)
{
    Asset *asset = &sState.asset[actor];
    for (u32 i = 0; i < 16u; ++i) {
        W2U_OBJ_PLTT[W2U_OBJ_PLT * 16u + i] = asset->palette[i];
    }
}

static b32 CopyObjFrame(ActorId actor, u16 frame)
{
    Asset *asset = &sState.asset[actor];
    if (frame >= asset->header.frameCount) {
        frame = 0;
    }
    const BattleAssetId assetId = (BattleAssetId)sState.actor[actor].assetId;
    const u32 offset = asset->header.frameOffset + (frame * asset->header.frameBytes);
    if (!ReadRange(assetId, offset, sFrameScratch, W2U_FRAME_BYTES)) {
        W2U_BattleAnim_Profile.objFrameReadFailCount =
            W2U_BattleAnim_Profile.objFrameReadFailCount + 1u;
        return false;
    }

    volatile u16 *dst = W2U_OBJ_VRAM + (W2U_OBJ_FRAME_VRAM_OFFSET / 2u);
    const u16 *src = (const u16 *)sFrameScratch;
    for (u32 i = 0; i < W2U_FRAME_BYTES / 2u; ++i) {
        dst[i] = src[i];
    }
    sState.actor[actor].copiedFrame = frame;
    W2U_BattleAnim_Profile.objFrameCopyCalls =
        W2U_BattleAnim_Profile.objFrameCopyCalls + 1u;
    return true;
}

static void SetObj(u32 index, u32 x, u32 y, u32 shape, u32 size, u32 tile)
{
    volatile u16 *oam = W2U_OBJ_OAM + ((W2U_BATTLE_OBJ_INDEX + index) * 4u);
    oam[0] = (u16)((y & 0xffu) | (shape << 14));
    oam[1] = (u16)((x & 0x1ffu) | (size << 14));
    oam[2] = (u16)((tile & 0x3ffu) | (W2U_OBJ_PRIORITY << 10) | (W2U_OBJ_PLT << 12));
    oam[3] = 0;
    W2U_BattleAnim_Profile.lastOamAttr0[index] = oam[0];
    W2U_BattleAnim_Profile.lastOamAttr1[index] = oam[1];
    W2U_BattleAnim_Profile.lastOamAttr2[index] = oam[2];
}

static void DrawObjFrame()
{
    SetObj(0, W2U_BATTLE_OBJ_X, W2U_BATTLE_OBJ_Y, 0, 3, W2U_OBJ_TILE_BASE);
    SetObj(1, W2U_BATTLE_OBJ_X + 64u, W2U_BATTLE_OBJ_Y, 2, 3,
           W2U_OBJ_TILE_BASE + (0x0800u / W2U_OBJ_1D_64K_BLOCK_BYTES));
    SetObj(2, W2U_BATTLE_OBJ_X, W2U_BATTLE_OBJ_Y + 64u, 1, 3,
           W2U_OBJ_TILE_BASE + (0x0c00u / W2U_OBJ_1D_64K_BLOCK_BYTES));
    SetObj(3, W2U_BATTLE_OBJ_X + 64u, W2U_BATTLE_OBJ_Y + 64u, 0, 2,
           W2U_OBJ_TILE_BASE + (0x1000u / W2U_OBJ_1D_64K_BLOCK_BYTES));
    W2U_BattleAnim_Profile.objDrawCalls = W2U_BattleAnim_Profile.objDrawCalls + 1u;
}

static b32 IsDirectObjActor(ActorId actor, const BattleActorIdentity *identity,
                            BattleAssetId assetId)
{
#if W2U_BATTLE_DIRECT_OBJ_MAWILE
    return actor == ACTOR_SINGLE_PLAYER_BACK &&
           identity &&
           identity->species == W2U_MAWILE_MEGA_SPECIES &&
           identity->form == W2U_MAWILE_MEGA_FORM &&
           assetId == (BattleAssetId)(W2U_MAWILE_MEGA_FORM_SPRITE_INDEX * 2u + 1u);
#else
    (void)actor;
    (void)identity;
    (void)assetId;
    return false;
#endif
}

static ActorId DirectObjActor()
{
    for (u32 i = 0; i < ACTOR_COUNT; ++i) {
        if (sState.actor[i].active && sState.actor[i].directObj) {
            return (ActorId)i;
        }
    }
    return ACTOR_COUNT;
}

static void DrawDirectObjActor()
{
    if (!W2U_BATTLE_DIRECT_OBJ_MAWILE) {
        return;
    }

    const ActorId actor = DirectObjActor();
    if (actor == ACTOR_COUNT) {
        HideOam();
        return;
    }

    ActorState *actorState = &sState.actor[actor];
    PrepareObjDisplay();
    CopyObjPalette(actor);
    const u16 frame = actorState->pendingFrame;
    if (actorState->textureDirty || actorState->copiedFrame != frame) {
        if (!CopyObjFrame(actor, frame)) {
            HideOam();
            return;
        }
        actorState->textureDirty = false;
        actorState->paletteDirty = false;
    }
    W2U_BattleAnim_Profile.directActor = (u32)actor;
    W2U_BattleAnim_Profile.directAsset = actorState->assetId;
    W2U_BattleAnim_Profile.directFrame = frame;
    DrawObjFrame();
}

static b32 IsSafeVramUploadTime()
{
    const u16 vcount = *W2U_REG_VCOUNT;
    return vcount >= W2U_MCSS_VCOUNT_LOW && vcount <= W2U_MCSS_VCOUNT_HIGH;
}

static void WaitForSafeVramUploadTime()
{
    u32 spins = 0;
    W2U_BattleAnim_Profile.waitCalls = W2U_BattleAnim_Profile.waitCalls + 1u;
    W2U_BattleAnim_Profile.lastVcountBeforeWait = *W2U_REG_VCOUNT;
    while (!IsSafeVramUploadTime()) {
        spins++;
    }
    W2U_BattleAnim_Profile.waitSpinIterations += spins;
    if (spins > W2U_BattleAnim_Profile.maxWaitSpinIterations) {
        W2U_BattleAnim_Profile.maxWaitSpinIterations = spins;
    }
    W2U_BattleAnim_Profile.lastVcountAfterWait = *W2U_REG_VCOUNT;
}

static void UploadPalette(ActorId actor, u32 paletteBase)
{
    const BattleAssetId assetId = (BattleAssetId)sState.actor[actor].assetId;
    if (assetId >= ASSET_COUNT) {
        return;
    }

    Asset *asset = &sState.asset[actor];
    u8 e, f, g;
    SetTexturePaletteBanksLcdc(&e, &f, &g);

    volatile u16 *dst = W2U_LCDC_TEX_PLTT +
                        (paletteBase >> 1);
    for (u32 i = 0; i < 16; ++i) {
        dst[i] = asset->palette[i];
    }

    RestoreTexturePaletteBanks(e, f, g);
    W2U_BattleAnim_Profile.paletteUploadCalls =
        W2U_BattleAnim_Profile.paletteUploadCalls + 1u;
    sState.actor[actor].paletteDirty = false;
}

static u16 FrameForTick(const Asset *asset, u32 tick)
{
    u32 at = 0;
    for (u32 i = 0; i < asset->header.timelineCount; ++i) {
        at += asset->timeline[i].ticks;
        if (tick < at) {
            return asset->timeline[i].frame;
        }
    }
    return asset->timeline[asset->header.timelineCount - 1].frame;
}

static void BlitTileSegmentToTexture(u8 *dst, const u8 *src, u32 dstX, u32 dstY, u32 tilesW, u32 tilesH)
{
    for (u32 tileY = 0; tileY < tilesH; ++tileY) {
        for (u32 tileX = 0; tileX < tilesW; ++tileX) {
            const u8 *tile = src + ((tileY * tilesW + tileX) * 32u);
            for (u32 y = 0; y < 8; ++y) {
                u8 *row = dst + (dstY + tileY * 8u + y) * W2U_MCSS_TEX_STRIDE_BYTES +
                          (dstX + tileX * 8u) / 2u;
                const u8 *srcRow = tile + y * 4u;
                row[0] = srcRow[0];
                row[1] = srcRow[1];
                row[2] = srcRow[2];
                row[3] = srcRow[3];
            }
        }
    }
}

static void ConvertFrameToTexture(void)
{
    u8 *texture = sTextureScratch;
    const u8 *frame = sFrameScratch;
    BlitTileSegmentToTexture(texture, frame + 0x0000u, 0, 0, 8, 8);
    BlitTileSegmentToTexture(texture, frame + 0x0800u, 64, 0, 4, 8);
    BlitTileSegmentToTexture(texture, frame + 0x0c00u, 0, 64, 8, 4);
    BlitTileSegmentToTexture(texture, frame + 0x1000u, 64, 64, 4, 4);
}

static void UploadTexture(ActorId actor, s32 mcssIndex)
{
    u8 a, b, c, d;
    SetTextureBanksLcdc(&a, &b, &c, &d);

    volatile u16 *dst = W2U_LCDC_TEX_VRAM +
                        ((W2U_MCSS_TEX_BASE + W2U_MCSS_TEX_SLOT_BYTES * (u32)mcssIndex) / 2u);
    for (u32 y = 0; y < W2U_VISIBLE_TEX_HEIGHT; ++y) {
        volatile u16 *dstRow = dst + ((y * W2U_MCSS_TEX_STRIDE_BYTES) / 2u);
        const u16 *srcRow = (const u16 *)(sTextureScratch + y * W2U_MCSS_TEX_STRIDE_BYTES);
        for (u32 x = 0; x < W2U_VISIBLE_TEX_ROW_HALFWORDS; ++x) {
            dstRow[x] = srcRow[x];
        }
    }

    RestoreTextureBanks(a, b, c, d);
    W2U_BattleAnim_Profile.textureUploadActors = W2U_BattleAnim_Profile.textureUploadActors + 1u;
    W2U_BattleAnim_Profile.textureBytesUploaded += W2U_VISIBLE_TEX_BYTES;
    W2U_BattleAnim_Profile.legacyTextureBytesAvoided += W2U_LEGACY_TEX_BYTES_AVOIDED;
    W2U_BattleAnim_Profile.lastUploadActors = W2U_BattleAnim_Profile.lastUploadActors + 1u;
    W2U_BattleAnim_Profile.lastUploadBytes += W2U_VISIBLE_TEX_BYTES;
    sState.actor[actor].textureDirty = false;
}

static b32 StageFrameTexture(ActorId actor, u16 frame)
{
    const BattleAssetId assetId = (BattleAssetId)sState.actor[actor].assetId;
    if (assetId >= ASSET_COUNT) {
        W2U_BattleAnim_Profile.stageFailCount = W2U_BattleAnim_Profile.stageFailCount + 1u;
        W2U_BattleAnim_Profile.lastStageFailActor = (u32)actor;
        W2U_BattleAnim_Profile.lastStageFailAsset = (u32)assetId;
        W2U_BattleAnim_Profile.lastStageFailFrame = frame;
        return false;
    }

    Asset *asset = &sState.asset[actor];
    const u32 offset = asset->header.frameOffset + (frame * asset->header.frameBytes);
    if (!ReadRange(assetId, offset, sFrameScratch, W2U_FRAME_BYTES)) {
        W2U_BattleAnim_Profile.stageFailCount = W2U_BattleAnim_Profile.stageFailCount + 1u;
        W2U_BattleAnim_Profile.lastStageFailActor = (u32)actor;
        W2U_BattleAnim_Profile.lastStageFailAsset = (u32)assetId;
        W2U_BattleAnim_Profile.lastStageFailFrame = frame;
        return false;
    }

    ConvertFrameToTexture();
    return true;
}

static void *GetMcssWork()
{
    void *bew = *W2U_BTLV_BEW_PTR;
    W2U_BattleAnim_Profile.lastBew = (u32)bew;
    if (!bew) {
        W2U_BattleAnim_Profile.nullBewCount = W2U_BattleAnim_Profile.nullBewCount + 1u;
        W2U_BattleAnim_Profile.lastBmw = 0;
        return 0;
    }
    void *bmw = *(void **)((u8 *)bew + W2U_BATTLE_SPRITE_SYSTEM_OFFSET);
    W2U_BattleAnim_Profile.lastBmw = (u32)bmw;
    if (!bmw) {
        W2U_BattleAnim_Profile.nullBmwCount = W2U_BattleAnim_Profile.nullBmwCount + 1u;
    }
    return bmw;
}

static s32 GetMcssIndex(void *bmw, int position)
{
    W2U_BattleAnim_Profile.mcssIndexCalls = W2U_BattleAnim_Profile.mcssIndexCalls + 1u;
    W2U_BattleAnim_Profile.lastMcssIndexPosition = (u32)position;
    if (!bmw) {
        W2U_BattleAnim_Profile.mcssIndexInvalid = W2U_BattleAnim_Profile.mcssIndexInvalid + 1u;
        W2U_BattleAnim_Profile.lastMcssIndexResult = -1;
        return -1;
    }
    const s32 index = BattleSpriteGetIndex_Fn(bmw, position);
    W2U_BattleAnim_Profile.lastMcssIndexResult = index;
    if (index >= 0 && (u32)index < W2U_MCSS_TEX_SLOT_COUNT) {
        W2U_BattleAnim_Profile.mcssIndexValid = W2U_BattleAnim_Profile.mcssIndexValid + 1u;
    } else {
        W2U_BattleAnim_Profile.mcssIndexInvalid = W2U_BattleAnim_Profile.mcssIndexInvalid + 1u;
    }
    return index;
}

static s32 GetMcssMonsNo(void *bmw, int position)
{
    W2U_BattleAnim_Profile.monsReadCalls = W2U_BattleAnim_Profile.monsReadCalls + 1u;
    if (!bmw) {
        W2U_BattleAnim_Profile.monsInvalidCount = W2U_BattleAnim_Profile.monsInvalidCount + 1u;
        return SPECIES_NONE;
    }

    const s32 index = GetMcssIndex(bmw, position);
    if (index < 0) {
        W2U_BattleAnim_Profile.monsInvalidCount = W2U_BattleAnim_Profile.monsInvalidCount + 1u;
        return SPECIES_NONE;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    W2U_BattleAnim_Profile.lastEntry = (u32)entry;
    W2U_BattleAnim_Profile.lastEntryMcss = (u32)(*(void **)entry);
    if (*(void **)entry == 0) {
        W2U_BattleAnim_Profile.entryNullCount = W2U_BattleAnim_Profile.entryNullCount + 1u;
        W2U_BattleAnim_Profile.monsInvalidCount = W2U_BattleAnim_Profile.monsInvalidCount + 1u;
        return SPECIES_NONE;
    }

    const s32 monsNo = *(s32 *)(entry + W2U_BATTLE_ACTOR_SPECIES_OFFSET);
    W2U_BattleAnim_Profile.lastEntryMons = monsNo;
    if (monsNo <= SPECIES_NONE) {
        W2U_BattleAnim_Profile.monsInvalidCount = W2U_BattleAnim_Profile.monsInvalidCount + 1u;
    }
    return monsNo;
}

static BattleActorIdentity DecodeBattleActorIdentity(s32 rawMonsNo)
{
    BattleActorIdentity identity;
    identity.rawMonsNo = rawMonsNo;
    identity.species = SPECIES_NONE;
    identity.form = 0;

    if (rawMonsNo <= SPECIES_NONE) {
        return identity;
    }

    const u32 raw = (u32)rawMonsNo;
    identity.species = (u16)(raw & W2U_BATTLE_SPECIES_FORM_MASK);
    identity.form = (u16)(raw >> 11);
    if (identity.form == 0) {
        identity.species = (u16)raw;
    }

    W2U_BattleAnim_Profile.lastDecodedSpecies = identity.species;
    W2U_BattleAnim_Profile.lastDecodedForm = identity.form;
    return identity;
}

static s32 GetMcssFormNo(void *bmw, int position)
{
    if (!bmw) {
        return 0;
    }

    const s32 index = GetMcssIndex(bmw, position);
    if (index < 0) {
        return 0;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    if (*(void **)entry == 0) {
        return 0;
    }

    return *(s32 *)(entry + W2U_BATTLE_ACTOR_FORM_OFFSET);
}

static McssAddWork MakeMawileMaw(u32 spriteIndex, int position)
{
    McssAddWork maw;
    const u32 base = spriteIndex * 20u;
    const b32 front = (position & 1) != 0;
    maw.arcID = 4u;
    maw.ncbr = base + (front ? 2u : 11u);
    maw.nclr = base + 18u;
    maw.ncer = base + (front ? 4u : 13u);
    maw.nanr = base + (front ? 5u : 14u);
    maw.nmcr = base + (front ? 6u : 15u);
    maw.nmar = base + (front ? 7u : 16u);
    maw.ncec = base + (front ? 8u : 17u);
    maw.heapLow = 0;
    return maw;
}

static McssAddWork MakeMegaMawileMaw(int position)
{
    return MakeMawileMaw(W2U_MAWILE_MEGA_FORM_SPRITE_INDEX, position);
}

static McssAddWork MakeBaseMawileMaw(int position)
{
    return MakeMawileMaw(W2U_MAWILE_BASE_SPRITE_INDEX, position);
}

static b32 IsMegaMawilePwanActor(const ActorState *actorState)
{
    return actorState &&
           actorState->species == W2U_MAWILE_MEGA_SPECIES &&
           actorState->form == W2U_MAWILE_MEGA_FORM &&
           actorState->assetId == (u16)(W2U_MAWILE_MEGA_FORM_SPRITE_INDEX * 2u + 1u);
}

static b32 PatchMcssCarrierFromSpriteIndex(void *bmw, int position, ActorState *actorState,
                                           u32 spriteIndex)
{
    W2U_BattleAnim_Profile.mawPatchCalls =
        W2U_BattleAnim_Profile.mawPatchCalls + 1u;

    if (!bmw || !actorState || spriteIndex > W2U_PWAN_MAX_ASSET_INDEX) {
        return false;
    }

    const s32 index = GetMcssIndex(bmw, position);
    if (!IsSafeMcssTextureIndex(index)) {
        return false;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    if (*(void **)entry == 0) {
        return false;
    }

    const McssAddWork maw = MakeMawileMaw(spriteIndex, position);
    const u32 oldNcbr = *(u32 *)(entry + 8u);
    const u32 oldNclr = *(u32 *)(entry + 12u);
    const u32 oldNcec = *(u32 *)(entry + 32u);
    if (oldNcbr == maw.ncbr && oldNclr == maw.nclr && oldNcec == maw.ncec) {
        if (!actorState->mcssMawPatched) {
            actorState->textureDirty = true;
            actorState->paletteDirty = true;
            actorState->copiedFrame = 0xffffu;
            actorState->pendingFrame = 0xffffu;
        }
        actorState->mcssMawPatched = true;
        return actorState->textureDirty || actorState->paletteDirty;
    }

    BattleSpriteOverwriteMaw_Fn(bmw, position, &maw);

    actorState->mcssMawPatched = true;
    actorState->textureDirty = true;
    actorState->paletteDirty = true;
    actorState->copiedFrame = 0xffffu;
    actorState->pendingFrame = 0xffffu;
    W2U_BattleAnim_Profile.mawPatchMatches =
        W2U_BattleAnim_Profile.mawPatchMatches + 1u;
    W2U_BattleAnim_Profile.lastMawPatchPosition = (u32)position;
    W2U_BattleAnim_Profile.lastMawPatchOldNcbr = oldNcbr;
    W2U_BattleAnim_Profile.lastMawPatchNewNcbr = maw.ncbr;
    return true;
}

static b32 PatchMegaMawileMaw(void *bmw, int position, ActorState *actorState)
{
    if (!bmw ||
        !actorState ||
        position != W2U_BTLV_POS_AA ||
        !IsMegaMawilePwanActor(actorState)) {
        return false;
    }

    return PatchMcssCarrierFromSpriteIndex(
        bmw, position, actorState, W2U_MAWILE_MEGA_FORM_SPRITE_INDEX);
}

static b32 PatchFormFromPwanConfig(void *bmw, int position, ActorState *actorState)
{
    if (!actorState ||
        actorState->form == 0 ||
        actorState->assetId == (u16)ASSET_NONE ||
        (u32)actorState->assetId >= ASSET_COUNT) {
        return false;
    }

    const u32 spriteIndex = ((u32)actorState->assetId) / 2u;
    return PatchMcssCarrierFromSpriteIndex(bmw, position, actorState, spriteIndex);
}

static void PatchBaseMawileMawIfNeeded(void *bmw, int position,
                                       const BattleActorIdentity *identity)
{
    if (!bmw ||
        !identity ||
        position != W2U_BTLV_POS_AA ||
        identity->species != W2U_MAWILE_MEGA_SPECIES ||
        identity->form != 0) {
        return;
    }

    const s32 index = GetMcssIndex(bmw, position);
    if (!IsSafeMcssTextureIndex(index)) {
        return;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    if (*(void **)entry == 0) {
        return;
    }

    const McssAddWork maw = MakeBaseMawileMaw(position);
    const u32 oldNcbr = *(u32 *)(entry + 8u);
    const u32 oldNclr = *(u32 *)(entry + 12u);
    const u32 oldNcec = *(u32 *)(entry + 32u);
    if (oldNcbr == maw.ncbr && oldNclr == maw.nclr && oldNcec == maw.ncec) {
        return;
    }

    BattleSpriteOverwriteMaw_Fn(bmw, position, &maw);
    W2U_BattleAnim_Profile.lastMawPatchPosition = (u32)position;
    W2U_BattleAnim_Profile.lastMawPatchOldNcbr = oldNcbr;
    W2U_BattleAnim_Profile.lastMawPatchNewNcbr = maw.ncbr;
}

static b32 PatchMegaMawileStaticMaw(void *bmw)
{
    W2U_BattleAnim_Profile.megaStaticMawPatchCalls =
        W2U_BattleAnim_Profile.megaStaticMawPatchCalls + 1u;

    if (!bmw) {
        return false;
    }

    const s32 index = GetMcssIndex(bmw, W2U_BTLV_POS_AA);
    if (!IsSafeMcssTextureIndex(index)) {
        return false;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    if (*(void **)entry == 0) {
        return false;
    }

    const s32 monsNo = *(s32 *)(entry + W2U_BATTLE_ACTOR_SPECIES_OFFSET);
    const s32 formNo = *(s32 *)(entry + W2U_BATTLE_ACTOR_FORM_OFFSET);
    if (monsNo != (s32)W2U_MAWILE_MEGA_SPECIES ||
        formNo != (s32)W2U_MAWILE_MEGA_FORM) {
        return false;
    }

    const McssAddWork maw = MakeMegaMawileMaw(W2U_BTLV_POS_AA);
    const u32 oldNcbr = *(u32 *)(entry + 8u);
    const u32 oldNclr = *(u32 *)(entry + 12u);
    const u32 oldNcec = *(u32 *)(entry + 32u);
    if (oldNcbr == maw.ncbr && oldNclr == maw.nclr && oldNcec == maw.ncec) {
        return false;
    }

    BattleSpriteOverwriteMaw_Fn(bmw, W2U_BTLV_POS_AA, &maw);
    W2U_BattleAnim_Profile.megaStaticMawPatchMatches =
        W2U_BattleAnim_Profile.megaStaticMawPatchMatches + 1u;
    W2U_BattleAnim_Profile.lastMawPatchPosition = W2U_BTLV_POS_AA;
    W2U_BattleAnim_Profile.lastMawPatchOldNcbr = oldNcbr;
    W2U_BattleAnim_Profile.lastMawPatchNewNcbr = maw.ncbr;
    return true;
}

static b32 IsValidMegaVisualState(volatile MegaVisualStateMirror *state)
{
    return state &&
           state->magic == W2U_MEGA_VISUAL_STATE_MAGIC &&
           state->version == W2U_MEGA_VISUAL_STATE_VERSION &&
           state->structSize >= sizeof(MegaVisualStateMirror) &&
           state->structSize <= W2U_MEGA_VISUAL_STATE_MAX_SIZE;
}

static volatile MegaVisualStateMirror *FindMegaVisualState()
{
    if (IsValidMegaVisualState(sMegaVisualState)) {
        return sMegaVisualState;
    }

    W2U_BattleAnim_Profile.megaProfileScanCalls =
        W2U_BattleAnim_Profile.megaProfileScanCalls + 1u;

    for (u32 address = W2U_MAIN_RAM_START;
         address + sizeof(MegaVisualStateMirror) <= W2U_MAIN_RAM_END;
         address += sizeof(u32)) {
        volatile MegaVisualStateMirror *candidate = (volatile MegaVisualStateMirror *)address;
        if (IsValidMegaVisualState(candidate)) {
            sMegaVisualState = candidate;
            W2U_BattleAnim_Profile.megaProfileFound = 1u;
            W2U_BattleAnim_Profile.megaProfileAddress = address;
            return candidate;
        }
    }

    W2U_BattleAnim_Profile.megaProfileFound = 0;
    W2U_BattleAnim_Profile.megaProfileAddress = 0;
    return 0;
}

static b32 IsMegaMawileVisualReadyRaw(volatile MegaVisualStateMirror *state)
{
    return IsValidMegaVisualState(state) &&
           state->visualOverrideReady != 0 &&
           state->clientChangeFormPokeID == 0 &&
           state->clientChangeFormForm == W2U_MAWILE_MEGA_FORM &&
           state->species == W2U_MAWILE_MEGA_SPECIES &&
           state->form == W2U_MAWILE_MEGA_FORM &&
           (state->usedSideMask & 1u) != 0;
}

static b32 IsPlausibleSummaryStat(u16 value)
{
    return value != 0 && value <= W2U_PWAN_MAX_ASSET_INDEX;
}

static b32 IsBattleSummaryCacheCandidate(u16 *entry)
{
    if (!IsLikelyMainRamPointer(entry) ||
        entry[0] != W2U_MAWILE_MEGA_SPECIES ||
        !IsPlausibleSummaryStat(entry[1]) ||
        !IsPlausibleSummaryStat(entry[2]) ||
        !IsPlausibleSummaryStat(entry[3]) ||
        !IsPlausibleSummaryStat(entry[4]) ||
        !IsPlausibleSummaryStat(entry[5]) ||
        !IsPlausibleSummaryStat(entry[7])) {
        return false;
    }

    u8 *bytes = (u8 *)entry;
    const u8 type1 = bytes[0x10];
    const u8 type2 = bytes[0x11];
    if (type1 == W2U_TYPE_STEEL && type2 == W2U_TYPE_FAIRY) {
        return true;
    }
    return type1 == W2U_TYPE_DRAGON && type2 == W2U_TYPE_DRAGON;
}

static void PatchBattleSummaryCacheEntry(u16 *entry,
                                         volatile MegaVisualStateMirror *state)
{
    W2U_BattleAnim_Profile.megaSummaryCachePatchCalls =
        W2U_BattleAnim_Profile.megaSummaryCachePatchCalls + 1u;

    if (!IsBattleSummaryCacheCandidate(entry) ||
        !IsValidMegaVisualState(state) ||
        state->mirroredPartyAttack == 0 ||
        state->mirroredPartyDefense == 0 ||
        state->mirroredPartySpeed == 0 ||
        state->mirroredPartySpAttack == 0 ||
        state->mirroredPartySpDefense == 0) {
        return;
    }

    entry[1] = (u16)state->mirroredPartyAttack;
    entry[2] = (u16)state->mirroredPartyDefense;
    entry[3] = (u16)state->mirroredPartySpeed;
    entry[4] = (u16)state->mirroredPartySpAttack;
    entry[5] = (u16)state->mirroredPartySpDefense;
    if (state->mirroredPartyMaxHP != 0) {
        entry[7] = (u16)state->mirroredPartyMaxHP;
        if (entry[6] > entry[7]) {
            entry[6] = entry[7];
        }
    }

    u8 *bytes = (u8 *)entry;
    bytes[0x10] = (u8)W2U_TYPE_DRAGON;
    bytes[0x11] = (u8)W2U_TYPE_DRAGON;
    const u16 ability = (u16)state->mirroredPartyAbility;
    if (ability != 0) {
        entry[10] = ability;
        entry[0x30] = ability;
        entry[0x56] = ability;
    }

    W2U_BattleAnim_Profile.megaSummaryCachePatchMatches =
        W2U_BattleAnim_Profile.megaSummaryCachePatchMatches + 1u;
    W2U_BattleAnim_Profile.megaSummaryCacheAddress = (u32)entry;
    W2U_BattleAnim_Profile.megaSummaryCacheLastSpecies = entry[0];
    W2U_BattleAnim_Profile.megaSummaryCacheLastAttack = entry[1];
    W2U_BattleAnim_Profile.megaSummaryCacheLastDefense = entry[2];
    W2U_BattleAnim_Profile.megaSummaryCacheLastSpeed = entry[3];
    W2U_BattleAnim_Profile.megaSummaryCacheLastSpAttack = entry[4];
    W2U_BattleAnim_Profile.megaSummaryCacheLastSpDefense = entry[5];
    W2U_BattleAnim_Profile.megaSummaryCacheLastCurrentHP = entry[6];
    W2U_BattleAnim_Profile.megaSummaryCacheLastMaxHP = entry[7];
    W2U_BattleAnim_Profile.megaSummaryCacheLastTypeWord =
        ((u32)bytes[0x10]) | (((u32)bytes[0x11]) << 8);
    W2U_BattleAnim_Profile.megaSummaryCacheLastAbilityWord =
        ((u32)entry[10]) |
        (((u32)entry[0x30]) << 8) |
        (((u32)entry[0x56]) << 16);
}

static void PatchMegaMawileBattleSummaryCache()
{
    volatile MegaVisualStateMirror *state = FindMegaVisualState();
    if (!IsMegaMawileVisualReadyRaw(state)) {
        sState.megaSummaryCacheAddress = 0;
        sState.megaSummaryCacheScanCooldown = 0;
        return;
    }

    if (sState.megaSummaryCacheAddress != 0) {
        u16 *entry = (u16 *)sState.megaSummaryCacheAddress;
        if (IsBattleSummaryCacheCandidate(entry)) {
            PatchBattleSummaryCacheEntry(entry, state);
            return;
        }
        sState.megaSummaryCacheAddress = 0;
    }

    u16 *knownEntry = (u16 *)W2U_BATTLE_SUMMARY_CACHE_KNOWN_ADDRESS;
    if (IsBattleSummaryCacheCandidate(knownEntry)) {
        sState.megaSummaryCacheAddress = W2U_BATTLE_SUMMARY_CACHE_KNOWN_ADDRESS;
        PatchBattleSummaryCacheEntry(knownEntry, state);
        return;
    }

    if (sState.megaSummaryCacheScanCooldown != 0) {
        sState.megaSummaryCacheScanCooldown =
            (u8)(sState.megaSummaryCacheScanCooldown - 1u);
        return;
    }
    sState.megaSummaryCacheScanCooldown = W2U_BATTLE_SUMMARY_CACHE_SCAN_COOLDOWN;
    W2U_BattleAnim_Profile.megaSummaryCacheScanCalls =
        W2U_BattleAnim_Profile.megaSummaryCacheScanCalls + 1u;

    for (u32 address = W2U_BATTLE_SUMMARY_CACHE_SCAN_START;
         address + 0x20u <= W2U_BATTLE_SUMMARY_CACHE_SCAN_END;
         address += sizeof(u16)) {
        u16 *entry = (u16 *)address;
        if (!IsBattleSummaryCacheCandidate(entry)) {
            continue;
        }

        sState.megaSummaryCacheAddress = address;
        PatchBattleSummaryCacheEntry(entry, state);
        return;
    }
}

extern "C" void W2U_BattleAnim_PatchMegaSummaryCache()
{
    PatchMegaMawileBattleSummaryCache();
}

static void ClearMegaVisualState()
{
    volatile MegaVisualStateMirror *state = FindMegaVisualState();
    if (!IsValidMegaVisualState(state)) {
        return;
    }

    state->clientChangeFormPokeID = 0;
    state->clientChangeFormForm = 0;
    state->visualOverrideReady = 0;
}

static void PatchBaseMawileMawWhenMegaVisualInactive(void *bmw)
{
    if (!bmw || IsMegaMawileVisualReadyRaw(FindMegaVisualState())) {
        return;
    }

    const s32 index = GetMcssIndex(bmw, W2U_BTLV_POS_AA);
    if (!IsSafeMcssTextureIndex(index)) {
        return;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    if (*(void **)entry == 0) {
        return;
    }

    const s32 monsNo = *(s32 *)(entry + W2U_BATTLE_ACTOR_SPECIES_OFFSET);
    const u32 species = ((u32)monsNo) & W2U_BATTLE_SPECIES_FORM_MASK;
    if (monsNo != (s32)W2U_MAWILE_MEGA_SPECIES &&
        species != W2U_MAWILE_MEGA_SPECIES) {
        return;
    }

    const McssAddWork maw = MakeBaseMawileMaw(W2U_BTLV_POS_AA);
    const u32 oldNcbr = *(u32 *)(entry + 8u);
    const u32 oldNclr = *(u32 *)(entry + 12u);
    const u32 oldNcec = *(u32 *)(entry + 32u);
    if (oldNcbr == maw.ncbr && oldNclr == maw.nclr && oldNcec == maw.ncec) {
        return;
    }

    BattleSpriteOverwriteMaw_Fn(bmw, W2U_BTLV_POS_AA, &maw);
    W2U_BattleAnim_Profile.lastMawPatchPosition = W2U_BTLV_POS_AA;
    W2U_BattleAnim_Profile.lastMawPatchOldNcbr = oldNcbr;
    W2U_BattleAnim_Profile.lastMawPatchNewNcbr = maw.ncbr;
}

static void RestoreSuppressedMegaMawileMcss()
{
    if (!sState.megaVisualSuppressed) {
        return;
    }

    RestoreNativeMcss(sState.megaVisualSuppressedMcss);
    sState.megaVisualSuppressed = false;
    sState.megaVisualSuppressedMcss = 0;
    W2U_BattleAnim_Profile.megaVisualRestoreCalls =
        W2U_BattleAnim_Profile.megaVisualRestoreCalls + 1u;
}

static void SuppressMegaMawileMcss(void *bmw)
{
    const s32 index = GetMcssIndex(bmw, W2U_BTLV_POS_AA);
    if (!IsSafeMcssTextureIndex(index)) {
        return;
    }

    void *mcss = GetMcssPointerByIndex(bmw, index);
    if (!IsLikelyMainRamPointer(mcss)) {
        return;
    }

    if (sState.megaVisualSuppressed &&
        sState.megaVisualSuppressedMcss != mcss) {
        RestoreSuppressedMegaMawileMcss();
    }

    HideNativeMcss(mcss);
    sState.megaVisualSuppressed = true;
    sState.megaVisualSuppressedMcss = mcss;

    W2U_BattleAnim_Profile.megaVisualSuppressCalls =
        W2U_BattleAnim_Profile.megaVisualSuppressCalls + 1u;
}

static void UpdateMegaVisualSettle(void *bmw)
{
    volatile MegaVisualStateMirror *state = FindMegaVisualState();
    if (!IsMegaMawileVisualReadyRaw(state)) {
        RestoreSuppressedMegaMawileMcss();
        sState.megaVisualReadyObserved = false;
        sState.megaVisualSettleFrames = 0;
        sState.megaVisualRevealHoldFrames = 0;
        sState.megaPwanStreamDelayFrames = 0;
        sState.megaVisualFirstFrameUploaded = false;
        sState.megaPwanStreamingReady = false;
        W2U_BattleAnim_Profile.megaVisualSettleFrames = 0;
        W2U_BattleAnim_Profile.megaVisualSettleReady = 0;
        W2U_BattleAnim_Profile.megaVisualFirstFrameUploaded = 0;
        W2U_BattleAnim_Profile.megaVisualRevealHoldFrames = 0;
        W2U_BattleAnim_Profile.megaPwanStreamDelayFrames = 0;
        W2U_BattleAnim_Profile.megaPwanStreamingReady = 0;
        return;
    }

    sState.megaVisualReadyObserved = true;
#if W2U_MEGA_VISUAL_SETTLE_FRAMES > 0
    if (sState.megaVisualSettleFrames < W2U_MEGA_VISUAL_SETTLE_FRAMES) {
        SuppressMegaMawileMcss(bmw);
        sState.megaVisualSettleFrames =
            (u8)(sState.megaVisualSettleFrames + 1u);
        W2U_BattleAnim_Profile.megaVisualSettleFrames =
            sState.megaVisualSettleFrames;
        W2U_BattleAnim_Profile.megaVisualSettleReady = 0;
        return;
    }
#endif

    W2U_BattleAnim_Profile.megaVisualSettleFrames =
        sState.megaVisualSettleFrames;
    W2U_BattleAnim_Profile.megaVisualSettleReady = 1u;
    PatchMegaMawileStaticMaw(bmw);

    ActorState *actorState = &sState.actor[ACTOR_SINGLE_PLAYER_BACK];
    if (actorState->active &&
        actorState->species == W2U_MAWILE_MEGA_SPECIES &&
        actorState->form == W2U_MAWILE_MEGA_FORM &&
        actorState->assetId == (u16)(W2U_MAWILE_MEGA_FORM_SPRITE_INDEX * 2u + 1u) &&
        actorState->copiedFrame != 0xffffu) {
        sState.megaVisualFirstFrameUploaded = true;
        W2U_BattleAnim_Profile.megaVisualFirstFrameUploaded = 1u;
    }

#if W2U_MEGA_PWAN_STREAM_DELAY_FRAMES > 0
    if (sState.megaPwanStreamDelayFrames < W2U_MEGA_PWAN_STREAM_DELAY_FRAMES) {
        SuppressMegaMawileMcss(bmw);
        sState.megaPwanStreamDelayFrames =
            (u8)(sState.megaPwanStreamDelayFrames + 1u);
        W2U_BattleAnim_Profile.megaPwanStreamDelayFrames =
            sState.megaPwanStreamDelayFrames;
        W2U_BattleAnim_Profile.megaPwanStreamingReady = 0;
        return;
    }
#endif

    sState.megaPwanStreamingReady = true;
    W2U_BattleAnim_Profile.megaPwanStreamDelayFrames =
        sState.megaPwanStreamDelayFrames;
    W2U_BattleAnim_Profile.megaPwanStreamingReady = 1u;

    if (!sState.megaVisualFirstFrameUploaded
#if W2U_MEGA_VISUAL_REVEAL_HOLD_FRAMES > 0
        || sState.megaVisualRevealHoldFrames < W2U_MEGA_VISUAL_REVEAL_HOLD_FRAMES
#endif
        ) {
        SuppressMegaMawileMcss(bmw);
#if W2U_MEGA_VISUAL_REVEAL_HOLD_FRAMES > 0
        if (sState.megaVisualFirstFrameUploaded) {
            sState.megaVisualRevealHoldFrames =
                (u8)(sState.megaVisualRevealHoldFrames + 1u);
        }
#endif
        W2U_BattleAnim_Profile.megaVisualRevealHoldFrames =
            sState.megaVisualRevealHoldFrames;
        return;
    }

    W2U_BattleAnim_Profile.megaVisualRevealHoldFrames =
        sState.megaVisualRevealHoldFrames;
    RestoreSuppressedMegaMawileMcss();
}

static b32 IsMegaMawileVisualReady(volatile MegaVisualStateMirror *state)
{
#if W2U_MEGA_VISUAL_SETTLE_FRAMES > 0
    return IsMegaMawileVisualReadyRaw(state) &&
           sState.megaVisualSettleFrames >= W2U_MEGA_VISUAL_SETTLE_FRAMES;
#else
    return IsMegaMawileVisualReadyRaw(state);
#endif
}

static b32 IsMegaMawilePwanStreamingReady()
{
    return sState.megaPwanStreamingReady;
}

static void ApplyMegaVisualStateOverride(int position, BattleActorIdentity *identity)
{
    W2U_BattleAnim_Profile.megaOverrideCalls =
        W2U_BattleAnim_Profile.megaOverrideCalls + 1u;

    if (!identity ||
        position != W2U_BTLV_POS_AA ||
        identity->species != W2U_MAWILE_MEGA_SPECIES ||
        identity->form != 0) {
        return;
    }

    volatile MegaVisualStateMirror *state = FindMegaVisualState();
    if (!IsMegaMawileVisualReady(state)) {
        return;
    }

    identity->form = W2U_MAWILE_MEGA_FORM;
    W2U_BattleAnim_Profile.lastDecodedForm = identity->form;
    W2U_BattleAnim_Profile.megaOverrideMatches =
        W2U_BattleAnim_Profile.megaOverrideMatches + 1u;
}

static void PatchMcssActorIdentity(void *bmw, int position, BattleActorIdentity *identity)
{
    W2U_BattleAnim_Profile.actorIdentityPatchCalls =
        W2U_BattleAnim_Profile.actorIdentityPatchCalls + 1u;

    if (!bmw ||
        !identity ||
        position != W2U_BTLV_POS_AA ||
        identity->species != W2U_MAWILE_MEGA_SPECIES ||
        identity->form != W2U_MAWILE_MEGA_FORM) {
        return;
    }

    const s32 index = GetMcssIndex(bmw, position);
    if (!IsSafeMcssTextureIndex(index)) {
        return;
    }

    u8 *entry = (u8 *)bmw + W2U_BATTLE_ACTOR_ENTRY_BASE +
                ((u32)index * W2U_BATTLE_ACTOR_ENTRY_BYTES);
    if (*(void **)entry == 0) {
        return;
    }

    s32 *rawMonsNo = (s32 *)(entry + W2U_BATTLE_ACTOR_SPECIES_OFFSET);
    s32 *formNo = (s32 *)(entry + W2U_BATTLE_ACTOR_FORM_OFFSET);
    const s32 oldRaw = *rawMonsNo;
    if (oldRaw != (s32)W2U_MAWILE_MEGA_SPECIES &&
        oldRaw != (s32)W2U_MAWILE_MEGA_PACKED_MONS) {
        return;
    }

    *rawMonsNo = (s32)W2U_MAWILE_MEGA_SPECIES;
    *formNo = (s32)W2U_MAWILE_MEGA_FORM;
    identity->rawMonsNo = (s32)W2U_MAWILE_MEGA_SPECIES;
    identity->species = W2U_MAWILE_MEGA_SPECIES;
    identity->form = W2U_MAWILE_MEGA_FORM;
    W2U_BattleAnim_Profile.actorIdentityPatchMatches =
        W2U_BattleAnim_Profile.actorIdentityPatchMatches + 1u;
    W2U_BattleAnim_Profile.lastActorIdentityPatchPosition = (u32)position;
    W2U_BattleAnim_Profile.lastActorIdentityPatchOldRaw = (u32)oldRaw;
    W2U_BattleAnim_Profile.lastActorIdentityPatchNewRaw =
        W2U_MAWILE_MEGA_SPECIES;
}

static BattleActorIdentity GetMcssActorIdentity(void *bmw, int position)
{
    BattleActorIdentity identity = DecodeBattleActorIdentity(GetMcssMonsNo(bmw, position));
    if (identity.species != SPECIES_NONE) {
        const s32 formNo = GetMcssFormNo(bmw, position);
        if (formNo >= 0 && formNo <= 31) {
            if (identity.species == W2U_MAWILE_MEGA_SPECIES &&
                formNo == (s32)W2U_MAWILE_MEGA_FORM &&
                position == W2U_BTLV_POS_AA &&
                !IsMegaMawileVisualReady(FindMegaVisualState())) {
                identity.form = 0;
            } else {
                identity.form = (u16)formNo;
            }
            W2U_BattleAnim_Profile.lastDecodedForm = identity.form;
        }
    }
    ApplyMegaVisualStateOverride(position, &identity);
    PatchMcssActorIdentity(bmw, position, &identity);
    return identity;
}

static BattleAssetId AssetForEntrySide(const PwanConfigEntry *entry, b32 isFront)
{
    if (isFront) {
        if ((entry->flags & W2U_PWAN_CONFIG_FRONT_FLAG) == 0 ||
            entry->assetIndex > W2U_PWAN_MAX_ASSET_INDEX) return ASSET_NONE;
        return (BattleAssetId)(entry->assetIndex * 2u);
    }

    if ((entry->flags & W2U_PWAN_CONFIG_BACK_FLAG) == 0 ||
        entry->assetIndex > W2U_PWAN_MAX_ASSET_INDEX) return ASSET_NONE;
    return (BattleAssetId)(entry->assetIndex * 2u + 1u);
}

static b32 IsMawileMegaFormSpriteFallback(const BattleActorIdentity *identity, const PwanConfigEntry *entry)
{
    return identity->rawMonsNo == (s32)W2U_MAWILE_MEGA_FORM_SPRITE_INDEX &&
           entry->species == W2U_MAWILE_MEGA_SPECIES &&
           entry->form == W2U_MAWILE_MEGA_FORM;
}

static BattleAssetId GetAssetForSpeciesSide(const BattleActorIdentity *identity, b32 isFront)
{
    PwanConfigHeader header = {};
    if (!ReadConfigRange(0, &header, sizeof(header)) ||
        header.magic != W2U_PWAN_CONFIG_MAGIC ||
        header.version != W2U_PWAN_CONFIG_VERSION ||
        header.count > W2U_PWAN_MAX_OVERRIDES ||
        header.maxTimeline > W2U_PWAN_MAX_TIMELINE ||
        header.entriesOffset < sizeof(PwanConfigHeader)) {
        W2U_BattleAnim_Profile.lastConfigVersion = header.version;
        return ASSET_NONE;
    }
    W2U_BattleAnim_Profile.lastConfigVersion = header.version;

    for (u32 i = 0; i < header.count; ++i) {
        u8 raw[W2U_PWAN_CONFIG_ENTRY_BYTES];
        const u32 offset = W2U_PwanConfigEntryOffset(&header, i);
        if (!ReadConfigRange(offset, raw, W2U_PWAN_CONFIG_ENTRY_BYTES)) return ASSET_NONE;
        PwanConfigEntry entry = W2U_DecodePwanConfigEntry(raw);
        if (identity->species == W2U_MAWILE_MEGA_SPECIES &&
            identity->form == W2U_MAWILE_MEGA_FORM &&
            !IsMegaMawilePwanStreamingReady()) {
            W2U_BattleAnim_Profile.lastConfigMatchMode = 4u;
            return ASSET_NONE;
        }
        if (entry.species == identity->species && entry.form == identity->form) {
            W2U_BattleAnim_Profile.lastConfigMatchMode = 2u;
            return AssetForEntrySide(&entry, isFront);
        }
        if (IsMawileMegaFormSpriteFallback(identity, &entry)) {
            W2U_BattleAnim_Profile.lastConfigMatchMode = 3u;
            return AssetForEntrySide(&entry, isFront);
        }
    }
    W2U_BattleAnim_Profile.lastConfigMatchMode = 0;
    return ASSET_NONE;
}

static BattleAssetId GetAssetForPositionSpecies(int position, const BattleActorIdentity *identity)
{
    if ((position & 1) == 0) {
        return GetAssetForSpeciesSide(identity, false);
    }

    return GetAssetForSpeciesSide(identity, true);
}

static b32 IsSafeMcssTextureIndex(s32 mcssIndex)
{
    return mcssIndex >= 0 && (u32)mcssIndex < W2U_MCSS_TEX_SLOT_COUNT;
}

static void RecordActorProfile(ActorId actor, u32 position, s32 mcssIndex,
                               const BattleActorIdentity *identity,
                               BattleAssetId assetId, b32 active, b32 textureDirty, u16 frame)
{
    W2U_BattleAnim_Profile.actorPosition[actor] = position;
    W2U_BattleAnim_Profile.actorMcssIndex[actor] = mcssIndex;
    W2U_BattleAnim_Profile.actorSpecies[actor] = identity->species;
    W2U_BattleAnim_Profile.actorForm[actor] = identity->form;
    W2U_BattleAnim_Profile.actorRawMons[actor] = identity->rawMonsNo;
    W2U_BattleAnim_Profile.actorAsset[actor] = (u32)assetId;
    W2U_BattleAnim_Profile.actorFrame[actor] = frame;
    if (active) {
        W2U_BattleAnim_Profile.lastActiveMask |= (1u << (u32)actor);
    }
    if (textureDirty) {
        W2U_BattleAnim_Profile.lastTextureDirtyMask |= (1u << (u32)actor);
    }
}

static void DeactivateActor(ActorId actor)
{
    if (sState.actor[actor].directObj) {
        RestoreNativeMcss(sState.actor[actor].mcss);
        HideOam();
    }
    sState.actor[actor].active = false;
    sState.actor[actor].directObj = false;
    sState.actor[actor].textureDirty = false;
    sState.actor[actor].paletteDirty = false;
    sState.actor[actor].copiedFrame = 0xffffu;
    sState.actor[actor].pendingFrame = 0xffffu;
    sState.actor[actor].mcssIndex = -1;
    sState.actor[actor].species = SPECIES_NONE;
    sState.actor[actor].form = 0;
    sState.actor[actor].assetId = ASSET_NONE;
    sState.actor[actor].mcssMawPatched = false;
    sState.actor[actor].mcss = 0;
}

static void UpdateActor(ActorId actor, void *bmw)
{
    const ActorConfig *cfg = &kActorConfig[actor];
    ActorState *actorState = &sState.actor[actor];

    const s32 mcssIndex = GetMcssIndex(bmw, cfg->position);
    if (!IsSafeMcssTextureIndex(mcssIndex)) {
        BattleActorIdentity none;
        none.rawMonsNo = SPECIES_NONE;
        none.species = SPECIES_NONE;
        none.form = 0;
        RecordActorProfile(actor, cfg->position, mcssIndex, &none, ASSET_NONE, false, false, 0xffffu);
        DeactivateActor(actor);
        return;
    }
    const BattleActorIdentity identity = GetMcssActorIdentity(bmw, cfg->position);
    PatchBaseMawileMawIfNeeded(bmw, cfg->position, &identity);
    const BattleAssetId assetId = GetAssetForPositionSpecies(cfg->position, &identity);
    if (assetId >= ASSET_COUNT || !LoadAsset(actor, assetId)) {
        W2U_BattleAnim_Profile.loadFailCount = W2U_BattleAnim_Profile.loadFailCount + 1u;
        W2U_BattleAnim_Profile.lastLoadFailActor = (u32)actor;
        W2U_BattleAnim_Profile.lastLoadFailAsset = (u32)assetId;
        RecordActorProfile(actor, cfg->position, mcssIndex, &identity, assetId, false, false, 0xffffu);
        DeactivateActor(actor);
        return;
    }

    const b32 wasInactive = !actorState->active;
    const b32 wasDirectObj = actorState->directObj;
    void *oldMcss = actorState->mcss;
    void *currentMcss = GetMcssPointerByIndex(bmw, mcssIndex);
    const b32 mcssIndexChanged = actorState->mcssIndex != (s16)mcssIndex;
    const b32 mcssPointerChanged = oldMcss != currentMcss;
    const b32 speciesChanged = actorState->species != identity.species ||
                               actorState->form != identity.form ||
                               actorState->assetId != assetId;
    if (speciesChanged) {
        actorState->tick = 0;
        actorState->copiedFrame = 0xffffu;
        actorState->pendingFrame = 0xffffu;
        actorState->mcssMawPatched = false;
    } else if (mcssIndexChanged || mcssPointerChanged) {
        actorState->copiedFrame = 0xffffu;
        actorState->pendingFrame = 0xffffu;
        actorState->mcssMawPatched = false;
    }

    actorState->active = true;
    actorState->mcssIndex = (s16)mcssIndex;
    actorState->species = identity.species;
    actorState->form = identity.form;
    actorState->assetId = (u16)assetId;
    actorState->mcss = currentMcss;
    actorState->directObj = IsDirectObjActor(actor, &identity, assetId);
    if (wasDirectObj && !actorState->directObj) {
        RestoreNativeMcss(oldMcss);
        HideOam();
    }
    if (actorState->directObj) {
        HideNativeMcss(actorState->mcss);
    }
    if (wasInactive || mcssIndexChanged || mcssPointerChanged || speciesChanged) {
        actorState->paletteDirty = true;
    }
    b32 carrierPatched = PatchMegaMawileMaw(bmw, cfg->position, actorState);
    if (!IsMegaMawilePwanActor(actorState)) {
        carrierPatched = PatchFormFromPwanConfig(bmw, cfg->position, actorState);
    }
    if (carrierPatched) {
        actorState->mcss = GetMcssPointerByIndex(bmw, mcssIndex);
    }
    SetMcssPaletteBase(actorState->mcss, GetPwanPaletteBase(mcssIndex));
    if (!actorState->directObj && !LiveMcssPaletteMatches(actor)) {
        actorState->paletteDirty = true;
        actorState->copiedFrame = 0xffffu;
    }
    if (actorState->paletteDirty && !actorState->directObj) {
        CopyPaletteToLiveMcss(actor);
    }

    Asset *asset = &sState.asset[actor];
    const u32 totalTicks = asset->header.totalTicks ? asset->header.totalTicks : 1;
    if (actorState->tick >= totalTicks) {
        actorState->tick = 0;
    }
    const u16 frame = FrameForTick(asset, actorState->tick);
    if (wasInactive || mcssIndexChanged || speciesChanged || frame != actorState->copiedFrame) {
        actorState->pendingFrame = frame;
        actorState->textureDirty = true;
    }
    RecordActorProfile(actor, cfg->position, mcssIndex, &identity, assetId, true,
                       actorState->textureDirty, frame);
    actorState->tick = actorState->tick + 1u;
    if (actorState->tick >= totalTicks) {
        actorState->tick = 0;
    }
}

extern "C" void W2U_BattleAnim_Update(void)
{
    RestoreNativeVramMapping();
    W2U_BattleAnim_Profile.updateCalls = W2U_BattleAnim_Profile.updateCalls + 1u;
    W2U_BattleAnim_Profile.lastActiveMask = 0;
    W2U_BattleAnim_Profile.lastTextureDirtyMask = 0;
    void *bmw = GetMcssWork();
    if (!bmw) {
        W2U_BattleAnim_Term();
        return;
    }
    PatchBaseMawileMawWhenMegaVisualInactive(bmw);
    UpdateMegaVisualSettle(bmw);
    PatchMegaMawileBattleSummaryCache();

    for (u32 i = 0; i < ACTOR_COUNT; ++i) {
        UpdateActor((ActorId)i, bmw);
    }
}

extern "C" void W2U_BattleAnim_Draw(void)
{
    W2U_BattleAnim_Profile.drawCalls = W2U_BattleAnim_Profile.drawCalls + 1u;
    PatchMegaMawileBattleSummaryCache();

    b32 needsUpload = false;
    for (u32 i = 0; i < ACTOR_COUNT; ++i) {
        if (!sState.actor[i].active) {
            continue;
        }
        if (sState.actor[i].directObj) {
            continue;
        }
        SetMcssPaletteBase(sState.actor[i].mcss,
                           GetPwanPaletteBase(sState.actor[i].mcssIndex));
        if (sState.actor[i].textureDirty || sState.actor[i].paletteDirty) {
            needsUpload = true;
        }
    }
    if (!needsUpload) {
        DrawDirectObjActor();
        return;
    }

    W2U_BattleAnim_Profile.lastUploadBytes = 0;
    W2U_BattleAnim_Profile.lastUploadActors = 0;
    W2U_BattleAnim_Profile.textureUploadCalls = W2U_BattleAnim_Profile.textureUploadCalls + 1u;

    for (u32 attempt = 0; attempt < ACTOR_COUNT; ++attempt) {
        u32 actorIndex = sState.nextUploadActor + attempt;
        while (actorIndex >= ACTOR_COUNT) {
            actorIndex -= ACTOR_COUNT;
        }
        const ActorId actor = (ActorId)actorIndex;
        ActorState *actorState = &sState.actor[actor];
        if (!actorState->active || actorState->directObj ||
            actorState->mcssIndex < 0 ||
            (!actorState->textureDirty && !actorState->paletteDirty)) {
            continue;
        }

        b32 stagedTexture = true;
        if (actorState->textureDirty) {
            stagedTexture = StageFrameTexture(actor, actorState->pendingFrame);
        }
        if (stagedTexture) {
            WaitForSafeVramUploadTime();
            if (actorState->paletteDirty) {
                CopyPaletteToLiveMcss(actor);
                UploadPalette(actor, GetPwanPaletteBase(actorState->mcssIndex));
            }
            if (actorState->textureDirty) {
                UploadTexture(actor, actorState->mcssIndex);
                actorState->copiedFrame = actorState->pendingFrame;
            }
        } else {
            actorState->textureDirty = false;
            actorState->paletteDirty = false;
        }
        actorIndex = actorIndex + 1u;
        if (actorIndex >= ACTOR_COUNT) {
            actorIndex = 0;
        }
        sState.nextUploadActor = (u8)actorIndex;
        break;
    }
    DrawDirectObjActor();
}

extern "C" void W2U_BattleAnim_Term(void)
{
    HideOam();
    RestoreNativeVramMapping();
    RestoreSuppressedMegaMawileMcss();
    ClearMegaVisualState();
    for (u32 i = 0; i < ACTOR_COUNT; ++i) {
        if (sState.actor[i].directObj) {
            RestoreNativeMcss(sState.actor[i].mcss);
        }
        sState.actor[i].active = false;
        sState.actor[i].directObj = false;
        sState.actor[i].textureDirty = false;
        sState.actor[i].paletteDirty = false;
        sState.actor[i].tick = 0;
        sState.actor[i].copiedFrame = 0xffffu;
        sState.actor[i].pendingFrame = 0xffffu;
        sState.actor[i].mcssIndex = -1;
        sState.actor[i].species = SPECIES_NONE;
        sState.actor[i].form = 0;
        sState.actor[i].assetId = ASSET_NONE;
        sState.actor[i].mcssMawPatched = false;
        sState.actor[i].mcss = 0;
    }
    sState.nextUploadActor = 0;
    sState.savedVramcntEValid = false;
    sState.megaVisualSettleFrames = 0;
    sState.megaVisualRevealHoldFrames = 0;
    sState.megaPwanStreamDelayFrames = 0;
    sState.megaVisualReadyObserved = false;
    sState.megaVisualFirstFrameUploaded = false;
    sState.megaPwanStreamingReady = false;
    sState.megaVisualSuppressed = false;
    sState.megaVisualSuppressedMcss = 0;
    sState.megaSummaryCacheAddress = 0;
    sState.megaSummaryCacheScanCooldown = 0;
}

} // namespace battle_anim
} // namespace w2u
