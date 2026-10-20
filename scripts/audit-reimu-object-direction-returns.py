#!/usr/bin/env python3
"""Check two root496540 x87 consumers and actual original lookup returns.

These bounded instruction windows and admitted native prefixes are diagnostic
evidence, not a full-root canonical match or proof of the original C++ return
type. Opaque calls stop execution without fabricated returns.
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
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "direction_world", ROOT / "scripts/audit-reimu-object-world-sharing.py"
)
world = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(world)
native, x = world.native, world.x
SINE = 0x406360
TABLE_READ = 0x4063B9
TABLE = 0x6FE8B0


def packets(rows, calls, read):
    calls = {int(pc): row for pc, row in calls.items()}
    result = {}
    for action in ("869", "901"):
        found = []
        for index, row in enumerate(rows):
            call = calls.get(row.address)
            if not call or call["target"] != SINE or call["entries"] != [action]:
                continue
            following = []
            for instruction in rows[index + 1 : index + 45]:
                if instruction.mnemonic in ("call", "ret"):
                    break
                following.append(instruction)
            stores = [
                instruction
                for instruction in following
                if instruction.mnemonic in ("mov", "or")
                and instruction.operands[0].type == x.X86_OP_MEM
                and instruction.operands[0].mem.base == x.X86_REG_ESI
                and instruction.operands[0].mem.disp == 0x33C
                and instruction.operands[0].size == 1
            ]
            if not stores:
                continue
            end = stores[-1].address + stores[-1].size
            instructions = [i for i in following if i.address < end]
            tests = [
                i
                for i in instructions
                if i.mnemonic == "test"
                and i.operands[0].type == x.X86_OP_REG
                and i.operands[0].reg == x.X86_REG_AH
            ]
            if len(tests) != 1:
                raise ValueError("unreviewed direction comparison status consumer")
            start = row.address + row.size
            boundaries = {i.address for i in instructions} | {end}
            for instruction in instructions:
                if instruction.group(world.graphs.capstone.CS_GRP_JUMP):
                    if (
                        instruction.operands[0].type != x.X86_OP_IMM
                        or instruction.operands[0].imm not in boundaries
                    ):
                        raise ValueError("direction kernel has an external exit")
            encoded = read(start, end - start)
            found.append(
                dict(
                    action=int(action),
                    call=row.address,
                    start=start,
                    end=end,
                    test=tests[0].address,
                    size=len(encoded),
                    bytes=encoded.hex(),
                    sha256=hashlib.sha256(encoded).hexdigest(),
                )
            )
        if len(found) != 1:
            raise ValueError("direction lookup does not have one physical consumer")
        result[int(action)] = found[0]
    return result


class DirectionProbe(native.Probe):
    def evaluate(self, case):
        self.direction_case = case
        self.direction_events = []
        self.direction_pending = None
        result = super().evaluate(case)
        if self.direction_pending is not None:
            raise ValueError("original lookup/consumer witness did not complete")
        return result

    def instruction(self, engine, address, size, unused):
        if address == self.start:
            # These are object input fields, written before its first instruction.
            pointer = struct.unpack("<I", engine.mem_read(native.OWNER + 0x340, 4))[0]
            if pointer != native.entry.PARAMETERS:
                raise ValueError("direction fixture parameter pointer differs")
            engine.mem_write(
                pointer, struct.pack("<f", self.direction_case["heading_parameter"])
            )
            engine.mem_write(
                native.OWNER + 0x33C,
                bytes([self.direction_case["initial_direction"]]),
            )
        if address == SINE:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", engine.mem_read(stack, 4))[0]
            packet = self.direction_returns.get(continuation)
            if packet is not None:
                if self.direction_pending is not None:
                    raise ValueError("nested direction lookup")
                self.direction_pending = dict(
                    packet=packet,
                    angle_word=bytes(engine.mem_read(stack + 4, 4)).hex(),
                    before=bytes(engine.mem_read(native.OWNER + 0x33C, 1)).hex(),
                    returned=False,
                )
        pending = self.direction_pending
        if pending is not None:
            if address == TABLE_READ:
                index = engine.reg_read(u.UC_X86_REG_EDX)
                if not 0 <= index < 3600:
                    raise ValueError("finite direction fixture left the used table")
                pending["table_index"] = index
                pending["table_word"] = bytes(
                    engine.mem_read(TABLE + index * 4, 4)
                ).hex()
            if address == pending["packet"]["start"]:
                if "table_word" not in pending:
                    raise ValueError("lookup return lacks the actual table read")
                pending["returned"] = True
            if address == pending["packet"]["test"]:
                pending["compare_status"] = engine.reg_read(u.UC_X86_REG_EAX) & 0x4500
            if address == pending["packet"]["end"]:
                if not pending["returned"] or "compare_status" not in pending:
                    raise ValueError("incomplete original direction return/status")
                self.direction_events.append(
                    {
                        **{k: v for k, v in pending.items() if k != "packet"},
                        "direction": engine.mem_read(native.OWNER + 0x33C, 1)[0],
                    }
                )
                self.direction_pending = None
        super().instruction(engine, address, size, unused)


def cases():
    angles = (
        -180.05,
        -180.0,
        -179.95,
        -90.0,
        -3.05,
        -3.0,
        -2.95,
        -0.0,
        0.0,
        0.05,
        89.95,
        90.0,
        90.05,
        179.95,
        180.0,
        180.05,
    )
    for action, angle, counter, frontier in itertools.product(
        (869, 901), angles, (0, 1), (False, True)
    ):
        yield dict(
            action=action,
            seq=0,
            counter=counter,
            heading_parameter=angle,
            initial_direction=255 if counter else 1,
            owner_word_7c8=0 if frontier else 1,
            owner_value174=0 if frontier else 100,
            cohort="direction-return",
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
    rows = [
        [
            i
            for lo, hi in native.facts.RANGES
            for i in native.facts.decode(native.c.target_bytes(lo, hi - lo), lo)
        ],
        world.graphs.decode(code[:metadata], native.S),
    ]
    views = [sharing["censuses"][side] for side in ("target", "source")]
    kernels = [
        packets(rows[0], views[0]["calls"], native.c.target_bytes),
        packets(
            rows[1],
            views[1]["calls"],
            lambda pc, size: code[pc - native.S : pc - native.S + size],
        ),
    ]
    if any(packet["size"] != 32 for packet in kernels[0].values()):
        raise ValueError("target direction consumer extent differs")
    load = native.facts.decode(native.c.target_bytes(TABLE_READ, 7), TABLE_READ)
    if (
        len(load) != 1
        or load[0].mnemonic != "fld"
        or load[0].operands[0].type != x.X86_OP_MEM
        or load[0].operands[0].size != 4
        or load[0].operands[0].mem.index != x.X86_REG_EDX
        or load[0].operands[0].mem.scale != 4
        or load[0].operands[0].mem.disp != TABLE
    ):
        raise ValueError("original lookup table-return instruction differs")
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("direction_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[TABLE - 0x400000 : TABLE - 0x400000 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    surfaces, surface_receipt = native.surface_fixtures(bytes(image))
    probes = [
        DirectionProbe(bytes(image), seeds=seeds, surfaces=surfaces),
        DirectionProbe(bytes(image), code, seeds=seeds, surfaces=surfaces),
    ]
    for probe, side in zip(probes, kernels):
        probe.direction_returns = {packet["start"]: packet for packet in side.values()}
    inputs = list(cases())
    differences, event_differences = [], []
    observed = [Counter(), Counter()]
    endpoints = Counter()
    witnesses = {}
    for index, case in enumerate(inputs):
        outputs = [probe.evaluate(case) for probe in probes]
        events = [probe.direction_events for probe in probes]
        if any(len(side) != 1 for side in events):
            raise ValueError("direction fixture did not observe one actual consumer")
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
        for counts, side in zip(observed, events):
            event = side[0]
            counts[(case["action"], event["compare_status"], event["direction"])] += 1
        endpoint = outputs[0]["endpoint"]["kind"]
        endpoints[endpoint] += 1
        event = events[0][0]
        key = (case["action"], event["compare_status"], event["direction"], endpoint)
        witnesses.setdefault(key, dict(input=case, events=events, endpoint=endpoint))
    kernel_equal = {
        str(action): kernels[0][action]["bytes"] == kernels[1][action]["bytes"]
        for action in (869, 901)
    }
    indirect = [
        Counter(
            tuple(row["entries"])
            for row in view["calls"].values()
            if row["target"] is None
        )
        for view in views
    ]
    accepted = (
        sharing["result"] == "equal_scoped_world_sharing"
        and all(sharing["direct_callee_partition_equal"].values())
        and indirect[0] == indirect[1]
        and all(kernel_equal.values())
        and not differences
        and not event_differences
    )
    return dict(
        schema="th105-reimu-object-direction-returns-v1",
        result="equal_scoped_direction_returns" if accepted else "rejected",
        target_sha256=sharing["target_sha256"],
        object_sha256=sharing["object_sha256"],
        candidate_sha256=sharing["candidate_sha256"],
        build_provenance_verified=False,
        original_lookup_cpp_return_type_proven=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        kernels=kernels,
        kernel_bytes_equal=kernel_equal,
        differences=differences,
        event_differences=event_differences,
        observations=[
            [
                dict(action=k[0], compare_status=k[1], direction=k[2], count=v)
                for k, v in sorted(side.items())
            ]
            for side in observed
        ],
        witnesses=list(witnesses.values()),
        endpoints=dict(endpoints),
        world_result=sharing["result"],
        direct_callee_partition_equal=sharing["direct_callee_partition_equal"],
        indirect_membership_equal=indirect[0] == indirect[1],
        lookup_initialization=lookup,
        surface_initialization=surface_receipt,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-direction-returns.py",
                "scripts/audit-reimu-object-world-sharing.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/iku_native_math.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="two complete32-byte post-lookup consumers and finite original lookup entries/table reads/returns/status/byte writes/prefix outputs; opaque-return, arbitrary resources/aliases, nonfinite hardware behavior, original C++ return type and full-root exactness unproved",
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
            json.dumps(
                {
                    k: v
                    for k, v in result.items()
                    if k in ("result", "reason", "case_count", "kernel_bytes_equal")
                }
            )
        )
    else:
        print(json.dumps(result, indent=2))
    return 0 if result["result"] == "equal_scoped_direction_returns" else 1


if __name__ == "__main__":
    raise SystemExit(main())
