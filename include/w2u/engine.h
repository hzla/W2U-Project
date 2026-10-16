/* W2U engine interface, layer A: the game's functions, types and IDs that W2U's mechanics use, under the pokebw2
 * decomp's names (its include/battle/btl_event.h and friends) as hzla's White 2 cleanup of it names them
 * (hzla/w2-expansion, def37f3: it keeps the decomp's public names and renames placeholders). C and C++. See
 * docs/engine-interface.md.
 *
 * Hand-written for the first mechanics converted to C; it becomes generated from the decomp crosswalk once the
 * decomp's names settle. Injection builds resolve these names through pmc/IRDO.yml; where the decomp spells a name
 * differently from IRDO.yml, the injection section maps it with a #define. Event IDs and event variables have no
 * names in the decomp yet: W2U owns those names, with the values the engine uses.
 *
 * Mechanic files include this (through w2u/battle_api.h) and never the C++ engine headers (w2u_abilities.h,
 * megab2w2/battle.h, megab2w2/battle_events.h), which declare the same engine under older names. */
#ifndef W2U_ENGINE_H
#define W2U_ENGINE_H

#if defined(__W2U_ABILITIES_H)
#error "w2u/engine.h and w2u_abilities.h declare the same engine twice: a mechanic file includes w2u/battle_api.h only"
#endif

#include "swantypes.h"

/* Injection builds: names the cleanup gives that IRDO.yml spells differently (the declarations below then declare
 * the IRDO.yml symbol) */
#if !defined(W2U_DECOMP)
#define BtlCalc_ClassifyEffectiveness TypeEffectivenessClass
#define IsFainted BattleMon_IsFainted
#define IsStatChangeValid BattleMon_IsStatChangeValid
#define HandlerDampEffective HandlerDampMessage
#define HandlerDampStart HandlerDampMoveStart
#define HandlerDampEnd HandlerDampNullified
#define BtlCalc_MakeMajorStatusCondition sub_21BD56C
#define BtlCalc_BuildMoveCondition BTL_MakeSickCont
#define PML_MoveGetConditionParam PML_MoveGetSickCont
#define Handler_CheckMatchup sub_21ABF54
#define Handler_PokeIDToPokePos Battle_GetMonPos
#define HandlerGetAlivePartyCount Battle_ExpandPos
#define GetBattleMonHeldItem BattleMon_GetHeldItem
#define PokeTypePair_MakeMonotype PokeTypePair_MakePure
#define GetTurnFlag BattleMon_GetTurnFlag
#define SetConditionTurns Condition_MakeTurn
#define MakeConditionPermanent Condition_MakePermanent
#endif

#ifdef __cplusplus
#define W2U_EXTERN_C extern "C"
#define W2U_C_BEGIN extern "C" {
#define W2U_C_END }
#else
#define W2U_EXTERN_C
#define W2U_C_BEGIN
#define W2U_C_END
#endif

/* Types (decomp: include/struct_decls.h, include/battle/btl_event.h) */
typedef struct BattleEventItem BattleEventItem;
typedef struct BattleMon BattleMon;
#if defined(W2U_DECOMP)
typedef struct BtlServerFlow BtlServerFlow;
#else
typedef struct ServerFlow BtlServerFlow;            /* IRDO.yml: ServerFlow */
#endif

/* A handler: the item, the server flow, the item's Pokémon (its ID, 0-23) and the item's work */
typedef void (*BattleEventHandlerFn)(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);

typedef struct BattleEventHandlerEntry {
    u32 event;
    BattleEventHandlerFn handler;
} BattleEventHandlerEntry;

