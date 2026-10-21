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

/* Ripen, Cud Chew, Opportunist, consumed items (handler_effects.c): the handler-effect dispatcher's commands
 * (BattleHandler_Execute) run through these instead of BattleHandler_UseHeldItem, _ForceUseItem, _RecoverHP, _Damage
 * and _StatChange: a Ripen holder's Berries work twice, Cud Chew notes the Berry eaten, Opportunist's copies are
 * flagged. ServerControl_ChangeHeldItem's consume branch calls W2U_ItemConsumed (BattleHandler_ConsumeItem passes
 * 1 + skipDisplay: 1 eaten, 2 consumed without eating): notes a Berry eaten (Belch) and raises EVENT_CONSUME_ITEM
 * (Cheek Pouch, Symbiosis). */
u8 W2U_HandlerUseHeldItem(BtlServerFlow *flow, BattleHandlerUseHeldItemParam *param);
u8 W2U_HandlerForceUseItem(BtlServerFlow *flow, BattleHandlerForceUseItemParam *param);
u8 W2U_HandlerRecoverHP(BtlServerFlow *flow, BattleHandlerRecoverHPParam *param, u16 itemId);
u8 W2U_HandlerDamage(BtlServerFlow *flow, BattleHandlerDamageParam *param);
u8 W2U_HandlerStatChange(BtlServerFlow *flow, BattleHandlerStatChangeParam *param, u16 context);
void W2U_ItemConsumed(BtlServerFlow *flow, u32 monId, u16 item, b32 consume);
void W2U_MoveState_SetConsumedBerryFlag(u32 monId);
b32 W2U_MoveState_HasConsumedBerryFlag(u32 monId);

/* Mega Sol (weather.c): ServerEvent_GetWeather's result goes through this: sun while a Mega Sol holder's move runs
 * (W2U_MB_SetMegaSolAttacker), the weather otherwise. */
u8 W2U_Weather(BtlServerFlow *flow, u8 weather);

/* Strong weathers (strong_weather.c; their state: w2u/strong_weather.h). ServerControl_ChangeWeatherCheck asks
 * W2U_StrongWeatherBlocksChange first (nonzero: another weather fails, with the kind's message). AICalcDamage calls
 * W2U_AICalcDamage instead of ServerEvent_CalcDamage: a move the strong weather would make fizzle is estimated as one
 * that doesn't affect the target (W2U_StrongWeatherStopsMove). */
b32 W2U_StrongWeatherBlocksChange(BtlServerFlow *flow, u32 weather);
b32 W2U_StrongWeatherStopsMove(BtlServerFlow *flow, const BtlFlowMoveParam *param);   /* it would fizzle */
b32 W2U_AICalcDamage(BtlServerFlow *flow, BattleMon *attacker, BattleMon *defender, const BtlFlowMoveParam *param,
                     u32 effectiveness, u32 ratio, b32 critical, b32 fixedRoll, u16 *damage);

/* Mold Breaker's skip check (mold_breaker.c), whole: the decomp's HandlerMoldBreakerSkipCheck returns it. Nonzero: skip the
 * handler (an ability's, factor type 4, that the native list or W2U's later list has) */
b32 W2U_MoldBreakerSkipCheck(BattleEventItem *item, BtlServerFlow *flow, u32 factorType, u32 eventType, u32 subId);
b32 W2U_IsLaterIgnorableAbility(u16 ability);

/* The protection check and Protect's counter (protect.c): per target of a move, whether its protection stops it (with
 * "X protected itself!" and W2U's EVENT_PROTECT_SUCCESS; a broken one raises EVENT_PROTECT_BROKEN).
 * flowsub_CheckNoEffect_Protect's protect step asks it in both builds. W2U_CheckProtectBreak:
 * EVENT_PROTECT_BREAK_CHECK with the attacker, the target, the category and the move; VAR_BREAK_PROTECT 0 holds,
 * 1 broken (Feint), 2 the move goes through (Unseen Fist). W2U_StartProtectCounterMove (HandlerProtectStart): resets
 * COUNTER_PROTECT unless the Pokémon's previous executed move is in W2U_IsProtectCounterMove (the damage shields too). */
b32 W2U_ProtectBlocks(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u16 move);
u32 W2U_CheckProtectBreak(BtlServerFlow *flow, u32 attacker, u32 defender, u32 category, u16 move);
b32 W2U_IsProtectCounterMove(u16 move);
void W2U_StartProtectCounterMove(BtlServerFlow *flow, u32 monId);

