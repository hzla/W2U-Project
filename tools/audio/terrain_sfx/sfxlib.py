"""Terrain sound effects (tools/audio/terrain_sfx): build new SDAT entries (sequences, banks, wave archives) from
B2W2's own sound archive.

Everything is derived from swan_sound_data.sdat: donor waves are decoded, optionally baked offline (trim, fades,
time-varying low-pass sweep, resample, seamless loops), re-encoded as DS IMA-ADPCM; sequences are written as raw SSEQ
bytes from a small event schedule (notes, pan, volume, vibrato, sweeps, random pitch bend). Vanilla entries are never
modified: new ones are appended after the last vanilla sequence / bank / wave archive.
"""
from dataclasses import dataclass, field
from pathlib import Path
import math
import struct

import numpy as np
from scipy import signal
import ndspy.soundArchive as SA
import ndspy.soundBank as SB
import ndspy.soundSequence as SS
import ndspy.soundWave as SW
import ndspy.soundWaveArchive as SWA

ARM7_TIMER = 16756991          # SWAV `time` = ARM7 bus clock / 2 / rate
TICKS_PER_SECOND = 191.95      # tempo 240: one tick per sequencer update (64 * 2728 / 33513982 s)
TEMPO = 240


def seconds(t):
    return int(round(t * TICKS_PER_SECOND))


# ---------------------------------------------------------------- waves


def decode_swav(swav):
    data = bytes(swav.data)
    if swav.waveType == 0:
        return np.frombuffer(data, dtype=np.int8).astype(np.float64) / 128.0
    if swav.waveType == 1:
        return np.frombuffer(data, dtype="<i2").astype(np.float64) / 32768.0
    return adpcm_decode(data)


STEPS = [7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97,
         107, 118, 130, 143, 157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724,
         796, 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327, 3660, 4026,
         4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500,
         20350, 22385, 24623, 27086, 29794, 32767]
INDEX = [-1, -1, -1, -1, 2, 4, 6, 8]


def adpcm_decode(data):
    pred = int.from_bytes(data[0:2], "little", signed=True)
    idx = min(max(data[2], 0), 88)
    out = []
    for b in data[4:]:
        for nib in (b & 15, b >> 4):
            pred, idx = _adpcm_step(pred, idx, nib)
            out.append(pred)
    return np.array(out, dtype=np.float64) / 32768.0


def _adpcm_step(pred, idx, nib):
    step = STEPS[idx]
    diff = step >> 3
    if nib & 1:
        diff += step >> 2
    if nib & 2:
        diff += step >> 1
    if nib & 4:
        diff += step
    pred = max(-32767, pred - diff) if nib & 8 else min(32767, pred + diff)
    return pred, min(max(idx + INDEX[nib & 7], 0), 88)


def adpcm_encode(x):
    """DS IMA-ADPCM: 4-byte header (predictor s16, index u8, 0), then nibbles low first. Greedy best-nibble search
    with the decoder's own arithmetic, so encoder and DS decoder never drift."""
    pcm = np.clip(np.round(np.asarray(x) * 32767), -32767, 32767).astype(int)
    if len(pcm) % 2:
        pcm = np.append(pcm, 0)
    pred, idx = int(pcm[0]), 0
    # start index near the signal's first step size
    first = np.abs(np.diff(pcm[:64])).mean() if len(pcm) > 64 else 0
    while idx < 88 and STEPS[idx] < first:
        idx += 1
    head = struct.pack("<hBB", pred, idx, 0)
    out = bytearray(head)
    nibs = []
    for s in pcm:
        best = None
        for nib in range(16):
            p, i = _adpcm_step(pred, idx, nib)
            err = abs(p - s)
            if best is None or err < best[0]:
                best = (err, nib, p, i)
        _, nib, pred, idx = best
        nibs.append(nib)
    for a, b in zip(nibs[0::2], nibs[1::2]):
        out.append(a | (b << 4))
    return bytes(out)


