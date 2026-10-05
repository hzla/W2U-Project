"""Shed Tail pays atomically and passes only the native doll state."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def compiled(source):
    with tempfile.TemporaryDirectory(prefix="w2u-shed-tail-") as folder:
        executable = Path(folder) / "check"
        subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                       input=source, text=True, check=True)
        subprocess.run([str(executable)], check=True)


class ShedTailHandler(unittest.TestCase):
    def test_compiled_resident_payment_and_two_copy_exit_filter(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        start = text.index('extern "C" bool W2U_MoveState_CreateShedTailSub(')
        end = text.index("static void RecordPartyMemberDirectHit", start)
        body = text[start:end]
        action = text[text.index("static void HandlerFieldGlaiveRushActionStart("):text.index("static void HandlerFieldGlaiveRushAccuracy(")]
        preamble = r'''
typedef unsigned u32;typedef unsigned short u16;typedef int s32;
struct ServerFlow{unsigned simulationCounter;void* serverCommandQueue;};
struct BattleMon{unsigned battleSlot,max,hp,sub,flags,volatiles,status;unsigned statStageParam;};
struct BattleEventItem{};
struct{unsigned shedTailTransferFlags,glaiveRushFlags;}sMoveState;
unsigned actor;
enum{VAR_MON_ID=2};
unsigned BattleEventVar_GetValue(unsigned){return actor;}
enum{W2U_NULL_BATTLE_POS=6,VALUE_MAX_HP=0,VALUE_CURRENT_HP=1,CONDITIONFLAG_BATONPASS=14,
 SCID_CreateSubstitute=39,SCID_SubstituteAppear=81,SCID_SetMessage=91};
BattleMon mon;unsigned missing,fainted,pos,available,order;
bool IsValidSlot(unsigned slot){return slot<24;}
unsigned SlotMask(unsigned slot){return slot<32?1u<<slot:0;}
BattleMon* GetBattleMon(ServerFlow*,unsigned){return missing?0:&mon;}
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned){return pos;}
bool BattleMon_IsFainted(BattleMon*){return fainted;}
bool BattleMon_IsSubstituteActive(BattleMon* m){return m->sub;}
unsigned BattleMon_GetValue(BattleMon* m,unsigned v){return v?m->hp:m->max;}
bool W2U_MoveState_EnsureTransientEvent(unsigned){return available;}
void ServerDisplay_SimpleHP(ServerFlow*,BattleMon* m,int volume,bool animate){
 if(order++!=0||!animate||volume!=-int((m->max+1)/2))__builtin_trap();m->hp+=volume;
}
void ServerControl_CheckItemReaction(ServerFlow*,BattleMon*,unsigned flags){if(order++!=1||flags!=1)__builtin_trap();}
void BattleMon_CreateSubstitute(BattleMon* m,unsigned hp){if(order++!=2||hp!=m->max/4)__builtin_trap();m->sub=hp;}
void ServerDisplay_AddCommon(void*,unsigned command,unsigned slot,...){if(slot!=0&&command==39)__builtin_trap();if(command!=(order==3?39:81))__builtin_trap();++order;}
void ServerDisplay_AddMessageImpl(void*,unsigned command,unsigned message,unsigned slot,unsigned end){if(order++!=5||command!=91||message!=785||slot||end!=0xffff0000)__builtin_trap();}
bool BattleMon_GetConditionFlag(BattleMon* m,unsigned flag){return m->flags&(1u<<flag);}
void ClearMoveStatusWork(BattleMon* m,bool major){if(major)__builtin_trap();m->volatiles=0;}
void ResetStatStages(unsigned* stages){*stages=6;}
void BattleMon_ResetConditionFlag(BattleMon* m,unsigned flag){m->flags&=~(1u<<flag);}
'''
        checks = r'''
int main(){
 ServerFlow flow={0,0};pos=0;available=1;
 for(unsigned max=1;max<=65535;++max){
  for(unsigned boundary=0;boundary<3;++boundary){
   mon={0,max,(max+1)/2+boundary,0,0,31,4,12};order=0;sMoveState.shedTailTransferFlags=0;
   bool expected=max>=4&&boundary>0;
   if(W2U_MoveState_CreateShedTailSub(&flow,0)!=expected)return 1;
   if(order!=(expected?6:0)||sMoveState.shedTailTransferFlags!=unsigned(expected))return 2;
   if(expected&&(mon.hp!=boundary||mon.sub!=max/4))return 3;
  }
 }
 for(unsigned mode=0;mode<7;++mode){
  mon={0,175,175,mode==0?43u:0u,0,31,4,12};order=0;missing=mode==1;fainted=mode==2;
  pos=mode==3?6:0;available=mode!=4;flow.simulationCounter=mode==5;
  if(W2U_MoveState_CreateShedTailSub(mode==6?0:&flow,0)||order)return 4;
 }
 flow.simulationCounter=0;missing=fainted=0;pos=0;available=1;
 mon={0,175,87,43,(1u<<14)|(1u<<9)|(1u<<10),31,4,12};sMoveState.shedTailTransferFlags=1;
 for(unsigned copy=0;copy<2;++copy){
  // Each delayed native copy is a different BattleMon but the same party ID.
  mon.volatiles=31;mon.statStageParam=12;mon.flags=(1u<<14)|(1u<<9)|(1u<<10);
  W2U_MoveState_PrepareShedTailExit(&mon);
  if(mon.volatiles||mon.statStageParam!=6||mon.flags!=(1u<<14)||mon.sub!=43||mon.status!=4||sMoveState.shedTailTransferFlags!=1)return 5;
 }
 flow.simulationCounter=1;actor=0;HandlerFieldGlaiveRushActionStart(0,&flow,0,0);
 if(sMoveState.shedTailTransferFlags!=1)return 8;
 flow.simulationCounter=0;actor=1;HandlerFieldGlaiveRushActionStart(0,&flow,0,0);
 if(sMoveState.shedTailTransferFlags!=1)return 9;
 actor=0;HandlerFieldGlaiveRushActionStart(0,&flow,0,0);
 if(sMoveState.shedTailTransferFlags)return 10;
 mon.flags=(1u<<14)|(1u<<9);mon.statStageParam=12;mon.volatiles=31;
 W2U_MoveState_PrepareShedTailExit(&mon);
 if(mon.flags!=((1u<<14)|(1u<<9))||mon.statStageParam!=12||mon.volatiles!=31)return 6;
 sMoveState.shedTailTransferFlags=1;mon.flags=1u<<9;
 W2U_MoveState_PrepareShedTailExit(&mon);
 if(mon.flags!=(1u<<9)||mon.statStageParam!=12||mon.volatiles!=31)return 7;
 return 0;
}
'''
        compiled(preamble + body + action + checks)

    def test_compiled_child_preflight_and_native_switch_work(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = text[text.index("static void HandlerShedTail("):text.index("static BattleEventHandlerTableEntry ShedTailHandlers")]
        preamble = r'''
typedef unsigned u32;typedef unsigned char u8;
struct BattleEventItem{};struct ServerFlow{unsigned simulationCounter;};
struct BattleMon{unsigned hp,max,sub,flags;};BattleMon mon;
struct Header{unsigned flags;};struct Str{unsigned value;};
struct HandlerParam_AddPosEffect{Header header;unsigned posEffect,targetPos,workToCopy[4],workCount;}transfer;
struct HandlerParam_Switch{Header header;Str preStr,exStr;unsigned pokeID,intrDisable;}pivot;
enum{BATTLE_MAX_SLOTS=24,VAR_ATTACKING_MON=3,VAR_TARGET_COUNT=5,VALUE_MAX_HP=0,VALUE_CURRENT_HP=1,
 W2U_NULL_BATTLE_POS=6,EFFECT_ADD_POS_EFFECT=30,EFFECT_SWITCH=41,CONDITIONFLAG_BATONPASS=14};
unsigned owner,targets=1,pos,bench,reserved,serviceAvailable,missing,fainted,order,paid,reservations;
unsigned BattleEventVar_GetValue(unsigned id){return id==3?owner:targets;}
BattleMon* GetBattleMon(ServerFlow*,unsigned){return missing?0:&mon;}
unsigned BattleMon_GetValue(BattleMon* m,unsigned value){return value?m->hp:m->max;}
bool BattleMon_IsFainted(BattleMon*){return fainted;}
bool BattleMon_IsSubstituteActive(BattleMon* m){return m->sub;}
unsigned Handler_PokeIDToPokePos(ServerFlow*,unsigned){return pos;}
unsigned Handler_GetFightEnableBenchPokeNum(ServerFlow*,unsigned){return bench;}
bool Handler_CheckReservedMemberChangeAction(ServerFlow*){++reservations;return reserved;}
bool W2U_MoveState_CreateShedTailSub(ServerFlow*,unsigned slot){if(slot!=owner)__builtin_trap();paid+=serviceAvailable;return serviceAvailable;}
void* BattleHandler_PushWork(ServerFlow*,unsigned effect,unsigned slot){
 if(slot!=owner||effect!=(order==0?30:41))__builtin_trap();return effect==30?(void*)&transfer:(void*)&pivot;
}
void BattleHandler_PopWork(ServerFlow*,void* work){if(work!=(order==0?(void*)&transfer:(void*)&pivot))__builtin_trap();++order;}
void ServerDisplay_SetConditionFlag(ServerFlow*,BattleMon* m,unsigned flag){if(order!=1||flag!=14)__builtin_trap();m->flags|=1u<<flag;}
void BattleHandler_StrClear(Str* m){m->value=0;}
'''
        checks = r'''
int main(){ServerFlow flow={0};
 for(unsigned sub=0;sub<2;++sub)for(unsigned hp=87;hp<=89;++hp)
 for(bench=0;bench<2;++bench)for(reserved=0;reserved<2;++reserved)for(serviceAvailable=0;serviceAvailable<2;++serviceAvailable){
  mon={hp,175,sub,0};owner=pos=order=paid=reservations=0;targets=1;pivot={};transfer={};
  HandlerShedTail(0,&flow,0,0);
  bool eligible=!sub&&hp>88&&bench;bool success=eligible&&reserved&&serviceAvailable;
  if(reservations!=unsigned(eligible)||paid!=unsigned(success)||order!=(success?2:0))return 1;
  if(success&&(transfer.posEffect!=4||transfer.targetPos||transfer.workCount!=1||transfer.workToCopy[0]||
               pivot.pokeID||!pivot.intrDisable||pivot.header.flags!=(1u<<24)||pivot.preStr.value||pivot.exStr.value||mon.flags!=(1u<<14)))return 2;
 }
 for(unsigned mode=0;mode<7;++mode){
  mon={175,175,0,0};order=paid=reservations=0;owner=mode==0?12:0;targets=mode==1?0:1;
  missing=mode==2;fainted=mode==3;pos=mode==4?6:0;flow.simulationCounter=mode==5;bench=reserved=serviceAvailable=1;
  HandlerShedTail(0,mode==6?0:&flow,0,0);if(order||paid||reservations)return 3;
 }
 return 0;}
'''
        compiled(preamble + body + checks)

    def test_native_exit_owner_and_marker_lifetime(self):
        moves = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        mega = (ROOT / "src/pokeweb_gameplay/w2u_mega.cpp").read_text()
        self.assertEqual(mega.count("W2U_MoveState_PrepareShedTailExit(battleMon);"), 1)
        hook = mega[mega.index('extern "C" void THUMB_BRANCH_BattleMon_ClearForSwitchOut('):]
        self.assertLess(hook.index("W2U_MoveState_PrepareShedTailExit"), hook.index("CONDITIONFLAG_BATONPASS"))
        action = moves[moves.index("static void HandlerFieldGlaiveRushActionStart("):moves.index("static void HandlerFieldGlaiveRushAccuracy(")]
        self.assertIn("shedTailTransferFlags &= ~SlotMask", action)
        self.assertIn("if (!flow->simulationCounter)", action)
        self.assertEqual(moves.count("shedTailTransferFlags &= ~SlotMask"), 1)

    def test_clean_us_create_substitute_and_display_contracts(self):
        import ndspy.rom
        for name, base in (("cleanwhite2.nds", 0x21BC59C), ("cleanblack2.nds", 0x21BC55C)):
            path = ROOT.parent / "Port-Pokeweb" / name
            if not path.exists(): self.skipTest("Optional clean US W2/B2 ROMs not present")
            overlay = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
            at = base - overlay.ramAddress
            self.assertEqual(bytes(overlay.data[at:at+12]), bytes.fromhex("024a034b815208211847c046"))
            self.assertEqual(int.from_bytes(overlay.data[at+12:at+16], "little"), 0x1F2)
            delta = base - 0x21BC59C
            # The original transaction's OP/ACT/message IDs and berry order.
            self.assertEqual(bytes(overlay.data[0x21A7B8C+delta-overlay.ramAddress:0x21A7B8E+delta-overlay.ramAddress]), bytes.fromhex("2721"))
            self.assertEqual(bytes(overlay.data[0x21A7B96+delta-overlay.ramAddress:0x21A7B98+delta-overlay.ramAddress]), bytes.fromhex("5121"))


if __name__ == "__main__": unittest.main()
