"""SPA capacity and actual resident hook argument-forwarding oracles."""
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import audit_battle_particle_work as audit


def spa(resources=1, textures=1, flags=0):
    optional = b"\0" * sum(size for bit, size in audit.OPTIONAL_BLOCKS.items() if flags & (1 << bit))
    row = struct.pack("<I", flags) + b"\0" * 84 + optional
    header = bytearray(32)
    header[:8] = b" APS12_1"
    struct.pack_into("<HH", header, 8, resources, textures)
    struct.pack_into("<I", header, 24, 32 + len(row) * resources)
    texture = b" TPS" + b"\0" * 24 + struct.pack("<I", 32)
    return bytes(header) + row * resources + texture * textures


class ParticleWork(unittest.TestCase):
    def test_all_repository_assets_fit_and_inherited_overruns_are_represented(self):
        records = [audit.inspect_spa(path.read_bytes()) for path in (ROOT / "data/graphics/move_spas").glob("*.bin")]
        self.assertGreaterEqual(len(records), 253)
        self.assertEqual(max(record["work_bytes"] for record in records), 19860)
        self.assertGreater(sum(record["work_bytes"] > 0x4800 for record in records), 5)
        self.assertEqual(audit.BASE_BYTES, 17420)

    def test_bounds_counts_and_oversized_resources_fail_closed(self):
        self.assertEqual(audit.inspect_spa(spa(flags=1 << 24))["work_bytes"], 17420 + 32 + 8 + 20)
        for bad in (b"", spa()[:-1], b"wrong___" + spa()[8:], spa(resources=300)):
            with self.assertRaises(ValueError):
                audit.inspect_spa(bad)
        bad = bytearray(spa())
        struct.pack_into("<I", bad, 24, 33)
        with self.assertRaises(ValueError):
            audit.inspect_spa(bytes(bad))

    def test_actual_hooks_resize_both_sides_and_preserve_every_argument(self):
        source = (ROOT / "src/w2anim/w2u_particle_work.cpp").read_text().replace('#include "swantypes.h"', 'using u32=unsigned;')
        program = r'''
#include <initializer_list>
using u32=unsigned;
unsigned wanted;int checked;void* p=(void*)0x1000;const char* file="native";
extern "C" void* GFL_HeapAllocate(u32 h,u32 n,u32 c,const char* f,u32 l){
 if(h!=7||n!=wanted||c!=1||f!=file||l!=123)checked=-100;else ++checked;return p;}
extern "C" void* GFL_PTC_CreateEx(void* w,int n,int c,int p0,int low,int high,u32 h){
 if(w!=p||n!=(int)wanted||c!=1||p0!=2||low!=3||high!=4||h!=7)checked=-100;else ++checked;return p;}
''' + source + r'''
int main(){for(unsigned bytes:{0u,0x4800u,0x6000u,20000u}){
 wanted=bytes==0x4800?0x6000:bytes;checked=0;
 if(THUMB_BRANCH_LINK_BTLV_EFFECT_CMD_LoadSPA_0x48(7,bytes,1,file,123)!=p)return 1;
 if(THUMB_BRANCH_LINK_BTLV_EFFECT_CMD_LoadSPA_0x98(p,bytes,1,2,3,4,7)!=p||checked!=2)return 2;
}return 0;}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)


if __name__ == "__main__":
    unittest.main()
