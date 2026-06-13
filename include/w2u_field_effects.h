#ifndef __W2U_FIELD_EFFECTS_H
#define __W2U_FIELD_EFFECTS_H

#include "w2u_abilities.h"

typedef u32 FIELD_EFFECT;

enum W2UFieldEffect : u32 {
    FLDEFF_TERRAIN = 8,
    FLDEFF_DARK_AURA = 9,
    FLDEFF_FAIRY_AURA = 10,
};

extern "C" void W2U_AuraField_ResetBattleState();
extern "C" bool W2U_AuraField_AddEffectOwner(ServerFlow* serverFlow, u32 pokemonSlot, FIELD_EFFECT fieldEffect);
extern "C" bool W2U_AuraField_RemoveEffectOwner(u32 pokemonSlot, FIELD_EFFECT fieldEffect);
extern "C" bool W2U_AuraField_AddAuraBreakMon(u32 pokemonSlot);
extern "C" bool W2U_AuraField_RemoveAuraBreakMon(u32 pokemonSlot);
extern "C" u32 W2U_AuraField_GetAuraBreakMons();

#endif
