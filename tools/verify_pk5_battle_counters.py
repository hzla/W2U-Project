#!/usr/bin/env python3
"""Verify the cross-version Gen 5 individual battle-counter PK5 layout."""

from __future__ import annotations

import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
HEADER = ROOT / "include" / "w2u_battle_log.h"
RUNTIME = ROOT / "src" / "battle_log" / "w2u_battle_log.cpp"
COUNTER_RUNTIME = ROOT / "src" / "battle_log" / "w2u_pk5_battle_counters.cpp"

PK5_SIZE = 136
DATA_OFFSET = 0x08
DATA_SIZE = 0x80
BLOCK_SIZE = 0x20
BROUGHT_OFFSET = 0x44
USED_OFFSET = 0x46
KOS_LOW_OFFSET = 0x43
KOS_HIGH_OFFSET = 0x5E
LEGACY_KOS_OFFSET = 0x64
COUNTER_BLOCK_OFFSET = 0x1C
KOS_LOW_BLOCK_OFFSET = 0x1B
KOS_HIGH_BLOCK_OFFSET = 0x16
DECRYPTED_FLAG = 1 << 1
EGG_FLAG = 1 << 30

EXPECTED_BLOCK_ORDER = (
    (0, 1, 2, 3), (0, 1, 3, 2), (0, 2, 1, 3), (0, 3, 1, 2),
    (0, 2, 3, 1), (0, 3, 2, 1), (1, 0, 2, 3), (1, 0, 3, 2),
    (2, 0, 1, 3), (3, 0, 1, 2), (2, 0, 3, 1), (3, 0, 2, 1),
    (1, 2, 0, 3), (1, 3, 0, 2), (2, 1, 0, 3), (3, 1, 0, 2),
    (2, 3, 0, 1), (3, 2, 0, 1), (1, 2, 3, 0), (1, 3, 2, 0),
    (2, 1, 3, 0), (3, 1, 2, 0), (2, 3, 1, 0), (3, 2, 1, 0),
    (0, 1, 2, 3), (0, 1, 3, 2), (0, 2, 1, 3), (0, 3, 1, 2),
    (0, 2, 3, 1), (0, 3, 2, 1), (1, 0, 2, 3), (1, 0, 3, 2),
)


def read_u16(data: bytes | bytearray, offset: int) -> int:
    return data[offset] | data[offset + 1] << 8


def write_u16(data: bytearray, offset: int, value: int) -> None:
    data[offset] = value & 0xFF
    data[offset + 1] = value >> 8 & 0xFF


def read_u32(data: bytes | bytearray, offset: int) -> int:
    return int.from_bytes(data[offset : offset + 4], "little")


def write_u32(data: bytearray, offset: int, value: int) -> None:
    data[offset : offset + 4] = value.to_bytes(4, "little")


def checksum(data: bytes | bytearray) -> int:
    return sum(read_u16(data, offset) for offset in range(0, DATA_SIZE, 2)) & 0xFFFF


def crypt(data: bytearray, seed: int) -> None:
    key = seed
    for offset in range(0, DATA_SIZE, 2):
        key = (key * 1103515245 + 24691) & 0xFFFFFFFF
        write_u16(data, offset, read_u16(data, offset) ^ (key >> 16))


def physical_block_offset(pk5: bytes | bytearray, logical_block: int) -> int:
    order = read_u32(pk5, 0) >> 13 & 31
    return EXPECTED_BLOCK_ORDER[order][logical_block] * BLOCK_SIZE


