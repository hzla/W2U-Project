#!/usr/bin/env python3
"""Import Essentials Gen 8/9 GIFs and selected non-Gmax form sprites.

The base species range is 810-1023. Regional and ordinary alternate forms are
allowlisted because Essentials numeric suffixes also include Gmax, Mega, gender,
and presentation-only forms.
"""

from __future__ import annotations

import importlib.util
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
PORT = Path(os.environ.get("POKEWEB_SOURCE_ROOT", ROOT.parent / "pokeweb-source"))
ESSENTIALS_GIFS = PORT / "essentials_gifs"
ESSENTIALS_PNGS = PORT / "essentials_pngs"
GEN7_DOWNLOADS = PORT / "gen7-sprite-work" / "downloads"
TRACKER = PORT / "White2Expansion" / "data" / "pokemon.gen6.json"
PROGRESS = PORT / "White2Expansion" / "data" / "published-progress.json"
SPECIES_NAMES = PORT / "reference_repos/PKHeX/PKHeX.Core/Resources/text/other/en/text_Species_en.txt"
PWAN_DIR = ROOT / "assets" / "pokeweb_pwan"
CONFIG_PATH = PWAN_DIR / "config.bin"
REPORT_PATH = PWAN_DIR / "gen8_gen9_essentials_import_report.json"
SAVE_LINEUP = PORT / "White2Expansion" / "data" / "gen8_gen9_save_lineup.json"
PML_ROOT = ROOT / "data" / "pml"
MESON_PML = PML_ROOT / "meson.build"
VFS_BATTLE = ROOT / "vfs" / "data" / "a" / "0" / "0" / "4"
VFS_ICONS = ROOT / "vfs" / "data" / "a" / "0" / "0" / "7"
VFS_PERSONAL = ROOT / "vfs" / "data" / "a" / "0" / "1" / "6"
VFS_LEARNSETS = ROOT / "vfs" / "data" / "a" / "0" / "1" / "8"
VFS_EVOLUTIONS = ROOT / "vfs" / "data" / "a" / "0" / "1" / "9"
POKE_FORM_LIST = PML_ROOT / "poke_form_list.bin"
ICON_PALETTE_MAP = PML_ROOT / "pokeicon_palette_map.bin"
REGIONAL_DEX = PML_ROOT / "RegionalDex.bin"
SPECIES_HEADER = ROOT / "include" / "species_ids.h"
SPECIES_ENUM = ROOT / "tools" / "mkdata" / "enum" / "species.toml"
POKEGRA_SOURCE = ROOT / "src" / "pokedex_expansion" / "w2u_pokegra.cpp"
POKEDEX_SOURCE = ROOT / "src" / "pokedex_expansion" / "w2u_pokedex.cpp"
EXPANSION_LIMITS = ROOT / "src" / "pokedex_expansion" / "Expansion_LimitAdjust.s"
MKDATA = ROOT / "tools" / "mkdata" / "mkdata.py"

GEN8_START = 810
GEN9_END = 1023
FILES_PER_SPECIES = 20
ICONS_PER_SPECIES = 2
ICON_ARCHIVE_OFFSET = 8
FORM_ASSET_BASE = 724
FORM_START = 14480
ICON_FORM_START = 1456
GEN7_SPECIES_START = 722
GEN7_SPECIES_END = 809
GEN7_BATTLE_ARCHIVE_START = 19000
GEN7_ICON_ARCHIVE_START = 1904
BASE_PWAN_ASSET_START = 1200
BASE_PWAN_SPECIES_START = 722
GEN8PLUS_STATIC_ASSET_START = 1200
GEN8PLUS_BATTLE_ARCHIVE_START = GEN8PLUS_STATIC_ASSET_START * FILES_PER_SPECIES
GEN8PLUS_ICON_ARCHIVE_START = GEN8PLUS_STATIC_ASSET_START * ICONS_PER_SPECIES + ICON_ARCHIVE_OFFSET
CARRIER_SEED_BATTLE_BASE = 13060
MAX_TIMELINE = 192

sys.path.insert(0, str(ROOT / "tools" / "pwan"))
from compile_pwan import compile_pwan  # noqa: E402
from report_paths import report_path, write_report  # noqa: E402
from pwan_config import (  # noqa: E402
    PWAN_CONFIG_BACK_FLAG,
    PWAN_CONFIG_FRONT_FLAG,
    parse_config,
    write_config as write_pwan_config,
)

graphics_spec = importlib.util.spec_from_file_location(
    "build_pokegra_battle", ROOT / "tools" / "graphics" / "build_pokegra_battle.py"
)
graphics = importlib.util.module_from_spec(graphics_spec)
assert graphics_spec.loader is not None
graphics_spec.loader.exec_module(graphics)


@dataclass(frozen=True)
class FormSource:
    key: str
    name: str
    kind: str
    base_species: int
    source_stem: str
    source_type: str = "essentials"
    gen7_slug: str | None = None
    notes: str = ""


ALOLAN_FORMS = [
    (19, "Rattata", "rattata", "RATTATA_1"),
    (20, "Raticate", "raticate", "RATICATE_1"),
    (26, "Raichu", "raichu", "RAICHU_1"),
    (27, "Sandshrew", "sandshrew", "SANDSHREW_1"),
    (28, "Sandslash", "sandslash", "SANDSLASH_1"),
    (37, "Vulpix", "vulpix", "VULPIX_1"),
    (38, "Ninetales", "ninetales", "NINETALES_1"),
    (50, "Diglett", "diglett", "DIGLETT_1"),
    (51, "Dugtrio", "dugtrio", "DUGTRIO_1"),
    (52, "Meowth", "meowth", "MEOWTH_1"),
    (53, "Persian", "persian", "PERSIAN_1"),
    (74, "Geodude", "geodude", "GEODUDE_1"),
    (75, "Graveler", "graveler", "GRAVELER_1"),
    (76, "Golem", "golem", "GOLEM_1"),
    (88, "Grimer", "grimer", "GRIMER_1"),
    (89, "Muk", "muk", "MUK_1"),
    (103, "Exeggutor", "exeggutor", "EXEGGUTOR_1"),
    (105, "Marowak", "marowak", "MAROWAK_1"),
]


