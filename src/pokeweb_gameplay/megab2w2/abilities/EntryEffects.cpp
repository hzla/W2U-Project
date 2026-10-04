// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/EntryEffects.cpp); see docs/megab2w2-integration.md.
// Entry abilities (Gen 8-9; data/abilities.yml CURIOUS_MEDICINE, COSTAR, SUPERSWEET_SYRUP): one file, three logic
// names (Gen 9 / Showdown):
//   Curious Medicine: on entry, its allies' stat changes are reset (Clear Smog's EFFECT_RESET_STAT_STAGES 0x10
//     {count, pokeIDs}, "X's stat changes were removed!" per ally, under the popup; nothing if none changed).
//   Costar: on entry, it copies an ally's stat changes (Psych Up's EFFECT_SET_STAT_STAGES 0x0F {pokeID, 7 stages},
//     "X copied Y's stat changes!"); nothing without an ally on the field.
//   Supersweet Syrup: on its first entry in a battle, its foes' evasion drops by 1 ("A supersweet aroma is wafting
//     from the syrup covering X!" + the drops; Clear Body and the like apply).
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

namespace {
constexpr u32 ENTRY_EFFECT_SET_STAGES = 0x0F, ENTRY_EFFECT_RESET_STAGES = 0x10;
constexpr u16 ENTRY_MSG_STATS_REMOVED = 195;   // bank 18: "{0}'s stat changes were removed!" (Clear Smog's)
constexpr u16 ENTRY_MSG_COPIED_STATS = 1047;   // bank 18: "{0} copied {1}'s stat changes!" (Psych Up's)
struct HandlerParam_ResetStatStages { HandlerParam_Header header; u8 count; u8 pokeIDs[6]; u8 _b; };
struct HandlerParam_SetStatStages { HandlerParam_Header header; u8 pokeID; u8 stages[7]; };
bool g_syrupUsed[ability::MAX_POKE_ID];

bool EntryHasStatChanges(BattleMon* bm) {
    for (u32 v = 1; v <= 7; ++v)
        if (GetBattleMonStat(bm, v) != 6) return true;
    return false;
}

void HandlerCuriousMedicineStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    u8 ids[6]; u32 n = 0;
    ability::ForEachOnField(sf, [&](u32 id) {
        if (id != pokeID && n < 6 && ability::SameSide(pokeID, id) && EntryHasStatChanges(GetBattleMon(sf, id)))
            ids[n++] = (u8)id;
    });
    if (!n) return;
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* p = (HandlerParam_ResetStatStages*)BattleHandler_PushWork(sf, ENTRY_EFFECT_RESET_STAGES, pokeID);
    p->count = (u8)n;
    for (u32 i = 0; i < n; ++i) p->pokeIDs[i] = ids[i];
    BattleHandler_PopWork(sf, p);
    for (u32 i = 0; i < n; ++i) {
        auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
        BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, ENTRY_MSG_STATS_REMOVED);
        BattleHandler_AddArg(&m->str, ids[i]);
        BattleHandler_PopWork(sf, m);
        MLOG("[ABIL] Curious Medicine: poke %d resets poke %d", pokeID, ids[i]);
    }
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}

void HandlerCostarStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    u32 ally = 0xFF;
    ability::ForEachOnField(sf, [&](u32 id) { if (ally == 0xFF && id != pokeID && ability::SameSide(pokeID, id)) ally = id; });
    if (ally == 0xFF) return;
    BattleMon* src = GetBattleMon(sf, ally);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* p = (HandlerParam_SetStatStages*)BattleHandler_PushWork(sf, ENTRY_EFFECT_SET_STAGES, pokeID);
    p->pokeID = (u8)pokeID;
    for (u32 v = 0; v < 7; ++v) p->stages[v] = (u8)GetBattleMonStat(src, 1 + v);
    BattleHandler_PopWork(sf, p);
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, ENTRY_MSG_COPIED_STATS);
    BattleHandler_AddArg(&m->str, pokeID);
    BattleHandler_AddArg(&m->str, ally);
    BattleHandler_PopWork(sf, m);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    MLOG("[ABIL] Costar: poke %d copies poke %d (Atk stage %d)", pokeID, ally, GetBattleMonStat(src, 1));
}

void HandlerSupersweetSyrupStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || pokeID >= ability::MAX_POKE_ID || g_syrupUsed[pokeID]) return;
    g_syrupUsed[pokeID] = true;
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, BTLMSG_SET_SUPERSWEET_SYRUP);
    BattleHandler_AddArg(&m->str, pokeID);
    BattleHandler_PopWork(sf, m);
    ability::ForEachOnField(sf, [&](u32 id) {
        if (!ability::SameSide(pokeID, id)) ability::ChangeStatStage(sf, pokeID, id, ability::STAT_EVASION, -1, false);
    });
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    MLOG("[ABIL] Supersweet Syrup: poke %d", pokeID);
}

constexpr BattleEventHandlerTableEntry CURIOUS_MEDICINE_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerCuriousMedicineStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerCuriousMedicineStart },
};
constexpr BattleEventHandlerTableEntry COSTAR_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerCostarStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerCostarStart },
};
constexpr BattleEventHandlerTableEntry SUPERSWEET_SYRUP_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerSupersweetSyrupStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerSupersweetSyrupStart },
};
} // namespace

void SupersweetSyrup_ResetForBattle() {
    for (bool& u : g_syrupUsed) u = false;
}

extern "C" const BattleEventHandlerTableEntry* EventAddCuriousMedicine(u32* packed) {
    *packed = sizeof(CURIOUS_MEDICINE_HANDLERS) / sizeof(CURIOUS_MEDICINE_HANDLERS[0]);
    return CURIOUS_MEDICINE_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddCostar(u32* packed) {
    *packed = sizeof(COSTAR_HANDLERS) / sizeof(COSTAR_HANDLERS[0]);
    return COSTAR_HANDLERS;
}
extern "C" const BattleEventHandlerTableEntry* EventAddSupersweetSyrup(u32* packed) {
    *packed = sizeof(SUPERSWEET_SYRUP_HANDLERS) / sizeof(SUPERSWEET_SYRUP_HANDLERS[0]);
    return SUPERSWEET_SYRUP_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_CuriousMedicineHandlers[2] = {CURIOUS_MEDICINE_HANDLERS[0], CURIOUS_MEDICINE_HANDLERS[1]};
static_assert(sizeof(CURIOUS_MEDICINE_HANDLERS) / sizeof(CURIOUS_MEDICINE_HANDLERS[0]) == 2, "MB_CuriousMedicineHandlers");
BattleEventHandlerTableEntry MB_CostarHandlers[2] = {COSTAR_HANDLERS[0], COSTAR_HANDLERS[1]};
static_assert(sizeof(COSTAR_HANDLERS) / sizeof(COSTAR_HANDLERS[0]) == 2, "MB_CostarHandlers");
BattleEventHandlerTableEntry MB_SupersweetSyrupHandlers[2] = {SUPERSWEET_SYRUP_HANDLERS[0], SUPERSWEET_SYRUP_HANDLERS[1]};
static_assert(sizeof(SUPERSWEET_SYRUP_HANDLERS) / sizeof(SUPERSWEET_SYRUP_HANDLERS[0]) == 2, "MB_SupersweetSyrupHandlers");
