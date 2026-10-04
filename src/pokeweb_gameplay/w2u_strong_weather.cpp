// Strong weathers (Delta Stream, Primordial Sea, Desolate Land). Ported from MegaB2W2; see
// include/w2u_strong_weather.h for the rules.
//
// Built twice: into the resident core (state, accessors, hooks; !W2U_BATTLE_CHILD) and into the
// abilities/strong_weather battle module (the three ability handler tables; W2U_BATTLE_CHILD), which reaches the
// state only through the exported W2U_StrongWeather_* functions.
#include "w2u_abilities.h"
#include "w2u_battle.h"
#include "w2u_strong_weather.h"

#define W2U_STRONG_WEATHER_CALL(type, address) ((type)(address))

#if defined(W2U_TARGET_B2)
// Not mapped for Black 2 (see the header): the tables exist for the static module resolver and do nothing.
extern "C" void HandlerStrongWeatherUnmapped(BattleEventItem*, ServerFlow*, u32, u32*) {}
BattleEventHandlerTableEntry DeltaStreamHandlers[W2U_DELTA_STREAM_HANDLER_COUNT] = {
    {EVENT_SWITCH_IN, HandlerStrongWeatherUnmapped}};
BattleEventHandlerTableEntry PrimordialSeaHandlers[W2U_PRIMORDIAL_SEA_HANDLER_COUNT] = {
    {EVENT_SWITCH_IN, HandlerStrongWeatherUnmapped}};
BattleEventHandlerTableEntry DesolateLandHandlers[W2U_DESOLATE_LAND_HANDLER_COUNT] = {
    {EVENT_SWITCH_IN, HandlerStrongWeatherUnmapped}};
#else

namespace {

const u32 SCID_WEATHER_START = 0x3F;      // (weather, turns): view plays the start effect, then the text
const u32 SCID_WEATHER_END = 0x40;        // (weather): view shows the end text
const u32 SCID_FIELD_EFFECT = 0x4C;       // (effect)
const u32 SCID_ABILITY_POPUP_IN = 0x57;   // (pokemonSlot)
const u32 SCID_ABILITY_POPUP_OUT = 0x58;  // (pokemonSlot)
const u32 TURNS_PERMANENT = 0xFF;
const u32 STRTYPE_STD = 1;
const u32 NO_TYPE = 0xFF;
const u32 ENGINE_SUN = 1;
const u32 ENGINE_RAIN = 2;
// Move-execution check (ov167 0x21A3DB0): EVENT_MOVE_EXECUTE_CHECK2 sets a fail cause in VAR_FAIL_CAUSE; any cause
// fails the move after its "used" message and raises EVENT_MOVE_EXECUTE_FAIL for the message. 0x13 is Damp's
// cause, which the fail display shows without a retail text.
const u32 FAIL_CAUSE_ABILITY = 0x13;
// During EVENT_WEATHER_CHECK (0x7A) variable 0x41 is "weather negated" (Air Lock / Cloud Nine set it).
const BattleEventVar VAR_WEATHER_NEGATED = (BattleEventVar)0x41;
// During EVENT_CHECK_TYPE_EFFECTIVENESS variable 0x4C forces a neutral result when set to 1.
const BattleEventVar VAR_FORCE_NEUTRAL = (BattleEventVar)0x4C;
const u32 EFFECTIVENESS_DOUBLE = 4;       // GetTypeEffectiveness: 0 immune ... 3 neutral, 4 x2, 5 x4

struct KindInfo {
    u32 view;
    u32 engine;
    u32 turnEffect;
    u16 msgBlock;
    u16 msgFizzle;
    u32 fizzleType;
};

const KindInfo kKinds[W2U_STRONG_WEATHER_KIND_COUNT] = {
    {0, 0, 0, 0, 0, NO_TYPE},
    {W2U_WEATHER_VIEW_STRONG_WINDS, 0, W2U_EFFECT_STRONG_WINDS, W2U_STD_MSG_DELTA_STREAM_BLOCK, 0, NO_TYPE},
    {W2U_WEATHER_VIEW_HEAVY_RAIN, ENGINE_RAIN, W2U_EFFECT_HEAVY_RAIN_TURN, W2U_STD_MSG_HEAVY_RAIN_BLOCK,
     W2U_STD_MSG_HEAVY_RAIN_FIZZLE, TYPE_FIRE},
    {W2U_WEATHER_VIEW_EXTREME_SUN, ENGINE_SUN, W2U_EFFECT_EXTREME_SUN_TURN, W2U_STD_MSG_EXTREME_SUN_BLOCK,
     W2U_STD_MSG_EXTREME_SUN_FIZZLE, TYPE_WATER},
};

void PushStdMessage(ServerFlow* serverFlow, u32 pokemonSlot, u32 msgID)
{
    HandlerParam_Message* message =
        (HandlerParam_Message*)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
    BattleHandler_StrSetup(&message->str, STRTYPE_STD, msgID);
    BattleHandler_PopWork(serverFlow, message);
}

} // namespace

