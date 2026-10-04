#!/usr/bin/env python3
"""Import Minior's meteor/core forms and animated PWAN battle sprites.

The source GIFs are 4x2 sheets of 96x96 animations in this order:
red, orange, yellow, green, blue, indigo, violet, shiny.
"""

from __future__ import annotations

import argparse
import importlib.util
import json
import re
import shutil
import struct
import sys
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
SOURCE_DIR = PWAN_DIR / "sources" / "minior"
CONFIG = PWAN_DIR / "config.bin"
PML_ROOT = ROOT / "data" / "pml"
FORM_LIST = PML_ROOT / "poke_form_list.bin"
PALETTE_MAP = PML_ROOT / "pokeicon_palette_map.bin"
MESON_PML = PML_ROOT / "meson.build"
SPECIES_HEADER = ROOT / "include" / "species_ids.h"
SPECIES_ENUM = ROOT / "tools" / "mkdata" / "enum" / "species.toml"
POKEGRA_SOURCE = ROOT / "src" / "pokedex_expansion" / "w2u_pokegra.cpp"
POKEDEX_SOURCE = ROOT / "src" / "pokedex_expansion" / "w2u_pokedex.cpp"
EXPANSION_LIMITS = ROOT / "src" / "pokedex_expansion" / "Expansion_LimitAdjust.s"
VFS_BATTLE = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
VFS_ICONS = ROOT / "vfs" / "data" / "a" / "0" / "0" / "7"
VFS_PERSONAL = ROOT / "vfs" / "data" / "a" / "0" / "1" / "6"
VFS_LEARNSETS = ROOT / "vfs" / "data" / "a" / "0" / "1" / "8"
VFS_EVOLUTIONS = ROOT / "vfs" / "data" / "a" / "0" / "1" / "9"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
ICON_SOURCE = ROOT / "data" / "graphics" / "pokegra" / "icons"
REGIONAL_DEX = PML_ROOT / "RegionalDex.bin"
REPORT = PWAN_DIR / "minior_import_report.json"

MINIOR = 774
FORM_COUNT = 14
METEOR_FORM_COUNT = 7
CORE_FORM_START = 7
FORM_DATA_START = 1273
FORM_SPRITE_START = 459
FORM_ASSET_BASE = 724
BASE_METEOR_PWAN_ASSET = 1252
CORE_ASSET_START = FORM_ASSET_BASE + FORM_SPRITE_START + CORE_FORM_START - 1
SHINY_CORE_ASSET = CORE_ASSET_START + 7
GEN7_BATTLE_ARCHIVE_START = 19000
GEN7_SPECIES_START = 722
BASE_BATTLE_SET = GEN7_BATTLE_ARCHIVE_START + (MINIOR - GEN7_SPECIES_START) * 20
BASE_ICON = 1904 + (MINIOR - GEN7_SPECIES_START) * 2
FILES_PER_SPECIES = 20
ICONS_PER_SPECIES = 2
ICON_ARCHIVE_OFFSET = 8
COLORS = ("red", "orange", "yellow", "green", "blue", "indigo", "violet", "shiny")
GRID_COLUMNS = 4
CELL_SIZE = 96


sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from compile_pwan import compile_pwan, iter_gif_frames  # noqa: E402
from pwan_config import parse_config, write_config  # noqa: E402
from report_paths import write_report  # noqa: E402


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


form_import = load_module(
    "w2u_minior_form_import_helpers",
    ROOT / "tools" / "pwan" / "import_essentials_gen8_gen9.py",
)


def set_toml_int(text: str, key: str, value: int) -> str:
    pattern = re.compile(rf'^("{re.escape(key)}"\s*=\s*).+$', re.MULTILINE)
    if not pattern.search(text):
        raise RuntimeError(f"missing {key!r} in personal data")
    return pattern.sub(rf"\g<1>{value}", text)


def replace_toml_root(text: str, personal_id: int) -> str:
    return re.sub(r"^\[[^\]]+\]", f"[SPECIES_{personal_id}]", text, count=1, flags=re.MULTILINE)


