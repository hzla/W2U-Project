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
 * Mechanic files and the resident MegaB2W2 core (megab2w2/mb_resident.cpp) include this (through w2u/battle_api.h)
 * and never W2U's C++ engine headers (w2u_abilities.h, w2u_battle.h), which declare the same engine under older
 * names. */
#ifndef W2U_ENGINE_H
#define W2U_ENGINE_H

#if defined(__W2U_ABILITIES_H)
#error "w2u/engine.h and w2u_abilities.h declare the same engine twice: a mechanic file includes w2u/battle_api.h only"
#endif

#if defined(W2U_DECOMP)
#include "w2u/engine_decomp.h"              /* the decomp's headers, and its names for W2U's (decomp builds) */
#else
#include "swantypes.h"
#endif

/* How many times a move hits and how its hits are checked (the decomp's BtlFlowHitWork, BtlServerFlow.unk4B4;
 * W2U's HitCheckParam): ServerEvent_CheckMultihitHits fills it */
typedef struct W2U_HitWork {
    u8 countMax;
    u8 count;
    u8 checkEveryTime;                  /* each hit rolls its accuracy (Triple Kick) */
    u8 multiHitMove;
    u8 putAnimCmd;
    u8 multiHitEffectiveness;
} W2U_HitWork;

#if defined(W2U_DECOMP)
W2U_DECOMP_CHECK(hit_work, sizeof(BtlFlowHitWork) == sizeof(W2U_HitWork));
W2U_DECOMP_CHECK(original_targets, (u32)&((BtlServerFlow *)0)->unk850 == 0x850);
#endif

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
#define IsSubstituteActive BattleMon_IsSubstituteActive
#define TransformCheck BattleMon_TransformCheck
#define GetMonID BattleMon_GetID
#define GetFieldWeather BattleField_GetWeather
#define IsGuaranteedHit ServerControl_IsGuaranteedHit
#define IsMoldBreakerIgnoredAbility IsMoldBreakerAffectedAbility
#define IsFieldEffectActive BattleField_CheckEffect
#define IsAssistExcludedMove BattleMove_AssistIsForbidden
#define IsSleepTalkExcludedMove BattleMove_SleepTalkIsForbidden
#define IsMeFirstExcludedMove BattleMove_MeFirstIsForbidden
#define IsCopycatExcludedMove BattleMove_CopycatIsForbidden
#define RawBattleMonStat BattleMon_GetRealStat
#define CritAtkDefLevel BattleMon_GetCriticalStat
#define BtlEventVar_TryRead BattleEventVar_GetValueIfExist
#define Condition_CheckTypeImmunity Condition_CheckUnaffectedByType   /* ov167's veneer to overlay 169's */
#define IsSideEffectSet SideEffect_IsActive     /* IRDO.yml names ov167's branch stub to it (the decomp's is in ov169) */
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

#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
/* Types (decomp: include/struct_decls.h, include/battle/btl_event.h) */
typedef struct BattleEventItem BattleEventItem;
typedef struct BattleMon BattleMon;
typedef struct PartyPkm PartyPkm;
typedef struct BtlPokeCon BtlPokeCon;
typedef struct BtlMainModule BtlMainModule;
typedef struct BtlServerCmdQueue BtlServerCmdQueue;
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

