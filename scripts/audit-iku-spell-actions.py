#!/usr/bin/env python3
"""Target-pinned control/literal facts for Iku's eight 600--610 action arms.

These are regions of 620920, not standalone compiler functions or partial
authored-byte acceptance. Calls are followed under their normal-return ABI.
"""
import hashlib
import json
import struct

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

from giant_owner_audit import decode
from linked_pe import comparator

ENTRIES = {600: 0x62BDC2, 601: 0x62BF12, 602: 0x62C232, 603: 0x62C619,
           606: 0x62C7A6, 607: 0x62C91B, 609: 0x62CA58, 610: 0x62CC24}
END = 0x62D02A
# Widths and values come from the actual load operands, independently of the
# decompiler's casts or the source's literal spelling.
LITERALS = {0x6C12A0: (8, 0.75), 0x6C0F00: (8, 30.0), 0x6C4D60: (8, 190.0),
            0x6C13F0: (4, 2.0), 0x6D6EDC: (4, 180.0), 0x6C4768: (8, 155.0),
            0x6C4A98: (8, 140.0), 0x6C1898: (8, 125.0), 0x6C4408: (8, 85.0),
            0x6C0EC0: (8, 320.0), 0x6C36C8: (8, 1000.0), 0x6D6ED8: (4, 3.0),
            0x6C4638: (8, 22.5), 0x6CD200: (4, 4.0), 0x6C3B3C: (4, 25.0),
            0x6C0ED8: (8, 360.0), 0x6C5CF8: (8, 138.0), 0x6CD190: (8, 100.0),
            0x6D6EB0: (8, 180.0), 0x6C12B0: (4, 12.0), 0x6C4380: (8, 275.0),
            0x6CD1D8: (4, 6.0), 0x6C3B70: (4, 5.0), 0x6C3E68: (4, 20.0),
            0x6C2A38: (4, 40.0), 0x6C5270: (8, 145.0), 0x6D6EF8: (4, 4294967296.0)}
WITNESSES = {
    0x62C117: ("xor", "edi, edi"), 0x62C119: ("mov", "dword ptr [esp + 0x10], edi"),
    0x62C13C: ("fild", "dword ptr [esp + 0x10]"),
    0x62C217: ("add", "edi, 0x2d"), 0x62C21A: ("cmp", "edi, 0x168"),
    0x62C224: ("jl", "0x62c120"),
    0x62C172: ("fcom", "st(1)"), 0x62C178: ("test", "ah, 1"),
    0x62C17B: ("jne", "0x62c1c9"), 0x62C17D: ("fcomp", "dword ptr [0x6d6edc]"),
    0x62C185: ("test", "ah, 0x41"), 0x62C188: ("jp", "0x62c1cb"),
    0x62C478: ("xor", "edi, edi"), 0x62C480: ("mov", "dword ptr [esp + 0x10], edi"),
    0x62C484: ("fild", "dword ptr [esp + 0x10]"),
    0x62C524: ("add", "edi, 0x2d"), 0x62C527: ("cmp", "edi, 0x168"),
    0x62C531: ("jl", "0x62c484"),
    0x62C4BE: ("fcom", "st(1)"), 0x62C4C4: ("test", "ah, 1"),
    0x62C4C7: ("jne", "0x62c4ec"), 0x62C4C9: ("fcomp", "dword ptr [0x6d6edc]"),
    0x62C4D1: ("test", "ah, 0x41"), 0x62C4D4: ("jp", "0x62c4ee"),
    0x62C5C3: ("sub", "eax, 0xc8"), 0x62C5D4: ("fadd", "dword ptr [0x6d6ef8]"),
    0x62C634: ("cmp", "dword ptr [esi + 0x144], 0x20"),
    0x62C63B: ("jge", "0x626c40"),
    0x62C947: ("cmp", "word ptr [esi + 0x140], 5"),
    0x62CA39: ("call", "0x4351c0"),
    0x62CA73: ("cmp", "dword ptr [esi + 0x144], 0x14"),
    0x62CA7A: ("jge", "0x626c40"),
    0x62CC4F: ("idiv", "ecx"), 0x62CD91: ("idiv", "ecx"),
    0x62CECA: ("cmp", "dword ptr [esi + 0x144], 0x78"),
    0x62CED1: ("jge", "0x626c40"),
}


