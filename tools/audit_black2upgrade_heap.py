#!/usr/bin/env python3
"""Fail the B2 build if the documented worst-case PMC allocation budget is unsafe."""

from __future__ import annotations

import argparse
import json
import subprocess
from pathlib import Path
from pwan.report_paths import write_report


LOADABLE_SECTIONS = {".text", ".rodata", ".rodata.str1.1", ".rodata.cst16", ".rodata.cst8", ".data", ".bss"}


def elf_load_size(path: Path) -> tuple[int, dict[str, int]]:
    output = subprocess.check_output(["arm-none-eabi-size", "-A", str(path)], text=True)
    sections: dict[str, int] = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 2 and fields[0] in LOADABLE_SECTIONS:
            sections[fields[0]] = int(fields[1])
    if not sections:
        raise RuntimeError(f"could not measure loadable sections in {path}")
    return sum(sections.values()), sections


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--core", required=True, type=Path)
    parser.add_argument("--pwan-battle", required=True, type=Path)
    parser.add_argument("--ui", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()

    # This is the fixed-allocator concurrency envelope used by B2 V1. The
    # 0x60000 pool excludes PMC's separately reserved 0x8000 overlay image.
    budget = 0x60000
    required_margin = 0x18000
    dynamic = {
        "terrainParticleLibrary": 0x4800,
        "terrainSpaAndResourceWorstCase": 0x10000,
        "terrainTextureReplacementBuffers": 0x8000,
        "allocatorAndModuleBookkeeping": 0x8000,
    }
    modules = {}
    module_total = 0
    for name, path in (("residentCore", args.core), ("pwanBattle", args.pwan_battle), ("uiCompanion", args.ui)):
        size, sections = elf_load_size(path)
        modules[name] = {"path": str(path), "loadBytes": size, "sections": sections}
        module_total += size
    used = module_total + sum(dynamic.values())
    remaining = budget - used
    report = {
        "schemaVersion": 1,
        "allocatorModel": "fixed B2 PMC module pool; PMC overlay reservation excluded",
        "budgetBytes": budget,
        "requiredSafetyMarginBytes": required_margin,
        "modules": modules,
        "dynamicWorstCaseBytes": dynamic,
        "worstCaseUsedBytes": used,
        "remainingBytes": remaining,
        "passed": remaining >= required_margin,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    write_report(args.output, report)
    if remaining < required_margin:
        raise SystemExit(
            f"Black2Upgrade heap audit failed: {remaining} bytes remain; "
            f"the documented safety margin is {required_margin} bytes"
        )
    print(f"Black2Upgrade heap audit passed: {used}/{budget} bytes, {remaining} bytes remain")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
