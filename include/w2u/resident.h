/* W2U's resident call-site functions: what an engine call site W2U changes calls instead of the engine function it
 * called. Each takes that call's arguments and returns its result type, so the change at the call site is the
 * function's name alone:
 *
 *   injection build   a call-site hook (THUMB_BRANCH_LINK_<module>_0x<address>, megab2w2/mb_resident.cpp) forwards
 *                     to it;
 *   decomp build      the call written into the decomp's source calls it (w2u-local/decomp/resident).
 *
 * Plain C on the engine interface (w2u/battle_api.h), in src/mechanics/resident/; resident in both builds (a battle
 * module can be unloaded while the engine runs). Their battle state is zero when empty, so a decomp build's
 * overlay 167 starts every battle with it cleared; the injection build clears it at battle exit
 * (W2U_Resident_ResetBattleState). See docs/engine-interface.md, "Call sites". */
#ifndef W2U_RESIDENT_H
#define W2U_RESIDENT_H

#include "w2u/battle_api.h"

W2U_C_BEGIN

/* Propeller Tail / Stalwart (redirection.c): instead of Battle_IsRedirectBlocked in the redirection checks,
 * Lightning Rod / Storm Drain (CommonMoveTargetChangeToMe) and Follow Me / Rage Powder (HandlerFollowMeBaitTarget).
 * Nonzero: the attacker's move is not redirected to the redirector. */
b32 W2U_RedirectBlocked(BtlServerFlow *flow, u8 attackerId, u8 redirectorId, u16 move);

/* Commander (commander.c): a commanding Tatsugiri is hidden (Shadow Force's flag) and recharging each turn.
 * Instead of IsGuaranteedHit before the hide checks (the accuracy and OHKO paths): No Guard and Lock-On don't reach
 * it. Instead of ServerControl_RechargeAction for the action order's recharge action: no "must recharge" for it. */
b32 W2U_GuaranteedHit(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target);
void W2U_RechargeAction(BtlServerFlow *flow, BattleMon *mon);

/* The move each fight action will use (pending_move.c; W2U_MB_PendingMove): instead of ServerEvent_GetMovePriority
 * where the action order is sorted (the turn's first order and SortActionOrderBySpeed), noting the move. */
u8 W2U_GetMovePriority(BtlServerFlow *flow, u16 move, BattleMon *mon);

/* Ripen, Cud Chew, Opportunist (handler_effects.c): the handler-effect dispatcher's commands (BattleHandler_Execute)
 * run through these instead of BattleHandler_UseHeldItem, _ForceUseItem, _RecoverHP, _Damage and _StatChange: a
 * Ripen holder's Berries work twice, Cud Chew notes the Berry eaten, Opportunist's copies are flagged. */
u8 W2U_HandlerUseHeldItem(BtlServerFlow *flow, BattleHandlerUseHeldItemParam *param);
u8 W2U_HandlerForceUseItem(BtlServerFlow *flow, BattleHandlerForceUseItemParam *param);
u8 W2U_HandlerRecoverHP(BtlServerFlow *flow, BattleHandlerRecoverHPParam *param, u16 itemId);
u8 W2U_HandlerDamage(BtlServerFlow *flow, BattleHandlerDamageParam *param);
u8 W2U_HandlerStatChange(BtlServerFlow *flow, BattleHandlerStatChangeParam *param, u16 context);

/* Mega Sol (weather.c): ServerEvent_GetWeather's result goes through this: sun while a Mega Sol holder's move runs
 * (W2U_MB_SetMegaSolAttacker), the weather otherwise. */
u8 W2U_Weather(BtlServerFlow *flow, u8 weather);

/* Mold Breaker's skip check (mold_breaker.c), whole: the decomp's func_ov167_021c09d0 returns it. Nonzero: skip the
 * handler (an ability's, factor type 4, that the native list or W2U's later list has) */
b32 W2U_MoldBreakerSkipCheck(BattleEventItem *item, BtlServerFlow *flow, u32 factorType, u32 eventType, u32 subId);
b32 W2U_IsLaterIgnorableAbility(u16 ability);

/* The protection check (protect.c): per target of a move, whether its protection stops it (with "X protected itself!"
 * and W2U's EVENT_PROTECT_SUCCESS; a broken one raises EVENT_PROTECT_BROKEN). flowsub_CheckNoEffect_Protect's protect
 * step asks it in both builds. W2U_CheckProtectBreak: EVENT_PROTECT_BREAK_CHECK with the attacker, the target, the
 * category and the move; VAR_BREAK_PROTECT 0 holds, 1 broken (Feint), 2 the move goes through (Unseen Fist). */
b32 W2U_ProtectBlocks(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u16 move);
u32 W2U_CheckProtectBreak(BtlServerFlow *flow, u32 attacker, u32 defender, u32 category, u16 move);

/* Clears the state above (the injection build, at battle exit; a decomp build's overlay 167 starts with it clear) */
void W2U_Resident_ResetBattleState(void);
void W2U_Resident_ResetPendingMoves(void);
void W2U_Resident_ResetHandlerEffects(void);
void W2U_Resident_ResetWeather(void);

W2U_C_END

#endif
