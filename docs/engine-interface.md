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
crosswalk later. It must not be included together with `w2u_abilities.h` or the `megab2w2` battle headers, which
declare the same engine under older names (it `#error`s).

## Layer B: `include/w2u/battle_api.h`

What mechanics would otherwise write by hand: who the event is about (`W2U_Attacker`, `W2U_Defender`, `W2U_Move`,
`W2U_MoveType`), moves (`W2U_MoveCategory`, `W2U_MoveHasFlag`, `W2U_MakesContact`, `W2U_TargetsPokemon`), sides and the field
(`W2U_IsAlly`, `W2U_OnField`, `W2U_HasActiveAbility`, `W2U_FirstFieldHolder`), the holder (`W2U_HolderAbility`), ratios (`W2U_MulRatio`, `W2U_MulMovePower`), effects through the
handler-effect queue (`W2U_PopupMessage`, `W2U_PopupMessageAbout`, `W2U_ChangeStatStage`, `W2U_PopupStatChange` (W2U's own abilities' way), `W2U_AddCondition`, `W2U_BlockMove`), `W2U_IsSimulating`. It grows from
`megab2w2/ability_api.h` as mechanics need more.

`engine.h` defines the handler-effect work it fills (`BattleHandlerMessageParam`, `BattleHandlerStatChangeParam`) as
the decomp does, with compile-time checks of the offsets the vanilla code uses. A name the cleanup gives that
`IRDO.yml` spells differently is mapped there for injection builds (`BtlCalc_ClassifyEffectiveness` is
`TypeEffectivenessClass`).

`w2u-local/decomp/wire_mechanic.py` does the registry steps below for converted MegaB2W2 files.

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

State a mechanic keeps between events beyond the item's `work[]` (Libero's once-per-switch-in flag, Mirror
Armor's reflected marks, Anger Shell's HP before a move, Electromorphosis' charge) is a file-static array per monId,
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
| Eelevate | `abilities/eelevate.c` | `megab2w2/abilities/BeastBoost.cpp` (its Beast Boost table was never registered) | `EELEVATE`, `EELEVATE_KO` (`wave_a.yml`); `BEAST_BOOST` unchanged |
| Damp | `abilities/damp.c` | `megab2w2/abilities/Damp.cpp` | `MISTY_EXPLOSION_DAMP`, `EXPLOSION_DAMP`, `MIND_BLOWN_DAMP`, `MIND_BLOWN_CONTROL`, `SUN_CONTROL` (`wave_field.yml`) |
| Spicy Spray, Toxic Chain | `abilities/status_on_hit.c` | `megab2w2/abilities/SpicySpray.cpp`, `ToxicChain.cpp` | `SPICY_SPRAY`, `TOXIC_CHAIN` (`wave_a.yml`): burned / badly poisoned as before |
| Screen Cleaner | `abilities/screen_cleaner.c` | `megab2w2/abilities/ScreenCleaner.cpp` | `SCREEN_CLEANER`, `SCREEN_CLEANER_NONE` (`wave_a.yml`) |
| Wind Rider | `abilities/wind_rider.c` | `megab2w2/abilities/WindRider.cpp` | `WIND_RIDER`, `WIND_RIDER_TAILWIND` (`wave_a.yml`) |
| Sword / Beads / Tablets / Vessel of Ruin | `abilities/ruin.c` | `megab2w2/abilities/Ruin.cpp` | `SWORD_OF_RUIN`, `BEADS_OF_RUIN`, `TABLETS_OF_RUIN`, `VESSEL_OF_RUIN` (`wave_a.yml`) |
| Armor Tail | `abilities/armor_tail.c` | `megab2w2/abilities/QueenlyMajesty.cpp` (only Armor Tail used it) | `ARMOR_TAIL` (`wave_a.yml`); `QUEENLY_MAJESTY`, `DAZZLING` unchanged |
| Grim Neigh, As One (both) | `abilities/neigh.c` | `megab2w2/abilities/Neigh.cpp` | `GRIM_NEIGH`, `AS_ONE` (`wave_a.yml`) |
| Hospitality | `abilities/hospitality.c` | `megab2w2/abilities/Hospitality.cpp` | `HOSPITALITY`, `HOSPITALITY_FULL` (`wave_a.yml`) |
| Gorilla Tactics | `abilities/gorilla_tactics.c` | `megab2w2/abilities/GorillaTactics.cpp` | `GORILLA_TACTICS`, `GORILLA_TACTICS_LOCK` (`wave_c.yml`) |
| Purifying Salt | `abilities/purifying_salt.c` | `megab2w2/abilities/PurifyingSalt.cpp` | `PURIFYING_SALT`, `PURIFYING_SALT_GHOST`, `PURIFYING_SALT_YAWN` (`wave_a.yml`) |
| Libero | `abilities/libero.c` | `megab2w2/abilities/Protean.cpp` (only Libero used it) | `LIBERO` (`wave_a.yml`); `PROTEAN` unchanged |
| Mirror Armor | `abilities/mirror_armor.c` | `megab2w2/abilities/MirrorArmor.cpp` | `MIRROR_ARMOR`, `MIRROR_ARMOR_INTIMIDATE` (`wave_a.yml`) |
| Anger Shell | `abilities/anger_shell.c` | `megab2w2/abilities/Berserk.cpp` (only Anger Shell used it) | `ANGER_SHELL` (`wave_a.yml`); `BERSERK`, `BERSERK_SHEER_FORCE*` unchanged |
| Sharpness, Transistor, Dragon's Maw, Rocky Payload, Fire Mane | `abilities/boost.c` | `megab2w2/abilities/Boost.cpp` (its Tough Claws / Strong Jaw / Mega Launcher / Steelworker rows were never reached) | `SHARPNESS`, `TRANSISTOR`, `DRAGONS_MAW`, `ROCKY_PAYLOAD`, `FIRE_MANE` (`wave_a.yml`); `STEELWORKER` unchanged |
| Electromorphosis, Wind Power | `abilities/charge.c` | `megab2w2/abilities/Charge.cpp` | `ELECTROMORPHOSIS`, `WIND_POWER` (`wave_a.yml`) |
| Unseen Fist, Piercing Drill | `abilities/unseen_fist.c` | `megab2w2/abilities/UnseenFist.cpp` | `UNSEEN_FIST`, `UNSEEN_FIST_NONCONTACT`, `PIERCING_DRILL` (`wave_c.yml`) |
| Lingering Aroma, Wandering Spirit | `abilities/lingering_aroma.c` | `megab2w2/abilities/LingeringAroma.cpp` | `LINGERING_AROMA`, `WANDERING_SPIRIT` (`wave_a.yml`) |
| Cotton Down, Perish Body, Toxic Debris | `abilities/hit_reactions.c` | `megab2w2/abilities/HitReactions.cpp` | `COTTON_DOWN`, `PERISH_BODY`, `TOXIC_DEBRIS` (`wave_a.yml`) |
| Poison Puppeteer | `abilities/poison_puppeteer.c` | its part of `megab2w2/abilities/MoveAbilities.cpp` | `POISON_PUPPETEER` (`wave_c.yml`); `MYCELIUM_MIGHT`, `MEGA_SOL*` unchanged |
| Pastel Veil | `abilities/pastel_veil.c` | `megab2w2/abilities/Veil.cpp` (only Pastel Veil used it) | `PASTEL_VEIL`, `PASTEL_VEIL_ALLY` (`wave_a.yml`); `AROMA_VEIL`, `FLOWER_VEIL`, `SWEET_VEIL` unchanged |
| Tera Shell | `abilities/tera_shell.c` | `megab2w2/abilities/Shields.cpp` (only Tera Shell used it) | `TERA_SHELL` (`wave_a.yml`); `DISGUISE`, `COMATOSE` unchanged |

