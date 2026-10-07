"""Terrain sound recipes: which donor material from B2W2's own sound archive, what is baked offline, and the live
sequence of each layer (docs/megab2w2-integration.md, "Terrain sounds"). Built by build_terrain_sfx.py.

Take 1 plays inside the terrain move's animation (attacker side; the move scripts' PlaySound commands); take 2 plays
when the terrain is applied (its start message; w2u_terrain_texture.cpp, so the Surges play only take 2). Each take is
up to three SEs started together on the SE players SE_1 / SE_2 / SE_3, at most four voices at once (the SE players
share channels 12-15), each SE within the SE player's 10,200-byte heap.

Times are seconds from the take's start, matched to measurements of the Sun / Moon terrain sounds (onsets, levels,
spectral balance, pan; the recordings themselves are not part of the project).
"""
from sfxlib import (Track, seconds, make_swav, lowpass_sweep, resample, fade, normalize, cycle_loop, noise_loop)

# Layer i of a take: SDAT player PLAYERS[i] (2 = PLAYER_SE_1, 3 = PLAYER_SE_2, 5 = PLAYER_SE_3), which the game
# addresses as sound handle HANDLES[i] (player - 1: GFL_SEPlayKeepVol, and the move scripts' PlaySound `player`).
PLAYERS = (2, 3, 5)
HANDLES = (1, 2, 4)


def S(t):
    return seconds(t)


class Assets:
    """Baked wave archives shared between SEs (each SE loads the archives its bank names)."""

    def __init__(self, ar):
        self.ar = ar
        self.swars = {}
        self.sizes = {}

    def baked(self, key, builder):
        if key not in self.swars:
            swavs = builder(self.ar)
            self.swars[key] = self.ar.add_swar(f"WAVE_W2U_TERRAIN_{key.upper()}", swavs)
            self.sizes[key] = sum(len(w.data) for w in swavs)
        return self.swars[key]


# ---------------------------------------------------------------- baked material


def sine_loop(ar):
    """Confusion / Psychic's pure tone (1456/0, ~790 Hz): eight whole cycles as a seamless loop."""
    x, sr, _ = ar.donor(1456)
    loop, rate, _ = cycle_loop(x, sr, 790.0, 0.05, 8)
    return [make_swav(normalize(loop, 0.9), rate, 0)]


def calm_mind_chimes(ar):
    """Calm Mind's chime (1504/0, 22,050 Hz): three takes of its first 0.35 s, each with a low-pass sweep baked in
    (bright 9 -> 4 kHz, mid 4 -> 1.5 kHz, dark 1.5 kHz -> 600 Hz); the darker ones need less bandwidth, so a lower
    rate. Played in turn, the echo taps sweep down."""
    x, sr, _ = ar.donor(1504)
    head = x[:int(0.35 * sr)]
    out = []
    for f0, f1, rate in ((9000, 4000, 22050), (4000, 1500, 11025), (1500, 600, 8000)):
        y = fade(lowpass_sweep(head, sr, f0, f1), sr, 0.0, 0.10)
        out.append(make_swav(normalize(resample(y, sr, rate), 0.92), rate))
    return out


def mist_whoosh(ar):
    """Mist's spray (1435/0, noise, 7.7 kHz centroid): [0] a bright 0.15 s burst at 32 kHz (the attack); [1] a
    breathy loop low-passed to 3.5 kHz at 16 kHz (the body)."""
    x, sr, _ = ar.donor(1435)
    burst = fade(x[:int(0.15 * sr)], sr, 0.0, 0.05)
    body = lowpass_sweep(x, sr, 3500, 3500, q=0.7)
    body = resample(body, sr, 16000)
    loop = noise_loop(normalize(body, 0.9), 16000, 0.08, 0.28)
    return [make_swav(normalize(burst, 0.95), sr), make_swav(loop, 16000, 0)]


