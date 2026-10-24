#!/usr/bin/env python3
"""Check Marisa slot5C facing/launch prefixes with original native helpers.

Stop at the genuine action callback entry. This is a bounded semantic audit,
not complete callback behavior or canonical equality.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

import pefile
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE, PAYLOAD = 0x4B8280, 1771, 1788


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "marisa_control_native", ROOT / "scripts/audit-cpu-policy-paths.py")
    native = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = native
    spec.loader.exec_module(native)
    canonical = native.boundary.load_script("marisa_control_canonical", "compare-function.py")
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS, PAYLOAD)
    if hashlib.sha256(target).hexdigest() != "c5a7b3efb8411936ea2c29941773cc94813aa4fe0353a6ca8e736f587c92f54e":
        raise ValueError("reviewed complete target payload changed")
    if int.from_bytes(canonical.target_bytes(0x6C458C, 4), "little") != 0x45BFE0:
        raise ValueError("native action callback binding changed")
    unit = load_manifest()["units"]["gpt-web-marisa-control-mode"]
    function, = unit["functions"]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("configured root changed")
    targets = canonical.known_targets()
    targets.update({name: int(value, 0) for name, value in
                    (binding.rsplit("=", 1) for binding in function["rel32_targets"])})
    candidate = canonical.coff_symbol_bytes(
        object_path, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
        targets, canonical.known_data_targets())

    class Prefix(native.NativeCpuProbe):
        def locate_join(self, code, address):
            return 0  # This root has no CPU-policy join; stop at its callback.

        def step(self, uc, address):
            if self.phase == "root" and address == 0x45BFE0:
                esp = uc.reg_read(self.reg.UC_X86_REG_ESP)
                argument, = struct.unpack("<i", uc.mem_read(esp + 4, 4))
                if uc.reg_read(self.reg.UC_X86_REG_ECX) != self.OWNER:
                    raise ValueError("action callback receiver differs")
                self.callback = (address, argument)
                self.stopped = True
                uc.emu_stop()
                return
            super().step(uc, address)
            if address == ADDRESS:
                uc.mem_write(self.OWNER, struct.pack("<I", 0x6C4584))
                uc.mem_write(self.OWNER + 0x76A, struct.pack("<h", 3))

        def prefix(self, vector):
            self.seed_state = self.seed(vector["seed"])
            self.case, self.phase, self.callback = vector, "root", None
            bits = int(vector["self_x_bits"], 16)
            result = self.run((vector["action"], vector["sequence"], bits,
                               vector["facing"], vector["mode"], vector["counter"], 0x27F))
            if self.callback != (0x45BFE0, 702):
                raise ValueError("prefix did not reach the expected real callback")
            result["callback"] = self.callback
            result["actor"] = bytes(self.engine.mem_read(self.OWNER, 0x78C)).hex()
            result["rng_state"] = hashlib.sha256(
                bytes(self.engine.mem_read(0x6FDEF0, 2496)) +
                bytes(self.engine.mem_read(0x6FA1FC, 4))).hexdigest()
            return result

    image = pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image()
    engines = (Prefix(image, target, SIZE, address=ADDRESS),
               Prefix(image, candidate, len(candidate), address=ADDRESS))
    base = dict(action=700, sequence=0, other_x=900., self_y=0., other_y=0.,
                vx=0., vy=0., other_action=0, resource=1000, mode=3, facing=-1,
                counter=100, policy=0, timer=10, refresh=1, seed=0)
    count, mismatches, examples, digest = 0, 0, [], hashlib.sha256()
    for sequence in (0, 8):
        for bits in ("00000000", "80000000", "441fffff", "44200000", "44200001",
                     "7f800000", "ff800000", "7fc00000", "7f800001"):
            vector = dict(base, sequence=sequence, self_x_bits=bits)
            expected, actual = (engine.prefix(vector) for engine in engines)
            facing, = struct.unpack_from("<b", bytes.fromhex(expected["actor"]), 0x104)
            required = -1 if bits in ("44200001", "7f800000") else 1
            if facing != required:
                raise ValueError("native target did not confirm ordered facing control")
            count += 1
            digest.update(json.dumps(vector, sort_keys=True).encode())
            if expected != actual:
                mismatches += 1
                examples.append(dict(vector=vector, fields=[
                    key for key in expected if expected[key] != actual[key]]))
    return dict(diagnostic_only=True, target_sha256=identity, count=count,
                mismatch_count=mismatches, vector_sha256=digest.hexdigest(),
                source_payload_sha256=hashlib.sha256(candidate).hexdigest(), examples=examples)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    unit = load_manifest()["units"]["gpt-web-marisa-control-mode"]
    report = audit(args.object or ROOT / unit["object"])
    print(json.dumps(report, indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
