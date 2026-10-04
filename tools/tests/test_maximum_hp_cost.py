"""Compile shared cost callbacks; no-target/AI/owner paths must stay inert."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MaximumHpCost(unittest.TestCase):
    def test_rounding_action_reset_owner_and_rock_head_policy(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        pieces = []
        for name in ("HandlerMindBlownReset", "HandlerMindBlownMarkAttempt",
                     "HandlerChloroblastMarkHit", "HandlerMindBlownRecoil"):
            match = re.search(r"static void " + name + r"\(.*?^\}", text, re.S | re.M)
            self.assertIsNotNone(match)
            pieces.append(match.group())
        source = r'''
typedef unsigned u32; struct BattleEventItem {};
struct ServerFlow { unsigned simulationCounter; };
struct BattleMon { unsigned maxHp, effectiveAbility, fainted; } mon;
enum { VAR_ATTACKING_MON=3, VAR_MON_ID=2, VAR_MOVE_ID=18, VALUE_MAX_HP=14,
       VALUE_EFFECTIVE_ABILITY=17, MOVE_CHLOROBLAST=835, BATTLE_RECOIL_MSGID=99 };
unsigned vars[64], calls, cost;
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
BattleMon* GetBattleMon(ServerFlow*,unsigned) { return &mon; }
bool BattleMon_IsFainted(BattleMon* mon) { return mon->fainted; }
unsigned BattleMon_GetValue(BattleMon* mon,unsigned key) {
    return key==VALUE_MAX_HP ? mon->maxHp : mon->effectiveAbility;
}
void PushDamage(ServerFlow*,unsigned source,unsigned target,unsigned damage,unsigned,unsigned arg) {
    if (source!=12 || target!=12 || arg!=12) __builtin_trap();
    ++calls; cost=damage;
}
''' + "\n".join(pieces) + r'''
int main() {
    ServerFlow flow={0};
    for (unsigned hp=1;hp<=513;++hp)
    for (unsigned move: {720u,796u,835u})
    for (unsigned ability: {0u,69u}) {
        mon={hp,ability,0}; vars[VAR_ATTACKING_MON]=12; vars[VAR_MON_ID]=12;
        vars[VAR_MOVE_ID]=move; calls=0; cost=0;
        unsigned work[4]={42,0x12345,0x67890,0x123456};
        HandlerMindBlownReset(0,&flow,12,work);
        HandlerMindBlownRecoil(0,&flow,12,work); // no target / no execution
        if (calls || work[0]) return 1;
        HandlerMindBlownMarkAttempt(0,&flow,11,work);
        if (work[0]) return 2;
        if (move==835) {
            flow.simulationCounter=1;
            HandlerChloroblastMarkHit(0,&flow,12,work);
            if (work[0]) return 3;
            flow.simulationCounter=0;
            HandlerChloroblastMarkHit(0,&flow,11,work);
            if (work[0]) return 4;
        }
        for (unsigned hit=0;hit<3;++hit) {
            if (move==835) HandlerChloroblastMarkHit(0,&flow,12,work);
            else HandlerMindBlownMarkAttempt(0,&flow,12,work);
        }
        HandlerMindBlownRecoil(0,&flow,11,work);
        if (calls || work[0]!=1) return 5;
        HandlerMindBlownRecoil(0,&flow,12,work);
        HandlerMindBlownRecoil(0,&flow,12,work);
        bool veto=move==835 && ability==69;
        if (calls!=!veto || (!veto && cost!=(hp+1)/2) || work[0]) return 6;
        if (work[1]!=0x12345 || work[2]!=0x67890 || work[3]!=0x123456) return 7;
    }
    return 0;
}
'''
        source = "#include <initializer_list>\n" + source
        with tempfile.TemporaryDirectory(prefix="w2u-hp-cost-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
