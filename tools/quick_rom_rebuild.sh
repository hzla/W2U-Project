#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repo_root"

java_bin="${JAVA:-/opt/homebrew/Cellar/openjdk@11/11.0.31/bin/java}"
rom_out="${ROM_OUT:-build/White2Upgrade.nds}"
copy_to="${COPY_ROM_TO:-/Users/andylee/Repos/White2Upgrade.nds}"

usage() {
  cat <<'EOF'
Usage: tools/quick_rom_rebuild.sh MODE [MODE...]

Fast data-test rebuilds that skip always-stale graphics staging.
Run a full Meson ROM build after code, graphics, build-system, or VFS-wide edits.

Modes:
  trainer           Repack trainer data NARCs, then rebuild/copy the ROM
  personal          Repack personal data NARC, then rebuild/copy the ROM
  trainer-personal  Repack both trainer and personal data NARCs
  rom-only          Run CTRMap ROMBuilder using already-staged VFS files

Environment:
  JAVA              Java binary to use for CTRMap
  ROM_OUT           Output ROM path, default build/White2Upgrade.nds
  COPY_ROM_TO       Copy destination, default /Users/andylee/Repos/White2Upgrade.nds
EOF
}

if [[ $# -eq 0 ]]; then
  usage >&2
  exit 2
fi

targets=()
rom_only=0

add_trainer_targets() {
  targets+=(
    data/trainers/pack_trdata_narc.stamp
    data/trainers/pack_trpoke_narc.stamp
  )
}

add_personal_targets() {
  targets+=(data/pml/pack_personal_narc.stamp)
}

for mode in "$@"; do
  case "$mode" in
    trainer)
      add_trainer_targets
      ;;
    personal)
      add_personal_targets
      ;;
    trainer-personal|personal-trainer)
      add_trainer_targets
      add_personal_targets
      ;;
    rom-only)
      rom_only=1
      ;;
    -h|--help|help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown quick rebuild mode: $mode" >&2
      usage >&2
      exit 2
      ;;
  esac
done

if [[ ${#targets[@]} -gt 0 ]]; then
  ninja -C build "${targets[@]}"
elif [[ "$rom_only" -ne 1 ]]; then
  echo "No data targets selected." >&2
  usage >&2
  exit 2
fi

"$java_bin" \
  -cp tools/CTRMap/CTRMapV-dirty.jar \
  ctrmap.cli.ROMBuilder --input White2Upgrade.cmproj --output "$rom_out"

python3 tools/patch_arm9_footer.py --rom "$rom_out" --arm9 vfs/arm9.bin

cp "$rom_out" "$copy_to"
shasum -a 256 "$rom_out" "$copy_to"
