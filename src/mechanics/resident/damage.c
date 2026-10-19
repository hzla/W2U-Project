/* The damage path's call sites (btl_server_flow.c) that W2U changes, other than the move category
 * (move_category.c):
 * - W2U_ThawHitTargets: the thaw after the hits; Scorching Sands and Matcha Gotcha thaw as a Fire move would (their
 *   damage, type and same-type bonus stay their own).
 * - W2U_DamageWeather: the weather of CalcDamage's weather modifier; in sun, W2U's EVENT_W2U_DAMAGE_WEATHER may change
 *   it (VAR_WEATHER).
 * - W2U_DispatchFinalMoveDamage: CalcDamage's last event (EVENT_MOVE_DAMAGE_PROCESSING_END), with VAR_DAMAGE set for
 *   fixed damage too; the damage is what the handlers leave.
 * - W2U_DispatchAttackStatSelector: GetAttackPower's first event, then W2U's EVENT_W2U_ATTACK_STAT_SELECTOR in its own
 *   scope (VAR_ATTACK_STAT_SELECTOR: Body Press attacks with Defense). W2U_CriticalAttackStat: the stat of a critical
 *   hit, where Defense is an attacking stat (drops ignored, boosts kept).
 * - W2U_DamagingSubstitute: the per-hit Substitute test; sound moves and moves that bypass it hit the Pokémon.
 * - W2U_MultiHitTargetCount, W2U_SpreadTargetCount: the target counts DamageRoot and the spread ratio use (Dragon
 *   Darts: one hit per target, never a spread move). */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define MOVE_DRAGON_DARTS 751           /* W2U's (Moves.h) */
#define MOVE_SCORCHING_SANDS 815
#define MOVE_MATCHA_GOTCHA 902

void W2U_ThawHitTargets(BtlServerFlow *flow, BtlFlowMoveParam *param, BattleMon *attacker, void *targets)
{
    if (param->move == MOVE_SCORCHING_SANDS || param->move == MOVE_MATCHA_GOTCHA) {
        BtlFlowMoveParam thaw = *param;
        thaw.type = TYPE_FIRE;
        ServerControl_ThawHitTargets(flow, &thaw, attacker, targets);
    } else {
        ServerControl_ThawHitTargets(flow, param, attacker, targets);
    }
}

u8 W2U_DamageWeather(BtlServerFlow *flow)
{
    u8 weather = ServerEvent_GetWeather(flow);
    if (weather != WEATHER_SUN) {
        return weather;
    }
    /* CalcDamage's scope (the move, its type, the attacker) gets VAR_WEATHER; CalcDamage pops it with the rest */
    BattleEventVar_SetValue(VAR_WEATHER, weather);
    BattleEvent_CallHandlers(flow, EVENT_W2U_DAMAGE_WEATHER);
    return (u8)BattleEventVar_GetValue(VAR_WEATHER);
}

void W2U_DispatchFinalMoveDamage(BtlServerFlow *flow, u32 event, u32 *damage)
{
    s32 existing;
    /* the normal path set VAR_DAMAGE already; fixed damage didn't */
    if (BtlEventVar_TryRead(VAR_DAMAGE, &existing)) {
        BattleEventVar_RewriteValue(VAR_DAMAGE, (s32)*damage);
    } else {
        BattleEventVar_SetValue(VAR_DAMAGE, (s32)*damage);
    }
    BattleEvent_CallHandlers(flow, event);
    *damage = BattleEventVar_GetValue(VAR_DAMAGE);
}

u32 W2U_DispatchAttackStatSelector(BtlServerFlow *flow, u32 event, const BtlFlowMoveParam *param, u32 stat)
{
    u32 result;
    BattleEvent_CallHandlers(flow, event);
    /* its own scope: Foul Play's and Unaware's variables stay for the rest of GetAttackPower */
    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetConstValue(VAR_MOVE_ID, param->move);
    BattleEventVar_SetValue(VAR_ATTACK_STAT_SELECTOR, (s32)stat);
    BattleEvent_CallHandlers(flow, EVENT_W2U_ATTACK_STAT_SELECTOR);
    result = BattleEventVar_GetValue(VAR_ATTACK_STAT_SELECTOR);
    BattleEventVar_Pop(__LINE__);
    return result;
}

u32 W2U_CriticalAttackStat(BattleMon *mon, u32 stat)
{
    if (stat != BMV_DEFENSE) {
        return (u32)CritAtkDefLevel(mon, stat);
    }
    /* CritAtkDefLevel reads Defense as a defending stat (boosts ignored); attacking with it, drops are */
    return GetBattleMonStat(mon, STATSTAGE_DEFENSE) < STATSTAGE_NEUTRAL ? (u32)RawBattleMonStat(mon, stat)
                                                                         : GetBattleMonStat(mon, stat);
}

b32 W2U_DamagingSubstitute(BattleMon *target, u16 move)
{
    if (getMoveFlag(move, MOVE_FLAG_INDEX_SOUND) || getMoveFlag(move, MOVE_FLAG_INDEX_BYPASS_SUBSTITUTE)) {
        return 0;
    }
    return IsSubstituteActive(target);
}

u32 W2U_MultiHitTargetCount(u16 move, u32 count, u32 countMax)
{
    return move == MOVE_DRAGON_DARTS ? count : countMax;
}

u32 W2U_SpreadTargetCount(u16 move, u32 countMax)
{
    return move == MOVE_DRAGON_DARTS ? 1 : countMax;
}
