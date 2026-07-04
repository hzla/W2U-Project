Custom move particle archives for B2W2 `/a/0/0/6`.

Files are named by their destination SPA archive index, matching `knarc`
unpack names. For example, `6_00000739.bin` becomes SPA `739` and can be
referenced from move animation scripts with `LoadSPA 739`.

Donor-particle recolor rule: when cloning a particle from an existing move,
account for every color source the donor may carry: resource color,
texture/palette colors, child color, alpha animation, and color animation
curves. For "use move Y's particle in color Z" work, remove or overwrite the
donor color animation curve if it is not intentionally part of the new effect;
leaving it in place can make the particle drift back toward the donor move's
colors during its lifetime.

Current generated SPA additions:
- `6_00000755.bin`: brown-tinted Shock Wave gathering particles for Land's
  Wrath, generated from SPA `528`.
- `6_00000756.bin`: flipped/reversed Quash hand particles for Mat Block,
  generated from SPA `681`.
- `6_00000757.bin`: dark red/black Solar Beam target beam particles for
  Oblivion Wing, generated from SPA `244`.
- `6_00000758.bin`: black Mega Drain absorption particles for Oblivion Wing,
  generated from SPA `237`.
- `6_00000759.bin`: Leaf Storm particles for Petal Blizzard, with projectile
  resources redirected to Petal Dance petals and impact colors shifted pink.
- `6_00000760.bin`: whitish-gray Sleep Powder particles for Powder, generated
  from SPA `247`.
- `6_00000761.bin`: Horn Drill particles for Rototiller, keeping the drills
  and recoloring only the small circular impact particles earth-brown while the
  large orange burst resources are omitted by the move script.
- `6_00000762.bin`: Razor Leaf particles for Trick-or-Treat, replacing the leaf
  texture with a downscaled transparent ghost texture, stripping child emitters
  and gravity-style behaviors, and retuning the target-side rising resource for
  upright upward-only motion.
- `6_00000763.bin`: Water Sport particles for Venom Drench, hue-shifting all
  resource colors, color animations, child colors, and texture palette/direct
  color data into purple venom tones.
- `6_00000764.bin`: Octazooka projectile resource for Water Shuriken, replacing
  the projectile texture with a downscaled transparent `blueshuriken.png`
  shuriken texture while timing the particle lifetime for the slower
  straight-line projectile to end at target contact during multi-hit playback.
- `6_00000765.bin`: SolarBeam gathering particles for Mega Evolution, cloned
  from SPA `243` and tinted pink.
- `6_00000766.bin`: Rapid Spin wind particles for Mega Evolution, cloned from
  SPA `399` and tinted dark pink.
- `6_00000767.bin`: intact pink Mega Evolution sphere texture, packed into
  Spark's SPA `379` layout so the move script can reuse Spark's centered
  expanding-circle behavior. Texture `1` uses the silhouette from
  `megasphere_128_lightpink.png`, but replaces the shaded source palette with a
  fixed flat light-pink fill plus border and forces every visible texel to
  maximum A5I3 alpha. Resources `1` and `2` use plain-white resource color,
  max DS particle alpha, and no color animation so the texture color does not
  drift while scaling. Resource `1` is retuned as a user-centered expanding
  particle with no child emitter, a 190-frame lifetime, alpha-only fade-in, and
  a doubled final scale for the larger Mega cover sphere. Resource `2` is a
  one-shot particle that holds the same full-size intact sphere at full opacity
  for 24 frames; the script starts it at frame `177` and advances after 17
  frames so it covers the final-scale handoff before overlapping cracked.
- `6_00000768.bin`: cracked pink Mega Evolution sphere texture, also packed
  into Spark's SPA `379` layout. Texture `1` uses
  `megasphere_128_lightpink_cracked_cleanjunction.png`, replacing the shaded
  source palette with the same flat light-pink fill plus border and bright
  crack pixels. Resources `1` and `2` also use plain-white resource color,
  max DS particle alpha, and no color animation. Resource `1` is a one-shot
  particle that holds the cracked sphere at full opacity for 50 frames; the
  script holds it for 38 frames while crack beams spawn, then advances with
  overlap. Resource `2` starts at the intact sphere's final scale and expands
  slightly larger with alpha-only fade-out.
- `6_00000769.bin`: Mega Evolution completion symbol particle, using a cropped
  64x64 direct-color Mega symbol texture. The source image's white interior
  pixels are converted to
  transparent pixels while the colored outline remains opaque. Resource `0` is
  a one-shot alpha-only particle with no color animation; it spawns above the
  user, drifts upward, and fades away over 58 frames.
- `6_00000770.bin`: Mega Evolution Leaf Tornado overlay, cloned from Leaf
  Tornado SPA `705`. Resource `1` keeps the user-side tornado motion but uses a
  much smaller bright-pink Shock Wave-style circular texture in place of
  leaves, with a larger radius and longer emitter life for the intact sphere
  expansion. Resource `3` is a matching softer Shock Wave glow layer behind
  resource `1`. Resource `2` keeps Leaf Tornado's spiral wind motion and
  partial-alpha texture shape, tints it dark pink, and uses a shortened emitter
  lifetime plus a stronger scale curve (`1.0x -> 2.65x -> 5.05x`). The VM
  script respawns it in four bounded radius/scale stages (`3x`, `4x`, `5x`,
  then `5.5x`) starting with the first intact sphere frame; do not use huge VM
  scale multipliers here because the engine's emitter base-scale setter casts
  through `fx16` and can wrap. Active resources remove donor color animation
  curves so the colors stay stable while alpha animation handles fade-out.