def make_pk5(
    order: int,
    *,
    egg: bool = False,
    empty: bool = False,
    decrypted: bool = False,
    legacy_kos: bool = False,
) -> bytearray:
    logical = bytearray((index * 37 + 11) & 0xFF for index in range(DATA_SIZE))
    write_u16(logical, 0, 0 if empty else 25)
    ivs = read_u32(logical, BLOCK_SIZE + 0x10)
    write_u32(logical, BLOCK_SIZE + 0x10, (ivs & ~EGG_FLAG) | (EGG_FLAG if egg else 0))
    write_u16(logical, BROUGHT_OFFSET - DATA_OFFSET, 10)
    write_u16(logical, USED_OFFSET - DATA_OFFSET, 20)
    logical[KOS_LOW_OFFSET - DATA_OFFSET] = 0 if legacy_kos else 30
    logical[KOS_HIGH_OFFSET - DATA_OFFSET] = 0
    logical[LEGACY_KOS_OFFSET - DATA_OFFSET : LEGACY_KOS_OFFSET - DATA_OFFSET + 4] = b"\0" * 4
    if legacy_kos:
        write_u16(logical, LEGACY_KOS_OFFSET - DATA_OFFSET, 30)
    # Explicit sentinels for B2W2's Block-D N-Pokemon and Pokestar bytes.
    logical[3 * BLOCK_SIZE + 0x1E] = 0xA5
    logical[3 * BLOCK_SIZE + 0x1F] = 0x5A

    physical = bytearray(DATA_SIZE)
    for logical_block in range(4):
        physical_block = EXPECTED_BLOCK_ORDER[order][logical_block]
        physical[physical_block * BLOCK_SIZE : (physical_block + 1) * BLOCK_SIZE] = logical[
            logical_block * BLOCK_SIZE : (logical_block + 1) * BLOCK_SIZE
        ]

    result = bytearray(PK5_SIZE)
    write_u32(result, 0, order << 13 | 0x123)
    write_u16(result, 4, DECRYPTED_FLAG if decrypted else 0)
    write_u16(result, 6, checksum(physical))
    if not decrypted:
        crypt(physical, read_u16(result, 6))
    result[DATA_OFFSET:] = physical
    return result


def logical_view(pk5: bytes | bytearray) -> bytearray:
    physical = bytearray(pk5[DATA_OFFSET:])
    if read_u16(pk5, 4) & DECRYPTED_FLAG == 0:
        crypt(physical, read_u16(pk5, 6))
    logical = bytearray(DATA_SIZE)
    for logical_block in range(4):
        physical_block = EXPECTED_BLOCK_ORDER[read_u32(pk5, 0) >> 13 & 31][logical_block]
        logical[logical_block * BLOCK_SIZE : (logical_block + 1) * BLOCK_SIZE] = physical[
            physical_block * BLOCK_SIZE : (physical_block + 1) * BLOCK_SIZE
        ]
    return logical


def read_kos(data: bytes | bytearray, block_b: int, block_c: int) -> int:
    split_value = data[block_b + KOS_LOW_BLOCK_OFFSET] | data[block_c + KOS_HIGH_BLOCK_OFFSET] << 8
    return split_value or read_u16(data, block_c + COUNTER_BLOCK_OFFSET)


def write_kos(data: bytearray, block_b: int, block_c: int, value: int) -> None:
    data[block_b + KOS_LOW_BLOCK_OFFSET] = value & 0xFF
    data[block_c + KOS_HIGH_BLOCK_OFFSET] = value >> 8 & 0xFF
    write_u16(data, block_c + COUNTER_BLOCK_OFFSET, 0)


def update(pk5: bytearray, ko_delta: int, used: bool) -> bool:
    data = bytearray(pk5[DATA_OFFSET:])
    already_decrypted = read_u16(pk5, 4) & DECRYPTED_FLAG != 0
    original_checksum = read_u16(pk5, 6)
    if not already_decrypted:
        crypt(data, original_checksum)
        if checksum(data) != original_checksum:
            crypt(data, original_checksum)
            assert data == pk5[DATA_OFFSET:]
            return False

    block_a = physical_block_offset(pk5, 0)
    block_b = physical_block_offset(pk5, 1)
    block_c = physical_block_offset(pk5, 2)
    is_empty = read_u16(data, block_a) == 0
    is_egg = read_u32(data, block_b + 0x10) & EGG_FLAG != 0
    if not is_empty and not is_egg:
        brought = read_u16(data, block_b + COUNTER_BLOCK_OFFSET)
        fights_used = read_u16(data, block_b + COUNTER_BLOCK_OFFSET + 2)
        kos = read_kos(data, block_b, block_c)
        write_u16(data, block_b + COUNTER_BLOCK_OFFSET, min(0xFFFF, brought + 1))
        if used:
            write_u16(data, block_b + COUNTER_BLOCK_OFFSET + 2, min(0xFFFF, fights_used + 1))
        write_kos(data, block_b, block_c, min(0xFFFF, kos + ko_delta))

    if not already_decrypted:
        write_u16(pk5, 6, checksum(data))
        crypt(data, read_u16(pk5, 6))
    pk5[DATA_OFFSET:] = data
    return not is_empty and not is_egg


