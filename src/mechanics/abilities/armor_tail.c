/* Armor Tail (Gen 9), MegaB2W2's Queenly Majesty rule: a foe's move with priority above 0 (after Prankster, Gale
 * Wings, Triage) aimed at the holder or its ally fails (Showdown). Showdown stops the move in TryMove ("X cannot use
 * Y!"); the engine's move-execution check carries no target, so here each target the rule covers is not affected
 * (EVENT_CHECK_NO_EFFECT: the popup and "It doesn't affect X..."), which ends the same way for the moves it covers,
 * moves aimed at Pokémon. Not covered: Prankster field moves (Haze), which have no target to check. Mold Breaker
 * ignores it (IsMoldBreakerAffectedAbility in w2u_abilities.cpp).
 * Queenly Majesty and Dazzling keep W2U's own handler (w2u_abilities.cpp), which blocks without a popup. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define PRIORITY_ZERO 7                 /* ServerEvent_GetMovePriority returns priority + 7 */

static void HandlerArmorTailNoEffect(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 defender = W2U_Defender(), attacker = W2U_Attacker();
    u16 move;

    (void)item;
    (void)work;
    if (!W2U_IsAlly(monId, defender) || W2U_IsAlly(monId, attacker)) {
        return;                         /* the holder's side, a foe's move */
    }
    move = W2U_Move();
    if (!W2U_TargetsPokemon(move)) {
        return;
    }
    if (ServerEvent_GetMovePriority(flow, move, GetBattleMon(flow, attacker)) <= PRIORITY_ZERO) {
        return;
    }
    if (BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) {
        W2U_PopupMessageAbout(flow, monId, W2U_MSG_SET_DOESNT_AFFECT, defender);
    }
}

W2U_HANDLER_TABLE(ArmorTailHandlers) = {
    { EVENT_CHECK_NO_EFFECT, HandlerArmorTailNoEffect },
};
W2U_MECHANIC(ABILITY, ABIL_ARMOR_TAIL, ArmorTailHandlers);
