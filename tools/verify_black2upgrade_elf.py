#!/usr/bin/env python3
"""Fail a B2U build when W2 addresses or unresolved aliases remain."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import subprocess


FORBIDDEN_W2_ADDRESSES = (
    0x02141428,
    0x021D7F38,
    0x021D8F68,
    0x021DA0F4,
    0x021EECFD,
    0x021F3644,
    0x021F3650,
    0x0203DA39,
    0x021D3171,
    0x0219C785,
    0x0219D1C9,
    0x021BB085,
    0x021DF7AD,
    0x0204BF49,
    0x0204BFC5,
    0x0204C06D,
    0x0204C135,
    0x0204C16D,
    0x0204C54D,
    0x0204C4B5,
    0x021A2429,
    0x0219FA19,
    0x0219FA39,
    0x0219FA29,
    0x0202452D,
    0x0219D78D,
    0x0219D815,
    0x0219F83D,
    0x0219DE59,
    0x0219F351,
    0x0219E689,
)


def command(*args: str) -> str:
    return subprocess.check_output(args, text=True)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("elf", type=Path)
    parser.add_argument("--esdb", type=Path, required=True)
    parser.add_argument("--allow-core-imports", action="store_true")
    args = parser.parse_args()

    esdb_names = set(re.findall(r"^\s+- Name:\s+(\S+)\s*$", args.esdb.read_text(), re.MULTILINE))
    undefined = []
    for line in command("arm-none-eabi-nm", "-u", str(args.elf)).splitlines():
        symbol = line.split()[-1]
        if args.allow_core_imports and symbol.startswith("W2U_"):
            continue
        if symbol not in esdb_names:
            undefined.append(symbol)
    if undefined:
        raise SystemExit(f"unmapped IREO imports in {args.elf}: {', '.join(sorted(undefined))}")

    dump = command("arm-none-eabi-objdump", "-dr", str(args.elf)).lower()
    retained = [f"0x{address:08x}" for address in FORBIDDEN_W2_ADDRESSES if f"{address:08x}" in dump]
    if retained:
        raise SystemExit(f"White 2 absolute addresses retained in {args.elf}: {', '.join(retained)}")

    symbols = command("arm-none-eabi-nm", "-a", str(args.elf))
    for match in re.finditer(r"(?:FULL_COPY|THUMB_BRANCH_LINK)_(165|167|168|169|207|255|265|299|302)_0x([0-9A-Fa-f]+)", symbols):
        overlay = int(match.group(1))
        address = int(match.group(2), 16)
        bounds = {
            165: (0x02199A00, 0x021A4D40),
            167: (0x021998C0, 0x021DDA60),
            168: (0x021DDA60, 0x021F4240),
            169: (0x06898020, 0x0689E960),
            207: (0x021B2F80, 0x021BB700),
            255: (0x021BB700, 0x021D96E0),
            265: (0x021998C0, 0x0219BAE0),
            299: (0x0219FBC0, 0x021A2A00),
            302: (0x021ACEE0, 0x021AE5E0),
        }[overlay]
        if not bounds[0] <= address < bounds[1]:
            raise SystemExit(
                f"hook {match.group(0)} is outside clean IREO overlay {overlay}: "
                f"0x{bounds[0]:08X}-0x{bounds[1]:08X}"
            )

    print(f"verified Black2Upgrade ELF: {args.elf}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
