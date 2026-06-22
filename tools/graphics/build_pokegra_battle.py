#!/usr/bin/env python3
import argparse
import concurrent.futures
import json
import shutil
import struct
import sys
import tomllib
from io import BytesIO
from pathlib import Path

TOOLS_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS_ROOT / "pwan"))

from ndspy import narc  # noqa: E402
from compile_pwan import compile_pwan  # noqa: E402
from pwan_config import (  # noqa: E402
    PWAN_CONFIG_BACK_FLAG,
    PWAN_CONFIG_FRONT_FLAG,
    parse_config as parse_pwan_config,
)
from PIL import Image  # noqa: E402


CONFIG_MAGIC = 0x434E5750
CONFIG_VERSION = 1
CONFIG_ENTRY_SIZE = 8
CONFIG_HEADER_SIZE = 16
MAX_TIMELINE_ENTRIES = 128
INCREMENTAL_MANIFEST_VERSION = 1
NCGR_TILED_HEADER = bytes.fromhex(
    "5247434efffe01013020000010000100"
    "52414843202000000c000c0003000000"
    "00000000000000000012000018000000"
)
NCGR_BITMAP_HEADER = bytes.fromhex(
    "5247434efffe01014040000010000200"
    "52414843204000001000200003000000"
    "00000000010000000040000018000000"
)
NCGR_BITMAP_TAIL = bytes.fromhex("534f5043100000000000000020001000")
NCLR_HEADER = bytes.fromhex(
    "524c434efffe00014800000010000100"
    "54544c503800000004000a0000000000"
    "2000000010000000"
)
TOML_BINARY_KINDS = {"ncer", "nanr", "nmcr", "nmar"}
ORDER_FILE = "order.toml"
LEGACY_BIN_PREFIX = "004_"
GEN7_SPECIES_START = 722
GEN7_SPECIES_END = 809
GEN7_BATTLE_ARCHIVE_START = 19000
GEN7_FILES_PER_SPRITE = 20
PWAN_SEGMENTS = (
    (0x0000, 0, 0, 8, 8),
    (0x0800, 64, 0, 4, 8),
    (0x0c00, 0, 64, 8, 4),
    (0x1000, 64, 64, 4, 4),
)
G2D_MAGIC_BY_KIND = {
    "ncer": "RECN",
    "nanr": "RNAN",
    "nmcr": "RCMN",
    "nmar": "RAMN",
}
PRIMARY_SECTION_BY_KIND = {
    "ncer": "KBEC",
    "nanr": "KNBA",
    "nmcr": "KBCM",
    "nmar": "KNBA",
}
FallbackPatchJob = tuple[Path, bytes, str]


class NeedsFullRebuild(RuntimeError):
    pass


def load_toml(path: Path) -> dict:
    with path.open("rb") as f:
        return tomllib.load(f)


def clean_dir(path: Path) -> None:
    if path.exists():
        shutil.rmtree(path)
    path.mkdir(parents=True, exist_ok=True)


def ensure_dir(path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)


def file_fingerprint(path: Path | None) -> dict | None:
    if path is None:
        return None
    try:
        stat = path.stat()
    except FileNotFoundError:
        return None
    return {"size": stat.st_size, "mtime_ns": stat.st_mtime_ns}


def output_fingerprint(path: Path) -> dict | None:
    fingerprint = file_fingerprint(path)
    if fingerprint is None:
        return None
    fingerprint["path"] = path.name
    return fingerprint


def manifest_path_for_stamp(stamp: Path) -> Path:
    return stamp.with_name(f"{stamp.stem}.manifest.json")


def load_incremental_manifest(path: Path) -> dict | None:
    if not path.exists():
        return None
    try:
        return json.loads(path.read_text())
    except (OSError, json.JSONDecodeError):
        return None


