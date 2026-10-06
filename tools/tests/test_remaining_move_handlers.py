"""Compile new resident contracts; retail battle outcomes live in tests/battle."""
import json
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
TEXT = (ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").read_text()


def bodies(*names):
    return "\n".join(re.search(r'(?:static|extern "C") [^\n]+ ' + name + r'\(.*?^\}', TEXT, re.S | re.M).group() for name in names)


def compiled(source):
    with tempfile.TemporaryDirectory(prefix="w2u-remaining-") as directory:
        executable = Path(directory) / "check"
        subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"], input=source, text=True, check=True)
        subprocess.run([str(executable)], check=True)


class RemainingMoveContracts(unittest.TestCase):
    def test_fairy_lock_allocation_refresh_ghost_and_native_trap(self):
        compiled(r'''
typedef unsigned u32; typedef unsigned char u8; typedef unsigned CONDITION;
enum {TYPE_GHOST=7,VAR_MON_ID=2,VAR_MOVE_FAIL_FLAG=65};
struct BattleMon {bool ghost,trap;}; struct BattleEventItem {}; struct ServerFlow {};
struct {u8 fairyLockTurns,commanderForm[24];} sMoveState={};
bool allocated=true; BattleMon mon={}; unsigned vars[128];
bool W2U_MoveState_EnsureTransientEvent(unsigned) {return allocated;}
bool HasTypeWithExtra(BattleMon* m,unsigned) {return m->ghost;}
bool BattleMon_CheckIfMoveCondition(BattleMon* m,unsigned) {return m->trap;}
BattleMon* GetBattleMon(ServerFlow*,unsigned) {return &mon;}
unsigned BattleEventVar_GetValue(unsigned id) {return vars[id];}
void BattleEventVar_RewriteValue(unsigned id,unsigned value) {vars[id]=value;}
''' + bodies("W2U_MoveState_StartFairyLock", "THUMB_BRANCH_LINK_167_0x21B4CD0", "HandlerFieldFairyLockRun",
             "W2U_MoveState_SetCommanderForm", "W2U_MoveState_GetCommanderForm") + r'''
int main() {
 allocated=false; if(W2U_MoveState_StartFairyLock(0)||sMoveState.fairyLockTurns) return 1;
 allocated=true; if(!W2U_MoveState_StartFairyLock(0)||sMoveState.fairyLockTurns!=2) return 2;
 if(W2U_MoveState_StartFairyLock(0)||sMoveState.fairyLockTurns!=2) return 3;
 if(!THUMB_BRANCH_LINK_167_0x21B4CD0(&mon,22)) return 4;
 mon.ghost=true; if(THUMB_BRANCH_LINK_167_0x21B4CD0(&mon,22)) return 5;
 mon.trap=true; if(!THUMB_BRANCH_LINK_167_0x21B4CD0(&mon,22)) return 6;
 mon={false,false}; ServerFlow flow; HandlerFieldFairyLockRun(0,&flow,31,0); if(vars[65]!=1) return 7;
 sMoveState.fairyLockTurns=0; vars[65]=0; HandlerFieldFairyLockRun(0,&flow,31,0); if(vars[65]) return 8;
 for(unsigned slot=0;slot<24;++slot) for(unsigned form=0;form<6;++form) {
   W2U_MoveState_SetCommanderForm(slot,form);
   if(W2U_MoveState_GetCommanderForm(slot)!=(form<=3?form:0)) return 9;
 }
 W2U_MoveState_SetCommanderForm(24,3); W2U_MoveState_SetCommanderForm(~0u,3);
 if(W2U_MoveState_GetCommanderForm(24)||W2U_MoveState_GetCommanderForm(~0u)) return 10;
 return 0;
}
''')

    def test_native_delegate_owner_scoped_targets_and_bounds(self):
        compiled(r'''
typedef unsigned u32; typedef unsigned short u16; typedef unsigned MOVE_ID; typedef unsigned BattleEventType; typedef unsigned BattleEventVar;
enum {MOVE_SMACK_DOWN=479,VAR_ATTACKING_MON=3,VAR_TARGET_COUNT=47,VAR_TARGET_MON_ID=40,EVENT_DAMAGE_PROCESSING_END_HIT_REAL=131};
struct BattleEventItem {}; struct ServerFlow {unsigned simulationCounter;};
typedef void (*Handler)(BattleEventItem*,ServerFlow*,unsigned,unsigned*);
struct BattleEventHandlerTableEntry {unsigned eventType; Handler handler;};
typedef BattleEventHandlerTableEntry* (*W2UNativeMoveGetter)(u32*);
unsigned vars[128],saved[128],calls,pushes,pops,targets[6],fail;
unsigned BattleEventVar_GetValue(unsigned id) {return vars[id];}
void BattleEventVar_Push() {__builtin_memcpy(saved,vars,sizeof(vars));++pushes;__builtin_memset(vars,0,sizeof(vars));}
void BattleEventVar_Pop() {__builtin_memcpy(vars,saved,sizeof(vars));++pops;}
void BattleEventVar_SetConstValue(unsigned id,unsigned value) {vars[id]=value;}
void vanilla(BattleEventItem*,ServerFlow*,unsigned slot,unsigned*) {
 if(vars[3]!=slot||calls>=6) __builtin_trap(); targets[calls++]=vars[40];
}
BattleEventHandlerTableEntry table[]={{131,vanilla},{153,vanilla}};
BattleEventHandlerTableEntry* getter(unsigned* count) {*count=2|0x10000;return table;}
W2UNativeMoveGetter W2U_FindNativeMoveGetter(unsigned id) {if(id!=479) __builtin_trap();return fail?0:getter;}
''' + bodies("RunNativeMoveHandler", "HandlerThousandArrowsGround") + r'''
int main() {
 ServerFlow flow={0}; vars[3]=1; vars[47]=2;vars[40]=12;vars[41]=13;
 HandlerThousandArrowsGround(0,&flow,0,0); if(calls) return 1;
 flow.simulationCounter=1;HandlerThousandArrowsGround(0,&flow,1,0);if(calls) return 2;
 flow.simulationCounter=0;vars[47]=7;HandlerThousandArrowsGround(0,&flow,1,0);if(calls) return 3;
 vars[47]=2; HandlerThousandArrowsGround(0,&flow,1,0);
 if(calls!=2||targets[0]!=12||targets[1]!=13||pushes!=2||pops!=2||vars[41]!=13) return 4;
 fail=1;HandlerThousandArrowsGround(0,&flow,1,0);if(calls!=2||pushes!=4||pops!=4) return 5;
 return 0;
}
''')

    def test_hoopa_current_species_and_form_restriction(self):
        compiled(r'''
typedef unsigned u32; enum {VAR_MON_ID=2,VAR_FAIL_CAUSE=18,MOVE_FAIL_OTHER=1,SPECIES_HOOPA=720};
struct BattleEventItem {}; struct ServerFlow {}; struct BattleMon {unsigned flags,transformedSpecies,species,form;} mon;
unsigned vars[128];bool missing;
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
void BattleEventVar_RewriteValue(unsigned id,unsigned value){vars[id]=value;}
BattleMon* GetBattleMon(ServerFlow*,unsigned){return missing?0:&mon;}
''' + bodies("HandlerHyperspaceFuryCheck") + r'''
int main() {
 ServerFlow flow; mon={0,0,720,1}; HandlerHyperspaceFuryCheck(0,&flow,0,0); if(vars[18]) return 1;
 mon.form=0;HandlerHyperspaceFuryCheck(0,&flow,0,0);if(!vars[18]) return 2;
 vars[18]=0;mon={0x20,720,151,1};HandlerHyperspaceFuryCheck(0,&flow,0,0);if(vars[18]) return 3;
 mon.transformedSpecies=151;HandlerHyperspaceFuryCheck(0,&flow,0,0);if(!vars[18]) return 4;
 vars[18]=0;missing=true;HandlerHyperspaceFuryCheck(0,&flow,0,0);if(!vars[18]) return 5;
 return 0;
}
''')

    def test_aggregate_ground_affinity_preserves_native_and_extra_types(self):
        compiled(r'''
typedef unsigned u32; typedef unsigned short u16; typedef unsigned char u8; typedef int b32;
enum {TYPE_NULL=18,TYPE_FLYING=2,TYPE_GROUND=4,TYPE_FIRE=9,TYPE_GRASS=11,
 MOVE_THOUSAND_ARROWS=614,RESULT_EFFECTIVE=3,RESULT_NOT_EFFECTIVE=0,RESULT_SUPER_EFFECTIVE=4};
struct ServerFlow {}; struct BattleMon {unsigned battleSlot;u16 types;bool floating;};
struct MoveParam {unsigned moveID,moveType;}; unsigned extra=18;bool tar=false;
bool HasTypeWithExtra(BattleMon* mon,unsigned type) {return mon->types>>8==type||(mon->types&255)==type||extra==type;}
unsigned W2U_MoveState_GetExtraType(unsigned) {return extra;}
bool W2U_MoveState_HasTarShot(unsigned) {return tar;}
unsigned THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(ServerFlow*,BattleMon*,BattleMon* target,unsigned move,unsigned type) {
 if(move==4 && type==2) return target->floating?0:3;
 if(move==4 && type==9) return 4;
 if(move==9 && type==11) return 4;
 return 3;
}
unsigned THUMB_BRANCH_GetTypeEffectivenessMultiplier(unsigned a,unsigned b) {if(!a||!b)return 0;return a+b-3;}
u16 BattleMon_GetPokeType(BattleMon* mon) {return mon->types;}
bool ServerControl_CheckFloating(ServerFlow*,BattleMon* mon,unsigned) {return mon->floating;}
''' + bodies("CheckFirstTypeEffectiveness", "THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness") + r'''
int main() {
 ServerFlow flow; BattleMon user={0,0,false},target={12,u16(9*256+2),true};MoveParam move={614,4};
 if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=3) return 1;
 move.moveID=89;if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=0) return 2;
 target.floating=false;if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=4) return 3;
 target={12,0,true};if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=0) return 4;
 move.moveID=614;if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=3) return 5;
 target.floating=false;move={53,9};extra=11;tar=true;
 if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=5) return 6;
 move.moveType=18;if(THUMB_BRANCH_SAFESTACK_ServerEvent_CheckMoveDamageEffectiveness(&flow,&user,&target,&move,0)!=3) return 7;
 return 0;
}
''')

    def test_order_boost_forms_owner_simulation_and_fainting(self):
        compiled(r'''
typedef unsigned u32; typedef signed char s8; typedef unsigned StatStage;
enum {VAR_ATTACKING_MON=3,STATSTAGE_ATTACK=0,STATSTAGE_DEFENSE=1,STATSTAGE_SPEED=4};
struct BattleEventItem {};struct ServerFlow {unsigned simulationCounter;};struct BattleMon {bool faint;}mon;
unsigned slot=0,form=0,calls,stat;bool missing;
unsigned BattleEventVar_GetValue(unsigned) {return slot;}
unsigned W2U_MoveState_GetCommanderForm(unsigned) {return form;}
BattleMon* GetBattleMon(ServerFlow*,unsigned) {return missing?0:&mon;}
bool BattleMon_IsFainted(BattleMon* m) {return m->faint;}
void ApplyStatChange(ServerFlow*,unsigned source,unsigned target,unsigned value,s8 amount,bool animation) {
 if(source!=target||source!=slot||amount!=1||!animation) __builtin_trap();stat=value;++calls;
}
''' + bodies("HandlerOrderUp") + r'''
int main() {
 ServerFlow flow={0};for(form=0;form<=3;++form) {
  unsigned before=calls;HandlerOrderUp(0,&flow,0,0);if(calls!=before+unsigned(form!=0)) return 1;
  if(form && stat!=(form==2?1u:form==3?4u:0u)) return 2;
 }
 form=1;unsigned before=calls;
 HandlerOrderUp(0,&flow,1,0);flow.simulationCounter=1;HandlerOrderUp(0,&flow,0,0);
 flow.simulationCounter=0;mon.faint=true;HandlerOrderUp(0,&flow,0,0);
 mon.faint=false;missing=true;HandlerOrderUp(0,&flow,0,0);if(calls!=before) return 3;
 return 0;
}
''')

    def test_commander_form_clears_on_native_switch_and_faint_path(self):
        compiled(r'''
typedef unsigned u32;typedef unsigned char u8;
enum {VAR_MON_ID=2,BATTLE_MAX_SLOTS=31,MOVE_NONE=0};
struct {
 u32 statsRaisedThisTurnFlags,statsLoweredThisTurnFlags,tarShotFlags,noRetreatFlags,glaiveRushFlags;
 u32 shellSideArmCategoryValidFlags,shellSideArmRecordedValidFlags,calledDartsFlags;
 u8 commanderForm[24],dragonCheerBoost[31];
 u32 lastSuccessfulSelectedMove[31],persistentFlags[3],persistentSources[3][31];
}sMoveState={};
u32 slot;
u32 BattleEventVar_GetValue(u32){return slot;}
u32 SlotMask(u32 value){return value<32?1u<<value:0;}
bool IsValidSlot(u32 value){return value<31;}
void ClearStompingOutcomeState(u32){}
void W2U_MoveState_ClearBeakBlast(u32){}
void W2U_MoveState_ClearShellTrap(u32){}
void W2U_MoveState_ClearLaserFocus(u32){}
void W2U_MoveState_ClearThroatChop(u32){}
bool HasTransientMoveState(){return true;}
void RemoveTransientMoveStateEvent(){}
''' + bodies("W2U_MoveState_SetCommanderForm", "W2U_MoveState_GetCommanderForm",
             "ClearSwitchedOrFaintedTransientState") + r'''
int main(){
 for(slot=0;slot<24;++slot)W2U_MoveState_SetCommanderForm(slot,3);
 for(slot=0;slot<24;++slot){
  ClearSwitchedOrFaintedTransientState();
  for(unsigned i=0;i<24;++i)if(W2U_MoveState_GetCommanderForm(i)!=(i<=slot?0:3))return 1;
 }
 slot=24;ClearSwitchedOrFaintedTransientState();slot=31;ClearSwitchedOrFaintedTransientState();
 return 0;
}
''')

    def test_registrations_are_unique_and_white2_only(self):
        registry = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
        wanted = {"MOVE_THOUSAND_ARROWS", "MOVE_THOUSAND_WAVES", "MOVE_HYPERSPACE_HOLE", "MOVE_HYPERSPACE_FURY", "MOVE_FAIRY_LOCK", "MOVE_GEAR_UP", "MOVE_PSYCHIC_FANGS", "MOVE_ORDER_UP"}
        found = []
        for group in registry["modules"]:
            for kind, name, _ in group["entries"]:
                if name in wanted:
                    found.append(name)
                    self.assertTrue(group.get("white2_only") or group["entry_overrides"][f"{kind}:{name}"]["white2_only"])
        self.assertEqual(set(found), wanted)
        self.assertEqual(len(found), len(wanted))
        self.assertNotIn("{ MOVE_FAIRY_LOCK, MOVE_SPIDER_WEB }", TEXT)

    def test_screen_break_uses_one_callback_per_event(self):
        for name in ("BrickBreakAuroraVeilHandlers", "RagingBullHandlers"):
            table = re.search(name + r'\[\] = \{(.*?)\n\};', TEXT, re.S).group(1)
            events = re.findall(r'\{\s*(EVENT_\w+),', table)
            self.assertEqual(len(events), len(set(events)), name)
        compiled(r'''
typedef unsigned u32; enum {VAR_ATTACKING_MON=3,VAR_DEFENDING_MON=4,BATTLE_MAX_SLOTS=24};
struct BattleEventItem {};struct ServerFlow {};
unsigned vars[8],nativeCalls,veilCalls,side;bool nativeFirst;
unsigned BattleEventVar_GetValue(unsigned id){return vars[id];}
unsigned GetSideFromMonID(unsigned slot){return slot/12;}
void HandlerBrickBreakCheck(BattleEventItem*,ServerFlow*,unsigned,unsigned*){++nativeCalls;}
void W2U_MoveState_RemoveAuroraVeilSide(ServerFlow*,unsigned,unsigned value,bool message){
 if(!message||!nativeCalls) __builtin_trap();++veilCalls;side=value;
}
''' + bodies("HandlerBrickBreakAuroraVeil") + r'''
int main(){
 ServerFlow flow;vars[3]=0;vars[4]=12;
 HandlerBrickBreakAuroraVeil(0,&flow,0,0);if(nativeCalls!=1||veilCalls!=1||side!=1)return 1;
 HandlerBrickBreakAuroraVeil(0,&flow,1,0);if(nativeCalls!=2||veilCalls!=1)return 2;
 vars[4]=24;HandlerBrickBreakAuroraVeil(0,&flow,0,0);if(nativeCalls!=3||veilCalls!=1)return 3;
 return 0;
}
''')

    def test_us_w2_native_pins(self):
        import ndspy.rom
        path = ROOT.parent / "Port-Pokeweb/cleanwhite2.nds"
        if not path.exists(): self.skipTest("Optional clean US W2 ROM unavailable")
        overlay = ndspy.rom.NintendoDSRom.fromFile(str(path)).loadArm9Overlays([167])[167]
        for address, signature in ((0x21B4B1C, "f8b5071c0e1c151c1c1c"), (0x21B4CD0, "06f018ff")):
            # The callsite's exact BL destination is independently decoded below.
            if address == 0x21B4CD0:
                from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB
                data=overlay.data[address-overlay.ramAddress:address-overlay.ramAddress+4]
                instruction=list(Cs(CS_ARCH_ARM,CS_MODE_THUMB).disasm(data,address))[0]
                self.assertEqual((instruction.mnemonic,instruction.op_str),("bl","#0x21bbb04"))
            else:
                at=address-overlay.ramAddress
                self.assertEqual(bytes(overlay.data[at:at+len(signature)//2]).hex(),signature)


if __name__ == "__main__": unittest.main()
