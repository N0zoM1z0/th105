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
import itertools
import json
from pathlib import Path
import random
import struct
import sys
import tomllib

import pefile
from capstone.x86_const import X86_OP_IMM
from giant_owner_audit import decode, reachable_boundary_audit

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("cpu_policy_boundary_base", ROOT / "scripts/audit-cpu-boundary-paths.py")
boundary = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = boundary
spec.loader.exec_module(boundary)

HELPERS = {0x406540: "atan2_degrees", 0x4066B0: "mt19937_next_u32",
           0x4067D0: "selector_random_roll", 0x4399C0: "checked_sequence", 0x68A1A0: "ftol2_sse"}
RETURN = 0x710000
ROOTS = {
    "default": ("default-cpu-action-policy", "gpt-web-default-cpu-action-policy",
                boundary.ADDRESS, boundary.SIZE, boundary.BODY_SHA256, 0x5F47B0),
    "aya": ("aya-cpu-action-policy", "gpt-web-aya-cpu-action-policy", 0x6126E0, 16032,
            "7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09", 0x614F8A),
}


def selector_call_sites(code, address):
    sites = set()
    for instruction in decode(code, address):
        if (instruction.mnemonic == "call" and instruction.operands[0].type == X86_OP_IMM
                and instruction.operands[0].imm & 0xFFFFFFFF == 0x4067D0):
            if instruction.size != 5 or instruction.bytes[0] != 0xE8:
                raise ValueError("selector call is not an ordinary E8 REL32")
            sites.add(instruction.address)
    return sites


def selector_call_site(return_address, allowed):
    site = return_address - 5
    if site not in allowed:
        raise ValueError("selector return does not name a decoded root call boundary")
    return site


def pair_selector_sites(target, candidate):
    if len(target) != len(candidate):
        raise ValueError("selector callsite traces have different lengths")
    pairs = []
    for (first, argument), (second, actual_argument) in zip(target, candidate):
        if argument != actual_argument:
            raise ValueError("selector callsite traces have different arguments")
        pairs.append((first, second, argument))
    return pairs


def float_input(case, key):
    if key + "_bits" in case:
        return struct.pack("<I", int(case[key + "_bits"], 16))
    return struct.pack("<f", case[key])


def height_cases():
    base = dict(action=201, sequence=200, self_x=100.0, vx=0.0, vy=0.0,
                other_action=0, resource=1000, mode=1, facing=1, counter=100,
                policy=0, timer=10, refresh=1, seed=0)
    seeds = (0, 1, 2, 3, 7, 42, 5489, 0xFFFFFFFF)
    zero, hundred, nan = "00000000", "42c80000", "7fc00000"
    heights = (zero, hundred, nan)
    pairs = ((nan, zero), (nan, hundred), (hundred, nan), (nan, nan),
             (zero, hundred), (hundred, zero), (hundred, "43480000"))
    for (sy, oy), x, sequence, seed in itertools.product(pairs, (250.0, 300.0), (200, 212), seeds):
        yield dict(base, self_y_bits=sy, other_y_bits=oy,
                   other_x=x, sequence=sequence, seed=seed)
    for sy, oy, x, seed in itertools.product(heights, heights, (250.0, 300.0), seeds):
        # Peer action 100 bypasses common attacks; timer zero selects policy0.
        yield dict(base, self_y_bits=sy, other_y_bits=oy, other_x=x,
                   other_action=100, timer=0, seed=seed)


