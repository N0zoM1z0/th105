#!/usr/bin/env python3
"""Observe scoped Aya820/826/853/861 scale additions against original root execution."""

from pathlib import Path
from collections import Counter
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "aya_scale_math", ROOT / "scripts/audit-aya-object-903-native.py"
)
math = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = math
spec.loader.exec_module(math)
base = math.base


def x87(uc):
    tag = uc.reg_read(base.r.UC_X86_REG_FPTAG)
    return dict(
        status=uc.reg_read(base.r.UC_X86_REG_FPSW),
        tag=tag,
        live=[
            None
            if (tag >> (2 * i)) & 3 == 3
            else uc.reg_read(getattr(base.r, "UC_X86_REG_FP" + str(i)))
            for i in range(8)
        ],
    )


def scale_read_sites(code, address):
    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cs.detail = True
    rows = list(cs.disasm(code, address))
    pairs = []
    for first, second, store in zip(rows, rows[1:], rows[2:]):
        if first.mnemonic != 'fld' or second.mnemonic != 'fadd' or store.mnemonic not in ('fst', 'fstp'):
            continue
        if first.operands[0].type != x.X86_OP_MEM or second.operands[0].type != x.X86_OP_MEM:
            continue
        a, b = first.operands[0], second.operands[0]
        if not (a.size == b.size == 4 and a.mem.base == b.mem.base == x.X86_REG_ESI
                and {a.mem.disp, b.mem.disp} == {0x11C, 0x370}):
            continue
        assert store.operands[0].type == x.X86_OP_MEM and store.operands[0].size == 4
        pairs.append(dict(start=hex(first.address), size=first.size + second.size,
                          sha256=hashlib.sha256(first.bytes + second.bytes).hexdigest(),
                          reads=[dict(pc=hex(row.address), offset=hex(row.operands[0].mem.disp))
                                 for row in (first, second)]))
    assert pairs, 'scale/rate operand pair missing'
    return pairs