#if !defined(W2U_BATTLE_CHILD)

extern "C" BattleMon* Handler_GetBattleMon(ServerFlow* serverFlow, u32 pokemonSlot);
extern "C" u32 ServerEvent_CalcDamage(ServerFlow* serverFlow, BattleMon* attacker, BattleMon* defender,
    MoveParam* moveParam, u32 typeEffectiveness, u32 targetRatio, u32 critical, u32 debugMode, u16* damage);

namespace {

typedef u32 (*FieldGetFn)();
typedef void (*FieldSetWeatherFn)(u32 weather, u32 turns);
typedef void (*ChangeAfterFn)(ServerFlow* serverFlow, u32 weather);
typedef b32 (*TurnCheckFn)(ServerFlow* serverFlow, void* pokeSet);
typedef void (*ClientSetFn)(void* field, u32 weather, u32 turns);
typedef void (*ClientClearFn)(void* field);
typedef b32 (*SkipEffectsFn)(void* client);
typedef void (*StdMessageFn)(void* view, u32 msgID, const void* args);
typedef b32 (*WaitMessageFn)(void* view);
typedef void (*EffectStartFn)(u32 effect);
typedef b32 (*EffectBusyFn)();

struct WeatherViewEntry {
    u16 stdMsg;
    u16 effect;
};

u32 FieldWeather() { return W2U_STRONG_WEATHER_CALL(FieldGetFn, W2U_ADDR_STRONG_WEATHER_FIELD_GET_WEATHER)(); }
u32 FieldWeatherTurns() { return W2U_STRONG_WEATHER_CALL(FieldGetFn, W2U_ADDR_STRONG_WEATHER_FIELD_GET_TURNS)(); }
void FieldSetWeather(u32 weather, u32 turns)
{
    W2U_STRONG_WEATHER_CALL(FieldSetWeatherFn, W2U_ADDR_STRONG_WEATHER_FIELD_SET_WEATHER)(weather, turns);
}
void ChangeWeatherAfter(ServerFlow* serverFlow, u32 weather)
{
    W2U_STRONG_WEATHER_CALL(ChangeAfterFn, W2U_ADDR_STRONG_WEATHER_CHANGE_AFTER)(serverFlow, weather);
}

struct StrongWeatherState {
    u32 kind;                                  // the active strong weather
    u32 holders[W2U_STRONG_WEATHER_KIND_COUNT]; // bit per battle slot: holders of that kind's ability
    u32 shownView;                             // view side: the strong weather on screen (0 = none)
};
StrongWeatherState sState;

} // namespace

