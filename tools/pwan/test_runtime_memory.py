#!/usr/bin/env python3
"""Host checks for the PWAN config limit and battle texture conversion/upload.

Run with python3 tools/pwan/test_runtime_memory.py. Requires clang++ with ASan.
The texture harness compiles the production functions directly from their source
file, with fake VRAM and bank registers; it does not emulate DS timing.
"""

from __future__ import annotations

import re
import subprocess
import tempfile
import unittest
from pathlib import Path

from build_pwan_narc import PWAN_RUNTIME_CONFIG_CACHE_BYTES, collect_members
from pwan_config import write_config


ROOT = Path(__file__).resolve().parents[2]
RUNTIME = ROOT / "src/pwan_animation"


class RuntimeMemoryTests(unittest.TestCase):
    def test_config_capacity(self) -> None:
        runtime = (RUNTIME / "w2u_pwan_archive.cpp").read_text()
        capacity = re.search(r"#define W2U_PWAN_CONFIG_CACHE_BYTES (\d+)u", runtime)
        self.assertIsNotNone(capacity)
        self.assertEqual(int(capacity[1]), PWAN_RUNTIME_CONFIG_CACHE_BYTES)
        with tempfile.TemporaryDirectory() as tmp:
            directory = Path(tmp)
            config = directory / "config.bin"
            entries = {
                (species, 0): dict(species=species, flags=3, assetIndex=species)
                for species in range(1, 769)
            }
            write_config(config, entries, 192, max_overrides=768)
            data = config.read_bytes()
            self.assertEqual(len(data), 3856)
            self.assertEqual(collect_members(directory), [data])
            padded = data.ljust(PWAN_RUNTIME_CONFIG_CACHE_BYTES, b"\0")
            config.write_bytes(padded)
            self.assertEqual(collect_members(directory), [padded])
            config.write_bytes(padded + b"\0")
            with self.assertRaisesRegex(ValueError, "exceeds runtime config cache"):
                collect_members(directory)

    def test_battle_texture(self) -> None:
        source = (RUNTIME / "w2u_battle_anim.cpp").read_text()
        constants = []
        for line in source.splitlines():
            if not line.startswith("#define "):
                continue
            name = line.split()[1]
            if name.startswith(("W2U_MCSS_TEX_", "W2U_VISIBLE_TEX_", "W2U_STAGING_TEX_")) or name in (
                "W2U_FRAME_BYTES", "W2U_LEGACY_TEX_BYTES_AVOIDED"
            ):
                constants.append(line)
        scratch = re.search(r"^static u8 sTextureScratch\[.*?;", source, re.MULTILINE)
        self.assertIsNotNone(scratch)
        functions = source[
            source.index("static void BlitTileSegmentToTexture("):
            source.index("static b32 StageFrameTexture(")
        ]
        harness = (
            HARNESS_PREFIX + "\n".join(constants) + "\n" + scratch[0]
            + HARNESS_STUBS + functions + HARNESS_MAIN
        )
        with tempfile.TemporaryDirectory() as tmp:
            cpp = Path(tmp) / "battle_texture.cpp"
            executable = Path(tmp) / "battle_texture"
            cpp.write_text(harness)
            subprocess.run([
                "clang++", "-std=c++17", "-O1", "-g",
                "-fsanitize=address,undefined", "-fno-omit-frame-pointer",
                str(cpp), "-o", str(executable),
            ], check=True)
            subprocess.run([str(executable)], check=True)


HARNESS_PREFIX = r"""
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using s32 = int32_t;
using ActorId = u32;
static void Check(bool condition) { if (!condition) std::abort(); }
"""

HARNESS_STUBS = r"""
static_assert(sizeof(sTextureScratch) == 4608, "packed staging must be 4.5 KiB");
static u8 sFrameScratch[W2U_FRAME_BYTES];
alignas(4) static u8 vram[0x44000];
#define W2U_LCDC_TEX_VRAM ((volatile u16 *)vram)
static struct { struct { bool textureDirty; } actor[8]; } sState;
static struct {
    u32 textureUploadActors, textureBytesUploaded, legacyTextureBytesAvoided;
    u32 lastUploadActors, lastUploadBytes;
} W2U_BattleAnim_Profile;
static bool banksMapped;
static void SetTextureBanksLcdc(u8 *a, u8 *b, u8 *c, u8 *d) {
    Check(!banksMapped);
    banksMapped = true;
    *a = 1; *b = 2; *c = 3; *d = 4;
}
static void RestoreTextureBanks(u8 a, u8 b, u8 c, u8 d) {
    Check(banksMapped && a == 1 && b == 2 && c == 3 && d == 4);
    banksMapped = false;
}
"""

HARNESS_MAIN = r"""
int main() {
    u32 random = 0x720196;
    u8 expected[96 * 96 / 2];
    u8 expectedVram[sizeof(vram)];
    for (u32 trial = 0; trial < 128; ++trial) {
        for (u8 &value : sFrameScratch) {
            random ^= random << 13; random ^= random >> 17; random ^= random << 5;
            value = (u8)random;
        }
        // Decode each pixel independently using the native four-segment tile layout.
        std::memset(expected, 0, sizeof(expected));
        for (u32 y = 0; y < 96; ++y) {
            for (u32 x = 0; x < 96; ++x) {
                const u32 localX = x < 64 ? x : x - 64;
                const u32 localY = y < 64 ? y : y - 64;
                const u32 tilesWide = x < 64 ? 8 : 4;
                const u32 segment = y < 64 ? (x < 64 ? 0 : 0x800)
                                           : (x < 64 ? 0xc00 : 0x1000);
                const u32 tile = (localY / 8) * tilesWide + localX / 8;
                const u32 offset = segment + tile * 32 + (localY % 8) * 4 + (localX % 8) / 2;
                const u8 pixel = (sFrameScratch[offset] >> ((x % 2) * 4)) & 15;
                expected[y * 48 + x / 2] |= pixel << ((x % 2) * 4);
            }
        }
        std::memset(sTextureScratch, 0xa5, sizeof(sTextureScratch));
        ConvertFrameToTexture();
        Check(std::memcmp(sTextureScratch, expected, sizeof(expected)) == 0);
        for (u32 slot = 0; slot < 8; ++slot) {
            std::memset(vram, 0xa5, sizeof(vram));
            std::memset(expectedVram, 0xa5, sizeof(expectedVram));
            for (u32 y = 0; y < 96; ++y) {
                std::memcpy(expectedVram + 0x24000 + slot * 0x4000 + y * 128,
                            expected + y * 48, 48);
            }
            const u32 actor = (slot + trial) % 8;
            sState.actor[actor].textureDirty = true;
            UploadTexture(actor, (s32)slot);
            Check(!banksMapped && !sState.actor[actor].textureDirty);
            // Includes row padding, unused bottom rows, and every other VRAM slot.
            Check(std::memcmp(vram, expectedVram, sizeof(vram)) == 0);
        }
    }
    std::puts("128 frames decoded; all 8 texture slots verified under ASan/UBSan");
}
"""


if __name__ == "__main__":
    unittest.main()
