#!/usr/bin/env python3
"""Export W2U's species data to the pokebw2 decomp's format: one JSON file per species and form.

usage: python tools/decomp/export_species_json.py --decomp=PATH [--out=DIR] [--check]

The decomp (github.com/fuddlesworth/pokebw2) keeps the species data in data/pokemon/<species>/data.json, a
form_<n>.json per form record and data/pokemon/forms.json, written with the constants of data/constants/*.txt and
include/constants/pokemon.h; its tools/data/species_data.py packs them into the archives (species.schema.json
describes the fields). This writes W2U's data/pml (personal.toml, learnset.toml, evolutions.toml, RegionalDex.bin, in
the record order of data/pml/meson.build) in that format, so a decomp-based W2U can take its data from ours. Only
the decomp's text files are read (constants and the tutor tables of src/ov036/scrcmd_shop.c); none of its code runs.

Names: a value is written with the decomp's constant where it means the same in W2U, else with W2U's name:
  - species 1-649, moves 1-559, abilities 1-164, items, growth rates, egg groups, colours: the decomp's;
  - species 650-1023: SPECIES_ + the English name (text bank 90), so Rowlet is SPECIES_ROWLET; the decomp numbers
    its egg, bad egg and Pokestar Studios species from 650, so W2U's numbering replaces those;
  - moves 560+: W2U's enum (tools/mkdata/enum/moves.toml); abilities 165+: ABILITY_ + the name (text bank 374);
  - type 17: TYPE_FAIRY (the decomp's TYPE_NULL); evolution methods 28-31: EVO_METHOD_ + W2U's names.
Every name it adds is in OUT/constants_added.json with its value.

Differences from the decomp's format, reported in OUT/report.md: heights are in centimetres in W2U (written here in
decimetres, as the decomp's), W2U has 8 evolution slots (the decomp 7), W2U has no egg record (its records 1024 and
1025, folders egg/ and bad_egg/, are Deoxys's Attack and Defense forms), and some form records have no species.
W2U keeps no baby species or egg moves of its own (the retail archives): species 1-649 take the decomp's, the rest
their own species and none.

--check converts every written record back to W2U's values and compares them with the TOML (the round trip), and
compares species 1-649 with the decomp's data.json (the retail data) field by field.
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
import tomllib
import unicodedata
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PML = ROOT / "data" / "pml"
ENUM = ROOT / "tools" / "mkdata" / "enum"
TEXT = ROOT / "data" / "text" / "system"
STATS = ["hp", "attack", "defense", "speed", "special_attack", "special_defense"]
TOML_STATS = ["Base HP", "Base Attack", "Base Defense", "Base Speed", "Base Special Attack", "Base Special Defense"]
NATIONAL = 1024                     # species 0-1023; records from 1024 are forms
RETAIL_SPECIES, RETAIL_MOVES, RETAIL_ABILITIES = 649, 559, 164
TYPE_TUTOR_MOVES = ["MOVE_GRASS_PLEDGE", "MOVE_FIRE_PLEDGE", "MOVE_WATER_PLEDGE", "MOVE_FRENZY_PLANT",
                    "MOVE_BLAST_BURN", "MOVE_HYDRO_CANNON", "MOVE_DRACO_METEOR"]
# The evolution methods whose parameter is a constant (the decomp's species_data.py PARAM_PREFIXES)
PARAM_PREFIXES = {6: "ITEM_", 8: "ITEM_", 17: "ITEM_", 18: "ITEM_", 19: "ITEM_", 20: "ITEM_", 21: "MOVE_",
                  7: "SPECIES_", 22: "SPECIES_"}
GENDER_NAMES = {0: "GENDER_RATIO_MALE_ONLY", 254: "GENDER_RATIO_FEMALE_ONLY", 255: "GENDER_RATIO_GENDERLESS"}


# Constants


def parse_list(path: Path) -> dict[str, int]:
    """A decomp constant list: NAME = value, or NAME for the previous value + 1."""
    values, next_value = {}, 0
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        name, _, value = (part.strip() for part in line.partition("="))
        next_value = int(value, 0) if value else next_value
        values[name] = next_value
        next_value += 1
    return values


def decomp_constants(decomp: Path) -> dict[str, dict[int, str]]:
    """By prefix, value -> the decomp's first name for it."""
    values = {}
    for path in sorted((decomp / "data" / "constants").glob("*.txt")):
        values.update(parse_list(path))
    header = (decomp / "include" / "constants" / "pokemon.h").read_text(encoding="utf-8")
    values.update({m[1]: int(m[2], 0) for m in re.finditer(r"#define (\w+) (0x[0-9a-fA-F]+|\d+)\b", header)})
    by_prefix: dict[str, dict[int, str]] = {}
    for name, value in values.items():
        prefix = name.split("_", 1)[0] + "_"
        if name.startswith(("EVO_METHOD_", "EGG_GROUP_", "GENDER_RATIO_")):
            prefix = "_".join(name.split("_", 2)[:2]) + "_"
        by_prefix.setdefault(prefix, {}).setdefault(value, name)
    return by_prefix


