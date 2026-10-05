#include "w2u_terrain_texture.h"

#include "Moves.h"
#include "w2u_battle.h"
#include "w2u_battle_lifecycle.h"
#include "w2u_platform.h"
#include "swan/gfl/core/gfl_heap.h"
#include "swan/gfl/fs/gfl_archive.h"
#include "swan/gfl/g3d/gfl_g3d_system.h"
#include "swan/math/vector.h"
#include "swan/nds/cp15.h"
#include "swan/nds/gx.h"

extern "C" void* BTLV_EFFECT_GetMcssWork();
extern "C" void BTLV_MCSS_GetPokeDefaultPos(void* mcssWork, VecFx32* position, int slot);
extern "C" void* GFL_PTC_CreateEx(
    void* work,
    int workSize,
    b32 personalCamera,
    int fixedPolygonID,
    int minimumPolygonID,
    int maximumPolygonID,
    HeapID heapID);
extern "C" void GFL_PTC_Delete(void* particleSystem);
extern "C" void* GFL_PTC_LoadArcResource(int archiveID, int member, HeapID heapID);
extern "C" void GFL_PTC_SetResourceSetup(void* particleSystem, void* resource);
extern "C" void GFL_PTC_LoadTex(void* particleSystem);
extern "C" void* GFL_PTC_CreateEmitter(
    void* particleSystem,
    int resourceIndex,
    const VecFx32* initialPosition);
extern "C" fx32 GFL_PTC_GetEmitterRadius(void* emitter);
extern "C" void GFL_PTC_SetEmitterRadius(void* emitter, fx32 radius);
extern "C" fx32 GFL_PTC_GetEmitterLength(void* emitter);
extern "C" void GFL_PTC_SetEmitterLength(void* emitter, fx32 length);

#if !defined(W2U_TARGET_B2)
// Floor fades (White 2): the terrain floor fades in and out instead of switching at once. Black 2 keeps the
// immediate swap until its battle-viewer addresses are verified.
#define W2U_TERRAIN_FLOOR_FADES 1
extern "C" int GFL_PTC_GetEmitterNum(void* particleSystem);   // live emitters (gx.h / cp15.h: the uploads)
#endif

