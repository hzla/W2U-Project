"""Run the actual pre-PMC parser on every child and malformed table mutations."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class RpmBounds(unittest.TestCase):
    def test_actual_api_validator_rejects_duplicates_bad_ranges_counts_and_priorities(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        functions = "\n".join(re.search(r'^bool ' + name + r'\(.*?^\}', source, re.M | re.S).group()
                              for name in ("IsRangeInside", "IsAligned", "IsValidHandlerPointer", "ValidateApi"))
        # Preserve the native pointer-width mask on the 64-bit host, whose
        # synthetic module addresses cannot be truncated to DS addresses.
        functions = functions.replace("~1u", "~u32(1u)")
        program = r'''
#include <cstdint>
using u8=unsigned char;using u16=unsigned short;using u32=uintptr_t;
enum W2UBattleMechanicKind {W2U_MECHANIC_ABILITY,W2U_MECHANIC_MOVE,W2U_MECHANIC_ITEM,
 W2U_MECHANIC_FIELD,W2U_MECHANIC_SIDE,W2U_MECHANIC_POSITION};
const u32 W2U_BATTLE_MODULE_MAGIC=0x4d423257,W2U_BATTLE_MODULE_ABI_VERSION=1,
 W2U_MAX_API_ENTRIES=96,W2U_MAX_HANDLERS_PER_ENTRY=64,W2U_BATTLE_MODULE_DEFAULT_PRIORITY=0xffff;
struct BattleEventHandlerTableEntry {u32 event;void (*handler)();};
struct W2UBattleHandlerExport {u16 kind,id,handlerCount,priority;const BattleEventHandlerTableEntry* handlers;};
struct W2UBattleModuleApi {unsigned magic;u16 abiVersion,entryCount;const W2UBattleHandlerExport* entries;};
struct W2UBattleModuleRecord {void* handle;const W2UBattleModuleApi* api;u32 fixedBytes;};
struct W2UBattleMechanicRoute {u16 kind,id;u8 module;};
W2UBattleMechanicRoute routes[]={{1,33,2},{5,7,2}};
const W2UBattleMechanicRoute* FindRoute(W2UBattleMechanicKind kind,u16 id){
 for(auto& r:routes)if(r.kind==kind&&r.id==id)return &r;return nullptr;}
namespace w2u {bool IsMainRamAddress(u32,u32){return false;}}
struct Image {W2UBattleModuleApi api;W2UBattleHandlerExport entries[2];BattleEventHandlerTableEntry handlers[2];alignas(4) u8 code[4];};
''' + functions + r'''
int main(){
 Image image={};image.api={0x4d423257,1,2,image.entries};
 image.handlers[0]={1,(void (*)())(image.code+1)};image.handlers[1]=image.handlers[0];
 image.entries[0]={1,33,1,0xffff,image.handlers};image.entries[1]={5,7,1,8,image.handlers+1};
 W2UBattleModuleRecord record={&image,&image.api,sizeof(image)};
 auto good=image;
 if(!ValidateApi(&record,2,W2U_MECHANIC_MOVE,33)||ValidateApi(&record,1,W2U_MECHANIC_MOVE,33)||
    ValidateApi(&record,2,W2U_MECHANIC_MOVE,34))return 1;
 for(unsigned mutation=0;mutation<13;++mutation){
  image=good;record.api=&image.api;
  switch(mutation){
   case 0:image.api.magic^=1;break;
   case 1:image.api.abiVersion=2;break;
   case 2:image.api.entryCount=0;break;
   case 3:image.api.entryCount=97;break;
   case 4:image.api.entries=(W2UBattleHandlerExport*)((u8*)&image+sizeof(image));break;
   case 5:image.entries[1]=image.entries[0];break;
   case 6:image.entries[0].handlerCount=0;break;
   case 7:image.entries[0].handlerCount=65;break;
   case 8:image.entries[0].priority=256;break;
   case 9:image.entries[0].handlers=(BattleEventHandlerTableEntry*)((u8*)&image+1);break;
   case 10:image.handlers[0].handler=nullptr;break;
   case 11:image.entries[0].kind=6;break;
   case 12:record.api=(W2UBattleModuleApi*)((u8*)&image+sizeof(image));break;
  }
  if(ValidateApi(&record,2,W2U_MECHANIC_MOVE,33))return 2;
 }
 return 0;
}
'''
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-fsanitize=address,undefined", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_actual_parser_rejects_truncation_overflows_constructors_and_patch_targets(self):
        source = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        constants = "\n".join(line for line in source.splitlines() if line.startswith("constexpr u32 W2U_RPM_"))
        functions = "\n".join(re.search(r'^(?:u16|u32|bool) ' + name + r'\(.*?^\}', source, re.M | re.S).group()
                              for name in ("ReadU16", "ReadU32", "AddFileOffset", "ValidateRpmTables", "ParseRpmHeader"))
        program = r'''
#include <fstream>
#include <iterator>
#include <vector>
using u8=unsigned char;using u16=unsigned short;using u32=unsigned;
''' + constants + "\n" + functions + r'''
bool valid(std::vector<u8>& d){u32 expanded,fixed;return ParseRpmHeader(d.data(),d.size(),&expanded,&fixed);}
void put(std::vector<u8>& d,unsigned n,unsigned v){for(unsigned k=0;k<4;++k)d[n+k]=v>>(k*8);}
int main(int argc,char** argv){
 for(int input=1;input<argc;++input){
  std::ifstream file(argv[input],std::ios::binary);std::vector<u8> original((std::istreambuf_iterator<char>(file)),{});
  if(!valid(original))return 1;
  unsigned e=ReadU32(original.data(),8),info=e+ReadU32(original.data(),e+8);
  unsigned sym=e+ReadU32(original.data(),info+4),rel=e+ReadU32(original.data(),info+8);
  for(unsigned length=0;length<original.size();++length){auto truncated=original;truncated.resize(length);if(valid(truncated))return 2;}
  for(unsigned at:{8u,e+8,e+12,e+16,info+4,info+8,info+24,info+28,sym+16,sym+20,rel+8,rel+12,rel+16,rel+20}){
   auto bad=original;put(bad,at,0xfffffffeu);if(valid(bad))return 3;
  }
  auto bad=original;put(bad,info+24,0);if(valid(bad))return 4; // static constructor
  bad=original;put(bad,e+12,0x20000);if(valid(bad))return 5; // BSS exceeds allocation
  bad=original;put(bad,rel+4,0x2000000);if(valid(bad))return 6; // already relocated image
  for(unsigned kind=0;kind<2;++kind){
   unsigned list=e+ReadU32(original.data(),rel+8+kind*4);
   if(ReadU32(original.data(),list)){
    bad=original;put(bad,list+4,0xfffffffcu);if(valid(bad))return 7; // patch address out of code
    bad=original;bad[list+9]=5;if(valid(bad))return 8; // external full-copy hook
    bad=original;bad[list+8]=0;if(valid(bad))return 9; // external module index
   }
  }
 }
 return 0;
}
'''
        modules = sorted((ROOT / "vfs/data/lib/w2u_battle").glob("*/*.dll"))
        self.assertEqual(len(modules), 30)
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-fsanitize=address,undefined", "-x", "c++", "-o", str(executable), "-"], input=program, text=True, check=True)
            subprocess.run([str(executable), *map(str, modules)], check=True)


if __name__ == "__main__":
    unittest.main()