#endif /* !W2U_DECOMP */
/* Battle events (W2U's names; the decomp's are numbers so far) */
enum {
    EVENT_ACTION_END = 0x02,            /* a Pokémon's action is over (Water Veil cures its status here) */
    EVENT_MOVE_START = 0x03,            /* the attacker's move begins */
    EVENT_MOVE_END = 0x04,
    EVENT_PREVENT_RUN = 0x0C,           /* may VAR_MON_ID flee? VAR_FAIL_FLAG blocks it (Shadow Tag; fleeing only) */
    EVENT_YAWN_CHECK = 0x0E,            /* may VAR_MON_ID get drowsy? VAR_FAIL_FLAG blocks it (Insomnia) */
    EVENT_SPECIAL_PRIORITY = 0x0F,      /* VAR_MON_ID's place within its priority bracket: VAR_SPECIAL_PRIORITY */
    EVENT_CHECK_FLOATING = 0x12,        /* VAR_MON_ID floats (Levitate) */
    EVENT_CALC_SPEED = 0x13,            /* VAR_MON_ID's Speed: VAR_RATIO *= x (Swift Swim, Quick Feet) */
    EVENT_CHECK_NO_EFFECT_TYPE = 0x1B,  /* a move's type found no effect (Levitate's popup) */
    EVENT_MOVE_EXECUTE_CHECK1 = 0x1E,   /* may VAR_MON_ID act? VAR_FAIL_CAUSE, VAR_FAIL_FLAG (W2U's name) */
    EVENT_DAMP_MOVE_CHECK = 0x1F,       /* may the move be used? VAR_FAIL_CAUSE (Damp) */
    EVENT_DAMP_FAIL_MESSAGE = 0x21,     /* the failed move's message */
    EVENT_AFTER_MOVE_USE = 0x22,        /* the attacker's move was used: the Choice items lock here */
    EVENT_CHECK_NO_EFFECT = 0x2D,       /* per target: may the move affect it? (Volt Absorb, Soundproof) */
    EVENT_PROTECT_BREAK_CHECK = 0x2E,
    EVENT_CHECK_DAMAGE_TO_RECOVER = 0x30, /* the move heals the defender instead (Volt Absorb): VAR_GENERAL_USE_FLAG */   /* per target of a protected move: VAR_BREAK_PROTECT (W2U raises it too) */
    /* W2U's own events reuse engine IDs as "new events": VAR_MON_ID / VAR_ATTACKING_MON / VAR_DEFENDING_MON are -1
     * (so the engine's handlers of that ID ignore them) and NEW_VAR_* carry the Pokémon (resident/protect.c) */
    EVENT_PROTECT_SUCCESS = 0x15,       /* new event: a protection stopped NEW_VAR_ATTACKING_MON's VAR_MOVE_ID */
    EVENT_PROTECT_BROKEN = 0x1F,        /* new event: NEW_VAR_ATTACKING_MON's move broke the protection */
    EVENT_ACCURACY_STAGE = 0x33,        /* a hit's accuracy / evasion stages: VAR_EVASION_STAGE (6 = neutral) */
    EVENT_MOVE_POWER = 0x38,            /* VAR_MOVE_POWER_RATIO *= x (Iron Fist, Technician) */
    EVENT_ATTACKING_STAT = 0x3B,        /* the attacker's attacking stat: VAR_RATIO *= x (Huge Power, Guts) */
    EVENT_DEFENDING_STAT = 0x3C,        /* the defender's defending stat: VAR_RATIO *= x; VAR_MOVE_CATEGORY 1: Defense */
    EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
    EVENT_DETERMINE_MOVE_DAMAGE = 0x45, /* a real hit's damage is settled (Disguise, Ice Face break here) */
    EVENT_DAMAGE_RATIO = 0x47,          /* the final damage of a hit: VAR_RATIO *= x (Filter, Multiscale) */
    EVENT_MOVE_DAMAGE_PROCESSING_END = 0x48, /* a hit's damage, estimated or real: VAR_DAMAGE (Disguise) */
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
    EVENT_TURN_CHECK_DONE = 0x78,       /* the turn's end is over */
    EVENT_WEATHER_NEGATION = 0x7A,      /* Air Lock, Cloud Nine: VAR_WEATHER_NEGATED */
    EVENT_AFTER_WEATHER_CHANGE = 0x7E,
    EVENT_AFTER_KO = 0x83,              /* the attacker's damaging move is done: VAR_TARGET_COUNT, VAR_TARGET0.. (W2U:
                                         * EVENT_DAMAGE_PROCESSING_END_HIT_REAL; Moxie counts its KOs here) */
    EVENT_AFTER_MOVE_HITS = 0x87,       /* a move's hits are done: the targets (HandlerTargetsContain) */
    EVENT_BEFORE_ABILITY_CHANGE = 0x89,
    EVENT_AFTER_ABILITY_CHANGE = 0x8A,
    EVENT_FORCE_OUT_CHECK = 0x8B,       /* may VAR_DEFENDING_MON be forced out (Roar, Whirlwind)? VAR_FAIL_FLAG */
    EVENT_SIMPLE_DAMAGE_REACTION = 0x91, /* new event (W2U's; the engine's ID is the item reaction check): damage that
                                         * wasn't a move's hit, NEW_VAR_MON_ID, VAR_DAMAGE (resident/damage.c) */
    EVENT_CHARGE_UP_START = 0x95,       /* a two-turn move's charge turn starts (Dive, Fly) */
    EVENT_NOTIFY_FAINTED = 0xA3,        /* VAR_MON_ID fainted */
    /* W2U's events past the engine's (resident/damage.c raises them; no engine handler has these IDs) */
    EVENT_W2U_DAMAGE_WEATHER = 0x100,   /* in sun, the weather CalcDamage's weather modifier uses: VAR_WEATHER */
    EVENT_W2U_ATTACK_STAT_SELECTOR = 0x102, /* the attacking stat: VAR_ATTACK_STAT_SELECTOR (BMV_*: Body Press) */
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
    NEW_VAR_MON_ID = 0x07,              /* W2U's new events: the Pokémon (VAR_MON_ID ... are -1 in them) */
    NEW_VAR_ATTACKING_MON = 0x08,
    NEW_VAR_DEFENDING_MON = 0x09,
    VAR_TARGET_COUNT = 0x05,            /* EVENT_AFTER_KO: the move's targets, VAR_TARGET0 + i */
    VAR_TARGET0 = 0x06,
    VAR_SPECIAL_PRIORITY = 0x11,        /* EVENT_SPECIAL_PRIORITY: 0 last, 1 normal, 2 first in the bracket */
    VAR_MOVE_ID = 0x12,
    VAR_POKE_TYPE = 0x15,               /* EVENT_CHECK_TYPE_EFFECTIVENESS: the defending type checked */
    VAR_MOVE_TYPE = 0x16,
    VAR_NO_TYPE_EFFECTIVENESS = 0x4B,   /* EVENT_CHECK_TYPE_EFFECTIVENESS: nonzero, an immunity counts as x1 */
    VAR_SET_TYPE_EFFECTIVENESS = 0x4C,  /* EVENT_CHECK_TYPE_EFFECTIVENESS: W2U_OVERRIDE_EFFECTIVENESS_* (the engine's
                                         * "force x1" flag before W2U) */
    VAR_MOVE_CATEGORY = 0x1A,           /* EVENT_DEFENDING_STAT: 1 = the defending stat is Defense (Psyshock too) */
    VAR_EVASION_STAGE = 0x28,           /* 6 = neutral */
    VAR_MOVE_POWER_RATIO = 0x31,        /* fixed point, 4096 = x1 */
    VAR_TYPE_EFFECTIVENESS = 0x38,      /* EVENT_DAMAGE_RATIO: the hit's effectiveness (BtlCalc_ClassifyEffectiveness) */
    VAR_RATIO = 0x35,                   /* fixed point, 4096 = x1 */
    VAR_NO_EFFECT = 0x40,
    VAR_FAIL_FLAG = 0x41,
    VAR_BREAK_PROTECT = 0x51,           /* EVENT_PROTECT_BREAK_CHECK: 1 broken (Feint), 2 through (W2U) */               /* the status, Yawn and stat change checks: 1 = blocked */
    VAR_WEATHER_NEGATED = 0x41,         /* EVENT_WEATHER_NEGATION: nonzero, the weather has no effect (VAR_FAIL_FLAG's slot) */
    VAR_GENERAL_USE_FLAG = 0x51,        /* a flag events set (EVENT_CHECK_DAMAGE_TO_RECOVER: the move heals) */
    VAR_NO_DEFAULT_MESSAGE = 0x51,      /* EVENT_CHECK_NO_EFFECT: nonzero, no "It doesn't affect X..." (VAR_BREAK_PROTECT's slot) */
    VAR_DAMAGE = 0x32,                  /* EVENT_MOVE_DAMAGE_PROCESSING_END: the hit's damage */
    VAR_ATTACK_STAT_SELECTOR = 0x33,    /* EVENT_W2U_ATTACK_STAT_SELECTOR: the attacking stat (BMV_ATTACK ...) */
    VAR_WEATHER = 0x39,                 /* EVENT_W2U_DAMAGE_WEATHER: the weather */
    VAR_SUBSTITUTE_HIT = 0x46,          /* nonzero: the hit landed on a substitute */
    VAR_NO_SECONDARY = 0x47,            /* nonzero: no secondary effects for this hit (Shield Dust) */               /* EVENT_CHECK_NO_EFFECT: rewritten to 1, the move does not affect the target */
};

