# Gen 8/9 move-handler progress

Scope: the [reference](gen8-gen9-move-handler-reference.md), easiest first.
The Hard rollout is in progress; the non-Hard doubles rollout is complete.
Inventory: 159 reference entries; 153 wired/implemented, 4 Hard pending/blocked,
0 non-Hard doubles-specific deferred, and 2 blocked by missing specification/data.
This is move-handler coverage, not a claim of every dependent ability/item system.
Animations are not changed.

Testing policy: reused/native-data effects are wired and build-checked without
per-move emulator tests, as requested. New custom logic still needs focused
tests. "Wired" below is not a claim of new emulator or full regression coverage.

| Move | Implementation | Focused tests | Status |
| --- | --- | --- | --- |
| Last Respects (854) | Existing `moves/flow` reads a resident per-trainer faint-event counter; native committed-faint hook and party-membership ownership; cap 5,050 | 5 doubles cases: fresh battle, elapsed turns, allied self-KO, opposing self-KO and one faint on each side; exact power/HP/PP; compiled caps, simulation, lifetime, ownership and clean-US W2/B2 guards | Implemented for non-multi battles; multi-trainer battles explicitly fail |
| Revival Blessing (863) | Existing `moves/flow` starts a resident adapter transaction; native fainted-party chooser and authoritative revival work, with no item consumption or user switch | 9 singles/doubles cases: either fainted choice, living-choice retry, cancel, odd/even half HP, no fainted member, Heal Block, native AI revival and a doubles revive/faint sequence proving 150-power Last Respects; additionally local owned-party revival in the Rage Fist multi suite; compiled native layouts, transaction bounds, ownership, reset and Sketch restrictions | Implemented, focused-tested; actual revived-Mega, broader multi/network and replay coverage pending |
| Dragon Darts (751) | Existing `moves/flow` expands unredirected doubles targets, then uses native one-pass eligibility filtering; resident hit-count/spread adapters preserve per-foe Pressure and called-Prankster origin | 27 doubles cases: two full-power hits, ally selection, either/both type-immune/protected/airborne foes, either accuracy miss, selected/other/immune Follow Me centers, Pressure, Wonder Guard/Mold Breaker, Parental Bond, Wide Guard, Substitute, direct and Rest/Sleep Talk-called Prankster; exact HP/doll/PP, target counts and accuracy-roll counts plus 6 compiled/native ABI checks | Implemented, focused doubles-tested; Ice Face, Ally Switch, triples and multi-battle coverage pending |
| Shed Tail (880) | Existing `moves/flow` pays half-ceil HP, creates the native quarter-HP Substitute, then uses native replacement selection; resident switch-out filter transfers only the doll to both server and client | 19 singles cases: odd/even boundaries, low HP, existing doll, no bench, Sitrus ordering, trapping, hazards, actual incoming damage to the doll, excluded stages/Focus Energy/Gastro Acid/Aqua Ring/Power Trick, and an ordinary Baton Pass control; compiled preflight, simulation, two-copy lifetime and clean-US W2/B2 checks | Implemented, focused-tested; multi-battle ownership and revived-Mega coverage pending |
| Chilly Reception (881) | Existing `moves/terrain` snow transaction followed by native replacement selection; resident once-per-turn preparation message only for direct selection | 9 singles cases: ordinary/native choice, existing snow, Rain replacement, Icy Rock, Mean Look bypass, entry hazards, Sleep Talk without early cue, no bench and both effects unavailable; compiled callback and resident turn-boundary guards | Implemented, focused-tested |
| Snowscape (883) | Existing `moves/terrain` queue plus resident logical snow; native cold-weather transport preserves distinct Hail, duration and delayed display ownership | 19 singles cases: no chip, Ice physical Defense only, 5/8-turn expiry, repeat failure, Hail/Rain replacement, restored hail chip, Ice Body, Snow Cloak accuracy boundary, Slush Rush, Cloud Nine/Air Lock, Veil, Weather Ball and Synthesis; compiled lifecycle/transport and clean-US W2/B2 call checks | Implemented, focused-tested; native hail graphics reused, no new assets |
| Shell Side Arm (801) | Final-target damage forecast in existing `moves/type`; per-action category/contact cache and separate retaliation history; no shared move-data mutation | 20 singles and 2 doubles cases: raw/staged stats, rounding ties, Wonder Room, poison, excluded item/ability modifiers, Helmet/Rough Skin/Fluffy, Counter/Mirror Coat and Follow Me's final target; compiled forecast, simulation and native ABI checks | Implemented, focused-tested; broader AI/multi-battle coverage pending |
| Court Change (756) | Transactional native side-factor re-registration in existing `moves/screens`; preserves duration/layers, swaps custom Web/Veil ownership, excludes current-turn guards | 16 doubles cases: empty sides, Reflect/Light Screen and Light Clay durations, hazard layers, Mist/Safeguard/Tailwind/Lucky Chant, Web/Veil ownership, actual damage and screen non-stacking; compiled asymmetric duration/pledge/guard checks | Implemented, focused doubles-tested; future entry/expiry and multi-battle coverage pending |
| Rage Fist (889) | Battle-long resident per-party direct-hit counter; existing `moves/flow` power callback; narrow Disguise/Transform services | 12 existing doubles cases plus 9 native multi cases: 0/1/2/6/7 hits/cap, AI partner isolation, fresh replacement history, switch-back persistence, and faint/revival/switch-back persistence; reversed revival → fresh-battle rollback check; compiled caps/simulation/self-hit/lifetime guards | Implemented, focused doubles and local multi-tested; networking and other multi configurations unverified |
| Teatime (752) | Snapshot eligible native-filtered recipients, then synchronous native consumption/temporary berry work in `moves/flow` | 16 doubles cases: four mixed berries, full HP/no status, no holders, Unnerve, Magic Room, Embargo, Substitute/hiding, Cheek Pouch, Symbiosis, Ion Deluge/Electrify, three absorbers, retained absorber berry and Ground holder; compiled bounds/duplicate/transaction guards | Implemented, focused doubles-tested |
| Doodle (867) | Atomic active-ally ability transaction in existing `moves/ability`; native ability work preserves party truth and re-registers changed abilities | 10 doubles cases: two/one/no changes, protected user/partner/target, Receiver asymmetry, custom Fur Coat registration, repeat no-op; compiled restriction/capacity checks and old-ROM negative control | Implemented, focused doubles-tested |
| Decorate (777) | Native target boosts in `moves/stats`; hiding filter and narrow Crafty Shield correction | 9 doubles cases: boosts/caps, Simple, Contrary, Protect, Substitute, Fly, Crafty Shield, Magic Bounce | Implemented, focused doubles-tested |
| Expanding Force (797) | Execution-time grounded Psychic Terrain power/target resolution in `moves/terrain` | 3 doubles cases: ordinary single target, grounded terrain spread, Air Balloon; independent terrain/spread damage oracle | Implemented, focused doubles-tested |
| Snipe Shot (745) | Resident redirection query with scoped `moves/flow` veto; target immunities remain native | 4 doubles cases: Follow Me with Water Gun control, remote Storm Drain, selected Water Absorb; critical stage observed | Implemented, focused doubles-tested |
| Jungle Healing (816), Lunar Blessing (849) | Shared active-ally quarter-heal/cure work in `moves/flow`; user-target metadata avoids native empty ally target lists | 8 doubles cases each: both allies, full/capped HP, actual burn/poison cures, status-only benefit, Substitute, hiding, ally Heal Block | Implemented, focused doubles-tested |
| Life Dew (791) | Same active-ally helper, without curing; native recipient Water immunity dispatch | 10 doubles cases: healing/caps, Substitute, hiding, Water Absorb, Dry Skin, Storm Drain, statuses remain with residual damage, ally Heal Block | Implemented, focused doubles-tested |
| Dragon Cheer (913) | `moves/stats` applies a fixed resident critical bonus using native Focus Energy exclusion; narrow Psych Up/Transform copy service | 10 doubles cases plus two attack follow-ups: Dragon/non-Dragon ranks, repeat/Focus Energy, Protect/Substitute/hiding, Soak type change, Psych Up and Transform copies | Implemented, focused doubles-tested |
| Make It Rain (874) | `moves/flow` queues one native self drop per action and delegates successful-hit coins to Pay Day; SV metadata | 5 doubles cases: two hits, one/both protected, Contrary, Simple; native bonus pool and independent spread damage checked | Implemented, focused doubles-tested |
| Matcha Gotcha (902) | `moves/flow` records actual hit damage; queues Ooze reversals before ordinary native drains; scoped native thaw adapter | 9 doubles cases: both drains, burn chance boundary, Big Root, either Ooze target, actual frozen user/targets, Substitute | Implemented, focused doubles-tested |
| Mortal Spin (866) | Existing expanded Rapid Spin cleanup in `moves/hazards`, guarded against fainted/departed user; native poison metadata | 7 doubles cases: both targets, Steel immunity, three native hazards, native Bind/Leech Seed cleanup; compiled faint guard | Implemented, focused doubles-tested |
| Coaching (811) | Ally-only selector/filter and recipient-owned native boost work in existing `moves/stats`; explicit hiding/Sky Drop exclusion; no new DLL or resident hook | 13 headless cases passed: doubles ally only, both/one capped, Simple/clamping, Contrary/floor/ceiling, Protect, Substitute, Crafty Shield, Fly exclusion, singles no-ally failure; all four battlers' commands/PP/stages and next turn checked | Implemented, focused doubles-tested |
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
| Ice Spinner (861) | Hit marker and post-reaction terrain removal in `moves/terrain`; living/on-field user required | 15 singles cases plus follow-up passed: all terrains, no terrain, airborne, KO, protection, immunity, miss, Substitute, contact KO, Red Card and Life Orb KO | Implemented, focused-tested |
| Body Press (776) | Defense selector in `moves/stats`; resident native attack-stat and critical-stage adapters | 12 singles cases passed: distinct Attack/Defense, either stat's stages, critical positive/negative stages, Huge Power, Fur Coat, Choice Band, Eviolite, burn and Unaware | Implemented, focused-tested |
| Tidy Up (882) | Both sides' hazards and active Substitutes cleared in `moves/hazards`; native Attack/Speed boosts, not Snatchable | 14 singles cases plus two follow-ups passed: caps, either/both dolls, all hazards/Web reapplication, Simple, Contrary, screens, terrain and Snatch | Implemented, focused-tested; no doubles-format claim |
| Lash Out (808) | Applied-stat history and same-turn doubling in `moves/flow` | 11 cases passed: actual/prevented/capped drops, Contrary, entry Intimidate, turn reset, Haze/Topsy-Turvy and Gooey/Instruct | Implemented, focused-tested |
| Burning Jealousy (807) | Pre-damage raised-stat snapshot; native burn work in `moves/flow` | 12 singles cases passed: current/earlier turn, caps, Weakness Policy ordering, Contrary, Sheer Force, Water Veil, Shield Dust and Substitute | Implemented, focused-tested |
| Alluring Voice (914) | Same eligibility family; native confusion and sound/Substitute routing | 12 cases passed, including Own Tempo, confusion veto, Sheer Force and sound bypass | Implemented, focused-tested |
| Eerie Spell (826) | Native last-used move/active-slot PP drain in `moves/flow` | 10 cases passed: PP boundaries, no history, Struggle, KO, Shield Dust, Sheer Force and Substitute | Implemented, focused-tested |
| Dynamax Cannon (744) | Ordinary damage data; resident Encore exclusion | Native damage tests skipped; exclusion and ordinary Encore control passed | Wired, restriction tested; no Dynamax system |
| Meteor Beam (800) | Native charge flow; confirmed charge-phase Special Attack boost in `moves/terrain` | 10 cases passed: two-turn/Herb, Magic Room, weather, Cloud Nine, caps, Simple, Contrary and Sheer Force | Implemented, focused-tested |
| Electro Shot (905) | Same boost flow; effective-rain charge skip | 11 cases passed: rain/Herb priority, sun, Cloud Nine, Magic Room, caps, Simple, Contrary and Sheer Force | Implemented, focused-tested |
| Upper Hand (918) | Pending damaging-action priority bracket in `moves/flow`; native flinch data | 10 cases passed: priority 0–4, priority status, already-acted target, Inner Focus, Shield Dust and Sheer Force | Implemented, focused-tested |
| Blazing Torque, Wicked Torque, Noxious Torque, Combat Torque, Magical Torque (896–900) | Native damage/status; shared resident copy/call restrictions | All 40 exclusion cases passed for Encore, Mimic, Sketch, Me First, Copycat, Instruct, Sleep Talk and Assist | Wired, restrictions tested |
| Scorching Sands (815) | Existing burn/user-thaw data; native target-thaw adapter with unchanged Ground damage context | Native effects not redundantly emulator-tested; compiled host adapter checks passed | Wired, source/build/host checked |
| Misty Explosion (802) | Native Explosion transaction; grounded Misty Terrain boost and expanded Damp predicate | All 11 singles cases passed: terrain/removal/replacement, airborne/Gravity, Damp/Mold Breaker, Protect, Magic Guard and Parental Bond | Implemented, focused-tested |
| Tar Shot (749) | One non-stacking Fire-effectiveness flag; native Speed -1 in `moves/type` | All 15 cases passed: repeat/cap/Clear Body/Contrary, type changes/added types, 16× weakness, resistance, Wonder Guard, Flash Fire, Substitute and switch cleanup | Implemented, focused-tested |
| Raging Bull (873) | Base type before ability/position conversions; native Brick Break and existing Veil removal in `moves/screens` | 15 singles cases passed across focused runs: four Tauros forms, non-Tauros, Normalize/-ates, Electrify/Ion Deluge, all screens, Protect and immunity | Implemented, focused-tested |
| Snap Trap (779), Thunder Cage (819) | Native Bind aliases; scoped 1/8 residual damage or 1/6 with Binding Band, safe overlay veneer | 8 cases each passed: activation, residual fractions, ordinary Bind control, Shield Dust, Sheer Force, Protect and Substitute | Implemented, focused-tested |
| No Retreat (748) | Five native stat boosts and source-dependent self-trap in `moves/trapping`; resident once-per-occupant flag | 7 cases passed: cap, repeat, Simple, Contrary, Ghost and pre-existing trap | Implemented, focused-tested |
| Jaw Lock (746) | Real-hit reciprocal native traps in `moves/trapping` | 8 cases passed: both Ghost exemptions, prior trap, Shield Dust, Sheer Force, Protect and Substitute | Implemented, focused-tested |
| Octolock (753) | Core-owned source-linked state; field residual in `moves/trapping` | 10 cases passed: repeated ticks, floor, reapplication, Clear Body, Simple, Contrary, Ghost, protection/Substitute and source exit | Implemented, focused-tested |
| Salt Cure (864) | Native secondary eligibility; resident occupant state and current-type residual in `moves/volatile` | 10 cases passed: ordinary/Water/Steel fractions, reapplication, Shield Dust, Sheer Force, Magic Guard, Protect/Substitute and source exit | Implemented, focused-tested |
| Syrup Bomb (903) | Same lifetime service; three non-refreshing, source-linked Speed drops | 11 cases passed: exact duration, reapplication, Clear Body, Simple, Contrary, Shield Dust, Sheer Force, Bulletproof, Protect/Substitute and source exit | Implemented, focused-tested |
| Stuff Cheeks (747) | Forced native berry consumption/effect work plus Defense +2 in `moves/flow`; resident selection gate | 15 cases passed: full HP, healing once, cap/no berry, Simple, Contrary, Recycle, Belch, Cheek Pouch, Unnerve, Magic Room, Embargo and execution-time removal | Implemented, focused-tested |
| Corrosive Gas (810) | Native item-destruction work in `moves/flow`; no consumption/Recycle bookkeeping | 13 singles cases passed: Sticky Hold/Mold Breaker, protected species items/Mega stones, unrelated holders, no item, Magic Room, Recycle, Protect/Substitute | Implemented, focused-tested; no doubles claim |
| Glaive Rush (862) | Resident next-action window; `moves/volatile` activation uses native attacker ownership | 9 cases passed: either speed order, Protect, accuracy/evasion, immunity, fixed damage/OHKO, NPC ownership and Truant | Implemented, focused-tested |
| Blood Moon (901), Gigaton Hammer (893) | Resident successful selected-move history and selection-only rejection; no child allocation | 9 cases each passed: repeat rejection, intervening move, miss/Protect, Instruct, Sleep Talk, Choice lock, no alternatives and faster Encore/Struggle | Implemented, focused-tested |
| Psychic Noise (917) | Native damage + 100% two-turn Heal Block data; existing sound/Substitute, Aroma Veil and healing gates | Packed record and native overwrite rejection audited; no new DLL or redundant emulator suite | Wired, native-data checked |

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