/* Battle events (W2U's names; the decomp's are numbers so far) */
enum {
    EVENT_ACTION_END = 0x02,            /* a Pokémon's action is over (Water Veil cures its status here) */
    EVENT_MOVE_START = 0x03,            /* the attacker's move begins */
    EVENT_MOVE_END = 0x04,
    EVENT_YAWN_CHECK = 0x0E,
    EVENT_SPECIAL_PRIORITY = 0x0F,      /* VAR_MON_ID's place within its priority bracket: VAR_SPECIAL_PRIORITY */            /* may VAR_MON_ID get drowsy? VAR_FAIL_FLAG blocks it (Insomnia) */
    EVENT_CHECK_FLOATING = 0x12,
    EVENT_CALC_SPEED = 0x13,            /* VAR_MON_ID's Speed: VAR_RATIO *= x (Swift Swim, Quick Feet) */        /* VAR_MON_ID floats (Levitate) */
    EVENT_CHECK_NO_EFFECT_TYPE = 0x1B,  /* a move's type found no effect (Levitate's popup) */
    EVENT_DAMP_MOVE_CHECK = 0x1F,       /* may the move be used? VAR_FAIL_CAUSE (Damp) */
    EVENT_DAMP_FAIL_MESSAGE = 0x21,     /* the failed move's message */
    EVENT_AFTER_MOVE_USE = 0x22,        /* the attacker's move was used: the Choice items lock here */
    EVENT_CHECK_NO_EFFECT = 0x2D,
    EVENT_PROTECT_BREAK_CHECK = 0x2E,   /* per target of a protected move: VAR_BREAK_PROTECT (W2U raises it too) */       /* per target: may the move affect it? (Volt Absorb, Soundproof) */
    EVENT_ACCURACY_STAGE = 0x33,        /* a hit's accuracy / evasion stages: VAR_EVASION_STAGE (6 = neutral) */
    EVENT_MOVE_POWER = 0x38,            /* VAR_MOVE_POWER_RATIO *= x (Iron Fist, Technician) */
    EVENT_ATTACKING_STAT = 0x3B,        /* the attacker's attacking stat: VAR_RATIO *= x (Huge Power, Guts) */
    EVENT_DEFENDING_STAT = 0x3C,        /* the defender's defending stat: VAR_RATIO *= x; VAR_MOVE_CATEGORY 1: Defense */
    EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
    EVENT_DAMAGE_RATIO = 0x47,          /* the final damage of a hit: VAR_RATIO *= x (Filter, Multiscale) */
    EVENT_AFTER_DAMAGE_REACTION = 0x4B, /* a hit landed on the defender (Rough Skin, Weak Armor, Justified) */
    EVENT_SWITCH_OUT_END = 0x54,
    EVENT_SWITCH_IN = 0x55,
    EVENT_BEFORE_SWITCH_IN_BATCH = 0x56, /* ServerEvent_BeforeSwitchInBatch */
    EVENT_REFRESH_ACTIVATION = 0x58,    /* ServerEvent_RefreshActivation */
    EVENT_STAT_CHANGE_CHECK = 0x5B,     /* may VAR_MON_ID's stat change? */
    EVENT_STAT_CHANGE_GUARD = 0x5C,
    EVENT_STAT_CHANGE_APPLIED = 0x5D,   /* VAR_MON_ID's VAR_STAT changed by VAR_STAT_CHANGE, as applied (raises too) */
    EVENT_ADD_CONDITION_CHECK = 0x65,   /* a status for the defender: VAR_FAIL_FLAG blocks it (Water Veil) */
    EVENT_ADD_CONDITION_FAILED = 0x67,  /* the blocked status' message */
    EVENT_STATUS_INFLICTED = 0x68,      /* a status was inflicted: VAR_CONDITION, the attacker and the defender */
    EVENT_ABILITY_NULLIFIED = 0x6A,
    EVENT_USE_ITEM = 0x72,              /* VAR_MON_ID uses its held item */
    EVENT_TURN_CHECK = 0x76,            /* the end of the turn */
    EVENT_TURN_CHECK_END = 0x77,        /* after the end-of-turn checks */
    EVENT_AFTER_KO = 0x83,
    EVENT_AFTER_MOVE_HITS = 0x87,       /* a move's hits are done: the targets (HandlerTargetsContain) */              /* the attacker's move KO'd targets: VAR_TARGET_COUNT, VAR_TARGET0.. */
    EVENT_BEFORE_ABILITY_CHANGE = 0x89,
    EVENT_FORCE_OUT_CHECK = 0x8B,
    EVENT_NOTIFY_FAINTED = 0xA3,       /* may VAR_MON_ID be forced out (Roar, Whirlwind)? */
    EVENT_AFTER_ABILITY_CHANGE = 0x8A,
};

