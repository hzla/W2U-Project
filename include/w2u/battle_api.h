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

/* The resident core's battle state (megab2w2/mb_resident.cpp), kept by its engine call-site hooks */
/* The move the Pokémon's fight action will use this turn (EVENT_SPECIAL_PRIORITY carries no move); 0: none */
u16 W2U_MB_PendingMove(BtlServerFlow *flow, u32 monId);
/* Turn end: forget the Pokémon's noted move */
void W2U_MB_ClearPendingMove(u32 monId);
/* Mega Sol: the Pokémon whose move is running (0xFF: none); the weather reads as sun meanwhile */
void W2U_MB_SetMegaSolAttacker(u32 monId);
/* Cud Chew: the effect dispatcher notes a Berry a holder ate. At each turn end this counts down and returns the
 * Berry to chew again at the end of the next turn (0: nothing yet); the second bite is not noted. */
u16 W2U_MB_CudChewTurnEnd(u32 monId);
void W2U_MB_CudChewForget(u32 monId);
/* Opportunist: a copy the holder queued (one stat change, run by the dispatcher with the copying flag set, so the
 * copy is not recorded again) */
void W2U_MB_OpportunistCopyQueued(u32 monId);
u8 W2U_MB_OpportunistCopying(void);             /* C++ bool */

/* W2U's terrain (w2u_moves.cpp): the current one (W2U_TERRAIN_*), and starting one from an ability under its popup
 * (W2U's Surge path: the popup, then the message, with which the terrain fades in; W2U's after-terrain-change event
 * fires). msgID: the terrain's start message, or with ...Named an ability's own message naming the holder. False if
 * that terrain is already up. */
u32 W2U_MoveState_GetTerrain(void);
b32 W2U_MoveState_SetTerrainFromAbility(BtlServerFlow *flow, u32 monId, u32 terrain, u32 msgID, u32 animMove);
b32 W2U_MoveState_SetTerrainFromAbilityNamed(BtlServerFlow *flow, u32 monId, u32 terrain, u32 msgID, u32 animMove);

W2U_C_END

/* Who and what the current event is about */
static inline u8 W2U_Subject(void) { return (u8)BattleEventVar_GetValue(VAR_MON_ID); }
static inline u8 W2U_Attacker(void) { return (u8)BattleEventVar_GetValue(VAR_ATTACKING_MON); }
static inline u8 W2U_Defender(void) { return (u8)BattleEventVar_GetValue(VAR_DEFENDING_MON); }
static inline u16 W2U_Move(void) { return (u16)BattleEventVar_GetValue(VAR_MOVE_ID); }
/* The move's type as this hit uses it (after -ate abilities, Weather Ball...) */
static inline u32 W2U_MoveType(void) { return BattleEventVar_GetValue(VAR_MOVE_TYPE); }

/* Items */
/* Berries: 149 (Cheri) .. 212 (Rowap), the vanilla Berry range (Cheek Pouch, Ripen, Cud Chew) */
static inline b32 W2U_IsBerry(u32 item) { return item >= 149 && item <= 212; }

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

/* The Pokémon is on the field */
static inline b32 W2U_OnField(BtlServerFlow *flow, u8 monId)
{
    return monId < BATTLE_MAX_MON_ID && Handler_PokeIDToPokePos(flow, monId) != BATTLE_POS_NONE;
}

/* The Pokémon is on the field and has not fainted (MegaB2W2's ForEachOnField) */
static inline b32 W2U_OnFieldAlive(BtlServerFlow *flow, u8 monId)
{
    return W2U_OnField(flow, monId) && !IsFainted(GetBattleMon(flow, monId));
}

/* The Pokémon has this ability and it works (not suppressed by Gastro Acid): for checks outside the holder's own
 * handlers */
static inline b32 W2U_HasActiveAbility(BattleMon *mon, u16 ability)
{
    return mon && (u16)GetBattleMonStat(mon, BMV_ABILITY) == ability && !CheckCondition(mon, CONDITION_GASTRO_ACID);
}

/* The lowest monId on the field with this ability working, or BATTLE_MAX_MON_ID: for field-wide effects that apply
 * once however many holders there are (the Ruin abilities) */
static inline u8 W2U_FirstFieldHolder(BtlServerFlow *flow, u16 ability)
{
    u8 monId;

    for (monId = 0; monId < BATTLE_MAX_MON_ID; ++monId) {
        if (W2U_OnField(flow, monId) && W2U_HasActiveAbility(GetBattleMon(flow, monId), ability)) {
            return monId;
        }
    }
    return BATTLE_MAX_MON_ID;
}

