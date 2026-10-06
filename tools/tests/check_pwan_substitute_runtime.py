#!/usr/bin/env python3
"""Exercise the compiled PWAN update/draw functions in an isolated ARM harness.

Usage: python3 tools/tests/check_pwan_substitute_runtime.py build/src/PokewebPwanBattleW2.elf
Requires Unicorn and the ARM toolchain. Game index lookup and archive reads are
stubbed; the production actor update, palette writes, and suspension run as ARM
machine code. This does not run the game or replace an in-game visual check.
"""

import argparse
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import (
    UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
    UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
)


def check(elf: Path, black2: bool, dsi: bool = False) -> None:
    with tempfile.TemporaryDirectory(prefix="pwan-substitute-") as temp:
        linked = Path(temp) / "runtime.elf"
        subprocess.run([
            "arm-none-eabi-ld", "--unresolved-symbols=ignore-all",
            "-Ttext=0x02300000", "-Tdata=0x02318000", "-Tbss=0x02320000",
            "--section-start=.rodata=0x02310000", "-e", "W2U_BattleAnim_Update",
            "--defsym=memset=0x023E0001",
            "--defsym=hw_isDSi=0x023E0020",
            "-o", str(linked), str(elf),
        ], check=True)
        data = linked.read_bytes()
        output = subprocess.check_output(["arm-none-eabi-nm", str(linked)], text=True)
        symbols = {fields[2]: int(fields[0], 16) for line in output.splitlines()
                   if len(fields := line.split()) == 3}

    cpu = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
    cpu.mem_map(0x02000000, 0x1000000)
    # Stub mode for this actor fixture; the packaged guard suite separately
    # executes the real cold/cached retail getter in both games.
    cpu.mem_write(0x023E0020, struct.pack("<II", 0xe3a00000 | int(dsi), 0xe12fff1e))
    section_offset = struct.unpack_from("<I", data, 0x20)[0]
    section_size, section_count = struct.unpack_from("<HH", data, 0x2E)
    for i in range(section_count):
        _, kind, flags, address, offset, size, *_ = struct.unpack_from(
            "<10I", data, section_offset + i * section_size)
        if flags & 2 and kind != 8 and size:
            cpu.mem_write(address, data[offset:offset + size])

    def write32(address, value):
        cpu.mem_write(address, struct.pack("<I", value))

    def read32(address):
        return struct.unpack("<I", cpu.mem_read(address, 4))[0]

    def read16(address):
        return struct.unpack("<H", cpu.mem_read(address, 2))[0]

    arena = 0x02800000 if dsi else 0x02200000
    bew, bmw, mcss = arena, arena + 0x1000, arena + 0x2000
    palette, faded = arena + 0x3000, arena + 0x3100
    # Position zero deliberately maps to MCSS index two, as in the report.
    entry = bmw + 8 + 2 * 0x5C
    write32(0x021F4240 if black2 else 0x021F4280, bew)
    write32(bew + 0x190, bmw)
    write32(entry, mcss)
    write32(entry + 12, 14378)  # saved normal palette, not the live doll palette
    write32(entry + 0x2C, 718)
    write32(mcss + 0xD4, palette)
    write32(mcss + 0xD8, faded)
    write32(mcss + 0xDC, 32)

    state = symbols['_ZN3w2u11battle_animL6sStateE']
    actor = state + 8 * 464
    # Preload one one-frame asset: restoration must not rely on a frame change.
    write32(state, 1)
    write32(state + 4, 718 * 2 + 1)
    cpu.mem_write(state + 8, struct.pack(
        '<I6H6I', 0x4E415750, 1, 96, 96, 4, 1, 1, 1, 0x1200, 16, 0, 0, 0))
    cpu.mem_write(state + 48, bytes([0, 1]))
    pokemon_palette = struct.pack('<16H', *range(100, 116))
    cpu.mem_write(state + 432, pokemon_palette)
    config = struct.pack('<I4HI', 0x434E5750, 3, 1, 1, 0, 16)
    config += struct.pack('<HBH', 718, 0x60, 718)
    read_member = symbols['_ZN3w2u12pwan_archive15ReadMemberRangeEjjPvj']
    get_index = 0x021E9794 if black2 else 0x021E97D4
    stop = 0x023F0000

    def on_code(uc, address, size, user_data):
        if address == get_index:
            position = uc.reg_read(UC_ARM_REG_R1)
            uc.reg_write(UC_ARM_REG_R0, 2 if position == 0 else 0xFFFFFFFF)
            uc.reg_write(UC_ARM_REG_PC, uc.reg_read(UC_ARM_REG_LR))
        elif address == read_member:
            member = uc.reg_read(UC_ARM_REG_R0)
            offset = uc.reg_read(UC_ARM_REG_R1)
            dest = uc.reg_read(UC_ARM_REG_R2)
            count = uc.reg_read(UC_ARM_REG_R3)
            assert member == 0 and offset + count <= len(config), "unexpected asset I/O"
            uc.mem_write(dest, config[offset:offset + count])
            uc.reg_write(UC_ARM_REG_R0, 1)
            uc.reg_write(UC_ARM_REG_PC, uc.reg_read(UC_ARM_REG_LR))
        elif address == 0x023E0000:
            dest = uc.reg_read(UC_ARM_REG_R0)
            value = uc.reg_read(UC_ARM_REG_R1) & 0xFF
            count = uc.reg_read(UC_ARM_REG_R2)
            uc.mem_write(dest, bytes([value]) * count)
            uc.reg_write(UC_ARM_REG_PC, uc.reg_read(UC_ARM_REG_LR))

    cpu.hook_add(UC_HOOK_CODE, on_code)

    def call(name):
        cpu.reg_write(UC_ARM_REG_SP, 0x023EF000)
        cpu.reg_write(UC_ARM_REG_LR, stop | 1)
        cpu.emu_start(symbols[name] | 1, stop, count=100000)
        assert cpu.reg_read(UC_ARM_REG_PC) == stop, (
            f"runtime did not return: pc={cpu.reg_read(UC_ARM_REG_PC):08x} "
            f"lr={cpu.reg_read(UC_ARM_REG_LR):08x}")

    def show_doll():
        write32(entry + 0x40, 5)
        cpu.mem_write(palette, bytes([0xAA]) * 32)
        cpu.mem_write(faded, bytes([0xBB]) * 32)
        write32(mcss + 0xC8, 0x1040)

    def assert_doll_preserved():
        assert read32(actor) == 0, "PWAN actor remains active over doll"
        assert read32(actor + 4) == 0 and read32(actor + 8) == 0, "queued uploads remain"
        assert read16(actor + 16) == 0xFFFF, "copied frame was not invalidated"
        assert cpu.mem_read(palette, 32) == bytes([0xAA]) * 32, "doll palette overwritten"
        assert cpu.mem_read(faded, 32) == bytes([0xBB]) * 32, "doll fade palette overwritten"
        assert read32(mcss + 0xC8) == 0x1040, "doll palette proxy overwritten"
        assert read32(state) == 1, "cached PWAN asset was discarded"

    def assert_pokemon_refresh():
        assert read32(actor) == 1, "PWAN did not resume"
        assert read32(actor + 4) == 1 and read32(actor + 8) == 1, "refresh not scheduled"
        assert cpu.mem_read(palette, 32) == pokemon_palette, "Pokemon palette not restored"
        assert read16(actor + 18) == 0, "one-frame texture not queued"

    call('W2U_BattleAnim_Update')
    assert_pokemon_refresh()
    show_doll()
    call('W2U_BattleAnim_Update')
    assert_doll_preserved()
    call('W2U_BattleAnim_Draw')
    assert_doll_preserved()

    # The doll still exists, but the Pokemon is temporarily visible to attack.
    write32(entry + 0x40, 1)
    call('W2U_BattleAnim_Update')
    assert_pokemon_refresh()

    # A native swap between update and draw must cancel the queued upload.
    show_doll()
    call('W2U_BattleAnim_Draw')
    assert_doll_preserved()

    # Substitute breaks; the same MCSS and same one-frame asset resume normally.
    write32(entry + 0x40, 0)
    call('W2U_BattleAnim_Update')
    assert_pokemon_refresh()
    print(f'{elf.name} ({"DSi extra RAM" if dsi else "DS RAM"}): doll suspension, pending-upload cancellation, temporary reveal, and restoration passed')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('elf', type=Path)
    parser.add_argument('--black2', action='store_true')
    parser.add_argument('--dsi', action='store_true', help='Put all native battle objects and palettes in extra RAM')
    args = parser.parse_args()
    check(args.elf, args.black2, args.dsi)
