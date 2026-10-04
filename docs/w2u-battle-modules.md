# White 2 on-demand battle modules

White 2 keeps battle hooks, Mega Evolution, terrain graphics, shared state,
aliases, and the registration dispatchers in `White2Upgrade.dll`. The 59
managed ability entries (including updated Overcoat), 101 managed move entries,
13 custom item entries and their subordinate field/side/position entries are
grouped into 22 RPMs under
`vfs/data/lib/w2u_battle/`.

Updated Overcoat stays in the defense group, retaining its native weather
handler alongside the new powder immunity. If that child cannot be resolved,
the loader logs/caches the failure and registration explicitly preserves
Overcoat's native weather table. This reviewed native-only degradation does
not permit custom numeric IDs to fall through to unrelated vanilla handlers.

`src/pokeweb_gameplay/battle_modules/registry.json` is the source manifest for
module IDs, VFS paths, source sets, API entries, handler counts, priorities,
and dependencies. `tools/generate_w2u_battle_registry.py` generates the
resident route table, grouped API definitions, Meson child manifest, and Black
2 static getter table.

The private resident route uses a 16-bit mechanic ID and byte-sized kind/module
indices (four bytes total). The public module API still uses its original
fixed-width fields. A host test compiles the generated routes and checks every
key and module index, including mechanic IDs above 255.

For native event composition, `W2U_FindNativeMoveGetter` resolves an immutable
getter from the current game's native table; children never import other
children's handlers. Supercell Slam uses this service for crash/Minimize damage.
Hydro Steam uses the resident damage-weather adapter's W2U-only event `0x100`
in the active damage context. This adds no shared storage or ABI layout changes,
and leaves native weather rounding in place. New hooks always remain resident.

Terrain Pulse uses W2U-only event `0x101`, dispatched by the existing resident
move-parameter routine after ordinary move/ability/position callbacks and before
reading the final parameters. This prevents a later Normalize/-ate callback
from overwriting its special type. The child still applies Electrify and the
Normal-only Ion Deluge exception, and the shared -ate power helper excludes it.
The same dispatcher is linked statically for Black 2; no raw hook or ABI layout
change is added for this phase.

At registration time, the resident loader reads the RPM through the ROM
filesystem, validates its bounds, allocates its declared expanded size from
PMC, starts it at `INTERNAL_RELOCATIONS`, and resolves
`W2U_GetBattleModuleApi`. Successful and failed resolutions are cached for the
battle. A fixed 24-record table is used; there is no loader heap and there are
no per-event references. Modules unload in reverse order at battle teardown,
the next-battle guard, or resident module unload.

Private descriptors store relative paths, sharing one `lib/w2u_battle/` prefix.
The loader reconstructs full paths in a bounded 64-byte stack buffer; registry
generation rejects longer paths. This saves resident storage without another
allocation, public ABI change, or changing staged paths.

Triple Axel reuses Triple Kick's native accuracy event and native action-owned
scratch for its escalating power. Disguise remains in `abilities/forms`; its
damage-estimation callback is read-only apart from the event result, and form/HP
work is queued only at native real-execution damage determination. The resident
final-damage adapter forwards the native cached normal/fixed result through
event `0x48`, then reads it back. Both W2 and B2 builds include the verified
stack-preserving call-site wrapper; no child handler is imported by the core.

Steel Beam shares Mind Blown's attempt-marking table in `moves/flow`.
Chloroblast marks only native real-execution damage determination, so a hit
absorbed by Substitute or Disguise still qualifies without using an AI preview.
The same sequence-end cost callback rounds half maximum HP up, consumes its
action scratch once, and honors effective Rock Head only for Chloroblast.
Native simple damage retains Magic Guard handling; no new core hook, shared
state, module group or damage-based recoil metadata is introduced.

Clangorous Soul and Fillet Away share an executor-local transaction in
`moves/stats`. It validates HP and effective boost direction first, uses native
HP-shift work rather than recoil, queues the native stat changes and then checks
HP berries. The native event's work result supplies failure when nothing was
queued; it does not expose a move-failure flag. Snatch pays from the actual
executor. No shared scratch state, core hook or additional module is needed.

Temporary native move events are registered for pre-action or execution work,
not before every action-order query. Effects such as Grassy Glide's priority
therefore use the existing resident field tracker. An initial moveset alone
does not guarantee that all of its child handlers are live during action sorting.

Child RPMs are always stripped. RPMTool retains internal symbols needed by
relocations, so the packaging step narrows the RPM export window after
generation. The resulting module retains exactly one public export hash while
keeping its internal relocation symbols and contains no symbol-name strings.

The core, children and Black 2 core use `tools/package_rpm_checked.py` to
validate a freshly generated temporary RPM before replacing the output.
RPMTool can report parser errors while exiting successfully; validating an
existing DLL alone would not catch a stale build. Resident branch-hook owners
must resolve in the ESDB, including battle setup, damage-root and added-type
effectiveness call sites. This owner check does not cover legacy `FULL_COPY`
aliases.

Black 2 compiles the same gameplay sources without the dynamic-core define.
The registry generates 22 uniquely named hidden API getters plus a static
resolver; the legacy duplicate ability/move/item registration tables are not
compiled. No child RPMs are built into or staged for the Black 2 package.

Useful build targets:

```sh
ninja -C build-stripped src/stage_w2u_battle_modules.stamp
ninja -C build-stripped src/white2upgrade-battle-heap-audit.json
ninja -C build-stripped src/Black2Upgrade.dll
ninja -C build-stripped src/black2upgrade-compatibility.json
```

The runtime telemetry returned by `W2U_BattleModules_GetTelemetry()` records
the resident fixed size, current/peak child bytes, current module count,
cumulative load/unload/failure counts, and the battle-local failure mask.

For the next move-handler batch, see the [Generation 8 and 9 implementation
reference](gen8-gen9-move-handler-reference.md). It inventories non-Max moves,
paraphrases their implementation-relevant effects, and records complexity,
reuse candidates, proposed module placement, dependencies, and focused tests.
