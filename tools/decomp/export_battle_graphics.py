#!/usr/bin/env python3
"""Export W2U's battle and type graphics for the pokebw2 decomp: Fairy's button palette and icons, the command screen's
indicator sheet and the terrain floors, as the decomp's files.

usage: python tools/decomp/export_battle_graphics.py --decomp=PATH [--rom=build/White2Upgrade.nds] [--retail=ROM]
                                                     [--out=DIR] [--check]

The decomp keeps each 2D graphics archive as a directory of res/graphics/ (tools/data/graphics_archive.py): a palette
as a JASC `.pal`, a character resource as an indexed `.png`, any other resource as itself (`.ncer`, `.nanr`, `.nsbtx`,
`.bin`), each named after its number in the archive, packed back into the ROM's archive; a member past the archive's
last is added by the next number's file.

W2U's archives that differ from the retail game's in graphics, besides what the other exporters cover, are these
members, all of archives it stages under data/graphics/:

  Fairy (type 17; the retail game has none, and its type 17 is the typeless type, with no graphics of its own):
    a/0/1/1   btlv            member 572, a palette W2U adds: the move-menu button's (Fairy_BattleLimitAdjust.s
                              writes 572 after the 17 retail entries of the table of palettes by type; the retail
                              ones are members 464-480)
    a/0/8/2   app_menu_common 33, the type icons' palette (Fairy's two colors, in palette 2), and 51, the icon: file
                              0x22 + type, which for type 17 is a contest category's icon. Every menu draws the
                              type icons from it: the battle's move menu, the summary, the Pokedex, the bag, the PC
    a/1/2/5   waza_oshie      22 and 23, the same palette and the move reminder's own copy of the icons

  The command screen's indicators (tools/graphics/build_command_indicators.py, w2u_terrain_indicator.cpp):
    a/0/1/1   btlv            420-423, the screen's sprite set (characters, palette, cells, animations: the WEATHER
                              panel, the tile and party-icon animations; btlv_input.c loads them), which W2U adds to:
                              80 tiles (a TERRAIN label and the slots of a strong weather's and a terrain's icon),
                              colors in palette slots the retail sheet leaves empty, 5 cells, 3 animations, and the
                              animation 0x13 (the retail one for a fifth weather, which no retail weather has) as the
                              strong winds' icon. Every retail tile, cell and animation but that one is as it was.
                              941, a raw table (not a Nitro resource, so a `.bin`): the indicators' frames (weather
                              3 kinds x 3 frames, terrain 4 x 2, 480 bytes each) and the terrain palettes, which W2U's
                              code copies into the sheet's slots when the panel appears

  The terrain floors (tools/graphics/build_terrain_texture_mvp.py, w2u_terrain_texture.cpp):
    a/0/1/1   btlv            573-940, 92 groups of four NSBTX (Electric, Grassy, Misty, Psychic): each a battle
                              background's texture block with its floor, and for the outdoor ones its sky, redrawn.
                              w2u_terrain_texture_mappings.inc lists the groups by the retail background's number

The tables of the move buttons' palettes and the type icons' are code, not archive members (W2U also gives type 17
palette 2: data/pml/types/type_palette_map.bin, which patch_resident.py reads): this writes only the files, from W2U's
staged copies (what its build packs):

    OUT/res/graphics/<archive>/<number>.<extension>   for w2u-local/decomp/pilot/sync.sh to copy over the decomp's

The command screen's and the terrain floors' members are data for code the decomp doesn't have (W2U's C++ view): the
retail btlv_input.c loads 420-423 as it did, and nothing loads 573-941. They are here so that a build has W2U's
archive, and its member numbers, for when that code is ported. No retail member changes except 420-423.

Packed again by the decomp, the members' colors and pixels are W2U's. The bytes are too, except where the packer
writes a resource's header itself: bit 15 of a palette entry (W2U's editor sets it on some colors; the packer keeps
the retail member's, and clears it in a new one) and the new palette's format field (the packer gives a 256-color
palette format 4; W2U's 572 is 3, as the retail button palettes are, and the game reads only its colors).

--check: the staged members are the kinds the list says (and, with --rom, the same bytes as the built ROM's), the
retail members they replace are in the decomp's directories (not in black2/ or white2/, which would hide them), the new
ones are not and follow the last in order, the table entry Fairy_BattleLimitAdjust.s writes is the member listed, and
(with the retail ROM, --retail: Port-Pokeweb/cleanwhite2.nds) W2U's staged archive is the retail one in every member
but the listed ones: the listed members past the retail archive's last are all it adds.
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
TERRAIN_MAPPINGS = ROOT / "src" / "pokeweb_gameplay" / "w2u_terrain_texture_mappings.inc"
INDICATOR_CODE = ROOT / "src" / "pokeweb_gameplay" / "w2u_terrain_indicator.cpp"
RETAIL_ROM = ROOT.parent / "Port-Pokeweb" / "cleanwhite2.nds"
# W2U's: the new member of archive 11, from the .word the patch writes at the table's end
BUTTON_PALETTE = int(re.search(r"^FULL_COPY_168_0x021F38E8:\s*\.word (\d+)", ADJUST.read_text(), re.M)[1])
# The terrain floors: four consecutive members from the first each mapping line names ({ field, first, nsbta, ... })
TERRAIN_FLOORS = sorted(n for first in re.findall(r"^\{ \d+u, (\d+)u,", TERRAIN_MAPPINGS.read_text(), re.M)
                        for n in range(int(first), int(first) + 4))
# The indicators' art, which the code reads whole by member number
INDICATOR_ART = int(re.search(r"W2U_INDICATOR_ART_MEMBER = (\d+)u", INDICATOR_CODE.read_text())[1])
# The command screen's sprite set (build_command_indicators.py: battgra 420-423): characters, palette, cells, animations
INDICATOR_SHEET = {420: b"RGCN", 421: b"RLCN", 422: b"RECN", 423: b"RNAN"}
# (the decomp's directory, its archive, W2U's staging directory, the file name of member N there, the members, and
# the kind of each: the magic of its resource, RLCN a palette, RGCN a character resource, BTX0 a texture archive;
# b"" for a member that is no resource)
ARCHIVES = (
    ("btlv", "a/0/1/1", "battle", "{n}",
     {**INDICATOR_SHEET, BUTTON_PALETTE: b"RLCN", **{n: b"BTX0" for n in TERRAIN_FLOORS}, INDICATOR_ART: b""}),
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
    parser.add_argument("--retail", type=Path, default=RETAIL_ROM)
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_battle_graphics")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    sys.path.insert(0, str(args.decomp))
    from tools.data.graphics_archive import member_file  # the decomp's own dump of a member  # noqa: E402

    roms = {}
    if args.check:
        import ndspy.narc
        import ndspy.rom
        roms = {name: ndspy.rom.NintendoDSRom.fromFile(str(path))
                for name, path in (("built", args.rom), ("retail", args.retail)) if path.exists()}
    problems = []
    written = []
    for directory, archive, staging, pattern, kinds in ARCHIVES:
        res = args.decomp / "res" / "graphics" / directory
        members = staged(staging, pattern)
        digits = number_digits(res)
        existing = {}   # the decomp's files by member number
        for path in res.rglob("*"):
            if path.stem.isdigit():
                existing.setdefault(int(path.stem), []).append(path)
        files = {name: [bytes(m) for m in ndspy.narc.NARC(rom.getFileByName(archive)).files]
                 for name, rom in roms.items()} if args.check else {}
        new = sorted(n for n in kinds if n not in existing)
        if args.check:
            if new and new != list(range(max(existing) + 1, max(existing) + 1 + len(new))):
                problems.append(f"{res}: the new members {new[:3]}... don't follow the archive's last ({max(existing)})")
            if "retail" in files:
                retail = files["retail"]
                changed = {n for n in range(len(retail)) if members[n] != retail[n]}
                listed = {n for n in kinds if n < len(retail)}
                if changed != listed:
                    problems.append(f"{archive}: W2U changes members {sorted(changed)} of the retail archive "
                                    f"({len(retail)} members), the list has {sorted(listed)}")
                added = set(range(len(retail), len(members)))
                if added != set(kinds) - listed:
                    problems.append(f"{archive}: W2U adds {len(added)} members past the retail archive's, the list "
                                    f"{len(set(kinds) - listed)}")
        for n, kind in kinds.items():
            data = members[n]
            name, content = member_file(f"{n:0{digits}d}", data, members, n)
            if args.check:
                if kind and data[:4] != kind:
                    problems.append(f"{archive} member {n}: W2U's staged file is {bytes(data[:4])!r}, not {kind!r}")
                if "built" in files and files["built"][n] != data:
                    problems.append(f"{archive} member {n}: the built ROM's differs from the staged file")
                if n in existing and [p.parent for p in existing[n]] != [res]:
                    problems.append(f"{res}: member {n} is in {[str(p.relative_to(res)) for p in existing[n]]}, not at the top")
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
    print(f"battle graphics: {len(written)} files ({', '.join(written[:8])}, ...) -> {args.out}")


if __name__ == "__main__":
    main()
