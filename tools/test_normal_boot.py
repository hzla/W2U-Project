#!/usr/bin/env python3
"""Cold-boot the byte-identical release ROM, not a materialized battle fixture.

Uses headless melonDS with a private ROM/save copy and ordinary keypad input.
Never edits game RAM, loads a savestate, or writes caller saves. This is a
US White 2 rev-0 DS-mode startup check, not complete gameplay certification.
"""
import argparse
from contextlib import contextmanager
import ctypes
import hashlib
import json
import os
from pathlib import Path
import shutil
import struct
import sys
import tempfile

from patch_arm9_footer import DEFAULT_FOOTER_OFFSET, MODULE_PARAMS_MAGIC

ROOT = Path(__file__).resolve().parents[1]
HEADLESS = ROOT.parent / "Port-Pokeweb/work/scan-button"


def digest(path):
    value = hashlib.sha256()
    with path.open("rb") as stream:
        for data in iter(lambda: stream.read(1024 * 1024), b""):
            value.update(data)
    return value.hexdigest()


def file_names(fnt):
    """Walk bounded Nitro directory records; include paths, not just basenames."""
    if len(fnt) < 8:
        raise ValueError("Truncated filename table")
    count = struct.unpack_from("<H", fnt, 6)[0]
    if not count or count * 8 > len(fnt):
        raise ValueError("Invalid directory count")
    pending, seen, result = [(0, "")], set(), []
    while pending:
        index, prefix = pending.pop()
        if index >= count or index in seen:
            raise ValueError("Invalid or cyclic directory reference")
        seen.add(index)
        cursor = struct.unpack_from("<I", fnt, index * 8)[0]
        if cursor < count * 8 or cursor >= len(fnt):
            raise ValueError("Invalid directory offset")
        while cursor < len(fnt):
            length = fnt[cursor]
            cursor += 1
            if not length:
                break
            size = length & 127
            if not size or size > len(fnt) - cursor:
                raise ValueError("Truncated filename")
            name = fnt[cursor:cursor + size].decode("ascii")
            cursor += size
            if "/" in name or name in (".", ".."):
                raise ValueError("Invalid filename component")
            path = prefix + name
            if length & 128:
                if cursor + 2 > len(fnt):
                    raise ValueError("Truncated directory reference")
                child = struct.unpack_from("<H", fnt, cursor)[0]
                cursor += 2
                if child < 0xF000:
                    raise ValueError("Invalid directory ID")
                pending.append((child - 0xF000, path + "/"))
            else:
                result.append(path)
        else:
            raise ValueError("Unterminated directory")
    return result


def validate_release_startup(path):
    size = path.stat().st_size
    with path.open("rb") as stream:
        header = stream.read(0x1000)
        if len(header) != 0x1000 or header[0x0C:0x10] != b"IRDO" or header[0x1E] != 0:
            raise ValueError("Expected supported US White 2 release")
        offset = struct.unpack_from("<I", header, 0x20)[0]
        length = struct.unpack_from("<I", header, 0x2C)[0]
        if offset < len(header) or length <= DEFAULT_FOOTER_OFFSET + 16 or offset + length > size:
            raise ValueError("Invalid ARM9 range")
        stream.seek(offset + DEFAULT_FOOTER_OFFSET)
        startup = stream.read(16)
        if startup[8:] != MODULE_PARAMS_MAGIC or startup[:4] != b"\0" * 4:
            raise ValueError("Expanded release ARM9 retains invalid/stale compression metadata")
        offset, length = struct.unpack_from("<II", header, 0x40)
        if not length or offset < len(header) or offset + length > size:
            raise ValueError("Invalid filename-table range")
        stream.seek(offset)
        names = file_names(stream.read(length))
    if any(name.lower().startswith("patches/") and "mainmenuskip" in name.lower()
           for name in names):
        raise ValueError("Production ROM contains a testing main-menu skip")
    return {"compressed_static_end": 0, "main_menu_skip_staged": False}


@contextmanager
def native_log(path):
    sys.stdout.flush()
    sys.stderr.flush()
    saved = [os.dup(fd) for fd in (1, 2)]
    try:
        with path.open("w") as stream:
            for fd in (1, 2):
                os.dup2(stream.fileno(), fd)
            yield
    finally:
        sys.stdout.flush()
        sys.stderr.flush()
        ctypes.CDLL(None).fflush(None)
        for fd, original in zip((1, 2), saved):
            os.dup2(original, fd)
            os.close(original)


