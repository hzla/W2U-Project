# Species data in the decomp's format

`tools/decomp/export_species_json.py` writes W2U's species data (`data/pml`: personal, learnset and evolution TOML,
`RegionalDex.bin`) in the pokebw2 decomp's format: `data/pokemon/<species>/data.json`, a `form_<n>.json` per form
record and `data/pokemon/forms.json`, with the decomp's constant names (`species.schema.json`, packed by the decomp's
`tools/data/species_data.py`). The TOML stays the source of truth; this is the step that lets a decomp-based W2U take
its data from ours. It reads only the decomp's text files (constant lists, `include/constants/pokemon.h`, the tutor
tables in `src/ov036/scrcmd_shop.c`).

```sh
python tools/decomp/export_species_json.py --decomp=PATH/TO/pokebw2 --check
```

Output in `work/decomp_species/` (ignored): the JSON, `constants_added.json` (the names W2U adds, with their values)
and `report.md`. `--check` converts each record back and compares it with the TOML (the round trip), and compares
species 1-649 with the decomp's retail data.

Naming: the decomp's constant where a value means the same in W2U; species 650-1023 as `SPECIES_<NAME>` from their
English names (Rowlet is `SPECIES_ROWLET`); new moves from W2U's move enum, new abilities from their names (the second
As One is `ABILITY_AS_ONE_2`); type 17 is `TYPE_FAIRY` (the decomp's `TYPE_NULL`); evolution methods 28-31 from W2U's
enum. Heights are written in decimetres (W2U's TOML holds centimetres).

As of 2026-10-15 (decomp 0919097ff): 1024 species and 251 form records, every one round trips. What a W2U layout of the
decomp's packer would have to change:

- W2U numbers species 650-1023 where the decomp has the egg, the bad egg and the Pokéstar Studios species, and has
  no records for those; its records 1024 and 1025 (folders `egg/`, `bad_egg/`) are Deoxys's forms 1 and 2;
- 15 records no species points at (1041, 1050, 1076, 1082, 1087, 1096-1100, 1108, 1128, 1129, 1157, 1171);
- 8 evolution slots (Eevee uses the eighth, Sylveon); the decomp packs 7;
- W2U has no baby species or egg moves of its own (the retail archives): species 1-649 take the decomp's.

Data found on the way: Corsola's, Galarian Corsola's and Snorunt's 5% held items are 648 / 649 (Gen 6's Luminous
Moss and Snowball), past the end of the item table (638).