def w2u_enum(name: str) -> dict[str, int]:
    return tomllib.loads((ENUM / f"{name}.toml").read_text(encoding="utf-8"))["DEFINE"]


def text_lines(bank: int) -> dict[int, str]:
    entries = tomllib.loads((TEXT / f"{bank}.toml").read_text(encoding="utf-8"))["msg"]["section_0"]["entries"]
    return {int(k): "".join(v["text"]).rstrip("$") for k, v in entries.items()}


def constant_name(prefix: str, text: str) -> str:
    """SPECIES_ + "Type: Null" -> SPECIES_TYPE_NULL; accents dropped, ♀/♂ as F/M."""
    text = text.replace("♀", "_F").replace("♂", "_M")
    text = unicodedata.normalize("NFKD", text).encode("ascii", "ignore").decode()
    return prefix + re.sub(r"[^A-Z0-9]+", "_", text.upper()).strip("_")


class Names:
    """W2U values -> constant names for the JSON, and back."""

    def __init__(self, decomp: Path):
        d = decomp_constants(decomp)
        self.added: dict[str, int] = {}
        self.renamed: list[str] = []
        species_text, ability_text = text_lines(90), text_lines(374)
        w2u_moves = {v: k for k, v in w2u_enum("moves").items()}
        self.species = {v: n for v, n in d["SPECIES_"].items() if v <= RETAIL_SPECIES}
        for value in range(RETAIL_SPECIES + 1, NATIONAL):
            self.species[value] = self.add(constant_name("SPECIES_", species_text[value]), value)
        self.moves = {v: n for v, n in d["MOVE_"].items() if v <= RETAIL_MOVES}
        for value, name in w2u_moves.items():
            if value > RETAIL_MOVES:
                self.moves[value] = self.add(constant_name("MOVE_", name.removeprefix("MOVE_")), value)
        self.abilities = {v: n for v, n in d["ABILITY_"].items() if v <= RETAIL_ABILITIES}
        for value, text in ability_text.items():
            if value > RETAIL_ABILITIES and text.strip():
                self.abilities[value] = self.add(constant_name("ABILITY_", text), value)
        self.items = d["ITEM_"]
        self.types = {v: n for v, n in d["TYPE_"].items() if v < 17}
        self.types[17] = self.add("TYPE_FAIRY", 17)
        self.methods = dict(d["EVO_METHOD_"])
        for name, value in w2u_enum("evolution_methods").items():
            if value not in self.methods:
                self.methods[value] = self.add("EVO_METHOD_" + name.removeprefix("METHOD_"), value)
        self.growth, self.eggs, self.colors = d["GROWTH_"], d["EGG_GROUP_"], d["COLOR_"]
        # W2U's own names, for its TOML
        self.w2u_species, self.w2u_moves = w2u_enum("species"), w2u_enum("moves")
        self.w2u_methods = w2u_enum("evolution_methods")

    def add(self, name: str, value: int) -> str:
        """A new constant; a name already taken by another value (two abilities named As One) gets _2, _3, ..."""
        base, n = name, 1
        while self.added.get(name, value) != value:
            n += 1
            name = f"{base}_{n}"
        if n > 1:
            self.renamed.append(f"{name} = {value} ({base} is {self.added[base]})")
        self.added[name] = value
        return name

    @staticmethod
    def get(table: dict[int, str], value: int, what: str) -> str:
        if value not in table:
            raise KeyError(f"no {what} constant for {value}")
        return table[value]


