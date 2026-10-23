#!/usr/bin/env python3
"""Check Aya817/822 normal control flow across observed fade-tail sharing changes."""

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import tomllib

import linked_pe as lp
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]


def load_flow():
    spec = importlib.util.spec_from_file_location(
        "aya_fade_sharing_flow", ROOT / "scripts/audit-aya-object-normal-flow.py"
    )
    flow = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = flow
    spec.loader.exec_module(flow)
    flow.c = lp.comparator()
    flow.c.verify_target()
    flow.f = load_manifest()["units"]["gpt-web-aya-object-vslot28-full-root"][
        "functions"
    ][0]
    flow.mapper = flow.load(
        "aya_fade_sharing_coff", "scripts/compare-giant-action-switches.py"
    )
    flow.world = flow.load(
        "aya_fade_sharing_switches", "scripts/audit-reimu-object-world-sharing.py"
    )
    flow.root = flow.mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "aya-object-vslot28",
    )
    return flow


def primary(flow, packet):
    surfaces = [
        sw for sw in packet["switches"].values() if sw["checked_maximum"] == 198
    ]
    assert len(surfaces) == 1
    switch = surfaces[0]
    offset = switch["index_table"] - flow.S
    indices = packet["code"][offset : offset + 199]
    return switch, indices


def compare(flow, old, new, starts, boundaries=()):
    """Instruction product graph, with two explicit integer-flag transformations."""
    pending = [(starts[0], starts[1], None, ())]
    seen, moved, inverted = set(), [], []
    boundary_pairs = set(boundaries)
    left_boundaries = {a for a, _ in boundary_pairs}
    right_boundaries = {b for _, b in boundary_pairs}
    while pending:
        a, b, deferred, floating_pairs = pending.pop()
        if a in left_boundaries or b in right_boundaries:
            assert (a, b) in boundary_pairs and deferred is None
            continue
        a, b = flow.contract(old, a), flow.contract(new, b)
        key = (a, b, deferred)
        if key in seen:
            continue
        seen.add(key)
        left, right = old["by"][a], new["by"][b]
        left_label, right_label = flow.label(old, left), flow.label(new, right)

        if deferred is not None:
            if right_label == "cmp al, 0x14":
                assert len(floating_pairs) == 11, "unreviewed compare movement"
                moved.append(
                    dict(
                        previous_compare=hex(deferred),
                        candidate_compare=hex(b),
                        matched_floating_instructions=[
                            dict(previous=hex(u), candidate=hex(v), label=label)
                            for u, v, label in floating_pairs
                        ],
                        guard="AL and CPU EFLAGS are not written by any intervening instruction; no call, integer instruction or branch is crossed",
                    )
                )
                pending.append((a, b + right.size, None, ()))
                continue
            assert left.mnemonic == right.mnemonic
            assert left.mnemonic in ("fld", "fadd", "fstp", "fst", "fmul")
            forbidden = {
                flow.x.X86_REG_EFLAGS,
                flow.x.X86_REG_EAX,
                flow.x.X86_REG_AX,
                flow.x.X86_REG_AL,
                flow.x.X86_REG_AH,
            }
            for row in (left, right):
                assert not forbidden.intersection(row.regs_access()[1])
            floating_pairs += ((a, b, left_label),)
            assert len(floating_pairs) <= 11

        if left_label != right_label:
            if left.mnemonic == "jb" and right.mnemonic == "jae":
                assert deferred is None
                assert left_label == "jb <branch>" and right_label == "jae <branch>"
                inverted.append(dict(previous=hex(a), candidate=hex(b), flags="CF"))
                pending.extend(
                    (u, v, None, ())
                    for u, v in zip(
                        flow.edges(old, left), reversed(flow.edges(new, right))
                    )
                )
                continue
            if (
                left_label == "cmp al, 0x14"
                and right_label == "fadd dword ptr [esi + 0x370]"
            ):
                assert deferred is None
                pending.append((a + left.size, b, a, ()))
                continue
            raise AssertionError((hex(a), hex(b), left_label, right_label))

        if a in old["switches"] or b in new["switches"]:
            su, iu = primary(flow, old)
            sv, iv = primary(flow, new)
            assert a in old["switches"] and b in new["switches"]
            assert old["switches"][a] == su and new["switches"][b] == sv
            assert iu == iv
        eu, ev = flow.edges(old, left), flow.edges(new, right)
        assert len(eu) == len(ev)
        pending.extend((u, v, deferred, floating_pairs) for u, v in zip(eu, ev))
    return dict(
        paired_states=len(seen), deferred_compares=moved, inverted_branches=inverted
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("previous", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument(
        "--output", type=Path, default=ROOT / "build/aya-fade-sharing.json"
    )
    args = parser.parse_args()
    flow = load_flow()
    old, new = flow.packet(args.previous), flow.packet(args.candidate)
    old_switch, old_indices = primary(flow, old)
    new_switch, new_indices = primary(flow, new)
    assert old_indices == new_indices
    boundaries = list(zip(old_switch["destinations"], new_switch["destinations"]))
    assert len(old_switch["destinations"]) == len(new_switch["destinations"]) == 33
    entry = compare(flow, old, new, (flow.S, flow.S), boundaries)
    assert not entry["deferred_compares"] and not entry["inverted_branches"]
    actions = {}
    for action in (817, 822):
        index = old_indices[action - 800]
        assert old_indices.count(index) == 1
        actions[str(action)] = compare(flow, old, new, boundaries[index])
    report = dict(
        evidence="scoped_normal_control_flow_not_canonical_acceptance",
        target_sha256=flow.c.verify_target(),
        objects=[
            dict(
                path=str(path),
                object_sha256=lp.sha(path),
                mapped_base=hex(flow.S),
                mapped_size=len(packet["code"]),
                mapped_sha256=hashlib.sha256(packet["code"]).hexdigest(),
            )
            for path, packet in ((args.previous, old), (args.candidate, new))
        ],
        entry_graph=entry,
        actions=actions,
        scope="Equal instruction labels, ordered edges and root entry ABI/dispatch for817/822; direct internal JMPs contracted; only reported JB/JAE edge inversion and the checked AL20 compare movement across11 identical floating instructions; external calls assumed normal return with identical ABI/behavior. No x87 input-order allowance, asynchronous observer, unmasked-exception, target semantic, other-action or whole-root proof; no exact credit.",
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
