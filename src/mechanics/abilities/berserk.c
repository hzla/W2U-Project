/* Berserk, Anger Shell (Gen 7, 9): when a move's hits take the holder from above half its max HP to half or less,
 * its row's stat changes apply (Showdown: checked once after the whole move, so a multi-hit move counts its total;
 * not for its own moves; not after a move whose secondary effects Sheer Force removed: the engine then skips
 * EVENT_AFTER_MOVE_HITS). Berserk: Sp. Atk +1. Anger Shell: Attack, Sp. Atk, Speed +1, Defense, Sp. Def -1 (one
 * popup). The HP before the move is taken when every other Pokémon's move starts (fixed-damage moves skip the damage
 * events) and compared after its hits when the holder is among the targets. A substitute takes the hits: the HP
 * doesn't change, nothing happens.
 * One table for both (registry name BerserkHandlers; Black 2's baseline copy keeps W2U's earlier per-hit Berserk). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

typedef struct {
    u16 ability;
    u8 count;
    u8 stats[5];
    s8 stages[5];
} AngerShellRow;

static const AngerShellRow sAngerShellRows[] = {
    { ABIL_BERSERK, 1, { STATSTAGE_SPECIAL_ATTACK }, { 1 } },
    { ABIL_ANGER_SHELL, 5,
      { STATSTAGE_ATTACK, STATSTAGE_SPECIAL_ATTACK, STATSTAGE_SPEED, STATSTAGE_DEFENSE, STATSTAGE_SPECIAL_DEFENSE },
      { 1, 1, 1, -1, -1 } },
};

/* Per Pokémon: a move by another Pokémon started, and the HP then (module state, as MegaB2W2 kept it) */
static b32 sAngerShellArmed[BATTLE_MAX_MON_ID];
static u16 sAngerShellHPBefore[BATTLE_MAX_MON_ID];

/* The current and max HP (MegaB2W2 took the smaller and the larger of the two values) */
static void AngerShellHP(BattleMon *mon, u32 *current, u32 *max)
{
    u32 a = GetBattleMonStat(mon, BMV_HP), b = GetBattleMonStat(mon, BMV_MAX_HP);

    *current = a < b ? a : b;
    *max = a < b ? b : a;
}

static void HandlerAngerShellMoveStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 current, max;

    (void)item;
    (void)work;
    if (monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    sAngerShellArmed[monId] = W2U_Attacker() != monId;
    if (!sAngerShellArmed[monId]) {
        return;
    }
    AngerShellHP(GetBattleMon(flow, monId), &current, &max);
    sAngerShellHPBefore[monId] = (u16)current;
}

static void HandlerAngerShellAfterHits(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 current, max, before, i, j;
    u16 ability;

    (void)item;
    (void)work;
    if (monId >= BATTLE_MAX_MON_ID || !sAngerShellArmed[monId]) {
        return;
    }
    sAngerShellArmed[monId] = 0;
    if (W2U_Attacker() == monId || !HandlerTargetsContain(monId)) {
        return;
    }
    AngerShellHP(GetBattleMon(flow, monId), &current, &max);
    before = sAngerShellHPBefore[monId];
    if (current == 0 || current * 2 > max || before * 2 <= max) {
        return;
    }
    ability = W2U_HolderAbility(flow, monId);
    for (i = 0; i < NELEMS(sAngerShellRows); ++i) {
        const AngerShellRow *row = &sAngerShellRows[i];
        if (row->ability != ability) {
            continue;
        }
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
        for (j = 0; j < row->count; ++j) {
            W2U_ChangeStatStage(flow, monId, monId, row->stats[j], row->stages[j], 0);
        }
        BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    }
}

W2U_HANDLER_TABLE(BerserkHandlers) = {
    { EVENT_MOVE_START, HandlerAngerShellMoveStart },
    { EVENT_AFTER_MOVE_HITS, HandlerAngerShellAfterHits },
};
W2U_MECHANIC(ABILITY, ABIL_BERSERK, BerserkHandlers);
W2U_MECHANIC(ABILITY, ABIL_ANGER_SHELL, BerserkHandlers);
