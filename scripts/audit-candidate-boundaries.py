#!/usr/bin/env python3
"""Audit provisional callable reachability from exact TH10.5 1.06a PE bytes.

This is a boundary triage tool, not an origin classifier or a compiler-boundary
proof. Indirect jumps, outgoing tails, EH chunks, and adjacent metadata need
separate review. Reports belong below build/ or .analysis/.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources/th105.exe"
FUNCTIONS = ROOT / "config/functions.csv"
ORIGINS = ROOT / "config/function-origins.csv"


def pe_reader() -> tuple[str, object]:
    data = TARGET.read_bytes()
    with (ROOT / "config/target.toml").open("rb") as stream:
        expected = str(tomllib.load(stream)["target"]["sha256"])
    actual = hashlib.sha256(data).hexdigest()
    if actual != expected:
        raise ValueError(f"target SHA-256 mismatch: {actual} != {expected}")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    image_base = struct.unpack_from("<I", data, pe + 52)[0]
    sections = []
    for index in range(count):
        offset = pe + 24 + optional_size + 40 * index
        raw_size, raw_pointer = struct.unpack_from("<II", data, offset + 16)
        rva = struct.unpack_from("<I", data, offset + 12)[0]
        sections.append((image_base + rva, image_base + rva + raw_size, raw_pointer))

    def read(address: int, size: int) -> bytes:
        for start, end, pointer in sections:
            if start <= address and address + size <= end:
                result = data[pointer + address - start : pointer + address - start + size]
                if len(result) == size:
                    return result
        raise ValueError(f"0x{address:08X}+{size}: no initialized PE bytes")

    return actual, read


def runs(addresses: set[int]) -> list[list[str]]:
    spans: list[list[int]] = []
    for address in sorted(addresses):
        if not spans or address != spans[-1][1]:
            spans.append([address, address + 1])
        else:
            spans[-1][1] += 1
    return [[f"0x{start:08X}", f"0x{end:08X}"] for start, end in spans]


def analyze_body(read, start: int, size: int) -> dict[str, object]:
    end = start + size
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    pending = [start]
    instructions = {}
    returns = []
    traps = []
    outgoing = []
    indirect_exits = []
    invalid = []
    direct_calls = []
    while pending:
        address = pending.pop()
        if address in instructions:
            continue
        if not start <= address < end:
            outgoing.append(address)
            continue
        try:
            decoded = next(iter(decoder.disasm(read(address, min(15, end - address)), address, 1)), None)
        except ValueError:
            decoded = None
        if decoded is None:
            invalid.append(address)
            continue
        instructions[address] = decoded
        next_address = address + decoded.size
        direct = int(decoded.op_str, 16) if decoded.op_str.startswith("0x") else None
        name = decoded.mnemonic
        if name.startswith("ret"):
            returns.append({"address": f"0x{address:08X}", "kind": name})
        elif name in {"int3", "ud2"}:
            traps.append({"address": f"0x{address:08X}", "kind": name})
        elif name == "jmp":
            if direct is None:
                indirect_exits.append(address)
            else:
                pending.append(direct)
        elif name.startswith("j") or name.startswith("loop"):
            if direct is None:
                indirect_exits.append(address)
            else:
                pending.append(direct)
            pending.append(next_address)
        else:
            if name == "call" and direct is not None:
                direct_calls.append({"site": f"0x{address:08X}", "target": f"0x{direct:08X}"})
            pending.append(next_address)

    covered: set[int] = set()
    overlaps: set[int] = set()
    for address, decoded in instructions.items():
        for byte in range(address, address + decoded.size):
            if byte in covered:
                overlaps.add(byte)
            covered.add(byte)
    missing = set(range(start, end)) - covered

    def context(address: int) -> str | None:
        try:
            return read(address, 8).hex()
        except ValueError:
            return None

    return {
        "address": f"0x{start:08X}",
        "candidate_size": size,
        "body_sha256": hashlib.sha256(read(start, size)).hexdigest(),
        "reachable_instruction_count": len(instructions),
        "reachable_bytes": len(covered),
        "unreached_ranges": runs(missing),
        "return_sites": sorted(returns, key=lambda row: row["address"]),
        "trap_sites": sorted(traps, key=lambda row: row["address"]),
        "direct_calls": sorted(direct_calls, key=lambda row: row["site"]),
        "outgoing_direct_edges": [f"0x{address:08X}" for address in sorted(set(outgoing))],
        "indirect_jump_sites": [f"0x{address:08X}" for address in sorted(set(indirect_exits))],
        "invalid_decode_sites": [f"0x{address:08X}" for address in sorted(set(invalid))],
        "overlapping_decode_bytes": runs(overlaps),
        "preceding_bytes": context(start - 8),
        "following_bytes": context(end),
        "interpretation": "candidate reachability only; origin, TU boundary, indirect edges, and remote chunks require independent evidence",
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("addresses", nargs="*", help="candidate starts, e.g. 0x00420B90")
    parser.add_argument("--review", action="store_true", help="audit every origin-review row")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    if not args.addresses and not args.review:
        parser.error("supply addresses or --review")
    try:
        target_sha, read = pe_reader()
        with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
            rows = {row["address"].upper(): row for row in csv.DictReader(stream)}
        selected = {f"0x{int(address, 0):08X}".upper() for address in args.addresses}
        if args.review:
            with ORIGINS.open(newline="", encoding="utf-8") as stream:
                selected.update(
                    row["address"].upper() for row in csv.DictReader(stream)
                    if row["disposition"] == "review"
                )
        unknown = selected - rows.keys()
        if unknown:
            raise ValueError(f"untracked candidate starts: {sorted(unknown)}")
        results = []
        for address in sorted(selected):
            row = rows[address]
            result = analyze_body(read, int(address, 0), int(row["size"], 0))
            results.append(result)
    except (OSError, KeyError, ValueError, struct.error) as exc:
        parser.exit(2, f"boundary audit failed: {exc}\n")
    summary = {
        "candidate_count": len(results),
        "fully_reachable_without_visible_exit": sum(
            result["reachable_bytes"] == result["candidate_size"]
            and bool(result["return_sites"])
            and not result["outgoing_direct_edges"]
            and not result["indirect_jump_sites"]
            and not result["invalid_decode_sites"]
            and not result["overlapping_decode_bytes"]
            for result in results
        ),
        "with_unreached_bytes": sum(bool(result["unreached_ranges"]) for result in results),
        "with_indirect_jumps": sum(bool(result["indirect_jump_sites"]) for result in results),
        "with_outgoing_direct_edges": sum(bool(result["outgoing_direct_edges"]) for result in results),
        "with_invalid_or_overlapping_decode": sum(
            bool(result["invalid_decode_sites"] or result["overlapping_decode_bytes"])
            for result in results
        ),
    }
    if args.json:
        print(json.dumps({"schema": "th105-candidate-boundary-audit-v1", "target_sha256": target_sha, "summary": summary, "candidates": results}, indent=2))
    else:
        print(f"target {target_sha}: {summary}")
        for result in results:
            print(
                result["address"],
                f"{result['reachable_bytes']}/{result['candidate_size']} bytes",
                f"RET={len(result['return_sites'])}",
                f"unreached={len(result['unreached_ranges'])}",
                f"indirect={len(result['indirect_jump_sites'])}",
                f"outgoing={len(result['outgoing_direct_edges'])}",
            )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