/* Type effectiveness grades: the engine's (immune, x1/4, x1/2, x1, x2, x4) and W2U's beyond them (resident/
 * effectiveness.c: added types, Tar Shot) */
enum {
    W2U_EFF_IMMUNE = 0,
    W2U_EFF_1_4 = 1,
    W2U_EFF_1_2 = 2,
    W2U_EFF_1 = 3,
    W2U_EFF_2 = 4,
    W2U_EFF_4 = 5,
    W2U_EFF_1_8 = 6,
    W2U_EFF_8 = 7,
    W2U_EFF_16 = 8,
};
/* VAR_SET_TYPE_EFFECTIVENESS: keep, x1/2, x1, x2, or W2U_COMPOUND_EFFECTIVENESS + a grade to multiply by */
enum {
    W2U_DONT_OVERRIDE_EFFECTIVENESS = 0,
    W2U_OVERRIDE_EFFECTIVENESS_1_2 = 1,
    W2U_OVERRIDE_EFFECTIVENESS_1 = 2,
    W2U_OVERRIDE_EFFECTIVENESS_2 = 3,
    W2U_COMPOUND_EFFECTIVENESS = 4,
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
    HANDLER_CMD_DAMAGE = 0x07,          /* BattleHandlerDamageParam */
    HANDLER_CMD_CURE_CONDITION = 0x0B,  /* BattleHandlerCureConditionParam */
    HANDLER_CMD_ADD_CONDITION = 0x0C,   /* BattleHandlerAddConditionParam */
    HANDLER_CMD_CHANGE_STAT = 0x0E,     /* BattleHandlerStatChangeParam */
    HANDLER_CMD_SET_STAT_STAGES = 0x0F, /* BattleHandlerSetStatStageParam (Psych Up) */
    HANDLER_CMD_RESET_STAT_STAGES = 0x10, /* BattleHandlerResetStatStageParam (Clear Smog, Haze) */
    HANDLER_CMD_CHANGE_TYPE = 0x14,     /* BattleHandlerChangeTypeParam: "X transformed into the Y type!" */
    HANDLER_CMD_SET_CONTINUE_FLAG = 0x17,   /* BattleHandlerFlagParam: CONT_FLAG_* */
    HANDLER_CMD_RESET_CONTINUE_FLAG = 0x18, /* BattleHandlerFlagParam */
    HANDLER_CMD_ADD_SIDE_EFFECT = 0x19, /* BattleHandlerAddSideEffectParam */
    HANDLER_CMD_REMOVE_SIDE_EFFECT = 0x1A, /* BattleHandlerRemoveSideEffectParam */
    HANDLER_CMD_CHANGE_WEATHER = 0x1D,  /* BattleHandlerChangeWeatherParam */
    HANDLER_CMD_CHANGE_ABILITY = 0x1F,  /* BattleHandlerAbilityChangeParam */
    HANDLER_CMD_FORCE_USE_ITEM = 0x22,  /* BattleHandlerForceUseItemParam: eat or use an item now (Bug Bite) */
    HANDLER_CMD_CONSUME_ITEM = 0x23,    /* BattleHandlerConsumeItemParam: the item animation and message, used up */
    HANDLER_CMD_HIDE_TURN_CANCEL = 0x36, /* BattleHandlerHideTurnParam: a hidden Pokémon (Fly, Dig) comes back */
    HANDLER_CMD_CHANGE_FORM = 0x39,     /* BattleHandlerChangeFormParam */
};

