// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Neuroforce.cpp); see docs/megab2w2-integration.md.
// Neuroforce (Gen 7; data/abilities.yml NEUROFORCE): the holder's super-effective hits deal 1.25x (Gen 9). Tinted
// Lens' shape (EVENT_DAMAGE_RATIO, attacker side, effectiveness class 2 = super effective; Tinted Lens: 3 = resisted).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
extern "C" u32 TypeEffectivenessClass(u32 eff);   // 0x21BD328: 2 super effective, 3 not very effective
void HandlerNeuroforceDamageRatio(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    if (TypeEffectivenessClass((u32)BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS)) != 2) return;
    ability::MulRatio(5120);                                    // x1.25
    if (!ability::Simulating(sf)) MLOG("[ABIL] Neuroforce: poke %d move %d x1.25", pokeID, ability::Move());
}

constexpr BattleEventHandlerTableEntry NEUROFORCE_HANDLERS[] = {
    { EVENT_DAMAGE_RATIO, HandlerNeuroforceDamageRatio },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddNeuroforce(u32* packed) {
    *packed = sizeof(NEUROFORCE_HANDLERS) / sizeof(NEUROFORCE_HANDLERS[0]);
    return NEUROFORCE_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_NeuroforceHandlers[1] = {NEUROFORCE_HANDLERS[0]};
static_assert(sizeof(NEUROFORCE_HANDLERS) / sizeof(NEUROFORCE_HANDLERS[0]) == 1, "MB_NeuroforceHandlers");
