/* Abilities that inflict a status through a hit (EVENT_AFTER_DAMAGE_REACTION):
 *   Spicy Spray  (Legends: Z-A) being hit by a damaging move burns the attacker, every time, contact or not:
 *                Flame Body without its contact and 30% checks (a burn's default value, inside the popup)
 *   Toxic Chain  (Gen 9) the holder's damaging hits badly poison the target 30% of the time, not through a
 *                substitute or Shield Dust: Poison Touch without the contact check, with Toxic's condition value
 *                built as the engine builds a move's
 * The engine applies the usual immunities and shows the status' own text. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MOVE_TOXIC 92
#define MAX_MON_ID 24

static void HandlerSpicySprayReaction(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 attacker;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) || Handler_CheckMatchup(flow)) {
        return;
    }
    attacker = W2U_Attacker();
    if (attacker == monId || attacker >= MAX_MON_ID) {
        return;
    }
    if (W2U_IsFainted(flow, attacker) || GetBattleMonStatus(GetBattleMon(flow, attacker))) {
        return;
    }
    W2U_AddCondition(flow, monId, attacker, CONDITION_BURN, BtlCalc_MakeMajorStatusCondition(CONDITION_BURN));
}

static void HandlerToxicChainReaction(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 target;
    BattleCondition value = { 0 };

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId) {
        return;
    }
    if (BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) != 0 || BattleEventVar_GetValue(VAR_NO_SECONDARY) != 0) {
        return;
    }
    target = W2U_Defender();
    if (target == monId || !AbilityEvent_RollEffectChance(flow, 30)) {
        return;
    }
    BtlCalc_BuildMoveCondition(PML_MoveGetConditionParam(MOVE_TOXIC), GetBattleMon(flow, monId), &value);
    W2U_AddCondition(flow, monId, target, CONDITION_POISON, value);
}

W2U_HANDLER_TABLE(SpicySprayHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerSpicySprayReaction },
};
W2U_MECHANIC(ABILITY, ABIL_SPICY_SPRAY, SpicySprayHandlers);

W2U_HANDLER_TABLE(ToxicChainHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerToxicChainReaction },
};
W2U_MECHANIC(ABILITY, ABIL_TOXIC_CHAIN, ToxicChainHandlers);
