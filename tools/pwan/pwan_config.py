"""PWAN runtime config v3 helpers.

Rows are packed as:
    u16 species
    u8  formAndFlags: bits 0-4 form, bit 5 front present, bit 6 back present
    u16 paired asset index
"""

from __future__ import annotations

import struct
from pathlib import Path


PWAN_CONFIG_MAGIC = b"PWNC"
PWAN_CONFIG_VERSION = 3
PWAN_CONFIG_HEADER_BYTES = 16
PWAN_CONFIG_ENTRY_BYTES = 5
PWAN_CONFIG_FORM_MASK = 0x1F
PWAN_CONFIG_FRONT_FLAG = 1
PWAN_CONFIG_BACK_FLAG = 2
PWAN_RUNTIME_MAX_TIMELINE = 192


def _paired_asset_index(entry: dict) -> int:
    explicit = entry.get("assetIndex")
    if explicit is not None:
        return int(explicit)

    flags = int(entry.get("flags", 0)) & 0x3
    candidates: list[int] = []
    if flags & PWAN_CONFIG_FRONT_FLAG:
        candidates.append(int(entry.get("frontIndex", 0)))
    if flags & PWAN_CONFIG_BACK_FLAG:
        candidates.append(int(entry.get("backIndex", 0)))
    if not candidates:
        candidates.append(int(entry.get("frontIndex", entry.get("backIndex", 0))))

    unique = set(candidates)
    if len(unique) != 1:
        raise ValueError(
            f"PWAN v3 requires one paired asset index per row, got {sorted(unique)} "
            f"for species {entry.get('species')} form {entry.get('form')}"
        )
    return candidates[0]


def _normalize_entry(entry: dict) -> dict:
    species = int(entry["species"])
    form = int(entry.get("form", 0))
    flags = int(entry.get("flags", 0)) & 0x3
    asset_index = _paired_asset_index(entry)
    if form & ~PWAN_CONFIG_FORM_MASK:
        raise ValueError(f"PWAN v3 form {form} is outside the 5-bit range")
    return {
        "species": species,
        "form": form,
        "flags": flags,
        "assetIndex": asset_index,
        "frontIndex": asset_index if flags & PWAN_CONFIG_FRONT_FLAG else 0,
        "backIndex": asset_index if flags & PWAN_CONFIG_BACK_FLAG else 0,
    }


def parse_config(path: Path) -> tuple[dict[tuple[int, int], dict], int]:
    if not path.exists():
        return {}, 0

    data = path.read_bytes()
    magic, version, count, max_timeline, entries_offset = struct.unpack_from("<4sHHII", data, 0)
    if magic != PWAN_CONFIG_MAGIC:
        raise ValueError(f"{path} is not a PWAN config")
    if version != PWAN_CONFIG_VERSION:
        raise ValueError(f"{path} uses unsupported PWAN config version {version}")

    entries: dict[tuple[int, int], dict] = {}
    for index in range(count):
        species, form_flags, asset_index = struct.unpack_from(
            "<HBH", data, entries_offset + index * PWAN_CONFIG_ENTRY_BYTES
        )
        form = form_flags & PWAN_CONFIG_FORM_MASK
        flags = (form_flags >> 5) & 0x3
        entry = _normalize_entry({
            "species": species,
            "form": form,
            "flags": flags,
            "assetIndex": asset_index,
        })
        entries[(species, form)] = entry
    return entries, max_timeline


def write_config(
    path: Path,
    entries: dict[tuple[int, int], dict],
    max_timeline: int,
    *,
    dry_run: bool = False,
    max_overrides: int | None = None,
) -> None:
    if dry_run:
        return

    max_timeline = min(int(max_timeline), PWAN_RUNTIME_MAX_TIMELINE)
    ordered = [_normalize_entry(entries[key]) for key in sorted(entries)]
    if max_overrides is not None and len(ordered) > max_overrides:
        raise ValueError(
            f"PWAN config would have {len(ordered)} entries, above runtime cap {max_overrides}"
        )

    blob = bytearray()
    blob += struct.pack(
        "<4sHHII",
        PWAN_CONFIG_MAGIC,
        PWAN_CONFIG_VERSION,
        len(ordered),
        max_timeline,
        PWAN_CONFIG_HEADER_BYTES,
    )
    for entry in ordered:
        form_flags = (entry["form"] & PWAN_CONFIG_FORM_MASK) | ((entry["flags"] & 0x3) << 5)
        blob += struct.pack("<HBH", entry["species"], form_flags, entry["assetIndex"])
    path.write_bytes(bytes(blob))


def set_entry_side(
    entries: dict[tuple[int, int], dict],
    species: int,
    form: int,
    side: str,
    asset_index: int,
) -> dict:
    entry = entries.setdefault((species, form), {
        "species": species,
        "form": form,
        "flags": 0,
        "assetIndex": asset_index,
        "frontIndex": 0,
        "backIndex": 0,
    })
    current = int(entry.get("assetIndex", asset_index))
    if current != asset_index:
        raise ValueError(
            f"PWAN v3 requires paired front/back assets; species {species} form {form} "
            f"already uses asset index {current}, cannot add {asset_index}"
        )
    entry["assetIndex"] = asset_index
    if side == "front":
        entry["flags"] = int(entry.get("flags", 0)) | PWAN_CONFIG_FRONT_FLAG
        entry["frontIndex"] = asset_index
    elif side == "back":
        entry["flags"] = int(entry.get("flags", 0)) | PWAN_CONFIG_BACK_FLAG
        entry["backIndex"] = asset_index
    else:
        raise ValueError(f"unknown PWAN side {side!r}")
    return entry
