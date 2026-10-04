# Pokémon White 2 Upgrade
This repository aims to bring new features to the Generation V Pokémon game, Pokémon White 2. This should also work for Black 2, given the conditions are satisfied (proper symbols database, PMC port).

> Migration branch note: the active build entrypoint is Meson plus CTRMap VFS,
> not the old `ndstool` extraction/repack flow. See
> `docs/pokeweb-migration-build.md` for current setup, build, and verification
> commands.

## Pokeweb Branch Changes
This branch keeps the original W2U expansion goals, but it also carries several
larger Pokeweb systems. Upstream review is easiest if these are treated as
separate merge surfaces.

### Black 2 Upgrade V1
- The clean-US Black 2 expansion is a separate four-module target and does not
  stage into the White 2 VFS. Its data package starts from clean `IREO` and is
  installed transactionally by Pokeweb Serverless.
- Build layout, compatibility rules, merge policy, commands, and validation
  boundaries are documented in `docs/black2upgrade-v1.md`.

### Gameplay DLL residency
- `White2Upgrade.dll` remains resident because it patches ARM9 and owns the
  battle mechanics and shared state.
- Field-item code lives in `White2UpgradeField.dll`, Pokédex UI limit patches
  in `White2UpgradePokedex.dll`, and PC/Hall of Fame/summary patches in
  `White2UpgradeUI.dll`. Each is scoped only to the overlays that use it, so a
  battle summary does not also load the unrelated field and Pokédex code.
- The current split reduces the fixed resident W2U allocation from 87,096 to
  82,828 bytes, leaving 4,268 more bytes available while a battle is active.
  The summary-capable UI module occupies 2,128 fixed bytes while active, so the
  split still saves 2,140 bytes when overlay 207 is open during battle.

### PWAN animated Pokemon graphics
- Runtime support lives in `src/pwan_animation/`. It builds three
  overlay-scoped runtimes: `PokewebPwanSummaryW2.dll`,
  `PokewebPwanBattleW2.dll`, and `PokewebPwanMiscW2.dll`. Together they contain
  the summary, battle, evolution, egg hatch, and non-battle hooks for animated
  Pokemon sprites without keeping unrelated PWAN code loaded.
- `PokewebPwanSummaryB2.dll`, `PokewebPwanBattleB2.dll`, and
  `PokewebPwanMiscB2.dll` are separate stock-US Black 2 (`IREO`) targets. They
  share the archive/format implementation but use B2-specific hook assembly,
  symbols, and code-layout addresses; Serverless bundles them without staging
  them into the White 2 Upgrade VFS.
- Runtime assets live in `assets/pokeweb_pwan/`: `config.bin` plus sparse
  `NNN_front.pwan` and `NNN_back.pwan` files. `tools/pwan/build_pwan_narc.py`
  packs them into `vfs/data/zz_pokeweb_pwan/pwan.narc`.
- `config.bin` now uses the compact `PWNC` v3 layout: a small header plus
  5-byte species/form rows with front/back flags and one paired asset index.
  Species and forms absent from this table fall back to normal static graphics.
- PWAN assets are packed into a single sparse NARC instead of the older loose
  `vfs/data/pokeweb_pwan` runtime output. NARC member `0` is `config.bin`;
  front and back animation members are addressed as `asset index * 2 + 1` and
  `asset index * 2 + 2`.
- Static fallback and form graphics are staged from `data/graphics/pokegra/`
  and `data/graphics/pokegra_battle_extra/`; import, relocation, grounding,
  form, icon, and Mega preview helpers live under `tools/pwan/`.
- Start with `docs/pwan-animation-workflow.md`, `data/graphics/meson.build`,
  and `src/pwan_animation/meson.build` when merging or auditing this system.

### New move animation assets
- Visible battle animation changes are data authored in the move-animation VM
  scripts and SPA particle archives, not C/C++. The routing hook is
  `src/pokeweb_gameplay/w2u_move_animation_hooks.s`.
- Move scripts are staged from `data/graphics/move_animations/` into archive
  `a/0/6/5`; SPA particle archives are staged from `data/graphics/move_spas/`
  into archive `a/0/0/6`. Both staging paths are wired in
  `data/graphics/meson.build`.
