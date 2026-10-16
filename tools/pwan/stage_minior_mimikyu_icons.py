#!/usr/bin/env python3
"""Stage Minior's and Mimikyu's form icons from Essentials icons.

usage: python tools/pwan/stage_minior_mimikyu_icons.py [ICONS_DIR]

import_minior.py and import_disguise.py copied the species icon to every Minior form and to Busted Mimikyu, so the
Meteor and Core forms and Busted Mimikyu all showed one icon. This writes each form's own icon to its form slot
(docs/pokemon-icons.md) from the Essentials icons (ICONS_DIR, default stage_form_icon_assets.ESSENTIALS_ICONS):
  - Minior forms 1-6 (Meteor): MINIOR (Essentials has one Meteor icon; the colours look the same in game),
    forms 7-13 (Core): MINIOR_7 ... MINIOR_13;
  - Busted Mimikyu: MIMIKYU_1;
  - the species icons too: Minior's (form 0, Red Meteor) showed the Red Core, and Mimikyu's was on a palette that
    turned it olive.
Converted as stage_form_icon_assets.py does (two frames, 64 -> 32, the closest of the 3 shared palettes), then moved
to where the Gen 7 icons sit (Minior 1 px left and 5 down, Mimikyu 3 down) so a form lines up with its species' icon.
"""

from __future__ import annotations

import sys
from pathlib import Path

from PIL import Image

import stage_form_icon_assets as S

MINIOR, MIMIKYU = 774, 778
GEN7_SPECIES_START, GEN7_ICON_START = 722, 1904
ICON_FORM_START, FORM_PALETTE_START = 1456, 724
SHIFT = {MINIOR: (-1, 5), MIMIKYU: (0, 3)}


def form_slot(sprite_offset: int, form: int) -> tuple[int, int]:
    """Icon member and palette map entry of a form (w2u_pokegra.cpp)."""
    index = sprite_offset + form - 1
    return ICON_FORM_START + 2 * index, FORM_PALETTE_START + index


def sprite_offset(species: int) -> int:
    import tomllib
    personal = S.ROOT / "data" / "pml" / str(species) / "personal.toml"
    return next(iter(tomllib.loads(personal.read_text(encoding="utf-8")).values()))["Form Sprite Offset"]


def stage(target: int, palette_key: int, species: int, source: Path, palettes, palette_map: bytearray) -> dict:
    image = S.render_icon_sheet(source)
    dx, dy = SHIFT[species]
    image = image.transform(image.size, Image.Transform.AFFINE, (1, 0, -dx, 0, 1, -dy))
    palette = S.choose_palette(image, palettes)
    template = bytearray(S.icon_path(2408).read_bytes())
    template[-0x400:] = S.tile_icon_pixels(image, palettes[palette])
    S.icon_path(target).write_bytes(bytes(template))
    if not S.icon_path(target + 1).exists():
        S.icon_path(target + 1).write_bytes(b"")
    palette_map[palette_key] = palette | (palette << 4)
    return {"targetIcon": target, "paletteKey": palette_key, "sourceStem": source.stem, "palette": palette}


def main() -> None:
    icons = Path(sys.argv[1]) if len(sys.argv) > 1 else S.ESSENTIALS_ICONS
    palettes = S.read_icon_palettes()
    palette_map = bytearray(S.PALETTE_MAP.read_bytes())
    jobs = [(GEN7_ICON_START + 2 * (MINIOR - GEN7_SPECIES_START), MINIOR, MINIOR, "MINIOR"),
            (GEN7_ICON_START + 2 * (MIMIKYU - GEN7_SPECIES_START), MIMIKYU, MIMIKYU, "MIMIKYU")]
    minior, mimikyu = sprite_offset(MINIOR), sprite_offset(MIMIKYU)
    for form in range(1, 14):
        jobs.append((*form_slot(minior, form), MINIOR, "MINIOR" if form <= 6 else "MINIOR_%d" % form))
    jobs.append((*form_slot(mimikyu, 1), MIMIKYU, "MIMIKYU_1"))
    for target, key, species, stem in jobs:
        row = stage(target, key, species, icons / f"{stem}.png", palettes, palette_map)
        print("icon %4d  palette entry %4d = %d  %s" % (row["targetIcon"], key, row["palette"], stem))
    S.PALETTE_MAP.write_bytes(bytes(palette_map))


if __name__ == "__main__":
    main()
