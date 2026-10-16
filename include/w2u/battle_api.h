/* W2U engine interface, layer B: the battle API W2U's mechanics are written against. C and C++; no addresses and no
 * struct offsets (those live in w2u/engine.h). See docs/engine-interface.md.
 *
 * A mechanic file (src/mechanics/) includes only this header. It defines its handlers static, its handler table with
 * W2U_HANDLER_TABLE and registers the table per ability / item / move with W2U_MECHANIC; the battle module registry
 * (src/pokeweb_gameplay/battle_modules/registry.json) must list the same entries, which its generator checks.
 *
 * The helpers grow from megab2w2/ability_api.h as mechanics are converted: queries and ratios now; the effect
 * helpers (popups, stat stage changes, messages) with the first mechanic that needs the handler-effect structs. */
#ifndef W2U_BATTLE_API_H
#define W2U_BATTLE_API_H

#include "w2u/engine.h"

/* A mechanic's handler table: W2U_HANDLER_TABLE(FluffyHandlers) = { { EVENT_DAMAGE_RATIO, Handler }, }; */
#define W2U_HANDLER_TABLE(name) W2U_EXTERN_C const BattleEventHandlerEntry name[]

/* Registers a handler table for an ability, item or move (kind: ABILITY, ITEM or MOVE; id: its constant). It declares
 * the table again, so it follows the table's definition; tools/generate_w2u_battle_registry.py reads these lines. */
#define W2U_MECHANIC(kind, id, table) W2U_EXTERN_C const BattleEventHandlerEntry table[]

#define W2U_RATIO_ONE 4096              /* VAR_RATIO's x1 */

W2U_C_BEGIN

/* W2U's own engine extensions (resident in White2Upgrade.dll) */

/* The move makes contact as used now: its contact flag, unless the attacker's Long Reach removes it (Shell Side Arm:
 * when it hits physically). Logic reacting to contact asks this, not the move's flag. */
b32 W2U_MoveMakesContact(BtlServerFlow *flow, u16 move, u32 attacker);

W2U_C_END

/* Who and what the current event is about */
static inline u8 W2U_Subject(void) { return (u8)BattleEventVar_GetValue(VAR_MON_ID); }
static inline u8 W2U_Attacker(void) { return (u8)BattleEventVar_GetValue(VAR_ATTACKING_MON); }
static inline u8 W2U_Defender(void) { return (u8)BattleEventVar_GetValue(VAR_DEFENDING_MON); }
static inline u16 W2U_Move(void) { return (u16)BattleEventVar_GetValue(VAR_MOVE_ID); }
/* The move's type as this hit uses it (after -ate abilities, Weather Ball...) */
static inline u32 W2U_MoveType(void) { return BattleEventVar_GetValue(VAR_MOVE_TYPE); }

/* Moves */
static inline u32 W2U_MoveCategory(u16 move) { return (u32)PML_MoveGetParam(move, MOVE_PARAM_CATEGORY); }
static inline b32 W2U_IsStatusMove(u16 move) { return W2U_MoveCategory(move) == MOVE_CATEGORY_STATUS; }
/* The current event's move makes contact, used by its attacker */
static inline b32 W2U_MakesContact(BtlServerFlow *flow, u16 move)
{
    return W2U_MoveMakesContact(flow, move, W2U_Attacker()) != 0;
}

/* Pokémon */
/* The holder's current ability: table-driven families (one table, several abilities) find their row by it */
static inline u16 W2U_HolderAbility(BtlServerFlow *flow, u8 monId)
{
    return (u16)GetBattleMonStat(GetBattleMon(flow, monId), BMV_ABILITY);
}

/* Ratios (fixed point, W2U_RATIO_ONE = x1) */
static inline void W2U_MulRatio(s32 ratio) { BattleEventVar_MulValue(VAR_RATIO, ratio); }
/* a x b in fixed point, as the game multiplies ratios */
static inline u32 W2U_RatioMul(u32 a, u32 b) { return a * b >> 12; }

/* The AI's damage simulation runs the damage events too (dozens a turn): handlers that log or count skip it */
static inline b32 W2U_IsSimulating(BtlServerFlow *flow)
{
#if defined(W2U_DECOMP)
    return flow->simulationDepth != 0;
#else
    return *(const u32 *)((const u8 *)flow + W2U_SERVERFLOW_SIMULATION_DEPTH) != 0;
#endif
}

#endif /* W2U_BATTLE_API_H */
