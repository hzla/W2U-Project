// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/HitReactions.cpp); see docs/megab2w2-integration.md.
// Reactions to being hit (Gen 8-9), one file, three logic names (Gen 9 / Showdown onDamagingHit; the hit reaction
// EVENT_AFTER_DAMAGE_REACTION, the defender is the holder, not a substitute hit):
//   `logic: CottonDown`   Every other Pokémon on the field (allies too) has its Speed lowered by 1.
//   `logic: PerishBody`   A contact move: the attacker and the holder both get Perish Song's count (condition 20,
//                         3 turns; one already counting down is left alone), "Both Pokémon will faint in three turns!".
//   `logic: ToxicDebris`  A physical move: a layer of Toxic Spikes on the attacker's side (the engine's side effect 7,
//                         permanent, its own "Poison spikes were scattered..." message 152; max 2 layers - the engine).
// Toxic Debris and Cotton Down follow PW2Code (Paideieitor; docs/CREDITS.md), with this framework's event names.
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

extern "C" {
u32 Condition_MakeTurn(u32 turns);                    // 0x21CE1C0: a continuation lasting `turns`
u32 Condition_MakePermanent();                        // 0x21CE240
u32 GetSideFromOpposingMonID(u32 pokeID);             // 0x219D36C: the side facing pokeID
}

namespace {
constexpr u32 HIT_EFFECT_ADD_SIDE_EFFECT = 0x19, HIT_CONDITION_PERISH = 20, HIT_SIDE_TOXIC_SPIKES = 7;
constexpr u16 HIT_MSG_TOXIC_SPIKES = 152;             // std bank: "Poison spikes were scattered all around..." (+side)
struct HandlerParam_AddSideEffectH { HandlerParam_Header header; u32 sideEffect; u32 cont; u8 side; u8 _d[3];
                                     HandlerParam_StrParams exStr; };

bool HitReactionApplies(u32 pokeID) {
    return ability::Defender() == pokeID && !BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) &&
           ability::Attacker() != pokeID && ability::Attacker() < ability::MAX_POKE_ID;
}

void HandlerCottonDownHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (!HitReactionApplies(pokeID)) return;
    auto* p = (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(sf, EFFECT_CHANGE_STAT_STAGE, pokeID);
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->stat = ability::STAT_SPEED;
    p->stages = -1;
    p->_e = 1;
    p->pokeCount = 0;
    ability::ForEachOnField(sf, [&](u32 id) { if (id != pokeID && p->pokeCount < 6) p->pokeIDs[p->pokeCount++] = (u8)id; });
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Cotton Down: poke %d lowers the Speed of %d Pokémon", pokeID, p->pokeCount);
}

void HandlerPerishBodyHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (!HitReactionApplies(pokeID) || !ability::MakesContact(sf, ability::Move())) return;
    u32 ids[2] = { ability::Attacker(), pokeID };
    bool announced = false;
    for (u32 id : ids) {
        BattleMon* bm = GetBattleMon(sf, id);
        if (BattleMon_IsFainted(bm) || CheckCondition(bm, HIT_CONDITION_PERISH)) continue;
        if (!announced) {
            announced = true;
            BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
        }
        auto* c = (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
        c->condition = HIT_CONDITION_PERISH;
        c->cont = Condition_MakeTurn(4);
        c->pokeID = (u8)id;
        BattleHandler_PopWork(sf, c);
    }
    if (!announced) return;
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, BTL_STRTYPE_STD, BTLMSG_STD_PERISH_BODY);
    BattleHandler_PopWork(sf, m);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    MLOG("[ABIL] Perish Body: poke %d and poke %d", pokeID, ids[0]);
}

void HandlerToxicDebrisHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (!HitReactionApplies(pokeID) || ability::MoveCategory(ability::Move()) != ability::CATEGORY_PHYSICAL) return;
    u32 side = GetSideFromOpposingMonID(pokeID);
    auto* p = (HandlerParam_AddSideEffectH*)BattleHandler_PushWork(sf, HIT_EFFECT_ADD_SIDE_EFFECT, pokeID);
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->sideEffect = HIT_SIDE_TOXIC_SPIKES;
    p->side = (u8)side;
    p->cont = Condition_MakePermanent();
    BattleHandler_StrSetup(&p->exStr, BTL_STRTYPE_STD, HIT_MSG_TOXIC_SPIKES);
    BattleHandler_AddArg(&p->exStr, side);
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Toxic Debris: poke %d, Toxic Spikes on side %d", pokeID, side);
}

constexpr BattleEventHandlerTableEntry COTTON_DOWN_HANDLERS[] = { { EVENT_AFTER_DAMAGE_REACTION, HandlerCottonDownHit } };
constexpr BattleEventHandlerTableEntry PERISH_BODY_HANDLERS[] = { { EVENT_AFTER_DAMAGE_REACTION, HandlerPerishBodyHit } };
constexpr BattleEventHandlerTableEntry TOXIC_DEBRIS_HANDLERS[] = { { EVENT_AFTER_DAMAGE_REACTION, HandlerToxicDebrisHit } };
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddCottonDown(u32* packed) { *packed = 1; return COTTON_DOWN_HANDLERS; }
extern "C" const BattleEventHandlerTableEntry* EventAddPerishBody(u32* packed) { *packed = 1; return PERISH_BODY_HANDLERS; }
extern "C" const BattleEventHandlerTableEntry* EventAddToxicDebris(u32* packed) { *packed = 1; return TOXIC_DEBRIS_HANDLERS; }

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_CottonDownHandlers[1] = {COTTON_DOWN_HANDLERS[0]};
static_assert(sizeof(COTTON_DOWN_HANDLERS) / sizeof(COTTON_DOWN_HANDLERS[0]) == 1, "MB_CottonDownHandlers");
BattleEventHandlerTableEntry MB_PerishBodyHandlers[1] = {PERISH_BODY_HANDLERS[0]};
static_assert(sizeof(PERISH_BODY_HANDLERS) / sizeof(PERISH_BODY_HANDLERS[0]) == 1, "MB_PerishBodyHandlers");
BattleEventHandlerTableEntry MB_ToxicDebrisHandlers[1] = {TOXIC_DEBRIS_HANDLERS[0]};
static_assert(sizeof(TOXIC_DEBRIS_HANDLERS) / sizeof(TOXIC_DEBRIS_HANDLERS[0]) == 1, "MB_ToxicDebrisHandlers");
