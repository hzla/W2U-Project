"""Compile the actual Doodle transaction, not a separate model of its logic."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class DoodleContract(unittest.TestCase):
    def test_atomicity_restrictions_ownership_and_native_work(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        header = (ROOT / "include/w2u_abilities.h").read_text()
        functions = "\n".join(re.search(r'static [^\n]+ ' + name + r'\(.*?^\}', text, re.S | re.M).group()
                              for name in ("IsDoodleProtectedAbility", "HandlerDoodle"))
        names = set(re.findall(r'ABIL_\w+', functions))
        constants = ",".join(re.search(name + r'\s*=\s*\d+', header).group() for name in sorted(names))
        source = r'''
typedef unsigned u32; typedef unsigned short u16; typedef unsigned char u8; typedef unsigned ABILITY;
struct BattleEventItem {}; struct ServerFlow {};
struct BattleMon { unsigned ability,pos; bool fainted,present; } mons[24];
enum { VAR_ATTACKING_MON=3,VAR_TARGET_COUNT=34,VAR_TARGET_MON_ID=35,VALUE_ABILITY=16,
 W2U_SIDE_SLOT_COUNT=3,W2U_NULL_BATTLE_POS=6,EFFECT_CHANGE_ABILITY=31 };
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
enum { ''' + constants + r''' };
struct Message {};
struct HandlerParam_ChangeAbility { unsigned ability,pokeID,sameAbilityEffective,skipSwitchInEvent; Message exStr; } effects[3];
unsigned vars[128],count,pops;
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
BattleMon* GetBattleMon(ServerFlow*,unsigned slot) { return slot<24 && mons[slot].present?&mons[slot]:0; }
bool BattleMon_IsFainted(BattleMon* mon) { return mon->fainted; }
unsigned BattleMon_GetValue(BattleMon* mon,unsigned) { return mon->ability; }
bool MainModule_IsAllyMonID(unsigned a,unsigned b) { return (a<12)==(b<12); }
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned slot) { return mons[slot].pos; }
void* BattleHandler_PushWork(ServerFlow*,unsigned effect,unsigned) { if(effect!=31 || count==3) throw 1; return &effects[count++]; }
void BattleHandler_PopWork(ServerFlow*,void*) { ++pops; }
void BattleHandler_StrSetup(Message*,unsigned,unsigned) {}
void BattleHandler_AddArg(Message*,unsigned) {}
''' + functions + r'''
void reset(unsigned copied=169) {
 count=pops=0; vars[3]=0; vars[34]=1; vars[35]=12;
 for(unsigned i=0;i<24;++i) mons[i]={50,6,false,true};
 mons[0].ability=99; mons[0].pos=0; mons[1].pos=1;
 mons[12].pos=3; mons[12].ability=copied; mons[13].pos=4;
}
int main() {
 ServerFlow flow;
 const unsigned protectedIds[]={121,161,176,197,208,209,210,211,213,225,241,248,266,267,278,279,281,282,310};
 for(unsigned ability=0;ability<320;++ability) {
   bool protectedAbility=false; for(unsigned id:protectedIds) if(id==ability) protectedAbility=true;
   if(IsDoodleProtectedAbility(ability)!=protectedAbility) return 1;
   reset(ability); HandlerDoodle(0,&flow,0,0);
   if(count!=unsigned(protectedAbility || ability==222?0:ability==50 || ability==99?1:2)) return 2;
   for(unsigned i=0;i<count;++i) if(effects[i].ability!=ability || effects[i].sameAbilityEffective || effects[i].skipSwitchInEvent) return 3;
   for(unsigned slot=0;slot<2;++slot) {
     reset(); mons[slot].ability=ability; HandlerDoodle(0,&flow,0,0);
     if(count!=unsigned(protectedAbility?0:ability==169?1:2)) return 4;
   }
 }
 reset(); mons[1].ability=121; HandlerDoodle(0,&flow,0,0); if(count || pops) return 5;
 reset(); mons[2].pos=2; HandlerDoodle(0,&flow,0,0); if(count!=3 || pops!=3) return 6;
 reset(); mons[2].pos=2; mons[3].pos=5; HandlerDoodle(0,&flow,0,0); if(count || pops) return 7;
 reset(); mons[1].fainted=true; HandlerDoodle(0,&flow,0,0); if(count!=1 || effects[0].pokeID!=0) return 8;
 reset(); mons[1].pos=6; HandlerDoodle(0,&flow,0,0); if(count!=1) return 9;
 reset(); mons[12].fainted=true; HandlerDoodle(0,&flow,0,0); if(count) return 10;
 reset(); mons[12].present=false; HandlerDoodle(0,&flow,0,0); if(count) return 11;
 reset(); HandlerDoodle(0,&flow,1,0); if(count) return 12;
 reset(); vars[34]=2; HandlerDoodle(0,&flow,0,0); if(count) return 13;
 reset(); mons[0].ability=mons[1].ability=169; HandlerDoodle(0,&flow,0,0); if(count) return 14;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-doodle-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
