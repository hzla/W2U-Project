// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Fluffy.cpp); see docs/megab2w2-integration.md.
// Fluffy family (`logic: Fluffy`; data/abilities.yml FLUFFY, ICE_SCALES, AURA_GUARD): damage the holder takes is
// multiplied when the hit matches a row (EVENT_DAMAGE_RATIO; Gen 9 / Showdown onSourceModifyDamage). Rows multiply
// together: Fluffy = contact x0.5 and Fire x2 (both: x1); Ice Scales = special x0.5; Aura Guard (Legends Z-A) =
// contact x0.5. Mold Breaker ignores them (`breakable: true`).
#include "../ability_api.h"
#include "../megalog.h"

namespace {
enum : u8 { DT_CONTACT, DT_TYPE, DT_SPECIAL };
struct FluffyRow { u16 ability; u8 match, type; u16 ratio; ROW_NAME_FIELD };
const FluffyRow FLUFFY_ROWS[] = {
    { ABIL_FLUFFY, DT_CONTACT, 0, 2048 ROW_NAME("[ABIL] Fluffy: poke %d move %d x0.5") },
    { ABIL_FLUFFY, DT_TYPE, TYPE_FIRE, 8192 ROW_NAME("[ABIL] Fluffy: poke %d move %d x2") },
    { ABIL_ICE_SCALES, DT_SPECIAL, 0, 2048 ROW_NAME("[ABIL] Ice Scales: poke %d move %d x0.5") },
    { ABIL_AURA_GUARD, DT_CONTACT, 0, 2048 ROW_NAME("[ABIL] Aura Guard: poke %d move %d x0.5") },
};

void HandlerFluffyDamageRatio(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID) return;
    u16 ability = ability::HolderAbility(sf, pokeID), move = ability::Move();
    bool hits[sizeof(FLUFFY_ROWS) / sizeof(FLUFFY_ROWS[0])];
    u32 product = 4096, i = 0;
    for (const FluffyRow& r : FLUFFY_ROWS) {
        hits[i] = r.ability == ability &&
                  (r.match == DT_CONTACT ? ability::MakesContact(sf, move) != 0
                   : r.match == DT_TYPE ? ability::MoveType() == r.type
                   : ability::MoveCategory(move) == ability::CATEGORY_SPECIAL);
        if (hits[i]) product = product * r.ratio >> 12;
        ++i;
    }
    if (product == 4096) return;                                // no row, or rows cancelling out (Fluffy: contact Fire)
    ability::MulRatio((int)product);
    if (ability::Simulating(sf)) return;
    for (i = 0; i < sizeof(FLUFFY_ROWS) / sizeof(FLUFFY_ROWS[0]); ++i)
        if (hits[i]) MLOG(FLUFFY_ROWS[i].name, pokeID, move);
}

constexpr BattleEventHandlerTableEntry FLUFFY_HANDLERS[] = {
    { EVENT_DAMAGE_RATIO, HandlerFluffyDamageRatio },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddFluffy(u32* packed) {
    *packed = sizeof(FLUFFY_HANDLERS) / sizeof(FLUFFY_HANDLERS[0]);
    return FLUFFY_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_FluffyHandlers[1] = {FLUFFY_HANDLERS[0]};
static_assert(sizeof(FLUFFY_HANDLERS) / sizeof(FLUFFY_HANDLERS[0]) == 1, "MB_FluffyHandlers");
