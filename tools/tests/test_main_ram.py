"""Check real-RAM spans used by sprite guards and dynamic handler validation."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class MainRamTests(unittest.TestCase):
    def test_native_mode_and_complete_spans(self):
        source = r'''
#include <cassert>
#define __HW_H
using u32 = unsigned;
static unsigned mode, queries;
static int hw_isDSi() { ++queries; return mode; }
#include "util/main_ram.h"
int main() {
    for (mode=0;mode<2;++mode) {
        queries=0;
        assert(w2u::IsMainRamAddress(0x02000000,1));
        assert(w2u::IsMainRamAddress(0x023ffffe,2));
        assert(queries==0); // Native/PMC low code remains on the fast path.
        assert(!w2u::IsMainRamAddress(0,1));
        assert(!w2u::IsMainRamAddress(0x02000000,0));
        assert(!w2u::IsMainRamAddress(0x01ffffff,4));
        assert(w2u::IsMainRamAddress(0x023ffffe,4)==bool(mode));
        assert(w2u::IsMainRamAddress(0x02400000,2)==bool(mode));
        assert(w2u::IsMainRamAddress(0x02820000,512)==bool(mode));
        assert(w2u::IsMainRamAddress(0x02fffffe,2)==bool(mode));
        assert(!w2u::IsMainRamAddress(0x02fffffe,4));
        assert(!w2u::IsMainRamAddress(0x03000000,1));
        assert(!w2u::IsMainRamAddress(0xffffffff,0xffffffff));
        assert(!w2u::IsMainRamAddress(0x02000000,0xffffffff));
        assert(queries==4);
    }
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            executable = Path(tmp) / 'check'
            subprocess.run(['clang++', '-std=c++11', '-fsanitize=address,undefined',
                            '-I', str(ROOT / 'include'), '-I', str(ROOT / 'include/swan'), '-x', 'c++', '-', '-o', str(executable)],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == '__main__':
    unittest.main()
