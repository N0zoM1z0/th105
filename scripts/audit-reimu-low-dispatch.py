#!/usr/bin/env python3
"""Native comparison of the integrated Reimu entry/low source path.

The phase is not an original function boundary. Executes original helpers,
original angle-table initialization and MT19937; stops at real world requests.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import itertools
import json
from pathlib import Path
import struct
import sys
import tomllib

import pefile
import unicorn
from unicorn import unicorn as unicorn_api
from unicorn import x86_const as r

import linked_pe
from reimu_staging_extent import staging_execution_extent
from reimu_return_contract import pending_from_return, validate_return_symbol
from reimu_late_low_fixture import resource_graph, native_orientation_table

ROOT = Path(__file__).resolve().parents[1]


def load_script(name, filename):
    import importlib.util
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


late = load_script("reimu_dispatch_late_contract", "audit-reimu-late-low-actions.py")
ADDRESS, SIZE, BODY_SHA = late.ADDRESS, late.SIZE, late.BODY_SHA
OWNER, STACK, RETURN = late.OWNER, late.STACK, late.RETURN
VTABLE = late.VTABLE
RESOURCE, TREE, VECTOR = late.RESOURCE, late.TREE, late.VECTOR
WORLD = late.WORLD
SYMBOL = "?run_checked_low_dispatch@ReimuActionStatePreludeView@th105@@QAE_NXZ"
ACTIONS = (*range(11), *range(71, 79), 88, 89, 145, *range(197, 205),
           208, 209, 210, 211, 212, 214, 215, 220, 221, 222, 223, 224, 225, 226, 300)
KEYS = tuple(sorted(set(ACTIONS) | {97, 669, 700}))
HELPERS = {**late.HELPERS, 0x4740C0: (10219, "common_action_entry")}
CALL_TARGETS = {**late.CALL_TARGETS, "update_common_action_state": 0x4740C0}
MID = 0x47CC5F


def cases(smoke=False):
    base = {**next(late.cases(True)), "action": 0, "y": 0.0,
            "sequence": 0, "effect": 1, "entry_timer": 0, "entry_count": 0,
            "entry_latch": 0, "entry_gate": 0, "peer_gate": 0,
            "self_word": 1, "peer_word": 1, "initial_words": (-19, -23)}
    if smoke:
        for action in (*ACTIONS, -32768, -1, 11, 149, 227, 299, 301, 560, 798, 32767):
            yield {**base, "cohort": "smoke", "action": action}
        for change in ({"entry_gate": 1}, {"peer_gate": 1},
                       {"entry_timer": 1, "entry_count": 6, "state": 1},
                       {"action": 150, "effect": 0, "facing": -1}):
            yield {**base, "cohort": "smoke", **change}
        return
    for action, change, cw in itertools.product(ACTIONS, (
            {}, {"y": 100.0, "sequence": 1},
            {"y": 0.0, "vy": 0xC0400000, "sequence": 1},
            {"counter": -1, "timer": -1, "sequence": 1},
            {"counter": 5, "sequence": 2},
            {"single_sequence": True, "transition": "terminal"}), (0x27F, 0x37F)):
        yield {**base, "cohort": "bodies", "action": action, "control_word": cw, **change}
    defaults = [a for a in (-32768, -32767, -1, *range(301)) if a not in ACTIONS]
    for action, flag, cw in itertools.product(defaults, (0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "default", "action": action, "flag": flag, "control_word": cw}
    for action, flag, cw in itertools.product((-32768, -1, 11, 42, 149, 227, 299),
                                               (0, 1), (0x27F, 0x37F)):
        yield {**base, "cohort": "common_return", "action": action, "flag": flag,
               "control_word": cw, "execute_common": True}
    for action, gate, peer_gate, timer, count, latch, state, words in itertools.product(
            (0, 10, 71, 300, 301), (0, 1), (0, 1), (-1, 1), (6, 32767),
            (0, 1), (0, 1, 7), ((1, 1), (0, 1), (1, 0))):
        yield {**base, "cohort": "entry", "action": action, "entry_gate": gate,
               "peer_gate": peer_gate, "entry_timer": timer, "entry_count": count,
               "entry_latch": latch, "state": state, "self_word": words[0], "peer_word": words[1]}
    for action, facing, cw in itertools.product((150, 153, 154, 157, 158),
                                               (-128, -1, 0, 1, 127), (0x27F, 0x37F)):
        yield {**base, "cohort": "entry_spawn", "action": action, "effect": 0,
               "facing": facing, "control_word": cw}
    for action, gate, peer_gate in itertools.product(
            (301, 551, 560, 561, 798, 799, 32767), (0, 1), (0, 1)):
        yield {**base, "cohort": "handoff", "action": action,
               "entry_gate": gate, "peer_gate": peer_gate}


class Probe(late.Probe):
    candidate_return_kind = "bool"
    helpers = HELPERS
    resource_keys = KEYS
    resource_size = 0x100000
    handled_action_max = 300
    frame_capacity = 6
    sequence_capacity = 7

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if (not self.candidate and address == MID
                and uc.reg_read(r.UC_X86_REG_EAX) > self.handled_action_max):
            self.pending_handoff = True
            uc.emu_stop()
        if address == 0x4740C0 and not self.execute_common:
            self.spawn_request = (address,)
            uc.emu_stop()
        if address == 0x45BFE0:
            argument = struct.unpack("<I", uc.mem_read(uc.reg_read(r.UC_X86_REG_ESP)+4, 4))[0]
            if argument == 669:
                self.spawn_request = (address, argument)
                uc.emu_stop()

    def prepare_extra_case(self, case):
        super().prepare_extra_case(case)
        self.execute_common = case.get("execute_common", False)

    def extra_actor_fields(self, case):
        return (*super().extra_actor_fields(case),
                (0x174, "h", case["self_word"]), (0x2174, "h", case["peer_word"]),
                (0x186, "h", case["entry_gate"]), (0x248C, "h", case["peer_gate"]),
                (0x751, "B", case["effect"]), (0x7C8, "h", case["entry_timer"]),
                (0x7CA, "h", case["entry_count"]), (0x7CC, "h", case["entry_latch"]),
                (0x7A0, "h", case["initial_words"][0]), (0x7A2, "h", case["initial_words"][1]))

    def evaluate(self, case):
        uc = self.engine
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes(0x10000))
        uc.mem_write(STACK+0xC000, bytes(0x4000))
        uc.mem_write(WORLD, bytes.fromhex("0000803f"))
        graph, blocks, frames, frame_count = resource_graph(case, tuple(sorted(set(self.resource_keys) | {case["action"]})),
                                                          frame_capacity=self.frame_capacity,
                                                          sequence_capacity=self.sequence_capacity)
        uc.mem_write(RESOURCE, graph)
        self.prepare_extra_case(case)
        action, sequence = case["action"], case["sequence"]
        index = sequence if 0 <= sequence < self.sequence_capacity else 0
        stride = (self.frame_capacity*0x88+0x3ff) & ~0x3ff
        block, frame = blocks[action]+index*0x20, frames[action]+index*stride
        timer = case["timer"] if case["timer"] is not None else 0 if case["transition"] == "unexpired" else case["duration"]-1
        fields = ((0, "I", VTABLE), (0xEC, "f", case["x"]), (0xF0, "f", case["y"]),
                  (0xF4, "I", case["vx"]), (0xF8, "I", case["vy"]), (0xFC, "f", 0.2),
                  (0x100, "I", case["ay"]), (0x104, "b", case["facing"]),
                  (0x12C, "I", case["angle"]), (0x130, "I", VECTOR),
                  (0x13C, "h", action), (0x13E, "h", sequence), (0x140, "h", case["frame"]),
                  (0x142, "h", timer), (0x144, "i", case["counter"]), (0x148, "h", frame_count),
                  (0x14C, "h", case["limit"] if case["limit"] is not None else case["duration"]),
                  (0x150, "I", frame), (0x158, "I", frame+case["frame"]*0x88),
                  (0x15C, "I", block), (0x160, "I", TREE), (0x170, "I", OWNER+0x2000),
                  (0x174, "h", 1), (0x47E, "B", case["flag"]), (0x490, "B", case["coupled"]),
                  (0x6AC, "I", 0x42C60000), (0x6B8, "i", case["field"]),
                  (0x730, "h", case["counter730"]), (0x732, "h", -77),
                  (0x7A2, "h", 85), (0x7A4, "h", case["spawn"]))
        for offset, fmt, value in (*fields, *self.extra_actor_fields(case)):
            uc.mem_write(OWNER+offset, struct.pack("<"+fmt, value))
        saved = {r.UC_X86_REG_EBX: 0x11111111, r.UC_X86_REG_ESI: 0x22222222,
                 r.UC_X86_REG_EDI: 0x33333333, r.UC_X86_REG_EBP: 0x44444444}
        for register, value in saved.items():
            uc.reg_write(register, value)
        sp = STACK+0xFF00
        uc.mem_write(sp, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case["control_word"])
        self.failure, self.calls, self.saw_ret, self.spawn_request = None, [], False, None
        self.pending_handoff = False
        try:
            uc.emu_start(ADDRESS, RETURN, count=100000)
        except unicorn.UcError as error:
            raise ValueError(f"{case}: {error} at {uc.reg_read(r.UC_X86_REG_EIP):#x}") from error
        if self.failure:
            raise ValueError(f"{case}: {self.failure}")
        if self.spawn_request is None and not self.pending_handoff:
            if (not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                    or uc.reg_read(r.UC_X86_REG_ESP) != sp+4
                    or any(uc.reg_read(reg) != value for reg, value in saved.items())):
                raise ValueError(f"recovery action did not restore RET ABI: {case}")
            if self.candidate:
                self.pending_handoff = pending_from_return(
                    uc.reg_read(r.UC_X86_REG_EAX), self.candidate_return_kind)
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("recovery action leaves live x87 values")
        return {"actor": bytes(uc.mem_read(OWNER, 0x1000)), "calls": self.calls,
                "control_word": uc.reg_read(r.UC_X86_REG_FPCW),
                "world": bytes(uc.mem_read(WORLD, 4)), "spawn_request": self.spawn_request,
                "endpoint": "request" if self.spawn_request else "pending" if self.pending_handoff else "ret",
                **self.extra_result()}


def check_target_case(case, result, sites):
    if case["cohort"] == "default" and result["spawn_request"] != (0x4740C0,):
        raise ValueError("default fixture bypassed the actual common action entry")
    if case["cohort"] == "common_return":
        if result["endpoint"] != "ret" or not any(call[0] == 0x4740C0 for call in result["calls"]):
            raise ValueError("common-return fixture did not reach its native RET")
    if case["cohort"] == "handoff":
        expected = "ret" if case["entry_gate"] or case["peer_gate"] else "pending"
        if result["endpoint"] != expected:
            raise ValueError("entry gates/high-action handoff did not reach its advertised endpoint")
    if case["cohort"] == "entry_spawn" and result["spawn_request"][:2] != (0x465190, 998):
        raise ValueError("entry fixture bypassed the real object998 request")


def audit(object_path, smoke=False, selected_cohorts=None, *, contract=None):
    contract = contract or sys.modules[__name__]
    SYMBOL, Probe, cases = contract.SYMBOL, contract.Probe, contract.cases
    return_kind = getattr(Probe, "candidate_return_kind", "bool")
    validate_return_symbol(SYMBOL, return_kind)
    HELPERS, CALL_TARGETS = contract.HELPERS, contract.CALL_TARGETS
    COHORT_COUNTS = contract.COHORT_COUNTS
    check_target_case = contract.check_target_case
    support_paths = [Path(__file__), ROOT / "scripts/reimu_late_low_fixture.py",
                     ROOT / "scripts/audit-reimu-movement-attack-actions.py",
                     ROOT / "scripts/audit-reimu-late-low-actions.py",
                     ROOT / "scripts/audit-reimu-recovery-actions.py",
                     ROOT / "scripts/audit-reimu-low-actions.py",
                     ROOT / "scripts/reimu_animation_fixture.py",
                     ROOT / "scripts/audit-common-fighter-animation-paths.py"]
    support_paths.extend((ROOT / "scripts/reimu_staging_extent.py",
                          ROOT / "scripts/reimu_return_contract.py", Path(contract.__file__)))
    allow_metadata = getattr(contract, "ALLOW_SWITCH_METADATA", False)
    if allow_metadata:
        support_paths.extend(ROOT / name for name in (
            "config/giant-action-switches.toml", "config/functions.csv",
            "scripts/compare-giant-action-switches.py", "scripts/map-giant-action-switches.py"))
    support_paths.extend(getattr(contract, "SUPPORT_PATHS", ()))
    support_hashes = {str(path.relative_to(ROOT)): linked_pe.sha(path) for path in support_paths}
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError("Reimu root boundary/hash changed")
    mapper = load_script("reimu_dispatch_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(object_path, symbol_base=SYMBOL)
    rel32 = {symbol.name: address for symbol in obj.symbols.values()
             for name, address in CALL_TARGETS.items() if symbol.name.startswith("?"+name+"@")}
    rel32["__ftol2_sse"] = 0x68A1A0
    known = dict(canonical.known_data_targets())
    bindings = {'405e000000000000': 7093872, '405b800000000000': 7093880, '3ee66666': 7093888, 'c1200000': 7093024, 'c1600000': 7093892, '4000000000000000': 7086528, '3fe0000000000000': 7131448, '4054000000000000': 7080016, '40f00000': 7093844, '3fe8000000000000': 7082656, '4059000000000000': 7131536, '4066800000000000': 7171760, '41200000': 7171820, '3fd3333340000000': 7088752, '442a0000': 7093848, '3ff0000000000000': 7131488, '4008000000000000': 7093112, '3f266666': 7093860, '41a00000': 7093864, '41700000': 7093920, '418c0000': 7093856, '41000000': 7088244, 'c1000000': 7131696, '41100000': 7093852, '40400000': 7171800, '40800000': 7131648, '4f800000': 7171832, '4049000000000000': 7093256, 'c1a00000': 7093368}
    bindings.update({'4057800000000000': 7093936, '404e000000000000': 7084168, '40900000': 7093928, 'c0900000': 7093924, '41700000': 7093920, '3f0ccccd': 7093916, 'c0800000': 7093912, '3f19999a': 7093908, '3f000000': 7131456, 'c0a00000': 7093080, 'c0400000': 7093084, 'c000000000000000': 7131632, '4004000000000000': 7091104, '40a00000': 7093104, '403e000000000000': 7081728, 'c02e000000000000': 7093088, 'c039000000000000': 7093096, '40000000': 7082992, '3eb33333': 7093904, 'c1480000': 7093900, '41480000': 7093320, '42aa0000': 7094276, '3e800000': 7091264, '3f647ae140000000': 7093072, '4044000000000000': 7082960})
    bindings["41780000"] = 0x6C3E88
    bindings.update(getattr(contract, "LITERAL_BINDINGS", {}))
    for bits, address in bindings.items():
        literal = bytes.fromhex(bits)[::-1]
        if canonical.target_bytes(address, len(literal)) != literal:
            raise ValueError(f"target numeric binding changed: {address:#x}")
        known.setdefault("__real@"+bits, (address, literal, frozenset({0}), "literal"))
    object_sha = linked_pe.sha(object_path)
    candidate = canonical.coff_symbol_bytes(object_path, SYMBOL, ADDRESS, len(obj.text), rel32, known, {})
    metadata_start = None
    if len(candidate) > SIZE and allow_metadata:
        manifest = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
        target_mapper = mapper.load_target_mapper()
        root = target_mapper.select_root(manifest, "reimu-vslot28")
        if (int(root["address"], 0) != ADDRESS or int(root["callable_end"], 0) != ADDRESS+SIZE
                or int(root["metadata_end"], 0) != 0x48D38C):
            raise ValueError("reviewed Reimu callable/metadata extent changed")
        target_mapper.map_root(target_mapper.PeImage(ROOT / "resources/th105.exe"),
                               target_mapper.load_function_rows(ROOT / "config/functions.csv"), root)
        metadata_start = mapper.build_candidate_map(obj, root)["metadata_start"]
    execution_extent = staging_execution_extent(
        len(candidate), SIZE, allow_switch_metadata=allow_metadata,
        metadata_start=metadata_start, metadata_limit=0x48D38C-ADDRESS)
    if any(ADDRESS < start+length and start < ADDRESS+len(candidate)
           for start, (length, _) in HELPERS.items()):
        raise ValueError("candidate staging body overlaps a real helper")
    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    if (image[0x2FA898:0x2FBC98] != bytes(0x1400)
            or canonical.target_bytes(0x6FCA98, 0x200) != bytes(0x200)
            or canonical.target_bytes(0x6FA880, 4) == struct.pack("<I", 16)):
        raise ValueError("fixture needs original flat surface/inactive event context")
    tables = {cw: native_orientation_table(image, cw) for cw in (0x27F, 0x37F)}
    probes = [Probe(image, target, False, tables), Probe(image, candidate, True, tables)]
    probes[1].end = ADDRESS+execution_extent
    count = mismatches = 0
    digest, cohorts, stops, examples = hashlib.sha256(), Counter(), Counter(), []
    for case in cases(smoke):
        if selected_cohorts and case["cohort"] not in selected_cohorts:
            continue
        expected, actual = (probe.evaluate(case) for probe in probes)
        check_target_case(case, expected, probes[0].case_sites)
        count += 1
        cohorts[case["cohort"]] += 1
        stops[hex(expected["spawn_request"][0]) if expected["spawn_request"] else expected["endpoint"]] += 1
        digest.update(json.dumps(case, sort_keys=True).encode())
        if expected != actual:
            mismatches += 1
            if len(examples) < 6:
                examples.append({"case": case, "different_actor_offsets": [hex(i) for i, (a, b) in
                                 enumerate(zip(expected["actor"], actual["actor"])) if a != b],
                                 "target_calls": expected["calls"], "candidate_calls": actual["calls"],
                                 "target_request": expected["spawn_request"], "candidate_request": actual["spawn_request"],
                                 "target_endpoint": expected["endpoint"], "candidate_endpoint": actual["endpoint"]})
        if count % 1000 == 0:
            print(f"Reimu low dispatch: {count}, differences {mismatches}", file=sys.stderr)
    expected_count = sum(COHORT_COUNTS[name] for name in set(selected_cohorts)) if selected_cohorts else getattr(contract, "SMOKE_COUNT", 59) if smoke else sum(COHORT_COUNTS.values())
    if (count != expected_count or linked_pe.sha(object_path) != object_sha
            or any(linked_pe.sha(ROOT / path) != digest for path, digest in support_hashes.items())):
        raise ValueError("input matrix incomplete or an input changed during execution")
    return {"schema": getattr(contract, "SCHEMA", "th105-reimu-low-dispatch-native-v1"), "target_sha256": target_sha,
            "body_sha256": BODY_SHA, "object_sha256": object_sha, "cases": count,
            "mismatch_count": mismatches, "cohorts": dict(cohorts), "stops": dict(stops),
            "selected_cohorts": selected_cohorts, "input_sha256": digest.hexdigest(), "examples": examples,
            "visited_root_instructions": [len(probe.visited) for probe in probes],
            "helper_counts": [{HELPERS[address][1]: probe.helper_counts[address]
                              for address in HELPERS} for probe in probes],
            "helper_sha256": {hex(address): hashlib.sha256(canonical.target_bytes(address, length)).hexdigest()
                              for address, (length, _) in HELPERS.items()},
            "orientation_initialization": [tables[cw][1] for cw in sorted(tables)],
            "unicorn_version": unicorn.__version__, "python_version": sys.version.split()[0],
            "unicorn_library_sha256": linked_pe.sha(Path(unicorn_api._uc._name)),
            "build_provenance_verified": False, "support_sha256": support_hashes,
            "candidate_execution_extent": execution_extent,
            "candidate_return_kind": return_kind,
            "candidate_text_bytes": len(candidate), "candidate_metadata_start": metadata_start,
            "scope": getattr(contract, "SCOPE", "integrated entry and low source; common/669/world stops compare real call entry; "
                     "upper pending compares state at original mid selector; supplied flat/zero-handle context, "
                     "MT and helpers; RET or complete real world request; no returning request, "
                     "whole-game, floating-exception, full-root source or canonical-exact claim")}


COHORT_COUNTS = {"bodies": 540, "default": 1036, "entry": 1440, "common_return": 28,
                 "entry_spawn": 50, "handoff": 28}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--smoke", action="store_true")
    selection.add_argument("--cohort", action="append", choices=tuple(COHORT_COUNTS))
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke, args.cohort)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu low-dispatch audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