## Deferred and dependencies

Hard pending (1): Population Bomb. Its
ordinary and Skill Link branches passed 16 focused cases, but Loaded Dice's
missing item system awaits a scope decision. It is not counted complete.

Hard blocked by explicit scope choice (3): Tera Blast, Tera Starstorm, Order Up.
The missing Tera/Stellar and Commander systems are outside this rollout.

After this rollout, audit existing Gen 6/7 custom move logic against the linked
Bulbapedia move descriptions and add focused headless tests. Exclude plain
metadata effects and handlers that merely copy/reuse a Gen 5-or-earlier native
handler. Report generation-specific rules and unverified dependencies explicitly.

Incomplete specification/data (2):

- Ivy Cudgel: mask item IDs and working Ogerpon/mask data are absent. Its
  critical-stage data is not counted as a completed mask-dependent handler.
- Nihil Light: no assigned move ID or approved conventional turn-based
  adaptation. The move-range sentinel is not repurposed.

Related systems not implemented by this batch: Hunger Switch (Aura Wheel),
Utility Umbrella (Hydro Steam), Loaded Dice (Triple Axel), Dynamax and Tera.
Existing BW2 protection success odds remain. The later Gen 6/7 ability audit
replaces Parental Bond's old half-power rule with Gen 7 quarter final damage
and removes Disguise's modern HP cost; see the
[ability/item audit](gen6-gen7-ability-item-audit.md).
No animation, learnset, new item or global generation-rules migration is claimed.

