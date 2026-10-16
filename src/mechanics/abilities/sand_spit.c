/* Sand Spit, Seed Sower (Gen 8, 9): being hit by a damaging move sets a field condition (Showdown): Sand Spit a
 * sandstorm (Sand Stream's weather effect, default turns, inside the popup), Seed Sower Grassy Terrain (W2U's terrain,
 * started as its Surges do). Nothing happens, and no popup, if that condition is already up. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerSandSpitHit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerChangeWeatherParam *param;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) || W2U_Attacker() == monId) {
        return;
    }
    if (W2U_HolderAbility(flow, monId) == ABIL_SEED_SOWER) {
        if (W2U_Terrain() != W2U_TERRAIN_GRASSY) {
            W2U_SetTerrainFromAbility(flow, monId, W2U_TERRAIN_GRASSY);
        }
        return;
    }
    if (GetWeather(flow) == WEATHER_SAND) {
        return;
    }
    param = (BattleHandlerChangeWeatherParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_WEATHER, monId);
    param->popup = 1;
    param->weather = WEATHER_SAND;
    param->duration = WEATHER_TURNS_DEFAULT;
    BattleHandler_PopWork(flow, param);
}

W2U_HANDLER_TABLE(SandSpitHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerSandSpitHit },
};
W2U_MECHANIC(ABILITY, ABIL_SAND_SPIT, SandSpitHandlers);
W2U_MECHANIC(ABILITY, ABIL_SEED_SOWER, SandSpitHandlers);