extern "C" u32 W2U_StrongWeather_Kind() { return sState.kind; }
extern "C" bool W2U_StrongWeather_WindsActive() { return sState.kind == W2U_STRONG_WEATHER_WINDS; }
extern "C" u32 W2U_StrongWeather_ShownView() { return sState.shownView; }
extern "C" u32 W2U_StrongWeather_FizzleType(u32 kind)
{
    return kind < W2U_STRONG_WEATHER_KIND_COUNT ? kKinds[kind].fizzleType : NO_TYPE;
}

extern "C" void W2U_StrongWeather_Reset()
{
    sState.kind = W2U_STRONG_WEATHER_NONE;
    for (u32 i = 0; i < W2U_STRONG_WEATHER_KIND_COUNT; ++i) {
        sState.holders[i] = 0;
    }
    sState.shownView = 0;
}

extern "C" u32 W2U_StrongWeather_FirstHolder(u32 kind)
{
    for (u32 slot = 0; slot < 32; ++slot) {   // no __builtin_ctz: it needs a libgcc helper the game lacks
        if (sState.holders[kind] & (1u << slot)) {
            return slot;
        }
    }
    return 0;
}

extern "C" bool W2U_StrongWeather_Negated(void* serverFlow)
{
    BattleEventVar_Push();
    BattleEventVar_SetRewriteOnceValue(VAR_WEATHER_NEGATED, 0);
    BattleEvent_CallHandlers((ServerFlow*)serverFlow, EVENT_WEATHER_CHECK);
    int negated = BattleEventVar_GetValue(VAR_WEATHER_NEGATED);
    BattleEventVar_Pop();
    return negated != 0;
}

extern "C" void W2U_StrongWeather_Start(void* flow, u32 pokemonSlot, u32 kind)
{
    ServerFlow* serverFlow = (ServerFlow*)flow;
    if (kind == W2U_STRONG_WEATHER_NONE || kind >= W2U_STRONG_WEATHER_KIND_COUNT) {
        return;
    }
    sState.holders[kind] |= 1u << pokemonSlot;
    if (sState.kind == kind) {
        return;   // already up (another holder)
    }
    // Any weather is replaced without its end text (Gen 6+). Not the native change routine: it would send 0x3F
    // with the engine weather, which the view plays as a retail weather start.
    u32 old = FieldWeather();
    u32 engine = kKinds[kind].engine;
    FieldSetWeather(engine, engine ? TURNS_PERMANENT : 0);
    sState.kind = kind;
    ServerDisplay_AddCommon(serverFlow->serverCommandQueue, (ServerCommandID)SCID_ABILITY_POPUP_IN, pokemonSlot);
    ServerDisplay_AddCommon(serverFlow->serverCommandQueue, (ServerCommandID)SCID_WEATHER_START,
        kKinds[kind].view, TURNS_PERMANENT);
    ServerDisplay_AddCommon(serverFlow->serverCommandQueue, (ServerCommandID)SCID_ABILITY_POPUP_OUT, pokemonSlot);
    if (old != engine) {
        ChangeWeatherAfter(serverFlow, engine);   // Forecast, Flower Gift ...
    }
}

extern "C" void W2U_StrongWeather_End(void* flow, u32 pokemonSlot)
{
    ServerFlow* serverFlow = (ServerFlow*)flow;
    for (u32 kind = 1; kind < W2U_STRONG_WEATHER_KIND_COUNT; ++kind) {
        if (!(sState.holders[kind] & (1u << pokemonSlot))) {
            continue;
        }
        sState.holders[kind] &= ~(1u << pokemonSlot);
        if (kind != sState.kind || sState.holders[kind]) {
            continue;
        }
        u32 engine = kKinds[kind].engine;
        if (engine && FieldWeather() == engine) {
            FieldSetWeather(0, 0);
        }
        sState.kind = W2U_STRONG_WEATHER_NONE;
        ServerDisplay_AddCommon(serverFlow->serverCommandQueue, (ServerCommandID)SCID_WEATHER_END, kKinds[kind].view);
        if (engine) {
            ChangeWeatherAfter(serverFlow, 0);
        }
    }
}

