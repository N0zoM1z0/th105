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


def caller_buffer(rows, cleanup, initial_registers=None):
    """Track only observed stack/pointer/zero/one instructions; reject others."""
    if cleanup != 28:
        raise ValueError("spawn cleanup is not seven words")
    sp, registers, memory, floating, requests = (
        0,
        dict(initial_registers or {}),
        {},
        [],
        [],
    )

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


def preserved_to_window(rows, entry, stop, register):
    """Check every decoded normal-return path from this case to the window."""
    by_address = {row.address: row for row in rows}
    pending, edges = [entry], {}
    while pending:
        address = pending.pop()
        if address in edges:
            continue
        if address not in by_address:
            raise ValueError("source edge leaves decoded code")
        row = by_address[address]
        destinations = []
        if address != stop and not row.group(capstone.CS_GRP_RET):
            if row.group(capstone.CS_GRP_JUMP):
                if row.operands[0].type != x.X86_OP_IMM:
                    raise ValueError("unreviewed source indirect jump")
                destinations.append(row.operands[0].imm)
            if row.mnemonic != "jmp":
                destinations.append(address + row.size)
        edges[address] = destinations
        pending.extend(destinations)
    if stop not in edges:
        raise ValueError("808 window is unreachable from its source table entry")
    reverse = {}
    for address, destinations in edges.items():
        for destination in destinations:
            reverse.setdefault(destination, []).append(address)
    pending, reaches = [stop], set()
    while pending:
        address = pending.pop()
        if address in reaches:
            continue
        reaches.add(address)
        pending.extend(reverse.get(address, []))
    aliases = {register, x.X86_REG_BP} if register == x.X86_REG_EBP else {register}
    for address in reaches - {stop}:
        if aliases.intersection(by_address[address].regs_access()[1]):
            raise ValueError(
                "hoisted constant register is overwritten before the window"
            )
    return len(reaches)


def source_registers(rows, candidate, stop):
    """Recognize the reviewed VC8 primary dispatch's optional EBP constant."""
    dispatch_index = next(
        n
        for n, row in enumerate(rows)
        if row.mnemonic == "jmp" and row.operands[0].type == x.X86_OP_MEM
    )
    prefix = rows[dispatch_index - 7 : dispatch_index + 1]
    definition = rows[dispatch_index - 1]
    if not (
        definition.mnemonic == "mov"
        and definition.operands[0].reg == x.X86_REG_EBP
        and definition.operands[1].type == x.X86_OP_IMM
    ):
        return {}, None  # Earlier compiler phase passes immediate variant1.
    if [row.mnemonic for row in prefix] != [
        "movsx",
        "add",
        "cmp",
        "push",
        "ja",
        "movzx",
        "mov",
        "jmp",
    ]:
        raise ValueError("unreviewed hoisted-register dispatch")
    load, add, bound, _, guard, index, _, dispatch = prefix
    if not (
        load.operands[0].reg
        == add.operands[0].reg
        == bound.operands[0].reg
        == x.X86_REG_EAX
        and load.operands[1].type == x.X86_OP_MEM
        and load.operands[1].size == 2
        and load.operands[1].mem.base == x.X86_REG_ESI
        and not load.operands[1].mem.index
        and load.operands[1].mem.disp == 0x13C
        and add.operands[1].type == x.X86_OP_IMM
        and add.operands[1].imm & 0xFFFFFFFF == 0xFFFFFCE0
        and bound.operands[1].type == x.X86_OP_IMM
        and bound.operands[1].imm == 199
        and guard.operands[0].type == x.X86_OP_IMM
        and index.operands[0].reg == x.X86_REG_EAX
        and index.operands[1].type == x.X86_OP_MEM
        and index.operands[1].size == 1
        and index.operands[1].mem.base == x.X86_REG_EAX
        and not index.operands[1].mem.index
        and dispatch.operands[0].mem.index == x.X86_REG_EAX
        and not dispatch.operands[0].mem.base
        and dispatch.operands[0].mem.scale == 4
    ):
        raise ValueError("source808 dispatch data flow differs")

    def read(address, size):
        offset = address - native.S
        if not 0 <= offset <= offset + size <= len(candidate):
            raise ValueError("source table outside replay")
        return candidate[offset : offset + size]

    slot = read(index.operands[1].mem.disp + 8, 1)[0]
    entry = int.from_bytes(read(dispatch.operands[0].mem.disp + slot * 4, 4), "little")
    count = preserved_to_window(rows, entry, stop, x.X86_REG_EBP)
    value = definition.operands[1].imm
    return {x.X86_REG_EBP: value}, {
        "register": "ebp",
        "value": value,
        "definition": hex(definition.address),
        "case808_entry": hex(entry),
        "window_entry": hex(stop),
        "checked_instructions": count,
        "scope": "all decoded case-to-window paths; external calls preserve EBP on normal ABI returns",
    }


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
    registers, register_evidence = source_registers(
        rows, candidate, selected[0].address
    )
    source = caller_buffer(selected, cleanup, registers)
    expected = (True, [[0, 0, 0], [AFTER_CALL, AFTER_CALL, 0x3F800000]])
    if signature(target) != expected or signature(source) != expected:
        raise ValueError("caller buffer reuse or third-word assignment differs")
    return {
        "target": target,
        "source": source,
        "source_register_evidence": register_evidence,
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
