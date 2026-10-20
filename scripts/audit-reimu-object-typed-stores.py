#!/usr/bin/env python3
"""Check root496540's ordered field writes and902 float-member stores.

Uses original helper execution and the existing finite prefix fixtures. Opaque
calls remain entry stops. Neither this audit nor its instruction diagnostics
establishes whole-root exactness, original source spelling or arbitrary aliases.
"""

from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import importlib.util
import json
from pathlib import Path
import time
import tomllib

from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "typed_store_native", ROOT / "scripts/audit-reimu-object-scalar-actions.py"
)
native = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(native)

# First writes of fifteen X/Y pairs and855's368/366 pair, from the attested PE.
PAIR_STARTS = (
    0x496624, 0x496989, 0x496B16, 0x496B44,
    0x497446, 0x497698, 0x497706, 0x497EF5,
    0x49906C, 0x499298, 0x49935E, 0x49997B,
    0x49A179, 0x49B7A5, 0x49B7B1, 0x49BF13,
)
BOUNDARY_FIELDS = tuple(range(0x7A8, 0x7C8, 4))


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def stack_float(row):
    return (
        len(row.operands) == 1
        and row.operands[0].type == x.X86_OP_MEM
        and row.operands[0].size == 4
        and row.operands[0].mem.base == x.X86_REG_ESP
        and row.operands[0].mem.index == 0
    )


def boundary_packets(rows):
    """Describe real stores; require a float spill/reload, without masking bytes."""
    packets = []
    for index, row in enumerate(rows):
        if not (
            row.mnemonic == "fstp"
            and len(row.operands) == 1
            and row.operands[0].type == x.X86_OP_MEM
            and row.operands[0].size == 4
            and row.operands[0].mem.base in
            (x.X86_REG_EAX, x.X86_REG_ECX, x.X86_REG_EDX)
            and row.operands[0].mem.index == 0
            and row.operands[0].mem.disp in BOUNDARY_FIELDS
        ):
            continue
        before = rows[max(0, index - 2):index]
        rounded = (
            len(before) == 2
            and before[0].mnemonic == "fstp"
            and before[1].mnemonic == "fld"
            and all(stack_float(r) for r in before)
            and before[0].operands[0].mem.disp == before[1].operands[0].mem.disp
        )
        instructions = before + [row]
        packets.append({
            "field": row.operands[0].mem.disp,
            "store": row.address,
            "float_spill_reload": rounded,
            "instructions": [
                {"address": r.address, "bytes": r.bytes.hex(),
                 "mnemonic": r.mnemonic, "operands": r.op_str}
                for r in instructions
            ],
        })
    fields = Counter(p["field"] for p in packets)
    return {
        "packets": packets,
        "one_store_per_field": fields == Counter(BOUNDARY_FIELDS),
        "all_float_spill_reload": len(packets) == 8
        and all(p["float_spill_reload"] for p in packets),
    }


def heading_packet(rows):
    """822's post-opaque parameter/heading pair is a static obligation."""
    found = []
    for index, row in enumerate(rows[:-1]):
        following = rows[index + 1]
        if not (
            row.mnemonic == following.mnemonic == "fst"
            and row.operands[0].type == following.operands[0].type == x.X86_OP_MEM
            and row.operands[0].size == following.operands[0].size == 4
            and row.operands[0].mem.base in
            (x.X86_REG_EAX, x.X86_REG_ECX, x.X86_REG_EDX, x.X86_REG_EDI)
            and row.operands[0].mem.index == row.operands[0].mem.disp == 0
            and following.operands[0].mem.base == x.X86_REG_ESI
            and following.operands[0].mem.index == 0
            and following.operands[0].mem.disp == 0x12C
        ):
            continue
        found.append({
            "start": row.address,
            "instructions": [
                {"address": r.address, "bytes": r.bytes.hex(),
                 "mnemonic": r.mnemonic, "operands": r.op_str}
                for r in (row, following)
            ],
        })
    return {"one_ordered_pair": len(found) == 1, "packets": found}


class StoreProbe(native.Probe):
    def evaluate(self, case):
        self.events = []
        result = super().evaluate(case)
        return result, self.events

    def write(self, uc, access, address, size, value, user):
        for region, base, length in (
            ("object", native.OWNER, 0x388),
            ("owner", native.FIGHTER, 0x800),
            ("parameters", native.entry.PARAMETERS, 16),
        ):
            if base <= address and address + size <= base + length:
                self.events.append((
                    uc.reg_read(native.r.UC_X86_REG_EIP), region,
                    address - base, size, value & ((1 << (size * 8)) - 1),
                ))
                break
        super().write(uc, access, address, size, value, user)


