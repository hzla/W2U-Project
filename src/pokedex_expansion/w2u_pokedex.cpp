#include "swan/swantypes.h"
#include "gfl/fs/gfl_archive.h"
#include "species_ids.h"
#include "personal_data.h"
#include "FileSystem.h"
#include "w2u_platform.h"

#define REGIONAL_DEX_FILE_INDEX 1290

#define POKE_FORM_LIST_SIZE 0xB7
#define POKEDEX_MAGIC 0xBEEFCAFE
#define POKEDEX_LEGACY_FLAG_BYTES 84
#define POKEDEX_LEGACY_SPECIES_MAX 672
#define POKEDEX_EXTENSION_SPECIES_MIN (POKEDEX_LEGACY_SPECIES_MAX + 1)
#define POKEDEX_EXTENSION_FLAG_BYTES 44
#define POKEDEX_EXTENSION_SLOT_COUNT 9
#define POKEDEX_FORM_FLAG_BYTES 9
#define POKEDEX_FORM_FLAG_BITS (POKEDEX_FORM_FLAG_BYTES * 8)
#define POKEDEX_TEXT_VERSION_BYTES 432
#define POKEDEX_NATIONAL_OBTAINED_FLAG 0x00000001
#define POKEDEX_NATIONAL_MODE_FLAG 0x00000800
#define SPINDA_SPECIES 327
#define POKEMON_PARADATA_OFFSET 8
#define POKEMON_PARADATA_SIZE 128
#define POKEMON_PARAM_BLOCK_SIZE 32
#define POKEMON_FAST_MODE_FLAG 0x2
#define POKEMON_BAD_EGG_FLAG 0x4

#ifndef W2U_DISABLE_DEX_REGISTRATION_ON_OBTAIN
#define W2U_DISABLE_DEX_REGISTRATION_ON_OBTAIN 0
#endif

namespace w2u {
    namespace pml {

        struct Poke_form
        {
            u16 species;
            u16 form_count;
        };

        struct PokedexSave {
            u32 zukanMagic;
            u32 flags;
            u8 caught[POKEDEX_LEGACY_FLAG_BYTES];
            u8 seen[4][POKEDEX_LEGACY_FLAG_BYTES];
            u8 seenMale[POKEDEX_LEGACY_FLAG_BYTES];
            u8 seenFemale[POKEDEX_LEGACY_FLAG_BYTES];
            u8 shinyMale[POKEDEX_LEGACY_FLAG_BYTES];
            u8 shinyFemale[POKEDEX_LEGACY_FLAG_BYTES];
            u8 formFlags[2][POKEDEX_FORM_FLAG_BYTES];
            u8 forms[POKEDEX_FORM_FLAG_BYTES];
            u8 shinyForms[POKEDEX_FORM_FLAG_BYTES];
            u8 textVersionUp[POKEDEX_TEXT_VERSION_BYTES];
            u32 pachiRandom;
        };

        typedef void PokemonParam;

        struct PokemonDexSnapshot {
            u32 species;
            u32 form;
            u32 sex;
            u32 shiny;
            u32 egg;
            u32 personalRnd;
        };

        extern "C" b32 PokeDex_IsCaught(void *pDexAddress, u16 species);
        extern "C" b32 PokeDex_IsSeen(void *pDexAddress, u16 species);
        extern "C" b32 PML_PkmIsRegionalDexExclude(u32 species);
        extern "C" b32 PML_PkmIsNationalDexExclude(u32 species);
        extern "C" u16 *PML_PersonalLoadRegionalDexTable(HeapID heapId, u16 *regionalDexCount);
        extern "C" s16 getIndexNumOfPkmForm(u16 species);
		extern "C" s32 getIndexPokemonWithForms(u32 species);
		extern "C" PersonalData* PML_PersonalLoad(u16 species, u16 form, u16 heapId);
		extern "C" u32 PML_PersonalGetParam(PersonalData* personal, PersonalField field);
		extern "C" void PML_PersonalFree(PersonalData* personal);

        extern ArcTool **g_PMLPersonalArcBW2 = (ArcTool **)W2U_ADDR_PERSONAL_ARC_BW2;

