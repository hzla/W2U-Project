#!/usr/bin/env python3
"""Stage form and low-ID Mega preview party icons persistently.

Earlier import scripts wrote some generated icon members directly to VFS. The
build restages archive 7 from data/graphics/pokegra/icons, so direct VFS writes
disappear on rebuild. This script writes the same members into the source icon
folder and updates the palette map entries used by form icons.
"""

from __future__ import annotations

import json
import re
import shutil
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
PORT = Path("/Users/andylee/Repos/Port-Pokeweb")
if not PORT.exists():
    PORT = ROOT.parent / "Port-Pokeweb"

TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"
ESSENTIALS_ICONS = PORT / "essentials_pngs" / "Icons"
ICON_SOURCE = ROOT / "data" / "graphics" / "pokegra" / "icons"
PALETTE_MAP = ROOT / "data" / "pml" / "pokeicon_palette_map.bin"
MEGA_PREVIEW_REPORT = ROOT / "assets" / "pokeweb_pwan" / "mega_preview_low_ids_report.json"
REPORT = ROOT / "assets" / "pokeweb_pwan" / "form_icon_staging_report.json"

SOURCE_STEM_RE = re.compile(r"sourceStem ([A-Z0-9_]+)")


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
        boxes = [(0, 0, frame_width, frame_height), (frame_width, 0, frame_width * 2, frame_height)]
    elif source.width >= 64 and source.height >= 64:
        boxes = [(0, 0, 64, 64), (0, 0, 64, 64)]
    elif source.width == 32 and source.height >= 64:
        return source.crop((0, 0, 32, 64))
    else:
        boxes = [(0, 0, source.width, source.height), (0, 0, source.width, source.height)]

    output = Image.new("RGBA", (32, 64), (0, 0, 0, 0))
    for index, box in enumerate(boxes[:2]):
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


def icon_path(index: int) -> Path:
    return ICON_SOURCE / f"07_{index:08d}.bin"


def write_generated_icon(target_icon: int, palette_key: int, stem: str,
                         palettes: list[list[tuple[int, int, int, int]]], palette_map: bytearray) -> dict:
    source = ESSENTIALS_ICONS / f"{stem}.png"
    if not source.exists():
        raise FileNotFoundError(source)
    image = render_icon_sheet(source)
    palette_index = choose_palette(image, palettes)
    template = bytearray(icon_path(2408).read_bytes())
    template[-0x400:] = tile_icon_pixels(image, palettes[palette_index])
    icon_path(target_icon).write_bytes(bytes(template))
    icon_path(target_icon + 1).write_bytes(b"")
    if palette_key >= len(palette_map):
        palette_map.extend(b"\x00" * (palette_key + 1 - len(palette_map)))
    palette_map[palette_key] = palette_index | (palette_index << 4)
    return {
        "targetIcon": target_icon,
        "paletteKey": palette_key,
        "sourceStem": stem,
        "palette": palette_index,
    }


def stage_form_icons(palettes: list[list[tuple[int, int, int, int]]], palette_map: bytearray) -> list[dict]:
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    staged = []
    for row in rows:
        if row.get("kind") not in {"regional form", "alternate form"}:
            continue
        match = SOURCE_STEM_RE.search(row.get("runtimeNotes", ""))
        if not match:
            continue
        icon = int(row["icon"])
        asset = (icon - 8) // 2
        staged.append(write_generated_icon(icon, asset, match.group(1), palettes, palette_map) | {
            "key": row.get("key"),
            "name": row.get("name"),
        })
    return staged


def stage_preview_icons() -> list[dict]:
    if not MEGA_PREVIEW_REPORT.exists():
        return []
    report = json.loads(MEGA_PREVIEW_REPORT.read_text(encoding="utf-8"))
    staged = []
    for row in report.get("rows", []):
        preview_species = int(row["previewSpecies"])
        static_asset = int(row["staticAsset"])
        source_icon = static_asset * 2 + 8
        target_icon = preview_species * 2 + 8
        copied = []
        for offset in range(2):
            src = icon_path(source_icon + offset)
            dst = icon_path(target_icon + offset)
            if src.exists():
                shutil.copy2(src, dst)
                copied.append(offset)
            else:
                dst.write_bytes(b"")
        staged.append({
            "previewSpecies": preview_species,
            "name": row.get("name"),
            "staticAsset": static_asset,
            "sourceIcon": source_icon,
            "targetIcon": target_icon,
            "copiedOffsets": copied,
        })
    return staged


def main() -> int:
    palettes = read_icon_palettes()
    palette_map = bytearray(PALETTE_MAP.read_bytes())
    form_icons = stage_form_icons(palettes, palette_map)
    preview_icons = stage_preview_icons()
    PALETTE_MAP.write_bytes(bytes(palette_map))
    report = {
        "version": 1,
        "formIcons": form_icons,
        "previewIcons": preview_icons,
        "errors": [],
    }
    REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"Staged {len(form_icons)} form icon set(s) and {len(preview_icons)} Mega preview icon set(s).")
    print(f"Wrote {REPORT}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
