// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/SandSpit.cpp); see docs/megab2w2-integration.md.
// Sand Spit family (`logic: SandSpit`; data/abilities.yml SAND_SPIT, SEED_SOWER): being hit by a damaging move sets a
// field condition (Gen 9 / Showdown): Sand Spit = sandstorm (Sand Stream's effect, ov167 0x21BF01C: EFFECT_CHANGE_WEATHER
// {weather, turns 0xFF = the default 5 / item-extended}, popup); Seed Sower = Grassy Terrain (terrain.h). Nothing
// happens (no popup) if that condition is already up.
#include "../ability_api.h"
#include "../megalog.h"
#include "../terrain.h"

namespace {
constexpr u8 SAND_SPIT_SAND = 4;
struct HandlerParam_ChangeWeather { HandlerParam_Header header; u8 weather; u8 turns; u8 _6[2]; };

void HandlerSandSpitHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT)) return;
    if (ability::Attacker() == pokeID) return;
    if (ability::HolderAbility(sf, pokeID) == ABIL_SEED_SOWER) {
        if (terrain::Current() == terrain::GRASSY) return;
        terrain::Set(sf, pokeID, terrain::GRASSY, true);
        MLOG("[ABIL] Seed Sower: poke %d sets Grassy Terrain", pokeID);
        return;
    }
    if (GetWeather(sf) == SAND_SPIT_SAND) return;
    auto* p = (HandlerParam_ChangeWeather*)BattleHandler_PushWork(sf, 0x1D, pokeID);   // EFFECT_CHANGE_WEATHER
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->weather = SAND_SPIT_SAND;
    p->turns = 0xFF;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Sand Spit: poke %d whips up a sandstorm", pokeID);
}

const BattleEventHandlerTableEntry SAND_SPIT_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerSandSpitHit },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddSandSpit(u32* packed) {
    *packed = sizeof(SAND_SPIT_HANDLERS) / sizeof(SAND_SPIT_HANDLERS[0]);
    return SAND_SPIT_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_SandSpitHandlers[1] = {SAND_SPIT_HANDLERS[0]};
static_assert(sizeof(SAND_SPIT_HANDLERS) / sizeof(SAND_SPIT_HANDLERS[0]) == 1, "MB_SandSpitHandlers");
