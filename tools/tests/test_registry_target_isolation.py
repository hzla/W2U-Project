"""Target restrictions must not leak W2-only entries into the B2 resolver."""
import copy
import importlib.util
import json
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location("registry", ROOT / "tools/generate_w2u_battle_registry.py")
registry = importlib.util.module_from_spec(spec)
spec.loader.exec_module(registry)


class RegistryTargetIsolation(unittest.TestCase):
    def setUp(self):
        self.data = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())

    def preprocess(self, text, b2=False):
        flags = ["-DW2U_BATTLE_STATIC_RESOLVER_BUILD", "-DW2U_BATTLE_STATIC_GROUPS", "-DW2U_BATTLE_API_SOURCE_ABILITIES"]
        if b2:
            flags.append("-DW2U_TARGET_B2")
        return subprocess.run(["c++", "-E", "-P", "-x", "c++", *flags, "-"], input=text,
                              text=True, check=True, capture_output=True).stdout

    def test_entry_restriction_filters_routes_and_api(self):
        module = self.data["modules"][0]
        kind, identifier, table = module["entries"][0]
        module.setdefault("entry_overrides", {})[f"{kind}:{identifier}"] = {"white2_only": True}
        for render in (registry.render_cpp, registry.render_api_cpp):
            text = render(self.data)
            self.assertIn(identifier, self.preprocess(text))
            self.assertNotIn(identifier, self.preprocess(text, b2=True))

    def test_group_restriction_cannot_be_weakened(self):
        module = copy.deepcopy(self.data["modules"][0])
        module["white2_only"] = True
        kind, identifier, _ = module["entries"][0]
        module["entry_overrides"] = {f"{kind}:{identifier}": {"white2_only": False}}
        self.assertTrue(registry.entry_config(self.data, module, kind, identifier)["white2_only"])

    def test_non_boolean_restrictions_fail(self):
        module = self.data["modules"][0]
        kind, identifier, _ = module["entries"][0]
        module["entry_overrides"] = {f"{kind}:{identifier}": {"white2_only": "yes"}}
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / "registry.json"
            path.write_text(json.dumps(self.data))
            with self.assertRaisesRegex(RuntimeError, "boolean"):
                registry.load_registry(path)


if __name__ == "__main__":
    unittest.main()
