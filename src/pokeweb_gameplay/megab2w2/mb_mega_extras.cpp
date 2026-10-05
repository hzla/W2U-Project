// MegaB2W2 Mega extras (phase 5), resident in White2Upgrade.dll, White 2 only. Ported from MegaB2W2's MegaSound.cpp
// and MegaGaugeIcon.cpp onto W2U's own Mega Evolution flow (w2u_mega.cpp). See docs/megab2w2-integration.md.
//
// 1. The Mega's cry with a reverb tail. W2U's Mega animation plays no cry. The cry is loaded through PokeVoice 32
//    frames after W2U swaps the sprite (W2U_MEGA_FORM_REFRESH_FRAME), its PCM8 samples run through a Freeverb-style
//    reverb into a buffer 1.9 s longer (in chunks, one per frame, so no frame takes the whole cost), and it plays 62
//    frames after the swap (or when the animation ends, if that is sooner) - MegaB2W2's timing relative to the
//    swap. PokeVoice slots: 0x34 bytes at *(0x02006AF8): +0x08 sample bytes, +0x0C rate, +0x10 PCM8 data. On
//    release PokeVoice_Reset points +0x10 back at the slot's own buffer, so ours is freed once the voice stops. The
//    reverb is bit-exact with MegaB2W2's scripts/sound/cry_reverb.py. (MegaB2W2's four remixed sound effects were
//    for its own shell animation; with W2U's animation it plays only this cry, as here.)
//
// 2. The Mega icon on the HP gauges: DBK's UI/Battle/icon_mega.png (Lucidious89, credited in the docs) at 11x11 in
//    a 16x16 OBJ, a prefix to the name on every gauge (both sides, every layout), for a Pokemon in a Mega form that
//    is not transformed; hidden while its Mega animation plays. Gauge system (ov168, btlv_gauge): 8 gauges x 0x84
//    by view position; +0x40 main actor (+0xC/+0xE s16 screen x/y of the 128x32 cell centre, +0x60 bit 26 drawn),
//    +0xB0 bit 3 set up. Every gauge setup goes through BtlvCore_SetupGauge (re-implemented 1:1 to remember the
//    BattleMon); the gauge system's create / delete call sites bracket the battle view. The icon is written into
//    the OAM shadow at the game's main OAM transfer (unused entries only), its palette into OBJ palette 12 at the
//    palette transfer, its tiles at OBJ VRAM 0x7F80 (game data ends around 0x6700 in triples).
//
// 3. The Mega glyph, MegaB2W2's: DBK's Mega/icon.png (13x25 + outline in a 16x32 OBJ, 4 dithered fade stages)
//    above the Mega's own sprite instead of W2U's SPA 769, which the animation script showed at a fixed spot
//    (removed from a/0/6/5 #622; W2U's animation is otherwise unchanged). Armed when W2U refreshes the sprite, it
//    appears GLYPH_DELAY frames later (where SPA 769 appeared), fades in (4 x 6 frames), stays, fades out
//    (MegaB2W2 / DBK timing); W2U's Mega wait holds until it is gone. Placement: the sprite's MCSS ground point
//    projected every frame (as MCSS_Draw: camera x projection, MegaB2W2's ProjectSprite) and the Mega's PWAN
//    top row / centre (mb_mega_glyph_heights.inc; canvas row 88 = the ground point, measured); its bottom 10 px
//    above the sprite's top, kept on screen. Tiles at OBJ VRAM 0x7B80, palette 13.
//
// Every hooked call site was checked in W2U's built ROM (same BL and target as vanilla White 2); none is hooked by
// W2U.
#include "ability_api.h"
#include "mb_resident.h"

