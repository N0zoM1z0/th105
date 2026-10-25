#!/usr/bin/env python3
"""Close Alice's complete 1.06a Fighter update CFG and metadata ownership.

This reads only the hash-attested PE. It proves byte/edge facts, not a source
implementation, original type names, or an exact compiler match.
"""
from __future__ import annotations

from collections import Counter
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, CODE_END, PAYLOAD_END = 0x4E9F50, 0x4F4631, 0x4F4B80
CODE_SHA256 = "588194779ec2bba363702ac150979a064ce8bf77553bfa727b34951fc8788a89"
PAYLOAD_SHA256 = "2bd6bb53be12d74e98f1fee7dfcedf2b1adcf71597fd89a9ce8185f4d0e1f823"
TABLES = {
    0x4F4634: 31, 0x4F4794: 34, 0x4F48EC: 5, 0x4F4900: 5,
    0x4F4914: 40, 0x4F4AB0: 5, 0x4F4AC4: 5, 0x4F4AD8: 5,
    0x4F4AEC: 5, 0x4F4B00: 5, 0x4F4B14: 5, 0x4F4B28: 4,
    0x4F4B38: 4, 0x4F4B48: 4, 0x4F4B58: 4, 0x4F4B68: 4,
}
REGIONS = (
    (0, 226, 0x4F4634, 0x4F46B0),
    (301, 508, 0x4F4794, 0x4F481C),
    (521, 770, 0x4F4914, 0x4F49B4),
)
METADATA_GAPS = {
    0x4F4631: bytes.fromhex("8d4900"),
    0x4F4793: bytes.fromhex("90"),
    0x4F4AAE: bytes.fromhex("8bff"),
    0x4F4B78: bytes.fromhex("cccccccccccccccc"),
}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def audit():
    spec = importlib.util.spec_from_file_location(
        "alice_fighter_target_comparator", ROOT / "scripts/compare-function.py")
    comparator = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(comparator)
    identity = comparator.verify_target()
    payload = comparator.target_bytes(ADDRESS, PAYLOAD_END - ADDRESS)
    code = payload[:CODE_END - ADDRESS]
    require(hashlib.sha256(code).hexdigest() == CODE_SHA256, "main byte pin changed")
    require(hashlib.sha256(payload).hexdigest() == PAYLOAD_SHA256, "payload byte pin changed")
    require(struct.unpack("<I", comparator.target_bytes(0x6C4C04, 4))[0] == ADDRESS,
            "Alice primary vtable slot28 changed")
    with (ROOT / "config/functions.csv").open(newline="") as handle:
        rows = {int(row["address"], 0): row for row in csv.DictReader(handle)}
    require(int(rows[ADDRESS]["size"]) == len(code), "candidate main size changed")

    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == len(code), "main decoding incomplete")
    require(len(instructions) == 11170, "instruction census changed")
    by_address = {i.address: i for i in instructions}
    tables = {}
    metadata = bytearray(PAYLOAD_END - CODE_END)

    def own_metadata(address, size):
        offset = address - CODE_END
        require(0 <= offset <= len(metadata) - size, "metadata escapes complete payload")
        require(not any(metadata[offset:offset + size]), "metadata ranges overlap")
        metadata[offset:offset + size] = b"\x01" * size

    for address, count in TABLES.items():
        destinations = struct.unpack("<" + "I" * count,
                                    comparator.target_bytes(address, count * 4))
        require(all(a in by_address for a in destinations), "table edge escapes instruction starts")
        tables[address] = destinations
        own_metadata(address, count * 4)
    regions = []
    for first, last, table, remap in REGIONS:
        indices = comparator.target_bytes(remap, last - first + 1)
        require(max(indices) < len(tables[table]), "remap index escapes destination table")
        own_metadata(remap, len(indices))
        regions.append(dict(first=first, last=last, table=hex(table), remap=hex(remap),
                            groups=len(set(indices)),
                            remap_sha256=hashlib.sha256(indices).hexdigest()))
    for address, expected in METADATA_GAPS.items():
        require(comparator.target_bytes(address, len(expected)) == expected,
                "metadata alignment pin changed")
        own_metadata(address, len(expected))
    require(all(metadata), "complete metadata ownership has a hole")

    indirect_jumps = set()
    calls = Counter()
    indirect_calls = []
    returns = []
    for instruction in instructions:
        operand = instruction.operands[0] if instruction.operands else None
        if instruction.mnemonic == "jmp" and operand.type != x86.X86_OP_IMM:
            require(operand.type == x86.X86_OP_MEM and not operand.mem.base
                    and operand.mem.index and operand.mem.scale == 4
                    and operand.mem.disp in tables, "unreviewed indirect jump")
            indirect_jumps.add(operand.mem.disp)
        if instruction.mnemonic == "call":
            if operand.type == x86.X86_OP_IMM:
                calls[operand.imm] += 1
            else:
                require(operand.type == x86.X86_OP_REG, "indirect call form changed")
                indirect_calls.append(hex(instruction.address))
        if instruction.mnemonic == "ret":
            require(bytes(instruction.bytes) == b"\xc3", "root no longer has RET0 only")
            returns.append(hex(instruction.address))
    require(indirect_jumps == set(tables), "jump/table ownership differs")
    require(sum(calls.values()) == 674 and len(calls) == 27, "direct call census changed")
    require(len(indirect_calls) == 163 and len(returns) == 128, "call/return census changed")

    reached, pending = set(), [ADDRESS]
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, f"escaping or noninstruction CFG edge {address:#x}")
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == "ret":
            continue
        if instruction.mnemonic == "jmp":
            operand = instruction.operands[0]
            pending.extend(tables[operand.mem.disp] if operand.type == x86.X86_OP_MEM
                           else [operand.imm])
            continue
        if instruction.group(capstone.CS_GRP_JUMP):
            pending.append(instruction.operands[0].imm)
        pending.append(address + instruction.size)
    unreachable = [i for i in instructions if i.address not in reached]
    require(len(unreachable) == 1 and unreachable[0].address == 0x4F28ED
            and bytes(unreachable[0].bytes) == bytes.fromhex("8d4900"),
            "unreachable alignment pin changed")
    return dict(
        result="target_cfg_closed", evidence_class="hash-attested target bytes and edges",
        source_present_claim=False, exact_claim=False, target_sha256=identity,
        address=hex(ADDRESS), code_end_exclusive=hex(CODE_END), payload_end_exclusive=hex(PAYLOAD_END),
        main_size=len(code), main_sha256=CODE_SHA256, payload_size=len(payload),
        payload_sha256=PAYLOAD_SHA256, instructions=len(instructions), reached=len(reached),
        unreachable_alignment=dict(address="0x4F28ED", bytes="8d4900"), external_edges=[],
        aligned_frame_bytes=0x410, ret0_sites=returns, indirect_call_sites=indirect_calls,
        direct_calls={hex(a): dict(count=n, name=rows[a]["proposed_name"],
                                  signature=rows[a]["signature"], status=rows[a]["status"])
                      for a, n in sorted(calls.items())},
        tables={hex(a): dict(dwords=len(ds), destinations=[hex(d) for d in ds])
                for a, ds in sorted(tables.items())},
        regions=regions, metadata_bytes=len(metadata), destination_dwords=165, remap_bytes=685,
        metadata_alignment_bytes=14,
    )


def main():
    try:
        report = audit()
    except (OSError, ValueError, KeyError, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
