# ROM Rebuild Command

Use a real JDK binary. The macOS system Java launcher stub is not enough for
CTRMap/RPMTool.

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
NARC and replaces only that ROM file through the existing FAT/FNT. If an
archive outgrows its existing allocation, the helper automatically falls back
to CTRMap so the NTR digest tables and TWL tail are rebuilt safely. It copies
the ROM to `COPY_ROM_TO` and prints matching SHA256 hashes. Run one full build
first so `build/White2Upgrade.nds` exists as the patch base.

To force the older CTRMap ROMBuilder path for the same narrow targets:

```sh
QUICK_ROM_METHOD=rombuilder tools/quick_rom_rebuild.sh trainer-personal
```

Use the full build after code, graphics, build-system, VFS-wide changes, or
before committing/release testing:

```sh
JAVA=java ninja -C build White2Upgrade.nds
cp build/White2Upgrade.nds "$COPY_ROM_TO"
```

## ROMs Larger Than 512 MiB

The final ROM target runs `tools/finalize_white2_rom.py` after CTRMap and the
ARM9 footer patch. CTRMap places every NTR file and its regenerated digest
tables before a new 0x80000-aligned NTR/TWL boundary, then emits the TWL
binaries after that boundary. The finalizer validates that layout, advertises
the tested 2 GiB device-capacity value once the file exceeds 512 MiB, and
refreshes the secure-area, header, and CTRMap DSi signature digests.

CTRMap's digest builder temporarily needs several times the final ROM size in
Java heap. Meson defaults to `-Xmx4g`; change it when configuring if needed:

```sh
python3 subprojects/meson-1.7.0/meson.py configure build \
  -Drombuilder_java_heap=6g
```

The repository supports ROM offsets below CTRMap's signed 2 GiB ceiling and
rejects outputs at or above it. The post-512-MiB path is intended for the
tested Pokeweb emulator deployment; stock hardware and third-party
flashcart/loader compatibility are not implied.

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
In local testing, no-op staging took about 1.3 seconds; touching five Gen 7 PWAN
assets patched 12 fallback NCGRs in about 1.7 seconds. Delete the manifest or
run the script with `--force-full` if you need a complete restage for debugging.

This repo uses the Meson/CTRMap VFS build. Do not revive the old Makefile-era
`ndstool` ROM repack workflow.

## Source Privacy Checks

Run `python3 tools/check_source_privacy.py` or
`ninja -C build-stripped source-privacy-check` before distributing source.
The check covers tracked and nonignored files, submodules, and decompressed
ZIP/JAR members. Git history and ignored local build metadata are not scanned.
Additional private identifiers can be supplied with repeated `--forbid TOKEN`
arguments without storing them in the repository.

Report generators should use `tools/pwan/report_paths.py`'s `write_report`
helper so saved paths are repository-relative, including external input paths
and embedded path diagnostics. Run `python3 tools/tests/test_source_privacy.py`
to verify report normalization and archive sanitization.

For a fresh build directory:

```sh
python3 subprojects/meson-1.7.0/meson.py setup build --cross-file=meson/nitro.ini
```
