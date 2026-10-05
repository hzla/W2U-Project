"""Dragon Darts delegates one native eligibility pass and damage rounding."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def compiled(source):
    with tempfile.TemporaryDirectory(prefix="w2u-dragon-darts-") as directory:
        executable = Path(directory) / "check"
        subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                       input=source, text=True, check=True)
        subprocess.run([str(executable)], check=True)


class DragonDartsHandler(unittest.TestCase):
    def test_prankster_immunity_is_only_for_a_called_payload_and_foe_dark_type(self):
        text=(ROOT/"src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        bodies="\n".join(re.search(pattern,text,re.S|re.M).group() for pattern in (
            r'extern "C" bool W2U_DragonDartsHasPranksterOrigin\(.*?^\}',
            r'static void HandlerDragonDartsPrankster\(.*?^\}'))
        compiled(r'''
typedef unsigned u32;struct BattleEventItem{};struct BattleMon{unsigned ability,type;};struct ServerFlow{};
enum{VAR_DEFENDING_MON=4,VAR_ATTACKING_MON=3,VAR_MOVE_ID=18,MOVE_DRAGON_DARTS=751,VAR_NO_EFFECT_FLAG=64,TYPE_DARK=16,
 VALUE_EFFECTIVE_ABILITY=1,ABIL_PRANKSTER=158};
struct{unsigned calledDartsFlags;}sMoveState;BattleMon mons[24];unsigned vars[128];
unsigned SlotMask(unsigned slot){return slot<24?1u<<slot:0;}
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEventVar_RewriteValue(unsigned id,unsigned value){vars[id]=value;}
BattleMon* GetBattleMon(ServerFlow*,unsigned slot){return slot<24?&mons[slot]:0;}
unsigned BattleMon_GetValue(BattleMon* mon,unsigned){return mon->ability;}
bool HasTypeWithExtra(BattleMon* mon,unsigned type){return mon&&mon->type==type;}
bool MainModule_IsAllyMonID(unsigned a,unsigned b){return a/12==b/12;}
''' + bodies + r'''
int main(){ServerFlow f;unsigned abilities[]={0,50,158},types[]={0,16};
 for(unsigned called=0;called<2;++called)for(unsigned ability: abilities)
 for(unsigned owner=0;owner<24;++owner)for(unsigned target=0;target<24;++target)
 for(unsigned type: types){
  sMoveState.calledDartsFlags=called;mons[0].ability=ability;mons[target].type=type;
  vars[3]=0;vars[4]=target;vars[64]=0;vars[18]=751;
  HandlerDragonDartsPrankster(0,&f,owner,0);
  if(vars[64]!=(owner==0&&target>=12&&type==16&&called&&ability==158))return 1;
 }return 0;}
''')

    def test_final_target_adapter_appends_only_a_living_active_foe(self):
        text=(ROOT/"src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body=re.search(r'extern "C" b32 THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA\(.*?^\}',text,re.S|re.M).group()
        compiled(r'''
typedef unsigned u32;typedef unsigned b32;
enum{MOVE_SHELL_SIDE_ARM=801,MOVE_DRAGON_DARTS=751,VAR_MOVE_ID=18,
 VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_MOVE_CATEGORY=30,VAR_MOVE_FAIL_FLAG=65,
 VAR_GENERAL_USE_FLAG=81,EVENT_W2U_TARGET_PARAM_FINAL=261,W2U_NULL_BATTLE_POS=6};
struct BattleMon{unsigned slot,fainted,position;};
struct PokeCon{BattleMon* activeBattleMon[24];};struct ServerFlow{PokeCon* pokeCon;};
struct MoveParam{unsigned moveID,category,originalMoveID,flags;};
struct PokeSet{BattleMon* battleMon[6];unsigned damage[6],substituteDamage[6],damageType[6],count,countMax;};
struct{unsigned redirectedTargetFlags,calledDartsFlags;}sMoveState;
unsigned vars[128],dispatches,pushes,pops,expanded,correction;
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
unsigned SlotMask(unsigned slot){return 1u<<slot;}
void SetSlotFlag(unsigned& flags,unsigned slot,bool set){if(set)flags|=SlotMask(slot);else flags&=~SlotMask(slot);}
bool PML_MoveIsDamaging(unsigned move){return move!=214;}
unsigned BattleMon_GetID(BattleMon* mon){return mon->slot;}
unsigned BattleMon_IsFainted(BattleMon* mon){return mon->fainted;}
bool MainModule_IsAllyMonID(unsigned a,unsigned b){return a/12==b/12;}
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned slot){return slot==12?1:slot==13?3:6;}
unsigned ServerControl_CorrectTargetDead(ServerFlow*,unsigned,BattleMon*,const MoveParam*,unsigned,PokeSet*){return correction;}
void BattleEventVar_Push(){++pushes;}void BattleEventVar_Pop(){++pops;}
void BattleEventVar_SetConstValue(unsigned id,unsigned value){vars[id]=value;}
void BattleEventVar_SetValue(unsigned id,unsigned value){vars[id]=value;}
void BattleEventVar_SetRewriteOnceValue(unsigned id,unsigned value){vars[id]=value;}
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEvent_CallHandlers(ServerFlow*,unsigned event){
 if(event!=261)__builtin_trap();++dispatches;vars[81]=expanded;
 if(vars[18]==801)vars[30]=1;
}
''' + body + r'''
int main(){BattleMon user={0,0,0},selected={12,0,1},other={13,0,3},ally={1,0,2},bench={14,0,6};
 PokeCon con={};ServerFlow flow={&con};con.activeBattleMon[0]=&user;con.activeBattleMon[1]=&ally;
 con.activeBattleMon[12]=&selected;con.activeBattleMon[13]=&other;con.activeBattleMon[14]=&bench;
 unsigned moves[]={751,801,33};for(unsigned move: moves)for(unsigned available=0;available<2;++available)
 for(expanded=0;expanded<2;++expanded)for(correction=0;correction<2;++correction)
 for(unsigned called=0;called<2;++called)for(unsigned origin: moves){
  other.fainted=!available;PokeSet set={};set.battleMon[0]=&selected;set.count=set.countMax=1;
  // The extra entry starts dirty to require native Add initialization.
  set.damage[1]=set.substituteDamage[1]=set.damageType[1]=99;
  MoveParam param={move,2,called?origin:0,called?4u:0u};dispatches=pushes=pops=0;sMoveState.redirectedTargetFlags=1;
  sMoveState.calledDartsFlags=0;
  if(THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&flow,1,&user,&param,1,&set)!=correction)return 1;
  unsigned want=move==751&&available&&expanded?2:1;
  if(set.count!=want||set.countMax!=want||set.battleMon[0]!=&selected)return 2;
  if(want==2&&(set.battleMon[1]!=&other||set.damage[1]||set.substituteDamage[1]||set.damageType[1]))return 3;
  if(dispatches!=(move!=33)||pushes!=dispatches||pops!=dispatches)return 4;
  if(move!=33&&(vars[3]!=0||vars[4]!=12||vars[65]!=1))return 5;
  if(param.category!=(move==801?1u:2u))return 6;
  if(sMoveState.calledDartsFlags)return 10; // All three sampled origins are damage moves.
 }
 MoveParam called={751,2,214,4};PokeSet selectedSet={};selectedSet.battleMon[0]=&selected;selectedSet.count=1;
 THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&flow,1,&user,&called,1,&selectedSet);
 if(sMoveState.calledDartsFlags!=1)return 11;
 called.flags=0;selectedSet.count=1;
 THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&flow,1,&user,&called,1,&selectedSet);
 if(sMoveState.calledDartsFlags)return 12;
 // A failed/absent custom table cannot request expansion; no vanilla alias.
 // Null input and an empty filtered set must retain the original result.
 PokeSet empty={};MoveParam param={751,2};correction=1;
 if(!THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&flow,1,0,&param,1,&empty))return 7;
 if(!THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&flow,1,&user,0,1,&empty))return 8;
 if(!THUMB_BRANCH_LINK_ServerControl_RegisterTargets_0xBA(&flow,1,&user,&param,1,&empty)||empty.count)return 9;
 return 0;}
''')

    def test_redirection_query_preserves_value_and_detects_same_selected_center(self):
        text=(ROOT/"src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        bodies="\n".join(re.search(r'extern "C" void '+name+r'\(.*?^\}',text,re.S|re.M).group()
                          for name in ("THUMB_BRANCH_LINK_167_0x21AEDCE","THUMB_BRANCH_LINK_167_0x21AEE28"))
        compiled(r'''
typedef unsigned u32;typedef unsigned BattleEventType;
enum{VAR_MOVE_ID=18,VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_MOVE_FAIL_FLAG=65,
 EVENT_W2U_REDIRECTION_CHECK=258,MOVE_DRAGON_DARTS=751,BATTLE_MAX_SLOTS=31};
struct ServerFlow{};struct{unsigned redirectedTargetFlags;}sMoveState;
unsigned vars[128],claimed,redirect,veto,calls;
unsigned SlotMask(unsigned slot){return 1u<<slot;}
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEventVar_SetValue(unsigned id,unsigned value){vars[id]=value;}
unsigned BattleEventVar_RewriteValue(unsigned id,unsigned value){
 if(id!=4)__builtin_trap();if(claimed)return 0;claimed=1;vars[id]=value;return 1;
}
void BattleEvent_CallHandlers(ServerFlow*,unsigned event){
 ++calls;if(event==258){vars[65]=veto;return;}
 if(redirect!=31){if(!BattleEventVar_RewriteValue(4,redirect))__builtin_trap();}
}
''' + bodies + r'''
int main(){ServerFlow f;vars[3]=0;vars[18]=751;
 for(unsigned early=0;early<2;++early)for(unsigned later=0;later<3;++later){
  vars[4]=31;claimed=0;redirect=early?12:31;sMoveState.redirectedTargetFlags=0xffffffff;
  THUMB_BRANCH_LINK_167_0x21AEDCE(&f,41);
  if(bool(sMoveState.redirectedTargetFlags&1)!=bool(early)||vars[4]!=(early?12u:31u))return 1;
  // Includes a center that is exactly the selected input (later=1).
  vars[4]=12;claimed=0;redirect=later==0?31:later==1?12:13;
  THUMB_BRANCH_LINK_167_0x21AEE28(&f,42);
  if(bool(sMoveState.redirectedTargetFlags&1)!=bool(early||later)||vars[4]!=(later==2?13u:12u))return 2;
  if(sMoveState.redirectedTargetFlags!=(early||later?0xffffffffu:0xfffffffeu))return 3;
 }
 // Preserve the Snipe Shot veto and leave other moves' rewrite state intact.
 vars[18]=745;vars[4]=12;claimed=0;veto=1;redirect=13;calls=0;
 THUMB_BRANCH_LINK_167_0x21AEE28(&f,42);
 if(claimed||vars[4]!=12||calls!=1)return 4;
 return 0;}
''')

    def test_split_policy_respects_final_owner_redirection_and_format(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = re.search(r'static void HandlerDragonDartsTargets\(.*?^\}', text, re.S | re.M).group()
        compiled(r'''
typedef unsigned u32;
struct BattleEventItem{};struct ServerFlow{void* mainModule;};
enum{VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_MOVE_ID=18,MOVE_DRAGON_DARTS=751,VAR_MOVE_FAIL_FLAG=65,VAR_GENERAL_USE_FLAG=81,BTL_STYLE_DOUBLE=1};
unsigned vars[128],style;
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEventVar_RewriteValue(unsigned id,unsigned value){vars[id]=value;}
unsigned BtlSetup_GetBattleStyle(void*){return style;}
bool MainModule_IsAllyMonID(unsigned a,unsigned b){return a/12==b/12;}
''' + body + r'''
int main(){ServerFlow flow={0};
 for(style=0;style<4;++style)for(unsigned redirected=0;redirected<2;++redirected)
 for(unsigned owner=0;owner<24;++owner)for(unsigned attacker=0;attacker<24;++attacker)
 for(unsigned target=0;target<24;++target){
  vars[3]=attacker;vars[4]=target;vars[65]=redirected;vars[81]=0;vars[18]=751;
  HandlerDragonDartsTargets(0,&flow,owner,0);
  unsigned expected=owner==attacker&&style==1&&!redirected&&!MainModule_IsAllyMonID(attacker,target);
  if(vars[81]!=expected)return 1;
 }return 0;}
''')

    def test_filtered_count_and_unrounded_spread_selector_are_move_scoped(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        bodies = "\n".join(re.search(r'extern "C" u32 '+name+r'\(.*?^\}', text, re.S | re.M).group()
                           for name in ("W2U_GetFilteredMultiHitTargetCount", "W2U_GetDamageSpreadTargetCount"))
        compiled(r'''
typedef unsigned u32;enum{MOVE_DRAGON_DARTS=751};
struct PokeSet{unsigned count,countMax;};struct MoveParam{unsigned moveID;};
''' + bodies + r'''
int main(){for(unsigned move=0;move<920;++move)for(unsigned max=0;max<=6;++max)
 for(unsigned count=0;count<=max;++count){PokeSet set={count,max};MoveParam param={move};
  if(W2U_GetFilteredMultiHitTargetCount(&set,&param)!=(move==751?count:max))return 1;
  if(W2U_GetDamageSpreadTargetCount(&set,&param)!=(move==751?1:max))return 2;
  if(set.count!=count||set.countMax!=max)return 3;
 }return 0;}
''')

    def test_us_w2_b2_call_frames_and_count_offsets(self):
        import capstone
        import ndspy.rom
        md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
        for name, delta in (("cleanwhite2.nds",0),("cleanblack2.nds",-64)):
            path=ROOT.parent/"Port-Pokeweb"/name
            if not path.exists():self.skipTest("Optional clean US W2/B2 ROMs absent")
            overlay=ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
            def instructions(address,size):
                address+=delta
                return [(i.mnemonic,i.op_str) for i in md.disasm(overlay.data[address-overlay.ramAddress:address-overlay.ramAddress+size],address)]
            self.assertEqual(instructions(0x21A445C,10),[("adds","r0, r7, #0"),("bl",f"#0x{0x21A4520+delta:x}"),("cmp","r0, #1"),("bne",f"#0x{0x21A447A+delta:x}")])
            self.assertEqual(instructions(0x21A4878,10),[("str","r1, [sp, #0x10]"),("adds","r7, r2, #0"),("str","r3, [sp, #0x14]"),("bl",f"#0x{0x21A49A4+delta:x}")])
            for address,value in ((0x21AEDBA,"#0x1f"),(0x21AEE1C,"r4")):
                self.assertEqual(instructions(address,8),[("movs","r0, #4"),
                    ("movs","r1, "+value) if value.startswith("#") else ("adds","r1, r4, #0"),
                    ("bl",f"#0x{0x21BCE84+delta:x}")])
            for address,event in ((0x21AEDCA,41),(0x21AEE24,42)):
                self.assertEqual(instructions(address,8),[("adds","r0, r6, #0"),("movs",f"r1, #0x{event:x}"),("bl",f"#0x{0x21BC940+delta:x}")])
            # Source PokeSet layout: six pointers, two u16 damage arrays,
            # six type bytes, six u16 sorting entries, then count/countMax.
            header=(ROOT/"include/w2u_battle.h").read_text()
            self.assertIn("u16 sortWork[6];",header)
            self.assertIn("u8 count;\n    u8 countMax;",header)


if __name__ == "__main__":unittest.main()