def audit(obj, cohorts):
    inputs = [
        Path(__file__), obj, ROOT / "resources/th105.exe",
        ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
        ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
        ROOT / "scripts/audit-reimu-object-scalar-actions.py",
        ROOT / "scripts/audit-reimu-object-update-target.py",
        ROOT / "scripts/audit-reimu-object-entry-calls.py",
        ROOT / "scripts/audit-common-fighter-animation-paths.py",
        ROOT / "scripts/iku_native_math.py",
        ROOT / "scripts/compare-function.py",
    ]
    pins = {str(p): digest(p) for p in inputs}
    code = native.export(obj)  # Attests the complete target root and relocations.
    pe = native.pefile.PE(str(ROOT / "resources/th105.exe"))
    target_rows = [
        r for start, end in native.facts.RANGES
        for r in native.facts.decode(pe.get_data(start - 0x400000, end - start), start)
    ]
    # COFF switch metadata is not executable. Decode only the reviewed prefix.
    root = native.m.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "reimu-object-vslot28",
    )
    mapping = native.m.build_candidate_map(
        native.m.CoffObject(obj, symbol_base=native.SYMBOL), root
    )
    source_rows = native.facts.decode(code[:mapping["metadata_start"]], native.S)
    target_packets = boundary_packets(target_rows)
    source_packets = boundary_packets(source_rows)
    target_heading = heading_packet(target_rows)
    source_heading = heading_packet(source_rows)
    if not target_packets["one_store_per_field"] or not target_packets["all_float_spill_reload"]:
        raise ValueError("target902 store evidence differs")
    if (
        not target_heading["one_ordered_pair"]
        or target_heading["packets"][0]["start"] != 0x499F14
    ):
        raise ValueError("target822 parameter/heading order differs")

    image = bytearray(pe.get_memory_mapped_image())
    math = native.load("typed_store_math", "scripts/iku_native_math.py")
    table, lookup_receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0:0x2FE8B0 + len(table)] = table
    image = bytes(image)
    seeds = native.seed_fixtures(image, (0, 5489, 0xFFFFFFFF, 79, 137))
    surfaces, surface_receipt = native.surface_fixtures(image)
    target = StoreProbe(image, seeds=seeds, surfaces=surfaces)
    source = StoreProbe(image, code, seeds=seeds, surfaces=surfaces)
    generators = (
        native.cases, native.projectile_cases, native.sequence_cases,
        native.late_projectile_cases, native.owner_projectile_cases,
        native.follow_projectile_cases, native.sibling_projectile_cases,
        native.orbit_projectile_cases, native.upper_projectile_cases,
        native.actions_903_905_cases, native.final_action_cases,
    )
    cases = [case for generate in generators for case in generate()]
    available = {c.get("cohort", "scalar") for c in cases}
    if set(cohorts) - available:
        raise ValueError("unknown cohort")
    if cohorts:
        cases = [c for c in cases if c.get("cohort", "scalar") in cohorts]
    output_failures, event_failures = [], []
    output_count = event_count = 0
    action_failures = Counter()
    visits = Counter()
    witnesses = defaultdict(set)
    started = time.monotonic()
    for index, case in enumerate(cases):
        a, ae = target.evaluate(case)
        b, be = source.evaluate(case)
        visits.update(e[0] for e in ae)
        if a != b:
            output_count += 1
            if len(output_failures) < 20:
                output_failures.append({
                    "index": index, "case": case,
                    "fields": [key for key in a if a[key] != b[key]],
                })
        if [e[1:] for e in ae] != [e[1:] for e in be]:
            event_count += 1
            action_failures[case["action"]] += 1
            if len(event_failures) < 20:
                event_failures.append({
                    "index": index, "case": case, "target": ae, "source": be,
                })
        else:
            for ta, sa in zip(ae, be):
                if ta[0] in PAIR_STARTS:
                    witnesses[ta[0]].add(sa[0])
        if index % 5000 == 0:
            print(index, len(cases), "seconds", round(time.monotonic() - started, 1),
                  "outputs", output_count, "events", event_count, flush=True)
    required = PAIR_STARTS + tuple(p["store"] for p in target_packets["packets"])
    coverage = {hex(a): visits[a] for a in required}
    complete_coverage = all(coverage.values())
    if pins != {str(p): digest(p) for p in inputs}:
        raise ValueError("audit inputs changed during execution")
    equal = (
        output_count == event_count == 0 and complete_coverage
        and source_packets["one_store_per_field"]
        and source_packets["all_float_spill_reload"]
        and source_heading["one_ordered_pair"]
    )
    return {
        "schema": "th105-reimu-object-typed-stores-v1",
        "result": "equal_scoped_typed_stores" if equal else "different_or_uncovered",
        "scope": "finite original-code prefixes; object/owner/parameter write order and "
        "results; opaque entry stops; no exact or arbitrary-alias claim",
        "case_count": len(cases),
        "input_sha256": hashlib.sha256(json.dumps(cases, sort_keys=True).encode()).hexdigest(),
        "cohorts": dict(Counter(c.get("cohort", "scalar") for c in cases)),
        "output_difference_count": output_count, "output_differences": output_failures,
        "event_difference_count": event_count, "event_differences": event_failures,
        "event_failures_by_action": dict(action_failures),
        "target_store_coverage": coverage, "complete_store_coverage": complete_coverage,
        "pair_first_store_witnesses": {
            hex(a): [hex(b) for b in sorted(values)]
            for a, values in sorted(witnesses.items())
        },
        "boundary_packets": {"target": target_packets, "source": source_packets},
        "post_opaque_heading_pair": {
            "target": target_heading, "source": source_heading,
            "target_execution_count": visits[0x499F14],
            "scope": "static instruction order; a zero execution count is "
            "uncovered, not evidence of execution through the opaque prefix",
        },
        "lookup_initialization": lookup_receipt,
        "surface_initialization": surface_receipt,
        "candidate_sha256": hashlib.sha256(code).hexdigest(),
        "build_provenance_verified": False,
        "input_pins_before_and_after": pins,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--cohort", action="append", default=[])
    args = parser.parse_args()
    report = audit(args.object, args.cohort)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in (
        "result", "case_count", "output_difference_count", "event_difference_count",
        "complete_store_coverage",
    )}))
    return int(report["result"] != "equal_scoped_typed_stores")


if __name__ == "__main__":
    raise SystemExit(main())
