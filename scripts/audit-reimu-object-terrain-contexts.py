#!/usr/bin/env python3
"""Run866 terrain requests with both real CRT conversion dispatch branches.

Supply runtime data at7039C8, observe actual surface loads, and stop at the
real first spawn entry. Neither height results nor conversion returns are
replaced. This is a bounded input-context diagnostic, not a whole-root match.
"""

from pathlib import Path
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "object_terrain_context_native",
    ROOT / "scripts/audit-reimu-object-scalar-actions.py",
)
native = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(native)
DISPATCH = 0x7039C8


def conversion_model_probe(image):
    """Observe one original CVTTSD2SI; never replace its emulated result."""
    uc = native.unicorn.Uc(native.unicorn.UC_ARCH_X86, native.unicorn.UC_MODE_32)
    uc.mem_map(
        0x400000, 0x311000, native.unicorn.UC_PROT_READ | native.unicorn.UC_PROT_EXEC
    )
    uc.mem_write(0x400000, image)
    uc.mem_map(native.STACK, 0x10000)
    sp = native.STACK + 0xFF00
    operand = struct.pack("<d", float("nan"))
    uc.mem_write(sp, operand)
    uc.reg_write(native.r.UC_X86_REG_ESP, sp)
    uc.reg_write(native.r.UC_X86_REG_MXCSR, 0x1F80)
    uc.emu_start(0x68A1B5, 0x68A1BA, count=1)
    eax = uc.reg_read(native.r.UC_X86_REG_EAX)
    mxcsr = uc.reg_read(native.r.UC_X86_REG_MXCSR)
    return {
        "instruction": "0x68a1b5",
        "bytes": image[0x28A1B5:0x28A1BA].hex(),
        "operand": operand.hex(),
        "eax": hex(eax),
        "mxcsr_input": "0x1f80",
        "mxcsr_output": hex(mxcsr),
        "hardware_expected_eax": "0x80000000",
        "hardware_expected_mxcsr_invalid": True,
        "matches_hardware_nan_contract": eax == 0x80000000 and bool(mxcsr & 1),
        "scope": "isolated original instruction, no function return or replacement result; exceptional SIMD observations require hardware qualification",
    }


class Probe(native.Probe):
    def __init__(self, image, candidate, seeds, surfaces, dispatch):
        super().__init__(image, candidate, seeds, surfaces)
        self.dispatch = dispatch
        # Runtime input data only: original code and vtable bytes stay intact.
        self.uc.mem_write(DISPATCH, struct.pack("<I", dispatch))
        self.uc.reg_write(native.r.UC_X86_REG_MXCSR, 0x1F80)
        self.initial = self.uc.context_save()
        self.uc.hook_add(native.unicorn.UC_HOOK_MEM_READ, self.surface_read)

    def instruction(self, uc, address, size, unused):
        if address == 0x435D95:
            self.conversion_eax.append(hex(uc.reg_read(native.r.UC_X86_REG_EAX)))
        super().instruction(uc, address, size, unused)

    def surface_read(self, uc, access, address, size, value, unused):
        pc = uc.reg_read(native.r.UC_X86_REG_EIP)
        if pc in (0x435D7C, 0x435D9C, 0x435DAA):
            if size != 4:
                raise ValueError("surface load is not one float word")
            self.surface_reads.append(
                {
                    "pc": hex(pc),
                    "address": hex(address),
                    "bytes": bytes(uc.mem_read(address, size)).hex(),
                    "index_eax": hex(uc.reg_read(native.r.UC_X86_REG_EAX))
                    if pc == 0x435DAA
                    else None,
                }
            )

    def evaluate(self, case):
        self.surface_reads = []
        self.conversion_eax = []
        result = super().evaluate(case)
        if result["endpoint"]["kind"] != "spawn" or len(self.surface_reads) != 1:
            raise ValueError("expected one actual surface load and first spawn entry")
        if struct.unpack("<I", self.uc.mem_read(DISPATCH, 4))[0] != self.dispatch:
            raise ValueError("CRT dispatch input changed")
        return {
            **result,
            "surface_reads": self.surface_reads,
            "crt_dispatch": self.dispatch,
            "conversion_eax": self.conversion_eax,
            "mxcsr": self.uc.reg_read(native.r.UC_X86_REG_MXCSR),
        }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    facts = native.facts.audit()
    candidate = native.export(args.object)
    image = bytes(
        native.pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    )
    surfaces, receipt = native.surface_fixtures(image)
    seeds = native.seed_fixtures(image)
    differences, observations, inputs = [], [], []
    for dispatch in (0, 1):
        target = Probe(image, None, seeds, surfaces, dispatch)
        source = Probe(image, candidate, seeds, surfaces, dispatch)
        for xpos, surface, cw in itertools.product(
            (-1.0, 0.0, 639.49, 639.5, 1279.5, float("nan")),
            surfaces,
            (0x27F, 0x37F),
        ):
            case = dict(
                action=866,
                seq=0,
                owner_action=616,
                owner_seq=5,
                state=0,
                fade_word=0,
                x=xpos,
                y=17.0,
                surface=surface,
                counter=1,
                timer=1,
                cw=cw,
                crt_dispatch=dispatch,
                mxcsr=0x1F80,
            )
            inputs.append(case)
            a, b = target.evaluate(case), source.evaluate(case)
            observations.append(
                {
                    "case": case,
                    "reads": a["surface_reads"],
                    "conversion_eax": a["conversion_eax"],
                    "mxcsr": a["mxcsr"],
                }
            )
            if a != b:
                differences.append(
                    {"case": case, "different": [key for key in a if a[key] != b[key]]}
                )
    report = {
        "case_count": len(inputs),
        "input_sha256": hashlib.sha256(
            json.dumps(inputs, sort_keys=True).encode()
        ).hexdigest(),
        "differences": differences,
        "observations": observations,
        "target_sha256": facts["target_sha256"],
        "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
        "object_sha256": hashlib.sha256(args.object.read_bytes()).hexdigest(),
        "surface_initialization": receipt,
        "dispatch_input": hex(DISPATCH),
        "mxcsr_input": hex(0x1F80),
        "mapped_dispatch_word": image[
            DISPATCH - 0x400000 : DISPATCH - 0x400000 + 4
        ].hex(),
        "conversion_model_probe": conversion_model_probe(image),
        "hardware_probe_source": "scripts/probes/cvttsd2si-hardware.cpp",
        "hardware_probe_source_sha256": hashlib.sha256(
            (ROOT / "scripts/probes/cvttsd2si-hardware.cpp").read_bytes()
        ).hexdigest(),
        "unicorn_version": native.unicorn.__version__,
        "finite_case_count": sum(case["x"] == case["x"] for case in inputs),
        "nonfinite_hardware_unqualified_count": sum(
            case["x"] != case["x"] for case in inputs
        ),
        "adjacent_surface_word": image[
            native.SURFACE - 4 - 0x400000 : native.SURFACE - 0x400000
        ].hex(),
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
        "scope": "equal emulated prefixes under both supplied7039C8 values and masked MXCSR; actual target bytes, no replacement result; exceptional SIMD conversion is hardware-unqualified when the isolated model probe disagrees; no whole-root/exact claim",
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(
        {
            key: report[key]
            for key in (
                "case_count",
                "input_sha256",
                "candidate_sha256",
                "nonfinite_hardware_unqualified_count",
                "conversion_model_probe",
                "scope",
            )
        },
        "differences",
        len(differences),
        flush=True,
    )
    return int(bool(differences))


if __name__ == "__main__":
    raise SystemExit(main())
