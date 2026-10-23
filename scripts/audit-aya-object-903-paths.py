#!/usr/bin/env python3
"""Audit Aya903 paths and real frame transitions; exact matching remains separate."""

from pathlib import Path
from collections import Counter
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "aya903_epoch_math", ROOT / "scripts/audit-aya-object-903-native.py"
)
math = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = math
spec.loader.exec_module(math)
b = math.base


class Probe(math.Probe):
    def __init__(self, table, obj=None):
        super().__init__(table, obj)
        code = bytes(self.uc.mem_read(self.start, self.size))
        window = b.c.target_bytes(0x61E829, 14)
        self.window_starts = []
        offset = code.find(window)
        while offset >= 0:
            self.window_starts.append(self.start + offset)
            offset = code.find(window, offset + 1)

    def step(self, uc, pc, size, data):
        if pc in self.window_starts:
            self.window_hits += 1
        super().step(uc, pc, size, data)

    def prepare(self, ignored):
        self.window_hits = 0
        self.gate_reads = []
        self.time_reads = []
        fields = dict(self.settings)
        seq = fields.pop("seq")
        fields.pop("cw")
        fields.pop("health")
        assert seq != 9 or fields["time"] % 3 != 0
        specs = {
            "phase": (0x180, "i"),
            "fade": (0x364, "h"),
            "alpha": (0x113, "B"),
            "time": (0x144, "i"),
            "facing": (0x104, "b"),
            "x": (0xEC, "I"),
            "y": (0xF0, "I"),
            "vx": (0xF4, "I"),
            "vy": (0xF8, "I"),
            "scale_x": (0x11C, "I"),
            "scale_y": (0x120, "I"),
            "angle": (0x12C, "I"),
            "floor": (0x370, "I"),
            "owner_action": (0x113C, "h"),
            "owner_sequence": (0x113E, "h"),
            "owner_x": (0x10EC, "I"),
            "owner_y": (0x10F0, "I"),
            "phase_index": (0x184, "B"),
            "state6": (0x384, "h"),
            "frame_timer": (0x142, "h"),
        }
        for key, value in fields.items():
            offset, fmt = specs[key]
            self.uc.mem_write(b.OWNER + offset, struct.pack("<" + fmt, value))
        self.uc.mem_write(b.OWNER + 0x110, bytes([7, 250]))

    def read(self, uc, access, address, size, value, data):
        if address == b.OWNER + 0x144:
            tag = uc.reg_read(b.r.UC_X86_REG_FPTAG)
            self.time_reads.append(
                dict(
                    width=size,
                    value=bytes(uc.mem_read(address, size)).hex(),
                    writes=len(self.writes),
                    status=uc.reg_read(b.r.UC_X86_REG_FPSW),
                    tag=tag,
                    live=[
                        None
                        if (tag >> (2 * i)) & 3 == 3
                        else uc.reg_read(getattr(b.r, "UC_X86_REG_FP" + str(i)))
                        for i in range(8)
                    ],
                )
            )
        if address == b.OWNER + 0x364:
            tag = uc.reg_read(b.r.UC_X86_REG_FPTAG)
            self.gate_reads.append(
                dict(
                    width=size,
                    value=bytes(uc.mem_read(address, size)).hex(),
                    writes=len(self.writes),
                    status=uc.reg_read(b.r.UC_X86_REG_FPSW),
                    tag=tag,
                    live=[
                        None
                        if (tag >> (2 * i)) & 3 == 3
                        else uc.reg_read(getattr(b.r, "UC_X86_REG_FP" + str(i)))
                        for i in range(8)
                    ],
                )
            )
        super().read(uc, access, address, size, value, data)

    def evaluate(self, case):
        self.settings = case
        out = b.Probe.run(self, (case["seq"], 0, case["health"], case["cw"], 20.0))
        assert out["stop"] == "ret"
        out["read_store_hits"] = self.window_hits
        out["gate_reads"] = self.gate_reads
        out["time_reads"] = self.time_reads
        return out


