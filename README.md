# Pokémon White 2 Upgrade — Pokeweb

This Pokeweb-oriented fork builds an expanded US Pokémon White 2 (`IRDO`)
ROM and provides a separate US Black 2 (`IREO`) runtime/data package. It uses
Meson/Ninja, PMC RPM modules, and a source-tree CTRMap VFS. GNU Make is only a
convenience wrapper; the old `make base`, `make tools`, and `ndstool` workflow
does not apply.

## Current Scope

- Expanded Pokémon data through National Dex **#1023**, plus selected regional,
  Mega, and alternate forms; Fairy typing and expanded graphics/data tables.
- Mega Evolution with battle selection, ability changes, and sprite refresh.
- Gen 6/7 battle mechanics and incremental Gen 8/9 move-handler support.
- Electric, Grassy, Misty, and Psychic Terrain effects with animated floor
  textures and terrain indicators.
- PWAN animated graphics, custom move-animation scripts, and SPA particles.
- Overlay-scoped battle logging, individual Pokémon counters, and summary
  integration; a White 2 single-NPC double-battle compatibility patch.

Expanded data is not a claim of complete modern-generation mechanics.
The [Gen 8/9 progress ledger](docs/gen8-gen9-move-handler-progress.md) distinguishes
focused emulator-tested handlers, native/reused effects that were only wired
and build-checked, and pending work. Hard and doubles-dependent entries in that
implementation batch remain deferred. Full gameplay, visual, lifecycle/stress,
and Black 2 behavioral regression coverage is not implied.

Battle logging repurposes Wi-Fi/Pal Pad save blocks. Back up saves and read the
[save-format and compatibility notes](docs/battle-log-save-format.md) before use.

## Runtime Architecture

| Component | White 2 | Black 2 |
| --- | --- | --- |
| Resident core | `White2Upgrade.dll`: hooks, shared state, Mega Evolution, terrain graphics, registration dispatch, and native aliases | `Black2Upgrade.dll`: game-specific hooks and static mechanic registration |
| Managed battle mechanics | On-demand grouped DLLs under `lib/w2u_battle/` | Same grouped sources linked statically; no child DLL loading |
| Field, Pokédex, and menu code | Overlay-scoped `White2UpgradeField.dll`, `White2UpgradePokedex.dll`, and `White2UpgradeUI.dll` | Separate matching `Black2Upgrade*` companions |
| PWAN graphics | Overlay-scoped Summary, Battle, Misc, and Trainer DLLs | Separate B2 builds with B2-specific hooks |

The [battle registry](src/pokeweb_gameplay/battle_modules/registry.json) currently
defines **23 groups**, with 62 managed ability entries, 101 move entries,
13 item entries, and subordinate field/side/position handlers. These are managed
registrations, including updates to some vanilla mechanics—not total coverage
counts. The registry generates the resident lookup, child API tables, Meson
manifest, and Black 2 static resolver.

White 2 loads a group when the engine registers one of its mechanic events,
resolves its versioned `W2U_GetBattleModuleApi` export, and caches it for the
battle. Multiple registrations reuse one handle. Children remain loaded until
battle cleanup, rather than unloading when an originating event disappears.
The resident loader has 24 fixed records and uses PMC's existing allocation
and module services without a separate loader heap or NitroKernel runtime DLL.
Native aliases stay resident. Temporary move registration does not guarantee
that every move in a moveset is loaded before action-order queries.

White 2's PMC heap is patched to **164 KiB**. Use the generated stripped-build
heap audit for the current budget; historical monolith sizes are not the
current allocation. The audit is a static model, not a runtime fragmentation
or load-peak guarantee. See [battle-module details](docs/w2u-battle-modules.md).

PWAN assets in `assets/pokeweb_pwan/` use the compact `PWNC` v3 config and are
packed into `vfs/data/zz_pokeweb_pwan/pwan.narc`. Unconfigured Pokémon use native
static graphics. The four W2 runtimes are `PokewebPwanSummaryW2.dll`,
`PokewebPwanBattleW2.dll`, `PokewebPwanMiscW2.dll`, and
`PokewebPwanTrainerW2.dll`; matching B2 targets are built separately.
See the [PWAN workflow](docs/pwan-animation-workflow.md) and
[memory-reduction notes](docs/pwan-memory-reduction.md).

