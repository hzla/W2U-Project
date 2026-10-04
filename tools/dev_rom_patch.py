#!/usr/bin/env python3

from __future__ import annotations

import argparse
import shutil
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

import ndspy.fnt


HEADER_FNT_OFFSET = 0x40
HEADER_FNT_LENGTH = 0x44
HEADER_FAT_OFFSET = 0x48
HEADER_FAT_LENGTH = 0x4C


@dataclass(frozen=True)
class RomTables:
    filenames: ndspy.fnt.Folder
    fat_offset: int
    fat_length: int


@dataclass(frozen=True)
class ArchivePatch:
    rom_path: str
    source: Path


class RelocationRequiredError(ValueError):
    pass


def read_u32(data: bytes | bytearray, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def write_u32(file, offset: int, value: int) -> None:
    file.seek(offset)
    file.write(struct.pack("<I", value))


def parse_archive(value: str) -> ArchivePatch:
    try:
        rom_path, source = value.split("=", 1)
    except ValueError as exc:
        raise argparse.ArgumentTypeError(
            "archive patches must use ROM_PATH=SOURCE, for example "
            "a/0/9/1=vfs/data/a/0/9/1"
        ) from exc

    rom_path = rom_path.strip().strip("/")
    if rom_path.startswith("data/"):
        rom_path = rom_path.removeprefix("data/")
    if not rom_path:
        raise argparse.ArgumentTypeError("archive ROM path is empty")
    return ArchivePatch(rom_path, Path(source))


def load_rom_tables(rom_path: Path) -> RomTables:
    with rom_path.open("rb") as file:
        header = file.read(0x200)
        if len(header) < 0x200:
            raise ValueError(f"{rom_path} is too small to be a Nintendo DS ROM")

        fnt_offset = read_u32(header, HEADER_FNT_OFFSET)
        fnt_length = read_u32(header, HEADER_FNT_LENGTH)
        fat_offset = read_u32(header, HEADER_FAT_OFFSET)
        fat_length = read_u32(header, HEADER_FAT_LENGTH)

        file.seek(fnt_offset)
        fnt_data = file.read(fnt_length)
        if len(fnt_data) != fnt_length:
            raise ValueError(f"{rom_path} ended before the filename table")

    return RomTables(ndspy.fnt.load(fnt_data), fat_offset, fat_length)


def resolve_file_id(tables: RomTables, rom_path: str) -> int:
    candidates = [rom_path.strip("/")]
    if candidates[0].startswith("data/"):
        candidates.append(candidates[0].removeprefix("data/"))
    else:
        candidates.append(f"data/{candidates[0]}")

    for candidate in candidates:
        file_id = tables.filenames.idOf(candidate)
        if file_id is not None:
            if file_id >= tables.fat_length // 8:
                raise ValueError(
                    f"{candidate} resolved to file ID {file_id}, outside FAT file count "
                    f"{tables.fat_length // 8}"
                )
            return file_id

    raise ValueError(f"could not find {rom_path!r} in the ROM filename table")


def numeric_file_key(path: Path) -> int:
    try:
        return int(path.name)
    except ValueError as exc:
        raise ValueError(f"{path} is not a numeric flat NARC member") from exc


def read_flat_archive_members(archive_dir: Path) -> list[bytes]:
    if not archive_dir.is_dir():
        raise ValueError(f"{archive_dir} is not a staged .arc directory")
    arc_meta = archive_dir / ".arc"
    if not arc_meta.is_file():
        raise ValueError(f"{archive_dir} is missing .arc metadata")

    files = [path for path in archive_dir.iterdir() if path.is_file() and path.name != ".arc"]
    files.sort(key=numeric_file_key)
    expected_names = [str(index) for index in range(len(files))]
    actual_names = [path.name for path in files]
    if actual_names != expected_names:
        raise ValueError(
            f"{archive_dir} is not a contiguous flat archive; expected members "
            f"0..{len(files) - 1}"
        )
    return [path.read_bytes() for path in files]


def pack_flat_narc(archive_dir: Path) -> bytes:
    """Pack a CTRMap flat .arc directory using the NARC shape CTRMap emits."""
    members = read_flat_archive_members(archive_dir)

    fatb = bytearray()
    fatb.extend(struct.pack("<4sII", b"BTAF", 0x0C + 8 * len(members), len(members)))

    fimg_payload = bytearray()
    for member in members:
        start = len(fimg_payload)
        fimg_payload.extend(member)
        end = len(fimg_payload)
        fatb.extend(struct.pack("<II", start, end))
        while len(fimg_payload) % 4:
            fimg_payload.append(0)

    # CTRMap writes an empty filename block with a root entries offset of 4.
    fntb = struct.pack("<4sIIHH", b"BTNF", 0x10, 4, 0, 1)
    fimg = struct.pack("<4sI", b"GMIF", len(fimg_payload) + 8) + fimg_payload

    data = bytearray(0x10)
    data.extend(fatb)
    data.extend(fntb)
    data.extend(fimg)
    struct.pack_into("<4sHHIHH", data, 0, b"NARC", 0xFFFE, 0x0100, len(data), 0x10, 3)
    return bytes(data)


def payload_for_source(source: Path) -> bytes:
    if source.is_dir():
        return pack_flat_narc(source)
    if source.is_file():
        return source.read_bytes()
    raise ValueError(f"{source} does not exist")


def read_fat_entry(file, tables: RomTables, file_id: int) -> tuple[int, int]:
    file.seek(tables.fat_offset + file_id * 8)
    entry = file.read(8)
    if len(entry) != 8:
        raise ValueError(f"FAT entry {file_id} is outside the ROM")
    return struct.unpack("<II", entry)


def replace_file_payload(
    rom_path: Path,
    tables: RomTables,
    file_id: int,
    payload: bytes,
    *,
    dry_run: bool,
) -> tuple[int, int, int, bool]:
    with rom_path.open("r+b") as file:
        start, end = read_fat_entry(file, tables, file_id)
        old_size = end - start
        if len(payload) > old_size:
            raise RelocationRequiredError(
                f"file ID {file_id} grows from {old_size} to {len(payload)} bytes; "
                "a full CTRMap ROMBuilder rebuild is required so NTR digest tables and "
                "the TWL tail can be placed after the expanded file data"
            )

        if dry_run:
            return old_size, len(payload), start, False

        file.seek(start)
        file.write(payload)
        if len(payload) < old_size:
            file.write(b"\xFF" * (old_size - len(payload)))
        write_u32(file, tables.fat_offset + file_id * 8 + 4, start + len(payload))
        return old_size, len(payload), start, False


def verify_payload(rom_path: Path, tables: RomTables, file_id: int, payload: bytes) -> None:
    with rom_path.open("rb") as file:
        start, end = read_fat_entry(file, tables, file_id)
        if end - start != len(payload):
            raise ValueError(
                f"FAT size mismatch for file ID {file_id}: expected {len(payload)}, "
                f"found {end - start}"
            )
        file.seek(start)
        actual = file.read(len(payload))
    if actual != payload:
        raise ValueError(f"verification failed for file ID {file_id}")


def main() -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Dev-only ROM file replacer for small VFS data archive edits. "
            "This patches an existing built ROM instead of invoking CTRMap ROMBuilder."
        )
    )
    parser.add_argument("--rom", type=Path, required=True, help="Existing built ROM to patch from")
    parser.add_argument("--output", type=Path, required=True, help="Patched ROM path")
    parser.add_argument(
        "--archive",
        action="append",
        type=parse_archive,
        required=True,
        help="Archive replacement as ROM_PATH=SOURCE. May be provided more than once.",
    )
    parser.add_argument("--dry-run", action="store_true", help="Validate and report without writing")
    args = parser.parse_args()

    if not args.rom.is_file():
        raise FileNotFoundError(f"{args.rom} does not exist; run one full build first")

    args.output.parent.mkdir(parents=True, exist_ok=True)
    if args.rom.resolve(strict=True) != args.output.resolve(strict=False) and not args.dry_run:
        shutil.copy2(args.rom, args.output)

    patch_rom = args.rom if args.dry_run else args.output
    tables = load_rom_tables(patch_rom)

    for archive in args.archive:
        payload = payload_for_source(archive.source)
        file_id = resolve_file_id(tables, archive.rom_path)
        old_size, new_size, offset, appended = replace_file_payload(
            patch_rom,
            tables,
            file_id,
            payload,
            dry_run=args.dry_run,
        )
        if not args.dry_run:
            verify_payload(patch_rom, tables, file_id, payload)
        action = "append" if appended else "in-place"
        print(
            f"{archive.rom_path}: file_id={file_id} old={old_size} new={new_size} "
            f"offset=0x{offset:x} {action}"
        )

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except RelocationRequiredError as error:
        print(error, file=sys.stderr)
        raise SystemExit(75)
