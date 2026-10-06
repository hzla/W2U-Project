"""Reject RPM short branches that wrap between main RAM and VRAM."""
from pathlib import Path
import importlib.util
import subprocess
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location("battle_linkage", ROOT / "tools/verify_w2u_battle_linkage.py")
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)


class VramCalls(unittest.TestCase):
    def test_relative_vram_calls_rejected_absolute_and_main_ram_allowed(self):
        addresses = {"VramFunction": 0x06898C11, "MainFunction": 0x021A0001}
        for kind in ("THM_CALL", "THM_JUMP24", "CALL", "JUMP24"):
            with patch.object(MODULE.subprocess, "run", return_value=subprocess.CompletedProcess([],0,f"0000 R_ARM_{kind} VramFunction+0x4\n","")):
                with self.assertRaisesRegex(RuntimeError, "absolute long call"):
                    MODULE.verify_vram_branch_relocations(Path("example.elf"), addresses)
        with patch.object(MODULE.subprocess, "run", return_value=subprocess.CompletedProcess([],0,
                "0000 R_ARM_ABS32 VramFunction\n0004 R_ARM_THM_CALL MainFunction\n0008 R_ARM_THM_CALL W2U_Service\n", "")):
            MODULE.verify_vram_branch_relocations(Path("example.elf"), addresses)


if __name__ == "__main__":
    unittest.main()
