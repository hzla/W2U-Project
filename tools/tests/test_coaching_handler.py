"""Compile Coaching's narrow ally filter; native work owns the boosts."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class CoachingHandlerTests(unittest.TestCase):
    def test_ally_filter_without_shared_state_or_stat_writes(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        handler = re.search(r'static void HandlerCoaching\(.*?^\}', text, re.S | re.M).group()
        apply = re.search(r'static void HandlerCoachingApply\(.*?^\}', text, re.S | re.M).group()
        source = r'''
typedef unsigned u32;
typedef signed char s8;
struct BattleEventItem {}; struct ServerFlow {}; struct BattleMon {} mon;
enum { VAR_ATTACKING_MON=3, VAR_DEFENDING_MON=4, VAR_TARGET_COUNT=5,
       VAR_TARGET_MON_ID=6, VAR_NO_EFFECT_FLAG=64, STATSTAGE_ATTACK=0, STATSTAGE_DEFENSE=1,
       VALUE_EFFECTIVE_ABILITY=100 };
enum { CONDITIONFLAG_FLY=3, CONDITIONFLAG_SHADOW_FORCE=6, CONDITION_SKYDROP=33 };
unsigned hidden=0; bool carried=false;
bool BattleMon_GetConditionFlag(BattleMon*,unsigned flag) { return hidden&(1u<<flag); }
bool BattleMon_CheckIfMoveCondition(BattleMon*,unsigned flag) { return flag==33 && carried; }
unsigned vars[128], calls; bool exists=true, fainted=false;
bool BattleMon_IsFainted(BattleMon*) { return fainted; }
unsigned BattleMon_GetValue(BattleMon*,unsigned) { return 50; }
bool BattleMon_IsStatChangeValid(BattleMon*,unsigned,int) { return true; }
struct Call { unsigned owner,target,stat,volume,animation; } queued[2];
void ApplyStatChange(ServerFlow*,unsigned owner,unsigned target,unsigned stat,int volume,bool animation) {
 if(calls<2) queued[calls]={owner,target,stat,(unsigned)volume,(unsigned)animation}; ++calls;
}
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
void BattleEventVar_RewriteValue(unsigned key,unsigned value) { vars[key]=value; }
bool MainModule_IsAllyMonID(unsigned a,unsigned b) { return a/6==b/6; }
BattleMon* GetBattleMon(ServerFlow*,unsigned) { return exists?&mon:0; }
''' + handler + '\n' + apply + r'''
int main() {
 ServerFlow flow;
 for(unsigned user=0;user<24;++user) for(unsigned target=0;target<24;++target)
 for(unsigned owner=0;owner<24;++owner) for(unsigned present=0;present<2;++present) {
   vars[3]=user; vars[4]=target; vars[64]=0; exists=present;
   HandlerCoaching(0,&flow,owner,0);
   bool blocked=owner==user && (user==target || user/6!=target/6 || !present);
   if(vars[64]!=blocked) return 1;
 }
 for(unsigned user=0;user<24;++user) for(unsigned target=0;target<24;++target)
 for(unsigned owner=0;owner<24;++owner) for(unsigned present=0;present<2;++present)
 for(unsigned count=0;count<2;++count) for(unsigned dead=0;dead<2;++dead) {
   vars[3]=user; vars[6]=target; vars[5]=count; exists=present; fainted=dead; calls=0;
   HandlerCoachingApply(0,&flow,owner,0);
   bool eligible=owner==user && count && present && !dead && user!=target && user/6==target/6;
   if(calls!=(eligible?2u:0u)) return 2;
   for(unsigned i=0;i<calls;++i) if(queued[i].owner!=target || queued[i].target!=target ||
       queued[i].stat!=i || queued[i].volume!=1 || queued[i].animation) return 3;
 }
 vars[3]=0; vars[6]=1; vars[5]=1; exists=true; fainted=false;
 for(unsigned flag=0;flag<16;++flag) {
   hidden=1u<<flag; calls=0; HandlerCoachingApply(0,&flow,0,0);
   if(calls!=((flag>=3 && flag<=6)?0u:2u)) return 4;
 }
 hidden=0; carried=true; calls=0; HandlerCoachingApply(0,&flow,0,0);
 if(calls) return 5;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-coaching-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
