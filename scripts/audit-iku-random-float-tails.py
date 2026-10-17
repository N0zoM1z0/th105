#!/usr/bin/env python3
"""Prove Iku's unsigned random-to-x87 correction guards from exact PE bytes.

Raw CFG reachability is kept distinct from arithmetic path feasibility.
This is type/control evidence for the whole 59038-byte root, not exact credit.
"""
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import struct

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_ESI

from giant_owner_audit import decode, reachable_boundary_audit
from linked_pe import comparator

ROOT = Path(__file__).resolve().parents[1]
START, SIZE = 0x620920, 59038
BODY_SHA = "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea"
CORRECTION = 0x6D6EF8
SWITCHES = ((0x620B1B, 0x62EFC0, 33), (0x62374C, 0x62F128, 42),
            (0x6290B3, 0x62F2C8, 35))


def selector_bound(limit):
    if not 0 < limit <= 0xFFFFFFFF:
        raise ValueError("invalid unsigned selector limit")
    maximum = 0xFFFFFFFF // (0xFFFFFFFF // limit)
    if maximum >= 0x80000000:
        raise ValueError("selector result can have its sign bit set")
    return maximum


def selector_argument(rows, call_index):
    slot = 0
    for index in range(call_index - 1, max(-1, call_index - 40), -1):
        row = rows[index]
        if row.group(capstone.CS_GRP_JUMP) or row.group(capstone.CS_GRP_CALL) or row.group(capstone.CS_GRP_RET):
            raise ValueError("control transfer precedes selector argument definition")
        if row.mnemonic == "push":
            if slot == 0:
                if row.operands[0].type != X86_OP_IMM:
                    raise ValueError("selector argument is not an attested immediate")
                return index, row.operands[0].imm
            slot -= 4
        elif row.mnemonic in ("add", "sub") and row.op_str.startswith("esp, "):
            amount = row.operands[1].imm
            slot += amount if row.mnemonic == "add" else -amount
        elif row.mnemonic == "pop" or capstone.x86.X86_REG_ESP in row.regs_access()[1]:
            raise ValueError("unsupported selector argument stack update")
        if row.operands and row.operands[0].type == X86_OP_MEM:
            memory = row.operands[0].mem
            if memory.base == capstone.x86.X86_REG_ESP and memory.index:
                raise ValueError("indexed stack access obscures selector argument")
            if memory.base == capstone.x86.X86_REG_ESP and memory.disp <= slot < memory.disp + row.operands[0].size:
                raise ValueError("selector argument overwritten before call")
    raise ValueError("selector argument definition not found")


