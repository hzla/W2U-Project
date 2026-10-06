"""Execute the actual callbacks against independent fraction/event oracles."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pokeweb_gameplay/w2u_moves.cpp"


class RecoveryAndHaze(unittest.TestCase):
    def run_program(self, program):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_shore_up_floors_exact_fractions_without_changing_native_recovery(self):
        callback = re.search(r'extern "C" u32 THUMB_BRANCH_ServerEvent_CalcMoveHealAmount\(.*?^\}', SOURCE.read_text(), re.M | re.S).group()
        program = r'''
using u32=unsigned;using u64=unsigned long long;using MOVE_ID=unsigned;struct ServerFlow{};struct BattleMon{};
enum {MVDATA_HEAL,VAR_MON_ID,VAR_RATIO,VAR_MOVE_ID,EVENT_RECOVER_HP,VALUE_MAX_HP,MOVE_SHORE_UP=659};
constexpr unsigned W2U_RECOVER_RATIO_TWO_THIRDS=2732;
unsigned hp,ratio;unsigned PML_MoveGetParam(unsigned,unsigned){return 50;}
unsigned BattleMon_GetID(BattleMon*){return 0;}void BattleEventVar_Push(){}void BattleEventVar_Pop(){}
void BattleEventVar_SetConstValue(unsigned,unsigned){}void BattleEventVar_SetValue(unsigned,unsigned){}
unsigned BattleEventVar_GetValue(unsigned){return ratio;}void BattleEvent_CallHandlers(ServerFlow*,unsigned){}
unsigned BattleMon_GetValue(BattleMon*,unsigned){return hp;}
unsigned fixed_round(unsigned x,unsigned q){return (x*q+2048)/4096;}
unsigned MultiplyValueByRatio(unsigned x,unsigned q){return (x*q+50)/100;}
''' + callback + r'''
int main(){ServerFlow sf;BattleMon mon;for(hp=1;hp<=2048;++hp){
 for(unsigned q:{2048u,2732u}){ratio=q;unsigned exact=q==2048?hp/2:hp*2/3;if(!exact)exact=1;
 if(THUMB_BRANCH_ServerEvent_CalcMoveHealAmount(&sf,659,&mon)!=exact)return 1;}
 ratio=0;if(THUMB_BRANCH_ServerEvent_CalcMoveHealAmount(&sf,105,&mon)!=(hp+1)/2)return 2;
}return 0;}
'''
        self.run_program("#include <initializer_list>\n" + program)

    def test_haze_uses_native_field_event_and_owner_only(self):
        callback = re.search(r'static void HandlerFreezyFrost\(.*?^\}', SOURCE.read_text(), re.M | re.S).group()
        program = r'''
using u32=unsigned;struct BattleEventItem{};struct ServerFlow{};
enum{VAR_ATTACKING_MON,EVENT_CALL_FIELD_EFFECT=0x9e,EVENT_UNCATEGORIZED_MOVE=0xa0,MOVE_HAZE=114};
struct BattleEventHandlerTableEntry{unsigned eventType;void(*handler)(BattleEventItem*,ServerFlow*,unsigned,unsigned*);};
unsigned owner,calls,lookups;bool missing;
unsigned BattleEventVar_GetValue(unsigned){return owner;}
void native(BattleEventItem*,ServerFlow*,unsigned,unsigned*){++calls;}
BattleEventHandlerTableEntry table[]={{EVENT_UNCATEGORIZED_MOVE,nullptr},{EVENT_CALL_FIELD_EFFECT,native}};
BattleEventHandlerTableEntry* get(unsigned* count){*count=2;return table;}
using W2UNativeMoveGetter=BattleEventHandlerTableEntry*(*)(unsigned*);
W2UNativeMoveGetter W2U_FindNativeMoveGetter(unsigned id){if(id!=MOVE_HAZE)return nullptr;++lookups;return missing?nullptr:get;}
''' + callback + r'''
int main(){ServerFlow sf;owner=0;HandlerFreezyFrost(nullptr,&sf,12,nullptr);if(calls||lookups)return 1;
 HandlerFreezyFrost(nullptr,&sf,0,nullptr);if(calls!=1||lookups!=1)return 2;
 missing=true;HandlerFreezyFrost(nullptr,&sf,0,nullptr);return calls!=1||lookups!=2;}
'''
        self.run_program(program)


if __name__ == "__main__":
    unittest.main()