namespace {

constexpr u32 W2U_BATTGRA_ARC_ID = 11u;
constexpr u32 W2U_PTC_ARC_ID = 6u;
constexpr u32 W2U_ELECTRIC_AMBIENT_SPA_MEMBER = 787u;
constexpr u32 W2U_GRASSY_AMBIENT_SPA_MEMBER = 788u;
constexpr u32 W2U_MISTY_AMBIENT_SPA_MEMBER = 789u;
constexpr u32 W2U_PSYCHIC_AMBIENT_SPA_MEMBER = 790u;
constexpr u32 W2U_ELECTRIC_AMBIENT_ANCHOR_COUNT = 6u;
constexpr u32 W2U_BATTLER_AMBIENT_ANCHOR_COUNT = 2u;
// Grassy (motes) and Misty (fog) emit over the whole floor: player side, middle, foe side in turn
// (tools/graphics/build_terrain_ambient_effects.py draws both SPAs).
constexpr u32 W2U_FIELD_AMBIENT_ANCHOR_COUNT = 3u;
constexpr s32 W2U_MISTY_FOG_X_OFFSET = -FX32_ONE * 5 / 2;   // the fog rolls towards +X (screen right)
constexpr u32 W2U_PARTICLE_LIBRARY_HEAP_SIZE = 0x4800u;
// Starting a terrain through a Surge ability happens while the switch-in and
// terrain move animations still need this heap.  Leave room for those native
// viewer allocations in addition to the standalone ambient SPA resource.
constexpr u32 W2U_PARTICLE_ALLOCATION_HEADROOM = 0x3000u;
constexpr u32 W2U_PARTICLE_POLYGON_ID_FIXED = 5u;
constexpr u32 W2U_PARTICLE_POLYGON_ID_MINIMUM = 6u;
constexpr u32 W2U_PARTICLE_POLYGON_ID_MAXIMUM = 54u;
constexpr u32 W2U_PARTICLE_Z_PRIORITY_OFFSET = 0x500u;
constexpr u32 W2U_PSYCHIC_AMBIENT_Y_OFFSET = 0x2000u;
constexpr u32 W2U_FIELD_RENDER_OFFSET = 0x14u;
constexpr u32 W2U_FIELD_PALETTE_RESOURCES_OFFSET = 0x58u;
constexpr u32 W2U_FIELD_HEAP_ID_OFFSET = 0x6Cu;
constexpr u32 W2U_NO_DEFERRED_MESSAGE = 0xFFFFFFFFu;
constexpr u32 W2U_PALETTE_FADE_MAX_EVY = 16u;
constexpr u32 W2U_PALETTE_BACKUP_COLORS = 1024u;
constexpr u32 W2U_NSBTA_MAGIC = 0x30415442u;
constexpr u32 W2U_NITRO_NAME_LENGTH = 16u;
constexpr u16 W2U_NO_FLOOR_ANIMATION_MEMBER = 0xFFFFu;
constexpr u32 W2U_TERRAIN_TEXTURE_COUNT = 4u;

const u8 W2U_FLOOR_ANIMATION_SOURCE_MATERIAL[W2U_NITRO_NAME_LENGTH] = {
    'p', 'a', 's', 't', 'e', 'd', '1', 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
const s32 W2U_ELECTRIC_AMBIENT_RADIUS_QUARTERS[W2U_ELECTRIC_AMBIENT_ANCHOR_COUNT] = {
    4, 40, 11, 33, 18, 26,
};
enum ElectricTransitionPhase {
    ELECTRIC_TRANSITION_IDLE = 0,
    ELECTRIC_TRANSITION_WAIT_ANIMATION,
    ELECTRIC_TRANSITION_WAIT_FADE_START,
    ELECTRIC_TRANSITION_WAIT_FADE_END,
};

// Each terrain's pace: the floor's UV animation (NSBTA frames per 60 fps frame), the gap between ambient particle
// emits, and the floor fade's two halves (old floor -> blend colour, blend colour -> new floor; frames). Electric
// is quick and busy; Grassy and Misty are slow and calm; Psychic's floor speed and emit gaps keep changing
// (PsychicFloorStep, W2U_PSYCHIC_AMBIENT_GAPS) and its fade wobbles.
struct TerrainPace {
    fx32 floorStep;
    u16 ambientInterval;
    u8 fadeOutFrames;
    u8 fadeInFrames;
};
const TerrainPace W2U_TERRAIN_PACE[W2U_TERRAIN_TEXTURE_COUNT] = {
    { FX32_ONE * 5 / 4, 20u, 10u, 14u },     // Electric
    { FX32_ONE * 5 / 16, 44u, 26u, 40u },    // Grassy (a 96-frame mote emitter every 44 frames; floor: W2U_FLOOR_DRIFT)
    { FX32_ONE / 4, 56u, 30u, 46u },         // Misty (a 110-frame fog emitter every 56 frames; floor: W2U_FLOOR_DRIFT)
    { FX32_ONE * 9 / 16, 60u, 20u, 30u },    // Psychic (floorStep: mean; ambientInterval unused)
};
constexpr u32 W2U_NATIVE_FLOOR_FADE_OUT_FRAMES = 20u;
const u8 W2U_PSYCHIC_AMBIENT_GAPS[] = { 34, 82, 47, 96, 28, 63, 110, 41 };
constexpr fx32 W2U_PSYCHIC_FLOOR_STEP_MIN = FX32_ONE / 24;

// sin(angle) in fx32, angle in 1/65536 turns (quarter-wave table, linear between 16 steps).
fx32 SinTurn(u32 angle)
{
    static const u16 kQuarter[17] = {
        0, 402, 799, 1189, 1567, 1931, 2276, 2598, 2896, 3166, 3406, 3612, 3784, 3920, 4017, 4076, 4096,
    };
    angle &= 0xFFFFu;
    const u32 quadrant = angle >> 14;
    u32 a = angle & 0x3FFFu;
    if (quadrant & 1u) {
        a = 0x4000u - a;
    }
    const u32 index = a >> 10;
    const u32 frac = a & 0x3FFu;
    const s32 lo = kQuarter[index];
    const s32 hi = kQuarter[index < 16u ? index + 1u : 16u];
    const s32 value = lo + (((hi - lo) * static_cast<s32>(frac)) >> 10);
    return (quadrant & 2u) ? -value : value;
}

// Psychic's floor: two out-of-step waves around the mean, so it surges, crawls and surges again.
fx32 PsychicFloorStep(u32 frame)
{
    const fx32 mean = W2U_TERRAIN_PACE[3].floorStep;
    const fx32 step = mean +
        static_cast<fx32>((static_cast<s64>(FX32_ONE * 7 / 16) * SinTurn(frame * 580u)) >> 12) +    // ~113 frames
        static_cast<fx32>((static_cast<s64>(FX32_ONE * 5 / 16) * SinTurn(frame * 1771u)) >> 12);    // ~37 frames
    return step < W2U_PSYCHIC_FLOOR_STEP_MIN ? W2U_PSYCHIC_FLOOR_STEP_MIN : step;
}

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
    // The generated Electric/Grassy/Misty/Psychic resources are always four
    // consecutive archive members. Store only the first member so expanding
    // background coverage does not waste resident PMC heap on redundant IDs.
    u16 terrainTextureBaseMember;
    u16 floorAnimationMember;
    char floorMaterial[W2U_NITRO_NAME_LENGTH];
    // The backdrop's (batt_sky*) palette range in colours; Grassy / Misty clones replace that sky (0: none).
    u16 skyPaletteFirst;
    u16 skyPaletteCount;
};

const TerrainTextureMapping sMappings[] = {
#include "w2u_terrain_texture_mappings.inc"
};

volatile u32 sRequestedTerrain = TERRAIN_NULL;
volatile u32 sRequestSerial = 1u;
volatile u32 sDeferredResetMsgID = W2U_NO_DEFERRED_MESSAGE;
volatile u32 sDeferredResetSerial = 0u;
volatile u32 sDeferredStartMsgID = W2U_NO_DEFERRED_MESSAGE;   // an ability's terrain: starts with this message
volatile u32 sDeferredStartSerial = 0u;
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
u32* sFloorTrackWords = 0;                     // the loaded floor animation's words (0: not the template)
u32 sFloorTrackOriginal[4];                    // its translate S, translate T as loaded
bool sFloorScrollHorizontal = false;
u32 sAppliedTerrain = TERRAIN_NULL;
u32 sPreparedTerrain = TERRAIN_NULL;
u16 sFloorAnimationMember = W2U_NO_FLOOR_ANIMATION_MEMBER;
const char* sFloorAnimationMaterial = 0;
const TerrainTextureMapping* sCurrentMapping = 0;
u16 sPaletteBackup[W2U_PALETTE_BACKUP_COLORS];
u32 sTerrainAmbientFrame = 0u;
u32 sTerrainAmbientStep = 0u;
void* sTerrainAmbientParticleHeap = 0;
void* sTerrainAmbientParticleSystem = 0;
u32 sTerrainAmbientParticleTerrain = TERRAIN_NULL;
bool sTerrainAmbientTexturePending = false;
bool sTerrainAmbientTextureReady = false;
// The floor is fading out: no new ambient emits; the particle system is released once its emitters have died out
// (at most W2U_AMBIENT_DRAIN_MAX_FRAMES later).
bool sTerrainAmbientStopping = false;
u32 sTerrainAmbientDrainFrames = 0u;
constexpr u32 W2U_AMBIENT_DRAIN_MAX_FRAMES = 360u;
u32 sPsychicFloorFrame = 0u;
u32 sPsychicGapIndex = 0u;

void ResetTerrainAmbientTimer()
{
    sTerrainAmbientFrame = 0u;
    sTerrainAmbientStep = 0u;
}

HeapID GetFieldLowHeapID()
{
    if (!sFieldWork) {
        return 0u;
    }
    const u32 heapID = *reinterpret_cast<const u32*>(
        reinterpret_cast<const u8*>(sFieldWork) + W2U_FIELD_HEAP_ID_OFFSET);
#if !defined(W2U_TARGET_B2)
    // The native heap queries resolve the ID to a heap handle without checking
    // it: an ID whose heap does not exist (for example when a battle starts
    // without the field, as the direct battle harness does) makes
    // GFL_HeapGetHighestAllocatableSize walk a free list from address 0 and
    // never return.  Treat a missing heap like an unavailable one.
    typedef void* (*HeapHandleForIdFn)(u32 heapID);
    const HeapHandleForIdFn heapHandleForId = (HeapHandleForIdFn)W2U_ADDR_GFL_HEAP_HANDLE_FOR_ID;
    if (!heapHandleForId(heapID & 0x7FFFu)) {
        return 0u;
    }
#endif
    return static_cast<HeapID>((heapID & 0x7FFFu) | 0x8000u);
}

#if !defined(W2U_TARGET_B2)
// The battle's own graphics heap (the heap MCSS gave its sprites: core +0x190 wrapper, entry +8 sprite, +0x14C), for
// battles whose field heap does not exist (a battle started without the field, as the direct battle harness does).
HeapID GetBattleSpriteLowHeapID()
{
    constexpr u32 BTLV_CORE_PTR = 0x021F4280u;
    const u8* core = *reinterpret_cast<u8* const*>(BTLV_CORE_PTR);
    const u8* wrap = core ? *reinterpret_cast<u8* const*>(core + 0x190) : 0;
    if (!wrap) {
        return 0u;
    }
    typedef void* (*HeapHandleForIdFn)(u32 heapID);
    const HeapHandleForIdFn heapHandleForId = (HeapHandleForIdFn)W2U_ADDR_GFL_HEAP_HANDLE_FOR_ID;
    for (u32 entry = 0; entry < 14u; ++entry) {
        const u8* sprite = *reinterpret_cast<u8* const*>(wrap + entry * 0x5Cu + 8u);
        if (!sprite) {
            continue;
        }
        const u32 heapID = *reinterpret_cast<const u32*>(sprite + 0x14C) & 0x7FFFu;
        return heapHandleForId(heapID) ? static_cast<HeapID>(heapID | 0x8000u) : 0u;
    }
    return 0u;
}
#endif

void ReleaseTerrainAmbientParticles()
{
    if (sTerrainAmbientParticleSystem) {
        GFL_PTC_Delete(sTerrainAmbientParticleSystem);
        sTerrainAmbientParticleSystem = 0;
    }
    if (sTerrainAmbientParticleHeap) {
        GFL_HeapFreeCore(sTerrainAmbientParticleHeap);
        sTerrainAmbientParticleHeap = 0;
    }
    sTerrainAmbientParticleTerrain = TERRAIN_NULL;
    sTerrainAmbientTexturePending = false;
    sTerrainAmbientTextureReady = false;
    sTerrainAmbientStopping = false;
    sTerrainAmbientDrainFrames = 0u;
    ResetTerrainAmbientTimer();
}

u32 AmbientSpaMemberForTerrain(u32 terrain)
{
    if (terrain == TERRAIN_ELECTRIC) {
        return W2U_ELECTRIC_AMBIENT_SPA_MEMBER;
    }
    if (terrain == TERRAIN_GRASSY) {
        return W2U_GRASSY_AMBIENT_SPA_MEMBER;
    }
    if (terrain == TERRAIN_MISTY) {
        return W2U_MISTY_AMBIENT_SPA_MEMBER;
    }
    if (terrain == TERRAIN_PSYCHIC) {
        return W2U_PSYCHIC_AMBIENT_SPA_MEMBER;
    }
    return 0u;
}

bool PrepareTerrainAmbientParticles(u32 terrain)
{
    const u32 spaMember = AmbientSpaMemberForTerrain(terrain);
    if (!spaMember) {
        return false;
    }
    if (sTerrainAmbientParticleSystem &&
        sTerrainAmbientParticleTerrain == terrain) {
        return true;
    }
    if (sTerrainAmbientParticleSystem) {
        ReleaseTerrainAmbientParticles();
    }

    HeapID heapID = GetFieldLowHeapID();
#if !defined(W2U_TARGET_B2)
    if (!heapID) {
        heapID = GetBattleSpriteLowHeapID();     // same preflight below: only when it has the room
    }
#endif
    if (!heapID) {
        return false;
    }

    // GFL_HeapAllocate() treats allocation failure as a fatal assertion.  The
    // ambient particle system is optional, so preflight its complete memory
    // footprint and use the non-asserting core allocator for its work buffer.
    // This lets the terrain mechanic, texture, and one-shot move animation
    // continue when a switch-in leaves too little contiguous viewer heap.
    const u32 resourceBytes = GFL_ArcSysGetDataLength(
        W2U_PTC_ARC_ID,
        static_cast<u16>(spaMember));
    if (!resourceBytes ||
        resourceBytes >
            0xFFFFFFFFu - W2U_PARTICLE_LIBRARY_HEAP_SIZE -
                W2U_PARTICLE_ALLOCATION_HEADROOM) {
        return false;
    }
    const u32 requiredBytes =
        W2U_PARTICLE_LIBRARY_HEAP_SIZE + resourceBytes +
        W2U_PARTICLE_ALLOCATION_HEADROOM;
    if (GFL_HeapGetHighestAllocatableSize(heapID) < requiredBytes) {
        return false;
    }

    void* particleHeap =
        GFL_HeapAllocateCore(heapID, W2U_PARTICLE_LIBRARY_HEAP_SIZE);
    if (!particleHeap) {
        return false;
    }
    void* resource = GFL_PTC_LoadArcResource(
        W2U_PTC_ARC_ID,
        spaMember,
        heapID);
    if (!resource) {
        GFL_HeapFreeCore(particleHeap);
        return false;
    }

    void* particleSystem = GFL_PTC_CreateEx(
        particleHeap,
        W2U_PARTICLE_LIBRARY_HEAP_SIZE,
        false,
        W2U_PARTICLE_POLYGON_ID_FIXED,
        W2U_PARTICLE_POLYGON_ID_MINIMUM,
        W2U_PARTICLE_POLYGON_ID_MAXIMUM,
        heapID);
    if (!particleSystem) {
        GFL_FREE(resource);
        GFL_HeapFreeCore(particleHeap);
        return false;
    }

    GFL_PTC_SetResourceSetup(particleSystem, resource);
    sTerrainAmbientParticleHeap = particleHeap;
    sTerrainAmbientParticleSystem = particleSystem;
    sTerrainAmbientParticleTerrain = terrain;
    sTerrainAmbientTexturePending = true;
    sTerrainAmbientTextureReady = false;
    return true;
}

void FinishTerrainAmbientParticleSetup()
{
    if (!sTerrainAmbientTexturePending ||
        !sTerrainAmbientParticleSystem ||
        sAppliedTerrain != sTerrainAmbientParticleTerrain) {
        return;
    }

    // This function runs from the existing post-viewer VBlank hook. Match the
    // native move VM's split resource setup so texture VRAM is never updated
    // from the main battle loop.
    GFL_PTC_LoadTex(sTerrainAmbientParticleSystem);
    sTerrainAmbientTexturePending = false;
    sTerrainAmbientTextureReady = true;
}

void EmitElectricAmbientSpark(u32 anchorIndex)
{
    if (!sTerrainAmbientParticleSystem ||
        anchorIndex >= W2U_ELECTRIC_AMBIENT_ANCHOR_COUNT) {
        return;
    }

    void* mcssWork = BTLV_EFFECT_GetMcssWork();
    if (!mcssWork) {
        return;
    }

    VecFx32 position = { 0, 0, 0 };
    BTLV_MCSS_GetPokeDefaultPos(
        mcssWork,
        &position,
        static_cast<int>(anchorIndex));
    position.z += static_cast<fx32>(W2U_PARTICLE_Z_PRIORITY_OFFSET);
    void* emitter = GFL_PTC_CreateEmitter(
        sTerrainAmbientParticleSystem,
        0,
        &position);
    if (!emitter || emitter == reinterpret_cast<void*>(0xFFFFFFFFu)) {
        return;
    }

    const s32 radiusQuarters = W2U_ELECTRIC_AMBIENT_RADIUS_QUARTERS[anchorIndex];
    const fx32 radius = GFL_PTC_GetEmitterRadius(emitter);
    const fx32 length = GFL_PTC_GetEmitterLength(emitter);
    GFL_PTC_SetEmitterRadius(
        emitter,
        static_cast<fx32>((static_cast<s64>(radius) * radiusQuarters) / 4));
    GFL_PTC_SetEmitterLength(
        emitter,
        static_cast<fx32>((static_cast<s64>(length) * radiusQuarters) / 4));
}

// One floor-wide emitter (a disk lying on the floor, see the SPA) at the step's anchor: the player's side, the
// middle of the field, the foe's side (the singles default positions; doubles share the same field).
bool FieldAmbientAnchor(u32 step, VecFx32* position)
{
    void* mcssWork = BTLV_EFFECT_GetMcssWork();
    if (!mcssWork) {
        return false;
    }
    VecFx32 player = { 0, 0, 0 };
    VecFx32 foe = { 0, 0, 0 };
    BTLV_MCSS_GetPokeDefaultPos(mcssWork, &player, 0);
    BTLV_MCSS_GetPokeDefaultPos(mcssWork, &foe, 1);
    const u32 anchor = step % W2U_FIELD_AMBIENT_ANCHOR_COUNT;
    if (anchor == 0u) {
        *position = player;
    } else if (anchor == 2u) {
        *position = foe;
    } else {
        position->x = (player.x + foe.x) >> 1;
        position->y = (player.y + foe.y) >> 1;
        position->z = (player.z + foe.z) >> 1;
    }
    return true;
}

void EmitFieldAmbient(u32 step, fx32 xOffset)
{
    VecFx32 position;
    if (!sTerrainAmbientParticleSystem || !FieldAmbientAnchor(step, &position)) {
        return;
    }
    position.x += xOffset;
    GFL_PTC_CreateEmitter(sTerrainAmbientParticleSystem, 0, &position);
}

void EmitPsychicAmbientEnergy(u32 anchor)
{
    if (!sTerrainAmbientParticleSystem ||
        anchor >= W2U_BATTLER_AMBIENT_ANCHOR_COUNT) {
        return;
    }

    void* mcssWork = BTLV_EFFECT_GetMcssWork();
    if (!mcssWork) {
        return;
    }

    // Alternate one slowed energy particle between the user and target. SPA
    // 790 retains Shock Wave resource 2's purple parent/child appearance.
    VecFx32 position = { 0, 0, 0 };
    BTLV_MCSS_GetPokeDefaultPos(mcssWork, &position, static_cast<int>(anchor));
    position.y += static_cast<fx32>(W2U_PSYCHIC_AMBIENT_Y_OFFSET);
    position.z += static_cast<fx32>(W2U_PARTICLE_Z_PRIORITY_OFFSET);
    GFL_PTC_CreateEmitter(sTerrainAmbientParticleSystem, 0, &position);
}

u32 TerrainAmbientStepInterval(u32 terrain)
{
    if (terrain == TERRAIN_PSYCHIC) {
        const u32 gaps = sizeof(W2U_PSYCHIC_AMBIENT_GAPS) / sizeof(W2U_PSYCHIC_AMBIENT_GAPS[0]);
        sPsychicGapIndex = (sPsychicGapIndex + 1u) % gaps;
        return W2U_PSYCHIC_AMBIENT_GAPS[sPsychicGapIndex];
    }
    const s32 index = terrain >= TERRAIN_ELECTRIC && terrain <= TERRAIN_PSYCHIC
        ? static_cast<s32>(terrain - TERRAIN_ELECTRIC) : -1;
    return index >= 0 ? W2U_TERRAIN_PACE[index].ambientInterval : 60u;
}

void AdvanceTerrainAmbient()
{
    if (!sFieldWork) {
        ResetTerrainAmbientTimer();
        return;
    }

    const bool appliedTerrainHasAmbient =
        AmbientSpaMemberForTerrain(sAppliedTerrain) != 0u;
    if (!appliedTerrainHasAmbient) {
        // Preserve a system prepared just before its terrain's next VBlank
        // upload. Once terrain expires, release the
        // private heap from this normal (non-VBlank) update path, after the
        // particles already in flight have finished (no cut-off).
        if (sTerrainAmbientParticleSystem &&
            !AmbientSpaMemberForTerrain(sRequestedTerrain)) {
#if defined(W2U_TERRAIN_FLOOR_FADES)
            if (sTerrainAmbientTextureReady &&
                GFL_PTC_GetEmitterNum(sTerrainAmbientParticleSystem) > 0 &&
                ++sTerrainAmbientDrainFrames < W2U_AMBIENT_DRAIN_MAX_FRAMES) {
                return;
            }
#endif
            ReleaseTerrainAmbientParticles();
        } else {
            ResetTerrainAmbientTimer();
        }
        return;
    }

    if (sTerrainAmbientStopping) {
        return;                                  // fading out: let the live particles finish
    }

    if (sTerrainAmbientParticleTerrain != sAppliedTerrain ||
        !sTerrainAmbientTextureReady ||
        !sTerrainAmbientParticleSystem) {
        ResetTerrainAmbientTimer();
        return;
    }

    if (sTerrainAmbientFrame != 0u) {
        sTerrainAmbientFrame -= 1u;
        return;
    }

    // Emit one deliberately paced step without waiting for all existing
    // particles to die. Each interval is matched to the slowed resource's
    // visible lifetime, eliminating the old completed-batch dead time.
    if (sAppliedTerrain == TERRAIN_ELECTRIC) {
        EmitElectricAmbientSpark(sTerrainAmbientStep);
        sTerrainAmbientStep = (sTerrainAmbientStep + 1u) %
            W2U_ELECTRIC_AMBIENT_ANCHOR_COUNT;
    } else if (sAppliedTerrain == TERRAIN_GRASSY) {
        EmitFieldAmbient(sTerrainAmbientStep, 0);
        sTerrainAmbientStep = (sTerrainAmbientStep + 1u) % W2U_FIELD_AMBIENT_ANCHOR_COUNT;
    } else if (sAppliedTerrain == TERRAIN_MISTY) {
        EmitFieldAmbient(sTerrainAmbientStep, W2U_MISTY_FOG_X_OFFSET);
        sTerrainAmbientStep = (sTerrainAmbientStep + 1u) % W2U_FIELD_AMBIENT_ANCHOR_COUNT;
    } else {
        EmitPsychicAmbientEnergy(sTerrainAmbientStep);
        sTerrainAmbientStep = (sTerrainAmbientStep + 1u) %
            W2U_BATTLER_AMBIENT_ANCHOR_COUNT;
    }
    const u32 interval = TerrainAmbientStepInterval(sAppliedTerrain);
    sTerrainAmbientFrame = interval > 0u ? interval - 1u : 0u;
}

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
        sCurrentMapping->terrainTextureBaseMember + terrainIndex);
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
#if !defined(W2U_TARGET_B2)
    sFloorTrackWords = 0;
    sFloorScrollHorizontal = false;
