"""Prevent silently omitted resident battle hooks in RPM packaging."""
import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location(
    "linkage", Path(__file__).resolve().parents[1] / "verify_w2u_battle_linkage.py")
linkage = importlib.util.module_from_spec(spec)
spec.loader.exec_module(linkage)


class HookOwners(unittest.TestCase):
    def test_named_callsite_requires_owner(self):
        with self.assertRaisesRegex(RuntimeError, "missing ESDB hook owner DamageRoot"):
            linkage.verify_hook_targets({"THUMB_BRANCH_LINK_DamageRoot_0x36"}, set())

    def test_replacement_and_safestack_require_owners(self):
        for name in ("THUMB_BRANCH_Damage", "THUMB_BRANCH_SAFESTACK_Damage"):
            with self.subTest(name=name), self.assertRaisesRegex(RuntimeError, "missing ESDB"):
                linkage.verify_hook_targets({name}, set())

    def test_valid_named_hooks(self):
        linkage.verify_hook_targets({"THUMB_BRANCH_LINK_Damage_0x36", "THUMB_BRANCH_SAFESTACK_Damage"}, {"Damage"})

    def test_numeric_overlay_and_ordinary_exports(self):
        linkage.verify_hook_targets({"THUMB_BRANCH_LINK_167_0x21A4436", "FULL_COPY_167_0x21A4436", "W2U_Service"}, set())


if __name__ == "__main__":
    unittest.main()
