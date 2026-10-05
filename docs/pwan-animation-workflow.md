# PWAN Animation Workflow

This repository uses the HZLA GIF animation workflow for expanded Pokemon sprites.

## Runtime

**White 2 (since 2026-10-05, `megab2w2-integration` branch):** the PWAN assets
stay the authoring format, but White 2 no longer stages the PWAN runtimes or
`pwan.narc`. The build converts the assets into `w2anim/streams.bin`
(`tools/w2anim/build_w2anim_streams.py`) for the resident w2anim runtime
(`src/w2anim/w2u_anim_streams.cpp`), which streams them into MCSS sprites on
every screen. See `docs/megab2w2-integration.md`, "Phase 4". The rest of this
section describes the PWAN runtimes, which Black 2 still uses.

Pokeweb animation support is split between `w2u_main.dll` hooks and three
overlay-scoped runtimes from `src/pwan_animation`:

| Runtime | Overlay scope | Expanded load | Fixed size |
| --- | --- | ---: | ---: |
| `PokewebPwanSummaryW2.dll` | Summary (`207`) | 20,736 bytes | 20,244 bytes |
| `PokewebPwanBattleW2.dll` | Battle (`167`, `168`) | 36,560 bytes | 36,044 bytes |
| `PokewebPwanMiscW2.dll` | Evolution, egg hatch, and other non-battle views (`265`, `284`, `298`, `307`) | 44,512 bytes | 43,616 bytes |

Each DLL contains its own archive cache and scratch storage, so it has no
runtime dependency on either of the other PWAN DLLs. Summary carries only the
4.5 KiB frame scratch; battle and misc also carry the 12 KiB texture scratch.
The staging target removes the old `PokewebPwanW2.dll` monolith to prevent PMC
from loading both layouts.

The same source tree also builds three clean-US Black 2 (`IREO`) runtimes:

| Runtime | Overlay scope |
| --- | --- |
| `PokewebPwanSummaryB2.dll` | Summary (`207`) |
| `PokewebPwanBattleB2.dll` | Battle (`167`, `168`) |
| `PokewebPwanMiscB2.dll` | Evolution, egg hatch, and other non-battle views (`265`, `284`, `298`, `307`) |

These targets have dedicated B2 hooks and an `IREO` symbol/address profile.
They do not replace or alter the three White 2 targets and are consumed by
Pokeweb-Serverless rather than the White 2 Upgrade VFS staging target.
`PokewebPwanLegacyRetiredW2.dll` is a tiny hook-free module used only to retire
the known old Serverless monolith without shifting an existing ROM file ID.

The runtime loads one archive from the ROM filesystem:

- `zz_pokeweb_pwan/pwan.narc`

Because the DLL is overlay-scoped, the PMC overlay staged by the build includes
a fix for its bundled heap allocator. The original `HeapArea::Realloc` shrink
path reserved 24 bytes for a 16-byte block header, losing 8 bytes every time an
RPM was fixed. The former monolithic PWAN runtime expanded to 59,856 bytes and
fixed to 58,360 bytes; after one unload, the buggy allocator recovered only
59,848 bytes and the second load failed. `tools/patch_pmc_sysheap.py` applies
the allocator fix while staging overlay 344.

NARC member `0` is the `PWNC` v3 config from
`assets/pokeweb_pwan/config.bin`. Runtime asset members are sparse:

```text
front member id = asset index * 2 + 1
back member id  = asset index * 2 + 2
```

Species not present in `config.bin` fall back to normal game rendering.

## Asset Format

Each `.pwan` file is a 96x96 4bpp animation:

- Header magic: `PWAN`
- Palette: 16 BGR555 colors, with palette index 0 reserved for transparency
- Timeline: `{ u16 frameIndex, u16 ticks }`
- Frame data: `0x1200` bytes per unique frame

The 96x96 frame is stored as four OBJ-compatible tiled regions:

- `64x64` top-left
- `32x64` top-right
- `64x32` bottom-left
- `32x32` bottom-right

The runtime keeps 192 timeline entries per loaded asset, so the compiler resamples
longer source GIF timelines down to that limit.

## Runtime Pack

The committed runtime pack source is `assets/pokeweb_pwan`:

- `config.bin`
- `NNN_front.pwan`
- `NNN_back.pwan`

Meson packs those files into `vfs/data/zz_pokeweb_pwan/pwan.narc` with:

```sh
ninja -C build data/build_pokeweb_pwan_narc.stamp
```

