#!/usr/bin/env python3
"""Stage Gen 8/9 native pokegra files outside the expanded form ranges.

PWAN animation config still uses the real species ids (810-1023). The native
fallback battle archive and party icon archive cannot use the direct Gen 8/9
indices because those collide with the relocated Gen 7 and expanded-form
windows. This script stages deterministic fallback files in the 1200+ asset
range and keeps the public tracker in sync with that runtime mapping.
"""

from __future__ import annotations

import importlib.util
import json
import os
import re
import shutil
import sys
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
PORT = Path(os.environ.get("POKEWEB_SOURCE_ROOT", ROOT.parent / "pokeweb-source"))

SPECIES_NAMES = PORT / "reference_repos/PKHeX/PKHeX.Core/Resources/text/other/en/text_Species_en.txt"
ESSENTIALS_ICONS = PORT / "essentials_pngs" / "Icons"
TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"

PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
REPORT = PWAN_DIR / "gen8plus_static_graphics_relocation_report.json"
VFS_BATTLE = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
ICON_SOURCE = ROOT / "data" / "graphics" / "pokegra" / "icons"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
PALETTE_MAP = ROOT / "data" / "pml" / "pokeicon_palette_map.bin"

GEN8_START = 810
GEN9_END = 1023
FILES_PER_SPECIES = 20
ICONS_PER_SPECIES = 2
ICON_ARCHIVE_OFFSET = 8
GEN8PLUS_STATIC_ASSET_START = 1200
GEN8PLUS_BATTLE_ARCHIVE_START = GEN8PLUS_STATIC_ASSET_START * FILES_PER_SPECIES
GEN8PLUS_ICON_ARCHIVE_START = GEN8PLUS_STATIC_ASSET_START * ICONS_PER_SPECIES + ICON_ARCHIVE_OFFSET
CARRIER_SEED_BATTLE_BASE = 13060


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


gen_import = load_module("gen8_gen9_import_helpers", ROOT / "tools" / "pwan" / "import_essentials_gen8_gen9.py")
graphics = gen_import.graphics


def normalize_name(value: str) -> str:
    return re.sub(r"[^A-Z0-9]+", "", value.upper())


def battle_base(species: int) -> int:
    return GEN8PLUS_BATTLE_ARCHIVE_START + ((species - GEN8_START) * FILES_PER_SPECIES)


def icon_base(species: int) -> int:
    return GEN8PLUS_ICON_ARCHIVE_START + ((species - GEN8_START) * ICONS_PER_SPECIES)


def static_asset(species: int) -> int:
    return GEN8PLUS_STATIC_ASSET_START + (species - GEN8_START)


def battle_vfs_path(index: int) -> Path:
    return VFS_BATTLE / str(index)


def battle_extra_path(index: int) -> Path:
    return BATTLE_EXTRA / f"004_{index:08d}.bin"


def icon_path(index: int) -> Path:
    return ICON_SOURCE / f"07_{index:08d}.bin"


def nonempty(path: Path) -> bool:
    return path.exists() and path.stat().st_size > 0


def load_species_names() -> list[str]:
    names = SPECIES_NAMES.read_text(encoding="utf-8").splitlines()
    if len(names) <= GEN9_END:
        raise RuntimeError(f"{SPECIES_NAMES} does not include species {GEN9_END}")
    return names


def bgr555_to_rgba(color: int) -> tuple[int, int, int, int]:
    return (
        (color & 0x1F) * 255 // 31,
        ((color >> 5) & 0x1F) * 255 // 31,
        ((color >> 10) & 0x1F) * 255 // 31,
        0 if color == 0 else 255,
    )


def read_icon_palettes() -> list[list[tuple[int, int, int, int]]]:
    data = (ICON_SOURCE / "007_00000000.nclr").read_bytes()
    offset = data.find(b"TTLP")
    if offset < 0:
        raise RuntimeError("could not find icon TTLP palette section")
    start = offset + 0x18
    count = (len(data) - start) // 32
    return [
        [
            bgr555_to_rgba(
                int.from_bytes(
                    data[start + (palette * 16 + index) * 2:start + (palette * 16 + index) * 2 + 2],
                    "little",
                )
            )
            for index in range(16)
        ]
        for palette in range(count)
    ]


def nearest_palette_index(pixel: tuple[int, int, int, int], palette: list[tuple[int, int, int, int]]) -> int:
    red, green, blue, alpha = pixel
    if alpha < 128:
        return 0
    best = 1
    best_distance = 1 << 30
    for index, (pal_red, pal_green, pal_blue, _pal_alpha) in enumerate(palette[1:], 1):
        dr = red - pal_red
        dg = green - pal_green
        db = blue - pal_blue
        distance = dr * dr + dg * dg + db * db
        if distance < best_distance:
            best = index
            best_distance = distance
    return best