/* BattleHandler_StrSetup message kinds */
enum {
    HANDLER_STR_STD = 1,                /* one message (bank 19); its arguments as AddArg gives them */
    HANDLER_STR_SET = 2,                /* a set of three messages (player's, wild, foe's Pokémon), bank 18 */
};

#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
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

#endif /* !W2U_DECOMP */
/* Battle Pokémon IDs and positions */
#define BATTLE_MAX_MON_ID 24                /* monIds are 0-23 */
#define BATTLE_POS_NONE 6                   /* Handler_PokeIDToPokePos: not on the field */
/* HandlerGetAlivePartyCount's code: the range (high byte) and the position (low byte) */
#define BATTLE_RANGE_FULL_FRIENDS 7         /* the whole side of the position */

/* GetTurnFlag's flags (W2U's names) */
enum {
    TURN_FLAG_PROTECT = 7,              /* protected this turn (Protect, Detect...) */
    TURN_FLAG_CANT_USE_ITEM = 9,        /* can't use its held item this turn */
};

#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
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
    CONDITION_EMBARGO = 0x13,           /* can't use its held item (Embargo) */
    CONDITION_PERISH_SONG = 20,
    CONDITION_CHOICE_LOCK = 0x1B,       /* locked into one move (the Choice items) */
};

/* The field's conditions (IsFieldEffectActive; decomp: include/constants/battle.h) */
enum {
    FIELD_CONDITION_MAGIC_ROOM = 7,     /* held items do nothing */
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

/* The stages, as GetBattleMonStat's STATSTAGE_ATTACK .. STATSTAGE_EVASION values (6 = neutral) */
typedef struct BattleHandlerSetStatStageParam {
    u32 header;
    u8 monIndex;
    u8 attack;
    u8 defense;
    u8 spAttack;
    u8 spDefense;
    u8 speed;
    u8 accuracy;
    u8 evasion;
} BattleHandlerSetStatStageParam;

typedef struct BattleHandlerResetStatStageParam {
    u32 header;
    u8 count;
    u8 monIndices[6];
} BattleHandlerResetStatStageParam;

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
    u8 useString;                       /* 1: the work's string instead of the cure messages (none if empty) */
    u8 unk16[2];
} BattleHandlerCureConditionParam;

typedef struct BattleHandlerDamageParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u16 amount;
    u8 targetIndex;
    u8 checkSemi : 1;                   /* no damage to a hidden Pokémon (Fly, Dig) */
    u8 showViewEffect : 1;              /* play effect first, at (effectArg1, effectArg2) */
    u8 unkFlags : 6;
    u16 effect;
    u8 effectArg1;
    u8 effectArg2;
    BattleHandlerString string;
} BattleHandlerDamageParam;

/* HANDLER_CMD_SET_CONTINUE_FLAG / RESET: a flag that lasts until reset */
typedef struct BattleHandlerFlagParam {
    u32 header;
    u32 flag;                           /* CONT_FLAG_* */
    u8 monIndex;
} BattleHandlerFlagParam;

/* Clears the flag (CONT_FLAG_SHADOW_FORCE...) and shows the Pokémon's sprite again; nothing if it wasn't set */
typedef struct BattleHandlerHideTurnParam {
    u32 header;
    u8 monIndex;
    u8 unk05[3];
    u32 flag;
    BattleHandlerString string;
} BattleHandlerHideTurnParam;

typedef struct BattleHandlerChangeFormParam {
    u32 header : 23;
    u32 popup : 1;
    u32 unk24 : 8;
    u8 monIndex;
    u8 form;
    u8 unk06[2];                        /* PW2Code's dontResetOnSwitch; nothing reads it */
    BattleHandlerString string;
} BattleHandlerChangeFormParam;

