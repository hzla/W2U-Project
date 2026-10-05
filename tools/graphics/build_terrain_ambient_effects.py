#!/usr/bin/env python3
"""Ambient particles for the terrains (src/pokeweb_gameplay/w2u_terrain_texture.cpp).

Writes SPL particle files, with textures drawn here (no game art):

  data/graphics/move_spas/6_00000788.bin   Grassy Terrain: glowing motes that drift up from the floor
  data/graphics/move_spas/6_00000789.bin   Misty Terrain: faint mist puffs rolling along the ground
  data/graphics/move_spas/6_00000787.bin   Electric Terrain: its existing spark resource (0, kept byte for byte) plus
                                           resource 1, a small bolt of lightning that flashes for a few frames (the
                                           runtime puts it in the sky, AdvanceElectricBolts)

Grassy / Misty emit from a disk lying on the floor (emission type 5, axis +Y); the runtime places the emitters on the
field (player side, middle, foe side) and paces them (W2U_TERRAIN_PACE). Psychic (790) is unchanged.

SPL layout (Pokeweb-Serverless src/pokeweb/nitroSpa.ts): 32-byte file header, per resource an 88-byte header and the
optional blocks its flags select (scale 12, colour 12, alpha 8, texture animation 12, child 20, gravity 8, random 8,
...), then the textures ('SPT ' + 32-byte header, image, palette). Textures here are A5I3 (format 6): one byte per
texel, alpha in the high 5 bits, a palette index in the low 3; the palette is a white ramp and the resource colour
tints it.

usage: python tools/graphics/build_terrain_ambient_effects.py [--preview DIR]   (--preview writes the textures as PNG)
"""
from __future__ import annotations

import argparse
import math
import random
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SPAS = ROOT / "data" / "graphics" / "move_spas"
SPA_ELECTRIC, SPA_GRASSY, SPA_MISTY = 787, 788, 789   # must match W2U_*_AMBIENT_SPA_MEMBER

FX = 4096
FLAG_SCALE_ANIM, FLAG_COLOR_ANIM, FLAG_ALPHA_ANIM = 1 << 8, 1 << 9, 1 << 10
FLAG_RANDOM_INIT_ANGLE = 1 << 13
FLAG_SELF_MAINTAINING = 1 << 14              # the emitter ends by itself once its life and particles are over
FLAG_GRAVITY, FLAG_RANDOM = 1 << 24, 1 << 25
EMIT_POINT, EMIT_DISK = 0, 5
AXIS_Y = 1


def fx32(v: float) -> int:
    return round(v * FX)


def rgb555(rgb: tuple[int, int, int]) -> int:
    r, g, b = (c >> 3 for c in rgb)
    return r | (g << 5) | (b << 10)


def air_resistance(v: float) -> int:
    """SPL stores air resistance as 0.75 + byte / 256 * 0.5 (0x80 = 1.0: no damping)."""
    return max(0, min(255, round((v - 0.75) / 0.5 * 256)))


