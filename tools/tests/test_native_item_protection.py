"""Native form-item predicate and replacement ABI regression guards."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class NativeItemProtection(unittest.TestCase):
    def test_native_item_sets(self):
        source = '''
#include "w2u_native_item_protection.h"
int main() {
    for (unsigned item = 0; item < 920; ++item) {
        if (W2U_IsNativeProtectedFormItem(487, item) != (item == 112)) return 1;
        if (W2U_IsNativeProtectedFormItem(493, item) != (item >= 298 && item <= 313)) return 2;
        if (W2U_IsNativeProtectedFormItem(649, item) != (item >= 116 && item <= 119)) return 3;
        if (W2U_IsNativeProtectedFormItem(151, item)) return 4;
    }
    return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-item-predicate-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-I", str(ROOT / "include"),
                            "-o", str(executable), "-"], input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_hook_accepts_species_and_never_calls_its_alias(self):
        code = (ROOT / "src/pokeweb_gameplay/w2u_mega.cpp").read_text()
        hook = code.split('extern "C" bool THUMB_BRANCH_HandlerCommon_IsUnremovableItem', 1)[1].split("\n}", 1)[0]
        self.assertIn("(SPECIES species, ITEM itemID)", hook)
        self.assertNotIn("GiratinaArceusGenesectItemCheck(", hook)
        self.assertIn("FindMegaEntry(species, itemID)", hook)


if __name__ == "__main__":
    unittest.main()
