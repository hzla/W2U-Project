"""A3I5 battle sprites in the W2U build (docs/megab2w2-integration.md, "A3I5 sprites").

Most W2U sprites stream as TEX4 (the PWAN's 96x96 4 bpp frames in the carrier set's texture). A side listed with
format "a3i5" in data/graphics/w2anim/sprites.toml streams its full-size art instead: 128x128 A3I5 texture (8 bpp,
index | alpha << 5, all 16 palette entries real colours), drawn through one quad covering its box.

Source MANI (committed, data/graphics/w2anim/a3i5/*.mani; written by tools/w2anim/import_a3i5_sources.py from the
original GIFs, which are not committed): MANI v2, flags own palettes | morph (A3I5), one sequence entry per source
frame with the source duration in ms, and in the morph block x0 = box left - canvas centre, y0 = -box height (the box
standing on the ground point, before placement). The build (build_w2anim_streams.py) turns it into the streamed MANI:
the side's timing spec applied to the durations, and its placement (see place()) written into the morph block; and it
writes the block's cell files so MCSS draws one quad of the box at that place.

MANI v2 (runtime: src/w2anim/w2u_anim_streams.cpp): 'MANI', u16 version 2, u16 flags (1 own palettes, 2 TEX4, 4 ticks,
8 morph block), u16 boxW, boxH, seqCount, uniqueCount, u32 seqOffset, framesOffset, paletteOffset; morph block at 0x1C
{s16 x0, y0, u8 map[16], u8 source[16]}; palettes 2 x 16 BGR555; seq {u16 unique, u16 duration}; frames {u32 offset,
u32 size} of LZ10 / LZ11 blobs of boxH rows of 128 bytes."""
from __future__ import annotations

import struct

MANI_OWN, MANI_TEX4, MANI_TICKS, MANI_MORPH = 1, 2, 4, 8
MANI_HEADER = struct.Struct("<4sHHHHHHIII")
MORPH = struct.Struct("<hh16s16s")
MORPH_OFFSET = 0x1C
ROW = 128
GROUND_ROW = 88                    # a PWAN carrier's ground point (canvas row; its frame is 96x96)
# The highest canvas row still on screen over a side's ground point (measured in battle, default camera: a foe's
# canvas row 0 is screen row 7, a player's back, drawn 2x, has row 0 at screen row 46), with a row to spare
SCREEN_TOP_ROW = {"front": -6, "back": -22}
MAX_SINK = 8                       # tall art sinks at most this far below its grounded place: where a PWAN stands
# A back left where its PWAN stood (grounding_back = "pwan") rises no higher than the 96x96 frame's top row, as far as a
# PWAN back could reach; taller art sinks as far as it must (a back's lower part is behind the text box anyway)
BACK_TOP_ROW = 0
OFFSET_LIMIT = 48                  # Pokeweb's PWAN side offset range (pwanAnimationModel.ts PWAN_MIN/MAX_OFFSET)
TEMPLATE_BLOCK = 11                # Metapod: a single-cell sprite whose animation files are reused (idle bob removed)
FILES_PER_SET = 20


# ---------------------------------------------------------------------------------------------------------- LZ11
def lz11_decompress(data: bytes) -> bytes:
    if data[0] != 0x11:
        raise ValueError("not LZ11")
    size = data[1] | data[2] << 8 | data[3] << 16
    pos = 4
    if not size:
        size, pos = struct.unpack_from("<I", data, 4)[0], 8
    out = bytearray()
    while len(out) < size:
        flags = data[pos]
        pos += 1
        for bit in range(8):
            if len(out) >= size:
                break
            if not flags & (0x80 >> bit):
                out.append(data[pos])
                pos += 1
                continue
            a, b = data[pos], data[pos + 1]
            pos += 2
            if a >> 4 == 0:
                c = data[pos]
                pos += 1
                count, disp = ((a & 15) << 4 | b >> 4) + 0x11, ((b & 15) << 8 | c) + 1
            elif a >> 4 == 1:
                c, d = data[pos], data[pos + 1]
                pos += 2
                count, disp = ((a & 15) << 12 | b << 4 | c >> 4) + 0x111, ((c & 15) << 8 | d) + 1
            else:
                count, disp = (a >> 4) + 1, ((a & 15) << 8 | b) + 1
            for _ in range(count):
                out.append(out[-disp])
    return bytes(out)


