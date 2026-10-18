#!/usr/bin/env python3
"""Export W2U's system text banks to the pokebw2 decomp's text format.

usage: python tools/decomp/export_text.py --decomp=PATH [--out=DIR] [--banks=18,19] [--check]

The decomp (github.com/fuddlesworth/pokebw2) keeps each message file of the system text archive (a/0/0/2) as
data/text/system/<bank>.txt, one message per line: `ID = text`, with `\\n` for a line break, `{TTTT:a,b}` for a control
code, `\\x{HHHH}` for a character it can't show, `\\c` before a compressed message, and a last `\\pad{XX}` line
(tools/text/text_data.py). This writes W2U's banks (data/text/system/<n>.toml, W2U's own notation: `[VAR PKNICK(0)]`
and so on, read through tools/text/gen5_text.py) in that format, so a decomp-based W2U has W2U's text, including the
messages W2U adds after the retail ones (W2U's battle mechanics' messages in bank 18, its standard messages in 19).

IDs: a message the decomp already has keeps the decomp's ID (by position, as the game numbers them); a message W2U
adds gets one the way the decomp's unpacker names messages: the bank's prefix and the first words, numbered from _2
where they repeat. Only the decomp's text files are read; none of its code runs.

--check reports the retail messages whose W2U text differs from the decomp's, re-reads every written line with the
decomp's line rules (in this file) and compares its code units with W2U's, and checks that the IDs are unique.
"""

from __future__ import annotations

import argparse
import re
import sys
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "text"))
import gen5_text  # noqa: E402  (W2U's text codec)

TEXT = ROOT / "data" / "text" / "system"
LINE_END, NEWLINE, CONTROL, COMPRESSED = 0xFFFF, 0xFFFE, 0xF000, 0xF100
ESCAPED = {"\\": "\\\\", "{": "\\{", "}": "\\}"}
MESSAGE = re.compile(r"([A-Za-z_]\w*) =(?: (.*))?")
STOP_WORDS = {"a", "an", "the", "and", "or", "of", "to", "is", "it", "i", "you", "your", "my", "me", "be", "in", "on",
              "for", "this", "that", "are", "was", "with", "at", "as", "so", "do"}


def printable(c: int) -> bool:
    if c < 0x20 or 0xD800 <= c < 0xF900 or c >= CONTROL:
        return False
    return chr(c).isprintable()


def format_message(chars: list[int], compressed: bool) -> str:
    """A message (no terminator) as a line of the decomp's text (its text_data.py format_message)."""
    out = ["\\c"] if compressed else []
    i = 0
    while i < len(chars):
        c = chars[i]
        if c == CONTROL and i + 2 < len(chars) and i + 3 + chars[i + 2] <= len(chars):
            kind, count = chars[i + 1], chars[i + 2]
            args = chars[i + 3:i + 3 + count]
            out.append(f"{{{kind:04x}" + (":" + ",".join(map(str, args)) if count else "") + "}")
            i += 3 + count
            continue
        if c == NEWLINE:
            out.append("\\n")
        elif printable(c):
            out.append(ESCAPED.get(chr(c), chr(c)))
        else:
            out.append(f"\\x{{{c:04x}}}")
        i += 1
    # A line can't end in spaces (they would be trimmed); the last one is written \x{0020}, which reads back as one
    if out and out[-1] == " ":
        out[-1] = "\\x{0020}"
    return "".join(out)


def parse_message(text: str) -> tuple[list[int], bool]:
    """A line of the decomp's text back to code units (its text_data.py parse_message), for --check."""
    compressed = text.startswith("\\c")
    if compressed:
        text = text[2:]
    chars, i = [], 0
    while i < len(text):
        ch = text[i]
        if ch == "\\":
            nxt = text[i + 1]
            if nxt == "n":
                chars.append(NEWLINE)
                i += 2
            elif nxt == "x":
                end = text.index("}", i)
                chars.append(int(text[i + 3:end], 16))
                i = end + 1
            else:
                chars.append(ord(nxt))
                i += 2
        elif ch == "{":
            end = text.index("}", i)
            kind, _, args = text[i + 1:end].partition(":")
            values = [int(a) for a in args.split(",")] if args else []
            chars += [CONTROL, int(kind, 16), len(values), *values]
            i = end + 1
        else:
            chars.append(ord(ch))
            i += 1
    return chars, compressed


