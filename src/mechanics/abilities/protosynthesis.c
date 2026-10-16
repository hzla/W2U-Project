/* Protosynthesis, Quark Drive (Gen 9): in harsh sunlight / on Electric Terrain, or without it by using up a held
 * Booster Energy, the holder's highest stat is boosted: x1.3, Speed x1.5 (Showdown). Sun as abilities see it
 * (GetWeather: Air Lock reads as none; Desolate Land's extreme sun counts); the terrain W2U's, grounded or not.
 * A sun boost ends when the sun does (then a held Booster Energy is used); a Booster boost lasts until the holder
 * leaves. Checked when it enters or gains the ability, when anyone enters (weather setters), after every action (Sunny
 * Day) and at the end of the turn (the sun running out). The best stat is taken at activation and kept until the boost
 * ends. Booster Energy is used up through the handler effect (its animation; it counts as used: Recycle, Unburden).
 * The state is cleared when the holder leaves; not on entry, since the holder's switch-in can come twice at the
 * battle's start, and a reset there lost a Booster boost (the item already used). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

typedef struct {
    u16 ability;
    u16 messageOn;                      /* the condition's activation message */
    u16 messageBooster;
    u16 messageEnd;
} ProtosynthesisRow;

static const ProtosynthesisRow sProtosynthesisRows[] = {
    { ABIL_PROTOSYNTHESIS, BTLMSG_SET_PROTO_SUN, BTLMSG_SET_PROTO_BOOSTER, BTLMSG_SET_PROTO_END },
    { ABIL_QUARK_DRIVE, BTLMSG_SET_QUARK_TERRAIN, BTLMSG_SET_QUARK_BOOSTER, BTLMSG_SET_QUARK_END },
};

static const u16 sProtosynthesisStatMessages[5] = {
    BTLMSG_SET_PROTO_ATTACK, BTLMSG_SET_PROTO_DEFENSE, BTLMSG_SET_PROTO_SP_ATK, BTLMSG_SET_PROTO_SP_DEF,
    BTLMSG_SET_PROTO_SPEED,
};

/* Per Pokémon: the boosted stat (0: none) and whether Booster Energy gave it */
typedef struct {
    u8 stat;
    u8 booster;
} ProtosynthesisState;

static ProtosynthesisState sProtosynthesisState[BATTLE_MAX_MON_ID];

static const ProtosynthesisRow *ProtosynthesisRowOf(BtlServerFlow *flow, u8 monId)
{
    return W2U_HolderAbility(flow, monId) == ABIL_QUARK_DRIVE ? &sProtosynthesisRows[1] : &sProtosynthesisRows[0];
}

static b32 ProtosynthesisCondition(BtlServerFlow *flow, u8 monId)
{
    if (W2U_HolderAbility(flow, monId) == ABIL_QUARK_DRIVE) {
        return W2U_Terrain() == W2U_TERRAIN_ELECTRIC;
    }
    return GetWeather(flow) == WEATHER_SUN;
}

/* The highest of Attack .. Speed, as MegaB2W2's BestStatWithStages computes it: GetBattleMonStat's stats (which
 * already include the stat stages) with the stages applied again. Kept as it was; Showdown applies them once. */
static u32 ProtosynthesisBestStat(BattleMon *mon)
{
    u32 best = STATSTAGE_ATTACK, bestValue = 0, i;

    for (i = 0; i < 5; ++i) {
        s32 stage = (s32)GetBattleMonStat(mon, STATSTAGE_ATTACK + i) - STATSTAGE_NEUTRAL;
        u32 value = GetBattleMonStat(mon, BMV_ATTACK + i);
        /* u64: a u32 division by a variable calls __aeabi_uidiv, which the ESDB lacks */
        value = stage >= 0 ? value * (u32)(2 + stage) / 2 : (u32)((u64)value * 2 / (u32)(2 - stage));
        if (value > bestValue) {
            bestValue = value;
            best = STATSTAGE_ATTACK + i;
        }
    }
    return best;
}