def resource(*, emit_type: int, axis_select: int, axis: tuple[float, float, float], count: float, radius: float,
             vel_pos: float, vel_axis: float, scale: float, aspect: float, color: tuple[int, int, int],
             emitter_life: int, particle_life: int, interval: int, base_alpha: int, air: float,
             variance: tuple[float, float, float], scale_anim: tuple[float, float, float, float, float] | None = None,
             color_anim: tuple[tuple[int, int, int], tuple[int, int, int]] | None = None,
             alpha_anim: tuple[int, int, int, float, float] | None = None,
             gravity: tuple[float, float, float] | None = None,
             random_walk: tuple[float, float, float, int] | None = None, random_angle: bool = False,
             texture: int = 0, self_maintaining: bool = False) -> bytes:
    flags = emit_type | (axis_select << 6)       # draw type 0: billboard
    if self_maintaining:
        flags |= FLAG_SELF_MAINTAINING
    blocks = []
    if scale_anim:
        flags |= FLAG_SCALE_ANIM
        start, mid, end, cin, cout = scale_anim
        blocks.append(struct.pack("<hhhBBH2x", fx32(start), fx32(mid), fx32(end), round(cin * 255), round(cout * 255), 0))
    if color_anim:
        flags |= FLAG_COLOR_ANIM
        start, end = color_anim                  # random start colour among {start, resource colour, end}
        blocks.append(struct.pack("<HHBBBxH2x", rgb555(start), rgb555(end), 0, 127, 255, 1))
    if alpha_anim:
        flags |= FLAG_ALPHA_ANIM
        a0, a1, a2, cin, cout = alpha_anim
        blocks.append(struct.pack("<HHBB2x", a0 | (a1 << 5) | (a2 << 10), 0, round(cin * 255), round(cout * 255)))
    if gravity:
        flags |= FLAG_GRAVITY
        blocks.append(struct.pack("<hhh2x", *(fx32(v) for v in gravity)))
    if random_walk:
        flags |= FLAG_RANDOM
        x, y, z, every = random_walk
        blocks.append(struct.pack("<hhhH", fx32(x), fx32(y), fx32(z), every))
    if random_angle:
        flags |= FLAG_RANDOM_INIT_ANGLE
    var_scale, var_life, var_vel = variance
    head = struct.pack(
        "<I3iiii3hHiiihHhhHHHH",
        flags, 0, 0, 0, fx32(count), fx32(radius), 0,
        *(fx32(v) for v in axis), rgb555(color),
        fx32(vel_pos), fx32(vel_axis), fx32(scale), fx32(aspect), 0,
        0, 0, 0, 0, emitter_life, particle_life)
    head += struct.pack("<I", round(var_scale * 255) | (round(var_life * 255) << 8) | (round(var_vel * 255) << 16))
    head += struct.pack("<I", interval | (base_alpha << 8) | (air_resistance(air) << 16) | (texture << 24))
    head += struct.pack("<I", 0)                 # loop frames, billboard scale, tiling: unused
    head += struct.pack("<I", 0)                 # flip / offset: none
    head += struct.pack("<hh4x", 0, 0)
    assert len(head) == 88, len(head)
    return head + b"".join(blocks)


def texture_a5i3(alpha: list[list[float]], shade: list[list[float]]) -> bytes:
    """alpha / shade in 0..1, rows of equal power-of-two width; shade picks one of 8 palette greys."""
    h, w = len(alpha), len(alpha[0])
    data = bytes((round(max(0.0, min(1.0, alpha[y][x])) * 31) << 3) | round(max(0.0, min(1.0, shade[y][x])) * 7)
                 for y in range(h) for x in range(w))
    palette = b"".join(struct.pack("<H", rgb555((v, v, v))) for v in (176, 192, 206, 218, 230, 240, 248, 255))
    param = 6 | ((int(math.log2(w)) - 3) << 4) | ((int(math.log2(h)) - 3) << 8)
    header = struct.pack("<4sIIIIIII", b" TPS", param, len(data), 32 + len(data), len(palette),
                         32 + len(data) + len(palette), 0, 32 + len(data) + len(palette))
    return header + data + palette


def spa(resources: list[bytes], textures: list[bytes]) -> bytes:
    body = b"".join(resources)
    header = struct.pack("<8sHHIIII4x", b" APS12_1", len(resources), len(textures), 0, 88, 56, 32 + len(body))
    out = header + body + b"".join(textures)
    return out + bytes(-len(out) % 4)


# ---- textures -------------------------------------------------------------------------------------------------

def glow_texture(size: int = 32) -> tuple[list[list[float]], list[list[float]]]:
    """A soft round light: bright core, long falloff."""
    alpha, shade = [], []
    c = (size - 1) / 2
    for y in range(size):
        arow, srow = [], []
        for x in range(size):
            r = math.hypot(x - c, y - c) / (size / 2)
            core = max(0.0, 1 - r / 0.35)
            halo = max(0.0, 1 - r) ** 2.2
            arow.append(min(1.0, halo * 0.85 + core))
            srow.append(min(1.0, 0.35 + core * 0.65 + halo * 0.3))
        alpha.append(arow)
        shade.append(srow)
    return alpha, shade


def value_noise(w: int, h: int, cell: int, rng: random.Random) -> list[list[float]]:
    gw, gh = w // cell + 2, h // cell + 2
    grid = [[rng.random() for _ in range(gw)] for _ in range(gh)]
    smooth = lambda t: t * t * (3 - 2 * t)
    out = []
    for y in range(h):
        row = []
        gy, fy = divmod(y / cell, 1)
        for x in range(w):
            gx, fx = divmod(x / cell, 1)
            gx, gy_ = int(gx), int(gy)
            a = grid[gy_][gx] + (grid[gy_][gx + 1] - grid[gy_][gx]) * smooth(fx)
            b = grid[gy_ + 1][gx] + (grid[gy_ + 1][gx + 1] - grid[gy_ + 1][gx]) * smooth(fx)
            row.append(a + (b - a) * smooth(fy))
        out.append(row)
    return out


