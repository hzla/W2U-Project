"""Build the upgrade-owned, test-only native multi-trainer setup adapter."""
import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[3]
SOURCE = ROOT / "tests/battle/runtime"


def build(output):
    toolchain = Path(os.environ.get("ARM_TOOLCHAIN_BIN", ROOT.parent /
        "Port-Pokeweb/toolchains/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi/bin"))
    jar = Path(os.environ.get("RPM_TOOL_JAR", ROOT / "tools/CTRMap/CTRMapV-dirty.jar"))
    output.mkdir(parents=True, exist_ok=True)
    run = lambda *args: subprocess.run(list(map(str, args)), check=True)
    run(toolchain / "arm-none-eabi-gcc", "-mthumb", "-mcpu=arm946e-s", "-Os",
        "-std=c11", "-ffreestanding", "-fvisibility=hidden", "-fno-builtin",
        "-fno-unwind-tables", "-fno-asynchronous-unwind-tables", "-Wall", "-Wextra",
        "-Werror", "-c", SOURCE / "multi.c", "-o", output / "multi.o")
    run(toolchain / "arm-none-eabi-as", "-mthumb", "-march=armv5t",
        SOURCE / "multi.s", "-o", output / "hooks.o")
    run(toolchain / "arm-none-eabi-ld", "-r", output / "multi.o", output / "hooks.o",
        "-o", output / "multi.elf")
    (output / "metadata.yml").write_text(
        "PMCGameID: W2\nPMCModulePriority: 3\nPMCVersion: multi-harness-1\n")
    dll = output / "W2UMultiHarness.dll"
    dll.unlink(missing_ok=True)
    run(os.environ.get("JAVA", "java"), "-cp", jar, "rpm.cli.RPMTool", "-i",
        output / "multi.elf", "--fourcc", "DLXF", "-o", dll, "--esdb",
        SOURCE / "symbols.yml", "--meta", output / "metadata.yml",
        "--generate-relocations", "--strip")
    specification=importlib.util.spec_from_file_location("multi_cpu",Path(__file__).with_name("verify-multi-runtime.py"))
    verifier=importlib.util.module_from_spec(specification)
    specification.loader.exec_module(verifier)
    receipt = {"version": 1, "cpuChecks":verifier.verify(dll), "dllSha256": hashlib.sha256(dll.read_bytes()).hexdigest(),
        "sources": {name: hashlib.sha256((SOURCE / name).read_bytes()).hexdigest()
                    for name in ("multi.c", "multi.s", "symbols.yml")}}
    (output / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", required=True, type=Path)
    build(parser.parse_args().out)
