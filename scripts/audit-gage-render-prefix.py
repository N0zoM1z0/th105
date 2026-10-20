#!/usr/bin/env python3
"""Replay CGage rendering through real helpers to RET or texture-bind entry.

The actual TGageValue providers, quantized lookup helpers and CRT instructions
execute unchanged. Texture binding is an opaque entry stop. This finite audit
does not execute graphics COM methods or establish canonical root equality,
original source spelling, arbitrary aliases or unmasked exception behavior.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
import pefile
import unicorn
from unicorn import x86_const as r

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


compare = load("gage_compare", "scripts/compare-function.py")
math = load("gage_math", "scripts/iku_native_math.py")
ADDRESS, SIZE, SOURCE = 0x41B3F0, 1010, 0x800000
OWNER, GETTER, VALUE = 0x2000000, 0x2001000, 0x2002000
STACK, STACK_SIZE, RETURN = 0x1000000, 0x10000, 0xF000000
BIND = 0x404DF0
HELPERS = {
    0x46FA50: (20, "int_value"), 0x46FA70: (27, "short_value"),
    0x406360: (100, "sine"), 0x4063D0: (94, "cosine"),
    0x68A1A0: (171, "ftol2_sse_member"),
    0x68BAAE: (182, "fabs"), 0x696387: (39, "control_word"),
}


def export(obj, address=SOURCE):
    unit = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"][
        "gpt-web-gage-render"
    ]["functions"][0]
    targets = compare.known_targets()
    for entry in unit["rel32_targets"]:
        name, destination = entry.split("=", 1)
        targets[name] = int(destination, 0)
    data = dict(entry.split("=", 1) for entry in unit["dir32_targets"])
    return compare.coff_symbol_bytes(
        obj, unit["symbol_base"], address, SIZE, targets,
        compare.known_data_targets(), data,
    )


def target_packet(mapped):
    code = mapped[ADDRESS - 0x400000:ADDRESS - 0x400000 + SIZE]
    if hashlib.sha256(code).hexdigest() != "67b9378f09e92621dad4bba0410f9aa4905bf24a8a73dd3e4440489bf860eedb":
        raise ValueError("target render body differs")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(code, ADDRESS))
    if sum(row.size for row in rows) != SIZE or len(rows) != 323:
        raise ValueError("target render decoding is incomplete")
    by, edges, returns = {row.address: row for row in rows}, {}, []
    for row in rows:
        destinations = []
        if row.group(capstone.CS_GRP_RET):
            if len(row.operands) != 1 or row.operands[0].imm != 8:
                raise ValueError("target render return purge differs")
            returns.append(row.address)
        else:
            if row.group(capstone.CS_GRP_JUMP):
                if row.operands[0].type != capstone.x86.X86_OP_IMM:
                    raise ValueError("unreviewed indirect target jump")
                destinations.append(row.operands[0].imm)
            if row.mnemonic != "jmp":
                destinations.append(row.address + row.size)
        if any(destination not in by for destination in destinations):
            raise ValueError("target render edge leaves reviewed instructions")
        edges[row.address] = destinations
    pending, seen = [ADDRESS], set()
    while pending:
        pc = pending.pop()
        if pc not in seen:
            seen.add(pc)
            pending.extend(edges[pc])
    if len(seen) != 323 or len(returns) != 2:
        raise ValueError("target render closure differs")
    if (mapped[0x6D6A54 - 0x400000:0x6D6A58 - 0x400000] != struct.pack("<I", ADDRESS)
            or mapped[ADDRESS - 0x400000 + SIZE:ADDRESS - 0x400000 + SIZE + 14] != b"\xCC" * 14):
        raise ValueError("target vslot/alignment evidence differs")
    return dict(size=SIZE, instructions=323, reachable=323, returns=returns,
                body_sha256=hashlib.sha256(code).hexdigest(), vslot=0x6D6A54)


def word(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


def cases():
    fractions = (
        0xBF800000, 0x80000000, 0, 1, 0x3EAAAAAB, 0x3F000000,
        0x3F7FFFFF, 0x3F800000, 0x3F800001, 0x40000000,
        0x7F800000, 0xFF800000, 0x7FC12345, 0x7F812345,
    )
    geometry = (
        (word(93.75), word(-1.125)),
        (word(0.3333333432674408), word(1.0000001192092896)),
        (0x7FC12345, 0x7FC54321),
        (1, word(2.0)),
    )
    for kind, value, mode, angle, cw, (height, scale) in itertools.product(
        ("int", "short"), fractions, (-1, 0, 1, 2, 7),
        (0.0, 37.25, -90.0, 359.95), (0x27F, 0x37F), geometry,
    ):
        yield dict(kind=kind, fraction_input_word=value, mode=mode, angle=angle,
                   cw=cw, height_word=height, scale_y_word=scale, null_value=False)
    for mode, cw in itertools.product((-1, 0, 1, 2, 7), (0x27F, 0x37F)):
        yield dict(kind="int", fraction_input_word=0, mode=mode, angle=37.25,
                   cw=cw, height_word=word(93.75), scale_y_word=word(-1.125),
                   null_value=True)


class Probe:
    def __init__(self, mapped, code=None):
        self.image, self.code = mapped, code
        self.start = ADDRESS if code is None else SOURCE
        self.size = SIZE if code is None else len(code)
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.uc.mem_write(0x400000, mapped)
        if code is not None:
            self.uc.mem_map(SOURCE, (len(code) + 0xFFF) & ~0xFFF,
                            unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            self.uc.mem_write(SOURCE, code)
        self.uc.mem_map(OWNER, 0x1000)
        self.uc.mem_map(GETTER, 0x1000, unicorn.UC_PROT_READ)
        self.uc.mem_map(VALUE, 0x1000, unicorn.UC_PROT_READ)
        self.uc.mem_map(STACK, STACK_SIZE)
        self.uc.mem_map(RETURN, 0x1000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.initial = self.uc.context_save()
        self.trace = {}
        self.visits = Counter()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.step)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def step(self, uc, address, size, unused):
        if address == BIND:
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            self.endpoint = dict(kind="bind_entry", receiver=uc.reg_read(r.UC_X86_REG_ECX),
                                 arguments=list(struct.unpack("<II", uc.mem_read(sp + 4, 8))))
            if self.endpoint["receiver"] != 0x702798:
                raise ValueError("texture-bind receiver is outside the reviewed view")
            uc.emu_stop()
            return
        if self.start <= address and address + size <= self.start + self.size:
            offset = address - self.start
            expected = (self.image[ADDRESS - 0x400000 + offset:
                                   ADDRESS - 0x400000 + offset + size]
                        if self.code is None else self.code[offset:offset + size])
            self.visits[offset] += 1
        elif any(lo <= address and address + size <= lo + length
                 for lo, (length, _) in HELPERS.items()):
            expected = self.image[address - 0x400000:address - 0x400000 + size]
        else:
            raise ValueError(f"unreviewed native instruction {address:#x}")
        raw = bytes(uc.mem_read(address, size))
        if raw != expected:
            raise ValueError("executed instruction differs from the immutable input")
        if address not in self.trace:
            rows = list(capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(raw, address))
            if len(rows) != 1 or rows[0].size != size:
                raise ValueError("native instruction does not decode completely")
            self.trace[address] = raw.hex()
        elif self.trace[address] != raw.hex():
            raise ValueError("native instruction boundary changed")
        if address in (0x46FA50, 0x46FA70):
            if uc.reg_read(r.UC_X86_REG_ECX) != GETTER:
                raise ValueError("getter receiver differs")
            self.calls.append((HELPERS[address][1],))
        elif address in (0x406360, 0x4063D0):
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            self.calls.append((HELPERS[address][1], bytes(uc.mem_read(sp + 4, 4)).hex()))

    def write(self, uc, access, address, size, value, unused):
        if OWNER <= address and address + size <= OWNER + 0xA4:
            self.events.append((address - OWNER, size, value & ((1 << (8 * size)) - 1)))
        elif not STACK <= address < address + size <= STACK + STACK_SIZE:
            raise ValueError(f"native write leaves object/stack at {address:#x}")

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes((i * 37 + 11) & 255 for i in range(0xA4)))
        uc.mem_write(STACK + STACK_SIZE - 0x2200, bytes([0xCD]) * 0x2200)
        for index, (x, y, u, v) in enumerate((
            (-31.25, 17.75, 0.125, 0.25), (42.5, 17.75, 0.875, 0.25),
            (-31.25, 82.125, 0.125, 0.95), (42.5, 82.125, 0.875, 0.95),
        )):
            uc.mem_write(OWNER + 8 + 28 * index,
                         struct.pack("<ffffIff", x, y, 0.25, 1.0, 0xA0B0C000 + index, u, v))
        for offset, value in (
            (0, 0x6D6A38), (4, 0xF1230001 if case["mode"] & 1 else 0),
            (0x78, word(137.25)), (0x7C, case["height_word"]),
            (0x80, word(4.125)), (0x84, word(-3.5)), (0x88, word(0.875)),
            (0x8C, case["scale_y_word"]), (0x90, word(case["angle"])),
            (0x94, word(0.75)), (0x98, word(0.7)),
            (0x9C, case["mode"] & 0xFFFFFFFF),
            (0xA0, 0 if case["null_value"] else GETTER),
        ):
            uc.mem_write(OWNER + offset, struct.pack("<I", value))
        desired = case["fraction_input_word"]
        start, span = ((0, word(-1.0)) if desired == 0x80000000
                       else (desired ^ 0x80000000, word(1.0)))
        uc.mem_write(GETTER, struct.pack("<IIII",
                     0x6C3890 if case["kind"] == "int" else 0x6C3898,
                     VALUE, start, span))
        uc.mem_write(VALUE, bytes(4))
        saved = {r.UC_X86_REG_EBX: 0x11223344, r.UC_X86_REG_ESI: 0x55667788,
                 r.UC_X86_REG_EDI: 0x99AABBCC, r.UC_X86_REG_EBP: 0xDEADBEEF}
        for register, value in saved.items():
            uc.reg_write(register, value)
        sp = STACK + STACK_SIZE - 0x100
        uc.mem_write(sp, struct.pack("<Iff", RETURN, 101.25, -51.5))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["cw"])
        uc.reg_write(r.UC_X86_REG_FPSW, 0)
        uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
        self.events, self.calls, self.endpoint = [], [], None
        uc.emu_start(self.start, RETURN, count=50000)
        if self.endpoint is None:
            if (uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                    or uc.reg_read(r.UC_X86_REG_ESP) != sp + 12
                    or any(uc.reg_read(register) != value for register, value in saved.items())):
                raise ValueError("native RET8/nonvolatile contract failed")
            self.endpoint = dict(kind="ret")
        if (uc.reg_read(r.UC_X86_REG_FPTAG) != 0xFFFF
                or uc.reg_read(r.UC_X86_REG_FPSW) & 0x3800
                or uc.reg_read(r.UC_X86_REG_FPCW) != case["cw"]):
            raise ValueError("native x87 stack/control word differs")
        return dict(object=bytes(uc.mem_read(OWNER, 0xA4)).hex(), events=self.events,
                    calls=self.calls, endpoint=self.endpoint,
                    status=uc.reg_read(r.UC_X86_REG_FPSW))


def audit(obj):
    paths = [Path(__file__), obj, ROOT / "src/ui/GageRender.cpp",
             ROOT / "resources/th105.exe", ROOT / "config/match-units.toml",
             ROOT / "config/target.toml", ROOT / "config/known-symbols.csv",
             ROOT / "config/reccmp-relocations.csv",
             ROOT / "scripts/compare-function.py", ROOT / "scripts/match_literals.py",
             ROOT / "scripts/iku_native_math.py"]
    pins = lambda: {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    before = pins()
    compare.verify_target()
    code = export(obj)
    mapped = bytearray(pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
    packet = target_packet(mapped)
    canonical = export(obj, ADDRESS)
    expected = mapped[ADDRESS - 0x400000:ADDRESS - 0x400000 + SIZE]
    canonical_diagnostic = dict(
        evidence="diagnostic_only_not_acceptance", source_extent=len(canonical),
        source_sha256=hashlib.sha256(canonical).hexdigest(),
        first_mismatch=compare.first_mismatch(expected, canonical, ADDRESS),
    )
    table, receipt = math.lookup_fixture(compare)
    mapped[0x2FE8B0:0x2FE8B0 + len(table)] = table
    target, source = Probe(bytes(mapped)), Probe(bytes(mapped), code)
    inputs = list(cases())
    count, examples, endpoints = 0, [], Counter()
    for case in inputs:
        a, b = target.evaluate(case), source.evaluate(case)
        endpoints[a["endpoint"]["kind"]] += 1
        if a != b:
            count += 1
            if len(examples) < 10:
                examples.append(dict(case=case, target=a, source=b))
    if before != pins():
        raise ValueError("audit inputs changed during execution")
    return dict(result="equal_scoped_prefixes" if count == 0 else "different_scoped_prefixes",
                case_count=len(inputs), difference_count=count, examples=examples,
                input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
                endpoints=dict(endpoints), target_visited_offsets=sorted(target.visits),
                source_visited_offsets=sorted(source.visits),
                target_instruction_trace=target.trace, source_instruction_trace=source.trace,
                lookup_fixture=receipt, input_pins=before, pins_unchanged=True,
                target_packet=packet, canonical_diagnostic=canonical_diagnostic,
                build_provenance_verified=False,
                limitations=["Finite distinct object/getter/stack fixtures; no arbitrary aliases.",
                             "Original getters/math execute; texture bind stops at actual entry.",
                             "No COM calls, unmasked exception delivery, or whole-root exact claim."])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    report = audit(args.object)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in ("result", "case_count", "difference_count", "endpoints")}))
    return int(report["difference_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
