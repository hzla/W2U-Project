#!/usr/bin/env python3
"""Normalize explicitly selected reports and bundled development archives.

Archive members retain their order, timestamps, comments, attributes and
compression method. ZIP compression framing may change. Animation bytes are untouched.
Java class edits touch only UTF-8 constant-pool path literals: pool indices,
non-string entries, method bytecode and attributes remain identical.
"""
from __future__ import annotations

import argparse
import copy
import json
import os
from pathlib import Path, PureWindowsPath
import re
import shutil
import struct
import tempfile
import zipfile

from pwan.report_paths import portable_report, write_report

WINDOWS_PATH = re.compile(r"(?<![\w])[A-Za-z]:[\\/][^\"\r\n\x00<>]+")
USER_PROJECT = re.compile(r"(?:[A-Za-z]:[\\/](?:Users|home)[\\/][^\\/]+|/(?:[a-z]/)?(?:Users|home)/[^/]+)/Pokeweb-Serverless(?:/Pokeweb-Serverless)?", re.I)
# The Windows variants use backslashes throughout rather than just the drive.
USER_PROJECT_WINDOWS = re.compile(r"[A-Za-z]:\\(?:Users|home)\\[^\\]+\\Pokeweb-Serverless(?:\\Pokeweb-Serverless)?", re.I)
TEXT_SUFFIXES = (".md", ".sh", ".cjs", ".js", ".ts", ".json", ".txt", ".py")


def class_parts(data: bytes) -> tuple[list[tuple[int, bytes] | None], bytes]:
    if len(data) < 10 or data[:4] != b"\xca\xfe\xba\xbe":
        raise ValueError("Invalid Java class")
    count, at, index = struct.unpack_from(">H", data, 8)[0], 10, 1
    entries: list[tuple[int, bytes] | None] = []
    widths = {3:4, 4:4, 5:8, 6:8, 7:2, 8:2, 9:4, 10:4, 11:4,
              12:4, 15:3, 16:2, 17:4, 18:4, 19:2, 20:2}
    while index < count:
        if at >= len(data): raise ValueError("Truncated constant pool")
        tag = data[at]; at += 1
        if tag == 1:
            if at + 2 > len(data): raise ValueError("Truncated UTF-8 length")
            size = struct.unpack_from(">H", data, at)[0]; at += 2
        elif tag in widths:
            size = widths[tag]
        else:
            raise ValueError("Unsupported constant-pool tag")
        if at + size > len(data): raise ValueError("Truncated constant-pool entry")
        entries.append((tag, data[at:at + size])); at += size
        index += 1
        if tag in (5, 6):
            entries.append(None); index += 1
    if index != count: raise ValueError("Invalid double-width constant")
    return entries, data[at:]


def sanitize_class(data: bytes) -> bytes:
    entries, tail = class_parts(data)
    output = bytearray(data[:10])
    for entry in entries:
        if entry is None: continue
        tag, value = entry
        if tag == 1 and re.search(rb"[A-Za-z]:[\\/]", value):
            text = value.decode("utf-8", errors="surrogatepass")
            def relative(match):
                raw = match.group()
                suffix = "/" if raw.endswith(("/", "\\")) else ""
                return PureWindowsPath(raw).name + suffix
            value = WINDOWS_PATH.sub(relative, text).encode("utf-8", errors="surrogatepass")
        output.append(tag)
        if tag == 1:
            if len(value) > 65535: raise ValueError("Oversized UTF-8 constant")
            output += struct.pack(">H", len(value))
        output += value
    output += tail
    new_entries, new_tail = class_parts(output)
    if new_tail != tail or len(new_entries) != len(entries):
        raise ValueError("Java code/attributes or pool indices changed")
    for old, new in zip(entries, new_entries):
        if old != new and (old is None or old[0] != 1):
            raise ValueError("Non-string constant changed")
    return bytes(output)


