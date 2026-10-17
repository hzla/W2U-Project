/* Electromorphosis, Wind Power (Gen 9): the holder becomes charged, and its next Electric move has double power (Gen 9
 * Charge: it lasts until the holder uses an Electric move or leaves).
 *   Electromorphosis  hit by any damaging move
 *   Wind Power        hit by a damaging wind move, or Tailwind starting on its side
 * The charge is this file's own state (the engine's Charge condition is Gen 5's one-turn version), shown with the
 * Charge move's "X began charging power!" inside the holder's popup. It ends after an Electric move and when the
 * holder enters (it left meanwhile). MegaB2W2's Charge_ResetForBattle, a reset at the battle's start, was never
 * called in W2U and is gone: the state lives as long as the module. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MSG_SET_CHARGE_BEGAN 664        /* bank 18: "{0} began charging power!" */
#define MOVE_TAILWIND 366

static b32 sChargeCharged[BATTLE_MAX_MON_ID];

static void ChargeUp(BtlServerFlow *flow, u8 monId)
{
    sChargeCharged[monId] = 1;
    W2U_PopupMessage(flow, monId, MSG_SET_CHARGE_BEGAN);
}

static void HandlerChargeHit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Defender() != monId || monId >= BATTLE_MAX_MON_ID || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT)) {
        return;
    }
    if (W2U_IsFainted(flow, monId)) {
        return;
    }
    if (W2U_HolderAbility(flow, monId) == ABIL_WIND_POWER && !W2U_MoveHasFlag(W2U_Move(), MOVE_FLAG_INDEX_WIND)) {
        return;
    }
    ChargeUp(flow, monId);
}

/* Tailwind starting on its side: noted when the move starts (work[0]), checked when it ends, after its messages */
static void HandlerChargeTailwindStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    work[0] = IsSideEffectSet(GetSideFromMonID(monId), SIDE_EFFECT_TAILWIND);
}

static void HandlerChargeTailwind(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    if (monId >= BATTLE_MAX_MON_ID || W2U_Move() != MOVE_TAILWIND || work[0]) {
        return;
    }
    if (W2U_HolderAbility(flow, monId) != ABIL_WIND_POWER || !W2U_IsAlly(monId, W2U_Attacker())) {
        return;
    }
    if (IsSideEffectSet(GetSideFromMonID(monId), SIDE_EFFECT_TAILWIND)) {
        ChargeUp(flow, monId);
    }
}

static void HandlerChargePower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID || !sChargeCharged[monId]) {
        return;
    }
    if (W2U_MoveType() == TYPE_ELECTRIC) {
        W2U_MulMovePower(8192);         /* x2 */
    }
}

static void HandlerChargeMoveEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    HandlerChargeTailwind(item, flow, monId, work);
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID || !sChargeCharged[monId]) {
        return;
    }
    if (W2U_FinalMoveType(flow, W2U_Move(), monId) == TYPE_ELECTRIC) {
        sChargeCharged[monId] = 0;
    }
}

static void HandlerChargeSwitchIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() == monId && monId < BATTLE_MAX_MON_ID) {
        sChargeCharged[monId] = 0;
    }
}

W2U_HANDLER_TABLE(ChargeHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerChargeHit },
    { EVENT_MOVE_START, HandlerChargeTailwindStart },
    { EVENT_MOVE_POWER, HandlerChargePower },
    { EVENT_MOVE_END, HandlerChargeMoveEnd },
    { EVENT_SWITCH_IN, HandlerChargeSwitchIn },
};
W2U_MECHANIC(ABILITY, ABIL_WIND_POWER, ChargeHandlers);
W2U_MECHANIC(ABILITY, ABIL_ELECTROMORPHOSIS, ChargeHandlers);
