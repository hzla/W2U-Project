/* Form abilities (Gen 8, 9; Showdown's rules, data/abilities.ts):
 *   Ice Face (Eiscue)        Ice Face form (0) takes one physical hit for no damage and breaks into Noice Face (1);
 *                            back to Ice Face on entry or when hail starts (W2U's stand-in for snow). Noice Face
 *                            survives switching (w2u_mega.cpp W2U_AbilityPreservesFormOnSwitchOut). Breakable.
 *   Gulp Missile (Cramorant) Surf hitting, or Dive's charge turn, catches prey: Gulping (more than half HP) or
 *                            Gorging. Hit by an attack while it holds prey: the attacker loses 1/4 of its max HP, then
 *                            Defense -1 (Gulping) or paralysis (Gorging), and the prey is gone. W2U has no Gulping /
 *                            Gorging forms or sprites: the state is kept here and shown with the popup instead.
 *   Hunger Switch (Morpeko)  every turn end Full Belly (0) <-> Hangry (1), no popup; back to Full Belly on switching out
 *                            (Aura Wheel's type follows the form: w2u_moves.cpp).
 *   Zero to Hero (Palafin)   switching out in Zero Form leaves as Hero Form (w2u_mega.cpp BattleMon_ClearForSwitchOut:
 *                            form, stats, kept for the battle); the next entry announces it once ("X underwent a heroic
 *                            transformation!").
 *   Commander (Tatsugiri)    doubles: with an ally Dondozo on the field, Tatsugiri goes inside it ("X was swallowed by
 *                            Y and became its commander!"): Tatsugiri is hidden (Shadow Force's flag: no move reaches
 *                            it, its sprite vanishes), its own actions are cancelled silently, and neither Pokémon can
 *                            switch out (Mean Look's condition) or be forced out; Dondozo gets +2 Attack, Defense, Sp.
 *                            Atk, Sp. Def and Speed. Ends when Dondozo faints (Tatsugiri reappears). If Tatsugiri faints
 *                            instead (residual damage), Dondozo stays trapped, boosted and can't be forced out, as
 *                            Showdown's `commanded` never ends (w2u_moves.cpp's field handler, on the Commander form
 *                            Order Up reads; this ability's handlers go with the fainted Tatsugiri). As in Showdown the
 *                            command menu skips Tatsugiri (the recharge flag, set again each turn; the resident core,
 *                            megab2w2/mb_resident.cpp, drops the recharge message for it) and No Guard / Lock-On don't
 *                            reach it (also the resident core).
 * The prey, the announcements and the pairs are module state, fresh every battle (docs/engine-interface.md). */
#include "w2u/battle_api.h"
#include "megab2w2/mb_ids.h"

#define SPECIES_CRAMORANT 845
#define SPECIES_EISCUE 875
#define SPECIES_MORPEKO 877
#define SPECIES_PALAFIN 964
#define SPECIES_DONDOZO 977
#define SPECIES_TATSUGIRI 978
#define MOVE_SURF 57
#define MOVE_DIVE 291
#define MOVE_FAIL_NO_REACTION 0x19          /* VAR_FAIL_CAUSE: the action fails without a message */

#define GULP_NONE 0
#define GULP_GULPING 1
#define GULP_GORGING 2

static u8 sGulpMissilePrey[BATTLE_MAX_MON_ID];
static u8 sZeroToHeroAnnounced[BATTLE_MAX_MON_ID];
static u8 sCommanding[BATTLE_MAX_MON_ID];       /* Tatsugiri -> its Dondozo's ID + 1 (0: not commanding) */
static u8 sCommandedBy[BATTLE_MAX_MON_ID];      /* Dondozo -> its Tatsugiri's ID + 1 */

static BattleMon *FormsMon(BtlServerFlow *flow, u32 monId)
{
    if (monId >= BATTLE_MAX_MON_ID) {
        return 0;
    }
    return GetBattleMon(flow, (u8)monId);
}

/* ---- Ice Face ---- */