def leaf_rustle(ar):
    """Razor Leaf's rustle (1679/0, noise, 6.8 kHz centroid) cut to 0.16 s with a fast fade (punchy burst); Magical
    Leaf's rustle loop (1408/0) low-passed to 6 kHz at 16 kHz for the tail."""
    x, sr, _ = ar.donor(1679)
    burst = fade(x[:int(0.16 * sr)], sr, 0.0, 0.07)
    y, sr2, _ = ar.donor(1408)
    tail = resample(lowpass_sweep(y, sr2, 6000, 6000, q=0.7), sr2, 16000)
    loop = noise_loop(normalize(tail, 0.9), 16000, 0.05, 0.25)
    return [make_swav(normalize(burst, 0.95), sr), make_swav(loop, 16000, 0)]


# ---------------------------------------------------------------- shared pieces


def opening(track, key, kind, boost=0):
    """The take-1 opening all four references share: four low events at 0.00 / 0.21 / 0.42 / 0.60 s (dominant
    150-300 Hz), as rising glides (Psychic, Misty, Electric) or plain bursts (Grassy)."""
    for t, vel in ((0.00, 112), (0.21, 104), (0.42, 100), (0.60, 112)):
        if kind == "glide":
            track.sweep(S(t), -768)          # start an octave low, glide up over the note
        track.note(S(t), key, min(127, vel + boost), S(0.19))


def stepped_expression(track, points):
    for t, v in points:
        track.expr(S(t), v)


# ---------------------------------------------------------------- recipes


def psychic(ar, assets):
    sine = assets.baked("sine", sine_loop)
    chimes = assets.baked("chimes", calm_mind_chimes)
    layers = {}

    # take 1: opening glides on the sine, the Calm Mind chimes sweeping darker from 0.70 s, a faint high tail
    t = Track(program=0, volume=110, mono=True)
    opening(t, 43, "glide")
    t.adsr(S(0.70), r=116)                                      # ~280 Hz
    t.lfo(S(0.70), 24, 22, 0)                                    # warble under the chimes
    t.note(S(0.70), 38, 60, S(0.95))                             # low hum ~200 Hz
    for k in range(6):
        t.pan_to(S(0.70 + 0.18 * k), 24 if k % 2 else 104)       # heavy left / right
    layers["P1A"] = dict(bank=[sine], defs=[(0, 0, 60, 127, 127, 127, 118)], tracks=[t], end=2.2)
    c = Track(program=0, volume=120, mono=True)
    c2 = Track(program=1, volume=116, mono=True)
    seq = [(0.70, c, 0, 60, 127), (0.86, c2, 1, 60, 112), (0.98, c, 1, 62, 104), (1.12, c2, 2, 60, 96),
           (1.20, c, 2, 63, 88), (1.29, c2, 2, 60, 80), (1.55, c, 0, 67, 64), (1.75, c2, 0, 67, 48)]
    for tt, tr, prog, key, vel in seq:                           # 1.55 / 1.75: the faint high tail
        tr.note(S(tt), key, vel, S(0.34), program=prog)
    layers["P1B"] = dict(bank=[chimes], defs=[(0, i, 60, 127, 127, 127, 116) for i in range(3)],
                         tracks=[c, c2], end=2.2)

    # take 2: sharp chime at 0.00 over the hum's start; chimes 0.31-0.94 s sweeping darker; from 1.3 s the wavy hum
    h = Track(program=0, volume=86, mono=True)
    h.adsr(0, r=118)
    h.bend_range(0, 2)
    h.lfo(0, 40, 20, 0)
    h.note(0, 41, 112, S(1.95))                                  # ~258 Hz
    for k in range(13):
        h.pan_to(S(0.18 * k), 16 if k % 2 else 112)              # heavily left / right, both ways
    stepped_expression(h, [(0.20, 76), (1.30, 112), (1.55, 96), (1.75, 72), (1.90, 52)])
    for k, b in enumerate((0, -16, -32, -48, -64)):              # dominant drifts down 258 -> ~200 Hz
        h.bend(S(1.3 + 0.2 * k), b)
    layers["P2A"] = dict(bank=[sine], defs=[(0, 0, 60, 127, 127, 127, 110)], tracks=[h], end=2.5)
    a = Track(program=0, volume=127, mono=True)
    b = Track(program=1, volume=120, mono=True)
    for tt, tr, prog, key, vel in ((0.00, a, 0, 60, 127), (0.31, b, 0, 62, 116), (0.45, a, 1, 60, 108),
                                   (0.60, b, 1, 63, 100), (0.72, a, 2, 60, 92), (0.94, b, 2, 58, 82)):
        tr.note(S(tt), key, vel, S(0.34), program=prog)
    layers["P2B"] = dict(bank=[chimes], defs=[(0, i, 60, 127, 127, 127, 116) for i in range(3)],
                         tracks=[a, b], end=1.5)
    return layers, {"1": ["P1A", "P1B"], "2": ["P2A", "P2B"]}


