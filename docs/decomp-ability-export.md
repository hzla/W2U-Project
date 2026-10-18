# Abilities in the decomp's format

`tools/decomp/export_ability_json.py` writes W2U's abilities (text banks 374, names, and 375, descriptions) in the
pokebw2 decomp's format: `data/abilities/<ability>.json` (`ability.schema.json`: name and description) and the
ordered list `data/constants/abilities.txt`, from which the decomp's `tools/text/text_sources.py` builds the name,
upper-case name and description banks. It also writes `mechanics.json`: which handler table of
`src/mechanics/abilities` serves which ability (the `W2U_MECHANIC(ABILITY, ...)` lines), for a decomp build's ability
table. Only the decomp's text files are read.

```sh
python tools/decomp/export_ability_json.py --decomp=PATH/TO/pokebw2 --check
```

Output in `work/decomp_abilities/` (ignored). `--check` compares abilities 0-164 with the decomp's own JSON (the
retail text), checks that no W2U-only escape is left in any text, and that every mechanic route names an ability with
text.

Naming as for species: abilities 0-164 keep the decomp's constants; 165 and up are `ABILITY_` + the English name (the
second As One is `ABILITY_AS_ONE_2`); a file is named after its constant (`ABILITY_AIR_LOCK`: `air_lock.json`). Text:
W2U's banks write line breaks both as `\n` escapes (the retail entries) and as real line breaks (the entries W2U
added); both become real line breaks, as the decomp's JSON has them, `\"` a plain quote, and the end marker `$` is
dropped.

As of 2026-10-17 (decomp ee3730d6d): 314 abilities (150 new constants), the 164 retail ones identical to the decomp's
text, 86 mechanic routes (Damp and Intimidate replace retail handlers; 84 are new abilities, 53 of them above 255).

What a decomp-based W2U still needs for its abilities:
- abilities above 255: a Pokémon's ability is a byte in the retail party and box data; W2U stores the high bits
  elsewhere (Pokeweb's packing) and reads them in its own code, which has to move too;
- battle messages: the mechanics' own messages (text bank 18 entries W2U added) are not in the decomp's banks yet;
- mechanics that work through the engine's own checks rather than their handlers (Propeller Tail and Stalwart:
  W2U's resident core wraps the redirection checks) need those hooks as source edits.