        static inline void ClearMemory(void *data, u32 size) {
            u8 *bytes = (u8 *)data;
            for (u32 i = 0; i < size; ++i) {
                bytes[i] = 0;
            }
        }

        static inline b32 IsValidDexSpecies(u32 species) {
            return species && species <= SPECIES_CNT;
        }

        static inline u16 ReadU16(const u8 *data, u32 offset) {
            return data[offset] | (data[offset + 1] << 8);
        }

        static inline u32 ReadU32(const u8 *data, u32 offset) {
            return ReadU16(data, offset) | (ReadU16(data, offset + 2) << 16);
        }

        static inline u32 GetPokemonParamBlockOffset(u32 personalRnd, u32 block) {
            static const u8 offsets[32][4] = {
                { 0, 32, 64, 96 },
                { 0, 32, 96, 64 },
                { 0, 64, 32, 96 },
                { 0, 96, 32, 64 },
                { 0, 64, 96, 32 },
                { 0, 96, 64, 32 },
                { 32, 0, 64, 96 },
                { 32, 0, 96, 64 },
                { 64, 0, 32, 96 },
                { 96, 0, 32, 64 },
                { 64, 0, 96, 32 },
                { 96, 0, 64, 32 },
                { 32, 64, 0, 96 },
                { 32, 96, 0, 64 },
                { 64, 32, 0, 96 },
                { 96, 32, 0, 64 },
                { 64, 96, 0, 32 },
                { 96, 64, 0, 32 },
                { 32, 64, 96, 0 },
                { 32, 96, 64, 0 },
                { 64, 32, 96, 0 },
                { 96, 32, 64, 0 },
                { 64, 96, 32, 0 },
                { 96, 64, 32, 0 },
                { 0, 32, 64, 96 },
                { 0, 32, 96, 64 },
                { 0, 64, 32, 96 },
                { 0, 96, 32, 64 },
                { 0, 64, 96, 32 },
                { 0, 96, 64, 32 },
                { 32, 0, 64, 96 },
                { 32, 0, 96, 64 },
            };
            return offsets[(personalRnd & 0x0003E000) >> 13][block];
        }

        static inline void CopyPokemonParadata(PokemonParam *pokemon, u8 *out) {
            const u8 *raw = (const u8 *)pokemon;
            u32 personalRnd = ReadU32(raw, 0);
            u16 flags = ReadU16(raw, 4);
            u16 checksum = ReadU16(raw, 6);
            const u8 *paradata = raw + POKEMON_PARADATA_OFFSET;

            for (u32 i = 0; i < POKEMON_PARADATA_SIZE; ++i) {
                out[i] = paradata[i];
            }

            if (flags & POKEMON_FAST_MODE_FLAG) {
                (void)personalRnd;
                return;
            }

            u32 code = checksum;
            for (u32 offset = 0; offset < POKEMON_PARADATA_SIZE; offset += 2) {
                code = (code * 1103515245) + 24691;
                u16 mask = (code >> 16) & 0xFFFF;
                u16 value = ReadU16(out, offset) ^ mask;
                out[offset] = value & 0xFF;
                out[offset + 1] = value >> 8;
            }
        }

        static inline PokemonDexSnapshot ReadPokemonDexSnapshot(PokemonParam *pokemon) {
            u8 paradata[POKEMON_PARADATA_SIZE];
            const u8 *raw = (const u8 *)pokemon;
            u32 personalRnd = ReadU32(raw, 0);
            u16 flags = ReadU16(raw, 4);
            CopyPokemonParadata(pokemon, paradata);

            u32 block1 = GetPokemonParamBlockOffset(personalRnd, 0);
            u32 block2 = GetPokemonParamBlockOffset(personalRnd, 1);
            u32 packedIvEgg = ReadU32(paradata, block2 + 16);
            u8 packedSexForm = paradata[block2 + 24];
            u32 trainerId = ReadU32(paradata, block1 + 4);
            u32 shinyValue = ((trainerId >> 16) ^ (trainerId & 0xFFFF)
                ^ (personalRnd >> 16) ^ (personalRnd & 0xFFFF));

            PokemonDexSnapshot snapshot;
            snapshot.species = ReadU16(paradata, block1);
            snapshot.form = (packedSexForm >> 3) & 0x1F;
            snapshot.sex = (packedSexForm >> 1) & 0x3;
            snapshot.shiny = shinyValue < 8;
            snapshot.egg = ((flags & POKEMON_BAD_EGG_FLAG) != 0) || ((packedIvEgg >> 30) & 1);
            snapshot.personalRnd = personalRnd;
            return snapshot;
        }

