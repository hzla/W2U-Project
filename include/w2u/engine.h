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
    EVENT_DAMAGE_RATIO = 0x47,          /* the final damage of a hit: VAR_RATIO *= x (Filter, Multiscale) */
};

/* Event variables (W2U's names) */
enum {
    VAR_MON_ID = 0x02,
    VAR_ATTACKING_MON = 0x03,
    VAR_DEFENDING_MON = 0x04,
    VAR_MOVE_ID = 0x12,
    VAR_MOVE_TYPE = 0x16,
    VAR_MOVE_CATEGORY = 0x1A,
    VAR_RATIO = 0x35,                   /* fixed point, 4096 = x1 */
};

/* GetBattleMonStat values */
enum {
    BMV_ABILITY = 0x10,
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

/* btl_server_flow.c, btl_pokeparam.c */
BattleMon *GetBattleMon(BtlServerFlow *serverFlow, u8 monId);
u32 GetBattleMonStat(const BattleMon *mon, u32 stat);

/* waza_tool.c */
s32 PML_MoveGetParam(u16 move, u32 param);

W2U_C_END

/* Struct fields the decomp has not named yet: their offsets, for the injection build only (battle_api.h) */
#if !defined(W2U_DECOMP)
#define W2U_SERVERFLOW_SIMULATION_DEPTH 0x774   /* BtlServerFlow.simulationDepth: nonzero while the AI simulates */
#endif

#endif /* W2U_ENGINE_H */
