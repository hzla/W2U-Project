"""Independent lifetime oracles for native-suite regression repairs."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pokeweb_gameplay/w2u_moves.cpp"


class TerrainAndLaserLifetime(unittest.TestCase):
    def test_electric_terrain_blocks_new_sleep_without_waking_existing_sleep(self):
        text = SOURCE.read_text()
        table = re.search(r"FieldTerrainHandlers\[\].*?\};", text, re.S).group()
        self.assertIn("EVENT_ADD_CONDITION_CHECK_FAIL, HandlerTerrainPreventStatus", table)
        self.assertNotIn("EVENT_CHECK_SLEEP", table)
        self.assertNotIn("TerrainCureSleep", text)
        self.assertNotIn("HandlerElectricTerrainSwitchIn", text)
        self.assertNotIn("HandlerElectricTerrainNewMon", text)

    def test_actual_laser_focus_callbacks_cover_activation_and_next_turn_only(self):
        text = SOURCE.read_text()
        callbacks = "\n".join(re.search(
            rf'extern "C" (?:void|bool) W2U_MoveState_{name}\(.*?^\}}',
            text, re.M | re.S).group() for name in (
                "StartLaserFocus", "IsLaserFocused", "TickLaserFocus", "ClearLaserFocus"))
        program = r'''
using u32=unsigned;
struct {unsigned laserFocusTurns[6];} sMoveState;
bool IsValidSlot(unsigned slot){return slot<6;}
''' + callbacks + r'''
int main(){
 for(unsigned slot=0;slot<6;++slot){
  if(W2U_MoveState_IsLaserFocused(slot))return 1;
  W2U_MoveState_StartLaserFocus(slot);
  if(!W2U_MoveState_IsLaserFocused(slot))return 2;
  W2U_MoveState_TickLaserFocus(slot);
  if(!W2U_MoveState_IsLaserFocused(slot))return 3;
  W2U_MoveState_TickLaserFocus(slot);
  if(W2U_MoveState_IsLaserFocused(slot))return 4;
  W2U_MoveState_TickLaserFocus(slot);
  if(W2U_MoveState_IsLaserFocused(slot))return 5;
  W2U_MoveState_StartLaserFocus(slot);W2U_MoveState_ClearLaserFocus(slot);
  if(W2U_MoveState_IsLaserFocused(slot))return 6;
 }
 W2U_MoveState_StartLaserFocus(6);W2U_MoveState_TickLaserFocus(6);
 W2U_MoveState_ClearLaserFocus(6);
 return W2U_MoveState_IsLaserFocused(6);
}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
