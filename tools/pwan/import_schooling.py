#!/usr/bin/env python3
"""Import Wishiwashi-School and wire its personal/form data for Schooling."""

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
VFS_PERSONAL = ROOT / "vfs" / "data" / "a" / "0" / "1" / "6"
REGIONAL_DEX = PML_ROOT / "RegionalDex.bin"
REPORT = PWAN_DIR / "schooling_import_report.json"

WISHIWASHI = 746
SOLO_FORM = 0
SCHOOL_FORM = 1
SCHOOL_PERSONAL = 1286
SCHOOL_SPRITE_FORM = 473
SCHOOL_ASSET = 1197
SCHOOL_ICON = SCHOOL_ASSET * 2 + 8


sys.path.insert(0, str(ROOT / "tools" / "pwan"))
import import_essentials_gen8_gen9 as form_import  # noqa: E402
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


def persist_native_fallback() -> None:
    base = SCHOOL_ASSET * form_import.FILES_PER_SPECIES
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(form_import.FILES_PER_SPECIES):
        source = form_import.battle_path(base + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        shutil.copy2(source, BATTLE_EXTRA / f"004_{base + offset:08d}.bin")


def write_personal_data() -> None:
    base_path = PML_ROOT / str(WISHIWASHI) / "personal.toml"
    base_text = base_path.read_text(encoding="utf-8")
    base_text = set_toml_int(base_text, "Form Data Offset", SCHOOL_PERSONAL)
    base_text = set_toml_int(base_text, "Form Sprite Offset", SCHOOL_SPRITE_FORM)
    base_text = set_toml_int(base_text, "Form Count", 2)
    base_path.write_text(base_text, encoding="utf-8")
    form_import.compile_data_file("personal", base_path, WISHIWASHI)

    school_text = replace_toml_root(base_text, SCHOOL_PERSONAL)
    school_text = set_toml_int(school_text, "Base Attack", 140)
    school_text = set_toml_int(school_text, "Base Defense", 130)
    school_text = set_toml_int(school_text, "Base Speed", 30)
    school_text = set_toml_int(school_text, "Base Special Attack", 140)
    school_text = set_toml_int(school_text, "Base Special Defense", 135)
    school_text = set_toml_int(school_text, "Form Data Offset", 0)
    school_text = set_toml_int(school_text, "Form Sprite Offset", 0)
    school_text = set_toml_int(school_text, "Base Experience", 217)
    school_text = set_toml_int(school_text, "Height (cm)", 820)
    school_text = set_toml_int(school_text, "Weight (cg)", 786)

    school_dir = PML_ROOT / str(SCHOOL_PERSONAL)
    school_dir.mkdir(parents=True, exist_ok=True)
    school_path = school_dir / "personal.toml"
    school_path.write_text(school_text, encoding="utf-8")
    form_import.compile_data_file("personal", school_path, SCHOOL_PERSONAL)

    for kind in ("learnset", "evolutions"):
        source = PML_ROOT / str(WISHIWASHI) / f"{kind}.toml"
        text = replace_species_constant(source.read_text(encoding="utf-8"), SCHOOL_PERSONAL)
        destination = school_dir / f"{kind}.toml"
        destination.write_text(text, encoding="utf-8")
        form_import.compile_data_file(kind, destination, SCHOOL_PERSONAL)

    form_import.ensure_meson_entries("personal", [SCHOOL_PERSONAL])
    form_import.ensure_meson_entries("learnset", [SCHOOL_PERSONAL])
    form_import.ensure_meson_entries("evolutions", [SCHOOL_PERSONAL])
    form_import.update_species_constants(SCHOOL_PERSONAL)


def stage_school_icon(source_root: Path) -> dict:
    os.environ["POKEWEB_SOURCE_ROOT"] = str(source_root)
    icons = load_module(
        "w2u_stage_schooling_icon",
        ROOT / "tools" / "pwan" / "stage_form_icon_assets.py",
    )
    palettes = icons.read_icon_palettes()
    palette_map = bytearray(icons.PALETTE_MAP.read_bytes())
    result = icons.write_generated_icon(
        SCHOOL_ICON,
        SCHOOL_ASSET,
        "WISHIWASHI_1",
        palettes,
        palette_map,
    )
    icons.PALETTE_MAP.write_bytes(palette_map)
    return result


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
    sources = {
        "front": source_root / "essentials_gifs" / "Front" / "WISHIWASHI_1.gif",
        "back": source_root / "essentials_gifs" / "Back" / "WISHIWASHI_1.gif",
        "frontShiny": source_root / "essentials_pngs" / "Front shiny" / "WISHIWASHI_1.png",
        "backShiny": source_root / "essentials_pngs" / "Back shiny" / "WISHIWASHI_1.png",
    }
    for source in sources.values():
        if not source.exists():
            raise FileNotFoundError(source)

    entries, max_timeline = parse_config(CONFIG)
    conflicts = [
        key
        for key, entry in entries.items()
        if entry["assetIndex"] == SCHOOL_ASSET and key != (WISHIWASHI, SCHOOL_FORM)
    ]
    if conflicts:
        raise RuntimeError(f"PWAN asset {SCHOOL_ASSET} is already used by {conflicts}")

    imported = form_import.compile_sources(
        WISHIWASHI,
        SCHOOL_FORM,
        SCHOOL_ASSET,
        sources,
        entries,
    )
    if imported["missingSides"] or not imported["nativeFallback"]:
        raise RuntimeError(f"incomplete Wishiwashi-School import: {imported}")
    write_config(CONFIG, entries, max_timeline, max_overrides=768)
    persist_native_fallback()
    icon = stage_school_icon(source_root)
    write_personal_data()

    form_list_size = form_import.update_form_list({WISHIWASHI: 2})
    regional_index = form_import.update_archive_constants(SCHOOL_PERSONAL, form_list_size)
    VFS_PERSONAL.mkdir(parents=True, exist_ok=True)
    shutil.copy2(REGIONAL_DEX, VFS_PERSONAL / str(regional_index))

    report = {
        "version": 1,
        "species": WISHIWASHI,
        "forms": {"solo": SOLO_FORM, "school": SCHOOL_FORM},
        "schoolPersonal": SCHOOL_PERSONAL,
        "schoolSpriteForm": SCHOOL_SPRITE_FORM,
        "schoolAsset": SCHOOL_ASSET,
        "schoolIcon": SCHOOL_ICON,
        "regionalDexFileIndex": regional_index,
        "formListRecords": form_list_size,
        "sources": {key: str(path) for key, path in sources.items()},
        "import": imported,
        "icon": icon,
    }
    write_report(REPORT, report)
    print(
        f"Imported Wishiwashi-School as form {SCHOOL_FORM}, PWAN asset {SCHOOL_ASSET}, "
        f"personal {SCHOOL_PERSONAL}, sprite form {SCHOOL_SPRITE_FORM}."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
