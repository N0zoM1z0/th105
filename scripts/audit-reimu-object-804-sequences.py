#!/usr/bin/env python3
"""Compare actual804 prefixes and the observed sequence0/1 call-site partition.

Original helper instructions run; secondary setup and other opaque entries
remain frontiers. Site coverage of this matrix is not whole-root equivalence
or canonical byte acceptance. No target code or helper return is replaced.
"""

from __future__ import annotations

import argparse
from collections import defaultdict
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct

import capstone
from capstone import x86_const as x
import pefile
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "sequence804_native", ROOT / "scripts/audit-reimu-object-scalar-actions.py"
)
native = importlib.util.module_from_spec(spec)
spec.loader.exec_module(native)

CALLEES = {
    0x496420: ("secondary_setup", 1),
    0x435160: ("orientation", 2),
    0x4963A0: ("state_six", 1),
    0x4963F0: ("secondary_release", 1),
    0x4066B0: ("mt_next", 2),
    0x4351C0: ("animation", 1),
}


def cases():
    for seq, phase, index, state, six, seed, cw in itertools.product(
        (0, 1),
        (0, 1, 2, 4, 6, 9),
        (0, 1, 127, 128, 255),
        (-32768, -1, 0, 2, 3, 32767),
        (9, 10),
        (0, 5489),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=804,
            seq=seq,
            phase=phase,
            index=index,
            state=state,
            six_counter=six,
            seed=seed,
            counter=1,
            cw=cw,
            cohort="804-phase-wrap",
        )
    for seq, counter, frame, timer, phase, cw in itertools.product(
        (0, 1), (0, 1), (0, 1), (0, 1), (0, 2, 6), (0x27F, 0x37F)
    ):
        yield dict(
            action=804,
            seq=seq,
            counter=counter,
            frame=frame,
            timer=timer,
            phase=phase,
            cw=cw,
            cohort="804-initialization",
        )
    for alpha, vy, ypos, cw in itertools.product(
        (0, 4, 5, 9, 255),
        (-0.25, 0.0, 0.25, 5.0),
        (-1.0, 0.0, 1.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=804,
            seq=2,
            counter=1,
            alpha=alpha,
            vy=vy,
            y=ypos,
            cw=cw,
            cohort="804-gravity-bounce",
        )
    for seq, phase in itertools.product((-32768, -1, 3, 32767), (5, 6)):
        yield dict(action=804, seq=seq, phase=phase, counter=1, cohort="804-widths")


def direct_returns(rows):
    return {
        row.address + row.size: (row.address, row.operands[0].imm)
        for row in rows
        if row.group(capstone.CS_GRP_CALL) and row.operands[0].type == x.X86_OP_IMM
    }


def source_rows(candidate):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(candidate, native.S))
    tables = [
        row.operands[0].mem.disp
        for row in rows
        if row.mnemonic == "jmp"
        and row.operands[0].type == x.X86_OP_MEM
        and not row.operands[0].mem.base
        and row.operands[0].mem.index
        and row.operands[0].mem.scale == 4
        and row.address < row.operands[0].mem.disp < native.S + len(candidate)
    ]
    if not tables:
        raise ValueError("missing source switch metadata")
    end = min(tables)
    rows = list(decoder.disasm(candidate[: end - native.S], native.S))
    if sum(row.size for row in rows) != end - native.S:
        raise ValueError("source callable prefix is not completely decoded")
    return rows


class SiteProbe(native.Probe):
    def evaluate(self, case):
        self.sites = defaultdict(set)
        return super().evaluate(case)

    def instruction(self, engine, address, size, unused):
        if address in CALLEES:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", engine.mem_read(stack, 4))[0]
            call = self.root_returns.get(continuation)
            if call is not None and call[1] == address:
                self.sites[address].add(call[0])
        super().instruction(engine, address, size, unused)


def audit(path):
    facts = native.facts.audit()
    candidate = native.export(path)
    target_rows = [
        row
        for lo, hi in native.facts.RANGES
        for row in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
    ]
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("sequence804_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    target, source = (
        SiteProbe(bytes(image), seeds=seeds),
        SiteProbe(bytes(image), candidate, seeds=seeds),
    )
    target.root_returns = direct_returns(target_rows)
    source.root_returns = direct_returns(source_rows(candidate))
    inputs = list(cases())
    partitions = [defaultdict(lambda: defaultdict(set)) for _ in range(2)]
    endpoints = defaultdict(int)
    for index, case in enumerate(inputs):
        expected, actual = target.evaluate(case), source.evaluate(case)
        if expected != actual:
            return dict(
                result="rejected",
                reason="804 actual prefix differs",
                case_index=index,
                input=case,
            )
        endpoints[expected["endpoint"]["kind"]] += 1
        if case["seq"] in (0, 1):
            for probe, collected in zip((target, source), partitions):
                for callee, sites in probe.sites.items():
                    collected[case["seq"]][callee].update(sites)
    serial = []
    for callee, (name, count) in CALLEES.items():
        sets = [[part[seq][callee] for seq in (0, 1)] for part in partitions]
        if any(len(sites) != count for sites in sets[0]):
            raise ValueError(f"matrix does not cover target804 {name} sites")
        shared = 1 if name == "animation" else 0
        if len(sets[0][0] & sets[0][1]) != shared:
            raise ValueError(
                f"target804 {name} sharing differs from reviewed partition"
            )
        if (
            any(len(sites) != count for sites in sets[1])
            or len(sets[1][0] & sets[1][1]) != shared
        ):
            return dict(
                result="rejected",
                reason=f"804 sequence call-site partition differs for {name}",
                case_count=len(inputs),
            )
        serial.append(
            dict(
                callee=f"0x{callee:08X}",
                name=name,
                target=[sorted(x) for x in sets[0]],
                source=[sorted(x) for x in sets[1]],
            )
        )
    return dict(
        result="equal_scoped_prefixes_and_sites",
        target_sha256=facts["target_sha256"],
        object_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        build_provenance_verified=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        endpoints=dict(endpoints),
        call_sites=serial,
        lookup_initialization=lookup,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-804-sequences.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-entry-calls.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/audit-common-fighter-animation-paths.py",
                "scripts/iku_native_math.py",
                "scripts/compare-function.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="actual804 prefixes plus observed sequence0/1 direct-call sites; opaque entries stop; no canonical or full-root equivalence claim",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (ValueError, OSError) as error:
        report = dict(result="rejected", reason=str(error))
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(
        json.dumps(
            {
                k: v
                for k, v in report.items()
                if k not in ("lookup_initialization", "call_sites", "support_sha256")
            },
            indent=2,
        )
    )
    return int(report["result"] != "equal_scoped_prefixes_and_sites")


if __name__ == "__main__":
    raise SystemExit(main())
