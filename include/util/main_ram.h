#ifndef W2U_MAIN_RAM_H
#define W2U_MAIN_RAM_H

#include "nds/hw.h"

namespace w2u {
// Native DSi mode exposes 16 MiB of main RAM. In DS mode the extra
// addresses mirror the 4 MiB allocation space and must not validate as heaps.
inline bool IsMainRamAddress(u32 address, u32 size = 1u)
{
    if (!size || address < 0x02000000u || address >= 0x03000000u) return false;
    if (address < 0x02400000u && size <= 0x02400000u - address) return true;
    return size <= 0x03000000u - address && hw_isDSi() != 0;
}
} // namespace w2u

#endif