/* Event variables (W2U's names) */
enum {
    VAR_CONDITION = 0x1D,               /* the status (CONDITION_*) */
    VAR_STAT = 0x1F,                    /* EVENT_STAT_CHANGE_CHECK: the stat (STATSTAGE_*) */
    VAR_STAT_CHANGE = 0x20,             /* EVENT_STAT_CHANGE_CHECK: the stages (< 0: a drop) */
    VAR_FAIL_CAUSE = 0x22,              /* EVENT_DAMP_MOVE_CHECK: why the move fails (0x13: Damp) */
    VAR_MON_ID = 0x02,
    VAR_ATTACKING_MON = 0x03,
    VAR_DEFENDING_MON = 0x04,
    VAR_TARGET_COUNT = 0x05,            /* EVENT_AFTER_KO: the move's targets, VAR_TARGET0 + i */
    VAR_TARGET0 = 0x06,
    VAR_SPECIAL_PRIORITY = 0x11,        /* EVENT_SPECIAL_PRIORITY: 0 last, 1 normal, 2 first in the bracket */
    VAR_MOVE_ID = 0x12,
    VAR_MOVE_TYPE = 0x16,
    VAR_MOVE_CATEGORY = 0x1A,           /* EVENT_DEFENDING_STAT: 1 = the defending stat is Defense (Psyshock too) */
    VAR_EVASION_STAGE = 0x28,           /* 6 = neutral */
    VAR_MOVE_POWER_RATIO = 0x31,        /* fixed point, 4096 = x1 */
    VAR_TYPE_EFFECTIVENESS = 0x38,      /* EVENT_DAMAGE_RATIO: the hit's effectiveness (BtlCalc_ClassifyEffectiveness) */
    VAR_RATIO = 0x35,                   /* fixed point, 4096 = x1 */
    VAR_NO_EFFECT = 0x40,
    VAR_FAIL_FLAG = 0x41,
    VAR_BREAK_PROTECT = 0x51,           /* EVENT_PROTECT_BREAK_CHECK: 1 broken (Feint), 2 through (W2U) */               /* the status, Yawn and stat change checks: 1 = blocked */
    VAR_SUBSTITUTE_HIT = 0x46,          /* nonzero: the hit landed on a substitute */
    VAR_NO_SECONDARY = 0x47,            /* nonzero: no secondary effects for this hit (Shield Dust) */               /* EVENT_CHECK_NO_EFFECT: rewritten to 1, the move does not affect the target */
};

/* Weather (GetWeather: as abilities see it, so Air Lock reads as none) */
enum {
    WEATHER_NONE = 0,
    WEATHER_SUN = 1,
    WEATHER_RAIN = 2,
    WEATHER_HAIL = 3,
    WEATHER_SAND = 4,
};
#define WEATHER_TURNS_DEFAULT 0xFF          /* BattleHandlerChangeWeatherParam: 5 turns, or the item's 8 */

/* VAR_TYPE_EFFECTIVENESS values */
enum {
    TYPE_EFFECTIVENESS_X0 = 0,
    TYPE_EFFECTIVENESS_X1_4 = 1,
    TYPE_EFFECTIVENESS_X1_2 = 2,
    TYPE_EFFECTIVENESS_X1 = 3,
    TYPE_EFFECTIVENESS_X2 = 4,
    TYPE_EFFECTIVENESS_X4 = 5,
};

/* BtlCalc_ClassifyEffectiveness results */
enum {
    EFFECTIVENESS_IMMUNE = 0,
    EFFECTIVENESS_NEUTRAL = 1,
    EFFECTIVENESS_SUPER = 2,
    EFFECTIVENESS_RESISTED = 3,
};

