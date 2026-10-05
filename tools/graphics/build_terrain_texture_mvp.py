#!/usr/bin/env python3
"""Build all terrain/background TEX0 replacements used by the battle viewer.

Each output is a one-block NSBTX containing an exact-layout clone of a vanilla
battle background's TEX0 block. Only the selected primary floor texture and its
bound palette are changed, and for Grassy / Misty Terrain also the backdrop
(the batt_sky* material of the outdoor backgrounds) and its palette. Keeping
every offset and allocation size intact lets the runtime borrow the live field
model's VRAM keys safely. The mapping include records each background's sky
palette range (colours) so the runtime fades the sky with its own blend colour.
"""

from __future__ import annotations

import argparse
import csv
import struct
from dataclasses import dataclass
from pathlib import Path

from PIL import Image


DEFAULT_FIRST_MEMBER = 573
FLOOR_ANIMATION_MEMBER = 119
TERRAINS = (
    ("electric", "electric-tileable.png"),
    ("grassy", "grassy-tileable.png"),
    ("misty", "misty-tileable.png"),
    ("psychic", "psychic-tileable.png"),
)
# Terrains that also replace the backdrop, and their sky images (tools/graphics/draw_terrain_floor_tiles.py)
SKY_SOURCES = {"grassy": "grassy-sky.png", "misty": "misty-sky.png"}
FORMAT_NAMES = {
    1: "A3I5",
    2: "4-color",
    3: "16-color",
    4: "256-color",
    6: "A5I3",
}
FORMAT_PALETTE_LIMITS = {1: 32, 2: 4, 3: 16, 4: 256, 6: 8}


@dataclass(frozen=True)
class FloorTarget:
    background: str
    seasons: str
    member: int
    material: str
    texture: str
    palette: str
    width: int
    height: int
    format_name: str
    notes: str
    output_base_member: int | None


@dataclass(frozen=True)
class DictionaryEntry:
    name: str
    datum_offset: int
    datum_size: int


@dataclass(frozen=True)
class TextureLayout:
    entry: DictionaryEntry
    format: int
    width: int
    height: int
    image_offset: int
    image_bytes: int
    color0_transparent: bool


