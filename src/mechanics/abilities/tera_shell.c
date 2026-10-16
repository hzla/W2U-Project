/* Tera Shell (Gen 9): at full HP, every hit from another Pokémon does not-very-effective damage: the hit's
 * effectiveness is scaled to x0.5 overall ("X made its shell gleam! It's distorting type matchups!" once per move).
 * The engine's own effectiveness text is unchanged. Mold Breaker ignores it (IsMoldBreakerAffectedAbility in
 * w2u_abilities.cpp). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

/* Shown during the current move (module state, as MegaB2W2 kept it) */
static b32 sTeraShellShown[BATTLE_MAX_MON_ID];

static void HandlerTeraShellMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (monId < BATTLE_MAX_MON_ID) {
        sTeraShellShown[monId] = 0;
    }
}

static void HandlerTeraShellDamage(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 effectiveness;
    s32 ratio;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || W2U_Attacker() == monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    if (!IsMonFullHP(GetBattleMon(flow, monId))) {
        return;
    }
    effectiveness = BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS);
    ratio = effectiveness == TYPE_EFFECTIVENESS_X1 ? 2048
          : effectiveness == TYPE_EFFECTIVENESS_X2 ? 1024
          : effectiveness == TYPE_EFFECTIVENESS_X4 ? 512 : W2U_RATIO_ONE;
    if (ratio == W2U_RATIO_ONE) {
        return;
    }
    W2U_MulRatio(ratio);
    if (W2U_IsSimulating(flow) || sTeraShellShown[monId]) {
        return;
    }
    sTeraShellShown[monId] = 1;
    W2U_PopupMessage(flow, monId, BTLMSG_SET_TERA_SHELL);
}

W2U_HANDLER_TABLE(TeraShellHandlers) = {
    { EVENT_MOVE_START, HandlerTeraShellMoveStart },
    { EVENT_DAMAGE_RATIO, HandlerTeraShellDamage },
};
W2U_MECHANIC(ABILITY, ABIL_TERA_SHELL, TeraShellHandlers);