def verify_source_constants() -> None:
    header = HEADER.read_text()
    expected_defines = {
        "W2U_PK5_SIZE": PK5_SIZE,
        "W2U_PK5_ENCRYPTED_DATA_OFFSET": DATA_OFFSET,
        "W2U_PK5_ENCRYPTED_DATA_SIZE": DATA_SIZE,
        "W2U_PK5_BLOCK_SIZE": BLOCK_SIZE,
        "W2U_PK5_BATTLES_BROUGHT_OFFSET": BROUGHT_OFFSET,
        "W2U_PK5_BATTLES_USED_OFFSET": USED_OFFSET,
        "W2U_PK5_KOS_LOW_OFFSET": KOS_LOW_OFFSET,
        "W2U_PK5_KOS_HIGH_OFFSET": KOS_HIGH_OFFSET,
        "W2U_PK5_LEGACY_KOS_OFFSET": LEGACY_KOS_OFFSET,
        "W2U_PK5_COUNTERS_IN_BLOCK_OFFSET": COUNTER_BLOCK_OFFSET,
        "W2U_PK5_KOS_LOW_IN_BLOCK_B_OFFSET": KOS_LOW_BLOCK_OFFSET,
        "W2U_PK5_KOS_HIGH_IN_BLOCK_C_OFFSET": KOS_HIGH_BLOCK_OFFSET,
    }
    for name, expected in expected_defines.items():
        match = re.search(rf"^#define {name} (0x[0-9A-Fa-f]+|[0-9]+)$", header, re.MULTILINE)
        assert match and int(match.group(1), 0) == expected, name

    runtime = RUNTIME.read_text()
    counter_runtime = COUNTER_RUNTIME.read_text()
    # The injected module intentionally delegates de-shuffling and crypto to
    # the retail routines to stay below the smallest observed PMC allocation.
    for helper in (
        "BattleLog_PkmDecrypt",
        "BattleLog_PkmReEncrypt",
        "BattleLog_PkmCryptoRun",
        "BattleLog_PkmGetBlock",
    ):
        assert helper.replace("BattleLog_", "k") in counter_runtime
    assert "kPk5BlockOrder" not in counter_runtime
    assert "kPk5CounterRpcMagic" in runtime
    assert "kPk5CounterRpcMagic" in counter_runtime


def verify_all_permutations() -> None:
    allowed = {
        BROUGHT_OFFSET - DATA_OFFSET,
        BROUGHT_OFFSET - DATA_OFFSET + 1,
        USED_OFFSET - DATA_OFFSET,
        USED_OFFSET - DATA_OFFSET + 1,
        KOS_LOW_OFFSET - DATA_OFFSET,
        KOS_HIGH_OFFSET - DATA_OFFSET,
        LEGACY_KOS_OFFSET - DATA_OFFSET,
        LEGACY_KOS_OFFSET - DATA_OFFSET + 1,
    }
    for order in range(32):
        for already_decrypted in (False, True):
            pk5 = make_pk5(order, decrypted=already_decrypted)
            sanity = read_u16(pk5, 4)
            checksum_before = read_u16(pk5, 6)
            before = logical_view(pk5)
            assert update(pk5, 3, True)
            after = logical_view(pk5)
            assert read_u16(after, BROUGHT_OFFSET - DATA_OFFSET) == 11
            assert read_u16(after, USED_OFFSET - DATA_OFFSET) == 21
            assert after[KOS_LOW_OFFSET - DATA_OFFSET] == 33
            assert after[KOS_HIGH_OFFSET - DATA_OFFSET] == 0
            assert read_u16(after, LEGACY_KOS_OFFSET - DATA_OFFSET) == 0
            assert read_u32(after, LEGACY_KOS_OFFSET - DATA_OFFSET) == 0
            assert read_u16(pk5, 4) == sanity
            for offset, (old, new) in enumerate(zip(before, after, strict=True)):
                if offset not in allowed:
                    assert old == new, (order, already_decrypted, offset, old, new)
            assert after[3 * BLOCK_SIZE + 0x1E : 3 * BLOCK_SIZE + 0x20] == b"\xA5\x5A"

            if already_decrypted:
                # A fast-mode owner keeps the structure decrypted and retains
                # responsibility for checksum regeneration when it exits.
                assert read_u16(pk5, 6) == checksum_before
            else:
                decrypted_physical = bytearray(pk5[DATA_OFFSET:])
                crypt(decrypted_physical, read_u16(pk5, 6))
                assert checksum(decrypted_physical) == read_u16(pk5, 6)


