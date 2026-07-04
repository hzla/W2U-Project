#!/usr/bin/env python3
"""Expose every tracked Mega form as a temporary low-ID preview species.

This intentionally overwrites the static graphics for species 1, 2, ... with
Mega graphics while keeping the real Mega form rows in place. PWAN entries are
added for preview species when a matching Mega PWAN row exists; Megas that only
have native/static fallback assets still get their low-ID battle/icon graphics
copied.
"""

from __future__ import annotations

import json
import os
import re
import shutil
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PORT = Path(os.environ.get("POKEWEB_SOURCE_ROOT", ROOT.parent / "pokeweb-source"))
TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG_PATH = PWAN_DIR / "config.bin"
REPORT_PATH = PWAN_DIR / "mega_preview_low_ids_report.json"
ESSENTIALS_IMPORT_REPORT = PWAN_DIR / "gen8_gen9_essentials_import_report.json"
VFS_BATTLE = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
VFS_ICONS = ROOT / "vfs" / "data" / "a" / "0" / "0" / "7"
ICON_PALETTE_MAP = ROOT / "data" / "pml" / "pokeicon_palette_map.bin"
POKEGRA_SOURCE = ROOT / "src" / "pokedex_expansion" / "w2u_pokegra.cpp"

PREVIEW_START_SPECIES = 1
FORM_ASSET_BASE = 724
BATTLE_FILES_PER_SPECIES = 20
ICON_FILES_PER_SPECIES = 2
ICON_ARCHIVE_OFFSET = 8
MAX_OVERRIDES = 768

sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from pwan_config import parse_config, write_config as write_pwan_config  # noqa: E402


def battle_path(index: int) -> Path:
    return VFS_BATTLE / str(index)


def icon_path(index: int) -> Path:
    return VFS_ICONS / str(index)


def asset_battle_base(asset: int) -> int:
    return asset * BATTLE_FILES_PER_SPECIES


def asset_icon_base(asset: int) -> int:
    return asset * ICON_FILES_PER_SPECIES + ICON_ARCHIVE_OFFSET


def asset_has_static_source(asset: int) -> bool:
    return battle_path(asset_battle_base(asset)).exists() or icon_path(asset_icon_base(asset)).exists()


def copy_or_empty(src: Path, dst: Path) -> bool:
    dst.parent.mkdir(parents=True, exist_ok=True)
    if src.exists():
        shutil.copy2(src, dst)
        return True
    dst.write_bytes(b"")
    return False


def copy_static_asset(source_asset: int, preview_species: int) -> dict:
    missing_battle: list[int] = []
    missing_icons: list[int] = []
    src_battle_base = asset_battle_base(source_asset)
    dst_battle_base = preview_species * BATTLE_FILES_PER_SPECIES
    for offset in range(BATTLE_FILES_PER_SPECIES):
        if not copy_or_empty(battle_path(src_battle_base + offset), battle_path(dst_battle_base + offset)):
            missing_battle.append(offset)

    src_icon_base = asset_icon_base(source_asset)
    dst_icon_base = preview_species * ICON_FILES_PER_SPECIES + ICON_ARCHIVE_OFFSET
    for offset in range(ICON_FILES_PER_SPECIES):
        if not copy_or_empty(icon_path(src_icon_base + offset), icon_path(dst_icon_base + offset)):
            missing_icons.append(offset)

    return {"missingBattleOffsets": missing_battle, "missingIconOffsets": missing_icons}


def copy_palette(source_asset: int, preview_species: int) -> bool:
    palette = bytearray(ICON_PALETTE_MAP.read_bytes())
    if preview_species >= len(palette):
        palette.extend(b"\x00" * (preview_species + 1 - len(palette)))
    copied = source_asset < len(palette)
    palette[preview_species] = palette[source_asset] if copied else 0
    ICON_PALETTE_MAP.write_bytes(bytes(palette))
    return copied