// ---- resident hooks (White 2) ------------------------------------------------------------------------------

// ServerControl_ChangeWeatherCheck (ov167 0x21A767C), re-implemented 1:1 plus the strong-weather block. Every
// weather setter (moves, Drizzle, Sand Stream ...) asks this first.
extern "C" b32 THUMB_BRANCH_167_0x21A767C(ServerFlow* serverFlow, u32 weather, u32 turns)
{
    if (weather > 4) {
        return 0;
    }
    if (sState.kind != W2U_STRONG_WEATHER_NONE && weather != 0) {
        PushStdMessage(serverFlow, W2U_StrongWeather_FirstHolder(sState.kind), kKinds[sState.kind].msgBlock);
        return 0;
    }
    if (weather == FieldWeather() && (turns != TURNS_PERMANENT || FieldWeatherTurns() == TURNS_PERMANENT)) {
        return 0;
    }
    return 1;
}

// Turn end: the turn-check sequence calls ServerControl_TurnCheckWeather at ov167 0x21A7FBA. A strong weather's
// turn effect plays first; heavy rain / harsh sun keep their engine weather with permanent turns, so the native
// routine still runs their per-Pokemon effects (Rain Dish, Dry Skin, Solar Power ...) without counting down.
extern "C" b32 THUMB_BRANCH_LINK_167_0x21A7FBA(ServerFlow* serverFlow, void* pokeSet)
{
    if (sState.kind != W2U_STRONG_WEATHER_NONE) {
        ServerDisplay_AddCommon(serverFlow->serverCommandQueue, (ServerCommandID)SCID_FIELD_EFFECT,
            kKinds[sState.kind].turnEffect);
    }
    return W2U_STRONG_WEATHER_CALL(TurnCheckFn, W2U_ADDR_STRONG_WEATHER_TURN_CHECK)(serverFlow, pokeSet);
}

// The AI's damage simulation (ov167 0x21AB994) calls ServerEvent_CalcDamage at 0x21ABA24 with the final move
// parameters: a move that would fizzle is worth 0, so the AI stops choosing it.
extern "C" u32 THUMB_BRANCH_LINK_167_0x21ABA24(ServerFlow* serverFlow, BattleMon* attacker, BattleMon* defender,
    MoveParam* moveParam, u32 typeEffectiveness, u32 targetRatio, u32 critical, u32 debugMode, u16* damage)
{
    u32 result = ServerEvent_CalcDamage(serverFlow, attacker, defender, moveParam, typeEffectiveness, targetRatio,
        critical, debugMode, damage);
    if (sState.kind != W2U_STRONG_WEATHER_NONE && kKinds[sState.kind].fizzleType == moveParam->moveType &&
        !W2U_StrongWeather_Negated(serverFlow)) {
        *damage = 0;
    }
    return result;
}

// ---- view side: display commands 0x3F / 0x40 ---------------------------------------------------------------
// Retail 0x3F (ov167 0x21B78AC): store (weather, turns) in the client's field copy (client+0x34), unless effects
// are skipped play WEATHER_VIEW_TABLE[w].effect, wait, show its std text, wait. 0x40 (0x21B792C): end text,
// wait, clear the copy. The copy is read with retail 5-entry tables, so it only holds retail weathers: strong
// winds clear it, heavy rain / harsh sun store rain / sun.