extern "C" {
// ARM9
u16  PokeVoice_Load(u32 species, u32 form, u32 pan, u32 chorus, u32 chorusVol, u32 chorusSpeed, u32 reverse,
                    void* chatter);
b32  PokeVoice_StartPlayback(u32 handle);
b32  PokeVoice_IsPlaying(u32 handle);
void PokeVoice_Release(u32 handle);
void* GFL_HeapAllocate(u32 heapID, u32 size, u32 clear, const char* file, u32 line);
void GFL_HeapFree(void* p);
void dma_copy(u32 dmaNo, const void* src, void* dst, u32 size, u32 flag);
void dma_copy16(u32 dmaNo, const void* src, void* dst, u32 size, u32 flag);
// ov168
void* BtlvGauge_Create(void* a, u32 battleType, u32 heap);
void  BtlvGauge_Delete(void* sys);
void  BtlvGauge_Setup(void* sys, void* a, BattleMon* bm, u32 layout, u32 vpos);
// w2u_mega.cpp
bool W2U_Mega_IsMegaEvolved(const BattleMon* bm);
s32  W2U_Mega_AnimatingViewPos();
}

namespace {
// ---- the Mega icon's art (MegaB2W2 generated/mega_shell.h: DBK icon_mega.png reduced to 11x11) ----------------
const u16 MEGA_ICON_PALETTE[16] = {0x0000, 0x7FDD, 0x5B8E, 0x6B6B, 0x4ED8, 0x22EE, 0x6F08, 0x76A8, 0x2EC7, 0x6A46,
                                   0x4264, 0x45B0, 0x3DC5, 0x45C2, 0x5962, 0x0C42};
const u32 MEGA_ICON_W = 11;
const u8 MEGA_ICON_TILES[128] __attribute__((aligned(4))) = {
#include "mb_mega_icon_tiles.inc"
};

// ---- cry reverb ---------------------------------------------------------------------------------------------
constexpr u32 CRY_LOAD_AFTER_SWAP = 32, CRY_AFTER_SWAP = 62;
constexpr u32 HEAP = 0x13;
constexpr u32 VOICE_SLOTS_PTR = 0x02006AF8, VOICE_SLOT_SIZE = 0x34;
constexpr u32 COMB_MS10[4] = { 297, 371, 411, 437 };
constexpr u32 AP_MS10[2] = { 50, 17 };
constexpr s32 FEEDBACK = 28180, DAMP = 13107, AP_GAIN = 16384, IN_GAIN = 8192;   // Q15
constexpr s32 DRY = 2662, WET = 3277;                                           // Q12
constexpr s32 KNEE = 96, SHIFT = 6;
constexpr u32 TAIL_MS = 1900;

u32 UDiv(u32 n, u32 d) {
    u32 q = 0, r = 0;
    for (int i = 31; i >= 0; --i) {
        r = (r << 1) | ((n >> i) & 1);
        if (r >= d) { r -= d; q |= 1u << i; }
    }
    return q;
}

enum : u8 { CRY_IDLE, CRY_PROCESSING, CRY_READY, CRY_PLAYING };
struct {
    u8 state;
    u16 handle;
    u8* slot;
    const s8* src; u32 n;
    s8* out; u32 total, pos, chunk;
    void* block;
    s32* comb[4]; u32 clen[4], cidx[4]; s32 filt[4];
    s32* ap[2]; u32 alen[2], aidx[2];
} g_cry;
struct { bool active; u16 species, form; u32 pan; u32 swapFrame; } g_seq;

u8* VoiceSlot(u32 handle) { return *(u8**)VOICE_SLOTS_PTR + handle * VOICE_SLOT_SIZE; }

void FreeCry() {
    if (g_cry.block) GFL_HeapFree(g_cry.block);
    g_cry.block = nullptr;
    g_cry.state = CRY_IDLE;
}

// Loads the cry (not playing yet) and sets the reverb up; without memory it plays dry.
void PrepareCry(u16 species, u16 form, u32 pan, u32 framesLeft) {
    FreeCry();
    g_cry.handle = PokeVoice_Load(species, form, pan, 0, 0, 0, 0, nullptr);
    g_cry.slot = VoiceSlot(g_cry.handle);
    g_cry.src = *(const s8**)(g_cry.slot + 0x10);
    g_cry.n = *(u32*)(g_cry.slot + 0x08);
    u32 rate = *(u32*)(g_cry.slot + 0x0C);
    if (!g_cry.src || !g_cry.n || rate < 4000 || rate > 48000) { g_cry.state = CRY_READY; return; }
    u32 len = 0;
    for (int k = 0; k < 4; ++k) { g_cry.clen[k] = UDiv(rate * COMB_MS10[k], 10000) | 1; len += g_cry.clen[k]; }
    for (int k = 0; k < 2; ++k) { g_cry.alen[k] = UDiv(rate * AP_MS10[k], 10000) | 1; len += g_cry.alen[k]; }
    g_cry.total = (g_cry.n + UDiv(rate * TAIL_MS, 1000) + 3) & ~3u;
    g_cry.block = GFL_HeapAllocate(HEAP, g_cry.total + len * 4, 1, "MegaCry", __LINE__);
    if (!g_cry.block) { g_cry.state = CRY_READY; return; }
    s32* w = (s32*)g_cry.block;
    for (int k = 0; k < 4; ++k) { g_cry.comb[k] = w; w += g_cry.clen[k]; g_cry.cidx[k] = 0; g_cry.filt[k] = 0; }
    for (int k = 0; k < 2; ++k) { g_cry.ap[k] = w; w += g_cry.alen[k]; g_cry.aidx[k] = 0; }
    for (s32* p = (s32*)g_cry.block; p < w; ++p) *p = 0;
    g_cry.out = (s8*)w;
    g_cry.pos = 0;
    g_cry.chunk = UDiv(g_cry.total, framesLeft ? framesLeft : 1) + 1;
    g_cry.state = CRY_PROCESSING;
}

void ProcessCry(u32 count) {
    u32 end = g_cry.pos + count;
    if (end > g_cry.total) end = g_cry.total;
    for (u32 i = g_cry.pos; i < end; ++i) {
        s32 dry = i < g_cry.n ? (s32)g_cry.src[i] << SHIFT : 0;
        s32 in = (dry * IN_GAIN) >> 15;
        s32 acc = 0;
        for (int k = 0; k < 4; ++k) {
            s32* b = g_cry.comb[k] + g_cry.cidx[k];
            s32 o = *b;
            g_cry.filt[k] = (o * (32768 - DAMP) + g_cry.filt[k] * DAMP) >> 15;
            *b = in + ((g_cry.filt[k] * FEEDBACK) >> 15);
            if (++g_cry.cidx[k] == g_cry.clen[k]) g_cry.cidx[k] = 0;
            acc += o;
        }
        for (int k = 0; k < 2; ++k) {
            s32* b = g_cry.ap[k] + g_cry.aidx[k];
            s32 v = *b;
            s32 o = v - acc;
            *b = acc + ((v * AP_GAIN) >> 15);
            if (++g_cry.aidx[k] == g_cry.alen[k]) g_cry.aidx[k] = 0;
            acc = o;
        }
        s32 y = ((dry * DRY) >> 12) + ((acc * WET) >> 12);
        y = (y + (1 << (SHIFT - 1))) >> SHIFT;
        s32 a = y < 0 ? -y : y;
        if (a > KNEE) a = KNEE + ((a - KNEE) >> 1);
        if (a > 127) a = 127;
        g_cry.out[i] = (s8)(y < 0 ? -a : a);
    }
    g_cry.pos = end;
    if (g_cry.pos >= g_cry.total) g_cry.state = CRY_READY;
}

void StartCry() {
    if (g_cry.state == CRY_PROCESSING) ProcessCry(g_cry.total);
    if (g_cry.state != CRY_READY) return;
    if (g_cry.block) {                                                   // swap our buffer into the slot
        *(s8**)(g_cry.slot + 0x10) = g_cry.out;
        *(u32*)(g_cry.slot + 0x08) = g_cry.total;
    }
    if (!PokeVoice_StartPlayback(g_cry.handle)) { FreeCry(); return; }
    g_cry.state = CRY_PLAYING;
}

// ---- gauge icon ---------------------------------------------------------------------------------------------
constexpr u32 OAM_MAIN = 0x07000000, OBJ_VRAM = 0x06400000, OBJ_PALETTE_MAIN = 0x05000200;
constexpr u32 ICON_VRAM = 0x7F80;
constexpr u16 ICON_TILE = ICON_VRAM / 64;
constexpr u8 PAL_ICON = 12, OBJ_PRIORITY = 1;
constexpr u32 BTLV_CORE_PTR = 0x021F4280;
constexpr u32 CORE_GAUGE = 0x1A4, CORE_BATTLE_TYPE = 0x1BC;
constexpr u32 GAUGES = 8, GAUGE_SIZE = 0x84;
constexpr u32 G_ACTOR = 0x40, G_FLAGS = 0xB0, G_FLAG_SET_UP = 1u << 3;
constexpr u32 ACTOR_X = 0xC, ACTOR_Y = 0xE, ACTOR_FLAGS = 0x60, ACTOR_DRAWN = 1u << 26;
// the name line relative to the main actor (MegaB2W2's measurements, every layout): rows y-9..y-1, the name starts
// at x-48 (player) / x-40 (foe); the icon ends 2 px before the name, bottom row on the text's bottom row
constexpr int NAME_GAP = 2, NAME_BOTTOM = -1;
constexpr int NAME_X[2] = { -48, -40 };

u8* g_gauges;
BattleMon* g_mon[GAUGES];

bool ShowsIcon(BattleMon* bm) {
    return bm && !BattleMon_IsFainted(bm) && !BattleMon_TransformCheck(bm) && W2U_Mega_IsMegaEvolved(bm);
}

// previous unused OAM entry before `slot` (disabled: attr0 bits 8-9 = 2, or y = 0xC0), -1 if none
s32 NextParked(const u16* shadow, s32 slot) {
    do { --slot; } while (slot >= 0 && !((shadow[slot * 4] & 0x300) == 0x200 || (shadow[slot * 4] & 0xFF) == 0xC0));
    return slot;
}

void WriteIcons(u16* shadow, s32& slot) {
    if (!g_gauges) return;
    s32 animating = W2U_Mega_AnimatingViewPos();
    bool shown = false;
    for (u32 i = 0; i < GAUGES; ++i) {
        if ((s32)i == animating || !ShowsIcon(g_mon[i])) continue;
        u8* gauge = g_gauges + i * GAUGE_SIZE;
        u8* actor = *(u8**)(gauge + G_ACTOR);
        if (!actor || !(*(u32*)(gauge + G_FLAGS) & G_FLAG_SET_UP) || !(*(u32*)(actor + ACTOR_FLAGS) & ACTOR_DRAWN))
            continue;
        int x = *(s16*)(actor + ACTOR_X) + NAME_X[i & 1] - NAME_GAP - (int)MEGA_ICON_W;
        int y = *(s16*)(actor + ACTOR_Y) + NAME_BOTTOM + 1 - (int)MEGA_ICON_W;
        if (x <= -16 || x >= 256 || y <= -16 || y >= 192) continue;      // slid off screen
        slot = NextParked(shadow, slot);
        if (slot < 0) break;
        u16* e = shadow + slot * 4;
        e[0] = (u16)(y & 0xFF);                                          // square, regular OBJ
        e[1] = (u16)((x & 0x1FF) | (1 << 14));                           // 16x16
        e[2] = (u16)(ICON_TILE | (OBJ_PRIORITY << 10) | (PAL_ICON << 12));
        shown = true;
    }
    if (shown) {
        volatile u32* d = (volatile u32*)(OBJ_VRAM + ICON_VRAM);
        const u32* s = (const u32*)MEGA_ICON_TILES;
        for (u32 k = 0; k < sizeof(MEGA_ICON_TILES) / 4; ++k) d[k] = s[k];
    }
}
// ---- Mega glyph ---------------------------------------------------------------------------------------------
const u16 MEGA_GLYPH_PALETTE[16] = {0x0000, 0x2F5A, 0x2F3B, 0x2F59, 0x2B57, 0x2ADB, 0x267B, 0x2B35, 0x2733, 0x2730,
                                    0x36CD, 0x468A, 0x263A, 0x21DA, 0x1C85, 0x1C85};
const u8 MEGA_GLYPH_TILES[1024] __attribute__((aligned(4))) = {
#include "mb_mega_glyph_tiles.inc"
};
struct GlyphPlace { u16 species; u8 form, frontTop, frontCx, backTop, backCx; };
const GlyphPlace GLYPH_PLACES[] = {
#include "mb_mega_glyph_heights.inc"
};
constexpr u32 GLYPH_VRAM = 0x7B80;                 // 4 stages x 256 bytes, below the gauge icon
constexpr u16 GLYPH_TILE = GLYPH_VRAM / 64;
constexpr u8 PAL_GLYPH = 13;
constexpr int GLYPH_DELAY = 59;                    // frames after W2U's sprite refresh: where its SPA 769 appeared
constexpr int GLYPH_STEP = 6, GLYPH_HOLD = 60;     // MegaB2W2: 4 x 6 in, shown 1 s, 4 x 6 out
constexpr int GLYPH_END = 4 * GLYPH_STEP + GLYPH_HOLD + 4 * GLYPH_STEP;
constexpr int CANVAS_GROUND_ROW = 88, CANVAS_CENTRE = 48, DEFAULT_TOP = 16, GLYPH_GAP = 10, GLYPH_MIN_BOTTOM = 34;
constexpr u32 CAMERA_MTX_LIT = 0x02019FA4, PROJ_MTX_LIT = 0x02019FC0;   // MCSS_Draw's literal pool

constexpr u32 VBLANK_COUNT = 0x027FFC3C;          // NitroSDK HW_VBLANK_COUNT_BUF: real frames (the OAM transfer
                                                   // runs several times a frame)
struct { bool active, uploaded, started; u32 vpos, start; u8 top, cx; } g_glyph;
// each view position's ground point and scale at the default camera, cached while the player picks a move (W2U's
// Mega animation and its PWAN sprites leave the MCSS sprite's own scale / position unusable for this until later)
struct Place { s16 gx, gy, scale; s32 depth; bool valid; } g_place[GAUGES];

s32 SDiv(s32 n, s32 d) {
    bool neg = (n < 0) != (d < 0);
    s32 q = (s32)UDiv((u32)(n < 0 ? -n : n), (u32)(d < 0 ? -d : d));
    return neg ? -q : q;
}

// the battle view's MCSS sprite at a view position (core +0x190: 14 entries of 0x5C {+8 sprite, +0x50 vpos}).
// W2U's Mega animation hides the old sprite (scale 1/16) and its sprite refresh adds the Mega's as another entry
// at the same view position: the shown one (normal scale, MCSS flag +0x140 bit 11 = vanish clear) is preferred.
s32 SpriteScale(const u8* spr) { return ((*(const s32*)(spr + 0xEC) >> 4) * (*(const s32*)(spr + 0x128) >> 4)) >> 12; }
u8* McssSpriteAt(u32 vpos) {
    u8* core = *(u8**)BTLV_CORE_PTR;
    u8* wrap = core ? *(u8**)(core + 0x190) : nullptr;
    if (!wrap) return nullptr;
    u8* any = nullptr;
    for (int i = 0; i < 14; ++i) {
        u8* e = wrap + i * 0x5C;
        u8* spr = *(u8**)(e + 8);
        if (!spr || *(u32*)(e + 0x50) != vpos) continue;
        s32 sc = SpriteScale(spr);
        if (sc >= 64 && sc <= 1024 && !(*(u32*)(spr + 0x140) & (1u << 11))) return spr;
        if (!any) any = spr;
    }
    return any;
}

// where MCSS draws the sprite's ground point on the top screen, its scale (8.8 screen px per sprite px) and the
// projection's depth term (clip w): on-screen size goes as 1 / w when the camera moves.
bool ProjectSprite(u32 vpos, s32& gx, s32& gy, s32& scale, s32* depth = nullptr, bool anyScale = false) {
    u8* spr = McssSpriteAt(vpos);
    const s32* cam = *(const s32**)CAMERA_MTX_LIT;
    const s32* prj = *(const s32**)PROJ_MTX_LIT;
    if (!spr || !cam || !prj) return false;
    s32 p[3], v[3], c[4];
    for (int k = 0; k < 3; ++k) p[k] = *(s32*)(spr + 0xE0 + 4 * k) + *(s32*)(spr + 0x11C + 4 * k);
    for (int k = 0; k < 3; ++k)
        v[k] = cam[9 + k] + ((p[0] * cam[k]) >> 12) + ((p[1] * cam[3 + k]) >> 12) + ((p[2] * cam[6 + k]) >> 12);
    for (int k = 0; k < 4; ++k)
        c[k] = prj[12 + k] + (((v[0] >> 4) * prj[k]) >> 8) + (((v[1] >> 4) * prj[4 + k]) >> 8) +
               (((v[2] >> 4) * prj[8 + k]) >> 8);
    if (c[3] <= 0) return false;
    if (depth) *depth = c[3];
    scale = SpriteScale(spr);
    if (!anyScale && (scale < 64 || scale > 1024)) return false;
    gx = 128 + SDiv(c[0] * 128, c[3]);
    gy = 96 - SDiv(c[1] * 96, c[3]);
    return gx > -128 && gx < 384 && gy > -96 && gy < 288;
}

// any HP gauge set up and drawn (the HUD is back)
bool GaugesShown() {
    if (!g_gauges) return false;
    for (u32 i = 0; i < GAUGES; ++i) {
        u8* gauge = g_gauges + i * GAUGE_SIZE;
        u8* actor = *(u8**)(gauge + G_ACTOR);
        if (actor && (*(u32*)(gauge + G_FLAGS) & G_FLAG_SET_UP) && (*(u32*)(actor + ACTOR_FLAGS) & ACTOR_DRAWN))
            return true;
    }
    return false;
}

// fade stage 0 (faintest) .. 3 (opaque), -1 hidden
int GlyphStage(int f) {
    if (f < 0 || f >= GLYPH_END) return -1;
    if (f < 4 * GLYPH_STEP) return (int)UDiv((u32)f, GLYPH_STEP);
    if (f < 4 * GLYPH_STEP + GLYPH_HOLD) return 3;
    return 3 - (int)UDiv((u32)(f - 4 * GLYPH_STEP - GLYPH_HOLD), GLYPH_STEP);
}

void WriteGlyph(u16* shadow, s32& slot) {
    if (!g_glyph.active) return;
    const u32 now = *(volatile u32*)VBLANK_COUNT;
    if (!g_glyph.started) { g_glyph.start = now; g_glyph.started = true; }
    int f = (int)(now - g_glyph.start) - GLYPH_DELAY;
    // the HP gauges come back as W2U's animation ends: the glyph fades out then (it would cover the foe's gauge)
    const int fadeOut = 4 * GLYPH_STEP + GLYPH_HOLD;
    if (f >= 4 * GLYPH_STEP && f < fadeOut && GaugesShown()) {
        g_glyph.start -= (u32)(fadeOut - f);
        f = fadeOut;
    }
    if (f >= GLYPH_END) { g_glyph.active = false; return; }
    int stage = GlyphStage(f);
    // the live ground point (the camera of the reveal is not the move-select one, and the screen shakes); the scale
    // from the one cached while the player picked a move, corrected by the depth ratio (W2U's PWAN sprites leave
    // the sprite's own scale fields unusable here)
    s32 gx = 0, gy = 0, sc = 0, depth = 0;
    bool projected = ProjectSprite(g_glyph.vpos, gx, gy, sc, &depth, true);
    if (projected && g_glyph.vpos < GAUGES && g_place[g_glyph.vpos].valid) {
        const Place& pl = g_place[g_glyph.vpos];
        sc = SDiv(pl.scale * (pl.depth >> 4), depth >> 4);
    }
    if (sc < 64 || sc > 1024) projected = false;
    if (stage < 0 || !projected) return;
    if (!g_glyph.uploaded) {
        volatile u32* d = (volatile u32*)(OBJ_VRAM + GLYPH_VRAM);
        const u32* t = (const u32*)MEGA_GLYPH_TILES;
        for (u32 k = 0; k < sizeof(MEGA_GLYPH_TILES) / 4; ++k) d[k] = t[k];
        g_glyph.uploaded = true;
    }
    int top = gy + ((((int)g_glyph.top - CANVAS_GROUND_ROW) * sc) >> 8);
    int bottom = top - GLYPH_GAP;
    if (bottom < GLYPH_MIN_BOTTOM) bottom = GLYPH_MIN_BOTTOM;
    int x = gx + ((((int)g_glyph.cx - CANVAS_CENTRE) * sc) >> 8) - 8, y = bottom - 32;
    if (x <= -16 || x >= 256 || y <= -32 || y >= 192) return;
    slot = NextParked(shadow, slot);
    if (slot < 0) return;
    u16* e = shadow + slot * 4;
    e[0] = (u16)((y & 0xFF) | (2 << 14));                                // vertical shape
    e[1] = (u16)((x & 0x1FF) | (2 << 14));                               // 16x32
    e[2] = (u16)((GLYPH_TILE + stage * 4) | (OBJ_PRIORITY << 10) | (PAL_GLYPH << 12));
}
} // namespace

