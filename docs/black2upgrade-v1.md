# Black2Upgrade V1

Black2Upgrade V1 targets only the clean US Black 2 `IREO` ROM with SHA-256
`2e6b2415354aa41471bc7617068dce059a59931bf5c4348a264f8043f297683a`.
MoonBlack2, other regions, and partially modified bases are not compatible
fresh-install targets.

## Runtime layout

- `Black2Upgrade.dll` is the resident ARM9/battle core.
- `Black2UpgradeField.dll` is limited to overlay 165.
- `Black2UpgradePokedex.dll` is limited to overlays 299 and 302.
- `Black2UpgradeUI.dll` is limited to overlays 255, 265, and 207.
- All modules declare `PMCGameID=B2`, runtime ABI 1, and expansion-data
  version 1. Companion modules may import shared W2U state only from the
  resident core.

Shared gameplay C++ uses `include/w2u_platform.h`; B2 hook assembly and the
IREO symbol database are generated separately. Every address embedded by the
shared assembly must be listed in `pmc/black2upgrade_aliases.json`. The build
rejects unreviewed addresses, W2-only anchors, wrong overlay ownership,
missing core exports, or incorrect RPM metadata.

The compatibility manifest records clean-ROM signatures for all hook windows,
216 imported functions, and raw data/call anchors. Serverless checks those
signatures before creating a draft installation.

## Expanded data policy

`tools/build_black2upgrade_package.py` starts from clean B2. It replaces the
expanded gameplay tables, overlays only authored graphics/archive members,
merges enumerated expansion text entries, patches the B2 item-icon table by
signature, and adds the expansion sidecars, terrain mapping, and canonical
PWAN archive. Trainers, encounters, story scripts, maps, and unmodified B2
text remain from Black 2.

The four vanilla terrain floor mappings are shared with W2 only after the
package builder verifies every referenced B2 field-model member byte-for-byte
against the reviewed W2 layout. The package contains the B2 mapping CSV for
runtime/editor auditing.

## Build and verification

The configured stripped build directory is `build-stripped`:

```sh
ninja -C build-stripped src/black2upgrade-artifacts.stamp black2upgrade-release-artifacts.stamp
cd ../Port-Pokeweb/Pokeweb-Serverless
npm run black2upgrade:sync
npm run black2upgrade:rom
npm run black2upgrade:verify-rom
```

The runtime build also enforces the recorded hashes of the four W2 modules.
The heap audit models the resident core, battle PWAN runtime, UI companion,
terrain resources, textures, particles, and allocator bookkeeping together;
V1 must retain at least a 96 KiB safety margin in the 384 KiB module pool.

Generated release artifacts are in `build-stripped/black2upgrade-artifacts/`.
The canonical ROM is `build-stripped/Black2Upgrade.nds`.

## Serverless install/update contract

A fresh install requires the exact base hash, validates all compatibility and
package hashes, then stages expanded data, PMC_B2, all four upgrade modules,
the three B2 PWAN modules, and the canonical PWAN archive in a cloned project.
The clone replaces live project state only after all steps succeed.

Serverless keeps PMC's overlay, symbol RPM, marker, and patch DLLs at the
front of the physical NitroFS data region while retaining their logical file
IDs. Expanded battle graphics can otherwise move the PMC overlay far enough
into the cartridge image to make early PMC loading branch through unread data.

An existing marked V1 ROM receives PMC and the four runtime modules only.
Its NARCs, PWAN imports, trainers, encounters, and other user edits are not
replaced. A marker checksum, ABI, data-version, runtime metadata, or hook
signature conflict blocks the update.

## Validation boundary

The automated suite covers build scopes, signatures, package determinism,
fresh installation, reload detection, data preservation, and all base species
assets through 1023. Gameplay behavior, battle transitions, terrain camera
behavior, and long-running heap stability still require the Release DeSmuME
matrix before publishing a release build.
