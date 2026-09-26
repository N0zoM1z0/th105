#!/usr/bin/env python3
"""Generate and validate the current TH105 1.06a function-origin census.

Rules are deliberately fail-closed: each current-target rule fixes its selected
candidate count and byte total, may attest target strings/opcodes/names, and is
applied only after the target SHA-256 matches config/target.toml.
"""
from __future__ import annotations

import argparse
from collections import Counter
import csv
import hashlib
import importlib.util
import os
from pathlib import Path
import struct
import subprocess
import tomllib

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config/functions.csv"
RULES = ROOT / "config/function-origin-rules.toml"
OUTPUT = ROOT / "config/function-origins.csv"
TARGET = ROOT / "resources/th105.exe"
XIPH_ANCHORS = ROOT / "config/xiph-origin-anchors.toml"
FIELDS = ["address", "origin", "subsystem", "disposition", "confidence", "evidence_id"]
ORIGINS = {"authored_game", "compiler_generated", "vc8_runtime", "third_party", "import_thunk", "unknown"}
DISPOSITIONS = {"authored", "exclude", "review"}
CONFIDENCES = {"observed", "inferred", "hypothesized", "unknown"}
AUTHORED_MODULES = {"assets", "audio", "battle", "characters", "config", "engine", "input", "network", "platform", "render", "script", "ui"}


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(newline="", encoding="utf-8") as stream:
        return list(csv.DictReader(stream))


def target_manifest() -> dict[str, object]:
    with (ROOT / "config/target.toml").open("rb") as stream:
        return tomllib.load(stream)


def attest_target(rules_doc: dict[str, object]) -> bytes:
    data = TARGET.read_bytes()
    configured = str(target_manifest()["target"]["sha256"])
    rules_hash = str(rules_doc["target_sha256"])
    actual = hashlib.sha256(data).hexdigest()
    if actual != configured or rules_hash != configured:
        raise ValueError(f"target identity mismatch: actual={actual} config={configured} rules={rules_hash}")
    return data


def pe_reader(data: bytes):
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    opt_size = struct.unpack_from("<H", data, pe + 20)[0]
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    section_base = pe + 24 + opt_size
    sections = []
    for index in range(count):
        off = section_base + index * 40
        virtual_size, rva, raw_size, raw_ptr = struct.unpack_from("<IIII", data, off + 8)
        sections.append((rva, virtual_size, raw_size, raw_ptr))

    def read(address: int, size: int) -> bytes:
        rva = address - image_base
        for section_rva, _virtual_size, raw_size, raw_ptr in sections:
            if section_rva <= rva and rva + size <= section_rva + raw_size:
                offset = raw_ptr + rva - section_rva
                return data[offset : offset + size]
        raise ValueError(f"0x{address:08X}: requested bytes are not initialized PE raw data")

    return read


def pe_raw_section_name(data: bytes, address: int) -> str:
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    opt_size = struct.unpack_from("<H", data, pe + 20)[0]
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    for index in range(count):
        off = pe + 24 + opt_size + index * 40
        name = data[off : off + 8].split(b"\x00", 1)[0].decode("ascii")
        rva = struct.unpack_from("<I", data, off + 12)[0]
        raw_size = struct.unpack_from("<I", data, off + 16)[0]
        if image_base + rva <= address < image_base + rva + raw_size:
            return name
    raise ValueError(f"0x{address:08X}: no initialized PE section")


def pe_import_names_by_iat(data: bytes, read_pe) -> dict[int, tuple[str, str]]:
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    optional = pe + 24
    if struct.unpack_from("<H", data, optional)[0] != 0x10B:
        raise ValueError("target import parser requires PE32")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    import_rva = struct.unpack_from("<I", data, optional + 96 + 8)[0]

    def c_string(address: int) -> str:
        raw = bytearray()
        for offset in range(256):
            byte = read_pe(address + offset, 1)[0]
            if byte == 0:
                return raw.decode("ascii")
            raw.append(byte)
        raise ValueError(f"unterminated PE import name at 0x{address:08X}")

    imports: dict[int, tuple[str, str]] = {}
    for descriptor_index in range(256):
        descriptor = read_pe(image_base + import_rva + 20 * descriptor_index, 20)
        original_thunk, _timestamp, _forwarder, name_rva, first_thunk = struct.unpack(
            "<IIIII", descriptor
        )
        if not any((original_thunk, name_rva, first_thunk)):
            return imports
        dll = c_string(image_base + name_rva)
        for index in range(4096):
            name_pointer = struct.unpack(
                "<I", read_pe(image_base + (original_thunk or first_thunk) + index * 4, 4)
            )[0]
            if name_pointer == 0:
                break
            name = (
                f"#{name_pointer & 0xFFFF}"
                if name_pointer & 0x80000000
                else c_string(image_base + name_pointer + 2)
            )
            imports[image_base + first_thunk + index * 4] = (dll, name)
        else:
            raise ValueError(f"PE import thunk list for {dll} did not terminate")
    raise ValueError("PE import descriptor list did not terminate")




def load_msvc_archive_module():
    extractor_path = ROOT / "scripts/extract-msvc-library-object.py"
    spec = importlib.util.spec_from_file_location("th105_msvc_extract", extractor_path)
    if spec is None or spec.loader is None:
        raise ValueError("cannot load pinned MSVC archive extractor")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def msvc_runtime_function_text(
    obj: bytes, symbol: str
) -> tuple[bytes, list[tuple[int, int, str]]]:
    """Return one exact COFF function extent plus relocations from a VC8 archive member."""
    if len(obj) < 20 or struct.unpack_from("<H", obj, 0)[0] != 0x014C:
        raise ValueError("VC8 runtime member is not an i386 COFF object")
    section_count = struct.unpack_from("<H", obj, 2)[0]
    symbol_pointer, symbol_count = struct.unpack_from("<II", obj, 8)
    optional_header_size = struct.unpack_from("<H", obj, 16)[0]
    section_table = 20 + optional_header_size
    string_table = symbol_pointer + symbol_count * 18

    sections: list[tuple[bytes, int, int, int, int]] = []
    for index in range(section_count):
        offset = section_table + index * 40
        raw_name = obj[offset : offset + 8]
        if raw_name.startswith(b"/"):
            try:
                start = string_table + int(raw_name[1:].rstrip(b"\0"))
                end = obj.find(b"\0", start)
                name = obj[start:end] if end >= 0 else raw_name.rstrip(b"\0")
            except ValueError:
                name = raw_name.rstrip(b"\0")
        else:
            name = raw_name.rstrip(b"\0")
        raw_size, raw_pointer = struct.unpack_from("<II", obj, offset + 16)
        relocation_pointer = struct.unpack_from("<I", obj, offset + 24)[0]
        relocation_count = struct.unpack_from("<H", obj, offset + 32)[0]
        sections.append((name, raw_size, raw_pointer, relocation_pointer, relocation_count))

    def symbol_name(offset: int) -> str:
        raw = obj[offset : offset + 8]
        if raw[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw, 4)[0]
            start = string_table + name_offset
            if not string_table + 4 <= start < len(obj):
                return ""
            end = obj.find(b"\0", start)
            if end < 0:
                end = len(obj)
            return obj[start:end].decode("ascii", errors="replace")
        return raw.rstrip(b"\0").decode("ascii", errors="replace")

    symbols: dict[int, tuple[str, int, int]] = {}
    functions: list[tuple[str, int, int, int]] = []
    index = 0
    while index < symbol_count:
        offset = symbol_pointer + index * 18
        name = symbol_name(offset)
        value = struct.unpack_from("<I", obj, offset + 8)[0]
        section_number = struct.unpack_from("<h", obj, offset + 12)[0]
        symbol_type = struct.unpack_from("<H", obj, offset + 14)[0]
        storage_class = obj[offset + 16]
        auxiliary_count = obj[offset + 17]
        symbols[index] = (name, value, section_number)
        total_size = 0
        if auxiliary_count and offset + 40 <= len(obj):
            total_size = struct.unpack_from("<I", obj, offset + 22)[0]
        if (
            0 < section_number <= section_count
            and symbol_type & 0x20
            and storage_class in (2, 3, 105)
        ):
            functions.append((name, value, section_number, total_size))
        index += 1 + auxiliary_count

    matches = [entry for entry in functions if entry[0] == symbol]
    if len(matches) != 1:
        raise ValueError(f"{symbol}: expected one VC8 archive function, found {len(matches)}")
    name, value, section_number, total_size = matches[0]
    section_name, raw_size, raw_pointer, relocation_pointer, relocation_count = sections[section_number - 1]
    if not section_name.startswith(b".text"):
        raise ValueError(f"{symbol}: unexpected section {section_name!r}")
    if not total_size:
        later = sorted(
            item[1]
            for item in functions
            if item[2] == section_number and item[1] > value
        )
        total_size = (later[0] if later else raw_size) - value
    if total_size <= 0 or value + total_size > raw_size:
        raise ValueError(f"{symbol}: invalid COFF function extent {total_size}")
    body = obj[raw_pointer + value : raw_pointer + value + total_size]
    relocations: list[tuple[int, int, str]] = []
    for relocation_index in range(relocation_count):
        offset = relocation_pointer + relocation_index * 10
        virtual_address, symbol_index, relocation_type = struct.unpack_from("<IIH", obj, offset)
        function_offset = virtual_address - value
        if 0 <= function_offset < total_size:
            relocations.append(
                (function_offset, relocation_type, symbols.get(symbol_index, ("?", 0, 0))[0])
            )
    return body, relocations


def replayed_msvc_relocation_target(code: bytes, base: int, offset: int, kind: int) -> int:
    if kind == 0x0006:
        return struct.unpack_from("<I", code, offset)[0]
    if kind == 0x0014:
        return base + offset + 4 + struct.unpack_from("<i", code, offset)[0]
    raise ValueError(f"unsupported VC8 relocation kind {kind:#x}")


def load_msvc_archive_symbols() -> set[str]:
    """Return all defined COFF symbols from the SHA-pinned VC8 SP1 archives."""
    module = load_msvc_archive_module()
    symbols: set[str] = set()
    for _key, (filename, expected_hash) in module.LIBRARIES.items():
        archive_path = ROOT / ".tools/msvc80-sp1/lib" / filename
        archive = archive_path.read_bytes()
        actual_hash = hashlib.sha256(archive).hexdigest()
        if actual_hash != expected_hash:
            raise ValueError(f"{filename} SHA-256 mismatch: {actual_hash} != {expected_hash}")
        for _member_name, obj in module.archive_members(archive):
            if len(obj) < 20 or struct.unpack_from("<H", obj, 0)[0] != 0x014C:
                continue
            symbol_ptr, symbol_count = struct.unpack_from("<II", obj, 8)
            string_table = symbol_ptr + symbol_count * 18
            if not symbol_ptr or string_table + 4 > len(obj):
                continue

            def symbol_name(offset: int) -> str:
                raw = obj[offset : offset + 8]
                if raw[:4] == b"\0\0\0\0":
                    name_offset = struct.unpack_from("<I", raw, 4)[0]
                    start = string_table + name_offset
                    if not string_table + 4 <= start < len(obj):
                        return ""
                    end = obj.find(b"\0", start)
                    if end < 0:
                        end = len(obj)
                    return obj[start:end].decode("ascii", errors="replace")
                return raw.rstrip(b"\0").decode("ascii", errors="replace")

            index = 0
            while index < symbol_count:
                offset = symbol_ptr + index * 18
                if offset + 18 > len(obj):
                    break
                name = symbol_name(offset)
                section = struct.unpack_from("<h", obj, offset + 12)[0]
                aux_count = obj[offset + 17]
                if section > 0 and name and not name.startswith("."):
                    symbols.add(name)
                index += 1 + aux_count
    return symbols


def msvc_symbol_aliases(name: str) -> set[str]:
    # GNU/COFF tooling and IDA differ by one C-name leading underscore.
    return {name, name[1:] if name.startswith("_") else "_" + name}


def load_xiph_sdk_module():
    path = ROOT / "scripts/fetch-xiph-sdk-object.py"
    spec = importlib.util.spec_from_file_location("th105_xiph_sdk", path)
    if spec is None or spec.loader is None:
        raise ValueError("cannot load pinned Xiph SDK extractor")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def xiph_rel32_operand_kind(code: bytes, field_offset: int) -> str | None:
    """Return the narrowly supported x86 instruction owning one REL32 field."""
    if field_offset >= 1 and code[field_offset - 1] in (0xE8, 0xE9):
        return "call" if code[field_offset - 1] == 0xE8 else "jmp"
    if (
        field_offset >= 2
        and code[field_offset - 2] == 0x0F
        and 0x80 <= code[field_offset - 1] <= 0x8F
    ):
        return "jcc"
    return None


