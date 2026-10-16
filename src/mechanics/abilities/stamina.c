/* Abilities that raise the holder's stats when it is hit (EVENT_AFTER_DAMAGE_REACTION):
 *   Stamina           any hit: Defense +1
 *   Water Compaction  a Water hit: Defense +2
 *   Steam Engine      a Fire or Water hit: Speed +6
 *   Thermal Exchange  a Fire hit: Attack +1; it can't be burned either (Water Veil's handlers)
 * Stamina and Water Compaction keep W2U's own rules and registry names, which Black 2's baseline copy
 * (b2_baseline/w2u_abilities.cpp.inc) also provides: any hit on the holder that is not on a substitute, the hit's
 * type, W2U's popup around the change (W2U_PopupStatChange). Steam Engine and Thermal Exchange keep MegaB2W2's: not
 * the holder's own hits nor a fainted holder, the move's final type, the change inside the popup. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerStaminaReaction(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Defender() == monId && !BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT)) {
        W2U_PopupStatChange(flow, monId, STATSTAGE_DEFENSE, 1);
    }
}

static void HandlerWaterCompactionReaction(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Defender() == monId && !BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) && W2U_MoveType() == TYPE_WATER) {
        W2U_PopupStatChange(flow, monId, STATSTAGE_DEFENSE, 2);
    }
}

typedef struct {
    u16 ability;
    u8 stat;
    s8 stages;
    u32 types;                          /* bit mask (1 << type) */
} SteamEngineRow;

static const SteamEngineRow sSteamEngineRows[] = {
    { ABIL_STEAM_ENGINE, STATSTAGE_SPEED, 6, (1u << TYPE_FIRE) | (1u << TYPE_WATER) },
    { ABIL_THERMAL_EXCHANGE, STATSTAGE_ATTACK, 1, 1u << TYPE_FIRE },
};

static void HandlerSteamEngineReaction(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 attacker = W2U_Attacker();
    u16 ability;
    u32 i;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || attacker == monId) {
        return;
    }
    if (BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) != 0 || W2U_IsFainted(flow, monId)) {
        return;
    }
    ability = W2U_HolderAbility(flow, monId);
    for (i = 0; i < NELEMS(sSteamEngineRows); ++i) {
        const SteamEngineRow *row = &sSteamEngineRows[i];
        if (row->ability != ability) {
            continue;
        }
        if (row->types & (1u << W2U_FinalMoveType(flow, W2U_Move(), attacker))) {
            W2U_ChangeStatStage(flow, monId, monId, row->stat, row->stages, 1);
        }
        return;
    }
}

W2U_HANDLER_TABLE(StaminaHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerStaminaReaction },
};
W2U_MECHANIC(ABILITY, ABIL_STAMINA, StaminaHandlers);

W2U_HANDLER_TABLE(WaterCompactionHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerWaterCompactionReaction },
};
W2U_MECHANIC(ABILITY, ABIL_WATER_COMPACTION, WaterCompactionHandlers);

W2U_HANDLER_TABLE(SteamEngineHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerSteamEngineReaction },
};
W2U_MECHANIC(ABILITY, ABIL_STEAM_ENGINE, SteamEngineHandlers);

W2U_HANDLER_TABLE(ThermalExchangeHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerSteamEngineReaction },
    { EVENT_ADD_CONDITION_CHECK, HandlerWaterVeil },
    { EVENT_ADD_CONDITION_FAILED, HandlerAddStatusFailedCommon },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerWaterVeilCureStatus },
    { EVENT_SWITCH_IN, HandlerWaterVeilCureStatus },
    { EVENT_ACTION_END, HandlerWaterVeilActionEnd },
};
W2U_MECHANIC(ABILITY, ABIL_THERMAL_EXCHANGE, ThermalExchangeHandlers);