def patch_preview_constants(preview_end: int) -> None:
    text = POKEGRA_SOURCE.read_text(encoding="utf-8")
    text = re.sub(
        r"#define MEGA_PREVIEW_SPECIES_START \d+",
        f"#define MEGA_PREVIEW_SPECIES_START {PREVIEW_START_SPECIES}",
        text,
    )
    text = re.sub(
        r"#define MEGA_PREVIEW_SPECIES_END \d+",
        f"#define MEGA_PREVIEW_SPECIES_END {preview_end}",
        text,
    )
    POKEGRA_SOURCE.write_text(text, encoding="utf-8")


def load_mega_rows() -> list[dict]:
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    return [row for row in rows if row.get("kind") == "mega form"]


def load_static_relocation_map() -> dict[tuple[int, int], int]:
    if not ESSENTIALS_IMPORT_REPORT.exists():
        return {}
    report = json.loads(ESSENTIALS_IMPORT_REPORT.read_text(encoding="utf-8"))
    out: dict[tuple[int, int], int] = {}
    for row in report.get("relocatedExistingForms", []):
        out[(int(row["baseSpeciesId"]), int(row["form"]))] = int(row["oldAssetIndex"])
    return out


def main() -> int:
    mega_rows = load_mega_rows()
    if not mega_rows:
        raise RuntimeError(f"no Mega rows found in {TRACKER}")

    entries, max_timeline = parse_config(CONFIG_PATH)
    static_relocations = load_static_relocation_map()
    preview_rows: list[dict] = []
    pwan_full = 0
    pwan_partial = 0
    pwan_missing = 0

    for index, row in enumerate(mega_rows):
        preview_species = PREVIEW_START_SPECIES + index
        base_species = int(row["baseSpeciesId"])
        form = int(row["form"])
        source_entry = entries.get((base_species, form))
        pwan_asset = (
            int(source_entry["assetIndex"])
            if source_entry
            else FORM_ASSET_BASE + int(row["spriteForm"])
        )
        static_asset = pwan_asset
        relocated_static_asset = static_relocations.get((base_species, form))
        if relocated_static_asset is not None and not asset_has_static_source(static_asset):
            static_asset = relocated_static_asset

        static_report = copy_static_asset(static_asset, preview_species)
        palette_copied = copy_palette(static_asset, preview_species)

        pwan_state = "missing"
        if source_entry and int(source_entry["flags"]):
            flags = int(source_entry["flags"]) & 0x3
            entries[(preview_species, 0)] = {
                "species": preview_species,
                "form": 0,
                "flags": flags,
                "assetIndex": pwan_asset,
                "frontIndex": pwan_asset if flags & 0x1 else 0,
                "backIndex": pwan_asset if flags & 0x2 else 0,
            }
            if flags == 0x3:
                pwan_full += 1
                pwan_state = "full"
            else:
                pwan_partial += 1
                pwan_state = f"flags_{flags}"
        else:
            entries.pop((preview_species, 0), None)
            pwan_missing += 1

        preview_rows.append(
            {
                "previewSpecies": preview_species,
                "name": row["name"],
                "key": row["key"],
                "baseSpeciesId": base_species,
                "form": form,
                "pwanAsset": pwan_asset,
                "staticAsset": static_asset,
                "pwan": pwan_state,
                "paletteCopied": palette_copied,
                **static_report,
            }
        )

    write_pwan_config(CONFIG_PATH, entries, max_timeline, max_overrides=MAX_OVERRIDES)
    patch_preview_constants(preview_rows[-1]["previewSpecies"])

    report = {
        "version": 1,
        "previewStartSpecies": PREVIEW_START_SPECIES,
        "previewEndSpecies": preview_rows[-1]["previewSpecies"],
        "megaForms": len(preview_rows),
        "pwanFull": pwan_full,
        "pwanPartial": pwan_partial,
        "pwanMissing": pwan_missing,
        "pwanConfigEntries": len(entries),
        "maxAssetIndex": max(int(entry["assetIndex"]) for entry in entries.values()),
        "rows": preview_rows,
    }
    REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"Applied {len(preview_rows)} low-ID Mega previews "
        f"{PREVIEW_START_SPECIES}-{preview_rows[-1]['previewSpecies']} "
        f"({pwan_full} full PWAN, {pwan_partial} partial PWAN, {pwan_missing} static-only)."
    )
    print(f"Wrote {REPORT_PATH}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
