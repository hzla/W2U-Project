"""Portable dependency discovery for upgrade-owned behavioral tests."""
import json
import os
from pathlib import Path
import subprocess
import tempfile

TEST_ROOT = Path(__file__).resolve().parents[1]
ROOT = TEST_ROOT.parents[1]
POKEWEB_ROOT = Path(os.environ.get(
    "POKEWEB_ROOT", ROOT.parent / "Port-Pokeweb/Pokeweb-Serverless")).resolve()
DEFAULT_SAVE = POKEWEB_ROOT / "src/assets/testbattle/test.sav"
HEADLESS_ROOT = ROOT.parent / "Port-Pokeweb/work/scan-button"


def fixture_builder_command(filename):
    """Only fixture construction needs the external ROM-authoring dependency."""
    script = TEST_ROOT / "scripts" / filename
    if script.parent != TEST_ROOT / "scripts" or not script.is_file():
        raise ValueError("Unknown fixture builder")
    runner = POKEWEB_ROOT / "node_modules/.bin/vite-node"
    if not runner.is_file() or not (POKEWEB_ROOT / "src/pokeweb/battleHarness.ts").is_file():
        raise RuntimeError("Fixture building requires a Pokeweb checkout with npm ci; set POKEWEB_ROOT")
    return [str(runner), "--config", str(TEST_ROOT / "vite.config.mjs"), str(script)]


def typecheck():
    """Generate only relative config paths, including for a dependency override."""
    compiler = POKEWEB_ROOT / "node_modules/typescript/bin/tsc"
    if not compiler.is_file():
        raise RuntimeError("Type checking requires Pokeweb's npm ci; set POKEWEB_ROOT")
    work = ROOT / "work/battle-tests"
    work.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="typecheck-", dir=work) as temporary:
        directory = Path(temporary)
        relative = lambda path: os.path.relpath(path, directory)
        config = {
            "extends": relative(TEST_ROOT / "tsconfig.json"),
            "compilerOptions": {
                "baseUrl": ".",
                "paths": {"@pokeweb/*": [relative(POKEWEB_ROOT / "src") + "/*"]},
                "typeRoots": [relative(POKEWEB_ROOT / "node_modules/@types")],
            },
            "include": [relative(TEST_ROOT / "scripts") + "/**/*.ts",
                        relative(POKEWEB_ROOT / "src/vite-env.d.ts")],
        }
        config_path = directory / "tsconfig.json"
        config_path.write_text(json.dumps(config, indent=2) + "\n")
        return subprocess.run(["node", str(compiler), "--project", str(config_path)], cwd=ROOT).returncode
