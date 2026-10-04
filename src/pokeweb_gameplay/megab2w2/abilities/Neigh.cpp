// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Neigh.cpp); see docs/megab2w2-integration.md.
// Neigh family (`logic: Neigh`; data/abilities.yml GRIM_NEIGH, AS_ONE_GLASTRIER, AS_ONE_SPECTRIER): KOing Pokémon
// with a move raises a stat by 1 per KO, as Moxie (vanilla HandlerMoxie 0x21C20FC: one EFFECT_CHANGE_STAT_STAGE per
// fainted target, with the popup). Grim Neigh: Sp. Atk. As One (Glastrier): Attack = Unnerve + Chilling Neigh;
// As One (Spectrier): Sp. Atk = Unnerve + Grim Neigh. As One also runs Unnerve's vanilla handlers (entry message,
// Berry blocking) and announces "X has two Abilities!" first. (Chilling Neigh itself = Moxie's handlers.)
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

extern "C" {
void HandlerUnnerveMemberIn(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);     // 0x21C24C4 (0x55)
void HandlerUnnerveRotationIn(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);   // 0x21C24E8 (0x56, 0x58)
}

namespace {
struct NeighRow { u16 ability; u8 stat; bool unnerve; ROW_NAME_FIELD };
const NeighRow NEIGH_ROWS[] = {
    { ABIL_GRIM_NEIGH, ability::STAT_SPATK, false ROW_NAME("Grim Neigh") },
    { ABIL_AS_ONE_GLASTRIER, ability::STAT_ATK, true ROW_NAME("As One (Glastrier)") },
    { ABIL_AS_ONE_SPECTRIER, ability::STAT_SPATK, true ROW_NAME("As One (Spectrier)") },
};
const NeighRow* NeighRowOf(ServerFlow* sf, u32 pokeID) {
    u16 ability = ability::HolderAbility(sf, pokeID);
    for (const NeighRow& r : NEIGH_ROWS)
        if (r.ability == ability) return &r;
    return nullptr;
}

void HandlerNeighKO(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    const NeighRow* r = NeighRowOf(sf, pokeID);
    if (!r) return;
    u32 count = (u32)BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 i = 0; i < count; ++i) {
        u32 target = (u32)BattleEventVar_GetValue(VAR_TARGET0 + i);
        if (!BattleMon_IsFainted(GetBattleMon(sf, target))) continue;
        ability::ChangeStatStage(sf, pokeID, pokeID, r->stat, 1, true);
        MLOG("[ABIL] %s: poke %d KO'd poke %d, stat %d +1", r->name, pokeID, target, r->stat);
    }
}
// Unnerve's handlers announce once (work[0] = 1 after its message); 0x58 can come before the holder's entry event
// at battle start, so "two Abilities" goes with whichever announces first.
void NeighAsOne(ServerFlow* sf, u32 pokeID, u32* work) {
    if (!work[0]) ability::PopupSetMessage(sf, pokeID, BTLMSG_SET_AS_ONE);
}
void HandlerNeighMemberIn(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work) {
    const NeighRow* r = NeighRowOf(sf, pokeID);
    if (!r || !r->unnerve || ability::Subject() != pokeID) return;
    NeighAsOne(sf, pokeID, work);
    HandlerUnnerveMemberIn(item, sf, pokeID, work);
}
void HandlerNeighUnnerve(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work) {
    const NeighRow* r = NeighRowOf(sf, pokeID);
    if (!r || !r->unnerve) return;
    NeighAsOne(sf, pokeID, work);
    HandlerUnnerveRotationIn(item, sf, pokeID, work);
}

constexpr BattleEventHandlerTableEntry NEIGH_HANDLERS[] = {
    { EVENT_AFTER_KO, HandlerNeighKO },
    { EVENT_SWITCH_IN, HandlerNeighMemberIn },
    { 0x56, HandlerNeighUnnerve },
    { 0x58, HandlerNeighUnnerve },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddNeigh(u32* packed) {
    *packed = sizeof(NEIGH_HANDLERS) / sizeof(NEIGH_HANDLERS[0]);
    return NEIGH_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_NeighHandlers[4] = {NEIGH_HANDLERS[0], NEIGH_HANDLERS[1], NEIGH_HANDLERS[2], NEIGH_HANDLERS[3]};
static_assert(sizeof(NEIGH_HANDLERS) / sizeof(NEIGH_HANDLERS[0]) == 4, "MB_NeighHandlers");
