/* The resident call sites' battle state, cleared (w2u/resident.h): the injection build at battle exit; a decomp
 * build's overlay 167 starts every battle with it clear, since the state is zero when empty. */
#include "w2u/resident.h"

void W2U_Resident_ResetBattleState(void)
{
    W2U_Resident_ResetPendingMoves();
    W2U_Resident_ResetHandlerEffects();
    W2U_Resident_ResetWeather();
    W2U_Resident_ResetMoveCategories();
    W2U_Resident_ResetParentalBond();
    W2U_Resident_ResetSimpleDamage();
    W2U_Resident_ResetEffectiveness();
    W2U_StrongWeather_Reset();
}
