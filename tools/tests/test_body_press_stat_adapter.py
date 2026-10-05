"""Compile the real critical-stage adapter; Defense is offensive here."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class BodyPressStatAdapter(unittest.TestCase):
    def test_defense_boosts_retained_and_drops_ignored_only_for_critical(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        match = re.search(r'extern "C" u32 THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x86\(.*?^\}', text, re.S | re.M)
        self.assertIsNotNone(match)
        source = r'''
typedef unsigned u32; typedef unsigned BattleMonValue;
enum { VALUE_DEFENSE_STAT=9, VALUE_DEFENSE_STAGE=19 };
struct BattleMon { unsigned rank, raw, staged; };
unsigned nativeCalls;
u32 BattleMon_GetCriticalStat(BattleMon*, unsigned selector) { ++nativeCalls; return 1000+selector; }
u32 BattleMon_GetRealStat(BattleMon* m,unsigned) { return m->raw; }
u32 BattleMon_GetValue(BattleMon* m,unsigned selector) { return selector==19 ? m->rank : m->staged; }
''' + match.group() + r'''
int main() {
  for(unsigned rank=0;rank<=12;++rank) {
    BattleMon m={rank,60, rank>=6 ? 60*(2+rank-6)/2 : 60*2/(2+6-rank)};
    unsigned value=THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x86(&m,9);
    if(value!=(rank<6 ? 60:m.staged) || nativeCalls) return 1;
  }
  BattleMon m={0,60,15};
  for(unsigned selector=0;selector<24;++selector) {
    if(selector==9) continue;
    unsigned calls=nativeCalls;
    if(THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x86(&m,selector)!=1000+selector || nativeCalls!=calls+1) return 2;
  }
  return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-body-press-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_selector_adapter_preserves_the_native_frame_contract(self):
        assembly = (ROOT / "src/pokeweb_gameplay/w2u_damage_hooks.s").read_text().split(
            "THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x4E:", 1)[1].split(".size", 1)[0]
        for instruction in ("push {r3, lr}", "movs r2, r5", "movs r3, r4",
                            "blx r4", "movs r4, r0", "pop {r3, pc}"):
            self.assertIn(instruction, assembly)


if __name__ == "__main__":
    unittest.main()