def misty(ar, assets):
    whoosh = assets.baked("whoosh", mist_whoosh)
    charm = 1682              # Charm's low tone loop (vanilla wave archive, no new data)
    wish = 1466               # Wish's sparkle chime (vanilla)
    layers = {}

    o = Track(program=0, volume=110, mono=True)
    opening(o, 60, "glide")
    o.adsr(S(0.60), r=125)                                      # 222 Hz
    layers["M1A"] = dict(bank=[charm], defs=[(0, 0, 60, 127, 127, 127, 116)], tracks=[o], end=1.0)

    w = Track(program=1, volume=118, pan=30, mono=True)
    w.adsr(0, a=118, r=116)
    w.note(S(0.62), 60, 120, S(1.45))
    for k in range(10):                                          # pan drifts -0.35 -> 0 between 0.6 and 1.5 s
        w.pan_to(S(0.6 + 0.1 * k), 30 + int(34 * k / 9))
    stepped_expression(w, [(0.62, 127), (1.0, 112), (1.4, 90), (1.6, 70), (1.8, 50), (1.95, 36)])
    layers["M1B"] = dict(bank=[whoosh], defs=[(0, 0, 60, 127, 127, 127, 118), (0, 1, 60, 118, 127, 127, 100)],
                         tracks=[w], end=2.5)

    ch_a = Track(program=0, volume=110, pan=34, mono=True)
    ch_b = Track(program=0, volume=110, pan=44, mono=True)
    for k, (tt, vel) in enumerate(((0.67, 120), (0.77, 104), (0.92, 92), (1.02, 80), (1.15, 70), (1.26, 60),
                                   (1.36, 52), (1.50, 44))):
        (ch_a if k % 2 == 0 else ch_b).note(S(tt), 67, vel, S(0.30))
    for tr in (ch_a, ch_b):
        tr.adsr(0, a=116, r=125)                                 # attack slowed, as asked
        for k in range(10):
            tr.pan_to(S(0.6 + 0.1 * k), tr.pan + int((64 - tr.pan) * k / 9))
    layers["M1C"] = dict(bank=[wish], defs=[(0, 0, 60, 116, 127, 127, 104)], tracks=[ch_a, ch_b], end=2.5)

    # take 2: bright attack 0-0.15 s (burst + first chime), breathy body to 1.2 s, decay to 2.1 s; decaying echoes
    w2 = Track(program=0, volume=120, mono=True)
    w2.note(0, 60, 120, S(0.14))
    w2.adsr(S(0.12), a=120, r=110)
    w2.at(S(0.12), [0x81, 1])
    w2.note(S(0.12), 60, 124, S(1.45))
    stepped_expression(w2, [(0.12, 127), (0.6, 116), (1.0, 100), (1.25, 78), (1.45, 60), (1.7, 46), (1.9, 36)])
    layers["M2A"] = dict(bank=[whoosh], defs=[(0, 0, 60, 127, 127, 127, 118), (0, 1, 60, 120, 127, 127, 100)],
                         tracks=[w2], end=2.3)
    e_a = Track(program=0, volume=118, mono=True)               # one echo track: the pad takes the 4th voice
    for k, (tt, vel) in enumerate(((0.00, 124), (0.18, 106), (0.36, 92), (0.54, 80), (0.72, 70), (0.90, 60),
                                   (1.08, 52), (1.26, 44))):
        e_a.note(S(tt), 67 if k % 3 else 72, vel, S(0.30))
    e_a.adsr(0, a=116, r=125)
    layers["M2B"] = dict(bank=[wish], defs=[(0, 0, 60, 116, 127, 127, 104)], tracks=[e_a], end=2.2)
    pad = Track(program=0, volume=96)
    pad.adsr(0, a=112, r=114)
    pad.lfo(0, 16, 18, 1)                                        # slow breathing on the volume
    pad.note(S(0.22), 48, 110, S(1.05))                          # Charm's tone an octave down: the low body
    layers["M2C"] = dict(bank=[charm], defs=[(0, 0, 60, 112, 127, 127, 114)], tracks=[pad], end=2.2)
    return layers, {"1": ["M1A", "M1B", "M1C"], "2": ["M2A", "M2B", "M2C"]}


