#!/usr/bin/env python3
"""Import Zygarde's Power Construct forms and preserve Mega Zygarde.

The two stable visual forms each expose Aura Break and Power Construct through
their personal-data ability slots. Complete and Mega are battle-only forms:

0: 50% (Aura Break or Power Construct)
1: 10% (Aura Break or Power Construct)
2: Complete
3: Mega Zygarde
"""

from __future__ import annotations

import argparse
import importlib.util
import json
import os
import re
import shutil
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG = PWAN_DIR / "config.bin"
PML_ROOT = ROOT / "data" / "pml"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
ICON_SOURCE = ROOT / "data" / "graphics" / "pokegra" / "icons"
PALETTE_MAP = PML_ROOT / "pokeicon_palette_map.bin"
REGIONAL_DEX = PML_ROOT / "RegionalDex.bin"
VFS_PERSONAL = ROOT / "vfs" / "data" / "a" / "0" / "1" / "6"
REPORT = PWAN_DIR / "power_construct_import_report.json"

ZYGARDE = 718
FORM_COUNT = 4
FORM_DATA_START = 1287
FORM_SPRITE_START = 778
FORM_ASSET_BASE = 724
NATIVE_ASSET_START = FORM_ASSET_BASE + FORM_SPRITE_START

FORM_50_AURA_BREAK = 0
FORM_10_AURA_BREAK = 1
FORM_COMPLETE = 2
FORM_MEGA = 3

BASE_50_ASSET = 718
TEN_PERCENT_ASSET = NATIVE_ASSET_START
COMPLETE_ASSET = NATIVE_ASSET_START + 3
MEGA_ASSET = 1081
OLD_MEGA_PERSONAL = 1171

AURA_BREAK = 188
POWER_CONSTRUCT = 211
FILES_PER_SPECIES = 20
ICONS_PER_SPECIES = 2
ICON_ARCHIVE_OFFSET = 8


sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from report_paths import write_report  # noqa: E402
import import_essentials_gen8_gen9 as form_import  # noqa: E402
from pwan_config import parse_config, write_config  # noqa: E402


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def set_toml_int(text: str, key: str, value: int) -> str:
    pattern = re.compile(rf'^("{re.escape(key)}"\s*=\s*).+$', re.MULTILINE)
    if not pattern.search(text):
        raise RuntimeError(f"missing {key!r} in personal data")
    return pattern.sub(rf"\g<1>{value}", text)


def replace_toml_root(text: str, personal_id: int) -> str:
    return re.sub(
        r"^\[[^\]]+\]",
        f"[SPECIES_{personal_id}]",
        text,
        count=1,
        flags=re.MULTILINE,
    )


def replace_species_constant(text: str, personal_id: int) -> str:
    match = re.search(r"\[(SPECIES_[A-Z0-9_]+)(?:\.|\])", text)
    if not match:
        raise RuntimeError("missing species constant in data file")
    return text.replace(match.group(1), f"SPECIES_{personal_id}")


def set_config_entry(entries: dict, form: int, asset: int) -> None:
    entries[(ZYGARDE, form)] = {
        "species": ZYGARDE,
        "form": form,
        "flags": 3,
        "assetIndex": asset,
    }


def source_paths(source_root: Path, stem: str) -> dict[str, Path]:
    return {
        "front": source_root / "essentials_gifs" / "Front" / f"{stem}.gif",
        "back": source_root / "essentials_gifs" / "Back" / f"{stem}.gif",
        "frontShiny": source_root / "essentials_pngs" / "Front shiny" / f"{stem}.png",
        "backShiny": source_root / "essentials_pngs" / "Back shiny" / f"{stem}.png",
    }


def native_asset_for_form(form: int) -> int:
    if form <= 0:
        return BASE_50_ASSET
    return NATIVE_ASSET_START + form - 1


def copy_battle_set(source_asset: int, destination_asset: int) -> None:
    if source_asset == destination_asset:
        return
    form_import.copy_battle_asset(source_asset, destination_asset)


