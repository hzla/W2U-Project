"""Compile the real callbacks; scratch belongs to native action registration."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class TripleAxelScratch(unittest.TestCase):
    def test_owner_move_counter_and_native_hit_count_adapter(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        bodies = []
        for name in ("HandlerTripleAxelPower", "HandlerTripleAxelHitCount"):
            match = re.search(r"static void " + name + r"\(.*?^\}", text, re.S | re.M)
            self.assertIsNotNone(match)
            bodies.append(match.group())
        source = r'''
typedef unsigned u32; struct BattleEventItem {}; struct ServerFlow {};
enum { VAR_ATTACKING_MON=3, VAR_MOVE_ID=18, VAR_MOVE_POWER=48,
       MOVE_TRIPLE_AXEL=813, MOVE_TRIPLE_KICK=167, EVENT_MOVE_HIT_COUNT=53 };
u32 vars[64], nativeCalls, nativeOwner;
u32 BattleEventVar_GetValue(u32 key) { return vars[key]; }
void BattleEventVar_RewriteValue(u32 key,u32 value) { vars[key]=value; }
void InvokeNativeMoveEvent(u32 move,u32 event,BattleEventItem*,ServerFlow*,u32 slot,u32*) {
    if(move != MOVE_TRIPLE_KICK || event != EVENT_MOVE_HIT_COUNT) __builtin_trap();
    ++nativeCalls; nativeOwner=slot;
}
''' + "\n".join(bodies) + r'''
int main() {
    for(u32 action=0;action<20;++action) {
        u32 work[4]={0,0x13579,0x24680,0x11111};
        vars[VAR_ATTACKING_MON]=action%24; vars[VAR_MOVE_ID]=MOVE_TRIPLE_AXEL;
        for(u32 hit=1;hit<=3;++hit) {
            vars[VAR_MOVE_POWER]=20;
            HandlerTripleAxelPower(0,0,24,work);
            if(work[0]!=hit-1 || vars[VAR_MOVE_POWER]!=20) return 1;
            vars[VAR_MOVE_ID]=33;
            HandlerTripleAxelPower(0,0,action%24,work);
            if(work[0]!=hit-1 || vars[VAR_MOVE_POWER]!=20) return 2;
            vars[VAR_MOVE_ID]=MOVE_TRIPLE_AXEL;
            HandlerTripleAxelPower(0,0,action%24,work);
            if(work[0]!=hit || vars[VAR_MOVE_POWER]!=hit*20) return 3;
            if(work[1]!=0x13579 || work[2]!=0x24680 || work[3]!=0x11111) return 4;
        }
        HandlerTripleAxelHitCount(0,0,action%24,work);
        if(nativeOwner!=action%24 || nativeCalls!=action+1) return 5;
    }
}
'''
        with tempfile.TemporaryDirectory() as directory:
            cpp, exe = Path(directory) / "test.cpp", Path(directory) / "test"
            cpp.write_text(source)
            subprocess.run(["c++", "-std=c++11", str(cpp), "-o", str(exe)], check=True)
            subprocess.run([str(exe)], check=True)


if __name__ == "__main__":
    unittest.main()