REGIONAL_FORMS = [
    FormSource("REGIONAL_GALAR_MEOWTH", "Galarian Meowth", "regional form", 52, "MEOWTH_2"),
    FormSource("REGIONAL_GALAR_PONYTA", "Galarian Ponyta", "regional form", 77, "PONYTA_1"),
    FormSource("REGIONAL_GALAR_RAPIDASH", "Galarian Rapidash", "regional form", 78, "RAPIDASH_1"),
    FormSource("REGIONAL_GALAR_SLOWPOKE", "Galarian Slowpoke", "regional form", 79, "SLOWPOKE_1"),
    FormSource("REGIONAL_GALAR_SLOWBRO", "Galarian Slowbro", "regional form", 80, "SLOWBRO_2"),
    FormSource("REGIONAL_GALAR_FARFETCHD", "Galarian Farfetch'd", "regional form", 83, "FARFETCHD_1"),
    FormSource("REGIONAL_GALAR_WEEZING", "Galarian Weezing", "regional form", 110, "WEEZING_1"),
    FormSource("REGIONAL_GALAR_MR_MIME", "Galarian Mr. Mime", "regional form", 122, "MRMIME_1"),
    FormSource("REGIONAL_GALAR_ARTICUNO", "Galarian Articuno", "regional form", 144, "ARTICUNO_1"),
    FormSource("REGIONAL_GALAR_ZAPDOS", "Galarian Zapdos", "regional form", 145, "ZAPDOS_1"),
    FormSource("REGIONAL_GALAR_MOLTRES", "Galarian Moltres", "regional form", 146, "MOLTRES_1"),
    FormSource("REGIONAL_GALAR_SLOWKING", "Galarian Slowking", "regional form", 199, "SLOWKING_1"),
    FormSource("REGIONAL_GALAR_CORSOLA", "Galarian Corsola", "regional form", 222, "CORSOLA_1"),
    FormSource("REGIONAL_GALAR_ZIGZAGOON", "Galarian Zigzagoon", "regional form", 263, "ZIGZAGOON_1"),
    FormSource("REGIONAL_GALAR_LINOONE", "Galarian Linoone", "regional form", 264, "LINOONE_1"),
    FormSource("REGIONAL_GALAR_DARUMAKA", "Galarian Darumaka", "regional form", 554, "DARUMAKA_2"),
    FormSource("REGIONAL_GALAR_DARMANITAN", "Galarian Darmanitan", "regional form", 555, "DARMANITAN_2"),
    FormSource("REGIONAL_GALAR_DARMANITAN_ZEN", "Galarian Darmanitan Zen Mode", "regional form", 555, "DARMANITAN_3"),
    FormSource("REGIONAL_GALAR_YAMASK", "Galarian Yamask", "regional form", 562, "YAMASK_1"),
    FormSource("REGIONAL_GALAR_STUNFISK", "Galarian Stunfisk", "regional form", 618, "STUNFISK_1"),
    FormSource("REGIONAL_HISUI_GROWLITHE", "Hisuian Growlithe", "regional form", 58, "GROWLITHE_1"),
    FormSource("REGIONAL_HISUI_ARCANINE", "Hisuian Arcanine", "regional form", 59, "ARCANINE_1"),
    FormSource("REGIONAL_HISUI_VOLTORB", "Hisuian Voltorb", "regional form", 100, "VOLTORB_1"),
    FormSource("REGIONAL_HISUI_ELECTRODE", "Hisuian Electrode", "regional form", 101, "ELECTRODE_1"),
    FormSource("REGIONAL_HISUI_TYPHLOSION", "Hisuian Typhlosion", "regional form", 157, "TYPHLOSION_1"),
    FormSource("REGIONAL_HISUI_QWILFISH", "Hisuian Qwilfish", "regional form", 211, "QWILFISH_1"),
    FormSource("REGIONAL_HISUI_SNEASEL", "Hisuian Sneasel", "regional form", 215, "SNEASEL_1"),
    FormSource("REGIONAL_HISUI_SAMUROTT", "Hisuian Samurott", "regional form", 503, "SAMUROTT_1"),
    FormSource("REGIONAL_HISUI_LILLIGANT", "Hisuian Lilligant", "regional form", 549, "LILLIGANT_1"),
    FormSource("REGIONAL_HISUI_ZORUA", "Hisuian Zorua", "regional form", 570, "ZORUA_1"),
    FormSource("REGIONAL_HISUI_ZOROARK", "Hisuian Zoroark", "regional form", 571, "ZOROARK_1"),
    FormSource("REGIONAL_HISUI_BRAVIARY", "Hisuian Braviary", "regional form", 628, "BRAVIARY_1"),
    FormSource("REGIONAL_HISUI_SLIGGOO", "Hisuian Sliggoo", "regional form", 705, "SLIGGOO_1"),
    FormSource("REGIONAL_HISUI_GOODRA", "Hisuian Goodra", "regional form", 706, "GOODRA_1"),
    FormSource("REGIONAL_HISUI_AVALUGG", "Hisuian Avalugg", "regional form", 713, "AVALUGG_1"),
    FormSource("REGIONAL_HISUI_DECIDUEYE", "Hisuian Decidueye", "regional form", 724, "DECIDUEYE_1"),
    FormSource("REGIONAL_PALDEA_TAUROS_COMBAT", "Paldean Tauros Combat Breed", "regional form", 128, "TAUROS_1"),
    FormSource("REGIONAL_PALDEA_TAUROS_BLAZE", "Paldean Tauros Blaze Breed", "regional form", 128, "TAUROS_2"),
    FormSource("REGIONAL_PALDEA_TAUROS_AQUA", "Paldean Tauros Aqua Breed", "regional form", 128, "TAUROS_3"),
    FormSource("REGIONAL_PALDEA_WOOPER", "Paldean Wooper", "regional form", 194, "WOOPER_1"),
]


