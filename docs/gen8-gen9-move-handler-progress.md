# Gen 8/9 move-handler progress

Scope: the [reference](gen8-gen9-move-handler-reference.md), easiest first.
Hard entries and entries requiring doubles-format validation are deferred.
Unlisted moves remain pending; this is an incremental batch, not full coverage.
Animations are not changed.

Testing policy: reused/native-data effects are wired and build-checked without
per-move emulator tests, as requested. New custom logic still needs focused
tests. "Wired" below is not a claim of new emulator or full regression coverage.

| Move | Implementation | Focused tests | Status |
| --- | --- | --- | --- |
| Ruination (877) | Resident Super Fang alias; no new DLL | 9 headless cases passed: full/odd/even/1 HP, boosted Defense, Protect, Wonder Guard, Substitute, miss; next-turn smoke passed | Implemented, focused-tested |
| Infernal Parade (844) | Resident Hex alias + existing 30% burn data | Skipped: native reuse | Wired |
| Flip Turn (812) | Resident U-turn alias; preserves Water typing | Skipped: native reuse | Wired |
| Power Shift (829) | Resident Power Trick alias | Skipped: native reuse | Wired |
| Raging Fury (833) | Resident Outrage alias + existing Instruct exclusion | Skipped: native reuse | Wired |
| Thunderclap (909) | Resident Sucker Punch alias + existing +1 priority data | Skipped: native reuse | Wired |
| Temper Flare (915) | Existing Stomping Tantrum table/history in `moves/flow` | Skipped: existing handler reuse | Wired; inherits tracker behavior |
| Torch Song (871) | Existing boost/sound data + native Substitute-bypass callback in `moves/flow` | Skipped: existing handler reuse | Wired |
| Comeuppance (894) | Resident Metal Burst alias; physical, normal priority, native retaliation targeting | Skipped: native reuse | Wired |
| Axe Kick (853) | Resident High Jump Kick crash alias + existing confusion data | Skipped: native reuse | Wired |
| Barb Barrage (839) | Poison-only doubling in `moves/type`; removed Hex alias | 9 cases passed: healthy, ordinary/bad poison, burn, sleep, secondary chance boundary, Sheer Force, Steel immunity | Implemented, focused-tested |
| Bolt Beak (754) | Execution-time target action flag in `moves/flow` | 5 cases passed: unacted, acted, failed action, native switch-in, Instruct | Implemented, focused-tested |
| Fishious Rend (755) | Same action-state handler; biting flag retained | The same 5 cases plus Strong Jaw passed | Implemented, focused-tested |
| Hard Press (912) | Target current-HP scale in `moves/type`; physical category fixed | 7 cases passed: full/near-half/odd/low/1 HP, native HP reduction before damage, Substitute | Implemented, focused-tested |
| Grav Apple (788) | Gravity power boost in `moves/type`; native Defense secondary | 5 cases passed: Gravity off/on, Clear Body, Sheer Force off/on | Implemented, focused-tested |
| Psyblade (875) | Electric Terrain boost in `moves/terrain`, independent of grounding | 4 cases passed: no terrain, Electric Terrain, native removal, both battlers airborne | Implemented, focused-tested |
| Collision Course (878) | Shared post-effectiveness damage modifier in `moves/type` | 5 cases passed: neutral, resisted, super-effective, dual-type weakness, Wonder Guard | Implemented, focused-tested |
| Electro Drift (879) | Same modifier; explicit effectiveness enum whitelist | 6 cases passed: neutral, resisted, super-effective, dual-type weakness, Ground immunity, added-Grass 1/8 resistance | Implemented, focused-tested |
| Fickle Beam (907) | One cached power roll per action in `moves/type` | 104 cases passed: all 100 draws, Parental Bond normal/double rolls, Instruct, Protect | Implemented, focused-tested |
| Double Shock (892) | Parameterized Burn Up table in `moves/type`; pre-Protean prerequisite and Electric-type loss | Skipped: existing handler reuse | Wired; Tera is outside scope |
| Dragon Energy (820) | Resident Eruption alias; native current-user-HP scaling reads this move's own power | Skipped: native reuse | Wired |
| Overdrive (786) | Same native damage/Substitute-bypass table as Torch Song in `moves/flow`; sound flag retained | Skipped: existing handler reuse | Wired |
| Poltergeist (809) | Per-action held-item snapshot and pre-damage announcement in `moves/flow` | 15 cases passed: held/no item, Knock Off, Embargo, Magic Room, Kasib, Weakness Policy, Red Card, Protect, miss, immunity, Substitute, Parental Bond, Instruct/recheck | Implemented, focused-tested |
| Grassy Glide (803) | +1 priority in the existing resident field tracker; current terrain and user grounding | 9 cases passed: no/Grassy/Psychic terrain, removal, Air Balloon, Gravity, Queenly Majesty off/on, Dazzling | Implemented, focused-tested |
| Bleakwind Storm (846) | Shared rain-accuracy table in `moves/type`; corrected Flying type and native Speed drop | 9 singles cases passed: clear/sun hit and miss boundaries, rain, accuracy/evasion stages, Cloud Nine, Fly, Protect | Implemented, focused-tested |
| Sandsear Storm (848) | Same rain table; native burn data retained | Same 9 singles cases passed | Implemented, focused-tested |
| Wildbolt Storm (847) | Same rain table; native paralysis data retained | Same 9 singles cases passed | Implemented, focused-tested |
| Rising Voltage (804) | Target-grounded Electric Terrain doubling in `moves/terrain`; separate from ordinary user-grounded terrain power | 14 singles cases passed: terrain on/off/removal/replacement, either/both airborne, Air Balloon, Levitate, Gravity, Protect, Ground immunity, Substitute | Implemented, focused-tested |
| Scale Shot (799) | Once-per-sequence self-stat handler in `moves/stats`; native multi-hit flow, 90% accuracy | 17 cases passed: 2–5 hits, stat limits, early KO, Skill Link, Simple, Contrary, Sheer Force, Protect, miss, Wonder Guard, Fairy immunity, breaking Substitute mid-sequence | Implemented, focused-tested |
| Steel Roller (798) | Execution-time terrain prerequisite/removal in `moves/terrain`; existing terrain state/graphics-reset service | 14 cases passed: no/all four terrains, removal/replacement, repeated use, airborne user, KO, Protect, immunity, miss, Substitute; follow-up damage confirms removal | Implemented, focused-tested |
| Ceaseless Edge (845) | Shared native side-effect work in `moves/hazards`; per-hit Spikes, native three-layer cap | 14 cases passed: layers/cap, KO, Substitute, Sheer Force, Parental Bond, Protect, miss, immunity, Shield Dust, Instruct, contact-punishment KO | Implemented, focused-tested |
| Stone Axe (830) | Same table; native Stealth Rock one-layer cap | 12 cases passed covering the same interactions and rock cap | Implemented, focused-tested |
| Dire Claw (827) | Native secondary-chance dispatch + uniform status choice in `moves/type`; native condition work, modern Electric paralysis immunity | 116 cases passed: all 100 activation draws, three statuses, existing poison, Serene Grace, Sheer Force, Parental Bond, type/ability immunities, Shield Dust, Protect, Substitute, Safeguard, KO | Implemented, focused-tested |
| Take Heart (850) | Combined native Special Attack/Special Defense boosts and major-status cure in `moves/stats`; removed incorrect stat metadata | 24 cases passed: either/both caps, Simple, Contrary, status-only cures, repeat use, user Substitute, native Snatch and snatcher-only cure | Implemented, focused-tested |
| Aura Wheel (783) | Current species/form checks and type resolution in `moves/type`; native Speed metadata; tiny resident Transform success hook | 15 singles cases passed: both forms, Transform into either/away, non-Morpeko failure, Protect, miss, Ground immunity, Normalize, Electrify, Ion Deluge, Pixilate, Protean, Substitute | Implemented, focused-tested; Hunger Switch pending |
| Magic Powder (750) | Native type replacement in `moves/type`; clears added types; updated Overcoat in `abilities/defense` | 23 singles cases plus 3 follow-ups passed: single/dual/pure/added types, powder immunities, Mold Breaker, Gastro Acid, Embargo, Protect, Substitute, miss, Magic Coat and native switch-back restoration | Implemented, focused-tested; no new group |
| Obstruct (792) | Shared damage-only guard table and child-owned position event in `moves/guards`; Defense -2 | 15 singles cases plus next-turn cleanup passed: contact/noncontact, status, Feint, Hyper Drill, immunity, Long Reach, Pads/Embargo, Helmet/Rough Skin, Clear Body, Contrary | Implemented, focused-tested; existing BW2 success odds |
| Silk Trap (852) | Same table; native Speed -1 work | Same 15 cases plus next-turn cleanup passed | Implemented, focused-tested; existing BW2 success odds |
| Burning Bulwark (908) | Same table; native burn work | 15 cases plus next-turn cleanup passed; native Water Veil/Fire immunity replace the stat-prevention cases | Implemented, focused-tested; existing BW2 success odds |
| Hydro Steam (876) | Weather-stage exception in `moves/type`; native damage rounding preserved | 9 singles cases passed: clear/sun/rain, distinct defense/rounding, Cloud Nine, Air Lock, Drought, Normalize, Protean/STAB | Implemented, focused-tested; Utility Umbrella item dependency |
| Supercell Slam (916) | Native crash/Stomp reuse plus target-aware Minimize accuracy in `moves/flow` | 3 singles cases passed: ordinary accuracy, native Minimize/double damage and lowered user accuracy | Implemented, focused-tested; reused crash paths build-checked |
| Terrain Pulse (805) | Final type-parameter phase and grounded terrain doubling in `moves/terrain`; existing pulse flag/bonuses | 36 singles cases passed: all terrains, grounding/Gravity, removal/replacement, Normalize/-ates, Mega Launcher, Protean, Electrify/Ion Deluge, Protect, immunity, Substitute | Implemented, focused-tested; no new group |
| Triple Axel (813) | Native Triple Kick accuracy composition and per-action 20/40/60 power in `moves/flow`; corrected Disguise first-strike absorption | 24 singles cases and one next-turn follow-up passed: miss boundaries, Skill Link, Technician, Parental Bond, Protect, Wonder Guard, Substitute, contact costs/KO, Disguise, Mold Breaker and Instruct | Implemented, focused-tested; Loaded Dice pending |
| Steel Beam (796) | Existing Mind Blown attempt table in `moves/flow`; shared rounded-up maximum-HP cost | 15 singles cases and one Magic Guard follow-up passed: odd/even/low HP, KO, miss, protection, immunity, Substitute, Disguise, Rock Head, Magic Guard, Reckless, Gastro Acid and Parental Bond | Wired, focused-tested rounding/cost policy |
| Chloroblast (835) | Same cost callback, but native hit-only marker and effective Rock Head veto | Same 15 cases plus one follow-up passed; misses/protection/immunity do not charge, and absorbed hits do | Implemented, focused-tested |
| Clangorous Soul (775) | Shared direct HP-payment/stat transaction in `moves/stats`; documented 33%-floor policy, five +1 boosts | 21 singles cases and one repeat-action follow-up passed: HP boundaries/rounding, caps, Simple, Contrary, Substitute, Magic Guard, Rock Head, Sitrus, Snatch and Throat Chop selection rejection | Implemented, focused-tested |
| Fillet Away (868) | Same executor-local transaction; floor-half payment and Attack/Special Attack/Speed +2 | Same 21 cases plus one follow-up passed; remains selectable after Throat Chop | Implemented, focused-tested |

