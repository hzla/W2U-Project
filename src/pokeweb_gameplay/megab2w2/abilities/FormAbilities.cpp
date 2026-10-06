// Gen 8 / 9 form abilities (Showdown's rules, data/abilities.ts; 2026-10-06), W2U battle module abilities/mb_forms.
// Written in W2U's style (w2u_battle.h types, as w2u_abilities.cpp's Disguise / Schooling), not ported from MegaB2W2
// (its registry lists these abilities without logic).
//   Ice Face (Eiscue)        Ice Face form (0) takes one physical hit for no damage and breaks into Noice Face (1);
//                            back to Ice Face on entry or when hail starts (W2U's stand-in for snow). Noice Face
//                            survives switching (w2u_mega.cpp W2U_AbilityPreservesFormOnSwitchOut). Breakable.
//   Gulp Missile (Cramorant) Surf hitting, or Dive's charge turn, catches prey: Gulping (more than half HP) or
//                            Gorging. Hit by an attack while it holds prey: the attacker loses 1/4 of its max HP, then
//                            Defense -1 (Gulping) or paralysis (Gorging), and the prey is gone. W2U has no Gulping /
//                            Gorging form records or sprites: the state is kept here and shown with the popup instead.
//   Hunger Switch (Morpeko)  every turn end Full Belly (0) <-> Hangry (1), no popup; back to Full Belly on switching out
//                            (Aura Wheel's type follows the form: w2u_moves.cpp).
//   Zero to Hero (Palafin)   switching out in Zero Form leaves as Hero Form (w2u_mega.cpp BattleMon_ClearForSwitchOut:
//                            form, stats, kept for the battle); the next entry announces it once ("X underwent a heroic
//                            transformation!").
//   Commander (Tatsugiri)    doubles: with an ally Dondozo on the field, Tatsugiri goes inside it ("X was swallowed by
//                            Y and became its commander!"): Tatsugiri is hidden (the Shadow Force flag: no move hits it,
//                            its sprite vanishes), its own actions are cancelled silently, and neither Pokemon can
//                            switch out (Mean Look's condition) or be forced out; Dondozo gets +2 Attack, Defense, Sp. Atk, Sp. Def and Speed.
//                            Ends when Dondozo faints (Tatsugiri reappears). As in Showdown the command menu skips
//                            Tatsugiri (the recharge flag, set again each turn; mb_resident.cpp drops the recharge
//                            action's message for it) and No Guard / Lock-On don't reach it (mb_resident.cpp).
#include "w2u_abilities.h"
#include "w2u_moves.h"
#include "w2u_battle.h"
#include "Moves.h"
#include "species_ids.h"

