/* Terrain abilities (Gen 7-9; Showdown), on W2U's terrain. W2U has its own Surges and Surge Surfer.
 *   Orichalcum Pulse  on entering, harsh sunlight starts (Drought's weather effect: 5 turns, or the Heat Rock's), then
 *                     "X turned the sunlight harsh..." ("basked in the sunlight" if it was up already); Attack x1.333
 *                     in sun
 *   Hadron Engine     the same with Electric Terrain and Sp. Atk
 *   Grass Pelt        Defense x1.5 on Grassy Terrain (Mold Breaker ignores it)
 *   Mimicry           its type becomes the terrain's (Electric / Grass / Fairy / Psychic), and its own types again
 *                     when there is none ("X transformed into the Y type!"); checked on entering, after every action
 *                     and at the end of the turn */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

/* ---- Orichalcum Pulse, Hadron Engine ---- */

static void HandlerPulseStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    b32 up;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId) {
        return;
    }
    if (W2U_HolderAbility(flow, monId) == ABIL_HADRON_ENGINE) {
        /* Starting the terrain shows its own popup and the message naming the holder at once, so the popup here is
         * only for Electric Terrain already being up */
        if (W2U_Terrain() != W2U_TERRAIN_ELECTRIC
            && W2U_SetTerrainFromAbilityNamed(flow, monId, W2U_TERRAIN_ELECTRIC, BTLMSG_SET_HADRON_START)) {
            return;
        }
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
        W2U_Message(flow, monId, BTLMSG_SET_HADRON_USE);
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    up = GetWeather(flow) == WEATHER_SUN;
    if (!up) {
        BattleHandlerChangeWeatherParam *param =
            (BattleHandlerChangeWeatherParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_WEATHER, monId);
        param->weather = WEATHER_SUN;
        param->duration = WEATHER_TURNS_DEFAULT;
        BattleHandler_PopWork(flow, param);
    }
    W2U_Message(flow, monId, up ? BTLMSG_SET_ORICHALCUM_BASK : BTLMSG_SET_ORICHALCUM_START);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerPulseAttackingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 category;
    b32 hadron;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId) {
        return;
    }
    category = W2U_MoveCategory(W2U_Move());
    hadron = W2U_HolderAbility(flow, monId) == ABIL_HADRON_ENGINE;
    if (hadron ? (category != MOVE_CATEGORY_SPECIAL || W2U_Terrain() != W2U_TERRAIN_ELECTRIC)
               : (category != MOVE_CATEGORY_PHYSICAL || GetWeather(flow) != WEATHER_SUN)) {
        return;
    }
    W2U_MulRatio(5461);                 /* x1.333 */
}

/* ---- Grass Pelt ---- */

static void HandlerGrassPeltDefense(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Defender() != monId) {
        return;
    }
    if (W2U_Terrain() == W2U_TERRAIN_GRASSY && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1) {
        W2U_MulRatio(6144);             /* x1.5 */
    }
}

/* ---- Mimicry ---- */

/* Per Pokémon: its own type pair while changed (0: not changed) */
static u16 sMimicryOwnType[BATTLE_MAX_MON_ID];

static void MimicryCheck(BtlServerFlow *flow, u8 monId)
{
    BattleHandlerChangeTypeParam *param;
    BattleMon *mon;
    u32 terrain;
    u16 want;

    if (monId >= BATTLE_MAX_MON_ID || !W2U_OnField(flow, monId)) {
        return;
    }
    mon = GetBattleMon(flow, monId);
    if (IsFainted(mon)) {
        return;
    }
    terrain = W2U_Terrain();
    if (terrain) {
        want = PokeTypePair_MakeMonotype(W2U_TerrainType(terrain));
        if (!sMimicryOwnType[monId]) {
            sMimicryOwnType[monId] = GetPokeType(mon);
        }
    } else {
        if (!sMimicryOwnType[monId]) {
            return;
        }
        want = sMimicryOwnType[monId];
    }
    if (GetPokeType(mon) == want) {
        if (!terrain) {
            sMimicryOwnType[monId] = 0;
        }
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    param = (BattleHandlerChangeTypeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_TYPE, monId);
    param->type = want;
    param->monIndex = monId;
    BattleHandler_PopWork(flow, param);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    if (!terrain) {
        sMimicryOwnType[monId] = 0;
    }
}

static void HandlerMimicryCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    MimicryCheck(flow, monId);
}

static void HandlerMimicryLeave(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() == monId && monId < BATTLE_MAX_MON_ID) {
        sMimicryOwnType[monId] = 0;
    }
}

W2U_HANDLER_TABLE(PulseHandlers) = {
    { EVENT_SWITCH_IN, HandlerPulseStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerPulseStart },
    { EVENT_ATTACKING_STAT, HandlerPulseAttackingStat },
};
W2U_MECHANIC(ABILITY, ABIL_ORICHALCUM_PULSE, PulseHandlers);
W2U_MECHANIC(ABILITY, ABIL_HADRON_ENGINE, PulseHandlers);

W2U_HANDLER_TABLE(GrassPeltHandlers) = {
    { EVENT_DEFENDING_STAT, HandlerGrassPeltDefense },
};
W2U_MECHANIC(ABILITY, ABIL_GRASS_PELT, GrassPeltHandlers);

W2U_HANDLER_TABLE(MimicryHandlers) = {
    { EVENT_SWITCH_IN, HandlerMimicryCheck },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerMimicryCheck },
    { EVENT_ACTION_END, HandlerMimicryCheck },
    { EVENT_TURN_CHECK, HandlerMimicryCheck },
    { EVENT_SWITCH_OUT_END, HandlerMimicryLeave },
};
W2U_MECHANIC(ABILITY, ABIL_MIMICRY, MimicryHandlers);