def counter_cases():
    base = dict(action=300, sequence=200, self_x=100.0, other_x=250.0,
                self_y=0.0, other_y=0.0, vx=0.0, vy=0.0, other_action=100,
                resource=1000, mode=3, facing=1, counter=90, policy=-1,
                timer=10, refresh=1, seed=0, control_6b4=1, control_6b8=-1)
    # These expected outputs are checked against native target execution first.
    # Policy -1 and peer action100 keep later policy writes from masking them.
    for action, counter, fields in (
            (300, 90, {"6b4": 0, "6b8": 0, "6bc": 2}),
            (305, 65, {"728": 2}), (320, 0, {"6b4": 0, "6b8": 0, "6bc": 2}),
            (404, 1, {"6b4": 1, "6b8": 0, "6c4": 2})):
        yield dict(base, action=action, counter=counter, expected_counter_fields=fields)
    seeds = (0, 1, 2, 3, 7, 42, 5489, 0xFFFFFFFF)
    boundaries = {
        300: (-32768, -1, 0, 1, 9, 10, 11, 89, 90, 91, 32767),
        305: (-32768, -1, 0, 1, 64, 65, 66, 74, 75, 76, 32767),
        320: (-32768, -1, 0, 1, 89, 90, 91, 32767),
        404: (-32768, -1, 0, 1, 9, 10, 11, 19, 20, 21, 29, 30, 31,
              39, 40, 41, 94, 95, 96, 99, 100, 101, 32767),
    }
    for action, counters in boundaries.items():
        for counter, mode, facing, seed in itertools.product(counters, range(4), (-1, 1), seeds):
            yield dict(base, action=action, counter=counter, mode=mode, facing=facing, seed=seed)
    for counter, resource, facing, seed in itertools.product(
            (64, 65, 75, 76), (-1, 399, 400, 401), (-1, 1), seeds[:4]):
        yield dict(base, action=305, counter=counter, resource=resource, facing=facing, seed=seed)
    geometry = ((499.0, 0.0, 0.0), (500.0, 0.0, 0.0), (150.0, 50.0, 0.0), (150.0, 150.0, 0.0))
    for counter, resource, (distance, sy, oy), facing, seed in itertools.product(
            (0, 10, 11, 20, 21, 30, 31, 40, 95, 100), (-1, 399, 400, 401), geometry, (-1, 1), seeds[:2]):
        yield dict(base, action=404, sequence=211, counter=counter, resource=resource,
                   other_x=100.0 + distance, self_y=sy, other_y=oy, facing=facing, seed=seed)


def aya_command_cases():
    bases = json.loads((ROOT / "tests/fixtures/aya-cpu-command-seeds.json").read_text())
    if len(bases) != 2 or {case["expected_aya_command"] for case in bases} != {0x200, 0x400}:
        raise ValueError("Aya command fixture omits a native positive control")
    yield from bases
    below, above = (struct.unpack("<f", struct.pack("<I", bits))[0] for bits in (0x43A07FFF, 0x43A08001))
    for base in bases:
        vector = {key: value for key, value in base.items() if key != "expected_aya_command"}
        direction = 1 if base["other_x"] > base["self_x"] else -1
        for distance, resource, seed in itertools.product(
                (319.0, 320.0, 320.5, below, 321.0, above, 600.0),
                (-1, 399, 400, 401, 1000), (0, 1, 2, 7, 42, 0xFFFFFFFF)):
            yield dict(vector, other_x=base["self_x"] + direction * distance, resource=resource, seed=seed)
        for bits, seed in itertools.product(
                ("7fc00000", "7f800001", "7f800000", "ff800000"), (0, 1, 2, 7, 42, 0xFFFFFFFF)):
            yield dict(vector, other_x_bits=bits, seed=seed)


