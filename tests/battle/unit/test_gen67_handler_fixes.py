"""Compile real callbacks and guard metadata behind the Gen 6/7 audit fixes."""
from pathlib import Path
import re
import subprocess
import tempfile
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[3]


class Gen67HandlerFixes(unittest.TestCase):
    def test_real_conversion_parental_and_grass_callbacks(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_abilities.cpp").read_text()
        names = ("KeepsOwnType", "GetNormalMoveConversionType", "BoostConvertedMove",
                 "HandlerNormalMoveConversionTypeChange", "HandlerNormalMoveConversionPower",
                 "HandlerParentalBondPower", "HandlerParentalBondDamage",
                 "HandlerShieldsDownPreventStatus")
        pieces = []
        for name in names:
            match = re.search(r'^(?:extern "C" |static )?(?:u32|void|bool) '+name+r'\(.*?^\}',text,re.M|re.S)
            self.assertIsNotNone(match,name)
            pieces.append(match.group())
        terrain_text = (ROOT / "src/pokeweb_gameplay/megab2w2/abilities/TerrainAbilities.cpp").read_text()
        pieces.append(re.search(r"^void HandlerGrassPeltDefense\(.*?^\}", terrain_text, re.M | re.S).group())
        program = r'''
#include <initializer_list>
using u32=unsigned; using ABILITY=unsigned; using CONDITION=unsigned;
struct BattleEventItem { ABILITY ability; }; struct ServerFlow {};
struct BattleMon { u32 species,form; bool transformed; } mon;
enum { VAR_MON_ID,VAR_ATTACKING_MON,VAR_DEFENDING_MON,VAR_MOVE_ID,VAR_MOVE_TYPE,
       VAR_MOVE_POWER_RATIO,VAR_RATIO,VAR_MOVE_CATEGORY,VAR_DAMAGE_CATEGORY,VAR_CONDITION_ID,VAR_MOVE_FAIL_FLAG,
       ABIL_DRAGONIZE=340,TYPE_DRAGON=15,ABIL_AERILATE=184,ABIL_PIXILATE=182,ABIL_REFRIGERATE=174,ABIL_GALVANIZE=206,
       TYPE_NORMAL=0,TYPE_FLYING=2,TYPE_FAIRY=17,TYPE_ICE=14,TYPE_ELECTRIC=12,TYPE_NULL=18,
       MOVE_STRUGGLE=165,MOVE_HIDDEN_POWER=237,MOVE_WEATHER_BALL=311,MOVE_NATURAL_GIFT=363,
       MOVE_JUDGMENT=449,MOVE_TECHNO_BLAST=546,MOVE_MULTIATTACK=718,MOVE_REVELATION_DANCE=686,MOVE_TERRAIN_PULSE=805,SPLIT_PHYSICAL=1,TERRAIN_GRASSY=2,
       W2U_ABILITY_POWER_RATIO_1_2X=4915,SPECIES_774=774,VALUE_FORM=0,
       W2U_MINIOR_METEOR_FORM_COUNT=7,W2U_FORCE_FAIL_MESSAGE=17,
       CONDITION_PARALYSIS=1,CONDITION_SLEEP=2,CONDITION_FREEZE=3,CONDITION_BURN=4,
       CONDITION_POISON=5,CONDITION_YAWN=6,CONDITION_CONFUSION=7 };
u32 vars[64],currentTerrain; bool rewriteAllowed=true,sParentalBondActive; unsigned char sParentalBondPowerHit;
u32 BattleEventVar_GetValue(u32 key) { return vars[key]; }
bool BattleEventVar_RewriteValue(u32 key,u32 value) {
  if (!rewriteAllowed) return false; vars[key]=value; return true;
}
void BattleEventVar_MulValue(u32 key,u32 value) { vars[key]=(vars[key]*value+2047)/4096; }
ABILITY GetEventItemAbility(BattleEventItem* item) { return item->ability; }
u32 W2U_MoveState_GetTerrain() { return currentTerrain; }
BattleMon* GetAbilityBattleMon(ServerFlow*,u32) { return &mon; }
bool BattleMon_TransformCheck(BattleMon* p) { return p->transformed; }
u32 BattleMon_GetValue(BattleMon* p,u32) { return p->form; }
namespace terrain { const u32 GRASSY=2;u32 Current(){return currentTerrain;} }
namespace ability { u32 Defender(){return vars[VAR_DEFENDING_MON];} void MulRatio(u32 r){BattleEventVar_MulValue(VAR_RATIO,r);} bool Simulating(ServerFlow*){return false;} }
#define MLOG(...) ((void)0)
''' + "\n".join(pieces) + r'''
int main() {
 ServerFlow flow;
 for (u32 ability:{174u,182u,184u,206u,340u}) for (u32 original:{0u,2u,10u,12u,14u,17u}) {
  BattleEventItem item={ability}; u32 work=999;
  vars[VAR_MON_ID]=vars[VAR_ATTACKING_MON]=0; vars[VAR_MOVE_ID]=33;
  vars[VAR_MOVE_TYPE]=original; vars[VAR_MOVE_POWER_RATIO]=4096;
  HandlerNormalMoveConversionTypeChange(&item,&flow,0,&work);
  HandlerNormalMoveConversionPower(&item,&flow,0,&work);
  if (vars[VAR_MOVE_TYPE]!=(original ? original:GetNormalMoveConversionType(ability))) return 1;
  if (vars[VAR_MOVE_POWER_RATIO]!=(original ? 4096u:4915u)) return 2;
  vars[VAR_MOVE_ID]=55;vars[VAR_MOVE_POWER_RATIO]=4096;
  HandlerNormalMoveConversionPower(&item,&flow,0,&work);
  if (vars[VAR_MOVE_POWER_RATIO]!=4096) return 3; // Stale work cannot boost another move.
 }
 BattleEventItem item={174}; u32 work=999;
 vars[VAR_MOVE_TYPE]=0;rewriteAllowed=false;
 HandlerNormalMoveConversionTypeChange(&item,&flow,0,&work);rewriteAllowed=true;
 if (work) return 4;
 for(u32 move:{165u,237u,311u,363u,449u,546u,718u,686u,805u}) {
  vars[VAR_MOVE_ID]=move;vars[VAR_MOVE_TYPE]=0;vars[VAR_MOVE_POWER_RATIO]=4096;work=999;
  HandlerNormalMoveConversionTypeChange(&item,&flow,0,&work);
  HandlerNormalMoveConversionPower(&item,&flow,0,&work);
  if(work || vars[VAR_MOVE_TYPE] || vars[VAR_MOVE_POWER_RATIO]!=4096) return 9;
 }
 sParentalBondActive=true;sParentalBondPowerHit=0;
 for (u32 hit=1;hit<=2;++hit) {
  vars[VAR_RATIO]=vars[VAR_MOVE_POWER_RATIO]=4096;
  HandlerParentalBondPower(0,&flow,0,0);HandlerParentalBondDamage(0,&flow,0,0);
  if (vars[VAR_RATIO]!=(hit==1 ? 4096u:1024u) || vars[VAR_MOVE_POWER_RATIO]!=4096) return 5;
 }
 sParentalBondActive=false;vars[VAR_RATIO]=4096;
 HandlerParentalBondDamage(0,&flow,0,0);if(vars[VAR_RATIO]!=4096) return 6;
 vars[VAR_DEFENDING_MON]=12;
 for(currentTerrain=0;currentTerrain<=4;++currentTerrain) for(u32 cat:{0u,1u,2u}) for(u32 owner:{0u,12u}) {
  vars[VAR_DAMAGE_CATEGORY]=cat;vars[VAR_RATIO]=4096;
  HandlerGrassPeltDefense(0,&flow,owner,0);
  if(vars[VAR_RATIO]!=(currentTerrain==2 && cat==1 && owner==12 ? 6144u:4096u)) return 7;
 }
 for(u32 species:{151u,774u}) for(u32 form=0;form<14;++form) for(u32 transform=0;transform<2;++transform)
 for(u32 condition=1;condition<=7;++condition) for(u32 owner:{0u,12u}) {
  mon={species,form,(bool)transform};vars[VAR_CONDITION_ID]=condition;vars[VAR_MOVE_FAIL_FLAG]=0;
  HandlerShieldsDownPreventStatus(0,&flow,owner,0);
  if(bool(vars[VAR_MOVE_FAIL_FLAG])!=(species==774 && form<7 && !transform && condition<=6 && owner==12)) return 8;
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-gen67-callbacks-") as directory:
            executable = Path(directory)/"check"
            subprocess.run(["c++","-std=c++11","-x","c++","-o",str(executable),"-"],input=program,text=True,check=True)
            subprocess.run([str(executable)],check=True)

    def test_ball_metadata_and_audit_ratios(self):
        balls=(121,140,188,190,192,247,296,301,311,350,360,396,402,411,412,426,439,443,486,491,546)
        for move in balls:
            data=tomllib.loads((ROOT/f"data/pml/moves/{move}.toml").read_text())
            self.assertIn("FLAG_BULLET",next(iter(data.values()))["Flags"],str(move))
        source=(ROOT/"src/pokeweb_gameplay/w2u_abilities.cpp").read_text()
        self.assertRegex(source,r"#define W2U_ABILITY_POWER_RATIO_1_3X 5325\b")
        critical=(ROOT/"src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        self.assertIn("BattleEventVar_GetValue(VAR_CRIT_STAGE) == 5",critical)
        disguise=re.search(r"static void HandlerDisguiseBreak\(.*?^\}",source,re.M|re.S).group()
        self.assertIn("DivideMaxHPZeroCheck(currentMon, 8u)", disguise)
        self.assertIn("W2U_MoveState_RecordDisguiseHit(serverFlow, pokemonSlot)", disguise)
        self.assertEqual(disguise.count("EFFECT_DAMAGE"), 1)


if __name__=="__main__":unittest.main()
