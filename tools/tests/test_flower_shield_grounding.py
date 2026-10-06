"""Flower Shield shares the grass filter, not Rototiller's grounding rule."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class FlowerShieldGrounding(unittest.TestCase):
    def test_actual_shared_callback(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        callback = re.search(r'extern "C" void HandlerRototiller\(.*?^\}', text, re.M | re.S).group()
        program = r'''
using u32=unsigned;struct BattleEventItem{};struct ServerFlow{};struct BattleMon{};
enum{VAR_ATTACKING_MON,VAR_DEFENDING_MON,VAR_MOVE_ID,VAR_NO_EFFECT_FLAG,TYPE_GRASS=11,MOVE_FLOWER_SHIELD=579};
unsigned vars[4];bool grass,grounded,missing;BattleMon mon;
unsigned BattleEventVar_GetValue(unsigned k){return vars[k];}
void BattleEventVar_RewriteValue(unsigned k,unsigned v){vars[k]=v;}
BattleMon* GetBattleMon(ServerFlow*,unsigned){return missing?nullptr:&mon;}
bool HasTypeWithExtra(BattleMon*,unsigned){return grass;}
bool IsGrounded(ServerFlow*,BattleMon*){return grounded;}
''' + callback + r'''
int main(){ServerFlow sf;vars[0]=0;vars[1]=12;
for(unsigned move:{563u,579u})for(unsigned g=0;g<2;++g)for(unsigned a=0;a<2;++a)for(unsigned m=0;m<2;++m){
 grass=g;grounded=a;missing=m;vars[2]=move;vars[3]=0;HandlerRototiller(nullptr,&sf,0,nullptr);
 if(vars[3]!=(m||!g||(move==563&&!a)))return 1;
}return 0;}
'''
        program = "#include <initializer_list>\n" + program
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
