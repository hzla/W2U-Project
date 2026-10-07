# White 2 integration report

Report date: 2026-10-06. Branch: `w2u-integration` in Upgrade and Pokeweb.

## Current status

The seven implementation stages and reviewed history reconciliation are complete. The delivered build is a **release candidate, not a fully accepted release**. Builds, registry/linkage checks, host tests, substantial headless battle coverage, animation-completion checks, and selected renderer/loader lifecycle tests pass within the scopes below. Normal trainer intros, complete visual lifecycle coverage, native repeated/address-changing reloads, and several other acceptance gates remain unverified.

The stage-7 evidence below retains its original input revisions; RC2 startup checks and the subsequent RC3 move completion are recorded separately. Test counts describe tested cases, not a claim that every interaction of every registered mechanic is covered.

The supported acceptance target is US White 2 revision 0 in DS mode. Black 2 received compile/static-isolation checks only. Hardware and DSi compatibility are not certified.

## Startup correction and RC2

RC2 superseded RC1 for startup; use RC3 below for the latest move handlers. Startup-fix commit `f47301dd6` addresses two release-packaging defects: stale compression metadata made the native bootstrap decompress an already-expanded ARM9, and an unconditional testing main-menu skip forced Continue without valid saved map data. RC2 clears that metadata and excludes main-menu skip from production; the DLL remains available under `assets/testing/` for fixtures.

The byte-identical exported RC2 ROM passed two 1,800-frame headless melonDS cold boots: no-save startup reached the new-game introduction, and a private copy of an existing save reached the overworld through normal Continue. No Pokeweb materialization, memory edits, or old savestates were used. The build now rejects stale metadata or a staged main-menu skip. Host tools pass 135 tests with one existing skip, out of 136 total. The [startup audit](../pmc/w2-integration-startup-audit.json) records the results and remaining limits; the new ROM was not GUI-tested in DeSmuME here.

RC2 SHA-256 is `3074da8263810c5576acbf0e64eb24aba4dbb5edd9caf3f822757f81b751c1ba`. Its stripped core hash is unchanged. Removing the testing DLL saves 320 PMC bytes including its allocator overhead: all-group post-fix free space is now 14,264 bytes, with a conservative transient minimum of 11,208 bytes. The earlier stage-7 coverage and memory tables below retain their original revision provenance; they are not a full mechanic rerun on RC2. Other acceptance gaps remain open.

## Follow-up: remaining move handlers and RC3

RC3 completes Thousand Arrows, Thousand Waves, Hyperspace Hole, Hyperspace Fury,
Fairy Lock, Gear Up, Psychic Fangs, and Order Up. They reuse five existing
on-demand groups; hooks, Fairy Lock lifetime, and Commander form storage remain
resident. All eight registrations are White-2-only. The current registry has
30 groups, 141 abilities, **153 moves**, 13 items, and 12 subordinate entries:
319 entries total. Multi-Attack and Ivy Cudgel remain deferred for their items.

All **70 root effect cases plus four follow-up actions** pass on RC3, with full
turn completion in each suite. An additional 15 Raging Bull cases and six
selected Gen 6/7 move regressions pass on the same ROM. The shared screen-break
callback now runs native screen removal and Aurora Veil removal together,
because the retail event dispatcher only invokes the first matching callback.
The new [coverage ledger](../tests/battle/remaining-move-coverage-2026-10-06.json)
records exact input hashes, cases, reports, negative controls, and limits.

Psychic Fangs' previous imported animation referenced nonexistent resources in
a SPA shared with Geomancy. RC3 uses Volt White 2 QoL's Egg Bomb replacement
(script member 121), imported into member 706. Its only SPA, 326, was verified
byte-identical in donor and release; no SPA replacement was needed. Geomancy
and Laser Focus's particles remain unchanged. All nine Fangs cases pass with
animations enabled. The other seven moves have earlier one-case animation
smoke results on the identical core and unchanged assets; these are completion
checks, not visual/audio certification.

