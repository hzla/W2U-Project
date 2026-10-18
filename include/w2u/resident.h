/* W2U's resident call-site functions: what an engine call site W2U changes calls instead of the engine function it
 * called. Each takes that call's arguments and returns its result type, so the change at the call site is the
 * function's name alone:
 *
 *   injection build   a call-site hook (THUMB_BRANCH_LINK_<module>_0x<address>, megab2w2/mb_resident.cpp) forwards
 *                     to it;
 *   decomp build      the call written into the decomp's source calls it (w2u-local/decomp/resident).
 *
 * Plain C on the engine interface (w2u/battle_api.h), in src/mechanics/resident/; resident in both builds (a battle
 * module can be unloaded while the engine runs). See docs/engine-interface.md, "Call sites". */
#ifndef W2U_RESIDENT_H
#define W2U_RESIDENT_H

#include "w2u/battle_api.h"

W2U_C_BEGIN

/* Propeller Tail / Stalwart (src/mechanics/resident/redirection.c): instead of Battle_IsRedirectBlocked in the
 * redirection checks, Lightning Rod / Storm Drain (CommonMoveTargetChangeToMe) and Follow Me / Rage Powder
 * (HandlerFollowMeBaitTarget). Nonzero: the attacker's move is not redirected to the redirector. */
b32 W2U_RedirectBlocked(BtlServerFlow *flow, u8 attackerId, u8 redirectorId, u16 move);

W2U_C_END

#endif
