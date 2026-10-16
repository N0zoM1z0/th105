#!/usr/bin/env python3
"""Execute complete CPU decision paths with the original native dependencies.

Diagnostic only: sampled actor/RNG/call equivalence is not canonical equality.
The PE supplies all code, including RNG, checked sequence access, atan2 and
float conversion. Only actor, sequence-container and seeded RNG input data are
initialized; no helper call is replaced with a hook result.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import random
import struct
import sys
import tomllib

import pefile

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("cpu_policy_boundary_base", ROOT / "scripts/audit-cpu-boundary-paths.py")
boundary = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = boundary
spec.loader.exec_module(boundary)

HELPERS = {0x406540: "atan2_degrees", 0x4066B0: "mt19937_next_u32",
           0x4067D0: "selector_random_roll", 0x4399C0: "checked_sequence", 0x68A1A0: "ftol2_sse"}
RETURN = 0x710000


def cases(count):
    rng = random.Random(105106)
    for _ in range(count):
        yield {
            "action": rng.choice((0, 50, 149, 150, 200, 201, 300, 301, 302, 303, 304, 305,
                                  306, 307, 308, 320, 321, 322, 400, 401, 402, 404, 405, 406,
                                  410, 412, 414, 415, 416, 999)),
            "sequence": rng.choice((200, 201, 202, 205, 211, 212)),
            "self_x": rng.choice((100.0, 600.0, 1000.0)),
            "other_x": rng.choice((0.0, 150.0, 300.0, 450.0, 500.0, 700.0, 1280.0)),
            "self_y": rng.choice((0.0, 30.0, 100.0, 300.0)),
            "other_y": rng.choice((0.0, 30.0, 100.0, 300.0)),
            "vx": rng.choice((-3.0, 0.0, 3.0)), "vy": rng.choice((-3.0, 0.0, 3.0)),
            "other_action": rng.choice((0, 50, 95, 96, 100, 139, 140, 200)),
            "resource": rng.choice((0, 399, 400, 599, 600, 799, 800, 1000)),
            "mode": rng.choice((0, 1, 2, 3)), "facing": rng.choice((-1, 1)),
            "counter": rng.choice((-32768, -1, 0, 10, 20, 30, 40, 50, 65, 75, 85, 90, 95, 100, 101, 32767)),
            "policy": rng.choice((0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                                  12, 13, 14, 15, 16, 17, 18, 19, 100, -1)),
            "timer": rng.choice((-32768, -1, 0, 1, 10, 32767)),
            "refresh": rng.choice((0, 1, 99)),
            "seed": rng.choice((0, 1, 2, 3, 7, 42, 5489, 0xFFFFFFFF)),
        }


class NativeCpuProbe(boundary.CpuProbe):
    def __init__(self, *args):
        super().__init__(*args)
        # Mapping permits the genuine RET to complete before emulation ends.
        self.engine.mem_map(RETURN, 0x1000)
        self.phase = "idle"
        self.seed_cache = {}
        self.helper_counts = Counter()
        self.root_end = boundary.ADDRESS + args[2]
        self.visited_root = set()

    def write(self, uc, access, address, size, value, unused):
        if (0x6FDEF0 <= address and address + size <= 0x6FE8B0) or (0x6FA1FC <= address and address + size <= 0x6FA200):
            return
        super().write(uc, access, address, size, value, unused)

    def fp80(self, uc):
        top = (uc.reg_read(self.reg.UC_X86_REG_FPSW) >> 11) & 7
        value = uc.reg_read(self.reg.UC_X86_REG_FP0 + top)
        if not isinstance(value, tuple) or len(value) != 2:
            raise ValueError("emulator does not expose the x87 input value")
        return value

    def step(self, uc, address):
        r = self.reg
        if address == boundary.ADDRESS:
            if self.phase != "root":
                raise ValueError("unexpected CPU entry during RNG setup")
            c = self.case
            uc.mem_write(0x6FDEF0, self.seed_state[0])
            uc.mem_write(0x6FA1FC, self.seed_state[1])
            uc.mem_write(self.STACK + 0xFF00, struct.pack("<I", RETURN))
            for offset, key, fmt in ((0xF0, "self_y", "<f"), (0xF4, "vx", "<f"), (0xF8, "vy", "<f"),
                                     (0x482, "resource", "<h"), (0x766, "policy", "<h"),
                                     (0x768, "timer", "<h"), (0x76C, "refresh", "<h")):
                uc.mem_write(self.OWNER + offset, struct.pack(fmt, c[key]))
            for offset, key, fmt in ((0xEC, "other_x", "<f"), (0xF0, "other_y", "<f"), (0x13C, "other_action", "<h")):
                uc.mem_write(self.OTHER + offset, struct.pack(fmt, c[key]))
            # Native ring: eight pointer slots, head0, one live 0x98-byte record.
            uc.mem_write(self.OWNER + 0x55C, struct.pack("<5I", 0, self.RECORD + 0x1000, 8, 0, 1))
            uc.mem_write(self.RECORD + 0x1000, struct.pack("<I", self.RECORD))
        if address == RETURN:
            self.stopped = True
            uc.emu_stop()
            return
        if bytes(uc.mem_read(address, 1)) == b"\xc3":
            esp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(esp, 4))[0] == RETURN:
                self.stopped = True
        if self.phase != "root":
            return
        if boundary.ADDRESS <= address < self.root_end:
            self.visited_root.add(address)
        if address in HELPERS:
            self.helper_counts[address] += 1
        esp = uc.reg_read(r.UC_X86_REG_ESP)
        if address == 0x4067D0:
            self.calls.append(("rng", struct.unpack("<I", uc.mem_read(esp + 4, 4))[0]))
        elif address == 0x4067EA:
            self.calls.append(("rng_return", uc.reg_read(r.UC_X86_REG_EAX)))
        elif address == 0x4066B0:
            self.calls.append(("mt",))
        elif address == 0x4067C6:
            self.calls.append(("mt_return", uc.reg_read(r.UC_X86_REG_EAX)))
        elif address == 0x4399C0:
            receiver = uc.reg_read(r.UC_X86_REG_ECX)
            index = struct.unpack("<I", uc.mem_read(esp + 4, 4))[0]
            if receiver != self.OWNER + 0x55C or index != 0:
                raise ValueError("unexpected native checked-sequence access")
            self.calls.append(("sequence", receiver - self.OWNER, index))
        elif address == 0x406540:
            self.calls.append(("atan2", bytes(uc.mem_read(esp + 4, 8)).hex()))
        elif address == 0x40657E:
            self.calls.append(("atan2_return", self.fp80(uc)))
        elif address == 0x68A1A0:
            self.calls.append(("ftol2", self.fp80(uc)))

    def seed(self, seed):
        if seed in self.seed_cache:
            return self.seed_cache[seed]
        uc, r = self.engine, self.reg
        # Run the original seed and next functions, discarding the first draw.
        for phase, entry in (("seed", 0x406670), ("warm", 0x4066B0)):
            self.phase, self.stopped, self.failure = phase, False, None
            uc.context_restore(self.initial)
            uc.mem_write(self.STACK + 0xFF00, struct.pack("<II", RETURN, seed))
            uc.reg_write(r.UC_X86_REG_ESP, self.STACK + 0xFF00)
            uc.emu_start(entry, RETURN, count=100000)
            if self.failure or not self.stopped or uc.reg_read(r.UC_X86_REG_EIP) != RETURN:
                raise ValueError(f"native RNG setup failed: {self.failure}")
        self.seed_cache[seed] = (bytes(uc.mem_read(0x6FDEF0, 2496)), bytes(uc.mem_read(0x6FA1FC, 4)))
        return self.seed_cache[seed]

    def evaluate(self, case):
        self.seed_state = self.seed(case["seed"])
        self.case, self.phase = case, "root"
        bits = (int(case["self_x_bits"], 16) if "self_x_bits" in case
                else struct.unpack("<I", struct.pack("<f", case["self_x"]))[0])
        result = self.run((case["action"], case["sequence"], bits, case["facing"],
                           case["mode"], case["counter"], 0x27F))
        uc, r = self.engine, self.reg
        if uc.reg_read(r.UC_X86_REG_EIP) != RETURN or result["stack_delta"] != 4:
            raise ValueError("CPU path did not complete its native no-argument RET")
        result["actor"] = bytes(uc.mem_read(self.OWNER, 0x7A4)).hex()
        result["rng_state"] = hashlib.sha256(bytes(uc.mem_read(0x6FDEF0, 2496)) + bytes(uc.mem_read(0x6FA1FC, 4))).hexdigest()
        result["x87_control_word"] = uc.reg_read(r.UC_X86_REG_FPCW)
        return result


def audit(object_path, count, selected_cases=None):
    import unicorn
    from unicorn import unicorn as unicorn_api
    canonical = boundary.load_script("cpu_policy_canonical", "compare-function.py")
    target_hash = canonical.verify_target()
    target = canonical.target_bytes(boundary.ADDRESS, boundary.SIZE)
    if hashlib.sha256(target).hexdigest() != boundary.BODY_SHA256:
        raise ValueError("CPU callable boundary/hash changed")
    mapper = boundary.load_script("cpu_policy_mapper", "compare-giant-action-switches.py")
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
    candidate = canonical.coff_symbol_bytes(object_path, function["symbol_base"], boundary.ADDRESS,
                                             len(obj.text), rel32, canonical.known_data_targets(), dir32)
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    engines = (NativeCpuProbe(image, target, boundary.SIZE),
               NativeCpuProbe(image, candidate, candidate_map["metadata_start"]))
    mismatches, examples, digest, processed = 0, [], hashlib.sha256(), 0
    vectors = cases(count) if selected_cases is None else selected_cases
    for number, case in enumerate(vectors, 1):
        digest.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = (engine.evaluate(case) for engine in engines)
        processed += 1
        if expected != actual:
            mismatches += 1
            if len(examples) < 20:
                examples.append({"case": case, "target": expected, "candidate": actual})
        if number % 1000 == 0:
            print(f"Complete CPU paths: {number}, differences {mismatches}", file=sys.stderr)
    library = Path(unicorn_api._uc._name)
    if processed != count:
        raise ValueError("CPU input generator did not complete the requested controls")
    coverage = [{HELPERS[a]: engine.helper_counts[a] for a in HELPERS} for engine in engines]
    return {"schema": "th105-cpu-native-policy-paths-v1", "evidence": "sampled native execution; no exact credit",
            "build_provenance_verified": False, "target_sha256": target_hash, "body_sha256": boundary.BODY_SHA256,
            "object_sha256": hashlib.sha256(object_path.read_bytes()).hexdigest(),
            "unicorn_version": unicorn.__version__, "unicorn_library_sha256": hashlib.sha256(library.read_bytes()).hexdigest(),
            "python_version": sys.version.split()[0], "input_sha256": digest.hexdigest(),
            "input_source": "built-in finite matrix" if selected_cases is None else "explicit cases",
            "cases": processed, "mismatch_count": mismatches, "examples": examples,
            "native_helper_coverage_target_candidate": coverage,
            "visited_root_instruction_addresses_target_candidate": [len(e.visited_root) for e in engines],
            "all_five_helpers_executed": all(all(c.values()) for c in coverage),
            "scope": "entry through native RET; entire7A4 actor prefix, RNG state, native call order/arguments/results, ftol2 x87 inputs, stack cleanup and control word; real seeded MT streams after one discarded draw; masked PC53; no helper-result hooks; complete numerical/gameplay/exception equivalence is unproved"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    inputs = parser.add_mutually_exclusive_group()
    inputs.add_argument("--cases", type=int)
    inputs.add_argument("--case-file", type=Path, help="nonempty JSON case array; self_x_bits overrides self_x")
    args = parser.parse_args()
    if args.cases is not None and args.cases <= 0:
        parser.error("--cases must be positive")
    try:
        selected = None
        if args.case_file:
            selected = json.loads(args.case_file.read_text())
            if not isinstance(selected, list) or not selected or not all(isinstance(c, dict) for c in selected):
                raise ValueError("case file must contain a nonempty array of input objects")
        count = len(selected) if selected is not None else (args.cases or 5000)
        result = audit(args.object, count, selected)
    except Exception as error:
        parser.exit(2, f"CPU native execution failed: {error}\n")
    print(json.dumps(result, indent=2))
    return int(bool(result["mismatch_count"]))


if __name__ == "__main__":
    raise SystemExit(main())