def replace_species_constant(text: str, personal_id: int) -> str:
    match = re.search(r"\[(SPECIES_[A-Z0-9_]+)(?:\.|\])", text)
    if not match:
        raise RuntimeError("missing species constant in data file")
    return text.replace(match.group(1), f"SPECIES_{personal_id}")


def slice_sheet(source: Path, side: str) -> dict[str, Path]:
    image = Image.open(source)
    expected_size = (GRID_COLUMNS * CELL_SIZE, 2 * CELL_SIZE)
    if image.size != expected_size:
        raise RuntimeError(f"{source}: expected {expected_size[0]}x{expected_size[1]}, got {image.size}")

    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    cells: list[list[Image.Image]] = [[] for _ in COLORS]
    durations: list[int] = []
    for frame, ticks in iter_gif_frames(source):
        durations.append(max(1, round(ticks * 1000 / 60)))
        for index in range(len(COLORS)):
            x = (index % GRID_COLUMNS) * CELL_SIZE
            y = (index // GRID_COLUMNS) * CELL_SIZE
            cells[index].append(frame.crop((x, y, x + CELL_SIZE, y + CELL_SIZE)))

    if not durations:
        raise RuntimeError(f"{source}: no GIF frames")

    outputs: dict[str, Path] = {}
    for color, frames in zip(COLORS, cells):
        destination = SOURCE_DIR / f"minior-core-{color}-{side}.gif"
        frames[0].save(
            destination,
            save_all=True,
            append_images=frames[1:],
            loop=0,
            duration=durations,
            disposal=2,
            optimize=False,
        )
        outputs[color] = destination
    return outputs


def set_config_entry(entries: dict, form: int, asset: int) -> None:
    entries[(MINIOR, form)] = {
        "species": MINIOR,
        "form": form,
        "flags": 3,
        "assetIndex": asset,
    }


def copy_base_battle_set(asset: int) -> None:
    destination_base = asset * FILES_PER_SPECIES
    for offset in range(FILES_PER_SPECIES):
        source = VFS_BATTLE / str(BASE_BATTLE_SET + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        destination = VFS_BATTLE / str(destination_base + offset)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)


def persist_battle_set(asset: int) -> None:
    source_base = asset * FILES_PER_SPECIES
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(FILES_PER_SPECIES):
        source = VFS_BATTLE / str(source_base + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        shutil.copy2(source, BATTLE_EXTRA / f"004_{source_base + offset:08d}.bin")


def stage_battle_assets(slices: dict[str, dict[str, Path]]) -> dict:
    # Forms 1-6 are meteor colors. Their battle appearance is identical, but
    # native form changes still require complete carrier sets to exist.
    for form in range(1, CORE_FORM_START):
        asset = FORM_ASSET_BASE + FORM_SPRITE_START + form - 1
        copy_base_battle_set(asset)
        persist_battle_set(asset)

    staged = {}
    shiny_sources = [slices[side]["shiny"] for side in ("front", "back")]
    for color_index, color in enumerate(COLORS[:7]):
        asset = CORE_ASSET_START + color_index
        copy_base_battle_set(asset)
        ok, shiny_ok, error = form_import.patch_static_fallback(
            asset,
            [slices[side][color] for side in ("front", "back")],
            shiny_sources,
        )
        if not ok:
            raise RuntimeError(f"failed to create {color} static fallback: {error}")
        persist_battle_set(asset)
        staged[color] = {"asset": asset, "shinyPalette": shiny_ok}

    copy_base_battle_set(SHINY_CORE_ASSET)
    ok, _shiny_ok, error = form_import.patch_static_fallback(
        SHINY_CORE_ASSET,
        shiny_sources,
        shiny_sources,
    )
    if not ok:
        raise RuntimeError(f"failed to create shiny static fallback: {error}")
    persist_battle_set(SHINY_CORE_ASSET)
    staged["shiny"] = {"asset": SHINY_CORE_ASSET, "shinyPalette": True}
    return staged


def stage_icons() -> None:
    ICON_SOURCE.mkdir(parents=True, exist_ok=True)
    for form in range(1, FORM_COUNT):
        asset = FORM_ASSET_BASE + FORM_SPRITE_START + form - 1
        icon = asset * ICONS_PER_SPECIES + ICON_ARCHIVE_OFFSET
        form_import.copy_icon_index(BASE_ICON, icon)
        for offset in range(ICONS_PER_SPECIES):
            source = VFS_ICONS / str(icon + offset)
            shutil.copy2(source, ICON_SOURCE / f"07_{icon + offset:08d}.bin")

    palette_map = bytearray(PALETTE_MAP.read_bytes())
    required = SHINY_CORE_ASSET + 1
    if len(palette_map) < required:
        palette_map.extend(b"\x00" * (required - len(palette_map)))
    base_palette = palette_map[MINIOR]
    for asset in range(FORM_ASSET_BASE + FORM_SPRITE_START, SHINY_CORE_ASSET + 1):
        palette_map[asset] = base_palette
    PALETTE_MAP.write_bytes(palette_map)


def write_personal_forms() -> list[int]:
    base_path = PML_ROOT / str(MINIOR) / "personal.toml"
    base_text = base_path.read_text(encoding="utf-8")
    base_text = set_toml_int(base_text, "Form Data Offset", FORM_DATA_START)
    base_text = set_toml_int(base_text, "Form Sprite Offset", FORM_SPRITE_START)
    base_text = set_toml_int(base_text, "Form Count", FORM_COUNT)
    base_path.write_text(base_text, encoding="utf-8")

    created = []
    for form in range(1, FORM_COUNT):
        personal_id = FORM_DATA_START + form - 1
        text = replace_toml_root(base_text, personal_id)
        text = set_toml_int(text, "Form Data Offset", 0)
        text = set_toml_int(text, "Form Sprite Offset", 0)
        if form >= CORE_FORM_START:
            text = set_toml_int(text, "Base Attack", 100)
            text = set_toml_int(text, "Base Defense", 60)
            text = set_toml_int(text, "Base Speed", 120)
            text = set_toml_int(text, "Base Special Attack", 100)
            text = set_toml_int(text, "Base Special Defense", 60)
            text = set_toml_int(text, "Base Experience", 175)

        directory = PML_ROOT / str(personal_id)
        directory.mkdir(parents=True, exist_ok=True)
        personal = directory / "personal.toml"
        personal.write_text(text, encoding="utf-8")
        form_import.compile_data_file("personal", personal, personal_id)

        for kind in ("learnset", "evolutions"):
            source = PML_ROOT / str(MINIOR) / f"{kind}.toml"
            aux_text = replace_species_constant(source.read_text(encoding="utf-8"), personal_id)
            destination = directory / f"{kind}.toml"
            destination.write_text(aux_text, encoding="utf-8")
            form_import.compile_data_file(kind, destination, personal_id)
        created.append(personal_id)
    return created


def update_form_list() -> int:
    entries: dict[int, int] = {}
    data = FORM_LIST.read_bytes()
    for offset in range(0, len(data), 4):
        species, count = struct.unpack_from("<HH", data, offset)
        if species == 0:
            break
        entries[species] = count
    entries[MINIOR] = FORM_COUNT
    output = bytearray()
    for species, count in sorted(entries.items()):
        output += struct.pack("<HH", species, count)
    output += struct.pack("<HH", 0, 0)
    FORM_LIST.write_bytes(output)
    return len(entries) + 1


def update_constants(max_personal: int, form_list_size: int) -> int:
    form_import.update_species_constants(max_personal)
    form_import.ensure_meson_entries("personal", list(range(FORM_DATA_START, max_personal + 1)))
    form_import.ensure_meson_entries("learnset", list(range(FORM_DATA_START, max_personal + 1)))
    form_import.ensure_meson_entries("evolutions", list(range(FORM_DATA_START, max_personal + 1)))

    regional_index = max_personal + 1
    replacements = (
        (POKEGRA_SOURCE, r"#define REGIONAL_DEX_FILE_INDEX \d+", f"#define REGIONAL_DEX_FILE_INDEX {regional_index}"),
        (POKEDEX_SOURCE, r"#define REGIONAL_DEX_FILE_INDEX \d+", f"#define REGIONAL_DEX_FILE_INDEX {regional_index}"),
        (POKEDEX_SOURCE, r"#define POKE_FORM_LIST_SIZE 0x[0-9A-Fa-f]+", f"#define POKE_FORM_LIST_SIZE 0x{form_list_size:X}"),
        (EXPANSION_LIMITS, r"\.equ RegionalDexFile, \d+", f".equ RegionalDexFile, {regional_index}"),
    )
    for path, pattern, replacement in replacements:
        text = path.read_text(encoding="utf-8")
        path.write_text(re.sub(pattern, replacement, text), encoding="utf-8")
    VFS_PERSONAL.mkdir(parents=True, exist_ok=True)
    shutil.copy2(REGIONAL_DEX, VFS_PERSONAL / str(regional_index))
    return regional_index


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source-root", required=True, type=Path)
    args = parser.parse_args()
    source_root = args.source_root.resolve()
    sheet_paths = {
        "front": source_root / "minior-core-front.gif",
        "back": source_root / "minior-core-back.gif",
    }
    for path in sheet_paths.values():
        if not path.exists():
            raise FileNotFoundError(path)

    slices = {side: slice_sheet(path, side) for side, path in sheet_paths.items()}
    entries, max_timeline = parse_config(CONFIG)
    for form in range(METEOR_FORM_COUNT):
        set_config_entry(entries, form, BASE_METEOR_PWAN_ASSET)

    pwan_stats = {}
    for color_index, color in enumerate(COLORS[:7]):
        asset = CORE_ASSET_START + color_index
        pwan_stats[color] = {}
        for side in ("front", "back"):
            pwan_stats[color][side] = compile_pwan(
                slices[side][color],
                PWAN_DIR / f"{asset}_{side}.pwan",
            )
        set_config_entry(entries, CORE_FORM_START + color_index, asset)

    pwan_stats["shiny"] = {}
    for side in ("front", "back"):
        pwan_stats["shiny"][side] = compile_pwan(
            slices[side]["shiny"],
            PWAN_DIR / f"{SHINY_CORE_ASSET}_{side}.pwan",
        )
    write_config(CONFIG, entries, max_timeline, max_overrides=768)

    battle_assets = stage_battle_assets(slices)
    stage_icons()
    max_personal = max(
        FORM_DATA_START + FORM_COUNT - 2,
        form_import.max_numeric_personal_id(),
    )
    form_import.update_species_constants(max_personal)
    form_import.ensure_meson_entries("personal", list(range(FORM_DATA_START, max_personal + 1)))
    form_import.ensure_meson_entries("learnset", list(range(FORM_DATA_START, max_personal + 1)))
    form_import.ensure_meson_entries("evolutions", list(range(FORM_DATA_START, max_personal + 1)))
    personal_ids = write_personal_forms()
    form_list_size = update_form_list()
    regional_index = update_constants(max(personal_ids[-1], max_personal), form_list_size)

    report = {
        "version": 1,
        "species": MINIOR,
        "formCount": FORM_COUNT,
        "meteorForms": list(range(METEOR_FORM_COUNT)),
        "coreForms": {color: CORE_FORM_START + i for i, color in enumerate(COLORS[:7])},
        "personalRange": [personal_ids[0], personal_ids[-1]],
        "spriteFormRange": [FORM_SPRITE_START, FORM_SPRITE_START + FORM_COUNT - 2],
        "coreAssetRange": [CORE_ASSET_START, CORE_ASSET_START + 6],
        "shinyCoreAsset": SHINY_CORE_ASSET,
        "regionalDexFileIndex": regional_index,
        "sources": {side: str(path) for side, path in sheet_paths.items()},
        "slices": {
            side: {color: str(path) for color, path in side_slices.items()}
            for side, side_slices in slices.items()
        },
        "pwan": pwan_stats,
        "battleAssets": battle_assets,
    }
    write_report(REPORT, report)
    print(
        f"Imported Minior forms 0-{FORM_COUNT - 1}; core PWAN assets "
        f"{CORE_ASSET_START}-{CORE_ASSET_START + 6}, shiny {SHINY_CORE_ASSET}; "
        f"personal {personal_ids[0]}-{personal_ids[-1]}."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
