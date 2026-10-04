#pragma once

// Strong weathers: Delta Stream (strong winds), Primordial Sea (heavy rain), Desolate Land (extremely harsh sun).
// Ported from MegaB2W2 (StrongWeather.cpp / WeatherView.cpp). White 2 only on this branch: the hook sites and
// the W2U_ADDR_STRONG_WEATHER_* anchors below have not been mapped for Black 2, so a Black 2 build gets one-entry
// no-op handler tables (the abilities do nothing there) and none of the hooks.
//
// Server: one strong weather at a time, kept up by the Pokemon holding its ability. A holder entering starts it
// and replaces any weather (no end text); it ends when no holder of the active kind remains. While one is active,
// ordinary weather fails with the kind's message. Air Lock / Cloud Nine negate its effects, not its presence.
//  - strong winds: no engine weather; super-effective hits on Flying types become neutral.
//  - heavy rain / harsh sun: the engine weather is rain / sun with permanent turns (every native rain / sun rule
//    applies); damaging Fire moves in heavy rain / Water moves in harsh sun fail after "X used Y!".
// View: display commands 0x3F / 0x40 carry the view weather values below; the effects are a/0/6/5 scripts
// (tools/graphics/build_strong_weather_effects.py) and the texts are std battle messages (text bank 19).

#include "w2u_abilities.h"

enum W2UStrongWeatherKind : u32 {
    W2U_STRONG_WEATHER_NONE = 0,
    W2U_STRONG_WEATHER_WINDS = 1,
    W2U_STRONG_WEATHER_RAIN = 2,
    W2U_STRONG_WEATHER_SUN = 3,
    W2U_STRONG_WEATHER_KIND_COUNT = 4,
};

// View weather values (display commands 0x3F / 0x40); 1-4 are the retail weathers.
#define W2U_WEATHER_VIEW_STRONG_WINDS 5u
#define W2U_WEATHER_VIEW_HEAVY_RAIN 6u
#define W2U_WEATHER_VIEW_EXTREME_SUN 7u

// Std battle messages (text bank 19, appended after the 201 retail entries).
#define W2U_STD_MSG_DELTA_STREAM_START 201u
#define W2U_STD_MSG_DELTA_STREAM_WEAKEN 202u
#define W2U_STD_MSG_DELTA_STREAM_BLOCK 203u
#define W2U_STD_MSG_DELTA_STREAM_END 204u
#define W2U_STD_MSG_HEAVY_RAIN_START 205u
#define W2U_STD_MSG_HEAVY_RAIN_BLOCK 206u
#define W2U_STD_MSG_HEAVY_RAIN_FIZZLE 207u
#define W2U_STD_MSG_HEAVY_RAIN_END 208u
#define W2U_STD_MSG_EXTREME_SUN_START 209u
#define W2U_STD_MSG_EXTREME_SUN_BLOCK 210u
#define W2U_STD_MSG_EXTREME_SUN_FIZZLE 211u
#define W2U_STD_MSG_EXTREME_SUN_END 212u

// Battle effects: a/0/6/5 members 960-964 started as member + 115 (w2u_move_animation_hooks.s).
#define W2U_EFFECT_STRONG_WINDS 1075u
#define W2U_EFFECT_HEAVY_RAIN 1076u
#define W2U_EFFECT_HEAVY_RAIN_TURN 1077u
#define W2U_EFFECT_EXTREME_SUN 1078u
#define W2U_EFFECT_EXTREME_SUN_TURN 1079u

// White 2 (IRDO) anchors with no name in pmc/IRDO.yml.
#define W2U_ADDR_STRONG_WEATHER_FIELD_GET_WEATHER        0x021D59F1u  // ov167: engine weather (0 none, 1 sun, 2 rain, 3 hail, 4 sand)
#define W2U_ADDR_STRONG_WEATHER_FIELD_GET_TURNS          0x021D5A01u  // ov167: remaining turns (0xFF permanent)
#define W2U_ADDR_STRONG_WEATHER_FIELD_SET_WEATHER        0x021D5A11u  // ov167: (weather, turns)
#define W2U_ADDR_STRONG_WEATHER_CHANGE_AFTER             0x021A76D1u  // ov167: (serverFlow, weather) Forecast etc.
#define W2U_ADDR_STRONG_WEATHER_TURN_CHECK               0x021A881Du  // ov167: (serverFlow, pokeSet)
#define W2U_ADDR_STRONG_WEATHER_CLIENT_SET               0x021D5B2Du  // ov167: (clientField, weather, turns)
#define W2U_ADDR_STRONG_WEATHER_CLIENT_CLEAR             0x021D5B35u  // ov167: (clientField)
#define W2U_ADDR_STRONG_WEATHER_SKIP_EFFECTS             0x021B19D1u  // ov167: (client) nonzero = skip effect + text
#define W2U_ADDR_STRONG_WEATHER_STD_MESSAGE              0x021D0291u  // ov167: (btlv, stdMsgID, args or 0)
#define W2U_ADDR_STRONG_WEATHER_WAIT_MESSAGE             0x021D0329u  // ov167: (btlv) nonzero when done
#define W2U_ADDR_STRONG_WEATHER_EFFECT_START             0x021DF309u  // ov168: (effectID)
#define W2U_ADDR_STRONG_WEATHER_EFFECT_BUSY              0x021DF829u  // ov168: nonzero while an effect runs
#define W2U_ADDR_STRONG_WEATHER_VIEW_TABLE               0x021D6F48u  // ov167 data: {u16 stdMsg, u16 effect} per weather 0-4

#if defined(W2U_TARGET_B2)
#define W2U_DELTA_STREAM_HANDLER_COUNT 1
#define W2U_PRIMORDIAL_SEA_HANDLER_COUNT 1
#define W2U_DESOLATE_LAND_HANDLER_COUNT 1
#else
#define W2U_DELTA_STREAM_HANDLER_COUNT 7
#define W2U_PRIMORDIAL_SEA_HANDLER_COUNT 8
#define W2U_DESOLATE_LAND_HANDLER_COUNT 8
#endif

// Ability handler tables (src/pokeweb_gameplay/w2u_strong_weather.cpp; battle module abilities/strong_weather).
extern BattleEventHandlerTableEntry DeltaStreamHandlers[W2U_DELTA_STREAM_HANDLER_COUNT];
extern BattleEventHandlerTableEntry PrimordialSeaHandlers[W2U_PRIMORDIAL_SEA_HANDLER_COUNT];
extern BattleEventHandlerTableEntry DesolateLandHandlers[W2U_DESOLATE_LAND_HANDLER_COUNT];

extern "C" {
// Resident state (core); battle-module children call these instead of touching storage directly.
u32 W2U_StrongWeather_Kind();
bool W2U_StrongWeather_WindsActive();
void W2U_StrongWeather_Start(void* serverFlow, u32 pokemonSlot, u32 kind);
void W2U_StrongWeather_End(void* serverFlow, u32 pokemonSlot);
u32 W2U_StrongWeather_FirstHolder(u32 kind);
bool W2U_StrongWeather_Negated(void* serverFlow);
u32 W2U_StrongWeather_FizzleType(u32 kind);
u32 W2U_StrongWeather_ShownView();
void W2U_StrongWeather_Reset();
}
