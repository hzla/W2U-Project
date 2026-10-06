#!/usr/bin/env python3
"""Measure w2anim's three per-sprite game-heap buffers, separately from PMC."""
import argparse
import json
from pathlib import Path
import struct


def inspect(data):
    if len(data) < 16 or data[:4] != b"W2AS":
        raise ValueError("Missing W2AS header")
    version, reserved, count, offset = struct.unpack_from("<HHII", data, 4)
    if version != 1 or reserved or offset < 16 or offset & 3 or count > (len(data) - offset) // 16:
        raise ValueError("Invalid W2AS index")
    records, previous = [], None
    for index in range(count):
        arc, flags, sheet, mani, palette = struct.unpack_from("<HHIII", data, offset + index * 16)
        key = (arc, sheet)
        if (previous is not None and key <= previous) or flags & ~1 or mani & 3 or mani + 28 > len(data):
            raise ValueError("Invalid/unsorted stream entry")
        previous = key
        if data[mani:mani + 4] != b"MANI":
            raise ValueError("Missing MANI header")
        version, flags, width, height, sequence, unique, seq_offset, frame_offset, pal_offset = struct.unpack_from("<6H3I", data, mani + 4)
        if version != 2 or flags & ~7 or not sequence or not unique or not height or not width:
            raise ValueError("Invalid MANI format")
        if height > 128 or width > (256 if flags & 2 else 128) or (flags & 2 and width & 1):
            raise ValueError("Unsupported runtime dimensions")
        if seq_offset < 28 or frame_offset < 28 or mani + seq_offset + sequence * 4 > len(data) or mani + frame_offset + unique * 8 > len(data):
            raise ValueError("Truncated MANI tables")
        max_blob = 0
        for frame in range(unique):
            at, size = struct.unpack_from("<II", data, mani + frame_offset + frame * 8)
            if size < 4 or size > 20 * 1024 or at > len(data) - mani or size > len(data) - mani - at:
                raise ValueError("Truncated or oversized frame")
            max_blob = max(max_blob, size)
        meta = sequence * 4 + unique * 8
        compressed = (max_blob + 3) & ~3
        staging = height * (width // 2 if flags & 2 else 128)
        records.append({"arc": arc, "sheet": sheet, "manifest_offset": mani,
                        "sequence_count": sequence, "unique_frame_count": unique,
                        "metadata_bytes": meta, "compressed_buffer_bytes": compressed,
                        "staging_bytes": staging, "payload_bytes": meta + compressed + staging})
    if not records:
        raise ValueError("Empty stream archive")
    maximum = max(records, key=lambda row: row["payload_bytes"])
    return {"entry_count": count, "unique_manifests": len({row["manifest_offset"] for row in records}),
            "max_per_sprite": maximum, "four_sprite_payload_upper_bound": maximum["payload_bytes"] * 4,
            "eight_slot_payload_upper_bound": maximum["payload_bytes"] * 8,
            "pmc_heap_bytes": 0, "allocations_per_sprite": 3,
            "note": "Payload bounds only: game allocator headers and the shared VBlank task are not measured here. Native lifecycle measurements are separate."}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--streams", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    args.output.write_text(json.dumps(inspect(args.streams.read_bytes()), indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
