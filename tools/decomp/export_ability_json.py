#!/usr/bin/env python3
"""Export W2U's abilities to the pokebw2 decomp's format: one JSON file per ability and the ordered constant list.

usage: python tools/decomp/export_ability_json.py --decomp=PATH [--out=DIR] [--check]

The decomp (github.com/fuddlesworth/pokebw2) keeps an ability's text in data/abilities/<ability>.json (name and
description, ability.schema.json) and the abilities' order in data/constants/abilities.txt; its tools/text/
text_sources.py builds the name, upper-case name and description banks from them. This writes W2U's abilities (text
banks 374 names and 375 descriptions) in that format, so a decomp-based W2U can take its ability text from ours, plus
OUT/mechanics.json: which handler table of src/mechanics/abilities serves which ability (W2U_MECHANIC lines), for
the decomp's ability table. Only the decomp's text files are read; none of its code runs.

Names as in export_species_json.py: abilities 0-164 keep the decomp's constants; 165 and up are ABILITY_ + the English
name (the second As One is ABILITY_AS_ONE_2). A file is named after its constant (ABILITY_AIR_LOCK: air_lock.json).
Text: W2U's line breaks (`\\n`) become real ones, as the decomp's JSON has them; the end marker `$` is dropped.

--check compares abilities 0-164 with the decomp's own JSON (the retail text), checks that no W2U escape is left in
any written text, and that every mechanic route names an ability with text.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_species_json import RETAIL_ABILITIES, ROOT, Names, text_lines, write  # noqa: E402

MECHANICS = ROOT / "src" / "mechanics" / "abilities"
ABILITY_HEADER = ROOT / "include" / "w2u_abilities.h"


def to_json_text(line: str) -> str:
    """A W2U text line as the decomp's JSON text: the `\\n` escapes become line breaks (W2U's banks have both forms:
    the retail entries `\\n`, the entries W2U added real line breaks) and `\\"` a plain quote."""
    return line.replace("\\n", "\n").replace('\\"', '"')


# Escapes the decomp's text format has in JSON text: \x{HHHH} characters; control codes are {TTTT:a,b}
DECOMP_ESCAPE = re.compile(r"\\x\{[0-9a-fA-F]+\}")


def file_name(constant: str) -> str:
    return constant.removeprefix("ABILITY_").lower() + ".json"


def mechanic_tables() -> list[dict]:
    """W2U_MECHANIC(ABILITY, <id>, <table>) lines of src/mechanics/abilities: which table serves which ability.
    The id is a W2U name (ABIL_*, include/w2u_abilities.h or megab2w2/mb_ids.h) or a number."""
    ids: dict[str, int] = {}
    aliases: dict[str, str] = {}                 # ABIL_QUEENLY_MAJESTY = ABIL_QUEENLY_MAGESTY
    for header in (ABILITY_HEADER, ROOT / "src" / "pokeweb_gameplay" / "megab2w2" / "mb_ids.h"):
        text = header.read_text(encoding="utf-8")
        for m in re.finditer(r"\b(ABIL_\w+)\s*=\s*(\d+)", text):
            ids.setdefault(m[1], int(m[2]))
        for m in re.finditer(r"\b(ABIL_\w+)\s*=\s*(ABIL_\w+)", text):
            aliases.setdefault(m[1], m[2])
    for name, target in aliases.items():
        if name not in ids and target in ids:
            ids[name] = ids[target]
    out = []
    for path in sorted(MECHANICS.glob("*.c")):
        for m in re.finditer(r"^W2U_MECHANIC\(ABILITY,\s*(\w+),\s*(\w+)\);", path.read_text(encoding="utf-8"),
                             re.M):
            ident, table = m[1], m[2]
            value = int(ident) if ident.isdigit() else ids.get(ident)
            if value is None:
                raise SystemExit(f"{path.name}: no value for {ident}")
            out.append({"ability": value, "w2u_name": ident, "table": table, "file": path.stem})
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True, help="a pokebw2 checkout (only its text is read)")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_abilities")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    names = Names(args.decomp)
    texts, descriptions = text_lines(374), text_lines(375)
    count = max(texts) + 1
    abilities_dir = args.out / "data" / "abilities"
    abilities_dir.mkdir(parents=True, exist_ok=True)

    constants = ["# Abilities (W2U: tools/decomp/export_ability_json.py; 0-164 as the decomp bootstraps them from the ROM)"]
    written = []
    for value in range(count):
        name = names.abilities.get(value)
        if name is None:
            raise SystemExit(f"ability {value} ({texts.get(value)!r}) has no constant (empty name?)")
        constants.append(f"{name} = {value}" if value == 0 else name)
        data = {"$schema": "ability.schema.json", "name": to_json_text(texts[value]),
                "description": to_json_text(descriptions.get(value, ""))}
        if value > 0:                            # ABILITY_NONE has no file in the decomp
            write(abilities_dir / file_name(name), data)
            written.append((value, name, data))
    (args.out / "data" / "constants").mkdir(parents=True, exist_ok=True)
    (args.out / "data" / "constants" / "abilities.txt").write_text("\n".join(constants) + "\n", encoding="utf-8")
    tables = mechanic_tables()
    for t in tables:
        t["constant"] = names.abilities.get(t["ability"])
    write(args.out / "mechanics.json", tables)
    added = {n: v for n, v in names.added.items() if n.startswith("ABILITY_")}
    write(args.out / "constants_added.json", added)
    print(f"{len(written)} abilities written ({len(added)} new constants), {len(tables)} mechanic routes -> {args.out}")
    if names.renamed:
        print("renamed: " + "; ".join(r for r in names.renamed if r.startswith("ABILITY_")))

    if args.check:
        problems = []
        for value, name, data in written:
            for key in ("name", "description"):
                if "\\" in DECOMP_ESCAPE.sub("", data[key]):
                    problems.append(f"{value} {name}: {key} keeps a W2U escape: {data[key]!r}")
            if value <= RETAIL_ABILITIES:
                retail = args.decomp / "data" / "abilities" / file_name(name)
                if not retail.exists():
                    problems.append(f"{value} {name}: no {retail.name} in the decomp")
                    continue
                theirs = json.loads(retail.read_text(encoding="utf-8"))
                for key in ("name", "description"):
                    if theirs.get(key) != data[key]:
                        problems.append(f"{value} {name}: {key} differs: decomp {theirs.get(key)!r}, W2U {data[key]!r}")
        unrouted = [t for t in tables if t["constant"] is None]
        problems += [f"mechanic {t['table']} ({t['file']}.c) routes ability {t['ability']}, which has no text"
                     for t in unrouted]
        print(f"check: {len(written)} files, {sum(1 for v, _, _ in written if v <= RETAIL_ABILITIES)} compared with "
              f"the decomp: {len(problems)} problem(s)")
        for p in problems[:40]:
            print("  " + p)
        if problems:
            sys.exit(1)


if __name__ == "__main__":
    main()
