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
`W2U_MoveType`), moves (`W2U_MoveCategory`, `W2U_MakesContact`), the holder (`W2U_HolderAbility`), ratios
(`W2U_MulRatio`, `W2U_RatioMul`), `W2U_IsSimulating`. It grows from `megab2w2/ability_api.h`; the effect helpers
(popups, stat stage changes, messages) come with the first mechanic that needs the handler-effect structs.

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

## Rules

- No addresses or struct offsets in a mechanic: they belong in `engine.h`.
- A mechanic includes `w2u/battle_api.h` and data headers only.
- No `switch` over more than a few cases. Jump tables need a libgcc helper the ESDB lacks; use `if` chains or tables.
- No runtime division by a variable (`__aeabi_uidiv` is missing too).
- Mechanic code never touches the PMC heap, module groups or DLL loading.

## Converted so far

| Mechanic | File | Replaces | Checked with |
|---|---|---|---|
| Fluffy, Ice Scales, Aura Guard | `src/mechanics/abilities/fluffy.c` | `w2u_abilities.cpp` `HandlerFluffy`, `megab2w2/abilities/Fluffy.cpp` | `FLUFFY_CONTACT`, `FLUFFY_FIRE`, `FLUFFY_FIRE_CONTACT` (`wave_shared.yml`), `ICE_SCALES`, `AURA_GUARD` (`wave_a.yml`): the same damage as before |

Black 2 builds from its baseline copy (`b2_baseline/w2u_abilities.cpp.inc`), whose Fluffy stays as it was.
