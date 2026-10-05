#!/usr/bin/env python3
"""Build w2anim/streams.bin, the w2anim runtime's animated sprites (src/w2anim/w2u_anim_streams.cpp), from W2U's
PWAN assets (assets/pokeweb_pwan: config.bin + NNN_front.pwan / NNN_back.pwan).

The stream of a config row goes to the sheet the game itself loads for that species / form: the block of W2U's
GetPokemonDataIDBase (src/pokedex_expansion/w2u_pokegra.cpp, ported in native_block below), which is a PWAN carrier set
(cells, NCGRs holding the first frame, normal / shiny NCLR 18 / 19) for every row. PWAN drew form 0 on that block as
well; for forms it switched MCSS to block asset * 20, which only differs for Zygarde forms 2 / 3 (identical blocks) and
Minior's meteor colours (same cells; the PWAN palette then comes with the stream). Rows whose block is not in the
built archive are reported and skipped. The runtime streams the remaining frames into the sprite's native 4 bpp texture
(MANI flag TEX4): the frame is un-tiled from PWAN's four OBJ regions into 96 rows of 48 bytes, the rows the carrier's
cells show. Durations stay PWAN's 1/60 s ticks (flag TICKS). A PWAN whose palette is not the set's normal NCLR (backs:
the carrier set holds the front's palette) carries its own palettes (flag OWN_PALETTES): its PWAN palette as normal,
and as shiny each colour mapped through the set's normal -> shiny NCLR pair (nearest normal colour).

Trainers (optional, --trainers; default assets/pokeweb_pwan/trainers when it exists): Pokeweb's trainer animation
format, a `PWNT` v1 config.bin ({u16 graphic, u16 asset} rows) and NNN.pwan per asset. A trainer graphic g (arc 71,
8 files) is indexed by its sheet g * 8 + 1 with the CARRIER flag: the runtime loads the front set of a Pokemon carrier
block instead (the most common carrier cell set among the indexed blocks), primes it with the trainer's frame 0 and
palette, and streams the rest. Trainer frames are moved up TRAINER_SHIFT rows: Pokeweb's trainer canvas stands on its
bottom row (96), a Pokemon carrier's ground point is canvas row 88.

Output layout: see the comment at the top of w2u_anim_streams.cpp. Sheets indexed: front 2 (+3 female when present),
back 11 (+12 female when present) of the block. Compressed MANIs are cached per PWAN file content in --cache.

usage: build_w2anim_streams.py --pwan assets/pokeweb_pwan --pokegra vfs/data/a/0/0/4 --personal vfs/data/a/0/1/6
                               --output vfs/data/w2anim/streams.bin
       [--cache DIR] [--stamp FILE] [--jobs N] [--report FILE]
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import struct
import sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from pwan_config import parse_config  # noqa: E402

ARC_POKEGRA = 4
ARC_TRAINER = 71
TRAINER_FILES = 8
TRAINER_SHIFT = 8
ENTRY_CARRIER = 1
FILES_PER_SET = 20
STREAMS_MAGIC = b"W2AS"
STREAMS_VERSION = 1
MANI_MAGIC = b"MANI"
MANI_VERSION = 2
MANI_OWN_PALETTES, MANI_TEX4, MANI_TICKS = 1, 2, 4
MANI_HEADER = struct.Struct("<4sHHHHHHIII")       # magic, version, flags, boxW, boxH, seqCount, uniqueCount,
                                                  # seqOffset, framesOffset, paletteOffset
INDEX_ENTRY = struct.Struct("<HHIII")             # arc, flags, sheetFile, maniOffset, shinyNclrFile
PWAN_HEADER = struct.Struct("<4sHHHHHHIIIIII")    # magic, version, width, height, bpp, frameCount, timelineCount,
                                                  # totalTicks, frameBytes, paletteColors, paletteOffset,
                                                  # timelineOffset, frameOffset
FRAME_W, FRAME_H, FRAME_BYTES = 96, 96, 0x1200
# w2u_pokegra.cpp
GEN7_START, GEN7_END, GEN7_BATTLE_START = 722, 809, 19000
GEN8_START, GEN8_END, GEN8_BATTLE_START = 810, 1023, 1200 * 20
FORM_START = 14480
ROW_BYTES = FRAME_W // 2
# PWAN's four OBJ-compatible regions: (byte offset, x, y, tiles wide, tiles high)
REGIONS = ((0x0000, 0, 0, 8, 8), (0x0800, 64, 0, 4, 8), (0x0C00, 0, 64, 8, 4), (0x1000, 64, 64, 4, 4))
CACHE_VERSION = b"w2anim-tex4-2"


def align4(n: int) -> int:
    return (n + 3) & ~3


def untile(frame: bytes) -> bytes:
    """PWAN frame (four tiled 4 bpp regions) -> 96 linear rows of 48 bytes (low nibble = left pixel, as both)."""
    out = bytearray(ROW_BYTES * FRAME_H)
    for base, x0, y0, tw, th in REGIONS:
        for ty in range(th):
            for tx in range(tw):
                tile = base + (ty * tw + tx) * 32
                for y in range(8):
                    row = (y0 + ty * 8 + y) * ROW_BYTES + (x0 + tx * 8) // 2
                    out[row:row + 4] = frame[tile + y * 4:tile + y * 4 + 4]
    return bytes(out)


def read_pwan(path: Path) -> tuple[list[int], list[tuple[int, int]], list[bytes]]:
    data = path.read_bytes()
    (magic, version, width, height, bpp, frame_count, timeline_count, _total, frame_bytes, colors, pal_off,
     tl_off, fr_off) = PWAN_HEADER.unpack_from(data, 0)
    if (magic, version, width, height, bpp, frame_bytes, colors) != (b"PWAN", 1, 96, 96, 4, FRAME_BYTES, 16):
        raise ValueError(f"{path}: unsupported PWAN header")
    palette = list(struct.unpack_from("<16H", data, pal_off))
    timeline = [struct.unpack_from("<HH", data, tl_off + 4 * i) for i in range(timeline_count)]
    frames = [data[fr_off + i * FRAME_BYTES:fr_off + (i + 1) * FRAME_BYTES] for i in range(frame_count)]
    for frame, ticks in timeline:
        if frame >= frame_count or not 0 < ticks <= 0xFFFF:
            raise ValueError(f"{path}: bad timeline entry {frame}, {ticks}")
    return palette, timeline, frames


def read_trainer_config(path: Path) -> list[tuple[int, int]]:
    """Pokeweb's trainer PWAN config (trainerPwanAnimationModel.ts): 'PWNT', u16 version 1, u16 count,
    u16 max timeline, u16 carrier graphic (Pokeweb's own carrier; not used here), u32 entries offset; {u16 graphic,
    u16 asset} rows."""
    data = path.read_bytes()
    magic, version, count, _max, _carrier, off = struct.unpack_from("<4sHHHHI", data, 0)
    if magic != b"PWNT" or version != 1:
        raise ValueError(f"{path}: not a PWNT v1 trainer config")
    return [struct.unpack_from("<HH", data, (off or 16) + 4 * i) for i in range(count)]


def carrier_block(pokegra: Path, blocks: list[int]) -> int:
    """The carrier for trainers: the lowest block with the most common front cell set (members 4-8)."""
    from collections import Counter
    def cells(b: int) -> bytes:
        return b"".join(hashlib.sha1((pokegra / str(b * FILES_PER_SET + k)).read_bytes()).digest() for k in range(4, 9))
    keyed = {b: cells(b) for b in sorted(set(blocks))}
    common = Counter(keyed.values()).most_common(1)[0][0]
    return min(b for b, k in keyed.items() if k == common)


def native_block(personal: Path, species: int, form: int) -> int:
    """The pokegra block (first file / 20) W2U's GetPokemonDataIDBase gives a species / form (not an egg)."""
    if GEN7_START <= species <= GEN7_END:
        first = GEN7_BATTLE_START + (species - GEN7_START) * FILES_PER_SET
    elif GEN8_START <= species <= GEN8_END:
        first = GEN8_BATTLE_START + (species - GEN8_START) * FILES_PER_SET
    else:
        first = species * FILES_PER_SET
    if form:
        record = (personal / str(species)).read_bytes()
        sprite_offset, form_count, sprite_forme = struct.unpack_from("<H", record, 0x1E)[0], record[0x20], record[0x21] & 0x80
        if form < form_count and not sprite_forme:
            first = FILES_PER_SET * (sprite_offset + form - 1) + FORM_START
    return first // FILES_PER_SET