ALTERNATE_FORMS = [
    FormSource("ALT_TOXTRICITY_LOW_KEY", "Toxtricity Low Key Form", "alternate form", 849, "TOXTRICITY_1"),
    FormSource("ALT_BASCULEGION_FEMALE", "Basculegion Female", "alternate form", 902, "BASCULEGION_1"),
    FormSource("ALT_INDEEDEE_FEMALE", "Indeedee Female", "alternate form", 876, "INDEEDEE_1"),
    FormSource("ALT_EISCUE_NOICE", "Eiscue Noice Face", "alternate form", 875, "EISCUE_1"),
    FormSource("ALT_MORPEKO_HANGRY", "Morpeko Hangry Mode", "alternate form", 877, "MORPEKO_1"),
    FormSource("ALT_ZACIAN_CROWNED", "Zacian Crowned Sword", "alternate form", 888, "ZACIAN_1"),
    FormSource("ALT_ZAMAZENTA_CROWNED", "Zamazenta Crowned Shield", "alternate form", 889, "ZAMAZENTA_1"),
    FormSource("ALT_URSHIFU_RAPID_STRIKE", "Urshifu Rapid Strike Style", "alternate form", 892, "URSHIFU_1"),
    FormSource("ALT_ZARUDE_DADA", "Zarude Dada", "alternate form", 893, "ZARUDE_1"),
    FormSource("ALT_CALYREX_ICE_RIDER", "Calyrex Ice Rider", "alternate form", 898, "CALYREX_1"),
    FormSource("ALT_CALYREX_SHADOW_RIDER", "Calyrex Shadow Rider", "alternate form", 898, "CALYREX_2"),
    FormSource("ALT_ENAMORUS_THERIAN", "Enamorus Therian Forme", "alternate form", 905, "ENAMORUS_1"),
    FormSource("ALT_OINKOLOGNE_FEMALE", "Oinkologne Female", "alternate form", 916, "OINKOLOGNE_1"),
    FormSource("ALT_DUDUNSPARCE_THREE_SEGMENT", "Dudunsparce Three-Segment Form", "alternate form", 982, "DUDUNSPARCE_1"),
    FormSource("ALT_MAUSHOLD_FAMILY_OF_THREE", "Maushold Family of Three", "alternate form", 925, "MAUSHOLD_1"),
    FormSource("ALT_SQUAWKABILLY_BLUE", "Squawkabilly Blue Plumage", "alternate form", 931, "SQUAWKABILLY_1"),
    FormSource("ALT_SQUAWKABILLY_YELLOW", "Squawkabilly Yellow Plumage", "alternate form", 931, "SQUAWKABILLY_2"),
    FormSource("ALT_SQUAWKABILLY_WHITE", "Squawkabilly White Plumage", "alternate form", 931, "SQUAWKABILLY_3"),
    FormSource("ALT_PALAFIN_HERO", "Palafin Hero Form", "alternate form", 964, "PALAFIN_1"),
    FormSource("ALT_GIMMIGHOUL_ROAMING", "Gimmighoul Roaming Form", "alternate form", 999, "GIMMIGHOUL_1"),
    FormSource("ALT_OGERPON_WELLSPRING", "Ogerpon Wellspring Mask", "alternate form", 1017, "OGERPON_1"),
    FormSource("ALT_OGERPON_HEARTHFLAME", "Ogerpon Hearthflame Mask", "alternate form", 1017, "OGERPON_2"),
    FormSource("ALT_OGERPON_CORNERSTONE", "Ogerpon Cornerstone Mask", "alternate form", 1017, "OGERPON_3"),
]


GMAX_SOURCE_STEMS = {
    "MEOWTH_3",
    "APPLETUN_1",
    "FLAPPLE_1",
    "HATTERENE_1",
    "GRIMMSNARL_1",
    "KINGLER_1",
    "LAPRAS_1",
    "MACHAMP_1",
    "GENGAR_2",
    "BUTTERFREE_1",
    "CENTISKORCH_1",
    "CORVIKNIGHT_1",
    "DREDNAW_1",
    "ORBEETLE_1",
    "COALOSSAL_1",
    "COPPERAJAH_1",
    "DURALUDON_1",
    "URSHIFU_2",
    "URSHIFU_3",
    "TOXTRICITY_2",
    "TOXTRICITY_3",
    "ALCREMIE_63",
    "GARBODOR_1",
    "MELMETAL_1",
    "SNORLAX_1",
}


def normalize_name(value: str) -> str:
    return re.sub(r"[^A-Z0-9]+", "", value.upper())


def rgb_to_ntr(red: int, green: int, blue: int) -> int:
    return (red // 8) | ((green // 8) << 5) | ((blue // 8) << 10)


def load_species_names() -> list[str]:
    names = SPECIES_NAMES.read_text(encoding="utf-8").splitlines()
    if len(names) <= GEN9_END:
        raise RuntimeError(f"{SPECIES_NAMES} does not contain names through {GEN9_END}")
    return names


def load_species_defines() -> tuple[dict[int, str], dict[str, int]]:
    id_to_const: dict[int, str] = {}
    const_to_id: dict[str, int] = {}
    pattern = re.compile(r"^#define\s+(SPECIES_[A-Z0-9_]+)\s+(\d+)\b")
    for line in SPECIES_HEADER.read_text(encoding="utf-8").splitlines():
        match = pattern.match(line)
        if not match:
            continue
        const = match.group(1)
        species_id = int(match.group(2))
        id_to_const[species_id] = const
        const_to_id[const] = species_id
    return id_to_const, const_to_id


def load_personal_paths() -> dict[str, Path]:
    paths: dict[str, Path] = {}
    for path in PML_ROOT.glob("*/personal.toml"):
        first = path.read_text(encoding="utf-8").splitlines()[0].strip()
        match = re.match(r"\[(SPECIES_[A-Z0-9_]+)\]", first)
        if match:
            paths[match.group(1)] = path
    return paths


def personal_path_for(species: int, id_to_const: dict[int, str], personal_paths: dict[str, Path]) -> Path:
    const = id_to_const.get(species, f"SPECIES_{species}")
    path = personal_paths.get(const)
    if path:
        return path
    numeric = PML_ROOT / str(species) / "personal.toml"
    if numeric.exists():
        return numeric
    raise FileNotFoundError(f"personal data for species {species} ({const})")


def load_personal(path: Path) -> tuple[str, dict]:
    data = tomllib.loads(path.read_text(encoding="utf-8"))
    if len(data) != 1:
        raise RuntimeError(f"{path} is not a single-root personal TOML")
    root, fields = next(iter(data.items()))
    return root, fields


def set_toml_int(text: str, key: str, value: int) -> str:
    pattern = re.compile(rf'^(("{re.escape(key)}"|{re.escape(key)})\s*=\s*).+$', re.MULTILINE)
    replacement = rf"\g<1>{value}"
    if pattern.search(text):
        return pattern.sub(replacement, text)
    return text.rstrip() + f'\n"{key}" = {value}\n'


def replace_toml_root(text: str, new_root: str) -> str:
    return re.sub(r"^\[[^\]]+\]", f"[{new_root}]", text, count=1, flags=re.MULTILINE)


def write_personal(path: Path, root: str, text: str, *, form_count: int | None = None,
                   form_data_offset: int | None = None, form_sprite_offset: int | None = None) -> None:
    text = replace_toml_root(text, root)
    if form_data_offset is not None:
        text = set_toml_int(text, "Form Data Offset", form_data_offset)
    if form_sprite_offset is not None:
        text = set_toml_int(text, "Form Sprite Offset", form_sprite_offset)
    if form_count is not None:
        text = set_toml_int(text, "Form Count", form_count)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def copy_aux(kind: str, source_path: Path, dst_id: int) -> Path:
    src = source_path.with_name(f"{kind}.toml")
    if not src.exists():
        src = PML_ROOT / "none" / f"{kind}.toml"
    text = src.read_text(encoding="utf-8")
    first = re.search(r"\[(SPECIES_[A-Z0-9_]+)\]", text)
    if first:
        text = text.replace(first.group(1), f"SPECIES_{dst_id}")
    dst = PML_ROOT / str(dst_id) / f"{kind}.toml"
    dst.parent.mkdir(parents=True, exist_ok=True)
    dst.write_text(text, encoding="utf-8")
    return dst


def compile_data_file(kind: str, src: Path, out_index: int) -> None:
    out_root = {
        "personal": VFS_PERSONAL,
        "learnset": VFS_LEARNSETS,
        "evolutions": VFS_EVOLUTIONS,
    }[kind]
    format_name = {
        "personal": "personal",
        "learnset": "learnsets",
        "evolutions": "evolutions",
    }[kind]
    out_root.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [sys.executable, str(MKDATA), "generic", str(src), str(out_root / str(out_index)), "format", format_name],
        cwd=ROOT,
        check=True,
    )


