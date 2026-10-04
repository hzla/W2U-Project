// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/ToxicChain.cpp); see docs/megab2w2-integration.md.
// Toxic Chain (Gen 9; data/abilities.yml TOXIC_CHAIN): any damaging hit of the holder badly poisons the target 30% of
// the time (not through a substitute or Shield Dust). Poison Touch's handler without the contact check, with Toxic's
// continuation (turns 15/15 = bad poison) built the way the engine builds a move's (PML_MoveGetSickCont +
// BTL_MakeSickCont). The status' own text follows (no extra message).
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
constexpr u16 MOVE_TOXIC = 92;
void HandlerToxicChainAfterDamageReaction(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    if (BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) != 0 || BattleEventVar_GetValue(VAR_NO_SECONDARY) != 0) return;
    u32 target = ability::Defender();
    if (target == pokeID || !AbilityEvent_RollEffectChance(sf, 30)) return;
    u32 moveCont = PML_MoveGetSickCont(MOVE_TOXIC);
    u32 cont = 0;
    BTL_MakeSickCont(moveCont | (moveCont << 16), GetBattleMon(sf, pokeID), &cont);   // as the engine passes it
    auto* p = (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->condition = COND_POISON;
    p->cont = cont;
    p->pokeID = (u8)target;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Toxic Chain: poke %d badly poisons poke %d", pokeID, target);
}

constexpr BattleEventHandlerTableEntry TOXIC_CHAIN_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerToxicChainAfterDamageReaction },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddToxicChain(u32* packed) {
    *packed = sizeof(TOXIC_CHAIN_HANDLERS) / sizeof(TOXIC_CHAIN_HANDLERS[0]);
    return TOXIC_CHAIN_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_ToxicChainHandlers[1] = {TOXIC_CHAIN_HANDLERS[0]};
static_assert(sizeof(TOXIC_CHAIN_HANDLERS) / sizeof(TOXIC_CHAIN_HANDLERS[0]) == 1, "MB_ToxicChainHandlers");
