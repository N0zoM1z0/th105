"""Shared validation for target-attested VC8 floating-point relocations."""

from __future__ import annotations

from collections.abc import Iterable, Mapping
import re
import struct
from typing import Any


REAL_LITERAL_SYMBOL = re.compile(r"^__real@([0-9A-Fa-f]{8}|[0-9A-Fa-f]{16})$")
REAL_LITERAL_REFERENCE = re.compile(
    r"^(__real@[0-9A-Fa-f]{8}|__real@[0-9A-Fa-f]{16})(?:\+0x([0-9A-Fa-f]+))?$"
)


def canonical_data_bytes(data_hex: str, context: str) -> bytes:
    """Decode a lowercase, byte-aligned ledger literal."""

    try:
        value = bytes.fromhex(data_hex)
    except ValueError as exc:
        raise ValueError(f"{context}: data_hex must contain hexadecimal bytes") from exc
    if not value:
        raise ValueError(f"{context}: data_hex must not be empty")
    if data_hex != value.hex():
        raise ValueError(f"{context}: data_hex must use canonical lowercase hexadecimal")
    return value


def real_literal_bytes(relocation: Mapping[str, object]) -> bytes | None:
    """Decode and validate a VC8 ``__real`` relocation's literal bytes."""

    symbol = str(relocation.get("symbol", ""))
    match = REAL_LITERAL_SYMBOL.fullmatch(symbol)
    if match is None:
        if symbol.startswith("__real@"):
            raise ValueError(
                "malformed __real symbol; expected exactly 8 or 16 hexadecimal digits"
            )
        if "data_hex" in relocation:
            raise ValueError("data_hex requires a 32-bit or 64-bit __real@... symbol")
        return None
    if str(relocation.get("type")) != "DIR32":
        raise ValueError("real literals must use DIR32 relocations")
    if int(relocation.get("addend", 0)) != 0:
        raise ValueError("real literals must use a zero addend")

    symbol_bytes = bytes.fromhex(match.group(1))[::-1]
    if "data_hex" not in relocation:
        return symbol_bytes

    declared = canonical_data_bytes(str(relocation["data_hex"]), symbol)
    if declared != symbol_bytes:
        raise ValueError(
            f"{symbol} encodes {symbol_bytes.hex()}, not declared {declared.hex()}"
        )
    return symbol_bytes


def real_literal_reference_bytes(reference: str) -> bytes | None:
    """Decode a manifest DIR32 source reference and reject real-literal addends."""

    if not reference.startswith("__real@"):
        return None
    match = REAL_LITERAL_REFERENCE.fullmatch(reference)
    if match is None:
        raise ValueError(
            "malformed __real reference; expected 8 or 16 hexadecimal digits"
        )
    addend = int(match.group(2), 16) if match.group(2) is not None else 0
    return real_literal_bytes(
        {"type": "DIR32", "symbol": match.group(1), "addend": addend}
    )


def parse_addends(raw: str, context: str) -> frozenset[int]:
    try:
        values = frozenset(
            int(value, 0) for value in raw.split(";") if value.strip()
        )
    except ValueError as exc:
        raise ValueError(f"{context}: invalid relocation addends {raw!r}") from exc
    if not values or any(value < 0 for value in values):
        raise ValueError(f"{context}: relocation addends must be nonnegative")
    return values


def pe_bytes_at(data: bytes, address: int, size: int) -> bytes:
    """Read an image VA while honoring PE virtual zero-fill."""

    pe = struct.unpack_from("<I", data, 0x3C)[0]
    section_count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    sections = pe + 24 + optional_size
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    rva = address - image_base
    for index in range(section_count):
        offset = sections + 40 * index
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, offset + 8
        )
        mapped_size = max(virtual_size, raw_size)
        if virtual_address <= rva < virtual_address + mapped_size:
            section_offset = rva - virtual_address
            if section_offset + size > mapped_size:
                raise ValueError(
                    f"range {address:#x}+{size:#x} crosses a PE section boundary"
                )
            raw_available = max(0, min(size, raw_size - section_offset))
            file_offset = raw_pointer + section_offset
            raw = data[file_offset : file_offset + raw_available]
            if len(raw) != raw_available:
                raise ValueError("PE section raw data is truncated")
            return raw + bytes(size - raw_available)
    raise ValueError(f"address {address:#x} is not in a PE section")


