#!/usr/bin/env python3
"""Battle effects for the strong weathers (Delta Stream, Primordial Sea, Desolate Land).

Ported from MegaB2W2 (scripts/data/steps/step_70_weather_fx.py). Reads retail particle files and weather scripts
from a clean extracted White 2 VFS and writes:

  data/graphics/move_spas/6_<SPA>.bin            recoloured particles (strong winds, heavy rain, harsh sun)
  data/graphics/move_animations/5_<MEMBER>.bin   effect scripts (start effects + turn-end effects)

The scripts live in a/0/6/5 above the move range and are started as effect ID member + 115
(src/pokeweb_gameplay/w2u_move_animation_hooks.s routes IDs >= 676 back into a/0/6/5), so the fixed
battle-animation archive a/0/6/6 keeps its 115 retail members. The IDs here must match
include/w2u_strong_weather.h.

Effect script format: u32 variant count (1), 14 u32 offsets (all 0x3C), then u16 opcode + u32 arguments.
Retail weather-start scripts (a/0/6/6): rain 55, sun 58. They use 06 load particles, 3A, 34 play SE (9 args),
09 emit (11 args), 39 wait, 38 wait for emitters, 4D end, plus 2A / 1B screen and sprite fades.
"""
from __future__ import annotations

import argparse
import struct
from pathlib import Path

import ndspy.narc

# Must match include/w2u_strong_weather.h
SPA_WINDS, SPA_RAIN, SPA_SUN = 1031, 1032, 1033
MEMBER_WINDS, MEMBER_RAIN, MEMBER_RAIN_TURN, MEMBER_SUN, MEMBER_SUN_TURN = 960, 961, 962, 963, 964

# Retail sources
SPA_SRC_WINDS, SPA_SRC_RAIN, SPA_SRC_SUN = 544, 411, 412   # Tailwind streaks, rain, sun
SCRIPT_RAIN, SCRIPT_SUN = 55, 58                            # a/0/6/6 weather-start scripts
SE_WINDS = 1497

# Emitter resources patched per particle file {offset: expected flags}; base alpha at +0x45, colour at +0x22
PARTICLE_RESOURCES = {
    SPA_SRC_WINDS: {0x20: 0x20204411, 0x90: 0x00205700},
    SPA_SRC_RAIN: {0x20: 0x00204652},
    SPA_SRC_SUN: {0x20: 0x00204710, 0x98: 0x0020C714},
}
BASE_ALPHA = 0x45
COLOR = 0x22
EMISSION_COUNT = 0x10   # fx32 particles per emission
PARTICLE_LIFE = 0x3E    # u16 frames
SPRITES_ALL = 14        # ChangeColor (1B) target: every battler
VANILLA_ARGS = {0x06: 1, 0x3A: 1, 0x34: 9, 0x09: 11, 0x39: 1, 0x38: 1, 0x4D: 0, 0x2A: 5, 0x40: 2, 0x1B: 5}
SCRIPT_START = 0x3C

# Heavy rain: denser than Rain Dance. The battle's particle pool is the limit (Rain Dance already fills it: its drops
# fall in waves, 40-frame lives mostly spent below the screen), so the drops live only about as long as they take to
# cross the screen (22 frames) and the emission is x1.5: steady, denser rain from the same pool. The background dims
# towards a dark blue-grey instead of black and the battlers take a faint blue tint (3/16) while it falls.
HEAVY_RAIN = {"particle_color": (200, 216, 248), "base_alpha": 31, "fade": 13, "se": 1562,
              "se_extra": (1514, 60), "emission_scale": 1.5, "particle_life": 22, "fade_color": (16, 28, 64),
              "sprite_tint": (3, (88, 136, 248))}
EXTREME_SUN = {"particle_color": (248, 128, 40), "fade": 9, "fade_color": (248, 96, 16), "se": 1565,
               "se_extra": (1425, 80)}


def bgr555(rgb: tuple[int, int, int]) -> int:
    r, g, b = (channel >> 3 for channel in rgb)
    return r | (g << 5) | (b << 10)


class Script:
    def __init__(self) -> None:
        self.b = bytearray()

    def op(self, code: int, *args: int) -> "Script":
        self.b += struct.pack("<H", code) + b"".join(struct.pack("<i", a) for a in args)
        return self

    def file(self) -> bytes:
        return bytes([1, 0, 0, 0]) + struct.pack("<14I", *([SCRIPT_START] * 14)) + bytes(self.b)


def strong_winds_script(spa: int) -> bytes:
    s = Script()
    s.op(0x06, spa)
    s.op(0x3A, 0)
    s.op(0x34, SE_WINDS, 1, 2, 0, 0, 0x64, 0, 0, 0)
    s.op(0x3A, 1)
    for emitter, wait in ((0, 12), (1, 12), (0, 0)):
        s.op(0x09, spa, emitter, 0, 8, 0, 0x2000, 0, 0x800, 0x1000, 0x800, 0x1000)
        if wait:
            s.op(0x39, wait)
    s.op(0x38, 0)
    s.op(0x4D)
    return s.file()


