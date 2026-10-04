#!/usr/bin/env python3
"""Generate the reviewed canonical Black2Upgrade ESDB.

The public names are inherited from the curated IRDO database.  Their IREO
addresses are selected by the reviewed alias map, which records the functions
that do not follow the normal ARM9 relocation and the independently verified
overlay relocations.  The result deliberately retains IRDO's compact segment
layout because the numeric overlay names are understood by RPMTool.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import sys

import yaml


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--white-esdb", type=Path, required=True)
    parser.add_argument("--ireo-esdb", type=Path, required=True)
    parser.add_argument("--aliases", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    return parser.parse_args()


def ireo_addresses(path: Path) -> set[int]:
    # Streaming is intentional: the Ghidra-generated IREO database is large.
    addresses: set[int] = set()
    address_re = re.compile(r"^\s+Address:\s+(0x[0-9a-fA-F]+)\s*$")
    with path.open("r", encoding="utf-8") as stream:
        for line in stream:
            match = address_re.match(line)
            if match:
                addresses.add(int(match.group(1), 16))
    return addresses


def emit_yaml(segments: list[dict], symbols: list[dict], output: Path) -> None:
    lines = ["# Generated; do not edit. Source: IREO.yml + black2upgrade_aliases.json", "Segments:"]
    for segment in segments:
        lines.extend(
            (
                f"  - ID: 0x{int(segment['ID']):X}",
                f"    Name: {segment['Name']}",
                f"    Type: {segment['Type'] if segment['Type'] is not None else 'null'}",
            )
        )
    lines.append("")
    lines.append("Symbols:")
    for symbol in symbols:
        lines.extend(
            (
                f"  - Name: {symbol['Name']}",
                f"    Segment: 0x{int(symbol['Segment']):X}",
                f"    Address: 0x{int(symbol['Address']):X}",
            )
        )
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    args = parse_args()
    aliases = json.loads(args.aliases.read_text(encoding="utf-8"))
    white = yaml.safe_load(args.white_esdb.read_text(encoding="utf-8"))
    segment_names = {int(entry["ID"]): str(entry["Name"]) for entry in white["Segments"]}
    fixed = set(aliases["arm9FixedSymbols"])
    supported = set(aliases["supportedExecutableSegments"])
    segment_deltas = {str(key): int(value) for key, value in aliases["segmentDeltas"].items()}
    known_ireo_addresses = ireo_addresses(args.ireo_esdb)

    translated: list[dict] = []
    unverified: list[str] = []
    for source in white["Symbols"]:
        segment_name = segment_names[int(source["Segment"])]
        if segment_name == "ARM9":
            delta = 0 if source["Name"] in fixed else int(aliases["arm9DefaultDelta"])
        elif segment_name in segment_deltas:
            delta = segment_deltas[segment_name]
        else:
            # Unreferenced W2-only segments must not leak into a B2 runtime.
            continue

        target = dict(source)
        target["Address"] = int(source["Address"]) + delta
        translated.append(target)
        if segment_name in supported and int(target["Address"]) not in known_ireo_addresses:
            # IREO.yml need not name every byte in a function, but every direct
            # function entry should have at least its Thumb/ARM address or the
            # corresponding even address represented in the source database.
            even = int(target["Address"]) & ~1
            if even not in known_ireo_addresses and (even | 1) not in known_ireo_addresses:
                unverified.append(str(source["Name"]))

    # The reviewed map is authoritative for aliases that Ghidra did not label;
    # retain a concise audit warning rather than silently changing the address.
    if unverified:
        print(
            f"[black2upgrade-esdb] {len(unverified)} aliases have no exact generic IREO label; "
            "their compatibility is enforced by the clean-ROM hook/signature manifest.",
            file=sys.stderr,
        )

    emit_yaml(white["Segments"], translated, args.output)
    print(f"wrote {args.output} ({len(translated)} canonical symbols)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
