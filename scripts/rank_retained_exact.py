#!/usr/bin/env python3
"""Rank retained TH105 1.06 exact source against the canonical 1.06a target.

This is a hypothesis-ranking tool, not an acceptance tool.  It compiles retained
source with the pinned VC8 probe profile, compares normalized instruction shape
against current IDA candidate spans, and reports raw byte differences with COFF
relocation fields masked.  A result still needs current-target semantic/boundary
review plus ``scripts/build.py --unit ... --compare`` before promotion.
"""

from __future__ import annotations

import argparse
import bisect
import csv
import difflib
import hashlib
import io
import json
import os
from pathlib import Path
import re
import shutil
import struct
import subprocess
import tempfile
import tomllib
from typing import Any, Iterable


ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources" / "th105.exe"
FUNCTIONS = ROOT / "config" / "functions.csv"
ORIGINS = ROOT / "config" / "function-origins.csv"
TARGET_CONFIG = ROOT / "config" / "target.toml"
COMPILE_UNIT = ROOT / "scripts" / "compile-unit.sh"
DEFAULT_HISTORICAL_REV = "dce97d1843051197720b981fa3c629ff579f92a0"
DEFAULT_OUTPUT = ROOT / ".analysis" / "retained-exact-migration" / "results.json"
DEFAULT_CACHE = ROOT / ".analysis" / "retained-exact-migration" / "objects"
ADDRESS_RE = re.compile(r"0x([0-9a-fA-F]+)")
DISASM_RE = re.compile(
    r"^\s*([0-9a-fA-F]+):\s+(?:(?:[0-9a-fA-F]{2})\s+)+\s*(.*?)\s*$"
)
BRANCH_MNEMONICS = {
    "call",
    "jmp",
    "ja",
    "jae",
    "jb",
    "jbe",
    "je",
    "jg",
    "jge",
    "jl",
    "jle",
    "jne",
    "jno",
    "jnp",
    "jns",
    "jo",
    "jp",
    "js",
    "jz",
    "jcxz",
    "jecxz",
    "loop",
    "loope",
    "loopne",
}


def git_text(revision: str, path: str) -> str:
    return subprocess.check_output(
        ["git", "show", f"{revision}:{path}"],
        cwd=ROOT,
        text=True,
        errors="replace",
    )


def parse_csv_text(text: str) -> list[dict[str, str]]:
    return list(csv.DictReader(io.StringIO(text)))


def verify_target() -> None:
    with TARGET_CONFIG.open("rb") as stream:
        expected = tomllib.load(stream)["target"]
    data = TARGET.read_bytes()
    if len(data) != int(expected["size"]):
        raise ValueError(
            f"target size mismatch: got {len(data)}, expected {expected['size']}"
        )
    digest = hashlib.sha256(data).hexdigest()
    if digest.lower() != str(expected["sha256"]).lower():
        raise ValueError(
            f"target SHA-256 mismatch: got {digest}, expected {expected['sha256']}"
        )


def is_function_symbol(name: str, symbol_base: str) -> bool:
    if name == symbol_base or name.startswith(f"?{symbol_base}@"):
        return True
    if name.startswith("?") and not name.startswith("??"):
        parts = name[1:].split("@", 2)
        if len(parts) >= 2 and symbol_base == f"{parts[1]}_{parts[0]}":
            return True
    if symbol_base.endswith("_ctor"):
        return name.startswith(f"??0{symbol_base.removesuffix('_ctor')}@")
    if symbol_base.endswith("_dtor"):
        return name.startswith(f"??1{symbol_base.removesuffix('_dtor')}@")
    if symbol_base.endswith("_scalar_deleting_destructor"):
        class_name = symbol_base.removesuffix("_scalar_deleting_destructor")
        return name.startswith(f"??_G{class_name}@")
    return False