def lz11_compress(data: bytes) -> bytes:
    """Greedy LZ11 with hash chains on 3-byte prefixes (the game's decoder: sys_uncomp_lz1x)."""
    n = len(data)
    if 0 < n <= 0xFFFFFF:
        out = bytearray([0x11, n & 0xFF, n >> 8 & 0xFF, n >> 16 & 0xFF])
    else:                                          # size 0 means "a 32-bit size follows"
        out = bytearray([0x11, 0, 0, 0]) + struct.pack("<I", n)
    chains: dict[bytes, list[int]] = {}
    pos = 0
    while pos < n:
        flag_at = len(out)
        out.append(0)
        flags = 0
        for bit in range(8):
            if pos >= n:
                break
            best, disp = 0, 0
            for cand in reversed(chains.get(data[pos:pos + 3], [])[-64:]):
                if pos - cand > 0x1000:
                    break
                length = 0
                while length < 0x10110 and pos + length < n and data[cand + length] == data[pos + length]:
                    length += 1
                if length > best:
                    best, disp = length, pos - cand
            if best >= 3:
                flags |= 0x80 >> bit
                d = disp - 1
                if best <= 0x10:
                    out += bytes([(best - 1) << 4 | d >> 8, d & 0xFF])
                elif best <= 0x110:
                    v = best - 0x11
                    out += bytes([v >> 4, (v & 15) << 4 | d >> 8, d & 0xFF])
                else:
                    v = best - 0x111
                    out += bytes([0x10 | v >> 12, v >> 4 & 0xFF, (v & 15) << 4 | d >> 8, d & 0xFF])
                step = best
            else:
                out.append(data[pos])
                step = 1
            for k in range(step):
                if pos + k + 3 <= n:
                    chains.setdefault(data[pos + k:pos + k + 3], []).append(pos + k)
            pos += step
        out[flag_at] = flags
    while len(out) % 4:
        out.append(0)
    return bytes(out)


def decompress(blob: bytes) -> bytes:
    if blob[0] == 0x11:
        return lz11_decompress(blob)
    import ndspy.lz10
    return ndspy.lz10.decompress(blob)


# ---------------------------------------------------------------------------------------------------------- MANI
def parse_mani(data: bytes) -> dict:
    magic, version, flags, w, h, nseq, nuniq, seq_off, fr_off, pal_off = MANI_HEADER.unpack_from(data, 0)
    if magic != b"MANI" or version != 2 or flags & ~15 or (flags & MANI_TEX4) or not flags & MANI_MORPH:
        raise ValueError("not an A3I5 MANI with a morph block")
    x0, y0, mp, src = MORPH.unpack_from(data, MORPH_OFFSET)
    seq = [list(struct.unpack_from("<HH", data, seq_off + 4 * k)) for k in range(nseq)]
    blobs = []
    for k in range(nuniq):
        off, size = struct.unpack_from("<II", data, fr_off + 8 * k)
        blobs.append(data[off:off + size])
    pals = [list(struct.unpack_from("<16H", data, pal_off + 32 * s)) for s in (0, 1)] if flags & MANI_OWN else None
    return dict(flags=flags, w=w, h=h, seq=seq, blobs=blobs, palettes=pals, x0=x0, y0=y0, map=mp, source=src)


