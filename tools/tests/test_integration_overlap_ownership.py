"""Compile overlap callbacks and reject duplicate resident hook owners."""
import importlib.util
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location("linkage", ROOT / "tools/verify_w2u_battle_linkage.py")
linkage = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(linkage)


class OverlapOwnership(unittest.TestCase):
    def test_numeric_and_named_hooks_have_one_owner(self):
        database = {"Segments": [{"ID":29, "Name":167}],
                    "Symbols": [{"Name":"WeatherCheck", "Address":0x021a767d, "Segment":29}]}
        linkage.verify_unique_hook_targets({"THUMB_BRANCH_WeatherCheck", "THUMB_BRANCH_LINK_WeatherCheck_0x10"}, database)
        with self.assertRaisesRegex(RuntimeError, "duplicate hook ownership"):
            linkage.verify_unique_hook_targets({"THUMB_BRANCH_WeatherCheck", "THUMB_BRANCH_167_0x21A767C"}, database)
        with self.assertRaisesRegex(RuntimeError, "duplicate hook ownership"):
            linkage.verify_unique_hook_targets({"FULL_COPY_167_0x21A768C", "THUMB_BRANCH_LINK_WeatherCheck_0x10"}, database)

    def test_real_terrain_callbacks_apply_exactly_one_move_specific_boost(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        patterns = (r"static void HandlerExpandingForcePower\(.*?^\}",
                    r"static void HandlerMistyExplosionPower\(.*?^\}",
                    r'extern "C" void HandlerTerrainPower\(.*?^\}')
        functions = "\n".join(re.search(pattern, text, re.S | re.M).group() for pattern in patterns)
        source = r"""
#include <initializer_list>
typedef unsigned u32, MOVE_ID, TERRAIN;
struct BattleEventItem {}; struct ServerFlow {}; struct BattleMon {};
enum {VAR_ATTACKING_MON=3,VAR_MOVE_ID=18,VAR_MOVE_TYPE=22,VAR_MOVE_POWER=48,
 VAR_MOVE_POWER_RATIO=49,TERRAIN_ELECTRIC=1,TERRAIN_GRASSY=2,TERRAIN_MISTY=3,
 TERRAIN_PSYCHIC=4,TYPE_ELECTRIC=12,TYPE_GRASS=11,TYPE_PSYCHIC=13,
 MOVE_MISTY_EXPLOSION=802,MOVE_EXPANDING_FORCE=797,W2U_TERRAIN_POWER_RATIO=5325};
unsigned vars[64],terrain;bool floating;BattleMon mon;
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEventVar_RewriteValue(unsigned id,unsigned value){vars[id]=value;}
void BattleEventVar_MulValue(unsigned id,unsigned value){vars[id]=(vars[id]*value+2047)/4096;}
unsigned W2U_MoveState_GetTerrain(){return terrain;}
BattleMon* GetBattleMon(ServerFlow*,unsigned slot){return slot==0?&mon:nullptr;}
bool IsGrounded(ServerFlow*,BattleMon* target){return target&&!floating;}
""" + functions + r"""
int main(){
 ServerFlow flow;
 for(unsigned move:{797u,802u,33u})for(terrain=0;terrain<5;++terrain)
 for(unsigned type:{0u,11u,12u,13u,17u})for(unsigned air=0;air<2;++air)
 for(unsigned owner:{0u,12u}){
  floating=air;vars[3]=0;vars[18]=move;vars[22]=type;vars[48]=80;vars[49]=4096;
  if(move==797)HandlerExpandingForcePower(0,&flow,owner,0);
  if(move==802)HandlerMistyExplosionPower(0,&flow,owner,0);
  HandlerTerrainPower(0,&flow,owner,0);
  bool boosted=!owner&&!air&&((move==797&&terrain==4)||(move==802&&terrain==3));
  if(vars[48]!=(boosted?120u:80u))return 1;
  bool terrainBoost=!air&&((terrain==1&&type==12)||(terrain==2&&type==11)||(terrain==4&&type==13));
  if(vars[49]!=(terrainBoost?5325u:4096u))return 2;
 }
 return 0;
}
"""
        with tempfile.TemporaryDirectory(prefix="w2u-overlap-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++","-std=c++11","-x","c++","-o",str(executable),"-"],
                           input=source,text=True,check=True)
            subprocess.run([str(executable)],check=True)
        self.assertNotRegex(text, r"\{\s*MOVE_MISTY_EXPLOSION\s*,\s*MOVE_EXPLOSION\s*\}")


if __name__ == "__main__":
    unittest.main()
