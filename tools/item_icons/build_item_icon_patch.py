#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import shutil
from dataclasses import dataclass
from pathlib import Path

from PIL import Image


@dataclass(frozen=True)
class ItemIconReplacement:
    item_id: int
    constant: str
    name: str


@dataclass(frozen=True)
class MegaStoneReplacement(ItemIconReplacement):
    species: str


MEGA_STONES: tuple[MegaStoneReplacement, ...] = (
    MegaStoneReplacement(505, "ITEM_VENUSAURITE", "Venusaurite", "Venusaur"),
    MegaStoneReplacement(506, "ITEM_CHARIZARDITE_X", "Charizardite X", "Charizard"),
    MegaStoneReplacement(507, "ITEM_CHARIZARDITE_Y", "Charizardite Y", "Charizard"),
    MegaStoneReplacement(508, "ITEM_BLASTOISINITE", "Blastoisinite", "Blastoise"),
    MegaStoneReplacement(509, "ITEM_BEEDRILLITE", "Beedrillite", "Beedrill"),
    MegaStoneReplacement(510, "ITEM_PIDGEOTITE", "Pidgeotite", "Pidgeot"),
    MegaStoneReplacement(511, "ITEM_ALAKAZITE", "Alakazite", "Alakazam"),
    MegaStoneReplacement(512, "ITEM_SLOWBRONITE", "Slowbronite", "Slowbro"),
    MegaStoneReplacement(513, "ITEM_GENGARITE", "Gengarite", "Gengar"),
    MegaStoneReplacement(514, "ITEM_KANGASKHANITE", "Kangaskhanite", "Kangaskhan"),
    MegaStoneReplacement(515, "ITEM_PINSIRITE", "Pinsirite", "Pinsir"),
    MegaStoneReplacement(516, "ITEM_GYARADOSITE", "Gyaradosite", "Gyarados"),
    MegaStoneReplacement(517, "ITEM_AERODACTYLITE", "Aerodactylite", "Aerodactyl"),
    MegaStoneReplacement(518, "ITEM_MEWTWONITE_X", "Mewtwonite X", "Mewtwo"),
    MegaStoneReplacement(519, "ITEM_MEWTWONITE_Y", "Mewtwonite Y", "Mewtwo"),
    MegaStoneReplacement(520, "ITEM_AMPHAROSITE", "Ampharosite", "Ampharos"),
    MegaStoneReplacement(521, "ITEM_STEELIXITE", "Steelixite", "Steelix"),
    MegaStoneReplacement(522, "ITEM_SCIZORITE", "Scizorite", "Scizor"),
    MegaStoneReplacement(523, "ITEM_HERACRONITE", "Heracronite", "Heracross"),
    MegaStoneReplacement(524, "ITEM_HOUNDOOMINITE", "Houndoominite", "Houndoom"),
    MegaStoneReplacement(525, "ITEM_TYRANITARITE", "Tyranitarite", "Tyranitar"),
    MegaStoneReplacement(526, "ITEM_SCEPTILITE", "Sceptilite", "Sceptile"),
    MegaStoneReplacement(527, "ITEM_BLAZIKENITE", "Blazikenite", "Blaziken"),
    MegaStoneReplacement(528, "ITEM_SWAMPERTITE", "Swampertite", "Swampert"),
    MegaStoneReplacement(529, "ITEM_GARDEVOIRITE", "Gardevoirite", "Gardevoir"),
    MegaStoneReplacement(530, "ITEM_SABLENITE", "Sablenite", "Sableye"),
    MegaStoneReplacement(531, "ITEM_MAWILITE", "Mawilite", "Mawile"),
    MegaStoneReplacement(592, "ITEM_AGGRONITE", "Aggronite", "Aggron"),
    MegaStoneReplacement(593, "ITEM_MEDICHAMITE", "Medichamite", "Medicham"),
    MegaStoneReplacement(594, "ITEM_MANECTITE", "Manectite", "Manectric"),
    MegaStoneReplacement(595, "ITEM_SHARPEDONITE", "Sharpedonite", "Sharpedo"),
    MegaStoneReplacement(596, "ITEM_CAMERUPTITE", "Cameruptite", "Camerupt"),
    MegaStoneReplacement(597, "ITEM_ALTARIANITE", "Altarianite", "Altaria"),
    MegaStoneReplacement(598, "ITEM_BANETTITE", "Banettite", "Banette"),
    MegaStoneReplacement(599, "ITEM_ABSOLITE", "Absolite", "Absol"),
    MegaStoneReplacement(600, "ITEM_GLALITITE", "Glalitite", "Glalie"),
    MegaStoneReplacement(601, "ITEM_SALAMENCITE", "Salamencite", "Salamence"),
    MegaStoneReplacement(602, "ITEM_METAGROSSITE", "Metagrossite", "Metagross"),
    MegaStoneReplacement(603, "ITEM_LATIASITE", "Latiasite", "Latias"),
    MegaStoneReplacement(604, "ITEM_LATIOSITE", "Latiosite", "Latios"),
    MegaStoneReplacement(605, "ITEM_LOPUNNITE", "Lopunnite", "Lopunny"),
    MegaStoneReplacement(606, "ITEM_GARCHOMPITE", "Garchompite", "Garchomp"),
    MegaStoneReplacement(607, "ITEM_LUCARIONITE", "Lucarionite", "Lucario"),
    MegaStoneReplacement(608, "ITEM_ABOMASITE", "Abomasite", "Abomasnow"),
    MegaStoneReplacement(609, "ITEM_GALLADITE", "Galladite", "Gallade"),
    MegaStoneReplacement(610, "ITEM_AUDINITE", "Audinite", "Audino"),
)

