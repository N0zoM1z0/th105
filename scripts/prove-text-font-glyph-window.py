#!/usr/bin/env python3
"""Prove the glyph integer residual's endpoint state under a disjointness condition.

This is a bounded raw-instruction proof, not canonical or whole-runtime acceptance.
Install the optional scripts/requirements-smt.txt dependency before use.
"""
from __future__ import annotations

import argparse
from functools import reduce
import hashlib
import importlib.util
import json
from pathlib import Path
import sys

import capstone
import z3

import linked_pe
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE, START, END = 0x411B80, 624, 88, 106
X = capstone.x86


def read_word(memory, address):
    return z3.Concat(*[z3.Select(memory, address + index) for index in (3, 2, 1, 0)])


def arithmetic_flags(left, right, value, subtraction):
    high = lambda word: z3.Extract(31, 31, word) == 1
    overflow = ((left ^ right) & (left ^ value) if subtraction
                else (left ^ value) & (right ^ value))
    parity = z3.Not(reduce(z3.Xor, [z3.Extract(bit, bit, value) == 1 for bit in range(8)]))
    return dict(cf=z3.ULT(left, right) if subtraction else z3.ULT(value, left),
                pf=parity, af=z3.Extract(4, 4, left ^ right ^ value) == 1,
                zf=value == 0, sf=high(value), of=high(overflow))


def execute(rows, initial_registers, initial_memory):
    registers, memory, flags, writes = dict(initial_registers), initial_memory, None, []

    def address(operand):
        if operand.mem.index or operand.mem.base not in (X.X86_REG_ESI, X.X86_REG_ESP):
            raise ValueError("unreviewed symbolic memory operand")
        return registers[rows[0].reg_name(operand.mem.base)] + operand.mem.disp

    def read(operand):
        if operand.size != 4:
            raise ValueError("unreviewed symbolic operand width")
        if operand.type == X.X86_OP_REG:
            return registers[rows[0].reg_name(operand.reg)]
        if operand.type == X.X86_OP_MEM:
            return read_word(memory, address(operand))
        raise ValueError("unreviewed symbolic operand kind")

    for row in rows:
        if row.mnemonic not in ("mov", "sub", "add") or len(row.operands) != 2:
            raise ValueError("unreviewed symbolic instruction")
        destination, source = row.operands
        right = read(source)
        if row.mnemonic == "mov":
            value = right
        else:
            left = read(destination)
            subtraction = row.mnemonic == "sub"
            value = left - right if subtraction else left + right
            flags = arithmetic_flags(left, right, value, subtraction)
        if destination.type == X.X86_OP_REG:
            registers[row.reg_name(destination.reg)] = value
        elif destination.type == X.X86_OP_MEM and destination.size == 4:
            location = address(destination)
            writes.append((location, value))
            for index in range(4):
                memory = z3.Store(memory, location + index,
                                  z3.Extract(index * 8 + 7, index * 8, value))
        else:
            raise ValueError("unreviewed symbolic destination")
    if flags is None or len(writes) != 1:
        raise ValueError("unreviewed flag/write surface")
    return registers, memory, flags, writes


