"""Compile the resident LZ guard and unload path against independent oracles."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/w2anim/w2u_anim_streams.cpp"


class W2AnimRuntime(unittest.TestCase):
    def run_program(self, program):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-fsanitize=address,undefined", "-x", "c++", "-o", str(executable), "-"],
                           input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_actual_lz_guard_accepts_formats_and_rejects_corruption(self):
        callback = re.search(r"bool ValidLz\(.*?^\}", SOURCE.read_text(), re.M | re.S).group()
        program = "#include <vector>\nusing u8=unsigned char;using u32=unsigned;constexpr unsigned SLOT_TEX_BYTES=16384;\n" + callback + r'''
int main(){
 std::vector<u8> literal={0x10,0,18,0};
 for(unsigned n=0;n<4608;n+=8){literal.push_back(0);for(unsigned k=0;k<8;++k)literal.push_back(n+k);}
 if(!ValidLz(literal.data(),literal.size(),4608))return 1;
 for(unsigned kind:{0x10u,0x11u}){literal[0]=kind;if(!ValidLz(literal.data(),literal.size(),4608))return 2;}
 literal.pop_back();if(ValidLz(literal.data(),literal.size(),4608))return 3;
 u8 l11long[]={0x11,0,18,0,0x40,0,0x11,0x0e,0xe0,0};
 if(!ValidLz(l11long,sizeof(l11long),4608))return 4;
 u8 l11medium[]={0x11,18,0,0,0x40,0,0,0,0};
 if(!ValidLz(l11medium,sizeof(l11medium),18))return 5;
 u8 l11short[]={0x11,4,0,0,0x40,0,0x20,0};
 if(!ValidLz(l11short,sizeof(l11short),4))return 6;
 u8 bad[]={0x10,3,0,0,0x80,0,0};
 if(ValidLz(bad,sizeof(bad),3)||ValidLz(l11long,sizeof(l11long),16384)||ValidLz(nullptr,0,0))return 7;
 l11long[9]=1;if(ValidLz(l11long,sizeof(l11long),4608))return 8; // distance exceeds produced bytes
 return 0;
}
'''
        self.run_program(program)

    def test_actual_module_unload_releases_all_buffers_task_and_file_once(self):
        source = SOURCE.read_text()
        free = re.search(r"void Free\(.*?^\}", source, re.M | re.S).group()
        unload = re.search(r'extern "C" void W2U_AnimStreams_OnModuleUnload\(.*?^\}', source, re.M | re.S).group()
        program = r'''
using u8=unsigned char;using u32=unsigned;
struct Stream{u8 active,pending,palettePending,indepPending,role;void* indepBmp;void* meta;void* lz;void* staging;};
Stream g_streams[8];void* g_vblankTask=(void*)1;bool g_fileOpen=true;int g_fileState=1,g_file;u32 g_fileSize=100,g_evoAdds=2;
unsigned frees,tasks,closes;
void GFL_HeapFree(void*){++frees;}void GFL_TCBRemove(void*){++tasks;}
namespace w2u{void CloseFile(void*){++closes;}}
''' + free + "\n" + unload + r'''
int main(){for(auto& s:g_streams){s.active=1;s.pending=s.palettePending=1;s.meta=(void*)2;s.lz=(void*)3;s.staging=(void*)4;}
 W2U_AnimStreams_OnModuleUnload();if(frees!=24||tasks!=1||closes!=1||g_fileOpen||g_fileSize||g_fileState||g_evoAdds)return 1;
 for(auto& s:g_streams)if(s.active||s.pending||s.palettePending||s.meta||s.lz||s.staging)return 2;
 W2U_AnimStreams_OnModuleUnload();return frees!=24||tasks!=1||closes!=1;
}
'''
        self.run_program(program)


if __name__ == "__main__":
    unittest.main()
