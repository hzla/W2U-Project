/* Power Spot, Steely Spirit, Battery: the holder's allies' moves hit harder.
 *   Power Spot     allies' moves: power x1.3, not the holder's own
 *   Steely Spirit  Steel moves on the holder's side: power x1.5, the holder's too (several holders each apply)
 *   Battery        allies' special moves: the attacking stat x1.3, not the holder's own
 * Power Spot and Steely Spirit share a table (EVENT_MOVE_POWER, Showdown's onAllyBasePower). Battery keeps W2U's
 * own effect on the attacking stat (EVENT_ATTACKING_STAT) and its registry name, which Black 2's baseline copy
 * (b2_baseline/w2u_abilities.cpp.inc) also provides; Showdown boosts the base power instead, which rounds differently.
 * Each module links only the table it registers (--gc-sections). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

enum { MATCH_ANY, MATCH_TYPE };

typedef struct {
    u16 ability;
    u8 holderToo;                       /* the holder's own moves get it too */
    u8 match;
    u8 type;
    u16 ratio;
} PowerSpotRow;

static const PowerSpotRow sPowerSpotRows[] = {
    { ABIL_POWER_SPOT, 0, MATCH_ANY, 0, 5325 },
    { ABIL_STEELY_SPIRIT, 1, MATCH_TYPE, TYPE_STEEL, 6144 },
};

static void HandlerPowerSpotMovePower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 attacker = W2U_Attacker();
    u16 ability;
    u32 i;

    (void)item;
    (void)work;
    if (!W2U_IsAlly(monId, attacker)) {
        return;
    }
    ability = W2U_HolderAbility(flow, monId);
    for (i = 0; i < NELEMS(sPowerSpotRows); ++i) {
        const PowerSpotRow *row = &sPowerSpotRows[i];
        if (row->ability != ability) {
            continue;
        }
        if (attacker == monId && !row->holderToo) {
            return;
        }
        if (row->match == MATCH_TYPE && W2U_MoveType() != row->type) {
            return;
        }
        W2U_MulMovePower(row->ratio);
        return;
    }
}

static void HandlerBatteryAttackerPower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 attacker = W2U_Attacker();

    (void)item;
    (void)flow;
    (void)work;
    if (monId != attacker && W2U_IsAlly(monId, attacker)
        && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == MOVE_CATEGORY_SPECIAL) {
        W2U_MulRatio(5325);
    }
}

W2U_HANDLER_TABLE(PowerSpotHandlers) = {
    { EVENT_MOVE_POWER, HandlerPowerSpotMovePower },
};
W2U_MECHANIC(ABILITY, ABIL_POWER_SPOT, PowerSpotHandlers);
W2U_MECHANIC(ABILITY, ABIL_STEELY_SPIRIT, PowerSpotHandlers);

W2U_HANDLER_TABLE(BatteryHandlers) = {
    { EVENT_ATTACKING_STAT, HandlerBatteryAttackerPower },
};
W2U_MECHANIC(ABILITY, ABIL_BATTERY, BatteryHandlers);
