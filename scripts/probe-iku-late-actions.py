#!/usr/bin/env python3
"""Native source diagnostic for all fourteen Iku high-switch arms after610.

Real target initialization supplies the cosine table; real math, lookup,
RNG, event and field helpers execute. Object/effect/animation backends remain
entry stops. No target instruction or helper result is replaced by a hook.
"""
import argparse
import csv
import hashlib
import itertools
import json
from pathlib import Path
import struct

import pefile
import unicorn
from unicorn import x86_const as r

import linked_pe
from iku_native_math import lookup_fixture, attest_instruction

ROOT = Path(__file__).resolve().parents[1]
# Reuse the focused source loader and existing genuine seed/texture fixture.
import importlib.util
spec = importlib.util.spec_from_file_location("iku_late_spell_fixture", ROOT / "scripts/probe-iku-spell-actions.py")
spell = importlib.util.module_from_spec(spec)
spec.loader.exec_module(spell)
base = spell.base
SOURCE = ROOT / "src/characters/IkuActionStateUpper.cpp"
ENTRIES = {650: 0x62D02A, 660: 0x62D1DE, 695: 0x62D5C7, 696: 0x62D72D,
           710: 0x62D7E1, 720: 0x62D8B0, 730: 0x62DA63, 740: 0x62E341,
           770: 0x62E4F1, 780: 0x62E588, 781: 0x62E909, 795: 0x62EADA,
           797: 0x62EB17, 798: 0x62ED65}
PAIR = base.OWNER + 0xA000
DATA_KEYS = base.DATA_KEYS
METHODS = base.METHODS
HELPERS = dict(spell.HELPERS) | {0x478E60: 0, 0x45B250: 0, 0x476AB0: 2, 0x476AD0: 2,
                                0x476AF0: 2, 0x427290: 2, 0x4272B0: 2, 0x4272D0: 2,
                                0x434E10: 2, 0x406330: 1, 0x406360: 1, 0x4063D0: 1,
                                0x406540: 2, 0x68BAAE: 2}
STOPS = dict(spell.STOPS) | {0x45D110: 1}


def input_cases(smoke=False):
    example = spell.input_cases(True)[0]
    basic = dict(example, action=730, sequence=0, frame=0, time=7, timer=0, vy=3.0,
                 bias=20, count736=0, phase_bits="00000000", radius_bits="43480000",
                 fade=0, word76c=123, peer_x=760.0, peer_y=80.0, match=0,
                 rgb=(0, 0, 0), x_bits=None, pair_bits="00000000")
    cases = []
    def add(action, **fields):
        case = dict(basic)
        case.update(fields)
        case["action"] = action
        cases.append(case)
    for action in ENTRIES:
        for sequence, frame, timer in itertools.product((0, 1, 2, 3, 4, 5, 7, 9, 10, 11),
                                                         (0, 3, 4, 5, 6, 7, 9, 10), (-1, 0)):
            if smoke and frame not in (0, 4, 7, 10):
                continue
            add(action, sequence=sequence, frame=frame, timer=timer,
                time=-1 if frame == 0 else 7)
    for sequence, match, vx, facing, peer_x, peer_y in itertools.product(
            (7, 8, 9, 10), (0, 1, 2, 3), ("00000000", "40400000", "c0400000") if smoke else
            ("00000000", "80000000", "00000001", "40400000", "c0400000", "7f800000", "7fc00000"),
            (-1, 1), (760.0,) if smoke else (520.0, 640.0, 760.0), (80.0,) if smoke else (-80.0, 0.0, 80.0)):
        add(730, sequence=sequence, match=match, vx_bits=vx, facing=facing, peer_x=peer_x, peer_y=peer_y)
    for sequence, count, bias, gate, phase, facing in itertools.product(
            (0, 1, 2, 3), (0, 180) if smoke else (-32768, 0, 179, 180, 181, 32767),
            (20,) if smoke else (-32768, -20, -1, 0, 1, 20, 32767),
            (0, 2, 3), ("00000000",) if smoke else ("00000000", "42b00000", "43340000", "43b30000"), (-1, 1)):
        add(780, sequence=sequence, count736=count, bias=bias, gate=gate, phase_bits=phase, facing=facing)
    for action, sequence, counter, gate in itertools.product(
            (660, 720, 730, 740, 781), (0, 1, 3, 5), (-1, 0, 14, 15, 19, 20, 59, 60, 119, 120),
            (0, 59, 32767)):
        add(action, sequence=sequence, time=counter, gate=gate, index=359)
    for action, sequence, vx, vy, gate in itertools.product(
            (797, 798), range(6), ("3f800000", "40400000") if smoke else
            ("00000000", "3f800000", "40400000", "c0400000", "7fc00000"),
            (-1.0, 0.0, 1.0), (0, 19, 32767)):
        add(action, sequence=sequence, vx_bits=vx, vy=vy, gate=gate)
    for phase, gate, radius, rgb in itertools.product(
            ("00000000", "43340000"), (0, 2, 3), ("3f800000", "43480000"),
            ((250, 20, 239), (5, 6, 240))):
        add(780, gate=gate, radius_bits=radius, phase_bits=phase, rgb=rgb)
    for phase, radius, tick, fade in itertools.product(
            ("bf800000", "00000000", "3f800000"), ("00000000", "3f800000"), (0, 1), (254, 255, 32767)):
        add(781, sequence=1, phase_bits=phase, radius_bits=radius, tick=tick, fade=fade)
    for bits in ("43a00000", "44200000", "44700000", "7fc00000"):
        add(740, sequence=1, time=-1, timer=-1, x_bits=bits)
    if not smoke:
        for sequence, bias, phase, facing in itertools.product(
                (0, 1, 2, 3), (-20, 20, 32767), ("00000000", "43340000"), (-1, 1)):
            add(780, sequence=sequence, bias=bias, phase_bits=phase, facing=facing, cw=0x37F)
        for sequence, match, vx, facing in itertools.product(
                (7, 9), (0, 3), ("00000000", "40400000", "7fc00000"), (-1, 1)):
            add(730, sequence=sequence, match=match, vx_bits=vx, facing=facing, cw=0x37F)
    return list({json.dumps(case, sort_keys=True): case for case in cases}.values())


