// W2U fix (2026-10-05, found by the Misty Explosion port); see docs/megab2w2-integration.md.
// Damp: no Pokemon can use a self-destructing move while the holder is on the field (Showdown: Explosion,
// Self-Destruct, Mind Blown, Misty Explosion). Vanilla Damp's move check (ov167 0x21C066C, event 0x1F) compares the
// move ID with Explosion / Self-Destruct only, so the newer moves went off. This table is vanilla Damp's with that
// check replaced: on a listed move it sets the fail cause 0x13 (VAR 0x22, if no cause yet) and keeps the cause and the
// move in work[0] / work[1] for vanilla's message handler (event 0x21: popup, "X cannot use Y!"); vanilla's other
// three handlers (0x03 / 0x04 / 0x6A) are reused as they are.
#include "../ability_api.h"

extern "C" {
void HandlerDampMessage(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);     // ov167 0x21C06A0
void HandlerDampMoveStart(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);   // ov167 0x21C06FC
void HandlerDampMoveEnd(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);     // ov167 0x21C070C
void HandlerDampNullified(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);   // ov167 0x21C0714
}

namespace {
constexpr u32 DAMP_EVENT_MOVE_CHECK = 0x1F, DAMP_EVENT_FAIL_MESSAGE = 0x21;
constexpr u32 DAMP_VAR_FAIL_CAUSE = 0x22, DAMP_FAIL_CAUSE = 0x13;
constexpr u16 DAMP_MOVES[] = { 120 /* Self-Destruct */, 153 /* Explosion */, 720 /* Mind Blown */,
                               802 /* Misty Explosion */ };

void HandlerDampMoveCheck(BattleEventItem*, ServerFlow*, u32, u32* work) {
    u16 move = ability::Move();
    work[0] = 0;
    bool listed = false;
    for (u16 m : DAMP_MOVES) listed |= m == move;
    if (!listed || BattleEventVar_GetValue(DAMP_VAR_FAIL_CAUSE) != 0) return;
    work[0] = BattleEventVar_RewriteValue(DAMP_VAR_FAIL_CAUSE, DAMP_FAIL_CAUSE);
    work[1] = move;
}

const BattleEventHandlerTableEntry DAMP_HANDLERS[] = {
    { DAMP_EVENT_MOVE_CHECK, HandlerDampMoveCheck },
    { DAMP_EVENT_FAIL_MESSAGE, HandlerDampMessage },
    { EVENT_MOVE_START, HandlerDampMoveStart },
    { EVENT_MOVE_END, HandlerDampMoveEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerDampNullified },
};
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_DampHandlers[5] = {DAMP_HANDLERS[0], DAMP_HANDLERS[1], DAMP_HANDLERS[2],
                                                   DAMP_HANDLERS[3], DAMP_HANDLERS[4]};
static_assert(sizeof(DAMP_HANDLERS) / sizeof(DAMP_HANDLERS[0]) == 5, "MB_DampHandlers");
