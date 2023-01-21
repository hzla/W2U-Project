#include "swan/swantypes.h"

u32 AbilZenMode(u32 a1, u32 a2, u32 a3) {
  u32 BattleMon; // r4
  u32 *result; // r0
  u32 BattleMonStat; // r5
  u32 v8; // r5
  char *v9; // r0
  char *v10; // r4
  u16 v11; // r2

  BattleMon = GetBattleMon(a2, a3);
  result = GetBattleMonSpecies(BattleMon);
  if (result == 555) {
    BattleMonStat = GetBattleMonStat(BattleMon, 13);
    v8 = BattleMonStat <= DivideMaxHp(BattleMon, 2u);
    result = GetBattleMonStat(BattleMon, 19);
    if (v8 != result) {
      v9 = sub_21AC424(a2, 57, a3);
      v10 = v9;
      *v9 |= 0x800000u;
      v9[4] = a3;
      v11 = 185;
      v9[5] = v8;
      if (!v8) {
        v11 = 186;
      }
      sub_21AC3B8(v9 + 4, 1u, v11);
      return sub_21AC448(a2, v10);
    }
  }
  return result;
}