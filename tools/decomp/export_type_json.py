#!/usr/bin/env python3
"""Export W2U's types for the pokebw2 decomp: the ordered constant list and one name file per type W2U adds.

usage: python tools/decomp/export_type_json.py --decomp=PATH [--out=DIR] [--check]

The decomp keeps a type's name in res/types/<type>.json and the types' order in generated/types.txt, which makes the
type name banks (398 "Fire", 489 "FIRE": \\from{types.name}, \\from{types.name_upper}) and Easy Chat's type words;
TYPE_NULL, the typeless moves' type, is listed but has no name. Retail: 17 types, TYPE_NULL 17.

W2U (include/type_constants.h) adds Fairy as 17; its typeless type is 18. This writes:

    OUT/data/constants/types.txt   the decomp's list with W2U's types after the retail ones (TYPE_FAIRY = 17), then
                                   TYPE_NULL = 17 as a second name: the decomp's code and data that name TYPE_NULL keep
                                   the retail value (the harness builds take TYPE_NULL 18 only where W2U changes the
                                   tests, w2u-local/decomp/resident, group types);
    OUT/types/<type>.json          the added types' names, from W2U's upper-case type names (bank 489, which has
                                   FAIRY; its mixed-case bank 398 stops at Dark), title-cased.

Easy Chat keeps the 17 retail type words (w2u-local/decomp/pilot/patch_decomp.py), as it keeps the retail abilities
and moves, so the main program stays retail.

--check: the retail types' upper-case names in W2U's bank 489 are the decomp's names, upper-cased, and W2U's
constants 0-16 are the decomp's.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_species_json import ROOT, parse_list, text_lines, write  # noqa: E402

TYPE_H = ROOT / "include" / "type_constants.h"
NAMES_UPPER = 489
RETAIL_TYPES = 17


def w2u_types() -> dict[int, str]:
    return {int(m[2]): m[1] for m in re.finditer(r"^#define (TYPE_(?!COUNT)\w+) (\d+)", TYPE_H.read_text(), re.M)}


def decomp_types(decomp: Path) -> tuple[Path, dict[str, int]]:
    path = next(p for p in (decomp / "generated" / "types.txt", decomp / "data" / "constants" / "types.txt")
                if p.exists())
    return path, parse_list(path)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True)
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_types")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    source, decomp = decomp_types(args.decomp)
    w2u = w2u_types()
    upper = text_lines(NAMES_UPPER)
    added = {v: n for v, n in sorted(w2u.items()) if v >= RETAIL_TYPES}
    if args.check:
        problems = [f"{v}: W2U {w2u.get(v)} / decomp {n}" for n, v in decomp.items()
                    if v < RETAIL_TYPES and w2u.get(v) != n]
        for v in range(RETAIL_TYPES):
            if v in w2u and upper.get(v) != w2u[v].removeprefix("TYPE_"):
                problems.append(f"{v}: bank {NAMES_UPPER} has {upper.get(v)!r} for {w2u[v]}")
        problems += [f"{v} {n}: no name in bank {NAMES_UPPER}" for v, n in added.items() if not upper.get(v)]
        for p in problems:
            print("CHECK:", p)
        print(f"{len(added)} added types, {len(problems)} problems")
        sys.exit(1 if problems else 0)

    lines = source.read_text(encoding="utf-8").splitlines()
    null = next(i for i, l in enumerate(lines) if l.split("#", 1)[0].strip().startswith("TYPE_NULL"))
    # the comment block right above TYPE_NULL stays with it
    while null and lines[null - 1].startswith("#"):
        null -= 1
    new = [f"{n} = {v}" for v, n in added.items()]
    text = "\n".join(lines[:null] + ["# W2U's types"] + new + [""] + lines[null:]) + "\n"
    (args.out / "data" / "constants").mkdir(parents=True, exist_ok=True)
    (args.out / "data" / "constants" / "types.txt").write_text(text, encoding="utf-8", newline="\n")
    for v, n in added.items():
        write(args.out / "types" / f"{n.removeprefix('TYPE_').lower()}.json",
              {"$schema": "type.schema.json", "name": upper[v].title()})
    print(f"types: {', '.join(added.values())} -> {args.out}")


if __name__ == "__main__":
    main()
