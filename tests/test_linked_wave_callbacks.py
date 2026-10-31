"""Wave callback proofs reject partial identity and untyped code-address uses."""
import copy
import hashlib
from pathlib import Path
import struct
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_pe as core
import linked_wave_callbacks as wave
from test_linked_lifecycle import MemoryPE


class WaveCallbackTests(unittest.TestCase):
    def unit(self):
        return {
            "link_wave_lifetime_callbacks": True, "link_runtime": "static",
            "link_runtime_data": ["___security_cookie"],
            "link_objects": [{"symbol": wave.GLOBAL, "size": 0x458,
                              "target": "wave_service_lifetime_object"}],
            "functions": [
                {"address": "0x00401880", "symbol_base": "??0WaveServiceLifetime@th105@@QAE@XZ",
                 "private_global": {"object": wave.GLOBAL, "role": "constructor"}},
                {"address": "0x00401910", "symbol_base": "??1WaveServiceLifetime@th105@@QAE@XZ",
                 "private_global": {"object": wave.GLOBAL, "role": "destructor"}},
            ],
        }

    def ref(self):
        c = wave.CALLBACKS[0]
        return dict(kind="wave_lifetime_callback", source_address=core.IMAGE_BASE + 0x1100,
                    address=c.address, size=c.size, symbol=c.symbol, callback_exact=True,
                    canonical_sha256=c.sha256, target_sha256=c.sha256)

    def test_flag_requires_static_real_wave_global_pair(self):
        wave.validate({})
        wave.validate(self.unit())
        changes = [
            lambda u: u.update(link_wave_lifetime_callbacks=1),
            lambda u: u.update(link_runtime="import"),
            lambda u: u.update(link_runtime_data=[]),
            lambda u: u.update(link_objects=[]),
            lambda u: u["link_objects"][0].update(size=0x454),
            lambda u: u["link_objects"][0].update(target="arbitrary"),
            lambda u: u["functions"][0].update(address="0x00401000"),
            lambda u: u["functions"][1]["private_global"].update(role="constructor"),
        ]
        for change in changes:
            u = self.unit(); change(u)
            with self.subTest(change=change), self.assertRaises(ValueError):
                wave.validate(u)

    def test_fixed_full_callback_identity_cannot_be_substituted(self):
        good = self.ref()
        self.assertTrue(wave.typed_push_allowed(good))
        for key, value in [("address", 0x401000), ("size", 16),
                           ("symbol", "?arbitrary@@YAXXZ"), ("callback_exact", 1),
                           ("canonical_sha256", "0" * 64), ("target_sha256", "1" * 64),
                           ("kind", "literal")]:
            bad = dict(good, **{key: value})
            with self.subTest(key=key):
                self.assertFalse(wave.typed_push_allowed(bad))

    def test_only_push_and_exact_highlow_are_supported(self):
        ref = self.ref(); start = core.IMAGE_BASE + 0x1000
        raw = b"\x68" + struct.pack("<I", ref["source_address"]) + b"\x58\xc3"
        result, _, refs = core.canonicalize(
            raw, start, 0x401000, [], lambda _: None,
            (core.IMAGE_BASE, core.IMAGE_BASE + 0x5000), (0x400000, 0x800000),
            internal_refs=[ref])
        self.assertEqual(result[1:5], struct.pack("<I", ref["address"]))
        pe = MemoryPE()
        with self.assertRaises(ValueError):
            core.validate_body_relocations(pe, start, len(raw), refs)
        pe.relocations(0x1001)
        core.validate_body_relocations(pe, start, len(raw), refs)
        for bad in [b"\xb8" + raw[1:5] + b"\xc3",
                    b"\xa1" + raw[1:5] + b"\xc3",
                    b"\xa3" + raw[1:5] + b"\xc3"]:
            with self.subTest(body=bad), self.assertRaises(ValueError):
                core.canonicalize(bad, start, 0x401000, [], lambda _: None,
                    (core.IMAGE_BASE, core.IMAGE_BASE + 0x5000), (0x400000, 0x800000),
                    internal_refs=[ref])

    def global_proof(self):
        return dict(target_address=0x702288, size=0x458, target_initializer=0x6BE6F0,
                    target_initializer_slot=0x6C035C, target_callback=0x6BEDC0,
                    regions=[dict(kind=k, size=n, canonical_sha256="a" * 64,
                                  target_sha256="a" * 64)
                             for k, n in [("initializer", 17), ("atexit callback", 5)]])

    def test_global_proof_requires_both_full_regions(self):
        wave._validate_global_witness(self.global_proof())
        changes = [lambda p: p.update(regions=[]),
                   lambda p: p.update(target_address=0x70228C),
                   lambda p: p["regions"][0].update(size=16),
                   lambda p: p["regions"][0].update(canonical_sha256=None, target_sha256=None),
                   lambda p: p["regions"][1].update(target_sha256="b" * 64)]
        for change in changes:
            proof = self.global_proof(); change(proof)
            with self.subTest(change=change), self.assertRaises(ValueError):
                wave._validate_global_witness(proof)

    def fixture(self):
        pe, target = MemoryPE(), MemoryPE(0x400000)
        pe.put(0x1000, b"\xc3" + b"\xcc" * 15)
        target.put(0x1000, b"\xc3")
        symbol = "??0Fixture@game@@QAE@XZ"; owner = "fixture.ltcg.obj"
        spec = wave.Callback(symbol, 0x401000, 1, hashlib.sha256(b"\xc3").hexdigest())
        functions = {core.IMAGE_BASE + 0x1000: [(symbol, owner)],
                     core.IMAGE_BASE + 0x1010: [("_next", owner)]}
        ledger = {"0x00401000": {"status": "matching", "size": "1", "source_file": wave.SOURCE}}
        return spec, pe, target, functions, owner, ledger

    def verify(self, f):
        spec, pe, target, functions, owner, ledger = f
        return wave._verify_callback(spec, pe, target, functions, {}, owner, {}, [], [],
            [], [], ledger, lambda a, n: target.get_data(a - 0x400000, n))

    def test_callback_replay_covers_whole_source_and_target(self):
        f = self.fixture(); result = self.verify(f)
        self.assertTrue(result["callback_exact"])
        for which in ("source", "target", "extent"):
            f = self.fixture()
            if which == "source":
                f[1].put(0x1000, b"\x90\xc3")
            elif which == "target":
                f[2].put(0x1000, b"\x90")
            else:
                f[5]["0x00401000"]["size"] = "2"
            with self.subTest(which=which), self.assertRaises(ValueError):
                self.verify(f)

    def test_callback_requires_existing_exact_source_and_unique_cil(self):
        changes = [lambda f: f[5]["0x00401000"].update(status="implemented"),
                   lambda f: f[5]["0x00401000"].update(source_file="src/other.cpp"),
                   lambda f: f[3].update({core.IMAGE_BASE + 0x1000: [(f[0].symbol, "libcmt:x.obj")]}),
                   lambda f: f[3][core.IMAGE_BASE + 0x1000].append(("_alias", f[4]))]
        for change in changes:
            f = self.fixture(); change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.verify(f)

    def test_required_callback_cleanup_failure_is_never_waived(self):
        f = list(self.fixture()); old = f[0]
        f[0] = wave.Callback(old.symbol, old.address, old.size, old.sha256,
                             ("0x00402000", "0x00403000"))
        with patch("linked_lifecycle.cleanup_eh", side_effect=ValueError("bad cleanup")):
            with self.assertRaisesRegex(ValueError, "bad cleanup"):
                self.verify(f)

    def test_wave_witness_does_not_accept_missing_provider_source(self):
        u = self.unit()
        with patch("workflow_manifest.source_dependencies", return_value=set()):
            with self.assertRaisesRegex(ValueError, "reviewed provider"):
                wave.witnesses(u, None, None, {}, {}, "owner", {}, [], [], [],
                               [], {}, lambda a, n: b"", {})