        static inline u32 GetExtensionSlot(const PokedexSave *pokedex, const u8 *legacyArray) {
            if (legacyArray == pokedex->caught) {
                return 0;
            }
            for (u32 i = 0; i < 4; ++i) {
                if (legacyArray == pokedex->seen[i]) {
                    return 1 + i;
                }
            }
            if (legacyArray == pokedex->seenMale) {
                return 5;
            }
            if (legacyArray == pokedex->seenFemale) {
                return 6;
            }
            if (legacyArray == pokedex->shinyMale) {
                return 7;
            }
            if (legacyArray == pokedex->shinyFemale) {
                return 8;
            }
            return POKEDEX_EXTENSION_SLOT_COUNT;
        }

        static inline u8 *GetFlagArray(PokedexSave *pokedex, u8 *flagArray, u32 species, u32 *bit) {
            if (species && species <= POKEDEX_LEGACY_SPECIES_MAX) {
                *bit = species - 1;
                return flagArray;
            }
            if (species >= POKEDEX_EXTENSION_SPECIES_MIN && species <= SPECIES_CNT) {
                u32 slot = GetExtensionSlot(pokedex, flagArray);
                if (slot < POKEDEX_EXTENSION_SLOT_COUNT) {
                    *bit = species - POKEDEX_EXTENSION_SPECIES_MIN;
                    return pokedex->textVersionUp + (slot * POKEDEX_EXTENSION_FLAG_BYTES);
                }
            }
            *bit = 0;
            return 0;
        }

        static inline const u8 *GetFlagArrayConst(const PokedexSave *pokedex, const u8 *flagArray, u32 species, u32 *bit) {
            if (species && species <= POKEDEX_LEGACY_SPECIES_MAX) {
                *bit = species - 1;
                return flagArray;
            }
            if (species >= POKEDEX_EXTENSION_SPECIES_MIN && species <= SPECIES_CNT) {
                u32 slot = GetExtensionSlot(pokedex, flagArray);
                if (slot < POKEDEX_EXTENSION_SLOT_COUNT) {
                    *bit = species - POKEDEX_EXTENSION_SPECIES_MIN;
                    return pokedex->textVersionUp + (slot * POKEDEX_EXTENSION_FLAG_BYTES);
                }
            }
            *bit = 0;
            return 0;
        }

        static inline void SetSpeciesBit(u8 *array, u32 bit) {
            if (!array) {
                return;
            }
            array[bit >> 3] |= 1 << (bit & 7);
        }

        static inline void ResetSpeciesBit(u8 *array, u32 bit) {
            if (!array) {
                return;
            }
            array[bit >> 3] &= (1 << (bit & 7)) ^ 0xFF;
        }

        static inline b32 CheckSpeciesBit(const u8 *array, u32 bit) {
            if (!array) {
                return 0;
            }
            return (array[bit >> 3] & (1 << (bit & 7))) != 0;
        }

        static inline void SetDexBit(PokedexSave *pokedex, u8 *flagArray, u32 species) {
            u32 bit;
            u8 *array = GetFlagArray(pokedex, flagArray, species, &bit);
            SetSpeciesBit(array, bit);
        }

        static inline void ResetDexBit(PokedexSave *pokedex, u8 *flagArray, u32 species) {
            u32 bit;
            u8 *array = GetFlagArray(pokedex, flagArray, species, &bit);
            ResetSpeciesBit(array, bit);
        }

        static inline b32 CheckDexBit(const PokedexSave *pokedex, const u8 *flagArray, u32 species) {
            u32 bit;
            const u8 *array = GetFlagArrayConst(pokedex, flagArray, species, &bit);
            return CheckSpeciesBit(array, bit);
        }

