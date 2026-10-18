#!/usr/bin/env python3
"""Export W2U's moves to the pokebw2 decomp's format: one JSON file per move and the ordered constant list.

usage: python tools/decomp/export_move_json.py --decomp=PATH [--out=DIR] [--check]

The decomp (github.com/fuddlesworth/pokebw2) keeps a move in data/moves/<move>/data.json (move.schema.json: its name,
description and its 36-byte record of the move data archive a/0/2/1, by constant names) and the moves' order in
data/constants/moves.txt; its tools/data/move_data.py packs the archive and tools/text/text_sources.py the name and
description banks (403, 402) from them. This writes W2U's moves (data/pml/moves/<id>.toml, text banks 403 and 402) in
that format. Each TOML is packed with W2U's own serializer (tools/mkdata, format "moves", the same record), and the
record is read back as the decomp's move_data.py reads one, so both sides' field order is the record's.

Names: moves 0-559 keep the decomp's constants, 560 and up are MOVE_ + W2U's enum name (export_species_json.py's
Names). Values are written by the decomp's names (include/constants/battle.h, move_effects.h, data/constants/
types.txt); a value with none is written as a number, as the decomp's dump does, except for what the schema wants as
a name: W2U's type Fairy (17, TYPE_NULL in the decomp) and the move flags W2U added, which get new constants:
OUT/constants_added.json, and OUT/battle_h_flags.txt has their #define lines for include/constants/battle.h.

--check compares the records of moves 1-559 with the decomp's own JSON (the retail data): W2U changes moves on
purpose (power, type, flags of later generations), so the differences are counted by field and listed for the text
only; it fails on a W2U escape left in the text or a value the schema needs a name for and doesn't get one.
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
import tempfile
import types
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_ability_json import DECOMP_ESCAPE, to_json_text  # noqa: E402
from export_species_json import ROOT, Names, text_lines, write  # noqa: E402

MKDATA = ROOT / "tools" / "mkdata"
MOVES = ROOT / "data" / "pml" / "moves"
RECORD = struct.Struct("<6BbBH6BHbbB3B3b3B2sI")          # the decomp's tools/data/move_data.py
MARKER = b"SS"
NAMES, DESCRIPTIONS = 403, 402
RETAIL_MOVES = 559
# The flags W2U added (tools/mkdata/enum/move_flags.toml) as decomp constants, by bit
ADDED_FLAGS = {14: "MOVE_FLAG_POWDER", 16: "MOVE_FLAG_WIND", 17: "MOVE_FLAG_SHARP", 18: "MOVE_FLAG_HEALING_PROPERTY",
               19: "MOVE_FLAG_DANCE", 20: "MOVE_FLAG_BULLET", 21: "MOVE_FLAG_BITE", 22: "MOVE_FLAG_PULSE"}
FLAG_COMMENTS = {14: "Grass types and Overcoat ignore it, as Spore", 16: "Wind Rider and Wind Power react to it",
                 17: "Sharpness boosts it", 18: "Triage gives it priority", 19: "Dancer copies it",
                 20: "Bulletproof blocks it", 21: "Strong Jaw boosts it", 22: "Mega Launcher boosts it"}
TYPE_FAIRY = 17
PAD = r"\x{ffff}"
DEFINE = re.compile(r"^#define (\w+) (?:\(1 << (\d+)\)|(0x[0-9a-fA-F]+\b|-?\d+\b))", re.M)


def decomp_names(decomp: Path) -> dict[str, dict[int, str]]:
    """By prefix, value -> the decomp's first name for it, from the headers the move data's names come from."""
    by_prefix: dict[str, dict[int, str]] = {}
    prefixes = ("MOVE_QUALITY_", "MOVE_CATEGORY_", "MOVE_TARGET_", "MOVE_FLAG_", "CONDITION_", "BATTLE_EFFECT_",
                "BATTLEMON_")
    for header in sorted((decomp / "include" / "constants").glob("*.h")):
        for m in DEFINE.finditer(header.read_text(encoding="utf-8")):
            prefix = next((p for p in prefixes if m[1].startswith(p)), None)
            if prefix is None or (prefix == "BATTLEMON_" and not m[1].endswith("_STAGE")):
                continue
            value = 1 << int(m[2]) if m[2] else int(m[3], 0)
            by_prefix.setdefault(prefix, {}).setdefault(value, m[1])
    return by_prefix


def pack_records() -> dict[int, bytes]:
    """Each W2U move TOML as its record, packed by W2U's serializer (as the build's mkdata.py generic ... moves)."""
    sys.path.insert(0, str(MKDATA))
    from impl.generic import GenericSerializer  # noqa: E402
    from mkdata_util import format_extra_parameters  # noqa: E402
    records = {}
    with tempfile.TemporaryDirectory() as tmp:
        for path in sorted(MOVES.glob("*.toml"), key=lambda p: int(p.stem)):
            out = Path(tmp) / path.stem
            args = types.SimpleNamespace(input=str(path), output=str(out),
                                         ex_parameters=format_extra_parameters(["format", "moves"]))
            if GenericSerializer().Serialize(args):
                raise SystemExit(f"{path.name}: W2U's serializer failed")
            records[int(path.stem)] = out.read_bytes()
    return records


class MoveNames:
    def __init__(self, decomp: Path, names: Names):
        self.d = decomp_names(decomp)
        self.types = dict(names.types)                   # 17: TYPE_FAIRY, added
        self.stats = self.d.get("BATTLEMON_", {})
        self.flags = dict(self.d["MOVE_FLAG_"])
        for bit, name in ADDED_FLAGS.items():
            self.flags.setdefault(1 << bit, name)
        self.missing: list[str] = []

    def named(self, prefix: str, value: int, where: str, required: bool = False):
        table = self.types if prefix == "TYPE_" else self.flags if prefix == "MOVE_FLAG_" else self.d.get(prefix, {})
        if value in table:
            return table[value]
        if required:
            self.missing.append(f"{where}: no {prefix} constant for {value}")
        return value


def move_json(record: bytes, n: MoveNames, where: str) -> dict:
    """The decomp's tools/data/move_data.py move_json, with W2U's names added."""
    (type_, quality, category, power, accuracy, pp, priority, hits, condition, chance, duration, min_turns, max_turns,
     crit, flinch, effect, drain, heal, target, *rest) = RECORD.unpack(record)
    stats, stages, chances, marker, flags = rest[0:3], rest[3:6], rest[6:9], rest[9], rest[10]
    if marker != MARKER:
        raise SystemExit(f"{where}: no SS marker")
    changes = [{"stat": n.named("BATTLEMON_", stats[i], where), "stages": stages[i], "chance": chances[i]}
               for i in range(3)]
    while changes and not (stats[len(changes) - 1] or stages[len(changes) - 1] or chances[len(changes) - 1]):
        changes.pop()
    return {
        "type": n.named("TYPE_", type_, where, True),
        "quality": n.named("MOVE_QUALITY_", quality, where, True),
        "category": n.named("MOVE_CATEGORY_", category, where, True),
        "power": power,
        "accuracy": accuracy,
        "pp": pp,
        "priority": priority,
        "hits": {"min": hits & 0xF, "max": hits >> 4},
        "inflicts": {"condition": n.named("CONDITION_", condition, where), "chance": chance, "duration": duration,
                     "min_turns": min_turns, "max_turns": max_turns},
        "crit_stage": crit,
        "flinch_chance": flinch,
        "effect": n.named("BATTLE_EFFECT_", effect, where),
        "drain": drain,
        "heal": heal,
        "target": n.named("MOVE_TARGET_", target, where, True),
        "stat_changes": changes,
        "flags": [n.named("MOVE_FLAG_", 1 << bit, where) for bit in range(32) if flags >> bit & 1],
    }


def directory(constant: str) -> str:
    return constant.removeprefix("MOVE_").lower()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True, help="a pokebw2 checkout (only its files are read)")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_moves")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    names = Names(args.decomp)
    n = MoveNames(args.decomp, names)
    records = pack_records()
    move_names, descriptions = text_lines(NAMES), text_lines(DESCRIPTIONS)
    if sorted(records) != list(range(len(records))):
        raise SystemExit("data/pml/moves doesn't number the moves from 0 in order")
    moves_dir = args.out / "data" / "moves"
    constants = ["# Moves (W2U: tools/decomp/export_move_json.py; 0-559 as the decomp bootstraps them from the ROM)"]
    written = []
    for value, record in records.items():
        constant = names.moves.get(value)
        if constant is None:
            raise SystemExit(f"move {value} ({move_names.get(value)!r}) has no constant")
        constants.append(f"{constant} = {value}" if value == 0 else constant)
        data = {"$schema": "../move.schema.json", "name": to_json_text(move_names.get(value, "")),
                "description": to_json_text(descriptions.get(value, "")),
                **move_json(record, n, f"{value} {constant}")}
        retail = args.decomp / "data" / "moves" / directory(constant) / "data.json"
        if 0 < value <= RETAIL_MOVES and retail.exists():
            # Leer's retail description ends in \x{ffff} padding, which W2U's text drops: keep the retail line
            theirs = json.loads(retail.read_text(encoding="utf-8"))["description"]
            if theirs.startswith(data["description"]) and not theirs[len(data["description"]):].replace(PAD, ""):
                data["description"] = theirs
        write(moves_dir / directory(constant) / "data.json", data)
        written.append((value, constant, data))
    (args.out / "data" / "constants").mkdir(parents=True, exist_ok=True)
    (args.out / "data" / "constants" / "moves.txt").write_text("\n".join(constants) + "\n", encoding="utf-8")

    used = {f for _, _, d in written for f in d["flags"] if isinstance(f, str)}
    added = {name: 1 << bit for bit, name in ADDED_FLAGS.items() if name not in n.d["MOVE_FLAG_"].values()}
    added.update({c: v for c, v in names.added.items() if c.startswith("MOVE_")})
    added["TYPE_FAIRY"] = TYPE_FAIRY
    write(args.out / "constants_added.json", added)
    lines = [f"#define {name} (1 << {bit}){' ' * max(1, 28 - len(name) - len(str(bit)))}// {FLAG_COMMENTS[bit]} (W2U)"
             for bit, name in ADDED_FLAGS.items() if name in added]
    (args.out / "battle_h_flags.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    new_moves = len(records) - RETAIL_MOVES - 1
    print(f"{len(written)} moves written ({new_moves} new), {len(added)} new constants -> {args.out}")
    print("added flags in use: " + ", ".join(sorted(f for f in used if f in added)))

    if args.check:
        problems = list(n.missing)
        differing: dict[str, int] = {}
        text_diffs = []
        for value, constant, data in written:
            for key in ("name", "description"):
                if "\\" in DECOMP_ESCAPE.sub("", data[key]):
                    problems.append(f"{value} {constant}: {key} keeps a W2U escape: {data[key]!r}")
            if not 0 < value <= RETAIL_MOVES:
                continue
            retail = args.decomp / "data" / "moves" / directory(constant) / "data.json"
            if not retail.exists():
                problems.append(f"{value} {constant}: no {retail.parent.name}/data.json in the decomp")
                continue
            theirs = json.loads(retail.read_text(encoding="utf-8"))
            for key, mine in data.items():
                if key != "$schema" and theirs.get(key) != mine:
                    differing[key] = differing.get(key, 0) + 1
                    if key in ("name", "description"):
                        text_diffs.append(f"{value} {constant}: {key}: decomp {theirs.get(key)!r}, W2U {mine!r}")
        print(f"check: {RETAIL_MOVES} retail moves compared with the decomp; W2U's changes by field: "
              + ", ".join(f"{k} {v}" for k, v in sorted(differing.items(), key=lambda kv: -kv[1])))
        for t in text_diffs[:15]:
            print("  text " + t)
        print(f"{len(problems)} problem(s)")
        for p in problems[:40]:
            print("  " + p)
        if problems:
            sys.exit(1)


if __name__ == "__main__":
    main()