/* The move lists W2U extends (move_lists.c): instead of IsAffectedBySheerForce in Sheer Force's handlers, and of
 * Is{Assist,SleepTalk,MeFirst,Copycat}ExcludedMove in those moves' handlers (the torques: NPC-only) */
b32 W2U_IsAffectedBySheerForce(u16 move);
b32 W2U_MoveIsRestrictedNpcAttack(u16 move);
b32 W2U_IsAssistExcludedMove(u16 move);
b32 W2U_IsSleepTalkExcludedMove(u16 move);
b32 W2U_IsMeFirstExcludedMove(u16 move);
b32 W2U_IsCopycatExcludedMove(u16 move);

/* Status conditions (status.c): Comatose (asleep for CheckCondition; no major status or drowsiness; its curing items
 * don't react), Corrosion (poisons Steel and Poison types), Hex (any major status as CheckCondition sees it), a status
 * check failed with W2U_FORCE_FAIL_MESSAGE (shows its message). W2U_ConditionFailCause adjusts
 * AddConditionCheckFailOverwrite's cause. */
b32 W2U_IsComatose(BattleMon *mon);
b32 W2U_ComatoseAsleep(BattleMon *mon, u32 condition);
u32 W2U_ConditionFailCause(BattleMon *target, BattleMon *attacker, u32 condition, u32 cause);
b32 W2U_ConditionFailForcesMessage(u32 failed);
b32 W2U_HasMajorStatus(BattleMon *mon);

/* The category a move hits with (move_category.c): Shell Side Arm (its handler's pick), Photon Geyser (Attack against
 * Special Attack), the record's otherwise. The damage path asks it instead of PML_MoveGetCategory: W2U_CalcDamageCategory
 * (CalcDamage, which records Shell Side Arm's for Counter), W2U_HitCategory (GetAttackPower, GetTargetDefenses;
 * record: keep Photon Geyser's). W2U_RecordedMoveCategory: the category of the attacker's last such hit (Counter,
 * Mirror Coat). */
u32 W2U_CalcDamageCategory(u16 move, BattleMon *attacker);
u32 W2U_HitCategory(u16 move, BattleMon *attacker, b32 record);
u32 W2U_RecordedMoveCategory(u16 move, u32 attackerId);
void W2U_MoveState_SetShellSideArmCategory(u32 monId, u32 category);
void W2U_MoveState_ClearShellSideArm(u32 monId, b32 recordedToo);

/* The damage path's other call sites (damage.c): the thaw after the hits (Scorching Sands, Matcha Gotcha thaw as
 * Fire), CalcDamage's weather (W2U's EVENT_W2U_DAMAGE_WEATHER in sun) and its last event (VAR_DAMAGE for fixed damage
 * too), GetAttackPower's stat (EVENT_W2U_ATTACK_STAT_SELECTOR: Body Press) and a critical hit's (Defense as an
 * attacking stat), the per-hit Substitute test (sound moves and bypassing moves hit the Pokémon), and the target
 * counts of DamageRoot and the spread ratio (Dragon Darts). */
void W2U_ThawHitTargets(BtlServerFlow *flow, BtlFlowMoveParam *param, BattleMon *attacker, void *targets);
u8 W2U_DamageWeather(BtlServerFlow *flow);
void W2U_DispatchFinalMoveDamage(BtlServerFlow *flow, u32 event, u32 *damage);
u32 W2U_DispatchAttackStatSelector(BtlServerFlow *flow, u32 event, const BtlFlowMoveParam *param, u32 stat);
u32 W2U_CriticalAttackStat(BattleMon *mon, u32 stat);
b32 W2U_DamagingSubstitute(BattleMon *target, u16 move);
u32 W2U_MultiHitTargetCount(u16 move, u32 count, u32 countMax);
u32 W2U_SpreadTargetCount(u16 move, u32 countMax);
void W2U_SimpleDamageReaction(BtlServerFlow *flow, BattleMon *mon, u32 damage, u32 beforeHP);
u32 W2U_SimpleDamageBeforeHP(u32 monId);
/* A healing move's amount (damage.c), ServerEvent_CalcMoveHealAmount whole: EVENT_RECOVER_HP gets VAR_MOVE_ID too, and
 * Shore Up floors its exact share (2/3 in a sandstorm, else 1/2) */
u32 W2U_CalcMoveHealAmount(BtlServerFlow *flow, u16 move, BattleMon *mon);
b32 W2U_DamageToRecoverCheck(BtlServerFlow *flow, BattleMon *attacker, BattleMon *defender,
                              const BtlFlowMoveParam *param);
