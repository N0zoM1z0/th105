#!/usr/bin/env python3
"""Close the 1.06a scenario interpreter's bytes, CFG and command table.

Target observations only: no source equivalence or exact compiler claim.
"""
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, CODE_END, TABLE, END = 0x458440, 0x459C29, 0x459C2C, 0x459C88
CODE_SHA = "7062af4006e7ea7f92d8401280bfe123715b729eb1c1bf991e15b6f892de915f"
UNREACHED = {0x45879A: "8d9b00000000", 0x4596D8: "8da42400000000", 0x4596DF: "90"}


def require(ok, message):
    if not ok:
        raise ValueError(message)


def audit():
    spec = importlib.util.spec_from_file_location(
        "scenario_target_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    target = compare.verify_target()
    payload = compare.target_bytes(ADDRESS, END - ADDRESS)
    code = payload[:CODE_END - ADDRESS]
    require(hashlib.sha256(code).hexdigest() == CODE_SHA, "code pin changed")
    require(compare.target_bytes(0x6C2998, 4) == struct.pack("<I", ADDRESS),
            "scenario vtable slot08 changed")
    require(compare.target_bytes(CODE_END, 3).hex() == "8d4900", "alignment changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == len(code), "decode incomplete")
    require(len(instructions) == 1693, "instruction census changed")
    by_address = {i.address: i for i in instructions}
    destinations = struct.unpack("<23I", compare.target_bytes(TABLE, 92))
    require(all(a in by_address for a in destinations), "command edge escapes code")
    calls, indirect_calls, returns = Counter(), [], []
    jumps = []
    for i in instructions:
        if i.mnemonic == "call":
            if i.operands[0].type == x86.X86_OP_IMM:
                calls[i.operands[0].imm] += 1
            else:
                indirect_calls.append(dict(address=hex(i.address), operand=i.op_str))
        if i.mnemonic == "ret":
            require(bytes(i.bytes) == b"\xc3", "return purge changed")
            returns.append(i.address)
        if i.mnemonic == "jmp" and i.operands[0].type != x86.X86_OP_IMM:
            operand = i.operands[0]
            require(operand.type == x86.X86_OP_MEM and not operand.mem.base
                    and operand.mem.index == x86.X86_REG_EAX
                    and operand.mem.scale == 4 and operand.mem.disp == TABLE,
                    "unreviewed indirect edge")
            jumps.append(i.address)
    require(jumps == [0x458C7F] and returns == [0x458965], "dispatch/exit changed")
    require(sum(calls.values()) == 216 and len(indirect_calls) == 14,
            "call census changed")
    reached, pending = set(), [ADDRESS]
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, f"escaping/noninstruction edge {address:#x}")
        reached.add(address)
        i = by_address[address]
        if i.mnemonic == "ret":
            continue
        if i.mnemonic == "jmp":
            pending.extend([i.operands[0].imm] if i.operands[0].type == x86.X86_OP_IMM
                           else destinations)
            continue
        if i.group(capstone.CS_GRP_JUMP):
            pending.append(i.operands[0].imm)
        pending.append(address + i.size)
    unreached = {i.address: bytes(i.bytes).hex()
                 for i in instructions if i.address not in reached}
    require(unreached == UNREACHED and len(reached) == 1690, "unreached bytes changed")
    require(compare.target_bytes(0x458940, 2).hex() == "b001"
            and compare.target_bytes(0x458B61, 2).hex() == "32c0"
            and compare.target_bytes(0x459C22, 2).hex() == "0cff",
            "AL exit carriers changed")
    require(compare.target_bytes(0x458454, 6).hex() == "81ec88020000",
            "aligned frame changed")
    return dict(
        result="target_cfg_closed", evidence_class="hash-attested target bytes/edges",
        target_sha256=target, address=hex(ADDRESS), code_size=len(code),
        code_sha256=CODE_SHA, code_end_exclusive=hex(CODE_END),
        payload_size=len(payload), payload_sha256=hashlib.sha256(payload).hexdigest(),
        payload_end_exclusive=hex(END), instructions=len(instructions),
        reached=len(reached), unreachable_alignment={hex(a): b for a, b in unreached.items()},
        external_edges=[], explicit_aligned_frame=0x288, ret0_sites=[hex(a) for a in returns],
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        indirect_call_sites=indirect_calls,
        command_table={str(n): hex(a) for n, a in enumerate(destinations)},
        metadata=dict(alignment_bytes=3, destination_dwords=23, total_bytes=95),
        trailing_eight_int3=compare.target_bytes(END, 8).hex(),
        trailing_int3_object_linker_ownership="unknown; outside this payload",
        return_observation="AL exits 00/01/FF; upper EAX not established",
        original_return_type="unknown; signed-char source view hypothesis",
        source_present_claim=False, exact_claim=False,
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
