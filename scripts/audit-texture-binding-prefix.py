#!/usr/bin/env python3
"""Compare native texture-binding paths to RET, lookup entry, COM call or fault.

No lookup/COM result is substituted and no device code executes. Read ordering
and real null-device faults distinguish lookup hoisting from the target. These
finite fixtures do not establish complete driver/lookup behavior or exactness.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
import pefile
import unicorn
from unicorn import x86_const as reg

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("texture_compare", ROOT / "scripts/compare-function.py")
compare = importlib.util.module_from_spec(spec)
spec.loader.exec_module(compare)
ADDRESS, SIZE, SOURCE = 0x404DF0, 107, 0x800000
LOOKUP, DEVICE_GLOBAL = 0x417800, 0x7036C0
OWNER, DEVICE, TABLE, METHOD = 0x2000000, 0x2200000, 0x2201000, 0xFEED000
STACK, STACK_SIZE, RETURN = 0x1000000, 0x10000, 0xF000000


def export(obj):
    function = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"][
        "gpt-web-texture-slot-binding"]["functions"][0]
    targets = compare.known_targets()
    targets.update({name: int(value, 0) for name, value in
                    (entry.split("=", 1) for entry in function["rel32_targets"])})
    data = dict(entry.split("=", 1) for entry in function["dir32_targets"])
    return compare.coff_symbol_bytes(obj, function["symbol_base"], SOURCE, SIZE,
                                     targets, compare.known_data_targets(), data)


def decode(code, base):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(code, base))
    if sum(row.size for row in rows) != len(code):
        raise ValueError("incomplete binder decoding")
    by, edges = {row.address: row for row in rows}, {}
    for row in rows:
        destinations = []
        if row.group(capstone.CS_GRP_RET):
            if len(row.operands) != 1 or row.operands[0].imm != 8:
                raise ValueError("binder return purge differs")
        else:
            if row.group(capstone.CS_GRP_JUMP):
                if row.operands[0].type != capstone.x86.X86_OP_IMM:
                    raise ValueError("unreviewed indirect binder jump")
                destinations.append(row.operands[0].imm)
            if row.mnemonic != "jmp":
                destinations.append(row.address + row.size)
        if any(destination not in by for destination in destinations):
            raise ValueError("binder edge leaves reviewed body")
        edges[row.address] = destinations
    pending, seen = [base], set()
    while pending:
        pc = pending.pop()
        if pc not in seen:
            seen.add(pc)
            pending.extend(edges[pc])
    if len(seen) != len(rows):
        raise ValueError("binder has unreachable bytes")
    return by


def cases():
    for stage in range(8):
        for handle in (0, 1, 0x10002, 0xFFFFFFFF):
            for cached in sorted({0, handle, handle ^ 0xFFFFFFFF}):
                for device in (0, DEVICE):
                    yield dict(stage=stage, handle=handle, cached=cached, device=device)


class Probe:
    def __init__(self, mapped, code=None):
        self.code = compare.target_bytes(ADDRESS, SIZE) if code is None else code
        self.base = ADDRESS if code is None else SOURCE
        self.rows = decode(self.code, self.base)
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.uc.mem_write(0x400000, mapped)
        if code is not None:
            self.uc.mem_map(SOURCE, (len(code) + 0xFFF) & ~0xFFF,
                            unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            self.uc.mem_write(SOURCE, code)
        self.uc.mem_map(OWNER, 0x1000)
        self.uc.mem_map(DEVICE, 0x2000, unicorn.UC_PROT_READ)
        self.uc.mem_write(DEVICE, struct.pack("<I", TABLE))
        self.uc.mem_write(TABLE + 0x104, struct.pack("<I", METHOD))
        self.uc.mem_map(STACK, STACK_SIZE)
        self.uc.mem_map(RETURN, 0x1000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.initial = self.uc.context_save()
        self.visits = Counter()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.step)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_READ, self.read)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_READ_UNMAPPED, self.fault)

    def step(self, uc, address, size, unused):
        if address == LOOKUP:
            sp = uc.reg_read(reg.UC_X86_REG_ESP)
            self.endpoint = dict(kind="lookup_entry", receiver=uc.reg_read(reg.UC_X86_REG_ECX),
                                 handle=struct.unpack("<I", uc.mem_read(sp + 4, 4))[0])
            uc.emu_stop()
            return
        row = self.rows.get(address)
        if row is None or row.size != size or bytes(uc.mem_read(address, size)) != row.bytes:
            raise ValueError("native binder instruction differs from immutable input")
        self.visits[address - self.base] += 1
        if row.group(capstone.CS_GRP_CALL) and row.operands[0].type != capstone.x86.X86_OP_IMM:
            operand = row.operands[0]
            if operand.type != capstone.x86.X86_OP_REG:
                raise ValueError("unreviewed device-call operand")
            registers = {"eax": reg.UC_X86_REG_EAX, "ecx": reg.UC_X86_REG_ECX,
                         "edx": reg.UC_X86_REG_EDX, "ebx": reg.UC_X86_REG_EBX,
                         "esi": reg.UC_X86_REG_ESI, "edi": reg.UC_X86_REG_EDI,
                         "ebp": reg.UC_X86_REG_EBP}
            target = uc.reg_read(registers[row.reg_name(operand.reg)])
            sp = uc.reg_read(reg.UC_X86_REG_ESP)
            self.endpoint = dict(kind="device_call", target=target,
                                 arguments=list(struct.unpack("<III", uc.mem_read(sp, 12))))
            uc.emu_stop()

    def read(self, uc, access, address, size, value, unused):
        tag = None
        if OWNER <= address and address + size <= OWNER + 0x84:
            tag = ("manager", address - OWNER)
        elif address == DEVICE_GLOBAL:
            tag = ("device_global", 0)
        elif address == DEVICE:
            tag = ("device_vptr", 0)
        elif address == TABLE + 0x104:
            tag = ("device_method", 0)
        if tag:
            self.reads.append((tag, size, bytes(uc.mem_read(address, size)).hex()))

    def write(self, uc, access, address, size, value, unused):
        if OWNER <= address and address + size <= OWNER + 0x84:
            self.writes.append((address - OWNER, size, value & ((1 << (8 * size)) - 1)))
        elif not STACK <= address < address + size <= STACK + STACK_SIZE:
            raise ValueError("native binder write leaves object/stack")

    def fault(self, uc, access, address, size, value, unused):
        if address != 0 or size != 4:
            raise ValueError("unreviewed native read fault")
        self.endpoint = dict(kind="null_device_read_fault", address=address, size=size)
        uc.emu_stop()
        return False

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes((i * 37 + 11) & 255 for i in range(0x84)))
        uc.mem_write(OWNER + 0x64 + case["stage"] * 4, struct.pack("<I", case["cached"]))
        uc.mem_write(DEVICE_GLOBAL, struct.pack("<I", case["device"]))
        uc.mem_write(STACK + STACK_SIZE - 0x1000, b"\xCD" * 0x1000)
        sp = STACK + STACK_SIZE - 0x100
        uc.mem_write(sp, struct.pack("<III", RETURN, case["handle"], case["stage"]))
        uc.reg_write(reg.UC_X86_REG_ESP, sp)
        uc.reg_write(reg.UC_X86_REG_ECX, OWNER)
        saved = {reg.UC_X86_REG_EBX: 0x11223344, reg.UC_X86_REG_EBP: 0x55667788,
                 reg.UC_X86_REG_ESI: 0x99AABBCC, reg.UC_X86_REG_EDI: 0xDDEEFF00}
        for register, value in saved.items():
            uc.reg_write(register, value)
        self.reads, self.writes, self.endpoint = [], [], None
        try:
            uc.emu_start(self.base, RETURN, count=1000)
        except unicorn.UcError:
            if self.endpoint is None or self.endpoint["kind"] != "null_device_read_fault":
                raise
        if self.endpoint is None:
            if (uc.reg_read(reg.UC_X86_REG_EIP) != RETURN
                    or uc.reg_read(reg.UC_X86_REG_ESP) != sp + 12
                    or any(uc.reg_read(register) != value for register, value in saved.items())):
                raise ValueError("binder RET8/nonvolatile contract failed")
            self.endpoint = dict(kind="ret")
        return dict(endpoint=self.endpoint, reads=self.reads, writes=self.writes,
                    object=bytes(uc.mem_read(OWNER, 0x84)).hex())


def audit(obj):
    paths = [Path(__file__), obj, ROOT / "src/assets/TextureStageBinding.cpp",
             ROOT / "resources/th105.exe", ROOT / "config/target.toml",
             ROOT / "config/match-units.toml", ROOT / "config/known-symbols.csv",
             ROOT / "config/reccmp-relocations.csv", ROOT / "scripts/compare-function.py",
             ROOT / "scripts/match_literals.py"]
    pins = lambda: {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}
    before = pins()
    compare.verify_target()
    target_code = compare.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target_code).hexdigest() != "c507bdb541478a700181ff1d1bfd3637cbc78261eed2de6390ec68fa1fb239fc":
        raise ValueError("binder target body changed")
    if compare.target_bytes(ADDRESS + SIZE, 5) != b"\xCC" * 5:
        raise ValueError("binder alignment boundary changed")
    mapped = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    target, source = Probe(mapped), Probe(mapped, export(obj))
    inputs, endpoints, source_endpoints, differences, examples = list(cases()), Counter(), Counter(), 0, []
    for case in inputs:
        a, b = target.evaluate(case), source.evaluate(case)
        endpoints[a["endpoint"]["kind"]] += 1
        source_endpoints[b["endpoint"]["kind"]] += 1
        if a != b:
            differences += 1
            if len(examples) < 8:
                examples.append(dict(case=case, target=a, source=b))
    if before != pins():
        raise ValueError("native audit inputs changed")
    return dict(result="equal_scoped_prefixes" if differences == 0 else "different_scoped_prefixes",
                case_count=len(inputs), difference_count=differences, examples=examples,
                input_sha256=hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest(),
                endpoints=dict(endpoints), source_endpoints=dict(source_endpoints),
                target_instructions=len(target.rows), source_instructions=len(source.rows),
                target_visited_offsets=sorted(target.visits), source_visited_offsets=sorted(source.visits),
                input_pins=before, pins_unchanged=True, build_provenance_verified=False,
                limitations=["Finite distinct manager/device/stack fixtures; stages0..7 only.",
                             "No helper result substitution; lookup entry/COM call are stops.",
                             "Post-call cache writes, lookup/driver continuations and whole-root exactness unproved."])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    report = audit(args.object)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({key: report[key] for key in ("result", "case_count", "difference_count", "endpoints")}))
    return int(report["difference_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
