#!/usr/bin/env python3
"""Execute Aya900 sequence4 to its original oriented-helper entry, without returns."""

from pathlib import Path
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import capstone
import pefile
import unicorn
from unicorn import x86_const as r

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import linked_pe as lp
from workflow_manifest import load_manifest

A, S, BASE, STACK, STOP, HELPER = (
    0x61A290,
    0x800000,
    0x2000000,
    0x3000000,
    0x900000,
    0x435160,
)
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument(
    "--output", type=Path, default=ROOT / "build/aya900-scale-prefix.json"
)
args = parser.parse_args()
c = lp.comparator()
target_sha = c.verify_target()
u = load_manifest()["units"]["gpt-web-aya-object-vslot28-full-root"]
f = u["functions"][0]
obj = ROOT / u["object"]
spec = importlib.util.spec_from_file_location(
    "aya_scale_coff", ROOT / "scripts/compare-giant-action-switches.py"
)
mapper = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = mapper
spec.loader.exec_module(mapper)
co = mapper.CoffObject(obj, symbol_base=f["symbol_base"])
code = c.coff_symbol_bytes(
    obj,
    f["symbol_base"],
    S,
    len(co.text),
    {a: int(b, 0) for a, b in (z.split("=", 1) for z in f["rel32_targets"])},
    c.known_data_targets(),
    dict(z.split("=", 1) for z in f.get("dir32_targets", [])),
)
image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()


class Probe:
    def __init__(self, candidate=False):
        self.start = S if candidate else A
        self.end = self.start + (len(code) if candidate else 19522)
        self.uc = uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc.mem_map(0x400000, 0x310000)
        uc.mem_write(0x400000, image)
        uc.mem_protect(0x400000, 0x310000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        if candidate:
            uc.mem_map(S, 0x10000)
            uc.mem_write(S, code)
            uc.mem_protect(S, 0x10000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        uc.mem_map(BASE, 0x10000)
        uc.mem_map(STACK, 0x10000)
        uc.hook_add(unicorn.UC_HOOK_CODE, self.step)
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def step(self, uc, pc, size, data):
        if pc == HELPER:
            self.stopped = True
            uc.emu_stop()
            return
        if not self.start <= pc < self.end:
            raise ValueError(f"unexpected code {pc:#x}")

    def write(self, uc, access, address, size, value, data):
        if BASE <= address < BASE + 0x10000:
            self.writes.append((address - BASE, size, value & ((1 << (size * 8)) - 1)))

    def run(self, case):
        scale, speed, phase, cw = case
        uc = self.uc
        uc.mem_write(BASE, bytes(0x10000))
        uc.mem_write(STACK, bytes(0x10000))

        def w(address, fmt, value):
            uc.mem_write(address, struct.pack("<" + fmt, value))

        w(BASE + 0x13C, "h", 900)
        w(BASE + 0x13E, "h", 4)
        w(BASE + 0x11C, "I", scale)
        w(BASE + 0x120, "I", 0xDEADBEEF)
        w(BASE + 0x340, "I", BASE + 0x8000)
        w(BASE + 0x8000, "f", phase)
        w(BASE + 0x8004, "I", speed)
        sp = STACK + 0xF000
        w(sp, "I", STOP)
        for reg in (
            r.UC_X86_REG_EAX,
            r.UC_X86_REG_EDX,
            r.UC_X86_REG_EBX,
            r.UC_X86_REG_ESI,
            r.UC_X86_REG_EDI,
            r.UC_X86_REG_EBP,
        ):
            uc.reg_write(reg, 0x11111111)
        uc.reg_write(r.UC_X86_REG_ECX, BASE)
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_EFLAGS, 2)
        uc.reg_write(r.UC_X86_REG_FPCW, cw)
        uc.reg_write(r.UC_X86_REG_FPSW, 0)
        uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
        self.writes = []
        self.stopped = False
        uc.emu_start(self.start, 0, count=1000)
        assert self.stopped and uc.reg_read(r.UC_X86_REG_EIP) == HELPER
        assert uc.reg_read(r.UC_X86_REG_ECX) == BASE + 4
        esp = uc.reg_read(r.UC_X86_REG_ESP)
        return dict(
            memory=hashlib.sha256(bytes(uc.mem_read(BASE, 0x10000))).hexdigest(),
            writes=self.writes,
            arguments=bytes(uc.mem_read(esp + 4, 8)).hex(),
            stack_depth=sp - esp,
            control=uc.reg_read(r.UC_X86_REG_FPCW),
            status=uc.reg_read(r.UC_X86_REG_FPSW),
            tag=uc.reg_read(r.UC_X86_REG_FPTAG),
        )


bits = (
    0,
    0x80000000,
    1,
    0x80000001,
    0x3F800000,
    0xBF800000,
    0x3F7FFFFF,
    0x40000000,
    0x7F800000,
    0xFF800000,
    0x7FC00123,
    0x7F800001,
)
cases = list(
    itertools.product(
        bits,
        bits,
        (-45.0, 0.0, 90.0),
        (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
    )
)
probes = [Probe(), Probe(True)]
differences = 0
samples = []
for case in cases:
    results = [p.run(case) for p in probes]
    if results[0] != results[1]:
        differences += 1
        if len(samples) < 4:
            samples.append(dict(case=case, results=results))
# Independently qualify the two action900 external-to-region exits.
cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
cs.detail = True
exits = []
for origin, payload, destination in (
    (0x61D83F, c.target_bytes(0x61D83F, 1773), 0x61BCF1),
    (S + 0x361B, code[0x361B : 0x361B + 1773], S + 0x277),
):
    rows = list(cs.disasm(payload, origin))
    assert len(rows) == 412 and sum(row.size for row in rows) == 1773
    edges = [
        row
        for row in rows
        if row.mnemonic in ("jne", "jle")
        and row.operands[0].type == capstone.x86_const.X86_OP_IMM
        and row.operands[0].imm == destination
    ]
    assert [row.mnemonic for row in edges] == ["jne", "jle"]
    exit_bytes = (
        c.target_bytes(destination, 17)
        if origin < S
        else code[destination - S : destination - S + 17]
    )
    assert exit_bytes == c.target_bytes(0x61BCF1, 17)
    exits.append(
        dict(
            entry=hex(destination),
            sites=[hex(row.address) for row in edges],
            bytes=17,
            sha256=hashlib.sha256(exit_bytes).hexdigest(),
        )
    )
report = dict(
    target_sha256=target_sha,
    object_sha256=lp.sha(obj),
    runtime_sha256=hashlib.sha256(code).hexdigest(),
    cases=len(cases),
    differences=differences,
    samples=samples,
    shared_exits=exits,
    scope="sequence4 complete root-entry prefix to original435160, stops before helper execution; no mocked return, no callback/full-root/exception equivalence; masked x87 matrix only",
    input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
)
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps(report, indent=2))
if differences:
    raise SystemExit(1)
