#!/usr/bin/env python3
"""Qualify shared Fighter virtual tail calls for a reviewed RTTI receiver domain.

Retains raw exit inventories. The optional linked-root helper supplies reviewed
ABI facts for diagnostic relocation replay; accepted-unit rules stay unchanged.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_MEM, X86_OP_IMM

from typed_indirect_tails import receiver_tail_facts
from linked_pe import pe_data, primary_type_name, linked_body
from giant_owner_audit import decode

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def qualify_domain(read_slot, tables, tails):
    """Never promote an unknown receiver or a disagreeing vtable family."""
    result = []
    for tail in tails:
        slot = tail["slot_offset"]
        qualified = tail["ecx_is_entry_receiver"] and slot == 0x14
        targets = sorted({read_slot(base + slot) for base in tables.values()}) if qualified else []
        qualified = qualified and len(targets) == 1
        result.append({**tail, "qualified_for_reviewed_domain": qualified,
                       "observed_domain_targets": targets,
                       "inferred_target": targets[0] if qualified else None})
    return result


def qualify_frame_epilogue(instructions, address):
    """Require the observed four-byte root frame and reviewed terminal stores.

    This is a local ABI witness, not an execution-equivalence claim. No branch
    may enter after the first restore; receiver provenance is checked separately.
    """
    index = next(i for i, row in enumerate(instructions) if row.address == address)
    end = [(row.mnemonic, row.op_str) for row in instructions[max(0, index - 3):index]]
    if end != [("pop", "esi"), ("pop", "ebx"), ("add", "esp, 4")]:
        raise ValueError("tail lacks the common root frame restoration")
    first = next((i for i in range(index - 4, max(-1, index - 10), -1)
                  if (instructions[i].mnemonic, instructions[i].op_str) == ("pop", "edi")), None)
    if first is None:
        raise ValueError("tail lacks EDI restoration")
    for row in instructions[first + 1:index - 3]:
        operands = row.operands
        receiver = ((row.mnemonic, row.op_str) in
                    {("mov", "ecx, esi"), ("lea", "ecx, [esi + 4]")})
        store = (row.mnemonic in {"mov", "fstp"} and operands
                 and operands[0].type == X86_OP_MEM and row.reg_name(operands[0].mem.base) == "esi"
                 and not operands[0].mem.index and not operands[0].mem.segment
                 and ((row.mnemonic == "fstp" and operands[0].size == 4
                       and operands[0].mem.disp in (0xF0, 0xF4, 0x6AC))
                      or (row.mnemonic == "mov" and row.op_str == "byte ptr [esi + 0x47e], 0")))
        conversion = row.mnemonic == "fild" and row.op_str == "dword ptr [esp + 8]"
        literal_multiply = (row.mnemonic == "fmul" and len(operands) == 1
                            and operands[0].type == X86_OP_MEM and operands[0].size == 8
                            and not operands[0].mem.base and not operands[0].mem.index
                            and not operands[0].mem.segment)
        if not (receiver or store or conversion or literal_multiply):
            raise ValueError("unreviewed instruction inside a tail epilogue")
    return instructions[first].address


def qualify_linked_tails(canonical, call_targets, pe, functions, code, start, switches, boundary):
    """Qualify only this root's actual receiver domain and zero-argument tails."""
    target = audit()  # Reattests target bytes, RTTI/PMDs and the accepted slot ABI.
    instructions = decode(code, start)
    if code[:18] != canonical.target_bytes(0x4740C0, 18):
        raise ValueError("linked common root has an unreviewed entry frame")
    flow = receiver_tail_facts(code, start, {table: values[1] for table, values in switches.items()},
                               include_direct_tails=True)
    if flow["reachable_instructions"] != boundary["reachable_instructions"]:
        raise ValueError("linked receiver and boundary traversals disagree")
    tables = {row["anchor_owner"]: row["vtable"] for row in target["receiver_domain"]}
    virtual = qualify_domain(lambda address: struct.unpack("<I", canonical.target_bytes(address, 4))[0],
                             tables, flow["register_tail_exits"])
    if not all(row["qualified_for_reviewed_domain"] for row in virtual):
        raise ValueError("linked virtual tail has an unknown receiver/slot/domain")
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {int(row["address"], 0): row for row in csv.DictReader(stream)}
    expected = {0x435110: (4, "reset_fighter_action_scratch"),
                0x4351C0: (0, "CharacterObjectRuntime_advance_frame_and_dispatch"),
                0x45AF40: (0, "Fighter_zero_velocity_acceleration")}
    direct, callees = {}, {}
    for tail in flow["direct_tail_exits"]:
        names = functions.get(tail["target"], [])
        destination = call_targets.get(names[0][0]) if len(names) == 1 else None
        contract = expected.get(destination)
        row = ledger.get(destination, {})
        if (contract is None or tail["ecx_entry_receiver_offset"] != contract[0]
                or row.get("proposed_name") != contract[1] or row.get("status") != "matching"
                or row.get("calling_convention") != "__thiscall"):
            raise ValueError("linked direct tail lacks a reviewed zero-argument receiver ABI")
        # Accepted callees must still have plain RET, with no stack arguments.
        target_body = canonical.target_bytes(destination, int(row["size"]))
        # These three accepted helpers contain no relocated addresses. Check
        # the actual linked body too: a map name cannot stand in for its ABI.
        if linked_body(pe, functions, tail["target"]) != target_body:
            raise ValueError("linked direct-tail callee differs from its accepted target body")
        callee = decode(target_body, destination)
        returns = [item for item in callee if item.mnemonic.startswith("ret")]
        if not returns or any(item.mnemonic != "ret" or item.op_str for item in returns):
            raise ValueError("linked direct-tail callee no longer has the zero-argument ABI")
        direct[tail["address"]] = destination
        callees[destination] = {"linked_address": tail["target"], "size": len(target_body),
                                "raw_equal_sha256": hashlib.sha256(target_body).hexdigest(),
                                "callee_ledger_name": contract[1]}
    starts = {tail["address"]: qualify_frame_epilogue(instructions, tail["address"])
              for tail in [*virtual, *flow["direct_tail_exits"]]}
    destinations = {row.operands[0].imm for row in instructions
                    if row.group(CS_GRP_JUMP) and row.operands[0].type == X86_OP_IMM}
    destinations.update(destination for _, values in switches.values() for destination in values)
    for tail, first in starts.items():
        if any(first < destination <= tail for destination in destinations):
            raise ValueError("control flow enters the middle of a linked tail epilogue")
    return {"virtual_sites": [row["address"] for row in virtual], "direct_sites": direct,
            "virtual_receiver_domain": target["receiver_domain"], "virtual_facts": virtual,
            "direct_facts": flow["direct_tail_exits"], "direct_callees": callees,
            "frame_epilogues": starts,
            "scope": "reviewed common-root receiver/epilogue ABI only; raw exits retained; no exact credit"}


