// MegaB2W2 wave C, the resident half (White2Upgrade.dll, White 2 only; ported from MegaB2W2's PropellerTail.cpp,
// QuickDraw.cpp, MegaServer.cpp, EffectAbilities.cpp and MoveAbilities.cpp). Engine call sites the event system
// does not reach, and the state the C mechanics share with them (the W2U_MB_* extensions in w2u/battle_api.h). Every
// call site below is a BL whose target was checked against vanilla White 2 and W2U's overlay 167; none is hooked by
// W2U. Written against the engine interface (include/w2u/engine.h, docs/engine-interface.md); the THUMB_BRANCH_*
// call-site hooks are the injection build's, which a decomp build replaces with calls written into its source.
// See docs/megab2w2-integration.md (wave C).
#include "w2u/battle_api.h"
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"
#include "mb_resident.h"

namespace {
constexpr u8 NONE = 0xFF;
constexpr u32 SPECIES_TATSUGIRI = 978;

u16 sSortMove[BATTLE_MAX_MON_ID];   // the move of each fight action at the last action-order sort
u8 sRipenUser = NONE;               // a Ripen holder eating a Berry (its UseHeldItem / ForceUseItem is running)
u8 sCudChewing = NONE;              // a Cud Chew holder's second bite is running
u16 sCudBerry[BATTLE_MAX_MON_ID];
u8 sCudCounter[BATTLE_MAX_MON_ID];
u8 sOppPendingCopies[BATTLE_MAX_MON_ID];
u8 sOppCopying;
u8 sMegaSolAttacker = NONE;

BattleMon* Mon(BtlServerFlow* flow, u32 monId) { return monId < BATTLE_MAX_MON_ID ? GetBattleMon(flow, (u8)monId) : nullptr; }

// ---- Ripen / Cud Chew: Berries eaten ----------------------------------------------------------------------------
// The handler-effect dispatcher (ov167 0x21AC4F8) carries a held item's effects out inside its UseHeldItem, so a
// "this Ripen holder is eating a Berry" flag around that call sees the Berry's own heal / stat / damage effects.
// The command's result goes back to the dispatcher (checkPrevResult, BattleHandler_Result).
u8 UseItem(BtlServerFlow* flow, void* param, bool force) {
    BattleHandlerForceUseItemParam* forced = (BattleHandlerForceUseItemParam*)param;
    u32 monId = force ? forced->monIndex : ((BattleHandlerHeader*)param)->monId;
    BattleMon* mon = Mon(flow, monId);
    u16 item = !mon ? 0 : force ? forced->item : (u16)GetBattleMonHeldItem(mon);
    u8 prev = sRipenUser;
    if (mon && W2U_IsBerry(item) && W2U_HasActiveAbility(mon, ABIL_RIPEN)) sRipenUser = (u8)monId;
    u8 result = force ? BattleHandler_ForceUseItem(flow, forced)
                      : BattleHandler_UseHeldItem(flow, (BattleHandlerHeader*)param);
    sRipenUser = prev;
    if (mon && W2U_IsBerry(item) && sCudChewing != monId && W2U_HasActiveAbility(mon, ABIL_CUD_CHEW)) {
        sCudBerry[monId] = item;
        sCudCounter[monId] = 2;   // the end of this turn, then the next: chewed again
    }
    return result;
}
} // namespace

// ---- Commander (src/mechanics/abilities/form_abilities.c) --------------------------------------------------------
// The mechanic hides a commanding Tatsugiri with Shadow Force's flag and sets the recharge flag each turn so the
// command menu skips it. Showdown: nothing reaches a commanding Tatsugiri, No Guard and Lock-On included, and it makes
// no choice at all.
static bool Commanding(BattleMon* mon) {
    return mon && W2U_Species(mon) == SPECIES_TATSUGIRI && W2U_HasActiveAbility(mon, ABIL_COMMANDER) &&
           GetAdditionalConditionFlag(mon, CONT_FLAG_SHADOW_FORCE);
}
// No Guard / Lock-On / Mind Reader (IsGuaranteedHit) skip the hide check: not for it
static b32 GuaranteedHit(BtlServerFlow* flow, BattleMon* attacker, BattleMon* target) {
    return Commanding(target) ? 0 : IsGuaranteedHit(flow, attacker, target);
}

