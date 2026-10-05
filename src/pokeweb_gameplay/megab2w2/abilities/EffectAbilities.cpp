// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/EffectAbilities.cpp); see docs/megab2w2-integration.md.
// Abilities that react to handler effects being carried out (Gen 8-9; Gen 9 / Showdown). The effect dispatcher's
// calls (ov167 0x21AC4F8: UseHeldItem, RecoverHP, Damage, StatChange, ForceUseItem) are wrapped in the resident core
// (mb_resident.cpp), which does the part that has to happen inside those calls; these are the holders' handlers.
//   Ripen        A Berry's HP restored, stat boosts and damage to the attacker (Jaboca / Rowap) are doubled (the
//                resident wrappers); the popup at event 0x72 (the item is used). Damage-halving Berries (Occa...) are
//                not doubled.
//   Opportunist  A foe's stat raises (what was actually applied, event 0x5D: moves and effects) are copied by the
//                holder after the move / action / switch-in / turn end (Showdown's onFoeAfterBoost + onAnyAfterMove).
//                Its own copies are not copied back: the resident StatChange wrapper runs them with a flag set.
//   Cud Chew     A Berry the holder ate (noted by the resident UseHeldItem wrapper) is eaten again at the end of the
//                next turn (turn end event 0x77, EFFECT_FORCE_USE_ITEM as Bug Bite eats).
// (MegaB2W2's Symbiosis is not ported: W2U has its own.)
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_resident.h"

namespace {
constexpr u32 FX_EVENT_USE_ITEM = 0x72, FX_EVENT_TURN_END = 0x77;
constexpr u32 FX_EFFECT_FORCE_USE_ITEM = 0x22;
constexpr u32 FX_FORCE_USE_FLAG = 1u << 24;            // header flag PW2Code's Cud Chew sets (eat, not held)
struct HandlerParam_ForceUseItemFX { HandlerParam_Header header; u8 pokeID; u8 ateBerry; u16 item; };

s8 g_oppBoost[ability::MAX_POKE_ID][8];

// ---- Ripen -------------------------------------------------------------------------------------------------
void HandlerRipenUseItem(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || !ability::IsBerry(BattleMon_GetHeldItem(GetBattleMon(sf, pokeID)))) return;
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}

// ---- Opportunist -------------------------------------------------------------------------------------------
void OpportunistApply(ServerFlow* sf, u32 pokeID) {
    if (pokeID >= ability::MAX_POKE_ID || !ability::OnField(sf, pokeID) || BattleMon_IsFainted(GetBattleMon(sf, pokeID)))
        return;
    bool popup = false;
    for (u32 stat = ability::STAT_ATK; stat <= ability::STAT_EVASION; ++stat) {
        int n = g_oppBoost[pokeID][stat];
        if (n <= 0) continue;
        g_oppBoost[pokeID][stat] = 0;
        if (!popup) { popup = true; BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID); }
        W2U_MB_OpportunistCopyQueued(pokeID);   // before the push: the effect may run at once
        ability::ChangeStatStage(sf, pokeID, pokeID, stat, n > 6 ? 6 : n, false);
        MLOG("[ABIL] Opportunist: poke %d copies stat %d +%d", pokeID, stat, n);
    }
    if (popup) BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
}
void HandlerOpportunistAny(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) { OpportunistApply(sf, pokeID); }
// event 0x5D: VAR_MON_ID's VAR_STAT changed by VAR_STAT_CHANGE (as applied) - moves and effects alike
void HandlerOpportunistStatApplied(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    u32 target = ability::Subject(), stat = (u32)BattleEventVar_GetValue(VAR_STAT);
    int n = BattleEventVar_GetValue(VAR_STAT_CHANGE);
    if (W2U_MB_OpportunistCopying() || n <= 0 || target == pokeID || target >= ability::MAX_POKE_ID ||
        IsAllyMonID(pokeID, target))
        return;
    if (stat < ability::STAT_ATK || stat > ability::STAT_EVASION || pokeID >= ability::MAX_POKE_ID) return;
    int v = g_oppBoost[pokeID][stat] + n;
    g_oppBoost[pokeID][stat] = (s8)(v > 12 ? 12 : v);
    MLOG("[ABIL] Opportunist: poke %d noted poke %d's stat %d +%d", pokeID, target, stat, n);
}

// ---- Cud Chew ----------------------------------------------------------------------------------------------
void HandlerCudChewTurnEnd(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    if (BattleMon_IsFainted(GetBattleMon(sf, pokeID))) { W2U_MB_CudChewForget(pokeID); return; }
    u16 item = W2U_MB_CudChewTurnEnd(pokeID);
    if (!item) return;
    BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
    auto* p = (HandlerParam_ForceUseItemFX*)BattleHandler_PushWork(sf, FX_EFFECT_FORCE_USE_ITEM, pokeID);
    p->header.flags |= FX_FORCE_USE_FLAG;
    p->pokeID = (u8)pokeID;
    p->item = item;
    BattleHandler_PopWork(sf, p);
    BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
    MLOG("[ABIL] Cud Chew: poke %d chews item %d again", pokeID, item);
}

const BattleEventHandlerTableEntry RIPEN_HANDLERS[] = { { FX_EVENT_USE_ITEM, HandlerRipenUseItem } };
const BattleEventHandlerTableEntry OPPORTUNIST_HANDLERS[] = {
    { EVENT_STAT_LOWERED, HandlerOpportunistStatApplied },
    { EVENT_MOVE_END, HandlerOpportunistAny },
    { EVENT_ACTION_END, HandlerOpportunistAny },
    { EVENT_SWITCH_IN, HandlerOpportunistAny },
    { FX_EVENT_TURN_END, HandlerOpportunistAny },
};
const BattleEventHandlerTableEntry CUD_CHEW_HANDLERS[] = { { FX_EVENT_TURN_END, HandlerCudChewTurnEnd } };
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_RipenHandlers[1] = {RIPEN_HANDLERS[0]};
BattleEventHandlerTableEntry MB_OpportunistHandlers[5] = {OPPORTUNIST_HANDLERS[0], OPPORTUNIST_HANDLERS[1],
                                                          OPPORTUNIST_HANDLERS[2], OPPORTUNIST_HANDLERS[3],
                                                          OPPORTUNIST_HANDLERS[4]};
BattleEventHandlerTableEntry MB_CudChewHandlers[1] = {CUD_CHEW_HANDLERS[0]};
static_assert(sizeof(RIPEN_HANDLERS) / sizeof(RIPEN_HANDLERS[0]) == 1, "MB_RipenHandlers");
static_assert(sizeof(OPPORTUNIST_HANDLERS) / sizeof(OPPORTUNIST_HANDLERS[0]) == 5, "MB_OpportunistHandlers");
static_assert(sizeof(CUD_CHEW_HANDLERS) / sizeof(CUD_CHEW_HANDLERS[0]) == 1, "MB_CudChewHandlers");
