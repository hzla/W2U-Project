/* Mirror Armor (Gen 8): a stat drop from another Pokémon (moves, Intimidate, secondary effects) is blocked and the
 * same drop hits that Pokémon instead (Showdown). Clear Body's check (EVENT_STAT_CHANGE_CHECK: VAR_MON_ID the
 * target, VAR_ATTACKING_MON the source, VAR_STAT, VAR_STAT_CHANGE < 0 -> VAR_FAIL_FLAG) remembers the drop; the guard
 * event pushes the popup and the reflected drop. A reflected drop is not reflected again (Showdown: the effect is
 * Mirror Armor itself): the source is marked until the next move or switch-in. Mold Breaker ignores it
 * (IsMoldBreakerAffectedAbility in w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MIRROR_ARMOR_NO_SOURCE 0x1F

/* The Pokémon is receiving a reflected drop (module state, as MegaB2W2 kept it) */
static b32 sMirrorArmorReflected[BATTLE_MAX_MON_ID];

static void HandlerMirrorArmorClear(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 i;

    (void)item;
    (void)flow;
    (void)monId;
    (void)work;
    for (i = 0; i < BATTLE_MAX_MON_ID; ++i) {
        sMirrorArmorReflected[i] = 0;
    }
}

static void HandlerMirrorArmorCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 source;
    s32 stages;

    (void)item;
    (void)flow;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID || sMirrorArmorReflected[monId]) {
        return;
    }
    source = W2U_Attacker();
    stages = (s32)BattleEventVar_GetValue(VAR_STAT_CHANGE);
    if (source == monId || source == MIRROR_ARMOR_NO_SOURCE || stages >= 0) {
        return;
    }
    work[0] = BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1);
    work[1] = (s32)BattleEventVar_GetValue(VAR_STAT);
    work[2] = stages;
    work[3] = source;
}

static void HandlerMirrorArmorGuard(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 source;

    (void)item;
    if (W2U_Subject() != monId || !work[0]) {
        return;
    }
    work[0] = 0;
    source = (u8)work[3];
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    if (W2U_OnField(flow, source) && !W2U_IsFainted(flow, source)) {
        sMirrorArmorReflected[source] = 1;
        W2U_ChangeStatStage(flow, monId, source, (u32)work[1], work[2], 0);
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

W2U_HANDLER_TABLE(MirrorArmorHandlers) = {
    { EVENT_STAT_CHANGE_CHECK, HandlerMirrorArmorCheck },
    { EVENT_STAT_CHANGE_GUARD, HandlerMirrorArmorGuard },
    { EVENT_MOVE_START, HandlerMirrorArmorClear },
    { EVENT_SWITCH_IN, HandlerMirrorArmorClear },
};
W2U_MECHANIC(ABILITY, ABIL_MIRROR_ARMOR, MirrorArmorHandlers);