/* Handler commands (BattleHandler_PushWork / PushRun; the decomp's are numbers) */
enum {
    HANDLER_CMD_POPUP_IN = 0x02,        /* PushRun: the ability popup appears */
    HANDLER_CMD_POPUP_OUT = 0x03,
    HANDLER_CMD_MESSAGE = 0x04,         /* BattleHandlerMessageParam */
    HANDLER_CMD_RECOVER_HP = 0x05,      /* BattleHandlerRecoverHPParam */
    HANDLER_CMD_CURE_CONDITION = 0x0B,  /* BattleHandlerCureConditionParam */
    HANDLER_CMD_ADD_CONDITION = 0x0C,   /* BattleHandlerAddConditionParam */
    HANDLER_CMD_CHANGE_STAT = 0x0E,     /* BattleHandlerStatChangeParam */
    HANDLER_CMD_CHANGE_TYPE = 0x14,
    HANDLER_CMD_ADD_SIDE_EFFECT = 0x19, /* BattleHandlerAddSideEffectParam */     /* BattleHandlerChangeTypeParam: "X transformed into the Y type!" */
    HANDLER_CMD_REMOVE_SIDE_EFFECT = 0x1A,
    HANDLER_CMD_CHANGE_WEATHER = 0x1D,  /* BattleHandlerChangeWeatherParam */
    HANDLER_CMD_CHANGE_ABILITY = 0x1F,
    HANDLER_CMD_FORCE_USE_ITEM = 0x22,  /* BattleHandlerForceUseItemParam: eat or use an item now (Bug Bite) */
    HANDLER_CMD_CONSUME_ITEM = 0x23,    /* BattleHandlerConsumeItemParam: the item animation and message, used up */  /* BattleHandlerAbilityChangeParam */ /* BattleHandlerRemoveSideEffectParam */
};

/* BattleHandler_StrSetup message kinds */
enum {
    HANDLER_STR_STD = 1,                /* one message (bank 19); its arguments as AddArg gives them */
    HANDLER_STR_SET = 2,                /* a set of three messages (player's, wild, foe's Pokémon), bank 18 */
};

/* The handler-effect work the commands take (decomp: include/battle/btl_handler.h) */
typedef struct BattleHandlerString {
    u16 message;
    u16 flags;
    u32 args[8];
    u32 soundEffect;
} BattleHandlerString;

typedef struct BattleHandlerMessageParam {
    u32 header : 23;
    u32 popup : 1;                      /* inside the ability popup */
    u32 unk24 : 8;
    BattleHandlerString string;
} BattleHandlerMessageParam;

typedef struct BattleHandlerStatChangeParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u32 stat;                           /* STATSTAGE_* */
    u32 value;
    s8 change;                          /* stages, +-1..6 */
    u8 flag;
    u8 unk0e;                           /* 1, as the vanilla abilities set it */
    u8 count;
    u8 monIds[8];
    BattleHandlerString string;
} BattleHandlerStatChangeParam;

/* Battle Pokémon IDs and positions */
#define BATTLE_MAX_MON_ID 24                /* monIds are 0-23 */
#define BATTLE_POS_NONE 6                   /* Handler_PokeIDToPokePos: not on the field */
/* HandlerGetAlivePartyCount's code: the range (high byte) and the position (low byte) */
#define BATTLE_RANGE_FULL_FRIENDS 7         /* the whole side of the position */

/* GetTurnFlag's flags (W2U's names) */
enum {
    TURN_FLAG_PROTECT = 7,              /* protected this turn (Protect, Detect...) */
};

/* Conditions: the majors, then the others (CheckCondition, the add and cure condition work) */
enum {
    CONDITION_PARALYSIS = 1,
    CONDITION_SLEEP = 2,
    CONDITION_FREEZE = 3,
    CONDITION_BURN = 4,
    CONDITION_POISON = 5,               /* bad poison: poison with Toxic's turn counter */
    CONDITION_CONFUSION = 6,
    CONDITION_YAWN = 14,                /* Yawn's drowsiness, checked like the majors */
    CONDITION_GASTRO_ACID = 0x10,       /* the ability is suppressed */
    CONDITION_PERISH_SONG = 20,
    CONDITION_CHOICE_LOCK = 0x1B,       /* locked into one move (the Choice items) */
};

/* A condition's value: its kind and turns (decomp: include/battle/btl_pokeparam.h, a union) */
typedef struct BattleCondition {
    u32 raw;
} BattleCondition;

