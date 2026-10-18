/* Contact as a move makes it now (W2U_MoveMakesContact, battle_api.h): the move's contact flag (Shell Side Arm: when
 * it hits physically), unless the attacker's Long Reach or Protective Pads removes it. These ask it instead of the
 * flag: W2U's C mechanics (W2U_MakesContact) and the engine's contact reactions W2U changes,
 * CommonContactStatusAbility, HandlerRoughSkin, HandlerAftermath, HandlerPickpocket, HandlerPoisonTouch, HandlerMummy,
 * HandlerStickyBarbDamageReaction and HandlerRockyHelmet (the injection build replaces them whole in
 * w2u_abilities.cpp; a decomp build changes their contact test). Also whether a Pokémon can use its held item. */
#include "w2u/resident.h"
#include "megab2w2/mb_ids.h"

#define ABIL_KLUTZ 103                  /* vanilla (w2u_battle.h) */
#define ITEM_PROTECTIVE_PADS 114        /* W2U's (Items.h) */
#define MOVE_SHELL_SIDE_ARM 801         /* W2U's (Moves.h) */

b32 W2U_BattleMonCanUseHeldItem(BattleMon *mon)
{
    return mon && !IsFieldEffectActive(FIELD_CONDITION_MAGIC_ROOM) &&
           GetBattleMonStat(mon, BMV_EFFECTIVE_ABILITY) != ABIL_KLUTZ && !CheckCondition(mon, CONDITION_EMBARGO) &&
           !GetTurnFlag(mon, TURN_FLAG_CANT_USE_ITEM);
}

b32 W2U_MoveMakesContact(BtlServerFlow *flow, u16 move, u32 attacker)
{
    BattleMon *mon;

    if (move == MOVE_SHELL_SIDE_ARM ? W2U_MoveState_ShellSideArmCategory(attacker) != MOVE_CATEGORY_PHYSICAL
                                    : !getMoveFlag(move, MOVE_FLAG_INDEX_CONTACT)) {
        return 0;
    }
    mon = attacker < BATTLE_MAX_MON_ID ? GetBattleMon(flow, (u8)attacker) : 0;
    if (!mon) {
        return 1;
    }
    if (GetBattleMonStat(mon, BMV_EFFECTIVE_ABILITY) == ABIL_LONG_REACH) {
        return 0;
    }
    return !(GetBattleMonHeldItem(mon) == ITEM_PROTECTIVE_PADS && W2U_BattleMonCanUseHeldItem(mon));
}