## Build Setup

Required tools:

- Git, Ninja, GNU Make, and a POSIX shell environment.
- Python **3.11 or newer**, with packages from `requirements.txt`.
- A working JDK with `java` available on `PATH`; the macOS system launcher
  stub alone is not a JDK. `JAVA` can select another Java executable.
- ARM embedded tools: `arm-none-eabi-gcc`, `arm-none-eabi-g++`,
  `arm-none-eabi-as`, `arm-none-eabi-ld`, `arm-none-eabi-objcopy`,
  `arm-none-eabi-nm`, and `arm-none-eabi-readelf`.

Clone this fork and install the Python dependencies:

```sh
git clone --recurse-submodules https://github.com/hzla/W2U-Project.git
cd W2U-Project
python3 -m pip install -r requirements.txt
cp White2Upgrade.cmproj.example White2Upgrade.cmproj
```

`include/swan` is the remaining Git submodule. ExtLib and NitroKernel sources
are vendored at their existing include paths; their pinned upstream revisions
and local portability changes are recorded in
[native-dependencies.json](include/native-dependencies.json).
Use the bundled `tools/CTRMap/CTRMapV-dirty.jar`, which contains this build's
ROMBuilder/RPMTool changes; do not replace it with an arbitrary CTRMap release.

Supply your own clean US ROM inputs. The current build expects:

- A clean extracted White 2 VFS at `../IRDO_Extracted`.
- Clean White 2 and Black 2 ROMs at `../Port-Pokeweb/cleanwhite2.nds` and
  `../Port-Pokeweb/cleanblack2.nds` for targets that use clean-ROM inputs.
- `White2Upgrade.cmproj` with `VFSBase: ../IRDO_Extracted` and
  `VFSOverlay: vfs`.

These sibling paths are current build assumptions, not files supplied by the
repository. Several Meson targets reference them directly, so changing only
the cmproj's `VFSBase` is not sufficient to relocate all inputs. The Black 2
base path can be changed with `-Dblack2_base_rom=...`. A loose `IRDO.nds` in
the repository root is not the primary input for the White 2 VFS build.

### White 2

For a stripped build:

```sh
make meson
python3 subprojects/meson-1.7.0/meson.py setup build-stripped \
  --cross-file=meson/nitro.ini -Dstrip_rpms=true
ninja -C build-stripped White2Upgrade.nds
```

`make meson` fetches the pinned Meson 1.7.0 tool. The ROM is written to
`build-stripped/White2Upgrade.nds`. Subsequent builds only need the `ninja`
command. Child battle DLLs are always stripped; `strip_rpms` also strips
the generated core and companion RPMs while retaining diagnostic ELF files.

For an unstripped development build, use `make configure` followed by `make`;
the output is `build/White2Upgrade.nds`. Both build directories stage into the
same source-tree `vfs/`, so do not build them concurrently. ROMBuilder defaults
to a 4 GiB Java heap, configurable with `-Drombuilder_java_heap=6g`.

The ROM finalizer validates FAT/digest/TWL ordering and adjusts oversized ROM
headers. The post-512-MiB path is tested for the Pokeweb emulator deployment;
stock hardware and arbitrary flashcart compatibility are not claimed.
See [BUILD_ROM.md](BUILD_ROM.md) for full-build and fast data-test commands.

### Black 2

Black 2 is a separate clean-US `IREO` package, not a White 2 ROM with renamed
DLLs. Its hooks, symbol database, metadata, and compatibility signatures are
game-specific. Other regions and modified bases are not supported fresh-install
targets. It does not package or load White 2's child mechanic DLLs.

```sh
ninja -C build-stripped src/black2upgrade-artifacts.stamp \
  black2upgrade-release-artifacts.stamp
```