def audit():
    canonical = comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(0x620920, 59038)
    body_sha = hashlib.sha256(body).hexdigest()
    if body_sha != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku whole-root bytes differ")
    rows = {row.address: row for row in decode(body, 0x620920)}
    table = struct.unpack("<35I", canonical.target_bytes(0x62F2C8, 140))
    lookup = canonical.target_bytes(0x62F354, 238)
    for action, entry in ENTRIES.items():
        if table[lookup[action - 561]] != entry:
            raise ValueError("compressed spell action entry differs")
    if table[lookup[650 - 561]] != END:
        raise ValueError("physical spell family end differs")
    for address, expected in WITNESSES.items():
        row = rows[address]
        if (row.mnemonic, row.op_str) != expected:
            raise ValueError(f"spell control witness differs at {address:#x}")
    pending, seen = list(ENTRIES.values()), set()
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        if address not in rows:
            raise ValueError("spell edge leaves root or enters an instruction")
        seen.add(address)
        row = rows[address]
        if row.group(capstone.CS_GRP_RET):
            continue
        destinations = [address + row.size]
        if row.group(capstone.CS_GRP_JUMP):
            if row.operands[0].type != X86_OP_IMM:
                raise ValueError("unreviewed spell-family indirect jump")
            destinations = [row.operands[0].imm] + ([] if row.mnemonic == "jmp" else destinations)
        pending.extend(destinations)
    physical = [row for row in rows.values() if ENTRIES[600] <= row.address < END]
    if (len(physical), len(seen), sum(rows[a].size for a in seen)) != (1214, 1233, 4739):
        raise ValueError("complete spell-family control flow differs")
    if not {row.address for row in physical} <= seen:
        raise ValueError("physical spell bytes are not in the complete case CFG")
    literals = []
    for address, (width, value) in LITERALS.items():
        raw = canonical.target_bytes(address, width)
        witnesses = [row.address for row in physical if row.mnemonic.startswith("f")
                     for operand in row.operands if operand.type == X86_OP_MEM
                     and not (operand.mem.base or operand.mem.index)
                     and operand.mem.disp == address and operand.size == width]
        if not witnesses or struct.unpack("<f" if width == 4 else "<d", raw)[0] != value:
            raise ValueError("spell literal width/value has no actual operand witness")
        literals.append({"address": address, "width": width, "value": value, "bytes": raw.hex(), "sites": witnesses})
    cases = []
    ordered = list(ENTRIES.items())
    for (action, start), end in zip(ordered, [entry for _, entry in ordered[1:]] + [END]):
        code = canonical.target_bytes(start, end - start)
        selected = [row for row in physical if start <= row.address < end]
        cases.append({"action": action, "entry": start, "end": end, "bytes": len(code),
                      "sha256": hashlib.sha256(code).hexdigest(), "instructions": len(selected),
                      "calls": [{"site": row.address, "operand": row.op_str} for row in selected if row.mnemonic == "call"]})
    return {"schema": "th105-iku-spell-facts-v1", "target_sha256": target_sha, "root_sha256": body_sha,
            "cases": cases, "physical_bytes": END - ENTRIES[600], "cfg_instructions": len(seen),
            "cfg_bytes": sum(rows[a].size for a in seen),
            "remote_instructions": sorted(a for a in seen if not ENTRIES[600] <= a < END),
            "literals": literals,
            "integer_loops": [{"action": 601, "head": 0x62C120}, {"action": 602, "head": 0x62C484}],
            "loop_contract": "EDI/int32 and DWORD stack carrier; initial0, step45, signed<360: eight iterations; "
                             "not a float loop counter; both angle tests use ordered inclusive0..180",
            "scope": "complete normal-return action CFG with shared tails; raw observations plus reviewed source inference; "
                     "not standalone boundaries, post-backend equivalence or partial/full exact credit"}


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