- `6_00000771.bin`: Mega Evolution crack beams, cloned from Explosion SPA
  `321`, resource/texture `6`. The beam texture is reused at its original
  64x64 size while the resource is scrubbed of donor color and scale animation
  curves, recolored bright white-pink, zeroed from Explosion's hidden 77-frame start delay, and given only a simple alpha fade. The
  Mega script emits these beams sequentially during the cracked sphere hold and
  once more as the cracked sphere fades.
- `6_00000772.bin`: Thousand Arrows launch particles, cloned from Water Spout
  SPA `497` resources `3` and `4` only. Every texture is replaced by the 64x64
  transparent green arrow texture from
  `codex-clipboard-f8080045-2086-4c0f-8ee6-99cad30f194b.png`. Donor resource
  colors are forced to white and donor color animation curves are removed so
  the arrow texture stays green. Water Spout's target-side falling resources and
  broad splash resource are intentionally omitted from this SPA.
- `6_00000773.bin`: Thousand Arrows falling rain, cloned from Rain Dance SPA
  `411`. The original screen-wide rain motion is kept, but the rain texture is
  recolored to the same green as the launch arrows. Donor color animation is
  removed and alpha animation is kept so the rain fades like Rain Dance without
  drifting back to white/blue.
- `6_00000774.bin`: Thousand Waves hexagon particles, cloned from Aurora Beam
  SPA `227`. Aurora Beam texture `0` is replaced with a solid filled hexagon
  using transparent outer pixels and a subtle glow/outline alpha shape. The two
  Aurora Beam projectile resources keep their original scale, alpha, draw type,
  and projectile timing, but the donor rainbow color animation is replaced with
  a green/light-green random color curve so the projectiles alternate between
  the two reference greens instead of blue, pink, and yellow.
- `6_00000775.bin`: Hyperspace Fury target portal variants, cloned from Dark
  Void SPA `644` through the Hyperspace portal gold-border pass. Texture `3`
  is recolored to gold `#dba423` with the original alpha mask preserved, and
  ring emitters are scrubbed to white so the gold texture is not re-tinted
  purple. It contains five duplicated portal resource groups with baked
  non-uniform X/Y offsets around the target, fixed per-group angles, and a
  `2/3x` target-portal scale so the Fury side portals are smaller than the
  shared user/target portal. This is used only for Fury's target-side portal
  ring.
- `6_00000776.bin`: Dragon Darts particles, cloned from Twineedle SPA `206`.
  Resource `1` keeps Twineedle's directional projectile motion but replaces
  projectile texture `1` with a 64x64 Dragon Darts A3I5 texture. Resource `1`
  is forced to plain white with no donor
  color animation or texture animation so the imported dart colors are not
  tinted by Twineedle's magenta needle settings. Resource `0` and texture `0`
  are kept intact for Twineedle's small impact/setup particle.
- `6_00000779.bin`: Hyperspace Hole/Fury shared portal SPA, cloned from Dark
  Void SPA `644` with texture `3` recolored to gold `#dba423` while preserving
  its alpha mask. Hole and Fury load this instead of vanilla `644` so their
  portal border can change without affecting Dark Void or other users of the
  original SPA.
- `6_00000777.bin`: Light of Ruin user-side gathering particles, cloned from
  Bolt Strike SPA `723`. Active user-gather resources `2`, `4`, `5`, and `9`
  are recolored to the Mega-style pink range and have Bolt Strike's yellow
  color animation curves overwritten. Resource `7` keeps Bolt Strike's
  gathering spark/electricity motion but is recolored pink, and resource `10`
  is a cloned copy of that spark resource recolored near-black so the move can
  spawn pink and black sparks together. Active spark/circle textures are
  normalized toward white so resource color controls the pink/black tint.
- `6_00000778.bin`: Light of Ruin cannon particles, cloned from Hydro Cannon
  SPA `479`. All textures are shifted toward the same Mega-style pink while
  preserving alpha and brightness, and all resource/child colors plus donor
  blue/purple color animation curves are replaced with light-pink to hot-pink
  curves for the firing projectiles and target burst.
- `6_00000780.bin`: Dragon Ascent giant meteor, generated from Draco Meteor
  SPA `613` motion and SPA `593` texture `3`. It keeps only one Draco Meteor
  falling resource, replaces the texture with a 45-degree neon-green flame
  texture while preserving brightness variation, removes donor color animation
  and child emitters, zeroes random scale/lifetime variance, and clamps the
  emitter to a true one-shot so Dragon Ascent drops one large meteor instead of
  the original multi-meteor shower.
- `6_00000781.bin`: Precipice Blades stalagmites, generated from Water Pledge
  SPA `688` geyser resources `7`, `8`, and `6` for their target-side left,
  right, then center base positions. Each resource replaces the donor geyser
  texture with a custom stalagmite texture, removes donor blue color animation,
  child emitters, motion variance, and behaviors. The rock spikes are retuned
  as one-shot particles roughly three times wider and five times taller than
  the first pass, with a narrower width/height aspect so their vertical scale
  reads stronger before fading.
- `6_00000782.bin`: Steam Eruption particles, cloned from Scald SPA `674`.
  Resources `0` and `1` preserve Scald's target-side steam puffs with explicit
  zero start delay and no behaviors. Scald stream resource `2` is cloned into
  two stream resources at indices `2` and `3`, with original base scale and
  emission radius, start positions baked slightly up-left and down-right, donor
  blue-white color/alpha animation intentionally preserved, and child
  color/texture settings kept so the emitted steam particles match Scald while
  reading as two parallel streams.