def pwan_side_path(asset: int, side: str) -> Path:
    return PWAN_DIR / f"{asset}_{side}.pwan"


def battle_path(index: int) -> Path:
    return VFS_BATTLE / str(index)


def icon_path(index: int) -> Path:
    return VFS_ICONS / str(index)


def battle_base_for_asset(asset: int) -> int:
    return asset * FILES_PER_SPECIES


def icon_base_for_asset(asset: int) -> int:
    return asset * ICONS_PER_SPECIES + ICON_ARCHIVE_OFFSET


def asset_for_sprite_form(sprite_form: int) -> int:
    return FORM_ASSET_BASE + sprite_form


def base_pwan_asset_index(species: int) -> int:
    if BASE_PWAN_SPECIES_START <= species <= GEN9_END:
        return BASE_PWAN_ASSET_START + (species - BASE_PWAN_SPECIES_START)
    return species


def base_battle_index(species: int) -> int:
    if GEN7_SPECIES_START <= species <= GEN7_SPECIES_END:
        return GEN7_BATTLE_ARCHIVE_START + ((species - GEN7_SPECIES_START) * FILES_PER_SPECIES)
    if GEN8_START <= species <= GEN9_END:
        return GEN8PLUS_BATTLE_ARCHIVE_START + ((species - GEN8_START) * FILES_PER_SPECIES)
    return species * FILES_PER_SPECIES


def base_icon_index(species: int) -> int:
    if GEN7_SPECIES_START <= species <= GEN7_SPECIES_END:
        return GEN7_ICON_ARCHIVE_START + ((species - GEN7_SPECIES_START) * ICONS_PER_SPECIES)
    if GEN8_START <= species <= GEN9_END:
        return GEN8PLUS_ICON_ARCHIVE_START + ((species - GEN8_START) * ICONS_PER_SPECIES)
    return species * ICONS_PER_SPECIES + ICON_ARCHIVE_OFFSET


def copy_battle_asset(src_asset: int, dst_asset: int) -> None:
    src_base = battle_base_for_asset(src_asset)
    dst_base = battle_base_for_asset(dst_asset)
    for offset in range(FILES_PER_SPECIES):
        src = battle_path(src_base + offset)
        dst = battle_path(dst_base + offset)
        dst.parent.mkdir(parents=True, exist_ok=True)
        if src.exists():
            shutil.copy2(src, dst)
        else:
            seed = battle_path(CARRIER_SEED_BATTLE_BASE + offset)
            shutil.copy2(seed, dst)


def seed_battle_asset(asset: int) -> None:
    dst_base = battle_base_for_asset(asset)
    for offset in range(FILES_PER_SPECIES):
        dst = battle_path(dst_base + offset)
        if not dst.exists():
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(battle_path(CARRIER_SEED_BATTLE_BASE + offset), dst)


def copy_icon_index(src_icon: int, dst_icon: int) -> None:
    for offset in range(ICONS_PER_SPECIES):
        src = icon_path(src_icon + offset)
        dst = icon_path(dst_icon + offset)
        dst.parent.mkdir(parents=True, exist_ok=True)
        if src.exists():
            shutil.copy2(src, dst)
        else:
            dst.write_bytes(b"")


def collect_image_palette(paths: list[Path]) -> list[int]:
    from PIL import Image, ImageSequence

    frames = []
    for path in paths:
        if not path or not path.exists():
            continue
        image = Image.open(path)
        if getattr(image, "is_animated", False):
            for frame in ImageSequence.Iterator(image):
                frames.append(frame.convert("RGBA"))
        else:
            frames.append(image.convert("RGBA"))
    if not frames:
        return [0] * 16
    width = max(frame.width for frame in frames)
    height = sum(frame.height for frame in frames)
    sheet = Image.new("RGBA", (width, height), (0, 0, 0, 0))
    y = 0
    for frame in frames:
        sheet.alpha_composite(frame, (0, y))
        y += frame.height
    pal = sheet.convert("P", palette=Image.Palette.ADAPTIVE, colors=15)
    raw = pal.getpalette()[:45]
    rgb_colors = [(0, 0, 0)]
    rgb_colors.extend(tuple(raw[i:i + 3]) for i in range(0, len(raw), 3))
    while len(rgb_colors) < 16:
        rgb_colors.append((0, 0, 0))
    return [rgb_to_ntr(*color) for color in rgb_colors[:16]]