Queenly Majesty and Dazzling keep W2U's own handler (`w2u_abilities.cpp`), which blocks without a popup and uses
W2U's own priority helper; Armor Tail keeps MegaB2W2's rule (the popup and "It doesn't affect X..."). Converting
W2U's would mean either rule for all three, a behaviour change to decide on.

MegaB2W2 code that was never reached is gone rather than converted: the Aroma, Flower and Sweet Veil rows (W2U's
own handlers serve those), MegaB2W2's Disguise (W2U's `DisguiseHandlers`), its Comatose (never registered; W2U
handles Comatose in its own hooks) and the Boost rows of Tough Claws, Strong Jaw, Mega Launcher and Steelworker.

Beast Boost itself stays in `w2u_abilities.cpp` for now: it picks the highest stat from the BattleMon's fields,
which needs the BattleMon layout in `engine.h` first.

Found while converting (behaviour unchanged): `GetBattleMonStat(8 .. 0xC)` returns the stats with stat stages
applied (`RawBattleMonStat`, IRDO.yml's `BattleMon_GetRealStat`, is the unstaged one, with Wonder Room's swap).
MegaB2W2's `BestStat`, which Eelevate uses, therefore picks the highest *boosted* stat, unlike Beast Boost and
Showdown; its `BestStatWithStages` applies the stages a second time.

Battery keeps W2U's effect on the attacking stat (`EVENT_ATTACKING_STAT`). Showdown (and the MegaB2W2 row that was
never registered) boosts the move's base power, which rounds differently; switching would be a behaviour change.

Black 2 builds from its baseline copy (`b2_baseline/w2u_abilities.cpp.inc`), whose Fluffy, Battery, Stamina and
Water Compaction stay as they were; the other mechanics here are White 2 only. Where W2U and MegaB2W2 implemented an
ability twice, the conversion keeps the implementation the registry actually used, so nothing changes in game.
