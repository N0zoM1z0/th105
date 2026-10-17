#!/usr/bin/env python3
"""Close the raw normal-return CFGs of the nine newly staged upper actions."""
import hashlib
import json
import struct

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

from giant_owner_audit import decode
from iku_upper_actions import ENTRIES, NEW_ENTRIES
from linked_pe import comparator

ROOT_SHA = "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea"


def closure(rows, entries):
    pending, seen = list(entries), set()
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        if address not in rows:
            raise ValueError("upper action edge leaves root or enters an instruction")
        seen.add(address)
        row = rows[address]
        if row.group(capstone.CS_GRP_RET):
            continue
        targets = [address + row.size]
        if row.group(capstone.CS_GRP_JUMP):
            if row.operands[0].type != X86_OP_IMM:
                raise ValueError("unreviewed upper action indirect jump")
            targets = [row.operands[0].imm] + ([] if row.mnemonic == "jmp" else targets)
        pending.extend(targets)
    return seen


def audit():
    canonical = comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(0x620920, 59038)
    if hashlib.sha256(body).hexdigest() != ROOT_SHA:
        raise ValueError("Iku root differs")
    rows = {row.address: row for row in decode(body, 0x620920)}
    table = struct.unpack("<35I", canonical.target_bytes(0x62F2C8, 140))
    lookup = canonical.target_bytes(0x62F354, 238)
    if {561 + i for i, index in enumerate(lookup) if table[index] != 0x62EFA5} != set(ENTRIES) - {560}:
        raise ValueError("complete high-switch action set differs")
    for action, entry in ENTRIES.items():
        if action != 560 and table[lookup[action - 561]] != entry:
            raise ValueError("compressed upper entry differs")
    evidence = {
        0x623724: ("cmp", "eax, 0x230"),
        0x62372F: ("je", "0x628ead"),
        0x62919C: ("fcomp", "qword ptr [0x6c4c98]"),
        0x62960F: ("fcom", "st(1)"),
        0x62962A: ("fcomp", "qword ptr [0x6c1888]"),
        0x62B94E: ("jge", "0x62b993"),
        0x62B986: ("push", "edi"),
        0x62BC24: ("div", "ecx"),
        0x62BC4F: ("div", "ecx"),
        0x62BCD6: ("div", "ecx"),
        0x62BBF5: ("mov", "ebx, 5"),
        0x62BBFA: ("jle", "0x62bd84"),
        0x62BC08: ("jge", "0x62bd84"),
        0x62BC12: ("jge", "0x62bd84"),
    }
    for address, expected in evidence.items():
        if (rows[address].mnemonic, rows[address].op_str) != expected:
            raise ValueError(f"raw upper discriminator differs at {address:x}")
    seen = closure(rows, NEW_ENTRIES.values())
    all_seen = closure(rows, ENTRIES.values())
    if (len(seen), sum(rows[a].size for a in seen), len(all_seen),
            sum(rows[a].size for a in all_seen)) != (969, 3770, 6324, 24997):
        raise ValueError("upper CFG union differs")
    intervals = ((0x628EAD, 0x62909C), (0x6290BA, 0x6296BE), (0x62B784, 0x62BDC2))
    physical = {a for a in rows if any(first <= a < last for first, last in intervals)}
    if physical - seen:
        raise ValueError("new family physical ownership differs")
    literals = {}
    for address in sorted(seen):
        row = rows[address]
        if not row.mnemonic.startswith("f"):
            continue
        for op in row.operands:
            if op.type == X86_OP_MEM and not (op.mem.base or op.mem.index) and op.size in (4, 8):
                key = (op.mem.disp, op.size)
                if key not in literals:
                    raw = canonical.target_bytes(op.mem.disp, op.size)
                    literals[key] = {"address": op.mem.disp, "width": op.size, "bytes": raw.hex(),
                                     "value": struct.unpack("<f" if op.size == 4 else "<d", raw)[0], "sites": []}
                literals[key]["sites"].append(address)
    return {"schema": "th105-iku-upper-action-facts-v1", "target_sha256": target_sha, "root_sha256": ROOT_SHA,
            "new_entries": NEW_ENTRIES, "new_cfg_instructions": len(seen),
            "new_cfg_bytes": sum(rows[a].size for a in seen),
            "physical_intervals": intervals, "physical_bytes": sum(last - first for first, last in intervals),
            "physical_not_reached": sorted(physical - seen), "remote_instructions": sorted(seen - physical),
            "all_upper_actions": len(ENTRIES), "all_upper_cfg_instructions": len(all_seen),
            "all_upper_cfg_bytes": sum(rows[a].size for a in all_seen),
            "per_action": [{"action": action, "entry": entry,
                            "instructions": len(closure(rows, [entry])),
                            "bytes": sum(rows[a].size for a in closure(rows, [entry]))}
                           for action, entry in NEW_ENTRIES.items()],
            "raw_discriminators": evidence, "x87_literals": list(literals.values()),
            "scope": "normal-return direct CFG closure; call continuations are static only; "
                     "overlapping regions are not independent functions or additive authored credit"}


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