namespace {

// mb_ids.h BTLMSG_SET_ZERO_TO_HERO / _COMMANDER (that header clashes with w2u_battle.h, so the ids are mirrored here)
constexpr u16 BTLMSG_SET_ZERO_TO_HERO = 1445;
constexpr u16 BTLMSG_SET_COMMANDER = 1448;

constexpr u32 FA_EISCUE = 875, FA_CRAMORANT = 845, FA_MORPEKO = 877, FA_PALAFIN = 964, FA_DONDOZO = 977,
              FA_TATSUGIRI = 978;
constexpr u32 FA_MAX_POKE = 24;
constexpr u8 GULP_NONE = 0, GULP_GULPING = 1, GULP_GORGING = 2;

// per battle (the module is loaded fresh each battle)
u8 sGulp[FA_MAX_POKE];
u8 sHeroAnnounced[FA_MAX_POKE];
u8 sCommanding[FA_MAX_POKE];        // Tatsugiri -> its Dondozo's ID + 1 (0: not commanding)
u8 sCommandedBy[FA_MAX_POKE];       // Dondozo -> its Tatsugiri's ID + 1

// Gen 5 engine pieces that W2U's headers don't name (ov167, read from its disassembly 2026-10-06)
struct FA_SetConditionFlag {        // EFFECT_SET_CONDITION_FLAG (0x17): ov167 0x21AD2F8 reads flag +4, pokeID +8
    HandlerParam_Header header;
    u32 flag;
    u8 pokeID;
};
struct FA_HideTurnCancel {          // EFFECT_CANCEL_SEMI_INVULN (0x36): ov167 0x21AE21C reads pokeID +4, flag +8
    HandlerParam_Header header;
    u8 pokeID;
    u32 flag;
    HandlerParam_StrParams exStr;
};
constexpr u32 FA_EFFECT_SET_CONDITION_FLAG = 0x17;
constexpr u32 FA_EFFECT_RESET_CONDITION_FLAG = 0x18;  // same layout (ov167 0x21AD324)
constexpr u32 FA_EFFECT_CANCEL_SEMI_INVULN = 0x36;
constexpr u32 FA_CONDITIONFLAG_SHADOWFORCE = 0x6;   // hidden: no move hits (Shadow Force's charge turn)
// the recharge flag (Hyper Beam): the client skips the command menu (ov167 0x21B46B8) and the server clears the flag
// once the actions are in (0x219F73C), so it is set again at every turn end
constexpr u32 FA_CONDITIONFLAG_NOACTION = 0xC;
// the charge-move hide command: (pokeID, 1) hides the sprite, (pokeID, 0) shows it (ov167 0x21A8FB8 sends 0)
constexpr u32 FA_SCID_CHARGE_HIDE = 0x31;
constexpr u32 FA_EVENT_PREVENT_RUN = 0x0C;          // Shadow Tag's event: may VAR_MON_ID flee? (fleeing only)
// Switching is checked by the client (ov167 0x21B4BFC): trapping abilities on the other side, then the Mean Look
// (0x16), Bind (0x8) and Ingrain (0x15) conditions. Commander uses Mean Look's: Tatsugiri's lasts while its Dondozo
// is on the field (condition data linked to it: type 3, ID in bits 3-8, ov167 0x21CE21C), Dondozo's is permanent.
constexpr CONDITION FA_CONDITION_BLOCK = (CONDITION)0x16;
constexpr ConditionData FA_LinkedTo(u32 pokeID) { return 3u | ((pokeID & 0x3Fu) << 3); }
constexpr u32 FA_EVENT_CHECK_FORCE_SWITCH = 0x8B;   // Suction Cups' event: may VAR_DEFENDING_MON be forced out?

BattleMon* Mon(ServerFlow* sf, u32 pokeID)
{
    if (!sf || !sf->pokeCon || pokeID >= FA_MAX_POKE) return 0;
    return PokeCon_GetBattleMon(sf->pokeCon, pokeID);
}

bool Usable(BattleMon* mon, u32 species)
{
    return mon && mon->species == species && !BattleMon_IsFainted(mon) && !BattleMon_TransformCheck(mon);
}

void PushForm(ServerFlow* sf, u32 pokeID, u32 form, bool keep, bool popup)
{
    HandlerParam_ChangeForm* change =
        (HandlerParam_ChangeForm*)BattleHandler_PushWork(sf, EFFECT_CHANGE_FORM, pokeID);
    if (popup) change->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    change->pokeID = (u8)pokeID;
    change->newForm = (u8)form;
    change->dontResetOnSwitch = keep ? 1 : 0;
    HandlerParam_StrParams none = {};
    change->exStr = none;
    BattleHandler_PopWork(sf, change);
}

void Popup(ServerFlow* sf, u32 pokeID, bool in)
{
    BattleHandler_PushRun(sf, in ? EFFECT_ABILITY_POPUP_ADD : EFFECT_ABILITY_POPUP_REMOVE, pokeID);
}

// ---- Ice Face ------------------------------------------------------------------------------------------------

BattleMon* IceFaceIntact(ServerFlow* sf, u32 pokeID)
{
    if (pokeID != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON)) return 0;
    BattleMon* mon = Mon(sf, pokeID);
    if (!Usable(mon, FA_EISCUE) || BattleMon_GetValue(mon, VALUE_FORM) != 0 || BattleMon_IsSubstituteActive(mon)) {
        return 0;
    }
    const MOVE_ID move = (MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID);
    return PML_MoveGetCategory(move) == 1 ? mon : 0;     // physical only
}

