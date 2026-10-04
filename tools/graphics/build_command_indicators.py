#!/usr/bin/env python3
"""Command-screen weather / terrain indicators (battgra a/0/1/1 members 420-423 and 941).

Merged from MegaB2W2 (scripts/data/steps/step_75_weather_panel.py, step_76_terrain_panel.py,
scripts/build/gen_terrain_panel.py) and replaces the static terrain icons of build_terrain_indicator.py.

The retail command screen shows a WEATHER panel: cell-animation sequence weather + 0xE of the battle input sprite
set (sun 0xF, rain 0x10, hail 0x11, sand 0x12), each frame = the shared "WEATHER" label (tiles 67 / 71, palette 7)
plus a 40x24 box (OAMs 32x16, 8x16, 32x8, 8x8 = 15 tiles). This tool adds:

  - strong-weather icons (Delta Stream winds, Primordial Sea heavy rain, Desolate Land harsh sun), animated, drawn
    over the hail icon's box with palette 5 (heavy rain / harsh sun colours go into its unused slots 9-11 / 13-15);
  - an animated TERRAIN panel (label + box) per terrain, palette 15.

Sprite VRAM is tight on the command screen (the Double Battle party icons share it), so the sheet holds one slot
per indicator instead of every frame: a 3-frame weather slot and a 2-frame terrain slot (+ the 5 TERRAIN label
tiles). w2u_terrain_indicator.cpp copies the current strong weather's / terrain's frames (and the terrain palette)
from member 941 into those slots when the panel appears.

Sequences: 0x13 strong winds (weather value 5), 21 heavy rain, 22 extreme sun, 23 terrain (must match
src/pokeweb_gameplay/w2u_terrain_indicator.cpp). Member 941 layout: weather frames [kind 0-2][frame 0-2][480 B],
terrain frames [terrain 0-3][frame 0-1][480 B], terrain palettes [terrain 0-3][16 x u16].
"""
from __future__ import annotations

import argparse
import math
import struct
from pathlib import Path

from PIL import Image

SEQ_BASE = 0xE
LABEL_TILES = (67, 71)
BOX_W, BOX_H = 40, 24
BOX_OAMS = ((-16, 5, 1, 2), (16, 5, 2, 0), (-16, 21, 1, 1), (16, 21, 0, 0))   # (x, y, shape, size)
SIZES = {(0, 0): (8, 8), (0, 1): (16, 16), (0, 2): (32, 32), (0, 3): (64, 64),
         (1, 0): (16, 8), (1, 1): (32, 8), (1, 2): (32, 16), (1, 3): (64, 32),
         (2, 0): (8, 16), (2, 1): (8, 32), (2, 2): (16, 32), (2, 3): (32, 64)}
FRAME_TILES = 15
FRAME_BYTES = FRAME_TILES * 32
HAIL_CELL = 19

WEATHER_PAL = 5
WEATHER_SLOT_FRAMES = 3
WEATHER_SEQS = (0x13, 21, 22)          # winds (weather 5), heavy rain, extreme sun
WEATHER_NEW_COLORS = {9: (32, 48, 96), 10: (56, 88, 144), 11: (152, 184, 224),    # heavy rain
                      13: (200, 56, 16), 14: (248, 128, 32), 15: (248, 216, 88)}  # extreme sun
WEATHERS = (  # kind, colours (bg, mid, light, white), shifts, frame duration
    ("winds", (7, 6, 8, 2), (0, 4), 12),
    ("heavy_rain", (9, 10, 11, 2), (0, 3, 6), 8),
    ("extreme_sun", (13, 14, 15, 2), (0, 1), 12),
)

