# Gen 6/7 custom move-handler audit

Branch note: the fix release below was built on `megab2w2-integration`.
Those implementation changes are preserved separately and have **not** been
merged into `main`. The portable test suite is now maintained on `main`;
this historical result must not be read as certification of a `main` build.

Audited and fixed 2026-10-05. Scope: existing, non-Z Gen 6/7 move-table
mechanics and Belch's resident berry gate. Fixes use the existing on-demand
DLL groups and resident dispatch hooks; no new modules or animation changes
were needed.

The registry contains 61 eligible move IDs; Belch adds one resident mechanic.
Geomancy's native charge/stat data and Solar Blade's copied Solar Beam behavior
were source-reviewed but not emulator-tested, following the native-reuse policy.
The remaining 60 moves received focused native headless scenarios.

Initial audit: 113 current scenario identities observed across incremental runs;
101 passed and 12 failed. Eleven failing scenarios exposed the behavioral issues
below; the twelfth is Water Shuriken's generation-category mismatch. This
count excludes superseded test mistakes and counts follow-up actions inside
their parent scenario, not as extra tests.

## Fix release

Final complete-suite run: **117/117 scenarios pass**, in 93 native headless
batches covering 60 audited moves. All twelve original failures pass. The
expanded suite adds two Shore Up cases at 175 maximum HP to distinguish floor
rounding from nearest-integer rounding, plus two additional Substitute controls.
This certifies the listed scenarios, not every exception on every move's page.

- Trapping uses a per-defender damage-reaction event and native source-dependent
  condition work, rather than an attacker-only end-of-move scope.
- Freezy Frost resolves Haze from the native move table and calls its field
  callback after damage. The old named Haze symbol pointed into a literal pool.
- Aurora Veil uses the correct execution-check variables and rechecks hail on
  application; Flower Shield no longer inherits Rototiller's grounding filter.
- Revelation Dance runs in the final type-resolution phase. Laser Focus is
  active immediately, including called attacks during its activation turn.
- Flying Press shares the native Minimize damage modifier and skip-accuracy
  callback with Supercell Slam.
- Electric Terrain retains sleep prevention but removes existing-sleep cures.
  Happy Hour uses the event dispatched by its existing move metadata.
- Shore Up requests floor rounding through the resident recovery dispatcher;
  other recovery moves retain their original rounding. Water Shuriken's packed
  category is now Special, matching its Gen 7 Ash-Greninja behavior.
- The wider rerun also exposed Spectral Thief hitting a Substitute rather
  than the real target. Its table now uses the native bypass callback, and a
  resident damage-classification adapter dispatches that event for damage,
  not just status targeting. The target receives full calculated damage while
  the doll remains intact, including when boosts are stolen. A native Tackle
  control checks that ordinary attacks still damage the doll. No battler HP
  or Substitute state is temporarily edited to implement the bypass.

Two assertions previously hidden behind earlier failures were corrected:
Flying Press's Normal target still receives its ordinary Fighting weakness,
in addition to the Minimize multiplier; Dancer damage is measured after the
triggering ally attack and includes both attacks' actual HP application.
Neither correction relaxes the required hit, power, critical, or damage checks.
Belch's consumed-berry fixture now uses native Substitute to lower HP and
trigger Sitrus consumption, rather than depending on Stuff Cheeks, which is not
registered in this branch. Uneaten-berry and Natural Gift controls remain.

Host checks: 145 harness/oracle tests, strict TypeScript checking, and 46 upgrade
repository tests pass. A compiled-callback test exercises event scopes, trapping
guards, Laser Focus expiration, and recovery rounding across HP values 1–1023.
Child packaging/import/export checks pass. The fresh stripped heap audit
measures a 62,472-byte core and 28,140 bytes free in the conservative all-29-group
scenario, above the 12 KiB headroom requirement. Its historical 8 KiB core-size
savings gate does not pass: the stored 63,700-byte monolithic baseline exceeds
the current core by only 1,228 bytes. The normal resident-battle comparison
saves 31,124 bytes. The baseline was not refreshed or the gate bypassed;
full heap acceptance is not claimed by this move-handler fix.

