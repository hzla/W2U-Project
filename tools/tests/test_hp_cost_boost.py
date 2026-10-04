"""Compile actual HP/stat transaction, native layouts and complete HP rounding."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class HpCostBoost(unittest.TestCase):
    def test_payment_and_atomic_eligibility(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        header = (ROOT / "include/w2u_battle.h").read_text()
        pieces = []
        for pattern, source in (
            (r"struct HandlerParam_ShiftHP \{.*?^\};", header),
            (r"struct HandlerParam_CheckItem \{.*?^\};", header),
            (r"static u32 HpCostBoostPayment\(.*?^\}", text),
            (r"static void HandlerHpCostBoost\(.*?^\}", text),
        ):
            match = re.search(pattern, source, re.S | re.M)
            self.assertIsNotNone(match)
            pieces.append(match.group())
        source = r'''
#include <cstddef>
#include <initializer_list>
typedef unsigned u32; typedef unsigned char u8; typedef signed char s8;
typedef int s32; typedef unsigned StatStage;
struct HandlerParam_Header { u32 flags; };
struct BattleEventItem {}; struct ServerFlow {};
struct BattleMon { u32 maximum, hp, ability, fainted, stages[6]; } mon;
enum { VAR_ATTACKING_MON=3, VAR_TARGET_COUNT=52, VAR_MOVE_ID=18, VAR_MOVE_FAIL_FLAG=65,
       VALUE_MAX_HP=14, VALUE_CURRENT_HP=13, VALUE_EFFECTIVE_ABILITY=17,
       STATSTAGE_ATTACK=1, STATSTAGE_DEFENSE=2, STATSTAGE_SPECIAL_DEFENSE=4,
       STATSTAGE_SPEED=5, MOVE_CLANGOROUS_SOUL=775, MOVE_FILLET_AWAY=868,
       EFFECT_SHIFT_HP=8, EFFECT_CHECK_ITEM=33 };
u32 vars[80], calls, boosts, failures; alignas(4) u8 buffer[40];
u32 BattleEventVar_GetValue(u32 key) { return vars[key]; }
void BattleEventVar_RewriteValue(u32 key,u32 value) { vars[key]=value; ++failures; }
BattleMon* GetBattleMon(ServerFlow*,u32) { return &mon; }
bool BattleMon_IsFainted(BattleMon* p) { return p->fainted; }
u32 BattleMon_GetValue(BattleMon* p,u32 key) {
  return key==VALUE_MAX_HP ? p->maximum : key==VALUE_CURRENT_HP ? p->hp : p->ability;
}
bool BattleMon_IsStatChangeValid(BattleMon* p,StatStage stat,int direction) {
  return direction>0 ? p->stages[stat]<12 : p->stages[stat]>0;
}
void* BattleHandler_PushWork(ServerFlow*,u32 effect,u32 slot) {
  if (slot!=12 || (effect==8 ? calls!=0 : effect!=33 || calls!=1)) __builtin_trap();
  for (u8& byte: buffer) byte=0;
  return buffer;
}
void ApplyStatChange(ServerFlow*,u32 source,u32 target,StatStage stat,s8 volume,bool animate) {
  if (calls!=1 || source!=12 || target!=12 || !animate || volume!=(vars[18]==775 ? 1:2)) __builtin_trap();
  if (vars[18]==868 && (stat==2 || stat==4)) __builtin_trap();
  ++boosts;
}
void BattleHandler_PopWork(ServerFlow*,void*);
''' + "\n".join(pieces) + r'''
static_assert(sizeof(HandlerParam_ShiftHP)==40 && offsetof(HandlerParam_ShiftHP,volume)==16,
              "Native payment ABI");
static_assert(offsetof(HandlerParam_ShiftHP,pokeID)==7 && offsetof(HandlerParam_ShiftHP,itemReactionDisable)==6,
              "Native payment flags");
static_assert(sizeof(HandlerParam_CheckItem)==12 && offsetof(HandlerParam_CheckItem,reactionType)==8,
              "Native delayed item ABI");
void BattleHandler_PopWork(ServerFlow*,void* pointer) {
  if (calls==0) {
    auto* p=(HandlerParam_ShiftHP*)pointer;
    unsigned cost=vars[18]==775 ? mon.maximum*33/100 : mon.maximum/2;
    if (!cost) cost=1;
    if (p->pokeCount!=1 || p->pokeID[0]!=12 || p->effectDisable || !p->itemReactionDisable ||
        p->volume[0]!=-(int)cost || mon.hp<=cost) __builtin_trap();
  } else {
    auto* p=(HandlerParam_CheckItem*)pointer;
    if (p->pokeID!=12 || p->reactionType!=1 || boosts!=(vars[18]==775 ? 5:3)) __builtin_trap();
  }
  ++calls;
}
int main() {
  for (u32 hp=1;hp<=65535;++hp) {
    if (HpCostBoostPayment(hp,true)!=(hp*33/100 ? hp*33/100 : 1)) return 1;
    if (HpCostBoostPayment(hp,false)!=(hp/2 ? hp/2 : 1)) return 2;
  }
  ServerFlow flow;
  for (u32 move: {775u,868u}) for (u32 maximum: {1u,2u,3u,99u,175u,178u,235u,65535u})
  for (u32 ability: {0u,69u,86u,98u,126u}) for (u32 stage: {0u,6u,12u})
  for (u32 partial=0;partial<2;++partial) for (u32 boundary=0;boundary<3;++boundary) {
    const u32 cost=HpCostBoostPayment(maximum,move==775);
    mon={maximum,boundary==2 ? maximum : cost+boundary,ability,0,{stage,stage,stage,stage,stage,stage}};
    if (mon.hp>maximum) continue;
    if (partial) mon.stages[3]=6;
    vars[3]=12; vars[18]=move; vars[52]=1; vars[65]=0;
    calls=boosts=failures=0;
    bool possible=partial || (ability==126 ? stage>0 : stage<12);
    bool eligible=mon.hp>cost && possible;
    HandlerHpCostBoost(0,&flow,11,0);
    if (calls || failures) return 3;
    HandlerHpCostBoost(0,&flow,12,0);
    if (calls!=(eligible ? 2u:0u) || boosts!=(eligible ? (move==775 ? 5u:3u):0u) || failures) return 4;
    calls=boosts=failures=0; vars[52]=0;
    HandlerHpCostBoost(0,&flow,12,0);
    if (calls || boosts || failures) return 5;
    vars[52]=1; mon.fainted=1;
    HandlerHpCostBoost(0,&flow,12,0);
    if (calls || boosts || failures) return 6;
  }
  return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-hp-boost-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