#endif
}

#if !defined(W2U_TARGET_B2)
// Grassy / Misty drift their floor sideways with their sky (UpdateSkyRepeat): both translate tracks of the loaded
// floor animation are made constant and translate S's value is written every frame (the animation reads the resource
// every frame); the others keep the template's vertical scroll. Template member 119: {info, value} words of
// translate S at 0x78, translate T at 0x80 (tracks: scale S 0x60, scale T 0x68, rotation 0x70, translate S, T).
constexpr u32 W2U_SRT_TRANS_S_WORD = 0x78u / 4u, W2U_SRT_TRANS_T_WORD = 0x80u / 4u;
constexpr u32 W2U_SRT_CONST_TRACK = 0x30000000u;

void RememberFloorTracks()
{
    NNSG3DResData* data = sFloorAnimationResource ? GFL_G3DResGetResData(sFloorAnimationResource) : 0;
    sFloorTrackWords = 0;
    sFloorScrollHorizontal = false;
    if (!data || data->Header.FileSize < (W2U_SRT_TRANS_T_WORD + 2u) * 4u) {
        return;
    }
    u32* words = reinterpret_cast<u32*>(data);
    if ((words[W2U_SRT_TRANS_S_WORD] & 0xF0000000u) != W2U_SRT_CONST_TRACK ||
        (words[W2U_SRT_TRANS_S_WORD] & 0xFFFFu) != (words[W2U_SRT_TRANS_T_WORD] & 0xFFFFu)) {
        return;
    }
    for (u32 k = 0; k < 4u; ++k) {
        sFloorTrackOriginal[k] = words[W2U_SRT_TRANS_S_WORD + k];
    }
    sFloorTrackWords = words;
}

void SetFloorScrollHorizontal(bool horizontal)
{
    sFloorScrollHorizontal = horizontal;
    if (!sFloorTrackWords) {
        return;
    }
    u32* track = sFloorTrackWords + W2U_SRT_TRANS_S_WORD;
    if (horizontal) {
        track[0] = sFloorTrackOriginal[0];       // translate S: constant, value written by the drift
        track[1] = 0u;
        track[2] = W2U_SRT_CONST_TRACK | (sFloorTrackOriginal[2] & 0x0FFFFFFFu);
        track[3] = 0u;
    } else {
        for (u32 k = 0; k < 4u; ++k) {
            track[k] = sFloorTrackOriginal[k];
        }
    }
    cp15_flushDC(track, 16u);
}

