// w2anim sprite streams: animated MCSS sprites (Pokemon and trainers, every screen that uses MCSS), frames streamed
// from one ROM file into the sprite's texture. Replaces the PWAN runtimes (docs/megab2w2-integration.md, Phase 4).
// Ported from MegaB2W2's AnimSprites (tools/w2anim), generalised:
//  - any MCSS system: registration at MCSS's three LoadMCSSGraphicsData calls (ARM9), the tick at every caller of
//    MCSS_Main (battle, summary, evolution, egg hatch, ...), release at MCSS_DelSprite (also reached from MCSS_Exit);
//  - the index is read from the ROM when a sprite loads (no table in RAM): sorted {arc, sheet file} -> stream;
//  - two texture modes: TEX4 (the sprite keeps its native 4 bpp texture, palette and cells: each frame overwrites
//    the rows its cells show - W2U's carrier sets) and A3I5 (MegaB2W2: the proxy switched to 128x128 A3I5);
//  - frame durations in ms or in 1/60 s ticks;
//  - all buffers on the sprite's own game heap: nothing in PMC's heap but this code;
//  - evolution (ov284): its morph renderer draws the before / after Pokemon from its own 128x128 bitmaps, built from
//    the native sheets; their stream's current frame and palette are written into it (no extra buffers);
//  - Hall of Fame (ov265): the first frame only, as PWAN showed it.
//
// File `w2anim/streams.bin` (tools/w2anim/build_w2anim_streams.py):
//   header  {'W2AS', u16 version 1, u16 reserved, u32 entryCount, u32 entriesOffset}
//   entries entryCount x {u16 arc, u16 flags, u32 sheetFile, u32 maniOffset, u32 shinyNclrFile} sorted by (arc, sheet);
//           flags & ENTRY_CARRIER (trainers): MCSS loads the front set of pokegra block shinyNclrFile / 20 instead
//           (a 96x96 carrier, primed with the stream's frame 0 and palette, so its own art never shows)
//   MANI    {'MANI', u16 version, u16 flags, u16 boxW, boxH, seqCount, uniqueCount, u32 seqOffset, framesOffset,
//            paletteOffset} (offsets from the MANI start); seq {u16 unique, u16 duration}; frames {u32 offset, size}
//            (from the MANI start; LZ10 / LZ11 blobs of boxH rows); palettes 2 x 16 BGR555 (normal, shiny)
//
// MCSS facts (MegaB2W2 docs/MODLOG.md "Animated sprites"): a sprite slot owns 16 KB of texture VRAM (sys->texBase +
// slot * 0x4000; 256x128 4 bpp natively) and 0x20 bytes of palette VRAM (sys->palBase + slot * 0x20); its image proxy
// (spr + 0x9C: +0xA8 size S, +0xAC size T, +0xB0 format) builds TEXIMAGE_PARAM; spr + 0xD4 / 0xD8 are the original /
// working palette copies its fades start from.
#include "swantypes.h"
#include "util/filesystem.h"

extern "C" {
void LoadMCSSGraphicsData(void* sys, int slot, u32* params);
void MCSS_Main(void* sys);
void MCSS_FreeSpriteResources(void* spr);
void sys_uncomp_lz1x(const void* src, void* dst);
void cp15_flushDC(const void* addr, u32 size);
void gfxBeginTextureUpload();
void gfxUploadTexture(const void* src, u32 texAddr, u32 size);
void gfxEndTextureUpload();
void gfxBeginPaletteUpload();
void gfxUploadPalette(const void* src, u32 palAddr, u32 size);
void gfxEndPaletteUpload();
void* GFL_VBlankTCBAdd(void (*fn)(void* tcb, void* data), void* data, u32 priority);
void GFL_TCBRemove(void* tcb);
void* GFL_HeapAllocate(u32 heapID, u32 size, u32 clear, const char* file, u32 line);
void GFL_HeapFree(void* p);
}