static BattleMon *IceFaceIntact(BtlServerFlow *flow, u8 monId)
{
    BattleMon *mon;

    if (W2U_Defender() != monId) {
        return 0;
    }
    mon = FormsMon(flow, monId);
    if (!W2U_IsUsableSpecies(mon, SPECIES_EISCUE) || W2U_Form(mon) != 0 || IsSubstituteActive(mon)) {
        return 0;
    }
    return PML_MoveGetCategory(W2U_Move()) == MOVE_CATEGORY_PHYSICAL ? mon : 0;
}

/* The damage estimate and the real hit alike (as Disguise): the strike deals nothing */
static void HandlerIceFacePreventDamage(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (IceFaceIntact(flow, monId)) {
        BattleEventVar_RewriteValue(VAR_DAMAGE, 0);
    }
}

static void HandlerIceFaceBreak(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (IceFaceIntact(flow, monId)) {
        W2U_ChangeForm(flow, monId, 1, 1);              /* Noice Face, kept on switching */
    }
}

static void HandlerIceFaceRestore(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleMon *mon = FormsMon(flow, monId);

    (void)item;
    (void)work;
    if (!W2U_IsUsableSpecies(mon, SPECIES_EISCUE) || W2U_Form(mon) != 1) {
        return;
    }
    if (ServerEvent_GetWeather(flow) == WEATHER_HAIL) {
        W2U_ChangeForm(flow, monId, 0, 1);
    }
}

static void HandlerIceFaceRestoreOnEntry(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    if (W2U_Subject() == monId) {
        HandlerIceFaceRestore(item, flow, monId, work);
    }
}

/* ---- Gulp Missile ---- */

static void GulpMissileCatch(BtlServerFlow *flow, u8 monId)
{
    BattleMon *mon = FormsMon(flow, monId);

    if (!W2U_IsUsableSpecies(mon, SPECIES_CRAMORANT) || sGulpMissilePrey[monId] != GULP_NONE) {
        return;
    }
    sGulpMissilePrey[monId] =
        GetBattleMonStat(mon, BMV_HP) * 2 <= GetBattleMonStat(mon, BMV_MAX_HP) ? GULP_GORGING : GULP_GULPING;
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);   /* no Gulping / Gorging sprite: the popup shows it */
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerGulpMissileSurf(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Attacker() == monId && W2U_Move() == MOVE_SURF) {
        GulpMissileCatch(flow, monId);
    }
}

static void HandlerGulpMissileDive(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (W2U_Attacker() == monId && W2U_Move() == MOVE_DIVE) {
        GulpMissileCatch(flow, monId);
    }
}

static void HandlerGulpMissileSpit(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleHandlerDamageParam *damage;
    BattleMon *source;
    u8 prey, attacker;

    (void)item;
    (void)work;
    if (W2U_Defender() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    prey = sGulpMissilePrey[monId];
    if (prey == GULP_NONE || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT)) {
        return;
    }
    attacker = W2U_Attacker();
    source = FormsMon(flow, attacker);
    if (!source || attacker == monId || IsFainted(source)) {
        return;
    }
    sGulpMissilePrey[monId] = GULP_NONE;
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    damage = (BattleHandlerDamageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_DAMAGE, monId);
    damage->targetIndex = attacker;
    damage->amount = (u16)DivideMaxHPZeroCheck(source, 4);
    BattleHandler_PopWork(flow, damage);
    if (prey == GULP_GULPING) {
        W2U_ChangeStatStage(flow, monId, attacker, STATSTAGE_DEFENSE, -1, 0);
    } else {
        BattleHandlerAddConditionParam *add =
            (BattleHandlerAddConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_CONDITION, monId);
        add->targetIndex = attacker;
        add->condition = CONDITION_PARALYSIS;
        add->value = BtlCalc_MakeMajorStatusCondition(CONDITION_PARALYSIS);
        BattleHandler_PopWork(flow, add);
    }
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
}

static void HandlerGulpMissileReset(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (W2U_Subject() == monId && monId < BATTLE_MAX_MON_ID) {
        sGulpMissilePrey[monId] = GULP_NONE;
    }
}

/* ---- Hunger Switch ---- */

