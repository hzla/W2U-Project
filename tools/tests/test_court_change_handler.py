"""Court Change preserves durations/layers and rebuilds side-owned factors."""
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class CourtChangeHandler(unittest.TestCase):
    def test_veil_uses_native_screen_damage_phase(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        table = re.search(r'BattleEventHandlerTableEntry SideAuroraVeilHandlers\[\] = \{(.*?)\};', text, re.S).group(1)
        self.assertIn("EVENT_MOVE_DAMAGE_PROCESSING_2, HandlerSideAuroraVeilGuard", table)
        self.assertNotIn("EVENT_DEFENDER_GUARD", table)

    def test_vram_registration_uses_absolute_call(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        self.assertRegex(text, r'SideEffectEvent_AddItem\(u32 side, SIDE_EFFECT effect, ConditionData condition\)\s*__attribute__\(\(long_call\)\)')

    def test_real_transaction_native_and_custom_ownership(self):
        text = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()
        body = re.search(r'extern "C" bool W2U_MoveState_CourtChange\(.*?^\}', text, re.S | re.M).group()
        source = r'''
typedef unsigned u32; typedef unsigned char u8; typedef unsigned short u16;
struct ServerFlow { unsigned simulationCounter; };
struct BattleEventItem { unsigned side,id,active; } pool[64];
struct NativeSideEffectRecord { BattleEventItem* item; unsigned condition,elapsed,layers; } native[2][14];
struct SideState { BattleEventItem* item; u8 turns; bool active; };
struct { SideState stickyWeb[2],auroraVeil[2]; } sMoveState;
struct W2UBattleHandlerExport { unsigned* handlers; unsigned handlerCount; } api={0,2};
enum { SIDEEFF_STICKY_WEB=14,SIDEEFF_AURORA_VEIL=15,W2U_MECHANIC_SIDE=4,
       EVENTITEM_SIDE=2,EVENTPRI_SIDE_DEFAULT=2 };
#define W2U_ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
unsigned added,removed,missingApi,missingState;
NativeSideEffectRecord (*GetNativeSideState())[14] { return missingState?0:native; }
const W2UBattleHandlerExport* W2U_BattleStatic_Resolve(unsigned,unsigned) { return missingApi?0:&api; }
BattleEventItem* BattleEvent_AddItem(unsigned,unsigned id,unsigned,unsigned,unsigned side,unsigned*,unsigned) {
 for(unsigned i=0;i<64;++i) if(!pool[i].active) { pool[i]={side,id,1}; ++added; return &pool[i]; }
 __builtin_trap();
}
void BattleEventItem_Remove(BattleEventItem* item) { if(!item->active) __builtin_trap(); item->active=0; ++removed; }
BattleEventItem* SideEffectEvent_AddItem(unsigned side,unsigned id,unsigned condition) {
 auto& record=native[side][id]; if(record.item||record.layers) __builtin_trap();
 record={BattleEvent_AddItem(2,id,2,0,side,0,1),condition,0,1}; return record.item;
}
''' + body + r'''
int main() {
 ServerFlow flow={0};
 if(W2U_MoveState_CourtChange(&flow)) return 1;
 for(unsigned side=0;side<2;++side) for(unsigned id=0;id<14;++id) {
   SideEffectEvent_AddItem(side,id,100+id+side*20);
   native[side][id].elapsed=side+id%5;
   native[side][id].layers=1+(id==6?side+1:0);
 }
 for(unsigned side=0;side<2;++side) {
   sMoveState.stickyWeb[side]={BattleEvent_AddItem(2,14,2,0,side,0,1),0,true};
   sMoveState.auroraVeil[side]={BattleEvent_AddItem(2,15,2,0,side,0,1),u8(2+side*3),true};
 }
 unsigned before=added;
 flow.simulationCounter=1; if(W2U_MoveState_CourtChange(&flow)||added!=before) return 2;
 flow.simulationCounter=0; missingState=1; if(W2U_MoveState_CourtChange(&flow)||added!=before) return 3;
 missingState=0; missingApi=1; if(W2U_MoveState_CourtChange(&flow)||added!=before) return 4;
 missingApi=0;
 for(unsigned repeat=1;repeat<=2;++repeat) {
   if(!W2U_MoveState_CourtChange(&flow)) return 5;
   for(unsigned side=0;side<2;++side) for(unsigned id=0;id<14;++id) {
     unsigned src=(repeat==1 && id!=9 && id!=10)?1-side:side;
     const auto& r=native[side][id];
     if(r.condition!=100+id+src*20||r.elapsed!=src+id%5||r.layers!=1+(id==6?src+1:0)) return 6;
     if(!r.item||!r.item->active||r.item->side!=side||r.item->id!=id) return 7;
   }
   for(unsigned side=0;side<2;++side) {
     const auto& web=sMoveState.stickyWeb[side]; const auto& veil=sMoveState.auroraVeil[side];
     if(!web.active||!veil.active||web.item->side!=side||veil.item->side!=side||veil.turns!=2+((repeat==1?1-side:side)*3)) return 8;
   }
 }
 if(added-removed!=32) return 9;
 return 0;
}
'''
        with tempfile.TemporaryDirectory(prefix="w2u-court-change-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source,text=True,check=True)
            subprocess.run([str(executable)],check=True)

    def test_clean_us_native_literal_contract(self):
        import ndspy.rom
        # Optional local ROMs are never copied into published test artifacts.
        paths = [ROOT.parent / "Port-Pokeweb/cleanblack2.nds", ROOT / "build-stripped/White2Upgrade.nds"]
        if not all(path.exists() for path in paths):
            self.skipTest("Clean B2 and built W2 ROMs are required for the binary check")
        import struct
        for path in paths:
            overlay = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([169])[169]
            offset = 0x06898CF4-overlay.ramAddress
            self.assertEqual(struct.unpack_from("<H",overlay.data,offset)[0],0x22E0)
            self.assertEqual(struct.unpack_from("<H",overlay.data,offset+4)[0],0x4804)
            self.assertEqual(struct.unpack_from("<I",overlay.data,offset+0x18)[0],0x0689E960)
            self.assertEqual(overlay.data[0x06898C10-overlay.ramAddress:0x06898C10-overlay.ramAddress+4],bytes.fromhex("0fb4f0b5"))


if __name__ == "__main__":
    unittest.main()
