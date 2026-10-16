/* Lingering Aroma, Wandering Spirit (Gen 9, 8): reactions to a contact move, modelled on vanilla Mummy (the defender is
 * the holder, not a substitute hit, no matchup check running, the move makes contact; an ability change with its
 * message; the popup only against a foe). Showdown:
 *   Lingering Aroma   the attacker's ability becomes Lingering Aroma ("A lingering aroma clings to X!")
 *   Wandering Spirit  the holder and the attacker swap abilities ("X swapped Abilities with its target!")
 * Not over abilities that can't be replaced (Showdown's cantsuppress / failskillswap lists, those in the game). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MSG_SET_SWAPPED_ABILITIES 508   /* bank 18: "{0} swapped Abilities with its target!" (Skill Swap's) */

/* Wonder Guard, Multitype, Illusion, Zen Mode, Imposter, then the Gen 6+ form and special abilities */
static const u16 sLingeringAromaFixed[] = {
    25, 121, 149, 161, 150, ABIL_STANCE_CHANGE, ABIL_SCHOOLING, ABIL_DISGUISE, ABIL_BATTLE_BOND, ABIL_POWER_CONSTRUCT,
    ABIL_COMATOSE, ABIL_SHIELDS_DOWN, ABIL_RKS_SYSTEM, ABIL_GULP_MISSILE, ABIL_ICE_FACE, ABIL_NEUTRALIZING_GAS,
    ABIL_HUNGER_SWITCH, ABIL_AS_ONE_GLASTRIER, ABIL_AS_ONE_SPECTRIER, ABIL_ZERO_TO_HERO, ABIL_COMMANDER,
    ABIL_TERA_SHIFT, ABIL_LINGERING_AROMA, ABIL_WANDERING_SPIRIT,
};

static b32 LingeringAromaFixed(u16 ability)
{
    u32 i;

    for (i = 0; i < NELEMS(sLingeringAromaFixed); ++i) {
        if (sLingeringAromaFixed[i] == ability) {
            return 1;
        }
    }
    return 0;
}

static void LingeringAromaChange(BtlServerFlow *flow, u8 holder, u8 target, u16 ability, u16 message, b32 popup)
{
    BattleHandlerAbilityChangeParam *param =
        (BattleHandlerAbilityChangeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_ABILITY, holder);

    param->ability = ability;
    param->targetIndex = target;
    if (message) {
        BattleHandler_StrSetup(&param->string, HANDLER_STR_SET, message);
        BattleHandler_AddArg(&param->string, target);
    }
    if (popup) {
        param->popup = 1;
    }
    BattleHandler_PopWork(flow, param);
}

static void HandlerLingeringAromaHit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 attacker;
    u16 theirs, mine;
    BattleHandlerMessageParam *message;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) || Handler_CheckMatchup(flow)) {
        return;
    }
    if (!W2U_MakesContact(flow, W2U_Move())) {
        return;
    }
    attacker = W2U_Attacker();
    if (attacker == monId || attacker >= BATTLE_MAX_MON_ID) {
        return;
    }
    theirs = (u16)GetBattleMonStat(GetBattleMon(flow, attacker), BMV_ABILITY);
    mine = W2U_HolderAbility(flow, monId);
    if (LingeringAromaFixed(theirs) || theirs == mine) {
        return;
    }
    if (mine == ABIL_LINGERING_AROMA) {
        LingeringAromaChange(flow, monId, attacker, ABIL_LINGERING_AROMA, BTLMSG_SET_LINGERING_AROMA,
                             !W2U_IsAlly(monId, attacker));
        return;
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    LingeringAromaChange(flow, monId, attacker, ABIL_WANDERING_SPIRIT, 0, 0);
    LingeringAromaChange(flow, monId, monId, theirs, 0, 0);
    message = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
    BattleHandler_StrSetup(&message->string, HANDLER_STR_SET, MSG_SET_SWAPPED_ABILITIES);
    BattleHandler_AddArg(&message->string, monId);
    BattleHandler_PopWork(flow, message);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

W2U_HANDLER_TABLE(LingeringAromaHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerLingeringAromaHit },
};
W2U_MECHANIC(ABILITY, ABIL_LINGERING_AROMA, LingeringAromaHandlers);
W2U_MECHANIC(ABILITY, ABIL_WANDERING_SPIRIT, LingeringAromaHandlers);