namespace {

const u32 RETAIL_WEATHERS = 5;
const u16 kWeatherEndMsg[RETAIL_WEATHERS] = {0, 0x59, 0x5A, 0x5C, 0x5B};

struct StrongView {
    u32 view;
    u32 clientWeather;
    u32 effect;
    u16 msgStart;
    u16 msgEnd;
};

const StrongView kStrongViews[] = {
    {W2U_WEATHER_VIEW_STRONG_WINDS, 0, W2U_EFFECT_STRONG_WINDS,
     W2U_STD_MSG_DELTA_STREAM_START, W2U_STD_MSG_DELTA_STREAM_END},
    {W2U_WEATHER_VIEW_HEAVY_RAIN, ENGINE_RAIN, W2U_EFFECT_HEAVY_RAIN,
     W2U_STD_MSG_HEAVY_RAIN_START, W2U_STD_MSG_HEAVY_RAIN_END},
    {W2U_WEATHER_VIEW_EXTREME_SUN, ENGINE_SUN, W2U_EFFECT_EXTREME_SUN,
     W2U_STD_MSG_EXTREME_SUN_START, W2U_STD_MSG_EXTREME_SUN_END},
};

const StrongView* FindStrongView(u32 view)
{
    for (u32 i = 0; i < sizeof(kStrongViews) / sizeof(kStrongViews[0]); ++i) {
        if (kStrongViews[i].view == view) {
            return &kStrongViews[i];
        }
    }
    return 0;
}

void* ClientField(void* client) { return *(void**)((u8*)client + 0x34); }
void* ClientView(void* client) { return *(void**)((u8*)client + 0x54); }
const WeatherViewEntry* RetailViewTable() { return (const WeatherViewEntry*)W2U_ADDR_STRONG_WEATHER_VIEW_TABLE; }

} // namespace

extern "C" b32 THUMB_BRANCH_167_0x21B78AC(void* client, int* sequence, const u32* args)
{
    u32 weather = args[0] & 0xFF;
    const StrongView* strong = FindStrongView(weather);
    switch (*sequence) {
    case 0:
        if (strong) {
            if (strong->clientWeather) {
                W2U_STRONG_WEATHER_CALL(ClientSetFn, W2U_ADDR_STRONG_WEATHER_CLIENT_SET)(
                    ClientField(client), strong->clientWeather, TURNS_PERMANENT);
            } else {
                W2U_STRONG_WEATHER_CALL(ClientClearFn, W2U_ADDR_STRONG_WEATHER_CLIENT_CLEAR)(ClientField(client));
            }
            sState.shownView = strong->view;
        } else {
            W2U_STRONG_WEATHER_CALL(ClientSetFn, W2U_ADDR_STRONG_WEATHER_CLIENT_SET)(
                ClientField(client), weather, args[1] & 0xFFFF);
            sState.shownView = 0;
        }
        if (W2U_STRONG_WEATHER_CALL(SkipEffectsFn, W2U_ADDR_STRONG_WEATHER_SKIP_EFFECTS)(client)) {
            return 1;
        }
        if (strong) {
            W2U_STRONG_WEATHER_CALL(EffectStartFn, W2U_ADDR_STRONG_WEATHER_EFFECT_START)(strong->effect);
        } else if (weather < RETAIL_WEATHERS) {
            W2U_STRONG_WEATHER_CALL(EffectStartFn, W2U_ADDR_STRONG_WEATHER_EFFECT_START)(
                RetailViewTable()[weather].effect);
        }
        break;
    case 1:
        if (W2U_STRONG_WEATHER_CALL(EffectBusyFn, W2U_ADDR_STRONG_WEATHER_EFFECT_BUSY)()) {
            return 0;
        }
        W2U_STRONG_WEATHER_CALL(StdMessageFn, W2U_ADDR_STRONG_WEATHER_STD_MESSAGE)(
            ClientView(client), strong ? strong->msgStart : RetailViewTable()[weather].stdMsg, 0);
        break;
    case 2:
        return W2U_STRONG_WEATHER_CALL(WaitMessageFn, W2U_ADDR_STRONG_WEATHER_WAIT_MESSAGE)(ClientView(client)) ? 1 : 0;
    default:
        return 0;
    }
    ++*sequence;
    return 0;
}

