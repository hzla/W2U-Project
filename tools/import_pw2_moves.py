#!/usr/bin/env python3
"""Import Generation 7-9 move records and text from PW2Code.

PW2Code stores expanded move records as loose 36-byte files and expanded
message banks as compiled Gen 5 message files. This tool translates those
inputs into White2Upgrade's checked-in TOML data while preserving this repo's
move-flag ABI and placeholder-animation policy.
"""

from __future__ import annotations

import argparse
import copy
import re
import struct
import sys
import tempfile
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO_ROOT))

from tools.text.gen5_text import (  # noqa: E402
    decode_message_file,
    normalize_entry,
    read_toml,
    text_units_to_plaintext,
    write_toml,
)


FIRST_MOVE = 622
LAST_MOVE = 919
MOVE_COUNT = LAST_MOVE - FIRST_MOVE + 1
MOVE_RECORD_SIZE = 36
MOVE_END_MSG = LAST_MOVE + 1
TACKLE_ANIMATION_ID = 0
TARGET_PADDING = 21331

TYPE_NAMES = [
    "TYPE_NORMAL", "TYPE_FIGHTING", "TYPE_FLYING", "TYPE_POISON",
    "TYPE_GROUND", "TYPE_ROCK", "TYPE_BUG", "TYPE_GHOST",
    "TYPE_STEEL", "TYPE_FIRE", "TYPE_WATER", "TYPE_GRASS",
    "TYPE_ELECTRIC", "TYPE_PSYCHIC", "TYPE_ICE", "TYPE_DRAGON",
    "TYPE_DARK", "TYPE_FAIRY",
]
QUALITY_NAMES = [
    "EFFECT_NO_SPECIAL_EFFECT",
    "EFFECT_STATUS_INFLICTING",
    "EFFECT_TARGET_STAT_CHANGING",
    "EFFECT_HEALING",
    "EFFECT_CHANCE_TO_INFLICT_STATUS",
    "EFFECT_RAISING_TARGET_STAT",
    "EFFECT_DAMAGE_AND_TARGET_STAT_EFFECT",
    "EFFECT_DAMAGE_AND_USER_STAT_EFFECT",
    "EFFECT_LIFE_STEAL",
    "EFFECT_OHKO",
    "EFFECT_FIELD_EFFCT",
    "EFFECT_SIDE_EFFCT",
    "EFFECT_FORCE_SWITCH_OUT",
    "EFFECT_OTHERS",
]
CATEGORY_NAMES = ["SPLIT_STATUS", "SPLIT_PHYSICAL", "SPLIT_SPECIAL"]
STATUS_NAMES = [
    "STATUS_NONE", "STATUS_PARALYZE", "STATUS_SLEEP", "STATUS_FREEZE",
    "STATUS_BURN", "STATUS_POSION", "STATUS_CONFUSE", "STATUS_INFATUATE",
    "STATUS_BINDING", "STATUS_NIGHTMARE", "STATUS_CURSED", "STATUS_TAUNT",
    "STATUS_TORMENT", "STATUS_DISABLE_LAST_MOVE", "STATUS_NEXT_TURN_SLEEP",
    "STATUS_HEAL_BLOCK", "STATUS_DISBALE_ABILITY", "STATUS_FORESIGHT",
    "STATUS_LEECH_SEED", "STATUS_BLOCK_ITEM", "STATUS_PERISH_SONG",
    "STATUS_INGRAIN", "STATUS_CANT_ESCAPE", "STATUS_ENCORE",
]
DURATION_NAMES = [
    "INFLICT_DURATION_NONE", "INFLICT_DURATION_PERMANENT",
    "INFLICT_DURATION_TURN", "INFLICT_DURATION_POKE",
    "INFLICT_DURATION_POKE_TURN",
]
STAT_NAMES = [
    0, "STAT_ATK", "STAT_DEF", "STAT_SPATK", "STAT_SPDEF", "STAT_SPEED",
    "STAT_ACCURACY", "STAT_EVASION", "STAT_ALL",
]
TARGET_NAMES = [
    "TARGET_OTHER_SELECT", "TARGET_FRIEND_AND_USER", "TARGET_FRIEND_SELECT",
    "TARGET_ENEMY_SELECT", "TARGET_OTHER_ALL", "TARGET_ENEMY_ALL",
    "TARGET_FRIEND_ALL", "TARGET_USER", "TARGET_ALL", "TARGET_ENEMY_RANDOM",
    "TARGET_FIELD", "TARGET_FIELD_SIDE_ENEMY", "TARGET_FIELD_SIDE_FRIEND",
    "TARGET_UNKNOWN",
]