LOW_ITEM_ICONS: tuple[ItemIconReplacement, ...] = (
    ItemIconReplacement(120, "ITEM_ABILITY_CAPSULE", "Ability Capsule"),
    ItemIconReplacement(121, "ITEM_ASSAULT_VEST", "Assault Vest"),
    ItemIconReplacement(122, "ITEM_LUMINOUS_MOSS", "Luminous Moss"),
    ItemIconReplacement(123, "ITEM_MARANGA_BERRY", "Maranga Berry"),
    ItemIconReplacement(124, "ITEM_MEGA_RING", "Mega Ring"),
    ItemIconReplacement(125, "ITEM_FAIRY_FEATHER", "Fairy Feather"),
    ItemIconReplacement(126, "ITEM_ROSELI_BERRY", "Roseli Berry"),
    ItemIconReplacement(127, "ITEM_SAFETY_GOGGLES", "Safety Goggles"),
    ItemIconReplacement(128, "ITEM_SNOWBALL", "Snowball"),
    ItemIconReplacement(129, "ITEM_WEAKNESS_POLICY", "Weakness Policy"),
    ItemIconReplacement(130, "ITEM_ABILITY_PATCH", "Ability Patch"),
)

MEGA_ITEM_IDS = frozenset(stone.item_id for stone in MEGA_STONES)
LOW_ITEM_IDS = frozenset(item.item_id for item in LOW_ITEM_ICONS)
VANILLA_ITEM_COUNT = 639
DEFAULT_ICON_ARCHIVE_MEMBER_COUNT = 1025
ENTRY_SIZE = 4
ICON_WIDTH = 32
ICON_HEIGHT = 32
ICON_COLOR_COUNT = 16
ICON_TILE_SIZE = 8
ICON_TILE_WIDTH = ICON_WIDTH // ICON_TILE_SIZE
ICON_TILE_HEIGHT = ICON_HEIGHT // ICON_TILE_SIZE
POKE_BALL_VISIBLE_LEFT = 3
POKE_BALL_VISIBLE_TOP = 3
MEGA_STONE_REFERENCE_CENTER_X = 11.5
MEGA_STONE_REFERENCE_CENTER_Y = 11.5
ITEM_GRAPHICS_ANCHOR = (
    (2, 3),
    (4, 5),
    (6, 7),
    (8, 9),
    (10, 11),
    (12, 13),
    (14, 15),
    (16, 17),
    (18, 19),
    (20, 19),
    (21, 22),
    (23, 22),
)


