#!/usr/bin/env python3
"""Check tracked/publishable files, submodules and decompressed ZIP/JAR members.

Usage: python3 tools/check_source_privacy.py [--forbid TOKEN ...]
The current account name is checked without embedding it in repository files.
Git internals and ignored local build outputs are deliberately outside scope.
Standard system interpreter shebangs and web URLs are not private host paths.
"""
from __future__ import annotations

import argparse
from io import BytesIO
from pathlib import Path
import re
import subprocess
import zipfile

from sanitize_private_artifacts import class_parts

ROOT = Path(__file__).resolve().parents[1]
HOST_PATH = re.compile(
    rb"(?<![.\w:/\\%])(?:/(?:[a-z]/)?(?:Users|home)/[\w.-]+/|/var/folders/[\w.-]+/|"
    rb"/private/var/[\w.-]+/|/Volumes/[\w .-]+/|[A-Za-z]:[\\/][\w .-]+)"
)
ARCHIVES = {".zip", ".jar", ".whl", ".docx", ".xlsx", ".pptx"}


def publishable_files(root: Path):
    names = subprocess.check_output(["git", "-C", str(root), "ls-files", "-z", "--cached", "--others", "--exclude-standard"])
    for name in sorted(set(names.decode().strip("\0").split("\0"))):
        if not name: continue
        path = root / name
        if path.is_dir() and (path / ".git").exists():
            yield from publishable_files(path)
        elif path.is_file():
            yield path


def check_content(data: bytes, tokens: list[str], *, binary: bool = False) -> list[str]:
    failures = []
    lower = data.lower()
    for token in tokens:
        if any(token.encode(encoding).lower() in lower for encoding in ("utf-8", "utf-16le", "utf-16be")):
            failures.append("private token")
    # Raw binary data can coincidentally resemble a drive path. Fixed host
    # roots remain searchable; executable class strings are checked separately.
    if binary:
        if any(root in data for root in (b"/Users/", b"/home/", b"/var/folders/", b"/private/var/")):
            failures.append("absolute host path")
    elif HOST_PATH.search(data):
        failures.append("absolute host path")
    return sorted(set(failures))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--forbid", action="append", default=[])
    args = parser.parse_args()
    account = Path.home().name
    tokens = [account] if account not in ("root", "runner", "user") else []
    tokens += args.forbid
    if any(not token for token in tokens): raise ValueError("Empty private token")
    failures, files, members = [], 0, 0
    for path in publishable_files(ROOT):
        files += 1
        label = path.relative_to(ROOT).as_posix()
        data = path.read_bytes()
        for failure in check_content(label.encode(), tokens): failures.append((label, failure))
        for failure in check_content(data, tokens, binary=b"\0" in data): failures.append((label, failure))
        if path.suffix.lower() not in ARCHIVES: continue
        with zipfile.ZipFile(BytesIO(data)) as archive:
            if archive.testzip() is not None: raise ValueError("Corrupt archive")
            for entry in archive.infolist():
                if entry.is_dir(): continue
                members += 1
                content = archive.read(entry)
                locations = [entry.filename.encode(), content]
                if entry.filename.endswith(".class"):
                    pool, _ = class_parts(content)
                    locations += [value for record in pool if record is not None for tag, value in [record] if tag == 1]
                for index, value in enumerate(locations):
                    binary = index == 1 and b"\0" in value
                    for failure in check_content(value, tokens, binary=binary):
                        failures.append((label + " :: " + entry.filename, failure))
    for label, failure in sorted(set(failures)): print("FAIL", label, failure)
    print(f"Checked {files} publishable files and {members} archive members; {len(set(failures))} violations.")
    return 1 if failures else 0


if __name__ == "__main__": raise SystemExit(main())
