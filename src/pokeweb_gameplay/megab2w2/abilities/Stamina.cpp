// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Stamina.cpp); see docs/megab2w2-integration.md.
// Stamina family (`logic: Stamina`; data/abilities.yml STAMINA, WATER_COMPACTION, STEAM_ENGINE; THERMAL_EXCHANGE =
// `logic: ThermalExchange`, the same + no burns): a damaging hit from another Pokémon raises the holder's stat
// (Gen 9 / Showdown onDamagingHit: not through a substitute, not once fainted). Rows: Stamina any hit Defense +1;
// Water Compaction Water hits Defense +2; Steam Engine Fire or Water hits Speed +6; Thermal Exchange Fire hits
// Attack +1 (+ Water Veil's vanilla handlers for the burn immunity and cure). The type is the move's final type.
#include "../ability_api.h"
#include "../megalog.h"

namespace {
constexpr u32 ST_ANY = 0;   // types: bit mask (1 << type), 0 = any damaging hit
struct StaminaRow { u16 ability; u32 types; u8 stat; s8 stages; ROW_NAME_FIELD };
const StaminaRow STAMINA_ROWS[] = {
    { ABIL_STAMINA, ST_ANY, ability::STAT_DEF, 1 ROW_NAME("Stamina") },
    { ABIL_WATER_COMPACTION, 1u << TYPE_WATER, ability::STAT_DEF, 2 ROW_NAME("Water Compaction") },
    { ABIL_STEAM_ENGINE, (1u << TYPE_FIRE) | (1u << TYPE_WATER), ability::STAT_SPEED, 6 ROW_NAME("Steam Engine") },
    { ABIL_THERMAL_EXCHANGE, 1u << TYPE_FIRE, ability::STAT_ATK, 1 ROW_NAME("Thermal Exchange") },
};

void HandlerStaminaAfterDamageReaction(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    u32 attacker = ability::Attacker();
    if (ability::Defender() != pokeID || attacker == pokeID) return;
    if (BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) != 0 || BattleMon_IsFainted(GetBattleMon(sf, pokeID))) return;
    u16 ability = ability::HolderAbility(sf, pokeID), move = ability::Move();
    for (const StaminaRow& r : STAMINA_ROWS) {
        if (r.ability != ability) continue;
        if (r.types && !(r.types & (1u << ability::FinalMoveType(sf, move, attacker)))) return;
        ability::ChangeStatStage(sf, pokeID, pokeID, r.stat, r.stages, true);
        MLOG("[ABIL] %s: poke %d stat %d %+d (move %d)", r.name, pokeID, r.stat, r.stages, move);
        return;
    }
}

constexpr BattleEventHandlerTableEntry STAMINA_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerStaminaAfterDamageReaction },
};
constexpr BattleEventHandlerTableEntry THERMAL_EXCHANGE_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerStaminaAfterDamageReaction },
    { EVENT_ADD_CONDITION_CHECK, HandlerWaterVeil },              // burns blocked (Water Veil's handlers)
    { EVENT_ADD_CONDITION_FAILED, HandlerAddStatusFailedCommon },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerWaterVeilCureStatus },
    { EVENT_SWITCH_IN, HandlerWaterVeilCureStatus },
    { EVENT_ACTION_END, HandlerWaterVeilActionEnd },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddStamina(u32* packed) {
    *packed = sizeof(STAMINA_HANDLERS) / sizeof(STAMINA_HANDLERS[0]);
    return STAMINA_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddThermalExchange(u32* packed) {
    *packed = sizeof(THERMAL_EXCHANGE_HANDLERS) / sizeof(THERMAL_EXCHANGE_HANDLERS[0]);
    return THERMAL_EXCHANGE_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_StaminaHandlers[1] = {STAMINA_HANDLERS[0]};
static_assert(sizeof(STAMINA_HANDLERS) / sizeof(STAMINA_HANDLERS[0]) == 1, "MB_StaminaHandlers");
BattleEventHandlerTableEntry MB_ThermalExchangeHandlers[6] = {THERMAL_EXCHANGE_HANDLERS[0], THERMAL_EXCHANGE_HANDLERS[1], THERMAL_EXCHANGE_HANDLERS[2], THERMAL_EXCHANGE_HANDLERS[3], THERMAL_EXCHANGE_HANDLERS[4], THERMAL_EXCHANGE_HANDLERS[5]};
static_assert(sizeof(THERMAL_EXCHANGE_HANDLERS) / sizeof(THERMAL_EXCHANGE_HANDLERS[0]) == 6, "MB_ThermalExchangeHandlers");
