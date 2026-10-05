"""Last Respects observes committed native faints, never switch notices."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class LastRespectsHandler(unittest.TestCase):
    def test_compiled_resident_history_and_child(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        names = ("W2U_RecordCommittedFaint", "W2U_MoveState_LastRespectsPower",
                 "HandlerLastRespectsCheck", "HandlerLastRespectsPower")
        functions = "\n".join(re.search(r'(?:static|extern "C") [^\n]+ ' + name + r'\(.*?^\}', text, re.S | re.M).group() for name in names)
        source = r'''
typedef unsigned u32;typedef unsigned char u8;
struct BattleEventItem{};struct FaintRecord{};
struct PokeCon{struct {unsigned memberCount;}party[4];};
struct ServerFlow{unsigned simulationCounter;PokeCon* pokeCon;};
struct {u8 faintEvents[4];}sMoveState;
enum{VAR_ATTACKING_MON=3,VAR_MON_ID=2,VAR_FAIL_CAUSE=0,MOVE_FAIL_OTHER=1,VAR_MOVE_POWER=48};
unsigned vars[64],forwarded;
void FaintRecord_Add(FaintRecord*,u32){++forwarded;}
unsigned W2U_GetBattlePartyOwner(ServerFlow*,unsigned slot){return slot/6;}
unsigned BattleEventVar_GetValue(unsigned k){return vars[k];}
void BattleEventVar_RewriteValue(unsigned k,unsigned v){vars[k]=v;}
''' + functions + r'''
int main(){
 PokeCon con={};con.party[0].memberCount=6;con.party[1].memberCount=6;
 ServerFlow flow={0,&con};FaintRecord record;
 for(unsigned slot=0;slot<24;++slot){
  for(unsigned p=0;p<4;++p)sMoveState.faintEvents[p]=0;
  for(unsigned n=1;n<=110;++n){
   W2U_RecordCommittedFaint(&record,slot,&flow);
   unsigned count=n>100?100:n;
   if(W2U_MoveState_LastRespectsPower(&flow,slot)!=50+50*count)return 1;
   for(unsigned p=0;p<4;++p)if(sMoveState.faintEvents[p]!=(p==slot/6?count:0))return 2;
  }
 }
 unsigned saved=sMoveState.faintEvents[3];flow.simulationCounter=1;
 W2U_RecordCommittedFaint(&record,18,&flow);
 W2U_RecordCommittedFaint(&record,31,&flow);
 W2U_RecordCommittedFaint(&record,18,0);
 if(sMoveState.faintEvents[3]!=saved||forwarded!=2643)return 3;
 flow.simulationCounter=0;
 for(unsigned party=2;party<=3;++party){
  con.party[party].memberCount=1;vars[2]=0;vars[3]=0;vars[0]=0;vars[48]=123;
  HandlerLastRespectsCheck(0,&flow,1,0);if(vars[0])return 4;
  HandlerLastRespectsCheck(0,&flow,0,0);if(!vars[0])return 5;
  HandlerLastRespectsPower(0,&flow,0,0);if(vars[48]!=123)return 6;
  con.party[party].memberCount=0;
 }
 for(unsigned slot=0;slot<24;++slot){
  vars[3]=slot;vars[48]=123;HandlerLastRespectsPower(0,&flow,slot,0);
  if(vars[48]!=W2U_MoveState_LastRespectsPower(&flow,slot))return 7;
 }
 if(W2U_MoveState_LastRespectsPower(0,0)||W2U_MoveState_LastRespectsPower(&flow,24))return 8;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-last-respects-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)
        cleanup = text.split("static void ClearSwitchedOrFaintedTransientState()", 1)[1].split('extern "C"', 1)[0]
        self.assertNotIn("faintEvents", cleanup)
        transform = re.search(r'extern "C" void W2U_CopyTransformMoveState\(.*?^\}', text, re.S | re.M).group()
        self.assertNotIn("faintEvents", transform)
        self.assertIn("sizeof(sMoveState)", text.split("void ClearMoveState()", 1)[1].split("void InitExtraTypes", 1)[0])

    def test_clean_us_commit_guard_and_call(self):
        import capstone
        import ndspy.rom
        md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
        for name, delta in (("cleanwhite2.nds", 0), ("cleanblack2.nds", -64)):
            path = ROOT.parent / "Port-Pokeweb" / name
            if not path.exists(): self.skipTest("Optional clean US ROM absent")
            overlay = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
            address = 0x21A8A74 + delta
            decoded = [(i.mnemonic, i.op_str) for i in md.disasm(overlay.data[address-overlay.ramAddress:address-overlay.ramAddress+40], address)]
            self.assertIn(("ldrb", "r0, [r5, r6]"), decoded)
            self.assertIn(("strb", "r0, [r5, r6]"), decoded)
            self.assertIn(("bne", f"#0x{0x21A8B60+delta:x}"), decoded)
            self.assertIn(("beq", f"#0x{0x21A8B60+delta:x}"), decoded)
            self.assertIn(("bl", f"#0x{0x21A8B78+delta:x}"), decoded)


if __name__ == "__main__": unittest.main()
