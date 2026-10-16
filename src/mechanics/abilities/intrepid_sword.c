/* Intrepid Sword, Dauntless Shield (Gen 9): the first time the holder enters in a battle, Attack (Sword) or Defense
 * (Shield) +1. "Once per battle" is this module's state, reloaded fresh every battle (docs/engine-interface.md);
 * MegaB2W2's IntrepidSword_ResetForBattle, never called in W2U, is gone. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

typedef struct {
    u16 ability;
    u8 stat;
} IntrepidSwordRow;

static const IntrepidSwordRow sIntrepidSwordRows[] = {
    { ABIL_INTREPID_SWORD, STATSTAGE_ATTACK },
    { ABIL_DAUNTLESS_SHIELD, STATSTAGE_DEFENSE },
};

/* Bits by monId: the boost was used this battle */
static u32 sIntrepidSwordUsed;

static void HandlerIntrepidSwordSwitchIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u16 ability;
    u32 i;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId || (sIntrepidSwordUsed & (1u << monId))) {
        return;
    }
    ability = W2U_HolderAbility(flow, monId);
    for (i = 0; i < NELEMS(sIntrepidSwordRows); ++i) {
        if (sIntrepidSwordRows[i].ability == ability) {
            sIntrepidSwordUsed |= 1u << monId;
            W2U_ChangeStatStage(flow, monId, monId, sIntrepidSwordRows[i].stat, 1, 1);
            return;
        }
    }
}

W2U_HANDLER_TABLE(IntrepidSwordHandlers) = {
    { EVENT_SWITCH_IN, HandlerIntrepidSwordSwitchIn },
};
W2U_MECHANIC(ABILITY, ABIL_INTREPID_SWORD, IntrepidSwordHandlers);
W2U_MECHANIC(ABILITY, ABIL_DAUNTLESS_SHIELD, IntrepidSwordHandlers);