Current fast checks pass: 146 repository host tests plus one existing skip,
185 battle unit tests, strict TypeScript, source privacy, stripped build,
registry/RPM linkage and packaging, and Black 2 compile/static compatibility.
An unmodified 1,800-frame RC3 cold boot reaches the normal four-entry menu,
without a save, old savestate, memory edits, or the production menu-skip patch.
This is not a new DeSmuME, hardware, or DSi certification.

The versioned parent-directory artifact is
`White2Upgrade-w2-integration-20261006-rc3.nds`, with SHA-256
`017cc0e0fbecd23b79dc095134806ec7b0e08749d74fed465677f65798be4940`.
The stripped core hash is
`cadcc3fa9ea266283efd61c3b60401661343766e746a1feea12354d7a714bbbc`.
Earlier ROMs and user saves are retained.

RC3's current heap audit budgets 192,488 bytes with all groups post-fix,
leaving **12,312 bytes**—only 24 bytes above the 12 KiB floor. Conservative
expanded loading leaves 9,256 bytes. This transient limit and the acceptance
gaps below remain open; RC3 is still a release candidate.

## Follow-up: battle groups on game heap 1 (2026-10-07)

Contributor follow-up on RC3 (`36355ece7`). White 2 now loads the battle groups into GFL game heap 1 while a battle
runs, so PMC's heap holds only the resident core. Details and measurements are in
[the MegaB2W2 integration notes](megab2w2-integration.md) ("Battle modules on the game heap").