def write_mani(m: dict) -> bytes:
    seq = [s for s in m["seq"] if s[1] > 0]
    pal_off = MORPH_OFFSET + MORPH.size
    seq_off = pal_off + (64 if m["palettes"] else 0)
    fr_off = seq_off + 4 * len(seq)
    data_off = fr_off + 8 * len(m["blobs"])
    flags = MANI_MORPH | (MANI_OWN if m["palettes"] else 0)
    out = bytearray(MANI_HEADER.pack(b"MANI", 2, flags, m["w"], m["h"], len(seq), len(m["blobs"]), seq_off, fr_off,
                                     pal_off if m["palettes"] else 0))
    out += MORPH.pack(m["x0"], m["y0"], bytes(m["map"]), bytes(m["source"]))
    if m["palettes"]:
        out += struct.pack("<16H", *m["palettes"][0]) + struct.pack("<16H", *m["palettes"][1])
    out += b"".join(struct.pack("<HH", u, min(d, 0xFFFF)) for u, d in seq)
    cursor = data_off
    table = bytearray()
    for b in m["blobs"]:
        table += struct.pack("<II", cursor, len(b))
        cursor = (cursor + len(b) + 3) & ~3
    out += table
    for b in m["blobs"]:
        out += b
        out += bytes(-len(out) % 4)
    return bytes(out)


def frame_rows(m: dict, unique: int) -> bytes:
    rows = decompress(m["blobs"][unique])
    if len(rows) != m["h"] * ROW:
        raise ValueError("frame size")
    return rows


# ---------------------------------------------------------------------------------------------------------- timing
def timed(durations: list[int], spec: dict) -> list[int]:
    """w2anim's timing options (MegaB2W2 tools/w2anim core/timing.py), applied in this order:
      ms: [..]        one duration per source frame (0 = leave the frame out)
      even: true      normalisation: every frame the same time, the loop length kept
      loop_ms: n      normalisation: durations scaled so the loop lasts n ms
      min_ms: n       normalisation: frames shorter than n ms raised to n
      frame_ms: n     every frame n ms
      scale: x        every duration times x
      hold: {i: ms}   frame i (0-based) gets ms
    An empty spec keeps the source timing."""
    d = list(durations)
    if "ms" in spec:
        if len(spec["ms"]) != len(d):
            raise ValueError(f"timing.ms: {len(spec['ms'])} durations for {len(d)} frames")
        d = [int(x) for x in spec["ms"]]
    live = [x for x in d if x > 0]
    if spec.get("even") and live:
        each = max(1, round(sum(live) / len(live)))
        d = [each if x > 0 else 0 for x in d]
    if spec.get("loop_ms") and live:
        total = sum(d)
        d = [max(1, round(x * spec["loop_ms"] / total)) if x > 0 else 0 for x in d]
    if spec.get("min_ms"):
        d = [max(x, int(spec["min_ms"])) if x > 0 else 0 for x in d]
    if "frame_ms" in spec:
        d = [int(spec["frame_ms"])] * len(d)
    if "scale" in spec:
        d = [round(x * float(spec["scale"])) for x in d]
    for i, ms in (spec.get("hold") or {}).items():
        if not 0 <= int(i) < len(d):
            raise ValueError(f"timing.hold: frame {i} of {len(d)}")
        d[int(i)] = int(ms)
    if any(x < 0 for x in d) or sum(d) <= 0:
        raise ValueError(f"timing: bad durations {d}")
    return d


# ---------------------------------------------------------------------------------------------------------- placement
def check_offset(offset) -> tuple[int, int]:
    dx, dy = (int(v) for v in (offset or (0, 0)))
    if not (-OFFSET_LIMIT <= dx <= OFFSET_LIMIT and -OFFSET_LIMIT <= dy <= OFFSET_LIMIT):
        raise ValueError(f"offset {dx}, {dy} outside +-{OFFSET_LIMIT}")
    return dx, dy


