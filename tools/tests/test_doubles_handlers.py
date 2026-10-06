"""Compile narrow doubles contracts; native battles separately test work effects."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
TEXT = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()


def bodies(*names):
    return "\n".join(re.search(r'(?:static|extern "C") [^\n]+ ' + name + r'\(.*?^\}', TEXT, re.S | re.M).group() for name in names)


def compiled(source):
    with tempfile.TemporaryDirectory(prefix="w2u-doubles-") as directory:
        executable = Path(directory) / "check"
        subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o",str(executable),"-"],input=source,text=True,check=True)
        subprocess.run([str(executable)],check=True)


class DoublesContracts(unittest.TestCase):
    def test_spread_drain_order_capacity_simulation_and_faint_guard(self):
        compiled(r'''
typedef unsigned u32; typedef unsigned short u16; typedef unsigned char u8;
struct BattleEventItem {}; struct ServerFlow { unsigned simulationCounter; };
struct BattleMon { bool fainted; unsigned ability; } mons[31];
enum { VAR_MON_ID=2,VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,VAR_DAMAGE=32,
 VALUE_EFFECTIVE_ABILITY=1,ABIL_LIQUID_OOZE=64,EFFECT_DRAIN=6,W2U_NULL_BATTLE_POS=6 };
unsigned vars[128],calls,rapid,pos;
struct Message {};
struct HandlerParam_Drain { u16 recoverHP; u8 recipientSlot,damageSourceSlot; Message exStr; } drains[6];
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
BattleMon* GetBattleMon(ServerFlow*,unsigned slot) { return slot<31?&mons[slot]:0; }
unsigned BattleMon_GetValue(BattleMon* mon,unsigned) { return mon->ability; }
bool BattleMon_IsFainted(BattleMon* mon) { return mon->fainted; }
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned) { return pos; }
void HandlerRapidSpin(BattleEventItem*,ServerFlow*,unsigned,unsigned*) { ++rapid; }
void* BattleHandler_PushWork(ServerFlow*,unsigned,unsigned) { return &drains[calls++]; }
void BattleHandler_PopWork(ServerFlow*,void*) {}
void BattleHandler_StrSetup(Message*,unsigned,unsigned) {}
void BattleHandler_AddArg(Message*,unsigned) {}
''' + bodies("HandlerMatchaReset","HandlerMatchaRecord","HandlerMatchaDrain","HandlerMortalSpin") + r'''
int main() {
 ServerFlow flow={0}; unsigned work[7]={}; vars[2]=vars[3]=0;
 mons[12].ability=0; mons[13].ability=64;
 vars[4]=12; vars[32]=9; HandlerMatchaRecord(0,&flow,0,work);
 vars[4]=13; vars[32]=1; HandlerMatchaRecord(0,&flow,0,work);
 if(work[0]!=2) return 1;
 HandlerMatchaDrain(0,&flow,0,work);
 if(calls!=2 || drains[0].damageSourceSlot!=13 || drains[0].recoverHP!=1 ||
    drains[1].damageSourceSlot!=12 || drains[1].recoverHP!=4 || work[0]) return 2;
 for(unsigned i=0;i<12;++i) HandlerMatchaRecord(0,&flow,0,work);
 if(work[0]!=6) return 3;
 flow.simulationCounter=1; HandlerMatchaRecord(0,&flow,0,work); HandlerMatchaDrain(0,&flow,0,work);
 if(work[0]!=6 || calls!=2) return 4;
 flow.simulationCounter=0; mons[0].fainted=true; HandlerMatchaDrain(0,&flow,0,work);
 if(calls!=2 || work[0]) return 5;
 for(unsigned dead=0;dead<2;++dead) for(pos=0;pos<8;++pos) {
   mons[0].fainted=dead; rapid=0; HandlerMortalSpin(0,&flow,0,work);
   if(rapid!=unsigned(!dead && pos<6)) return 6;
 }
 work[0]=3; HandlerMatchaReset(0,&flow,1,work); if(work[0]!=3) return 7;
 HandlerMatchaReset(0,&flow,0,work); for(unsigned value:work) if(value) return 8;
 return 0;
}
''')

    def test_fixed_critical_bonus_copy_focus_and_type_changes(self):
        compiled(r'''
typedef unsigned u32; typedef unsigned char u8;
struct BattleMon { unsigned battleSlot,critStage; bool focus,dragon; } mons[31];
struct ServerFlow {};
enum { TYPE_DRAGON=15 };
struct { u8 dragonCheerBoost[31]; } sMoveState;
bool allocation=true;
bool IsValidSlot(unsigned slot) { return slot<31; }
BattleMon* GetBattleMon(ServerFlow*,unsigned slot) { return slot<31?&mons[slot]:0; }
bool BattleMon_GetConditionFlag(BattleMon* mon,unsigned) { return mon->focus; }
void BattleMon_SetConditionFlag(BattleMon* mon,unsigned) { mon->focus=true; }
void BattleMon_ResetConditionFlag(BattleMon* mon,unsigned) { mon->focus=false; }
bool HasTypeWithExtra(BattleMon* mon,unsigned) { return mon->dragon; }
bool W2U_MoveState_EnsureTransientEvent(unsigned) { return allocation; }
void ServerDisplay_SetConditionFlag(ServerFlow*,BattleMon* mon,unsigned) { mon->focus=true; }
''' + bodies("W2U_MoveState_ApplyDragonCheer","W2U_CopyCriticalBoost","THUMB_BRANCH_BattleMon_GetCriticalRank") + r'''
int main() {
 ServerFlow flow;
 for(unsigned slot=0;slot<31;++slot) for(unsigned dragon=0;dragon<2;++dragon) {
   mons[slot]={slot,0,false,bool(dragon)};
   if(!W2U_MoveState_ApplyDragonCheer(&flow,slot)) return 1;
   unsigned rank=dragon?2:1;
   mons[slot].dragon=!dragon;
   if(THUMB_BRANCH_BattleMon_GetCriticalRank(&mons[slot])!=rank ||
      W2U_MoveState_ApplyDragonCheer(&flow,slot)) return 2;
   unsigned copy=(slot+1)%31; mons[copy]={copy,0,false,false};
   W2U_CopyCriticalBoost(&mons[copy],&mons[slot]);
   if(!mons[copy].focus || THUMB_BRANCH_BattleMon_GetCriticalRank(&mons[copy])!=rank) return 3;
   mons[slot].focus=false; W2U_CopyCriticalBoost(&mons[copy],&mons[slot]);
   if(mons[copy].focus || sMoveState.dragonCheerBoost[copy]) return 4;
 }
 mons[0]={0,0,true,false}; sMoveState.dragonCheerBoost[0]=0;
 if(THUMB_BRANCH_BattleMon_GetCriticalRank(&mons[0])!=2) return 5;
 mons[0].critStage=3;
 if(THUMB_BRANCH_BattleMon_GetCriticalRank(&mons[0])!=4) return 6;
 mons[0].focus=false; allocation=false;
 if(W2U_MoveState_ApplyDragonCheer(&flow,0) || mons[0].focus) return 7;
 return 0;
}
''')
        cleanup = TEXT.split("static void ClearSwitchedOrFaintedTransientState()",1)[1].split("extern \"C\"",1)[0]
        self.assertIn("sMoveState.dragonCheerBoost[currentSlot] = 0;",cleanup)

    def test_execution_time_terrain_and_redirection_are_owner_scoped(self):
        compiled(r'''
typedef unsigned u32;
struct BattleEventItem {}; struct BattleMon {} mon; struct ServerFlow {};
enum { VAR_MON_ID=2,VAR_ATTACKING_MON=3,VAR_TARGET_TYPE=1,VAR_MOVE_POWER=48,
 VAR_MOVE_FAIL_FLAG=65,TERRAIN_PSYCHIC=4,TARGET_ENEMY_ALL=5 };
unsigned vars[128],terrain; bool grounded;
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
void BattleEventVar_RewriteValue(unsigned key,unsigned value) { vars[key]=value; }
unsigned W2U_MoveState_GetTerrain() { return terrain; }
BattleMon* GetBattleMon(ServerFlow*,unsigned) { return &mon; }
bool IsGrounded(ServerFlow*,BattleMon*) { return grounded; }
''' + bodies("HandlerExpandingForceTarget","HandlerExpandingForcePower","HandlerSnipeShotRedirection") + r'''
int main() {
 ServerFlow flow;
 for(terrain=0;terrain<6;++terrain) for(unsigned air=0;air<2;++air)
 for(unsigned owner=0;owner<31;++owner) {
   grounded=!air; vars[2]=vars[3]=0; vars[1]=0; vars[48]=80; vars[65]=0;
   HandlerExpandingForceTarget(0,&flow,owner,0); HandlerExpandingForcePower(0,&flow,owner,0);
   bool expand=owner==0 && terrain==4 && grounded;
   if(vars[1]!=(expand?5u:0u) || vars[48]!=(expand?120u:80u)) return 1;
   HandlerSnipeShotRedirection(0,&flow,owner,0); if(vars[65]!=(owner==0)) return 2;
 }
 return 0;
}
''')


if __name__ == "__main__":
    unittest.main()
