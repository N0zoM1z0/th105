#!/usr/bin/env python3
"""Attest Iku's whole root, selector coverage and an optional real COFF CFG.

The generated packets are evidence, not byte acceptance or new helper bounds.
"""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

from giant_owner_audit import decode
from iku_opening_actions import OPENING_ENTRIES
from iku_middle_actions import MIDDLE_ENTRIES
from iku_upper_actions import ENTRIES
from linked_pe import comparator
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
START, SIZE = 0x620920, 59038
ROOT_SHA = "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea"


def call_census(rows):
    calls = Counter()
    for row in rows:
        if row.group(capstone.CS_GRP_CALL):
            operand = row.operands[0]
            calls[hex(operand.imm) if operand.type == X86_OP_IMM else "register"] += 1
    return dict(sorted(calls.items()))


def load_script(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def target_audit(canonical):
    body = canonical.target_bytes(START, SIZE)
    if hashlib.sha256(body).hexdigest() != ROOT_SHA:
        raise ValueError("Iku root differs")
    rows = {row.address: row for row in decode(body, START)}
    tables = {}
    for jump, table, count in ((0x620B1B, 0x62EFC0, 33), (0x62374C, 0x62F128, 42), (0x6290B3, 0x62F2C8, 35)):
        tables[jump] = struct.unpack("<" + "I" * count, canonical.target_bytes(table, count * 4))
    entries = {}
    for first, table, count, lookup, length in ((0, 0x62EFC0, 33, 0x62F044, 227),
            (301, 0x62F128, 42, 0x62F1D0, 247), (561, 0x62F2C8, 35, 0x62F354, 238)):
        destinations = struct.unpack("<" + "I" * count, canonical.target_bytes(table, count * 4))
        entries.update({first + i: destinations[index] for i, index in enumerate(canonical.target_bytes(lookup, length))
                        if destinations[index] != 0x62EFA5})
    entries.update({300: 0x62360E, 560: 0x628EAD})
    if entries != OPENING_ENTRIES | MIDDLE_ENTRIES | ENTRIES or len(entries) != 110:
        raise ValueError("whole selector map differs")
    def closure(starts):
        todo, seen = list(starts), set()
        while todo:
            address = todo.pop()
            if address in seen:
                continue
            if address not in rows:
                raise ValueError("whole target edge leaves root or enters an instruction")
            seen.add(address)
            row = rows[address]
            if row.group(capstone.CS_GRP_RET):
                continue
            edges = [address + row.size]
            if row.group(capstone.CS_GRP_JUMP):
                if row.operands[0].type == X86_OP_IMM:
                    edges = [row.operands[0].imm] + ([] if row.mnemonic == "jmp" else edges)
                elif address in tables:
                    edges = list(tables[address])
                else:
                    raise ValueError("unknown target indirect jump")
            todo.extend(edges)
        return seen

    seen = closure([START])
    if set(rows) != seen or (len(rows), sum(row.size for row in rows.values())) != (15132, SIZE):
        raise ValueError("whole target coverage differs")
    action_default = closure([*entries.values(), 0x62EFA5])
    route_bytes = sum(rows[a].size for a in seen - action_default)
    action_bytes = sum(rows[a].size for a in action_default)
    if (route_bytes, action_bytes) != (591, 58447):
        raise ValueError("whole action/default and routing unions differ")
    # PF/CF/C3 decoding is essential: these four seq3/8 branches reject NaN.
    if [(rows[a].mnemonic, rows[a].op_str) for a in (0x622823, 0x622863, 0x6229EA, 0x622A54)] != [
            ("jp", "0x622873"), ("jne", "0x622871"), ("jp", "0x622a21"), ("jne", "0x622a8e")]:
        raise ValueError("ordered glide exit-facing facts differ")
    return {"instructions": len(rows), "bytes": SIZE,
            "calls": call_census(rows.values()),
            "returns": sum(row.group(capstone.CS_GRP_RET) for row in rows.values()),
            "actions": len(entries), "opening_entries": OPENING_ENTRIES,
            "prelude_and_route_bytes": route_bytes, "action_and_default_union_bytes": action_bytes,
            "unreached": [], "indirect_switch_sites": sorted(tables),
            "ordered_nan_rejection_sites": [0x622823, 0x622863, 0x6229EA, 0x622A54]}


def candidate_audit(canonical, path):
    coff = load_script("iku_full_coff", "scripts/compare-giant-action-switches.py")
    obj = coff.CoffObject(path)
    root = next(symbol for symbol in obj.symbols.values() if symbol.name.startswith("?dispatch_action_state_vslot28@"))
    section = obj.sections[root.section_number - 1]
    local_fields, local_calls = set(), []
    for i in range(section.reloc_count):
        field, number, kind = struct.unpack_from("<IIH", obj.data, section.reloc_offset + i * 10)
        symbol = obj.symbols[number]
        if symbol.section_number == root.section_number and kind == 6:
            local_fields.add(field - root.value)
        if kind == 0x14 and symbol.section_number > 0:
            local_calls.append({"field": field, "symbol": symbol.name})
    unit = load_manifest()["units"]["gpt-web-iku-action-state"]["functions"][0]
    calls = {name: int(address, 0) for name, _, address in (mapping.partition("=") for mapping in unit["rel32_targets"])}
    data = {name: target for name, _, target in (mapping.partition("=") for mapping in unit["dir32_targets"])}
    # CFG diagnostics must replay the actual candidate table tail even when
    # that section is larger than the target callable. Acceptance still uses
    # the canonical comparator's independently fixed target extent.
    code = canonical.coff_symbol_bytes(path, root.name, START, section.raw_size - root.value,
                                       calls, canonical.known_data_targets(), data)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    todo, rows, owners, indirect, tails = [START], {}, {}, {}, []
    while todo:
        address = todo.pop()
        if address in rows:
            continue
        offset = address - START
        if not 0 <= offset < len(code):
            raise ValueError(f"candidate direct edge {address:#x} leaves root section "
                             f"[{START:#x},{START + len(code):#x})")
        row = next(md.disasm(code[offset:offset + 15], address, count=1), None)
        if row is None or any(byte in owners for byte in range(address, address + row.size)):
            raise ValueError("candidate decode fails or overlaps an instruction")
        rows[address] = row
        owners.update({byte: address for byte in range(address, address + row.size)})
        if row.group(capstone.CS_GRP_RET):
            continue
        edges = [address + row.size]
        if row.group(capstone.CS_GRP_JUMP):
            op = row.operands[0]
            if op.type == X86_OP_IMM:
                if not START <= op.imm < START + len(code):
                    if row.mnemonic != "jmp" or op.imm not in calls.values():
                        raise ValueError("candidate unqualified external branch")
                    tails.append({"site": address, "destination": op.imm})
                    continue
                edges = [op.imm] + ([] if row.mnemonic == "jmp" else edges)
            elif op.type == X86_OP_MEM and not op.mem.base and op.mem.scale == 4:
                cursor = op.mem.disp - START
                destinations = []
                while cursor in local_fields:
                    destinations.append(struct.unpack_from("<I", code, cursor)[0])
                    cursor += 4
                if not destinations:
                    raise ValueError("candidate jump table has no real local DIR32 entries")
                indirect[address] = destinations
                edges = destinations
            else:
                raise ValueError("unqualified candidate indirect jump")
        todo.extend(edges)
    end = max(row.address + row.size for row in rows.values())
    return {"source_object": str(path), "object_sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "canonical_section_tail_sha256": hashlib.sha256(code).hexdigest(),
            "section_tail_bytes": len(code), "callable_span_bytes": end - START,
            "instructions": len(rows), "unique_instruction_bytes": len(owners),
            "calls": call_census(rows.values()),
            "unreached_bytes_inside_callable_span": sum(a not in owners for a in range(START, end)),
            "post_callable_metadata_bytes": START + len(code) - end,
            "returns": sum(row.group(capstone.CS_GRP_RET) for row in rows.values()),
            "switches": {str(site): len(destinations) for site, destinations in indirect.items()},
            "external_tails": tails, "remaining_local_CALLs": local_calls,
            "first_bytes": code[:16].hex(), "scope": "normal-return CFG from actual COFF relocations; no byte acceptance"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--native-object", type=Path,
                        help="check that the native-tested root replays to the same bytes as --object")
    args = parser.parse_args()
    if args.native_object and not args.object:
        parser.error("--native-object requires --object")
    canonical = comparator()
    report = {"schema": "th105-iku-full-root-facts-v1", "target_sha256": canonical.verify_target(),
              "root_sha256": ROOT_SHA, "target": target_audit(canonical)}
    if args.object:
        report["candidate"] = candidate_audit(canonical, args.object.resolve())
    if args.native_object:
        report["native_candidate"] = candidate_audit(canonical, args.native_object.resolve())
        if report["native_candidate"]["canonical_section_tail_sha256"] != report["candidate"]["canonical_section_tail_sha256"]:
            raise ValueError("native-tested and canonical-unit roots differ after genuine relocation replay")
        report["native_and_unit_replay_identical"] = True
    print(json.dumps(report, indent=2))
