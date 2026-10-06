"""Population Bomb delegates ordinary per-strike checks, not Skill Link's."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class PopulationBombHandler(unittest.TestCase):
    def test_real_handler_owner_and_effective_ability(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = re.search(r'static void HandlerPopulationBombHitCount\(.*?^\}', text, re.S | re.M).group()
        source = r'''
typedef unsigned u32;
struct BattleEventItem {}; struct ServerFlow {}; struct BattleMon { unsigned ability; } mon;
enum { VAR_ATTACKING_MON=3,VALUE_EFFECTIVE_ABILITY=1,ABIL_SKILL_LINK=92,
       MOVE_TRIPLE_KICK=167,EVENT_MOVE_HIT_COUNT=53 };
unsigned owner,calls,missing;
unsigned BattleEventVar_GetValue(unsigned) { return owner; }
BattleMon* GetBattleMon(ServerFlow*,unsigned) { return missing?0:&mon; }
unsigned BattleMon_GetValue(BattleMon* m,unsigned key) {
 if(key!=VALUE_EFFECTIVE_ABILITY) __builtin_trap(); return m->ability;
}
void InvokeNativeMoveEvent(unsigned move,unsigned event,BattleEventItem*,ServerFlow*,unsigned slot,unsigned*) {
 if(move!=167||event!=53||slot!=owner) __builtin_trap(); ++calls;
}
''' + body + r'''
int main() {
 ServerFlow flow;
 for(unsigned ability=0;ability<320;++ability) for(unsigned isOwner=0;isOwner<2;++isOwner)
 for(unsigned absent=0;absent<2;++absent) {
   owner=0; calls=0; missing=absent; mon.ability=ability;
   HandlerPopulationBombHitCount(0,&flow,isOwner?0:12,0);
   if(calls!=unsigned(isOwner&&!absent&&ability!=92)) return 1;
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-population-bomb-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)
        data = (ROOT / "data/pml/moves/860.toml").read_text()
        self.assertIn('Hit = "10 | 10"', data)
        self.assertIn('FLAG_CONTACT', data)


if __name__ == "__main__":
    unittest.main()
