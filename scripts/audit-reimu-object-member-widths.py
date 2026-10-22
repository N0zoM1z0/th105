#!/usr/bin/env python3
"""Attest selected direct ESI field widths in the complete496540 code ranges."""
from __future__ import annotations

from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "member_widths", ROOT / "scripts/audit-reimu-object-804-lifetimes.py"
)
lifetimes = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(lifetimes)
native, x = lifetimes.native, lifetimes.x
FIELDS = {
    0x110: 1, 0x111: 1, 0x112: 1, 0x113: 1,
    0x13C: 2, 0x13E: 2, 0x140: 2, 0x142: 2, 0x144: 4,
    0x170: 4, 0x174: 2, 0x180: 4, 0x184: 1,
    0x330: 4, 0x33C: 1, 0x348: 4, 0x34C: 4,
    0x364: 2, 0x366: 2, 0x368: 2, 0x36A: 2, 0x36C: 2,
}


def audit():
    paths = [ROOT / "resources/th105.exe", Path(__file__),
             ROOT / "scripts/audit-reimu-object-update-target.py",
             ROOT / "scripts/audit-reimu-object-804-lifetimes.py",
             ROOT / "config/target.toml", ROOT / "config/function-byte-ownership.toml"]
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}
    before = pins()
    native.facts.audit()
    rows = [row for lo, hi in native.facts.RANGES
            for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)]
    fields = []
    for offset, width in FIELDS.items():
        hits = [(row, operand) for row in rows for operand in row.operands
                if operand.type == x.X86_OP_MEM and operand.mem.base == x.X86_REG_ESI
                and not operand.mem.index and operand.mem.disp == offset]
        if not hits or {operand.size for _, operand in hits} != {width}:
            raise ValueError(f"selected field access width changed at {offset:#x}")
        fields.append(dict(offset=offset, width=width, count=len(hits),
                           mnemonics=dict(Counter(row.mnemonic for row, _ in hits)),
                           instructions=[dict(address=row.address, bytes=row.bytes.hex(),
                                              text=row.mnemonic + " " + row.op_str)
                                         for row, _ in hits]))
    writes = [row for row in rows
              if set(row.regs_access()[1]) & {x.X86_REG_ESI, x.X86_REG_SI}]
    if (sum(row.mnemonic == "mov" and row.op_str == "esi, ecx" for row in writes) != 1
            or any((row.mnemonic, row.op_str) not in (("mov", "esi, ecx"), ("pop", "esi"))
                   for row in writes) or before != pins()):
        raise ValueError("changed owner register or member-width inputs")
    return dict(schema="th105-reimu-object-member-widths-v1",
                target_sha256=native.c.verify_target(), input_pins=before,
                evidence_class="raw target instruction observations",
                field_count=len(fields), direct_observations=sum(field["count"] for field in fields),
                fields=fields, esi_writes=[dict(address=row.address,
                                                text=row.mnemonic + " " + row.op_str) for row in writes],
                scope="selected direct nonindexed ESI accesses in reviewed root code ranges; "
                      "this does not establish unique C++ types, member grouping, nominal base "
                      "ownership, indirect accesses or complete dynamic parent identity")


if __name__ == "__main__":
    print(json.dumps(audit(), indent=2))
