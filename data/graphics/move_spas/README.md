Custom move particle archives for B2W2 `/a/0/0/6`.

Files are named by their destination SPA archive index, matching `knarc`
unpack names. For example, `6_00000739.bin` becomes SPA `739` and can be
referenced from move animation scripts with `LoadSPA 739`.

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
