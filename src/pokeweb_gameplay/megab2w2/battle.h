// Ported from MegaB2W2 (src/include/battle.h); see docs/megab2w2-integration.md.
// White 2 battle engine (overlay 167) declarations used by MegaB2W2.
// Offsets/semantics verified in Ghidra; see research/re/*.c and docs/MODLOG.md "Battle engine".
// Struct layouts are only declared as far as we touch them.
#pragma once
#include "swantypes.h"

struct ServerFlow; struct BattleMon; struct MainModule; struct BtlClientWk; struct BtlvCore; struct PartyPkm;

// ---- action word (BattleActionParam): cmd:4 | target:3 | move:16 | spare:9 ------------------------------
enum : u32 { BTL_ACTION_NULL = 0, BTL_ACTION_FIGHT = 1, BTL_ACTION_ITEM = 2, BTL_ACTION_SWITCH = 3, BTL_ACTION_RUN = 4 };
// (Mega requests are not kept in the action word: see mega::BattleState::requested)

// ---- ServerFlow: action order (ServerFlow_ActOrderProcMain @ 0x219FA10) -----------------------------------
struct ActionOrderWork {       // 0x10 bytes
    BattleMon* battleMon;
    u32 action;                // action word
    u32 speed;                 // priority/speed key (recomputed by SortActionOrderBySpeed)
    u8 partyID, done, _e, _f;
};
constexpr u32 SF_NUM_ACT_ORDER = 0x782;            // u8
constexpr u32 SF_ACT_ORDER = 0x7E0;                // ActionOrderWork[]
inline u8 SF_NumActOrder(ServerFlow* sf) { return *((u8*)sf + SF_NUM_ACT_ORDER); }
inline ActionOrderWork* SF_ActOrder(ServerFlow* sf) { return (ActionOrderWork*)((u8*)sf + SF_ACT_ORDER); }
inline MainModule* SF_MainModule(ServerFlow* sf) { return *(MainModule**)((u8*)sf + 0x4); }

// ---- BattleMon value IDs (GetBattleMonStat / BattleMon_GetValue) ------------------------------------------
enum : u32 { BMV_ABILITY = 0x10, BMV_FORM = 0x13 };

// ---- handler effects (BattleHandler_PushWork) --------------------------------------------------------------
enum : u32 { EFFECT_MESSAGE = 0x04, EFFECT_RECOVER_HP = 0x05, EFFECT_ADD_CONDITION = 0x0C, EFFECT_CHANGE_STAT_STAGE = 0x0E,
             EFFECT_CURE_CONDITION = 0x0B, EFFECT_CHANGE_TYPE = 0x14, EFFECT_REMOVE_SIDE_EFFECT = 0x1A, EFFECT_CHANGE_ABILITY = 0x1F, EFFECT_CONSUME_ITEM = 0x23,
             EFFECT_SWAP_ITEM = 0x24,
             EFFECT_CHANGE_FORM = 0x39 };
struct HandlerParam_StrParams { u16 id; u16 flags; u32 subProcID; u32 args[8]; };
struct HandlerParam_Header { u32 flags; };
struct HandlerParam_Message { HandlerParam_Header header; HandlerParam_StrParams str; };
// EFFECT_CHANGE_STAT_STAGE (layout from Defiant @ ov167 0x21C18BC / Weak Armor @ 0x21C16D4)
struct HandlerParam_ChangeStatStage {
    HandlerParam_Header header; u32 stat; u32 _8; s8 stages; u8 _d; u8 _e; u8 pokeCount; u8 pokeIDs[6];
};
// EFFECT_ADD_CONDITION (Poison Touch @ ov167 0x21C1D3C): condition, continuation, target; message at +0x14 (optional)
// +0x10: 2 in the Choice items' lock (ov167 0x21C423C), 0 elsewhere
struct HandlerParam_AddCondition {
    HandlerParam_Header header; u32 condition; u32 cont; u8 _c[3]; u8 pokeID; u8 mode; u8 _11[3];
    HandlerParam_StrParams exStr;
};
// EFFECT_CURE_CONDITION (Choice items when the item changes @ 0x21C4284): condition 0x1B = the Choice lock
struct HandlerParam_CureCondition { HandlerParam_Header header; u32 condition; u8 pokeID; u8 _9[11]; u8 _14; u8 _15; };
// EFFECT_CHANGE_TYPE (Conversion @ 0x21C5D46): the engine shows "X transformed into the Y type!"
struct HandlerParam_ChangeType { HandlerParam_Header header; u16 typePair; u8 pokeID; u8 _7; };
// EFFECT_RECOVER_HP (CommonTypeRecoverHP @ ov167 0x21C0144): heal pokeID by amount; message (0x183 "X's HP was
// restored.") at +8
struct HandlerParam_RecoverHP { HandlerParam_Header header; u16 amount; u8 pokeID; u8 _7; HandlerParam_StrParams exStr; };
// EFFECT_REMOVE_SIDE_EFFECT (Brick Break @ 0x21C60C0, Defog @ 0x21C5FE8): a bit set {size byte = 3, bits 0-7, bits 8-15}
// of side effects (SIDE_EFFECT_*) to remove from `side`; their end messages come from the engine
struct HandlerParam_RemoveSideEffect { HandlerParam_Header header; u8 flags[3]; u8 side; };
enum : u32 { SIDE_EFFECT_REFLECT = 0, SIDE_EFFECT_LIGHT_SCREEN = 1, SIDE_EFFECT_SAFEGUARD = 2, SIDE_EFFECT_MIST = 3,
             SIDE_EFFECT_SPIKES = 6, SIDE_EFFECT_TOXIC_SPIKES = 7, SIDE_EFFECT_STEALTH_ROCK = 8 };
