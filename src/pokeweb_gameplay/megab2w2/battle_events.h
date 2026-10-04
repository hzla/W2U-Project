// Ported from MegaB2W2 (src/include/battle_events.h); see docs/megab2w2-integration.md.
// Battle event system (ov167). IDs verified against vanilla handler tables (EventAddDrizzle: {0x55,0x8A}) and
// ServerEvent_CheckDamageEffectiveness (@0x21AAB90: event 0x3E, vars 0x15/0x16/0x4B/0x4C).
#pragma once
#include "swantypes.h"

struct ServerFlow; struct BattleMon; struct BattleEventItem;

typedef void (*BattleEventHandler)(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);
struct BattleEventHandlerTableEntry { u32 event; BattleEventHandler handler; };
// EventAdd functions: *packed = (priority << 16) | handlerCount (priority 0 -> default 5)
typedef const BattleEventHandlerTableEntry* (*AbilityEventAddFunc)(u32* packed);
struct AbilityEventAddEntry { u32 ability; AbilityEventAddFunc add; };

enum : u32 {
    EVENT_ACTION_END = 0x02,            // a Pokémon's action is over (Water Veil / Immunity cure their status here)
    EVENT_MOVE_START = 0x03,            // attacker's move begins (Mold Breaker attaches its skip check here)
    EVENT_CHECK_FLOATING = 0x12,        // ServerEvent_CheckFloating: VAR_MON_ID floats if var 0x51 is set (Levitate);
                                        // var 0x41 = grounded anyway (Gravity, Iron Ball)
    EVENT_TURN_CHECK = 0x76,
    EVENT_CHECK_NO_EFFECT_TYPE = 0x1B,  // a move's type found no effect (Levitate shows its popup + message here)            // end of turn (Levitate resets its message flag here)
    EVENT_YAWN_CHECK = 0x0E,            // may VAR_MON_ID get drowsy (Yawn)? VAR_FAIL_FLAG = 1 blocks (Insomnia, Leaf Guard)
    EVENT_MOVE_PRIORITY = 0x11,         // VAR_PRIORITY (= priority + 7) for the attacker's move (Prankster)
    EVENT_CALC_SPEED = 0x13,            // VAR_MON_ID's Speed: VAR_RATIO *= x (Swift Swim, Sand Rush, Quick Feet)
    EVENT_MOVE_END = 0x04,
    EVENT_MOVE_TYPE = 0x28,             // the move's type is settled: rewrite VAR_MOVE_TYPE (once) (Normalize, -ate)
    EVENT_AFTER_MOVE_USE = 0x22,        // the attacker's move was used (VAR_ATTACKING_MON, VAR_MOVE_ID): Choice items lock here
    EVENT_PROTECT_BREAK_CHECK = 0x2E,   // VAR_ATTACKING_MON's move (no VAR_MOVE_ID: raised by ov167 0x21AA1C0): rewrite
                                        // VAR_BREAK_PROTECT to 1 = Protect / Detect don't stop it (Feint @ 0x21C9A98)
    EVENT_CHECK_NO_EFFECT = 0x2D,       // per target: may the move affect it? (Soundproof, Volt Absorb, Telepathy)
    EVENT_ACCURACY_STAGE = 0x33,        // accuracy / evasion stages for a hit: VAR_ACCURACY_STAGE / VAR_EVASION_STAGE (6 =
                                        // neutral; Unaware sets them to 6)
    EVENT_CRIT_CHECK = 0x36,            // the crit roll for a hit: VAR_FAIL_FLAG = no crit (Battle Armor), stage (Super Luck)
    EVENT_MOVE_POWER = 0x38,            // Iron Fist / Technician: VAR_MOVE_POWER_RATIO *= x
    EVENT_ATTACKING_STAT = 0x3B,        // the attacker's Atk / Sp. Atk for this hit: VAR_RATIO *= x (Huge Power, Guts;
                                        // Thick Fat from the defender's side: attacker var 3, defender var 4, type 0x16)
    EVENT_DEFENDING_STAT = 0x3C,        // the defender's Def / Sp. Def: VAR_RATIO *= x (Marvel Scale; VAR_DAMAGE_CATEGORY)
    EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
    EVENT_DAMAGE_RATIO = 0x47,          // final damage of a hit: VAR_RATIO *= x (Filter, Multiscale, Tinted Lens, Sniper)
    EVENT_AFTER_DAMAGE_REACTION = 0x4B, // a hit landed on the defender (Rough Skin, Static, Weak Armor, Justified)
    EVENT_STAT_CHANGE_CHECK = 0x5B,     // may VAR_ATTACKING_MON change VAR_MON_ID's VAR_STAT by VAR_STAT_CHANGE? VAR_FAIL_FLAG
                                        // = 1 blocks (Clear Body, Keen Eye); 0x5C = the blocked message
    EVENT_STAT_CHANGE_GUARD = 0x5C,
    EVENT_STAT_LOWERED = 0x5D,          // VAR_MON_ID's stat was lowered by VAR_ATTACKING_MON (Defiant); VAR_STAT_CHANGE < 0
    EVENT_SWITCH_OUT_END = 0x54,
    EVENT_SWITCH_IN = 0x55,
    EVENT_ADD_CONDITION_CHECK = 0x65,   // a status for the defender (VAR_CONDITION): VAR_FAIL_FLAG = 1 blocks (Water Veil)
    EVENT_ADD_CONDITION_FAILED = 0x67,  // the blocked status' message (HandlerAddStatusFailedCommon)
    EVENT_ABILITY_NULLIFIED = 0x6A,
    EVENT_WEATHER_NEGATION = 0x7A,      // Air Lock / Cloud Nine set VAR_WEATHER_NEGATED
    EVENT_BEFORE_ABILITY_CHANGE = 0x89,
    EVENT_AFTER_ABILITY_CHANGE = 0x8A,
    EVENT_AFTER_KO = 0x83,              // the attacker's move KO'd targets: VAR_TARGET_COUNT, VAR_TARGET0.. (Moxie)
    EVENT_AFTER_MOVE_HITS = 0x87,       // a move's hits are done: VAR_ATTACKING_MON, the targets (Pickpocket)
    EVENT_FORCE_OUT_CHECK = 0x8B,       // may VAR_MON_ID be forced out (Roar, Whirlwind)? (Suction Cups)
    EVENT_NOTIFY_FAINTED = 0xA3,
};
enum : u32 {
    VAR_MON_ID = 0x02, VAR_ATTACKING_MON = 0x03, VAR_DEFENDING_MON = 0x04,
    VAR_TARGET_COUNT = 0x05, VAR_TARGET0 = 0x06,   // EVENT_AFTER_KO / _AFTER_MOVE_HITS: the move's targets
    VAR_MOVE_ID = 0x12,
    VAR_STAT = 0x1F,                    // EVENT_STAT_CHANGE_CHECK: the stat (1 Atk .. 7 evasion)
    VAR_ACCURACY_STAGE = 0x27, VAR_EVASION_STAGE = 0x28,
    VAR_PRIORITY = 0x18,                // EVENT_MOVE_PRIORITY: priority + 7
    VAR_CONDITION = 0x1D,               // EVENT_ADD_CONDITION_CHECK: 1 paralysis 2 sleep 3 freeze 4 burn 5 poison ...
    VAR_POKE_TYPE = 0x15, VAR_MOVE_TYPE = 0x16,
    VAR_MOVE_POWER_RATIO = 0x31,        // fx 4096 = 1.0
    VAR_RATIO = 0x35,                   // fx 4096: stat / damage multiplier (EVENT_ATTACKING_STAT, _DEFENDING_STAT, _DAMAGE_RATIO)
    VAR_TYPE_EFFECTIVENESS = 0x38,      // EVENT_DAMAGE_RATIO: the hit's effectiveness (Filter)
    VAR_DAMAGE_CATEGORY = 0x1A,         // 1 = physical (the defending stat is Defense; Marvel Scale, Weak Armor)
    VAR_STAT_CHANGE = 0x20,             // EVENT_STAT_LOWERED: stages (< 0)
    VAR_SUBSTITUTE_HIT = 0x46,          // nonzero: the hit landed on a substitute (Rough Skin / Weak Armor skip it)
    VAR_NO_SECONDARY = 0x47,            // nonzero: no secondary effects for this hit (Shield Dust; Poison Touch checks it)
    VAR_NO_EFFECT = 0x40,               // EVENT_CHECK_NO_EFFECT: rewrite to 1 = the move does not affect the target
    VAR_WEATHER_NEGATED = 0x41,
    VAR_BREAK_PROTECT = 0x51,           // EVENT_PROTECT_BREAK_CHECK
    VAR_FAIL_FLAG = 0x41,               // the same variable in the status / Yawn checks: 1 = blocked
    VAR_NO_IMMUNITY = 0x4B, VAR_FORCE_NEUTRAL = 0x4C,
};
enum : u32 { BATTLE_EVENT_ITEM_ABILITY = 4 };
enum : u32 { EFF_IMMUNE = 0, EFF_QUARTER = 1, EFF_HALF = 2, EFF_NEUTRAL = 3, EFF_DOUBLE = 4, EFF_QUAD = 5 };
enum : u32 { TYPE_FLYING = 2, TYPE_GROUND = 4, TYPE_GHOST = 7, TYPE_STEEL = 8, TYPE_FIRE = 9, TYPE_WATER = 10 };
enum : u32 { WEATHER_SUN = 1, WEATHER_RAIN = 2, WEATHER_HAIL = 3, WEATHER_SAND = 4 };
enum : u32 { COND_PARALYSIS = 1, COND_SLEEP = 2, COND_FREEZE = 3, COND_BURN = 4, COND_POISON = 5 };
enum : u32 { MOVE_FLAG_SOUND = 8 };   // getMoveFlag (scripts/data/movereg.py FLAGS order)
enum : u32 { MOVE_FLAG_CONTACT = 0, MOVE_FLAG_PUNCH = 7 };   // getMoveFlag (Rough Skin: 0, Iron Fist: 7)
constexpr u32 HANDLER_ABILITY_POPUP_FLAG = 1u << 23;   // HandlerParam_Header.flags