def selection_cases():
    # These seeds are inputs, never substituted RNG results. The target must
    # independently confirm each predicted policy roll during native execution.
    seeds = json.loads((ROOT / "tests/fixtures/cpu-policy-selection-seeds.json").read_text())
    if (not isinstance(seeds, list) or len(seeds) != 101 or len(set(seeds)) != 101
            or any(type(seed) is not int or not 0 <= seed <= 0xFFFFFFFF for seed in seeds)):
        raise ValueError("selection fixture requires 101 distinct uint32 seeds")
    base = dict(action=201, sequence=200, vx=0.0, vy=0.0, other_action=100,
                resource=1000, mode=1, counter=100, policy=0, timer=0, refresh=1,
                control_6b4=1, control_6b8=-1)
    heights = ((0.0, 0.0), (0.0, 100.0), (0.0, 300.0), (0.0, 500.0),
               (100.0, 0.0), (300.0, 0.0), (100.0, 200.0), (300.0, 100.0),
               (100.0, 500.0), (500.0, 100.0))
    for (roll, seed), (x, facing), (sy, oy), distance in itertools.product(
            enumerate(seeds), ((100.0, 1), (100.0, -1), (1100.0, 1), (1100.0, -1)),
            heights, (90.0, 150.0, 300.0, 600.0)):
        yield dict(base, seed=seed, selection_roll=roll, self_x=x,
                   other_x=x + distance if x == 100.0 else x - distance,
                   self_y=sy, other_y=oy, facing=facing)


def selection_coverage(canonical, root, target, visited, *, address=boundary.ADDRESS, expected_entry=0x5F47B0):
    policy, = (region for region in root["regions"] if region["name"] == "policy")
    index = -int(policy["case_min"])
    if not 0 <= index <= int(policy["case_max"]) - int(policy["case_min"]):
        raise ValueError("policy table does not contain case0")
    slot = canonical.target_bytes(int(policy["index_table"], 0) + index, 1)[0]
    if slot >= int(policy["destination_count"]):
        raise ValueError("policy0 table slot exceeds the destination count")
    entry = int.from_bytes(canonical.target_bytes(int(policy["destination_table"], 0) + 4 * slot, 4), "little")
    if entry != expected_entry:
        raise ValueError("policy0 table entry differs from the reviewed target")
    code = target[entry - address:]
    cfg = reachable_boundary_audit(code, entry, {})
    if (cfg["unresolved_indirect_exits"] or cfg["internal_call_targets"]
            or any(t["address"] != 0x4067D0 or any(s["kind"] != "call" for s in t["sites"])
                   for t in cfg["direct_external_targets"])):
        raise ValueError("policy0 has an unreviewed transfer or dependency")
    reachable = {i.address for i in decode(code, entry)
                 if not any(start <= i.address < end for start, end in cfg["unreached_ranges"])}
    missing = sorted(reachable - visited)
    return {"entry": f"0x{entry:08X}", "reachable_target_instructions": len(reachable),
            "reachable_target_bytes": cfg["reachable_bytes"],
            "visited_target_instructions": len(reachable & visited),
            "missing_target_instruction_addresses": [f"0x{address:08X}" for address in missing],
            "scope": "instruction coverage of policy0 including shared return tails; branch and numerical completeness unproved"}


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
    def __init__(self, *args, address=boundary.ADDRESS, collect_selector_sites=False):
        super().__init__(*args, address=address)
        # Mapping permits the genuine RET to complete before emulation ends.
        self.engine.mem_map(RETURN, 0x1000)
        self.phase = "idle"
        self.seed_cache = {}
        self.helper_counts = Counter()
        self.root_end = self.address + args[2]
        self.visited_root = set()
        self.collect_selector_sites = collect_selector_sites
        self.allowed_selector_sites = selector_call_sites(args[1][:args[2]], address) if collect_selector_sites else set()
        self.selector_sites = []

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
        if address == self.address:
            if self.phase != "root":
                raise ValueError("unexpected CPU entry during RNG setup")
            c = self.case
            uc.mem_write(0x6FDEF0, self.seed_state[0])
            uc.mem_write(0x6FA1FC, self.seed_state[1])
            uc.mem_write(self.STACK + 0xFF00, struct.pack("<I", RETURN))
            for offset, key in ((0x6B4, "control_6b4"), (0x6B8, "control_6b8")):
                if key in c:
                    uc.mem_write(self.OWNER + offset, struct.pack("<i", c[key]))
            for offset, key, fmt in ((0xF0, "self_y", "<f"), (0xF4, "vx", "<f"), (0xF8, "vy", "<f"),
                                     (0x482, "resource", "<h"), (0x766, "policy", "<h"),
                                     (0x768, "timer", "<h"), (0x76C, "refresh", "<h")):
                uc.mem_write(self.OWNER + offset, float_input(c, key) if fmt == "<f" else struct.pack(fmt, c[key]))
            for offset, key, fmt in ((0xEC, "other_x", "<f"), (0xF0, "other_y", "<f"), (0x13C, "other_action", "<h")):
                uc.mem_write(self.OTHER + offset, float_input(c, key) if fmt == "<f" else struct.pack(fmt, c[key]))
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
        if self.address <= address < self.root_end:
            self.visited_root.add(address)
        if address in HELPERS:
            self.helper_counts[address] += 1
        esp = uc.reg_read(r.UC_X86_REG_ESP)
        if address == 0x4067D0:
            argument = struct.unpack("<I", uc.mem_read(esp + 4, 4))[0]
            self.calls.append(("rng", argument))
            if self.collect_selector_sites:
                returned = struct.unpack("<I", uc.mem_read(esp, 4))[0]
                self.selector_sites.append((selector_call_site(returned, self.allowed_selector_sites), argument))
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
        self.selector_sites = []
        self.case, self.phase = case, "root"
        bits = struct.unpack("<I", float_input(case, "self_x"))[0]
        result = self.run((case["action"], case["sequence"], bits, case["facing"],
                           case["mode"], case["counter"], 0x27F))
        uc, r = self.engine, self.reg
        if uc.reg_read(r.UC_X86_REG_EIP) != RETURN or result["stack_delta"] != 4:
            raise ValueError("CPU path did not complete its native no-argument RET")
        result["actor"] = bytes(uc.mem_read(self.OWNER, 0x7A4)).hex()
        result["rng_state"] = hashlib.sha256(bytes(uc.mem_read(0x6FDEF0, 2496)) + bytes(uc.mem_read(0x6FA1FC, 4))).hexdigest()
        result["x87_control_word"] = uc.reg_read(r.UC_X86_REG_FPCW)
        return result


