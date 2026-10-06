"""Applied-event history ignores simulations and invalid owners."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class AppliedStatHistory(unittest.TestCase):
    def test_resident_collector_and_child_snapshot(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        definitions = []
        for prefix, name in ((r'extern "C" bool ', "W2U_MoveState_HadStatChangeThisTurn"),
                             ("static void ", "HandlerFieldAppliedStatHistory"),
                             ("static void ", "HandlerStatRiseStatusReset"),
                             ("static void ", "HandlerStatRiseStatusSnapshot")):
            match = re.search(prefix + name + r"\(.*?^\}", text, re.S | re.M)
            self.assertIsNotNone(match)
            definitions.append(match.group())
        source = r'''
typedef unsigned u32; struct BattleEventItem {}; struct ServerFlow { unsigned simulationCounter; };
enum {VAR_MON_ID=2, VAR_ATTACKING_MON=3, VAR_DEFENDING_MON=4, VAR_VOLUME=32};
struct { u32 statsRaisedThisTurnFlags,statsLoweredThisTurnFlags; } sMoveState;
int vars[64];
int BattleEventVar_GetValue(unsigned key) { return vars[key]; }
bool IsValidSlot(unsigned slot) { return slot<31; }
unsigned SlotMask(unsigned slot) { return slot<32 ? 1u<<slot:0; }
void SetSlotFlag(u32& flags,unsigned slot,bool enabled) { if(enabled) flags|=SlotMask(slot); else flags&=~SlotMask(slot); }
''' + "\n".join(definitions) + r'''
int main() {
  ServerFlow flow={0};
  for(unsigned simulation=0;simulation<2;++simulation) for(unsigned slot=0;slot<40;++slot) {
    for(int volume=-6;volume<=6;++volume) {
      sMoveState={0,0}; flow.simulationCounter=simulation; vars[VAR_MON_ID]=slot; vars[VAR_VOLUME]=volume;
      HandlerFieldAppliedStatHistory(0,&flow,31,0);
      unsigned mask=slot<31 && !simulation ? SlotMask(slot):0;
      if(sMoveState.statsRaisedThisTurnFlags!=(volume>0?mask:0) ||
         sMoveState.statsLoweredThisTurnFlags!=(volume<0?mask:0)) return 1;
      for(unsigned query=0;query<40;++query) {
        if(W2U_MoveState_HadStatChangeThisTurn(query,true)!=(query==slot && mask && volume>0) ||
           W2U_MoveState_HadStatChangeThisTurn(query,false)!=(query==slot && mask && volume<0)) return 2;
      }
    }
  }
  flow.simulationCounter=0; vars[VAR_ATTACKING_MON]=0; vars[VAR_DEFENDING_MON]=12;
  unsigned work[4]={0,77,88,99}; sMoveState.statsRaisedThisTurnFlags=1u<<12;
  HandlerStatRiseStatusSnapshot(0,&flow,1,work); if(work[0]) return 3;
  HandlerStatRiseStatusSnapshot(0,&flow,0,work); if(work[0]!=(1u<<12)) return 4;
  flow.simulationCounter=1; sMoveState.statsRaisedThisTurnFlags=0;
  HandlerStatRiseStatusSnapshot(0,&flow,0,work); if(work[0]!=(1u<<12)) return 5;
  HandlerStatRiseStatusReset(0,&flow,1,work); if(work[0]!=(1u<<12)) return 6;
  HandlerStatRiseStatusReset(0,&flow,0,work);
  if(work[0] || work[1]!=77 || work[2]!=88 || work[3]!=99) return 7;
  return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-stat-history-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