def cloud_texture(w: int = 128, h: int = 64, seed: int = 7) -> tuple[list[list[float]], list[list[float]]]:
    """A wide, soft-edged wisp: layered value noise inside an elliptical falloff (seamless edges: alpha 0)."""
    rng = random.Random(seed)
    layers = [(value_noise(w, h, cell, rng), weight) for cell, weight in ((32, 0.5), (16, 0.3), (8, 0.2))]
    alpha, shade = [], []
    for y in range(h):
        arow, srow = [], []
        for x in range(w):
            n = sum(layer[y][x] * weight for layer, weight in layers)
            ex, ey = (x - (w - 1) / 2) / (w / 2), (y - (h - 1) / 2) / (h / 2)
            fall = max(0.0, 1 - (ex * ex + ey * ey)) ** 1.6
            a = max(0.0, (n - 0.28) / 0.72) * fall
            arow.append(min(1.0, a * 1.5))
            srow.append(0.55 + 0.45 * n)
        alpha.append(arow)
        shade.append(srow)
    return alpha, shade


def bolt_texture(w: int = 32, h: int = 64, seed: int = 11) -> tuple[list[list[float]], list[list[float]]]:
    """A small jagged bolt: a bright core zig-zagging down (a short fork off it) inside a soft glow; alpha 0 at the
    edges."""
    rng = random.Random(seed)
    points = [((w - 1) / 2, 2.0)]
    while points[-1][1] < h - 4:
        x, y = points[-1]
        points.append((max(6.0, min(w - 7.0, x + rng.uniform(-5, 5))), y + rng.uniform(5, 9)))
    fork_at = points[len(points) // 2]
    fork = [fork_at, (fork_at[0] + rng.choice((-1, 1)) * 7, fork_at[1] + 8), (fork_at[0] + rng.choice((-1, 1)) * 9,
                                                                               fork_at[1] + 15)]

    def distance(px: float, py: float, path: list[tuple[float, float]]) -> float:
        best = 1e9
        for (x0, y0), (x1, y1) in zip(path, path[1:]):
            dx, dy = x1 - x0, y1 - y0
            t = max(0.0, min(1.0, ((px - x0) * dx + (py - y0) * dy) / (dx * dx + dy * dy)))
            best = min(best, math.hypot(px - x0 - t * dx, py - y0 - t * dy))
        return best

    alpha, shade = [], []
    for y in range(h):
        arow, srow = [], []
        for x in range(w):
            d = min(distance(x, y, points), distance(x, y, fork) + 0.6)
            core = max(0.0, 1 - d / 1.6)
            glow = max(0.0, 1 - d / 6.0) ** 1.6
            edge = min(1.0, min(x, w - 1 - x, y, h - 1 - y) / 3)
            arow.append(min(1.0, core + glow * 0.55) * edge)
            srow.append(min(1.0, 0.4 + core * 0.6))
        alpha.append(arow)
        shade.append(srow)
    return alpha, shade


def resource_size(flags: int) -> int:
    """88 + the optional blocks a resource's flags select (Pokeweb nitroSpa.ts)."""
    size = 88
    for bit, block in ((8, 12), (9, 12), (10, 8), (11, 12), (16, 20), (24, 8), (25, 8), (26, 16), (27, 4), (28, 8),
                       (29, 16)):
        if flags & (1 << bit):
            size += block
    return size


def native_resources(data: bytes, keep: int) -> tuple[list[bytes], list[bytes]]:
    """The first `keep` resources of an SPL file and its textures (an earlier run's additions dropped)."""
    count, textures = struct.unpack_from("<HH", data, 8)
    tex_offset = struct.unpack_from("<I", data, 24)[0]
    resources, offset = [], 32
    for _ in range(count):
        size = resource_size(struct.unpack_from("<I", data, offset)[0])
        resources.append(data[offset:offset + size])
        offset += size
    if offset != tex_offset:
        raise ValueError("unexpected SPL resource layout")
    images = []
    for _ in range(textures):
        total = struct.unpack_from("<I", data, offset + 28)[0]
        images.append(data[offset:offset + total])
        offset += total
    # (texture animations and children reach further than a resource's own texture index: keep every texture but
    # the ones an earlier run appended, one per added resource)
    return resources[:keep], images[:len(images) - (count - keep)]


# ---- effects --------------------------------------------------------------------------------------------------

def grassy_motes() -> bytes:
    """Small glowing motes rising slowly from the grass all over the field, wandering a little, fading in and out.
    One emitter lives 96 frames and releases a mote every 4 frames over a 4.5-unit disk (the runtime keeps two or
    three of them alive across the field, about 45 motes at once)."""
    motes = resource(
        emit_type=EMIT_DISK, axis_select=AXIS_Y, axis=(0.0, 1.0, 0.0), count=1, radius=4.5,
        vel_pos=0.0, vel_axis=0.011, scale=0.36, aspect=1.0, color=(236, 255, 196),
        emitter_life=96, particle_life=150, interval=4, base_alpha=31, air=1.0, variance=(0.55, 0.35, 0.5),
        scale_anim=(0.55, 1.0, 0.75, 0.3, 0.7),
        color_anim=((255, 255, 224), (200, 252, 150)),
        alpha_anim=(0, 30, 0, 0.25, 0.62),
        random_walk=(0.0035, 0.0012, 0.0035, 10))
    return spa([motes], [texture_a5i3(*glow_texture())])


def misty_fog() -> bytes:
    """Wide, faint mist puffs that appear on the floor, roll slowly sideways (a weak pull along +X with drag gives a
    gentle, even drift), swell and fade. Overlapping puffs keep the layer continuous."""
    fog = resource(
        emit_type=EMIT_DISK, axis_select=AXIS_Y, axis=(0.0, 1.0, 0.0), count=1, radius=4.0,
        vel_pos=0.0, vel_axis=0.0015, scale=2.0, aspect=2.0, color=(255, 246, 254),
        emitter_life=110, particle_life=230, interval=22, base_alpha=31, air=0.98, variance=(0.35, 0.25, 0.4),
        scale_anim=(0.75, 1.05, 1.3, 0.4, 0.6),
        alpha_anim=(0, 18, 0, 0.35, 0.6),
        gravity=(0.0004, 0.0, 0.0),
        random_walk=(0.0012, 0.0, 0.0012, 20),
        random_angle=False)
    return spa([fog], [texture_a5i3(*cloud_texture())])


def electric_with_bolts(existing: bytes) -> bytes:
    """787: the spark resource as it is, plus a small bolt of lightning: one particle per emitter that flashes in
    within about 3 frames and fades out slowly over the rest of its 40 (Sun / Moon), white with a warm glow, tall
    (aspect 0.5)."""
    sparks, images = native_resources(existing, 1)
    bolt = resource(
        emit_type=EMIT_POINT, axis_select=AXIS_Y, axis=(0.0, 1.0, 0.0), count=1, radius=0.0,
        vel_pos=0.0, vel_axis=0.0, scale=2.0, aspect=0.5, color=(255, 255, 236),
        emitter_life=1, particle_life=40, interval=1, base_alpha=31, air=1.0, variance=(0.0, 0.25, 0.0),
        alpha_anim=(0, 31, 0, 0.08, 0.15), texture=len(images), self_maintaining=True)
    return spa(sparks + [bolt], images + [texture_a5i3(*bolt_texture())])


def write_preview(name: str, alpha, shade, directory: Path) -> None:
    from PIL import Image
    h, w = len(alpha), len(alpha[0])
    img = Image.new("RGBA", (w, h))
    img.putdata([(round(176 + 79 * shade[y][x]),) * 3 + (round(255 * alpha[y][x]),) for y in range(h) for x in range(w)])
    img.resize((w * 4, h * 4), Image.NEAREST).save(directory / f"{name}.png")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--preview", type=Path, help="also write the textures as PNG into this folder")
    args = parser.parse_args()
    electric = (SPAS / f"6_{SPA_ELECTRIC:08d}.bin").read_bytes()
    out = {SPA_GRASSY: grassy_motes(), SPA_MISTY: misty_fog(), SPA_ELECTRIC: electric_with_bolts(electric)}
    for member, data in out.items():
        (SPAS / f"6_{member:08d}.bin").write_bytes(data)
    if args.preview:
        args.preview.mkdir(parents=True, exist_ok=True)
        write_preview("grassy_mote", *glow_texture(), args.preview)
        write_preview("misty_wisp", *cloud_texture(), args.preview)
        write_preview("electric_bolt", *bolt_texture(), args.preview)
    print("terrain ambient particles: " + ", ".join(f"SPA {m} ({len(d)} bytes)" for m, d in out.items()))


if __name__ == "__main__":
    main()