def read_coff_function(
    path: Path, symbol_base: str, requested_size: int
) -> tuple[str, bytes, frozenset[int], list[tuple[int, int, str]]]:
    data = path.read_bytes()
    if len(data) < 20 or struct.unpack_from("<H", data, 0)[0] != 0x14C:
        raise ValueError(f"{path} is not an i386 COFF object")
    section_count = struct.unpack_from("<H", data, 2)[0]
    symbol_pointer, symbol_count = struct.unpack_from("<II", data, 8)
    optional_header_size = struct.unpack_from("<H", data, 16)[0]
    section_table = 20 + optional_header_size
    string_table = symbol_pointer + symbol_count * 18

    sections: list[tuple[bytes, int, int, int, int]] = []
    for index in range(section_count):
        offset = section_table + 40 * index
        name = data[offset : offset + 8].rstrip(b"\0")
        raw_size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        relocation_pointer = struct.unpack_from("<I", data, offset + 24)[0]
        relocation_count = struct.unpack_from("<H", data, offset + 32)[0]
        sections.append(
            (name, raw_size, raw_pointer, relocation_pointer, relocation_count)
        )

    def symbol_name(offset: int) -> str:
        raw = data[offset : offset + 8]
        if raw[:4] == b"\0\0\0\0":
            string_offset = struct.unpack_from("<I", raw, 4)[0]
            start = string_table + string_offset
            end = data.find(b"\0", start)
            if end < 0:
                raise ValueError("unterminated COFF symbol string")
            return data[start:end].decode("ascii", "replace")
        return raw.rstrip(b"\0").decode("ascii", "replace")

    symbols: dict[int, tuple[str, int, int]] = {}
    matches: list[tuple[str, int, int]] = []
    index = 0
    while index < symbol_count:
        offset = symbol_pointer + index * 18
        name = symbol_name(offset)
        value = struct.unpack_from("<I", data, offset + 8)[0]
        section_number = struct.unpack_from("<h", data, offset + 12)[0]
        auxiliary_count = data[offset + 17]
        symbols[index] = (name, value, section_number)
        if (
            0 < section_number <= len(sections)
            and is_function_symbol(name, symbol_base)
        ):
            matches.append((name, value, section_number))
        index += 1 + auxiliary_count

    if len(matches) != 1:
        raise ValueError(
            f"{symbol_base}: expected one COFF symbol, found {matches[:6]}"
        )
    name, value, section_number = matches[0]
    section_name, raw_size, raw_pointer, relocation_pointer, relocation_count = (
        sections[section_number - 1]
    )
    if section_name != b".text":
        raise ValueError(f"{symbol_base}: unexpected section {section_name!r}")
    if value + requested_size > raw_size:
        raise ValueError(
            f"{symbol_base}: requested {requested_size} bytes exceeds section tail"
        )
    raw = data[raw_pointer + value : raw_pointer + value + requested_size]
    wild: set[int] = set()
    relocations: list[tuple[int, int, str]] = []
    for relocation_index in range(relocation_count):
        offset = relocation_pointer + relocation_index * 10
        virtual_address, symbol_index, relocation_type = struct.unpack_from(
            "<IIH", data, offset
        )
        function_offset = virtual_address - value
        if 0 <= function_offset <= requested_size - 4:
            wild.update(range(function_offset, function_offset + 4))
            relocation_name = symbols.get(symbol_index, ("?", 0, 0))[0]
            relocations.append(
                (function_offset, relocation_type, relocation_name)
            )
    return name, raw, frozenset(wild), relocations


def pe_bytes(path: Path, address: int, size: int) -> bytes:
    data = path.read_bytes()
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    section_count = struct.unpack_from("<H", data, pe_offset + 6)[0]
    optional_header_size = struct.unpack_from("<H", data, pe_offset + 20)[0]
    section_table = pe_offset + 24 + optional_header_size
    image_base = struct.unpack_from("<I", data, pe_offset + 52)[0]
    rva = address - image_base
    for index in range(section_count):
        offset = section_table + 40 * index
        virtual_size, virtual_address, raw_size, raw_pointer = struct.unpack_from(
            "<IIII", data, offset + 8
        )
        mapped_size = max(virtual_size, raw_size)
        if virtual_address <= rva < virtual_address + mapped_size:
            section_offset = rva - virtual_address
            end = section_offset + size
            if end > raw_size:
                raise ValueError(
                    f"0x{address:08X}+{size} extends beyond initialized PE bytes"
                )
            return data[raw_pointer + section_offset : raw_pointer + end]
    raise ValueError(f"address 0x{address:08X} is not mapped")


