#!/usr/bin/env python3
"""Ground imported PWAN sprites against Scatterbug's current floor.

The script shifts each eligible PWAN side by one vertical delta computed from
the lowest opaque pixel across the whole animation. The same delta is applied
to every frame in that side, preserving the original idle motion.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import struct
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path
from typing import Any
from report_paths import write_report


ROOT = Path(__file__).resolve().parents[2]
PORT = Path(os.environ.get("POKEWEB_SOURCE_ROOT", ROOT.parent / "pokeweb-source"))

PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG_PATH = PWAN_DIR / "config.bin"
REPORT_PATH = PWAN_DIR / "pwan_grounding_report.json"
PML_ROOT = ROOT / "data" / "pml"
SPECIES_HEADER = ROOT / "include" / "species_ids.h"
TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"
SPECIES_NAMES = PORT / "reference_repos" / "PKHeX" / "PKHeX.Core" / "Resources" / "text" / "other" / "en" / "text_Species_en.txt"
SHOWDOWN_SPECIES = PORT / "reference_repos" / "Pokeweb-Live" / "public" / "dist" / "calc" / "data" / "species.js"

MAGIC = b"PWAN"
WIDTH = 96
HEIGHT = 96
FRAME_BYTES = 0x1200
LEVITATE_ABILITY = 26

PWAN_HEADER = struct.Struct("<4sHHHHHHIIIIII")
PWAN_NAME_RE = re.compile(r"^(\d+)_(front|back)\.pwan$")
ASSET_NOTE_RE = re.compile(r"PWAN asset index (\d+)")
SOURCE_STEM_RE = re.compile(r"sourceStem ([A-Z0-9_]+)")

SEGMENTS = (
    (0, 0, 64, 64),
    (64, 0, 32, 64),
    (0, 64, 64, 32),
    (64, 64, 32, 32),
)

EXPLICIT_FLOATING_OR_WATER = {
    "floette",
    "inkay",
    "skrelp",
    "hoopa",
    "vikavolt",
    "wishiwashi",
    "wishiwashischool",
    "minior",
    "miniorred",
    "miniormeteor",
    "cosmog",
    "cosmoem",
    "kartana",
    "flapple",
    "arrokuda",
    "barraskewda",
    "frosmoth",
    "eternatus",
    "veluza",
    "fluttermane",
}

FISH_OR_WATER_SUSPENDED = {
    "basculin",
    "basculinbluestriped",
    "basculinwhitestriped",
    "basculegion",
    "basculegionfemale",
    "bruxish",
    "clauncher",
    "clawitzer",
    "dondozo",
    "dragalge",
    "finizen",
    "palafin",
    "palafinhero",
    "qwilfish",
    "qwilfishhisui",
    "overqwil",
    "tatsugiri",
    "tatsugiridroopy",
    "tatsugiristretchy",
}

GROUNDED_FLYING_OVERRIDES = {
    "pikipek",
    "trumbeak",
    "trumpeak",
    "oricorio",
    "oricoriobaile",
    "oricoriopompom",
    "oricoriopau",
    "oricoriosensu",
    "rookidee",
    "squawkabilly",
    "squawkabillyblue",
    "squawkabillyyellow",
    "squawkabillywhite",
    "squakably",
}


@dataclass(frozen=True)
class PwanHeader:
    magic: bytes
    version: int
    width: int
    height: int
    bpp: int
    frame_count: int
    timeline_count: int
    total_ticks: int
    frame_bytes: int
    palette_colors: int
    palette_offset: int
    timeline_offset: int
    frame_offset: int


@dataclass(frozen=True)
class PersonalMeta:
    personal_id: int
    path: Path
    types: tuple[str, ...]
    abilities: tuple[int, ...]


def to_id(value: str | None) -> str:
    return re.sub(r"[^a-z0-9]+", "", (value or "").lower())


def read_pwan(path: Path) -> tuple[PwanHeader, list[list[int]], bytes]:
    data = path.read_bytes()
    values = PWAN_HEADER.unpack_from(data, 0)
    header = PwanHeader(*values)
    if header.magic != MAGIC:
        raise ValueError(f"{path} is not a PWAN file")
    if header.width != WIDTH or header.height != HEIGHT or header.bpp != 4:
        raise ValueError(f"{path} has unsupported geometry {header.width}x{header.height} {header.bpp}bpp")
    if header.frame_bytes != FRAME_BYTES:
        raise ValueError(f"{path} has frame byte size {header.frame_bytes}, expected {FRAME_BYTES}")
    frames = [
        decode_frame(data[header.frame_offset + i * header.frame_bytes:header.frame_offset + (i + 1) * header.frame_bytes])
        for i in range(header.frame_count)
    ]
    return header, frames, data


def decode_frame(data: bytes) -> list[int]:
    if len(data) != FRAME_BYTES:
        raise ValueError(f"frame is {len(data)} bytes, expected {FRAME_BYTES}")
    pixels = [0] * (WIDTH * HEIGHT)
    cursor = 0
    for x0, y0, width, height in SEGMENTS:
        for tile_y in range(0, height, 8):
            for tile_x in range(0, width, 8):
                for y in range(8):
                    for x in range(0, 8, 2):
                        byte = data[cursor]
                        cursor += 1
                        dst = (y0 + tile_y + y) * WIDTH + x0 + tile_x + x
                        pixels[dst] = byte & 0x0F
                        pixels[dst + 1] = byte >> 4
    return pixels


def encode_frame(pixels: list[int]) -> bytes:
    if len(pixels) != WIDTH * HEIGHT:
        raise ValueError(f"frame has {len(pixels)} pixels, expected {WIDTH * HEIGHT}")
    out = bytearray()
    for x0, y0, width, height in SEGMENTS:
        for tile_y in range(0, height, 8):
            for tile_x in range(0, width, 8):
                for y in range(8):
                    for x in range(0, 8, 2):
                        src = (y0 + tile_y + y) * WIDTH + x0 + tile_x + x
                        out.append((pixels[src] & 0x0F) | ((pixels[src + 1] & 0x0F) << 4))
    if len(out) != FRAME_BYTES:
        raise ValueError(f"encoded frame is {len(out)} bytes, expected {FRAME_BYTES}")
    return bytes(out)


def animation_bounds(frames: list[list[int]]) -> dict[str, int | None]:
    min_x = WIDTH
    min_y = HEIGHT
    max_x = -1
    max_y = -1
    pixels = 0
    for frame in frames:
        for index, value in enumerate(frame):
            if value == 0:
                continue
            x = index % WIDTH
            y = index // WIDTH
            min_x = min(min_x, x)
            min_y = min(min_y, y)
            max_x = max(max_x, x)
            max_y = max(max_y, y)
            pixels += 1
    if max_y < 0:
        return {"minX": None, "minY": None, "maxX": None, "maxY": None, "pixels": 0}
    return {"minX": min_x, "minY": min_y, "maxX": max_x, "maxY": max_y, "pixels": pixels}


def shift_frame(frame: list[int], delta_y: int) -> tuple[list[int], int]:
    if delta_y == 0:
        return frame[:], 0
    shifted = [0] * (WIDTH * HEIGHT)
    clipped = 0
    for y in range(HEIGHT):
        dst_y = y + delta_y
        for x in range(WIDTH):
            value = frame[y * WIDTH + x]
            if value == 0:
                continue
            if 0 <= dst_y < HEIGHT:
                shifted[dst_y * WIDTH + x] = value
            else:
                clipped += 1
    return shifted, clipped


def write_shifted_pwan(path: Path, target_floor: int, *, dry_run: bool) -> dict[str, Any]:
    header, frames, data = read_pwan(path)
    before = animation_bounds(frames)
    if before["maxY"] is None:
        return {"path": str(path), "status": "empty", "deltaY": 0, "before": before, "after": before, "clippedPixels": 0}

    delta_y = int(target_floor) - int(before["maxY"])
    if delta_y == 0:
        return {"path": str(path), "status": "already-grounded", "deltaY": 0, "before": before, "after": before, "clippedPixels": 0}

    shifted_frames: list[list[int]] = []
    clipped = 0
    for frame in frames:
        shifted, frame_clipped = shift_frame(frame, delta_y)
        shifted_frames.append(shifted)
        clipped += frame_clipped
    after = animation_bounds(shifted_frames)

    if not dry_run:
        out = bytearray(data)
        cursor = header.frame_offset
        for frame in shifted_frames:
            out[cursor:cursor + header.frame_bytes] = encode_frame(frame)
            cursor += header.frame_bytes
        path.write_bytes(bytes(out))

    return {
        "path": str(path),
        "status": "shifted",
        "deltaY": delta_y,
        "before": before,
        "after": after,
        "clippedPixels": clipped,
    }


def load_species_defines() -> tuple[dict[int, str], dict[str, int]]:
    id_to_const: dict[int, str] = {}
    const_to_id: dict[str, int] = {}
    pattern = re.compile(r"^#define\s+(SPECIES_[A-Z0-9_]+)\s+(\d+)\b")
    for line in SPECIES_HEADER.read_text(encoding="utf-8").splitlines():
        match = pattern.match(line)
        if not match:
            continue
        const = match.group(1)
        species_id = int(match.group(2))
        id_to_const[species_id] = const
        const_to_id[const] = species_id
    return id_to_const, const_to_id


def load_personal_paths(const_to_id: dict[str, int]) -> dict[int, Path]:
    paths: dict[int, Path] = {}
    for path in PML_ROOT.glob("*/personal.toml"):
        first = path.read_text(encoding="utf-8").splitlines()[0].strip()
        match = re.match(r"\[(SPECIES_[A-Z0-9_]+)\]", first)
        if not match:
            continue
        const = match.group(1)
        if const in const_to_id:
            paths[const_to_id[const]] = path
            continue
        numeric = re.match(r"SPECIES_(\d+)$", const)
        if numeric:
            paths[int(numeric.group(1))] = path
    return paths


def load_personal(path: Path) -> dict[str, Any]:
    data = tomllib.loads(path.read_text(encoding="utf-8"))
    if len(data) != 1:
        raise ValueError(f"{path} is not a single-root personal TOML")
    return next(iter(data.values()))


def personal_id_for_entry(species: int, form: int, personal_paths: dict[int, Path]) -> int:
    if form == 0:
        return species
    base_path = personal_paths.get(species)
    if not base_path:
        return species
    fields = load_personal(base_path)
    form_data_offset = int(fields.get("Form Data Offset", 0) or 0)
    if form_data_offset <= 0:
        return species
    return form_data_offset + form - 1


def personal_meta_for_entry(species: int, form: int, personal_paths: dict[int, Path]) -> PersonalMeta | None:
    personal_id = personal_id_for_entry(species, form, personal_paths)
    path = personal_paths.get(personal_id)
    if not path:
        path = PML_ROOT / str(personal_id) / "personal.toml"
    if not path.exists():
        return None
    fields = load_personal(path)
    types = tuple(
        str(fields.get(key, "")).replace("TYPE_", "").title()
        for key in ("Primary Type", "Secondary Type")
        if fields.get(key)
    )
    abilities = tuple(
        int(fields.get(key, 0) or 0)
        for key in ("Primary Ability", "Secondary Ability", "Hidden Ability")
    )
    return PersonalMeta(personal_id=personal_id, path=path, types=types, abilities=abilities)


def load_species_names() -> dict[int, str]:
    if not SPECIES_NAMES.exists():
        return {}
    return {index: name for index, name in enumerate(SPECIES_NAMES.read_text(encoding="utf-8").splitlines())}


def load_tracker_rows() -> tuple[dict[int, dict[str, Any]], dict[int, list[dict[str, Any]]]]:
    if not TRACKER.exists():
        return {}, {}
    rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    by_id: dict[int, dict[str, Any]] = {}
    by_asset: dict[int, list[dict[str, Any]]] = {}
    for row in rows:
        try:
            by_id[int(row.get("id"))] = row
        except (TypeError, ValueError):
            pass
        note = row.get("runtimeNotes", "")
        match = ASSET_NOTE_RE.search(note)
        if match:
            by_asset.setdefault(int(match.group(1)), []).append(row)
    return by_id, by_asset


def load_showdown_metadata() -> dict[str, dict[str, Any]]:
    if not SHOWDOWN_SPECIES.exists():
        return {}
    js = """
