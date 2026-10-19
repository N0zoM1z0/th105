#!/usr/bin/env python3
"""Check812's caller loop conditional on normal world-call returns.

No call is executed or made to return. This checks the unescaped float counter,
one loop body's stack expressions, and the actual callee's RET1C. The current
iteration may read changed actor/parameter values after an earlier world call.
"""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object812_native", ROOT / "scripts/audit-reimu-object-scalar-actions.py"
)
native = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(native)


def require(ok, message):
    if not ok:
        raise ValueError(message)


def stack_slot(op):
    require(
        op.type == x.X86_OP_MEM
        and op.size == 4
        and op.mem.base == x.X86_REG_ESP
        and not op.mem.index,
        "unreviewed float stack slot",
    )
    return op.mem.disp


def literal(op, read):
    require(
        op.type == x.X86_OP_MEM
        and not op.mem.base
        and not op.mem.index
        and op.size in (4, 8),
        "unreviewed numeric literal",
    )
    return struct.unpack("<f" if op.size == 4 else "<d", read(op.mem.disp, op.size))[0]


def loop_contract(rows, read):
    by_address = {row.address: n for n, row in enumerate(rows)}
    candidates = []
    for n, row in enumerate(rows):
        if row.mnemonic != "jnp" or row.operands[0].type != x.X86_OP_IMM:
            continue
        head = row.operands[0].imm
        if not 0 < row.address - head < 0x200 or head not in by_address:
            continue
        body = rows[by_address[head] : n]
        if any(
            r.mnemonic == "push"
            and r.operands[0].type == x.X86_OP_IMM
            and r.operands[0].imm == 812
            for r in body
        ):
            candidates.append((n, head))
    require(len(candidates) == 1, "expected one812 float caller loop")
    branch_index, head = candidates[0]
    guard = rows[branch_index - 9 : branch_index + 1]
    require(
        [r.mnemonic for r in guard]
        == [
            "fld",
            "fadd",
            "fstp",
            "fld",
            "fld",
            "fcom",
            "fnstsw",
            "fstp",
            "test",
            "jnp",
        ],
        "unreviewed loop guard",
    )
    counter = stack_slot(guard[0].operands[0])
    require(
        stack_slot(guard[2].operands[0]) == counter
        and stack_slot(guard[4].operands[0]) == counter,
        "loop counter slots differ",
    )
    require(
        guard[1].operands[0].size == 8 and literal(guard[1].operands[0], read) == 1.0,
        "loop increment is not double1",
    )
    require(
        guard[3].operands[0].size == 4 and literal(guard[3].operands[0], read) == 8.0,
        "loop bound is not float8",
    )
    require(
        guard[5].operands[0].type == x.X86_OP_REG
        and guard[5].operands[0].reg == x.X86_REG_ST1
        and guard[6].operands[0].reg == x.X86_REG_AX
        and guard[7].operands[0].reg == x.X86_REG_ST1
        and guard[8].operands[0].reg == x.X86_REG_AH
        and guard[8].operands[1].type == x.X86_OP_IMM
        and guard[8].operands[1].imm == 5,
        "guard does not establish ordered counter<8",
    )
    start = by_address[head]
    init = rows[start - 3 : start]
    require(
        [r.mnemonic for r in init] == ["fldz", "fstp", "fld"]
        and stack_slot(init[1].operands[0]) == counter
        and stack_slot(init[2].operands[0]) == counter,
        "counter lacks zero initialization",
    )
    require(
        sum(
            r.mnemonic.startswith("j")
            and r.operands[0].type == x.X86_OP_IMM
            and r.operands[0].imm == head
            for r in rows
        )
        == 1,
        "unreviewed loop entry edge",
    )
    body = rows[start : branch_index - 9]
    require(
        body
        and body[-1].mnemonic == "call"
        and body[-1].address + body[-1].size == guard[0].address,
        "guard does not immediately follow the request",
    )
    sp, fp, memory, registers = 0, ["sector"], {}, {x.X86_REG_ESI: "actor"}

    def value(op):
        if op.type == x.X86_OP_IMM:
            return op.imm
        if op.type == x.X86_OP_REG:
            return registers.get(op.reg, "unknown")
        require(
            op.type == x.X86_OP_MEM and not op.mem.index, "unreviewed value address"
        )
        if op.mem.base == x.X86_REG_ESP:
            return memory.get(sp + stack_slot(op), "unknown")
        if not op.mem.base:
            return literal(op, read)
        base = registers.get(op.mem.base)
        if base == "actor":
            if op.mem.disp == 0x340 and op.size == 4:
                return "parameters"
            if op.mem.disp in (0xEC, 0xF0) and op.size == 4:
                return ("actor_float", op.mem.disp)
            if op.mem.disp == 0x104 and op.size == 1:
                return "unsigned_facing"
        if base == "parameters" and op.mem.disp == 0 and op.size == 4:
            return "current_parameter0"
        raise ValueError("unreviewed body read")

    for row in body:
        ops = row.operands
        if row.mnemonic in ("mov", "movzx"):
            require(
                ops[0].type == x.X86_OP_REG
                and ops[0].size == 4
                and ops[0].reg != x.X86_REG_ESP,
                "unreviewed register assignment",
            )
            registers[ops[0].reg] = value(ops[1])
        elif row.mnemonic == "push":
            require(ops[0].size == 4, "non-dword push")
            sp -= 4
            memory[sp] = value(ops[0])
        elif row.mnemonic == "lea":
            require(
                ops[0].type == x.X86_OP_REG
                and ops[0].size == 4
                and ops[0].reg != x.X86_REG_ESP,
                "unreviewed pointer register",
            )
            registers[ops[0].reg] = ("stack", sp + stack_slot(ops[1]))
        elif row.mnemonic == "sub":
            require(
                ops[0].type == x.X86_OP_REG
                and ops[0].reg == x.X86_REG_ESP
                and ops[1].type == x.X86_OP_IMM
                and ops[1].imm == 8,
                "unreviewed stack allocation",
            )
            sp -= 8
        elif row.mnemonic == "fldz":
            fp.append(0.0)
        elif row.mnemonic == "fld":
            fp.append(value(ops[0]))
        elif row.mnemonic in ("fmul", "fadd"):
            require(bool(fp), "missing x87 operand")
            fp[-1] = ("*" if row.mnemonic == "fmul" else "+", fp[-1], value(ops[0]))
        elif row.mnemonic == "fstp":
            require(bool(fp), "missing x87 store value")
            address = sp + stack_slot(ops[0])
            require(address != counter, "body overwrites the unescaped counter")
            memory[address] = fp.pop()
        elif row.mnemonic == "call":
            require(
                row is body[-1]
                and ops[0].type == x.X86_OP_IMM
                and ops[0].imm == native.SPAWN,
                "unreviewed body call",
            )
        else:
            raise ValueError("unreviewed body instruction " + row.mnemonic)
    require(
        sp == -28 and not fp and registers.get(x.X86_REG_ECX) == "actor",
        "request stack or receiver differs",
    )
    require(
        memory.get(sp) == 812 and memory.get(sp + 16) == 1 and memory.get(sp + 24) == 4,
        "request action/variant/four-word count differs",
    )
    pointer = memory.get(sp + 20)
    require(
        isinstance(pointer, tuple) and pointer[0] == "stack", "missing payload pointer"
    )
    offset = pointer[1]
    require(
        offset % 4 == 0 and offset >= 0 and not offset <= counter < offset + 16,
        "counter escapes through the payload",
    )
    payload = [memory.get(offset + n, "unknown") for n in (0, 4, 8, 12)]
    expected = [
        "current_parameter0",
        0.0,
        2.0,
        ("+", ("*", "sector", 45.0), "current_parameter0"),
    ]
    require(
        payload == expected
        and memory.get(sp + 4) == ("actor_float", 0xEC)
        and memory.get(sp + 8) == ("actor_float", 0xF0)
        and memory.get(sp + 12) == "unsigned_facing",
        "current-iteration request expressions differ",
    )
    return {
        "loop_head": hex(head),
        "request": hex(body[-1].address),
        "backedge": hex(guard[-1].address),
        "counter_offset": counter,
        "payload_offset": offset,
        "payload": payload,
        "initial": 0,
        "increment": 1,
        "exclusive_limit": 8,
        "conditional_iteration_count": 8,
    }


def audit(path):
    native.facts.audit()
    require(
        native.c.target_bytes(0x64CCFB, 3) == bytes.fromhex("c2 1c 00"),
        "actual spawn normal-return cleanup differs",
    )
    target_rows = native.facts.decode(native.c.target_bytes(0x497FEC, 0x101), 0x497FEC)
    candidate = native.export(path)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    source_rows = list(decoder.disasm(candidate, native.S))
    return {
        "target": loop_contract(target_rows, native.c.target_bytes),
        "source": loop_contract(source_rows, native.c.target_bytes),
        "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
        "scope": "caller expressions and eight iterations conditional on normal ABI returns preserving the unescaped counter; fresh actor/parameter reads each iteration; no returning-world execution or exact claim",
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    print(json.dumps(audit(args.object), indent=2))