def place(m: dict, pwan_bottom: int | None, altitude: int, offset, top_row: int | None = None,
          max_sink: int | None = MAX_SINK) -> tuple[int, int]:
    """The box's top-left relative to the sprite's ground point (y down). The box's bottom stands where the side's
    PWAN stood (its lowest opaque row over all frames, relative to the carrier's ground row 88; none: on the ground
    point), raised by `altitude`, then moved by the manual offset correction (Pokeweb's per-side offset: px, +x right,
    +y down) - the same correction a PWAN side gets, without the 96x96 clip. top_row: art taller than the screen allows
    above the ground point sinks until its top is on that canvas row, by at most max_sink (MAX_SINK: no lower than
    its PWAN stood, taller art keeps its top cut by the screen; None: as far as needed), before the manual offset."""
    dx, dy = check_offset(offset)
    sink = (pwan_bottom - GROUND_ROW) if pwan_bottom else 0
    y0 = m["y0"] + sink - int(altitude)
    if top_row is not None:
        need = top_row - GROUND_ROW - y0
        y0 += max(0, need if max_sink is None else min(need, max_sink))
    return m["x0"] + dx, y0 + dy


# ---------------------------------------------------------------------------------------------------------- block files
def _ncgr_data_offset(ncgr: bytes) -> int:
    if ncgr[:4] != b"RGCN":
        raise ValueError("not an NCGR")
    return 0x10 + 8 + struct.unpack_from("<I", ncgr, 0x10 + 0x1C)[0]


_OAM_SHAPES = {(8, 8): (0, 0), (16, 16): (0, 1), (32, 32): (0, 2), (64, 64): (0, 3), (16, 8): (1, 0), (32, 8): (1, 1),
               (32, 16): (1, 2), (64, 32): (1, 3), (8, 16): (2, 0), (8, 32): (2, 1), (16, 32): (2, 2), (32, 64): (2, 3)}