## Native data audited (51 moves)

No handler is added for these effects. Existing data is retained unless a
correction is noted. Emulator tests are skipped for this native-data batch.

| Family | Moves |
| --- | --- |
| Ordinary damage/accuracy | Behemoth Bash, Behemoth Blade, Branch Poke, False Surrender, Aqua Cutter, Kowtow Cleave, Astral Barrage, Glacial Lance |
| Stat changes | Apple Acid, Bitter Malice, Drum Beating, Esper Wing, Headlong Rush, Mystical Power, Psyshield Bash, Shelter, Skitter Smack, Spirit Break, Springtide Storm, Thunderous Kick, Triple Arrows, Victory Dance, Aqua Step, Armor Cannon, Lumina Crash, Pounce, Spicy Extract, Spin Out, Trailblaze, Breaking Swipe |
| Status/flinch | Freezing Glare, Mountain Gale, Strange Steam, Malignant Chain, Fiery Wrath |
| Fixed multi-hit | Dual Wingbeat, Triple Dive, Twin Beam, Tachyon Cutter |
| Drain/recoil | Bitter Blade, Wave Crash |
| Recharge | Eternabeam, Meteor Assault |
| Priority | Jet Punch |
| Forced-critical encoding | Wicked Blow, Surging Strikes, Flower Trick |
| User thaw/burn/bullet flags | Pyro Ball |
| Non-destructive protection bypass | Hyper Drill, Mighty Cleave |
| Attack drop / call-pool exclusion | Chilling Water |

