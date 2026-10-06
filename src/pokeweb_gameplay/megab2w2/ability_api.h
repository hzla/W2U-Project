// Ported from MegaB2W2 (abilities/ability_api.h); see docs/megab2w2-integration.md.
// Helpers for custom ability logic (data/abilities.yml `logic:`, docs/ABILITIES.md "Writing ability logic",
// docs/ABILITY_EVENTS.md for which vanilla abilities use which event).
//
// A logic file defines `extern "C" const BattleEventHandlerTableEntry* EventAdd<Logic>(u32* packed)` returning a
// table of { event, handler }. A handler is `void H(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32* work)`:
// pokeID is the ability holder; the event's variables (BattleEventVar_*) say who acts on whom with what.
// Messages and popups go through the handler-effect queue (BattleHandler_PushWork / PushRun) like vanilla.
#pragma once
#include "battle.h"
#include "battle_events.h"
#include "mb_ids.h"

extern "C" {
u32 PML_MoveGetParam(u16 move, u32 param);
b32 PML_MoveIsDamaging(u16 move);
b32 IsAllyMonID(u32 a, u32 b);
BattleMon* GetBattleMon(ServerFlow* sf, u32 pokeID);                 // sub_21AB874: sf+8 pokecon
u32  GetWeather(ServerFlow* sf);                 // ov167 0x21ABE08: the weather as abilities see it (Air Lock -> 0)
b32  IsMonFullHP(BattleMon* bm);                 // 0x21BB388 (Multiscale)
// vanilla ability helpers (ov167), as the abilities that use them call them
b32  CommonDamageRecoverCheck(ServerFlow* sf, u32 pokeID, u32 type);     // 0x21C0110: a `type` move at the holder ->
                                                                         // no effect (Volt Absorb, Sap Sipper)
void CommonTypeRecoverHP(ServerFlow* sf, u32 pokeID, u32 denominator);   // 0x21C0144: heal 1/denominator (or "unaffected")
void CommonTypeNoEffectRankUp(ServerFlow* sf, u32 pokeID, u32 stat, int stages);   // 0x21C01D4 (Sap Sipper)
b32  HandlerCommonGuardStatus(ServerFlow* sf, u32 pokeID, u32 condition);         // 0x21BEEB0: block VAR_CONDITION
void CommonAbilityCureStatus(ServerFlow* sf, u32 pokeID, u32 condition);          // 0x21BEF44 (on entry / gain)
void CommonAbilityCureStatusCore(ServerFlow* sf, u32 pokeID, u32 condition);      // 0x21BEF64 (action end)
// vanilla handlers, usable as they are in our tables
void HandlerAddStatusFailedCommon(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);   // 0x21BEF34
void HandlerInsomniaYawnCheck(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);       // 0x21BECC8
void HandlerWaterVeil(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);               // 0x21BED6C
void HandlerWaterVeilCureStatus(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);     // 0x21BED80
void HandlerWaterVeilActionEnd(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);      // 0x21BED90
void HandlerScrappy(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);                 // 0x21C03B0
void HandlerKeenEyeCheck(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);            // 0x21BEAA8
void HandlerKeenEyeGuard(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);            // 0x21BEAB8
void HandlerSuctionCups(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);             // 0x21C0DC8
void HandlerLevitate(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);                // 0x21C045C: 0x12 floating
void HandlerLevitateAddImmunity(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);     // 0x21C0484: 0x1B popup
void HandlerLevitateTurnCheck(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);       // 0x21C04D4: 0x76
void HandlerIntimidateMemberIn(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);      // 0x21BDE5C
b32  AbilityEvent_RollEffectChance(ServerFlow* sf, u32 percent);       // 0x21BDE28: % roll (Serene Grace etc.)
u32  GetBattleMonStat(BattleMon* bm, u32 value);                         // 0x21BB1F4: 8 Atk 9 Def 0xA SpA 0xB SpD 0xC Spe
u32  GetBattleMonStatus(BattleMon* bm);                                  // 0x21BBAE8: 0 none, COND_* otherwise
b32  GetAdditionalConditionFlag(BattleMon* bm, u32 flag);               // 0x21BB41C: flag 0 = on the field a whole turn
u16  BattleMon_GetHeldItem(BattleMon* bm);
b32  PML_MoveIsAlwaysCrit(u16 move);
u16  PML_MoveGetSickCont(u16 move);                                      // 0x20214DC: the move's status continuation
void BTL_MakeSickCont(u32 moveCont, BattleMon* attacker, u32* out);      // 0x21BD4C4: -> battle continuation
b32  HandlerTargetsContain(u32 pokeID);                                  // 0x21CDE78: VAR_TARGET0.. holds pokeID
b32  ItemSwapBlocked(ServerFlow* sf, u32 receiver, u32 giver);          // 0x21CDF68: Pickpocket's "can't take it" check
u32  ServerEvent_GetMovePriority(ServerFlow* sf, u16 move, BattleMon* bm); // 0x21A03C0: priority + 7 after event 0x11
b32  CheckCondition(BattleMon* bm, u32 condition);                       // BattleMon_CheckIfMoveCondition (0x10 Gastro Acid)
u32  GetSideFromMonID(u32 pokeID);                                       // 0x219D35C
b32  SideEffect_IsActive(u32 side, u32 effect);                          // 0x21C6150 (thunk to ov169): SIDE_EFFECT_* on side
u32  Battle_GetMonPos(ServerFlow* sf, u32 pokeID);                       // 0x21ABB90: battle position, 6 = not on the field
u32  Battle_ExpandPos(ServerFlow* sf, u16 expr, u8* outIDs);             // 0x21ABAE8: (range << 8 | pos) -> pokeIDs, count
u32  DivideMaxHPZeroCheck(BattleMon* bm, u32 denominator);              // 0x21BD3C8: max HP / denominator, at least 1
u32  MakeConditionParamPermanent(u16 move);                              // 0x21CE254: a permanent cont (Choice lock)
u32  GetPokeType(BattleMon* bm);                                         // 0x21BB03C: packed type pair
b32  PokeTypePair_HasType(u32 typePair, u32 type);                         // ESDB (batch 4): the pair has the type
u16  PokeTypePair_MakePure(u32 type);                                    // 0x21CE570
void ServerEvent_GetMoveParam(ServerFlow* sf, u16 move, BattleMon* attacker, void* out);   // final type at +6
void* GetPartyData(void* pokecon, u32 clientID);                        // 0x219D408: {BattleMon* members[6]; u8 count @0x18}
u32  PokeParty_GetParam(void* pkm, u32 param, void* extra);              // ARM9: 0x4C = is an egg
void BattleHandler_PushRun(ServerFlow* sf, u32 effect, u32 pokeID);   // effects without parameters (popups)

// W2U: contact as used now (Long Reach, Protective Pads), resident in White2Upgrade.dll
b32 W2U_MoveMakesContact(ServerFlow* sf, u16 move, u32 attacker);
u32 sub_21BD56C(u32 condition);                 // ov167: the default continuation of a major status (burn, poison...)
b32 sub_21ABF54(ServerFlow* sf);                // ov167: Mummy / Flame Body skip their reaction while it is set
}

