#!/usr/bin/env python3
"""Reconcile complete native suites and explicit retries without hiding failures."""
import argparse
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def reconcile(batches, root=ROOT):
    selected, resolved, history = [], {}, []
    for index, batch in enumerate(batches):
        if index == 0:
            selected = batch["selectedSuites"]
            if not selected or len(selected) != len(set(selected)):
                raise ValueError("The primary batch must declare unique required suites")
        for row in batch["results"]:
            suite = row["suite"]
            if suite not in selected:
                raise ValueError("A retry introduced a suite outside the primary batch")
            path = (root / row["report"]).resolve()
            if not path.is_relative_to(root.resolve()):
                raise ValueError("Evidence path escaped the repository")
            details = json.loads(path.read_text())
            passed = (row["exitCode"] == 0 and row.get("passed") is True and
                      details.get("passed") is True and details.get("completeSuite") is True and
                      details.get("inputRomSha256") == batch["inputRomSha256"] and
                      bool(details.get("cases")) and all(case.get("passed") is True for case in details["cases"]))
            item = {"suite": suite, "passed": passed, "report": row["report"],
                    "input_rom_sha256": details.get("inputRomSha256"),
                    "case_count": len(details.get("cases", [])),
                    "full_turn_validated": details.get("fullTurnValidated", False)}
            history.append(item)
            # A later incomplete/failed retry cannot retain an earlier green.
            resolved[suite] = item
    missing = [suite for suite in selected if suite not in resolved]
    failed = [suite for suite in selected if suite in resolved and not resolved[suite]["passed"]]
    return {"format": "w2-integration-native-suite-summary-1",
            "passed": not missing and not failed, "required_suite_count": len(selected),
            "missing_suites": missing, "failed_suites": failed,
            "accepted_case_count": sum(item["case_count"] for item in resolved.values() if item["passed"]),
            "accepted_rom_sha256s": sorted({item["input_rom_sha256"] for item in resolved.values() if item["passed"]}),
            "suites": [resolved[suite] for suite in selected if suite in resolved],
            "failed_or_incomplete_attempts": [item for item in history if not item["passed"]],
            "note": "Multi-revision evidence is explicit; this summary does not claim that every suite was rerun on the final ROM or certify all move interactions."}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--batch", type=Path, action="append", required=True, help="Primary batch first, complete retries in chronological order")
    args = parser.parse_args()
    result = reconcile([json.loads(path.read_text()) for path in args.batch])
    print(json.dumps(result, indent=2))
    return 0 if result["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
