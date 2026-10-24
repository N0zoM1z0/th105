#!/usr/bin/env python3
"""Check specific Marisa CPU path ambiguities with genuine native helpers.

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
ADDRESS = 0x004B4070
CALLABLE_SIZE = 16229
PAYLOAD_SIZE = 16907


def cases():
    base = dict(action=201, sequence=205, self_x=100., other_x=350.,
                self_y=0., other_y=0., vx=0., vy=0., other_action=100,
                resource=1000, mode=3, facing=1, counter=100, policy=-1,
                timer=10, refresh=1, seed=0, control_6b4=-7, control_6b8=5)
    # Isolate first-stage windows and sequence switches from later writes.
    for action in (200, 300, 301, 302, 303, 304, 305, 306, 307, 308, 320,
                   321, 322, 400, 401, 402, 404, 405, 406, 410, 411, 414, 416):
        for counter in (-1, 0, 10, 15, 20, 25, 30, 35, 40, 50, 55, 65, 70,
                        75, 80, 85, 90, 95, 100, 101):
            yield dict(base, tag="action-windows", action=action, counter=counter)
    for action in (302, 304, 305, 322, 400, 410):
        for sequence in range(199, 213):
            yield dict(base, tag="sequence-edges", action=action, sequence=sequence)
    # A few actual MT streams distinguish independent attack draws by posture.
    for sy, oy in ((0., 0.), (0., 100.), (100., 0.), (100., 200.)):
        for distance in (60., 140., 210., 400.):
            for seed in (0, 1, 7, 42):
                yield dict(base, tag="attack-calls", policy=0, timer=10,
                           self_y=sy, other_y=oy, other_x=100 + distance,
                           other_action=201, seed=seed)
    # Full real selector range in four distinct policy0 bands; no hooked RNG.
    seeds = json.loads((ROOT / "tests/fixtures/cpu-policy-selection-seeds.json").read_text())
    if len(seeds) != 101 or len(set(seeds)) != 101:
        raise ValueError("expected 101 distinct native selection seeds")
    for sy, oy, distance in ((0., 0., 80.), (0., 300., 100.),
                             (300., 0., 200.), (300., 100., 600.)):
        for roll, seed in enumerate(seeds):
            yield dict(base, tag="policy0-calls", policy=0, timer=0, self_y=sy,
                       other_y=oy, other_x=100 + distance, seed=seed,
                       expected_roll=roll)
    for policy in list(range(1, 20)) + [100, 101, 102]:
        for timer in (0, 10):
            yield dict(base, tag="terminal-policies", policy=policy,
                       timer=timer, action=200)
    # Native FCOMP180 / TEST AH,41 / JP includes equality in this gate.
    for seed in (0, 1, 7, 42):
        yield dict(base, tag="distance180", other_x=280., other_action=201,
                   sequence=212, policy=0, timer=10, seed=seed)
    # These two real streams reach different shared tails. Their vertical
    # values must be attested before comparing the candidate.
    for sy, oy, vertical, site in ((300., 0., 1, 0x4B64A3),
                                   (400., 100., 0, 0x4B692F)):
        yield dict(base, tag="descending-tail", self_y=sy, other_y=oy,
                   sequence=212, other_action=201, policy=0, timer=10,
                   seed=54, expected_descending_vertical=vertical,
                   expected_descending_site=site)
    # Resolve the ordered velocity predicates using specific exceptional inputs.
    for sy, oy, distance in ((100., 250., 90.), (300., 100., 140.),
                             (300., 0., 140.)):
        for axis in ("vx_bits", "vy_bits"):
            for bits in ("7fc00000", "40400000", "c0400000"):
                for seed in (0, 1, 7, 42):
                    yield dict(base, tag="velocity-predicates", self_y=sy,
                               other_y=oy, other_x=100 + distance, sequence=212,
                               other_action=201, policy=0, timer=10, seed=seed,
                               **{axis: bits})


def audit(object_path):
    # Reuse the existing execution engine; every helper executes PE code.
    import importlib.util
    import sys
    spec = importlib.util.spec_from_file_location(
        "marisa_native_paths", ROOT / "scripts/audit-cpu-policy-paths.py")
    paths = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = paths
    spec.loader.exec_module(paths)
    canonical = paths.boundary.load_script("marisa_path_canonical", "compare-function.py")
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != "390ace272a1567150c1332831c28fb1c252073f80879975b86c6d1e9a30d0e90":
        raise ValueError("complete target payload changed")
    unit = load_manifest()["units"]["exact-first-marisa-cpu-policy"]
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
        if "expected_descending_vertical" in vector:
            actor = bytes.fromhex(expected["actor"])
            vertical, = struct.unpack_from("<i", actor, 0x6B8)
            button, = struct.unpack_from("<i", actor, 0x6C4)
            if button != 2 or vertical != vector["expected_descending_vertical"]:
                raise ValueError("native target did not confirm descending-tail ownership")
            if vector["expected_descending_site"] not in engines[0].visited_root:
                raise ValueError("native target did not visit the pinned descending tail")
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
    unit = load_manifest()["units"]["exact-first-marisa-cpu-policy"]
    report = audit(args.object or ROOT / unit["object"])
    print(json.dumps(report, indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
