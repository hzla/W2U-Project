/* Neuroforce (Gen 7, Ultra Necrozma): the holder's super effective hits deal x1.25 damage. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerNeuroforceDamageRatio(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId
        && BtlCalc_ClassifyEffectiveness((s32)BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS)) == EFFECTIVENESS_SUPER) {
        W2U_MulRatio(5120);             /* x1.25 */
    }
}

W2U_HANDLER_TABLE(NeuroforceHandlers) = {
    { EVENT_DAMAGE_RATIO, HandlerNeuroforceDamageRatio },
};
W2U_MECHANIC(ABILITY, ABIL_NEUROFORCE, NeuroforceHandlers);