def patch_nclr_file(path: Path, palette: list[int]) -> None:
    blob = struct.pack("<16H", *palette[:16])
    data = bytearray(path.read_bytes())
    if len(data) < 0x28 or data[:4] != b"RLCN":
        raise RuntimeError(f"{path} is not a supported NCLR")
    required = 0x28 + len(blob)
    if len(data) < required:
        data.extend(bytes(required - len(data)))
        struct.pack_into("<I", data, 0x08, len(data))
        if data[0x10:0x14] == b"TTLP":
            struct.pack_into("<I", data, 0x14, len(data) - 0x10)
            struct.pack_into("<I", data, 0x20, len(blob))
    data[0x28:0x28 + len(blob)] = blob
    path.write_bytes(bytes(data))


def nonempty(path: Path) -> bool:
    return path.exists() and path.stat().st_size > 0


def patch_static_fallback(asset: int, normal_sources: list[Path], shiny_sources: list[Path]) -> tuple[bool, bool, str]:
    seed_battle_asset(asset)
    base = battle_base_for_asset(asset)
    normal_palette = collect_image_palette(normal_sources)
    shiny_palette = collect_image_palette(shiny_sources) if shiny_sources else normal_palette
    shiny_derived = bool(shiny_sources)
    try:
        for side, compact_offsets, wide_offsets in (
            ("front", (0, 1), (2, 3)),
            ("back", (9, 10), (11, 12)),
        ):
            pwan = pwan_side_path(asset, side)
            if not pwan.exists():
                continue
            pixels = graphics.pwan_first_pixels(pwan)
            pixels = graphics.remap_pixels_to_palette(
                pixels,
                graphics.pwan_palette_values(pwan),
                normal_palette,
            )
            compact = graphics.segmented_pwan_pixels(pixels)
            wide = graphics.linear_wide_pwan_pixels(pixels)
            for offset in compact_offsets:
                path = battle_path(base + offset)
                if nonempty(path):
                    graphics.patch_compressed_ncgr_payload(path, compact, "nlz11")
            for offset in wide_offsets:
                path = battle_path(base + offset)
                if nonempty(path):
                    graphics.patch_compressed_ncgr_payload(path, wide, "nlz11")
        patch_nclr_file(battle_path(base + 18), normal_palette)
        patch_nclr_file(battle_path(base + 19), shiny_palette)
    except Exception as exc:
        return False, shiny_derived, str(exc)
    return True, shiny_derived, ""


def source_paths(stem: str) -> dict[str, Path | None]:
    return {
        "front": ESSENTIALS_GIFS / "Front" / f"{stem}.gif",
        "back": ESSENTIALS_GIFS / "Back" / f"{stem}.gif",
        "frontShiny": ESSENTIALS_PNGS / "Front shiny" / f"{stem}.png",
        "backShiny": ESSENTIALS_PNGS / "Back shiny" / f"{stem}.png",
    }


def gen7_source_paths(slug: str, shiny_fallback_stem: str) -> dict[str, Path | None]:
    return {
        "front": GEN7_DOWNLOADS / f"{slug}-front.gif",
        "back": GEN7_DOWNLOADS / f"{slug}-back.gif",
        "frontShiny": (
            GEN7_DOWNLOADS / f"{slug}-front-shiny.gif"
            if (GEN7_DOWNLOADS / f"{slug}-front-shiny.gif").exists()
            else ESSENTIALS_PNGS / "Front shiny" / f"{shiny_fallback_stem}.png"
        ),
        "backShiny": (
            GEN7_DOWNLOADS / f"{slug}-back-shiny.gif"
            if (GEN7_DOWNLOADS / f"{slug}-back-shiny.gif").exists()
            else ESSENTIALS_PNGS / "Back shiny" / f"{shiny_fallback_stem}.png"
        ),
    }


def existing_form_end() -> int:
    max_end = -1
    for personal in PML_ROOT.glob("*/personal.toml"):
        try:
            _root, fields = load_personal(personal)
        except Exception:
            continue
        count = int(fields.get("Form Count", 1) or 1)
        sprite_offset = int(fields.get("Form Sprite Offset", 0) or 0)
        if count > 1 and sprite_offset > 0:
            max_end = max(max_end, sprite_offset + count - 2)
    return max_end


def max_numeric_personal_id() -> int:
    return max(int(path.name) for path in PML_ROOT.iterdir() if path.is_dir() and path.name.isdigit())


def set_entry(entries: dict[tuple[int, int], dict], species: int, form: int, asset: int, side: str) -> None:
    entry = entries.setdefault(
        (species, form),
        {"species": species, "form": form, "flags": 0, "assetIndex": asset, "frontIndex": 0, "backIndex": 0},
    )
    entry["species"] = species
    entry["form"] = form
    entry["assetIndex"] = asset
    if side == "front":
        entry["flags"] = int(entry.get("flags", 0)) | PWAN_CONFIG_FRONT_FLAG
        entry["frontIndex"] = asset
    elif side == "back":
        entry["flags"] = int(entry.get("flags", 0)) | PWAN_CONFIG_BACK_FLAG
        entry["backIndex"] = asset


def compile_sources(species: int, form: int, asset: int, paths: dict[str, Path | None],
                    entries: dict[tuple[int, int], dict]) -> dict:
    stats: dict[str, dict] = {}
    missing = []
    normal_sources = []
    shiny_sources = []
    for side in ("front", "back"):
        src = paths[side]
        if src is None or not src.exists():
            missing.append(side)
            continue
        dst = pwan_side_path(asset, side)
        stats[side] = compile_pwan(src, dst)
        set_entry(entries, species, form, asset, side)
        normal_sources.append(src)
    for side in ("frontShiny", "backShiny"):
        src = paths[side]
        if src is not None and src.exists():
            shiny_sources.append(src)
    native_ok, shiny_ok, native_error = patch_static_fallback(asset, normal_sources, shiny_sources)
    return {
        "assetIndex": asset,
        "front": report_path(paths["front"]) if paths["front"] and paths["front"].exists() else None,
        "back": report_path(paths["back"]) if paths["back"] and paths["back"].exists() else None,
        "frontShiny": report_path(paths["frontShiny"]) if paths["frontShiny"] and paths["frontShiny"].exists() else None,
        "backShiny": report_path(paths["backShiny"]) if paths["backShiny"] and paths["backShiny"].exists() else None,
        "stats": stats,
        "missingSides": missing,
        "nativeFallback": native_ok,
        "nativeFallbackError": native_error,
        "shinyPalette": shiny_ok,
    }


