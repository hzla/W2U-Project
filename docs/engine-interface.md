# The engine interface: mechanics in C

W2U's battle mechanics are moving to plain C written against a thin interface, so they build under code injection now
and into a decomp-based W2U later without a rewrite. The game's battle event model (handler tables, event
variables, the handler-effect queue) is the interface: it is the same in the decomp (`src/ov167/ability_handlers.c`).
What the interface hides is what exists only because of injection: addresses, struct offsets, assembly thunks, the
PMC module loader and C++.

```
 mechanics            src/mechanics/**.c             C: handler tables + handlers
 battle API (B)       include/w2u/battle_api.h       W2U_* helpers, mostly static inline
 engine names (A)     include/w2u/engine.h           the game's functions and types, by decomp name
 adapters             injection: pmc/IRDO.yml, battle modules  |  decomp: its headers (later)
```

## Layer A: `include/w2u/engine.h`

The game functions, types and IDs the mechanics use, under the names of hzla's White 2 cleanup of the pokebw2 decomp
(`hzla/w2-expansion`, which keeps the decomp's public names): `BtlServerFlow`, `BattleEventHandlerEntry`,
`BattleEventVar_GetValue`, `GetBattleMon`, `GetBattleMonStat`, `PML_MoveGetParam`. Injection builds resolve them through
`pmc/IRDO.yml`; a name spelled differently there gets a `#define` in the header's injection part. Event IDs and event
variables are still numbers in the decomp, so W2U names them (`EVENT_DAMAGE_RATIO`, `VAR_RATIO`, ...). The struct
offsets injection needs live here only (`W2U_SERVERFLOW_SIMULATION_DEPTH`, the decomp's `simulationDepth`).

It is hand-written for the mechanics converted so far and grows with them; it becomes generated from the decomp
crosswalk later. It must not be included together with `w2u_abilities.h`, which declares the same engine under
older names (it `#error`s).

In a decomp build (`W2U_DECOMP` defined) the decomp's own headers declare the engine: `engine.h` then includes
`w2u/engine_decomp.h` instead of declaring the types, the handler-command work and the functions, and keeps only the
names W2U owns (events, event variables, handler commands, flags). `engine_decomp.h` adds the few names the decomp
lacks and checks that the constants both define agree; where the decomp has its own name for a constant, `engine.h`
uses that name (`MOVE_TARGET_*`), and where the decomp's name means something else W2U's gets a distinct one
(`getMoveFlag`'s bit indices are `MOVE_FLAG_INDEX_*`; the decomp's `MOVE_FLAG_*` are masks). Against the public
pokebw2 decomp, the names only hzla's cleanup has come from a generated `w2u/decomp_names.h`. A pilot build of Damp
into the public decomp, with W2U's harness passing on the ROM, is described in `w2u-local/decomp/pilot/README.md`
(2026-10-16).

## Layer B: `include/w2u/battle_api.h`

What mechanics would otherwise write by hand: who the event is about (`W2U_Attacker`, `W2U_Defender`, `W2U_Move`,
`W2U_MoveType`), moves (`W2U_MoveCategory`, `W2U_MoveHasFlag`, `W2U_MakesContact`, `W2U_TargetsPokemon`), sides and the field
(`W2U_IsAlly`, `W2U_OnField`, `W2U_HasActiveAbility`, `W2U_FirstFieldHolder`), the holder (`W2U_HolderAbility`), ratios (`W2U_MulRatio`, `W2U_MulMovePower`), effects through the
handler-effect queue (`W2U_PopupMessage`, `W2U_PopupMessageAbout`, `W2U_ChangeStatStage`, `W2U_PopupStatChange` (W2U's own abilities' way), `W2U_AddCondition`, `W2U_BlockMove`), `W2U_IsSimulating`. It grew from
MegaB2W2's `ability_api.h`, gone since every user moved here (the resident core last), and grows as mechanics need
more.

`engine.h` defines the handler-effect work it fills (`BattleHandlerMessageParam`, `BattleHandlerStatChangeParam`) as
the decomp does, with compile-time checks of the offsets the vanilla code uses. A name the cleanup gives that
`IRDO.yml` spells differently is mapped there for injection builds (`BtlCalc_ClassifyEffectiveness` is
`TypeEffectivenessClass`).

`w2u-local/decomp/wire_mechanic.py` does the registry steps below for converted MegaB2W2 files.

## W2U's own engine extensions

Some mechanics need state the engine's events don't carry: the move a Pokémon will use this turn (Quick Draw,
Mycelium Might), the sun during Mega Sol's moves, the Berry Cud Chew ate. W2U's resident core
(`megab2w2/mb_resident.cpp`, C++ written on `engine.h` / `battle_api.h` like the mechanics, with the decomp's names
for the functions its call-site hooks wrap) keeps it through those hooks and exposes it as plain C functions
(`W2U_MB_*`), and the terrain module the same way (`W2U_MoveState_*`, with C helpers in `battle_api.h`: `W2U_Terrain`,
`W2U_SetTerrainFromAbility`, `W2U_TerrainType`; Commander's `W2U_MoveState_SetCommanderForm` for Order Up). Which
form changes survive switching out is W2U's too: its switch-out hook keeps the form for a list of abilities
(`w2u_mega.cpp` `W2U_AbilityPreservesFormOnSwitchOut`); the form-change work's `dontResetOnSwitch` byte, which
PW2Code-style code sets, is read by nothing. `battle_api.h` declares them among W2U's
extensions, so a mechanic calls them like any other API function and stays portable. In a decomp build, those
functions stay, and only the hooks that feed them become calls written into the decomp's source (the named hooks
of the plan's step 4).

## Call sites

Where W2U changes what an engine call site does (not an event handler: a call inside the engine's own code), the
change is a resident C function on the engine interface, declared in `include/w2u/resident.h` and written in
`src/mechanics/resident/`. It takes the original call's arguments and returns its result type, so only the called
name changes:

- the injection build keeps its call-site hook (`THUMB_BRANCH_LINK_<module>_0x<address>` in
  `megab2w2/mb_resident.cpp`), which forwards to the function;
- a decomp build writes the call into the decomp's source and compiles the same C file.

| Function | Replaces | Call sites (White 2 address, decomp function) |
| --- | --- | --- |
| `W2U_RedirectBlocked` (`redirection.c`) | `Battle_IsRedirectBlocked` | `0x21C0D82` `CommonMoveTargetChangeToMe` (Lightning Rod, Storm Drain); `0x21C64C4` `HandlerFollowMeBaitTarget` (Follow Me, Rage Powder) |
| `W2U_GuaranteedHit` (`commander.c`) | `IsGuaranteedHit` | `0x21A3340` (the accuracy check's hide test), `0x21A6F7C` `ServerControl_OHKO` |
| `W2U_RechargeAction` (`commander.c`) | `ServerControl_RechargeAction` | `0x21A094E`, the action order's recharge action |
| `W2U_GetMovePriority` (`pending_move.c`) | `ServerEvent_GetMovePriority` | `0x21A0266` (the turn's first order), `0x219FBF8` (SortActionOrderBySpeed) |
| `W2U_HandlerUseHeldItem`, `_ForceUseItem`, `_RecoverHP`, `_Damage`, `_StatChange` (`handler_effects.c`) | `BattleHandler_UseHeldItem`, ... | `BattleHandler_Execute`'s command calls `0x21AC59E`, `0x21AC6D6`, `0x21AC5AA`, `0x21AC5C0`, `0x21AC604` |
| `W2U_Weather` (`weather.c`) | applied to `ServerEvent_GetWeather`'s result | the injection build replaces the whole function (its thunk is too short for a hook) |
| `W2U_MoldBreakerSkipCheck` (`mold_breaker.c`) | Mold Breaker's skip check, whole | the decomp's `HandlerMoldBreakerSkipCheck` returns it |
| `W2U_ProtectBlocks`, `W2U_CheckProtectBreak` (`protect.c`) | the protect step of `flowsub_CheckNoEffect_Protect` | per target: the three-way break check (holds / broken / goes through), "X protected itself!" and W2U's protect-success / broken events; the injection build replaces the whole function (`w2u_moves.cpp`), a decomp build's `ServerControl_RemoveNoEffectTargets` changes only its protect loop |
| `W2U_IsAffectedBySheerForce`, `W2U_Is{Assist,SleepTalk,MeFirst,Copycat}ExcludedMove` (`move_lists.c`) | `IsAffectedBySheerForce`, `Is*ExcludedMove` | Sheer Force's power / failure / hit checks (`0x18` into each handler); the four calling moves' checks (`0x21CC4DC`, `0x21CC5A2`, `0x21CC754`, `0x21CC7D6`) |
| `W2U_ComatoseAsleep`, `W2U_ConditionFailCause`, `W2U_ConditionFailForcesMessage`, `W2U_HasMajorStatus`, `W2U_IsComatose` (`status.c`) | the tests in `CheckCondition`, `ServerControl_AddConditionCheckFail`, `HandlerHex`, `CommonStatusReaction` | Comatose (asleep; no major status or drowsiness; its curing items don't react), Corrosion, Hex, the forced fail message; the injection build replaces the four whole (`w2u_abilities.cpp`), a decomp build changes their tests (Hex keeps each build's own doubling: W2U the base power, the decomp vanilla's ratio) |
| `W2U_MoveMakesContact`, `W2U_BattleMonCanUseHeldItem` (`contact.c`) | the contact flag test (`getMoveFlag(move, 0)`) | `CommonContactStatusAbility`, `HandlerRoughSkin`, `HandlerAftermath`, `HandlerPickpocket`, `HandlerPoisonTouch`, `HandlerMummy`, `HandlerStickyBarbDamageReaction`, `HandlerRockyHelmet`: the injection build replaces them whole (`w2u_abilities.cpp`), a decomp build only their contact test |
| `W2U_CalcDamageCategory`, `W2U_HitCategory`, `W2U_RecordedMoveCategory` (`move_category.c`) | `PML_MoveGetCategory` on the damage path | `ServerEvent_CalcDamage` (`+0x10`), `ServerEvent_GetAttackPower` (`+0xC`), `ServerEvent_GetTargetDefenses` (`+0xE`); Counter's record (`CommonCounterGetRecord`). Shell Side Arm (its handler's pick), Photon Geyser (Attack against Special Attack); the state (`W2U_MoveState_SetShellSideArmCategory` ...) was w2u_moves.cpp's |
| `W2U_DamageWeather`, `W2U_DispatchFinalMoveDamage`, `W2U_DispatchAttackStatSelector`, `W2U_CriticalAttackStat` (`damage.c`) | `ServerEvent_GetWeather`, the last event (`0x48`), the first event (`0x39`), `CritAtkDefLevel` | `ServerEvent_CalcDamage` `+0xDE`, `+0x1C0`; `ServerEvent_GetAttackPower` `+0x4E`, `+0x86` (the last three through `w2u_damage_hooks.s`): W2U's `EVENT_W2U_DAMAGE_WEATHER` and `EVENT_W2U_ATTACK_STAT_SELECTOR` (Body Press), `VAR_DAMAGE` for fixed damage |
| `W2U_ThawHitTargets`, `W2U_DamagingSubstitute`, `W2U_MultiHitTargetCount`, `W2U_SpreadTargetCount` (`damage.c`) | `ServerControl_ThawHitTargets`, `IsSubstituteActive`, the target counts | `0x21A5542` (Scorching Sands, Matcha Gotcha thaw as Fire), `0x21A462A` (sound moves through a Substitute), `ServerControl_DamageRoot` `+0x5E` and `0x21A487E` (Dragon Darts) |
| `W2U_CheckMultihitHits` (`parental_bond.c`) | `ServerEvent_CheckMultihitHits` | `ServerControl_DamageRoot` `+0x36`: a single-target move of a Parental Bond holder hits twice; the ability's handlers (`mechanics/abilities/parental_bond.c`) read `W2U_ParentalBondActive` and count the hits |
| `W2U_SimpleDamageReaction` (`damage.c`) | added to `ServerControl_SimpleDamageCore` | W2U's `EVENT_SIMPLE_DAMAGE_REACTION` after the item reaction (damage that isn't a move's hit); `W2U_SimpleDamageBeforeHP` for Emergency Exit. The injection build replaces the function whole, a decomp build adds the call |
| `W2U_DamageToRecoverCheck` (`damage.c`) | `ServerEvent_CheckDamageToRecover`, whole | the decomp's `ServerEvent_CheckDamageToRecover` returns it: `EVENT_CHECK_DAMAGE_TO_RECOVER` with the move's category too |
| `W2U_EffectivenessMultiplier`, `W2U_EffectivenessPowerMod`, `W2U_CheckTypeEffectiveness`, `W2U_CheckMoveEffectiveness`, `W2U_HasType`, `W2U_ClassifyEffectiveness`, `W2U_EffectivenessMessage` (`effectiveness.c`) | `GetTypeEffectivenessMultiplier`, `TypeEffectivenessPowerMod`, `ServerEvent_CheckTypeEffectiveness`, `ServerControl_CheckMoveEffectiveness`, `DoesMonHaveType`, `BtlCalc_ClassifyEffectiveness`, `ServerDisplay_EffectivenessMessage` (`0x21A508C`), all whole; and `W2U_DisplayEffectiveness` (x1/8 passed as x1/4) at the call sites that only compare a grade with x1: `VAR_TYPE_EFFECTIVENESS`'s setters (`0x21A32DE`, `0x21A597C`, `0x21A7D9A`), the records' count (`0x21A46B6`), the effectiveness message (`0x21A4E2E`, `0x21A7C34`) | W2U's grades past x4 (`W2U_EFF_*`), a Pokémon's added type (Forest's Curse, Trick-or-Treat) and Tar Shot (their state is here too), Thousand Arrows, W2U's overrides in `VAR_SET_TYPE_EFFECTIVENESS`. The injection build replaces the five functions, a decomp build's return these |
| `W2U_AIMoveEffectiveness`, `W2U_AICalcDamage` (`effectiveness.c`, `strong_weather.c`) | `ServerControl_CheckMoveEffectiveness` in `CalcMoveEffectiveness` (`0x21AB97E`), `ServerEvent_CalcDamage` in `AICalcDamage` (`0x21ABA24`) | the trainer AI's grade (its scripts test the engine's grades only: x1/8 as x1/4, x8 / x16 as x4) and damage estimate (the true grade back); a damaging move a strong weather stops (`W2U_StrongWeatherStopsMove`) is no effect to it, estimated as an immune hit, not 0 (the scripts take 0 for a status move) |
| `W2U_StrongWeatherBlocksChange` (`strong_weather.c`) | first in `ServerControl_ChangeWeatherCheck` | while a strong weather is up, another weather fails with its message. The strong weathers' state and server side are C (`include/w2u/strong_weather.h`), their abilities a C mechanic (`mechanics/abilities/strong_weather.c`); `w2u_strong_weather.cpp` keeps the injection build's hooks and view |

The state they keep for the mechanics (`W2U_MB_PendingMove`, Cud Chew, Opportunist, Mega Sol: `battle_api.h`'s
extensions) is in the same files. It is zero when empty, so a decomp build's overlay 167, loaded fresh for each
battle, starts clear; the injection build clears it at battle exit (`W2U_Resident_ResetBattleState`). The functions
are resident in both builds (`src/pokeweb_gameplay/meson.build`), since a battle module can be unloaded while the
engine runs, and pass the strict C99 check with the mechanics. `mb_resident.cpp` keeps only the hooks.

Where the injection build must replace a whole engine function to change one test in it, the C function is that
test, and a decomp build changes the test alone in the decomp's function: the rest stays the decomp's own code.

The Fairy type is data and constants rather than a call site. Fairy is type 17, and the typeless type (`TYPE_NULL`,
17 in the retail game) is 18. The injection build does this with `src/type_expansion/`:

- `GetTypeEffectiveness` and `GetTypeWeaknesses` read the 18x18 chart, `data/pml/types/type_chart.bin`;
- `Fairy_BattleLimitAdjust.s` holds byte patches, each a whole Thumb instruction (CTRMap copies a `FULL_COPY` in
  halfwords). They cover:
  - the same-type bonus and the typeless move;
  - Roost's typeless Flying in `splitTypeCore`;
  - `DoesMonHaveType`, Color Change and Conversion 2;
  - the "no move yet" type that `BattleMon_Create`, `ClearUsedMoveFlag` and `TransformSet` set;
  - the move buttons' palettes.

A decomp build defines the two numbers in its own header, gives `btl_calc.c` the same chart (taken from that file
when the build runs), and makes the same tests use `TYPE_NULL`. Its move-button palette table gets Fairy as
Normal's palette, because W2U's 572 is a file W2U adds to archive 11 and the decomp has no export of it yet.

## Writing a mechanic

```c
/* src/mechanics/abilities/fluffy.c */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"            /* data IDs: abilities, types */

static void HandlerFluffyDamageRatio(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work) { ... }

W2U_HANDLER_TABLE(FluffyHandlers) = {
    { EVENT_DAMAGE_RATIO, HandlerFluffyDamageRatio },
};
W2U_MECHANIC(ABILITY, ABIL_FLUFFY, FluffyHandlers);
W2U_MECHANIC(ABILITY, ABIL_ICE_SCALES, FluffyHandlers);
```

Then:

1. List it in `src/meson.build` (`w2u_mechanics_sources`).
2. In `src/pokeweb_gameplay/battle_modules/registry.json`, add the file to the module's `extra_sources` (as
   `../mechanics/...`) and the module's `entries`, one per `W2U_MECHANIC` line.
3. Declare the table for the C++ side in `src/mechanics/w2u_mechanics.h`, so the generated registry entries can count
   it.
4. Regenerate the registry:
   ```sh
   python tools/generate_w2u_battle_registry.py --registry src/pokeweb_gameplay/battle_modules/registry.json --output src/pokeweb_gameplay/w2u_battle_module_registry.inc --api-output src/pokeweb_gameplay/w2u_battle_module_api_entries.inc --meson-output src/pokeweb_gameplay/battle_modules/meson.build --source src/pokeweb_gameplay/w2u_abilities.cpp --source src/pokeweb_gameplay/w2u_moves.cpp --source src/pokeweb_gameplay/w2u_items.cpp --source src/pokeweb_gameplay/w2u_field_effects.cpp --source src/pokeweb_gameplay/w2u_strong_weather.cpp
   ```
   On Windows it writes CRLF; convert the outputs back to LF.

The build checks the rest:

- `verify_w2u_battle_registry`: every `W2U_MECHANIC` line has its registry entry and the other way round.
- `verify_w2u_mechanics_c`: each file passes as strict C99 (`-std=c99 -Wall -Wextra -pedantic -Werror`). The battle
  modules themselves compile it with g++, like the rest.

Data IDs the C mechanics read live in `megab2w2/mb_ids.h` (abilities, types, W2U's extra move flags), visible to C;
a vanilla ID that exists only as a C++ enumerator (`ABIL_DAMP`) is defined in the mechanic itself. Never define a
name in `engine.h` that a data header has too: the mechanics compile as C++ as well, where both are seen.

State a mechanic keeps between events beyond the item's `work[]` (Protean's once-per-switch-in flag, Mirror
Armor's reflected marks, Berserk's HP before a move, Electromorphosis' charge) is a file-static array per monId,
as MegaB2W2 kept it. On White 2 that is battle-scoped already: `W2U_BattleState_OnBattleExit` and the first turn's
setup (`W2U_BattleModules_Reset`) unload every battle module, and the next battle loads them again from their files,
which store the zeroed arrays as zeros (`bss_bytes: 0` in the heap audit). So MegaB2W2's battle-start resets
(`Charge_ResetForBattle`, `IntrepidSword_ResetForBattle`), which nothing in W2U calls, are not needed here. A decomp
build links the mechanics in for good: there they need a battle-start reset, which the engine interface's battle
hooks will have to provide.

## Rules

- No addresses or struct offsets in a mechanic: they belong in `engine.h`.
- A mechanic includes `w2u/battle_api.h` and data headers only.
- No `switch` over more than a few cases. Jump tables need a libgcc helper the ESDB lacks; use `if` chains or tables.
- No runtime division by a variable (`__aeabi_uidiv` is missing too).
- Give even static functions and tables names unique to the mechanic (`FluffyRowMatches`, not `RowMatches`):
  rpmtool resolves symbols by name across a module's files, static or not.
- Mechanic code never touches the PMC heap, module groups or DLL loading.

## Converted so far

| Mechanic | File | Replaces | Checked with |
|---|---|---|---|
| Fluffy, Ice Scales, Aura Guard | `src/mechanics/abilities/fluffy.c` | `w2u_abilities.cpp` `HandlerFluffy`, `megab2w2/abilities/Fluffy.cpp` | `FLUFFY_CONTACT`, `FLUFFY_FIRE`, `FLUFFY_FIRE_CONTACT` (`wave_shared.yml`), `ICE_SCALES`, `AURA_GUARD` (`wave_a.yml`): the same damage as before |
| Power Spot, Steely Spirit, Battery | `abilities/power_spot.c` | `megab2w2/abilities/PowerSpot.cpp`, `w2u_abilities.cpp` `HandlerBattery` | `POWER_SPOT`, `STEELY_SPIRIT` (`wave_a.yml`), `BATTERY` (`wave_shared.yml`) |
| Punk Rock | `abilities/punk_rock.c` | `megab2w2/abilities/PunkRock.cpp` | `PUNK_ROCK`, `PUNK_ROCK_DEF` (`wave_a.yml`) |
| Earth Eater, Well-Baked Body | `abilities/absorb.c` | `megab2w2/abilities/EarthEater.cpp`, `WellBakedBody.cpp` | `EARTH_EATER`, `WELL_BAKED_BODY` (`wave_a.yml`) |
| Mind's Eye | `abilities/minds_eye.c` | `megab2w2/abilities/MindsEye.cpp` | `MINDS_EYE` (`wave_a.yml`) |
| Propeller Tail, Stalwart | `abilities/propeller_tail.c` | `megab2w2/abilities/PropellerTail.cpp` | `PROPELLER_TAIL`, `STALWART_FOLLOW_ME` and their controls (`wave_c.yml`) |
| Good as Gold | `abilities/good_as_gold.c` | `megab2w2/abilities/GoodAsGold.cpp` | the five `GOOD_AS_GOLD*` scenarios (`wave_a.yml`), transcripts identical |
| Neuroforce | `abilities/neuroforce.c` | `megab2w2/abilities/Neuroforce.cpp` | `NEUROFORCE` (`wave_a.yml`) |
| Stamina, Water Compaction, Steam Engine, Thermal Exchange | `abilities/stamina.c` | `w2u_abilities.cpp` `HandlerStamina` / `HandlerWaterCompaction`, `megab2w2/abilities/Stamina.cpp` | `STAMINA`, `WATER_COMPACTION` (`wave_shared.yml`), `STEAM_ENGINE`, `THERMAL_EXCHANGE`, `THERMAL_EXCHANGE_BURN` (`wave_a.yml`), transcripts identical |
| Eelevate | `abilities/eelevate.c` | `megab2w2/abilities/BeastBoost.cpp` (its Beast Boost table was never registered) | `EELEVATE`, `EELEVATE_KO`, `EELEVATE_RAW` (`wave_a.yml`); `BEAST_BOOST` unchanged |
| Damp | `abilities/damp.c` | `megab2w2/abilities/Damp.cpp` | `MISTY_EXPLOSION_DAMP`, `EXPLOSION_DAMP`, `MIND_BLOWN_DAMP`, `MIND_BLOWN_CONTROL`, `SUN_CONTROL` (`wave_field.yml`) |
| Spicy Spray, Toxic Chain | `abilities/status_on_hit.c` | `megab2w2/abilities/SpicySpray.cpp`, `ToxicChain.cpp` | `SPICY_SPRAY`, `TOXIC_CHAIN` (`wave_a.yml`): burned / badly poisoned as before |
| Screen Cleaner | `abilities/screen_cleaner.c` | `megab2w2/abilities/ScreenCleaner.cpp` | `SCREEN_CLEANER`, `SCREEN_CLEANER_NONE` (`wave_a.yml`) |
| Wind Rider | `abilities/wind_rider.c` | `megab2w2/abilities/WindRider.cpp` | `WIND_RIDER`, `WIND_RIDER_TAILWIND` (`wave_a.yml`) |
| Sword / Beads / Tablets / Vessel of Ruin | `abilities/ruin.c` | `megab2w2/abilities/Ruin.cpp` | `SWORD_OF_RUIN`, `BEADS_OF_RUIN`, `TABLETS_OF_RUIN`, `VESSEL_OF_RUIN` (`wave_a.yml`) |
| Queenly Majesty, Dazzling, Armor Tail | `abilities/queenly_majesty.c` | `megab2w2/abilities/QueenlyMajesty.cpp`, `w2u_abilities.cpp` `HandlerQueenlyMajesty` | `ARMOR_TAIL` (`wave_a.yml`), `QUEENLY_MAJESTY`, `QUEENLY_MAJESTY_SPREAD`, `QUEENLY_MAJESTY_NORMAL`, `QUEENLY_MAJESTY_ALLY`, `DAZZLING` (`wave_shared.yml`) |
| Grim Neigh, As One (both) | `abilities/neigh.c` | `megab2w2/abilities/Neigh.cpp` | `GRIM_NEIGH`, `AS_ONE` (`wave_a.yml`) |
| Hospitality | `abilities/hospitality.c` | `megab2w2/abilities/Hospitality.cpp` | `HOSPITALITY`, `HOSPITALITY_FULL` (`wave_a.yml`) |
| Gorilla Tactics | `abilities/gorilla_tactics.c` | `megab2w2/abilities/GorillaTactics.cpp` | `GORILLA_TACTICS`, `GORILLA_TACTICS_LOCK` (`wave_c.yml`) |
| Purifying Salt | `abilities/purifying_salt.c` | `megab2w2/abilities/PurifyingSalt.cpp` | `PURIFYING_SALT`, `PURIFYING_SALT_GHOST`, `PURIFYING_SALT_YAWN` (`wave_a.yml`) |
| Protean, Libero | `abilities/protean.c` | `megab2w2/abilities/Protean.cpp`, `w2u_abilities.cpp` `HandlerProtean` | `LIBERO` (`wave_a.yml`), `PROTEAN` (`wave_shared.yml`) |
| Mirror Armor | `abilities/mirror_armor.c` | `megab2w2/abilities/MirrorArmor.cpp` | `MIRROR_ARMOR`, `MIRROR_ARMOR_INTIMIDATE` (`wave_a.yml`) |
| Berserk, Anger Shell | `abilities/berserk.c` | `megab2w2/abilities/Berserk.cpp`, `w2u_abilities.cpp` `HandlerBerserk` | `ANGER_SHELL` (`wave_a.yml`), `BERSERK`, `BERSERK_SHEER_FORCE`, `BERSERK_SHEER_FORCE_PLAIN` (`wave_shared.yml`) |
| Sharpness, Transistor, Dragon's Maw, Rocky Payload, Fire Mane | `abilities/boost.c` | `megab2w2/abilities/Boost.cpp` (its Tough Claws / Strong Jaw / Mega Launcher / Steelworker rows were never reached) | `SHARPNESS`, `TRANSISTOR`, `DRAGONS_MAW`, `ROCKY_PAYLOAD`, `FIRE_MANE` (`wave_a.yml`); `STEELWORKER` unchanged |
| Electromorphosis, Wind Power | `abilities/charge.c` | `megab2w2/abilities/Charge.cpp` | `ELECTROMORPHOSIS`, `WIND_POWER` (`wave_a.yml`) |
| Unseen Fist, Piercing Drill | `abilities/unseen_fist.c` | `megab2w2/abilities/UnseenFist.cpp` | `UNSEEN_FIST`, `UNSEEN_FIST_NONCONTACT`, `PIERCING_DRILL` (`wave_c.yml`) |
| Lingering Aroma, Wandering Spirit | `abilities/lingering_aroma.c` | `megab2w2/abilities/LingeringAroma.cpp` | `LINGERING_AROMA`, `WANDERING_SPIRIT` (`wave_a.yml`) |
| Cotton Down, Perish Body, Toxic Debris | `abilities/hit_reactions.c` | `megab2w2/abilities/HitReactions.cpp` | `COTTON_DOWN`, `PERISH_BODY`, `TOXIC_DEBRIS` (`wave_a.yml`) |
| Poison Puppeteer | `abilities/poison_puppeteer.c` | its part of `megab2w2/abilities/MoveAbilities.cpp` | `POISON_PUPPETEER` (`wave_c.yml`); `MYCELIUM_MIGHT`, `MEGA_SOL*` unchanged |
| Pastel Veil | `abilities/pastel_veil.c` | `megab2w2/abilities/Veil.cpp` (only Pastel Veil used it) | `PASTEL_VEIL`, `PASTEL_VEIL_ALLY` (`wave_a.yml`); `AROMA_VEIL`, `FLOWER_VEIL`, `SWEET_VEIL` unchanged |
| Tera Shell | `abilities/tera_shell.c` | `megab2w2/abilities/Shields.cpp` (only Tera Shell used it) | `TERA_SHELL` (`wave_a.yml`); `DISGUISE`, `COMATOSE` unchanged |
| Guard Dog (and the tracked Intimidate it needs) | `abilities/guard_dog.c` | `megab2w2/abilities/GuardDog.cpp` | `GUARD_DOG`, `GUARD_DOG_ROAR`, `MIRROR_ARMOR_INTIMIDATE` (`wave_a.yml`) |
| Intrepid Sword, Dauntless Shield | `abilities/intrepid_sword.c` | `megab2w2/abilities/IntrepidSword.cpp` | `INTREPID_SWORD`, `DAUNTLESS_SHIELD` (`wave_a.yml`) |
| Quick Draw | `abilities/quick_draw.c` | `megab2w2/abilities/QuickDraw.cpp` | `QUICK_DRAW`, `QUICK_DRAW_STATUS` (`wave_c.yml`) |
| Mycelium Might, Mega Sol | `abilities/move_abilities.c` | the rest of `megab2w2/abilities/MoveAbilities.cpp` | `MYCELIUM_MIGHT`, `MEGA_SOL`, `MEGA_SOL_FIRE` (`wave_c.yml`) |
| Protosynthesis, Quark Drive | `abilities/protosynthesis.c` | `megab2w2/abilities/Protosynthesis.cpp` | the seven `PROTOSYNTHESIS*` / `QUARK_DRIVE*` scenarios (`wave_b.yml`) |
| Sand Spit, Seed Sower | `abilities/sand_spit.c` | `megab2w2/abilities/SandSpit.cpp` | `SAND_SPIT`, `SEED_SOWER` (`wave_b.yml`) |
| Orichalcum Pulse, Hadron Engine, Grass Pelt, Mimicry | `abilities/terrain_abilities.c` | `megab2w2/abilities/TerrainAbilities.cpp` | `ORICHALCUM_PULSE`, `HADRON_ENGINE`, `MIMICRY` (`wave_b.yml`), `GRASS_PELT` (`wave_shared.yml`) |
| Ripen, Opportunist, Cud Chew | `abilities/effect_abilities.c` | `megab2w2/abilities/EffectAbilities.cpp` | `RIPEN`, `OPPORTUNIST`, `OPPORTUNIST_BOTH`, `CUD_CHEW` (`wave_c.yml`) |
| Curious Medicine, Costar, Supersweet Syrup | `abilities/entry_effects.c` | `megab2w2/abilities/EntryEffects.cpp` | `CURIOUS_MEDICINE`, `COSTAR`, `SUPERSWEET_SYRUP` (`wave_a.yml`) |
| Supreme Overlord | `abilities/supreme_overlord.c` | `megab2w2/abilities/SupremeOverlord.cpp` | `SUPREME_OVERLORD`, `SUPREME_OVERLORD_NONE` (`wave_a.yml`) |
| Ice Face, Gulp Missile, Hunger Switch, Zero to Hero, Commander | `abilities/form_abilities.c` | `megab2w2/abilities/FormAbilities.cpp` (and the then empty `megab2w2/mb_ability_tables.h`) | the twelve `ICE_FACE*`, `GULP_MISSILE*`, `HUNGER_SWITCH`, `ZERO_TO_HERO`, `COMMANDER*` scenarios (`wave_forms.yml`), transcripts identical |

Behaviour decided 2026-10-16 (where W2U and MegaB2W2 had implemented an ability twice, or a finding was a bug):
Protean and Libero share the Gen 9 rule (once per switch-in; not for calling moves or future attacks); Berserk and
Anger Shell share Showdown's timing (once after the move, from above half HP to half or less); Queenly Majesty,
Dazzling and Armor Tail show the holder's popup and "X cannot use Y!" (bank 18 905-907) once per move, and read the
move's own priority (W2U's `W2U_GetQueuedMovePriority` adds the turn-order bracket, so a Quick Claw activation made
an ordinary move count; W2U's Psychic Terrain still uses it); Protosynthesis and Quark Drive apply stat stages once;
Eelevate compares the stats without stages, as Beast Boost does; Bulbasaur's base HP is 45 again (it was 50). Black
2's baseline copy (`b2_baseline/w2u_abilities.cpp.inc`) keeps W2U's earlier Protean, Berserk and Queenly Majesty.
Battery stays as it is for now.

MegaB2W2 code that was never reached is gone rather than converted: the Aroma, Flower and Sweet Veil rows (W2U's
own handlers serve those), MegaB2W2's Disguise (W2U's `DisguiseHandlers`), its Comatose (never registered; W2U
handles Comatose in its own hooks) and the Boost rows of Tough Claws, Strong Jaw, Mega Launcher and Steelworker.

Beast Boost itself stays in `w2u_abilities.cpp` for now: it picks the highest stat from the BattleMon's fields,
which needs the BattleMon layout in `engine.h` first.

Found while converting: `GetBattleMonStat(8 .. 0xC)` returns the stats with stat stages applied
(`RawBattleMonStat`, IRDO.yml's `BattleMon_GetRealStat`, is the unstaged one, with Wonder Room's swap). MegaB2W2's
`BestStat` (Eelevate) therefore picked the highest *boosted* stat, and its `BestStatWithStages` (Protosynthesis,
Quark Drive) applied the stages a second time; both fixed 2026-10-16 (`W2U_BestStatOf`). Beast Boost reads the
BattleMon's stat fields, which differs from Eelevate's `RawBattleMonStat` only under Wonder Room.

Two MegaB2W2 names that said the wrong thing, behaviour unchanged: event 0x5D is "a stat change was applied" (raises
too: Opportunist copies raises from it), not "stat lowered"; and bit 24 of the force-use-item header, which MegaB2W2 and
PW2Code set for Cud Chew as "eat, not held", is the header's `checkPrevResult` in the decomp's layout.

Battery keeps W2U's effect on the attacking stat (`EVENT_ATTACKING_STAT`). Showdown (and the MegaB2W2 row that was
never registered) boosts the move's base power, which rounds differently; switching would be a behaviour change.

Black 2 builds from its baseline copy (`b2_baseline/w2u_abilities.cpp.inc`), whose Fluffy, Battery, Stamina and
Water Compaction stay as they were; the other mechanics here are White 2 only. Where W2U and MegaB2W2 implemented an
ability twice, the conversion keeps the implementation the registry actually used, so nothing changes in game.
