/* Table-driven boosts: the holder's moves that match a row get the row's ratio, one handler per event.
 *   Sharpness                                   slicing moves (W2U's move flag): power x1.5
 *   Transistor                                  Electric moves: the attacking stat x1.3 (Gen 9; Gen 8 x1.5)
 *   Dragon's Maw, Rocky Payload, Fire Mane (Z-A)  Dragon / Rock / Fire moves: the attacking stat x1.5
 * MegaB2W2's table also had rows for Tough Claws, Strong Jaw, Mega Launcher and Steelworker, which keep W2U's own
 * handlers (w2u_abilities.cpp); those rows were never reached and are gone. A new member: one row and its scenario. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

enum { BOOST_POWER, BOOST_ATTACKING_STAT };       /* which event, and so VAR_MOVE_POWER_RATIO or VAR_RATIO */
enum { BOOST_MATCH_MOVE_FLAG, BOOST_MATCH_TYPE };

typedef struct {
    u16 ability;
    u8 event;
    u8 match;
    u8 param;                           /* the move flag or the type */
    u16 ratio;
} BoostRow;

static const BoostRow sBoostRows[] = {
    { ABIL_SHARPNESS, BOOST_POWER, BOOST_MATCH_MOVE_FLAG, MOVE_FLAG_SLICING, 6144 },
    { ABIL_TRANSISTOR, BOOST_ATTACKING_STAT, BOOST_MATCH_TYPE, TYPE_ELECTRIC, 5325 },
    { ABIL_DRAGONS_MAW, BOOST_ATTACKING_STAT, BOOST_MATCH_TYPE, TYPE_DRAGON, 6144 },
    { ABIL_ROCKY_PAYLOAD, BOOST_ATTACKING_STAT, BOOST_MATCH_TYPE, TYPE_ROCK, 6144 },
    { ABIL_FIRE_MANE, BOOST_ATTACKING_STAT, BOOST_MATCH_TYPE, TYPE_FIRE, 6144 },
};

static void BoostApply(BtlServerFlow *flow, u8 monId, u8 event, u16 var)
{
    u16 ability, move;
    u32 i;

    if (W2U_Attacker() != monId) {
        return;
    }
    ability = W2U_HolderAbility(flow, monId);
    move = W2U_Move();
    for (i = 0; i < NELEMS(sBoostRows); ++i) {
        const BoostRow *row = &sBoostRows[i];
        if (row->ability != ability || row->event != event) {
            continue;
        }
        if (row->match == BOOST_MATCH_MOVE_FLAG ? W2U_MoveHasFlag(move, row->param) : W2U_MoveType() == row->param) {
            BattleEventVar_MulValue(var, row->ratio);
        }
        return;
    }
}

static void HandlerBoostMovePower(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    BoostApply(flow, monId, BOOST_POWER, VAR_MOVE_POWER_RATIO);
}

static void HandlerBoostAttackingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    BoostApply(flow, monId, BOOST_ATTACKING_STAT, VAR_RATIO);
}

W2U_HANDLER_TABLE(BoostHandlers) = {
    { EVENT_MOVE_POWER, HandlerBoostMovePower },
    { EVENT_ATTACKING_STAT, HandlerBoostAttackingStat },
};
W2U_MECHANIC(ABILITY, ABIL_TRANSISTOR, BoostHandlers);
W2U_MECHANIC(ABILITY, ABIL_DRAGONS_MAW, BoostHandlers);
W2U_MECHANIC(ABILITY, ABIL_ROCKY_PAYLOAD, BoostHandlers);
W2U_MECHANIC(ABILITY, ABIL_SHARPNESS, BoostHandlers);
W2U_MECHANIC(ABILITY, ABIL_FIRE_MANE, BoostHandlers);
