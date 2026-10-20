/* Strong weathers' state and server side (was w2u_strong_weather.cpp's): see include/w2u/strong_weather.h.
 * - W2U_StrongWeatherBlocksChange: ServerControl_ChangeWeatherCheck asks it first; while a strong weather is up any
 *   other weather fails, with the kind's message;
 * - W2U_AICalcDamage: instead of ServerEvent_CalcDamage in AICalcDamage, the AI's damage estimate: with W2U's true
 *   effectiveness grade (CalcMoveEffectiveness gives the AI's, effectiveness.c), and a move the strong weather would
 *   make fizzle (W2U_StrongWeatherStopsMove) estimated as a hit that doesn't affect the target; its effectiveness
 *   grade is "no effect" too (effectiveness.c's W2U_AIMoveEffectiveness), so the scripts' penalty for that applies.
 *   W2U's C++ made the estimate 0, which the scripts take for a status move: the AI went on choosing the move. */
#include "w2u/resident.h"
#include "w2u/strong_weather.h"
#include "megab2w2/mb_ids.h"

#define SERVER_CMD_WEATHER_START 0x3F   /* (weather, turns): the view's start effect and text */
#define SERVER_CMD_WEATHER_END 0x40     /* (weather): the end text */
#define SERVER_CMD_POPUP_IN 0x57        /* (monId) */
#define SERVER_CMD_POPUP_OUT 0x58
#define TURNS_PERMANENT 0xFF

typedef struct StrongWeatherKind {
    u8 view;
    u8 engine;          /* the engine weather it keeps up (WEATHER_RAIN / WEATHER_SUN), none for strong winds */
    u8 fizzleType;
    u16 turnEffect;
    u16 msgStart;
    u16 msgBlock;
    u16 msgEnd;
} StrongWeatherKind;

static const StrongWeatherKind sKinds[W2U_STRONG_WEATHER_KIND_COUNT] = {
    { 0, WEATHER_NONE, W2U_STRONG_WEATHER_NO_TYPE, 0, 0, 0, 0 },
    { W2U_WEATHER_VIEW_STRONG_WINDS, WEATHER_NONE, W2U_STRONG_WEATHER_NO_TYPE, W2U_EFFECT_STRONG_WINDS,
      W2U_STD_MSG_DELTA_STREAM_START, W2U_STD_MSG_DELTA_STREAM_BLOCK, W2U_STD_MSG_DELTA_STREAM_END },
    { W2U_WEATHER_VIEW_HEAVY_RAIN, WEATHER_RAIN, TYPE_FIRE, W2U_EFFECT_HEAVY_RAIN_TURN,
      W2U_STD_MSG_HEAVY_RAIN_START, W2U_STD_MSG_HEAVY_RAIN_BLOCK, W2U_STD_MSG_HEAVY_RAIN_END },
    { W2U_WEATHER_VIEW_EXTREME_SUN, WEATHER_SUN, TYPE_WATER, W2U_EFFECT_EXTREME_SUN_TURN,
      W2U_STD_MSG_EXTREME_SUN_START, W2U_STD_MSG_EXTREME_SUN_BLOCK, W2U_STD_MSG_EXTREME_SUN_END },
};

static u8 sKind;
static u8 sShownView;
static u32 sHolders[W2U_STRONG_WEATHER_KIND_COUNT];   /* bit per monId: holders of that kind's ability */

u32 W2U_StrongWeather_Kind(void) { return sKind; }
b32 W2U_StrongWeather_WindsActive(void) { return sKind == W2U_STRONG_WEATHER_WINDS; }
u32 W2U_StrongWeather_ShownView(void) { return sShownView; }
void W2U_StrongWeather_SetShownView(u32 view) { sShownView = (u8)view; }

u32 W2U_StrongWeather_FizzleType(u32 kind)
{
    return kind < W2U_STRONG_WEATHER_KIND_COUNT ? sKinds[kind].fizzleType : W2U_STRONG_WEATHER_NO_TYPE;
}

u32 W2U_StrongWeather_TurnEffect(void) { return sKinds[sKind].turnEffect; }

void W2U_StrongWeather_Reset(void)
{
    u32 i;

    sKind = W2U_STRONG_WEATHER_NONE;
    sShownView = 0;
    for (i = 0; i < W2U_STRONG_WEATHER_KIND_COUNT; ++i) {
        sHolders[i] = 0;
    }
}

u32 W2U_StrongWeather_FirstHolder(u32 kind)
{
    u32 monId;

    if (kind == W2U_STRONG_WEATHER_NONE || kind >= W2U_STRONG_WEATHER_KIND_COUNT) {
        return 0;
    }
    for (monId = 0; monId < BATTLE_MAX_MON_ID; ++monId) {
        if (sHolders[kind] & (1u << monId)) {
            return monId;
        }
    }
    return 0;
}

b32 W2U_StrongWeather_Negated(BtlServerFlow *flow)
{
    s32 negated;

    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetRewriteOnceValue(VAR_WEATHER_NEGATED, 0);
    BattleEvent_CallHandlers(flow, EVENT_WEATHER_NEGATION);
    negated = (s32)BattleEventVar_GetValue(VAR_WEATHER_NEGATED);
    BattleEventVar_Pop(__LINE__);
    return negated != 0;
}

/* The start or end on the client: the injection build's view plays the kind's effect and text; a decomp build's
 * client is retail (its weather tables stop at sand), so there the text alone */
