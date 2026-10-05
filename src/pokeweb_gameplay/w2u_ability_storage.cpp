// Ability IDs above 255 (ported from MegaB2W2's AbilityStorage.cpp, adapted to W2U's direct IDs).
//
// Battle code keeps abilities as u16; the stored copies are one byte: species data (personal +0x18 / +0x19 / +0x1A)
// and each Pokemon's data (PF_Ability, box data +0x15). IDs 0-255 stay exactly as before. Above 255:
//   species data   the ability byte holds the low 8 bits; bits 14-15 of the matching wild item word (personal
//                  +0x0C / +0x0E / +0x10; item IDs use bits 0-13) hold bits 8-9. Pokeweb's packing
//                  (personalAbilityPacking.ts), so Pokeweb shows and edits these abilities; written by
//                  tools/mkdata (format personal); IDs up to 1023
//   Pokemon data   PF_Ability holds the low 8 bits, byte 0x42 (block B +0x1A; vanilla uses only bit 0 hidden
//                  ability and bit 1 N's Pokemon) bits 6-7 hold bits 8-9; IDs up to 1023. Saves made before this
//                  have bits 6-7 clear, which reads as the plain byte.
// Decoded / encoded at the boundary so every caller sees real IDs:
//   PML_PersonalGetParam   re-implemented 1:1 (its 48-case jump table, ARM9 0x20202D8), abilities decoded
//   PML_PkmGetParamCore    both calls (PML_PkmGetParam 0x201CDC6, the party getter 0x201DEEE): PF_Ability decoded
//   PML_PkmSetParamCore    both calls (PML_PkmSetParam 0x201CD82, PokeParty_SetParamCore 0x201E452): encoded
//   PC box panel (ov255)   w2u_ability_storage_ui.cpp (White2UpgradeUI.dll)
// White 2 only (the addresses are White 2's).
#include "swantypes.h"

#if !defined(W2U_TARGET_B2)

extern "C" {
u8* PML_PkmGetParamBlockCore(void* pkm, u32 personality, u32 block);   // block 0-3 (A-D), decrypted
u32 PML_PkmGetParamCore(void* pkm, u32 field, void* extra);
u32 PML_PkmSetParamCore(void* pkm, u32 field, u32 value);
u32 PML_PkmGetParam(void* pkm, u32 field, void* extra);
}

namespace {

const u32 PF_ABILITY = 0x0A;
const u32 PERSONAL_ABILITY1 = 0x1A;
const u32 PERSONAL_ABILITY2 = 0x1B;
const u32 PERSONAL_ABILITY_HIDDEN = 0x1C;
const u32 WILD_ITEM_MASK = 0x3FFF;
const u32 PKM_BLOCK_B = 1;
const u32 PKM_ABILITY_HIGH = 0x1A;     // byte 0x42 of the Pokemon data
const u32 PKM_ABILITY_HIGH_SHIFT = 6;  // bits 6-7

inline u32 U8(const u8* p, u32 o) { return p[o]; }
inline u32 U16(const u8* p, u32 o) { return *(const u16*)(p + o); }
inline u32 U32(const u8* p, u32 o) { return *(const u32*)(p + o); }

u32 PersonalAbility(const u8* p, u32 slot)
{
    return U8(p, 0x18 + slot) | (((U16(p, 0x0C + 2 * slot) >> 14) & 3u) << 8);
}

u8* AbilityHigh(void* pkm)
{
    return PML_PkmGetParamBlockCore(pkm, *(u32*)pkm, PKM_BLOCK_B) + PKM_ABILITY_HIGH;
}

u32 GetAbility(void* pkm, u32 storageByte)
{
    return (storageByte & 0xFF) | ((u32)(*AbilityHigh(pkm) >> PKM_ABILITY_HIGH_SHIFT) << 8);
}

u32 SetAbility(void* pkm, u32 id)   // -> the PF_Ability byte; sets the high bits
{
    u8* high = AbilityHigh(pkm);
    *high = (u8)((*high & ((1u << PKM_ABILITY_HIGH_SHIFT) - 1)) | (((id >> 8) & 3u) << PKM_ABILITY_HIGH_SHIFT));
    return id & 0xFF;
}

} // namespace

// PML_PersonalGetParam(personal, param), 1:1 with the retail jump table. No compiler jump table: Thumb switch tables
// call __gnu_thumb1_case_uqi, a libgcc helper the game does not have.
extern "C" __attribute__((optimize("no-jump-tables"))) u32 THUMB_BRANCH_PML_PersonalGetParam(const u8* p, u32 param)
{
    if (param <= 0x08) return U8(p, param);                              // base stats, types, capture rate
    switch (param) {
    case 0x09: return U16(p, 0x22);                                      // base experience
    case 0x0A: case 0x0B: case 0x0C: case 0x0D: case 0x0E: case 0x0F:
        return (U16(p, 0x0A) >> (2 * (param - 0x0A))) & 3;               // EV yields, 2 bits each
    case 0x10: return (U16(p, 0x0A) >> 12) & 1;
    case 0x11: return U16(p, 0x0C) & WILD_ITEM_MASK;                     // wild items (bits 14-15: abilities)
    case 0x12: return U16(p, 0x0E) & WILD_ITEM_MASK;
    case 0x13: return U16(p, 0x10) & WILD_ITEM_MASK;
    case PERSONAL_ABILITY1: return PersonalAbility(p, 0);
    case PERSONAL_ABILITY2: return PersonalAbility(p, 1);
    case PERSONAL_ABILITY_HIDDEN: return PersonalAbility(p, 2);
    case 0x1D: return U8(p, 0x1B);
    case 0x1E: return U16(p, 0x1C);                                      // form data / sprite offsets
    case 0x1F: return U16(p, 0x1E);
    case 0x20: return U8(p, 0x20);                                       // form count
    case 0x21: return U8(p, 0x21) & 0x3F;                                // color
    case 0x22: return (U8(p, 0x21) >> 6) & 1;
    case 0x23: return (U8(p, 0x21) >> 7) & 1;
    case 0x24: return U8(p, 0x09);                                       // evolution stage
    case 0x25: return U16(p, 0x24);                                      // height
    case 0x26: return U16(p, 0x26);                                      // weight
    default:
        if (param >= 0x14 && param <= 0x19) return U8(p, 0x12 + (param - 0x14));     // gender .. egg groups
        if (param >= 0x27 && param <= 0x2F) return U32(p, 0x28 + 4 * (param - 0x27)); // TM / tutor bits
        return 0;
    }
}

extern "C" u32 THUMB_BRANCH_LINK_ARM9_0x201CDC6(void* pkm, u32 field, void* extra)
{
    u32 value = PML_PkmGetParamCore(pkm, field, extra);
    return field == PF_ABILITY ? GetAbility(pkm, value) : value;
}

extern "C" u32 THUMB_BRANCH_LINK_ARM9_0x201DEEE(void* pkm, u32 field, void* extra)
{
    u32 value = PML_PkmGetParamCore(pkm, field, extra);
    return field == PF_ABILITY ? GetAbility(pkm, value) : value;
}

extern "C" u32 THUMB_BRANCH_LINK_ARM9_0x201CD82(void* pkm, u32 field, u32 value)
{
    return PML_PkmSetParamCore(pkm, field, field == PF_ABILITY ? SetAbility(pkm, value) : value);
}

extern "C" u32 THUMB_BRANCH_LINK_ARM9_0x201E452(void* pkm, u32 field, u32 value)
{
    return PML_PkmSetParamCore(pkm, field, field == PF_ABILITY ? SetAbility(pkm, value) : value);
}

#endif // !W2U_TARGET_B2
