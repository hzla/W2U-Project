# MegaB2W2 integration branch

Branch `megab2w2-integration`. Work in progress: bringing selected MegaB2W2 features into White2Upgrade.
**Not for `main`**: nothing here is merged until the maintainer decides. MegaB2W2 stays a separate project.

## Provisional decisions

These follow the integration plan's recommendations and still need the maintainer's review. Each phase records
what it actually did below.

| # | Topic | Provisional choice |
|---|---|---|
| D1 | Item IDs | W2U's IDs stay. Ported items use W2U's existing constants; only items W2U lacks (Booster Energy) get new IDs from W2U's free ranges |
| D2 | Animated sprites | PWAN stays the runtime. The MegaB2W2 `w2anim` tool gains a PWAN writer; the PWAN runtime itself is unchanged in this branch |
| D3 | Weather / terrain indicators | One indicator system on the command screen, based on MegaB2W2's panels (animated, terrain stacked under weather, primal-weather panels), drawn with W2U's own-unit CLACT approach |
| D4 | Terrain visuals | W2U's floor textures and ambient particles stay. MegaB2W2's highlight glow is not ported |
| D5 | Abilities implemented by both | W2U's code stays unless a test shows a Showdown (Gen 9 / National Dex) difference; then the W2U handler is fixed |
| D6 | Action order | W2U's action-order loop stays; MegaB2W2 order rules move into it |
| D7 | Memory | 164 KiB PMC heap unchanged; ported mechanics go into on-demand module groups, not the resident core |
| D8 | Testing | Pokeweb-Serverless's battle harness (`runtime/battle-harness`, direct boot into a trainer battle) run in headless melonDS (PlatinumMaster/melonDS-headless, `headless` branch); MegaB2W2's scenario suite is not ported |
| D9 | Mega | W2U's Mega implementation stays; only MegaB2W2 extras are added |
| D10 | Species ability storage | Pokeweb's packing (`personalAbilityPacking.ts`): ability byte = low 8 bits, bits 14-15 of the matching wild-item word = bits 8-9; max ID 1023. Pokeweb shows and edits the same values |

Licence and asset terms for contributed code and art are still open. Assets with restricted permissions
(PokeRogue art: private use only) are not added on this branch.

## Phases

| Phase | Content | Status |
|---|---|---|
| 0 | This record; build portability | done |
| 1 | Baseline build on this branch + battle-harness smoke test | done |
| 2a | Primal weathers (Primordial Sea, Desolate Land, Delta Stream) | done (White 2) |
| 2b | Merged weather / terrain indicator | done (White 2) |
| 3 | Abilities by group (Gen 8 / 9 and custom), terrain extras, Booster Energy | in progress (wave A tested + storage done) |
| 4 | `w2anim` PWAN writer (tool-side; lives in the w2anim repository) | planned |
| 5 | Mega extras (held-START toggle, Mega sound cues, HP-gauge Mega icon) | planned |
| 6 | Fixes for differences found in shared abilities | planned |
| 7 | Documentation | planned |

## Build notes

- `tools/CTRMap/meson.build` references the jar with `files()` instead of `find_program()`: the jar is only passed
  to `java -cp`, and Windows hosts cannot run a `.jar` as a program. Behaviour on other hosts is unchanged.
- Windows hosts also need: a POSIX `sh` (Git for Windows), a `python3` executable on `PATH` with
  `requirements.txt` installed, and `-Dblack2_base_rom=` pointing at a file when no clean Black 2 ROM is available
  (Black 2 targets are then not built).

## Phase 1: baseline

- The unmodified branch builds on Windows (see Build notes) and passes the ROM layout check.
- Battle harness smoke test (trainer 1, singles) in headless melonDS: `verified: true`, direct-placement opening,
  command menu reached, sub-screen UI visible.
- Pre-existing, not caused by this branch: the PWAN back sprite of Charizard renders corrupted / offset on the
  command screen (also visible in headless screenshots of the unmodified build).

## Phase 2a: primal weathers

Code: `include/w2u_strong_weather.h`, `src/pokeweb_gameplay/w2u_strong_weather.cpp`, battle module
`abilities/strong_weather` (registry id 22). The resident part (state, accessors, hooks) is White 2 only; Black 2
gets one-entry no-op handler tables so its static resolver still links (abilities do nothing there).

