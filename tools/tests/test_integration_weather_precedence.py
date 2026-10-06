"""Compile the real combined weather callbacks against independent state oracles."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class WeatherPrecedence(unittest.TestCase):
    def test_strong_weather_presence_suppression_lifetime_and_invalid_inputs(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_strong_weather.cpp").read_text()
        weather = (ROOT / "src/pokeweb_gameplay/w2u_weather.cpp").read_text()
        pieces = [re.search(r"struct KindInfo \{.*?^\};", source, re.M | re.S).group(),
                  re.search(r"const KindInfo kKinds\[.*?^\};", source, re.M | re.S).group(),
                  re.search(r"struct StrongWeatherState \{.*?^\};", source, re.M | re.S).group()]
        for name in ("W2U_StrongWeather_Reset", "W2U_StrongWeather_FirstHolder",
                     "W2U_StrongWeather_Negated", "W2U_StrongWeather_Start", "W2U_StrongWeather_End",
                     "THUMB_BRANCH_167_0x21A767C"):
            pieces.append(re.search(r'extern "C" (?:void|u32|bool|b32) '+name+r'\(.*?^\}', source, re.M | re.S).group())
        can_change = re.search(r'extern "C" b32 W2U_Weather_CanChange\(.*?^\}', weather, re.M | re.S).group()
        constants = "\n".join(line for line in (ROOT / "include/w2u_strong_weather.h").read_text().splitlines()
                              if re.match(r"#define W2U_(?:WEATHER_VIEW|EFFECT_|STD_MSG_)", line))
        preamble = r'''
#include <cstdarg>
#include <initializer_list>
#define W2U_WEATHER_SNOW 8u
using u32=unsigned;using u16=unsigned short;using b32=int;using WEATHER=unsigned;using ServerCommandID=unsigned;
enum {W2U_STRONG_WEATHER_NONE,W2U_STRONG_WEATHER_WINDS,W2U_STRONG_WEATHER_RAIN,W2U_STRONG_WEATHER_SUN,W2U_STRONG_WEATHER_KIND_COUNT};
enum {SCID_WEATHER_START=63,SCID_WEATHER_END=64,SCID_ABILITY_POPUP_IN=87,SCID_ABILITY_POPUP_OUT=88,
 ENGINE_SUN=1,ENGINE_RAIN=2,TURNS_PERMANENT=255,NO_TYPE=255,TYPE_FIRE=9,TYPE_WATER=10,
 VAR_WEATHER_NEGATED=65,EVENT_WEATHER_CHECK=122,WEATHER_HAIL=3,WEATHER_SANDSTORM=4,SNOW=8,BATTLE_MAX_SLOTS=24};
struct ServerFlow {unsigned simulationCounter;void* serverCommandQueue;};
unsigned nativeWeather,nativeTurns,starts,ends,lastView,lastMessage;bool sSnow,negated;
unsigned BattleField_GetWeather(){return nativeWeather;}unsigned BattleField_GetWeatherTurn(){return nativeTurns;}
unsigned FieldWeather(){return nativeWeather;}
void FieldSetWeather(unsigned w,unsigned t){nativeWeather=w;nativeTurns=t;}
void ChangeWeatherAfter(ServerFlow*,unsigned w){if(w!=3)sSnow=false;}
void PushStdMessage(ServerFlow*,unsigned,unsigned m){lastMessage=m;}
void ServerDisplay_AddCommon(void*,unsigned command,...){
 va_list args;va_start(args,command);unsigned value=va_arg(args,unsigned);va_end(args);
 if(command==63){++starts;lastView=value;}if(command==64){++ends;lastView=value;}
}
void BattleEventVar_Push(){}void BattleEventVar_Pop(){}
void BattleEventVar_SetRewriteOnceValue(unsigned,unsigned){}
void BattleEvent_CallHandlers(ServerFlow*,unsigned){}
int BattleEventVar_GetValue(unsigned){return negated;}
'''
        program = preamble + constants + "\n" + pieces[0] + "\n" + pieces[1] + "\n" + pieces[2] + "\nStrongWeatherState sState;\n" + can_change + "\n" + "\n".join(pieces[3:]) + r'''
int main(){
 ServerFlow sf={0,nullptr};
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
  W2U_StrongWeather_End(&sf,0);if(sState.kind!=kind||ends)return 7;
  W2U_StrongWeather_End(&sf,12);if(sState.kind||ends!=1||nativeWeather||lastView!=kind+4)return 8;
 }
 W2U_StrongWeather_Reset();starts=0;nativeWeather=2;nativeTurns=255;negated=false;sSnow=false;
 if(!THUMB_BRANCH_167_0x21A767C(&sf,8,5))return 9;
 for(unsigned bad:{0u,4u,32u})W2U_StrongWeather_Start(&sf,0,bad);
 W2U_StrongWeather_Start(nullptr,0,1);W2U_StrongWeather_Start(&sf,24,1);
 sf.simulationCounter=1;W2U_StrongWeather_Start(&sf,0,1);
 if(starts||sState.kind||nativeWeather!=2)return 10;
 for(unsigned bad:{0u,4u,32u})if(W2U_StrongWeather_FirstHolder(bad))return 11;
 sf.simulationCounter=0;W2U_StrongWeather_Start(&sf,0,1);
 sf.simulationCounter=1;W2U_StrongWeather_End(&sf,0);if(sState.kind!=1)return 12;
 for(unsigned bad:{5u,6u,7u,9u,255u})if(THUMB_BRANCH_167_0x21A767C(&sf,bad,5))return 13;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-weather-precedence-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