static void HandlerHungerSwitch(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleMon *mon = FormsMon(flow, monId);
    u32 form;

    (void)item;
    (void)work;
    if (!W2U_IsUsableSpecies(mon, SPECIES_MORPEKO)) {
        return;
    }
    form = W2U_Form(mon);
    if (form <= 1) {
        W2U_ChangeForm(flow, monId, form ? 0 : 1, 0);      /* back to Full Belly on switching out */
    }
}

/* ---- Zero to Hero ---- */

static void HandlerZeroToHeroEntry(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    BattleMon *mon;

    (void)item;
    (void)work;
    if (W2U_Subject() != monId || monId >= BATTLE_MAX_MON_ID) {
        return;
    }
    mon = FormsMon(flow, monId);
    if (!W2U_IsUsableSpecies(mon, SPECIES_PALAFIN) || W2U_Form(mon) != 1 || sZeroToHeroAnnounced[monId]) {
        return;
    }
    sZeroToHeroAnnounced[monId] = 1;
    W2U_PopupMessage(flow, monId, BTLMSG_SET_ZERO_TO_HERO);
}

/* ---- Commander ---- */

/* The Pokémon beside it in a double battle, BATTLE_MAX_MON_ID if none */
static u32 CommanderAllyID(BtlServerFlow *flow, u8 monId)
{
    u8 pos;

    if (BtlSetup_GetBattleStyle(W2U_MainModule(flow)) != BTL_STYLE_DOUBLE) {
        return BATTLE_MAX_MON_ID;
    }
    pos = Handler_PokeIDToPokePos(flow, monId);
    if (pos >= 4) {
        return BATTLE_MAX_MON_ID;
    }
    return Handler_PokePosToPokeID(flow, (u8)(pos ^ 2));     /* doubles: 0 / 2 player side, 1 / 3 foe side */
}

static void CommanderPushFlag(BtlServerFlow *flow, u8 monId, u32 command, u32 flag)
{
    BattleHandlerFlagParam *param = (BattleHandlerFlagParam *)BattleHandler_PushWork(flow, command, monId);

    param->flag = flag;
    param->monIndex = monId;
    BattleHandler_PopWork(flow, param);
}

/* Tatsugiri hidden (again after its actions and at every turn end) */
static void CommanderHide(BtlServerFlow *flow, u8 monId)
{
    CommanderPushFlag(flow, monId, HANDLER_CMD_SET_CONTINUE_FLAG, CONT_FLAG_SHADOW_FORCE);
}

/* No command menu for Tatsugiri in the coming turn */
static void CommanderSkipMenu(BtlServerFlow *flow, u8 monId)
{
    CommanderPushFlag(flow, monId, HANDLER_CMD_SET_CONTINUE_FLAG, CONT_FLAG_RECHARGE);
}

/* Can't switch out: Tatsugiri's lasts while its Dondozo stays, Dondozo's for good */
static void CommanderTrap(BtlServerFlow *flow, u8 monId, u8 target, BattleCondition value)
{
    BattleHandlerAddConditionParam *add =
        (BattleHandlerAddConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_ADD_CONDITION, monId);

    add->targetIndex = target;
    add->condition = CONDITION_CANT_ESCAPE;
    add->value = value;
    BattleHandler_PopWork(flow, add);
}

