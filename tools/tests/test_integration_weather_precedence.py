"""Compile the real combined weather callbacks against independent state oracles."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class WeatherPrecedence(unittest.TestCase):
    def test_strong_weather_presence_suppression_lifetime_and_invalid_inputs(self):
        # The server side is C (src/mechanics/resident/strong_weather.c), whole; the injection build's weather-change
        # hook (w2u_strong_weather.cpp) and Snow's check (w2u_weather.cpp) around it
        resident = (ROOT / "src/mechanics/resident/strong_weather.c").read_text()
        resident = "\n".join(line for line in resident.splitlines() if not line.startswith("#include"))
        source = (ROOT / "src/pokeweb_gameplay/w2u_strong_weather.cpp").read_text()
        weather = (ROOT / "src/pokeweb_gameplay/w2u_weather.cpp").read_text()
        hook = re.search(r'extern "C" b32 THUMB_BRANCH_167_0x21A767C\(.*?^\}', source, re.M | re.S).group()
        can_change = re.search(r'extern "C" b32 W2U_Weather_CanChange\(.*?^\}', weather, re.M | re.S).group()
        ids = "\n".join(line for line in (ROOT / "include/w2u/strong_weather_ids.h").read_text().splitlines()
                        if line.startswith("#define W2U_") and "_H" not in line.split()[1][-2:])
        preamble = r'''
#include <cstdarg>
#include <initializer_list>
#define W2U_WEATHER_SNOW 8u
typedef unsigned u32;typedef unsigned short u16;typedef unsigned char u8;typedef int s32;typedef int b32;
typedef unsigned WEATHER;typedef unsigned ServerCommandID;
enum {WEATHER_NONE=0,WEATHER_SUN=1,WEATHER_RAIN=2,WEATHER_HAIL=3,WEATHER_SANDSTORM=4,
 TYPE_FIRE=9,TYPE_WATER=10,TYPE_NORMAL=0,BATTLE_MAX_MON_ID=24,VAR_WEATHER_NEGATED=65,EVENT_WEATHER_NEGATION=122,
 HANDLER_CMD_MESSAGE=4,HANDLER_STR_STD=1,SERVER_CMD_STD_MESSAGE=0x5A,W2U_EFF_IMMUNE=0,W2U_EFF_1_4=1,W2U_EFF_4=5,
 W2U_EFF_8=7,SNOW=8};
struct BtlServerFlow {unsigned simulationDepth;};typedef BtlServerFlow ServerFlow;
struct BattleMon {};
struct BtlFlowMoveParam {u16 move;u16 originalMove;u16 userType;u8 type;u8 unk07;u32 category;};
struct BattleHandlerString {u16 message;};struct BattleHandlerMessageParam {u32 header;BattleHandlerString string;};
unsigned nativeWeather,nativeTurns,starts,ends,lastView,lastMessage,afterCalls;bool sSnow,negated;
unsigned BattleField_GetWeather(){return nativeWeather;}unsigned BattleField_GetWeatherTurn(){return nativeTurns;}
unsigned GetFieldWeather(){return nativeWeather;}
void FieldStatusSetWeather(unsigned w,unsigned t){nativeWeather=w;nativeTurns=t;}
void ServerControl_ChangeWeatherAfter(ServerFlow*,unsigned w){++afterCalls;if(w!=3)sSnow=false;}
static BattleHandlerMessageParam sWork;
void* BattleHandler_PushWork(ServerFlow*,unsigned,unsigned){return &sWork;}
void BattleHandler_StrSetup(BattleHandlerString* s,unsigned,u16 m){s->message=m;}
void BattleHandler_PopWork(ServerFlow*,void* w){lastMessage=((BattleHandlerMessageParam*)w)->string.message;}
void* W2U_ServerQueue(ServerFlow*){return nullptr;}
b32 W2U_IsSimulating(ServerFlow* f){return f->simulationDepth!=0;}
b32 W2U_IsStatusMove(u16 move){return move==261;}   // Will-O-Wisp
void ServerDisplay_AddCommon(void*,unsigned command,...){
 va_list args;va_start(args,command);unsigned value=va_arg(args,unsigned);va_end(args);
 if(command==63){++starts;lastView=value;}if(command==64){++ends;lastView=value;}
}
void ServerDisplay_AddMessageImpl(void*,unsigned,...){}
void BattleEventVar_Push(unsigned){}void BattleEventVar_Pop(unsigned){}
void BattleEventVar_SetRewriteOnceValue(unsigned,unsigned){}
void BattleEvent_CallHandlers(ServerFlow*,unsigned){}
int BattleEventVar_GetValue(unsigned){return negated;}
// The AI's damage estimate: what CalcDamage was asked, and the true grade W2U's effectiveness gives
unsigned calcEffectiveness,trueGrade;
b32 ServerEvent_CalcDamage(ServerFlow*,BattleMon*,BattleMon*,const BtlFlowMoveParam*,u32 e,u32,b32,b32,u16* d)
{calcEffectiveness=e;*d=e?100:1;return 1;}
u32 W2U_CheckMoveEffectiveness(ServerFlow*,BattleMon*,BattleMon*,const BtlFlowMoveParam*,b32){return trueGrade;}
u32 W2U_AIEffectiveness(u32 e){return e==7||e==8?5:e==6?1:e;}
'''
        program = (preamble + ids + "\n" + resident + "\n" + can_change + "\n" + hook + r'''
int main(){
 ServerFlow sf={0};
 for(unsigned kind=1;kind<4;++kind){
  W2U_StrongWeather_Reset();nativeWeather=3;nativeTurns=4;sSnow=true;starts=ends=0;
  W2U_StrongWeather_Start(&sf,0,kind);
  unsigned engine=kind==1?0:kind==2?2:1;
  if(nativeWeather!=engine||nativeTurns!=(engine?255u:0u)||sSnow||starts!=1||lastView!=kind+4)return 1;
  W2U_StrongWeather_Start(&sf,12,kind);if(starts!=1)return 2;
  for(negated=false;!negated;negated=true){
   if(W2U_StrongWeather_Negated(&sf))return 3;
   if(THUMB_BRANCH_167_0x21A767C(&sf,8,5))return 4;
  }
  if(!W2U_StrongWeather_Negated(&sf)||THUMB_BRANCH_167_0x21A767C(&sf,8,5))return 5;
  if(lastMessage!=(kind==1?203u:kind==2?206u:210u))return 6;
  W2U_StrongWeather_End(&sf,0);if(W2U_StrongWeather_Kind()!=kind||ends)return 7;
  W2U_StrongWeather_End(&sf,12);if(W2U_StrongWeather_Kind()||ends!=1||nativeWeather||lastView!=kind+4)return 8;
 }
 W2U_StrongWeather_Reset();starts=0;nativeWeather=2;nativeTurns=255;negated=false;sSnow=false;
 if(!THUMB_BRANCH_167_0x21A767C(&sf,8,5))return 9;
 for(unsigned bad:{0u,4u,32u})W2U_StrongWeather_Start(&sf,0,bad);
 W2U_StrongWeather_Start(nullptr,0,1);W2U_StrongWeather_Start(&sf,24,1);
 sf.simulationDepth=1;W2U_StrongWeather_Start(&sf,0,1);
 if(starts||W2U_StrongWeather_Kind()||nativeWeather!=2)return 10;
 for(unsigned bad:{0u,4u,32u})if(W2U_StrongWeather_FirstHolder(bad))return 11;
 sf.simulationDepth=0;W2U_StrongWeather_Start(&sf,0,1);
 sf.simulationDepth=1;W2U_StrongWeather_End(&sf,0);if(W2U_StrongWeather_Kind()!=1)return 12;
 for(unsigned bad:{5u,6u,7u,9u,255u})if(THUMB_BRANCH_167_0x21A767C(&sf,bad,5))return 13;
 // The AI's estimate in heavy rain: a damaging Fire move as a hit that doesn't affect (not 0: the scripts take 0 for a
 // status move); Will-O-Wisp, Water, or the rain negated are left alone; x4 from a x8 grade gets the true grade back
 sf.simulationDepth=0;W2U_StrongWeather_Reset();W2U_StrongWeather_Start(&sf,0,2);negated=false;
 BattleMon a,d;u16 damage;BtlFlowMoveParam fire={53,53,0,TYPE_FIRE},wisp={261,261,0,TYPE_FIRE},water={57,57,0,TYPE_WATER};
 W2U_AICalcDamage(&sf,&a,&d,&fire,5,0x1000,0,0,&damage);if(calcEffectiveness!=0||damage!=1)return 14;
 if(!W2U_StrongWeatherStopsMove(&sf,&fire)||W2U_StrongWeatherStopsMove(&sf,&wisp)||W2U_StrongWeatherStopsMove(&sf,&water))return 15;
 trueGrade=3;W2U_AICalcDamage(&sf,&a,&d,&water,3,0x1000,0,0,&damage);if(calcEffectiveness!=3)return 16;
 negated=true;W2U_AICalcDamage(&sf,&a,&d,&fire,3,0x1000,0,0,&damage);if(calcEffectiveness!=3)return 17;
 negated=false;trueGrade=7;W2U_AICalcDamage(&sf,&a,&d,&water,5,0x1000,0,0,&damage);if(calcEffectiveness!=7)return 18;
 trueGrade=5;W2U_AICalcDamage(&sf,&a,&d,&water,5,0x1000,0,0,&damage);if(calcEffectiveness!=5)return 19;
 return 0;
}
''')
        with tempfile.TemporaryDirectory(prefix="w2u-weather-precedence-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