TERRAIN_PAL = 15
TERRAIN_SEQ = 23
TERRAIN_FRAMES = 2
TERRAIN_DURATION = 14
TERRAINS = ("electric", "grassy", "misty", "psychic")
OUTLINE, WHITE = (32, 32, 32), (240, 240, 248)
TERRAIN_COLORS = {   # palette 15: 0 transparent, 1 outline, 2 white, 3 bg, 4 mid, 5 light, 6 accent
    "electric": [(40, 40, 96), (248, 200, 32), (248, 248, 152), (120, 168, 248)],
    "grassy": [(40, 104, 48), (80, 160, 56), (152, 216, 88), (232, 240, 136)],
    "misty": [(200, 96, 160), (232, 152, 200), (248, 200, 232), (248, 240, 248)],
    "psychic": [(72, 32, 120), (144, 72, 184), (208, 136, 232), (248, 192, 248)],
}
BG, MID, LIGHT, ACCENT, W = 3, 4, 5, 6, 2
ART_MEMBER = 941


# ---------------------------------------------------------------------------------------------- Nitro files
def chunks(data: bytes) -> list[bytearray]:
    out, offset = [], 0x10
    while offset < len(data):
        size = struct.unpack_from("<I", data, offset + 4)[0]
        out.append(bytearray(data[offset:offset + size]))
        offset += size
    return out


def join(data: bytes, parts: list[bytearray]) -> bytes:
    body = b"".join(bytes(p) for p in parts)
    header = bytearray(data[:0x10])
    struct.pack_into("<I", header, 8, 0x10 + len(body))
    struct.pack_into("<H", header, 0xE, len(parts))
    return bytes(header) + body


def ncgr_tiles(ncgr: bytes) -> bytes:
    rahc = chunks(ncgr)[0]
    if rahc[:4] != b"RAHC":
        raise ValueError("member 420 is not the expected NCGR")
    size = struct.unpack_from("<I", rahc, 0x18)[0]
    return bytes(rahc[0x20:0x20 + size])


def append_tiles(ncgr: bytes, data: bytes) -> tuple[bytes, int]:
    parts = chunks(ncgr)
    rahc = parts[0]
    first = struct.unpack_from("<I", rahc, 0x18)[0] // 32
    rahc += data
    struct.pack_into("<I", rahc, 4, len(rahc))
    struct.pack_into("<I", rahc, 0x18, struct.unpack_from("<I", rahc, 0x18)[0] + len(data))
    return join(ncgr, parts), first


def ncer_cells(ncer: bytes) -> list[list[tuple[int, int, int, int, int, int]]]:
    kbec = chunks(ncer)[0]
    n, attr, coff = struct.unpack_from("<HHI", kbec, 8)
    if attr & 1:
        raise ValueError("cells with bounding boxes are not supported")
    base = 8 + coff + n * 8
    cells = []
    for c in range(n):
        count, _, off = struct.unpack_from("<HHI", kbec, 8 + coff + c * 8)
        oams = []
        for k in range(count):
            a0, a1, a2 = struct.unpack_from("<HHH", kbec, base + off + 6 * k)
            y = a0 & 0xFF
            y = y - 256 if y > 127 else y
            x = a1 & 0x1FF
            x = x - 512 if x > 255 else x
            oams.append((x, y, a0 >> 14, a1 >> 14, a2 & 0x3FF, a2 >> 12))
        cells.append(oams)
    return cells


def append_cells(ncer: bytes, new_cells: list) -> tuple[bytes, int]:
    parts = chunks(ncer)
    kbec = parts[0]
    n, attr, coff = struct.unpack_from("<HHI", kbec, 8)
    table = bytes(kbec[8 + coff:8 + coff + n * 8])
    oam_start = 8 + coff + n * 8
    oam_end = max(struct.unpack_from("<I", table, i * 8 + 4)[0] + 6 * struct.unpack_from("<H", table, i * 8)[0]
                  for i in range(n))
    oams = bytes(kbec[oam_start:oam_start + oam_end])
    for cell in new_cells:
        entry = b"".join(struct.pack("<HHH", (y & 0xFF) | (shape << 14), (x & 0x1FF) | (size << 14),
                                     tile | (pal << 12)) for x, y, shape, size, tile, pal in cell)
        table += struct.pack("<HHI", len(cell), 0, len(oams))
        oams += entry
    block = bytearray(kbec[:8 + coff]) + table + oams
    while len(block) % 4:
        block += b"\0"
    struct.pack_into("<H", block, 8, n + len(new_cells))
    struct.pack_into("<I", block, 4, len(block))
    parts[0] = block
    return join(ncer, parts), n


