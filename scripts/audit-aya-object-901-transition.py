#!/usr/bin/env python3
"""Audit Aya901 transitions with original animation callees and actual root returns."""

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

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import linked_pe as lp
from workflow_manifest import load_manifest
from native_callbacks import guarded_callback


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--previous-object", type=Path)
parser.add_argument(
    "--output", type=Path, default=ROOT / "build/aya901-transition.json"
)
args = parser.parse_args() if __name__ == "__main__" else None
c = lp.comparator()
c.verify_target()
entry = load("aya901_animation", "scripts/audit-reimu-object-entry-calls.py")
mapper = load("aya901_coff", "scripts/compare-giant-action-switches.py")
A, S, OWNER, STACK, RESOURCE, RETURN = (
    0x61A290,
    0x800000,
    entry.OWNER,
    entry.STACK,
    entry.RESOURCE,
    entry.RETURN,
)
helpers = dict(entry.animation.HELPERS)
helpers[0x64CD00] = (73, "phase_counter")
unit = load_manifest()["units"]["gpt-web-aya-object-vslot28-full-root"]
f = unit["functions"][0]
image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
assert struct.unpack("<I", c.target_bytes(0x6C624C + 0x14, 4))[0] == 0x45C220


class Probe:
    require_901_calls = True
    action_id = 901

    def prepare(self, case):
        pass

    def __init__(self, obj=None):
        self.uc = uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        uc.mem_write(0x400000, image)
        self.start, self.size = A, 19522
        if obj:
            co = mapper.CoffObject(obj, symbol_base=f["symbol_base"])
            code = c.coff_symbol_bytes(
                obj,
                f["symbol_base"],
                S,
                len(co.text),
                {
                    a: int(b, 0)
                    for a, b in (z.split("=", 1) for z in f["rel32_targets"])
                },
                c.known_data_targets(),
                dict(z.split("=", 1) for z in f.get("dir32_targets", [])),
            )
            uc.mem_map(S, 0x10000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            uc.mem_write(S, code)
            self.start, self.size = S, len(code)
        uc.mem_map(OWNER, 0x10000)
        uc.mem_map(STACK, 0x10000)
        uc.mem_map(RESOURCE, 0x10000, unicorn.UC_PROT_READ)
        self.initial = uc.context_save()
        self.hook_errors = []
        uc.hook_add(unicorn.UC_HOOK_CODE, guarded_callback(self.step, self.hook_errors))
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, guarded_callback(self.write, self.hook_errors))
        uc.hook_add(unicorn.UC_HOOK_MEM_READ, guarded_callback(self.read, self.hook_errors))

    def step(self, uc, pc, size, data):
        if pc == 0x435160:
            self.stop = "unexpected_oriented_entry"
            uc.emu_stop()
            return
        if not (
            self.start <= pc < self.start + self.size
            or any(a <= pc < pc + size <= a + n for a, (n, _) in helpers.items())
        ):
            raise ValueError(f"unreviewed code {pc:#x}")
        if pc in helpers:
            self.calls.append(pc)
        if pc == 0x45C220:
            assert uc.reg_read(r.UC_X86_REG_ECX) == OWNER
            assert bytes(uc.mem_read(OWNER, 4)) == struct.pack("<I", 0x6C624C)

    def write(self, uc, access, address, size, value, data):
        if (
            OWNER <= address < address + size <= OWNER + 0x388
            or OWNER + 0x8000 <= address < address + size <= OWNER + 0x8008
        ):
            self.writes.append((address - OWNER, size, value & ((1 << (size * 8)) - 1)))
        elif not STACK <= address < address + size <= STACK + 0x10000:
            raise ValueError(f"unreviewed write {address:#x}")

    def read(self, uc, access, address, size, value, data):
        if address == OWNER + 0x113 and size == 1:
            self.reads.append(
                (len(self.writes), bytes(uc.mem_read(address, size)).hex())
            )

    def run(self, case):
        seq, phase, health, cw, amplitude = case[:5]
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x10000))
        uc.mem_write(STACK, bytes(0x10000))
        graph = bytearray(entry.graph(dict(action=self.action_id, request=0)))
        struct.pack_into("<ff", graph, entry.PARAMETERS - RESOURCE, 45.0, 12.0)
        uc.mem_write(RESOURCE, bytes(graph))
        # The real root changes its separate parameter record; animation resources stay read-only.
        uc.mem_write(OWNER + 0x8000, struct.pack("<ff", 45.0, 12.0))
        fields = (
            (0, "I", 0x6C624C),
            (0xEC, "f", 640.0),
            (0xF0, "f", 100.0),
            (0x104, "b", 1),
            (0x130, "I", entry.VECTOR),
            (0x13C, "h", self.action_id),
            (0x13E, "h", seq),
            (0x144, "i", 1),
            (0x148, "h", 1),
            (0x14C, "h", 3),
            (0x150, "I", entry.FRAME + seq * 0x100),
            (0x158, "I", entry.FRAME + seq * 0x100),
            (0x15C, "I", entry.BLOCK + seq * 0x20),
            (0x160, "I", entry.TREE),
            (0x180, "i", phase),
            (0x330, "i", 5),
            (0x340, "I", OWNER + 0x8000),
            (0x348, "I", OWNER + 0x1000),
            (0x370, "f", 10.0),
            (0x374, "f", amplitude),
            (0x384, "h", 20),
        )
        for off, fmt, value in fields:
            uc.mem_write(OWNER + off, struct.pack("<" + fmt, value))
        uc.mem_write(OWNER + 0x1174, struct.pack("<h", health))
        if len(case) > 5:
            alpha, scale_x, scale_y = case[5:]
            uc.mem_write(OWNER + 0x113, struct.pack("<B", alpha))
            uc.mem_write(OWNER + 0x11C, struct.pack("<II", scale_x, scale_y))
        self.prepare(case)
        registers = (
            r.UC_X86_REG_EBX,
            r.UC_X86_REG_ESI,
            r.UC_X86_REG_EDI,
            r.UC_X86_REG_EBP,
        )
        for i, reg in enumerate(registers):
            uc.reg_write(reg, 0x11111111 * (i + 1))
        sp = STACK + 0xFF00
        uc.mem_write(sp, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_FPCW, cw)
        uc.reg_write(r.UC_X86_REG_FPSW, 0)
        uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
        self.hook_errors.clear()
        self.stop = "ret"
        self.writes = []
        self.reads = []
        self.calls = []
        try:
            uc.emu_start(self.start, RETURN, count=20000)
        except unicorn.UcError as error:
            raise ValueError(
                f"native execution failed at {uc.reg_read(r.UC_X86_REG_EIP):#x}, calls={self.calls}, case={case}: {error}"
            ) from error
        if self.hook_errors:
            raise ValueError("native hook rejected execution: " + repr(self.hook_errors))
        if self.stop == "ret":
            assert uc.reg_read(r.UC_X86_REG_EIP) == RETURN
            assert uc.reg_read(r.UC_X86_REG_ESP) == sp + 4
            assert [uc.reg_read(reg) for reg in registers] == [
                0x11111111 * (i + 1) for i in range(4)
            ]
        if self.require_901_calls:
            assert self.calls.count(0x45C220) == (1 if seq in (0, 3) else 0)
        return dict(
            stop=self.stop,
            alpha_reads=self.reads,
            actor=bytes(uc.mem_read(OWNER, 0x388)).hex(),
            parameters=bytes(uc.mem_read(OWNER + 0x8000, 8)).hex(),
            writes=self.writes,
            calls=self.calls,
            status=uc.reg_read(r.UC_X86_REG_FPSW),
            tag=uc.reg_read(r.UC_X86_REG_FPTAG),
        )


