#pragma once

// Strong weathers: Delta Stream (strong winds), Primordial Sea (heavy rain), Desolate Land (extremely harsh sun).
// Ported from MegaB2W2 (StrongWeather.cpp / WeatherView.cpp). White 2 only on this branch: the hook sites and
// the W2U_ADDR_STRONG_WEATHER_* anchors below have not been mapped for Black 2; the battle module is
// "white2_only" in the registry, so Black 2 builds neither the module nor this code.
//
// Server: in C, both builds (include/w2u/strong_weather.h has the rules). This is the injection build's side: its
// hooks and the view.
// View: display commands 0x3F / 0x40 carry the view weather values below; the effects are a/0/6/5 scripts
// (tools/graphics/build_strong_weather_effects.py) and the texts are std battle messages (text bank 19).

#include "w2u_abilities.h"

#include "w2u/strong_weather_ids.h"   // kinds, view weathers, std messages, effects

// White 2 (IRDO) anchors with no name in pmc/IRDO.yml.
#define W2U_ADDR_STRONG_WEATHER_TURN_CHECK               0x021A881Du  // ov167: (serverFlow, pokeSet)
#define W2U_ADDR_STRONG_WEATHER_CLIENT_SET               0x021D5B2Du  // ov167: (clientField, weather, turns)
#define W2U_ADDR_STRONG_WEATHER_CLIENT_CLEAR             0x021D5B35u  // ov167: (clientField)
#define W2U_ADDR_STRONG_WEATHER_SKIP_EFFECTS             0x021B19D1u  // ov167: (client) nonzero = skip effect + text
#define W2U_ADDR_STRONG_WEATHER_STD_MESSAGE              0x021D0291u  // ov167: (btlv, stdMsgID, args or 0)
#define W2U_ADDR_STRONG_WEATHER_WAIT_MESSAGE             0x021D0329u  // ov167: (btlv) nonzero when done
#define W2U_ADDR_STRONG_WEATHER_EFFECT_START             0x021DF309u  // ov168: (effectID)
#define W2U_ADDR_STRONG_WEATHER_EFFECT_BUSY              0x021DF829u  // ov168: nonzero while an effect runs
#define W2U_ADDR_STRONG_WEATHER_VIEW_TABLE               0x021D6F48u  // ov167 data: {u16 stdMsg, u16 effect} per weather 0-4

extern "C" {
// The state and server side: src/mechanics/resident/strong_weather.c (w2u/strong_weather.h); the abilities' handler
// tables: src/mechanics/abilities/strong_weather.c (battle module abilities/strong_weather).
u32 W2U_StrongWeather_Kind();
b32 W2U_StrongWeather_WindsActive();
u32 W2U_StrongWeather_FirstHolder(u32 kind);
u32 W2U_StrongWeather_FizzleType(u32 kind);
u32 W2U_StrongWeather_ShownView();
void W2U_StrongWeather_SetShownView(u32 view);
u32 W2U_StrongWeather_TurnEffect();
void W2U_StrongWeather_Reset();
}
