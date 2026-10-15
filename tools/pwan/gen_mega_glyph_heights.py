#!/usr/bin/env python3
"""Mega glyph placement table: src/pokeweb_gameplay/megab2w2/mb_mega_glyph_heights.inc.

For every Mega form (W2U_MEGA_TABLE in w2u_mega.cpp + Rayquaza's Dragon Ascent form) with a PWAN asset in
assets/pokeweb_pwan/config.bin: the topmost opaque row and the horizontal centre of the head (the topmost 16 rows) of the front and back
sprites, over all animation frames, in 96x96 canvas pixels. mb_mega_extras.cpp places the glyph above the sprite from these
(the battle's MCSS ground point is canvas row 88 / the canvas centre column, measured in battle).
Sides streamed as A3I5 (data/graphics/w2anim/sprites.toml) are measured from their source MANI at their placement, in
the same canvas coordinates (their top can be above the canvas: the top fields are signed); a side's manual offset
correction moves its row as well, and so does the build's grounding (sprites.toml `grounding`).

usage: python tools/pwan/gen_mega_glyph_heights.py   (rerun when a Mega's PWAN or sprites.toml changes)
"""

from __future__ import annotations

import re
import sys
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from pwan_config import parse_config  # noqa: E402
import ground_pwan_assets as G  # noqa: E402
sys.path.insert(0, str(ROOT / "tools" / "w2anim"))
import a3i5  # noqa: E402
from build_w2anim_streams import a3i5_bottom, a3i5_max_sink, a3i5_top, ground_raise, load_grounding  # noqa: E402

SPRITES = ROOT / "data" / "graphics" / "w2anim" / "sprites.toml"
A3I5_SOURCES = ROOT / "data" / "graphics" / "w2anim" / "a3i5"

OUT = ROOT / "src" / "pokeweb_gameplay" / "megab2w2" / "mb_mega_glyph_heights.inc"
HEAD_ROWS = 16


def species_ids() -> dict[str, int]:
    text = (ROOT / "include" / "species_ids.h").read_text(encoding="utf-8")
    return {m.group(1): int(m.group(2)) for m in re.finditer(r"#define\s+(SPECIES_\w+)\s+(\d+)", text)}


def mega_forms() -> list[tuple[int, int]]:
    text = (ROOT / "src" / "pokeweb_gameplay" / "w2u_mega.cpp").read_text(encoding="utf-8")
    table = text[text.index("W2U_MEGA_TABLE[] = {"):]
    table = table[:table.index("};")]
    ids = species_ids()
    forms = {(ids[m.group(1)], int(m.group(2))) for m in re.finditer(r"\{(SPECIES_\w+),\s*ITEM_\w+,\s*(\d+)\}", table)}
    form = re.search(r"W2U_RAYQUAZA_DRAGON_ASCENT_MEGA_FORM\s*=\s*(\d+)", text)
    if form:
        forms.add((ids["SPECIES_RAYQUAZA"], int(form.group(1))))
    return sorted(forms)


def side_box(asset: int, side: str) -> tuple[int, int] | None:
    path = ROOT / "assets" / "pokeweb_pwan" / f"{asset}_{side}.pwan"
    if not path.exists():
        return None
    _, frames, _ = G.read_pwan(path)
    b = G.animation_bounds(frames)
    if b["minY"] is None:
        return None
    # centre of the head: the opaque columns of the topmost HEAD_ROWS rows (all frames), not of the whole sprite
    # (a tail or a wing would pull the glyph off the head)
    cols = [i % G.WIDTH for f in frames for i, v in enumerate(f)
            if v and b["minY"] <= i // G.WIDTH < b["minY"] + HEAD_ROWS]
    return b["minY"], (min(cols) + max(cols) + 1) // 2


def a3i5_box(row: dict, asset: int, side: str, grounding: str) -> tuple[int, int] | None:
    """An A3I5 side: its source MANI's frames at the build's placement, in canvas coordinates."""
    m = a3i5.parse_mani((A3I5_SOURCES / row["source"]).read_bytes())
    x0, y0 = a3i5.place(m, a3i5_bottom(ROOT / "assets" / "pokeweb_pwan" / f"{asset}_{side}.pwan", grounding),
                        int(row.get("altitude", 0)), row.get("offset"), a3i5_top(side, grounding),
                        a3i5_max_sink(side, grounding))
    w, h = m["w"], m["h"]
    frames = [a3i5.frame_rows(m, u) for u in sorted({u for u, d in m["seq"]})]
    opaque = lambda rows, x, y: rows[y * a3i5.ROW + x] >> 5
    top = min(y for rows in frames for y in range(h) if any(opaque(rows, x, y) for x in range(w)))
    cols = [x for rows in frames for y in range(top, min(h, top + HEAD_ROWS)) for x in range(w) if opaque(rows, x, y)]
    return a3i5.GROUND_ROW + y0 + top, G.WIDTH // 2 + x0 + (min(cols) + max(cols) + 1) // 2


def side_place(settings: dict, species: int, form: int, asset: int, side: str, grounding: str) -> tuple[int, int] | None:
    row = settings.get((species, form, side), {})
    if row.get("format") == "a3i5":
        return a3i5_box(row, asset, side, grounding)
    box = side_box(asset, side)
    if box:
        box = (box[0] - ground_raise(ROOT / "assets" / "pokeweb_pwan" / f"{asset}_{side}.pwan", grounding), box[1])
    if box and row.get("offset"):
        dx, dy = a3i5.check_offset(row["offset"])
        box = (box[0] + dy, box[1] + dx)
    return box


def main() -> int:
    config, _ = parse_config(ROOT / "assets" / "pokeweb_pwan" / "config.bin")
    settings = {(int(r["species"]), int(r.get("form", 0)), r["side"]): r
                for r in tomllib.loads(SPRITES.read_text(encoding="utf-8")).get("side", [])} if SPRITES.exists() else {}
    grounding = load_grounding(SPRITES)
    rows, missing = [], []
    for species, form in mega_forms():
        entry = config.get((species, form))
        front = entry and side_place(settings, species, form, entry["frontIndex"], "front", grounding["front"])
        back = entry and side_place(settings, species, form, entry["backIndex"], "back", grounding["back"])
        if not front or not back:
            missing.append((species, form))
            continue
        if not all(-128 <= v <= 127 for v in (front[0], back[0])) or not all(0 <= v <= 255 for v in (front[1], back[1])):
            raise ValueError(f"{species}/{form}: glyph place {front}, {back} outside the table's range")
        rows.append(f"    {{ {species}, {form}, {front[0]}, {front[1]}, {back[0]}, {back[1]} }},")
    OUT.write_text("// GENERATED by tools/pwan/gen_mega_glyph_heights.py: {species, form, front top row, front centre x,\n"
                   "// back top row, back centre x} in 96x96 canvas pixels (all animation frames; A3I5 sides at their\n"
                   "// placement, top rows signed).\n"
                   + "\n".join(rows) + "\n", encoding="utf-8", newline="\n")
    print(f"{len(rows)} Mega forms written to {OUT.relative_to(ROOT)}; without PWAN: {missing}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
