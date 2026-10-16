/* W2U engine interface, layer B: the battle API W2U's mechanics are written against. C and C++; no addresses and no
 * struct offsets (those live in w2u/engine.h). See docs/engine-interface.md.
 *
 * A mechanic file (src/mechanics/) includes only this header. It defines its handlers static, its handler table with
 * W2U_HANDLER_TABLE and registers the table per ability / item / move with W2U_MECHANIC; the battle module registry
 * (src/pokeweb_gameplay/battle_modules/registry.json) must list the same entries, which its generator checks.
 *
 * The helpers grow from megab2w2/ability_api.h as mechanics are converted. */
#ifndef W2U_BATTLE_API_H
#define W2U_BATTLE_API_H

#include "w2u/engine.h"

/* A mechanic's handler table: W2U_HANDLER_TABLE(FluffyHandlers) = { { EVENT_DAMAGE_RATIO, Handler }, }; */
#define W2U_HANDLER_TABLE(name) W2U_EXTERN_C const BattleEventHandlerEntry name[]

/* Registers a handler table for an ability, item or move (kind: ABILITY, ITEM or MOVE; id: its constant). It declares
 * the table again, so it follows the table's definition; tools/generate_w2u_battle_registry.py reads these lines. */
#define W2U_MECHANIC(kind, id, table) W2U_EXTERN_C const BattleEventHandlerEntry table[]

#define W2U_RATIO_ONE 4096              /* VAR_RATIO's x1 */

W2U_C_BEGIN

/* W2U's own engine extensions (resident in White2Upgrade.dll) */

/* The move makes contact as used now: its contact flag, unless the attacker's Long Reach removes it (Shell Side Arm:
 * when it hits physically). Logic reacting to contact asks this, not the move's flag. */
b32 W2U_MoveMakesContact(BtlServerFlow *flow, u16 move, u32 attacker);

W2U_C_END

/* Who and what the current event is about */
static inline u8 W2U_Subject(void) { return (u8)BattleEventVar_GetValue(VAR_MON_ID); }
static inline u8 W2U_Attacker(void) { return (u8)BattleEventVar_GetValue(VAR_ATTACKING_MON); }
static inline u8 W2U_Defender(void) { return (u8)BattleEventVar_GetValue(VAR_DEFENDING_MON); }
static inline u16 W2U_Move(void) { return (u16)BattleEventVar_GetValue(VAR_MOVE_ID); }
/* The move's type as this hit uses it (after -ate abilities, Weather Ball...) */
static inline u32 W2U_MoveType(void) { return BattleEventVar_GetValue(VAR_MOVE_TYPE); }

/* Pokémon on the same side: a Pokémon is its own ally (IsAllyMonID compares sides) */
static inline b32 W2U_IsAlly(u8 a, u8 b) { return IsAllyMonID(a, b); }

/* Moves */
static inline u32 W2U_MoveCategory(u16 move) { return (u32)PML_MoveGetParam(move, MOVE_PARAM_CATEGORY); }
/* The move record's flag (MOVE_FLAG_SOUND ...); contact as used now: W2U_MakesContact */
static inline b32 W2U_MoveHasFlag(u16 move, u32 flag) { return getMoveFlag(move, flag); }
static inline b32 W2U_IsStatusMove(u16 move) { return W2U_MoveCategory(move) == MOVE_CATEGORY_STATUS; }
/* The move picks Pokémon as targets (one, several, all adjacent foes), not the user, the field, a side or every
 * Pokémon at once (Haze, Perish Song): the moves a "can't be targeted by" ability stops */
static inline b32 W2U_TargetsPokemon(u16 move)
{
    u32 target = (u32)PML_MoveGetParam(move, MOVE_PARAM_TARGET);

    return target <= MOVE_TARGET_ENEMY_ALL || target == MOVE_TARGET_ENEMY_RANDOM;
}
/* The final type of a move as attacker uses it (after -ate abilities, Weather Ball...) */
static inline u32 W2U_FinalMoveType(BtlServerFlow *flow, u16 move, u8 attacker)
{
    BtlFlowMoveParam param = { 0 };

    ServerEvent_GetMoveParam(flow, move, GetBattleMon(flow, attacker), &param);
    return param.type;
}
/* The current event's move makes contact, used by its attacker */
static inline b32 W2U_MakesContact(BtlServerFlow *flow, u16 move)
{
    return W2U_MoveMakesContact(flow, move, W2U_Attacker()) != 0;
}

/* Pokémon */
/* The holder's current ability: table-driven families (one table, several abilities) find their row by it */
static inline u16 W2U_HolderAbility(BtlServerFlow *flow, u8 monId)
{
    return (u16)GetBattleMonStat(GetBattleMon(flow, monId), BMV_ABILITY);
}