class Probe(math.Probe):
    observe_position_lifetimes = False

    def __init__(self, table, obj=None, scale_read_lifetimes=False):
        super().__init__(table, obj)
        self.scale_read_lifetimes = scale_read_lifetimes
        window = base.c.target_bytes(0x61C2BA, 37)
        code = bytes(self.uc.mem_read(self.start, self.size))
        if scale_read_lifetimes:
            self.scale_read_pairs = scale_read_sites(code, self.start)
            self.scale_read_pcs = {int(row['pc'], 0): int(row['offset'], 0)
                                   for pair in self.scale_read_pairs for row in pair['reads']}
        self.position_window_starts = []
        offset = code.find(window)
        while offset >= 0:
            self.position_window_starts.append(self.start + offset)
            offset = code.find(window, offset + 1)

    def step(self, uc, pc, size, data):
        if self.observe_position_lifetimes and pc in self.position_window_starts:
            self.position_window_hits.append(pc)
        super().step(uc, pc, size, data)

    def prepare(self, case):
        action, seq, scale, growth, alpha, phase, cw = self.settings[:7]
        assert self.action_id == action
        for off, fmt, value in (
            (0x11C, "I", scale),
            (0x120, "I", 0x3F800001),
            (0x370, "I", growth),
            (0x113, "B", alpha),
            (0x144, "i", 1),
        ):
            self.uc.mem_write(base.OWNER + off, struct.pack("<" + fmt, value))
        # Owner position usesEC/F0, outside the actor's own388-byte extent.
        self.uc.mem_write(base.OWNER + 0x10EC, struct.pack("<ff", 640.0, 100.0))
        if len(self.settings) > 7:
            self.uc.mem_write(base.OWNER + 0x10F0, struct.pack("<I", self.settings[7]))
        self.scale_stores = []
        self.position_stores = []
        self.position_window_hits = []
        self.scale_operand_reads = []

    def write(self, uc, access, address, size, value, data):
        if address in (base.OWNER + 0x11C, base.OWNER + 0x120) and size == 4:
            self.scale_stores.append(
                dict(
                    offset=hex(address - base.OWNER),
                    value=value & 0xFFFFFFFF,
                    **x87(uc),
                )
            )
        if getattr(self, "observe_position_lifetimes", False) and address in (
            base.OWNER + 0xEC,
            base.OWNER + 0xF0,
            base.OWNER + 0x113,
        ):
            self.position_stores.append(
                dict(
                    offset=hex(address - base.OWNER),
                    size=size,
                    value=value & ((1 << (8 * size)) - 1),
                    **x87(uc),
                )
            )
        super().write(uc, access, address, size, value, data)

    def read(self, uc, access, address, size, value, data):
        # Alpha-read epochs remain outside this audit.
        if self.scale_read_lifetimes:
            pc = uc.reg_read(base.r.UC_X86_REG_EIP)
            if pc in self.scale_read_pcs:
                assert size == 4 and address == base.OWNER + self.scale_read_pcs[pc]
                self.scale_operand_reads.append(dict(
                    offset=hex(address - base.OWNER), value=bytes(uc.mem_read(address, size)).hex(), **x87(uc)))

    def evaluate(self, case):
        self.settings = case
        action, seq, scale, growth, alpha, phase, cw = case[:7]
        out = base.Probe.run(self, (seq, phase, 100, cw, 20.0))
        assert out["stop"] == "ret" and len(self.scale_stores) == 2
        out["scale_stores"] = self.scale_stores
        if self.scale_read_lifetimes:
            assert len(self.scale_operand_reads) == 2, 'scale pair must execute both operand reads once'
            out['scale_operand_reads'] = self.scale_operand_reads
        if getattr(self, "observe_position_lifetimes", False):
            assert len(self.position_stores) == 3
            out["position_stores"] = self.position_stores
            out["position_window_hits"] = len(self.position_window_hits)
        return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, default=ROOT / base.unit["object"])
    parser.add_argument("--control-object", type=Path)
    parser.add_argument(
        "--scale-read-lifetimes",
        action="store_true",
        help="Observe scale/rate read order and live x87; include PC24 control words",
    )
    parser.add_argument(
        "--actions",
        type=int,
        nargs="+",
        choices=(820, 826, 853, 861),
        default=(853, 861),
        help="Select audited actions; default preserves the original853/861 scope",
    )
    parser.add_argument(
        "--position-lifetimes",
        action="store_true",
        help="826/861 only: observe X/alpha/Y store x87 states, add owner-Y boundary cases, and require execution of the37-byte target interval",
    )
    parser.add_argument(
        "--diagnostic",
        action="store_true",
        help="Report all differences; do not claim target agreement",
    )
    parser.add_argument(
        "--output", type=Path, default=ROOT / "build/aya-scale-adds.json"
    )
    args = parser.parse_args()
    assert len(set(args.actions)) == len(args.actions), "duplicate action selection"
    assert not args.position_lifetimes or set(args.actions) <= {826, 861}, (
        "position lifetimes require actions826/861 only"
    )
    table, receipt = math.lookup_fixture(base.c)
    cws = (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F)
    if args.scale_read_lifetimes:
        cws = (0x7F, 0x47F, 0x87F, 0xC7F) + cws
    bits = (
        0,
        0x80000000,
        1,
        0x80000001,
        0x3F800000,
        0x3F800001,
        0xBF800000,
        0xBF800001,
        0x7F7FFFFF,
        0xFF7FFFFF,
        0x7F800000,
        0xFF800000,
        0x7FC00123,
        0xFFC00456,
        0x7F800001,
        0xFF800002,
    )
    action_sequences = [
        (action, seq)
        for action, seq in ((820, 2), (820, 3), (826, 1), (853, 2), (853, 3), (861, 1))
        if action in args.actions
    ]
    cases = [
        (action, seq, scale, growth, 20, 0, cw)
        for (action, seq), scale, growth, cw in itertools.product(
            action_sequences, bits, bits, cws
        )
    ]
    cases += [
        (action, seq, scale, growth, alpha, phase, cw)
        for (action, seq), scale, growth, alpha, phase, cw in itertools.product(
            action_sequences,
            (0x3F800001,),
            (0x3DCCCCCD,),
            (0, 15, 16, 255),
            (0, 1, 6),
            (0x27F, 0x37F),
        )
    ]
    if args.position_lifetimes:
        cases += [
            (action, 1, 0x3F800001, 0x3DCCCCCD, alpha, 0, cw, owner_y)
            for action, owner_y, alpha, cw in itertools.product(
                sorted(set(args.actions)), bits, (0, 9, 10, 255), cws
            )
        ]
    objects = [args.object] + ([args.control_object] if args.control_object else [])
    probes = {
        action: [Probe(table, scale_read_lifetimes=args.scale_read_lifetimes)]
                + [Probe(table, obj, scale_read_lifetimes=args.scale_read_lifetimes) for obj in objects]
        for action in sorted(set(args.actions))
    }
    for action, items in probes.items():
        for p in items:
            p.action_id = action
            p.observe_position_lifetimes = args.position_lifetimes
    diffs = {action: [Counter() for _ in objects] for action in probes}
    counts, calls, examples = Counter(), Counter(), []
    window_hits = {
        action: [Counter() for _ in range(len(objects) + 1)] for action in probes
    }
    for case in cases:
        action = case[0]
        values = [p.evaluate(case) for p in probes[action]]
        counts.update([str(action)])
        calls.update(hex(a) for a in values[0]["calls"])
        if args.position_lifetimes:
            for i, val in enumerate(values):
                window_hits[action][i].update([val["position_window_hits"]])
        for i, val in enumerate(values[1:]):
            fields = [k for k in values[0] if val[k] != values[0][k]]
            diffs[action][i].update(fields)
            if fields and len(examples) < 3:
                examples.append(
                    dict(
                        case=case,
                        object=i,
                        fields=fields,
                        actor_difference_offsets=[
                            hex(j)
                            for j, (a, b) in enumerate(
                                zip(
                                    bytes.fromhex(values[0]["actor"]),
                                    bytes.fromhex(val["actor"]),
                                )
                            )
                            if a != b
                        ],
                        target_writes=values[0]["writes"],
                        candidate_writes=val["writes"],
                        target_position_stores=values[0].get("position_stores"),
                        candidate_position_stores=val.get("position_stores"),
                        target=values[0]["scale_stores"],
                        candidate=val["scale_stores"],
                        target_operand_reads=values[0].get('scale_operand_reads'),
                        candidate_operand_reads=val.get('scale_operand_reads'),
                    )
                )
    window_report = None
    if args.position_lifetimes:
        window = base.c.target_bytes(0x61C2BA, 37)
        matches = [len(p.position_window_starts) for p in probes[args.actions[0]]]
        assert matches[0] == 1
        for action in probes:
            assert window_hits[action][0] == Counter({1: counts[str(action)]})
        window_report = dict(
            target="0x61c2ba",
            size=37,
            sha256=hashlib.sha256(window).hexdigest(),
            target_matches=matches[0],
            object_matches=matches[1:],
            execution_hits={
                str(action): [dict(hits) for hits in window_hits[action]]
                for action in probes
            },
        )
        if not args.diagnostic:
            assert matches[1] == 1, (
                "selected X/Y-capture/alpha/Y-store interval missing"
            )
            for action in probes:
                assert window_hits[action][1] == Counter({1: counts[str(action)]}), (
                    "selected action does not execute the target interval"
                )
    report = dict(
        target_sha256=base.c.verify_target(),
        actual_returns=len(cases),
        counts=dict(counts),
        action_sequences=action_sequences,
        diagnostic=args.diagnostic,
        selected_target_agreement=not any(items[0] for items in diffs.values()),
        position_lifetimes=args.position_lifetimes,
        scale_read_lifetimes=args.scale_read_lifetimes,
        x87_control_words=[hex(cw) for cw in cws],
        position_lifetime_window=window_report,
        objects=[
            dict(
                path=str(obj),
                sha256=base.lp.sha(obj),
                differences={str(action): dict(diffs[action][i]) for action in diffs},
            )
            for i, obj in enumerate(objects)
        ],
        examples=examples,
        target_calls=dict(calls),
        lookup={k: v for k, v in receipt.items() if k != "trace"},
        input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
        auditor_inputs={path: base.lp.sha(ROOT / path) for path in (
            'scripts/audit-aya-object-scale-adds.py', 'scripts/audit-aya-object-903-native.py',
            'scripts/audit-aya-object-901-transition.py', 'scripts/iku_native_math.py')},
        scope="Explicit action_sequences only, original root/frame returns; scale-store live x87 snapshots, actor/parameter bytes, ordered writes, calls and final x87 status/tag. Optional826/861 position lifetimes add X/alpha/Y write snapshots, owner-Y raw-bit cases and observed execution of the37-byte target interval by each action. Alpha-read epochs are not observed. Owner X finite, owner Y finite unless explicitly varied; masked x87 only; no spawn, arbitrary resources, callback/exception or full-root proof",
    )
    if args.scale_read_lifetimes:
        report['scale_read_pairs'] = [probe.scale_read_pairs for probe in probes[args.actions[0]]]
        report['selected_operand_read_agreement'] = not any(
            items[0].get('scale_operand_reads') for items in diffs.values())
        report['scope'] += '; scale-read mode additionally records actual scale/rate operand order, values and live x87'
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    if not args.diagnostic and any(d for items in diffs.values() for d in items):
        raise SystemExit(1)


if __name__ == "__main__":
    main()
