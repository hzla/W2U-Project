#!/usr/bin/env python3
"""Stage Ash-Greninja form data assets without colliding with Mega Greninja."""

from __future__ import annotations

import argparse
import importlib.util
import json
import os
import shutil
import struct
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG = PWAN_DIR / "config.bin"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
BATTLE_VFS = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
PALETTE_MAP = ROOT / "data" / "pml" / "pokeicon_palette_map.bin"
FORM_LIST = ROOT / "data" / "pml" / "poke_form_list.bin"
REPORT = PWAN_DIR / "battle_bond_import_report.json"

GRENINJA = 658
MEGA_FORM = 1
ASH_FORM = 2
OLD_MEGA_ASSET = 1067
NEW_MEGA_ASSET = 1180
ASH_ASSET = 1181
FILES_PER_SPECIES = 20
ICON_ARCHIVE_OFFSET = 8


sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from compile_pwan import compile_pwan  # noqa: E402
from pwan_config import parse_config, write_config  # noqa: E402


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def copy_mega_battle_assets() -> None:
    source_base = OLD_MEGA_ASSET * FILES_PER_SPECIES
    target_base = NEW_MEGA_ASSET * FILES_PER_SPECIES
    for offset in range(FILES_PER_SPECIES):
        source = BATTLE_EXTRA / f"004_{source_base + offset:08d}.bin"
        if not source.exists():
            raise FileNotFoundError(source)
        target = BATTLE_EXTRA / f"004_{target_base + offset:08d}.bin"
        shutil.copy2(source, target)
        shutil.copy2(source, BATTLE_VFS / str(target_base + offset))


def update_form_list() -> None:
    data = bytearray(FORM_LIST.read_bytes())
    for offset in range(0, len(data), 4):
        species, _count = struct.unpack_from("<HH", data, offset)
        if species == GRENINJA:
            struct.pack_into("<HH", data, offset, GRENINJA, 3)
            FORM_LIST.write_bytes(data)
            return
        if species == 0:
            break
    raise RuntimeError("Greninja is missing from poke_form_list.bin")


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
    os.environ["POKEWEB_SOURCE_ROOT"] = str(source_root)

    front = source_root / "essentials_gifs" / "Front" / "GRENINJA_2.gif"
    back = source_root / "essentials_gifs" / "Back" / "GRENINJA_2.gif"
    icon = source_root / "essentials_pngs" / "Icons" / "GRENINJA_2.png"
    for source in (front, back, icon):
        if not source.exists():
            raise FileNotFoundError(source)

    shutil.copy2(PWAN_DIR / f"{OLD_MEGA_ASSET}_front.pwan", PWAN_DIR / f"{NEW_MEGA_ASSET}_front.pwan")
    shutil.copy2(PWAN_DIR / f"{OLD_MEGA_ASSET}_back.pwan", PWAN_DIR / f"{NEW_MEGA_ASSET}_back.pwan")
    ash_front = compile_pwan(front, PWAN_DIR / f"{ASH_ASSET}_front.pwan")
    ash_back = compile_pwan(back, PWAN_DIR / f"{ASH_ASSET}_back.pwan")

    entries, max_timeline = parse_config(CONFIG)
    for asset in (NEW_MEGA_ASSET, ASH_ASSET):
        conflicts = [key for key, entry in entries.items() if entry["assetIndex"] == asset and key[0] != GRENINJA]
        if conflicts:
            raise RuntimeError(f"PWAN asset {asset} is already used by {conflicts}")
    entries[(GRENINJA, MEGA_FORM)] = {
        "species": GRENINJA,
        "form": MEGA_FORM,
        "flags": 3,
        "assetIndex": NEW_MEGA_ASSET,
    }
    entries[(GRENINJA, ASH_FORM)] = {
        "species": GRENINJA,
        "form": ASH_FORM,
        "flags": 3,
        "assetIndex": ASH_ASSET,
    }
    write_config(CONFIG, entries, max_timeline, max_overrides=768)

    copy_mega_battle_assets()
    form_battle = load_module("w2u_stage_battle_bond_form", ROOT / "tools" / "pwan" / "stage_form_battle_assets.py")
    ash_static = form_battle.patch_form_battle(
        {"key": "ALT_GRENINJA_ASH", "name": "Ash-Greninja", "battleSet": ASH_ASSET * FILES_PER_SPECIES},
        ASH_ASSET,
        "GRENINJA_2",
    )

    form_icons = load_module("w2u_stage_battle_bond_icon", ROOT / "tools" / "pwan" / "stage_form_icon_assets.py")
    old_icon = OLD_MEGA_ASSET * 2 + ICON_ARCHIVE_OFFSET
    new_icon = NEW_MEGA_ASSET * 2 + ICON_ARCHIVE_OFFSET
    for offset in range(2):
        shutil.copy2(form_icons.icon_path(old_icon + offset), form_icons.icon_path(new_icon + offset))

    palettes = form_icons.read_icon_palettes()
    palette_map = bytearray(PALETTE_MAP.read_bytes())
    if len(palette_map) <= ASH_ASSET:
        palette_map.extend(b"\x00" * (ASH_ASSET + 1 - len(palette_map)))
    palette_map[NEW_MEGA_ASSET] = palette_map[OLD_MEGA_ASSET]
    ash_icon = form_icons.write_generated_icon(
        ASH_ASSET * 2 + ICON_ARCHIVE_OFFSET,
        ASH_ASSET,
        "GRENINJA_2",
        palettes,
        palette_map,
    )
    PALETTE_MAP.write_bytes(palette_map)
    update_form_list()

    report = {
        "version": 1,
        "species": GRENINJA,
        "forms": {
            "mega": {"form": MEGA_FORM, "assetIndex": NEW_MEGA_ASSET},
            "ash": {"form": ASH_FORM, "assetIndex": ASH_ASSET},
        },
        "ashPwan": {"front": ash_front, "back": ash_back},
        "ashStatic": ash_static,
        "ashIcon": ash_icon,
    }
    REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"Staged Mega Greninja at asset {NEW_MEGA_ASSET} and Ash-Greninja at asset {ASH_ASSET}.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