// ---- W2U's Mega flow calls these (w2u_mega.cpp, White 2) ------------------------------------------------------
// W2U refreshed the Mega's sprite: the glyph's timer starts.
extern "C" void W2U_MB_MegaGlyphArm(u32 viewPos, u32 species, u32 form) {
    g_glyph.active = true;
    g_glyph.uploaded = false;
    g_glyph.vpos = viewPos;
    g_glyph.started = false;
    g_glyph.top = DEFAULT_TOP;
    g_glyph.cx = CANVAS_CENTRE;
    const bool front = (viewPos & 1) != 0;
    for (const GlyphPlace& p : GLYPH_PLACES)
        if (p.species == species && p.form == form) {
            g_glyph.top = front ? p.frontTop : p.backTop;
            g_glyph.cx = front ? p.frontCx : p.backCx;
        }
}

// While the player picks a move (default camera, W2U_Mega_OnActionSelectFightWait): cache every view position's
// ground point and scale for the glyph.
extern "C" void W2U_MB_CacheSpritePlaces() {
    for (u32 v = 0; v < GAUGES; ++v) {
        s32 gx, gy, sc, depth;
        if (ProjectSprite(v, gx, gy, sc, &depth)) g_place[v] = Place{ (s16)gx, (s16)gy, (s16)sc, depth, true };
    }
}