void SetFloorScrollOffset(u32 offset)          // translate S, fx32 texture widths (wrapped)
{
    if (sFloorTrackWords && sFloorScrollHorizontal) {
        sFloorTrackWords[W2U_SRT_TRANS_S_WORD + 1u] = offset;
    }
}
#endif

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

#if !defined(W2U_TARGET_B2)
    RememberFloorTracks();
#endif
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

#if defined(W2U_TERRAIN_FLOOR_FADES)
void ReleaseFloorFade();
#endif

void ClearFieldViewState()
{
    SetFieldPaletteFadeResource(sFieldResource);
#if defined(W2U_TERRAIN_FLOOR_FADES)
    ReleaseFloorFade();
#endif
    ReleaseTerrainAmbientParticles();
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
    ResetTerrainAmbientTimer();
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

#if defined(W2U_TERRAIN_FLOOR_FADES)
// ---- Floor fades ---------------------------------------------------------------------------------------------
// A terrain clone changes only the primary floor's image and the palette bound to it (build_terrain_texture_mvp.py),
// and the image indices differ, so the two floors cannot be cross-faded through one palette. Instead the floor's
// own palette range fades to the incoming floor's average colour, the image is swapped while every floor colour
// is that one colour, and the incoming palette fades in from it. Only the floor's palette range is uploaded (the
// rest of the background is untouched). Starting a terrain, this waits until the terrain move's animation has
// finished: those animations fade the whole field palette themselves (Misty, Electric) and the two would fight.
// Electric keeps its masked swap under its animation's black field fade (its fade-in) and fades out like the rest.
enum FloorFadePhase {
    FLOOR_FADE_IDLE = 0,
    FLOOR_FADE_OUT,
    FLOOR_FADE_IN,
};
constexpr u32 W2U_ADDR_BTLV_EFFECT_CHECK_EXECUTE = 0x021DF829u;   // ov168: nonzero while an effect script runs
constexpr u32 W2U_EFFECT_START_TIMEOUT_FRAMES = 20u;              // no animation started: fade at once
constexpr u32 W2U_FLOOR_UPLOAD_LAST_LINE = 0xD0u;                 // palette uploads end well before the 3D render

u32 sFloorFadePhase = FLOOR_FADE_IDLE;
u32 sFloorFadeFrame = 0u;
u32 sFloorFadeOutFrames = 0u;
u32 sFloorFadeInFrames = 0u;
u32 sFloorFadeSerial = 0u;
u32 sFloorFadeTerrain = TERRAIN_NULL;      // the terrain fading in (TERRAIN_NULL: the native floor)
u32 sFloorFadeWobble = 0u;                 // Psychic: the fade wobbles
u16 sFloorFadeColor = 0u;
G3DResource* sFloorFadeResource = 0;       // the incoming terrain clone (owned during the fade)
NNSG3DResTex* sFloorFadeTex = 0;
G3DResource* sFloorFadeFrom = 0;           // the palette faded out
u32 sFloorPaletteFirst = 0u;
u32 sFloorPaletteCount = 0u;               // 0: not known yet
// The backdrop: Grassy / Misty clones replace it too (its own blend colour in a fade, no haze on it). Owned: the
// palette shown there comes from the terrain clone rather than the native one.
u32 sSkyFirst = 0u;
u32 sSkyCount = 0u;
u16 sSkyFadeColor = 0u;
bool sSkyOwned = false;

bool InSkyRange(u32 index)
{
    return index >= sSkyFirst && index < sSkyFirst + sSkyCount;
}
bool sEffectSeenBusy = false;
u32 sEffectWaitFrames = 0u;

bool EffectBusy()
{
    typedef b32 (*CheckExecuteFn)();
    return ((CheckExecuteFn)W2U_ADDR_BTLV_EFFECT_CHECK_EXECUTE)() != 0;
}

void ResetEffectWatch()
{
    sEffectSeenBusy = false;
    sEffectWaitFrames = 0u;
}

// The terrain move's animation has run and ended (or none started within the timeout).
bool TerrainAnimationFinished()
{
    const bool busy = EffectBusy();
    if (!sEffectSeenBusy) {
        if (busy) {
            sEffectSeenBusy = true;
            return false;
        }
        return ++sEffectWaitFrames > W2U_EFFECT_START_TIMEOUT_FRAMES;
    }
    return !busy;
}

const TerrainPace* PaceFor(u32 terrain)
{
    const s32 index = TerrainTextureIndex(terrain);
    return index >= 0 ? &W2U_TERRAIN_PACE[index] : 0;
}

// The floor's palette range: the entries the terrain clones change (one contiguous run on every field), widened to
// whole words for the palette transfer.
bool FindFloorPaletteRange(G3DResource* terrainResource)
{
    if (sFloorPaletteCount) {
        return true;
    }
    const u16* native = sFieldResource
        ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(sFieldResource)) : 0;
    const u16* terrain = terrainResource
        ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(terrainResource)) : 0;
    if (!native || !terrain || !sFieldTex) {
        return false;
    }
    const u32 colorCount = (static_cast<u32>(sFieldTex->PaletteHeader.ImageSize) << 3) / sizeof(u16);
    if (colorCount > W2U_PALETTE_BACKUP_COLORS) {
        return false;
    }
    u32 first = colorCount, last = 0u;
    for (u32 index = 0; index < colorCount; ++index) {
        if (native[index] != terrain[index] && !InSkyRange(index)) {
            if (first == colorCount) {
                first = index;
            }
            last = index;
        }
    }
    if (first == colorCount) {
        return false;
    }
    first &= ~1u;
    last |= 1u;
    if (last >= colorCount) {
        last = colorCount - 1u;
    }
    sFloorPaletteFirst = first;
    sFloorPaletteCount = last - first + 1u;
    return true;
}

u16 AverageRangeColor(G3DResource* resource, u32 first, u32 count)
{
    const u16* palette = resource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(resource)) : 0;
    if (!palette || !count) {
        return 0u;
    }
    u32 red = 0u, green = 0u, blue = 0u;
    for (u32 index = 0; index < count; ++index) {
        const u16 color = palette[first + index];
        red += color & 0x1Fu;
        green += (color >> 5) & 0x1Fu;
        blue += (color >> 10) & 0x1Fu;
    }
    const u64 n = count;                         // u64: no __aeabi_uidiv
    return static_cast<u16>(static_cast<u32>(red / n) | (static_cast<u32>(green / n) << 5) |
                            (static_cast<u32>(blue / n) << 10));
}

// The resource's backdrop differs from the native one (a Grassy / Misty clone).
bool SkyDiffers(G3DResource* resource)
{
    const u16* palette = resource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(resource)) : 0;
    const u16* native = sFieldResource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(sFieldResource)) : 0;
    if (!palette || !native || !sSkyCount || resource == sFieldResource) {
        return false;
    }
    for (u32 index = sSkyFirst; index < sSkyFirst + sSkyCount; ++index) {
        if (palette[index] != native[index]) {
            return true;
        }
    }
    return false;
}

u16 AverageFloorColor(G3DResource* resource)
{
    const u16* palette = resource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(resource)) : 0;
    if (!palette || !sFloorPaletteCount) {
        return 0u;
    }
    u32 red = 0u, green = 0u, blue = 0u;
    for (u32 index = 0; index < sFloorPaletteCount; ++index) {
        const u16 color = palette[sFloorPaletteFirst + index];
        red += color & 0x1Fu;
        green += (color >> 5) & 0x1Fu;
        blue += (color >> 10) & 0x1Fu;
    }
    // u64 division: PMC links no __aeabi_uidiv (a u32 / u32 by a variable would call an unresolved helper)
    const u64 n = sFloorPaletteCount;
    return static_cast<u16>(static_cast<u32>(red / n) | (static_cast<u32>(green / n) << 5) |
                            (static_cast<u32>(blue / n) << 10));
}

// Floor palette animation while a terrain is shown (Grassy: the grass glows softly brighter and back; Misty: random
// floor colours twinkle towards white, dew catching the light). Only between animations: a running effect script
// owns the field palette (its fades), so the animation pauses and leaves the plain floor.
struct FloorTwinkle {
    u16 index;                                 // in the floor range
    u8 age;
    u8 active;
};
constexpr u32 W2U_FLOOR_TWINKLES = 8u;
constexpr u16 W2U_TWINKLE_COLOR = 0x7FDF;      // (31, 30, 31): white with a breath of pink
constexpr u16 W2U_GRASSY_GLOW_COLOR = 0x4BFA;  // (26, 31, 18): sunlit yellow-green
constexpr u32 W2U_GRASSY_GLOW_MAX_EVY = 3u;
constexpr u32 W2U_GRASSY_GLOW_PERIOD_STEP = 65536u / 200u;   // one swell every 200 frames
// A twinkle's brightness per frame of its life (evy towards W2U_TWINKLE_COLOR): quick rise, slow fall. A table:
// -Os turns even a constant divisor into a helper call PMC cannot link.
const u8 W2U_TWINKLE_LEVELS[] = { 2, 4, 7, 9, 11, 11, 10, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 2, 2, 1, 1 };
FloorTwinkle sTwinkles[W2U_FLOOR_TWINKLES];
u32 sFloorAnimFrame = 0u;
u32 sFloorAnimSpawn = 0u;
u32 sFloorAnimEvy = 0xFFu;
u32 sFloorAnimRandom = 0x2545F491u;
bool sFloorAnimDirty = false;

