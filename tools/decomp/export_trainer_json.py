#!/usr/bin/env python3
"""Export W2U's trainers for the pokebw2 decomp: the data the decomp's own trainer dump reads.

usage: python tools/decomp/export_trainer_json.py [--rom=build/White2Upgrade.nds] [--out=DIR] [--check]

The decomp keeps a trainer in res/trainers/data/<trainer>.json (trainer.schema.json: its name, class, battle style,
items, AI flags, money, reward, party and messages) in the order of generated/trainers.txt; tools/data/trainer_data.py
dumps those from a ROM's files once and packs the trainer (a/0/9/1) and party (a/0/9/2) archives and the message
tables (a/0/8/9, a/0/9/0) from them; the names and messages are system text 382 and 381.

W2U keeps the retail trainers' numbering (814 trainers, TRAINER_NONE included). This takes, from W2U's built ROM (what
it ships), those archives and the system text archive into OUT/files/ for
`python3 tools/data/trainer_data.py dump OUT/files res/trainers/data` in the decomp (w2u-local/decomp/pilot/sync.sh).

TRAINER_NONE: the decomp's format has no file for it and its entries are retail's empty placeholder (16-byte record,
6-byte party). W2U's trainer 0 is not empty (data/trainers/0.toml: class 0 with trainer 1's Blitzle party, from the
data conversion; nothing battles trainer 0), so the placeholder is written instead and --check reports it.

--check: the archives have one entry per retail trainer, and what trainer 0 holds.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_species_json import ROOT  # noqa: E402

ARCHIVES = ("a/0/9/1", "a/0/9/2", "a/0/8/9", "a/0/9/0", "a/0/0/2")
TRAINERS, PARTIES = "a/0/9/1", "a/0/9/2"
NONE_TRAINER, NONE_PARTY = bytes(16), bytes(6)
RETAIL_TRAINERS = 814


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--rom", type=Path, default=ROOT / "build" / "White2Upgrade.nds")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_trainers")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    import ndspy.narc
    import ndspy.rom
    rom = ndspy.rom.NintendoDSRom.fromFile(args.rom)
    trainers = ndspy.narc.NARC(rom.getFileByName(TRAINERS))
    parties = ndspy.narc.NARC(rom.getFileByName(PARTIES))
    if args.check:
        problems = [] if len(trainers.files) == len(parties.files) == RETAIL_TRAINERS else [
            f"{len(trainers.files)} trainers, {len(parties.files)} parties (retail {RETAIL_TRAINERS})"]
        zero = (trainers.files[0], parties.files[0])
        note = "empty" if zero == (NONE_TRAINER, NONE_PARTY) else \
            f"not empty ({zero[0].hex()} / {zero[1].hex()}): the placeholder is written instead"
        for p in problems:
            print("CHECK:", p)
        print(f"trainer 0: {note}; {len(problems)} problems")
        sys.exit(1 if problems else 0)

    trainers.files[0], parties.files[0] = NONE_TRAINER, NONE_PARTY
    for archive in ARCHIVES:
        data = {TRAINERS: trainers.save(), PARTIES: parties.save()}.get(archive) or rom.getFileByName(archive)
        target = args.out / "files" / archive
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
    print(f"{len(trainers.files)} trainers; {', '.join(ARCHIVES)} from {args.rom.name} -> {args.out}")


if __name__ == "__main__":
    main()
