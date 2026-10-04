// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Protean.cpp); see docs/megab2w2-integration.md.
// Protean / Libero (Gen 6 / 8; data/abilities.yml PROTEAN, LIBERO): before it uses a move, the holder becomes that
// move's type (its final type: -ate abilities, Weather Ball) - Gen 9 / Showdown: once per switch-in, only when the
// type actually changes, not for Struggle or a move that calls another (Metronome, Sleep Talk...: the called move
// counts). EVENT_MOVE_START (the attacker in VAR_ATTACKING_MON) + Conversion's EFFECT_CHANGE_TYPE with the popup;
// the engine shows "X transformed into the Y type!".
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u16 PROTEAN_SKIP[] = { 165 /* Struggle */, 118 /* Metronome */, 119 /* Mirror Move */, 214 /* Sleep Talk */,
                                 267 /* Nature Power */, 274 /* Assist */, 382 /* Me First */, 383 /* Copycat */ };
bool g_proteanUsed[ability::MAX_POKE_ID];

void HandlerProteanSwitchIn(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Subject() == pokeID && pokeID < ability::MAX_POKE_ID) g_proteanUsed[pokeID] = false;
}
void HandlerProteanMoveStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID || g_proteanUsed[pokeID]) return;
    u16 move = ability::Move();
    for (u16 skip : PROTEAN_SKIP) if (move == skip) return;
    u32 type = ability::FinalMoveType(sf, move, pokeID);
    u16 pair = PokeTypePair_MakePure(type);
    if (GetPokeType(GetBattleMon(sf, pokeID)) == pair) return;
    g_proteanUsed[pokeID] = true;
    auto* p = (HandlerParam_ChangeType*)BattleHandler_PushWork(sf, EFFECT_CHANGE_TYPE, pokeID);
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->typePair = pair;
    p->pokeID = (u8)pokeID;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Protean: poke %d becomes type %d (move %d)", pokeID, type, move);
}

constexpr BattleEventHandlerTableEntry PROTEAN_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerProteanSwitchIn },
    { EVENT_MOVE_START, HandlerProteanMoveStart },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddProtean(u32* packed) {
    *packed = sizeof(PROTEAN_HANDLERS) / sizeof(PROTEAN_HANDLERS[0]);
    return PROTEAN_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_ProteanHandlers[2] = {PROTEAN_HANDLERS[0], PROTEAN_HANDLERS[1]};
static_assert(sizeof(PROTEAN_HANDLERS) / sizeof(PROTEAN_HANDLERS[0]) == 2, "MB_ProteanHandlers");
