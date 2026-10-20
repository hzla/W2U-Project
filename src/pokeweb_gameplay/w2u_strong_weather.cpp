// Strong weathers (Delta Stream, Primordial Sea, Desolate Land). Ported from MegaB2W2; see
// include/w2u/strong_weather.h for the rules. Their state, server side and the AI's damage estimate are C
// (src/mechanics/resident/strong_weather.c), the abilities' handlers too (src/mechanics/abilities/strong_weather.c);
// this is the injection build's side: the call-site hooks forwarding to that C, and the view.
#include "w2u_abilities.h"
#include "w2u_battle.h"
#include "w2u_strong_weather.h"
#include "w2u_weather.h"

#define W2U_STRONG_WEATHER_CALL(type, address) ((type)(address))

#if !defined(W2U_TARGET_B2)   // White 2 only (registry "white2_only")

extern "C" b32 W2U_StrongWeatherBlocksChange(ServerFlow* serverFlow, u32 weather);
extern "C" u32 W2U_AICalcDamage(ServerFlow* serverFlow, BattleMon* attacker, BattleMon* defender,
    MoveParam* moveParam, u32 typeEffectiveness, u32 targetRatio, u32 critical, u32 debugMode, u16* damage);

namespace {

const u32 SCID_FIELD_EFFECT = 0x4C;       // (effect)
const u32 TURNS_PERMANENT = 0xFF;
const u32 ENGINE_SUN = 1;
const u32 ENGINE_RAIN = 2;

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

} // namespace

// ---- resident hooks (White 2) ------------------------------------------------------------------------------

// ServerControl_ChangeWeatherCheck (ov167 0x21A767C), re-implemented 1:1 plus the strong-weather block. Every
// weather setter (moves, Drizzle, Sand Stream ...) asks this first.
extern "C" b32 THUMB_BRANCH_167_0x21A767C(ServerFlow* serverFlow, u32 weather, u32 turns)
{
    if (weather > 4 && weather != W2U_WEATHER_SNOW) {
        return 0;
    }
    if (W2U_StrongWeatherBlocksChange(serverFlow, weather)) {
        return 0;
    }
    return W2U_Weather_CanChange(serverFlow, (WEATHER)weather, turns);
}

// Turn end: the turn-check sequence calls ServerControl_TurnCheckWeather at ov167 0x21A7FBA. A strong weather's
// turn effect plays first; heavy rain / harsh sun keep their engine weather with permanent turns, so the native
// routine still runs their per-Pokemon effects (Rain Dish, Dry Skin, Solar Power ...) without counting down.
extern "C" b32 THUMB_BRANCH_LINK_167_0x21A7FBA(ServerFlow* serverFlow, void* pokeSet)
{
    if (u32 effect = W2U_StrongWeather_TurnEffect()) {
        ServerDisplay_AddCommon(serverFlow->serverCommandQueue, (ServerCommandID)SCID_FIELD_EFFECT, effect);
    }
    return W2U_STRONG_WEATHER_CALL(TurnCheckFn, W2U_ADDR_STRONG_WEATHER_TURN_CHECK)(serverFlow, pokeSet);
}

// The AI's damage simulation (AICalcDamage, ov167 0x21AB994) calls ServerEvent_CalcDamage at 0x21ABA24 with the final
// move parameters: W2U_AICalcDamage estimates a move that would fizzle as one that doesn't affect the target, so the
// AI stops choosing it.
extern "C" u32 THUMB_BRANCH_LINK_167_0x21ABA24(ServerFlow* serverFlow, BattleMon* attacker, BattleMon* defender,
    MoveParam* moveParam, u32 typeEffectiveness, u32 targetRatio, u32 critical, u32 debugMode, u16* damage)
{
    return W2U_AICalcDamage(serverFlow, attacker, defender, moveParam, typeEffectiveness, targetRatio, critical,
        debugMode, damage);
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
    const bool snow = weather == W2U_WEATHER_SNOW;
    const u32 retail = snow ? WEATHER_HAIL : weather;
    if (!strong && retail >= RETAIL_WEATHERS) return 1;
    switch (*sequence) {
    case 0:
        if (strong) {
            if (strong->clientWeather) {
                W2U_STRONG_WEATHER_CALL(ClientSetFn, W2U_ADDR_STRONG_WEATHER_CLIENT_SET)(
                    ClientField(client), strong->clientWeather, TURNS_PERMANENT);
            } else {
                W2U_STRONG_WEATHER_CALL(ClientClearFn, W2U_ADDR_STRONG_WEATHER_CLIENT_CLEAR)(ClientField(client));
            }
            W2U_StrongWeather_SetShownView(strong->view);
        } else {
            W2U_STRONG_WEATHER_CALL(ClientSetFn, W2U_ADDR_STRONG_WEATHER_CLIENT_SET)(
                ClientField(client), retail, args[1] & 0xFFFF);
            W2U_StrongWeather_SetShownView(snow ? W2U_WEATHER_SNOW : 0);
        }
        if (W2U_STRONG_WEATHER_CALL(SkipEffectsFn, W2U_ADDR_STRONG_WEATHER_SKIP_EFFECTS)(client)) {
            return 1;
        }
        if (strong) {
            W2U_STRONG_WEATHER_CALL(EffectStartFn, W2U_ADDR_STRONG_WEATHER_EFFECT_START)(strong->effect);
        } else if (retail < RETAIL_WEATHERS) {
            W2U_STRONG_WEATHER_CALL(EffectStartFn, W2U_ADDR_STRONG_WEATHER_EFFECT_START)(
                RetailViewTable()[retail].effect);
        }
        break;
    case 1:
        if (W2U_STRONG_WEATHER_CALL(EffectBusyFn, W2U_ADDR_STRONG_WEATHER_EFFECT_BUSY)()) {
            return 0;
        }
        W2U_STRONG_WEATHER_CALL(StdMessageFn, W2U_ADDR_STRONG_WEATHER_STD_MESSAGE)(
            ClientView(client), strong ? strong->msgStart : snow ? W2U_SNOW_START_MESSAGE : RetailViewTable()[retail].stdMsg, 0);
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
    const bool snow = weather == W2U_WEATHER_SNOW;
    if (*sequence == 0) {
        if (!strong && !snow && (weather == 0 || weather >= RETAIL_WEATHERS)) {
            return 1;
        }
        W2U_STRONG_WEATHER_CALL(StdMessageFn, W2U_ADDR_STRONG_WEATHER_STD_MESSAGE)(
            ClientView(client), strong ? strong->msgEnd : snow ? W2U_SNOW_END_MESSAGE : kWeatherEndMsg[weather], 0);
        ++*sequence;
    } else if (*sequence == 1 &&
               W2U_STRONG_WEATHER_CALL(WaitMessageFn, W2U_ADDR_STRONG_WEATHER_WAIT_MESSAGE)(ClientView(client))) {
        if (strong || snow) {
            W2U_StrongWeather_SetShownView(0);
        }
        W2U_STRONG_WEATHER_CALL(ClientClearFn, W2U_ADDR_STRONG_WEATHER_CLIENT_CLEAR)(ClientField(client));
        return 1;
    }
    return 0;
}


#endif // W2U_TARGET_B2