// ---- the call sites --------------------------------------------------------------------------------------------
// The hide checks' guaranteed-hit tests (ov167 0x21A3340, 0x21A6F7C; each followed by the hide check 0x21AA4A0)
extern "C" b32 THUMB_BRANCH_LINK_167_0x21A3340(BtlServerFlow* flow, BattleMon* a, BattleMon* t) { return GuaranteedHit(flow, a, t); }
extern "C" b32 THUMB_BRANCH_LINK_167_0x21A6F7C(BtlServerFlow* flow, BattleMon* a, BattleMon* t) { return GuaranteedHit(flow, a, t); }
// ActionOrder_Proc's recharge action (kind 7): "X must recharge!" (message 0x350), not for a commanding Tatsugiri
extern "C" void THUMB_BRANCH_LINK_167_0x21A094E(BtlServerFlow* flow, BattleMon* mon) {
    if (!Commanding(mon)) ServerControl_RechargeAction(flow, mon);
}

// Propeller Tail / Stalwart: Lightning Rod / Storm Drain (0x21C0D82) and Follow Me / Rage Powder (0x21C64C4) ask
// W2U_RedirectBlocked (src/mechanics/resident/redirection.c) instead of Battle_IsRedirectBlocked
extern "C" b32 THUMB_BRANCH_LINK_167_0x21C0D82(BtlServerFlow* flow, u8 a, u8 r, u16 m) { return W2U_RedirectBlocked(flow, a, r, m); }
extern "C" b32 THUMB_BRANCH_LINK_167_0x21C64C4(BtlServerFlow* flow, u8 a, u8 r, u16 m) { return W2U_RedirectBlocked(flow, a, r, m); }

// The two ServerEvent_GetMovePriority calls: the turn's first action order (0x21A0266, before its event 0x0F check)
// and SortActionOrderBySpeed (0x219FBF8). Event 0x0F follows for the same Pokemon without a move.
extern "C" u8 THUMB_BRANCH_LINK_167_0x21A0266(BtlServerFlow* flow, u16 move, BattleMon* mon) {
    u32 id = GetMonID(mon);
    if (id < BATTLE_MAX_MON_ID) sSortMove[id] = move;
    return ServerEvent_GetMovePriority(flow, move, mon);
}
extern "C" u8 THUMB_BRANCH_LINK_167_0x219FBF8(BtlServerFlow* flow, u16 move, BattleMon* mon) {
    u32 id = GetMonID(mon);
    if (id < BATTLE_MAX_MON_ID) sSortMove[id] = move;
    return ServerEvent_GetMovePriority(flow, move, mon);
}

// The dispatcher's command calls; each returns the command's result
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC59E(BtlServerFlow* flow, void* param) { return UseItem(flow, param, false); }
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC6D6(BtlServerFlow* flow, void* param) {
    u8 result = UseItem(flow, param, true);
    sCudChewing = NONE;
    return result;
}
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC5AA(BtlServerFlow* flow, BattleHandlerRecoverHPParam* param, u16 itemId) {
    if (sRipenUser != NONE && param->targetIndex == sRipenUser) param->amount = (u16)(param->amount * 2);   // Sitrus, Oran...
    return BattleHandler_RecoverHP(flow, param, itemId);
}
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC5C0(BtlServerFlow* flow, BattleHandlerDamageParam* param) {
    if (sRipenUser != NONE && param->targetIndex != sRipenUser) param->amount = (u16)(param->amount * 2);   // Jaboca / Rowap
    return BattleHandler_Damage(flow, param);
}
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC604(BtlServerFlow* flow, BattleHandlerStatChangeParam* param, u16 context) {
    bool single = param->change > 0 && param->count == 1 && param->monIds[0] < BATTLE_MAX_MON_ID;
    bool copy = single && sOppPendingCopies[param->monIds[0]] > 0;
    if (copy) --sOppPendingCopies[param->monIds[0]];
    if (single && sRipenUser != NONE && param->monIds[0] == sRipenUser)                           // Liechi, Salac...
        param->change = (s8)(param->change * 2 > 6 ? 6 : param->change * 2);
    u8 prev = sOppCopying;
    if (copy) sOppCopying = 1;
    u8 result = BattleHandler_StatChange(flow, param, context);
    sOppCopying = prev;
    return result;
}

