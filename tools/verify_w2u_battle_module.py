#!/usr/bin/env python3
"""Verify a White 2 child ELF/RPM pair before it is staged."""

from __future__ import annotations

import argparse
import re
import struct
import subprocess
from pathlib import Path


API_SYMBOL = "W2U_GetBattleModuleApi"
FORBIDDEN_DEFINED = re.compile(r"(?:THUMB_BRANCH|HOOK|_GLOBAL__sub_I_|__cxa_atexit)")
FORBIDDEN_CORE_IMPORT = re.compile(r"(?:Handler|Handlers|EventAddTable)")


def command(*args: str) -> str:
    return subprocess.run(
        args,
        check=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    ).stdout


def u16(data: bytes, offset: int) -> int:
    return struct.unpack_from("<H", data, offset)[0]


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def fnv1a(name: str) -> int:
    value = 0x811C9DC5
    for byte in name.encode("ascii"):
        value = ((value ^ byte) * 16777619) & 0xFFFFFFFF
    return value


def rpm_export_hashes(path: Path) -> list[int]:
    data = path.read_bytes()
    if len(data) < 24 or data[:4] != b"DLXF":
        raise RuntimeError(f"{path}: invalid RPM header")
    exec_offset = u32(data, 8)
    if exec_offset + 20 > len(data) or data[exec_offset : exec_offset + 4] != b"DLXH":
        raise RuntimeError(f"{path}: invalid executable header")
    info_offset = exec_offset + u32(data, exec_offset + 8)
    if info_offset + 36 > len(data) or data[info_offset : info_offset + 4] != b"INFO":
        raise RuntimeError(f"{path}: invalid INFO section")
    symbols_offset = exec_offset + u32(data, info_offset + 4)
    if symbols_offset + 24 > len(data) or data[symbols_offset : symbols_offset + 4] != b"SYM0":
        raise RuntimeError(f"{path}: invalid symbol section")
    export_count = u16(data, symbols_offset + 10)
    hash_relative = u32(data, symbols_offset + 16)
    if not export_count or not hash_relative:
        raise RuntimeError(f"{path}: missing export hash table")
    hash_offset = exec_offset + hash_relative
    hash_end = hash_offset + export_count * 4
    if hash_end > len(data):
        raise RuntimeError(f"{path}: export hash table exceeds RPM bounds")
    return list(struct.unpack_from(f"<{export_count}I", data, hash_offset))


def defined_symbols(path: Path) -> list[str]:
    output = command("arm-none-eabi-nm", "--defined-only", str(path))
    return [line.split()[-1] for line in output.splitlines() if line.split()]


def undefined_symbols(path: Path) -> list[str]:
    output = command("arm-none-eabi-nm", "-u", str(path))
    return [line.split()[-1] for line in output.splitlines() if line.split()]


def default_global_api_count(path: Path) -> int:
    output = command("arm-none-eabi-readelf", "-Ws", str(path))
    count = 0
    for line in output.splitlines():
        fields = line.split()
        if (
            len(fields) >= 8
            and fields[3] == "FUNC"
            and fields[4] == "GLOBAL"
            and fields[5] == "DEFAULT"
            and fields[7] == API_SYMBOL
        ):
            count += 1
    return count


def reject_lifecycle_sections(path: Path) -> None:
    output = command("arm-none-eabi-readelf", "-SW", str(path))
    for line in output.splitlines():
        match = re.match(
            r"\s*\[\s*\d+\]\s+(\.\S+)\s+\S+\s+[0-9a-fA-F]+\s+"
            r"[0-9a-fA-F]+\s+([0-9a-fA-F]+)",
            line,
        )
        if not match or match.group(1) not in (".init_array", ".fini_array"):
            continue
        if int(match.group(2), 16) != 0:
            raise RuntimeError(f"{path}: non-empty {match.group(1)} is prohibited")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", type=Path, required=True)
    parser.add_argument("--rpm", type=Path, required=True)
    parser.add_argument("--core", type=Path, required=True)
    args = parser.parse_args()

    if default_global_api_count(args.elf) != 1:
        raise RuntimeError(f"{args.elf}: expected exactly one public module API export")
    reject_lifecycle_sections(args.elf)

    defined = defined_symbols(args.elf)
    forbidden = sorted(symbol for symbol in defined if FORBIDDEN_DEFINED.search(symbol))
    if forbidden:
        raise RuntimeError(f"{args.elf}: forbidden symbols: {', '.join(forbidden)}")

    core_defined = set(
        line.split()[-1]
        for line in command(
            "arm-none-eabi-nm", "-g", "--defined-only", str(args.core)
        ).splitlines()
        if line.split()
    )
    imports = undefined_symbols(args.elf)
    broad_state_imports = sorted(
        symbol for symbol in imports if symbol.endswith("_GetStorage")
    )
    if broad_state_imports:
        raise RuntimeError(
            f"{args.elf}: imports mutable shared layouts: "
            + ", ".join(broad_state_imports)
        )
    missing_core = sorted(
        symbol
        for symbol in imports
        if symbol.startswith("W2U_") and symbol not in core_defined
    )
    if missing_core:
        raise RuntimeError(
            f"{args.elf}: resident W2U imports are unavailable: {', '.join(missing_core)}"
        )
    direct_child_imports = sorted(
        symbol
        for symbol in imports
        if symbol.startswith("W2U_") and FORBIDDEN_CORE_IMPORT.search(symbol)
    )
    if direct_child_imports:
        raise RuntimeError(
            f"{args.elf}: imports child implementation symbols: "
            + ", ".join(direct_child_imports)
        )

    hashes = rpm_export_hashes(args.rpm)
    if len(hashes) != 1:
        raise RuntimeError(
            f"{args.rpm}: expected exactly one RPM export, found {len(hashes)}"
        )
    if fnv1a(API_SYMBOL) not in hashes:
        raise RuntimeError(f"{args.rpm}: API export hash was stripped")
    if API_SYMBOL.encode("ascii") in args.rpm.read_bytes():
        raise RuntimeError(f"{args.rpm}: API symbol name string was not stripped")

    print(
        f"[+] {args.rpm.name}: one public API; export hash retained; "
        f"{len(imports)} imports reviewed"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
