#ifndef __W2U_PMC_RUNTIME_H
#define __W2U_PMC_RUNTIME_H

#include "swantypes.h"

typedef void* W2UPmcModuleHandle;

typedef void* (*W2UPmcAllocModuleMemoryFunc)(u32 size);
typedef void (*W2UPmcFreeModuleMemoryFunc)(W2UPmcModuleHandle memory);
typedef W2UPmcModuleHandle (*W2UPmcLoadModuleFunc)(void* data);
typedef void (*W2UPmcStartModuleFunc)(W2UPmcModuleHandle handle);
typedef void* (*W2UPmcGetProcAddressFunc)(W2UPmcModuleHandle handle, const char* name);
typedef void (*W2UPmcUnloadModuleFunc)(W2UPmcModuleHandle handle);

struct W2UPmcRuntimeApi {
    W2UPmcAllocModuleMemoryFunc allocModuleMemory;
    W2UPmcFreeModuleMemoryFunc freeModuleMemory;
    W2UPmcLoadModuleFunc loadModule;
    W2UPmcStartModuleFunc startModule;
    W2UPmcGetProcAddressFunc getProcAddress;
    W2UPmcUnloadModuleFunc unloadModule;
};

#endif