# W2U's data


def record_folders() -> list[str]:
    text = (PML / "meson.build").read_text(encoding="utf-8")
    folders = re.findall(r"'([^']+)/personal\.toml'", text)
    for kind in ("learnset", "evolutions"):
        if re.findall(rf"'([^']+)/{kind}\.toml'", text) != folders:
            raise SystemExit(f"data/pml/meson.build: the {kind} files are not in the personal files' order")
    return folders


def load_toml(folder: str, kind: str) -> dict:
    data = tomllib.loads((PML / folder / f"{kind}.toml").read_text(encoding="utf-8"))
    return next(iter(data.values())) if data else {}


def entries(table: dict, key: str) -> list[dict]:
    found = [(int(k.rsplit("_", 1)[1]), v) for k, v in table.items() if k.startswith(key) and isinstance(v, dict)]
    return [v for _, v in sorted(found)]


def tutor_tables(decomp: Path) -> list[list[str]]:
    """The moves of the five tutor words by bit (the decomp's species_data.py tutor_moves)."""
    source = (decomp / "src" / "ov036" / "scrcmd_shop.c").read_text(encoding="utf-8")
    tables = {m[1]: re.findall(r"\{ \{ (MOVE_\w+), \d+ \}, \d+ \}", m[2]) for m in
              re.finditer(r"static const MoveTutorShopItem (MOVE_TUTOR_ITEMS_\w+)\[\] = \{(.*?)\n\};", source, re.S)}
    order = re.search(r"MOVE_TUTOR_SHOP_ITEMS\[\] = \{(.*?)\};", source, re.S)[1]
    return [TYPE_TUTOR_MOVES] + [tables[n.strip()] for n in order.split(",") if n.strip()]


def machine_name(bit: int) -> str:
    return f"TM{bit + 1:02d}" if bit < 95 else f"HM{bit - 94:02d}"


def record_json(p: dict, learnset: dict, evolutions: dict, names: Names, tutors: list[list[str]]) -> dict:
    evs = p["EV Yield"]
    if evs >> 13 or p["Color"] >> 8 or p["Height (cm)"] % 10:
        raise ValueError("unknown EV / colour bits, or a height not in whole decimetres")
    machine_bits = sum((p[f"TM HM {i + 1}"] & 0xFFFFFFFF) << (32 * i) for i in range(4))
    tutor_words = [p["Type Tutors"] & 0xFFFFFFFF] + [w & 0xFFFFFFFF for w in p["Special Tutors"]]
    by_tutor = []
    for moves, word in zip(tutors, tutor_words):
        for bit in range(32):
            if word >> bit & 1:
                if bit >= len(moves):
                    raise ValueError(f"tutor bit {bit} has no move")
                by_tutor.append(moves[bit])
    by_level = [[e["LEVEL"], names.get(names.moves, names.w2u_moves[e["MOVE"]], "move")]
                for e in entries(learnset, "LEARNSET_ENTRY_")]
    evolution_list = []
    for e in entries(evolutions, "EVOLUTION_"):
        method = names.w2u_methods[e["Method"]] if isinstance(e["Method"], str) else e["Method"]
        if not method:
            continue
        param = e["Parameter"]
        if isinstance(param, str):
            param = {**names.w2u_moves, **names.w2u_species}.get(param, param)
        prefix = PARAM_PREFIXES.get(method)
        if prefix and param:
            table = {"ITEM_": names.items, "MOVE_": names.moves, "SPECIES_": names.species}[prefix]
            param = names.get(table, param, prefix)
        target = names.w2u_species[e["Target Species"]] if isinstance(e["Target Species"], str) else e["Target Species"]
        evolution_list.append({"method": names.get(names.methods, method, "evolution method"), "param": param,
                               "species": names.get(names.species, target, "species")})
    return {
        "base_stats": {s: p[t] for s, t in zip(STATS, TOML_STATS)},
        "types": [names.get(names.types, names_type(p, k), "type") for k in ("Primary Type", "Secondary Type")],
        "catch_rate": p["Capture Rate"],
        "evolution_stage": p["Evolution Stage"],
        "ev_yields": {stat: evs >> (2 * i) & 3 for i, stat in enumerate(STATS)},
        "underground": bool(evs >> 12 & 1),
        # an item past W2U's item table (Gen 6 IDs: Luminous Moss 648, Snowball 649) stays a number
        "held_items": {k: names.items.get(p[t], p[t]) for k, t in
                       (("common", "Wild Item (50%)"), ("rare", "Wild Item (5%)"), ("very_rare", "Wild Item (1%)"))},
        "gender_ratio": GENDER_NAMES.get(p["Gender Probability"], p["Gender Probability"]),
        "hatch_cycles": p["Egg Happiness"],
        "base_friendship": p["Base Happiness"],
        "growth_rate": names.get(names.growth, p["Experience Group"], "growth rate"),
        "egg_groups": [names.get(names.eggs, p[k], "egg group") for k in ("Egg Group 1", "Egg Group 2")],
        "abilities": [names.get(names.abilities, p[k], "ability") if p[k] else "ABILITY_NONE"
                      for k in ("Primary Ability", "Secondary Ability")],
        "hidden_ability": names.get(names.abilities, p["Hidden Ability"], "ability") if p["Hidden Ability"]
        else "ABILITY_NONE",
        "flee_rate": p["Escape Rate"],
        "forms": {"count": p["Form Count"], "sprite_offset": p["Form Sprite Offset"]},
        "color": names.get(names.colors, p["Color"] & 0x3F, "colour"),
        "asymmetric": bool(p["Color"] >> 6 & 1),
        "palette_forms": bool(p["Color"] >> 7 & 1),
        "base_exp": p["Base Experience"],
        "height": p["Height (cm)"] // 10,
        "weight": p["Weight (cg)"],
        "learnset": {"by_level": by_level, "by_tm": [machine_name(b) for b in range(128) if machine_bits >> b & 1],
                     "by_tutor": by_tutor},
        "evolutions": evolution_list,
    }


