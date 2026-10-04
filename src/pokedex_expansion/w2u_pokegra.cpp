#include "personal_data.h"
#include "species_ids.h"
#include "FileSystem.h"
#include "pml/poke_param.h"
#include "pml/poke_party.h"
#include "pml/poke_data.h"
#include "gfl/fs/gfl_archive.h"
#include "w2u_platform.h"

#define EGG_INDEX 722
#define PLACEHOLDER_SPECIES_START 722
#define PLACEHOLDER_SPECIES_END 1023
#define PLACEHOLDER_GRAPHICS_SPECIES SPECIES_TEPIG
#define GEN7_SPECIES_START 722
#define GEN7_SPECIES_END 809
#define GEN8PLUS_SPECIES_START 810
#define GEN8PLUS_SPECIES_END 1023
#define GEN7_BATTLE_ARCHIVE_START 19000
#define GEN7_ICON_ARCHIVE_START 1904
#define GEN8PLUS_STATIC_ASSET_START 1200
#define GEN8PLUS_BATTLE_ARCHIVE_START (GEN8PLUS_STATIC_ASSET_START * 20)
#define GEN8PLUS_ICON_ARCHIVE_START (GEN8PLUS_STATIC_ASSET_START * 2 + 8)
// MEGA_PREVIEW_SLOTS_BEGIN
#define MEGA_PREVIEW_SPECIES_START 1
#define MEGA_PREVIEW_SPECIES_END 96
// MEGA_PREVIEW_SLOTS_END

#define FORM_START 14480
#define RARE_FORM_START 17953
#define REGIONAL_DEX_FILE_INDEX 1290

#define ICON_FORM_START 1456

namespace w2u {
    namespace pokegra {
        extern "C" u32 PML_PersonalGetParamSingle(u32, u32, u32);

        static inline b32 IsGen7Species(u32 Species) {
            return Species >= GEN7_SPECIES_START && Species <= GEN7_SPECIES_END;
        }

        static inline b32 IsGen8PlusSpecies(u32 Species) {
            return Species >= GEN8PLUS_SPECIES_START && Species <= GEN8PLUS_SPECIES_END;
        }

        static inline u32 Gen7BattleIndex(u32 Species) {
            return GEN7_BATTLE_ARCHIVE_START + ((Species - GEN7_SPECIES_START) * 20);
        }

        static inline u32 Gen7IconIndex(u32 Species) {
            return GEN7_ICON_ARCHIVE_START + ((Species - GEN7_SPECIES_START) * 2);
        }

        static inline u32 Gen8PlusBattleIndex(u32 Species) {
            return GEN8PLUS_BATTLE_ARCHIVE_START + ((Species - GEN8PLUS_SPECIES_START) * 20);
        }

        static inline u32 Gen8PlusIconIndex(u32 Species) {
            return GEN8PLUS_ICON_ARCHIVE_START + ((Species - GEN8PLUS_SPECIES_START) * 2);
        }

        static inline b32 IsMegaIconForm(u32 Species, u32 Form) {
            if (!Form) {
                return false;
            }

            switch (Species) {
            case SPECIES_CHARIZARD:
            case SPECIES_MEWTWO:
                return Form <= 2;
            case SPECIES_VENUSAUR:
            case SPECIES_BLASTOISE:
            case SPECIES_BEEDRILL:
            case SPECIES_PIDGEOT:
            case SPECIES_ALAKAZAM:
            case SPECIES_SLOWBRO:
            case SPECIES_GENGAR:
            case SPECIES_KANGASKHAN:
            case SPECIES_PINSIR:
            case SPECIES_GYARADOS:
            case SPECIES_AERODACTYL:
            case SPECIES_AMPHAROS:
            case SPECIES_STEELIX:
            case SPECIES_SCIZOR:
            case SPECIES_HERACROSS:
            case SPECIES_HOUNDOOM:
            case SPECIES_TYRANITAR:
            case SPECIES_SCEPTILE:
            case SPECIES_BLAZIKEN:
            case SPECIES_SWAMPERT:
            case SPECIES_GARDEVOIR:
            case SPECIES_SABLEYE:
            case SPECIES_MAWILE:
            case SPECIES_AGGRON:
            case SPECIES_MEDICHAM:
            case SPECIES_MANECTRIC:
            case SPECIES_SHARPEDO:
            case SPECIES_CAMERUPT:
            case SPECIES_ALTARIA:
            case SPECIES_BANETTE:
            case SPECIES_ABSOL:
            case SPECIES_GLALIE:
            case SPECIES_SALAMENCE:
            case SPECIES_METAGROSS:
            case SPECIES_LATIAS:
            case SPECIES_LATIOS:
            case SPECIES_LOPUNNY:
            case SPECIES_GARCHOMP:
            case SPECIES_LUCARIO:
            case SPECIES_ABOMASNOW:
            case SPECIES_GALLADE:
            case SPECIES_AUDINO:
                return Form == 1;
            default:
                return false;
            }
        }