u32 FloorAnimRandom(u32 range)                 // 0 .. range - 1 (no division)
{
    sFloorAnimRandom = sFloorAnimRandom * 1103515245u + 12345u;
    return static_cast<u32>((static_cast<u64>(sFloorAnimRandom >> 16) * range) >> 16);
}

// Scene haze (Sun / Moon): while Grassy or Misty Terrain is up, the rest of the battle background (every field palette
// entry outside the floor range) is washed towards the terrain's colour. It fades with the floor; once a terrain is
// in, it is also written into the terrain clone's palette in RAM (BakeHaze), the source every field palette fade of
// a move animation starts from, so animations start and end on the hazed scene.
struct TerrainHaze {
    u16 color;
    u8 evy;
};
TerrainHaze HazeFor(u32 terrain)
{
    if (terrain == TERRAIN_GRASSY) {
        return { 0x47D6u, 7u };                  // (22, 30, 17): light, fresh green
    }
    if (terrain == TERRAIN_MISTY) {
        return { 0x773Fu, 7u };                  // (31, 25, 29): soft pink
    }
    return { 0u, 0u };
}
u16 sHazeColor = 0u;
u32 sHazeEvy = 0u;                             // the haze on screen now
TerrainHaze sHazeFrom = { 0u, 0u };
TerrainHaze sHazeTo = { 0u, 0u };

u32 FieldPaletteColorCount()
{
    return sFieldTex ? (static_cast<u32>(sFieldTex->PaletteHeader.ImageSize) << 3) / sizeof(u16) : 0u;
}

bool InFloorRange(u32 index)
{
    return index >= sFloorPaletteFirst && index < sFloorPaletteFirst + sFloorPaletteCount;
}

// The whole field palette straight to palette VRAM: the floor range from `resource`, faded to `color` by evy / 16
// (and the live twinkles brightened); every other entry the native colour under the current haze.
bool UploadFloorPaletteTo(G3DResource* resource, u32 evy, u16 color, bool twinkles)
{
    const u16* palette = resource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(resource)) : 0;
    const u16* native = sFieldResource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(sFieldResource)) : 0;
    const u32 colorCount = FieldPaletteColorCount();
    if (!palette || !native || !sFloorPaletteCount || !colorCount || colorCount > W2U_PALETTE_BACKUP_COLORS) {
        return false;
    }
    if (evy > W2U_PALETTE_FADE_MAX_EVY) {
        evy = W2U_PALETTE_FADE_MAX_EVY;
    }
    for (u32 index = 0; index < colorCount; ++index) {
        if (InFloorRange(index)) {
            sPaletteBackup[index] = evy ? FadeColor(palette[index], color, evy) : palette[index];
        } else if (sSkyOwned && InSkyRange(index)) {
            sPaletteBackup[index] = evy ? FadeColor(palette[index], sSkyFadeColor, evy) : palette[index];
        } else {
            sPaletteBackup[index] = sHazeEvy ? FadeColor(native[index], sHazeColor, sHazeEvy) : native[index];
        }
    }
    for (u32 t = 0; twinkles && t < W2U_FLOOR_TWINKLES; ++t) {
        const FloorTwinkle& twinkle = sTwinkles[t];
        if (!twinkle.active || twinkle.index >= sFloorPaletteCount || twinkle.age >= sizeof(W2U_TWINKLE_LEVELS)) {
            continue;
        }
        const u32 index = sFloorPaletteFirst + twinkle.index;
        sPaletteBackup[index] = FadeColor(palette[index], W2U_TWINKLE_COLOR, W2U_TWINKLE_LEVELS[twinkle.age]);
    }
    const u32 bytes = colorCount * sizeof(u16);
    cp15_flushDC(sPaletteBackup, bytes);
    const u32 base = (sFieldTex->PaletteHeader.RTVRAMAddr & 0xFFFFu) << 3;   // NNS palette key -> address
    gfxBeginPaletteUpload();
    gfxUploadPalette(sPaletteBackup, base, bytes);
    gfxEndPaletteUpload();
    return true;
}

// Glow (Sun / Moon): the battle lights the field model (light 0; diffuse 25/31, ambient 31/31, no emission), and in
// the evening / at night that light is dim and blue, so no floor texture can look luminous. Grassy and Misty Terrain
// give the floor material an emission in their colour (the hardware adds it to the lit vertex colour and clamps:
// under full daylight it changes little, at night it lifts the floor to the texture's own colours) and the field's
// other materials a share of it (the scene brightens with the haze). Written into the field model's material data
// in RAM, which the renderer reads every frame; restored when the terrain fades out and at field exit.
struct FieldMaterial {
    u32* specEmi;                              // NNSG3dResMatData +8: specular (0-14), emission (16-30)
    u32 original;
    bool floor;
};
constexpr u32 W2U_FIELD_MATERIALS_MAX = 8u;
constexpr u32 W2U_SCENE_GLOW_SHARE = 10u;      // the other materials get 10/16 of the floor's glow
FieldMaterial sFieldMaterials[W2U_FIELD_MATERIALS_MAX];
u32 sFieldMaterialCount = 0u;
char sSkyMaterialName[W2U_NITRO_NAME_LENGTH] = {};   // the backdrop material (*sky*), empty: none
bool sFieldMaterialsSearched = false;
u16 sGlowColor = 0u;
u32 sGlowLevel = 0u;                           // 0..16 of the glow on screen now
TerrainHaze sGlowFrom = { 0u, 0u };
TerrainHaze sGlowTo = { 0u, 0u };

TerrainHaze GlowFor(u32 terrain)               // (emission colour, unused)
{
    if (terrain == TERRAIN_GRASSY) {
        return { 0x19AAu, 16u };               // (10, 13, 6): soft mint-green
    }
    if (terrain == TERRAIN_MISTY) {
        return { 0x2D0Cu, 16u };               // (12, 8, 11): pink
    }
    return { 0u, 0u };
}

u16 ReadU16(const u8* p) { return static_cast<u16>(p[0] | (p[1] << 8)); }
u32 ReadU32(const u8* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | (static_cast<u32>(p[3]) << 24); }

// The field NSBMD's first model's materials (MDL0 -> model dictionary -> NNSG3dResMat dictionary), the floor by name.
void FindFieldMaterials()
{
    sFieldMaterialsSearched = true;
    sFieldMaterialCount = 0u;
    NNSG3DResData* data = sFieldResource ? GFL_G3DResGetResData(sFieldResource) : 0;
    if (!data || !sFloorAnimationMaterial) {
        return;
    }
    const u8* file = reinterpret_cast<const u8*>(data);
    const u32 fileSize = data->Header.FileSize;
    const u32 blockCount = ReadU16(file + 0x0E);
    const u8* mdl0 = 0;
    for (u32 block = 0; block < blockCount && 0x10u + block * 4u + 4u <= fileSize; ++block) {
        const u32 offset = ReadU32(file + 0x10 + block * 4u);
        if (offset + 8u <= fileSize && ReadU32(file + offset) == 0x304C444Du) {   // 'MDL0'
            mdl0 = file + offset;
            break;
        }
    }
    if (!mdl0) {
        return;
    }
    // NNSG3dResDict: +1 entry count, +6 entry table; table: +0 data unit size, +2 names offset, +4 data
    const u8* modelDict = mdl0 + 8;
    const u8* modelTable = modelDict + ReadU16(modelDict + 6);
    if (!modelDict[1]) {
        return;
    }
    const u8* model = mdl0 + ReadU32(modelTable + 4);
    const u8* materials = model + ReadU32(model + 8);                // NNSG3dResMdl +8: ofsMat
    const u8* matDict = materials + 4;                                // NNSG3dResMat: dictionary at +4
    const u32 count = matDict[1];
    const u8* matTable = matDict + ReadU16(matDict + 6);
    const u32 unit = ReadU16(matTable);
    const u8* names = matTable + ReadU16(matTable + 2);
    for (u32 index = 0; index < count && sFieldMaterialCount < W2U_FIELD_MATERIALS_MAX; ++index) {
        u8* matData = const_cast<u8*>(materials + ReadU32(matTable + 4 + index * unit));
        if (reinterpret_cast<u32>(matData) & 3u || matData < file || matData + 12 > file + fileSize) {
            continue;
        }
        bool floor = true;
        for (u32 c = 0; c < W2U_NITRO_NAME_LENGTH; ++c) {
            const char want = c + 1u < W2U_NITRO_NAME_LENGTH ? sFloorAnimationMaterial[c] : 0;
            if (names[index * W2U_NITRO_NAME_LENGTH + c] != static_cast<u8>(want)) {
                floor = false;
                break;
            }
            if (!want) {
                break;
            }
        }
        const u8* name = names + index * W2U_NITRO_NAME_LENGTH;
        for (u32 c = 0; !sSkyMaterialName[0] && c + 3u <= W2U_NITRO_NAME_LENGTH - 1u && name[c]; ++c) {
            if (name[c] == 's' && name[c + 1] == 'k' && name[c + 2] == 'y') {
                for (u32 k = 0; k + 1u < W2U_NITRO_NAME_LENGTH; ++k) {
                    sSkyMaterialName[k] = static_cast<char>(name[k]);
                }
                break;
            }
        }
        FieldMaterial& material = sFieldMaterials[sFieldMaterialCount++];
        material.specEmi = reinterpret_cast<u32*>(matData + 8);
        material.original = *material.specEmi;
        material.floor = floor;
    }
}