void HandlerIceFacePreventDamage(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    // damage estimation and the real hit alike (as Disguise): the strike deals nothing
    if (IceFaceIntact(sf, pokeID)) BattleEventVar_RewriteValue(VAR_DAMAGE, 0);
}

void HandlerIceFaceBreak(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (!IceFaceIntact(sf, pokeID)) return;
    PushForm(sf, pokeID, 1, true, true);                   // Noice Face, kept on switching
}

void HandlerIceFaceRestore(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    BattleMon* mon = Mon(sf, pokeID);
    if (!Usable(mon, FA_EISCUE) || BattleMon_GetValue(mon, VALUE_FORM) != 1) return;
    if (ServerEvent_GetWeather(sf) != WEATHER_HAIL) return;
    PushForm(sf, pokeID, 0, true, true);
}

void HandlerIceFaceRestoreOnEntry(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work)
{
    if (pokeID != (u32)BattleEventVar_GetValue(VAR_MON_ID)) return;
    HandlerIceFaceRestore(item, sf, pokeID, work);
}

// ---- Gulp Missile --------------------------------------------------------------------------------------------

void GulpCatch(ServerFlow* sf, u32 pokeID)
{
    BattleMon* mon = Mon(sf, pokeID);
    if (!Usable(mon, FA_CRAMORANT) || sGulp[pokeID] != GULP_NONE) return;
    sGulp[pokeID] = (u32)mon->currentHP * 2u <= (u32)mon->maxHP ? GULP_GORGING : GULP_GULPING;
    Popup(sf, pokeID, true);                                // no Gulping / Gorging sprite: the popup shows the catch
    Popup(sf, pokeID, false);
}

void HandlerGulpMissileSurf(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    if ((MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_SURF) return;
    GulpCatch(sf, pokeID);
}

void HandlerGulpMissileDive(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID != (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON)) return;
    if ((MOVE_ID)BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE_DIVE) return;
    GulpCatch(sf, pokeID);
}

void HandlerGulpMissileSpit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID != (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON) || pokeID >= FA_MAX_POKE) return;
    const u8 prey = sGulp[pokeID];
    if (prey == GULP_NONE || BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG)) return;
    const u32 attacker = (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON);
    BattleMon* source = Mon(sf, attacker);
    if (!source || attacker == pokeID || BattleMon_IsFainted(source)) return;
    sGulp[pokeID] = GULP_NONE;
    Popup(sf, pokeID, true);
    HandlerParam_Damage* damage = (HandlerParam_Damage*)BattleHandler_PushWork(sf, EFFECT_DAMAGE, pokeID);
    damage->pokeID = (u8)attacker;
    damage->damage = (u16)DivideMaxHPZeroCheck(source, 4u);
    BattleHandler_PopWork(sf, damage);
    if (prey == GULP_GULPING) {
        HandlerParam_ChangeStatStage* stat =
            (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(sf, EFFECT_CHANGE_STAT_STAGE, pokeID);
        stat->stat = STATSTAGE_DEFENSE;
        stat->volume = -1;
        stat->moveAnimation = 1;
        stat->pokeCount = 1;
        stat->pokeID[0] = (u8)attacker;
        BattleHandler_PopWork(sf, stat);
    } else {
        HandlerParam_AddCondition* add =
            (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
        add->pokeID = (u8)attacker;
        add->condition = CONDITION_PARALYSIS;
        add->condData = MakeBasicStatus(CONDITION_PARALYSIS);
        BattleHandler_PopWork(sf, add);
    }
    Popup(sf, pokeID, false);
}

void HandlerGulpMissileReset(BattleEventItem*, ServerFlow*, u32 pokeID, u32*)
{
    if (pokeID == (u32)BattleEventVar_GetValue(VAR_MON_ID) && pokeID < FA_MAX_POKE) sGulp[pokeID] = GULP_NONE;
}

// ---- Hunger Switch -------------------------------------------------------------------------------------------

void HandlerHungerSwitch(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    BattleMon* mon = Mon(sf, pokeID);
    if (!Usable(mon, FA_MORPEKO)) return;
    const u32 form = BattleMon_GetValue(mon, VALUE_FORM);
    if (form > 1) return;
    PushForm(sf, pokeID, form ? 0 : 1, false, false);       // back to Full Belly on switching out
}

// ---- Zero to Hero --------------------------------------------------------------------------------------------

void HandlerZeroToHeroEntry(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID != (u32)BattleEventVar_GetValue(VAR_MON_ID) || pokeID >= FA_MAX_POKE) return;
    BattleMon* mon = Mon(sf, pokeID);
    if (!Usable(mon, FA_PALAFIN) || BattleMon_GetValue(mon, VALUE_FORM) != 1 || sHeroAnnounced[pokeID]) return;
    sHeroAnnounced[pokeID] = 1;
    Popup(sf, pokeID, true);
    HandlerParam_Message* message = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&message->str, 2u, BTLMSG_SET_ZERO_TO_HERO);
    BattleHandler_AddArg(&message->str, pokeID);
    BattleHandler_PopWork(sf, message);
    Popup(sf, pokeID, false);
}

