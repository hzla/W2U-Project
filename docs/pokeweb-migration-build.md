# Pokeweb Migration Build Setup

This branch keeps upstream's Meson and CTRMap VFS build as the public build
entrypoint. The old Makefile-era `base`, `ndstool`, and full-ROM repack flow is
not restored.

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

After building the relevant targets, run:

```sh
python3 tools/migration/verify_pokeweb_migration.py
```

The verifier checks staged DLLs, PWAN v3 NARC structure, sidecar binaries,
behavior-critical archive counts, generated item icon patches, and, when the old
local Makefile build is available, byte-compares staged archive members against
that build.

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