# PW2Code's bits 15-17 predate this repo's Bullet/Bite/Pulse allocation.
# Wind and Sharp are moved into unused target bits; bit 18 remains the
# expanded healing property consumed by MOVE_FLAG_INDEX_HEALING.
SOURCE_FLAG_TO_TARGET = {
    0: (0, "FLAG_CONTACT"),
    1: (1, "FLAG_REQUIRES_CHARGE"),
    2: (2, "FLAG_RECHARGE_TURN"),
    3: (3, "FLAG_BLOCKED_BY_PROTECT"),
    4: (4, "FLAG_REFLECTED_BY_MAGIC_COAT"),
    5: (5, "FLAG_STOLEN_BY_SNATCH"),
    6: (6, "FLAG_COPIED_BY_MIRROR_MOVE"),
    7: (7, "FLAG_PUNCH_MOVE"),
    8: (8, "FLAG_SOUND_MOVE"),
    9: (9, "FLAG_GROUNDED_BY_GRAVITY"),
    10: (10, "FLAG_DEFROSTS_TARGETS"),
    11: (11, "FLAG_HITS_NON_ADJACENT_OPPONENTS"),
    12: (12, "FLAG_HEALING_MOVE"),
    13: (13, "FLAG_HITS_THROUGH_SUBSTITUTE"),
    14: (14, "FLAG_POWDER"),
    15: (20, "FLAG_BULLET"),
    16: (21, "FLAG_BITE"),
    17: (22, "FLAG_PULSE"),
    18: (18, "FLAG_HEALING_PROPERTY"),
    19: (19, "FLAG_DANCE"),
    20: (16, "FLAG_WIND"),
    21: (17, "FLAG_SHARP"),
}

MOVE_STRUCT = struct.Struct("<BBBBBBbBHBBBBBBHbbB3b3b3bHI")


