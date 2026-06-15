# ROM Rebuild Command

Use Homebrew's real JDK binary. The macOS `/usr/bin/java` stub fails in Codex.

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
