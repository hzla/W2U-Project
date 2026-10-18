/* Commander's engine call sites (the mechanic: abilities/form_abilities.c). The mechanic hides a commanding
 * Tatsugiri with Shadow Force's flag and sets the recharge flag each turn so the command menu skips it. Showdown:
 * nothing reaches a commanding Tatsugiri, No Guard and Lock-On included, and it makes no choice at all. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define SPECIES_TATSUGIRI 978

static b32 Commanding(BattleMon *mon)
{
    return mon && W2U_Species(mon) == SPECIES_TATSUGIRI && W2U_HasActiveAbility(mon, ABIL_COMMANDER) &&
           GetAdditionalConditionFlag(mon, CONT_FLAG_SHADOW_FORCE);
}

/* No Guard / Lock-On / Mind Reader skip the hide check that follows: not for it */
b32 W2U_GuaranteedHit(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target)
{
    return Commanding(target) ? 0 : IsGuaranteedHit(flow, attacker, target);
}

/* The action order's recharge action: "X must recharge!", not for a commanding Tatsugiri */
void W2U_RechargeAction(BtlServerFlow *flow, BattleMon *mon)
{
    if (!Commanding(mon)) {
        ServerControl_RechargeAction(flow, mon);
    }
}