def prove_fixup(rows, at, incoming, read):
    if not 6 <= at < len(rows):
        raise ValueError("conversion producer is truncated")
    correction = rows[at]
    if (correction.mnemonic != "fadd" or correction.op_str != "dword ptr [0x6d6ef8]"
            or read(CORRECTION, 4) != struct.pack("<f", 2.0 ** 32)):
        raise ValueError("unsigned-float correction literal differs")
    guard, load, store, test = rows[at - 1], rows[at - 2], rows[at - 3], rows[at - 4]
    if (guard.mnemonic != "jge" or guard.operands[0].type != X86_OP_IMM
            or guard.operands[0].imm != correction.address + correction.size
            or load.mnemonic != "fild" or not load.op_str.startswith("dword ptr [esp")
            or store.mnemonic != "mov" or len(store.operands) != 2
            or store.op_str.rsplit(", ", 1)[0] != load.op_str):
        raise ValueError("unproved conversion store/load/guard")
    register = store.op_str.rsplit(", ", 1)[1]
    if test.mnemonic != "test" or test.op_str != f"{register}, {register}":
        raise ValueError("JGE flags are not from the converted integer")
    subtract = 0
    if register == "edx":
        if at < 8:
            raise ValueError("unsigned remainder producer is truncated")
        first = at - 8
        call, zero, divisor, division = rows[first:at - 4]
        if ((call.mnemonic, call.op_str) != ("call", "0x4066b0")
                or (zero.mnemonic, zero.op_str) != ("xor", "edx, edx")
                or divisor.mnemonic != "mov" or divisor.op_str.split(", ")[0] != "ecx"
                or divisor.operands[1].type != X86_OP_IMM
                or (division.mnemonic, division.op_str) != ("div", "ecx")):
            raise ValueError("unproved unsigned remainder producer")
        limit = divisor.operands[1].imm
        if not 0 < limit <= 0x80000000:
            raise ValueError("remainder may have its sign bit set")
        kind, maximum = "unsigned_remainder", limit - 1
    elif register == "eax":
        cursor = at - 5
        if rows[cursor].mnemonic == "sub" and rows[cursor].op_str.startswith("eax, "):
            subtract = rows[cursor].operands[1].imm
            if not 0 <= subtract <= 0xFFFFFFFF:
                raise ValueError("unsupported unsigned subtraction")
            cursor -= 1
        if (rows[cursor].mnemonic, rows[cursor].op_str) == ("add", "esp, 4"):
            cursor -= 1
        call = rows[cursor]
        if (call.mnemonic, call.op_str) != ("call", "0x4067d0"):
            raise ValueError("unproved selector argument/call/cleanup")
        first, limit = selector_argument(rows, cursor)
        kind, maximum = "selector_unsigned_conversion", selector_bound(limit)
    else:
        raise ValueError("unreviewed conversion register")
    window = rows[first:at + 1]
    if any(left.address + left.size != right.address for left, right in zip(window, window[1:])):
        raise ValueError("conversion producer is not contiguous")
    # The call has an ordinary return edge. No root branch or switch may enter
    # halfway through the producer and bypass the range or flags definition.
    if any(incoming.get(row.address) for row in window[1:]):
        raise ValueError("alternate CFG edge bypasses conversion proof")
    low, high = -subtract, maximum - subtract
    if low < 0 <= high:
        intervals = [[0, high], [2**32 + low, 2**32 - 1]]
    elif high < 0:
        intervals = [[2**32 + low, 2**32 + high]]
    else:
        intervals = [[low, high]]
    always_taken = True if all(hi < 2**31 for lo, hi in intervals) else None
    return {"correction": correction.address, "guard": guard.address,
            "producer": window[0].address, "kind": kind, "limit": limit,
            "producer_range_inclusive": [0, maximum], "unsigned_subtract": subtract,
            "converted_unsigned_intervals": intervals, "correction_bytes": correction.size,
            "guard_always_taken": always_taken,
            "reason": "TEST clears OF; SF follows converted bit31; MOV/FILD preserve EFLAGS"}


