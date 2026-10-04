// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/QueenlyMajesty.cpp); see docs/megab2w2-integration.md.
// Queenly Majesty (Gen 7; data/abilities.yml QUEENLY_MAJESTY; Dazzling / Armor Tail are the same): a foe's move with
// priority above 0 (after Prankster / Gale Wings / Triage: ServerEvent_GetMovePriority) aimed at the holder or its
// ally fails (Gen 9 / Showdown). Showdown stops the move in TryMove ("X cannot use Y!"); the engine's move-execution
// check (event 0x1F) carries no target, so here each target the rule covers is "not affected" (EVENT_CHECK_NO_EFFECT,
// popup + "It doesn't affect X..."), which ends the same way for the moves it covers: moves aimed at Pokémon
// (ability::TargetsPokemon). Not covered: Prankster field moves (Showdown's target "all", e.g. Haze), which have
// no target to check. Mold Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u32 QM_PRIORITY_ZERO = 7;   // ServerEvent_GetMovePriority returns priority + 7

void HandlerQueenlyMajestyNoEffect(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    u32 defender = ability::Defender(), attacker = ability::Attacker();
    if (!IsAllyMonID(pokeID, defender) || IsAllyMonID(pokeID, attacker)) return;   // holder's side, foe's move
    u16 move = ability::Move();
    if (!ability::TargetsPokemon(move)) return;
    u32 priority = ServerEvent_GetMovePriority(sf, move, GetBattleMon(sf, attacker));
    if (priority <= QM_PRIORITY_ZERO) return;
    if (!BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) return;
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, ability::MSG_SET_DOESNT_AFFECT);
    BattleHandler_AddArg(&m->str, defender);
    BattleHandler_PopWork(sf, m);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    MLOG("[ABIL] Queenly Majesty: poke %d blocks move %d (priority %d) from poke %d at poke %d", pokeID, move,
         (int)priority - (int)QM_PRIORITY_ZERO, attacker, defender);
}

constexpr BattleEventHandlerTableEntry QUEENLY_MAJESTY_HANDLERS[] = {
    { EVENT_CHECK_NO_EFFECT, HandlerQueenlyMajestyNoEffect },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddQueenlyMajesty(u32* packed) {
    *packed = sizeof(QUEENLY_MAJESTY_HANDLERS) / sizeof(QUEENLY_MAJESTY_HANDLERS[0]);
    return QUEENLY_MAJESTY_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_QueenlyMajestyHandlers[1] = {QUEENLY_MAJESTY_HANDLERS[0]};
static_assert(sizeof(QUEENLY_MAJESTY_HANDLERS) / sizeof(QUEENLY_MAJESTY_HANDLERS[0]) == 1, "MB_QueenlyMajestyHandlers");
