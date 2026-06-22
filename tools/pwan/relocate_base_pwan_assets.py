#!/usr/bin/env python3
"""Relocate Gen 7-9 base PWAN assets away from form/Mega asset ids."""

from __future__ import annotations

import json
import re
import shutil
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PORT = Path("/Users/andylee/Repos/Port-Pokeweb")
if not PORT.exists():
    PORT = ROOT.parent / "Port-Pokeweb"

PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG_PATH = PWAN_DIR / "config.bin"
TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"
SPECIES_NAMES = PORT / "reference_repos/PKHeX/PKHeX.Core/Resources/text/other/en/text_Species_en.txt"
GEN7_DOWNLOADS = PORT / "gen7-sprite-work" / "downloads"
SMOGON_G7 = PORT / "sprites" / "smogon-gifs-g7"
ESSENTIALS_GIFS = PORT / "essentials_gifs"
REPORT = PWAN_DIR / "base_pwan_asset_relocation_report.json"

GEN7_START = 722
GEN9_END = 1023
BASE_PWAN_ASSET_START = 1200
MAX_OVERRIDES = 768
SOURCE_SLUG_RE = re.compile(r"gen7-sprite-work/downloads/([^;]+)")
ASSET_NOTE_RE = re.compile(r"PWAN asset index \d+")

sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from compile_pwan import compile_pwan  # noqa: E402
from pwan_config import (  # noqa: E402
    PWAN_CONFIG_BACK_FLAG,
    PWAN_CONFIG_FRONT_FLAG,
    parse_config,
    write_config as write_pwan_config,
)


def normalize_name(value: str) -> str:
    return re.sub(r"[^A-Z0-9]+", "", value.upper())


def compact_slug(value: str) -> str:
    return re.sub(r"[^a-z0-9]+", "", value.lower())


def target_asset(species: int) -> int:
    return BASE_PWAN_ASSET_START + (species - GEN7_START)


def pwan_path(asset: int, side: str) -> Path:
    return PWAN_DIR / f"{asset}_{side}.pwan"


def species_name_map() -> dict[int, str]:
    names = SPECIES_NAMES.read_text(encoding="utf-8").splitlines()
    return {species: names[species] for species in range(GEN7_START, GEN9_END + 1)}


def tracker_base_rows() -> dict[int, dict]:
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    return {
        int(row["id"]): row
        for row in rows
        if row.get("kind") == "base species" and GEN7_START <= int(row.get("id", 0)) <= GEN9_END
    }


def find_gen7_source(row: dict, name: str, side: str) -> Path | None:
    notes = row.get("runtimeNotes", "")
    slug_match = SOURCE_SLUG_RE.search(notes)
    candidates = []
    if slug_match:
        candidates.append(GEN7_DOWNLOADS / f"{slug_match.group(1)}-{side}.gif")
    slug = compact_slug(name)
    candidates.extend([
        GEN7_DOWNLOADS / f"{slug}-{side}.gif",
        SMOGON_G7 / f"{slug}-{side}.gif",
        SMOGON_G7 / f"{slug}-{side}.png",
    ])
    stem = normalize_name(name)
    folder = "Front" if side == "front" else "Back"
    candidates.append(ESSENTIALS_GIFS / folder / f"{stem}.gif")
    for candidate in candidates:
        if candidate.exists():
            return candidate
    return None


def find_gen8plus_source(name: str, side: str) -> Path | None:
    stem = normalize_name(name)
    folder = "Front" if side == "front" else "Back"
    source = ESSENTIALS_GIFS / folder / f"{stem}.gif"
    return source if source.exists() else None


def find_source(species: int, row: dict, name: str, side: str) -> Path | None:
    if species < 810:
        return find_gen7_source(row, name, side)
    return find_gen8plus_source(name, side)


def compile_side(source: Path, asset: int, side: str) -> dict:
    destination = pwan_path(asset, side)
    stats = compile_pwan(source, destination)
    return {
        "side": side,
        "source": str(source),
        "destination": str(destination),
        "frames": stats.get("frames"),
        "uniqueFrames": stats.get("unique_frames"),
        "timelineEntries": stats.get("timeline_entries"),
    }


def update_tracker_rows(assignments: dict[int, int]) -> int:
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    changed = 0
    for row in rows:
        if row.get("kind") != "base species":
            continue
        species = int(row.get("id", 0))
        asset = assignments.get(species)
        if asset is None:
            continue
        notes = row.get("runtimeNotes", "")
        replacement = f"PWAN asset index {asset}"
        if ASSET_NOTE_RE.search(notes):
            row["runtimeNotes"] = ASSET_NOTE_RE.sub(replacement, notes, count=1)
        else:
            row["runtimeNotes"] = (notes + f"; {replacement}").strip("; ")
        changed += 1
    TRACKER.write_text(json.dumps(rows, indent=2) + "\n", encoding="utf-8")
    return changed


def main() -> int:
    names = species_name_map()
    rows = tracker_base_rows()
    entries, max_timeline = parse_config(CONFIG_PATH)
    compiled = []
    missing = []
    assignments: dict[int, int] = {}

    for species in range(GEN7_START, GEN9_END + 1):
        asset = target_asset(species)
        name = names[species]
        row = rows.get(species, {})
        flags = 0
        side_reports = []
        for side, flag in (("front", PWAN_CONFIG_FRONT_FLAG), ("back", PWAN_CONFIG_BACK_FLAG)):
            source = find_source(species, row, name, side)
            if source is None:
                missing.append({"species": species, "name": name, "side": side})
                continue
            side_reports.append(compile_side(source, asset, side))
            flags |= flag

        if flags:
            entries[(species, 0)] = {
                "species": species,
                "form": 0,
                "flags": flags,
                "assetIndex": asset,
                "frontIndex": asset if flags & PWAN_CONFIG_FRONT_FLAG else 0,
                "backIndex": asset if flags & PWAN_CONFIG_BACK_FLAG else 0,
            }
            assignments[species] = asset
            compiled.append({
                "species": species,
                "name": name,
                "assetIndex": asset,
                "sides": side_reports,
            })
        else:
            entries.pop((species, 0), None)

    write_pwan_config(CONFIG_PATH, entries, max_timeline, max_overrides=MAX_OVERRIDES)
    tracker_changed = update_tracker_rows(assignments)
    report = {
        "version": 1,
        "speciesRange": [GEN7_START, GEN9_END],
        "assetRange": [target_asset(GEN7_START), target_asset(GEN9_END)],
        "compiled": compiled,
        "missing": missing,
        "trackerRowsUpdated": tracker_changed,
        "pwanConfigEntries": len(entries),
        "maxAssetIndex": max(int(entry["assetIndex"]) for entry in entries.values()),
    }
    REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(
        f"Relocated {len(compiled)} base PWAN asset(s) to "
        f"{target_asset(GEN7_START)}-{target_asset(GEN9_END)}; missing sides={len(missing)}."
    )
    print(f"Wrote {REPORT}")
    return 1 if missing else 0


if __name__ == "__main__":
    raise SystemExit(main())