## Verification and build

Focused custom-handler tests run with the sibling Pokeweb-Serverless headless
runner. They observe native PP, completion/history, events and actual HP/stages;
RNG control changes draws, not calculated outcomes. Native data and exact reuse
skip redundant emulator tests as requested. Generated output is ignored;
fixture ROMs and snapshots are cleaned up, while fixture saves are retained.

```sh
# Run from the sibling Pokeweb-Serverless repository:
python3 scripts/test-move-handlers.py --move octolock --rom <relative-ROM-path>
python3 scripts/test-move-handlers.py --move blood-moon --rom <relative-ROM-path>
python3 scripts/test-move-handlers.py --move coaching --rom <relative-ROM-path>
python3 scripts/test-move-handlers.py --move dragon-darts --rom <relative-ROM-path>
python3 scripts/test-move-handlers.py --move last-respects --rom <relative-ROM-path>
python3 scripts/test-move-handlers.py --move revival-blessing --rom <relative-ROM-path>
# Run from this repository:
python3 -m unittest discover -s tools/tests -p 'test_*.py'
ninja -C build-stripped src/black2upgrade-compatibility.json src/white2upgrade-battle-heap-audit.json
```

The sibling runner's `runtime/battle-harness/INTERACTION-TESTS.md` describes
fixture authoring and CLI use. Detailed per-case reports remain in its ignored
`work/move-handlers/` output. Cases in the table were validated across successive
builds; all earlier suites were not rerun on the final ROM.

