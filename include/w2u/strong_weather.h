/* Strong weathers: Delta Stream (strong winds), Primordial Sea (heavy rain), Desolate Land (extremely harsh sun).
 * Ported from MegaB2W2 (StrongWeather.cpp / WeatherView.cpp). White 2 only.
 *
 * Server (src/mechanics/resident/strong_weather.c, resident in both builds): one strong weather at a time, kept up by
 * the Pokémon holding its ability. A holder entering starts it and replaces any weather (no end text); it ends when no
 * holder of the active kind remains. While one is active, ordinary weather fails with the kind's message. Air Lock /
 * Cloud Nine negate its effects, not its presence.
 *  - strong winds: no engine weather; a super-effective hit's Flying weakness becomes x1;
 *  - heavy rain / harsh sun: the engine weather is rain / sun with permanent turns (every native rain / sun rule
 *    applies); damaging Fire moves in heavy rain / Water moves in harsh sun fail after "X used Y!", and the AI's
 *    damage estimate for them is 0.
 * The abilities' handlers: src/mechanics/abilities/strong_weather.c. The view (display commands 0x3F / 0x40 with the
 * view weathers of w2u/strong_weather_ids.h, a/0/6/5 effects) is the injection build's (src/pokeweb_gameplay/w2u_strong_weather.cpp); a
 * decomp build's client is retail, so there the start and end are their texts alone. */
#ifndef W2U_STRONG_WEATHER_H
#define W2U_STRONG_WEATHER_H

#include "w2u/battle_api.h"
#include "w2u/strong_weather_ids.h"

W2U_C_BEGIN

/* The state (battle-long; zero is none) */
u32 W2U_StrongWeather_Kind(void);
b32 W2U_StrongWeather_WindsActive(void);
u32 W2U_StrongWeather_FirstHolder(u32 kind);           /* the lowest monId holding it (0 if none) */
u32 W2U_StrongWeather_FizzleType(u32 kind);            /* the type its weather stops, or W2U_STRONG_WEATHER_NO_TYPE */
b32 W2U_StrongWeather_Negated(BtlServerFlow *flow);    /* Air Lock / Cloud Nine on the field */
void W2U_StrongWeather_Reset(void);
/* The holder enters (or gains the ability) / leaves (or loses it, faints) */
void W2U_StrongWeather_Start(BtlServerFlow *flow, u32 monId, u32 kind);
void W2U_StrongWeather_End(BtlServerFlow *flow, u32 monId);
/* The view weather the client shows (the injection build's view: strong weather or Snow; 0 = retail) */
u32 W2U_StrongWeather_ShownView(void);
void W2U_StrongWeather_SetShownView(u32 view);
/* The turn-end effect of the active kind, 0 if none */
u32 W2U_StrongWeather_TurnEffect(void);

W2U_C_END

#endif /* W2U_STRONG_WEATHER_H */
