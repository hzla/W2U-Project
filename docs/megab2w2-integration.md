# MegaB2W2 integration branch

Branch `megab2w2-integration`. Work in progress: bringing selected MegaB2W2 features into White2Upgrade.
**Not for `main`**: nothing here is merged until the maintainer decides. MegaB2W2 stays a separate project.

## Provisional decisions

These follow the integration plan's recommendations and still need the maintainer's review. Each phase records
what it actually did below.

| # | Topic | Provisional choice |
|---|---|---|
| D1 | Item IDs | W2U's IDs stay. Ported items use W2U's existing constants; only items W2U lacks (Booster Energy) get new IDs from W2U's free ranges |
| D2 | Animated sprites | **Changed 2026-10-05 (agreed with hzla):** w2anim's streaming runtime replaces the PWAN runtimes; PWAN assets are converted. The PWAN DLLs held 46.5 KB of the PMC heap in battle (see "Fix: PMC heap out of memory"). Original choice: PWAN stays, w2anim gains a PWAN writer |
| D3 | Weather / terrain indicators | One indicator system on the command screen, based on MegaB2W2's panels (animated, terrain stacked under weather, primal-weather panels), drawn with W2U's own-unit CLACT approach |
| D4 | Terrain visuals | W2U's floor textures and ambient particles stay. MegaB2W2's highlight glow is not ported |
| D5 | Abilities implemented by both | W2U's code stays unless a test shows a Showdown (Gen 9 / National Dex) difference; then the W2U handler is fixed |
| D6 | Action order | W2U's action-order loop stays; MegaB2W2 order rules move into it |
| D7 | Memory | **Changed 2026-10-05:** PMC heap 200 KiB (MegaB2W2's value, measured room below); ported mechanics still go into on-demand module groups where they can |
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
| 3 | Abilities by group (Gen 8 / 9 and custom), terrain extras, Booster Energy | done (waves A-C, field checks) |
| 4 | w2anim runtime replaces PWAN (D2 changed); assets converted | in progress |
| 5 | Mega extras (held-START toggle, Mega cry, HP-gauge Mega icon, Mega glyph) | done (White 2) |
| 6 | Fixes for differences found in shared abilities | done |
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

## Open W2U issues (not fixed on this branch)

| Issue | Found | Details |
|---|---|---|
| Raichu forms 1 / 2 (Mega Raichu X / Y) and Slowbro form 1 (Mega Slowbro) have no battle set | 2026-10-05, Phase 4 | The Gen 8 / 9 import (`assets/pokeweb_pwan/gen8_gen9_essentials_import_report.json`, `relocatedExistingForms`) moved these forms to sprite forms 373 / 374 / 393, i.e. pokegra blocks 1097 / 1098 / 1117, and moved their PWAN assets to the same indices, but the battle members were never staged there: the built a/0/0/4 has no files 21940-21959, 21960-21979, 22340-22359. Their old sets are still at blocks 1038 / 1039 / 737 (the "staticAsset" of `mega_preview_low_ids_report.json`). The game therefore loads missing files for these forms, with PWAN as with w2anim, and the w2anim build skips their streams (`build_w2anim_streams.py` lists them). Fix: stage the three sets at the new blocks (copy or `restage_pwan_carrier_sets.py`), then the converter picks them up |

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

## Phase 5: Mega extras (2026-10-05)

White 2 resident code `src/pokeweb_gameplay/megab2w2/mb_mega_extras.cpp` (API in `mb_resident.h`), called from W2U's
Mega flow in `w2u_mega.cpp`; W2U's Mega animation is kept as it is, apart from its symbol.

- START toggle: edge detection on the held keys (`GCTX_HIDGetHeldKeys`) instead of the one-update pressed trigger,
  which the move-select wait (polled about every other frame) could miss - MegaB2W2's doubles fix. A START held
  when the move screen opens does not toggle. (`w2u_mega.cpp`, both games.)
- The Mega's cry with a reverb tail (MegaB2W2's MegaSound): W2U's animation plays no cry. PokeVoice loads it 32
  frames after W2U's sprite refresh, a Freeverb-style reverb (bit-exact with MegaB2W2's `cry_reverb.py`) writes it
  into a buffer 1.9 s longer, processed a chunk per frame, and it plays 62 frames after the refresh (or at the
  animation's end). MegaB2W2's four remixed sound effects were made for its own animation and are not used, as in
  MegaB2W2 with W2U's animation. Checked: `PokeVoice_Load(448, 1, ...)` then `StartPlayback` with the 33,848-byte
  reverb buffer (scenario MEGA_PLAYER_SINGLE traces both).
- The Mega icon on the HP gauges (MegaB2W2's MegaGaugeIcon, DBK's `icon_mega.png`, Lucidious89): 11x11 in a 16x16
  OBJ, a prefix to the name on every gauge, for a Pokemon in a Mega form that is not transformed, hidden while its
  animation plays. Hooks: the gauge system's create / delete call sites (ov168 0x21DF096 / 0x21DF202),
  `BtlvCore_SetupGauge` (re-implemented 1:1 to remember the BattleMon), the game's OAM and OBJ-palette transfers
  (ARM9 0x20756DC / 0x207561A: the icon goes into unused OAM entries, OBJ palette 12, tiles at VRAM 0x7F80).
- The Mega glyph: W2U's animation showed its symbol as SPA 769 at a fixed spot; it is replaced by MegaB2W2's glyph
  (DBK `Mega/icon.png`, 13x25 + outline in a 16x32 OBJ, 4 dithered fade stages) above the Mega's own sprite. The
  script `5_00000622.bin` lost only its `LoadSPA 769` / `DoSPAAnimation2 769` (the other 49 commands are byte-
  identical; `docs/moveanimation-spanotes.md` updated). The glyph starts 59 frames after W2U's sprite refresh
  (where SPA 769 appeared), fades in, stays 1 s, fades out (earlier once the HP gauges are back); W2U's Mega wait
  holds until it is gone. Placement: the sprite's MCSS ground point projected every frame (camera x projection, as
  MCSS_Draw; it follows the screen shake), the scale cached while the player picks a move and corrected by the
  depth ratio (W2U's Mega sequence and its PWAN sprites leave the sprite's own scale fields unusable then), and the
  Mega's PWAN head: top row and the centre of its topmost 16 rows (`mb_mega_glyph_heights.inc`, generated by
  `tools/pwan/gen_mega_glyph_heights.py`; the MCSS ground point is canvas row 88, measured). Bottom 10 px above the
  sprite's top. The 14 Megas without a PWAN asset (native sprites) use a default top row.