static void CommanderTry(BtlServerFlow *flow, u8 monId)
{
    BattleHandlerMessageParam *message;
    BattleMon *mon, *allyMon;
    u32 ally;

    if (monId >= BATTLE_MAX_MON_ID || sCommanding[monId]) {
        return;
    }
    mon = FormsMon(flow, monId);
    if (!W2U_IsUsableSpecies(mon, SPECIES_TATSUGIRI)) {
        return;
    }
    ally = CommanderAllyID(flow, monId);
    allyMon = FormsMon(flow, ally);
    if (!allyMon || W2U_Species(allyMon) != SPECIES_DONDOZO || IsFainted(allyMon) || sCommandedBy[ally]) {
        return;
    }
    sCommanding[monId] = (u8)(ally + 1);
    sCommandedBy[ally] = (u8)(monId + 1);
    W2U_MoveState_SetCommanderForm(ally, W2U_Form(mon) + 1);

    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_IN, monId);
    message = (BattleHandlerMessageParam *)BattleHandler_PushWork(flow, HANDLER_CMD_MESSAGE, monId);
    BattleHandler_StrSetup(&message->string, HANDLER_STR_SET, BTLMSG_SET_COMMANDER);
    BattleHandler_AddArg(&message->string, monId);
    BattleHandler_AddArg(&message->string, ally);
    BattleHandler_PopWork(flow, message);
    CommanderHide(flow, monId);
    CommanderSkipMenu(flow, monId);
    ServerDisplay_AddCommon(W2U_ServerQueue(flow), SERVER_CMD_HIDE_SPRITE, monId, 1);
    BattleHandler_PushRun(flow, HANDLER_CMD_POPUP_OUT, monId);
    CommanderTrap(flow, monId, monId, W2U_ConditionLinkedTo(ally));
    CommanderTrap(flow, monId, (u8)ally, MakeConditionPermanent());

    W2U_ChangeStatStage(flow, monId, (u8)ally, STATSTAGE_ATTACK, 2, 0);
    W2U_ChangeStatStage(flow, monId, (u8)ally, STATSTAGE_DEFENSE, 2, 0);
    W2U_ChangeStatStage(flow, monId, (u8)ally, STATSTAGE_SPECIAL_ATTACK, 2, 0);
    W2U_ChangeStatStage(flow, monId, (u8)ally, STATSTAGE_SPECIAL_DEFENSE, 2, 0);
    W2U_ChangeStatStage(flow, monId, (u8)ally, STATSTAGE_SPEED, 2, 0);
}

static void CommanderForget(u8 monId)
{
    u32 ally = sCommanding[monId] - 1u;

    sCommanding[monId] = 0;
    if (ally < BATTLE_MAX_MON_ID) {
        sCommandedBy[ally] = 0;
    }
    W2U_MoveState_SetCommanderForm(ally, 0);
}

static void CommanderEnd(BtlServerFlow *flow, u8 monId)
{
    BattleHandlerHideTurnParam *show;
    BattleMon *mon;

    CommanderForget(monId);
    mon = FormsMon(flow, monId);
    if (!mon || IsFainted(mon)) {
        return;
    }
    CommanderPushFlag(flow, monId, HANDLER_CMD_RESET_CONTINUE_FLAG, CONT_FLAG_RECHARGE);
    if (CheckCondition(mon, CONDITION_CANT_ESCAPE)) {         /* free again (not left to the link's cleanup) */
        BattleHandlerCureConditionParam *cure =
            (BattleHandlerCureConditionParam *)BattleHandler_PushWork(flow, HANDLER_CMD_CURE_CONDITION, monId);
        cure->condition = CONDITION_CANT_ESCAPE;
        cure->monIds[0] = monId;
        cure->count = 1;
        cure->useString = 1;                                /* and no message */
        BattleHandler_PopWork(flow, cure);
    }
    show = (BattleHandlerHideTurnParam *)BattleHandler_PushWork(flow, HANDLER_CMD_HIDE_TURN_CANCEL, monId);
    show->monIndex = monId;
    show->flag = CONT_FLAG_SHADOW_FORCE;                    /* clears the flag and shows the sprite again */
    BattleHandler_PopWork(flow, show);
}

/* Showdown's onStart + onAnySwitchIn: any Pokémon entering (Tatsugiri itself, or a new Dondozo beside it) */
static void HandlerCommanderSwitchIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    CommanderTry(flow, monId);
}

static void HandlerCommanderFainted(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (monId >= BATTLE_MAX_MON_ID || !sCommanding[monId]) {
        return;
    }
    if (W2U_Subject() == sCommanding[monId] - 1u) {
        CommanderEnd(flow, monId);
    }
}

static void HandlerCommanderSwitchOut(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (monId < BATTLE_MAX_MON_ID && W2U_Subject() == monId && sCommanding[monId]) {
        CommanderForget(monId);
    }
}