def ensure_sequence(nanr: bytes, seq: int, template_seq: int = 0x13) -> bytes:
    parts = chunks(nanr)
    knba = parts[0]
    nseq, nfr, soff, foff, eoff = struct.unpack_from("<HHIII", knba, 8)
    if seq < nseq:
        return nanr
    seqs = bytearray(knba[8 + soff:8 + foff])
    template = seqs[template_seq * 16:template_seq * 16 + 16]
    grow = (seq + 1 - nseq) * 16
    seqs += template * (seq + 1 - nseq)
    header = bytearray(knba[:8 + soff])
    struct.pack_into("<HHIII", header, 8, seq + 1, nfr, soff, foff + grow, eoff + grow)
    block = header + seqs + knba[8 + foff:]
    while len(block) % 4:
        block += b"\0"
    struct.pack_into("<I", block, 4, len(block))
    parts[0] = block
    return join(nanr, parts)


def set_sequence(nanr: bytes, seq: int, cells_and_durations: list[tuple[int, int]]) -> bytes:
    parts = chunks(nanr)
    knba = parts[0]
    nseq, nfr, soff, foff, eoff = struct.unpack_from("<HHIII", knba, 8)
    seqs = bytearray(knba[8 + soff:8 + foff])
    frames = bytearray(knba[8 + foff:8 + eoff])
    elems = bytearray(knba[8 + eoff:])
    s = seq * 16
    if struct.unpack_from("<H", seqs, s + 4)[0] != 0:
        raise ValueError(f"sequence {seq} must use index elements")
    first_frame = len(frames)
    for cell, duration in cells_and_durations:
        while len(elems) % 4:
            elems += b"\0"
        frames += struct.pack("<IHH", len(elems), duration, 0xBEEF)
        elems += struct.pack("<HH", cell, 0xCCCC)
    struct.pack_into("<HH", seqs, s, len(cells_and_durations), 0)
    struct.pack_into("<I", seqs, s + 12, first_frame)
    header = bytearray(knba[:8 + soff])
    struct.pack_into("<HHIII", header, 8, nseq, nfr + len(cells_and_durations), soff, soff + len(seqs),
                     soff + len(seqs) + len(frames))
    block = header + seqs + frames + elems
    while len(block) % 4:
        block += b"\0"
    struct.pack_into("<I", block, 4, len(block))
    parts[0] = block
    return join(nanr, parts)


def nclr_colors(nclr: bytes) -> list[int]:
    ttlp = chunks(nclr)[0]
    size = struct.unpack_from("<I", ttlp, 0x10)[0]
    return list(struct.unpack_from(f"<{size // 2}H", ttlp, 0x18))


def nclr_replace(nclr: bytes, colors: list[int]) -> bytes:
    parts = chunks(nclr)
    ttlp = parts[0]
    struct.pack_into(f"<{len(colors)}H", ttlp, 0x18, *colors)
    return join(nclr, parts)


def bgr555(rgb: tuple[int, int, int]) -> int:
    r, g, b = (c >> 3 for c in rgb)
    return r | (g << 5) | (b << 10)


def rgb(color: int) -> tuple[int, int, int]:
    return ((color & 31) << 3, ((color >> 5) & 31) << 3, ((color >> 10) & 31) << 3)


