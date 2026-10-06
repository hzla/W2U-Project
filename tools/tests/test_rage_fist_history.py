"""Resident per-party history survives switches, faints and child unloading."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class RageFistHistory(unittest.TestCase):
    def test_real_callbacks_caps_scopes_and_transform(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        functions = "\n".join(re.search(r'(?:static|extern "C") [^\n]+ ' + name + r'\(.*?^\}', text, re.S | re.M).group()
                              for name in ("RecordPartyMemberDirectHit", "W2U_MoveState_RageFistPower",
                                           "W2U_MoveState_RecordDisguiseHit", "W2U_CopyTransformMoveState",
                                           "HandlerFieldTransientMoveStateDamageReaction", "HandlerRageFistPower"))
        source = r'''
typedef unsigned u32; typedef unsigned char u8;
struct BattleEventItem {}; struct ServerFlow { unsigned simulationCounter; };
struct BattleMon { unsigned battleSlot; };
struct { u8 directHitsReceived[24]; } sMoveState;
enum { VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_SUBSTITUTE_FLAG=71,VAR_DAMAGE=32,VAR_MOVE_POWER=48 };
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
unsigned vars[128],criticalCopies;
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
void BattleEventVar_RewriteValue(unsigned key,unsigned value) { vars[key]=value; }
void W2U_CopyCriticalBoost(BattleMon*,BattleMon*) { ++criticalCopies; }
void HandlerFieldTransientMoveStateBeakBlastContact(BattleEventItem*,ServerFlow*,unsigned,unsigned*) {}
void HandlerFieldTransientMoveStateShellTrapHit(BattleEventItem*,ServerFlow*,unsigned,unsigned*) {}
''' + functions + r'''
int main() {
 ServerFlow flow={0};
 for(unsigned slot=0;slot<32;++slot) {
   vars[3]=slot==0?12:0; vars[4]=slot; vars[32]=1;
   for(unsigned hit=0;hit<100;++hit) {
     HandlerFieldTransientMoveStateDamageReaction(0,&flow,31,0);
     unsigned count=hit<6?hit+1:6;
     if(W2U_MoveState_RageFistPower(slot)!=(slot<24?50+50*count:50)) return 1;
   }
 }
 for(unsigned simulated=0;simulated<2;++simulated)
 for(unsigned substitute=0;substitute<2;++substitute)
 for(unsigned self=0;self<2;++self)
 for(unsigned damage=0;damage<2;++damage) {
   sMoveState.directHitsReceived[1]=0; vars[3]=self?1:0; vars[4]=1; vars[32]=damage; vars[71]=substitute;
   flow.simulationCounter=simulated;
   HandlerFieldTransientMoveStateDamageReaction(0,&flow,31,0);
   if(sMoveState.directHitsReceived[1]!=unsigned(!simulated && !substitute && !self && damage)) return 2;
 }
 flow.simulationCounter=0; vars[3]=0; vars[4]=1; vars[32]=0; vars[71]=0;
 sMoveState.directHitsReceived[1]=0;
 W2U_MoveState_RecordDisguiseHit(&flow,1);
 HandlerFieldTransientMoveStateDamageReaction(0,&flow,31,0);
 if(W2U_MoveState_RageFistPower(1)!=100) return 3;
 flow.simulationCounter=1; W2U_MoveState_RecordDisguiseHit(&flow,1);
 W2U_MoveState_RecordDisguiseHit(0,1); if(W2U_MoveState_RageFistPower(1)!=100) return 4;
 for(unsigned user=0;user<32;++user) for(unsigned target=0;target<32;++target) {
   BattleMon a={user},b={target};
   for(unsigned slot=0;slot<24;++slot) sMoveState.directHitsReceived[slot]=slot%7;
   W2U_CopyTransformMoveState(&a,&b);
   if(user<24 && target<24 && sMoveState.directHitsReceived[user]!=target%7) return 5;
 }
 vars[3]=0; vars[48]=123; HandlerRageFistPower(0,&flow,1,0); if(vars[48]!=123) return 6;
 HandlerRageFistPower(0,&flow,0,0); if(vars[48]!=W2U_MoveState_RageFistPower(0)) return 7;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-rage-fist-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)
        cleanup = text.split("static void ClearSwitchedOrFaintedTransientState()",1)[1].split('extern "C"',1)[0]
        self.assertNotIn("directHitsReceived",cleanup)
        critical = re.search(r'extern "C" void W2U_CopyCriticalBoost\(.*?^\}',text,re.S|re.M).group()
        self.assertNotIn("directHitsReceived",critical)  # Psych Up is not Transform.
        reset = text.split("void ClearMoveState()",1)[1].split("void InitExtraTypes",1)[0]
        self.assertIn("sizeof(sMoveState)",reset)


if __name__ == "__main__":
    unittest.main()
