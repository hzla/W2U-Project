"""Compile the real berry transaction; item changes happen at native PopWork."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class TeatimeHandler(unittest.TestCase):
    def test_bounds_scopes_and_synchronous_item_changes(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = re.search(r'static void HandlerTeatime\(.*?^\}', text, re.S | re.M).group()
        source = r'''
typedef unsigned u32; typedef unsigned char u8; typedef unsigned short u16;
typedef unsigned ITEM; typedef unsigned BattleEventVar;
struct BattleEventItem {}; struct ServerFlow { unsigned simulationCounter; };
struct BattleMon { unsigned item,hidden,fainted,position; } mons[24];
struct Header { unsigned flags; };
struct HandlerParam_ConsumeItem { Header header; unsigned dontUse; } consume;
struct HandlerParam_UseTempItem { Header header; u8 pokeID,pad; u16 itemID; } effect;
enum { VAR_ATTACKING_MON=3,VAR_TARGET_COUNT=18,VAR_TARGET_MON_ID=20,
       W2U_NULL_BATTLE_POS=6,ITEM_NULL=0,EFFECT_CONSUME_ITEM=1,EFFECT_USE_TEMP_ITEM=2,
       EFFECT_FORCE_MOVE_SUCCESS=3 };
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
unsigned vars[64],owner,consumed[24],effects[24],success,failAllocation,symbiosis;
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
BattleMon* GetBattleMon(ServerFlow*,unsigned id) { return id<24?&mons[id]:0; }
bool BattleMon_IsFainted(BattleMon* mon) { return mon->fainted; }
bool IsMoveRecipientHidden(BattleMon* mon) { return mon->hidden; }
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned id) { return mons[id].position; }
unsigned BattleMon_GetHeldItem(BattleMon* mon) { return mon->item; }
bool PML_ItemIsBerry(unsigned item) { return item>=149 && item<=212; }
void* BattleHandler_PushWork(ServerFlow*,unsigned kind,unsigned slot) {
 owner=slot; if(failAllocation) return 0;
 if(kind==1) { consume={}; return &consume; }
 effect={}; return &effect;
}
void BattleHandler_PopWork(ServerFlow*,void* work) {
 if(work==&consume) {
   consumed[owner]=mons[owner].item; mons[owner].item=0;
   if(symbiosis && owner==0) { mons[0].item=mons[1].item; mons[1].item=0; }
 } else { effects[effect.pokeID]+=1; if(effect.itemID!=consumed[effect.pokeID]) __builtin_trap(); }
}
void BattleHandler_PushRun(ServerFlow*,unsigned,unsigned) { ++success; }
''' + body + r'''
int main() {
 ServerFlow flow={0}; vars[3]=0; vars[18]=6;
 for(unsigned i=0;i<6;++i) { vars[20+i]=i; mons[i]={155,0,0,i}; }
 HandlerTeatime(0,&flow,0,0);
 if(success!=6) return 1;
 for(unsigned i=0;i<6;++i) if(consumed[i]!=155||effects[i]!=1||mons[i].item) return 2;
 vars[18]=7; HandlerTeatime(0,&flow,0,0); if(success!=6) return 3;
 vars[18]=2; vars[20]=0; vars[21]=1; mons[0].item=155; mons[1].item=158;
 symbiosis=1; HandlerTeatime(0,&flow,0,0);
 if(success!=7||mons[0].item!=158||mons[1].item||consumed[0]!=155||consumed[1]!=155||effects[0]!=2||effects[1]!=1) return 4;
 symbiosis=0; vars[18]=6;
 for(unsigned i=0;i<6;++i) { vars[20+i]=i; mons[i]={155,0,0,i}; }
 mons[1].hidden=1; mons[2].fainted=1; mons[3].position=6; mons[4].item=234; vars[25]=31;
 HandlerTeatime(0,&flow,0,0); if(success!=8||mons[1].item!=155||mons[2].item!=155||mons[3].item!=155||mons[4].item!=234) return 5;
 mons[0].item=155; vars[18]=2; vars[20]=vars[21]=0;
 HandlerTeatime(0,&flow,0,0); if(success!=9||effects[0]!=4) return 6;
 mons[0].item=155; flow.simulationCounter=1; HandlerTeatime(0,&flow,0,0);
 flow.simulationCounter=0; HandlerTeatime(0,&flow,1,0); HandlerTeatime(0,0,0,0);
 failAllocation=1; HandlerTeatime(0,&flow,0,0);
 if(success!=9||mons[0].item!=155) return 7;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-teatime-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