Corrections: Mystical Power raises Special Attack rather than Speed; Thunderous
Kick is physical; Aqua Cutter is Water; Kowtow Cleave is physical with 85 power.
Native stage-6 forced-critical dispatch was source-inspected: it runs after
ability/side vetoes and before the ordinary critical-rank roll. No new critical
hook is added. No Dynamax-only bonus is claimed for the Behemoth moves.
Springtide's native Fairy/spread/30% Attack-drop/wind data is retained; it is
not registered with the rain helper. Native spread targeting is not newly
doubles-tested by this audit.
Astral Barrage, Glacial Lance, Breaking Swipe and Fiery Wrath retain the native
opponent-only spread target. Their packed records were checked against source
data; no extra table or doubles-specific logic was added. Glacial Lance uses
120 power, Breaking Swipe a guaranteed Attack drop, and Fiery Wrath 20% flinch.
Hyper Drill and Mighty Cleave omit `FLAG_BLOCKED_BY_PROTECT`. Source checks
confirmed native Protect and the supported custom guard/retaliation paths
respect that flag; neither move uses Feint's protection removal/counter reset.
Both retain contact, and Mighty Cleave retains slicing. Packed metadata is
checked; no extra registration/DLL or new guard/doubles emulator tests are added.
Chilling Water retains native guaranteed Attack -1 metadata. Clean-US W2/B2
Metronome routines enumerate only IDs 1–559; the final W2 pool-bound instructions
and packed Chilling Water record were checked. No extra exclusion hook or DLL
is needed with that pool. Expanding Metronome later requires an explicit
Chilling Water exclusion, rather than silently admitting it.