        static inline u32 DirectFormIconSpecies(u32 Species, u32 Form) {
            u32 formDataOffset = PML_PersonalGetParamSingle(Species, 0, Personal_FormeDataOffs);
            return formDataOffset ? formDataOffset + Form - 1 : 0;
        }

        static inline b32 HasExpandedGraphics(u32 Species) {
            return IsGen7Species(Species) ||
                IsGen8PlusSpecies(Species) ||
                (Species >= MEGA_PREVIEW_SPECIES_START && Species <= MEGA_PREVIEW_SPECIES_END);
        }

        static inline b32 IsPlaceholderSpecies(u32 Species) {
            return Species >= PLACEHOLDER_SPECIES_START && Species <= PLACEHOLDER_SPECIES_END &&
                !HasExpandedGraphics(Species);
        }

        extern "C" void THUMB_BRANCH_SAFESTACK_GetPokemonDataIDBase(u32 ARCID, u32 Species, u32 Form, u32 Gender, b32 isRare, b32 isBackSprite, b32 isEgg, u32 *SpeciesData, u32 *OffsetBase, u32 *pGender, u32 *pValidRarity, u32 *pValidRareForme, b32 linearGraphics) {
            u32 displaySpecies = (!isEgg && IsPlaceholderSpecies(Species)) ? PLACEHOLDER_GRAPHICS_SPECIES : Species;
            if (displaySpecies != Species) {
                Form = 0;
            }

			u32 actual_index = 0;
            // An actual Pokémon; calculate its base index.
            // Gen 7 species overlap the expanded form ranges at the direct index,
            // so keep them in a separate archive range.
            u32 expected_index = IsGen7Species(displaySpecies)
                ? Gen7BattleIndex(displaySpecies)
                : (IsGen8PlusSpecies(displaySpecies) ? Gen8PlusBattleIndex(displaySpecies) : 20 * displaySpecies);

            // There are 9 files for the front, and 9 for the back.
            // Two palettes are shared.
            u32 backsprite_shift = isBackSprite ? 9 : 0;

            if (isEgg) {
                // Egg; check if it is Manaphy first.
                u32 species_is_manaphy = Species == SPECIES_MANAPHY;
                // Calculate the new index.
                expected_index = 20 * (species_is_manaphy + EGG_INDEX);
                actual_index = expected_index;
            }
            else {
                // Index 0 of the sprite set is the linear tiled image.
                // Index 2 of the sprite set is the horizontally tiled image.
                u32 linear_shift = linearGraphics ? 0 : 2;

                // Calculate the new index.
                actual_index = expected_index + backsprite_shift + linear_shift;
            }

            // Handle forms.
            // In our case, we pushed the form data back.
            if (Form) {
                u32 FormCount = PML_PersonalGetParamSingle(displaySpecies, 0, Personal_FormeCount);
                u32 FormSpriteOffset = PML_PersonalGetParamSingle(displaySpecies, 0, Personal_FormeSpritesOffset);
                u32 SpriteForme = PML_PersonalGetParamSingle(displaySpecies, 0, Personal_SpriteForme);

                if (Form < FormCount) {
                    // Form is valid. Check if it is a rare forme.
                    if (SpriteForme) {
                        if (pValidRareForme) {
                            *pValidRareForme = isRare + 2 * (FormSpriteOffset + Form - 1) + RARE_FORM_START;
                        }
                    }
                    else {
                        expected_index = 20 * (FormSpriteOffset + Form - 1) + FORM_START;
                        actual_index = expected_index;
                    }
                }
            }

            // Handle the gender attributes.
            switch (Gender) {
            case 1:
                // In case of female Pokemon, check for alternate gender sprite.
                if (!GFL_ArcSysGetDataLength(ARCID, actual_index + 1)) {
                    // Set to default if ther is none.
                    Gender = 0;
                }
                break;
            case 2:
                // Set genderless Pokemon to default.
                Gender = 0;
                break;
            }

            // Set the pointers for the resultant data.
            if (SpeciesData) {
                *SpeciesData = expected_index;
            }

            if (OffsetBase) {
                *OffsetBase = backsprite_shift;
            }

            if (pGender) {
                *pGender = Gender;
            }

            if (pValidRarity) {
                *pValidRarity = isRare;
            }
        }