def patched_particles(spa: bytes, source: int, alpha: int | None = None, color: int | None = None,
                      emission_scale: float | None = None, life: int | None = None) -> bytes:
    out = bytearray(spa)
    if out[:8] != b" APS12_1":
        raise ValueError(f"SPA {source} is not an SPL particle file")
    for offset, flags in PARTICLE_RESOURCES[source].items():
        if struct.unpack_from("<I", out, offset)[0] != flags:
            raise ValueError(f"SPA {source}: unexpected emitter resource at {offset:#x}")
        if alpha is not None:
            out[offset + BASE_ALPHA] = alpha
        if color is not None:
            struct.pack_into("<H", out, offset + COLOR, color)
        if emission_scale is not None:
            count = struct.unpack_from("<i", out, offset + EMISSION_COUNT)[0]
            struct.pack_into("<i", out, offset + EMISSION_COUNT, round(count * emission_scale))
        if life is not None:
            struct.pack_into("<H", out, offset + PARTICLE_LIFE, life)
    return bytes(out)


def decode_script(data: bytes) -> list[tuple[int, list[int]]]:
    if data[0] != 1 or len(set(struct.unpack_from("<14I", data, 4))) != 1:
        raise ValueError("expected a one-variant effect script")
    offset = struct.unpack_from("<I", data, 4)[0]
    ops = []
    while True:
        code = struct.unpack_from("<H", data, offset)[0]
        offset += 2
        count = VANILLA_ARGS[code]
        ops.append((code, list(struct.unpack_from(f"<{count}i", data, offset))))
        offset += 4 * count
        if code == 0x4D:
            return ops


def adapted_script(vanilla: list[tuple[int, list[int]]], spa: int, v: dict, turn: bool) -> bytes:
    fade = v["fade"] if not turn else max(1, v["fade"] * 2 // 3)
    color = bgr555(v["fade_color"]) if "fade_color" in v else None
    tint = v.get("sprite_tint")
    s = Script()
    for code, args in vanilla:
        if code == 0x06:
            args = [spa]
        elif code in (0x2A, 0x1B):
            args = list(args)
            if args[1] == 0:
                args[2] = fade
            else:
                args[1] = fade
            if color is not None:
                args[4] = color
            if code == 0x2A and tint:            # the battlers' tint follows the background fade
                evy, rgb = tint
                fade_in = args[1] == 0
                s.op(0x1B, SPRITES_ALL, 0 if fade_in else evy, evy if fade_in else 0, args[3], bgr555(rgb))
        elif code == 0x34:
            if turn:
                continue
            s.op(code, *args)
            se, volume = v["se_extra"]
            s.op(0x34, se, args[1], args[2], 0, 0, volume, 0, 0, 0)
            continue
        elif code == 0x09:
            args = [spa] + args[1:]
            s.op(code, *args)
            if not turn:
                s.op(0x39, 6)
                s.op(code, *args)
            continue
        s.op(code, *args)
    return s.file()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    root = Path(__file__).resolve().parents[2]
    parser.add_argument("--base-vfs", type=Path, default=root.parent / "IRDO_Extracted")
    parser.add_argument("--root", type=Path, default=root)
    args = parser.parse_args()
    spas = ndspy.narc.NARC((args.base_vfs / "data/a/0/0/6").read_bytes()).files
    effects = ndspy.narc.NARC((args.base_vfs / "data/a/0/6/6").read_bytes()).files
    if len(effects) != 115:
        raise ValueError(f"expected the retail a/0/6/6 (115 members), got {len(effects)}")
    rain_script, sun_script = decode_script(effects[SCRIPT_RAIN]), decode_script(effects[SCRIPT_SUN])
    for script, v in ((rain_script, HEAVY_RAIN), (sun_script, EXTREME_SUN)):
        if not any(code == 0x34 and a[0] == v["se"] for code, a in script):
            raise ValueError(f"SE {v['se']} not found in the retail weather script")

    spa_out = {
        SPA_WINDS: patched_particles(spas[SPA_SRC_WINDS], SPA_SRC_WINDS, alpha=20),
        SPA_RAIN: patched_particles(spas[SPA_SRC_RAIN], SPA_SRC_RAIN, HEAVY_RAIN["base_alpha"],
                                    bgr555(HEAVY_RAIN["particle_color"]), HEAVY_RAIN["emission_scale"],
                                    HEAVY_RAIN["particle_life"]),
        SPA_SUN: patched_particles(spas[SPA_SRC_SUN], SPA_SRC_SUN, None, bgr555(EXTREME_SUN["particle_color"])),
    }
    script_out = {
        MEMBER_WINDS: strong_winds_script(SPA_WINDS),
        MEMBER_RAIN: adapted_script(rain_script, SPA_RAIN, HEAVY_RAIN, turn=False),
        MEMBER_RAIN_TURN: adapted_script(rain_script, SPA_RAIN, HEAVY_RAIN, turn=True),
        MEMBER_SUN: adapted_script(sun_script, SPA_SUN, EXTREME_SUN, turn=False),
        MEMBER_SUN_TURN: adapted_script(sun_script, SPA_SUN, EXTREME_SUN, turn=True),
    }
    graphics = args.root / "data/graphics"
    for spa, data in spa_out.items():
        (graphics / "move_spas" / f"6_{spa:08d}.bin").write_bytes(data)
    for member, data in script_out.items():
        (graphics / "move_animations" / f"5_{member:08d}.bin").write_bytes(data)
    print(f"strong weather effects: SPAs {min(spa_out)}-{max(spa_out)}, scripts {min(script_out)}-{max(script_out)} "
          f"(effect IDs {min(script_out) + 115}-{max(script_out) + 115})")


if __name__ == "__main__":
    main()
