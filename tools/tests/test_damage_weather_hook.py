"""Compile the weather-stage adapter and child callback, preserving real weather."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class DamageWeatherHook(unittest.TestCase):
    def test_only_the_attacking_water_move_gets_the_sun_exception(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        pieces = []
        for pattern in (r"static void HandlerHydroSteamDamageWeather\(.*?^\}",
                        r'extern "C" WEATHER THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0xDE\(.*?^\}'):
            match = re.search(pattern, text, re.S | re.M)
            self.assertIsNotNone(match)
            pieces.append(match.group(0))
        source = r'''
typedef unsigned u32; typedef unsigned WEATHER;
struct BattleEventItem {}; struct ServerFlow {};
enum { VAR_ATTACKING_MON=3, VAR_MOVE_ID=18, VAR_MOVE_TYPE=22, VAR_WEATHER=57,
       MOVE_HYDRO_STEAM=876, TYPE_WATER=10, WEATHER_SUN=1, WEATHER_RAIN=2,
       EVENT_W2U_DAMAGE_WEATHER=256 };
static unsigned vars[64], realWeather, calls, owner;
static bool loaded;
unsigned ServerEvent_GetWeather(ServerFlow*) { return realWeather; }
unsigned BattleEventVar_GetValue(unsigned key) { return vars[key]; }
void BattleEventVar_SetValue(unsigned key, unsigned value) { vars[key]=value; }
void BattleEventVar_RewriteValue(unsigned key, unsigned value) { vars[key]=value; }
static void HandlerHydroSteamDamageWeather(BattleEventItem*,ServerFlow*,u32,u32*);
void BattleEvent_CallHandlers(ServerFlow* flow, unsigned event) {
  if (event!=EVENT_W2U_DAMAGE_WEATHER) __builtin_trap();
  ++calls;
  if (loaded) HandlerHydroSteamDamageWeather(0,flow,owner,0);
}
'''
        source += "\n".join(pieces)
        source += r'''
int main() {
  ServerFlow flow;
  for (unsigned weather=0;weather<5;++weather)
  for (unsigned type=0;type<18;++type)
  for (unsigned move: {876u,33u})
  for (unsigned module=0;module<2;++module)
  for (unsigned slot: {0u,12u}) {
    realWeather=weather; vars[VAR_ATTACKING_MON]=0; vars[VAR_MOVE_ID]=move;
    vars[VAR_MOVE_TYPE]=type; loaded=module; owner=slot; calls=0;
    unsigned expected=weather;
    if (weather==1 && type==10 && move==876 && module && !slot) expected=2;
    if (THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0xDE(&flow)!=expected) return 1;
    if (realWeather!=weather) return 2;
    if (calls!=(weather==1)) return 3;
    if (vars[VAR_MOVE_ID]!=move || vars[VAR_MOVE_TYPE]!=type || vars[VAR_ATTACKING_MON]) return 4;
  }
  return 0;
}
'''
        source = "#include <initializer_list>\n" + source
        with tempfile.TemporaryDirectory(prefix="w2u-weather-stage-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