def render_icon_sheet(path: Path) -> Image.Image:
    source = Image.open(path).convert("RGBA")
    if source.width >= 128 and source.height >= 64:
        frame_width = source.width // 2
        frame_height = source.height
        frame_boxes = [(0, 0, frame_width, frame_height), (frame_width, 0, frame_width * 2, frame_height)]
    elif source.width >= 64 and source.height >= 64:
        frame_boxes = [(0, 0, 64, 64), (0, 0, 64, 64)]
    elif source.width == 32 and source.height >= 64:
        return source.crop((0, 0, 32, 64))
    else:
        frame_boxes = [(0, 0, source.width, source.height), (0, 0, source.width, source.height)]

    output = Image.new("RGBA", (32, 64), (0, 0, 0, 0))
    for index, box in enumerate(frame_boxes[:2]):
        frame = source.crop(box)
        frame.thumbnail((32, 32), Image.Resampling.NEAREST)
        cell = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
        cell.alpha_composite(frame, ((32 - frame.width) // 2, 32 - frame.height))
        output.alpha_composite(cell, (0, index * 32))
    return output


def choose_palette(image: Image.Image, palettes: list[list[tuple[int, int, int, int]]]) -> int:
    pixels = [pixel for pixel in image.getdata() if pixel[3] >= 128]
    if not pixels:
        return 0
    best = 0
    best_score = 1 << 60
    for index, palette in enumerate(palettes[:3]):
        score = 0
        for pixel in pixels:
            palette_index = nearest_palette_index(pixel, palette)
            pal_red, pal_green, pal_blue, _pal_alpha = palette[palette_index]
            dr = pixel[0] - pal_red
            dg = pixel[1] - pal_green
            db = pixel[2] - pal_blue
            score += dr * dr + dg * dg + db * db
        if score < best_score:
            best = index
            best_score = score
    return best


def tile_icon_pixels(image: Image.Image, palette: list[tuple[int, int, int, int]]) -> bytes:
    pixels = image.load()
    output = bytearray()
    for tile_y in range(0, 64, 8):
        for tile_x in range(0, 32, 8):
            for y in range(8):
                for x in range(0, 8, 2):
                    lo = nearest_palette_index(pixels[tile_x + x, tile_y + y], palette)
                    hi = nearest_palette_index(pixels[tile_x + x + 1, tile_y + y], palette)
                    output.append(lo | (hi << 4))
    return bytes(output)


def write_icon(species: int, stem: str, palettes: list[list[tuple[int, int, int, int]]], palette_map: bytearray) -> dict:
    source = ESSENTIALS_ICONS / f"{stem}.png"
    if not source.exists():
        raise FileNotFoundError(source)
    image = render_icon_sheet(source)
    palette_index = choose_palette(image, palettes)
    template = bytearray(icon_path(GEN8PLUS_ICON_ARCHIVE_START).read_bytes() if icon_path(GEN8PLUS_ICON_ARCHIVE_START).exists() else icon_path(1904).read_bytes())
    template[-0x400:] = tile_icon_pixels(image, palettes[palette_index])
    target = icon_base(species)
    icon_path(target).write_bytes(bytes(template))
    icon_path(target + 1).write_bytes(b"")
    if species >= len(palette_map):
        palette_map.extend(b"\x00" * (species + 1 - len(palette_map)))
    palette_map[species] = palette_index | (palette_index << 4)
    return {
        "species": species,
        "source": str(source),
        "target": target,
        "palette": palette_index,
    }


def seed_battle_files(base: int) -> None:
    for offset in range(FILES_PER_SPECIES):
        source = battle_vfs_path(CARRIER_SEED_BATTLE_BASE + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        target = battle_vfs_path(base + offset)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)


def patch_battle_static(species: int, stem: str) -> dict:
    base = battle_base(species)
    seed_battle_files(base)
    paths = gen_import.source_paths(stem)
    normal_sources = [path for key in ("front", "back") if (path := paths[key]) is not None and path.exists()]
    shiny_sources = [
        path for key in ("frontShiny", "backShiny") if (path := paths[key]) is not None and path.exists()
    ]
    normal_palette = gen_import.collect_image_palette(normal_sources)
    shiny_palette = gen_import.collect_image_palette(shiny_sources) if shiny_sources else normal_palette
    patched_sides = []
    errors = []
    for side, compact_offsets, wide_offsets in (
        ("front", (0, 1), (2, 3)),
        ("back", (9, 10), (11, 12)),
    ):
        pwan_path = PWAN_DIR / f"{species}_{side}.pwan"
        if not pwan_path.exists():
            continue
        try:
            pixels = graphics.pwan_first_pixels(pwan_path)
            pixels = graphics.remap_pixels_to_palette(
                pixels,
                graphics.pwan_palette_values(pwan_path),
                normal_palette,
            )
            compact = graphics.segmented_pwan_pixels(pixels)
            wide = graphics.linear_wide_pwan_pixels(pixels)
            for offset in compact_offsets:
                path = battle_vfs_path(base + offset)
                if nonempty(path):
                    graphics.patch_compressed_ncgr_payload(path, compact, "nlz11")
            for offset in wide_offsets:
                path = battle_vfs_path(base + offset)
                if nonempty(path):
                    graphics.patch_compressed_ncgr_payload(path, wide, "nlz11")
            patched_sides.append(side)
        except Exception as exc:  # noqa: BLE001 - report and continue with seeded fallback.
            errors.append(f"{side}: {exc}")
    gen_import.patch_nclr_file(battle_vfs_path(base + 18), normal_palette)
    gen_import.patch_nclr_file(battle_vfs_path(base + 19), shiny_palette)
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(FILES_PER_SPECIES):
        shutil.copy2(battle_vfs_path(base + offset), battle_extra_path(base + offset))
    return {
        "species": species,
        "staticAsset": static_asset(species),
        "targetBase": base,
        "patchedSides": patched_sides,
        "shinyPalette": bool(shiny_sources),
        "errors": errors,
    }


def update_tracker(species_names: list[str]) -> int:
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    changed = 0
    for row in rows:
        species = int(row.get("id", -1))
        if not (GEN8_START <= species <= GEN9_END) or row.get("kind") != "base species":
            continue
        stem = normalize_name(species_names[species])
        row["battleSet"] = battle_base(species)
        row["battleSprites"] = "20/20"
        row["icon"] = icon_base(species)
        row["iconFile"] = "OK"
        row["iconPalette"] = "OK"
        row["runtimeNotes"] = (
            f"Essentials Gen 8/9 import path; sourceStem {stem}; PWAN asset index {species}; "
            "relocated Gen 8/9 static graphics range"
        )
        changed += 1
    TRACKER.write_text(json.dumps(rows, indent=2) + "\n", encoding="utf-8")
    return changed


def main() -> int:
    names = load_species_names()
    palettes = read_icon_palettes()
    palette_map = bytearray(PALETTE_MAP.read_bytes())
    battle_rows = []
    icon_rows = []
    missing = []
    for species in range(GEN8_START, GEN9_END + 1):
        stem = normalize_name(names[species])
        try:
            battle_row = patch_battle_static(species, stem)
            battle_rows.append(battle_row)
            for error in battle_row["errors"]:
                missing.append({"species": species, "name": names[species], "stage": "battle", "error": error})
        except Exception as exc:  # noqa: BLE001 - collect all failures in the report.
            missing.append({"species": species, "name": names[species], "stage": "battle", "error": str(exc)})
        try:
            icon_rows.append(write_icon(species, stem, palettes, palette_map))
        except Exception as exc:  # noqa: BLE001
            missing.append({"species": species, "name": names[species], "stage": "icon", "error": str(exc)})
    PALETTE_MAP.write_bytes(bytes(palette_map))
    tracker_changed = update_tracker(names)
    report = {
        "version": 1,
        "speciesRange": [GEN8_START, GEN9_END],
        "staticAssetRange": [GEN8PLUS_STATIC_ASSET_START, static_asset(GEN9_END)],
        "battleArchiveRange": [GEN8PLUS_BATTLE_ARCHIVE_START, battle_base(GEN9_END) + FILES_PER_SPECIES - 1],
        "iconArchiveRange": [GEN8PLUS_ICON_ARCHIVE_START, icon_base(GEN9_END) + ICONS_PER_SPECIES - 1],
        "battle": battle_rows,
        "icons": icon_rows,
        "trackerRowsUpdated": tracker_changed,
        "missingOrErrors": missing,
    }
    REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"Staged {len(battle_rows)} battle fallback set(s), {len(icon_rows)} icon set(s); "
        f"updated {tracker_changed} tracker row(s); errors={len(missing)}"
    )
    print(f"Wrote {REPORT}")
    return 1 if missing else 0


if __name__ == "__main__":
    raise SystemExit(main())
