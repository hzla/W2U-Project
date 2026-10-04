#!/usr/bin/env python3
"""Repair Gen 7 base PWAN rows that collided with form/Mega asset IDs.

Some earlier Gen 7 tracker rows pointed base species at high PWAN asset IDs
that were later reused by Gen 9 or form/Mega assets. The runtime config keeps
Gen 7 base species on relocated base asset IDs (1200-1287), while the static
battle archive still uses the relocated 19000+ range.
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
OLD_PWAN_DIR = PORT / "White2Upgrade" / "assets" / "pokeweb_pwan"
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG_PATH = PWAN_DIR / "config.bin"
REPORT_PATH = PWAN_DIR / "gen7_pwan_asset_collision_repair_report.json"

GEN7_START = 722
GEN7_END = 809
BASE_PWAN_ASSET_START = 1200
MAX_OVERRIDES = 768
ASSET_NOTE_RE = re.compile(r"PWAN asset index \d+")

sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from report_paths import write_report  # noqa: E402
from pwan_config import (  # noqa: E402
    PWAN_CONFIG_BACK_FLAG,
    PWAN_CONFIG_FRONT_FLAG,
    parse_config,
    write_config as write_pwan_config,
)


def pwan_path(asset: int, side: str, root: Path = PWAN_DIR) -> Path:
    return root / f"{asset}_{side}.pwan"


def target_asset(species: int) -> int:
    return BASE_PWAN_ASSET_START + (species - GEN7_START)


def referenced_asset(row: dict) -> int | None:
    match = re.search(r"PWAN asset index (\d+)", row.get("runtimeNotes", ""))
    return int(match.group(1)) if match else None


def repair_missing_direct_side(species: int, source_asset: int | None, side: str) -> str | None:
    direct = pwan_path(target_asset(species), side)
    if direct.exists() or source_asset is None:
        return None
    source = pwan_path(source_asset, side, OLD_PWAN_DIR)
    if not source.exists():
        return None
    shutil.copy2(source, direct)
    return str(source)


def main() -> int:
    entries, max_timeline = parse_config(CONFIG_PATH)
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))

    repaired: list[dict] = []
    copied: list[dict] = []
    missing: list[dict] = []

    for row in rows:
        if row.get("kind") != "base species":
            continue
        species = int(row.get("id", 0))
        if not GEN7_START <= species <= GEN7_END:
            continue

        old_asset = referenced_asset(row)
        for side in ("front", "back"):
            copied_from = repair_missing_direct_side(species, old_asset, side)
            if copied_from:
                copied.append({"species": species, "side": side, "source": copied_from})

        flags = 0
        asset = target_asset(species)
        if pwan_path(asset, "front").exists():
            flags |= PWAN_CONFIG_FRONT_FLAG
        if pwan_path(asset, "back").exists():
            flags |= PWAN_CONFIG_BACK_FLAG
        if flags == 0:
            missing.append({"species": species, "name": row.get("name")})
            entries.pop((species, 0), None)
            continue

        current = entries.get((species, 0))
        if current is None or int(current.get("assetIndex", -1)) != asset or int(current.get("flags", 0)) != flags:
            repaired.append(
                {
                    "species": species,
                    "name": row.get("name"),
                    "oldEntry": current,
                    "newAssetIndex": asset,
                    "flags": flags,
                }
            )
        entries[(species, 0)] = {
            "species": species,
            "form": 0,
            "flags": flags,
            "assetIndex": asset,
            "frontIndex": asset if flags & PWAN_CONFIG_FRONT_FLAG else 0,
            "backIndex": asset if flags & PWAN_CONFIG_BACK_FLAG else 0,
        }

        notes = row.get("runtimeNotes", "")
        replacement = f"PWAN asset index {asset}"
        if ASSET_NOTE_RE.search(notes):
            row["runtimeNotes"] = ASSET_NOTE_RE.sub(replacement, notes, count=1)

    write_pwan_config(CONFIG_PATH, entries, max_timeline, max_overrides=MAX_OVERRIDES)
    write_report(TRACKER, rows)

    report = {
        "version": 1,
        "repairedRows": repaired,
        "copiedMissingDirectSides": copied,
        "missingDirectAssets": missing,
        "pwanConfigEntries": len(entries),
        "maxAssetIndex": max(int(entry["assetIndex"]) for entry in entries.values()),
    }
    write_report(REPORT_PATH, report)
    print(
        f"Repaired {len(repaired)} Gen 7 PWAN config row(s); "
        f"copied {len(copied)} missing direct side(s)."
    )
    if missing:
        print(f"Missing direct PWAN assets for {len(missing)} Gen 7 species; see {REPORT_PATH}.")
    print(f"Wrote {REPORT_PATH}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
