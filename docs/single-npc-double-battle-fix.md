# Single-NPC double-battle fix

White2Upgrade bundles Pokeweb's White 2 double-battle compatibility patch as
`patches/DoubleBattleFixW2.dll`. It fixes global-script trainers configured for
a double battle when there is no partner trainer NPC to pair with them.

The RPM is scoped to field overlay 36 and hooks two routines:

- `0x021A5D6C`: paired-trainer validation used by trainer sight encounters.
- `0x021A6910`: trainer dialogue selection for the same single-NPC double case.

This is not part of the resident battle-mechanic DLL set and does not consume
the battle heap while overlay 36 is unloaded. The staged file uses Pokeweb's
canonical filename, so a ROM containing it is recognized as already having the
patch. Do not install another copy after building White2Upgrade.

`tools/stage_double_battle_fix.py` contains the pinned 1,520-byte RPM payload.
Every White 2 ROM build verifies its SHA-256, overlay dependency, base overlay
ID/address, and both original instruction windows before staging it. If another
patch changes either hook site, the build stops with the conflicting address
instead of emitting a ROM with competing hooks.

Black 2 packaging does not include this White 2 RPM. Black 2 needs a separately
validated regional patch if the same behavior is desired there.
