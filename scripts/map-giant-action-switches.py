#!/usr/bin/env python3
"""Validate and map byte-indexed switch metadata for giant Fighter roots.

The TH105 roster action-state roots use a common VC8 lowering for sparse integer
switches: an array of physical destination pointers plus a byte index table.
Those tables live outside the authored callable and are compiler metadata, but
their topology is strong source-ownership evidence.  This tool deliberately
fails closed if a table index is out of range or a decoded destination escapes
the reviewed callable boundary.
"""
from __future__ import annotations

import argparse
import csv
import json
import struct
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    from capstone.x86_const import X86_INS_CALL, X86_INS_RET
except ImportError as exc:  # pragma: no cover - repo environment pins capstone
    raise SystemExit(f"capstone is required: {exc}")


@dataclass(frozen=True)
class Section:
    name: str
    rva: int
    virtual_size: int
    raw_offset: int
    raw_size: int


class PeImage:
    def __init__(self, path: Path) -> None:
        self.path = path
        self.data = path.read_bytes()
        pe = struct.unpack_from("<I", self.data, 0x3C)[0]
        if self.data[pe : pe + 4] != b"PE\0\0":
            raise ValueError(f"{path}: missing PE signature")
        section_count = struct.unpack_from("<H", self.data, pe + 6)[0]
        optional = pe + 24
        optional_size = struct.unpack_from("<H", self.data, pe + 20)[0]
        self.image_base = struct.unpack_from("<I", self.data, optional + 28)[0]
        section_table = optional + optional_size
        sections: list[Section] = []
        for index in range(section_count):
            off = section_table + index * 40
            name = self.data[off : off + 8].split(b"\0", 1)[0].decode(
                "ascii", errors="replace"
            )
            virtual_size, rva, raw_size, raw_offset = struct.unpack_from(
                "<IIII", self.data, off + 8
            )
            sections.append(Section(name, rva, virtual_size, raw_offset, raw_size))
        self.sections = sections

    def file_offset(self, va: int) -> int:
        rva = va - self.image_base
        for section in self.sections:
            extent = max(section.virtual_size, section.raw_size)
            if section.rva <= rva < section.rva + extent:
                delta = rva - section.rva
                if delta >= section.raw_size:
                    raise ValueError(f"VA {va:#x} is in zero-fill, not raw PE data")
                return section.raw_offset + delta
        raise ValueError(f"VA {va:#x} is not mapped by {self.path}")

    def read(self, va: int, size: int) -> bytes:
        off = self.file_offset(va)
        out = self.data[off : off + size]
        if len(out) != size:
            raise ValueError(f"short PE read at {va:#x}+{size:#x}")
        return out

    def u32(self, va: int) -> int:
        return struct.unpack("<I", self.read(va, 4))[0]


def parse_int(value: int | str) -> int:
    return value if isinstance(value, int) else int(value, 0)


def compact_ranges(values: list[int]) -> str:
    values = sorted(values)
    if not values:
        return ""
    out: list[str] = []
    start = previous = values[0]
    for value in values[1:]:
        if value == previous + 1:
            previous = value
            continue
        out.append(str(start) if start == previous else f"{start}-{previous}")
        start = previous = value
    out.append(str(start) if start == previous else f"{start}-{previous}")
    return ",".join(out)


def load_function_rows(path: Path) -> list[tuple[int, int, dict[str, str]]]:
    rows: list[tuple[int, int, dict[str, str]]] = []
    with path.open(newline="") as handle:
        for row in csv.DictReader(handle):
            try:
                address = int(row["address"], 16)
                size = int(row["size"])
            except (KeyError, TypeError, ValueError):
                continue
            rows.append((address, address + size, row))
    return sorted(rows)


def owning_function(
    rows: list[tuple[int, int, dict[str, str]]], address: int
) -> dict[str, str] | None:
    lo, hi = 0, len(rows)
    while lo < hi:
        middle = (lo + hi) // 2
        if rows[middle][0] <= address:
            lo = middle + 1
        else:
            hi = middle
    if lo:
        start, end, row = rows[lo - 1]
        if start <= address < end:
            return row
    return None


def direct_calls(code: bytes, address: int) -> dict[int, int]:
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    calls: dict[int, int] = {}
    for instruction in decoder.disasm(code, address):
        if instruction.id != X86_INS_CALL or not instruction.operands:
            continue
        operand = instruction.operands[0]
        # Capstone x86 operand type 2 is immediate.  Avoid importing another
        # version-sensitive constant just for this small stable check.
        if operand.type != 2:
            continue
        target = int(operand.imm) & 0xFFFFFFFF
        calls[target] = calls.get(target, 0) + 1
    return calls