static inline b32 W2U_IsFainted(BtlServerFlow *flow, u8 monId) { return IsFainted(GetBattleMon(flow, monId)); }
/* The highest of Attack .. Speed as GetBattleMonStat returns them, stat stages applied, as STATSTAGE_ATTACK ..
 * STATSTAGE_SPEED; ties: the first. MegaB2W2's "BestStat" (Eelevate). Showdown's Beast Boost compares the stats
 * without stages, as w2u_abilities.cpp's GetHighestStatStage does. */
static inline u32 W2U_BestBoostedStat(BtlServerFlow *flow, u8 monId)
{
    BattleMon *mon = GetBattleMon(flow, monId);
    u32 best = STATSTAGE_ATTACK, bestValue = 0, i;

    for (i = 0; i < 5; ++i) {
        u32 value = GetBattleMonStat(mon, BMV_ATTACK + i);
        if (value > bestValue) {
            bestValue = value;
            best = STATSTAGE_ATTACK + i;
        }
    }
    return best;
}

/* Ratios (fixed point, W2U_RATIO_ONE = x1) */
static inline void W2U_MulRatio(s32 ratio) { BattleEventVar_MulValue(VAR_RATIO, ratio); }
static inline void W2U_MulMovePower(s32 ratio) { BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, ratio); }
/* a x b in fixed point, as the game multiplies ratios */
static inline u32 W2U_RatioMul(u32 a, u32 b) { return a * b >> 12; }

/* Effects: pushed to the handler-effect queue, as the vanilla abilities do */

/* The holder's ability popup around a set message (bank 18; argument 0 = the holder) */
static inline void W2U_PopupMessage(BtlServerFlow *flow, u8 monId, u16 message)
{
    BattleHandlerMessageParam *param;

    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    param = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
    BattleHandler_StrSetup(&param->string, HANDLER_STR_SET, message);
    BattleHandler_AddArg(&param->string, monId);
    BattleHandler_PopWork(flow, param);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

/* One Pokémon's stat stage change (STATSTAGE_*, +-1..6), as Defiant and Weak Armor push it; popup: inside the
 * holder's ability popup */
static inline void W2U_ChangeStatStage(BtlServerFlow *flow, u8 holder, u8 target, u32 stat, s32 stages, b32 popup)
{
    BattleHandlerStatChangeParam *param =
        (BattleHandlerStatChangeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_STAT, holder);

    if (popup) {
        param->popup = 1;
    }
    param->stat = stat;
    param->change = (s8)stages;
    param->unk0e = 1;
    param->count = 1;
    param->monIds[0] = target;
    BattleHandler_PopWork(flow, param);
}

/* The holder's own stat stage change with the ability popup around it, as W2U's abilities push it
 * (PushAbilityStatStageChange in w2u_abilities.cpp): nothing if the holder has fainted or the stat can't change that
 * way any more. True if pushed. */
static inline b32 W2U_PopupStatChange(BtlServerFlow *flow, u8 monId, u32 stat, s32 stages)
{
    BattleMon *mon = GetBattleMon(flow, monId);
    BattleHandlerStatChangeParam *param;

    if (!mon || IsFainted(mon) || !IsStatChangeValid(mon, stat, stages)) {
        return 0;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    param = (BattleHandlerStatChangeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_STAT, monId);
    param->count = 1;
    param->monIds[0] = monId;
    param->unk0e = 1;
    param->stat = stat;
    param->change = (s8)stages;
    BattleHandler_PopWork(flow, param);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    return 1;
}

/* A status for target from the holder's ability, inside its popup (Poison Touch, Flame Body). The engine applies the
 * usual immunities (types, Water Veil, an existing status) and shows the status' own text. */
static inline void W2U_AddCondition(BtlServerFlow *flow, u8 holder, u8 target, u32 condition, BattleCondition value)
{
    BattleHandlerAddConditionParam *param =
        (BattleHandlerAddConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_CONDITION, holder);

    param->popup = 1;
    param->condition = condition;
    param->value = value;
    param->targetIndex = target;
    BattleHandler_PopWork(flow, param);
}

#define W2U_MSG_SET_DOESNT_AFFECT 210   /* bank 18: "It doesn't affect {0}..." */

/* From an EVENT_CHECK_NO_EFFECT handler: the move does not affect the holder, with the ability popup and "It
 * doesn't affect..." (Soundproof). False if another handler already decided (the variable is rewritten once). */
static inline b32 W2U_BlockMove(BtlServerFlow *flow, u8 monId)
{
    if (!BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) {
        return 0;
    }
    W2U_PopupMessage(flow, monId, W2U_MSG_SET_DOESNT_AFFECT);
    return 1;
}

/* The AI's damage simulation runs the damage events too (dozens a turn): handlers that log or count skip it */
static inline b32 W2U_IsSimulating(BtlServerFlow *flow)
{
#if defined(W2U_DECOMP)
    return flow->simulationDepth != 0;
#else
    return *(const u32 *)((const u8 *)flow + W2U_SERVERFLOW_SIMULATION_DEPTH) != 0;
#endif
}

#endif /* W2U_BATTLE_API_H */
