"""Serialize report paths relative to the repository, never the host checkout.

Runtime I/O still uses the original paths. Only persisted report values and
embedded path diagnostics are normalized. Cross-drive paths fail closed.
"""
from __future__ import annotations

import json
import os
from pathlib import Path, PureWindowsPath
import re

ROOT = Path(__file__).resolve().parents[2]
HOST_PATH = re.compile(
    r"(?<![.\w:/\\])(?:/(?:[a-z]/)?(?:Users|home|Volumes|private|tmp|var|opt|root|workspace|workspaces)/|[A-Za-z]:[\\/])"
    r"[^\"'\r\n<>\x00]+"
)


def report_path(path: str | Path, base: Path = ROOT) -> str:
    """Return a slash-normalized, repository-relative path for a report."""
    if os.name != "nt" and PureWindowsPath(path).is_absolute():
        raise ValueError("Report inputs must use the host filesystem or an explicit relative path")
    try:
        result = os.path.relpath(Path(path).resolve(), base.resolve())
    except ValueError:
        raise ValueError("Report inputs must share a filesystem root with the repository") from None
    return Path(result).as_posix()


def portable_report(value, base: Path = ROOT):
    if isinstance(value, Path):
        return report_path(value, base)
    if isinstance(value, dict):
        result = {}
        for key, item in value.items():
            key = portable_report(key, base)
            if key in result:
                raise ValueError("Report keys collide after path normalization")
            result[key] = portable_report(item, base)
        return result
    if isinstance(value, (list, tuple)):
        return [portable_report(item, base) for item in value]
    if isinstance(value, str):
        # Remove a known checkout prefix from diagnostics before generic
        # matching; this preserves spaces and surrounding error wording.
        value = value.replace(str(base.resolve()) + os.sep, "")
        if Path(value).is_absolute():
            return report_path(value, base)
        return HOST_PATH.sub(lambda match: report_path(match.group(), base), value)
    return value


def write_report(path: Path, value, *, sort_keys: bool = False) -> None:
    path.write_text(json.dumps(portable_report(value), indent=2, sort_keys=sort_keys) + "\n", encoding="utf-8")
