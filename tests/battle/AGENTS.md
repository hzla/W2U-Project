# Battle mechanic regression tests

Keep move/ability scenarios, fixture builders, native runners, independent
oracles and their unit tests in this directory, not in Pokeweb-Serverless.
Read README.md before adding or modifying a suite. Use tools/test_battle.py
from the upgrade repository root for execution and strict TypeScript checks.
Pokeweb's production ROM/save editors remain an external dependency; do not
copy them or the browser application here. Keep generated evidence in ignored
work/, remove generated ROMs and snapshots by default, and retain fixture saves.
