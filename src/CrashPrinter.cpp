#include "CrashPrinter.hpp"

// b32 THUMB_BRANCH_GFL_NetErrShow() {
//     return 0;
// }
enum DllMainReason {
    DLL_MODULE_LOAD,
    DLL_MODULE_UNLOAD
};


namespace w2u_debug {
    void DllMain(void* mgr, void* module, int reason) {
        w2u_debug::crash::InstallExceptionHandler();
    }
}
