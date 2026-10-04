# Battle log save format

The version-specific battle modules record the player's team and KO
attribution for ordinary AI trainer battles. Their small `BattleCounters.dll`
companions update individual PK5 counters through an overlay-local hook, and
their matching summary modules
(`White2UpgradeBattleLogSummary.dll` and
`Black2UpgradeBattleLogSummary.dll`) display species-family frag totals. The
battle modules and counter companions load only with battle overlay 167 in
BW2 (93 in BW); the summary modules load only with summary overlay 207 in BW2
(131 in BW). Splitting the 544-byte White 2 counter companion keeps the main
battle module within the smallest observed 2,528-byte fragmented PMC slot.
They do not log
wild, facility, online, or demo battles. Allied NPC partner KOs are recorded
as history-only attribution and do not increment player PK5 counters. The battle module edits normal save-control RAM, so new records become
permanent on the player's next ordinary game save.

## Repurposed normal-save blocks

| Save block | Original use | Size | Record capacity |
| --- | --- | ---: | ---: |
| 29 | Wi-Fi History | `0x1338` | 350 |
| 30 | Pal Pad / Wi-Fi List | `0x07C4` | 140 |
| 31 | Wi-Fi Negotiation | `0x0D54` | 110 |

These Wi-Fi features are incompatible with the log. The three blocks are
initialized together the first time a completed trainer battle is recorded,
providing a total capacity of 600 trainer records. Once full, new records are
discarded and the overflow flag is set. A tag battle against two trainers
creates one record for each opposing trainer, with the same player-team
snapshot in both.

White 2 normally mirrors the Pal Pad into a separate heap buffer and copies
that shadow back over block 30 immediately before saving. Installing battle
logging disables the retail Wi-Fi List copy routine because the Pal Pad and
related Wi-Fi data are deliberately incompatible with the log. This is a
two-byte static ARM9 patch, not a branch into either DLL, so each battle-log
module can still unload with its own overlay. The battle DLL also repairs
saves made by the initial v2 build, which could retain valid blocks 29 and 31
while block 30 was restored to its old Pal Pad contents.

Version 2 replaces the earlier 3-byte KO-event prototype. If version-1 data or
unrecognized data is present, all three blocks are reinitialized together on
the first completed trainer battle.

## Block header

Each block starts with this 16-byte little-endian header:

| Offset | Size | Field |
| ---: | ---: | --- |
| `0x00` | 4 | Magic `KLOG` (`0x474F4C4B`) |
| `0x04` | 2 | Format version (`2`) |
| `0x06` | 2 | Records used in this block |
| `0x08` | 2 | Capacity of this block |
| `0x0A` | 2 | Flags; bit 0 means overflow |
| `0x0C` | 4 | Reserved, zero |

Records begin at offset `0x10`. Entries in block 30 follow all entries in block
29, and entries in block 31 follow all entries in block 30.

## Trainer-battle record

Every record is a packed, little-endian 112-bit (14-byte) value:

| Bits | Field |
| ---: | --- |
| `0..9` | Opposing trainer ID |
| `10..12` | Player party count (`1..6`) |
| `13..72` | Six player species IDs, 10 bits each; unused slots are zero |
| `73..90` | For enemy slots 1–6, the credited player-side source (`0`, player party slot `1..6`, or AI partner `7`) |
| `91..108` | For player slots 1–6, the credited enemy party slot (`0` or `1..6`) |
| `109..111` | Reserved, zero |

The record is accumulated in the battle DLL's static overlay state and appended only
when the retail battle controller publishes a terminal result. Closing or
aborting a battle overlay before that point cannot leave a partial record.

For single and rotation battles, a KO is credited to the opposing Pokémon. In
double and triple battles, it is credited to the last opposing Pokémon whose
resolved move target set included the fainted Pokémon; this includes misses and
protected hits. If no such targeter exists, the Pokémon directly across from
the fainted Pokémon is used. The first attribution stored for a party slot is
retained if unusual revive mechanics make the same slot faint more than once.
In an AI-partner battle, the partner is also a valid last targeter for an enemy
faint and is stored as credit value `7`. Partner KOs remain visible in history
without incrementing any player Pokémon's individual KO counter.

