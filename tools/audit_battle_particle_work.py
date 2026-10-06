#!/usr/bin/env python3
"""Bound native battle SPL allocations before staging imported SPA assets.

The US White 2 LoadSPA context has 24 emitters and 200 particles. Its SPL
allocator is an unchecked aligned bump allocator. Texture pixels live outside
this arena; the manager, arrays and behavior dispatch records live inside it.
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import struct

WORK_BYTES = 0x6000
BASE_BYTES = 76 + 24 * 156 + 200 * 68
OPTIONAL_BLOCKS = {8: 12, 9: 12, 10: 8, 11: 12, 16: 20,
                   24: 8, 25: 8, 26: 16, 27: 4, 28: 8, 29: 16}


def inspect_spa(data: bytes) -> dict:
    if len(data) < 32 or data[:8] != b" APS12_1":
        raise ValueError("unsupported or truncated SPA header")
    resources, textures = struct.unpack_from("<HH", data, 8)
    texture_offset = struct.unpack_from("<I", data, 24)[0]
    if not 32 <= texture_offset <= len(data):
        raise ValueError("texture section is outside the SPA")
    cursor, behaviors = 32, 0
    for _ in range(resources):
        if cursor + 88 > texture_offset:
            raise ValueError("truncated resource header")
        flags = struct.unpack_from("<I", data, cursor)[0]
        cursor += 88 + sum(size for bit, size in OPTIONAL_BLOCKS.items() if flags & (1 << bit))
        behaviors += sum(bool(flags & (1 << bit)) for bit in range(24, 30))
        if cursor > texture_offset:
            raise ValueError("truncated optional resource block")
    if cursor != texture_offset:
        raise ValueError("resource count does not match the texture offset")
    for _ in range(textures):
        if cursor + 32 > len(data) or data[cursor:cursor + 4] != b" TPS":
            raise ValueError("truncated or invalid SPT header")
        size = struct.unpack_from("<I", data, cursor + 28)[0]
        if size < 32 or cursor + size > len(data):
            raise ValueError("texture resource extends beyond the SPA")
        cursor += size
    needed = BASE_BYTES + resources * 32 + behaviors * 8 + textures * 20
    if needed > WORK_BYTES:
        raise ValueError(f"native SPL needs {needed} bytes; battle work arena has {WORK_BYTES}")
    return {"resources": resources, "textures": textures, "behaviors": behaviors,
            "work_bytes": needed, "headroom_bytes": WORK_BYTES - needed}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    records = []
    for path in sorted(args.source.glob("*.bin")):
        try:
            records.append({"asset": path.name, **inspect_spa(path.read_bytes())})
        except ValueError as error:
            raise SystemExit(f"{path.name}: {error}") from error
    if not records:
        raise SystemExit("No SPA assets to validate")
    report = {"work_arena_bytes": WORK_BYTES, "native_base_bytes": BASE_BYTES,
              "extra_game_heap_bytes_per_context": WORK_BYTES - 0x4800,
              "pmc_heap_bytes": 0, "asset_count": len(records),
              "maximum": max(records, key=lambda entry: entry["work_bytes"]), "assets": records}
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