## Pending/partial

Scorching Sands' user-thaw flag is wired; its target-thaw path still needs
audit. The legacy `FLAG_DEFROSTS_TARGETS` name is misleading: native bit 10
allows a frozen user to thaw when using the move, rather than proving target
thaw. Torque copy/call restrictions remain pending. Other unlisted eligible
moves are pending; Hard/doubles entries
remain deferred. Remaining small families include protection and weather
rules. Utility Umbrella is not an implemented item; Hydro Steam's umbrella
exception remains an item dependency. No item ID or working item behavior is
invented for that dependency.

## Build and lifetime checks

White 2 uses the existing dynamic resolver for managed mechanics; exact vanilla
aliases remain resident. Black 2 retains the same static registration route.
No compatibility baselines are refreshed merely to obtain passing checks.

The registry has 101 managed moves, 59 managed abilities, 22 groups and 183 API
entries. Native aliases resolve getters from each game's own table without extra child allocations or
redundant getter imports. Stripped W2 packaging/export/import checks and the B2
static compatibility report passed; B2 behavioral tests were not run. The
stripped heap audit passed against the unchanged 164 KiB baseline: core 55,368
bytes (67,728 expanded); `moves/guards` 3,300, `moves/flow` 4,276, `moves/type` 3,540,
`moves/terrain` 4,148, `moves/hazards` 2,116 and `moves/stats` 3,756 fixed bytes;
`abilities/defense` 1,604 and `abilities/forms` 1,892 fixed bytes; conservative all-group free space 57,456
bytes including the audit's resident set and allocation overhead. This is a
static budget calculation, not an emulator stress/load-peak test.

Ruination testing exposed and fixed a pre-existing resident end-of-turn lookup
past the native 24-battler array. The event sentinel (31) remains unchanged.
The pre-change ROM was rejected as a negative control (1 damage, expected 117).
Ruination's emulator results precede the final native-ID alias consolidation;
that consolidation and the subsequent reused effects were build-checked only.

The old Barb Barrage/Hex build was rejected as a real negative control: burn
incorrectly doubled its power. Repeat-action tests retain completion before
end-of-turn flags reset, require correct PP per action, and recheck target
action state and already-applied damage. Normal BIOS IRQ/SWI execution is not
misclassified as an ARM abort. Fast outcome-oracle/deadline tests: 95 passed;
these do not substitute for each new handler's emulator suite.