        static inline void ClearDrawSexFlags(PokedexSave *pokedex, u32 species) {
            ResetDexBit(pokedex, pokedex->seenMale, species);
            ResetDexBit(pokedex, pokedex->seenFemale, species);
            ResetDexBit(pokedex, pokedex->shinyMale, species);
            ResetDexBit(pokedex, pokedex->shinyFemale, species);
        }

        static inline void SetDrawSexFlag(PokedexSave *pokedex, u32 species, u32 sex, u32 shiny) {
            if (sex == 1) {
                if (shiny) {
                    SetDexBit(pokedex, pokedex->shinyFemale, species);
                }
                else {
                    SetDexBit(pokedex, pokedex->seenFemale, species);
                }
            }
            else if (shiny) {
                SetDexBit(pokedex, pokedex->shinyMale, species);
            }
            else {
                SetDexBit(pokedex, pokedex->seenMale, species);
            }
        }

        static inline void SetSeenSexFlag(PokedexSave *pokedex, u32 species, u32 sex, u32 shiny) {
            u32 slot = shiny ? (sex == 1 ? 3 : 2) : (sex == 1 ? 1 : 0);
            SetDexBit(pokedex, pokedex->seen[slot], species);
        }

        static inline void SetDrawData(PokedexSave *pokedex, u32 species, u32 sex, u32 shiny, u32 form) {
            Poke_form pokemonFormList[POKE_FORM_LIST_SIZE];
            if (ReadDataFromFile(W2U_PATH_POKE_FORM_LIST, POKE_FORM_LIST_SIZE * sizeof(Poke_form), (u8*)pokemonFormList)) {
                s32 formIdx = 0;
                for (u32 formListIdx = 0; formListIdx < POKE_FORM_LIST_SIZE && pokemonFormList[formListIdx].species; ++formListIdx) {
                    Poke_form* pokeForm = &pokemonFormList[formListIdx];
                    if (species == pokeForm->species) {
                        u32 formCount = pokeForm->form_count;
                        for (u32 currentForm = 0; currentForm < formCount; ++currentForm) {
                            u32 flagIdx = formIdx + currentForm;
                            if (flagIdx < POKEDEX_FORM_FLAG_BITS) {
                                u32 formGroup = flagIdx >> 3;
                                u8 formMask = (u8)(1 << (flagIdx & 7));
                                formMask = ~formMask;
                                pokedex->forms[formGroup] &= formMask;
                                pokedex->shinyForms[formGroup] &= formMask;
                            }
                        }
                        if (form >= formCount) {
                            form = 0;
                        }
                        formIdx += form;
                        if ((u32)formIdx < POKEDEX_FORM_FLAG_BITS) {
                            if (shiny) {
                                pokedex->shinyForms[formIdx >> 3] |= 1 << (formIdx & 7);
                            }
                            else {
                                pokedex->forms[formIdx >> 3] |= 1 << (formIdx & 7);
                            }
                        }
                        break;
                    }
                    formIdx += pokeForm->form_count;
                }
            }

            ClearDrawSexFlags(pokedex, species);
            SetDrawSexFlag(pokedex, species, sex, shiny);
        }

        extern "C" u32 THUMB_BRANCH_getSizeofPokedexData() {
            return sizeof(PokedexSave);
        }

        extern "C" void THUMB_BRANCH_initPokedex(PokedexSave *pokedex) {
            ClearMemory(pokedex, sizeof(PokedexSave));
            pokedex->zukanMagic = POKEDEX_MAGIC;
            pokedex->flags = POKEDEX_NATIONAL_OBTAINED_FLAG | POKEDEX_NATIONAL_MODE_FLAG;
        }

        extern "C" void THUMB_BRANCH_PokeDex_SetNationalObtained(PokedexSave *pokedex) {
            if (pokedex) {
                pokedex->flags |= POKEDEX_NATIONAL_OBTAINED_FLAG | POKEDEX_NATIONAL_MODE_FLAG;
            }
        }

        extern "C" b32 THUMB_BRANCH_PokeDex_IsNationalObtained(PokedexSave *pokedex) {
            if (pokedex) {
                pokedex->flags |= POKEDEX_NATIONAL_OBTAINED_FLAG | POKEDEX_NATIONAL_MODE_FLAG;
            }
            return 1;
        }