def sanitize_animation_text(text: str) -> str:
    # Archived tools are run from the consumer's project root; dependencies
    # are resolved through Node rather than another developer's node_modules.
    text = re.sub(r'(?<=require\(")[^"\r\n]*[\\/]node_modules[\\/]pngjs(?="\))', "pngjs", text)
    text = USER_PROJECT_WINDOWS.sub(".", text)
    text = USER_PROJECT.sub(".", text)
    text = text.replace('.\\work\\moves-preview.nds', 'work/moves-preview.nds')
    text = text.replace('.\\White2Upgrade_gen9.nds', 'White2Upgrade_gen9.nds')
    text = text.replace('cd . || exit 1', 'cd "${POKEWEB_PROJECT_ROOT:-.}" || exit 1')
    text = text.replace('W=./work', 'W="${ANIMATION_WORK_DIR:-work}"')
    text = text.replace('W=../work', 'W="${ANIMATION_WORK_DIR:-work}"')
    text = text.replace('D=./work/$slug/reference', 'D="${ANIMATION_WORK_DIR:-work}/$slug/reference"')
    return text


def sanitize_archive(path: Path, apply: bool = False) -> list[str]:
    with zipfile.ZipFile(path) as source:
        infos = source.infolist()
        if len({i.filename for i in infos}) != len(infos):
            raise ValueError("Duplicate archive member names")
        if any(i.filename.startswith("META-INF/") and i.filename.upper().endswith((".SF", ".RSA", ".DSA", ".EC")) for i in infos):
            raise ValueError("Signed archives require a source rebuild")
        original = {i.filename: source.read(i) for i in infos}
        replacements = dict(original)
        for info in infos:
            content = original[info.filename]
            if info.filename.endswith(".class"):
                replacements[info.filename] = sanitize_class(content)
            elif info.filename.lower().endswith(TEXT_SUFFIXES):
                replacements[info.filename] = sanitize_animation_text(content.decode("utf-8")).encode("utf-8")
        changed = [name for name in original if original[name] != replacements[name]]
        if not apply or not changed: return changed
        comment = source.comment
    fd, temporary = tempfile.mkstemp(prefix=".privacy-", suffix=".tmp", dir=path.parent)
    os.close(fd)
    temporary = Path(temporary)
    try:
        with zipfile.ZipFile(temporary, "w") as output:
            output.comment = comment
            for info in infos:
                written = copy.copy(info)
                output.writestr(written, replacements[info.filename])
                # zipfile supplies default UNIX permissions when the original
                # attribute word is zero (common for Windows-created ZIPs).
                # Restore that word before it writes the central directory.
                written.external_attr = info.external_attr
        with zipfile.ZipFile(temporary) as output:
            if output.testzip() is not None or output.namelist() != [i.filename for i in infos]:
                raise ValueError("Repacked archive failed integrity check")
            for info in infos:
                if output.read(info.filename) != replacements[info.filename]:
                    raise ValueError("Unexpected archive payload change")
        temporary.chmod(path.stat().st_mode)
        temporary.replace(path)
    finally:
        temporary.unlink(missing_ok=True)
    return changed


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--report", type=Path, action="append", default=[])
    parser.add_argument("--archive", type=Path, action="append", default=[])
    parser.add_argument("--apply", action="store_true", help="Otherwise preview changes only")
    parser.add_argument("--backup-dir", type=Path, help="Optional private, external backup location")
    args = parser.parse_args()
    for path in args.report + args.archive:
        if args.apply and args.backup_dir:
            args.backup_dir.mkdir(parents=True, exist_ok=True)
            target = args.backup_dir / path.name
            if target.exists(): raise ValueError("Backup target already exists")
            shutil.copy2(path, target)
        if path in args.report:
            original = json.loads(path.read_text())
            changed = portable_report(original) != original
            if changed and args.apply: write_report(path, original)
            print(path, "report changed" if changed else "unchanged")
        else:
            changed = sanitize_archive(path, args.apply)
            print(path, len(changed), "changed archive members")
            for name in changed: print(" ", name)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
