// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/SupremeOverlord.cpp); see docs/megab2w2-integration.md.
// Supreme Overlord (Gen 9; data/abilities.yml SUPREME_OVERLORD): on entering, it counts its party's fainted members
// (at most 5); its moves' power is x1.1 per member (Showdown's table: 4096, 4506, 4915, 5325, 5734, 6144) until it
// leaves. Popup + "X gained strength from the fallen!" when the count is above 0. The party: GetPartyData(pokecon
// (sf+8), client) = {BattleMon* members[6]; u8 count}; eggs (PokeParty param 0x4C) are not fallen.
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

namespace {
constexpr u32 SO_MAX_FALLEN = 5;
constexpr u32 SO_PARAM_IS_EGG = 0x4C;
constexpr int SO_POWER[SO_MAX_FALLEN + 1] = { 4096, 4506, 4915, 5325, 5734, 6144 };
u8 g_overlordFallen[ability::MAX_POKE_ID];

u32 SupremeOverlordCountFallen(ServerFlow* sf, u32 pokeID) {
    u8* party = (u8*)GetPartyData(*(void**)((u8*)sf + 8), PokeIDToClientID(pokeID));
    BattleMon** members = (BattleMon**)party;
    u32 count = party[0x18], fallen = 0;
    for (u32 i = 0; i < count && i < 6; ++i) {
        BattleMon* bm = members[i];
        if (!bm || !BattleMon_IsFainted(bm)) continue;
        if (PokeParty_GetParam(*(void**)bm, SO_PARAM_IS_EGG, nullptr)) continue;
        ++fallen;
    }
    return fallen > SO_MAX_FALLEN ? SO_MAX_FALLEN : fallen;
}
void HandlerSupremeOverlordStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    u32 fallen = SupremeOverlordCountFallen(sf, pokeID);
    g_overlordFallen[pokeID] = (u8)fallen;
    MLOG("[ABIL] Supreme Overlord: poke %d fallen %d", pokeID, fallen);
    if (fallen) ability::PopupSetMessage(sf, pokeID, BTLMSG_SET_SUPREME_OVERLORD);
}
void HandlerSupremeOverlordMovePower(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    u32 fallen = g_overlordFallen[pokeID];
    if (!fallen) return;
    BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, SO_POWER[fallen]);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Supreme Overlord: poke %d power x%d/4096", pokeID, SO_POWER[fallen]);
}

constexpr BattleEventHandlerTableEntry SUPREME_OVERLORD_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerSupremeOverlordStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerSupremeOverlordStart },
    { EVENT_MOVE_POWER, HandlerSupremeOverlordMovePower },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddSupremeOverlord(u32* packed) {
    *packed = sizeof(SUPREME_OVERLORD_HANDLERS) / sizeof(SUPREME_OVERLORD_HANDLERS[0]);
    return SUPREME_OVERLORD_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_SupremeOverlordHandlers[3] = {SUPREME_OVERLORD_HANDLERS[0], SUPREME_OVERLORD_HANDLERS[1], SUPREME_OVERLORD_HANDLERS[2]};
static_assert(sizeof(SUPREME_OVERLORD_HANDLERS) / sizeof(SUPREME_OVERLORD_HANDLERS[0]) == 3, "MB_SupremeOverlordHandlers");