- The loader points PMC's `ModuleManager` heap at a small ExtLib-compatible allocator over heap 1 around its own
  load and unload calls only, after checking that the manager's heap is exactly PMC's. It does this only during a
  battle (battle heap 0x13 present, the field's heap 0x15 absent) and only when the group plus a 64 KiB reserve fits
  heap 1 in one block; otherwise the group goes to PMC's heap as in RC3, with the existing refusal guard. No PMC
  change. Black 2 is unaffected: its core has no module loader.
- Heap 1 had 512,856 bytes free throughout every measured battle, direct-boot and started from the overworld. The
  field's heaps are destroyed before a battle and rebuilt only after the groups are unloaded (traced).
- The heap audit's `--enforce-headroom` now applies the 12 KiB floor to PMC's heap with every group on heap 1
  (`all_groups_on_game_heap`: 96,776 bytes free) and checks a heap-1 budget (all groups, block headers and the largest
  transient load: 89,248 bytes, plus the 65,536-byte reserve, against 512,856). The all-groups-on-PMC scenarios stay
  in the report as the fallback worst case, not gated. Transient expanded loads now happen on heap 1 as well.

Evidence (the contributor's local harness, which is not in this checkout, so like the incoming results above these
are not counted as integration runs): the eight local regression specs, 209 scenarios, pass on this build and on
the same build without the change, spec for spec; a battle started from the overworld with a group loaded (outside
PMC's heap during the battle, heap 1 back to its overworld size after it); a doubles battle loading 12 groups at once
(40,936 bytes on heap 1, lowest free 471,200); a build forced onto the PMC fallback runs that battle message for
message the same. Host tests: 147, with the nine Windows-only failures of unmodified RC3; the loader-lifetime test
now also checks that a heap-1 group unloads through the allocator. Built with GCC 14.3.1, which makes the same core
336 bytes larger than RC3's GCC 16.1.0 (RC3 itself leaves 11,976 bytes here). Not run: hardware, DSi, Black 2.

## Sources, commits, and delivered build

Upgrade used `megab2w2-integration` at `4369e8a4738ea435a350eff4e9c527d523bd8c31` as its base and selectively ported `main` at `eb6c002384f2fcc4df7bfef6d3cdad5626364a73`. Pokeweb started at `d5e2dc0f47a7fe829204527a09572f4d48ef88c1`. Work happened in isolated checkouts; unrelated dirty work in the original checkouts was preserved.

| Upgrade commit | Scope |
| --- | --- |
| `62ee879a9` | Baselines, shared regression infrastructure, loader/build validation, and target-aware registry support. |
| `74f6e61cd` | Missing White 2 moves and their resident services, state, and lifecycle wiring. |
| `d8f7b120c` | Overlapping handlers, parameter phases, action ordering, and single ownership of engine hooks. |
| `254c35fd4` | Shared ability fixes and the selected Parental Bond, Disguise, and Grass Pelt policies. |
| `3b229a02e` | Weather, move restrictions, and called-move/NPC policy reconciliation. |
| `e9c892467` | Final IDs, messages, registry, and generated manifests. |
| `c689810c6` | w2anim release integration, validation-driven fixes, and release audit. |
| `6f095a4f7` | Reviewed reconciliation merge preserving both pinned histories. |

The final merge used an `ours` strategy **after** the semantic ports and review. It changed reconciliation/progress metadata only, not the resolved runtime tree. It is not evidence that an automatic content merge was conflict-free. The intentional exclusions are recorded in the [reconciliation manifest](../pmc/w2-integration-reconciliation.json).

Pokeweb commits are `1bb7062` (expanded ability IDs in test teams) and `78b08f5` (lossless w2anim ROM authoring).

The stage-7 stripped artifact was delivered as `White2Upgrade-w2-integration-20261006-rc1.nds` and is now superseded by RC2 above. Both versioned files are retained in the workspace parent directory; existing ROMs and saves are not overwritten.

```text
ROM SHA-256:
24457ec7f10575963d9c29b01020de3f4d36a1d6076709f365c9646bd7eeb1be

Stripped core RPM SHA-256:
f62adf3f15fd44f55d41dc86f2e7abd10c7c2a3722876f66b14bc7e5805a036b
```

## What was integrated

### Runtime, registry, and battle mechanics

We retained the incoming resident **w2anim renderer**, **200 KiB PMC reservation**, module ABI version 1, 32-record loader capacity, module paths/IDs, incoming ability IDs/messages, registry architecture, and preview cleanup. White 2 does not link or stage the old PWAN renderer hooks/runtime.

We ported main's 44 missing White 2 move registrations and used main's implementations for overlapping moves. Required action ordering, called-move context, move history, targeting, extra-action execution, switching, revival, and reset services remain resident; grouped mechanic handlers remain on-demand. Groups load during mechanic registration, not only when a move is used, and remain loaded until battle cleanup.

The stage-7 [declarative registry](../src/pokeweb_gameplay/battle_modules/registry.json) contained **30 groups, 141 abilities, 145 moves, and 13 items**, plus five field, two side, and five position entries: 311 entries total. RC3's updated counts are above. These are registration counts, not a claim of universal Gen 6–9 support. Per-entry `white2_only` filtering keeps White 2 additions out of Black 2's static tables.

The loader has stronger RPM/API bounds, pointer, relocation, and RAM-range checks; caches both success and failure for a battle; and refuses allocations that cannot fit. Shared cleanup disables registration, clears cached pointers, unloads in reverse order, and resets shared state. Normal exit, abnormal new-battle setup, and resident unload use that lifecycle. No per-event unload was introduced.

### Deliberately reconciled policies

| Area | Integrated policy |
| --- | --- |
| Parental Bond | Main's implementation: second ordinary hit takes one quarter of final damage; fixed-damage exceptions retain full damage. |
| Disguise | Incoming Mimikyu-only behavior, one 1/8-max-HP bust payment, with main's hit-history bookkeeping. |
| Grass Pelt | Exactly one registration, owned by `mb_terrain`. |
| Weather | Incoming strong-weather IDs 5/6/7 retained; Snow has logical/display ID 8, using native Hail transport ID 3. Cold-weather consumers, suppression, and strong-weather precedence are combined. |
| Restrictions | Gorilla Tactics combined with selection/execution restrictions, Encore, Instruct, extra actions, and NPC move policy. |
| Parameters and terrain | Native, ability-modified, and final phases kept distinct. Duplicate Expanding Force/Misty Explosion boosts and the conflicting alias were removed. |
| IDs/messages | Incoming IDs retained; main references remapped and main-only messages appended without overwriting occupied IDs. |

Validation also exposed and corrected native trapping/Happy Hour/Haze event contexts; Water Shuriken's Gen 7 category; Flying Press against Minimize; Flower Shield grounding; Shore Up rounding; Revelation Dance's final type phase; Electric Terrain's treatment of existing sleep; Laser Focus lifetime; and Coaching/Tidy Up/Take Heart effective stat caps. Fixture corrections preserved independent damage, status, action-order, and failure expectations rather than weakening them.

### Animation repair and Pokeweb authoring

Drum Beating, Pyro Ball, and Raging Fury were repaired within this integration as requested. Terrain Pulse and Infernal Parade shared the same particle-work overflow. The repair increases both the native particle allocation and its advertised capacity from 18,432 to 24,576 bytes; incoming Pyro Ball assets were restored. This adds 6,144 bytes per live particle context on the **game heap**, not PMC.

Pokeweb now imports, edits, and exports existing w2anim ROMs using W2AS v1 / MANI v2. Backend detection prevents PWAN installation into a w2anim ROM. Untouched streams, shared frames, palettes, timings, and native mappings are preserved; supported edited streams use lossless LZ10, frame deduplication, and the converter's carrier/palette conventions. New Pokémon and trainer exports are supported.

Supported edits are bounded to the implemented 96×96 TEX4/timeline constraints, including at most 128 timeline ticks. Longer or otherwise unsupported original streams remain preservable untouched; unsupported edits are explicitly rejected before project mutation. This is **not** a clean-ROM w2anim installer. Test-team ability packing/validation now supports IDs through 1023 while preserving unrelated Pokémon flags.

### Black 2 boundary

Black 2 retains frozen incoming gameplay/assembly sources and target-filtered static registrations. No Black 2 behavioral/hash baseline was refreshed and no Black 2 ROM was published. Shared data prepared for White 2 must not be treated as a certified Black 2 release; the gameplay/renderer port remains a later phase.

## Current test coverage

### Stage 7 host tests and build gates

| Layer | Recorded result | What it establishes |
| --- | --- | --- |
| Upgrade tool units | 126 passed, 1 skipped; 127 total | Registry/isolation, hook ownership, restrictions, memory accounting, RPM bounds, loader lifetime, and focused source/contracts. |
| Battle harness/oracle units | 180 passed | Fixture, result-reader, and independent behavior-oracle tests. |
| Battle TypeScript | Strict check passed | Harness/fixture type consistency. |
| Pokeweb | 1,708 passed, 3 skipped; 1,711 total in 163 files | Existing application regressions plus expanded ability IDs and w2anim authoring tests. |
| Pokeweb release gates | Typecheck, production build, privacy scan passed | Buildable authoring application and checked publishable output. |
| Upgrade release gates | Stripped/unstripped builds, RPM linkage, registry generation/packaging, privacy checks passed | Build/link/package consistency; unstripped output remains diagnostic only. |
| Black 2 | 174 hooks, 231 imports, 48 anchors checked | Compile/static compatibility and White 2 isolation, not behavioral acceptance. |

The skipped Upgrade test is Court Change's clean-US native literal contract; it requires clean Black 2 and built White 2 ROM inputs. A skip is not a pass. The three Pokeweb skips are likewise excluded from the passing count.

Build gates check duplicate numeric registrations, counts/priorities, target filtering, generated-output freshness, the exact packaged group set, satisfiable imports, and child export/hook/constructor restrictions. Stripped children retain the API export hash without symbol-name strings, and the core must not import child handlers directly.

### Native headless battle behavior

Native testing used headless melonDS and fresh fixture ROM/save inputs produced through the test tooling. No browser emulator or old user save states were used as release evidence. Most mechanic runs disabled battle animations; animation-enabled checks are listed separately.

| Coverage set | Accepted result | Qualification |
| --- | --- | --- |
| Gen 8/9 and shared-mechanic batch | 87 suites, 1,246 cases | 53 suites report full-turn validation; 34 use focused checkpoints. |
| Gen 6/7 moves | 117 cases | Complete suite, full-turn validated. |
| Gen 6/7 abilities | 143 cases | Complete suite, full-turn validated. |
| Gen 6/7 items | 33 cases | Complete suite, full-turn validated. |

That is **1,539 accepted behavioral cases**, spread across multiple integration revisions. The [native suite summary](../pmc/w2-integration-native-results.json) contains every one of the 87 suite names, case counts, full-turn flags, input hashes, and retained failed attempts.

The suites exercise healing/status/stat changes; terrain and weather; damage formulas and multi-hit moves; shields and restrictions; doubles targeting and redirection; called moves and PP; trapping, switching, revival, and move history. Representative focused suites include Dragon Darts, Coaching, Shell Side Arm doubles, Court Change, Teatime, Rage Fist, Blood Moon, Gigaton Hammer, Glaive Rush, Snowscape, Chilly Reception, Shed Tail, and Revival Blessing. Gen 6/7 suites cover the selected Parental Bond, Disguise, Grass Pelt, terrain, and form policies within their defined cases. This does not replace focused coverage for every additional incoming ability or Mega policy.

**Revision provenance matters:** the 87-suite primary run used hash `1699af25…`; 11 complete corrected retries, totaling 119 cases, used the delivered `24457ec7…` ROM. The Gen 6/7 ability/item suites used `3edcc914…`, and the move suite used `1699af25…`. Eleven failed/incomplete primary attempts remain recorded rather than disappearing from the report. Therefore, “all tests passed on the final ROM” would be inaccurate; a comprehensive single-hash rerun remains a useful release gate.

### Loader, renderer, animation, and authoring coverage

| Area | Existing evidence | Boundary |
| --- | --- | --- |
| RPM/API corruption | Compiled-host ASan/UBSan parser/API tests, including every truncation of all 30 actual child files and malformed tables/pointers/counts/relocations. | Host validation is not native coverage of every corruption variant. |
| Native negative loading | Six modes: missing file, corrupt API magic, wrong ABI, truncation, corrupt RPM tables, heap refusal. Failures cache once; child/stream counters return to zero at exit. | Modes span pre-final and final revisions; native record-capacity exhaustion remains untested. |
| All-group loading | Synthetic native registration of all 30 actual APIs: 30 loads, reused handles, no failures; 30 unloads and zero current child bytes at real exit. | Private 160-byte wrapper, not a legal-party route or repeated/address-changing reload test. |
| Cleanup | Host reverse-order, idempotent, re-entrant lifetime checks; native one-battle exit measurements. | Dedicated native repeated-battle/address-change cases remain open. |
| Gen 8/9 script completion | 158 non-Max scripts: 156 inert-metadata completions plus two native prerequisite cases, Comeuppance and Thunderclap. | Completion is not visual correctness or complete gameplay validation. |
| Repaired animations | All five repaired moves complete with production modules/streamed sprites and verified real battle exit. | Raging Fury required a finite 4,800-frame limit; it completed at 3,012 frames. The earlier 2,400-frame timeout is retained. |
| Animation-enabled behavior | Four Snipe Shot doubles cases and one Take Heart/own-Substitute case. | Selected scenarios only, not exhaustive visual comparisons. |
| Native authored sprite | Newly materialized native Pokémon stream loads on both sides and frees its six live buffers at field exit. | Quick-battle entry skips normal trainer intros. |
| Pokeweb ROM round trip | 1,147 indexed streams; 1,146 untouched streams byte-identical; 12 edited/new frames independently decoded; new Pokémon/trainer exports checked. | Trainer export has host coverage, not native trainer-intro certification. |

## Stage 7 memory audit

The authoritative budget is the corrected [release audit](../pmc/w2-integration-release-audit.json), not the earlier stage estimates. It accounts for core/BSS, resident Battle Log/counters, bootstrap patches, the PMC root/work area, allocation alignment/headers, and a bookkeeping/fragmentation reserve. Loader state is already included in the resident core.

The stripped core occupies 96,008 resident bytes, including 4,016 bytes of BSS. Production child modules total 83,544 resident bytes including BSS before per-allocation alignment/headers.

| Stripped PMC scenario | Budgeted used bytes | Free bytes |
| --- | ---: | ---: |
| No custom groups | 106,832 | 97,968 |
| Largest single group | 116,016 | 88,784 |
| All 30 groups, post-fix | 190,856 | **13,944 (13.62 KiB)** |
| Conservative expanded final group load | 193,912 | **10,888 (10.63 KiB)** |

The 12 KiB **post-fix** headroom target passes within the 204,800-byte heap. It is not guaranteed during every transient loading order. The synthetic native order observed a 13,176-byte minimum during loading and zero child bytes after teardown, but that is one measured order, not a universal transient bound.

Stages 1–6 omitted the root/work/bootstrap costs from their historical free-byte figures. Those figures are not acceptance budgets. The original 164 KiB monolith comparison's 8 KiB/4 KiB savings goals are **not met or claimed** by this larger integration. The unstripped all-group build exceeds the heap by 25,752 bytes and is not release eligible.

w2anim and particle allocations use separate game heaps. Audited stream payload bounds are 8,084 bytes per sprite, 32,336 for four sprites, and 64,672 for eight slots. These exclude game-allocator headers and the shared VBlank task. The particle audit checks 253 assets; the maximum computed requirement is 19,860 bytes within the repaired 24,576-byte arena. No complete worst-case game-heap budget is claimed.

## Remaining acceptance work

Before promoting this candidate, complete the following:

1. Run normal trainer intros and the full nonbattle renderer lifecycle; compare forms, Substitute, shiny/female palettes, first-frame priming, and doubles visuals.
2. Add dedicated native repeated-battle, changed-address reload, and loader-record capacity-exhaustion cases.
3. Exercise a legal party that reaches all groups, rather than relying only on synthetic API registration; examine transient load orders and fragmentation.
4. Add focused native cases for remaining incoming ability/Mega policies. The incoming local scenario/check-ROM harness is absent from this checkout, so its historical results are not counted as integration runs.
5. Measure game-heap headers/shared-task overhead and the complete peak allocation picture.
6. Rerun the consolidated behavior gates on one final ROM hash, retaining failed attempts and explicit retries.
7. Verify hardware/DSi separately if those targets are to be supported. Keep the deferred Black 2 port and acceptance as a separate phase.

## Evidence and maintenance

The committed [release audit](../pmc/w2-integration-release-audit.json), [native results](../pmc/w2-integration-native-results.json), [stage progress](../pmc/w2-integration-progress.json), and [reconciliation manifest](../pmc/w2-integration-reconciliation.json) are the evidence index. Raw `work/` reports are local, ignored artifacts; they may not exist in a fresh clone. Counts, hashes, accepted scopes, failed attempts, and limitations are retained in the committed summaries.

The repository-owned [battle test guide](../tests/battle/README.md) describes setup and fixture/oracle conventions. [The regression runner](../tools/run_w2_integration_regressions.py) freezes the input ROM for a batch; [the summarizer](../tools/summarize_w2_integration_regressions.py) rejects incomplete results and records provenance. Heap/particle/w2anim audit tools and `tools/tests/` provide the host checks. Run builds serially across build directories because they share the source-tree VFS.

Future changes should regenerate registry outputs, pass relevant independent behavior tests and linkage/build gates, and update this report's evidence index or create a new dated report. Do not relabel an old pass as coverage of a changed binary, an animation completion as visual correctness, or a synthetic registration test as legal gameplay.