namespace ability {

// PML_MoveGetParam (ARM9 0x20212AC) parameters (its 32-case switch, decoded: docs/MODLOG.md)
enum : u32 { MOVE_TYPE = 0x00, MOVE_EFFECT_CLASS = 0x01, MOVE_CATEGORY = 0x02, MOVE_POWER = 0x03,
             MOVE_ACCURACY = 0x04, MOVE_PP = 0x05, MOVE_PRIORITY = 0x06, MOVE_TARGET = 0x1B };
enum : u32 { CATEGORY_STATUS = 0, CATEGORY_PHYSICAL = 1, CATEGORY_SPECIAL = 2 };
// move targets (data/moves.yml `target`)
enum : u32 { TARGET_OTHER_SELECT = 0, TARGET_FRIEND_AND_USER = 1, TARGET_FRIEND_SELECT = 2, TARGET_ENEMY_SELECT = 3,
             TARGET_OTHER_ALL = 4, TARGET_ENEMY_ALL = 5, TARGET_FRIEND_ALL = 6, TARGET_USER = 7, TARGET_ALL = 8,
             TARGET_ENEMY_RANDOM = 9, TARGET_FIELD = 10, TARGET_FIELD_SIDE_ENEMY = 11, TARGET_FIELD_SIDE_FRIEND = 12 };
constexpr u32 RUN_POPUP_IN = 2, RUN_POPUP_OUT = 3;            // BattleHandler_PushRun effects (Soundproof)
constexpr u16 MSG_SET_DOESNT_AFFECT = 210;                    // bank 18: "It doesn't affect {0102:0}..." x3
constexpr u16 STRTYPE_SET = 2;                                // BattleHandler_StrSetup: bank 18, per-Pokémon variants
constexpr u16 MSG_SET_HP_RESTORED = 0x183;                    // bank 18: "{0}'s HP was restored." (CommonTypeRecoverHP)
constexpr u32 CONDITION_GASTRO_ACID = 0x10;                   // CheckCondition: the ability is suppressed
constexpr u32 POS_RANGE_FULL_FRIENDS = 7;                     // Battle_ExpandPos: the whole side of pos (Plus / Minus)
constexpr u32 POS_NONE = 6;
constexpr u32 MOVE_PARAM_TYPE = 6;                            // ServerEvent_GetMoveParam out: u8 final type at +6
constexpr u32 MAX_POKE_ID = 24;

inline u32 Attacker() { return (u32)BattleEventVar_GetValue(VAR_ATTACKING_MON); }
inline u32 Defender() { return (u32)BattleEventVar_GetValue(VAR_DEFENDING_MON); }
inline u32 Subject() { return (u32)BattleEventVar_GetValue(VAR_MON_ID); }
inline u16 Move() { return (u16)BattleEventVar_GetValue(VAR_MOVE_ID); }
inline u32 MoveCategory(u16 move) { return PML_MoveGetParam(move, MOVE_CATEGORY); }
inline u32 MoveTarget(u16 move) { return PML_MoveGetParam(move, MOVE_TARGET); }
inline bool IsStatusMove(u16 move) { return MoveCategory(move) == CATEGORY_STATUS; }

// The move picks Pokémon as targets (one, several or "all adjacent foes"), rather than the user itself, the
// field, a side, or every Pokémon at once (Haze, Perish Song): the moves a "can't be targeted by" ability stops.
inline bool TargetsPokemon(u16 move) {
    switch (MoveTarget(move)) {
        case TARGET_OTHER_SELECT: case TARGET_FRIEND_AND_USER: case TARGET_FRIEND_SELECT: case TARGET_ENEMY_SELECT:
        case TARGET_OTHER_ALL: case TARGET_ENEMY_ALL: case TARGET_ENEMY_RANDOM: return true;
        default: return false;
    }
}

// The holder's ability popup around a message: popup in, set message (arg 0 = pokeID), popup out.
inline void PopupSetMessage(ServerFlow* sf, u32 pokeID, u16 msg) {
    BattleHandler_PushRun(sf, RUN_POPUP_IN, pokeID);
    auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
    BattleHandler_StrSetup(&m->str, STRTYPE_SET, msg);
    BattleHandler_AddArg(&m->str, pokeID);
    BattleHandler_PopWork(sf, m);
    BattleHandler_PushRun(sf, RUN_POPUP_OUT, pokeID);
}

// Stat stage change for one Pokémon (as Defiant / Weak Armor push it): stat STAT_ATK .. STAT_EVASION, stages +-1..6.
// popup: the holder's ability popup around it (the header flag the vanilla abilities set).
enum : u32 { STAT_ATK = 1, STAT_DEF = 2, STAT_SPATK = 3, STAT_SPDEF = 4, STAT_SPEED = 5, STAT_ACCURACY = 6,
             STAT_EVASION = 7 };
inline void ChangeStatStage(ServerFlow* sf, u32 holderID, u32 targetID, u32 stat, int stages, bool popup) {
    auto* p = (HandlerParam_ChangeStatStage*)BattleHandler_PushWork(sf, EFFECT_CHANGE_STAT_STAGE, holderID);
    if (popup) p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->stat = stat;
    p->stages = (s8)stages;
    p->_e = 1;
    p->pokeCount = 1;
    p->pokeIDs[0] = (u8)targetID;
    BattleHandler_PopWork(sf, p);
}

// The damage simulation (ov167 0x21AB994, the AI's estimates) runs the damage-calc events too: sf+0x774 is its
// depth. Handlers on those events log only outside it (dozens of simulations a turn would flood the MLOG ring).
inline bool Simulating(ServerFlow* sf) { return *(u32*)((u8*)sf + 0x774) != 0; }
inline void MulRatio(int ratio) { BattleEventVar_MulValue(VAR_RATIO, ratio); }   // fx 4096
inline u32 MoveType() { return (u32)BattleEventVar_GetValue(VAR_MOVE_TYPE); }

// The Pokémon has this ability and it works (not suppressed by Gastro Acid): for hooks outside the event system,
// where the handler table is not consulted (Parental Bond, Corrosion).
inline bool HasActiveAbility(BattleMon* bm, u16 ability) {
    return bm && (u16)BattleMon_GetValue(bm, BMV_ABILITY) == ability && !CheckCondition(bm, CONDITION_GASTRO_ACID);
}
// The Pokémon is in battle (has a field position).
inline bool OnField(ServerFlow* sf, u32 pokeID) { return pokeID < MAX_POKE_ID && Battle_GetMonPos(sf, pokeID) != POS_NONE; }
// The lowest pokeID on the field with this ability working, or MAX_POKE_ID: field-wide effects that must apply once
// however many holders there are (Ruin abilities, Showdown's move.ruinedDef).
inline u32 FirstFieldHolder(ServerFlow* sf, u16 ability) {
    for (u32 id = 0; id < MAX_POKE_ID; ++id)
        if (OnField(sf, id) && HasActiveAbility(GetBattleMon(sf, id), ability)) return id;
    return MAX_POKE_ID;
}
// The highest of Attack .. Speed by raw stat (GetBattleMonStat 8 Atk .. 0xC Spe; ties: the first, Showdown's order),
// as STAT_ATK .. STAT_SPEED. Beast Boost, Protosynthesis.
inline u32 BestStat(BattleMon* bm) {
    u32 best = STAT_ATK, bestValue = 0;
    for (u32 i = 0; i < 5; ++i) {
        u32 v = GetBattleMonStat(bm, 8 + i);
        if (v > bestValue) { bestValue = v; best = STAT_ATK + i; }
    }
    return best;
}

// The same with stat stages applied (BattleMon values 1 Atk .. 5 Spe, 6 = neutral; x(2+s)/2 up, x2/(2-s) down):
// Showdown's getBestStat(false, true) - stages count, other modifiers do not. Protosynthesis / Quark Drive.
inline u32 BestStatWithStages(BattleMon* bm) {
    u32 best = STAT_ATK, bestValue = 0;
    for (u32 i = 0; i < 5; ++i) {
        int s = (int)GetBattleMonStat(bm, 1 + i) - 6;
        u32 v = GetBattleMonStat(bm, 8 + i);
        // u64: a u32 division by a variable calls __aeabi_uidiv, which the ESDB lacks (a branch to itself)
        v = s >= 0 ? v * (2 + s) / 2 : (u32)((u64)v * 2 / (u32)(2 - s));
        if (v > bestValue) { bestValue = v; best = STAT_ATK + i; }
    }
    return best;
}

// The holder's current ability: table-driven families (`logic:` shared by several abilities) find their row by it.
inline u16 HolderAbility(ServerFlow* sf, u32 pokeID) { return (u16)BattleMon_GetValue(GetBattleMon(sf, pokeID), BMV_ABILITY); }
// Row names exist in debug builds only (logs); release rows carry no strings.
#ifdef MEGA_DEBUG
#define ROW_NAME_FIELD const char* name;
#define ROW_NAME(n) , n
#else
#define ROW_NAME_FIELD
#define ROW_NAME(n)
#endif

// The move makes contact as used now: its contact flag, unless the attacker's Long Reach removes it. Logic that
// reacts to contact (Gooey, Fluffy, Tough Claws...) asks this; the engine's own contact checks are wrapped
// (LongReach.cpp).
inline bool MakesContact(ServerFlow* sf, u16 move) { return W2U_MoveMakesContact(sf, move, Attacker()) != 0; }
// Berries: item IDs 149 (Cheri) .. 212 (Rowap) - the whole vanilla Berry range (Cheek Pouch, Ripen, Cud Chew).
inline bool IsBerry(u16 item) { return item >= 149 && item <= 212; }
// a and b are on the same side (the same Pokémon counts).
inline bool SameSide(u32 a, u32 b) { return a == b || IsAllyMonID(a, b); }
// Every Pokémon on the field (not fainted): f(pokeID).
template <typename F> inline void ForEachOnField(ServerFlow* sf, F f) {
    for (u32 id = 0; id < MAX_POKE_ID; ++id)
        if (OnField(sf, id) && !BattleMon_IsFainted(GetBattleMon(sf, id))) f(id);
}

// The move pokeID will use this turn from the action order (0: not a fight action, or it has acted) - for events
// that carry no move (0x0F special priority: Quick Draw, Mycelium Might). QuickDraw.cpp.
u16 PendingMove(ServerFlow* sf, u32 pokeID);

// The final type of a move used by attacker (after -ate abilities, Weather Ball...).
inline u32 FinalMoveType(ServerFlow* sf, u16 move, u32 attacker) {
    u8 param[0x20] = {};
    ServerEvent_GetMoveParam(sf, move, GetBattleMon(sf, attacker), param);
    return param[MOVE_PARAM_TYPE];
}

// From an EVENT_CHECK_NO_EFFECT handler: the move does not affect the holder ("It doesn't affect X..." with the
// ability popup, as Soundproof does). False if another handler already decided (the variable rewrites once).
inline bool BlockMove(ServerFlow* sf, u32 pokeID) {
    if (!BattleEventVar_RewriteValue(VAR_NO_EFFECT, 1)) return false;
    PopupSetMessage(sf, pokeID, MSG_SET_DOESNT_AFFECT);
    return true;
}

} // namespace ability