// ServerEvent_GetWeather (ov167 0x21A65A0), rewritten whole as vanilla: Air Lock / Cloud Nine (EVENT_WEATHER_NEGATION,
// VAR_WEATHER_NEGATED) -> no weather, else the field's. Mega Sol first: during its holder's move, sun. (Its 8-byte
// GetWeather thunk at 0x21ABE08 is too short for PMC's 12-byte branch.)
extern "C" u32 THUMB_BRANCH_ServerEvent_GetWeather(BtlServerFlow* flow) {
    if (sMegaSolAttacker != NONE && W2U_HasActiveAbility(Mon(flow, sMegaSolAttacker), ABIL_MEGA_SOL))
        return WEATHER_SUN;
    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetRewriteOnceValue(VAR_WEATHER_NEGATED, 0);
    BattleEvent_CallHandlers(flow, EVENT_WEATHER_NEGATION);
    u32 negated = BattleEventVar_GetValue(VAR_WEATHER_NEGATED);
    BattleEventVar_Pop(__LINE__);
    return negated ? 0 : GetFieldWeather();
}

// ---- the API (w2u/battle_api.h's W2U extensions, mb_resident.h) --------------------------------------------------
extern "C" void W2U_MB_ResetBattleState() {
    W2U_MB_MegaExtrasReset();
    sRipenUser = sCudChewing = sMegaSolAttacker = NONE;
    sOppCopying = 0;
    for (u32 i = 0; i < BATTLE_MAX_MON_ID; ++i) {
        sSortMove[i] = 0; sCudBerry[i] = 0; sCudCounter[i] = 0; sOppPendingCopies[i] = 0;
    }
}

extern "C" u16 W2U_MB_PendingMove(BtlServerFlow* flow, u32 monId) {
    ActionOrderEntry* order = W2U_ActionOrder(flow);
    for (u32 i = 0; i < W2U_ActionOrderCount(flow); ++i) {
        const ActionOrderEntry& e = order[i];
        if (e.done || !e.mon || GetMonID(e.mon) != monId) continue;
        return W2U_ActionMove(e.action);
    }
    // The turn's first order runs before the action order is filled in: the move just noted for this Pokemon.
    return monId < BATTLE_MAX_MON_ID ? sSortMove[monId] : 0;
}

extern "C" void W2U_MB_ClearPendingMove(u32 monId) {
    if (monId < BATTLE_MAX_MON_ID) sSortMove[monId] = 0;
}

extern "C" u16 W2U_MB_CudChewTurnEnd(u32 monId) {
    if (monId >= BATTLE_MAX_MON_ID || !sCudBerry[monId] || --sCudCounter[monId]) return 0;
    u16 item = sCudBerry[monId];
    sCudBerry[monId] = 0;
    sCudChewing = (u8)monId;   // cleared when the bite has run: it is not noted again
    return item;
}
extern "C" void W2U_MB_CudChewForget(u32 monId) {
    if (monId < BATTLE_MAX_MON_ID) sCudBerry[monId] = 0;
}

extern "C" void W2U_MB_OpportunistCopyQueued(u32 monId) {
    if (monId < BATTLE_MAX_MON_ID) ++sOppPendingCopies[monId];
}
extern "C" u8 W2U_MB_OpportunistCopying(void) { return sOppCopying; }

extern "C" void W2U_MB_SetMegaSolAttacker(u32 monId) { sMegaSolAttacker = (u8)(monId < BATTLE_MAX_MON_ID ? monId : NONE); }