def nclr_colors(path: Path) -> list[int]:
    data = path.read_bytes()
    k = data.find(b"TTLP")
    if k < 0:
        raise ValueError(f"{path}: no TTLP block")
    off = k + 8 + struct.unpack_from("<I", data, k + 8 + 12)[0]
    return list(struct.unpack_from("<16H", data, off))


def rgb(c: int) -> tuple[int, int, int]:
    return c & 31, (c >> 5) & 31, (c >> 10) & 31


def nearest(c: int, palette: list[int]) -> int:
    r, g, b = rgb(c)
    return min(range(1, 16), key=lambda i: (rgb(palette[i])[0] - r) ** 2 + (rgb(palette[i])[1] - g) ** 2
               + (rgb(palette[i])[2] - b) ** 2)


def shift_up(pixels: bytes, rows: int) -> bytes:
    return pixels[rows * ROW_BYTES:] + bytes(rows * ROW_BYTES) if rows else pixels


def build_mani(path: Path, normal: list[int] | None, shiny: list[int] | None, shift: int = 0) -> tuple[bytes, dict]:
    """normal / shiny None: a stream with its own palette only (trainers: the PWAN palette for both)."""
    import ndspy.lz10
    palette, timeline, frames = read_pwan(path)
    if normal is None:
        normal, shiny = list(palette), list(palette)
    own = palette[1:] != normal[1:] or shift != 0
    unique: dict[bytes, int] = {}
    blobs: list[bytes] = []
    seq: list[tuple[int, int]] = []
    linear = [shift_up(untile(f), shift) for f in frames]
    for frame, ticks in timeline:
        pixels = linear[frame]
        if pixels not in unique:
            unique[pixels] = len(blobs)
            blobs.append(ndspy.lz10.compress(pixels))
        seq.append((unique[pixels], ticks))
    flags = MANI_TEX4 | MANI_TICKS | (MANI_OWN_PALETTES if own else 0)
    seq_off = align4(MANI_HEADER.size)
    frames_off = seq_off + 4 * len(seq)
    pal_off = frames_off + 8 * len(blobs)
    data_off = pal_off + (64 if own else 0)
    out = bytearray(MANI_HEADER.pack(MANI_MAGIC, MANI_VERSION, flags, FRAME_W, FRAME_H, len(seq), len(blobs),
                                     seq_off, frames_off, pal_off if own else 0))
    out += bytes(seq_off - len(out))
    for u, ticks in seq:
        out += struct.pack("<HH", u, ticks)
    cursor = data_off
    table = bytearray()
    for blob in blobs:
        table += struct.pack("<II", cursor, len(blob))
        cursor = align4(cursor + len(blob))
    out += table
    if own:
        shiny_own = [shiny[0]] + [shiny[nearest(c, normal)] if c not in normal[1:] else shiny[normal.index(c, 1)]
                                  for c in palette[1:]]
        out += struct.pack("<16H", *([normal[0]] + palette[1:])) + struct.pack("<16H", *shiny_own)
    for blob in blobs:
        out += blob
        out += bytes(align4(len(out)) - len(out))
    info = {"steps": len(seq), "unique": len(blobs), "ownPalettes": own, "bytes": len(out)}
    return bytes(out), info