def encode_4bpp_tiled(px: list[list[int]]) -> bytes:
    out = bytearray()
    for ty in range(len(px) // 8):
        for tx in range(len(px[0]) // 8):
            for y in range(8):
                row = px[ty * 8 + y][tx * 8:tx * 8 + 8]
                out += bytes(row[i] | (row[i + 1] << 4) for i in range(0, 8, 2))
    return bytes(out)


# ---------------------------------------------------------------------------------------------- art
def box_from_cell(cell, tiles: bytes) -> list[list[int]]:
    px = [[0] * BOX_W for _ in range(BOX_H)]
    for x, y, shape, size, t, _pal in cell:
        if t in LABEL_TILES:
            continue
        w, h = SIZES[(shape, size)]
        for ty in range(h // 8):
            for tx in range(w // 8):
                for py in range(8):
                    for qx in range(8):
                        b = tiles[t * 32 + py * 4 + qx // 2]
                        px[y - 5 + ty * 8 + py][x + 16 + tx * 8 + qx] = (b >> 4) if qx & 1 else b & 15
                t += 1
    return px


def box_tiles(px: list[list[int]]) -> bytes:
    out = bytearray()
    for x, y, shape, size in BOX_OAMS:
        w, h = SIZES[(shape, size)]
        out += encode_4bpp_tiled([[px[y - 5 + yy][x + 16 + xx] for xx in range(w)] for yy in range(h)])
    return bytes(out)


def interior(frame):
    px = [row[:] for row in frame]
    inside = {(x, y) for y in range(BOX_H) for x in range(BOX_W) if px[y][x] not in (0, 1)}
    return px, inside


def wind_frame(frame, shift, bg, mid, light, white):
    px, inside = interior(frame)
    for x, y in inside:
        px[y][x] = bg
    for row, x0, length, phase in ((5, 2, 24, 0.0), (11, 10, 22, 2.0), (16, 4, 20, 4.0)):
        pts = [((x0 + i + shift) % 36 + 1, row + int(round(math.sin((i + phase + shift) / 3.2) * 1.2)))
               for i in range(length)]
        for i, (x, y) in enumerate(pts):
            if (x, y) not in inside:
                continue
            px[y][x] = white if i > length * 0.55 else light
            if 0 < i < length - 1 and (x, y + 1) in inside and px[y + 1][x] == bg:
                px[y + 1][x] = mid
        hx, hy = pts[-1]
        for dx, dy in ((1, -1), (2, -1), (2, 0), (2, 1), (1, 1), (0, 1)):
            if (hx + dx, hy + dy) in inside:
                px[hy + dy][hx + dx] = white
    return px


def rain_frame(frame, shift, bg, mid, light, white):
    px, inside = interior(frame)
    for x, y in inside:
        px[y][x] = bg
    for k, x0 in enumerate(range(-12, 40, 5)):
        start = (k * 7 + shift) % 11
        for top in range(start - 11, BOX_H, 11):
            for i in range(6):
                y = top + i
                x = x0 + y * 2 // 3
                if (x, y) in inside:
                    px[y][x] = light if i >= 2 else mid
    for k in range(5):
        x, y = (k * 9 + shift * 3) % 34 + 3, 19 + (k % 2)
        if (x, y) in inside:
            px[y][x] = white
    return px


def sun_frame(frame, shift, bg, mid, light, white):
    px, inside = interior(frame)
    for x, y in inside:
        px[y][x] = bg
    cx, cy = 20, 11
    reach = 10 + shift * 2
    for a in range(16):
        angle = a * math.pi / 8 + shift * math.pi / 16
        length = reach if a % 2 == 0 else reach - 4
        for r in range(6, length):
            x, y = int(round(cx + math.cos(angle) * r * 1.3)), int(round(cy + math.sin(angle) * r))
            if (x, y) in inside:
                px[y][x] = mid if r > length - 3 else light
    for y in range(BOX_H):
        for x in range(BOX_W):
            d = ((x - cx) / 1.3) ** 2 + (y - cy) ** 2
            if (x, y) in inside and d <= 30:
                px[y][x] = white if d <= 9 else light
    return px


WEATHER_DRAW = {"winds": wind_frame, "heavy_rain": rain_frame, "extreme_sun": sun_frame}


def plot(px, inside, x, y, c):
    if (x, y) in inside:
        px[y][x] = c


def line(px, inside, p0, p1, c):
    (x0, y0), (x1, y1) = p0, p1
    n = max(abs(x1 - x0), abs(y1 - y0), 1)
    for i in range(n + 1):
        plot(px, inside, round(x0 + (x1 - x0) * i / n), round(y0 + (y1 - y0) * i / n), c)


def terrain_base(frame):
    px, inside = interior(frame)
    for x, y in inside:
        px[y][x] = BG
    return px, inside


def electric(frame, k):
    px, inside = terrain_base(frame)
    for x0, flip in ([(7, 0), (19, 1), (31, 0)] if k == 0 else [(12, 1), (26, 0)]):
        s = -1 if flip else 1
        pts = [(x0, 1), (x0 - 3 * s, 8), (x0 + 1 * s, 9), (x0 - 4 * s, 19)]
        for a, b in zip(pts, pts[1:]):
            line(px, inside, (a[0] + 1, a[1]), (b[0] + 1, b[1]), MID)
            line(px, inside, a, b, LIGHT)
    for x, y in ([(3, 17), (15, 4), (24, 15), (35, 6)] if k == 0 else [(5, 6), (20, 17), (33, 14), (17, 9)]):
        plot(px, inside, x, y, W)
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            plot(px, inside, x + dx, y + dy, ACCENT)
    return px


def grassy(frame, k):
    px, inside = terrain_base(frame)
    for i, x in enumerate(range(2, 37, 3)):
        h = 7 + (i * 5) % 6
        lean = 1 if (i + k) % 2 else -1
        for d in range(h):
            y = 20 - d
            xx = x + (lean if d > h * 0.6 else 0)
            plot(px, inside, xx, y, LIGHT if d >= h - 2 else MID)
            if d < h // 2:
                plot(px, inside, xx + 1, y, MID)
    for x, y in ((6, 6), (22, 4), (31, 8)) if k == 0 else ((10, 5), (26, 7), (35, 4)):
        plot(px, inside, x, y, ACCENT)
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            plot(px, inside, x + dx, y + dy, W)
    return px


def misty(frame, k):
    px, inside = terrain_base(frame)
    for row, phase in ((5, 0.0), (11, 2.1), (17, 4.2)):
        for x in range(0, 40):
            y = row + round(math.sin((x + phase * 3 + k * 4) / 4.0) * 1.5)
            plot(px, inside, x, y, LIGHT)
            plot(px, inside, x, y + 1, MID)
    for x, y in ((8, 8), (27, 14), (17, 2)) if k == 0 else ((12, 14), (31, 8), (4, 3)):
        plot(px, inside, x, y, W)
    return px


def psychic(frame, k):
    px, inside = terrain_base(frame)
    cx, cy = 18.5, 10.5
    for x, y in inside:
        d = math.hypot((x - cx) / 1.6, y - cy) - k * 2.5
        r = d % 5.0
        if r < 1.0:
            px[y][x] = LIGHT if int(d // 5) % 2 == 0 else MID
        elif r < 1.8:
            px[y][x] = MID
    plot(px, inside, 18, 10, W)
    plot(px, inside, 19, 10, ACCENT)
    return px


TERRAIN_DRAW = {"electric": electric, "grassy": grassy, "misty": misty, "psychic": psychic}


def label_tiles(tiles: bytes) -> tuple[bytes, list[list[int]]]:
    """"TERRAIN" in the WEATHER label's font (tiles 67-70 32x8 + 71 8x8, palette 7): T, E, R, A copied from
    W E A T H E R, I = E's stem, N = H's strokes + a diagonal, on the label's own dark bar."""
    def tile(n):
        return [[(tiles[n * 32 + y * 4 + x // 2] >> 4) if x & 1 else (tiles[n * 32 + y * 4 + x // 2] & 15)
                 for x in range(8)] for y in range(8)]
    src = [sum((tile(n)[y] for n in (67, 68, 69, 70, 71)), []) for y in range(8)]
    out = [row[:] for row in src]
    for y in range(1, 6):
        for x in range(1, 37):
            if out[y][x] in (2, 3, 4):
                out[y][x] = 1
    cols = {"W": (2, 6), "E": (8, 10), "A": (12, 15), "T": (17, 21), "H": (23, 26), "R": (32, 35)}

    def glyph(ch):
        if ch == "I":
            return [[src[y][8]] for y in range(1, 6)]
        if ch == "N":
            a, _b = cols["H"]
            g = [[0] * 4 for _ in range(5)]
            for r in range(5):
                g[r][0] = g[r][3] = src[r + 1][a]
            for r, c in ((1, 1), (2, 1), (2, 2), (3, 2)):
                g[r][c] = src[r + 1][a]
            return g
        a, b = cols[ch]
        return [[src[y][x] if src[y][x] in (2, 3, 4) else 0 for x in range(a, b + 1)] for y in range(1, 6)]

    word = [glyph(c) for c in "TERRAIN"]
    width = sum(len(g[0]) for g in word) + len(word) - 1
    x = 2 + (35 - width) // 2
    for g in word:
        for r in range(5):
            for c, v in enumerate(g[r]):
                if v:
                    out[1 + r][x + c] = v
        x += len(g[0]) + 1
    data = b""
    for t in range(5):
        for y in range(8):
            row = out[y][t * 8:t * 8 + 8]
            data += bytes((row[i] | (row[i + 1] << 4)) for i in range(0, 8, 2))
    return data, out


# ---------------------------------------------------------------------------------------------- build
def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[2])
    args = parser.parse_args()
    root = args.root.resolve()
    base_dir = root / "assets/terrain_indicator/base"
    out_dir = root / "data/graphics/battle"
    preview_dir = root / "assets/terrain_indicator/preview"
    ncgr, nclr, ncer, nanr = ((base_dir / str(m)).read_bytes() for m in (420, 421, 422, 423))
    if struct.unpack_from("<H", chunks(ncer)[0], 8)[0] != 23 or struct.unpack_from("<H", chunks(nanr)[0], 8)[0] != 21:
        raise ValueError("expected the retail battle input sprite set (23 cells, 21 sequences)")

    tiles = ncgr_tiles(ncgr)
    cells = ncer_cells(ncer)
    hail = cells[HAIL_CELL]
    frame = box_from_cell(hail, tiles)
    weather_label = [o for o in hail if o[4] in LABEL_TILES]
    colors = nclr_colors(nclr)
    for slot, color in WEATHER_NEW_COLORS.items():
        index = WEATHER_PAL * 16 + slot
        if colors[index] != 0:
            raise ValueError(f"palette {WEATHER_PAL} slot {slot} is in use")
        colors[index] = bgr555(color)

    # art: weather frames [kind][slot frame], terrain frames [terrain][frame] + palettes
    art = bytearray()
    previews: dict[str, list[Image.Image]] = {}
    for kind, (bg, mid, light, white), shifts, _duration in WEATHERS:
        frames = [WEATHER_DRAW[kind](frame, s, bg, mid, light, white) for s in shifts]
        for k in range(WEATHER_SLOT_FRAMES):
            art += box_tiles(frames[min(k, len(frames) - 1)])
        previews[kind] = [preview_box(f, [rgb(c) for c in colors[WEATHER_PAL * 16:WEATHER_PAL * 16 + 16]])
                          for f in frames]
    label, label_px = label_tiles(tiles)
    terrain_palettes = b""
    for name in TERRAINS:
        pal = [(0, 0, 0), OUTLINE, WHITE] + TERRAIN_COLORS[name] + [(0, 0, 0)] * 9
        terrain_palettes += b"".join(struct.pack("<H", bgr555(c)) for c in pal)
        frames = [TERRAIN_DRAW[name](frame, k) for k in range(TERRAIN_FRAMES)]
        for f in frames:
            art += box_tiles(f)
        label_colors = [rgb(c) for c in colors[7 * 16:7 * 16 + 16]]
        previews[name] = [preview_terrain(f, pal, label_px, label_colors) for f in frames]
    art += terrain_palettes

    # sheet: weather slot (3 frames, the winds art as placeholder), TERRAIN label, terrain slot (2 frames, electric)
    slot_art = art[:WEATHER_SLOT_FRAMES * FRAME_BYTES]
    terrain_art = art[3 * WEATHER_SLOT_FRAMES * FRAME_BYTES:3 * WEATHER_SLOT_FRAMES * FRAME_BYTES + TERRAIN_FRAMES * FRAME_BYTES]
    ncgr_out, weather_tile = append_tiles(ncgr, bytes(slot_art) + label + bytes(terrain_art))
    label_tile = weather_tile + WEATHER_SLOT_FRAMES * FRAME_TILES
    terrain_tile = label_tile + 5                     # the TERRAIN label: 32x8 + 8x8 = 5 tiles

    new_cells = []
    for k in range(WEATHER_SLOT_FRAMES):
        t = weather_tile + k * FRAME_TILES
        box = []
        for x, y, shape, size in BOX_OAMS:
            box.append((x, y, shape, size, t, WEATHER_PAL))
            w, h = SIZES[(shape, size)]
            t += w * h // 64
        new_cells.append(box + weather_label)
    terrain_label = [(-16, -4, 1, 1, label_tile, 7), (16, -4, 0, 0, label_tile + 4, 7)]
    for k in range(TERRAIN_FRAMES):
        t = terrain_tile + k * FRAME_TILES
        box = []
        for x, y, shape, size in BOX_OAMS:
            box.append((x, y, shape, size, t, TERRAIN_PAL))
            w, h = SIZES[(shape, size)]
            t += w * h // 64
        new_cells.append(box + terrain_label)
    ncer_out, first_cell = append_cells(ncer, new_cells)
    nanr_out = nanr
    for seq in WEATHER_SEQS + (TERRAIN_SEQ,):
        nanr_out = ensure_sequence(nanr_out, seq)
    for seq, (_kind, _colors, shifts, duration) in zip(WEATHER_SEQS, WEATHERS):
        nanr_out = set_sequence(nanr_out, seq, [(first_cell + k, duration) for k in range(len(shifts))])
    nanr_out = set_sequence(nanr_out, TERRAIN_SEQ,
                            [(first_cell + WEATHER_SLOT_FRAMES + k, TERRAIN_DURATION) for k in range(TERRAIN_FRAMES)])
    colors[TERRAIN_PAL * 16:TERRAIN_PAL * 16 + 16] = list(struct.unpack_from("<16H", terrain_palettes, 0))
    nclr_out = nclr_replace(nclr, colors)

    out_dir.mkdir(parents=True, exist_ok=True)
    for member, data in ((420, ncgr_out), (421, nclr_out), (422, ncer_out), (423, nanr_out), (ART_MEMBER, bytes(art))):
        (out_dir / str(member)).write_bytes(data)
    preview_dir.mkdir(parents=True, exist_ok=True)
    for old in preview_dir.glob("*.png"):
        old.unlink()
    for name, images in previews.items():
        sheet = Image.new("RGBA", (len(images) * 44, images[0].height), (200, 32, 40, 255))
        for i, im in enumerate(images):
            sheet.paste(im, (i * 44, 0))
        sheet.resize((sheet.width * 4, sheet.height * 4), Image.Resampling.NEAREST).save(preview_dir / f"{name}.png")
    end_tile = terrain_tile + TERRAIN_FRAMES * FRAME_TILES
    print(f"command indicators: weather slot tiles {weather_tile}-{label_tile - 1}, label {label_tile}-"
          f"{label_tile + 4}, terrain slot {terrain_tile}-{end_tile - 1}; cells {first_cell}-"
          f"{first_cell + len(new_cells) - 1}; sequences {', '.join(str(s) for s in WEATHER_SEQS)} weather, "
          f"{TERRAIN_SEQ} terrain; art member {ART_MEMBER} ({len(art)} bytes)")


def preview_box(px, palette):
    im = Image.new("RGBA", (BOX_W, BOX_H), (200, 32, 40, 255))
    for y in range(BOX_H):
        for x in range(BOX_W):
            if px[y][x]:
                im.putpixel((x, y), palette[px[y][x]] + (255,))
    return im


def preview_terrain(px, palette, label_px, label_colors):
    im = Image.new("RGBA", (BOX_W, BOX_H + 10), (200, 32, 40, 255))
    for y in range(8):
        for x in range(BOX_W):
            if label_px[y][x]:
                im.putpixel((x, y), label_colors[label_px[y][x]] + (255,))
    for y in range(BOX_H):
        for x in range(BOX_W):
            if px[y][x]:
                im.putpixel((x, y + 9), palette[px[y][x]] + (255,))
    return im


if __name__ == "__main__":
    main()
