#!/usr/bin/env python3
"""Export W2U's Fairy graphics for the pokebw2 decomp: the move-button palette and the type icons, as the decomp's files.

usage: python tools/decomp/export_battle_graphics.py --decomp=PATH [--rom=build/White2Upgrade.nds] [--out=DIR] [--check]

The decomp keeps each 2D graphics archive as a directory of res/graphics/ (tools/data/graphics_archive.py): a palette
as a JASC `.pal`, a character resource as an indexed `.png`, each named after its number in the archive, packed back
into the ROM's archive; a member past the archive's last is added by the next number's file.

W2U's Fairy (type 17) has these graphics, all members of archives it stages under data/graphics/ (the retail game has
no Fairy, and its type 17 is the typeless type, with no graphics of its own):

    a/0/1/1   btlv            member 572, a palette W2U adds: the move-menu button's (Fairy_BattleLimitAdjust.s
                              writes 572 after the 17 retail entries of the table of palettes by type; the retail
                              ones are members 464-480)
    a/0/8/2   app_menu_common 33, the type icons' palette (Fairy's two colors, in palette 2), and 51, the icon: file
                              0x22 + type, which for type 17 is a contest category's icon. Every menu draws the
                              type icons from it: the battle's move menu, the summary, the Pokedex, the bag, the PC
    a/1/2/5   waza_oshie      22 and 23, the same palette and the move reminder's own copy of the icons

W2U also gives type 17 palette 2 (data/pml/types/type_palette_map.bin, which its GetPokemonTypeIconPalette reads;
the decomp's table is AppMenuCommon_GetTypeIconPaletteIndex's sTypeIconPalettes, which patch_resident.py changes the
same way). The tables of the move buttons' palettes and the type icons' are code, not archive members: this writes only
the files, from W2U's staged copies (what its build packs):

    OUT/res/graphics/<archive>/<number>.pal|png   for w2u-local/decomp/pilot/sync.sh to copy over the decomp's

Packed again by the decomp, the colors and pixels are W2U's. The bytes differ in what the DS ignores: bit 15 of a
palette entry (W2U's editor sets it on some colors; the packer keeps the retail member's, and clears it in a new
one) and the new palette's format field (the packer gives a 256-color palette format 4; W2U's 572 is 3, as the
retail button palettes are, and the game reads only its colors).

--check: the staged members are the palette and character resources the list says (and, with --rom, the same bytes as
the built ROM's), the retail members they replace are in the decomp's directories (not in black2/ or white2/, which
would hide them), the new one is not, and the table entry Fairy_BattleLimitAdjust.s writes is the member listed.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from export_species_json import ROOT  # noqa: E402

GRAPHICS = ROOT / "data" / "graphics"
ADJUST = ROOT / "src" / "type_expansion" / "Fairy_BattleLimitAdjust.s"
# W2U's: the new member of archive 11, from the .word the patch writes at the table's end
BUTTON_PALETTE = int(re.search(r"^FULL_COPY_168_0x021F38E8:\s*\.word (\d+)", ADJUST.read_text(), re.M)[1])
# (the decomp's directory, its archive, W2U's staging directory, the file name of member N there, the members, and
# the kind of each: RLCN a palette, RGCN a character resource)
ARCHIVES = (
    ("btlv", "a/0/1/1", "battle", "{n}", {BUTTON_PALETTE: b"RLCN"}),
    ("app_menu_common", "a/0/8/2", "ui", "082_{n:08d}.bin", {33: b"RLCN", 51: b"RGCN"}),
    ("waza_oshie", "a/1/2/5", "ui_2", "125_{n:08d}.bin", {22: b"RLCN", 23: b"RGCN"}),
)


def staged(staging: str, pattern: str) -> list[bytes]:
    """W2U's whole staged archive, member by member (the character resources' preview palettes are among them)."""
    count = len(list((GRAPHICS / staging).iterdir()))
    return [(GRAPHICS / staging / pattern.format(n=n)).read_bytes() for n in range(count)]


def number_digits(directory: Path) -> int:
    """How many digits the decomp's files of a directory have (btlv's members are 000-571)."""
    return max(len(p.stem) for p in directory.rglob("*") if p.stem.isdigit())


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True)
    parser.add_argument("--rom", type=Path, default=ROOT / "build" / "White2Upgrade.nds")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_battle_graphics")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    sys.path.insert(0, str(args.decomp))
    from tools.data.graphics_archive import member_file  # the decomp's own dump of a member  # noqa: E402

    rom = None
    if args.check and args.rom.exists():
        import ndspy.rom
        rom = ndspy.rom.NintendoDSRom.fromFile(str(args.rom))
    problems = []
    written = []
    for directory, archive, staging, pattern, kinds in ARCHIVES:
        res = args.decomp / "res" / "graphics" / directory
        members = staged(staging, pattern)
        digits = number_digits(res)
        retail = {}   # the decomp's files by member number
        for path in res.rglob("*"):
            if path.stem.isdigit():
                retail.setdefault(int(path.stem), []).append(path)
        built = None
        if rom is not None:
            import ndspy.narc
            built = ndspy.narc.NARC(rom.getFileByName(archive)).files
        for n, kind in kinds.items():
            data = members[n]
            name, content = member_file(f"{n:0{digits}d}", data, members, n)
            if args.check:
                if data[:4] != kind:
                    problems.append(f"{archive} member {n}: W2U's staged file is {bytes(data[:4])!r}, not {kind!r}")
                if built is not None and bytes(built[n]) != data:
                    problems.append(f"{archive} member {n}: the built ROM's differs from the staged file")
                if n in retail and [p.parent for p in retail[n]] != [res]:
                    problems.append(f"{res}: member {n} is in {[str(p.relative_to(res)) for p in retail[n]]}, not at the top")
                if n not in retail and n != max(retail) + 1:
                    problems.append(f"{res}: member {n} is not the archive's next ({max(retail) + 1})")
                continue
            target = args.out / "res" / "graphics" / directory / name
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(content)
            written.append(f"{directory}/{name}")
    if args.check:
        for p in problems:
            print("CHECK:", p)
        print(f"{sum(len(a[4]) for a in ARCHIVES)} members, {len(problems)} problems")
        sys.exit(1 if problems else 0)
    print(f"battle graphics: {', '.join(written)} -> {args.out}")


if __name__ == "__main__":
    main()