Black 2's shared move source compiles in static mode with hidden group getters.
The damage adapter also compiles for Black 2; its register/stack instruction
window was verified against both US overlays and its relocation was added to
the reviewed alias map. Full Black 2 packaging is blocked by the pre-existing
unreviewed terrain-indicator assembly address `0x021EE748`; that mapping and
the compatibility baseline were not changed. Black 2 gameplay is not certified
by these White 2 tests.

ROM: `White2Upgrade-gen67-audit-fixes-20261005-r3.nds`, copied to the repositories'
parent directory. SHA-256:
`a5e233954cc122db56b54bc639a287d3a0288f7ce66689fdca44064f6142ef5d`.

Sources: Bulbapedia's [Gen VI](https://bulbapedia.bulbagarden.net/wiki/Category:Generation_VI_moves)
and [Gen VII](https://bulbapedia.bulbagarden.net/wiki/Category:Generation_VII_moves)
lists and individual move Effect sections, compared with
`src/pokeweb_gameplay/w2u_moves.cpp`, resident ability hooks,
`src/pokeweb_gameplay/battle_modules/registry.json`, and `data/pml/moves/`.
Use ordinary turn-based core-series rules, not Legends or Z-move descriptions.

## Original confirmed failures (fixed)

These were failing regression scenarios, not expected failures accepted as passes.
The observations below describe the pre-fix ROM, not the fix release.

| Mechanic | Native observation | Required behavior / likely source cause |
| --- | --- | --- |
| Anchor Shot; Spirit Shackle | The user's trap condition becomes active; the target's remains clear | Trap the target, recording the user as the source. `HandlerAnchorShot` calls native Spider Web with a damaging-move event context. [Reference](https://bulbapedia.bulbagarden.net/wiki/Anchor_Shot_(move)) |
| Freezy Frost | Damage occurs, but boosted/lowered stages on both battlers survive through the next command menu | Reset all active battlers' stages after damage. `HandlerFreezyFrost` similarly calls native Haze with a different event context. [Reference](https://bulbapedia.bulbagarden.net/wiki/Freezy_Frost_(move)) |
| Aurora Veil | A fresh, weather-free battle still gains the side effect | Require effective hail under the Gen 7 rule. The execute check rewrites `VAR_MOVE_FAIL_FLAG`; compare the functioning checks using `VAR_MON_ID`/`VAR_FAIL_CAUSE`. Its application callback does not independently check weather. [Reference](https://bulbapedia.bulbagarden.net/wiki/Aurora_Veil_(move)) |
| Flower Shield | A levitating Grass-type receives no Defense boost; its grounded control does | Flower Shield, unlike Rototiller, includes airborne Grass-types. The shared Grass-stat path applies a grounded filter. [Reference](https://bulbapedia.bulbagarden.net/wiki/Flower_Shield_(move)) |
| Revelation Dance | Normalize changes a Psychic user's move to Normal | Ignore Normalize and the Normal-conversion abilities, while retaining Electrify/Ion Deluge. Its current `EVENT_MOVE_PARAM` callback does not reliably win type resolution. [Reference](https://bulbapedia.bulbagarden.net/wiki/Revelation_Dance_(move)) |
| Laser Focus | Next-turn attacks crit, but a same-turn Dancer attack does not | The effect starts immediately and lasts through the following turn. `W2U_MoveState_IsLaserFocused` only accepts counter value 1, not the initial value 2. [Reference](https://bulbapedia.bulbagarden.net/wiki/Laser_Focus_(move)) |
| Flying Press | Against a native Minimize user, accuracy still rolls and the move misses at draw 99 | Minimize must make it hit and double damage. The registered table only adds Flying effectiveness. [Reference](https://bulbapedia.bulbagarden.net/wiki/Flying_Press_(move)) |
| Electric Terrain | It cures an opponent's existing native Rest sleep | Prevent new sleep; do not cure existing sleep. The same Rest scenario remains asleep under Misty Terrain. `TerrainCureSleep` explicitly queues the cure. [Reference](https://bulbapedia.bulbagarden.net/wiki/Electric_Terrain_(move)) |
| Happy Hour | PP/action completion occur, but the battle's money-double flag remains clear | Set the prize-money multiplier. Its sole `EVENT_CALL_FIELD_EFFECT` callback is paired with non-field-effect move quality; dispatch is the first place to inspect. Prize payout itself was not tested. [Reference](https://bulbapedia.bulbagarden.net/wiki/Happy_Hour_(move)) |
| Shore Up | At 165 maximum HP outside sand, it heals 83 rather than 82 | The documented half-HP recovery rounds down. The handler changes the recovery ratio but inherits native recovery rounding. Sand recovery passed the sampled HP value. [Reference](https://bulbapedia.bulbagarden.net/wiki/Shore_Up_(move)) |

The two trapping moves share one defect; the table describes ten distinct
behavioral issues affecting eleven moves. The fixes are described above.

## Generation-policy mismatches, not automatically handler defects

The current repository has no single consistent generation policy:

| Move/family | Current behavior/data | Version distinction |
| --- | --- | --- |
| Water Shuriken | Now Special; Ash-Greninja uses three 20-power hits | Gen 6 was physical; the fix release deliberately uses Gen 7 behavior. [Reference](https://bulbapedia.bulbagarden.net/wiki/Water_Shuriken_(move)) |
| Flying Press | 80 power | Gen 6: 80; Gen 7 onward: 100. The Minimize defect is independent of this choice. |
| Fell Stinger | 30 power and +2 Attack on a KO | Gen 6 values; Gen 7 uses 50 and +3. Both current survivor/KO scenarios pass. [Reference](https://bulbapedia.bulbagarden.net/wiki/Fell_Stinger_(move)) |
| King's Shield | Contact lowers Attack by two stages | Correct for Gen 6/7; Gen 8 lowers it by one. The native -2 and status-pass-through scenarios pass. [Reference](https://bulbapedia.bulbagarden.net/wiki/King%27s_Shield_(move)) |
| Terrain damage boosts | 1.3 times | Gen 8 onward policy; Gen 6/7 used 1.5. Electric Terrain's current 1.3 damage path passes. |
| Freezy Frost | 100 power / 90 accuracy | Gen 8 unused-move data; Let's Go used 90 / 100. Its missing stat reset is a separate issue. |

Floral Healing heals 118/157 HP at 235 maximum HP, rather than the initially
assumed floors 117/156. Its [description](https://bulbapedia.bulbagarden.net/wiki/Floral_Healing_(move))
specifies the half/two-thirds fractions but not integer rounding. The final test
allows the adjacent floor/ceiling values and separates the move's heal from
Grassy Terrain's later residual heal. Exact cartridge rounding remains unverified;
this is not counted as a confirmed defect.

Fairy Lock is outside the custom-table test scope because it is a resident
Spider Web alias. That alias does **not** establish canonical Fairy Lock's
global next-turn restriction. It is a source-level limitation, not a passed
behavioral test. Other excluded native/data reuse includes Phantom Force,
Hold Back, Infestation, Nature's Madness, Power Trip, Prismatic Laser,
Pika Papow, and Veevee Volley. Missing mechanics without an existing custom
registration/hook are not covered by this audit.

## Focused coverage

"Pass" means only the listed scenarios passed; it is not blanket certification
of every exception on a move's page. Fixed entries include focused post-fix checks.

| Move(s) | Scenarios covered | Result |
| --- | --- | --- |
| Freeze-Dry | Water weakness, Water/Ground four-times weakness, ordinary neutral Ice damage | Pass |
| Flying Press | Normal and Grass compound effectiveness; native Minimize | Pass after fix |
| Mat Block | First-turn damage protection | Pass |
| Rototiller | Grounded Grass boost; Levitate exclusion | Pass |
| Flower Shield | Grounded/levitating Grass Defense boost | Pass after fix |
| Sticky Web | Opposing side deployment; duplicate use does not stack | Pass |
| Fell Stinger | Surviving target; KO +2 Attack | Pass under Gen 6 policy |
| Trick-or-Treat; Forest's Curse | Added Ghost immunity / added Grass Fire weakness, checked with a following attack | Pass |
| Ion Deluge; Electrify; Plasma Fists | Resolve a real incoming move to Electric | Pass |
| Parting Shot | Attack and Special Attack drops with no available bench | Pass; switching not certified |
| Topsy-Turvy | All seven positive/negative/neutral stage values | Pass |
| Crafty Shield | Targeted status blocked; damage not blocked | Pass |
| Electric Terrain | New sleep blocked; existing Rest sleep; boosted following attack | Pass after fix |
| Grassy Terrain | Grounded end-turn one-sixteenth healing | Pass |
| Misty Terrain | Paralysis prevention; existing Rest sleep not cured | Pass |
| Psychic Terrain | Incoming priority damage prevented after setup | Pass |
| King's Shield | Physical contact block/-2 Attack; status passes through | Pass under Gen 6/7 policy |
| Water Shuriken | Ash-Greninja Special category, three 20-power strikes | Pass after Gen 7 category fix |
| Spiky Shield | Contact protection and one-eighth retaliation | Pass |
| Venom Drench | Poisoned target receives three drops; healthy target does not | Pass |
| Powder | Fire move prevented; quarter-maximum-HP payment | Pass |
| Magnetic Flux | Plus user boosted; ineligible ability not boosted | Pass |
| Happy Hour | Native action and prize-money flag | Pass after fix |
| Shore Up | Ordinary and sand recovery; floor-vs-nearest cases | Pass after fix |
| First Impression | First turn damage; later selection gate | Pass; later-turn execution failure not separately certified |
| Baneful Bunker | Contact blocked and attacker poisoned | Pass |
| Anchor Shot; Spirit Shackle | Damage and trap recipient/source | Pass after fix |
| Darkest Lariat | Ignores positive/negative Defense and Evasion; retains user Attack stages | Pass |
| Sparkling Aria | Damage and target burn cure | Pass |
| Floral Healing | Half and Grassy two-thirds targeted healing | Pass for fractions; exact rounding unverified |
| Strength Sap | Pre-drop Attack healing; raised Attack; -6 failure | Pass |
| Spotlight | Real doubles target redirection of an ally attack | Pass for this redirection case |
| Laser Focus | Next-turn critical; Battle Armor veto; same-turn Dancer critical | Pass after fix |
| Throat Chop | Prevents a later same-turn Growl | Pass |
| Pollen Puff | Opponent damage; real doubles ally healing | Pass |
| Burn Up | Pure Fire becomes typeless; dual Fire/Flying keeps Flying; non-Fire fails | Pass |
| Speed Swap | Raw Speed swapped, stages retained | Pass |
| Purify | Target status cured/user healed; healthy target does not heal user | Pass |
| Revelation Dance | Primary Psychic type; Normalize exclusion | Pass after fix |
| Core Enforcer | Already-acted suppression; unacted target unaffected; Stance Change exception | Pass |
| Instruct | Real doubles ally executes Tackle twice | Pass |
| Beak Blast | Incoming contact during preparation burns its attacker | Pass |
| Aurora Veil | Hail application; weather-free rejection | Pass after fix |
| Shell Trap | Physical trigger; special/Substitute hits do not trigger | Pass |
| Stomping Tantrum | Fresh turn, failed Thunder Wave, successful Splash | Pass |
| Spectral Thief | Positive stages before damage, unboosted damage, Simple, Contrary, full damage past native Substitute, Clear Body/user cap | Pass after additional fix |
| Sunsteel Strike; Moongeist Beam | Neutral Wonder Guard / full-HP Multiscale bypass | Pass |
| Photon Geyser | Attack/Special Attack/tie/stage category decisions; physical Fur Coat bypass | Pass |
| Mind Blown | Rounded-up half HP on hit/Protect; Magic Guard and Damp | Pass |
| Glitzy Glow; Baddy Bad | Damage and matching native screen deployment | Pass |
| Sappy Seed | Damage and Leech Seed condition | Pass |
| Freezy Frost | Damage followed by both battlers' stat reset | Pass after fix |
| Sparkly Swirl | Damage and active user's burn cure | Pass; bench cures not certified |
| Belch | Uneaten-berry rejection; native Sitrus consumption enables use; Natural Gift does not | Pass |
| Geomancy; Solar Blade | Charge/stat metadata and copied charge/weather behavior | Source review only; native-reuse exclusion |

Not yet exhaustively covered: switch/faint/Baton Pass lifetimes, duration
boundaries, additional suppression exceptions, all redirection competitors,
all Shield Dust/Sheer Force/Substitute interactions, spread/multi/triple formats,
all screen stacking/removal/Light Clay cases, party-wide status cures,
called-move ability-ignore rules, and animation/text timing. Black 2 was not
emulator-tested in this audit. Passing tests do not imply these are correct.

## Reproduction and evidence

From this upgrade repository root:

```sh
python3 tools/test_battle.py move --move gen67-audit --rom ./game.nds --continue-on-failure
python3 tools/test_battle.py move --move gen67-audit --rom ./game.nds --variant spectral-thief
python3 tools/test_battle.py unit
```

The suite exits nonzero if any required assertion fails.
`--continue-on-failure` restores each case and continues; it never makes a
failure pass. `--variant` is repeatable. Read `tests/battle/README.md`
for dependency setup and adding scenarios.

Inventory: `tests/battle/gen67-move-inventory.json`.
Scenarios: `tests/battle/scripts/move-handler-gen67-fixtures.ts`.
Independent assertions: `tests/battle/scripts/gen67_move_oracles.py`.
The fixture builder checks packed move metadata, native executable signatures,
four-battler setup where applicable, and ROM/save hashes. Expected outcomes are
not derived by reading handler source or invoking a handler from the host.
RNG overrides control actual native draws; pre-action raw stats/stages are
explicit fixture preconditions, not post-result corrections.

Initial audit input: `White2Upgrade-gen89-batch40-20261005.nds` (unchanged), SHA-256
`a5760f1ed082ea56c9eeb998df9cace9bdb6c7b9ab9bb9b7e29e6b887bfd16fc`.
Multiple incremental runs were combined by current variant/case identity;
superseded fixture mistakes are not counted as game defects. Early scenarios
used the native action checkpoint; later lifetime-sensitive scenarios reached
the next command menu. This was not one pristine complete-suite run.

Initial evidence is under ignored `work/move-handlers/gen67-audit*-20261005/` directories
in the former harness host, Pokeweb Serverless: per-case native state/damage/selection JSON, failure
screenshots, batch logs, input manifests and result summaries. Fixture ROMs and
in-memory snapshots are removed by default; checksum-valid saves are retained.
No user save was overwritten.

The canonical tests now live in this repository's `tests/battle/`. New runs
write into this repository's ignored `work/`; historical evidence above was
preserved in place rather than discarded or treated as a new test run.

Fix-release evidence is under `work/move-handlers/gen67-fixes-*-20261005/`.
The early focused rerun exposed the remaining Haze getter problem and the two
assertion-scope mistakes; it is retained as diagnostic evidence, not counted
as a final passing run. `gen67-fixes-final-controls-20261005` passes Freezy
Frost and the corrected same-turn Dancer damage-application assertion.

The wider first-ROM run (`gen67-fixes-full-20261005`) reached all 115 cases:
113 passed; the Belch setup dependency and Spectral Thief Substitute-routing
defect failed. The first bypass-table-only attempt still hit the doll; its
matching real-HP loss was the opponent's later Substitute payment, not damage
capped to the doll's HP. `gen67-fixes-substitute-controls2-20261005` passes all
three final-ROM controls: real damage past the doll, boost theft past the doll,
and native Tackle still damaging the doll. Supercell Slam's shared Minimize
helpers also passed their three focused regression controls.

An additional diagnostic Eerie Spell run has the same 4/10 passing case
identities on the pre-routing-adapter and final ROMs. Its existing PP-drain,
Sheer Force and damage-application assertions are not certified or repaired
by this Gen 6/7 scope. Both comparison runs are retained under the same ignored
fix-release evidence prefix; this is not a claim that all Gen 8/9 suites pass.

Final evidence: `gen67-fixes-complete-r3-20261005/result.json` records a complete
run with exit code zero and 117 passing scenarios on the final ROM hash above.
All 93 batch reports confirm their in-memory snapshots were released. No fixture
ROM or save-state files remain in that run; 93 fixture saves are retained as
requested. The reports and saves are Git-ignored, and no user save was changed.