def normalize_instruction(text: str) -> str:
    text = text.split("#", 1)[0].strip().lower()
    if not text:
        return ""
    parts = text.split(None, 1)
    mnemonic = parts[0]
    operands = parts[1] if len(parts) == 2 else ""
    if mnemonic in BRANCH_MNEMONICS or mnemonic.startswith("j"):
        return f"{mnemonic} <relative>"

    def replace_address(match: re.Match[str]) -> str:
        value = int(match.group(1), 16)
        return "<absolute>" if value >= 0x10000 else match.group(0).lower()

    operands = ADDRESS_RE.sub(replace_address, operands)
    operands = re.sub(r"\s+", " ", operands)
    return f"{mnemonic} {operands}".rstrip()


def parse_objdump(output: str) -> list[tuple[int, str]]:
    instructions: list[tuple[int, str]] = []
    for line in output.splitlines():
        match = DISASM_RE.match(line)
        if not match:
            continue
        text = normalize_instruction(match.group(2))
        if text:
            instructions.append((int(match.group(1), 16), text))
    return instructions


def disassemble_target(objdump: str) -> tuple[list[int], list[str]]:
    output = subprocess.check_output(
        [objdump, "-d", "-Mintel", str(TARGET)], cwd=ROOT, text=True
    )
    instructions = parse_objdump(output)
    return [item[0] for item in instructions], [item[1] for item in instructions]


def structural_object_bytes(
    raw: bytes, relocations: Iterable[tuple[int, int, str]]
) -> bytes:
    patched = bytearray(raw)
    for offset, relocation_type, _ in relocations:
        if relocation_type == 0x0006:  # IMAGE_REL_I386_DIR32
            patched[offset : offset + 4] = struct.pack("<I", 0x12345678)
        elif relocation_type == 0x0014:  # IMAGE_REL_I386_REL32
            patched[offset : offset + 4] = b"\0\0\0\0"
    return bytes(patched)


def disassemble_blob(objdump: str, raw: bytes) -> list[str]:
    with tempfile.NamedTemporaryFile(prefix="th105-struct-", suffix=".bin") as stream:
        stream.write(raw)
        stream.flush()
        output = subprocess.check_output(
            [
                objdump,
                "-D",
                "-b",
                "binary",
                "-m",
                "i386",
                "-Mintel",
                stream.name,
            ],
            cwd=ROOT,
            text=True,
        )
    return [text for _, text in parse_objdump(output)]


def target_signature(
    addresses: list[int], texts: list[str], start: int, size: int
) -> list[str]:
    first = bisect.bisect_left(addresses, start)
    last = bisect.bisect_left(addresses, start + size)
    return texts[first:last]


def similarity(left: list[str], right: list[str]) -> float:
    return difflib.SequenceMatcher(a=left, b=right, autojunk=False).ratio()


def cache_digest(source: Path) -> str:
    digest = hashlib.sha256()
    inputs = [source, COMPILE_UNIT, ROOT / "config" / "tools.lock.toml"]
    inputs.extend(sorted((ROOT / "src").rglob("*.hpp")))
    for path in inputs:
        if not path.exists():
            continue
        relative = path.relative_to(ROOT).as_posix().encode()
        digest.update(len(relative).to_bytes(4, "little"))
        digest.update(relative)
        data = path.read_bytes()
        digest.update(len(data).to_bytes(8, "little"))
        digest.update(data)
    return digest.hexdigest()