Focused interaction checks exposed three missing ESDB owners: battle setup,
Parental Bond's damage-root call, and added-type effectiveness. Their existing
hooks are now wired to clean-US W2/B2 call sites; the effectiveness wrapper
preserves the native fifth argument (including temporary type changes).
Branch-hook verification rejects unresolved owners. Legacy `FULL_COPY`
aliases are outside this new branch-hook check. Core/child/B2-core packaging
uses a fresh temporary RPM and validates it before replacing the output:
an exit-zero RPMTool parser error can no longer validate an old DLL. The
11 focused hook/packaging/native-item/route-layout unit checks, two
Transform-hook CPU/translation checks and one compiled native-Overcoat
fallback guard passed.
The compiled shared protection-start policy also passed, covering all eleven
native/custom counter moves, non-protection history and wrong-owner callbacks.
The compiled damage-weather adapter/child callback passed 720 combinations
of weather, move/type, owner and module availability, without changing real
weather or the native damage context's ID/type/owner. These are host checks,
not emulator fault-injection or lifecycle coverage.
The compiled final-parameter dispatcher and Terrain Pulse callbacks passed
1,920 combinations of move, terrain, grounding, ability, module availability,
Electrify/Ion Deluge and owner. The same context supplies the final parameters;
native conversions stay unchanged without a matching child callback.

Fickle Beam interaction testing also exposed Parental Bond's rewrite-once
conflict: its second-hit base-power rewrite was rejected after the move's
rewrite. The ability now applies the same half-power rule through the later
power-ratio stage. This is not a switch to modern quarter-damage rules.

Prior delivery: `White2Upgrade-gen89-batch2-20261003-234000.nds`.
SHA-256: `50da1a7a6e91f447ab4ea0290a36e955ed03e14acc1e166da70af1061976f8bb`.
All nine new custom-handler suites were rerun against this exact final build:
151 cases passed. Ruination's earlier native-reuse tests are not included in
that total. Reused effects, including Double Shock, were build-checked only.

Prior delivery: `White2Upgrade-gen89-batch3-20261004.nds`.
SHA-256: `0e7ceb1513be66b365830d972ddf74c3034ebb0304b11a4ec8c6b3e28295806f`.
Poltergeist and Grassy Glide were rerun on this exact final build: 24 cases
passed. The prior 151-case batch was not rerun on this build. Native message
construction/arguments were checked, not visual rendering. Full teardown,
load-peak stress, doubles, Mega, nonbattle and B2 behavioral suites were not run.

Grassy Glide's first child-only implementation failed the action-order test:
native priority queries precede temporary move registration. Its adjustment
now lives in the existing resident field tracker, using the event's actual
attacker rather than its sentinel owner. No new module or raw hook is added.
The terrain getter uses the type's existing null-on-reset/removal invariant.
Terrain setup, removal and replacement were exercised by the focused suite.

Poltergeist's Knock Off setup exposed a pre-existing item-hook ABI bug: native
callers pass species, not a BattleMon pointer. The replacement now preserves
native Giratina/Arceus/Genesect item protection without calling an alias of
its own patched address, then checks every supported Mega stone. Host predicate
and ABI guards passed; this is not full Mega or Symbiosis battle coverage.
Shared-ROM fixture construction now rejects conflicting Personal ability-slot
edits, preventing one trainer variant from silently changing another.

Prior delivery: `White2Upgrade-gen89-batch4-20261004.nds`.
SHA-256: `c9a843d8dc3a27f4164ff7397f8636baa5c6c6594e4ea733b22272cba49eaeaf`.
All three storm suites passed on this exact build: 27 singles cases. Their
accuracy draws are observed at the native RNG return, separately from secondary
rolls. The initial Fly fixture incorrectly tested after landing; it was fixed
to attack during the next native charge, without changing the move handler.
The prior move suites were not rerun on this build. Native secondary/spread
effects, visual behavior, lifecycle stress and full W2/B2 regressions are not
claimed. No new module was added. Private route records now use four bytes;
host checks enumerate every key, preserve 16-bit IDs/public ABI and reject an
index capacity that would truncate the byte-sized module field.