TYPES = None


def names_type(p: dict, key: str) -> int:
    global TYPES
    TYPES = TYPES or w2u_enum("types")
    return TYPES[p[key]] if isinstance(p[key], str) else p[key]


# The round trip: JSON -> W2U's values


def back_to_w2u(data: dict, names: Names, tutors: list[list[str]], form_offset: int) -> dict:
    inv = lambda table: {n: v for v, n in table.items()}
    species, moves, items = inv(names.species), inv(names.moves), inv(names.items)
    abilities, types, methods = inv(names.abilities), inv(names.types), inv(names.methods)
    machine_bits = 0
    for m in data["learnset"]["by_tm"]:
        machine_bits |= 1 << (int(m[2:]) - 1 if m.startswith("TM") else int(m[2:]) + 94)
    words = [0] * len(tutors)
    for move in data["learnset"]["by_tutor"]:
        w, b = next((w, b) for w, ms in enumerate(tutors) for b, m in enumerate(ms) if m == move)
        words[w] |= 1 << b
    signed = lambda v: v - (1 << 32) if v >> 31 else v
    gender = data["gender_ratio"]
    out = {t: data["base_stats"][s] for s, t in zip(STATS, TOML_STATS)}
    out.update({
        "Primary Type": types[data["types"][0]], "Secondary Type": types[data["types"][1]],
        "Capture Rate": data["catch_rate"], "Evolution Stage": data["evolution_stage"],
        "EV Yield": sum(data["ev_yields"][s] << (2 * i) for i, s in enumerate(STATS)) | data["underground"] << 12,
        **{t: items.get(data["held_items"][k], data["held_items"][k]) for k, t in
           (("common", "Wild Item (50%)"), ("rare", "Wild Item (5%)"), ("very_rare", "Wild Item (1%)"))},
        "Gender Probability": {n: v for v, n in GENDER_NAMES.items()}.get(gender, gender),
        "Egg Happiness": data["hatch_cycles"], "Base Happiness": data["base_friendship"],
        "Experience Group": inv(names.growth)[data["growth_rate"]],
        "Egg Group 1": inv(names.eggs)[data["egg_groups"][0]], "Egg Group 2": inv(names.eggs)[data["egg_groups"][1]],
        "Primary Ability": abilities.get(data["abilities"][0], 0),
        "Secondary Ability": abilities.get(data["abilities"][1], 0),
        "Hidden Ability": abilities.get(data["hidden_ability"], 0), "Escape Rate": data["flee_rate"],
        "Form Data Offset": form_offset, "Form Sprite Offset": data["forms"]["sprite_offset"],
        "Form Count": data["forms"]["count"],
        "Color": inv(names.colors)[data["color"]] | data["asymmetric"] << 6 | data["palette_forms"] << 7,
        "Base Experience": data["base_exp"], "Height (cm)": data["height"] * 10, "Weight (cg)": data["weight"],
        **{f"TM HM {i + 1}": signed(machine_bits >> (32 * i) & 0xFFFFFFFF) for i in range(4)},
        "Type Tutors": signed(words[0]), "Special Tutors": [signed(w) for w in words[1:]],
        "learnset": [(moves[m], level) for level, m in data["learnset"]["by_level"]],
        "evolutions": [(methods[e["method"]], e["param"] if isinstance(e["param"], int) else
                        {**items, **moves, **species}[e["param"]], species[e["species"]]) for e in data["evolutions"]],
    })
    return out


