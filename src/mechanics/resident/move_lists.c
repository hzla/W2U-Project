/* W2U's additions to the engine's move lists:
 *   Sheer Force   its moves (power, the failure check, the effects suppressed) include later moves whose added effect
 *                 isn't a native secondary effect: the engine's IsAffectedBySheerForce callers ask this
 *                 (HandlerSheerForcePower, HandlerSheerForceCheckFail, HandlerSheerForceHitCheck);
 *   calling       Assist, Sleep Talk, Me First and Copycat can't call the torque moves (NPC-only: the Starmobile's)
 *                 either, nor the moves their native lists exclude. */
#include "w2u/resident.h"

#define MOVE_SPIRIT_SHACKLE 662         /* W2U's (Moves.h) */
#define MOVE_THROAT_CHOP 675
#define MOVE_ANCHOR_SHOT 677
#define MOVE_BURNING_JEALOUSY 807
#define MOVE_EERIE_SPELL 826
#define MOVE_STONE_AXE 830
#define MOVE_CEASELESS_EDGE 845
#define MOVE_SALT_CURE 864
#define MOVE_BLAZING_TORQUE 896         /* the torques: Blazing .. Magical */
#define MOVE_MAGICAL_TORQUE 900
#define MOVE_SYRUP_BOMB 903
#define MOVE_ELECTRO_SHOT 905
#define MOVE_ALLURING_VOICE 914

b32 W2U_IsAffectedBySheerForce(u16 move)
{
    switch (move) {
    case MOVE_ANCHOR_SHOT:
    case MOVE_SPIRIT_SHACKLE:
    case MOVE_THROAT_CHOP:
    case MOVE_CEASELESS_EDGE:
    case MOVE_STONE_AXE:
    case MOVE_BURNING_JEALOUSY:
    case MOVE_ALLURING_VOICE:
    case MOVE_EERIE_SPELL:
    case MOVE_SALT_CURE:
    case MOVE_SYRUP_BOMB:
    case MOVE_ELECTRO_SHOT:
        return 1;
    default:
        return IsAffectedBySheerForce(move);
    }
}

b32 W2U_MoveIsRestrictedNpcAttack(u16 move)
{
    return move >= MOVE_BLAZING_TORQUE && move <= MOVE_MAGICAL_TORQUE;
}

b32 W2U_IsAssistExcludedMove(u16 move) { return W2U_MoveIsRestrictedNpcAttack(move) || IsAssistExcludedMove(move); }
b32 W2U_IsSleepTalkExcludedMove(u16 move) { return W2U_MoveIsRestrictedNpcAttack(move) || IsSleepTalkExcludedMove(move); }
b32 W2U_IsMeFirstExcludedMove(u16 move) { return W2U_MoveIsRestrictedNpcAttack(move) || IsMeFirstExcludedMove(move); }
b32 W2U_IsCopycatExcludedMove(u16 move) { return W2U_MoveIsRestrictedNpcAttack(move) || IsCopycatExcludedMove(move); }
