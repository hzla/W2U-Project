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
    def __init__(self, emu):
        self.emu = emu
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

    def install(self, probes):
        for probe in probes:
            def callback(cpu, address, name=probe["name"], probe=probe):
                try:
                    if probe.get("signature") and bytes(self.emu.memory.unsigned[address:address+len(probe["signature"])//2]).hex() != probe["signature"]:
                        raise AssertionError(f"Native probe signature mismatch: {name}")
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

    def ability(self, cpu, address):
        pointer = self.emu.memory.register_arm9.r0
        slot = self.emu.memory.read_byte(pointer + 25)
        self.pointers[slot] = pointer

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
            self.ends.append({"frame": self.emu.frame_count, "animationId": self.emu.memory.read_short(context + 0x258)})

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
                except Exception as error:
                    self.errors.append(str(error))
            self.returns[ret] = self.emu.memory.register_exec(ret, returned)

    def cycle(self):
        self.emu.cycle()
        common.check(not self.errors, "; ".join(self.errors))
        for name in ("register_arm9", "register_arm7"):
            r = getattr(self.emu.memory, name)
            common.check(r.cpsr & 0x1f not in (0x17, 0x1b), f"{name} entered fault mode at {r.pc:#x}")

    def close(self):
        for hook in [*self.hooks,*self.returns.values()]:
            hook.remove()


def prepare(args, directory):
    fixtures = Path(args.fixtures).resolve() if args.fixtures else directory / "fixtures"
    if not args.fixtures:
        subprocess.run([*common.fixture_builder_command("build-animation-completion-fixtures.ts"), "--rom", str(Path(args.rom).resolve()), "--save", str(Path(args.save).resolve()), "--out", str(fixtures)], cwd=ROOT, check=True)
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
            observer = Observer(emu)
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
            for case in cases:
                report["activeCase"] = {"sourceMoveId": case["sourceMoveId"], "name": case["name"]}
                (directory / "result.json").write_text(json.dumps(report,indent=2)+"\n")
                emu.restore_snapshot(snapshot)
                emu.input.keypad_update(0)
                emu.input.touch_release()
                observer.case, observer.commands, observer.loads, observer.damage_calls, observer.errors = case, 0, [], 0, []
                observer.ui_phase = None
                observer.command_frames = []
                observer.ends, observer.waits = [], []
                observer.read_pending, observer.scripts = {}, []
                mon = observer.pointers[0]
                # Bounded pre-input move-list fixture only. Selection, execution,
                # VM instructions, waits and completion flags run unmodified.
                for pointer in {mon, observer.client_pointer}:
                    identity = common.read_mon(emu,pointer)
                    common.check(identity["species"] == 151 and identity["slot"] == 0, "Wrong fixture BattleMon identity")
                    for offset in (0x104, 0x10a):
                        common.check(emu.memory.read_short(pointer+offset) == 845, "Unexpected checkpoint move list")
                        emu.memory.write_short(pointer + offset, case["moveId"])
                        emu.memory.write_byte(pointer + offset + 2, 35)
                result = {**case, "passed": False}
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
                result.update(frames=emu.frame_count-frame, wallSeconds=round(time.monotonic()-case_start,3), verifiedScripts=observer.scripts, animationLoads=observer.loads, animationEnds=observer.ends, animationWaits=observer.waits, uiPhase=hex(observer.ui_phase or 0), damageCalls=observer.damage_calls, commandCalls=observer.commands, commandFrames=observer.command_frames, pp=emu.memory.read_byte(mon+0x106), arm9Pc=hex(emu.memory.register_arm9.pc), arm7Pc=hex(emu.memory.register_arm7.pc))
                report["cases"].append(result)
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
        report.update(inputRomSha256=manifest["inputRomSha256"], fixtureRomSha256=manifest["rom"]["sha256"], animationsEnabled=True, mode=manifest["mode"])
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
    parser.add_argument("--max-frames", type=int, default=2400)
    parser.add_argument("--boot-frames", type=int, default=2400)
    parser.add_argument("--case-timeout", type=float, default=120)
    parser.add_argument("--keep-fixtures", action="store_true")
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
