#!/usr/bin/env python3
"""Verify the resident core never depends on child implementation symbols."""

from __future__ import annotations

import argparse
import re
import struct
import subprocess
from pathlib import Path

import yaml


PMC_RUNTIME_EXPORT_HASHES = {
    0x469AEBEF,
    0xA8054409,
    0xC6FA286C,
    0xC13E1C85,
    0x5529ACB6,
    0x5B7ED5FB,
}


def verify_hook_targets(definitions: set[str], database_symbols: set[str]) -> None:
    for name in sorted(definitions):
        match = re.fullmatch(
            r"THUMB_BRANCH_LINK_(.+)_0x[0-9A-Fa-f]+", name
        ) or re.fullmatch(r"THUMB_BRANCH_(?:SAFESTACK_)?(.+)", name)
        if not match or match[1].isdigit() or match[1] in ("ARM9", "ARM7") or re.fullmatch(r"(?:\d+|ARM9|ARM7)_0x[0-9A-Fa-f]+", match[1]):
            continue  # Direct numeric-overlay hooks (with or without LINK) have no named ESDB owner.
        if match[1] not in database_symbols:
            raise RuntimeError(f"{name}: missing ESDB hook owner {match[1]}; hook has no mapped game target")


def symbols(path: Path, *arguments: str) -> set[str]:
    output = subprocess.run(
        ["arm-none-eabi-nm", *arguments, str(path)],
        check=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    ).stdout
    return {line.split()[-1] for line in output.splitlines() if line.split()}


def rpm_export_hashes(path: Path) -> set[int]:
    data = path.read_bytes()

    def u16(offset: int) -> int:
        return struct.unpack_from("<H", data, offset)[0]

    def u32(offset: int) -> int:
        return struct.unpack_from("<I", data, offset)[0]

    exec_offset = u32(8)
    if data[exec_offset : exec_offset + 4] != b"DLXH":
        raise RuntimeError(f"{path}: missing DLXH header")
    info_offset = exec_offset + u32(exec_offset + 8)
    if data[info_offset : info_offset + 4] != b"INFO":
        raise RuntimeError(f"{path}: missing INFO section")
    symbol_offset = exec_offset + u32(info_offset + 4)
    if data[symbol_offset : symbol_offset + 4] != b"SYM0":
        raise RuntimeError(f"{path}: missing SYM0 section")
    export_count = u16(symbol_offset + 10)
    hash_offset = exec_offset + u32(symbol_offset + 16)
    return {u32(hash_offset + index * 4) for index in range(export_count)}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--core", type=Path, required=True)
    parser.add_argument("--child", type=Path, action="append", default=[])
    parser.add_argument("--expected-count", type=int, required=True)
    parser.add_argument("--pmc-symbols", type=Path, required=True)
    parser.add_argument("--esdb", type=Path, required=True)
    parser.add_argument("--stamp", type=Path, required=True)
    args = parser.parse_args()

    if len(args.child) != args.expected_count:
        raise RuntimeError(
            f"expected {args.expected_count} child ELFs, got {len(args.child)}"
        )
    core_imports = symbols(args.core, "-u")
    database = yaml.safe_load(args.esdb.read_text(encoding="utf-8"))
    verify_hook_targets(symbols(args.core, "--defined-only"), {entry["Name"] for entry in database["Symbols"]})
    direct_pmc_imports = sorted(
        symbol for symbol in core_imports if symbol.startswith("_ZN3pmc3fwk")
    )
    if direct_pmc_imports:
        raise RuntimeError(
            "resident core directly imports PMC runtime functions instead of "
            "using the relocatable symbol-RPM resolver: "
            + ", ".join(direct_pmc_imports)
        )

    missing_pmc_exports = PMC_RUNTIME_EXPORT_HASHES - rpm_export_hashes(args.pmc_symbols)
    if missing_pmc_exports:
        raise RuntimeError(
            f"{args.pmc_symbols}: missing required PMC runtime export hashes: "
            + ", ".join(f"0x{value:08X}" for value in sorted(missing_pmc_exports))
        )

    child_definitions: set[str] = set()
    for child in args.child:
        child_definitions.update(symbols(child, "--defined-only"))
    forbidden = sorted(core_imports & child_definitions)
    if forbidden:
        raise RuntimeError(
            "resident core imports child implementation symbols: "
            + ", ".join(forbidden)
        )

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()
    print(
        f"[+] resident core has no direct PMC/child imports; "
        f"all branch-hook owners, six runtime exports and {len(args.child)} children verified"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