Prior delivery: `White2Upgrade-gen89-batch5-20261004.nds`.
SHA-256: `f80e8aed185cbd555a673007fe8bc2aa5814c3bf74ea6515534ba6758aeadfa4`.
Rising Voltage and Scale Shot passed on this exact build: 31 singles cases.
Rising Voltage observes native floating results instead of inferring them from
items alone. Scale Shot verifies unchanged user stages at every strike and one
post-sequence change, and traces separate HP/Substitute damage without spillover.
Its old per-hit self-stat metadata was removed. Native hit-count selection is
reused, not replaced; four controlled draws cover 2–5 hits, not a statistical
sample. Loaded Dice support is not claimed. Earlier suites were not rerun on
this build; full W2/B2, lifecycle and visual regressions remain unverified.

Prior delivery: `White2Upgrade-gen89-batch6-20261004.nds`.
SHA-256: `2866d922d5455c3fb15336f01efc23e796a7635af255e360b00f274eddd8dd22`.
Steel Roller, Ceaseless Edge and Stone Axe passed on this exact build: 40 singles
cases. The pre-handler ROM failed the native hazard-count assertion despite
dealing ordinary damage, confirming the negative control. Hazard tests observe
native side records without writing them; native layer caps and permanent
conditions are checked. Sheer Force gains its native boost but suppresses the
hazard; each Parental Bond strike can add a layer. Steel Roller checks native
terrain-end message construction and follow-up execution, not visual rendering.
No new group, hook or shared state was added. Earlier suites were not rerun on
this build; full W2/B2, lifecycle and visual regressions remain unverified.

Prior delivery: `White2Upgrade-gen89-batch7-20261004.nds`.
SHA-256: `f2a39931e58f9858b24d40c62ef0e3bc610ef812697b02d8da80159a688e8f01`.
Dire Claw passed all 116 singles cases on this exact build. An older core/child
build with matching move metadata dealt damage but failed the secondary-status
assertion, providing a real negative control. Activation precedes one uniform
choice; immunities do not reroll. RNG observations are scoped to the hit-reaction
handler window, excluding the AI's later full-paralysis check. Native sleep
duration draws are distinguished from status selection. This enumerates
controlled draws, not stochastic frequencies. No new module, hook or shared
state was added; the core's fixed size is unchanged. Earlier suites, rainbow
in doubles, full W2/B2, lifecycle and visual regressions were not run.

Prior delivery: `White2Upgrade-gen89-batch8-20261004.nds`.
SHA-256: `a46659a52886240247c89465b34766c762441f3aea9e452be90406c4eb41d0bc`.
Take Heart passed all 24 singles cases on this exact build, including an
additional repeated execution. The older core/children with matching final
metadata failed the boost assertion. Native event/work-result observation
checks the executing owner and combined success, not merely unchanged stats
on failed attempts. Orbs and Thunder Wave establish statuses through normal
battle actions; Snatch cures only its executing user, including at stat caps.
No new DLL, hook or shared state was added; the core's fixed size is unchanged.
Earlier suites, sleeping/frozen-user execution, doubles, full W2/B2, lifecycle
and visual regressions were not run on this build.

Prior delivery: `White2Upgrade-gen89-batch9-20261004-2.nds`.
SHA-256: `e327050a6e1c5d39ef17a64349590a03acb14bf7923d7b077a94518dbac9e00d`.
Aura Wheel passed all 15 singles cases on this exact build. The old build
damaged a target when a non-Morpeko used the move, and the same oracle rejected
it. Native Transform runs normally; the harness now reads active surface PP
separately from preserved original PP. The resident hook is 12 bytes of code,
adds no allocation/global state, and only fills the unused species word on
successful Transform. Its exact W2/B2 success sites were checked against the
clean US binaries; B2's static report has 171 hooks, 230 imports and 48 raw
anchors. No new child group is added. Earlier move suites, automatic Hunger
Switch, actual Mimic/Imposter, full W2/B2, lifecycle and visual regressions
were not run on this build.

