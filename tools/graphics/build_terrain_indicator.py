#!/usr/bin/env python3
"""Build the battle command-screen terrain indicator into battgra members 420-423.

Superseded by build_command_indicators.py (weather + terrain indicators, art member 941); running this would
put back the static terrain icons that w2u_terrain_indicator.cpp no longer uses.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path

from PIL import Image


TERRAINS = ("electric", "grassy", "misty", "psychic")
PANEL_WIDTH = 32
PANEL_HEIGHT = 32
PALETTE_SLOT = 6
OBJECT_TILE_HEIGHT = 4
OBJECT_TILE_WIDTH = 4
PANEL_TILE_COUNT = OBJECT_TILE_WIDTH * OBJECT_TILE_HEIGHT
SCENE_WIDTH = 22
SCENE_HEIGHT = 16


def u16(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def put_u16(data: bytearray, offset: int, value: int) -> None:
    struct.pack_into("<H", data, offset, value)


def put_u32(data: bytearray, offset: int, value: int) -> None:
    struct.pack_into("<I", data, offset, value)


def crop_cover(image: Image.Image, width: int, height: int) -> Image.Image:
    image = image.convert("RGB")
    scale = max(width / image.width, height / image.height)
    resized = image.resize((round(image.width * scale), round(image.height * scale)), Image.Resampling.LANCZOS)
    left = (resized.width - width) // 2
    top = (resized.height - height) // 2
    return resized.crop((left, top, left + width, top + height))


def label_mask() -> Image.Image:
    glyphs = {
        "T": (0b111, 0b010, 0b010, 0b010, 0b010),
        "E": (0b111, 0b100, 0b110, 0b100, 0b111),
        "R": (0b110, 0b101, 0b110, 0b101, 0b101),
        "A": (0b010, 0b101, 0b111, 0b101, 0b101),
        "I": (0b111, 0b010, 0b010, 0b010, 0b111),
        "N": (0b101, 0b111, 0b111, 0b111, 0b101),
    }
    mask = Image.new("1", (PANEL_WIDTH, 10), 0)
    word = "TERRAIN"
    left = (PANEL_WIDTH - (len(word) * 4 - 1)) // 2
    for glyph_index, letter in enumerate(word):
        for y, row in enumerate(glyphs[letter]):
            for x in range(3):
                if row & (1 << (2 - x)):
                    mask.putpixel((left + glyph_index * 4 + x, y + 2), 1)
    return mask


def terrain_colors(crops: list[Image.Image]) -> list[tuple[int, int, int]]:
    strip = Image.new("RGB", (SCENE_WIDTH, SCENE_HEIGHT * len(crops)))
    for index, crop in enumerate(crops):
        strip.paste(crop, (0, index * SCENE_HEIGHT))
    quantized = strip.quantize(colors=11, method=Image.Quantize.MEDIANCUT)
    raw_palette = quantized.getpalette() or []
    colors: list[tuple[int, int, int]] = []
    for index in range(11):
        colors.append(tuple(raw_palette[index * 3:index * 3 + 3]))
    return colors


def nearest_color(rgb: tuple[int, int, int], palette: list[tuple[int, int, int]]) -> int:
    return min(range(len(palette)), key=lambda index: sum((rgb[channel] - palette[index][channel]) ** 2 for channel in range(3)))


def build_panels(source_dir: Path) -> tuple[list[list[int]], list[tuple[int, int, int]], list[Image.Image]]:
    sources = []
    for terrain in TERRAINS:
        matches = list(source_dir.glob(f"{terrain}.*"))
        if len(matches) != 1:
            raise ValueError(f"expected exactly one source image for {terrain}, found {len(matches)}")
        sources.append(crop_cover(Image.open(matches[0]), SCENE_WIDTH, SCENE_HEIGHT))

    palette = [(0, 0, 0), (16, 16, 16), (255, 255, 255), (70, 70, 70), (176, 176, 176)]
    palette.extend(terrain_colors(sources))
    label = label_mask()
    panels: list[list[int]] = []
    previews: list[Image.Image] = []
    for crop in sources:
        pixels = [0] * (PANEL_WIDTH * PANEL_HEIGHT)
        for y in range(10):
            for x in range(PANEL_WIDTH):
                if not label.getpixel((x, y)):
                    continue
                for oy in (-1, 0, 1):
                    for ox in (-1, 0, 1):
                        px, py = x + ox, y + oy
                        if 0 <= px < PANEL_WIDTH and 0 <= py < PANEL_HEIGHT:
                            pixels[py * PANEL_WIDTH + px] = 1
        for y in range(10):
            for x in range(PANEL_WIDTH):
                if label.getpixel((x, y)):
                    pixels[y * PANEL_WIDTH + x] = 2
        draw_colors = {1: 1, 2: 3, 3: 4}
        for inset, color in draw_colors.items():
            left = 1 + inset
            top = 9 + inset
            right = PANEL_WIDTH - 2 - inset
            bottom = PANEL_HEIGHT - 1 - inset
            for x in range(left, right + 1):
                pixels[top * PANEL_WIDTH + x] = color
                pixels[bottom * PANEL_WIDTH + x] = color
            for y in range(top, bottom + 1):
                pixels[y * PANEL_WIDTH + left] = color
                pixels[y * PANEL_WIDTH + right] = color
        for y in range(SCENE_HEIGHT):
            for x in range(SCENE_WIDTH):
                rgb = crop.getpixel((x, y))
                pixels[(13 + y) * PANEL_WIDTH + 5 + x] = 5 + nearest_color(rgb, palette[5:])
        panels.append(pixels)
        preview = Image.new("RGBA", (PANEL_WIDTH, PANEL_HEIGHT), (0, 0, 0, 0))
        preview.putdata([(0, 0, 0, 0) if value == 0 else (*palette[value], 255) for value in pixels])
        previews.append(preview)
    return panels, palette, previews


def encode_tile(pixels: list[int], tile_x: int, tile_y: int) -> bytes:
    out = bytearray()
    for y in range(8):
        for x in range(0, 8, 2):
            low = pixels[(tile_y * 8 + y) * PANEL_WIDTH + tile_x * 8 + x]
            high = pixels[(tile_y * 8 + y) * PANEL_WIDTH + tile_x * 8 + x + 1]
            out.append(low | (high << 4))
    return bytes(out)


def bgr555(rgb: tuple[int, int, int]) -> int:
    r, g, b = (round(channel * 31 / 255) for channel in rgb)
    return r | (g << 5) | (b << 10)


def patch_ncgr(base: bytes, panels: list[list[int]]) -> tuple[bytes, int]:
    if base[:4] != b"RGCN" or base[0x10:0x14] != b"RAHC":
        raise ValueError("member 420 is not the expected NCGR")
    old_tile_count = u32(base, 0x28) // 32
    sheet_width = u16(base, 0x20)
    if sheet_width != 16:
        raise ValueError(f"expected a 16-tile-wide battgra sheet, got {sheet_width}")
    # Battle's sub engine uses GX_OBJVRAMMODE_CHAR_1D_32K, so character names
    # address individual 32-byte tiles and do not require a 32-tile-aligned
    # base.  Packing directly after the native sheet is important: padding to
    # the next 32-tile boundary leaves too little sub-OBJ VRAM for both party
    # icons on the second command screen of a Double Battle.
    tile_base = old_tile_count
    appended = b""
    object_tiles = []
    for panel in panels:
        for tile_y in range(OBJECT_TILE_HEIGHT):
            for tile_x in range(OBJECT_TILE_WIDTH):
                object_tiles.append(encode_tile(panel, tile_x, tile_y))
    appended += b"".join(object_tiles)
    out = bytearray(base + appended)
    put_u32(out, 0x08, len(out))
    put_u32(out, 0x14, u32(base, 0x14) + len(appended))
    put_u32(out, 0x28, u32(base, 0x28) + len(appended))
    return bytes(out), tile_base


def patch_nclr(base: bytes, palette: list[tuple[int, int, int]]) -> bytes:
    if base[:4] != b"RLCN" or base[0x10:0x14] != b"TTLP":
        raise ValueError("member 421 is not the expected NCLR")
    if len(palette) != 16:
        raise ValueError(f"terrain palette must contain 16 colors, got {len(palette)}")
    out = bytearray(base)
    palette_offset = 0x28 + PALETTE_SLOT * 32
    for index, color in enumerate(palette):
        put_u16(out, palette_offset + index * 2, bgr555(color))
    return bytes(out)


def oam(width: int, height: int, x: int, y: int, character: int) -> bytes:
    shapes = {(32, 32): (0, 2), (16, 32): (2, 2)}
    shape, size = shapes[(width, height)]
    attr0 = (y & 0xFF) | (shape << 14)
    attr1 = (x & 0x1FF) | (size << 14)
    attr2 = (character & 0x3FF) | (PALETTE_SLOT << 12)
    return struct.pack("<HHH", attr0, attr1, attr2)


def patch_ncer(base: bytes, tile_base: int) -> bytes:
    if base[:4] != b"RECN" or base[0x10:0x14] != b"KBEC":
        raise ValueError("member 422 is not the expected NCER")
    block_size = u32(base, 0x14)
    block_end = 0x10 + block_size
    payload = 0x18
    count = u16(base, payload)
    bank_attributes = u16(base, payload + 2)
    if count != 23 or bank_attributes != 0:
        raise ValueError(f"unexpected base NCER layout: {count} cells, attributes={bank_attributes}")
    record_start = payload + u32(base, payload + 4)
    record_size = 8
    old_oam_start = record_start + count * record_size
    old_oam = base[old_oam_start:block_end]
    new_records = bytearray()
    new_oam = bytearray()
    for index in range(4):
        new_records.extend(struct.pack("<HHI", 1, 0, len(old_oam) + len(new_oam)))
        first_tile = tile_base + index * PANEL_TILE_COUNT
        new_oam.extend(oam(32, 32, -16, -16, first_tile))
    new_block = bytearray(base[0x10:old_oam_start])
    put_u16(new_block, payload - 0x10, count + 4)
    new_block.extend(new_records)
    new_block.extend(old_oam)
    new_block.extend(new_oam)
    put_u32(new_block, 4, len(new_block))
    out = bytearray(base[:0x10] + new_block + base[block_end:])
    put_u32(out, 0x08, len(out))
    return bytes(out)


def patch_nanr(base: bytes) -> bytes:
    if base[:4] != b"RNAN" or base[0x10:0x14] != b"KNBA":
        raise ValueError("member 423 is not the expected NANR")
    block_size = u32(base, 0x14)
    block_end = 0x10 + block_size
    payload = 0x18
    sequence_count = u16(base, payload)
    frame_count = u16(base, payload + 2)
    sequence_rel = u32(base, payload + 4)
    frame_rel = u32(base, payload + 8)
    value_rel = u32(base, payload + 12)
    if sequence_count != 21 or frame_count != 36:
        raise ValueError(f"unexpected base NANR layout: {sequence_count} sequences, {frame_count} frames")
    sequence_start = payload + sequence_rel
    frame_start = payload + frame_rel
    value_start = payload + value_rel
    old_sequences = base[sequence_start:frame_start]
    old_frames = base[frame_start:value_start]
    old_values = base[value_start:block_end]
    new_sequences = bytearray()
    new_frames = bytearray()
    new_values = bytearray()
    for index in range(4):
        new_sequences.extend(struct.pack("<HHIII", 1, 0, 0x00010000, 2, len(old_frames) + index * 8))
        new_frames.extend(struct.pack("<IHH", len(old_values) + index * 2, 4, 0))
        new_values.extend(struct.pack("<H", 23 + index))
    new_frame_rel = frame_rel + len(new_sequences)
    new_value_rel = new_frame_rel + len(old_frames) + len(new_frames)
    new_payload = bytearray(base[payload:sequence_start])
    put_u16(new_payload, 0, sequence_count + 4)
    put_u16(new_payload, 2, frame_count + 4)
    put_u32(new_payload, 8, new_frame_rel)
    put_u32(new_payload, 12, new_value_rel)
    new_payload.extend(old_sequences)
    new_payload.extend(new_sequences)
    new_payload.extend(old_frames)
    new_payload.extend(new_frames)
    new_payload.extend(old_values)
    new_payload.extend(new_values)
    new_block = bytearray(base[0x10:payload] + new_payload)
    put_u32(new_block, 4, len(new_block))
    out = bytearray(base[:0x10] + new_block + base[block_end:])
    put_u32(out, 0x08, len(out))
    return bytes(out)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[2])
    args = parser.parse_args()
    root = args.root.resolve()
    source_dir = root / "assets/move_backgrounds/terrains"
    base_dir = root / "assets/terrain_indicator/base"
    output_dir = root / "data/graphics/battle"
    preview_dir = root / "assets/terrain_indicator/preview"
    panels, palette, previews = build_panels(source_dir)
    ncgr, tile_base = patch_ncgr((base_dir / "420").read_bytes(), panels)
    outputs = {
        420: ncgr,
        421: patch_nclr((base_dir / "421").read_bytes(), palette),
        422: patch_ncer((base_dir / "422").read_bytes(), tile_base),
        423: patch_nanr((base_dir / "423").read_bytes()),
    }
    output_dir.mkdir(parents=True, exist_ok=True)
    for member, data in outputs.items():
        (output_dir / str(member)).write_bytes(data)
    preview_dir.mkdir(parents=True, exist_ok=True)
    for terrain, preview in zip(TERRAINS, previews):
        preview.resize((PANEL_WIDTH * 4, PANEL_HEIGHT * 4), Image.Resampling.NEAREST).save(preview_dir / f"{terrain}.png")
    last_tile = tile_base + len(panels) * PANEL_TILE_COUNT - 1
    print(f"terrain indicator: tiles {tile_base}-{last_tile}, cells 23-26, sequences 21-24, palette {PALETTE_SLOT}")


if __name__ == "__main__":
    main()
