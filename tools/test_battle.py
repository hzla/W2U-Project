#!/usr/bin/env python3
"""Run upgrade-owned headless move/ability/item regressions from the repository root."""
import argparse
import importlib.util
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
BATTLE_TESTS = ROOT / "tests/battle"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("suite", choices=("ability", "item", "move", "animation", "unit", "typecheck"))
    args = parser.parse_args(sys.argv[1:2])
    extra = sys.argv[2:]
    if args.suite == "unit":
        return subprocess.run([sys.executable, "-m", "unittest", "discover", "-s",
                               str(BATTLE_TESTS / "unit"), "-p", "test_*.py", *extra], cwd=ROOT).returncode
    if args.suite == "typecheck":
        if extra:
            parser.error("typecheck takes no extra arguments")
        spec = importlib.util.spec_from_file_location("harness_paths", BATTLE_TESTS / "scripts/harness_paths.py")
        paths = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(paths)
        return paths.typecheck()
    suite_index = extra.index("--suite") if "--suite" in extra else None
    gen67 = suite_index is not None and extra[suite_index + 1:suite_index + 2] == ["gen67"]
    if args.suite == "item" or (args.suite == "ability" and gen67):
        if "--suite" in extra:
            index = extra.index("--suite")
            if extra[index + 1:index + 2] != ["gen67"]:
                parser.error("the item suite currently supports --suite gen67 only")
            del extra[index:index + 2]
        if "--move" in extra:
            parser.error("ability/item selects --move internally; use --variant to filter")
        extra = ["--move", "gen67-items" if args.suite == "item" else "gen67-abilities", *extra]
        script = "test-move-handlers.py"
    else:
        script = {"ability": "test-battle-interactions.py", "move": "test-move-handlers.py",
                  "animation": "test-animation-completion.py"}[args.suite]
    # Preserve the caller's cwd for relative --rom/--save/--out arguments.
    return subprocess.run([sys.executable, str(BATTLE_TESTS / "scripts" / script), *extra]).returncode


if __name__ == "__main__":
    raise SystemExit(main())