def raw_direct_call_census(code: bytes, address: int) -> tuple[int, set[int]]:
    # Reviewed giant callables contain code only; raw E8 census is retained as
    # a boundary regression guard because historical handoff counts use it.
    sites = 0
    targets: set[int] = set()
    for offset in range(max(0, len(code) - 4)):
        if code[offset] != 0xE8:
            continue
        displacement = struct.unpack_from("<i", code, offset + 1)[0]
        target = (address + offset + 5 + displacement) & 0xFFFFFFFF
        if 0x00400000 <= target < 0x00710000:
            sites += 1
            targets.add(target)
    return sites, targets


def select_root(manifest: dict[str, Any], name: str) -> dict[str, Any]:
    roots = manifest.get("roots", [])
    for root in roots:
        if root.get("name") == name:
            return root
    names = ", ".join(str(root.get("name")) for root in roots)
    raise ValueError(f"unknown root {name!r}; available: {names}")


def map_root(
    image: PeImage,
    functions: list[tuple[int, int, dict[str, str]]],
    root: dict[str, Any],
) -> dict[str, Any]:
    root_address = parse_int(root["address"])
    callable_end = parse_int(root["callable_end"])
    metadata_end = parse_int(root["metadata_end"])
    if not root_address < callable_end <= metadata_end:
        raise ValueError("invalid callable/metadata boundary ordering")

    callable_bytes = image.read(root_address, callable_end - root_address)
    raw_sites, raw_targets = raw_direct_call_census(callable_bytes, root_address)
    expected_sites = root.get("expected_direct_call_sites")
    if expected_sites is not None and raw_sites != int(expected_sites):
        raise ValueError(f"direct-call site census {raw_sites} != expected {expected_sites}")
    expected_targets = root.get("expected_direct_call_targets")
    if expected_targets is not None and len(raw_targets) != int(expected_targets):
        raise ValueError(
            f"direct-call target census {len(raw_targets)} != expected {expected_targets}"
        )
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    instruction_rets = sum(
        1 for instruction in decoder.disasm(callable_bytes, root_address)
        if instruction.id == X86_INS_RET
    )
    expected_rets = root.get("expected_ret_opcodes")
    if expected_rets is not None and instruction_rets != int(expected_rets):
        raise ValueError(
            f"instruction RET census {instruction_rets} != expected {expected_rets}"
        )

    decoded_regions: list[dict[str, Any]] = []
    all_destinations: set[int] = set()
    metadata_ranges: list[tuple[int, int, str]] = []
    for region in root.get("regions", []):
        case_min = int(region["case_min"])
        case_max = int(region["case_max"])
        destination_table = parse_int(region["destination_table"])
        destination_count = int(region["destination_count"])
        index_table = parse_int(region["index_table"])
        case_count = case_max - case_min + 1
        destinations = [
            image.u32(destination_table + index * 4)
            for index in range(destination_count)
        ]
        indices = image.read(index_table, case_count)
        if max(indices, default=0) >= destination_count:
            raise ValueError(
                f"{region['name']}: index {max(indices)} escapes {destination_count} destinations"
            )
        mapping = {
            case_min + offset: destinations[index]
            for offset, index in enumerate(indices)
        }
        escaped = sorted(
            {destination for destination in mapping.values() if not root_address <= destination < callable_end}
        )
        if escaped:
            raise ValueError(
                f"{region['name']}: destination(s) escape callable: "
                + ", ".join(f"{value:#x}" for value in escaped)
            )
        groups: dict[int, list[int]] = {}
        for case, destination in mapping.items():
            groups.setdefault(destination, []).append(case)
        expected_groups = region.get("expected_physical_groups")
        if expected_groups is not None and len(groups) != int(expected_groups):
            raise ValueError(
                f"{region['name']}: {len(groups)} groups != expected {expected_groups}"
            )
        all_destinations.update(groups)
        metadata_ranges.extend(
            [
                (destination_table, destination_table + destination_count * 4, f"{region['name']} destinations"),
                (index_table, index_table + case_count, f"{region['name']} indices"),
            ]
        )
        decoded_regions.append(
            {
                "name": region["name"],
                "case_min": case_min,
                "case_max": case_max,
                "groups": groups,
            }
        )

    expected_unique = root.get("expected_unique_destinations")
    if expected_unique is not None and len(all_destinations) != int(expected_unique):
        raise ValueError(
            f"{len(all_destinations)} unique destinations != expected {expected_unique}"
        )

    for start, end, label in metadata_ranges:
        if not callable_end <= start < end <= metadata_end:
            raise ValueError(
                f"{label} {start:#x}..{end:#x} escapes reviewed metadata island "
                f"{callable_end:#x}..{metadata_end:#x}"
            )

    ordered = sorted(all_destinations)
    next_destination = {
        value: ordered[index + 1] if index + 1 < len(ordered) else callable_end
        for index, value in enumerate(ordered)
    }

    destination_owners: dict[int, dict[str, list[int]]] = {}
    region_output: list[dict[str, Any]] = []
    for region in decoded_regions:
        groups_output: list[dict[str, Any]] = []
        for destination, cases in sorted(region["groups"].items()):
            end = next_destination[destination]
            calls = direct_calls(image.read(destination, end - destination), destination)
            call_output: list[dict[str, Any]] = []
            for target, count in sorted(calls.items(), key=lambda item: (-item[1], item[0])):
                row = owning_function(functions, target)
                call_output.append(
                    {
                        "address": target,
                        "count": count,
                        "name": (
                            (row.get("proposed_name") or row.get("current_name"))
                            if row
                            else None
                        ),
                        "status": row.get("status") if row else None,
                    }
                )
            groups_output.append(
                {
                    "destination": destination,
                    "offset": destination - root_address,
                    "span_to_next_destination": end - destination,
                    "cases": sorted(cases),
                    "calls": call_output,
                }
            )
            destination_owners.setdefault(destination, {})[region["name"]] = sorted(cases)
        region_output.append(
            {
                "name": region["name"],
                "case_min": region["case_min"],
                "case_max": region["case_max"],
                "physical_group_count": len(groups_output),
                "groups": groups_output,
            }
        )

    shared = []
    for destination, owners in sorted(destination_owners.items()):
        if len(owners) > 1:
            shared.append({"destination": destination, "regions": owners})

    return {
        "name": root["name"],
        "address": root_address,
        "callable_end": callable_end,
        "callable_size": callable_end - root_address,
        "metadata_end": metadata_end,
        "direct_call_sites": raw_sites,
        "direct_call_target_count": len(raw_targets),
        "ret_opcode_count": instruction_rets,
        "unique_destination_count": len(all_destinations),
        "regions": region_output,
        "cross_region_shared_destinations": shared,
    }


