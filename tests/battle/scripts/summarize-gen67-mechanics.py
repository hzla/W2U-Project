"""Recheck and combine same-ROM native audit batches; never turn omissions green."""
import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SCRIPTS = Path(__file__).resolve().parent


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, SCRIPTS / filename)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def identity(variant, case):
    return variant["mechanic"]["kind"], variant["name"], case["id"]


def semantic_variant(variant):
    # Ignore only harness placement/trainer numbering and accessor offsets.
    # The save's authored party and every gameplay identity remain pinned.
    keys = ("mechanic", "player", "allyPlayer", "benchPlayer", "moveId", "category", "power", "type",
            "playerSpecies", "playerAbilityId", "playerForm", "defenderSpecies", "abilityId",
            "defenderForm", "trainerMove", "trainerBagItems", "defenderItemId", "battleType", "bench", "benchMove", "incomingSpecies",
            "incomingAttackerSpecies", "allySpecies", "allyAbilityId", "allyMoves", "allyLevel",
            "defenderAllySpecies", "defenderAllyAbilityId", "defenderAllyMove", "defenderAllyItemId")
    return {key:variant.get(key) for key in keys}


def summarize(runs, verify):
    loaded, catalogs, hashes = [], {}, set()
    for directory in runs:
        report = json.loads((directory / "result.json").read_text())
        manifest = json.loads((directory / "fixtures/suite.json").read_text())
        if manifest["move"] not in ("gen67-abilities", "gen67-items"):
            raise ValueError("Not an ability/item audit")
        if report.get("error") or report.get("cleanupError"):
            raise ValueError("A fatal/incomplete run cannot certify an audit")
        hashes.add(report["inputRomSha256"])
        catalogs[manifest["move"]] = manifest  # Explicit later receipts replace earlier definitions.
        loaded.append((directory, report, manifest))
    if len(hashes) != 1:
        raise ValueError("Cannot combine different source ROMs")
    entries = [(v,c) for m in catalogs.values() for v in m["variants"] for c in v["cases"]]
    expected = {identity(v,c):(v,c) for v,c in entries}
    if not expected or len(expected) != len(entries):
        raise ValueError("Empty or duplicate scenario catalog")
    observations = {}
    for directory, report, manifest in loaded:
        for variant in manifest["variants"]:
            if variant["name"] not in report["selectedVariants"]:
                continue
            batch = json.loads((directory / "trials" / f"{variant['name']}-batch.json").read_text())
            if not batch.get("snapshotReleased") or batch.get("error"):
                raise ValueError("Native batch did not release its snapshot")
            for case in variant["cases"]:
                key = identity(variant,case)
                current = expected.get(key)
                if current is None or case != current[1] or semantic_variant(variant) != semantic_variant(current[0]):
                    continue  # Superseded scenario, never count as current coverage.
                record_path = directory / "trials" / f"{variant['name']}-{case['id']}.json"
                record = json.loads(record_path.read_text())
                observations[key] = record_path, record
    cases = []
    for key, (variant, case) in expected.items():
        outcome = {"kind":key[0],"variant":key[1],"case":key[2],"mechanicId":variant["mechanic"]["id"],"passed":False}
        if key not in observations:
            outcome.update(missing=True,error="No matching current native scenario")
        else:
            path, record = observations[key]
            outcome["evidence"] = os.path.relpath(path, ROOT)
            try:
                verify(case,record,variant)
                outcome["passed"] = True
            except (AssertionError, KeyError) as error:
                outcome["error"] = str(error)
        cases.append(outcome)
    return {"format":"w2u-gen67-native-audit-1","inputRomSha256":next(iter(hashes)),
            "passed":all(c["passed"] for c in cases),"complete":all(not c.get("missing") for c in cases),
            "caseCount":len(cases),"passCount":sum(c["passed"] for c in cases),
            "failureCount":sum(not c["passed"] for c in cases),"cases":cases,
            "method":"Native battle evidence revalidated against current independent oracle; later matching receipts supersede earlier cases"}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run",type=Path,action="append",required=True,help="Completed run, in chronological order")
    parser.add_argument("--out",type=Path,required=True,help="New JSON file inside ignored work/")
    args=parser.parse_args()
    output=args.out.resolve()
    if not output.is_relative_to(ROOT/"work"):
        parser.error("--out must be inside this repository's ignored work directory")
    runner=load("summary_native_runner","test-move-handlers.py")
    oracle=load("summary_native_oracle","gen67_mechanic_oracles.py")
    result=summarize([p.resolve() for p in args.run],lambda c,r,v:oracle.verify(c,r,v,vars(runner)))
    result["oracleSha256"]=hashlib.sha256((SCRIPTS/"gen67_mechanic_oracles.py").read_bytes()).hexdigest()
    output.parent.mkdir(parents=True,exist_ok=True)
    with output.open("x") as stream:stream.write(json.dumps(result,indent=2)+"\n")
    print(f"{result['passCount']}/{result['caseCount']} passed; complete={result['complete']}; report={os.path.relpath(output,ROOT)}")
    return 0 if result["passed"] else 1


if __name__ == "__main__":raise SystemExit(main())