/* A move's parameters (damage.c), ServerEvent_GetMoveParam whole: VAR_MOVE_ID in the frame, mutable VAR_MOVE_TYPE, and
 * W2U's base / final parameter phases around EVENT_MOVE_PARAM (Terrain Pulse) */
void W2U_GetMoveParam(BtlServerFlow *flow, u16 move, BattleMon *mon, BtlFlowMoveParam *param);

/* Parental Bond (parental_bond.c): DamageRoot asks W2U_CheckMultihitHits instead of ServerEvent_CheckMultihitHits
 * (hitWork: W2U_HitWork); a single-target move of the holder becomes two hits. Its handlers ask W2U_ParentalBondActive
 * and count the hits (W2U_ParentalBondCountHit on EVENT_MOVE_POWER: 1, 2; W2U_ParentalBondHit: the count). */
void W2U_CheckMultihitHits(BtlServerFlow *flow, BattleMon *attacker, u16 move, void *hitWork);
b32 W2U_ParentalBondApplies(BtlServerFlow *flow, u16 move, BattleMon *attacker, void *targets);
b32 W2U_ParentalBondActive(void);
u32 W2U_ParentalBondCountHit(void);
u32 W2U_ParentalBondHit(void);

/* Type effectiveness (effectiveness.c): a Pokémon's added type (Forest's Curse, Trick-or-Treat) and Tar Shot, W2U's
 * grades beyond vanilla's (W2U_EFF_*), the per-type check with W2U's overrides, the per-move check (added type, Tar
 * Shot, Thousand Arrows), and the type check with the added type. GetTypeEffectivenessMultiplier,
 * TypeEffectivenessPowerMod, ServerEvent_CheckTypeEffectiveness, ServerControl_CheckMoveEffectiveness and
 * DoesMonHaveType (BattleMon_HasType) return these. */
void W2U_MoveState_SetExtraType(u32 monId, u32 type);
void W2U_MoveState_ClearExtraType(u32 monId);
u32 W2U_MoveState_GetExtraType(u32 monId);
b32 W2U_MoveState_ApplyTarShot(u32 monId);
b32 W2U_MoveState_HasTarShot(u32 monId);
void W2U_MoveState_ClearTarShot(u32 monId);
b32 W2U_HasType(BattleMon *mon, u32 type);
u32 W2U_ClassifyEffectiveness(s32 effectiveness);
void W2U_EffectivenessMessage(BtlServerFlow *flow, s32 effectiveness);
u32 W2U_DisplayEffectiveness(u32 effectiveness);
void W2U_SetEffectivenessVar(u32 key, s32 effectiveness);
void W2U_CountEffectiveness(u16 *counts, BtlServerFlow *flow, BattleMon *mon, BattleMon *target, s32 effectiveness);
void W2U_EffectivenessMessageMulti(BtlServerFlow *flow, u32 count, u32 *effectiveness, BattleMon **mons,
                                   b32 multipleTargets);
u32 W2U_EffectivenessMultiplier(u32 effectiveness1, u32 effectiveness2);
u32 W2U_EffectivenessPowerMod(u32 damage, u32 effectiveness);
u32 W2U_CheckTypeEffectiveness(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u32 moveType,
                               u32 defenseType);
u32 W2U_CheckMoveEffectiveness(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target,
                               const BtlFlowMoveParam *param, b32 message);
/* The trainer AI's grade (CalcMoveEffectiveness, instead of ServerControl_CheckMoveEffectiveness): its scripts test
 * the engine's grades only, so x1/8 reads as x1/4, x8 and x16 as x4. W2U_AIEffectiveness maps a grade so. */
u32 W2U_AIEffectiveness(u32 effectiveness);
u32 W2U_AIMoveEffectiveness(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, const BtlFlowMoveParam *param,
                            b32 message);

/* Clears the state above (the injection build, at battle exit; a decomp build's overlay 167 starts with it clear) */
void W2U_Resident_ResetBattleState(void);
void W2U_Resident_ResetPendingMoves(void);
void W2U_Resident_ResetHandlerEffects(void);
void W2U_Resident_ResetWeather(void);
void W2U_Resident_ResetMoveCategories(void);
void W2U_Resident_ResetParentalBond(void);
void W2U_Resident_ResetSimpleDamage(void);
void W2U_Resident_ResetEffectiveness(void);
void W2U_StrongWeather_Reset(void);

W2U_C_END

#endif