namespace {

const char STREAMS_PATH[] = "w2anim/streams.bin";
constexpr u32 STREAMS_MAGIC = 0x53413257;              // 'W2AS'
constexpr u32 MANI_MAGIC = 0x494E414D;                 // 'MANI'
constexpr u32 MAX_STREAMS = 8;                         // MCSS battle systems have 8 sprite slots
constexpr u32 SLOT_TEX_BYTES = 0x4000, SLOT_PAL_BYTES = 0x20;
constexpr u32 NATIVE_ROW_BYTES = 128;                  // 256 texels, 4 bpp
constexpr u32 A3I5_ROW_BYTES = 128;                    // 128 texels, 8 bpp
constexpr u32 GX_TEXSIZE_128 = 4, GX_TEXFMT_A3I5 = 1;

constexpr u16 MANI_OWN_PALETTES = 1, MANI_TEX4 = 2, MANI_TICKS = 4;
constexpr u16 ENTRY_CARRIER = 1;
constexpr u32 ARC_POKEGRA = 4;

struct StreamsHeader { u32 magic; u16 version, reserved; u32 entryCount, entriesOffset; };
struct IndexEntry { u16 arc, flags; u32 sheetFile, maniOffset, shinyNclrFile; };
struct ManiHeader {
    u32 magic; u16 version, flags; u16 boxW, boxH; u16 seqCount, uniqueCount; u32 seqOffset, framesOffset;
    u32 paletteOffset;
};
struct SeqEntry { u16 unique, duration; };
struct FrameEntry { u32 offset, size; };

// MCSS system / sprite fields
inline u32 SysTexBase(void* sys) { return *(u32*)((u8*)sys + 0x30); }
inline u32 SysPalBase(void* sys) { return *(u32*)((u8*)sys + 0x34); }
inline u32 SysCount(void* sys) { return *(u32*)((u8*)sys + 0x10); }
inline u8* SysSprite(void* sys, u32 slot) { return (*(u8***)((u8*)sys + 0x14))[slot]; }
inline void* SprUploadTask(u8* spr) { return *(void**)spr; }
inline u32 SprFlags(u8* spr) { return *(u32*)(spr + 0x140); }
inline u16 SprHeap(u8* spr) { return (u16)*(u32*)(spr + 0x14C); }
inline s32 SprAnimSpeed(u8* spr) { return *(s32*)(spr + 0x174); }             // fx32 frames per tick
inline u16* SprPaletteOrig(u8* spr) { return *(u16**)(spr + 0xD4); }
inline u16* SprPaletteWork(u8* spr) { return *(u16**)(spr + 0xD8); }
inline u32 SprPaletteSize(u8* spr) { return *(u32*)(spr + 0xDC); }
inline bool SprAnimPaused(u8* spr) { return ((SprFlags(spr) << 21) >> 30) != 0; }   // as MCSS_Main
inline void SprSetA3I5(u8* spr) {
    *(u32*)(spr + 0xA8) = GX_TEXSIZE_128; *(u32*)(spr + 0xAC) = GX_TEXSIZE_128; *(u32*)(spr + 0xB0) = GX_TEXFMT_A3I5;
}

struct Stream {
    void* sys; u8* spr; u32 slot; u32 mani;            // mani: offset of the MANI in the streams file
    u16 flags, boxW, boxH, seqCount, uniqueCount, rowBytes;
    u8* meta;                                          // seq table then frame table (heap)
    u8* lz;                                            // one compressed frame (heap, the largest blob)
    u8* staging;                                       // boxH * rowBytes (heap)
    u32 seqPos; s32 elapsed;                           // time into the current entry, 1/60000 s
    u16 shown;                                         // unique frame in the texture (0xFFFF: none yet)
    volatile u8 pending;                               // staging holds a frame for the next VBlank
    volatile u8 palettePending;
    u8 active, started, formatSet;
    u8 primed;                                         // TEX4: frame 0 and the palette went into MCSS's own upload
    u8 role;                                           // evolution: 1 the Pokemon before, 2 after (0: none)
    volatile u8 indepPending;                          // evolution: the morph bitmap holds a new frame for VBlank
    u16 indepShown;                                    // evolution: unique frame in the morph bitmap
    u8* indepBmp; u32 indepTex;                        // evolution: the morph renderer's bitmap (RAM) and its VRAM
    u16 palette[16];                                   // own palette (normal or shiny), MANI_OWN_PALETTES only
};
Stream g_streams[MAX_STREAMS];
void* g_vblankTask = nullptr;
s8 g_fileState = 0;                                    // 0 unknown, 1 present, -1 missing / invalid
StreamsHeader g_header;

SeqEntry* Seq(Stream& s) { return (SeqEntry*)s.meta; }
FrameEntry* Frames(Stream& s) { return (FrameEntry*)(s.meta + s.seqCount * sizeof(SeqEntry)); }

bool Read(u32 offset, void* dst, u32 size) {
    return w2u::ReadDataFromFileAt(STREAMS_PATH, offset, size, (u8*)dst);
}

bool HaveFile() {
    if (g_fileState == 0) {
        g_fileState = Read(0, &g_header, sizeof(g_header)) && g_header.magic == STREAMS_MAGIC &&
                      g_header.version == 1 ? 1 : -1;
    }
    return g_fileState > 0;
}

// Binary search of the sorted index in the ROM file (a sprite load reads about log2(entries) entries).
bool FindEntry(u16 arc, u32 sheet, IndexEntry& out) {
    if (!HaveFile()) return false;
    u32 lo = 0, hi = g_header.entryCount;
    while (lo < hi) {
        u32 mid = (lo + hi) >> 1;
        IndexEntry e;
        if (!Read(g_header.entriesOffset + mid * sizeof(IndexEntry), &e, sizeof(e))) return false;
        if (e.arc == arc && e.sheetFile == sheet) { out = e; return true; }
        if (e.arc < arc || (e.arc == arc && e.sheetFile < sheet)) lo = mid + 1;
        else hi = mid;
    }
    return false;
}

void Free(Stream& s) {
    if (!s.active) return;
    s.active = 0; s.pending = 0; s.palettePending = 0; s.indepPending = 0; s.role = 0; s.indepBmp = nullptr;
    if (s.meta) GFL_HeapFree(s.meta);
    if (s.lz) GFL_HeapFree(s.lz);
    if (s.staging) GFL_HeapFree(s.staging);
    s.meta = s.lz = s.staging = nullptr;
    bool any = false;
    for (auto& o : g_streams) any |= o.active != 0;
    if (!any && g_vblankTask) { GFL_TCBRemove(g_vblankTask); g_vblankTask = nullptr; }
}

// While an upload runs, texture / palette VRAM is mapped to the CPU and the 3D engine reads nothing from it. The 3D
// engine starts drawing the next frame at about scanline 214, so every upload has to end before then: one that ends
// later blanks every textured polygon (sprites, battle background) for a frame. Measured in battle: a TEX4 frame costs
// about 9 scanlines per 96 rows (one call per row), and three 96-row sprites changing frame in the same VBlank ended at
// line 218. An upload that would not end by UPLOAD_LAST_LINE waits for the next VBlank (its sprite's frame shows 1/60 s
// later; its timeline waits too).
constexpr u32 UPLOAD_LAST_LINE = 211;
inline u32 VCount() { return *(volatile u16*)0x04000006; }
inline bool UploadFits(u32 lines) { return VCount() + lines <= UPLOAD_LAST_LINE; }
inline u32 StreamUploadLines(const Stream& s) {
    return (s.flags & MANI_TEX4) ? s.boxH * 3u / 32u + 1u : s.boxH * A3I5_ROW_BYTES / 4096u + 1u;
}

void VBlankUpload(void*, void*) {
    u16 vcount = *(volatile u16*)0x04000006;
    if (vcount < 0xC0 || vcount > 0xC8) return;        // like MCSS's own upload: only at the start of VBlank
    bool begun = false;
    for (auto& s : g_streams) {
        if (!s.active || !s.pending) continue;
        if (!UploadFits(StreamUploadLines(s))) continue;
        if (!begun) { gfxBeginTextureUpload(); begun = true; }
        const u32 tex = SysTexBase(s.sys) + s.slot * SLOT_TEX_BYTES;
        if (s.flags & MANI_TEX4) {
            // the native 256-texel rows: only the part the sprite's cells show is replaced
            for (u32 y = 0; y < s.boxH; ++y)
                gfxUploadTexture(s.staging + y * s.rowBytes, tex + y * NATIVE_ROW_BYTES, s.rowBytes);
        } else {
            gfxUploadTexture(s.staging, tex, s.boxH * A3I5_ROW_BYTES);
            if (!s.formatSet) { SprSetA3I5(s.spr); s.formatSet = 1; }
        }
        s.pending = 0;
    }
    for (auto& s : g_streams) {                        // evolution: the morph renderer's bitmap
        if (!s.active || !s.indepPending || !s.indepBmp) continue;
        if (!UploadFits(0x2000 / 4096 + 1)) continue;
        if (!begun) { gfxBeginTextureUpload(); begun = true; }
        gfxUploadTexture(s.indepBmp, s.indepTex, 0x2000);
        s.indepPending = 0;
    }
    if (begun) gfxEndTextureUpload();
    begun = false;
    for (auto& s : g_streams) {
        if (!s.active || !s.palettePending) continue;
        if (!UploadFits(1)) continue;
        if (!begun) { gfxBeginPaletteUpload(); begun = true; }
        gfxUploadPalette(s.palette, SysPalBase(s.sys) + s.slot * SLOT_PAL_BYTES, sizeof(s.palette));
        s.palettePending = 0;
    }
    if (begun) gfxEndPaletteUpload();
}

// Decompress unique frame `u` into staging and hand it to the next VBlank.
void Prepare(Stream& s, u16 u) {
    FrameEntry fe = Frames(s)[u];
    if (!Read(s.mani + fe.offset, s.lz, fe.size)) { s.shown = u; return; }   // keep the last frame
    sys_uncomp_lz1x(s.lz, s.staging);
    cp15_flushDC(s.staging, s.boxH * s.rowBytes);
    s.shown = u;
    s.pending = 1;
}

// MCSS's texture upload task (ARM9 0x201B788, a VBlank TCB made by LoadMCSSGraphicsData; sprite +0 = its handle) copies
// its work's character data (+0x00 NNSG2dCharacterData: +0x14 pRawData, linear 256-texel 4 bpp rows) and palette
// (+0x04 NNSG2dPaletteData: +0x0C pRawData) to the slot's VRAM. Writing frame 0 and the stream's palette there first
// means the carrier's own (often older) art never reaches the screen. The work is found from the task: the pointer in
// it whose +0x20 / +0x24 are this system / sprite.
u8* McssUploadWork(void* sys, u8* spr) {
    u32* tcb = (u32*)SprUploadTask(spr);
    if (!tcb || (u32)tcb < 0x02000000 || (u32)tcb >= 0x02400000) return nullptr;
    for (u32 i = 0; i < 12; ++i) {
        u8* w = (u8*)tcb[i];
        if ((u32)w >= 0x02000000 && (u32)w < 0x023FFFD0 && (((u32)w) & 3) == 0 &&
            *(void**)(w + 0x20) == sys && *(u8**)(w + 0x24) == spr)
            return w;
    }
    return nullptr;
}

bool Prime(Stream& s) {
    u8* work = McssUploadWork(s.sys, s.spr);
    u8* chr = work ? *(u8**)work : nullptr;
    u8* raw = chr ? *(u8**)(chr + 0x14) : nullptr;
    if (!raw || *(u32*)(chr + 0x10) < (u32)(s.boxH - 1) * NATIVE_ROW_BYTES + s.rowBytes) return false;
    const u16 u = Seq(s)[0].unique;
    FrameEntry fe = Frames(s)[u];
    if (!Read(s.mani + fe.offset, s.lz, fe.size)) return false;
    sys_uncomp_lz1x(s.lz, s.staging);
    for (u32 y = 0; y < s.boxH; ++y) {
        u8* dst = raw + y * NATIVE_ROW_BYTES;
        const u8* src = s.staging + y * s.rowBytes;
        for (u32 x = 0; x < s.rowBytes; ++x) dst[x] = src[x];
    }
    cp15_flushDC(raw, s.boxH * NATIVE_ROW_BYTES);
    if (s.flags & MANI_OWN_PALETTES) {
        u8* pal = *(u8**)(work + 4);
        u16* palRaw = pal ? *(u16**)(pal + 0x0C) : nullptr;
        if (palRaw) { for (u32 i = 0; i < 16; ++i) palRaw[i] = s.palette[i]; cp15_flushDC(palRaw, sizeof(s.palette)); }
        u32 n = SprPaletteSize(s.spr) < sizeof(s.palette) ? SprPaletteSize(s.spr) : sizeof(s.palette);
        for (u32 i = 0; i < n / 2; ++i) {             // MCSS's own copies: its fades start from them
            if (SprPaletteOrig(s.spr)) SprPaletteOrig(s.spr)[i] = s.palette[i];
            if (SprPaletteWork(s.spr)) SprPaletteWork(s.spr)[i] = s.palette[i];
        }
    }
    s.shown = u;
    return true;
}

void Register(void* sys, int slot, const IndexEntry& entry, bool shiny) {
    Stream* s = nullptr;
    for (auto& o : g_streams) if (!o.active) { s = &o; break; }
    if (!s) return;
    ManiHeader h;
    if (!Read(entry.maniOffset, &h, sizeof(h)) || h.magic != MANI_MAGIC || !h.seqCount || !h.uniqueCount ||
        h.boxH > 128 || h.boxW > ((h.flags & MANI_TEX4) ? 256 : 128))
        return;
    u8* spr = SysSprite(sys, slot);
    const u16 heap = SprHeap(spr);
    const u32 seqBytes = h.seqCount * sizeof(SeqEntry), metaSize = seqBytes + h.uniqueCount * sizeof(FrameEntry);
    s->flags = h.flags;
    s->boxW = h.boxW; s->boxH = h.boxH; s->seqCount = h.seqCount; s->uniqueCount = h.uniqueCount;
    s->rowBytes = (h.flags & MANI_TEX4) ? (u16)(h.boxW / 2) : (u16)A3I5_ROW_BYTES;
    s->meta = (u8*)GFL_HeapAllocate(heap, metaSize, 0, "w2anim", __LINE__);
    if (!s->meta) return;
    if (!Read(entry.maniOffset + h.seqOffset, s->meta, seqBytes) ||
        !Read(entry.maniOffset + h.framesOffset, s->meta + seqBytes, h.uniqueCount * sizeof(FrameEntry))) {
        GFL_HeapFree(s->meta); s->meta = nullptr; return;
    }
    if (h.flags & MANI_OWN_PALETTES) {
        Read(entry.maniOffset + h.paletteOffset + (shiny ? sizeof(s->palette) : 0), s->palette, sizeof(s->palette));
    }
    u32 maxBlob = 0;
    FrameEntry* frames = (FrameEntry*)(s->meta + seqBytes);
    for (u32 i = 0; i < h.uniqueCount; ++i) if (frames[i].size > maxBlob) maxBlob = frames[i].size;
    s->lz = (u8*)GFL_HeapAllocate(heap, (maxBlob + 3) & ~3u, 0, "w2anim", __LINE__);
    s->staging = (u8*)GFL_HeapAllocate(heap, h.boxH * s->rowBytes, 0, "w2anim", __LINE__);
    if (!s->lz || !s->staging) {
        if (s->lz) GFL_HeapFree(s->lz);
        if (s->staging) GFL_HeapFree(s->staging);
        GFL_HeapFree(s->meta);
        s->meta = s->lz = s->staging = nullptr;
        return;
    }
    s->sys = sys; s->spr = spr; s->slot = slot; s->mani = entry.maniOffset;
    s->seqPos = 0; s->elapsed = 0; s->pending = 0; s->palettePending = 0; s->started = 0; s->formatSet = 0;
    s->role = 0; s->indepPending = 0; s->indepShown = 0xFFFF; s->indepBmp = nullptr; s->indepTex = 0;
    s->shown = 0xFFFF;
    s->primed = (h.flags & MANI_TEX4) && Prime(*s);
    s->active = 1;
    if (!g_vblankTask) g_vblankTask = GFL_VBlankTCBAdd(VBlankUpload, nullptr, 0);
}

// a slot is gone when MCSS no longer lists our sprite there
bool SlotGone(Stream& s) { return s.slot >= SysCount(s.sys) || SysSprite(s.sys, s.slot) != s.spr; }

void Tick(void* sys, bool firstFrameOnly = false) {
    for (auto& s : g_streams) {
        if (!s.active || s.sys != sys) continue;
        if (SlotGone(s)) { Free(s); continue; }
        if (s.pending) continue;                       // previous frame not uploaded yet
        if (!s.started) {
            if (SprUploadTask(s.spr)) continue;        // MCSS is still uploading its own texture
            s.started = 1;
            if (s.primed) continue;                    // frame 0 and the palette came with MCSS's own upload
            if (s.flags & MANI_OWN_PALETTES) {         // MCSS's buffers first: its fades / flashes start from them
                u32 n = SprPaletteSize(s.spr) < sizeof(s.palette) ? SprPaletteSize(s.spr) : sizeof(s.palette);
                for (u32 i = 0; i < n / 2; ++i) {
                    if (SprPaletteOrig(s.spr)) SprPaletteOrig(s.spr)[i] = s.palette[i];
                    if (SprPaletteWork(s.spr)) SprPaletteWork(s.spr)[i] = s.palette[i];
                }
                cp15_flushDC(s.palette, sizeof(s.palette));
                s.palettePending = 1;
            }
            Prepare(s, Seq(s)[0].unique);
            continue;
        }
        if (SprAnimPaused(s.spr) || firstFrameOnly) continue;
        // time in 1/60000 s: one 60 fps tick is 1000 at the normal MCSS speed (fx32 4096); a duration is ms (x 60)
        // or 1/60 s ticks (x 1000)
        const s32 unit = (s.flags & MANI_TICKS) ? 1000 : 60;
        s.elapsed += (SprAnimSpeed(s.spr) * 1000) >> 12;
        u32 pos = s.seqPos;
        for (u32 guard = 0; Seq(s)[pos].duration && s.elapsed >= (s32)Seq(s)[pos].duration * unit &&
                            guard < s.seqCount; ++guard) {
            s.elapsed -= (s32)Seq(s)[pos].duration * unit;
            pos = pos + 1 < s.seqCount ? pos + 1 : 0;
        }
        s.seqPos = pos;
        if (Seq(s)[pos].unique != s.shown) Prepare(s, Seq(s)[pos].unique);
    }
}

// ---- evolution (ov284): the morph renderer ------------------------------------------------------------------
// Its work (+0x58) holds a manager with the two Pokemon (+0x08 before, +0x0C after); each has a GFL bitmap
// (+0x10 -> +0x00: 128x128 4 bpp, 64 bytes a row, high nibble = left pixel) uploaded to texture VRAM +0x14, and a
// palette (+0x2C current 16 colours, faded towards +0x4C at rate +0x56 / 31) - the layout PWAN's evolution runtime
// documented. The 96x96 frame sits at (16, 16).
constexpr u32 EVO_WORK_MORPH = 0x58, MORPH_POKE[2] = { 0x08, 0x0C };
constexpr u32 POKE_BMP = 0x10, POKE_TEX = 0x14, POKE_PAL = 0x2C, POKE_FADE_COLOR = 0x4C, POKE_FADE_RATE = 0x56;
constexpr u32 MORPH_SIDE = 128, MORPH_ROW_BYTES = MORPH_SIDE / 2, MORPH_ORIGIN = 16;

bool InMainRam(const void* p) { u32 a = (u32)p; return a >= 0x02000000 && a < 0x02400000; }

u16 Fade(u16 c, u16 to, s32 rate) {
    if (rate <= 0) return c;
    if (rate >= 31) return to;
    s32 out = 0;
    for (int sh = 0; sh < 15; sh += 5) {
        s32 a = (c >> sh) & 31, b = (to >> sh) & 31;
        out |= ((a + (((b - a) * rate) >> 5)) & 31) << sh;
    }
    return (u16)out;
}

void MorphUpdate(void* work) {
    u8* mgr = InMainRam(work) ? *(u8**)((u8*)work + EVO_WORK_MORPH) : nullptr;
    if (!InMainRam(mgr)) return;
    for (u32 r = 0; r < 2; ++r) {
        u8* poke = *(u8**)(mgr + MORPH_POKE[r]);
        Stream* s = nullptr;
        for (auto& o : g_streams) if (o.active && o.role == r + 1 && o.started && o.shown != 0xFFFF) { s = &o; break; }
        if (!s || !InMainRam(poke) || !(s->flags & MANI_TEX4)) continue;
        if (s->flags & MANI_OWN_PALETTES) {            // the renderer's fade, applied to the stream's palette
            u16* pal = (u16*)(poke + POKE_PAL);
            const u16 to = *(u16*)(poke + POKE_FADE_COLOR);
            const s32 rate = *(s16*)(poke + POKE_FADE_RATE);
            for (u32 i = 1; i < 16; ++i) pal[i] = Fade(s->palette[i], to, rate);
        }
        u8* bmpObj = *(u8**)(poke + POKE_BMP);
        u8* bmp = InMainRam(bmpObj) ? *(u8**)bmpObj : nullptr;
        if (!InMainRam(bmp) || (s->indepShown == s->shown && s->indepBmp == bmp)) continue;
        // the stream's staging holds its current frame (96 rows of 48 bytes, low nibble = left pixel)
        for (u32 y = 0; y < MORPH_SIDE; ++y) {
            u8* row = bmp + y * MORPH_ROW_BYTES;
            const bool inside = y >= MORPH_ORIGIN && y < MORPH_ORIGIN + s->boxH;
            for (u32 x = 0; x < MORPH_ROW_BYTES; ++x) {
                const u32 sx = x - MORPH_ORIGIN / 2;
                u8 v = 0;
                if (inside && x >= MORPH_ORIGIN / 2 && sx < s->rowBytes) {
                    v = s->staging[(y - MORPH_ORIGIN) * s->rowBytes + sx];
                    v = (u8)((v << 4) | (v >> 4));
                }
                row[x] = v;
            }
        }
        cp15_flushDC(bmp, MORPH_SIDE * MORPH_ROW_BYTES);
        s->indepBmp = bmp; s->indepTex = *(u32*)(poke + POKE_TEX); s->indepShown = s->shown; s->indepPending = 1;
    }
}

void TagEvolution(void* spr, u8 role) {
    for (auto& s : g_streams) if (s.active && s.spr == spr) s.role = role;
}

typedef void* (*AddPokeMcssFn)(void* sys, const void* pp, int dir, s32 x, s32 y, s32 z);
typedef void (*EvoWorkFn)(void* work);
AddPokeMcssFn const AddPokeMcss = (AddPokeMcssFn)0x0201C179;        // ARM9: MCSS sprite of a Pokemon param
EvoWorkFn const MorphMain = (EvoWorkFn)0x021E57A1, MorphDraw = (EvoWorkFn)0x021E5801;   // ov284
u8 g_evoAdds = 0;

// LoadMCSSGraphicsData(sys, slot, params): params = {arc, ncbr, nclr, ncer, nanr, nmcr, nmar, ncec, heap flag}.
void LoadAndRegister(void* sys, int slot, u32* params) {
    for (auto& s : g_streams)
        if (s.active && s.sys == sys && s.slot == (u32)slot) Free(s);   // the slot is reloaded
    IndexEntry entry;
    const bool found = params[0] <= 0xFFFF && FindEntry((u16)params[0], params[1], entry);
    if (found && (entry.flags & ENTRY_CARRIER)) {
        const u32 b = entry.shinyNclrFile;             // the carrier block's first file: its front set
        u32 carrier[9] = { ARC_POKEGRA, b + 2, b + 18, b + 4, b + 5, b + 6, b + 7, b + 8, params[8] };
        LoadMCSSGraphicsData(sys, slot, carrier);
    } else {
        LoadMCSSGraphicsData(sys, slot, params);
    }
    if (found) Register(sys, slot, entry, !(entry.flags & ENTRY_CARRIER) && params[2] == entry.shinyNclrFile);
}

} // namespace

