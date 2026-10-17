/* W2U engine interface, decomp builds (W2U_DECOMP defined; included by w2u/engine.h before anything else). In a
 * decomp build the decomp's own headers declare the engine, so engine.h leaves out its declarations of the types,
 * the handler-command work and the functions, and keeps only the names W2U owns (events, event variables, handler
 * commands, flags). This file includes the decomp's headers, adds the few names W2U uses that the decomp lacks, and
 * checks that the constants both define agree.
 *
 * Checked against the public pokebw2 decomp (fuddlesworth/pokebw2). The names hzla's cleanup gives functions that the
 * public decomp still calls by placeholder (func_ov167_...) come from w2u/decomp_names.h, which
 * w2u-local/decomp/pilot/gen_decomp_names.py writes for the decomp being built (by address, from both symbol lists).
 * See docs/engine-interface.md. */
#ifndef W2U_ENGINE_DECOMP_H
#define W2U_ENGINE_DECOMP_H

#include "types.h"
#include "battle/btl_ability.h"
#include "battle/btl_action.h"
#include "battle/btl_action_order.h"
#include "battle/btl_calc.h"
#include "battle/btl_event.h"
#include "battle/btl_field.h"
#include "battle/btl_handler.h"
#include "battle/btl_handler_work.h"
#include "battle/btl_main.h"
#include "battle/btl_pokeparam.h"
#include "battle/btl_server_cmd.h"
#include "battle/btl_server_flow.h"
#include "battle/handler_common.h"
#include "battle/side_handlers.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
#include "pml/poke_party.h"
#include "pml/waza.h"

typedef BOOL b32;                           /* W2U's 32-bit boolean */

#include "w2u/decomp_names.h"

/* Fields hzla's cleanup names that the public decomp hasn't named yet */
#define simulationDepth unk774              /* BtlServerFlow: nonzero while the AI simulates */

/* W2U's names the decomp doesn't have (yet) */
#define BTL_ACTION_FIGHT 1                  /* BattleAction.bits.action: a move */
#ifndef CONDITION_CHOICE_LOCK
#define CONDITION_CHOICE_LOCK 0x1B          /* locked into one move (the Choice items) */
#endif

/* Constants W2U names that the decomp defines too: engine.h leaves them out here, so their values must agree */
#define W2U_DECOMP_CHECK(name, cond) typedef char w2u_decomp_check_##name[(cond) ? 1 : -1]
W2U_DECOMP_CHECK(paralysis, CONDITION_PARALYSIS == 1);
W2U_DECOMP_CHECK(poison, CONDITION_POISON == 5);
W2U_DECOMP_CHECK(confusion, CONDITION_CONFUSION == 6);
W2U_DECOMP_CHECK(yawn, CONDITION_YAWN == 14);
W2U_DECOMP_CHECK(gastro_acid, CONDITION_GASTRO_ACID == 0x10);
W2U_DECOMP_CHECK(perish_song, CONDITION_PERISH_SONG == 20);
W2U_DECOMP_CHECK(mean_look, CONDITION_MEAN_LOOK == 0x16);
W2U_DECOMP_CHECK(target_adjacent_foes, MOVE_TARGET_ADJACENT_FOES == 5);
W2U_DECOMP_CHECK(target_random_foe, MOVE_TARGET_RANDOM_FOE == 9);
W2U_DECOMP_CHECK(target_user_side, MOVE_TARGET_USER_SIDE == 12);
W2U_DECOMP_CHECK(category_physical, MOVE_CATEGORY_PHYSICAL == 1);
W2U_DECOMP_CHECK(category_special, MOVE_CATEGORY_SPECIAL == 2);
W2U_DECOMP_CHECK(param_category, MOVE_PARAM_CATEGORY == 2);
W2U_DECOMP_CHECK(param_target, MOVE_PARAM_TARGET == 0x1B);
W2U_DECOMP_CHECK(style_double, BTL_STYLE_DOUBLE == 1);
W2U_DECOMP_CHECK(is_egg, PKM_PARAM_IS_EGG == 0x4c);

#endif /* W2U_ENGINE_DECOMP_H */
