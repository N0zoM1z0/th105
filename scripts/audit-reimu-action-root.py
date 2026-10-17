#!/usr/bin/env python3
"""Reconcile the entire Reimu +0x28 callable and its eleven target switches.

Read-only target observations and explicit ABI assumptions; no source/exact
credit. Internal loop alignment remains significant in canonical comparisons.
"""
from __future__ import annotations

import argparse
from collections import Counter
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
from capstone import x86_const as x
import pefile

from giant_owner_audit import decode, reachable_boundary_audit
from linked_pe import is_branch, primary_type_name

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def reaching_ebp_definitions(rows, switches, site):
    """Backward nearest writes, with ordinary callee-saved EBP at CALLs.

    Keep all reaching definitions: a disagreeing/unknown path is never silently
    dropped. Partial BP writes also terminate provenance at that instruction.
    """
    by_address = {row.address: row for row in rows}
    predecessors = {address: [] for address in by_address}
    for row in rows:
        if row.group(capstone.CS_GRP_RET):
            continue
        if is_branch(row):
            operand = row.operands[0]
            if operand.type == x.X86_OP_IMM:
                destinations = [operand.imm]
            elif row.mnemonic == "jmp" and operand.type == x.X86_OP_MEM:
                destinations = switches[operand.mem.disp][1]
            else:
                raise ValueError("unreviewed branch in EBP-bound traversal")
            if row.mnemonic != "jmp":
                destinations = [*destinations, row.address + row.size]
        else:
            destinations = [row.address + row.size]
        for destination in destinations:
            if destination in predecessors:
                predecessors[destination].append(row.address)
    pending, visited, definitions = list(predecessors[site]), set(), set()
    while pending:
        address = pending.pop()
        if address in visited:
            continue
        visited.add(address)
        row = by_address[address]
        written = {row.reg_name(register) for register in row.regs_access()[1]}
        if written & {"ebp", "bp", "bpl", "bph"}:
            definitions.add(address)
        elif address == rows[0].address:
            definitions.add(None)
        else:
            pending.extend(predecessors[address])
    return definitions, len(visited)