def xiph_relocated_text(data: bytes, wanted_symbol: str) -> tuple[bytes, list[tuple[int, int]]]:
    """Return one COMDAT body and its supported link relocations."""
    if len(data) < 20 or struct.unpack_from("<H", data, 0)[0] != 0x014C:
        raise ValueError("Xiph SDK member is not an i386 COFF object")
    section_count = struct.unpack_from("<H", data, 2)[0]
    symbol_pointer, symbol_count = struct.unpack_from("<II", data, 8)
    optional_size = struct.unpack_from("<H", data, 16)[0]
    section_base = 20 + optional_size
    string_table = symbol_pointer + symbol_count * 18
    sections: list[dict[str, object]] = []
    for index in range(section_count):
        offset = section_base + index * 40
        raw_size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        reloc_pointer = struct.unpack_from("<I", data, offset + 24)[0]
        reloc_count = struct.unpack_from("<H", data, offset + 32)[0]
        characteristics = struct.unpack_from("<I", data, offset + 36)[0]
        sections.append({
            "name": data[offset : offset + 8].rstrip(b"\0"),
            "raw_size": raw_size,
            "raw_pointer": raw_pointer,
            "reloc_pointer": reloc_pointer,
            "reloc_count": reloc_count,
            "characteristics": characteristics,
            "functions": [],
        })

    def symbol_name(offset: int) -> str:
        raw = data[offset : offset + 8]
        if raw[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw, 4)[0]
            start = string_table + name_offset
            end = data.find(b"\0", start)
            if end < 0:
                raise ValueError("unterminated Xiph COFF symbol name")
            return data[start:end].decode("ascii", errors="replace")
        return raw.rstrip(b"\0").decode("ascii", errors="replace")

    index = 0
    while index < symbol_count:
        offset = symbol_pointer + index * 18
        name = symbol_name(offset)
        value = struct.unpack_from("<I", data, offset + 8)[0]
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        symbol_type = struct.unpack_from("<H", data, offset + 14)[0]
        storage_class = data[offset + 16]
        auxiliary = data[offset + 17]
        if (
            0 < section_number <= section_count
            and value == 0
            and symbol_type == 0x20
            and storage_class in (2, 3)
        ):
            sections[section_number - 1]["functions"].append(name)
        index += 1 + auxiliary

    matches: list[tuple[bytes, list[tuple[int, int]]]] = []
    for section in sections:
        if section["name"] != b".text" or section["functions"] != [wanted_symbol]:
            continue
        if int(section["characteristics"]) & 0x01000000:
            raise ValueError(f"Xiph symbol {wanted_symbol} uses relocation overflow")
        start = int(section["raw_pointer"])
        size = int(section["raw_size"])
        body = data[start : start + size]
        relocations: list[tuple[int, int]] = []
        for reloc_index in range(int(section["reloc_count"])):
            offset = int(section["reloc_pointer"]) + reloc_index * 10
            field_offset, _symbol_index, relocation_type = struct.unpack_from(
                "<IIH", data, offset
            )
            if relocation_type not in (0x0006, 0x0014):
                raise ValueError(
                    f"Xiph symbol {wanted_symbol} has unsupported relocation {relocation_type:#x}"
                )
            if field_offset + 4 > size:
                raise ValueError(
                    f"Xiph symbol {wanted_symbol} relocation crosses its COMDAT body"
                )
            relocations.append((field_offset, relocation_type))
        matches.append((body, relocations))
    if len(matches) != 1:
        raise ValueError(
            f"Xiph symbol {wanted_symbol} has {len(matches)} function COMDAT bodies"
        )
    return matches[0]


def xiph_relocation_free_text(data: bytes, wanted_symbol: str) -> bytes:
    """Return one zero-relocation COMDAT body for a named i386 COFF function."""
    if len(data) < 20 or struct.unpack_from("<H", data, 0)[0] != 0x014C:
        raise ValueError("Xiph SDK member is not an i386 COFF object")
    section_count = struct.unpack_from("<H", data, 2)[0]
    symbol_pointer, symbol_count = struct.unpack_from("<II", data, 8)
    optional_size = struct.unpack_from("<H", data, 16)[0]
    section_base = 20 + optional_size
    string_table = symbol_pointer + symbol_count * 18
    sections: list[dict[str, object]] = []
    for index in range(section_count):
        offset = section_base + index * 40
        raw_size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        reloc_count = struct.unpack_from("<H", data, offset + 32)[0]
        sections.append({
            "name": data[offset : offset + 8].rstrip(b"\0"),
            "raw_size": raw_size,
            "raw_pointer": raw_pointer,
            "reloc_count": reloc_count,
            "functions": [],
        })

    def symbol_name(offset: int) -> str:
        raw = data[offset : offset + 8]
        if raw[:4] == b"\0\0\0\0":
            name_offset = struct.unpack_from("<I", raw, 4)[0]
            start = string_table + name_offset
            end = data.find(b"\0", start)
            if end < 0:
                raise ValueError("unterminated Xiph COFF symbol name")
            return data[start:end].decode("ascii", errors="replace")
        return raw.rstrip(b"\0").decode("ascii", errors="replace")

    index = 0
    while index < symbol_count:
        offset = symbol_pointer + index * 18
        name = symbol_name(offset)
        value = struct.unpack_from("<I", data, offset + 8)[0]
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        symbol_type = struct.unpack_from("<H", data, offset + 14)[0]
        storage_class = data[offset + 16]
        auxiliary = data[offset + 17]
        if (
            0 < section_number <= section_count
            and value == 0
            and symbol_type == 0x20
            and storage_class in (2, 3)
        ):
            sections[section_number - 1]["functions"].append(name)
        index += 1 + auxiliary

    matches = []
    for section in sections:
        if (
            section["name"] == b".text"
            and section["reloc_count"] == 0
            and section["functions"] == [wanted_symbol]
        ):
            start = int(section["raw_pointer"])
            size = int(section["raw_size"])
            matches.append(data[start : start + size])
    if len(matches) != 1:
        raise ValueError(
            f"Xiph symbol {wanted_symbol} has {len(matches)} zero-relocation COMDAT bodies"
        )
    return matches[0]


def validate_xiph_anchor_evidence(
    rule: dict[str, object],
    selected: list[dict[str, str]],
    rows: list[dict[str, str]],
    read_pe,
) -> list[str]:
    errors: list[str] = []
    anchor_path = ROOT / str(rule["xiph_anchor_file"])
    anchors_doc = tomllib.loads(anchor_path.read_text(encoding="utf-8"))
    configured_hash = str(target_manifest()["target"]["sha256"])
    if str(anchors_doc.get("target_sha256")) != configured_hash:
        errors.append(f"{rule['id']}: Xiph anchor target SHA-256 differs from canonical target")
        return errors
    module = load_xiph_sdk_module()
    if str(anchors_doc.get("sdk_sha256")) != module.ARCHIVE_SHA256:
        errors.append(f"{rule['id']}: Xiph anchor SDK SHA-256 differs from pinned extractor")
        return errors
    cache = ROOT / ".tools/upstream/OggVorbis-win32sdk-1.0.1.zip"
    if not cache.is_file():
        errors.append(f"{rule['id']}: pinned Xiph SDK cache is missing: {cache}")
        return errors
    sdk = cache.read_bytes()
    if hashlib.sha256(sdk).hexdigest() != module.ARCHIVE_SHA256:
        errors.append(f"{rule['id']}: cached Xiph SDK SHA-256 mismatch")
        return errors

    anchors = anchors_doc.get("anchors", [])
    selected_addresses = {row["address"] for row in selected}
    anchor_addresses = {str(anchor["address"]) for anchor in anchors}
    if selected_addresses != anchor_addresses:
        errors.append(f"{rule['id']}: selected addresses differ from Xiph anchor file")
        return errors
    row_by_address = {row["address"]: row for row in rows}
    object_cache: dict[tuple[str, str], bytes] = {}
    candidate_bytes: dict[str, bytes] = {}
    for row in rows:
        try:
            candidate_bytes[row["address"]] = read_pe(
                int(row["address"], 0), int(row["size"], 0)
            )
        except ValueError:
            pass

    padding = {0x00, 0x90, 0xCC}
    for anchor in anchors:
        address = str(anchor["address"])
        row = row_by_address.get(address)
        if row is None:
            errors.append(f"{rule['id']}: missing Xiph candidate {address}")
            continue
        size = int(anchor["size"])
        if int(row["size"], 0) != size:
            errors.append(
                f"{rule['id']}: {address} size {row['size']} differs from anchor {size}"
            )
            continue
        component = str(anchor["component"])
        object_name = str(anchor["object"])
        key = (component, object_name)
        if key not in object_cache:
            object_cache[key] = module.extract_object(sdk, component, object_name)
        try:
            body = xiph_relocation_free_text(object_cache[key], str(anchor["symbol"]))
        except ValueError as exc:
            errors.append(f"{rule['id']}: {address}: {exc}")
            continue
        if len(body) != int(anchor["section_size"]):
            errors.append(f"{rule['id']}: {address} Xiph section size changed")
            continue
        actual = candidate_bytes.get(address)
        if actual != body[:size] or any(byte not in padding for byte in body[size:]):
            errors.append(f"{rule['id']}: {address} no longer raw-matches Xiph anchor")
            continue
        candidates = []
        for other in rows:
            other_body = candidate_bytes.get(other["address"])
            if other_body is None or len(other_body) > len(body):
                continue
            if other_body != body[: len(other_body)]:
                continue
            if any(byte not in padding for byte in body[len(other_body) :]):
                continue
            candidates.append(other["address"])
        if candidates != [address]:
            errors.append(
                f"{rule['id']}: {address} Xiph anchor is not inventory-unique: {candidates}"
            )
    return errors

def validate_xiph_relocated_anchor_evidence(
    rule: dict[str, object],
    selected: list[dict[str, str]],
    rows: list[dict[str, str]],
    read_pe,
) -> list[str]:
    """Validate link-agnostic exact Xiph fingerprints against current 1.06a."""
    errors: list[str] = []
    anchor_path = ROOT / str(rule["xiph_relocated_anchor_file"])
    anchors_doc = tomllib.loads(anchor_path.read_text(encoding="utf-8"))
    configured_hash = str(target_manifest()["target"]["sha256"])
    if str(anchors_doc.get("target_sha256")) != configured_hash:
        return [f"{rule['id']}: relocated Xiph anchor target SHA-256 differs from canonical target"]
    module = load_xiph_sdk_module()
    if str(anchors_doc.get("sdk_sha256")) != module.ARCHIVE_SHA256:
        return [f"{rule['id']}: relocated Xiph anchor SDK SHA-256 differs from pinned extractor"]
    cache = ROOT / ".tools/upstream/OggVorbis-win32sdk-1.0.1.zip"
    if not cache.is_file():
        return [f"{rule['id']}: pinned Xiph SDK cache is missing: {cache}"]
    sdk = cache.read_bytes()
    if hashlib.sha256(sdk).hexdigest() != module.ARCHIVE_SHA256:
        return [f"{rule['id']}: cached Xiph SDK SHA-256 mismatch"]

    anchors = anchors_doc.get("anchors", [])
    selected_addresses = {row["address"] for row in selected}
    anchor_addresses = {str(anchor["address"]) for anchor in anchors}
    if selected_addresses != anchor_addresses:
        return [f"{rule['id']}: selected addresses differ from relocated Xiph anchor file"]
    min_coverage = float(anchors_doc.get("min_nonreloc_coverage", 0.0))
    min_nonreloc = int(anchors_doc.get("min_nonreloc_bytes", 0))
    if not 0.0 < min_coverage <= 1.0 or min_nonreloc < 1:
        return [f"{rule['id']}: invalid relocated Xiph evidence thresholds"]

    row_by_address = {row["address"]: row for row in rows}
    object_cache: dict[tuple[str, str], bytes] = {}
    candidate_bytes: dict[str, bytes] = {}
    for row in rows:
        try:
            candidate_bytes[row["address"]] = read_pe(
                int(row["address"], 0), int(row["size"], 0)
            )
        except ValueError:
            pass
    padding = {0x00, 0x90, 0xCC}

    equivalence_groups: dict[str, set[str]] = {}
    group_shapes: dict[str, tuple[int, str, str, str]] = {}
    for anchor in anchors:
        group = str(anchor.get("equivalence_group", "")).strip()
        if not group:
            continue
        address = str(anchor["address"])
        shape = (
            int(anchor["size"]),
            str(anchor["component"]),
            str(anchor["object"]),
            str(anchor["symbol"]),
        )
        previous_shape = group_shapes.setdefault(group, shape)
        if previous_shape != shape:
            errors.append(
                f"{rule['id']}: relocated Xiph equivalence group {group!r} mixes witness shapes"
            )
        equivalence_groups.setdefault(group, set()).add(address)

    def candidate_matches(body: bytes, relocations: list[tuple[int, int]], candidate: bytes) -> bool:
        size = len(candidate)
        if size > len(body):
            return False
        wild: set[int] = set()
        for field_offset, relocation_type in relocations:
            if field_offset + 4 > size:
                return False
            if relocation_type == 0x0014 and xiph_rel32_operand_kind(body, field_offset) is None:
                return False
            wild.update(range(field_offset, field_offset + 4))
        nonreloc = sum(index not in wild for index in range(size))
        if nonreloc < min_nonreloc or nonreloc / size < min_coverage:
            return False
        if any(
            index not in wild and candidate[index] != body[index]
            for index in range(size)
        ):
            return False
        # No relocation may hide bytes after the candidate boundary; the COMDAT
        # tail must be ordinary compiler/linker alignment only.
        if any(byte not in padding for byte in body[size:]):
            return False
        return True

    for anchor in anchors:
        address = str(anchor["address"])
        row = row_by_address.get(address)
        if row is None:
            errors.append(f"{rule['id']}: missing relocated Xiph candidate {address}")
            continue
        size = int(anchor["size"])
        if int(row["size"], 0) != size:
            errors.append(f"{rule['id']}: {address} size differs from relocated Xiph anchor")
            continue
        key = (str(anchor["component"]), str(anchor["object"]))
        if key not in object_cache:
            object_cache[key] = module.extract_object(sdk, *key)
        try:
            body, relocations = xiph_relocated_text(
                object_cache[key], str(anchor["symbol"])
            )
        except ValueError as exc:
            errors.append(f"{rule['id']}: {address}: {exc}")
            continue
        if not relocations:
            errors.append(f"{rule['id']}: {address} relocated anchor has no relocations")
            continue
        if len(body) != int(anchor["section_size"]):
            errors.append(f"{rule['id']}: {address} Xiph section size changed")
            continue
        actual = candidate_bytes.get(address)
        if actual is None or not candidate_matches(body, relocations, actual):
            errors.append(f"{rule['id']}: {address} no longer matches strict relocated Xiph fingerprint")
            continue
        candidates = [
            other["address"]
            for other in rows
            if (candidate := candidate_bytes.get(other["address"])) is not None
            and candidate_matches(body, relocations, candidate)
        ]
        group = str(anchor.get("equivalence_group", "")).strip()
        expected_candidates = sorted(equivalence_groups[group]) if group else [address]
        if sorted(candidates) != expected_candidates:
            label = f"equivalence group {group!r}" if group else "unique anchor"
            errors.append(
                f"{rule['id']}: {address} relocated Xiph {label} mismatch: "
                f"got {sorted(candidates)}, expected {expected_candidates}"
            )
    return errors


