/* Mega Sol: during its holder's move the weather reads as sun (W2U_MB_SetMegaSolAttacker, from the mechanic).
 * ServerEvent_GetWeather's result (the field's weather, none under Air Lock / Cloud Nine) goes through W2U_Weather. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

static u8 sMegaSolAttacker;                 /* + 1; 0: none */

u8 W2U_Weather(BtlServerFlow *flow, u8 weather)
{
    if (sMegaSolAttacker && W2U_HasActiveAbility(GetBattleMon(flow, (u8)(sMegaSolAttacker - 1)), ABIL_MEGA_SOL)) {
        return WEATHER_SUN;
    }
    return weather;
}

void W2U_MB_SetMegaSolAttacker(u32 monId)
{
    sMegaSolAttacker = (u8)(monId < BATTLE_MAX_MON_ID ? monId + 1 : 0);
}

void W2U_Resident_ResetWeather(void)
{
    sMegaSolAttacker = 0;
}