The older loose `vfs/data/pokeweb_pwan` output path is intentionally bypassed on
this branch so stale PWAN v1 files do not shadow or confuse the v3 runtime.

## In-Game Verification

The current Route 6 save can exercise the battle path with wild Xerneas. Use the
ARM9 GDB stub and HID input method documented in `docs/debugging-gdb.md`.

Useful filtered breakpoint:

```gdb
break *0x02070ecc
commands
silent
if *(unsigned char*)$r1 == 0x70
  printf "PWAN_OPEN %s\n", $r1
end
continue
end
```

Then load the save and walk with the HID update breakpoint at `0x0203dd70`.
When Xerneas appears, the battle animation runtime should open:

```text
zz_pokeweb_pwan/pwan.narc
```

Asset index `66` maps to species `650 + 66 = 716`, which is Xerneas. The front
sprite is NARC member `133`, and the back sprite is member `134`.

## Form Changes Without an Intermediate Native Frame

PWAN-backed form changes must treat the actor identity and the rendered carrier
as separate pieces of state. The native `BattleViewRefreshFormSprite` path does
three conceptual jobs:

1. update the MCSS actor's species/form identity;
2. build the target form's native MAW resources;
3. queue the native carrier/static texture replacement.

The third step is not guaranteed to finish in the same frame. If PWAN uploads
the target texture first, the queued native replacement can arrive afterward
and overwrite texture VRAM. The PWAN frame cache will not notice that overwrite:
its species, form, asset, and copied frame are still unchanged. The native
texture can therefore remain visible until the next PWAN timeline frame. It may
also look offset or incorrectly colored because native NCBR pixels are being
displayed through the PWAN palette or through carrier metadata with a different
anchor.

For an **instant** PWAN form change:

1. Keep the native identity/form preparation. Do not remove the entire refresh
   call; doing so leaves MCSS on the old identity and the form may never change.
2. Suppress only the final native carrier/static texture replacement when the
   old carrier is compatible with the new PWAN asset.
3. Reuse that one live carrier, invalidate `copiedFrame` and `pendingFrame`, mark
   both texture and palette dirty, and upload the new PWAN frame immediately at
   the safe upload point.
4. Ensure both forms use compatible carrier geometry, cell, animation, and
   anchor metadata. If they do not, create a shared neutral carrier or copy the
   required metadata deliberately.

For a **transform animation**, apply the same ownership rule for the full
effect:

- Keep one carrier and one anchor from the first animation frame through the
  last. Do not let a native effect restore a snapshot MAW while PWAN installs a
  second carrier; alternating those carriers causes the position flicker.
- Allow the logical MCSS form to update, but keep a temporary PWAN visual-form
  override pointing at the old asset until the animation's explicit swap frame.
- At the swap frame, upload the new PWAN texture and palette onto the same
  carrier. Release the visual override when the effect completes.
- Native fades, particles, scaling, and similar effects are safe as long as
  they do not replace or restore the carrier texture/MAW.

Mimikyu's instant Disguise bust is the reference implementation:

- `src/pokeweb_gameplay/w2u_mega.cpp` keeps the native form/identity refresh.
- `src/pwan_animation/w2u_battle_hooks.s` hooks the final native carrier call at
  `THUMB_BRANCH_LINK_168_0x21DF7DC` and suppresses it only for busted Mimikyu.
- `src/pwan_animation/w2u_battle_anim.cpp` reuses the base-form carrier and
  forces the new PWAN texture/palette upload with
  `W2U_BattleAnim_RefreshPositionNow`.
- `tools/pwan/import_disguise.py` makes the busted form inherit the compatible
  carrier metadata.

The current exception is intentionally Mimikyu-specific. Before generalizing
it, verify that the new form can safely use the existing carrier.

### Diagnosing a Bad Intermediate Frame

Save one state on the first bad frame and another on the first good frame, then
compare:

- the MCSS entry's species/form and MAW resource IDs;
- the live MCSS pointer and palette proxy;
- the PWAN actor's `active`, `species`, `form`, `assetId`, `tick`,
  `copiedFrame`, `pendingFrame`, and dirty flags;
- texture and palette VRAM against the expected PWAN source bytes.

If the bad state reports a clean `copiedFrame` but texture VRAM does not match
that PWAN frame, and the image fixes itself at the next timeline frame, another
renderer overwrote VRAM after PWAN. Fix ownership or ordering; repeatedly
uploading earlier in the frame will not solve it. Also verify that the rebuilt
DLL is loaded for the target overlay and restart the emulator after replacing
the runtime build.
