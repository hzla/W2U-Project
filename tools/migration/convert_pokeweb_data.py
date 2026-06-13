#!/usr/bin/env python3

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
from pathlib import Path

import yaml


REPO_ROOT = Path(__file__).resolve().parents[2]


def toml_key(key: str) -> str:
    if re.fullmatch(r"[A-Za-z0-9_-]+", key):
        return key
    return '"' + key.replace("\\", "\\\\").replace('"', '\\"') + '"'


def toml_value(value) -> str:
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, int):
        return str(value)
    if isinstance(value, list):
        return "[" + ", ".join(toml_value(item) for item in value) + "]"
    if value is None:
        return '""'
    text = str(value)
    return '"' + text.replace("\\", "\\\\").replace('"', '\\"') + '"'


def load_yaml(path: Path):
    with path.open("r", encoding="utf-8") as handle:
        return yaml.safe_load(handle)


def flatten_sequence(sequence: list) -> dict:
    out = {}
    for item in sequence:
        if not isinstance(item, dict):
            raise TypeError(f"Expected mapping in sequence, got {type(item).__name__}")
        out.update(item)
    return out


def write_pml_toml(doc: dict, output: Path) -> str:
    if len(doc) != 1:
        raise ValueError(f"{output}: expected one top-level table")
    root, body = next(iter(doc.items()))
    output.parent.mkdir(parents=True, exist_ok=True)

    scalars: list[tuple[str, object]] = []
    subtables: list[tuple[str, dict]] = []
    for item in body:
        if len(item) != 1:
            raise ValueError(f"{output}: expected one key per sequence item")
        key, value = next(iter(item.items()))
        if isinstance(value, list) and all(isinstance(entry, dict) for entry in value):
            subtables.append((key, flatten_sequence(value)))
        else:
            scalars.append((key, value))

    lines = [f"[{toml_key(root)}]"]
    for key, value in scalars:
        lines.append(f"{toml_key(key)} = {toml_value(value)}")
    for key, fields in subtables:
        lines.append("")
        lines.append(f"[{toml_key(root)}.{toml_key(key)}]")
        for field_key, field_value in fields.items():
            lines.append(f"{toml_key(field_key)} = {toml_value(field_value)}")
    output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return root


def normalize_legacy_evolution_params(doc: dict) -> dict:
    body = next(iter(doc.values()))
    for item in body:
        key, value = next(iter(item.items()))
        if not key.startswith("EVOLUTION_") or not isinstance(value, list):
            continue
        for field in value:
            if "Parameter" not in field:
                continue
            parameter = field["Parameter"]
            if (
                isinstance(parameter, str)
                and not parameter.strip().isdigit()
                and (parameter.startswith("ITEM_") or parameter.startswith("MOVE_"))
            ):
                # The old Pokeweb mkdata evolution serializer did not include
                # item/move enums, so these labels serialized as zero.
                field["Parameter"] = 0
    return doc


def write_table(lines: list[str], path: list[str], table: dict, header: str = "[{}]") -> None:
    scalars = []
    nested = []
    arrays = []
    for key, value in table.items():
        if isinstance(value, dict):
            nested.append((key, value))
        elif isinstance(value, list) and value and all(isinstance(item, dict) for item in value):
            arrays.append((key, value))
        else:
            scalars.append((key, value))

    if path:
        lines.append(header.format(".".join(toml_key(part) for part in path)))
    for key, value in scalars:
        lines.append(f"{toml_key(key)} = {toml_value(value)}")
    if path and (nested or arrays):
        lines.append("")

    for index, (key, value) in enumerate(nested):
        write_table(lines, [*path, key], value)
        if index != len(nested) - 1 or arrays:
            lines.append("")

    for array_index, (key, values) in enumerate(arrays):
        for item_index, item in enumerate(values):
            write_table(lines, [*path, key], item, header="[[{}]]")
            if item_index != len(values) - 1:
                lines.append("")
        if array_index != len(arrays) - 1:
            lines.append("")


