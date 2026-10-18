/* Propeller Tail, Stalwart (Gen 8): the holder's moves ignore redirection. The engine's redirection checks
 * (Lightning Rod / Storm Drain, Follow Me / Rage Powder) ask Battle_IsRedirectBlocked first; they call this instead
 * (w2u/resident.h). W2U's Spotlight checks the abilities itself (w2u_moves.cpp); the abilities' handler table
 * (abilities/propeller_tail.c) only registers them. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

b32 W2U_RedirectBlocked(BtlServerFlow *flow, u8 attackerId, u8 redirectorId, u16 move)
{
    BattleMon *attacker = attackerId < BATTLE_MAX_MON_ID ? GetBattleMon(flow, attackerId) : 0;

    if (W2U_HasActiveAbility(attacker, ABIL_PROPELLER_TAIL) || W2U_HasActiveAbility(attacker, ABIL_STALWART)) {
        return 1;
    }
    return Battle_IsRedirectBlocked(flow, attackerId, redirectorId, move);
}