def format_text(result: dict[str, Any]) -> str:
    lines = [
        f"{result['name']}: {result['address']:#010x}..{result['callable_end']:#010x} "
        f"({result['callable_size']} callable bytes)",
        f"direct calls: {result['direct_call_sites']} sites / "
        f"{result['direct_call_target_count']} targets; RET opcodes: {result['ret_opcode_count']}",
        f"unique physical destinations: {result['unique_destination_count']}",
    ]
    for region in result["regions"]:
        lines.append(
            f"\n[{region['name']}] cases {region['case_min']}..{region['case_max']}: "
            f"{region['physical_group_count']} groups"
        )
        for group in region["groups"]:
            call_bits = []
            for call in group["calls"]:
                name = call["name"] or "?"
                status = call["status"] or "?"
                call_bits.append(
                    f"{name}@{call['address']:#010x}x{call['count']}[{status}]"
                )
            lines.append(
                f"  {group['destination']:#010x} +{group['offset']:#06x} "
                f"span={group['span_to_next_destination']:4d} "
                f"cases={compact_ranges(group['cases']):<30} "
                f"calls={'; '.join(call_bits)}"
            )
    lines.append("\n[cross-region shared destinations]")
    if not result["cross_region_shared_destinations"]:
        lines.append("  none")
    else:
        for item in result["cross_region_shared_destinations"]:
            owners = "; ".join(
                f"{name}:{compact_ranges(cases)}"
                for name, cases in item["regions"].items()
            )
            lines.append(f"  {item['destination']:#010x} {owners}")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("root", help="root name from config/giant-action-switches.toml")
    parser.add_argument("--manifest", type=Path, default=Path("config/giant-action-switches.toml"))
    parser.add_argument("--pe", type=Path, default=Path("resources/th105.exe"))
    parser.add_argument("--functions", type=Path, default=Path("config/functions.csv"))
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    manifest = tomllib.loads(args.manifest.read_text())
    root = select_root(manifest, args.root)
    result = map_root(PeImage(args.pe), load_function_rows(args.functions), root)
    if args.json:
        json.dump(result, sys.stdout, indent=2)
        sys.stdout.write("\n")
    else:
        print(format_text(result))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
