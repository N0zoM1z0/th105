#!/usr/bin/env python3
"""Check root496540 call ownership and actual original-animation prefixes.

Physical membership is conditional CFG evidence, not callee identity for an
indirect CALL. Runtime prefixes stop at the first opaque entry; they never
substitute a returning animation or World helper.
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

import pefile
from unicorn import x86_const as u

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "animation_sites_world", ROOT / "scripts/audit-reimu-object-world-sharing.py"
)
world = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(world)
native = world.native
ANIMATION = 0x4351C0


def cases(entries):
    for entry in entries:
        action = 802 if entry["name"] == "default" else entry["cases"][0]
        for seq, timer, counter, terminal in itertools.product(
            range(10), (0, 2), (0, 1), (False, True)
        ):
            case = dict(
                action=action,
                seq=seq,
                timer=timer,
                counter=counter,
                terminal=terminal,
                cohort="animation-sites",
            )
            if action == 825:
                case["owner_action"] = 614
            if action == 852:
                case.update(owner_action=609, owner_seq=1)
            yield case


def fields(engine):
    # Keep integer widths and float words, without interpreting x87 encodings.
    return [
        bytes(engine.mem_read(native.OWNER + offset, size)).hex()
        for offset, size in ((0x13E, 2), (0x140, 2), (0x142, 2), (0x144, 4), (0x330, 4))
    ]


class SiteProbe(native.Probe):
    def evaluate(self, case):
        self.animation_events = []
        self.pending_animation = None
        result = super().evaluate(case)
        if self.pending_animation is not None:
            raise ValueError("original animation did not return to its actual caller")
        return result

    def instruction(self, engine, address, size, unused):
        if address == ANIMATION:
            stack = engine.reg_read(u.UC_X86_REG_ESP)
            continuation = struct.unpack("<I", engine.mem_read(stack, 4))[0]
            if continuation in self.animation_returns:
                if self.pending_animation is not None:
                    raise ValueError("unexpected nested root animation")
                receiver = engine.reg_read(u.UC_X86_REG_ECX)
                if receiver != native.OWNER:
                    raise ValueError("root animation receiver differs")
                self.pending_animation = dict(
                    continuation=continuation,
                    site=self.animation_returns[continuation],
                    receiver=receiver,
                    before=fields(engine),
                )
        if (
            self.pending_animation is not None
            and address == self.pending_animation["continuation"]
        ):
            event = self.pending_animation
            self.animation_events.append(
                dict(
                    site=event["site"],
                    receiver=event["receiver"],
                    before=event["before"],
                    after=fields(engine),
                    returned_al=engine.reg_read(u.UC_X86_REG_EAX) & 255,
                )
            )
            self.pending_animation = None
        super().instruction(engine, address, size, unused)


def audit(path):
    sharing = world.audit(path)
    views = [sharing["censuses"][side] for side in ("target", "source")]
    direct_equal = sharing["direct_callee_partition_equal"]
    indirect = [
        Counter(
            tuple(row["entries"])
            for row in view["calls"].values()
            if row["target"] is None
        )
        for view in views
    ]
    animation = [
        {
            int(pc): row
            for pc, row in view["calls"].items()
            if row["target"] == ANIMATION
        }
        for view in views
    ]
    if len(animation[0]) != 22:
        raise ValueError("target animation inventory differs")
    code = native.export(path)
    image = bytearray(
        pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    math = native.load("animation_sites_math", "scripts/iku_native_math.py")
    table, lookup = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image), (0, 5489, 0xFFFFFFFF, 79, 137))
    surfaces, surface_receipt = native.surface_fixtures(bytes(image))
    probes = [
        SiteProbe(bytes(image), seeds=seeds, surfaces=surfaces),
        SiteProbe(bytes(image), code, seeds=seeds, surfaces=surfaces),
    ]
    for probe, sites in zip(probes, animation):
        for site in sites:
            encoded = (
                native.c.target_bytes(site, 5)
                if probe.start == native.A
                else code[site - native.S : site - native.S + 5]
            )
            if len(encoded) != 5 or encoded[0] != 0xE8:
                raise ValueError("animation census is not an E8 direct CALL")
            displacement = struct.unpack("<i", encoded[1:])[0]
            if site + 5 + displacement != ANIMATION:
                raise ValueError(
                    "animation return address does not identify the actual callee"
                )
        probe.animation_returns = {site + 5: site for site in sites}
    inputs = list(cases(sharing["entries"]))
    differences, event_differences = [], []
    observed = [Counter(), Counter()]
    witnesses = [{}, {}]
    endpoints = Counter()
    for index, case in enumerate(inputs):
        outputs = [probe.evaluate(case) for probe in probes]
        if outputs[0] != outputs[1]:
            differences.append(
                dict(
                    index=index,
                    input=case,
                    different=[k for k in outputs[0] if outputs[0][k] != outputs[1][k]],
                )
            )
        events = []
        for side, probe in enumerate(probes):
            normalized = []
            for event in probe.animation_events:
                site = event["site"]
                observed[side][site] += 1
                witnesses[side].setdefault(site, case)
                normalized.append({k: v for k, v in event.items() if k != "site"})
            events.append(normalized)
        if events[0] != events[1]:
            event_differences.append(dict(index=index, input=case))
        endpoints[outputs[0]["endpoint"]["kind"]] += 1
    covered = [set(sites) == set(counts) for sites, counts in zip(animation, observed)]
    accepted = (
        sharing["result"] == "equal_scoped_world_sharing"
        and all(direct_equal.values())
        and indirect[0] == indirect[1]
        and all(covered)
        and not differences
        and not event_differences
    )
    return dict(
        schema="th105-reimu-object-animation-sites-v1",
        result="equal_scoped_animation_sites" if accepted else "rejected",
        target_sha256=sharing["target_sha256"],
        object_sha256=sharing["object_sha256"],
        candidate_sha256=sharing["candidate_sha256"],
        build_provenance_verified=False,
        case_count=len(inputs),
        input_sha256=hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        differences=differences,
        animation_event_differences=event_differences,
        endpoints=dict(endpoints),
        animation_site_counts=[len(sites) for sites in animation],
        all_animation_sites_executed=covered,
        animation_sites=[
            [
                dict(
                    site=site,
                    entries=row["entries"],
                    hits=observed[side][site],
                    witness=witnesses[side].get(site),
                )
                for site, row in sorted(sites.items())
            ]
            for side, sites in enumerate(animation)
        ],
        direct_callee_partition_equal=direct_equal,
        indirect_membership_equal=indirect[0] == indirect[1],
        indirect_partitions=[
            [dict(entries=list(k), count=v) for k, v in sorted(counts.items())]
            for counts in indirect
        ],
        world_result=sharing["result"],
        lookup_initialization=lookup,
        surface_initialization=surface_receipt,
        support_sha256={
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in (
                "scripts/audit-reimu-object-animation-sites.py",
                "scripts/audit-reimu-object-world-sharing.py",
                "scripts/audit-reimu-object-scalar-actions.py",
                "scripts/audit-reimu-object-update-target.py",
                "scripts/iku_native_math.py",
                "src/characters/ReimuObjectActionStateStaging.cpp",
                "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        scope="physical25 direct-callee and indirect-site memberships over42 action destinations; admitted actual original-animation entries/returns and prefix outputs; no arbitrary vtable/indirect callee identity, opaque-return, full-root semantics or exact claim",
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
                    if k
                    in (
                        "result",
                        "reason",
                        "case_count",
                        "animation_site_counts",
                        "all_animation_sites_executed",
                        "indirect_membership_equal",
                    )
                }
            )
        )
    else:
        print(json.dumps(result, indent=2))
    return 0 if result["result"] == "equal_scoped_animation_sites" else 1


if __name__ == "__main__":
    raise SystemExit(main())