/* The start of every handler command's work (BattleHandler_PushWork fills it in) */
typedef struct BattleHandlerHeader {
    u32 command : 8;
    u32 monId : 5;                      /* the Pokémon the command is pushed for */
    u32 size : 10;
    u32 popup : 1;                      /* inside the ability popup */
    u32 checkPrevResult : 1;            /* skipped when the previous command failed */
    u32 checkFainted : 1;               /* skipped when monId has fainted */
    u32 unk26 : 6;
} BattleHandlerHeader;
typedef BattleHandlerHeader BattleHandlerUseHeldItemParam;   /* UseHeldItem's work is the header alone (decomp name) */

/* A Pokémon's chosen action (decomp: include/battle/btl_action.h) */
typedef union BattleAction {
    u32 raw;
    struct {
        u32 action : 4;                 /* BTL_ACTION_* */
        u32 target : 3;
        u32 move : 16;
        u32 unk23 : 9;
    } bits;
} BattleAction;
#define BTL_ACTION_FIGHT 1

/* The turn's action order (decomp: include/battle/btl_action_order.h) */
typedef struct ActionOrderEntry {
    BattleMon *mon;
    BattleAction action;
    u32 key;                            /* the sort key: speed, priorities */
    u8 clientId;
    u8 done;                            /* the action has run */
    u8 interrupting;
    u8 unk0F;
} ActionOrderEntry;

#endif /* !W2U_DECOMP */
/* Continue flags (BattleHandlerFlagParam, BattleHandlerHideTurnParam; W2U's names) */
enum {
    CONT_FLAG_SHADOW_FORCE = 0x06,      /* hidden: no move reaches it (Shadow Force's charge turn) */
    CONT_FLAG_RECHARGE = 0x0C,          /* must recharge (Hyper Beam): the command menu skips it; the server resets
                                         * it once the turn's actions are in */
};

/* Server display commands (ServerDisplay_AddCommon; W2U's names) */
enum {
    SERVER_CMD_HIDE_SPRITE = 0x31,      /* (monId, 1) hides the Pokémon's sprite (a charge turn), (monId, 0) shows it */
    SERVER_CMD_STD_MESSAGE = 0x5A,      /* ServerDisplay_AddMessageImpl: a standard message (bank 19) */
    SERVER_CMD_SET_MESSAGE = 0x5B,      /* ServerDisplay_AddMessageImpl: a set message (bank 18) and its arguments */
};

#if !defined(W2U_DECOMP)
#define BTL_STYLE_DOUBLE 1                  /* BtlSetup_GetBattleStyle */
#endif
#define CONDITION_CANT_ESCAPE 0x16          /* Mean Look's: can't switch out */

#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
/* A client's party in battle (decomp: include/battle/btl_main.h) */
typedef struct BattleParty {
    BattleMon *mons[6];
    u8 count;
    u8 unk19[3];
} BattleParty;

#define PKM_PARAM_IS_EGG 0x4c                /* PokeParty_GetParam */

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
W2U_ENGINE_LAYOUT(set_stat_stages_size, sizeof(BattleHandlerSetStatStageParam) == 0x0C);
W2U_ENGINE_LAYOUT(reset_stat_stages_ids, __builtin_offsetof(BattleHandlerResetStatStageParam, monIndices) == 0x05);
W2U_ENGINE_LAYOUT(battle_party_count, __builtin_offsetof(BattleParty, count) == 0x18);
W2U_ENGINE_LAYOUT(move_param_type, __builtin_offsetof(BtlFlowMoveParam, type) == 0x06);
W2U_ENGINE_LAYOUT(damage_effect, __builtin_offsetof(BattleHandlerDamageParam, effect) == 0x08);
W2U_ENGINE_LAYOUT(damage_string, __builtin_offsetof(BattleHandlerDamageParam, string) == 0x0C);
W2U_ENGINE_LAYOUT(flag_mon, __builtin_offsetof(BattleHandlerFlagParam, monIndex) == 0x08);
W2U_ENGINE_LAYOUT(hide_turn_flag, __builtin_offsetof(BattleHandlerHideTurnParam, flag) == 0x08);
W2U_ENGINE_LAYOUT(hide_turn_string, __builtin_offsetof(BattleHandlerHideTurnParam, string) == 0x0C);
W2U_ENGINE_LAYOUT(change_form_string, __builtin_offsetof(BattleHandlerChangeFormParam, string) == 0x08);
W2U_ENGINE_LAYOUT(handler_header_size, sizeof(BattleHandlerHeader) == 4);
W2U_ENGINE_LAYOUT(action_order_size, sizeof(ActionOrderEntry) == 0x10);
W2U_ENGINE_LAYOUT(action_order_done, __builtin_offsetof(ActionOrderEntry, done) == 0x0D);
W2U_ENGINE_LAYOUT(stat_change_string, __builtin_offsetof(BattleHandlerStatChangeParam, string) == 0x18);

#endif /* !W2U_DECOMP */
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
    BMV_EFFECTIVE_ABILITY = 0x11,       /* the ability, 0 while suppressed (Gastro Acid) */
    BMV_FORM = 0x13,
};