def cached_mani(job: tuple) -> tuple[bytes, dict]:
    path_s, normal, shiny, cache_dir, shift = job
    path = Path(path_s)
    key = hashlib.sha1(CACHE_VERSION + path.read_bytes() + struct.pack("<H", shift) +
                       (struct.pack("<32H", *normal, *shiny) if normal else b"own")).hexdigest()
    if cache_dir:
        cached = Path(cache_dir) / f"{key}.mani"
        meta = Path(cache_dir) / f"{key}.json"
        if cached.exists() and meta.exists():
            return cached.read_bytes(), json.loads(meta.read_text())
    data, info = build_mani(path, normal, shiny, shift)
    if cache_dir:
        Path(cache_dir).mkdir(parents=True, exist_ok=True)
        cached.write_bytes(data)
        meta.write_text(json.dumps(info))
    return data, info


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--pwan", type=Path, required=True)
    ap.add_argument("--pokegra", type=Path, required=True, help="the built a/0/0/4 folder (numbered members)")
    ap.add_argument("--personal", type=Path, required=True, help="the built a/0/1/6 folder (personal records)")
    ap.add_argument("--output", type=Path, required=True)
    ap.add_argument("--cache", type=Path)
    ap.add_argument("--stamp", type=Path)
    ap.add_argument("--report", type=Path)
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1)
    ap.add_argument("--trainers", type=Path, help="Pokeweb trainer animations (PWNT config.bin + NNN.pwan); default "
                    "assets/pokeweb_pwan/trainers when present")
    args = ap.parse_args()

    entries, _ = parse_config(args.pwan / "config.bin")
    jobs, sheets = [], []                 # sheets: (job index, [sheet files], shiny NCLR file)
    seen: set[tuple[int, int]] = set()
    skipped = []
    for (species, form), entry in sorted(entries.items()):
        asset = int(entry["assetIndex"])
        block = native_block(args.personal, species, form)
        for side, flag, sheet_off in (("front", 1, 2), ("back", 2, 11)):
            if not int(entry["flags"]) & flag:
                continue
            path = args.pwan / f"{asset}_{side}.pwan"
            if not path.exists():
                raise FileNotFoundError(path)
            base = block * FILES_PER_SET
            if not (args.pokegra / str(base + sheet_off)).exists():
                skipped.append({"species": species, "form": form, "asset": asset, "side": side, "block": block})
                continue
            if (block, sheet_off) in seen:
                raise ValueError(f"block {block} side {side}: two config rows")
            seen.add((block, sheet_off))
            normal = nclr_colors(args.pokegra / str(base + 18))
            shiny = nclr_colors(args.pokegra / str(base + 19))
            jobs.append((str(path), normal, shiny, str(args.cache) if args.cache else None, 0))
            files = [base + sheet_off]
            female = args.pokegra / str(base + sheet_off + 1)
            if female.exists() and female.stat().st_size:
                files.append(base + sheet_off + 1)
            sheets.append((len(jobs) - 1, files, base + 19, asset, side, species, form))

    trainers = args.trainers or (args.pwan / "trainers")
    trainer_rows = []
    if (trainers / "config.bin").exists():
        carrier = carrier_block(args.pokegra, [f[0] // FILES_PER_SET for _j, f, *_r in sheets if f[0] % FILES_PER_SET == 2])
        asset_job: dict[int, int] = {}                 # graphics sharing an asset share its stream
        for graphic, asset in read_trainer_config(trainers / "config.bin"):
            path = trainers / f"{asset}.pwan"
            if not path.exists():
                raise FileNotFoundError(path)
            if asset not in asset_job:
                jobs.append((str(path), None, None, str(args.cache) if args.cache else None, TRAINER_SHIFT))
                asset_job[asset] = len(jobs) - 1
            trainer_rows.append((asset_job[asset], graphic, asset, carrier))

    with ProcessPoolExecutor(max_workers=max(1, args.jobs)) as ex:
        results = list(ex.map(cached_mani, jobs, chunksize=8))

    index = []
    blobs_off = align4(16 + INDEX_ENTRY.size * (sum(len(s[1]) for s in sheets) + len(trainer_rows)))
    blob_offsets, cursor = [], blobs_off
    for data, _info in results:
        blob_offsets.append(cursor)
        cursor = align4(cursor + len(data))
    for job, files, shiny_file, *_ in sheets:
        for f in files:
            index.append((ARC_POKEGRA, 0, f, blob_offsets[job], shiny_file))
    for job, graphic, _asset, carrier in trainer_rows:
        index.append((ARC_TRAINER, ENTRY_CARRIER, graphic * TRAINER_FILES + 1, blob_offsets[job], carrier * FILES_PER_SET))
    index.sort(key=lambda e: (e[0], e[2]))
    keys = [(e[0], e[2]) for e in index]
    if len(set(keys)) != len(keys):
        raise ValueError("two streams for one sheet")

    out = bytearray(struct.pack("<4sHHII", STREAMS_MAGIC, STREAMS_VERSION, 0, len(index), 16))
    for e in index:
        out += INDEX_ENTRY.pack(*e)
    out += bytes(blobs_off - len(out))
    for data, _info in results:
        out += data
        out += bytes(align4(len(out)) - len(out))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    tmp = args.output.with_suffix(".tmp")
    tmp.write_bytes(bytes(out))
    os.replace(tmp, args.output)

    own = sum(1 for _d, info in results if info["ownPalettes"])
    if trainer_rows:
        print(f"[+] w2anim trainers: {len(trainer_rows)} graphics on carrier block {trainer_rows[0][3]}")
    print(f"[+] w2anim streams: {len(results)} animations, {len(index)} sheets, {own} with own palettes, "
          f"{len(out) / 1e6:.1f} MB -> {args.output}")
    for row in skipped:
        print(f"[!] no pokegra block {row['block']} for species {row['species']} form {row['form']} "
              f"({row['side']}, PWAN asset {row['asset']}): stays static")
    if args.report:
        report = {"streams": [{"species": sp, "form": fo, "asset": a, "side": s, "sheets": f, **results[j][1]}
                              for j, f, _sh, a, s, sp, fo in sheets], "skipped": skipped}
        args.report.write_text(json.dumps(report, indent=1))
    if args.stamp:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.write_text("ok\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
