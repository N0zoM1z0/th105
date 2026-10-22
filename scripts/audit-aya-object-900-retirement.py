#!/usr/bin/env python3
"""Finite Aya action900 retirement audit; full entry/RET, no fabricated callees."""

from pathlib import Path
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import pefile
import unicorn
from unicorn import x86_const as r

R = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(R / "scripts"))
import linked_pe as lp
from workflow_manifest import load_manifest

A = 0x61A290
S = 0x800000
BASE = 0x2000000
STACK = 0x3000000
STOP = 0x900000
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--previous-object", type=Path)
parser.add_argument("--output", type=Path, default=R / "build/aya-900-retirement.json")
args = parser.parse_args()
c = lp.comparator()
c.verify_target()
m = load_manifest()
spec = importlib.util.spec_from_file_location(
    "tail_coff", R / "scripts/compare-giant-action-switches.py"
)
coff = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = coff
spec.loader.exec_module(coff)
image = pefile.PE(str(R / "resources/th105.exe")).get_memory_mapped_image()
u = m["units"]["gpt-web-aya-object-vslot28-full-root"]
f = u["functions"][0]


class Probe:
    def __init__(self, obj=None):
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc = self.uc
        uc.mem_map(0x400000, 0x310000)
        uc.mem_write(0x400000, image)
        uc.mem_protect(0x400000, 0x310000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        uc.mem_protect(0x6FA000, 0x1000, unicorn.UC_PROT_READ | unicorn.UC_PROT_WRITE)
        uc.mem_map(BASE, 0x10000)
        uc.mem_map(STACK, 0x10000)
        uc.mem_map(STOP, 0x1000)
        uc.mem_write(STOP, b"\xcc")
        self.retirement_window = None
        self.read_windows = {}
        self.start = A
        self.end = A + 19522
        if obj:
            co = coff.CoffObject(obj, symbol_base=f["symbol_base"])
            code = c.coff_symbol_bytes(
                obj,
                f["symbol_base"],
                S,
                len(co.text),
                {
                    x: int(y, 0)
                    for x, y in (z.split("=", 1) for z in f.get("rel32_targets", []))
                },
                c.known_data_targets(),
                dict(z.split("=", 1) for z in f.get("dir32_targets", [])),
            )
            window = c.target_bytes(0x61DC18, 76)
            if code.count(window) == 1:
                self.retirement_window = S + code.index(window)
            for address, size in ((0x61D8B9, 92), (0x61DBC8, 38), (0x61DC18, 90)):
                expected = c.target_bytes(address, size)
                if code.count(expected) == 1:
                    self.read_windows[hex(address)] = dict(
                        size=size, source=hex(S + code.index(expected))
                    )
            uc.mem_map(S, 0x10000)
            uc.mem_write(S, code)
            uc.mem_protect(S, 0x10000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            self.start = S
            self.end = S + len(code)
        uc.hook_add(unicorn.UC_HOOK_CODE, self.step)
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)
        uc.hook_add(unicorn.UC_HOOK_MEM_READ, self.read)

    def step(self, uc, pc, size, data):
        if pc == STOP:
            self.stopped = True
            uc.emu_stop()
            return
        if not self.start <= pc < self.end:
            raise RuntimeError("unexpected code " + hex(pc))

    def write(self, uc, access, address, size, value, data):
        if BASE <= address < BASE + 0x10000:
            self.events.append((address - BASE, size, value & ((1 << (size * 8)) - 1)))

    def read(self, uc, access, address, size, value, data):
        if (address == self.actor + 0x348 and size == 4) or (
            address in (BASE + 0x13C, BASE + 0x13E) and size == 2
        ):
            self.owner_reads.append(
                (
                    len(self.events),
                    address - BASE,
                    bytes(uc.mem_read(address, size)).hex(),
                )
            )

    def run(self, case):
        mode, state, x, seq, cw, alias = case[:6]
        facing, heading = case[6:8] if len(case) > 6 else (1, None)
        uc = self.uc
        actor = BASE + 0x3E8 if alias else BASE + 0x2000
        self.actor = actor
        owner = BASE
        uc.mem_write(BASE, b"\0" * 0x10000)
        uc.mem_write(STACK, b"\0" * 0x10000)

        def w(a, fmt, v):
            uc.mem_write(a, struct.pack("<" + fmt, v))

        w(actor + 0x13C, "h", 900)
        w(actor + 0x348, "I", owner)
        w(actor + 0x330, "i", 5)
        w(actor + 0x364, "h", 1)
        w(actor + 0xEC, "f", x)
        w(actor + 0xF0, "f", 100)
        w(actor + 0x104, "b", facing)
        w(owner + 0x13C, "h", case[8] if len(case) > 8 else 710)
        w(owner + 0x13E, "h", seq)
        w(owner + 0x186, "h", 1)
        if heading is not None:
            w(owner + 0x186, "h", 0)
            w(actor + 0x340, "I", BASE + 0x8000)
            w(BASE + 0x8004, "f", heading)
        if not alias:
            w(owner + 0x730, "H", state)
        else:
            w(owner + 0xA31, "h", 2)
        w(0x6FA894, "I", mode & 0xFFFFFFFF)
        sp = STACK + 0xF000
        w(sp, "I", STOP)
        registers = (
            r.UC_X86_REG_EBX,
            r.UC_X86_REG_ESI,
            r.UC_X86_REG_EDI,
            r.UC_X86_REG_EBP,
        )
        for i, reg in enumerate(registers):
            uc.reg_write(reg, 0x11111111 * (i + 1))
        uc.reg_write(r.UC_X86_REG_ECX, actor)
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_FPCW, cw)
        uc.reg_write(r.UC_X86_REG_FPSW, 0)
        uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
        uc.reg_write(r.UC_X86_REG_EFLAGS, 2)
        self.events = []
        self.owner_reads = []
        self.stopped = False
        uc.emu_start(self.start, 0, count=1000)
        assert self.stopped
        assert [uc.reg_read(reg) for reg in registers] == [
            0x11111111 * (i + 1) for i in range(4)
        ]
        assert uc.reg_read(r.UC_X86_REG_ESP) == sp + 4
        return (
            hashlib.sha256(bytes(uc.mem_read(BASE, 0x10000))).hexdigest(),
            self.events,
            uc.reg_read(r.UC_X86_REG_FPSW),
            uc.reg_read(r.UC_X86_REG_FPTAG),
            self.owner_reads,
        )


