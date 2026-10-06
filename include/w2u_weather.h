#ifndef W2U_WEATHER_H
#define W2U_WEATHER_H

#include "w2u_abilities.h"

// Snow is distinct from Hail. Native cold-weather consumers use Hail as an
// opaque transport; only the resident core owns the logical weather state.
#define W2U_WEATHER_SNOW 8u
#define W2U_SNOW_START_MESSAGE 221u
#define W2U_SNOW_END_MESSAGE 222u
extern "C" b32 W2U_Weather_CanChange(ServerFlow*, WEATHER, u32);
extern "C" bool W2U_Weather_QueueSnow(ServerFlow* flow, u32 user);
extern "C" void W2U_Weather_Reset();
extern "C" void W2U_Weather_PrepareChillyReception(ServerFlow*, u32 startAction);
extern "C" void W2U_Weather_EndTurn();
extern "C" void W2U_Weather_Defense(BattleEventItem*, ServerFlow*, u32, u32*);
extern "C" void W2U_Weather_AfterChange(BattleEventItem*, ServerFlow*, u32, u32*);

#endif
