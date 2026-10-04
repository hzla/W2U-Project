# Generation 8 and 9 move handler implementation reference

Research date: 2026-10-03. Target: White2Upgrade-Original-pokeweb, using White 2 on-demand battle modules and Black 2 static registration.

This is a preparation and implementation specification, not a claim that these moves have been implemented or tested. It covers every non-Max entry found in Bulbapedia's [Generation VIII category](https://bulbapedia.bulbagarden.net/wiki/Category:Generation_VIII_moves) and [Generation IX category](https://bulbapedia.bulbagarden.net/wiki/Category:Generation_IX_moves) on the research date. Each of the 159 included move pages was fetched and its Effect section reviewed. Effects below are paraphrased; source links and reviewed page revision numbers accompany each entry. Links open the live page; revision numbers identify the version reviewed for this reference.

The complexity ratings and suggested module placements are engineering judgments based on the present repository. The Effect paragraphs describe the sourced move rules; Implementation paragraphs describe proposed integration. No ROM build, emulator test, battle regression, or heap measurement was performed for this documentation task.

## Scope and ruleset

| Inventory | Category entries | Excluded Max or G-Max entries | Included |
| --- | ---: | ---: | ---: |
| Generation VIII | 141 | 52 | 89 |
| Generation IX | 71 | 1 | 70 |
| Total | 212 | 53 | 159 |

The 52 Generation VIII exclusions are the 33 G-Max moves and 19 Max moves. The Generation IX exclusion is Max Spirit. Ordinary moves such as Behemoth Blade, Behemoth Bash, and Dynamax Cannon remain included; their anti-Dynamax bonus has no application without a Dynamax system.

Proposed default: use updated Scarlet/Violet turn-based mechanics, including DLC updates, where a move has that specification. For moves absent there, use Sword/Shield's conventional battle rules when available. This is a proposed implementation policy, not a user-approved change to the project's global generation rules. Do not silently substitute Champions changes, Arceus agile/strong styles or action-speed modifiers, or Z-A real-time cooldowns. Important differences are recorded in the entries.

Power Shift is a special case: this reference proposes its Generation IX raw Attack/Defense swap, which can reuse Power Trick, rather than Arceus's four-stat swap. Nihil Light has no canonical conventional turn-based version; its PP, ID, and turn adaptation require a decision before coding.

Animations, species learnsets, evolution-by-move counters, and complete new ability/item systems are outside this handler specification unless an effect cannot work without them. Still validate move type, category, power, accuracy, PP, priority, target mask, hit counts, flags, and animation linkage: a correct handler does not repair incorrect move data or an incompatible imported animation script.

### Complexity definitions

- **Already Supported by vanilla Gen 5 engine**: the move-specific effect fits generic Gen 5 move data or can directly clone/reuse an existing handler, without new unique mechanic logic. Registration aliases, metadata corrections, and compatibility tests may still be necessary. This does not mean the move is currently enabled, correctly configured, or proven playable.
- **Easy**: a small check, parameterized extension, or additional callback using established engine services; little new lifetime-sensitive state.
- **Medium**: several interacting callbacks, execution/selection ordering, conditional targets/category/type, or a new source-linked/turn-linked volatile.
- **Hard**: engine-flow or UI work, persistent party/side history, transactional side/ability changes, multi-target sequencing, or a missing major battle system.

Ratings assume move-specific work on the existing framework. Global differences such as modern critical rates, protection probabilities, Ghost escape, and sound/Substitute rules must be audited separately; they are not reasons to write duplicate bespoke handlers for every ordinary move.

| Complexity | Generation VIII | Generation IX | Total |
| --- | ---: | ---: | ---: |
| Already Supported by vanilla Gen 5 engine | 38 | 21 | 59 |
| Easy | 24 | 19 | 43 |
| Medium | 23 | 19 | 42 |
| Hard | 4 | 11 | 15 |

## Repository integration requirements

Use [the existing battle-module guide](w2u-battle-modules.md) and these repository-relative sources:

| Concern | Source of truth or reviewed code |
| --- | --- |
| Move IDs and data layout | `include/Moves.h`; `data/pml/moves/<ID>.toml` |
| Managed primary and subordinate entries | `src/pokeweb_gameplay/battle_modules/registry.json` |
| Registry/API/Meson generation | `tools/generate_w2u_battle_registry.py` |
| Resident routing and existing move logic | `src/pokeweb_gameplay/w2u_moves.cpp` |
| Shared move/extra-action services | `include/w2u_moves.h` |
| Module ABI and loader | `include/w2u_battle_module_api.h`; `include/w2u_battle_module_loader.h`; `src/pokeweb_gameplay/w2u_battle_module_loader.cpp` |
| Child verification and packaging | `tools/verify_w2u_battle_module.py`; `tools/stage_w2u_battle_modules.py` |
| Black 2 compatibility reporting | `tools/generate_black2upgrade_compatibility.py` |

All 158 included moves other than Nihil Light already have named IDs in `include/Moves.h`. An ID or TOML record is not evidence that its special effect exists. For example, Order Up and Salt Cure have ordinary-damage records but need additional logic. Current data already contains useful ordinary effects such as Headlong Rush's two self-stat drops and Surging Strikes' three-hit/critical settings.

The registry currently has 22 modules against a fixed capacity of 24, with 101 managed move entries. Prefer an existing cohesive module; only two additional groups fit without a reviewed loader-capacity change. The table's module column is a recommendation, not a reason to load a child for a wholly data-driven move. Exact vanilla aliases should remain resident unless a reviewed exception requires new logic.

For new handlers:

1. Update the declarative registry, non-generated source/data, and any relevant reviewed service declarations; regenerate the route table, API definitions, and Meson group manifest. Do not hand-edit generated files.
2. The generator currently enforces primary counts of 59 abilities, 101 managed moves, and 13 items. Update those expectations coherently when adding managed entries, retaining duplicate and coverage checks rather than bypassing validation. The ability count includes Overcoat's updated powder immunity.
3. White 2 must resolve the child through the existing versioned API at registration, not import child handler addresses into the core. Keep handlers/tables hidden and the single child API export unchanged. Black 2 must use the same logic through its generated static resolver.
4. Add subordinate field/side/position entries and dependencies where needed. A native move caller, copied move, or newly acquired ability can introduce a module not present in the initial moveset; audit registration for those paths instead of assuming all children were preloaded.
5. Store shared mutable state in the resident core behind narrow `W2U_*` services. Do not expose mutable structure layouts or add child-owned history that disappears on switch/removal. Keep one-action scratch state separate from per-turn, per-field-occupant, per-party-member, and per-side state.
6. Load once per group, keep it alive for the battle, and unload only through established teardown. Do not unload when a primary move/ability/item event disappears: subordinate effects retain function pointers.
7. Remove conflicting resident aliases when replacing them. Managed resolution failure must not fall through to a vanilla mechanic sharing the numeric ID.
8. Preserve the dirty worktree, overlay/PWAN modules, existing Mega behavior, and White 2/Black 2 build symmetry. Do not refresh compatibility/hash baselines merely to make checks pass.

### Recommended families and shared services

| Existing group or core service | Appropriate extensions |
| --- | --- |
| `moves/guards` | Obstruct, Silk Trap, Burning Bulwark; non-destructive Hyper Drill/Mighty Cleave bypass |
| `moves/hazards` | Ceaseless Edge, Stone Axe, Mortal Spin, Tidy Up |
| `moves/trapping` | Jaw Lock, Octolock; modern binding for Snap Trap/Thunder Cage |
| `moves/screens` | Court Change and Aurora Veil-aware Raging Bull |
| `moves/terrain` | Conditional terrain attacks, charging helpers, snow-related move entry points |
| `moves/type` | Conditional power/type, Body Press-adjacent category services, Double Shock, Tera integration |
| `moves/stats` | HP-cost boosts, Body Press, Dragon Cheer, combined stat/cure effects |
| `moves/volatile` | Glaive Rush, Salt Cure, Syrup Bomb, Psychic Noise |
| `moves/flow` | Selection/history rules, healing/drain/item actions, redirection, multi-hit sequencing |
| `moves/ability` | Doodle and Order Up entry points |
| Resident core | History collectors, party counters, selection/extra-action dispatch, weather/Tera/Commander systems |

These placements are provisional: adding many moves to a large existing group can increase the cost of loading a single mechanic. Measure stripped fixed and expanded sizes, then split/regroup cohesive families only if justified by heap results. A capacity increase must update the loader, failure mask, ABI-facing assumptions, registry validation, and stress tests together; do not simply add a 25th group.

Prefer shared helpers over copying near-identical callbacks: Bolt Beak/Fishious Rend, Burning Jealousy/Alluring Voice, Blood Moon/Gigaton Hammer, Collision Course/Electro Drift, Jungle Healing/Lunar Blessing, the three rain-accurate storm moves, and Hyper Drill/Mighty Cleave.

PW2Code has a concrete reviewed implementation in `PW2Code/Libraries/Moves/CeaselessEdge.cpp`, registered by its battle-engine table. It queues Spikes work from a real-hit end event; it is a porting starting point, not a tested drop-in. The inspected `HyperspaceFury.cpp` uses Feint's protection-breaking callbacks, so it is not an exact implementation of the new non-destructive protection bypass moves. In this repository's protect-check hook, break value 1 invokes guard breaking while the nonzero non-1 path skips protection without breaking it; validate that route against every relevant guard.

The resident critical-roll hook returns false for out-of-table ranks unless Laser Focus is active. Several imported move records use critical stage 6, including Surging Strikes and Flower Trick. Native dispatch has now been inspected: stage 6 is the forced-critical encoding, checked after ability/side vetoes and before the rank-roll call. These moves reuse that path rather than Laser Focus state; this source inspection is not a new emulator test.

The conflicting Barb Barrage → Hex alias has been replaced with a poison-only handler and focused status tests. Temper Flare is wired to the existing Stomping Tantrum table/tracker, which distinguishes protected failures; its listed history/recharge cases were not newly emulator-tested under the requested reuse-testing policy. The legacy bit-10 name `FLAG_DEFROSTS_TARGETS` actually enables native user thaw; it alone does not establish Scorching Sands' target-thaw behavior. See the [incremental progress tracker](gen8-gen9-move-handler-progress.md) for wiring versus test status.

## Engine dependencies and decisions before the full batch

- **Snow**: no snow runtime implementation was found in the inspected battle sources; Hail already exists. Choose a separate weather or an explicit project-wide Hail replacement policy. Snow is not just Hail with a different label: remove hail damage, add Ice Defense, and update weather-dependent abilities, recovery, Weather Ball, Aurora Veil, duration, and presentation.
- **Tera and Stellar**: full Tera Blast/Tera Starstorm behavior requires type retention, category selection, Stellar effectiveness, forms, and integration with type-changing moves. Implementing only their ordinary non-Tera branch is partial support.
- **Commander and forms**: Order Up needs the actual Dondozo/Tatsugiri relationship. Aura Wheel, Ivy Cudgel, and Raging Bull need correct species/form/item data. A constant or sprite alone does not establish battle support.
- **Persistent history**: Rage Fist and Last Respects need collectors active before their child is loaded. Preserve party-member/side identity across switch/faint/revival/Transform as specified. Account for the fixed resident cost of those collectors in heap audits.
- **Ten strikes**: Population Bomb requires an audit of all hit-count storage, loops, event work, damage aggregation, and animation commands. Four-bit `HitMin/HitMax` fields do not prove the pipeline handles ten hits.
- **Revival and substitution/switch transactions**: Revival Blessing and Shed Tail need safe party-choice flow and party-state work, including multi-battle ownership and existing Mega state.
- **Move calling and selection**: review Metronome, Copycat, Sleep Talk, Nature Power, Assist, Me First, Mimic, Sketch, Encore, and Instruct as applicable. Implement specific blacklists and called-move exceptions as shared policy, not ad hoc duplicate checks. Preserve PP, natural turn order, and extra-action identity.
- **Global generation policy**: explicitly retain or upgrade critical chance/damage, modern Protect success rates, Ghost escape, Electric paralysis immunity, powder immunity, modern binding fractions, and sound/Substitute behavior. Existing forced-critical code must still honor armor abilities. These decisions affect old moves too.
- **Flags and ability integration**: set sound, contact, wind, bullet, bite, punch, pulse, powder, slicing, healing, thawing, reflection, and guard flags from move rules, not names. An imported flag does not implement an absent ability. For new added effects, audit all Sheer Force power/failure/hit checks plus Shield Dust, Aroma Veil, Clear Body, Contrary, Mirror Armor, and Magic Bounce where relevant.
- **New move ID**: Nihil Light requires a coordinated move-range/data/text/UI audit. `MOVE_END_MSG = 920` is a sentinel; do not simply reuse it.

Do not deliberately recreate old glitches such as Dragon Cheer's pre-3.0.1 switch persistence or Order Up's pre-fix protected-target boost without a documented compatibility choice. Pages sometimes describe software bugs as well as intended effects; distinguish them locally.

Resolve explicit Bulbapedia research gaps without inventing answers. The entries identify important gaps in Dragon Darts, Eerie Spell, No Retreat, Corrosive Gas, Last Respects multi-battle scope, and some residual/reapplication timing. Consult additional trustworthy evidence or write a labeled project policy and tests; do not present a guessed policy as canonical behavior.

## Implementation and validation sequence

A future implementation agent should use this as one batch's checklist, but work in verifiable stages:

1. Fix or verify all 59 vanilla-data/reuse entries, including metadata, aliases, and ancillary call restrictions. Add coverage that distinguishes damage-only placeholders from complete effects.
2. Build shared small predicates and parameterized families, then implement easy entries. Port the reviewed Ceaseless Edge pattern rather than importing an unrelated module architecture.
3. Add medium event chains and resident state services, with explicit reset/lifetime tests before adding their consumers.
4. Address hard systemic dependencies first, then enable their moves. If a system or adaptation decision is missing, report the exact blocked behavior; do not count ordinary damage fallback as completion.
5. Run W2 dynamic/B2 static builds, registry/export/import/package checks, and the existing Mega/vanilla/nonbattle/overlay/PWAN regressions. Do not perform browser-emulator testing unless requested; user-run battle testing remains a valid separate acceptance step.

Current implementation scope excludes Hard entries and effects requiring doubles-format validation. At the user's request, native-data effects and exact existing-handler reuse get source/build checks, not separate per-move emulator suites. New custom logic gets focused singles tests for the affected interactions. The per-entry case lists below remain research checklists, not claims that those tests were performed or instructions to override this narrower scope.

Loader acceptance must include a custom move present but unused, two users sharing one group, called moves acquiring another group, a missing/corrupt module, and repeated battles with unload/reload at different addresses. Every teardown must return child counts/current bytes to zero with no retained pointers.

Production heap is the patched **164 KiB**, using stripped RPMs. Re-audit core fixed bytes and every child after this batch; include PWAN Battle, Battle Log, allocation overhead, dependencies, and any new resident history. Check both legal encounters and a conservative loaded-group scenario with at least 12 KiB headroom. Loading children temporarily uses expanded sizes before relocation/shrink, so fixed totals alone do not establish successful load-time allocation. This document contains no fresh size measurements or acceptance claims.

Useful existing target names, subject to the current build configuration:

```sh
ninja -C build-stripped src/stage_w2u_battle_modules.stamp
ninja -C build-stripped src/white2upgrade-battle-heap-audit.json
ninja -C build-stripped src/Black2Upgrade.dll
ninja -C build-stripped src/black2upgrade-compatibility.json
```

## Move index

The full complexity label for “Already Supported” is “Already Supported by vanilla Gen 5 engine.” Module assignments below are proposed placements; “vanilla data” and “vanilla reuse” do not request a new child DLL.

### Generation VIII index

