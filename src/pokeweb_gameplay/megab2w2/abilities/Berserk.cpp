// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Berserk.cpp); see docs/megab2w2-integration.md.
// Berserk family (`logic: Berserk`; data/abilities.yml BERSERK, ANGER_SHELL): when a move's hits take the holder from
// above half its max HP to half or less, its row's stat changes apply (Gen 9 / Showdown: checked once after the whole
// move, so a multi-hit move counts its total; not for its own moves; not after a move whose secondary effects the
// attacker's Sheer Force removed - nothing to do here: vanilla Sheer Force's event 0x82 handler sets var 0x48, and
// the engine then skips EVENT_AFTER_MOVE_HITS for that move; scenario BERSERK_SHEER_FORCE). Berserk: Sp. Atk +1. Anger Shell: Attack, Sp. Atk, Speed +1, Defense, Sp. Def -1 (one popup). The HP before
// the move is taken at EVENT_MOVE_START of every other Pokémon's move (fixed-damage moves skip the damage-calc
// events) and compared at EVENT_AFTER_MOVE_HITS when the holder is among the targets. A substitute takes the hits:
// HP unchanged, nothing happens.
#include "../ability_api.h"
#include "../megalog.h"

// Names in the anonymous namespace carry the ability's name: rpmtool resolves symbols by name across the DLL's
// files, anonymous or not (two files' HandlerMovePower crossed Tough Claws and Mega Launcher, batch 8).
namespace {
constexpr u32 BERSERK_HP_A = 0xD, BERSERK_HP_B = 0xE;   // GetBattleMonStat: current / max HP (order not relied on)
struct BerserkRow { u16 ability; u8 count; u8 stats[5]; s8 stages[5]; ROW_NAME_FIELD };
const BerserkRow BERSERK_ROWS[] = {
    { ABIL_BERSERK, 1, { ability::STAT_SPATK }, { 1 } ROW_NAME("Berserk") },
    { ABIL_ANGER_SHELL, 5, { ability::STAT_ATK, ability::STAT_SPATK, ability::STAT_SPEED, ability::STAT_DEF,
                             ability::STAT_SPDEF }, { 1, 1, 1, -1, -1 } ROW_NAME("Anger Shell") },
};
bool g_berserkArmed[ability::MAX_POKE_ID];
u16 g_berserkHPBefore[ability::MAX_POKE_ID];

void BerserkHP(BattleMon* bm, u32* cur, u32* max) {
    u32 a = GetBattleMonStat(bm, BERSERK_HP_A), b = GetBattleMonStat(bm, BERSERK_HP_B);
    *cur = a < b ? a : b; *max = a < b ? b : a;
}
void HandlerBerserkMoveStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (pokeID >= ability::MAX_POKE_ID) return;
    g_berserkArmed[pokeID] = ability::Attacker() != pokeID;
    if (!g_berserkArmed[pokeID]) return;
    u32 cur, max;
    BerserkHP(GetBattleMon(sf, pokeID), &cur, &max);
    g_berserkHPBefore[pokeID] = (u16)cur;
}
void HandlerBerserkAfterHits(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (pokeID >= ability::MAX_POKE_ID || !g_berserkArmed[pokeID]) return;
    g_berserkArmed[pokeID] = false;
    if (ability::Attacker() == pokeID || !HandlerTargetsContain(pokeID)) return;
    u32 cur, max;
    BerserkHP(GetBattleMon(sf, pokeID), &cur, &max);
    u32 before = g_berserkHPBefore[pokeID];
    if (cur == 0 || cur * 2 > max || before * 2 <= max) return;
    u16 ability = ability::HolderAbility(sf, pokeID);
    for (const BerserkRow& r : BERSERK_ROWS) {
        if (r.ability != ability) continue;
        MLOG("[ABIL] %s: poke %d HP %d -> %d of %d", r.name, pokeID, before, cur, max);
        BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
        for (u32 i = 0; i < r.count; ++i) ability::ChangeStatStage(sf, pokeID, pokeID, r.stats[i], r.stages[i], false);
        BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    }
}

constexpr BattleEventHandlerTableEntry BERSERK_HANDLERS[] = {
    { EVENT_MOVE_START, HandlerBerserkMoveStart },
    { EVENT_AFTER_MOVE_HITS, HandlerBerserkAfterHits },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddBerserk(u32* packed) {
    *packed = sizeof(BERSERK_HANDLERS) / sizeof(BERSERK_HANDLERS[0]);
    return BERSERK_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_BerserkHandlers[2] = {BERSERK_HANDLERS[0], BERSERK_HANDLERS[1]};
static_assert(sizeof(BERSERK_HANDLERS) / sizeof(BERSERK_HANDLERS[0]) == 2, "MB_BerserkHandlers");