objects = [R / u["object"]]
if args.previous_object:
    objects.insert(0, args.previous_object)
probes = [Probe()] + [Probe(p) for p in objects]
assert probes[-1].retirement_window is not None, "target retirement window differs"
assert len(probes[-1].read_windows) == 3, "target owner-read windows differ"
counts = dict(
    normal=0,
    alias=0,
    old_normal_differences=0,
    old_alias_differences=0,
    new_differences=0,
    previous_effect_differences=0,
    previous_read_epoch_differences=0,
)
samples = []
cases = list(
    itertools.product(
        (0, 1, 2, 3, -1, 0x7FFFFFFF, 0x80000000),
        (0, 1, 2, 3, 0x8000, 0xFFFF),
        (2000.0, 2001.0, -720.0, -721.0),
        (1, 2),
        (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
        (False,),
    )
)
cases += list(
    itertools.product(
        (0, 1, 2, 3, -1), (0,), (2000.0, -720.0), (1, 2), (0x37F,), (True,)
    )
)
# Movement stays outside the stage, so every case reaches a real RET without calls.
cases += [
    (*base, facing, heading)
    for base in itertools.product(
        (0, 1, 2, -1),
        (0, 2),
        (4000.0, -2000.0),
        (1, 2),
        (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
        (False,),
    )
    for facing in (-1, 1)
    for heading in (-100.25, -0.0, 0.0, 100.25)
]
# Invalid owner actions must return before reading the owner sequence word.
cases += [
    (0, 0, 2000.0, seq, 0x37F, False, 1, None, action)
    for action in (-32768, -1, 0, 709, 711, 32767)
    for seq in (-32768, -1, 0, 1, 2, 32767)
]
for case in cases:
    results = [p.run(case) for p in probes]
    kind = "alias" if case[5] else "normal"
    counts[kind] += 1
    if args.previous_object:
        counts["previous_effect_differences"] += results[0][:-1] != results[1][:-1]
        counts["previous_read_epoch_differences"] += results[0][-1] != results[1][-1]
    if args.previous_object and results[0] != results[1]:
        counts["old_" + kind + "_differences"] += 1
    if results[0] != results[-1]:
        counts["new_differences"] += 1
        if len(samples) < 3:
            samples.append(dict(case=case, results=results))
report = dict(
    target_sha256=c.verify_target(),
    objects=[dict(path=str(p), sha256=lp.sha(p)) for p in objects],
    compared_previous=bool(args.previous_object),
    translated_read_windows=probes[-1].read_windows,
    translated_retirement_window=dict(
        target="0x61DC18", source=hex(probes[-1].retirement_window), size=76
    ),
    counts=counts,
    samples=samples,
    scope="full root entry to actual RET; no opaque callees; finite normal disjoint-object cases; alias cases artificial raw ABI stress, not game reachability or valid C++ object overlap",
    input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
)
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps(report, indent=2))

if counts["new_differences"]:
    raise SystemExit(1)
