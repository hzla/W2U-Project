Expanded move animation overrides for B2W2 `a/0/6/5`.

Files are named by their destination animation index. For Gen 6 move IDs
`560..621`, W2U starts battle-view move animations with `moveID + 115` so the
vanilla loader does not treat the ID as a fixed battle-effect animation, then
the loader hook subtracts `115` and reads the real per-move file here.

The initial files are clones of each move's `Move Animation ID` source from
`data/pml/moves/*.yml`. Future custom animation work should edit the destination
file directly, for example `5_00000573.bin` for Freeze-Dry.

Terrain placeholders currently copy Aromatherapy (`5_00000312.bin`) into
Grassy Terrain's slot `5_00000580.bin`, Mist (`5_00000054.bin`) into Misty
Terrain's slot `5_00000581.bin`.

Electric Terrain (`5_00000604.bin`) is generated from Discharge with the
target-camera hit section removed and a custom floor spark SPA installed at
`/a/0/0/6` member `742`.

Topsy-Turvy (`5_00000576.bin`) is generated from Psychic's background sequence
and rotates the field sprite selector upside down and back.

Trick-or-Treat (`5_00000567.bin`) is generated from Razor Leaf's opening emitter
with a custom transparent ghost texture in SPA `762`; upright ghosts rise from
the target and continue upward offscreen.

Venom Drench (`5_00000599.bin`) is generated from Water Sport's animation with
its referenced particle archive hue-shifted purple in SPA `763`.

Water Shuriken (`5_00000594.bin`) is generated from Octazooka's single-projectile
path with a custom transparent `blueshuriken.png` texture in SPA `764`, firing
one straight-line projectile per multi-hit playback with no target camera
zoom/shake. The projectile speed is reduced to 75%, and the shuriken lifetime
is timed to end at target contact before
using only Razor Shell's circular white/blue impact particles from SPA `703`.

`tools/import_move_animations_from_rom.py` imports replacement-map animations
from donor ROMs into these per-move override files. For example, the Blaze
Black 2 Redux map in `import_maps/bb2redex14.json` copies donor vanilla move
members into matching Gen 6 move IDs while skipping later-generation targets.