def audit():
    canonical = load_script("reimu_root_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = load_script("reimu_root_mapper", "map-giant-action-switches.py")
    root = mapper.select_root(tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
                              "reimu-vslot28")
    address, end = int(root["address"], 0), int(root["callable_end"], 0)
    code = canonical.target_bytes(address, end - address)
    body_sha = hashlib.sha256(code).hexdigest()
    if (address, len(code), body_sha, int(root["metadata_end"], 0)) != (
            0x478FA0, 81550, "dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6",
            0x48D38C):
        raise ValueError("Reimu reviewed callable boundary/hash changed")
    observed = mapper.map_root(mapper.PeImage(ROOT / "resources/th105.exe"),
                               mapper.load_function_rows(ROOT / "config/functions.csv"), root)
    rows = decode(code, address)
    by_address = {row.address: row for row in rows}
    positions = {row.address: index for index, row in enumerate(rows)}
    for configured, site in zip(root["regions"], (0x4791FE, 0x47CC87, 0x487A8E)):
        number = positions[site]
        compare, guard, load, jump = rows[number-3:number+1]
        table, index = int(configured["destination_table"], 0), int(configured["index_table"], 0)
        if (compare.mnemonic != "cmp" or compare.op_str.split(",")[0] != "eax"
                or compare.operands[1].type != x.X86_OP_IMM
                or compare.operands[1].imm != configured["case_max"] - configured["case_min"]
                or guard.mnemonic != "ja" or guard.operands[0].imm != 0x48CE1F
                or load.mnemonic != "movzx" or load.operands[1].size != 1
                or load.operands[1].type != x.X86_OP_MEM or load.operands[1].mem.disp != index
                or jump.operands[0].mem.disp != table
                or index != table + configured["destination_count"] * 4):
            raise ValueError("primary action table disagrees with its decoded unsigned bound")
        low = configured["case_min"]
        if low and (rows[number-4].mnemonic != "sub" or rows[number-4].operands[1].imm != low):
            raise ValueError("primary action selector bias changed")
    switches = {int(configured["destination_table"], 0):
                (configured["name"], [group["destination"] for group in actual["groups"]])
                for configured, actual in zip(root["regions"], observed["regions"])}
    for configured in root["auxiliary_switches"]:
        table = int(configured["destination_table"], 0)
        destinations = [int(value, 0) for value in configured["destinations"]]
        actual = list(struct.unpack("<" + "I" * len(destinations),
                                    canonical.target_bytes(table, 4 * len(destinations))))
        dispatch = by_address[int(configured["dispatch"], 0)]
        if (actual != destinations or table in switches or dispatch.mnemonic != "jmp"
                or dispatch.operands[0].type != x.X86_OP_MEM
                or dispatch.operands[0].mem.disp != table
                or any(destination not in by_address for destination in destinations)):
            raise ValueError("Reimu auxiliary table bytes/dispatch/boundaries disagree")
        switches[table] = (configured["name"], destinations)
        number = positions[dispatch.address]
        guard = rows[number-1]
        compare = next((row for row in reversed(rows[max(0, number-5):number-1])
                        if row.mnemonic == "cmp"), None)
        if (guard.mnemonic != "ja" or compare is None
                or compare.operands[0].type != x.X86_OP_REG
                or compare.operands[0].reg != dispatch.operands[0].mem.index):
            raise ValueError("nested switch lacks its decoded unsigned index bound")
        operand = compare.operands[1]
        bound = (operand.imm if operand.type == x.X86_OP_IMM else
                 3 if compare.address == 0x48BE95 and operand.type == x.X86_OP_REG
                 and operand.reg == x.X86_REG_EBP else None)
        if bound is None or bound + 1 != len(destinations):
            raise ValueError("nested table length differs from its guarded index domain")
    boundary = reachable_boundary_audit(code, address, switches)
    if (len(boundary["switch_jumps"]) != 11 or boundary["unresolved_indirect_exits"]
            or boundary["internal_call_targets"]
            or any(site["kind"] != "call" for edge in boundary["direct_external_targets"]
                   for site in edge["sites"])):
        raise ValueError("Reimu root has an unclosed CPU transfer")
    alignment = []
    for first, last in boundary["unreached_ranges"]:
        previous = rows[positions[first] - 1]
        if (previous.mnemonic != "jmp" or previous.operands[0].type != x.X86_OP_IMM
                or previous.operands[0].imm != last or last % 16):
            raise ValueError("unreachable Reimu bytes lack a direct aligned skip")
        for row in rows[positions[first]:positions[last]]:
            if row.mnemonic == "nop" and row.size == 1:
                continue
            operands = row.operands
            if (row.mnemonic != "lea" or len(operands) != 2
                    or operands[0].type != x.X86_OP_REG or operands[1].type != x.X86_OP_MEM
                    or operands[0].reg != operands[1].mem.base
                    or row.reg_name(operands[0].reg) not in {"ebx", "ecx", "esp"}
                    or operands[1].mem.index or operands[1].mem.disp or operands[1].mem.segment):
                raise ValueError("unreviewed Reimu alignment instruction")
        alignment.append({"start": first, "end": last, "bytes": canonical.target_bytes(first, last-first).hex()})
    definitions, visited = reaching_ebp_definitions(rows, switches, 0x48BE95)
    if definitions != {0x48BC57} or by_address[0x48BC57].bytes != bytes.fromhex("bd03000000"):
        raise ValueError("action720 match-identifier bound is not proved EBP=3")
    image = pefile.PE(str(ROOT / "resources/th105.exe"))
    if (primary_type_name(image, 0x6C412C) != ".?AVReimu@@"
            or canonical.target_bytes(0x6C4154, 4) != struct.pack("<I", address)):
        raise ValueError("Reimu RTTI primary-vtable ownership changed")
    calls = Counter(row.operands[0].imm for row in rows
                    if row.mnemonic == "call" and row.bytes[0] == 0xE8)
    if (len(rows), boundary["reachable_instructions"], boundary["reachable_bytes"],
            len(alignment), sum(calls.values()), len(calls)) != (20256, 20243, 81488, 9, 1188, 32):
        raise ValueError("Reimu decoded/CFG census changed")
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {int(row["address"], 0): row for row in csv.DictReader(stream)}
    return {"schema": "th105-reimu-action-root-facts-v1", "target_sha256": target_sha,
            "address": address, "callable_size": len(code), "body_sha256": body_sha,
            "boundary": boundary, "alignment": alignment,
            "action720_bound": {"compare": 0x48BE95, "reaching_definition": 0x48BC57,
                                "value": 3, "backward_instructions": visited,
                                "assumption": "ordinary callees preserve EBP"},
            "calls": [{"address": destination, "count": count,
                       "name": ledger.get(destination, {}).get("proposed_name"),
                       "status": ledger.get(destination, {}).get("status")}
                      for destination, count in sorted(calls.items())],
            "raw_e8_sanity": {"sites": root["expected_direct_call_sites"],
                              "targets": root["expected_direct_call_targets"],
                              "scope": "byte-scan regression guard; includes three noninstruction false positives"},
            "scope": "whole bounded target CFG and receiver identity; no source completeness or exact credit; "
                     "62 loop-alignment bytes remain part of strict canonical comparisons"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = audit()
    except (KeyError, OSError, TypeError, ValueError) as error:
        parser.exit(2, f"Reimu root audit failed: {error}\n")
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print("Reimu: 81550 bytes, 11 switches, 1188 direct calls; 62 bytes of proved loop alignment; no exact credit")
