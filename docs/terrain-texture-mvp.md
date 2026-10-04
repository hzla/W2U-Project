# Animated terrain floor textures

The battle viewer can replace and scroll the primary floor material for all
four terrain states across every vanilla Pokémon White 2 battle-background
model identified by the background table.

## Coverage and generated assets

- Terrains: Electric, Grassy, Misty, and Psychic
- Displayed vanilla backgrounds: 0 through 46
- Distinct table-declared field NSBMDs: 92
- Generated exact-layout NSBTX resources: 368
- Battle graphics member range: 573 through 940
- UV animation template: native NSBTA member 119

The source-of-truth target list is
`assets/move_backgrounds/terrains/battle-background-floor-targets.csv`. It was
distilled from the White 2 floor analysis in
`../Port-Pokeweb/Pokeweb-Serverless/docs/battle-background-floor-textures-white2.csv`.
For each distinct NSBMD, the selected target is the `primary` candidate with
the greatest projected area. The material's palette name is resolved from the
actual NSBMD material-to-palette binding rather than inferred from its name.
Coverage includes both valid low and high halves of the packed resource IDs in
the built ROM's battle-background table. White 2 normally selects 70 of these
models, but the other packed variants remain valid field assets and can be
selected by custom battle-background logic.

`docs/terrain-texture-mappings.csv` is the generated reference table. It lists
the displayed background and season, source model/material/texture/palette,
native format and dimensions, and all four replacement member IDs. The C++
mapping used at runtime is generated at
`src/pokeweb_gameplay/w2u_terrain_texture_mappings.inc`. Because each terrain
set is consecutive, the resident runtime table stores only its Electric member
and derives the other three IDs; this keeps full packed-model coverage from
needlessly increasing PMC heap use.

The four seamless, square source tiles are:

- `assets/move_backgrounds/terrains/electric-tileable.png`
- `assets/move_backgrounds/terrains/grassy-tileable.png`
- `assets/move_backgrounds/terrains/misty-tileable.png`
- `assets/move_backgrounds/terrains/psychic-tileable.png`

`tools/graphics/build_terrain_texture_mvp.py` generates the catalog in sorted
NSBMD-member order. Each row receives four resources in Electric, Grassy,
Misty, Psychic order. Existing rows retain their original sequential IDs;
newly discovered models can set `output_base_member` so they append resources
without renumbering the catalog. Every output clones the model's complete TEX0
block and replaces only the selected floor image and its bound palette. Texture
names, formats, dimensions, offsets, allocation sizes, other materials, and
model geometry stay unchanged. Rectangular allocations repeat a square
downsample instead of stretching the tile.

The generator supports every selected floor format: 256-color, 16-color,
A3I5, and A5I3. Alpha-indexed textures retain the native per-texel alpha bits.
Indexed textures with color-zero transparency retain the native transparent
mask. This exact-layout constraint lets the replacement safely borrow the live
field resource's texture and palette VRAM keys.

Regenerate the assets, mapping include, and report with:

```sh
python3 tools/graphics/build_terrain_texture_mvp.py
```

After adding/removing generated archive members, reconfigure Meson before
building so the battle-graphics staging target enumerates them:

```sh
python3 subprojects/meson-1.7.0/meson.py setup --reconfigure build
ninja -C build White2Upgrade.nds
```

## Runtime behavior

The viewer resolves the loaded season-specific NSBMD member to its generated
mapping. It does not preload the full catalog. When the logical terrain move
starts, it loads only that model's requested terrain NSBTX, borrows the native
VRAM keys, and publishes it for the next VBlank upload. The visible replacement
resource remains alive because native move-animation palette fades use its
palette as their source. A terrain-to-terrain replacement briefly holds the
old and new resource, then frees the old resource after the successful upload.
Terrain removal uploads the native field TEX0 before freeing the replacement.

Electric Terrain retains its field-only black fade mask: the upload occurs at
the completed EVY 16 fade, after which the terrain palette fades back in. The
other terrain resources upload at their terrain move-animation start. Terrain
Surge abilities queue the same logical move animation, so they use the same
path. Resource/layout/animation failures leave the currently visible static
field intact.

