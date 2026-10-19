#!/usr/bin/env python3
"""Recover the808 caller's shared stack buffer, without returning a world call.

This is a restricted straight-line stack analysis. The real RET1C supplies the
normal-return stack effect. A call invalidates every passed payload word: the
second request's first two values are not proved by caller instructions alone.
"""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object808_native", ROOT / "scripts/audit-reimu-object-scalar-actions.py"
)
native = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(native)
UNKNOWN = "unknown"
AFTER_CALL = "unknown_after_call"


def stack_address(op, sp):
    if op.type == x.X86_OP_MEM and op.mem.base == x.X86_REG_ESP and not op.mem.index:
        return sp + op.mem.disp
    raise ValueError("unreviewed stack address")


def caller_buffer(rows, cleanup):
    """Track only observed stack/pointer/zero/one instructions; reject others."""
    if cleanup != 28:
        raise ValueError("spawn cleanup is not seven words")
    sp, registers, memory, floating, requests = 0, {}, {}, [], []

    def value(op):
        if op.type == x.X86_OP_IMM:
            return op.imm
        if op.type == x.X86_OP_REG:
            return registers.get(op.reg, UNKNOWN)
        return UNKNOWN

    for row in rows:
        ops = row.operands
        if row.mnemonic == "push":
            if ops[0].size != 4:
                raise ValueError("non-dword push")
            sp -= 4
            memory[sp] = value(ops[0])
        elif row.mnemonic == "sub" and ops[0].reg == x.X86_REG_ESP:
            if ops[1].type != x.X86_OP_IMM or ops[1].imm != 8:
                raise ValueError("unreviewed stack allocation")
            sp -= 8
        elif row.mnemonic == "lea":
            if ops[0].size != 4 or ops[0].reg == x.X86_REG_ESP:
                raise ValueError("unreviewed pointer register")
            registers[ops[0].reg] = ("stack", stack_address(ops[1], sp))
        elif row.mnemonic in ("mov", "movzx"):
            if (
                ops[0].type != x.X86_OP_REG
                or ops[0].size != 4
                or ops[0].reg == x.X86_REG_ESP
            ):
                raise ValueError("unreviewed register assignment")
            registers[ops[0].reg] = value(ops[1])
        elif row.mnemonic in ("fldz", "fld1", "fld"):
            if row.mnemonic == "fldz":
                v = 0
            elif row.mnemonic == "fld1":
                v = 0x3F800000
            elif ops[0].type == x.X86_OP_MEM and ops[0].mem.base == x.X86_REG_ESP:
                v = (
                    memory.get(stack_address(ops[0], sp), UNKNOWN)
                    if ops[0].size == 4
                    else UNKNOWN
                )
            else:
                v = UNKNOWN
            floating.append(v)
        elif row.mnemonic == "fadd":
            if not floating or ops[0].type != x.X86_OP_MEM:
                raise ValueError("unreviewed floating add")
            floating[-1] = UNKNOWN
        elif row.mnemonic in ("fst", "fstp"):
            if not floating or ops[0].size != 4:
                raise ValueError("missing float value or non-dword store")
            memory[stack_address(ops[0], sp)] = floating[-1]
            if row.mnemonic == "fstp":
                floating.pop()
        elif row.mnemonic == "call":
            if ops[0].type != x.X86_OP_IMM or ops[0].imm != native.SPAWN:
                raise ValueError("unreviewed call")
            pointer = memory.get(sp + 20)
            if (
                memory.get(sp) != 808
                or memory.get(sp + 16) != 1
                or memory.get(sp + 24) != 3
                or not isinstance(pointer, tuple)
                or pointer[0] != "stack"
                or floating
            ):
                raise ValueError("unreviewed808 argument protocol")
            offset = pointer[1]
            requests.append(
                {
                    "call": hex(row.address),
                    "pointer_offset": offset,
                    "payload": [memory.get(offset + n, UNKNOWN) for n in (0, 4, 8)],
                }
            )
            # The world call receives this pointer. Preserve neither payload
            # contents nor volatile registers across its conditional return.
            for n in (0, 4, 8):
                memory[offset + n] = AFTER_CALL
            for reg in (x.X86_REG_EAX, x.X86_REG_ECX, x.X86_REG_EDX):
                registers[reg] = UNKNOWN
            sp += cleanup
        else:
            raise ValueError(f"unreviewed instruction {row.mnemonic}")
    if len(requests) != 2 or sp != 0 or floating:
        raise ValueError("incomplete two-call stack protocol")
    return {
        "requests": requests,
        "same_pointer": requests[0]["pointer_offset"] == requests[1]["pointer_offset"],
        "stack_restored_on_normal_returns": True,
    }


def signature(packet):
    return (packet["same_pointer"], [r["payload"] for r in packet["requests"]])


def audit(path):
    native.facts.audit()
    target_rows = native.facts.decode(native.c.target_bytes(0x497225, 0xA8), 0x497225)
    ret = native.facts.decode(native.c.target_bytes(0x64CCFB, 3), 0x64CCFB)[0]
    if ret.mnemonic != "ret" or ret.operands[0].type != x.X86_OP_IMM:
        raise ValueError("real spawn return encoding differs")
    cleanup = ret.operands[0].imm
    candidate = native.export(path)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(candidate, native.S))
    calls = [
        n
        for n, row in enumerate(rows)
        if row.mnemonic == "call"
        and row.operands[0].type == x.X86_OP_IMM
        and row.operands[0].imm == native.SPAWN
        and any(
            prev.mnemonic == "push"
            and prev.operands[0].type == x.X86_OP_IMM
            and prev.operands[0].imm == 808
            for prev in rows[max(0, n - 3) : n]
        )
    ]
    if len(calls) != 2:
        raise ValueError("expected exactly two source808 requests")
    first, last = calls
    starts = [n for n in range(max(0, first - 30), first) if rows[n].mnemonic == "fldz"]
    if not starts:
        raise ValueError("missing source buffer zero initialization")
    selected = rows[starts[-1] : last + 1]
    target = caller_buffer(target_rows, cleanup)
    source = caller_buffer(selected, cleanup)
    expected = (True, [[0, 0, 0], [AFTER_CALL, AFTER_CALL, 0x3F800000]])
    if signature(target) != expected or signature(source) != expected:
        raise ValueError("caller buffer reuse or third-word assignment differs")
    return {
        "target": target,
        "source": source,
        "callee_ret": hex(ret.address),
        "cleanup": cleanup,
        "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
        "target_window_sha256": hashlib.sha256(
            native.c.target_bytes(0x497225, 0xA8)
        ).hexdigest(),
        "scope": "caller-only stack relationships conditional on normal ABI returns; payload invalidated across calls; no returning-world execution or exact claim",
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    print(json.dumps(audit(args.object), indent=2))
