/* Grim Neigh, As One (Gen 8): KOing Pokémon with a move raises a stat by 1 per KO, as Moxie (one stat change per
 * fainted target, inside the popup).
 *   Grim Neigh             Sp. Atk
 *   As One (Glastrier)     Attack (Unnerve + Chilling Neigh)
 *   As One (Spectrier)     Sp. Atk (Unnerve + Grim Neigh)
 * As One also runs Unnerve's vanilla handlers (the entry message, Berries blocked) and announces "X has two
 * Abilities!" first. Chilling Neigh itself is Moxie's handlers. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

typedef struct {
    u16 ability;
    u8 stat;
    u8 unnerve;                         /* As One: Unnerve too */
} NeighRow;

static const NeighRow sNeighRows[] = {
    { ABIL_GRIM_NEIGH, STATSTAGE_SPECIAL_ATTACK, 0 },
    { ABIL_AS_ONE_GLASTRIER, STATSTAGE_ATTACK, 1 },
    { ABIL_AS_ONE_SPECTRIER, STATSTAGE_SPECIAL_ATTACK, 1 },
};

static const NeighRow *NeighRowOf(BtlServerFlow *flow, u8 monId)
{
    u16 ability = W2U_HolderAbility(flow, monId);
    u32 i;

    for (i = 0; i < NELEMS(sNeighRows); ++i) {
        if (sNeighRows[i].ability == ability) {
            return &sNeighRows[i];
        }
    }
    return 0;
}

static void HandlerNeighKO(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    const NeighRow *row;
    u32 count, i;

    (void)item;
    (void)work;
    if (W2U_Attacker() != monId || (row = NeighRowOf(flow, monId)) == 0) {
        return;
    }
    count = BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (i = 0; i < count; ++i) {
        if (W2U_IsFainted(flow, (u8)BattleEventVar_GetValue(VAR_TARGET0 + i))) {
            W2U_ChangeStatStage(flow, monId, monId, row->stat, 1, 1);
        }
    }
}

/* Unnerve's handlers announce once (work[0] = 1 after its message); a refresh can come before the holder's entry at
 * the battle's start, so "two Abilities" goes with whichever announces first */
static void NeighAsOne(BtlServerFlow *flow, u8 monId, s32 *work)
{
    if (!work[0]) {
        W2U_PopupMessage(flow, monId, BTLMSG_SET_AS_ONE);
    }
}

static void HandlerNeighMemberIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    const NeighRow *row = NeighRowOf(flow, monId);

    if (!row || !row->unnerve || W2U_Subject() != monId) {
        return;
    }
    NeighAsOne(flow, monId, work);
    HandlerUnnerveMemberIn(item, flow, monId, work);
}

static void HandlerNeighUnnerve(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    const NeighRow *row = NeighRowOf(flow, monId);

    if (!row || !row->unnerve) {
        return;
    }
    NeighAsOne(flow, monId, work);
    HandlerUnnerveRotationIn(item, flow, monId, work);
}

W2U_HANDLER_TABLE(NeighHandlers) = {
    { EVENT_AFTER_KO, HandlerNeighKO },
    { EVENT_SWITCH_IN, HandlerNeighMemberIn },
    { EVENT_BEFORE_SWITCH_IN_BATCH, HandlerNeighUnnerve },
    { EVENT_REFRESH_ACTIVATION, HandlerNeighUnnerve },
};
W2U_MECHANIC(ABILITY, ABIL_GRIM_NEIGH, NeighHandlers);
W2U_MECHANIC(ABILITY, ABIL_AS_ONE_GLASTRIER, NeighHandlers);
W2U_MECHANIC(ABILITY, ABIL_AS_ONE_SPECTRIER, NeighHandlers);
