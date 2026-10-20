/* Type effectiveness as W2U computes it (was w2u_moves.cpp's):
 * - a Pokémon's added type (Forest's Curse, Trick-or-Treat: W2U_MoveState_SetExtraType) and Tar Shot (Fire hits it
 *   doubly) count, so effectiveness goes beyond vanilla's grades: W2U_EFF_1_8 .. W2U_EFF_16;
 * - W2U_EffectivenessMultiplier, W2U_EffectivenessPowerMod: GetTypeEffectivenessMultiplier and
 *   TypeEffectivenessPowerMod with those grades;
 * - W2U_CheckTypeEffectiveness: one move type against one defending type, as ServerEvent_CheckTypeEffectiveness, with
 *   W2U's overrides in VAR_SET_TYPE_EFFECTIVENESS (x0.5 / x1 / x2, or another grade compounded: Freeze-Dry,
 *   Flying Press);
 * - W2U_CheckMoveEffectiveness: a move against a Pokémon, as ServerControl_CheckMoveEffectiveness, with the added type,
 *   Tar Shot and Thousand Arrows (it hits a floating Flying type for x1);
 * - W2U_HasType: the Pokémon's types and its added one (BattleMon_HasType / DoesMonHaveType; not Roost-aware, as W2U's);
 * - W2U_ClassifyEffectiveness: BtlCalc_ClassifyEffectiveness with W2U's grades. The engine's counts every grade above
 *   x1 as super effective, so a x1/8 hit (grade 6) got Filter's and Tinted Lens' modifiers the wrong way;
 *   W2U_EffectivenessMessage: ServerDisplay_EffectivenessMessage (a multi-hit move's message) through it. Still on
 *   the raw "above x1" test: ServerDisplay_EffectivenessMessageMulti (the usual message: a x1/8 hit still says
 *   "It's super effective!"), Expert Belt, the battle records' counts, the AI's switch logic.
 * The injection build replaces those engine functions whole; a decomp build's functions return these. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define MOVE_THOUSAND_ARROWS 614        /* W2U's (Moves.h) */
#define W2U_TYPE_NONE 18                /* TYPE_NULL with Fairy (type_constants.h) */
#define W2U_MSG_SUPER_EFFECTIVE 0x4E    /* bank 19: "It's super effective!" */
#define W2U_MSG_NOT_VERY_EFFECTIVE 0x4F /* bank 19: "It's not very effective..." */

/* Per Pokémon: the added type + 1 (0: none), and Tar Shot */
static u8 sExtraType[BATTLE_MAX_MON_ID];
static u32 sTarShot;

void W2U_MoveState_SetExtraType(u32 monId, u32 type)
{
    if (monId < BATTLE_MAX_MON_ID) {
        sExtraType[monId] = type < W2U_TYPE_NONE ? (u8)(type + 1) : 0;
    }
}

void W2U_MoveState_ClearExtraType(u32 monId)
{
    W2U_MoveState_SetExtraType(monId, W2U_TYPE_NONE);
}

u32 W2U_MoveState_GetExtraType(u32 monId)
{
    return monId < BATTLE_MAX_MON_ID && sExtraType[monId] ? sExtraType[monId] - 1u : W2U_TYPE_NONE;
}

b32 W2U_MoveState_ApplyTarShot(u32 monId)
{
    u32 bit = monId < BATTLE_MAX_MON_ID ? 1u << monId : 0;
    b32 changed = bit && !(sTarShot & bit);
    sTarShot |= bit;
    return changed;
}

b32 W2U_MoveState_HasTarShot(u32 monId)
{
    return monId < BATTLE_MAX_MON_ID && (sTarShot & (1u << monId));
}

void W2U_MoveState_ClearTarShot(u32 monId)
{
    if (monId < BATTLE_MAX_MON_ID) {
        sTarShot &= ~(1u << monId);
    }
}

void W2U_Resident_ResetEffectiveness(void)
{
    u32 i;
    for (i = 0; i < BATTLE_MAX_MON_ID; i++) {
        sExtraType[i] = 0;
    }
    sTarShot = 0;
}

