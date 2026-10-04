// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/MirrorArmor.cpp); see docs/megab2w2-integration.md.
// Mirror Armor (Gen 8; data/abilities.yml MIRROR_ARMOR): a stat drop from another Pokémon (moves, Intimidate,
// secondary effects) is blocked and the same drop hits that Pokémon instead (Gen 9 / Showdown). Clear Body's check
// (EVENT_STAT_CHANGE_CHECK: VAR_MON_ID the target, VAR_ATTACKING_MON the source, VAR_STAT, VAR_STAT_CHANGE < 0 ->
// VAR_FAIL_FLAG) remembers the drop; the guard event (0x5C) pushes the popup and the reflected drop. A reflected drop
// is not reflected again (Showdown: the effect is Mirror Armor itself): the source is marked until the next move /
// switch-in. Mold Breaker ignores it (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u32 MA_NO_SOURCE = 0x1F;
bool g_mirrorReflected[ability::MAX_POKE_ID];   // the Pokémon is receiving a reflected drop

void HandlerMirrorArmorClear(BattleEventItem*, ServerFlow*, u32, u32*) {
    for (bool& r : g_mirrorReflected) r = false;
}
void HandlerMirrorArmorCheck(BattleEventItem*, ServerFlow*, u32 pokeID, u32* work) {
    if (ability::Subject() != pokeID || pokeID >= ability::MAX_POKE_ID || g_mirrorReflected[pokeID]) return;
    u32 source = ability::Attacker();
    int stages = (int)BattleEventVar_GetValue(VAR_STAT_CHANGE);
    if (source == pokeID || source == MA_NO_SOURCE || stages >= 0) return;
    work[0] = BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1);
    work[1] = (u32)BattleEventVar_GetValue(VAR_STAT);
    work[2] = (u32)stages;
    work[3] = source;
}
void HandlerMirrorArmorGuard(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    if (ability::Subject() != pokeID || !work[0]) return;
    work[0] = 0;
    u32 source = work[3];
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    if (ability::OnField(sf, source) && !BattleMon_IsFainted(GetBattleMon(sf, source))) {
        g_mirrorReflected[source] = true;
        ability::ChangeStatStage(sf, pokeID, source, work[1], (int)work[2], false);
        MLOG("[ABIL] Mirror Armor: poke %d reflects stat %d %d to poke %d", pokeID, work[1], (int)work[2], source);
    }
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}

constexpr BattleEventHandlerTableEntry MIRROR_ARMOR_HANDLERS[] = {
    { EVENT_STAT_CHANGE_CHECK, HandlerMirrorArmorCheck },
    { EVENT_STAT_CHANGE_GUARD, HandlerMirrorArmorGuard },
    { EVENT_MOVE_START, HandlerMirrorArmorClear },
    { EVENT_SWITCH_IN, HandlerMirrorArmorClear },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddMirrorArmor(u32* packed) {
    *packed = sizeof(MIRROR_ARMOR_HANDLERS) / sizeof(MIRROR_ARMOR_HANDLERS[0]);
    return MIRROR_ARMOR_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_MirrorArmorHandlers[4] = {MIRROR_ARMOR_HANDLERS[0], MIRROR_ARMOR_HANDLERS[1], MIRROR_ARMOR_HANDLERS[2], MIRROR_ARMOR_HANDLERS[3]};
static_assert(sizeof(MIRROR_ARMOR_HANDLERS) / sizeof(MIRROR_ARMOR_HANDLERS[0]) == 4, "MB_MirrorArmorHandlers");
