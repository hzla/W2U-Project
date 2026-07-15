#include "w2u_terrain_texture.h"

#include "Moves.h"
#include "w2u_battle.h"
#include "w2u_battle_lifecycle.h"
#include "swan/gfl/fs/gfl_archive.h"
#include "swan/gfl/g3d/gfl_g3d_system.h"

namespace {

constexpr u32 W2U_BATTGRA_ARC_ID = 11u;
constexpr u32 W2U_FIELD_RENDER_OFFSET = 0x14u;
constexpr u32 W2U_FIELD_PALETTE_RESOURCES_OFFSET = 0x58u;
constexpr u32 W2U_NO_DEFERRED_MESSAGE = 0xFFFFFFFFu;
constexpr u32 W2U_PALETTE_FADE_MAX_EVY = 16u;
constexpr u32 W2U_PALETTE_BACKUP_COLORS = 1024u;
constexpr fx16 W2U_FLOOR_ANIMATION_STEP = static_cast<fx16>(FX32_ONE / 2);
constexpr u32 W2U_NSBTA_MAGIC = 0x30415442u;
constexpr u32 W2U_NITRO_NAME_LENGTH = 16u;
constexpr u16 W2U_NO_FLOOR_ANIMATION_MEMBER = 0xFFFFu;
constexpr u32 W2U_TERRAIN_TEXTURE_COUNT = 4u;

const u8 W2U_FLOOR_ANIMATION_SOURCE_MATERIAL[W2U_NITRO_NAME_LENGTH] = {
    'p', 'a', 's', 't', 'e', 'd', '1', 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
enum ElectricTransitionPhase {
    ELECTRIC_TRANSITION_IDLE = 0,
    ELECTRIC_TRANSITION_WAIT_ANIMATION,
    ELECTRIC_TRANSITION_WAIT_FADE_START,
    ELECTRIC_TRANSITION_WAIT_FADE_END,
};

// This is BTLV_FIELD_WORK::epfw at offset 0x58. The animation VM populates it
// through BTLV_FIELD_SetPaletteFade and the native field main loop advances
// it. Only the fields needed to synchronize the masked upload are mirrored.
struct FieldPaletteFadeWork {
    G3DResource** resources;
    void** destinations;
    u8 active;
    u8 resourceCount;
    u8 startEvy;
    u8 endEvy;
    u8 wait;
    u8 waitCounter;
    u16 rgb;
};

// Each terrain NSBTX is an exact-layout clone of this model's TEX0. Native
// member 119 supplies a one-track NSBTA template; its private loaded copy is
// retargeted from pasted1 to the selected primary floor material.
struct TerrainTextureMapping {
    u16 fieldMember;
    u16 terrainTextureMembers[W2U_TERRAIN_TEXTURE_COUNT];
    u16 floorAnimationMember;
    char floorMaterial[W2U_NITRO_NAME_LENGTH];
};

const TerrainTextureMapping sMappings[] = {
#include "w2u_terrain_texture_mappings.inc"
};

volatile u32 sRequestedTerrain = TERRAIN_NULL;
volatile u32 sRequestSerial = 1u;
volatile u32 sDeferredResetMsgID = W2U_NO_DEFERRED_MESSAGE;
volatile u32 sDeferredResetSerial = 0u;
volatile u32 sElectricTransitionSerial = 0u;
volatile u32 sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
volatile bool sElectricAnimationStarted = false;
u32 sAppliedSerial = 0u;
u32 sPreparedSerial = 0u;
u32 sPrepareFailedSerial = 0u;

void* sFieldWork = 0;
G3DResource* sFieldResource = 0;
G3DResource* sActiveTerrainResource = 0;
G3DResource* sPreparedTerrainResource = 0;
G3DResource* sFloorAnimationResource = 0;
NNSG3DResTex* sFieldTex = 0;
NNSG3DResTex* sActiveTerrainTex = 0;
NNSG3DResTex* sPreparedTerrainTex = 0;
G3DModel* sFieldModel = 0;
G3DAnim* sFloorAnimation = 0;
bool sSupportedField = false;
bool sFloorAnimationBound = false;
bool sFloorAnimationSetupAttempted = false;
u32 sAppliedTerrain = TERRAIN_NULL;
u32 sPreparedTerrain = TERRAIN_NULL;
u16 sFloorAnimationMember = W2U_NO_FLOOR_ANIMATION_MEMBER;
const char* sFloorAnimationMaterial = 0;
const TerrainTextureMapping* sCurrentMapping = 0;
u16 sPaletteBackup[W2U_PALETTE_BACKUP_COLORS];

FieldPaletteFadeWork* GetFieldPaletteFadeWork()
{
    if (!sFieldWork) {
        return 0;
    }

    return reinterpret_cast<FieldPaletteFadeWork*>(
        reinterpret_cast<u8*>(sFieldWork) + W2U_FIELD_PALETTE_RESOURCES_OFFSET);
}

void SetFieldPaletteFadeResource(G3DResource* resource)
{
    if (!sFieldWork || !resource) {
        return;
    }

    // BTLV_FIELD_WORK::epfw.g3DRES is a one-element resource array at
    // offset 0x58.  Native move-animation palette fades read their source
    // palette from this array and upload it to the field palette key.  Point
    // it at the active terrain clone so a fade cannot restore the native
    // green palette on top of terrain-indexed texture pixels.
    G3DResource*** resourceArraySlot =
        reinterpret_cast<G3DResource***>(
            reinterpret_cast<u8*>(sFieldWork) + W2U_FIELD_PALETTE_RESOURCES_OFFSET);
    G3DResource** resourceArray = *resourceArraySlot;
    if (resourceArray) {
        resourceArray[0] = resource;
    }
}

const TerrainTextureMapping* FindMapping(u32 fieldMember)
{
    for (u32 index = 0; index < sizeof(sMappings) / sizeof(sMappings[0]); ++index) {
        if (sMappings[index].fieldMember == fieldMember) {
            return &sMappings[index];
        }
    }
    return 0;
}

bool HasCompatibleLayout(const NNSG3DResTex* fieldTex, const NNSG3DResTex* terrainTex)
{
    return fieldTex && terrainTex &&
        fieldTex->TexHeader.ImageSize == terrainTex->TexHeader.ImageSize &&
        fieldTex->CompressedTexHeader.ImageSize == terrainTex->CompressedTexHeader.ImageSize &&
        fieldTex->PaletteHeader.ImageSize == terrainTex->PaletteHeader.ImageSize;
}

void BorrowFieldVramKeys(NNSG3DResTex* terrainTex, const NNSG3DResTex* fieldTex)
{
    terrainTex->TexHeader.RTVRAMAddr = fieldTex->TexHeader.RTVRAMAddr;
    terrainTex->CompressedTexHeader.RTVRAMAddr = fieldTex->CompressedTexHeader.RTVRAMAddr;
    terrainTex->PaletteHeader.RTVRAMAddr = fieldTex->PaletteHeader.RTVRAMAddr;
}

void DetachBorrowedVramKeys(NNSG3DResTex* terrainTex)
{
    if (!terrainTex) {
        return;
    }

    // The target ROM's GFL free path only returns VRAM allocations whose
    // corresponding loaded flag is set. Clear both the borrowed keys and
    // those flags so freeing the replacement cannot release the field's
    // native allocation.
    terrainTex->TexHeader.RTVRAMAddr = 0u;
    terrainTex->TexHeader.Flags &= ~1u;
    terrainTex->CompressedTexHeader.RTVRAMAddr = 0u;
    terrainTex->CompressedTexHeader.Flags &= ~1u;
    terrainTex->PaletteHeader.RTVRAMAddr = 0u;
    terrainTex->PaletteHeader.Flags &= ~1u;
}

void ReleaseTerrainResource(G3DResource*& resource, NNSG3DResTex*& texture)
{
    DetachBorrowedVramKeys(texture);
    if (resource) {
        GFL_G3DResFree(resource);
    }

    resource = 0;
    texture = 0;
}

void ReleaseActiveTerrainResource()
{
    ReleaseTerrainResource(sActiveTerrainResource, sActiveTerrainTex);
    sAppliedTerrain = TERRAIN_NULL;
}

void ReleasePreparedTerrainResource()
{
    // Unpublish the pending slot before freeing it so VBlank can never select
    // a half-replaced resource while the main viewer command prepares one.
    sPreparedTerrain = TERRAIN_NULL;
    sPreparedSerial = 0u;
    ReleaseTerrainResource(sPreparedTerrainResource, sPreparedTerrainTex);
}

s32 TerrainTextureIndex(u32 terrain)
{
    if (terrain < TERRAIN_ELECTRIC || terrain > TERRAIN_PSYCHIC) {
        return -1;
    }
    return static_cast<s32>(terrain - TERRAIN_ELECTRIC);
}

u32 TerrainForMove(u32 moveID)
{
    static const u16 moveIDs[W2U_TERRAIN_TEXTURE_COUNT] = {
        MOVE_ELECTRIC_TERRAIN,
        MOVE_GRASSY_TERRAIN,
        MOVE_MISTY_TERRAIN,
        MOVE_PSYCHIC_TERRAIN,
    };
    for (u32 index = 0; index < W2U_TERRAIN_TEXTURE_COUNT; ++index) {
        if (moveID == moveIDs[index]) {
            return TERRAIN_ELECTRIC + index;
        }
    }
    return TERRAIN_NULL;
}

G3DResource* GetVisiblePaletteResource()
{
    return sActiveTerrainResource
        ? sActiveTerrainResource
        : sFieldResource;
}

bool PrepareTerrainResource(u32 terrain, u32 serial)
{
    const s32 terrainIndex = TerrainTextureIndex(terrain);
    if (!sSupportedField || !sCurrentMapping || !sFieldTex || terrainIndex < 0) {
        return false;
    }
    if (sAppliedTerrain == terrain && sActiveTerrainResource) {
        return true;
    }
    if (sPreparedTerrain == terrain &&
        sPreparedSerial == serial &&
        sPreparedTerrainResource) {
        return true;
    }

    ReleasePreparedTerrainResource();
    G3DResource* resource = GFL_G3DSysReadArcSysResource(
        W2U_BATTGRA_ARC_ID,
        sCurrentMapping->terrainTextureMembers[terrainIndex]);
    if (!resource) {
        return false;
    }

    NNSG3DResTex* texture = GFL_G3DResGetTexData(resource);
    if (!HasCompatibleLayout(sFieldTex, texture)) {
        GFL_G3DResFree(resource);
        return false;
    }

    BorrowFieldVramKeys(texture, sFieldTex);
    sPreparedTerrainResource = resource;
    sPreparedTerrainTex = texture;
    sPreparedSerial = serial;
    sPreparedTerrain = terrain;
    return true;
}

G3DModel* GetFieldModel(void* fieldWork)
{
    if (!fieldWork) {
        return 0;
    }

    return *reinterpret_cast<G3DModel**>(
        reinterpret_cast<u8*>(fieldWork) + W2U_FIELD_RENDER_OFFSET);
}

bool RetargetFloorAnimationResource(G3DResource* resource, const char* targetMaterial)
{
    NNSG3DResData* resourceData = resource
        ? GFL_G3DResGetResData(resource)
        : 0;
    if (!resourceData || !targetMaterial ||
        static_cast<u32>(resourceData->Header.Magic) != W2U_NSBTA_MAGIC ||
        resourceData->Header.FileSize < W2U_NITRO_NAME_LENGTH) {
        return false;
    }

    u8* bytes = reinterpret_cast<u8*>(resourceData);
    const u32 size = resourceData->Header.FileSize;
    u32 matchOffset = size;
    u32 matchCount = 0u;
    for (u32 offset = 0; offset + W2U_NITRO_NAME_LENGTH <= size; ++offset) {
        bool matches = true;
        for (u32 index = 0; index < W2U_NITRO_NAME_LENGTH; ++index) {
            if (bytes[offset + index] != W2U_FLOOR_ANIMATION_SOURCE_MATERIAL[index]) {
                matches = false;
                break;
            }
        }
        if (matches) {
            matchOffset = offset;
            ++matchCount;
        }
    }
    if (matchCount != 1u) {
        return false;
    }

    for (u32 index = 0; index < W2U_NITRO_NAME_LENGTH; ++index) {
        bytes[matchOffset + index] = 0u;
    }
    for (u32 index = 0;
         index + 1u < W2U_NITRO_NAME_LENGTH && targetMaterial[index];
         ++index) {
        bytes[matchOffset + index] = static_cast<u8>(targetMaterial[index]);
    }
    return true;
}

bool BindFloorAnimation()
{
    if (!sFieldModel || !sFloorAnimation) {
        return false;
    }

    // GFL's actor helper is the target ROM's public wrapper around the native
    // NNS render-object animation list. A tiny proxy lets this additional
    // animation bind to the already-live field model without resizing the
    // BTLV_FIELD actor's fixed native animation array.
    G3DAnim* animations[] = { sFloorAnimation };
    G3DActor proxy = { sFieldModel, animations, 1u, 0u };
    return GFL_G3DActorBindAnm(&proxy, 0u);
}

void ResetFloorAnimation()
{
    if (!sFieldModel || !sFloorAnimation || !sFloorAnimationBound) {
        return;
    }

    G3DAnim* animations[] = { sFloorAnimation };
    G3DActor proxy = { sFieldModel, animations, 1u, 0u };
    fx32 frame = 0;
    GFL_G3DActorSetAnmFrame(&proxy, 0u, &frame);
}

void ReleaseFloorAnimation()
{
    if (sFieldModel && sFloorAnimation && sFloorAnimationBound) {
        ResetFloorAnimation();
        G3DAnim* animations[] = { sFloorAnimation };
        G3DActor proxy = { sFieldModel, animations, 1u, 0u };
        GFL_G3DActorUnbindAnm(&proxy, 0u);
    }

    sFloorAnimationBound = false;
    if (sFloorAnimation) {
        GFL_G3DAnmFree(sFloorAnimation);
    }
    if (sFloorAnimationResource) {
        GFL_G3DResFree(sFloorAnimationResource);
    }

    sFloorAnimation = 0;
    sFloorAnimationResource = 0;
}

bool SetupFloorAnimation(u16 animationMember)
{
    if (!sFieldModel) {
        return false;
    }

    sFloorAnimationResource = GFL_G3DSysReadArcSysResource(
        W2U_BATTGRA_ARC_ID,
        animationMember);
    if (!RetargetFloorAnimationResource(
            sFloorAnimationResource,
            sFloorAnimationMaterial)) {
        ReleaseFloorAnimation();
        return false;
    }

    sFloorAnimation = GFL_G3DAnmCreate(sFieldModel, sFloorAnimationResource, 0u);
    if (!sFloorAnimation) {
        ReleaseFloorAnimation();
        return false;
    }

    sFloorAnimationBound = BindFloorAnimation();
    if (!sFloorAnimationBound) {
        ReleaseFloorAnimation();
        return false;
    }

    ResetFloorAnimation();
    return true;
}

bool EnsureFloorAnimation()
{
    if (sFloorAnimationBound) {
        return true;
    }
    if (sFloorAnimationSetupAttempted ||
        !sFieldWork ||
        sFloorAnimationMember == W2U_NO_FLOOR_ANIMATION_MEMBER) {
        return false;
    }

    // The field-init hook runs at the native texture-upload call. SWAN's
    // BTLV_FIELD_Init creates field_render later in the same function, so it
    // is necessarily null at hook time. Resolve it lazily from the completed
    // work object on the first viewer update instead.
    sFieldModel = GetFieldModel(sFieldWork);
    if (!sFieldModel) {
        return false;
    }

    sFloorAnimationSetupAttempted = true;
    return SetupFloorAnimation(sFloorAnimationMember);
}

void ClearFieldViewState()
{
    SetFieldPaletteFadeResource(sFieldResource);
    ReleaseFloorAnimation();
    ReleasePreparedTerrainResource();
    ReleaseActiveTerrainResource();
    sFieldWork = 0;
    sFieldResource = 0;
    sFieldTex = 0;
    sFieldModel = 0;
    sSupportedField = false;
    sCurrentMapping = 0;
    sFloorAnimationMaterial = 0;
    sElectricTransitionSerial = 0u;
    sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
    sElectricAnimationStarted = false;
    sFloorAnimationSetupAttempted = false;
    sFloorAnimationMember = W2U_NO_FLOOR_ANIMATION_MEMBER;
    sPreparedSerial = 0u;
    sPrepareFailedSerial = 0u;
    sAppliedSerial = sRequestSerial;
}

bool UploadTexture(G3DResource* resource)
{
    // GFL's target-ROM upload core uses the keys already present in the TEX0
    // headers and transfers both image and palette data. Keeping this behind
    // the verified public GFL interface avoids binary-variant-specific raw
    // Nitro function addresses.
    return resource && GFL_G3DResUploadTexDataCore(resource);
}

u32 FadeColorComponent(u32 before, u32 after, u32 evy)
{
    return before +
        static_cast<u32>((static_cast<s32>(after) - static_cast<s32>(before)) *
            static_cast<s32>(evy) >> 4);
}

u16 FadeColor(u16 source, u16 target, u32 evy)
{
    const u32 sourceRed = source & 0x1Fu;
    const u32 sourceGreen = (source >> 5) & 0x1Fu;
    const u32 sourceBlue = (source >> 10) & 0x1Fu;
    const u32 targetRed = target & 0x1Fu;
    const u32 targetGreen = (target >> 5) & 0x1Fu;
    const u32 targetBlue = (target >> 10) & 0x1Fu;

    return static_cast<u16>(
        FadeColorComponent(sourceRed, targetRed, evy) |
        (FadeColorComponent(sourceGreen, targetGreen, evy) << 5) |
        (FadeColorComponent(sourceBlue, targetBlue, evy) << 10));
}

bool UploadTextureAtFade(
    G3DResource* resource,
    NNSG3DResTex* texture,
    u32 evy,
    u16 rgb)
{
    if (!resource || !texture) {
        return false;
    }

    const u32 paletteBytes = static_cast<u32>(texture->PaletteHeader.ImageSize) << 3;
    if ((paletteBytes & 1u) || paletteBytes > sizeof(sPaletteBackup)) {
        return false;
    }

    u16* palette = static_cast<u16*>(GFL_G3DResGetTexPaletteData(resource));
    if (!palette) {
        return false;
    }

    const u32 colorCount = paletteBytes / sizeof(u16);
    if (evy > W2U_PALETTE_FADE_MAX_EVY) {
        evy = W2U_PALETTE_FADE_MAX_EVY;
    }

    // Upload the new image with a palette matching the field's completed
    // fade. The image-index change is therefore invisible. Restore the raw
    // palette afterward so the VM can fade the Electric palette back in.
    for (u32 index = 0; index < colorCount; ++index) {
        sPaletteBackup[index] = palette[index];
        palette[index] = FadeColor(palette[index], rgb, evy);
    }

    const bool uploaded = UploadTexture(resource);

    for (u32 index = 0; index < colorCount; ++index) {
        palette[index] = sPaletteBackup[index];
    }

    return uploaded;
}

} // namespace

extern "C" void W2U_TerrainTexture_Request(u32 terrain)
{
    sDeferredResetMsgID = W2U_NO_DEFERRED_MESSAGE;
    sDeferredResetSerial = 0u;
    sRequestedTerrain = terrain;
    sRequestSerial = sRequestSerial + 1u;
    if (sRequestSerial == 0u) {
        sRequestSerial = 1u;
    }
    sPrepareFailedSerial = 0u;

    if (terrain == TERRAIN_ELECTRIC && sAppliedTerrain != TERRAIN_ELECTRIC) {
        sElectricTransitionSerial = sRequestSerial;
        sElectricTransitionPhase = sElectricAnimationStarted
            ? ELECTRIC_TRANSITION_WAIT_FADE_START
            : ELECTRIC_TRANSITION_WAIT_ANIMATION;
    } else {
        sElectricTransitionSerial = 0u;
        sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
        sElectricAnimationStarted = false;
    }
}

extern "C" void W2U_TerrainTexture_DeferResetUntilMessage(u32 msgID)
{
    sDeferredResetMsgID = msgID;
    sDeferredResetSerial = sRequestSerial;
}

extern "C" void W2U_TerrainTexture_OnSetMessageStart(u32 msgID)
{
    if (msgID != sDeferredResetMsgID) {
        return;
    }

    const u32 deferredSerial = sDeferredResetSerial;
    sDeferredResetMsgID = W2U_NO_DEFERRED_MESSAGE;
    sDeferredResetSerial = 0u;

    // A replacement terrain may have been queued while the viewer was still
    // consuming older commands.  Never let the stale expiry message clear a
    // newer terrain request.
    if (sRequestSerial == deferredSerial) {
        W2U_TerrainTexture_Request(TERRAIN_NULL);
    }
}

extern "C" void W2U_TerrainTexture_OnMoveAnimationStart(u32 moveID)
{
    const u32 terrain = TerrainForMove(moveID);
    if (terrain == TERRAIN_NULL || sRequestedTerrain != terrain) {
        return;
    }

    const u32 requestSerial = sRequestSerial;
    if (!PrepareTerrainResource(terrain, requestSerial)) {
        sPrepareFailedSerial = requestSerial;
        return;
    }

    sPrepareFailedSerial = 0u;
    if (terrain == TERRAIN_ELECTRIC && sAppliedTerrain != TERRAIN_ELECTRIC) {
        sElectricAnimationStarted = true;
        sElectricTransitionSerial = sRequestSerial;
        sElectricTransitionPhase = ELECTRIC_TRANSITION_WAIT_FADE_START;
    }
}

extern "C" void W2U_TerrainTexture_FieldInit(
    void* fieldWork,
    G3DResource* fieldResource,
    u32 battgraMember)
{
    // Defensive cleanup for an interrupted/re-entered viewer lifetime.  The
    // normal path invokes FieldExit before the next FieldInit.
    ClearFieldViewState();

    const TerrainTextureMapping* mapping = FindMapping(battgraMember);
    if (!fieldResource || !mapping) {
        return;
    }

    sFieldWork = fieldWork;
    sFieldResource = fieldResource;
    sFieldTex = GFL_G3DResGetTexData(fieldResource);
    sCurrentMapping = mapping;
    sFloorAnimationMember = mapping->floorAnimationMember;
    sFloorAnimationMaterial = mapping->floorMaterial;

    if (!sFieldTex ||
        (sFieldTex->TexHeader.ImageSize && !sFieldTex->TexHeader.RTVRAMAddr) ||
        (sFieldTex->CompressedTexHeader.ImageSize && !sFieldTex->CompressedTexHeader.RTVRAMAddr) ||
        (sFieldTex->PaletteHeader.ImageSize && !sFieldTex->PaletteHeader.RTVRAMAddr)) {
        ClearFieldViewState();
        return;
    }

    // Animation is created lazily after BTLV_FIELD_Init has constructed its
    // render object. It remains an enhancement rather than a prerequisite for
    // the terrain swap: setup failure must leave the static texture active.
    sSupportedField = true;
    sAppliedSerial = 0u;
}

extern "C" void W2U_TerrainTexture_ApplyPending()
{
    const u32 requestedSerial = sRequestSerial;
    if (requestedSerial == sAppliedSerial) {
        return;
    }

    if (!sSupportedField || !sFieldTex || !sCurrentMapping) {
        ReleasePreparedTerrainResource();
        sElectricTransitionSerial = 0u;
        sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
        sElectricAnimationStarted = false;
        sAppliedSerial = requestedSerial;
        return;
    }

    const u32 requestedTerrain = sRequestedTerrain;
    if (requestedTerrain == TERRAIN_NULL) {
        ReleasePreparedTerrainResource();
        if (sAppliedTerrain != TERRAIN_NULL) {
            SetFieldPaletteFadeResource(sFieldResource);
            if (UploadTexture(sFieldResource)) {
                ResetFloorAnimation();
                ReleaseActiveTerrainResource();
            } else {
                SetFieldPaletteFadeResource(GetVisiblePaletteResource());
            }
        } else {
            SetFieldPaletteFadeResource(sFieldResource);
        }
    } else if (requestedTerrain == sAppliedTerrain && sActiveTerrainResource) {
        ReleasePreparedTerrainResource();
        SetFieldPaletteFadeResource(sActiveTerrainResource);
    } else if (sPrepareFailedSerial == requestedSerial) {
        ReleasePreparedTerrainResource();
        SetFieldPaletteFadeResource(GetVisiblePaletteResource());
    } else {
        if (sPreparedSerial != requestedSerial ||
            sPreparedTerrain != requestedTerrain ||
            !sPreparedTerrainResource ||
            !sPreparedTerrainTex) {
            // The resource is deliberately loaded by the move-start callback,
            // outside VBlank and only for the terrain that is about to appear.
            return;
        }

        bool readyToUpload = requestedTerrain != TERRAIN_ELECTRIC;
        bool maskedElectricUpload = false;
        FieldPaletteFadeWork* fadeWork = 0;
        if (requestedTerrain == TERRAIN_ELECTRIC) {
            if (sElectricTransitionSerial != requestedSerial) {
                sElectricTransitionSerial = requestedSerial;
                sElectricTransitionPhase = sElectricAnimationStarted
                    ? ELECTRIC_TRANSITION_WAIT_FADE_START
                    : ELECTRIC_TRANSITION_WAIT_ANIMATION;
            }

            fadeWork = GetFieldPaletteFadeWork();
            if (sElectricTransitionPhase == ELECTRIC_TRANSITION_WAIT_ANIMATION) {
                return;
            }
            if (sElectricTransitionPhase == ELECTRIC_TRANSITION_WAIT_FADE_START) {
                // Ignore the animation's pre-existing 0->12 all-background
                // tint. The added field-only 0->16 black fade is the texture-
                // swap mask.
                if (!fadeWork || !fadeWork->active ||
                    fadeWork->endEvy != W2U_PALETTE_FADE_MAX_EVY ||
                    fadeWork->rgb != 0u) {
                    return;
                }
                sElectricTransitionPhase = ELECTRIC_TRANSITION_WAIT_FADE_END;
                return;
            }
            if (sElectricTransitionPhase == ELECTRIC_TRANSITION_WAIT_FADE_END) {
                if (!fadeWork || fadeWork->active) {
                    return;
                }
                readyToUpload = true;
                maskedElectricUpload = true;
            }
        }

        if (!readyToUpload) {
            return;
        }

        SetFieldPaletteFadeResource(sPreparedTerrainResource);
        const bool uploaded = maskedElectricUpload
            ? UploadTextureAtFade(
                sPreparedTerrainResource,
                sPreparedTerrainTex,
                W2U_PALETTE_FADE_MAX_EVY,
                fadeWork ? fadeWork->rgb : 0u)
            : UploadTexture(sPreparedTerrainResource);
        if (uploaded) {
            G3DResource* previousResource = sActiveTerrainResource;
            NNSG3DResTex* previousTex = sActiveTerrainTex;
            sActiveTerrainResource = sPreparedTerrainResource;
            sActiveTerrainTex = sPreparedTerrainTex;
            sPreparedTerrainResource = 0;
            sPreparedTerrainTex = 0;
            sPreparedTerrain = TERRAIN_NULL;
            sPreparedSerial = 0u;
            sAppliedTerrain = requestedTerrain;
            SetFieldPaletteFadeResource(sActiveTerrainResource);
            ReleaseTerrainResource(previousResource, previousTex);
            ResetFloorAnimation();
        } else {
            SetFieldPaletteFadeResource(GetVisiblePaletteResource());
            ReleasePreparedTerrainResource();
        }
    }

    sElectricTransitionSerial = 0u;
    sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
    sElectricAnimationStarted = false;
    sPrepareFailedSerial = 0u;
    sAppliedSerial = requestedSerial;
}

extern "C" void W2U_TerrainTexture_AdvanceAnimation()
{
    if (sAppliedTerrain == TERRAIN_NULL || !EnsureFloorAnimation()) {
        return;
    }

    G3DAnim* animations[] = { sFloorAnimation };
    G3DActor proxy = { sFieldModel, animations, 1u, 0u };
    GFL_G3DActorStepAnmFrameLoop(&proxy, 0u, W2U_FLOOR_ANIMATION_STEP);
}

extern "C" void W2U_TerrainTexture_FieldExit()
{
    W2U_BattleState_OnBattleExit();
    sRequestedTerrain = TERRAIN_NULL;
    sDeferredResetMsgID = W2U_NO_DEFERRED_MESSAGE;
    sDeferredResetSerial = 0u;
    sRequestSerial = sRequestSerial + 1u;
    if (sRequestSerial == 0u) {
        sRequestSerial = 1u;
    }
    ClearFieldViewState();
}
