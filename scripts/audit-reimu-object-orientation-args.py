#!/usr/bin/env python3
"""Observe854's overwritten orientation arguments while running real helpers.

The first magnitude contains a ten-unit bias. A later orientation call can
erase its object writes, so final object snapshots do not establish that
argument. Observe the actual incoming receiver/float words, then continue
through original435160 code and the root's real return.
"""

from pathlib import Path
import argparse
import hashlib
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object_orientation_args_native",
    ROOT / "scripts/audit-reimu-object-scalar-actions.py",
)
native = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(native)


class Probe(native.Probe):
    def instruction(self, uc, address, size, unused):
        if address == 0x435160:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            receiver = uc.reg_read(native.r.UC_X86_REG_ECX)
            if receiver != native.OWNER + 4:
                raise ValueError(
                    "orientation receiver is outside the reviewed actor view"
                )
            self.orientation_arguments.append(
                [receiver, bytes(uc.mem_read(sp + 4, 8)).hex()]
            )
        super().instruction(uc, address, size, unused)

    def evaluate(self, case):
        self.orientation_arguments = []
        result = super().evaluate(case)
        if result["endpoint"]["kind"] != "ret" or len(self.orientation_arguments) != 2:
            raise ValueError("case did not execute two real orientation calls and RET")
        return {**result, "orientation_arguments": self.orientation_arguments}


def cases():
    ordinary = [
        case
        for case in native.sibling_projectile_cases()
        if case["cohort"] == "sibling-orientation"
    ]
    # After the word gains50 these give -1000/-900. Multiplication by the
    # observed float-valued double0.01f followed by +10 nearly cancels, making
    # a genuinely double0.01 operand distinguishable at the float argument.
    return ordinary + [
        {**case, "speed_word": speed, "cohort": "orientation-cancellation"}
        for case in ordinary
        if case["speed_word"] == -50
        for speed in (-1050, -950)
    ]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    target_facts = native.facts.audit()
    candidate = native.export(args.object)
    pe = native.pefile.PE(str(ROOT / "resources/th105.exe"))
    image = bytearray(pe.get_memory_mapped_image())
    math = native.load("object_orientation_args_math", "scripts/iku_native_math.py")
    table, receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    target = Probe(bytes(image), seeds=seeds)
    source = Probe(bytes(image), candidate, seeds)
    inputs = cases()
    differences = []
    for index, case in enumerate(inputs):
        a, b = target.evaluate(case), source.evaluate(case)
        if a != b:
            differences.append(
                {
                    "index": index,
                    "case": case,
                    "different": [key for key in a if a[key] != b[key]],
                    "target_arguments": a["orientation_arguments"],
                    "source_arguments": b["orientation_arguments"],
                }
            )
    report = {
        "case_count": len(inputs),
        "ordinary_case_count": sum(
            case["cohort"] == "sibling-orientation" for case in inputs
        ),
        "cancellation_case_count": sum(
            case["cohort"] == "orientation-cancellation" for case in inputs
        ),
        "differences": differences,
        "input_sha256": hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        "target_sha256": target_facts["target_sha256"],
        "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
        "object_sha256": hashlib.sha256(args.object.read_bytes()).hexdigest(),
        "lookup_initialization": receipt,
        "build_provenance_verified": False,
        "support_sha256": {
            str(path.relative_to(ROOT)): hashlib.sha256(path.read_bytes()).hexdigest()
            for path in (
                Path(__file__),
                ROOT / "scripts/audit-reimu-object-scalar-actions.py",
                ROOT / "src/characters/ReimuObjectActionStateStaging.cpp",
                ROOT / "src/characters/ReimuObjectActionStateStaging.hpp",
            )
        },
        "scope": "two actual incoming receiver/float-word pairs per854 input, then original435160 bodies and real root RET; no replacement result, full-root or exact claim",
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(
        {
            key: report[key]
            for key in ("case_count", "input_sha256", "candidate_sha256", "scope")
        },
        "differences",
        len(differences),
        flush=True,
    )
    return int(bool(differences))


if __name__ == "__main__":
    raise SystemExit(main())
