# ROM Rebuild Command

Use Homebrew's real JDK binary. The macOS `/usr/bin/java` stub fails in Codex.

## Fast Local Data-Test Rebuilds

For trainer/personal-data test edits, do not default to the full Meson ROM
target. The full target intentionally depends on broad VFS staging, including
always-stale graphics targets, so it is much slower than needed for one trainer
or one personal file.

Use the narrow helper from the repository root:

```sh
tools/quick_rom_rebuild.sh trainer
tools/quick_rom_rebuild.sh personal
tools/quick_rom_rebuild.sh trainer-personal
```

These commands repack only the relevant data NARC(s), then use a dev-only ROM
patch path by default. The patcher packs the staged VFS `.arc` folder into a
NARC and replaces only that ROM file through the existing FAT/FNT, appending if
the archive grows. It copies the ROM to `/Users/andylee/Repos/White2Upgrade.nds`
and prints matching SHA256 hashes. Run one full build first so
`build/White2Upgrade.nds` exists as the patch base.

To force the older CTRMap ROMBuilder path for the same narrow targets:

```sh
QUICK_ROM_METHOD=rombuilder tools/quick_rom_rebuild.sh trainer-personal
```

Use the full build after code, graphics, build-system, VFS-wide changes, or
before committing/release testing:

```sh
JAVA=/opt/homebrew/Cellar/openjdk@11/11.0.31/bin/java ninja -C build White2Upgrade.nds
cp build/White2Upgrade.nds /Users/andylee/Repos/White2Upgrade.nds
```

The full build's `stage_pokegra_battle` target patches Gen 7 native fallback
sprites by recompressing 404 NCGR files. Dev builds default to fast literal LZ11
through `-Dpokegra_fallback_compression=literal` and use
`-Dpokegra_fallback_jobs=6`. To switch back to compact non-literal NLZ11 output,
run:

```sh
python3 subprojects/meson-1.7.0/meson.py configure build -Dpokegra_fallback_compression=nlz11
```

Switch back to fast dev mode with:

```sh
python3 subprojects/meson-1.7.0/meson.py configure build -Dpokegra_fallback_compression=literal
```

`stage_pokegra_battle` is also incremental. It writes
`build/data/graphics/stage_pokegra_battle.manifest.json` and only restages
changed NNS entries, extra binaries, or PWAN fallback patches on later runs.
On this machine, no-op staging is about 1.3 seconds; touching five Gen 7 PWAN
assets patched 12 fallback NCGRs in about 1.7 seconds. Delete the manifest or
run the script with `--force-full` if you need a complete restage for debugging.

This repo uses the Meson/CTRMap VFS build. Do not revive the old Makefile-era
`ndstool` ROM repack workflow.

For a fresh build directory:

```sh
python3 subprojects/meson-1.7.0/meson.py setup build --cross-file=meson/nitro.ini
```