def prove(obj):
    comparator = linked_pe.comparator()
    target_hash = comparator.verify_target()
    unit = load_manifest()["units"]["gpt-web-text-font-render"]
    function = next(row for row in unit["functions"] if int(row["address"], 0) == ADDRESS)
    spec = importlib.util.spec_from_file_location(
        "glyph_proof_coff", ROOT / "scripts/compare-giant-action-switches.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    coff = module.CoffObject(obj, symbol_base=function["symbol_base"])
    targets = {key: int(value, 0) for key, value in
               (item.split("=", 1) for item in function["rel32_targets"])}
    paths = [obj, Path(__file__), ROOT / "resources/th105.exe",
             ROOT / "scripts/requirements-smt.txt", ROOT / "scripts/linked_pe.py",
             ROOT / "scripts/compare-function.py", ROOT / "scripts/compare-giant-action-switches.py",
             ROOT / "scripts/workflow_manifest.py", ROOT / "scripts/match_literals.py",
             *[ROOT / "config" / name for name in (
                 "target.toml", "match-units.toml", "known-symbols.csv", "known-globals.csv",
                 "reccmp-relocations.csv")]]
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}
    before = pins()
    source = comparator.coff_symbol_bytes(obj, function["symbol_base"], ADDRESS,
                                           len(coff.text), targets, comparator.known_data_targets())
    target = comparator.target_bytes(ADDRESS, SIZE)
    if (len(source) != SIZE or target[:START] != source[:START]
            or target[END:] != source[END:]):
        raise ValueError("candidate has a residual outside the reviewed window")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    windows = [list(decoder.disasm(code[START:END], ADDRESS + START)) for code in (target, source)]
    for rows in windows:
        if sum(row.size for row in rows) != END - START:
            raise ValueError("incomplete window decoding")
    registers = {name: z3.BitVec(name, 32) for name in
                 ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp")}
    memory = z3.Array("initial_memory", z3.BitVecSort(32), z3.BitVecSort(8))
    states = [execute(rows, registers, memory) for rows in windows]
    mismatches = [states[0][0][name] != states[1][0][name] for name in registers]
    mismatches += [states[0][1] != states[1][1]]
    mismatches += [states[0][2][name] != states[1][2][name] for name in states[0][2]]
    for lhs, rhs in zip(states[0][3], states[1][3]):
        mismatches += [lhs[0] != rhs[0], lhs[1] != rhs[1]]
    changed = z3.Or(*mismatches)
    ascent, temporary = registers["esi"] + 0x13C, registers["esp"] + 0x10
    disjoint = z3.And(*[ascent + left != temporary + right
                        for left in range(4) for right in range(4)])
    solver = z3.Solver()
    solver.set(timeout=20000)
    solver.add(disjoint, changed)
    answer = solver.check()
    if answer != z3.unsat:
        raise ValueError(f"endpoint proof did not close: {answer}")
    solver = z3.Solver()
    solver.set(timeout=20000)
    solver.add(registers["esi"] == 0x1000, registers["esp"] == 0x112C,
               registers["ecx"] == 1, registers["edx"] == 3,
               read_word(memory, ascent) == 16,
               read_word(memory, registers["esp"] + 0x30) == 0, changed)
    if solver.check() != z3.sat:
        raise ValueError("overlap sensitivity control did not produce a counterexample")
    model = solver.model()
    overlap = dict(target_edi=model.eval(states[0][0]["edi"]).as_long(),
                   source_edi=model.eval(states[1][0]["edi"]).as_long())
    if before != pins():
        raise ValueError("changed glyph proof inputs")
    return dict(schema="th105-font-glyph-window-proof-v1", result="proved_scoped_endpoint",
                target_sha256=target_hash, input_pins=before, object=str(obj),
                target_body_sha256=hashlib.sha256(target).hexdigest(),
                source_body_sha256=hashlib.sha256(source).hexdigest(), size=SIZE,
                differing_offsets=[offset for offset in range(SIZE) if target[offset] != source[offset]],
                window=dict(start=ADDRESS + START, exclusive_end=ADDRESS + END,
                            instructions=[[dict(address=row.address, bytes=row.bytes.hex(),
                                                text=row.mnemonic + " " + row.op_str)
                                           for row in rows] for rows in windows]),
                solver=dict(version=z3.get_version_string(), disjoint_mismatch="unsat",
                            overlapping_mismatch="sat", overlap_control=overlap),
                preconditions="identical arbitrary32-bit entry registers/data memory; immutable "
                              "instruction bytes; four ascent "
                              "bytes at ESI+13C disjoint from four temporary bytes at ESP+10; "
                              "all accesses readable/writable as needed, no asynchronous observers",
                scope="18-byte straight-line MOV/SUB/ADD windows: same endpoint registers, byte "
                      "memory, six arithmetic flags and one ordered write; differing intermediate "
                      "states/read order are retained; no fault behavior, root/GDI/runtime or "
                      "arbitrary-alias equivalence, build provenance or canonical acceptance claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    print(json.dumps(prove(parser.parse_args().object), indent=2))
