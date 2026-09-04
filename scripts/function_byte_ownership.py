#!/usr/bin/env python3
"""Load and validate reviewed multi-chunk source-function byte ownership."""

from __future__ import annotations

import hashlib
from pathlib import Path
import re
import struct
import tomllib
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config"
TARGET = ROOT / "resources" / "th105.exe"
MANIFEST = CONFIG / "function-byte-ownership.toml"
ADDRESS = re.compile(r"^0x[0-9A-F]{8}$")
SHA256 = re.compile(r"^[0-9a-f]{64}$")


def parse_address(raw: object, context: str) -> int:
    value = str(raw)
    if not ADDRESS.fullmatch(value):
        raise ValueError(f"{context}: noncanonical address {value!r}")
    return int(value, 16)


def pe_reader(image: bytes):
    if len(image) < 0x40 or image[:2] != b"MZ":
        raise ValueError("resources/th105.exe: target is not a PE image")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe : pe + 4] != b"PE\0\0":
        raise ValueError("resources/th105.exe: missing PE signature")
    sections = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    table = optional + optional_size
    spans: list[tuple[int, int, int]] = []
    for index in range(sections):
        offset = table + index * 40
        _virtual_size, rva, raw_size, raw_offset = struct.unpack_from(
            "<IIII", image, offset + 8
        )
        spans.append((image_base + rva, image_base + rva + raw_size, raw_offset))

    def read(address: int, size: int) -> bytes:
        for start, end, raw_offset in spans:
            if start <= address and address + size <= end:
                relative = address - start
                return image[raw_offset + relative : raw_offset + relative + size]
        raise ValueError(
            f"function-byte-ownership: span 0x{address:08X}+{size} is not raw-mapped"
        )

    return read


def load(
    functions: dict[int, dict[str, str]] | None = None,
    *,
    require_bytes: bool = False,
) -> dict[int, dict[str, Any]]:
    if not MANIFEST.exists():
        return {}
    with MANIFEST.open("rb") as stream:
        manifest = tomllib.load(stream)
    if manifest.get("schema_version") != 1:
        raise ValueError("function-byte-ownership.toml: unsupported schema_version")

    with (CONFIG / "target.toml").open("rb") as stream:
        target_manifest = tomllib.load(stream)
    target_sha = str(target_manifest["target"]["sha256"])
    if manifest.get("target_sha256") != target_sha:
        raise ValueError("function-byte-ownership.toml: target SHA-256 mismatch")

    image = TARGET.read_bytes() if require_bytes else b""
    if require_bytes and hashlib.sha256(image).hexdigest() != target_sha:
        raise ValueError("resources/th105.exe: target SHA-256 mismatch")
    read_target = pe_reader(image) if require_bytes else None

    result: dict[int, dict[str, Any]] = {}
    for index, raw in enumerate(manifest.get("functions", []), start=1):
        context = f"function-byte-ownership.toml:functions[{index}]"
        address = parse_address(raw.get("address"), context)
        if address in result:
            raise ValueError(f"{context}: duplicate function address")
        main_size = int(raw.get("main_size", 0))
        main_end = parse_address(raw.get("main_end"), context)
        extent_end = parse_address(raw.get("extent_end"), context)
        if main_size <= 0 or main_end != address + main_size - 1:
            raise ValueError(f"{context}: inconsistent main chunk boundary")
        if functions is not None:
            row = functions.get(address)
            if row is None:
                raise ValueError(f"{context}: address is not in functions.csv")
            if int(row["size"], 0) != main_size or int(row["span_end"], 0) != main_end:
                raise ValueError(f"{context}: main chunk disagrees with functions.csv")

        chunks: list[dict[str, Any]] = []
        previous_end = main_end
        for chunk_index, chunk in enumerate(raw.get("chunks", []), start=1):
            chunk_context = f"{context}.chunks[{chunk_index}]"
            start = parse_address(chunk.get("start"), chunk_context)
            end = parse_address(chunk.get("end"), chunk_context)
            size = int(chunk.get("size", 0))
            digest = str(chunk.get("sha256", ""))
            if start <= previous_end or end < start or size != end - start + 1:
                raise ValueError(f"{chunk_context}: invalid or overlapping chunk span")
            if not SHA256.fullmatch(digest):
                raise ValueError(f"{chunk_context}: invalid SHA-256")
            if functions is not None:
                intruders = [
                    other
                    for other in functions
                    if other != address and start <= other <= end
                ]
                if intruders:
                    raise ValueError(
                        f"{chunk_context}: overlaps tracked candidate start "
                        f"0x{min(intruders):08X}"
                    )
            if read_target is not None:
                actual = hashlib.sha256(read_target(start, size)).hexdigest()
                if actual != digest:
                    raise ValueError(f"{chunk_context}: canonical bytes changed")
            chunks.append(
                {"start": start, "end": end, "size": size, "sha256": digest}
            )
            previous_end = end

        remote_bytes = sum(chunk["size"] for chunk in chunks)
        if not chunks or extent_end != chunks[-1]["end"]:
            raise ValueError(f"{context}: extent_end does not match last remote chunk")
        if int(raw.get("remote_bytes", -1)) != remote_bytes:
            raise ValueError(f"{context}: remote_bytes mismatch")
        owned_bytes = main_size + remote_bytes
        if int(raw.get("owned_bytes", -1)) != owned_bytes:
            raise ValueError(f"{context}: owned_bytes mismatch")
        remote_exact = bool(raw.get("remote_exact", False))
        if remote_exact and not str(raw.get("exact_evidence", "")).strip():
            raise ValueError(f"{context}: remote_exact requires exact_evidence")
        result[address] = {
            "address": address,
            "main_size": main_size,
            "main_end": main_end,
            "extent_end": extent_end,
            "remote_bytes": remote_bytes,
            "owned_bytes": owned_bytes,
            "remote_exact": remote_exact,
            "exact_evidence": str(raw.get("exact_evidence", "")),
            "evidence": str(raw.get("evidence", "")),
            "chunks": chunks,
        }
    return result


def owned_size(address: int, main_size: int, ownership: dict[int, dict[str, Any]]) -> int:
    row = ownership.get(address)
    return int(row["owned_bytes"]) if row is not None else main_size


def exact_extra_bytes(address: int, ownership: dict[int, dict[str, Any]]) -> int:
    row = ownership.get(address)
    if row is None or not row["remote_exact"]:
        return 0
    return int(row["remote_bytes"])