The runtime loads a private copy of native NSBTA member 119 and retargets its
single `pasted1` track to the mapped primary material. Only that material's
texture matrix animates; secondary floor layers, effects, sky, props, Pokémon
platforms, model geometry, and draw calls remain untouched. Electric, Grassy,
Misty, and Psychic advance the 101-frame one-tile translation track by half a
frame per VBlank (about one loop every 3.4 seconds at 60 Hz). Animation resets
to frame zero on each terrain change.

Electric Terrain additionally advances an ambient step timer from the normal
`BTLV_EFFECT_Main` path immediately before `GFL_PTC_Main`. A standalone
particle system preloads compact SPA `787`, uploads its textures through the
existing VBlank hook, and cycles one 32-frame spark through six native MCSS
floor anchors at 32-frame intervals. Moves and the free-roaming battle camera
can run concurrently. The timer resets on terrain
requests, successful terrain uploads, and field teardown. This path never
starts the shared move-effect VM and therefore never
changes the camera, palettes, sounds, sprites, or HUD. Reserved particles-only
member `626` remains available as a fallback/test representation of the same
distribution but is not invoked by runtime ambient playback.

Grassy, Misty, and Psychic Terrain use the same standalone particle-system
lifecycle with per-terrain pacing and no completed-batch cooldown. Grassy
loads compact SPA `788` and starts one root every 100 frames in user-left,
target-right, user-right, target-left order. It retains only Ingrain's growing
left/right emitters with 100-frame particle life; the delayed final-texture
redraw emitters that cause handoff flicker, the absorption emitter, and its
child particles are absent. Misty loads compact SPA `789` and emits only
Mist Ball SPA `466` resource `1` at `AA`, retaining the command's `+2px` Y
offset and `5325/4096` scale. Its timing is doubled, velocity halved, and the
mist restarts every 200 frames. Psychic loads compact SPA `790`, containing one
half-speed, 60-frame Shock Wave SPA `528` resource `2` parent and its child
energy particles, hue-shifted to the Psychic Terrain texture color. It
alternates every 60 frames between the `AA` user and `BB` target positions with
the donor's `+2px` Y offset. Switching directly among terrains replaces the one
private ambient system rather than retaining multiple particle heaps.

Animation creation is deferred until the first post-init viewer update because
the native texture-upload call occurs before `BTLV_FIELD_Init` constructs its
field render object. The additional NSBTA is bound through the target ROM's GFL
animation wrapper and detached before the native field model is destroyed.

## Nonstandard/compound backgrounds

The system deliberately follows the earlier “primary floor only” rule.
Backgrounds with multiple primary surfaces therefore recolor and animate only
the highest-area surface. This affects compound scenes such as backgrounds 18,
20, 22, 23, 25, 26 (Winter), 27, 30 (Autumn), 32, and 33 (Spring). Backgrounds
24, 28 (Autumn), and 33 (Spring) also contain a large untextured base plane,
which cannot be changed by a texture swap. Background 33 Spring targets its
dominant cloud surface; Autumn uses the separately shaped space-field model.
See the generated CSV for the exact selected material in each case.

Pokémon battle platforms are separate stage models and are not part of these
field replacements.

## Viewer hooks

The English White 2 overlay assumptions remain isolated in
`src/pokeweb_gameplay/w2u_terrain_texture_hooks.s`:

- Overlay 168 `0x021DE1D0`: preserve the native field texture upload, then pass
  the selected season-specific member and field resource into the terrain
  layer.
- Overlay 168 `0x021E05C2`: apply a prepared terrain TEX0 and advance the
  primary-floor NSBTA after native battle VBlank work.
- Overlay 168 `0x021DF1DE`: detach borrowed keys and free terrain resources
  before vanilla destroys the field resource.
- Overlay 168 `0x021DF2F2`: advance the independent Electric/Grassy/Misty/Psychic Terrain
  ambient timer immediately before the native global particle draw.
- Overlay 167 `0x021B733E`: synchronize terrain expiry with the disappearance
  message reaching the viewer.

The replacement uses the linked `GFL_G3DResUploadTexDataCore` interface rather
than raw Nitro function addresses. Before any replacement is freed, borrowed
keys and loaded flags are cleared so the native field remains their sole owner.