## Individual PK5 counters

The battle runtime also stores three saturating little-endian `u16` counters on
each individual player Pokemon. They live in the encrypted 136-byte PK5 core,
so they follow that Pokemon through party/PC moves, trades within Generation
5, and evolution. Offsets below are logical offsets after decrypting and
de-shuffling the PID-selected blocks:

| PK5 offset | Logical block | Counter |
| ---: | --- | --- |
| `0x44..0x45` | B | Completed eligible trainer battles brought to |
| `0x46..0x47` | B | Completed eligible trainer battles entered |
| `0x43` (low), `0x5E` (high) | B, C | Opposing Pokemon KO events credited |

Block B's last four bytes are the dummy `u32` present in both BW and B2W2.
The low KO byte occupies Block B's last otherwise-unused byte before the two
participation counters. The high byte uses Block C's unused `0x5E` byte. The
bytes are assembled as a little-endian value even though they are not
contiguous. Keeping logical `0x64..0x67` zero avoids colliding with PKHeX's
Gen 4/5 encrypted-data sentinel, which otherwise causes an already-decrypted
PK5 to be decrypted a second time. Block D is not used because B2W2 assigns
its final bytes to N-Pokemon and Pokestar Studios metadata. Unencrypted
offsets `0x04..0x05` are also unavailable: they contain the fast-mode and
bad-egg sanity flags.

Logger builds predating the split stored KOs at `0x64..0x65`. Readers fall
back to that legacy halfword when the split value is zero. The next eligible
battle update copies the value into `0x43`/`0x5E` and clears the legacy bytes,
so existing logged Pokemon migrate without losing their counts.

Every nonempty, non-egg Pokemon in the starting party gains one brought count
when an eligible trainer battle reaches a normal terminal result, including a
loss. A Pokemon gains one used count if the engine's persistent entered-battle
flag was set; switching it in repeatedly during the same battle still counts
once. Partner Pokemon are ignored, and a two-opponent battle increments these
participation counters once rather than once per trainer record.

KO increments reuse the attribution rules above. Unlike the compact trainer
record, which retains only the first attribution for each party slot, the
individual counter increments for every newly observed faint event. The three
counters saturate at `65535`. They continue updating if the 600-record save log
is full. A malformed PK5 checksum causes only that Pokemon's counter update to
be skipped; the trainer record and other valid party Pokemon are unaffected.

Normal vanilla Pokemon initialize these reserved bits to zero. Because the PK5
has no extra bytes for a counter-format signature, any pre-existing nonzero
reserved values are interpreted as prior counts.

## Enhanced Party Menu and Battle Log Integration (BW2)

`MenuEvolutionW2.dll` and `MenuEvolutionB2.dll` are optional, stripped
overlay-scoped companions to the individual-counter runtime. In the field
party menu they expose an `EVOLVE` command for the first matching evolution
record when the current level satisfies method `4`, or when the PK5 counters
satisfy methods `29` (KOs), `30` (battles brought), or `31` (battles used).
Method `29` also participates in the normal post-battle evolution pass after a
trainer-battle win when a Pokemon's KO counter increased during that battle.
Companion 1.3.1 hooks both the candidate pass and the separate `SHINKA_Check`
call in battle-return overlay 166 (B2 `0x0219D26A`, W2 `0x0219D2AA`). Earlier
companions marked the candidate but left that second call vanilla, so a KO-only
evolution never launched. Targets are bound to their destination party slots
before retail copyback, consumed once, and cleared at the next battle return;
the vanilla evolution result takes precedence. No new Pokemon/save fields or
battle-counter DLL changes are required. The DLL filenames remain unchanged.
Methods `30` and `31`
remain menu-only so merely ending a battle does not start an unexpected
evolution sequence.

The runtime accepts both retail 42-byte and expanded 48-byte evolution
members, resolves alternate-form personal IDs, rejects eggs and malformed PK5
checksums, and intentionally ignores Everstone. It reuses menu item
`PMIT_ENTER` only in field mode. A Pokemon with all four field moves omits the
command so the retail eight-entry menu storage cannot overflow.

