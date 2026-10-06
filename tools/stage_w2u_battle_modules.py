#!/usr/bin/env python3
"""Stage the exact White 2 on-demand battle module registry into the VFS."""

from __future__ import annotations

import argparse
import json
import shutil
from pathlib import Path
from generate_w2u_battle_registry import load_registry


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--registry", type=Path, required=True)
    parser.add_argument("--stage-root", type=Path, required=True)
    parser.add_argument("--stamp", type=Path, required=True)
    parser.add_argument("--module", action="append", default=[])
    args = parser.parse_args()

    registry = load_registry(args.registry)
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

    # Cleanup is authorized only inside this exact module directory. Reject
    # symlinked destination components before copying or removing anything.
    if args.stage_root.name != "w2u_battle" or any(part.is_symlink() for part in (args.stage_root, *args.stage_root.parents)):
        raise RuntimeError("stage root must be a non-symlink w2u_battle directory")
    for source in provided.values():
        if not source.is_file() or source.read_bytes()[:4] != b"DLXF":
            raise RuntimeError(f"missing or invalid built RPM: {source}")
    for module in modules:
        output = args.stage_root / (module["name"] + ".dll")
        if output.is_symlink() or output.parent.is_symlink():
            raise RuntimeError(f"symlinked staging destination: {output}")
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

    staged = {path.resolve() for path in args.stage_root.rglob("*.dll")}
    if staged != expected_paths:
        raise RuntimeError("staged DLL set does not exactly match registry")
    for module in modules:
        output = args.stage_root / (module["name"] + ".dll")
        if output.read_bytes() != provided[int(module["id"])].read_bytes():
            raise RuntimeError(f"staged RPM differs from build: {output}")

    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