        extern "C" bool THUMB_BRANCH_PML_PkmIsBadMonsNo(u32 species) {
            // A "Bad" Pokemon is a Pokemon that's outside of the range (or 0).
            return !species || species > SPECIES_CNT;
        }

        extern "C" b32 THUMB_BRANCH_PokeDex_IsCaught(PokedexSave *pokedex, u16 species) {
            if (!IsValidDexSpecies(species)) {
                return 0;
            }
            return CheckDexBit(pokedex, pokedex->caught, species);
        }

        extern "C" b32 THUMB_BRANCH_PokeDex_IsSeen(PokedexSave *pokedex, u16 species) {
            if (!IsValidDexSpecies(species)) {
                return 0;
            }
            for (u32 i = 0; i < 4; ++i) {
                if (CheckDexBit(pokedex, pokedex->seen[i], species)) {
                    return 1;
                }
            }
            return 0;
        }

        extern "C" u16 *THUMB_BRANCH_PML_PersonalLoadRegionalDexTable(HeapID heapId, u16 *regionalDexCount) {
            u16 v3 = 0;
            u32 fileLength;
            u16 *result = (u16 *)GFL_ArcToolReadHeapNewLZGetLen(*g_PMLPersonalArcBW2, REGIONAL_DEX_FILE_INDEX, 0, heapId, &fileLength);
            u32 v5 = (fileLength << 15 >> 16);
            if (regionalDexCount) {
                for (u32 i = 0; i < v5; i++) {
                    if (*(result + i) != 999) {
                        ++v3;
                    }
                }
                *regionalDexCount = v3;
            }
            return result;
        }

        extern "C" u16 THUMB_BRANCH_PokeDex_GetCaughtNoNational(void *pDexAddress) {
            u16 caught_number = 0;
            for (s32 i = 1; i <= SPECIES_CNT; ++i) {
                caught_number += PokeDex_IsCaught(pDexAddress, i);
            }
            return caught_number;
        }

        extern "C" u32 THUMB_BRANCH_PokeDex_GetSeenNoUnovaPermissive(void *pDexAddress, HeapID heapId) {
            u32 v3 = 0;
            u16 *RegionalDexTable = (u16 *)PML_PersonalLoadRegionalDexTable(heapId, 0);
            for (u32 i = 1; i <= SPECIES_CNT; i++) {
                if (PokeDex_IsSeen(pDexAddress, i) && RegionalDexTable[i] != 999 && PML_PkmIsRegionalDexExclude(i) ){
                    v3++;
                }
            }
            GFL_HeapFree(RegionalDexTable);
            return v3;
        }

        extern "C" u32 THUMB_BRANCH_PokeDex_GetCaughtNoUnova(void *pDexAddress, HeapID heapId) {
            u32 v3 = 0;
            u16 *RegionalDexTable = (u16 *)PML_PersonalLoadRegionalDexTable(heapId, 0);
            for (u32 i = 1; i <= SPECIES_CNT; i++){
                if (PokeDex_IsCaught(pDexAddress, i) && RegionalDexTable[i] != 999) {
                    v3++;
                }
            }
            GFL_HeapFree(RegionalDexTable);
            return v3;
        }

        extern "C" u32 THUMB_BRANCH_PokeDex_GetCaughtNoPermissive(void *pDexAddress) {
            u32 v2 = 0;
            for (s32 i = 1; i <= SPECIES_CNT; ++i) {
                if (PokeDex_IsCaught(pDexAddress, i) && PML_PkmIsNationalDexExclude(i)) {
                    v2++;
                }
            }
            return v2;
        }

        extern "C" u32 THUMB_BRANCH_PokeDex_GetCaughtNoUnovaPermissive(void *pDexAddress, HeapID heapId) {
            u32 v3 = 0;
            u16 *RegionalDexTable = (u16 *)PML_PersonalLoadRegionalDexTable(heapId, 0);
            for (u32 i = 1; i <= SPECIES_CNT; i++) {
                if (PokeDex_IsCaught(pDexAddress, i) && RegionalDexTable[i] != 999 && PML_PkmIsRegionalDexExclude(i)) {
                    v3++;
                }
            }
            GFL_HeapFree(RegionalDexTable);
            return v3;
        }

