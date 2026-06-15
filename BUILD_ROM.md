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

These commands repack only the relevant data NARC(s), run CTRMap ROMBuilder on
the already-staged VFS, patch the ARM9 footer, copy the ROM to
`/Users/andylee/Repos/White2Upgrade.nds`, and print matching SHA256 hashes.

Use the full build after code, graphics, build-system, VFS-wide changes, or
before committing/release testing:

```sh
JAVA=/opt/homebrew/Cellar/openjdk@11/11.0.31/bin/java ninja -C build White2Upgrade.nds
cp build/White2Upgrade.nds /Users/andylee/Repos/White2Upgrade.nds
```

This repo uses the Meson/CTRMap VFS build. Do not revive the old Makefile-era
`ndstool` ROM repack workflow.

For a fresh build directory:

```sh
python3 subprojects/meson-1.7.0/meson.py setup build --cross-file=meson/nitro.ini
```
