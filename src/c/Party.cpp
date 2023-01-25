#include "swan/pml/poke_param.h"
#include "Personal.h"

#define FORM_START 1522

namespace W2U
{
    extern "C"
    {
        extern u32 PML_PersonalGetParamSingle(u32, u32, u32);
        extern u32 GFL_ArcSysGetDataLength(u32, u32);
        int THUMB_BRANCH_PokeParty_GetIconIndex(int Species, u32 Form, int Gender, int Egg)
        {
            u16 v4 = Species;
            u32 v5 = Form;
            int v7 = 2 * Species + 8;
            u32 v9;
            u32 ParamSingle;
            if (Species >= 650)
            {
                // Rebase on Chespin's sprite (1378)
                return 2 * (Species - 650) + 1378;
            }
            if (Egg)
            {
                v7 = (((Species == 490) + 683) << 2) + 8;
            }
            else if (Form)
            {
                ParamSingle = PML_PersonalGetParamSingle(Species, 0, Personal_FormeSpritesOffset);
                v9 = PML_PersonalGetParamSingle(v4, 0, Personal_SpriteForme);
                if (v5 >= PML_PersonalGetParamSingle(v4, 0, Personal_FormeCount))
                {
                    v5 = 0;
                }
                if (!v9 && v5)
                {
                    // TODO: Fix. This is broken, so I disabled it for now. It just returns either 2 * Species + 8, or one of the eggs.
                    // v7 = 2 * (ParamSingle + v5 - 1) + FORM_START;
                    return v7;
                }
            }
            if (Gender)
            {
                if (Gender != 1)
                {
                    if (Gender != 2)
                    {
                        return v7 + Gender;
                    }
                    goto LABEL_14;
                }
                Gender = 1;
                if (!GFL_ArcSysGetDataLength(7u, v7 + 1))
                {
                LABEL_14:
                    Gender = 0;
                }
            }
            return v7 + Gender;
        }
    }
};