#ifndef __W2U_BATTLE_MODULE_API_H
#define __W2U_BATTLE_MODULE_API_H

#include "w2u_abilities.h"

#define W2U_BATTLE_MODULE_MAGIC 0x4D423257u
#define W2U_BATTLE_MODULE_ABI_VERSION 1u
#define W2U_BATTLE_MODULE_DEFAULT_PRIORITY 0xFFFFu

enum W2UBattleMechanicKind : u16 {
    W2U_MECHANIC_ABILITY = 0,
    W2U_MECHANIC_MOVE = 1,
    W2U_MECHANIC_ITEM = 2,
    W2U_MECHANIC_FIELD = 3,
    W2U_MECHANIC_SIDE = 4,
    W2U_MECHANIC_POSITION = 5,
};

struct W2UBattleHandlerExport {
    u16 kind;
    u16 id;
    u16 handlerCount;
    u16 priority;
    const BattleEventHandlerTableEntry* handlers;
};

struct W2UBattleModuleApi {
    u32 magic;
    u16 abiVersion;
    u16 entryCount;
    const W2UBattleHandlerExport* entries;
};

static_assert(sizeof(W2UBattleHandlerExport) == 12, "battle handler ABI layout changed");
static_assert(sizeof(W2UBattleModuleApi) == 12, "battle module ABI layout changed");

typedef const W2UBattleModuleApi* (*W2UGetBattleModuleApiFunc)();

#if defined(__GNUC__)
#define W2U_BATTLE_MODULE_EXPORT __attribute__((visibility("default"), used))
#else
#define W2U_BATTLE_MODULE_EXPORT
#endif

#endif
