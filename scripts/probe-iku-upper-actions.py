#!/usr/bin/env python3
"""Execute staged middle/upper Iku C++ actions against original target paths.

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
from iku_middle_actions import MIDDLE_ENTRIES
from iku_upper_actions import DATA_KEYS, ENTRIES, METHODS, NEW_ENTRIES

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("iku_upper_late_fixture", ROOT / "scripts/probe-iku-late-actions.py")
late = importlib.util.module_from_spec(spec)
spec.loader.exec_module(late)
spell, base = late.spell, late.base
SOURCE = ROOT / "src/characters/IkuActionState.cpp"


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


def middle_cases(smoke=False):
    basic = dict(late.input_cases(True)[0], middle_fixture=True, state_180=6, seed=1,
                 time=-1, timer=-1, frame=0, sequence=0, brake=0, field_6bc=1,
                 byte606=0, direction_state=0, direction_gate=0, horizontal=0, vertical=0)
    airborne = {306, 307, 308, 309, 310, 404, 406, 409, 412, 414, 415, 416, 417, 418, 547}
    cases = []
    def add(action, **fields):
        cases.append(basic | {"action": action, "y": 100.0 if action in airborne else 0.0} | fields)
    frames = (0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14) if smoke else range(16)
    for action, sequence, frame, timer in itertools.product(
            MIDDLE_ENTRIES, (0, 1, 2) if smoke else (-1, 0, 1, 2, 3), frames, (-1, 0)):
        add(action, sequence=sequence, frame=frame, timer=timer)
    for action, mode, horizontal, vertical, facing, gate in itertools.product(
            (300, 301, 302, 303, 304, 305, 320, 321, 322), (0, 6) if smoke else (0, 1, 6, 7, 9),
            (-1, 0, 1), (-1, 0) if smoke else (-1, 0, 1), (-1, 1), (0,) if smoke else (0, 1)):
        add(action, state_180=mode, direction_state=10, horizontal=horizontal, vertical=vertical,
            facing=facing, direction_gate=gate, frame=4)
    for action in (300, 301, 302, 303, 304, 305, 320, 321, 322, 408, 412, 418, 500, 501):
        for sequence, frame, vx, brake in itertools.product(
                (0, 1, 2), (0, 5, 7) if smoke else (0, 2, 5, 7, 11, 12, 14),
                ("bf800000", "3e800000", "41700000", "7fc00000") if smoke else
                ("bf800000", "80000000", "00000000", "3e800000", "3f800000", "40400000", "41700000", "7fc00000"),
                (0, 1, 128, 255) if action in (300, 301, 303) else (0,)):
            add(action, sequence=sequence, frame=frame, vx_bits=vx, brake=brake)
    for action, sequence, counter, mode, byte184, time in itertools.product(
            (309, 310, 500, 501), (0, 1) if smoke else (0, 1, 2),
            (0, 4, 5, 32767) if smoke else (-32768, -1, 0, 3, 4, 5, 6, 32767),
            (6,) if smoke else (0, 6), (1,) if smoke else (0, 1, -128),
            (0, 15, 31) if smoke else (-9, -8, -1, 0, 8, 14, 15, 30, 31)):
        add(action, sequence=sequence, gate=counter, state_180=mode, byte_184=byte184, time=time,
            frame=7, phase_bits="41700000")
    for action, sequence, y, vy in itertools.product(
            sorted(airborne), (0, 1, 2), (0.0, 0.25, 100.0), (-1.0, 0.0, 3.0)):
        add(action, sequence=sequence, y=y, vy=vy, acceleration=0.5, frame=7)
    for action, sequence, frame, flag, resources in itertools.product(
            (302, 304, 307, 308, 400, 401, 402, 404, 406, 410, 411, 414, 415,
             416, 417, 505, 506, 540, 541, 547), (0, 1), (3, 4, 5, 7, 8, 12), (0, 1, 2, 255), (0, 1)):
        if smoke and frame not in (3, 8):
            continue
        add(action, sequence=sequence, frame=frame, flag=flag,
            field_6bc=resources, field_6c0=resources, field_6c4=resources)
    for action, frame, value in itertools.product((540, 541), (5, 6, 8, 12, 13, 14), (0, 3, 4, 127, 128, 255)):
        add(action, frame=frame, byte606=value)
    for action, frame, seed, facing in itertools.product(
            (301, 302, 304, 505, 506, 520, 521), (4, 6, 10), (1, 1472677) if smoke else (0, 1, 31, 119, 1472677), (-1, 1)):
        add(action, frame=frame, seed=seed, facing=facing, timer=0 if action in (520, 521) else -1)
    if not smoke:
        for action, sequence, frame, cw, vy in itertools.product(
                (309, 310, 412, 547), (0, 1, 2), (0, 2, 7), (0x27F, 0x37F), (-1.0, 0.1, 3.0)):
            add(action, sequence=sequence, frame=frame, cw=cw, vy=vy, y=0.25, phase_bits="41700000")
    return list({json.dumps(case, sort_keys=True): case for case in cases}.values())


def coordinate_cases(smoke=False):
    actions = (540, 541, 545, 546)
    cases = [case for case in middle_cases(smoke) if case["action"] in actions]
    basic = dict(middle_cases(True)[0], seed=1, sequence=0, y=0.0, time=7)
    for action, sequence, frame, timer, facing, cw, bits in itertools.product(
            actions, (0, 1), (8, 12), (-1, 0), (-1, 1), (0x27F, 0x37F),
            ("00000000", "80000000", "00000001", "80000001", "44200000")):
        cases.append(basic | {"action": action, "sequence": sequence, "frame": frame, "timer": timer,
                              "facing": facing, "cw": cw, "x_bits": bits})
    return list({json.dumps(case, sort_keys=True): case for case in cases}.values())


class UpperProbe(late.LateProbe):
    def __init__(self, canonical, candidate, seeds, table):
        super().__init__(canonical, candidate, seeds, table)
        self.entries = MIDDLE_ENTRIES | ENTRIES
        self.helpers = self.helpers | {0x478EE0: 1}
        self.target_boundaries.update(row.address for row in base.decode(canonical.target_bytes(0x478EE0, 184), 0x478EE0))
        for event in (27, 28, 29):
            if canonical.target_bytes(0x6FCA98 + event * 4, 4) != bytes(4):
                raise ValueError("middle event fixture is not the target zero handle")

    def actor_fields(self, case):
        fields = super().actor_fields(case)
        if not case.get("middle_fixture"):
            return fields
        return (*fields, (0x47E, "B", case["brake"]), (0x4A8, "h", 99),
                (0x4B2, "H", case["direction_gate"]), (0x4B8, "i", case["direction_state"]),
                (0x606, "B", case["byte606"]), (0x6B4, "i", case["horizontal"]),
                (0x6B8, "i", case["vertical"]), (0x6BC, "i", case["field_6bc"]))


def audit(source=SOURCE, output=None, smoke=False, new_only=False, middle=False, control=None, coordinates=False):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    if hashlib.sha256(canonical.target_bytes(0x620920, 59038)).hexdigest() != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku root differs")
    output = output or ROOT / "build/IkuActionState.obj"
    receipt = base.build_source(source, output)
    table, initialization = lookup_fixture(canonical)
    ledger = {int(row["address"], 0): int(row["size"])
              for row in csv.DictReader((ROOT / "config/functions.csv").open())}
    cases = coordinate_cases(smoke) if coordinates else middle_cases(smoke) if middle else gate_cases(smoke) if new_only else input_cases(smoke)
    control_actions = {"single-counter": (310,), "unsigned-brake": (303,), "current-height": (547,),
                       "zero-offset": (540, 541, 545, 546)}
    if middle and control in control_actions:
        cases = [case for case in cases if case["action"] in control_actions[control]]
    seed_engine = spell.seed_module.Probe(canonical, pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image(),
                                          {address: ledger[address] for address in spell.seed_module.HELPERS})
    seeds = {seed: seed_engine.seed(seed) for seed in sorted({case["seed"] for case in cases})}
    probe = UpperProbe(canonical, base.load_object(output, root_prefix="?try_dispatch_verified_action@",
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
    return {"schema": "th105-iku-action-state-source-native-v1", "target_sha256": target_sha, "build": receipt,
            "actions": len(ENTRIES) + len(MIDDLE_ENTRIES),
            "case_set": "middle-coordinates" if coordinates else "middle-actions" if middle else "new-action-gates" if new_only else "upper-actions",
            "tested_actions": sorted({case["action"] for case in cases}), "cases": len(cases), "mismatch_count": differences, "examples": examples,
            "input_sha256": inputs.hexdigest(), "target_output_sha256": outputs.hexdigest(),
            "lookup_initialization": initialization, "math_runtime_trace": probe.math_trace,
            "outcomes": [{"side": side, "stop": stop, "cases": count} for (side, stop), count in sorted(probe.outcomes.items())],
            "target_root_instructions_visited": len(probe.visited), "source_view_aliases": probe.aliases,
            "probe_sha256": linked_pe.sha(Path(__file__)), "base_probe_sha256": linked_pe.sha(Path(base.__file__)),
            "fixture_sha256": {name: linked_pe.sha(ROOT / "scripts" / name) for name in
                               ("probe-iku-spell-actions.py", "probe-iku-late-actions.py", "iku_native_math.py", "iku_upper_actions.py", "iku_middle_actions.py")},
            "unicorn_version": unicorn.__version__,
            "scope": "77 complete staged action bodies in one compiled dispatcher; real prelude/math/RNG/helpers; "
                     "RET or genuine first object/effect/animation/finalize backend entry; NaN X stops at abs entry; "
                     "no injected helper returns; post-backend paths, remaining33 opening actions and full-root exact equality unproved"}


def control_source(name):
    source = SOURCE.read_text()
    if name == "aim-limit":
        needle = "if (float_at(0x744) > 60.0) float_at(0x744) = 60.0f;"
        replacement = "if (float_at(0x744) > 60.0) float_at(0x744) = -60.0f;"
    elif name == "unsigned-gate":
        needle = "if (short_at(0x730) > 0 && frame_index_140 < 7 && short_at(0x730) < 12) {"
        replacement = "if (static_cast<unsigned short>(short_at(0x730)) > 0 && frame_index_140 < 7 && short_at(0x730) < 12) {"
    elif name == "single-counter":
        needle = ("// The second increment in sequence1 is distinct and intentional.\n"
                  "            if (int_at(0x180) != 0 && ++short_at(0x730) > 5) { int_at(0x180) = 0; short_at(0x730) = 0; }")
        replacement = "// Deliberately omitted second increment for native calibration."
    elif name == "unsigned-brake":
        needle = "static_cast<signed char>(byte_at(0x47e)) > 0"
        replacement = "byte_at(0x47e) != 0"
    elif name == "current-height":
        start = source.index("    case 547:\n")
        prefix, source = source[:start], source[start:]
        needle = "double projected_y = static_cast<double>(float_at(0xf8)) + float_at(0xf0);"
        replacement = "double projected_y = float_at(0xf0);"
        if source.count(needle) != 1:
            raise ValueError("predictive control no longer identifies one547 expression")
        source = prefix + source.replace(needle, replacement)
        path = ROOT / "build/iku-middle-current-height.cpp"
        path.write_bytes(source.replace("\n", "\r\n").encode())
        return path
    elif name == "zero-offset":
        needle = "ahead == 0 ? float_at(0xec) : "
        if source.count(needle) != 2:
            raise ValueError("zero-offset control no longer identifies the two shared coordinate expressions")
        source = source.replace(needle, "")
        path = ROOT / "build/iku-middle-zero-offset.cpp"
        path.write_bytes(source.replace("\n", "\r\n").encode())
        return path
    else:
        raise ValueError("unknown Iku source control")
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
    cases = parser.add_mutually_exclusive_group()
    cases.add_argument("--new-only", action="store_true", help="focus on the nine upper actions with post-advance gate inputs")
    cases.add_argument("--middle", action="store_true", help="focus on the42 new middle actions")
    parser.add_argument("--control", choices=("aim-limit", "unsigned-gate", "single-counter", "unsigned-brake", "current-height", "zero-offset"))
    parser.add_argument("--coordinates", action="store_true", help="with --middle, focus on direct X transfer and signed zero")
    args = parser.parse_args()
    if args.coordinates and not args.middle:
        parser.error("coordinate cases require --middle")
    if args.control == "zero-offset" and not args.coordinates:
        parser.error("zero-offset control requires --middle --coordinates")
    if args.control in ("single-counter", "unsigned-brake", "current-height") and not args.middle:
        parser.error("middle controls require --middle")
    source = control_source(args.control) if args.control else args.source.resolve()
    output = args.output.resolve() if args.output else (ROOT / "build" / ("IkuUpper-" + args.control + ".obj")
                                                       if args.control else None)
    report = audit(source, output, args.smoke, args.new_only, args.middle, args.control, args.coordinates)
    report["diagnostic_control"] = args.control
    print(json.dumps(report, indent=2))
    raise SystemExit(bool(report["mismatch_count"]))
