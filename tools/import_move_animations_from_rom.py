#!/usr/bin/env python3
"""Import move animation script members from a donor ROM.

White2Upgrade routes Gen 6 move animations through per-move members in
`a/0/6/5`: member N is the animation script for move ID N. Donor hacks often
replace vanilla move slots with newer moves, so this tool copies a source
vanilla move member from the donor archive into a target W2U move member.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

import ndspy.narc
import ndspy.rom


DEFAULT_MAP = Path("data/graphics/move_animations/import_maps/bb2redex14.json")
DEFAULT_ARCHIVE = "/a/0/6/5"


def normalized_name(value: str) -> str:
    value = value.replace("Vise", "Vice")
    value = value.replace("Smelling Salts", "SmellingSalt")
    return re.sub(r"[^a-z0-9]", "", value.lower())


def load_move_names(move_text_path: Path) -> dict[str, int]:
    names: dict[str, int] = {}
    for move_id, line in enumerate(move_text_path.read_text().splitlines()):
        name = line.strip()
        if not name:
            continue
        names[normalized_name(name)] = move_id
    return names


def load_mapping(path: Path) -> tuple[str, str, list[tuple[str, str]]]:
    raw = json.loads(path.read_text())
    source_name = raw.get("source", path.stem)
    archive = raw.get("archive", DEFAULT_ARCHIVE)
    mapping = raw.get("replacementMap", raw.get("moves", raw))

    if isinstance(mapping, dict):
        pairs = list(mapping.items())
    elif isinstance(mapping, list):
        pairs = []
        for entry in mapping:
            pairs.append((entry["source"], entry["target"]))
    else:
        raise TypeError(f"Unsupported mapping shape in {path}")

    return source_name, archive, pairs


def load_implemented_tracker_moves(path: Path | None) -> set[int]:
    if path is None:
        return set()

    raw = json.loads(path.read_text())
    rows = raw if isinstance(raw, list) else raw.get("moves", [])
    implemented: set[int] = set()
    for row in rows:
        if not isinstance(row, dict):
            continue
        if row.get("defaultProgress", {}).get("animation") is True and row.get("id") is not None:
            implemented.add(int(row["id"]))
    return implemented


def resolve_move(name_to_id: dict[str, int], move_name: str) -> int | None:
    return name_to_id.get(normalized_name(move_name))


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    repo_root = Path(__file__).resolve().parents[1]
    parser.add_argument(
        "--repo-root",
        type=Path,
        default=repo_root,
        help="White2Upgrade repo root.",
    )
    parser.add_argument(
        "--donor-rom",
        type=Path,
        default=repo_root.parent / "bb2redex14.nds",
        help="Donor NDS containing replacement move animations.",
    )
    parser.add_argument(
        "--mapping-json",
        type=Path,
        default=repo_root / DEFAULT_MAP,
        help="JSON replacement map from donor move name to target move name.",
    )
    parser.add_argument(
        "--dest-dir",
        type=Path,
        default=repo_root / "data/graphics/move_animations",
        help="Destination directory for W2U move animation override members.",
    )
    parser.add_argument(
        "--move-text",
        type=Path,
        default=repo_root / "tools/helpers/txtdmp/Moves.txt",
        help="Move-name text file used to resolve move IDs.",
    )
    parser.add_argument(
        "--min-target-id",
        type=int,
        default=560,
        help="Lowest target move ID to import.",
    )
    parser.add_argument(
        "--max-target-id",
        type=int,
        default=621,
        help="Highest target move ID to import.",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print the planned copies without writing files.",
    )
    parser.add_argument(
        "--skip-implemented-tracker",
        type=Path,
        help="Skip target moves already marked with defaultProgress.animation=true in a tracker seed JSON.",
    )
    parser.add_argument(
        "--only-target-id",
        type=int,
        action="append",
        default=[],
        help="Only import mappings whose resolved target move ID matches this value. May be repeated.",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="Fail if a mapping entry cannot be resolved or imported.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    source_label, archive_path, mapping = load_mapping(args.mapping_json)
    name_to_id = load_move_names(args.move_text)
    implemented_targets = load_implemented_tracker_moves(args.skip_implemented_tracker)
    only_target_ids = set(args.only_target_id)

    donor_rom = ndspy.rom.NintendoDSRom.fromFile(str(args.donor_rom))
    donor_narc = ndspy.narc.NARC(donor_rom.getFileByName(archive_path))

    imported: list[str] = []
    skipped: list[str] = []
    errors: list[str] = []

    for source_name, target_name in mapping:
        source_id = resolve_move(name_to_id, source_name)
        target_id = resolve_move(name_to_id, target_name)

        if target_id is None:
            skipped.append(f"{source_name} -> {target_name}: target not in W2U move table")
            continue
        if only_target_ids and target_id not in only_target_ids:
            skipped.append(f"{source_name} -> {target_name}: target ID {target_id} not requested")
            continue
        if not (args.min_target_id <= target_id <= args.max_target_id):
            skipped.append(f"{source_name} -> {target_name}: target ID {target_id} outside range")
            continue
        if target_id in implemented_targets:
            skipped.append(f"{source_name} -> {target_name}: target ID {target_id} already implemented")
            continue
        if source_id is None:
            message = f"{source_name} -> {target_name}: source not in W2U move table"
            errors.append(message)
            continue
        if source_id >= len(donor_narc.files):
            message = f"{source_name} -> {target_name}: donor member {source_id} missing"
            errors.append(message)
            continue

        dest_path = args.dest_dir / f"5_{target_id:08d}.bin"
        source_bytes = bytes(donor_narc.files[source_id])
        action = "would import" if args.dry_run else "imported"
        imported.append(
            f"{action} {source_label}: {source_name} #{source_id} -> "
            f"{target_name} #{target_id} ({len(source_bytes)} bytes)"
        )
        if not args.dry_run:
            dest_path.parent.mkdir(parents=True, exist_ok=True)
            dest_path.write_bytes(source_bytes)

    for line in imported:
        print(line)
    for line in skipped:
        print(f"skipped: {line}")
    for line in errors:
        print(f"error: {line}")

    print(f"summary: imported={len(imported)} skipped={len(skipped)} errors={len(errors)}")
    if errors and args.strict:
        return 1
    if args.strict and not imported:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
