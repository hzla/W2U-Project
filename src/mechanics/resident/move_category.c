/* The category a move hits with when it isn't its record's: Shell Side Arm (the category its handler picked for the
 * attack, W2U_MoveState_SetShellSideArmCategory) and Photon Geyser (physical when the user's Attack beats its Special
 * Attack, stages included, before items and abilities: ties are special). The damage path asks it instead of
 * PML_MoveGetCategory: ServerEvent_CalcDamage, ServerEvent_GetAttackPower and ServerEvent_GetTargetDefenses. The
 * category each Pokémon's last such hit used is kept for Counter and Mirror Coat, whose damage record has only the
 * move. Was w2u_moves.cpp's move state (ResolveRuntimeMoveCategory). */
#include "w2u/resident.h"

#define MOVE_PHOTON_GEYSER 722          /* W2U's (Moves.h) */
#define MOVE_SHELL_SIDE_ARM 801

/* Per Pokémon (monId 0-23), as bits */
static u32 sShellSideArmValid;          /* its handler picked the category for the attack */
static u32 sShellSideArmPhysical;
static u32 sShellSideArmRecordedValid;  /* a hit used it (CalcDamage) */
static u32 sShellSideArmRecordedPhysical;
static u32 sPhotonGeyserValid;
static u32 sPhotonGeyserPhysical;

static u32 MonBit(u32 monId)
{
    return monId < 32 ? 1u << monId : 0;
}

static void SetBit(u32 *flags, u32 bit, b32 value)
{
    if (value) {
        *flags |= bit;
    } else {
        *flags &= ~bit;
    }
}

void W2U_MoveState_SetShellSideArmCategory(u32 monId, u32 category)
{
    u32 bit = MonBit(monId);
    if (bit) {
        sShellSideArmValid |= bit;
        SetBit(&sShellSideArmPhysical, bit, category == MOVE_CATEGORY_PHYSICAL);
    }
}

u32 W2U_MoveState_ShellSideArmCategory(u32 monId)
{
    u32 bit = MonBit(monId);
    return bit && (sShellSideArmValid & bit) && (sShellSideArmPhysical & bit) ? MOVE_CATEGORY_PHYSICAL
                                                                               : MOVE_CATEGORY_SPECIAL;
}

void W2U_MoveState_ClearShellSideArm(u32 monId, b32 recordedToo)
{
    u32 bit = MonBit(monId);
    sShellSideArmValid &= ~bit;
    if (recordedToo) {
        sShellSideArmRecordedValid &= ~bit;
    }
}

u32 W2U_HitCategory(u16 move, BattleMon *attacker, b32 record)
{
    if (move == MOVE_SHELL_SIDE_ARM && attacker) {
        return W2U_MoveState_ShellSideArmCategory(GetMonID(attacker));
    }
    if (move == MOVE_PHOTON_GEYSER && attacker) {
        u32 category = GetBattleMonStat(attacker, BMV_ATTACK) > GetBattleMonStat(attacker, BMV_SPECIAL_ATTACK)
                           ? MOVE_CATEGORY_PHYSICAL
                           : MOVE_CATEGORY_SPECIAL;
        u32 bit = MonBit(GetMonID(attacker));
        if (record && bit) {
            sPhotonGeyserValid |= bit;
            SetBit(&sPhotonGeyserPhysical, bit, category == MOVE_CATEGORY_PHYSICAL);
        }
        return category;
    }
    return (u32)PML_MoveGetCategory(move);
}

u32 W2U_CalcDamageCategory(u16 move, BattleMon *attacker)
{
    u32 category = W2U_HitCategory(move, attacker, 1);
    if (move == MOVE_SHELL_SIDE_ARM && attacker) {
        u32 bit = MonBit(GetMonID(attacker));
        if (sShellSideArmValid & bit) {
            sShellSideArmRecordedValid |= bit;
            SetBit(&sShellSideArmRecordedPhysical, bit, category == MOVE_CATEGORY_PHYSICAL);
        }
    }
    return category;
}

u32 W2U_RecordedMoveCategory(u16 move, u32 attackerId)
{
    u32 bit = MonBit(attackerId);
    if (move == MOVE_SHELL_SIDE_ARM && (sShellSideArmRecordedValid & bit)) {
        return sShellSideArmRecordedPhysical & bit ? MOVE_CATEGORY_PHYSICAL : MOVE_CATEGORY_SPECIAL;
    }
    if (move == MOVE_PHOTON_GEYSER && (sPhotonGeyserValid & bit)) {
        return sPhotonGeyserPhysical & bit ? MOVE_CATEGORY_PHYSICAL : MOVE_CATEGORY_SPECIAL;
    }
    return (u32)PML_MoveGetCategory(move);
}

void W2U_Resident_ResetMoveCategories(void)
{
    sShellSideArmValid = sShellSideArmPhysical = 0;
    sShellSideArmRecordedValid = sShellSideArmRecordedPhysical = 0;
    sPhotonGeyserValid = sPhotonGeyserPhysical = 0;
}