def u16(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def find_tex0(model: bytes) -> tuple[int, int]:
    if model[:4] != b"BMD0":
        raise ValueError("base resource is not an NSBMD/BMD0 file")
    section_count = u16(model, 0x0E)
    for index in range(section_count):
        offset = u32(model, 0x10 + index * 4)
        if model[offset : offset + 4] == b"TEX0":
            size = u32(model, offset + 4)
            if offset + size > len(model):
                raise ValueError("TEX0 block extends past the base resource")
            return offset, size
    raise ValueError("base resource has no TEX0 block")


def find_sky(model: bytes) -> tuple[str, str] | None:
    """(texture, palette) of the model's first material named *sky* (MDL0: NNSG3dResMat's texture / palette to
    material dictionaries), or None."""
    def entries(base: int) -> list[tuple[str, bytes]]:
        count = model[base + 1]
        table = base + u16(model, base + 6)
        unit, names = u16(model, table), table + u16(model, table + 2)
        return [(bytes(model[names + 16 * i:names + 16 * i + 16]).split(b"\0", 1)[0].decode("ascii"),
                 bytes(model[table + 4 + i * unit:table + 4 + (i + 1) * unit])) for i in range(count)]

    mdl0 = next((u32(model, 0x10 + 4 * i) for i in range(u16(model, 0x0E))
                 if model[u32(model, 0x10 + 4 * i):u32(model, 0x10 + 4 * i) + 4] == b"MDL0"), None)
    if mdl0 is None:
        return None
    mdl = mdl0 + u32(entries(mdl0 + 8)[0][1], 0)
    resmat = mdl + u32(model, mdl + 8)
    materials = [name for name, _data in entries(resmat + 4)]

    def bound(dictionary: int) -> dict[str, str]:
        out: dict[str, str] = {}
        for name, data in entries(resmat + u16(model, dictionary)):
            for k in range(data[2]):
                out.setdefault(materials[model[resmat + u16(data, 0) + k]], name)
        return out

    textures, palettes = bound(resmat), bound(resmat + 2)
    for material in materials:
        if "sky" in material and material in textures and material in palettes:
            return textures[material], palettes[material]
    return None


def read_dictionary(data: bytes | bytearray, offset: int) -> list[DictionaryEntry]:
    count = data[offset + 1]
    datum_size = u16(data, offset + 12 + count * 4)
    datum_offset = offset + 16 + count * 4
    names_offset = datum_offset + count * datum_size
    entries: list[DictionaryEntry] = []
    for index in range(count):
        raw_name = data[names_offset + index * 16 : names_offset + (index + 1) * 16]
        name = bytes(raw_name).split(b"\0", 1)[0].decode("ascii")
        entries.append(DictionaryEntry(name, datum_offset + index * datum_size, datum_size))
    return entries


def texture_byte_length(format_id: int, width: int, height: int) -> int:
    pixels = width * height
    if format_id in (1, 4, 6):
        return pixels
    if format_id == 3:
        return pixels // 2
    if format_id == 2:
        return pixels // 4
    raise ValueError(f"unsupported primary-floor texture format {format_id}")


def texture_layout(tex0: bytearray, entry: DictionaryEntry) -> TextureLayout:
    params = u32(tex0, entry.datum_offset)
    format_id = (params >> 26) & 7
    width = 8 << ((params >> 20) & 7)
    height = 8 << ((params >> 23) & 7)
    return TextureLayout(
        entry=entry,
        format=format_id,
        width=width,
        height=height,
        image_offset=(params & 0xFFFF) * 8,
        image_bytes=texture_byte_length(format_id, width, height),
        color0_transparent=bool((params >> 29) & 1),
    )


def prepare_tile(source: Path, width: int, height: int) -> Image.Image:
    with Image.open(source) as opened:
        image = opened.convert("RGB")

    # The authored terrain sources are square seamless tiles. Preserve their
    # aspect ratio for rectangular Nitro allocations by repeating a square
    # downsample instead of stretching the motif horizontally or vertically.
    unit = min(width, height)
    tile = image.resize((unit, unit), Image.Resampling.LANCZOS)
    prepared = Image.new("RGB", (width, height))
    for y in range(0, height, unit):
        for x in range(0, width, unit):
            prepared.paste(tile, (x, y))
    return prepared


def rgb555(red: int, green: int, blue: int) -> int:
    return (red >> 3) | ((green >> 3) << 5) | ((blue >> 3) << 10)


def quantize(image: Image.Image, color_count: int) -> tuple[list[int], bytes]:
    if color_count <= 0:
        raise ValueError("palette has no usable colors")
    quantized = image.quantize(
        colors=color_count,
        method=Image.Quantize.MEDIANCUT,
        dither=Image.Dither.NONE,
    )
    indices = list(quantized.get_flattened_data())
    raw_palette = quantized.getpalette() or []
    palette = bytearray(color_count * 2)
    for index in range(color_count):
        base = index * 3
        red = raw_palette[base] if base < len(raw_palette) else 0
        green = raw_palette[base + 1] if base + 1 < len(raw_palette) else 0
        blue = raw_palette[base + 2] if base + 2 < len(raw_palette) else 0
        struct.pack_into("<H", palette, index * 2, rgb555(red, green, blue))
    return indices, bytes(palette)


def unpack_indices(data: bytes, format_id: int, pixel_count: int) -> list[int]:
    if format_id in (1, 4, 6):
        if format_id == 1:
            return [value & 0x1F for value in data[:pixel_count]]
        if format_id == 6:
            return [value & 0x07 for value in data[:pixel_count]]
        return list(data[:pixel_count])
    if format_id == 3:
        return [
            (data[index // 2] >> (4 * (index & 1))) & 0x0F
            for index in range(pixel_count)
        ]
    if format_id == 2:
        return [
            (data[index // 4] >> (2 * (index & 3))) & 0x03
            for index in range(pixel_count)
        ]
    raise ValueError(f"unsupported texture format {format_id}")


def encode_indices(
    indices: list[int],
    original: bytes,
    layout: TextureLayout,
) -> bytes:
    pixel_count = layout.width * layout.height
    if len(indices) != pixel_count:
        raise ValueError("quantized texture has the wrong pixel count")

    # Alpha-indexed floor layers often use their per-texel alpha as a shape
    # mask. Keep those alpha bits and change only the color index.
    if layout.format == 1:
        return bytes((original[index] & 0xE0) | (indices[index] & 0x1F) for index in range(pixel_count))
    if layout.format == 6:
        return bytes((original[index] & 0xF8) | (indices[index] & 0x07) for index in range(pixel_count))

    original_indices = unpack_indices(original, layout.format, pixel_count)
    if layout.color0_transparent:
        indices = [0 if original_indices[index] == 0 else value for index, value in enumerate(indices)]

    if layout.format == 4:
        return bytes(indices)
    if layout.format == 3:
        packed = bytearray(pixel_count // 2)
        for index, value in enumerate(indices):
            packed[index // 2] |= (value & 0x0F) << (4 * (index & 1))
        return bytes(packed)
    if layout.format == 2:
        packed = bytearray(pixel_count // 4)
        for index, value in enumerate(indices):
            packed[index // 4] |= (value & 0x03) << (2 * (index & 3))
        return bytes(packed)
    raise ValueError(f"unsupported texture format {layout.format}")


def palette_span(tex0: bytearray, entries: list[DictionaryEntry], target: DictionaryEntry) -> tuple[int, int]:
    total_size = u16(tex0, 0x30) * 8
    start = u16(tex0, target.datum_offset) * 8
    later_offsets = [
        u16(tex0, entry.datum_offset) * 8
        for entry in entries
        if u16(tex0, entry.datum_offset) * 8 > start
    ]
    end = min(later_offsets, default=total_size)
    if start < 0 or end <= start or end > total_size:
        raise ValueError(f"invalid palette span {start}:{end} of {total_size}")
    return start, end


def replace_texture(tex0: bytearray, texture: str, palette: str, image: Image.Image, member: int) -> tuple[int, int]:
    """Quantize `image` (already the texture's size) into the named texture and its palette; returns the palette
    span in colours (first, count)."""
    texture_entries = read_dictionary(tex0, u16(tex0, 0x0E))
    texture_entry = next((entry for entry in texture_entries if entry.name == texture), None)
    palette_entries = read_dictionary(tex0, u32(tex0, 0x34))
    palette_entry = next((entry for entry in palette_entries if entry.name == palette), None)
    if texture_entry is None or palette_entry is None:
        raise ValueError(f"member {member} is missing {texture!r} / {palette!r}")
    layout = texture_layout(tex0, texture_entry)
    palette_start, palette_end = palette_span(tex0, palette_entries, palette_entry)
    color_count = min((palette_end - palette_start) // 2, FORMAT_PALETTE_LIMITS[layout.format])
    image_start = u32(tex0, 0x14) + layout.image_offset
    original = bytes(tex0[image_start:image_start + layout.image_bytes])
    reserve_transparent = layout.color0_transparent and layout.format in (2, 3, 4)
    indices, colors = quantize(image.resize((layout.width, layout.height), Image.Resampling.LANCZOS),
                               color_count - 1 if reserve_transparent else color_count)
    if reserve_transparent:
        indices = [value + 1 for value in indices]
        colors = b"\0\0" + colors
    encoded = encode_indices(indices, original, layout)
    tex0[image_start:image_start + layout.image_bytes] = encoded
    write = u32(tex0, 0x38) + palette_start
    tex0[write:write + len(colors)] = colors
    return palette_start // 2, (palette_end - palette_start) // 2


def sky_span(model: bytes) -> tuple[int, int]:
    """The backdrop's palette range in colours (0, 0: no batt_sky* material)."""
    sky = find_sky(model)
    if sky is None:
        return 0, 0
    tex0_offset, tex0_size = find_tex0(model)
    tex0 = model[tex0_offset:tex0_offset + tex0_size]
    entries = read_dictionary(tex0, u32(tex0, 0x34))
    entry = next(entry for entry in entries if entry.name == sky[1])
    start, end = palette_span(bytearray(tex0), entries, entry)
    return start // 2, (end - start) // 2


def build_one(
    base_model: Path,
    source_image: Path,
    output: Path,
    target: FloorTarget,
    sky_image: Path | None = None,
) -> dict[str, int | str]:
    model = base_model.read_bytes()
    tex0_offset, tex0_size = find_tex0(model)
    tex0 = bytearray(model[tex0_offset : tex0_offset + tex0_size])

    texture_entries = read_dictionary(tex0, u16(tex0, 0x0E))
    texture_entry = next((entry for entry in texture_entries if entry.name == target.texture), None)
    if texture_entry is None:
        raise ValueError(f"member {target.member} is missing texture {target.texture!r}")
    layout = texture_layout(tex0, texture_entry)
    actual_format = FORMAT_NAMES.get(layout.format, f"format-{layout.format}")
    if (layout.width, layout.height, actual_format) != (target.width, target.height, target.format_name):
        raise ValueError(
            f"member {target.member} floor layout changed: expected "
            f"{target.width}x{target.height} {target.format_name}, got "
            f"{layout.width}x{layout.height} {actual_format}"
        )

    palette_entries = read_dictionary(tex0, u32(tex0, 0x34))
    palette_entry = next((entry for entry in palette_entries if entry.name == target.palette), None)
    if palette_entry is None:
        raise ValueError(f"member {target.member} is missing palette {target.palette!r}")
    palette_start, palette_end = palette_span(tex0, palette_entries, palette_entry)
    palette_capacity = (palette_end - palette_start) // 2
    color_count = min(palette_capacity, FORMAT_PALETTE_LIMITS[layout.format])

    texture_data_offset = u32(tex0, 0x14)
    image_start = texture_data_offset + layout.image_offset
    image_end = image_start + layout.image_bytes
    original_image = bytes(tex0[image_start:image_end])

    prepared = prepare_tile(source_image, layout.width, layout.height)
    reserve_transparent = layout.color0_transparent and layout.format in (2, 3, 4)
    quantized_count = color_count - 1 if reserve_transparent else color_count
    indices, palette = quantize(prepared, quantized_count)
    if reserve_transparent:
        indices = [value + 1 for value in indices]
        palette = b"\0\0" + palette

    encoded = encode_indices(indices, original_image, layout)
    if len(encoded) != layout.image_bytes:
        raise AssertionError("encoded texture byte count changed")
    tex0[image_start:image_end] = encoded

    palette_data_offset = u32(tex0, 0x38)
    palette_write = palette_data_offset + palette_start
    tex0[palette_write : palette_write + len(palette)] = palette

    sky = find_sky(model)
    if sky_image is not None and sky is not None:
        with Image.open(sky_image) as opened:
            replace_texture(tex0, sky[0], sky[1], opened.convert("RGB"), target.member)

    header_size = 0x14
    output_data = bytearray(header_size + len(tex0))
    struct.pack_into(
        "<4sHHIHHI",
        output_data,
        0,
        b"BTX0",
        0xFEFF,
        0x0100,
        len(output_data),
        0x10,
        1,
        header_size,
    )
    output_data[header_size:] = tex0
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(output_data)
    return {
        "bytes": len(output_data),
        "width": layout.width,
        "height": layout.height,
        "format": actual_format,
        "colors": color_count,
    }


def read_targets(path: Path) -> list[FloorTarget]:
    with path.open(newline="", encoding="utf-8") as stream:
        rows = list(csv.DictReader(stream))
    targets = [
        FloorTarget(
            background=row["background"],
            seasons=row["seasons"],
            member=int(row["nsbmd_member"]),
            material=row["material"],
            texture=row["texture"],
            palette=row["palette"],
            width=int(row["width"]),
            height=int(row["height"]),
            format_name=row["format"],
            notes=row.get("notes", ""),
            output_base_member=(
                int(row["output_base_member"])
                if (row.get("output_base_member") or "").strip()
                else None
            ),
        )
        for row in rows
    ]
    members = [target.member for target in targets]
    if members != sorted(members) or len(members) != len(set(members)):
        raise ValueError("floor-target CSV must contain one row per NSBMD member in ascending order")
    if any(len(target.material.encode("ascii")) > 15 for target in targets):
        raise ValueError("animation material names must fit in a null-terminated Nitro name")
    return targets


def assign_output_members(
    targets: list[FloorTarget],
    first_member: int,
) -> list[tuple[FloorTarget, tuple[int, ...]]]:
    """Assign stable terrain members while allowing appended IDs for new models.

    Targets with no explicit base keep the legacy sequential numbering. An
    explicit base does not consume a legacy slot, so inserting a newly
    discovered field model cannot renumber every later replacement resource.
    """
    assignments: list[tuple[FloorTarget, tuple[int, ...]]] = []
    legacy_index = 0
    used_members: set[int] = set()
    for target in targets:
        if target.output_base_member is None:
            base_member = first_member + legacy_index * len(TERRAINS)
            legacy_index += 1
        else:
            base_member = target.output_base_member
        members = tuple(base_member + terrain for terrain in range(len(TERRAINS)))
        duplicates = used_members.intersection(members)
        if duplicates:
            raise ValueError(
                f"terrain replacement member collision for model {target.member}: "
                f"{sorted(duplicates)}"
            )
        used_members.update(members)
        assignments.append((target, members))
    return assignments


def write_mapping_include(
    path: Path,
    assignments: list[tuple[FloorTarget, tuple[int, ...]]],
    sky_spans: dict[int, tuple[int, int]],
) -> None:
    lines = [
        "// Generated by tools/graphics/build_terrain_texture_mvp.py.",
        "// field member, first of four consecutive terrain NSBTX members, NSBTA, primary material,",
        "// backdrop palette first colour / colour count (0: no batt_sky* backdrop)",
    ]
    for target, members in assignments:
        first, count = sky_spans.get(target.member, (0, 0))
        lines.append(
            f'{{ {target.member}u, {members[0]}u, '
            f'{FLOOR_ANIMATION_MEMBER}u, "{target.material}", {first}u, {count}u }},'
        )
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def write_report(
    path: Path,
    assignments: list[tuple[FloorTarget, tuple[int, ...]]],
) -> None:
    fieldnames = [
        "background",
        "seasons",
        "nsbmd_member",
        "material",
        "texture",
        "palette",
        "width",
        "height",
        "format",
        "electric_member",
        "grassy_member",
        "misty_member",
        "psychic_member",
        "notes",
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=fieldnames, lineterminator="\n")
        writer.writeheader()
        for target, members in assignments:
            writer.writerow(
                {
                    "background": target.background,
                    "seasons": target.seasons,
                    "nsbmd_member": target.member,
                    "material": target.material,
                    "texture": target.texture,
                    "palette": target.palette,
                    "width": target.width,
                    "height": target.height,
                    "format": target.format_name,
                    "electric_member": members[0],
                    "grassy_member": members[1],
                    "misty_member": members[2],
                    "psychic_member": members[3],
                    "notes": target.notes,
                }
            )


def build_catalog(args: argparse.Namespace) -> None:
    targets = read_targets(args.targets)
    assignments = assign_output_members(targets, args.first_member)
    sources = [(name, args.terrain_dir / filename) for name, filename in TERRAINS]
    for _name, source in sources:
        if not source.is_file():
            raise FileNotFoundError(source)

    output_members = [member for _target, members in assignments for member in members]
    output_count = len(output_members)
    for member in output_members:
        path = args.output_dir / str(member)
        if path.exists():
            path.unlink()

    format_counts: dict[str, int] = {}
    total_bytes = 0
    sky_spans: dict[int, tuple[int, int]] = {}
    for target, members in assignments:
        base_model = args.battle_dir / str(target.member)
        sky_spans[target.member] = sky_span(base_model.read_bytes())
        for terrain_index, (terrain_name, source) in enumerate(sources):
            output_member = members[terrain_index]
            sky_image = args.terrain_dir / SKY_SOURCES[terrain_name] if terrain_name in SKY_SOURCES else None
            result = build_one(base_model, source, args.output_dir / str(output_member), target, sky_image)
            total_bytes += int(result["bytes"])
            format_name = str(result["format"])
            format_counts[format_name] = format_counts.get(format_name, 0) + 1
        print(
            f"member {target.member}: {target.material} -> {target.texture}/{target.palette} "
            f"({target.width}x{target.height} {target.format_name})"
        )

    write_mapping_include(args.mapping_include, assignments, sky_spans)
    write_report(args.report, assignments)
    print(
        f"built {output_count} NSBTX members {min(output_members)}.."
        f"{max(output_members)} for {len(targets)} field models; "
        f"{total_bytes} bytes total; formats={format_counts}"
    )


def main() -> int:
    root = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--battle-dir", type=Path, default=root / "data/graphics/battle")
    parser.add_argument(
        "--targets",
        type=Path,
        default=root / "assets/move_backgrounds/terrains/battle-background-floor-targets.csv",
    )
    parser.add_argument(
        "--terrain-dir",
        type=Path,
        default=root / "assets/move_backgrounds/terrains",
    )
    parser.add_argument("--output-dir", type=Path, default=root / "data/graphics/battle")
    parser.add_argument(
        "--mapping-include",
        type=Path,
        default=root / "src/pokeweb_gameplay/w2u_terrain_texture_mappings.inc",
    )
    parser.add_argument(
        "--report",
        type=Path,
        default=root / "docs/terrain-texture-mappings.csv",
    )
    parser.add_argument("--first-member", type=int, default=DEFAULT_FIRST_MEMBER)
    args = parser.parse_args()
    build_catalog(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