static b32 CommanderPair(u8 monId, u32 other)
{
    return monId < BATTLE_MAX_MON_ID && sCommanding[monId] && (other == monId || other == sCommanding[monId] - 1u);
}

/* Tatsugiri is inside Dondozo: an action it still gets (a foe AI's choice) does nothing, silently */
static void HandlerCommanderSkipAction(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (monId >= BATTLE_MAX_MON_ID || !sCommanding[monId] || W2U_Subject() != monId) {
        return;
    }
    BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_NO_REACTION);
    BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1);
}

/* The move flow clears a Pokémon's hide flags after any action it started hidden (a charge move's release; flags
 * only, the sprite stays hidden), the cancelled ones included: hide again */
static void HandlerCommanderActionEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (monId < BATTLE_MAX_MON_ID && sCommanding[monId] && W2U_Subject() == monId) {
        CommanderHide(flow, monId);
    }
}

static void HandlerCommanderTurnEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)work;
    if (monId < BATTLE_MAX_MON_ID && sCommanding[monId]) {
        CommanderHide(flow, monId);
        CommanderSkipMenu(flow, monId);
    }
}

static void HandlerCommanderNoRun(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (CommanderPair(monId, W2U_Subject())) {
        BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1);
    }
}

static void HandlerCommanderNoForceOut(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work)
{
    (void)item;
    (void)flow;
    (void)work;
    if (CommanderPair(monId, W2U_Defender())) {
        BattleEventVar_RewriteValue(VAR_FAIL_FLAG, 1);
    }
}

W2U_HANDLER_TABLE(IceFaceHandlers) = {
    { EVENT_MOVE_DAMAGE_PROCESSING_END, HandlerIceFacePreventDamage },
    { EVENT_DETERMINE_MOVE_DAMAGE, HandlerIceFaceBreak },
    { EVENT_SWITCH_IN, HandlerIceFaceRestoreOnEntry },
    { EVENT_AFTER_WEATHER_CHANGE, HandlerIceFaceRestore },
};
W2U_MECHANIC(ABILITY, ABIL_ICE_FACE, IceFaceHandlers);

W2U_HANDLER_TABLE(GulpMissileHandlers) = {
    { EVENT_AFTER_KO, HandlerGulpMissileSurf },
    { EVENT_CHARGE_UP_START, HandlerGulpMissileDive },
    { EVENT_AFTER_DAMAGE_REACTION, HandlerGulpMissileSpit },
    { EVENT_SWITCH_OUT_END, HandlerGulpMissileReset },
    { EVENT_SWITCH_IN, HandlerGulpMissileReset },
};
W2U_MECHANIC(ABILITY, ABIL_GULP_MISSILE, GulpMissileHandlers);

W2U_HANDLER_TABLE(HungerSwitchHandlers) = {
    { EVENT_TURN_CHECK_END, HandlerHungerSwitch },
};
W2U_MECHANIC(ABILITY, ABIL_HUNGER_SWITCH, HungerSwitchHandlers);

W2U_HANDLER_TABLE(ZeroToHeroHandlers) = {
    { EVENT_SWITCH_IN, HandlerZeroToHeroEntry },
};
W2U_MECHANIC(ABILITY, ABIL_ZERO_TO_HERO, ZeroToHeroHandlers);

W2U_HANDLER_TABLE(CommanderHandlers) = {
    { EVENT_SWITCH_IN, HandlerCommanderSwitchIn },
    { EVENT_NOTIFY_FAINTED, HandlerCommanderFainted },
    { EVENT_SWITCH_OUT_END, HandlerCommanderSwitchOut },
    { EVENT_MOVE_EXECUTE_CHECK1, HandlerCommanderSkipAction },
    { EVENT_ACTION_END, HandlerCommanderActionEnd },
    { EVENT_TURN_CHECK_DONE, HandlerCommanderTurnEnd },
    { EVENT_PREVENT_RUN, HandlerCommanderNoRun },
    { EVENT_FORCE_OUT_CHECK, HandlerCommanderNoForceOut },
};
W2U_MECHANIC(ABILITY, ABIL_COMMANDER, CommanderHandlers);
