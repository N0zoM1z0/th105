#!/usr/bin/env python3
"""Compare giant Fighter byte-index switch ownership against a compiled COFF object.

This is the candidate-side companion to map-giant-action-switches.py.  It never
uses compiler-generated $LN symbol numbers.  Instead it finds each VC8 sparse
switch destination table by relocation topology: N consecutive IMAGE_REL_I386_DIR32
relocations to local .text symbols followed immediately by a byte index table
whose values are all < N.  The manifest supplies only target-backed case ranges
and expected physical-group counts.

The output is source-ownership evidence, not exact-byte acceptance.  A candidate
can have the right action grouping while still failing the canonical comparator.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import struct
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path
from typing import Any

IMAGE_REL_I386_DIR32 = 0x0006


def load_target_mapper() -> Any:
    path = Path(__file__).with_name("map-giant-action-switches.py")
    spec = importlib.util.spec_from_file_location("th105_giant_target_mapper", path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load target mapper {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


@dataclass(frozen=True)
class CoffSection:
    name: str
    raw_size: int
    raw_offset: int
    reloc_offset: int
    reloc_count: int


@dataclass(frozen=True)
class CoffSymbol:
    name: str
    value: int
    section_number: int


class CoffObject:
    def __init__(self, path: Path) -> None:
        self.path = path
        self.data = path.read_bytes()
        if len(self.data) < 20:
            raise ValueError(f"{path}: truncated COFF header")
        machine, section_count = struct.unpack_from("<HH", self.data, 0)
        if machine != 0x014C:
            raise ValueError(f"{path}: expected i386 COFF machine 0x14c, got {machine:#x}")
        symbol_table, symbol_count = struct.unpack_from("<II", self.data, 8)
        optional_size = struct.unpack_from("<H", self.data, 16)[0]
        section_table = 20 + optional_size
        sections: list[CoffSection] = []
        for index in range(section_count):
            off = section_table + index * 40
            if off + 40 > len(self.data):
                raise ValueError(f"{path}: truncated section table")
            name = self.data[off : off + 8].split(b"\0", 1)[0].decode(
                "ascii", errors="replace"
            )
            raw_size, raw_offset = struct.unpack_from("<II", self.data, off + 16)
            reloc_offset = struct.unpack_from("<I", self.data, off + 24)[0]
            reloc_count = struct.unpack_from("<H", self.data, off + 32)[0]
            sections.append(CoffSection(name, raw_size, raw_offset, reloc_offset, reloc_count))
        self.sections = sections
        self.text_section_number = next(
            index + 1 for index, section in enumerate(sections) if section.name == ".text"
        )
        self.text_section = sections[self.text_section_number - 1]
        self.text = self._read_raw(self.text_section.raw_offset, self.text_section.raw_size)

        string_table = symbol_table + symbol_count * 18
        if string_table + 4 > len(self.data):
            raise ValueError(f"{path}: truncated COFF string table")
        string_size = struct.unpack_from("<I", self.data, string_table)[0]
        if string_size < 4 or string_table + string_size > len(self.data):
            raise ValueError(f"{path}: invalid COFF string table size {string_size}")

        def symbol_name(off: int) -> str:
            raw = self.data[off : off + 8]
            if raw[:4] == b"\0\0\0\0":
                string_off = struct.unpack_from("<I", raw, 4)[0]
                start = string_table + string_off
                if not string_table + 4 <= start < string_table + string_size:
                    raise ValueError(f"{path}: bad COFF symbol string offset {string_off}")
                end = self.data.find(b"\0", start, string_table + string_size)
                if end < 0:
                    raise ValueError(f"{path}: unterminated COFF symbol name")
                return self.data[start:end].decode("ascii", errors="replace")
            return raw.rstrip(b"\0").decode("ascii", errors="replace")

        symbols: dict[int, CoffSymbol] = {}
        index = 0
        while index < symbol_count:
            off = symbol_table + index * 18
            if off + 18 > len(self.data):
                raise ValueError(f"{path}: truncated COFF symbol table")
            name = symbol_name(off)
            value = struct.unpack_from("<I", self.data, off + 8)[0]
            section_number = struct.unpack_from("<h", self.data, off + 12)[0]
            aux_count = self.data[off + 17]
            symbols[index] = CoffSymbol(name, value, section_number)
            index += 1 + aux_count
        self.symbols = symbols

        relocations: dict[int, tuple[CoffSymbol, int]] = {}
        section = self.text_section
        for index in range(section.reloc_count):
            off = section.reloc_offset + index * 10
            if off + 10 > len(self.data):
                raise ValueError(f"{path}: truncated .text relocation table")
            address, symbol_index, reloc_type = struct.unpack_from("<IIH", self.data, off)
            symbol = symbols.get(symbol_index)
            if symbol is None:
                raise ValueError(f"{path}: relocation references unknown symbol {symbol_index}")
            if address in relocations:
                raise ValueError(f"{path}: duplicate .text relocation at {address:#x}")
            relocations[address] = (symbol, reloc_type)
        self.relocations = relocations

    def _read_raw(self, offset: int, size: int) -> bytes:
        out = self.data[offset : offset + size]
        if len(out) != size:
            raise ValueError(f"{self.path}: short raw read {offset:#x}+{size:#x}")
        return out

    def u32_text(self, offset: int) -> int:
        if not 0 <= offset <= len(self.text) - 4:
            raise ValueError(f"{self.path}: .text u32 read escapes at {offset:#x}")
        return struct.unpack_from("<I", self.text, offset)[0]

    def relocated_text_value(self, offset: int) -> int:
        item = self.relocations.get(offset)
        if item is None:
            raise ValueError(f"{self.path}: missing relocation at .text+{offset:#x}")
        symbol, reloc_type = item
        if reloc_type != IMAGE_REL_I386_DIR32:
            raise ValueError(
                f"{self.path}: relocation .text+{offset:#x} type {reloc_type:#x}, expected DIR32"
            )
        if symbol.section_number != self.text_section_number:
            raise ValueError(
                f"{self.path}: relocation .text+{offset:#x} targets {symbol.name!r} "
                f"in section {symbol.section_number}, expected local .text"
            )
        return symbol.value + self.u32_text(offset)


def candidate_region_tables(
    obj: CoffObject, root: dict[str, Any]
) -> list[dict[str, Any]]:
    out: list[dict[str, Any]] = []
    used_starts: set[int] = set()
    for region in root.get("regions", []):
        case_min = int(region["case_min"])
        case_max = int(region["case_max"])
        destination_count = int(region["destination_count"])
        case_count = case_max - case_min + 1
        expected_groups = int(region.get("expected_physical_groups", destination_count))
        candidates: list[tuple[int, int, list[int], bytes]] = []
        for start in sorted(obj.relocations):
            if start in used_starts:
                continue
            relocation_offsets = [start + index * 4 for index in range(destination_count)]
            if not all(offset in obj.relocations for offset in relocation_offsets):
                continue
            try:
                destinations = [obj.relocated_text_value(offset) for offset in relocation_offsets]
            except ValueError:
                continue
            if any(not 0 <= destination < len(obj.text) for destination in destinations):
                continue
            index_start = start + destination_count * 4
            index_end = index_start + case_count
            if index_end > len(obj.text):
                continue
            indices = obj.text[index_start:index_end]
            if not indices or max(indices) >= destination_count:
                continue
            mapping_destinations = {destinations[index] for index in indices}
            if len(mapping_destinations) != expected_groups:
                continue
            candidates.append((start, index_start, destinations, indices))
        if len(candidates) != 1:
            detail = ", ".join(f"{start:#x}" for start, *_ in candidates) or "none"
            raise ValueError(
                f"{region['name']}: expected one candidate COFF switch table, found "
                f"{len(candidates)} ({detail})"
            )
        start, index_start, destinations, indices = candidates[0]
        used_starts.add(start)
        mapping = {
            case_min + offset: destinations[index]
            for offset, index in enumerate(indices)
        }
        groups: dict[int, list[int]] = {}
        for case, destination in mapping.items():
            groups.setdefault(destination, []).append(case)
        out.append(
            {
                "name": region["name"],
                "case_min": case_min,
                "case_max": case_max,
                "destination_table_offset": start,
                "index_table_offset": index_start,
                "mapping": mapping,
                "groups": groups,
            }
        )
    return out


def build_candidate_map(obj: CoffObject, root: dict[str, Any]) -> dict[str, Any]:
    regions = candidate_region_tables(obj, root)
    all_destinations = sorted(
        {destination for region in regions for destination in region["groups"]}
    )
    expected_unique = int(root.get("expected_unique_destinations", len(all_destinations)))
    if len(all_destinations) != expected_unique:
        raise ValueError(
            f"candidate has {len(all_destinations)} unique destinations; expected {expected_unique}"
        )
    metadata_start = min(region["destination_table_offset"] for region in regions)
    if any(destination >= metadata_start for destination in all_destinations):
        raise ValueError("candidate switch destination escapes candidate callable into metadata")
    next_destination = {
        destination: (
            all_destinations[index + 1]
            if index + 1 < len(all_destinations)
            else metadata_start
        )
        for index, destination in enumerate(all_destinations)
    }
    region_output: list[dict[str, Any]] = []
    for region in regions:
        groups = []
        for destination, cases in sorted(region["groups"].items()):
            groups.append(
                {
                    "destination": destination,
                    "offset": destination,
                    "span_to_next_destination": next_destination[destination] - destination,
                    "cases": sorted(cases),
                }
            )
        region_output.append(
            {
                "name": region["name"],
                "case_min": region["case_min"],
                "case_max": region["case_max"],
                "physical_group_count": len(groups),
                "destination_table_offset": region["destination_table_offset"],
                "index_table_offset": region["index_table_offset"],
                "groups": groups,
                "mapping": region["mapping"],
            }
        )
    return {
        "object": str(obj.path),
        "text_size": len(obj.text),
        "metadata_start": metadata_start,
        "unique_destination_count": len(all_destinations),
        "regions": region_output,
    }


def compare_maps(target: dict[str, Any], candidate: dict[str, Any]) -> dict[str, Any]:
    candidate_regions = {region["name"]: region for region in candidate["regions"]}
    rows: list[dict[str, Any]] = []
    split_count = 0
    for target_region in target["regions"]:
        candidate_region = candidate_regions.get(target_region["name"])
        if candidate_region is None:
            raise ValueError(f"candidate missing region {target_region['name']}")
        mapping: dict[int, int] = candidate_region["mapping"]
        candidate_groups_by_dest = {
            group["destination"]: group for group in candidate_region["groups"]
        }
        for target_group in target_region["groups"]:
            candidate_destinations = sorted({mapping[case] for case in target_group["cases"]})
            if len(candidate_destinations) != 1:
                split_count += 1
                rows.append(
                    {
                        "region": target_region["name"],
                        "cases": target_group["cases"],
                        "target_offset": target_group["offset"],
                        "target_span": target_group["span_to_next_destination"],
                        "candidate_offsets": candidate_destinations,
                        "candidate_span": None,
                        "drift": None,
                        "span_diff": None,
                        "split": True,
                    }
                )
                continue
            candidate_destination = candidate_destinations[0]
            candidate_group = candidate_groups_by_dest[candidate_destination]
            candidate_span = candidate_group["span_to_next_destination"]
            rows.append(
                {
                    "region": target_region["name"],
                    "cases": target_group["cases"],
                    "target_offset": target_group["offset"],
                    "target_span": target_group["span_to_next_destination"],
                    "candidate_offsets": candidate_destinations,
                    "candidate_span": candidate_span,
                    "drift": target_group["offset"] - candidate_destination,
                    "span_diff": target_group["span_to_next_destination"] - candidate_span,
                    "split": False,
                }
            )
    return {
        "name": target["name"],
        "target_callable_size": target["callable_size"],
        "target_metadata_size": target["metadata_end"] - target["address"],
        "candidate_text_size": candidate["text_size"],
        "candidate_metadata_start": candidate["metadata_start"],
        "candidate_unique_destination_count": candidate["unique_destination_count"],
        "split_target_group_count": split_count,
        "candidate_tables": [
            {
                "name": region["name"],
                "destination_table_offset": region["destination_table_offset"],
                "index_table_offset": region["index_table_offset"],
                "physical_group_count": region["physical_group_count"],
            }
            for region in candidate["regions"]
        ],
        "rows": rows,
    }


def format_text(result: dict[str, Any], compact_ranges: Any) -> str:
    lines = [
        f"{result['name']}: target callable={result['target_callable_size']} "
        f"target through metadata={result['target_metadata_size']} "
        f"candidate .text={result['candidate_text_size']}",
        f"candidate metadata starts +{result['candidate_metadata_start']:#06x}; "
        f"physical destinations={result['candidate_unique_destination_count']}; "
        f"target-group splits={result['split_target_group_count']}",
    ]
    for table in result["candidate_tables"]:
        lines.append(
            f"  [{table['name']}] dest=+{table['destination_table_offset']:#06x} "
            f"index=+{table['index_table_offset']:#06x} "
            f"groups={table['physical_group_count']}"
        )
    current_region = None
    for row in result["rows"]:
        if row["region"] != current_region:
            current_region = row["region"]
            lines.append(f"\n[{current_region}]")
        cases = compact_ranges(row["cases"])
        if row["split"]:
            destinations = ",".join(f"+{value:#06x}" for value in row["candidate_offsets"])
            lines.append(
                f"  cases={cases:<24} target=+{row['target_offset']:#06x} "
                f"span={row['target_span']:4d} candidate=SPLIT({destinations})"
            )
        else:
            lines.append(
                f"  cases={cases:<24} target=+{row['target_offset']:#06x} "
                f"candidate=+{row['candidate_offsets'][0]:#06x} "
                f"drift={row['drift']:+5d} span {row['target_span']:4d}/{row['candidate_span']:4d} "
                f"diff={row['span_diff']:+5d}"
            )
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("root", help="root name from config/giant-action-switches.toml")
    parser.add_argument("object", type=Path, help="compiled i386 COFF object containing the giant root")
    parser.add_argument("--manifest", type=Path, default=Path("config/giant-action-switches.toml"))
    parser.add_argument("--pe", type=Path, default=Path("resources/th105.exe"))
    parser.add_argument("--functions", type=Path, default=Path("config/functions.csv"))
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    target_mapper = load_target_mapper()
    manifest = tomllib.loads(args.manifest.read_text())
    root = target_mapper.select_root(manifest, args.root)
    target = target_mapper.map_root(
        target_mapper.PeImage(args.pe),
        target_mapper.load_function_rows(args.functions),
        root,
    )
    candidate = build_candidate_map(CoffObject(args.object), root)
    result = compare_maps(target, candidate)
    if args.json:
        json.dump(result, sys.stdout, indent=2)
        sys.stdout.write("\n")
    else:
        print(format_text(result, target_mapper.compact_ranges))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
