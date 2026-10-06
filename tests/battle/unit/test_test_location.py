"""Keep test ownership, dependency discovery and generated paths portable."""
import importlib.util
import json
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch

TEST_ROOT = Path(__file__).resolve().parents[1]
REPO = TEST_ROOT.parents[1]


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


paths = load("test_paths", TEST_ROOT / "scripts/harness_paths.py")
cli = load("test_cli", REPO / "tools/test_battle.py")


class TestLocation(unittest.TestCase):
    def test_runner_root_is_upgrade_repository(self):
        self.assertEqual(paths.ROOT, REPO)
        self.assertEqual(paths.TEST_ROOT, TEST_ROOT)
        self.assertTrue((paths.ROOT / "src/pokeweb_gameplay/w2u_moves.cpp").is_file())

    def test_missing_fixture_dependency_has_actionable_error(self):
        with tempfile.TemporaryDirectory() as directory, patch.object(paths, "POKEWEB_ROOT", Path(directory)):
            with self.assertRaisesRegex(RuntimeError, "npm ci; set POKEWEB_ROOT"):
                paths.fixture_builder_command("build-move-handler-fixtures.ts")

    def test_fixture_command_executes_upgrade_owned_source(self):
        with tempfile.TemporaryDirectory() as directory:
            dependency = Path(directory)
            (dependency / "node_modules/.bin").mkdir(parents=True)
            (dependency / "node_modules/.bin/vite-node").touch()
            (dependency / "src/pokeweb").mkdir(parents=True)
            (dependency / "src/pokeweb/battleHarness.ts").touch()
            with patch.object(paths, "POKEWEB_ROOT", dependency):
                command = paths.fixture_builder_command("build-move-handler-fixtures.ts")
                self.assertEqual(Path(command[-1]), TEST_ROOT / "scripts/build-move-handler-fixtures.ts")
                self.assertEqual(Path(command[2]), TEST_ROOT / "vite.config.mjs")
                self.assertEqual(Path(command[0]), dependency / "node_modules/.bin/vite-node")

    def test_fixture_command_rejects_traversal(self):
        for filename in ("../README.md", "missing.ts", str(REPO / "README.md")):
            with self.subTest(filename=Path(filename).name), self.assertRaises(ValueError):
                paths.fixture_builder_command(filename)

    def test_typecheck_config_contains_only_relative_paths_and_is_cleaned(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            dependency = root / "authoring"
            compiler = dependency / "node_modules/typescript/bin/tsc"
            compiler.parent.mkdir(parents=True)
            compiler.touch()
            captured = []

            def compile(command, **kwargs):
                config_path = Path(command[-1])
                config = json.loads(config_path.read_text())
                values = [config["extends"], *config["include"],
                          *config["compilerOptions"]["paths"]["@pokeweb/*"],
                          *config["compilerOptions"]["typeRoots"]]
                self.assertTrue(all(not Path(value).is_absolute() for value in values))
                captured.append(config_path)
                return SimpleNamespace(returncode=0)

            with patch.object(paths, "ROOT", root / "upgrade"), \
                 patch.object(paths, "POKEWEB_ROOT", dependency), \
                 patch.object(paths.subprocess, "run", side_effect=compile):
                self.assertEqual(paths.typecheck(), 0)
            self.assertEqual(len(captured), 1)
            self.assertFalse(captured[0].exists())

    def test_cli_forwards_suite_help_and_exit_status(self):
        with patch.object(cli.sys, "argv", ["test_battle.py", "move", "--help"]), \
             patch.object(cli.subprocess, "run", return_value=SimpleNamespace(returncode=7)) as run:
            self.assertEqual(cli.main(), 7)
            self.assertEqual(run.call_args.args[0][-1], "--help")
            self.assertEqual(Path(run.call_args.args[0][1]), TEST_ROOT / "scripts/test-move-handlers.py")

    def test_cli_preserves_callers_relative_input_paths(self):
        with patch.object(cli.sys, "argv", ["test_battle.py", "ability", "--rom", "fixtures/game.nds"]), \
             patch.object(cli.subprocess, "run", return_value=SimpleNamespace(returncode=0)) as run:
            self.assertEqual(cli.main(), 0)
            self.assertEqual(run.call_args.args[0][-2:], ["--rom", "fixtures/game.nds"])
            self.assertNotIn("cwd", run.call_args.kwargs)


if __name__ == "__main__":
    unittest.main()