Prior delivery: `White2Upgrade-gen89-batch10-20261004-2.nds`.
SHA-256: `e3f81c77954d38a0fec11ab648fe6d5111fb02870e91333bd3489ea50dee0794`.
Magic Powder passed all 23 singles cases and three follow-ups on this exact
build. An older ROM with matching move data failed the type-change oracle.
Native switch-in events track the same returning party battler, including
cached ability events. Swift fails against added Ghost before replacement and
hits afterward. The explicit missing-child Overcoat weather fallback is
host-checked, not emulator fault-injected. No new module, hook or shared state
is added. Earlier suites, Tera, doubles, full W2/B2, lifecycle and visual
regressions were not run on this build.

Prior delivery: `White2Upgrade-gen89-batch11-20261004-3.nds`.
SHA-256: `ca5dc975273c77dcc036821ab3bee31e3617e7f85fb384f28785d42e23575652`.
Obstruct, Silk Trap and Burning Bulwark each passed all 15 singles cases and
one follow-up on this exact ROM. The older no-handler ROM failed the protection
oracle. A targeted fix defers only genuinely blocked type immunity until the
protection pass; immune Hyper Drill stays immune and cannot retaliate. All
retaliation callbacks remain child-owned; no module group or shared mutable
state is added. King’s Shield reuses the corrected damage-only path and retains
Attack -2, but was source/build-checked rather than separately emulator-tested.
Native Protect-family chaining recognizes the new IDs in both directions;
BW2's existing consecutive-use odds are intentionally retained. Modern one-third
odds, Mirror Armor and Unseen Fist remain generation/ability dependencies.
B2's static report has 172 hooks, 229 imports and 48 raw anchors. Prior suites,
full W2/B2 behavior, switching/fainting/doubles, lifecycle and visual regressions
were not run on this build.

Prior delivery: `White2Upgrade-gen89-batch12-20261004-2.nds`.
SHA-256: `8a3b778b5b46e3935d67220a482dd9ed5f903163eb5af4e7e93d52a1218b960d`.
Hydro Steam's nine cases and Supercell Slam's three cases passed on this exact
ROM; both suites reject the prior build as a real negative control. The native
crash/Stomp handlers are composed through a narrow resident getter; all new
mechanic callbacks remain file-local in the existing two groups. The new weather
hook is verified at matching clean-US W2/B2 call sites. B2's static report has
173 hooks, 229 imports and 48 raw anchors. All 92 fast harness tests and 16
focused host checks passed. Stripped packaging, registry-only staging and the
unchanged heap audit passed; conservative all-group free space is 58,576 bytes.
The core remains 8,196 bytes below its monolithic baseline (only four bytes
above the 8 KiB threshold), so future resident additions require more savings.
Utility Umbrella, prior emulator suites, full W2/B2 behavior, doubles, lifecycle
stress and visual regressions were not tested on this build. Hard/doubles moves
remain deferred; this is incremental coverage, not completion of the reference.

Prior delivery: `White2Upgrade-gen89-batch13-20261004-2.nds`.
SHA-256: `4bad13f031f488841af0916d5207295b895ec83867cad57722135e9f5f1e7f7c`.
Terrain Pulse passed its complete 36-case singles suite on this exact ROM;
the prior build failed its resolved-type oracle. The initial implementation
failed Normalize ordering; the final parameter phase fixes that without a new
raw hook, group, ABI layout or shared state. Protect/Substitute fixtures now
use entry-time Surge instead of repeated protection or pre-checkpoint dolls.
W2 packaging/staging, B2 static compatibility, 95 fast harness tests and 17
focused host checks passed. Conservative all-group free space is 58,184 bytes;
core savings remain 8,196 bytes. Chilling Water is source/build-checked only.
Prior emulator suites, full W2/B2 behavior, doubles, lifecycle/stress and visual
regressions were not run on this build. Other eligible moves remain pending.