u32 W2U_ClassifyEffectiveness(s32 effectiveness)
{
    if (effectiveness == W2U_EFF_IMMUNE) {
        return EFFECTIVENESS_IMMUNE;
    }
    if (effectiveness == W2U_EFF_1) {
        return EFFECTIVENESS_NEUTRAL;
    }
    if (effectiveness < W2U_EFF_1 || effectiveness == W2U_EFF_1_8) {
        return EFFECTIVENESS_RESISTED;
    }
    return EFFECTIVENESS_SUPER;
}

void W2U_EffectivenessMessage(BtlServerFlow *flow, s32 effectiveness)
{
    u32 cls = W2U_ClassifyEffectiveness(effectiveness);
    if (cls == EFFECTIVENESS_SUPER) {
        ServerDisplay_AddMessageImpl(W2U_ServerQueue(flow), SERVER_CMD_STD_MESSAGE, W2U_MSG_SUPER_EFFECTIVE, 0xFFFF0000);
    } else if (cls != EFFECTIVENESS_NEUTRAL) {
        ServerDisplay_AddMessageImpl(W2U_ServerQueue(flow), SERVER_CMD_STD_MESSAGE, W2U_MSG_NOT_VERY_EFFECTIVE,
                                     0xFFFF0000);
    }
}

b32 W2U_HasType(BattleMon *mon, u32 type)
{
    if (!mon || type >= W2U_TYPE_NONE) {
        return 0;
    }
    return W2U_MonType1(mon) == type || W2U_MonType2(mon) == type || W2U_MoveState_GetExtraType(GetMonID(mon)) == type;
}

/* Each grade as a multiple of 1/8 (x1 = 8), indexed by grade (W2U_EFF_*: 0 .. 8). Tables and if-chains, not switch:
 * a switch's jump table needs a libgcc helper the injection build lacks. */
static const u8 sScaled[] = { 0, 2, 4, 8, 16, 32, 1, 64, 128 };

static u32 Scaled(u32 effectiveness)
{
    return effectiveness < sizeof(sScaled) ? sScaled[effectiveness] : 0xFFFFFFFFu;
}

u32 W2U_EffectivenessMultiplier(u32 effectiveness1, u32 effectiveness2)
{
    u32 a = Scaled(effectiveness1), b = Scaled(effectiveness2), product, i;
    if (a == 0xFFFFFFFFu || b == 0xFFFFFFFFu) {
        return W2U_EFF_1;
    }
    product = a * b / 4;                /* in 1/16ths: x1 * x1 = 16 */
    for (i = 0; i < sizeof(sScaled); i++) {
        if (sScaled[i] * 2u == product) {
            return i;
        }
    }
    return W2U_EFF_1;                   /* x1/16 and below the 1/8 grade: W2U has no such grade */
}

/* The damage shift of each grade (W2U_EFF_*: x1/8 is -3, x16 is 4): a table, since gcc turns an if-chain on
 * these values into a jump table, which needs the libgcc helper */
static const s8 sShift[] = { 0, -2, -1, 0, 1, 2, -3, 3, 4 };

u32 W2U_EffectivenessPowerMod(u32 damage, u32 effectiveness)
{
    s32 shift;
    if (effectiveness == W2U_EFF_IMMUNE) {
        return 0;
    }
    if (effectiveness >= sizeof(sShift)) {
        return damage;
    }
    shift = sShift[effectiveness];
    return shift < 0 ? damage >> -shift : damage << shift;
}

