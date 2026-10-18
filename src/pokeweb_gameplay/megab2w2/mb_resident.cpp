// MegaB2W2 wave C, the resident half's call-site hooks (White2Upgrade.dll, White 2 only). Engine call sites the event
// system does not reach: each hook below is a BL whose target was checked against vanilla White 2 and W2U's overlay
// 167 (none is hooked by W2U otherwise), and forwards to its resident call-site function, plain C on the engine
// interface (include/w2u/resident.h, src/mechanics/resident/), which also keeps the state the C mechanics share with
// them (the W2U_MB_* extensions in w2u/battle_api.h). A decomp build writes those calls into its source instead of
// the hooks (w2u-local/decomp/resident). See docs/engine-interface.md ("Call sites") and docs/megab2w2-integration.md
// (wave C).
#include "w2u/battle_api.h"
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"
#include "mb_resident.h"

// Commander (resident/commander.c): the hide checks' guaranteed-hit tests (ov167 0x21A3340, 0x21A6F7C; each followed
// by the hide check 0x21AA4A0), and ActionOrder_Proc's recharge action (kind 7, "X must recharge!", 0x21A094E)
extern "C" b32 THUMB_BRANCH_LINK_167_0x21A3340(BtlServerFlow* flow, BattleMon* a, BattleMon* t) { return W2U_GuaranteedHit(flow, a, t); }
extern "C" b32 THUMB_BRANCH_LINK_167_0x21A6F7C(BtlServerFlow* flow, BattleMon* a, BattleMon* t) { return W2U_GuaranteedHit(flow, a, t); }
extern "C" void THUMB_BRANCH_LINK_167_0x21A094E(BtlServerFlow* flow, BattleMon* mon) { W2U_RechargeAction(flow, mon); }

// Propeller Tail / Stalwart (resident/redirection.c): Lightning Rod / Storm Drain (0x21C0D82) and Follow Me / Rage
// Powder (0x21C64C4)
extern "C" b32 THUMB_BRANCH_LINK_167_0x21C0D82(BtlServerFlow* flow, u8 a, u8 r, u16 m) { return W2U_RedirectBlocked(flow, a, r, m); }
extern "C" b32 THUMB_BRANCH_LINK_167_0x21C64C4(BtlServerFlow* flow, u8 a, u8 r, u16 m) { return W2U_RedirectBlocked(flow, a, r, m); }

// The move each fight action will use (resident/pending_move.c): the two ServerEvent_GetMovePriority calls, the
// turn's first action order (0x21A0266, before its event 0x0F check) and SortActionOrderBySpeed (0x219FBF8)
extern "C" u8 THUMB_BRANCH_LINK_167_0x21A0266(BtlServerFlow* flow, u16 move, BattleMon* mon) { return W2U_GetMovePriority(flow, move, mon); }
extern "C" u8 THUMB_BRANCH_LINK_167_0x219FBF8(BtlServerFlow* flow, u16 move, BattleMon* mon) { return W2U_GetMovePriority(flow, move, mon); }

// Ripen / Cud Chew / Opportunist (resident/handler_effects.c): the handler-effect dispatcher's (ov167 0x21AC4F8)
// command calls; each returns the command's result
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC59E(BtlServerFlow* flow, BattleHandlerUseHeldItemParam* param) { return W2U_HandlerUseHeldItem(flow, param); }
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC6D6(BtlServerFlow* flow, BattleHandlerForceUseItemParam* param) { return W2U_HandlerForceUseItem(flow, param); }
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC5AA(BtlServerFlow* flow, BattleHandlerRecoverHPParam* param, u16 itemId) { return W2U_HandlerRecoverHP(flow, param, itemId); }
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC5C0(BtlServerFlow* flow, BattleHandlerDamageParam* param) { return W2U_HandlerDamage(flow, param); }
extern "C" u8 THUMB_BRANCH_LINK_167_0x21AC604(BtlServerFlow* flow, BattleHandlerStatChangeParam* param, u16 context) { return W2U_HandlerStatChange(flow, param, context); }

// ServerEvent_GetWeather (ov167 0x21A65A0), rewritten whole as vanilla: Air Lock / Cloud Nine (EVENT_WEATHER_NEGATION,
// VAR_WEATHER_NEGATED) -> no weather, else the field's; then Mega Sol (resident/weather.c). Its 8-byte GetWeather
// thunk at 0x21ABE08 is too short for PMC's 12-byte branch, so this replaces the function.
extern "C" u32 THUMB_BRANCH_ServerEvent_GetWeather(BtlServerFlow* flow) {
    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetRewriteOnceValue(VAR_WEATHER_NEGATED, 0);
    BattleEvent_CallHandlers(flow, EVENT_WEATHER_NEGATION);
    u32 negated = BattleEventVar_GetValue(VAR_WEATHER_NEGATED);
    BattleEventVar_Pop(__LINE__);
    return W2U_Weather(flow, negated ? 0 : (u8)GetFieldWeather());
}

// Battle exit (W2U_BattleState_OnBattleExit)
extern "C" void W2U_MB_ResetBattleState() {
    W2U_MB_MegaExtrasReset();
    W2U_Resident_ResetBattleState();
}
