#!/usr/bin/env python3
"""Export W2U's items for the pokebw2 decomp: the ordered constant list, and the data the decomp's own item dump reads.

usage: python tools/decomp/export_item_json.py --decomp=PATH [--rom=build/White2Upgrade.nds] [--out=DIR] [--check]

The decomp (github.com/fuddlesworth/pokebw2) keeps an item in res/items/<item>/data.json (item.schema.json: its name,
plural, description and its 36-byte record of the item data archive a/0/2/4) and the items' order in
generated/items.txt; tools/data/item_data.py dumps those from a ROM's files once and packs the archive from them, and
the text banks (64 names, 481 names with an article, 482 plurals, 63 descriptions) come from the same JSON.

W2U keeps the retail item numbering and reuses retail slots for its own items (the unused 113-130 and 426, the Data
Cards 505-531 and the second X items 592-610 for Mega Stones, the Apricorns 485-488 for the terrain seeds). This
writes, from W2U's built ROM (what W2U actually ships, so the record and the text are exactly W2U's):

    OUT/data/constants/items.txt   the decomp's list with W2U's constant first for each slot it reuses (include/
                                   Items.h's name) and the retail name after it as a second name, so the decomp's
                                   code that names the slot (pml_item.c, shooter_item.c) still builds;
    OUT/files/a/0/2/4, a/0/0/2     W2U's item archive and its system text archive, for
                                   `python3 tools/data/item_data.py dump OUT/files res/items` in the decomp
                                   (w2u-local/decomp/pilot/sync.sh does it), which then packs them back unchanged;
    OUT/items_reused.json          the reused slots: value, W2U's constant, the retail one, W2U's name.

The item icons are not part of this: W2U gives its items icons through a code patch of the icon tables
(tools/item_icons/build_item_icon_patch.py); the decomp has them in pml_item.c and res/items/*/icon.png.

--check: the reused slots' names in W2U's text are W2U's (not the retail item's), and every reused slot is one the
decomp names as unused, a Data Card, a second X item or an Apricorn.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_species_json import ROOT, parse_list, text_lines, write  # noqa: E402

ITEMS_H = ROOT / "include" / "Items.h"
NAMES = 64
ARCHIVES = ("a/0/2/4", "a/0/0/2")
REUSABLE = re.compile(r"ITEM_(UNUSED_\d+|DATA_CARD_\d+|[A-Z]+_APRICORN|X_[A-Z_]+_[236]|DIRE_HIT_[236])$")


def decomp_items(decomp: Path) -> tuple[Path, dict[int, str]]:
    path = next(p for p in (decomp / "generated" / "items.txt", decomp / "data" / "constants" / "items.txt")
                if p.exists())
    first: dict[int, str] = {}
    for name, value in parse_list(path).items():
        first.setdefault(value, name)
    return path, first


def reused_slots(decomp_first: dict[int, str]) -> dict[int, str]:
    """value -> W2U's constant, for the slots whose Items.h name isn't the decomp's (ITEM_NULL is ITEM_NONE)"""
    w2u = {int(m[2]): m[1] for m in re.finditer(r"^#define (ITEM_\w+) (\d+)\b", ITEMS_H.read_text(), re.M)}
    return {v: n for v, n in sorted(w2u.items()) if v and decomp_first.get(v) != n}


def constant_list(source: Path, reused: dict[int, str]) -> str:
    """The decomp's list, each reused slot's line as W2U's constant = value, then the retail name = value"""
    out, value = [], -1
    for raw in source.read_text(encoding="utf-8").splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line:
            out.append(raw)
            continue
        name, _, given = (part.strip() for part in line.partition("="))
        value = int(given, 0) if given else value + 1
        if value in reused and not name.startswith("ITEM_LAST"):
            out.append(f"{reused[value]} = {value}")
            out.append(f"{name} = {value}  # the retail slot W2U reuses")
        else:
            out.append(raw)
    return "\n".join(out) + "\n"


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True)
    parser.add_argument("--rom", type=Path, default=ROOT / "build" / "White2Upgrade.nds")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_items")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    source, first = decomp_items(args.decomp)
    reused = reused_slots(first)
    names = text_lines(NAMES)
    if args.check:
        problems = [f"{v} {n}: the decomp's {first.get(v)} isn't a slot W2U can reuse" for v, n in reused.items()
                    if not REUSABLE.match(first.get(v, ""))]
        problems += [f"{v} {n}: W2U's text names it {names.get(v)!r}" for v, n in reused.items()
                     if names.get(v, "???") in ("", "???")]
        for p in problems:
            print("CHECK:", p)
        print(f"{len(reused)} reused slots, {len(problems)} problems")
        sys.exit(1 if problems else 0)

    import ndspy.rom
    rom = ndspy.rom.NintendoDSRom.fromFile(args.rom)
    for archive in ARCHIVES:
        data = rom.getFileByName(archive)
        target = args.out / "files" / archive
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
    (args.out / "data" / "constants").mkdir(parents=True, exist_ok=True)
    (args.out / "data" / "constants" / "items.txt").write_text(constant_list(source, reused), encoding="utf-8",
                                                               newline="\n")
    write(args.out / "items_reused.json", [{"value": v, "constant": n, "retail": first.get(v), "name": names.get(v)}
                                          for v, n in reused.items()])
    print(f"{len(reused)} reused slots; {', '.join(ARCHIVES)} from {args.rom.name} -> {args.out}")


if __name__ == "__main__":
    main()