def write_generic_toml(doc: dict, output: Path) -> None:
    output.parent.mkdir(parents=True, exist_ok=True)
    lines: list[str] = []
    write_table(lines, [], doc)
    output.write_text("\n".join(lines).rstrip() + "\n", encoding="utf-8")


def slug_from_symbol(symbol: str, prefix: str) -> str:
    raw = symbol.removeprefix(prefix).lower()
    return raw


def convert_indexed_pml(source_dir: Path, dest_root: Path, filename: str) -> list[str]:
    entries: list[str] = []
    for source in sorted(source_dir.glob("*.yml"), key=lambda path: int(path.stem)):
        index = int(source.stem)
        doc = load_yaml(source)
        if filename == "evolutions.toml":
            doc = normalize_legacy_evolution_params(doc)
        root = next(iter(doc.keys()))
        slug = slug_from_symbol(root, "SPECIES_")
        output = dest_root / slug / filename
        written_root = write_pml_toml(doc, output)
        if written_root != root:
            raise AssertionError(f"{source}: wrote {written_root}, expected {root}")
        entries.append(f"{slug}/{filename}")
        if index != len(entries) - 1:
            raise ValueError(f"{source}: non-contiguous PML index")
    return entries


def clean_pml_file(dest_root: Path, filename: str) -> None:
    for old in dest_root.glob(f"*/{filename}"):
        old.unlink()


def convert_numbered_pml(source_dir: Path, dest_dir: Path) -> list[str]:
    for old in dest_dir.glob("*.toml"):
        old.unlink()
    entries: list[str] = []
    for source in sorted(source_dir.glob("*.yml"), key=lambda path: int(path.stem)):
        index = int(source.stem)
        output = dest_dir / f"{index}.toml"
        write_pml_toml(load_yaml(source), output)
        entries.append(output.name)
    return entries


def convert_items(source_dir: Path, dest_dir: Path) -> tuple[list[str], list[tuple[str, int]]]:
    for old in dest_dir.glob("*.toml"):
        old.unlink()
    entries: list[str] = []
    defines: list[tuple[str, int]] = []
    seen_slugs: set[str] = set()
    seen_defines: set[str] = set()
    for source in sorted(source_dir.glob("*.yml"), key=lambda path: int(path.stem)):
        index = int(source.stem)
        root = next(iter(load_yaml(source).keys()))
        slug = slug_from_symbol(root, "ITEM_")
        define = root
        if slug in seen_slugs:
            slug = f"{slug}_{index}"
        if define in seen_defines:
            define = f"{define}_{index}"
        seen_slugs.add(slug)
        seen_defines.add(define)
        output = dest_dir / f"{slug}.toml"
        write_pml_toml(load_yaml(source), output)
        entries.append(output.name)
        defines.append((define, index))
    return entries, defines


def convert_numbered_generic(source_dir: Path, dest_dir: Path, prefix: str) -> list[str]:
    for old in dest_dir.glob("*.toml"):
        old.unlink()
    entries: list[str] = []
    for source in sorted(source_dir.glob(f"{prefix}_*.yml")):
        index = int(source.stem.rsplit("_", 1)[1])
        output = dest_dir / f"{index}.toml"
        write_generic_toml(load_yaml(source), output)
        entries.append(output.name)
    return entries


def dump_text_bins(source_dir: Path, dest_dir: Path, gen5_text: Path) -> list[str]:
    for old in dest_dir.glob("*.toml"):
        old.unlink()
    entries: list[str] = []
    for source in sorted(source_dir.glob("002_*.bin")):
        index = int(source.stem.rsplit("_", 1)[1])
        output = dest_dir / f"{index}.toml"
        subprocess.run(["python3", str(gen5_text), "dump-file", str(source), str(output)], check=True)
        entries.append(output.name)
    return entries