static void ShowStart(BtlServerFlow *flow, const StrongWeatherKind *kind)
{
#if defined(W2U_DECOMP)
    ServerDisplay_AddMessageImpl(W2U_ServerQueue(flow), SERVER_CMD_STD_MESSAGE, kind->msgStart, 0xFFFF0000);
#else
    ServerDisplay_AddCommon(W2U_ServerQueue(flow), SERVER_CMD_WEATHER_START, kind->view, TURNS_PERMANENT);
#endif
}

static void ShowEnd(BtlServerFlow *flow, const StrongWeatherKind *kind)
{
#if defined(W2U_DECOMP)
    ServerDisplay_AddMessageImpl(W2U_ServerQueue(flow), SERVER_CMD_STD_MESSAGE, kind->msgEnd, 0xFFFF0000);
#else
    ServerDisplay_AddCommon(W2U_ServerQueue(flow), SERVER_CMD_WEATHER_END, kind->view);
#endif
}

void W2U_StrongWeather_Start(BtlServerFlow *flow, u32 monId, u32 kind)
{
    u32 old, engine;

    if (!flow || W2U_IsSimulating(flow) || monId >= BATTLE_MAX_MON_ID || kind == W2U_STRONG_WEATHER_NONE
        || kind >= W2U_STRONG_WEATHER_KIND_COUNT) {
        return;
    }
    sHolders[kind] |= 1u << monId;
    if (sKind == kind) {
        return;   /* already up (another holder) */
    }
    /* Any weather is replaced without its end text (Gen 6+). Not the native change routine: it would show the engine
     * weather's own start */
    old = GetFieldWeather();
    engine = sKinds[kind].engine;
    FieldStatusSetWeather(engine, engine != WEATHER_NONE ? TURNS_PERMANENT : 0);
    sKind = (u8)kind;
    ServerDisplay_AddCommon(W2U_ServerQueue(flow), SERVER_CMD_POPUP_IN, monId);
    ShowStart(flow, &sKinds[kind]);
    ServerDisplay_AddCommon(W2U_ServerQueue(flow), SERVER_CMD_POPUP_OUT, monId);
    if (old != engine) {
        ServerControl_ChangeWeatherAfter(flow, engine);   /* Forecast, Flower Gift ... */
    }
}

void W2U_StrongWeather_End(BtlServerFlow *flow, u32 monId)
{
    u32 kind, engine;

    if (!flow || W2U_IsSimulating(flow) || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    for (kind = 1; kind < W2U_STRONG_WEATHER_KIND_COUNT; ++kind) {
        if (!(sHolders[kind] & (1u << monId))) {
            continue;
        }
        sHolders[kind] &= ~(1u << monId);
        if (kind != sKind || sHolders[kind]) {
            continue;
        }
        engine = sKinds[kind].engine;
        if (engine != WEATHER_NONE && GetFieldWeather() == engine) {
            FieldStatusSetWeather(WEATHER_NONE, 0);
        }
        sKind = W2U_STRONG_WEATHER_NONE;
        ShowEnd(flow, &sKinds[kind]);
        if (engine != WEATHER_NONE) {
            ServerControl_ChangeWeatherAfter(flow, WEATHER_NONE);
        }
    }
}

b32 W2U_StrongWeatherBlocksChange(BtlServerFlow *flow, u32 weather)
{
    BattleHandlerMessageParam *param;

    if (sKind == W2U_STRONG_WEATHER_NONE || weather == WEATHER_NONE) {
        return 0;
    }
    param = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE,
                                                                W2U_StrongWeather_FirstHolder(sKind));
    BattleHandler_StrSetup(&param->string, HANDLER_STR_STD, sKinds[sKind].msgBlock);
    BattleHandler_PopWork(flow, param);
    return 1;
}

b32 W2U_StrongWeatherStopsMove(BtlServerFlow *flow, const BtlFlowMoveParam *param)
{
    return sKind != W2U_STRONG_WEATHER_NONE && sKinds[sKind].fizzleType == param->type && !W2U_IsStatusMove(param->move)
           && !W2U_StrongWeather_Negated(flow);
}

b32 W2U_AICalcDamage(BtlServerFlow *flow, BattleMon *attacker, BattleMon *defender, const BtlFlowMoveParam *param,
                     u32 effectiveness, u32 ratio, b32 critical, b32 fixedRoll, u16 *damage)
{
    /* A move the strong weather stops is estimated as a hit that doesn't affect the target. Not as 0: the scripts take
     * an estimate of 0 for a move that deals no damage (a status move) and skip their "doesn't affect" penalty */
    if (W2U_StrongWeatherStopsMove(flow, param)) {
        effectiveness = W2U_EFF_IMMUNE;
    } else if (effectiveness == W2U_EFF_1_4 || effectiveness == W2U_EFF_4) {
        /* CalcMoveEffectiveness gave the AI's grade (W2U_AIMoveEffectiveness): the damage takes the true one */
        u32 grade = W2U_CheckMoveEffectiveness(flow, attacker, defender, param, 0);

        if (W2U_AIEffectiveness(grade) == effectiveness) {
            effectiveness = grade;
        }
    }
    return ServerEvent_CalcDamage(flow, attacker, defender, param, effectiveness, ratio, critical, fixedRoll, damage);
}
