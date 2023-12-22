#include "Personal.h"
#include "pml/poke_param.h"
#include "pml/poke_party.h"
#include "pml/poke_data.h"

#define FORM_START 1378

namespace w2u {
    extern "C" {  
        extern u32 PML_PersonalGetParamSingle(u32, u32, u32);
        extern u32 GFL_ArcSysGetDataLength(u32, u32);      
        s32 THUMB_BRANCH_PokeParty_GetIconIndex(s32 Species, s32 Form, s32 Gender, s32 Egg) {
            // TODO: Handle forms.
            u32 Index  = 8 + 2 * Species;

            if (Species >= 650) {
                // Rebase on Chespin's sprite (1378)
                Index = 2 * (Species - 650) + 1378;
            }

            if (Egg) {
                Index = (((Species == 490) + 755) << 2) + 8;
            }
            
            if ((Gender && Gender > 1) || !GFL_ArcSysGetDataLength(7u, Index + 1)) {
                // Empty file or invalid file.
                Gender = 0;
            }

            return Index + Gender;
        }
    }
}; // namespace W2U