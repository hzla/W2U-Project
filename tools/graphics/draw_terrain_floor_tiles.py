#!/usr/bin/env python3
"""Draw the Grassy and Misty Terrain floor tiles and skies (assets/move_backgrounds/terrains/*-tileable.png, *-sky.png).

Sun / Moon style: soft, luminous, low contrast (Grassy: a pale glowing green ground with gentle light patches and a
fine sheen of grass; Misty: a sea of soft pink-white cloud). Drawn here from seamless (wrapping) value noise, so the
tiles repeat without seams across the floor; tools/graphics/build_terrain_texture_mvp.py then fits them to every
battle background's floor texture (32-128 px, 16 / 256 colours). The skies replace the backdrop (the batt_sky*
material of the outdoor backgrounds, 128x64): top of the image = top of the sky, bottom row = the horizon, which
matches the floor's colour so the two meet without a seam; they wrap horizontally. Electric and Psychic keep their
tiles and the native sky.

usage: python tools/graphics/draw_terrain_floor_tiles.py   (then build_terrain_texture_mvp.py)
"""
from __future__ import annotations

from pathlib import Path

import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "assets" / "move_backgrounds" / "terrains"
SIZE = 512
SKY_W, SKY_H = 512, 256
# The battle camera shows the lower half of the backdrop texture (measured with a banded test sky: rows 128-255 of
# 256, the bottom row on the horizon). The scenery is drawn into that window; above it is one flat colour.
SKY_WINDOW = 0.5
# The backdrop stretches its texture about 4.5x wider than tall on screen (same test: 64 image px across = 103 DS px,
# 32 image px down = 11.5 DS px). The runtime repeats a Grassy / Misty sky 4x across the backdrop (texture scale S 4,
# w2u_terrain_texture.cpp UpdateSkyRepeat), leaving a 1.125x stretch: the scenery is drawn at true proportions on a
# 1.125x wider canvas and squeezed into the 512-wide image. It is one quarter of the backdrop and wraps.
SKY_STRETCH = 4.5 / 4
SKY_DW = int(SKY_W * SKY_STRETCH)


def spectral_noise(rng: np.random.Generator, scale_x: float, scale_y: float | None = None,
                   shape: tuple[int, int] = (SIZE, SIZE)) -> np.ndarray:
    """Seamless soft noise in 0..1: white noise filtered in frequency space (periodic by construction). scale_x /
    scale_y: feature size in pixels along x / y (different values give streaks). shape: (height, width)."""
    scale_y = scale_x if scale_y is None else scale_y
    kx, ky = np.meshgrid(np.fft.fftfreq(shape[1]), np.fft.fftfreq(shape[0]))
    spectrum = np.exp(-((kx * scale_x) ** 2 + (ky * scale_y) ** 2) * 2.0)
    field = np.real(np.fft.ifft2(np.fft.fft2(rng.standard_normal(shape)) * spectrum))
    field = (field - field.mean()) / (field.std() * 4) + 0.5
    return np.clip(field, 0, 1)


def mix(c0, c1, t: np.ndarray) -> np.ndarray:
    c0, c1 = np.array(c0, float), np.array(c1, float)
    return c0[None, None, :] * (1 - t[..., None]) + c1[None, None, :] * t[..., None]


def grassy(rng: np.random.Generator) -> np.ndarray:
    # a pale glowing green ground: broad sunlit patches, a finer mottling, and a fine vertical sheen of grass blades
    broad = spectral_noise(rng, 110)
    mottle = spectral_noise(rng, 30)
    light = np.clip(broad * 0.7 + mottle * 0.3, 0, 1)
    image = mix((126, 212, 116), (204, 250, 172), light)
    blades = spectral_noise(rng, 3, 16)          # narrow and tall: short upright streaks
    image += mix((-10, -8, -6), (14, 12, 2), blades)
    return image


def misty(rng: np.random.Generator) -> np.ndarray:
    # a sea of soft cloud: rounded white puffs (three noise scales, a soft threshold) over pink-lilac hollows, with a
    # faint brighter rim where a puff rises
    n = spectral_noise(rng, 70) * 0.65 + spectral_noise(rng, 28) * 0.3 + spectral_noise(rng, 11) * 0.05
    x = np.clip((n - 0.28) / 0.46, 0, 1)
    puff = x * x * (3 - 2 * x)
    image = mix((238, 178, 218), (255, 230, 246), puff)
    rim = np.clip(1 - np.abs(puff - 0.55) / 0.25, 0, 1)
    image += mix((0, 0, 0), (6, 8, 4), rim)
    return image


def vertical(t: np.ndarray, stops: list[tuple[float, tuple[int, int, int]]]) -> np.ndarray:
    """A colour ramp over t (0 top .. 1 horizon) through (position, colour) stops, eased between them."""
    out = np.zeros(t.shape + (3,))
    for (p0, c0), (p1, c1) in zip(stops, stops[1:]):
        x = np.clip((t - p0) / (p1 - p0), 0, 1)
        x = x * x * (3 - 2 * x)
        inside = (t >= p0) & (t <= p1)
        out[inside] = mix(c0, c1, x)[inside]
    return out


def window(t: np.ndarray) -> np.ndarray:
    """0 at the top of the visible window .. 1 at the horizon (negative above the window)."""
    return (t - SKY_WINDOW) / (1 - SKY_WINDOW)


