/* Delta Stream, Primordial Sea, Desolate Land: the strong weathers' abilities (their state and server side:
 * resident/strong_weather.c, include/w2u/strong_weather.h). Entering, or gaining the ability, starts the holder's
 * kind; leaving, losing the ability or fainting ends it once no holder is left. While one is up, only its first holder
 * acts for the field:
 *  - strong winds: a move super effective on the Flying type is x1 against it (W2U_OVERRIDE_EFFECTIVENESS_1; W2U's
 *    C++ wrote 1, which W2U reads as x1/2, so the hit was resisted), with "The mysterious strong winds weakened the
 *    attack!" (not while the AI simulates);
 *  - heavy rain / harsh sun: a damaging Fire / Water move fails after "X used Y!" (fail cause 0x13, Damp's), with the
 *    kind's message. */
#include "w2u/battle_api.h"
#include "w2u/strong_weather.h"
#include "megab2w2/mb_ids.h"

#define STRONG_WEATHER_FAIL_CAUSE 0x13      /* Damp's: the fail display shows no retail text for it */

static void Start(BtlServerFlow *flow, u8 monId, u32 kind)
{
    if (W2U_Subject() == monId) {
        W2U_StrongWeather_Start(flow, monId, kind);
    }
}

static void HandlerStartWinds(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    Start(flow, monId, W2U_STRONG_WEATHER_WINDS);
}

static void HandlerStartRain(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    Start(flow, monId, W2U_STRONG_WEATHER_RAIN);
}

static void HandlerStartSun(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    Start(flow, monId, W2U_STRONG_WEATHER_SUN);
}

static void HandlerEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Subject() == monId) {
        W2U_StrongWeather_End(flow, monId);
    }
}

static void StdMessage(BtlServerFlow *flow, u8 monId, u16 message)
{
    BattleHandlerMessageParam *param =
        (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);

    BattleHandler_StrSetup(&param->string, HANDLER_STR_STD, message);
    BattleHandler_PopWork(flow, param);
}

/* Runs for every type check while a holder is out; only the first holder acts (the rule is field-wide) */
static void HandlerWindsEffectiveness(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (!W2U_StrongWeather_WindsActive() || monId != W2U_StrongWeather_FirstHolder(W2U_STRONG_WEATHER_WINDS)
        || BattleEventVar_GetValue(VAR_POKE_TYPE) != TYPE_FLYING
        || GetTypeEffectiveness((u8)W2U_MoveType(), TYPE_FLYING) != W2U_EFF_2 || W2U_StrongWeather_Negated(flow)) {
        return;
    }
    BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, W2U_OVERRIDE_EFFECTIVENESS_1);
    if (!W2U_IsSimulating(flow)) {
        StdMessage(flow, monId, W2U_STD_MSG_DELTA_STREAM_WEAKEN);
    }
}

static void FizzleCheck(BtlServerFlow *flow, u8 monId, s32 *work, u32 kind)
{
    u16 move;

    if (W2U_StrongWeather_Kind() != kind || monId != W2U_StrongWeather_FirstHolder(kind)
        || BattleEventVar_GetValue(VAR_FAIL_CAUSE) != 0) {
        return;
    }
    move = W2U_Move();
    if (W2U_IsStatusMove(move) || W2U_FinalMoveType(flow, move, W2U_Subject()) != W2U_StrongWeather_FizzleType(kind)
        || W2U_StrongWeather_Negated(flow)) {
        return;
    }
    work[0] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, STRONG_WEATHER_FAIL_CAUSE);
}

static void FizzleMessage(BtlServerFlow *flow, u8 monId, s32 *work, u16 message)
{
    if (!work[0]) {
        return;
    }
    work[0] = 0;
    StdMessage(flow, monId, message);
}

static void HandlerFizzleRain(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    FizzleCheck(flow, monId, work, W2U_STRONG_WEATHER_RAIN);
}

static void HandlerFizzleSun(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    FizzleCheck(flow, monId, work, W2U_STRONG_WEATHER_SUN);
}

static void HandlerFizzleMessageRain(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    FizzleMessage(flow, monId, work, W2U_STD_MSG_HEAVY_RAIN_FIZZLE);
}

static void HandlerFizzleMessageSun(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    FizzleMessage(flow, monId, work, W2U_STD_MSG_EXTREME_SUN_FIZZLE);
}

W2U_HANDLER_TABLE(DeltaStreamHandlers) = {
    { EVENT_SWITCH_IN, HandlerStartWinds },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerStartWinds },
    { EVENT_SWITCH_OUT_END, HandlerEnd },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerEnd },
    { EVENT_NOTIFY_FAINTED, HandlerEnd },
    { EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerWindsEffectiveness },
};
W2U_MECHANIC(ABILITY, ABIL_DELTA_STREAM, DeltaStreamHandlers);

W2U_HANDLER_TABLE(PrimordialSeaHandlers) = {
    { EVENT_SWITCH_IN, HandlerStartRain },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerStartRain },
    { EVENT_SWITCH_OUT_END, HandlerEnd },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerEnd },
    { EVENT_NOTIFY_FAINTED, HandlerEnd },
    { EVENT_DAMP_MOVE_CHECK, HandlerFizzleRain },
    { EVENT_DAMP_FAIL_MESSAGE, HandlerFizzleMessageRain },
};
W2U_MECHANIC(ABILITY, ABIL_PRIMORDIAL_SEA, PrimordialSeaHandlers);

W2U_HANDLER_TABLE(DesolateLandHandlers) = {
    { EVENT_SWITCH_IN, HandlerStartSun },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerStartSun },
    { EVENT_SWITCH_OUT_END, HandlerEnd },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerEnd },
    { EVENT_ABILITY_NULLIFIED, HandlerEnd },
    { EVENT_NOTIFY_FAINTED, HandlerEnd },
    { EVENT_DAMP_MOVE_CHECK, HandlerFizzleSun },
    { EVENT_DAMP_FAIL_MESSAGE, HandlerFizzleMessageSun },
};
W2U_MECHANIC(ABILITY, ABIL_DESOLATE_LAND, DesolateLandHandlers);
