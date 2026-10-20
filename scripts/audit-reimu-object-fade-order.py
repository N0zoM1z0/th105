#!/usr/bin/env python3
"""Audit850/853/854 field-write order and local fade returns in root496540.

The windows and native prefixes are diagnostic evidence, not full-root exactness
or proof of original source spelling, returning opaque graphs or hardware FP.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import tomllib

import pefile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "fade_tail_support", ROOT / "scripts/audit-reimu-object-999-tail.py"
)
support = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(support)
world, native = support.world, support.native
x = world.x
ACTIONS = (850, 853, 854)
FIELDS = (0xF4, 0xF8, 0x11C, 0x120, 0x124, 0x128, 0x12C)


def memory(row, offset, size=None):
    return bool(
        row.operands
        and row.operands[0].type == x.X86_OP_MEM
        and row.operands[0].mem.base == x.X86_REG_ESI
        and row.operands[0].mem.disp == offset
        and (size is None or row.operands[0].size == size)
    )


def packets(rows, switches, entries, side, read):
    by = {r.address: r for r in rows}
    result = {}
    for action in ACTIONS:
        entry = next(e for e in entries if e["name"] == str(action))
        reached = world.graphs.closure(by, entry[side], switches)
        found = []
        pairs = []
        for index, row in enumerate(rows):
            if row.address not in reached:
                continue
            if row.mnemonic == "fst" and memory(row, 0xF4, 4):
                following = rows[index + 1]
                if following.mnemonic == "fst" and memory(following, 0xF8, 4):
                    pairs.append(
                        dict(
                            start=row.address,
                            end=following.address + following.size,
                            bytes=read(
                                row.address,
                                following.address + following.size - row.address,
                            ).hex(),
                        )
                    )
            if row.mnemonic != "fcomp" or not memory(row, 0x11C, 4):
                continue
            if not any(
                r.mnemonic == "add" and memory(r, 0x113, 1)
                for r in rows[max(0, index - 3) : index]
            ):
                continue
            start = rows[index - 8]
            if start.mnemonic != "fld" or not memory(start, 0x11C, 4):
                raise ValueError("unreviewed scale-fade expression start")
            status = rows[index + 2]
            if (
                status.mnemonic != "test"
                or status.operands[0].type != x.X86_OP_REG
                or status.operands[0].reg != x.X86_REG_AH
            ):
                raise ValueError("unreviewed fade comparison status consumer")
            after = rows[index + 3 : index + 13]
            retire = [r for r in after if r.mnemonic == "add" and memory(r, 0x330, 4)]
            returns = [r for r in after if r.mnemonic == "ret"]
            kernel = None
            if (
                len(retire) == len(returns) == 1
                and retire[0].address < returns[0].address
            ):
                end = returns[0].address + returns[0].size
                kernel = dict(
                    start=start.address,
                    end=end,
                    bytes=read(start.address, end - start.address).hex(),
                )
            found.append(
                dict(
                    start=start.address,
                    compare=row.address,
                    test=status.address,
                    kernel=kernel,
                )
            )
        if len(found) != 1 or len(pairs) > 1:
            raise ValueError(
                "fade family does not have one reviewed comparison/zero pair"
            )
        result[action] = dict(**found[0], zero_pair=pairs[0] if pairs else None)
    return result


class FadeProbe(native.Probe):
    def evaluate(self, case):
        self.fade_events = []
        self.fade_case = case
        return super().evaluate(case)

    def instruction(self, engine, pc, size, unused):
        packet = self.fade_packets[self.fade_case["action"]]
        if pc == packet["start"]:
            self.fade_events.append(
                dict(kind="fade_entry", **support.floating_state(engine))
            )
        if pc == packet["test"]:
            self.fade_events.append(
                dict(
                    kind="comparison",
                    status=engine.reg_read(native.r.UC_X86_REG_EAX) & 0x4500,
                    **support.floating_state(engine),
                )
            )
        if pc in self.return_opcodes:
            stack = engine.reg_read(native.r.UC_X86_REG_ESP)
            if struct.unpack("<I", engine.mem_read(stack, 4))[0] == native.RETURN:
                self.fade_events.append(
                    dict(kind="ret", **support.floating_state(engine))
                )
        super().instruction(engine, pc, size, unused)

    def write(self, engine, access, address, size, value, unused):
        offset = address - native.OWNER
        if offset in FIELDS:
            if size != 4:
                raise ValueError("unexpected tracked field write width")
            self.fade_events.append(
                dict(kind="store", field=offset, word=value & 0xFFFFFFFF)
            )
        super().write(engine, access, address, size, value, unused)


def cases():
    scales = (
        -0.25,
        -0.0,
        0.0,
        0.1,
        0.19999998807907104,
        0.20000000298023224,
        0.20000001788139343,
        1.0,
    )
    for action, scale, alpha, control in itertools.product(
        ACTIONS, scales, (0, 9, 10, 255), (0x27F, 0x37F)
    ):
        yield dict(
            action=action,
            seq=0,
            phase=0,
            frame=2,
            timer=1,
            counter=1,
            scale=scale,
            scale_y=0.75,
            alpha=alpha,
            speed_word=250,
            cw=control,
            cohort="fade-order-fade",
        )
    for action, scale, speed, control in itertools.product(
        ACTIONS, (0.25, 0.95, 1.0, 1.4, 1.5, 1.6), (0, 250), (0x27F, 0x37F)
    ):
        yield dict(
            action=action,
            seq=0,
            phase=0,
            frame=0,
            timer=1,
            counter=1,
            scale=scale,
            scale_y=0.375,
            alpha=200,
            speed_word=speed,
            cw=control,
            cohort="fade-order-growth",
        )
    for action, phase, sequence, control in itertools.product(
        ACTIONS, (1, 6), (0, 1, 2), (0x27F, 0x37F)
    ):
        yield dict(
            action=action,
            seq=sequence,
            phase=phase,
            frame=0,
            timer=1,
            counter=1,
            scale=0.25,
            scale_y=0.375,
            alpha=200,
            speed_word=250,
            cw=control,
            cohort="fade-order-burst",
        )


def audit(path):
    sharing = world.audit(path)
    code = native.export(path)
    mapper = native.m
    root = mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "reimu-object-vslot28",
    )
    metadata = mapper.build_candidate_map(
        mapper.CoffObject(path, symbol_base=native.SYMBOL), root
    )["metadata_start"]
    facts = native.facts.audit()
    rows = [
        [
            i
            for lo, hi in native.facts.RANGES
            for i in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
        ],
        world.graphs.decode(code[:metadata], native.S),
    ]
    switches = [
        {
            int(r["instruction"], 0): dict(
                destinations=[int(d, 0) for d in r["destinations"]]
            )
            for r in facts["switches"]
        },
        {r["instruction"]: r for r in sharing["source_switches"]},
    ]
    kernels = [
        packets(
            rows[0], switches[0], sharing["entries"], "target", native.c.target_bytes
        ),
        packets(
            rows[1],
            switches[1],
            sharing["entries"],
            "source",
            lambda pc, size: code[pc - native.S : pc - native.S + size],
        ),
    ]
    if any(
        k["kernel"] is None
        or k["kernel"]["end"] - k["kernel"]["start"] != 72
        or k["zero_pair"] is None
        for k in kernels[0].values()
    ):
        raise ValueError("target fade extent/zero-store pair differs")
    equal = {
        str(action): {
            key: kernels[1][action][key] is not None
            and kernels[0][action][key]["bytes"] == kernels[1][action][key]["bytes"]
            for key in ("zero_pair", "kernel")
        }
        for action in ACTIONS
    }
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    table, receipt = native.load(
        "fade_math", "scripts/iku_native_math.py"
    ).lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    surfaces, surface_receipt = native.surface_fixtures(bytes(image))
    probes = [
        FadeProbe(bytes(image), seeds=seeds, surfaces=surfaces),
        FadeProbe(bytes(image), code, seeds=seeds, surfaces=surfaces),
    ]
    for probe, packet in zip(probes, kernels):
        probe.fade_packets = packet
    inputs = list(cases())
    differences = []
    event_differences = []
    witnesses = {}
    endpoints = Counter()
    counts = [Counter(), Counter()]
    for index, case in enumerate(inputs):
        outputs = [p.evaluate(case) for p in probes]
        events = [p.fade_events for p in probes]
        if outputs[0] != outputs[1]:
            differences.append(
                dict(
                    index=index,
                    input=case,
                    fields=[k for k in outputs[0] if outputs[0][k] != outputs[1][k]],
                )
            )
        if events[0] != events[1]:
            event_differences.append(dict(index=index, input=case, events=events))
        endpoints[outputs[0]["endpoint"]["kind"]] += 1
        for c, side in zip(counts, events):
            c.update((case["action"], e["kind"], e.get("status")) for e in side)
        key = (
            case["action"],
            case["cohort"],
            tuple((e["kind"], e.get("status")) for e in events[0]),
        )
        witnesses.setdefault(
            key, dict(input=case, events=events, endpoint=outputs[0]["endpoint"])
        )
    indirect = [
        Counter(
            tuple(v["entries"])
            for v in sharing["censuses"][side]["calls"].values()
            if v["target"] is None
        )
        for side in ("target", "source")
    ]
    coverage = all(
        any(k[0] == action and k[1] == "comparison" and v for k, v in c.items())
        for c in counts
        for action in ACTIONS
    )
    accepted = (
        all(all(v.values()) for v in equal.values())
        and coverage
        and not differences
        and not event_differences
        and sharing["result"] == "equal_scoped_world_sharing"
        and all(sharing["direct_callee_partition_equal"].values())
        and indirect[0] == indirect[1]
    )
    return dict(
        schema="th105-reimu-object-fade-order-v1",
        result="equal_scoped_fade_order" if accepted else "rejected",
        target_sha256=sharing["target_sha256"],
        object_sha256=sharing["object_sha256"],
        candidate_sha256=sharing["candidate_sha256"],
        build_provenance_verified=False,
        original_source_spelling_proven=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        kernels=kernels,
        instruction_windows_equal=equal,
        differences=differences,
        event_differences=event_differences,
        witnesses=list(witnesses.values()),
        endpoints=dict(endpoints),
        comparison_coverage=coverage,
        event_counts=[
            [
                dict(action=k[0], kind=k[1], status=k[2], count=v)
                for k, v in sorted(c.items(), key=str)
            ]
            for c in counts
        ],
        lookup_initialization=receipt,
        surface_initialization=surface_receipt,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-fade-order.py",
                "scripts/audit-reimu-object-999-tail.py",
                "scripts/audit-reimu-object-world-sharing.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/iku_native_math.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="three original action families, finite fixtures and observed field order/x87/returns/opaque frontiers;72-byte local kernels and12-byte zero stores; other guards/registers/source/TU, arbitrary aliases/resources and hardware exceptions remain unproved",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except (ValueError, KeyError) as exc:
        result = dict(result="rejected", reason=str(exc))
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, indent=2) + "\n")
        print(
            {
                k: result.get(k)
                for k in (
                    "result",
                    "reason",
                    "case_count",
                    "input_sha256",
                    "instruction_windows_equal",
                    "endpoints",
                )
            }
        )
    else:
        print(json.dumps(result, indent=2))
    return int(result["result"] != "equal_scoped_fade_order")


if __name__ == "__main__":
    raise SystemExit(main())
