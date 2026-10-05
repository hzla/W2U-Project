// w2anim sprite streams: animated MCSS sprites (Pokemon and trainers, every screen that uses MCSS), frames streamed
// from one ROM file into the sprite's texture. Replaces the PWAN runtimes (docs/megab2w2-integration.md, Phase 4).
// Ported from MegaB2W2's AnimSprites (tools/w2anim), generalised:
//  - any MCSS system: registration at MCSS's three LoadMCSSGraphicsData calls (ARM9), the tick at every caller of
//    MCSS_Main (battle, summary, evolution, egg hatch, ...), release at MCSS_DelSprite (also reached from MCSS_Exit);
//  - the index is read from the ROM when a sprite loads (no table in RAM): sorted {arc, sheet file} -> stream;
//  - two texture modes: TEX4 (the sprite keeps its native 4 bpp texture, palette and cells: each frame overwrites
//    the rows its cells show - W2U's carrier sets) and A3I5 (MegaB2W2: the proxy switched to 128x128 A3I5);
//  - frame durations in ms or in 1/60 s ticks;
//  - all buffers on the sprite's own game heap: nothing in PMC's heap but this code.
//
// File `w2anim/streams.bin` (tools/w2anim/build_w2anim_streams.py):
//   header  {'W2AS', u16 version 1, u16 reserved, u32 entryCount, u32 entriesOffset}
//   entries entryCount x {u16 arc, u16 flags, u32 sheetFile, u32 maniOffset, u32 shinyNclrFile} sorted by (arc, sheet)
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
    s.active = 0; s.pending = 0; s.palettePending = 0;
    if (s.meta) GFL_HeapFree(s.meta);
    if (s.lz) GFL_HeapFree(s.lz);
    if (s.staging) GFL_HeapFree(s.staging);
    s.meta = s.lz = s.staging = nullptr;
    bool any = false;
    for (auto& o : g_streams) any |= o.active != 0;
    if (!any && g_vblankTask) { GFL_TCBRemove(g_vblankTask); g_vblankTask = nullptr; }
}

void VBlankUpload(void*, void*) {
    u16 vcount = *(volatile u16*)0x04000006;
    if (vcount < 0xC0 || vcount > 0xC8) return;        // like MCSS's own upload: only at the start of VBlank
    bool begun = false;
    for (auto& s : g_streams) {
        if (!s.active || !s.pending) continue;
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
    if (begun) gfxEndTextureUpload();
    begun = false;
    for (auto& s : g_streams) {
        if (!s.active || !s.palettePending) continue;
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

void Register(void* sys, int slot, const u32* params) {
    for (auto& s : g_streams)
        if (s.active && s.sys == sys && s.slot == (u32)slot) Free(s);   // the slot was reloaded
    IndexEntry entry;
    if (params[0] > 0xFFFF || !FindEntry((u16)params[0], params[1], entry)) return;
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
        const bool shiny = params[2] == entry.shinyNclrFile;
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
    s->shown = 0xFFFF;
    s->active = 1;
    if (!g_vblankTask) g_vblankTask = GFL_VBlankTCBAdd(VBlankUpload, nullptr, 0);
}

// a slot is gone when MCSS no longer lists our sprite there
bool SlotGone(Stream& s) { return s.slot >= SysCount(s.sys) || SysSprite(s.sys, s.slot) != s.spr; }

void Tick(void* sys) {
    for (auto& s : g_streams) {
        if (!s.active || s.sys != sys) continue;
        if (SlotGone(s)) { Free(s); continue; }
        if (s.pending) continue;                       // previous frame not uploaded yet
        if (!s.started) {
            if (SprUploadTask(s.spr)) continue;        // MCSS is still uploading its own texture
            s.started = 1;
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
        if (SprAnimPaused(s.spr)) continue;
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

} // namespace

// --- hooks --------------------------------------------------------------------------------------------------
// The three calls of LoadMCSSGraphicsData(sys, slot, params) (ARM9 0x2019C32, 0x201AA84, 0x201AFBE).
extern "C" void THUMB_BRANCH_LINK_ARM9_0x2019C32(void* sys, int slot, u32* params) {
    LoadMCSSGraphicsData(sys, slot, params); Register(sys, slot, params);
}
extern "C" void THUMB_BRANCH_LINK_ARM9_0x201AA84(void* sys, int slot, u32* params) {
    LoadMCSSGraphicsData(sys, slot, params); Register(sys, slot, params);
}
extern "C" void THUMB_BRANCH_LINK_ARM9_0x201AFBE(void* sys, int slot, u32* params) {
    LoadMCSSGraphicsData(sys, slot, params); Register(sys, slot, params);
}

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
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_265_0x2199EF6)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_284_0x21E51B0)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_294_0x21A3662)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_298_0x21A80BC)
W2ANIM_MCSS_MAIN_CALLER(THUMB_BRANCH_LINK_307_0x21DEE3E)
