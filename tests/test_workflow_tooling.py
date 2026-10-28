"""Exact acceptance invariants; live ledgers own checkpoint counts and names."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
import tomllib
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_script(name: str):
    path = ROOT / "scripts" / name
    spec = importlib.util.spec_from_file_location(name.removesuffix(".py"), path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class WorkflowToolingTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.validator = load_script("validate-tracking.py")
        cls.comparator = load_script("compare-function.py")
        cls.literals = load_script("match_literals.py")
        cls.manifest = load_script("workflow_manifest.py")
        cls.exact_replay = load_script("verify-exact-units.py")
        cls.ida_check = load_script("check-ida-mcp.py")
        cls.inventory = load_script("export-ida-inventory.py")
        cls.typed = load_script("typed-re.py")
        cls.mcp_runtime = load_script("mcp_runtime.py")
        cls.rdata_text_pointers = load_script("rank-unledgered-rdata-text-pointers.py")
        cls.origins = load_script("function-origins.py")
        cls.boundaries = load_script("audit-candidate-boundaries.py")

    def test_corrected_target_identity(self) -> None:
        manifest = self.validator.validate_target(require_bytes=False)
        self.assertEqual(manifest["target"]["size"], 3_129_344)
        self.assertEqual(
            manifest["target"]["sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(manifest["pe"]["entry_point"], "0x0068B9D2")

    def test_exact_functions_use_the_exact_origin_baseline(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            matching = {
                row["address"].upper()
                for row in csv.DictReader(stream)
                if row["status"] == "matching"
            }
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        self.assertTrue(all(
            origins[address]["evidence_id"] == "canonical-exact-authored"
            for address in matching
        ))
        rules = tomllib.loads((ROOT / "config" / "function-origin-rules.toml").read_text())
        for rule in rules["rules"]:
            if rule.get("skip_matching"):
                continue
            overlap = matching.intersection(
                str(address).upper() for address in rule.get("addresses", [])
            )
            self.assertFalse(overlap, f"{rule['id']} reclaims exact functions: {sorted(overlap)}")

    def test_origin_direct_edge_witness_replays_target_call(self) -> None:
        site = 0x401002
        target = 0x401100
        code = b"\xE8" + struct.pack("<i", target - site - 5)
        rows = [
            {"address": "0x00401000", "size": "16", "status": "matching"},
            {"address": "0x00401100", "size": "5", "status": "identified"},
        ]
        rule = {
            "id": "direct-edge-control",
            "required_direct_edges": [{
                "site": "0x00401002", "caller": "0x00401000",
                "target": "0x00401100", "caller_status": "matching",
            }],
        }

        def read_pe(address: int, size: int) -> bytes:
            self.assertEqual((address, size), (site, 5))
            return code

        self.assertEqual(
            self.origins.validate_rule_evidence(rule, rows[1:], rows, b"", read_pe),
            [],
        )
        self.assertTrue(self.origins.validate_rule_evidence(
            rule, rows[1:], rows, b"", lambda _address, _size: b"\xE9" + code[1:]
        ))
        self.assertTrue(self.origins.validate_rule_evidence(
            rule, rows[1:], rows, b"", lambda _address, _size: b"\xE8\0\0\0\0"
        ))

    def test_origin_body_witness_checks_full_candidate_extent(self) -> None:
        body = b"\x90\xC3"
        row = {"address": "0x00401100", "size": "2", "status": "identified"}
        rule = {
            "id": "body-control",
            "required_body_hashes": [{
                "address": row["address"], "size": 2,
                "sha256": hashlib.sha256(body).hexdigest(),
            }],
        }
        self.assertEqual(
            self.origins.validate_rule_evidence(
                rule, [row], [row], b"", lambda _address, _size: body
            ),
            [],
        )
        self.assertTrue(self.origins.validate_rule_evidence(
            rule, [row], [row], b"", lambda _address, _size: b"\xC3\x90"
        ))
        self.assertTrue(self.origins.validate_rule_evidence(
            rule, [row], [{**row, "size": "3"}], b"", lambda _address, _size: body
        ))

    def test_origin_tail_jump_requires_complete_alias_and_candidate_target(self) -> None:
        source = {"address": "0x00401000", "size": "5", "status": "identified"}
        target = {"address": "0x00401100", "size": "7", "status": "unclassified"}
        rule = {
            "id": "tail-alias-control",
            "required_tail_jumps": [{
                "address": source["address"], "target": target["address"],
                "target_origin": "compiler_generated",
            }],
        }
        body = b"\xE9" + struct.pack("<i", 0x401100 - 0x401000 - 5)
        verify = self.origins.validate_rule_evidence
        self.assertEqual(verify(rule, [source], [source, target], b"", lambda *_: body), [])
        self.assertTrue(verify(rule, [source], [source, target], b"", lambda *_: b"\xE8" + body[1:]))
        self.assertTrue(verify(rule, [source], [source, target], b"", lambda *_: b"\xE9\0\0\0\0"))
        self.assertTrue(verify(rule, [source], [source], b"", lambda *_: body))
        self.assertTrue(verify(rule, [source], [{**source, "size": "6"}, target], b"", lambda *_: body))

    def test_import_thunk_witness_resolves_pe_iat_name(self) -> None:
        data = bytearray(0x1500)
        struct.pack_into("<I", data, 0x3C, 0x80)
        struct.pack_into("<H", data, 0x80 + 6, 1)
        struct.pack_into("<H", data, 0x80 + 20, 0xE0)
        optional = 0x80 + 24
        struct.pack_into("<H", data, optional, 0x10B)
        struct.pack_into("<I", data, optional + 28, 0x400000)
        struct.pack_into("<I", data, optional + 96 + 8, 0x1100)
        section = optional + 0xE0
        data[section:section + 8] = b".rdata\0\0"
        struct.pack_into("<IIII", data, section + 8, 0x1000, 0x1000, 0x1000, 0x400)
        struct.pack_into("<IIIII", data, 0x500, 0x1200, 0, 0, 0x1300, 0x1400)
        struct.pack_into("<I", data, 0x600, 0x1500)
        data[0x700:0x70D] = b"KERNEL32.dll\0"
        data[0x900:0x900 + 21] = b"\0\0GetUserDefaultLCID\0"
        data[0x410:0x416] = b"\xFF\x25" + struct.pack("<I", 0x401400)
        read_pe = self.origins.pe_reader(bytes(data))
        row = {"address": "0x00401010", "size": "6", "status": "identified"}
        entry = {"address": row["address"], "iat_slot": "0x00401400",
                 "dll": "KERNEL32.dll", "name": "GetUserDefaultLCID"}
        rule = {"id": "iat-control", "required_iat_imports": [entry]}
        verify = self.origins.validate_rule_evidence
        self.assertEqual(verify(rule, [row], [row], bytes(data), read_pe), [])
        wrong = {"id": "iat-control", "required_iat_imports": [{**entry, "name": "RtlUnwind"}]}
        self.assertTrue(verify(wrong, [row], [row], bytes(data), read_pe))

    def test_msvc_runtime_relocation_targets_use_linked_x86_fields(self) -> None:
        base = 0x401000
        code = b"\x3B\x0D" + struct.pack("<I", 0x6F7A88) + b"\xE9" + struct.pack(
            "<i", 0x68FCFC - (base + 11)
        )
        self.assertEqual(
            self.origins.replayed_msvc_relocation_target(code, base, 2, 0x0006),
            0x6F7A88,
        )
        self.assertEqual(
            self.origins.replayed_msvc_relocation_target(code, base, 7, 0x0014),
            0x68FCFC,
        )
        with self.assertRaises(ValueError):
            self.origins.replayed_msvc_relocation_target(code, base, 2, 0x9999)

    def test_global_destructor_alias_requires_atexit_registration(self) -> None:
        source = {"address": "0x00401000", "size": "10", "status": "identified"}
        target = {"address": "0x00401200", "size": "12", "status": "identified"}
        register_site = 0x401100
        atexit_site = register_site + 5
        body = b"\xB9" + struct.pack("<I", 0x6E6000) + b"\xE9" + struct.pack(
            "<i", 0x401200 - 0x401000 - 10
        )
        push = b"\x68" + struct.pack("<I", 0x401000)
        call = b"\xE8" + struct.pack("<i", 0x68AF1E - atexit_site - 5)
        rule = {
            "id": "global-dtor-control",
            "required_global_dtor_aliases": [{
                "address": source["address"], "object": "0x006E6000",
                "target": target["address"], "register_site": "0x00401100",
                "atexit_site": "0x00401105", "gap_hex": "",
            }],
        }
        code = {0x401000: body, register_site: push, atexit_site: call}
        verify = self.origins.validate_rule_evidence
        self.assertEqual(
            verify(rule, [source], [source, target], b"", lambda address, _size: code[address]),
            [],
        )
        bad_code = {**code, atexit_site: b"\xE8\0\0\0\0"}
        self.assertTrue(verify(
            rule, [source], [source, target], b"", lambda address, _size: bad_code[address]
        ))

    def test_atexit_callback_pins_entire_body_and_registration(self) -> None:
        source = {"address": "0x00401000", "size": "2", "status": "identified"}
        body = b"\x90\xC3"
        register_site = 0x401100
        atexit_site = 0x401105
        callback = {
            "address": source["address"], "size": 2,
            "sha256": hashlib.sha256(body).hexdigest(),
            "register_site": "0x00401100", "atexit_site": "0x00401105",
            "gap_hex": "",
        }
        rule = {"id": "atexit-body-control", "required_atexit_callbacks": [callback]}
        code = {
            0x401000: body,
            register_site: b"\x68" + struct.pack("<I", 0x401000),
            atexit_site: b"\xE8" + struct.pack("<i", 0x68AF1E - atexit_site - 5),
        }
        verify = self.origins.validate_rule_evidence
        self.assertEqual(verify(rule, [source], [source], b"", lambda address, _size: code[address]), [])
        self.assertTrue(verify(rule, [source], [source], b"", lambda address, _size: {
            **code, 0x401000: b"\xC3\x90"
        }[address]))
        self.assertTrue(verify(rule, [source], [source], b"", lambda address, _size: {
            **code, register_site: b"\x68\0\0\0\0"
        }[address]))

    def test_atexit_cleanup_requires_pinned_free_call(self) -> None:
        address = 0x401000
        register_site = 0x401100
        atexit_site = register_site + 5
        body = b"\xE8" + struct.pack("<i", 0x6898EA - address - 5) + b"\xC3"
        row = {"address": "0x00401000", "size": "6", "status": "identified"}
        callback = {
            "address": row["address"], "size": 6,
            "sha256": hashlib.sha256(body).hexdigest(),
            "register_site": "0x00401100", "atexit_site": "0x00401105",
            "gap_hex": "", "free_call_site": row["address"],
        }
        rule = {"id": "free-callback-control", "required_atexit_callbacks": [callback]}
        code = {
            address: body,
            register_site: b"\x68" + struct.pack("<I", address),
            atexit_site: b"\xE8" + struct.pack("<i", 0x68AF1E - atexit_site - 5),
        }
        verify = self.origins.validate_rule_evidence
        self.assertEqual(verify(rule, [row], [row], b"", lambda site, _size: code[site]), [])
        wrong_call = b"\xE8" + struct.pack("<i", 0x6898E0 - address - 5) + b"\xC3"
        bad_rule = {"id": "free-callback-control", "required_atexit_callbacks": [{
            **callback, "sha256": hashlib.sha256(wrong_call).hexdigest()
        }]}
        self.assertTrue(verify(bad_rule, [row], [row], b"", lambda site, _size: {
            **code, address: wrong_call
        }[site]))

    def test_candidate_boundary_audit_keeps_branches_and_gaps_distinct(self) -> None:
        start = 0x401000
        code = b"\x74\x01\xC3\xC3"

        def read(address: int, size: int) -> bytes:
            if start <= address and address + size <= start + len(code):
                return code[address - start : address - start + size]
            raise ValueError("outside test bytes")

        result = self.boundaries.analyze_body(read, start, len(code))
        self.assertEqual(result["reachable_bytes"], 4)
        self.assertEqual(result["unreached_ranges"], [])
        self.assertEqual(len(result["return_sites"]), 2)
        self.assertEqual(result["outgoing_direct_edges"], [])

        code = b"\xEB\x02\x90\x90\xC3"
        result = self.boundaries.analyze_body(read, start, len(code))
        self.assertEqual(result["reachable_bytes"], 3)
        self.assertEqual(result["unreached_ranges"], [["0x00401002", "0x00401004"]])

    def test_cold_replay_selects_only_accepted_exact_functions(self) -> None:
        units = self.manifest.load_manifest()["units"]
        accepted = self.exact_replay.accepted_functions(units)
        expected = {
            row["address"].upper()
            for row in self.validator.rows(ROOT / "config" / "matches.csv")
            if row["status"] == "matching"
        }
        actual = set()
        for name, addresses in accepted.items():
            view = self.exact_replay.comparison_view(units[name], addresses)
            selected = {row["address"].upper() for row in view["functions"]}
            self.assertEqual(selected, {address.upper() for address in addresses})
            self.assertTrue(actual.isdisjoint(selected))
            actual.update(selected)
        self.assertEqual(actual, expected)

    def test_rtti_name_tail_is_not_a_code_pointer(self) -> None:
        blob = b"\0.?AVCSelectSV@@\0"
        offset = blob.index(b"V@@\0")
        self.assertEqual(int.from_bytes(blob[offset:offset + 4], "little"), 0x00404056)
        self.assertEqual(
            self.rdata_text_pointers.containing_msvc_rtti_name(blob, offset),
            (1, len(blob) - 1, ".?AVCSelectSV@@"),
        )
        for invalid, at in ((b"\0V@@\0", 1), (blob[:-1], offset), (blob, -1), (blob, len(blob))):
            self.assertIsNone(self.rdata_text_pointers.containing_msvc_rtti_name(invalid, at))

    def test_inventory_pagination_normalization(self) -> None:
        data, next_offset = self.inventory.normalize_page(
            {
                "data": [
                    {
                        "address": "0x401000",
                        "name": "sub_401000",
                        "size": "0x34",
                    }
                ],
                "next_offset": 1,
            }
        )
        self.assertEqual(len(data), 1)
        self.assertEqual(next_offset, 1)

    def test_attestation_byte_parser(self) -> None:
        self.assertEqual(
            self.ida_check.parse_ida_bytes("90 00 ff"), b"\x90\x00\xff"
        )

    def test_ida_mcp_runtime_is_pinned_and_project_independent(self) -> None:
        self.assertEqual(self.mcp_runtime.MCP_REQUIREMENT, "mcp==1.26.0")
        self.assertEqual(
            self.mcp_runtime.bootstrap_command(
                "/usr/bin/uv", ["scripts/check-ida-mcp.py"]
            ),
            [
                "/usr/bin/uv",
                "run",
                "--quiet",
                "--no-project",
                "--with",
                "mcp==1.26.0",
                "python3",
                "scripts/check-ida-mcp.py",
            ],
        )

    def test_ida_mcp_runtime_reports_missing_uv(self) -> None:
        with (
            mock.patch.object(
                self.mcp_runtime, "installed_mcp_version", return_value=None
            ),
            mock.patch.object(self.mcp_runtime.shutil, "which", return_value=None),
            mock.patch.dict(
                self.mcp_runtime.os.environ,
                {self.mcp_runtime.BOOTSTRAP_MARKER: ""},
            ),
        ):
            with self.assertRaisesRegex(RuntimeError, "install uv"):
                self.mcp_runtime.ensure_mcp_runtime()

    @unittest.skipUnless(
        (ROOT / "resources" / "th105.exe").is_file(), "private target is unavailable"
    )
    def test_typed_target_mapping_reads_exact_pe_bytes(self) -> None:
        data, _manifest = self.typed.verify_local_target()
        self.assertEqual(
            self.typed.target_bytes(data, 0x00401000, 8), data[0x1000:0x1008]
        )

    def test_first_mismatch_is_structured(self) -> None:
        mismatch = self.comparator.first_mismatch(
            b"\x90\x90\xc3", b"\x90\xcc\xc3", 0x401000
        )
        self.assertEqual(mismatch["offset"], 1)
        self.assertEqual(mismatch["address"], "0x00401001")

    def test_unknown_dir32_is_a_blocker(self) -> None:
        result, failure = self.comparator.failure_record(
            ValueError("unknown absolute data relocation: __ehhandler$probe")
        )
        self.assertEqual(result, "blocked")
        self.assertEqual(failure["category"], "relocation.dir32.unknown_symbol")

    def test_vc8_real_literal_symbol_contract(self) -> None:
        self.assertEqual(
            self.literals.real_literal_bytes(
                {"type": "DIR32", "symbol": "__real@3f800000"}
            ),
            bytes.fromhex("0000803f"),
        )
        self.assertEqual(
            self.literals.real_literal_bytes(
                {"type": "DIR32", "symbol": "__real@4060000000000000"}
            ),
            bytes.fromhex("0000000000006040"),
        )
        self.assertIsNone(
            self.literals.real_literal_bytes(
                {"type": "REL32", "symbol": "ordinary"}
            )
        )
        with self.assertRaisesRegex(ValueError, "must use DIR32"):
            self.literals.real_literal_bytes(
                {"type": "REL32", "symbol": "__real@3f800000"}
            )
        with self.assertRaisesRegex(ValueError, "zero addend"):
            self.literals.real_literal_bytes(
                {
                    "type": "DIR32",
                    "symbol": "__real@3f800000",
                    "addend": 4,
                }
            )
        with self.assertRaisesRegex(ValueError, "malformed __real"):
            self.literals.real_literal_bytes(
                {"type": "DIR32", "symbol": "__real@xyz"}
            )

    def test_real_literal_override_cannot_hide_value_mismatch(self) -> None:
        destination = {
            "coff_symbol": "_named_scalar",
            "address": "0x00600000",
            "data_hex": "0000000000006040",
            "addends": "0",
            "evidence": "test fixture",
            "validation": "address",
        }
        with self.assertRaisesRegex(ValueError, "source encodes .*destination declares"):
            self.literals.validate_real_literal_mapping(
                "__real@0000000000000000", "_named_scalar", destination
            )
        self.assertEqual(
            self.literals.validate_real_literal_mapping(
                "__real@4060000000000000", "_named_scalar", destination
            ),
            bytes.fromhex("0000000000006040"),
        )

    def test_rel32_accepts_only_supported_instruction_forms(self) -> None:
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\xe8\0\0\0\0", 1), "call"
        )
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\xe9\0\0\0\0", 1), "jmp"
        )
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\x0f\x84\0\0\0\0", 2), "jcc"
        )
        self.assertIsNone(
            self.comparator.rel32_operand_kind(b"\x90\0\0\0\0", 1)
        )

if __name__ == "__main__":
    unittest.main()