def make_swav(x, rate, loop_start=None):
    """IMA-ADPCM SWAV. `loop_start` (samples) must be a multiple of 8; the loop runs to the end."""
    n = len(x)
    pad = (-n) % 8
    x = np.concatenate([x, np.zeros(pad)]) if pad else x
    data = adpcm_encode(x)
    sw = SW.SWAV()
    sw.waveType = 2
    sw.isLooped = loop_start is not None
    sw.sampleRate = int(rate)
    sw.time = ARM7_TIMER // int(rate)
    sw.loopOffset = 1 + (loop_start // 8 if loop_start is not None else 0)
    sw.totalLength = len(data) // 4
    sw.data = data
    return sw


# ---------------------------------------------------------------- offline bakes


def resample(x, sr_in, sr_out):
    g = math.gcd(int(sr_in), int(sr_out))
    return signal.resample_poly(x, int(sr_out) // g, int(sr_in) // g)


def lowpass_sweep(x, sr, f_start, f_end, q=0.9, curve="exp", block=64):
    """4th-order Butterworth low-pass whose cutoff moves from f_start to f_end over the whole signal (64-sample
    blocks, filter state carried across blocks). `q` is kept for the recipes' call signature."""
    n = len(x)
    out = np.empty(n)
    zi = None
    for a in range(0, n, block):
        u = (a + block / 2) / max(1, n)
        fc = f_start * (f_end / f_start) ** u if curve == "exp" else f_start + (f_end - f_start) * u
        sos = signal.butter(4, min(fc, sr * 0.45), fs=sr, output="sos")
        if zi is None:
            zi = signal.sosfilt_zi(sos) * x[0]
        out[a:a + block], zi = signal.sosfilt(sos, x[a:a + block], zi=zi)
    return out


def fade(x, sr, fade_in=0.0, fade_out=0.0):
    x = x.copy()
    a, b = int(fade_in * sr), int(fade_out * sr)
    if a:
        x[:a] *= np.linspace(0, 1, a)
    if b:
        x[-b:] *= np.linspace(1, 0, b)
    return x


def normalize(x, peak=0.95):
    m = np.abs(x).max()
    return x * (peak / m) if m else x


def cycle_loop(x, sr, f0, start_s, cycles, out_rate=None):
    """A seamless loop of whole cycles cut from a tonal sample: `cycles` periods starting at `start_s`, resampled so
    the loop is a multiple of 8 samples (ADPCM block). Returns (samples, rate, loop_start=0)."""
    period = sr / f0
    a = int(start_s * sr)
    # start on a rising zero crossing
    z = np.nonzero((x[a:a + int(2 * period)] <= 0) & (np.roll(x[a:a + int(2 * period)], -1) > 0))[0]
    a += int(z[0]) if len(z) else 0
    seg = x[a:a + int(round(cycles * period)) + 1]
    target = int(round(len(seg) / 8.0)) * 8
    rate = out_rate or sr
    looped = signal.resample(seg[:-1], target)
    return looped, rate * target / (len(seg) - 1), 0


def noise_loop(x, sr, start_s, length_s, xfade_s=0.04):
    """A crossfaded loop for noisy material: the tail is blended into the head so the wrap is seamless."""
    a, n, xf = int(start_s * sr), int(length_s * sr), int(xfade_s * sr)
    n -= n % 8
    seg = x[a:a + n + xf].copy()
    w = np.linspace(0, 1, xf)
    head = seg[:xf] * w + seg[n:n + xf] * (1 - w)
    out = seg[:n].copy()
    out[:xf] = head
    return out


# ---------------------------------------------------------------- sequences


def varlen(v):
    v = int(v)
    out = [v & 0x7F]
    v >>= 7
    while v:
        out.append(0x80 | (v & 0x7F))
        v >>= 7
    return bytes(reversed(out))


@dataclass
class Track:
    """Commands at absolute ticks; compiled with rests in between. Notes never wait: the track runs in poly mode
    (the DS's mono mode makes every note wait for its duration, which would delay the commands after it). `mono`
    instead trims each note so it ends where the track's next note starts (one voice plus its release)."""
    program: int = 0
    volume: int = 127
    pan: int = 64
    priority: int | None = None
    mono: bool = False
    events: list = field(default_factory=list)      # (tick, order, bytes)

    def at(self, t, data, order=1):
        self.events.append((int(t), order, bytes(data)))
        return self

    def note(self, t, key, vel, dur, program=None):
        if program is not None:
            self.at(t, bytes([0x81]) + varlen(program), order=1)
        return self.at(t, bytes([key & 0x7F, vel & 0x7F]) + varlen(max(1, dur)), order=2)

    def pan_to(self, t, v):
        return self.at(t, [0xC0, max(0, min(127, int(v)))])

    def vol(self, t, v):
        return self.at(t, [0xC1, max(0, min(127, int(v)))])

    def expr(self, t, v):
        return self.at(t, [0xD5, max(0, min(127, int(v)))])

    def bend(self, t, v):                   # pitch bend, -128..127 of the bend range (semitones, set by bend_range)
        return self.at(t, [0xC4, int(v) & 0xFF])

    def bend_range(self, t, semis):
        return self.at(t, [0xC5, semis])

    def random_bend(self, t, lo, hi):       # 0xA0 random prefix on pitch bend: a new random value each time
        return self.at(t, [0xA0, 0xC4] + list(struct.pack("<hh", lo, hi)))

    def sweep(self, t, v):                  # sweep pitch (1/64 semitone) applied from the next note's start
        return self.at(t, [0xE3] + list(struct.pack("<h", int(v))))

    def transpose(self, t, v):
        return self.at(t, [0xC3, int(v) & 0xFF])

    def lfo(self, t, depth, speed, kind=0, rng=1, delay=0):
        """Modulation: kind 0 pitch (vibrato), 1 volume, 2 pan."""
        return self.at(t, [0xCC, kind, 0xCA, depth, 0xCB, speed, 0xCD, rng, 0xE0] + list(struct.pack("<H", delay)))

    def adsr(self, t, a=None, d=None, s=None, r=None):
        out = []
        for code, v in ((0xD0, a), (0xD1, d), (0xD2, s), (0xD3, r)):
            if v is not None:
                out += [code, v]
        return self.at(t, out)

    def portamento(self, t, from_key, time):
        return self.at(t, [0xCE, 1, 0xC9, from_key, 0xCF, time])

    def portamento_off(self, t):
        return self.at(t, [0xCE, 0])

    def compile(self, end_tick):
        head = bytearray([0xC7, 0, 0x81]) + varlen(self.program)
        head += bytes([0xC1, self.volume, 0xC0, self.pan, 0xD5, 127])
        if self.mono:
            head += bytes([0xD3, 125])          # retriggered: fast release (63 ms); the sample's decay is the tail
        if self.priority is not None:
            head += bytes([0xC6, self.priority])
        body = bytearray()
        now = 0
        events = sorted(self.events, key=lambda e: (e[0], e[1]))
        if self.mono:
            starts = [t for t, order, _ in events if order == 2]
            trimmed = []
            for t, order, data in events:
                if order == 2:
                    later = [s for s in starts if s > t]
                    dur = note_duration(data)
                    if later and t + dur > later[0]:
                        data = data[:2] + varlen(max(1, later[0] - t))
                trimmed.append((t, order, data))
            events = trimmed
        for t, _, data in events:
            if t > now:
                body += b"\x80" + varlen(t - now)
                now = t
            body += data
        if end_tick > now:
            body += b"\x80" + varlen(end_tick - now)
        return bytes(head + body + b"\xFF")


def note_duration(data):
    dur = 0
    for b in data[2:]:
        dur = (dur << 7) | (b & 0x7F)
    return dur


def build_sseq(tracks, end_tick):
    """Raw SSEQ file: alloc tracks, open 1..n-1, tempo, track 0 inline."""
    n = len(tracks)
    mask = (1 << n) - 1
    bodies = [t.compile(end_tick) for t in tracks]
    pre = bytearray(struct.pack("<BH", 0xFE, mask))
    open_len = 5 * (n - 1)
    tempo = bytes([0xE1]) + struct.pack("<H", TEMPO)
    # layout: alloc, opens, [track0: tempo + body], track1, ...
    t0 = len(pre) + open_len
    offsets = []
    pos = t0 + len(tempo) + len(bodies[0])
    for b in bodies[1:]:
        offsets.append(pos)
        pos += len(b)
    for k, off in enumerate(offsets, 1):
        pre += bytes([0x93, k]) + struct.pack("<I", off)[:3]
    data = bytes(pre) + tempo + b"".join(bodies)
    data += b"\x00" * ((-len(data)) % 4)
    size = 0x1C + len(data)
    head = b"SSEQ" + struct.pack("<HHIHH", 0xFEFF, 0x0100, size, 0x10, 1)
    block = b"DATA" + struct.pack("<II", 0x0C + len(data), 0x1C)
    return head + block + data


# ---------------------------------------------------------------- archive


class Archive:
    """The vanilla SDAT plus appended entries."""

    def __init__(self, path):
        self.path = Path(path)
        self.sdat = SA.SDAT(self.path.read_bytes())
        self.first_seq = len(self.sdat.sequences)
        self.first_bank = len(self.sdat.banks)
        self.first_swar = len(self.sdat.waveArchives)

    def donor(self, swar, index=0):
        sw = self.sdat.waveArchives[swar][1].waves[index]
        return decode_swav(sw), sw.sampleRate, sw

    def swar_bytes(self, swar):
        return len(self.sdat.waveArchives[swar][1].save()[0])

    def add_swar(self, name, swavs):
        ar = SWA.SWAR()
        ar.waves = list(swavs)
        self.sdat.waveArchives.append((name, ar))
        return len(self.sdat.waveArchives) - 1

    def add_bank(self, name, swar_ids, notedefs):
        """notedefs: [(slot, wave_index, root_key, attack, decay, sustain, release)] (pan 64, PCM): one instrument
        each, program = list index."""
        bank = SB.SBNK(waveArchiveIDs=list(swar_ids))
        bank.instruments = [SB.SingleNoteInstrument(SB.NoteDefinition(w, slot, root, a, d, s, r, 64, SB.NoteType.PCM))
                            for slot, w, root, a, d, s, r in notedefs]
        self.sdat.banks.append((name, bank))
        return len(self.sdat.banks) - 1

    def add_sequence(self, name, raw, bank, volume=110, channel_priority=104, player_priority=64, player=2):
        seq = SS.SSEQ(raw, bankID=bank, volume=volume, channelPressure=channel_priority,
                      polyphonicPressure=player_priority, playerID=player)
        self.sdat.sequences.append((name, seq))
        return len(self.sdat.sequences) - 1

    def se_bytes(self, seq_id):
        """Sequence + bank + every wave archive it loads: what the SE player's 10,200-byte heap must hold."""
        _, seq = self.sdat.sequences[seq_id]
        bank = self.sdat.banks[seq.bankID][1]
        total = len(seq.save()[0]) + len(bank.save()[0])
        for w in set(bank.waveArchiveIDs):
            if w < len(self.sdat.waveArchives):
                total += len(self.sdat.waveArchives[w][1].save()[0])
        return total

    def save(self, out):
        Path(out).write_bytes(self.sdat.save())