def write_incremental_manifest(path: Path, manifest: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n")


def incremental_config(args: argparse.Namespace) -> dict:
    pwan_config = (
        args.gen7_pwan_fallback_source / "config.bin"
        if args.gen7_pwan_fallback_source is not None
        else None
    )
    return {
        "version": INCREMENTAL_MANIFEST_VERSION,
        "preserve_base_before": args.preserve_base_before,
        "base_archive": file_fingerprint(args.base_archive),
        "order": file_fingerprint(args.source / ORDER_FILE),
        "extra_bin_source": str(args.extra_bin_source) if args.extra_bin_source else None,
        "pwan_config": file_fingerprint(pwan_config),
        "skip_pwan": bool(args.skip_pwan),
    }


def can_incremental_rebuild(manifest: dict | None, config: dict, battle_vfs: Path) -> bool:
    if not isinstance(manifest, dict):
        return False
    if manifest.get("config") != config:
        return False
    if not battle_vfs.is_dir():
        return False
    if not (battle_vfs / ".arc").exists():
        return False
    return True


def seed_base_archive(base_archive: Path | None, battle_vfs: Path) -> int:
    if base_archive is None:
        return 0
    archive = narc.NARC(base_archive.read_bytes())
    for index, data in enumerate(archive.files):
        (battle_vfs / str(index)).write_bytes(data)
    return len(archive.files)


def lz11_compress(data: bytes) -> bytes:
    # Literal-only LZ11 is larger than search-compressed LZ11, but it is still a
    # valid 0x11 stream and keeps ordinary rebuilds fast.
    out = bytearray(struct.pack("<I", (len(data) << 8) | 0x11))
    for index in range(0, len(data), 8):
        out.append(0)
        out.extend(data[index:index + 8])
    padding = (-len(out)) % 4
    if padding:
        out.extend(b"\xff" * padding)
    return bytes(out)


def lz11_decompress(data: bytes) -> bytes:
    sys.path.insert(0, str(TOOLS_ROOT / "helpers" / "DumpUtil"))
    from lzss import decompress_bytes  # type: ignore

    return bytes(decompress_bytes(data))


def lz11_compress_nlz(data: bytes) -> bytes:
    sys.path.insert(0, str(TOOLS_ROOT / "mkdata"))
    from impl.lz import LZSerializer  # type: ignore

    out = BytesIO()
    LZSerializer().compress_nlz11(data, out)
    return out.getvalue()


def ntr_to_rgb(value: int) -> tuple[int, int, int]:
    return (
        ((value & 0x1F) * 255) // 31,
        (((value >> 5) & 0x1F) * 255) // 31,
        (((value >> 10) & 0x1F) * 255) // 31,
    )


def rgb_to_ntr(red: int, green: int, blue: int) -> int:
    return (red // 8) | ((green // 8) << 5) | ((blue // 8) << 10)


def png_indices(path: Path) -> tuple[Image.Image, bytes]:
    image = Image.open(path)
    if image.mode != "P":
        raise RuntimeError(f"{path}: expected indexed PNG")
    return image, bytes(image.getdata())


def palette_from_nclr(data: bytes) -> list[int]:
    if len(data) < len(NCLR_HEADER) + 32 or data[:4] != b"RLCN":
        raise RuntimeError("not a supported pokegra NCLR")
    return [int.from_bytes(data[len(NCLR_HEADER) + i * 2:len(NCLR_HEADER) + i * 2 + 2], "little") for i in range(16)]


def pwan_first_pixels(path: Path) -> list[list[int]]:
    data = path.read_bytes()
    (
        magic,
        version,
        width,
        height,
        bpp,
        frame_count,
        _timeline_count,
        _total_ticks,
        frame_bytes,
        _palette_colors,
        _palette_offset,
        _timeline_offset,
        frame_offset,
    ) = struct.unpack_from("<4sHHHHHHIIIIII", data, 0)
    if (
        magic != b"PWAN"
        or version != 1
        or width != 96
        or height != 96
        or bpp != 4
        or frame_count < 1
        or frame_bytes != 0x1200
    ):
        raise RuntimeError(f"{path}: expected 96x96 4bpp PWAN v1")

    frame = data[frame_offset:frame_offset + frame_bytes]
    pixels = [[0 for _x in range(96)] for _y in range(96)]
    for segment_offset, dst_x, dst_y, tiles_w, tiles_h in PWAN_SEGMENTS:
        segment = frame[segment_offset:segment_offset + tiles_w * tiles_h * 32]
        for tile_y in range(tiles_h):
            for tile_x in range(tiles_w):
                tile_offset = (tile_y * tiles_w + tile_x) * 32
                for y in range(8):
                    row = segment[tile_offset + y * 4:tile_offset + y * 4 + 4]
                    for x_pair, packed in enumerate(row):
                        x = dst_x + tile_x * 8 + x_pair * 2
                        yy = dst_y + tile_y * 8 + y
                        pixels[yy][x] = packed & 0x0f
                        pixels[yy][x + 1] = (packed >> 4) & 0x0f
    return pixels


def pwan_palette_values(path: Path) -> list[int]:
    data = path.read_bytes()
    (
        magic,
        version,
        width,
        height,
        bpp,
        _frame_count,
        _timeline_count,
        _total_ticks,
        _frame_bytes,
        palette_colors,
        palette_offset,
        _timeline_offset,
        _frame_offset,
    ) = struct.unpack_from("<4sHHHHHHIIIIII", data, 0)
    if (
        magic != b"PWAN"
        or version != 1
        or width != 96
        or height != 96
        or bpp != 4
        or palette_colors != 16
    ):
        raise RuntimeError(f"{path}: expected 96x96 4bpp PWAN v1")
    return [
        int.from_bytes(data[palette_offset + i * 2:palette_offset + i * 2 + 2], "little")
        for i in range(16)
    ]


def bgr555_to_rgb(value: int) -> tuple[int, int, int]:
    return ((value & 0x1f) << 3, ((value >> 5) & 0x1f) << 3, ((value >> 10) & 0x1f) << 3)


def nearest_palette_index(color: int, palette: list[int]) -> int:
    src_r, src_g, src_b = bgr555_to_rgb(color)
    best = 1
    best_dist = 1 << 30
    for index in range(1, 16):
        dst_r, dst_g, dst_b = bgr555_to_rgb(palette[index])
        dr = src_r - dst_r
        dg = src_g - dst_g
        db = src_b - dst_b
        dist = dr * dr + dg * dg + db * db
        if dist < best_dist:
            best = index
            best_dist = dist
    return best


def remap_pixels_to_palette(
    pixels: list[list[int]], source_palette: list[int], native_palette: list[int]
) -> list[list[int]]:
    remap = list(range(16))
    for index in range(1, 16):
        remap[index] = nearest_palette_index(source_palette[index], native_palette)
    return [[0 if value == 0 else remap[value] for value in row] for row in pixels]


def tile_indexed_region(
    pixels: list[list[int]], x0: int, y0: int, width: int, height: int
) -> bytes:
    out = bytearray()
    for tile_y in range(0, height, 8):
        for tile_x in range(0, width, 8):
            for y in range(8):
                row = pixels[y0 + tile_y + y]
                for x in range(0, 8, 2):
                    lo = row[x0 + tile_x + x] & 0x0f
                    hi = row[x0 + tile_x + x + 1] & 0x0f
                    out.append(lo | (hi << 4))
    return bytes(out)


def segmented_pwan_pixels(pixels: list[list[int]]) -> bytes:
    chunks = [
        tile_indexed_region(pixels, dst_x, dst_y, tiles_w * 8, tiles_h * 8)
        for _segment_offset, dst_x, dst_y, tiles_w, tiles_h in PWAN_SEGMENTS
    ]
    payload = b"".join(chunks)
    if len(payload) != 0x1200:
        raise RuntimeError(f"segmented PWAN fallback is {len(payload)} bytes, expected 0x1200")
    return payload


def linear_wide_pwan_pixels(pixels: list[list[int]]) -> bytes:
    indices = bytearray(256 * 128)
    for y in range(96):
        row = pixels[y]
        indices[y * 256:y * 256 + 96] = bytes(row[:96])
    return pack_bitmap_4bpp(bytes(indices), 256, 128)


def read_jasc_palette(path: Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    if len(lines) < 3 or lines[0] != "JASC-PAL" or lines[1] != "0100":
        raise RuntimeError(f"{path}: expected JASC-PAL palette")
    color_count = int(lines[2])
    if color_count < 16:
        raise RuntimeError(f"{path}: expected at least 16 colors")
    colors = []
    for line in lines[3:3 + 16]:
        parts = line.split()
        if len(parts) != 3:
            raise RuntimeError(f"{path}: invalid palette row {line!r}")
        red, green, blue = (int(part) for part in parts)
        colors.append((red, green, blue))
    return colors


def palette_payload(path: Path, high_bits: list[int] | None = None) -> bytes:
    palette = read_jasc_palette(path)
    high_bit_set = set(high_bits or [])
    out = bytearray()
    for index, (red, green, blue) in enumerate(palette):
        value = rgb_to_ntr(red, green, blue)
        if index in high_bit_set:
            value |= 0x8000
        out.extend(value.to_bytes(2, "little"))
    return bytes(out)


def build_nclr_from_pal(path: Path, high_bits: list[int] | None = None) -> bytes:
    return NCLR_HEADER + palette_payload(path, high_bits)


def pack_oam_attribute(attribute: dict) -> bytes:
    attr0 = (
        (int(attribute["position_y"]) & 0xFF)
        | ((int(attribute.get("transformable", 0)) & 1) << 8)
        | ((int(attribute.get("double_sized", 0)) & 1) << 9)
        | ((int(attribute.get("object_mode", 0)) & 3) << 10)
        | ((int(attribute.get("mosaic", 0)) & 1) << 12)
        | ((int(attribute.get("palette_mode", 0)) & 1) << 13)
        | ((int(attribute.get("key_shape", 0)) & 3) << 14)
    )
    attr1 = (
        (int(attribute["position_x"]) & 0x1FF)
        | ((int(attribute.get("transform_parameter", 0)) & 7) << 9)
        | ((int(attribute.get("horizontal_flip", 0)) & 1) << 12)
        | ((int(attribute.get("vertical_flip", 0)) & 1) << 13)
        | ((int(attribute.get("key_size", 0)) & 3) << 14)
    )
    attr2 = (
        (int(attribute["tile_index"]) & 0x3FF)
        | ((int(attribute.get("priority", 0)) & 3) << 10)
        | ((int(attribute.get("palette_index", 0)) & 0xF) << 12)
    )
    return struct.pack("<HHH", attr0, attr1, attr2)


def frame_property_size(prop: dict) -> int:
    animation_type = int(prop.get("animation_type", 0))
    if animation_type == 0:
        return 2
    if animation_type == 1:
        return 16
    if animation_type == 2:
        return 8
    raise RuntimeError(f"unsupported animation_type {animation_type}")


def fixed_20_12(value: int | float) -> int:
    if isinstance(value, float):
        return round(value * 4096.0) & 0xFFFFFFFF
    return int(value) & 0xFFFFFFFF


def pack_kbec(section: dict) -> bytes:
    if isinstance(section.get("cells"), dict):
        section = dict(section)
        section["cells"] = [
            {"name": name, **cell}
            for name, cell in section["cells"].items()
        ]

    if section.get("cells") and isinstance(section["cells"][0].get("objects"), list):
        attributes = []
        cells = []
        for cell in section["cells"]:
            objects = cell.get("objects", [])
            derived = dict(cell)
            derived["number_objects"] = len(objects)
            derived["offset_object"] = len(attributes) * 6
            derived.pop("objects", None)
            cells.append(derived)
            attributes.extend(objects)

        section = dict(section)
        section["cells"] = cells
        section["attributes"] = attributes
        section["number_cells"] = len(cells)
        section["offset_data_cell"] = 0x18

    if isinstance(section.get("object_groups"), dict):
        section = dict(section)
        section["object_groups"] = [
            {"name": name, **group}
            for name, group in section["object_groups"].items()
        ]

    if section.get("object_groups"):
        object_groups = section.get("object_groups", [])
        group_offsets = {}
        attributes = []
        for group in object_groups:
            name = group.get("name")
            if not isinstance(name, str):
                raise RuntimeError("KBEC object group requires name")
            group_offsets[name] = len(attributes) * 6
            attributes.extend(group.get("attributes", []))

        cells = []
        for cell in section.get("cells", []):
            object_group = cell.get("objects")
            if object_group not in group_offsets:
                raise RuntimeError(f"KBEC cell references unknown object group {object_group!r}")
            group = next(group for group in object_groups if group.get("name") == object_group)
            derived = dict(cell)
            derived["number_objects"] = len(group.get("attributes", []))
            derived["offset_object"] = group_offsets[object_group]
            cells.append(derived)

        section = dict(section)
        section["cells"] = cells
        section["attributes"] = attributes
        section["number_cells"] = len(cells)
        section["offset_data_cell"] = 0x18

    cells = section.get("cells", [])
    attributes = section.get("attributes", [])
    use_bounds = int(section.get("use_bounds", 0))
    cell_size = 16 if use_bounds else 8
    body = bytearray(struct.pack(
        "<HHIIIII",
        int(section.get("number_cells", len(cells))),
        use_bounds,
        int(section.get("offset_data_cell", 0x18)),
        int(section.get("size_boundary", 0)),
        int(section.get("unknown0", 0)),
        int(section.get("unknown1", 0)),
        int(section.get("unknown2", 0)),
    ))
    if len(body) < int(section.get("offset_data_cell", 0x18)):
        body.extend(bytes(int(section.get("offset_data_cell", 0x18)) - len(body)))
    for cell in cells:
        body.extend(struct.pack(
            "<HBBI",
            int(cell["number_objects"]),
            int(cell.get("unknown0", 0)) & 0xFF,
            int(cell.get("unknown1", 0)) & 0xFF,
            int(cell["offset_object"]),
        ))
        if use_bounds:
            body.extend(struct.pack(
                "<hhhh",
                int(cell.get("bound_right", 0)),
                int(cell.get("bound_bottom", 0)),
                int(cell.get("bound_left", 0)),
                int(cell.get("bound_top", 0)),
            ))
    expected = int(section.get("offset_data_cell", 0x18)) + len(cells) * cell_size
    if len(body) < expected:
        body.extend(bytes(expected - len(body)))
    for attribute in attributes:
        body.extend(pack_oam_attribute(attribute))
    body.extend(bytes(int(section.get("padding_size", 0))))
    return bytes(body)


def pack_frame_property(prop: dict) -> bytes:
    animation_type = int(prop.get("animation_type", 0))
    cell_index = prop.get("cell_index", prop.get("cell", prop.get("multi_cell", 0)))
    if animation_type == 0:
        return struct.pack("<H", int(cell_index))
    if animation_type == 1:
        return struct.pack(
            "<HHIIhh",
            int(cell_index),
            int(prop.get("rotate", 0)),
            fixed_20_12(prop.get("scale_w", 0)),
            fixed_20_12(prop.get("scale_h", 0)),
            int(prop.get("translate_x", 0)),
            int(prop.get("translate_y", 0)),
        )
    if animation_type == 2:
        return struct.pack(
            "<HHhh",
            int(cell_index),
            int(prop.get("unknown0", 0)),
            int(prop.get("translate_x", 0)),
            int(prop.get("translate_y", 0)),
        )
    raise RuntimeError(f"unsupported animation_type {animation_type}")


def pack_knba(section: dict) -> bytes:
    if isinstance(section.get("sequences"), dict):
        section = dict(section)
        section["sequences"] = [
            {"name": name, **sequence}
            for name, sequence in section["sequences"].items()
        ]

    if section.get("sequences") and "frames" in section["sequences"][0]:
        property_offsets = {}
        property_data = bytearray()

        frames = []
        frame_offset = 0
        sequences = []
        for sequence in section.get("sequences", []):
            sequence_frames = sequence.get("frames", [])
            derived_sequence = dict(sequence)
            derived_sequence["number_frames"] = len(sequence_frames)
            derived_sequence["offset_frame"] = frame_offset
            derived_sequence.pop("frames", None)
            sequences.append(derived_sequence)
            frame_offset += len(sequence_frames) * 8
            for frame in sequence_frames:
                if "property" in frame:
                    raise RuntimeError("KNBA authoring frames must inline properties")
                property_offset = len(property_data)
                property_data.extend(pack_frame_property(frame))
                property_data.extend(bytes(int(value) & 0xFF for value in frame.get("padding_after", [])))
                frames.append({
                    "offset_properties": property_offset,
                    "duration_in_frames": frame.get("duration_in_frames", 0),
                    "unknown0": frame.get("frame_unknown", -16657),
                })
        property_data_size = len(property_data)

        section = dict(section)
        section["sequences"] = sequences
        section["frames"] = frames
        section["frame_properties"] = []
        section["property_padding"] = []
        section["number_sequences"] = len(sequences)
        section["number_frames"] = len(frames)
        section["offset_data_sequences"] = 0x18
        section["offset_data_frame"] = 0x18 + len(sequences) * 16
        section["offset_data_frame_properties"] = section["offset_data_frame"] + len(frames) * 8
        section["property_data_size"] = property_data_size
    else:
        property_data = None

    sequences = section.get("sequences", [])
    frames = section.get("frames", [])
    properties = section.get("frame_properties", [])
    property_padding = section.get("property_padding", [])
    property_data_size = int(section.get("property_data_size", 0))
    body = bytearray(struct.pack(
        "<HHIIIII",
        int(section.get("number_sequences", len(sequences))),
        int(section.get("number_frames", len(frames))),
        int(section.get("offset_data_sequences", 0x18)),
        int(section.get("offset_data_frame", 0)),
        int(section.get("offset_data_frame_properties", 0)),
        int(section.get("unknown0", 0)),
        int(section.get("unknown1", 0)),
    ))
    if len(body) < int(section.get("offset_data_sequences", 0x18)):
        body.extend(bytes(int(section.get("offset_data_sequences", 0x18)) - len(body)))
    for sequence in sequences:
        body.extend(struct.pack(
            "<IHHII",
            int(sequence["number_frames"]),
            int(sequence.get("animation_type", 0)),
            int(sequence.get("cell_type", 0)),
            int(sequence.get("loop_mode", 0)),
            int(sequence["offset_frame"]),
        ))
    if len(body) < int(section["offset_data_frame"]):
        body.extend(bytes(int(section["offset_data_frame"]) - len(body)))
    for frame in frames:
        body.extend(struct.pack(
            "<IHh",
            int(frame["offset_properties"]),
            int(frame["duration_in_frames"]),
            int(frame["unknown0"]),
        ))
    if len(body) < int(section["offset_data_frame_properties"]):
        body.extend(bytes(int(section["offset_data_frame_properties"]) - len(body)))
    if property_data is None:
        props = bytearray(property_data_size)
        for prop in properties:
            packed = pack_frame_property(prop)
            offset = int(prop["offset"])
            props[offset:offset + len(packed)] = packed
        for pad in property_padding:
            data = bytes(int(value) & 0xFF for value in pad.get("bytes", []))
            offset = int(pad["offset"])
            props[offset:offset + len(data)] = data
    else:
        props = property_data
    body.extend(props)
    return bytes(body)


def pack_kbcm(section: dict) -> bytes:
    if isinstance(section.get("multi_cells"), dict):
        section = dict(section)
        section["multi_cells"] = [
            {"name": name, **multi_cell}
            for name, multi_cell in section["multi_cells"].items()
        ]

    if section.get("multi_cells") and "properties" in section["multi_cells"][0]:
        properties = []
        offset = 0
        multi_cells = []
        for multi_cell in section.get("multi_cells", []):
            rows = multi_cell.get("properties", [])
            derived = dict(multi_cell)
            derived["number_displayed_cells"] = len(rows)
            derived["number_loaded_cells"] = int(multi_cell.get("loaded_cells", len(rows)))
            derived["offset_data"] = offset
            derived.pop("properties", None)
            derived.pop("loaded_cells", None)
            multi_cells.append(derived)
            offset += len(rows) * 8
            properties.extend(rows)

        section = dict(section)
        section["multi_cells"] = multi_cells
        section["properties"] = properties
        section["number_multi_cells"] = len(multi_cells)
        section["offset_data_multi_cell"] = 0x14
        section["offset_data_multi_cell_properties"] = 0x14 + len(multi_cells) * 8

    multi_cells = section.get("multi_cells", [])
    properties = section.get("properties", [])
    body = bytearray(struct.pack(
        "<HHIIII",
        int(section.get("number_multi_cells", len(multi_cells))),
        int(section.get("unknown0", 0)),
        int(section.get("offset_data_multi_cell", 0x14)),
        int(section.get("offset_data_multi_cell_properties", 0)),
        int(section.get("unknown1", 0)),
        int(section.get("unknown2", 0)),
    ))
    if len(body) < int(section.get("offset_data_multi_cell", 0x14)):
        body.extend(bytes(int(section.get("offset_data_multi_cell", 0x14)) - len(body)))
    for multi_cell in multi_cells:
        body.extend(struct.pack(
            "<HHI",
            int(multi_cell["number_displayed_cells"]),
            int(multi_cell["number_loaded_cells"]),
            int(multi_cell["offset_data"]),
        ))
    if len(body) < int(section["offset_data_multi_cell_properties"]):
        body.extend(bytes(int(section["offset_data_multi_cell_properties"]) - len(body)))
    for prop in properties:
        if "sequence" in prop:
            raise RuntimeError("KBCM sequence references must be resolved before packing")
        body.extend(struct.pack(
            "<HhhBB",
            int(prop.get("index_sequence", 0)),
            int(prop.get("translate_x", 0)),
            int(prop.get("translate_y", 0)),
            int(prop.get("frame_mode", 0)) & 0xFF,
            int(prop.get("unique_id", 0)) & 0xFF,
        ))
    return bytes(body)


def named_index_map(path: Path, key: str) -> dict[str, int]:
    data = load_toml(path)
    values = data.get(key, {})
    if isinstance(values, dict):
        return {name: index for index, name in enumerate(values.keys())}
    if isinstance(values, list):
        out = {}
        for index, value in enumerate(values):
            name = value.get("name")
            if isinstance(name, str):
                out[name] = index
        return out
    return {}


def resolve_named_animation_references(data: dict, name_map: dict[str, int]) -> dict:
    if not name_map or not isinstance(data.get("sequences"), dict):
        return data
    data = dict(data)
    sequences = {}
    for sequence_name, sequence in data["sequences"].items():
        sequence = dict(sequence)
        frames = []
        for frame in sequence.get("frames", []):
            frame = dict(frame)
            for field in ("cell", "multi_cell"):
                if field in frame:
                    name = frame.pop(field)
                    if name not in name_map:
                        raise RuntimeError(f"unknown {field} reference {name!r}")
                    frame["cell_index"] = name_map[name]
            frames.append(frame)
        sequence["frames"] = frames
        sequences[sequence_name] = sequence
    data["sequences"] = sequences
    return data


def resolve_named_multicell_references(data: dict, sequence_map: dict[str, int]) -> dict:
    if not sequence_map or not isinstance(data.get("multi_cells"), dict):
        return data
    data = dict(data)
    multi_cells = {}
    for multi_cell_name, multi_cell in data["multi_cells"].items():
        multi_cell = dict(multi_cell)
        properties = []
        for prop in multi_cell.get("properties", []):
            prop = dict(prop)
            if "sequence" in prop:
                name = prop.pop("sequence")
                if name not in sequence_map:
                    raise RuntimeError(f"unknown sequence reference {name!r}")
                prop["index_sequence"] = sequence_map[name]
            properties.append(prop)
        multi_cell["properties"] = properties
        multi_cells[multi_cell_name] = multi_cell
    data["multi_cells"] = multi_cells
    return data


def pack_lbal(section: dict) -> bytes:
    labels = section.get("labels")
    if not isinstance(labels, list):
        raise RuntimeError("LBAL section requires labels")
    offsets = []
    string_data = bytearray()
    for label in labels:
        if not isinstance(label, str):
            raise RuntimeError("LBAL labels must be strings")
        offsets.append(len(string_data))
        string_data.extend(label.encode("utf-8"))
        string_data.append(0)
    body = bytearray()
    for offset in offsets:
        body.extend(int(offset).to_bytes(4, "little"))
    body.extend(string_data)
    return bytes(body)


def pack_section(section: dict) -> bytes:
    magic = section.get("magic")
    if not isinstance(magic, str) or len(magic.encode("ascii")) != 4:
        raise RuntimeError(f"invalid section magic {magic!r}")

    if magic == "KBEC":
        body = pack_kbec(section)
    elif magic == "KNBA":
        body = pack_knba(section)
    elif magic == "KBCM":
        body = pack_kbcm(section)
    elif magic == "LBAL":
        body = pack_lbal(section)
    elif magic == "TXEU":
        body = struct.pack("<I", int(section.get("extended", 0)))
    else:
        raise RuntimeError(f"unsupported section magic {magic!r}")

    return magic.encode("ascii") + (len(body) + 8).to_bytes(4, "little") + bytes(body)


def authoring_sections(data: dict, expected_kind: str) -> list[dict]:
    primary_magic = PRIMARY_SECTION_BY_KIND[expected_kind]
    primary = {"magic": primary_magic}

    if expected_kind == "ncer":
        for key in ("use_bounds", "size_boundary", "unknown0", "unknown1", "unknown2", "padding_size"):
            if key in data:
                primary[key] = data[key]
        primary["object_groups"] = data.get("object_groups", [])
        primary["cells"] = data.get("cells", [])
    elif expected_kind in ("nanr", "nmar"):
        for key in ("unknown0", "unknown1"):
            if key in data:
                primary[key] = data[key]
        primary["sequences"] = data.get("sequences", [])
    elif expected_kind == "nmcr":
        for key in ("unknown0", "unknown1", "unknown2"):
            if key in data:
                primary[key] = data[key]
        primary["multi_cells"] = data.get("multi_cells", [])
    else:
        raise RuntimeError(f"unsupported G2D kind {expected_kind!r}")

    derived_labels = None
    if expected_kind == "ncer" and isinstance(data.get("cells"), dict):
        derived_labels = list(data["cells"].keys())
    elif expected_kind in ("nanr", "nmar") and isinstance(data.get("sequences"), dict):
        derived_labels = list(data["sequences"].keys())
    elif expected_kind == "nmcr" and isinstance(data.get("multi_cells"), dict):
        derived_labels = list(data["multi_cells"].keys())

    sections = [primary]
    if "labels" in data:
        sections.append({"magic": "LBAL", "labels": data["labels"]})
    elif derived_labels is not None:
        sections.append({"magic": "LBAL", "labels": derived_labels})
    if "extended" in data:
        sections.append({"magic": "TXEU", "extended": data["extended"]})
    return sections


def build_binary_from_toml(path: Path, expected_kind: str, reference_map: dict[str, int] | None = None) -> bytes:
    data = load_toml(path)
    if reference_map is not None:
        if expected_kind == "nmcr":
            data = resolve_named_multicell_references(data, reference_map)
        else:
            data = resolve_named_animation_references(data, reference_map)
    fmt = data.get("format")
    if fmt != expected_kind:
        raise RuntimeError(f"{path}: expected format {expected_kind!r}, got {fmt!r}")
    payload = data.get("data")
    if isinstance(payload, str):
        return bytes.fromhex(payload)

    sections = data.get("sections")
    if sections is None:
        sections = authoring_sections(data, expected_kind)
    if not isinstance(sections, list):
        raise RuntimeError(f"{path}: invalid sections")
    magic = data.get("magic", G2D_MAGIC_BY_KIND[expected_kind])
    if not isinstance(magic, str) or len(magic.encode("ascii")) != 4:
        raise RuntimeError(f"{path}: invalid magic")
    byte_order = int(data.get("byte_order", 0xFEFF))
    version = int(data.get("version", 0x0100))
    header_size = int(data.get("header_size", 0x10))
    if header_size != 0x10:
        raise RuntimeError(f"{path}: unsupported header_size {header_size}")

    section_payload = b"".join(pack_section(section) for section in sections)
    file_size = header_size + len(section_payload)
    return (
        magic.encode("ascii")
        + byte_order.to_bytes(2, "little")
        + version.to_bytes(2, "little")
        + file_size.to_bytes(4, "little")
        + header_size.to_bytes(2, "little")
        + len(sections).to_bytes(2, "little")
        + section_payload
    )


def pack_tiled_4bpp(indices: bytes, width: int, height: int) -> bytes:
    if width % 8 != 0 or height % 8 != 0:
        raise RuntimeError("NCGR PNG dimensions must be multiples of 8")
    tiles_wide = width // 8
    tiles_high = height // 8
    out = bytearray()
    for tile_y in range(tiles_high):
        for tile_x in range(tiles_wide):
            for y in range(8):
                row = (tile_y * 8 + y) * width + tile_x * 8
                for x in range(0, 8, 2):
                    left = indices[row + x] & 0xF
                    right = indices[row + x + 1] & 0xF
                    out.append((right << 4) | left)
    return bytes(out)


def pack_bitmap_4bpp(indices: bytes, width: int, height: int) -> bytes:
    if width % 8 != 0 or height % 8 != 0:
        raise RuntimeError("NCGR PNG dimensions must be multiples of 8")
    tiles_wide = width // 8
    tiles_high = height // 8
    out = bytearray(tiles_wide * tiles_high * 32)
    for tile_y in range(tiles_high):
        for tile_x in range(tiles_wide):
            base = 4 * tile_x + 32 * tile_y * tiles_wide
            for y in range(8):
                row = (tile_y * 8 + y) * width + tile_x * 8
                for x in range(0, 8, 2):
                    left = indices[row + x] & 0xF
                    right = indices[row + x + 1] & 0xF
                    out[base + (x // 2) + 4 * y * tiles_wide] = (right << 4) | left
    return bytes(out)


def build_ncgr_from_png(path: Path, sopc_height: int = 32) -> bytes:
    image, indices = png_indices(path)
    width, height = image.size
    if (width, height) == (96, 96):
        return NCGR_TILED_HEADER + pack_tiled_4bpp(indices, width, height)
    if (width, height) == (256, 128):
        if sopc_height not in (16, 32):
            raise RuntimeError(f"{path}: unsupported SOPC height {sopc_height}")
        tail = bytearray(NCGR_BITMAP_TAIL)
        tail[14] = sopc_height
        return NCGR_BITMAP_HEADER + pack_bitmap_4bpp(indices, width, height) + bytes(tail)
    raise RuntimeError(f"{path}: unsupported NCGR PNG dimensions {width}x{height}")


def build_nns_payload(entry: dict, manifest: Path, manifest_data: dict | None = None) -> bytes:
    for dependency in entry.get("depends_on", []):
        if not (manifest.parent / dependency).exists():
            raise RuntimeError(f"{manifest}: {entry['raw']} depends on missing {dependency}")
    raw = manifest.parent / entry["raw"]
    if not raw.exists():
        raise RuntimeError(f"{manifest}: raw file {raw.name!r} does not exist")
    kind = entry.get("kind")
    if kind == "ncgr" and raw.suffix == ".png":
        sopc_height = entry.get("sopc_height")
        if sopc_height is None and manifest_data is not None:
            sopc_height = manifest_data.get("sopc_height")
        return build_ncgr_from_png(raw, int(sopc_height or 32))
    if kind == "nclr" and raw.suffix == ".pal":
        return build_nclr_from_pal(raw, entry.get("high_bits"))
    if kind in TOML_BINARY_KINDS and raw.suffix == ".toml":
        reference_map = None
        dependencies = entry.get("depends_on", [])
        if kind == "nanr" and dependencies:
            reference_map = named_index_map(manifest.parent / dependencies[0], "cells")
        elif kind == "nmcr" and dependencies:
            reference_map = named_index_map(manifest.parent / dependencies[0], "sequences")
        elif kind == "nmar" and len(dependencies) >= 2:
            reference_map = named_index_map(manifest.parent / dependencies[1], "multi_cells")
        return build_binary_from_toml(raw, kind, reference_map)
    return raw.read_bytes()


def stage_nns_entry(entry: dict, manifest: Path, manifest_data: dict, output: Path) -> None:
    payload = build_nns_payload(entry, manifest, manifest_data)
    if entry.get("lz11", False):
        output.write_bytes(lz11_compress(payload))
    else:
        output.write_bytes(payload)


def nns_source_fingerprint(entry: dict, manifest: Path, manifest_data: dict) -> dict:
    raw = manifest.parent / entry["raw"]
    dependencies = [manifest.parent / dependency for dependency in entry.get("depends_on", [])]
    return {
        "entry": entry,
        "manifest": file_fingerprint(manifest),
        "raw": file_fingerprint(raw),
        "dependencies": [
            {"name": dependency.name, "fingerprint": file_fingerprint(dependency)}
            for dependency in dependencies
        ],
        "sopc_height": manifest_data.get("sopc_height"),
    }


def graphics_order_entries(source_root: Path) -> list[dict]:
    order_path = source_root / ORDER_FILE
    order = load_toml(order_path)
    entries = order.get("entries")
    if not isinstance(entries, list):
        raise RuntimeError(f"{order_path}: missing entries array")
    for index, entry in enumerate(entries):
        folder = entry.get("folder")
        kind = entry.get("type")
        if not isinstance(folder, str):
            raise RuntimeError(f"{order_path}: entries[{index}].folder must be a string")
        if kind not in ("nns", "pwan"):
            raise RuntimeError(f"{order_path}: entries[{index}].type must be \"nns\" or \"pwan\"")
    return entries


def collect_nns_stage_entries(source_root: Path, preserve_before: int) -> tuple[int, list[dict]]:
    if not (source_root / ORDER_FILE).exists():
        raise NeedsFullRebuild("legacy numeric pokegra source layout needs full rebuild")

    count = 0
    stage_entries = []
    for item in graphics_order_entries(source_root):
        manifest = source_root / item["folder"] / "nns.toml"
        manifest_data = load_toml(manifest)
        for entry in manifest_data.get("entries", []):
            if count >= preserve_before:
                stage_entries.append({
                    "index": count,
                    "entry": entry,
                    "manifest": manifest,
                    "manifest_data": manifest_data,
                    "source": nns_source_fingerprint(entry, manifest, manifest_data),
                })
            count += 1
    return count, stage_entries


def stage_nns_archive_entries_incremental(
    source_root: Path,
    battle_vfs: Path,
    preserve_before: int,
    previous: dict,
    force: bool,
) -> tuple[int, set[int], dict, int]:
    nns_count, stage_entries = collect_nns_stage_entries(source_root, preserve_before)
    previous_count = previous.get("count")
    if not force and previous_count is not None and previous_count != nns_count:
        raise NeedsFullRebuild("pokegra NNS entry count changed")

    previous_entries = previous.get("entries", {}) if isinstance(previous, dict) else {}
    next_entries = {}
    changed_outputs: set[int] = set()
    staged = 0

    for stage_entry in stage_entries:
        index = int(stage_entry["index"])
        key = str(index)
        output = battle_vfs / key
        current_output = output_fingerprint(output)
        source_fingerprint = stage_entry["source"]
        previous_entry = previous_entries.get(key)
        should_stage = (
            force
            or previous_entry is None
            or previous_entry.get("source") != source_fingerprint
            or current_output is None
        )
        if should_stage:
            stage_nns_entry(
                stage_entry["entry"],
                stage_entry["manifest"],
                stage_entry["manifest_data"],
                output,
            )
            current_output = output_fingerprint(output)
            changed_outputs.add(index)
            staged += 1
        next_entries[key] = {
            "source": source_fingerprint,
            "output": current_output,
        }

    return nns_count, changed_outputs, {"count": nns_count, "entries": next_entries}, staged


def copy_nns_archive_entries(source_root: Path, battle_vfs: Path, preserve_before: int = 0) -> int:
    if (source_root / ORDER_FILE).exists():
        count = 0
        for item in graphics_order_entries(source_root):
            manifest = source_root / item["folder"] / "nns.toml"
            manifest_data = load_toml(manifest)
            for entry in manifest_data.get("entries", []):
                if count >= preserve_before:
                    stage_nns_entry(entry, manifest, manifest_data, battle_vfs / str(count))
                count += 1
        return count

    source = source_root
    count = 0
    for file in sorted(source.iterdir(), key=lambda p: int(p.name) if p.name.isdecimal() else -1):
        if not file.is_file() or not file.name.isdecimal():
            continue
        shutil.copy2(file, battle_vfs / file.name)
        count += 1
    return count


def extra_bin_member_id(path: Path) -> int | None:
    if path.name.isdecimal():
        return int(path.name)
    if path.name.startswith(LEGACY_BIN_PREFIX) and path.name.endswith(".bin"):
        raw = path.name[len(LEGACY_BIN_PREFIX):-4]
        if raw.isdecimal():
            return int(raw)
    return None


def copy_extra_bin_entries(extra_source: Path | None, battle_vfs: Path, first_extra_index: int) -> int:
    if extra_source is None:
        return 0
    if not extra_source.is_dir():
        raise NotADirectoryError(extra_source)

    count = 0
    for file in sorted(extra_source.iterdir()):
        if not file.is_file():
            continue
        index = extra_bin_member_id(file)
        if index is None:
            continue
        if index < first_extra_index:
            raise RuntimeError(
                f"{file}: extra battle graphic index {index} overlaps generated range 0..{first_extra_index - 1}"
            )
        shutil.copy2(file, battle_vfs / str(index))
        count += 1
    return count


def collect_extra_bin_entries(extra_source: Path | None, first_extra_index: int) -> list[dict]:
    if extra_source is None:
        return []
    if not extra_source.is_dir():
        raise NotADirectoryError(extra_source)

    entries = []
    for file in sorted(extra_source.iterdir()):
        if not file.is_file():
            continue
        index = extra_bin_member_id(file)
        if index is None:
            continue
        if index < first_extra_index:
            raise RuntimeError(
                f"{file}: extra battle graphic index {index} overlaps generated range 0..{first_extra_index - 1}"
            )
        entries.append({
            "index": index,
            "path": file,
            "source": {"name": file.name, "fingerprint": file_fingerprint(file)},
        })
    return entries


def copy_extra_bin_entries_incremental(
    extra_source: Path | None,
    battle_vfs: Path,
    first_extra_index: int,
    previous: dict,
    force: bool,
) -> tuple[int, set[int], dict, int]:
    entries = collect_extra_bin_entries(extra_source, first_extra_index)
    current_keys = {str(entry["index"]) for entry in entries}
    previous_entries = previous.get("entries", {}) if isinstance(previous, dict) else {}
    if not force and set(previous_entries.keys()) != current_keys:
        raise NeedsFullRebuild("extra battle graphic file set changed")

    next_entries = {}
    changed_outputs: set[int] = set()
    copied = 0
    for entry in entries:
        index = int(entry["index"])
        key = str(index)
        output = battle_vfs / key
        current_output = output_fingerprint(output)
        source_fingerprint = entry["source"]
        previous_entry = previous_entries.get(key)
        should_copy = (
            force
            or previous_entry is None
            or previous_entry.get("source") != source_fingerprint
            or current_output is None
        )
        if should_copy:
            shutil.copy2(entry["path"], output)
            current_output = output_fingerprint(output)
            changed_outputs.add(index)
            copied += 1
        next_entries[key] = {
            "source": source_fingerprint,
            "output": current_output,
        }

    return len(entries), changed_outputs, {"entries": next_entries}, copied


def gen7_battle_base(species: int) -> int:
    return GEN7_BATTLE_ARCHIVE_START + (species - GEN7_SPECIES_START) * GEN7_FILES_PER_SPRITE


def patch_compressed_ncgr_payload(path: Path, payload: bytes, compression: str) -> None:
    decompressed = bytearray(lz11_decompress(path.read_bytes()))
    if len(decompressed) < len(payload) or decompressed[:4] != b"RGCN":
        raise RuntimeError(f"{path}: not a supported compressed NCGR")
    decompressed[-len(payload):] = payload
    if compression == "literal":
        path.write_bytes(lz11_compress(bytes(decompressed)))
    elif compression == "nlz11":
        path.write_bytes(lz11_compress_nlz(bytes(decompressed)))
    else:
        raise RuntimeError(f"unsupported fallback compression {compression!r}")


def patch_compressed_ncgr_payload_job(job: FallbackPatchJob) -> str:
    path, payload, compression = job
    patch_compressed_ncgr_payload(path, payload, compression)
    return str(path)


def run_fallback_patch_jobs(patch_jobs: list[FallbackPatchJob], fallback_jobs: int) -> int:
    if fallback_jobs < 1:
        raise RuntimeError("--fallback-jobs must be at least 1")
    if not patch_jobs:
        return 0
    if fallback_jobs == 1:
        for job in patch_jobs:
            patch_compressed_ncgr_payload_job(job)
        return len(patch_jobs)

    workers = min(fallback_jobs, len(patch_jobs))
    with concurrent.futures.ProcessPoolExecutor(max_workers=workers) as executor:
        for _path in executor.map(patch_compressed_ncgr_payload_job, patch_jobs, chunksize=4):
            pass
    return len(patch_jobs)


def nonempty_path(path: Path) -> bool:
    return path.exists() and path.stat().st_size > 0


def patch_gen7_native_fallbacks(
    pwan_source: Path | None,
    battle_vfs: Path,
    fallback_jobs: int,
    fallback_compression: str,
) -> int:
    patched, _manifest = patch_gen7_native_fallbacks_incremental(
        pwan_source,
        battle_vfs,
        fallback_jobs,
        fallback_compression,
        {},
        set(),
        True,
    )
    return patched


def patch_gen7_native_fallbacks_incremental(
    pwan_source: Path | None,
    battle_vfs: Path,
    fallback_jobs: int,
    fallback_compression: str,
    previous: dict,
    changed_outputs: set[int],
    force: bool,
) -> tuple[int, dict]:
    if pwan_source is None:
        return 0, {"entries": {}}
    config_path = pwan_source / "config.bin"
    if not config_path.exists():
        raise FileNotFoundError(config_path)

    entries, _max_timeline = parse_pwan_config(config_path)
    patch_jobs: list[FallbackPatchJob] = []
    patched_keys: list[str] = []
    previous_entries = previous.get("entries", {}) if isinstance(previous, dict) else {}
    next_entries = {}
    for species in range(GEN7_SPECIES_START, GEN7_SPECIES_END + 1):
        entry = entries.get((species, 0))
        if entry is None:
            continue
        base = gen7_battle_base(species)
        asset_index = int(entry["assetIndex"])
        flags = int(entry["flags"])
        for side, side_flag, compact_offsets, wide_offsets, palette_offset in (
            ("front", PWAN_CONFIG_FRONT_FLAG, (0, 1), (2, 3), 18),
            ("back", PWAN_CONFIG_BACK_FLAG, (9, 10), (11, 12), 19),
        ):
            if not (flags & side_flag):
                continue
            pwan_path = pwan_source / f"{asset_index}_{side}.pwan"
            if not pwan_path.exists():
                continue
            compact_paths = [
                battle_vfs / str(base + offset)
                for offset in compact_offsets
                if nonempty_path(battle_vfs / str(base + offset))
            ]
            wide_paths = [
                battle_vfs / str(base + offset)
                for offset in wide_offsets
                if nonempty_path(battle_vfs / str(base + offset))
            ]
            nclr_path = battle_vfs / str(base + palette_offset)
            if not compact_paths or not wide_paths or not nclr_path.exists():
                continue
            pwan_fingerprint = file_fingerprint(pwan_path)
            palette_fingerprint = output_fingerprint(nclr_path)
            pixels = pwan_first_pixels(pwan_path)
            pixels = remap_pixels_to_palette(
                pixels,
                pwan_palette_values(pwan_path),
                palette_from_nclr(nclr_path.read_bytes()),
            )
            compact_payload = segmented_pwan_pixels(pixels)
            wide_payload = linear_wide_pwan_pixels(pixels)
            for output_path, payload in (
                [(path, compact_payload) for path in compact_paths]
                + [(path, wide_payload) for path in wide_paths]
            ):
                key = output_path.name
                state = {
                    "compression": fallback_compression,
                    "pwan": pwan_fingerprint,
                    "palette": palette_fingerprint,
                    "output": output_fingerprint(output_path),
                }
                previous_state = previous_entries.get(key)
                should_patch = (
                    force
                    or int(key) in changed_outputs
                    or previous_state != state
                )
                if should_patch:
                    patch_jobs.append((output_path, payload, fallback_compression))
                    patched_keys.append(key)
                next_entries[key] = state

    patched = run_fallback_patch_jobs(patch_jobs, fallback_jobs)
    for key in patched_keys:
        next_entries[key]["output"] = output_fingerprint(battle_vfs / key)
    return patched, {"entries": next_entries}


def build_pwan_assets(source_root: Path, pwan_vfs: Path) -> list[dict]:
    sources = []
    config_entries = []
    asset_index = 0
    ensure_dir(pwan_vfs)
    expected_outputs = {"config.bin", "sources.json"}

    for entry in graphics_order_entries(source_root):
        if entry["type"] != "pwan":
            continue
        folder_name = entry["folder"]
        pokemon_dir = source_root / folder_name
        manifest_data = load_toml(pokemon_dir / "nns.toml")
        species = int(manifest_data["species"])
        config_path = pokemon_dir / "config.toml"
        if not config_path.exists():
            raise RuntimeError(f"{config_path}: missing PWAN config")

        config = load_toml(config_path)
        fmt = config.get("format")
        if fmt != "pwan":
            raise RuntimeError(f"{config_path}: unsupported format {fmt!r}")

        side_outputs = {}
        for side in ("front", "back"):
            side_config = config.get(side)
            if not isinstance(side_config, dict) or "source" not in side_config:
                raise RuntimeError(f"{config_path}: missing [{side}].source")
            src = pokemon_dir / side_config["source"]
            dst = pwan_vfs / f"{asset_index:03}_{side}.pwan"
            expected_outputs.add(dst.name)
            scale = float(side_config.get("scale", 1.0))
            offset_x = int(side_config.get("offset_x", 0))
            offset_y = int(side_config.get("offset_y", 0))
            source_mtime = max(src.stat().st_mtime, config_path.stat().st_mtime)
            if not dst.exists() or dst.stat().st_mtime < source_mtime:
                stats = compile_pwan(src, dst, scale=scale, offset_x=offset_x, offset_y=offset_y)
            else:
                stats = {
                    "frames": None,
                    "timeline": None,
                    "ticks": None,
                    "bytes": dst.stat().st_size,
                }
            side_outputs[side] = dst.name
            sources.append({
                "species": species,
                "folder": folder_name,
                "side": side,
                "source": str(src.relative_to(source_root)),
                "pwan": dst.name,
                "frames": stats["frames"],
                "timeline": stats["timeline"],
                "ticks": stats["ticks"],
                "bytes": stats["bytes"],
                "scale": scale,
                "offset_x": offset_x,
                "offset_y": offset_y,
            })

        config_entries.append(struct.pack("<HHHH", species, 0x0003, asset_index, asset_index))
        asset_index += 1

    for file in pwan_vfs.iterdir():
        if file.is_file() and file.name not in expected_outputs:
            file.unlink()

    header = struct.pack(
        "<IHHHHI",
        CONFIG_MAGIC,
        CONFIG_VERSION,
        len(config_entries),
        MAX_TIMELINE_ENTRIES,
        0,
        CONFIG_HEADER_SIZE,
    )
    pwan_vfs.mkdir(parents=True, exist_ok=True)
    (pwan_vfs / "config.bin").write_bytes(header + b"".join(config_entries))
    (pwan_vfs / "sources.json").write_text(json.dumps(sources, indent=2) + "\n")
    return sources


def run_stage(
    args: argparse.Namespace,
    previous_manifest: dict | None,
    config: dict,
    force_full: bool,
) -> dict:
    previous_manifest = previous_manifest or {}
    preserve_before = args.preserve_base_before if args.base_archive is not None else 0

    if force_full:
        clean_dir(args.battle_vfs)
        base_count = seed_base_archive(args.base_archive, args.battle_vfs)
    else:
        ensure_dir(args.battle_vfs)
        counts = previous_manifest.get("counts", {})
        base_count = counts.get("base_entries")
        if not isinstance(base_count, int):
            raise NeedsFullRebuild("previous manifest is missing base entry count")

    if preserve_before > base_count:
        raise RuntimeError(
            f"--preserve-base-before {preserve_before} exceeds base archive file count {base_count}"
        )

    nns_count, nns_changed, nns_manifest, nns_staged = stage_nns_archive_entries_incremental(
        args.source,
        args.battle_vfs,
        preserve_before,
        previous_manifest.get("nns", {}),
        force_full,
    )
    extra_count, extra_changed, extra_manifest, extra_staged = copy_extra_bin_entries_incremental(
        args.extra_bin_source,
        args.battle_vfs,
        nns_count,
        previous_manifest.get("extra", {}),
        force_full,
    )
    changed_outputs = nns_changed | extra_changed
    gen7_fallbacks, fallback_manifest = patch_gen7_native_fallbacks_incremental(
        args.gen7_pwan_fallback_source,
        args.battle_vfs,
        args.fallback_jobs,
        args.fallback_compression,
        previous_manifest.get("fallback", {}),
        changed_outputs,
        force_full,
    )

    (args.battle_vfs / ".arc").write_text(args.arc_text)
    if args.skip_pwan:
        if args.pwan_vfs is not None and args.pwan_vfs.exists():
            shutil.rmtree(args.pwan_vfs)
        sources = []
    else:
        if args.pwan_vfs is None:
            raise RuntimeError("--pwan-vfs is required unless --skip-pwan is set")
        ensure_dir(args.pwan_vfs)
        sources = build_pwan_assets(args.source, args.pwan_vfs)

    counts = {
        "base_entries": base_count,
        "preserved_base_entries": preserve_before,
        "nns_entries": nns_count,
        "extra_bin_entries": extra_count,
        "pwan_assets": len(sources),
    }
    manifest = {
        "config": config,
        "counts": counts,
        "nns": nns_manifest,
        "extra": extra_manifest,
        "fallback": fallback_manifest,
    }
    return {
        "manifest": manifest,
        "counts": counts,
        "nns_staged": nns_staged,
        "extra_bin_staged": extra_staged,
        "gen7_native_fallbacks": gen7_fallbacks,
        "pwan_assets": len(sources),
        "full_rebuild": force_full,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description="Build pokegra battle graphics into VFS outputs.")
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--battle-vfs", type=Path, required=True)
    parser.add_argument("--pwan-vfs", type=Path)
    parser.add_argument("--base-archive", type=Path)
    parser.add_argument("--preserve-base-before", type=int, default=0)
    parser.add_argument("--extra-bin-source", type=Path)
    parser.add_argument("--gen7-pwan-fallback-source", type=Path)
    parser.add_argument("--fallback-jobs", type=int, default=1)
    parser.add_argument("--fallback-compression", choices=("literal", "nlz11"), default="literal")
    parser.add_argument("--force-full", action="store_true")
    parser.add_argument("--skip-pwan", action="store_true")
    parser.add_argument("--arc-text", required=True)
    parser.add_argument("--stamp", type=Path, required=True)
    args = parser.parse_args()
    if args.fallback_jobs < 1:
        parser.error("--fallback-jobs must be at least 1")

    manifest_path = manifest_path_for_stamp(args.stamp)
    previous_manifest = load_incremental_manifest(manifest_path)
    config = incremental_config(args)
    force_full = args.force_full or not can_incremental_rebuild(
        previous_manifest,
        config,
        args.battle_vfs,
    )

    try:
        result = run_stage(args, previous_manifest, config, force_full)
    except NeedsFullRebuild:
        result = run_stage(args, {}, config, True)

    write_incremental_manifest(manifest_path, result["manifest"])
    counts = result["counts"]
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.write_text(
        f"base_entries={counts['base_entries']}\n"
        f"preserved_base_entries={counts['preserved_base_entries']}\n"
        f"nns_entries={counts['nns_entries']}\n"
        f"nns_entries_staged={result['nns_staged']}\n"
        f"extra_bin_entries={counts['extra_bin_entries']}\n"
        f"extra_bin_entries_staged={result['extra_bin_staged']}\n"
        f"gen7_native_fallbacks={result['gen7_native_fallbacks']}\n"
        f"gen7_native_fallback_jobs={args.fallback_jobs}\n"
        f"gen7_native_fallback_compression={args.fallback_compression}\n"
        f"full_rebuild={int(result['full_rebuild'])}\n"
        f"incremental_manifest={manifest_path}\n"
        f"pwan_assets={result['pwan_assets']}\n"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
