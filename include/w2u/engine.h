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
    EVENT_CHECK_FLOATING = 0x12,        /* VAR_MON_ID floats (Levitate) */
    EVENT_CHECK_NO_EFFECT_TYPE = 0x1B,  /* a move's type found no effect (Levitate's popup) */
    EVENT_DAMP_MOVE_CHECK = 0x1F,       /* may the move be used? VAR_FAIL_CAUSE (Damp) */
    EVENT_DAMP_FAIL_MESSAGE = 0x21,     /* the failed move's message */
    EVENT_CHECK_NO_EFFECT = 0x2D,       /* per target: may the move affect it? (Volt Absorb, Soundproof) */
    EVENT_ACCURACY_STAGE = 0x33,        /* a hit's accuracy / evasion stages: VAR_EVASION_STAGE (6 = neutral) */
    EVENT_MOVE_POWER = 0x38,            /* VAR_MOVE_POWER_RATIO *= x (Iron Fist, Technician) */
    EVENT_ATTACKER_POWER = 0x3B,        /* the attacker's attacking stat: VAR_RATIO *= x (Huge Power) */
    EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
    EVENT_DAMAGE_RATIO = 0x47,          /* the final damage of a hit: VAR_RATIO *= x (Filter, Multiscale) */
    EVENT_AFTER_DAMAGE_REACTION = 0x4B, /* a hit landed on the defender (Rough Skin, Weak Armor, Justified) */
    EVENT_SWITCH_IN = 0x55,
    EVENT_STAT_CHANGE_CHECK = 0x5B,     /* may VAR_MON_ID's stat change? */
    EVENT_STAT_CHANGE_GUARD = 0x5C,
    EVENT_ADD_CONDITION_CHECK = 0x65,   /* a status for the defender: VAR_FAIL_FLAG blocks it (Water Veil) */
    EVENT_ADD_CONDITION_FAILED = 0x67,  /* the blocked status' message */
    EVENT_ABILITY_NULLIFIED = 0x6A,
    EVENT_TURN_CHECK = 0x76,            /* the end of the turn */
    EVENT_AFTER_KO = 0x83,              /* the attacker's move KO'd targets: VAR_TARGET_COUNT, VAR_TARGET0.. */
    EVENT_AFTER_ABILITY_CHANGE = 0x8A,
};

/* Event variables (W2U's names) */
enum {
    VAR_STAT = 0x1F,                    /* EVENT_STAT_CHANGE_CHECK: the stat (STATSTAGE_*) */
    VAR_FAIL_CAUSE = 0x22,              /* EVENT_DAMP_MOVE_CHECK: why the move fails (0x13: Damp) */
    VAR_MON_ID = 0x02,
    VAR_ATTACKING_MON = 0x03,
    VAR_DEFENDING_MON = 0x04,
    VAR_TARGET_COUNT = 0x05,            /* EVENT_AFTER_KO: the move's targets, VAR_TARGET0 + i */
    VAR_TARGET0 = 0x06,
    VAR_MOVE_ID = 0x12,
    VAR_MOVE_TYPE = 0x16,
    VAR_MOVE_CATEGORY = 0x1A,
    VAR_EVASION_STAGE = 0x28,           /* 6 = neutral */
    VAR_MOVE_POWER_RATIO = 0x31,        /* fixed point, 4096 = x1 */
    VAR_TYPE_EFFECTIVENESS = 0x38,      /* EVENT_DAMAGE_RATIO: the hit's effectiveness (BtlCalc_ClassifyEffectiveness) */
    VAR_RATIO = 0x35,                   /* fixed point, 4096 = x1 */
    VAR_NO_EFFECT = 0x40,
    VAR_SUBSTITUTE_HIT = 0x46,          /* nonzero: the hit landed on a substitute */               /* EVENT_CHECK_NO_EFFECT: rewritten to 1, the move does not affect the target */
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
    HANDLER_CMD_CHANGE_STAT = 0x0E,     /* BattleHandlerStatChangeParam */
};

/* BattleHandler_StrSetup message kinds */
enum {
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
};

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
BattleMon *GetBattleMon(BtlServerFlow *serverFlow, u8 monId);
u32 GetBattleMonStat(const BattleMon *mon, u32 stat);
b32 IsFainted(const BattleMon *mon);
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

/* waza_tool.c */
s32 PML_MoveGetParam(u16 move, u32 param);
b32 getMoveFlag(u16 move, u32 flag);

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

W2U_C_END

/* Struct fields the injection build reads by offset (battle_api.h); a decomp build uses the field */
#if !defined(W2U_DECOMP)
#define W2U_SERVERFLOW_SIMULATION_DEPTH 0x774   /* BtlServerFlow.simulationDepth: nonzero while the AI simulates */
#endif

#endif /* W2U_ENGINE_H */
