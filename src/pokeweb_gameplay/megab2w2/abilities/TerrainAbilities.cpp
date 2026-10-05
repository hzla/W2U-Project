// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/TerrainAbilities.cpp); see docs/megab2w2-integration.md.
// Terrain abilities (Gen 7-9), one file with several logic names (Gen 9 / Showdown). W2U port: Orichalcum Pulse /
// Hadron Engine, Mimicry and Grass Pelt (W2U has its own Surges and Surge Surfer; Grass Pelt was only in its Mold
// Breaker list, with no effect - phase 6, 2026-10-05); terrain = W2U's (../terrain.h).
//   `logic: Surge`        Electric / Psychic / Misty / Grassy Surge: on entry (or gaining the ability) the terrain
//                         starts, under the popup; nothing if it is already up.
//   `logic: TerrainStat`  Grass Pelt: Defense x1.5 on Grassy Terrain (breakable). Surge Surfer: Speed x2 on Electric
//                         Terrain. (Not tied to being grounded, as in Gen 9.)
//   `logic: Pulse`        Orichalcum Pulse: on entry harsh sunlight starts (Drought's weather effect: 5 turns / Heat
//                         Rock), then "X turned the sunlight harsh, ..." ("basked in the sunlight" if it was up);
//                         Attack x1.333 in sun. Hadron Engine: the same with Electric Terrain and Sp. Atk.
//   `logic: Mimicry`      Mimicry: its type becomes the terrain's (Electric / Grass / Fairy / Psychic); back to its
//                         own types when there is none (Conversion's EFFECT_CHANGE_TYPE: "X transformed into the Y
//                         type!"). Checked on entry, after every action and at the turn end.
#include "../ability_api.h"
#include "../megalog.h"
#include "../terrain.h"

namespace {
constexpr u32 TA_SUN = 1;
constexpr u32 TA_EFFECT_CHANGE_WEATHER = 0x1D;
struct HandlerParam_ChangeWeatherTA { HandlerParam_Header header; u8 weather; u8 turns; u8 _6[2]; };

// ---- Orichalcum Pulse / Hadron Engine ------------------------------------------------------------------------
void PulseMessage(ServerFlow* sf, u32 pokeID, u16 msg) {
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, msg);
    BattleHandler_AddArg(&m->str, pokeID);
    BattleHandler_PopWork(sf, m);
}
void HandlerPulseStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    if (ability::HolderAbility(sf, pokeID) == ABIL_HADRON_ENGINE) {
        // W2U: starting the terrain shows its own popup, animation and the message naming the holder at once
        // (terrain::SetNamed), so the queued popup is only used when Electric Terrain is already up.
        if (terrain::Current() != terrain::ELECTRIC &&
            terrain::SetNamed(sf, pokeID, terrain::ELECTRIC, BTLMSG_SET_HADRON_START)) {
            MLOG("[ABIL] Hadron Engine: poke %d sets Electric Terrain", pokeID);
            return;
        }
        BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
        PulseMessage(sf, pokeID, BTLMSG_SET_HADRON_USE);
        BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
        MLOG("[ABIL] Hadron Engine: poke %d (already up)", pokeID);
        return;
    }
    {
        BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
        bool up = GetWeather(sf) == TA_SUN;
        if (!up) {
            auto* p = (HandlerParam_ChangeWeatherTA*)BattleHandler_PushWork(sf, TA_EFFECT_CHANGE_WEATHER, pokeID);
            p->weather = TA_SUN;
            p->turns = 0xFF;
            BattleHandler_PopWork(sf, p);
        }
        PulseMessage(sf, pokeID, up ? BTLMSG_SET_ORICHALCUM_BASK : BTLMSG_SET_ORICHALCUM_START);
        MLOG("[ABIL] Orichalcum Pulse: poke %d (%s)", pokeID, up ? "sun was up" : "sets sun");
    }
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}
void HandlerPulseAttackingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    u32 cat = ability::MoveCategory(ability::Move());
    bool hadron = ability::HolderAbility(sf, pokeID) == ABIL_HADRON_ENGINE;
    if (hadron ? (cat != ability::CATEGORY_SPECIAL || terrain::Current() != terrain::ELECTRIC)
               : (cat != ability::CATEGORY_PHYSICAL || GetWeather(sf) != TA_SUN)) return;
    ability::MulRatio(5461);
    if (!ability::Simulating(sf)) MLOG("[ABIL] %s: poke %d x1.333", hadron ? "Hadron Engine" : "Orichalcum Pulse", pokeID);
}
const BattleEventHandlerTableEntry PULSE_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerPulseStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerPulseStart },
    { EVENT_ATTACKING_STAT, HandlerPulseAttackingStat },
};

