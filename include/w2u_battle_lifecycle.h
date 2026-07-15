#ifndef __W2U_BATTLE_LIFECYCLE_H
#define __W2U_BATTLE_LIFECYCLE_H

#include "swantypes.h"

C_DECL_BEGIN

// Called once from the battle viewer teardown path. Custom battle state must
// not use heap-address changes as a proxy for a new battle because consecutive
// battles can reuse the same ServerFlow/MainModule/PokeCon allocations.
void W2U_BattleState_OnBattleExit();

C_DECL_END

#endif
