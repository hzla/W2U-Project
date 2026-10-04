#!/usr/bin/env python3
"""Build the deterministic Black2Upgrade V1 data package from clean IREO.

Common gameplay tables are complete expanded replacements.  Graphics and text
use a three-way merge (clean W2, authored W2U, clean B2), so untouched B2
members and messages stay byte-identical to Black 2.
"""

from __future__ import annotations

import argparse
import csv
import gzip
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import shutil
import sys
import tarfile
from typing import Any

import ndspy.codeCompression
import ndspy.narc
import ndspy.rom


BASE_B2_SHA256 = "2e6b2415354aa41471bc7617068dce059a59931bf5c4348a264f8043f297683a"
RUNTIME_ABI = 1
DATA_VERSION = 1

FULL_REPLACEMENTS = (
    "a/0/1/6",  # personal/form records
    "a/0/1/8",  # learnsets
    "a/0/1/9",  # evolutions
    "a/0/2/1",  # moves
    "a/0/2/4",  # items
)

AUTHORED_MEMBER_OVERLAYS = (
    "a/0/0/6",  # SPA
    "a/0/0/7",  # Pokémon icons
    "a/0/2/5",  # item icons
    "a/0/6/5",  # move animation scripts
    "a/0/8/2",  # UI graphics
    "a/1/2/5",  # secondary UI graphics
    "a/2/1/3",  # Hall of Fame graphics
    "a/1/6/5",  # footprints
)

TEXT_ARCHIVES = ("a/0/0/2", "a/0/0/3")

