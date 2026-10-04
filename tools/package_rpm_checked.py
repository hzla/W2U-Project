#!/usr/bin/env python3
"""Fail closed when RPMTool reports an error but exits successfully."""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile

from audit_white2upgrade_battle_heap import rpm_sizes


# Compiler support routines the game does not provide: RPMTool leaves them unresolved without an error, and the
# module then branches into nothing (e.g. a Thumb switch table's __gnu_thumb1_case_uqi hung the boot).
MISSING_RUNTIME_HELPERS = ("__gnu_thumb1_case_",)


def check_runtime_helpers(options: list[str]) -> None:
    inputs = [options[i + 1] for i, option in enumerate(options[:-1]) if option in ("-i", "--input")]
    for path in inputs:
        if not path.endswith(".elf"):
            continue
        undefined = subprocess.run(["arm-none-eabi-nm", "-u", path], check=True, capture_output=True, text=True).stdout
        bad = sorted({line.split()[-1] for line in undefined.splitlines()
                      if line.split() and line.split()[-1].startswith(MISSING_RUNTIME_HELPERS)})
        if bad:
            raise RuntimeError(f"{path}: needs runtime helpers the game lacks: {', '.join(bad)} "
                               "(add __attribute__((optimize(\"no-jump-tables\"))) or avoid the construct)")


def package(jar: Path, output: Path, options: list[str]) -> None:
    if any(option in ("-o", "--output") for option in options):
        raise ValueError("Output is owned by the checked packager")
    check_runtime_helpers(options)
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(prefix=output.name + ".", suffix=".tmp", dir=output.parent, delete=False) as file:
        temporary = Path(file.name)
    try:
        subprocess.run([os.environ.get("JAVA", "java"), "-cp", str(jar),
                        "rpm.cli.RPMTool", *options, "-o", str(temporary)], check=True)
        # The temporary starts empty: an exit-zero parser error cannot validate
        # yesterday's artifact. Keep the previous output intact until success.
        rpm_sizes(temporary)
        temporary.replace(output)
    finally:
        temporary.unlink(missing_ok=True)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--jar", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("options", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    options = args.options[1:] if args.options[:1] == ["--"] else args.options
    package(args.jar, args.output, options)


if __name__ == "__main__":
    main()
