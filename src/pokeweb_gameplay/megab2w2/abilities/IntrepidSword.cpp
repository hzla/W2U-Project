// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/IntrepidSword.cpp); see docs/megab2w2-integration.md.
// Intrepid Sword family (`logic: IntrepidSword`; data/abilities.yml INTREPID_SWORD, DAUNTLESS_SHIELD): on entering,
// its row's stat +1 - once per battle (Gen 9 / Showdown; Gen 8 was every entry). Intrepid Sword: Attack; Dauntless
// Shield: Defense. The "used" bits are reset at battle start (mega::ResetForBattle -> IntrepidSword_ResetForBattle).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
struct IntrepidRow { u16 ability; u8 stat; ROW_NAME_FIELD };
const IntrepidRow INTREPID_ROWS[] = {
    { ABIL_INTREPID_SWORD, ability::STAT_ATK ROW_NAME("[ABIL] Intrepid Sword: poke %d Attack +1 (once per battle)") },
    { ABIL_DAUNTLESS_SHIELD, ability::STAT_DEF ROW_NAME("[ABIL] Dauntless Shield: poke %d Defense +1 (once per battle)") },
};
u32 g_intrepidUsed = 0;

void HandlerIntrepidSwordSwitchIn(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || (g_intrepidUsed & (1u << pokeID))) return;
    u16 ability = ability::HolderAbility(sf, pokeID);
    for (const IntrepidRow& r : INTREPID_ROWS) {
        if (r.ability != ability) continue;
        g_intrepidUsed |= 1u << pokeID;
        ability::ChangeStatStage(sf, pokeID, pokeID, r.stat, 1, true);
        MLOG(r.name, pokeID);
        return;
    }
}

constexpr BattleEventHandlerTableEntry INTREPID_SWORD_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerIntrepidSwordSwitchIn },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddIntrepidSword(u32* packed) {
    *packed = sizeof(INTREPID_SWORD_HANDLERS) / sizeof(INTREPID_SWORD_HANDLERS[0]);
    return INTREPID_SWORD_HANDLERS;
}
void IntrepidSword_ResetForBattle() { g_intrepidUsed = 0; }

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_IntrepidSwordHandlers[1] = {INTREPID_SWORD_HANDLERS[0]};
static_assert(sizeof(INTREPID_SWORD_HANDLERS) / sizeof(INTREPID_SWORD_HANDLERS[0]) == 1, "MB_IntrepidSwordHandlers");