// ---- Grass Pelt -----------------------------------------------------------------------------------------------
void HandlerGrassPeltDefense(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID) return;
    if (terrain::Current() != terrain::GRASSY || BattleEventVar_GetValue(VAR_DAMAGE_CATEGORY) != 1) return;
    ability::MulRatio(6144);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Grass Pelt: poke %d Defense x1.5", pokeID);
}
const BattleEventHandlerTableEntry GRASS_PELT_HANDLERS[] = {
    { EVENT_DEFENDING_STAT, HandlerGrassPeltDefense },
};

// ---- Mimicry -------------------------------------------------------------------------------------------------
u16 g_mimicryOwn[ability::MAX_POKE_ID];   // its own type pair while changed (0 = not changed)
void MimicryCheck(ServerFlow* sf, u32 pokeID) {
    if (pokeID >= ability::MAX_POKE_ID || !ability::OnField(sf, pokeID)) return;
    BattleMon* bm = GetBattleMon(sf, pokeID);
    if (BattleMon_IsFainted(bm)) return;
    u8 t = terrain::Current();
    u16 want;
    if (t) {
        want = PokeTypePair_MakePure(terrain::TypeOf(t));
        if (!g_mimicryOwn[pokeID]) g_mimicryOwn[pokeID] = (u16)GetPokeType(bm);
    } else {
        if (!g_mimicryOwn[pokeID]) return;
        want = g_mimicryOwn[pokeID];
    }
    if ((u16)GetPokeType(bm) == want) { if (!t) g_mimicryOwn[pokeID] = 0; return; }
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* p = (HandlerParam_ChangeType*)BattleHandler_PushWork(sf, EFFECT_CHANGE_TYPE, pokeID);
    p->typePair = want;
    p->pokeID = (u8)pokeID;
    BattleHandler_PopWork(sf, p);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    if (!t) g_mimicryOwn[pokeID] = 0;
    MLOG("[ABIL] Mimicry: poke %d type pair %x (terrain %d)", pokeID, want, t);
}
void HandlerMimicryCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) { MimicryCheck(sf, pokeID); }
void HandlerMimicryLeave(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Subject() == pokeID && pokeID < ability::MAX_POKE_ID) g_mimicryOwn[pokeID] = 0;
}
const BattleEventHandlerTableEntry MIMICRY_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerMimicryCheck },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerMimicryCheck },
    { EVENT_ACTION_END, HandlerMimicryCheck },
    { EVENT_TURN_CHECK, HandlerMimicryCheck },
    { EVENT_SWITCH_OUT_END, HandlerMimicryLeave },
};
} // namespace

void Mimicry_ResetForBattle() {
    for (u16& o : g_mimicryOwn) o = 0;
}

extern "C" const BattleEventHandlerTableEntry* EventAddPulse(u32* packed) {
    *packed = sizeof(PULSE_HANDLERS) / sizeof(PULSE_HANDLERS[0]);
    return PULSE_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddMimicry(u32* packed) {
    *packed = sizeof(MIMICRY_HANDLERS) / sizeof(MIMICRY_HANDLERS[0]);
    return MIMICRY_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_PulseHandlers[3] = {PULSE_HANDLERS[0], PULSE_HANDLERS[1], PULSE_HANDLERS[2]};
static_assert(sizeof(PULSE_HANDLERS) / sizeof(PULSE_HANDLERS[0]) == 3, "MB_PulseHandlers");

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_MimicryHandlers[5] = {MIMICRY_HANDLERS[0], MIMICRY_HANDLERS[1], MIMICRY_HANDLERS[2], MIMICRY_HANDLERS[3], MIMICRY_HANDLERS[4]};
static_assert(sizeof(MIMICRY_HANDLERS) / sizeof(MIMICRY_HANDLERS[0]) == 5, "MB_MimicryHandlers");
BattleEventHandlerTableEntry MB_GrassPeltHandlers[1] = {GRASS_PELT_HANDLERS[0]};
static_assert(sizeof(GRASS_PELT_HANDLERS) / sizeof(GRASS_PELT_HANDLERS[0]) == 1, "MB_GrassPeltHandlers");