def _pieces(w: int, h: int) -> list[tuple[int, int, int, int]]:
    """Cover a w x h box (multiples of 8) with OAM-valid rectangles (the NCER describes the cell; MCSS draws the
    record's quad)."""
    def sizes(n):
        out = []
        for s in (64, 32, 16, 8):
            while n >= s:
                out.append(s)
                n -= s
        return out
    res, y = [], 0
    for ph in sizes(h):
        x = 0
        for pw in sizes(w):
            todo = [(x, y, pw, ph)]
            while todo:
                px, py, a, b = todo.pop()
                if (a, b) in _OAM_SHAPES:
                    res.append((px, py, a, b))
                elif a > b:
                    todo += [(px, py, a // 2, b), (px + a // 2, py, a // 2, b)]
                else:
                    todo += [(px, py, a, b // 2), (px, py + b // 2, a, b // 2)]
            x += pw
        y += ph
    return res


def _ncer(w: int, h: int) -> bytes:
    cw, ch = -(-w // 8) * 8, -(-h // 8) * 8
    oams = b"".join(struct.pack("<HHH", (py & 0xFF) | _OAM_SHAPES[(pw, ph)][0] << 14,
                                (px & 0x1FF) | _OAM_SHAPES[(pw, ph)][1] << 14, (py // 8) * 32 + px // 8)
                    for px, py, pw, ph in _pieces(cw, ch))
    kbec = struct.pack("<HHIIIII", 1, 0, 0x18, 4, 0, 0, 0)[:0x18] + \
        struct.pack("<HHI", len(oams) // 6, min(63, max(cw, ch) // 2), 0) + oams
    kbec += bytes(-len(kbec) % 4)
    kbec = b"KBEC" + struct.pack("<I", 8 + len(kbec)) + kbec
    ncer = bytearray(b"RECN" + struct.pack("<HHIHH", 0xFEFF, 0x0100, 0, 0x10, 1)) + kbec
    struct.pack_into("<I", ncer, 8, len(ncer))
    return bytes(ncer)


def _still_nanr(nanr_lz: bytes) -> bytes:
    """The template's NANR with every keyframe at identity (no idle bob: the stream animates)."""
    out = bytearray(lz11_decompress(nanr_lz))
    if out[:4] != b"RNAN":
        raise ValueError("not an NANR")
    d = 0x18
    na, _, ao, fo, ko = struct.unpack_from("<HHIII", out, d)
    for a in range(na):
        cnt, _, etype, _, foff = struct.unpack_from("<IHHII", out, d + ao + 16 * a)
        for i in range(cnt):
            e = d + ko + struct.unpack_from("<I", out, d + fo + foff + 8 * i)[0]
            if etype == 1:
                struct.pack_into("<Hiihh", out, e + 2, 0, 4096, 4096, 0, 0)
            elif etype == 2:
                struct.pack_into("<hh", out, e + 4, 0, 0)
    return lz11_compress(bytes(out))


def _zeroed_nmcr(nmcr: bytes) -> bytes:
    out = bytearray(nmcr)
    hio = 0x18 + struct.unpack_from("<I", out, 0x20)[0]
    node = hio + struct.unpack_from("<I", out, 0x18 + struct.unpack_from("<I", out, 0x1C)[0] + 4)[0]
    struct.pack_into("<hh", out, node + 2, 0, 0)
    return bytes(out)


def template(member) -> dict:
    """The single-cell template block's files; member(n) -> bytes of a/0/0/4 member n."""
    t = TEMPLATE_BLOCK * FILES_PER_SET
    return {"sheet": lz11_decompress(member(t + 2)), "ncer": member(t + 4), "nanr": _still_nanr(member(t + 5)),
            "nmcr": _zeroed_nmcr(member(t + 6)), "nmar": member(t + 7), "record": member(t + 8)}


def block_files(m: dict, x0: int, y0: int, tpl: dict) -> dict[int, bytes]:
    """Side files (offsets within the side: sheet 2, NCER 4, NANR 5, NMCR 6, NMAR 7, record 8) drawing one quad of the
    box with its top-left at (x0, y0) from the ground point. The 4 bpp sheet holds the first frame (index 0
    transparent there); the runtime primes the texture with the A3I5 frame before MCSS's upload."""
    w, h = m["w"], m["h"]
    rows = frame_rows(m, m["seq"][0][0])
    sheet_px = bytearray(256 * 128 // 2)
    for y in range(h):
        for x in range(0, w, 2):
            a = rows[y * ROW + x]
            b = rows[y * ROW + x + 1] if x + 1 < w else 0
            lo = a & 15 if a >> 5 else 0
            hi = b & 15 if b >> 5 else 0
            sheet_px[y * 128 + x // 2] = lo | hi << 4
    sheet = bytearray(tpl["sheet"])
    off = _ncgr_data_offset(sheet)
    sheet[off:off + len(sheet_px)] = sheet_px
    rec = bytearray(tpl["record"])
    struct.pack_into("<HH", rec, 4, w, h)
    struct.pack_into("<6i", rec, 0xC, x0 * 256, -y0 * 256, w << 12, h << 12, 0, 0)
    rec[0x24:0x3C] = bytes(0x18)
    return {2: lz11_compress(bytes(sheet)), 4: _ncer(w, h), 5: tpl["nanr"], 6: tpl["nmcr"], 7: tpl["nmar"], 8: bytes(rec)}


def build(source: bytes, timing_spec: dict, pwan_bottom: int | None, altitude: int, offset, tpl: dict,
          top_row: int | None = None, max_sink: int | None = MAX_SINK):
    """Source MANI + the side's settings -> (streamed MANI, side files, info)."""
    m = parse_mani(source)
    durations = timed([d for _, d in m["seq"]], timing_spec or {})
    m["seq"] = [[u, d] for (u, _), d in zip(m["seq"], durations)]
    x0, y0 = place(m, pwan_bottom, altitude, offset, top_row, max_sink)
    m["x0"], m["y0"] = x0, y0
    data = write_mani(m)
    files = block_files(m, x0, y0, tpl)
    max_blob = max(len(b) for b in m["blobs"])
    payload = len([s for s in m["seq"] if s[1]]) * 4 + len(m["blobs"]) * 8 + ((max_blob + 3) & ~3) + m["h"] * ROW
    return data, files, {"w": m["w"], "h": m["h"], "x0": x0, "y0": y0, "ms": sum(durations), "payload": payload}
