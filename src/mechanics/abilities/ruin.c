/* The Ruin abilities (Gen 9): while the holder is on the field, every other Pokémon's stat is x0.75 in the damage
 * calculation.
 *   Sword of Ruin    Defense (when the defending stat is Defense: Psyshock too)
 *   Beads of Ruin    Sp. Def (the other case)
 *   Tablets of Ruin  Attack (physical moves' attacking stat)
 *   Vessel of Ruin   Sp. Atk (special moves')
 * Showdown: Pokémon with the same Ruin ability aren't affected, and two holders still give x0.75 once (only the
 * lowest monId's handler acts). On entering: the popup and "X weakened the <stat> of all surrounding Pokémon!". */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define RUIN_RATIO 3072                 /* x0.75 */

enum { RUIN_ATTACKER, RUIN_DEFENDER };

typedef struct {
    u16 ability;
    u8 side;                            /* whose stat: the attacker's or the defender's */
    u8 category;                        /* the hit's: MOVE_CATEGORY_PHYSICAL / SPECIAL */
    u16 message;
} RuinRow;

static const RuinRow sRuinRows[] = {
    { ABIL_SWORD_OF_RUIN, RUIN_DEFENDER, MOVE_CATEGORY_PHYSICAL, BTLMSG_SET_RUIN_DEFENSE },
    { ABIL_BEADS_OF_RUIN, RUIN_DEFENDER, MOVE_CATEGORY_SPECIAL, BTLMSG_SET_RUIN_SP_DEF },
    { ABIL_TABLETS_OF_RUIN, RUIN_ATTACKER, MOVE_CATEGORY_PHYSICAL, BTLMSG_SET_RUIN_ATTACK },
    { ABIL_VESSEL_OF_RUIN, RUIN_ATTACKER, MOVE_CATEGORY_SPECIAL, BTLMSG_SET_RUIN_SP_ATK },
};

static const RuinRow *RuinRowFor(BtlServerFlow *flow, u8 monId)
{
    u16 ability = W2U_HolderAbility(flow, monId);
    u32 i;

    for (i = 0; i < NELEMS(sRuinRows); ++i) {
        if (sRuinRows[i].ability == ability) {
            return &sRuinRows[i];
        }
    }
    return 0;
}

static void HandlerRuinStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    const RuinRow *row;

    (void)item;
    (void)work;
    if (W2U_Subject() == monId && (row = RuinRowFor(flow, monId)) != 0) {
        W2U_PopupMessage(flow, monId, row->message);
    }
}

/* Lowers target's stat for a hit of this category, if the holder's row covers it */
static void RuinApply(BtlServerFlow *flow, u8 monId, u8 side, u8 target, u32 category)
{
    const RuinRow *row = RuinRowFor(flow, monId);

    if (!row || row->side != side || row->category != category || target == monId) {
        return;
    }
    if (W2U_HasActiveAbility(GetBattleMon(flow, target), row->ability)) {
        return;
    }
    if (W2U_FirstFieldHolder(flow, row->ability) != monId) {
        return;
    }
    W2U_MulRatio(RUIN_RATIO);
}

static void HandlerRuinDefendingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 category = BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1 ? MOVE_CATEGORY_PHYSICAL : MOVE_CATEGORY_SPECIAL;

    (void)item;
    (void)work;
    RuinApply(flow, monId, RUIN_DEFENDER, W2U_Defender(), category);
}

static void HandlerRuinAttackingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    RuinApply(flow, monId, RUIN_ATTACKER, W2U_Attacker(), W2U_MoveCategory(W2U_Move()));
}

W2U_HANDLER_TABLE(RuinHandlers) = {
    { EVENT_SWITCH_IN, HandlerRuinStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerRuinStart },
    { EVENT_DEFENDING_STAT, HandlerRuinDefendingStat },
    { EVENT_ATTACKING_STAT, HandlerRuinAttackingStat },
};
W2U_MECHANIC(ABILITY, ABIL_VESSEL_OF_RUIN, RuinHandlers);
W2U_MECHANIC(ABILITY, ABIL_SWORD_OF_RUIN, RuinHandlers);
W2U_MECHANIC(ABILITY, ABIL_TABLETS_OF_RUIN, RuinHandlers);
W2U_MECHANIC(ABILITY, ABIL_BEADS_OF_RUIN, RuinHandlers);
