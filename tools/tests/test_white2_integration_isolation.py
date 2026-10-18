"""White 2 ports must not silently alter Black 2's frozen runtime sources."""
from pathlib import Path
import subprocess
import unittest

ROOT = Path(__file__).resolve().parents[2]
BASE = "4369e8a4738ea435a350eff4e9c527d523bd8c31"


class IntegrationIsolation(unittest.TestCase):
    def test_frozen_black2_sources_match_pinned_base(self):
        for name in ("w2u_moves.cpp", "w2u_abilities.cpp", "w2u_mega.cpp",
                     "w2u_move_animation_hooks.s", "w2u_transform_hooks.s", "w2u_damage_hooks.s"):
            with self.subTest(name=name):
                expected = subprocess.run(["git", "show", BASE + ":src/pokeweb_gameplay/" + name],
                                          cwd=ROOT, check=True, capture_output=True, text=True).stdout
                if name.endswith(".cpp"):
                    expected = expected.replace('#include "w2u_battle_module_api_entries.inc"',
                                                '#include "../w2u_battle_module_api_entries.inc"')
                    frozen = name + ".inc"
                else:
                    frozen = name
                self.assertEqual((ROOT / "src/pokeweb_gameplay/b2_baseline" / frozen).read_text(), expected)

    @staticmethod
    def registries():
        import json
        data = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
        original = json.loads(subprocess.run(
            ["git", "show", BASE + ":src/pokeweb_gameplay/battle_modules/registry.json"],
            cwd=ROOT, check=True, capture_output=True, text=True).stdout)
        return data, original

    @staticmethod
    def canonical(kind, name):
        """An entry's key with enum aliases resolved (ABIL_QUEENLY_MAJESTY = ABIL_QUEENLY_MAGESTY): a rename to an
        alias routes the same ID, so it is not a new entry."""
        import re
        aliases = dict(re.findall(r"\b([A-Z][A-Z0-9_]+)\s*=\s*([A-Z][A-Z0-9_]+)\s*,",
                                  (ROOT / "include/w2u_abilities.h").read_text()))
        while name in aliases:
            name = aliases[name]
        return kind, name

    @staticmethod
    def white2_only(module, entry):
        return bool(module.get("white2_only") or
                    module.get("entry_overrides", {}).get(":".join(entry[:2]), {}).get("white2_only"))

    def test_white2_new_moves_never_enter_black2_api(self):
        data, original = self.registries()
        keys = {self.canonical(*entry[:2]) for module in original["modules"] for entry in module["entries"]}
        added = [(module, entry) for module in data["modules"] for entry in module["entries"]
                 if self.canonical(*entry[:2]) not in keys]
        self.assertEqual(sum(entry[0] == "move" for _, entry in added), 52)
        for module, entry in added:
            with self.subTest(entry=entry[:2]):
                self.assertTrue(self.white2_only(module, entry))

    def test_white2_only_mechanics_stay_out_of_black2_api(self):
        """A mechanic Black 2 never had (White 2-only at the base) stays White 2-only when it moves to another module:
        moving Armor Tail into a shared module once gave Black 2 a route to it."""
        data, original = self.registries()
        shared = {self.canonical(*entry[:2]) for module in original["modules"] for entry in module["entries"]
                  if not self.white2_only(module, entry)}
        for module in data["modules"]:
            for entry in module["entries"]:
                key = self.canonical(*entry[:2])
                if key not in shared:
                    with self.subTest(module=module["name"], entry=entry[:2]):
                        self.assertTrue(self.white2_only(module, entry))

    def test_black2_address_checks_ignore_comments_only(self):
        import tempfile
        with tempfile.TemporaryDirectory(prefix="w2u-b2-comments-") as directory:
            source, output = Path(directory) / "hook.s", Path(directory) / "out.s"
            command = ["python3", str(ROOT / "tools/generate_black2upgrade_asm.py"),
                       "--input", str(source), "--output", str(output),
                       "--aliases", str(ROOT / "pmc/black2upgrade_aliases.json")]
            source.write_text("@ diagnostic 0x02123456\nbx lr\n")
            subprocess.run(command, check=True)
            source.write_text("ldr r3, =0x02123456 @ executable address must fail\n")
            result = subprocess.run(command, capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("unreviewed", result.stderr)


if __name__ == "__main__":
    unittest.main()