def verify_edge_cases() -> None:
    decrypted = make_pk5(23, decrypted=True)
    checksum_before = read_u16(decrypted, 6)
    assert update(decrypted, 2, True)
    assert read_u16(decrypted, 4) == DECRYPTED_FLAG
    assert read_u16(decrypted, 6) == checksum_before
    view = logical_view(decrypted)
    assert read_u16(view, BROUGHT_OFFSET - DATA_OFFSET) == 11
    assert read_u16(view, USED_OFFSET - DATA_OFFSET) == 21
    assert view[KOS_LOW_OFFSET - DATA_OFFSET] == 32
    assert view[KOS_HIGH_OFFSET - DATA_OFFSET] == 0

    invalid = make_pk5(17)
    invalid[DATA_OFFSET + 7] ^= 0x80
    before = bytes(invalid)
    assert not update(invalid, 1, True)
    assert bytes(invalid) == before

    for excluded in (make_pk5(4, egg=True), make_pk5(9, empty=True)):
        before = bytes(excluded)
        assert not update(excluded, 1, True)
        assert bytes(excluded) == before

    no_use = make_pk5(31)
    assert update(no_use, 0, False)
    view = logical_view(no_use)
    assert read_u16(view, BROUGHT_OFFSET - DATA_OFFSET) == 11
    assert read_u16(view, USED_OFFSET - DATA_OFFSET) == 20
    assert view[KOS_LOW_OFFSET - DATA_OFFSET] == 30
    assert view[KOS_HIGH_OFFSET - DATA_OFFSET] == 0

    for already_decrypted in (False, True):
        legacy = make_pk5(6, decrypted=already_decrypted, legacy_kos=True)
        assert update(legacy, 4, False)
        view = logical_view(legacy)
        assert view[KOS_LOW_OFFSET - DATA_OFFSET] == 34
        assert view[KOS_HIGH_OFFSET - DATA_OFFSET] == 0
        assert read_u32(view, LEGACY_KOS_OFFSET - DATA_OFFSET) == 0

    saturated = make_pk5(12, decrypted=True)
    physical = saturated[DATA_OFFSET:]
    block_b = physical_block_offset(saturated, 1)
    block_c = physical_block_offset(saturated, 2)
    write_u16(physical, block_b + COUNTER_BLOCK_OFFSET, 0xFFFF)
    write_u16(physical, block_b + COUNTER_BLOCK_OFFSET + 2, 0xFFFE)
    write_kos(physical, block_b, block_c, 0xFFFE)
    saturated[DATA_OFFSET:] = physical
    assert update(saturated, 10, True)
    view = logical_view(saturated)
    assert read_u16(view, BROUGHT_OFFSET - DATA_OFFSET) == 0xFFFF
    assert read_u16(view, USED_OFFSET - DATA_OFFSET) == 0xFFFF
    assert view[KOS_LOW_OFFSET - DATA_OFFSET] == 0xFF
    assert view[KOS_HIGH_OFFSET - DATA_OFFSET] == 0xFF
    assert read_u32(view, LEGACY_KOS_OFFSET - DATA_OFFSET) == 0


def main() -> None:
    verify_source_constants()
    verify_all_permutations()
    verify_edge_cases()
    print("PK5 battle counters verified: split KO encoding, legacy migration, 32 permutations, preservation, exclusions, saturation")


if __name__ == "__main__":
    main()
