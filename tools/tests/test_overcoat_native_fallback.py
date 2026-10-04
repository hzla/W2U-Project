"""Compile the actual registration body to guard its explicit native fallback."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class OvercoatNativeFallback(unittest.TestCase):
    def test_missing_upgrade_preserves_weather_but_custom_ids_never_fall_through(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_abilities.cpp").read_text()
        body = re.search(r'extern "C" BattleEventItem\* THUMB_BRANCH_AbilityEvent_AddItem\(.*?^\}', text, re.S | re.M)
        self.assertIsNotNone(body)
        source = r'''
#define W2U_DYNAMIC_BATTLE_CORE 1
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
typedef unsigned short u16; typedef unsigned u32; typedef unsigned ABILITY;
enum { VALUE_ABILITY, W2U_MECHANIC_ABILITY=0, ABIL_OVERCOAT=142 };
struct BattleEventItem {}; struct BattleMon { unsigned ability; };
struct BattleEventHandlerTableEntry {};
struct W2UBattleHandlerExport { const BattleEventHandlerTableEntry* handlers; unsigned handlerCount; };
typedef void (*Getter)();
struct AbilityEventAddTable { unsigned ability; Getter func; };
struct W2UVanillaAbilityAliasEventAddTable { unsigned ability, vanillaAbility; };
static BattleEventItem nativeEvent, upgradedEvent;
static BattleEventHandlerTableEntry handlers[2];
static W2UBattleHandlerExport exported = { handlers, 2 };
static bool available;
unsigned BattleMon_GetValue(BattleMon* mon, unsigned) { return mon->ability; }
bool W2U_BattleModules_IsManaged(unsigned, u16 ability) { return ability==142 || ability==170; }
const W2UBattleHandlerExport* W2U_BattleModules_Resolve(unsigned, u16) { return available ? &exported : 0; }
BattleEventItem* AddAbilityEvent(BattleMon*, ABILITY, BattleEventHandlerTableEntry* table, unsigned count) {
    return table==handlers && count==2 ? &upgradedEvent : 0;
}
void getter() {}
BattleEventItem* GetAbilityEvent(BattleMon*, ABILITY, Getter callback) { return callback==getter ? &nativeEvent : 0; }
static W2UVanillaAbilityAliasEventAddTable sVanillaAbilityAliasEventAddTable[] = {{230,29}};
static AbilityEventAddTable nativeTable[] = {{142,getter},{170,getter},{29,getter}};
#define W2U_VANILLA_ABILITY_EVENT_TABLE nativeTable
#define W2U_VANILLA_ABILITY_EVENT_TABLE_COUNT 3u
'''
        source += body.group(0)
        source += r'''
int main() {
    BattleMon mon = {142};
    if (THUMB_BRANCH_AbilityEvent_AddItem(&mon) != &nativeEvent) return 1;
    mon.ability=170;
    if (THUMB_BRANCH_AbilityEvent_AddItem(&mon)) return 2;
    available=true;
    if (THUMB_BRANCH_AbilityEvent_AddItem(&mon) != &upgradedEvent) return 3;
    mon.ability=142;
    if (THUMB_BRANCH_AbilityEvent_AddItem(&mon) != &upgradedEvent) return 4;
    mon.ability=230;
    if (THUMB_BRANCH_AbilityEvent_AddItem(&mon) != &nativeEvent) return 5;
    mon.ability=999;
    if (THUMB_BRANCH_AbilityEvent_AddItem(&mon)) return 6;
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-overcoat-fallback-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
