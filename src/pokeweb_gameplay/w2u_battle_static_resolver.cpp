#include "Moves.h"
#include "w2u_battle.h"
#include "w2u_battle_module_loader.h"
#include "w2u_field_effects.h"

#define W2U_BATTLE_STATIC_RESOLVER_BUILD
#include "w2u_battle_module_registry.inc"
#undef W2U_BATTLE_STATIC_RESOLVER_BUILD

extern "C" const W2UBattleHandlerExport* W2U_BattleStatic_Resolve(
    W2UBattleMechanicKind kind,
    u16 id)
{
    const W2UBattleMechanicRoute* route = 0;
    for (u32 index = 0; index < W2U_ARRAY_COUNT(sBattleMechanicRoutes); ++index) {
        const W2UBattleMechanicRoute* candidate = &sBattleMechanicRoutes[index];
        if (candidate->kind == (u16)kind && candidate->id == id) {
            route = candidate;
            break;
        }
    }
    if (!route || route->module >= W2U_ARRAY_COUNT(sBattleStaticApiGetters)) {
        return 0;
    }

    const W2UBattleModuleApi* api = sBattleStaticApiGetters[route->module]();
    if (!api ||
        api->magic != W2U_BATTLE_MODULE_MAGIC ||
        api->abiVersion != W2U_BATTLE_MODULE_ABI_VERSION) {
        return 0;
    }
    for (u32 index = 0; index < api->entryCount; ++index) {
        const W2UBattleHandlerExport* entry = &api->entries[index];
        if (entry->kind == (u16)kind && entry->id == id) {
            return entry;
        }
    }
    return 0;
}