- Fixed on the way: Mega Lucario (asset 1053) and Mega Garchomp (1051) were drawn garbled - their native battle
  members were a static sprite's set (own cell layout, smaller NCGRs) instead of the PWAN carrier set every other
  PWAN asset has. `tools/pwan/restage_pwan_carrier_sets.py` rebuilds such sets (carrier template, the PWAN's first
  frame in the NCGRs, palettes) without pokeweb-source; `--check` lists any left (none now).
- Tests (`w2u-local/harness/wave_mega.yml`): the player's Mega by START in singles and doubles (once a battle), none
  without START, the foe's AI Mega in singles and doubles; glyph / icon / cry checked on recordings and traces.
  Harness: `M1*` turns (START on the move screen), `trace:` / `probe_mcss:` debugging keys.
- The heap stall seen while finishing this phase was the PMC heap (section above), not Phase 5's hooks; the hooks
  disabled while bisecting it are enabled again.

## Phase 4: w2anim runtime replaces PWAN (2026-10-05)

D2 changed (agreed with hzla): White 2 animates its sprites with w2anim's streaming runtime instead of the four PWAN
runtimes. Reason: heap. In battle the PWAN DLLs held 46.5 KB of PMC's heap (battle 25,176 bytes, trainer 21,312; both
mostly static frame / texture scratch), and the trainer runtime animated nothing (its config member 3203 is not in
`pwan.narc`, which ends at member 3012).

