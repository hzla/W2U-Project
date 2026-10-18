# Text banks in the decomp's format

`tools/decomp/export_text.py` writes W2U's system text banks (`data/text/system/<n>.toml`, W2U's notation:
`[VAR PKNICK(0)]` and so on) in the pokebw2 decomp's text format: `data/text/system/<bank>.txt`, one message per line
(`ID = text`, `\n` line breaks, `{TTTT:a,b}` control codes, `\x{HHHH}` characters, `\c` compressed messages, a last
`\pad{XX}` line). The default is banks 18 (battle messages) and 19 (standard battle messages), where W2U adds the
messages its mechanics use. Ability names and descriptions (banks 374 / 375) come from the decomp's ability JSON
instead (`decomp-ability-export.md`). Only the decomp's text files are read.

```sh
python tools/decomp/export_text.py --decomp=PATH/TO/pokebw2 --check [--banks=18,19]
```

Output in `work/decomp_text/` (ignored). W2U's text goes through `tools/text/gen5_text.py` to code units, then into the
decomp's line format. IDs: a message the decomp has keeps the decomp's ID (by position: the decomp's code names
messages by ID); one W2U adds gets an ID the way the decomp's unpacker names them (the bank's prefix and the first
words, numbered from `_2`). A message ending in spaces writes its last one as `\x{0020}` (a line can't end in spaces).

`--check` lists the retail messages whose W2U text differs from the decomp's, reads every written line back and
compares its code units with W2U's, and checks that the IDs are unique.

As of 2026-10-17: bank 18 has 1,470 messages (311 added by W2U), bank 19 233 (32 added). 13 retail messages in bank 18
have W2U's own text: the Mega Evolution messages in the slots of "completely synchronized" and "the sea of fire"
(1153-1158), a better line break in the item-passing messages (1114-1117) and three blank placeholders without their
second terminator (878-880); they keep the decomp's IDs, so a few IDs no longer describe their text. A decomp build
with these banks gives banks 18, 19, 374 and 375 identical to W2U's ROM, message for message.

A decomp build that takes W2U's abilities has to keep Easy Chat's ability words at the retail 164: its word tables in
the main program count the ability names' file.