// Emission `color` at level / 16 on the floor (the share elsewhere); 0 restores the model's own values.
void SetFieldGlow(u16 color, u32 level)
{
    if (!sFieldMaterialsSearched) {
        FindFieldMaterials();
    }
    sGlowColor = color;
    sGlowLevel = level;
    for (u32 index = 0; index < sFieldMaterialCount; ++index) {
        FieldMaterial& material = sFieldMaterials[index];
        const u32 share = material.floor ? 16u : W2U_SCENE_GLOW_SHARE;
        const u32 scale = level * share;                              // /256
        const u32 own = material.original >> 16;
        u32 emission = 0u;
        for (u32 shift = 0; shift < 15u; shift += 5u) {
            const u32 add = (((color >> shift) & 31u) * scale) >> 8;
            const u32 sum = ((own >> shift) & 31u) + add;
            emission |= (sum > 31u ? 31u : sum) << shift;
        }
        *material.specEmi = (material.original & 0x8000FFFFu) | (emission << 16);
    }
}

void RestoreFieldGlow()
{
    for (u32 index = 0; index < sFieldMaterialCount; ++index) {
        *sFieldMaterials[index].specEmi = sFieldMaterials[index].original;
    }
    sFieldMaterialCount = 0u;
    sFieldMaterialsSearched = false;
    sSkyMaterialName[0] = 0;
    sGlowLevel = 0u;
}

// Sky and floor drift (Grassy / Misty): texture translation per 60 fps frame in 1/65536 texture widths (wrapped at
// one width). Measured on screen just above / below the horizon, a floor drift 8x the sky's moves the two together
// (both the same way); 4 / 32 is about 3 screen pixels a second: very slow and subtle.
constexpr u32 W2U_SKY_DRIFT = 4u;
constexpr u32 W2U_FLOOR_DRIFT = 32u;
u32 sDriftSky = 0u;                            // 16.16 texture widths
u32 sDriftFloor = 0u;

// Sky repeat: the backdrop stretches its 128x64 texture about 4.5x wider than tall on screen, and textures are not
// filtered, so a Grassy / Misty sky looked blocky. While such a sky is shown, a copy of the floor's SRT animation
// template (one constant track) is bound to the sky material with scale S 4: the texture repeats four times across
// the backdrop and a texel is about 1.6 x 1.4 screen pixels. Loaded and bound from the main battle update
// (UpdateSkyRepeat); the fade only asks for it at its midpoint, while the sky is one flat colour.
constexpr fx32 W2U_SKY_REPEAT_S = FX32_ONE * 4;
// template member 119 (SRT0, one material): the track words of scale S and translate T (each {info, value}; tracks
// scale S 0x60, scale T 0x68, rotation 0x70, translate S 0x78, translate T 0x80)
constexpr u32 W2U_SRT_SCALE_S_INFO = 0x60u, W2U_SRT_TRANS_S_INFO = 0x78u, W2U_SRT_TRANS_T_INFO = 0x80u;
constexpr u32 W2U_SRT_CONST = 0x30000000u;     // constant track (value in the data word)
G3DResource* sSkyRepeatResource = 0;
u32* sSkyTransS = 0;
G3DAnim* sSkyRepeatAnimation = 0;
bool sSkyRepeatBound = false;
volatile bool sSkyRepeatWanted = false;

void ReleaseSkyRepeat()
{
    if (sFieldModel && sSkyRepeatAnimation && sSkyRepeatBound) {
        G3DAnim* animations[] = { sSkyRepeatAnimation };
        G3DActor proxy = { sFieldModel, animations, 1u, 0u };
        GFL_G3DActorUnbindAnm(&proxy, 0u);
    }
    sSkyRepeatBound = false;
    if (sSkyRepeatAnimation) {
        GFL_G3DAnmFree(sSkyRepeatAnimation);
    }
    if (sSkyRepeatResource) {
        GFL_G3DResFree(sSkyRepeatResource);
    }
    sSkyRepeatAnimation = 0;
    sSkyRepeatResource = 0;
    sSkyTransS = 0;
}

// The template retargeted to the sky material, scale S constant 4, translate T constant 0 (no scroll).
bool PatchSkyRepeat(G3DResource* resource)
{
    NNSG3DResData* data = resource ? GFL_G3DResGetResData(resource) : 0;
    if (!data || data->Header.FileSize < W2U_SRT_TRANS_T_INFO + 8u ||
        !RetargetFloorAnimationResource(resource, sSkyMaterialName)) {
        return false;
    }
    u32* words = reinterpret_cast<u32*>(data);
    u32* scaleS = words + W2U_SRT_SCALE_S_INFO / 4u;
    u32* transS = words + W2U_SRT_TRANS_S_INFO / 4u;
    u32* transT = words + W2U_SRT_TRANS_T_INFO / 4u;
    if ((scaleS[0] & 0xF0000000u) != W2U_SRT_CONST || scaleS[1] != static_cast<u32>(FX32_ONE) ||
        (transS[0] & 0xF0000000u) != W2U_SRT_CONST || (scaleS[0] & 0xFFFFu) != (transT[0] & 0xFFFFu)) {
        return false;                            // not the expected template
    }
    scaleS[1] = static_cast<u32>(W2U_SKY_REPEAT_S);
    transT[0] = W2U_SRT_CONST | (transT[0] & 0x0FFFFFFFu);
    transT[1] = 0u;
    transS[1] = 0u;
    sSkyTransS = transS + 1;                     // translate S's value word (a constant track): the drift
    cp15_flushDC(data, data->Header.FileSize);
    return true;
}

void UpdateSkyRepeat()
{
    const bool wanted = sSkyRepeatWanted;
    if (wanted == sSkyRepeatBound) {
        return;
    }
    if (!wanted) {
        ReleaseSkyRepeat();
        return;
    }
    if (!sFieldModel || sFloorAnimationMember == W2U_NO_FLOOR_ANIMATION_MEMBER) {
        return;
    }
    if (!sFieldMaterialsSearched) {
        FindFieldMaterials();
    }
    if (!sSkyMaterialName[0]) {
        sSkyRepeatWanted = false;
        return;
    }
    sSkyRepeatResource = GFL_G3DSysReadArcSysResource(W2U_BATTGRA_ARC_ID, sFloorAnimationMember);
    if (!PatchSkyRepeat(sSkyRepeatResource)) {
        ReleaseSkyRepeat();
        sSkyRepeatWanted = false;
        return;
    }
    sSkyRepeatAnimation = GFL_G3DAnmCreate(sFieldModel, sSkyRepeatResource, 0u);
    if (!sSkyRepeatAnimation) {
        ReleaseSkyRepeat();
        sSkyRepeatWanted = false;
        return;
    }
    G3DAnim* animations[] = { sSkyRepeatAnimation };
    G3DActor proxy = { sFieldModel, animations, 1u, 0u };
    sSkyRepeatBound = GFL_G3DActorBindAnm(&proxy, 0u);
    if (!sSkyRepeatBound) {
        ReleaseSkyRepeat();
        sSkyRepeatWanted = false;
        return;
    }
    fx32 frame = 0;
    GFL_G3DActorSetAnmFrame(&proxy, 0u, &frame);
}

// The terrain clone's own palette (RAM) takes the haze outside the floor range.
void BakeHaze()
{
    u16* palette = sActiveTerrainResource
        ? static_cast<u16*>(GFL_G3DResGetTexPaletteData(sActiveTerrainResource)) : 0;
    const u16* native = sFieldResource ? static_cast<const u16*>(GFL_G3DResGetTexPaletteData(sFieldResource)) : 0;
    const u32 colorCount = FieldPaletteColorCount();
    if (!palette || !native || !sHazeEvy || !sFloorPaletteCount) {
        return;
    }
    for (u32 index = 0; index < colorCount; ++index) {
        if (!InFloorRange(index) && !(sSkyOwned && InSkyRange(index))) {
            palette[index] = FadeColor(native[index], sHazeColor, sHazeEvy);
        }
    }
    cp15_flushDC(palette, colorCount * sizeof(u16));
}

bool UploadFloorPalette(G3DResource* resource, u32 evy)
{
    return UploadFloorPaletteTo(resource, evy, sFloorFadeColor, false);
}

void ResetFloorPaletteAnimation()
{
    for (u32 t = 0; t < W2U_FLOOR_TWINKLES; ++t) {
        sTwinkles[t].active = 0u;
    }
    sFloorAnimEvy = 0xFFu;
    sFloorAnimSpawn = 0u;
}

// Image and palette of `resource`, with the floor range already at evy / 16 towards the blend colour.
bool UploadTextureFloorFaded(G3DResource* resource, u32 evy)
{
    u16* palette = resource ? static_cast<u16*>(GFL_G3DResGetTexPaletteData(resource)) : 0;
    if (!palette || !sFloorPaletteCount) {
        return UploadTexture(resource);
    }
    for (u32 index = 0; index < sFloorPaletteCount; ++index) {
        sPaletteBackup[index] = palette[sFloorPaletteFirst + index];
        palette[sFloorPaletteFirst + index] = FadeColor(sPaletteBackup[index], sFloorFadeColor, evy);
    }
    const u32 skyCount = sSkyOwned ? sSkyCount : 0u;
    u16* skyBackup = sPaletteBackup + sFloorPaletteCount;
    for (u32 index = 0; index < skyCount && sFloorPaletteCount + index < W2U_PALETTE_BACKUP_COLORS; ++index) {
        skyBackup[index] = palette[sSkyFirst + index];
        palette[sSkyFirst + index] = FadeColor(skyBackup[index], sSkyFadeColor, evy);
    }
    const bool uploaded = UploadTexture(resource);
    for (u32 index = 0; index < sFloorPaletteCount; ++index) {
        palette[sFloorPaletteFirst + index] = sPaletteBackup[index];
    }
    for (u32 index = 0; index < skyCount && sFloorPaletteCount + index < W2U_PALETTE_BACKUP_COLORS; ++index) {
        palette[sSkyFirst + index] = skyBackup[index];
    }
    return uploaded;
}

