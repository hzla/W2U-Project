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
    EVENT_MOVE_END = 0x04,
    EVENT_CHECK_NO_EFFECT = 0x2D,       /* per target: may the move affect it? (Volt Absorb, Soundproof) */
    EVENT_ACCURACY_STAGE = 0x33,        /* a hit's accuracy / evasion stages: VAR_EVASION_STAGE (6 = neutral) */
    EVENT_MOVE_POWER = 0x38,            /* VAR_MOVE_POWER_RATIO *= x (Iron Fist, Technician) */
    EVENT_ATTACKER_POWER = 0x3B,        /* the attacker's attacking stat: VAR_RATIO *= x (Huge Power) */
    EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
    EVENT_DAMAGE_RATIO = 0x47,          /* the final damage of a hit: VAR_RATIO *= x (Filter, Multiscale) */
    EVENT_STAT_CHANGE_CHECK = 0x5B,     /* may VAR_MON_ID's stat change? */
    EVENT_STAT_CHANGE_GUARD = 0x5C,
};

/* Event variables (W2U's names) */
enum {
    VAR_MON_ID = 0x02,
    VAR_ATTACKING_MON = 0x03,
    VAR_DEFENDING_MON = 0x04,
    VAR_MOVE_ID = 0x12,
    VAR_MOVE_TYPE = 0x16,
    VAR_MOVE_CATEGORY = 0x1A,
    VAR_EVASION_STAGE = 0x28,           /* 6 = neutral */
    VAR_MOVE_POWER_RATIO = 0x31,        /* fixed point, 4096 = x1 */
    VAR_RATIO = 0x35,                   /* fixed point, 4096 = x1 */
};

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

W2U_C_END

/* Struct fields the injection build reads by offset (battle_api.h); a decomp build uses the field */
#if !defined(W2U_DECOMP)
#define W2U_SERVERFLOW_SIMULATION_DEPTH 0x774   /* BtlServerFlow.simulationDepth: nonzero while the AI simulates */
#endif

#endif /* W2U_ENGINE_H */
