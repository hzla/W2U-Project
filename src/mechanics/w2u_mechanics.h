// The handler tables of the C mechanics (src/mechanics, written against include/w2u/battle_api.h), declared for the
// C++ side: the battle module registry's generated entries (w2u_battle_module_api_entries.inc) count them. The
// mechanics define them as const BattleEventHandlerEntry[] (the same layout as BattleEventHandlerTableEntry).
#pragma once
#include "w2u_abilities.h"

extern "C" BattleEventHandlerTableEntry FluffyHandlers[1];   // abilities/fluffy.c: Fluffy, Ice Scales, Aura Guard
extern "C" BattleEventHandlerTableEntry PowerSpotHandlers[1];  // abilities/power_spot.c: Power Spot, Steely Spirit
extern "C" BattleEventHandlerTableEntry BatteryHandlers[1];    // abilities/power_spot.c
extern "C" BattleEventHandlerTableEntry PunkRockHandlers[2];   // abilities/punk_rock.c
extern "C" BattleEventHandlerTableEntry EarthEaterHandlers[1];    // abilities/absorb.c
extern "C" BattleEventHandlerTableEntry WellBakedBodyHandlers[1]; // abilities/absorb.c
extern "C" BattleEventHandlerTableEntry MindsEyeHandlers[4];      // abilities/minds_eye.c
extern "C" BattleEventHandlerTableEntry PropellerTailHandlers[1]; // abilities/propeller_tail.c: Propeller Tail, Stalwart
extern "C" BattleEventHandlerTableEntry GoodAsGoldHandlers[1];
extern "C" BattleEventHandlerTableEntry NeuroforceHandlers[1];
