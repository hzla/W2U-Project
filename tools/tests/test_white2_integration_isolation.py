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

    def test_white2_new_moves_never_enter_black2_api(self):
        import json
        data = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
        original = json.loads(subprocess.run(
            ["git", "show", BASE + ":src/pokeweb_gameplay/battle_modules/registry.json"],
            cwd=ROOT, check=True, capture_output=True, text=True).stdout)
        keys = {(entry[0], entry[1]) for module in original["modules"] for entry in module["entries"]}
        added = [(module, entry) for module in data["modules"] for entry in module["entries"]
                 if (entry[0], entry[1]) not in keys]
        self.assertEqual(sum(entry[0] == "move" for _, entry in added), 52)
        for module, entry in added:
            self.assertTrue(module.get("white2_only") or
                            module.get("entry_overrides", {}).get(":".join(entry[:2]), {}).get("white2_only"))

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
