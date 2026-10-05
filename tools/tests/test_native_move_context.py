"""Compile scoped native adapters: no shared move or Substitute mutation."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class NativeMoveContext(unittest.TestCase):
    def test_hit_classifier_and_native_thaw_preserve_context(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        bodies = []
        for name, result in (("W2U_CheckDamagingSubstitute", "b32"),
                             ("THUMB_BRANCH_LINK_167_0x21A5542", "void")):
            match = re.search(r'extern "C" ' + result + " " + name + r'\(.*?^\}', text, re.S | re.M)
            self.assertIsNotNone(match)
            bodies.append(match.group())
        source = r'''
typedef unsigned u32; typedef unsigned MOVE_ID; typedef bool b32;
enum { MOVE_SCORCHING_SANDS=815, MOVE_MATCHA_GOTCHA=902, TYPE_FIRE=9, MOVE_FLAG_INDEX_SOUND=8 };
struct ServerFlow {}; struct PokeSet {}; struct BattleMon { unsigned doll; };
struct MoveParam { unsigned moveID,moveType,flags; };
unsigned nativeCalls,thawCalls; const MoveParam* forwarded;
MoveParam observed;
bool getMoveFlag(unsigned, unsigned flag);
unsigned flags;
bool getMoveFlag(unsigned, unsigned flag) { return flags & (1u<<flag); }
bool BattleMon_IsSubstituteActive(BattleMon* mon) { ++nativeCalls; return mon->doll; }
void ServerControl_ThawHitTargets(ServerFlow*, const MoveParam* move, BattleMon*, PokeSet*) {
  ++thawCalls; forwarded=move; observed=*move;
}
''' + "\n".join(bodies) + r'''
int main() {
  ServerFlow flow; PokeSet targets;
  for(unsigned doll=0;doll<2;++doll) for(unsigned sound=0;sound<2;++sound)
  for(unsigned bypass=0;bypass<2;++bypass) {
    BattleMon mon={doll}; MoveParam move={33,0,123}; flags=(sound<<8)|(bypass<<13); nativeCalls=0;
    if(W2U_CheckDamagingSubstitute(&mon,&move)!=(doll && !sound && !bypass) ||
       nativeCalls!=(sound||bypass?0:1) || mon.doll!=doll) return 1;
    if(W2U_CheckDamagingSubstitute(&mon,0)!=bool(doll)) return 2;
  }
  for(unsigned id=0;id<920;++id) for(unsigned type=0;type<19;++type) {
    BattleMon mon={1}; MoveParam move={id,type,123}; unsigned calls=thawCalls;
    THUMB_BRANCH_LINK_167_0x21A5542(&flow,&move,&mon,&targets);
    if(thawCalls!=calls+1 || observed.moveID!=id || observed.flags!=123 ||
       observed.moveType!=((id==815||id==902)?9:type) || move.moveType!=type || mon.doll!=1) return 3;
    if(id!=815 && id!=902 && forwarded!=&move) return 4;
  }
  return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-native-context-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