def audit():
    canonical = comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(START, SIZE)
    if hashlib.sha256(body).hexdigest() != BODY_SHA:
        raise ValueError("Iku callable differs")
    rows = decode(body, START)
    switches, incoming = {}, defaultdict(set)
    for site, table, count in SWITCHES:
        destinations = list(struct.unpack("<" + "I" * count,
                                         canonical.target_bytes(table, 4 * count)))
        instruction, = (row for row in rows if row.address == site)
        if instruction.mnemonic != "jmp" or instruction.operands[0].mem.disp != table:
            raise ValueError("Iku switch dispatch differs")
        switches[table] = (hex(site), destinations)
        for destination in destinations:
            incoming[destination].add(site)
    for row in rows:
        if (row.group(capstone.CS_GRP_JUMP) or row.group(capstone.CS_GRP_CALL)):
            if row.operands[0].type == X86_OP_IMM:
                incoming[row.operands[0].imm & 0xFFFFFFFF].add(row.address)
    boundary = reachable_boundary_audit(body, START, switches)
    if (boundary["reachable_bytes"] != SIZE or boundary["reachable_instructions"] != 15132
            or boundary["unreached_ranges"] or boundary["unresolved_indirect_exits"]
            or boundary["internal_call_targets"]):
        raise ValueError("whole Iku CFG no longer closes")
    # Pin the actual selector's two unsigned divisions before using its range.
    selector = canonical.target_bytes(0x4067D0, 27)
    actual = [(row.mnemonic, row.op_str) for row in decode(selector, 0x4067D0)]
    expected = [("push", "esi"), ("call", "0x4066b0"), ("mov", "ecx, eax"),
                ("or", "eax, 0xffffffff"), ("xor", "edx, edx"),
                ("div", "dword ptr [esp + 8]"), ("xor", "edx, edx"),
                ("mov", "esi, eax"), ("mov", "eax, ecx"), ("div", "esi"),
                ("pop", "esi"), ("ret", "")]
    if actual != expected:
        raise ValueError("selector range proof no longer matches its target body")
    facts = [prove_fixup(rows, index, incoming, canonical.target_bytes)
             for index, row in enumerate(rows)
             if row.mnemonic == "fadd" and row.op_str == "dword ptr [0x6d6ef8]"]
    if len(facts) != 46 or sum(fact["kind"] == "unsigned_remainder" for fact in facts) != 17:
        raise ValueError("Iku conversion inventory differs")
    if [fact["correction"] for fact in facts if fact["guard_always_taken"] is not True] != [0x62C5D4]:
        raise ValueError("Iku feasible unsigned correction inventory differs")
    writes = [row for row in rows if X86_REG_ESI in row.regs_access()[1] and row.mnemonic != "pop"]
    if len(writes) != 1 or (writes[0].address, writes[0].mnemonic, writes[0].op_str) != (0x62092F, "mov", "esi, ecx"):
        raise ValueError("ESI is not an invariant root receiver")
    epilogue = [("pop", "ebp"), ("pop", "ebx"), ("mov", "esp, ebp"), ("pop", "ebp"), ("ret", "")]
    for index, row in enumerate(rows):
        if (row.mnemonic, row.op_str) == ("pop", "esi"):
            if [(item.mnemonic, item.op_str) for item in rows[index + 1:index + 6]] != epilogue:
                raise ValueError("receiver restore is not immediately followed by the root RET epilogue")
    fields = {}
    for row in rows:
        for operand in row.operands:
            if operand.type != X86_OP_MEM or operand.mem.base != X86_REG_ESI:
                continue
            if operand.mem.index:
                raise ValueError("indexed receiver access requires another layout model")
            offset = operand.mem.disp
            field = fields.setdefault(offset, {"offset": offset, "widths": set(),
                                               "operations": set(), "witnesses": []})
            field["widths"].add(operand.size)
            if row.mnemonic not in field["operations"]:
                field["witnesses"].append({"address": row.address, "instruction": row.mnemonic + " " + row.op_str})
            field["operations"].add(row.mnemonic)
    for field in fields.values():
        field["widths"] = sorted(field["widths"])
        field["operations"] = sorted(field["operations"])
        field["address_only"] = field["operations"] == ["lea"]
        if not field["address_only"]:
            offset, (width,), operations = field["offset"], field["widths"], field["operations"]
            kind = f"undefined{width}"
            if width == 4 and any(operation.startswith("f") for operation in operations):
                kind = "float32"
            if offset in (0, 0x170):
                kind = "void_pointer32"
            if offset == 0x104:
                kind = "signed_char"
            if width == 2 and ("movsx" in operations or offset in (0x13C, 0x13E, 0x140, 0x142)):
                kind = "signed_short"
            if offset == 0x144:
                kind = "signed_int"
            prefix = "float" if kind == "float32" else "byte" if width == 1 else "word" if width == 2 else "field"
            name = f"{prefix}_{offset:03x}"
            if offset == 0:
                name = "vtable_000"
            if offset == 0x170:
                name = "peer_170"
            field["working_field"] = {"name": name, "type": kind,
                                      "scope": "partial method view; not unique original C++ spelling"}
    return {"schema": "th105-iku-random-float-tails-v1", "target_sha256": target_sha,
            "root_body_sha256": BODY_SHA, "selector_sha256": hashlib.sha256(selector).hexdigest(),
            "raw_boundary": boundary, "corrections": facts,
            "receiver_accesses": [fields[offset] for offset in sorted(fields)],
            "scope": "46 unsigned conversion guards:45 corrections infeasible on normal root CFG, "
                     "62C5D4 remains feasible after unsigned selector(400)-200; "
                     "17 remainder and29 selector ranges; ESI field witnesses are not a complete class layout; "
                     "no source-present, exclusion or exact credit"}


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
