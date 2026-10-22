#!/usr/bin/env python3
"""Prove begin's MOV/PUSH endpoint under explicit data-storage disjointness.

Uses the actual configured linked body/caller witness. Install the optional
scripts/requirements-smt.txt dependency. This never grants canonical credit.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import capstone
import pefile
import z3

import linked_pe as linked
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE, LOW, HIGH, WINDOW = 0x4119A0, 291, 59, 69, 0x702A1C
OPERATIONS = {
    ("mov", "dword ptr [esi + 4], eax"),
    ("mov", "ecx, dword ptr [0x702a1c]"),
    ("push", "ecx"),
}


def read_word(memory, address):
    return z3.Concat(*[z3.Select(memory, address + index) for index in (3, 2, 1, 0)])


def write_word(memory, address, value):
    for index in range(4):
        memory = z3.Store(memory, address + index,
                          z3.Extract(index * 8 + 7, index * 8, value))
    return memory


def execute(rows, registers, memory):
    registers, order = dict(registers), []
    if (len(rows) != 3 or {(row.mnemonic, row.op_str) for row in rows} != OPERATIONS
            or sum(row.size for row in rows) != HIGH - LOW):
        raise ValueError("unreviewed begin instruction window")
    for row in rows:
        if row.mnemonic == "push":
            registers["esp"] = registers["esp"] - 4
            memory = write_word(memory, registers["esp"], registers["ecx"])
            order.append("outgoing_hwnd")
        elif row.op_str.startswith("ecx,"):
            memory_address = z3.BitVecVal(WINDOW, 32)
            registers["ecx"] = read_word(memory, memory_address)
        else:
            memory = write_word(memory, registers["esi"] + 4, registers["eax"])
            order.append("font_handle")
    return registers, memory, order


def prove(unit_name):
    comparator = linked.comparator()
    target_hash = comparator.verify_target()
    unit = load_manifest()["units"][unit_name]
    function = next(row for row in unit["functions"] if int(row["address"], 0) == ADDRESS)
    image = ROOT / unit["object"]
    paths = [image, image.with_suffix(".map"), image.with_suffix(".link.json"),
             image.with_suffix(".ltcg.obj"), image.with_suffix(".bindings.obj"),
             Path(__file__), ROOT / "resources/th105.exe",
             *[ROOT / "scripts" / name for name in (
                 "requirements-smt.txt", "linked_pe.py", "linked_lifecycle.py",
                 "linked_noreturn.py", "compare-function.py", "workflow_manifest.py", "match_literals.py")],
             *[ROOT / "config" / name for name in (
                 "target.toml", "functions.csv", "match-units.toml", "known-symbols.csv",
                 "known-globals.csv", "reccmp-relocations.csv")]]
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}
    before = pins()
    report, = linked.compare_linked(unit_name, unit, {function["address"]})
    pe = pefile.PE(str(image))
    functions = linked.parse_map(image.with_suffix(".map").read_text())
    start = int(report["linked_function_va"], 0)
    raw = linked.linked_body(pe, functions, start)
    imports = {entry.address: (dll.dll.decode("ascii").lower(), linked.import_identity(entry))
               for dll in pe.DIRECTORY_ENTRY_IMPORT for entry in dll.imports}
    targets = {symbol: int(address, 0) for symbol, address in
               (item.split("=", 1) for item in function["rel32_targets"])}
    game = pefile.PE(str(comparator.TARGET), fast_load=True)
    game_range = (game.OPTIONAL_HEADER.ImageBase,
                  game.OPTIONAL_HEADER.ImageBase + game.OPTIONAL_HEADER.SizeOfImage)
    resolve = lambda destination: linked.resolve_linked_call(
        destination, pe, functions, imports, targets, [])
    source, _, _ = linked.canonicalize(raw, start, ADDRESS, linked.target_bindings(unit), resolve,
                                     (linked.IMAGE_BASE, linked.IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage),
                                     game_range)
    target = comparator.target_bytes(ADDRESS, SIZE)
    if (len(source) != SIZE or target[:LOW] != source[:LOW]
            or target[HIGH:] != source[HIGH:]):
        raise ValueError("begin has a residual outside the reviewed ten-byte window")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = [list(decoder.disasm(code[LOW:HIGH], ADDRESS + LOW)) for code in (target, source)]
    registers = {name: z3.BitVec(name, 32) for name in
                 ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp")}
    memory = z3.Array("initial_data", z3.BitVecSort(32), z3.BitVecSort(8))
    states = [execute(rows, registers, memory) for rows in windows]
    changed = z3.Or(states[0][1] != states[1][1],
                    *[states[0][0][name] != states[1][0][name] for name in registers])
    font, argument = registers["esi"] + 4, registers["esp"] - 4
    disjoint = lambda left, right: z3.And(*[left + a != right + b
                                          for a in range(4) for b in range(4)])
    solver = z3.Solver()
    solver.set(timeout=20000)
    solver.add(disjoint(font, z3.BitVecVal(WINDOW, 32)), disjoint(font, argument), changed)
    if solver.check() != z3.unsat:
        raise ValueError("begin endpoint equivalence did not close")
    overlaps = {}
    for label, owner in (("window_cell", WINDOW - 4), ("outgoing_argument", 0x2100800 - 8)):
        solver = z3.Solver()
        solver.set(timeout=20000)
        solver.add(registers["esi"] == owner, registers["esp"] == 0x2100800,
                   registers["eax"] == 0x11111111,
                   read_word(memory, z3.BitVecVal(WINDOW, 32)) == 0x22222222, changed)
        if solver.check() != z3.sat:
            raise ValueError("begin overlap sensitivity control did not differ")
        model = solver.model()
        overlaps[label] = {side: model.eval(read_word(state[1], state[0]["esp"])).as_long()
                           for side, state in zip(("target_hwnd", "source_hwnd"), states)}
    if before != pins():
        raise ValueError("changed begin proof inputs")
    return dict(schema="th105-font-begin-window-proof-v1", result="proved_scoped_endpoint",
                canonical_result=report["result"], target_sha256=target_hash, input_pins=before,
                unit=unit_name, body_bytes=SIZE, target_body_sha256=hashlib.sha256(target).hexdigest(),
                source_body_sha256=hashlib.sha256(source).hexdigest(),
                differing_offsets=[index for index in range(SIZE) if target[index] != source[index]],
                window=dict(start=ADDRESS + LOW, exclusive_end=ADDRESS + HIGH,
                            instructions=[[dict(address=row.address, bytes=row.bytes.hex(),
                                                text=row.mnemonic + " " + row.op_str) for row in rows]
                                          for rows in windows]),
                ordered_write_roles=dict(target=states[0][2], source=states[1][2]),
                solver=dict(version=z3.get_version_string(), disjoint_mismatch="unsat",
                            overlap_mismatches="sat", examples=overlaps),
                build_provenance_verified=True, private_caller_witness=report["private_caller_witness"],
                preconditions="identical arbitrary32-bit entry registers/data; four font-handle bytes "
                              "at ESI+4 disjoint from HWND702A1C and from outgoing argument at ESP-4; "
                              "immutable instructions, valid accesses, no exception/asynchronous delivery",
                scope="isolated ten-byte MOV/PUSH windows: same endpoint GPR/data state; arithmetic "
                      "flags untouched; ordered writes/read traces differ. No CreateFont/GetDC "
                      "execution or supplied return, whole-begin/GDI/RET, arbitrary alias, original "
                      "type/TU/compiler provenance, or canonical equality claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--unit", default="gpt-web-text-font-color-linked")
    print(json.dumps(prove(parser.parse_args().unit), indent=2))
