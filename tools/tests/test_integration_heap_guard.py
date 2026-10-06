"""Exercise actual free-list validation without entering the native allocator."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class HeapGuard(unittest.TestCase):
    def test_valid_fragmented_and_corrupt_free_lists(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        pieces = [re.search(r"bool IsPmcHeapRange\(.*?^\}", source, re.M | re.S).group(),
                  re.search(r"u32 LargestFreePmcBlock\(.*?^\}", source, re.M | re.S).group()]
        program = r'''
#include <cstdint>
using u8=unsigned char;using u32=uintptr_t;
struct W2UPmcHeapBlock {u32 size;W2UPmcHeapBlock* next;u32 pad;void* allocator;};
struct W2UPmcHeapArea {void* vtable;u8* heapBase;u32 totalSize;W2UPmcHeapBlock* freeBlocks;};
constexpr u32 W2U_PMC_HEAP_MAX_FREE_BLOCKS=512;
alignas(8) u8 storage[4096];W2UPmcHeapArea heap;W2UPmcHeapArea* sPmcHeap;
void EnsurePmcHeap(){}
bool IsMainRamPointer(const void* p){return p && !(reinterpret_cast<u32>(p)&3);}
''' + "\n".join(pieces) + r'''
int main(){
 if(LargestFreePmcBlock()!=0)return 1;
 sPmcHeap=&heap;heap.heapBase=storage;heap.totalSize=sizeof(storage);
 auto* a=(W2UPmcHeapBlock*)storage;auto* b=(W2UPmcHeapBlock*)(storage+256);
 a->size=128;a->next=b;b->size=1024;b->next=nullptr;heap.freeBlocks=a;
 if(LargestFreePmcBlock()!=1024)return 2;
 b->size=4096;if(LargestFreePmcBlock()!=0)return 3;b->size=1024;
 b->next=a;if(LargestFreePmcBlock()!=0)return 4;b->next=nullptr;
 b->size=1023;if(LargestFreePmcBlock()!=0)return 5;b->size=1024;
 a->next=(W2UPmcHeapBlock*)(storage+sizeof(storage));if(LargestFreePmcBlock()!=0)return 6;
 a->next=nullptr;if(LargestFreePmcBlock()!=128)return 7;
 heap.freeBlocks=nullptr;if(LargestFreePmcBlock()!=0)return 8;
 return 0;
}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-fsanitize=address,undefined", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_telemetry_retains_bss_and_unload_clears_heap_cache(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        self.assertIn("currentChildBytes += fixedSize + expandedSize - fileSize", source)
        self.assertIn("sPmcHeap = 0;", source[source.index("int DllMain("):])


if __name__ == "__main__":
    unittest.main()
