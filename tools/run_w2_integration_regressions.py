#!/usr/bin/env python3
"""Run the repository's native move suites with pinned ROM provenance."""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time
import uuid

ROOT = Path(__file__).resolve().parents[1]


def available_suites():
    help_text = subprocess.run([sys.executable, str(ROOT / "tools/test_battle.py"), "move", "--help"],
                               cwd=ROOT, check=True, text=True, capture_output=True).stdout
    choices = re.search(r"--move \{([^}]+)\}", help_text)
    if not choices:
        raise RuntimeError("Move runner did not advertise its suite contract")
    return choices.group(1).split(",")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, default=ROOT / "build/White2Upgrade.nds")
    parser.add_argument("--suites", nargs="+")
    parser.add_argument("--jobs", type=int, default=2)
    args = parser.parse_args()
    choices = available_suites()
    suites = args.suites or [s for s in choices if not s.startswith("gen67-")]
    if not 1 <= args.jobs <= 4 or len(suites) != len(set(suites)) or not set(suites) <= set(choices):
        parser.error("Use one to four workers and unique advertised suite names")
    rom = args.rom.resolve()
    digest = hashlib.sha256(rom.read_bytes()).hexdigest()
    output = ROOT / "work/integration-regressions" / (time.strftime("%Y%m%d-%H%M%S") + "-" + uuid.uuid4().hex[:6])
    output.mkdir(parents=True)
    frozen_rom = output / "input.nds"
    shutil.copyfile(rom, frozen_rom)
    report = {"format": "w2-integration-regressions-1", "inputRomSha256": digest,
              "selectedSuites": suites, "results": [], "passed": False}

    def run(suite):
        destination = output / suite
        with (output / f"{suite}.log").open("w") as log:
            command = [sys.executable, str(ROOT / "tools/test_battle.py"), "move",
                                     "--move", suite, "--rom", str(frozen_rom), "--out", str(destination),
                                     "--continue-on-failure", "--full-turn-smoke"]
            # This batch authors up to seven preceding actions per case;
            # retain emulated-frame bounds while allowing its actual work.
            if suite == "rage-fist":
                command += ["--trial-timeout", "1200"]
            result = subprocess.run(command,
                                    cwd=ROOT, stdout=log, stderr=subprocess.STDOUT)
        details = json.loads((destination / "result.json").read_text()) if (destination / "result.json").is_file() else {}
        # A rebuilt input between cases invalidates the batch, never silently
        # aggregates evidence from different binaries under one digest.
        provenance = details.get("inputRomSha256") == digest
        return {"suite": suite, "passed": result.returncode == 0 and details.get("passed", False) and provenance,
                "exitCode": result.returncode, "romProvenanceMatches": provenance,
                "report": str((destination / "result.json").relative_to(ROOT)),
                "completeSuite": details.get("completeSuite", False),
                "fullTurnValidated": details.get("fullTurnValidated", False)}

    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        for future in as_completed([pool.submit(run, suite) for suite in suites]):
            item = future.result()
            report["results"].append(item)
            (output / "result.json").write_text(json.dumps(report, indent=2) + "\n")
            print(f"{'PASS' if item['passed'] else 'FAIL'} {item['suite']}", flush=True)
    report["passed"] = all(item["passed"] for item in report["results"])
    (output / "result.json").write_text(json.dumps(report, indent=2) + "\n")
    print(f"Report: {output.relative_to(ROOT)}/result.json", flush=True)
    return 0 if report["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
