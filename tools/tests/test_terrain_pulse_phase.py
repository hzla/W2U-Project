"""Compile the real final parameter phase and Terrain Pulse callbacks."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class TerrainPulsePhase(unittest.TestCase):
    def test_final_type_does_not_change_native_context_or_power_rules(self):
        moves = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        abilities = (ROOT / "src/pokeweb_gameplay/w2u_abilities.cpp").read_text()
        pieces = []
        for text, pattern in (
            (moves, r"static u32 TerrainPulseType\(.*?^\}"),
            (moves, r"static void HandlerTerrainPulseType\(.*?^\}"),
            (moves, r"static void HandlerTerrainPulsePower\(.*?^\}"),
            (abilities, r'extern "C" void THUMB_BRANCH_ServerEvent_GetMoveParam\([^;]*?^\{.*?^\}'),
        ):
            match = re.search(pattern, text, re.S | re.M)
            self.assertIsNotNone(match)
            pieces.append(match.group(0))
        source = r'''
#include <initializer_list>
typedef unsigned u32; typedef unsigned short u16; typedef unsigned char u8;
typedef unsigned MOVE_ID;
struct BattleEventItem {}; struct ServerFlow {}; struct BattleMon {};
struct MoveParam { u16 moveID, originalMoveID, userType; u8 moveType, damageType;
                   u32 category, targetType, flags; };
enum { VAR_MON_ID=2, VAR_ATTACKING_MON=3, VAR_MOVE_ID=18, VAR_MOVE_TYPE=22,
       VAR_USER_TYPE=23, VAR_MOVE_CATEGORY=26, VAR_TARGET_TYPE=27,
       VAR_MOVE_POWER=48, VAR_NO_TYPE_EFFECTIVENESS=56,
       MOVE_TERRAIN_PULSE=805, TYPE_NORMAL=0, TYPE_ELECTRIC=12,
       TYPE_GRASS=11, TYPE_FAIRY=17, TYPE_PSYCHIC=13, TYPE_NULL=18,
       TERRAIN_ELECTRIC=1, TERRAIN_GRASSY=2, TERRAIN_MISTY=3, TERRAIN_PSYCHIC=4,
       EVENT_MOVE_PARAM=40, EVENT_W2U_MOVE_PARAM_FINAL=257, MVDATA_TARGET=20 };
static u32 vars[64], terrain, abilityType, owner, calls, depth;
static bool floating, electrified, ion, loaded;
static BattleMon mon;
BattleMon* GetBattleMon(ServerFlow*, u32 slot) { return slot==0 ? &mon : nullptr; }
bool IsGrounded(ServerFlow*, BattleMon* mon) { return mon && !floating; }
u32 W2U_MoveState_GetTerrain() { return terrain; }
bool W2U_MoveState_IsElectrified(u32 slot) { return slot==0 && electrified; }
bool W2U_MoveState_IsIonDelugeActive() { return ion; }
u32 BattleMon_GetID(BattleMon*) { return 0; }
u32 BattleMon_GetPokeType(BattleMon*) { return 0x0d0d; }
u32 PML_MoveGetType(u32) { return TYPE_NORMAL; }
u32 PML_MoveGetCategory(u32) { return 2; }
u32 PML_MoveGetParam(u32, u32) { return 0; }
u32 BattleEventVar_GetValue(u32 key) { return vars[key]; }
void BattleEventVar_SetValue(u32 key, u32 value) { vars[key]=value; }
void BattleEventVar_SetConstValue(u32 key, u32 value) { vars[key]=value; }
void BattleEventVar_SetRewriteOnceValue(u32 key, u32 value) { vars[key]=value; }
void BattleEventVar_RewriteValue(u32 key, u32 value) { vars[key]=value; }
void BattleEventVar_Push() { ++depth; }
void BattleEventVar_Pop() { --depth; }
static void HandlerTerrainPulseType(BattleEventItem*,ServerFlow*,u32,u32*);
void BattleEvent_CallHandlers(ServerFlow* flow, u32 event) {
  if (event==EVENT_MOVE_PARAM) {
    if (calls++) __builtin_trap();
    if (electrified || ion) vars[VAR_MOVE_TYPE]=TYPE_ELECTRIC;
    // Native Normalize always rewrites; -ates only convert Normal. This
    // deliberately runs after the ordinary move/position callbacks.
    if (abilityType==TYPE_NORMAL) vars[VAR_MOVE_TYPE]=TYPE_NORMAL;
    else if (abilityType!=TYPE_NULL && vars[VAR_MOVE_TYPE]==TYPE_NORMAL)
      vars[VAR_MOVE_TYPE]=abilityType;
  } else if (event==EVENT_W2U_MOVE_PARAM_FINAL) {
    if (calls++!=1 || depth!=1) __builtin_trap();
    if (loaded) HandlerTerrainPulseType(nullptr,flow,owner,nullptr);
  } else __builtin_trap();
}
'''
        source += "\n".join(pieces)
        source += r'''
int main() {
 ServerFlow flow; MoveParam param;
 for (unsigned move: {805u,33u})
 for (terrain=0;terrain<5;++terrain)
 for (unsigned airborne=0;airborne<2;++airborne)
 for (unsigned ability: {18u,0u,14u,17u,2u,12u})
 for (unsigned module=0;module<2;++module)
 for (unsigned electric=0;electric<2;++electric)
 for (unsigned deluge=0;deluge<2;++deluge)
 for (unsigned slot: {0u,12u}) {
  floating=airborne; abilityType=ability; loaded=module;
  electrified=electric; ion=deluge; owner=slot; calls=depth=0;
  THUMB_BRANCH_ServerEvent_GetMoveParam(&flow,move,&mon,&param);
  unsigned expected=(electric || deluge) ? TYPE_ELECTRIC : TYPE_NORMAL;
  if (ability==TYPE_NORMAL) expected=TYPE_NORMAL;
  else if (ability!=TYPE_NULL && expected==TYPE_NORMAL) expected=ability;
  if (move==805 && loaded && slot==0) {
   expected=(!airborne && terrain) ?
     (terrain==1 ? 12 : terrain==2 ? 11 : terrain==3 ? 17 : 13) : 0;
   if (electric || (!expected && deluge)) expected=12;
  }
  if (param.moveType!=expected || param.damageType!=expected) return 1;
  if (param.moveID!=move || param.originalMoveID!=move || param.userType!=0x0d0d
      || param.category!=2 || param.targetType || param.flags || depth || calls!=2) return 2;
  vars[VAR_MOVE_ID]=move; vars[VAR_ATTACKING_MON]=0; vars[VAR_MOVE_POWER]=50;
  HandlerTerrainPulsePower(nullptr,&flow,slot,nullptr);
  if (vars[VAR_MOVE_POWER]!=(move==805 && !slot && !airborne && terrain ? 100u : 50u)) return 3;
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-terrain-phase-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
