"""Native animation lifecycle sweep. This tests scripts, not move effects or visuals."""
import argparse
import importlib.util
import json
import hashlib
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import time
import uuid

spec = importlib.util.spec_from_file_location("battle_interactions", Path(__file__).with_name("test-battle-interactions.py"))
common = importlib.util.module_from_spec(spec)
spec.loader.exec_module(common)
ROOT = common.ROOT


class Observer:
    def __init__(self, emu, core_offsets=None, trace_allocations=False):
        self.emu = emu
        self.core_offsets = core_offsets or {}
        self.core_base = None
        self.hooks = []
        self.errors = []
        self.pointers = {}
        self.client_pointer = None
        self.case = None
        self.commands = 0
        self.command_frames = []
        self.loads = []
        self.damage_calls = 0
        self.ui_phase = None
        self.ends, self.waits = [], []
        self.returns, self.read_pending, self.scripts = {}, {}, []
        self.sprite_allocations = {}
        self.sprite_pending = {}
        self.sprite_peak_bytes = 0
        self.sprite_loads = self.sprite_frees = 0
        self.faults = []
        self.battle_exits = []
        self.exit_hook = None
        self.failed_game_allocations = []
        self.trace_allocations = trace_allocations
        self.pmc_heap_area = None
        self.pmc_allocator_inputs = []
        self.pmc_allocations = []
        self.pmc_pending = {}
        self.pmc_minimum_free = None
        self.script_starts = []
        self.primary_commands = []
        self.emitter_results = []
        self.emitter_pending = {}
        self.script_writes = []
        self.script_write_hooks = {}
        self.particle_allocations = []
        self.particle_pending = {}
        self.particle_creates = []
        self.mcss_requests = []

    def mcss_request(self, cpu, address):
        r = self.emu.memory.register_arm9
        # Native field graphics also pass parameters through the DS main-RAM
        # mirror. This is a read-only probe, not an RPM allocation range.
        common.check(0x02000000 <= r.r2 < 0x03000000 - 36 and not r.r2 & 3,
                     f"MCSS parameters outside native RAM/mirrors: {r.r2:#x} at {address:#x}")
        record = {"frame": self.emu.frame_count, "slot": r.r1,
            "parameters": [self.emu.memory.read_long(r.r2 + n * 4) for n in range(9)],
            "allocationsBefore": self.sprite_loads}
        self.mcss_requests.append(record)
        key = ("mcss", address + 4)
        self.sprite_pending.setdefault(key, []).append(record)
        if key not in self.returns:
            def returned(cpu, at):
                pending = self.sprite_pending.get(key)
                if pending:
                    row = pending.pop()
                    row["streamBufferAllocations"] = self.sprite_loads - row["allocationsBefore"]
            self.returns[key] = self.emu.memory.register_exec(address + 4, returned)

    def sprite_alloc(self, cpu, address):
        r = self.emu.memory.register_arm9
        streamed = 0x02000000 <= r.r3 <= 0x023ffffa and bytes(self.emu.memory.unsigned[r.r3:r.r3+6]) == b"w2anim"
        if not streamed:
            if not self.trace_allocations:return
            ret=r.lr & ~1
            key=("allocation",ret)
            self.sprite_pending.setdefault(key,[]).append({"heap":r.r0,"bytes":r.r1,"sourceAddress":hex(r.r3)})
            if key not in self.returns:
                def returned(cpu,address):
                    pending=self.sprite_pending.get(key)
                    if pending:
                        record=pending.pop()
                        if not self.emu.memory.register_arm9.r0:self.failed_game_allocations.append(record)
                self.returns[key]=self.emu.memory.register_exec(ret,returned)
            return
        ret = r.lr & ~1
        self.sprite_pending.setdefault(ret, []).append({"heap": r.r0, "bytes": r.r1})
        key = ("sprite", ret)
        if key not in self.returns:
            def returned(cpu, address):
                pending = self.sprite_pending.get(ret)
                if pending:
                    record = pending.pop()
                    pointer = self.emu.memory.register_arm9.r0
                    if pointer:
                        self.sprite_allocations[pointer] = record
                        self.sprite_loads += 1
                        self.sprite_peak_bytes = max(self.sprite_peak_bytes, sum(item["bytes"] for item in self.sprite_allocations.values()))
            self.returns[key] = self.emu.memory.register_exec(ret, returned)

    def sprite_free(self, cpu, address):
        pointer = self.emu.memory.register_arm9.r0
        hook = self.script_write_hooks.pop(pointer, None)
        if hook:
            hook.remove() # Freed script storage may legitimately be reused by the native heap.
        if self.sprite_allocations.pop(pointer, None):
            self.sprite_frees += 1

    def install(self, probes):
        def undefined(cpu,address):
            r=self.emu.memory.register_arm9
            at=r.lr
            self.faults.append({"frame":self.emu.frame_count,"returnPc":hex(at),
                               "registers":{f"r{i}":hex(getattr(r,f"r{i}")) for i in range(16)},
                               "nearReturnBytes":bytes(self.emu.memory.unsigned[max(0,at-16):at+16]).hex()})
        self.hooks.append(self.emu.memory.register_exec(0xffff0004,undefined))
        for probe in probes:
            def callback(cpu, address, name=probe["name"], probe=probe):
                try:
                    if probe.get("signature") and bytes(self.emu.memory.unsigned[address:address+len(probe["signature"])//2]).hex() != probe["signature"]:
                        stub = bytes(self.emu.memory.unsigned[address:address+12])
                        target = self.emu.memory.read_long(address+12)
                        # PMC replaces this entire function. The fixture
                        # validates its retail prologue before installation;
                        # at runtime require the exact PMC thunk and RAM code.
                        whole_branch = stub == bytes.fromhex("7847c04600c09fe51cff2fe1") and (target & 1) and 0x02000001 <= target < 0x02400000
                        high, low = int.from_bytes(stub[2:4],"little"), int.from_bytes(stub[4:6],"little")
                        displacement = ((high & 0x7ff) << 12) | ((low & 0x7ff) << 1)
                        if displacement & 0x400000: displacement -= 0x800000
                        relay = address + 6 + displacement
                        thumb_branch = (stub[:2] == b"\x00\xb5" and stub[6:8] == b"\x00\xbd" and
                                        high & 0xf800 == 0xf000 and low & 0xf800 == 0xf800 and
                                        0x02000000 <= relay < 0x02400000)
                        if name not in ("ability","move_registration") or not (whole_branch or thumb_branch):
                            raise AssertionError(f"Native probe signature mismatch: {name}, bytes={stub.hex()}, target={target:#x}")
                    getattr(self, name)(cpu, address)
                except Exception as error:
                    self.errors.append(str(error))
            self.hooks.append(self.emu.memory.register_exec(probe["address"], callback))

    def command(self, cpu, address):
        if self.emu.memory.read_long(self.emu.memory.register_arm9.r1) == 0:
            self.commands += 1
            self.command_frames.append(self.emu.frame_count)
            core = self.emu.memory.register_arm9.r0
            self.client_pointer = self.emu.memory.read_long(core + 0xbc)

    def move_registration(self, cpu, address):
        high, low = self.emu.memory.read_short(address+2), self.emu.memory.read_short(address+4)
        common.check(high & 0xf800 == 0xf000 and low & 0xf800 == 0xf800,"Unexpected resident move hook")
        delta = ((high & 0x7ff) << 12) | ((low & 0x7ff) << 1)
        if delta & 0x400000: delta -= 0x800000
        self.core_base = address + 6 + delta - self.core_offsets["THUMB_BRANCH_MoveEvent_AddItem"]
        if self.exit_hook is None and "W2U_BattleState_OnBattleExit" in self.core_offsets:
            def exiting(cpu,address):
                ret=self.emu.memory.register_arm9.lr & ~1
                def returned(cpu,address):
                    self.battle_exits.append({"frame":self.emu.frame_count,"telemetry":self.module_telemetry()})
                key=("exit",ret)
                if key not in self.returns:self.returns[key]=self.emu.memory.register_exec(ret,returned)
            self.exit_hook=self.emu.memory.register_exec(self.core_base+self.core_offsets["W2U_BattleState_OnBattleExit"],exiting)
            self.hooks.append(self.exit_hook)

    def module_telemetry(self):
        if self.core_base is None: self.move_registration(None,0x021c5b44)
        getter = self.core_base + self.core_offsets["W2U_BattleModules_GetTelemetry"]
        common.check(bytes(self.emu.memory.unsigned[getter:getter+4]) == bytes.fromhex("00487047"),"Unexpected telemetry accessor")
        pointer = self.emu.memory.read_long(getter+4)
        common.check(0x02000000 <= pointer < 0x02400000-48,"Telemetry outside main RAM")
        names=("coreFixedBytes","loadedModuleCount","currentChildBytes","peakChildBytes","loadCount","unloadCount","failureCount","failedModuleMask","lastFailureModuleId","heapRefusalCount","lastRefusedBytes","lastLargestFreeBytes")
        return {name:self.emu.memory.read_long(pointer+i*4) for i,name in enumerate(names)}

    def pmc_heap_state(self):
        # Independent read-only verification of the bundled ExtLib allocator
        # header. The RPM image may follow its allocation's short prologue;
        # accept only a fully bounded 200-KiB heap object, never guessed data.
        memory=self.emu.memory
        candidates=([self.pmc_heap_area] if self.pmc_heap_area else [])
        for area in candidates:
            if not 0x02000000<=area<=0x02400000-200*1024 or area&7:continue
            base,total,block=[memory.read_long(area+i) for i in (4,8,12)]
            # Verified bundled constructor: the object occupies 32 bytes,
            # but its size field adds those bytes rather than subtracting
            # them. Never count the resulting 64 bytes past the reserved
            # arena as usable headroom, even though ExtLib lists them free.
            if base!=area+32 or total!=200*1024+32:continue
            limit=area+200*1024
            free,nominal,largest,seen=0,0,0,set()
            while block:
                if block in seen or len(seen)>=512 or block&3 or not base<=block<=limit-16:break
                seen.add(block)
                size,next_block=memory.read_long(block),memory.read_long(block+4)
                if not size or size&7 or size>base+total-block-16:break
                bounded=min(size,limit-block-16)
                nominal+=size;free+=bounded;largest=max(largest,bounded);block=next_block
            if not block:return {"reservedHeapBytes":200*1024,"nativeDeclaredBytes":total,"rootObjectBytes":32,"freePayloadBytes":free,"largestFreePayloadBytes":largest,"freeBlockCount":len(seen),"excludedOutOfArenaBytes":nominal-free}
        return None

    def pmc_alloc(self,cpu,address):
        area=self.emu.memory.register_arm9.r0
        if 0x02000000<=area<=0x023ffff0 and not area&3:
            fields=[self.emu.memory.read_long(area+i*4) for i in range(4)]
            if len(self.pmc_allocator_inputs)<8:self.pmc_allocator_inputs.append({"area":hex(area),"fields":[hex(x) for x in fields]})
            if fields[1]==area+32 and fields[2]==200*1024+32:
                self.pmc_heap_area=area
                r=self.emu.memory.register_arm9
                ret=r.lr & ~1
                self.pmc_pending.setdefault(ret,[]).append({"bytes":r.r1,"caller":hex(r.lr)})
                key=("pmc",ret)
                if key not in self.returns:
                    def returned(cpu,address):
                        pending=self.pmc_pending.get(ret)
                        if not pending:return
                        record=pending.pop()
                        record["pointer"]=hex(self.emu.memory.register_arm9.r0)
                        state=self.pmc_heap_state()
                        if state:
                            record["freePayloadBytes"]=state["freePayloadBytes"]
                            self.pmc_minimum_free=state["freePayloadBytes"] if self.pmc_minimum_free is None else min(self.pmc_minimum_free,state["freePayloadBytes"])
                        self.pmc_allocations.append(record)
                    self.returns[key]=self.emu.memory.register_exec(ret,returned)

    def script_pc(self,cpu,address):
        if self.case:self.script_starts.append({"frame":self.emu.frame_count,"cursor":self.emu.memory.register_arm9.r1})

    def primary_script_pc(self,cpu,address):
        if self.case:self.script_starts.append({"frame":self.emu.frame_count,"cursor":self.emu.memory.register_arm9.r1,"primary":True})

    def vm_command(self,cpu,address):
        if not self.case or len(self.primary_commands)>=1024:return
        r=self.emu.memory.register_arm9
        cursor=self.emu.memory.read_long(r.r5+0x20)-2
        if any(s["pointer"]<=cursor<s["pointer"]+self.case["scriptBytes"] for s in self.scripts):
            self.primary_commands.append({"frame":self.emu.frame_count,"cursor":cursor,"opcode":r.r0,"vm":r.r5})

    def particle_emitter(self,cpu,address):
        if not self.case:return
        r=self.emu.memory.register_arm9
        ret=r.lr & ~1
        self.emitter_pending.setdefault(ret,[]).append({"frame":self.emu.frame_count,"resource":r.r1,"context":hex(r.r0)})
        key=("emitter",ret)
        if key not in self.returns:
            def returned(cpu,address):
                pending=self.emitter_pending.get(ret)
                if pending:
                    record=pending.pop();record["pointer"]=hex(self.emu.memory.register_arm9.r0)
                    self.emitter_results.append(record)
            self.returns[key]=self.emu.memory.register_exec(ret,returned)

    def ability(self, cpu, address):
        pointer = self.emu.memory.register_arm9.r0
        slot = self.emu.memory.read_byte(pointer + 25)
        self.pointers[slot] = pointer

    def particle_parse(self,cpu,address):
        if not self.case:return
        callback=self.emu.memory.read_long(self.emu.memory.register_arm9.r0) & ~1
        key=("particle_allocator",callback)
        if key in self.returns:return
        def allocating(cpu,address):
            r=self.emu.memory.register_arm9
            ret=r.lr & ~1
            self.particle_pending.setdefault(ret,[]).append({"bytes":r.r0,"callback":hex(callback),"caller":hex(r.lr)})
            return_key=("particle_return",ret)
            if return_key not in self.returns:
                def returned(cpu,address):
                    pending=self.particle_pending.get(ret)
                    if pending:
                        record=pending.pop();record["pointer"]=hex(self.emu.memory.register_arm9.r0)
                        self.particle_allocations.append(record)
                self.returns[return_key]=self.emu.memory.register_exec(ret,returned)
        self.returns[key]=self.emu.memory.register_exec(callback,allocating)

    def particle_create(self,cpu,address):
        r=self.emu.memory.register_arm9
        self.particle_creates.append({"frame":self.emu.frame_count,"buffer":hex(r.r0),"capacity":r.r1,"caller":hex(r.lr)})

    def random(self, cpu, address):
        pass  # Never change animation or gameplay RNG for this lifecycle test.

    def damage(self, cpu, address):
        if self.case:
            self.damage_calls += 1

    def animation_load(self, cpu, address):
        if self.case:
            r = self.emu.memory.register_arm9
            self.loads.append({"frame": self.emu.frame_count, "r0": r.r0, "r1": r.r1, "r2": r.r2, "r3": r.r3, "lr": r.lr})

    def ui(self, cpu, address):
        core = self.emu.memory.register_arm9.r0
        self.ui_phase = self.emu.memory.read_long(core + 20) & ~1

    def animation_end(self, cpu, address):
        if self.case:
            context = self.emu.memory.register_arm9.r1
            self.ends.append({"frame": self.emu.frame_count, "animationId": self.emu.memory.read_short(context + 0x258),
                              "vm":self.emu.memory.register_arm9.r0,
                              "vmWords":[self.emu.memory.read_long(self.emu.memory.register_arm9.r0+i*4) for i in range(12)]})

    def animation_wait(self, cpu, address):
        if self.case:
            r = self.emu.memory.register_arm9
            self.waits.append({"frame": self.emu.frame_count, "vm": r.r0, "context": r.r1})

    def archive_read(self, cpu, address):
        r = self.emu.memory.register_arm9
        if not self.case or r.r0 != 65 or r.r1 != self.case["animationTarget"]["index"]:
            return
        ret = r.lr & ~1
        self.read_pending.setdefault(ret, []).append(dict(self.case))
        if ret not in self.returns:
            def returned(cpu, address):
                try:
                    if not self.read_pending.get(address):
                        return
                    case = self.read_pending[address].pop()
                    pointer = self.emu.memory.register_arm9.r0
                    common.check(0x02000000 <= pointer < 0x02400000 - case["scriptBytes"], "Invalid loaded script pointer")
                    actual = hashlib.sha256(bytes(self.emu.memory.unsigned[pointer:pointer + case["scriptBytes"]])).hexdigest()
                    common.check(actual == case["scriptSha256"], "Runtime loaded the wrong animation script")
                    self.scripts.append({"frame": self.emu.frame_count, "pointer": pointer, "sha256": actual})
                    if case["sourceMoveId"] in (778,805,833,844):
                        def writing(cpu,address,width,value):
                            if len(self.script_writes)>=128:return
                            r=self.emu.memory.register_arm9
                            self.script_writes.append({"frame":self.emu.frame_count,"address":hex(address),"width":width,"value":hex(value),"pc":hex(r.r15),"lr":hex(r.lr)})
                        self.script_write_hooks[pointer] = self.emu.memory.register_write(pointer,writing,size=case["scriptBytes"])
                except Exception as error:
                    self.errors.append(str(error))
            self.returns[ret] = self.emu.memory.register_exec(ret, returned)

    def cycle(self):
        self.emu.cycle()
        common.check(not self.errors, "; ".join(self.errors))
        for name in ("register_arm9", "register_arm7"):
            r = getattr(self.emu.memory, name)
            if r.cpsr & 0x1f in (0x17,0x1b):
                self.faults.append({"cpu":name,"frame":self.emu.frame_count,
                                   "registers":{f"r{i}":hex(getattr(r,f"r{i}")) for i in range(16)},
                                   "cpsr":hex(r.cpsr)})
            common.check(r.cpsr & 0x1f not in (0x17, 0x1b), f"{name} entered fault mode at {r.pc:#x}")

    def close(self):
        for hook in [*self.hooks,*self.returns.values(),*self.script_write_hooks.values()]:
            hook.remove()


def prepare(args, directory):
    fixtures = Path(args.fixtures).resolve() if args.fixtures else directory / "fixtures"
    if not args.fixtures:
        command=[*common.fixture_builder_command("build-animation-completion-fixtures.ts"), "--rom", str(Path(args.rom).resolve()), "--save", str(Path(args.save).resolve()), "--out", str(fixtures),"--sprites",args.sprites,"--modules",args.modules,"--baseline-control","yes" if args.baseline_control else "no","--native-mechanics","yes" if args.native_mechanics else "no"]
        if args.stress_loader:command += ["--stress-loader",str(Path(args.stress_loader).resolve())]
        if args.isolate_particles:command += ["--isolate-particles","yes"]
        if args.authoring_smoke:command += ["--authoring-smoke","yes"]
        subprocess.run(command,cwd=ROOT,check=True)
    manifest = json.loads((fixtures / "suite.json").read_text())
    cases = [c for c in manifest["cases"] if not args.moves or c["sourceMoveId"] in args.moves]
    common.check(cases and (not args.moves or {c["sourceMoveId"] for c in cases} == set(args.moves)), "Unknown/empty requested move set")
    return fixtures, manifest, cases


def run(args):
    started = time.monotonic()
    MelonDS, library = common.configure_melon(args)
    directory = Path(args.out).resolve() if args.out else ROOT / "work/animation-completion" / (time.strftime("%Y%m%d-%H%M%S") + "-" + uuid.uuid4().hex[:6])
    common.create_output_directory(directory)
    fixtures, manifest, cases = prepare(args, directory)
    common.check(manifest["format"] == "pokeweb-animation-completion-1" and manifest["animationsEnabled"], "Wrong animation fixture format/options")
    for key in ("rom", "save"):
        common.check(common.digest(fixtures / manifest[key]["file"]) == manifest[key]["sha256"], f"Fixture {key} hash mismatch")
    save = (fixtures / "battle.sav").read_bytes()
    for half in (0, 0x26000):
        common.check(not save[half + 0x19400] & 0x80, "Animation fixture has Battle Scene Off")
    report = {"format": "pokeweb-animation-completion-results-1", "inputRomSha256": manifest["inputRomSha256"], "animationsEnabled": True, "mode": manifest["mode"], "cases": [], "passed": False}
    snapshot = observer = emu = None
    progress_fd = os.dup(1)
    try:
        # The supervising process owns this temporary tree, so even a blocked
        # native C call killed by the watchdog cannot leak its ROM/save copy.
        with common.native_log(directory / "native.log"):
            scratch = args.scratch
            common.check(scratch is not None, "Animation workers require parent-owned scratch storage")
            rom = Path(scratch) / "battle.nds"
            common.clone(fixtures / "battle.nds", rom)
            shutil.copyfile(fixtures / "battle.sav", rom.with_suffix(".sav"))
            emu = MelonDS(library)
            observer = Observer(emu,manifest.get("coreOffsets"),args.trace_allocation_failures)
            observer.install(manifest["probes"])
            emu.open(rom)
            for _ in range(args.boot_frames):
                observer.cycle()
                if observer.commands and {0, 12}.issubset(observer.pointers):
                    break
            common.check(observer.commands and {0, 12}.issubset(observer.pointers), "No initial command menu/battlers")
            emu.input.keypad_update(0)
            emu.input.touch_release()
            snapshot = emu.save_snapshot()
            frame = emu.frame_count
            report.update(checkpointFrame=frame, snapshotBytes=len(snapshot))
            sprite_checkpoint = dict(observer.sprite_allocations)
            if manifest.get("authoringSmoke"):
                report["authoringIntroStreamBuffers"] = {"allocations": observer.sprite_loads, "frees": observer.sprite_frees, "live": len(sprite_checkpoint), "mcssRequests": observer.mcss_requests}
                pokemon = [row for row in observer.mcss_requests if row["parameters"][:2] == [4, 3031]]
                common.check(len(pokemon) == 1 and pokemon[0].get("streamBufferAllocations") == 3 and len(sprite_checkpoint) == 6,
                             "Newly authored native-Pokemon stream did not allocate its three buffers")
                report["authoredPokemonLifecycleValidated"] = True
                trainer = [row for row in observer.mcss_requests if row["parameters"][0] == 71]
                if trainer:
                    common.check(any(row.get("streamBufferAllocations") == 3 for row in trainer) and observer.sprite_frees >= 3,
                                 "Authored trainer stream did not load/release during native intro")
                report["authoredTrainerNativeExercised"] = bool(trainer)
                if not trainer:
                    report["trainerNativeLimit"] = "The native quick-battle fixture bypasses trainer MCSS intro; trainer authoring is host round-trip tested, not native-certified."
            for case in cases:
                report["activeCase"] = {"sourceMoveId": case["sourceMoveId"], "name": case["name"]}
                (directory / "result.json").write_text(json.dumps(report,indent=2)+"\n")
                emu.restore_snapshot(snapshot)
                observer.sprite_allocations = dict(sprite_checkpoint)
                observer.sprite_pending = {}
                emu.input.keypad_update(0)
                emu.input.touch_release()
                observer.case, observer.commands, observer.loads, observer.damage_calls, observer.errors = case, 0, [], 0, []
                observer.ui_phase = None
                observer.command_frames = []
                observer.ends, observer.waits = [], []
                observer.read_pending, observer.scripts = {}, []
                observer.faults = []
                observer.failed_game_allocations = []
                observer.script_starts = []
                observer.primary_commands = []
                observer.emitter_results = []
                observer.script_writes = []
                observer.particle_allocations = []
                for hook in observer.script_write_hooks.values():hook.remove()
                observer.script_write_hooks = {}
                mon = observer.pointers[0]
                # Bounded pre-input move-list fixture only. Selection, execution,
                # VM instructions, waits and completion flags run unmodified.
                for pointer in {mon, observer.client_pointer}:
                    identity = common.read_mon(emu,pointer)
                    common.check(identity["species"] == manifest.get("playerSpecies",151) and identity["slot"] == 0, "Wrong fixture BattleMon identity")
                    for offset in (0x104, 0x10a):
                        common.check(emu.memory.read_short(pointer+offset) == manifest.get("checkpointMoveId",845), "Unexpected checkpoint move list")
                        emu.memory.write_short(pointer + offset, case["moveId"])
                        emu.memory.write_byte(pointer + offset + 2, 35)
                result = {**case, "passed": False,"beforeModuleTelemetry":observer.module_telemetry() if observer.core_offsets else None}
                result["pmcHeapAtMenu"]=observer.pmc_heap_state()
                result["pmcAllocationLedger"]=observer.pmc_allocations
                result["pmcMinimumFreePayloadBytes"]=observer.pmc_minimum_free
                if manifest.get("syntheticAllGroupRegistration"):
                    telemetry=result["beforeModuleTelemetry"]
                    common.check(telemetry["loadedModuleCount"]==30 and telemetry["loadCount"]==30 and not telemetry["failureCount"],"Synthetic registration did not load all 30 real module APIs")
                    common.check(result["pmcHeapAtMenu"] is not None,f"Cannot locate bounded native PMC heap: {observer.pmc_allocator_inputs}, core={observer.core_base:#x}")
                    common.check(result["pmcHeapAtMenu"]["largestFreePayloadBytes"]>=12*1024,f"All-group native heap has less than 12 KiB contiguous headroom: {result['pmcHeapAtMenu']}")
                case_start = time.monotonic()
                try:
                    for step in range(args.max_frames):
                        emu.input.keypad_update(1 if 24 <= step < 27 else 0)
                        if step >= 60 and step % 12 < 3 and not observer.damage_calls:
                            emu.input.touch_set_pos(64, 50)
                        else:
                            emu.input.touch_release()
                        observer.cycle()
                        completed = [e["frame"] for e in observer.ends if e["animationId"] == case["moveId"] + 115]
                        if (observer.ui_phase in (0x021cf02c,0x021cef18) and observer.damage_calls and observer.scripts
                            and completed and any(f > completed[-1] for f in observer.command_frames)
                            and emu.memory.read_short(mon + 0x14c) == case["moveId"]
                            and emu.memory.read_byte(mon + 0x106) < 35):
                            result["passed"] = True
                            break
                        if time.monotonic() - case_start > args.case_timeout:
                            raise AssertionError("Animation case exceeded wall-clock deadline")
                    common.check(result["passed"], "Animation/battle failed to return to the next command menu")
                except Exception as error:
                    result["error"] = str(error)
                    emu.screenshot().save(directory / f"{case['sourceMoveId']}-failure.png")
                result.update(frames=emu.frame_count-frame, wallSeconds=round(time.monotonic()-case_start,3), verifiedScripts=observer.scripts, animationLoads=observer.loads, animationEnds=observer.ends, animationWaits=observer.waits, uiPhase=hex(observer.ui_phase or 0), damageCalls=observer.damage_calls, commandCalls=observer.commands, commandFrames=observer.command_frames, pp=emu.memory.read_byte(mon+0x106), arm9Pc=hex(emu.memory.register_arm9.pc), arm7Pc=hex(emu.memory.register_arm7.pc), w2animGameHeap={"currentPayloadBytes":sum(item["bytes"] for item in observer.sprite_allocations.values()), "peakPayloadBytes":observer.sprite_peak_bytes, "allocationCount":observer.sprite_loads, "freeCount":observer.sprite_frees, "allocatorOverheadIncluded":False})
                report["cases"].append(result)
                result["undefinedFaults"] = observer.faults
                result["failedGameAllocations"] = observer.failed_game_allocations
                result["allGameAllocationFailuresTraced"] = observer.trace_allocations
                result["scriptStarts"]=observer.script_starts
                result["primaryScriptCommands"]=observer.primary_commands
                result["particleEmitters"]=observer.emitter_results
                result["scriptWrites"]=observer.script_writes
                result["particleAllocations"]=observer.particle_allocations
                result["particleCreates"]=observer.particle_creates
                if observer.core_offsets:
                    result["afterModuleTelemetry"] = observer.module_telemetry()
                    if case["sourceMoveId"] == 797 and manifest.get("moduleMode") in ("missing","corrupt","wrong-abi","truncated","corrupt-tables","heap-refusal"):
                        telemetry = result["afterModuleTelemetry"]
                        common.check(not telemetry["loadedModuleCount"] and not telemetry["currentChildBytes"] and
                                     telemetry["failureCount"] == 1, "Unavailable terrain module was not cached exactly once")
                        result["unavailableModuleBehaviorValidated"] = True
                        if manifest.get("moduleMode") == "heap-refusal":
                            common.check(telemetry["heapRefusalCount"] == 1 and telemetry["lastRefusedBytes"] == 128*1024 and
                                         telemetry["lastLargestFreeBytes"] < 128*1024,
                                         "Oversized child was not refused before the non-returning native allocator")
                if args.verify_teardown and result["passed"]:
                    # A bounded pre-input HP fixture, not a forced callback:
                    # native Tackle, faint processing and field exit all run.
                    target=observer.pointers[12]
                    identity=common.read_mon(emu,target)
                    common.check(identity["slot"]==12 and identity["species"]==manifest["defenderSpecies"],"Wrong teardown target")
                    emu.memory.write_short(target+16,1)
                    observer.damage_calls=0
                    exits_before=len(observer.battle_exits)
                    for step in range(args.max_frames):
                        emu.input.keypad_update(1 if step%12<3 else 0)
                        if step>=60 and step%12<3 and not observer.damage_calls:emu.input.touch_set_pos(192,50)
                        else:emu.input.touch_release()
                        observer.cycle()
                        if len(observer.battle_exits)>exits_before and not observer.sprite_allocations:break
                    result["battleExitTelemetry"]=observer.battle_exits[exits_before:]
                    result["teardownSpritePayloadBytes"]=sum(x["bytes"] for x in observer.sprite_allocations.values())
                    result["teardownSpriteFreeCount"]=observer.sprite_frees
                    common.check(result["battleExitTelemetry"],"Native battle exit was not observed")
                    common.check(all(not x["telemetry"]["loadedModuleCount"] and not x["telemetry"]["currentChildBytes"] for x in result["battleExitTelemetry"]),"Child modules survived native battle exit")
                    common.check(not observer.sprite_allocations,"Stream buffers survived native sprite destruction")
                report["activeCase"] = None
                (directory / "result.json").write_text(json.dumps(report, indent=2)+"\n")
                os.write(progress_fd, f"{'PASS' if result['passed'] else 'FAIL'} {case['sourceMoveId']} {case['name']}: {result['frames']} frames\n".encode())
            report["passed"] = all(c["passed"] for c in report["cases"])
    finally:
        os.close(progress_fd)
        snapshot = None
        report["snapshotReleased"] = True
        if observer:
            observer.close()
        if emu:
            emu.destroy()
        if not args.fixtures and not args.keep_fixtures:
            report["removedFixtureRoms"] = common.cleanup_fixture_rom(fixtures)
        report["wallSeconds"] = round(time.monotonic()-started,3)
        (directory / "result.json").write_text(json.dumps(report,indent=2)+"\n")
    print(f"Report: {directory.relative_to(ROOT) if directory.is_relative_to(ROOT) else directory.name}/result.json", flush=True)
    return 0 if report["passed"] else 1


def supervise(args):
    """Workers reuse snapshots; an external watchdog catches native deadlocks."""
    common.configure_melon(args)
    directory = Path(args.out).resolve() if args.out else ROOT / "work/animation-completion" / (time.strftime("%Y%m%d-%H%M%S") + "-" + uuid.uuid4().hex[:6])
    common.create_output_directory(directory)
    fixtures = Path(args.fixtures).resolve() if args.fixtures else directory / "fixtures"
    jobs, results = [], []
    started = time.monotonic()
    report = {"format":"pokeweb-animation-completion-results-1","passed":False,"cases":[]}
    try:
        fixtures, manifest, cases = prepare(args, directory)
        report.update(inputRomSha256=manifest["inputRomSha256"], fixtureRomSha256=manifest["rom"]["sha256"], animationsEnabled=True, mode=manifest["mode"],baselineControl=manifest.get("baselineControl",False),moduleMode=manifest.get("moduleMode"),animationBackend=manifest.get("animationBackend"),syntheticAllGroupRegistration=manifest.get("syntheticAllGroupRegistration",False))
        with tempfile.TemporaryDirectory(prefix="pokeweb-animation-sweep-") as scratch:
            for index in range(min(args.jobs, len(cases))):
                selected = cases[index::args.jobs]
                child = directory / f"worker-{index+1}"
                temp = Path(scratch) / f"worker-{index+1}"
                temp.mkdir()
                command = [__import__("sys").executable, str(Path(__file__).resolve()), "--worker", "--scratch", str(temp), "--fixtures", str(fixtures), "--out", str(child), "--moves", *[str(c["sourceMoveId"]) for c in selected], "--max-frames", str(args.max_frames), "--boot-frames", str(args.boot_frames), "--case-timeout", str(args.case_timeout)]
                for option in ("melon_python", "melon_lib"):
                    if getattr(args, option):
                        command += ["--"+option.replace("_", "-"), getattr(args,option)]
                if args.verify_teardown:command.append("--verify-teardown")
                if args.trace_allocation_failures:command.append("--trace-allocation-failures")
                jobs.append({"process":subprocess.Popen(command), "directory":child, "selected":selected, "seen":None, "deadline":time.monotonic()+args.case_timeout+30})
            while any(job["process"].poll() is None for job in jobs):
                for job in jobs:
                    if job["process"].poll() is not None:
                        continue
                    path = job["directory"] / "result.json"
                    try:
                        progress = json.loads(path.read_text())
                        seen = (len(progress["cases"]), (progress.get("activeCase") or {}).get("sourceMoveId"))
                        if seen != job["seen"]:
                            job.update(seen=seen, deadline=time.monotonic()+args.case_timeout+15)
                    except (FileNotFoundError,json.JSONDecodeError):
                        pass
                    if time.monotonic() > job["deadline"]:
                        job["process"].kill()
                        job["process"].wait()
                        job["watchdog"] = True
                        print(f"FAIL {job['directory'].name}: native worker exceeded watchdog deadline",flush=True)
                time.sleep(0.25)
            for job in jobs:
                path = job["directory"] / "result.json"
                partial = json.loads(path.read_text()) if path.exists() else {"cases":[]}
                results.extend(partial["cases"])
                done = {c["sourceMoveId"] for c in partial["cases"]}
                for case in job["selected"]:
                    if case["sourceMoveId"] not in done:
                        results.append({**case,"passed":False,"error":"Native worker stopped before case completed", "watchdog":job.get("watchdog",False)})
                if job["process"].returncode and all(c["passed"] for c in partial["cases"]):
                    report.setdefault("workerErrors",[]).append(job["directory"].name)
            report.update(cases=sorted(results,key=lambda c:c["sourceMoveId"]),passed=bool(results) and all(c["passed"] for c in results) and not report.get("workerErrors"))
    finally:
        for job in jobs:
            if job["process"].poll() is None:
                job["process"].kill()
                job["process"].wait()
        if not args.fixtures and not args.keep_fixtures:
            report["removedFixtureRoms"] = common.cleanup_fixture_rom(fixtures)
        report.update(wallSeconds=round(time.monotonic()-started,3), scratchCleaned=True)
        (directory / "result.json").write_text(json.dumps(report,indent=2)+"\n")
    print(f"{sum(c['passed'] for c in report['cases'])}/{len(report['cases'])} passed; Report: {directory.relative_to(ROOT) if directory.is_relative_to(ROOT) else directory.name}/result.json",flush=True)
    return 0 if report["passed"] else 1


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom")
    parser.add_argument("--save", default=str(common.paths.DEFAULT_SAVE))
    parser.add_argument("--fixtures")
    parser.add_argument("--out")
    parser.add_argument("--moves", type=int, nargs="+")
    parser.add_argument("--sprites", choices=("streamed","native"), default="streamed")
    parser.add_argument("--modules", choices=("missing","production","corrupt","wrong-abi","truncated","corrupt-tables","heap-refusal"), default="missing")
    # Raging Fury's unchanged imported script exceeds 2,400 frames. Keep a
    # finite bound that accommodates it rather than reporting a false hang.
    parser.add_argument("--max-frames", type=int, default=4800)
    parser.add_argument("--boot-frames", type=int, default=2400)
    parser.add_argument("--case-timeout", type=float, default=120)
    parser.add_argument("--keep-fixtures", action="store_true")
    parser.add_argument("--verify-teardown", action="store_true", help="Win a bounded native battle and require zero child/stream counters")
    parser.add_argument("--authoring-smoke", action="store_true", help="Exercise private newly authored Pokemon/trainer streams; no visual-correctness claim")
    parser.add_argument("--baseline-control", action="store_true", help="Diagnostic pinned prebuilt base-core/Pyro-asset comparison; not acceptance evidence")
    parser.add_argument("--native-mechanics", action="store_true", help="Keep original effect/category/type metadata and use a faster attacking target")
    parser.add_argument("--stress-loader", help="Private diagnostic veils DLL registering all groups; never a production module")
    parser.add_argument("--trace-allocation-failures", action="store_true", help="Expensive native heap-allocation failure tracing")
    parser.add_argument("--isolate-particles", action="store_true", help="DIAGNOSTIC: remove particle commands from the two inherited faulting scripts")
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--worker", action="store_true", help=argparse.SUPPRESS)
    parser.add_argument("--scratch", help=argparse.SUPPRESS)
    parser.add_argument("--melon-python")
    parser.add_argument("--melon-lib")
    args = parser.parse_args()
    if not args.rom and not args.fixtures:
        parser.error("Supply --rom or --fixtures")
    if args.jobs < 1 or args.max_frames < 1 or args.case_timeout <= 0:
        parser.error("Jobs, frame limits and deadlines must be positive")
    raise SystemExit(run(args) if args.worker else supervise(args))
