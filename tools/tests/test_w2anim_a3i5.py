"""A3I5 sprites and the manual offset correction in the w2anim build (tools/w2anim/a3i5.py, build_w2anim_streams.py)."""
from pathlib import Path
import random
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "w2anim"))
import a3i5  # noqa: E402
import build_w2anim_streams as streams  # noqa: E402


def pokeweb_shift(pixels, dx, dy):
    """Pokeweb's shiftIndexedPixels (pwanCompiler.ts), on a 96x96 index grid."""
    out = [[0] * 96 for _ in range(96)]
    for y in range(96):
        for x in range(96):
            nx, ny = x + dx, y + dy
            if 0 <= nx < 96 and 0 <= ny < 96:
                out[ny][nx] = pixels[y][x]
    return out


def pack(grid):
    return bytes((grid[y][x] & 15) | (grid[y][x + 1] & 15) << 4 for y in range(96) for x in range(0, 96, 2))


def unpack(data):
    return [[(data[y * 48 + x // 2] >> (4 if x & 1 else 0)) & 15 for x in range(96)] for y in range(96)]


class Lz11(unittest.TestCase):
    def test_round_trip(self):
        rng = random.Random(7)
        cases = [b"", bytes(5000), bytes(rng.randrange(4) for _ in range(9000)), bytes(range(256)) * 70,
                 bytes(rng.randrange(256) for _ in range(3000))]
        for data in cases:
            with self.subTest(size=len(data)):
                packed = a3i5.lz11_compress(data)
                self.assertEqual(packed[0], 0x11)
                self.assertEqual(a3i5.lz11_decompress(packed), data)


class Timing(unittest.TestCase):
    def test_options(self):
        d = [100, 50, 150, 100]
        self.assertEqual(a3i5.timed(d, {}), d)
        self.assertEqual(a3i5.timed(d, {"even": True}), [100] * 4)
        self.assertEqual(a3i5.timed(d, {"loop_ms": 800}), [200, 100, 300, 200])
        self.assertEqual(a3i5.timed(d, {"min_ms": 120}), [120, 120, 150, 120])
        self.assertEqual(a3i5.timed(d, {"frame_ms": 60}), [60] * 4)
        self.assertEqual(a3i5.timed(d, {"scale": 2}), [200, 100, 300, 200])
        self.assertEqual(a3i5.timed(d, {"hold": {"1": 500}}), [100, 500, 150, 100])
        self.assertEqual(a3i5.timed(d, {"ms": [10, 0, 10, 10]}), [10, 0, 10, 10])
        for bad in ({"ms": [1, 2]}, {"hold": {"9": 5}}, {"frame_ms": 0}):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                a3i5.timed(d, bad)


class Offset(unittest.TestCase):
    def test_tex4_shift_matches_pokeweb(self):
        rng = random.Random(3)
        grid = [[rng.randrange(16) if 10 < x < 80 and 5 < y < 90 else 0 for x in range(96)] for y in range(96)]
        for dx, dy in ((0, 0), (5, -3), (-48, 48), (48, -48), (1, 1), (-7, 20)):
            with self.subTest(dx=dx, dy=dy):
                self.assertEqual(unpack(streams.shift_frame(pack(grid), dx, dy)), pokeweb_shift(grid, dx, dy))

    def test_limits_and_a3i5_placement(self):
        self.assertEqual(a3i5.check_offset(None), (0, 0))
        for bad in ((49, 0), (0, -49)):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                a3i5.check_offset(bad)
        m = {"x0": -50, "y0": -108}
        self.assertEqual(a3i5.place(m, None, 0, None), (-50, -108))          # on the ground point
        self.assertEqual(a3i5.place(m, 96, 16, [0, 0]), (-50, -116))         # PWAN stood 8 rows lower, raised 16
        self.assertEqual(a3i5.place(m, 96, 16, [3, -2]), (-47, -118))        # + the manual offset (+y down)
        # top limit: a box 108 tall standing on row 96 has its top on row -12; limited to row 0 it sinks 12 rows,
        # by at most MAX_SINK (8) for fronts, as far as needed (None) for backs under grounding_back = "pwan"
        self.assertEqual(a3i5.place(m, 96, 0, None, 0), (-50, -100 + a3i5.MAX_SINK))
        self.assertEqual(a3i5.place(m, 96, 0, None, 0, None), (-50, -88))
        self.assertEqual(a3i5.place(m, 96, 0, None, -20, None), (-50, -100))     # already below the limit: no move

    def test_grounding_per_side(self):
        import tempfile
        def load(text):
            with tempfile.TemporaryDirectory() as d:
                p = Path(d) / "sprites.toml"
                p.write_text(text, encoding="utf-8")
                return streams.load_grounding(p)
        self.assertEqual(streams.load_grounding(None), {"front": "pwan", "back": "pwan"})
        self.assertEqual(load('grounding = "carrier"\n'), {"front": "carrier", "back": "carrier"})
        self.assertEqual(load('grounding = "carrier"\ngrounding_back = "pwan"\n'), {"front": "carrier", "back": "pwan"})
        with self.assertRaises(ValueError):
            load('grounding_back = "floor"\n')
        self.assertEqual(streams.a3i5_top("back", "pwan"), a3i5.BACK_TOP_ROW)
        self.assertIsNone(streams.a3i5_top("front", "pwan"))
        self.assertIsNone(streams.a3i5_max_sink("back", "pwan"))
        self.assertEqual(streams.a3i5_max_sink("back", "carrier"), a3i5.MAX_SINK)


class Build(unittest.TestCase):
    def test_committed_sources_build(self):
        sources = sorted((ROOT / "data/graphics/w2anim/a3i5").glob("*.mani"))
        if not sources:
            self.skipTest("no A3I5 sides committed (data/graphics/w2anim/sprites.toml lists none)")
        tpl = a3i5.template(lambda n: (ROOT / "vfs/data/a/0/0/4" / str(n)).read_bytes())
        for path in sources:
            with self.subTest(source=path.name):
                src = path.read_bytes()
                data, files, info = a3i5.build(src, {"frame_ms": 80}, 96, 4, [1, 2], tpl)
                m = a3i5.parse_mani(data)
                self.assertEqual(sum(d for _, d in m["seq"]), 80 * len(a3i5.parse_mani(src)["seq"]))
                self.assertEqual((m["x0"], m["y0"]), (info["x0"], info["y0"]))
                for u in range(len(m["blobs"])):                              # every frame decodes to its box
                    self.assertEqual(len(a3i5.frame_rows(m, u)), m["h"] * a3i5.ROW)
                rec = files[8]
                self.assertEqual(struct.unpack_from("<HH", rec, 4), (m["w"], m["h"]))
                self.assertEqual(struct.unpack_from("<2i", rec, 0xC), (info["x0"] * 256, -info["y0"] * 256))
                self.assertEqual(files[4][:4], b"RECN")
                self.assertEqual(a3i5.lz11_decompress(files[2])[:4], b"RGCN")
                self.assertTrue(all(1 <= v <= 15 for v in m["map"]))


if __name__ == "__main__":
    unittest.main()
