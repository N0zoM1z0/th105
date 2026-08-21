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
from pathlib import Path
import struct
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




def load_msvc_archive_symbols() -> set[str]:
    """Return all defined COFF symbols from the SHA-pinned VC8 SP1 archives."""
    extractor_path = ROOT / "scripts/extract-msvc-library-object.py"
    spec = importlib.util.spec_from_file_location("th105_msvc_extract", extractor_path)
    if spec is None or spec.loader is None:
        raise ValueError("cannot load pinned MSVC archive extractor")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
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
        if candidates != [address]:
            errors.append(
                f"{rule['id']}: {address} relocated Xiph fingerprint is not inventory-unique: {candidates}"
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
    xiph_manifest = rule.get("xiph_anchor_file") or rule.get("xiph_relocated_anchor_file")
    if xiph_manifest:
        anchor_doc = tomllib.loads(
            (ROOT / str(xiph_manifest)).read_text(encoding="utf-8")
        )
        explicit = {str(anchor["address"]).upper() for anchor in anchor_doc.get("anchors", [])}
    start = int(str(rule["start"]), 0) if "start" in rule else None
    end = int(str(rule["end"]), 0) if "end" in rule else None
    selected = []
    for row in rows:
        address = int(row["address"], 0)
        if explicit and row["address"].upper() not in explicit:
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
    if rule.get("xiph_anchor_file"):
        errors.extend(validate_xiph_anchor_evidence(rule, selected, rows, read_pe))
    if rule.get("xiph_relocated_anchor_file"):
        errors.extend(
            validate_xiph_relocated_anchor_evidence(rule, selected, rows, read_pe)
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
