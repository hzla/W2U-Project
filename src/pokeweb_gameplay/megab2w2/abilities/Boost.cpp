// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Boost.cpp); see docs/megab2w2-integration.md.
// Table-driven boosts: abilities whose whole rule is "the holder's moves that match X get x ratio" share one
// handler per event and a row each here (`logic: Boost` in data/abilities.yml), instead of a file each (DLL memory,
// docs/PLAN.md 7.2.0). The holder's row is found by its current ability value. Mold Breaker does not matter (the
// holder is the attacker). A new member: one row (+ its scenario); docs/ABILITIES.md "Bundles" lists candidates.
//   Tough Claws (Mega Charizard X): contact (the move record's flag), power x1.3 (Gen 6+)
//   Strong Jaw / Mega Launcher / Sharpness: move_flags bite / pulse / slicing (data/moves.yml), power x1.5
//   Steelworker / Dragon's Maw / Rocky Payload / Fire Mane (Legends Z-A): Steel / Dragon / Rock / Fire moves, attacking
//   stat x1.5 (Showdown onModifyAtk / SpA); Transistor: Electric x1.3 (Gen 9; Gen 8 x1.5)
#include "../ability_api.h"
#include "../megalog.h"

namespace {
enum : u8 { BOOST_POWER, BOOST_ATTACKING_STAT };               // the event: VAR_MOVE_POWER_RATIO / VAR_RATIO
enum : u8 { MATCH_ENGINE_FLAG, MATCH_MOVE_FLAG, MATCH_TYPE };  // getMoveFlag / moves::HasFlag / final move type
struct BoostRow {
    u16 ability; u8 event, match, param; u16 ratio;
#ifdef MEGA_DEBUG
    const char* name; const char* text;
#endif
};
#ifdef MEGA_DEBUG
#define BOOST_NAME(n, t) , n, t
#else
#define BOOST_NAME(n, t)
#endif
const BoostRow BOOST_ROWS[] = {
    { ABIL_TOUGH_CLAWS, BOOST_POWER, MATCH_ENGINE_FLAG, MOVE_FLAG_CONTACT, 5325 BOOST_NAME("Tough Claws", "x1.3") },
    { ABIL_STRONG_JAW, BOOST_POWER, MATCH_MOVE_FLAG, MOVE_FLAG_BITE, 6144 BOOST_NAME("Strong Jaw", "x1.5") },
    { ABIL_MEGA_LAUNCHER, BOOST_POWER, MATCH_MOVE_FLAG, MOVE_FLAG_PULSE, 6144 BOOST_NAME("Mega Launcher", "x1.5") },
    { ABIL_SHARPNESS, BOOST_POWER, MATCH_MOVE_FLAG, MOVE_FLAG_SLICING, 6144 BOOST_NAME("Sharpness", "x1.5") },
    { ABIL_STEELWORKER, BOOST_ATTACKING_STAT, MATCH_TYPE, TYPE_STEEL, 6144 BOOST_NAME("Steelworker", "x1.5") },
    { ABIL_TRANSISTOR, BOOST_ATTACKING_STAT, MATCH_TYPE, TYPE_ELECTRIC, 5325 BOOST_NAME("Transistor", "x1.3") },
    { ABIL_DRAGONS_MAW, BOOST_ATTACKING_STAT, MATCH_TYPE, TYPE_DRAGON, 6144 BOOST_NAME("Dragon's Maw", "x1.5") },
    { ABIL_ROCKY_PAYLOAD, BOOST_ATTACKING_STAT, MATCH_TYPE, TYPE_ROCK, 6144 BOOST_NAME("Rocky Payload", "x1.5") },
    { ABIL_FIRE_MANE, BOOST_ATTACKING_STAT, MATCH_TYPE, TYPE_FIRE, 6144 BOOST_NAME("Fire Mane", "x1.5") },
};

const BoostRow* BoostRowFor(ServerFlow* sf, u32 pokeID, u8 event) {
    u16 ability = (u16)BattleMon_GetValue(GetBattleMon(sf, pokeID), BMV_ABILITY);
    for (const BoostRow& r : BOOST_ROWS)
        if (r.ability == ability && r.event == event) return &r;
    return nullptr;
}
bool BoostMatches(ServerFlow* sf, const BoostRow& r, u16 move) {
    switch (r.match) {
        case MATCH_ENGINE_FLAG: return r.param == MOVE_FLAG_CONTACT ? ability::MakesContact(sf, move) : getMoveFlag(move, r.param);
        case MATCH_MOVE_FLAG: return moves::HasFlag(move, (MoveFlagExt)r.param);
        default: return ability::MoveType() == r.param;
    }
}
void BoostApply(ServerFlow* sf, u32 pokeID, u8 event, u32 var) {
    if (ability::Attacker() != pokeID) return;
    const BoostRow* r = BoostRowFor(sf, pokeID, event);
    u16 move = ability::Move();
    if (!r || !BoostMatches(sf, *r, move)) return;
    BattleEventVar_MulValue(var, r->ratio);
#ifdef MEGA_DEBUG
    if (!ability::Simulating(sf)) MLOG("[ABIL] %s: poke %d move %d %s", r->name, pokeID, move, r->text);
#endif
}
void HandlerBoostMovePower(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    BoostApply(sf, pokeID, BOOST_POWER, VAR_MOVE_POWER_RATIO);
}
void HandlerBoostAttackingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    BoostApply(sf, pokeID, BOOST_ATTACKING_STAT, VAR_RATIO);
}

constexpr BattleEventHandlerTableEntry BOOST_HANDLERS[] = {
    { EVENT_MOVE_POWER, HandlerBoostMovePower },
    { EVENT_ATTACKING_STAT, HandlerBoostAttackingStat },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddBoost(u32* packed) {
    *packed = sizeof(BOOST_HANDLERS) / sizeof(BOOST_HANDLERS[0]);
    return BOOST_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_BoostHandlers[2] = {BOOST_HANDLERS[0], BOOST_HANDLERS[1]};
static_assert(sizeof(BOOST_HANDLERS) / sizeof(BOOST_HANDLERS[0]) == 2, "MB_BoostHandlers");
