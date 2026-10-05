"""Revival transactions use native work and never ordinary switch-in work."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class RevivalBlessingHandler(unittest.TestCase):
    def test_compiled_server_transaction(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_revival.cpp").read_text()
        names = ("W2U_Revival_Reset", "FaintedMember", "W2U_GetBattlePartyOwner", "W2U_Revival_CanUse",
                 "W2U_Revival_Begin", "W2U_Revival_Resume")
        functions = "\n".join(re.search(r'(?:static|extern "C") [^\n]+ ' + name + r'\(.*?^\}', text, re.S | re.M).group() for name in names)
        source = r'''
typedef unsigned u32;typedef unsigned short u16;typedef unsigned char u8;typedef unsigned b32;
struct MainModule{};struct BtlServerWk{};
struct BattleMon{unsigned slot,hp,maxHp;};struct BattleParty{BattleMon* members[6];u8 memberCount;};
struct PokeCon{BattleParty party[4];};
struct ServerFlow{PokeCon* pokeCon;MainModule* mainModule;BtlServerWk* server;unsigned simulationCounter,flowResult;};
struct HandlerParam_Header{u32 flags;};struct HandlerParam_StrParams{u32 type,id,arg;};
struct RevivalWork{HandlerParam_Header header;u8 pokeID,padding;u16 recoverHP;HandlerParam_StrParams exStr;};
enum BattleHandlerEffect{EFFECT_FORCE_MOVE_SUCCESS=33};enum{VALUE_MAX_HP=14};
struct RevivalPending{ServerFlow* flow;u8 owner,positionIndex;};static RevivalPending sRevival;
unsigned requests,requestPos,forceSuccess,pushes,records,forwarded,reserved=1,pos=0,owner=0,index=0;RevivalWork work;
BattleParty* PokeCon_GetBattleParty(PokeCon* c,unsigned p){return &c->party[p];}
BattleMon* BattleParty_GetPartyMember(BattleParty* p,unsigned i){return p->members[i];}
bool BattleMon_IsFainted(BattleMon* m){return !m->hp;}
unsigned BattleMon_GetID(BattleMon* m){return m->slot;}
unsigned BattleMon_GetValue(BattleMon* m,unsigned){return m->maxHp;}
unsigned Handler_CheckReservedMemberChangeAction(ServerFlow*){return reserved;}
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned){return pos;}
void MainModule_BattlePosOwner(MainModule*,unsigned,u8* o,u8* i){*o=owner;*i=index;}
void BattleServer_RequestChangePokemon(BtlServerWk*,unsigned p){++requests;requestPos=p;}
void BattleHandler_PushRun(ServerFlow*,BattleHandlerEffect,unsigned){++forceSuccess;}
void* BattleHandler_PushWork(ServerFlow*,BattleHandlerEffect e,unsigned slot){if(e!=44||slot!=2)return 0;++pushes;return &work;}
void BattleHandler_StrSetup(HandlerParam_StrParams* s,unsigned t,unsigned id){s->type=t;s->id=id;}
void BattleHandler_AddArg(HandlerParam_StrParams* s,unsigned id){s->arg=id;}
void BattleHandler_PopWork(ServerFlow* f,void*){f->pokeCon->party[0].members[2]->hp=work.recoverHP;}
void ServerFlow_AddRevivedMonRecord(ServerFlow*,unsigned slot){if(slot==2)++records;}
b32 ServerControl_OnlyPokeIn(ServerFlow*,void*){++forwarded;return 9;}
''' + functions + r'''
int main(){
 BattleMon mons[4]={{0,100,100},{1,0,125},{2,0,101},{3,20,150}};
 PokeCon con={};con.party[0].memberCount=4;for(unsigned i=0;i<4;++i)con.party[0].members[i]=&mons[i];
 MainModule main;BtlServerWk server;ServerFlow flow={&con,&main,&server,0,0};
 unsigned actions[16]={};unsigned char* bytes=(unsigned char*)actions;
 if(!W2U_Revival_CanUse(&flow,0)||W2U_Revival_CanUse(0,0)||W2U_Revival_CanUse(&flow,24))return 1;
 reserved=0;if(W2U_Revival_Begin(&flow,0))return 2;reserved=1;
 flow.simulationCounter=1;if(W2U_Revival_Begin(&flow,0))return 3;flow.simulationCounter=0;
 for(unsigned maxHp=1;maxHp<65536;maxHp+=17){
  mons[2].hp=0;mons[2].maxHp=maxHp;
  if(!W2U_Revival_Begin(&flow,0)||W2U_Revival_Begin(&flow,0)||flow.flowResult!=1||requestPos!=128)return 4;
  actions[0]=3|(2<<7);bytes[48]=1;
  if(W2U_Revival_Resume(&flow,actions)||sRevival.flow||mons[2].hp!=(maxHp>1?maxHp/2:1)||mons[1].hp)return 5;
 }
 if(pushes!=records||work.exStr.type!=2||work.exStr.id!=3||work.exStr.arg!=2||work.pokeID!=2)return 6;
 for(unsigned malformed: {0u,3u|(3<<7),3u|(6<<7),3u|(2<<7)|(1<<4),3u|(2<<7)|(1<<10)}){
  W2U_Revival_Reset();mons[2].hp=0;unsigned old=pushes;
  if(!W2U_Revival_Begin(&flow,0))return 7;
  actions[0]=malformed;W2U_Revival_Resume(&flow,actions);
  if(pushes!=old||mons[2].hp||sRevival.flow)return 8;
 }
 if(W2U_Revival_Resume(&flow,actions)!=9||forwarded!=1)return 9;
 W2U_Revival_Begin(&flow,0);W2U_Revival_Reset();if(sRevival.flow)return 10;
 mons[1].hp=1;mons[2].hp=1;if(W2U_Revival_CanUse(&flow,0))return 11;
 return 0;
}
'''
        source = '#include <initializer_list>\n' + source
        with tempfile.TemporaryDirectory(prefix="w2u-revival-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_both_clean_us_native_calls_and_layouts(self):
        import capstone
        import ndspy.rom
        md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
        for name, delta in (("cleanwhite2.nds", 0), ("cleanblack2.nds", -64)):
            path = ROOT.parent / "Port-Pokeweb" / name
            if not path.exists(): self.skipTest("Optional clean US ROM absent")
            overlay = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
            for call, target in ((0x21B1AAC, 0x21B1D54), (0x21B1C60, 0x21B1D54),
                                 (0x219F7C2, 0x219FCB4), (0x21AFC46, 0x21AC060)):
                address = call + delta
                instructions = list(md.disasm(overlay.data[address-overlay.ramAddress:address-overlay.ramAddress+4], address))
                self.assertEqual([(i.mnemonic, i.op_str) for i in instructions], [("bl", f"#0x{target+delta:x}")])
            address = 0x219D408 + delta
            instructions = list(md.disasm(overlay.data[address-overlay.ramAddress:address-overlay.ramAddress+10], address))
            self.assertIn(("movs", "r0, #0x1c"), [(i.mnemonic,i.op_str) for i in instructions])
        source = (ROOT / "src/pokeweb_gameplay/w2u_revival.cpp").read_text()
        self.assertNotIn("EFFECT_SWITCH", source)
        self.assertIn("W2U_Revival_Reset();", (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text())


if __name__ == "__main__": unittest.main()