def write_list_meson(path: Path, variable: str, entries: list[str], body: str) -> None:
    lines = [f"{variable} = ["]
    lines.extend(f"  '{entry}'," for entry in entries)
    lines.append("]")
    lines.append("")
    lines.append(body.strip())
    lines.append("")
    path.write_text("\n".join(lines), encoding="utf-8")


def write_pml_meson(path: Path, personal: list[str], learnsets: list[str], evolutions: list[str]) -> None:
    def block(name: str, entries: list[str]) -> list[str]:
        out = [f"{name} = ["]
        out.extend(f"  '{entry}'," for entry in entries)
        out.append("]")
        out.append("")
        return out

    body = []
    body.append("subdir('moves')")
    body.append("")
    body.extend(block("personal_sources", personal))
    body.extend(block("learnset_sources", learnsets))
    body.extend(block("evolution_sources", evolutions))
    body.append("""personal_arc = 'a' / '0' / '1' / '6'
personal_files = []
personal_index = 0
foreach personal_file : personal_sources
  personal_output = personal_index.to_string()
  personal_files += custom_target(
    'personal_' + personal_output,
    input: meson.current_source_dir() / personal_file,
    output: 'personal_' + personal_output,
    command: [mkdata_py, 'generic', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'format', 'personal'],
  )
  personal_index += 1
endforeach

vfs_files += custom_target(
  'pack_personal_narc',
  input: [personal_files, meson.current_source_dir() / 'RegionalDex.bin'],
  output: 'pack_personal_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / personal_arc, '@INPUT@'],
)

learnsets_arc = 'a' / '0' / '1' / '8'
learnset_files = []
learnset_index = 0
foreach learnset : learnset_sources
  learnset_output = learnset_index.to_string()
  learnset_files += custom_target(
    'learnset_' + learnset_output,
    input: meson.current_source_dir() / learnset,
    output: 'learnset_' + learnset_output,
    command: [mkdata_py, 'generic', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'format', 'learnsets'],
  )
  learnset_index += 1
endforeach

vfs_files += custom_target(
  'pack_learnsets_narc',
  input: learnset_files,
  output: 'pack_learnsets_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / learnsets_arc, '@INPUT@'],
)

evolutions_arc = 'a' / '0' / '1' / '9'
evolution_files = []
evolution_index = 0
foreach evolution : evolution_sources
  evolution_output = evolution_index.to_string()
  evolution_files += custom_target(
    'evolution_' + evolution_output,
    input: meson.current_source_dir() / evolution,
    output: 'evolution_' + evolution_output,
    command: [mkdata_py, 'generic', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'format', 'evolutions'],
  )
  evolution_index += 1
endforeach

vfs_files += custom_target(
  'pack_evolutions_narc',
  input: evolution_files,
  output: 'pack_evolutions_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / evolutions_arc, '@INPUT@'],
)
""")
    path.write_text("\n".join(body), encoding="utf-8")


def write_defines_toml(path: Path, defines: list[tuple[str, int]]) -> None:
    lines = ["[DEFINE]"]
    lines.extend(f'{toml_value(name)} = {value}' for name, value in defines)
    lines.append("")
    path.write_text("\n".join(lines), encoding="utf-8")


def write_defines_yml(path: Path, defines: list[tuple[str, int]]) -> None:
    lines = ["DEFINE:"]
    lines.extend(f"  - {name}: {value}" for name, value in defines)
    lines.append("")
    path.write_text("\n".join(lines), encoding="utf-8")


def add_define_aliases(defines: list[tuple[str, int]], aliases: dict[str, str]) -> list[tuple[str, int]]:
    by_name = dict(defines)
    out = list(defines)
    for alias, canonical in aliases.items():
        if alias in by_name:
            continue
        if canonical not in by_name:
            raise KeyError(f"Alias target {canonical} for {alias} is not defined")
        out.append((alias, by_name[canonical]))
    return out


