#!/usr/bin/env python3
"""Raw control/precision facts for Iku's fourteen high-switch arms after610.

Regions and shared tails are diagnostics, not independent compiler functions
or partial authored-byte acceptance. No decompiler text is required.
"""
import hashlib
import json
import struct

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

from giant_owner_audit import decode
from linked_pe import comparator

ENTRIES = {650: 0x62D02A, 660: 0x62D1DE, 695: 0x62D5C7, 696: 0x62D72D,
           710: 0x62D7E1, 720: 0x62D8B0, 730: 0x62DA63, 740: 0x62E341,
           770: 0x62E4F1, 780: 0x62E588, 781: 0x62E909, 795: 0x62EADA,
           797: 0x62EB17, 798: 0x62ED65}
END = 0x62EFA5


def audit():
    canonical = comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(0x620920, 59038)
    digest = hashlib.sha256(body).hexdigest()
    if digest != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku root differs")
    rows = {row.address: row for row in decode(body, 0x620920)}
    table = struct.unpack("<35I", canonical.target_bytes(0x62F2C8, 140))
    lookup = canonical.target_bytes(0x62F354, 238)
    for action, entry in ENTRIES.items():
        if table[lookup[action - 561]] != entry:
            raise ValueError("late compressed action entry differs")
    pending, seen = list(ENTRIES.values()), set()
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        if address not in rows:
            raise ValueError("late action edge leaves root or enters an instruction")
        seen.add(address)
        row = rows[address]
        if row.group(capstone.CS_GRP_RET):
            continue
        destinations = [address + row.size]
        if row.group(capstone.CS_GRP_JUMP):
            if row.operands[0].type != X86_OP_IMM:
                raise ValueError("unreviewed late-family indirect jump")
            destinations = [row.operands[0].imm] + ([] if row.mnemonic == "jmp" else destinations)
        pending.extend(destinations)
    physical = {a for a in rows if ENTRIES[650] <= a < END}
    if (len(physical), len(seen), sum(rows[a].size for a in seen)) != (2052, 2150, 8270):
        raise ValueError("complete late-family CFG differs")
    if physical - seen != {0x62EAC9}:
        raise ValueError("shared physical tail ownership differs")
    chains = []
    for start, end in ((0x62DB10, 0x62DB2D), (0x62DC8E, 0x62DCAB)):
        chain = [row for row in rows.values() if start <= row.address < end]
        if (sum(row.mnemonic == "fchs" for row in chain) != 2
                or any(row.mnemonic.startswith(("fsub", "fadd")) for row in chain)
                or (chain[-1].mnemonic, chain[-1].op_str) != ("call", "0x4063d0")):
            raise ValueError("heading is not the observed double negation")
        chains.append([{"address": row.address, "instruction": row.mnemonic + " " + row.op_str}
                       for row in chain])
    if (rows[0x62DD7A].mnemonic, rows[0x62DD7A].op_str) != ("jnp", "0x62b981"):
        raise ValueError("ordered positive VX branch differs")
    if [(rows[a].mnemonic, rows[a].op_str) for a in (0x62E5A1, 0x62E5B0, 0x62E5B6, 0x62E5BB)] != [
        ("movsx", "ecx, word ptr [esi + 0x738]"), ("fmul", "qword ptr [0x6c0ec8]"),
        ("call", "0x68a1a0"), ("mov", "word ptr [esi + 0x738], ax"),
    ]:
        raise ValueError("signed WORD/double/truncate decay differs")
    widened = struct.unpack("<f", struct.pack("<f", 0.95))[0]
    if struct.unpack("<d", canonical.target_bytes(0x6C0EC8, 8))[0] != widened or int(20 * widened) != 18:
        raise ValueError("decay constant is not the observed float widening")
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
    cases = []
    items = list(ENTRIES.items())
    for (action, start), end in zip(items, [entry for _, entry in items[1:]] + [END]):
        code = canonical.target_bytes(start, end - start)
        cases.append({"action": action, "entry": start, "physical_end": end, "physical_bytes": len(code),
                      "sha256": hashlib.sha256(code).hexdigest(),
                      "calls": [{"site": row.address, "operand": row.op_str} for row in rows.values()
                                if start <= row.address < end and row.mnemonic == "call"]})
    return {"schema": "th105-iku-late-action-facts-v1", "target_sha256": target_sha, "root_sha256": digest,
            "cases": cases, "cfg_instructions": len(seen), "cfg_bytes": sum(rows[a].size for a in seen),
            "physical_bytes": END - ENTRIES[650], "physical_not_reached_from_family": sorted(physical - seen),
            "remote_instructions": sorted(seen - physical), "heading_chains": chains,
            "decay": {"constant": 0x6C0EC8, "width": 8, "value": widened, "word20_result": 18,
                      "contract": "signed WORD to x87, multiply exact double widening of0.95f, int truncation before WORD store"},
            "x87_literals": list(literals.values()),
            "scope": "fourteen normal-return action CFGs; physical interval contains shared FSTP62EAC9 "
                     "owned by other root paths; no standalone boundary, unique source type or exact credit"}


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