def id_base(prefix: str, message: str) -> str:
    """The decomp unpacker's ID for a message, before numbering (its text_data.py message_ids)."""
    text = re.sub(r"\\x\{[^}]*\}|\{[^}]*\}|\\[nc]|\\.", " ", message)
    text = text.replace("é", "e").replace("É", "E").replace("’", "'")
    words = [w.replace("'", "") for w in re.findall(r"[A-Za-z0-9][A-Za-z0-9']*", text)]
    words = [w for w in words if w.lower() not in STOP_WORDS] or words
    return prefix + ("".join(w[:1].upper() + w[1:].lower() for w in words[:4]) or "Empty")


def w2u_messages(bank: int) -> list[tuple[list[int], bool]]:
    """W2U's messages of a bank, in order: code units without the final terminator, and whether compressed."""
    doc = tomllib.loads((TEXT / f"{bank}.toml").read_text(encoding="utf-8"))
    entries = doc["msg"]["section_0"]["entries"]
    out = []
    for index in range(max(int(k) for k in entries) + 1):
        entry = entries.get(str(index), {"text": ["$"]})
        units = gen5_text.parse_plaintext_units(entry["text"])
        if units and units[-1] == LINE_END:
            units = units[:-1]
        out.append((units, bool(entry.get("compressed"))))
    return out


def decomp_lines(path: Path) -> tuple[list[tuple[str, str]], str | None]:
    """The decomp's messages of a bank, (ID, text), and its \\pad line"""
    messages, pad = [], None
    for line in path.read_text(encoding="utf-8").splitlines():
        if line.startswith("\\pad{"):
            pad = line
            continue
        match = MESSAGE.fullmatch(line)
        if not match:
            raise SystemExit(f"{path}: not a message line: {line[:60]!r}")
        messages.append((match[1], match[2] or ""))
    return messages, pad


def export_bank(bank: int, decomp: Path, out: Path, check: bool) -> list[str]:
    name = f"{bank:04d}.txt"
    retail, pad = decomp_lines(decomp / "data" / "text" / "system" / name)
    prefix = f"Bank{bank:04d}_Text_"
    messages = w2u_messages(bank)
    if len(messages) < len(retail):
        raise SystemExit(f"bank {bank}: W2U has {len(messages)} messages, fewer than the decomp's {len(retail)}")
    used = {i for i, _ in retail}
    count: dict[str, int] = {}
    for message_id in used:
        base = re.sub(r"_\d+$", "", message_id)
        count[base] = max(count.get(base, 0), int(message_id.rsplit("_", 1)[1]) if message_id != base else 1)
    lines, problems, changed = [], [], []
    for index, (units, compressed) in enumerate(messages):
        text = format_message(units, compressed)
        if index < len(retail):
            message_id = retail[index][0]
            if text != retail[index][1]:
                changed.append(f"{bank}.{index} {message_id}: decomp {retail[index][1]!r} -> W2U {text!r}")
        else:
            base = id_base(prefix, text)
            count[base] = count.get(base, 0) + 1
            message_id = base if count[base] == 1 else f"{base}_{count[base]}"
            while message_id in used:
                count[base] += 1
                message_id = f"{base}_{count[base]}"
        used.add(message_id)
        lines.append(f"{message_id} = {text}".rstrip())
        if check:
            back, back_compressed = parse_message(text)
            if back != units or back_compressed != compressed:
                problems.append(f"{bank}.{index}: the line does not read back to W2U's code units")
    if pad:
        lines.append(pad)
    target = out / "data" / "text" / "system" / name
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text("\n".join(lines) + "\n", encoding="utf-8")
    ids = [line.split(" =", 1)[0] for line in lines if not line.startswith("\\pad{")]
    if check and len(ids) != len(set(ids)):
        problems.append(f"bank {bank}: duplicate IDs")
    print(f"bank {bank}: {len(messages)} messages ({len(messages) - len(retail)} added by W2U, {len(changed)} retail "
          f"messages with W2U's own text) -> {target}")
    if check:
        for c in changed:
            print("  changed " + c)
    return problems


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True, help="a pokebw2 checkout (only its text is read)")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_text")
    parser.add_argument("--banks", default="18,19", help="system text banks, comma-separated (default 18,19)")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    problems = []
    for bank in (int(b) for b in args.banks.split(",")):
        problems += export_bank(bank, args.decomp, args.out, args.check)
    if args.check:
        print(f"check: {len(problems)} problem(s)")
        for p in problems[:40]:
            print("  " + p)
        if problems:
            sys.exit(1)


if __name__ == "__main__":
    main()