def case(seq, **updates):
    value = dict(
        seq=seq,
        cw=0x27F,
        health=100,
        phase=0,
        fade=0,
        alpha=255,
        time=1,
        facing=1,
        x=0x44200000,
        y=0x42C80000,
        vx=0,
        vy=0,
        scale_x=0x3F800001,
        scale_y=0x3F000001,
        angle=0x3F800000,
        floor=0xC1200000,
        owner_action=740,
        owner_sequence=1,
        owner_x=0x43A00000,
        owner_y=0x42480000,
        phase_index=0,
        state6=20,
    )
    value.update(updates)
    return value


def make_cases():
    cases = []
    cws = (
        0x07F,
        0x47F,
        0x87F,
        0xC7F,
        0x27F,
        0x67F,
        0xA7F,
        0xE7F,
        0x37F,
        0x77F,
        0xB7F,
        0xF7F,
    )
    bits = (
        0,
        0x80000000,
        1,
        0x80000001,
        0x3F800000,
        0xBF800000,
        0x7F7FFFFF,
        0xFF7FFFFF,
        0x7F800000,
        0xFF800000,
        0x7FC00123,
        0xFFC00456,
        0x7F800001,
        0xFF800002,
    )
    for seq, cw, phase, health, alpha, late in itertools.product(
        range(10), (0x27F, 0x37F), (0, 6), (0, 100), (19, 20, 255), (False, True)
    ):
        cases.append(
            case(
                seq,
                cw=cw,
                phase=phase,
                health=health,
                alpha=alpha,
                time=(59 if seq == 9 else 180) if late else 1,
            )
        )
    for seq, cw, position, value, facing in itertools.product(
        (0, 7, 9), cws, ("x", "y"), bits, (-1, 1)
    ):
        cases.append(case(seq, **dict(cw=cw, facing=facing, **{position: value})))
    for cw, vy, floor in itertools.product(cws, bits, bits):
        cases.append(case(7, cw=cw, vy=vy, floor=floor))
    for seq, cw, action, owner_seq, alpha in itertools.product(
        (4, 5),
        (0x27F, 0x37F),
        (739, 740, 741),
        (-1, 0, 1, 2, 3),
        (0, 19, 245, 246, 255),
    ):
        cases.append(
            case(seq, cw=cw, owner_action=action, owner_sequence=owner_seq, alpha=alpha)
        )
    for seq, cw, coord, value in itertools.product(
        (4, 5), cws, ("owner_x", "owner_y", "angle"), bits
    ):
        cases.append(case(seq, **dict(cw=cw, **{coord: value})))
    for seq, cw, fade, phase, alpha in itertools.product(
        (2, 3), cws, (-32768, -1, 0, 1, 32767), (0, 6), (19, 20)
    ):
        cases.append(
            case(
                seq,
                cw=cw,
                fade=fade,
                phase=phase,
                alpha=alpha,
                time=180,
                phase_index=255,
                state6=32767,
            )
        )
    for cw, scale, alpha, time in itertools.product(
        cws, bits, (0, 19, 20, 255), (-1, 0, 4, 5, 6)
    ):
        cases.append(case(8, cw=cw, scale_x=scale, alpha=alpha, time=time))
    for seq, cw, phase, timer, alpha in itertools.product(
        range(10), cws, (0, 6), (-1, 0, 2, 3, 32767), (19, 20, 255)
    ):
        cases.append(
            case(
                seq,
                cw=cw,
                phase=phase,
                frame_timer=timer,
                alpha=alpha,
                time=59 if seq == 9 else 5,
            )
        )
    return cases


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, default=ROOT / b.unit["object"])
    parser.add_argument("--control-object", type=Path)
    parser.add_argument("--output", type=Path, default=ROOT / "build/aya903-paths.json")
    args = parser.parse_args()
    cases = make_cases()
    table, receipt = math.lookup_fixture(b.c)
    objects = [args.object] + ([args.control_object] if args.control_object else [])
    probes = [Probe(table)] + [Probe(table, obj) for obj in objects]
    assert len(probes[0].window_starts) == 1, "target read/store interval is not unique"
    differences = [{str(seq): Counter() for seq in range(10)} for _ in objects]
    counts, stops, calls = Counter(), Counter(), Counter()
    hit_counts = {str(seq): [Counter() for _ in probes] for seq in range(10)}
    examples = []
    for item in cases:
        values = [p.evaluate(item) for p in probes]
        seq = str(item["seq"])
        counts.update([seq])
        stops.update([values[0]["stop"]])
        calls.update(hex(a) for a in values[0]["calls"])
        expected_hits = int(
            item["seq"] in (2, 3) and item["health"] > 0 and item["fade"] != 0
        )
        assert values[0]["read_store_hits"] == expected_hits, (
            "target interval coverage disagrees with the case"
        )
        for index, value in enumerate(values):
            hit_counts[seq][index].update([value["read_store_hits"]])
        for index, value in enumerate(values[1:]):
            changed = [key for key in values[0] if values[0][key] != value[key]]
            differences[index][seq].update(changed)
            if changed and len(examples) < 4:
                examples.append(
                    dict(
                        case=item,
                        object=index,
                        fields=changed,
                        alpha_reads=[values[0]["alpha_reads"], value["alpha_reads"]],
                        gate_reads=[values[0]["gate_reads"], value["gate_reads"]],
                        time_reads=[values[0]["time_reads"], value["time_reads"]],
                        different_actor_offsets=[
                            hex(i)
                            for i, (a, z) in enumerate(
                                zip(
                                    bytes.fromhex(values[0]["actor"]),
                                    bytes.fromhex(value["actor"]),
                                )
                            )
                            if a != z
                        ],
                    )
                )
    assert calls["0x45c1a0"] > 0 and calls["0x45c220"] > 0, (
        "actual frame/sequence transitions were not exercised"
    )
    equal = all(
        not counter for per_object in differences for counter in per_object.values()
    )
    equal = equal and all(len(p.window_starts) == 1 for p in probes)
    epoch_keys = {"alpha_reads", "gate_reads", "time_reads", "read_store_hits"}
    helper_sizes = {
        address: size for address, (size, _) in b.helpers.items()
    } | math.MATH
    report = dict(
        result="equal" if equal else "differences_or_interval_missing",
        evidence="bounded_original_code_execution_not_exact_acceptance",
        target_sha256=b.c.verify_target(),
        cases=len(cases),
        control_words=sorted({item["cw"] for item in cases}),
        counts=dict(counts),
        stops=dict(stops),
        objects=[
            dict(
                path=str(obj),
                sha256=b.lp.sha(obj),
                differences={seq: dict(counter) for seq, counter in per_object.items()},
                effect_differences={
                    seq: {
                        key: count
                        for key, count in counter.items()
                        if key not in epoch_keys
                    }
                    for seq, counter in per_object.items()
                },
                mapped_code_sha256=hashlib.sha256(
                    bytes(p.uc.mem_read(p.start, p.size))
                ).hexdigest(),
            )
            for obj, per_object, p in zip(objects, differences, probes[1:])
        ],
        read_store_window=dict(
            target="0x61e829",
            size=14,
            sha256=hashlib.sha256(b.c.target_bytes(0x61E829, 14)).hexdigest(),
            literal_matches=[len(p.window_starts) for p in probes],
            execution_hits={
                seq: [dict(counter) for counter in values]
                for seq, values in hit_counts.items()
            },
        ),
        target_calls=dict(calls),
        examples=examples,
        input_sha256=hashlib.sha256(
            json.dumps(cases, sort_keys=True).encode()
        ).hexdigest(),
        auditor_inputs={
            str(path.relative_to(ROOT)): b.lp.sha(path)
            for path in (
                Path(__file__),
                Path(math.__file__),
                Path(b.__file__),
                Path(b.entry.__file__),
                Path(b.entry.animation.__file__),
                ROOT / "scripts/native_callbacks.py",
                ROOT / "scripts/iku_native_math.py",
            )
        },
        lookup={key: value for key, value in receipt.items() if key != "trace"},
        original_helpers={
            hex(address): dict(
                size=size,
                sha256=hashlib.sha256(b.c.target_bytes(address, size)).hexdigest(),
            )
            for address, size in helper_sizes.items()
            if hex(address) in calls
        },
        scope="903 sequences0..9, no seq9 random/spawn, original root/math/frame helpers through actual RET including real frame/sequence transitions; finite heading arguments, zero-texture ten-sequence resources; varied state/scale/coordinate/owner boundaries and masked x87; byte alpha, WORD364 and DWORD144 read epochs plus per-case14-byte interval hits; no arbitrary resource/callback/unmasked exception or complete root proof",
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    if not equal:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
