# Writing W2U code that ports to the decomp

The Black 2 / White 2 decompilation (github.com/fuddlesworth/pokebw2, GPL-3.0) builds both games byte for byte and
documents modified builds (`--bugfix`, `--shift`). W2U injects code instead (PMC / CTRMap). Since 2026-10-15 W2U is
GPL-3.0 as well, so the decomp's headers, names and code can be used in W2U. These guidelines keep
new code cheap to move over; existing code is not being rewritten for them. Measured 2026-10-15 with the local
crosswalk tooling (`w2u-local/decomp/`):

- W2U's code calls 463 game functions: 268 have the same name in the decomp, 81 another name, 96 are still unnamed
  placeholders there, 15 have no decomp symbol at their address. Calls port almost mechanically (a generated
  name-mapping header covers the renames).
- The cost is in how code attaches: 269 hooks in the White 2 build (158 at absolute addresses, 84 whole-function
  replacements, 27 calls inside named functions) and 119 hardcoded `0x02xxxxxx` addresses.

## Guidelines for new code

1. **Attach through the game's own extension points first.** Battle mechanics: event handlers (ability, item, move,
   side and field handler tables, `BattleEventVar_*`), as the abilities and items already do. They become entries
   in the decomp's handler tables instead of hooks.
2. **When a hook is needed, name what it patches.** Prefer a whole-function replacement (`THUMB_BRANCH_<Func>`) or
   a call inside a named function (`THUMB_BRANCH_LINK_<Func>_0x<off>`) over an absolute address
   (`THUMB_BRANCH_LINK_<seg>_0x<addr>`). Keep the hook a thin shim that calls a plain function holding the logic.
   One comment per hook: which game function it patches and why.
3. **No raw addresses.** Name globals and functions in the ESDB (`pmc/IRDO.yml`) and use the name. Where an address
   is unavoidable (a literal pool, a table inside a function), one named constant with a comment saying what it is.
4. **Logic in C-compatible code.** Plain functions, POD structs, fixed-size arrays; C++ (ExtLib, classes,
   namespaces) at the edges is fine, but the logic should compile as C (the decomp is C, built with MWCC / clang).
5. **Injection-only machinery stays at the edges.** Module groups, the PMC heap budget, GFL heap 1 placement and ROM
   sidecar tables exist because of injection; touch them in one place per feature, not throughout its logic.
6. **Data in data files.** New species, moves, items, text: the TOML / table sources with locked IDs, not code
   constants. The decomp keeps its data as JSON per entity with schemas (`data/` there); ours converts to it.
7. **Save data:** any change to what is saved goes into [save-format.md](save-format.md) in the same commit.

## Checking a change

`python w2u-local/decomp/portability_check.py [RANGE]` (default `origin/w2u-integration..HEAD`) lists what a commit
range adds against these guidelines: address hooks (with the decomp function and source file each lands in) and raw
addresses. Exit code 1 when it finds any, so it can gate a commit. The pushed A3I5 / grounding / battle-text work
(2026-10-14) adds none.

Related: `w2u-local/decomp/crosswalk.py` (W2U symbols and hooks placed in the decomp's functions and files; the
porting checklist), `decomp_names.py` (the name-mapping header), `w2u-local/harness/w2syms.py` (harness addresses
from decomp names); proposal and status in MegaB2W2 `research/w2u/decomp_readiness_2026-10-14.md`.