/* How long the condition a move inflicts lasts (decomp: include/pml/waza.h) */
typedef struct MoveConditionParam {
    u16 type : 4;
    u16 min : 6;
    u16 max : 6;
} MoveConditionParam;

typedef struct BattleHandlerAddConditionParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u32 condition;                      /* CONDITION_* */
    BattleCondition value;
    u8 showFail;
    u8 noMessage;                       /* no message of its own when there is no string */
    u8 skipItemReaction;
    u8 targetIndex;                     /* the Pokémon it is for */
    u8 overwrite;
    BattleHandlerString string;
} BattleHandlerAddConditionParam;

typedef u16 PokeTypePair;

typedef struct BattleHandlerChangeTypeParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    PokeTypePair type;
    u8 monIndex;
    u8 suppressMessage;
} BattleHandlerChangeTypeParam;

typedef struct BattleHandlerAbilityChangeParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u16 ability;
    u8 targetIndex;
    u8 force;
    u8 unk08;
    u8 unk09[3];
    BattleHandlerString string;
} BattleHandlerAbilityChangeParam;

typedef struct BattleHandlerAddSideEffectParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u32 effect;                         /* SIDE_EFFECT_* */
    BattleCondition cont;
    u8 side;
    BattleHandlerString string;
} BattleHandlerAddSideEffectParam;

typedef struct BattleHandlerChangeWeatherParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u8 weather;                         /* WEATHER_* */
    u8 duration;
    u8 notifyAirLock;
    u8 unk07;
    BattleHandlerString string;
} BattleHandlerChangeWeatherParam;

typedef struct BattleHandlerConsumeItemParam {
    u32 header;
    u32 skipDisplay;                    /* 0: the item animation and the message */
    BattleHandlerString string;
} BattleHandlerConsumeItemParam;

typedef struct BattleHandlerForceUseItemParam {
    u32 header : 24;
    u32 checkPrevResult : 1;            /* skipped when the previous command failed */
    u32 unk25 : 7;
    u8 monIndex;
    u8 unk05;
    u16 item;
} BattleHandlerForceUseItemParam;

typedef struct BattleHandlerRemoveSideEffectParam {
    u32 header;
    u8 effects[3];                      /* a bit set: its size in bytes (3), then the SIDE_EFFECT_* bits 0-15 */
    u8 side;
} BattleHandlerRemoveSideEffectParam;

typedef struct BattleHandlerRecoverHPParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u16 amount;
    u8 targetIndex;
    u8 bypassHealBlock;
    BattleHandlerString string;
} BattleHandlerRecoverHPParam;

typedef struct BattleHandlerCureConditionParam {
    u32 header;
    u32 condition;
    u8 monIds[12];
    u8 count;
    u8 useString;
    u8 unk16[2];
} BattleHandlerCureConditionParam;

/* A move's parameters as the events changed them (ServerEvent_GetMoveParam) */
typedef struct BtlFlowMoveParam {
    u16 move;
    u16 originalMove;
    u16 userType;                       /* PokeTypePair */
    u8 type;                            /* the final type (after -ate abilities, Weather Ball...) */
    u8 unk07;
    u32 category;
    u32 targetType;
    u32 flags;
} BtlFlowMoveParam;