- Resident hooks (none shared with existing W2U hooks): ov167 `0x21A767C` (weather change check, whole),
  `0x21A7FBA` (turn-end weather call), `0x21ABA24` (AI damage estimate), `0x21B78AC` / `0x21B792C` (weather
  start / end display commands, whole).
- Reset with the other battle state in `ServerFlow_SetupBeforeFirstTurn` and `W2U_BattleState_OnBattleExit`.
- Messages: std bank 19 entries 201-212. Effects: `tools/graphics/build_strong_weather_effects.py` writes
  SPAs 1031-1033 and a/0/6/5 scripts 960-964 (effect IDs 1075-1079); a/0/6/6 keeps its 115 retail members.
  The generated README tables of `move_animations` / `move_spas` were not regenerated (their generator lives in
  Pokeweb-Serverless).
- `tools/verify_w2u_battle_linkage.py` also accepts non-link numeric-overlay hooks (`THUMB_BRANCH_167_0x...`),
  which, like the link form, have no named ESDB owner.
- Registry guard raised to 62 managed abilities (README / module doc counts updated).

Headless checks (harness, singles, one turn):

| Scenario | Messages seen |
|---|---|
| Kyogre with Primordial Sea uses Ember; foe uses Sunny Day | heavy rain start, Fire fizzle, Sunny Day blocked |
| Groudon with Desolate Land uses Water Gun; foe uses Rain Dance | harsh sun start, Water evaporates, Rain Dance blocked |
| Tornadus with Delta Stream; foe uses Ice Beam | strong winds start, "weakened the attack" |

Notes for review:
- A base-form Rayquaza given Delta Stream through the harness has it reset by the existing leaked-Mega-ability
  repair (expected for normal play); Mega Rayquaza is the natural holder and was not tested here.
- A blocked weather move also shows the retail "But it failed!" after the block text (same as in MegaB2W2).
- Ending on switch-out / faint and Air Lock / Cloud Nine negation: tested 2026-10-05 (below, "Field checks").
- Host tests: four failures on Windows only (python3 alias lookup in two transform tests, path separators in two
  privacy-report tests); unrelated to this branch.

## Field checks: strong weathers, negation, terrain moves (2026-10-05)

Spec `w2u-local/harness/wave_field.yml`, 18 scenarios, all pass:

- Strong weathers (MegaB2W2's scenarios): heavy rain (Fire fizzles, Thunder sure-hit, Rain Dance "no relief",
  Weather Ball Water x2), extremely harsh sun (Water evaporates x3, Drizzle / Sunny Day "not lessened", one-turn
  SolarBeam, Weather Ball Fire), the holder switching out ("lifted") and, new, fainting (heavy rain and harsh sun
  both end; the next foe's Fire / Water move hits), Defog leaves it, Fire status moves still work.
- Negation: Air Lock with heavy rain (Flamethrower hits, Rain Dance still blocked); Cloud Nine with Desolate Land
  (Water Gun hits); and the resident `ServerEvent_GetWeather` (replaced in wave C for Mega Sol): Cloud Nine cancels
  Sunny Day's Fire boost (x1.000; control without Cloud Nine x1.500); Cloud Nine leaves Grassy Terrain's healing.
- Expanding Force and Misty Explosion, which W2U lacked: x1.5 for a grounded user on Psychic / Misty Terrain in W2U's
  terrain power handler (`HandlerTerrainPower`); Misty Explosion aliases Explosion's handlers (the user faints).
  Measured: Expanding Force x1.906 (x1.5 and the terrain's Psychic x1.3, integer rounding at 53 damage), Misty
  Explosion x1.490. Expanding Force's Gen 9 spread to every foe is not modelled.
- Damp: vanilla Damp's move check compares the move with Explosion / Self-Destruct only, so Misty Explosion and
  W2U's Mind Blown went off next to Damp. W2U's Damp (`megab2w2/abilities/Damp.cpp`, module `abilities/mb_defense`,
  White 2) is vanilla's table with that check replaced by Showdown's list (Self-Destruct, Explosion, Mind Blown,
  Misty Explosion); vanilla's message and other handlers are reused (four ESDB names). Checked: all three stopped
  ("X cannot use Y!"), Explosion still stopped, Mind Blown hits without Damp. Primary ability count 134 -> 135.

## Fix: terrain moves hung in battles started without the field

Every terrain move stopped after "X used ... Terrain!" in harness battles (reproduced on unmodified `main`,
stripped and unstripped). The battle client started the move-animation command, W2U's
`W2U_TerrainTexture_OnMoveAnimationStart` prepared the ambient particles, and
`GFL_HeapGetHighestAllocatableSize(GetFieldLowHeapID())` never returned: the heap ID has no heap in that boot,
the native lookup (ARM9 `0x2039AAC`) gives a null handle, and `HeapBase_GetHighestAllocatableSize` walks a free
list from address 0. `GetFieldLowHeapID()` now returns 0 for a missing heap (callers already skip on 0), so the
texture swap runs and only the ambient particles are skipped there. White 2 only (`W2U_ADDR_GFL_HEAP_HANDLE_FOR_ID`);
the Black 2 address is not mapped. Found by tracing the client's server-command handlers and the interrupted PC in
headless melonDS.

## Phase 2b: command-screen indicators

`tools/graphics/build_command_indicators.py` (replaces the static icons of `build_terrain_indicator.py`, which is
kept but marked superseded) writes battgra 420-423 and art member 941:

- strong-weather icons (Delta Stream, Primordial Sea, Desolate Land), animated, palette 5 (new colours in its unused
  slots 9-11 / 13-15); sequences 0x13 (winds, weather value 5), 21, 22;
- an animated TERRAIN panel per terrain (label in the native WEATHER font + box), palette 15, sequence 23;
- one 3-frame weather slot and one 2-frame terrain slot in the sheet (80 tiles after the 314 retail ones, 16 more
  than the previous terrain icons); the current icon's frames are copied from member 941 when the panel appears.

`w2u_terrain_indicator.cpp` keeps W2U's own CLACT unit and lifetime hooks, and now: picks the weather value / icon
for the native WEATHER panel (strong weathers), redirects its icon sequence (ov168 `0x21EE7FE`, White 2), and places
the TERRAIN panel under the WEATHER panel (or in its place without weather), sliding in with it from the input's
task list (White 2; Black 2 places it without the slide and shows no strong-weather icons).

Headless checks: heavy rain + Electric, strong winds + Grassy, harsh sun + Psychic, Misty alone (singles); Double
Battle with heavy rain + Electric Terrain: both command screens show both indicators and both party icons.

## W2U fixes found during integration

| Fix | Symptom |
|---|---|
| `GetFieldLowHeapID()` returns 0 for a missing heap | every terrain move hung in battles started without the field |
| `HANDLER_ABILITY_POPUP_FLAG` = 0x800000 (native bit) | replaced Rough Skin / Aftermath / Mummy / Pickpocket / Poison Touch, contact-status abilities, Cheek Pouch, Innards Out, form abilities and the Mega form change showed no ability popup |
| compile targets depend on the shared headers | a header edit left stale DLLs (custom targets without depfiles) |
| `package_rpm_checked.py` rejects `__gnu_thumb1_case_*` | a jump-table switch packaged without error and hung the boot |
| `CTRMapV-dirty.jar` via `files()` | Windows hosts could not configure |
| mkdata targets depend on the serializer scripts (`mkdata_deps` in `tools/mkdata/meson.build`; encounters, items, pml, pml/moves, trainers) | editing an mkdata script never rebuilt the data (`data/text` not checked yet) |
| Move flags synced with Showdown (wind, slicing, bite, pulse, bullet, dance, powder): 53 moves gain flags, 41 lose wrong ones | `FLAG_POWDER` is bit 14, which vanilla data uses for "not in Sky Battles": 39 moves (Earthquake, Surf, Body Slam, Seismic Toss, Substitute, Spikes ...) counted as powder moves, so Overcoat and Safety Goggles blocked them. Old moves lacked the newer flags (Gust / Hurricane not wind, Slash / Leaf Blade not slicing, Fire / Ice / Thunder Fang not biting, Aura Sphere not pulse, Shadow Ball / Sludge Bomb not ball moves), so W2U's Strong Jaw / Mega Launcher / Bulletproof and the ported Sharpness / Wind Rider / Wind Power missed them. Bullet Punch was a ball move and Bug Bite a biting move (neither is in Showdown) |
| `IsW2UIgnorableAbility` lists the breakable Gen 8 / 9 abilities (Showdown `breakable`) and Aura Guard | Mold Breaker / Teravolt / Turboblaze could not get past any ported ability (Good as Gold blocked a Mold Breaker Thunder Wave) |

## Fix: Gen 1 sprites (Mega preview leftovers)

Reported by hzla: mostly Gen 1 sprites are broken. Cause: `tools/pwan/apply_mega_preview_low_ids.py`, a temporary
preview that shows every Mega form under species 1, 2, 3 ... (96 Megas -> species 1-96), had left its state in the
data:

- `assets/pokeweb_pwan/config.bin`: 89 rows (species < 650, form 0) pointing at Mega PWAN assets, so Bulbasaur was
  drawn with Mega Gengar's animation data, Pikachu with another Mega's (broken back sprites, missing fronts);
- `data/graphics/pokegra/icons`: the party icons of species 1-96 were Mega icons, and
  `data/pml/pokeicon_palette_map.bin` gave them the Megas' icon palettes;
- `src/pokedex_expansion/w2u_pokegra.cpp`: `MEGA_PREVIEW_SPECIES_START/END` = 1-96 marked them as expanded graphics.

Fixed (`69c7eab82`): the 89 rows removed (each matches the preview report's species and asset; the 118 real form rows
below 650 stay), icons and icon palettes of species 1-96 restored from before the preview (`5351a2970^`), the preview
range set to 1-0. The battle sprite files themselves (a/0/0/4 below file 13000) are vanilla's and were never touched.

Checked in battle: every species 1-649, front and back, side by side with vanilla White 2 - all match (survey: one
trainer battle per 6 species; the foes use Memento so each faints in turn, the player switches through the same
6). Species 650-1023 (PWAN sprites, no vanilla counterpart): every front and back drawn whole and with its own
colours, Goodra (706) included. Not covered: 722-724, which Pokeweb's battle harness refuses to build (it treats
personal records 722-724 as Deoxys' form records); the harness, not W2U, is the limit there. Tools (local,
`w2u-local/harness`): `sprite_survey.py` (battles), `survey_grid.py` (24 species per sheet, vanilla | W2U).

## Phase 3: abilities

### Wave A: 51 hook-free abilities

MegaB2W2's logic files are compiled as they are against their own engine headers
(`src/pokeweb_gameplay/megab2w2/`: `battle.h`, `battle_events.h`, `ability_api.h`, `mb_ids.h`); the two sides meet
only at the handler tables (`MB_<Logic>Handlers`, same `{event, handler}` layout), declared for the generated
module API in `megab2w2/mb_ability_tables.h`. W2U's `W2U_MoveMakesContact` and move-record flags replace MegaB2W2's
Long Reach wrapper and flag table. Modules (White 2 only, registry ids 23-26): `abilities/mb_power`,
`mb_defense`, `mb_reactive`, `mb_entry`.

Abilities: Neuroforce, Intrepid Sword, Dauntless Shield, Libero, Cotton Down, Mirror Armor, Steam Engine, Punk Rock,
Ice Scales, Power Spot, Steely Spirit, Screen Cleaner, Perish Body, Wandering Spirit, Lingering Aroma, Pastel Veil,
Curious Medicine, Transistor, Dragon's Maw, Rocky Payload, Sharpness, Fire Mane, Grim Neigh, As One (both), Thermal
Exchange, Anger Shell, Purifying Salt, Well-Baked Body, Wind Rider, Guard Dog, Wind Power, Electromorphosis, Good as
Gold, the four Ruin abilities, Supreme Overlord, Costar, Toxic Debris, Armor Tail, Earth Eater, Mind's Eye,
Supersweet Syrup, Hospitality, Toxic Chain, Tera Shell, Spicy Spray, Eelevate, Aura Guard.

Supporting changes: registry `extra_sources` (and the source check reads them), capacity / loader records 32,
113 managed abilities, the ability enum completed (official IDs to 306, MegaB2W2 custom 307-314), 48 ESDB names,
messages in bank 18 (1352-1396) and bank 19 (213-214).

#### Wave A results (headless, 2026-10-04)

All 51 abilities are checked by 66 battle scenarios (converted from MegaB2W2's, same names) plus 5 move-flag
regression scenarios; all 71 pass. Messages and ability pop-ups come from the battle-message transcript, damage from
the real damage calculation (with the random roll pinned at 100% and critical hits off where a check compares two
hits). Fixed on the way:

- Mold Breaker: `IsW2UIgnorableAbility` now lists Mirror Armor, Punk Rock, Ice Scales, Pastel Veil, Thermal Exchange,
  Purifying Salt, Well-Baked Body, Wind Rider, Guard Dog, Good as Gold, Armor Tail, Earth Eater, Mind's Eye, Tera
  Shell (Showdown's `breakable` flag) and Aura Guard (MegaB2W2 custom). Thermal Exchange is breakable in Showdown but
  was not marked in MegaB2W2's registry; it is listed here.
- Guard Dog: it recognises Intimidate through a tracked copy of Intimidate's handler (records its user while it
  runs). That half was not ported: Intimidate (ability 22, `ABIL_INTIMIDATE` added to `w2u_abilities.h`) now routes
  to `abilities/mb_defense` with `MB_IntimidateTrackedHandlers` (same events and handler as vanilla). Primary
  ability count 113 -> 114 (`tools/generate_w2u_battle_registry.py`).
- Sharpness, Wind Rider, Wind Power: the move-flag fix above (Slash, Gust).
- Mega Evolution is announced in W2U's words ("... is reacting to a Mega Ring!", "... is Mega Evolving!"); the
  scenarios check those.

Measured: Sharpness x1.49 (Slash / Headbutt), Neuroforce x3.07 (super effective / neutral), Punk Rock x1.45 and
x2.0 taken, Purifying Salt x1.93 taken from Ghost moves, the four Ruin abilities x0.75 / x1.33, Transistor x1.29,
Dragon's Maw / Rocky Payload / Fire Mane x1.5, Ice Scales / Aura Guard x0.5, Supreme Overlord x1.1 with one fainted,
Power Spot / Steely Spirit gone once the holder left (x0.77 / x0.67), W2U's Strong Jaw x1.48 on Fire Fang.

The scenario runner is local tooling (`w2u-local/harness/wave.py`, spec `wave_a.yml`; D8: MegaB2W2's suite is not
ported into this repository). It drives Pokeweb battle-harness ROMs in headless melonDS and reads everything from the
emulator (no ROM instrumentation): one ROM per foe side, the player team in a per-scenario save, battle animations
off through the save's Battle Scene option (byte 0x19400 bit 7, CRC16 block checksum), 10 parallel workers. A full
run takes 9.5 min (17.7 before these speed-ups).

### Wave B: terrain-dependent abilities and Booster Energy

Seven abilities in one module, `abilities/mb_terrain` (registry id 27, White 2 only): Protosynthesis, Quark Drive
(`Protosynthesis.cpp`), Orichalcum Pulse, Hadron Engine, Mimicry (`TerrainAbilities.cpp`), Sand Spit, Seed Sower
(`SandSpit.cpp`). W2U already has the Surges, Grass Pelt and Surge Surfer, so MegaB2W2's versions of those were not
ported. Primary ability count 114 -> 121.

- Terrain is W2U's: `megab2w2/terrain.h` maps MegaB2W2's `terrain::` calls onto `W2U_MoveState_GetTerrain` and
  `W2U_MoveState_SetTerrainFromAbility` (the Surges' path: popup, the terrain move's animation, the start message,
  `EVENT_AFTER_TERRAIN_CHANGE`). New `W2U_MoveState_SetTerrainFromAbilityNamed` (`w2u_moves.cpp`): the same with the
  setter as the message argument, for Hadron Engine's "X turned the ground into Electric Terrain, ...".
- The module depends on `moves/terrain`, like `abilities/terrain`: in the dynamic battle core the terrain field
  handlers come from that module, and without it loaded setting terrain fails (Seed Sower and Hadron Engine did
  nothing in a battle without a terrain move).
- Booster Energy: item 426 (was `unknown_17`; `data/items/booster_energy.toml`, `ITEM_BOOSTER_ENERGY` in `Items.h`
  and `mb_ids.h`), name and description in banks 64 / 63, icon `assets/item_icons/icons/booster_energy.png` + palette
  (from Showdown's item sprite sheet; credit needed if kept). Used on entry when neither sun nor Electric Terrain is
  up.
- Messages: bank 18, 1397-1441 (15 sets: Protosynthesis / Quark Drive activation, the five stats, the end messages,
  Orichalcum Pulse, Hadron Engine).

#### Wave B results (headless, 2026-10-05)

10 scenarios (`w2u-local/harness/wave_b.yml`), all pass:

| Scenario | Checked |
|---|---|
| PROTOSYNTHESIS_BOOSTER | "used its Booster Energy to activate Protosynthesis", Attack x1.291 (Strength, holder vs plain Snorlax) |
| PROTOSYNTHESIS_SUN | the foe's Sunny Day activates it; Mantine's Sp. Def is boosted |
| PROTOSYNTHESIS_STAGES | stat stages count: Gardevoir after Swords Dance boosts Attack, not Sp. Atk |
| QUARK_DRIVE / QUARK_DRIVE_BOOSTER | its own Electric Terrain / Booster Energy activate it |
| SAND_SPIT, SEED_SOWER | hit by Tackle: sandstorm / Grassy Terrain, once |
| HADRON_ENGINE | Electric Terrain on entry with its own message; Thunderbolt x0.758 plain / holder |
| ORICHALCUM_PULSE | sun on entry; Strength x0.748 plain / holder |
| MIMICRY | Electric-type in Electric Terrain: the same Earthquake is neutral, then super effective |

### Wave C: abilities that need engine hooks

Thirteen abilities. Dragonize is W2U's own -ate conversion (`GetNormalMoveConversionType`: Dragon; module
`abilities/type`). The other twelve are in module `abilities/mb_hooked` (registry id 28, White 2 only):

| Ability | Module side (handlers) | Resident side |
|---|---|---|
| Gorilla Tactics | Attack x1.5; adds the Choice lock (condition 0x1B) after its first move; cures it when the ability goes | W2U's `IsUnselectableMove`: a holder locked without a usable Choice item gets Encore's "X can use only Y!" |
| Propeller Tail, Stalwart | (empty table) | Lightning Rod / Storm Drain (ov167 0x21C0D82) and Follow Me / Rage Powder (0x21C64C4) ask `Battle_IsRedirectBlocked`: wrapped; W2U's Spotlight handler checks the abilities |
| Unseen Fist, Piercing Drill | `EVENT_CHECK_PROTECT_BREAK`: contact moves answer 2 (go through, the protection stays); Piercing Drill's hit through protection x0.25 | `W2U_CheckProtectBreak` now also passes the move (`VAR_MOVE_ID`) |
| Quick Draw, Mycelium Might | event 0x0F (special priority, Quick Claw's): first / last in the bracket | the pending move, noted at the two `ServerEvent_GetMovePriority` calls of the action-order sorts (0x21A0266, 0x219FBF8) |
| Poison Puppeteer | event 0x68: a Pokemon it poisons is also confused | - |
| Mega Sol | its move start / end | `ServerEvent_GetWeather` replaced whole (as vanilla: Air Lock / Cloud Nine event, then the field weather), sun during the holder's move |
| Ripen, Cud Chew, Opportunist | popup; the second bite at the end of the next turn; recording foes' raises and copying them | the handler-effect dispatcher's calls (UseHeldItem 0x21AC59E, RecoverHP 0x21AC5AA, Damage 0x21AC5C0, StatChange 0x21AC604, ForceUseItem 0x21AC6D6): Berry effects doubled, Berries eaten noted, copies run with a flag |

- Resident code: `src/pokeweb_gameplay/megab2w2/mb_resident.cpp` (White2Upgrade.dll; API `mb_resident.h`, imported by
  the module as `W2U_MB_*`; state cleared in `W2U_BattleState_OnBattleExit`). Every hooked call site was checked in
  W2U's built overlay 167: the same BL and target as vanilla White 2, and none is hooked by W2U. ESDB: seven names
  added (`Battle_IsRedirectBlocked`, `BattleField_GetWeather`, `BattleHandler_UseHeldItem` / `RecoverHP` / `Damage`
  / `StatChange` / `ForceUseItem`).
- Black 2 is unchanged: the module and the resident file are White 2 only; the `IsUnselectableMove` branch is
  `#if !defined(W2U_TARGET_B2)`; the Spotlight check, Dragonize and the protect-break move argument are
  address-free and shared.
- Message: Quick Draw, bank 18 1442-1444. Primary ability count 121 -> 134.
- Fixed on the way (also present in MegaB2W2): Opportunist counted its own copy after pushing it, but the effect can
  run at once, so a foe's Opportunist copied the copy back (both sides +4). The copy is counted before the push.

#### Wave C results (headless, 2026-10-05)

20 scenarios (`w2u-local/harness/wave_c.yml`), all pass, among them: Gorilla Tactics x1.494 and the menu refusing
another move ("Machamp can use only Strength!"); Unseen Fist through Protect, Hyper Voice still blocked; Piercing
Drill x0.253 against Unseen Fist in the same turn; Quick Draw (roll pinned) moving the slower Shuckle first twice,
never with Splash; Propeller Tail past Lightningrod and Stalwart past Follow Me, each with a control where the
redirection happens; Ripen x1.324 (Liechi +2 "sharply raised" vs +1); Opportunist +2 and not copied back between two
holders; Cud Chew eating its Sitrus Berry again at the end of turn 2; Mycelium Might Toxic last and through
Immunity; Poison Puppeteer confusing; Mega Sol SolarBeam on turn 1 and Flamethrower x1.487; Dragonize Tackle hitting
Gengar. Waves A and B were re-run on the same build (the resident hooks run in every battle).

Runner changes: the transcript also decodes set messages loaded from 0x21D5523 (item-and-stat messages); the
party-screen check no longer depends on the lead's HP bar colour; `last_turn_refused: true` for a last move the
menu is expected to refuse; doubles targets: f1 is the foe's second Pokemon, f2 its first.

### Abilities above 255

W2U stored abilities in one byte (species data and each Pokemon), so no ability above 255 could be used; Gen 9
species had placeholders (e.g. Gholdengo: Overgrow). Now (White 2):

- species data (D10): ability byte = low 8 bits, bits 14-15 of the matching wild-item word (personal +0x0C / +0x0E /
  +0x10; item IDs use bits 0-13) = bits 8-9, Pokeweb's packing; `tools/mkdata` packs abilities up to 1023 and
  errors above it (or on an item above 0x3FFF); `PML_PersonalGetParam` masks the wild-item params to 0x3FFF. (The
  first version used EV Yield bit 13 + slot, max 511; Pokeweb could not read it);
- Pokemon data: byte 0x42 bits 6-7 = bits 8-9 (vanilla uses bit 0 hidden ability, bit 1 N's Pokemon; byte 0x43 and
  0x5E / 0x64-0x67 are taken by the battle log / PKHeX's probe); old saves read as before;
- `w2u_ability_storage.cpp` decodes at `PML_PersonalGetParam` (re-implemented 1:1) and the four Pokemon parameter
  get / set call sites; `w2u_ability_storage_ui.cpp` (UI companion) handles the PC box panel's display byte.

Data: the Gen 8 / 9 species have their real abilities (68 species, `e2f658e7a`). Checked: the built personal NARC
decodes to the toml values for all 566 numbered species (70 with abilities above 255).

Pokeweb battle harness: it capped `abilityId` at 255. A local patch (Pokeweb-Serverless is hzla's repository; to be
offered upstream) raises it to `PERSONAL_ABILITY_MAX_ID` (1023) and writes / reads byte 0x42 bits 6-7 in
`battleHarness.ts` and `testBattleTeam.ts`; trainer overrides already go through Pokeweb's personal packer, which
W2U now reads. Headless battle (player Snorlax Sword of Ruin 285 vs foe Snorlax Beads of Ruin 287): both pop-ups,
"The foe's Snorlax weakened the Sp. Def of all surrounding Pokemon!" (set 1382, foe variant) and "Snorlax weakened
the Defense of all surrounding Pokemon!" (set 1376, player variant).
