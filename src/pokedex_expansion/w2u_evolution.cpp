#include "swan/swantypes.h"
#include "species_ids.h"
#include "FileSystem.h"
#include "w2u_platform.h"

// Evolution by form (docs/evolution-forms.md).
//
// Retail reads a Pokemon's evolutions by species only and keeps its form number when the species changes, so a
// regional form evolved as its base species did, into whatever form had its number (Galarian Slowpoke, form 1,
// into Mega Slowbro). Here:
//  - CheckEvolveSpecies (retail's, with Expansion_LimitAdjust.s's 8-record patches) reads the evolution record of the
//    Pokemon's species and form: its getEvolutionInfoFile call goes to W2U_Evolution_Read with the Pokemon
//    (Expansion_LimitAdjust.s). The evolution archive has a member per personal record, forms included, like the
//    personal and learnset archives; a form record with no evolutions (cosmetic forms) falls back to its species',
//    as retail always read.
//  - setChangedPkmSpecies, which the evolution demo uses for the Pokemon and the copy it shows, gives the new species
//    a form when the species changes: the one data/pml/evolution_forms.bin names for (species, form, new species),
//    else the same form number if the new species has it, else form 0.

#define ARCID_EVOLUTIONS 19
#define EVOLUTION_RECORDS 8                // W2U's members: 8 x {method, param, species} (retail: 7)
#define PKM_PARAM_SPECIES 0x5
#define PKM_PARAM_FORM 0x6f
#define EVOLUTION_FORMS_MAX 64

namespace w2u {
    namespace pml {

        struct Evolution {
            u16 method;
            u16 param;
            u16 species;
        };

        // data/pml/evolution_forms.bin: entries until species 0, the file padded to EVOLUTION_FORMS_MAX entries
        struct EvolutionForm {
            u16 species;
            u16 targetSpecies;
            u8 form;
            u8 targetForm;
            u16 reserved;
        };

        static_assert(sizeof(Evolution) == 6, "Evolution layout");
        static_assert(sizeof(EvolutionForm) == 8, "EvolutionForm layout");

        extern "C" u32 PokeParty_GetParam(void *pkm, u32 field, void *extra);
        extern "C" u32 PML_PkmGetParam(void *pkm, u32 field, void *extra);
        extern "C" void PML_PkmSetParam(void *pkm, u32 field, u32 value);
        extern "C" void GFL_ArcSysRead(void *dest, u32 arcId, u32 index);
        extern "C" u16 PML_PersonalGetDatID(u16 species, u16 form);
        extern "C" s16 getNumberOfForms(u16 species);
        extern "C" b32 PokeParty_DecryptPkm(void *pkm);
        extern "C" void PokeParty_EncryptPkm(void *pkm, b32 wasEncrypted);
        extern "C" void PokeParty_RecalcStats(void *pkm);
        extern "C" void setNameChangedPkm(void *pkm, u16 species);

        // CheckEvolveSpecies' getEvolutionInfoFile(species, dest), with the Pokemon (Expansion_LimitAdjust.s).
        extern "C" void W2U_Evolution_Read(u16 species, Evolution *dest, void *pkm) {
            u16 form = (u16)PokeParty_GetParam(pkm, PKM_PARAM_FORM, 0);
            GFL_ArcSysRead(dest, ARCID_EVOLUTIONS, PML_PersonalGetDatID(species, form));
            if (form) {                           // a form record with no evolutions uses its species' (retail's way)
                for (u32 i = 0; i < EVOLUTION_RECORDS; ++i) {
                    if (dest[i].method) {
                        return;
                    }
                }
                GFL_ArcSysRead(dest, ARCID_EVOLUTIONS, species);
            }
        }

        // The form a Pokemon of (species, form) takes when it becomes newSpecies.
        static u32 EvolvedForm(u32 species, u32 form, u32 newSpecies) {
            EvolutionForm table[EVOLUTION_FORMS_MAX];
            if (ReadDataFromFile(W2U_PATH_EVOLUTION_FORMS, sizeof(table), (u8 *)table)) {
                for (u32 i = 0; i < EVOLUTION_FORMS_MAX && table[i].species; ++i) {
                    if (table[i].species == species && table[i].form == form && table[i].targetSpecies == newSpecies) {
                        return table[i].targetForm;
                    }
                }
            }
            s16 forms = getNumberOfForms((u16)newSpecies);
            return (forms > 0 && form < (u32)forms) ? form : 0;
        }

        // Retail's (decomp src/system/poke_tool.c), with the new species' form set before its ability and stats are.
        extern "C" void THUMB_BRANCH_setChangedPkmSpecies(void *pkm, u16 species) {
            b32 wasEncrypted = PokeParty_DecryptPkm(pkm);
            u32 oldSpecies = PML_PkmGetParam(pkm, PKM_PARAM_SPECIES, 0);
            if (oldSpecies != species) {
                u32 form = PML_PkmGetParam(pkm, PKM_PARAM_FORM, 0);
                u32 newForm = EvolvedForm(oldSpecies, form, species);
                if (newForm != form) {
                    PML_PkmSetParam(pkm, PKM_PARAM_FORM, newForm);
                }
            }
            setNameChangedPkm(pkm, species);
            PokeParty_RecalcStats(pkm);
            PokeParty_EncryptPkm(pkm, wasEncrypted);
        }
    }
}
