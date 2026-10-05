#!/usr/bin/env python3
"""Rebuild the native battle set of PWAN assets that still hold a static sprite's set.

A PWAN asset's 20 native battle members (a/0/0/4, asset * 20 ...) must be a PWAN carrier set: the generic
four-segment cell / animation members (offsets 4-8 and 13-17, as every other PWAN asset) and NCGRs sized for a
96x96 PWAN frame. Two Mega assets (1051 Mega Garchomp, 1053 Mega Lucario) still had a static sprite's set
(its own multi-cell layout and smaller NCGRs), so the runtime drew their PWAN frames through the wrong cells: the
sprite was garbled in battle. This tool reseeds such sets from the carrier template, writes the PWAN's first frame
into the NCGRs (front: 0-3, back: 9-12; the back remapped to the front palette, as stage_form_battle_assets.py
does), the front PWAN palette into the normal NCLR (18) and a shiny NCLR (19) mapped from the old static pair
(each PWAN colour -> the nearest old normal colour -> that slot's shiny colour). Unlike stage_form_battle_assets.py it
needs no pokeweb-source checkout (no source GIFs). The results go to data/graphics/pokegra_battle_extra.

usage: python tools/pwan/restage_pwan_carrier_sets.py ASSET [ASSET ...] [--check]
  --check: only list the PWAN assets of config.bin whose set is not a carrier set (offset 4 / 5 sizes).
Run after a build (it reads the built vfs/data/a/0/0/4 for the template and the old members).
"""

from __future__ import annotations

import importlib.util
import shutil
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from pwan_config import parse_config  # noqa: E402

VFS_BATTLE = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
FILES_PER_SET = 20
CARRIER_SEED_BASE = 13060                     # as stage_form_battle_assets.py
CARRIER_CELL_SIZES = {(115, 132), (115, 89)}  # offset 4 / 5 sizes of the carrier sets in use

spec = importlib.util.spec_from_file_location("w2u_pokegra_graphics", ROOT / "tools" / "graphics" / "build_pokegra_battle.py")
graphics = importlib.util.module_from_spec(spec)
spec.loader.exec_module(graphics)


def member(index: int) -> Path:
    return VFS_BATTLE / str(index)


def nclr_colors(path: Path) -> list[int]:
    data = path.read_bytes()
    k = data.find(b"TTLP")
    off = k + 8 + struct.unpack_from("<I", data, k + 8 + 12)[0]
    return [struct.unpack_from("<H", data, off + 2 * i)[0] for i in range(16)]


def write_nclr_colors(path: Path, colors: list[int]) -> None:
    data = bytearray(path.read_bytes())
    k = data.find(b"TTLP")
    off = k + 8 + struct.unpack_from("<I", data, k + 8 + 12)[0]
    for i, c in enumerate(colors):
        struct.pack_into("<H", data, off + 2 * i, c)
    path.write_bytes(bytes(data))


def rgb(c: int) -> tuple[int, int, int]:
    return c & 31, (c >> 5) & 31, (c >> 10) & 31


def nearest(c: int, palette: list[int]) -> int:
    r, g, b = rgb(c)
    return min(range(1, 16), key=lambda i: (rgb(palette[i])[0] - r) ** 2 + (rgb(palette[i])[1] - g) ** 2
               + (rgb(palette[i])[2] - b) ** 2)


def is_carrier(base: int) -> bool:
    a, b = member(base + 4), member(base + 5)
    return a.exists() and b.exists() and (a.stat().st_size, b.stat().st_size) in CARRIER_CELL_SIZES


def restage(asset: int) -> None:
    base = asset * FILES_PER_SET
    old_normal, old_shiny = nclr_colors(member(base + 18)), nclr_colors(member(base + 19))
    for offset in range(FILES_PER_SET):
        shutil.copy2(member(CARRIER_SEED_BASE + offset), member(base + offset))
    front = PWAN_DIR / f"{asset}_front.pwan"
    palette = graphics.pwan_palette_values(front)
    for side, compact, wide in (("front", (0, 1), (2, 3)), ("back", (9, 10), (11, 12))):
        path = PWAN_DIR / f"{asset}_{side}.pwan"
        if not path.exists():
            continue
        pixels = graphics.pwan_first_pixels(path)
        if side == "back":
            pixels = graphics.remap_pixels_to_palette(pixels, graphics.pwan_palette_values(path), palette)
        for offset in compact:
            if member(base + offset).stat().st_size:
                graphics.patch_compressed_ncgr_payload(member(base + offset), graphics.segmented_pwan_pixels(pixels), "nlz11")
        for offset in wide:
            if member(base + offset).stat().st_size:
                graphics.patch_compressed_ncgr_payload(member(base + offset), graphics.linear_wide_pwan_pixels(pixels), "nlz11")
    shiny = [palette[0]] + [old_shiny[nearest(palette[i], old_normal)] for i in range(1, 16)]
    write_nclr_colors(member(base + 18), palette)
    write_nclr_colors(member(base + 19), shiny)
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(FILES_PER_SET):
        shutil.copy2(member(base + offset), BATTLE_EXTRA / f"004_{base + offset:08d}.bin")
    print(f"asset {asset}: carrier set restaged (members {base}..{base + FILES_PER_SET - 1})")


def main() -> int:
    if "--check" in sys.argv:
        config, _ = parse_config(PWAN_DIR / "config.bin")
        assets = sorted({row["assetIndex"] for row in config.values()})
        bad = [a for a in assets if member(a * FILES_PER_SET + 4).exists() and not is_carrier(a * FILES_PER_SET)]
        print("PWAN assets without a carrier set:", bad)
        return 1 if bad else 0
    for arg in sys.argv[1:]:
        restage(int(arg))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
