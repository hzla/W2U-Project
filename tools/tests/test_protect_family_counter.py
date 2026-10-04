"""Compile the shared start policy; it must not allocate/load battle DLLs."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class ProtectFamilyCounter(unittest.TestCase):
    def test_native_and_custom_moves_share_previous_executed_move_policy(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        definitions = []
        for pattern in (r"bool IsProtectCounterMove\(.*?^\}",
                        r"void StartProtectCounterMove\(.*?^\}",
                        r'extern "C" void THUMB_BRANCH_HandlerProtectStart\(.*?^\}'):
            match = re.search(pattern, text, re.S | re.M)
            self.assertIsNotNone(match)
            definitions.append(match.group(0))
        family = (182, 197, 203, 469, 501, 661, 588, 596, 792, 852, 908)
        source = r'''
typedef unsigned u32; typedef unsigned MOVE_ID;
enum { VAR_ATTACKING_MON=3 };
struct BattleEventItem {}; struct ServerFlow {}; struct BattleMon { unsigned previous; };
static BattleMon mon; static unsigned owner=0, resets=0;
int BattleEventVar_GetValue(unsigned) { return owner; }
BattleMon* GetBattleMon(ServerFlow*, unsigned) { return &mon; }
unsigned BattleMon_GetPreviousMoveID(BattleMon* p) { return p->previous; }
void ResetProtectCounter(ServerFlow*, unsigned) { ++resets; }
'''
        moves = (ROOT / "include/Moves.h").read_text()
        for name in sorted(set(re.findall(r"MOVE_[A-Z_]+", definitions[0])) - {"MOVE_ID"}):
            value = re.search(rf"^#define {name} (\d+)\s*$", moves, re.M)
            self.assertIsNotNone(value)
            source += f"#define {name} {value.group(1)}\n"
        source += "\n".join(definitions)
        source += "\nint main() { ServerFlow f; unsigned family[] = {" + ",".join(map(str, family)) + "};\n"
        source += r'''
for (unsigned p: family) {
  mon.previous=p; resets=0; owner=0;
  if (!IsProtectCounterMove(p)) return 1;
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