def main(args):
    objects = [ROOT / unit["object"]]
    if args.previous_object:
        objects.insert(0, args.previous_object)
    probes = [Probe()] + [Probe(p) for p in objects]
    cases = list(
        itertools.product(
            (0, 3),
            (0, 1, 2, 4, 6, 8),
            (-1, 0),
            (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
            (-2.0, 0.0, 2.0, 20.0),
        )
    )
    cases += list(itertools.product((0, 3), (1, 2, 6), (100,), (0x27F, 0x37F), (20.0,)))
    scale_bits = (
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
    cases += [
        (2, 0, 100, cw, 20.0, alpha, sx, sy)
        for alpha, sx, sy, cw in itertools.product(
            (0, 4, 5, 6, 255),
            scale_bits,
            scale_bits,
            (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F),
        )
    ]
    counts = dict(
        cases=0,
        selected_differences=0,
        previous_differences=0,
        previous_continued=0,
        previous_alpha_read_differences=0,
        previous_effect_differences=0,
    )
    examples = []
    actual_helpers = set()
    for case in cases:
        results = [p.run(case) for p in probes]
        counts["cases"] += 1
        actual_helpers.update(results[0]["calls"])
        if results[0] != results[-1]:
            counts["selected_differences"] += 1
            if len(examples) < 2:
                examples.append(dict(case=case, results=results))
        if args.previous_object:
            counts["previous_effect_differences"] += {
                k: v for k, v in results[0].items() if k != "alpha_reads"
            } != {k: v for k, v in results[1].items() if k != "alpha_reads"}
            counts["previous_alpha_read_differences"] += (
                results[0]["alpha_reads"] != results[1]["alpha_reads"]
            )
            counts["previous_differences"] += results[0] != results[1]
            counts["previous_continued"] += (
                results[1]["stop"] == "unexpected_oriented_entry"
            )
    report = dict(
        target_sha256=c.verify_target(),
        objects=[dict(path=str(p), sha256=lp.sha(p)) for p in objects],
        original_helpers={
            hex(address): dict(
                size=helpers[address][0],
                sha256=hashlib.sha256(
                    c.target_bytes(address, helpers[address][0])
                ).hexdigest(),
            )
            for address in sorted(actual_helpers)
        },
        counts=counts,
        examples=examples,
        scope="901 sequence0/3 transition gates and sequence2 scale/fade; original phase/next-block/frame/texture-null helpers; target/selected actual RET; old source stops at unexpected oriented entry without fabricated return; finite valid animation fixture, not arbitrary resources or full-root proof",
        input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    if counts["selected_differences"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main(args)