def grassy(ar, assets):
    rustle = assets.baked("rustle", leaf_rustle)
    synthesis = 1490          # Synthesis' warm chime (vanilla)
    ping = 1466               # Giga Drain's closing ping (Wish's sample, vanilla)
    layers = {}

    g = Track(program=0, volume=127, mono=True)
    opening(g, 53, "burst", boost=20)
    g.adsr(S(0.60), r=125)                                      # Synthesis 7 semitones down: woody bloom
    layers["G1A"] = dict(bank=[synthesis], defs=[(0, 0, 60, 127, 127, 127, 112)], tracks=[g], end=1.4)
    r = Track(program=0, volume=124, mono=True)
    r.adsr(0, r=127)                                             # noise bursts: hard cut
    r.bend_range(0, 4)
    for k, tt in enumerate((0.62, 0.70, 0.76, 0.83, 0.92)):
        r.random_bend(S(tt), -64, 64)
        r.pan_to(S(tt), 30 if k % 2 else 64)
        r.note(S(tt), 60, 124 - 10 * k, S(0.12))
    r.bend(S(1.0), 0)
    r.adsr(S(1.0), r=110)
    r.at(S(1.0), [0x81, 1])
    r.note(S(1.0), 60, 70, S(0.9))
    stepped_expression(r, [(1.0, 90), (1.5, 70), (1.8, 50)])
    layers["G1B"] = dict(bank=[rustle], defs=[(0, 0, 60, 127, 127, 127, 124), (0, 1, 60, 124, 127, 127, 108)],
                         tracks=[r], end=2.2)
    p = Track(program=0, volume=112, mono=True)
    for k, tt in enumerate((0.70, 0.85, 1.00, 1.15, 1.30, 1.45, 1.60, 1.75)):
        p.note(S(tt), 72, 120 - 8 * k, S(0.14))
    layers["G1C"] = dict(bank=[ping], defs=[(0, 0, 60, 127, 127, 127, 112)], tracks=[p], end=2.2)

    # take 2: punchy rustle at 0.00, the drain ping's 7.7 kHz band 0.2-1.0 s, noisy tail to 1.9 s, subtle low chime
    r2 = Track(program=0, volume=124, mono=True)
    r2.adsr(0, r=127)
    r2.bend_range(0, 4)
    for k, tt in enumerate((0.00, 0.06, 0.11)):
        r2.random_bend(S(tt), -48, 48)
        r2.note(S(tt), 60, 127 - 12 * k, S(0.12))
    tail = Track(program=1, volume=110)
    tail.adsr(0, a=110, r=112)
    tail.note(S(0.70), 60, 96, S(1.1))
    stepped_expression(tail, [(0.70, 40), (0.80, 64), (0.90, 88), (1.0, 104), (1.3, 82), (1.55, 60), (1.75, 42)])
    layers["G2A"] = dict(bank=[rustle], defs=[(0, 0, 60, 127, 127, 127, 124), (0, 1, 60, 124, 127, 127, 108)],
                         tracks=[r2, tail], end=2.0)
    p2 = Track(program=0, volume=118, mono=True)
    for k, (tt, key) in enumerate(((0.20, 72), (0.36, 72), (0.52, 74), (0.68, 72), (0.84, 76))):
        p2.note(S(tt), key, 124 - 9 * k, S(0.15))
    layers["G2B"] = dict(bank=[ping], defs=[(0, 0, 60, 127, 127, 127, 112)], tracks=[p2], end=1.6)
    s2 = Track(program=0, volume=96)
    s2.note(S(0.95), 57, 64, S(0.5))                             # Synthesis 3 semitones down, quiet
    layers["G2C"] = dict(bank=[synthesis], defs=[(0, 0, 60, 127, 127, 127, 110)], tracks=[s2], end=1.9)
    return layers, {"1": ["G1A", "G1B", "G1C"], "2": ["G2A", "G2B", "G2C"]}