def run(args, report):
    sys.path.insert(0, str(args.melon_python))
    from melonds import MelonDS
    with tempfile.TemporaryDirectory(prefix="w2u-normal-boot-") as temporary:
        rom = Path(temporary) / "boot.nds"
        shutil.copyfile(args.rom, rom)
        if args.save:
            shutil.copyfile(args.save, rom.with_suffix(".sav"))
        if digest(rom) != report["input_rom_sha256"]:
            raise RuntimeError("Private ROM copy differs from release input")
        emulator = MelonDS(args.melon_lib)
        hooks = []
        try:
            for name, address in (("undefined", 0xFFFF0004), ("prefetch_abort", 0xFFFF000C),
                                  ("data_abort", 0xFFFF0010), ("assert", 0x0203CBC0),
                                  ("error_loop", 0x02012038), ("normal_menu", 0x02036318),
                                  ("field_continue", 0x0217CC60)):
                def observe(cpu, address, name=name):
                    report["event_counts"][name] = report["event_counts"].get(name, 0) + 1
                    if name not in report["first_events"]:
                        registers = emulator.memory.register_arm9
                        report["first_events"][name] = {"frame": emulator.frame_count,
                            "pc": hex(registers.pc), "lr": hex(registers.lr)}
                hooks.append(emulator.memory.register_exec(address, observe))
            emulator.open(rom)
            for frame in range(args.frames):
                emulator.input.keypad_update(1 if frame > 240 and frame % 90 < 5 else 0)
                emulator.cycle()
                if any(report["event_counts"].get(name, 0) for name in
                       ("undefined", "prefetch_abort", "data_abort", "assert", "error_loop")):
                    raise RuntimeError("Native startup entered an exception/assertion path")
            emulator.input.keypad_update(0)
            emulator.screenshot().save(args.out / "screens.png")
            report["frames"] = emulator.frame_count
            if not report["event_counts"].get("normal_menu"):
                raise RuntimeError("Native normal-menu path was never reached")
            if args.expect_continue and not report["event_counts"].get("field_continue"):
                raise RuntimeError("Saved-game Continue path was never reached")
            report["passed"] = True
        finally:
            for hook in hooks:
                hook.remove()
            emulator.destroy()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--save", type=Path, help="copied privately; caller save is never opened by the emulator")
    parser.add_argument("--expect-continue", action="store_true")
    parser.add_argument("--frames", type=int, default=1800)
    parser.add_argument("--out", type=Path, help="new, ignored evidence directory")
    parser.add_argument("--check-only", action="store_true", help="validate raw release metadata/packaging without an emulator")
    parser.add_argument("--melon-python", type=Path,
                        default=Path(os.environ.get("MELONDS_PYTHON_PATH", HEADLESS / "emulator-ref/python")))
    parser.add_argument("--melon-lib", type=Path,
                        default=Path(os.environ.get("MELONDS_HEADLESS_LIB", HEADLESS / "emulator-build/src/headless/libmelonds_headless.dylib")))
    args = parser.parse_args()
    if args.check_only:
        print(json.dumps(validate_release_startup(args.rom), indent=2))
        return 0
    if not args.out:
        parser.error("--out is required for native emulation")
    if args.frames < 1 or args.frames > 7200 or (args.expect_continue and not args.save):
        parser.error("Require 1..7200 frames and a save for --expect-continue")
    args.out.mkdir(parents=True, exist_ok=False)
    (args.out / ".gitignore").write_text("*\n")
    report = {"schema_version": 1, "passed": False, "input_rom_sha256": digest(args.rom),
              "input_save_sha256": digest(args.save) if args.save else None,
              "rom_modified_for_test": False, "caller_save_modified": False,
              "savestate_used": False, "memory_written_for_test": False,
              "event_counts": {}, "first_events": {}}
    try:
        report["startup"] = validate_release_startup(args.rom)
        with native_log(args.out / "native.log"):
            run(args, report)
    except Exception as error:
        report["error"] = str(error)
    (args.out / "result.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    return 0 if report["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
