"""Pending priority excludes item ordering bonuses and completed actions."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class PendingMovePriority(unittest.TestCase):
    def test_actual_resident_query_and_child_eligibility(self):
        definitions = []
        for file, pattern in (
            ("w2u_abilities.cpp", r'extern "C" bool W2U_ExtraAction_GetPendingMovePriority\(.*?^\}'),
            ("w2u_moves.cpp", r'static void HandlerUpperHandEligibility\(.*?^\}'),
        ):
            match = re.search(pattern, (ROOT / "src/pokeweb_gameplay" / file).read_text(), re.S | re.M)
            self.assertIsNotNone(match)
            definitions.append(match.group())
        source = r'''
typedef unsigned u32; typedef unsigned MOVE_ID;
enum { MOVE_NONE=0,TURNFLAG_ACTIONDONE=1,W2U_ACTION_ORDER_PRIO_OFFSET=7,
  VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_NO_EFFECT_FLAG=64,VAR_WORK_ADDRESS=63 };
struct BattleMon { bool acted; } mon;
struct BattleActionParam { unsigned cmd; struct { unsigned moveID; } baFight; };
struct ActionOrderWork { BattleMon* battleMon; BattleActionParam action; unsigned speed; bool done; };
struct ServerFlow { unsigned count; ActionOrderWork actionOrderWork[6]; };
struct BattleEventItem {}; struct HandlerParam_StrParams {};
bool active,damaging; unsigned owner,target,noEffect,messages;
BattleMon* W2U_GetActiveBattleMon(ServerFlow*,unsigned) { return active?&mon:0; }
bool BattleMon_GetTurnFlag(BattleMon* m,unsigned) { return m->acted; }
unsigned W2U_GetActionOrderCount(ServerFlow* f) { return f->count>6?6:f->count; }
unsigned BattleAction_GetAction(BattleActionParam* a) { return a->cmd; }
unsigned BattleEventVar_GetValue(unsigned key) { return key==3?owner:key==4?target:0; }
bool BattleEventVar_RewriteValue(unsigned,unsigned) { ++noEffect; return true; }
bool PML_MoveIsDamaging(unsigned) { return damaging; }
void BattleHandler_StrSetup(HandlerParam_StrParams*,unsigned,unsigned) { ++messages; }
''' + "\n".join(definitions) + r'''
int main() {
  ServerFlow flow={}; flow.count=1; flow.actionOrderWork[0].battleMon=&mon;
  flow.actionOrderWork[0].action={1,{98}}; active=true; target=12;
  for(unsigned bracket=0;bracket<64;++bracket) for(unsigned special=0;special<8;++special)
  for(unsigned done=0;done<2;++done) for(unsigned acted=0;acted<2;++acted) {
    flow.actionOrderWork[0].speed=(bracket<<16)|(special<<13)|123;
    flow.actionOrderWork[0].done=done; mon.acted=acted;
    unsigned move=0; int priority=-100;
    bool pending=W2U_ExtraAction_GetPendingMovePriority(&flow,12,&move,&priority);
    if(pending!=(!done&&!acted) || (pending && (move!=98||priority!=int(bracket)-7))) return 1;
    for(unsigned damage=0;damage<2;++damage) for(unsigned wrongOwner=0;wrongOwner<2;++wrongOwner) {
      damaging=damage; owner=wrongOwner; noEffect=0;
      HandlerUpperHandEligibility(0,&flow,0,0);
      bool success=pending && damaging && bracket>=8 && bracket<=10;
      if(noEffect!=(!wrongOwner&&!success)) return 2;
    }
  }
  mon.acted=false; flow.actionOrderWork[0].done=false;
  for(unsigned cmd=0;cmd<5;++cmd) {
    flow.actionOrderWork[0].action.cmd=cmd;
    unsigned move; int priority;
    if(W2U_ExtraAction_GetPendingMovePriority(&flow,12,&move,&priority)!=(cmd==1)) return 3;
  }
  unsigned move; int priority; active=false;
  if(W2U_ExtraAction_GetPendingMovePriority(&flow,12,&move,&priority)) return 4;
  return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-priority-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-Wno-int-to-pointer-cast", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
