#!/usr/bin/env python3
"""Execute staged Iku spell actions against hash-attested original instructions.

Original seed/warm/RNG, texture/deque, landing, frame and wave helpers execute.
Stop at the first spawn, effect or animation virtual backend; other
paths reach RET. No helper result is fabricated. This is not exact acceptance.
"""
import argparse
import csv
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys

import pefile
import unicorn
from unicorn import x86_const as r

import linked_pe

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/characters/IkuActionState.cpp"
ENTRIES = {600: 0x62BDC2, 601: 0x62BF12, 602: 0x62C232, 603: 0x62C619,
           606: 0x62C7A6, 607: 0x62C91B, 609: 0x62CA58, 610: 0x62CC24}


def load_script(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


base = load_script("iku_spell_native_base", "probe-iku-object818-actions.py")
seed_module = load_script("iku_spell_native_seed", "audit-iku-action602-spawn.py")
MANAGER, DEQUE = base.OWNER + 0x6000, base.OWNER + 0x8000
METHODS = base.METHODS
STOPS = dict(base.BOUNDARIES) | {0x45C220: 0, 0x45DEB0: 3, 0x473F90: 0}
HELPERS = dict(base.HELPERS) | {0x45F560: 2, 0x42D1B0: 1, 0x4067D0: 1, 0x4066B0: 0,
                               0x4359F0: 1, 0x43B1A0: 1}


def input_cases(smoke=False):
    basic = dict(sequence=0, timer=0, time=7, frame=0, gate=0, tick=0, index=0,
                 facing=1, x=640.0, y=0.0, vy=0.0, acceleration=0.6, field_6c0=1,
                 field_6c4=1, flag=1, cw=0x27F, phase=0, counter=1000, floor=0,
                 state_4b8=0, vx_bits="3f800000", byte_184=1, state_180=1, seed=1)
    cases = []
    def add(action, **fields):
        cases.append(dict(basic, action=action, **fields))
    for action in ENTRIES:
        for sequence, frame, timer in itertools.product(
                (0, 1, 2), (0, 3, 4, 5, 6, 7, 8, 11, 12), (-1, 0)):
            add(action, sequence=sequence, frame=frame, timer=timer,
                time=-1 if frame == 0 else 7)
        for counter in (-21, -20, -10, -1, 0, 1, 5, 6, 10, 19, 20, 31, 32, 59, 60, 119, 120, 121):
            add(action, sequence=1, time=counter)
    for frame, bits, tick, flag, state in itertools.product(
            (6, 7, 11, 12), ("3f800000", "bf800000") if smoke else
            ("00000000", "80000000", "00000001", "bf800000", "3f800000", "3fe00000", "7f7fffff",
             "ff7fffff", "7f800000", "ff800000", "7fc00000", "ffc00000", "7f800001"),
            (2, 32767) if smoke else (-32768, -1, 0, 1, 2, 3, 32767),
            (0, 1) if smoke else (-128, -1, 0, 1, 127), (0, 1)):
        add(601, frame=frame, vx_bits=bits, gate=tick, byte_184=flag, state_180=state)
    seeds = seed_module.SEEDS if not smoke else (1, 2, 145, 1472677)
    for seed, x, facing, counter, cw in itertools.product(
            seeds, (0.0, 1.0, 128.0, 320.0, 640.0, 1000.0, 1279.0) if not smoke else (640.0, 1000.0),
            (-1, 1), (5, 35), (0x27F, 0x37F) if not smoke else (0x27F,)):
        add(602, seed=seed, sequence=1, x=x, facing=facing, time=counter, cw=cw)
    for action, frame in ((600, 6), (601, 7), (601, 8), (602, 8), (602, 12),
                          (603, 12), (606, 7), (607, 11), (609, 0), (610, 5)):
        for seed, facing, cw in itertools.product(seeds, (-1, 1), (0x27F,) if smoke else (0x27F, 0x37F)):
            add(action, frame=frame, timer=0 if action == 607 else -1, facing=facing, seed=seed, cw=cw,
                sequence=1 if action == 609 else 0, time=-1 if action == 609 else 7)
    for action, frame in ((600, 4), (601, 4), (602, 4), (603, 4), (606, 4), (607, 5), (609, 3), (610, 3)):
        for facing, x, y, cw in itertools.product((-1, 1), (640.0,) if smoke else (0.0, 640.0, 1279.0),
                                                  (0.0,) if smoke else (0.0, 5.0),
                                                  (0x27F,) if smoke else (0x27F, 0x37F)):
            add(action, frame=frame, timer=0 if action == 607 else -1, facing=facing, x=x, y=y, cw=cw)
    return list({json.dumps(case, sort_keys=True): case for case in cases}.values())


class SpellProbe(base.Probe):
    def __init__(self, canonical, candidate, seeds):
        self.seeds = seeds
        super().__init__(canonical, candidate, entries=ENTRIES, helpers=HELPERS, boundaries=STOPS,
                         no_receiver=(0x4067D0, 0x4066B0, 0x42D1B0, 0x43B1A0),
                         extra_writes=((MANAGER, MANAGER + 0x1000), (0x6FDEF0, 0x6FDEF0 + 2496),
                                       (0x6FA1FC, 0x6FA200)))
        self.manager_global = canonical.known_data_targets()["?g_battle_object_manager@th105@@3PAUBattleObjectManager@1@A"][0]
        # Indexed event23 reaches the same original zero-handle sound return.
        if canonical.target_bytes(0x6FCA98 + 23 * 4, 4) != bytes(4):
            raise ValueError("indexed event23 is not the attested zero handle")

    def actor_fields(self, case):
        return (*super().actor_fields(case), (0xF4, "I", int(case["vx_bits"], 16)),
                (0x184, "b", case["byte_184"]), (0x180, "i", case["state_180"]))

    def prepare_case(self, case):
        uc = self.engine
        state, index = self.seeds[case["seed"]]
        uc.mem_write(0x6FDEF0, state)
        uc.mem_write(0x6FA1FC, index)
        uc.mem_write(self.manager_global, struct.pack("<I", MANAGER))
        uc.mem_write(base.OWNER + 0x68C, struct.pack("<5I", 0, DEQUE, 8, 0, 3))
        uc.mem_write(DEQUE, struct.pack("<I", DEQUE + 0x100))
        uc.mem_write(DEQUE + 0x100, struct.pack("<4I", 0x30000, 0x30001, 0x30002, 0x30003))

    def instruction(self, uc, address, size, unused):
        if address == 0x42D1B0 and uc.reg_read(r.UC_X86_REG_ECX) != base.OWNER + 0x68C:
            self.failure = "texture deque receiver differs"
            uc.emu_stop()
            return
        super().instruction(uc, address, size, unused)

    def evaluate(self, case, source):
        result = super().evaluate(case, source)
        uc = self.engine
        result["texture_handles"] = bytes(uc.mem_read(MANAGER + 0xD8, 8)).hex()
        result["rng_sha256"] = hashlib.sha256(bytes(uc.mem_read(0x6FDEF0, 2496))
                                              + bytes(uc.mem_read(0x6FA1FC, 4))).hexdigest()
        return result


def audit(source=SOURCE, output=None, smoke=False):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    if hashlib.sha256(canonical.target_bytes(0x620920, 59038)).hexdigest() != "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea":
        raise ValueError("Iku root differs")
    output = output or ROOT / "build/IkuSpellActions.obj"
    receipt = base.build_source(source, output)
    cases = input_cases(smoke)
    ledger = {int(row["address"], 0): int(row["size"])
              for row in csv.DictReader((ROOT / "config/functions.csv").open())}
    generator = seed_module.Probe(canonical, pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image(),
                                  {address: ledger[address] for address in seed_module.HELPERS})
    seeds = {seed: generator.seed(seed) for seed in sorted({case["seed"] for case in cases})}
    probe = SpellProbe(canonical, base.load_object(output, root_prefix="?try_dispatch_verified_spell_action@", methods=METHODS, data_keys=base.DATA_KEYS), seeds)
    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    differences, examples = 0, []
    for case in cases:
        inputs.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = probe.evaluate(case, False), probe.evaluate(case, True)
        outputs.update(json.dumps(expected, sort_keys=True).encode())
        if expected != actual:
            differences += 1
            if len(examples) < 2:
                examples.append({"case": case, "target": expected, "source": actual})
    if (linked_pe.sha(source) != receipt["source_sha256"] or linked_pe.sha(output) != receipt["object_sha256"]
            or linked_pe.sha(base.HEADER) != receipt["header_sha256"]):
        raise ValueError("source/header/object changed during native execution")
    return {"schema": "th105-iku-spell-source-native-v1", "target_sha256": target_sha, "build": receipt,
            "cases": len(cases), "mismatch_count": differences, "examples": examples,
            "input_sha256": inputs.hexdigest(), "target_output_sha256": outputs.hexdigest(),
            "outcomes": [{"side": side, "stop": stop, "cases": count}
                         for (side, stop), count in sorted(probe.outcomes.items())],
            "source_view_aliases": probe.aliases, "unicorn_version": unicorn.__version__,
            "target_root_instructions_visited": len(probe.visited),
            "probe_sha256": linked_pe.sha(Path(__file__)), "base_probe_sha256": linked_pe.sha(Path(base.__file__)),
            "scope": "eight staged action bodies; real seed/warm/RNG/texture/deque/landing/frame/event/wave code; "
                     "RET or first spawn/effect/animation backend entry; zero event23/wave handles, unexpired frames; "
                     "second spawn/ring continuation/post-backend/whole-root/exact equivalence unproved"}


def control_source(name):
    source = SOURCE.read_text()
    needle = "unsigned offset = random_roll(400) - 200U;"
    if source.count(needle) != 1:
        raise ValueError("periodic offset control no longer has one source site")
    if name == "signed-offset":
        source = source.replace(needle, "int offset = static_cast<int>(random_roll(400)) - 200;")
    elif name == "early-offset":
        source = source.replace(needle, needle + "\n            volatile float rounded_offset = static_cast<float>(offset);")
        expression = "static_cast<float>(offset) + float_at(0xec)"
        if source.count(expression) != 1:
            raise ValueError("offset expression control is no longer unique")
        source = source.replace(expression, "rounded_offset + float_at(0xec)")
    else:
        raise ValueError("unknown spell source control")
    path = ROOT / "build" / ("iku-spells-" + name + ".cpp")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(source.replace("\n", "\r\n").encode())
    return path


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=SOURCE)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--smoke", action="store_true")
    parser.add_argument("--control", choices=("signed-offset", "early-offset"))
    args = parser.parse_args()
    source = control_source(args.control) if args.control else args.source.resolve()
    output = args.output.resolve() if args.output else (ROOT / "build" / ("IkuSpells-" + args.control + ".obj")
                                                       if args.control else None)
    result = audit(source, output, args.smoke)
    result["diagnostic_control"] = args.control
    print(json.dumps(result, indent=2))
    raise SystemExit(bool(result["mismatch_count"]))
