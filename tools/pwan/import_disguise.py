#!/usr/bin/env python3
"""Import Mimikyu-Busted animation and form graphics for Disguise."""

from __future__ import annotations

import argparse
import json
import shutil
import struct
from pathlib import Path

import import_essentials_gen8_gen9 as form_import
from pwan_config import parse_config, write_config


ROOT = Path(__file__).resolve().parents[2]
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG = PWAN_DIR / "config.bin"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
ICON_SOURCE = ROOT / "data" / "graphics" / "pokegra" / "icons"
PALETTE_MAP = ROOT / "data" / "pml" / "pokeicon_palette_map.bin"
FORM_LIST = ROOT / "data" / "pml" / "poke_form_list.bin"
REPORT = PWAN_DIR / "disguise_import_report.json"

MIMIKYU = 778
BUSTED_FORM = 1
BUSTED_ASSET = 1182
BASE_BATTLE_SET = 20120
BASE_ICON = 2016
BUSTED_ICON = BUSTED_ASSET * 2 + form_import.ICON_ARCHIVE_OFFSET

# Keep the busted textures and palettes, but inherit Mimikyu's own cell and
# animation metadata. The native form-change effect applies affine transforms
# through these carrier resources, so a generic carrier visibly shifts the
# sprite while the effect flashes between phases.
CARRIER_METADATA_OFFSETS = (
    4, 5, 6, 7, 8,       # front NCER, NANR, NMCR, NMAR, NCEC
    13, 14, 15, 16, 17,  # back NCER, NANR, NMCR, NMAR, NCEC
)


def update_form_list() -> int:
    data = FORM_LIST.read_bytes()
    entries: dict[int, int] = {}
    for offset in range(0, len(data), 4):
        species, count = struct.unpack_from("<HH", data, offset)
        if species == 0:
            break
        entries[species] = count
    entries[MIMIKYU] = 2

    output = bytearray()
    for species, count in sorted(entries.items()):
        output += struct.pack("<HH", species, count)
    output += struct.pack("<HH", 0, 0)
    FORM_LIST.write_bytes(output)
    return len(entries) + 1


def persist_native_fallback() -> None:
    base = BUSTED_ASSET * form_import.FILES_PER_SPECIES
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(form_import.FILES_PER_SPECIES):
        source = form_import.battle_path(base + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        shutil.copy2(source, BATTLE_EXTRA / f"004_{base + offset:08d}.bin")


def inherit_mimikyu_carrier() -> list[int]:
    busted_base = BUSTED_ASSET * form_import.FILES_PER_SPECIES
    copied = []
    for offset in CARRIER_METADATA_OFFSETS:
        source = BATTLE_EXTRA / f"004_{BASE_BATTLE_SET + offset:08d}.bin"
        if not source.exists():
            source = form_import.battle_path(BASE_BATTLE_SET + offset)
        if not source.exists():
            raise FileNotFoundError(source)

        target = form_import.battle_path(busted_base + offset)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
        copied.append(offset)
    return copied


def persist_form_icon() -> None:
    form_import.copy_icon_index(BASE_ICON, BUSTED_ICON)
    ICON_SOURCE.mkdir(parents=True, exist_ok=True)
    for offset in range(form_import.ICONS_PER_SPECIES):
        source = form_import.icon_path(BUSTED_ICON + offset)
        shutil.copy2(source, ICON_SOURCE / f"07_{BUSTED_ICON + offset:08d}.bin")

    palette_map = bytearray(PALETTE_MAP.read_bytes())
    if len(palette_map) <= BUSTED_ASSET:
        palette_map.extend(b"\x00" * (BUSTED_ASSET + 1 - len(palette_map)))
    palette_map[BUSTED_ASSET] = palette_map[MIMIKYU]
    PALETTE_MAP.write_bytes(palette_map)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--source-root",
        required=True,
        type=Path,
        help="Port-Pokeweb root containing sprites/smogon-gifs-g7",
    )
    args = parser.parse_args()
    sprite_dir = args.source_root.resolve() / "sprites" / "smogon-gifs-g7"
    sources = {
        "front": sprite_dir / "mimikyu-busted-front.gif",
        "back": sprite_dir / "mimikyu-busted-back.gif",
        "frontShiny": None,
        "backShiny": None,
    }
    for side in ("front", "back"):
        if not sources[side].exists():
            raise FileNotFoundError(sources[side])

    entries, max_timeline = parse_config(CONFIG)
    conflicts = [
        key
        for key, entry in entries.items()
        if entry["assetIndex"] == BUSTED_ASSET and key != (MIMIKYU, BUSTED_FORM)
    ]
    if conflicts:
        raise RuntimeError(f"PWAN asset {BUSTED_ASSET} is already used by {conflicts}")

    imported = form_import.compile_sources(
        MIMIKYU,
        BUSTED_FORM,
        BUSTED_ASSET,
        sources,
        entries,
    )
    if imported["missingSides"] or not imported["nativeFallback"]:
        raise RuntimeError(f"incomplete Mimikyu-Busted import: {imported}")

    inherited_carrier_offsets = inherit_mimikyu_carrier()
    write_config(CONFIG, entries, max_timeline, max_overrides=768)
    persist_native_fallback()
    persist_form_icon()
    form_list_size = update_form_list()

    report = {
        "version": 1,
        "species": MIMIKYU,
        "form": BUSTED_FORM,
        "personalId": 1272,
        "spriteForm": 458,
        "assetIndex": BUSTED_ASSET,
        "formListRecords": form_list_size,
        "sources": {side: str(path) for side, path in sources.items() if path is not None},
        "import": imported,
        "battleSet": BUSTED_ASSET * form_import.FILES_PER_SPECIES,
        "carrierSourceBattleSet": BASE_BATTLE_SET,
        "inheritedCarrierOffsets": inherited_carrier_offsets,
        "icon": BUSTED_ICON,
    }
    REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"Imported Mimikyu-Busted form {BUSTED_FORM} as PWAN asset {BUSTED_ASSET}, "
        f"personal 1272, sprite form 458."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
