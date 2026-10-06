#!/usr/bin/env python3
"""Fail a PMC DLL build when its ELF imports a symbol nothing at run time resolves.

RPMTool turns an undefined symbol that is not in the ESDB into an import resolved by name when PMC loads the module;
when no loaded module exports it, the call is left as a branch to itself and the game hangs there. Every import must
be in an ESDB (--esdb) or, for a module loaded beside the resident core, be a global the core defines (--core: the
core RPM exports a hash for each of them, which the loader matches).
"""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path


def nm(*args: str) -> set[str]:
    output = subprocess.run(["arm-none-eabi-nm", *args], check=True, capture_output=True, text=True).stdout
    return {line.split()[-1] for line in output.splitlines() if line.split()}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    parser.add_argument("--esdb", type=Path, action="append", required=True)
    parser.add_argument("--core", type=Path, action="append", default=[])
    args = parser.parse_args()

    provided: set[str] = set()
    for esdb in args.esdb:
        provided.update(re.findall(r"^\s+- Name:\s+(\S+)\s*$", esdb.read_text(encoding="utf-8"), re.MULTILINE))
    for core in args.core:
        provided.update(nm("-g", "--defined-only", str(core)))

    unresolved = sorted(nm("-u", str(args.elf)) - provided)
    if unresolved:
        sources = ", ".join(path.name for path in args.esdb + args.core)
        lines = [f"[!] {args.elf.name} imports {len(unresolved)} symbol(s) not provided by {sources};",
                 "    RPMTool would leave each call branching to itself (a hang at run time):"]
        lines += [f"      {symbol}" for symbol in unresolved]
        lines.append("    Add the address to pmc/IRDO.yml, define the function in the module, or export it from the core.")
        if any(symbol.startswith("__aeabi_") for symbol in unresolved):
            lines.append("    __aeabi_* division helpers: use u64 division or a multiply (the ESDB only has the *divmod ones).")
        raise SystemExit("\n".join(lines))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
