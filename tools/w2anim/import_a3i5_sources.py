#!/usr/bin/env python3
"""Make the committed A3I5 source MANIs (data/graphics/w2anim/a3i5/*.mani) from the sprites' original GIFs.

Offline and only needed when a sprite is added or re-imported; the normal build reads the committed MANIs
(tools/w2anim/a3i5.py, build_w2anim_streams.py). The GIFs themselves are not committed: each format = "a3i5" side in
data/graphics/w2anim/sprites.toml names its source in [side.provenance] (url, sha256, shiny_url, shiny_sha256), and
this tool downloads it into --cache (work/w2anim_sources by default) and checks the hashes.

Per side: the frames as the GIF has them (canvas, durations: the build applies the side's timing spec), colours
reduced to 16 when there are more (normal and shiny kept index-aligned), the union box of all frames, own palettes
(normal + exact shiny), the evolution renderer's 16 -> 15 colour map, and x0 / y0 for the box standing on the ground
point at the canvas centre. Every frame is checked pixel-exact after a round trip through W2U's own decoder, and the
first frame is compared with the side's PWAN (silhouette after Pokeweb's fit into 96x96: a low match means another
art or the wrong sprite).

Uses w2anim (MegaB2W2/tools/w2anim, GPL-3.0-or-later) as an external package: --w2anim PATH or an installed w2anim.

usage: import_a3i5_sources.py [--only SPECIES[:FORM[:SIDE]]] [--w2anim PATH] [--cache DIR] [--offline]"""
from __future__ import annotations

import argparse
import hashlib
import sys
import tomllib
import urllib.request
from pathlib import Path

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(ROOT / "tools" / "pwan"))
import a3i5  # noqa: E402
from pwan_config import parse_config  # noqa: E402

SPRITES = ROOT / "data" / "graphics" / "w2anim" / "sprites.toml"
SOURCES = ROOT / "data" / "graphics" / "w2anim" / "a3i5"
PWAN = ROOT / "assets" / "pokeweb_pwan"
UA = {"User-Agent": "W2U-Project A3I5 sprite import (github.com/hzla/W2U-Project)"}


def fetch(url: str, sha: str | None, cache: Path, offline: bool) -> tuple[bytes, str]:
    name = hashlib.sha1(url.encode()).hexdigest()[:16] + "_" + url.rsplit("/", 1)[-1]
    path = cache / name
    if not path.exists():
        if offline:
            raise FileNotFoundError(f"{url}: not in {cache} (--offline)")
        cache.mkdir(parents=True, exist_ok=True)
        path.write_bytes(urllib.request.urlopen(urllib.request.Request(url, headers=UA), timeout=60).read())
    data = path.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if sha and sha != digest:
        raise ValueError(f"{url}: sha256 {digest} != the recorded {sha}")
    return data, digest


def morph_tables(frames, index_of) -> tuple[bytes, bytes]:
    """A3I5 index -> 4 bpp index 1..15 (with 16 colours the least-used one shares its nearest colour's index), and
    4 bpp index -> the A3I5 index whose colour it shows."""
    colours = {i: c for c, i in index_of.items()}
    use = dict.fromkeys(range(16), 0)
    for a, _ in frames:
        op = a[..., 3] > 127
        if op.any():
            cols, counts = np.unique(a[op][:, :3].reshape(-1, 3), axis=0, return_counts=True)
            for c, n in zip(cols.tolist(), counts.tolist()):
                use[index_of.get(tuple(c), 0)] += n
    used = sorted(colours)
    merged = None
    if len(used) == 16:
        m = min(used, key=lambda i: use[i])
        keep = [i for i in used if i != m]
        near = min(keep, key=lambda i: sum((x - y) ** 2 for x, y in zip(colours[i], colours[m])))
        merged = (m, near)
    else:
        keep = used
    mapping = {i: j for j, i in enumerate(keep, 1)}
    if merged:
        mapping[merged[0]] = mapping[merged[1]]
    mp = bytes(mapping.get(i, 1) for i in range(16))
    src = bytes([0] + [keep[j - 1] if j - 1 < len(keep) else 0 for j in range(1, 16)])
    return mp, src


def pwan_silhouette(species: int, form: int, side: str) -> np.ndarray | None:
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from build_w2anim_streams import read_pwan, untile
    cfg, _ = parse_config(PWAN / "config.bin")
    e = cfg.get((species, form))
    if not e:
        return None
    _pal, tl, frames = read_pwan(PWAN / f"{e['assetIndex']}_{side}.pwan")
    lin = np.frombuffer(untile(frames[tl[0][0]]), np.uint8).reshape(96, 48)
    idx = np.empty((96, 96), np.uint8)
    idx[:, 0::2], idx[:, 1::2] = lin & 15, lin >> 4
    return idx != 0