Runtime (`src/w2anim/w2u_anim_streams.cpp`, resident in White2Upgrade.dll): MegaB2W2's AnimSprites, generalised.
- Any MCSS system: a stream starts at MCSS's three `LoadMCSSGraphicsData` calls (ARM9), ticks at every caller of
  `MCSS_Main` (ov168 battle, ov194, ov207 summary, ov265, ov284, ov294, ov298, ov307: every BL to 0x2019B14 in White 2's
  ARM9 and decompressed overlays) and ends at `MCSS_DelSprite` (also reached from `MCSS_Exit`). So battle, summary,
  evolution, egg hatch and the other MCSS screens are covered by the same eleven generic hooks (plus four for
  evolution's morph renderer, Phase 4b; PWAN had 35), and form changes, Transform and Substitute need no special
  case: each reloads MCSS graphics.
- Index read from the ROM at sprite load (binary search, nothing kept in RAM); all buffers on the sprite's own game
  heap (at most 8,084 bytes per stream); nothing in PMC's heap but the code.
- TEX4 mode (new): the sprite keeps its native 4 bpp texture, cells and palette slot; each frame replaces the 96 rows
  x 48 bytes its carrier cells show. A3I5 mode (MegaB2W2's 128x128) stays for w2anim-authored sprites.
- Durations in ms or in 1/60 s ticks (PWAN's); MCSS's own speed and pause flags apply.

Data (`tools/w2anim/build_w2anim_streams.py`, build target `build_w2anim_streams`): the PWAN assets are converted at
build time into `w2anim/streams.bin` (PWAN's 166.5 MB NARC -> 31.4 MB: LZ10 per unique frame). Each config row's
stream goes to the sheet the game itself loads (W2U's `GetPokemonDataIDBase`, ported): PWAN drew form 0 on that block
too; for forms it switched MCSS to block asset * 20, which differs only for Zygarde forms 2 / 3 (identical blocks) and
Minior's meteor colours (same cells). Most carrier sets still hold an older static sprite and palette (PWAN overwrote
both at once), so 1,005 of the 1,111 streams carry their PWAN palette (normal) and a shiny one mapped through the
set's normal -> shiny NCLR pair.

Effect on the PMC heap (build audit, which now counts each module's BSS): resident set 110.5 KB, 94.3 KB free in a
battle with no module loaded; with every battle module loaded at once 26.0 KB stay free (before: 9.3 KB over a 164 KiB
heap). The runtime adds 4.2 KB to the core. ROM: 500 MB -> 362 MB.

Checked (headless, `w2u-local/harness/wave_sprites.yml` + `sprite_compare.py`): battle sprites captured every second
frame for 3.2 s on a PWAN build and on this build, Gen 6 (Greninja / Xerneas), Gen 7 (Litten / Primarina: native block
!= asset), Gen 9 (Ceruledge / Armarouge: no asset block), doubles (four Gen 8 sprites) and a vanilla control: each
w2anim frame matches a PWAN frame (median 0-11 differing pixels in the sprite boxes, below the backgrounds' own
frame-to-frame changes); the phase of the loops differs. Battle start (every frame from boot): the sprites appear with
their streamed art and colours on their first frame. Mid-battle switch with animations on (every frame): MCSS's recall
fade to white and the send-out's white silhouette, scale-up and colour fade-in all run on the streamed sprite. Not
checked headlessly (W2U ROMs do not boot to the field in melonDS-headless): summary, evolution, egg hatch and the other
MCSS screens.
Regression on this build: wave_mega 5/5, A 71/71, B 10/10, C 20/20, field 18/18, shared 61/61 (EMERGENCY_EXIT made
deterministic first: it only passed while the damage roll left the holder above half HP), shared extra 3/3.

### Phase 4b: every MCSS screen, evolution, trainers, first frame (2026-10-05)

Screens. Every screen that shows a Pokemon sprite through MCSS builds it with the same ARM9 helpers as battle
(`AddPokeMcss` 0x201C178, or `BuildSpriteParams` 0x201C070 / `...FromPp` 0x201C008 + `MCSS_Add`), found by scanning White
2's ARM9 and every decompressed overlay for their callers: ov168 battle, ov194, ov207 summary, ov265 Hall of Fame, ov284
evolution, ov294, ov298, ov307 egg hatch. They resolve the sheet through `GetPokemonDataIDBase`, so the same index entry
streams the sprite on all of them, from the generic hooks. PWAN's summary and egg-hatch runtimes hid the MCSS sprite and
drew a 2D OBJ copy instead; that is not needed. PWAN covered neither ov194 nor ov294 (PWAN species showed their carrier
art there). Hall of Fame (ov265) shows the first frame only, as PWAN did.

First frame ("priming"). Most carrier sets hold an older sprite (see above). MCSS uploads a sprite's texture and palette
from its work in a VBlank task after `LoadMCSSGraphicsData` (ARM9 0x201B788: work +0x00 NNSG2dCharacterData, pRawData
+0x14, linear 256-texel rows; +0x04 NNSG2dPaletteData, pRawData +0x0C; the work is found from the sprite's task handle).
The runtime writes the stream's frame 0 and palette there right after the load, so the carrier's own art never reaches
the screen, on any screen.

Evolution (ov284). Its morph sequence draws the Pokemon before / after with a second renderer from its own 128x128
bitmaps built from the native sheets (work +0x58 -> +0x08 / +0x0C; bitmap +0x10, VRAM +0x14, palette +0x2C faded towards
+0x4C at +0x56: the layout PWAN's evolution runtime documented). Without help it showed the carrier's older pose (checked
with Frogadier, whose carrier is a different sprite). The runtime tags the two evolution sprites when the scene adds them
and writes their streams' current frame (the decoded frame the sprite already holds: no new buffer) and faded palette
into those bitmaps around the renderer's update and draw. Checked headlessly: a won battle levels Froakie to 16 and the
scene plays after it (the harness loads the overworld after a win); silhouette and colour reveal now show the streamed
Frogadier.

Trainers. Pokeweb's trainer animation format is supported: `assets/pokeweb_pwan/trainers/` with a `PWNT` config.bin
({graphic, asset} rows) and NNN.pwan (none exist in W2U yet). A trainer graphic (arc 71, sheet graphic * 8 + 1) gets an
index entry with a CARRIER flag: the runtime loads the front set of a Pokemon carrier block instead (the most common
carrier cell set, block 650 today), primes it with the trainer's frame 0 and palette, and streams the rest; frames move
up 8 rows (trainer canvas on row 96, carrier ground point row 88); graphics sharing an asset share its stream. Checked
headlessly with a temporary test set (every graphic -> one animation): the defeated trainer slides in animated, in its
own colours, with no carrier art on the first frame; the test set is not committed.

Heap: all of this uses the stream's existing buffers (the per-frame streaming rule: one compressed frame, one decoded
frame per sprite, on the sprite's game heap); nothing new in PMC's heap but code.

Harness (local, `w2u-local/harness/wave.py`): `post` (frames after the last turn, A presses, keys), `capture`,
`capture_intro`, `capture_turns`, `heap_at_menu`, `peek`, `stuck_pc` / `stuck_heap`, a `P<n>[@x,y]` party action,
`--runs=DIR` / `--leave=K` (a second run alongside a regression). After a win the harness loads the overworld, but the
bundled save's field menu has no POKeMON entry, so the field summary is not reachable that way; summary, egg hatch,
Hall of Fame and ov194 / ov294 / ov298 still want an in-game look.

Notes:
- Not converted: Raichu forms 1 / 2 and Slowbro form 1, whose pokegra blocks 1097 / 1098 / 1117 are missing from the
  built archive (see "Open W2U issues").
- Black 2 keeps the PWAN runtimes (Black 2 is deferred on this branch); their sources and the PWAN tools are unchanged.
- Pokeweb's sprite workflow is unchanged: it still writes PWAN assets, which the White 2 build converts.

### Fix: one-frame texture blackouts when several sprites change frame together (2026-10-05)

Seen on the showcase recording (doubles: Kyogre, Mega Gardevoir, Rillaboom, Mega Charizard Y): every 0.5 s one frame
lost every texture of the 3D layer (both sprites gone, the battle background in flat colours). While w2anim's VBlank
task uploads, texture VRAM is mapped to the CPU; the 3D engine starts drawing the next frame at about scanline 214. A
TEX4 frame goes up one row per `gfxUploadTexture` call, about 9 scanlines per 96 rows. Measured with a probe: one or two
sprites ended by line 201 / 210, three 96-row sprites changing frame in the same VBlank ended at line 218, which is
when the blank frames appeared (their loops lined up every 30 frames). `VBlankUpload` now estimates each upload's
scanlines and leaves one that would not end by line 211 for the next VBlank (that sprite's frame shows 1/60 s later).
Showcase re-recorded: no blank frames (32 before). wave_mega 5/5; wave_sprites singles still match PWAN's frames
(median 0-4 differing pixels); SPR_DOUBLE still fails only on its known turn input.

## Polish: heavy rain and terrain animations (2026-10-05)

Heavy rain (Primordial Sea; `tools/graphics/build_strong_weather_effects.py`, SPA 1032, scripts 961 / 962):
- Denser rain. Rain Dance's emitter already fills the battle's particle pool: its drops fell in waves (a burst, about
  0.4 s of nothing, another burst), each drop living 40 frames, most of them below the screen. The drops now live 22
  frames (about one crossing of the screen) and the emission is x1.5: steady rain, 1.58x the rain pixels of the same
  scene before (A/B in the harness), with gaps gone.
- Tint: the background dims towards a dark blue-grey (16, 28, 64) instead of black, at the same strength, and the
  battlers take a faint blue tint (3/16, ChangeColor on every battler) that follows the background fade in and out.

Terrains (`w2u_terrain_texture.cpp`, White 2; Black 2 keeps the immediate swap):
- Fades. A terrain clone changes only the floor's image and its palette range (one contiguous run from entry 0 on
  every field, found at run time by comparing the palettes), and the image indices differ, so the floors cannot
  cross-fade through one palette. The floor's palette range fades to the incoming floor's average colour, the image is
  swapped while every floor colour is that colour, and the incoming palette fades in; only the floor range is uploaded
  (palette VRAM, in the VBlank hook). A new terrain fades in once its move's animation has ended (Misty's and
  Electric's animations fade the whole field palette themselves; the two would fight); Electric keeps its masked swap
  under its animation's black field fade as its fade-in. Every terrain fades out at its end message (expiry, Steel
  Roller, Defog) or into a replacing terrain. Ambient particles stop spawning when the fade-out starts and the system is
  released once its emitters have died out (`GFL_PTC_GetEmitterNum`, at most 6 s), so nothing is cut off. An animation
  that starts a field fade during a floor fade finishes the floor fade at once.
- Pace (`W2U_TERRAIN_PACE`): floor UV animation per 60 fps frame / ambient emit gap / fade halves.

  | Terrain | Floor step | Emit gap | Fade out / in | Feel |
  |---|---|---|---|---|
  | Electric | 1.25 (was 0.5) | 20 (was 32) | 10 / 14 | quick, busy |
  | Grassy | 0.31 | 130 (was 100) | 26 / 40 | calm |
  | Misty | 0.25 | 240 (was 200) | 30 / 46 | calmest |
  | Psychic | 0.56 mean, two out-of-step waves (0.04-1.3) | 28-110, irregular | 20 / 30, wobbling | uneven, surging |

  Measured floor motion while idle (mean frame difference): Electric 1.8, Psychic 0.6-2.6 drifting, Grassy 0.7,
  Misty 0.45.
- Build guard: the ESDB maps `__aeabi_uidivmod` / `__aeabi_idivmod` but not the plain `__aeabi_uidiv` /
  `__aeabi_idiv`; a call to one stayed a branch to itself after relocation (an endless loop: the first version hung
  every Grassy / Misty / Psychic battle at the Surge popup). `-Os` emits them even for constant divisors. The
  `w2u_main.dll` rule now fails when the ELF imports either (the PWAN runtimes already had this check).
- Verified headless (recordings `w2u-local/harness/previews.yml`): Surge → fade-in after the animation, idle turn,
  Steel Roller → fade-out, for all four terrains; heavy rain start and turn-end effects. wave_field 18/18
  (PRIMAL_RAIN_END given `no_crits`: a critical Flamethrower could knock Wobbuffet out), wave_b 10/10. Heap audit:
  core 111,112 bytes resident, 88.4 KB free with no module, 20.1 KB with every module.

## Fix: PMC heap out of memory (2026-10-05)

Symptom: a battle froze after both sides chose (top screen "What will X do?", bottom screen the idle Poke Ball), e.g.
a player with Damp or Good as Gold (module `abilities/mb_defense`) against a foe with Mind Blown (`moves/flow`).
Cause, found with the harness's new `stuck_pc` / `stuck_heap` keys: ARM9 spun in overlay 344 at 0x21FD840, the end of
ExtLib's `HeapArea::Alloc`. When no free block is large enough it copies an error string and loops forever instead of
returning null, so the module loader's `!allocation` fallback never ran. The heap at that point (164 KiB):

| Block | Bytes |
|---|---:|
| `White2Upgrade.dll` (core) | 101,032 |
| `PokewebPwanBattleW2.dll` | 25,176 |
| `PokewebPwanTrainerW2.dll` | 21,312 |
| battle log + counters | 5,216 |
| `abilities/mb_defense` | 5,144 |
| harness DLL, PMC's own blocks | 6,176 |
| free | 3,704 (`moves/flow` needs 5,616) |

Phase 5 (about 5 KB of resident code and art) tipped it; before it about 3 KB were left, so any battle loading three
larger modules was already at risk, on the harness and in the real game alike (the harness DLL is 1.3 KB). The build's
heap audit did not catch it: it is not part of the `White2Upgrade.nds` target, is enforced only with `strip_rpms`, and
counts PWAN at its fixed size (7.8 KB) while its BSS scratch keeps it at 25 KB.

Fixes:
- **200 KiB heap** (`tools/patch_pmc_sysheap.py`, MegaB2W2's value and patch site). PMC takes its heap from the top of
  ARM9 arena region 0 (it ends at 0x023E0000); the game takes its own heaps from that region once at boot and never
  again (MegaB2W2's research: every caller of the arena functions is boot code). Measured in a W2U battle: region 0
  free from 0x023AC104 to the heap's start, 44,796 bytes below a 164 KiB heap; at 200 KiB the heap starts at
  0x023AE000 and 7,932 bytes stay free (W2U's boot uses 0x4E0 bytes more arena than vanilla). The audit uses 200 KiB.
  DSi mode places PMC's heap elsewhere (`g_DSiModeLegacyRAMStart`); not checked yet.
- **Loader guard** (`w2u_battle_module_loader.cpp`): before allocating a module the loader walks `HeapArea`'s free
  list (found from a probe allocation's block header, so it works wherever PMC put the heap) and refuses a module that
  cannot fit: that mechanic is missing for the battle instead of the game freezing. Telemetry counts refusals
  (`heapRefusalCount`, `lastRefusedBytes`, `lastLargestFreeBytes`). Checked on a copy of the ROM with the cap set back
  to 164 KiB: the same battle plays on (Mind Blown hits without its recoil handler).
- **PWAN replaced by w2anim's runtime** (D2 changed; Phase 4): frees the PWAN DLLs' 46.5 KB in battle.

Backup plan, on hold until the heap is short again (user, 2026-10-05): move the bulk of the Mega extras out of the
resident core into an on-demand module loaded when a Mega Evolution starts (cry reverb, glyph projection and art, the
glyph place table: about 4 KB; the hooks and the 160-byte gauge icon stay resident). It needs a module kind that
exports functions rather than handler tables (the registry and loader only know handler exports today). Other options
if that is not enough, in order: art and tables into ROM files read on demand (MegaB2W2's habit); a larger cap is
limited by the 7.9 KB of arena left.

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
(`SandSpit.cpp`). W2U already has the Surges and Surge Surfer, so MegaB2W2's versions of those were not ported.
(Grass Pelt was thought to be W2U's too; it had no effect there and was added in phase 6.) Primary ability count 114 -> 121.

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

## Phase 6: abilities both projects implement (2026-10-05)

MegaB2W2's Showdown-checked scenarios for the 58 abilities W2U already implemented (51 through its registry, 7 in its
resident code), run against W2U's own implementations: `w2u-local/harness/convert_scenarios.py` converts them
(keys to IDs, MegaB2W2 debug-log checks dropped, doubles targets mapped; spec `wave_shared.yml`, hand-adjusted where
only the wording differs), plus W2U-specific cases (`wave_shared_extra.yml`).

Fixed in W2U:

| Issue | Fix |
|---|---|
| Cheek Pouch and Symbiosis never triggered on White 2 when an item was used up (a Berry eaten, a Gem used) | `BattleHandler_ConsumeItem` / `ServerControl_ChangeHeldItem` replacements (they raise `EVENT_CONSUME_ITEM`) were inside the `!W2U_DYNAMIC_BATTLE_CORE` handler block: the dynamic core skipped them and the child modules drop unreferenced hooks, so they were never installed. Moved out of the block (`!W2U_BATTLE_CHILD`); Black 2's static build is unchanged. No other hook is in such a block (scanned) |
| Merciless was a 50% crit (stage 4 in this generation's table) | `W2U_CRIT_STAGE_ALWAYS`: Merciless sets it, W2U's `BTL_CALC_CheckCritical` returns a crit for it (the native caller clamps the stage it passes, not the variable) |
| -ate abilities converted Weather Ball (no weather), Judgment, Natural Gift, Techno Blast, Hidden Power, Struggle, Multi-Attack, Revelation Dance, Terrain Pulse | `RewriteNormalMoveType` leaves them (Showdown's `noModifyType`); Weather Ball can't touch Gengar again |
| Grass Pelt had no effect (only in the Mold Breaker list) | Ported (Defense x1.5 on Grassy Terrain), module `abilities/mb_terrain`; measured x0.679 |
| Damp (above, field checks) | Mind Blown / Misty Explosion stopped too |
| Chilling Neigh had no effect (the one MegaB2W2-only ability left after waves A-C) | Aliased to Moxie (Attack +1 after a KO), as MegaB2W2 did |

Same behaviour, different wording (W2U's texts kept): Aroma / Sweet / Flower Veil ("X was protected by ... Veil!"),
Dark Aura, Receiver ("copied"), Symbiosis ("X's Symbiosis! Y obtained one Z"), Disguise (only "disguise was busted",
no "served it as a decoy"), Comatose (no entry message; Thunder Wave "But it failed!" rather than "doesn't affect").

For hzla to decide (left as W2U has them):
- Stakeout does not count the battle's first Pokemon on turn 1 (W2U tracks them on purpose); Showdown doubles damage
  against a lead on turn 1. Against a Pokemon sent in after a faint both agree (x2, tested).
- Disguise works only for Mimikyu (as Showdown); MegaB2W2 let any holder use it.
- W2U keeps this generation's critical-hit rates (1/16 base, x2 damage).

Checked: 61 converted scenarios + 3 extras (Cheek Pouch, Symbiosis mid-battle, Chilling Neigh) pass, and waves A, B,
C and the field checks were re-run on the same build (all pass); not checked: Disguise's 1/8 chip
damage (no HP read), Aroma Veil protecting an ally (the foe AI picked its own partner as the Taunt target), Cheek
Pouch's own MegaB2W2 scenario and Protean on switching (only debug-log checks).

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
