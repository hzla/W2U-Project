"""Target-dependent category/contact uses one action roll and native stat rules."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class ShellSideArmHandler(unittest.TestCase):
    def test_final_target_adapter_preserves_native_result_and_uses_live_set(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = re.search(r'extern "C" b32 THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA\(.*?^\}',text,re.S|re.M).group()
        source = r'''
typedef unsigned u32; typedef int b32;
#define W2U_ARRAY_COUNT(arr) (sizeof(arr)/sizeof((arr)[0]))
enum {MOVE_SHELL_SIDE_ARM=801,MOVE_DRAGON_DARTS=751,VAR_MOVE_ID=18,VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_MOVE_CATEGORY=26,VAR_MOVE_FAIL_FLAG=65,VAR_GENERAL_USE_FLAG=81,EVENT_W2U_TARGET_PARAM_FINAL=261,W2U_NULL_BATTLE_POS=6};
struct BattleMon {unsigned id;}; struct PokeCon {BattleMon* activeBattleMon[6];}; struct ServerFlow {PokeCon* pokeCon;}; struct MoveParam {unsigned moveID,category,originalMoveID,flags;};
struct PokeSet {BattleMon* battleMon[6]; unsigned count,countMax,damage[6],substituteDamage[6],damageType[6];};
struct {unsigned redirectedTargetFlags,calledDartsFlags;}sMoveState;
void SetSlotFlag(unsigned& flags,unsigned slot,bool set){if(set)flags|=1u<<slot;else flags&=~(1u<<slot);}
bool PML_MoveIsDamaging(unsigned move){return move!=214;}
unsigned SlotMask(unsigned slot) {return 1u<<slot;}
bool BattleMon_IsFainted(BattleMon*) {return false;}
bool MainModule_IsAllyMonID(unsigned a,unsigned b) {return (a/6)%2==(b/6)%2;}
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned) {return 6;}
unsigned vars[128],calls,pushes,pops,selected; int result;
int ServerControl_CorrectTargetDead(ServerFlow*,unsigned,BattleMon*,const MoveParam*,unsigned position,PokeSet*) {
 if(position!=3) __builtin_trap(); ++calls; return result;
}
void BattleEventVar_Push() {++pushes;} void BattleEventVar_Pop() {++pops;}
void BattleEventVar_SetConstValue(unsigned id,unsigned v) {vars[id]=v;}
void BattleEventVar_SetValue(unsigned id,unsigned v) {vars[id]=v;}
void BattleEventVar_SetRewriteOnceValue(unsigned id,unsigned v) {vars[id]=v;}
unsigned BattleEventVar_GetValue(unsigned id) {return vars[id];}
unsigned BattleMon_GetID(BattleMon* m) {return m->id;}
void BattleEvent_CallHandlers(ServerFlow*,unsigned id) {
 if(id!=261||vars[18]!=801||vars[3]!=1||vars[4]!=13) __builtin_trap(); vars[26]=selected;
}
''' + body + r'''
int main() {
 ServerFlow f; BattleMon user={1},target={13}; PokeSet targets={{&target},1};
 for(result=0;result<2;++result) for(selected=1;selected<3;++selected) {
   MoveParam p={801,2};unsigned before=pushes;
   if(THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&f,1,&user,&p,3,&targets)!=result||p.category!=selected||pushes!=before+1||pops!=pushes) return 1;
 }
 for(unsigned invalid=0;invalid<3;++invalid) {
   MoveParam p={invalid==0?33u:801u,2};targets.count=invalid==1?0:1;targets.battleMon[0]=invalid==2?0:&target;
   unsigned before=pushes;THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&f,1,&user,&p,3,&targets);
   if(pushes!=before||p.category!=2) return 2;
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-shell-target-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++","-std=c++11","-x","c++","-o",str(executable),"-"],input=source,text=True,check=True)
            subprocess.run([str(executable)],check=True)

    def test_real_forecast_stage_room_tie_cache_and_scopes(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        names = ("ShellSideArmStagedStat", "HandlerShellSideArmReset", "HandlerShellSideArmCategory")
        bodies = "\n".join(re.search(r'static [^\n]+ ' + name + r'\(.*?^\}',text,re.S|re.M).group() for name in names)
        source = r'''
typedef unsigned u32; typedef unsigned BattleMonValue;
enum {VALUE_ATTACK_STAT=8,VALUE_DEFENSE_STAT=9,VALUE_SPECIAL_ATTACK_STAT=10,VALUE_SPECIAL_DEFENSE_STAT=11,
 VALUE_ATTACK_STAGE=1,VALUE_DEFENSE_STAGE=2,VALUE_SPECIAL_ATTACK_STAGE=3,VALUE_SPECIAL_DEFENSE_STAGE=4,
 VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_MOVE_CATEGORY=26,SPLIT_PHYSICAL=1,SPLIT_SPECIAL=2};
struct BattleEventItem {}; struct ServerFlow { unsigned simulationCounter; };
struct BattleMon { unsigned level,raw[4],rank[4]; } mon[2];
unsigned vars[32],room,draw,rolls,writes,chosen,missing;
unsigned W2U_UnsignedQuotient(unsigned n,unsigned d) { return n/d; }
unsigned BattleMon_GetRealStat(BattleMon* m,unsigned id) {
 if(room && (id==9||id==11)) id=id==9?11:9; return m->raw[id-8];
}
unsigned BattleMon_GetValue(BattleMon* m,unsigned id) { return m->rank[id-1]; }
unsigned BattleEventVar_GetValue(unsigned id) { return vars[id]; }
void BattleEventVar_RewriteValue(unsigned id,unsigned v) { vars[id]=v; }
BattleMon* GetBattleMon(ServerFlow*,unsigned id) { return missing||id>1?0:&mon[id]; }
bool BattleField_CheckEffect(unsigned id) { if(id!=6) __builtin_trap(); return room; }
unsigned BattleRandom(unsigned n) { if(n!=2) __builtin_trap(); ++rolls; return draw; }
void W2U_MoveState_SetShellSideArmCategory(unsigned id,unsigned v) { if(id) __builtin_trap(); ++writes; chosen=v; }
''' + bodies + r'''
unsigned staged(unsigned raw,unsigned rank) { return rank<6?raw*2/(8-rank):raw*(rank-4)/2; }
int main() {
 ServerFlow flow={0}; vars[3]=0; vars[4]=1;
 mon[0]={50,{100,40,99,60},{6,6,6,6}}; mon[1]={50,{50,100,70,100},{6,6,6,6}};
 for(room=0;room<2;++room) for(unsigned a=0;a<13;++a) for(unsigned s=0;s<13;++s)
 for(unsigned d=0;d<13;++d) for(unsigned sd=0;sd<13;++sd) for(draw=0;draw<2;++draw) {
   mon[0].rank[0]=a;mon[0].rank[2]=s;mon[1].rank[1]=d;mon[1].rank[3]=sd;
   mon[1].raw[1]=80;mon[1].raw[3]=130;
   unsigned physical=(22*90*staged(100,a)/staged(80,room?sd:d))/50;
   unsigned special=(22*90*staged(99,s)/staged(130,room?d:sd))/50;
   unsigned expected=physical>special||(physical==special&&!draw)?1:2;
   unsigned work[4]={0},before=rolls;
   HandlerShellSideArmCategory(0,&flow,0,work);
   if(vars[26]!=expected||chosen!=expected||rolls-before!=unsigned(physical==special)) return 1;
   draw^=1;HandlerShellSideArmCategory(0,&flow,0,work);draw^=1;
   if(vars[26]!=expected||rolls-before!=unsigned(physical==special)) return 2;
   HandlerShellSideArmReset(0,&flow,1,work);if(work[0]!=expected) return 3;
   HandlerShellSideArmReset(0,&flow,0,work);if(work[0]) return 4;
 }
 room=0;mon[0]={50,{100,40,99,60},{6,6,6,6}};mon[1]={50,{50,100,70,100},{6,6,6,6}};
 unsigned before=rolls, work[4]={0};flow.simulationCounter=1;
 HandlerShellSideArmCategory(0,&flow,0,work);if(work[0]||rolls!=before||vars[26]!=2) return 5;
 flow.simulationCounter=0;missing=1;vars[26]=55;HandlerShellSideArmCategory(0,&flow,0,work);
 if(vars[26]!=55||work[0]) return 6;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-shell-side-arm-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++","-std=c++11","-O2","-x","c++","-o",str(executable),"-"],input=source,text=True,check=True)
            subprocess.run([str(executable)],check=True)

    def test_us_final_target_call_and_b2_mapping(self):
        import ndspy.rom
        import capstone
        for filename,address in (("cleanwhite2.nds",0x021AE36C),("cleanblack2.nds",0x021AE32C)):
            path = ROOT.parent / "Port-Pokeweb" / filename
            if not path.exists(): self.skipTest("Optional clean-US ROMs are required")
            overlay = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
            code = overlay.data[address-overlay.ramAddress+0xBA:address-overlay.ramAddress+0xBE]
            instruction = next(capstone.Cs(capstone.CS_ARCH_ARM,capstone.CS_MODE_THUMB).disasm(code,address+0xBA))
            self.assertEqual(instruction.mnemonic,"bl")
            self.assertEqual(instruction.op_str,f"#{address+0x7e4:#x}")


if __name__ == "__main__": unittest.main()