extern "C" {
BattleEventItem* BattleEvent_AddItem(u32 type, u16 subID, u32 mainPriority, u32 subPriority, u32 pokeID,
                                     const BattleEventHandlerTableEntry* table, u16 count);
void BattleEvent_CallHandlers(ServerFlow* sf, u32 event);
void BattleEventVar_Push();
void BattleEventVar_Pop();
void BattleEventVar_SetConstValue(u32 var, int value);
BattleEventItem* BattleEvent_SeekItem(u32 type, u32 pokeID);   // first live item of that type for the Pokémon
int  BattleEventVar_GetValue(u32 var);
u32  BattleEventVar_RewriteValue(u32 var, int value);
void BattleEventVar_SetRewriteOnceValue(u32 var, int value);
void BattleEventVar_MulValue(u32 var, int ratio);             // fx 4096
b32  getMoveFlag(u16 move, u32 flag);
u32  GetTypeEffectiveness(u32 moveType, u32 defType);
u16  calcAbilHandlerSubPriority(BattleMon* bm);
u32  devideNumHandersAndPri(u32* packed);
extern const AbilityEventAddEntry ABILITY_EVENT_TABLE[];   // ov167 0x21D7F38, 158 entries (src/esdb_extra.yml)
}
constexpr u32 ABILITY_EVENT_TABLE_COUNT = 0x9E;

// Per-item work words passed as the handlers' `work` (BattleEvent dispatcher sub_21BC98C: item + 0x1C).
inline u32* BattleEventItem_Work(BattleEventItem* item) { return (u32*)((u8*)item + 0x1C); }

// EventAdd function for an ability: our extra abilities first, then the vanilla table (AbilityEvents.cpp).
AbilityEventAddFunc FindAbilityEventAdd(u16 ability);