class ItemIconFiles:
    def __init__(self, cgx: bytes, pal: bytes) -> None:
        self.cgx = cgx
        self.pal = pal


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Patch item icon table entries and stage replacement item icon archive members."
    )
    parser.add_argument("--arm9-input", type=Path, required=True)
    parser.add_argument("--arm9-output", type=Path, required=True)
    parser.add_argument("--vfs-output-dir", type=Path, required=True)
    parser.add_argument("--icons", type=Path, required=True)
    parser.add_argument("--palettes", type=Path, required=True)
    parser.add_argument("--report", type=Path)
    parser.add_argument("--stamp", type=Path, required=True)
    parser.add_argument("--archive-member-count", type=int, default=None)
    parser.add_argument("--base-icon-archive", type=Path)
    parser.add_argument("--arc-text", default=".arc\ncompress default auto\n")
    parser.add_argument("--skip-low-items", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    require_paths(args)

    icon_member_count = resolve_icon_archive_member_count(args)
    archive_file_ids = list(range(icon_member_count))
    arm9 = bytearray(args.arm9_input.read_bytes())
    table_offset = locate_item_graphics_table(arm9)

    staged_icons: dict[int, bytes] = {}
    report: list[dict[str, object]] = []

    patch_icon_group(
        "mega_stones",
        MEGA_STONES,
        MEGA_ITEM_IDS,
        "poke_ball",
        arm9,
        table_offset,
        archive_file_ids,
        args,
        staged_icons,
        report,
    )

    if not args.skip_low_items:
        patch_icon_group(
            "gen6_low_items",
            LOW_ITEM_ICONS,
            LOW_ITEM_IDS,
            "mega_reference_mass",
            arm9,
            table_offset,
            archive_file_ids,
            args,
            staged_icons,
            report,
        )

    args.arm9_output.parent.mkdir(parents=True, exist_ok=True)
    args.arm9_output.write_bytes(arm9)
    write_staged_icons(args.vfs_output_dir, args.arc_text, staged_icons)

    if args.report is not None:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text(f"{len(staged_icons)}\n", encoding="ascii")
    print(
        f"Staged {len(staged_icons)} item icon files and patched "
        f"{len(report)} ARM9 item icon table entries."
    )
    return 0


def require_paths(args: argparse.Namespace) -> None:
    for path in (args.arm9_input, args.icons, args.palettes):
        if not path.exists():
            raise FileNotFoundError(path)
    for icon in (*MEGA_STONES, *LOW_ITEM_ICONS):
        png_path, palette_path = icon_source_paths(args, icon.constant)
        if not png_path.exists():
            raise FileNotFoundError(png_path)
        if not palette_path.exists():
            raise FileNotFoundError(palette_path)


def resolve_icon_archive_member_count(args: argparse.Namespace) -> int:
    if args.archive_member_count is not None:
        return args.archive_member_count
    if args.base_icon_archive is not None and args.base_icon_archive.exists():
        try:
            import ndspy.narc
        except ImportError as exc:
            raise RuntimeError("ndspy is required to inspect --base-icon-archive") from exc
        return len(ndspy.narc.NARC.fromFile(str(args.base_icon_archive)).files)
    return DEFAULT_ICON_ARCHIVE_MEMBER_COUNT


def patch_icon_group(
    group: str,
    icons: tuple[ItemIconReplacement, ...],
    target_ids: frozenset[int],
    align_mode: str,
    arm9: bytearray,
    table_offset: int,
    archive_file_ids: list[int],
    args: argparse.Namespace,
    staged_icons: dict[int, bytes],
    report: list[dict[str, object]],
) -> None:
    assignments = choose_target_file_ids(arm9, table_offset, target_ids, archive_file_ids, len(icons))
    patch_arm9_graphics_table(arm9, table_offset, assignments)

    for icon in icons:
        target_cgx, target_pal = assignments[icon.item_id]
        png_path, palette_path = icon_source_paths(args, icon.constant)
        icon_files = build_item_icon_files(png_path, palette_path, align_mode=align_mode)
        staged_icons[target_cgx] = icon_files.cgx
        staged_icons[target_pal] = icon_files.pal
        report.append(
            {
                "group": group,
                "itemId": icon.item_id,
                "constant": icon.constant,
                "name": icon.name,
                "cgxFile": target_cgx,
                "palFile": target_pal,
                "sourcePng": str(png_path),
                "sourcePalette": str(palette_path),
            }
        )


def choose_target_file_ids(
    arm9: bytes | bytearray,
    table_offset: int,
    target_ids: frozenset[int],
    archive_file_ids: list[int],
    target_count: int,
) -> dict[int, tuple[int, int]]:
    used_by_non_targets: set[int] = set()
    for item_id in range(VANILLA_ITEM_COUNT):
        if item_id in target_ids:
            continue
        cgx, pal = read_graphics_entry(arm9, table_offset, item_id)
        used_by_non_targets.add(cgx)
        used_by_non_targets.add(pal)

    free_files = [
        file_id
        for file_id in sorted(archive_file_ids)
        if file_id not in (0, 1) and file_id not in used_by_non_targets
    ]
    required = target_count * 2
    if len(free_files) < required:
        raise RuntimeError(f"Need {required} free icon files, found {len(free_files)}.")

    assignments: dict[int, tuple[int, int]] = {}
    for index, item_id in enumerate(sorted(target_ids)):
        assignments[item_id] = (free_files[index * 2], free_files[index * 2 + 1])
    return assignments


def write_staged_icons(output_dir: Path, arc_text: str, staged_icons: dict[int, bytes]) -> None:
    if output_dir.exists():
        shutil.rmtree(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    for file_id, data in sorted(staged_icons.items()):
        (output_dir / str(file_id)).write_bytes(data)
    (output_dir / ".arc").write_text(arc_text, encoding="utf-8")


def locate_item_graphics_table(arm9: bytes | bytearray) -> int:
    anchor = b"".join(write_u16(cgx) + write_u16(pal) for cgx, pal in ITEM_GRAPHICS_ANCHOR)
    offset = bytes(arm9).find(anchor)
    if offset < ENTRY_SIZE:
        raise RuntimeError("Unable to locate the item icon graphics table in ARM9.")
    return offset - ENTRY_SIZE


def patch_arm9_graphics_table(
    arm9: bytearray,
    table_offset: int,
    assignments: dict[int, tuple[int, int]],
) -> None:
    for item_id, (cgx, pal) in assignments.items():
        offset = table_offset + item_id * ENTRY_SIZE
        arm9[offset : offset + 2] = write_u16(cgx)
        arm9[offset + 2 : offset + 4] = write_u16(pal)


def icon_source_paths(args: argparse.Namespace, constant: str) -> tuple[Path, Path]:
    stem = constant.removeprefix("ITEM_").lower()
    return args.icons / f"{stem}.png", args.palettes / f"{stem}.pal"


def build_item_icon_files(png_path: Path, palette_path: Path, *, align_mode: str) -> ItemIconFiles:
    pixels = read_indexed_icon_pixels(png_path, align_mode=align_mode)
    palette = read_jasc_palette(palette_path)
    max_pixel = max(pixels)
    if max_pixel >= len(palette):
        raise RuntimeError(
            f"{png_path} uses color index {max_pixel}, but {palette_path} only has {len(palette)} colors."
        )
    return ItemIconFiles(build_ncgr(pixels), build_nclr(palette))


def read_indexed_icon_pixels(path: Path, *, align_mode: str) -> list[int]:
    with Image.open(path) as image:
        if image.mode != "P":
            raise RuntimeError(f"{path} must be an indexed-color PNG.")
        if image.width != image.height:
            raise RuntimeError(
                f"{path} is {image.width}x{image.height}; square source icons are required."
            )
        if align_mode == "mega_reference_mass":
            return align_icon_mass_to_mega_reference(list(image.tobytes()), image.width, image.height, path)
        if align_mode == "center_native":
            return center_native_icon_pixels(list(image.tobytes()), image.width, image.height, path)
        if image.size != (ICON_WIDTH, ICON_HEIGHT):
            image = image.resize((ICON_WIDTH, ICON_HEIGHT), Image.Resampling.NEAREST)
        pixels = list(image.tobytes())
        if align_mode == "poke_ball":
            return align_icon_to_poke_ball(pixels, path)
        if align_mode == "center":
            return center_icon_visible_bbox(pixels, path)
        raise ValueError(f"unknown item icon alignment mode: {align_mode}")


def align_icon_to_poke_ball(pixels: list[int], path: Path) -> list[int]:
    bbox = visible_bbox(pixels)
    if bbox is None:
        raise RuntimeError(f"{path} has no visible pixels.")
    left, top, _right, _bottom = bbox
    return translate_pixels(pixels, POKE_BALL_VISIBLE_LEFT - left, POKE_BALL_VISIBLE_TOP - top)


def center_icon_visible_bbox(pixels: list[int], path: Path) -> list[int]:
    bbox = visible_bbox(pixels)
    if bbox is None:
        raise RuntimeError(f"{path} has no visible pixels.")
    left, top, right, bottom = bbox
    width = right - left + 1
    height = bottom - top + 1
    target_left = (ICON_WIDTH - width) // 2
    target_top = (ICON_HEIGHT - height) // 2
    return translate_pixels(pixels, target_left - left, target_top - top)


def center_native_icon_pixels(pixels: list[int], width: int, height: int, path: Path) -> list[int]:
    if width > ICON_WIDTH or height > ICON_HEIGHT:
        raise RuntimeError(
            f"{path} is {width}x{height}; center-native item icons must fit within {ICON_WIDTH}x{ICON_HEIGHT}."
        )

    coords = [(index % width, index // width) for index, pixel in enumerate(pixels) if pixel != 0]
    if not coords:
        raise RuntimeError(f"{path} has no visible pixels.")
    xs = [coord[0] for coord in coords]
    ys = [coord[1] for coord in coords]
    left, top, right, bottom = min(xs), min(ys), max(xs), max(ys)
    visible_width = right - left + 1
    visible_height = bottom - top + 1
    target_left = (ICON_WIDTH - visible_width) // 2
    target_top = (ICON_HEIGHT - visible_height) // 2

    centered = [0] * (ICON_WIDTH * ICON_HEIGHT)
    for y in range(height):
        for x in range(width):
            pixel = pixels[y * width + x]
            if pixel == 0:
                continue
            target_x = x - left + target_left
            target_y = y - top + target_top
            centered[target_y * ICON_WIDTH + target_x] = pixel
    return centered


def align_icon_mass_to_mega_reference(pixels: list[int], width: int, height: int, path: Path) -> list[int]:
    if width > ICON_WIDTH or height > ICON_HEIGHT:
        raise RuntimeError(
            f"{path} is {width}x{height}; reference-aligned item icons must fit within {ICON_WIDTH}x{ICON_HEIGHT}."
        )

    coords = [(index % width, index // width) for index, pixel in enumerate(pixels) if pixel != 0]
    if not coords:
        raise RuntimeError(f"{path} has no visible pixels.")

    xs = [coord[0] for coord in coords]
    ys = [coord[1] for coord in coords]
    left, top, right, bottom = min(xs), min(ys), max(xs), max(ys)
    mass_x = sum(xs) / len(xs)
    mass_y = sum(ys) / len(ys)

    dx = closest_shift(mass_x, MEGA_STONE_REFERENCE_CENTER_X, -left, ICON_WIDTH - right - 1)
    dy = closest_shift(mass_y, MEGA_STONE_REFERENCE_CENTER_Y, -top, ICON_HEIGHT - bottom - 1)

    aligned = [0] * (ICON_WIDTH * ICON_HEIGHT)
    for y in range(height):
        for x in range(width):
            pixel = pixels[y * width + x]
            if pixel == 0:
                continue
            aligned[(y + dy) * ICON_WIDTH + (x + dx)] = pixel
    return aligned


def closest_shift(mass: float, target: float, minimum: int, maximum: int) -> int:
    preferred = round(target - mass)
    if preferred < minimum:
        return minimum
    if preferred > maximum:
        return maximum
    return preferred


def visible_bbox(pixels: list[int]) -> tuple[int, int, int, int] | None:
    coords = [(index % ICON_WIDTH, index // ICON_WIDTH) for index, pixel in enumerate(pixels) if pixel != 0]
    if not coords:
        return None
    xs = [coord[0] for coord in coords]
    ys = [coord[1] for coord in coords]
    return min(xs), min(ys), max(xs), max(ys)


def translate_pixels(pixels: list[int], dx: int, dy: int) -> list[int]:
    translated = [0] * (ICON_WIDTH * ICON_HEIGHT)
    for y in range(ICON_HEIGHT):
        for x in range(ICON_WIDTH):
            target_x = x + dx
            target_y = y + dy
            if 0 <= target_x < ICON_WIDTH and 0 <= target_y < ICON_HEIGHT:
                translated[target_y * ICON_WIDTH + target_x] = pixels[y * ICON_WIDTH + x]
    return translated


def read_jasc_palette(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    if len(lines) < 3 or lines[0] != "JASC-PAL" or lines[1] != "0100":
        raise RuntimeError(f"{path} is not a JASC-PAL 0100 palette.")
    color_count = int(lines[2])
    if color_count != ICON_COLOR_COUNT:
        raise RuntimeError(
            f"{path} has {color_count} colors; item icons require {ICON_COLOR_COUNT}."
        )
    colors: list[tuple[int, int, int]] = []
    for line in lines[3 : 3 + color_count]:
        parts = line.split()
        if len(parts) != 3:
            raise RuntimeError(f"Invalid palette row in {path}: {line!r}")
        rgb = tuple(int(part) for part in parts)
        if any(component < 0 or component > 255 for component in rgb):
            raise RuntimeError(f"Palette row out of range in {path}: {line!r}")
        colors.append(rgb)
    if len(colors) != color_count:
        raise RuntimeError(f"{path} ended before all palette colors were read.")
    return colors


def build_ncgr(pixels: list[int]) -> bytes:
    tile_data = bytearray()
    for tile_y in range(ICON_TILE_HEIGHT):
        for tile_x in range(ICON_TILE_WIDTH):
            for y in range(ICON_TILE_SIZE):
                pixel_y = tile_y * ICON_TILE_SIZE + y
                for x in range(0, ICON_TILE_SIZE, 2):
                    pixel_x = tile_x * ICON_TILE_SIZE + x
                    left = pixels[pixel_y * ICON_WIDTH + pixel_x]
                    right = pixels[pixel_y * ICON_WIDTH + pixel_x + 1]
                    if left >= ICON_COLOR_COUNT or right >= ICON_COLOR_COUNT:
                        raise RuntimeError("Item icon pixels must use 4bpp palette indices only.")
                    tile_data.append(left | (right << 4))

    char_section_size = 0x20 + len(tile_data)
    data = bytearray()
    data += build_ntr_header(b"RGCN", char_section_size, version_101=True)
    data += b"RAHC"
    data += write_u32(char_section_size)
    data += write_u16(0xFFFF)
    data += write_u16(0xFFFF)
    data += write_u32(3)
    data += write_u32(0x10)
    data += write_u32(0)
    data += write_u32(len(tile_data))
    data += write_u32(0x18)
    data += tile_data
    if len(data) != 0x230:
        raise RuntimeError(f"Generated NCGR has unexpected size: {len(data)}")
    return bytes(data)


def build_nclr(palette: list[tuple[int, int, int]]) -> bytes:
    palette_data = bytearray()
    for index in range(256):
        if index < len(palette):
            red, green, blue = palette[index]
            value = rgb_to_bgr555(red, green, blue)
        else:
            value = 0
        palette_data += write_u16(value)

    pltt_section_size = 0x18 + len(palette_data)
    data = bytearray()
    data += build_ntr_header(b"RLCN", pltt_section_size, version_101=False)
    data += b"TTLP"
    data += write_u32(pltt_section_size)
    data += write_u32(3)
    data += write_u32(0)
    data += write_u32(len(palette_data))
    data += write_u32(0x10)
    data += palette_data
    if len(data) != 0x228:
        raise RuntimeError(f"Generated NCLR has unexpected size: {len(data)}")
    return bytes(data)


def build_ntr_header(magic: bytes, section_payload_size: int, *, version_101: bool) -> bytes:
    total_size = 0x10 + section_payload_size
    version = b"\x01\x01" if version_101 else b"\x00\x01"
    return magic + b"\xff\xfe" + version + write_u32(total_size) + write_u16(0x10) + write_u16(1)


def rgb_to_bgr555(red: int, green: int, blue: int) -> int:
    return ((blue // 8) << 10) | ((green // 8) << 5) | (red // 8)


def read_graphics_entry(arm9: bytes | bytearray, table_offset: int, item_id: int) -> tuple[int, int]:
    offset = table_offset + item_id * ENTRY_SIZE
    return read_u16(arm9, offset), read_u16(arm9, offset + 2)


def read_u16(data: bytes | bytearray, offset: int) -> int:
    return int.from_bytes(data[offset : offset + 2], "little")


def write_u16(value: int) -> bytes:
    return value.to_bytes(2, "little")


def write_u32(value: int) -> bytes:
    return value.to_bytes(4, "little")


if __name__ == "__main__":
    raise SystemExit(main())
