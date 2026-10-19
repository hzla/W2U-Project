/* Parental Bond: a single-target move of the ability's holder hits twice, the second hit at a quarter of the damage.
 * DamageRoot asks W2U_CheckMultihitHits instead of ServerEvent_CheckMultihitHits: a move that isn't multi-hit
 * already becomes two hits (not rolled per hit) and the state below is set. The ability's handlers
 * (mechanics/abilities/parental_bond.c) count the hits on EVENT_MOVE_POWER and cut the second's damage. Was
 * w2u_abilities.cpp's (ParentalBondCheck, the ability state's parentalBond fields). */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define MOVE_SELFDESTRUCT 120           /* vanilla (Moves.h) */
#define MOVE_EXPLOSION 153
#define MOVE_ROLLOUT 205
#define MOVE_UPROAR 253
#define MOVE_ENDEAVOR 283
#define MOVE_ICE_BALL 301
#define MOVE_FLING 374
#define MOVE_FINAL_GAMBIT 515
#define MOVE_MISTY_EXPLOSION 802        /* W2U's */
#define MOVE_FLAG_INDEX_REQUIRES_CHARGE 1   /* two-turn moves (w2u_abilities.h) */

static u8 sActive;                      /* the current move is a Parental Bond double hit */
static u8 sPowerHit;                    /* its hits so far, as EVENT_MOVE_POWER counted them */

static b32 IgnoresParentalBond(u16 move)
{
    switch (move) {
    case MOVE_FLING:
    case MOVE_SELFDESTRUCT:
    case MOVE_EXPLOSION:
    case MOVE_MISTY_EXPLOSION:
    case MOVE_FINAL_GAMBIT:
    case MOVE_UPROAR:
    case MOVE_ROLLOUT:
    case MOVE_ICE_BALL:
    case MOVE_ENDEAVOR:
        return 1;
    default:
        return 0;
    }
}

b32 W2U_ParentalBondApplies(BtlServerFlow *flow, u16 move, BattleMon *attacker, void *targets)
{
    BtlFlowMoveParam param;

    if (!flow || !attacker || !targets || move == 0 ||
        GetBattleMonStat(attacker, BMV_EFFECTIVE_ABILITY) != ABIL_PARENTAL_BOND || W2U_TargetSetCount(targets) != 1) {
        return 0;
    }
    ServerEvent_GetMoveParam(flow, move, attacker, &param);
    return !(param.targetType == MOVE_TARGET_USER || param.targetType == MOVE_TARGET_FIELD ||
             param.targetType == MOVE_TARGET_FOE_SIDE || param.targetType == MOVE_TARGET_USER_SIDE ||
             getMoveFlag(param.move, MOVE_FLAG_INDEX_REQUIRES_CHARGE) || IgnoresParentalBond(param.move));
}

void W2U_CheckMultihitHits(BtlServerFlow *flow, BattleMon *attacker, u16 move, void *hitWork)
{
    W2U_HitWork *hit = (W2U_HitWork *)hitWork;

    ServerEvent_CheckMultihitHits(flow, attacker, move, hitWork);
    sActive = 0;
    sPowerHit = 0;
    if (!flow || !hit || hit->multiHitMove) {
        return;
    }
    if (W2U_ParentalBondApplies(flow, move, attacker, W2U_OriginalTargets(flow))) {
        hit->countMax = 2;
        hit->checkEveryTime = 0;
        hit->multiHitMove = 1;
        sActive = 1;
    }
}

b32 W2U_ParentalBondActive(void)
{
    return sActive;
}

u32 W2U_ParentalBondCountHit(void)
{
    return sActive ? ++sPowerHit : 0;
}

u32 W2U_ParentalBondHit(void)
{
    return sPowerHit;
}

void W2U_Resident_ResetParentalBond(void)
{
    sActive = 0;
    sPowerHit = 0;
}
