#!/usr/bin/env python3
"""Audit White 2 resident and on-demand RPM use against the 164 KiB PMC heap."""

from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path
from pwan.report_paths import portable_report


HEAP_BYTES = 164 * 1024
REQUIRED_HEADROOM = 12 * 1024
ALLOCATOR_BYTES_PER_MODULE = 16
# The fixed record array and telemetry live in White2Upgrade.dll's BSS and are
# already included in the core RPM's post-fix size.
LOADER_FIXED_BYTES = 0


def acceptance_failures(baseline_resident: int, no_custom: int,
                        typical: int, all_groups: int) -> list[str]:
    """Acceptance compares complete battle sets, not only the core RPM.

    Keep the captured pre-refactor baseline unchanged. Loader state and all
    current resident modules/allocator headers are charged in each scenario.
    Core-only savings remain a reported diagnostic, not a separate requirement.
    """
    failures = []
    if baseline_resident - no_custom < 8 * 1024:
        failures.append("no-custom battle saves less than 8 KiB")
    if baseline_resident - typical < 4 * 1024:
        failures.append("largest one-group scenario saves less than 4 KiB")
    if HEAP_BYTES - all_groups < REQUIRED_HEADROOM:
        failures.append("all-group scenario leaves less than 12 KiB headroom")
    return failures


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def rpm_sizes(path: Path) -> tuple[int, int]:
    data = path.read_bytes()
    if len(data) < 24 or data[:4] != b"DLXF":
        raise RuntimeError(f"{path}: invalid RPM header")
    expanded = u32(data, 4)
    exec_offset = u32(data, 8)
    if expanded < len(data) or exec_offset + 20 > len(data):
        raise RuntimeError(f"{path}: invalid RPM size/exec offset")
    if data[exec_offset : exec_offset + 4] != b"DLXH":
        raise RuntimeError(f"{path}: invalid executable header")
    info_offset = exec_offset + u32(data, exec_offset + 8)
    if info_offset + 36 > len(data) or data[info_offset : info_offset + 4] != b"INFO":
        raise RuntimeError(f"{path}: invalid INFO section")
    reloc_relative = u32(data, info_offset + 8)
    fixed = expanded
    if reloc_relative:
        reloc_offset = exec_offset + reloc_relative
        if reloc_offset + 24 > len(data) or data[reloc_offset : reloc_offset + 4] != b"REL0":
            raise RuntimeError(f"{path}: invalid relocation section")
        internal_relative = u32(data, reloc_offset + 8)
        if internal_relative:
            fixed = exec_offset + internal_relative
    if fixed <= 0 or fixed > expanded:
        raise RuntimeError(f"{path}: invalid fixed size {fixed}")
    return expanded, fixed


def module_record(path: Path) -> dict:
    expanded, fixed = rpm_sizes(path)
    return {
        "path": str(path),
        "file_bytes": path.stat().st_size,
        "expanded_bytes": expanded,
        "fixed_bytes": fixed,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--core", type=Path, required=True)
    parser.add_argument("--pwan-battle", type=Path, required=True)
    parser.add_argument("--battle-log", type=Path, required=True)
    parser.add_argument("--battle-counters", type=Path, required=True)
    parser.add_argument("--module", type=Path, action="append", default=[])
    parser.add_argument("--registry", type=Path, required=True)
    parser.add_argument("--baseline", type=Path, required=True)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--enforce", action="store_true")
    args = parser.parse_args()

    registry = json.loads(args.registry.read_text())
    baseline = json.loads(args.baseline.read_text())
    if baseline.get("heap_bytes") != HEAP_BYTES:
        raise RuntimeError("baseline does not describe the patched 164 KiB heap")
    monolithic_core_baseline = int(baseline["core_fixed_bytes"])
    monolithic_resident_baseline = int(baseline["resident_fixed_bytes"])
    expected_count = len(registry["modules"])
    if len(args.module) != expected_count:
        raise RuntimeError(
            f"expected {expected_count} child modules, got {len(args.module)}"
        )

    core = module_record(args.core)
    pwan = module_record(args.pwan_battle)
    battle_log = module_record(args.battle_log)
    battle_counters = module_record(args.battle_counters)
    children = [module_record(path) for path in args.module]
    resident_fixed = (
        core["fixed_bytes"]
        + pwan["fixed_bytes"]
        + battle_log["fixed_bytes"]
        + battle_counters["fixed_bytes"]
    )
    resident_overhead = 4 * ALLOCATOR_BYTES_PER_MODULE + LOADER_FIXED_BYTES
    no_custom = resident_fixed + resident_overhead
    typical_child = max((child["fixed_bytes"] for child in children), default=0)
    typical = no_custom + typical_child + ALLOCATOR_BYTES_PER_MODULE
    all_children_fixed = sum(child["fixed_bytes"] for child in children)
    all_groups = (
        no_custom
        + all_children_fixed
        + len(children) * ALLOCATOR_BYTES_PER_MODULE
    )
    report = {
        "heap_bytes": HEAP_BYTES,
        "required_headroom_bytes": REQUIRED_HEADROOM,
        "allocator_bytes_per_module": ALLOCATOR_BYTES_PER_MODULE,
        "loader_fixed_bytes": LOADER_FIXED_BYTES,
        "loader_state_included_in_core": True,
        "baseline": str(args.baseline),
        "monolithic_core_baseline_bytes": monolithic_core_baseline,
        "core_saving_vs_monolith": monolithic_core_baseline - core["fixed_bytes"],
        "monolithic_resident_baseline_bytes": monolithic_resident_baseline,
        "core": core,
        "pwan_battle": pwan,
        "battle_log": battle_log,
        "battle_counters": battle_counters,
        "children": children,
        "scenarios": {
            "no_custom": {
                "used_bytes": no_custom,
                "free_bytes": HEAP_BYTES - no_custom,
                "resident_saving_vs_monolith": monolithic_resident_baseline - no_custom,
            },
            "typical_largest_single_group": {
                "used_bytes": typical,
                "free_bytes": HEAP_BYTES - typical,
                "resident_saving_vs_monolith": monolithic_resident_baseline - typical,
            },
            "all_groups_conservative": {
                "used_bytes": all_groups,
                "free_bytes": HEAP_BYTES - all_groups,
                "child_fixed_bytes": all_children_fixed,
            },
        },
    }

    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(portable_report(report), indent=2) + "\n")
    print(json.dumps(portable_report(report), indent=2))

    failures = acceptance_failures(monolithic_resident_baseline, no_custom, typical, all_groups)
    if args.enforce and failures:
        raise RuntimeError("; ".join(failures))
    if failures:
        print("[!] acceptance warnings: " + "; ".join(failures))
    else:
        print("[+] stripped heap acceptance thresholds passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
