#!/usr/bin/env python3
"""Wrap the real veils module with a diagnostic all-group registration sweep.

The output belongs only in a private native-test ROM, never the release VFS.
The original API, handler tables and effects remain intact.
"""
import argparse
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build", type=Path, default=ROOT / "build-release")
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    output = args.out.resolve()
    output.mkdir(parents=True, exist_ok=False)
    registry = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
    modules = sorted(registry["modules"], key=lambda group: group["id"])
    if modules[0]["name"] != "abilities/veils" or len(modules) != 30:
        raise RuntimeError("Unexpected stress-fixture registry contract")
    primary = {"ability": "W2U_MECHANIC_ABILITY", "move": "W2U_MECHANIC_MOVE", "item": "W2U_MECHANIC_ITEM"}
    calls = []
    for module in modules[1:]:
        kind, identifier, *_ = next(entry for entry in module["entries"] if entry[0] in primary)
        calls.append(f"    W2U_BattleModules_Resolve({primary[kind]}, {identifier});")
    source = output / "stress.cpp"
    source.write_text('''#include "w2u_battle_module_loader.h"
#include "w2u_abilities.h"
#include "Moves.h"
#include "Items.h"
extern "C" const W2UBattleModuleApi* W2U_StressOriginalApi();
extern "C" __attribute__((visibility("default"))) const W2UBattleModuleApi* W2U_GetBattleModuleApi() {
''' + "\n".join(calls) + '''
    return W2U_StressOriginalApi();
}
''')
    original = args.build.resolve() / "src/w2u_battle_abilities_veils.elf"
    renamed, wrapper, combined = [output / name for name in ("veils.elf", "stress.elf", "combined.elf")]
    subprocess.run(["arm-none-eabi-objcopy", "--redefine-sym", "W2U_GetBattleModuleApi=W2U_StressOriginalApi",
                    str(original), str(renamed)], check=True)
    subprocess.run(["arm-none-eabi-g++", "-mthumb", "-march=armv5t", "-mlong-calls", "-r", "-Os", "-nostdinc++",
                    "-fno-exceptions", "-fno-rtti", "-fno-unwind-tables", "-fno-asynchronous-unwind-tables",
                    "-fvisibility=hidden", "-ffunction-sections", "-fdata-sections", "-I", str(ROOT / "include"),
                    "-I", str(ROOT / "include/swan"), "-o", str(wrapper), str(source)], check=True)
    subprocess.run(["arm-none-eabi-g++", "-r", "-nostdlib", "-o", str(combined), str(renamed), str(wrapper)], check=True)
    subprocess.run(["python3", str(ROOT / "tools/verify_rpm_imports.py"), str(combined), "--esdb",
                    str(ROOT / "pmc/IRDO.yml"), "--core", str(args.build.resolve() / "src/w2u_main.elf")], check=True)
    subprocess.run(["python3", str(ROOT / "tools/package_rpm_checked.py"), "--jar", str(ROOT / "tools/CTRMap/CTRMapV-dirty.jar"),
                    "--output", str(output / "veils-stress.dll"), "--", "-i", str(combined), "--fourcc", "DLXF",
                    "--esdb", str(ROOT / "pmc/IRDO.yml"), "--generate-relocations", "--strip"], check=True)
    subprocess.run(["python3", str(ROOT / "tools/restrict_w2u_battle_exports.py"), str(output / "veils-stress.dll")], check=True)
    subprocess.run(["python3", str(ROOT / "tools/rpm_verify_stripped.py"), str(output / "veils-stress.dll")], check=True)
    (output / "receipt.json").write_text(json.dumps({"format":"w2-loader-stress-1", "synthetic":True,
        "groups":len(modules), "preservesOriginalApiAndHandlers":True, "productionPackagingAllowed":False},indent=2)+"\n")


if __name__ == "__main__":
    main()
