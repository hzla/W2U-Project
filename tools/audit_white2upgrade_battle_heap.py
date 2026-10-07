#!/usr/bin/env python3
"""Audit White 2 resident and on-demand RPM use against the 200 KiB PMC heap (tools/patch_pmc_sysheap.py)."""

from __future__ import annotations

import argparse
import base64
import json
import struct
from pathlib import Path
from pwan.report_paths import portable_report


HEAP_BYTES = 200 * 1024
REQUIRED_HEADROOM = 12 * 1024
ALLOCATOR_BYTES_PER_MODULE = 16
ALLOCATOR_ALIGNMENT = 8
# The fixed record array and telemetry live in White2Upgrade.dll's BSS and are
# already included in the core RPM's post-fix size.
LOADER_FIXED_BYTES = 0
# Verified bundled PMC layout. The work area's object and buffer are two
# allocations from the primary arena; its small internal allocations consume
# that buffer, not another primary-heap allowance.
PMC_ROOT_OBJECT_BYTES = 32
PMC_WORK_AREA_BYTES = 32 + 16 + 4096 + 16
PMC_BOOKKEEPING_AND_FRAGMENTATION_RESERVE = 512

# Battle modules on GFL heap 1 (White 2, w2u_battle_module_loader.cpp PlaceOnGameHeap): the PMC floor applies to the
# heap with every group there; the groups get a budget on heap 1 instead. Heap 1's room during battles was measured
# natively (w2u-local harness `game_heaps: true`: direct-boot and overworld battles, the heaviest a doubles battle with
# two Mega Evolutions, terrain, heavy rain and animations; 2026-10-07): 512,856 bytes free, unchanged for the whole
# battle. The loader keeps GAME_HEAP_RESERVE of it for the game and falls back to PMC's heap when it is short.
GAME_HEAP_BATTLE_ROOM = 512856
GAME_HEAP_RESERVE = 0x10000
GAME_HEAP_BLOCK_OVERHEAD = 24 + 16            # W2U's block header (size, raw, allocator, 8-alignment) + NNS's
def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def rpm_sizes(path: Path) -> tuple[int, int]:
    return rpm_data_sizes(path.read_bytes(), str(path))


def rpm_data_sizes(data: bytes, path: str) -> tuple[int, int]:
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
    return module_data_record(path.read_bytes(), str(path))


