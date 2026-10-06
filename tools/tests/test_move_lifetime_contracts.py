"""Compile the resident selection/window and native source-trap contracts."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MoveLifetimeContracts(unittest.TestCase):
    def test_selection_history_and_source_encoding(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        trap = re.search(r'static bool QueueSourceTrap\(.*?^\}', text, re.S | re.M).group()
        history = re.search(r'    if \(currentMask && serverFlow && !serverFlow->simulationCounter\) \{.*?^    \}', text, re.S | re.M).group()
        selection = text.split("extern \"C\" b32 THUMB_BRANCH_SAFESTACK_IsUnselectableMove(", 1)[1]
        selection = selection.split("    const u32 slot =", 1)[1].split("#endif", 1)[0]
        functions = []
        for name in ("HandlerFieldGlaiveRushActionStart", "HandlerFieldGlaiveRushAccuracy", "HandlerFieldGlaiveRushDamage"):
            functions.append(re.search(r'static void ' + name + r'\(.*?^\}', text, re.S | re.M).group())
        source = r'''
typedef unsigned u32; typedef unsigned short u16; typedef unsigned char u8;
struct BattleEventItem {}; struct ServerFlow { unsigned simulationCounter; };
struct BattleMon { unsigned previousMove; bool fainted,ghost,trapped; } mons[31];
enum { MOVE_NONE=0,MOVE_BLOOD_MOON=901,MOVE_GIGATON_HAMMER=893,
  TYPE_GHOST=7,CONDITION_ESCAPE_PREVENTION=22,EFFECT_ADD_CONDITION=4,
  VAR_MON_ID=2,VAR_DEFENDING_MON=4,VAR_GENERAL_USE_FLAG=81,VAR_RATIO=53 };
struct HandlerParam_StrParams {};
struct HandlerParam_AddCondition { unsigned condition,condData; u8 pokeID,almost; HandlerParam_StrParams exStr; } effect;
struct { u16 lastSuccessfulSelectedMove[31]; unsigned glaiveRushFlags, shedTailTransferFlags; } sMoveState;
unsigned vars[128], pushes,pops; bool allocation=true;
unsigned SlotMask(unsigned slot) { return slot<31?1u<<slot:0; }
bool IsValidSlot(unsigned slot) { return slot<31; }
BattleMon* GetBattleMon(ServerFlow*,unsigned slot) { return slot<31?&mons[slot]:0; }
bool BattleMon_IsFainted(BattleMon* m) { return m->fainted; }
bool HasTypeWithExtra(BattleMon* m,unsigned) { return m->ghost; }
bool BattleMon_CheckIfMoveCondition(BattleMon* m,unsigned) { return m->trapped; }
void* BattleHandler_PushWork(ServerFlow*,unsigned,unsigned) { ++pushes; return allocation?&effect:0; }
void BattleHandler_PopWork(ServerFlow*,void*) { ++pops; }
void BattleHandler_StrSetup(HandlerParam_StrParams*,unsigned,unsigned) {}
void BattleHandler_AddArg(HandlerParam_StrParams*,unsigned) {}
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
void BattleEventVar_RewriteValue(unsigned key,unsigned value) { vars[key]=value; }
void BattleEventVar_MulValue(unsigned key,unsigned value) { vars[key]=(vars[key]*value)>>12; }
struct StringParam {};
void Btlv_StringParam_Setup(StringParam*,unsigned,unsigned) {}
void Btlv_StringParam_AddArg(StringParam*,unsigned) {}
unsigned BattleMon_GetID(BattleMon* mon) { return mon-mons; }
''' + trap + '\n' + '\n'.join(functions) + r'''
void record(ServerFlow* serverFlow,unsigned currentSlot) {
  unsigned currentMask=SlotMask(currentSlot);
''' + history + r'''
}
bool restricted(BattleMon* battleMon,unsigned moveID,StringParam* strparam) {
  const u32 slot =''' + selection + r'''
  return false;
}
int main() {
  ServerFlow flow={0};
  for(unsigned source=0;source<31;++source) for(unsigned target=0;target<31;++target) {
    mons[target]={0,false,false,false}; pushes=pops=0;
    if(!QueueSourceTrap(&flow,source,target) || effect.condition!=22 ||
       effect.condData!=(3u|(source<<3)) || effect.pokeID!=target || pushes!=1 || pops!=1) return 1;
    for(unsigned blocked=0;blocked<3;++blocked) {
      mons[target].fainted=blocked==0; mons[target].ghost=blocked==1; mons[target].trapped=blocked==2;
      pushes=0; if(QueueSourceTrap(&flow,source,target) || pushes) return 2;
    }
  }
  for(unsigned slot=0;slot<31;++slot) for(unsigned success=0;success<2;++success)
  for(unsigned simulated=0;simulated<2;++simulated) for(unsigned move=0;move<920;++move) {
    sMoveState.lastSuccessfulSelectedMove[slot]=77; mons[slot].previousMove=move;
    vars[VAR_GENERAL_USE_FLAG]=success; flow.simulationCounter=simulated; record(&flow,slot);
    unsigned expected=simulated?77:success?move:0;
    if(sMoveState.lastSuccessfulSelectedMove[slot]!=expected) return 3;
    if(restricted(&mons[slot],move,0)!=((move==901 || move==893) && expected==move)) return 4;
  }
  for(unsigned slot=0;slot<31;++slot) for(unsigned simulated=0;simulated<2;++simulated) {
    flow.simulationCounter=simulated; vars[VAR_MON_ID]=slot; sMoveState.glaiveRushFlags=0x7fffffff;
    HandlerFieldGlaiveRushActionStart(0,&flow,31,0);
    if(sMoveState.glaiveRushFlags!=(simulated?0x7fffffffu:0x7fffffffu&~SlotMask(slot))) return 5;
    vars[VAR_DEFENDING_MON]=slot; vars[VAR_GENERAL_USE_FLAG]=0; vars[VAR_RATIO]=4096;
    HandlerFieldGlaiveRushAccuracy(0,&flow,31,0); HandlerFieldGlaiveRushDamage(0,&flow,31,0);
    if(vars[VAR_GENERAL_USE_FLAG]!=simulated || vars[VAR_RATIO]!=(simulated?8192u:4096u)) return 6;
  }
  return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-move-lifetime-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
