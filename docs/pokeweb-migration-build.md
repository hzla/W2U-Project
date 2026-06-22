# Pokeweb Migration Build Setup

**Full local rebuild note:** from the repository root, use
`JAVA=/opt/homebrew/Cellar/openjdk@11/11.0.31/bin/java ninja -C build White2Upgrade.nds`
and then copy `build/White2Upgrade.nds` to `/Users/andylee/Repos/White2Upgrade.nds`.
The macOS `/usr/bin/java` stub is not enough for CTRMap/RPMTool.

**Fast data-test rebuild note:** for trainer and personal-data test edits, prefer
the narrow helper so Meson does not rerun always-stale graphics staging or the
full CTRMap ROMBuilder:

```sh
tools/quick_rom_rebuild.sh trainer
tools/quick_rom_rebuild.sh personal
tools/quick_rom_rebuild.sh trainer-personal
```

By default this uses `tools/dev_rom_patch.py`, which packs the staged flat VFS
`.arc` folders for `a/0/9/1`, `a/0/9/2`, and `a/0/1/6` into CTRMap-shaped NARCs
and replaces those files inside an existing `build/White2Upgrade.nds`. If the
new NARC is larger than the current FAT allocation, it appends the payload and
updates the FAT entry. Run one full build first so the base ROM exists. To force
the authoritative CTRMap path for a data test, run:

```sh
QUICK_ROM_METHOD=rombuilder tools/quick_rom_rebuild.sh trainer-personal
```

Use the full Meson target after code, graphics, build-system, or VFS-wide edits.

This branch keeps upstream's Meson and CTRMap VFS build as the public build
entrypoint. The old Makefile-era `base`, `ndstool`, and full-ROM repack flow is
not restored.

**Pokegra battle staging note:** the full build's `stage_pokegra_battle` target
patches Gen 7 native fallback sprites by recompressing 404 NCGR files. Dev
builds default to fast literal LZ11 with
`-Dpokegra_fallback_compression=literal` and `-Dpokegra_fallback_jobs=6`. To
switch back to compact non-literal NLZ11 output, run:

```sh
python3 subprojects/meson-1.7.0/meson.py configure build -Dpokegra_fallback_compression=nlz11
```

Switch back to fast dev mode with:

```sh
python3 subprojects/meson-1.7.0/meson.py configure build -Dpokegra_fallback_compression=literal
```

The target is incremental after its first run. It writes
`build/data/graphics/stage_pokegra_battle.manifest.json` and then only restages
changed NNS entries, extra binaries, or affected PWAN fallback patches. Current
observed timings on the M3 Pro are about 1.3 seconds for a no-op stage and about
1.7 seconds after touching five Gen 7 PWAN assets. Delete the manifest or run
`tools/graphics/build_pokegra_battle.py` with `--force-full` when a complete
restage is needed for debugging.

## Required Local Tools

- Java 8-compatible JDK. `java` must be on `PATH` for CTRMap.
  On this machine, Homebrew JDKs are available under `/opt/homebrew/opt`; for
  example:

  ```sh
  export JAVA=/opt/homebrew/opt/openjdk@17/bin/java
  ```
- ARM embedded toolchain with `arm-none-eabi-as`, `arm-none-eabi-gcc`,
  `arm-none-eabi-g++`, `arm-none-eabi-ld`, `arm-none-eabi-objcopy`, and
  `arm-none-eabi-nm`.
- Ninja, Git, GNU Make, and Python 3.11 or newer.
- Python packages from the repository root:

  ```sh
  python3 -m pip install -r requirements.txt
  ```

- Git submodules:

  ```sh
  git submodule update --init --recursive
  ```

- `tools/CTRMap/CTRMapV-dirty.jar`.

## Required Local ROM Project Files

- Copy `White2Upgrade.cmproj.example` to `White2Upgrade.cmproj`.
- In `White2Upgrade.cmproj`, set `VFSBase` to a clean extracted US White 2 VFS.
  Upstream currently assumes `../IRDO_Extracted`.
- The extracted VFS must come from a clean US White 2 ROM. The generated ROM is
  built from the VFS project; a loose `IRDO.nds` in the repository root is not
  the primary input for this Meson build.

## Building

Configure and build with:

```sh
make configure
make
```

`make` builds the Meson target `White2Upgrade.nds` under `build/`.

Useful partial targets while reviewing migration commits:

```sh
ninja -C build src/w2u_main.elf
ninja -C build data/build_pokeweb_pwan_narc.stamp
ninja -C build pmc_arm9.stamp pmc_overlay.stamp
```

The DLL and final ROM targets invoke CTRMap/RPMTool through Java, so they require
the Java/cmproj/VFS setup above.

## Verification

After building the relevant targets, confirm the staged DLLs, PWAN v3 NARC
structure, sidecar binaries, behavior-critical archive counts, generated item
icon patches, and imported archive members against the current local build.

## Pokeweb Migration Notes

- PWAN battle graphics stay on Pokeweb's archive-backed v3 runtime. The build
  stages `vfs/data/zz_pokeweb_pwan/pwan.narc`, whose first member is the
  `PWNC` v3 config from `assets/pokeweb_pwan/config.bin`.
- The separate resident PWAN runtime DLL is staged as
  `vfs/data/patches/PokewebPwanW2.dll`.
- Upstream's plaintext NNS/TOML/PNG battle graphics pipeline remains in place
  for regular NNS assets.
- Move animations, SPA overrides, UI graphics, type graphics, and item icon
  patches are staged as CTRMap VFS archive overlays under `vfs/data/a/...`.
- Generated VFS overlays are written under `vfs/`. Do not reintroduce the old
  `ndstool` ROM extraction/repack flow for migration-only assets.

## macOS Case-Sensitive Worktrees

This upstream revision tracks case-distinct paths such as `include/Species.h`
and `include/species.h`, plus `src/type_expansion/Types.cpp` and
`src/type_expansion/types.cpp`. A default case-insensitive macOS filesystem
collapses those names and makes a clean checkout appear dirty.

On macOS, use a case-sensitive APFS volume or disk image for development and
build verification.
