#!/usr/bin/env python3
"""Keep the Black 2 build from silently changing White2Upgrade modules."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--expected", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("artifacts", nargs="+", type=Path)
    args = parser.parse_args()

    expected = json.loads(args.expected.read_text(encoding="utf-8"))["artifacts"]
    actual = {path.name: hashlib.sha256(path.read_bytes()).hexdigest() for path in args.artifacts}
    missing = sorted(set(expected) - set(actual))
    mismatches = sorted(name for name, digest in actual.items() if expected.get(name) != digest)
    if missing or mismatches:
        raise SystemExit(
            "White2Upgrade binary guard failed"
            + (f"; missing: {', '.join(missing)}" if missing else "")
            + (f"; changed: {', '.join(mismatches)}" if mismatches else "")
        )
    report = {"schemaVersion": 1, "passed": True, "artifacts": actual}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print("White2Upgrade binary guard passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