// Smoothstep from 0 to 16 over `frames`; Psychic adds a slow wobble (still 0 at the start and 16 at the end).
u32 FadeEvy(u32 frame, u32 frames)
{
    if (!frames || frame >= frames) {
        return W2U_PALETTE_FADE_MAX_EVY;
    }
    const s32 n = static_cast<s32>(frames), f = static_cast<s32>(frame);
    s32 evy = static_cast<s32>((static_cast<s64>(16) * f * f * (3 * n - 2 * f)) / (static_cast<s64>(n) * n * n));
    if (sFloorFadeWobble) {
        const u32 angle = static_cast<u32>(static_cast<u64>(f) * 65536u * 3u / static_cast<u64>(n));
        evy += static_cast<s32>((3 * SinTurn(angle)) >> 12);
    }
    return evy < 0 ? 0u : evy > 16 ? 16u : static_cast<u32>(evy);
}

void EndFloorFade()
{
    sHazeColor = sHazeTo.color;
    sHazeEvy = sHazeTo.evy;
    sSkyOwned = SkyDiffers(sActiveTerrainResource);
    sSkyRepeatWanted = sSkyOwned;
    BakeHaze();
    SetFieldGlow(sGlowTo.color, sGlowTo.evy);
    sFloorFadePhase = FLOOR_FADE_IDLE;
    sFloorFadeFrom = 0;
    sAppliedSerial = sFloorFadeSerial;
    sElectricTransitionSerial = 0u;
    sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
    sElectricAnimationStarted = false;
    sPrepareFailedSerial = 0u;
}

void ReleaseFloorFade()
{
    if (sFloorFadeResource) {
        ReleaseTerrainResource(sFloorFadeResource, sFloorFadeTex);
    }
    sFloorFadeResource = 0;
    sFloorFadeTex = 0;
    sFloorFadeFrom = 0;
    sFloorFadePhase = FLOOR_FADE_IDLE;
    sFloorPaletteCount = 0u;
    sHazeEvy = 0u;
    sSkyFirst = 0u;
    sSkyCount = 0u;
    sSkyOwned = false;
    sSkyRepeatWanted = false;
    ReleaseSkyRepeat();
    RestoreFieldGlow();
    sFloorAnimDirty = false;
    ResetFloorPaletteAnimation();
    ResetEffectWatch();
}

// Start fading the visible floor to `resource` (a prepared terrain clone, taken over) or, with null, back to the
// native floor. False: no fade possible (the caller swaps at once).
bool StartFloorFade(G3DResource* resource, NNSG3DResTex* texture, u32 terrain, u32 serial)
{
    if (!FindFloorPaletteRange(resource ? resource : sActiveTerrainResource)) {
        return false;
    }
    const TerrainPace* from = PaceFor(sAppliedTerrain);
    const TerrainPace* to = PaceFor(terrain);
    sFloorFadeResource = resource;
    sFloorFadeTex = texture;
    sFloorFadeTerrain = terrain;
    sFloorFadeSerial = serial;
    sFloorFadeFrom = GetVisiblePaletteResource();
    sFloorFadeColor = AverageFloorColor(resource ? resource : sFieldResource);
    // the backdrop fades with the floor when either side replaces it
    sSkyOwned = SkyDiffers(sFloorFadeFrom) || SkyDiffers(resource);
    sSkyFadeColor = AverageRangeColor(resource ? resource : sFieldResource, sSkyFirst, sSkyCount);
    sFloorFadeOutFrames = from ? from->fadeOutFrames : W2U_NATIVE_FLOOR_FADE_OUT_FRAMES;
    sFloorFadeInFrames = to ? to->fadeInFrames : (from ? from->fadeInFrames : W2U_NATIVE_FLOOR_FADE_OUT_FRAMES);
    sFloorFadeWobble = sAppliedTerrain == TERRAIN_PSYCHIC ? 1u : 0u;
    sHazeFrom = HazeFor(sAppliedTerrain);
    sHazeTo = HazeFor(terrain);
    sGlowFrom = GlowFor(sAppliedTerrain);
    sGlowTo = GlowFor(terrain);
    sHazeColor = sHazeFrom.color;
    sHazeEvy = sHazeFrom.evy;
    sFloorFadeFrame = 0u;
    sFloorFadePhase = FLOOR_FADE_OUT;
    sFloorAnimDirty = false;                     // the fade takes over the floor palette
    ResetFloorPaletteAnimation();
    if (sAppliedTerrain != TERRAIN_NULL) {
        sTerrainAmbientStopping = true;          // the old terrain's particles finish, no new ones
    }
    return true;
}

// Midpoint: every floor colour is the blend colour (`evy` 16); swap the image underneath.
void SwapFloorUnderFade(u32 evy)
{
    if (sFloorFadeResource) {
        SetFieldPaletteFadeResource(sFloorFadeResource);
        if (!UploadTextureFloorFaded(sFloorFadeResource, evy)) {
            SetFieldPaletteFadeResource(GetVisiblePaletteResource());
            ReleaseTerrainResource(sFloorFadeResource, sFloorFadeTex);
            return;
        }
        G3DResource* previousResource = sActiveTerrainResource;
        NNSG3DResTex* previousTex = sActiveTerrainTex;
        sActiveTerrainResource = sFloorFadeResource;
        sActiveTerrainTex = sFloorFadeTex;
        sFloorFadeResource = 0;
        sFloorFadeTex = 0;
        sAppliedTerrain = sFloorFadeTerrain;
        sTerrainAmbientStopping = false;
        ResetTerrainAmbientTimer();
        SetFieldPaletteFadeResource(sActiveTerrainResource);
        ReleaseTerrainResource(previousResource, previousTex);
        ResetFloorAnimation();
    } else {
        SetFieldPaletteFadeResource(sFieldResource);
        if (UploadTextureFloorFaded(sFieldResource, evy)) {
            ResetFloorAnimation();
            ReleaseActiveTerrainResource();
        } else {
            SetFieldPaletteFadeResource(GetVisiblePaletteResource());
        }
    }
    sFloorFadeWobble = sAppliedTerrain == TERRAIN_PSYCHIC ? 1u : 0u;
    sSkyRepeatWanted = SkyDiffers(sActiveTerrainResource);
}

// One VBlank of the fade (from ApplyPending, after the native VBlank work).
void AdvanceFloorFade()
{
    FieldPaletteFadeWork* vm = GetFieldPaletteFadeWork();
    const bool vmFading = vm && vm->active;
    const u32 vcount = *reinterpret_cast<volatile u16*>(0x04000006);
    if (!vmFading && (vcount < 0xC0u || vcount > W2U_FLOOR_UPLOAD_LAST_LINE)) {
        return;                                  // too late in this VBlank: next one
    }
    // An animation fading the whole field takes over: finish at once and leave the palette to it.
    const bool hurry = vmFading || sRequestSerial != sFloorFadeSerial;
    if (sFloorFadePhase == FLOOR_FADE_OUT) {
        if (!hurry && sFloorFadeFrame < sFloorFadeOutFrames) {
            ++sFloorFadeFrame;
            const u32 progress = FadeEvy(sFloorFadeFrame, sFloorFadeOutFrames);
            sHazeColor = sHazeFrom.color;
            sHazeEvy = (sHazeFrom.evy * (W2U_PALETTE_FADE_MAX_EVY - progress)) >> 4;
            SetFieldGlow(sGlowFrom.color, (sGlowFrom.evy * (W2U_PALETTE_FADE_MAX_EVY - progress)) >> 4);
            UploadFloorPalette(sFloorFadeFrom, progress);
            if (sFloorFadeFrame < sFloorFadeOutFrames) {
                return;
            }
        }
        sHazeEvy = 0u;                           // the incoming palette is uploaded untinted
        SetFieldGlow(sGlowTo.color, 0u);
        SwapFloorUnderFade(hurry ? 0u : W2U_PALETTE_FADE_MAX_EVY);
        sFloorFadePhase = FLOOR_FADE_IN;
        sFloorFadeFrame = 0u;
        if (!hurry) {
            return;
        }
    }
    if (hurry) {
        sHazeColor = sHazeTo.color;
        sHazeEvy = sHazeTo.evy;
        sSkyOwned = SkyDiffers(sActiveTerrainResource);
        if (!vmFading) {
            UploadFloorPalette(GetVisiblePaletteResource(), 0u);
        }
        EndFloorFade();
        return;
    }
    ++sFloorFadeFrame;
    const u32 frames = sFloorFadeInFrames;
    const u32 progress = sFloorFadeFrame >= frames ? W2U_PALETTE_FADE_MAX_EVY : FadeEvy(sFloorFadeFrame, frames);
    sHazeColor = sHazeTo.color;
    sHazeEvy = (sHazeTo.evy * progress) >> 4;
    SetFieldGlow(sGlowTo.color, (sGlowTo.evy * progress) >> 4);
    UploadFloorPalette(GetVisiblePaletteResource(), W2U_PALETTE_FADE_MAX_EVY - progress);
    if (sFloorFadeFrame >= frames) {
        EndFloorFade();
    }
}

