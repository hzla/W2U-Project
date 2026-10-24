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
Names). Values are written by the decomp's names (include/constants/battle.h, move_effects.h, generated/types.txt); a
value with none is written as a number, as the decomp's dump does, except for what the schema wants as a name: W2U's
type Fairy (17, TYPE_NULL in the decomp), the move flags W2U added and the move effects the decomp has no name for,
which get new constants: OUT/constants_added.json, OUT/battle_h_flags.txt has the flags' #define lines for
include/constants/battle.h and OUT/move_effects_h.txt the effects' for include/constants/move_effects.h (patch_decomp.py
appends both).

The effects: the record's u16 at 0x0E, which the decomp calls the move's effect (BATTLE_EFFECT_*) and W2U's TOML "Move
Animation ID". The decomp names 0-337, the retail game's. W2U's records of its 360 added moves carry 36 other values,
all above that, on 37 moves (none on a retail move): 18 values, 345-380, on 19 Gen 6 moves (Parabolic Charge 345,
Boomburst 378...), and 18 values, 561-616, each the move's own number (Mat Block 561 ... Lands Wrath 616). They come
from the records of the original White2Upgrade (2023), which has no names for them (W2U's enums name only the move
quality, tools/mkdata/enum/btl_eff.toml). The other Gen 6 moves carry a retail effect (Moonblast, Play Rough...), and
the 298 Gen 7-9 moves 0 (BATTLE_EFFECT_HIT). W2U's code never reads the field (its handlers key on the move number, its
animations on the move number + 115); the only reader is the trainer AI (tr_ai.c: IF_MOVE_EFFECT and the effect
tables, which end the script past their size), for which an unknown effect matches nothing. Each value is named as the
decomp names its own beyond Gen 4's, after the first move that has it: BATTLE_EFFECT_PARABOLIC_CHARGE = 345,
BATTLE_EFFECT_HYPERSPACE_HOLE = 359 (Hyperspace Fury has it too).

Left as numbers, as the decomp's own dump does (the schema takes them): the stat 8 of the 3 retail moves that raise every
stat (Ancient Power, Ominous Wind, Silver Wind), the condition 65535 of Smack Down, Telekinesis and Tri Attack, and bit 15
(32768) of the flags of 53 moves, which W2U sets itself (retail has none, its code never tests it, and W2U's
move_flags.toml has no name for it).

--check compares the records of moves 1-559 with the decomp's own JSON (the retail data): W2U changes moves on
purpose (power, type, flags of later generations), so the differences are counted by field and listed for the text
only; it fails on a W2U escape left in the text, a value the schema needs a name for and doesn't get one, an effect
left as a number, an added effect that is not above the decomp's last, or a retail move that needs one.
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


def effect_names(decomp: Path) -> set[str]:
    """Every BATTLE_EFFECT_ name of the decomp's headers (a new one must not take one)."""
    return {m[1] for header in (decomp / "include" / "constants").glob("*.h")
            for m in DEFINE.finditer(header.read_text(encoding="utf-8")) if m[1].startswith("BATTLE_EFFECT_")}


def new_effects(records: dict[int, bytes], constants: dict[int, str], n: "MoveNames", taken: set[str]) -> dict[str, int]:
    """The effect values of W2U's records that the decomp has no name for, named after the first move that has each:
    BATTLE_EFFECT_ + the move's constant without MOVE_ (a name already taken gets _2, _3, ...). Added to n.effects."""
    added: dict[str, int] = {}
    for move, record in records.items():
        effect = RECORD.unpack(record)[15]
        if effect in n.effects:
            continue
        name = base = "BATTLE_EFFECT_" + constants[move].removeprefix("MOVE_")
        count = 1
        while name in taken or name in added:
            count += 1
            name = f"{base}_{count}"
        added[name] = effect
        n.effects[effect] = name
    return added


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
        self.effects = dict(self.d["BATTLE_EFFECT_"])    # W2U's are added after the decomp's (new_effects)
        for bit, name in ADDED_FLAGS.items():
            self.flags.setdefault(1 << bit, name)
        self.missing: list[str] = []

    def named(self, prefix: str, value: int, where: str, required: bool = False):
        table = {"TYPE_": self.types, "MOVE_FLAG_": self.flags, "BATTLE_EFFECT_": self.effects}.get(
            prefix) or self.d.get(prefix, {})
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
        "effect": n.named("BATTLE_EFFECT_", effect, where, True),
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
    effects = new_effects(records, names.moves, n, effect_names(args.decomp))
    move_names, descriptions = text_lines(NAMES), text_lines(DESCRIPTIONS)
    if sorted(records) != list(range(len(records))):
        raise SystemExit("data/pml/moves doesn't number the moves from 0 in order")
    moves_dir = args.out / "data" / "moves"
    retail_dir = args.decomp / "res" / "moves"       # since pokebw2 c1e21df84 (data/moves before)
    if not retail_dir.is_dir():
        retail_dir = args.decomp / "data" / "moves"
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
        retail = retail_dir / directory(constant) / "data.json"
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
    added.update(effects)
    write(args.out / "constants_added.json", added)
    lines = [f"#define {name} (1 << {bit}){' ' * max(1, 28 - len(name) - len(str(bit)))}// {FLAG_COMMENTS[bit]} (W2U)"
             for bit, name in ADDED_FLAGS.items() if name in added]
    (args.out / "battle_h_flags.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    (args.out / "move_effects_h.txt").write_text("\n".join(
        ["// W2U's: the effect values above the retail ones that its Gen 6 moves' records carry, named after the first move",
         "// that has each (W2U-Project tools/decomp/export_move_json.py). Only the trainer AI reads the effect, and for it",
         "// they match nothing"]
        + [f"#define {name} {value}" for name, value in sorted(effects.items(), key=lambda item: item[1])]) + "\n",
        encoding="utf-8")
    new_moves = len(records) - RETAIL_MOVES - 1
    print(f"{len(written)} moves written ({new_moves} new), {len(added)} new constants -> {args.out}")
    print("added flags in use: " + ", ".join(sorted(f for f in used if f in added)))
    on = sum(1 for r in records.values() if RECORD.unpack(r)[15] in effects.values())
    print(f"{len(effects)} added effects on {on} moves: {min(effects.values(), default=0)}-{max(effects.values(), default=0)}")

    if args.check:
        problems = list(n.missing)
        top = max(n.d["BATTLE_EFFECT_"])
        problems += [f"{name} = {value}: not above the decomp's last effect ({top})" for name, value in effects.items()
                     if value <= top]
        problems += [f"{names.moves[move]}: a retail move whose effect the decomp doesn't name"
                     for move, r in records.items() if move <= RETAIL_MOVES and RECORD.unpack(r)[15] in effects.values()]
        problems += [f"{constant}: effect {d['effect']} is a number" for _, constant, d in written
                     if not isinstance(d["effect"], str)]
        differing: dict[str, int] = {}
        text_diffs = []
        for value, constant, data in written:
            for key in ("name", "description"):
                if "\\" in DECOMP_ESCAPE.sub("", data[key]):
                    problems.append(f"{value} {constant}: {key} keeps a W2U escape: {data[key]!r}")
            if not 0 < value <= RETAIL_MOVES:
                continue
            retail = retail_dir / directory(constant) / "data.json"
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
