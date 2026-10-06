"""Exercise the composed custom prefix of the actual move-selection hook."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class SelectionRestrictions(unittest.TestCase):
    def test_gorilla_and_consecutive_move_selection_have_one_owner(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        hook = re.search(r'extern "C" b32 THUMB_BRANCH_SAFESTACK_IsUnselectableMove\(.*?^\}', source, re.M | re.S).group()
        # Native item/Encore/Disable logic continues below this boundary.
        prefix = hook.split("\n    if (BattleMon_GetHeldItem(battleMon) &&", 1)[0] + "\nreturn 0;\n}\n"
        program = r'''
#include <initializer_list>
using u32=unsigned;using b32=int;using MOVE_ID=unsigned;using ITEM=unsigned;
enum {MOVE_STRUGGLE=165,MOVE_BLOOD_MOON=901,MOVE_GIGATON_HAMMER=893,
 ABIL_GORILLA_TACTICS=255,VALUE_EFFECTIVE_ABILITY=23,CONDITION_CHOICELOCK=27};
struct BtlClientWk {};struct Btlv_StringParam {unsigned id;};
struct BattleMon {unsigned ability,item,id,locked;bool usable,itemUsable;};
struct {unsigned lastSuccessfulSelectedMove[24];} sMoveState;
unsigned BattleMon_GetValue(BattleMon* m,unsigned){return m->ability;}
bool BattleMon_CheckIfMoveCondition(BattleMon* m,unsigned){return m->locked;}
unsigned BattleMon_GetMoveCondition(BattleMon* m,unsigned){return m->locked;}
unsigned Condition_GetParam(unsigned c){return c;}
unsigned BattleMon_GetHeldItem(BattleMon* m){return m->item;}
bool CanMonUseHeldItem(BtlClientWk*,BattleMon* m){return m->itemUsable;}
bool Move_IsUsable(BattleMon* m,unsigned){return m->usable;}
unsigned BattleMon_GetID(BattleMon* m){return m->id;}
bool IsValidSlot(unsigned slot){return slot<24;}
void Btlv_StringParam_Setup(Btlv_StringParam* p,unsigned,unsigned id){p->id=id;}
void Btlv_StringParam_AddArg(Btlv_StringParam*,unsigned){}
''' + prefix + r'''
int main(){
 BtlClientWk client;Btlv_StringParam msg={0};
 for(unsigned ability:{50u,255u})for(unsigned item:{0u,124u,220u,287u,297u})
 for(bool enabled:{false,true})for(bool known:{false,true}){
  BattleMon m={ability,item,0,33,known,enabled};
  bool ownedChoice=(item==220||item==287||item==297)&&enabled;
  unsigned expected=ability==255&&known&&!ownedChoice;
  if(THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,55,&msg)!=expected)return 1;
  if(expected&&msg.id!=100)return 2;
  if(THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,33,&msg))return 3;
  if(THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,165,&msg))return 4;
 }
 BattleMon m={255,0,0,901,true,true};sMoveState.lastSuccessfulSelectedMove[0]=901;
 if(!THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,901,&msg)||msg.id!=580)return 5;
 if(!THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,55,&msg)||msg.id!=100)return 6;
 if(THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,165,&msg))return 7;
 if(!THUMB_BRANCH_SAFESTACK_IsUnselectableMove(&client,&m,55,nullptr))return 8;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-selection-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
