#include "w2u_weather.h"
#include "w2u_battle_module_loader.h"
#include "type_constants.h"

namespace {
const u32 SNOW = 5;
// Weather clients use the standard-message archive (17), not the
// three-variant battler-message archive (18).
const u32 SNOW_START_MESSAGE = 221;
const u32 SNOW_END_MESSAGE = 222;
bool sSnow;
u8 sClientSnowMessage;
u32 sChillyCue;

// Native work has byte-sized weather/turn fields, not enum-sized words.
struct WeatherWork {
    HandlerParam_Header header;
    u8 weather, turns, airLock, padding;
    HandlerParam_StrParams message;
};
static_assert(sizeof(WeatherWork) == 48, "Native weather work ABI changed");
}

extern "C" WEATHER BattleField_GetWeather();
extern "C" b32 BattleMon_HasType(BattleMon*, u32);
extern "C" u32 BattleField_GetWeatherTurn();
extern "C" void BattleField_SetWeather(WEATHER, u32);
extern "C" void ServerControl_ChangeWeatherAfter(ServerFlow*, WEATHER);
extern "C" u32 ClientWeatherStart_Original(void*, int*, const u32*);
extern "C" u32 ClientWeatherEnd_Original(void*, int*, const u32*);
extern "C" void BattleView_StartMessageStd(void*, u32, const void*);

extern "C" void W2U_Weather_Reset()
{
    sSnow = false;
    sClientSnowMessage = 0;
    sChillyCue = 0;
}

extern "C" void W2U_Weather_EndTurn()
{
    sChillyCue = 0;
}

extern "C" void W2U_Weather_PrepareChillyReception(ServerFlow* flow, u32 first)
{
    if (!flow || flow->simulationCounter || !flow->serverCommandQueue) return;
    const u32 count = flow->numActOrder < W2U_ARRAY_COUNT(flow->actionOrderWork) ?
        flow->numActOrder : W2U_ARRAY_COUNT(flow->actionOrderWork);
    for (u32 idx = first; idx < count; ++idx) {
        const ActionOrderWork& action = flow->actionOrderWork[idx];
        BattleMon* mon = action.battleMon;
        if (action.done || !mon || BattleMon_IsFainted(mon) ||
            BattleAction_GetAction((BattleActionParam*)&action.action) != 1 ||
            action.action.baFight.moveID != MOVE_CHILLY_RECEPTION) continue;
        const u32 slot = BattleMon_GetID(mon);
        if (slot >= 24 || (sChillyCue & (1u << slot))) continue;
#if defined(W2U_DYNAMIC_BATTLE_CORE)
        if (!W2U_BattleModules_Resolve(W2U_MECHANIC_MOVE, MOVE_CHILLY_RECEPTION)) continue;
#elif defined(W2U_BATTLE_STATIC_GROUPS)
        if (!W2U_BattleStatic_Resolve(W2U_MECHANIC_MOVE, MOVE_CHILLY_RECEPTION)) continue;
#endif
        sChillyCue |= 1u << slot;
        ServerDisplay_AddMessageImpl(flow->serverCommandQueue, SCID_SetMessage,
            1358, slot, 0xFFFF0000u);
    }
}

extern "C" b32 THUMB_BRANCH_ServerControl_ChangeWeatherCheck(
    ServerFlow*, WEATHER weather, u32 turns)
{
    if (weather > SNOW) return false;
    const WEATHER native = BattleField_GetWeather();
    const WEATHER current = sSnow && native == WEATHER_HAIL ? SNOW : native;
    // Preserve native permanent-weather promotion for ordinary weather.
    return current != weather ||
        (turns == 255 && BattleField_GetWeatherTurn() != 255);
}

extern "C" void THUMB_BRANCH_ServerControl_ChangeWeatherCore(
    ServerFlow* flow, WEATHER weather, u32 turns)
{
    const WEATHER transport = weather == SNOW ? WEATHER_HAIL : weather;
    BattleField_SetWeather(transport, turns);
    sSnow = weather == SNOW;
    // Carry logical weather in queued commands: the server can expire/change
    // weather before the client renders an earlier start/end command.
    ServerDisplay_AddCommon(flow->serverCommandQueue, (ServerCommandID)0x3F, weather, turns);
    ServerControl_ChangeWeatherAfter(flow, transport);
}

