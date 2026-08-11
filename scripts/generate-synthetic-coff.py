#!/usr/bin/env python3
"""Generate audited PE-derived i386 COFF diagnostic islands for objdiff."""

from __future__ import annotations

import argparse
import csv
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import struct
import tomllib


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "config" / "synthetic-islands.toml"
TARGET_CONFIG = ROOT / "config" / "target.toml"
FUNCTIONS = ROOT / "config" / "functions.csv"
TARGET = ROOT / "resources" / "th105.exe"
IMAGE_FILE_MACHINE_I386 = 0x014C
IMAGE_REL_I386_REL32 = 0x0014
IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_ALIGN_16BYTES = 0x00500000
IMAGE_SCN_MEM_EXECUTE = 0x20000000
IMAGE_SCN_MEM_READ = 0x40000000


def file_sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def target_bytes(address: int, size: int) -> bytes:
    data = TARGET.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    sections = pe + 24 + optional_size
    rva = address - image_base
    for index in range(section_count):
        row = sections + 40 * index
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, row + 8
        )
        if virtual_address <= rva < virtual_address + max(virtual_size, raw_size):
            within = rva - virtual_address
            if within + size > max(virtual_size, raw_size):
                raise ValueError("synthetic island crosses a PE section boundary")
            raw_available = max(0, min(size, raw_size - within))
            raw = data[raw_pointer + within : raw_pointer + within + raw_available]
            if len(raw) != raw_available:
                raise ValueError("target PE raw data is truncated")
            return raw + bytes(size - raw_available)
    raise ValueError(f"address 0x{address:08X} is outside the target PE")


def repository_path(raw: str) -> Path:
    relative = Path(raw)
    if relative.is_absolute() or ".." in relative.parts:
        raise ValueError(f"island output must be repository-relative: {raw!r}")
    output = (ROOT / relative).resolve()
    output.relative_to((ROOT / "build").resolve())
    return output


def load_manifest() -> dict[str, object]:
    with MANIFEST.open("rb") as stream:
        manifest = tomllib.load(stream)
    with TARGET_CONFIG.open("rb") as stream:
        target = tomllib.load(stream)["target"]
    actual = file_sha256(TARGET)
    if manifest.get("schema_version") != 1:
        raise ValueError("synthetic-island schema_version must be 1")
    if manifest.get("target_sha256") != target["sha256"] or actual != target["sha256"]:
        raise ValueError("synthetic-island target SHA-256 attestation failed")
    islands = manifest.get("islands")
    if not isinstance(islands, dict) or not islands:
        raise ValueError("synthetic-island manifest defines no islands")
    return manifest


def coff_name(name: str, strings: bytearray) -> bytes:
    encoded = name.encode("ascii")
    if len(encoded) <= 8:
        return encoded.ljust(8, bytes(1))
    offset = 4 + len(strings)
    strings.extend(encoded + bytes(1))
    return struct.pack("<II", 0, offset)


def symbol(name: str, strings: bytearray, section: int, symbol_type: int) -> bytes:
    return (
        coff_name(name, strings)
        + struct.pack("<IhHBB", 0, section, symbol_type, 2, 0)
    )


def validate_island(name: str, island: dict[str, object]) -> dict[str, object]:
    if island.get("classification") != "synthetic_pe_derived_not_original_coff":
        raise ValueError(f"island {name} has an unsafe classification")
    address = int(str(island.get("address", "")), 0)
    size = island.get("size")
    if not isinstance(size, int) or size <= 0:
        raise ValueError(f"island {name} has invalid size")
    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        ledger = {row["address"]: row for row in csv.DictReader(stream)}
    canonical = f"0x{address:08X}"
    row = ledger.get(canonical)
    if row is None or int(row["size"]) != size:
        raise ValueError(f"island {name} disagrees with ledger boundary")
    body = target_bytes(address, size)
    relocations = island.get("relocations")
    if not isinstance(relocations, list) or not relocations:
        raise ValueError(f"island {name} has no relocations")
    seen: set[int] = set()
    checked: list[dict[str, object]] = []
    for relocation in relocations:
        if not isinstance(relocation, dict):
            raise ValueError(f"island {name} has invalid relocation")
        offset = relocation.get("offset")
        if not isinstance(offset, int) or offset <= 0 or offset + 4 > size:
            raise ValueError(f"island {name} has invalid relocation offset")
        if offset in seen:
            raise ValueError(f"island {name} repeats relocation offset {offset:#x}")
        seen.add(offset)
        if relocation.get("type") != "IMAGE_REL_I386_REL32":
            raise ValueError(f"island {name} uses unsupported relocation type")
        opcode = relocation.get("opcode")
        if not isinstance(opcode, int) or body[offset - 1] != opcode or opcode not in (0xE8, 0xE9):
            raise ValueError(f"island {name} relocation at +{offset:#x} lacks E8/E9")
        linked = bytes.fromhex(str(relocation.get("linked_hex", "")))
        if len(linked) != 4 or body[offset : offset + 4] != linked:
            raise ValueError(f"island {name} linked operand changed at +{offset:#x}")
        destination = int(str(relocation.get("destination", "")), 0)
        displacement = struct.unpack("<i", linked)[0]
        replayed_destination = address + offset + 4 + displacement
        if replayed_destination != destination:
            raise ValueError(f"island {name} REL32 equation failed at +{offset:#x}")
        symbol_name = relocation.get("symbol")
        if not isinstance(symbol_name, str) or not symbol_name:
            raise ValueError(f"island {name} relocation lacks a synthetic symbol label")
        checked.append(
            {
                "offset": offset,
                "type": relocation["type"],
                "opcode": f"0x{opcode:02X}",
                "linked_hex": linked.hex(),
                "next_ip": f"0x{address + offset + 4:08X}",
                "destination": f"0x{destination:08X}",
                "synthetic_addend": 0,
                "symbol": symbol_name,
                "evidence": relocation.get("evidence", ""),
            }
        )
    return {
        "name": name,
        "address": address,
        "size": size,
        "body": body,
        "row": row,
        "relocations": checked,
        "output": repository_path(str(island.get("output", ""))),
        "function_symbol": str(island.get("function_symbol", "")),
        "classification": island["classification"],
        "notes": island.get("notes", ""),
    }


