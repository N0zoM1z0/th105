#!/usr/bin/env python3
"""Check root496540's action999 constant lifetimes and original returning paths.

This checks bounded instruction windows and admitted native prefixes, not
full-root exactness, original TU provenance or unmasked exception behavior.
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
    "tail_world", ROOT / "scripts/audit-reimu-object-world-sharing.py"
)
world = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(world)
native, x = world.native, world.x
CONSTANTS = (0x6C3EA0, 0x6C3CC0)
FIELDS = (0xF4, 0xF8, 0x100)
GUARDS = ((0x144, 4), (0x142, 2), (0x140, 2), (0x13E, 2)) * 2


def packet(rows, calls, read):
    calls = {int(pc): value for pc, value in calls.items()}
    sites = [
        index
        for index, row in enumerate(rows)
        if row.address in calls
        and calls[row.address]["target"] == 0x4351C0
        and calls[row.address]["entries"] == ["999"]
    ]
    if len(sites) != 1:
        raise ValueError("action999 does not have one physical animation call")
    index = sites[0]
    call = rows[index]
    tail = []
    for row in rows[index + 1 :]:
        if row.mnemonic == "call":
            break
        tail.append(row)
    if not tail or tail[-1].mnemonic != "ret":
        raise ValueError("action999 final store tail is not RET-terminated")
    loads = [
        row
        for row in tail
        if row.mnemonic == "fld"
        and row.operands[0].type == x.X86_OP_MEM
        and row.operands[0].mem.disp in CONSTANTS
        and row.operands[0].size == 4
    ]
    stores = [
        row
        for row in tail
        if row.mnemonic in ("fst", "fstp")
        and row.operands[0].type == x.X86_OP_MEM
        and row.operands[0].mem.base == x.X86_REG_ESI
        and row.operands[0].mem.disp in FIELDS
        and row.operands[0].size == 4
    ]
    guards = [
        row
        for row in tail
        if row.mnemonic == "cmp"
        and row.operands[0].type == x.X86_OP_MEM
        and row.operands[0].mem.base == x.X86_REG_ESI
        and row.operands[0].mem.disp in {offset for offset, _ in GUARDS}
    ]
    cleanups = [
        (first, second)
        for first, second in zip(rows, rows[1:])
        if first.mnemonic == second.mnemonic == "fstp"
        and first.op_str == "st(1)"
        and second.op_str == "st(0)"
        and first.address > call.address
    ]
    if len(cleanups) > 1:
        raise ValueError("ambiguous final x87 cleanup")
    pair = cleanups[0] if cleanups else None
    constants_complete = [r.operands[0].mem.disp for r in loads] == list(CONSTANTS)
    groups = []
    if len(stores) == 6:
        for ordinal, group in enumerate((stores[:3], stores[3:])):
            begin = next(i for i, r in enumerate(rows) if r.address == group[0].address)
            start = rows[begin - 1].address
            end = group[-1].address + group[-1].size
            if ordinal == 1:
                start = rows[begin - 2].address
                last = next(
                    i for i, r in enumerate(rows) if r.address == group[-1].address
                )
                end = next(
                    r.address + r.size
                    for r in rows[last + 1 : last + 12]
                    if r.mnemonic == "ret"
                )
            groups.append(
                dict(start=start, end=end, bytes=read(start, end - start).hex())
            )
    return dict(
        call=call.address,
        start=call.address + call.size,
        end=tail[-1].address + tail[-1].size,
        constants_complete=constants_complete,
        constants_end=loads[-1].address + loads[-1].size
        if constants_complete
        else None,
        load_bytes=read(
            loads[0].address, loads[-1].address + loads[-1].size - loads[0].address
        ).hex()
        if loads
        else "",
        guards=[
            dict(
                pc=r.address,
                field=r.operands[0].mem.disp,
                size=r.operands[0].size,
                register=r.reg_name(r.operands[1].reg)
                if r.operands[1].type == x.X86_OP_REG
                else None,
                immediate=r.operands[1].imm
                if r.operands[1].type == x.X86_OP_IMM
                else None,
            )
            for r in guards
        ],
        stores=[
            dict(pc=r.address, mnemonic=r.mnemonic, field=r.operands[0].mem.disp)
            for r in stores
        ],
        store_groups=groups,
        cleanup=None
        if pair is None
        else dict(
            start=pair[0].address,
            end=pair[1].address + pair[1].size,
            bytes=read(
                pair[0].address,
                next(
                    r.address + r.size
                    for r in rows
                    if pair[1].address < r.address and r.mnemonic == "ret"
                )
                - pair[0].address,
            ).hex(),
        ),
    )


def floating_state(engine):
    tags = engine.reg_read(native.r.UC_X86_REG_FPTAG)
    top = (engine.reg_read(native.r.UC_X86_REG_FPSW) >> 11) & 7
    values = []
    for index in range(8):
        physical = (top + index) & 7
        tag = (tags >> (2 * physical)) & 3
        if tag != 3:
            values.append(
                dict(
                    index=index,
                    tag=tag,
                    words=list(
                        engine.reg_read(
                            getattr(native.r, "UC_X86_REG_FP" + str(physical))
                        )
                    ),
                )
            )
    return dict(top=top, tags=tags, depth=len(values), values=values)


class TailProbe(native.Probe):
    def evaluate(self, case):
        self.tail_events = []
        return super().evaluate(case)

    def instruction(self, engine, pc, size, unused):
        for guard in self.tail_packet["guards"]:
            if pc == guard["pc"]:
                left = int.from_bytes(
                    engine.mem_read(native.OWNER + guard["field"], guard["size"]),
                    "little",
                )
                right = (
                    guard["immediate"]
                    if guard["register"] is None
                    else engine.reg_read(
                        getattr(native.r, "UC_X86_REG_" + guard["register"].upper())
                    )
                )
                self.tail_events.append(
                    dict(
                        kind="guard",
                        field=guard["field"],
                        size=guard["size"],
                        left=left,
                        right=right,
                    )
                )
        if pc == 0x4351C0:
            stack = engine.reg_read(native.r.UC_X86_REG_ESP)
            if (
                struct.unpack("<I", engine.mem_read(stack, 4))[0]
                == self.tail_packet["start"]
            ):
                self.tail_events.append(
                    dict(
                        kind="animation_entry",
                        fields=bytes(engine.mem_read(native.OWNER + 0x13E, 10)).hex(),
                    )
                )
        if pc == self.tail_packet["start"]:
            self.tail_events.append(
                dict(
                    kind="animation_return",
                    fields=bytes(engine.mem_read(native.OWNER + 0x13E, 10)).hex(),
                )
            )
        marks = {self.tail_packet["constants_end"]: "constants"}
        cleanup = self.tail_packet["cleanup"]
        if cleanup is not None:
            marks.update(
                {cleanup["start"]: "cleanup_before", cleanup["end"]: "cleanup_after"}
            )
        if pc in marks:
            self.tail_events.append(dict(kind=marks[pc], **floating_state(engine)))
        if pc in self.return_opcodes:
            stack = engine.reg_read(native.r.UC_X86_REG_ESP)
            if struct.unpack("<I", engine.mem_read(stack, 4))[0] == native.RETURN:
                self.tail_events.append(dict(kind="ret", **floating_state(engine)))
        super().instruction(engine, pc, size, unused)

    def write(self, engine, access, address, size, value, unused):
        pc = engine.reg_read(native.r.UC_X86_REG_EIP)
        if (
            self.tail_packet["start"] <= pc < self.tail_packet["end"]
            and address - native.OWNER in FIELDS
        ):
            group = (
                next(
                    i
                    for i, row in enumerate(self.tail_packet["stores"])
                    if row["pc"] == pc
                )
                // 3
            )
            self.tail_events.append(
                dict(
                    kind="store",
                    group=group,
                    field=address - native.OWNER,
                    size=size,
                    word=value & 0xFFFFFFFF,
                )
            )
        super().write(engine, access, address, size, value, unused)


def cases():
    for action, sequence, counter, timer, frame, control, terminal in itertools.product(
        (999,),
        (-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9),
        (-1, 0, 1),
        (-1, 0, 1),
        (0, 1),
        (0x27F, 0x37F),
        (False, True),
    ):
        yield dict(
            action=action,
            seq=sequence,
            counter=counter,
            timer=timer,
            frame=frame,
            cw=control,
            terminal=terminal,
            cohort="999-tail",
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
    kernels = [
        packet(rows[0], sharing["censuses"]["target"]["calls"], native.c.target_bytes),
        packet(
            rows[1],
            sharing["censuses"]["source"]["calls"],
            lambda pc, size: code[pc - native.S : pc - native.S + size],
        ),
    ]
    shape = [
        k["constants_complete"]
        and [(r["field"], r["size"]) for r in k["guards"]] == list(GUARDS)
        and [r["field"] for r in k["stores"]] == list(FIELDS) * 2
        and [r["mnemonic"] for r in k["stores"]]
        == ["fst", "fst", "fst", "fst", "fstp", "fstp"]
        and len(k["store_groups"]) == 2
        and k["cleanup"] is not None
        for k in kernels
    ]
    if not shape[0]:
        raise ValueError("target action999 two-guard floating shape differs")
    windows_equal = (
        shape[1]
        and all(kernels[0][key] == kernels[1][key] for key in ("load_bytes",))
        and [r["bytes"] for r in kernels[0]["store_groups"]]
        == [r["bytes"] for r in kernels[1]["store_groups"]]
        and kernels[0]["cleanup"]["bytes"] == kernels[1]["cleanup"]["bytes"]
    )
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    table, receipt = native.load(
        "tail_math", "scripts/iku_native_math.py"
    ).lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    surfaces, surface_receipt = native.surface_fixtures(bytes(image))
    probes = [
        TailProbe(bytes(image), seeds=seeds, surfaces=surfaces),
        TailProbe(bytes(image), code, seeds=seeds, surfaces=surfaces),
    ]
    for probe, kernel in zip(probes, kernels):
        probe.tail_packet = kernel
    inputs = list(cases())
    differences, event_differences, witnesses = [], [], {}
    counts, endpoints = [Counter(), Counter()], Counter()
    store_group_counts = [Counter(), Counter()]
    for index, case in enumerate(inputs):
        outputs = [p.evaluate(case) for p in probes]
        events = [p.tail_events for p in probes]
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
        for counts_side, groups_side, side in zip(counts, store_group_counts, events):
            counts_side.update(event["kind"] for event in side)
            groups_side.update(
                event["group"] for event in side if event["kind"] == "store"
            )
        key = tuple((e["kind"], e.get("field")) for e in events[0])
        witnesses.setdefault(key, dict(input=case, events=events))
    indirect = [
        Counter(
            tuple(v["entries"])
            for v in sharing["censuses"][s]["calls"].values()
            if v["target"] is None
        )
        for s in ("target", "source")
    ]
    store_coverage = all(
        set(c) == {0, 1} and all(v > 0 for v in c.values()) for c in store_group_counts
    )
    accepted = (
        windows_equal
        and store_coverage
        and not differences
        and not event_differences
        and sharing["result"] == "equal_scoped_world_sharing"
        and all(sharing["direct_callee_partition_equal"].values())
        and indirect[0] == indirect[1]
    )
    return dict(
        schema="th105-reimu-object-999-tail-v1",
        result="equal_scoped_999_tail" if accepted else "rejected",
        target_sha256=sharing["target_sha256"],
        object_sha256=sharing["object_sha256"],
        candidate_sha256=sharing["candidate_sha256"],
        build_provenance_verified=False,
        original_source_shape_proven=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        kernels=kernels,
        shape=shape,
        instruction_windows_equal=windows_equal,
        differences=differences,
        event_differences=event_differences,
        event_counts=[dict(c) for c in counts],
        store_group_counts=[dict(c) for c in store_group_counts],
        both_store_groups_executed=store_coverage,
        witnesses=list(witnesses.values()),
        endpoints=dict(endpoints),
        direct_callee_partition_equal=sharing["direct_callee_partition_equal"],
        indirect_membership_equal=indirect[0] == indirect[1],
        lookup_initialization=receipt,
        surface_initialization=surface_receipt,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-999-tail.py",
                "scripts/audit-reimu-object-world-sharing.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/iku_native_math.py",
                "scripts/audit-reimu-object-update-target.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="action999 two store groups/constant loads/cleanup opcode windows and actual animation/memory/x87/RET prefixes; zero-register operand and whole-root bytes still differ; opaque returns/arbitrary resources/aliases and unmasked exceptions unproved",
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
                    "case_count",
                    "input_sha256",
                    "instruction_windows_equal",
                    "endpoints",
                    "event_counts",
                )
            }
        )
    else:
        print(json.dumps(result, indent=2))
    return int(result["result"] != "equal_scoped_999_tail")


if __name__ == "__main__":
    raise SystemExit(main())
