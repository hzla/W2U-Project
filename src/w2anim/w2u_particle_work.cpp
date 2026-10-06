// Battle-only native SPL work arena. Large imported SPA resource tables must
// not spill into adjacent scripts or heap headers. The native bump allocator
// has no capacity check; both the allocation and its advertised size change.
#include "swantypes.h"

extern "C" {
void* GFL_HeapAllocate(u32 heap, u32 bytes, u32 clear, const char* file, u32 line);
void* GFL_PTC_CreateEx(void* work, int bytes, int camera, int polygon,
                      int minimum, int maximum, u32 heap);
}

static u32 BattleParticleWorkBytes(u32 nativeBytes)
{
    return nativeBytes == 0x4800u ? 0x6000u : nativeBytes;
}

extern "C" void* THUMB_BRANCH_LINK_BTLV_EFFECT_CMD_LoadSPA_0x48(
    u32 heap, u32 bytes, u32 clear, const char* file, u32 line)
{
    return GFL_HeapAllocate(heap, BattleParticleWorkBytes(bytes), clear, file, line);
}

extern "C" void* THUMB_BRANCH_LINK_BTLV_EFFECT_CMD_LoadSPA_0x98(
    void* work, int bytes, int camera, int polygon, int minimum, int maximum, u32 heap)
{
    return GFL_PTC_CreateEx(work, BattleParticleWorkBytes(bytes), camera, polygon, minimum, maximum, heap);
}