def module_data_record(data: bytes, path: str) -> dict:
    expanded, fixed = rpm_data_sizes(data, path)
    resident = fixed + expanded - len(data)
    return {
        "path": str(path),
        "file_bytes": len(data),
        "expanded_bytes": expanded,
        "fixed_bytes": fixed,
        # INTERNAL_RELOCATIONS removes relocation metadata, not the BSS tail.
        "bss_bytes": expanded - len(data),
        "resident_bytes": resident,
        "allocated_payload_bytes": (resident + ALLOCATOR_ALIGNMENT - 1) & -ALLOCATOR_ALIGNMENT,
        "expanded_payload_bytes": (expanded + ALLOCATOR_ALIGNMENT - 1) & -ALLOCATOR_ALIGNMENT,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--core", type=Path, required=True)
    parser.add_argument("--pwan-battle", type=Path, help="only when a PWAN battle runtime is staged (not since Phase 4)")
    parser.add_argument("--battle-log", type=Path, required=True)
    parser.add_argument("--battle-counters", type=Path, required=True)
    parser.add_argument("--save-guard", type=Path, required=True)
    parser.add_argument("--menu-skip", type=Path,
                        help="only for private fixtures which stage the testing main-menu skip")
    parser.add_argument("--module", type=Path, action="append", default=[])
    parser.add_argument("--registry", type=Path, required=True)
    parser.add_argument("--baseline", type=Path, required=True)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--enforce", action="store_true")
    parser.add_argument("--enforce-headroom", action="store_true",
                        help="fail only when every module loaded leaves less than the 12 KiB floor (the ROM's guard)")
    args = parser.parse_args()

    registry = json.loads(args.registry.read_text())
    baseline = json.loads(args.baseline.read_text())
    if baseline.get("heap_bytes") not in (164 * 1024, HEAP_BYTES):
        raise RuntimeError("baseline does not describe a patched PMC heap")
    monolithic_core_baseline = int(baseline["core_fixed_bytes"])
    monolithic_resident_baseline = int(baseline["resident_fixed_bytes"])
    expected_count = len(registry["modules"])
    if len(args.module) != expected_count:
        raise RuntimeError(
            f"expected {expected_count} child modules, got {len(args.module)}"
        )

    core = module_record(args.core)
    pwan = module_record(args.pwan_battle) if args.pwan_battle else {"path": None, "file_bytes": 0, "expanded_bytes": 0, "fixed_bytes": 0, "resident_bytes": 0}
    battle_log = module_record(args.battle_log)
    battle_counters = module_record(args.battle_counters)
    from stage_double_battle_fix import PATCH_BASE64, PATCH_NAME
    bootstrap = [module_record(args.save_guard),
                 module_data_record(base64.b64decode(PATCH_BASE64), "vfs/data/patches/" + PATCH_NAME)]
    if args.menu_skip:
        bootstrap.append(module_record(args.menu_skip))
    children = [module_record(path) for path in args.module]
    residents = [core, battle_log, battle_counters, *bootstrap]
    if args.pwan_battle:
        residents.append(pwan)
    resident_fixed = sum(record["allocated_payload_bytes"] for record in residents)
    resident_overhead = (len(residents) * ALLOCATOR_BYTES_PER_MODULE + LOADER_FIXED_BYTES +
                         PMC_ROOT_OBJECT_BYTES + PMC_WORK_AREA_BYTES + PMC_BOOKKEEPING_AND_FRAGMENTATION_RESERVE)
    no_custom = resident_fixed + resident_overhead
    typical_child = max((child["allocated_payload_bytes"] for child in children), default=0)
    typical = no_custom + typical_child + ALLOCATOR_BYTES_PER_MODULE
    all_children_fixed = sum(child["allocated_payload_bytes"] for child in children)
    all_groups = (
        no_custom
        + all_children_fixed
        + len(children) * ALLOCATOR_BYTES_PER_MODULE
    )
    # Conservative ordering: load the module with the largest temporary
    # relocation overhead last, with every other group already resident.
    largest_transient = max(children, key=lambda child: child["expanded_payload_bytes"] - child["allocated_payload_bytes"])
    transient_all = all_groups + largest_transient["expanded_payload_bytes"] - largest_transient["allocated_payload_bytes"]
    game_heap_children = sum(child["allocated_payload_bytes"] + GAME_HEAP_BLOCK_OVERHEAD for child in children)
    game_heap_transient = (game_heap_children + largest_transient["expanded_payload_bytes"]
                           - largest_transient["allocated_payload_bytes"])
    report = {
        "heap_bytes": HEAP_BYTES,
        "required_headroom_bytes": REQUIRED_HEADROOM,
        "allocator_bytes_per_module": ALLOCATOR_BYTES_PER_MODULE,
        "allocator_alignment": ALLOCATOR_ALIGNMENT,
        "loader_fixed_bytes": LOADER_FIXED_BYTES,
        "loader_state_included_in_core": True,
        "pmc_root_object_bytes": PMC_ROOT_OBJECT_BYTES,
        "pmc_work_area_bytes": PMC_WORK_AREA_BYTES,
        "pmc_bookkeeping_and_fragmentation_reserve_bytes": PMC_BOOKKEEPING_AND_FRAGMENTATION_RESERVE,
        "bootstrap_patches": bootstrap,
        "native_arena_limit_note": "The bundled constructor declares 64 bytes beyond the reserved arena; those bytes are never included in the 200-KiB budget.",
        "baseline": str(args.baseline),
        "monolithic_core_baseline_bytes": monolithic_core_baseline,
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
            "all_groups_transient_load": {
                "used_bytes": transient_all,
                "free_bytes": HEAP_BYTES - transient_all,
                "last_loaded_module": largest_transient["path"],
                "note": "Conservative expanded-module allocation before StartModule shrinks it; game heaps are separate.",
            },
            "all_groups_on_game_heap": {
                "used_bytes": no_custom,
                "free_bytes": HEAP_BYTES - no_custom,
                "note": "White 2: every group on GFL heap 1 during battle; PMC holds the residents only. The two "
                        "all_groups scenarios above are the fallback worst case (heap 1 short: groups on PMC, the "
                        "loader's refusal guard drops a mechanic instead of freezing).",
            },
        },
        "game_heap": {
            "heap_id": 1,
            "measured_battle_room_bytes": GAME_HEAP_BATTLE_ROOM,
            "reserve_bytes": GAME_HEAP_RESERVE,
            "block_overhead_bytes": GAME_HEAP_BLOCK_OVERHEAD,
            "all_groups_bytes": game_heap_children,
            "all_groups_transient_bytes": game_heap_transient,
            "spare_bytes": GAME_HEAP_BATTLE_ROOM - GAME_HEAP_RESERVE - game_heap_transient,
        },
    }

    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(portable_report(report), indent=2) + "\n")
    print(json.dumps(portable_report(report), indent=2))

    failures = []
    no_custom_saving = monolithic_core_baseline - core["fixed_bytes"]
    if no_custom_saving < 8 * 1024:
        failures.append(f"core saving is only {no_custom_saving} bytes")
    if monolithic_resident_baseline - typical < 4 * 1024:
        failures.append("largest one-group scenario saves less than 4 KiB")
    if HEAP_BYTES - all_groups < REQUIRED_HEADROOM:
        failures.append("all-group scenario on PMC's heap (the fallback worst case) leaves less than 12 KiB headroom")
    if args.enforce and failures:
        raise RuntimeError("; ".join(failures))
    if args.enforce_headroom:
        if HEAP_BYTES - no_custom < REQUIRED_HEADROOM:
            raise RuntimeError(
                f"with every group on the game heap, PMC's heap keeps {HEAP_BYTES - no_custom} bytes free, "
                f"under the {REQUIRED_HEADROOM}-byte floor")
        if game_heap_transient + GAME_HEAP_RESERVE > GAME_HEAP_BATTLE_ROOM:
            raise RuntimeError(
                f"every group on GFL heap 1 needs {game_heap_transient} bytes plus the {GAME_HEAP_RESERVE}-byte "
                f"reserve, over the {GAME_HEAP_BATTLE_ROOM} bytes measured free there during battles")
    if failures:
        print("[!] acceptance warnings: " + "; ".join(failures))
    else:
        print("[+] stripped heap acceptance thresholds passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