static void ProtosynthesisActivate(BtlServerFlow *flow, u8 monId, b32 booster)
{
    u32 stat = ProtosynthesisBestStat(GetBattleMon(flow, monId));

    sProtosynthesisState[monId].stat = (u8)stat;
    sProtosynthesisState[monId].booster = (u8)booster;
    if (booster) {
        BattleHandlerConsumeItemParam *param =
            (BattleHandlerConsumeItemParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CONSUME_ITEM, monId);
        param->skipDisplay = 0;
        BattleHandler_StrSetup(&param->string, HANDLER_STR_SET, ProtosynthesisRowOf(flow, monId)->messageBooster);
        BattleHandler_AddArg(&param->string, monId);
        BattleHandler_PopWork(flow, param);
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    if (!booster) {
        W2U_Message(flow, monId, ProtosynthesisRowOf(flow, monId)->messageOn);
    }
    W2U_Message(flow, monId, sProtosynthesisStatMessages[stat - STATSTAGE_ATTACK]);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerProtosynthesisCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    ProtosynthesisState *state;
    BattleMon *mon;
    b32 condition;

    (void)item;
    (void)work;
    if (monId >= BATTLE_MAX_MON_ID || !W2U_OnField(flow, monId)) {
        return;
    }
    mon = GetBattleMon(flow, monId);
    if (IsFainted(mon)) {
        return;
    }
    condition = ProtosynthesisCondition(flow, monId);
    state = &sProtosynthesisState[monId];
    if (state->stat && !state->booster && !condition) {
        state->stat = 0;
        W2U_Message(flow, monId, ProtosynthesisRowOf(flow, monId)->messageEnd);
    }
    if (state->stat) {
        return;
    }
    if (condition) {
        ProtosynthesisActivate(flow, monId, 0);
    } else if (GetBattleMonHeldItem(mon) == ITEM_BOOSTER_ENERGY) {
        ProtosynthesisActivate(flow, monId, 1);
    }
}

static void HandlerProtosynthesisLeave(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() == monId && monId < BATTLE_MAX_MON_ID) {
        sProtosynthesisState[monId].stat = 0;
    }
}

static void HandlerProtosynthesisAttackingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u32 category, stat;

    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Attacker() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    category = W2U_MoveCategory(W2U_Move());
    stat = sProtosynthesisState[monId].stat;
    if ((category == MOVE_CATEGORY_PHYSICAL && stat == STATSTAGE_ATTACK)
        || (category == MOVE_CATEGORY_SPECIAL && stat == STATSTAGE_SPECIAL_ATTACK)) {
        W2U_MulRatio(5325);             /* x1.3 */
    }
}

static void HandlerProtosynthesisDefendingStat(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    b32 physical;
    u32 stat;

    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Defender() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    physical = BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1;
    stat = sProtosynthesisState[monId].stat;
    if ((physical && stat == STATSTAGE_DEFENSE) || (!physical && stat == STATSTAGE_SPECIAL_DEFENSE)) {
        W2U_MulRatio(5325);
    }
}

static void HandlerProtosynthesisSpeed(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    if (sProtosynthesisState[monId].stat == STATSTAGE_SPEED) {
        W2U_MulRatio(6144);             /* x1.5 */
    }
}

W2U_HANDLER_TABLE(ProtosynthesisHandlers) = {
    { EVENT_SWITCH_IN, HandlerProtosynthesisCheck },    /* anyone entering may have set the weather */
    { EVENT_AFTER_ABILITY_CHANGE, HandlerProtosynthesisCheck },
    { EVENT_ACTION_END, HandlerProtosynthesisCheck },
    { EVENT_TURN_CHECK, HandlerProtosynthesisCheck },
    { EVENT_SWITCH_OUT_END, HandlerProtosynthesisLeave },
    { EVENT_BEFORE_ABILITY_CHANGE, HandlerProtosynthesisLeave },
    { EVENT_ABILITY_NULLIFIED, HandlerProtosynthesisLeave },
    { EVENT_NOTIFY_FAINTED, HandlerProtosynthesisLeave },
    { EVENT_ATTACKING_STAT, HandlerProtosynthesisAttackingStat },
    { EVENT_DEFENDING_STAT, HandlerProtosynthesisDefendingStat },
    { EVENT_CALC_SPEED, HandlerProtosynthesisSpeed },
};
W2U_MECHANIC(ABILITY, ABIL_PROTOSYNTHESIS, ProtosynthesisHandlers);
W2U_MECHANIC(ABILITY, ABIL_QUARK_DRIVE, ProtosynthesisHandlers);