def compile_source(
    source_relative: str,
    enable_gs: bool,
    cache_dir: Path,
    reuse_cache: bool,
) -> tuple[int, Path, str]:
    source = ROOT / source_relative
    digest = cache_digest(source)
    safe_name = source_relative.replace("/", "__").replace(".cpp", "")
    object_path = cache_dir / f"{safe_name}__gs{int(enable_gs)}__{digest[:16]}.obj"
    if reuse_cache and object_path.exists():
        return 0, object_path, "cached"
    cache_dir.mkdir(parents=True, exist_ok=True)
    environment = os.environ.copy()
    environment["TH105_ENABLE_GS"] = "1" if enable_gs else "0"
    process = subprocess.run(
        [str(COMPILE_UNIT), str(source), str(object_path)],
        cwd=ROOT,
        env=environment,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    return process.returncode, object_path, (process.stderr or process.stdout)[-2000:]


def load_current_candidates(
    objdump: str, maximum_size: int
) -> list[tuple[dict[str, str], int, list[str]]]:
    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        functions = list(csv.DictReader(stream))
    with ORIGINS.open(newline="", encoding="utf-8") as stream:
        origins = {row["address"]: row for row in csv.DictReader(stream)}
    addresses, texts = disassemble_target(objdump)
    candidates: list[tuple[dict[str, str], int, list[str]]] = []
    for row in functions:
        if origins.get(row["address"], {}).get("disposition") == "excluded":
            continue
        size = int(row["size"], 0)
        if size < 2 or size > maximum_size:
            continue
        signature = target_signature(addresses, texts, int(row["address"], 0), size)
        if signature:
            candidates.append((row, size, signature))
    return candidates


def historical_rows(
    revision: str, only_unconfigured: bool, sources: set[str], names: set[str]
) -> list[dict[str, str]]:
    rows = parse_csv_text(git_text(revision, "config/functions.csv"))
    configured: set[str] = set()
    if only_unconfigured:
        manifest = tomllib.loads(git_text(revision, "config/match-units.toml"))
        configured = {
            str(function.get("address"))
            for unit in manifest.get("units", {}).values()
            for function in unit.get("functions", [])
        }
    selected = []
    for row in rows:
        source = row.get("source_file", "")
        if row.get("status") != "matching" or not source.endswith(".cpp"):
            continue
        if only_unconfigured and row["address"] in configured:
            continue
        if not (ROOT / source).is_file():
            continue
        if sources and source not in sources:
            continue
        if names and row.get("proposed_name") not in names:
            continue
        selected.append(row)
    return selected


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--historical-rev", default=DEFAULT_HISTORICAL_REV)
    parser.add_argument("--only-unconfigured", action="store_true")
    parser.add_argument("--source", action="append", default=[])
    parser.add_argument("--name", action="append", default=[])
    parser.add_argument("--max-size", type=int, default=4096)
    parser.add_argument("--top", type=int, default=5)
    parser.add_argument("--minimum-score", type=float, default=0.72)
    parser.add_argument("--minimum-gap", type=float, default=0.08)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument("--cache-dir", type=Path, default=DEFAULT_CACHE)
    parser.add_argument("--reuse-cache", action="store_true")
    args = parser.parse_args()

    objdump = shutil.which("objdump")
    if not objdump:
        parser.error("GNU objdump is required for structural ranking")
    verify_target()
    subprocess.run(
        ["git", "cat-file", "-e", f"{args.historical_rev}^{{commit}}"],
        cwd=ROOT,
        check=True,
    )

    rows = historical_rows(
        args.historical_rev,
        args.only_unconfigured,
        set(args.source),
        set(args.name),
    )
    if not rows:
        print("no historical exact source rows matched the filters")
        return 0

    candidates = load_current_candidates(objdump, args.max_size)
    compiled: dict[tuple[str, bool], tuple[int, Path, str]] = {}
    for source in sorted({row["source_file"] for row in rows}):
        for enable_gs in (False, True):
            compiled[(source, enable_gs)] = compile_source(
                source, enable_gs, args.cache_dir, args.reuse_cache
            )

    results: list[dict[str, Any]] = []
    for row in rows:
        attempts: list[dict[str, Any]] = []
        best: dict[str, Any] | None = None
        historical_size = int(row["size"], 0)
        for enable_gs in (False, True):
            returncode, object_path, detail = compiled[
                (row["source_file"], enable_gs)
            ]
            if returncode:
                attempts.append(
                    {"enable_gs": enable_gs, "error": "compile", "detail": detail}
                )
                continue
            try:
                coff_symbol, raw, wild, relocations = read_coff_function(
                    object_path, row["proposed_name"], historical_size
                )
            except Exception as exc:  # analysis report should retain every failure
                attempts.append(
                    {"enable_gs": enable_gs, "error": "coff", "detail": str(exc)}
                )
                continue
            signature = disassemble_blob(
                objdump, structural_object_bytes(raw, relocations)
            )
            scored: list[tuple[float, dict[str, str], int]] = []
            for candidate, candidate_size, candidate_signature in candidates:
                if candidate_size < max(2, int(historical_size * 0.55)):
                    continue
                if candidate_size > int(historical_size * 1.8) + 8:
                    continue
                scored.append(
                    (
                        similarity(signature, candidate_signature),
                        candidate,
                        candidate_size,
                    )
                )
            scored.sort(
                key=lambda item: (
                    item[0],
                    -abs(item[2] - historical_size),
                    item[1]["address"],
                ),
                reverse=True,
            )
            top: list[dict[str, Any]] = []
            for score, candidate, candidate_size in scored[: args.top]:
                record: dict[str, Any] = {
                    "score": round(score, 4),
                    "address": candidate["address"],
                    "size": candidate_size,
                    "status": candidate["status"],
                    "current_name": candidate["current_name"],
                    "proposed_name": candidate["proposed_name"],
                }
                if candidate_size == historical_size:
                    target = pe_bytes(
                        TARGET, int(candidate["address"], 0), historical_size
                    )
                    mismatches = [
                        index
                        for index, (left, right) in enumerate(zip(raw, target))
                        if index not in wild and left != right
                    ]
                    record["non_relocation_mismatches"] = len(mismatches)
                    record["first_non_relocation_mismatch"] = (
                        f"0x{mismatches[0]:X}" if mismatches else None
                    )
                top.append(record)
            attempt = {
                "enable_gs": enable_gs,
                "coff_symbol": coff_symbol,
                "relocation_count": len(relocations),
                "top": top,
            }
            attempts.append(attempt)
            if top and (
                best is None or top[0]["score"] > best["top"][0]["score"]
            ):
                best = attempt
        result = {
            "historical_address": row["address"],
            "name": row["proposed_name"],
            "historical_size": historical_size,
            "source": row["source_file"],
            "module": row["module"],
            "attempts": attempts,
            "best": best,
        }
        results.append(result)
        if best and best["top"]:
            top = best["top"]
            gap = top[0]["score"] - (top[1]["score"] if len(top) > 1 else 0.0)
            if top[0]["score"] >= args.minimum_score and gap >= args.minimum_gap:
                mismatch = top[0].get("non_relocation_mismatches")
                mismatch_text = "n/a" if mismatch is None else str(mismatch)
                print(
                    f"{result['name']}: {result['historical_address']} "
                    f"({historical_size}) -> {top[0]['address']} ({top[0]['size']}) "
                    f"score={top[0]['score']:.4f} gap={gap:.4f} "
                    f"nonreloc_mismatches={mismatch_text} gs={int(best['enable_gs'])}"
                )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(results, indent=2) + "\n", encoding="utf-8")
    successful = sum(1 for result in results if result["best"])
    print(
        f"wrote {args.output}: {len(results)} historical rows, "
        f"{successful} COFF symbols ranked against {len(candidates)} current candidates"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
