#!/usr/bin/env python3
"""Observe817's incoming alpha byte while executing the real null-renderer helper.

The ordinary null fixture cannot observe a discarded alpha argument through
renderer writes. Record its actual byte/receiver at496370, then execute the
original helper normally. No renderer, code patch or replacement return is used.
"""

from pathlib import Path
import argparse
import hashlib
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object_alpha_args_native", ROOT / "scripts/audit-reimu-object-scalar-actions.py"
)
native = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(native)


class Probe(native.Probe):
    def instruction(self, uc, address, size, unused):
        if address == 0x496370:
            sp = uc.reg_read(native.r.UC_X86_REG_ESP)
            self.alpha_arguments.append(
                [
                    uc.reg_read(native.r.UC_X86_REG_ECX),
                    bytes(uc.mem_read(sp + 4, 1)).hex(),
                ]
            )
        super().instruction(uc, address, size, unused)

    def evaluate(self, case):
        self.alpha_arguments = []
        result = super().evaluate(case)
        if len(self.alpha_arguments) != 1:
            raise ValueError("case did not execute exactly one real alpha helper")
        return {**result, "alpha_arguments": self.alpha_arguments}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    candidate = native.export(args.object)
    pe = native.pefile.PE(str(ROOT / "resources/th105.exe"))
    image = bytearray(pe.get_memory_mapped_image())
    math = native.load("object_alpha_args_math", "scripts/iku_native_math.py")
    table, receipt = math.lookup_fixture(native.c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    seeds = native.seed_fixtures(bytes(image))
    target, source = (
        Probe(bytes(image), seeds=seeds),
        Probe(bytes(image), candidate, seeds),
    )
    cases = [
        case
        for case in native.late_projectile_cases()
        if case["cohort"] == "late-casts" and case["seq"] == 3
    ]
    differences = []
    for n, case in enumerate(cases):
        a, b = target.evaluate(case), source.evaluate(case)
        if a != b:
            differences.append(
                {
                    "index": n,
                    "case": case,
                    "different": [key for key in a if a[key] != b[key]],
                    "target_alpha": a["alpha_arguments"],
                    "source_alpha": b["alpha_arguments"],
                }
            )
    report = {
        "case_count": len(cases),
        "differences": differences,
        "input_sha256": hashlib.sha256(
            json.dumps(cases, sort_keys=True).encode()
        ).hexdigest(),
        "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
        "object_sha256": hashlib.sha256(args.object.read_bytes()).hexdigest(),
        "lookup_initialization": receipt,
        "scope": "actual incoming low byte and receiver, then real496370 null-renderer execution and RET ABI; no nonnull-renderer or exact claim",
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(
        {
            k: report[k]
            for k in ("case_count", "input_sha256", "candidate_sha256", "scope")
        },
        "differences",
        len(differences),
        flush=True,
    )
    return int(bool(differences))


if __name__ == "__main__":
    raise SystemExit(main())