extern "C" b32 THUMB_BRANCH_167_0x21B792C(void* client, int* sequence, const u32* args)
{
    u32 weather = args[0] & 0xFF;
    const StrongView* strong = FindStrongView(weather);
    if (*sequence == 0) {
        if (!strong && (weather == 0 || weather >= RETAIL_WEATHERS)) {
            return 1;
        }
        W2U_STRONG_WEATHER_CALL(StdMessageFn, W2U_ADDR_STRONG_WEATHER_STD_MESSAGE)(
            ClientView(client), strong ? strong->msgEnd : kWeatherEndMsg[weather], 0);
        ++*sequence;
    } else if (*sequence == 1 &&
               W2U_STRONG_WEATHER_CALL(WaitMessageFn, W2U_ADDR_STRONG_WEATHER_WAIT_MESSAGE)(ClientView(client))) {
        if (strong) {
            sState.shownView = 0;
        }
        W2U_STRONG_WEATHER_CALL(ClientClearFn, W2U_ADDR_STRONG_WEATHER_CLIENT_CLEAR)(ClientField(client));
        return 1;
    }
    return 0;
}

#endif // !W2U_BATTLE_CHILD

// ---- ability handlers (abilities/strong_weather battle module) ---------------------------------------------

namespace {

bool IsSelf(u32 pokemonSlot) { return (u32)BattleEventVar_GetValue(VAR_MON_ID) == pokemonSlot; }

void FizzleCheck(ServerFlow* serverFlow, u32 pokemonSlot, u32* work, u32 kind)
{
    if (W2U_StrongWeather_Kind() != kind || pokemonSlot != W2U_StrongWeather_FirstHolder(kind)) {
        return;
    }
    if (BattleEventVar_GetValue(VAR_FAIL_CAUSE) != 0) {
        return;
    }
    MOVE_ID moveID = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    if (!PML_MoveIsDamaging(moveID)) {
        return;
    }
    u32 attacker = (u32)BattleEventVar_GetValue(VAR_MON_ID);
    MoveParam param = {};
    W2U_ServerEvent_GetMoveParam(serverFlow, moveID, Handler_GetBattleMon(serverFlow, attacker), &param);
    if (param.moveType != W2U_StrongWeather_FizzleType(kind) || W2U_StrongWeather_Negated(serverFlow)) {
        return;
    }
    work[0] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, FAIL_CAUSE_ABILITY);
}

void FizzleMessage(ServerFlow* serverFlow, u32 pokemonSlot, u32* work, u32 msgID)
{
    if (!work[0]) {
        return;
    }
    work[0] = 0;
    PushStdMessage(serverFlow, pokemonSlot, msgID);
}

} // namespace

extern "C" void HandlerStrongWeatherStartWinds(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (IsSelf(pokemonSlot)) W2U_StrongWeather_Start(serverFlow, pokemonSlot, W2U_STRONG_WEATHER_WINDS);
}
extern "C" void HandlerStrongWeatherStartRain(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (IsSelf(pokemonSlot)) W2U_StrongWeather_Start(serverFlow, pokemonSlot, W2U_STRONG_WEATHER_RAIN);
}
extern "C" void HandlerStrongWeatherStartSun(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (IsSelf(pokemonSlot)) W2U_StrongWeather_Start(serverFlow, pokemonSlot, W2U_STRONG_WEATHER_SUN);
}
extern "C" void HandlerStrongWeatherEnd(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (IsSelf(pokemonSlot)) W2U_StrongWeather_End(serverFlow, pokemonSlot);
}

// Runs for every attack while a holder is out; only the first holder acts (the rule is field-wide).
extern "C" void HandlerStrongWeatherWindsEffectiveness(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32*)
{
    if (!W2U_StrongWeather_WindsActive() || pokemonSlot != W2U_StrongWeather_FirstHolder(W2U_STRONG_WEATHER_WINDS)) {
        return;
    }
    if ((u32)BattleEventVar_GetValue(VAR_POKE_TYPE) != TYPE_FLYING) {
        return;
    }
    if (GetTypeEffectiveness(BattleEventVar_GetValue(VAR_MOVE_TYPE), TYPE_FLYING) != EFFECTIVENESS_DOUBLE) {
        return;
    }
    if (W2U_StrongWeather_Negated(serverFlow)) {
        return;
    }
    BattleEventVar_RewriteValue(VAR_FORCE_NEUTRAL, 1);
    PushStdMessage(serverFlow, pokemonSlot, W2U_STD_MSG_DELTA_STREAM_WEAKEN);
}

