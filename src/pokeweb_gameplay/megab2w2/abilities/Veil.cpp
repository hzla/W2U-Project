// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/Veil.cpp); see docs/megab2w2-integration.md.
// Veil family (`logic: Veil`; data/abilities.yml AROMA_VEIL, FLOWER_VEIL, SWEET_VEIL, PASTEL_VEIL): the holder and
// its allies are protected from a set of conditions (Gen 9 / Showdown):
//   Aroma Veil: Attract, Taunt, Torment, Disable, Heal Block, Encore.
//   Flower Veil: Grass types only: major status and Yawn from another Pokémon, and stat drops from another Pokémon.
//   Sweet Veil: sleep and Yawn (also self-inflicted: Rest fails).
//   Pastel Veil: poison (incl. bad poison); on entry it cures poisoned allies, and an ally entering poisoned.
// The status check is the vanilla one (EVENT_ADD_CONDITION_CHECK: VAR_DEFENDING_MON the target, VAR_CONDITION,
// VAR_FAIL_FLAG; Insomnia's pattern) and the Yawn check (EVENT_YAWN_CHECK, VAR_MON_ID). The message (the holder's popup
// and the row's Gen 9 line naming the protected Pokémon) is pushed right there: some paths never raise
// EVENT_ADD_CONDITION_FAILED (a Taunt move, Toxic Orb); that event only swallows the engine's own failure text. Stat drops:
// Clear Body's check / guard pair (EVENT_STAT_CHANGE_CHECK / _GUARD). Mold Breaker ignores them (`breakable: true`).
// Conditions (scripts/data/movereg.py CONDITION): 2 sleep, 5 poison, 7 attract, 11 taunt, 12 torment, 13 disable,
// 14 Yawn's drowsiness, 15 heal block, 23 encore.
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

namespace {
constexpr u32 VEIL_NONE = 0x1F;
enum : u8 { VEIL_GRASS = 1, VEIL_OTHERS_ONLY = 2, VEIL_STAT_DROPS = 4, VEIL_YAWN = 8, VEIL_CURE = 16 };
struct VeilRow { u16 ability; u8 flags; u8 count; u8 conds[7]; u16 msg; ROW_NAME_FIELD };
const VeilRow VEIL_ROWS[] = {
    { ABIL_AROMA_VEIL, 0, 6, { 7, 11, 12, 13, 15, 23 }, BTLMSG_SET_AROMA_VEIL ROW_NAME("Aroma Veil") },
    { ABIL_FLOWER_VEIL, VEIL_GRASS | VEIL_OTHERS_ONLY | VEIL_STAT_DROPS | VEIL_YAWN, 6, { 1, 2, 3, 4, 5, 14 },
      BTLMSG_SET_FLOWER_VEIL ROW_NAME("Flower Veil") },
    { ABIL_SWEET_VEIL, VEIL_YAWN, 2, { 2, 14 }, BTLMSG_SET_SWEET_VEIL ROW_NAME("Sweet Veil") },
    { ABIL_PASTEL_VEIL, VEIL_CURE, 1, { 5 }, BTLMSG_SET_PASTEL_VEIL ROW_NAME("Pastel Veil") },
};
constexpr u32 VEIL_TYPE_GRASS = 11;
constexpr u32 VEIL_COND_POISON = 5;

const VeilRow* VeilRowOf(ServerFlow* sf, u32 pokeID) {
    u16 ability = ability::HolderAbility(sf, pokeID);
    for (const VeilRow& r : VEIL_ROWS)
        if (r.ability == ability) return &r;
    return nullptr;
}
// Does the holder's veil cover `target`?
bool VeilCovers(ServerFlow* sf, const VeilRow* r, u32 holder, u32 target) {
    if (target >= ability::MAX_POKE_ID || !ability::SameSide(holder, target)) return false;
    if (target != holder && !ability::OnField(sf, target)) return false;
    if (r->flags & VEIL_GRASS) return PokeTypePair_HasType(GetPokeType(GetBattleMon(sf, target)), VEIL_TYPE_GRASS);
    return true;
}
bool VeilBlocksCondition(const VeilRow* r, u32 cond) {
    for (u32 i = 0; i < r->count; ++i)
        if (r->conds[i] == cond) return true;
    return false;
}
void VeilMessage(ServerFlow* sf, u32 pokeID, const VeilRow* r, u32 target);
// work[0] = 1: a block happened (EVENT_ADD_CONDITION_FAILED then has nothing more to say)
void VeilBlocked(ServerFlow* sf, u32 pokeID, const VeilRow* r, u32* work, u32 target) {
    work[0] = 1;
    VeilMessage(sf, pokeID, r, target);
}

void HandlerVeilConditionCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    const VeilRow* r = VeilRowOf(sf, pokeID);
    u32 target = ability::Defender(), cond = (u32)BattleEventVar_GetValue(VAR_CONDITION);
    if (!r || !VeilBlocksCondition(r, cond) || !VeilCovers(sf, r, pokeID, target)) return;
    if ((r->flags & VEIL_OTHERS_ONLY) && ability::Attacker() == target) return;
    if (BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) {
        VeilBlocked(sf, pokeID, r, work, target);
        MLOG("[ABIL] %s: poke %d blocks condition %d on poke %d", r->name, pokeID, cond, target);
    }
}
void HandlerVeilYawnCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    const VeilRow* r = VeilRowOf(sf, pokeID);
    u32 target = ability::Subject();
    if (!r || !(r->flags & VEIL_YAWN) || !VeilCovers(sf, r, pokeID, target)) return;
    if (BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) {
        VeilBlocked(sf, pokeID, r, work, target);
        MLOG("[ABIL] %s: poke %d blocks Yawn on poke %d", r->name, pokeID, target);
    }
}
void VeilMessage(ServerFlow* sf, u32 pokeID, const VeilRow* r, u32 target) {
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, r->msg);
    BattleHandler_AddArg(&m->str, target);
    BattleHandler_PopWork(sf, m);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}