Pokeweb stores the selected English retail-US party message-bank 178 entries in
the DLL's versioned `MEVOMSG` configuration field. After the evolution demo,
companion-triggered evolutions reopen the party menu in normal field mode;
they do not enter the vanilla Rare Candy continuation or print an item-use
message. Uninstalling the companion leaves the harmless text entries in place
so other message IDs never shift. The matching Black 2 or White 2
battle-counter DLL must remain installed.

### Party-menu move reminder (companion 1.3.0)

`RELEARN` opens the native BW2 move reminder (overlay 258), without a Heart
Scale charge. The list uses the selected Pokemon's current species/form
personal ID: level-up moves from `a/0/1/8` with requirements at or below its
level, followed by KO moves from `battlelog_ko/learnsets.narc` with requirements
at or below its individual PK5 KO counter. Already-known moves and duplicate
IDs are omitted. Pre-evolution learnsets are not inherited. Missing optional
KO data still permits ordinary relearning; malformed members contribute no
moves. Eggs, invalid PK5 checksums, and empty lists hide the command.

Both archives are read with a 32-move-per-source bound and a required
`FFFF FFFF` terminator. The merged list holds at most 64 moves plus its `FFFF`
terminator. The companion builds this list itself, avoiding the retail NPC
helper's smaller fixed learnset buffer, then reuses the native tutor's move
replacement, learning, and cancellation flow. Field menus have eight expanded
entries: EVOLVE has priority when only one spare entry is available; either
command is suppressed when it would overflow the menu (including field moves).

The field ProcLink event allocation is extended from `0x7c` to `0x84` bytes,
with the retail prefix unchanged. It intercepts only the private field-party
return `0x4d52`. The old party overlay finishes unloading before the reminder
is queued; its parameters/list live on event heap 4 until the reminder has
closed and unloaded. The retail party-to-party transition then frees the old
party parameters and reopens the party menu at the selected slot. Normal
party/summary/bag and scripted transitions continue through the retail event
callback. No PK5 layout, save format, or additional save writes are introduced.

The new verified call hook is overlay 12 `0x0215B498` (B2) / `0x0215B4D8` (W2).
Pokeweb also checks the retail event callback, unload wait, reminder parameter
layout, and overlay-258 callback table. Config v2 is 20 bytes: `MEVOMSG\0`,
`u16 version=2`, `u16 evolveId`, `u16 evolveIdXor`, `u16 relearnId`,
`u16 relearnIdXor`, `u16 reserved=0`. Complements are XOR `0xffff`; the bundled
IDs are `0xffff` until Pokeweb appends/reuses `EVOLVE` and `RELEARN` and fills
both fields. Updating preserves existing KO learnsets and message IDs.

Native tests cover filtering, thresholds, level 100, deduplication, malformed
members, maximum list/menu capacity, and event-dispatch gating. Installer
checks cover both US ROMs, rejected altered tutor hooks, stripping, configured
text, idempotent installs, KO-data preservation, and exported-ROM reloads.
Gameplay validation (empty/full movesets, cancelling, repeated relearning,
alternate forms, field moves, and returning to other menus) remains an ad hoc
user test; no emulator tests are run by these checks.

The BW2 counter runtime can also teach moves immediately after a credited KO.
It reads `battlelog_ko/learnsets.narc`, an append-only NitroFS file generated by
Pokeweb when Menu Evolution is installed. The archive has one member per
personal/form ID. Each member uses the retail learnset layout: repeated
little-endian `{ u16 move, u16 requiredKOs }` entries followed by
`{ 0xFFFF, 0xFFFF }`, with at most 32 moves. A move whose threshold is crossed
by the newly credited KO enters the existing battle move-learning sequence,
including the ordinary four-move replacement prompt. Existing NitroFS file
IDs and NARC member IDs are not renumbered.

