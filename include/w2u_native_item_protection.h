#ifndef W2U_NATIVE_ITEM_PROTECTION_H
#define W2U_NATIVE_ITEM_PROTECTION_H

#include "swan/swantypes.h"
#include "species_ids.h"

// US BW2's native form-item sets. Keep this predicate independent of the
// replacement hook: importing an alias at that address would recurse.
constexpr bool W2U_IsNativeProtectedFormItem(u32 species, u32 itemID)
{
    return (species == SPECIES_GIRATINA && itemID == 112u) ||
        (species == SPECIES_ARCEUS && itemID >= 298u && itemID <= 313u) ||
        (species == SPECIES_GENESECT && itemID >= 116u && itemID <= 119u);
}

#endif
