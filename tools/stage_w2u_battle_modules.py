#!/usr/bin/env python3
"""Stage the exact White 2 on-demand battle module registry into the VFS."""

from __future__ import annotations

import argparse
import json
import shutil
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--registry", type=Path, required=True)
    parser.add_argument("--stage-root", type=Path, required=True)
    parser.add_argument("--stamp", type=Path, required=True)
    parser.add_argument("--module", action="append", default=[])
    args = parser.parse_args()

    registry = json.loads(args.registry.read_text())
    modules = registry["modules"]
    expected_ids = {int(module["id"]) for module in modules}
    provided: dict[int, Path] = {}
    for value in args.module:
        module_id_text, separator, path_text = value.partition("=")
        if not separator:
            raise RuntimeError(f"invalid --module value: {value!r}")
        module_id = int(module_id_text)
        if module_id in provided:
            raise RuntimeError(f"duplicate module input ID {module_id}")
        provided[module_id] = Path(path_text)
    if set(provided) != expected_ids:
        raise RuntimeError(
            f"module inputs mismatch: expected {sorted(expected_ids)}, "
            f"got {sorted(provided)}"
        )

    args.stage_root.mkdir(parents=True, exist_ok=True)
    expected_paths: set[Path] = set()
    for module in modules:
        relative = Path(module["name"] + ".dll")
        if relative.is_absolute() or ".." in relative.parts:
            raise RuntimeError(f"unsafe registry path: {relative}")
        output = args.stage_root / relative
        expected_paths.add(output.resolve())
        output.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(provided[int(module["id"])], output)

    for existing in args.stage_root.rglob("*.dll"):
        if existing.resolve() not in expected_paths:
            existing.unlink()

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