        extern "C" s32 THUMB_BRANCH_PokeParty_GetIconIndex(u32 Species, u32 Form, u32 Gender, u32 isEgg) {
            u32 displaySpecies = (!isEgg && IsPlaceholderSpecies(Species)) ? PLACEHOLDER_GRAPHICS_SPECIES : Species;
            if (displaySpecies != Species) {
                Form = 0;
            }

			// An actual Pokémon; calculate its icon index.
            // Gen 7 direct icon indexes overlap the expanded form icon range.
            u32 iconIndex = IsGen7Species(displaySpecies)
                ? Gen7IconIndex(displaySpecies)
                : (IsGen8PlusSpecies(displaySpecies) ? Gen8PlusIconIndex(displaySpecies) : 2 * displaySpecies + 8);
            
            if (isEgg) {
                // Egg; check if it is Manaphy first.
                u32 species_is_manaphy = Species == SPECIES_MANAPHY;
                // Calculate the new index.
                iconIndex = 2 * (species_is_manaphy + EGG_INDEX) + 8;
            }
            else if (Form) {
                // Handle forms.
                // The starting index has been pushed back.
                u32 formCount = PML_PersonalGetParamSingle(Species, 0, Personal_FormeCount);
                u32 formSpriteOffset = PML_PersonalGetParamSingle(Species, 0, Personal_FormeSpritesOffset);
                u32 formSprite = PML_PersonalGetParamSingle(Species, 0, Personal_SpriteForme);
                // Forme is valid.
				if (Form < formCount && !formSprite) {
                    u32 directFormSpecies = DirectFormIconSpecies(Species, Form);
                    u32 directIconIndex = directFormSpecies ? 2 * directFormSpecies + 8 : 0;
                    if (IsMegaIconForm(Species, Form) &&
                        directIconIndex &&
                        GFL_ArcSysGetDataLength(7u, directIconIndex)) {
                        iconIndex = directIconIndex;
                    }
                    else {
                        iconIndex = 2 * (formSpriteOffset + Form - 1) + ICON_FORM_START;
                    }
                }
            }
			
            // Handle the gender attributes.
            switch (Gender) {
            case 1:
                // In case of female Pokemon, check for alternate gender icon.
                if (!GFL_ArcSysGetDataLength(7u, iconIndex + 1)) {
                    // Set to default if ther is none.
                    Gender = 0;
                }
                break;
            case 2:
                // Set genderless Pokemon to default.
                Gender = 0;
                break;
            }
            
            return iconIndex + Gender;
        }

		extern "C" u32 THUMB_BRANCH_PokeParty_GetIconPalette(u32 Species, u32 Form, u32 Gender, u32 IsEgg) {
            u32 displaySpecies = (!IsEgg && IsPlaceholderSpecies(Species)) ? PLACEHOLDER_GRAPHICS_SPECIES : Species;
            if (displaySpecies != Species) {
                Form = 0;
            }

			// The palette index and species match unless there are any special cases
			u32 paletteIndex = displaySpecies;

			if (IsEgg) {
				// Egg; check if it is Manaphy first.
				u32 isManaphy = Species == 490;
				// Calculate the new index.
				paletteIndex = isManaphy + EGG_INDEX;
			}
			else if (Form) {
				// Handle forms.
                // The starting index has been pushed back.
				u32 formSpriteOffset = PML_PersonalGetParamSingle(Species, 0, Personal_FormeSpritesOffset);
				u32 formSprite = PML_PersonalGetParamSingle(Species, 0, Personal_SpriteForme);
				u32 formCount = PML_PersonalGetParamSingle(Species, 0, Personal_FormeCount);
				// Form is valid.
				if (Form < formCount && !formSprite) {
                    u32 directFormSpecies = DirectFormIconSpecies(Species, Form);
                    u32 directIconIndex = directFormSpecies ? 2 * directFormSpecies + 8 : 0;
                    if (IsMegaIconForm(Species, Form) &&
                        directIconIndex &&
                        GFL_ArcSysGetDataLength(7u, directIconIndex)) {
                        paletteIndex = directFormSpecies;
                    }
                    else {
					    paletteIndex = formSpriteOffset + (Form - 1) + (EGG_INDEX + 2);
                    }
				}   
				
			}

			u32 palette = ReadByteFromFile(W2U_PATH_POKEICON_PALETTE_MAP, paletteIndex);
			// Each Pokémon entry has 2 posible palettes, first 4 bits for male and the last 4 bits for female.
			// (this is only used for frillish and jellycent in vanilla but the new icons don't make use of if for now)
			if (Gender) {
				palette = (palette & 0xF0u) >> 4;
			}
			else {
				palette = palette & 0xF;
			}
			return palette;
		}
    }
}
