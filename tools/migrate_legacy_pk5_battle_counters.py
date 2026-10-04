#!/usr/bin/env python3
"""Migrate legacy Gen 5 PK5 KO counters to the split PKHeX-safe layout.

This tool targets Black 2/White 2 raw saves and DeSmuME .dsv files. It updates
both normal-save copies, preserves any DeSmuME footer, and refreshes the PK5,
box, party, and checksum-table checksums affected by the migration.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
from dataclasses import asdict, dataclass
from pathlib import Path
from pwan.report_paths import portable_report
from tempfile import NamedTemporaryFile


RAW_SAVE_SIZE = 0x80000
SAVE_HALF_OFFSETS = (0, 0x26000)
BOX_COUNT = 24
BOX_BLOCK_OFFSET = 0x400
BOX_BLOCK_STRIDE = 0x1000
BOX_DATA_LENGTH = 0xFF0
BOX_CHECKSUM_OFFSET = 0xFF2
BOX_SLOT_COUNT = 30
PK5_STORED_SIZE = 136
PARTY_BLOCK_OFFSET = 0x18E00
PARTY_BLOCK_LENGTH = 0x534
PARTY_COUNT_OFFSET = PARTY_BLOCK_OFFSET + 4
PARTY_SLOTS_OFFSET = PARTY_BLOCK_OFFSET + 8
PARTY_SLOT_COUNT = 6
PK5_PARTY_SIZE = 220
PARTY_CHECKSUM_OFFSET = 0x19336
CHECKSUM_TABLE_OFFSET = 0x25F00
CHECKSUM_TABLE_LENGTH = 0x94
CHECKSUM_TABLE_CHECKSUM_OFFSET = 0x25FA2
PARTY_CHECKSUM_INDEX = 26

PK5_DATA_OFFSET = 0x08
PK5_DATA_SIZE = 0x80
PK5_BLOCK_SIZE = 0x20
PK5_KOS_LOW_OFFSET = 0x43 - PK5_DATA_OFFSET
PK5_KOS_HIGH_OFFSET = 0x5E - PK5_DATA_OFFSET
PK5_LEGACY_KOS_OFFSET = 0x64 - PK5_DATA_OFFSET
PK5_BROUGHT_OFFSET = 0x44 - PK5_DATA_OFFSET
PK5_USED_OFFSET = 0x46 - PK5_DATA_OFFSET
PK5_NICKNAME_OFFSET = 0x48 - PK5_DATA_OFFSET
PK5_NICKNAME_LENGTH = 22

BLOCK_ORDERS = (
    (0, 1, 2, 3), (0, 1, 3, 2), (0, 2, 1, 3), (0, 3, 1, 2),
    (0, 2, 3, 1), (0, 3, 2, 1), (1, 0, 2, 3), (1, 0, 3, 2),
    (2, 0, 1, 3), (3, 0, 1, 2), (2, 0, 3, 1), (3, 0, 2, 1),
    (1, 2, 0, 3), (1, 3, 0, 2), (2, 1, 0, 3), (3, 1, 0, 2),
    (2, 3, 0, 1), (3, 2, 0, 1), (1, 2, 3, 0), (1, 3, 2, 0),
    (2, 1, 3, 0), (3, 1, 2, 0), (2, 3, 1, 0), (3, 2, 1, 0),
    (0, 1, 2, 3), (0, 1, 3, 2), (0, 2, 1, 3), (0, 3, 1, 2),
    (0, 2, 3, 1), (0, 3, 2, 1), (1, 0, 2, 3), (1, 0, 3, 2),
)


@dataclass(frozen=True)
class Migration:
    save_copy: int
    location: str
    species_id: int
    nickname: str
    personality: int
    kos: int
    battles_brought: int
    battles_used: int


@dataclass(frozen=True)
class Conflict:
    save_copy: int
    location: str
    species_id: int
    nickname: str
    personality: int
    legacy_kos: int
    split_kos: int


def read_u16(data: bytes | bytearray, offset: int) -> int:
    return data[offset] | data[offset + 1] << 8


def write_u16(data: bytearray, offset: int, value: int) -> None:
    data[offset] = value & 0xFF
    data[offset + 1] = value >> 8 & 0xFF


def read_u32(data: bytes | bytearray, offset: int) -> int:
    return int.from_bytes(data[offset : offset + 4], "little")


def crypt_words(data: bytes | bytearray, seed: int) -> bytearray:
    result = bytearray(data)
    state = seed
    for offset in range(0, len(result), 2):
        state = (state * 0x41C64E6D + 0x6073) & 0xFFFFFFFF
        write_u16(result, offset, read_u16(result, offset) ^ (state >> 16))
    return result


def add16(data: bytes | bytearray) -> int:
    return sum(read_u16(data, offset) for offset in range(0, len(data), 2)) & 0xFFFF


def crc16_ccitt(data: bytes | bytearray) -> int:
    top = 0xFF
    bottom = 0xFF
    for byte in data:
        value = byte ^ top
        value ^= value >> 4
        top = (bottom ^ (value >> 3) ^ (value << 4)) & 0xFF
        bottom = (value ^ (value << 5)) & 0xFF
    return top << 8 | bottom


def decrypt_pk5(pk5: bytes | bytearray) -> tuple[bytearray, int] | None:
    if len(pk5) < PK5_STORED_SIZE:
        return None
    personality = read_u32(pk5, 0)
    sanity = read_u16(pk5, 4)
    checksum = read_u16(pk5, 6)
    if sanity & 2:
        return None
    physical = crypt_words(pk5[PK5_DATA_OFFSET:PK5_STORED_SIZE], checksum)
    if add16(physical) != checksum:
        return None
    logical = bytearray(PK5_DATA_SIZE)
    order = BLOCK_ORDERS[(personality >> 13) & 31]
    for logical_block, physical_block in enumerate(order):
        logical_start = logical_block * PK5_BLOCK_SIZE
        physical_start = physical_block * PK5_BLOCK_SIZE
        logical[logical_start : logical_start + PK5_BLOCK_SIZE] = physical[
            physical_start : physical_start + PK5_BLOCK_SIZE
        ]
    species_id = read_u16(logical, 0)
    if not 1 <= species_id <= 1024:
        return None
    return logical, personality


def encrypt_pk5(pk5: bytes | bytearray, logical: bytes | bytearray, personality: int) -> bytearray:
    physical = bytearray(PK5_DATA_SIZE)
    order = BLOCK_ORDERS[(personality >> 13) & 31]
    for logical_block, physical_block in enumerate(order):
        logical_start = logical_block * PK5_BLOCK_SIZE
        physical_start = physical_block * PK5_BLOCK_SIZE
        physical[physical_start : physical_start + PK5_BLOCK_SIZE] = logical[
            logical_start : logical_start + PK5_BLOCK_SIZE
        ]
    checksum = add16(physical)
    result = bytearray(pk5)
    write_u16(result, 6, checksum)
    result[PK5_DATA_OFFSET:PK5_STORED_SIZE] = crypt_words(physical, checksum)
    return result


def decode_nickname(logical: bytes | bytearray) -> str:
    units = []
    end = PK5_NICKNAME_OFFSET + PK5_NICKNAME_LENGTH
    for offset in range(PK5_NICKNAME_OFFSET, end, 2):
        value = read_u16(logical, offset)
        if value in (0, 0xFFFF):
            break
        units.append(value)
    raw = b"".join(value.to_bytes(2, "little") for value in units)
    return raw.decode("utf-16le", errors="replace")


def migrate_pk5(
    raw: bytearray,
    offset: int,
    size: int,
    save_copy: int,
    location: str,
) -> tuple[Migration | None, Conflict | None]:
    original = raw[offset : offset + size]
    decrypted = decrypt_pk5(original)
    if decrypted is None:
        return None, None
    logical, personality = decrypted
    legacy_kos = read_u16(logical, PK5_LEGACY_KOS_OFFSET)
    split_kos = logical[PK5_KOS_LOW_OFFSET] | logical[PK5_KOS_HIGH_OFFSET] << 8
    if legacy_kos == 0:
        return None, None
    species_id = read_u16(logical, 0)
    nickname = decode_nickname(logical)
    if split_kos not in (0, legacy_kos):
        return None, Conflict(
            save_copy, location, species_id, nickname, personality, legacy_kos, split_kos
        )
    logical[PK5_KOS_LOW_OFFSET] = legacy_kos & 0xFF
    logical[PK5_KOS_HIGH_OFFSET] = legacy_kos >> 8 & 0xFF
    write_u16(logical, PK5_LEGACY_KOS_OFFSET, 0)
    raw[offset : offset + size] = encrypt_pk5(original, logical, personality)
    return Migration(
        save_copy,
        location,
        species_id,
        nickname,
        personality,
        legacy_kos,
        read_u16(logical, PK5_BROUGHT_OFFSET),
        read_u16(logical, PK5_USED_OFFSET),
    ), None


def refresh_checksum_table(raw: bytearray, half_offset: int) -> None:
    start = half_offset + CHECKSUM_TABLE_OFFSET
    checksum = crc16_ccitt(raw[start : start + CHECKSUM_TABLE_LENGTH])
    write_u16(raw, half_offset + CHECKSUM_TABLE_CHECKSUM_OFFSET, checksum)


def migrate_save(data: bytes) -> tuple[bytes, list[Migration], list[Conflict]]:
    if len(data) < RAW_SAVE_SIZE:
        raise ValueError(f"save is {len(data)} bytes; expected at least {RAW_SAVE_SIZE}")
    raw = bytearray(data)
    migrations: list[Migration] = []
    conflicts: list[Conflict] = []
    for save_copy, half_offset in enumerate(SAVE_HALF_OFFSETS):
        touched_boxes: set[int] = set()
        party_touched = False
        party_count = min(raw[half_offset + PARTY_COUNT_OFFSET], PARTY_SLOT_COUNT)
        for slot in range(party_count):
            offset = half_offset + PARTY_SLOTS_OFFSET + slot * PK5_PARTY_SIZE
            migrated, conflict = migrate_pk5(
                raw, offset, PK5_PARTY_SIZE, save_copy, f"party slot {slot + 1}"
            )
            if migrated:
                migrations.append(migrated)
                party_touched = True
            if conflict:
                conflicts.append(conflict)
        for box in range(BOX_COUNT):
            block = half_offset + BOX_BLOCK_OFFSET + box * BOX_BLOCK_STRIDE
            for slot in range(BOX_SLOT_COUNT):
                offset = block + slot * PK5_STORED_SIZE
                migrated, conflict = migrate_pk5(
                    raw, offset, PK5_STORED_SIZE, save_copy, f"box {box + 1}, slot {slot + 1}"
                )
                if migrated:
                    migrations.append(migrated)
                    touched_boxes.add(box)
                if conflict:
                    conflicts.append(conflict)
        for box in touched_boxes:
            block = half_offset + BOX_BLOCK_OFFSET + box * BOX_BLOCK_STRIDE
            checksum = crc16_ccitt(raw[block : block + BOX_DATA_LENGTH])
            write_u16(raw, block + BOX_CHECKSUM_OFFSET, checksum)
            write_u16(raw, half_offset + CHECKSUM_TABLE_OFFSET + (box + 1) * 2, checksum)
        if party_touched:
            block = half_offset + PARTY_BLOCK_OFFSET
            checksum = crc16_ccitt(raw[block : block + PARTY_BLOCK_LENGTH])
            write_u16(raw, half_offset + PARTY_CHECKSUM_OFFSET, checksum)
            write_u16(
                raw,
                half_offset + CHECKSUM_TABLE_OFFSET + PARTY_CHECKSUM_INDEX * 2,
                checksum,
            )
        if touched_boxes or party_touched:
            refresh_checksum_table(raw, half_offset)
    return bytes(raw), migrations, conflicts


def verify_output(data: bytes, migrations: list[Migration]) -> None:
    for migration in migrations:
        half_offset = SAVE_HALF_OFFSETS[migration.save_copy]
        if migration.location.startswith("party slot "):
            slot = int(migration.location.removeprefix("party slot ")) - 1
            offset = half_offset + PARTY_SLOTS_OFFSET + slot * PK5_PARTY_SIZE
            size = PK5_PARTY_SIZE
        else:
            box_text, slot_text = migration.location.split(", ")
            box = int(box_text.removeprefix("box ")) - 1
            slot = int(slot_text.removeprefix("slot ")) - 1
            offset = half_offset + BOX_BLOCK_OFFSET + box * BOX_BLOCK_STRIDE + slot * PK5_STORED_SIZE
            size = PK5_STORED_SIZE
        decrypted = decrypt_pk5(data[offset : offset + size])
        if decrypted is None:
            raise ValueError(f"invalid migrated PK5 at copy {migration.save_copy}: {migration.location}")
        logical, _ = decrypted
        split_kos = logical[PK5_KOS_LOW_OFFSET] | logical[PK5_KOS_HIGH_OFFSET] << 8
        if split_kos != migration.kos or read_u16(logical, PK5_LEGACY_KOS_OFFSET) != 0:
            raise ValueError(f"counter migration verification failed at {migration.location}")
    for half_offset in SAVE_HALF_OFFSETS:
        table_start = half_offset + CHECKSUM_TABLE_OFFSET
        expected = crc16_ccitt(data[table_start : table_start + CHECKSUM_TABLE_LENGTH])
        actual = read_u16(data, half_offset + CHECKSUM_TABLE_CHECKSUM_OFFSET)
        if expected != actual:
            raise ValueError(f"invalid checksum table in save half {half_offset:#x}")


def write_atomic(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with NamedTemporaryFile(dir=path.parent, prefix=f".{path.name}.", delete=False) as tmp:
        temp_path = Path(tmp.name)
        tmp.write(data)
        tmp.flush()
        os.fsync(tmp.fileno())
    temp_path.replace(path)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--report", type=Path, help="optional JSON report path")
    args = parser.parse_args()

    original = args.input.read_bytes()
    migrated, changes, conflicts = migrate_save(original)
    if conflicts:
        details = ", ".join(
            f"copy {item.save_copy} {item.location}: legacy={item.legacy_kos}, split={item.split_kos}"
            for item in conflicts
        )
        raise SystemExit(f"refusing to overwrite conflicting counters: {details}")
    verify_output(migrated, changes)
    if original[RAW_SAVE_SIZE:] != migrated[RAW_SAVE_SIZE:]:
        raise SystemExit("DeSmuME footer was modified")
    write_atomic(args.output, migrated)

    report = {
        "input": str(args.input),
        "output": str(args.output),
        "input_sha256": hashlib.sha256(original).hexdigest(),
        "output_sha256": hashlib.sha256(migrated).hexdigest(),
        "migrated_instances": len(changes),
        "unique_personalities": len({item.personality for item in changes}),
        "changes": [asdict(item) for item in changes],
    }
    text = json.dumps(portable_report(report), indent=2, ensure_ascii=False) + "\n"
    if args.report:
        write_atomic(args.report, text.encode())
    print(text, end="")


if __name__ == "__main__":
    main()