The current registry contains 145 managed moves, 59 abilities, 13 items,
229 API entries and 22 children (capacity 24). No new child group was required.
W2 remains dynamically resolved; B2 links the same groups statically.
Stripped RPM/export/import/linkage/staging checks and the B2 compatibility
report pass (199 hooks, 256 imports, 50 raw anchors). No B2 baseline was refreshed.

Latest stripped heap audit: core 65,128 fixed / 80,336 expanded bytes.
The no-custom resident set uses 74,832 bytes, saving 28,468 against the unchanged
103,300-byte monolithic resident baseline. The largest one-group case saves
19,288 bytes. Conservative all-group use is 131,920 bytes, leaving 36,016 of
the patched 164 KiB heap, including the audit's residents and allocation overhead.
These are static budgets, not observed peak allocations or load-time proof.

Focused tests also repaired shared defects: unmapped battle/Parental Bond/type
hooks; native item-protection ABI; missing W2 resident consumption bookkeeping;
source-trap continuation encoding; sound/Substitute classification; rewrite
ordering and native event ownership. The linkage check now requires resident
item-consumption and held-item-change hooks. New compiled host guards preserve
these native context, lifetime, route and budget contracts.

Broader doubles, Mega, vanilla/nonbattle, overlay/PWAN and B2 behavioral regressions,
missing-module fault injection, repeated-battle unload/reload stress and peak-load
heap acceptance were not run by this batch. Build/host checks do not substitute
for those broader suites.