def update_form_list(updates: dict[int, int]) -> int:
    entries: dict[int, int] = {}
    data = POKE_FORM_LIST.read_bytes()
    for offset in range(0, len(data), 4):
        species, count = struct.unpack_from("<HH", data, offset)
        if species == 0:
            break
        entries[species] = count
    entries.update(updates)
    blob = bytearray()
    for species, count in sorted(entries.items()):
        blob += struct.pack("<HH", species, count)
    blob += struct.pack("<HH", 0, 0)
    POKE_FORM_LIST.write_bytes(bytes(blob))
    return len(entries) + 1


def update_palette_map(assignments: dict[int, int]) -> None:
    data = bytearray(ICON_PALETTE_MAP.read_bytes())
    for target, source in assignments.items():
        if target >= len(data):
            data.extend(b"\x00" * (target + 1 - len(data)))
        data[target] = data[source] if source < len(data) else 0
    ICON_PALETTE_MAP.write_bytes(bytes(data))


def ensure_meson_entries(kind: str, ids: list[int]) -> None:
    text = MESON_PML.read_text(encoding="utf-8")
    list_name = {
        "personal": "personal_sources",
        "learnset": "learnset_sources",
        "evolutions": "evolution_sources",
    }[kind]
    filename = {
        "personal": "personal.toml",
        "learnset": "learnset.toml",
        "evolutions": "evolutions.toml",
    }[kind]
    start = text.index(f"{list_name} = [")
    end = text.index("\n]", start)
    block = text[start:end]
    additions = []
    for item_id in ids:
        entry = f"  '{item_id}/{filename}',"
        if entry not in block:
            additions.append(entry)
    if additions:
        text = text[:end] + "\n" + "\n".join(additions) + text[end:]
        MESON_PML.write_text(text, encoding="utf-8")


def update_species_constants(max_personal_id: int) -> None:
    text = SPECIES_HEADER.read_text(encoding="utf-8")
    new_defs = "\n".join(f"#define SPECIES_{idx} {idx}" for idx in range(1128, max_personal_id + 1))
    text = re.sub(
        r"(#define SPECIES_1127 1127\n)(?:#define SPECIES_11\d+ \d+\n|#define SPECIES_12\d+ \d+\n)*",
        r"\1" + (new_defs + "\n" if new_defs else ""),
        text,
    )
    SPECIES_HEADER.write_text(text, encoding="utf-8")

    enum_text = SPECIES_ENUM.read_text(encoding="utf-8")
    new_enum = "\n".join(f'"SPECIES_{idx}" = {idx}' for idx in range(1128, max_personal_id + 1))
    enum_text = re.sub(
        r'("SPECIES_1127" = 1127\n)(?:"SPECIES_11\d+" = \d+\n|"SPECIES_12\d+" = \d+\n)*',
        r"\1" + (new_enum + "\n" if new_enum else ""),
        enum_text,
    )
    SPECIES_ENUM.write_text(enum_text, encoding="utf-8")


def replace_regex(path: Path, pattern: str, replacement: str) -> None:
    text = path.read_text(encoding="utf-8")
    new_text = re.sub(pattern, replacement, text)
    if new_text != text:
        path.write_text(new_text, encoding="utf-8")


def update_archive_constants(max_personal_id: int, form_list_size: int) -> int:
    regional_index = max_personal_id + 1
    replace_regex(POKEGRA_SOURCE, r"#define REGIONAL_DEX_FILE_INDEX \d+", f"#define REGIONAL_DEX_FILE_INDEX {regional_index}")
    replace_regex(POKEDEX_SOURCE, r"#define REGIONAL_DEX_FILE_INDEX \d+", f"#define REGIONAL_DEX_FILE_INDEX {regional_index}")
    replace_regex(POKEDEX_SOURCE, r"#define POKE_FORM_LIST_SIZE 0x[0-9A-Fa-f]+", f"#define POKE_FORM_LIST_SIZE 0x{form_list_size:X}")
    replace_regex(EXPANSION_LIMITS, r"\.equ RegionalDexFile, \d+", f".equ RegionalDexFile, {regional_index}")
    return regional_index


def source_status(report: dict) -> str:
    if report["front"] and report["back"]:
        return "PWAN imported + shiny palette" if report["shinyPalette"] else "PWAN imported"
    if report["front"]:
        return "Front PWAN imported"
    if report["back"]:
        return "Back PWAN imported"
    return "Sprite source missing"


def progress_for(report: dict) -> dict:
    return {
        "personalData": True,
        "partyIcon": True,
        "frontSprite": report["front"] is not None,
        "backSprite": report["back"] is not None,
        "verified": False,
        "notes": "",
        "shinyPalette": bool(report["shinyPalette"]),
    }


