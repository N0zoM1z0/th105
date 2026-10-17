#!/usr/bin/env python3
"""Raw normal-return closure and width/order facts for Iku's42 middle actions.

This describes regions inside620920, not new callable/ownership boundaries or
partial authored acceptance. Decompiled text is not an input.
"""
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone.x86 import X86_OP_MEM

from giant_owner_audit import decode
from iku_middle_actions import MIDDLE_ENTRIES
from iku_upper_actions import ENTRIES as UPPER_ENTRIES
from linked_pe import comparator

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("iku_upper_raw_closure", ROOT / "scripts/audit-iku-upper-actions.py")
upper = importlib.util.module_from_spec(spec)
spec.loader.exec_module(upper)


def audit():
    canonical = comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(0x620920, 59038)
    root_sha = hashlib.sha256(body).hexdigest()
    if root_sha != upper.ROOT_SHA:
        raise ValueError("Iku root differs")
    rows = {row.address: row for row in decode(body, 0x620920)}
    table = struct.unpack("<42I", canonical.target_bytes(0x62F128, 168))
    lookup = canonical.target_bytes(0x62F1D0, 247)
    observed = {301 + i: table[index] for i, index in enumerate(lookup) if table[index] != 0x62EFA5}
    if observed != {a: entry for a, entry in MIDDLE_ENTRIES.items() if a != 300}:
        raise ValueError("middle switch selector/entry map differs")
    expected = {
        0x620B03: ("je", "0x62360e"),
        0x623D78: ("cmp", "byte ptr [esi + 0x47e], al"),
        0x623D7E: ("jle", "0x623db8"),
        0x6244E3: ("add", "word ptr [esi + 0x730], di"),
        0x624549: ("add", "word ptr [esi + 0x730], di"),
        0x6245BF: ("fadd", "dword ptr [esi + 0xf0]"),
        0x6245C5: ("fstp", "qword ptr [esp + 0x18]"),
        0x628D15: ("fadd", "dword ptr [esi + 0xf0]"),
        0x628D1B: ("fstp", "qword ptr [esp + 0x18]"),
        0x628D4D: ("call", "eax"),
        0x628D51: ("call", "0x435d60"),
        0x628B49: ("fld", "dword ptr [esi + 0xec]"),
        0x628B4F: ("fstp", "dword ptr [esp]"),
        0x628B99: ("fld", "dword ptr [esi + 0xec]"),
    }
    for address, instruction in expected.items():
        if (rows[address].mnemonic, rows[address].op_str) != instruction:
            raise ValueError(f"middle discriminator differs at {address:x}")
    seen = upper.closure(rows, MIDDLE_ENTRIES.values())
    if (len(seen), sum(rows[a].size for a in seen)) != (5799, 22738):
        raise ValueError("middle normal-return CFG differs")
    intervals = ((0x62360E, 0x623724), (0x623753, 0x628EAD))
    physical = {a for a in rows if any(first <= a < last for first, last in intervals)}
    if physical - seen or (len(physical), sum(rows[a].size for a in physical)) != (5746, 22640):
        raise ValueError("middle physical region differs")
    all_seen = upper.closure(rows, (MIDDLE_ENTRIES | UPPER_ENTRIES).values())
    literals, calls = {}, {}
    for address in sorted(seen):
        row = rows[address]
        if row.group(capstone.CS_GRP_CALL):
            calls.setdefault(row.op_str, []).append(address)
        if not row.mnemonic.startswith("f"):
            continue
        for op in row.operands:
            if op.type == X86_OP_MEM and not (op.mem.base or op.mem.index) and op.size in (4, 8):
                key = f"{op.mem.disp:x}/{op.size}"
                if key not in literals:
                    raw = canonical.target_bytes(op.mem.disp, op.size)
                    literals[key] = {"address": op.mem.disp, "width": op.size, "bytes": raw.hex(),
                                     "value": struct.unpack("<f" if op.size == 4 else "<d", raw)[0], "sites": []}
                literals[key]["sites"].append(address)
    return {"schema": "th105-iku-middle-action-facts-v1", "target_sha256": target_sha, "root_sha256": root_sha,
            "entries": MIDDLE_ENTRIES, "cfg_instructions": len(seen), "cfg_bytes": sum(rows[a].size for a in seen),
            "physical_intervals": intervals, "physical_bytes": sum(rows[a].size for a in physical),
            "physical_not_reached": sorted(physical - seen), "remote_instructions": sorted(seen - physical),
            "remote_bytes": sum(rows[a].size for a in seen - physical), "discriminators": expected,
            "all_staged_actions": len(MIDDLE_ENTRIES) + len(UPPER_ENTRIES),
            "all_staged_cfg_instructions": len(all_seen), "all_staged_cfg_bytes": sum(rows[a].size for a in all_seen),
            "calls": calls, "x87_literals": list(literals.values()),
            "scope": "normal-return direct closure, including static call continuations; "
                     "shared unions are not standalone functions or additive authored/exact credit"}


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