Latest delivery: `White2Upgrade-gen89-batch40-20261005.nds`, copied to the outer
`Repos/` directory without replacing existing ROMs or saves.
SHA-256: `a5760f1ed082ea56c9eeb998df9cace9bdb6c7b9ab9bb9b7e29e6b887bfd16fc`.
The final Last Respects and Revival Blessing reports contain 14 passing native
cases in total; their input ROM hash matches this delivery. This batch also
passes 88 repository host tests, 136 harness oracle/lifecycle tests, 20 fixture
input tests and the fixture builder's strict TypeScript check. Privacy validation
found no violations in publishable files or archive members.
SHA-256: `8610bc5150ee2efe27b4c527109d3442714ec1a96e1164fabc6c090f0a699cc8`.
This exact ROM passed all 27 Dragon Darts cases. The preceding batch 38 ROM
passed all 19 Shed Tail cases, including a real attack on the transferred doll
and both native server/client copies; its preceding focused build passed all
9 Chilly Reception cases. The doubles fixtures
configure both trainer data and the cold-boot runtime, supply two Pokémon per
side, independently check native rule/counts and all four slots, submit both
player commands, and restore one battle-start snapshot per case. The new input
driver selects move slots and explicit ally/foe targets through signature-pinned
native UI phases. HP/stages and selected major statuses are bounded pre-input
fixtures; protection, hiding, traps, hazards and Heal Block use real move setup.
No battle commands or calculated effects are overwritten. Triples remain
unverified; the separate Rage Fist suite below covers local multi ownership,
not the other mechanics in this doubles batch.