| Move | ID | Complexity | Proposed route |
| --- | ---: | --- | --- |
| [Apple Acid](#apple-acid) | 787 | Already Supported | `vanilla data` |
| [Astral Barrage](#astral-barrage) | 825 | Already Supported | `vanilla data` |
| [Aura Wheel](#aura-wheel) | 783 | Easy | `moves/type` |
| [Barb Barrage](#barb-barrage) | 839 | Easy | `moves/type` |
| [Behemoth Bash](#behemoth-bash) | 782 | Already Supported | `vanilla data` |
| [Behemoth Blade](#behemoth-blade) | 781 | Already Supported | `vanilla data` |
| [Bitter Malice](#bitter-malice) | 841 | Already Supported | `vanilla data` |
| [Bleakwind Storm](#bleakwind-storm) | 846 | Easy | `moves/type` |
| [Body Press](#body-press) | 776 | Medium | `moves/stats` |
| [Bolt Beak](#bolt-beak) | 754 | Easy | `moves/flow` |
| [Branch Poke](#branch-poke) | 785 | Already Supported | `vanilla data` |
| [Breaking Swipe](#breaking-swipe) | 784 | Already Supported | `vanilla data` |
| [Burning Jealousy](#burning-jealousy) | 807 | Medium | `moves/flow` |
| [Ceaseless Edge](#ceaseless-edge) | 845 | Easy | `moves/hazards` |
| [Chloroblast](#chloroblast) | 835 | Medium | `moves/flow` |
| [Clangorous Soul](#clangorous-soul) | 775 | Medium | `moves/stats` |
| [Coaching](#coaching) | 811 | Easy | `moves/stats` |
| [Corrosive Gas](#corrosive-gas) | 810 | Medium | `moves/flow` |
| [Court Change](#court-change) | 756 | Hard | `moves/screens` |
| [Decorate](#decorate) | 777 | Easy | `moves/stats` |
| [Dire Claw](#dire-claw) | 827 | Easy | `moves/type` |
| [Dragon Darts](#dragon-darts) | 751 | Hard | `moves/flow` |
| [Dragon Energy](#dragon-energy) | 820 | Already Supported | `vanilla reuse` |
| [Drum Beating](#drum-beating) | 778 | Already Supported | `vanilla data` |
| [Dual Wingbeat](#dual-wingbeat) | 814 | Already Supported | `vanilla data` |
| [Dynamax Cannon](#dynamax-cannon) | 744 | Easy | `moves/flow` |
| [Eerie Spell](#eerie-spell) | 826 | Medium | `moves/flow` |
| [Esper Wing](#esper-wing) | 840 | Already Supported | `vanilla data` |
| [Eternabeam](#eternabeam) | 795 | Already Supported | `vanilla reuse` |
| [Expanding Force](#expanding-force) | 797 | Medium | `moves/terrain` |
| [False Surrender](#false-surrender) | 793 | Already Supported | `vanilla data` |
| [Fiery Wrath](#fiery-wrath) | 822 | Already Supported | `vanilla data` |
| [Fishious Rend](#fishious-rend) | 755 | Easy | `moves/flow` |
| [Flip Turn](#flip-turn) | 812 | Already Supported | `vanilla reuse` |
| [Freezing Glare](#freezing-glare) | 821 | Already Supported | `vanilla data` |
| [Glacial Lance](#glacial-lance) | 824 | Already Supported | `vanilla data` |
| [Grassy Glide](#grassy-glide) | 803 | Easy | `resident core` |
| [Grav Apple](#grav-apple) | 788 | Easy | `moves/type` |
| [Headlong Rush](#headlong-rush) | 838 | Already Supported | `vanilla data` |
| [Infernal Parade](#infernal-parade) | 844 | Easy | `moves/type` |
| [Jaw Lock](#jaw-lock) | 746 | Medium | `moves/trapping` |
| [Jungle Healing](#jungle-healing) | 816 | Medium | `moves/flow` |
| [Lash Out](#lash-out) | 808 | Medium | `moves/flow` |
| [Life Dew](#life-dew) | 791 | Medium | `moves/flow` |
| [Lunar Blessing](#lunar-blessing) | 849 | Medium | `moves/flow` |
| [Magic Powder](#magic-powder) | 750 | Easy | `moves/type` |
| [Meteor Assault](#meteor-assault) | 794 | Already Supported | `vanilla reuse` |
| [Meteor Beam](#meteor-beam) | 800 | Medium | `moves/terrain` |
| [Misty Explosion](#misty-explosion) | 802 | Easy | `moves/terrain` |
| [Mountain Gale](#mountain-gale) | 836 | Already Supported | `vanilla data` |
| [Mystical Power](#mystical-power) | 832 | Already Supported | `vanilla data` |
| [No Retreat](#no-retreat) | 748 | Medium | `moves/trapping` |
| [Obstruct](#obstruct) | 792 | Easy | `moves/guards` |
| [Octolock](#octolock) | 753 | Medium | `moves/trapping` |
| [Overdrive](#overdrive) | 786 | Already Supported | `vanilla reuse` |
| [Poltergeist](#poltergeist) | 809 | Easy | `moves/flow` |
| [Power Shift](#power-shift) | 829 | Already Supported | `vanilla reuse` |
| [Psyshield Bash](#psyshield-bash) | 828 | Already Supported | `vanilla data` |
| [Pyro Ball](#pyro-ball) | 780 | Already Supported | `vanilla reuse` |
| [Raging Fury](#raging-fury) | 833 | Already Supported | `vanilla reuse` |
| [Rising Voltage](#rising-voltage) | 804 | Easy | `moves/terrain` |
| [Sandsear Storm](#sandsear-storm) | 848 | Easy | `moves/type` |
| [Scale Shot](#scale-shot) | 799 | Easy | `moves/stats` |
| [Scorching Sands](#scorching-sands) | 815 | Already Supported | `vanilla reuse` |
| [Shell Side Arm](#shell-side-arm) | 801 | Hard | `moves/type` |
| [Shelter](#shelter) | 842 | Already Supported | `vanilla reuse` |
| [Skitter Smack](#skitter-smack) | 806 | Already Supported | `vanilla data` |
| [Snap Trap](#snap-trap) | 779 | Medium | `moves/trapping` |
| [Snipe Shot](#snipe-shot) | 745 | Medium | `moves/flow` |
| [Spirit Break](#spirit-break) | 789 | Already Supported | `vanilla data` |
| [Springtide Storm](#springtide-storm) | 831 | Already Supported | `vanilla data` |
| [Steel Beam](#steel-beam) | 796 | Medium | `moves/flow` |
| [Steel Roller](#steel-roller) | 798 | Easy | `moves/terrain` |
| [Stone Axe](#stone-axe) | 830 | Easy | `moves/hazards` |
| [Strange Steam](#strange-steam) | 790 | Already Supported | `vanilla data` |
| [Stuff Cheeks](#stuff-cheeks) | 747 | Medium | `moves/flow` |
| [Surging Strikes](#surging-strikes) | 818 | Already Supported | `vanilla reuse` |
| [Take Heart](#take-heart) | 850 | Easy | `moves/stats` |
| [Tar Shot](#tar-shot) | 749 | Medium | `moves/type` |
| [Teatime](#teatime) | 752 | Hard | `moves/flow` |
| [Terrain Pulse](#terrain-pulse) | 805 | Medium | `moves/terrain` |
| [Thunder Cage](#thunder-cage) | 819 | Medium | `moves/trapping` |
| [Thunderous Kick](#thunderous-kick) | 823 | Already Supported | `vanilla data` |
| [Triple Arrows](#triple-arrows) | 843 | Already Supported | `vanilla data` |
| [Triple Axel](#triple-axel) | 813 | Medium | `moves/flow` |
| [Victory Dance](#victory-dance) | 837 | Already Supported | `vanilla data` |
| [Wave Crash](#wave-crash) | 834 | Already Supported | `vanilla reuse` |
| [Wicked Blow](#wicked-blow) | 817 | Already Supported | `vanilla reuse` |
| [Wildbolt Storm](#wildbolt-storm) | 847 | Easy | `moves/type` |

### Generation IX index

| Move | ID | Complexity | Proposed route |
| --- | ---: | --- | --- |
| [Alluring Voice](#alluring-voice) | 914 | Medium | `moves/flow` |
| [Aqua Cutter](#aqua-cutter) | 895 | Already Supported | `vanilla data` |
| [Aqua Step](#aqua-step) | 872 | Already Supported | `vanilla data` |
| [Armor Cannon](#armor-cannon) | 890 | Already Supported | `vanilla data` |
| [Axe Kick](#axe-kick) | 853 | Easy | `moves/flow` |
| [Bitter Blade](#bitter-blade) | 891 | Already Supported | `vanilla reuse` |
| [Blazing Torque](#blazing-torque) | 896 | Easy | `moves/type` |
| [Blood Moon](#blood-moon) | 901 | Medium | `moves/flow` |
| [Burning Bulwark](#burning-bulwark) | 908 | Easy | `moves/guards` |
| [Chilling Water](#chilling-water) | 886 | Already Supported | `vanilla data` |
| [Chilly Reception](#chilly-reception) | 881 | Hard | `moves/terrain` |
| [Collision Course](#collision-course) | 878 | Easy | `moves/type` |
| [Combat Torque](#combat-torque) | 899 | Easy | `moves/type` |
| [Comeuppance](#comeuppance) | 894 | Already Supported | `vanilla reuse` |
| [Doodle](#doodle) | 867 | Hard | `moves/ability` |
| [Double Shock](#double-shock) | 892 | Easy | `moves/type` |
| [Dragon Cheer](#dragon-cheer) | 913 | Medium | `moves/stats` |
| [Electro Drift](#electro-drift) | 879 | Easy | `moves/type` |
| [Electro Shot](#electro-shot) | 905 | Medium | `moves/terrain` |
| [Fickle Beam](#fickle-beam) | 907 | Easy | `moves/type` |
| [Fillet Away](#fillet-away) | 868 | Medium | `moves/stats` |
| [Flower Trick](#flower-trick) | 870 | Already Supported | `vanilla reuse` |
| [Gigaton Hammer](#gigaton-hammer) | 893 | Medium | `moves/flow` |
| [Glaive Rush](#glaive-rush) | 862 | Medium | `moves/volatile` |
| [Hard Press](#hard-press) | 912 | Easy | `moves/type` |
| [Hydro Steam](#hydro-steam) | 876 | Easy | `moves/type` |
| [Hyper Drill](#hyper-drill) | 887 | Easy | `moves/guards` |
| [Ice Spinner](#ice-spinner) | 861 | Medium | `moves/terrain` |
| [Ivy Cudgel](#ivy-cudgel) | 904 | Medium | `moves/type` |
| [Jet Punch](#jet-punch) | 857 | Already Supported | `vanilla data` |
| [Kowtow Cleave](#kowtow-cleave) | 869 | Already Supported | `vanilla data` |
| [Last Respects](#last-respects) | 854 | Hard | `moves/flow` |
| [Lumina Crash](#lumina-crash) | 855 | Already Supported | `vanilla data` |
| [Magical Torque](#magical-torque) | 900 | Easy | `moves/type` |
| [Make It Rain](#make-it-rain) | 874 | Medium | `moves/flow` |
| [Malignant Chain](#malignant-chain) | 919 | Already Supported | `vanilla data` |
| [Matcha Gotcha](#matcha-gotcha) | 902 | Medium | `moves/flow` |
| [Mighty Cleave](#mighty-cleave) | 910 | Easy | `moves/guards` |
| [Mortal Spin](#mortal-spin) | 866 | Medium | `moves/hazards` |
| [Nihil Light](#nihil-light) | Unassigned | Medium | `moves/type` |
| [Noxious Torque](#noxious-torque) | 898 | Easy | `moves/type` |
| [Order Up](#order-up) | 856 | Hard | `moves/ability` |
| [Population Bomb](#population-bomb) | 860 | Hard | `moves/flow` |
| [Pounce](#pounce) | 884 | Already Supported | `vanilla data` |
| [Psyblade](#psyblade) | 875 | Easy | `moves/terrain` |
| [Psychic Noise](#psychic-noise) | 917 | Medium | `moves/volatile` |
| [Rage Fist](#rage-fist) | 889 | Hard | `moves/flow` |
| [Raging Bull](#raging-bull) | 873 | Medium | `moves/screens` |
| [Revival Blessing](#revival-blessing) | 863 | Hard | `moves/flow` |
| [Ruination](#ruination) | 877 | Already Supported | `vanilla reuse` |
| [Salt Cure](#salt-cure) | 864 | Medium | `moves/volatile` |
| [Shed Tail](#shed-tail) | 880 | Hard | `moves/flow` |
| [Silk Trap](#silk-trap) | 852 | Easy | `moves/guards` |
| [Snowscape](#snowscape) | 883 | Hard | `moves/terrain` |
| [Spicy Extract](#spicy-extract) | 858 | Already Supported | `vanilla data` |
| [Spin Out](#spin-out) | 859 | Already Supported | `vanilla data` |
| [Supercell Slam](#supercell-slam) | 916 | Easy | `moves/flow` |
| [Syrup Bomb](#syrup-bomb) | 903 | Medium | `moves/volatile` |
| [Tachyon Cutter](#tachyon-cutter) | 911 | Already Supported | `vanilla data` |
| [Temper Flare](#temper-flare) | 915 | Easy | `moves/flow` |
| [Tera Blast](#tera-blast) | 851 | Hard | `moves/type` |
| [Tera Starstorm](#tera-starstorm) | 906 | Hard | `moves/type` |
| [Thunderclap](#thunderclap) | 909 | Already Supported | `vanilla reuse` |
| [Tidy Up](#tidy-up) | 882 | Medium | `moves/hazards` |
| [Torch Song](#torch-song) | 871 | Already Supported | `vanilla reuse` |
| [Trailblaze](#trailblaze) | 885 | Already Supported | `vanilla data` |
| [Triple Dive](#triple-dive) | 865 | Already Supported | `vanilla data` |
| [Twin Beam](#twin-beam) | 888 | Already Supported | `vanilla data` |
| [Upper Hand](#upper-hand) | 918 | Medium | `moves/flow` |
| [Wicked Torque](#wicked-torque) | 897 | Easy | `moves/type` |

## Generation VIII move specifications

### Apple Acid

Move ID: 787 (`MOVE_APPLE_ACID`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target and lowers its Special Defense one stage on a successful hit. Use Scarlet/Violet's 80 base power, not Champions' 90. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Apple_Acid_(move)>) (reviewed revision 4614728).

**Implementation:** Use the ordinary damage-plus-target-stat-change effect. No unique event table is needed.

**Focused checks:** Substitute; Clear Body; Sheer Force.

### Astral Barrage

Move ID: 825 (`MOVE_ASTRAL_BARRAGE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary Ghost-type special damage to all adjacent opponents, with no additional effect. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Astral_Barrage_(move)>) (reviewed revision 4577617).

**Implementation:** Configure opponent-spread targeting; do not include allies. The generic spread-damage reduction remains applicable.

**Focused checks:** Singles versus doubles; ally exclusion; Ghost immunity.

### Aura Wheel

Move ID: 783 (`MOVE_AURA_WHEEL`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Only Morpeko, or a Pokémon transformed into Morpeko, can use it successfully. It is Electric in Full Belly Mode and Dark in Hangry Mode, and raises the user's Speed one stage when successful. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Aura_Wheel_(move)>) (reviewed revision 4631991).

**Implementation:** Implemented in `moves/type`: current-species/form eligibility and execution-time typing, retaining native self-Speed metadata. Native Transform keeps the original core species, so a small resident success-tail hook records the copied species in the unused base-param word; the handler reads it only while the native Transform flag is set. Full Belly/Hangry Personal rows exist. Hunger Switch is not implemented by this change; forms are instantiated explicitly in focused fixtures. Normalize and Electrify take precedence, and Ion Deluge can convert Normalize's Normal type. [Primary type-modification reference](https://raw.githubusercontent.com/smogon/pokemon-showdown/master/data/abilities.ts).

**Focused checks:** Both forms; Transform; Mimic by another species; failed hit.

### Barb Barrage

Move ID: 839 (`MOVE_BARB_BARRAGE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** For Scarlet/Violet: damage, a 50% regular-poison chance, and doubled power only when the target is poisoned or badly poisoned. Legends: Arceus instead doubles against any major status and uses a 30% poison chance. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Barb_Barrage_(move)>) (reviewed revision 4593160).

**Implementation:** The resident EventAddHex alias currently doubles against every major status. It is not correct for the proposed Scarlet/Violet rules. Replace that alias with a poison-only power check plus poison metadata; never leave both routes active.

**Focused checks:** Poison versus burn/sleep; Toxic; poison immunity; Sheer Force.

### Behemoth Bash

Move ID: 782 (`MOVE_BEHEMOTH_BASH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary damage under the chosen non-Dynamax rules. Sword/Shield doubled damage against Dynamaxed targets; Scarlet/Violet has no such secondary effect. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Behemoth_Bash_(move)>) (reviewed revision 4636289).

**Implementation:** No custom handler is needed while Dynamax is absent. Excluding Max moves does not exclude this ordinary move.

**Focused checks:** Standard physical damage; no fabricated Dynamax flag.

### Behemoth Blade

Move ID: 781 (`MOVE_BEHEMOTH_BLADE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary damage under non-Dynamax rules. Sword/Shield's double damage against Dynamax is irrelevant without that system. This is a slicing move. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Behemoth_Blade_(move)>) (reviewed revision 4636287).

**Implementation:** Use ordinary damage metadata and the project's sharp/slicing flag. A future Sharpness ability must honor that flag; the flag alone does not implement the ability.

**Focused checks:** Standard damage; slicing metadata.

### Bitter Malice

Move ID: 841 (`MOVE_BITTER_MALICE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: 75-power damage and a guaranteed one-stage Attack reduction on a successful hit. It no longer doubles against status or inflicts frostbite. Those were Legends: Arceus rules. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Bitter_Malice_(move)>) (reviewed revision 4614824).

**Implementation:** Use ordinary damage-plus-target-stat metadata, not Hex. Frostbite is not required for the selected specification.

**Focused checks:** Attack floor; Clear Body; Substitute; no status multiplier.

### Bleakwind Storm

Move ID: 846 (`MOVE_BLEAKWIND_STORM`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Scarlet/Violet: damages all adjacent opponents, with a 30% chance to lower each target's Speed one stage. Rain removes its normal accuracy check, but not semi-invulnerability restrictions. It is wind-based; the Arceus frostbite effect is not used. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Bleakwind_Storm_(move)>) (reviewed revision 4621942).

**Implementation:** Share a rain-accuracy helper with Sandsear and Wildbolt Storm; retain independent per-target secondary rolls. Do not copy Springtide Storm's rain behavior, which differs.

**Focused checks:** Rain versus clear weather; doubles; airborne/semi-invulnerable target.

### Body Press

Move ID: 776 (`MOVE_BODY_PRESS`). Complexity: **Medium**. Proposed route: `moves/stats`.

**Effect:** Calculate physical damage using the user's Defense and Defense stages instead of Attack and Attack stages. Attack-side modifiers such as Huge Power, Choice Band, burn, Slow Start, and Defeatist still apply; Eviolite and Fur Coat do not simply boost its attacking value. Unaware can ignore the substituted stages. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Body_Press_(move)>) (reviewed revision 4629106).

**Implementation:** Replace the attacking stat at the correct damage-calculation layer, not the whole damage formula or category. Preserve physical screens, critical-hit stage handling, and ordinary physical modifiers.

**Focused checks:** Defense stages; burn/Choice Band; Eviolite/Fur Coat; Unaware; critical hit.

### Bolt Beak

Move ID: 754 (`MOVE_BOLT_BEAK`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Power doubles from 85 to 170 if the target has not yet acted this turn, including a target that switched into the battle that turn. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Bolt_Beak_(move)>) (reviewed revision 4577560).

**Implementation:** Share the target-action predicate with Fishious Rend. Read authoritative action state, not speed or whether the user happens to move first. Account for Instruct and other extra actions.

**Focused checks:** Unacted target; previously acted target; switch-in; failed action; extra action.

### Branch Poke

Move ID: 785 (`MOVE_BRANCH_POKE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary physical damage, with no secondary effect. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Branch_Poke_(move)>) (reviewed revision 4623006).

**Implementation:** Set normal move data and flags; no custom event table is necessary.

**Focused checks:** Accuracy; Protect; contact behavior.

### Breaking Swipe

Move ID: 784 (`MOVE_BREAKING_SWIPE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages all adjacent opponents and lowers each successfully hit target's Attack one stage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Breaking_Swipe_(move)>) (reviewed revision 4628034).

**Implementation:** Generic spread targeting and damage-plus-target-stat metadata implement the effect. Do not lower allies' Attack.

**Focused checks:** Doubles spread; one protected opponent; Clear Body; Substitute.

### Burning Jealousy

Move ID: 807 (`MOVE_BURNING_JEALOUSY`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Damages adjacent opponents and burns a target if its stats rose earlier during the current turn. An Imposter transformation does not count. A raise caused after this attack, such as its Weakness Policy activation, cannot retroactively qualify. Sheer Force boosts the move even when the burn condition is false. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Burning_Jealousy_(move)>) (reviewed revision 4628056).

**Implementation:** Add a resident per-battler current-turn stat-rise tracker; share it with Alluring Voice. Snapshot eligibility before this attack's reactions and implement all relevant Sheer Force checks, not just burn suppression.

**Focused checks:** Earlier boost; Weakness Policy; Imposter; doubles; Sheer Force.

### Ceaseless Edge

Move ID: 845 (`MOVE_CEASELESS_EDGE`). Complexity: **Easy**. Proposed route: `moves/hazards`.

**Effect:** After a successful damaging hit, place one layer of Spikes on the opposing side, up to the usual limit. The Scarlet/Violet move is slicing and does not have Arceus's elevated critical rate or splinter damage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Ceaseless_Edge_(move)>) (reviewed revision 4614422).

**Implementation:** PW2Code/Libraries/Moves/CeaselessEdge.cpp supplies the native side-effect work pattern. The implementation uses the per-hit `EVENT_MOVE_DAMAGE_SIDE_AFTER` instead of its real-hit-only end event: Substitute hits count, Parental Bond can add two layers, and contact-punishment KO prevents placement. Native registration supplies the layer cap and permanent condition. Both damaging hazards are explicitly added to all three existing Sheer Force predicates; boosted executions do not place hazards. [Sheer Force reference](<https://bulbapedia.bulbagarden.net/wiki/Sheer_Force_(Ability)>).

**Focused checks:** Hit/miss/Protect; Substitute; three layers; user/target fainting.

### Chloroblast

Move ID: 835 (`MOVE_CHLOROBLAST`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Scarlet/Violet: 150-power damage; when it hits, the user loses half its maximum HP, rounded up. Magic Guard and Rock Head prevent this loss. No ordinary Speed drop is applied. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Chloroblast_(move)>) (reviewed revision 4614539).

**Implementation:** Implemented in `moves/flow`, sharing the rounded-up maximum-HP cost callback with Mind Blown and Steel Beam. Native real-execution damage determination marks a hit, including Substitute and zero-damage Disguise, without marking AI estimates, misses, protection or immunity. The callback charges once at sequence end and uses the effective Rock Head value, so Gastro Acid removes that veto. Native simple damage supplies Magic Guard protection. No Speed-stage drop or ordinary damage-based recoil metadata is added.

**Focused checks:** Odd max HP; miss/Protect; Substitute; Magic Guard; Rock Head.

### Clangorous Soul

Move ID: 775 (`MOVE_CLANGOROUS_SOUL`). Complexity: **Medium**. Proposed route: `moves/stats`.

**Effect:** Spend one third of the user's maximum HP and raise Attack, Defense, Special Attack, Special Defense, and Speed one stage each. Fail when HP is insufficient or every affected stat is already at its cap. It is sound-based. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Clangorous_Soul_(move)>) (reviewed revision 4577547).

**Implementation:** Use one atomic eligibility/cost step and queued stat changes. Verify the exact integer rounding and whether HP equal to the cost fails; do not deduct HP again per stat. Sound and Throat Chop integration must be explicit.

Integration policy: the shared `moves/stats` handler uses 33% of maximum HP,
rounded down with a minimum payment of one, matching the reviewed
[turn-based reference implementation](https://github.com/smogon/pokemon-showdown/blob/master/data/moves.ts).
Thus 175 maximum HP pays 57, rather than the 58 from integer division by three.
This resolves the reference's broad "one third" description explicitly; it is
not a claim of extracting the original Sword/Shield integer formula. Equal or
lower remaining HP fails. Eligibility considers effective Contrary before
queuing native Simple/Contrary-aware stat work. Native direct HP payment cannot
be canceled by Magic Guard or Rock Head; berries react after the boosts. Snatch
uses the actual executor's HP and stats. Existing sound/dance flags are retained.

**Focused checks:** HP at boundary; mixed capped stats; all capped; Contrary; Throat Chop.

### Coaching

Move ID: 811 (`MOVE_COACHING`). Complexity: **Easy**. Proposed route: `moves/stats`.

**Effect:** Raises allies' Attack and Defense one stage each, excluding the user and allies currently semi-invulnerable. It bypasses protection, including Crafty Shield. It fails with no eligible ally, including singles. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Coaching_(move)>) (reviewed revision 4628079).

**Implementation:** Use ally-only target resolution and normal stat-change work, with explicit guard bypass rather than a Helping Hand alias. Preserve multi-battle ownership and adjacency rules.

**Focused checks:** Singles; doubles ally; Crafty Shield; semi-invulnerability; Contrary.

### Corrosive Gas

Move ID: 810 (`MOVE_CORROSIVE_GAS`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Destroy affected targets' held items for the rest of the battle, including across switching. These items cannot be restored by Recycle or Harvest. Substitute, Sticky Hold, and protected species-linked items can block removal. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Corrosive_Gas_(move)>) (reviewed revision 4628091).

**Implementation:** Distinguish destruction from consumption, temporary suppression, and Knock Off flags. Cover the surrounding-target mask and item-trigger ordering. Bulbapedia leaves some plate/mask interactions unresolved; choose and document them only after verification.

**Focused checks:** Recycle/Harvest; Sticky Hold; Substitute; allies; unremovable items.

### Court Change

Move ID: 756 (`MOVE_COURT_CHANGE`). Complexity: **Hard**. Proposed route: `moves/screens`.

**Effect:** Exchange the two sides' eligible conditions, including screens, Aurora Veil, hazards, Tailwind, Mist, Safeguard, and pledge effects. Preserve durations and layers. Switching hazards between sides does not immediately damage active Pokémon. Scarlet/Violet allows Defiant/Competitive on a later switch-in to Sticky Web swapped back to its source's side. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Court_Change_(move)>) (reviewed revision 4630638).

**Implementation:** Implement a reviewed side-condition transaction through core services. Swap event ownership, counters, and custom Sticky Web/Aurora Veil state together; copying only a bitmask leaves stale event pointers. Do not exchange weather, terrain, personal volatiles, or stat stages.

**Focused checks:** Asymmetric layers/durations; custom screens; repeated swaps; future switch-in; doubles.

### Decorate

Move ID: 777 (`MOVE_DECORATE`). Complexity: **Easy**. Proposed route: `moves/stats`.

**Effect:** Raises the target's Attack and Special Attack two stages. It bypasses ordinary Protect-style shields but not Crafty Shield, Substitute, or semi-invulnerability. It is not reflected by Magic Bounce. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Decorate_(move)>) (reviewed revision 4630636).

**Implementation:** Use two ordinary boosts with a narrow protection exception; do not globally disable protection for status moves or reuse Coaching's broader bypass.

**Focused checks:** Protect versus Crafty Shield; Substitute; Contrary; Magic Bounce.

### Dire Claw

Move ID: 827 (`MOVE_DIRE_CLAW`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Scarlet/Violet: a 50% total chance to inflict one of poison, paralysis, or sleep, with an equal choice among those statuses. It has no elevated critical rate. Champions instead uses 30%, and Arceus differs. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Dire_Claw_(move)>) (reviewed revision 4577630).

**Implementation:** `DireClawHandlers` in `moves/type` runs on the per-target damage-reaction event. It queries the native secondary-chance event, preserving Serene Grace, rainbow, Shield Dust and Sheer Force, then rolls activation before one uniform status choice. Native condition work applies that choice without rerolling; the handler additionally checks modern Electric-type paralysis immunity. Damage-plus-status metadata enables native Sheer Force, but the status field stays `NONE` to avoid a second fixed ailment. Generic one-status metadata alone is insufficient.

**Focused checks:** Probability distribution; poison/paralysis immunity; existing status; Shield Dust; Sheer Force.

### Dragon Darts

Move ID: 751 (`MOVE_DRAGON_DARTS`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** Two strikes. In doubles against opponents, normally one hits each foe; redirect both to the other if one would be immune, protected, semi-invulnerable, or missed. Targeting an ally sends both strikes there. Follow Me can force both even into immunity; Wide Guard does not block it. Pressure is counted per targeted foe. Called Prankster/Dark immunity also affects rerouting. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Dragon_Darts_(move)>) (reviewed revision 4621909).

**Implementation:** Requires per-strike target planning without duplicate accuracy rolls or side effects during preflight. Bulbapedia explicitly leaves Substitute, Ice Face, Mold Breaker, Ally Switch, and some both-immune interactions unresolved; resolve these separately.

**Focused checks:** Singles/doubles; one immune/protected foe; Follow Me; Pressure; accuracy reroute.

### Dragon Energy

Move ID: 820 (`MOVE_DRAGON_ENERGY`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** An Eruption-style spread attack: power is proportional to the user's current HP, using the 150-power scale and a minimum of one. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Dragon_Energy_(move)>) (reviewed revision 4621941).

**Implementation:** Clone/reuse vanilla Eruption or Water Spout's power calculation with Dragon-type move data. Verify the alias does not hardcode the original move ID or power.

**Focused checks:** Full/half/one HP; spread penalty; HP change before action.

### Drum Beating

Move ID: 778 (`MOVE_DRUM_BEATING`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target and lowers its Speed one stage on a successful hit. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Drum_Beating_(move)>) (reviewed revision 4631988).

**Implementation:** Use ordinary target-stat-change metadata. The name does not make this a sound move; copy the page's actual flags rather than guessing from the name.

**Focused checks:** Clear Body; Substitute; Sheer Force.

### Dual Wingbeat

Move ID: 814 (`MOVE_DUAL_WINGBEAT`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Exactly two strikes, each using the same base power. Usual multi-hit rules apply to critical hits, contact effects, Substitute breaking, and survival items. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Dual_Wingbeat_(move)>) (reviewed revision 4628129).

**Implementation:** Set the generic hit-count minimum and maximum to two, using the existing double-hit pipeline rather than two manually queued attacks.

**Focused checks:** Substitute breaks on first hit; contact twice; Focus Sash; second-hit KO.

### Dynamax Cannon

Move ID: 744 (`MOVE_DYNAMAX_CANNON`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Ordinary damage in Scarlet/Violet, which has no Dynamax. Sword/Shield doubled damage against Dynamaxed targets. Bulbapedia also records that Encore fails when this was the target's last move. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Dynamax_Cannon_(move)>) (reviewed revision 4636288).

**Implementation:** No Dynamax implementation is needed. Audit the Encore exception and its version applicability, then extend the resident Encore eligibility policy if required; do not silently assume ordinary damage means no ancillary restrictions.

**Focused checks:** Damage; Encore last-move check; no Dynamax emulation.

### Eerie Spell

Move ID: 826 (`MOVE_EERIE_SPELL`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Damages the target and removes up to three PP from its last used move in the battle, if any. Do not remove PP if that target faints from the damage. It is sound-based and bypasses Substitute. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Eerie_Spell_(move)>) (reviewed revision 4614713).

**Implementation:** Reuse reviewed move-history services and Spite-style PP work, keyed to a move still present in the target's set. The source flags unresolved history behavior across Truant, switching, Transform, Mimic, Sketch, and move replacement.

**Focused checks:** No history; 0–3 PP; target KO; Substitute; transformed/replaced moves.

### Esper Wing

Move ID: 840 (`MOVE_ESPER_WING`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: damage with an elevated critical-hit rate, followed by a one-stage user Speed increase on success. Arceus action-speed changes are not used. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Esper_Wing_(move)>) (reviewed revision 4614843).

**Implementation:** Use critical-stage metadata plus ordinary damage-and-user-stat metadata. Do not implement action-speed scheduling from Arceus.

**Focused checks:** Critical rate; Speed cap; Contrary; failed hit.

### Eternabeam

Move ID: 795 (`MOVE_ETERNABEAM`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Hyper Beam-style damage followed by a recharge turn after a successful hit. A miss, immunity, or protection does not cause recharge under the usual engine rule. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Eternabeam_(move)>) (reviewed revision 4614214).

**Implementation:** Reuse the vanilla recharge pipeline and move metadata. This is an ordinary move even though its name is associated with Eternatus.

**Focused checks:** Hit versus miss/Protect/immunity; KO; Instruct/Encore restrictions.

### Expanding Force

Move ID: 797 (`MOVE_EXPANDING_FORCE`). Complexity: **Medium**. Proposed route: `moves/terrain`.

**Effect:** When the user is grounded in Psychic Terrain, power increases by 50% and the move targets all adjacent opponents. Otherwise it remains a normal single-target attack. The terrain's ordinary Psychic damage bonus is additional. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Expanding_Force_(move)>) (reviewed revision 4628144).

**Implementation:** Determine both power and target mask at execution, without modifying shared move records. Use the core terrain/grounding services; changing only power misses its doubles behavior.

**Focused checks:** Grounded versus airborne user; terrain replaced mid-turn; singles/doubles; spread penalty.

### False Surrender

Move ID: 793 (`MOVE_FALSE_SURRENDER`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Always hits unless a target is in a normally untargetable semi-invulnerable state; it does not override type immunity or Protect. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/False_Surrender_(move)>) (reviewed revision 4614791).

**Implementation:** Use the engine's must-hit accuracy value, as for Aerial Ace. Do not globally force successful damage or bypass guards.

**Focused checks:** Evasion boosts; Protect; immunity; Fly/Dig.

### Fiery Wrath

Move ID: 822 (`MOVE_FIERY_WRATH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages adjacent opponents with a 20% flinch chance for each successfully hit target. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Fiery_Wrath_(move)>) (reviewed revision 4620156).

**Implementation:** Use normal spread targeting and flinch metadata; apply independent secondary rolls and the usual first-action/Inner Focus rules.

**Focused checks:** Doubles; one protected target; Inner Focus; Sheer Force.

### Fishious Rend

Move ID: 755 (`MOVE_FISHIOUS_REND`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Power doubles from 85 to 170 when the target has not yet acted that turn, including a newly switched-in target. It is biting, so Strong Jaw can increase its power. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Fishious_Rend_(move)>) (reviewed revision 4577551).

**Implementation:** Share Bolt Beak's action-state predicate while retaining separate biting metadata. Do not use relative speed as a substitute for turn history.

**Focused checks:** Switch-in; already acted; Strong Jaw; Instruct.

### Flip Turn

Move ID: 812 (`MOVE_FLIP_TURN`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Deals damage and then lets the user switch out, like U-turn. The switch can bypass trapping, but does not occur after a miss, immunity, or when no usable replacement exists. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Flip_Turn_(move)>) (reviewed revision 4628166).

**Implementation:** Reuse U-turn's damage-and-switch pipeline rather than queueing a second action. Preserve Eject Button/Red Card ordering; later-game changes to that interaction need a separate ruleset decision.

**Focused checks:** Trap; miss; no bench; target Eject Button; user forced out.

### Freezing Glare

Move ID: 821 (`MOVE_FREEZING_GLARE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target with a 10% chance of ordinary freeze. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Freezing_Glare_(move)>) (reviewed revision 4614196).

**Implementation:** Use generic freeze secondary metadata. This is not frostbite under the chosen turn-based specification.

**Focused checks:** Freeze immunity; existing status; Shield Dust; Sheer Force.

### Glacial Lance

Move ID: 824 (`MOVE_GLACIAL_LANCE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary physical Ice damage to adjacent opponents. Scarlet/Violet lowered base power from Sword/Shield's 130 to 120. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Glacial_Lance_(move)>) (reviewed revision 4614850).

**Implementation:** Use generic spread damage and the selected version's move data; no unique event handler is required.

**Focused checks:** Power value; spread penalty; ally exclusion.

### Grassy Glide

Move ID: 803 (`MOVE_GRASSY_GLIDE`). Complexity: **Easy**. Route: `resident core`.

**Effect:** Gets +1 priority when the user is grounded in Grassy Terrain. Base power changed from 70 in Sword/Shield to 60 initially in Scarlet/Violet, then 55 in its DLC update. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Grassy_Glide_(move)>) (reviewed revision 4628215).

**Implementation:** Use the current Scarlet/Violet value of 55. Native action sorting queries priority before registering temporary move events, so this adjustment belongs in the existing resident transient field tracker, not a move-specific child callback. Read the actual attacker from the event rather than the field event's owner. Preserve native priority-blocking checks; terrain changes after sorting do not themselves re-sort the native action queue.

**Focused checks:** Grounded/airborne; terrain changes; Psychic Terrain; Queenly Majesty.

### Grav Apple

Move ID: 788 (`MOVE_GRAV_APPLE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Damages the target and lowers Defense one stage. Gravity additionally multiplies its power by 1.5. Use Scarlet/Violet's 80 base power, not Champions' 90. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Grav_Apple_(move)>) (reviewed revision 4593168).

**Implementation:** Configure the Defense secondary normally, then add a Gravity-dependent power multiplier. Do not confuse Gravity with terrain or user grounding.

**Focused checks:** Gravity on/off; Clear Body; Sheer Force; rounding.

### Headlong Rush

Move ID: 838 (`MOVE_HEADLONG_RUSH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Deals damage, then lowers the user's Defense and Special Defense one stage each, as Close Combat does. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Headlong_Rush_(move)>) (reviewed revision 4614380).

**Implementation:** Reuse the ordinary self-stat-drop effect or Close Combat handler with Ground-type data.

**Focused checks:** Contrary; stat floor; successful hit versus immunity; contact.

### Infernal Parade

Move ID: 844 (`MOVE_INFERNAL_PARADE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Scarlet/Violet: 60-power damage, doubled if the target has any major status, plus a 30% burn chance. Champions uses 65 power; Arceus uses different values. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Infernal_Parade_(move)>) (reviewed revision 4628599).

**Implementation:** Combine the vanilla Hex power rule with ordinary burn metadata. This is unlike Scarlet/Violet Barb Barrage, which doubles only for poison.

**Focused checks:** Burn/sleep/poison; doubling and burn chance; Shield Dust; Sheer Force.

### Jaw Lock

Move ID: 746 (`MOVE_JAW_LOCK`). Complexity: **Medium**. Proposed route: `moves/trapping`.

**Effect:** After damaging a target, traps both user and target until either leaves the field. Do not add the mutual trap if either is already trapped. Switching items, forced switches, Wimp Out/Emergency Exit, Shed Shell, and modern Ghost escape can bypass it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Jaw_Lock_(move)>) (reviewed revision 4628300).

**Implementation:** Extend Anchor Shot's source-linked trap into a two-endpoint condition. Clearing one endpoint must release the other; do not use two unrelated permanent Mean Look flags.

**Focused checks:** Either endpoint switches/faints; existing trap; Ghost; Shed Shell; forced switch.

### Jungle Healing

Move ID: 816 (`MOVE_JUNGLE_HEALING`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Restores up to one quarter of maximum HP to the user and allies, and cures their major status conditions. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Jungle_Healing_(move)>) (reviewed revision 4511658).

**Implementation:** Share a multi-recipient healing/cure helper with Lunar Blessing. Queue the two operations per eligible battler with correct Heal Block/status-only handling; do not heal bench Pokémon as Heal Bell does.

**Focused checks:** User and ally; full HP plus status; Heal Block; fainted/no ally.

### Lash Out

Move ID: 808 (`MOVE_LASH_OUT`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Doubles power from 75 to 150 if the user's stat stages were lowered earlier in the current turn. Direct stage overwrites such as Haze, Clear Smog, and Topsy-Turvy do not qualify. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Lash_Out_(move)>) (reviewed revision 4628303).

**Implementation:** Track applied stage reductions, including self-inflicted ones, in resident turn state. Record actual results after Contrary and prevention, not attempted stat-change requests.

**Focused checks:** Intimidate; self drop; Contrary; blocked drop; Haze; next-turn reset.

### Life Dew

Move ID: 791 (`MOVE_LIFE_DEW`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Restores up to one quarter of maximum HP to the user and allies. Substitute does not block it, but semi-invulnerability can. Allied Water Absorb, Storm Drain, or Dry Skin can trigger their own Water immunity response instead of receiving normal Life Dew healing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Life_Dew_(move)>) (reviewed revision 4589562).

**Implementation:** Use target-aware healing with the Water ability/no-effect pipeline intact. A simple global HP loop would bypass these ability interactions.

**Focused checks:** Substitute; airborne/semi-invulnerable ally; Water Absorb; Storm Drain; Heal Block.

### Lunar Blessing

Move ID: 849 (`MOVE_LUNAR_BLESSING`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Scarlet/Violet: restores one quarter maximum HP to the user and allies and cures major status. Arceus instead healed the user by half and supplied its obscured effect. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Lunar_Blessing_(move)>) (reviewed revision 4523532).

**Implementation:** Share Jungle Healing's reviewed helper and targeting. Do not import Arceus's obscured status or silently interpret it as evasion stages.

**Focused checks:** User/ally; status-only benefit; full HP; Heal Block.

### Magic Powder

Move ID: 750 (`MOVE_MAGIC_POWDER`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Changes the target to pure Psychic while it remains in battle. It fails against an already pure Psychic target, Substitute, RKS System, or a Terastallized target. As powder, Grass types, Overcoat, and Safety Goggles block it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Magic_Powder_(move)>) (reviewed revision 4632221).

**Implementation:** Implemented in `moves/type` using native type-change work/message and switch restoration. Clear the core's added type on successful replacement; an already pure Psychic target fails unless it also has a different added type. Grass immunity includes Forest's Curse and cannot be ignored. PW2Code's updated Overcoat table is ported into `abilities/defense`, preserving native weather protection; the existing scoped ability-ignore policy now includes its powder immunity. Safety Goggles retains its existing item handler. Multitype/Arceus and RKS System remain protected. Tera is not implemented and is outside this handler's scope.

**Focused checks:** 23 singles cases and three follow-ups passed: type replacement and added-type removal, pure Psychic failure, Grass/Overcoat/Goggles immunity, scoped ability ignoring, native Gastro Acid/Embargo, Protect/Substitute/miss, Magic Coat and native switch-away/back restoration. See the [progress tracker](gen8-gen9-move-handler-progress.md) for build and coverage limits.

### Meteor Assault

Move ID: 794 (`MOVE_METEOR_ASSAULT`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Hyper Beam-style damage followed by recharge after a successful hit. Sword/Shield uses 150 base power; Champions changed it to 170. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Meteor_Assault_(move)>) (reviewed revision 4629782).

**Implementation:** Reuse vanilla recharge logic with the Sword/Shield value for this otherwise unavailable Scarlet/Violet move. Do not adopt Champions data accidentally.

**Focused checks:** Successful hit; miss/Protect; fainting; recharge-related restrictions.

### Meteor Beam

Move ID: 800 (`MOVE_METEOR_BEAM`). Complexity: **Medium**. Proposed route: `moves/terrain`.

**Effect:** Two-turn attack that raises the user's Special Attack during charging. Power Herb gives the boost and then attacks immediately in the same turn. Charging prevents ordinary switching; disruption can postpone rather than discard the attack. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Meteor_Beam_(move)>) (reviewed revision 4621929).

**Implementation:** Adapt the established charge/attack flow, not Beak Blast's start-of-turn charge queue. The boost and charge animation must each happen exactly once; preserve PP and move-history timing.

**Focused checks:** Two turns; Power Herb; sleep/flinch on attack turn; called move; charge animation.

### Misty Explosion

Move ID: 802 (`MOVE_MISTY_EXPLOSION`). Complexity: **Easy**. Proposed route: `moves/terrain`.

**Effect:** Explosion-like damage and user fainting; power is multiplied by 1.5 if the user is grounded in Misty Terrain. Damp prevents the attack and the self-faint. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Misty_Explosion_(move)>) (reviewed revision 4628348).

**Implementation:** Reuse Explosion's eligibility and self-KO handling with a terrain power hook. The terrain bonus is based on the user, not whether targets are grounded.

**Focused checks:** Damp; airborne user; terrain changed; Protect; spread damage.

### Mountain Gale

Move ID: 836 (`MOVE_MOUNTAIN_GALE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: damage with a 30% flinch chance, using 100 base power. Arceus's action-speed penalty is not a conventional stat drop; Champions uses 120 power. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Mountain_Gale_(move)>) (reviewed revision 4618753).

**Implementation:** Use normal flinch metadata under the Scarlet/Violet specification.

**Focused checks:** Inner Focus; moved target; Sheer Force; selected base power.

### Mystical Power

Move ID: 832 (`MOVE_MYSTICAL_POWER`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: damages the target and raises the user's Special Attack one stage on success. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Mystical_Power_(move)>) (reviewed revision 4527955).

**Implementation:** Use ordinary damage-plus-user-stat-change metadata. Arceus's temporary stat system is not part of this port.

**Focused checks:** Contrary; capped Special Attack; miss; Substitute.

### No Retreat

Move ID: 748 (`MOVE_NO_RETREAT`). Complexity: **Medium**. Proposed route: `moves/trapping`.

**Effect:** Raises all five core stats one stage and prevents the user from voluntarily leaving. Shed Shell, switch-triggering items, phazing, and Ghost escape can bypass the trap. Sword/Shield allowed repeat boosts if another effect already trapped the user; Champions instead allows only one successful use per switch-in. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/No_Retreat_(move)>) (reviewed revision 4622966).

**Implementation:** For this move absent from Scarlet/Violet, retain the Sword/Shield rule and a separate No Retreat-used condition. Bulbapedia leaves the all-stats-capped case unresolved; verify before choosing failure versus trap-only behavior.

**Focused checks:** Already trapped; repeat use; Ghost; Shed Shell; all stats capped; switch reset.

### Obstruct

Move ID: 792 (`MOVE_OBSTRUCT`). Complexity: **Easy**. Proposed route: `moves/guards`.

**Effect:** Protects from damaging moves, not status moves. A blocked contact attacker loses two Defense stages. It shares consecutive-use diminishing success with protection moves; an otherwise immune contact move can still trigger the drop. It fails if the user acts last; each consecutive qualifying protection divides success probability by three. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Obstruct_(move)>) (reviewed revision 4621927).

**Implementation:** Implemented in `moves/guards` with the shared damage-only shield table and a child-owned position event. Native protection work handles activation, last-action failure and the shared counter. The resident start hook recognizes native and custom protection moves in both chaining directions. The immunity callback retains an otherwise immune, genuinely blocked target until the protection pass; bypass moves retain their real immunity. Native stat work applies Defense -2, including prevention/Contrary. Blocked contact does not also trigger Rocky Helmet/Rough Skin. Global BW2 protection success odds are retained, not upgraded to the modern one-third rule. Obstruct is excluded from Instruct.

**Focused checks:** Contact/noncontact; status move; immunity; repeated Protect; Contrary.

### Octolock

Move ID: 753 (`MOVE_OCTOLOCK`). Complexity: **Medium**. Proposed route: `moves/trapping`.

**Effect:** Traps the target, then lowers its Defense and Special Defense one stage each at the end of every turn. The effect ends when the source leaves battle. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Octolock_(move)>) (reviewed revision 4628633).

**Implementation:** Combine a source-linked trap with a subordinate end-turn event. Keep the module loaded for the battle; clear the event on source/target departure, and use normal stat-change immunity/reflection rules.

**Focused checks:** First end turn; source departure; Substitute; Clear Body; Mirror Armor; doubles.

### Overdrive

Move ID: 786 (`MOVE_OVERDRIVE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Ordinary Electric special damage to adjacent opponents. It is sound-based and can hit through Substitute. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Overdrive_(move)>) (reviewed revision 4634803).

**Implementation:** Use generic spread damage plus Soundproof/sound flags and reuse vanilla HandlerBypassSubstitute if the global sound path does not already supply bypass. A sound flag alone is not proof that Gen 6+ bypass is wired.

**Focused checks:** Soundproof; Substitute; Throat Chop; Liquid Voice; doubles.

### Poltergeist

Move ID: 809 (`MOVE_POLTERGEIST`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Fails if the target is not holding an item. Otherwise it announces the item and damages normally; Kasib Berry, Weakness Policy, or Red Card can activate without retroactively canceling the hit. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Poltergeist_(move)>) (reviewed revision 4622994).

**Implementation:** Snapshot item eligibility before hit reactions, then use normal item processing. Do not continuously recheck held-item presence after consumption.

**Focused checks:** No item; Knock Off earlier; Kasib Berry; Weakness Policy; Red Card.

### Power Shift

Move ID: 829 (`MOVE_POWER_SHIFT`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** In its Generation IX form, exchanges the user's underlying Attack and Defense, without exchanging their stages or ordinary in-battle modifiers. Arceus also exchanged Special Attack and Special Defense; that is not the selected rule. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Power_Shift_(move)>) (reviewed revision 4636326).

**Implementation:** Clone/reuse Power Trick's raw-stat swap for the Generation IX version. Verify switch, Transform, and repeated-use restoration through the existing stat service.

**Focused checks:** Two uses; Attack/Defense stages unchanged; switch; Transform.

### Psyshield Bash

Move ID: 828 (`MOVE_PSYSHIELD_BASH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: damages the target and raises the user's Defense one stage. Use its 70 base power rather than Champions' 90. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Psyshield_Bash_(move)>) (reviewed revision 4593171).

**Implementation:** Use ordinary damage-and-user-stat metadata. Do not port Arceus's temporary defensive-stat abstraction.

**Focused checks:** Contrary; capped Defense; successful hit.

### Pyro Ball

Move ID: 780 (`MOVE_PYRO_BALL`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Deals damage with a 10% burn chance and thaws the user when used. Bulletproof blocks it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Pyro_Ball_(move)>) (reviewed revision 4628394).

**Implementation:** Use ordinary burn metadata, bullet tagging, and the vanilla thaw-user behavior used by compatible moves. User thaw and target thaw are separate checks; verify the available thaw handler is not hardcoded to its original ID.

**Focused checks:** Frozen user; Bulletproof; miss; burn immunity.

### Raging Fury

Move ID: 833 (`MOVE_RAGING_FURY`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Scarlet/Violet: Thrash-style consecutive attacks for two or three turns, followed by confusion, with the usual interruption and lock rules. Arceus's fixation effect is not used. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Raging_Fury_(move)>) (reviewed revision 4636321).

**Implementation:** Reuse the vanilla Thrash/Outrage rampage pipeline. Apply the chosen generation's Instruct exception separately; modern Instruct allows Raging Fury while excluding many other consecutive moves.

**Focused checks:** Two/three turns; confusion; interruption; switching; Instruct.

### Rising Voltage

Move ID: 804 (`MOVE_RISING_VOLTAGE`). Complexity: **Easy**. Proposed route: `moves/terrain`.

**Effect:** Power doubles from 70 to 140 when Electric Terrain is active and the target is grounded. The user need not be grounded for this extra multiplier. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Rising_Voltage_(move)>) (reviewed revision 4628433).

**Implementation:** Use target grounding in the power hook, separately from the terrain's ordinary user-grounded Electric damage bonus.

**Focused checks:** Airborne user/grounded target; inverse case; terrain removed; doubles.

### Sandsear Storm

Move ID: 848 (`MOVE_SANDSEAR_STORM`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Scarlet/Violet: damages adjacent opponents with a 20% burn chance. Rain makes the accuracy check automatic except for normal semi-invulnerability. It is wind-based. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Sandsear_Storm_(move)>) (reviewed revision 4621944).

**Implementation:** Share the storm rain-accuracy helper and use ordinary spread/burn metadata. Do not carry over Arceus's alternate effect probabilities or action-speed values.

**Focused checks:** Rain; semi-invulnerability; per-target burn; Sheer Force.

### Scale Shot

Move ID: 799 (`MOVE_SCALE_SHOT`). Complexity: **Easy**. Proposed route: `moves/stats`.

**Effect:** Hits two to five times, then raises the user's Speed one stage and lowers Defense one stage. These self changes occur once for the whole sequence and are not removed by Sheer Force. Skill Link supplies five hits; Loaded Dice matters only if that item is implemented. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Scale_Shot_(move)>) (reviewed revision 4628446).

**Implementation:** Reuse vanilla multi-hit distribution and add a once-per-sequence self-stat step. Avoid attaching the boosts to a per-hit event, or each strike will repeat them. Preserve the 35%/35%/15%/15% distribution for two/three/four/five hits.

The implemented record uses 25 power and 90% accuracy. It omits generic
damage-plus-user-stat metadata, which runs per strike; the managed handler
uses the successful whole-sequence event that also includes Substitute hits.

**Focused checks:** 2–5 hits; Skill Link; Substitute; early KO; Contrary; Sheer Force.

### Scorching Sands

Move ID: 815 (`MOVE_SCORCHING_SANDS`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Deals damage with a 30% burn chance. Like Scald, it thaws the user before attempting the move and thaws a frozen target it hits. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Scorching_Sands_(move)>) (reviewed revision 4628402).

**Implementation:** Clone/reuse Scald's thaw behavior with Ground-type data and burn metadata. Confirm both thaw paths and the no-target/miss ordering rather than relying only on the defrost-target flag.

**Focused checks:** Frozen user; missed move; frozen target; immunity; Sheer Force.

### Shell Side Arm

Move ID: 801 (`MOVE_SHELL_SIDE_ARM`). Complexity: **Hard**. Proposed route: `moves/type`.

**Effect:** Chooses physical versus special by comparing Attack/Defense with Special Attack/Special Defense using raw stats and stages, not other modifiers; a tie is random. Physical use makes contact, special use does not. It has a 20% poison chance. Wonder Room's stat/stage interaction requires care. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Shell_Side_Arm_(move)>) (reviewed revision 4615223).

**Implementation:** Resolve category and contact dynamically for this action without mutating shared move data. Category must be visible to screens, Counter/Mirror Coat, abilities, animation, and per-hit reactions.

**Focused checks:** Tie RNG; stages; Wonder Room; Choice items; physical contact; special noncontact.

### Shelter

Move ID: 842 (`MOVE_SHELTER`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Scarlet/Violet: raises the user's Defense two stages. Arceus's obscured effect is not part of this rule. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Shelter_(move)>) (reviewed revision 4578281).

**Implementation:** Reuse Iron Defense's ordinary two-stage boost.

**Focused checks:** Defense cap; Contrary; Snatch where applicable.

### Skitter Smack

Move ID: 806 (`MOVE_SKITTER_SMACK`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target and lowers Special Attack one stage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Skitter_Smack_(move)>) (reviewed revision 4628484).

**Implementation:** Use normal damage-plus-target-stat metadata.

**Focused checks:** Clear Body; Substitute; Contrary; Sheer Force.

### Snap Trap

Move ID: 779 (`MOVE_SNAP_TRAP`). Complexity: **Medium**. Proposed route: `moves/trapping`.

**Effect:** Damages and binds the target for four or five turns, with one eighth maximum HP lost each turn. Grip Claw gives seven turns; Binding Band boosts residual to one sixth maximum HP. The source's departure ends the bind. Sword/Shield's move is Grass, whereas Champions changed it to Steel. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Snap_Trap_(move)>) (reviewed revision 4593358).

**Implementation:** Reuse the bind event structure, but audit its residual constants: vanilla Gen 5 uses a different baseline. Do not call this an exact Bind alias until modern fractions and item modifiers are implemented. Retain Sword/Shield's Grass typing.

**Focused checks:** 4/5/7 turns; Binding Band; source switch; Ghost escape; residual rounding.

### Snipe Shot

Move ID: 745 (`MOVE_SNIPE_SHOT`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Has an elevated critical rate and ignores move/ability redirection such as Follow Me, Rage Powder, and Storm Drain. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Snipe_Shot_(move)>) (reviewed revision 4629693).

**Implementation:** Bypass only target redirection, not every defensive ability. A target's own Water immunity must remain effective. Account for ally targeting and Pressure after the actual target is settled. Its page documents legacy Metronome/Sleep Talk glitches; do not reproduce them without a deliberate compatibility decision.

**Focused checks:** Follow Me; Storm Drain redirect versus targeted immunity; critical hit; doubles.

### Spirit Break

Move ID: 789 (`MOVE_SPIRIT_BREAK`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target and lowers its Special Attack one stage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Spirit_Break_(move)>) (reviewed revision 4614750).

**Implementation:** Use generic damage-plus-target-stat metadata.

**Focused checks:** Clear Body; Substitute; Contrary; Sheer Force.

### Springtide Storm

Move ID: 831 (`MOVE_SPRINGTIDE_STORM`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: damages adjacent opponents with a 30% chance to lower Attack one stage. It is wind-based, but unlike the other three storm moves, rain does not guarantee a hit. Arceus's form-dependent behavior is not used. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Springtide_Storm_(move)>) (reviewed revision 4512124).

**Implementation:** Use generic spread/stat-change metadata. Do not include it in a shared storm helper's rain-accuracy whitelist.

**Focused checks:** Rain still checks accuracy; doubles; Contrary; Sheer Force.

### Steel Beam

Move ID: 796 (`MOVE_STEEL_BEAM`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Deals damage and costs half the user's maximum HP, rounded up. The cost applies on a miss, Protect, or Substitute, but not when there is no target. Magic Guard prevents it; Rock Head and Reckless do not affect it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Steel_Beam_(move)>) (reviewed revision 4628406).

**Implementation:** Wired to the existing Mind Blown table in `moves/flow`, with shared rounded-up maximum-HP cost. Successful and no-effect target outcomes mark an attempted attack; a no-target rejection does not. The sequence-end callback consumes its native action scratch once and queues native simple damage, preserving Magic Guard but not Rock Head. No ordinary damage-based recoil metadata is added. Focused singles checks cover the rounding correction and contrast this attempt policy with Chloroblast's hit-only policy; spread/terminal-battle completion is not claimed.

**Focused checks:** Odd HP; miss; Protect; no target; Magic Guard; Rock Head.

### Steel Roller

Move ID: 798 (`MOVE_STEEL_ROLLER`). Complexity: **Easy**. Proposed route: `moves/terrain`.

**Effect:** Fails when no terrain is active. On a successful hit, removes the current terrain. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Steel_Roller_(move)>) (reviewed revision 4635283).

**Implementation:** `moves/terrain` checks the current terrain at execution and removes it through the resident service after a successful whole-sequence hit, including Substitute. Misses, protection and immunity do not remove it. The service also requests the existing deferred graphics reset; this is not visual validation.

**Focused checks:** No terrain; Protect; immunity; Substitute; terrain renderer cleanup.

### Stone Axe

Move ID: 830 (`MOVE_STONE_AXE`). Complexity: **Easy**. Proposed route: `moves/hazards`.

**Effect:** After damaging the target, places Stealth Rock on the opposing side. Scarlet/Violet treats it as slicing, without Arceus's elevated critical rate or splinter damage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Stone_Axe_(move)>) (reviewed revision 4578322).

**Implementation:** Shares Ceaseless Edge's callback in `moves/hazards`, selecting native Stealth Rock work and announcement. The native one-layer cap is retained; existing rocks do not prevent the damaging move from succeeding. No custom entry-damage model or new module is added.

**Focused checks:** Already present rocks; miss/Protect; Substitute; target KO; doubles.

### Strange Steam

Move ID: 790 (`MOVE_STRANGE_STEAM`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Deals damage with a 20% confusion chance. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Strange_Steam_(move)>) (reviewed revision 4533590).

**Implementation:** Use the vanilla confusion secondary effect and move data; no unique table is needed.

**Focused checks:** Own Tempo; Substitute; Shield Dust; Sheer Force.

### Stuff Cheeks

Move ID: 747 (`MOVE_STUFF_CHEEKS`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** The user eats its held Berry, receiving the normal Berry effect, and gains two Defense stages. It cannot be selected without a Berry and rechecks at execution. It can consume a Berry despite Unnerve or Magic Room, even when its normal activation condition is unmet. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Stuff_Cheeks_(move)>) (reviewed revision 4628410).

**Implementation:** Use the existing item consumption and consumed-Berry tracking services, preserving Cheek Pouch/Recycle/Belch interactions. Do not just delete the item and queue Defense boosts.

**Focused checks:** No Berry; stolen before action; Unnerve; Magic Room; full-HP healing Berry; Cheek Pouch.

### Surging Strikes

Move ID: 818 (`MOVE_SURGING_STRIKES`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Exactly three same-power strikes; each is a guaranteed critical hit unless Battle Armor, Shell Armor, or an equivalent critical blocker prevents it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Surging_Strikes_(move)>) (reviewed revision 4622938).

**Implementation:** Use fixed three-hit metadata plus the vanilla Storm Throw/Frost Breath forced-critical rule. The same generic pipeline must execute contact and survival reactions separately for each hit.

**Focused checks:** Armor ability; contact three times; Substitute; Focus Sash; early KO.

### Take Heart

Move ID: 850 (`MOVE_TAKE_HEART`). Complexity: **Easy**. Proposed route: `moves/stats`.

**Effect:** Scarlet/Violet: raises the user's Special Attack and Special Defense one stage each and cures its major status condition. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Take_Heart_(move)>) (reviewed revision 4614830).

**Implementation:** Combine Calm Mind-style stat work with a user status-cure step. Either benefit can remain useful when the other is unavailable; avoid incorrectly making full stats or no status an unconditional failure.

Implemented in `moves/stats`: uncategorized native stat/cure work, with no new
module or shared state. Native work aggregates success across both boosts and
the cure, supplies Simple/Contrary and stage limits, and targets the executing
user after Snatch. The old Attack/Special Attack metadata was removed.

**Focused checks:** No status; capped stats; Contrary; status-only benefit; Snatch policy.

### Tar Shot

Move ID: 749 (`MOVE_TAR_SHOT`). Complexity: **Medium**. Proposed route: `moves/type`.

**Effect:** Lowers target Speed one stage and applies a field-duration condition doubling Fire effectiveness against it. Repeated use can lower Speed again but cannot repeatedly multiply Fire vulnerability. The altered effectiveness can change Wonder Guard's result. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Tar_Shot_(move)>) (reviewed revision 4630703).

**Implementation:** Store a target volatile and modify effectiveness before immunity/ability checks, rather than simply doubling final damage. Modern Tera has special application/preservation rules, requiring later integration if that system is added.

**Focused checks:** Repeat use; Fire resistance/immunity; Wonder Guard; Clear Body; switch reset.

### Teatime

Move ID: 752 (`MOVE_TEATIME`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** All active eligible Pokémon consume held Berries and receive their effects, even under Unnerve/Magic Room or when normal activation conditions are unmet. It bypasses Substitute but not semi-invulnerability, and fails with no Berry holder. After conversion to Electric by Electrify or Plasma Fists, Volt Absorb, Lightning Rod, and Motor Drive activate instead, even without a Berry. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Teatime_(move)>) (reviewed revision 4578351).

**Implementation:** Implement all-battler item work through the standard item event pipeline, with stable snapshots and explicit converted-type immunity handling. Resolve exact Electrify/Ion Deluge behavior from the source before using a generic Berry loop.

**Focused checks:** Mixed Berries; no holder; Substitute; Unnerve; Electrify/Ion Deluge; absorbers.

### Terrain Pulse

Move ID: 805 (`MOVE_TERRAIN_PULSE`). Complexity: **Medium**. Proposed route: `moves/terrain`.

**Effect:** If the user is grounded on terrain, doubles power from 50 to 100 and changes type to Electric, Grass, Fairy, or Psychic for the terrain. Otherwise it remains Normal. Ordinary terrain bonuses and Mega Launcher can also apply. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Terrain_Pulse_(move)>) (reviewed revision 4628583).

**Implementation:** Implemented in the existing `moves/terrain` group: move-parameter resolution restores the terrain-derived type after ability/position callbacks; a separate base-power callback doubles only for a grounded user on terrain. Electrify and a Normal-only Ion Deluge conversion remain allowed. The shared -ate power helper excludes this move, while native pulse metadata retains Mega Launcher. Shared move data is not mutated. See the progress tracker for focused validation.

**Focused checks:** All terrains; airborne user; Mega Launcher; Normalize/Pixilate; Electrify.

### Thunder Cage

Move ID: 819 (`MOVE_THUNDER_CAGE`). Complexity: **Medium**. Proposed route: `moves/trapping`.

**Effect:** Deals damage, then applies a four- or five-turn binding effect with one eighth maximum HP residual. Grip Claw gives seven turns, Binding Band raises residual to one sixth, and source departure releases the target. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Thunder_Cage_(move)>) (reviewed revision 4621940).

**Implementation:** Share the modernized bind helper with Snap Trap. A direct vanilla Bind alias would retain Gen 5 residual behavior unless separately upgraded.

**Focused checks:** Residual fraction; Binding Band; Grip Claw; source leaves; switching.

### Thunderous Kick

Move ID: 823 (`MOVE_THUNDEROUS_KICK`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target and lowers Defense one stage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Thunderous_Kick_(move)>) (reviewed revision 4614479).

**Implementation:** Use ordinary damage-plus-target-stat metadata.

**Focused checks:** Clear Body; Substitute; Contrary; Sheer Force.

### Triple Arrows

Move ID: 843 (`MOVE_TRIPLE_ARROWS`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: one damaging strike with an elevated critical rate, a 50% chance to lower Defense one stage, and a separate 30% flinch chance. It is not a three-hit move. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Triple_Arrows_(move)>) (reviewed revision 4614616).

**Implementation:** Use independent stat-secondary, flinch, and critical-stage metadata. Ensure the engine evaluates both secondaries independently; do not combine them into a single shared roll.

**Focused checks:** Both/neither secondary; Inner Focus; critical rate; Shield Dust; Sheer Force.

### Triple Axel

Move ID: 813 (`MOVE_TRIPLE_AXEL`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Up to three strikes with powers 20, 40, and 60. Normally each strike makes an accuracy check and the sequence ends at the first miss. Skill Link bypasses later accuracy checks; later Loaded Dice behavior matters if implemented. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Triple_Axel_(move)>) (reviewed revision 4630705).

**Implementation:** Implemented in `moves/flow`: native event-owned action scratch supplies the 20/40/60 counter, and a narrow resident getter composes Triple Kick's per-hit accuracy callback. Native Skill Link suppresses later checks. Disguise's updated form-group callbacks absorb only the first strike; a resident final-damage adapter carries the result back to native normal/fixed damage without queuing work during AI estimates. Substitute and per-hit contact stay native. Loaded Dice is not implemented.

**Focused checks:** Miss on hit 2; Skill Link; Disguise; Substitute; contact; Loaded Dice dependency.

### Victory Dance

Move ID: 837 (`MOVE_VICTORY_DANCE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Scarlet/Violet: raises the user's Attack, Defense, and Speed one stage each. Arceus's temporary stat/damage effects are not used. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Victory_Dance_(move)>) (reviewed revision 4614272).

**Implementation:** Use the three ordinary stat-change metadata slots; no unique handler is necessary if the generic status boost effect supports them.

**Focused checks:** All three boosts; Contrary; partly capped stats; Snatch.

### Wave Crash

Move ID: 834 (`MOVE_WAVE_CRASH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Scarlet/Violet: 120-power damage with recoil of one third the damage inflicted. It does not also raise Speed. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Wave_Crash_(move)>) (reviewed revision 4622560).

**Implementation:** Reuse the ordinary one-third damage-recoil rule, including Rock Head/Reckless/Magic Guard and rounding. Do not import Arceus's action-speed effects.

**Focused checks:** Low damage rounding; Substitute damage; Rock Head; recoil KO.

### Wicked Blow

Move ID: 817 (`MOVE_WICKED_BLOW`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Guaranteed critical damage unless a critical-blocking ability prevents it. Scarlet/Violet lowered base power from 80 to 75. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Wicked_Blow_(move)>) (reviewed revision 4623001).

**Implementation:** Reuse Storm Throw/Frost Breath's forced-critical rule rather than a merely increased critical stage. Retain Battle Armor/Shell Armor checks.

**Focused checks:** Armor ability; burn; screens; selected 75 power.

### Wildbolt Storm

Move ID: 847 (`MOVE_WILDBOLT_STORM`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Scarlet/Violet: damages adjacent opponents with a 20% paralysis chance. Rain guarantees the ordinary accuracy check, but does not defeat semi-invulnerability. It is wind-based. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Wildbolt_Storm_(move)>) (reviewed revision 4621943).

**Implementation:** Share the Bleakwind/Sandsear rain helper and normal per-target secondary metadata.

**Focused checks:** Rain; Electric paralysis immunity policy; doubles; semi-invulnerability.

## Generation IX move specifications

### Alluring Voice

Move ID: 914 (`MOVE_ALLURING_VOICE`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Damages and confuses a target if its stats rose earlier in the current turn. It is sound-based. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Alluring_Voice_(move)>) (reviewed revision 4627948).

**Implementation:** Share Burning Jealousy's resident stat-rise history and pre-reaction eligibility snapshot, replacing burn with confusion. Wire sound/Substitute bypass and Throat Chop checks.

**Focused checks:** Earlier boost; boost from this hit; Own Tempo; Substitute; Sheer Force.

### Aqua Cutter

Move ID: 895 (`MOVE_AQUA_CUTTER`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary damaging move with an elevated critical-hit rate. It is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Aqua_Cutter_(move)>) (reviewed revision 4627565).

**Implementation:** Use critical-stage and sharp/slicing metadata. Do not confuse elevated critical chance with Flower Trick's guaranteed critical hit.

**Focused checks:** Critical rate; Sharpness flag; Protect.

### Aqua Step

Move ID: 872 (`MOVE_AQUA_STEP`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages the target and raises the user's Speed one stage on success. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Aqua_Step_(move)>) (reviewed revision 4621948).

**Implementation:** Use generic damage-plus-user-stat metadata.

**Focused checks:** Contrary; capped Speed; miss/Protect; Substitute.

### Armor Cannon

Move ID: 890 (`MOVE_ARMOR_CANNON`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages and lowers the user's Defense and Special Defense one stage each, like Close Combat. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Armor_Cannon_(move)>) (reviewed revision 4632428).

**Implementation:** Use the same self-stat-drop effect with Fire/special move data.

**Focused checks:** Contrary; immunity; successful hit; self-drop once.

### Axe Kick

Move ID: 853 (`MOVE_AXE_KICK`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Damage with a 30% confusion chance. A miss, immunity, or protected target causes crash damage of half the user's maximum HP. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Axe_Kick_(move)>) (reviewed revision 4632440).

**Implementation:** Adapt High Jump Kick's crash logic plus confusion metadata. Preserve crash eligibility and rounding; unlike ordinary recoil, the cost is from maximum HP and failed contact.

**Focused checks:** Miss; Protect; Ghost immunity; Own Tempo; Magic Guard; crash KO.

### Bitter Blade

Move ID: 891 (`MOVE_BITTER_BLADE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Restores up to half the damage inflicted as user HP. Big Root increases recovery by 30%; Liquid Ooze converts that recovery into damage. It is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Bitter_Blade_(move)>) (reviewed revision 4622928).

**Implementation:** Use ordinary 50% draining-move logic and metadata, not a fixed half-max-HP heal.

**Focused checks:** Big Root; Liquid Ooze; Substitute; Heal Block; slicing flag.

### Blazing Torque

Move ID: 896 (`MOVE_BLAZING_TORQUE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Damages with a 30% burn chance. This Starmobile move has special copy/call restrictions, including Encore, Instruct, Mimic, Sketch, and Copycat-related eligibility. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Blazing_Torque_(move)>) (reviewed revision 4635199).

**Implementation:** The damage/status portion is generic. Review and add its full move-calling blacklist to the central eligibility services; NPC origin does not make those restrictions disappear when assigning it to ordinary Pokémon.

**Focused checks:** Burn immunity; Sheer Force; all supported copying/calling paths.

### Blood Moon

Move ID: 901 (`MOVE_BLOOD_MOON`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Cannot be selected consecutively after successful use; using another move or a failed attempt allows it again. Choice locking or no alternatives can force alternating Struggle. Instruct and Sleep Talk can repeat it; Encore permits one immediate repeat, then forces Struggle on subsequent Encore turns. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Blood_Moon_(move)>) (reviewed revision 4632439).

**Implementation:** Share a selection-restriction service with Gigaton Hammer. Do not replace the rule with an execution-time ban, which would incorrectly block called moves. Track success and the Encore exception across extra actions.

**Focused checks:** Choice lock; failure; Instruct; Sleep Talk; Encore sequence; switch reset.

### Burning Bulwark

Move ID: 908 (`MOVE_BURNING_BULWARK`). Complexity: **Easy**. Proposed route: `moves/guards`.

**Effect:** Blocks damaging moves, not status moves, and burns an opposing contacting attacker. It participates in the consecutive protection success penalty. An attack that bypasses protection must not trigger its burn. It fails if the user acts last; each consecutive qualifying protection divides success probability by three. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Burning_Bulwark_(move)>) (reviewed revision 4632484).

**Implementation:** Implemented in the same `moves/guards` damage-only shield family as Obstruct, using native burn work after a confirmed blocked contact. Long Reach and usable Protective Pads prevent retaliation; native condition work applies burn immunities. Feint and non-destructive bypass moves do not retaliate. Unseen Fist remains an ability dependency, not permission to burn unblocked attackers. Global BW2 protection success odds are retained. Allied/doubles interactions are not newly validated.

**Focused checks:** Contact/noncontact; allied attack; status move; repeat protection; burn immunity; bypass.

### Chilling Water

Move ID: 886 (`MOVE_CHILLING_WATER`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages and lowers the target's Attack one stage. It is also excluded from Metronome's call pool. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Chilling_Water_(move)>) (reviewed revision 4628062).

**Implementation:** Wired through existing generic target-stat metadata; no new DLL. The current native W2/B2 Metronome pool is move IDs 1–559, so this move is already excluded. The final W2 packed record and native pool-bound instructions were checked. If that pool is later expanded, add the explicit exclusion to the shared eligibility policy; do not silently admit Chilling Water.

**Focused checks:** Clear Body; Substitute; Sheer Force; Metronome exclusion.

### Chilly Reception

Move ID: 881 (`MOVE_CHILLY_RECEPTION`). Complexity: **Hard**. Proposed route: `moves/terrain`.

**Effect:** Starts five-turn snow, extended to eight by Icy Rock, then switches the user out. Existing snow does not prevent the switch; no replacement means weather only. Direct selection has an early preparation message, unlike calling the move indirectly. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Chilly_Reception_(move)>) (reviewed revision 4614463).

**Implementation:** Depends on a real snow weather implementation. Combine weather work and a Parting Shot/U-turn-style switch without requiring a damaging hit. Queue the early message once with safe action ownership; do not reuse Beak Blast's phase assumptions.

**Focused checks:** Existing snow; Icy Rock; no bench; trapped user; indirect call; early message.

### Collision Course

Move ID: 878 (`MOVE_COLLISION_COURSE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** On a super-effective hit, gets an additional damage multiplier of 5461/4096, approximately 4/3, beyond ordinary type effectiveness. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Collision_Course_(move)>) (reviewed revision 4628588).

**Implementation:** Share a post-effectiveness damage modifier with Electro Drift. Do not change base power or the type chart, and preserve fixed-point rounding.

**Focused checks:** Neutral/resisted/super-effective; dual-type effectiveness; rounding; Wonder Guard.

### Combat Torque

Move ID: 899 (`MOVE_COMBAT_TORQUE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Damages with a 30% paralysis chance and the Starmobile move copy/call restrictions. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Combat_Torque_(move)>) (reviewed revision 4635219).

**Implementation:** Use normal paralysis data plus the shared Torque eligibility policy. Audit exact affected calling moves from its source, not just Metronome.

**Focused checks:** Paralysis immunity; Sheer Force; Encore/Instruct/copying exclusions.

### Comeuppance

Move ID: 894 (`MOVE_COMEUPPANCE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Metal Burst-style retaliation: deals 1.5 times damage from the last opposing damaging attack that hit the user. It has normal priority, so fails if no qualifying earlier damage exists; Substitute damage does not qualify. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Comeuppance_(move)>) (reviewed revision 4628080).

**Implementation:** Reuse vanilla Metal Burst, preserving source targeting, ally exclusion, and fallback behavior if the damage source has left/fainted. Do not use Counter's physical-only rule or negative priority.

**Focused checks:** Physical/special; moves first; Substitute; ally attack; source faints.

### Doodle

Move ID: 867 (`MOVE_DOODLE`). Complexity: **Hard**. Proposed route: `moves/ability`.

**Effect:** Copies the target's Ability to the user and its ally. It fails if any participant has a protected Ability; Receiver additionally blocks copying from the target, but not replacing Receiver on a recipient. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Doodle_(move)>) (reviewed revision 4511990).

**Implementation:** Validate every participant before changing any ability. The protected set is As One, Battle Bond, Comatose, Commander, Disguise, Gulp Missile, Ice Face, Multitype, Poison Puppeteer, Power Construct, Protosynthesis, Quark Drive, RKS System, Schooling, Shields Down, Stance Change, Zen Mode, and Zero to Hero. Register new abilities through the dynamic resolver.

**Focused checks:** One protected participant; Receiver asymmetry; newly loaded ability; switch restoration; doubles.

### Double Shock

Move ID: 892 (`MOVE_DOUBLE_SHOCK`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Requires the user already to be Electric before Protean/Libero activation. After a successful hit, removes Electric: pure Electric becomes typeless, dual type retains the other type. Switching restores typing. Electric Terastallization would prevent type loss. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Double_Shock_(move)>) (reviewed revision 4628113).

**Implementation:** Parameterize Burn Up's prerequisite/type-removal helpers for Electric. Do not reinterpret typeless as Normal or remove both types. Champions' new punching flag is not part of Scarlet/Violet.

**Focused checks:** Pure/dual Electric; Protean prerequisite; miss; switch; later Tera dependency.

### Dragon Cheer

Move ID: 913 (`MOVE_DRAGON_CHEER`). Complexity: **Medium**. Proposed route: `moves/stats`.

**Effect:** Raises adjacent allies' critical stage by one, or two if Dragon-type at application time. That bonus stays fixed if typing later changes. Fail with no ally or if it already has Focus Energy/Dragon Cheer. Current Scarlet/Violet clears it on switching; it is not sound-based there. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Dragon_Cheer_(move)>) (reviewed revision 4628118).

**Implementation:** Reuse Focus Energy storage through a distinct application service, preserving copy behavior through Psych Up/Transform and later Costar/Opportunist/Mirror Herb if supported. Do not confuse Champions' sound flag with Scarlet/Violet.

**Focused checks:** Dragon versus non-Dragon; later type change; Focus Energy; switch; copying.

### Electro Drift

Move ID: 879 (`MOVE_ELECTRO_DRIFT`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Gets an extra 5461/4096 damage multiplier, approximately 4/3, when the attack is super effective. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Electro_Drift_(move)>) (reviewed revision 4623927).

**Implementation:** Share Collision Course's final-damage modifier with the same rounding and effectiveness predicate.

**Focused checks:** Neutral versus super-effective; dual types; damage rounding.

### Electro Shot

Move ID: 905 (`MOVE_ELECTRO_SHOT`). Complexity: **Medium**. Proposed route: `moves/terrain`.

**Effect:** Raises Special Attack during its charging phase, then attacks on the next turn. Rain skips the extra turn; Power Herb also gives the boost and immediate attack. The source notes a Sheer Force power interaction without removing the boost. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Electro_Shot_(move)>) (reviewed revision 4581379).

**Implementation:** Share Meteor Beam's charge service, adding the execution-time rain shortcut. Keep boost, PP deduction, and animations single-shot. Verify the stated Sheer Force exception before applying broad secondary-effect suppression.

**Focused checks:** Rain starts/stops; Power Herb; flinch/sleep; called move; Sheer Force.

### Fickle Beam

Move ID: 907 (`MOVE_FICKLE_BEAM`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Has a 30% chance to double its normal power from 80 to 160 for that use. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Fickle_Beam_(move)>) (reviewed revision 4637025).

**Implementation:** Roll once per action and cache the result for all relevant calculations/animation. Do not reroll every time an event asks for power; this is not an ordinary target status secondary.

**Focused checks:** RNG frequency; repeated power queries; called move; animation branch.

### Fillet Away

Move ID: 868 (`MOVE_FILLET_AWAY`). Complexity: **Medium**. Proposed route: `moves/stats`.

**Effect:** Spends half the user's maximum HP, rounded down, to raise Attack, Special Attack, and Speed two stages each. Fail with insufficient HP or if all affected stats are already maximized. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Fillet_Away_(move)>) (reviewed revision 4527964).

**Implementation:** Share a transactional HP-cost/stat-boost service with Clangorous Soul but keep this move's rounding and +2 values. Do not heal or subtract per stat; test HP exactly at the boundary.

The shared handler now uses native direct HP-payment work for this move too,
with floor-half maximum HP and a minimum payment of one. It preserves the
non-sound metadata and queues only Attack, Special Attack and Speed boosts;
Defense, Special Defense, accuracy and evasion remain unchanged.

**Focused checks:** Odd max HP; boundary HP; partly/all capped stats; Contrary; Berry trigger.

### Flower Trick

Move ID: 870 (`MOVE_FLOWER_TRICK`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Always hits and always critically hits when a critical hit is permitted. It still obeys ordinary type immunity, protection, and semi-invulnerability. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Flower_Trick_(move)>) (reviewed revision 4623068).

**Implementation:** Combine must-hit accuracy metadata with vanilla Storm Throw/Frost Breath critical logic; neither rule should erase Battle Armor/Shell Armor.

**Focused checks:** Evasion; armor ability; Protect; semi-invulnerability; immunity.

### Gigaton Hammer

Move ID: 893 (`MOVE_GIGATON_HAMMER`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Cannot be selected after a successful consecutive use, unless another move intervenes or the prior attempt failed. Choice lock/no alternative forces alternating Struggle. Instruct/Sleep Talk can repeat it; Encore has a one-repeat exception before Struggle. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Gigaton_Hammer_(move)>) (reviewed revision 4623056).

**Implementation:** Share Blood Moon's selection policy and success history. Ordinary Torment is not an exact alias because the calling and Encore exceptions differ.

**Focused checks:** Choice item; miss/failure; Instruct; Sleep Talk; Encore; extra action.

### Glaive Rush

Move ID: 862 (`MOVE_GLAIVE_RUSH`). Complexity: **Medium**. Proposed route: `moves/volatile`.

**Effect:** After it hits, attacks aimed at the user bypass accuracy/evasion and have doubled ordinary damage until the user's next action; fixed-damage moves do not get the multiplier. The accuracy effect also applies to OHKO moves. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Glaive_Rush_(move)>) (reviewed revision 4628387).

**Implementation:** Use a user volatile consumed at the correct next-action boundary, not simply at end of turn. Preserve Protect/type immunity and fixed-damage treatment; test action prevention and extra actions to resolve the precise expiry.

**Focused checks:** Next action versus next turn; Instruct; OHKO; Super Fang; Protect; switching.

### Hard Press

Move ID: 912 (`MOVE_HARD_PRESS`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Power scales with the target's current HP: floor(100 × current HP / maximum HP), with a minimum of one and maximum of 100. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Hard_Press_(move)>) (reviewed revision 4577757).

**Implementation:** Reuse the target-HP power pattern from Crush Grip/Wring Out, but replace its constants/formula explicitly. An unmodified alias would not match the 100-power scale.

**Focused checks:** Full/half/one HP; integer rounding; target HP changes before execution.

### Hydro Steam

Move ID: 876 (`MOVE_HYDRO_STEAM`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** In sun, Water damage is multiplied by 1.5 rather than the usual 0.5. The source reports that the user's Utility Umbrella prevents this special boost while ordinary sun weakening still applies. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Hydro_Steam_(move)>) (reviewed revision 4570738).

**Implementation:** Implemented in `moves/type`. A small resident adapter at the native damage-weather getter notifies the child in the active damage context. The child substitutes rain's multiplier only for Water-type Hydro Steam in effective sun; the actual weather is unchanged. Native weather rounding stays before random damage and STAB; power and final modifiers are unchanged. Utility Umbrella is not an implemented repository item, so its item-specific exception remains a future item dependency, not verified coverage.

**Focused checks:** Sun/rain; Cloud Nine/Air Lock; Utility Umbrella; rounded damage.

### Hyper Drill

Move ID: 887 (`MOVE_HYPER_DRILL`). Complexity: **Easy**. Proposed route: `moves/guards`.

**Effect:** Damages through applicable protection moves without removing their protection for later attacks. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Hyper_Drill_(move)>) (reviewed revision 4614319).

**Implementation:** Native data audited: omit `FLAG_BLOCKED_BY_PROTECT`, with no new registration or DLL. The native protect check and supported custom guard/retaliation paths respect that flag. No Feint alias, protection removal or counter reset is introduced. Packed flags are checked; new emulator/doubles coverage is skipped under the native-reuse policy.

**Focused checks:** Protect remains afterward; shield retaliation; later ally attack; immunity.

### Ice Spinner

Move ID: 861 (`MOVE_ICE_SPINNER`). Complexity: **Medium**. Proposed route: `moves/terrain`.

**Effect:** Damages and removes terrain. Under Scarlet/Violet, user fainting from Life Orb or contact punishment, or a Red Card-forced departure, can prevent the removal; Champions changed some of these cases. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Ice_Spinner_(move)>) (reviewed revision 4628283).

**Implementation:** Use the core terrain-removal service at the correct post-hit/post-reaction phase. It is not an exact Steel Roller clone: it can work without terrain and has reaction-order distinctions.

**Focused checks:** No terrain; Life Orb KO; Rough Skin/Helmet KO; Red Card; visual cleanup.

### Ivy Cudgel

Move ID: 904 (`MOVE_IVY_CUDGEL`). Complexity: **Medium**. Proposed route: `moves/type`.

**Effect:** Has an elevated critical rate. Ogerpon's mask selects Grass, Water, Fire, or Rock type; another species uses Grass even when holding a mask. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Ivy_Cudgel_(move)>) (reviewed revision 4620154).

**Implementation:** Resolve type from species and held-mask IDs at execution. Confirm mask item/form data exists; do not infer type from the item's name string. Tera/form changes are separate dependencies.

**Focused checks:** Four masks; no mask; non-Ogerpon; item change; critical rate.

### Jet Punch

Move ID: 857 (`MOVE_JET_PUNCH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Ordinary damaging move at +1 priority, tagged as punching. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Jet_Punch_(move)>) (reviewed revision 4578131).

**Implementation:** Use generic priority and punch flags. Iron Fist and priority-blocking mechanics should receive the ordinary events.

**Focused checks:** Psychic Terrain; Queenly Majesty; Iron Fist; order ties.

### Kowtow Cleave

Move ID: 869 (`MOVE_KOWTOW_CLEAVE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Always hits except normal semi-invulnerability, while retaining protection and type-immunity checks. It is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Kowtow_Cleave_(move)>) (reviewed revision 4614952).

**Implementation:** Use must-hit accuracy and sharp/slicing metadata, like Aerial Ace's accuracy behavior.

**Focused checks:** Evasion; Protect; semi-invulnerability; Sharpness flag.

### Last Respects

Move ID: 854 (`MOVE_LAST_RESPECTS`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** Starts at 50 power and adds 50 for every fainting event on the user's side during the battle, including a revived Pokémon fainting again. Caps at 5,050 after 100 events. The source leaves multi-battle ally scope unresolved. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Last_Respects_(move)>) (reviewed revision 4614671).

**Implementation:** Use a resident side/party faint-event counter that exists before the move module loads, with a wide enough power representation. Counting currently fainted party members is wrong. Resolve multi-owner scope before implementation.

**Focused checks:** Pre-registration faints; repeat revival/faint; self KO; power >255; multi battles.

### Lumina Crash

Move ID: 855 (`MOVE_LUMINA_CRASH`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages and lowers the target's Special Defense two stages. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Lumina_Crash_(move)>) (reviewed revision 4578150).

**Implementation:** Use ordinary damage-plus-target-stat metadata with a -2 value.

**Focused checks:** Stage floor; Clear Body; Contrary; Substitute; Sheer Force.

### Magical Torque

Move ID: 900 (`MOVE_MAGICAL_TORQUE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Damages with a 30% confusion chance and the Starmobile copy/call restrictions. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Magical_Torque_(move)>) (reviewed revision 4635267).

**Implementation:** Use generic confusion metadata plus the reviewed shared Torque blacklist.

**Focused checks:** Own Tempo; Shield Dust; Encore/Instruct/Mimic/Sketch/Copycat restrictions.

### Make It Rain

Move ID: 874 (`MOVE_MAKE_IT_RAIN`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Damages adjacent opponents and lowers the user's Special Attack one stage once per use. Successful hits scatter prize coins at five times user level per hit target; Amulet Coin/Luck Incense affects the final payout. Scarlet/Violet uses -1 and 100% accuracy; Champions uses -2 and 95%. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Make_It_Rain_(move)>) (reviewed revision 4620155).

**Implementation:** Combine spread/self-stat metadata with a Pay Day-style payout service. Count successful targets without multiplying the self drop, and preserve trainer/wild/battle-end money handling.

**Focused checks:** Doubles two hits; one protected foe; drop once; payout; Amulet Coin.

### Malignant Chain

Move ID: 919 (`MOVE_MALIGNANT_CHAIN`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Deals damage with a 50% chance of badly poisoning the target, not ordinary poisoning. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Malignant_Chain_(move)>) (reviewed revision 4632458).

**Implementation:** Use the engine's damage-plus-toxic secondary encoding; verify the status representation includes the toxic flag/counter rather than ordinary poison.

**Focused checks:** Poison/Steel immunity; Immunity; existing poison; toxic counter; Sheer Force.

### Matcha Gotcha

Move ID: 902 (`MOVE_MATCHA_GOTCHA`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** Damages both opponents, drains half damage, and has a 20% burn chance. Big Root increases healing by 30%. Liquid Ooze reverses the drain; if one foe has it, that damage is processed before healing from the other. It thaws the user on execution and frozen targets on hit. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Matcha_Gotcha_(move)>) (reviewed revision 4614876).

**Implementation:** Use a shared spread-drain service that explicitly orders Liquid Ooze before other healing. Add Scald-style thaw work and independent burn rolls; do not heal from planned rather than actual damage.

**Focused checks:** Mixed Liquid Ooze foes; Big Root; frozen user/target; Substitute; drain KO.

### Mighty Cleave

Move ID: 910 (`MOVE_MIGHTY_CLEAVE`). Complexity: **Easy**. Proposed route: `moves/guards`.

**Effect:** Damages through applicable protection without removing it. It is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Mighty_Cleave_(move)>) (reviewed revision 4477404).

**Implementation:** Same native-data bypass as Hyper Drill, retaining contact and slicing. No Feint alias, extra handler or protection-counter reset is introduced. Packed flags are checked; new emulator coverage is skipped under the native-reuse policy.

**Focused checks:** Protection remains; later attacks; shield retaliation; slicing flag.

### Mortal Spin

Move ID: 866 (`MOVE_MORTAL_SPIN`). Complexity: **Medium**. Proposed route: `moves/hazards`.

**Effect:** Damages adjacent opponents and poisons each eligible hit target. Removes the user's binding/Leech Seed and hazards on its side, unless the user has fainted from the move's reactions. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Mortal_Spin_(move)>) (reviewed revision 4631936).

**Implementation:** Adapt the expanded Rapid Spin cleanup for Sticky Web too, but do not inherit an unrelated Speed boost. Separate per-target poisoning from once-per-action cleanup and respect reaction timing.

**Focused checks:** Two foes; poison immunity; Sticky Web; binding; Rough Skin user KO.

### Nihil Light

Move ID: unassigned. Complexity: **Medium**. Proposed route: `moves/type`.

**Effect:** Legends: Z-A only: damages while ignoring target stat changes, and ignores Fairy's Dragon immunity. Against a Fairy dual type, use the other type alone, e.g. Fairy/Dragon still takes super-effective Dragon damage. Its real-time cooldown has no canonical BW2 turn equivalent. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Nihil_Light_(move)>) (reviewed revision 4634595).

**Implementation:** Adapt target-stage bypass and component-wise effectiveness only after choosing PP/turn data. There is no current MOVE_NIHIL_LIGHT constant; 920 is MOVE_END_MSG, not a free safe ID. Do not claim a canonical turn-based implementation.

**Focused checks:** Fairy/Dragon; Fairy/Steel; target defense/evasion stages; assigned ID/range audit.

### Noxious Torque

Move ID: 898 (`MOVE_NOXIOUS_TORQUE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Damages with a 30% ordinary-poison chance and the Starmobile move-calling restrictions. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Noxious_Torque_(move)>) (reviewed revision 4635211).

**Implementation:** Use generic poison metadata plus the shared Torque eligibility policy; do not convert the poison to Toxic.

**Focused checks:** Poison immunity; ordinary poison counter; Sheer Force; copy/call restrictions.

### Order Up

Move ID: 856 (`MOVE_ORDER_UP`). Complexity: **Hard**. Proposed route: `moves/ability`.

**Effect:** Ordinary Dragon damage when no Commander relationship exists. Dondozo with Tatsugiri in its mouth additionally gains one stage of Attack, Defense, or Speed according to Tatsugiri's Curly, Droopy, or Stretchy form. The source records special Sheer Force behavior and a corrected old protection-related boost bug. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Order_Up_(move)>) (reviewed revision 4622559).

**Implementation:** The full effect depends on Commander, partner occupancy, and form state not established by the present move registry. Build that system first; partial plain damage must be labeled partial, not complete.

**Focused checks:** No Commander; three forms; Protect; Sheer Force; partner departure; doubles.

### Population Bomb

Move ID: 860 (`MOVE_POPULATION_BOMB`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** Up to ten strikes with a separate accuracy check for each, ending at the first miss. Skill Link gives ten strikes after one check. Loaded Dice gives uniformly four to ten after one check. Contact and survival reactions occur per strike; it is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Population_Bomb_(move)>) (reviewed revision 4589972).

**Implementation:** Audit all hit-count arrays, loops, command records, and animations for Gen 5's normal five-hit limit before extending the pipeline. Metadata's four-bit counts alone do not prove ten-hit safety.

**Focused checks:** Ten hits; miss mid-sequence; Skill Link; Loaded Dice; Helmet; Substitute; early KO.

### Pounce

Move ID: 884 (`MOVE_POUNCE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages and lowers the target's Speed one stage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Pounce_(move)>) (reviewed revision 4628378).

**Implementation:** Use ordinary damage-plus-target-stat metadata.

**Focused checks:** Clear Body; Substitute; Contrary; Sheer Force.

### Psyblade

Move ID: 875 (`MOVE_PSYBLADE`). Complexity: **Easy**. Proposed route: `moves/terrain`.

**Effect:** Gets a 1.5× power multiplier in Electric Terrain, regardless of whether the user or target is grounded. It is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Psyblade_(move)>) (reviewed revision 4614871).

**Implementation:** Use a terrain-active power predicate only; do not copy Rising Voltage's target grounding or Grassy Glide's user grounding.

**Focused checks:** Both battlers airborne; terrain removed; power rounding; slicing.

### Psychic Noise

Move ID: 917 (`MOVE_PSYCHIC_NOISE`). Complexity: **Medium**. Proposed route: `moves/volatile`.

**Effect:** Damages and applies two-turn Heal Block without refreshing an existing block. This stops relevant healing and draining moves. It is sound-based; Shield Dust and Aroma Veil can prevent the added effect, and Sheer Force suppresses it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Psychic_Noise_(move)>) (reviewed revision 4628390).

**Implementation:** Reuse the native Heal Block condition with a damage-triggered, non-refreshing duration. Extend selection and execution gates where required, sharing Throat Chop's immediate same-turn blocking lessons but not its sound-move predicate.

**Focused checks:** Faster hit then healing; draining move; refresh attempt; Aroma Veil; Sheer Force; Substitute.

### Rage Fist

Move ID: 889 (`MOVE_RAGE_FIST`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** Power is 50 plus 50 per direct-damage hit received, capped at 350 after six hits. Allies and each multi-hit strike count; Disguise activation counts, but Substitute hits and confusion self-damage do not. Transform copies the counter. Scarlet/Violet preserves it across switching and fainting; Champions resets it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Rage_Fist_(move)>) (reviewed revision 4630698).

**Implementation:** Maintain resident battle-local party-member hit counters before the move module loads, not field-slot counters. Add an explicit Transform-copy operation and reset only at the selected ruleset's boundary.

**Focused checks:** Earlier hits before registration; multi-hit; Disguise; Substitute; switch/revive; Transform.

### Raging Bull

Move ID: 873 (`MOVE_RAGING_BULL`). Complexity: **Medium**. Proposed route: `moves/screens`.

**Effect:** Breaks Reflect, Light Screen, and Aurora Veil in the Brick Break timing before damage. Paldean Tauros Combat, Blaze, and Aqua breeds give Fighting, Fire, and Water respectively; other users use Normal. Remove screens from the actual target's side even when targeting an ally; a failed hit must not remove them. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Raging_Bull_(move)>) (reviewed revision 4578233).

**Implementation:** Share the existing Aurora Veil-aware Brick Break logic, adding a species/form type resolver. Do not remove screens only after damage, or this attack still receives their reduction.

**Focused checks:** Three forms; other species; screens + Veil; Protect; immunity; Substitute.

### Revival Blessing

Move ID: 863 (`MOVE_REVIVAL_BLESSING`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** Selects a fainted party member and revives it at half maximum HP; fails if none exists. Heal Block prevents it. A revived Mega retains its Mega form. Sketch cannot copy the move. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Revival_Blessing_(move)>) (reviewed revision 4628400).

**Implementation:** Needs a safe in-battle fainted-party selection command/UI and authoritative party mutation, not a heal effect on an active slot. Preserve trainer/multi-battle ownership, cancellation behavior, and existing Mega state.

**Focused checks:** No fainted member; selected bench member; Mega; Heal Block; cancel; multi battles.

### Ruination

Move ID: 877 (`MOVE_RUINATION`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Removes half the target's current HP, rounded down, dealing at least one HP. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Ruination_(move)>) (reviewed revision 4403657).

**Implementation:** Reuse vanilla Super Fang exactly, as the resident Nature's Madness alias already does. Do not calculate half of maximum HP or ordinary base-power damage.

**Focused checks:** Odd current HP; one HP; Substitute; type immunity; Protect.

### Salt Cure

Move ID: 864 (`MOVE_SALT_CURE`). Complexity: **Medium**. Proposed route: `moves/volatile`.

**Effect:** After damaging, applies residual loss each end turn: one eighth maximum HP, or one quarter if the target is currently Water or Steel. Ends on target departure and is not Baton Passed. Scarlet/Violet fractions differ from Champions' halved values. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Salt_Cure_(move)>) (reviewed revision 4578256).

**Implementation:** Use a target volatile with a subordinate end-turn handler, checking current typing each tick and preventing duplicate condition instances. Confirm reapplication behavior from a verified test rather than assuming a generic bind duration.

**Focused checks:** Water/Steel dual type; type change; switch; Baton Pass; Protect; residual rounding.

### Shed Tail

Move ID: 880 (`MOVE_SHED_TAIL`). Complexity: **Hard**. Proposed route: `moves/flow`.

**Effect:** Costs half the user's maximum HP rounded up, creates a Substitute worth one quarter of that user's maximum HP, then switches and transfers it. A triggered Berry is eaten before switching. Fail with an existing Substitute, insufficient HP, or no replacement. Entry hazards still affect the incoming Pokémon. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Shed_Tail_(move)>) (reviewed revision 4578277).

**Implementation:** Compose Substitute and switching transactionally, transferring only the intended substitute state rather than all Baton Pass effects. Audit rounding, eligibility, trap bypass, and the bench selection command.

**Focused checks:** Odd max HP; boundary HP; Sitrus ordering; no bench; existing Sub; hazards; no stat pass.

### Silk Trap

Move ID: 852 (`MOVE_SILK_TRAP`). Complexity: **Easy**. Proposed route: `moves/guards`.

**Effect:** Blocks damaging moves, not status moves, and lowers a contacting attacker's Speed one stage. Shares protection's consecutive-use failure rate. It fails if the user acts last; each consecutive qualifying protection divides success probability by three. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Silk_Trap_(move)>) (reviewed revision 4403633).

**Implementation:** Implemented in the same `moves/guards` family with native Speed -1 stat work, preserving Clear Body/Contrary handling. Child callbacks expire on turn end, protection break or owner switch-out, and the module remains loaded for the battle. King’s Shield shares this corrected damage-only path, retaining the project's Attack -2 retaliation. Global BW2 protection success odds are retained. Mirror Armor/Unseen Fist execution, allied/doubles interactions and rendered animations are outside this focused implementation's verified coverage.

**Focused checks:** Status move; contact; Clear Body; Contrary; Mirror Armor; repeated Protect.

### Snowscape

Move ID: 883 (`MOVE_SNOWSCAPE`). Complexity: **Hard**. Proposed route: `moves/terrain`.

**Effect:** Sets five-turn snow, extended to eight by Icy Rock. Snow replaces other weather, fails if already active, and boosts Ice Defense by 50% without hail chip damage. Ice Body, Snow Cloak, Slush Rush, Aurora Veil, Weather Ball, and reduced Synthesis-family recovery must recognize snow. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Snowscape_(move)>) (reviewed revision 4636006).

**Implementation:** Implement a distinct core weather or explicitly approved replacement policy; merely renaming Hail is incorrect. Cover weather enums, duration, damage, abilities, move eligibility, displays, and weather graphics. No snow runtime implementation was found in this audit.

**Focused checks:** No chip; Ice Defense; Icy Rock; weather overwrite; Veil; Weather Ball; healing.

### Spicy Extract

Move ID: 858 (`MOVE_SPICY_EXTRACT`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Raises target Attack two stages and lowers Defense two stages, with independent results. It has must-hit accuracy. Mirror Armor can reflect the Defense drop. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Spicy_Extract_(move)>) (reviewed revision 4587177).

**Implementation:** Use a mixed-sign target-stat effect with two metadata entries and must-hit accuracy. Do not use Swagger, which would add confusion, or make either successful change depend on the other.

**Focused checks:** Attack capped; Defense capped; Contrary; Mirror Armor; evasion; Substitute.

### Spin Out

Move ID: 859 (`MOVE_SPIN_OUT`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages and lowers the user's Speed two stages after success. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Spin_Out_(move)>) (reviewed revision 4635281).

**Implementation:** Use ordinary damage-plus-user-stat metadata with a -2 Speed change.

**Focused checks:** Contrary; Speed floor; miss; successful hit.

### Supercell Slam

Move ID: 916 (`MOVE_SUPERCELL_SLAM`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Crashes for half maximum HP, rounded down, if it misses or meets protection/type/ability immunity. Against a minimized target, it doubles damage and hits without the ordinary accuracy check. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Supercell_Slam_(move)>) (reviewed revision 4632430). The damage-stage rather than base-power interpretation also matches [Pokémon Showdown's move/Minimize implementation](https://github.com/smogon/pokemon-showdown/blob/master/data/moves.ts).

**Implementation:** Implemented in `moves/flow`. The resident native-getter service supplies High Jump Kick's crash event and Stomp's final Minimize damage modifier from each game's own table. A file-local target-aware accuracy event (`0x1C`, not the attacker-only weather shortcut `0x32`) skips the ordinary roll against a minimized target. Native protection, immunity and semi-invulnerability filtering still precede this check. New focused coverage checks actual native Minimize, skipped rolls, ordinary accuracy without Minimize and doubled applied damage; reused crash paths are source/build-checked under the native-reuse policy, not separately emulator-tested.

**Focused checks:** Protect; Ground immunity; Volt Absorb; Minimize; odd HP; crash KO.

### Syrup Bomb

Move ID: 903 (`MOVE_SYRUP_BOMB`). Complexity: **Medium**. Proposed route: `moves/volatile`.

**Effect:** Damages and applies an effect that lowers the target's Speed one stage at the end of each of the next three turns. The effect immediately ends if its user leaves the field. Bulletproof blocks it. Scarlet/Violet uses 85% accuracy. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Syrup_Bomb_(move)>) (reviewed revision 4638547).

**Implementation:** Use a source-linked three-tick event, sharing Octolock-style ownership but not its trap. Verify first-tick/reapplication rules; the page does not settle every refresh edge case. Keep handler pointers valid through teardown.

**Focused checks:** Three ticks; source switch/faint; target switch; Bulletproof; repeat application; Clear Body.

### Tachyon Cutter

Move ID: 911 (`MOVE_TACHYON_CUTTER`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Exactly two strikes, with must-hit accuracy and normal per-strike critical/contact/survival behavior. It is slicing. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Tachyon_Cutter_(move)>) (reviewed revision 4616453).

**Implementation:** Use fixed two-hit metadata and must-hit accuracy. Standard immunity/protection and semi-invulnerability still apply.

**Focused checks:** Evasion; Substitute; survival item; Protect; slicing flag.

### Temper Flare

Move ID: 915 (`MOVE_TEMPER_FLARE`). Complexity: **Easy**. Proposed route: `moves/flow`.

**Effect:** Doubles power from 75 to 150 if the previous turn's last move missed, affected no target, or was prevented. Recharging does not qualify, and any target blocking that prior move with protection excludes the boost. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Temper_Flare_(move)>) (reviewed revision 4628582).

**Implementation:** The resident Stomping Tantrum tracker already distinguishes protection and stores last-turn failure. Review and parameterize it, then verify all listed exclusions and extra-action history before reusing its getter.

**Focused checks:** Paralysis; miss; all immune; any protected target; recharge; Instruct; turn rollover.

### Tera Blast

Move ID: 851 (`MOVE_TERA_BLAST`). Complexity: **Hard**. Proposed route: `moves/type`.

**Effect:** Without Tera, Normal special damage and ordinary type-changing abilities apply. With Tera, uses the user's Tera type, ignores type changes, and becomes physical only if staged Attack exceeds staged Special Attack at execution. Stellar uses 100 power, is super effective against Tera targets/neutral otherwise, and lowers both offenses one stage. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Tera_Blast_(move)>) (reviewed revision 4615218).

**Implementation:** Full support requires Tera and Stellar systems. Ignore item/ability stat boosts when choosing category; preserve the Flying/Gale Wings exception. A Normal-only fallback is playable partial behavior, not completion.

**Focused checks:** No Tera; Normal Tera versus -ate; changed stages; Gale Wings; Stellar targeting/drops.

### Tera Starstorm

Move ID: 906 (`MOVE_TERA_STARSTORM`). Complexity: **Hard**. Proposed route: `moves/type`.

**Effect:** Normally Normal-type special damage. Terapagos in Stellar Form makes it Stellar-type and opponent-spread. When Terastallized, staged Attack versus Special Attack chooses physical versus special as for Tera Blast. Sketch cannot copy it. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Tera_Starstorm_(move)>) (reviewed revision 4633812).

**Implementation:** Depends on Terapagos forms, Tera/Stellar effectiveness, dynamic category, and execution-time target masks. Share the Tera Blast service instead of adding a second interpretation of Stellar.

**Focused checks:** Ordinary user; Terapagos forms; doubles mask; category tie; Sketch; full-system dependency.

### Thunderclap

Move ID: 909 (`MOVE_THUNDERCLAP`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Sucker Punch-like +1-priority damage: requires the target to have selected a damaging move and not yet had its action. It can qualify even if sleep or Truant will later prevent that action. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Thunderclap_(move)>) (reviewed revision 4621485).

**Implementation:** Clone/reuse vanilla Sucker Punch with Electric/special data. Check pending selected action, not whether the target will actually succeed.

**Focused checks:** Status choice; already acted; sleeping target; Truant; priority blockers.

### Tidy Up

Move ID: 882 (`MOVE_TIDY_UP`). Complexity: **Medium**. Proposed route: `moves/hazards`.

**Effect:** Raises user Attack and Speed one stage each, removes all active Substitutes, and clears Spikes, Toxic Spikes, Stealth Rock, and Sticky Web on both sides. It can still boost when no removable effects exist. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Tidy_Up_(move)>) (reviewed revision 4578365).

**Implementation:** Compose global Substitute/hazard cleanup with self boosts; use core custom-hazard services. Unlike Defog, do not also remove screens or terrain.

**Focused checks:** No hazards; both sides; both Substitutes; Sticky Web; capped stats; Contrary.

### Torch Song

Move ID: 871 (`MOVE_TORCH_SONG`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla reuse`.

**Effect:** Damages and raises user Special Attack one stage. It is sound-based and bypasses Substitute. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Torch_Song_(move)>) (reviewed revision 4621949).

**Implementation:** Use self-stat metadata plus sound checks and the vanilla Substitute-bypass handler where needed. Do not infer bypass solely from a Gen 5 sound flag.

**Focused checks:** Substitute; Soundproof; Throat Chop; Liquid Voice; Contrary.

### Trailblaze

Move ID: 885 (`MOVE_TRAILBLAZE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Damages and raises user Speed one stage on success. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Trailblaze_(move)>) (reviewed revision 4628625).

**Implementation:** Use generic damage-and-user-stat metadata.

**Focused checks:** Contrary; Speed cap; Protect; Substitute.

### Triple Dive

Move ID: 865 (`MOVE_TRIPLE_DIVE`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Exactly three strikes with the same power; normal multi-hit damage, survival, Substitute, and contact rules apply. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Triple_Dive_(move)>) (reviewed revision 4577618).

**Implementation:** Use fixed three-hit metadata. It is not Triple Axel's increasing-power/independent-accuracy pattern.

**Focused checks:** Three hits; Focus Sash; Substitute; contact; early KO.

### Twin Beam

Move ID: 888 (`MOVE_TWIN_BEAM`). Complexity: **Already Supported by vanilla Gen 5 engine**. Proposed route: `vanilla data`.

**Effect:** Exactly two same-power strikes with ordinary multi-hit behavior. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Twin_Beam_(move)>) (reviewed revision 4614269).

**Implementation:** Use fixed two-hit metadata and normal Psychic immunity/protection checks.

**Focused checks:** Dark immunity; Substitute; survival item; early KO.

### Upper Hand

Move ID: 918 (`MOVE_UPPER_HAND`). Complexity: **Medium**. Proposed route: `moves/flow`.

**Effect:** At +3 priority, succeeds only against a target with a pending damaging move of effective priority +1 through +3 that has not yet had its action, then guarantees flinch. Ability-granted priority such as Gale Wings counts. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Upper_Hand_(move)>) (reviewed revision 4628416).

**Implementation:** Extend Sucker Punch-style action validation with the authoritative effective-priority value. Recomputing only move-data priority misses abilities; do not assume +4 guard moves qualify or bypass Inner Focus.

**Focused checks:** Priority 0/1/3/4; Gale Wings; faster Upper Hand; already acted; Inner Focus.

### Wicked Torque

Move ID: 897 (`MOVE_WICKED_TORQUE`). Complexity: **Easy**. Proposed route: `moves/type`.

**Effect:** Damages with a 10% sleep chance and the Starmobile copy/call restrictions. [Bulbapedia](<https://bulbapedia.bulbagarden.net/wiki/Wicked_Torque_(move)>) (reviewed revision 4635205).

**Implementation:** Use generic sleep secondary metadata plus the shared Torque eligibility policy, preserving normal sleep immunity and duration.

**Focused checks:** Insomnia/Vital Spirit; existing status; Sheer Force; copying/calling exclusions.

## Completion ledger for the implementation agent

Track each indexed move as data verified, reuse wired, custom handler implemented, dependent system missing, or battle tested. Keep those states separate from the complexity rating. Record source/ruleset deviations, W2 module-size deltas, B2 compatibility results, and exact tests performed. The batch report must account for all 159 entries and must not silently omit NPC-only, Hisui-origin, or difficult moves. If a systemic dependency or Nihil Light adaptation remains blocked, report that as incomplete implementation rather than claiming the full batch is finished.

This reference deliberately contains only portable repository-relative paths and public source links. It adds no runtime behavior and does not authorize broad unrelated cleanup.
