"""Exercise the resident teardown callback, including re-entrant unloads."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class LoaderLifetime(unittest.TestCase):
    def test_actual_reset_clears_all_pointers_and_unloads_reverse_load_order(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        reset = re.search(r'extern "C" void W2U_BattleModules_Reset\(.*?^\}', source, re.M | re.S).group()
        program = r'''
#include <vector>
using u8=unsigned char;using u16=unsigned short;using u32=unsigned;
using W2UPmcModuleHandle=void*;
constexpr unsigned W2U_MAX_MODULE_RECORDS=32,W2U_BATTLE_MODULE_COUNT=30,W2U_NO_MODULE=255;
enum {W2U_MODULE_NOT_LOADED,W2U_MODULE_LOADED,W2U_MODULE_FAILED};
struct W2UBattleModuleRecord {void* handle;void* api;u32 expandedBytes,fixedBytes;u8 state,moduleId;u16 loadOrdinal;};
struct {u32 loadedModuleCount,currentChildBytes,failedModuleMask,lastFailureModuleId,unloadCount;} sTelemetry;
W2UBattleModuleRecord sModuleRecords[32];bool sResetting,sRegistrationEnabled=true;
std::vector<void*> unloaded;bool invalid;
extern "C" void W2U_BattleModules_Reset();
void unload(void* p){
 if(sRegistrationEnabled)invalid=true;
 for(auto& r:sModuleRecords)if(r.handle||r.api||r.state==W2U_MODULE_LOADED)invalid=true;
 unloaded.push_back(p);W2U_BattleModules_Reset(); // Re-entry must be a no-op.
}
struct {void (*unloadModule)(void*);} sPmcRuntime={unload};
void ClearBytes(void* p,u32 n){for(u32 i=0;i<n;++i)((u8*)p)[i]=0;}
''' + reset + r'''
int main(){
 unsigned ids[]={18,2,29};
 for(unsigned ordinal=0;ordinal<3;++ordinal){auto& r=sModuleRecords[ids[ordinal]];
  r.handle=r.api=(void*)(unsigned long)(ordinal+1);r.state=W2U_MODULE_LOADED;r.loadOrdinal=ordinal;
 }
 sModuleRecords[7].state=W2U_MODULE_FAILED;
 sTelemetry.loadedModuleCount=3;sTelemetry.currentChildBytes=8000;sTelemetry.failedModuleMask=128;
 W2U_BattleModules_Reset();
 if(invalid||unloaded!=std::vector<void*>({(void*)3,(void*)2,(void*)1})||!sRegistrationEnabled)return 1;
 if(sTelemetry.loadedModuleCount||sTelemetry.currentChildBytes||sTelemetry.failedModuleMask||sTelemetry.unloadCount!=3)return 2;
 W2U_BattleModules_Reset();if(unloaded.size()!=3||sResetting)return 3;
 sRegistrationEnabled=false;W2U_BattleModules_Reset();if(sRegistrationEnabled)return 4;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-loader-lifetime-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_registration_and_resident_unload_share_cleanup(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        load = re.search(r'^bool LoadModule\(.*?^\}', source, re.M | re.S).group()
        self.assertLess(load.index("if (!sRegistrationEnabled)"), load.index("W2U_MODULE_LOADED"))
        dllmain = source[source.index('int DllMain('):]
        self.assertIn("W2U_BattleState_OnBattleExit();", dllmain)
        self.assertIn("sRegistrationEnabled = false;", dllmain)
        for name in ("test-move-handlers.py", "test-battle-interactions.py"):
            script = (ROOT / "tests/battle/scripts" / name).read_text()
            self.assertIn('default=ROOT / "build/White2Upgrade.nds"', script)


if __name__ == "__main__":
    unittest.main()