const species = require(process.argv[1]).SPECIES;
const latest = species[species.length - 1];
const out = {};
for (const [name, data] of Object.entries(latest)) {
  out[name] = {
    types: data.types || [],
    abilities: Object.values(data.abilities || {}).filter(Boolean),
    baseSpecies: data.baseSpecies || null
  };
}
console.log(JSON.stringify(out));
"""
    try:
        result = subprocess.run(
            ["node", "-e", js, str(SHOWDOWN_SPECIES)],
            cwd=ROOT,
            text=True,
            capture_output=True,
            check=True,
            timeout=20,
        )
    except (FileNotFoundError, subprocess.CalledProcessError, subprocess.TimeoutExpired):
        return {}

    raw = json.loads(result.stdout)
    return {to_id(name): {"name": name, **data} for name, data in raw.items()}


def source_stem(row: dict[str, Any] | None) -> str | None:
    if not row:
        return None
    match = SOURCE_STEM_RE.search(row.get("runtimeNotes", ""))
    return match.group(1) if match else None


def metadata_candidate_ids(name: str, stem: str | None = None) -> list[str]:
    candidates: list[str] = []

    def add(value: str | None) -> None:
        key = to_id(value)
        if key and key not in candidates:
            candidates.append(key)

    add(name)
    add(stem)
    if stem:
        add(stem.replace("_", " "))

    words_to_remove = (
        " Forme",
        " Form",
        " Mode",
        " Face",
        " Plumage",
        " Breed",
        " Mask",
        " Style",
    )
    simplified = name
    for word in words_to_remove:
        simplified = simplified.replace(word, "")
    add(simplified)

    regional_prefixes = {
        "Alolan ": "Alola",
        "Galarian ": "Galar",
        "Hisuian ": "Hisui",
        "Paldean ": "Paldea",
    }
    for prefix, suffix in regional_prefixes.items():
        if name.startswith(prefix):
            base = name[len(prefix):]
            add(f"{base}-{suffix}")
            add(f"{base} {suffix}")
            if "Tauros" in base:
                if "Blaze" in base:
                    add("Tauros-Paldea-Blaze")
                elif "Aqua" in base:
                    add("Tauros-Paldea-Aqua")
                elif "Combat" in base:
                    add("Tauros-Paldea-Combat")

    if name.startswith("Mega "):
        base = name[len("Mega "):]
        if base.endswith(" X") or base.endswith(" Y"):
            suffix = base[-1]
            base = base[:-2]
            add(f"{base}-Mega-{suffix}")
            add(f"{base} Mega {suffix}")
        else:
            add(f"{base}-Mega")
            add(f"{base} Mega")

    if name.startswith("Primal "):
        base = name[len("Primal "):]
        add(f"{base}-Primal")

    replacements = {
        "Crowned Sword": "Crowned",
        "Crowned Shield": "Crowned",
        "Rapid Strike Style": "Rapid-Strike",
        "Family of Three": "Three",
        "Noice Face": "Noice",
        "Hangry Mode": "Hangry",
        "Hero Form": "Hero",
        "Roaming Form": "Roaming",
    }
    for old, new in replacements.items():
        if old in name:
            add(name.replace(old, new))

    return candidates


def ids_match_any(ids: set[str], patterns: set[str]) -> bool:
    for candidate in ids:
        for pattern in patterns:
            if candidate == pattern or candidate.endswith(pattern) or pattern in candidate:
                return True
    return False


def choose_tracker_row(rows: list[dict[str, Any]]) -> dict[str, Any] | None:
    if not rows:
        return None
    preferred_kinds = ("regional form", "alternate form", "mega form", "base species")
    for kind in preferred_kinds:
        for row in rows:
            if row.get("kind") == kind:
                return row
    return rows[0]


def choose_representative(
    asset: int,
    entries: list[tuple[int, int]],
    tracker_by_asset: dict[int, list[dict[str, Any]]],
    tracker_by_id: dict[int, dict[str, Any]],
    personal_paths: dict[int, Path],
    species_names: dict[int, str],
) -> dict[str, Any]:
    asset_row = choose_tracker_row(tracker_by_asset.get(asset, []))
    if asset_row:
        return {
            "species": asset_row.get("baseSpecies", asset_row.get("id")),
            "form": None,
            "personalId": asset_row.get("id"),
            "name": asset_row.get("name", f"asset {asset}"),
            "trackerRowId": asset_row.get("id"),
            "sourceStem": source_stem(asset_row),
            "kind": asset_row.get("kind"),
            "source": "tracker asset note",
        }

    ordered = sorted(entries, key=lambda key: (0 if key[1] else 1, 0 if key[0] >= 650 else 1, key[0], key[1]))
    species, form = ordered[0]
    personal_id = personal_id_for_entry(species, form, personal_paths)
    row = tracker_by_id.get(personal_id)
    name = row.get("name") if row else species_names.get(species, f"species {species}")
    return {
        "species": species,
        "form": form,
        "personalId": personal_id,
        "name": name,
        "trackerRowId": row.get("id") if row else None,
        "sourceStem": source_stem(row),
        "kind": row.get("kind") if row else None,
        "source": "pwan config",
    }


def lookup_showdown_meta(name: str, stem: str | None, showdown: dict[str, dict[str, Any]]) -> tuple[dict[str, Any] | None, list[str]]:
    candidates = metadata_candidate_ids(name, stem)
    for candidate in candidates:
        if candidate in showdown:
            return showdown[candidate], candidates
    return None, candidates


def should_ground(
    representative: dict[str, Any],
    personal: PersonalMeta | None,
    showdown: dict[str, dict[str, Any]],
) -> tuple[bool, str, dict[str, Any]]:
    name = str(representative.get("name", ""))
    name_id = to_id(name)
    stem = representative.get("sourceStem")
    stem_id = to_id(stem)

    meta, candidates = lookup_showdown_meta(name, stem, showdown)
    types = tuple(meta.get("types", ())) if meta else tuple(personal.types if personal else ())
    abilities = tuple(meta.get("abilities", ())) if meta else tuple(personal.abilities if personal else ())
    meta_source = "showdown species.js" if meta else ("personal TOML" if personal else "none")

    all_ids = {name_id, stem_id, *candidates}
    if any(value.startswith("tapu") for value in all_ids):
        return False, "explicit floating exception: Tapu", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    if ids_match_any(all_ids, EXPLICIT_FLOATING_OR_WATER):
        return False, "explicit floating/water exception", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    if ids_match_any(all_ids, FISH_OR_WATER_SUSPENDED):
        return False, "fish/water-suspended exception", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}

    grounded_override = ids_match_any(all_ids, GROUNDED_FLYING_OVERRIDES)
    normalized_types = {to_id(type_name) for type_name in types}
    normalized_abilities = {to_id(str(ability)) for ability in abilities}

    if "ghost" in normalized_types:
        return False, "Ghost type", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    if "flying" in normalized_types and not grounded_override:
        return False, "Flying type", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    if "levitate" in normalized_abilities or (personal and LEVITATE_ABILITY in personal.abilities):
        return False, "Levitate ability", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    if not meta and not personal:
        return False, "missing metadata", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    if grounded_override:
        return True, "grounded Flying override", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}
    return True, "eligible", {"types": types, "abilities": abilities, "metadataSource": meta_source, "candidateIds": candidates}


def parse_pwan_config(path: Path) -> dict[tuple[int, int], dict[str, int]]:
    sys.path.insert(0, str(ROOT / "tools" / "pwan"))
    from pwan_config import parse_config  # noqa: PLC0415

    entries, _max_timeline = parse_config(path)
    return entries


def collect_asset_entries(entries: dict[tuple[int, int], dict[str, int]]) -> dict[int, list[tuple[int, int]]]:
    assets: dict[int, list[tuple[int, int]]] = {}
    for key, entry in entries.items():
        assets.setdefault(int(entry["assetIndex"]), []).append(key)
    return assets


def reference_floor(reference_asset: int, sides: tuple[str, ...]) -> dict[str, Any]:
    side_reports = []
    floors = []
    for side in sides:
        path = PWAN_DIR / f"{reference_asset}_{side}.pwan"
        if not path.exists():
            continue
        _header, frames, _data = read_pwan(path)
        bounds = animation_bounds(frames)
        side_reports.append({"side": side, "path": str(path), "bounds": bounds})
        if bounds["maxY"] is not None:
            floors.append(int(bounds["maxY"]))
    if not floors:
        raise RuntimeError(f"reference asset {reference_asset} has no measurable PWAN side")
    return {"asset": reference_asset, "floorY": max(floors), "sides": side_reports}


def main() -> int:
    global PWAN_DIR

    parser = argparse.ArgumentParser(description="Ground eligible imported PWAN assets to Scatterbug's floor.")
    parser.add_argument("--pwan-dir", type=Path, default=PWAN_DIR)
    parser.add_argument("--config", type=Path, default=CONFIG_PATH)
    parser.add_argument("--report", type=Path, default=REPORT_PATH)
    parser.add_argument("--reference-asset", type=int, default=664)
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--asset", type=int, action="append", help="limit to one PWAN asset index; may be repeated")
    args = parser.parse_args()

    PWAN_DIR = args.pwan_dir

    entries = parse_pwan_config(args.config)
    assets = collect_asset_entries(entries)
    if args.asset:
        wanted = set(args.asset)
        assets = {asset: value for asset, value in assets.items() if asset in wanted}

    _id_to_const, const_to_id = load_species_defines()
    personal_paths = load_personal_paths(const_to_id)
    species_names = load_species_names()
    tracker_by_id, tracker_by_asset = load_tracker_rows()
    showdown = load_showdown_metadata()
    reference = reference_floor(args.reference_asset, ("front", "back"))
    target_floor = int(reference["floorY"])

    shifted: list[dict[str, Any]] = []
    skipped: list[dict[str, Any]] = []
    errors: list[dict[str, Any]] = []

    for asset in sorted(assets):
        representative = choose_representative(
            asset,
            assets[asset],
            tracker_by_asset,
            tracker_by_id,
            personal_paths,
            species_names,
        )
        personal = None
        if isinstance(representative.get("species"), int) and isinstance(representative.get("form"), int):
            personal = personal_meta_for_entry(representative["species"], representative["form"], personal_paths)
        elif isinstance(representative.get("personalId"), int):
            personal_path = personal_paths.get(representative["personalId"]) or PML_ROOT / str(representative["personalId"]) / "personal.toml"
            if personal_path.exists():
                fields = load_personal(personal_path)
                personal = PersonalMeta(
                    personal_id=representative["personalId"],
                    path=personal_path,
                    types=tuple(str(fields.get(key, "")).replace("TYPE_", "").title() for key in ("Primary Type", "Secondary Type") if fields.get(key)),
                    abilities=tuple(int(fields.get(key, 0) or 0) for key in ("Primary Ability", "Secondary Ability", "Hidden Ability")),
                )

        eligible, reason, metadata = should_ground(representative, personal, showdown)
        if not eligible:
            skipped.append({
                "assetIndex": asset,
                "entries": assets[asset],
                "representative": representative,
                "reason": reason,
                **metadata,
            })
            continue

        asset_result = {
            "assetIndex": asset,
            "entries": assets[asset],
            "representative": representative,
            "reason": reason,
            **metadata,
            "sides": [],
        }
        for side in ("front", "back"):
            side_path = PWAN_DIR / f"{asset}_{side}.pwan"
            if not side_path.exists():
                continue
            try:
                side_result = write_shifted_pwan(side_path, target_floor, dry_run=args.dry_run)
                side_result["side"] = side
                asset_result["sides"].append(side_result)
            except Exception as exc:  # keep processing other assets for a useful report
                errors.append({
                    "assetIndex": asset,
                    "side": side,
                    "path": str(side_path),
                    "representative": representative,
                    "error": str(exc),
                })
        if asset_result["sides"]:
            shifted.append(asset_result)

    shifted_sides = [
        side
        for asset in shifted
        for side in asset["sides"]
        if side["status"] == "shifted"
    ]
    report = {
        "version": 1,
        "dryRun": args.dry_run,
        "reference": reference,
        "targetFloorY": target_floor,
        "assetCountConsidered": len(assets),
        "assetsWithShiftedSides": sum(1 for asset in shifted if any(side["status"] == "shifted" for side in asset["sides"])),
        "shiftedSideCount": len(shifted_sides),
        "skippedAssetCount": len(skipped),
        "errorCount": len(errors),
        "shifted": shifted,
        "skipped": skipped,
        "errors": errors,
    }
    args.report.parent.mkdir(parents=True, exist_ok=True)
    write_report(args.report, report)

    print(
        f"{'Would shift' if args.dry_run else 'Shifted'} {len(shifted_sides)} side(s) "
        f"across {report['assetsWithShiftedSides']} asset(s); skipped {len(skipped)} asset(s); "
        f"errors {len(errors)}. Report: {args.report}"
    )
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
