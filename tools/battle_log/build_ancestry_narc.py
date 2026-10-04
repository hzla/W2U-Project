#!/usr/bin/env python3
"""Build the battle-log species ancestry NARC from compiled evolution data.

The runtime only needs reverse evolution ancestry: a Charmeleon summary counts
Charmander and Charmeleon KOs, while a Vaporeon summary counts Eevee and
Vaporeon KOs but not KOs by the other Eevee evolutions.

The tool deliberately accepts either ordered 42/48-byte evolution members (the
build path) or a complete evolution NARC (the installer path).
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path
from typing import Sequence


EVOLUTION_SLOT_SIZE = 6
EVOLUTION_MEMBER_SIZES = (42, 48)
DEFAULT_SPECIES_COUNT = 1024
ANCESTRY_MEMBER_VERSION = 1
MAX_ANCESTORS = 32


def _indexed_member_path(path: Path) -> tuple[int, Path]:
    suffix = path.name.rsplit("_", 1)[-1]
    try:
        return int(suffix), path
    except ValueError as error:
        raise ValueError(f"evolution member has no numeric suffix: {path}") from error


def load_member_files(paths: Sequence[Path]) -> list[bytes]:
    indexed = sorted(_indexed_member_path(path) for path in paths)
    indices = [index for index, _ in indexed]
    expected = list(range(len(indexed)))
    if indices != expected:
        raise ValueError(
            "evolution members must be contiguous and start at 0; "
            f"got {indices[:8]}{'...' if len(indices) > 8 else ''}"
        )
    return [path.read_bytes() for _, path in indexed]


def parse_narc(data: bytes) -> list[bytes]:
    if len(data) < 0x1C or data[:4] != b"NARC":
        raise ValueError("input is not a NARC")
    file_size, header_size, block_count = struct.unpack_from("<IHH", data, 8)
    if file_size != len(data) or header_size != 0x10 or block_count != 3:
        raise ValueError("invalid NARC header")

    fat_offset = header_size
    if data[fat_offset : fat_offset + 4] != b"BTAF":
        raise ValueError("NARC is missing its BTAF block")
    fat_size, member_count = struct.unpack_from("<II", data, fat_offset + 4)
    if fat_size != 0x0C + member_count * 8 or fat_offset + fat_size > len(data):
        raise ValueError("invalid NARC BTAF block")

    fnt_offset = fat_offset + fat_size
    if fnt_offset + 8 > len(data) or data[fnt_offset : fnt_offset + 4] != b"BTNF":
        raise ValueError("NARC is missing its BTNF block")
    (fnt_size,) = struct.unpack_from("<I", data, fnt_offset + 4)
    image_offset = fnt_offset + fnt_size
    if image_offset + 8 > len(data) or data[image_offset : image_offset + 4] != b"GMIF":
        raise ValueError("NARC is missing its GMIF block")
    (image_size,) = struct.unpack_from("<I", data, image_offset + 4)
    if image_offset + image_size != len(data):
        raise ValueError("invalid NARC GMIF block")

    image_data = image_offset + 8
    image_data_size = image_size - 8
    members: list[bytes] = []
    for index in range(member_count):
        start, end = struct.unpack_from("<II", data, fat_offset + 0x0C + index * 8)
        if start > end or end > image_data_size:
            raise ValueError(f"invalid NARC member range at index {index}")
        members.append(data[image_data + start : image_data + end])
    return members


def build_narc(members: Sequence[bytes]) -> bytes:
    image = bytearray(8)
    ranges: list[tuple[int, int]] = []
    for member in members:
        start = len(image) - 8
        image.extend(member)
        end = start + len(member)
        ranges.append((start, end))
        while len(image) % 4:
            image.append(0)
    struct.pack_into("<4sI", image, 0, b"GMIF", len(image))

    fat = bytearray(struct.pack("<4sII", b"BTAF", 0x0C + len(members) * 8, len(members)))
    for start, end in ranges:
        fat.extend(struct.pack("<II", start, end))

    # One unnamed root directory, matching the standard Nitro NARC layout.
    # The root directory's entry list begins at payload offset 8. A zero byte
    # terminates the unnamed list; the remaining bytes are alignment padding.
    fnt = struct.pack("<4sI IHH", b"BTNF", 0x14, 8, 0, 1) + b"\0\0\0\0"
    output = bytearray(0x10)
    output.extend(fat)
    output.extend(fnt)
    output.extend(image)
    struct.pack_into("<4sHHIHH", output, 0, b"NARC", 0xFEFF, 1, len(output), 0x10, 3)
    return bytes(output)


def validate_evolution_members(members: Sequence[bytes]) -> None:
    if not members:
        raise ValueError("no evolution members were supplied")
    member_size = len(members[0])
    if member_size not in EVOLUTION_MEMBER_SIZES:
        raise ValueError(
            f"evolution member 0 is {member_size} bytes; expected vanilla 42 or expanded 48"
        )
    for index, member in enumerate(members):
        if len(member) != member_size:
            raise ValueError(
                f"evolution member {index} is {len(member)} bytes; "
                f"expected the archive's {member_size}-byte member size"
            )


def build_ancestry_members(
    evolution_members: Sequence[bytes], species_count: int
) -> list[bytes]:
    validate_evolution_members(evolution_members)
    if not 1 <= species_count <= 1024:
        raise ValueError("species count must be between 1 and 1024")

    parents: list[set[int]] = [set() for _ in range(species_count)]
    for source, member in enumerate(evolution_members[:species_count]):
        for slot in range(len(member) // EVOLUTION_SLOT_SIZE):
            offset = slot * EVOLUTION_SLOT_SIZE
            method, _, target = struct.unpack_from("<HHH", member, offset)
            if method == 0 or target == 0 or target >= species_count:
                continue
            parents[target].add(source)

    cache: dict[int, frozenset[int]] = {}

    def ancestry(species: int, active: tuple[int, ...] = ()) -> frozenset[int]:
        if species in cache:
            return cache[species]
        if species in active:
            cycle = " -> ".join(str(node) for node in (*active, species))
            raise ValueError(f"evolution graph contains a cycle: {cycle}")

        result = {species}
        next_active = (*active, species)
        for parent in sorted(parents[species]):
            result.update(ancestry(parent, next_active))
        if len(result) > MAX_ANCESTORS:
            raise ValueError(
                f"species {species} has {len(result)} ancestors; runtime limit is {MAX_ANCESTORS}"
            )
        cache[species] = frozenset(result)
        return cache[species]

    output: list[bytes] = []
    for species in range(species_count):
        family = sorted(ancestry(species))
        record = bytearray((ANCESTRY_MEMBER_VERSION, len(family)))
        for member_species in family:
            record.extend(struct.pack("<H", member_species))
        output.append(bytes(record))
    return output


def write_if_changed(path: Path, data: bytes) -> None:
    if path.exists() and path.read_bytes() == data:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument("--evolution-members", nargs="+", type=Path)
    source.add_argument("--evolution-narc", type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--stamp", type=Path)
    parser.add_argument("--species-count", type=int, default=DEFAULT_SPECIES_COUNT)
    args = parser.parse_args()

    if args.evolution_members:
        evolution_members = load_member_files(args.evolution_members)
        source_description = f"{len(evolution_members)} compiled evolution members"
    else:
        evolution_members = parse_narc(args.evolution_narc.read_bytes())
        source_description = str(args.evolution_narc)

    ancestry_members = build_ancestry_members(evolution_members, args.species_count)
    output = build_narc(ancestry_members)
    # Reparse our output before staging it so malformed archives fail the build.
    if parse_narc(output) != ancestry_members:
        raise RuntimeError("generated ancestry NARC failed its round-trip validation")
    write_if_changed(args.output, output)

    if args.stamp:
        stamp = (
            f"source: {source_description}\n"
            f"evolution members: {len(evolution_members)}\n"
            f"ancestry members: {len(ancestry_members)}\n"
            f"archive bytes: {len(output)}\n"
        ).encode()
        write_if_changed(args.stamp, stamp)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
