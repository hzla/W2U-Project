// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/GorillaTactics.cpp); see docs/megab2w2-integration.md.
// Gorilla Tactics (Gen 8; Gen 9 / Showdown): Attack x1.5, and locked into the first move it uses - Choice Band as an
// ability. The Choice items' handlers (ov167 table 0x21D89B0): EVENT_ATTACKING_STAT x1.5 for physical moves;
// EVENT_AFTER_MOVE_USE adds condition 0x1B (the Choice lock) with MakeConditionParamPermanent(move) (not for
// Struggle); switching out clears it. Losing the ability (Skill Swap, Gastro Acid...) cures the lock, as the items do
// when the item changes - unless a Choice item still holds it.
// W2U: the move menu enforces the lock in W2U's IsUnselectableMove (w2u_moves.cpp), which words it with Encore's
// "{Pokemon} can use only Y!" for a Gorilla Tactics holder (MegaB2W2 wrapped that function's five callers).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u32 GT_CONDITION_CHOICE_LOCK = 0x1B;
constexpr u16 GT_MOVE_STRUGGLE = 165;
constexpr u16 GT_CHOICE_BAND = 220, GT_CHOICE_SCARF = 287, GT_CHOICE_SPECS = 297;

void HandlerGorillaTacticsAttackingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || ability::MoveCategory(ability::Move()) != ability::CATEGORY_PHYSICAL) return;
    ability::MulRatio(6144);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Gorilla Tactics: poke %d Attack x1.5", pokeID);
}
void HandlerGorillaTacticsLock(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    u16 move = ability::Move();
    if (move == GT_MOVE_STRUGGLE) return;
    auto* p = (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
    p->condition = GT_CONDITION_CHOICE_LOCK;
    p->cont = MakeConditionParamPermanent(move);
    p->pokeID = (u8)pokeID;
    p->mode = 2;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Gorilla Tactics: poke %d locked into move %d", pokeID, move);
}
void HandlerGorillaTacticsEnd(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    u16 item = BattleMon_GetHeldItem(GetBattleMon(sf, pokeID));
    if (item == GT_CHOICE_BAND || item == GT_CHOICE_SCARF || item == GT_CHOICE_SPECS) return;
    auto* p = (HandlerParam_CureCondition*)BattleHandler_PushWork(sf, EFFECT_CURE_CONDITION, pokeID);
    p->condition = GT_CONDITION_CHOICE_LOCK;
    p->pokeID = (u8)pokeID;
    p->_14 = 1;
    p->_15 = 1;
    BattleHandler_PopWork(sf, p);
}

const BattleEventHandlerTableEntry GORILLA_TACTICS_HANDLERS[] = {
    { EVENT_ATTACKING_STAT, HandlerGorillaTacticsAttackingStat },
    { EVENT_AFTER_MOVE_USE, HandlerGorillaTacticsLock },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerGorillaTacticsEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerGorillaTacticsEnd },
};
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_GorillaTacticsHandlers[4] = {
    GORILLA_TACTICS_HANDLERS[0], GORILLA_TACTICS_HANDLERS[1], GORILLA_TACTICS_HANDLERS[2], GORILLA_TACTICS_HANDLERS[3]};
static_assert(sizeof(GORILLA_TACTICS_HANDLERS) / sizeof(GORILLA_TACTICS_HANDLERS[0]) == 4, "MB_GorillaTacticsHandlers");