/* getMoveFlag's flags: bit indices into the move record's flags (the decomp's MOVE_FLAG_* are the bit masks) */
enum {
    MOVE_FLAG_INDEX_CONTACT = 0,
    MOVE_FLAG_INDEX_PROTECT = 3,        /* Protect blocks it */
    MOVE_FLAG_INDEX_SOUND = 8,
    MOVE_FLAG_INDEX_BYPASS_SUBSTITUTE = 13, /* hits through a Substitute (Roar, Perish Song) */
};                                      /* W2U's own flags (MOVE_FLAG_INDEX_WIND ...): megab2w2/mb_ids.h */

/* Side effects (IsSideEffectSet, BattleHandlerRemoveSideEffectParam) */
enum {
    SIDE_EFFECT_REFLECT = 0,
    SIDE_EFFECT_LIGHT_SCREEN = 1,
    SIDE_EFFECT_SAFEGUARD = 2,
    SIDE_EFFECT_MIST = 3,
    SIDE_EFFECT_TAILWIND = 4,
    SIDE_EFFECT_TOXIC_SPIKES = 7,
};
#define BATTLE_SIDES 2

#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
/* PML_MoveGetParam parameters and the categories it returns */
enum {
    MOVE_PARAM_TYPE = 0x00,
    MOVE_PARAM_CATEGORY = 0x02,
    MOVE_PARAM_TARGET = 0x1B,
};

#endif /* !W2U_DECOMP */

/* Move targets (MOVE_PARAM_TARGET; the decomp's names, include/constants/battle.h) */
#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
enum {
    MOVE_TARGET_SELECTED = 0,           /* one adjacent Pokémon the user picks (Pound) */
    MOVE_TARGET_USER_OR_ALLY = 1,       /* Acupressure */
    MOVE_TARGET_ALLY = 2,               /* Helping Hand */
    MOVE_TARGET_FOE = 3,                /* one foe (Me First) */
    MOVE_TARGET_ALL_ADJACENT = 4,       /* every adjacent Pokémon but the user (Surf, Earthquake) */
    MOVE_TARGET_ADJACENT_FOES = 5,      /* every adjacent foe (Growl, Rock Slide) */
    MOVE_TARGET_USER_PARTY = 6,         /* the user's party (Heal Bell) */
    MOVE_TARGET_USER = 7,               /* Swords Dance */
    MOVE_TARGET_ALL = 8,                /* every Pokémon in battle (Perish Song) */
    MOVE_TARGET_RANDOM_FOE = 9,         /* Thrash, Outrage */
    MOVE_TARGET_FIELD = 10,             /* the whole field (Rain Dance, Trick Room) */
    MOVE_TARGET_FOE_SIDE = 11,          /* the foes' side (Spikes) */
    MOVE_TARGET_USER_SIDE = 12,         /* the user's side (Reflect) */
};
#endif /* !W2U_DECOMP */
#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
enum {
    MOVE_CATEGORY_STATUS = 0,
    MOVE_CATEGORY_PHYSICAL = 1,
    MOVE_CATEGORY_SPECIAL = 2,
};
#endif /* !W2U_DECOMP */

/* Data IDs (abilities, types, moves, items, messages) are not the engine's: mechanics take them from the data
 * headers (megab2w2/mb_ids.h for now). */

#if !defined(W2U_DECOMP)   /* decomp builds: w2u/engine_decomp.h (the decomp's own declarations) */
W2U_C_BEGIN

/* battle_event.c */
void BattleEvent_CallHandlers(BtlServerFlow *flow, u32 event);
/* A frame of event variables around an event call; line is a debug aid the game ignores */
void BattleEventVar_Push(u32 line);
void BattleEventVar_Pop(u32 line);
void BattleEventVar_SetRewriteOnceValue(u32 key, s32 value);
void BattleEventVar_SetValue(u32 key, s32 value);
void BattleEventVar_SetConstValue(u32 key, s32 value);   /* fixed for the event: handlers can't rewrite it */
u32 BattleEventVar_GetValue(u32 key);
/* The variable's value, if the frame has it: nonzero then */
b32 BtlEventVar_TryRead(u16 key, s32 *value);
void BattleEventVar_MulValue(u16 key, s32 value);
b32 BattleEventVar_RewriteValue(u16 key, s32 value);

