/* Unseen Fist (Gen 8), Piercing Drill (Legends: Z-A): the holder's contact moves go through Protect and its variants
 * (Showdown: they lose the protect flag, so Mat Block and the damage shields don't stop them either). Piercing Drill:
 * the same, but a hit that went through protection does 1/4 damage.
 * W2U's protection check (flowsub_CheckNoEffect_Protect in w2u_moves.cpp) raises EVENT_PROTECT_BREAK_CHECK for each
 * target, with the attacker, the target and the move: VAR_BREAK_PROTECT 1 = broken (Feint's effect, the protection
 * ends), 2 = it goes through and the protection stays. The holder answers 2, unless something already answered. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define UNSEEN_FIST_PASS_THROUGH 2
#define PIERCING_DRILL_RATIO 1024       /* x0.25 */

/* Per Piercing Drill holder: the targets it hit through protection during its move (bits; module state) */
static u32 sUnseenFistPierced[BATTLE_MAX_MON_ID];

static void HandlerUnseenFistBreakCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 target;
    u16 move;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    target = W2U_Defender();
    move = W2U_Move();
    if (target >= BATTLE_MAX_MON_ID || !W2U_MakesContact(flow, move)) {
        return;
    }
    if (BattleEventVar_GetValue(VAR_BREAK_PROTECT) != 0) {
        return;
    }
    BattleEventVar_RewriteValue(VAR_BREAK_PROTECT, UNSEEN_FIST_PASS_THROUGH);
    if (W2U_HolderAbility(flow, monId) == ABIL_PIERCING_DRILL
        && GetTurnFlag(GetBattleMon(flow, target), TURN_FLAG_PROTECT)) {
        sUnseenFistPierced[monId] |= 1u << target;
    }
}

static void HandlerUnseenFistMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() == monId && monId < BATTLE_MAX_MON_ID) {
        sUnseenFistPierced[monId] = 0;
    }
}

static void HandlerUnseenFistDamageRatio(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 defender;

    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    defender = W2U_Defender();
    if (defender < 32 && (sUnseenFistPierced[monId] & (1u << defender))) {
        W2U_MulRatio(PIERCING_DRILL_RATIO);
    }
}

W2U_HANDLER_TABLE(UnseenFistHandlers) = {
    { EVENT_PROTECT_BREAK_CHECK, HandlerUnseenFistBreakCheck },
    { EVENT_MOVE_START, HandlerUnseenFistMoveStart },
    { EVENT_DAMAGE_RATIO, HandlerUnseenFistDamageRatio },
};
W2U_MECHANIC(ABILITY, ABIL_UNSEEN_FIST, UnseenFistHandlers);
W2U_MECHANIC(ABILITY, ABIL_PIERCING_DRILL, UnseenFistHandlers);
