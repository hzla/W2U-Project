/* Good as Gold (Gen 9, Gholdengo): status moves used by any other Pokémon, foes and allies alike, don't affect the
 * holder (the ability popup and "It doesn't affect..."). Showdown's rule: blocked when the status move targets
 * Pokémon (one, several or all adjacent foes) and its user is not the holder. Not blocked: damaging moves and their
 * secondary effects, the holder's own moves, field and side moves (hazards, screens) and moves aimed at every Pokémon
 * at once (Haze, Perish Song). Mold Breaker ignores it (W2U_IsLaterIgnorableAbility, resident/mold_breaker.c). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerGoodAsGoldNoEffect(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u16 move;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || W2U_Attacker() == monId) {
        return;
    }
    move = W2U_Move();
    if (W2U_IsStatusMove(move) && W2U_TargetsPokemon(move)) {
        W2U_BlockMove(flow, monId);
    }
}

W2U_HANDLER_TABLE(GoodAsGoldHandlers) = {
    { EVENT_CHECK_NO_EFFECT, HandlerGoodAsGoldNoEffect },
};
W2U_MECHANIC(ABILITY, ABIL_GOOD_AS_GOLD, GoodAsGoldHandlers);
