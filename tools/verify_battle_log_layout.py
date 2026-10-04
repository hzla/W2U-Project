#!/usr/bin/env python3
"""Verify the public White2Upgrade merged trainer-battle log layout."""

from __future__ import annotations


HEADER_SIZE = 16
RECORD_SIZE = 14
PARTY_SLOTS = 6
BLOCKS = (
    (0x1338, 350),
    (0x07C4, 140),
    (0x0D54, 110),
)

TRAINER_ID_BIT = 0
PLAYER_COUNT_BIT = 10
PLAYER_SPECIES_BIT = 13
PLAYER_KO_CREDIT_BIT = 73
AI_KO_CREDIT_BIT = 91
RESERVED_BIT = 109
PARTNER_KO_CREDIT = 7


def write_bits(record: bytearray, offset: int, width: int, value: int) -> None:
    for bit in range(width):
        destination = offset + bit
        mask = 1 << (destination & 7)
        if (value >> bit) & 1:
            record[destination >> 3] |= mask
        else:
            record[destination >> 3] &= ~mask


def read_bits(record: bytes, offset: int, width: int) -> int:
    value = 0
    for bit in range(width):
        source = offset + bit
        value |= ((record[source >> 3] >> (source & 7)) & 1) << bit
    return value


def pack(
    trainer_id: int,
    player_species: tuple[int, ...],
    player_ko_credits: tuple[int, ...],
    ai_ko_credits: tuple[int, ...],
) -> bytes:
    assert 1 <= len(player_species) <= PARTY_SLOTS
    assert len(player_ko_credits) == PARTY_SLOTS
    assert len(ai_ko_credits) == PARTY_SLOTS

    record = bytearray(RECORD_SIZE)
    write_bits(record, TRAINER_ID_BIT, 10, trainer_id)
    write_bits(record, PLAYER_COUNT_BIT, 3, len(player_species))
    for slot in range(PARTY_SLOTS):
        species = player_species[slot] if slot < len(player_species) else 0
        write_bits(record, PLAYER_SPECIES_BIT + slot * 10, 10, species)
        write_bits(record, PLAYER_KO_CREDIT_BIT + slot * 3, 3, player_ko_credits[slot])
        write_bits(record, AI_KO_CREDIT_BIT + slot * 3, 3, ai_ko_credits[slot])
    return bytes(record)


def unpack(record: bytes) -> tuple[int, tuple[int, ...], tuple[int, ...], tuple[int, ...]]:
    player_count = read_bits(record, PLAYER_COUNT_BIT, 3)
    return (
        read_bits(record, TRAINER_ID_BIT, 10),
        tuple(
            read_bits(record, PLAYER_SPECIES_BIT + slot * 10, 10)
            for slot in range(player_count)
        ),
        tuple(
            read_bits(record, PLAYER_KO_CREDIT_BIT + slot * 3, 3)
            for slot in range(PARTY_SLOTS)
        ),
        tuple(
            read_bits(record, AI_KO_CREDIT_BIT + slot * 3, 3)
            for slot in range(PARTY_SLOTS)
        ),
    )


def main() -> None:
    assert sum(capacity for _, capacity in BLOCKS) == 600
    for size, capacity in BLOCKS:
        assert HEADER_SIZE + capacity * RECORD_SIZE <= size

    cases = (
        (0, (1,), (1, 0, 0, 0, 0, 0), (1, 0, 0, 0, 0, 0)),
        (
            1023,
            (1023, 778, 6, 491, 1, 999),
            (6, 5, 4, 3, 2, PARTNER_KO_CREDIT),
            (1, 2, 3, 4, 5, 6),
        ),
    )
    for case in cases:
        encoded = pack(*case)
        assert len(encoded) == RECORD_SIZE
        assert unpack(encoded) == case
        assert read_bits(encoded, RESERVED_BIT, 3) == 0

    print("battle-log layout verified: 3 blocks, 600 packed 14-byte battle records")


if __name__ == "__main__":
    main()
