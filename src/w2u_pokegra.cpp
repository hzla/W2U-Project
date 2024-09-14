#include "Personal.h"
#include "Species.h"
#include "pml/poke_param.h"
#include "pml/poke_party.h"
#include "pml/poke_data.h"
#include "gfl/fs/gfl_archive.h"

#define FORM_START 14460
#define RARE_FORM_START 17953
#define REGIONAL_DEX_FILE_INDEX 826

namespace w2u {
    namespace pokegra {
        extern "C" u32 PML_PersonalGetParamSingle(u32, u32, u32);
        extern "C" void THUMB_BRANCH_SAFESTACK_GetPokemonDataIDBase(int ARCID, int Species, int Form, int Sex, b32 isRare, b32 isBackSprite, int isEgg, u32 *SpeciesData, u32 *OffsetBase, u32 *pGender, u32 *pValidRarity, u32 *pValidRareForme, b32 linearGraphics) {
            u32 actual_index = 0;
            
            // There are 9 files for the front, and 9 for the back.
            // Two palettes are shared.
            u32 backsprite_shift = isBackSprite ? 9 : 0;
            
            if (isEgg) {
                // Egg; check if it is Manaphy first.
                u32 species_is_manaphy = Species == 490;
                // Calculate the new index.
                actual_index = 20 * (species_is_manaphy + 683);
            } else {
                // An actual Pokémon; calculate its base index.
                // Should be, by default, 20 * Species.
                u32 expected_species_index = 20 * Species;

                // Index 0 of the sprite set is the linear tiled image.
                // Index 2 of the sprite set is the horizontally tiled image.
                u32 linear_shift = linearGraphics ? 2 : 0;

                // Calculate the new index.
                actual_index = expected_species_index + backsprite_shift + linear_shift;
            }

            // Handle forms.
            // In our case, we pushed the form data back.
            if (Form) {
                u32 FormCount = PML_PersonalGetParamSingle(Species, 0, Personal_FormeCount);
                u32 FormSpriteOffset = PML_PersonalGetParamSingle(Species, 0, Personal_FormeSpritesOffset);
                u32 SpriteForme = PML_PersonalGetParamSingle(Species, 0, Personal_SpriteForme);
                
                if (Form < FormCount) {
                    // Form is valid. Check if it is a rare forme.
                    if (SpriteForme && pValidRareForme) {
                        u32 rare_form_index = (FormSpriteOffset + Form - 1);
                        *pValidRareForme = isRare + 2 * rare_form_index + RARE_FORM_START;
                    } else {
                        actual_index = 20 * (FormSpriteOffset + Form - 1) + FORM_START;
                    }
                }
            }

            // Handle the gender attributes.
            if (Species <= SPECIES_AND_EGG_CNT || isEgg) {
                Sex &= !GFL_ArcSysGetDataLength(ARCID, actual_index + 1);
            }

            // Set the pointers for the resultant data.
            if (SpeciesData) {
                *SpeciesData = actual_index;
            }

            if (OffsetBase) {
                *OffsetBase = backsprite_shift;
            }

            if (pGender) {
                *pGender = 0;
            }

            if (pValidRarity) {
                *pValidRarity = 0;
            }
        }

        extern "C" s32 THUMB_BRANCH_PokeParty_GetIconIndex(s32 Species, s32 Form, s32 Gender, s32 Egg) {
            // TODO: Handle forms.
            u32 Index = 8 + 2 * Species;

            // if (Species >= 650) {
            //     // Rebase on Chespin's sprite (1378)
            //     Index = 2 * (Species - 650) + FORM_START;
            // }

            // if (Egg) {
            //     Index = (((Species == 490) + 755) << 2) + 8;
            // }

            // if ((Gender && Gender > 1) || !GFL_ArcSysGetDataLength(7u, Index + 1)) {
            //     // Empty file or invalid file.
            //     Gender = 0;
            // }
            Gender = 0;
            return Index + Gender;
        }
    }
}