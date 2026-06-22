#!/usr/bin/env python3
"""Stage regional/alternate form native battle fallback assets.

The PC summary view still asks the native pokegra archive for a form battle set
even when PWAN animation is available. Missing form battle members can freeze
the summary view, so generated fallbacks must live in pokegra_battle_extra and
not only in the transient VFS directory.
"""

from __future__ import annotations

import importlib.util
import json
import re
import shutil
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PORT = Path("/Users/andylee/Repos/Port-Pokeweb")
if not PORT.exists():
    PORT = ROOT.parent / "Port-Pokeweb"

TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"
ESSENTIALS_GIFS = PORT / "essentials_gifs"
ESSENTIALS_PNGS = PORT / "essentials_pngs"
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
VFS_BATTLE = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
BATTLE_EXTRA = ROOT / "data" / "graphics" / "pokegra_battle_extra"
REPORT = PWAN_DIR / "form_battle_staging_report.json"

FILES_PER_SPECIES = 20
CARRIER_SEED_BATTLE_BASE = 13060
SOURCE_STEM_RE = re.compile(r"sourceStem ([A-Z0-9_]+)")
ASSET_RE = re.compile(r"PWAN asset index (\d+)")


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


gen_import = load_module("gen8_gen9_import_helpers_for_forms", ROOT / "tools" / "pwan" / "import_essentials_gen8_gen9.py")
graphics = gen_import.graphics


def battle_path(index: int) -> Path:
    return VFS_BATTLE / str(index)


def battle_extra_path(index: int) -> Path:
    return BATTLE_EXTRA / f"004_{index:08d}.bin"


def pwan_path(asset: int, side: str) -> Path:
    return PWAN_DIR / f"{asset}_{side}.pwan"


def nonempty(path: Path) -> bool:
    return path.exists() and path.stat().st_size > 0


def source_paths(stem: str) -> dict[str, Path]:
    return {
        "front": ESSENTIALS_GIFS / "Front" / f"{stem}.gif",
        "back": ESSENTIALS_GIFS / "Back" / f"{stem}.gif",
        "frontShiny": ESSENTIALS_PNGS / "Front shiny" / f"{stem}.png",
        "backShiny": ESSENTIALS_PNGS / "Back shiny" / f"{stem}.png",
    }


def seed_battle_files(base: int) -> None:
    for offset in range(FILES_PER_SPECIES):
        source = battle_path(CARRIER_SEED_BATTLE_BASE + offset)
        if not source.exists():
            raise FileNotFoundError(source)
        target = battle_path(base + offset)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)


def patch_form_battle(row: dict, asset: int, stem: str) -> dict:
    base = int(row["battleSet"])
    if base != asset * FILES_PER_SPECIES:
        raise RuntimeError(f"{row['name']}: battleSet {base} does not match asset {asset}")

    seed_battle_files(base)
    paths = source_paths(stem)
    normal_sources = [paths[key] for key in ("front", "back") if paths[key].exists()]
    shiny_sources = [paths[key] for key in ("frontShiny", "backShiny") if paths[key].exists()]
    if not normal_sources:
        raise FileNotFoundError(f"{row['name']}: no normal source GIFs for {stem}")

    normal_palette = gen_import.collect_image_palette(normal_sources)
    shiny_palette = gen_import.collect_image_palette(shiny_sources) if shiny_sources else normal_palette
    patched_sides = []
    for side, compact_offsets, wide_offsets in (
        ("front", (0, 1), (2, 3)),
        ("back", (9, 10), (11, 12)),
    ):
        source_pwan = pwan_path(asset, side)
        if not source_pwan.exists():
            continue
        pixels = graphics.pwan_first_pixels(source_pwan)
        pixels = graphics.remap_pixels_to_palette(
            pixels,
            graphics.pwan_palette_values(source_pwan),
            normal_palette,
        )
        compact = graphics.segmented_pwan_pixels(pixels)
        wide = graphics.linear_wide_pwan_pixels(pixels)
        for offset in compact_offsets:
            path = battle_path(base + offset)
            if nonempty(path):
                graphics.patch_compressed_ncgr_payload(path, compact, "nlz11")
        for offset in wide_offsets:
            path = battle_path(base + offset)
            if nonempty(path):
                graphics.patch_compressed_ncgr_payload(path, wide, "nlz11")
        patched_sides.append(side)

    gen_import.patch_nclr_file(battle_path(base + 18), normal_palette)
    gen_import.patch_nclr_file(battle_path(base + 19), shiny_palette)
    BATTLE_EXTRA.mkdir(parents=True, exist_ok=True)
    for offset in range(FILES_PER_SPECIES):
        shutil.copy2(battle_path(base + offset), battle_extra_path(base + offset))

    return {
        "key": row.get("key"),
        "name": row.get("name"),
        "assetIndex": asset,
        "battleSet": base,
        "sourceStem": stem,
        "patchedSides": patched_sides,
        "shinyPalette": bool(shiny_sources),
    }


def main() -> int:
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    staged = []
    errors = []
    for row in rows:
        if row.get("kind") not in {"regional form", "alternate form"}:
            continue
        notes = row.get("runtimeNotes", "")
        stem_match = SOURCE_STEM_RE.search(notes)
        asset_match = ASSET_RE.search(notes)
        if not stem_match or not asset_match:
            errors.append({"key": row.get("key"), "name": row.get("name"), "error": "missing sourceStem or asset note"})
            continue
        try:
            staged.append(patch_form_battle(row, int(asset_match.group(1)), stem_match.group(1)))
        except Exception as exc:  # noqa: BLE001 - report all broken rows.
            errors.append({"key": row.get("key"), "name": row.get("name"), "error": str(exc)})

    report = {
        "version": 1,
        "staged": staged,
        "errors": errors,
    }
    REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"Staged {len(staged)} form battle fallback set(s); errors={len(errors)}.")
    print(f"Wrote {REPORT}")
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