// ---- Commander ------------------------------------------------------------------------------------------------

u32 DoublesAllyID(ServerFlow* sf, u32 pokeID)
{
    if (BtlSetup_GetBattleStyle(sf->mainModule) != BTL_STYLE_DOUBLE) return FA_MAX_POKE;
    const u32 pos = Handler_PokeIDToPokePos(sf, pokeID);
    if (pos >= 4) return FA_MAX_POKE;
    return Handler_PokePosToPokeID(sf, pos ^ 2u);           // doubles: 0 / 2 player side, 1 / 3 foe side
}

void PushBoost(ServerFlow* sf, u32 pokeID, u32 target, StatStage stat)
{
    HandlerParam_ChangeStatStage* boost =
        (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(sf, EFFECT_CHANGE_STAT_STAGE, pokeID);
    boost->stat = stat;
    boost->volume = 2;
    boost->moveAnimation = 1;
    boost->pokeCount = 1;
    boost->pokeID[0] = (u8)target;
    BattleHandler_PopWork(sf, boost);
}

void PushConditionFlag(ServerFlow* sf, u32 pokeID, u32 target, u32 flag, bool set)
{
    FA_SetConditionFlag* work = (FA_SetConditionFlag*)BattleHandler_PushWork(
        sf, (BattleHandlerEffect)(set ? FA_EFFECT_SET_CONDITION_FLAG : FA_EFFECT_RESET_CONDITION_FLAG), pokeID);
    work->flag = flag;
    work->pokeID = (u8)target;
    BattleHandler_PopWork(sf, work);
}

// Tatsugiri hidden (re-asserted after Tatsugiri's actions and at every turn end)
void CommanderHide(ServerFlow* sf, u32 pokeID)
{
    PushConditionFlag(sf, pokeID, pokeID, FA_CONDITIONFLAG_SHADOWFORCE, true);
}

// no command menu for Tatsugiri in the coming turn
void CommanderSkipMenu(ServerFlow* sf, u32 pokeID)
{
    PushConditionFlag(sf, pokeID, pokeID, FA_CONDITIONFLAG_NOACTION, true);
}

void PushTrap(ServerFlow* sf, u32 pokeID, u32 target, ConditionData data)
{
    HandlerParam_AddCondition* add =
        (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
    add->pokeID = (u8)target;
    add->condition = FA_CONDITION_BLOCK;
    add->condData = data;
    BattleHandler_PopWork(sf, add);
}

void CommanderTry(ServerFlow* sf, u32 pokeID)
{
    if (pokeID >= FA_MAX_POKE || sCommanding[pokeID]) return;
    BattleMon* mon = Mon(sf, pokeID);
    if (!Usable(mon, FA_TATSUGIRI)) return;
    const u32 ally = DoublesAllyID(sf, pokeID);
    BattleMon* allyMon = Mon(sf, ally);
    if (!allyMon || allyMon->species != FA_DONDOZO || BattleMon_IsFainted(allyMon) || sCommandedBy[ally]) return;
    sCommanding[pokeID] = (u8)(ally + 1);
    sCommandedBy[ally] = (u8)(pokeID + 1);
    W2U_MoveState_SetCommanderForm(ally, mon->form + 1);

    Popup(sf, pokeID, true);
    HandlerParam_Message* message = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&message->str, 2u, BTLMSG_SET_COMMANDER);
    BattleHandler_AddArg(&message->str, pokeID);
    BattleHandler_AddArg(&message->str, ally);
    BattleHandler_PopWork(sf, message);
    CommanderHide(sf, pokeID);
    CommanderSkipMenu(sf, pokeID);
    ServerDisplay_AddCommon(sf->serverCommandQueue, (ServerCommandID)FA_SCID_CHARGE_HIDE, pokeID, 1);
    Popup(sf, pokeID, false);
    PushTrap(sf, pokeID, pokeID, FA_LinkedTo(ally));
    PushTrap(sf, pokeID, ally, Condition_MakePermanent());

    PushBoost(sf, pokeID, ally, STATSTAGE_ATTACK);
    PushBoost(sf, pokeID, ally, STATSTAGE_DEFENSE);
    PushBoost(sf, pokeID, ally, STATSTAGE_SPECIAL_ATTACK);
    PushBoost(sf, pokeID, ally, STATSTAGE_SPECIAL_DEFENSE);
    PushBoost(sf, pokeID, ally, STATSTAGE_SPEED);
}

void CommanderEnd(ServerFlow* sf, u32 pokeID)
{
    const u32 ally = sCommanding[pokeID] - 1u;
    sCommanding[pokeID] = 0;
    if (ally < FA_MAX_POKE) sCommandedBy[ally] = 0;
    W2U_MoveState_SetCommanderForm(ally, 0);
    BattleMon* mon = Mon(sf, pokeID);
    if (!mon || BattleMon_IsFainted(mon)) return;
    PushConditionFlag(sf, pokeID, pokeID, FA_CONDITIONFLAG_NOACTION, false);
    if (BattleMon_CheckIfMoveCondition(mon, FA_CONDITION_BLOCK)) {   // free again (not left to the link's cleanup)
        HandlerParam_CureCondition* cure =
            (HandlerParam_CureCondition*)BattleHandler_PushWork(sf, EFFECT_CURE_STATUS, pokeID);
        cure->condition = FA_CONDITION_BLOCK;
        cure->pokeID[0] = (u8)pokeID;
        cure->pokeCount = 1;
        cure->msgDisable = 1;
        BattleHandler_PopWork(sf, cure);
    }
    FA_HideTurnCancel* show = (FA_HideTurnCancel*)BattleHandler_PushWork(
        sf, (BattleHandlerEffect)FA_EFFECT_CANCEL_SEMI_INVULN, pokeID);
    show->pokeID = (u8)pokeID;
    show->flag = FA_CONDITIONFLAG_SHADOWFORCE;        // clears the flag and shows the sprite again
    HandlerParam_StrParams none = {};
    show->exStr = none;
    BattleHandler_PopWork(sf, show);
}

// Showdown's onStart + onAnySwitchIn: any Pokemon entering (Tatsugiri itself, or a new Dondozo beside it)
void HandlerCommanderSwitchIn(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    CommanderTry(sf, pokeID);
}

void HandlerCommanderFainted(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID >= FA_MAX_POKE || !sCommanding[pokeID]) return;
    if ((u32)BattleEventVar_GetValue(VAR_MON_ID) == sCommanding[pokeID] - 1u) CommanderEnd(sf, pokeID);
}