def validate_msvc_runtime_anchor_evidence(
    rule: dict[str, object],
    selected: list[dict[str, str]],
    rows: list[dict[str, str]],
    read_pe,
) -> list[str]:
    """Validate strict relocation-masked fingerprints from SHA-pinned VC8 runtime archives."""
    errors: list[str] = []
    anchor_path = ROOT / str(rule["msvc_runtime_anchor_file"])
    anchors_doc = tomllib.loads(anchor_path.read_text(encoding="utf-8"))
    configured_hash = str(target_manifest()["target"]["sha256"])
    if str(anchors_doc.get("target_sha256")) != configured_hash:
        return [f"{rule['id']}: MSVC runtime anchor target SHA-256 differs from canonical target"]

    anchors = anchors_doc.get("anchors", [])
    selected_addresses = {row["address"] for row in selected}
    anchor_addresses = {str(anchor["address"]) for anchor in anchors}
    if selected_addresses != anchor_addresses:
        return [f"{rule['id']}: selected addresses differ from MSVC runtime anchor file"]
    min_coverage = float(anchors_doc.get("min_nonreloc_coverage", 0.0))
    min_nonreloc = int(anchors_doc.get("min_nonreloc_bytes", 0))
    if not 0.0 < min_coverage <= 1.0 or min_nonreloc < 1:
        return [f"{rule['id']}: invalid MSVC runtime evidence thresholds"]

    module = load_msvc_archive_module()
    members: dict[str, dict[str, bytes]] = {}
    for library, (filename, expected_hash) in module.LIBRARIES.items():
        archive_path = ROOT / ".tools/msvc80-sp1/lib" / filename
        if not archive_path.is_file():
            return [f"{rule['id']}: pinned VC8 archive is missing: {archive_path}"]
        archive = archive_path.read_bytes()
        actual_hash = hashlib.sha256(archive).hexdigest()
        if actual_hash != expected_hash:
            return [f"{rule['id']}: {filename} SHA-256 mismatch"]
        members[library] = {name: body for name, body in module.archive_members(archive)}

    row_by_address = {row["address"]: row for row in rows}
    candidate_bytes: dict[str, bytes] = {}
    for row in rows:
        try:
            candidate_bytes[row["address"]] = read_pe(
                int(row["address"], 0), int(row["size"], 0)
            )
        except ValueError:
            pass

    fingerprint_cache: dict[tuple[str, str, str], tuple[bytes, list[tuple[int, int, str]]]] = {}
    for anchor in anchors:
        address = str(anchor["address"])
        row = row_by_address.get(address)
        if row is None:
            errors.append(f"{rule['id']}: missing MSVC runtime candidate {address}")
            continue
        size = int(anchor["size"])
        if int(row["size"], 0) != size:
            errors.append(f"{rule['id']}: {address} size differs from MSVC runtime anchor")
            continue
        library = str(anchor["library"])
        object_name = str(anchor["object"]).replace("\\", "/")
        symbol = str(anchor["symbol"])
        key = (library, object_name, symbol)
        if key not in fingerprint_cache:
            archive_members = members.get(library)
            if archive_members is None:
                errors.append(f"{rule['id']}: unknown pinned VC8 archive {library}")
                continue
            obj = archive_members.get(object_name)
            if obj is None:
                errors.append(f"{rule['id']}: missing VC8 archive member {library}/{object_name}")
                continue
            try:
                fingerprint_cache[key] = msvc_runtime_function_text(obj, symbol)
            except ValueError as exc:
                errors.append(f"{rule['id']}: {address}: {exc}")
                continue
        body, relocations = fingerprint_cache[key]
        if len(body) != size:
            errors.append(
                f"{rule['id']}: {address} VC8 archive function extent changed: {len(body)} != {size}"
            )
            continue
        wild: set[int] = set()
        invalid_relocation = False
        for field_offset, relocation_type, relocation_name in relocations:
            if field_offset + 4 > size or relocation_type not in (0x0006, 0x0014):
                errors.append(
                    f"{rule['id']}: {address} unsupported VC8 relocation {relocation_type:#x} "
                    f"at +{field_offset:#x} for {relocation_name}"
                )
                invalid_relocation = True
                continue
            if relocation_type == 0x0014 and xiph_rel32_operand_kind(body, field_offset) is None:
                errors.append(
                    f"{rule['id']}: {address} REL32 at +{field_offset:#x} is not CALL/JMP/Jcc"
                )
                invalid_relocation = True
            wild.update(range(field_offset, field_offset + 4))
        if invalid_relocation:
            continue
        nonreloc = size - len(wild)
        if nonreloc < min_nonreloc or nonreloc / size < min_coverage:
            errors.append(f"{rule['id']}: {address} MSVC runtime fingerprint coverage is too weak")
            continue
        actual = candidate_bytes.get(address)
        if actual is None or any(
            index not in wild and actual[index] != body[index]
            for index in range(size)
        ):
            errors.append(f"{rule['id']}: {address} no longer matches MSVC runtime fingerprint")
            continue
        expected_relocations = anchor.get("relocation_targets")
        if expected_relocations is not None:
            expected = sorted(
                (
                    int(item["offset"]), int(str(item["type"]), 0),
                     str(item["symbol"]), int(str(item["target"]), 0))
                for item in expected_relocations
            )
            observed = sorted(
                (
                    offset, kind, name,
                     replayed_msvc_relocation_target(actual, int(address, 0), offset, kind))
                for offset, kind, name in relocations
            )
            if expected != observed:
                errors.append(
                    f"{rule['id']}: {address} VC8 relocation symbols or target addresses differ"
                )
                continue
        candidates = [
            other["address"]
            for other in rows
            if int(other["size"], 0) == size
            and (candidate := candidate_bytes.get(other["address"])) is not None
            and all(index in wild or candidate[index] == body[index] for index in range(size))
        ]
        expected_hits = sorted(str(value) for value in anchor.get("inventory_hits", [address]))
        if sorted(candidates) != expected_hits:
            errors.append(
                f"{rule['id']}: {address} MSVC runtime full-inventory hit set changed: "
                f"got {sorted(candidates)}, expected {expected_hits}"
            )
    return errors