class LateProbe(spell.SpellProbe):
    def __init__(self, canonical, candidate, seeds, table):
        self.seeds, self.table = seeds, table
        self.mapped = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
        self.math_trace = {}
        base.Probe.__init__(self, canonical, candidate, entries=ENTRIES, helpers=HELPERS, boundaries=STOPS,
                            no_receiver=(0x4067D0, 0x4066B0, 0x42D1B0, 0x43B1A0, 0x434E10,
                                         0x427290, 0x4272B0, 0x4272D0, 0x406330, 0x406360,
                                         0x4063D0, 0x406540, 0x68BAAE),
                            extra_writes=((spell.MANAGER, spell.MANAGER + 0x1000), (PAIR, PAIR + 0x1000),
                                          (0x6FBCC0, 0x6FBCF0), (0x6FDEF0, 0x6FE8B0), (0x6FA1FC, 0x6FA200)))
        self.manager_global = canonical.known_data_targets()["?g_battle_object_manager@th105@@3PAUBattleObjectManager@1@A"][0]
        self.shared_initial = bytes(self.engine.mem_read(0x6FBCC0, 0x30))
        for event in (23, 29, 55):
            if canonical.target_bytes(0x6FCA98 + event * 4, 4) != bytes(4):
                raise ValueError("indexed event fixture is not the target zero handle")

    def actor_fields(self, case):
        fields = (*super().actor_fields(case), (0x736, "h", case["count736"]), (0x738, "h", case["bias"]),
                  (0x73C, "I", int(case["phase_bits"], 16)), (0x740, "I", int(case["radius_bits"], 16)),
                  (0x76C, "h", case["word76c"]), (0x7B2, "h", case["fade"]),
                  (0x7B4, "I", int(case["pair_bits"], 16)),
                  *[(0x110 + index, "B", value) for index, value in enumerate(case["rgb"])])
        return (*fields, (0xEC, "I", int(case["x_bits"], 16))) if case["x_bits"] else fields

    def prepare_case(self, case):
        super().prepare_case(case)
        uc = self.engine
        # A NaN geometry argument reaches CRT error/OS processing outside this
        # fixture. Still qualify its caller's facing decision and float ABI at
        # the real abs entry, without fabricating that backend's return.
        self.boundaries = STOPS | ({0x406330: 1} if case["x_bits"] == "7fc00000" else {})
        uc.mem_write(0x6FE8B0, self.table)
        uc.mem_write(0x6FA894, struct.pack("<i", case["match"]))
        uc.mem_write(base.PEER + 0xEC, struct.pack("<2f", case["peer_x"], case["peer_y"]))
        uc.mem_write(0x6FBCA0, struct.pack("<I", PAIR))
        uc.mem_write(0x6FBCC0, self.shared_initial)

    def instruction(self, uc, address, size, unused):
        try:
            if address == 0x434E10 and uc.reg_read(r.UC_X86_REG_ECX) != base.OWNER + 0x130:
                raise ValueError("global pair subobject receiver differs")
            if address in (0x427290, 0x4272B0, 0x4272D0) and uc.reg_read(r.UC_X86_REG_ECX) != 0x6FBCC0:
                raise ValueError("shared target service receiver differs")
            if 0x68A000 <= address < 0x6BF33A:
                attest_instruction(self.mapped, uc, address, size, self.math_trace)
                self.target_boundaries.add(address)
        except Exception as error:
            self.failure = str(error)
            uc.emu_stop()
            return
        super().instruction(uc, address, size, unused)

    def evaluate(self, case, source):
        result = super().evaluate(case, source)
        result["shared_targets"] = bytes(self.engine.mem_read(0x6FBCC0, 0x30)).hex()
        result["global_pair"] = bytes(self.engine.mem_read(PAIR + 0x10C, 8)).hex()
        return result


