#include "w2u_battle_module_loader.h"

#include "Items.h"
#include "Moves.h"
#include "util/filesystem.h"
#include "w2u_field_effects.h"
#include "w2u_pmc_runtime.h"

namespace {

constexpr u32 W2U_RPM_MAGIC = 0x46584C44u;
constexpr u32 W2U_RPM_SYMBOL_FILE_MAGIC = 0x304D5052u;
constexpr u32 W2U_RPM_EXEC_MAGIC = 0x48584C44u;
constexpr u32 W2U_RPM_INFO_MAGIC = 0x4F464E49u;
constexpr u32 W2U_RPM_RELOC_MAGIC = 0x304C4552u;
constexpr u32 W2U_RPM_SYMBOL_MAGIC = 0x304D5953u;
constexpr u32 W2U_RPM_MINIMUM_SIZE = 24u;
constexpr u32 W2U_RPM_MAXIMUM_EXPANDED_SIZE = 128u * 1024u;
constexpr u32 W2U_RPM_PROLOG_SIZE = 0x20u;
constexpr u32 W2U_RPM_MINIMUM_REVISION = 13u;
constexpr u32 W2U_RPM_MAXIMUM_SYMBOLS = 4096u;
constexpr u32 W2U_RPM_MAXIMUM_EXPORTS = 512u;
constexpr u32 W2U_RPM_EXPORT_HASH_CHUNK = 16u;
constexpr u32 W2U_MAX_MODULE_RECORDS = 32u;
constexpr u32 W2U_MAX_API_ENTRIES = 96u;
constexpr u32 W2U_MAX_HANDLERS_PER_ENTRY = 64u;

constexpr u8 W2U_RPM_SYMBOL_FUNCTION_THUMB = 3u;
constexpr u8 W2U_RPM_SYMBOL_EXPORT = 1u << 0;
constexpr u8 W2U_RPM_SYMBOL_IMPORT = 1u << 1;
constexpr u8 W2U_RPM_SYMBOL_GLOBAL = 1u << 2;

const char* const W2U_PMC_SYMBOL_PATHS[] = {
    "codeinjection/RPMSYM-PMC.rpm",
    "data/codeinjection/RPMSYM-PMC.rpm",
};

// FNV-1a hashes retained in stripped RPM export tables.
const u32 W2U_PMC_EXPORT_HASHES[] = {
    0x469AEBEFu, // pmc::fwk::AllocModuleMemory(unsigned int)
    0xA8054409u, // pmc::fwk::FreeModuleMemory(void*)
    0xC6FA286Cu, // pmc::fwk::LoadModule(void*)
    0xC13E1C85u, // pmc::fwk::StartModule(void*)
    0x5529ACB6u, // pmc::fwk::GetProcAddress(void*, char const*)
    0x5B7ED5FBu, // pmc::fwk::UnloadModule(void*)
};

#include "w2u_battle_module_registry.inc"

static_assert(W2U_BATTLE_MODULE_COUNT <= W2U_MAX_MODULE_RECORDS, "battle module record capacity exceeded");
static_assert(
    W2U_ARRAY_COUNT(sBattleModuleDescriptors) == W2U_BATTLE_MODULE_COUNT,
    "battle module descriptor count mismatch");

enum W2UModuleLoadState : u8 {
    W2U_MODULE_NOT_LOADED,
    W2U_MODULE_LOADED,
    W2U_MODULE_FAILED,
};

struct W2UBattleModuleRecord {
    W2UPmcModuleHandle handle;
    const W2UBattleModuleApi* api;
    u32 expandedBytes;
    u32 fixedBytes;
    u8 state;
    u8 moduleId;
};

W2UBattleModuleRecord sModuleRecords[W2U_MAX_MODULE_RECORDS];
W2UBattleModuleTelemetry sTelemetry;
W2UPmcRuntimeApi sPmcRuntime;
bool sRegistrationEnabled = true;
bool sResetting = false;
u8 sPmcRuntimeState = 0;

u16 ReadU16(const u8* data, u32 offset)
{
    return (u16)data[offset] | ((u16)data[offset + 1] << 8);
}

u32 ReadU32(const u8* data, u32 offset)
{
    return (u32)data[offset] |
        ((u32)data[offset + 1] << 8) |
        ((u32)data[offset + 2] << 16) |
        ((u32)data[offset + 3] << 24);
}

void ClearBytes(void* memory, u32 size)
{
    volatile u8* bytes = static_cast<volatile u8*>(memory);
    for (u32 index = 0; index < size; ++index) {
        bytes[index] = 0;
    }
}

bool BuildModulePath(char* output, u32 capacity, const char* relative)
{
    if (!output || !relative || !capacity) return false;
    u32 count = 0;
    const char* parts[] = { sBattleModuleRoot, relative };
    for (u32 part = 0; part < 2; ++part) {
        for (const char* at = parts[part]; *at; ++at) {
            if (count + 1 >= capacity) return false;
            output[count++] = *at;
        }
    }
    output[count] = 0;
    return true;
}

bool AddFileOffset(u32 base, u32 relative, u32 fileSize, u32* result)
{
    if (!result || relative == 0xFFFFFFFFu || base > fileSize || relative > fileSize - base) {
        return false;
    }
    *result = base + relative;
    return true;
}

bool ReadFileRange(
    const char* path,
    u32 fileSize,
    u32 offset,
    u32 size,
    u8* output)
{
    return output && size && offset <= fileSize && size <= fileSize - offset &&
        w2u::ReadDataFromFileAt(path, offset, size, output);
}

bool ResolvePmcRuntimeFromFile(const char* path, W2UPmcRuntimeApi* runtime)
{
    u32 fileSize = 0;
    u8 fileHeader[12];
    if (!runtime || !w2u::GetFileSize(path, &fileSize) ||
        !ReadFileRange(path, fileSize, 0u, sizeof(fileHeader), fileHeader) ||
        ReadU32(fileHeader, 0u) != W2U_RPM_SYMBOL_FILE_MAGIC) {
        return false;
    }

    const u32 execOffset = ReadU32(fileHeader, 8u);
    u8 execHeader[16];
    if (!ReadFileRange(path, fileSize, execOffset, sizeof(execHeader), execHeader) ||
        ReadU32(execHeader, 0u) != W2U_RPM_EXEC_MAGIC ||
        ReadU32(execHeader, 4u) < W2U_RPM_MINIMUM_REVISION) {
        return false;
    }

    u32 infoOffset = 0;
    u8 infoHeader[36];
    if (!AddFileOffset(execOffset, ReadU32(execHeader, 8u), fileSize, &infoOffset) ||
        !ReadFileRange(path, fileSize, infoOffset, sizeof(infoHeader), infoHeader) ||
        ReadU32(infoHeader, 0u) != W2U_RPM_INFO_MAGIC) {
        return false;
    }

    u32 symbolOffset = 0;
    u32 relocOffset = 0;
    if (!AddFileOffset(execOffset, ReadU32(infoHeader, 4u), fileSize, &symbolOffset) ||
        !AddFileOffset(execOffset, ReadU32(infoHeader, 8u), fileSize, &relocOffset)) {
        return false;
    }

    u8 relocHeader[8];
    if (!ReadFileRange(path, fileSize, relocOffset, sizeof(relocHeader), relocHeader) ||
        ReadU32(relocHeader, 0u) != W2U_RPM_RELOC_MAGIC) {
        return false;
    }
    const u32 baseAddress = ReadU32(relocHeader, 4u);

    u8 symbolHeader[24];
    if (!ReadFileRange(path, fileSize, symbolOffset, sizeof(symbolHeader), symbolHeader) ||
        ReadU32(symbolHeader, 0u) != W2U_RPM_SYMBOL_MAGIC) {
        return false;
    }

    const u32 firstExport = ReadU16(symbolHeader, 8u);
    const u32 exportCount = ReadU16(symbolHeader, 10u);
    const u32 symbolCount = ReadU32(symbolHeader, 20u);
    u32 exportHashOffset = 0;
    if (firstExport == 0xFFFFu || !exportCount ||
        exportCount > W2U_RPM_MAXIMUM_EXPORTS ||
        symbolCount > W2U_RPM_MAXIMUM_SYMBOLS ||
        firstExport > symbolCount || exportCount > symbolCount - firstExport ||
        !AddFileOffset(
            execOffset,
            ReadU32(symbolHeader, 16u),
            fileSize,
            &exportHashOffset)) {
        return false;
    }

    void* resolved[W2U_ARRAY_COUNT(W2U_PMC_EXPORT_HASHES)];
    ClearBytes(resolved, sizeof(resolved));
    u32 foundMask = 0;
    u8 hashBytes[W2U_RPM_EXPORT_HASH_CHUNK * sizeof(u32)];
    for (u32 exportIndex = 0; exportIndex < exportCount;) {
        u32 chunkCount = exportCount - exportIndex;
        if (chunkCount > W2U_RPM_EXPORT_HASH_CHUNK) {
            chunkCount = W2U_RPM_EXPORT_HASH_CHUNK;
        }
        if (!ReadFileRange(
                path,
                fileSize,
                exportHashOffset + exportIndex * sizeof(u32),
                chunkCount * sizeof(u32),
                hashBytes)) {
            return false;
        }

        for (u32 chunkIndex = 0; chunkIndex < chunkCount; ++chunkIndex) {
            const u32 hash = ReadU32(hashBytes, chunkIndex * sizeof(u32));
            for (u32 wantedIndex = 0;
                 wantedIndex < W2U_ARRAY_COUNT(W2U_PMC_EXPORT_HASHES);
                 ++wantedIndex) {
                if (hash != W2U_PMC_EXPORT_HASHES[wantedIndex]) {
                    continue;
                }
                const u32 wantedBit = 1u << wantedIndex;
                if (foundMask & wantedBit) {
                    return false;
                }

                const u32 symbolIndex = firstExport + exportIndex + chunkIndex;
                const u32 recordOffset = symbolOffset + 24u + symbolIndex * 12u;
                u8 symbolRecord[12];
                if (!ReadFileRange(
                        path,
                        fileSize,
                        recordOffset,
                        sizeof(symbolRecord),
                        symbolRecord)) {
                    return false;
                }

                const u8 type = symbolRecord[8];
                const u8 attributes = symbolRecord[9];
                if (type != W2U_RPM_SYMBOL_FUNCTION_THUMB ||
                    !(attributes & W2U_RPM_SYMBOL_EXPORT) ||
                    (attributes & W2U_RPM_SYMBOL_IMPORT)) {
                    return false;
                }

                u32 functionAddress = ReadU32(symbolRecord, 4u);
                if (!(attributes & W2U_RPM_SYMBOL_GLOBAL)) {
                    if (baseAddress > 0xFFFFFFFFu - W2U_RPM_PROLOG_SIZE ||
                        functionAddress > 0xFFFFFFFFu -
                            (baseAddress + W2U_RPM_PROLOG_SIZE)) {
                        return false;
                    }
                    functionAddress += baseAddress + W2U_RPM_PROLOG_SIZE;
                }
                if ((functionAddress & ~1u) < 0x02000000u ||
                    (functionAddress & ~1u) >= 0x02400000u) {
                    return false;
                }
                resolved[wantedIndex] = reinterpret_cast<void*>(functionAddress | 1u);
                foundMask |= wantedBit;
            }
        }
        exportIndex += chunkCount;
    }

    if (foundMask != (1u << W2U_ARRAY_COUNT(W2U_PMC_EXPORT_HASHES)) - 1u) {
        return false;
    }

    runtime->allocModuleMemory =
        reinterpret_cast<W2UPmcAllocModuleMemoryFunc>(resolved[0]);
    runtime->freeModuleMemory =
        reinterpret_cast<W2UPmcFreeModuleMemoryFunc>(resolved[1]);
    runtime->loadModule = reinterpret_cast<W2UPmcLoadModuleFunc>(resolved[2]);
    runtime->startModule = reinterpret_cast<W2UPmcStartModuleFunc>(resolved[3]);
    runtime->getProcAddress = reinterpret_cast<W2UPmcGetProcAddressFunc>(resolved[4]);
    runtime->unloadModule = reinterpret_cast<W2UPmcUnloadModuleFunc>(resolved[5]);
    return true;
}

bool EnsurePmcRuntime()
{
    if (sPmcRuntimeState == 1u) {
        return true;
    }
    if (sPmcRuntimeState == 2u) {
        return false;
    }
    for (u32 pathIndex = 0; pathIndex < W2U_ARRAY_COUNT(W2U_PMC_SYMBOL_PATHS); ++pathIndex) {
        if (ResolvePmcRuntimeFromFile(W2U_PMC_SYMBOL_PATHS[pathIndex], &sPmcRuntime)) {
            sPmcRuntimeState = 1u;
            return true;
        }
    }
    ClearBytes(&sPmcRuntime, sizeof(sPmcRuntime));
    sPmcRuntimeState = 2u;
    return false;
}

bool IsRangeInside(const void* base, u32 size, const void* pointer, u32 rangeSize)
{
    if (!base || !pointer || rangeSize > size) {
        return false;
    }
    const u32 start = reinterpret_cast<u32>(base);
    const u32 address = reinterpret_cast<u32>(pointer);
    return address >= start && address - start <= size - rangeSize;
}

bool IsAligned(const void* pointer, u32 alignment)
{
    return pointer && (reinterpret_cast<u32>(pointer) & (alignment - 1u)) == 0;
}

bool IsValidHandlerPointer(
    const W2UBattleModuleRecord* record,
    const void* pointer)
{
    const u32 rawAddress = reinterpret_cast<u32>(pointer);
    const u32 codeAddress = rawAddress & ~1u;
    if (!codeAddress || (codeAddress & 1u)) {
        return false;
    }
    if (IsRangeInside(record->handle, record->fixedBytes, reinterpret_cast<void*>(codeAddress), 2u)) {
        return true;
    }
    // Reviewed game/PMC symbols resolve into main-memory code. Imported table
    // handlers such as the vanilla Protect and Overcoat handlers live here.
    return codeAddress >= 0x02000000u && codeAddress < 0x02400000u;
}

bool IsModuleCodePointer(
    const W2UBattleModuleRecord* record,
    const void* pointer)
{
    const u32 codeAddress = reinterpret_cast<u32>(pointer) & ~1u;
    return codeAddress &&
        IsRangeInside(
            record->handle,
            record->fixedBytes,
            reinterpret_cast<const void*>(codeAddress),
            2u);
}

const W2UBattleMechanicRoute* FindRoute(W2UBattleMechanicKind kind, u16 id)
{
    for (u32 index = 0; index < W2U_ARRAY_COUNT(sBattleMechanicRoutes); ++index) {
        const W2UBattleMechanicRoute* route = &sBattleMechanicRoutes[index];
        if (route->kind == (u16)kind && route->id == id) {
            return route;
        }
    }
    return 0;
}

const W2UBattleHandlerExport* FindApiEntry(
    const W2UBattleModuleApi* api,
    W2UBattleMechanicKind kind,
    u16 id)
{
    if (!api) {
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

bool ParseRpmHeader(
    const u8* data,
    u32 fileSize,
    u32* expandedSize,
    u32* fixedSize)
{
    if (!data || fileSize < W2U_RPM_MINIMUM_SIZE ||
        ReadU32(data, 0) != W2U_RPM_MAGIC) {
        return false;
    }

    const u32 expanded = ReadU32(data, 4);
    const u32 execOffset = ReadU32(data, 8);
    if (expanded < fileSize || expanded > W2U_RPM_MAXIMUM_EXPANDED_SIZE ||
        execOffset > fileSize - 20u ||
        ReadU32(data, execOffset) != W2U_RPM_EXEC_MAGIC) {
        return false;
    }

    const u32 infoRelative = ReadU32(data, execOffset + 8u);
    if (infoRelative > fileSize - execOffset ||
        infoRelative + 36u > fileSize - execOffset) {
        return false;
    }
    const u32 infoOffset = execOffset + infoRelative;
    if (ReadU32(data, infoOffset) != W2U_RPM_INFO_MAGIC) {
        return false;
    }

    u32 fixed = expanded;
    const u32 relocRelative = ReadU32(data, infoOffset + 8u);
    if (relocRelative) {
        if (relocRelative > fileSize - execOffset ||
            relocRelative + 24u > fileSize - execOffset) {
            return false;
        }
        const u32 relocOffset = execOffset + relocRelative;
        if (ReadU32(data, relocOffset) != W2U_RPM_RELOC_MAGIC) {
            return false;
        }
        const u32 internalRelative = ReadU32(data, relocOffset + 8u);
        if (internalRelative) {
            fixed = execOffset + internalRelative;
            if (fixed < W2U_RPM_MINIMUM_SIZE || fixed > expanded) {
                return false;
            }
        }
    }

    *expandedSize = expanded;
    *fixedSize = fixed;
    return true;
}

bool ValidateApi(
    const W2UBattleModuleRecord* record,
    u8 moduleId,
    W2UBattleMechanicKind expectedKind,
    u16 expectedId)
{
    const W2UBattleModuleApi* api = record->api;
    if (!IsAligned(api, 4u) ||
        !IsRangeInside(record->handle, record->fixedBytes, api, sizeof(*api)) ||
        api->magic != W2U_BATTLE_MODULE_MAGIC ||
        api->abiVersion != W2U_BATTLE_MODULE_ABI_VERSION ||
        api->entryCount == 0 ||
        api->entryCount > W2U_MAX_API_ENTRIES ||
        !IsAligned(api->entries, 4u) ||
        !IsRangeInside(
            record->handle,
            record->fixedBytes,
            api->entries,
            api->entryCount * sizeof(W2UBattleHandlerExport))) {
        return false;
    }

    bool foundExpected = false;
    for (u32 entryIndex = 0; entryIndex < api->entryCount; ++entryIndex) {
        const W2UBattleHandlerExport* entry = &api->entries[entryIndex];
        const W2UBattleMechanicRoute* route =
            entry->kind <= W2U_MECHANIC_POSITION
                ? FindRoute((W2UBattleMechanicKind)entry->kind, entry->id)
                : 0;
        if (!route ||
            route->module != moduleId ||
            entry->handlerCount == 0 ||
            entry->handlerCount > W2U_MAX_HANDLERS_PER_ENTRY ||
            (entry->priority != W2U_BATTLE_MODULE_DEFAULT_PRIORITY && entry->priority > 0xFFu) ||
            !IsAligned(entry->handlers, 4u) ||
            !IsRangeInside(
                record->handle,
                record->fixedBytes,
                entry->handlers,
                entry->handlerCount * sizeof(BattleEventHandlerTableEntry))) {
            return false;
        }

        for (u32 otherIndex = 0; otherIndex < entryIndex; ++otherIndex) {
            const W2UBattleHandlerExport* other = &api->entries[otherIndex];
            if (entry->kind == other->kind && entry->id == other->id) {
                return false;
            }
        }

        for (u32 handlerIndex = 0; handlerIndex < entry->handlerCount; ++handlerIndex) {
            if (!IsValidHandlerPointer(
                    record,
                    reinterpret_cast<const void*>(
                        entry->handlers[handlerIndex].handler))) {
                return false;
            }
        }

        if (entry->kind == (u16)expectedKind && entry->id == expectedId) {
            foundExpected = true;
        }
    }
    return foundExpected;
}

void MarkFailure(u8 moduleId)
{
    W2UBattleModuleRecord* record = &sModuleRecords[moduleId];
    record->moduleId = moduleId;
    record->handle = 0;
    record->api = 0;
    record->expandedBytes = 0;
    record->fixedBytes = 0;
    if (record->state != W2U_MODULE_FAILED) {
        record->state = W2U_MODULE_FAILED;
        ++sTelemetry.failureCount;
        sTelemetry.failedModuleMask |= 1u << moduleId;
        sTelemetry.lastFailureModuleId = moduleId;
    }
}

bool LoadModule(u8 moduleId, W2UBattleMechanicKind expectedKind, u16 expectedId)
{
    if (moduleId >= W2U_BATTLE_MODULE_COUNT) {
        return false;
    }

    W2UBattleModuleRecord* record = &sModuleRecords[moduleId];
    record->moduleId = moduleId;
    if (record->state == W2U_MODULE_LOADED) {
        return true;
    }
    if (record->state == W2U_MODULE_FAILED || !sRegistrationEnabled) {
        return false;
    }

    const W2UBattleModuleDescriptor* descriptor = &sBattleModuleDescriptors[moduleId];
    if (descriptor->dependency != W2U_NO_MODULE &&
        !LoadModule(descriptor->dependency, W2U_MECHANIC_FIELD, FLDEFF_TERRAIN)) {
        MarkFailure(moduleId);
        return false;
    }

    if (!EnsurePmcRuntime()) {
        MarkFailure(moduleId);
        return false;
    }

    u32 fileSize = 0;
    u8 header[64];
    char path[64];
    if (!BuildModulePath(path, sizeof(path), descriptor->path) ||
        !w2u::GetFileSize(path, &fileSize) ||
        fileSize < W2U_RPM_MINIMUM_SIZE ||
        !w2u::ReadDataFromFile(path, sizeof(header), header)) {
        MarkFailure(moduleId);
        return false;
    }

    u32 expandedSize = 0;
    u32 fixedSize = 0;
    if (!ParseRpmHeader(header, sizeof(header), &expandedSize, &fixedSize)) {
        // The compact header read cannot validate sections beyond byte 64.
        expandedSize = ReadU32(header, 4);
        if (ReadU32(header, 0) != W2U_RPM_MAGIC ||
            expandedSize < fileSize ||
            expandedSize > W2U_RPM_MAXIMUM_EXPANDED_SIZE) {
            MarkFailure(moduleId);
            return false;
        }
    }

    u8* allocation = static_cast<u8*>(sPmcRuntime.allocModuleMemory(expandedSize));
    if (!allocation) {
        MarkFailure(moduleId);
        return false;
    }
    ClearBytes(allocation, expandedSize);
    if (!w2u::ReadDataFromFile(path, fileSize, allocation) ||
        !ParseRpmHeader(allocation, fileSize, &expandedSize, &fixedSize)) {
        sPmcRuntime.freeModuleMemory(allocation);
        MarkFailure(moduleId);
        return false;
    }

    W2UPmcModuleHandle handle = sPmcRuntime.loadModule(allocation);
    if (!handle) {
        MarkFailure(moduleId);
        return false;
    }
    sPmcRuntime.startModule(handle);

    W2UGetBattleModuleApiFunc getApi =
        reinterpret_cast<W2UGetBattleModuleApiFunc>(
            sPmcRuntime.getProcAddress(handle, "W2U_GetBattleModuleApi"));
    record->handle = handle;
    record->expandedBytes = expandedSize;
    record->fixedBytes = fixedSize;
    record->api =
        IsModuleCodePointer(record, reinterpret_cast<const void*>(getApi))
            ? getApi()
            : 0;
    if (!ValidateApi(record, moduleId, expectedKind, expectedId)) {
        record->handle = 0;
        record->api = 0;
        sPmcRuntime.unloadModule(handle);
        MarkFailure(moduleId);
        return false;
    }

    record->state = W2U_MODULE_LOADED;
    ++sTelemetry.loadedModuleCount;
    ++sTelemetry.loadCount;
    sTelemetry.currentChildBytes += fixedSize;
    if (sTelemetry.currentChildBytes > sTelemetry.peakChildBytes) {
        sTelemetry.peakChildBytes = sTelemetry.currentChildBytes;
    }
    return true;
}

} // namespace

extern "C" const W2UBattleHandlerExport* W2U_BattleModules_Resolve(
    W2UBattleMechanicKind kind,
    u16 id)
{
    const W2UBattleMechanicRoute* route = FindRoute(kind, id);
    if (!route || !LoadModule(route->module, kind, id)) {
        return 0;
    }
    return FindApiEntry(sModuleRecords[route->module].api, kind, id);
}

extern "C" const W2UBattleHandlerExport* W2U_BattleModules_FindLoaded(
    W2UBattleMechanicKind kind,
    u16 id)
{
    const W2UBattleMechanicRoute* route = FindRoute(kind, id);
    if (!route || route->module >= W2U_BATTLE_MODULE_COUNT ||
        sModuleRecords[route->module].state != W2U_MODULE_LOADED) {
        return 0;
    }
    return FindApiEntry(sModuleRecords[route->module].api, kind, id);
}

extern "C" bool W2U_BattleModules_IsManaged(W2UBattleMechanicKind kind, u16 id)
{
    return FindRoute(kind, id) != 0;
}

extern "C" void W2U_BattleModules_Reset()
{
    if (sResetting) {
        return;
    }
    sResetting = true;
    sRegistrationEnabled = false;

    for (u32 index = W2U_BATTLE_MODULE_COUNT; index > 0; --index) {
        W2UBattleModuleRecord* record = &sModuleRecords[index - 1];
        W2UPmcModuleHandle handle = record->handle;
        const bool loaded = record->state == W2U_MODULE_LOADED && handle;
        record->handle = 0;
        record->api = 0;
        record->expandedBytes = 0;
        record->fixedBytes = 0;
        record->state = W2U_MODULE_NOT_LOADED;
        if (loaded) {
            sPmcRuntime.unloadModule(handle);
            ++sTelemetry.unloadCount;
        }
    }

    sTelemetry.loadedModuleCount = 0;
    sTelemetry.currentChildBytes = 0;
    sTelemetry.failedModuleMask = 0;
    sTelemetry.lastFailureModuleId = W2U_NO_MODULE;
    sRegistrationEnabled = true;
    sResetting = false;
}

extern "C" void W2U_BattleModules_SetRegistrationEnabled(bool enabled)
{
    sRegistrationEnabled = enabled;
}

extern "C" const W2UBattleModuleTelemetry* W2U_BattleModules_GetTelemetry()
{
    return &sTelemetry;
}

extern "C" __attribute__((visibility("default"))) int DllMain(
    void* manager,
    void* module,
    int reason)
{
    (void)manager;
    if (reason == 1) {
        W2U_BattleModules_Reset();
        ClearBytes(&sPmcRuntime, sizeof(sPmcRuntime));
        sPmcRuntimeState = 0;
    } else if (module) {
        // PMC invokes DllMain after applying INTERNAL_RELOCATIONS, so the
        // allocation header now holds the core's post-fix size.
        sTelemetry.coreFixedBytes = ReadU32(static_cast<const u8*>(module), 4u);
        sTelemetry.lastFailureModuleId = W2U_NO_MODULE;
    }
    return 0;
}