def grassy_sky(rng: np.random.Generator) -> np.ndarray:
    # green glow deepening upwards, soft light shafts, clumps of tall grass rising out of a bright horizon
    yy, xx = np.mgrid[0:SKY_H, 0:SKY_DW].astype(float)
    v = window(yy / (SKY_H - 1))
    image = vertical(np.clip(v, 0, 1), [(0.0, (84, 162, 98)), (0.5, (128, 206, 120)), (0.85, (180, 240, 152)),
                                        (1.0, (206, 250, 174))])
    # light shafts: soft diagonal bands, whole periods across the canvas so the sky still wraps
    shafts = 0.5 + 0.5 * np.sin(2 * np.pi * (xx + yy * 0.8) * 2 / SKY_DW)
    shafts = shafts ** 5 * (0.55 + 0.45 * spectral_noise(rng, 60, 30, (SKY_H, SKY_DW)))
    image += mix((0, 0, 0), (46, 50, 30), shafts * np.clip(1.1 - v, 0, 1))
    # grass: clumps of three to five blades, darker bodies with light edges, rooted in the horizon glow
    blades = np.zeros((SKY_H, SKY_DW))
    edge = np.zeros((SKY_H, SKY_DW))
    columns = np.arange(SKY_DW, dtype=float)
    span = SKY_H * (1 - SKY_WINDOW)
    for _ in range(12):
        cx0 = rng.uniform(0, SKY_DW)
        for _blade in range(int(rng.integers(3, 6))):
            x0 = cx0 + rng.uniform(-40, 40)
            height = rng.uniform(0.35, 0.9) * span
            lean = rng.uniform(-0.6, 0.6)
            width = rng.uniform(9, 16)
            for y in range(int(SKY_H - height), SKY_H):
                f = min(1.0, (SKY_H - y) / height)        # 0 at the root .. 1 at the tip
                cx = x0 + lean * (SKY_H - y) * f
                w = width * (1 - f) ** 0.7 + 3
                d = np.abs(((columns - cx + SKY_DW / 2) % SKY_DW) - SKY_DW / 2)
                blades[y] = np.maximum(blades[y], np.clip(1 - d / w, 0, 1) * (1 - f * 0.6))
                edge[y] = np.maximum(edge[y], np.clip(1 - np.abs(d - w * 0.7) / 3.0, 0, 1) * (1 - f * 0.5))
    fade = np.clip((1.0 - v) / 0.12, 0, 1)                # the roots melt into the horizon glow
    image -= mix((0, 0, 0), (70, 52, 58), blades * fade)
    image += mix((0, 0, 0), (40, 34, 18), edge * fade * 0.8)
    return image


def misty_sky(rng: np.random.Generator) -> np.ndarray:
    # lilac-pink above, pink-white at the horizon, three banks of soft cloud and a few sparkles up high
    yy, xx = np.mgrid[0:SKY_H, 0:SKY_DW].astype(float)
    v = window(yy / (SKY_H - 1))
    image = vertical(np.clip(v, 0, 1), [(0.0, (198, 142, 208)), (0.5, (234, 182, 224)), (0.85, (250, 220, 240)),
                                        (1.0, (255, 230, 246))])
    white = np.array((255.0, 244.0, 252.0))
    for centre, spread, strength, scale in ((0.85, 0.09, 1.0, 34), (0.58, 0.1, 0.9, 28), (0.28, 0.09, 0.7, 22)):
        n = (spectral_noise(rng, scale * 2.4, scale, (SKY_H, SKY_DW)) * 0.7 +
             spectral_noise(rng, scale * 1.2, scale * 0.6, (SKY_H, SKY_DW)) * 0.3)
        band = np.exp(-((v - centre) / spread) ** 2)
        cloud = np.clip((n * band - 0.2) / 0.3, 0, 1)
        cloud = cloud * cloud * (3 - 2 * cloud) * strength * 0.9
        under = np.clip(np.roll(cloud, -6, axis=0) - cloud, 0, 1)   # a lilac underside: a cloud, not a smear
        image = image - mix((0, 0, 0), (22, 30, 6), under * 0.8)
        image = image * (1 - cloud[..., None]) + white * cloud[..., None]
    glints = np.zeros((SKY_H, SKY_DW))
    top = int(SKY_H * SKY_WINDOW)
    for _ in range(16):
        y, x = int(rng.uniform(top, top + (SKY_H - top) * 0.45)), int(rng.uniform(0, SKY_DW))
        for dy in range(-5, 6):
            for dx in range(-5, 6):
                val = max(0.0, 1 - (abs(dx) + abs(dy)) / 5)
                yy_, xx_ = (y + dy) % SKY_H, (x + dx) % SKY_DW
                glints[yy_, xx_] = max(glints[yy_, xx_], val)
    image += mix((0, 0, 0), (50, 44, 34), glints)
    return image


def main() -> int:
    rng = np.random.default_rng(20261005)
    for name, draw in (("grassy", grassy), ("misty", misty)):
        image = np.clip(draw(rng), 0, 255).astype(np.uint8)
        Image.fromarray(image, "RGB").save(OUT / f"{name}-tileable.png")
        print(f"{name}-tileable.png {SIZE}x{SIZE}")
    for name, draw in (("grassy", grassy_sky), ("misty", misty_sky)):
        image = np.clip(draw(rng), 0, 255).astype(np.uint8)
        squeezed = Image.fromarray(image, "RGB").resize((SKY_W, SKY_H), Image.Resampling.LANCZOS)
        squeezed.save(OUT / f"{name}-sky.png")
        print(f"{name}-sky.png {SKY_W}x{SKY_H}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
