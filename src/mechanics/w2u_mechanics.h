// The handler tables of the C mechanics (src/mechanics, written against include/w2u/battle_api.h), declared for the
// C++ side: the battle module registry's generated entries (w2u_battle_module_api_entries.inc) count them. The
// mechanics define them as const BattleEventHandlerEntry[] (the same layout as BattleEventHandlerTableEntry).
#pragma once
#include "w2u_abilities.h"

extern "C" BattleEventHandlerTableEntry FluffyHandlers[1];   // abilities/fluffy.c: Fluffy, Ice Scales, Aura Guard
