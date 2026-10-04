"""CPU checks for the resident native-Transform success-tail adapter."""
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R4, UC_ARM_REG_R7, UC_ARM_REG_LR

ROOT = Path(__file__).resolve().parents[2]


class TransformSpeciesHook(unittest.TestCase):
    def test_success_tail_preserves_flag_and_copies_species_only(self):
        with tempfile.TemporaryDirectory(prefix="w2u-transform-cpu-") as directory:
            obj, binary = Path(directory) / "hook.o", Path(directory) / "hook.bin"
            subprocess.run(["arm-none-eabi-as", "-march=armv5t", "-mthumb", "-o", str(obj),
                            str(ROOT / "src/pokeweb_gameplay/w2u_transform_hooks.s")], check=True)
            subprocess.run(["arm-none-eabi-objcopy", "-O", "binary", "-j", ".text", str(obj), str(binary)], check=True)
            code = binary.read_bytes()
            self.assertEqual(len(code), 12)
            for species, flags in ((877, 0x80), (151, 0x82), (493, 0)):
                with self.subTest(species=species, flags=flags):
                    emu = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
                    emu.mem_map(0x02000000, 0x4000)
                    emu.mem_write(0x02000000, code)
                    user, target, ret = 0x02001000, 0x02002000, 0x02003000
                    before = bytearray([0x5a] * 0x1f8)
                    before[27] = flags
                    emu.mem_write(user, bytes(before))
                    emu.mem_write(target + 12, struct.pack("<H", species))
                    for register, value in ((UC_ARM_REG_R0, 0x20), (UC_ARM_REG_R1, flags),
                        (UC_ARM_REG_R4, user), (UC_ARM_REG_R7, target), (UC_ARM_REG_LR, ret | 1)):
                        emu.reg_write(register, value)
                    emu.emu_start(0x02000001, ret, count=8)
                    expected = bytearray(before)
                    expected[27] |= 0x20
                    struct.pack_into("<H", expected, 0xec, species)
                    self.assertEqual(bytes(emu.mem_read(user, len(expected))), bytes(expected))
                    self.assertEqual(emu.reg_read(UC_ARM_REG_R4), user)
                    self.assertEqual(emu.reg_read(UC_ARM_REG_R7), target)
                    self.assertEqual(emu.reg_read(UC_ARM_REG_LR), ret | 1)

    def test_b2_translation_uses_reviewed_success_site(self):
        with tempfile.TemporaryDirectory(prefix="w2u-transform-b2-") as directory:
            output = Path(directory) / "hook.s"
            subprocess.run(["python3", str(ROOT / "tools/generate_black2upgrade_asm.py"),
                "--input", str(ROOT / "src/pokeweb_gameplay/w2u_transform_hooks.s"),
                "--output", str(output), "--aliases", str(ROOT / "pmc/black2upgrade_aliases.json")], check=True)
            source = output.read_text()
            self.assertIn("THUMB_BRANCH_LINK_167_0x21BC532", source)
            self.assertNotIn("0x21BC572", source)


if __name__ == "__main__":
    unittest.main()
