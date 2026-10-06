"""Weather and native party-choice transactions remain independent."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class ChillyReceptionHandler(unittest.TestCase):
    def test_compiled_weather_then_pivot_with_no_fake_recipient(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = source[source.index("static void HandlerChillyReception("):source.index("static BattleEventHandlerTableEntry ChillyReceptionHandlers")]
        preamble = r'''
typedef unsigned u32;typedef unsigned char u8;
struct BattleEventItem {};struct ServerFlow {unsigned simulationCounter;};
struct Message {unsigned words[10];};
struct HandlerParam_Switch {unsigned header;Message preStr,exStr;u8 pokeID,intrDisable,pad[2];};
enum {VAR_ATTACKING_MON=3,EFFECT_SWITCH=41,EFFECT_FORCE_MOVE_SUCCESS=60};
unsigned owner=0,weather,bench,reserved,available,success,queued,order,weatherOrder,pivotOrder;
HandlerParam_Switch pivot;
unsigned BattleEventVar_GetValue(unsigned id){if(id!=3)__builtin_trap();return owner;}
bool W2U_Weather_QueueSnow(ServerFlow*,unsigned slot){if(slot!=owner)__builtin_trap();weatherOrder=++order;return weather;}
unsigned Handler_GetFightEnableBenchPokeNum(ServerFlow*,unsigned){return bench;}
bool Handler_CheckReservedMemberChangeAction(ServerFlow*){return reserved;}
void* BattleHandler_PushWork(ServerFlow*,unsigned effect,unsigned slot){if(effect!=41||slot!=owner)__builtin_trap();pivotOrder=++order;return available?&pivot:0;}
void BattleHandler_StrClear(Message* m){for(auto& n:m->words)n=0;}
void BattleHandler_PopWork(ServerFlow*,void* p){if(p!=&pivot)__builtin_trap();++queued;}
void BattleHandler_PushRun(ServerFlow*,unsigned effect,unsigned slot){if(effect!=60||slot!=owner)__builtin_trap();++success;}
'''
        checks = r'''
int main(){
 ServerFlow flow={0};
 for(weather=0;weather<2;++weather)for(bench=0;bench<2;++bench)
 for(reserved=0;reserved<2;++reserved)for(available=0;available<2;++available){
   order=weatherOrder=pivotOrder=success=queued=0;
   pivot.header=0;for(auto& n:pivot.preStr.words)n=99;for(auto& n:pivot.exStr.words)n=99;
   HandlerChillyReception(0,&flow,0,0);
   const bool switched=bench&&reserved&&available;
   if(success!=bool(weather||switched)||queued!=switched||weatherOrder!=1)return 1;
   if(switched){
     if(pivotOrder!=2||pivot.pokeID||pivot.intrDisable)return 2;
     for(auto n:pivot.preStr.words)if(n)return 3;
     for(auto n:pivot.exStr.words)if(n)return 4;
   }
 }
 for(unsigned mode=0;mode<3;++mode){
   order=success=queued=0;flow.simulationCounter=mode==0;owner=mode==1?12:0;
   HandlerChillyReception(0,mode==2?nullptr:&flow,0,0);
   if(order||success||queued)return 5;
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-chilly-") as folder:
            executable = Path(folder) / "check"
            subprocess.run(["c++","-std=c++11","-x","c++","-o",str(executable),"-"],
                           input=preamble+body+checks,text=True,check=True)
            subprocess.run([str(executable)],check=True)

    def test_preparation_resets_in_resident_turn_tracker_not_guard_child(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        self.assertEqual(source.count("W2U_Weather_EndTurn();"),1)
        start = source.index('extern "C" void HandlerFieldTransientMoveStateTurnCheckDone(')
        end = source.index("#if !defined(W2U_BATTLE_CHILD)",start)
        self.assertIn("W2U_Weather_EndTurn();",source[start:end])


if __name__ == "__main__": unittest.main()
