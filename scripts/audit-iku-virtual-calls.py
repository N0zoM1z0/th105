#!/usr/bin/env python3
"""Qualify all Iku root register calls, retaining mixed virtual-slot joins.

Target observations plus ordinary-ABI/valid-Iku receiver inference only.
No target is selected arbitrarily at a multi-target call and no exact credit
is assigned by this report.
"""
from collections import Counter
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
import pefile

from giant_owner_audit import decode
from linked_pe import comparator, primary_type_name
from typed_indirect_tails import receiver_tail_facts

ROOT = Path(__file__).resolve().parents[1]
VTABLE = 0x6C652C
SLOTS = {8: 0x45BFE0, 12: 0x45C390, 20: 0x45C220, 28: 0x45C180}


def conversion_runtime(canonical):
    # This is a shared runtime island, not a newly accepted function boundary.
    code = canonical.target_bytes(0x68A1A0, 171)
    digest = hashlib.sha256(code).hexdigest()
    if digest != "aeb7a87183a558dd228b968d6264bdeb993114992b7807d638c943a2adadd1a2":
        raise ValueError("VC8 conversion island differs")
    fast = decode(code[:28], 0x68A1A0)
    if [(row.address, row.mnemonic, row.op_str) for row in fast] != [
        (0x68A1A0, "cmp", "dword ptr [0x7039c8], 0"),
        (0x68A1A7, "je", "0x68a1d6"),
        (0x68A1A9, "push", "ebp"), (0x68A1AA, "mov", "ebp, esp"),
        (0x68A1AC, "sub", "esp, 8"), (0x68A1AF, "and", "esp, 0xfffffff8"),
        (0x68A1B2, "fstp", "qword ptr [esp]"),
        (0x68A1B5, "cvttsd2si", "eax, qword ptr [esp]"),
        (0x68A1BA, "leave", ""), (0x68A1BB, "ret", ""),
    ]:
        raise ValueError("VC8 conversion fast-path physical contract differs")
    return {"entry": 0x68A1A0, "island_size": len(code), "island_sha256": digest,
            "input_storage": "ST0:10", "output_storage": "EAX:4", "stack_argument_bytes": 0,
            "stack_purge_bytes": 0, "fast_path": [row.address for row in fast],
            "scope": "entry consumes ST0 and returns int32 in EAX; SSE fast path never writes EDX; "
                     "shared fallback also computes EDX, which does not establish an int64 return "
                     "for this entry; custom compiler ABI, not a normal C++ helper declaration"}


def audit():
    spec = importlib.util.spec_from_file_location("iku_virtual_root_facts", ROOT / "scripts/audit-iku-random-float-tails.py")
    root = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(root)
    facts = root.audit()
    canonical = comparator()
    image = pefile.PE(str(ROOT / "resources/th105.exe"))
    if (primary_type_name(image, VTABLE) != ".?AVIku@@"
            or struct.unpack("<I", canonical.target_bytes(VTABLE + 0x28, 4))[0] != root.START):
        raise ValueError("Iku primary receiver/vslot28 domain differs")
    ledger = {int(row["address"], 0): row
              for row in csv.DictReader((ROOT / "config/functions.csv").open())}
    matches = {int(row["address"], 0): row
               for row in csv.DictReader((ROOT / "config/matches.csv").open())}
    methods = {}
    for offset, address in SLOTS.items():
        if struct.unpack("<I", canonical.target_bytes(VTABLE + offset, 4))[0] != address:
            raise ValueError("Iku virtual interface target differs")
        if (ledger[address]["status"] != "matching" or address not in matches
                or matches[address]["status"] != "matching"
                or matches[address]["match_percent"] != "100.00"):
            raise ValueError("virtual target lacks its accepted interface implementation")
        methods[offset] = {"target": address, "name": ledger[address]["proposed_name"],
                           "signature": ledger[address]["signature"],
                           "source": ledger[address]["source_file"],
                           "stack_argument_bytes": 0 if offset == 20 else 4}
    switches = {table: list(struct.unpack("<" + "I" * count, canonical.target_bytes(table, 4 * count)))
                for site, table, count in root.SWITCHES}
    code = canonical.target_bytes(root.START, root.SIZE)
    rows = decode(code, root.START)
    for row in rows:
        for operand in row.operands:
            if (operand.type == capstone.x86.X86_OP_MEM
                    and operand.mem.base == capstone.x86.X86_REG_ESI and not operand.mem.index
                    and operand.mem.disp == 0 and operand.access & capstone.CS_AC_WRITE):
                raise ValueError("root mutates its receiver vptr")
    flow = receiver_tail_facts(code, root.START, switches, include_calls=True, allow_slot_unions=True)
    calls = flow["register_indirect_calls"]
    if flow["reachable_instructions"] != 15132 or len(calls) != 177 or flow["register_tail_exits"]:
        raise ValueError("Iku receiver/call traversal no longer closes")
    for call in calls:
        slots = call["possible_vtable_slots"]
        if not call["ecx_is_entry_receiver"] or not slots or not set(slots) <= SLOTS.keys():
            raise ValueError("unqualified Iku register call")
        call["inferred_domain_targets"] = [SLOTS[slot] for slot in slots]
        widths = {methods[slot]["stack_argument_bytes"] for slot in slots}
        if len(widths) != 1:
            raise ValueError("mixed call has incompatible physical argument cleanup")
        call["stack_argument_bytes"] = next(iter(widths))
    mixed = [call for call in calls if len(call["possible_vtable_slots"]) > 1]
    if [(call["address"], call["possible_vtable_slots"]) for call in mixed] != [(0x621040, [8, 12])]:
        raise ValueError("Iku mixed-target join differs")
    counts = Counter(tuple(call["possible_vtable_slots"]) for call in calls)
    return {"schema": "th105-iku-virtual-call-facts-v1", "target_sha256": facts["target_sha256"],
            "root_sha256": facts["root_body_sha256"], "vtable": VTABLE, "methods": methods,
            "conversion_runtime": conversion_runtime(canonical),
            "call_groups": [{"slots": list(slots), "sites": count} for slots, count in sorted(counts.items())],
            "dataflow": flow,
            "scope": "all177 register CALLs, under ordinary x86 callee-save rules and valid Iku primary receiver; "
                     "176 single-slot sites and621040 with both8/C targets; raw bytes/CFG unchanged; "
                     "not a direct-call binding, original C++ declaration proof, complete gameplay or exact acceptance"}


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
