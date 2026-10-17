/* Reactions to being hit (Gen 8, 9; Showdown's onDamagingHit): EVENT_AFTER_DAMAGE_REACTION, the defender is the
 * holder, not a substitute hit.
 *   Cotton Down   every other Pokémon on the field (allies too) has its Speed lowered by 1
 *   Perish Body   a contact move: the attacker and the holder both get Perish Song's count (3 turns; one already
 *                 counting down is left alone), "Both Pokémon will faint in three turns!"
 *   Toxic Debris  a physical move: a layer of Toxic Spikes on the attacker's side (the engine's side effect, permanent,
 *                 its own "Poison spikes were scattered..." message; at most 2 layers: the engine)
 * Toxic Debris and Cotton Down follow PW2Code's. */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define MSG_STD_TOXIC_SPIKES 152        /* bank 19: "Poison spikes were scattered all around..." (+ the side) */

static b32 HitReactionApplies(u8 monId)
{
    u8 attacker = W2U_Attacker();

    return W2U_Defender() == monId && !BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) && attacker != monId
           && attacker < BATTLE_MAX_MON_ID;
}

static void HandlerCottonDownHit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerStatChangeParam *param;
    u8 id;

    (void)item;
    (void)work;
    if (!HitReactionApplies(monId)) {
        return;
    }
    param = (BattleHandlerStatChangeParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CHANGE_STAT, monId);
    param->popup = 1;
    param->stat = STATSTAGE_SPEED;
    param->change = -1;
    param->unk0e = 1;
    param->count = 0;
    for (id = 0; id < BATTLE_MAX_MON_ID; ++id) {
        if (W2U_OnFieldAlive(flow, id) && id != monId && param->count < 6) {
            param->monIds[param->count++] = id;
        }
    }
    BattleHandler_PopWork(flow, param);
}

static void HandlerPerishBodyHit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    u8 ids[2];
    b32 announced = 0;
    u32 i;
    BattleHandlerMessageParam *message;

    (void)item;
    (void)work;
    if (!HitReactionApplies(monId) || !W2U_MakesContact(flow, W2U_Move())) {
        return;
    }
    ids[0] = W2U_Attacker();
    ids[1] = monId;
    for (i = 0; i < 2; ++i) {
        BattleMon *mon = GetBattleMon(flow, ids[i]);
        BattleHandlerAddConditionParam *param;
        if (IsFainted(mon) || CheckCondition(mon, CONDITION_PERISH_SONG)) {
            continue;
        }
        if (!announced) {
            announced = 1;
            BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
        }
        param = (BattleHandlerAddConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_CONDITION, monId);
        param->condition = CONDITION_PERISH_SONG;
        param->value = SetConditionTurns(4);
        param->targetIndex = ids[i];
        BattleHandler_PopWork(flow, param);
    }
    if (!announced) {
        return;
    }
    message = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
    BattleHandler_StrSetup(&message->string, HANDLER_STR_STD, BTLMSG_STD_PERISH_BODY);
    BattleHandler_PopWork(flow, message);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerToxicDebrisHit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerAddSideEffectParam *param;
    u8 side;

    (void)item;
    (void)work;
    if (!HitReactionApplies(monId) || W2U_MoveCategory(W2U_Move()) != MOVE_CATEGORY_PHYSICAL) {
        return;
    }
    side = GetSideFromOpposingMonID(monId);
    param = (BattleHandlerAddSideEffectParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_SIDE_EFFECT, monId);
    W2U_WorkPopup(param);
    param->effect = SIDE_EFFECT_TOXIC_SPIKES;
    param->side = side;
    param->cont = MakeConditionPermanent();
    BattleHandler_StrSetup(&param->string, HANDLER_STR_STD, MSG_STD_TOXIC_SPIKES);
    BattleHandler_AddArg(&param->string, side);
    BattleHandler_PopWork(flow, param);
}

W2U_HANDLER_TABLE(CottonDownHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerCottonDownHit },
};
W2U_MECHANIC(ABILITY, ABIL_COTTON_DOWN, CottonDownHandlers);

W2U_HANDLER_TABLE(PerishBodyHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerPerishBodyHit },
};
W2U_MECHANIC(ABILITY, ABIL_PERISH_BODY, PerishBodyHandlers);

W2U_HANDLER_TABLE(ToxicDebrisHandlers) = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerToxicDebrisHit },
};
W2U_MECHANIC(ABILITY, ABIL_TOXIC_DEBRIS, ToxicDebrisHandlers);
