/* Supreme Overlord (Gen 9): on entering, it counts its party's fainted members (at most 5); its moves' power is x1.1
 * per member (Showdown's table: 4096, 4506, 4915, 5325, 5734, 6144) until it leaves. The popup and "X gained strength
 * from the fallen!" when the count is above 0. Eggs are not fallen. The count is module state, fresh every battle. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define SUPREME_OVERLORD_MAX_FALLEN 5

static const u16 sSupremeOverlordPower[SUPREME_OVERLORD_MAX_FALLEN + 1] = { 4096, 4506, 4915, 5325, 5734, 6144 };

static u8 sSupremeOverlordFallen[BATTLE_MAX_MON_ID];

static u32 SupremeOverlordCountFallen(BtlServerFlow *flow, u8 monId)
{
    BattleParty *party = W2U_PartyOf(flow, monId);
    u32 fallen = 0, i;

    for (i = 0; i < party->count && i < 6; ++i) {
        BattleMon *mon = party->mons[i];
        if (!mon || !IsFainted(mon)) {
            continue;
        }
        if (PokeParty_GetParam(W2U_BattleMonSource(mon), PKM_PARAM_IS_EGG, 0)) {
            continue;
        }
        ++fallen;
    }
    return fallen > SUPREME_OVERLORD_MAX_FALLEN ? SUPREME_OVERLORD_MAX_FALLEN : fallen;
}

static void HandlerSupremeOverlordStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 fallen;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    fallen = SupremeOverlordCountFallen(flow, monId);
    sSupremeOverlordFallen[monId] = (u8)fallen;
    if (fallen) {
        W2U_PopupMessage(flow, monId, BTLMSG_SET_SUPREME_OVERLORD);
    }
}

static void HandlerSupremeOverlordMovePower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 fallen;

    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    fallen = sSupremeOverlordFallen[monId];
    if (fallen) {
        W2U_MulMovePower(sSupremeOverlordPower[fallen]);
    }
}

W2U_HANDLER_TABLE(SupremeOverlordHandlers) = {
    { EVENT_SWITCH_IN, HandlerSupremeOverlordStart },
    { EVENT_AFTER_ABILITY_CHANGE, HandlerSupremeOverlordStart },
    { EVENT_MOVE_POWER, HandlerSupremeOverlordMovePower },
};
W2U_MECHANIC(ABILITY, ABIL_SUPREME_OVERLORD, SupremeOverlordHandlers);