/* The layouts the vanilla code uses (C99 has no static_assert: a negative array size fails the build) */
#define W2U_ENGINE_LAYOUT(name, cond) typedef char w2u_engine_layout_##name[(cond) ? 1 : -1]
W2U_ENGINE_LAYOUT(string_size, sizeof(BattleHandlerString) == 0x28);
W2U_ENGINE_LAYOUT(message_string, __builtin_offsetof(BattleHandlerMessageParam, string) == 0x04);
W2U_ENGINE_LAYOUT(stat_change_change, __builtin_offsetof(BattleHandlerStatChangeParam, change) == 0x0C);
W2U_ENGINE_LAYOUT(stat_change_count, __builtin_offsetof(BattleHandlerStatChangeParam, count) == 0x0F);
W2U_ENGINE_LAYOUT(stat_change_mons, __builtin_offsetof(BattleHandlerStatChangeParam, monIds) == 0x10);
W2U_ENGINE_LAYOUT(condition_size, sizeof(BattleCondition) == 4);
W2U_ENGINE_LAYOUT(add_condition_target, __builtin_offsetof(BattleHandlerAddConditionParam, targetIndex) == 0x0F);
W2U_ENGINE_LAYOUT(add_condition_string, __builtin_offsetof(BattleHandlerAddConditionParam, string) == 0x14);
W2U_ENGINE_LAYOUT(recover_hp_string, __builtin_offsetof(BattleHandlerRecoverHPParam, string) == 0x08);
W2U_ENGINE_LAYOUT(cure_count, __builtin_offsetof(BattleHandlerCureConditionParam, count) == 0x14);
W2U_ENGINE_LAYOUT(add_condition_overwrite, __builtin_offsetof(BattleHandlerAddConditionParam, overwrite) == 0x10);
W2U_ENGINE_LAYOUT(ability_change_string, __builtin_offsetof(BattleHandlerAbilityChangeParam, string) == 0x0C);
W2U_ENGINE_LAYOUT(add_side_effect_string, __builtin_offsetof(BattleHandlerAddSideEffectParam, string) == 0x10);
W2U_ENGINE_LAYOUT(change_weather_string, __builtin_offsetof(BattleHandlerChangeWeatherParam, string) == 0x08);
W2U_ENGINE_LAYOUT(consume_item_string, __builtin_offsetof(BattleHandlerConsumeItemParam, string) == 0x08);
W2U_ENGINE_LAYOUT(force_use_item_item, __builtin_offsetof(BattleHandlerForceUseItemParam, item) == 0x06);
W2U_ENGINE_LAYOUT(move_param_type, __builtin_offsetof(BtlFlowMoveParam, type) == 0x06);
W2U_ENGINE_LAYOUT(stat_change_string, __builtin_offsetof(BattleHandlerStatChangeParam, string) == 0x18);

/* Stat stages (W2U's names: the decomp's are numbers) */
enum {
    STATSTAGE_ATTACK = 1,
    STATSTAGE_DEFENSE = 2,
    STATSTAGE_SPECIAL_ATTACK = 3,
    STATSTAGE_SPECIAL_DEFENSE = 4,
    STATSTAGE_SPEED = 5,
    STATSTAGE_ACCURACY = 6,
    STATSTAGE_EVASION = 7,
};
#define STATSTAGE_NEUTRAL 6                 /* the decomp's BATTLEMON_STAT_STAGE_NEUTRAL */

/* GetBattleMonStat values */
enum {
    BMV_HP = 0x0D,
    BMV_MAX_HP = 0x0E,
    BMV_ATTACK = 0x08,                  /* the raw stats: Attack .. Speed, 0x08 .. 0x0C */
    BMV_DEFENSE = 0x09,
    BMV_SPECIAL_ATTACK = 0x0A,
    BMV_SPECIAL_DEFENSE = 0x0B,
    BMV_SPEED = 0x0C,
    BMV_ABILITY = 0x10,
};

/* getMoveFlag flags (the move record's flag bits) */
enum {
    MOVE_FLAG_CONTACT = 0,
    MOVE_FLAG_SOUND = 8,
};                                      /* W2U's own flags (MOVE_FLAG_WIND ...): megab2w2/mb_ids.h */

/* Side effects (SideEffect_IsActive, BattleHandlerRemoveSideEffectParam) */
enum {
    SIDE_EFFECT_REFLECT = 0,
    SIDE_EFFECT_LIGHT_SCREEN = 1,
    SIDE_EFFECT_SAFEGUARD = 2,
    SIDE_EFFECT_MIST = 3,
    SIDE_EFFECT_TAILWIND = 4,
    SIDE_EFFECT_TOXIC_SPIKES = 7,
};
#define BATTLE_SIDES 2

/* PML_MoveGetParam parameters and the categories it returns */
enum {
    MOVE_PARAM_TYPE = 0x00,
    MOVE_PARAM_CATEGORY = 0x02,
    MOVE_PARAM_TARGET = 0x1B,
};