/* Ratios (fixed point, W2U_RATIO_ONE = x1) */
static inline void W2U_MulRatio(s32 ratio) { BattleEventVar_MulValue(VAR_RATIO, ratio); }
static inline void W2U_MulMovePower(s32 ratio) { BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, ratio); }
/* a x b in fixed point, as the game multiplies ratios */
static inline u32 W2U_RatioMul(u32 a, u32 b) { return a * b >> 12; }

/* Effects: pushed to the handler-effect queue, as the vanilla abilities do */

/* The holder's ability popup around a set message (bank 18) about a Pokémon (its argument 0) */
static inline void W2U_PopupMessageAbout(BtlServerFlow *flow, u8 holder, u16 message, u8 about)
{
    BattleHandlerMessageParam *param;

    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, holder);
    param = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, holder);
    BattleHandler_StrSetup(&param->string, HANDLER_STR_SET, message);
    BattleHandler_AddArg(&param->string, about);
    BattleHandler_PopWork(flow, param);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, holder);
}

/* The holder's ability popup around a set message about the holder */
static inline void W2U_PopupMessage(BtlServerFlow *flow, u8 monId, u16 message)
{
    W2U_PopupMessageAbout(flow, monId, message, monId);
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

/* Terrain */
enum { W2U_TERRAIN_NONE, W2U_TERRAIN_ELECTRIC, W2U_TERRAIN_GRASSY, W2U_TERRAIN_MISTY, W2U_TERRAIN_PSYCHIC };

static inline u32 W2U_Terrain(void) { return W2U_MoveState_GetTerrain(); }

/* The terrain's type (Mimicry): Electric, Grass, Fairy, Psychic */
static inline u32 W2U_TerrainType(u32 terrain)
{
    static const u8 types[5] = { 0, 12, 11, 17, 13 };

    return terrain <= W2U_TERRAIN_PSYCHIC ? types[terrain] : 0;
}

/* W2U's terrain start messages (bank 18) and the terrain moves whose animation plays (Black 2 only) */
static inline u16 W2U_TerrainStartMessage(u32 terrain)
{
    static const u16 messages[5] = { 0, 1292, 1295, 1298, 1313 };

    return messages[terrain];
}

static inline u16 W2U_TerrainAnimationMove(u32 terrain)
{
    static const u16 moves[5] = { 0, 604, 580, 581, 678 };

    return moves[terrain];
}

/* Starts terrain from the holder's ability, as W2U's Surges do; nothing if it is already up */
static inline b32 W2U_SetTerrainFromAbility(BtlServerFlow *flow, u8 monId, u32 terrain)
{
    return terrain && terrain <= W2U_TERRAIN_PSYCHIC
           && W2U_MoveState_SetTerrainFromAbility(flow, monId, terrain, W2U_TerrainStartMessage(terrain),
                                                  W2U_TerrainAnimationMove(terrain));
}

/* The same with the ability's own message naming the holder instead of the terrain's start message */
static inline b32 W2U_SetTerrainFromAbilityNamed(BtlServerFlow *flow, u8 monId, u32 terrain, u16 message)
{
    return terrain && terrain <= W2U_TERRAIN_PSYCHIC
           && W2U_MoveState_SetTerrainFromAbilityNamed(flow, monId, terrain, message, W2U_TerrainAnimationMove(terrain));
}

/* A set message about the holder, without the popup (inside one already shown, or none) */
static inline void W2U_Message(BtlServerFlow *flow, u8 monId, u16 message)
{
    BattleHandlerMessageParam *param =
        (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);

    BattleHandler_StrSetup(&param->string, HANDLER_STR_SET, message);
    BattleHandler_AddArg(&param->string, monId);
    BattleHandler_PopWork(flow, param);
}

/* Parties */
static inline BtlPokeCon *W2U_PokeCon(BtlServerFlow *flow)
{
#if defined(W2U_DECOMP)
    return flow->pokeCon;
#else
    return *(BtlPokeCon **)((u8 *)flow + W2U_SERVERFLOW_POKECON);
#endif
}

/* The party of the Pokémon's client */
static inline BattleParty *W2U_PartyOf(BtlServerFlow *flow, u8 monId)
{
    return GetPartyData(W2U_PokeCon(flow), MonIDToClientID(monId));
}

/* The party Pokémon a battle Pokémon battles as */
static inline const PartyPkm *W2U_BattleMonSource(BattleMon *mon)
{
#if defined(W2U_DECOMP)
    return mon->core.src;
#else
    return *(const PartyPkm **)((u8 *)mon + W2U_BATTLEMON_SOURCE);
#endif
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