        extern "C" u16 THUMB_BRANCH_PokeDex_GetSeenNoNational(void *pDexAddress) {
            u16 v2 = 0;
            for (s32 i = 1; i <= SPECIES_CNT; ++i) {
                if (PokeDex_IsSeen(pDexAddress, i)) {
                    ++v2;
                }
            }
            return v2;
        }

        extern "C" u32 THUMB_BRANCH_PokeDex_GetSeenNoUnova(void *pDexAddress, HeapID heapId) {
            u32 v3 = 0;
            u16 *RegionalDexTable = (u16 *)PML_PersonalLoadRegionalDexTable(heapId, 0);
            for (u32 i = 1; i <= SPECIES_CNT; i++) {
                if (PokeDex_IsSeen(pDexAddress, i) && RegionalDexTable[i] != 999) {
                    v3++;
                }
            }
            GFL_HeapFree(RegionalDexTable);
            return v3;
        }

        extern "C" s32 THUMB_BRANCH_getIndexPokemonWithForms(u32 species) {
			Poke_form pokemonFormList[POKE_FORM_LIST_SIZE];
			if (!ReadDataFromFile(W2U_PATH_POKE_FORM_LIST, POKE_FORM_LIST_SIZE * sizeof(Poke_form), (u8*)pokemonFormList)) {
				return -1;
			}
			
            s32 formIdx = 0;
			for (u32 i = 0; i < POKE_FORM_LIST_SIZE; ++i)
            {
                Poke_form *form = &pokemonFormList[i];
                if ( species == form->species ) {
					return formIdx;
				}

                formIdx += form->form_count;
            }
			return -1;
		}  

        extern "C" s16 THUMB_BRANCH_getIndexNumOfPkmForm(u16 species) {
			Poke_form pokemonFormList[POKE_FORM_LIST_SIZE];
			if (!ReadDataFromFile(W2U_PATH_POKE_FORM_LIST, POKE_FORM_LIST_SIZE * sizeof(Poke_form), (u8*)pokemonFormList)) {
				return -1;
			}

            for (u32 i = 0; i < POKE_FORM_LIST_SIZE; ++i) {
                if ( species == pokemonFormList[i].species) {
                    return i;
                }
            }

			return -1;
		}

        extern "C" s16 THUMB_BRANCH_getNumberOfForms(u16 species)
		{
			Poke_form pokemonFormList[POKE_FORM_LIST_SIZE];
			if (!ReadDataFromFile(W2U_PATH_POKE_FORM_LIST, POKE_FORM_LIST_SIZE * sizeof(Poke_form), (u8*)pokemonFormList)) {
				return -1;
			}

			s16 formListIdx = getIndexNumOfPkmForm(species);
			if ( formListIdx == -1 ) {
				return 1;
			}
			else {
				return pokemonFormList[formListIdx].form_count;
			}
		}
		
		extern "C" u32 THUMB_BRANCH_SAFESTACK_addToDex(PokedexSave* pokedex, u32 species, u32 sex, u32 shiny, u32 form) {
            if (!IsValidDexSpecies(species)) {
                return 0xFFFFFFFF;
            }

            SetDrawData(pokedex, species, sex, shiny, form);
			return (species - 1) >> 3;
		}
		
