"""Target-compiler ID checks and exact registry packaging contracts."""
import copy
import importlib.util
import json
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location("registry", ROOT / "tools/generate_w2u_battle_registry.py")
generator = importlib.util.module_from_spec(spec)
spec.loader.exec_module(generator)


class RegistryValidation(unittest.TestCase):
    def test_distinct_enum_names_with_same_numeric_key_fail_compile(self):
        data = {"output_root": "lib/w2u_battle", "modules": [{"id": 0, "name": "moves/test",
            "entries": [["move", "FIRST", "One"], ["move", "ALIAS", "Two"]]}]}
        source = "using u8=unsigned char;using u16=unsigned short;using u32=unsigned;\n"
        source += "enum {W2U_MECHANIC_MOVE=1,FIRST=700,ALIAS=700};\n" + generator.render_cpp(data)
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run(["c++", "-std=c++11", "-x", "c++", "-c", "-o", str(Path(directory)/"out.o"), "-"],
                                    input=source, text=True, capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("duplicate case", result.stderr)

    def test_malformed_counts_and_priorities_are_rejected(self):
        data = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
        kind, identifier, _ = data["modules"][0]["entries"][0]
        for override in ({"handler_count": 65}, {"handler_count": True}, {"priority": True},
                         {"priority": "EVENTPRI_LOW); injected("}):
            variant = copy.deepcopy(data)
            variant["modules"][0].setdefault("entry_overrides", {})[f"{kind}:{identifier}"] = override
            with tempfile.TemporaryDirectory() as directory:
                path = Path(directory) / "registry.json"
                path.write_text(json.dumps(variant))
                with self.assertRaises(RuntimeError):
                    generator.load_registry(path)

    def test_staging_rejects_symlink_without_touching_outside(self):
        registry = ROOT / "src/pokeweb_gameplay/battle_modules/registry.json"
        data = generator.load_registry(registry)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            outside = root / "outside"
            outside.mkdir()
            sentinel = outside / "keep.dll"
            sentinel.write_bytes(b"user asset")
            stage = root / "w2u_battle"
            stage.symlink_to(outside, target_is_directory=True)
            rpm = root / "built.dll"
            rpm.write_bytes(b"DLXF")
            command = ["python3", str(ROOT / "tools/stage_w2u_battle_modules.py"),
                       "--registry", str(registry), "--stage-root", str(stage), "--stamp", str(root / "stamp")]
            for module in data["modules"]:
                command += ["--module", f"{module['id']}={rpm}"]
            result = subprocess.run(command, capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertEqual(sentinel.read_bytes(), b"user asset")
            self.assertFalse((root / "stamp").exists())


if __name__ == "__main__":
    unittest.main()