void HandlerCommanderSwitchOut(BattleEventItem*, ServerFlow*, u32 pokeID, u32*)
{
    if (pokeID >= FA_MAX_POKE || pokeID != (u32)BattleEventVar_GetValue(VAR_MON_ID) || !sCommanding[pokeID]) return;
    const u32 ally = sCommanding[pokeID] - 1u;
    sCommanding[pokeID] = 0;
    if (ally < FA_MAX_POKE) sCommandedBy[ally] = 0;
    W2U_MoveState_SetCommanderForm(ally, 0);
}

bool CommanderPair(u32 pokeID, u32 mon)
{
    return pokeID < FA_MAX_POKE && sCommanding[pokeID] && (mon == pokeID || mon == sCommanding[pokeID] - 1u);
}

void HandlerCommanderSkipAction(BattleEventItem*, ServerFlow*, u32 pokeID, u32*)
{
    // Tatsugiri is inside Dondozo: an action it still gets (a foe AI's choice) does nothing, silently
    if (pokeID >= FA_MAX_POKE || !sCommanding[pokeID] || pokeID != (u32)BattleEventVar_GetValue(VAR_MON_ID)) return;
    BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVE_FAIL_NO_REACTION);
    BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
}

// The move flow clears a Pokemon's hide flags after any action it started hidden (a charge move's release, ov167
// 0x21A1DB0 -> 0x21A3944; flags only, the sprite stays hidden), the cancelled ones included: hide again.
void HandlerCommanderActionEnd(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID >= FA_MAX_POKE || !sCommanding[pokeID] || pokeID != (u32)BattleEventVar_GetValue(VAR_MON_ID)) return;
    CommanderHide(sf, pokeID);
}

