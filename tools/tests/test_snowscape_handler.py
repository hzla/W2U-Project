"""Logical snow must not change ordinary Hail or leak into native tables."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class SnowscapeHandler(unittest.TestCase):
    def test_compiled_weather_lifetime_transport_work_and_defense(self):
        body = (ROOT / "src/pokeweb_gameplay/w2u_weather.cpp").read_text()
        body = "\n".join(line for line in body.splitlines() if not line.startswith("#include"))
        preamble = r'''
#include <cstdarg>
typedef unsigned u32, WEATHER, ServerCommandID, BattleHandlerEffect;
typedef unsigned char u8; typedef int b32;
struct HandlerParam_Header {u32 flags;};
struct HandlerParam_StrParams {u32 words[10];};
struct ServerCommandQueue {};
struct BattleEventItem {}; struct BattleMon {unsigned types[2],hp,id;bool fainted;};
struct BattleActionParam {unsigned type;struct {unsigned moveID;} baFight;};
struct ActionOrderWork {BattleMon* battleMon;BattleActionParam action;bool done;};
struct ServerFlow {unsigned simulationCounter;ServerCommandQueue* serverCommandQueue;unsigned numActOrder;ActionOrderWork actionOrderWork[6];};
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof(a[0]))
enum {WEATHER_HAIL=3,WEATHER_SANDSTORM=4,TYPE_ICE=14,TYPE_ROCK=5,TYPE_STEEL=8,TYPE_GROUND=4,
 VAR_WEATHER=57,VAR_ATTACKING_MON=3,VAR_EFFECT_TURN_COUNT=36,VAR_MOVE_CATEGORY=26,VAR_DEFENDING_MON=4,VAR_RATIO=53,
 EVENT_MOVE_WEATHER_TURN_COUNT=124,SPLIT_PHYSICAL=1,VALUE_MAX_HP=14,MOVE_CHILLY_RECEPTION=881,SCID_SetMessage=20};
unsigned weather,turns,effective,vars[64],extended,queued,allocations,available=1,ratio=4096,msg;
unsigned char workBytes[48]; BattleMon mon={{14,14},175,0,false};
unsigned BattleAction_GetAction(BattleActionParam* a){return a->type;}
unsigned BattleMon_GetID(BattleMon* m){return m->id;}
bool BattleMon_IsFainted(BattleMon* m){return m->fainted;}
unsigned cues,cueSlots;
void ServerDisplay_AddMessageImpl(ServerCommandQueue*,unsigned cmd,unsigned text,unsigned slot,unsigned arg){
 if(cmd!=20||text!=1358||slot>=24||arg!=0xffff0000u)__builtin_trap();++cues;cueSlots|=1u<<slot;
}
void BattleEventVar_Push() {} void BattleEventVar_Pop() {}
void BattleEventVar_SetConstValue(unsigned id,unsigned v){vars[id]=v;}
void BattleEventVar_SetValue(unsigned id,unsigned v){vars[id]=v;}
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEventVar_MulValue(unsigned id,unsigned v){if(id!=53)__builtin_trap();ratio=ratio*v/4096;}
void BattleEvent_CallHandlers(ServerFlow*,unsigned id){if(id!=124||vars[57]!=3||vars[3]>23)__builtin_trap();vars[36]=extended;}
void* BattleHandler_PushWork(ServerFlow*,unsigned effect,unsigned){if(effect!=29)__builtin_trap();++allocations;return available?workBytes:0;}
void BattleHandler_PopWork(ServerFlow*,void*){++queued;}
void BattleHandler_StrClear(HandlerParam_StrParams* p){for(auto& n:p->words)n=0;}
unsigned ServerEvent_GetWeather(ServerFlow*){return effective;}
BattleMon* Handler_GetBattleMon(ServerFlow*,unsigned id){return id==12?&mon:0;}
unsigned BattleMon_GetValue(BattleMon* m,unsigned){return m->hp;}
extern "C" unsigned BattleField_GetWeather(){return weather;}
extern "C" unsigned BattleField_GetWeatherTurn(){return turns;}
extern "C" void BattleField_SetWeather(unsigned w,unsigned t){weather=w;turns=t;}
extern "C" int BattleMon_HasType(BattleMon* m,unsigned t){return m->types[0]==t||m->types[1]==t;}
extern "C" void ServerControl_ChangeWeatherAfter(ServerFlow*,unsigned w){if(w>4)__builtin_trap();}
unsigned command,logical,duration;
void ServerDisplay_AddCommon(ServerCommandQueue*,unsigned c,...){command=c;va_list a;va_start(a,c);logical=va_arg(a,unsigned);if(c==63)duration=va_arg(a,unsigned);va_end(a);}
extern "C" void BattleView_StartMessageStd(void*,unsigned m,const void*){msg=m;}
extern "C" void THUMB_BRANCH_LINK_ClientWeatherStart_0x60(void*,unsigned,const void*);
extern "C" void THUMB_BRANCH_LINK_ClientWeatherEnd_0x4A(void*,unsigned,const void*);
extern "C" unsigned ClientWeatherStart_Original(void*,int*,const unsigned* a){if(a[0]>4)__builtin_trap();THUMB_BRANCH_LINK_ClientWeatherStart_0x60(0,88,0);return 17;}
extern "C" unsigned ClientWeatherEnd_Original(void*,int*,const unsigned* a){if(a[0]>4)__builtin_trap();THUMB_BRANCH_LINK_ClientWeatherEnd_0x4A(0,92,0);return 19;}
'''
        checks = r'''
int main(){
 ServerCommandQueue q;ServerFlow f={0,&q};
 for(unsigned snow=0;snow<2;++snow) for(weather=0;weather<5;++weather)
 for(unsigned incoming=0;incoming<8;++incoming) for(turns=4;turns<=255;turns+=251) {
   sSnow=snow;unsigned current=snow&&weather==3?5:weather;
   for(unsigned next:{5u,255u}){
     bool expected=incoming<=5&&(current!=incoming||(next==255&&turns!=255));
     if(bool(THUMB_BRANCH_ServerControl_ChangeWeatherCheck(&f,incoming,next))!=expected)return 1;
   }
 }
 weather=0;turns=0;sSnow=0;
 for(extended=0;extended<5;++extended){
   if(!W2U_Weather_QueueSnow(&f,0))return 2;
   auto* w=(WeatherWork*)workBytes;
   if(w->weather!=5||w->turns!=(extended==3?8:5)||w->airLock||weather||sSnow)return 3;
 }
 for(unsigned bad=0;bad<4;++bad){
   unsigned n=queued;f.simulationCounter=bad==0;available=bad!=1;turns=bad==2?255:0;
   if(W2U_Weather_QueueSnow(&f,bad==3?24:0)||queued!=n)return 4;
 }
 f.simulationCounter=0;available=1;turns=0;
 THUMB_BRANCH_ServerControl_ChangeWeatherCore(&f,5,8);
 if(weather!=3||turns!=8||!sSnow||logical!=5||duration!=8||command!=63)return 5;
 if(W2U_Weather_QueueSnow(&f,0))return 6;
 for(effective=0;effective<5;++effective) for(unsigned type=0;type<18;++type)
 for(unsigned category=1;category<3;++category){
   mon.types[0]=mon.types[1]=type;vars[26]=category;vars[4]=12;ratio=4096;
   W2U_Weather_Defense(0,&f,0,0);
   if(ratio!=(effective==3&&type==14&&category==1?6144:4096))return 7;
 }
 for(unsigned type=0;type<18;++type){
   mon.types[0]=mon.types[1]=type;
   if(THUMB_BRANCH_LINK_167_0x21A8898(&mon,3))return 8;
 }
 THUMB_BRANCH_LINK_167_0x21A8830(&q,64,3);if(logical!=5)return 9;
 vars[57]=0;W2U_Weather_AfterChange(0,&f,0,0);if(sSnow)return 10;
 unsigned args[2]={5,8};int seq=1;
 if(THUMB_BRANCH_ClientWeatherStart(0,&seq,args)!=17||msg!=221||sClientSnowMessage)return 11;
 if(THUMB_BRANCH_ClientWeatherEnd(0,&seq,args)!=19||msg!=222||sClientSnowMessage)return 12;
 args[0]=3;THUMB_BRANCH_ClientWeatherStart(0,&seq,args);if(msg!=88)return 13;
 THUMB_BRANCH_ClientWeatherEnd(0,&seq,args);if(msg!=92)return 14;
 mon.types[0]=mon.types[1]=0;
 if(THUMB_BRANCH_LINK_167_0x21A8898(&mon,3)!=10)return 15;
 THUMB_BRANCH_ServerControl_ChangeWeatherCore(&f,5,5);THUMB_BRANCH_ServerControl_ChangeWeatherCore(&f,3,5);
 if(sSnow||logical!=3||THUMB_BRANCH_LINK_167_0x21A8898(&mon,3)!=10)return 16;
 W2U_Weather_Reset();if(sSnow||sClientSnowMessage)return 17;
 // Only genuine pending selections announce a joke; scans and later turns
 // must not duplicate or omit it. Called moves do not have this selection.
 BattleMon other={{0,0},100,12,false};
 f.numActOrder=6;
 f.actionOrderWork[0]={&mon,{1,{881}},false};
 f.actionOrderWork[1]={&other,{1,{881}},false};
 f.actionOrderWork[2]={&mon,{1,{33}},false};
 f.actionOrderWork[3]={&mon,{2,{881}},false};
 f.actionOrderWork[4]={&mon,{1,{881}},true};
 f.actionOrderWork[5]={nullptr,{1,{881}},false};
 W2U_Weather_PrepareChillyReception(&f,0);W2U_Weather_PrepareChillyReception(&f,0);
 if(cues!=2||cueSlots!=4097)return 18;
 W2U_Weather_EndTurn();W2U_Weather_PrepareChillyReception(&f,1);if(cues!=3||sChillyCue!=4096)return 19;
 W2U_Weather_Reset();f.simulationCounter=1;W2U_Weather_PrepareChillyReception(&f,0);if(cues!=3)return 20;
 f.simulationCounter=0;mon.fainted=true;other.id=24;W2U_Weather_PrepareChillyReception(&f,0);if(cues!=3)return 21;
 mon.fainted=false;other.id=12;f.numActOrder=99;W2U_Weather_PrepareChillyReception(&f,0);if(cues!=5)return 22;
 return 0;
}
'''
        source = "#include <initializer_list>\n" + preamble + body + checks
        with tempfile.TemporaryDirectory(prefix="w2u-snow-") as folder:
            output = Path(folder) / "check"
            subprocess.run(["c++","-std=c++11","-x","c++","-o",str(output),"-"],input=source,text=True,check=True)
            subprocess.run([str(output)],check=True)

    def test_clean_us_w2_b2_weather_call_and_trampoline_contracts(self):
        import capstone
        import ndspy.rom
        import struct
        md = capstone.Cs(capstone.CS_ARCH_ARM,capstone.CS_MODE_THUMB)
        for filename,delta in (("cleanwhite2.nds",0),("cleanblack2.nds",-64)):
            path = ROOT.parent / "Port-Pokeweb" / filename
            if not path.exists(): self.skipTest("Optional clean-US ROMs required")
            o = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
            for address,destination in ((0x21a8830,0x21b1474),(0x21a8898,0x21bd428),
                                        (0x21b790c,0x21d0290),(0x21b7976,0x21d0290)):
                at=address+delta-o.ramAddress
                ins=next(md.disasm(o.data[at:at+4],address+delta))
                self.assertEqual((ins.mnemonic,ins.op_str),("bl",f"#{destination+delta:#x}"))
            for address,hex_bytes in ((0x21b78ac,"70b5061c10680d1c"),(0x21b792c,"38b50d1c041c2868")):
                at=address+delta-o.ramAddress
                self.assertEqual(o.data[at:at+8].hex(),hex_bytes)
            self.assertEqual(struct.unpack_from("<I",o.data,0x21d59f8+delta-o.ramAddress)[0],0x21dd928+delta)


if __name__ == "__main__": unittest.main()