def load_retained_rank_module():
    path = ROOT / "scripts/rank_retained_exact.py"
    spec = importlib.util.spec_from_file_location("th105_retained_rank", path)
    if spec is None or spec.loader is None:
        raise ValueError("cannot load retained-source COFF helper")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def validate_vc8_generated_anchor_evidence(
    rule: dict[str, object],
    selected: list[dict[str, str]],
    rows: list[dict[str, str]],
    read_pe,
) -> list[str]:
    """Rebuild pinned VC8 template COMDATs and prove unique current fingerprints."""
    errors: list[str] = []
    anchor_path = ROOT / str(rule["vc8_generated_anchor_file"])
    anchors_doc = tomllib.loads(anchor_path.read_text(encoding="utf-8"))
    configured_hash = str(target_manifest()["target"]["sha256"])
    if str(anchors_doc.get("target_sha256")) != configured_hash:
        return [f"{rule['id']}: VC8 generated anchor target SHA-256 differs from canonical target"]

    compiler_root = Path(
        os.environ.get("TH105_MSVC8_ROOT", str(ROOT / ".tools" / "msvc80-sp1"))
    )
    compiler = compiler_root / "bin" / "cl.exe"
    if not compiler.is_file():
        return [f"{rule['id']}: pinned VC8 compiler is missing: {compiler}"]
    compiler_hash = hashlib.sha256(compiler.read_bytes()).hexdigest()
    if compiler_hash != str(anchors_doc.get("compiler_sha256")):
        return [f"{rule['id']}: VC8 compiler SHA-256 differs from anchor manifest"]

    anchors = anchors_doc.get("anchors", [])
    selected_addresses = {row["address"] for row in selected}
    anchor_addresses = {str(anchor["address"]) for anchor in anchors}
    if selected_addresses != anchor_addresses:
        return [f"{rule['id']}: selected addresses differ from VC8 generated anchor file"]

    source = ROOT / str(anchors_doc["source"])
    if not source.is_file():
        return [f"{rule['id']}: VC8 generated anchor source is missing: {source}"]
    object_path = ROOT / "build" / "origin-anchors" / f"{anchor_path.stem}.obj"
    object_path.parent.mkdir(parents=True, exist_ok=True)
    env = os.environ.copy()
    env["TH105_ENABLE_GS"] = "1" if bool(anchors_doc.get("enable_gs")) else "0"
    proc = subprocess.run(
        [str(ROOT / "scripts" / "compile-unit.sh"), str(source), str(object_path)],
        cwd=ROOT,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if proc.returncode != 0:
        return [f"{rule['id']}: VC8 generated anchor source failed to compile: {proc.stdout.strip()}"]

    min_coverage = float(anchors_doc.get("min_nonreloc_coverage", 0.0))
    min_nonreloc = int(anchors_doc.get("min_nonreloc_bytes", 0))
    if not 0.0 < min_coverage <= 1.0 or min_nonreloc < 1:
        return [f"{rule['id']}: invalid VC8 generated anchor evidence thresholds"]

    rank = load_retained_rank_module()
    row_by_address = {row["address"]: row for row in rows}
    candidate_bytes: dict[str, bytes] = {}
    for row in rows:
        try:
            candidate_bytes[row["address"]] = read_pe(
                int(row["address"], 0), int(row["size"], 0)
            )
        except ValueError:
            pass

    equivalence_groups: dict[str, set[str]] = {}
    group_shapes: dict[str, tuple[int, str]] = {}
    for anchor_row in anchors:
        group = str(anchor_row.get("equivalence_group", "")).strip()
        if not group:
            continue
        address = str(anchor_row["address"])
        shape = (int(anchor_row["size"]), str(anchor_row["symbol"]))
        previous_shape = group_shapes.setdefault(group, shape)
        if previous_shape != shape:
            errors.append(
                f"{rule['id']}: generated equivalence group {group!r} mixes symbols/sizes"
            )
        equivalence_groups.setdefault(group, set()).add(address)

    for anchor_row in anchors:
        address = str(anchor_row["address"])
        row = row_by_address.get(address)
        if row is None:
            errors.append(f"{rule['id']}: missing VC8 generated candidate {address}")
            continue
        size = int(anchor_row["size"])
        if int(row["size"], 0) != size:
            errors.append(f"{rule['id']}: {address} size differs from VC8 generated anchor")
            continue
        expected_address = int(address, 0)
        for pointer_text in anchor_row.get("pointer_slots", []):
            try:
                pointer_address = int(str(pointer_text), 0)
                pointer_value = struct.unpack("<I", read_pe(pointer_address, 4))[0]
            except (ValueError, struct.error) as exc:
                errors.append(
                    f"{rule['id']}: {address} invalid generated pointer witness {pointer_text!r}: {exc}"
                )
                continue
            if pointer_value != expected_address:
                errors.append(
                    f"{rule['id']}: {address} pointer witness 0x{pointer_address:08X} contains "
                    f"0x{pointer_value:08X}, expected 0x{expected_address:08X}"
                )

        symbol = str(anchor_row["symbol"])
        try:
            _name, body, wild, relocations = rank.read_coff_function(
                object_path, symbol, size
            )
            max_tail = int(anchors_doc.get("max_alignment_tail", 0))
            allowed_tail = set(bytes.fromhex(str(anchors_doc.get("alignment_tail_hex", ""))))
            final_tail = b""
            saw_end = False
            for extra in range(1, max_tail + 2):
                try:
                    _extended_name, extended, _extended_wild, extended_relocations = (
                        rank.read_coff_function(object_path, symbol, size + extra)
                    )
                except ValueError as exc:
                    if "exceeds section tail" not in str(exc):
                        raise
                    saw_end = True
                    break
                final_tail = extended[size:]
                if any(offset >= size for offset, _kind, _symbol in extended_relocations):
                    raise ValueError("generated COMDAT alignment tail contains a relocation")
            if not saw_end:
                raise ValueError("generated COMDAT exceeds permitted alignment tail")
            if final_tail and (not allowed_tail or any(byte not in allowed_tail for byte in final_tail)):
                raise ValueError(
                    f"generated COMDAT has non-allowlisted alignment tail {final_tail.hex()}"
                )
        except ValueError as exc:
            errors.append(f"{rule['id']}: {address}: {exc}")
            continue

        expected_rel32: dict[str, int] = {}
        for mapping in anchor_row.get("rel32_targets", []):
            text = str(mapping)
            symbol_name, separator, target_text = text.rpartition("=")
            if not separator or not symbol_name or not target_text:
                errors.append(
                    f"{rule['id']}: {address} has invalid generated REL32 target mapping {text!r}"
                )
                continue
            try:
                expected_rel32[symbol_name] = int(target_text, 0)
            except ValueError:
                errors.append(
                    f"{rule['id']}: {address} has invalid generated REL32 target address {target_text!r}"
                )

        rel32_offsets: dict[str, list[int]] = {}
        for field_offset, relocation_type, relocation_name in relocations:
            if relocation_type not in (0x0006, 0x0014):
                errors.append(
                    f"{rule['id']}: {address} generated symbol has unsupported relocation "
                    f"{relocation_type:#x} for {relocation_name}"
                )
            if relocation_type == 0x0014:
                rel32_offsets.setdefault(relocation_name, []).append(field_offset)
                if xiph_rel32_operand_kind(body, field_offset) is None:
                    errors.append(
                        f"{rule['id']}: {address} REL32 at +{field_offset:#x} is not CALL/JMP/Jcc"
                    )
        if expected_rel32:
            if set(rel32_offsets) != set(expected_rel32):
                errors.append(
                    f"{rule['id']}: {address} generated REL32 symbols differ: "
                    f"got {sorted(rel32_offsets)}, expected {sorted(expected_rel32)}"
                )
            for relocation_name, offsets in rel32_offsets.items():
                if len(offsets) != 1:
                    errors.append(
                        f"{rule['id']}: {address} generated REL32 symbol {relocation_name!r} "
                        f"occurs {len(offsets)} times, expected exactly once"
                    )
        nonreloc = size - len(wild)
        if nonreloc < min_nonreloc or nonreloc / size < min_coverage:
            errors.append(f"{rule['id']}: {address} generated fingerprint coverage is too weak")
            continue

        actual = candidate_bytes.get(address)
        if actual is None or any(
            index not in wild and actual[index] != body[index]
            for index in range(size)
        ):
            errors.append(f"{rule['id']}: {address} no longer matches generated VC8 fingerprint")
            continue

        rel32_expectations: list[tuple[int, int, str]] = []
        for relocation_name, expected_target in expected_rel32.items():
            offsets = rel32_offsets.get(relocation_name, [])
            if len(offsets) != 1:
                continue
            field_offset = offsets[0]
            displacement = struct.unpack_from("<i", actual, field_offset)[0]
            actual_target = int(address, 0) + field_offset + 4 + displacement
            if actual_target != expected_target:
                errors.append(
                    f"{rule['id']}: {address} REL32 {relocation_name!r} targets "
                    f"0x{actual_target:08X}, expected 0x{expected_target:08X}"
                )
            rel32_expectations.append((field_offset, expected_target, relocation_name))

        candidates = []
        for other in rows:
            other_body = candidate_bytes.get(other["address"])
            if other_body is None or len(other_body) != size:
                continue
            if not all(
                index in wild or other_body[index] == body[index]
                for index in range(size)
            ):
                continue
            other_address = int(other["address"], 0)
            if any(
                other_address + field_offset + 4
                + struct.unpack_from("<i", other_body, field_offset)[0]
                != expected_target
                for field_offset, expected_target, _relocation_name in rel32_expectations
            ):
                continue
            candidates.append(other["address"])
        group = str(anchor_row.get("equivalence_group", "")).strip()
        expected_candidates = (
            sorted(equivalence_groups[group]) if group else [address]
        )
        if sorted(candidates) != expected_candidates:
            label = f"equivalence group {group!r}" if group else "unique anchor"
            errors.append(
                f"{rule['id']}: {address} generated VC8 {label} mismatch: "
                f"got {sorted(candidates)}, expected {expected_candidates}"
            )
    return errors


def baseline(row: dict[str, str]) -> dict[str, str]:
    if row["status"] == "matching":
        if row["module"] not in AUTHORED_MODULES:
            raise ValueError(f"{row['address']}: matching function lacks authored module")
        return {"address": row["address"], "origin": "authored_game", "subsystem": row["module"], "disposition": "authored", "confidence": "observed", "evidence_id": "canonical-exact-authored"}
    return {"address": row["address"], "origin": "unknown", "subsystem": row["module"], "disposition": "review", "confidence": "unknown", "evidence_id": "ida-1.06a-initial-inventory"}


def select(rule: dict[str, object], rows: list[dict[str, str]], msvc_symbols: set[str] | None = None) -> list[dict[str, str]]:
    explicit = {str(value).upper() for value in rule.get("addresses", [])}
    anchor_manifest = (
        rule.get("xiph_anchor_file")
        or rule.get("xiph_relocated_anchor_file")
        or rule.get("vc8_generated_anchor_file")
        or rule.get("msvc_runtime_anchor_file")
        or rule.get("pointer_anchor_file")
    )
    if anchor_manifest:
        anchor_doc = tomllib.loads(
            (ROOT / str(anchor_manifest)).read_text(encoding="utf-8")
        )
        explicit = {str(anchor["address"]).upper() for anchor in anchor_doc.get("anchors", [])}
    start = int(str(rule["start"]), 0) if "start" in rule else None
    end = int(str(rule["end"]), 0) if "end" in rule else None
    selected = []
    for row in rows:
        address = int(row["address"], 0)
        if explicit and row["address"].upper() not in explicit:
            continue
        if rule.get("skip_matching") and row["status"] == "matching":
            continue
        if start is not None and not (start <= address <= end):
            continue
        if rule.get("msvc_archive_defined_symbol"):
            if msvc_symbols is None:
                raise ValueError(f"{rule['id']}: MSVC archive symbols were not loaded")
            prefixes = tuple(str(value) for value in rule.get("exclude_name_prefixes", []))
            name = row["current_name"]
            if not name or (prefixes and name.startswith(prefixes)):
                continue
            if not any(alias in msvc_symbols for alias in msvc_symbol_aliases(name)):
                continue
        selected.append(row)
    return selected


def validate_pointer_anchor_evidence(
    rule: dict[str, object],
    selected: list[dict[str, str]],
    rows: list[dict[str, str]],
    read_pe,
) -> list[str]:
    """Replay target-owned vtable/function pointer witnesses fail-closed."""
    errors: list[str] = []
    rule_id = str(rule["id"])
    anchor_path = ROOT / str(rule["pointer_anchor_file"])
    anchors_doc = tomllib.loads(anchor_path.read_text(encoding="utf-8"))
    configured_hash = str(target_manifest()["target"]["sha256"])
    if str(anchors_doc.get("target_sha256")) != configured_hash:
        return [f"{rule_id}: pointer anchor target SHA-256 differs from canonical target"]

    anchors = anchors_doc.get("anchors", [])
    row_by_address = {row["address"]: row for row in rows}
    selected_addresses = {row["address"] for row in selected}
    anchor_addresses = {str(anchor["address"]) for anchor in anchors}
    expected_selected = anchor_addresses
    if rule.get("skip_matching"):
        expected_selected = {
            address
            for address in anchor_addresses
            if row_by_address.get(address, {}).get("status") != "matching"
        }
    if selected_addresses != expected_selected:
        errors.append(f"{rule_id}: selected addresses differ from active pointer anchors")

    seen_slots: dict[int, str] = {}
    owner_bases: dict[str, int] = {}
    for anchor in anchors:
        address = str(anchor["address"])
        row = row_by_address.get(address)
        if row is None:
            errors.append(f"{rule_id}: missing pointer-owned candidate {address}")
            continue
        size = int(anchor["size"])
        if int(row["size"], 0) != size:
            errors.append(f"{rule_id}: {address} size differs from pointer anchor")
        slots = anchor.get("pointer_slots", [])
        if not slots:
            errors.append(f"{rule_id}: {address} has no pointer-slot witness")
            continue
        expected = int(address, 0)
        for slot in slots:
            slot_address = int(str(slot["address"]), 0)
            owner = str(slot.get("owner", "")).strip()
            if not owner:
                errors.append(f"{rule_id}: {address} pointer slot 0x{slot_address:08X} lacks owner")
                continue
            try:
                slot_offset = int(str(slot["slot_offset"]), 0)
            except (KeyError, ValueError):
                errors.append(f"{rule_id}: {address} pointer slot 0x{slot_address:08X} has invalid slot_offset")
                continue
            if slot_offset < 0 or slot_offset & 3:
                errors.append(f"{rule_id}: {address} pointer slot 0x{slot_address:08X} has unaligned slot_offset")
            base = slot_address - slot_offset
            previous_base = owner_bases.setdefault(owner, base)
            if previous_base != base:
                errors.append(
                    f"{rule_id}: owner {owner!r} has inconsistent primary-vtable bases "
                    f"0x{previous_base:08X} and 0x{base:08X}"
                )
            previous_owner = seen_slots.setdefault(slot_address, address)
            if previous_owner != address:
                errors.append(
                    f"{rule_id}: pointer slot 0x{slot_address:08X} is claimed by both "
                    f"{previous_owner} and {address}"
                )
            try:
                actual = struct.unpack("<I", read_pe(slot_address, 4))[0]
            except ValueError as exc:
                errors.append(f"{rule_id}: {exc}")
                continue
            if actual != expected:
                errors.append(
                    f"{rule_id}: pointer slot 0x{slot_address:08X} contains "
                    f"0x{actual:08X}, expected {address}"
                )
    return errors


def atexit_registration_error(callback: dict[str, object], read_pe) -> str | None:
    address = int(str(callback["address"]), 0)
    register_site = int(str(callback["register_site"]), 0)
    atexit_site = int(str(callback["atexit_site"]), 0)
    gap = bytes.fromhex(str(callback["gap_hex"]))
    if len(gap) > 64 or atexit_site != register_site + 5 + len(gap):
        return "registration interval differs"
    try:
        pushed = read_pe(register_site, 5)
        actual_gap = read_pe(register_site + 5, len(gap)) if gap else b""
        call = read_pe(atexit_site, 5)
    except ValueError as exc:
        return str(exc)
    call_target = atexit_site + 5 + struct.unpack_from("<i", call, 1)[0]
    if (
        pushed[0] != 0x68 or struct.unpack_from("<I", pushed, 1)[0] != address
        or actual_gap != gap
        or call[0] != 0xE8 or call_target != 0x0068AF1E
    ):
        return "PUSH-to-_atexit witness differs"
    return None


def validate_rule_evidence(
    rule: dict[str, object],
    selected: list[dict[str, str]],
    rows: list[dict[str, str]],
    data: bytes,
    read_pe,
) -> list[str]:
    errors: list[str] = []
    rule_id = str(rule["id"])
    expected_names = [str(value) for value in rule.get("expected_names", [])]
    if expected_names:
        actual = [row["current_name"] for row in selected]
        if actual != expected_names:
            errors.append(f"{rule_id}: current names differ: got {actual!r}")
    prefix = bytes.fromhex(str(rule.get("opcode_prefix_hex", "")))
    if prefix:
        for row in selected:
            try:
                actual = read_pe(int(row["address"], 0), len(prefix))
            except ValueError as exc:
                errors.append(f"{rule_id}: {exc}")
                continue
            if actual != prefix:
                errors.append(f"{rule_id}: {row['address']} opcode {actual.hex()} != {prefix.hex()}")
    for text in rule.get("required_target_strings", []):
        encoded = str(text).encode("ascii")
        if encoded not in data:
            errors.append(f"{rule_id}: target string missing: {text!r}")
    for check in rule.get("required_dword_values", []):
        address = int(str(check["address"]), 0)
        expected = int(str(check["value"]), 0)
        try:
            actual = struct.unpack("<I", read_pe(address, 4))[0]
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            continue
        if actual != expected:
            errors.append(
                f"{rule_id}: dword 0x{address:08X} is 0x{actual:08X}, "
                f"expected 0x{expected:08X}"
            )
    row_by_address = {row["address"].upper(): row for row in rows}
    selected_addresses = {row["address"].upper() for row in selected}
    msvc_setters = rule.get("required_msvc_short_setters", [])
    if msvc_setters and (
        len(msvc_setters) != len(selected_addresses)
        or {str(item["address"]).upper() for item in msvc_setters} != selected_addresses
    ):
        errors.append(f"{rule_id}: VC8 short-setter witnesses do not cover selected candidates exactly")
    if msvc_setters:
        extractor = load_msvc_archive_module()
        filename, expected_archive_hash = extractor.LIBRARIES["libcmt"]
        archive = (ROOT / ".tools/msvc80-sp1/lib" / filename).read_bytes()
        if hashlib.sha256(archive).hexdigest() != expected_archive_hash:
            errors.append(f"{rule_id}: pinned VC8 libcmt archive hash differs")
            members = {}
        else:
            members = {name: body for name, body in extractor.archive_members(archive)}
    for item in msvc_setters:
        address = int(str(item["address"]), 0)
        key = f"0x{address:08X}".upper()
        consumer = int(str(item["consumer"]), 0)
        consumer_key = f"0x{consumer:08X}".upper()
        consumer_site = int(str(item["consumer_site"]), 0)
        target_global = int(str(item["global"]), 0)
        if (
            key not in selected_addresses
            or int(row_by_address[key]["size"], 0) != 10
            or consumer_key not in row_by_address
        ):
            errors.append(f"{rule_id}: VC8 short setter 0x{address:08X} has wrong selection or consumer")
            continue
        consumer_size = int(row_by_address[consumer_key]["size"], 0)
        if not consumer <= consumer_site <= consumer + consumer_size - 4:
            errors.append(f"{rule_id}: VC8 short setter 0x{address:08X} has out-of-body consumer site")
            continue
        try:
            member = members[str(item["object"])]
            target = read_pe(address, 10)
            consumer_body = read_pe(consumer, consumer_size)
            consumed_global = struct.unpack("<I", read_pe(consumer_site, 4))[0]
            source, relocations = msvc_runtime_function_text(member, str(item["symbol"]))
        except (KeyError, ValueError, struct.error) as exc:
            errors.append(f"{rule_id}: VC8 short setter 0x{address:08X}: {exc}")
            continue
        if (
            hashlib.sha256(member).hexdigest() != item["object_sha256"]
            or len(source) != 10
            or source[:5] != b"\x8B\x44\x24\x04\xA3"
            or source[9:] != b"\xC3"
            or relocations != [(5, 0x0006, item["relocation_symbol"])]
            or target[:5] != source[:5]
            or target[9:] != source[9:]
            or hashlib.sha256(target).hexdigest() != item["sha256"]
            or struct.unpack_from("<I", target, 5)[0] != target_global
            or consumed_global != target_global
            or hashlib.sha256(consumer_body).hexdigest() != item["consumer_sha256"]
        ):
            errors.append(f"{rule_id}: VC8 short setter 0x{address:08X} COFF/consumer replay differs")
    adjustor_thunks = rule.get("required_rtti_adjustor_thunks", [])
    if adjustor_thunks and (
        len(adjustor_thunks) != len(selected_addresses)
        or {str(thunk["address"]).upper() for thunk in adjustor_thunks} != selected_addresses
    ):
        errors.append(f"{rule_id}: RTTI adjustor witnesses do not cover selected candidates exactly")
    for thunk in adjustor_thunks:
        address = int(str(thunk["address"]), 0)
        slot = int(str(thunk["slot"]), 0)
        col_slot = int(str(thunk["col_slot"]), 0)
        expected_col = int(str(thunk["col"]), 0)
        expected_type = int(str(thunk["type_descriptor"]), 0)
        expected_target = int(str(thunk["target"]), 0)
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != 8:
            errors.append(f"{rule_id}: RTTI adjustor 0x{address:08X} is not an eight-byte selected candidate")
            continue
        if f"0x{expected_target:08X}".upper() not in row_by_address:
            errors.append(f"{rule_id}: RTTI adjustor 0x{address:08X} target is not a candidate")
            continue
        if slot % 4 or col_slot % 4 or not 4 <= slot - col_slot <= 12:
            errors.append(f"{rule_id}: RTTI adjustor 0x{address:08X} has invalid vtable slot spacing")
            continue
        try:
            if any(pe_raw_section_name(data, pointer) != ".rdata" for pointer in (slot, col_slot, expected_col)):
                raise ValueError("vtable or RTTI locator is outside .rdata")
            code = read_pe(address, 8)
            pointed = struct.unpack("<I", read_pe(slot, 4))[0]
            vtable_is_text = all(
                pe_raw_section_name(
                    data, struct.unpack("<I", read_pe(pointer, 4))[0]
                ) == ".text"
                for pointer in range(col_slot + 4, slot + 4, 4)
            )
            col = struct.unpack("<I", read_pe(col_slot, 4))[0]
            signature, offset, cd_offset, type_descriptor, _hierarchy = struct.unpack(
                "<IIIII", read_pe(col, 20)
            )
            type_name = read_pe(type_descriptor + 8, 192).split(b"\x00", 1)[0]
        except (ValueError, struct.error) as exc:
            errors.append(f"{rule_id}: RTTI adjustor 0x{address:08X}: {exc}")
            continue
        target = address + 8 + struct.unpack_from("<i", code, 4)[0]
        if (
            code[:2] != b"\x83\xE9"
            or code[3] != 0xE9
            or code[2] != offset
            or target != expected_target
            or pointed != address
            or not vtable_is_text
            or col != expected_col
            or signature != 0
            or cd_offset != 0
            or type_descriptor != expected_type
            or not type_name.startswith((b".?AU", b".?AV"))
            or b"exception_detail@boost@@" not in type_name
        ):
            errors.append(f"{rule_id}: RTTI adjustor 0x{address:08X} code/vtable/Boost RTTI differs")
    deleting_dtors = rule.get("required_rtti_deleting_dtors", [])
    if deleting_dtors and (
        len(deleting_dtors) != len(selected_addresses)
        or {str(dtor["address"]).upper() for dtor in deleting_dtors} != selected_addresses
    ):
        errors.append(f"{rule_id}: RTTI deleting-destructor witnesses do not cover selected candidates exactly")
    for dtor in deleting_dtors:
        address = int(str(dtor["address"]), 0)
        size = int(dtor["size"])
        slot = int(str(dtor["slot"]), 0)
        expected_col = int(str(dtor["col"]), 0)
        expected_type = int(str(dtor["type_descriptor"]), 0)
        destructor_site = int(str(dtor["destructor_site"]), 0)
        destructor = int(str(dtor["destructor"]), 0)
        free_site = int(str(dtor["free_site"]), 0)
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != size:
            errors.append(f"{rule_id}: RTTI deleting destructor 0x{address:08X} has wrong selection or size")
            continue
        if (
            size not in (30, 57)
            or not address <= destructor_site <= address + size - 5
            or not destructor_site < free_site <= address + size - 5
            or f"0x{destructor:08X}".upper() not in row_by_address
        ):
            errors.append(f"{rule_id}: RTTI deleting destructor 0x{address:08X} has invalid call sites")
            continue
        try:
            if any(pe_raw_section_name(data, pointer) != ".rdata" for pointer in (slot, expected_col)):
                raise ValueError("vtable slot or RTTI locator is outside .rdata")
            body = read_pe(address, size)
            pointed = struct.unpack("<I", read_pe(slot, 4))[0]
            col = struct.unpack("<I", read_pe(slot - 4, 4))[0]
            signature, offset, cd_offset, type_descriptor, _hierarchy = struct.unpack(
                "<IIIII", read_pe(col, 20)
            )
            type_name = read_pe(type_descriptor + 8, 192).split(b"\x00", 1)[0]
            first_call = read_pe(destructor_site, 5)
            free_call = read_pe(free_site, 5)
        except (ValueError, struct.error) as exc:
            errors.append(f"{rule_id}: RTTI deleting destructor 0x{address:08X}: {exc}")
            continue
        first_target = destructor_site + 5 + struct.unpack_from("<i", first_call, 1)[0]
        free_target = free_site + 5 + struct.unpack_from("<i", free_call, 1)[0]
        type_fragment = str(dtor.get("type_name_contains", "exception_detail@boost@@")).encode("ascii")
        if (
            hashlib.sha256(body).hexdigest() != dtor["sha256"]
            or body[:3] != b"\x56\x8B\xF1"
            or b"\xF6\x44\x24\x08\x01" not in body
            or body[-3:] != b"\xC2\x04\x00"
            or pointed != address
            or col != expected_col
            or signature != 0
            or offset != 0
            or cd_offset != 0
            or type_descriptor != expected_type
            or not type_name.startswith((b".?AU", b".?AV"))
            or type_fragment not in type_name
            or first_call[0] != 0xE8
            or first_target != destructor
            or free_call[0] != 0xE8
            or free_target != 0x006898EA
        ):
            errors.append(f"{rule_id}: RTTI deleting destructor 0x{address:08X} body/vtable/calls differ")
    inline_dtors = rule.get("required_rtti_inline_deleting_dtors", [])
    if inline_dtors and (
        len(inline_dtors) != len(selected_addresses)
        or {str(dtor["address"]).upper() for dtor in inline_dtors} != selected_addresses
    ):
        errors.append(f"{rule_id}: inline deleting-destructor witnesses do not cover selected candidates exactly")
    for dtor in inline_dtors:
        address = int(str(dtor["address"]), 0)
        size = int(dtor["size"])
        slot = int(str(dtor["slot"]), 0)
        col_slot = int(str(dtor["col_slot"]), 0)
        expected_col = int(str(dtor["col"]), 0)
        expected_type = int(str(dtor["type_descriptor"]), 0)
        expected_vptr = int(str(dtor["vptr"]), 0)
        free_site = int(str(dtor["free_site"]), 0)
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != size:
            errors.append(f"{rule_id}: inline deleting destructor 0x{address:08X} has wrong selection or size")
            continue
        if size not in (31, 38) or not address <= free_site <= address + size - 5:
            errors.append(f"{rule_id}: inline deleting destructor 0x{address:08X} has invalid free site")
            continue
        try:
            if any(pe_raw_section_name(data, pointer) != ".rdata" for pointer in (slot, col_slot, expected_col)):
                raise ValueError("vtable slot or RTTI locator is outside .rdata")
            if not col_slot < slot or (slot - col_slot) % 4 or slot - col_slot > 16:
                raise ValueError("vtable slot is not near its RTTI locator")
            body = read_pe(address, size)
            pointed = struct.unpack("<I", read_pe(slot, 4))[0]
            col = struct.unpack("<I", read_pe(col_slot, 4))[0]
            intervening = [
                struct.unpack("<I", read_pe(pointer, 4))[0]
                for pointer in range(col_slot + 4, slot, 4)
            ]
            intervening_in_text = all(
                pe_raw_section_name(data, pointer) == ".text" for pointer in intervening
            )
            signature, offset, cd_offset, type_descriptor, _hierarchy = struct.unpack(
                "<IIIII", read_pe(col, 20)
            )
            type_name = read_pe(type_descriptor + 8, 192).split(b"\x00", 1)[0]
            free_call = read_pe(free_site, 5)
        except (ValueError, struct.error) as exc:
            errors.append(f"{rule_id}: inline deleting destructor 0x{address:08X}: {exc}")
            continue
        free_target = free_site + 5 + struct.unpack_from("<i", free_call, 1)[0]
        type_fragment = str(dtor["type_name_contains"]).encode("ascii")
        branch_offset = 21 if size == 38 else 14
        if (
            hashlib.sha256(body).hexdigest() != dtor["sha256"]
            or body[:8] != b"\xF6\x44\x24\x04\x01\x56\x8B\xF1"
            or body[-6:] != b"\x8B\xC6\x5E\xC2\x04\x00"
            or body[branch_offset : branch_offset + 2] != b"\x74\x09"
            or struct.pack("<I", expected_vptr) not in body
            or pointed != address
            or col != expected_col
            or not intervening_in_text
            or signature != 0
            or offset != 0
            or cd_offset != 0
            or type_descriptor != expected_type
            or not type_name.startswith((b".?AU", b".?AV"))
            or type_fragment not in type_name
            or free_call[0] != 0xE8
            or free_target != 0x006898EA
        ):
            errors.append(f"{rule_id}: inline deleting destructor 0x{address:08X} body/vtable/call differs")
    copy_helpers = rule.get("required_rtti_copy_helpers", [])
    if copy_helpers and (
        len(copy_helpers) != len(selected_addresses)
        or {str(item["address"]).upper() for item in copy_helpers} != selected_addresses
    ):
        errors.append(f"{rule_id}: RTTI copy-helper witnesses do not cover selected candidates exactly")
    for item in copy_helpers:
        address = int(str(item["address"]), 0)
        size = int(item["size"])
        key = f"0x{address:08X}".upper()
        handler = int(str(item["handler"]), 0)
        base_site = int(str(item["base_site"]), 0)
        base_target = int(str(item["base_target"]), 0)
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != size:
            errors.append(f"{rule_id}: RTTI copy helper 0x{address:08X} has wrong selection or size")
            continue
        if not address <= base_site <= address + size - 5:
            errors.append(f"{rule_id}: RTTI copy helper 0x{address:08X} has out-of-body base call")
            continue
        try:
            body = read_pe(address, size)
            base_call = read_pe(base_site, 5)
        except ValueError as exc:
            errors.append(f"{rule_id}: RTTI copy helper 0x{address:08X}: {exc}")
            continue
        actual_base = base_site + 5 + struct.unpack_from("<i", base_call, 1)[0]
        if (
            hashlib.sha256(body).hexdigest() != item["sha256"]
            or body[:3] != b"\x6A\xFF\x68"
            or struct.unpack_from("<I", body, 3)[0] != handler
            or body[-3:] != b"\xC2\x04\x00"
            or base_call[0] != 0xE8
            or actual_base != base_target
            or len(item["vptrs"]) != 2
        ):
            errors.append(f"{rule_id}: RTTI copy helper 0x{address:08X} body/base call differs")
        expected_type = int(str(item["type_descriptor"]), 0)
        for vptr_entry in item["vptrs"]:
            vptr = int(str(vptr_entry["vptr"]), 0)
            expected_col = int(str(vptr_entry["col"]), 0)
            expected_offset = int(vptr_entry["offset"])
            try:
                if any(pe_raw_section_name(data, pointer) != ".rdata" for pointer in (vptr, expected_col)):
                    raise ValueError("vtable or RTTI locator is outside .rdata")
                col = struct.unpack("<I", read_pe(vptr - 4, 4))[0]
                signature, offset, cd_offset, descriptor, _hierarchy = struct.unpack(
                    "<IIIII", read_pe(col, 20)
                )
                type_name = read_pe(descriptor + 8, 192).split(b"\x00", 1)[0]
            except (ValueError, struct.error) as exc:
                errors.append(f"{rule_id}: RTTI copy helper 0x{address:08X} vptr: {exc}")
                continue
            if (
                struct.pack("<I", vptr) not in body
                or col != expected_col
                or signature != 0
                or offset != expected_offset
                or cd_offset != 0
                or descriptor != expected_type
                or b"error_info_injector@" not in type_name
                or b"exception_detail@boost@@" not in type_name
            ):
                errors.append(f"{rule_id}: RTTI copy helper 0x{address:08X} vptr/COL differs")
    array_adjustors = rule.get("required_array_adjustor_callbacks", [])
    if array_adjustors and (
        len(array_adjustors) != len(selected_addresses)
        or {str(item["address"]).upper() for item in array_adjustors} != selected_addresses
    ):
        errors.append(f"{rule_id}: array adjustor witnesses do not cover selected candidates exactly")
    for item in array_adjustors:
        address = int(str(item["address"]), 0)
        key = f"0x{address:08X}".upper()
        target = int(str(item["target"]), 0)
        target_key = f"0x{target:08X}".upper()
        if (
            key not in selected_addresses
            or int(row_by_address[key]["size"], 0) != 8
            or target_key not in row_by_address
            or int(row_by_address[target_key]["size"], 0) != int(item["target_size"])
        ):
            errors.append(f"{rule_id}: array adjustor 0x{address:08X} has wrong selection or target")
            continue
        try:
            body = read_pe(address, 8)
            target_body = read_pe(target, int(item["target_size"]))
        except ValueError as exc:
            errors.append(f"{rule_id}: array adjustor 0x{address:08X}: {exc}")
            continue
        actual_target = address + 8 + struct.unpack_from("<i", body, 4)[0]
        if (
            hashlib.sha256(body).hexdigest() != item["sha256"]
            or body[:2] != b"\x83\xC1"
            or body[2] != int(item["this_offset"])
            or body[3] != 0xE9
            or actual_target != target
            or hashlib.sha256(target_body).hexdigest() != item["target_sha256"]
            or len(item["array_uses"]) != 2
        ):
            errors.append(f"{rule_id}: array adjustor 0x{address:08X} body/target differs")
        for use in item["array_uses"]:
            owner = int(str(use["owner"]), 0)
            owner_key = f"0x{owner:08X}".upper()
            pointer_site = int(str(use["pointer_site"]), 0)
            call_site = int(str(use["array_call_site"]), 0)
            expected_array_target = int(str(use["array_target"]), 0)
            owner_row = row_by_address.get(owner_key)
            if (
                owner_row is None
                or owner_row["status"] != "matching"
                or not owner <= pointer_site - 1 < call_site < owner + int(owner_row["size"], 0) - 4
                or call_site - pointer_site > 32
            ):
                errors.append(f"{rule_id}: array adjustor 0x{address:08X} has invalid exact-owner use")
                continue
            try:
                push = read_pe(pointer_site - 1, 5)
                call = read_pe(call_site, 5)
            except ValueError as exc:
                errors.append(f"{rule_id}: array adjustor 0x{address:08X} use: {exc}")
                continue
            actual_array_target = call_site + 5 + struct.unpack_from("<i", call, 1)[0]
            if (
                push[0] != 0x68
                or struct.unpack_from("<I", push, 1)[0] != address
                or call[0] != 0xE8
                or actual_array_target != expected_array_target
            ):
                errors.append(f"{rule_id}: array adjustor 0x{address:08X} callback path differs")
    array_ctors = rule.get("required_array_zero_constructors", [])
    if array_ctors and (
        len(array_ctors) != len(selected_addresses)
        or {str(item["address"]).upper() for item in array_ctors} != selected_addresses
    ):
        errors.append(f"{rule_id}: array zero-constructor witnesses do not cover selected candidates exactly")
    for item in array_ctors:
        address = int(str(item["address"]), 0)
        key = f"0x{address:08X}".upper()
        dtor = int(str(item["paired_dtor"]), 0)
        dtor_key = f"0x{dtor:08X}".upper()
        owner = int(str(item["owner"]), 0)
        owner_key = f"0x{owner:08X}".upper()
        ctor_site = int(str(item["ctor_site"]), 0)
        dtor_site = int(str(item["dtor_site"]), 0)
        call_site = int(str(item["array_call_site"]), 0)
        first_field = int(item["first_field"])
        owner_row = row_by_address.get(owner_key)
        if (
            key not in selected_addresses
            or int(row_by_address[key]["size"], 0) != 17
            or dtor_key not in row_by_address
            or int(row_by_address[dtor_key]["size"], 0) != 8
            or owner_row is None
            or owner_row["status"] != "matching"
            or not owner <= dtor_site - 1 < ctor_site - 1 < call_site < owner + int(owner_row["size"], 0) - 4
            or ctor_site - dtor_site != 5
            or call_site - ctor_site > 32
        ):
            errors.append(f"{rule_id}: array constructor 0x{address:08X} has wrong selection or owner use")
            continue
        if not 4 <= first_field <= 0x70:
            errors.append(f"{rule_id}: array constructor 0x{address:08X} has invalid field offset")
            continue
        try:
            body = read_pe(address, 17)
            dtor_body = read_pe(dtor, 8)
            dtor_push = read_pe(dtor_site - 1, 5)
            ctor_push = read_pe(ctor_site - 1, 5)
            call = read_pe(call_site, 5)
        except ValueError as exc:
            errors.append(f"{rule_id}: array constructor 0x{address:08X}: {exc}")
            continue
        expected_body = b"\x8B\xC1\x33\xC9" + b"".join(
            b"\x89\x48" + bytes([first_field + 4 * index]) for index in range(4)
        ) + b"\xC3"
        array_target = call_site + 5 + struct.unpack_from("<i", call, 1)[0]
        if (
            hashlib.sha256(body).hexdigest() != item["sha256"]
            or body != expected_body
            or hashlib.sha256(dtor_body).hexdigest() != item["paired_dtor_sha256"]
            or dtor_body[:2] != b"\x83\xC1"
            or dtor_body[2] + 4 != first_field
            or dtor_push[0] != 0x68
            or struct.unpack_from("<I", dtor_push, 1)[0] != dtor
            or ctor_push[0] != 0x68
            or struct.unpack_from("<I", ctor_push, 1)[0] != address
            or call[0] != 0xE8
            or array_target != 0x0068A30C
        ):
            errors.append(f"{rule_id}: array constructor 0x{address:08X} body/callback path differs")
    cleanup_tail = rule.get("required_rtti_eh_cleanup_tail")
    if cleanup_tail:
        address = int(str(cleanup_tail["address"]), 0)
        target = int(str(cleanup_tail["target"]), 0)
        action = int(str(cleanup_tail["action"]), 0)
        vptr = int(str(cleanup_tail["vptr"]), 0)
        expected_col = int(str(cleanup_tail["col"]), 0)
        expected_type = int(str(cleanup_tail["type_descriptor"]), 0)
        key = f"0x{address:08X}".upper()
        target_key = f"0x{target:08X}".upper()
        if (
            selected_addresses != {key}
            or int(row_by_address[key]["size"], 0) != 11
            or target_key not in row_by_address
            or int(row_by_address[target_key]["size"], 0) != int(cleanup_tail["target_size"])
        ):
            errors.append(f"{rule_id}: RTTI EH cleanup tail has wrong selection or target")
        else:
            try:
                if any(pe_raw_section_name(data, pointer) != ".rdata" for pointer in (vptr, expected_col)):
                    raise ValueError("vtable or RTTI locator outside .rdata")
                body = read_pe(address, 11)
                target_body = read_pe(target, int(cleanup_tail["target_size"]))
                action_body = read_pe(action, 8)
                col = struct.unpack("<I", read_pe(vptr - 4, 4))[0]
                signature, offset, cd_offset, type_descriptor, _hierarchy = struct.unpack(
                    "<IIIII", read_pe(col, 20)
                )
                type_name = read_pe(type_descriptor + 8, 120).split(b"\x00", 1)[0]
            except (ValueError, struct.error) as exc:
                errors.append(f"{rule_id}: RTTI EH cleanup tail: {exc}")
            else:
                actual_target = address + 11 + struct.unpack_from("<i", body, 7)[0]
                action_target = action + 8 + struct.unpack_from("<i", action_body, 4)[0]
                if (
                    hashlib.sha256(body).hexdigest() != cleanup_tail["sha256"]
                    or body[:2] != b"\xC7\x01"
                    or struct.unpack_from("<I", body, 2)[0] != vptr
                    or body[6] != 0xE9
                    or actual_target != target
                    or hashlib.sha256(target_body).hexdigest() != cleanup_tail["target_sha256"]
                    or hashlib.sha256(action_body).hexdigest() != cleanup_tail["action_sha256"]
                    or action_body[:3] != b"\x8B\x4D\xF0"
                    or action_body[3] != 0xE9
                    or action_target != address
                    or col != expected_col
                    or signature != 0
                    or offset != 0
                    or cd_offset != 0
                    or type_descriptor != expected_type
                    or b"invalid_argument@std@@" not in type_name
                ):
                    errors.append(f"{rule_id}: RTTI EH cleanup tail body/action/RTTI differs")
    rtti_virtuals = rule.get("required_rtti_virtual_bodies", [])
    if rtti_virtuals and (
        len(rtti_virtuals) != len(selected_addresses)
        or {str(method["address"]).upper() for method in rtti_virtuals} != selected_addresses
    ):
        errors.append(f"{rule_id}: RTTI virtual witnesses do not cover selected candidates exactly")
    for method in rtti_virtuals:
        address = int(str(method["address"]), 0)
        size = int(method["size"])
        slot = int(str(method["slot"]), 0)
        col_slot = int(str(method["col_slot"]), 0)
        expected_col = int(str(method["col"]), 0)
        expected_type = int(str(method["type_descriptor"]), 0)
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != size:
            errors.append(f"{rule_id}: RTTI virtual 0x{address:08X} has wrong selection or size")
            continue
        if slot % 4 or col_slot % 4 or not 4 <= slot - col_slot <= 64:
            errors.append(f"{rule_id}: RTTI virtual 0x{address:08X} has invalid vtable slot spacing")
            continue
        try:
            if any(pe_raw_section_name(data, pointer) != ".rdata" for pointer in (slot, col_slot, expected_col)):
                raise ValueError("vtable or RTTI locator is outside .rdata")
            body = read_pe(address, size)
            pointed = struct.unpack("<I", read_pe(slot, 4))[0]
            col = struct.unpack("<I", read_pe(col_slot, 4))[0]
            vtable_is_text = all(
                pe_raw_section_name(data, struct.unpack("<I", read_pe(pointer, 4))[0]) == ".text"
                for pointer in range(col_slot + 4, slot + 4, 4)
            )
            signature, _offset, cd_offset, type_descriptor, _hierarchy = struct.unpack(
                "<IIIII", read_pe(col, 20)
            )
            type_name = read_pe(type_descriptor + 8, 192).split(b"\x00", 1)[0]
        except (ValueError, struct.error) as exc:
            errors.append(f"{rule_id}: RTTI virtual 0x{address:08X}: {exc}")
            continue
        expected_fragment = str(method["type_name_contains"]).encode("ascii")
        if (
            hashlib.sha256(body).hexdigest() != method["sha256"]
            or pointed != address
            or not vtable_is_text
            or col != expected_col
            or signature != 0
            or cd_offset != 0
            or type_descriptor != expected_type
            or expected_fragment not in type_name
        ):
            errors.append(f"{rule_id}: RTTI virtual 0x{address:08X} body/vtable/type differs")
        for edge in method.get("calls", []):
            site = int(str(edge["site"]), 0)
            target = int(str(edge["target"]), 0)
            if not address <= site <= address + size - 5:
                errors.append(f"{rule_id}: RTTI virtual 0x{address:08X} has out-of-body E8 site")
                continue
            code = read_pe(site, 5)
            actual = site + 5 + struct.unpack_from("<i", code, 1)[0]
            if code[0] != 0xE8 or actual != target:
                errors.append(f"{rule_id}: RTTI virtual 0x{address:08X} E8 site 0x{site:08X} differs")
        terminal_call = method.get("terminal_call")
        if terminal_call is not None:
            target = int(str(terminal_call), 0)
            code = body[-5:]
            actual = address + size + struct.unpack_from("<i", code, 1)[0]
            if code[0] != 0xE8 or actual != target:
                errors.append(f"{rule_id}: RTTI virtual 0x{address:08X} does not end in the pinned call")
    shared_eh = rule.get("required_shared_eh")
    if shared_eh:
        handler = int(str(shared_eh["handler"]), 0)
        func_info = int(str(shared_eh["func_info"]), 0)
        unwind_map = int(str(shared_eh["unwind_map"]), 0)
        action = int(str(shared_eh["action"]), 0)
        try:
            if (
                pe_raw_section_name(data, handler) != ".text"
                or pe_raw_section_name(data, action) != ".text"
                or pe_raw_section_name(data, func_info) != ".rdata"
                or pe_raw_section_name(data, unwind_map) != ".rdata"
            ):
                raise ValueError("shared EH code or metadata has the wrong PE section")
            handler_body = read_pe(handler, 27)
            info_body = read_pe(func_info, 36)
            map_body = read_pe(unwind_map, 8)
            action_body = read_pe(action, 11)
        except ValueError as exc:
            errors.append(f"{rule_id}: shared EH evidence: {exc}")
        else:
            info_magic, max_state, actual_map = struct.unpack_from("<III", info_body)
            to_state, actual_action = struct.unpack("<iI", map_body)
            security_target = handler + 17 + struct.unpack_from("<i", handler_body, 13)[0]
            frame_target = handler + 27 + struct.unpack_from("<i", handler_body, 23)[0]
            free_target = action + 9 + struct.unpack_from("<i", action_body, 5)[0]
            if (
                hashlib.sha256(handler_body).hexdigest() != shared_eh["handler_sha256"]
                or hashlib.sha256(info_body).hexdigest() != shared_eh["func_info_sha256"]
                or hashlib.sha256(map_body).hexdigest() != shared_eh["unwind_map_sha256"]
                or hashlib.sha256(action_body).hexdigest() != shared_eh["action_sha256"]
                or handler_body[12] != 0xE8
                or security_target != 0x00689D25
                or handler_body[17] != 0xB8
                or struct.unpack_from("<I", handler_body, 18)[0] != func_info
                or handler_body[22] != 0xE9
                or frame_target != 0x006899E7
                or info_magic != 0x19930522
                or max_state != 1
                or actual_map != unwind_map
                or to_state != -1
                or actual_action != action
                or action_body[4] != 0xE8
                or free_target != 0x006898EA
            ):
                errors.append(f"{rule_id}: shared EH handler/FuncInfo/unwind action differs")
        for method in rtti_virtuals:
            address = int(str(method["address"]), 0)
            try:
                prolog = read_pe(address, 7)
            except ValueError as exc:
                errors.append(f"{rule_id}: shared EH prolog 0x{address:08X}: {exc}")
                continue
            if prolog[:3] != b"\x6A\xFF\x68" or struct.unpack_from("<I", prolog, 3)[0] != handler:
                errors.append(f"{rule_id}: shared EH prolog 0x{address:08X} does not push handler")
    eh_unwind = rule.get("required_vc8_eh_unwind")
    if eh_unwind:
        owner = int(str(eh_unwind["owner"]), 0)
        push_site = int(str(eh_unwind["handler_push_site"]), 0)
        handler = int(str(eh_unwind["handler"]), 0)
        handler_size = int(eh_unwind["handler_size"])
        info_site = int(str(eh_unwind["func_info_site"]), 0)
        func_info = int(str(eh_unwind["func_info"]), 0)
        unwind_map = int(str(eh_unwind["unwind_map"]), 0)
        entries = eh_unwind["unwind_entries"]
        actions = eh_unwind["actions"]
        if f"0x{owner:08X}".upper() not in selected_addresses:
            errors.append(f"{rule_id}: VC8 EH owner 0x{owner:08X} is not selected")
        elif not owner <= push_site <= owner + int(row_by_address[f"0x{owner:08X}".upper()]["size"], 0) - 5:
            errors.append(f"{rule_id}: VC8 EH handler push lies outside owner")
        if (
            not entries
            or not actions
            or len({str(action["address"]).upper() for action in actions}) != len(actions)
            or {str(entry["action"]).upper() for entry in entries}
            != {str(action["address"]).upper() for action in actions}
        ):
            errors.append(f"{rule_id}: VC8 EH unwind entries/actions are incomplete")
        try:
            if (
                pe_raw_section_name(data, handler) != ".text"
                or pe_raw_section_name(data, func_info) != ".rdata"
                or pe_raw_section_name(data, unwind_map) != ".rdata"
            ):
                raise ValueError("VC8 EH handler or metadata has the wrong PE section")
            push = read_pe(push_site, 5)
            handler_body = read_pe(handler, handler_size)
            info_instruction = read_pe(info_site, 5)
            info_body = read_pe(func_info, 36)
            map_body = read_pe(unwind_map, len(entries) * 8)
        except ValueError as exc:
            errors.append(f"{rule_id}: VC8 EH evidence: {exc}")
        else:
            magic, max_state, actual_map = struct.unpack_from("<III", info_body)
            frame_tail = handler_body[-5:]
            frame_target = handler + handler_size + struct.unpack_from("<i", frame_tail, 1)[0]
            if (
                push[0] != 0x68
                or struct.unpack_from("<I", push, 1)[0] != handler
                or hashlib.sha256(handler_body).hexdigest() != eh_unwind["handler_sha256"]
                or not handler <= info_site <= handler + handler_size - 5
                or info_instruction[0] != 0xB8
                or struct.unpack_from("<I", info_instruction, 1)[0] != func_info
                or frame_tail[0] != 0xE9
                or frame_target != 0x006899E7
                or hashlib.sha256(info_body).hexdigest() != eh_unwind["func_info_sha256"]
                or magic != 0x19930522
                or max_state != len(entries)
                or actual_map != unwind_map
                or hashlib.sha256(map_body).hexdigest() != eh_unwind["unwind_map_sha256"]
            ):
                errors.append(f"{rule_id}: VC8 EH handler/FuncInfo/unwind map differs")
            for index, entry in enumerate(entries):
                to_state, action = struct.unpack_from("<iI", map_body, index * 8)
                if to_state != int(entry["to_state"]) or action != int(str(entry["action"]), 0):
                    errors.append(f"{rule_id}: VC8 EH unwind state {index} differs")
        for action in actions:
            address = int(str(action["address"]), 0)
            size = int(action["size"])
            target = int(str(action["target"]), 0)
            try:
                if pe_raw_section_name(data, address) != ".text":
                    raise ValueError("EH action is outside .text")
                body = read_pe(address, size)
            except ValueError as exc:
                errors.append(f"{rule_id}: VC8 EH action 0x{address:08X}: {exc}")
                continue
            tail = body[-5:]
            actual_target = address + size + struct.unpack_from("<i", tail, 1)[0]
            if (
                hashlib.sha256(body).hexdigest() != action["sha256"]
                or tail[0] != 0xE9
                or actual_target != target
            ):
                errors.append(f"{rule_id}: VC8 EH action 0x{address:08X} differs")
    for terminal in rule.get("required_terminal_noreturn_calls", []):
        owner = int(str(terminal["owner"]), 0)
        site = int(str(terminal["site"]), 0)
        callee = int(str(terminal["callee"]), 0)
        callee_size = int(terminal["callee_size"])
        throw_target = int(str(terminal["throw_target"]), 0)
        owner_key = f"0x{owner:08X}".upper()
        callee_key = f"0x{callee:08X}".upper()
        if (
            owner_key not in selected_addresses
            or callee_key not in row_by_address
            or int(row_by_address[callee_key]["size"], 0) != callee_size
            or site + 5 != owner + int(row_by_address[owner_key]["size"], 0)
        ):
            errors.append(f"{rule_id}: terminal no-return call has wrong candidate boundary")
            continue
        try:
            caller_call = read_pe(site, 5)
            callee_body = read_pe(callee, callee_size)
            caller_padding = read_pe(site + 5, 8)
            callee_padding = read_pe(callee + callee_size, 8)
        except ValueError as exc:
            errors.append(f"{rule_id}: terminal no-return call: {exc}")
            continue
        caller_target = site + 5 + struct.unpack_from("<i", caller_call, 1)[0]
        throw_call = callee_body[-5:]
        actual_throw = callee + callee_size + struct.unpack_from("<i", throw_call, 1)[0]
        if (
            caller_call[0] != 0xE8
            or caller_target != callee
            or hashlib.sha256(callee_body).hexdigest() != terminal["callee_sha256"]
            or throw_call[0] != 0xE8
            or actual_throw != throw_target
            or caller_padding != b"\xCC" * 8
            or callee_padding != b"\xCC" * 8
            or f"0x{throw_target:08X}".upper() not in row_by_address
        ):
            errors.append(f"{rule_id}: terminal no-return call or throw callee differs")
    for body in rule.get("required_body_hashes", []):
        address = int(str(body["address"]), 0)
        size = int(body["size"])
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or key not in row_by_address:
            errors.append(f"{rule_id}: body 0x{address:08X} is not selected")
            continue
        if int(row_by_address[key]["size"], 0) != size:
            errors.append(f"{rule_id}: body 0x{address:08X} has wrong candidate size")
            continue
        try:
            actual_hash = hashlib.sha256(read_pe(address, size)).hexdigest()
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            continue
        if actual_hash != body["sha256"]:
            errors.append(f"{rule_id}: body 0x{address:08X} SHA-256 differs")
    for edge in rule.get("required_selected_body_calls", []):
        owner = int(str(edge["owner"]), 0)
        site = int(str(edge["site"]), 0)
        target = int(str(edge["target"]), 0)
        owner_key = f"0x{owner:08X}".upper()
        target_key = f"0x{target:08X}".upper()
        if owner_key not in selected_addresses:
            errors.append(f"{rule_id}: body-call owner 0x{owner:08X} is not selected")
            continue
        target_row = row_by_address.get(target_key)
        expected_status = str(edge.get("target_status", "matching"))
        if expected_status not in {"matching", "implemented", "identified"}:
            errors.append(f"{rule_id}: unsupported body-call target status {expected_status!r}")
            continue
        if target_row is None or target_row["status"] != expected_status:
            errors.append(
                f"{rule_id}: body-call target 0x{target:08X} status is not {expected_status}"
            )
            continue
        owner_size = int(row_by_address[owner_key]["size"], 0)
        if not owner <= site <= owner + owner_size - 5:
            errors.append(f"{rule_id}: body-call site 0x{site:08X} is outside owner")
            continue
        try:
            code = read_pe(site, 5)
        except ValueError as exc:
            errors.append(f"{rule_id}: body-call site 0x{site:08X}: {exc}")
            continue
        actual_target = site + 5 + struct.unpack_from("<i", code, 1)[0]
        if code[0] != 0xE8 or actual_target != target:
            errors.append(f"{rule_id}: body CALL at 0x{site:08X} differs")
    for edge in rule.get("required_direct_edges", []):
        site = int(str(edge["site"]), 0)
        target = int(str(edge["target"]), 0)
        caller = str(edge["caller"]).upper()
        kind = str(edge.get("kind", "call"))
        if kind not in {"call", "jump"}:
            errors.append(f"{rule_id}: unsupported direct-edge kind {kind!r}")
            continue
        if f"0x{target:08X}".upper() not in selected_addresses:
            errors.append(f"{rule_id}: edge target 0x{target:08X} is not selected")
        caller_row = row_by_address.get(caller)
        if caller_row is None:
            errors.append(f"{rule_id}: missing caller {caller}")
            continue
        caller_start = int(caller, 0)
        caller_end = caller_start + int(caller_row["size"], 0)
        if not caller_start <= site <= caller_end - 5:
            errors.append(f"{rule_id}: edge site 0x{site:08X} is outside caller {caller}")
            continue
        if edge.get("caller_status") and caller_row["status"] != edge["caller_status"]:
            errors.append(f"{rule_id}: caller {caller} status is not {edge['caller_status']}")
        try:
            code = read_pe(site, 5)
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            continue
        expected_opcode = 0xE8 if kind == "call" else 0xE9
        if code[0] != expected_opcode:
            errors.append(f"{rule_id}: 0x{site:08X} is not a direct {kind}")
            continue
        actual_target = site + 5 + struct.unpack_from("<i", code, 1)[0]
        if actual_target != target:
            errors.append(
                f"{rule_id}: 0x{site:08X} {kind} lands at 0x{actual_target:08X}, "
                f"expected 0x{target:08X}"
            )
    for jump in rule.get("required_tail_jumps", []):
        address = int(str(jump["address"]), 0)
        target = int(str(jump["target"]), 0)
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses:
            errors.append(f"{rule_id}: tail jump 0x{address:08X} is not selected")
            continue
        if int(row_by_address[key]["size"], 0) != 5:
            errors.append(f"{rule_id}: tail jump 0x{address:08X} is not five bytes")
            continue
        if f"0x{target:08X}".upper() not in row_by_address:
            errors.append(f"{rule_id}: tail jump target 0x{target:08X} is not a candidate")
            continue
        try:
            code = read_pe(address, 5)
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            continue
        actual_target = address + 5 + struct.unpack_from("<i", code, 1)[0]
        if code[0] != 0xE9 or actual_target != target:
            errors.append(
                f"{rule_id}: 0x{address:08X} is not E9 to 0x{target:08X}"
            )
    if rule.get("required_iat_imports"):
        try:
            imports = pe_import_names_by_iat(data, read_pe)
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            imports = {}
        for import_entry in rule["required_iat_imports"]:
            address = int(str(import_entry["address"]), 0)
            slot = int(str(import_entry["iat_slot"]), 0)
            key = f"0x{address:08X}".upper()
            if key not in selected_addresses or int(row_by_address[key]["size"], 0) != 6:
                errors.append(f"{rule_id}: 0x{address:08X} is not a selected six-byte import thunk")
                continue
            code = read_pe(address, 6)
            if code[:2] != b"\xFF\x25" or struct.unpack_from("<I", code, 2)[0] != slot:
                errors.append(f"{rule_id}: 0x{address:08X} FF25 IAT slot differs")
            expected_name = (str(import_entry["dll"]), str(import_entry["name"]))
            if imports.get(slot) != expected_name:
                errors.append(f"{rule_id}: IAT slot 0x{slot:08X} import name differs")
    for thunk in rule.get("required_global_dtor_aliases", []):
        address = int(str(thunk["address"]), 0)
        object_address = int(str(thunk["object"]), 0)
        target = int(str(thunk["target"]), 0)
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != 10:
            errors.append(f"{rule_id}: 0x{address:08X} is not a selected ten-byte thunk")
            continue
        if f"0x{target:08X}".upper() not in row_by_address:
            errors.append(f"{rule_id}: 0x{address:08X} destructor target is not a candidate")
            continue
        data_section = next(
            section for section in target_manifest()["pe"]["sections"]
            if section["name"] == ".data"
        )
        data_start = int(target_manifest()["pe"]["image_base"], 0) + int(data_section["rva"], 0)
        if not data_start <= object_address < data_start + int(data_section["virtual_size"]):
            errors.append(f"{rule_id}: 0x{address:08X} receiver is not in .data")
            continue
        try:
            body = read_pe(address, 10)
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            continue
        body_target = address + 10 + struct.unpack_from("<i", body, 6)[0]
        registration_error = atexit_registration_error(thunk, read_pe)
        if (
            body[0] != 0xB9 or body[5] != 0xE9
            or struct.unpack_from("<I", body, 1)[0] != object_address
            or body_target != target
            or registration_error
        ):
            errors.append(f"{rule_id}: 0x{address:08X} static destructor registration differs")
    for callback in rule.get("required_atexit_callbacks", []):
        address = int(str(callback["address"]), 0)
        size = int(callback["size"])
        key = f"0x{address:08X}".upper()
        if key not in selected_addresses or int(row_by_address[key]["size"], 0) != size:
            errors.append(f"{rule_id}: 0x{address:08X} callback size or selection differs")
            continue
        try:
            actual_hash = hashlib.sha256(read_pe(address, size)).hexdigest()
        except ValueError as exc:
            errors.append(f"{rule_id}: {exc}")
            continue
        if actual_hash != callback["sha256"]:
            errors.append(f"{rule_id}: 0x{address:08X} callback body differs")
        registration_error = atexit_registration_error(callback, read_pe)
        if registration_error:
            errors.append(f"{rule_id}: 0x{address:08X} {registration_error}")
        if "free_call_site" in callback:
            site = int(str(callback["free_call_site"]), 0)
            if not address <= site <= address + size - 5:
                errors.append(f"{rule_id}: 0x{address:08X} free call lies outside callback")
                continue
            code = read_pe(site, 5)
            free_target = site + 5 + struct.unpack_from("<i", code, 1)[0]
            if code[0] != 0xE8 or free_target != 0x006898EA:
                errors.append(f"{rule_id}: 0x{address:08X} free call target differs")
    if rule.get("xiph_anchor_file"):
        errors.extend(validate_xiph_anchor_evidence(rule, selected, rows, read_pe))
    if rule.get("xiph_relocated_anchor_file"):
        errors.extend(
            validate_xiph_relocated_anchor_evidence(rule, selected, rows, read_pe)
        )
    if rule.get("vc8_generated_anchor_file"):
        errors.extend(
            validate_vc8_generated_anchor_evidence(rule, selected, rows, read_pe)
        )
    if rule.get("msvc_runtime_anchor_file"):
        errors.extend(
            validate_msvc_runtime_anchor_evidence(rule, selected, rows, read_pe)
        )
    if rule.get("pointer_anchor_file"):
        errors.extend(
            validate_pointer_anchor_evidence(rule, selected, rows, read_pe)
        )
    return errors


def materialize() -> tuple[list[dict[str, str]], list[str]]:
    rows = read_csv(FUNCTIONS)
    rules_doc = tomllib.loads(RULES.read_text(encoding="utf-8"))
    data = attest_target(rules_doc)
    read_pe = pe_reader(data)
    census = {row["address"]: baseline(row) for row in rows}
    errors: list[str] = []
    claimed: dict[str, str] = {}
    rules = rules_doc.get("rules", [])
    need_msvc = any(bool(rule.get("msvc_archive_defined_symbol")) for rule in rules)
    msvc_symbols = load_msvc_archive_symbols() if need_msvc else None
    for rule in rules:
        rule_id = str(rule["id"])
        selected = select(rule, rows, msvc_symbols)
        count = len(selected)
        byte_count = sum(int(row["size"], 0) for row in selected)
        if count != int(rule["expected_count"]):
            errors.append(f"{rule_id}: selected {count} rows, expected {rule['expected_count']}")
        if byte_count != int(rule["expected_bytes"]):
            errors.append(f"{rule_id}: selected {byte_count} bytes, expected {rule['expected_bytes']}")
        errors.extend(validate_rule_evidence(rule, selected, rows, data, read_pe))
        for row in selected:
            if row["status"] == "matching":
                errors.append(f"{rule_id}: overlaps canonical authored function {row['address']}")
                continue
            previous = claimed.get(row["address"])
            if previous:
                errors.append(f"{rule_id}: overlaps {previous} at {row['address']}")
                continue
            claimed[row["address"]] = rule_id
            census[row["address"]] = {
                "address": row["address"],
                "origin": str(rule["origin"]),
                "subsystem": str(rule["subsystem"]),
                "disposition": str(rule["disposition"]),
                "confidence": str(rule["confidence"]),
                "evidence_id": rule_id,
            }
    for rule in rules:
        for jump in rule.get("required_tail_jumps", []):
            target = f"0x{int(str(jump['target']), 0):08X}"
            target_origin = str(jump["target_origin"])
            target_row = census.get(target)
            if target_row is None or target_row["origin"] != target_origin or target_row["disposition"] != "exclude":
                errors.append(
                    f"{rule['id']}: jump target {target} is not an excluded {target_origin} candidate"
                )
        if rule.get("required_global_dtor_aliases") or rule.get("required_atexit_callbacks"):
            atexit = census.get("0x0068AF1E")
            if atexit is None or atexit["origin"] != "vc8_runtime" or atexit["disposition"] != "exclude":
                errors.append(f"{rule['id']}: _atexit runtime destination is not excluded")
        if any("free_call_site" in callback for callback in rule.get("required_atexit_callbacks", [])):
            free_alias = census.get("0x006898EA")
            if free_alias is None or free_alias["origin"] != "compiler_generated" or free_alias["disposition"] != "exclude":
                errors.append(f"{rule['id']}: pinned VC8 free alias is not excluded")
    return [census[row["address"]] for row in rows], errors


def validate_rows(rows: list[dict[str, str]]) -> list[str]:
    errors: list[str] = []
    ledger = read_csv(FUNCTIONS)
    if not rows or list(rows[0]) != FIELDS:
        return ["function-origins.csv: invalid or missing header"]
    if [row["address"] for row in rows] != [row["address"] for row in ledger]:
        errors.append("function-origins.csv: addresses do not exactly match functions.csv")
    for line, row in enumerate(rows, 2):
        if row["origin"] not in ORIGINS: errors.append(f"function-origins.csv:{line}: invalid origin")
        if row["disposition"] not in DISPOSITIONS: errors.append(f"function-origins.csv:{line}: invalid disposition")
        if row["confidence"] not in CONFIDENCES: errors.append(f"function-origins.csv:{line}: invalid confidence")
        if row["origin"] == "unknown" and row["disposition"] != "review": errors.append(f"function-origins.csv:{line}: unknown origin must remain review")
    return errors


def write(rows: list[dict[str, str]]) -> None:
    with OUTPUT.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator="\n")
        writer.writeheader(); writer.writerows(rows)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    try:
        expected, errors = materialize()
    except (OSError, KeyError, TypeError, ValueError, tomllib.TOMLDecodeError) as exc:
        print(f"error: origin census failed: {exc}"); return 1
    if errors:
        print("\n".join(errors)); return 1
    if args.write: write(expected)
    if args.check:
        if not OUTPUT.exists(): print("missing config/function-origins.csv"); return 1
        actual = read_csv(OUTPUT); errors.extend(validate_rows(actual))
        if actual != expected: errors.append("config/function-origins.csv is stale; run scripts/function-origins.py --write")
        if errors: print("\n".join(errors)); return 1
    counts = Counter(row["origin"] for row in expected)
    excluded = sum(row["disposition"] == "exclude" for row in expected)
    authored = sum(row["disposition"] == "authored" for row in expected)
    print(f"origin census OK: {len(expected)} rows, authored={authored}, excluded={excluded}, review={len(expected)-authored-excluded}; " + ", ".join(f"{k}={counts[k]}" for k in sorted(counts)))
    return 0

if __name__ == "__main__": raise SystemExit(main())