- The current generated Gen 6 move script range is `5_00000560.bin` through
  `5_00000623.bin`, with matching custom SPA additions currently in the
  `6_00000739.bin` through `6_00000783.bin` range.
- Per-animation notes live in `data/graphics/move_animations/README.md` and
  `data/graphics/move_spas/README.md`; broader editing references are in
  `docs/moveanimation-spanotes.md`, `docs/spa-editing-reference.md`, and
  `tools/import_move_animations_from_rom.py`.

### Mega Evolution
- Core mechanics, action selection integration, battle state repair, native
  Mega button behavior, and sprite-refresh synchronization live in
  `src/pokeweb_gameplay/w2u_mega.cpp` and
  `src/pokeweb_gameplay/w2u_mega_hooks.s`.
- The visible transformation is still handled by the move-animation system:
  `data/graphics/move_animations/5_00000622.bin` uses SPA assets
  `data/graphics/move_spas/6_00000765.bin` through
  `data/graphics/move_spas/6_00000771.bin`.
- Mega item definitions and icons are spread across `data/items/`,
  `tools/mkdata/enum/items.toml`, `assets/item_icons/icons/`,
  `assets/item_icons/icon_palettes/`, `tools/item_icons/build_item_icon_patch.py`,
  and `include/w2u_mega_native_button_assets.h`.
- Mega form graphics share the PWAN and pokegra paths above, with preview/form
  staging helpers in `tools/pwan/apply_mega_preview_low_ids.py`,
  `tools/pwan/stage_form_battle_assets.py`, and
  `tools/pwan/stage_form_icon_assets.py`.

### Move, ability, and item mechanics
- Pokeweb gameplay extensions are grouped in `src/pokeweb_gameplay/`:
  `w2u_moves.cpp`, `w2u_abilities.cpp`, `w2u_items.cpp`,
  `w2u_field_effects.cpp`, `w2u_field_items.cpp`, plus the associated hook
  assembly listed in `src/pokeweb_gameplay/meson.build`.
- Public declarations and expanded enums are in `include/w2u_moves.h`,
  `include/w2u_abilities.h`, `include/w2u_field_effects.h`,
  `include/w2u_battle.h`, `include/Moves.h`, `include/Items.h`,
  `include/species_ids.h`, `include/personal_data.h`, and
  `include/type_constants.h`.
- Data-side changes live mainly under `data/pml/`, `data/pml/moves/`,
  `data/pml/types/`, `data/items/`, `data/text/system/`, and `data/trainers/`.
  The mkdata enum inputs in `tools/mkdata/enum/` should be reviewed alongside
  those data files.

## Current Features
- Expanded Pokédex (currently up to 721).
- Fairy type.

## Setup
You will need the following tools to use this repository:
- [arm-none-eabi-{as, gcc, ld}](https://developer.arm.com/downloads/-/gnu-rm).
- [CTRMap (Community Edition)](https://github.com/kingdom-of-ds-hacking/CTRMap-CE/releases).
- gcc
- GNU Make (anything over 3.81).
- Java 1.8
- Python 3.4+
- [ndstool (2.2.0)](https://github.com/devkitPro/ndstool)
- A Linux environment (native or Windows Subsystem for Linux)

## Installation
### Initial Setup
1) Clone this repository using `git clone --recursive git@github.com:PlatinumMaster/White2Upgrade.git`, then `cd White2Upgrade`. **Do not omit the recursive flag, or you will not have all of the submodules associated with this repository.**
2) Download [CTRMap (Community Edition)](https://github.com/kingdom-of-ds-hacking/CTRMap-CE/releases), and put `CTRMap.jar` in `tools/CTRMap`, making the directory if it does not exist.
3) Grab a fresh American Pokémon White 2 ROM (preferrably one with SHA256SUM `3e50aec3db401332175a5d2b5fe2a68ac1a05ec63995dba9d1506b1b51837446`), name it `IRDO.nds`, and place it in the root directory of the repository (i.e in the same folder as `Makefile`).
4) Run `make tools` to build all of the tools associated.
5) Run `make base` to prepare the ROM contents for the build.

### Building
Once the repository is setup, run `make -j$(nproc)`. If all goes well, you shall see `White2Upgrade.nds` at the end of your build.

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
