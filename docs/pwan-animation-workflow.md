# PWAN Animation Workflow

This repository uses the HZLA GIF animation workflow for expanded Pokemon sprites.

## Runtime

Pokeweb animation support is split between `w2u_main.dll` hooks and the
resident `PokewebPwanW2.dll` runtime from `src/pwan_animation`.

The runtime loads one archive from the ROM filesystem:

- `zz_pokeweb_pwan/pwan.narc`

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