/* btl_main.c, btl_server_flow.c, btl_pokeparam.c */
b32 IsAllyMonID(u8 monId1, u8 monId2);
u8 MonIDToClientID(u8 monId);
BattleParty *GetPartyData(BtlPokeCon *pokeCon, u32 clientId);
u8 GetSideFromMonID(u8 monId);
u8 GetSideFromOpposingMonID(u8 monId);          /* the side facing the Pokémon */
/* The side effect (SIDE_EFFECT_*) is up on the side */
b32 IsSideEffectSet(u8 side, u32 sideEffectId);
BattleMon *GetBattleMon(BtlServerFlow *serverFlow, u8 monId);
/* BMV_ATTACK .. BMV_SPEED: the stat with its stat stage applied */
u32 GetBattleMonStat(const BattleMon *mon, u32 stat);
/* BMV_ATTACK .. BMV_SPEED: the stat without stages (Wonder Room swaps the defenses) */
s32 RawBattleMonStat(const BattleMon *mon, u32 stat);
/* A critical hit's stat: the attacker's drops and the defender's boosts are ignored */
u16 CritAtkDefLevel(BattleMon *mon, u32 stat);
b32 IsFainted(const BattleMon *mon);
b32 CheckCondition(const BattleMon *mon, u32 conditionId);
u32 GetBattleMonHeldItem(BattleMon *mon);
b32 IsSubstituteActive(BattleMon *mon);
b32 TransformCheck(BattleMon *mon);             /* transformed (Transform, Imposter) */
u8 GetMonID(BattleMon *mon);
u32 GetAdditionalConditionFlag(BattleMon *mon, u32 flag);   /* CONT_FLAG_* */
u16 GetBattleMonSpecies(const BattleMon *mon);  /* decomp builds (W2U_Species): not in IRDO.yml */
u32 GetTurnFlag(BattleMon *mon, u32 flag);
PokeTypePair GetPokeType(BattleMon *mon);
PokeTypePair PokeTypePair_MakeMonotype(u32 singleTypeId);
b32 PokeTypePair_HasType(PokeTypePair pair, u32 queryTypeId);
b32 IsMonFullHP(BattleMon *mon);
/* Max HP / divisor, at least 1 */
u32 DivideMaxHPZeroCheck(BattleMon *mon, u32 divisor);
/* The Pokémon a position code covers ((range << 8) | position), into monIds: their count */
u8 HandlerGetAlivePartyCount(BtlServerFlow *handler, u16 code, u8 *monIds);
/* The Pokémon's battle position, BATTLE_POS_NONE if it is not on the field */
u8 Handler_PokeIDToPokePos(BtlServerFlow *flow, u8 monId);
u8 Handler_PokePosToPokeID(BtlServerFlow *flow, u8 battlePosition);
u32 BtlSetup_GetBattleStyle(BtlMainModule *mainModule);
/* The weather as it is (Air Lock doesn't hide it) */
u8 ServerEvent_GetWeather(BtlServerFlow *flow);
/* The field's weather, before Air Lock and Cloud Nine */
u32 GetFieldWeather(void);
/* No Guard, Lock-On and Mind Reader: the move hits whatever (the hide check is skipped) */
b32 IsGuaranteedHit(BtlServerFlow *flow, BattleMon *attacker, BattleMon *defender);
b32 IsMoldBreakerIgnoredAbility(u16 ability);  /* the native list of abilities Mold Breaker ignores (Gen 4-5) */
b32 IsFieldEffectActive(u32 effect);            /* FIELD_CONDITION_*: Trick Room, Magic Room... */
/* The native move lists: Sheer Force's moves, and the moves Assist / Sleep Talk / Me First / Copycat can't call */
b32 IsAffectedBySheerForce(u16 move);
b32 IsAssistExcludedMove(u16 move);
b32 IsSleepTalkExcludedMove(u16 move);
b32 IsMeFirstExcludedMove(u16 move);
b32 IsCopycatExcludedMove(u16 move);
/* "X must recharge!": the recharge turn's action */
void ServerControl_RechargeAction(BtlServerFlow *flow, BattleMon *rechargingMon);
/* Lightning Rod, Storm Drain, Follow Me, Rage Powder ask first: nonzero, the move isn't redirected */
b32 Battle_IsRedirectBlocked(BtlServerFlow *flow, u8 attackerId, u8 defenderId, u16 move);
/* The move's priority after the events (Prankster, Gale Wings, Triage), + 7 */
u8 ServerEvent_GetMovePriority(BtlServerFlow *flow, u16 move, BattleMon *mon);
u32 GetBattleMonStatus(BattleMon *mon);         /* 0: none, else CONDITION_* */
/* The stat can still change by stageDelta (not at +6 / -6 already) */
b32 IsStatChangeValid(BattleMon *mon, u32 statId, s32 stageDelta);
void ServerEvent_GetMoveParam(BtlServerFlow *flow, u16 move, BattleMon *moveUser, BtlFlowMoveParam *moveParamsOut);
/* btl_calc.c: one type against one type (W2U: its chart file), W2U_EFF_* */
u32 GetTypeEffectiveness(u8 attackType, u8 defenseType);
/* The Pokémon floats (Flying type, Levitate, Magnet Rise...); checkSkyDrop: Sky Drop counts too */
b32 ServerControl_CheckFloating(BtlServerFlow *flow, BattleMon *mon, u32 checkSkyDrop);
/* overlay 169: the conditions that change a type check (Foresight, Miracle Eye, Ingrain, Smack Down...) */
void Condition_CheckTypeImmunity(BtlServerFlow *flow, BattleMon *target);
/* How many times the move hits (hitWork: W2U_HitWork) */
b32 ServerEvent_CheckMultihitHits(BtlServerFlow *flow, BattleMon *mon, u16 move, void *hitWork);
/* After a move's hits: its Fire-type hits thaw the frozen targets (targets: the hit Pokémon, a BtlMonSet) */
void ServerControl_ThawHitTargets(BtlServerFlow *flow, BtlFlowMoveParam *param, BattleMon *attacker, void *targets);

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