u32 W2U_CheckTypeEffectiveness(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u32 moveType,
                               u32 defenseType)
{
    b32 ignoreImmunity;
    u32 override, effectiveness;

    BattleEventVar_Push(__LINE__);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, GetMonID(attacker));
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, GetMonID(target));
    BattleEventVar_SetConstValue(VAR_POKE_TYPE, (s32)defenseType);
    BattleEventVar_SetConstValue(VAR_MOVE_TYPE, (s32)moveType);
    BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);
    BattleEventVar_SetRewriteOnceValue(VAR_SET_TYPE_EFFECTIVENESS, W2U_DONT_OVERRIDE_EFFECTIVENESS);
    Condition_CheckTypeImmunity(flow, target);
    BattleEvent_CallHandlers(flow, EVENT_CHECK_TYPE_EFFECTIVENESS);
    ignoreImmunity = BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS);
    override = BattleEventVar_GetValue(VAR_SET_TYPE_EFFECTIVENESS);
    BattleEventVar_Pop(__LINE__);

    effectiveness = GetTypeEffectiveness((u8)moveType, (u8)defenseType);
    if (effectiveness == W2U_EFF_IMMUNE && ignoreImmunity) {
        effectiveness = W2U_EFF_1;
    }
    if (effectiveness != W2U_EFF_IMMUNE) {
        if (override == W2U_OVERRIDE_EFFECTIVENESS_1_2) {
            return W2U_EFF_1_2;
        }
        if (override == W2U_OVERRIDE_EFFECTIVENESS_1) {
            return W2U_EFF_1;
        }
        if (override == W2U_OVERRIDE_EFFECTIVENESS_2) {
            return W2U_EFF_2;
        }
        if (override >= W2U_COMPOUND_EFFECTIVENESS) {
            effectiveness = W2U_EffectivenessMultiplier(effectiveness, override - W2U_COMPOUND_EFFECTIVENESS);
        }
    }
    return effectiveness;
}

/* The first type's check, with the added type and Tar Shot: once per move (the engine combines the second type) */
static u32 FirstTypeEffectiveness(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target, u32 moveType,
                                  u32 type)
{
    u32 effectiveness = W2U_CheckTypeEffectiveness(flow, attacker, target, moveType, type);
    u32 extra = W2U_MoveState_GetExtraType(GetMonID(target));
    if (extra != W2U_TYPE_NONE) {
        effectiveness = W2U_EffectivenessMultiplier(
            effectiveness, W2U_CheckTypeEffectiveness(flow, attacker, target, moveType, extra));
    }
    if (moveType == TYPE_FIRE && W2U_MoveState_HasTarShot(GetMonID(target))) {
        effectiveness = W2U_EffectivenessMultiplier(effectiveness, W2U_EFF_2);
    }
    return effectiveness;
}

u32 W2U_CheckMoveEffectiveness(BtlServerFlow *flow, BattleMon *attacker, BattleMon *target,
                               const BtlFlowMoveParam *param, b32 message)
{
    b32 arrows, floating = 0;
    u32 types, first, second, result;

    if (param->type >= W2U_TYPE_NONE) {
        return W2U_EFF_1;
    }
    arrows = param->move == MOVE_THOUSAND_ARROWS && param->type == TYPE_GROUND;
    if (arrows && W2U_HasType(target, TYPE_FLYING) && ServerControl_CheckFloating(flow, target, 1)) {
        return W2U_EFF_1;               /* Thousand Arrows: x1 on a floating Flying type, whatever its other type */
    }
    types = W2U_PokeTypes(target);
    first = (types >> 8) & 0xFF;
    second = types & 0xFF;
    result = FirstTypeEffectiveness(flow, attacker, target, param->type, first);
    if (first != second) {
        result = W2U_EffectivenessMultiplier(result,
                                             W2U_CheckTypeEffectiveness(flow, attacker, target, param->type, second));
    }
    if (!arrows && param->type == TYPE_GROUND) {
        if (result != W2U_EFF_IMMUNE) {
            floating = ServerControl_CheckFloating(flow, target, 0);
            if (floating) {
                result = W2U_EFF_IMMUNE;
            }
        } else if (!ServerControl_CheckFloating(flow, target, 1)) {
            result = W2U_EFF_1;
        }
    }
    if (result == W2U_EFF_IMMUNE && message) {
        if (floating) {
            ServerControl_FloatingImmune(flow, target);
        } else {
            ServerDisplay_DoesntAffect(flow, target);
        }
    }
    return result;
}
