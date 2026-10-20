/* The strong weathers' numbers (include/w2u/strong_weather.h): plain defines, shared by the C server and the
 * injection build's C++ view (include/w2u_strong_weather.h). */
#ifndef W2U_STRONG_WEATHER_IDS_H
#define W2U_STRONG_WEATHER_IDS_H

#define W2U_STRONG_WEATHER_NONE 0u
#define W2U_STRONG_WEATHER_WINDS 1u
#define W2U_STRONG_WEATHER_RAIN 2u
#define W2U_STRONG_WEATHER_SUN 3u
#define W2U_STRONG_WEATHER_KIND_COUNT 4u

/* View weather values (display commands 0x3F / 0x40); 1-4 are the retail weathers */
#define W2U_WEATHER_VIEW_STRONG_WINDS 5u
#define W2U_WEATHER_VIEW_HEAVY_RAIN 6u
#define W2U_WEATHER_VIEW_EXTREME_SUN 7u

/* Std battle messages (text bank 19, after the 201 retail entries) */
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

/* Battle effects: a/0/6/5 members 960-964 started as member + 115 (w2u_move_animation_hooks.s) */
#define W2U_EFFECT_STRONG_WINDS 1075u
#define W2U_EFFECT_HEAVY_RAIN 1076u
#define W2U_EFFECT_HEAVY_RAIN_TURN 1077u
#define W2U_EFFECT_EXTREME_SUN 1078u
#define W2U_EFFECT_EXTREME_SUN_TURN 1079u

#define W2U_STRONG_WEATHER_NO_TYPE 0xFFu

#endif /* W2U_STRONG_WEATHER_IDS_H */
