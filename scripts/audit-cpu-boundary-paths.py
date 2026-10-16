#!/usr/bin/env python3
"""Execute bounded CPU boundary paths against the pinned PE (diagnostic only).

The target's real float-to-integer runtime executes. Two deterministic hooks
supply bounded RNG results and a checked sequence record. This checks the outer
action phase up to the shared policy join, not complete gameplay or exactness.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import pefile

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0x5F1F80
SIZE = 15910
BODY_SHA256 = "fb26e85839101f4dc89506c9d51a14b76c729b6836d0efe2c063d18b22c10f77"


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def policy_join(code, address):
    """Require the unique counter-test / policy-constant pair, on boundaries."""
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, address))
    if not instructions or sum(i.size for i in instructions) != len(code):
        raise ValueError("incomplete callable decoding")
    sites = [a.address for a, b in zip(instructions, instructions[1:])
             if (a.mnemonic, a.op_str) == ("cmp", "word ptr [esi + 0x766], bx")
             and (b.mnemonic, b.op_str) == ("mov", "ebp, 7")]
    if len(sites) != 1:
        raise ValueError("expected one shared CPU policy join")
    return sites[0]


def input_cases():
    values = {0, 0x80000000, 1, 0x80000001, 0x7F7FFFFF, 0xFF7FFFFF,
              0x7F800000, 0xFF800000, 0x7FC00000, 0xFFC00000, 0x7FC12345,
              0x7F800001, 0xFF800001}
    for value in (300.0, 400.0, 860.0, 960.0):
        bits = struct.unpack("<I", struct.pack("<f", value))[0]
        values.update((bits - 1, bits, bits + 1))
    actions = (302, 304, 322, 410, 412)
    sequences = (-1, 199, 200, 201, 202, 203, 204, 205, 206, 210, 211, 212, 213)
    primary = itertools.product(actions, sequences, sorted(values), (-1, 1), (1, 3), (100,), (0x27F, 0x37F))
    guards = itertools.product(actions, (200, 205, 212, 213), (0, 0x44570000, 0x7FC00000),
                               (-1, 1), (0, 1, 2, 3), (-32768, -1, 0, 94, 95, 100, 101, 32767), (0x27F,))
    yield from dict.fromkeys(itertools.chain(primary, guards))


class CpuProbe:
    OWNER, OTHER, RECORD, STACK = 0x2000000, 0x2010000, 0x2020000, 0x1000000

    def __init__(self, mapped, code, callable_size, *, address=ADDRESS):
        import unicorn
        from unicorn import x86_const as registers
        self.reg = registers
        self.address = address
        self.engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc = self.engine
        uc.mem_map(0x400000, 0x310000)
        uc.mem_write(0x400000, mapped)
        uc.mem_write(self.address, code)
        for address in (self.OWNER, self.OTHER, self.RECORD, self.STACK):
            uc.mem_map(address, 0x10000)
        self.join = policy_join(code[:callable_size], self.address)
        self.initial = uc.context_save()
        uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        allowed = any(base <= address and address + size <= base + 0x10000
                      for base in (self.OWNER, self.STACK))
        if not allowed:
            self.failure = f"unexpected emulated write at {address:#x}"
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        try:
            self.step(uc, address)
        except Exception as error:
            self.failure = str(error)
            uc.emu_stop()

    def step(self, uc, address):
        r = self.reg
        if address == self.join:
            self.stopped = True
            uc.emu_stop()
        elif address in (0x4067D0, 0x4399C0):
            esp = uc.reg_read(r.UC_X86_REG_ESP)
            returned, argument = struct.unpack("<II", uc.mem_read(esp, 8))
            if address == 0x4399C0:
                if argument != 0 or uc.reg_read(r.UC_X86_REG_ECX) != self.OWNER + 0x55C:
                    raise ValueError("checked-sequence hook ABI mismatch")
                value, cleanup = self.RECORD, 8
            else:
                if argument not in (100, 1000):
                    raise ValueError("unexpected random bound")
                value, cleanup = 0, 4
            self.calls.append((address, argument))
            uc.reg_write(r.UC_X86_REG_EAX, value)
            uc.reg_write(r.UC_X86_REG_ESP, esp + cleanup)
            uc.reg_write(r.UC_X86_REG_EIP, returned)
        elif address in (0x406540, 0x4066B0):
            raise ValueError("unreviewed helper reached by this bounded probe")

    def run(self, case):
        action, sequence, xbits, facing, mode, counter, control_word = case
        uc, r = self.engine, self.reg
        uc.context_restore(self.initial)
        for base in (self.OWNER, self.OTHER):
            uc.mem_write(base, bytes(0x1000))
        uc.mem_write(self.STACK + 0xC000, bytes(0x4000))

        def put(offset, fmt, value):
            uc.mem_write(self.OWNER + offset, struct.pack(fmt, value))

        put(0x170, "<I", self.OTHER)
        uc.mem_write(self.OTHER + 0x174, struct.pack("<h", 10000))
        uc.mem_write(self.RECORD, struct.pack("<h", sequence))
        put(0xEC, "<I", xbits)
        put(0x104, "<b", facing)
        put(0x13C, "<h", action)
        put(0x180, "<I", mode)
        put(0x55A, "<b", 1)
        put(0x6B4, "<i", -7)
        put(0x6B8, "<i", 5)
        put(0x764, "<h", counter)
        put(0x766, "<h", 1)
        uc.reg_write(r.UC_X86_REG_ESP, self.STACK + 0xFF00)
        uc.reg_write(r.UC_X86_REG_ECX, self.OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, control_word)
        self.stopped, self.calls, self.failure = False, [], None
        uc.emu_start(self.address, 0x710000, count=10000)
        if self.failure:
            raise ValueError(self.failure)
        if not self.stopped:
            raise ValueError("CPU path failed to reach the reviewed policy join")
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("CPU path leaves live x87 values at the policy join")
        return {"control": bytes(uc.mem_read(self.OWNER + 0x6B4, 32)).hex(),
                "command_flags": bytes(uc.mem_read(self.OWNER + 0x724, 8)).hex(),
                "policy_words": bytes(uc.mem_read(self.OWNER + 0x764, 12)).hex(),
                "policy_state": bytes(uc.mem_read(self.OWNER + 0x180, 4)).hex(),
                "calls": self.calls,
                "stack_delta": uc.reg_read(r.UC_X86_REG_ESP) - (self.STACK + 0xFF00)}


def audit(object_path):
    import unicorn
    from unicorn import unicorn as unicorn_api
    canonical = load_script("cpu_boundary_canonical", "compare-function.py")
    target_hash = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA256:
        raise ValueError("CPU callable boundary/hash changed")
    mapper = load_script("cpu_boundary_mapper", "compare-giant-action-switches.py")
    roots = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = mapper.load_target_mapper().select_root(roots, "default-cpu-action-policy")
    unit = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]["gpt-web-default-cpu-action-policy"]
    function, = unit["functions"]
    obj = mapper.CoffObject(object_path)
    symbols = [s for s in obj.symbols.values() if s.name == function["symbol_base"]]
    if len(symbols) != 1 or symbols[0].value != 0 or symbols[0].section_number != obj.text_section_number:
        raise ValueError("CPU root must start the selected COFF section")
    candidate_map = mapper.build_candidate_map(obj, root)
    rel32 = canonical.known_targets()
    rel32.update({k: int(v, 0) for k, v in (s.split("=", 1) for s in function["rel32_targets"])})
    dir32 = dict(s.split("=", 1) for s in function["dir32_targets"])
    candidate = canonical.coff_symbol_bytes(object_path, function["symbol_base"], ADDRESS, len(obj.text),
                                             rel32, canonical.known_data_targets(), dir32)
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    engines = (CpuProbe(image, target, SIZE), CpuProbe(image, candidate, candidate_map["metadata_start"]))
    mismatches, count = [], 0
    for case in input_cases():
        expected, actual = (engine.run(case) for engine in engines)
        count += 1
        if expected != actual:
            mismatches.append({"action": case[0], "sequence": case[1], "x_bits": f"{case[2]:08x}",
                               "facing": case[3], "mode": case[4], "counter": case[5],
                               "x87_control_word": f"{case[6]:04x}", "target": expected, "candidate": actual})
        if count % 4000 == 0:
            print(f"CPU boundary controls: {count}, differences {len(mismatches)}", file=sys.stderr)
    library = Path(unicorn_api._uc._name)
    return {"schema": "th105-cpu-boundary-paths-v1", "evidence": "bounded emulation; no exact credit",
            "build_provenance_verified": False, "target_sha256": target_hash,
            "body_sha256": BODY_SHA256, "object_sha256": hashlib.sha256(object_path.read_bytes()).hexdigest(),
            "unicorn_version": unicorn.__version__, "unicorn_library_sha256": hashlib.sha256(library.read_bytes()).hexdigest(),
            "cases": count, "mismatch_count": len(mismatches), "mismatches": mismatches,
            "scope": "outer actions302/304/322/410/412 to policy join; masked exceptions, round-to-nearest, x87 PC53/64; deterministic RNG0 and checked-sequence hooks; real target ftol2 executes; numerical exceptions and complete gameplay are not proved"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except Exception as error:
        parser.exit(2, f"CPU boundary execution failed: {error}\n")
    print(json.dumps(result, indent=2))
    return int(bool(result["mismatch_count"]))


if __name__ == "__main__":
    raise SystemExit(main())
