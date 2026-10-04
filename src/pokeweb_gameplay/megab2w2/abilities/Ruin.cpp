// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Ruin.cpp); see docs/megab2w2-integration.md.
// Ruin family (`logic: Ruin`; data/abilities.yml SWORD_OF_RUIN, TABLETS_OF_RUIN, VESSEL_OF_RUIN, BEADS_OF_RUIN, Gen 9):
// every other Pokémon's stat x0.75 while the holder is on the field, in the damage calc. Sword: Defense (the
// defending stat when VAR_DAMAGE_CATEGORY says Defense is used - Psyshock too); Beads: Sp. Def (the other case);
// Tablets: Attack (physical moves' attacking stat); Vessel: Sp. Atk (special). Gen 9 / Showdown: Pokémon with the
// same Ruin ability are not affected, and two holders still give x0.75 once (only the lowest pokeID's handler
// acts). Entry: popup + "X weakened the <stat> of all surrounding Pokémon!".
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

namespace {
constexpr int RUIN_RATIO = 3072;   // x0.75
enum : u8 { RUIN_ATTACKER, RUIN_DEFENDER };
struct RuinRow { u16 ability; u8 side, category; u16 msg; ROW_NAME_FIELD };
const RuinRow RUIN_ROWS[] = {
    { ABIL_SWORD_OF_RUIN, RUIN_DEFENDER, ability::CATEGORY_PHYSICAL, BTLMSG_SET_RUIN_DEFENSE ROW_NAME("[ABIL] Sword of Ruin: poke %d: poke %d Defense x0.75") },
    { ABIL_BEADS_OF_RUIN, RUIN_DEFENDER, ability::CATEGORY_SPECIAL, BTLMSG_SET_RUIN_SP_DEF ROW_NAME("[ABIL] Beads of Ruin: poke %d: poke %d Sp. Def x0.75") },
    { ABIL_TABLETS_OF_RUIN, RUIN_ATTACKER, ability::CATEGORY_PHYSICAL, BTLMSG_SET_RUIN_ATTACK ROW_NAME("[ABIL] Tablets of Ruin: poke %d: poke %d Attack x0.75") },
    { ABIL_VESSEL_OF_RUIN, RUIN_ATTACKER, ability::CATEGORY_SPECIAL, BTLMSG_SET_RUIN_SP_ATK ROW_NAME("[ABIL] Vessel of Ruin: poke %d: poke %d Sp. Atk x0.75") },
};
const RuinRow* RuinRowFor(ServerFlow* sf, u32 pokeID) {
    u16 ability = ability::HolderAbility(sf, pokeID);
    for (const RuinRow& r : RUIN_ROWS) if (r.ability == ability) return &r;
    return nullptr;
}

void HandlerRuinStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    if (const RuinRow* r = RuinRowFor(sf, pokeID)) ability::PopupSetMessage(sf, pokeID, r->msg);
}
// The stat of `target` is lowered by this holder's row for a hit of `category`
void RuinApply(ServerFlow* sf, u32 pokeID, u8 side, u32 target, u32 category) {
    const RuinRow* r = RuinRowFor(sf, pokeID);
    if (!r || r->side != side || r->category != category || target == pokeID) return;
    if (ability::HasActiveAbility(GetBattleMon(sf, target), r->ability)) return;
    if (ability::FirstFieldHolder(sf, r->ability) != pokeID) return;
    ability::MulRatio(RUIN_RATIO);
    if (!ability::Simulating(sf)) MLOG(r->name, pokeID, target);
}
void HandlerRuinDefendingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    u32 category = BattleEventVar_GetValue(VAR_DAMAGE_CATEGORY) == 1 ? ability::CATEGORY_PHYSICAL : ability::CATEGORY_SPECIAL;
    RuinApply(sf, pokeID, RUIN_DEFENDER, ability::Defender(), category);
}
void HandlerRuinAttackingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    RuinApply(sf, pokeID, RUIN_ATTACKER, ability::Attacker(), ability::MoveCategory(ability::Move()));
}

constexpr BattleEventHandlerTableEntry RUIN_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerRuinStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerRuinStart },
    { EVENT_DEFENDING_STAT, HandlerRuinDefendingStat },
    { EVENT_ATTACKING_STAT, HandlerRuinAttackingStat },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddRuin(u32* packed) {
    *packed = sizeof(RUIN_HANDLERS) / sizeof(RUIN_HANDLERS[0]);
    return RUIN_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_RuinHandlers[4] = {RUIN_HANDLERS[0], RUIN_HANDLERS[1], RUIN_HANDLERS[2], RUIN_HANDLERS[3]};
static_assert(sizeof(RUIN_HANDLERS) / sizeof(RUIN_HANDLERS[0]) == 4, "MB_RuinHandlers");
