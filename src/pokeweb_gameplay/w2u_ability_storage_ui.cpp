// PC box panel half of the ability storage (w2u_ability_storage.cpp): overlay 255, so it lives in the
// overlay-scoped UI companion. The panel keeps the ability in a display byte (+0xE, filled at 0x21BF0CA, named at
// 0x21CE65C); it shows one Pokemon at a time, so a one-entry cache carries the full ID. White 2 only.
#include "swantypes.h"

#if !defined(W2U_TARGET_B2)

extern "C" u32 PML_PkmGetParam(void* pkm, u32 field, void* extra);

namespace {
typedef void (*RegisterAbilityNameFn)(void* wordset, u32 index, u32 ability);
const RegisterAbilityNameFn RegisterAbilityName = (RegisterAbilityNameFn)0x0202452Du;   // WordSet_RegisterAbilityName
u32 sPanelAbility;   // the full ID of the Pokemon whose low byte is in the display byte
} // namespace

// PC box panel (ov255): its display struct keeps the ability in a byte (+0xE)
extern "C" u32 THUMB_BRANCH_LINK_255_0x21BF0CA(void* pkm, u32 field, void* extra)
{
    u32 id = PML_PkmGetParam(pkm, field, extra);
    sPanelAbility = id;
    return id & 0xFF;
}

extern "C" void THUMB_BRANCH_LINK_255_0x21CE65C(void* wordset, u32 index, u32 storageByte)
{
    u32 low = storageByte & 0xFF;
    RegisterAbilityName(wordset, index, (sPanelAbility & 0xFF) == low ? sPanelAbility : low);
}

#endif // !W2U_TARGET_B2
