"""Compile the final-damage adapter and read-only Disguise calculation path."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class FinalDamageHook(unittest.TestCase):
    def test_existing_and_fixed_damage_contexts_without_shared_mutation(self):
        moves = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        abilities = (ROOT / "src/pokeweb_gameplay/w2u_abilities.cpp").read_text()
        patterns = (
            (abilities, r"static BattleMon\* DisguiseIntactTarget\(.*?^\}"),
            (abilities, r"static void HandlerDisguisePreventDamage\(.*?^\}"),
            (moves, r'extern "C" void W2U_DispatchFinalMoveDamage\(.*?^\}'),
        )
        bodies = []
        for text, pattern in patterns:
            match = re.search(pattern, text, re.S | re.M)
            self.assertIsNotNone(match)
            bodies.append(match.group())
        source = r'''
typedef unsigned u32; typedef unsigned BattleEventType;
enum { VAR_DAMAGE=1, VAR_DEFENDING_MON=2, VALUE_FORM=3, SPECIES_778=778 };
struct BattleEventItem {};
struct BattleMon { u32 species, form, hp, substitute; } mon;
struct ServerFlow { void* pokeCon; };
u32 damageValue, labels, creates, observedDamage, owner, calls;
u32 BattleEventVar_GetValue(u32 key) { return key==VAR_DAMAGE ? damageValue : 12; }
bool BattleEventVar_GetValueIfExist(u32, u32* out) { *out=damageValue; return labels; }
void BattleEventVar_SetValue(u32, u32 value) {
    if (labels) __builtin_trap();
    labels=1; ++creates; damageValue=value;
}
void BattleEventVar_RewriteValue(u32, u32 value) {
    if (!labels) __builtin_trap();
    damageValue=value;
}
BattleMon* PokeCon_GetBattleMon(void*,u32) { return &mon; }
u32 BattleMon_GetValue(BattleMon* mon,u32) { return mon->form; }
bool BattleMon_IsSubstituteActive(BattleMon* mon) { return mon->substitute; }
static void HandlerDisguisePreventDamage(BattleEventItem*,ServerFlow*,u32,u32*);
void BattleEvent_CallHandlers(ServerFlow* flow,BattleEventType event) {
    if (event!=0x48) __builtin_trap();
    ++calls; observedDamage=damageValue;
    HandlerDisguisePreventDamage(0,flow,owner,0);
}
''' + "\n".join(bodies) + r'''
int main() {
    ServerFlow flow={&mon};
    for (u32 fixed=0;fixed<2;++fixed)
    for (u32 form=0;form<2;++form)
    for (u32 substitute=0;substitute<2;++substitute)
    for (u32 wrongSpecies=0;wrongSpecies<2;++wrongSpecies)
    for (u32 wrongOwner=0;wrongOwner<2;++wrongOwner) {
        labels=!fixed; creates=0; calls=0; owner=12+wrongOwner;
        mon={778+wrongSpecies,form,130,substitute};
        for (u32 estimate=0;estimate<100;++estimate) {
            damageValue=999; u32 result=50+estimate;
            W2U_DispatchFinalMoveDamage(&flow,0x48,&result);
            if (observedDamage!=50+estimate) return 1;
            bool blocked=!form && !substitute && !wrongSpecies && !wrongOwner;
            if (result!=(blocked ? 0 : 50+estimate)) return 2;
            if (mon.hp!=130 || mon.form!=form || mon.substitute!=substitute) return 3;
        }
        if (labels!=1 || creates!=fixed || calls!=100) return 4;
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-final-damage-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_both_builds_include_native_stack_adapter(self):
        assembly = (ROOT / "src/pokeweb_gameplay/w2u_damage_hooks.s").read_text().split(
            "THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x1C0:", 1)[1].split(".size", 1)[0]
        self.assertIn("add r2, sp, #8", assembly)
        self.assertIn("bx r3", assembly)
        self.assertNotIn("push", assembly)
        self.assertIn("'w2u_damage_hooks.s'", (ROOT / "src/pokeweb_gameplay/meson.build").read_text())
        black = (ROOT / "src/meson.build").read_text().split("b2u_main_asm_inputs = [", 1)[1].split("]", 1)[0]
        self.assertIn("pokeweb_gameplay/b2_baseline/w2u_damage_hooks.s", black)


if __name__ == "__main__":
    unittest.main()