This stages runtime/compatibility/heap artifacts and the expansion-data package
under `build-stripped/black2upgrade-artifacts/`. Pokeweb Serverless handles the
installation and canonical Black 2 ROM workflow separately; this target does
not itself build `Black2Upgrade.nds`.
See [Black2Upgrade V1](docs/black2upgrade-v1.md) for installation, preservation,
and verification requirements.

## Verification and Contribution

Run repository host tests and the source privacy check:

```sh
python3 -m unittest discover -s tools/tests
python3 tools/check_source_privacy.py
```

PWAN's sanitizer-backed texture/config host tests additionally require
`clang++` with AddressSanitizer and UndefinedBehaviorSanitizer:

```sh
python3 tools/pwan/test_runtime_memory.py
```

Useful configured-build checks:

```sh
ninja -C build-stripped src/stage_w2u_battle_modules.stamp \
  src/white2upgrade-battle-heap-audit.json \
  src/Black2Upgrade.dll src/black2upgrade-compatibility.json
```

Packaging checks cover registry consistency, child exports/imports, stripped
RPMs, hook ownership, staged modules, and heap budgeting. Host tests are not
emulator gameplay tests. Focused headless move-interaction tests use the separate
Pokeweb Serverless harness; recorded per-move coverage and limitations are in
the progress ledger. Do not refresh compatibility baselines just to hide a
failing check.

For new mechanics, prefer an existing cohesive module group, compose native
effects where appropriate, and keep hooks/shared state resident. Update the
registry and generated manifests together. See the
[Gen 8/9 handler reference](docs/gen8-gen9-move-handler-reference.md) and
[module architecture](docs/w2u-battle-modules.md).

Source map:

- Gameplay, Mega, terrain logic/graphics, and hooks: `src/pokeweb_gameplay/`.
- PWAN graphics: `src/pwan_animation/`, `assets/pokeweb_pwan/`, `tools/pwan/`.
- Pokémon/move/type data: `data/pml/`; items, text, and trainers: `data/`.
- Move scripts and particles: `data/graphics/move_animations/` and
  `data/graphics/move_spas/`; see their READMEs and the
  [animation notes](docs/moveanimation-spanotes.md).
- Terrain assets/mappings: `assets/move_backgrounds/terrains/` and the
  [terrain-texture guide](docs/terrain-texture-mvp.md).
- Battle-log/counter code: `src/battle_log/`; see the
  [save format](docs/battle-log-save-format.md).
- Single-NPC doubles patch: [scope and checks](docs/single-npc-double-battle-fix.md).
- Build targets/staging: `meson.build`, `src/meson.build`, `data/meson.build`.

Keep published documentation and generated reports free of host-specific
paths and private identifiers. Report writers use `tools/pwan/report_paths.py`;
the privacy check includes publishable files, submodules, and ZIP/JAR contents,
but does not rewrite Git history or ignored build metadata.

## Creators

- [PlatinumMaster](https://github.com/PlatinumMaster)
- [Dararo](https://github.com/Paideieitor)
- [BluRose](https://github.com/BluRosie)
- [SpagoAsparago](https://github.com/SpagoAsparago)
- [Bubble791](https://github.com/Bubble791)
- [BromBromBromley](https://github.com/BromBromBromley)
- [totally_anonymous](https://github.com/totallyanon)

## Credits

- Log(n) - All supplied Gen 8 and Gen 9 move animations.
- [Bond697](https://github.com/Bond697) - Initial Generation V research.
- [KazoWAR](https://projectpokemon.org/home/forums/topic/33493-project-721/) - Project 721 (which this was based on).
- [MeroMero](https://projectpokemon.org/home/profile/50874-meromero/?tab=activity#) - Initial fairy type implementation.
- [Hello007](https://github.com/HelloOO7) - CTRMap, PMC, code injection tools, Generation V research.
- [BluRose](https://github.com/BluRosie) - Fairy type fixes, expansion fixes.
- [PlatinumMaster](https://github.com/PlatinumMaster) - Expansion fixes, PMC, code injection tools, Generation V research, build system.