def build_coff(validated: dict[str, object]) -> bytes:
    body = bytearray(validated["body"])
    relocations = validated["relocations"]
    strings = bytearray()
    symbols = [
        symbol(str(validated["function_symbol"]), strings, 1, 0x20),
    ]
    for relocation in relocations:
        body[relocation["offset"] : relocation["offset"] + 4] = bytes(4)
        symbols.append(symbol(str(relocation["symbol"]), strings, 0, 0x20))

    header_size = 20 + 40
    raw_pointer = header_size
    relocation_pointer = raw_pointer + len(body)
    symbol_pointer = relocation_pointer + len(relocations) * 10
    file_header = struct.pack(
        "<HHIIIHH",
        IMAGE_FILE_MACHINE_I386,
        1,
        0,
        symbol_pointer,
        len(symbols),
        0,
        0,
    )
    characteristics = (
        IMAGE_SCN_CNT_CODE
        | IMAGE_SCN_ALIGN_16BYTES
        | IMAGE_SCN_MEM_EXECUTE
        | IMAGE_SCN_MEM_READ
    )
    section_header = (
        b".text".ljust(8, bytes(1))
        + struct.pack(
            "<IIIIIIHHI",
            0,
            0,
            len(body),
            raw_pointer,
            relocation_pointer,
            0,
            len(relocations),
            0,
            characteristics,
        )
    )
    relocation_table = b"".join(
        struct.pack("<IIH", relocation["offset"], index + 1, IMAGE_REL_I386_REL32)
        for index, relocation in enumerate(relocations)
    )
    string_table = struct.pack("<I", 4 + len(strings)) + strings
    return file_header + section_header + body + relocation_table + b"".join(symbols) + string_table


def replay_link(validated: dict[str, object], coff: bytes) -> bytes:
    body = bytearray(coff[60 : 60 + validated["size"]])
    address = validated["address"]
    for relocation in validated["relocations"]:
        offset = relocation["offset"]
        displacement = int(relocation["destination"], 0) - (address + offset + 4)
        struct.pack_into("<i", body, offset, displacement)
    return bytes(body)


def generate(validated: dict[str, object]) -> Path:
    coff = build_coff(validated)
    replayed = replay_link(validated, coff)
    if replayed != validated["body"]:
        raise ValueError(f"island {validated['name']} does not relink to exact target bytes")
    output = validated["output"]
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(coff)
    provenance = {
        "schema_version": 1,
        "classification": validated["classification"],
        "warning": "PE-derived diagnostic island; not original COFF, TU, or LTCG evidence",
        "island": validated["name"],
        "target_sha256": file_sha256(TARGET),
        "address": f"0x{validated['address']:08X}",
        "size": validated["size"],
        "span_end": validated["row"]["span_end"],
        "target_code_sha256": hashlib.sha256(validated["body"]).hexdigest(),
        "synthetic_coff_sha256": hashlib.sha256(coff).hexdigest(),
        "generator_sha256": file_sha256(Path(__file__).resolve()),
        "manifest_sha256": file_sha256(MANIFEST),
        "relocations": validated["relocations"],
        "link_replay_exact": True,
        "notes": validated["notes"],
        "generated_utc": datetime.now(timezone.utc).isoformat().replace("+00:00", "Z"),
    }
    output.with_suffix(output.suffix + ".provenance.json").write_text(
        json.dumps(provenance, indent=2) + "\n", encoding="utf-8"
    )
    return output


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--island")
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        manifest = load_manifest()
        islands = manifest["islands"]
        selected = [args.island] if args.island else list(islands)
        reports = []
        for name in selected:
            if name not in islands:
                raise ValueError(f"unknown synthetic island: {name}")
            validated = validate_island(name, islands[name])
            report = {
                "island": name,
                "classification": validated["classification"],
                "address": f"0x{validated['address']:08X}",
                "size": validated["size"],
                "relocations": len(validated["relocations"]),
            }
            if not args.check:
                output = generate(validated)
                report["output"] = str(output.relative_to(ROOT))
                report["coff_sha256"] = file_sha256(output)
                report["link_replay_exact"] = True
            reports.append(report)
        if args.json:
            print(json.dumps({"ok": True, "islands": reports}, indent=2))
        else:
            for report in reports:
                action = "validated" if args.check else f"generated {report['output']}"
                print(
                    f"{report['island']}: {action}; {report['size']} bytes, "
                    f"{report['relocations']} REL32 relocations"
                )
        return 0
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as error:
        if args.json:
            print(json.dumps({"ok": False, "error": str(error)}, indent=2))
        else:
            print(f"error: {error}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
