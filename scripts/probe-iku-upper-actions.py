#!/usr/bin/env python3
"""Execute the unified 35-action C++ dispatcher against original Iku paths.

This is a semantic source diagnostic, not a standalone-object exact claim.
The original prelude runs on both sides. Backend calls stop at their genuine
entry; native dependencies run without injected return values.
"""
import argparse
import csv
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import sys

import pefile
import unicorn
import unicorn.x86_const as r

import linked_pe
from iku_native_math import lookup_fixture
from iku_upper_actions import DATA_KEYS, ENTRIES, METHODS, NEW_ENTRIES

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("iku_upper_late_fixture", ROOT / "scripts/probe-iku-late-actions.py")
late = importlib.util.module_from_spec(spec)
spec.loader.exec_module(late)
spell, base = late.spell, late.base
SOURCE = ROOT / "src/characters/IkuActionStateUpper.cpp"


def input_cases(smoke=False):
    basic = dict(late.input_cases(True)[0], action=560, sequence=0, frame=0, timer=0, time=7, state_180=6)
    cases = []
    def add(action, **fields):
        cases.append(dict(basic, **(fields | {"action": action})))
    # The previous three families now run through the same compiled dispatcher.
    # Preserve every prior case field; pad only fields absent in its fixture.
    for factory in (base.input_cases, spell.input_cases, late.input_cases):
        for case in factory(smoke):
            cases.append(basic | case)
    for action, sequence, frame, timer in itertools.product(
            NEW_ENTRIES, (-1, 0, 1, 2, 3), (0, 5, 7, 8, 9), (-1, 0)):
        add(action, sequence=sequence, frame=frame, timer=timer, time=0 if frame == 0 else 7)
    for action, facing, peer_x, peer_y, phase, counter in itertools.product(
            (560, 561, 562, 563), (-1, 1), (520.0, 640.0, 760.0),
            (-160.0, 0.0, 80.0, 240.0), (0,) if smoke else (-1, 0, 1, 2),
            (1000,) if smoke else (-32768, 0, 1000, 32767)):
        add(action, frame=7, facing=facing, peer_x=peer_x, peer_y=peer_y, phase=phase, counter=counter)
    for action, sequence, flag, field_6c0, field_6c4 in itertools.product(
            (560, 561, 562, 563), (0, 1, 2), (0, 1, 255), (0, 1), (0, 1)):
        add(action, sequence=sequence, frame=8, flag=flag, field_6c0=field_6c0, field_6c4=field_6c4)
    for action, sequence, y, vy in itertools.product(
            (562, 563, 572, 573), (-1, 0, 1, 2, 3), (-1.0, 0.0, 1.0, 100.0), (-1.0, 0.0, 3.0)):
        add(action, sequence=sequence, frame=9, y=y, vy=vy, acceleration=0.5)
    for action, sequence, frame, facing in itertools.product((570, 571, 572, 573), (0, 1, 2), (7, 9), (-1, 1)):
        add(action, sequence=sequence, frame=frame, facing=facing)
    for gate, frame, timer, facing, seed in itertools.product(
            (-32768, -1, 0, 1, 2, 11, 12, 32767), (-1, 0, 5, 6, 7), (-1, 0), (-1, 1),
            (1, 119) if smoke else spell.seed_module.SEEDS):
        add(599, gate=gate, frame=frame, timer=timer, facing=facing, seed=seed)
    if not smoke:
        for action, sequence, frame, time, cw in itertools.product(
                NEW_ENTRIES, (-32768, -1, 0, 1, 2, 32767), (0, 2, 5, 7, 8, 9), (-1, 0, 1), (0x27F, 0x37F)):
            add(action, sequence=sequence, frame=frame, time=time, cw=cw)
    return list({json.dumps(case, sort_keys=True): case for case in cases}.values())


def gate_cases(smoke=False):
    # Genuine4351C0 increments both counters. A post-advance zero gate needs
    # input -1; the earlier broad aim matrix used0 and skipped its shot gates.
    basic = dict(late.input_cases(True)[0], action=560, sequence=0, frame=7,
                 timer=-1, time=-1, state_180=6, seed=1)
    cases = []
    def add(action, **fields):
        cases.append(basic | {"action": action, "y": 100.0 if action in (562, 563, 572, 573) else 0.0} | fields)
    for action, sequence, frame, timer, time, vy in itertools.product(
            NEW_ENTRIES, (0, 1, 2) if smoke else (-1, 0, 1, 2, 3),
            (0, 7, 8, 9) if smoke else (0, 2, 5, 7, 8, 9),
            (-1,) if smoke else (-1, 0), (-1,) if smoke else (-1, 0, 7),
            (3.0,) if smoke else (-1.0, 0.0, 3.0)):
        add(action, sequence=sequence, frame=frame, timer=timer, time=time, vy=vy)
    for action, facing, peer_x, peer_y, phase, counter, cw in itertools.product(
            (560, 561, 562, 563), (-1, 1), (520.0, 640.0, 760.0), (-160.0, 0.0, 80.0, 240.0),
            (0,) if smoke else (-1, 0, 1, 2), (1000,) if smoke else (-32768, 0, 1000, 32767),
            (0x27F,) if smoke else (0x27F, 0x37F)):
        add(action, facing=facing, peer_x=peer_x, peer_y=peer_y, phase=phase, counter=counter, cw=cw)
    for action, sequence, flag, field_6c0, field_6c4 in itertools.product(
            (560, 561, 562, 563), (0, 1, 2), (0, 1, 255), (0, 1), (0, 1)):
        add(action, sequence=sequence, frame=8, flag=flag, field_6c0=field_6c0, field_6c4=field_6c4)
    for gate, frame, timer, facing, seed in itertools.product(
            (-32768, -1, 0, 1, 2, 11, 12, 32767), (-1, 0, 5, 6, 7), (-1, 0), (-1, 1), (1, 119)):
        add(599, gate=gate, frame=frame, timer=timer, facing=facing, seed=seed)
    return list({json.dumps(case, sort_keys=True): case for case in cases}.values())


