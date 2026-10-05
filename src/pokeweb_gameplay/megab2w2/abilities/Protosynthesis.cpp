// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Protosynthesis.cpp); see docs/megab2w2-integration.md.
// Protosynthesis / Quark Drive (Gen 9; data/abilities.yml PROTOSYNTHESIS, QUARK_DRIVE; `logic: Protosynthesis`): in harsh
// sunlight / on Electric Terrain - or, without it, by using up a held Booster Energy - the holder's highest stat is
// boosted: x1.3, Speed x1.5 (Gen 9 / Showdown). Sun as abilities see it (GetWeather: Air Lock -> none; Desolate Land's
// extreme sun counts); the terrain from terrain.h (grounded or not). Below, "sun" means the row's condition.
// A sun boost ends when the sun does (then a held Booster Energy is used); a Booster boost lasts until the holder
// leaves. Checked when it enters / gains the ability, when anyone enters (weather setters), after every action
// (Sunny Day) and at the end of the turn (the sun running out). The best stat is taken at activation, stat stages
// included (Showdown's getBestStat(false, true); ability::BestStatWithStages), and kept until it ends. Booster Energy = EFFECT_CONSUME_ITEM (item animation, used for Recycle /
// Unburden). Boost: EVENT_ATTACKING_STAT / EVENT_DEFENDING_STAT for the matching stat, EVENT_CALC_SPEED. The state
// is cleared when the holder leaves and at battle start (mega::ResetForBattle), not on entry: the holder's
// EVENT_SWITCH_IN can come twice at battle start, and a reset there lost a Booster boost (the item already used).
#include "../ability_api.h"
#include "../megalog.h"
#include "../terrain.h"

namespace {
constexpr u32 PROTO_WEATHER_SUN = 1;
// per ability: the condition's activation message, the Booster Energy message, the end message
struct ProtoRow { u16 ability; u16 msgOn, msgBooster, msgEnd; };
const ProtoRow PROTO_ROWS[] = {
    { ABIL_PROTOSYNTHESIS, BTLMSG_SET_PROTO_SUN, BTLMSG_SET_PROTO_BOOSTER, BTLMSG_SET_PROTO_END },
    { ABIL_QUARK_DRIVE, BTLMSG_SET_QUARK_TERRAIN, BTLMSG_SET_QUARK_BOOSTER, BTLMSG_SET_QUARK_END },
};
const ProtoRow& ProtoRowOf(ServerFlow* sf, u32 pokeID) {
    return ability::HolderAbility(sf, pokeID) == ABIL_QUARK_DRIVE ? PROTO_ROWS[1] : PROTO_ROWS[0];
}
bool ProtoCondition(ServerFlow* sf, u32 pokeID) {
    if (ability::HolderAbility(sf, pokeID) == ABIL_QUARK_DRIVE) return terrain::Current() == terrain::ELECTRIC;
    return GetWeather(sf) == PROTO_WEATHER_SUN;
}
constexpr u16 PROTO_STAT_MSG[5] = { BTLMSG_SET_PROTO_ATTACK, BTLMSG_SET_PROTO_DEFENSE, BTLMSG_SET_PROTO_SP_ATK,
                                    BTLMSG_SET_PROTO_SP_DEF, BTLMSG_SET_PROTO_SPEED };
struct ProtoState { u8 stat; bool booster; };   // stat 0 = not active
ProtoState g_proto[ability::MAX_POKE_ID];

void ProtoMessage(ServerFlow* sf, u32 pokeID, u16 msg) {
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, msg);
    BattleHandler_AddArg(&m->str, pokeID);
    BattleHandler_PopWork(sf, m);
}
void ProtoActivate(ServerFlow* sf, u32 pokeID, bool booster) {
    BattleMon* bm = GetBattleMon(sf, pokeID);
    u32 stat = ability::BestStatWithStages(bm);
    MLOG("[ABIL] Protosynthesis: poke %d stages %d %d %d %d %d", pokeID, GetBattleMonStat(bm, 1), GetBattleMonStat(bm, 2),
         GetBattleMonStat(bm, 3), GetBattleMonStat(bm, 4), GetBattleMonStat(bm, 5));
    g_proto[pokeID].stat = (u8)stat; g_proto[pokeID].booster = booster;
    if (booster) {
        auto* c = (HandlerParam_ConsumeItem*)BattleHandler_PushWork(sf, EFFECT_CONSUME_ITEM, pokeID);
        c->noAnim = 0;
        BattleHandler_StrSetup(&c->exStr, ability::STRTYPE_SET, ProtoRowOf(sf, pokeID).msgBooster);
        BattleHandler_AddArg(&c->exStr, pokeID);
        BattleHandler_PopWork(sf, c);
    }
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    if (!booster) ProtoMessage(sf, pokeID, ProtoRowOf(sf, pokeID).msgOn);
    ProtoMessage(sf, pokeID, PROTO_STAT_MSG[stat - ability::STAT_ATK]);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    MLOG("[ABIL] Protosynthesis: poke %d stat %d (%s)", pokeID, stat, booster ? "Booster Energy" : "sun");
}
void ProtoCheck(ServerFlow* sf, u32 pokeID) {
    if (pokeID >= ability::MAX_POKE_ID || !ability::OnField(sf, pokeID)) return;
    BattleMon* bm = GetBattleMon(sf, pokeID);
    if (BattleMon_IsFainted(bm)) return;
    bool sun = ProtoCondition(sf, pokeID);
    ProtoState& s = g_proto[pokeID];
    if (s.stat && !s.booster && !sun) {
        s.stat = 0;
        ProtoMessage(sf, pokeID, ProtoRowOf(sf, pokeID).msgEnd);
        MLOG("[ABIL] Protosynthesis: poke %d ends (no sun)", pokeID);
    }
    if (s.stat) return;
    if (sun) ProtoActivate(sf, pokeID, false);
    else if (BattleMon_GetHeldItem(bm) == ITEM_BOOSTER_ENERGY) ProtoActivate(sf, pokeID, true);
}

void HandlerProtosynthesisCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) { ProtoCheck(sf, pokeID); }
void HandlerProtosynthesisLeave(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Subject() == pokeID && pokeID < ability::MAX_POKE_ID) g_proto[pokeID].stat = 0;
}
void HandlerProtosynthesisAttackingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    u32 cat = ability::MoveCategory(ability::Move()), stat = g_proto[pokeID].stat;
    if ((cat == ability::CATEGORY_PHYSICAL && stat == ability::STAT_ATK) ||
        (cat == ability::CATEGORY_SPECIAL && stat == ability::STAT_SPATK)) {
        ability::MulRatio(5325);
        if (!ability::Simulating(sf)) MLOG("[ABIL] Protosynthesis: poke %d attack x1.3", pokeID);
    }
}
void HandlerProtosynthesisDefendingStat(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    bool physical = BattleEventVar_GetValue(VAR_DAMAGE_CATEGORY) == 1;
    u32 stat = g_proto[pokeID].stat;
    if ((physical && stat == ability::STAT_DEF) || (!physical && stat == ability::STAT_SPDEF)) {
        ability::MulRatio(5325);
        if (!ability::Simulating(sf)) MLOG("[ABIL] Protosynthesis: poke %d defense x1.3", pokeID);
    }
}
void HandlerProtosynthesisSpeed(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    if (g_proto[pokeID].stat == ability::STAT_SPEED) ability::MulRatio(6144);
}

const BattleEventHandlerTableEntry PROTOSYNTHESIS_HANDLERS[] = {
    { EVENT_SWITCH_IN, HandlerProtosynthesisCheck },              // anyone entering may have set the weather
    { EVENT_AFTER_ABILITY_CHANGE, HandlerProtosynthesisCheck },
    { EVENT_ACTION_END, HandlerProtosynthesisCheck },
    { EVENT_TURN_CHECK, HandlerProtosynthesisCheck },
    { EVENT_SWITCH_OUT_END, HandlerProtosynthesisLeave },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerProtosynthesisLeave },
    { EVENT_ABILITY_NULLIFIED, HandlerProtosynthesisLeave },
    { EVENT_NOTIFY_FAINTED, HandlerProtosynthesisLeave },
    { EVENT_ATTACKING_STAT, HandlerProtosynthesisAttackingStat },
    { EVENT_DEFENDING_STAT, HandlerProtosynthesisDefendingStat },
    { EVENT_CALC_SPEED, HandlerProtosynthesisSpeed },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddProtosynthesis(u32* packed) {
    *packed = sizeof(PROTOSYNTHESIS_HANDLERS) / sizeof(PROTOSYNTHESIS_HANDLERS[0]);
    return PROTOSYNTHESIS_HANDLERS;
}
void Protosynthesis_ResetForBattle() { for (auto& s : g_proto) s.stat = 0; }

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_ProtosynthesisHandlers[11] = {PROTOSYNTHESIS_HANDLERS[0], PROTOSYNTHESIS_HANDLERS[1], PROTOSYNTHESIS_HANDLERS[2], PROTOSYNTHESIS_HANDLERS[3], PROTOSYNTHESIS_HANDLERS[4], PROTOSYNTHESIS_HANDLERS[5], PROTOSYNTHESIS_HANDLERS[6], PROTOSYNTHESIS_HANDLERS[7], PROTOSYNTHESIS_HANDLERS[8], PROTOSYNTHESIS_HANDLERS[9], PROTOSYNTHESIS_HANDLERS[10]};
static_assert(sizeof(PROTOSYNTHESIS_HANDLERS) / sizeof(PROTOSYNTHESIS_HANDLERS[0]) == 11, "MB_ProtosynthesisHandlers");