void HandlerCommanderTurnEnd(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*)
{
    if (pokeID >= FA_MAX_POKE || !sCommanding[pokeID]) return;
    CommanderHide(sf, pokeID);
    CommanderSkipMenu(sf, pokeID);
}

void HandlerCommanderTrap(BattleEventItem*, ServerFlow*, u32 pokeID, u32*)
{
    if (CommanderPair(pokeID, (u32)BattleEventVar_GetValue(VAR_MON_ID))) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    }
}

void HandlerCommanderNoForceOut(BattleEventItem*, ServerFlow*, u32 pokeID, u32*)
{
    if (CommanderPair(pokeID, (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON))) {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    }
}

} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json, module abilities/mb_forms)
BattleEventHandlerTableEntry MB_IceFaceHandlers[4] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_END, HandlerIceFacePreventDamage},
    {EVENT_DETERMINE_MOVE_DAMAGE, HandlerIceFaceBreak},
    {EVENT_SWITCH_IN, HandlerIceFaceRestoreOnEntry},
    {EVENT_AFTER_WEATHER_CHANGE, HandlerIceFaceRestore},
};
BattleEventHandlerTableEntry MB_GulpMissileHandlers[5] = {
    {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, HandlerGulpMissileSurf},
    {EVENT_CHARGE_UP_START, HandlerGulpMissileDive},
    {EVENT_AFTER_DAMAGE_REACTION, HandlerGulpMissileSpit},
    {EVENT_SWITCH_OUT_END, HandlerGulpMissileReset},
    {EVENT_SWITCH_IN, HandlerGulpMissileReset},
};
BattleEventHandlerTableEntry MB_HungerSwitchHandlers[1] = {
    {EVENT_TURN_CHECK_END, HandlerHungerSwitch},
};
BattleEventHandlerTableEntry MB_ZeroToHeroHandlers[1] = {
    {EVENT_SWITCH_IN, HandlerZeroToHeroEntry},
};
BattleEventHandlerTableEntry MB_CommanderHandlers[8] = {
    {EVENT_SWITCH_IN, HandlerCommanderSwitchIn},
    {EVENT_NOTIFY_FAINTED, HandlerCommanderFainted},
    {EVENT_SWITCH_OUT_END, HandlerCommanderSwitchOut},
    {EVENT_MOVE_EXECUTE_CHECK1, HandlerCommanderSkipAction},
    {EVENT_ACTION_PROCESSING_END, HandlerCommanderActionEnd},
    {EVENT_TURN_CHECK_DONE, HandlerCommanderTurnEnd},
    {(BattleEventType)FA_EVENT_PREVENT_RUN, HandlerCommanderTrap},
    {(BattleEventType)FA_EVENT_CHECK_FORCE_SWITCH, HandlerCommanderNoForceOut},
};
