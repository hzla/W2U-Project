# Save format: what W2U changes

White 2 (the Black 2 port differs and is not covered). Written 2026-10-15 so that W2U saves stay readable when the
code moves elsewhere (a decomp-based build, github.com/fuddlesworth/pokebw2, or anything else): every place where a
W2U save differs from a retail White 2 save, how a W2U build reads and writes it, and what a retail save needs to be
used. Offsets are from the start of a save half unless they say otherwise.

## Save file basics (unchanged)

Two halves (main at 0x00000, backup at 0x26000), each a list of blocks on 0x100 boundaries. A block at offset O of
length L has a footer at O+L (u16 counter, u16 CRC-16/CCITT of the block). The checksum table at 0x25F00 (0x94
bytes) holds every block's CRC in block order; its own CRC is at 0x25FA2. The block lengths come from the game's
size table (`getSizeofPokedexData` and its siblings), so a block whose size W2U changes moves its own footer and CRC.
The Pokédex block's change does not move the blocks after it: 0x4D4 and 0x4DC plus the 4-byte footer both round up
to the same 0x500 slot.

## 1. Pokédex: block 54 (0x36) at 0x21400, 0x4D4 bytes (retail 0x4DC)

`src/pokedex_expansion/w2u_pokedex.cpp` (`PokedexSave`, `getSizeofPokedexData`, `initPokedex` and the
`PokeDex_*` accessors replaced) keeps species 1-672 in the retail bit lists and stores species 673-1023 in the area
retail uses for foreign-language entries. The decomp's retail struct is `PokeDexSave` in `include/save/pokedex.h`.

| Retail field (decomp name) | Retail offset, size | W2U field | W2U offset, size |
|---|---|---|---|
| `magic` 0xBEEFCAFE | 0x000, 4 | `zukanMagic` (same value) | 0x000, 4 |
| bit fields (national obtained, mode, last species, ...) | 0x004, 4 | `flags` | 0x004, 4 |
| `caught` | 0x008, 0x54 | `caught` | 0x008, 0x54 |
| `seen[4]` (male, female, shiny male, shiny female) | 0x05C, 4 x 0x54 | `seen[4]` | 0x05C, 4 x 0x54 |
| `shown[4]` (which sex / shininess the dex shows) | 0x1AC, 4 x 0x54 | `seenMale`, `seenFemale`, `shinyMale`, `shinyFemale` | 0x1AC, 4 x 0x54 |
| `seenForms` (normal, shiny) | 0x2FC, 2 x 0x0B | `formFlags[2]` | 0x2FC, 2 x 0x09 |
| `shownForms` (normal, shiny) | 0x312, 2 x 0x0B | `forms`, `shinyForms` | 0x30E, 2 x 0x09 |
| `languages` (7 bits per species 1-493) | 0x328, 0x1B0 | `textVersionUp`: species 673-1023 | 0x320, 0x1B0 |
| `spindaPersonality` | 0x4D8, 4 | `pachiRandom` | 0x4D0, 4 |

- The species lists are 0x54 bytes = 672 bits (species - 1), so species 650-672 fit the retail lists as they are.
- Species 673-1023 (`POKEDEX_EXTENSION_SPECIES_MIN` .. `SPECIES_CNT`): nine lists of 44 bytes (352 bits, bit =
  species - 673) inside `textVersionUp`, in this order: caught, seen[0..3], the four shown lists (`seenMale`,
  `seenFemale`, `shinyMale`, `shinyFemale`). 396 of the 432 bytes; the last 36 are unused.
- Form lists: 9 bytes (72 form bits) each instead of 11 (88), in the order of `pokemonFormList`
  (`data/pml/poke_form_list.bin`, 0xB7 entries; a species' forms take `form_count` consecutive bits). From
  `formFlags` on, every field sits 8 bytes earlier than in retail.
- **Known limitation (found 2026-10-15):** W2U's form list needs 433 form bits (182 species with forms), the lists
  hold 72, and `SetDrawData` skips any bit past 72 without a word. So for 151 of the 182 species (from Muk, species
  89, on; including the later regional forms) the Pokédex records no seen / shown forms. Fixing it needs about 55
  bytes per list instead of 9 (4 lists: about 0xB0 more bytes), more than the block's spare room (0x500-byte slot,
  0x4D8 used with the footer) and the extension area's 36 unused bytes: a save-layout change, best made together
  with the move to the decomp (or by moving the form lists into a new area).
