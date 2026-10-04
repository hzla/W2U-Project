#!/usr/bin/env python3
"""Generate clean-IREO signatures for every B2U hook and raw anchor."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess

import ndspy.codeCompression
import ndspy.rom
import yaml


DIRECT_RE = re.compile(r"^(FULL_COPY|THUMB_BRANCH_LINK)_(\d+)_0x([0-9A-Fa-f]+)$")
OFFSET_RE = re.compile(r"^(FULL_COPY|THUMB_BRANCH_LINK)_([A-Za-z][A-Za-z0-9_]*)_0x([0-9A-Fa-f]+)$")
REPLACE_RE = re.compile(r"^THUMB_BRANCH_(?:SAFESTACK_)?([A-Za-z][A-Za-z0-9_]*)$")
PLATFORM_RE = re.compile(
    r"^#define\s+(W2U_ADDR_[A-Z0-9_]+)\s+(0x[0-9A-Fa-f]+)u?\s*$",
    re.MULTILINE,
)
ASM_LITERAL_RE = re.compile(r"=\s*(0x[0-9A-Fa-f]{7,8})")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--rom", type=Path, required=True)
    parser.add_argument("--esdb", type=Path, required=True)
    parser.add_argument("--aliases", type=Path, required=True)
    parser.add_argument("--platform-header", type=Path, required=True)
    parser.add_argument("--elf", type=Path, action="append", required=True)
    parser.add_argument("--asm", type=Path, action="append", default=[])
    parser.add_argument("--output", type=Path, required=True)
    return parser.parse_args()


def nm_symbols(elf: Path) -> list[tuple[str, int]]:
    output = subprocess.check_output(["arm-none-eabi-nm", "-S", str(elf)], text=True)
    result = []
    for line in output.splitlines():
        fields = line.split()
        if len(fields) >= 4:
            result.append((fields[3], int(fields[1], 16)))
    return result


def undefined_symbols(elf: Path) -> list[str]:
    output = subprocess.check_output(["arm-none-eabi-nm", "-u", str(elf)], text=True)
    return [line.split()[-1] for line in output.splitlines() if line.split()]


def main() -> int:
    args = parse_args()
    aliases = json.loads(args.aliases.read_text(encoding="utf-8"))
    asm_address_map = {int(source, 16): int(target, 16) for source, target in aliases["asmAddressMap"].items()}
    expected_hash = aliases["baseRomSha256"]
    actual_hash = hashlib.sha256(args.rom.read_bytes()).hexdigest()
    if actual_hash != expected_hash:
        raise SystemExit(f"clean IREO hash mismatch: expected {expected_hash}, got {actual_hash}")

    esdb = yaml.safe_load(args.esdb.read_text(encoding="utf-8"))
    segment_names = {int(row["ID"]): str(row["Name"]) for row in esdb["Segments"]}
    symbols = {row["Name"]: row for row in esdb["Symbols"]}

    rom = ndspy.rom.NintendoDSRom.fromFile(str(args.rom))
    arm9 = bytes(ndspy.codeCompression.decompress(rom.arm9))
    overlays = rom.loadArm9Overlays()

    def segment_for_address(address: int) -> str | None:
        even = address & ~1
        if rom.arm9RamAddress <= even < rom.arm9RamAddress + len(arm9):
            return "ARM9"
        for overlay_id in (165, 167, 168, 169, 207, 255, 265, 299, 302):
            overlay = overlays[overlay_id]
            if overlay.ramAddress <= even < overlay.ramAddress + overlay.ramSize:
                return str(overlay_id)
        return None

    def clean_bytes(segment: str, address: int, size: int) -> bytes:
        even = address & ~1
        if segment == "ARM9":
            offset = even - rom.arm9RamAddress
            return arm9[offset : offset + size]
        overlay = overlays[int(segment)]
        offset = even - overlay.ramAddress
        return bytes(overlay.data[offset : offset + size])

    hooks: list[dict] = []
    seen_hooks: set[tuple[str, int, str]] = set()
    for elf in args.elf:
        for name, emitted_size in nm_symbols(elf):
            if name.startswith("W2U_DISABLED_"):
                continue
            kind = None
            segment = None
            address = None
            signature_size = None
            match = DIRECT_RE.match(name)
            if match:
                kind, segment, encoded = match.groups()
                address = int(encoded, 16)
                signature_size = emitted_size if kind == "FULL_COPY" else 4
            else:
                match = OFFSET_RE.match(name)
                if match:
                    kind, base_name, encoded = match.groups()
                    base = symbols.get(base_name)
                    if not base and kind == "THUMB_BRANCH_LINK":
                        raise SystemExit(f"{name}: missing ESDB hook owner {base_name}")
                    if base:
                        segment = segment_names[int(base["Segment"])]
                        address = int(base["Address"]) + int(encoded, 16)
                        signature_size = emitted_size if kind == "FULL_COPY" else 4
                else:
                    match = REPLACE_RE.match(name)
                    if match and match.group(1) not in symbols:
                        raise SystemExit(f"{name}: missing ESDB hook owner {match.group(1)}")
                    if match and match.group(1) in symbols:
                        kind = "FUNCTION_REPLACE"
                        base = symbols[match.group(1)]
                        segment = segment_names[int(base["Segment"])]
                        address = int(base["Address"])
                        signature_size = 8
            if kind is None or segment not in {"ARM9", "165", "167", "168", "169", "207", "255", "265", "299", "302"}:
                continue
            key = (segment, int(address), kind)
            if key in seen_hooks:
                continue
            seen_hooks.add(key)
            original = clean_bytes(segment, int(address), int(signature_size))
            hooks.append(
                {
                    "module": elf.stem,
                    "symbol": name,
                    "kind": kind,
                    "segment": segment,
                    "address": f"0x{int(address):08X}",
                    "size": len(original),
                    "originalHex": original.hex(),
                    "originalSha256": hashlib.sha256(original).hexdigest(),
                }
            )

    imported_functions: dict[tuple[str, int], dict] = {}
    for elf in args.elf:
        for name in undefined_symbols(elf):
            symbol = symbols.get(name)
            if not symbol:
                # Companion W2U_* imports bind to Black2Upgrade.dll and are
                # checked against the resident core's exports at build time.
                continue
            segment = segment_names[int(symbol["Segment"])]
            address = int(symbol["Address"])
            if segment not in {"ARM9", "165", "167", "168", "169", "207", "255", "265", "299", "302"}:
                continue
            key = (segment, address)
            entry = imported_functions.get(key)
            if entry is None:
                original = clean_bytes(segment, address, 16)
                entry = {
                    "symbol": name,
                    "modules": [],
                    "segment": segment,
                    "address": f"0x{address:08X}",
                    "size": len(original),
                    "originalHex": original.hex(),
                    "originalSha256": hashlib.sha256(original).hexdigest(),
                }
                imported_functions[key] = entry
            if elf.stem not in entry["modules"]:
                entry["modules"].append(elf.stem)

    # Read only the B2 side of the platform header.
    header = args.platform_header.read_text(encoding="utf-8")
    b2_block = header.split("#if defined(W2U_TARGET_B2)", 1)[1].split("#else", 1)[0]
    raw_anchors: dict[tuple[str, int], dict] = {}
    for match in PLATFORM_RE.finditer(b2_block):
        name, raw = match.groups()
        address = int(raw, 16)
        segment = segment_for_address(address)
        entry = {
            "name": name,
            "address": f"0x{address:08X}",
            "segment": segment,
        }
        if segment:
            original = clean_bytes(segment, address, 8)
            entry.update(originalHex=original.hex(), originalSha256=hashlib.sha256(original).hexdigest())
        raw_anchors[(name, address)] = entry

    for asm in args.asm:
        for match in ASM_LITERAL_RE.finditer(asm.read_text(encoding="utf-8")):
            source_address = int(match.group(1), 16)
            address = asm_address_map.get(source_address, source_address)
            if address == source_address and 0x02010000 <= source_address < 0x02200000:
                raise SystemExit(f"unreviewed Black 2 assembly address in {asm}: {match.group(1)}")
            if address < 0x02000000:
                continue
            segment = segment_for_address(address)
            name = f"asm-call:{asm.name}:{match.group(1)}"
            entry = {"name": name, "address": f"0x{address:08X}", "segment": segment}
            if segment:
                original = clean_bytes(segment, address, 8)
                entry.update(originalHex=original.hex(), originalSha256=hashlib.sha256(original).hexdigest())
            raw_anchors[(name, address)] = entry

    result = {
        "schemaVersion": 1,
        "baseGameId": aliases["baseGameId"],
        "baseRomSha256": actual_hash,
        "runtimeAbi": aliases["runtimeAbi"],
        "expansionDataVersion": aliases["expansionDataVersion"],
        "hooks": sorted(hooks, key=lambda row: (row["segment"], row["address"], row["symbol"])),
        "importedFunctions": sorted(imported_functions.values(), key=lambda row: (row["segment"], row["address"], row["symbol"])),
        "rawAnchors": sorted(raw_anchors.values(), key=lambda row: (row["segment"] or "", row["address"], row["name"])),
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2, sort_keys=False) + "\n", encoding="utf-8")
    print(
        f"wrote {args.output}: {len(result['hooks'])} hooks, "
        f"{len(result['importedFunctions'])} imported functions, "
        f"{len(result['rawAnchors'])} raw anchors"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