void HandlerVeilConditionFailed(BattleEventItem*, ServerFlow*, u32, u32* work) {
    work[0] = 0;   // the message is out already
}
// Flower Veil: stat drops from another Pokémon (Clear Body's pair; the message at the guard event)
void HandlerVeilStatCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    const VeilRow* r = VeilRowOf(sf, pokeID);
    u32 target = ability::Subject(), source = ability::Attacker();
    if (!r || !(r->flags & VEIL_STAT_DROPS) || !VeilCovers(sf, r, pokeID, target)) return;
    if (source == target || source == VEIL_NONE || (int)BattleEventVar_GetValue(VAR_STAT_CHANGE) >= 0) return;
    if (BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1)) {
        work[2] = 1; work[3] = target;
        MLOG("[ABIL] %s: poke %d blocks a stat drop on poke %d", r->name, pokeID, target);
    }
}
void HandlerVeilStatGuard(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work) {
    if (work[2] != 1) return;
    work[2] = 0;
    const VeilRow* r = VeilRowOf(sf, pokeID);
    if (r) VeilMessage(sf, pokeID, r, work[3]);
}
// Pastel Veil: cure poison (CommonAbilityCureStatusCore's effect, for any Pokémon on the holder's side)
void VeilCure(ServerFlow* sf, u32 pokeID, u32 target, bool* popup) {
    if (!CheckCondition(GetBattleMon(sf, target), VEIL_COND_POISON)) return;
    if (!*popup) { BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID); *popup = true; }
    auto* p = (HandlerParam_CureCondition*)BattleHandler_PushWork(sf, EFFECT_CURE_CONDITION, pokeID);
    p->condition = VEIL_COND_POISON;
    p->pokeID = (u8)target;
    p->_14 = 1;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Pastel Veil: poke %d cures poke %d", pokeID, target);
}
void HandlerVeilSwitchIn(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    const VeilRow* r = VeilRowOf(sf, pokeID);
    if (!r || !(r->flags & VEIL_CURE)) return;
    u32 who = ability::Subject();
    bool popup = false;
    if (who == pokeID) {   // the holder enters: every poisoned Pokémon on its side
        ability::ForEachOnField(sf, [&](u32 id) { if (ability::SameSide(pokeID, id)) VeilCure(sf, pokeID, id, &popup); });
    } else if (ability::SameSide(pokeID, who) && ability::OnField(sf, pokeID)) {
        VeilCure(sf, pokeID, who, &popup);
    }
    if (popup) BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}

constexpr BattleEventHandlerTableEntry VEIL_HANDLERS[] = {
    { EVENT_ADD_CONDITION_CHECK, HandlerVeilConditionCheck },
    { EVENT_YAWN_CHECK, HandlerVeilYawnCheck },
    { EVENT_ADD_CONDITION_FAILED, HandlerVeilConditionFailed },
    { EVENT_STAT_CHANGE_CHECK, HandlerVeilStatCheck },
    { EVENT_STAT_CHANGE_GUARD, HandlerVeilStatGuard },
    { EVENT_SWITCH_IN, HandlerVeilSwitchIn },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerVeilSwitchIn },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddVeil(u32* packed) {
    *packed = sizeof(VEIL_HANDLERS) / sizeof(VEIL_HANDLERS[0]);
    return VEIL_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_VeilHandlers[7] = {VEIL_HANDLERS[0], VEIL_HANDLERS[1], VEIL_HANDLERS[2], VEIL_HANDLERS[3], VEIL_HANDLERS[4], VEIL_HANDLERS[5], VEIL_HANDLERS[6]};
static_assert(sizeof(VEIL_HANDLERS) / sizeof(VEIL_HANDLERS[0]) == 7, "MB_VeilHandlers");