def defines_from_header(path: Path, prefix: str, skip: set[str] | None = None) -> list[tuple[str, int]]:
    skip = skip or set()
    defines = []
    pattern = re.compile(rf"^#define\s+({re.escape(prefix)}[A-Z0-9_]+)\s+([0-9]+)\b")
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        match = pattern.match(line)
        if not match:
            continue
        name, value = match.groups()
        if name in skip:
            continue
        defines.append((name, int(value)))
    return defines


def copy_binary(source: Path, dest: Path) -> None:
    dest.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, dest)


def main() -> int:
    parser = argparse.ArgumentParser(description="Convert local Pokeweb YAML/bin data into upstream TOML/VFS sources.")
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--dest", type=Path, default=REPO_ROOT)
    args = parser.parse_args()

    source = args.source.resolve()
    dest = args.dest.resolve()

    clean_pml_file(dest / "data" / "pml", "personal.toml")
    clean_pml_file(dest / "data" / "pml", "learnset.toml")
    clean_pml_file(dest / "data" / "pml", "evolutions.toml")
    personal = convert_indexed_pml(source / "data" / "pml" / "personal", dest / "data" / "pml", "personal.toml")
    learnsets = convert_indexed_pml(source / "data" / "pml" / "learnsets", dest / "data" / "pml", "learnset.toml")
    evolutions = convert_indexed_pml(source / "data" / "pml" / "evolutions", dest / "data" / "pml", "evolutions.toml")
    write_pml_meson(dest / "data" / "pml" / "meson.build", personal, learnsets, evolutions)

    moves = convert_numbered_pml(source / "data" / "pml" / "moves", dest / "data" / "pml" / "moves")
    write_list_meson(dest / "data" / "pml" / "moves" / "meson.build", "moves", moves, """# Moves (/a/0/2/1)
moves_arc = 'a' / '0' / '2' / '1'
move_files = []
foreach move : moves
  move_name = fs.replace_suffix(move, '')
  move_files += custom_target(
    'move_' + move_name,
    input: meson.current_source_dir() / move,
    output: move_name,
    command: [mkdata_py, 'generic', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'format', 'moves'],
  )
endforeach

vfs_files += custom_target(
  'pack_moves_narc',
  input: move_files,
  output: 'pack_moves_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / moves_arc, '@INPUT@'],
)""")

    items, item_defines = convert_items(source / "data" / "items", dest / "data" / "items")
    write_list_meson(dest / "data" / "items" / "meson.build", "items", items, """# Items (/a/0/2/4)
items_arc = 'a' / '0' / '2' / '4'
item_files = []
foreach item_index : range(items.length())
  item_files += custom_target(
    'item_' + item_index.to_string(),
    input: meson.current_source_dir() / items[item_index],
    output: 'item_' + item_index.to_string(),
    command: [mkdata_py, 'generic', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'format', 'items'],
  )
endforeach

vfs_files += custom_target(
  'pack_items_narc',
  input: item_files,
  output: 'pack_items_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / items_arc, '@INPUT@'],
)""")

    encounters = convert_numbered_generic(source / "data" / "encounters", dest / "data" / "encounters", "a127")
    write_list_meson(dest / "data" / "encounters" / "meson.build", "encounters", encounters, """# Encounters (/a/1/2/7)
encounters_arc = 'a' / '1' / '2' / '7'
encounter_files = []
foreach encounter : encounters
  encounter_name = fs.replace_suffix(encounter, '')
  encounter_files += custom_target(
    'encounter_' + encounter_name,
    input: meson.current_source_dir() / encounter,
    output: encounter_name,
    command: [mkdata_py, 'encounter', '@INPUT@', meson.project_build_root() / '@OUTPUT@'],
  )
endforeach

vfs_files += custom_target(
  'pack_encounters_narc',
  input: encounter_files,
  output: 'pack_encounters_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / encounters_arc, '@INPUT@'],
)""")

    trainers = convert_numbered_generic(source / "data" / "trainers", dest / "data" / "trainers", "a091")
    write_list_meson(dest / "data" / "trainers" / "meson.build", "trainers", trainers, """# trdata & trpoke
trdata_arc = 'a' / '0' / '9' / '1'
trpoke_arc = 'a' / '0' / '9' / '2'

trdata_files = []
trpoke_files = []
foreach trainer : trainers
  tr_name = fs.replace_suffix(trainer, '')
  trdata_files += custom_target(
    'trdata_' + tr_name,
    input: meson.current_source_dir() / trainer,
    output: 'trdata_' + tr_name,
    command: [mkdata_py, 'trainer', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'output_type', 'trdata'],
  )

  trpoke_files += custom_target(
    'trpoke_' + tr_name,
    input: meson.current_source_dir() / trainer,
    output: 'trpoke_' + tr_name,
    command: [mkdata_py, 'trainer', '@INPUT@', meson.project_build_root() / '@OUTPUT@', 'output_type', 'trpoke'],
  )
endforeach

vfs_files += custom_target(
  'pack_trdata_narc',
  input: trdata_files,
  output: 'pack_trdata_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / trdata_arc, '@INPUT@'],
)

vfs_files += custom_target(
  'pack_trpoke_narc',
  input: trpoke_files,
  output: 'pack_trpoke_narc.stamp',
  command: [pack_narc_py, '@OUTPUT@', meson.project_source_root() / 'vfs' / 'data' / trpoke_arc, '@INPUT@'],
)""")

    dump_text_bins(source / "data" / "text" / "system", dest / "data" / "text" / "system", dest / "tools" / "text" / "gen5_text.py")

    copy_binary(source / "data" / "pml" / "RegionalDex.bin", dest / "data" / "pml" / "RegionalDex.bin")
    copy_binary(source / "data" / "poke_form_list.bin", dest / "data" / "pml" / "poke_form_list.bin")
    copy_binary(source / "data" / "pokeicon_palette_map.bin", dest / "data" / "pml" / "pokeicon_palette_map.bin")
    copy_binary(source / "data" / "type_chart.bin", dest / "data" / "pml" / "types" / "type_chart.bin")
    copy_binary(source / "data" / "type_palette_map.bin", dest / "data" / "pml" / "types" / "type_palette_map.bin")

    species_defines = defines_from_header(dest / "include" / "species.h", "SPECIES_", {"SPECIES_CNT", "SPECIES_AND_EGG_CNT"})
    move_defines = defines_from_header(dest / "include" / "Moves.h", "MOVE_")
    write_defines_toml(dest / "tools" / "mkdata" / "enum" / "species.toml", species_defines)
    write_defines_yml(dest / "data" / "enums" / "species.yml", species_defines)
    write_defines_toml(dest / "tools" / "mkdata" / "enum" / "moves.toml", move_defines)
    write_defines_yml(dest / "data" / "enums" / "moves.yml", move_defines)
    item_defines = add_define_aliases(item_defines, {
        "ITEM_POKE_BALL": "ITEM_POKé_BALL",
        "ITEM_POKE_DOLL": "ITEM_POKé_DOLL",
        "ITEM_POKE_RADAR": "ITEM_POKé_RADAR",
        "ITEM_POKE_TOY": "ITEM_POKé_TOY",
        "ITEM_X_DEFENSE": "ITEM_X_DEFEND",
        "ITEM_X_SP_ATK": "ITEM_X_SPECIAL",
    })
    write_defines_toml(dest / "tools" / "mkdata" / "enum" / "items.toml", item_defines)
    write_defines_yml(dest / "data" / "enums" / "items.yml", item_defines)

    print(f"personal={len(personal)} learnsets={len(learnsets)} evolutions={len(evolutions)}")
    print(f"moves={len(moves)} items={len(items)} encounters={len(encounters)} trainers={len(trainers)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
