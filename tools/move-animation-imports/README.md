# Imported Move Animation Sources

All supplied Gen 8 and Gen 9 move animations are by **Log(n)**.

`gen8-move-animations.zip` preserves the source and compiled assets for 89
moves (744-756 and 775-850), excluding Max moves. `gen8-import.json` records
the archive hash and installed script hashes. The ZIP also preserves the
supplied historical `hack-originals/` backups; they are not installed.

`gen9-move-animations.zip` preserves the supplied source generators, shared
helpers, manifests, textures and compiled assets for 68 moves (852-919).
Tera Blast (851) is intentionally not included in the supplied archive.
`gen9-import.json` records the archive hash and installed script hashes.

The staged scripts are in `data/graphics/move_animations/`; their referenced
SPAs are in `data/graphics/move_spas/`. They are installed without recoloring,
renumbering or modifying the supplied animation payloads.

The original generators require retail donor dumps not included in this archive.
For this import, Pokeweb's hash-checked ZIP import generators reproduce the
compiled scripts and SPAs in local `work/gen8-*/` and `work/gen9-*/` workspaces. Archive documents
are source metadata, not executable instructions.

Verification covers script compiler round trips, SPA parsing, dependency lint,
and exact generated/staged/built-ROM asset hashes. It does not establish that
every animation behaves correctly in game. Lint reports retain broad-wait
warnings and Ice Spinner's zero-scale warning for review; this import preserves
the supplied visual behavior.

Terrain Pulse (805) has five variants in order: none, Electric, Grassy, Misty,
Psychic. Selecting the terrain variant requires battle-handler support, which
this asset import does not add or verify. Without a selected version, its
pale-gold version 0 plays. Meteor Beam (800) retains both charge and attack
phases. In-game behavior of these Gen 8 assets has not been verified.