def w2u_values(p: dict, learnset: dict, evolutions: dict, names: Names) -> dict:
    out = {k: v for k, v in p.items()}
    for k in ("Primary Type", "Secondary Type"):
        out[k] = names_type(p, k)
    out["learnset"] = [(names.w2u_moves[e["MOVE"]], e["LEVEL"]) for e in entries(learnset, "LEARNSET_ENTRY_")]
    evo = []
    for e in entries(evolutions, "EVOLUTION_"):
        method = names.w2u_methods[e["Method"]] if isinstance(e["Method"], str) else e["Method"]
        if method:
            param = e["Parameter"]
            param = {**names.w2u_moves, **names.w2u_species}.get(param, param) if isinstance(param, str) else param
            target = e["Target Species"]
            evo.append((method, param, names.w2u_species[target] if isinstance(target, str) else target))
    out["evolutions"] = evo
    return out


# Writing


def write(path: Path, data) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=4, ensure_ascii=False) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--decomp", type=Path, required=True, help="a pokebw2 checkout (only its text is read)")
    parser.add_argument("--out", type=Path, default=ROOT / "work" / "decomp_species")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    names, tutors = Names(args.decomp), tutor_tables(args.decomp)
    folders = record_folders()
    regional = struct.unpack("<1024H", (PML / "RegionalDex.bin").read_bytes())
    retail_dir = args.decomp / "data" / "pokemon"
    out = args.out / "data" / "pokemon"
    personal = [load_toml(f, "personal") for f in folders]
    learnsets = [load_toml(f, "learnset") for f in folders]
    evolutions = [load_toml(f, "evolutions") for f in folders]
    directory = lambda value: names.species[value].removeprefix("SPECIES_").lower() if value else "none"

    # The form records, by the species whose Form Data Offset points at them
    owner: dict[int, tuple[int, int]] = {}
    problems = []
    for value in range(NATIONAL):
        p = personal[value]
        if p["Form Data Offset"]:
            for form in range(1, p["Form Count"]):
                record = p["Form Data Offset"] + form - 1
                if record in owner:
                    problems.append(f"record {record}: form of {names.species[owner[record][0]]} and "
                                    f"{names.species[value]}")
                owner[record] = (value, form)
    orphans = [r for r in range(NATIONAL, len(folders)) if r not in owner]

    written, round_trip, retail_diffs, bad_items, eighth = 0, [], {}, [], []
    for record, folder in enumerate(folders):
        if record >= NATIONAL and record not in owner:
            continue
        data = {"$schema": "../species.schema.json"}
        if record < NATIONAL:
            data["name"] = text_lines(90)[record] if record else ""
        data.update(record_json(personal[record], learnsets[record], evolutions[record], names, tutors))
        if record < NATIONAL:
            data["regional_dex_number"] = None if regional[record] == 999 else regional[record]
            retail = retail_dir / directory(record) / "data.json"
            if record and record <= RETAIL_SPECIES and retail.exists():
                retail_data = json.loads(retail.read_text(encoding="utf-8"))
                data["baby_species"] = retail_data["baby_species"]
                if "egg_moves" in retail_data["learnset"]:
                    data["learnset"]["egg_moves"] = retail_data["learnset"]["egg_moves"]
            else:
                data["baby_species"] = names.species[record] if record else "SPECIES_NONE"
            path = out / directory(record) / "data.json"
        else:
            value, form = owner[record]
            path = out / directory(value) / f"form_{form}.json"
        if record == 0:
            data.pop("name")
        if len(data["evolutions"]) > 7:
            eighth.append((record, len(data["evolutions"])))
        bad_items += [f"record {record} ({folder}): {k} = {v}" for k, v in data["held_items"].items()
                      if isinstance(v, int)]
        write(path, data)
        written += 1
        if args.check:
            mine = w2u_values(personal[record], learnsets[record], evolutions[record], names)
            back = back_to_w2u(data, names, tutors, personal[record]["Form Data Offset"])
            diff = sorted(k for k in back if back[k] != mine.get(k))
            if diff:
                round_trip.append(f"record {record} ({folder}): {', '.join(diff)}")
            if 0 < record <= RETAIL_SPECIES:
                retail = retail_dir / directory(record) / "data.json"
                if retail.exists():
                    r = json.loads(retail.read_text(encoding="utf-8"))
                    for key in data:
                        if key in ("$schema", "name", "pokedex", "regional_dex_number", "cry_volume"):
                            continue
                        a, b = data[key], r.get(key)
                        if key == "learnset":
                            for part in ("by_level", "by_tm", "by_tutor"):
                                if a[part] != b[part]:
                                    retail_diffs.setdefault(f"learnset.{part}", []).append(record)
                        elif a != b:
                            retail_diffs.setdefault(key, []).append(record)
    write(out / "forms.json", [[names.species[owner[r][0]], owner[r][1]] for r in sorted(owner)])
    write(args.out / "constants_added.json", dict(sorted(names.added.items(), key=lambda kv: (kv[0].split("_")[0],
                                                                                              kv[1]))))
    lines = [f"# W2U species data in the decomp's format", "",
             f"{written} files: {NATIONAL} species (data.json) and {len(owner)} form records (form_<n>.json), "
             f"forms.json; {len(names.added)} constants W2U adds (constants_added.json).", "",
             "## What the decomp's packer can't take as it is", "",
             f"- Records with no species pointing at them (not written): {orphans}.",
             "- W2U's SPECIES_EGG / SPECIES_BAD_EGG (1024 / 1025) have no records: records 1024 and 1025 (folders egg/, "
             "bad_egg/) are Deoxys's forms 1 and 2. The decomp packs the egg as a species record after the national "
             "Pokédex, so a W2U layout needs the egg (and the Pokéstar Studios species, which W2U has none of) "
             "placed again.",
             "- 8 evolution slots (the decomp packs 7): "
             + (", ".join(f"{names.species[r]} has {n}" for r, n in eighth) or "none uses the eighth")
             + "; heights: W2U stores centimetres (written here as decimetres).",
             "- Numbering: species 650+ (decomp: egg, bad egg, Pokéstar), type 17 (decomp: TYPE_NULL) mean other "
             "things in W2U.", ""]
    lines += [f"- {p}" for p in problems]
    if bad_items:
        lines += ["- Held items past the item table (written as numbers): " + "; ".join(bad_items)]
    lines += [""]
    if names.renamed:
        lines += ["Names taken twice (numbered): " + "; ".join(names.renamed), ""]
    if args.check:
        lines += ["## Round trip (JSON -> W2U values)", "",
                  "Every record converts back to its TOML values." if not round_trip else "Differences:"]
        lines += [f"- {r}" for r in round_trip[:50]]
        lines += ["", "## Species 1-649 against the decomp's (retail) data", "",
                  "Fields where W2U differs from retail, and how many species:"]
        lines += [f"- {k}: {len(v)} (e.g. {', '.join(names.species[s] for s in v[:6])})"
                  for k, v in sorted(retail_diffs.items(), key=lambda kv: -len(kv[1]))]
    (args.out / "report.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("\n".join(lines))
    if round_trip:
        sys.exit(1)


if __name__ == "__main__":
    main()