The tests exposed and fixed native direct-stat Substitute rejection and
MUST_HIT status reachability during Fly. Boosts use native work (including
Simple/Contrary, caps and success), without removing Substitute or overwriting
stages. The native hiding table/accessor and work-result signatures are pinned
by the fixture builder. The harness now rejects doubles saves with fewer than
two eligible living non-Egg Pokémon.

Earlier suites are recorded above and were not all rerun on this ROM. No
Retreat/Jaw Lock/Octolock/Glaive Rush/Salt Cure/Syrup Bomb's 55 cases passed on
batch 29; Blood Moon/Gigaton Hammer's 18 cases passed on batch 28. Final checks:
84 repository host tests, 133 runner/oracle/deadline tests, 20 harness fixture
tests, fixture TypeScript checking and the tracked/archive privacy scans passed.
Generated fixture ROM cleanup and snapshot release were verified; fixture saves
remain retained and output stays ignored. No full B2 behavioral suite was run.

The doubles rollout also corrected the harness's obsolete status bit masks:
BW2 party status is an ID (0–5). Cure/thaw tests now assert the condition before
execution, so a healthy fixture cannot produce a false-positive pass. Matcha
damage checks include native fixed-point spread rounding rather than reading
an unsupported private-stack alias. Dragon Cheer leaves the project's global
critical odds unchanged; Costar/Opportunist/Mirror Herb depend on separate
systems. Full prize payout, Baton Pass, switching/teardown stress, drain-induced
KO and Mortal Spin contact-KO remain outside this native doubles case set;
compiled guards are not substitutes for those emulator regressions.

## Rage Fist native multi validation (2026-10-05)

`rage-fist-multi` passed all 9 cases on the current main ROM, plus 2 reversed
cases proving that a faint/revival timeline cannot leak hit history into the
restored fresh battle. Setup requires four separate native trainer parties,
mode 3 and active IDs `0/6/12/18`; NPCs take real AI turns. Power is checked
against observed direct hits, with independent damage, committed HP, PP and
next-command assertions. The existing production handler needed no changes.

The test-only native setup adapter passed 6 compiled ARM946 argument/relocation
checks; 177 battle host tests, 89 repository tool tests and strict fixture
TypeScript checks passed. Fixture ROM deletion and memory-snapshot release were
verified; saves and ignored reports remain. Original inputs and Pokeweb were
unchanged. These fixtures run in DS mode, not DSi/network/replay or B2.
Last Respects remains non-multi-only.

Usage and future-suite guidance: [battle test reference](../tests/battle/README.md#native-multi-trainer-harness-rage-fist).