class UpperProbe(late.LateProbe):
    def __init__(self, canonical, candidate, seeds, table):
        super().__init__(canonical, candidate, seeds, table)
        self.entries = ENTRIES


def audit(source=SOURCE, output=None, smoke=False, new_only=False):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    if hashlib.sha256(canonical.target_bytes(0x620920, 59038)).hexdigest() != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku root differs")
    output = output or ROOT / "build/IkuActionStateUpper.obj"
    receipt = base.build_source(source, output)
    table, initialization = lookup_fixture(canonical)
    ledger = {int(row["address"], 0): int(row["size"])
              for row in csv.DictReader((ROOT / "config/functions.csv").open())}
    cases = gate_cases(smoke) if new_only else input_cases(smoke)
    seed_engine = spell.seed_module.Probe(canonical, pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image(),
                                          {address: ledger[address] for address in spell.seed_module.HELPERS})
    seeds = {seed: seed_engine.seed(seed) for seed in sorted({case["seed"] for case in cases})}
    probe = UpperProbe(canonical, base.load_object(output, root_prefix="?try_dispatch_verified_upper_action@",
                                                 methods=METHODS, data_keys=DATA_KEYS), seeds, table)
    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    differences, examples = 0, []
    for number, case in enumerate(cases, 1):
        inputs.update(json.dumps(case, sort_keys=True).encode())
        try:
            expected, actual = probe.evaluate(case, False), probe.evaluate(case, True)
        except Exception as error:
            raise ValueError(f"{case}; pc={probe.engine.reg_read(r.UC_X86_REG_EIP):#x}; "
                             f"calls={probe.calls[-4:]}; {error}") from error
        outputs.update(json.dumps(expected, sort_keys=True).encode())
        if expected != actual:
            differences += 1
            if len(examples) < 2:
                examples.append({"case": case, "target": expected, "source": actual})
        if number % 2000 == 0:
            print(f"{number}/{len(cases)} cases; {differences} differences", file=sys.stderr, flush=True)
    if (linked_pe.sha(source) != receipt["source_sha256"] or linked_pe.sha(output) != receipt["object_sha256"]
            or linked_pe.sha(base.HEADER) != receipt["header_sha256"]):
        raise ValueError("source/header/object changed during native execution")
    return {"schema": "th105-iku-upper-source-native-v1", "target_sha256": target_sha, "build": receipt,
            "actions": len(ENTRIES), "case_set": "new-action-gates" if new_only else "all-staged",
            "tested_actions": sorted({case["action"] for case in cases}), "cases": len(cases), "mismatch_count": differences, "examples": examples,
            "input_sha256": inputs.hexdigest(), "target_output_sha256": outputs.hexdigest(),
            "lookup_initialization": initialization, "math_runtime_trace": probe.math_trace,
            "outcomes": [{"side": side, "stop": stop, "cases": count} for (side, stop), count in sorted(probe.outcomes.items())],
            "target_root_instructions_visited": len(probe.visited), "source_view_aliases": probe.aliases,
            "probe_sha256": linked_pe.sha(Path(__file__)), "base_probe_sha256": linked_pe.sha(Path(base.__file__)),
            "fixture_sha256": {name: linked_pe.sha(ROOT / "scripts" / name) for name in
                               ("probe-iku-spell-actions.py", "probe-iku-late-actions.py", "iku_native_math.py", "iku_upper_actions.py")},
            "unicorn_version": unicorn.__version__,
            "scope": "35 complete staged action bodies in one compiled dispatcher; real prelude/math/RNG/helpers; "
                     "RET or genuine first object/effect/animation/finalize backend entry; NaN X stops at abs entry; "
                     "no injected helper returns; post-backend paths, remaining75 actions and full-root exact equality unproved"}


def control_source(name):
    source = SOURCE.read_text()
    if name == "aim-limit":
        needle = "if (float_at(0x744) > 60.0) float_at(0x744) = 60.0f;"
        replacement = "if (float_at(0x744) > 60.0) float_at(0x744) = -60.0f;"
    elif name == "unsigned-gate":
        needle = "if (short_at(0x730) > 0 && frame_index_140 < 7 && short_at(0x730) < 12) {"
        replacement = "if (static_cast<unsigned short>(short_at(0x730)) > 0 && frame_index_140 < 7 && short_at(0x730) < 12) {"
    else:
        raise ValueError("unknown upper source control")
    if source.count(needle) != 1:
        raise ValueError("control no longer identifies one source predicate")
    path = ROOT / "build" / ("iku-upper-" + name + ".cpp")
    path.write_bytes(source.replace(needle, replacement).replace("\n", "\r\n").encode())
    return path


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=SOURCE)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--smoke", action="store_true")
    parser.add_argument("--new-only", action="store_true", help="focus on the nine new actions with post-advance gate inputs")
    parser.add_argument("--control", choices=("aim-limit", "unsigned-gate"))
    args = parser.parse_args()
    source = control_source(args.control) if args.control else args.source.resolve()
    output = args.output.resolve() if args.output else (ROOT / "build" / ("IkuUpper-" + args.control + ".obj")
                                                       if args.control else None)
    report = audit(source, output, args.smoke, args.new_only)
    report["diagnostic_control"] = args.control
    print(json.dumps(report, indent=2))
    raise SystemExit(bool(report["mismatch_count"]))