def audit(object_path, count, selected_cases=None, check_selection=False, *, root_name="default"):
    import unicorn
    from unicorn import unicorn as unicorn_api
    canonical = boundary.load_script("cpu_policy_canonical", "compare-function.py")
    target_hash = canonical.verify_target()
    root_key, unit_key, address, size, body_hash, policy_entry = ROOTS[root_name]
    target = canonical.target_bytes(address, size)
    if hashlib.sha256(target).hexdigest() != body_hash:
        raise ValueError("CPU callable boundary/hash changed")
    mapper = boundary.load_script("cpu_policy_mapper", "compare-giant-action-switches.py")
    roots = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = mapper.load_target_mapper().select_root(roots, root_key)
    unit = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"][unit_key]
    function, = unit["functions"]
    obj = mapper.CoffObject(object_path)
    object_hash = hashlib.sha256(object_path.read_bytes()).hexdigest()
    symbols = [s for s in obj.symbols.values() if s.name == function["symbol_base"]]
    if len(symbols) != 1 or symbols[0].value != 0 or symbols[0].section_number != obj.text_section_number:
        raise ValueError("CPU root must start the selected COFF section")
    candidate_map = mapper.build_candidate_map(obj, root)
    rel32 = canonical.known_targets()
    rel32.update({k: int(v, 0) for k, v in (s.split("=", 1) for s in function["rel32_targets"])})
    dir32 = dict(s.split("=", 1) for s in function["dir32_targets"])
    candidate = canonical.coff_symbol_bytes(object_path, function["symbol_base"], address,
                                             len(obj.text), rel32, canonical.known_data_targets(), dir32)
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    engines = (NativeCpuProbe(image, target, size, address=address, collect_selector_sites=check_selection),
               NativeCpuProbe(image, candidate, candidate_map["metadata_start"], address=address,
                              collect_selector_sites=check_selection))
    mismatches, examples, digest, processed = 0, [], hashlib.sha256(), 0
    selection_rolls = [set(), set()]
    selector_pairs = Counter()
    vectors = cases(count) if selected_cases is None else selected_cases
    for number, case in enumerate(vectors, 1):
        digest.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = (engine.evaluate(case) for engine in engines)
        if "expected_counter_fields" in case:
            actor = bytes.fromhex(expected["actor"])
            for key, value in case["expected_counter_fields"].items():
                offset = int(key, 16)
                if (offset not in (0x6B4, 0x6B8, 0x6BC, 0x6C4, 0x728)
                        or int.from_bytes(actor[offset:offset + 4], "little", signed=True) != value):
                    raise ValueError("native target did not confirm a counter positive control")
        if "expected_aya_command" in case:
            command = int.from_bytes(bytes.fromhex(expected["actor"])[0x728:0x72C], "little")
            if root_name != "aya" or command != case["expected_aya_command"]:
                raise ValueError("native target did not confirm the Aya command seed fixture")
        if "selection_roll" in case:
            for side, result in enumerate((expected, actual)):
                calls = result["calls"]
                roll = next((calls[n + 3][1] for n, call in enumerate(calls[:-3])
                             if call == ("rng", 100) and calls[n + 3][0] == "rng_return"), None)
                if side == 0 and roll != case["selection_roll"]:
                    raise ValueError("native target did not confirm the selection seed fixture")
                if roll is not None:
                    selection_rolls[side].add(roll)
        processed += 1
        if expected != actual:
            mismatches += 1
            if len(examples) < 20:
                examples.append({"case": case, "target": expected, "candidate": actual})
        elif check_selection:
            selector_pairs.update(pair_selector_sites(engines[0].selector_sites, engines[1].selector_sites))
        if number % 1000 == 0:
            print(f"Complete CPU paths: {number}, differences {mismatches}", file=sys.stderr)
    library = Path(unicorn_api._uc._name)
    if processed != count:
        raise ValueError("CPU input generator did not complete the requested controls")
    coverage = [{HELPERS[a]: engine.helper_counts[a] for a in HELPERS} for engine in engines]
    if object_hash != hashlib.sha256(object_path.read_bytes()).hexdigest():
        raise ValueError("object changed during native CPU execution")
    result = {"schema": "th105-cpu-native-policy-paths-v1", "evidence": "sampled native execution; no exact credit",
            "root": root_key, "address": f"0x{address:08X}",
            "build_provenance_verified": False, "target_sha256": target_hash, "body_sha256": body_hash,
            "object_sha256": object_hash,
            "candidate_metadata_start": candidate_map["metadata_start"],
            "candidate_canonical_section_tail_sha256": hashlib.sha256(candidate).hexdigest(),
            "unicorn_version": unicorn.__version__, "unicorn_library_sha256": hashlib.sha256(library.read_bytes()).hexdigest(),
            "python_version": sys.version.split()[0], "input_sha256": digest.hexdigest(),
            "input_source": "built-in finite matrix" if selected_cases is None else "explicit cases",
            "cases": processed, "mismatch_count": mismatches, "examples": examples,
            "native_helper_coverage_target_candidate": coverage,
            "visited_root_instruction_addresses_target_candidate": [len(e.visited_root) for e in engines],
            "all_five_helpers_executed": all(all(c.values()) for c in coverage),
            "scope": "entry through native RET; entire7A4 actor prefix, RNG state, native call order/arguments/results, ftol2 x87 inputs, stack cleanup and control word; real seeded MT streams after one discarded draw; masked PC53; no helper-result hooks; complete numerical/gameplay/exception equivalence is unproved"}
    if check_selection:
        result["policy0_coverage"] = selection_coverage(
            canonical, root, target, engines[0].visited_root, address=address, expected_entry=policy_entry)
        result["observed_selection_rolls_target_candidate"] = [sorted(values) for values in selection_rolls]
        result["selection_coverage_complete"] = (not result["policy0_coverage"]["missing_target_instruction_addresses"]
                                                  and all(values == set(range(101)) for values in selection_rolls))
        result["selector_callsite_correspondence"] = {
            "static_root_sites_target_candidate": [len(engine.allowed_selector_sites) for engine in engines],
            "observed_sites_target_candidate": [len({pair[side] for pair in selector_pairs}) for side in (0, 1)],
            "observations": sum(selector_pairs.values()),
            "non_equivalent_cases_skipped": mismatches,
            "pairs": [{"target": f"0x{first:08X}", "candidate": f"0x{second:08X}",
                       "argument": argument, "observations": count}
                      for (first, second, argument), count in sorted(selector_pairs.items())],
            "scope": "decoded E8 caller sites paired by ordinal/argument only on full-output-equivalent sampled paths; no static bijection or canonical matching claim"}
    if root_name == "aya":
        result["aya_command_branch_coverage"] = []
        for start in (0x6142C0, 0x61447C):
            instructions = decode(canonical.target_bytes(start, 61), start)
            missing = [i.address for i in instructions if i.address not in engines[0].visited_root]
            result["aya_command_branch_coverage"].append({
                "entry": f"0x{start:08X}", "target_instructions": len(instructions),
                "missing_target_instruction_addresses": [f"0x{a:08X}" for a in missing]})
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--root", choices=tuple(ROOTS), default="default", help="target-pinned CPU root")
    inputs = parser.add_mutually_exclusive_group()
    inputs.add_argument("--cases", type=int)
    inputs.add_argument("--case-file", type=Path, help="nonempty JSON case array; <float field>_bits overrides its value")
    inputs.add_argument("--height-cases", action="store_true", help="368 finite/NaN height and RNG controls")
    inputs.add_argument("--counter-cases", action="store_true", help="4164 signed counter/mode/resource/geometry controls")
    inputs.add_argument("--aya-command-cases", action="store_true", help="470 Aya command/RNG/resource/truncation controls")
    inputs.add_argument("--selection-cases", action="store_true", help="16160 policy0 controls; require all target instructions and rolls0..100")
    args = parser.parse_args()
    if args.cases is not None and args.cases <= 0:
        parser.error("--cases must be positive")
    if args.aya_command_cases and args.root != "aya":
        parser.error("--aya-command-cases requires --root aya")
    try:
        selected = None
        if args.case_file:
            selected = json.loads(args.case_file.read_text())
            if not isinstance(selected, list) or not selected or not all(isinstance(c, dict) for c in selected):
                raise ValueError("case file must contain a nonempty array of input objects")
        elif args.height_cases:
            selected = list(height_cases())
        elif args.counter_cases:
            selected = list(counter_cases())
        elif args.aya_command_cases:
            selected = list(aya_command_cases())
        elif args.selection_cases:
            selected = list(selection_cases())
        count = len(selected) if selected is not None else (args.cases or 5000)
        result = audit(args.object, count, selected, check_selection=args.selection_cases, root_name=args.root)
        if args.selection_cases:
            result["input_source"] = "built-in policy0 selection matrix"
        if args.counter_cases:
            result["input_source"] = "built-in signed action-counter matrix with target-confirmed positive stores"
        if args.aya_command_cases:
            if count != 470 or any(block["missing_target_instruction_addresses"]
                                   for block in result["aya_command_branch_coverage"]):
                raise ValueError("Aya command controls did not complete native target instruction coverage")
            result["input_source"] = "built-in Aya command matrix with target-confirmed positive seeds"
    except Exception as error:
        parser.exit(2, f"CPU native execution failed: {error}\n")
    print(json.dumps(result, indent=2))
    return int(bool(result["mismatch_count"]) or (args.selection_cases and not result["selection_coverage_complete"]))


if __name__ == "__main__":
    raise SystemExit(main())