def electric(ar, assets):
    thunder_wave = 1517       # Thunder Wave's static (vanilla, loops)
    charge = 1403             # Charge's modulating hum (vanilla, loops)
    spark = 1453              # Spark's zap (vanilla, loops)
    layers = {}

    def crackles(track, start, end, gap, vel0, vel1):
        """Staccato static: rapid retriggers at random pitch (live random pitch bend), strictly alternating L / R."""
        n = int((end - start) / gap)
        for k in range(n):
            tt = start + k * gap
            track.random_bend(S(tt), -72, 72)
            track.pan_to(S(tt), 0 if k % 2 == 0 else 127)
            track.note(S(tt), 62, int(vel0 + (vel1 - vel0) * k / max(1, n - 1)), max(2, S(gap * 0.7)))

    h = Track(program=0, volume=127, mono=True)
    opening(h, 48, "glide", boost=20)
    h.adsr(S(0.60), r=118)
    layers["E1A"] = dict(bank=[charge], defs=[(0, 0, 60, 127, 127, 127, 114)], tracks=[h], end=1.0)
    c = Track(program=0, volume=118, mono=True)
    c.adsr(0, r=127)                                             # noise: a hard cut does not click
    c.bend_range(0, 12)
    crackles(c, 0.62, 1.05, 0.045, 120, 96)
    s = Track(program=0, volume=112, mono=True)
    s.adsr(0, r=112)
    s.transpose(0, 5)
    s.note(S(1.05), 60, 110, S(0.9))
    stepped_expression(s, [(1.05, 127), (1.4, 104), (1.7, 80), (1.9, 60)])
    layers["E1B"] = dict(bank=[thunder_wave], defs=[(0, 0, 60, 127, 127, 127, 116)], tracks=[c, s], end=2.2)
    z = Track(program=0, volume=120, mono=True)
    z.adsr(0, r=124)
    z.note(S(0.70), 60, 120, S(0.22))
    layers["E1C"] = dict(bank=[spark], defs=[(0, 0, 60, 127, 127, 127, 110)], tracks=[z], end=1.4)

    # take 2: impact zap + crackle run 0-0.35 s, sustained static buzz with Charge's hum under it to 1.1 s, then the
    # level steps down (1.2 / 1.3 / 1.5 s) as in the reference
    c2 = Track(program=0, volume=120, mono=True)
    c2.adsr(0, r=127)
    c2.bend_range(0, 12)
    crackles(c2, 0.0, 0.36, 0.04, 124, 100)
    crackles(c2, 0.40, 1.15, 0.11, 88, 70)
    b = Track(program=0, volume=110, mono=True)
    b.adsr(0, a=112, r=116)
    b.transpose(0, 4)
    b.lfo(0, 20, 60, 1)                                          # volume flutter
    b.note(S(0.05), 60, 112, S(1.55))
    steps = [(0.05, 127), (1.18, 72), (1.25, 44), (1.48, 26)]
    stepped_expression(b, steps)
    layers["E2A"] = dict(bank=[thunder_wave], defs=[(0, 0, 60, 127, 127, 127, 116)], tracks=[c2, b], end=1.9)
    hm = Track(program=0, volume=78, mono=True)
    hm.adsr(0, a=112, r=116)
    hm.lfo(0, 60, 40, 0)                                         # modulating hum
    hm.note(S(0.05), 60, 110, S(1.55))
    stepped_expression(hm, steps)
    layers["E2B"] = dict(bank=[charge], defs=[(0, 0, 60, 127, 127, 127, 100)], tracks=[hm], end=1.9)
    z2 = Track(program=0, volume=124, mono=True)
    z2.adsr(0, r=124)
    z2.note(0, 64, 124, S(0.18))
    layers["E2C"] = dict(bank=[spark], defs=[(0, 0, 60, 127, 127, 127, 112)], tracks=[z2], end=0.8)
    return layers, {"1": ["E1A", "E1B", "E1C"], "2": ["E2A", "E2B", "E2C"]}


TERRAINS = {"psychic": psychic, "misty": misty, "grassy": grassy, "electric": electric}
