"""Native call/copy restrictions retain every non-NPC predicate/delegate."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class NpcMovePolicy(unittest.TestCase):
    def test_resident_policy_and_native_copy_delegate(self):
        # The predicates are resident C (move_lists.c); the hooks and the copy handler are w2u_moves.cpp's
        lists = (ROOT / "src/mechanics/resident/move_lists.c").read_text()
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        parts = []
        for source_text, pattern in (
                (lists, r'^b32 W2U_MoveIsRestrictedNpcAttack\(.*?^\}'),
                (lists, r'^b32 W2U_IsAssistExcludedMove\(.*?^b32 W2U_IsCopycatExcludedMove\([^\n]*'),
                (text, r'^extern "C" b32 THUMB_BRANCH_LINK_167_0x21CC4DC\(.*?THUMB_BRANCH_LINK_167_0x21CC7D6\([^\n]*'),
                (text, r'static void HandlerNativeCopyRestricted\(.*?^\}')):
            match = re.search(pattern, source_text, re.S | re.M)
            self.assertIsNotNone(match, pattern)
            parts.append(match.group())
        source = r'''
typedef unsigned u32; typedef unsigned short u16; typedef unsigned MOVE_ID; typedef bool b32;
#define IsAssistExcludedMove BattleMove_AssistIsForbidden
#define IsSleepTalkExcludedMove BattleMove_SleepTalkIsForbidden
#define IsMeFirstExcludedMove BattleMove_MeFirstIsForbidden
#define IsCopycatExcludedMove BattleMove_CopycatIsForbidden
enum {MOVE_BLAZING_TORQUE=896,MOVE_MAGICAL_TORQUE=900,MOVE_SKETCH=166,MOVE_REVIVAL_BLESSING=863,VAR_ATTACKING_MON=3,
  VAR_TARGET_COUNT=5,VAR_TARGET_MON_ID=6,EVENT_UNCATEGORIZED_MOVE=160};
struct BattleEventItem { unsigned move; }; struct ServerFlow {}; struct BattleMon {};
typedef void (*Handler)(BattleEventItem*,ServerFlow*,unsigned,unsigned*);
struct BattleEventHandlerTableEntry { unsigned eventType; Handler handler; };
typedef BattleEventHandlerTableEntry* (*W2UNativeMoveGetter)(unsigned*);
unsigned calls,delegates,lookup,owner,targetCount,previous,original; bool nativeResult;
bool BattleMove_AssistIsForbidden(unsigned) { ++calls; return nativeResult; }
bool BattleMove_SleepTalkIsForbidden(unsigned) { ++calls; return nativeResult; }
bool BattleMove_MeFirstIsForbidden(unsigned) { ++calls; return nativeResult; }
bool BattleMove_CopycatIsForbidden(unsigned) { ++calls; return nativeResult; }
unsigned BattleEventVar_GetValue(unsigned key) { return key==3?owner:key==5?targetCount:12; }
BattleMon mon; BattleMon* GetBattleMon(ServerFlow*,unsigned) { return &mon; }
unsigned BattleMon_GetPreviousMove(BattleMon*) { return previous; }
unsigned BattleMon_GetPreviousMoveID(BattleMon*) { return original; }
unsigned GetEventItemMove(BattleEventItem* item) { return item->move; }
void nativeHandler(BattleEventItem* item,ServerFlow*,unsigned slot,unsigned* work) {
  if((item->move!=102 && item->move!=166) || slot!=0 || *work!=123) __builtin_trap();
  ++delegates;
}
BattleEventHandlerTableEntry entries[]={{1,0},{160,nativeHandler}};
BattleEventHandlerTableEntry* nativeGetter(unsigned* count) { *count=2; return entries; }
W2UNativeMoveGetter W2U_FindNativeMoveGetter(unsigned move) { lookup=move; return nativeGetter; }
''' + "\n".join(parts) + r'''
int main() {
  bool (*policies[])(unsigned)={THUMB_BRANCH_LINK_167_0x21CC4DC,THUMB_BRANCH_LINK_167_0x21CC5A2,
    THUMB_BRANCH_LINK_167_0x21CC754,THUMB_BRANCH_LINK_167_0x21CC7D6};
  for(unsigned id=0;id<920;++id) for(unsigned value=0;value<2;++value) for(auto policy:policies) {
    calls=0; nativeResult=value; bool restricted=id>=896 && id<=900;
    if(policy(id)!=(restricted || value) || calls!=(restricted?0:1)) return 1;
  }
  ServerFlow flow; unsigned work=123;
  for(unsigned copy: {102u,166u}) for(unsigned id=0;id<920;++id)
  for(unsigned wrongOwner=0;wrongOwner<2;++wrongOwner) for(unsigned count=0;count<2;++count)
  for(unsigned oldTorque=0;oldTorque<2;++oldTorque) {
    BattleEventItem item={copy}; owner=wrongOwner; targetCount=count;
    previous=id; original=oldTorque?896:id; delegates=0; lookup=0;
    HandlerNativeCopyRestricted(&item,&flow,0,&work);
    bool shouldDelegate=!wrongOwner && count && !(id>=896&&id<=900) && !oldTorque && !(copy==166&&id==863);
    if(delegates!=shouldDelegate || (shouldDelegate && lookup!=copy)) return 2;
  }
  return 0;
}
'''.replace('for(unsigned copy: {102u,166u})', 'for(unsigned copyIndex=0;copyIndex<2;++copyIndex)')
        # Avoid a standard-library initializer_list in the production-like
        # no-library compilation while preserving both native copy callers.
        source = source.replace('BattleEventItem item={copy};', 'unsigned copy=copyIndex?166:102; BattleEventItem item={copy};')
        with tempfile.TemporaryDirectory(prefix="w2u-npc-policy-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