/* Move targets (MOVE_PARAM_TARGET) */
enum {
    MOVE_TARGET_OTHER_SELECT = 0,
    MOVE_TARGET_FRIEND_AND_USER = 1,
    MOVE_TARGET_FRIEND_SELECT = 2,
    MOVE_TARGET_ENEMY_SELECT = 3,
    MOVE_TARGET_OTHER_ALL = 4,
    MOVE_TARGET_ENEMY_ALL = 5,
    MOVE_TARGET_FRIEND_ALL = 6,
    MOVE_TARGET_USER = 7,
    MOVE_TARGET_ALL = 8,
    MOVE_TARGET_ENEMY_RANDOM = 9,
    MOVE_TARGET_FIELD = 10,
    MOVE_TARGET_FIELD_SIDE_ENEMY = 11,
    MOVE_TARGET_FIELD_SIDE_FRIEND = 12,
};
enum {
    MOVE_CATEGORY_STATUS = 0,
    MOVE_CATEGORY_PHYSICAL = 1,
    MOVE_CATEGORY_SPECIAL = 2,
};

/* Data IDs (abilities, types, moves, items, messages) are not the engine's: mechanics take them from the data
 * headers (megab2w2/mb_ids.h for now). */

W2U_C_BEGIN

/* battle_event.c */
u32 BattleEventVar_GetValue(u32 key);
void BattleEventVar_MulValue(u16 key, s32 value);
b32 BattleEventVar_RewriteValue(u16 key, s32 value);

/* btl_main.c, btl_server_flow.c, btl_pokeparam.c */
b32 IsAllyMonID(u8 monId1, u8 monId2);
u8 GetSideFromMonID(u8 monId);
u8 GetSideFromOpposingMonID(u8 monId);          /* the side facing the Pokémon */
/* W2U's name (the decomp has none yet): the side effect is up on the side */
b32 SideEffect_IsActive(u32 side, u32 effect);
BattleMon *GetBattleMon(BtlServerFlow *serverFlow, u8 monId);
u32 GetBattleMonStat(const BattleMon *mon, u32 stat);
b32 IsFainted(const BattleMon *mon);
b32 CheckCondition(const BattleMon *mon, u32 conditionId);
u32 GetBattleMonHeldItem(BattleMon *mon);
u32 GetTurnFlag(BattleMon *mon, u32 flag);
PokeTypePair GetPokeType(BattleMon *mon);
PokeTypePair PokeTypePair_MakeMonotype(u32 singleTypeId);
b32 IsMonFullHP(BattleMon *mon);
/* Max HP / divisor, at least 1 */
u32 DivideMaxHPZeroCheck(BattleMon *mon, u32 divisor);
/* The Pokémon a position code covers ((range << 8) | position), into monIds: their count */
u8 HandlerGetAlivePartyCount(BtlServerFlow *handler, u16 code, u8 *monIds);
/* The Pokémon's battle position, BATTLE_POS_NONE if it is not on the field */
u8 Handler_PokeIDToPokePos(BtlServerFlow *flow, u8 monId);
/* The move's priority after the events (Prankster, Gale Wings, Triage), + 7 */
u8 ServerEvent_GetMovePriority(BtlServerFlow *flow, u16 move, BattleMon *mon);
u32 GetBattleMonStatus(BattleMon *mon);         /* 0: none, else CONDITION_* */
/* The stat can still change by stageDelta (not at +6 / -6 already) */
b32 IsStatChangeValid(BattleMon *mon, u32 statId, s32 stageDelta);
void ServerEvent_GetMoveParam(BtlServerFlow *flow, u16 move, BattleMon *moveUser, BtlFlowMoveParam *moveParamsOut);

/* btl_handler_work.c: the handler-effect queue */
void *BattleHandler_PushWork(BtlServerFlow *flow, u32 command, u32 monId);
void BattleHandler_PushRun(BtlServerFlow *flow, u32 command, u32 monId);
void BattleHandler_PopWork(BtlServerFlow *flow, void *work);
void BattleHandler_StrSetup(BattleHandlerString *string, u32 enabled, u16 message);
void BattleHandler_AddArg(BattleHandlerString *string, u32 arg);