		extern "C" void THUMB_BRANCH_SAFESTACK_GetPkmDataFromPokedex(PokedexSave* pokedex, int species, int* sex, int* shiny, int* form, u16 heapID) {
			// This presets all the values of the Pokémon to a usable value in case no flags are found.
			*sex = 0;
			*shiny = 0;
			*form = 0;

            if (!IsValidDexSpecies(species)) {
                return;
            }

			// Find the index of the first form of the Pokémon.
			s16 formListIdx = getIndexNumOfPkmForm(species);
		
			// If the Pokémon does NOT have a form.
			if (formListIdx == -1) {
				*form = 0;
				if (CheckDexBit(pokedex, pokedex->seenMale, species)) {
					*sex = 0;
					*shiny = 0;
				}
				if (CheckDexBit(pokedex, pokedex->seenFemale, species)) {
					*sex = 1;
					*shiny = 0;
				}
				if (CheckDexBit(pokedex, pokedex->shinyMale, species)) {
					*sex = 0;
					*shiny = 1;
				}
				if (CheckDexBit(pokedex, pokedex->shinyFemale, species)) {
					*sex = 1;
					*shiny = 1;
				}
			}
			else {
				s32 formIdx = getIndexPokemonWithForms(species);
		
				Poke_form pokemonFormList[POKE_FORM_LIST_SIZE];
				if (!ReadDataFromFile(W2U_PATH_POKE_FORM_LIST, POKE_FORM_LIST_SIZE * sizeof(Poke_form), (u8*)pokemonFormList)) {
					return;
				}
		
				u16 formCount = pokemonFormList[formListIdx].form_count;
				if (formCount) {
					for (u32 currentForm = 0; currentForm < formCount; ++currentForm) {
                        u32 flagIdx = formIdx + currentForm;
                        if (flagIdx >= POKEDEX_FORM_FLAG_BITS) {
                            continue;
                        }
						u32 formGroup = flagIdx >> 3;
						u8 formMask = (u8)(1 << (flagIdx & 7));
		
						if ((pokedex->forms[formGroup] & formMask) != 0) {
							*form = currentForm;
							*shiny = 0;
							break;
						}
						if ((pokedex->shinyForms[formGroup] & formMask) != 0) {
							*form = currentForm;
							*shiny = 1;
							break;
						}
					}
				}
		
				if (CheckDexBit(pokedex, pokedex->seenMale, species)
					|| CheckDexBit(pokedex, pokedex->shinyMale, species)) {
					*sex = 0;
				}
				if (CheckDexBit(pokedex, pokedex->seenFemale, species)
					|| CheckDexBit(pokedex, pokedex->shinyFemale, species)) {
					*sex = 1;
				}
			}
		
			PersonalData* personal = PML_PersonalLoad(species, *form, heapID);
			if (PML_PersonalGetParam(personal, Personal_GenderProb) == 255)
			{
				*sex = 2;
			}
			PML_PersonalFree(personal);
        }

        static inline void RegisterPokedexSeen(PokedexSave *pokedex, PokemonParam *pokemon, b32 caught) {
            PokemonDexSnapshot pokemonData = ReadPokemonDexSnapshot(pokemon);
            if (pokemonData.egg) {
                return;
            }

            u32 species = pokemonData.species;
            if (!IsValidDexSpecies(species)) {
                return;
            }

            if (!THUMB_BRANCH_PokeDex_IsSeen(pokedex, species)) {
                SetDrawData(pokedex, species, pokemonData.sex, pokemonData.shiny, pokemonData.form);
            }

            SetSeenSexFlag(pokedex, species, pokemonData.sex, pokemonData.shiny);
            if (caught) {
                SetDexBit(pokedex, pokedex->caught, species);
            }

            if (species == SPINDA_SPECIES) {
                if (!pokedex->pachiRandom) {
                    pokedex->pachiRandom = pokemonData.personalRnd;
                }
            }
        }

        extern "C" void THUMB_BRANCH_addPkmToDex(PokedexSave *pokedex, PokemonParam *pokemon) {
#if W2U_DISABLE_DEX_REGISTRATION_ON_OBTAIN
            (void)pokedex;
            (void)pokemon;
#else
            RegisterPokedexSeen(pokedex, pokemon, 0);
#endif
        }

        extern "C" void THUMB_BRANCH_PokeDex_RegistPkm(PokedexSave *pokedex, PokemonParam *pokemon) {
#if W2U_DISABLE_DEX_REGISTRATION_ON_OBTAIN
            (void)pokedex;
            (void)pokemon;
#else
            RegisterPokedexSeen(pokedex, pokemon, 1);
#endif
        }

        extern "C" u16 THUMB_BRANCH_PokeDex_GetCaughtNo(PokedexSave *pokedex) {
            return THUMB_BRANCH_PokeDex_GetCaughtNoNational(pokedex);
        }

        extern "C" u16 THUMB_BRANCH_countSeenDexPokes(PokedexSave *pokedex) {
            return THUMB_BRANCH_PokeDex_GetSeenNoNational(pokedex);
        }
    }
}
