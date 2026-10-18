# Moves in the decomp's format

`tools/decomp/export_move_json.py` writes W2U's moves (`data/pml/moves/<id>.toml`, text banks 403, names, and 402,
descriptions) in the pokebw2 decomp's format: `data/moves/<move>/data.json` (`move.schema.json`: name, description
and the 36-byte record of the move data archive `a/0/2/1`, by constant names) and the ordered list
`data/constants/moves.txt`, from which the decomp's `tools/data/move_data.py` packs the archive and
`tools/text/text_sources.py` the name and description banks. Only the decomp's files are read.

```sh
python tools/decomp/export_move_json.py --decomp=PATH/TO/pokebw2 --check
```

Output in `work/decomp_moves/` (ignored), plus `constants_added.json` (the constants the JSON names that the decomp
doesn't have) and `battle_h_flags.txt` (their `#define` lines for the move flags, for `include/constants/battle.h`).

How: each TOML is packed with W2U's own serializer (`tools/mkdata`, format `moves`, as the build does), and the record
is read back the way the decomp's `move_data.py` reads one, so both sides' field order is the record's own and the
decomp's archive packed from the JSON is W2U's, byte for byte.

Names: moves 0-559 keep the decomp's constants, 560 and up are `MOVE_` + W2U's enum name; a folder is named after its
constant (`MOVE_AIR_SLASH`: `air_slash/`). Values are written by the decomp's names (`battle.h`, `move_effects.h`,
`types.txt`); a value without one is a number, as the decomp's own dump writes it (37 effects of W2U's added moves),
except where the schema wants a name:
- the move flags W2U added: `MOVE_FLAG_POWDER` (bit 14), `MOVE_FLAG_WIND` (16), `MOVE_FLAG_SHARP` (17),
  `MOVE_FLAG_HEALING_PROPERTY` (18), `MOVE_FLAG_DANCE` (19), `MOVE_FLAG_BULLET` (20), `MOVE_FLAG_BITE` (21),
  `MOVE_FLAG_PULSE` (22);
- type 17, `TYPE_FAIRY` (the decomp's `TYPE_NULL`, which no move uses).

`--check` compares moves 1-559 with the decomp's own JSON. W2U changes retail moves on purpose, so the differences are
counted by field; it fails on a W2U escape left in the text or a value the schema needs a name for that has none.
Leer's retail description ends in `\x{ffff}` padding that W2U's text drops; the retail line is kept.

As of 2026-10-18 (decomp ee3730d6d): 920 moves, 360 new; W2U's changes to the retail ones: flags 142, power 51,
PP 16, accuracy 11, priority 4, stat changes 3, target 3, type 3 (Fairy), effect 2, inflicted condition 2; the text of
all 559 identical. A decomp build with these files has a move archive identical to W2U's built records (920 of 920).

What a decomp-based W2U still needs for its moves:
- the type chart and type names for Fairy (the three retail moves W2U made Fairy, and the added Fairy moves, index
  the 17-type chart past its end in a vanilla engine);
- the added moves' effects (the 37 effect numbers without a decomp name, and the handlers of W2U's added moves);
- Easy Chat keeps the retail moves (its word tables are in the main program), as it keeps the retail abilities.