// One VBlank of the Grassy / Misty floor animation (W2U_TerrainTexture_AdvanceAnimation).
void AdvanceFloorPaletteAnimation()
{
    const u32 terrain = sAppliedTerrain;
    const bool animated = (terrain == TERRAIN_GRASSY || terrain == TERRAIN_MISTY) &&
        sFloorFadePhase == FLOOR_FADE_IDLE && sActiveTerrainResource && sFloorPaletteCount;
    FieldPaletteFadeWork* vm = GetFieldPaletteFadeWork();
    const bool vmFading = vm && vm->active;
    const u32 vcount = *reinterpret_cast<volatile u16*>(0x04000006);
    if (vcount < 0xC0u || vcount > W2U_FLOOR_UPLOAD_LAST_LINE) {
        return;
    }
    if (!animated || vmFading || EffectBusy()) {
        // leave the plain floor to the fade / the effect (once; a field fade uploads the whole palette itself)
        if (sFloorAnimDirty && animated && !vmFading) {
            UploadFloorPaletteTo(sActiveTerrainResource, 0u, 0u, false);
        }
        sFloorAnimDirty = false;
        ResetFloorPaletteAnimation();
        return;
    }
    ++sFloorAnimFrame;
    if (terrain == TERRAIN_GRASSY) {
        // 0 .. W2U_GRASSY_GLOW_MAX_EVY .. 0: (1 - cos) / 2 over the period, rounded
        const fx32 wave = FX32_ONE - SinTurn(sFloorAnimFrame * W2U_GRASSY_GLOW_PERIOD_STEP + 0x4000u);
        const u32 evy = static_cast<u32>((wave * static_cast<fx32>(W2U_GRASSY_GLOW_MAX_EVY) + FX32_ONE) >> 13);
        if (evy != sFloorAnimEvy) {
            sFloorAnimEvy = evy;
            UploadFloorPaletteTo(sActiveTerrainResource, evy, W2U_GRASSY_GLOW_COLOR, false);
            sFloorAnimDirty = true;
        }
        return;
    }
    // Misty: start a twinkle every 2-6 frames, age the live ones, upload while any is lit
    bool any = false;
    for (u32 t = 0; t < W2U_FLOOR_TWINKLES; ++t) {
        FloorTwinkle& twinkle = sTwinkles[t];
        if (twinkle.active && ++twinkle.age >= sizeof(W2U_TWINKLE_LEVELS)) {
            twinkle.active = 0u;
        }
        any |= twinkle.active != 0u;
    }
    if (sFloorAnimSpawn) {
        --sFloorAnimSpawn;
    } else {
        for (u32 t = 0; t < W2U_FLOOR_TWINKLES; ++t) {
            if (!sTwinkles[t].active) {
                sTwinkles[t].index = static_cast<u16>(FloorAnimRandom(sFloorPaletteCount));
                sTwinkles[t].age = 0u;
                sTwinkles[t].active = 1u;
                any = true;
                break;
            }
        }
        sFloorAnimSpawn = 2u + FloorAnimRandom(5u);
    }
    if (any || sFloorAnimDirty) {
        UploadFloorPaletteTo(sActiveTerrainResource, 0u, 0u, true);
        sFloorAnimDirty = any;
    }
}
#endif

fx32 FloorAnimationStep(u32 terrain)
{
    if (terrain == TERRAIN_PSYCHIC) {
        return PsychicFloorStep(sPsychicFloorFrame++);
    }
    const TerrainPace* pace = 0;
    const s32 index = TerrainTextureIndex(terrain);
    if (index >= 0) {
        pace = &W2U_TERRAIN_PACE[index];
    }
    return pace ? pace->floorStep : FX32_ONE / 2;
}

} // namespace

extern "C" void W2U_TerrainTexture_Request(u32 terrain)
{
    ResetTerrainAmbientTimer();
#if defined(W2U_TERRAIN_FLOOR_FADES)
    ResetEffectWatch();
#endif
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

namespace {
// Load the requested terrain's texture and particles (the viewer's normal update, never VBlank). `animated`: a
// terrain move's animation is starting and the floor fades in once it has ended; otherwise (an ability, which plays
// no animation) at once.
void PrepareRequestedTerrain(u32 terrain, bool animated)
{
    const u32 requestSerial = sRequestSerial;
    if (!PrepareTerrainResource(terrain, requestSerial)) {
        sPrepareFailedSerial = requestSerial;
        return;
    }

    if (AmbientSpaMemberForTerrain(terrain)) {
        // Archive IO and particle-system allocation stay in the normal viewer
        // update. Only the texture upload is deferred to the VBlank hook.
        PrepareTerrainAmbientParticles(terrain);
    }

    sPrepareFailedSerial = 0u;
#if defined(W2U_TERRAIN_FLOOR_FADES)
    ResetEffectWatch();                          // the floor fades in once this animation has ended
    if (!animated) {
        sEffectSeenBusy = true;                  // no animation: "ended" as soon as no effect runs
    }
#else
    (void)animated;
#endif
    if (terrain == TERRAIN_ELECTRIC && sAppliedTerrain != TERRAIN_ELECTRIC) {
        // (no animation: no masking black fade either; the floor fade takes over, ApplyPending)
        sElectricAnimationStarted = true;
        sElectricTransitionSerial = sRequestSerial;
        sElectricTransitionPhase = ELECTRIC_TRANSITION_WAIT_FADE_START;
    }
}
} // namespace

extern "C" void W2U_TerrainTexture_DeferStartUntilMessage(u32 msgID)
{
    sDeferredStartMsgID = msgID;
    sDeferredStartSerial = sRequestSerial;
}

extern "C" void W2U_TerrainTexture_OnSetMessageStart(u32 msgID)
{
    if (msgID == sDeferredStartMsgID) {
        const u32 startSerial = sDeferredStartSerial;
        sDeferredStartMsgID = W2U_NO_DEFERRED_MESSAGE;
        sDeferredStartSerial = 0u;
        const u32 terrain = sRequestedTerrain;
        // (a newer terrain request since then has its own start)
        if (sRequestSerial == startSerial && terrain >= TERRAIN_ELECTRIC && terrain <= TERRAIN_PSYCHIC) {
            PrepareRequestedTerrain(terrain, false);
        }
    }

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
    PrepareRequestedTerrain(terrain, true);
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
#if defined(W2U_TERRAIN_FLOOR_FADES)
    sSkyFirst = mapping->skyPaletteFirst;
    sSkyCount = mapping->skyPaletteCount;
#endif
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
#if defined(W2U_TERRAIN_FLOOR_FADES)
    if (sFloorFadePhase != FLOOR_FADE_IDLE) {
        AdvanceFloorFade();                      // the fade owns the floor until it ends
        return;
    }
#endif
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
#if defined(W2U_TERRAIN_FLOOR_FADES)
        if (sAppliedTerrain != TERRAIN_NULL && StartFloorFade(0, 0, TERRAIN_NULL, requestedSerial)) {
            return;
        }
#endif
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
#if defined(W2U_TERRAIN_FLOOR_FADES)
            // The masking black fade was missed (its animation ran while another floor fade owned the floor, or
            // never started): fade the floor in like the other terrains instead of waiting for it forever.
            if (sElectricTransitionPhase != ELECTRIC_TRANSITION_WAIT_FADE_END &&
                sElectricAnimationStarted && TerrainAnimationFinished()) {
                sElectricTransitionPhase = ELECTRIC_TRANSITION_IDLE;
                readyToUpload = true;
            } else
#endif
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
#if defined(W2U_TERRAIN_FLOOR_FADES)
        if (!maskedElectricUpload) {
            if (requestedTerrain != TERRAIN_ELECTRIC && !TerrainAnimationFinished()) {
                return;                          // fade in after the terrain move's animation
            }
            if (StartFloorFade(sPreparedTerrainResource, sPreparedTerrainTex, requestedTerrain, requestedSerial)) {
                sPreparedTerrainResource = 0;    // owned by the fade now
                sPreparedTerrainTex = 0;
                sPreparedTerrain = TERRAIN_NULL;
                sPreparedSerial = 0u;
                return;
            }
        }
#endif

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
            ResetTerrainAmbientTimer();
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
    // Particle texture VRAM setup stays in VBlank. Emitter timing and creation
    // run from the normal BTLV_EFFECT_Main path below.
    FinishTerrainAmbientParticleSetup();
#if defined(W2U_TERRAIN_FLOOR_FADES)
    AdvanceFloorPaletteAnimation();
#endif

#if defined(W2U_TERRAIN_FLOOR_FADES)
    if (sSkyRepeatBound && sSkyTransS) {
        sDriftSky += W2U_SKY_DRIFT;
        *sSkyTransS = (sDriftSky >> 4) & (FX32_ONE - 1);   // fx32, one texture width = FX32_ONE
    }
#endif

    if (sAppliedTerrain == TERRAIN_NULL || !EnsureFloorAnimation()) {
        return;
    }

    G3DAnim* animations[] = { sFloorAnimation };
    G3DActor proxy = { sFieldModel, animations, 1u, 0u };
#if defined(W2U_TERRAIN_FLOOR_FADES)
    const bool sideways = sAppliedTerrain == TERRAIN_GRASSY || sAppliedTerrain == TERRAIN_MISTY;
    if (sideways != sFloorScrollHorizontal) {
        SetFloorScrollHorizontal(sideways);
        ResetFloorAnimation();
    }
    if (sideways) {
        sDriftFloor += W2U_FLOOR_DRIFT;
        SetFloorScrollOffset((sDriftFloor >> 4) & (FX32_ONE - 1));
        return;
    }
#endif
    GFL_G3DActorStepAnmFrameLoop(&proxy, 0u, FloorAnimationStep(sAppliedTerrain));
}

extern "C" void W2U_TerrainTexture_AdvanceAmbient()
{
    // BTLV_EFFECT_Main and GFL_PTC_Main continue to run while the native
    // camera free-roams. This standalone system consequently neither waits on
    // the move VM nor starts the HUD/background changes made by that VM.
    AdvanceTerrainAmbient();
#if defined(W2U_TERRAIN_FLOOR_FADES)
    UpdateSkyRepeat();
#endif
}

extern "C" void W2U_TerrainTexture_FieldExit()
{
    W2U_BattleState_OnBattleExit();
    sRequestedTerrain = TERRAIN_NULL;
    sDeferredResetMsgID = W2U_NO_DEFERRED_MESSAGE;
    sDeferredResetSerial = 0u;
    sDeferredStartMsgID = W2U_NO_DEFERRED_MESSAGE;
    sDeferredStartSerial = 0u;
    sRequestSerial = sRequestSerial + 1u;
    if (sRequestSerial == 0u) {
        sRequestSerial = 1u;
    }
    ClearFieldViewState();
}
