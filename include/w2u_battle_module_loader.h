#ifndef __W2U_BATTLE_MODULE_LOADER_H
#define __W2U_BATTLE_MODULE_LOADER_H

#include "w2u_battle_module_api.h"

struct W2UBattleModuleTelemetry {
    u32 coreFixedBytes;
    u32 loadedModuleCount;
    u32 currentChildBytes;
    u32 peakChildBytes;
    u32 loadCount;
    u32 unloadCount;
    u32 failureCount;
    u32 failedModuleMask;
    u32 lastFailureModuleId;
    u32 heapRefusalCount;      // loads refused because no PMC heap block was large enough
    u32 lastRefusedBytes;      // the size that last refusal needed
    u32 lastLargestFreeBytes;  // the largest free PMC heap block at that refusal
    u32 gameHeapModuleCount;   // loaded modules placed on GFL heap 1 instead of PMC's heap (White 2, during battle)
    u32 gameHeapBytes;         // their current size on that heap (blocks, including W2U's block headers)
    u32 gameHeapPeakBytes;
};

extern "C" const W2UBattleHandlerExport* W2U_BattleModules_Resolve(
    W2UBattleMechanicKind kind,
    u16 id);
extern "C" const W2UBattleHandlerExport* W2U_BattleModules_FindLoaded(
    W2UBattleMechanicKind kind,
    u16 id);
extern "C" bool W2U_BattleModules_IsManaged(W2UBattleMechanicKind kind, u16 id);
extern "C" void W2U_BattleModules_Reset();
extern "C" void W2U_BattleModules_SetRegistrationEnabled(bool enabled);
extern "C" const W2UBattleModuleTelemetry* W2U_BattleModules_GetTelemetry();
extern "C" const W2UBattleHandlerExport* W2U_BattleStatic_Resolve(
    W2UBattleMechanicKind kind,
    u16 id);

#endif
