#!/usr/bin/env python3
"""Build the terrain sound effects into the ROM's sound archive (docs/megab2w2-integration.md, "Terrain sounds").

Reads the base ROM's data/swan_sound_data.sdat, appends the recipes' sequences, banks and wave archives
(recipes.py: donor sounds from the same archive, offline bakes, live sequences) after the last vanilla entry, and
writes the result for the ROM builder (vfs/data/swan_sound_data.sdat). Vanilla entries are not touched: the output is
checked to hold the base archive's every sequence, bank and wave archive byte for byte.

The new sequence IDs are fixed by the recipe order and must match what the game uses:
- include/w2u_terrain_sfx.h: the take-2 IDs the terrain code plays at a terrain's start message;
- the four terrain move scripts (data/graphics/move_animations): their take-1 PlaySound commands.
A mismatch, a changed base archive or an SE over the SE player's 10,200-byte heap fails the build.

usage: build_terrain_sfx.py --sdat BASE.sdat --output OUT.sdat --header include/w2u_terrain_sfx.h
                            --scripts data/graphics/move_animations [--stamp FILE]
"""
import argparse
import re
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from sfxlib import Archive, build_sseq, seconds   # noqa: E402
import recipes                                     # noqa: E402

VANILLA_SEQUENCES = 2416          # base archive: sequences 0..2415 (2415 = SEQ_SE_END)
SE_HEAP = 10200                   # PLAYER_SE_1 / SE_2 / SE_3 heap: sequence + bank + wave archives
SCRIPTS = {"electric": 604, "grassy": 580, "misty": 581, "psychic": 624}   # Psychic Terrain 678 plays member 624
PLAY_SOUND = 52


def build(base: Path):
    ar = Archive(base)
    if ar.first_seq != VANILLA_SEQUENCES:
        raise SystemExit(f"base archive has {ar.first_seq} sequences, expected {VANILLA_SEQUENCES}: not the vanilla "
                         "White 2 sound archive")
    assets = recipes.Assets(ar)
    ids = {}
    for terrain, fn in recipes.TERRAINS.items():
        layers, takes = fn(ar, assets)
        for take, names in takes.items():
            for i, name in enumerate(names):
                spec = layers[name]
                bank = ar.add_bank(f"BANK_SE_W2U_TERRAIN_{name}", spec["bank"], spec["defs"])
                raw = build_sseq(spec["tracks"], seconds(spec["end"]))
                ids[name] = ar.add_sequence(f"SEQ_SE_W2U_TERRAIN_{name}", raw, bank, player=recipes.PLAYERS[i])
                size = ar.se_bytes(ids[name])
                if size > SE_HEAP:
                    raise SystemExit(f"{name}: {size} bytes > the {SE_HEAP}-byte SE heap")
            ids[(terrain, take)] = [ids[n] for n in names]
    return ar, ids


def header_ids(header: Path):
    """{(terrain, slot): id} from W2U_TERRAIN_SFX_<TERRAIN>_APPLY_<n> defines."""
    out = {}
    for m in re.finditer(r"#define W2U_TERRAIN_SFX_(\w+)_APPLY_(\d) (\d+)u?", header.read_text()):
        out[(m.group(1).lower(), int(m.group(2)))] = int(m.group(3))
    return out


def script_sound_ids(path: Path):
    """PlaySound sequence IDs of a single-entry B2W2 move script, in order."""
    from_cmds = []
    data = path.read_bytes()
    count = struct.unpack_from("<I", data, 0)[0]
    cur = struct.unpack_from("<I", data, 4)[0]
    sizes = command_sizes()
    while cur + 2 <= len(data):
        op = struct.unpack_from("<H", data, cur)[0]
        n = sizes[op]
        if op == PLAY_SOUND:
            from_cmds.append(struct.unpack_from("<i", data, cur + 2)[0])
        cur += 2 + 4 * n
        if op in (71, 77):
            break
    assert count >= 1
    return from_cmds


def command_sizes():
    """Parameter count of every move-script opcode 0..77 (Pokeweb-Serverless B2W2_MOVSCRCMD.s; all 32-bit)."""
    return dict(enumerate([5, 10, 6, 6, 2, 0, 1, 11, 15, 11, 10, 1, 11, 13, 11, 13, 10, 10, 7, 9, 6, 7, 6, 6, 6, 4,
                           2, 5, 2, 2, 7, 1, 5, 8, 2, 1, 1, 6, 6, 2, 1, 6, 5, 2, 7, 7, 7, 7, 2, 5, 1, 2, 9, 1, 8,
                           9, 1, 1, 1, 4, 4, 3, 1, 1, 2, 3, 0, 7, 1, 6, 3, 0, 1, 0, 1, 1, 1, 0]))


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--sdat", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--header", type=Path, required=True)
    p.add_argument("--scripts", type=Path, required=True)
    p.add_argument("--stamp", type=Path)
    a = p.parse_args()

    base = a.sdat.read_bytes()
    ar, ids = build(a.sdat)

    errors = []
    want = header_ids(a.header)
    for terrain in recipes.TERRAINS:
        got = ids[(terrain, "2")]
        for slot in range(3):
            expected = got[slot] if slot < len(got) else 0
            if want.get((terrain, slot), None) != expected:
                errors.append(f"{a.header.name}: W2U_TERRAIN_SFX_{terrain.upper()}_APPLY_{slot} should be {expected}")
        script = a.scripts / f"5_{SCRIPTS[terrain]:08d}.bin"
        if script_sound_ids(script) != ids[(terrain, "1")]:
            errors.append(f"{script.name}: PlaySound IDs {script_sound_ids(script)}, expected take 1 "
                          f"{ids[(terrain, '1')]}")
    if errors:
        raise SystemExit("terrain sounds out of step:\n  " + "\n  ".join(errors))

    out = ar.sdat.save()
    import ndspy.soundArchive as SA
    vanilla, built = SA.SDAT(base), SA.SDAT(out)
    for kind in ("sequences", "banks", "waveArchives"):
        old, new = getattr(vanilla, kind), getattr(built, kind)
        for i, (o, n) in enumerate(zip(old, new)):
            same = o[0] == n[0] and (o[1] is None) == (n[1] is None)
            if same and o[1] is not None:
                same = o[1].save()[0] == n[1].save()[0]
            if not same:
                raise SystemExit(f"vanilla {kind} {i} changed")
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_bytes(out)
    print(f"terrain sounds: sequences {VANILLA_SEQUENCES}-{len(built.sequences) - 1}, "
          f"{len(out) - len(base)} bytes added to the sound archive")
    if a.stamp:
        a.stamp.write_text("ok\n")


if __name__ == "__main__":
    main()
