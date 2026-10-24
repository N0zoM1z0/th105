#!/usr/bin/env python3
"""Check specific Alice CPU path ambiguities with genuine native helpers.

Diagnostic only: actor/RNG/call equivalence on these inputs is not exactness.
The complete callable and all emitted tables have a separate canonical audit.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_MEM
import pefile
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS = 0x004F4B80
CALLABLE_SIZE = 16354
PAYLOAD_SIZE = 17009


def cases():
    base = dict(action=201, sequence=205, self_x=100., other_x=350.,
                self_y=0., other_y=0., vx=0., vy=0., other_action=100,
                resource=1000, mode=3, facing=1, counter=100, policy=-1,
                timer=10, refresh=1, seed=0, control_6b4=-7, control_6b8=5)
    # Specific timer, command-width and sequence-sharing ambiguities.
    actions = ((301,45,200), (302,80,200), (304,65,203), (305,95,202),
               (306,5,200), (306,23,200), (308,90,200), (400,98,204),
               (402,98,206), (404,28,200), (406,98,204), (410,98,206),
               (415,8,200))
    for action, counter, sequence in actions:
        yield dict(base, tag="action-ambiguity", action=action,
                   counter=counter, sequence=sequence)
    seeds = json.loads((ROOT / "tests/fixtures/cpu-policy-selection-seeds.json").read_text())
    if len(seeds) != 101 or len(set(seeds)) != 101:
        raise ValueError("expected 101 distinct native selection seeds")
    # Only the concrete overlapping ranges and independent duration tails.
    selections = ((0.,0.,100.,50), (0.,0.,400.,35), (0.,0.,550.,35),
                  (0.,0.,550.,85), (0.,0.,700.,85), (0.,300.,100.,25),
                  (0.,300.,100.,50), (0.,500.,400.,50), (0.,300.,500.,52),
                  (0.,300.,500.,85), (0.,300.,600.,45), (300.,0.,100.,30),
                  (300.,0.,400.,45), (300.,0.,500.,12), (300.,0.,700.,35),
                  (100.,500.,100.,5), (500.,100.,400.,25),
                  (500.,100.,500.,48), (500.,100.,700.,4))
    for sy, oy, distance, roll in selections:
        yield dict(base, tag="policy-overlap", policy=0, timer=0,
                   self_y=sy, other_y=oy, other_x=100+distance,
                   seed=seeds[roll], expected_roll=roll)
    # Three real MT streams expose the corrected h400 guard; both airborne
    # entries also exercise the independently retained proposal sequence.
    for sy, oy in ((0.,0.), (0.,200.), (100.,0.), (100.,200.)):
        for seed in (1,7,42):
            yield dict(base, tag="attack-order", policy=0, timer=10,
                       self_y=sy, other_y=oy, other_x=500.,
                       other_action=201, seed=seed)


def audit(object_path):
    # Reuse the existing execution engine; every helper executes PE code.
    import importlib.util
    import sys
    spec = importlib.util.spec_from_file_location(
        "alice_native_paths", ROOT / "scripts/audit-cpu-policy-paths.py")
    paths = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = paths
    spec.loader.exec_module(paths)
    canonical = paths.boundary.load_script("alice_path_canonical", "compare-function.py")
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != "44c74a61697409bc3628dbd5c2e48788f4c0e5ce02a439bcce5331d19812431d":
        raise ValueError("complete target payload changed")
    unit = load_manifest()["units"]["exact-first-alice-cpu-policy"]
    function, = unit["functions"]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("configured root address changed")
    targets = canonical.known_targets()
    targets.update({name: int(value, 0) for name, value in
                    (binding.rsplit("=", 1) for binding in function["rel32_targets"])})
    candidate = canonical.coff_symbol_bytes(
        object_path, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
        targets, canonical.known_data_targets())
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    # The first action table precedes the other emitted tables. Discover its
    # base from instructions before attempting strict code-only decoding.
    metadata_start = None
    for instruction in decoder.disasm(candidate, ADDRESS):
        if instruction.mnemonic == "jmp" and instruction.operands[0].type == X86_OP_MEM:
            metadata_start = instruction.operands[0].mem.disp
            break
    if metadata_start is None or not ADDRESS < metadata_start < ADDRESS + len(candidate):
        raise ValueError("candidate has no bounded switch tables")
    paths.decode(candidate[:metadata_start - ADDRESS], ADDRESS)

    class Probe(paths.NativeCpuProbe):
        def locate_join(self, code, address):
            # NativeCpuProbe completes RET; this boundary does not stop it.
            sites = [i.address for i in paths.decode(code, address)
                     if (i.mnemonic, i.op_str) ==
                     ("cmp", "word ptr [esi + 0x766], bx")]
            if len(sites) != 1:
                raise ValueError("expected one common attack guard")
            return sites[0]

    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    engines = (Probe(image, target, CALLABLE_SIZE, address=ADDRESS),
               Probe(image, candidate, metadata_start - ADDRESS, address=ADDRESS))
    counts, digest, mismatches, examples = Counter(), hashlib.sha256(), 0, []
    for vector in cases():
        for engine in engines:
            engine.visited_root.clear()
        expected, actual = (engine.evaluate(vector) for engine in engines)
        counts[vector["tag"]] += 1
        digest.update(json.dumps(vector, sort_keys=True).encode())
        if "expected_roll" in vector:
            roll = struct.unpack_from("<h", bytes.fromhex(expected["actor"]), 0x76A)[0]
            if roll != vector["expected_roll"]:
                raise ValueError("native target did not confirm selection seed")
        if vector["tag"] == "attack-order" and vector["self_y"] == vector["other_y"] == 0.0:
            if sum(call[0] == "rng" for call in expected["calls"]) != 17:
                raise ValueError("native target did not confirm the h400 RNG counterexample")
        if expected != actual:
            mismatches += 1
            if len(examples) < 4:
                examples.append(dict(vector=vector, differing_fields=[
                    key for key in expected if expected[key] != actual[key]]))
    return dict(diagnostic_only=True, target_sha256=identity,
                source_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                count=sum(counts.values()), categories=dict(counts),
                vector_sha256=digest.hexdigest(), mismatch_count=mismatches,
                examples=examples)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    unit = load_manifest()["units"]["exact-first-alice-cpu-policy"]
    report = audit(args.object or ROOT / unit["object"])
    print(json.dumps(report, indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