// W2U's Mega wait holds while the glyph is shown
extern "C" bool W2U_MB_MegaGlyphBusy() { return g_glyph.active; }
extern "C" void W2U_MB_MegaCryBegin(u32 species, u32 form, u32 viewPos, u32 swapFrame) {
    g_seq.active = true;
    g_seq.species = (u16)species; g_seq.form = (u16)form;
    g_seq.pan = (viewPos & 1) ? 96 : 32;                                 // foe right of centre, player left
    g_seq.swapFrame = swapFrame;
}

// every frame of the animation wait, with its frame counter
extern "C" void W2U_MB_MegaCryFrame(u32 frame) {
    if (!g_seq.active) return;
    const u32 load = g_seq.swapFrame + CRY_LOAD_AFTER_SWAP, at = g_seq.swapFrame + CRY_AFTER_SWAP;
    if (frame == load) PrepareCry(g_seq.species, g_seq.form, g_seq.pan, at - load - 2);
    if (frame > load && frame < at && g_cry.state == CRY_PROCESSING) ProcessCry(g_cry.chunk);
    if (frame == at) { StartCry(); g_seq.active = false; }
}

// the animation is over: the cry now if it has not played yet
extern "C" void W2U_MB_MegaCryEnd() {
    if (!g_seq.active) return;
    if (g_cry.state == CRY_IDLE) PrepareCry(g_seq.species, g_seq.form, g_seq.pan, 1);
    StartCry();
    g_seq.active = false;
}

