/* Mold Breaker's skip check (the decomp's HandlerMoldBreakerSkipCheck, W2U's HandlerMoldBreakerSkipCheck), replaced whole:
 * while Mold Breaker, Teravolt, Turboblaze, Moongeist Beam or Mycelium Might work, the target's ability handlers are
 * skipped when the native Gen 4-5 list has the ability, or when it is one of the later-generation abilities the games
 * also let them ignore. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define ABIL_OVERCOAT 142               /* vanilla (w2u_abilities.h has it as a C++ enumerator) */
#define FACTOR_ABILITY 4                /* the event factor type of an ability's handlers */

/* The later abilities Mold Breaker ignores */
b32 W2U_IsLaterIgnorableAbility(u16 ability)
{
    switch (ability) {
    /* Generation VI */
    case ABIL_OVERCOAT:                 /* its powder immunity was added after the native table */
    case ABIL_AURA_BREAK:
    case ABIL_AROMA_VEIL:
    case ABIL_BULLETPROOF:
    case ABIL_DARK_AURA:
    case ABIL_FAIRY_AURA:
    case ABIL_FLOWER_VEIL:
    case ABIL_FUR_COAT:
    case ABIL_GRASS_PELT:
    case ABIL_SWEET_VEIL:
    /* Generation VII */
    case ABIL_DAZZLING:
    case ABIL_DISGUISE:
    case ABIL_FLUFFY:
    case ABIL_QUEENLY_MAJESTY:
    case ABIL_WATER_BUBBLE:
    /* Generation VIII / IX (ported from MegaB2W2; Showdown's `breakable` flag) */
    case ABIL_ICE_FACE:
    case ABIL_MIRROR_ARMOR:
    case ABIL_PUNK_ROCK:
    case ABIL_ICE_SCALES:
    case ABIL_PASTEL_VEIL:
    case ABIL_THERMAL_EXCHANGE:
    case ABIL_PURIFYING_SALT:
    case ABIL_WELL_BAKED_BODY:
    case ABIL_WIND_RIDER:
    case ABIL_GUARD_DOG:
    case ABIL_GOOD_AS_GOLD:
    case ABIL_ARMOR_TAIL:
    case ABIL_EARTH_EATER:
    case ABIL_MINDS_EYE:
    case ABIL_TERA_SHELL:
    /* MegaB2W2 custom */
    case ABIL_AURA_GUARD:
        return 1;
    default:
        return 0;
    }
}

b32 W2U_MoldBreakerSkipCheck(BattleEventItem *item, BtlServerFlow *flow, u32 factorType, u32 eventType, u32 subId)
{
    (void)item;
    (void)flow;
    (void)eventType;
    return factorType == FACTOR_ABILITY &&
           (IsMoldBreakerIgnoredAbility((u16)subId) || W2U_IsLaterIgnorableAbility((u16)subId));
}