BW2 runtime v6 matches pending KO-learning requests by the original player
battle ID (0–5) plus PID, not by PK5 pointer: the server and client own distinct
copies of each party Pokémon. The client move-learning hook receives its
`BattleMon` from the retail caller's stack so switching/party sorting cannot
transfer a request to another slot. A zero-EXP display command runs the normal
learning sequence even when no EXP is awarded. The archive's existence is
checked before queuing that command; installing Battle Log without the
optional KO-move archive remains supported. Updating a ROM requires a fresh
boot, since existing emulator savestates retain the old loaded DLL code.

BW2 runtime v7 relocates the zero-EXP transition hook to the initial
`cmp exp, #0` / conditional branch pair. The later `str r0, [seq]` is a shared
tail reached by the normal level-up and move-learning states; it must remain
unpatched. V6 overwrote that tail with the second halfword of a Thumb BL,
causing a crash when the move-learning sequence finished. Nonzero-EXP paths
continue at the original instruction after the comparison, while zero-EXP
learning exits through the retail end-of-frame epilogue.

BW2 runtime v8 distinguishes those KO-only learning sessions from real
level-ups. KO-only sessions skip the retail level learnset until the learning
loop returns NONE, including while learning/replacement/decline prompts are
open. This prevents a later KO from offering the current level's moves again
(notably a declined level-100 move). Genuine level-up sessions still check
level moves first and pending KO moves afterward. The session flag resets on
completion or battle cleanup; PK5 and battle-history formats are unchanged.

The companion also extends the retail field-script command `0x010C`
(`GetPartyPokeParameter`). Its existing three operands remain destination work
variable, zero-based party slot, and parameter ID. Retail parameter IDs are
unchanged; the following read-only IDs return the individual Pokemon's `u16`
counters:

| Parameter ID | Value |
| --- | --- |
| `0x0400` | KOs |
| `0x0401` | Battles brought to |
| `0x0402` | Battles used in |

For example, after the retail party-selection command `0x0103` has written a
slot from `0` through `5`, a script can call `0x010C` with parameter `0x0400`
and compare the destination work variable with `100`. Invalid party slots,
invalid PK5 checksums, and unsupported parameter IDs return zero. The command
does not modify the Pokemon.

## Summary display

The Pokémon summary info page displays the number of player-KO attribution
fields credited to the displayed species or any of its evolutionary ancestors
in the existing `ID No.` value field. ROM builds may rename system message bank
179 entry 15 to `Frags`; the runtime does not require or modify that text. For
example, Charmeleon includes Charmander, while Vaporeon includes Eevee but not
Jolteon or another sibling evolution. Records contain species, not personality
values, so multiple Pokémon of the same species share this count. A full
600-record log can contain at most 3,600 credited player KOs; the summary
renders four digits without leading zeroes.

## Generated ancestry archive

The ancestry table is stored outside the summary DLL as
`battlelog/ancestry.narc`. The dedicated directory lets ROM builders append
the archive without renumbering any existing NitroFS file IDs. It contains
1,024 small members indexed by the
10-bit species ID. A member starts with a one-byte format version (`1`), a
one-byte species count, and that many little-endian `u16` species IDs. The summary DLL
opens the archive only while formatting the summary, reads that one member into
stack memory, closes the file, and then scans the save records once. It does not
allocate from the PMC heap or keep the ancestry table in an overlay.

White2Upgrade generates the archive from the same compiled 48-byte evolution
members used to build `a/0/1/9`, so data edits automatically update family
aggregation. The generator also accepts vanilla White 2's seven-slot, 42-byte
members and supports an extracted ROM's packed evolution NARC:

```sh
python3 tools/battle_log/build_ancestry_narc.py \
  --evolution-narc a_0_1_9.narc \
  --output battlelog/ancestry.narc
```

The Pokeweb Serverless installer selects the matching stripped battle,
counter, and summary DLL set for Black, White, Black 2, or White 2, adds the
generated ancestry NARC, and
disables that version's ARM9 Wi-Fi List copy routine. It leaves summary text to
the normal text editor and regenerates the ancestry NARC from the project's
current evolution mappings each time it installs. Apart from the two-byte
save-ownership patch, the version-specific runtimes use their base game's
relocated battle-overlay 167 and summary-overlay 207 entry points. If the
ancestry NARC is missing or invalid, the summary safely falls back to counting
only the displayed species.