// Battle exit (W2U_BattleState_OnBattleExit through W2U_MB_ResetBattleState): the cry and the glyph stop.
extern "C" void W2U_MB_MegaExtrasReset() {
    if (g_cry.state == CRY_PLAYING) PokeVoice_Release(g_cry.handle);
    FreeCry();
    g_seq.active = false;
    g_glyph.active = false;
    for (Place& pl : g_place) pl.valid = false;
}

// ---- hooks --------------------------------------------------------------------------------------------------
// The battle view creates / deletes the gauge system (ov168 0x21DF096 in its setup, 0x21DF202 in its exit).
extern "C" void* THUMB_BRANCH_LINK_168_0x21DF096(void* a, u32 battleType, u32 heap) {
    void* sys = BtlvGauge_Create(a, battleType, heap);
    for (u32 i = 0; i < GAUGES; ++i) g_mon[i] = nullptr;
    g_gauges = (u8*)sys;
    return sys;
}

// (W2U deletes and recreates the gauge system mid-battle too - around the Mega sprite refresh - so the cry and
// the glyph are reset at battle exit instead: W2U_MB_MegaExtrasReset.)
extern "C" void THUMB_BRANCH_LINK_168_0x21DF202(void* sys) {
    if ((u8*)sys == g_gauges) {
        g_gauges = nullptr;
        for (u32 i = 0; i < GAUGES; ++i) g_mon[i] = nullptr;
    }
    BtlvGauge_Delete(sys);
}