- Foreign-language Pokédex entries are not kept (the area holds the extension lists).

**A retail save in a W2U build** (derived from the two layouts, partly confirmed in game): the block's CRC is checked
over 0x4D4 bytes, so a retail block reads as corrupt. The game loads it anyway at start, but the full check at game
clear calls the save corrupted, rewrites it through its recovery path and aborts there (the Hall of Fame never
saves; seen with the harness's bundled retail-layout save, 2026-10-05). The fields also shift: retail's shown-form
bytes 9-10 and its first language bytes land in W2U's form and extension lists, so language entries a retail player
has (species 1-493 caught in other languages) would read as seen / caught flags of species 673+.

**Migrating a retail save** (none is built in yet): for both halves, keep 0x000-0x2FB; copy the first 9 bytes of
each of the four retail form lists into W2U's (bits beyond 72 dropped, after checking the form list fits); zero the
0x1B0-byte extension area (retail's language flags are not kept); move `spindaPersonality` to 0x4D0; then write the
footer at 0x4D4 (counter, CRC over 0x4D4 bytes), the block's entry in the checksum table and the table's CRC.
`w2u-local/checks/make_checks.py` (local test tooling) does exactly this for its test saves (`to_w2u_pokedex_layout`;
checked on the harness's retail-layout save: both halves validate, the lists are kept, a second run changes nothing).

## 2. Battle log: blocks 29, 30, 31

`src/battle_log/` stores W2U's battle log in the save blocks retail uses for Wi-Fi battle history, friends and
negotiation; layout, versions and recovery in [battle-log-save-format.md](battle-log-save-format.md). The retail code
that reads or writes those structures (including trade rollback by memcpy) gets separate scratch copies on the
application heap instead (`w2u_battle_log_save_guard.cpp`, 10,320 bytes), so it can never overwrite the log. A
retail save's Wi-Fi data in those blocks is not shown by W2U; the log's header (magic, version) tells a W2U log apart
from it.

## 3. Pokemon data (party and boxes)

The structures are retail's (136-byte box data, 220-byte party data, the same encryption and block shuffling); W2U
stores larger values in them:

| Value | Where | Retail range | W2U |
|---|---|---|---|
| Species | box data +0x08, u16 | 1-649 | 1-1023 |
| Form | box data +0x40, bits 3-7 | as retail | as retail (5 bits) |
| Moves | box data +0x28..+0x2E, u16 | 1-559 | up to 920 |
| Held item | box data +0x0A, u16 | up to 638 | up to 610 (`include/Items.h`) |
| Ability | box data +0x15, u8 | 1-164 | up to 1023: +0x15 holds the low 8 bits, byte +0x42 bits 6-7 hold bits 8-9 (retail uses only bits 0-1 there: hidden ability, N's Pokemon) |

The ability packing is in `src/pokeweb_gameplay/w2u_ability_storage.cpp`; it is decoded at `PML_PkmGetParamCore`
and encoded at `PML_PkmSetParamCore`, so callers see real IDs. Saves made before it have bits 6-7 clear, which reads
as the plain byte. Retail Pokemon load unchanged; a W2U Pokemon with a species, move or ability past retail's range
traded or moved into a retail game is invalid there.

## 4. Unchanged

All other blocks keep retail's size and layout: no W2U code reads or writes a save block directly except the battle
log (`SaveControl_DataPtrGet`, checked 2026-10-15), and no other block size is changed. Event flags: W2U changes one
field script (`data/scripting/.../container_1243.pkr`, the Strength prompt); it uses the same flag as retail's
(`EVENT_FLAG_0x0964`, 2404; the decomp's `data/field_scripts/global_10000.s`) and only temporary work values
(0x8010, 0x8021-0x8024), so W2U saves no flags or work values of its own.

## For a build on another code base

Reproduce or migrate: the Pokédex block (size 0x4D4, the extension lists, 9-byte form lists, the spinda value at
0x4D0), the battle log blocks 29-31 with the Wi-Fi structures redirected away from them, and the Pokemon value
ranges with the ability packing. A save made by the injection build should load unchanged; a build that wants retail
layout back needs the reverse of the migration above (and has nowhere to keep species 673+ unless it grows the
block).

Tools (local, `w2u-local/checks/`): `savecheck.py SAVE [OTHER]` validates both halves' blocks and CRCs and diffs two
saves by block.
