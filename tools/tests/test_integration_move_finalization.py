"""Protect the event contexts established by native regression failures."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pokeweb_gameplay/w2u_moves.cpp"


class MoveFinalization(unittest.TestCase):
    def test_actual_take_heart_keeps_status_cure_independent_of_effective_caps(self):
        callback = re.search(r'static void HandlerTakeHeart\(.*?^\}', SOURCE.read_text(), re.M | re.S).group()
        program = r'''
#include <initializer_list>
using u32=unsigned;using s8=signed char;using CONDITION=unsigned;
enum {VAR_ATTACKING_MON,VAR_TARGET_COUNT,VALUE_EFFECTIVE_ABILITY,STATSTAGE_SPECIAL_ATTACK,STATSTAGE_SPECIAL_DEFENSE};
struct BattleEventItem{};struct ServerFlow{unsigned simulationCounter;};struct BattleMon{} mon;
unsigned ability,attack,defense,status,calls,cures,owner=0;bool fainted=false;
unsigned BattleEventVar_GetValue(unsigned v){return v==VAR_ATTACKING_MON?owner:1;}
BattleMon* GetBattleMon(ServerFlow*,unsigned slot){return slot==owner?&mon:nullptr;}
bool BattleMon_IsFainted(BattleMon*){return fainted;}
unsigned BattleMon_GetValue(BattleMon*,unsigned){return ability;}
bool BattleMon_IsStatChangeValid(BattleMon*,unsigned stat,int direction){
 unsigned stage=stat==STATSTAGE_SPECIAL_ATTACK?attack:defense;return direction<0?stage>0:stage<12;}
void ApplyStatChange(ServerFlow*,unsigned from,unsigned to,unsigned,int,bool){if(from!=owner||to!=owner)calls=100;else ++calls;}
unsigned BattleMon_GetStatus(BattleMon*){return status;}
bool IsPurifiableStatus(unsigned value){return value>0&&value<=5;}
void CureMoveCondition(ServerFlow*,unsigned target,unsigned value){if(target!=owner||value!=status)cures=100;else ++cures;}
''' + callback + r'''
int main(){ServerFlow sf={0};
 for(owner=0;owner<=12;owner+=12)for(unsigned selected:{50u,126u,86u})
 for(attack=0;attack<=12;++attack)for(defense=0;defense<=12;++defense)for(status=0;status<=6;++status){
  ability=selected;calls=cures=0;HandlerTakeHeart(nullptr,&sf,owner,nullptr);
  bool changes=ability==126?(attack>0||defense>0):(attack<12||defense<12);
  if(calls!=(changes?2u:0u)||cures!=(status>0&&status<=5?1u:0u))return 1;
 }
 owner=0;status=1;sf.simulationCounter=1;calls=cures=0;HandlerTakeHeart(nullptr,&sf,owner,nullptr);
 if(calls||cures)return 2;
 sf.simulationCounter=0;fainted=true;HandlerTakeHeart(nullptr,&sf,owner,nullptr);
 if(calls||cures)return 3;
 fainted=false;HandlerTakeHeart(nullptr,&sf,12,nullptr);return calls||cures;
}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_actual_tidy_up_preserves_cleanup_benefits_without_false_cap_success(self):
        callback = re.search(r'static void HandlerTidyUp\(.*?^\}', SOURCE.read_text(), re.M | re.S).group()
        program = r'''
#include <initializer_list>
using u32=unsigned;using s8=signed char;using SIDE_EFFECT=unsigned;
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
const unsigned W2U_SIDE_COUNT=2,W2U_NULL_BATTLE_POS=6;
enum {VAR_ATTACKING_MON,VAR_TARGET_COUNT,VALUE_EFFECTIVE_ABILITY,STATSTAGE_ATTACK,STATSTAGE_SPEED,
 SIDEEFF_SPIKES,SIDEEFF_TOXIC_SPIKES,SIDEEFF_STEALTH_ROCK,SIDEEFF_STICKY_WEB,EFFECT_FORCE_MOVE_SUCCESS};
struct BattleEventItem{};struct BattleMon{} mon;
struct PokeCon {BattleMon* activeBattleMon[2];} con;
struct ServerFlow {unsigned simulationCounter;PokeCon* pokeCon;};
unsigned attack,speed,ability,stats,removed,forced,mode;bool fainted;
unsigned BattleEventVar_GetValue(unsigned v){return v==VAR_ATTACKING_MON?0:1;}
BattleMon* GetBattleMon(ServerFlow*,unsigned slot){return slot==0?&mon:nullptr;}
bool BattleMon_IsFainted(BattleMon*){return fainted;}
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned slot){return slot;}
bool BattleMon_IsSubstituteActive(BattleMon*){return mode==1;}
void BattleMon_RemoveSubstitute(BattleMon*){++removed;}
bool SideEffectEvent_IsActive(unsigned side,unsigned effect){return mode==2&&side==1&&effect==SIDEEFF_SPIKES;}
void RemoveSideEffects(ServerFlow*,unsigned,unsigned,const SIDE_EFFECT*,unsigned){++removed;}
bool RemoveStickyWebSide(ServerFlow*,unsigned,unsigned side,bool){if(mode==3&&side==0){++removed;return true;}return false;}
unsigned BattleMon_GetValue(BattleMon*,unsigned){return ability;}
bool BattleMon_IsStatChangeValid(BattleMon*,unsigned stat,int direction){
 unsigned stage=stat==STATSTAGE_ATTACK?attack:speed;return direction<0?stage>0:stage<12;}
void ApplyStatChange(ServerFlow*,unsigned,unsigned,unsigned,int,bool){++stats;}
void BattleHandler_PushRun(ServerFlow*,unsigned,unsigned){++forced;}
''' + callback + r'''
int main(){ServerFlow sf={0,&con};
 for(unsigned selected:{50u,126u,86u})for(attack=0;attack<=12;++attack)for(speed=0;speed<=12;++speed)for(mode=0;mode<4;++mode){
  ability=selected;
  stats=removed=forced=0;HandlerTidyUp(nullptr,&sf,0,nullptr);
  bool changes=ability==126?(attack>0||speed>0):(attack<12||speed<12);
  if(stats!=(changes?2u:0u)||removed!=(mode?1u:0u)||forced!=(mode?1u:0u))return 1;
 }
 sf.simulationCounter=1;stats=removed=forced=0;HandlerTidyUp(nullptr,&sf,0,nullptr);
 if(stats||removed||forced)return 2;
 sf.simulationCounter=0;fainted=true;HandlerTidyUp(nullptr,&sf,0,nullptr);
 return stats||removed||forced;
}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_actual_coaching_does_not_report_success_at_effective_caps(self):
        callback = re.search(r'static void HandlerCoachingApply\(.*?^\}', SOURCE.read_text(), re.M | re.S).group()
        program = r'''
#include <initializer_list>
using u32=unsigned;using s8=signed char;using StatStage=unsigned;
struct BattleEventItem{};struct ServerFlow{};struct BattleMon{};
enum {VAR_ATTACKING_MON,VAR_TARGET_COUNT,VAR_TARGET_MON_ID,VALUE_EFFECTIVE_ABILITY,
 CONDITIONFLAG_FLY,CONDITIONFLAG_SHADOW_FORCE,CONDITION_SKYDROP,STATSTAGE_ATTACK,STATSTAGE_DEFENSE};
BattleMon mon;unsigned ability,attack,defense,calls;
unsigned BattleEventVar_GetValue(unsigned v){return v==VAR_ATTACKING_MON?0:1;}
BattleMon* GetBattleMon(ServerFlow*,unsigned){return &mon;}
bool BattleMon_IsFainted(BattleMon*){return false;}
bool MainModule_IsAllyMonID(unsigned,unsigned){return true;}
bool BattleMon_GetConditionFlag(BattleMon*,unsigned){return false;}
bool BattleMon_CheckIfMoveCondition(BattleMon*,unsigned){return false;}
unsigned BattleMon_GetValue(BattleMon*,unsigned){return ability;}
bool BattleMon_IsStatChangeValid(BattleMon*,unsigned stat,int direction){
 unsigned stage=stat==STATSTAGE_ATTACK?attack:defense;return direction<0?stage>0:stage<12;}
void ApplyStatChange(ServerFlow*,unsigned,unsigned,unsigned,int,bool){++calls;}
''' + callback + r'''
int main(){ServerFlow sf;for(unsigned selected:{50u,126u,86u})for(attack=0;attack<=12;++attack)for(defense=0;defense<=12;++defense){
 ability=selected;calls=0;HandlerCoachingApply(nullptr,&sf,0,nullptr);
 bool changes=ability==126?(attack>0||defense>0):(attack<12||defense<12);
 if(calls!=(changes?2u:0u))return 1;
}return 0;}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_actual_revelation_final_type_retains_only_permitted_conversions(self):
        text = SOURCE.read_text()
        callback = re.search(r'extern "C" void HandlerRevelationDanceType\(.*?^\}', text, re.M | re.S).group()
        self.assertIn("EVENT_W2U_MOVE_PARAM_FINAL", re.search(r'RevelationDanceHandlers\[\].*?\};', text, re.S).group())
        program = r'''
#include <initializer_list>
using u32=unsigned;struct BattleEventItem{};struct ServerFlow{};struct BattleMon{};
enum {VAR_MON_ID,VAR_MOVE_TYPE,TYPE_NORMAL=0,TYPE_ELECTRIC=13};
unsigned resolved,type;bool electric,deluge;BattleMon mon;
unsigned BattleEventVar_GetValue(unsigned){return 0;}
void BattleEventVar_RewriteValue(unsigned,unsigned v){type=v;}
unsigned W2U_ResolveRevelationDanceType(BattleMon*){return resolved;}
BattleMon* GetBattleMon(ServerFlow*,unsigned){return &mon;}
bool W2U_MoveState_IsElectrified(unsigned){return electric;}
bool W2U_MoveState_IsIonDelugeActive(){return deluge;}
''' + callback + r'''
int main(){ServerFlow sf;for(resolved=0;resolved<19;++resolved)for(unsigned e:{0u,1u})for(unsigned d:{0u,1u}){
 electric=e;deluge=d;type=0;HandlerRevelationDanceType(nullptr,&sf,0,nullptr);
 if(type!=((e||(resolved==0&&d))?13:resolved))return 1;
}return 0;}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_trapping_uses_hit_recipients_not_native_spider_web_context(self):
        text = SOURCE.read_text()
        table = re.search(r'AnchorShotHandlers\[\].*?\};', text, re.S).group()
        callback = re.search(r'extern "C" void HandlerAnchorShot\(.*?^\}', text, re.M | re.S).group()
        self.assertIn("EVENT_DAMAGE_PROCESSING_END_HIT_REAL", table)
        self.assertIn("QueueSourceTrap", callback)
        self.assertIn("VAR_TARGET_COUNT", callback)
        self.assertIn("target != pokemonSlot", callback)
        self.assertNotIn("EventAddSpiderWeb", callback)

    def test_aurora_and_happy_hour_use_executable_no_target_context(self):
        text = SOURCE.read_text()
        self.assertIn("EVENT_UNCATEGORIZED_MOVE_NO_TARGET", re.search(r'HappyHourHandlers\[\].*?\};', text, re.S).group())
        callback = re.search(r'extern "C" void HandlerAuroraVeil\(.*?^\}', text, re.M | re.S).group()
        self.assertIn("ServerEvent_GetWeather(serverFlow) != WEATHER_HAIL", callback)


if __name__ == "__main__":
    unittest.main()