def audit(source=SOURCE, output=None, smoke=False):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    if hashlib.sha256(canonical.target_bytes(0x620920, 59038)).hexdigest() != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku root differs")
    output = output or ROOT / "build/IkuLateActions.obj"
    receipt = base.build_source(source, output)
    table, initialization = lookup_fixture(canonical)
    ledger = {int(row["address"], 0): int(row["size"])
              for row in csv.DictReader((ROOT / "config/functions.csv").open())}
    cases = input_cases(smoke)
    seed_engine = spell.seed_module.Probe(canonical, pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image(),
                                          {address: ledger[address] for address in spell.seed_module.HELPERS})
    seeds = {seed: seed_engine.seed(seed) for seed in sorted({case["seed"] for case in cases})}
    probe = LateProbe(canonical, base.load_object(output, root_prefix="?try_dispatch_verified_late_action@",
                                                methods=METHODS, data_keys=DATA_KEYS), seeds, table)
    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    differences, examples = 0, []
    for case in cases:
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
    if (linked_pe.sha(source) != receipt["source_sha256"] or linked_pe.sha(output) != receipt["object_sha256"]
            or linked_pe.sha(base.HEADER) != receipt["header_sha256"]):
        raise ValueError("source/header/object changed during native execution")
    return {"schema": "th105-iku-late-source-native-v1", "target_sha256": target_sha, "build": receipt,
            "cases": len(cases), "mismatch_count": differences, "examples": examples,
            "input_sha256": inputs.hexdigest(), "target_output_sha256": outputs.hexdigest(),
            "lookup_initialization": initialization, "math_runtime_trace": probe.math_trace,
            "outcomes": [{"side": side, "stop": stop, "cases": count} for (side, stop), count in sorted(probe.outcomes.items())],
            "target_root_instructions_visited": len(probe.visited), "source_view_aliases": probe.aliases,
            "probe_sha256": linked_pe.sha(Path(__file__)), "base_probe_sha256": linked_pe.sha(Path(base.__file__)),
            "unicorn_version": unicorn.__version__,
            "math_fixture_sha256": linked_pe.sha(ROOT / "scripts/iku_native_math.py"),
            "scope": "fourteen complete staged arms; genuine lookup initialization/math/RNG/helpers; "
                     "RET or first object/effect/animation/finalize backend entry; NaN X stops at real abs entry "
                     "before unsupported CRT error/OS processing; no helper-result hooks; "
                     "post-backend/ring continuation/full-root/exception behavior or exact equality unproved"}


def control_source(name):
    source = SOURCE.read_text()
    if name == "heading-decrement":
        needle = "lookup_orientation_cosine_quantized_abs(-float_at(0x744))"
        if source.count(needle) != 1:
            raise ValueError("heading control no longer identifies one source call")
        source = source.replace(needle, "lookup_orientation_cosine_quantized_abs(-float_at(0x744) - 1.0f)")
    elif name == "rounded-decay":
        needle = "short_at(0x738) = static_cast<short>(short_at(0x738) * static_cast<double>(0.95f));"
        if source.count(needle) != 1:
            raise ValueError("decay control no longer identifies one source store")
        source = source.replace(needle, "volatile float rounded_decay = static_cast<float>(short_at(0x738) * static_cast<double>(0.95f));\n"
                                       "            short_at(0x738) = static_cast<short>(rounded_decay);")
    else:
        raise ValueError("unknown late-action source control")
    path = ROOT / "build" / ("iku-late-" + name + ".cpp")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(source.replace("\n", "\r\n").encode())
    return path


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=SOURCE)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--smoke", action="store_true")
    parser.add_argument("--control", choices=("heading-decrement", "rounded-decay"))
    args = parser.parse_args()
    source = control_source(args.control) if args.control else args.source.resolve()
    output = args.output.resolve() if args.output else (ROOT / "build" / ("IkuLate-" + args.control + ".obj")
                                                       if args.control else None)
    report = audit(source, output, args.smoke)
    report["diagnostic_control"] = args.control
    print(json.dumps(report, indent=2))
    raise SystemExit(bool(report["mismatch_count"]))