def validate_real_literal_mapping(
    source_reference: str,
    destination_symbol: str,
    destination_row: Mapping[str, str],
) -> bytes | None:
    """Prove that a real-symbol override retains the source floating value."""

    source_bytes = real_literal_reference_bytes(source_reference)
    if source_bytes is None:
        return None
    context = f"DIR32 mapping {source_reference}={destination_symbol}"
    destination_bytes = canonical_data_bytes(destination_row["data_hex"], context)
    if source_bytes != destination_bytes:
        raise ValueError(
            f"{context}: source encodes {source_bytes.hex()}, but destination "
            f"declares {destination_bytes.hex()}"
        )
    if 0 not in parse_addends(destination_row["addends"], context):
        raise ValueError(f"{context}: destination does not allow the required zero addend")
    return source_bytes


def audit_real_literals(
    relocation_rows: Iterable[Mapping[str, str]],
    manifest: Mapping[str, Any],
    *,
    target_data: bytes | None = None,
) -> dict[str, int]:
    """Validate every real relocation ledger row and explicit manifest mapping."""

    rows: dict[str, Mapping[str, str]] = {}
    ledger_literals = 0
    target_checks = 0
    for line, row in enumerate(relocation_rows, start=2):
        symbol = row["coff_symbol"]
        if not symbol:
            raise ValueError(f"reccmp-relocations.csv:{line}: empty coff_symbol")
        if symbol in rows:
            raise ValueError(
                f"reccmp-relocations.csv:{line}: duplicate coff_symbol {symbol!r}"
            )
        rows[symbol] = row
        if not symbol.startswith("__real@"):
            continue
        context = f"reccmp-relocations.csv:{line}"
        addends = parse_addends(row["addends"], context)
        if addends != frozenset({0}):
            raise ValueError(f"{context}: real literals must allow only addend zero")
        if (row.get("validation") or "literal") != "literal":
            raise ValueError(f"{context}: real literals require literal validation")
        literal = real_literal_bytes(
            {
                "type": "DIR32",
                "symbol": symbol,
                "addend": 0,
                "data_hex": row["data_hex"],
            }
        )
        assert literal is not None
        ledger_literals += 1
        if target_data is not None:
            address = int(row["address"], 0)
            actual = pe_bytes_at(target_data, address, len(literal))
            if actual != literal:
                raise ValueError(
                    f"{context}: target literal at 0x{address:08X} is "
                    f"{actual.hex()}, not {literal.hex()}"
                )
            target_checks += 1

    explicit_mappings = 0
    for unit_name, unit in manifest.get("units", {}).items():
        for function in unit.get("functions", []):
            address = str(function.get("address", "<unknown>"))
            for mapping in function.get("dir32_targets", []):
                source_reference, separator, destination_symbol = mapping.partition("=")
                if not separator:
                    continue
                source_bytes = real_literal_reference_bytes(source_reference)
                if source_bytes is None:
                    continue
                explicit_mappings += 1
                if destination_symbol not in rows:
                    raise ValueError(
                        f"match unit {unit_name!r} function {address} references "
                        f"unknown DIR32 allowlist key {destination_symbol!r}"
                    )
                destination = rows[destination_symbol]
                validate_real_literal_mapping(
                    source_reference, destination_symbol, destination
                )
                if target_data is not None:
                    destination_address = int(destination["address"], 0)
                    actual = pe_bytes_at(
                        target_data, destination_address, len(source_bytes)
                    )
                    if actual != source_bytes:
                        raise ValueError(
                            f"match unit {unit_name!r} function {address}: target "
                            f"literal at 0x{destination_address:08X} is {actual.hex()}, "
                            f"not source value {source_bytes.hex()}"
                        )
                    target_checks += 1

    return {
        "ledger_literals": ledger_literals,
        "explicit_mappings": explicit_mappings,
        "target_checks": target_checks,
    }