Prior delivery: `White2Upgrade-gen89-batch14-20261004-2.nds`.
SHA-256: `ab127a0ef0cd56f2e303fb2d2d5a656f6468832070d190c8650714edfc0359cb`.
Triple Axel passed its complete 24-case singles suite and one next-turn reset
follow-up on this exact ROM. The prior build failed the second-strike power
oracle (11 damage instead of 22). Disguise previously removed the defender
before the multi-hit loop; it now absorbs one strike and changes form only
during real execution. Fixed/single damage, miss, Substitute and Mold Breaker
cases passed. The first Substitute fixture was too slow to create its doll;
the corrected case requires a genuine native doll before the first strike.
All 99 fast harness tests and 29 repository host checks passed. Compiled checks
cover repeated normal/fixed damage estimates without form/HP mutations,
action-owned scratch reset, path reconstruction and buffer canaries. W2 stripped
packaging/staging and B2 static compatibility passed (174 hooks, 229 imports,
48 raw anchors), without refreshing baselines. Prefix deduplication offsets
the new resident adapter: core savings are 8,348 bytes and conservative
all-group free space is 58,096 bytes. No new module group was added. Prior
emulator suites, full W2/B2 behavior, Loaded Dice, doubles, lifecycle/load-peak
stress and visual regressions were not run. Other eligible moves remain pending.

Prior delivery: `White2Upgrade-gen89-batch15-20261004-1.nds`.
SHA-256: `1ac49d3514300efb038a1dc3161994d5671b145279e31ca5cf07fdd59ecddb81`.
Steel Beam and Chloroblast each passed their complete 15-case singles suite
and one Magic Guard repeat-action check on this exact ROM. Both pre-handler
builds fail the HP-cost oracle. The shared callback corrects Mind Blown's
odd-HP rounding as well; that existing move has compiled/source checks, not a
new emulator suite. The compiled callbacks cover 3,078 HP/move/ability
combinations, owner guards, unmarked actions, AI hit estimates, scratch reset
and duplicate sequence-end notifications. Native no-target rejection is
source/host-checked, not emulator-tested. A fatal-cost experiment reached
normal whiteout, but the runner cannot certify terminal battle completion;
its passing low-HP cases stay nonterminal rather than weakening that oracle.
All 102 fast harness tests and 30 repository host checks passed. W2 stripped
packaging/staging, B2 static compatibility (174 hooks, 229 imports, 48 raw
anchors) and the unchanged heap baseline passed. Core savings are 8,332 bytes;
conservative all-group free space is 57,888 bytes. No new module group, core
hook or shared storage was added. Prior emulator suites, full W2/B2 behavior,
doubles, terminal battle/lifecycle/load-peak and visual regressions were not
run. Other eligible moves remain pending.

Current delivery: `White2Upgrade-gen89-batch16-20261004-2.nds`.
SHA-256: `d1f2c49fc0ebe7342bf9fb26e1e95aaf07de513de0f7110039bcbb98996b2443`.
Clangorous Soul and Fillet Away each passed their complete 21-case singles
suite plus one repeat-action follow-up on this exact ROM. The pre-handler
ROM fails both native effect-work oracles. Native direct payment, queued
stat work and delayed item reaction keep Magic Guard/Rock Head from canceling
the cost and make Snatch charge the actual executor. Compiled checks verify
both payment formulas across all 65,535 native maximum-HP values, work layouts,
effective-direction eligibility, owner/no-target/fainted guards and ordering.
Soul's 33%-floor rounding is an explicit reviewed integration policy, not a
claim of extracting the Sword/Shield game binary's formula.

The Throat Chop case for Soul verifies native move-selection rejection with
unchanged PP, action history, HP and stages and no effect execution; it is not
a completed-action claim. The command client's battler copy is matched by
native identity rather than the server allocation address. Fillet succeeds;
its payment is checked before the later opponent attack, whose damage and PP
are independently certified. Initial harness assumptions incorrectly waited
for a rejected action and conflated later attack damage with payment; the
final tests fix those oracles without writing expected outcomes or relaxing
completion checks.

All 108 fast harness tests and 31 repository host checks passed. Exact packed
core/22-child bytes and move metadata, registry-only staging, stripped RPM
linkage/export checks, B2 static compatibility (174 hooks, 229 imports, 48 raw
anchors) and the unchanged heap baseline passed. Core size remains 55,368
fixed bytes with 8,332 bytes saved; `moves/stats` is 3,756 fixed bytes and
conservative all-group free space is 57,456 bytes. No new group, resident hook,
shared state or compiler-runtime import is added. Prior emulator suites,
Dancer, full W2/B2 behavior, doubles, lifecycle/load-peak stress and visual
regressions were not run. Work is paused after this shared family at the
user's request; other eligible moves remain pending.

Generated test ROMs are temporary and deleted by default. Fixture saves and
small diagnostic reports are retained, and generated test output is Git-ignored.