def main() -> int:
    species_names = load_species_names()
    id_to_const, _const_to_id = load_species_defines()
    personal_paths = load_personal_paths()
    entries, max_timeline = parse_config(CONFIG_PATH)
    max_timeline = max(max_timeline, MAX_TIMELINE)

    form_sources = [
        FormSource(
            key=f"REGIONAL_ALOLA_{name.upper().replace(' ', '_')}",
            name=f"Alolan {name}",
            kind="regional form",
            base_species=species,
            source_stem=stem,
            source_type="gen7",
            gen7_slug=slug,
            notes="from gen7-sprite-work same-name Alolan source",
        )
        for species, name, slug, stem in ALOLAN_FORMS
    ]
    form_sources.extend(REGIONAL_FORMS)
    form_sources.extend(ALTERNATE_FORMS)

    next_personal = max_numeric_personal_id() + 1
    initial_sprite_form = existing_form_end() + 1
    next_sprite_form = initial_sprite_form
    new_personal_ids: list[int] = []
    new_tracker_rows: list[dict] = []
    relocated_rows: list[dict] = []
    imported_base_rows: list[dict] = []
    form_imports: list[dict] = []
    missing: list[dict] = []
    form_count_updates: dict[int, int] = {}
    palette_assignments: dict[int, int] = {}
    save_lineup = {
        "version": 1,
        "description": "Gen 8/9 base species plus imported regional/alternate forms",
        "pokemon": [],
    }

    # Base Gen 8/9 species.
    for species in range(GEN8_START, GEN9_END + 1):
        name = species_names[species]
        stem = normalize_name(name)
        paths = source_paths(stem)
        asset = base_pwan_asset_index(species)
        report = compile_sources(species, 0, asset, paths, entries)
        if report["missingSides"]:
            missing.append({"species": species, "name": name, "missingSides": report["missingSides"], "sourceStem": stem})
        battle_base = base_battle_index(species)
        icon = base_icon_index(species)
        key = f"SPECIES_{species}"
        row = {
            "key": key,
            "id": species,
            "constant": key,
            "name": name,
            "kind": "base species",
            "assetStatus": source_status(report),
            "personalFile": f"data/pml/{species}/personal.toml",
            "battleSet": battle_base,
            "battleSprites": "4/4",
            "icon": icon,
            "iconFile": "OK" if (icon_path(icon).exists() or icon_path(icon + 1).exists()) else "Missing",
            "iconPalette": "OK",
            "credits": "Pokemon Essentials Gen 9 Pack",
            "runtimeNotes": (
                f"Essentials Gen 8/9 import path; sourceStem {stem}; PWAN asset index {asset}; "
                "relocated Gen 8/9 static graphics range"
            ),
            "defaultProgress": progress_for(report),
        }
        imported_base_rows.append(row)
        save_lineup["pokemon"].append({"species": species, "form": 0, "name": name, "nickname": name[:10]})

    # Group form sources by base species so existing forms can be relocated into
    # one contiguous block per base.
    grouped: dict[int, list[FormSource]] = {}
    for source in form_sources:
        grouped.setdefault(source.base_species, []).append(source)

    for base_species, sources in sorted(grouped.items()):
        base_path = personal_path_for(base_species, id_to_const, personal_paths)
        base_root, base_fields = load_personal(base_path)
        old_count = int(base_fields.get("Form Count", 1) or 1)
        old_data_offset = int(base_fields.get("Form Data Offset", 0) or 0)
        old_sprite_offset = int(base_fields.get("Form Sprite Offset", 0) or 0)
        old_forms = []
        if old_count > 1 and old_data_offset > 0:
            for form_no in range(1, old_count):
                old_forms.append(
                    {
                        "form": form_no,
                        "personalId": old_data_offset + form_no - 1,
                        "spriteForm": old_sprite_offset + form_no - 1 if old_sprite_offset else 0,
                    }
                )

        block_len = len(old_forms) + len(sources)
        new_count = 1 + block_len
        new_data_offset = next_personal
        new_sprite_offset = next_sprite_form
        form_count_updates[base_species] = new_count

        base_text = base_path.read_text(encoding="utf-8")
        write_personal(
            base_path,
            base_root,
            base_text,
            form_count=new_count,
            form_data_offset=new_data_offset,
            form_sprite_offset=new_sprite_offset,
        )
        compile_data_file("personal", base_path, base_species)

        for index, old in enumerate(old_forms):
            form_no = index + 1
            new_id = new_data_offset + index
            sprite_form = new_sprite_offset + index
            asset = asset_for_sprite_form(sprite_form)
            old_personal_path = personal_path_for(old["personalId"], id_to_const, personal_paths)
            old_asset = asset_for_sprite_form(old["spriteForm"]) if old["spriteForm"] else asset
            old_text = old_personal_path.read_text(encoding="utf-8")
            dst_personal = PML_ROOT / str(new_id) / "personal.toml"
            write_personal(dst_personal, f"SPECIES_{new_id}", old_text, form_count=new_count, form_data_offset=0, form_sprite_offset=0)
            learnset = copy_aux("learnset", old_personal_path, new_id)
            evolutions = copy_aux("evolutions", old_personal_path, new_id)
            compile_data_file("personal", dst_personal, new_id)
            compile_data_file("learnset", learnset, new_id)
            compile_data_file("evolutions", evolutions, new_id)
            new_personal_ids.append(new_id)

            copy_battle_asset(old_asset, asset)
            copy_icon_index(icon_base_for_asset(old_asset), icon_base_for_asset(asset))
            for side in ("front", "back"):
                src = pwan_side_path(old_asset, side)
                if src.exists():
                    shutil.copy2(src, pwan_side_path(asset, side))
            old_entry = entries.get((base_species, form_no))
            if old_entry:
                flags = int(old_entry["flags"])
                entries[(base_species, form_no)] = {
                    "species": base_species,
                    "form": form_no,
                    "flags": flags,
                    "assetIndex": asset,
                    "frontIndex": asset if flags & PWAN_CONFIG_FRONT_FLAG else 0,
                    "backIndex": asset if flags & PWAN_CONFIG_BACK_FLAG else 0,
                }
            palette_assignments[asset] = old_asset
            relocated_rows.append(
                {
                    "baseSpeciesId": base_species,
                    "form": form_no,
                    "oldPersonalId": old["personalId"],
                    "newPersonalId": new_id,
                    "oldSpriteForm": old["spriteForm"],
                    "newSpriteForm": sprite_form,
                    "oldAssetIndex": old_asset,
                    "newAssetIndex": asset,
                }
            )

        for local_index, source in enumerate(sources, start=len(old_forms)):
            form_no = local_index + 1
            new_id = new_data_offset + local_index
            sprite_form = new_sprite_offset + local_index
            asset = asset_for_sprite_form(sprite_form)
            if source.source_type == "gen7":
                paths = gen7_source_paths(source.gen7_slug or source.source_stem.lower(), source.source_stem)
            else:
                paths = source_paths(source.source_stem)
            base_clone = base_path.read_text(encoding="utf-8")
            dst_personal = PML_ROOT / str(new_id) / "personal.toml"
            write_personal(dst_personal, f"SPECIES_{new_id}", base_clone, form_count=new_count, form_data_offset=0, form_sprite_offset=0)
            learnset = copy_aux("learnset", base_path, new_id)
            evolutions = copy_aux("evolutions", base_path, new_id)
            compile_data_file("personal", dst_personal, new_id)
            compile_data_file("learnset", learnset, new_id)
            compile_data_file("evolutions", evolutions, new_id)
            new_personal_ids.append(new_id)

            import_report = compile_sources(base_species, form_no, asset, paths, entries)
            if import_report["missingSides"]:
                missing.append(
                    {
                        "key": source.key,
                        "name": source.name,
                        "baseSpeciesId": base_species,
                        "form": form_no,
                        "missingSides": import_report["missingSides"],
                        "sourceStem": source.source_stem,
                    }
                )
            copy_icon_index(base_icon_index(base_species), icon_base_for_asset(asset))
            palette_assignments[asset] = base_species if base_species < ICON_PALETTE_MAP.stat().st_size else 0

            row = {
                "key": source.key,
                "id": new_id,
                "constant": f"SPECIES_{new_id}",
                "name": source.name,
                "kind": source.kind,
                "baseSpecies": base_root,
                "baseSpeciesId": base_species,
                "form": form_no,
                "spriteForm": sprite_form,
                "assetStatus": source_status(import_report),
                "personalFile": f"data/pml/{new_id}/personal.toml",
                "battleSet": battle_base_for_asset(asset),
                "battleSprites": "20/20",
                "icon": icon_base_for_asset(asset),
                "iconFile": "OK",
                "iconPalette": "OK",
                "credits": "Pokemon Essentials Gen 9 Pack" if source.source_type != "gen7" else "gen7-sprite-work",
                "runtimeNotes": (
                    f"Essentials Gen 8/9 import path; sourceStem {source.source_stem}; "
                    f"PWAN asset index {asset}; form-aware graphics slot; {source.notes}"
                ).strip(),
                "defaultProgress": progress_for(import_report),
            }
            new_tracker_rows.append(row)
            form_imports.append({"row": row, "import": import_report})
            save_lineup["pokemon"].append(
                {"species": base_species, "form": form_no, "name": source.name, "nickname": source.name[:10]}
            )

        next_personal += block_len
        next_sprite_form += block_len

    max_personal = next_personal - 1
    ensure_meson_entries("personal", new_personal_ids)
    ensure_meson_entries("learnset", new_personal_ids)
    ensure_meson_entries("evolutions", new_personal_ids)
    form_list_size = update_form_list(form_count_updates)
    update_palette_map(palette_assignments)
    regional_index = update_archive_constants(max_personal, form_list_size)
    update_species_constants(max_personal)
    shutil.copy2(REGIONAL_DEX, VFS_PERSONAL / str(regional_index))
    write_pwan_config(CONFIG_PATH, entries, max_timeline)

    tracker_rows = json.loads(TRACKER.read_text(encoding="utf-8"))
    generated_keys = {row["key"] for row in imported_base_rows + new_tracker_rows}
    tracker_rows = [row for row in tracker_rows if row.get("key") not in generated_keys]
    relocated_by_old = {(item["baseSpeciesId"], item["form"]): item for item in relocated_rows}
    for row in tracker_rows:
        key = (int(row.get("baseSpeciesId", -1)), int(row.get("form", -1)))
        relocation = relocated_by_old.get(key)
        if not relocation:
            continue
        asset = relocation["newAssetIndex"]
        row["id"] = relocation["newPersonalId"]
        row["constant"] = f"SPECIES_{relocation['newPersonalId']}"
        row["spriteForm"] = relocation["newSpriteForm"]
        row["personalFile"] = f"data/pml/{relocation['newPersonalId']}/personal.toml"
        row["battleSet"] = battle_base_for_asset(asset)
        row["icon"] = icon_base_for_asset(asset)
        row["runtimeNotes"] = (
            str(row.get("runtimeNotes", ""))
            + f"; relocated by Essentials form import from personal {relocation['oldPersonalId']} "
            f"spriteForm {relocation['oldSpriteForm']}"
        ).strip("; ")

    tracker_rows.extend(imported_base_rows)
    tracker_rows.extend(new_tracker_rows)
    tracker_rows.sort(key=lambda row: (0 if row.get("kind") == "base species" else 1, int(row.get("id", 0)), row.get("key", "")))
    write_report(TRACKER, tracker_rows)

    progress_data = json.loads(PROGRESS.read_text(encoding="utf-8"))
    pokemon_progress = progress_data.setdefault("progress", {}).setdefault("pokemon", {})
    for row in imported_base_rows + new_tracker_rows:
        pokemon_progress[row["key"]] = row["defaultProgress"]
    write_report(PROGRESS, progress_data)

    write_report(SAVE_LINEUP, save_lineup)

    imported_stems = {source.source_stem for source in form_sources}
    ignored_gmax = []
    ignored_unknown_suffix = []
    for path in sorted((ESSENTIALS_GIFS / "Front").glob("*_*.gif")):
        stem = path.stem
        if stem in imported_stems:
            continue
        if stem.endswith("_female") or "_female" in stem:
            continue
        if stem in GMAX_SOURCE_STEMS:
            ignored_gmax.append(stem)
        elif re.search(r"_\d+$", stem):
            ignored_unknown_suffix.append(stem)

    report = {
        "version": 1,
        "baseSpeciesImported": len(imported_base_rows),
        "formsImported": len(new_tracker_rows),
        "relocatedExistingForms": relocated_rows,
        "personalRange": [new_personal_ids[0], max_personal] if new_personal_ids else None,
        "spriteFormRange": [initial_sprite_form, next_sprite_form - 1],
        "regionalDexFileIndex": regional_index,
        "formListSize": form_list_size,
        "pwanConfigEntries": len(entries),
        "maxAssetIndex": max(int(entry["assetIndex"]) for entry in entries.values()),
        "missing": missing,
        "forms": form_imports,
        "ignoredGmaxSourceStems": ignored_gmax,
        "ignoredUnknownNumericSuffixes": ignored_unknown_suffix,
        "saveLineup": str(SAVE_LINEUP),
    }
    write_report(REPORT_PATH, report)

    print(
        f"Imported {len(imported_base_rows)} base species and {len(new_tracker_rows)} forms; "
        f"relocated {len(relocated_rows)} existing forms."
    )
    print(f"Personal range {report['personalRange']}; RegionalDex file {regional_index}.")
    print(f"PWAN config entries {len(entries)}, max asset {report['maxAssetIndex']}.")
    print(f"Wrote {REPORT_PATH}")
    print(f"Wrote {SAVE_LINEUP}")
    if missing:
        print(f"Missing sprite sides for {len(missing)} row(s); see report.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