def persist_battle_set(asset: int) -> None:
    base = asset * FILES_PER_SPECIES
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(FILES_PER_SPECIES):
        source = form_import.battle_path(base + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        shutil.copy2(source, BATTLE_EXTRA / f"004_{base + offset:08d}.bin")


def stage_native_carriers() -> dict[int, int]:
    carrier_sources = {
        native_asset_for_form(FORM_10_AURA_BREAK): TEN_PERCENT_ASSET,
        native_asset_for_form(FORM_COMPLETE): COMPLETE_ASSET,
        native_asset_for_form(FORM_MEGA): MEGA_ASSET,
    }
    for destination, source in carrier_sources.items():
        copy_battle_set(source, destination)
        persist_battle_set(destination)
    return carrier_sources


def icon_index(asset: int) -> int:
    return asset * ICONS_PER_SPECIES + ICON_ARCHIVE_OFFSET


def copy_persistent_icon(source_asset: int, destination_asset: int) -> None:
    source_icon = icon_index(source_asset)
    destination_icon = icon_index(destination_asset)
    for offset in range(ICONS_PER_SPECIES):
        source = ICON_SOURCE / f"07_{source_icon + offset:08d}.bin"
        destination = ICON_SOURCE / f"07_{destination_icon + offset:08d}.bin"
        if not source.exists():
            raise FileNotFoundError(source)
        shutil.copy2(source, destination)


def persist_icon_members(asset: int) -> None:
    first = icon_index(asset)
    for offset in range(ICONS_PER_SPECIES):
        path = ICON_SOURCE / f"07_{first + offset:08d}.bin"
        if not path.exists():
            raise FileNotFoundError(path)


def stage_icons(source_root: Path) -> list[dict]:
    os.environ["POKEWEB_SOURCE_ROOT"] = str(source_root)
    icons = load_module(
        "w2u_stage_power_construct_icons",
        ROOT / "tools" / "pwan" / "stage_form_icon_assets.py",
    )
    palettes = icons.read_icon_palettes()
    palette_map = bytearray(PALETTE_MAP.read_bytes())
    results = []

    generated = {
        native_asset_for_form(FORM_10_AURA_BREAK): "ZYGARDE_1",
        native_asset_for_form(FORM_COMPLETE): "ZYGARDE_2",
    }
    for asset, stem in generated.items():
        results.append(
            icons.write_generated_icon(
                icon_index(asset),
                asset,
                stem,
                palettes,
                palette_map,
            )
        )

    copy_persistent_icon(MEGA_ASSET, native_asset_for_form(FORM_MEGA))

    palette_sources = {
        native_asset_for_form(FORM_MEGA): MEGA_ASSET,
    }
    for destination, source in palette_sources.items():
        if destination >= len(palette_map):
            palette_map.extend(b"\x00" * (destination + 1 - len(palette_map)))
        palette_map[destination] = palette_map[source] if source < len(palette_map) else 0

    PALETTE_MAP.write_bytes(palette_map)
    for form in range(1, FORM_COUNT):
        persist_icon_members(native_asset_for_form(form))
    return results


def apply_stats(text: str, stats: tuple[int, int, int, int, int, int]) -> str:
    hp, attack, defense, speed, special_attack, special_defense = stats
    for key, value in (
        ("Base HP", hp),
        ("Base Attack", attack),
        ("Base Defense", defense),
        ("Base Speed", speed),
        ("Base Special Attack", special_attack),
        ("Base Special Defense", special_defense),
    ):
        text = set_toml_int(text, key, value)
    return text


def write_personal_forms() -> list[int]:
    base_path = PML_ROOT / "zygarde" / "personal.toml"
    base_text = base_path.read_text(encoding="utf-8")
    base_text = set_toml_int(base_text, "Form Data Offset", FORM_DATA_START)
    base_text = set_toml_int(base_text, "Form Sprite Offset", FORM_SPRITE_START)
    base_text = set_toml_int(base_text, "Form Count", FORM_COUNT)
    base_text = set_toml_int(base_text, "Primary Ability", AURA_BREAK)
    base_text = set_toml_int(base_text, "Secondary Ability", POWER_CONSTRUCT)
    base_text = set_toml_int(base_text, "Hidden Ability", POWER_CONSTRUCT)
    base_path.write_text(base_text, encoding="utf-8")
    form_import.compile_data_file("personal", base_path, ZYGARDE)

    old_mega_text = (PML_ROOT / str(OLD_MEGA_PERSONAL) / "personal.toml").read_text(
        encoding="utf-8"
    )
    form_specs = {
        FORM_10_AURA_BREAK: {
            "stats": (54, 100, 71, 115, 61, 85),
            "abilities": (AURA_BREAK, POWER_CONSTRUCT, POWER_CONSTRUCT),
            "height": 120,
            "weight": 335,
            "experience": 219,
        },
        FORM_COMPLETE: {
            "stats": (216, 100, 121, 85, 91, 95),
            "abilities": (POWER_CONSTRUCT, POWER_CONSTRUCT, POWER_CONSTRUCT),
            "height": 450,
            "weight": 6100,
            "experience": 319,
        },
    }

    created = []
    for form in range(1, FORM_COUNT):
        personal_id = FORM_DATA_START + form - 1
        if form == FORM_MEGA:
            text = replace_toml_root(old_mega_text, personal_id)
        else:
            spec = form_specs[form]
            text = replace_toml_root(base_text, personal_id)
            text = apply_stats(text, spec["stats"])
            for key, ability in zip(
                ("Primary Ability", "Secondary Ability", "Hidden Ability"),
                spec["abilities"],
            ):
                text = set_toml_int(text, key, ability)
            text = set_toml_int(text, "Height (cm)", spec["height"])
            text = set_toml_int(text, "Weight (cg)", spec["weight"])
            text = set_toml_int(text, "Base Experience", spec["experience"])

        text = set_toml_int(text, "Form Data Offset", 0)
        text = set_toml_int(text, "Form Sprite Offset", 0)
        text = set_toml_int(text, "Form Count", FORM_COUNT)

        directory = PML_ROOT / str(personal_id)
        directory.mkdir(parents=True, exist_ok=True)
        personal_path = directory / "personal.toml"
        personal_path.write_text(text, encoding="utf-8")
        form_import.compile_data_file("personal", personal_path, personal_id)

        for kind in ("learnset", "evolutions"):
            source = PML_ROOT / "zygarde" / f"{kind}.toml"
            aux_text = replace_species_constant(source.read_text(encoding="utf-8"), personal_id)
            destination = directory / f"{kind}.toml"
            destination.write_text(aux_text, encoding="utf-8")
            form_import.compile_data_file(kind, destination, personal_id)
        created.append(personal_id)

    form_import.ensure_meson_entries("personal", created)
    form_import.ensure_meson_entries("learnset", created)
    form_import.ensure_meson_entries("evolutions", created)
    form_import.update_species_constants(created[-1])
    return created


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--source-root",
        required=True,
        type=Path,
        help="Port-Pokeweb root containing essentials_gifs and essentials_pngs",
    )
    args = parser.parse_args()
    source_root = args.source_root.resolve()

    ten_sources = source_paths(source_root, "ZYGARDE_1")
    complete_sources = source_paths(source_root, "ZYGARDE_2")
    for path in (*ten_sources.values(), *complete_sources.values()):
        if not path.exists():
            raise FileNotFoundError(path)
    for side in ("front", "back"):
        if not (PWAN_DIR / f"{MEGA_ASSET}_{side}.pwan").exists():
            raise FileNotFoundError(PWAN_DIR / f"{MEGA_ASSET}_{side}.pwan")

    entries, max_timeline = parse_config(CONFIG)
    occupied = {
        entry["assetIndex"]
        for key, entry in entries.items()
        if key[0] != ZYGARDE
    }
    conflicts = sorted(
        asset
        for asset in range(NATIVE_ASSET_START, NATIVE_ASSET_START + FORM_COUNT - 1)
        if asset in occupied
    )
    if conflicts:
        raise RuntimeError(f"native Zygarde carrier assets are already used: {conflicts}")

    ten_import = form_import.compile_sources(
        ZYGARDE,
        FORM_10_AURA_BREAK,
        TEN_PERCENT_ASSET,
        ten_sources,
        entries,
    )
    complete_import = form_import.compile_sources(
        ZYGARDE,
        FORM_COMPLETE,
        COMPLETE_ASSET,
        complete_sources,
        entries,
    )
    for result in (ten_import, complete_import):
        if result["missingSides"] or not result["nativeFallback"]:
            raise RuntimeError(f"incomplete Zygarde import: {result}")

    form_assets = {
        FORM_50_AURA_BREAK: BASE_50_ASSET,
        FORM_10_AURA_BREAK: TEN_PERCENT_ASSET,
        FORM_COMPLETE: COMPLETE_ASSET,
        FORM_MEGA: MEGA_ASSET,
    }
    for key in [key for key in entries if key[0] == ZYGARDE and key[1] >= FORM_COUNT]:
        del entries[key]
    for form, asset in form_assets.items():
        set_config_entry(entries, form, asset)
    write_config(CONFIG, entries, max_timeline, max_overrides=768)

    carrier_sources = stage_native_carriers()
    icons = stage_icons(source_root)
    personal_ids = write_personal_forms()
    form_list_size = form_import.update_form_list({ZYGARDE: FORM_COUNT})
    regional_index = form_import.update_archive_constants(personal_ids[-1], form_list_size)
    VFS_PERSONAL.mkdir(parents=True, exist_ok=True)
    shutil.copy2(REGIONAL_DEX, VFS_PERSONAL / str(regional_index))

    report = {
        "version": 2,
        "species": ZYGARDE,
        "formCount": FORM_COUNT,
        "forms": {
            "50Stable": FORM_50_AURA_BREAK,
            "10Stable": FORM_10_AURA_BREAK,
            "complete": FORM_COMPLETE,
            "mega": FORM_MEGA,
        },
        "formAssets": form_assets,
        "nativeCarrierSources": carrier_sources,
        "personalRange": [personal_ids[0], personal_ids[-1]],
        "spriteFormRange": [FORM_SPRITE_START, FORM_SPRITE_START + FORM_COUNT - 2],
        "regionalDexFileIndex": regional_index,
        "formListRecords": form_list_size,
        "imports": {"10Percent": ten_import, "complete": complete_import},
        "icons": icons,
    }
    write_report(REPORT, report)
    print(
        f"Imported Zygarde forms 0-{FORM_COUNT - 1}; personal "
        f"{personal_ids[0]}-{personal_ids[-1]}; native assets "
        f"{NATIVE_ASSET_START}-{NATIVE_ASSET_START + FORM_COUNT - 2}."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
