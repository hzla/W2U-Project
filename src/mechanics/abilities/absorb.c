/* Absorbing abilities built on the vanilla ones' helpers (CommonDamageRecoverCheck: moves of a type don't affect
 * the holder):
 *   Earth Eater      Ground moves heal it 1/4 instead (Volt Absorb with Ground)
 *   Well-Baked Body  Fire moves raise its Defense by 2 instead (Sap Sipper with Fire)
 * Mold Breaker ignores both (IsMoldBreakerAffectedAbility in w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

static void HandlerEarthEaterCheckNoEffect(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (CommonDamageRecoverCheck(flow, monId, TYPE_GROUND)) {
        CommonTypeRecoverHP(flow, monId, 4);
    }
}

static void HandlerWellBakedBodyCheckNoEffect(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (CommonDamageRecoverCheck(flow, monId, TYPE_FIRE)) {
        CommonTypeNoEffectRankUp(flow, monId, STATSTAGE_DEFENSE, 2);
    }
}

W2U_HANDLER_TABLE(EarthEaterHandlers) = {
    { EVENT_CHECK_NO_EFFECT, HandlerEarthEaterCheckNoEffect },
};
W2U_MECHANIC(ABILITY, ABIL_EARTH_EATER, EarthEaterHandlers);

W2U_HANDLER_TABLE(WellBakedBodyHandlers) = {
    { EVENT_CHECK_NO_EFFECT, HandlerWellBakedBodyCheckNoEffect },
};
W2U_MECHANIC(ABILITY, ABIL_WELL_BAKED_BODY, WellBakedBodyHandlers);