// --- hooks --------------------------------------------------------------------------------------------------
// The three calls of LoadMCSSGraphicsData(sys, slot, params) (ARM9 0x2019C32, 0x201AA84, 0x201AFBE).
extern "C" void THUMB_BRANCH_LINK_ARM9_0x2019C32(void* sys, int slot, u32* params) { LoadAndRegister(sys, slot, params); }
extern "C" void THUMB_BRANCH_LINK_ARM9_0x201AA84(void* sys, int slot, u32* params) { LoadAndRegister(sys, slot, params); }
extern "C" void THUMB_BRANCH_LINK_ARM9_0x201AFBE(void* sys, int slot, u32* params) { LoadAndRegister(sys, slot, params); }

// MCSS_DelSprite(sys, spr) +0x8: bl MCSS_FreeSpriteResources(spr) - also reached from MCSS_Exit.
extern "C" void THUMB_BRANCH_LINK_ARM9_0x201AAB4(void* spr) {
    for (auto& s : g_streams) if (s.active && s.spr == spr) Free(s);
    MCSS_FreeSpriteResources(spr);
}

// Every caller of MCSS_Main (one per screen that draws MCSS sprites): tick the streams right after MCSS's own
// animations. Found by scanning White 2's ARM9 and decompressed overlays for BLs to 0x2019B14.
#define W2ANIM_MCSS_MAIN_CALLER(name)                                                                          \
    extern "C" void name(void* sys) { MCSS_Main(sys); Tick(sys); }
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_168_0x21E692C)   // battle
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_194_0x21BBC20)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_207_0x21B3384)   // summary
extern "C" void THUMB_BRANCH_LINK_265_0x2199EF6(void* sys) { MCSS_Main(sys); Tick(sys, true); }   // Hall of Fame
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_284_0x21E51B0)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_294_0x21A3662)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_298_0x21A80BC)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_307_0x21DEE3E)

// Evolution (ov284): the scene adds the Pokemon before, then after (a loop of two calls), or only the one after.
extern "C" void* THUMB_BRANCH_LINK_284_0x21E5364(void* sys, const void* pp, int dir, s32 x, s32 y, s32 z) {
    void* spr = AddPokeMcss(sys, pp, dir, x, y, z);
    TagEvolution(spr, (g_evoAdds++ & 1) ? 2 : 1);
    return spr;
}
extern "C" void* THUMB_BRANCH_LINK_284_0x21E53AE(void* sys, const void* pp, int dir, s32 x, s32 y, s32 z) {
    void* spr = AddPokeMcss(sys, pp, dir, x, y, z);
    TagEvolution(spr, 2);
    return spr;
}
// The morph renderer's update and draw: the streams' frames and palettes go into its bitmaps after its own update and
// again right before it draws (its fade changes the palette every frame).
extern "C" void THUMB_BRANCH_LINK_284_0x21E51B6(void* work) { MorphMain(work); MorphUpdate(work); }
extern "C" void THUMB_BRANCH_LINK_284_0x21E51D8(void* work) { MorphUpdate(work); MorphDraw(work); }