def quoted(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"') + '"'


def display_name(entry: dict) -> str:
    text = "".join(text_units_to_plaintext(entry.get("code_units", [])))
    if not text.endswith("$"):
        raise ValueError(f"move-name entry is missing terminator: {text!r}")
    return text[:-1]


def move_label(name: str) -> str:
    label = name.upper().replace("É", "E")
    for char in ("'", "’", ".", ","):
        label = label.replace(char, "")
    label = label.replace("-", "").replace(" ", "_")
    label = re.sub(r"[^A-Z0-9_]", "", label)
    return "MOVE_" + label


def enum_value(values: list, index: int, field: str, move_id: int):
    if not 0 <= index < len(values):
        raise ValueError(f"move {move_id}: invalid {field} value {index}")
    return values[index]


def toml_atom(value) -> str:
    return quoted(value) if isinstance(value, str) else str(value)


def translate_flags(source: int, move_id: int) -> tuple[int, list[str]]:
    target = 0
    names: list[str] = []
    remaining = source
    for source_bit, (target_bit, name) in SOURCE_FLAG_TO_TARGET.items():
        mask = 1 << source_bit
        if source & mask:
            target |= 1 << target_bit
            names.append(name)
            remaining &= ~mask
    if remaining:
        raise ValueError(
            f"move {move_id}: unsupported PW2Code move-flag bits 0x{remaining:08X}"
        )
    return target, names


def parse_record(move_id: int, data: bytes) -> dict:
    if len(data) != MOVE_RECORD_SIZE:
        raise ValueError(
            f"move {move_id}: expected {MOVE_RECORD_SIZE} bytes, got {len(data)}"
        )
    values = MOVE_STRUCT.unpack(data)
    (
        move_type, quality, category, power, accuracy, base_pp, priority,
        packed_hits, status, inflict_chance, duration, turn_min, turn_max,
        crit_stage, flinch_rate, _source_animation, recoil, heal, target,
        stat1, stat2, stat3, stage1, stage2, stage3,
        chance1, chance2, chance3, _source_padding, source_flags,
    ) = values
    if status == 0xFFFF:
        status_name = "STATUS_SPECIAL_CODE"
    else:
        status_name = enum_value(STATUS_NAMES, status, "status", move_id)
    _, flag_names = translate_flags(source_flags, move_id)
    return {
        "type": enum_value(TYPE_NAMES, move_type, "type", move_id),
        "quality": enum_value(QUALITY_NAMES, quality, "quality", move_id),
        "category": enum_value(CATEGORY_NAMES, category, "category", move_id),
        "power": power,
        "accuracy": "MUST_HIT" if accuracy == 101 else accuracy,
        "base_pp": base_pp,
        "priority": priority,
        "packed_hits": packed_hits,
        "status": status_name,
        "inflict_chance": inflict_chance,
        "duration": enum_value(DURATION_NAMES, duration, "duration", move_id),
        "turn_min": turn_min,
        "turn_max": turn_max,
        "crit_stage": crit_stage,
        "flinch_rate": flinch_rate,
        "recoil": recoil,
        "heal": heal,
        "target": enum_value(TARGET_NAMES, target, "target", move_id),
        "stats": [
            enum_value(STAT_NAMES, stat1, "stat", move_id),
            enum_value(STAT_NAMES, stat2, "stat", move_id),
            enum_value(STAT_NAMES, stat3, "stat", move_id),
        ],
        "stages": [stage1, stage2, stage3],
        "chances": [chance1, chance2, chance3],
        "source_flags": source_flags,
        "flag_names": flag_names,
    }


def render_record(label: str, record: dict) -> str:
    flags = " | ".join(record["flag_names"])
    flag_value = quoted(flags) if flags else "0"
    hit_min = record["packed_hits"] & 0xF
    hit_max = record["packed_hits"] >> 4
    lines = [
        f"[{label}]",
        f"Type = {quoted(record['type'])}",
        f"Quality = {quoted(record['quality'])}",
        f"Category = {quoted(record['category'])}",
        f"Power = {record['power']}",
        f"Accuracy = {toml_atom(record['accuracy'])}",
        f'"Base PP" = {record["base_pp"]}',
        f"Priority = {record['priority']}",
        f'Hit = {quoted(f"{hit_min} | {hit_max}")}',
        f'"Inflict Status" = {quoted(record["status"])}',
        f'"Inflict Chance" = {record["inflict_chance"]}',
        f'"Inflict Duration" = {quoted(record["duration"])}',
        f'"Turn (min)" = {record["turn_min"]}',
        f'"Turn (max)" = {record["turn_max"]}',
        f'"Critical Hit Stage" = {record["crit_stage"]}',
        f'"Flinch Rate" = {record["flinch_rate"]}',
        f'"Move Animation ID" = {TACKLE_ANIMATION_ID}',
        f"Recoil = {record['recoil']}",
        f"Heal = {record['heal']}",
        f"Target = {quoted(record['target'])}",
        '"Status Change Stats" = [' + ", ".join(map(toml_atom, record["stats"])) + "]",
        '"Status Change Stages" = [' + ", ".join(map(str, record["stages"])) + "]",
        '"Status Change Chances" = [' + ", ".join(map(str, record["chances"])) + "]",
        f"Padding = {TARGET_PADDING}",
        f"Flags = {flag_value}",
        "",
    ]
    return "\n".join(lines)


def replace_move_enum_tail(text: str, style: str, rows: list[tuple[int, str]]) -> str:
    lines = text.splitlines()
    kept: list[str] = []
    if style == "yml":
        pattern = re.compile(r"^  - (MOVE_[A-Z0-9_]+): (\d+)$")
        emit = lambda label, value: f"  - {label}: {value}"
    elif style == "toml":
        pattern = re.compile(r'^"(MOVE_[A-Z0-9_]+)" = (\d+)$')
        emit = lambda label, value: f'"{label}" = {value}'
    elif style == "header":
        pattern = re.compile(r"^#define (MOVE_[A-Z0-9_]+) (\d+)$")
        emit = lambda label, value: f"#define {label} {value}"
    else:
        raise ValueError(style)

    for line in lines:
        match = pattern.match(line)
        if match and int(match.group(2)) >= FIRST_MOVE:
            continue
        if style == "header" and line == "#endif":
            continue
        kept.append(line)
    while kept and not kept[-1]:
        kept.pop()
    kept.extend(emit(label, move_id) for move_id, label in rows)
    kept.append(emit("MOVE_END_MSG", MOVE_END_MSG))
    if style == "header":
        kept.extend(["", "#endif"])
    return "\n".join(kept) + "\n"


def render_message_toml(doc: dict) -> str:
    with tempfile.TemporaryDirectory() as tmp:
        output = Path(tmp) / "message.toml"
        write_toml(doc, output)
        return output.read_text(encoding="utf-8")


def replace_message_tail(
    target_path: Path,
    prefix_count: int,
    replacements: list[dict],
) -> str:
    target = read_toml(target_path)
    if len(target["entries"]) < prefix_count:
        raise ValueError(
            f"{target_path}: expected at least {prefix_count} entries, "
            f"got {len(target['entries'])}"
        )
    target["entries"] = target["entries"][:prefix_count] + copy.deepcopy(replacements)
    target["payload_start"] = 4 + len(target["entries"]) * 8
    return render_message_toml(target)


def collect_outputs(repo: Path, pw2code: Path) -> tuple[dict[Path, str], int]:
    records_dir = pw2code / "Assets/a/0/2/1"
    text_dir = pw2code / "Assets/a/0/0/2"
    missing = [move_id for move_id in range(FIRST_MOVE, LAST_MOVE + 1)
               if not (records_dir / str(move_id)).is_file()]
    if missing:
        raise ValueError(f"missing PW2Code move records: {missing}")

    source_names_doc = decode_message_file((text_dir / "403").read_bytes())
    source_caps_doc = decode_message_file((text_dir / "488").read_bytes())
    source_battle_doc = decode_message_file((text_dir / "16").read_bytes())
    for name, doc, minimum in (
        ("move names", source_names_doc, LAST_MOVE + 1),
        ("uppercase move names", source_caps_doc, LAST_MOVE + 1),
        ("battle move strings", source_battle_doc, (LAST_MOVE + 1) * 3),
    ):
        if len(doc["entries"]) < minimum:
            raise ValueError(f"PW2Code {name}: expected {minimum} entries")

    names = {
        move_id: display_name(source_names_doc["entries"][move_id])
        for move_id in range(FIRST_MOVE, LAST_MOVE + 1)
    }
    rows = [(move_id, move_label(names[move_id]))
            for move_id in range(FIRST_MOVE, LAST_MOVE + 1)]
    labels = [label for _, label in rows]
    if len(set(labels)) != len(labels):
        raise ValueError("normalized PW2Code move labels are not unique")

    outputs: dict[Path, str] = {}
    zero_records = 0
    for move_id, label in rows:
        data = (records_dir / str(move_id)).read_bytes()
        if not any(data):
            zero_records += 1
        record = parse_record(move_id, data)
        outputs[repo / f"data/pml/moves/{move_id}.toml"] = render_record(label, record)

    outputs[repo / "data/enums/moves.yml"] = replace_move_enum_tail(
        (repo / "data/enums/moves.yml").read_text(encoding="utf-8"), "yml", rows
    )
    outputs[repo / "tools/mkdata/enum/moves.toml"] = replace_move_enum_tail(
        (repo / "tools/mkdata/enum/moves.toml").read_text(encoding="utf-8"), "toml", rows
    )
    outputs[repo / "include/Moves.h"] = replace_move_enum_tail(
        (repo / "include/Moves.h").read_text(encoding="utf-8"), "header", rows
    )

    outputs[repo / "data/pml/moves/meson.build"] = (
        "moves = [\n"
        + "".join(f"  '{move_id}.toml',\n" for move_id in range(MOVE_END_MSG))
        + "]\n\n"
        + (repo / "data/pml/moves/meson.build").read_text(encoding="utf-8").split(
            "]\n\n", 1
        )[1]
    )

    helper_names = (repo / "tools/helpers/txtdmp/Moves.txt").read_text(
        encoding="utf-8"
    ).splitlines()
    if len(helper_names) < FIRST_MOVE:
        raise ValueError("Moves.txt is shorter than the existing move range")
    helper_names = helper_names[:FIRST_MOVE]
    helper_names.extend(names[move_id] for move_id in range(FIRST_MOVE, LAST_MOVE + 1))
    helper_names.append("END_MSG")
    outputs[repo / "tools/helpers/txtdmp/Moves.txt"] = "\n".join(helper_names) + "\n"

    system_text = repo / "data/text/system"
    descriptions = [
        normalize_entry({"text": [f"{names[move_id]} description.$"]}, move_id)
        for move_id in range(FIRST_MOVE, LAST_MOVE + 1)
    ]
    outputs[system_text / "402.toml"] = replace_message_tail(
        system_text / "402.toml", FIRST_MOVE, descriptions
    )
    outputs[system_text / "403.toml"] = replace_message_tail(
        system_text / "403.toml",
        FIRST_MOVE,
        source_names_doc["entries"][FIRST_MOVE:LAST_MOVE + 1],
    )
    outputs[system_text / "488.toml"] = replace_message_tail(
        system_text / "488.toml", 560, source_caps_doc["entries"][560:LAST_MOVE + 1]
    )
    outputs[system_text / "16.toml"] = replace_message_tail(
        system_text / "16.toml",
        FIRST_MOVE * 3,
        source_battle_doc["entries"][FIRST_MOVE * 3:(LAST_MOVE + 1) * 3],
    )
    return outputs, zero_records


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pw2code", type=Path, required=True)
    parser.add_argument("--repo-root", type=Path, default=REPO_ROOT)
    parser.add_argument(
        "--check", action="store_true",
        help="Validate that checked-in outputs match the importer without writing.",
    )
    args = parser.parse_args()

    repo = args.repo_root.resolve()
    pw2code = args.pw2code.resolve()
    outputs, zero_records = collect_outputs(repo, pw2code)

    mismatches: list[Path] = []
    for path, content in outputs.items():
        if path.is_file() and path.read_text(encoding="utf-8") == content:
            continue
        mismatches.append(path)
        if not args.check:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content, encoding="utf-8")

    action = "checked" if args.check else "generated"
    print(
        f"{action} {MOVE_COUNT} moves ({FIRST_MOVE}-{LAST_MOVE}); "
        f"zero_records={zero_records}; changed_outputs={len(mismatches)}"
    )
    if args.check and mismatches:
        for path in mismatches:
            print(f"out of date: {path.relative_to(repo)}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