/* btl_server_flow.c: the handler commands the dispatcher runs; each returns its result (nonzero: done), which the
 * dispatcher keeps for checkPrevResult and BattleHandler_Result */
u8 BattleHandler_UseHeldItem(BtlServerFlow *flow, BattleHandlerUseHeldItemParam *param);
u8 BattleHandler_ForceUseItem(BtlServerFlow *flow, BattleHandlerForceUseItemParam *param);
u8 BattleHandler_RecoverHP(BtlServerFlow *flow, const BattleHandlerRecoverHPParam *param, u16 itemId);
u8 BattleHandler_Damage(BtlServerFlow *flow, BattleHandlerDamageParam *param);
u8 BattleHandler_StatChange(BtlServerFlow *flow, const BattleHandlerStatChangeParam *param, u16 context);

/* btl_server_cmd.c: a command for the clients (SERVER_CMD_*) and its arguments */
void ServerDisplay_AddCommon(BtlServerCmdQueue *queue, u32 commandId, ...);
/* a message command (SERVER_CMD_SET_MESSAGE: the message ID, then its arguments) */
void ServerDisplay_AddMessageImpl(BtlServerCmdQueue *queue, u32 commandId, ...);
/* The handler-effect state (BtlServerFlow.actionState): a new level for effects pushed by events raised now, and back
 * (W2U_PushHandlerState / W2U_PopHandlerState in battle_api.h) */
u32 HEManager_PushState(u32 *state);
void HEManager_PopState(u32 *state, u32 level);

/* btl_handler.c: the current event's targets contain the Pokémon (EVENT_AFTER_MOVE_HITS) */
b32 HandlerTargetsContain(u32 monId);

/* btl_server_flow.c */
/* The weather as abilities see it (Air Lock and Cloud Nine read as none) */
u8 GetWeather(BtlServerFlow *serverFlow);
/* Set while the engine checks a matchup: Mummy and Flame Body skip their reactions then */
b32 Handler_CheckMatchup(BtlServerFlow *flow);
b32 AbilityEvent_RollEffectChance(BtlServerFlow *flow, u32 chancePercent);

/* poke_tool.c */
u32 PokeParty_GetParam(const PartyPkm *pkm, u32 param, void *buffer);

/* waza_tool.c */
s32 PML_MoveGetParam(u16 move, u32 param);
s32 PML_MoveGetCategory(u16 move);             /* MOVE_CATEGORY_* */
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

#endif /* !W2U_DECOMP */
/* Struct fields the injection build reads by offset (battle_api.h); a decomp build uses the field */
#if !defined(W2U_DECOMP)
#define W2U_SERVERFLOW_SIMULATION_DEPTH 0x774   /* BtlServerFlow.simulationDepth: nonzero while the AI simulates */
#define W2U_SERVERFLOW_MAIN_MODULE 0x04         /* BtlServerFlow.mainModule */
#define W2U_SERVERFLOW_POKECON 0x08             /* BtlServerFlow.pokeCon */
#define W2U_SERVERFLOW_QUEUE 0x0C               /* BtlServerFlow.queue: the commands for the clients */
#define W2U_SERVERFLOW_ORIGINAL_TARGETS 0x850  /* the move's targets before redirection (BtlServerFlow.unk850) */
#define W2U_POKESET_COUNT 0x42                 /* PokeSet.count, the set's Pokémon */
#define W2U_BATTLEMON_TYPE1 0xF8               /* BattleMon.type1, type2 after it */
#define W2U_ADDR_ANNOUNCE_NO_EFFECT 0x021A92A9u /* ov167 ServerDisplay_DoesntAffect (Thumb), White 2 */
#define W2U_ADDR_ANNOUNCE_FLOATING 0x021AAB19u  /* ov167 ServerControl_FloatingImmune (Thumb), White 2 */
#define W2U_ADDR_COUNT_EFFECTIVENESS 0x021AB77Du /* ov167 BtlServerFlow_CountEffectiveness (Thumb), White 2 */
#define W2U_ADDR_EFFECTIVENESS_MESSAGE_MULTI 0x021A9399u /* ov167 ServerDisplay_EffectivenessMessageMulti (Thumb) */
#define W2U_SERVERFLOW_HANDLER_STATE 0x1DAC     /* BtlServerFlow.actionState (W2U's ServerFlow.HEManager) */
#define W2U_SERVERFLOW_ACTION_ORDER_COUNT 0x782  /* BtlServerFlow.actionOrderCount */
#define W2U_SERVERFLOW_ACTION_ORDER 0x7E0       /* BtlServerFlow.actionOrder[6] */
#define W2U_BATTLEMON_SOURCE 0x00               /* BattleMon.core.src: the party Pokémon it battles as */
#define W2U_BATTLEMON_SPECIES 0x0C              /* BattleMon.core.species (GetBattleMonSpecies isn't in IRDO.yml) */
#endif

#endif /* W2U_ENGINE_H */
