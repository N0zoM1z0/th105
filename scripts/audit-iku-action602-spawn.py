#!/usr/bin/env python3
"""Execute original Iku action602 through its periodic object852 spawn boundary.

Seed, warm draw, selectors, texture/landing/frame helpers are original code.
Execution stops before the object manager; no helper result is substituted.
There is no candidate root or full-root RET/equivalence claim.
"""
import argparse
from collections import Counter
import csv
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct

import capstone
import pefile
import unicorn
from unicorn import x86_const as registers

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
OWNER, PEER, MANAGER, DEQUE = 0x2000000, 0x2002000, 0x2004000, 0x2006000
STACK, RETURN = 0x1000000, 0xF000000
ENTRY_SP = STACK + 0xFF00
HELPERS = (0x406670, 0x4066B0, 0x4067D0, 0x45F560, 0x42D1B0,
           0x473DD0, 0x4351C0, 0x435D60, 0x435DC0, 0x68A1A0)
SEEDS = tuple(range(32)) + (119, 145, 388, 1472677)


def float_bits(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


def rounded_float(value):
    return struct.unpack("<f", struct.pack("<f", value))[0]


def input_cases(smoke):
    if smoke:
        return [dict(zip(("seed", "x", "facing", "counter", "control_word"), values))
                for values in itertools.product((1, 2, 9, 119, 145, 388, 1472677),
                                                 (320.0, 640.0, 1000.0), (1,), (5,), (0x27F,))]
    return [dict(zip(("seed", "x", "facing", "counter", "control_word"), values))
            for values in itertools.product(SEEDS, (0.0, 1.0, 128.0, 320.0, 640.0, 1000.0, 1279.0),
                                             (-1, 1), (5, 35), (0x27F, 0x37F))]


class Probe:
    def __init__(self, canonical, mapped, sizes):
        self.canonical, self.sizes = canonical, sizes
        self.engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        uc = self.engine
        uc.mem_map(0x400000, 0x311000)
        uc.mem_write(0x400000, mapped)
        for address, size in ((STACK, 0x10000), (OWNER, 0x10000), (RETURN, 0x1000)):
            uc.mem_map(address, size)
        decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        spans = [(0x620920, 59038), *sizes.items()]
        self.boundaries = {address for start, length in spans
                           for address, _, _, _ in decoder.disasm_lite(canonical.target_bytes(start, length), start)}
        self.initial = uc.context_save()
        self.phase, self.failure = "setup", None
        self.seed_cache = {}
        self.visited, self.call_counts = set(), Counter()
        uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        allowed = ((STACK, STACK + 0x10000), (OWNER, OWNER + 0x7B8),
                   (MANAGER, MANAGER + 0x1000), (0x6FDEF0, 0x6FDEF0 + 2496),
                   (0x6FA1FC, 0x6FA200))
        if not any(first <= address and address + size <= last for first, last in allowed):
            self.failure = f"write outside actor/manager/stack/RNG fixture at {address:#x}"
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        try:
            if self.phase == "root" and address == 0x465190:
                esp = uc.reg_read(registers.UC_X86_REG_ESP)
                returned, = struct.unpack("<I", uc.mem_read(esp, 4))
                self.arguments = struct.unpack("<7I", uc.mem_read(esp + 4, 28))
                if (returned != 0x62C5F7 or self.arguments[0] != 852
                        or self.arguments[6] != 3 or esp - ENTRY_SP != -1080
                        or uc.reg_read(registers.UC_X86_REG_ECX) != OWNER):
                    raise ValueError("unexpected object852 caller/ABI/stack boundary")
                pointer = self.arguments[5]
                if not STACK <= pointer <= STACK + 0x10000 - 12:
                    raise ValueError("payload is not inside the original root stack frame")
                self.payload = bytes(uc.mem_read(pointer, 12))
                self.stopped = True
                uc.emu_stop()
                return
            if address not in self.boundaries:
                raise ValueError(f"unreviewed instruction boundary {address:#x}")
            if self.phase == "root":
                if 0x620920 <= address < 0x62EFBE:
                    self.visited.add(address)
                    self.case_visited.add(address)
                if address in self.sizes:
                    self.call_counts[hex(address)] += 1
                if address == 0x4067EA:
                    esp = uc.reg_read(registers.UC_X86_REG_ESP)
                    limit, = struct.unpack("<I", uc.mem_read(esp + 4, 4))
                    self.rolls.append((limit, uc.reg_read(registers.UC_X86_REG_EAX)))
        except Exception as error:
            self.failure = str(error)
            uc.emu_stop()

    def seed(self, seed):
        if seed not in self.seed_cache:
            uc = self.engine
            for phase, entry in (("seed", 0x406670), ("warm", 0x4066B0)):
                self.phase, self.failure = phase, None
                uc.context_restore(self.initial)
                uc.mem_write(ENTRY_SP, struct.pack("<II", RETURN, seed))
                uc.reg_write(registers.UC_X86_REG_ESP, ENTRY_SP)
                uc.emu_start(entry, RETURN, count=100000)
                if self.failure or uc.reg_read(registers.UC_X86_REG_EIP) != RETURN:
                    raise ValueError(f"original RNG setup failed: {self.failure}")
            self.seed_cache[seed] = (bytes(uc.mem_read(0x6FDEF0, 2496)),
                                     bytes(uc.mem_read(0x6FA1FC, 4)))
        return self.seed_cache[seed]

    def evaluate(self, case):
        if (case["facing"] not in (-1, 1) or case["counter"] not in (5, 35)
                or case["control_word"] not in (0x27F, 0x37F) or not 0 <= case["x"] <= 1279):
            raise ValueError("input outside reviewed action602 fixture")
        state, index = self.seed(case["seed"])
        uc = self.engine
        uc.context_restore(self.initial)
        uc.mem_write(0x6FDEF0, state)
        uc.mem_write(0x6FA1FC, index)
        for address, length in ((OWNER, 0x7B8), (PEER, 0x1000), (MANAGER, 0x1000),
                                (DEQUE, 0x1000), (STACK, 0x10000)):
            uc.mem_write(address, bytes(length))
        fields = ((0, "I", 0x6C652C), (0xEC, "f", case["x"]), (0xF0, "f", 0.0),
                  (0x104, "b", case["facing"]), (0x13C, "h", 602), (0x13E, "h", 1),
                  (0x144, "i", case["counter"]), (0x14C, "h", 32767),
                  (0x170, "I", PEER), (0x174, "h", 1000))
        for offset, fmt, value in fields:
            uc.mem_write(OWNER + offset, struct.pack("<" + fmt, value))
        # Real checked deque<int>, with three valid texture handles. The target
        # publishes handle2 into both manager texture slots; no render backend.
        uc.mem_write(OWNER + 0x68C, struct.pack("<5I", 0, DEQUE, 8, 0, 3))
        uc.mem_write(DEQUE, struct.pack("<I", DEQUE + 0x100))
        uc.mem_write(DEQUE + 0x100, struct.pack("<4I", 0x30000, 0x30001, 0x30002, 0x30003))
        manager_global = self.canonical.known_data_targets()[
            "?g_battle_object_manager@th105@@3PAUBattleObjectManager@1@A"][0]
        uc.mem_write(manager_global, struct.pack("<I", MANAGER))
        uc.mem_write(ENTRY_SP, struct.pack("<I", RETURN))
        uc.reg_write(registers.UC_X86_REG_ESP, ENTRY_SP)
        uc.reg_write(registers.UC_X86_REG_ECX, OWNER)
        uc.reg_write(registers.UC_X86_REG_FPCW, case["control_word"])
        self.phase, self.failure, self.stopped = "root", None, False
        self.rolls, self.case_visited = [], set()
        uc.emu_start(0x620920, RETURN, count=100000)
        if self.failure or not self.stopped or uc.reg_read(registers.UC_X86_REG_EIP) != 0x465190:
            raise ValueError(f"original root failed its spawn boundary: {self.failure}")
        if [limit for limit, value in self.rolls] != [500, 400]:
            raise ValueError("original selector call order differs")
        if (uc.reg_read(registers.UC_X86_REG_FPCW) != case["control_word"]
                or ((uc.reg_read(registers.UC_X86_REG_FPSW) >> 11) & 7)
                or struct.unpack("<2I", uc.mem_read(MANAGER + 0xD8, 8)) != (0x30002, 0x30002)
                or struct.unpack("<i", uc.mem_read(OWNER + 0x144, 4))[0] != case["counter"] + 1
                or struct.unpack("<h", uc.mem_read(OWNER + 0x142, 2))[0] != 1):
            raise ValueError("original helper effects, stack or x87 state differ")
        vertical, horizontal = (value for limit, value in self.rolls)
        offset = (horizontal - 200) & 0xFFFFFFFF
        expected_x = float_bits(float(offset) + case["x"])
        expected_y = float_bits(float(vertical))
        if (self.arguments[1:5] != (expected_x, expected_y, case["facing"] & 0xFF, 1)
                or self.payload != struct.pack("<3f", 0.0, 0.0, 5.0)
                or (0x62C5D4 in self.case_visited) != (horizontal < 200)):
            raise ValueError("original spawn differs from unsigned/late-rounding model")
        return {"rolls": self.rolls, "x_bits": f"{expected_x:08x}",
                "unsigned_fixup_taken": horizontal < 200,
                "signed_control_differs": float_bits(horizontal - 200 + case["x"]) != expected_x,
                "early_float_control_differs": float_bits(rounded_float(float(offset)) + case["x"]) != expected_x}


def audit(smoke=False):
    spec = importlib.util.spec_from_file_location("iku_unsigned_facts", ROOT / "scripts/audit-iku-random-float-tails.py")
    facts_module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(facts_module)
    facts = facts_module.audit()
    canonical = linked_pe.comparator()
    mapped = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    stage = canonical.known_data_targets()["?g_stage_surface_heights@th105@@3PAMA"][0] - 0x400000
    if mapped[stage:stage + 0x1400] != bytes(0x1400):
        raise ValueError("fixture requires the attested initially flat stage")
    if struct.unpack("<I", canonical.target_bytes(0x6C6554, 4))[0] != 0x620920:
        raise ValueError("Iku primary vslot28 differs")
    ledger = {int(row["address"], 0): int(row["size"])
              for row in csv.DictReader((ROOT / "config/functions.csv").open())}
    sizes = {address: ledger[address] for address in HELPERS}
    probe = Probe(canonical, mapped, sizes)
    digest, output_digest, counts, rolls, examples = hashlib.sha256(), hashlib.sha256(), Counter(), set(), []
    cases = input_cases(smoke)
    for case in cases:
        digest.update(json.dumps(case, sort_keys=True).encode())
        result = probe.evaluate(case)
        output_digest.update(json.dumps(result, sort_keys=True).encode())
        rolls.add(result["rolls"][1][1])
        for key in ("unsigned_fixup_taken", "signed_control_differs", "early_float_control_differs"):
            counts[key] += result[key]
        if case["facing"] == 1 and case["counter"] == 5 and case["control_word"] == 0x27F and case["seed"] in (2, 9, 119, 145, 388, 1472677) and case["x"] == 640:
            examples.append({"input": case, **result})
    if not {0, 199, 200, 201, 400} <= rolls or not all(counts.values()):
        raise ValueError("boundary seeds or numerical negative controls were not exercised")
    return {"schema": "th105-iku-action602-native-spawn-v1", "evidence": "original target to spawn entry; not root exactness",
            "target_sha256": facts["target_sha256"], "root_sha256": facts["root_body_sha256"],
            "unicorn_version": unicorn.__version__, "unicorn_library_sha256": linked_pe.sha(Path(unicorn.unicorn._uc._name)),
            "helper_hashes": {hex(address): hashlib.sha256(canonical.target_bytes(address, size)).hexdigest()
                              for address, size in sizes.items()},
            "cases": len(cases), "model_mismatches": 0, "input_sha256": digest.hexdigest(),
            "output_sha256": output_digest.hexdigest(), "controls": dict(counts),
            "observed_horizontal_rolls": sorted(rolls), "visited_root_instructions": len(probe.visited),
            "helper_calls": dict(probe.call_counts), "examples": examples,
            "scope": "original root entry, native seed/warm/MT/selectors and texture/landing/frame helpers; "
                     "grounded flat stage, unexpired frame, sequence1, periodic counters6/36; "
                     "object852 seven DWORD arguments and three-float payload, x87 PC53/64 and stack checked; "
                     "stop before spawn implementation; no backend execution, native root RET, candidate or complete gameplay claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--smoke", action="store_true")
    args = parser.parse_args()
    print(json.dumps(audit(args.smoke), indent=2))