def audit():
    canonical = load_script("common_tail_canonical", "compare-function.py")
    target_hash = canonical.verify_target()
    mapper = load_script("common_tail_mapper", "map-giant-action-switches.py")
    roots = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = mapper.select_root(roots, "fighter-common-action")
    observed = mapper.map_root(mapper.PeImage(ROOT / "resources/th105.exe"),
                               mapper.load_function_rows(ROOT / "config/functions.csv"), root)
    address, size = observed["address"], observed["callable_size"]
    code = canonical.target_bytes(address, size)
    if size != 10219 or hashlib.sha256(code).hexdigest() != "7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6":
        raise ValueError("shared root boundary/hash changed")
    switches = {int(configured["destination_table"], 0): [g["destination"] for g in actual["groups"]]
                for configured, actual in zip(root["regions"], observed["regions"])}
    flow = receiver_tail_facts(code, address, switches)
    if flow["reachable_instructions"] != 2799 or len(flow["register_tail_exits"]) != 8:
        raise ValueError("shared root receiver traversal is incomplete")
    coverage = load_script("common_tail_roster", "audit-roster-primary-vtable-coverage.py")
    tables = coverage.vtable_bases(ROOT / "config/roster-fighter-vtable-origin-anchors.toml")
    tables["CharacterEx"] = 0x6C3F94
    if len(tables) != 16 or len(set(tables.values())) != 16:
        raise ValueError("reviewed receiver vtables must be distinct")
    image = pefile.PE(str(ROOT / "resources/th105.exe"))

    def dword(address):
        return struct.unpack("<I", canonical.target_bytes(address, 4))[0]

    domain = []
    for owner, base in sorted(tables.items()):
        typename = primary_type_name(image, base)
        if typename != f".?AV{owner}@@":
            raise ValueError("roster anchor owner disagrees with raw RTTI")
        col = dword(base - 4)
        hierarchy = dword(col + 16)
        count, array = struct.unpack("<II", pe_data(image, hierarchy + 8, 8))
        if not 1 <= count <= 32:
            raise ValueError("unexpected RTTI base count")
        character_base = []
        for index in range(count):
            descriptor = dword(array + index * 4)
            typedesc = dword(descriptor)
            name = pe_data(image, typedesc + 8, 128).split(b"\0", 1)[0].decode("ascii")
            if name == ".?AVCharacterEx@@":
                pmd = struct.unpack("<iii", pe_data(image, descriptor + 8, 12))
                if pmd != (0, -1, 0):
                    raise ValueError("CharacterEx receiver requires a nonzero/virtual base adjustment")
                character_base.append(descriptor)
        if len(character_base) != 1:
            raise ValueError("reviewed receiver lacks one primary CharacterEx base")
        slots = {offset: dword(base + offset) for offset in (8, 12, 20)}
        if slots != {8: 0x45BFE0, 12: 0x45C390, 20: 0x45C220}:
            raise ValueError("reviewed receiver virtual interface changed")
        domain.append({"anchor_owner": owner, "vtable": base, "rtti_name": typename,
                       "character_ex_base_descriptor": character_base[0], "slots": slots})
    tails = qualify_domain(dword, tables, flow["register_tail_exits"])
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, address))
    positions = {instruction.address: index for index, instruction in enumerate(instructions)}
    for tail in tails:
        index = positions[tail["address"]]
        previous = [(i.mnemonic, i.op_str) for i in instructions[max(0, index - 5):index]]
        ordinary = [("pop", "edi"), ("pop", "esi"), ("pop", "ebx"), ("add", "esp, 4")]
        reload = [("pop", "edi"), ("mov", "ecx, esi"), *ordinary[1:]]
        if previous[-4:] != ordinary and previous != reload:
            raise ValueError("register exit lacks the root's complete frame-restoring epilogue")
        tail["frame_restoring_epilogue"] = True
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {int(row["address"], 0): row for row in csv.DictReader(stream)}
    for tail in tails:
        if tail["qualified_for_reviewed_domain"]:
            row = ledger.get(tail["inferred_target"])
            if row is None or row["proposed_name"] != "AttackObject_next_sequence_block" or row["status"] != "matching":
                raise ValueError("qualified target lacks its accepted semantic interface")
            tail["callee_ledger_name"] = row["proposed_name"]
            tail["callee_source"] = row["source_file"]
    return {"schema": "th105-common-fighter-indirect-tail-facts-v1",
            "evidence": "target observations plus receiver-domain inference; no exact credit",
            "target_sha256": target_hash, "root": address, "callable_size": size,
            "body_sha256": hashlib.sha256(code).hexdigest(), "receiver_domain": domain,
            "dataflow": flow, "qualified_tails": tails,
            "qualified_count": sum(t["qualified_for_reviewed_domain"] for t in tails),
            "raw_register_exit_count": len(tails),
            "scope": "only the 15 reviewed roster primary vtables and CharacterEx; other receiver domains are not inferred"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = audit()
    except (KeyError, OSError, TypeError, ValueError) as error:
        parser.exit(2, f"shared Fighter indirect-tail audit failed: {error}\n")
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"{result['qualified_count']}/{result['raw_register_exit_count']} virtual tails qualified for "
              f"{len(result['receiver_domain'])} reviewed receiver types; no exact credit")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