extern "C" void HandlerStrongWeatherFizzleRain(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    FizzleCheck(serverFlow, pokemonSlot, work, W2U_STRONG_WEATHER_RAIN);
}
extern "C" void HandlerStrongWeatherFizzleSun(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    FizzleCheck(serverFlow, pokemonSlot, work, W2U_STRONG_WEATHER_SUN);
}
extern "C" void HandlerStrongWeatherFizzleMsgRain(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    FizzleMessage(serverFlow, pokemonSlot, work, W2U_STD_MSG_HEAVY_RAIN_FIZZLE);
}
extern "C" void HandlerStrongWeatherFizzleMsgSun(BattleEventItem*, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    FizzleMessage(serverFlow, pokemonSlot, work, W2U_STD_MSG_EXTREME_SUN_FIZZLE);
}

BattleEventHandlerTableEntry DeltaStreamHandlers[W2U_DELTA_STREAM_HANDLER_COUNT] = {
    {EVENT_SWITCH_IN, HandlerStrongWeatherStartWinds},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerStrongWeatherStartWinds},
    {EVENT_SWITCH_OUT_END, HandlerStrongWeatherEnd},
    {EVENT_BEFORE_ABILITY_CHANGE, HandlerStrongWeatherEnd},
    {EVENT_ABILITY_NULLIFIED, HandlerStrongWeatherEnd},
    {EVENT_NOTIFY_FAINTED, HandlerStrongWeatherEnd},
    {EVENT_CHECK_TYPE_EFFECTIVENESS, HandlerStrongWeatherWindsEffectiveness},
};

BattleEventHandlerTableEntry PrimordialSeaHandlers[W2U_PRIMORDIAL_SEA_HANDLER_COUNT] = {
    {EVENT_SWITCH_IN, HandlerStrongWeatherStartRain},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerStrongWeatherStartRain},
    {EVENT_SWITCH_OUT_END, HandlerStrongWeatherEnd},
    {EVENT_BEFORE_ABILITY_CHANGE, HandlerStrongWeatherEnd},
    {EVENT_ABILITY_NULLIFIED, HandlerStrongWeatherEnd},
    {EVENT_NOTIFY_FAINTED, HandlerStrongWeatherEnd},
    {EVENT_MOVE_EXECUTE_CHECK2, HandlerStrongWeatherFizzleRain},
    {EVENT_MOVE_EXECUTE_FAIL, HandlerStrongWeatherFizzleMsgRain},
};

BattleEventHandlerTableEntry DesolateLandHandlers[W2U_DESOLATE_LAND_HANDLER_COUNT] = {
    {EVENT_SWITCH_IN, HandlerStrongWeatherStartSun},
    {EVENT_AFTER_ABILITY_CHANGE, HandlerStrongWeatherStartSun},
    {EVENT_SWITCH_OUT_END, HandlerStrongWeatherEnd},
    {EVENT_BEFORE_ABILITY_CHANGE, HandlerStrongWeatherEnd},
    {EVENT_ABILITY_NULLIFIED, HandlerStrongWeatherEnd},
    {EVENT_NOTIFY_FAINTED, HandlerStrongWeatherEnd},
    {EVENT_MOVE_EXECUTE_CHECK2, HandlerStrongWeatherFizzleSun},
    {EVENT_MOVE_EXECUTE_FAIL, HandlerStrongWeatherFizzleMsgSun},
};

#endif // W2U_TARGET_B2
