#!/usr/bin/env python3
"""Import move animation script members from a donor ROM.

White2Upgrade routes implemented expansion moves through per-move members in
`a/0/6/5`: member N is the animation script for move ID N. Donor hacks often
replace vanilla move slots with newer moves, so this tool copies a source
vanilla move member from the donor archive into a target W2U move member.
"""

from __future__ import annotations

import argparse
import json
import re
import struct
from pathlib import Path

import ndspy.narc
import ndspy.rom


DEFAULT_MAP = Path("data/graphics/move_animations/import_maps/bb2redex14.json")
DEFAULT_ARCHIVE = "/a/0/6/5"
NORMALIZED_NAME_ALIASES = {
    # The Gen V name table and donor replacement lists do not always use the
    # same spelling, especially for names shortened to fit the original UI.
    "visegrip": "vicegrip",
    "smellingsalts": "smellingsalt",
    "1stimpression": "firstimpression",
    "stompintantrum": "stompingtantrum",
}


def normalized_name(value: str) -> str:
    normalized = re.sub(r"[^a-z0-9]", "", value.lower())
    return NORMALIZED_NAME_ALIASES.get(normalized, normalized)


def load_move_names(move_text_path: Path) -> dict[str, int]:
    names: dict[str, int] = {}
    for move_id, line in enumerate(move_text_path.read_text().splitlines()):
        name = line.strip()
        if not name:
            continue
        names[normalized_name(name)] = move_id
    return names


def load_mapping(
    path: Path,
) -> tuple[str, str, list[tuple[str, str]], str | None, list[dict[str, object]]]:
    raw = json.loads(path.read_text())
    source_name = raw.get("source", path.stem)
    archive = raw.get("archive", DEFAULT_ARCHIVE)
    mapping = raw.get("replacementMap", raw.get("moves", raw))
    particle_archive = raw.get("particleArchive")
    particle_remaps = raw.get("particleRemaps", [])

    if isinstance(mapping, dict):
        pairs = list(mapping.items())
    elif isinstance(mapping, list):
        pairs = []
        for entry in mapping:
            pairs.append((entry["source"], entry["target"]))
    else:
        raise TypeError(f"Unsupported mapping shape in {path}")

    if not isinstance(particle_remaps, list):
        raise TypeError(f"particleRemaps must be a list in {path}")

    return source_name, archive, pairs, particle_archive, particle_remaps


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
        "--particle-dest-dir",
        type=Path,
        default=repo_root / "data/graphics/move_spas",
        help="Destination directory for remapped donor SPA members.",
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
    source_label, archive_path, mapping, particle_archive_path, particle_remaps = load_mapping(
        args.mapping_json
    )
    name_to_id = load_move_names(args.move_text)
    implemented_targets = load_implemented_tracker_moves(args.skip_implemented_tracker)
    only_target_ids = set(args.only_target_id)

    donor_rom = ndspy.rom.NintendoDSRom.fromFile(str(args.donor_rom))
    donor_narc = ndspy.narc.NARC(donor_rom.getFileByName(archive_path))
    donor_particle_narc = None
    if particle_remaps:
        if not particle_archive_path:
            raise ValueError("particleArchive is required when particleRemaps are present")
        donor_particle_narc = ndspy.narc.NARC(
            donor_rom.getFileByName(str(particle_archive_path))
        )

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

        action = "would import" if args.dry_run else "imported"
        source_bytes = bytes(donor_narc.files[source_id])
        matching_particle_remaps = [
            entry
            for entry in particle_remaps
            if normalized_name(str(entry.get("target", ""))) == normalized_name(target_name)
        ]
        for entry in matching_particle_remaps:
            source_particle_id = int(entry["sourceId"])
            target_particle_id = int(entry["targetId"])
            expected_references = int(entry.get("expectedReferences", 0))
            source_word = struct.pack("<I", source_particle_id)
            reference_count = source_bytes.count(source_word)
            if expected_references and reference_count != expected_references:
                errors.append(
                    f"{source_name} -> {target_name}: SPA {source_particle_id} has "
                    f"{reference_count} references, expected {expected_references}"
                )
                continue
            if reference_count == 0:
                errors.append(
                    f"{source_name} -> {target_name}: SPA {source_particle_id} is not referenced"
                )
                continue
            if donor_particle_narc is None or source_particle_id >= len(donor_particle_narc.files):
                errors.append(
                    f"{source_name} -> {target_name}: donor SPA {source_particle_id} missing"
                )
                continue

            source_bytes = source_bytes.replace(
                source_word,
                struct.pack("<I", target_particle_id),
            )
            particle_dest = args.particle_dest_dir / f"6_{target_particle_id:08d}.bin"
            imported.append(
                f"{action} {source_label}: SPA {source_particle_id} -> "
                f"SPA {target_particle_id} ({len(donor_particle_narc.files[source_particle_id])} bytes)"
            )
            if not args.dry_run:
                particle_dest.parent.mkdir(parents=True, exist_ok=True)
                particle_dest.write_bytes(bytes(donor_particle_narc.files[source_particle_id]))

        if any(
            line.startswith(f"{source_name} -> {target_name}:")
            for line in errors
        ):
            continue

        dest_path = args.dest_dir / f"5_{target_id:08d}.bin"
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