def silhouette_match(first: np.ndarray, pwan: np.ndarray) -> float:
    """Pokeweb's fit of the canvas into 96x96 (bottom-centred), then the best IoU over small shifts."""
    from PIL import Image
    h, w = first.shape[:2]
    s = min(1.0, 96 / w, 96 / h)
    sw, sh = max(1, round(w * s)), max(1, round(h * s))
    m = np.array(Image.fromarray(((first[..., 3] > 127) * 255).astype(np.uint8)).resize((sw, sh), Image.BILINEAR)) > 127
    can = np.zeros((96, 96), bool)
    can[96 - sh:, (96 - sw) // 2:(96 - sw) // 2 + sw] = m
    best = 0.0
    for dy in range(-24, 25):
        a = np.roll(can, dy, axis=0)
        if dy > 0:
            a[:dy] = False
        elif dy < 0:
            a[dy:] = False
        for dx in range(-2, 3):
            b = np.roll(a, dx, axis=1)
            union = np.logical_or(b, pwan).sum()
            if union:
                best = max(best, np.logical_and(b, pwan).sum() / union)
    return float(best)


def import_side(row: dict, w2: dict, cache: Path, offline: bool) -> str:
    fr, palette, timing, mani, lz, ntrgfx = w2["frames"], w2["palette"], w2["timing"], w2["mani"], w2["lz"], w2["ntrgfx"]
    prov = row.get("provenance") or {}
    if not prov.get("url"):
        raise ValueError("no provenance.url")
    notes = []
    gif, digest = fetch(prov["url"], prov.get("sha256"), cache, offline)
    if not prov.get("sha256"):
        notes.append(f'add sha256 = "{digest}"')
    tmp = cache / "_frames.gif"
    tmp.write_bytes(gif)
    frames = fr.gif_frames(str(tmp))
    first = frames[0][0]                       # the GIF's own first frame (canvas), for the PWAN comparison
    shiny = frames
    if prov.get("shiny_url"):
        sgif, sdigest = fetch(prov["shiny_url"], prov.get("shiny_sha256"), cache, offline)
        if not prov.get("shiny_sha256"):
            notes.append(f'add shiny_sha256 = "{sdigest}"')
        tmp.write_bytes(sgif)
        shiny = fr.gif_frames(str(tmp))
        if len(shiny) != len(frames):
            shiny = timing.resample_by_time(shiny, [d for _, d in frames])
    if row.get("fit"):
        limit = int(row["fit"])
        h, w = frames[0][0].shape[:2]
        s = min(1.0, limit / w, limit / h)
        if s < 1:
            nw, nh = int(w * s), int(h * s)
            ys, xs = (np.arange(nh) * h) // nh, (np.arange(nw) * w) // nw
            frames = [(a[ys][:, xs], d) for a, d in frames]
            shiny = [(a[ys][:, xs], d) for a, d in shiny]
            notes.append(f"fitted {w}x{h} -> {nw}x{nh} (nearest)")
    frames, shiny, n_colours = palette.reduce_colors(frames, shiny, 16)
    if n_colours > 16:
        notes.append(f"{n_colours} colours reduced to 16")
    index_of = palette.assign_palette(frames)
    shiny_map = palette.shiny_colors(index_of, frames, shiny)
    normal_pal, shiny_pal = [0] * 16, [0] * 16
    for c, i in index_of.items():
        normal_pal[i] = ntrgfx.bgr555(*c)
        shiny_pal[i] = ntrgfx.bgr555(*shiny_map.get(i, c))
    box = fr.union_box(frames)
    bx0, by0, bx1, by1 = (int(v) for v in box)
    if bx1 - bx0 > 128 or by1 - by0 > 128:
        raise ValueError(f"box {bx1 - bx0}x{by1 - by0} exceeds 128x128 (set fit = 128)")
    blobs, uniq, seq = [], {}, []
    for a, d in frames:
        rows = mani.a3i5_rows(*mani.index_image(a, index_of, box))
        if rows not in uniq:
            uniq[rows] = len(blobs)
            blobs.append(lz.compress11(rows))
        seq.append([uniq[rows], int(d)])
    mp, src = morph_tables(frames, index_of)
    m = dict(w=bx1 - bx0, h=by1 - by0, seq=seq, blobs=blobs, palettes=[normal_pal, shiny_pal],
             x0=bx0 - frames[0][0].shape[1] // 2, y0=-(by1 - by0), map=mp, source=src)
    data = a3i5.write_mani(m)
    # round trip through W2U's decoder: every frame pixel-exact
    back = a3i5.parse_mani(data)
    for k, (a, _d) in enumerate(frames):
        expect = mani.a3i5_rows(*mani.index_image(a, index_of, box))
        if a3i5.frame_rows(back, back["seq"][k][0]) != expect:
            raise ValueError(f"frame {k}: round trip differs")
    pw = pwan_silhouette(int(row["species"]), int(row.get("form", 0)), row["side"])
    if pw is not None:
        match = silhouette_match(first, pw)
        notes.append(f"PWAN match {match:.3f}" + ("  <- LOW: another art or the wrong sprite?" if match < 0.8 else ""))
    out = SOURCES / row["source"]
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(data)
    return (f"{out.relative_to(ROOT)}: {m['w']}x{m['h']}, {len(frames)} frames, {len(blobs)} unique, "
            f"{sum(d for _, d in seq)} ms, {len(data)} bytes; " + "; ".join(notes))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--only", help="SPECIES[:FORM[:SIDE]]")
    ap.add_argument("--w2anim", type=Path, help="the w2anim package's folder (MegaB2W2/tools/w2anim)")
    ap.add_argument("--cache", type=Path, default=ROOT / "work" / "w2anim_sources")
    ap.add_argument("--offline", action="store_true", help="use only the cache")
    args = ap.parse_args()
    if args.w2anim:
        sys.path.insert(0, str(args.w2anim))
    try:
        from w2anim.core import frames, palette, timing, mani, lz, ntrgfx
    except ImportError:
        sys.exit("w2anim not found: pass --w2anim PATH (MegaB2W2/tools/w2anim) or install it")
    w2 = dict(frames=frames, palette=palette, timing=timing, mani=mani, lz=lz, ntrgfx=ntrgfx)
    rows = tomllib.loads(SPRITES.read_text(encoding="utf-8")).get("side", [])
    want = args.only.split(":") if args.only else []
    for row in rows:
        if row.get("format") != "a3i5":
            continue
        key = [str(row["species"]), str(row.get("form", 0)), row["side"]]
        if want and key[:len(want)] != want:
            continue
        print(f"{':'.join(key)}  {import_side(row, w2, args.cache, args.offline)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