// EFFECT_CONSUME_ITEM (the Gems @ ov167 0x21C5A3C; BattleHandler_ConsumeItem 0x21ADA4C): the effect's pokeID uses up
// its held item (item animation + message unless noAnim; the item counts as used: Recycle, Unburden)
struct HandlerParam_ConsumeItem { HandlerParam_Header header; u32 noAnim; HandlerParam_StrParams exStr; };
// EFFECT_SWAP_ITEM (Pickpocket @ 0x21C1554): the receiver is the effect's pokeID, the other side here
struct HandlerParam_SwapItem { HandlerParam_Header header; u8 pokeID; u8 _5[3]; HandlerParam_StrParams exStr; };
struct HandlerParam_ChangeForm {
    HandlerParam_Header header; u8 pokeID; u8 newForm; u8 dontResetOnSwitch; u8 _pad; HandlerParam_StrParams exStr;
};
struct HandlerParam_ChangeAbility {   // BattleHandler_AbilityChange @ 0x21AD5E0
    HandlerParam_Header header; u16 ability; u8 pokeID; u8 force; u32 _8; HandlerParam_StrParams exStr;
};

extern "C" {
// actions
u32  BattleAction_GetAction(u32* action);
u32  ActionOrder_Proc(ServerFlow* sf, ActionOrderWork* entry);
void SortActionOrderBySpeed(ServerFlow* sf, ActionOrderWork* entries, u32 count);
u32  ServerFlow_SetupBeforeFirstTurn(ServerFlow* sf);

// handlers
HandlerParam_Header* BattleHandler_PushWork(ServerFlow* sf, u32 effect, u32 pokeID);
void BattleHandler_PopWork(ServerFlow* sf, void* work);
void BattleHandler_StrSetup(HandlerParam_StrParams* str, u16 type, u16 msgID);
void BattleHandler_AddArg(HandlerParam_StrParams* str, u32 arg);

// BattleMon
u32  BattleMon_GetID(BattleMon* bm);
u16  BattleMon_GetSpecies(BattleMon* bm);
u16  BattleMon_GetHeldItem(BattleMon* bm);
u32  BattleMon_GetValue(BattleMon* bm, u32 value);
b32  BattleMon_IsFainted(BattleMon* bm);
u32  BattleMon_TransformCheck(BattleMon* bm);
u32  Move_SearchIndex(BattleMon* bm, u32 move);       // 4 = not found

// main module / setup / bag
void* MainModule_GetBtlSetup(MainModule* mm);
u16  BagSave_GetItemCountByID(void* bag, u16 item, u16 heapId);

// personal data
u32  PML_PersonalGetParamSingle(u16 species, u16 form, u32 field);
}

enum : u32 { PERSONAL_ABILITY1 = 0x1A };
constexpr u32 BTLSETUP_BAG = 0x78;          // BtlSetup_LoadGameData: bag save pointer
constexpr u32 HEAPID_BATTLE_SYSTEM = 0x2;   // any heap works for the bag lookup (not used for allocation)

// client c owns poke IDs [base..base+5], base = {0, 12, 6, 18}[c] (table @0x21D6C64) -> use the game's lookup
extern "C" u32 MonIDToClientID(u32 pokeID);
extern "C" u8 GetPlayerClientID(MainModule* mm);
inline u32 PokeIDToClientID(u32 pokeID) { return MonIDToClientID(pokeID); }