// ov168 0x21DFA44, 1:1: the core's layout type is 2 (triples) / 3 (rotation) or 0 for everything else.
extern "C" void THUMB_BRANCH_BtlvCore_SetupGauge(void* a, BattleMon* bm, u32 vpos) {
    u8* core = *(u8**)BTLV_CORE_PTR;
    u32 type = *(u32*)(core + CORE_BATTLE_TYPE);
    if (vpos < GAUGES) g_mon[vpos] = bm;
    BtlvGauge_Setup(*(void**)(core + CORE_GAUGE), a, bm, (type == 2 || type == 3) ? type : 0, vpos);
}

// The game's OAM transfer: dma_copy(3, shadow, OAM + 0x20, 124 * 8, 1) (ARM9 0x20756DC, both screens). Also frees
// the cry's reverb buffer once the voice is done (runs every frame).
extern "C" void THUMB_BRANCH_LINK_ARM9_0x20756DC(u32 dmaNo, u16* src, void* dst, u32 size, u32 flag) {
    if ((u32)dst == OAM_MAIN + 0x20) {
        s32 slot = (s32)(size / 8);
        WriteGlyph(src, slot);
        WriteIcons(src, slot);
        if (g_cry.state == CRY_PLAYING && !PokeVoice_IsPlaying(g_cry.handle)) FreeCry();
    }
    dma_copy(dmaNo, src, dst, size, flag);
}

// The game's OBJ palette transfer: dma_copy16(3, shadow, 0x05000200 / 0x05000600, 0x200, 1) (ARM9 0x207561A).
extern "C" void THUMB_BRANCH_LINK_ARM9_0x207561A(u32 dmaNo, u16* src, void* dst, u32 size, u32 flag) {
    if ((u32)dst == OBJ_PALETTE_MAIN && size >= 16 * 32 && g_gauges) {
        for (int i = 0; i < 16; ++i) src[PAL_ICON * 16 + i] = MEGA_ICON_PALETTE[i];
        if (g_glyph.active)
            for (int i = 0; i < 16; ++i) src[PAL_GLYPH * 16 + i] = MEGA_GLYPH_PALETTE[i];
    }
    dma_copy16(dmaNo, src, dst, size, flag);
}