/* btl_calc.c */
u32 BtlCalc_ClassifyEffectiveness(s32 effectivenessId);
/* The value a major status gets by default (burn, poison: no turns) */
BattleCondition BtlCalc_MakeMajorStatusCondition(u32 status);
/* The value of the condition a move inflicts, for the Pokémon using it */
void BtlCalc_BuildMoveCondition(MoveConditionParam param, BattleMon *mon, BattleCondition *out);

/* A condition value that lasts until removed (the Choice lock's move) */
BattleCondition MakeConditionParamPermanent(u16 param);
BattleCondition MakeConditionPermanent(void);
BattleCondition SetConditionTurns(u8 turns);

/* btl_handler.c: the current event's targets contain the Pokémon (EVENT_AFTER_MOVE_HITS) */
b32 HandlerTargetsContain(u32 monId);

/* btl_server_flow.c */
/* The weather as abilities see it (Air Lock and Cloud Nine read as none) */
u8 GetWeather(BtlServerFlow *serverFlow);
/* Set while the engine checks a matchup: Mummy and Flame Body skip their reactions then */
b32 Handler_CheckMatchup(BtlServerFlow *flow);
b32 AbilityEvent_RollEffectChance(BtlServerFlow *flow, u32 chancePercent);

/* waza_tool.c */
s32 PML_MoveGetParam(u16 move, u32 param);
b32 getMoveFlag(u16 move, u32 flag);
MoveConditionParam PML_MoveGetConditionParam(u16 move);

/* ability_handlers.c: the vanilla abilities' helpers and handlers, which W2U's abilities reuse */
/* A `type` move at the holder has no effect (Volt Absorb, Sap Sipper): true if so */
b32 CommonDamageRecoverCheck(BtlServerFlow *flow, u32 monId, u32 type);
/* Heals 1/divisor of the holder's max HP, or "unaffected" when full (Volt Absorb) */
void CommonTypeRecoverHP(BtlServerFlow *flow, u8 monId, u32 divisor);
/* Raises a stat instead (Sap Sipper, Motor Drive) */
void CommonTypeNoEffectRankUp(BtlServerFlow *flow, u8 monId, u32 stat, u32 amount);
void HandlerScrappy(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerKeenEyeCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerKeenEyeGuard(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerWaterVeil(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerWaterVeilCureStatus(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerWaterVeilActionEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerAddStatusFailedCommon(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerLevitate(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerLevitateAddImmunity(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerLevitateTurnCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
/* Damp's: the failed move's popup and message, and its bookkeeping around moves and when nullified */
void HandlerDampEffective(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerDampStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerDampMoveEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerDampEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
/* Unnerve's: its entry message (once: work[0]) and the same when activations are refreshed */
/* Blocks a status (VAR_FAIL_FLAG) for the holder: true if it did (Water Veil's check) */
b32 HandlerCommonGuardStatus(void *flow, u32 monId, u32 status);
/* Cures the holder's status: on entering or gaining the ability / at the action's end */
void CommonAbilityCureStatus(BtlServerFlow *flow, u8 monId, u32 status);
void CommonAbilityCureStatusCore(BtlServerFlow *flow, u8 monId, u32 status);
void HandlerInsomniaYawnCheck(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
/* Intimidate's entry handler; Suction Cups' force-out guard; Mold Breaker's move start / end (the skip check) */
void HandlerIntimidateMemberIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerSuctionCups(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerMoldBreakerStart(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerMoldBreakerEnd(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerUnnerveMemberIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);
void HandlerUnnerveRotationIn(BattleEventItem *item, BtlServerFlow *flow, u8 monId, s32 *work);

W2U_C_END

/* Struct fields the injection build reads by offset (battle_api.h); a decomp build uses the field */
#if !defined(W2U_DECOMP)
#define W2U_SERVERFLOW_SIMULATION_DEPTH 0x774   /* BtlServerFlow.simulationDepth: nonzero while the AI simulates */
#endif

#endif /* W2U_ENGINE_H */