SIDECARS = (
    "poke_form_list.bin",
    "pokeicon_palette_map.bin",
    "type_chart.bin",
    "type_palette_map.bin",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--clean-b2", type=Path, required=True)
    parser.add_argument("--clean-w2", type=Path, required=True)
    parser.add_argument("--vfs", type=Path, required=True)
    parser.add_argument("--root", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--manifest-output", type=Path, required=True)
    parser.add_argument("--expanded-files", type=Path, required=True)
    return parser.parse_args()


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def load_module(path: Path, name: str):
    spec = importlib.util.spec_from_file_location(name, path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"unable to import {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def archive_bytes(rom: ndspy.rom.NintendoDSRom, path: str) -> bytes:
    return bytes(rom.files[rom.filenames.idOf(path)])


def source_members(directory: Path) -> dict[int, bytes]:
    result: dict[int, bytes] = {}
    if not directory.is_dir():
        return result
    for child in directory.iterdir():
        if child.is_file() and child.name.isdigit():
            result[int(child.name)] = child.read_bytes()
    return result


def save_narc(template: ndspy.narc.NARC, files: list[bytes]) -> bytes:
    template.files = [bytearray(data) for data in files]
    return template.save()


def complete_replacement(path: str, vfs: Path, b2_rom: ndspy.rom.NintendoDSRom) -> tuple[bytes, dict]:
    members = source_members(vfs / path)
    if not members:
        raise RuntimeError(f"expanded replacement is missing: {vfs / path}")
    expected = list(range(max(members) + 1))
    if sorted(members) != expected:
        raise RuntimeError(f"expanded archive {path} has non-contiguous members")
    template = ndspy.narc.NARC(archive_bytes(b2_rom, path))
    result = save_narc(template, [members[index] for index in expected])
    return result, {"policy": "replace-expanded-table", "members": len(expected)}


def authored_overlay(
    path: str,
    vfs: Path,
    w2_rom: ndspy.rom.NintendoDSRom,
    b2_rom: ndspy.rom.NintendoDSRom,
    allowed_member_ids: set[int] | None = None,
) -> tuple[bytes | None, dict]:
    members = source_members(vfs / path)
    if not members:
        return None, {"policy": "authored-members", "membersPatched": 0}
    w2 = ndspy.narc.NARC(archive_bytes(w2_rom, path))
    b2 = ndspy.narc.NARC(archive_bytes(b2_rom, path))
    output = [bytes(data) for data in b2.files]
    patched: list[int] = []
    conflicts: list[int] = []
    for member_id, authored in sorted(members.items()):
        if allowed_member_ids is not None and member_id not in allowed_member_ids:
            continue
        if member_id < len(w2.files) and authored == bytes(w2.files[member_id]):
            continue
        while len(output) <= member_id:
            output.append(b"")
        if member_id < len(w2.files) and member_id < len(b2.files):
            if bytes(w2.files[member_id]) != bytes(b2.files[member_id]):
                conflicts.append(member_id)
        output[member_id] = authored
        patched.append(member_id)
    if not patched:
        return None, {"policy": "authored-members", "membersPatched": 0}
    return save_narc(b2, output), {
        "policy": "authored-members",
        "membersPatched": len(patched),
        "memberIds": patched,
        "authoredVersionConflicts": conflicts,
    }


def merge_text_archive(
    path: str,
    vfs: Path,
    w2_rom: ndspy.rom.NintendoDSRom,
    b2_rom: ndspy.rom.NintendoDSRom,
    text_module: Any,
) -> tuple[bytes | None, dict]:
    authored_members = source_members(vfs / path)
    clean_w2 = ndspy.narc.NARC(archive_bytes(w2_rom, path))
    clean_b2 = ndspy.narc.NARC(archive_bytes(b2_rom, path))
    output = [bytes(data) for data in clean_b2.files]
    changed_entries: dict[str, list[int]] = {}

    for member_id, authored_bytes in sorted(authored_members.items()):
        if member_id < len(clean_w2.files) and authored_bytes == bytes(clean_w2.files[member_id]):
            continue
        authored = text_module.decode_message_file(authored_bytes)
        baseline = text_module.decode_message_file(bytes(clean_w2.files[member_id])) if member_id < len(clean_w2.files) else {"entries": []}
        target = text_module.decode_message_file(bytes(clean_b2.files[member_id])) if member_id < len(clean_b2.files) else {**authored, "entries": []}
        baseline_entries = baseline.get("entries", [])
        authored_entries = authored.get("entries", [])
        target_entries = list(target.get("entries", []))
        member_changes: list[int] = []
        for index, entry in enumerate(authored_entries):
            old_units = text_module.entry_code_units(baseline_entries[index]) if index < len(baseline_entries) else None
            new_units = text_module.entry_code_units(entry)
            if old_units == new_units:
                continue
            while len(target_entries) <= index:
                target_entries.append({"index": len(target_entries), "text": "$", "text_bits": 16})
            target_entries[index] = dict(entry)
            member_changes.append(index)
        if not member_changes:
            continue
        target["entries"] = target_entries
        # Recompute the payload start when expansion appends messages; the
        # vanilla offset only reserves room for the original entry table.
        target.pop("payload_start", None)
        encoded = text_module.encode_message_file(target)
        while len(output) <= member_id:
            output.append(b"")
        output[member_id] = encoded
        changed_entries[str(member_id)] = member_changes

    if not changed_entries:
        return None, {"policy": "enumerated-text-entries", "membersPatched": 0, "entriesPatched": 0}
    return save_narc(clean_b2, output), {
        "policy": "enumerated-text-entries",
        "membersPatched": len(changed_entries),
        "entriesPatched": sum(len(value) for value in changed_entries.values()),
        "entries": changed_entries,
    }


def build_item_icon_patch(root: Path, b2_rom: ndspy.rom.NintendoDSRom) -> tuple[list[dict], dict[int, bytes]]:
    module = load_module(root / "tools/item_icons/build_item_icon_patch.py", "b2u_item_icons")
    original_arm9 = bytes(ndspy.codeCompression.decompress(b2_rom.arm9))
    patched_arm9 = bytearray(original_arm9)
    table_offset = module.locate_item_graphics_table(patched_arm9)
    archive_path = "a/0/2/5"
    icon_archive = ndspy.narc.NARC(archive_bytes(b2_rom, archive_path))
    file_ids = list(range(len(icon_archive.files)))
    staged: dict[int, bytes] = {}
    operations: list[dict] = []

    groups = (
        (module.MEGA_STONES, module.MEGA_ITEM_IDS, "poke_ball"),
        (module.GEN7_UTILITY_ITEM_ICONS, module.GEN7_UTILITY_ITEM_IDS, "mega_reference_mass"),
        (module.LOW_ITEM_ICONS, module.LOW_ITEM_IDS, "mega_reference_mass"),
        (module.TERRAIN_SEED_ICONS, module.TERRAIN_SEED_ITEM_IDS, "mega_reference_mass"),
    )
    for icons, target_ids, align_mode in groups:
        assignments = module.choose_target_file_ids(patched_arm9, table_offset, target_ids, file_ids, len(icons))
        module.patch_arm9_graphics_table(patched_arm9, table_offset, assignments)
        for icon in icons:
            cgx, pal = assignments[icon.item_id]
            stem = icon.constant.removeprefix("ITEM_").lower()
            files = module.build_item_icon_files(
                root / "assets/item_icons/icons" / f"{stem}.png",
                root / "assets/item_icons/icon_palettes" / f"{stem}.pal",
                align_mode=align_mode,
            )
            staged[cgx] = files.cgx
            staged[pal] = files.pal

    patched_item_ids = (
        module.MEGA_ITEM_IDS
        | module.GEN7_UTILITY_ITEM_IDS
        | module.LOW_ITEM_IDS
        | module.TERRAIN_SEED_ITEM_IDS
    )
    for item_id in sorted(patched_item_ids):
        offset = table_offset + item_id * module.ENTRY_SIZE
        before = original_arm9[offset : offset + module.ENTRY_SIZE]
        after = bytes(patched_arm9[offset : offset + module.ENTRY_SIZE])
        operations.append(
            {
                "operation": "patch-arm9-decompressed",
                "offset": offset,
                "size": len(after),
                "originalHex": before.hex(),
                "replacementHex": after.hex(),
                "itemId": item_id,
            }
        )
    return operations, staged


def deterministic_tar_gz(files: dict[str, bytes], manifest: bytes) -> bytes:
    tar_buffer = io.BytesIO()
    with tarfile.open(fileobj=tar_buffer, mode="w", format=tarfile.PAX_FORMAT) as archive:
        entries = {"manifest.json": manifest, **{f"files/{path}": data for path, data in files.items()}}
        for path, data in sorted(entries.items()):
            info = tarfile.TarInfo(path)
            info.size = len(data)
            info.mtime = 0
            info.mode = 0o644
            info.uid = 0
            info.gid = 0
            info.uname = ""
            info.gname = ""
            archive.addfile(info, io.BytesIO(data))
    return gzip.compress(tar_buffer.getvalue(), compresslevel=9, mtime=0)


def main() -> int:
    args = parse_args()
    if sha256(args.clean_b2.read_bytes()) != BASE_B2_SHA256:
        raise SystemExit("Black2Upgrade package requires the exact clean US IREO ROM")
    b2_rom = ndspy.rom.NintendoDSRom.fromFile(str(args.clean_b2))
    w2_rom = ndspy.rom.NintendoDSRom.fromFile(str(args.clean_w2))
    text_module = load_module(args.root / "tools/text/gen5_text.py", "b2u_gen5_text")

    terrain_csv = args.root / "assets/move_backgrounds/terrains/battle-background-floor-targets.csv"
    with terrain_csv.open(newline="", encoding="utf-8") as stream:
        terrain_rows = list(csv.DictReader(stream))
    clean_w2_fields = ndspy.narc.NARC(archive_bytes(w2_rom, "a/0/1/1"))
    clean_b2_fields = ndspy.narc.NARC(archive_bytes(b2_rom, "a/0/1/1"))
    covered_backgrounds: set[int] = set()
    for row in terrain_rows:
        member = int(row["nsbmd_member"])
        if bytes(clean_w2_fields.files[member]) != bytes(clean_b2_fields.files[member]):
            raise RuntimeError(f"B2 field model {member} differs from the reviewed W2 terrain layout")
        for token in row["background"].split(";"):
            covered_backgrounds.add(int(token.strip()))
    missing_backgrounds = sorted(set(range(47)) - covered_backgrounds)
    if missing_backgrounds:
        raise RuntimeError(f"terrain floor mapping omits vanilla B2 backgrounds: {missing_backgrounds}")

    staged: dict[str, bytes] = {}
    merge_report: dict[str, dict] = {}
    for path in FULL_REPLACEMENTS:
        staged[path], merge_report[path] = complete_replacement(path, args.vfs, b2_rom)
    for path in AUTHORED_MEMBER_OVERLAYS:
        data, report = authored_overlay(path, args.vfs, w2_rom, b2_rom)
        merge_report[path] = report
        if data is not None:
            staged[path] = data

    # The native battle sprite archive is seeded from clean B2.  The authored
    # expansion begins at member 13000; lower vanilla members are never copied
    # from the W2 staging tree.
    battle_path = "a/0/0/4"
    battle_ids = {member_id for member_id in source_members(args.vfs / battle_path) if member_id >= 13000}
    data, report = authored_overlay(battle_path, args.vfs, w2_rom, b2_rom, battle_ids)
    merge_report[battle_path] = report
    if data is not None:
        staged[battle_path] = data

    # Battle field models 0..852 remain native B2.  Four terrain-indicator
    # members and the generated per-model terrain TEX0 catalog are authored.
    field_path = "a/0/1/1"
    field_ids = {420, 421, 422, 423}
    field_ids.update(member_id for member_id in source_members(args.vfs / field_path) if member_id >= 853)
    data, report = authored_overlay(field_path, args.vfs, w2_rom, b2_rom, field_ids)
    merge_report[field_path] = report
    if data is not None:
        staged[field_path] = data
    for path in TEXT_ARCHIVES:
        data, report = merge_text_archive(path, args.vfs, w2_rom, b2_rom, text_module)
        merge_report[path] = report
        if data is not None:
            staged[path] = data

    arm9_patches, item_icon_members = build_item_icon_patch(args.root, b2_rom)
    item_path = "a/0/2/5"
    item_narc = ndspy.narc.NARC(staged.get(item_path, archive_bytes(b2_rom, item_path)))
    item_files = [bytes(data) for data in item_narc.files]
    for member_id, data in item_icon_members.items():
        item_files[member_id] = data
    staged[item_path] = save_narc(item_narc, item_files)
    merge_report[item_path]["b2ItemIconMembers"] = sorted(item_icon_members)

    for name in SIDECARS:
        source = args.vfs / name
        if not source.is_file():
            raise RuntimeError(f"missing expansion sidecar: {source}")
        # Root-level additions would be inserted before the native /a tree in
        # Nitro's contiguous FNT ranges, shifting every baked Gen 5 archive
        # file ID. Keep B2-only sidecars in an appended expansion directory.
        staged[f"data/black2upgrade/{name}"] = source.read_bytes()
    pwan = args.vfs / "zz_pokeweb_pwan/pwan.narc"
    if not pwan.is_file():
        raise RuntimeError(f"missing canonical PWAN archive: {pwan}")
    staged["zz_pokeweb_pwan/pwan.narc"] = pwan.read_bytes()
    staged["data/black2upgrade/battle-background-floor-targets.csv"] = terrain_csv.read_bytes()

    payload_hasher = hashlib.sha256()
    for path, data in sorted(staged.items()):
        payload_hasher.update(path.encode("utf-8") + b"\0")
        payload_hasher.update(len(data).to_bytes(8, "little"))
        payload_hasher.update(hashlib.sha256(data).digest())
    payload_hasher.update(json.dumps(arm9_patches, sort_keys=True, separators=(",", ":")).encode("utf-8"))
    payload_hash = payload_hasher.hexdigest()

    marker = {
        "magic": "B2UP",
        "schemaVersion": 1,
        "baseGameId": "IREO",
        "dataVersion": DATA_VERSION,
        "runtimeAbi": RUNTIME_ABI,
        "packageChecksum": payload_hash,
    }
    staged["data/black2upgrade/manifest.json"] = (json.dumps(marker, indent=2) + "\n").encode("utf-8")

    operations = [
        {
            "path": path,
            "operation": "replace" if path.startswith("a/") else "add-or-replace",
            "size": len(data),
            "sha256": sha256(data),
        }
        for path, data in sorted(staged.items())
    ]
    manifest = {
        "schemaVersion": 1,
        "magic": "B2UP-PACKAGE",
        "baseGameId": "IREO",
        "baseRomSha256": BASE_B2_SHA256,
        "runtimeAbi": RUNTIME_ABI,
        "dataVersion": DATA_VERSION,
        "packageChecksum": payload_hash,
        "files": operations,
        "arm9Patches": arm9_patches,
        "mergeReport": merge_report,
        "terrainVerification": {
            "backgrounds": 47,
            "seasonRows": len(terrain_rows),
            "fieldModelsByteIdenticalAcrossCleanW2B2": True,
            "terrainTypes": ["Electric", "Grassy", "Misty", "Psychic"],
        },
        "preserved": ["trainers", "encounters", "story-scripts", "maps", "unmodified-b2-text"],
    }
    manifest_bytes = (json.dumps(manifest, indent=2, sort_keys=False) + "\n").encode("utf-8")
    package_bytes = deterministic_tar_gz(staged, manifest_bytes)

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(package_bytes)
    args.manifest_output.parent.mkdir(parents=True, exist_ok=True)
    args.manifest_output.write_bytes(manifest_bytes)
    if args.expanded_files.exists():
        shutil.rmtree(args.expanded_files)
    for path, data in staged.items():
        destination = args.expanded_files / path
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(data)
    (args.output.with_suffix(args.output.suffix + ".sha256")).write_text(
        f"{sha256(package_bytes)}  {args.output.name}\n", encoding="ascii"
    )
    print(
        f"built {args.output} ({len(package_bytes)} bytes, {len(staged)} files, "
        f"{len(arm9_patches)} ARM9 patches, payload {payload_hash})"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
