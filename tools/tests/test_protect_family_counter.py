"""Compile the shared start policy; it must not allocate/load battle DLLs."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class ProtectFamilyCounter(unittest.TestCase):
    def test_native_and_custom_moves_share_previous_executed_move_policy(self):
        protect_c = (ROOT / "src/mechanics/resident/protect.c").read_text()
        moves_cpp = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        definitions = []
        for pattern in (r"static const u16 sProtectCounterMoves\[\] = \{.*?\};",
                        r"b32 W2U_IsProtectCounterMove\(.*?^\}",
                        r"void W2U_StartProtectCounterMove\(.*?^\}"):
            match = re.search(pattern, protect_c, re.S | re.M)
            self.assertIsNotNone(match)
            definitions.append(match.group(0))
        for pattern in (r"void StartProtectCounterMove\(.*?^\}",
                        r'extern "C" void THUMB_BRANCH_HandlerProtectStart\(.*?^\}'):
            match = re.search(pattern, moves_cpp, re.S | re.M)
            self.assertIsNotNone(match)
            definitions.append(match.group(0))
        family = (182, 197, 203, 469, 501, 661, 588, 596, 792, 852, 908)
        source = r'''
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned u32; typedef int b32;
enum { FALSE=0, TRUE=1, VAR_ATTACKING_MON=3, HANDLER_CMD_SET_COUNTER=0x26, COUNTER_PROTECT=3 };
#define NELEMS(a) (sizeof(a) / sizeof((a)[0]))
struct BattleEventItem {}; struct BtlServerFlow {}; typedef BtlServerFlow ServerFlow;
struct BattleMon { u16 previous; };
struct BattleHandlerSetCounterParam { int header; u8 monIndex; u8 counter; u8 value; };
static BattleMon mon; static BattleHandlerSetCounterParam work; static unsigned owner=0, resets=0;
int BattleEventVar_GetValue(unsigned) { return owner; }
BattleMon* GetBattleMon(BtlServerFlow*, unsigned) { return &mon; }
u16 GetPreviousMoveID(BattleMon* p) { return p->previous; }
void* BattleHandler_PushWork(BtlServerFlow*, int, unsigned) { return &work; }
void BattleHandler_PopWork(BtlServerFlow*, void*) { if (work.counter == COUNTER_PROTECT && work.value == 0) ++resets; }
'''
        source += "\n".join(definitions)
        source += "\nint main() { ServerFlow f; unsigned family[] = {" + ",".join(map(str, family)) + "};\n"
        source += r'''
for (unsigned p: family) {
  mon.previous=p; resets=0; owner=0;
  if (!W2U_IsProtectCounterMove(p)) return 1;
  THUMB_BRANCH_HandlerProtectStart(0,&f,0,0);
  if (resets) return 2;
}
for (unsigned p: {0u,33u,150u,850u}) {
  mon.previous=p; resets=0; owner=0;
  THUMB_BRANCH_HandlerProtectStart(0,&f,0,0);
  if (resets!=1) return 3;
  resets=0; owner=12;
  THUMB_BRANCH_HandlerProtectStart(0,&f,0,0);
  if (resets) return 4;
}
return 0;
}
'''
        # Avoid stdlib dependence in the actual game policy; range-for's
        # initializer_list convenience is used only by this host driver.
        source = "#include <initializer_list>\n" + source
        with tempfile.TemporaryDirectory(prefix="w2u-protect-family-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