extern "C" bool W2U_Weather_QueueSnow(ServerFlow* flow, u32 user)
{
    if (!flow || flow->simulationCounter || user >= 24 ||
        BattleField_GetWeatherTurn() == 255 ||
        !THUMB_BRANCH_ServerControl_ChangeWeatherCheck(flow, SNOW, 5)) return false;
    // Native Icy Rock/item suppression handlers decide the extension.
    BattleEventVar_Push();
    BattleEventVar_SetConstValue(VAR_WEATHER, WEATHER_HAIL);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, user);
    BattleEventVar_SetValue(VAR_EFFECT_TURN_COUNT, 0);
    BattleEvent_CallHandlers(flow, EVENT_MOVE_WEATHER_TURN_COUNT);
    const u32 extension = BattleEventVar_GetValue(VAR_EFFECT_TURN_COUNT);
    BattleEventVar_Pop();
    WeatherWork* work = (WeatherWork*)BattleHandler_PushWork(flow, (BattleHandlerEffect)0x1D, user);
    if (!work) return false;
    work->weather = SNOW;
    work->turns = extension == 3 ? 8 : 5;
    work->airLock = 0;
    work->padding = 0;
    BattleHandler_StrClear(&work->message);
    BattleHandler_PopWork(flow, work);
    return true;
}

extern "C" void W2U_Weather_AfterChange(BattleEventItem*, ServerFlow* flow, u32, u32*)
{
    if (!flow->simulationCounter && BattleEventVar_GetValue(VAR_WEATHER) != WEATHER_HAIL)
        sSnow = false;
}

extern "C" void W2U_Weather_Defense(BattleEventItem*, ServerFlow* flow, u32, u32*)
{
    if (!sSnow || BattleEventVar_GetValue(VAR_MOVE_CATEGORY) != SPLIT_PHYSICAL ||
        ServerEvent_GetWeather(flow) != WEATHER_HAIL) return;
    BattleMon* defender = Handler_GetBattleMon(flow, BattleEventVar_GetValue(VAR_DEFENDING_MON));
    if (defender && BattleMon_HasType(defender, TYPE_ICE))
        BattleEventVar_MulValue(VAR_RATIO, 6144);
}

// Intercept baseline weather chip before native ability reactions. Ice Body
// still sees cold weather and schedules its ordinary heal.
extern "C" u32 THUMB_BRANCH_LINK_167_0x21A8898(BattleMon* mon, WEATHER weather)
{
    if (weather == WEATHER_HAIL) {
        if (sSnow || BattleMon_HasType(mon, TYPE_ICE)) return 0;
    } else if (weather == WEATHER_SANDSTORM) {
        if (BattleMon_HasType(mon, TYPE_ROCK) || BattleMon_HasType(mon, TYPE_STEEL) ||
            BattleMon_HasType(mon, TYPE_GROUND)) return 0;
    } else return 0;
    const u32 hp = BattleMon_GetValue(mon, VALUE_MAX_HP) / 16;
    return hp ? hp : 1;
}

extern "C" void THUMB_BRANCH_LINK_167_0x21A8830(
    ServerCommandQueue* queue, ServerCommandID command, WEATHER weather)
{
    ServerDisplay_AddCommon(queue, command, sSnow && weather == WEATHER_HAIL ? SNOW : weather);
}

extern "C" u32 THUMB_BRANCH_ClientWeatherStart(void* client, int* sequence, const u32* args)
{
    const u32 normalized[2] = { args[0] == SNOW ? WEATHER_HAIL : args[0], args[1] };
    sClientSnowMessage = args[0] == SNOW ? 1 : 0;
    const u32 result = ClientWeatherStart_Original(client, sequence, normalized);
    sClientSnowMessage = 0;
    return result;
}

extern "C" u32 THUMB_BRANCH_ClientWeatherEnd(void* client, int* sequence, const u32* args)
{
    const u32 normalized = args[0] == SNOW ? WEATHER_HAIL : args[0];
    sClientSnowMessage = args[0] == SNOW ? 2 : 0;
    const u32 result = ClientWeatherEnd_Original(client, sequence, &normalized);
    sClientSnowMessage = 0;
    return result;
}

extern "C" void THUMB_BRANCH_LINK_ClientWeatherStart_0x60(void* view, u32 message, const void* args)
{
    BattleView_StartMessageStd(view, sClientSnowMessage == 1 ? SNOW_START_MESSAGE : message, args);
}

extern "C" void THUMB_BRANCH_LINK_ClientWeatherEnd_0x4A(void* view, u32 message, const void* args)
{
    BattleView_StartMessageStd(view, sClientSnowMessage == 2 ? SNOW_END_MESSAGE : message, args);
}
