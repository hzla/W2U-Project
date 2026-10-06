# Gen 6/7 ability and battle-item audit

Work is on `main`. Tests, fixtures and independent oracles live in
`tests/battle/`; Pokeweb supplies only the ROM/save authoring dependency.
This is focused behavioral coverage, not an exhaustive interaction certification.

## Fixes

- Bulletproof: corrected legacy ball/bomb move flags, including Shadow Ball.
- Refrigerate, Pixilate, Aerilate and Galvanize: grant the 20% power boost
  only after an actual Normal-type conversion, not to naturally matching types.
- Tough Claws: corrected the fixed-point multiplier from approximately 4/3
  to 1.3.
- Merciless: preserve a forced-critical request across BW2's rank clamp.
  Native Battle Armor, Shell Armor and Lucky Chant prevention still wins.
- Protective Pads: the original failing fixture held Mega Ring (124), not
  Protective Pads (114). Corrected the fixture and added an item-ID guard;
  no item-ID reassignment or unnecessary handler change.
- Shields Down: Meteor forms prevent major status/Yawn; exactly half HP
  qualifies for Core form. Core status and healing controls are included.
- Grass Pelt: added 1.5x Defense on Grassy Terrain in the existing defense DLL.
- Stakeout: double the attacking stat, rather than base power, after a native
  opponent replacement. Initial send-out and next-turn controls are included.
- Per the chosen Gen 7 policy, Parental Bond's second hit has quarter **final
  damage**, and Disguise breaks without an HP cost. Fixed-damage moves retain
  full damage on both hits; native multistrike moves receive no extra hit.

No new DLL group, public module ABI, loader allocation or shared-state layout
was added. The registry and generated routes/API entries remain synchronized.
Audit trainers explicitly have empty bags. Inherited X-items initially consumed
the opponent's action in two KO/survivor fixtures; those were fixture errors,
not failed Battle Bond or Innards Out effects. Opponent PP/action assertions
remain mandatory. The runner also supports `--reverse-cases` for isolation checks.

## Added coverage

Twenty previously uncovered ability IDs now have authored native scenarios:

- Stance Change, Shields Down, Schooling, Power Construct, Disguise, Battle Bond:
  form changes, relevant HP/level controls, and damage-preserving HP-pool growth.
- Parental Bond: ordinary/fixed/multistrike damage, status control, next-action reset.
- Grass Pelt, Battery, Stakeout: terrain/ally/switch prerequisites and no-boost controls.
- Triage: Recover precedes +2 Extreme Speed; ordinary attacks retain normal priority.
- Symbiosis: real Substitute payment consumes Sitrus, transfers the donor's item,
  and allows the transferred Leftovers to heal; no-ability control.
- Dancer: native copied dance, one ordinary action, and no extra copied-move PP cost.
- Receiver, Power of Alchemy: allied faint copies an eligible ability; living ally control.
- Soul-Heart, Beast Boost: real KO boosts, allied-faint coverage, survivor controls.
- Innards Out: KO retaliation equals pre-hit HP; survival control.
- Wimp Out, Emergency Exit: native party selection after crossing half HP,
  with already-low and still-above-half controls.

Four abilities remain explicitly blocked by scope choice: Primordial Sea,
Desolate Land, Delta Stream and RKS System. Strong-weather rules and the
Silvally/Memory item typing system were not implemented or certified.

## Verification

On 2026-10-05, **176/176 native scenarios passed**: 143 ability scenarios and
33 item scenarios, covering 64 ability IDs and all 13 implemented Gen 6/7
battle items. Four complete ability batches and one item batch used the same
fresh stripped ROM; a further four KO/survivor checks passed in reverse order.
The independent combined receipt is `work/battle-tests/gen67-final-summary.json`.
Its completeness check rejects missing, changed or failed scenarios rather than
counting earlier mismatched fixture results.

The ROM SHA-256 is
`490fa181ca6cd5b01dfcc62de6efdad01b6eb509af463de79bc195554af36a7b`.
The identical rebuilt image is copied to the repository's parent directory as
`White2Upgrade-main-gen67-abilities-items-20261005.nds`. Existing ROMs/saves were
preserved. Work remains uncommitted on `main`; integration work is untouched.

Also passing: 170 host battle tests, 89 repository tool tests, strict TypeScript
checking, registry validation (22 groups / 230 API entries), source/archive
privacy scanning, and fourteen selected legacy move scenarios cross-checking
the new Parental Bond/Disguise policy. These focused reruns do not certify the
complete legacy move catalog or every generation-specific exception.

Expectations are independent of DLL outputs. Tests read actual damage, HP,
forms, stages, items, action order, PP, native party selections and validated
loader telemetry. Only pre-input setup and RNG draws are controlled; results
and child-handler calls are not forced. Host fault injection rejects absent
DLLs, wrong damage/rounding, missing form/copy/HP changes and stale strike HP.

Fixtures disable animations. Generated output is ignored under `work/`;
fixture ROMs and snapshots are removed, while fixture saves remain cached.

The heap audit now counts retained BSS. The stripped core is 68,700 bytes;
the conservative all-22-groups resident set uses 153,352 bytes of the 167,936-byte
PMC heap, leaving 14,584 bytes (14.24 KiB). This clears the 12 KiB reserve,
but the unchanged pre-refactor baseline's no-custom and largest-single-group
savings gates fail. The old calculation omitted 21,120 bytes of resident BSS.
That accounting fix does not allocate additional memory in the game. These
are static size estimates, not a native all-groups peak-allocation stress test.

The White 2 stripped ROM and Black 2 static DLL/signature checks build. The
old White 2 binary hash guard rejects the intentionally changed core; its
baseline was not refreshed. Black 2 native gameplay and the guarded complete
Black 2 ROM package are not claimed verified.

```sh
python3 tools/test_battle.py ability --suite gen67 --rom ./game.nds --continue-on-failure
python3 tools/test_battle.py item --suite gen67 --rom ./game.nds --continue-on-failure
python3 tools/test_battle.py ability --suite gen67 --rom ./game.nds --variant parental-bond --variant grass-pelt
python3 tools/test_battle.py unit
```

Remaining interaction gaps include full form-transition timing/switch restoration,
ability-copy exclusions, every raw-stat tie, multistrike/contact exceptions,
broader doubles redirection, and battle reload/teardown. A passing focused case
does not establish all clauses of an ability's description.

Rules: [Parental Bond](https://bulbapedia.bulbagarden.net/wiki/Parental_Bond_(Ability)),
[Disguise](https://bulbapedia.bulbagarden.net/wiki/Disguise_(Ability)),
[Shields Down](https://bulbapedia.bulbagarden.net/wiki/Shields_Down_(Ability)),
[Grass Pelt](https://bulbapedia.bulbagarden.net/wiki/Grass_Pelt_(Ability)),
[Stakeout](https://bulbapedia.bulbagarden.net/wiki/Stakeout_(Ability)),
[Merciless](https://bulbapedia.bulbagarden.net/wiki/Merciless_(Ability)),
and [Recover](https://bulbapedia.bulbagarden.net/wiki/Recover_(move)).
