// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/ScreenCleaner.cpp); see docs/megab2w2-integration.md.
// Screen Cleaner (Gen 8; data/abilities.yml SCREEN_CLEANER): on entering (or gaining the ability) it removes Reflect
// and Light Screen from both sides (Gen 9 / Showdown; Aurora Veil does not exist here). The popup only shows when
// there is something to remove. Removal = Brick Break's handler effect (EFFECT_REMOVE_SIDE_EFFECT); the engine shows
// the "wore off" messages.
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u32 SC_SIDES = 2;

bool ScreenCleanerHasScreens(u32 side) {
    return SideEffect_IsActive(side, SIDE_EFFECT_REFLECT) || SideEffect_IsActive(side, SIDE_EFFECT_LIGHT_SCREEN);
}
void HandlerScreenCleanerStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    bool sides[SC_SIDES];
    bool any = false;
    for (u32 side = 0; side < SC_SIDES; ++side) any |= (sides[side] = ScreenCleanerHasScreens(side));
    if (!any) return;
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    for (u32 side = 0; side < SC_SIDES; ++side) {
        if (!sides[side]) continue;
        auto* p = (HandlerParam_RemoveSideEffect*)BattleHandler_PushWork(sf, EFFECT_REMOVE_SIDE_EFFECT, pokeID);
        p->flags[0] = 3;
        p->flags[1] = (1 << SIDE_EFFECT_REFLECT) | (1 << SIDE_EFFECT_LIGHT_SCREEN);
        p->flags[2] = 0;
        p->side = (u8)side;
        BattleHandler_PopWork(sf, p);
        MLOG("[ABIL] Screen Cleaner: poke %d clears side %d", pokeID, side);
    }
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}

constexpr BattleEventHandlerTableEntry SCREEN_CLEANER_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerScreenCleanerStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerScreenCleanerStart },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddScreenCleaner(u32* packed) {
    *packed = sizeof(SCREEN_CLEANER_HANDLERS) / sizeof(SCREEN_CLEANER_HANDLERS[0]);
    return SCREEN_CLEANER_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_ScreenCleanerHandlers[2] = {SCREEN_CLEANER_HANDLERS[0], SCREEN_CLEANER_HANDLERS[1]};
static_assert(sizeof(SCREEN_CLEANER_HANDLERS) / sizeof(SCREEN_CLEANER_HANDLERS[0]) == 2, "MB_ScreenCleanerHandlers");
