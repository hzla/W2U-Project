# Pokeweb Migration Build Setup

**Full local rebuild note:** from the repository root, use
`JAVA=java ninja -C build White2Upgrade.nds`
and then copy `build/White2Upgrade.nds` to the desired output path.
The macOS system Java launcher stub is not enough for CTRMap/RPMTool.

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
and replaces those files inside an existing `build/White2Upgrade.nds`. If a new
NARC is larger than its current FAT allocation, the helper falls back to the
authoritative CTRMap rebuild so expanded NTR data remains before the digest
tables and TWL region. Run one full build first so the base ROM exists. To force
the CTRMap path for a data test, run:

```sh
QUICK_ROM_METHOD=rombuilder tools/quick_rom_rebuild.sh trainer-personal
```

Use the full Meson target after code, graphics, build-system, or VFS-wide edits.

The final target also runs `tools/finalize_white2_rom.py`. CTRMap dynamically
moves the 0x80000-aligned NTR/TWL boundary after all NTR files; the finalizer
validates the resulting FAT/digest/TWL ordering and switches outputs larger
than 512 MiB to the tested 2 GiB device-capacity header value. CTRMap receives
a 4 GiB Java heap by default because digest generation temporarily uses several
times the output size. Configure another value with
`-Drombuilder_java_heap=6g`, or set `ROMBUILDER_JAVA_HEAP=6g` for the quick
helper. Outputs at or above CTRMap's signed 2 GiB ceiling are rejected.

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
changed NNS entries, extra binaries, or affected PWAN fallback patches. Local
test timings were about 1.3 seconds for a no-op stage and about 1.7 seconds
after touching five Gen 7 PWAN assets. Delete the manifest or run
`tools/graphics/build_pokegra_battle.py` with `--force-full` when a complete
restage is needed for debugging.

## Required Local Tools

- Java 8-compatible JDK. `java` must be on `PATH` for CTRMap. For example:

  ```sh
  export JAVA=/path/to/jdk/bin/java
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

For a release-style ROM whose generated W2U and PWAN RPMs are stripped, use a
separate build directory:

```sh
subprojects/meson-1.7.0/meson.py setup build-stripped \
  --cross-file=meson/nitro.ini -Dstrip_rpms=true
ninja -C build-stripped White2Upgrade.nds
```

Subsequent stripped builds only require the `ninja` command. This writes
`build-stripped/White2Upgrade.nds`. Source files and the corresponding `.elf`
files retain their symbols; only the packaged DLLs staged into the ROM are
stripped. The ordinary `make` path remains unstripped. Both build directories
share the source-tree VFS staging area, so do not run stripped and unstripped
ROM builds concurrently.

Useful partial targets while reviewing migration commits:

```sh
ninja -C build src/w2u_main.dll src/w2u_field.dll src/w2u_pokedex_ui.dll src/w2u_menu_ui.dll
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

- The main gameplay patch is split into a resident ARM9/battle core and three
  overlay-scoped RPMs: `White2UpgradeField.dll` for field-item code on overlay
  165, `White2UpgradePokedex.dll` for overlays 299/302, and
  `White2UpgradeUI.dll` for PC, Hall of Fame, and summary patches on overlays
  255/265/207. The build runs `tools/rpm_verify_nonresident.py` to reject an
  accidental ARM9/ARM7 dependency or overlay-scope change.
- RPM stripping is optional through the `strip_rpms` Meson option. RPMTool
  first generates name-driven automated hooks, then removes unused symbols,
  human-readable symbol names, and redundant self-relative relocations. The
  build verifies that stripped RPMs contain no symbol-name offsets while
  retaining the normal overlay-scope checks.
- In the current build, the resident core expands to 95,392 bytes and fixes to
  82,828 bytes. The old monolith expanded to 99,968 bytes and fixed to 87,096
  bytes, so the split returns 4,268 fixed bytes during an ordinary battle.
  The field, Pokédex, and UI RPMs fix to 1,988, 1,136, and 2,128 bytes
  respectively. A battle summary loads only the UI RPM and therefore retains
  2,140 bytes of the saving; unrelated field and Pokédex code stays unloaded.
- PWAN battle graphics stay on Pokeweb's archive-backed v3 runtime. The build
  stages `vfs/data/zz_pokeweb_pwan/pwan.narc`, whose first member is the
  `PWNC` v3 config from `assets/pokeweb_pwan/config.bin`.
- The overlay-scoped PWAN runtime is split into three staged DLLs:
  `vfs/data/patches/PokewebPwanSummaryW2.dll` for overlay 207,
  `vfs/data/patches/PokewebPwanBattleW2.dll` for overlays 167/168, and
  `vfs/data/patches/PokewebPwanMiscW2.dll` for overlays 265/284/298/307.
- Upstream's plaintext NNS/TOML/PNG battle graphics pipeline remains in place
  for regular NNS assets.
- Move animations, SPA overrides, UI graphics, type graphics, and item icon
  patches are staged as CTRMap VFS archive overlays under `vfs/data/a/...`.
- Generated VFS overlays are written under `vfs/`. Do not reintroduce the old
  `ndstool` ROM extraction/repack flow for migration-only assets.

## macOS Worktrees

The migration previously tracked paths that differed only by capitalization,
which required a case-sensitive disk image on macOS. Those collisions have been
removed: the canonical headers are now `include/species_ids.h`,
`include/personal_data.h`, and `include/type_constants.h`, and the active type
implementation is `src/type_expansion/type_effectiveness.cpp`. The repository
can be checked out and built directly on the default macOS APFS filesystem.
