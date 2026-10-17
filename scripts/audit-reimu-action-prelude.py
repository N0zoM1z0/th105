#!/usr/bin/env python3
"""Compare Reimu's staged entry phase with bounded original instructions.

Stops before action dispatch or the first real spawn/action callback. No helper
result is fabricated, and this is not a whole-root or exact-unit comparator.
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

import pefile
import unicorn
from unicorn import unicorn as unicorn_api
from unicorn import x86_const as r

from giant_owner_audit import decode

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x478FA0, 81550
BODY_SHA = "dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6"
SYMBOL = "?run_checked_prelude@ReimuActionStatePreludeView@th105@@QAE_NXZ"
SPAWN = "?spawn_owned_object_via_manager@ReimuActionStatePreludeView@th105@@QAEHHMMHHHH@Z"
OWNER, PEER, STACK, RETURN = 0x1000000, 0x1020000, 0x1100000, 0x710000


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def cases(smoke=False):
    base = dict(action=200, timer=1, self_word=1, peer_word=1, state=1,
                count=6, latch=0, gate=0, peer_gate=0, effect=1, facing=1,
                x_bits=0x42C80000, y_bits=0x42480000, cw=0x27F)
    if smoke:
        for change in ({}, {"self_word": 0}, {"action": 10}, {"count": 32767},
                       {"gate": 1}, {"peer_gate": -1},
                       {"action": 150, "effect": 0, "facing": -1},
                       {"action": 154, "effect": 0}, {"action": 158, "effect": 0}):
            yield {**base, **change}
        return
    for action, timer, words, state, count, latch in itertools.product(
            (-1, 0, 10, 11), (-32768, -1, 0, 1, 2, 32767),
            ((1, 1), (0, 1), (1, 0), (-1, 1), (1, -1)),
            (0, 1, 7, 8), (-32768, -1, 0, 6, 7, 32767), (0, 1)):
        yield {**base, "action": action, "timer": timer, "self_word": words[0],
               "peer_word": words[1], "state": state, "count": count, "latch": latch}
    for gate, peer_gate, timer, state, count, latch in itertools.product(
            (-1, 0, 1), (-1, 0, 1), (0, 1), (0, 1, 7, 8),
            (-32768, -1, 0, 6, 7, 32767), (0, 1)):
        yield {**base, "gate": gate, "peer_gate": peer_gate, "timer": timer,
               "state": state, "count": count, "latch": latch}
    for action, effect, facing, bits, cw in itertools.product(
            range(149, 160), (0, 1, 128, 255), (-128, -1, 0, 1, 127),
            (0, 0x80000000, 1, 0x40400000, 0xC0400000, 0x501502F9,
             0x7F800000, 0x7FC12345, 0x7F812345), (0x27F, 0x37F)):
        yield {**base, "action": action, "effect": effect, "facing": facing,
               "x_bits": bits, "y_bits": bits, "cw": cw}


class Probe:
    def __init__(self, image, code, candidate):
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000)
        self.uc.mem_write(0x400000, image)
        self.uc.mem_write(ADDRESS, code)
        for address in (OWNER, PEER, STACK):
            self.uc.mem_map(address, 0x10000)
        self.initial = self.uc.context_save()
        self.candidate = candidate
        self.code_end = ADDRESS + len(code)
        self.visited = set()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        if not (OWNER <= address <= address + size <= OWNER + 0x7D0
                or STACK <= address <= address + size <= STACK + 0x10000):
            self.error = f"write outside actor/stack: {address:#x}"
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        self.visited.add(address)
        if address in (0x465190, 0x45BFE0):
            if uc.reg_read(r.UC_X86_REG_ECX) != OWNER:
                self.error = "callback receiver differs from entry receiver"
            count = 7 if address == 0x465190 else 1
            self.result = {"exit": "spawn" if count == 7 else "action",
                           "arguments": bytes(uc.mem_read(uc.reg_read(r.UC_X86_REG_ESP) + 4,
                                                         count * 4)).hex()}
            uc.emu_stop()
        elif not self.candidate and address == 0x4791D4:
            self.result = {"exit": "dispatch"}
            uc.emu_stop()
        elif not ((self.candidate and ADDRESS <= address < self.code_end)
                  or (not self.candidate and (ADDRESS <= address < 0x4791D4
                                             or 0x489D6A <= address < 0x489D72))):
            self.error = f"unreviewed execution at {address:#x}"
            uc.emu_stop()

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x1000))
        uc.mem_write(PEER, bytes(0x1000))
        uc.mem_write(STACK + 0xC000, bytes(0x4000))
        fields = ((0, "I", 0x6C412C), (0xEC, "I", case["x_bits"]),
                  (0xF0, "I", case["y_bits"]), (0x104, "b", case["facing"]),
                  (0x13C, "h", case["action"]), (0x170, "I", PEER),
                  (0x174, "h", case["self_word"]), (0x180, "i", case["state"]),
                  (0x186, "h", case["gate"]), (0x751, "B", case["effect"]),
                  (0x7A0, "h", -3), (0x7A2, "h", -4), (0x7C8, "h", case["timer"]),
                  (0x7CA, "h", case["count"]), (0x7CC, "h", case["latch"]))
        for offset, fmt, value in fields:
            uc.mem_write(OWNER + offset, struct.pack("<" + fmt, value))
        for offset, value in ((0x174, case["peer_word"]), (0x48C, case["peer_gate"])):
            uc.mem_write(PEER + offset, struct.pack("<h", value))
        sentinels = {r.UC_X86_REG_EBX: 0x12345678, r.UC_X86_REG_ESI: 0x22345678,
                     r.UC_X86_REG_EDI: 0x32345678, r.UC_X86_REG_EBP: 0x42345678}
        for register, value in sentinels.items():
            uc.reg_write(register, value)
        sp = STACK + 0xFF00
        uc.mem_write(sp, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["cw"])
        self.result, self.error = None, None
        uc.emu_start(ADDRESS, RETURN, count=5000)
        if self.error:
            raise ValueError(self.error)
        if uc.reg_read(r.UC_X86_REG_EIP) == RETURN:
            if (uc.reg_read(r.UC_X86_REG_ESP) != sp + 4
                    or any(uc.reg_read(key) != value for key, value in sentinels.items())):
                raise ValueError("entry helper/handled target path violates native RET ABI")
            self.result = {"exit": "handled" if not self.candidate
                           or uc.reg_read(r.UC_X86_REG_EAX) & 0xFF else "dispatch"}
        if self.result is None:
            raise ValueError("entry phase did not reach a reviewed exit")
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("entry phase leaves live x87 values")
        return {**self.result, "actor": bytes(uc.mem_read(OWNER, 0x7D0)).hex(),
                "control_word": uc.reg_read(r.UC_X86_REG_FPCW)}


def audit(object_path, smoke=False):
    canonical = load_script("reimu_prelude_canonical", "compare-function.py")
    target_hash = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError("Reimu callable bytes changed")
    mapper = load_script("reimu_prelude_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(object_path, symbol_base=SYMBOL)
    known = dict(canonical.known_data_targets())
    # Private diagnostic bindings only, with exact double bytes read back.
    # Do not broaden shared relocation ledgers for a staged source fragment.
    for bits, address in (("4057800000000000", 0x6C3EB0),
                          ("404e000000000000", 0x6C1888),
                          ("4059000000000000", 0x6CD190)):
        literal = bytes.fromhex(bits)[::-1]
        if canonical.target_bytes(address, 8) != literal:
            raise ValueError("entry literal binding changed")
        key = "__real@" + bits
        if key not in known:
            known[key] = (address, literal, frozenset({0}), "literal")
    candidate = canonical.coff_symbol_bytes(object_path, SYMBOL, ADDRESS, len(obj.text),
                                             {SPAWN: 0x465190}, known, {})
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    probes = [Probe(image, target, False), Probe(image, candidate, True)]
    digest, counts, examples, mismatches = hashlib.sha256(), {}, [], 0
    object_hash = hashlib.sha256(object_path.read_bytes()).hexdigest()
    count = 0
    for count, case in enumerate(cases(smoke), 1):
        digest.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = (probe.evaluate(case) for probe in probes)
        counts[expected["exit"]] = counts.get(expected["exit"], 0) + 1
        if expected != actual:
            mismatches += 1
            if len(examples) < 8:
                examples.append({"case": case, "target": expected, "candidate": actual})
        if count % 2000 == 0:
            print(f"Reimu entry: {count}, differences {mismatches}", file=sys.stderr)
    if count != (9 if smoke else 10584):
        raise ValueError("entry input matrix did not complete")
    if object_hash != hashlib.sha256(object_path.read_bytes()).hexdigest():
        raise ValueError("staged object changed during audit")
    return {"schema": "th105-reimu-entry-native-v1", "target_sha256": target_hash,
            "body_sha256": BODY_SHA, "object_sha256": object_hash,
            "cases": count, "mismatch_count": mismatches, "target_exits": counts,
            "input_sha256": digest.hexdigest(), "examples": examples,
            "visited_instructions": [len(probe.visited) for probe in probes],
            "unicorn_version": unicorn.__version__,
            "unicorn_library_sha256": hashlib.sha256(Path(unicorn_api._uc._name).read_bytes()).hexdigest(),
            "python_version": sys.version.split()[0],
            "audit_source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            "build_provenance_verified": False,
            "scope": "entry phase only; actor prefix, first callback arguments, native handled RET, "
                     "control word and TOP; stops before callbacks/action dispatch; no helper-result hooks, "
                     "full-root, exception, original-source or exact-unit claim"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true")
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu entry audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    return 1 if result["mismatch_count"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
