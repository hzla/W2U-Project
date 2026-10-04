// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/PowerSpot.cpp); see docs/megab2w2-integration.md.
// Power Spot family (`logic: PowerSpot`; data/abilities.yml POWER_SPOT, BATTERY, STEELY_SPIRIT): moves used by the
// holder's allies get a power boost (EVENT_MOVE_POWER with the attacker an ally of the holder; Gen 9 / Showdown
// onAllyBasePower). Power Spot: any move x1.3, not the holder's; Battery: special moves x1.3, not the holder's;
// Steely Spirit: Steel moves x1.5, the holder's too. Several holders each apply.
#include "../ability_api.h"
#include "../megalog.h"

namespace {
enum : u8 { PS_ANY, PS_SPECIAL, PS_TYPE };
struct PowerSpotRow { u16 ability; bool self; u8 match, type; u16 ratio; ROW_NAME_FIELD };
const PowerSpotRow POWER_SPOT_ROWS[] = {
    { ABIL_POWER_SPOT, false, PS_ANY, 0, 5325 ROW_NAME("Power Spot") },
    { ABIL_BATTERY, false, PS_SPECIAL, 0, 5325 ROW_NAME("Battery") },
    { ABIL_STEELY_SPIRIT, true, PS_TYPE, TYPE_STEEL, 6144 ROW_NAME("Steely Spirit") },
};

void HandlerPowerSpotMovePower(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    u32 attacker = ability::Attacker();
    if (!IsAllyMonID(pokeID, attacker)) return;
    u16 ability = ability::HolderAbility(sf, pokeID), move = ability::Move();
    for (const PowerSpotRow& r : POWER_SPOT_ROWS) {
        if (r.ability != ability) continue;
        if (attacker == pokeID && !r.self) return;
        if (r.match == PS_SPECIAL && ability::MoveCategory(move) != ability::CATEGORY_SPECIAL) return;
        if (r.match == PS_TYPE && ability::MoveType() != r.type) return;
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, r.ratio);
        if (!ability::Simulating(sf)) MLOG("[ABIL] %s: poke %d boosts poke %d move %d", r.name, pokeID, attacker, move);
        return;
    }
}

constexpr BattleEventHandlerTableEntry POWER_SPOT_HANDLERS[] = {
    { EVENT_MOVE_POWER, HandlerPowerSpotMovePower },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddPowerSpot(u32* packed) {
    *packed = sizeof(POWER_SPOT_HANDLERS) / sizeof(POWER_SPOT_HANDLERS[0]);
    return POWER_SPOT_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_PowerSpotHandlers[1] = {POWER_SPOT_HANDLERS[0]};
static_assert(sizeof(POWER_SPOT_HANDLERS) / sizeof(POWER_SPOT_HANDLERS[0]) == 1, "MB_PowerSpotHandlers");
