# PWAN memory reduction — 2026-09-06

The shared runtime config cache is now 4,096 bytes instead of 8,192 bytes.
The current config is 3,276 bytes, leaving 820 bytes of cache capacity. A
canonical v3 config at the runtime limit of 768 overrides occupies 3,856 bytes.
The NARC packer rejects configs larger than the cache at build time.

Battle texture staging now stores 96 rows of 48 bytes (4,608 bytes total),
instead of 96 rows of 128 bytes (12,288 bytes). Tile conversion writes packed
rows, and upload reads them with the packed stride while retaining the native
128-byte VRAM destination stride. The array is explicitly four-byte aligned.
Both battle builds link the frame-only scratch source; miscellaneous viewers
retain their existing texture scratch buffer.

## Compiled results

These are stripped RPM allocations including BSS, eight-byte allocation
rounding, and the 16-byte allocation header. White 2 and Black 2 produced the
same sizes for each module.

| DLL | Before | After | Saved |
| --- | ---: | ---: | ---: |
| PWAN battle | 34,920 B | 23,144 B | 11,776 B / 11.5 KiB |
| PWAN summary | 18,488 B | 14,392 B | 4,096 B / 4 KiB |
| PWAN miscellaneous | 40,304 B | 36,208 B | 4,096 B / 4 KiB |

Battle BSS falls from 29,176 to 17,400 bytes. On-disk DLL sizes stay unchanged:
these savings come from zero-initialized runtime buffers.

Using the existing 164 KiB PMC allocation model, with all 22 lazy battle
categories retained, estimated remaining space changes as follows:

| Scenario | Before | After |
| --- | ---: | ---: |
| All categories loaded and settled | 27,936 B | 39,712 B / 38.78 KiB |
| Conservative category-load peak envelope | 26,928 B | 38,704 B / 37.80 KiB |

This is a static allocation estimate, not a measured runtime free list. It
includes the prior infrastructure allowance and MainMenuSkip allocation but
excludes fragmentation, free-block metadata, and additional concurrent viewers
or overlays. Summary and miscellaneous savings apply when those DLLs load;
they are not added to the battle-only estimate.

## Verification

- `python3 tools/pwan/test_runtime_memory.py` passed. The host harness compiles
  the production tile-conversion and upload functions with AddressSanitizer
  and UndefinedBehaviorSanitizer. It checks 128 generated frames against an
  independent pixel decoder and checks all eight VRAM slots, including row
  padding, unused rows, other slots, and bank restoration.
- Config tests cover all 768 entries, a config exactly at the cache limit,
  rejection at 4,097 bytes, and agreement between runtime and packer limits.
- All six White 2/Black 2 PWAN DLLs compiled and passed the build's RPM checks;
  explicit stripped-symbol verification also passed for all six.
- The full `build-stripped/White2Upgrade.nds` build passed ROM layout validation.
  Its three PWAN DLLs match the rebuilt outputs, and its PWAN NARC is identical
  to the previous stripped ROM's NARC. The core DLL was also rebuilt from the
  existing working tree and retains its previous allocation size.
- In-game animation/timing testing remains to be done.

## Git rollback

Branch: `codex/pwan-memory`. Checkpoint `6f526c467` preserves the pre-existing
battle source and Meson edits before the memory changes. Revert the subsequent
memory-reduction commit and rebuild to undo this change while retaining those
earlier edits. Unrelated working-tree changes were excluded from both commits.
