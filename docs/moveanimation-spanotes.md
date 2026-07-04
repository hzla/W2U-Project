Expanded move animation overrides for B2W2 `a/0/6/5`.

Animation workflow rule: all battle-animation visuals, particles, fades,
screen brightening, and animation timing must be authored in the game's
move-animation VM scripts and referenced SPA assets. C/C++ hooks may route a
custom animation, start it, wait for it, and perform gameplay or form-state
sync at safe points, but they should not implement visible animation effects or
multi-frame visual timing.

When copying donor particles for a recolor, inspect the donor SPA resource
color, texture/palette colors, child color, alpha animation, and especially
color animation curves. If the request is "particle X from move Y, but in
color Z", overwrite or remove the donor color animation curve as part of the
recolor; otherwise the original move's hidden color interpolation can tint the
new particle during scale/lifetime changes.

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

Mega Evolution's custom transform animation reserves slot `5_00000622.bin`.
It uses SolarBeam's first gathering script body from member `76`, redirected to
custom pink SPA `765`, with SolarBeam's yellow user-flash constants changed to
white, SolarBeam's opening background dimming made a no-op, and SolarBeam's
`PlaySound 1480, 2, 14, 0, 0, 100, 0, 0, 0` replaced by Spark's
`PlaySound 1483, 2, 14, 0, 0, 100, 0, 0, 0`. It then loads the intact pink
sphere SPA `767` and cracked pink sphere SPA `768` through the orthographic
`DoSPAAnimation2` path so the sphere plane does not depth-sort behind the
Pokemon sprite. During the intact sphere's expansion, it also loads
Mega tornado SPA `770` through the orthographic particle path, which clones
Leaf Tornado's user-side tornado and target-side spiral-wind motion, replaces
the leaves with smaller Shock Wave-style partial-alpha pink glow particles, and
tints the spiral wind dark pink. It also loads crack-beam SPA `771`, cloned
from Explosion texture/resource `6` and retuned to fixed bright white-pink
size/color, zero start delay, and only a clean alpha fade. The spiral wind starts at the same time as the
intact sphere and ramps through four VM spawns at safe fixed-point radius/scale
values (`3x`, `4x`, `5x`, then `5.5x`) at frames `0`, `30`, `70`, and `115`.
The wind blade expansion itself lives in SPA `770` resource `2`'s scale curve
(`1x -> 2.65x -> 5.05x`); avoid very large VM scale multipliers here because
the engine casts the computed emitter base scale to `fx16`, which can wrap and
make later spawns look unchanged. This keeps the first frame at the current
readable size while pushing the visible expansion into the SPA curve. To avoid scene-dependent dark/orange blending, the sphere
resources do not use color animation; the resource color is plain white and the
circle texels stay fully opaque. Alpha animation is used only for opacity:
`767` resource `1` scales up while fading in, `767` resource `2` starts at
frame `177` to cover the final-scale handoff and holds intact at full opacity
until the cracked sphere starts at frame `194`; `768` resource `1` holds
cracked at full opacity for roughly 1.25 seconds while SPA `771` emits
sequential beams from the user center starting two frames after the cracked
sphere appears; the first beam also plays
`PlaySound 1483, 2, 16, 0, 0, 80, 0, 0, 0`. Then `768` resource `2` expands slightly
while fading out with one final beam. The client hook refreshes the battler sprite
to its Mega form at frame `186`, while the full-opacity intact hold sphere is
already active, so the cracked sphere
fade-out reveals the Mega sprite directly without running the vanilla
form-change animation. The cracked fade-out also plays
`PlaySound 1504, 1, 14, 0, 0, 120, 0, 0, 0` and a light VM `ShakeScreen`.
Eight frames into that fade-out, the script spawns Mega symbol SPA `769`
above the user; the symbol fades in, drifts upward, and fades away as the
transformation completes. The full-size intact hold starts early enough to cover the expanding
particle's final-frame culling, and hold particles live longer than their
script waits, so adjacent sphere stages overlap instead of flickering blank. Do not add parallel sphere
spawns or child emitters unless the in-battle centering has been revalidated.
Dragon Darts reserves slot `5_00000623.bin`. It is generated from Twineedle's
move script, with every `LoadSPA` and `DoSPA*` reference redirected from
Twineedle SPA `206` to custom Dragon Darts SPA `776`. The sequence keeps
Twineedle's two projectile launches, waits, target freeze, target shake, and
sounds, but the projectile particles in SPA `776` use the custom 64x64 dart
texture instead of Twineedle's needle texture. The earlier Flash/whiteout
fade-back helper that used this slot is retired; Mega animations should not
append Flash snippets unless a future visual pass explicitly reintroduces them
through the VM script.

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

Hyperspace Hole (`5_00000593.bin`) is generated from Dark Void's portal/sink
sequence and Shadow Punch's hit. It swaps Dark Void's background `192` for
background `126`, opens Dark Void SPA `644` at the user's platform, applies the
Dark Void sink/visibility commands to the user sprite selector, opens the same
portal at the target without running Dark Void's target-drag commands, plays
Shadow Punch SPA `499` and target distortion, closes the target portal, then
reopens the user-side portal and restores the user sprite/shadow before fading
the background out.

Hyperspace Fury (`5_00000621.bin`) follows the same Dark Void-based user
vanish/reappear flow as Hyperspace Hole, also using background `126` and Dark
Void SPA `644`. After the user sinks into the portal, it opens five offset Dark
Void portal groups around target selector `11` instead of one target-foot
portal, then plays Close Combat's impact particles from SPA `549` plus the
target freeze/shake/distortion before closing all five target portals and
returning the user.

Thousand Arrows (`5_00000614.bin`) is generated from Water Spout's user-side
spouting motion and Rain Dance's screen-wide rain motion. The script dims the
screen at startup, opens with two short user-side spout bursts from custom arrow
SPA `772`, and schedules several staggered `PlaySound 1560` calls so the launch
reads as many arrows being fired. It then shifts to the target camera, plays a
slight target-side sprite shake, and starts green Rain Dance rain from SPA `773`
before restoring the background color. Water Spout's target-side falling and
broad splash resources are not used.

Thousand Waves (`5_00000615.bin`) is generated from Aurora Beam's animation
script. It keeps Aurora Beam's projectile cadence, sounds, background-color
dim/restore, target camera, target shake, and target freeze timing, but redirects
the particles from Aurora Beam SPA `227` to custom hexagon SPA `774`.

`tools/import_move_animations_from_rom.py` imports replacement-map animations
from donor ROMs into these per-move override files. For example, the Blaze
Black 2 Redux map in `import_maps/bb2redex14.json` copies donor vanilla move
members into matching Gen 6 move IDs while skipping later-generation targets.
