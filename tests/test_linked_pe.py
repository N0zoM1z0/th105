"""Fail-closed linked-code tests; no game bytes or proprietary tools needed."""
import json
import copy
from pathlib import Path
import struct
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_pe as linked


class VTablePe:
    """Small PE memory model with separate code, read-only and writable data."""
    def __init__(self, base=linked.IMAGE_BASE):
        self.OPTIONAL_HEADER = SimpleNamespace(ImageBase=base)
        self.data = bytearray(0x4000)
        self.sections = [SimpleNamespace(VirtualAddress=rva, Misc_VirtualSize=0x1000,
            Characteristics=flags, Name=name) for rva, flags, name in [(0x1000, 0x60000020, b".text"),
                (0x2000, 0x40000040, b".rdata"), (0x3000, 0xc0000040, b".data")]]

    def get_section_by_rva(self, rva):
        return next((s for s in self.sections if s.VirtualAddress <= rva < s.VirtualAddress + s.Misc_VirtualSize), None)

    def get_data(self, rva, size):
        return bytes(self.data[rva:rva + size])


class LinkedPeTests(unittest.TestCase):
    start = linked.IMAGE_BASE + 0x1000
    target = 0x401000
    game = (0x400000, 0x706000)
    image = (linked.IMAGE_BASE, linked.IMAGE_BASE + 0x5000)

    def test_zero_exit_linker_warning_rejects_build_phase(self):
        # Actual /Os CIL trial: link.exe returned zero despite an unhandled
        # CRT initialization section in the NOENTRY comparison image.
        warning = ("msvcrt.lib(cpu_disp.obj) : warning LNK4210: .CRT section "
                   "exists; there may be unhandled static initializers or terminators\n")
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "candidate.link.log"
            log.write_text(warning)
            with self.assertRaisesRegex(RuntimeError, "warning LNK4210") as caught:
                linked.check_build_phase("link", 0, log)
            self.assertIn(str(log), str(caught.exception))

    def test_link_diagnostics_and_nonzero_status_fail_independently(self):
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "candidate.link.log"
            for status, output in [(1, ""),
                    (0, "owner.obj : error LNK2001: unresolved external symbol _missing\n"),
                    (0, "LINK : Warning LNK4098: conflicting default library\n"),
                    (0, "context.cpp : fatal error C1083: cannot open include file\n")]:
                with self.subTest(status=status, output=output):
                    log.write_text(output)
                    with self.assertRaises(RuntimeError):
                        linked.check_build_phase("link", status, log)

    def test_clean_build_phase_log_passes(self):
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "candidate.link.log"
            log.write_text("Generating code\nFinished generating code\n")
            linked.check_build_phase("link", 0, log)

    def test_vtable_entry_contract_preserves_a_real_exported_root(self):
        f = self.private_fixture()
        child = f["unit"]["functions"][1]
        symbol = "??_7Pool@game@@6B@"
        child.pop("private_from")
        child.update(symbol_base="??_GPool@game@@UAEPAXI@Z", vtable_entry=symbol)
        unit = {**f["unit"], "profile": linked.PROFILE, "object": "build/test.dll",
                "link_data_targets": [], "link_vtables": [{"symbol": symbol,
                    "target": "pool", "entry": child["symbol_base"] + "=0x00402000",
                    "target_type_name": ".?AVOriginalPool@@"}]}
        linked.validate_contract(unit, {"pool"})
        changes = [lambda u: u["functions"][1].update(vtable_entry="missing"),
                   lambda u: u["functions"][1].update(export_name="_alias"),
                   lambda u: u["functions"][1].update(private_from={"caller": "0x00401000", "site": "0x00401000"}),
                   lambda u: u["link_vtables"][0].update(entry=child["symbol_base"] + "=0x00403000"),
                   lambda u: u.update(functions=[u["functions"][1]]),
                   lambda u: u["functions"][0].update(private_from={"caller": "0x00402000", "site": "0x00402000"})]
        for change in changes:
            bad = copy.deepcopy(unit); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError):
                linked.validate_contract(bad, {"pool"})

    def test_vtable_entry_requires_the_attested_pointer_and_only_its_compiler_alias(self):
        symbol = "??_GPool@game@@UAEPAXI@Z"
        vector_alias = symbol.replace("??_G", "??_E", 1)
        function = {"address": "0x00402000", "symbol_base": symbol,
                    "vtable_entry": "??_7Pool@game@@6B@"}
        table = {"symbol": function["vtable_entry"], "entry_symbol": symbol,
                 "entry_target": 0x402000, "source_entry": self.start}
        functions = {self.start: [(symbol, "Pool.ltcg.obj"),
                                  (vector_alias, "i CIL library: CIL module")]}
        self.assertEqual(linked.source_function_start(function, functions, {},
            "Pool.ltcg.obj", [table]), self.start)
        bad_tables = [[], [table, table], [{**table, "source_entry": self.start + 4}],
                      [{**table, "entry_target": 0x403000}], [{**table, "entry_symbol": "_unrelated"}]]
        for tables in bad_tables:
            with self.subTest(tables=tables), self.assertRaises(ValueError):
                linked.source_function_start(function, functions, {}, "Pool.ltcg.obj", tables)
        for aliases in [[(symbol, "Other.obj")], [(symbol, "Pool.ltcg.obj"), ("_unrelated", "Pool.ltcg.obj")],
                        [(symbol, "Pool.ltcg.obj"), (vector_alias, "Other.obj")],
                        [(symbol, "Pool.ltcg.obj"), (vector_alias, "Pool.ltcg.obj"), (vector_alias, "Pool.ltcg.obj")]]:
            with self.subTest(aliases=aliases), self.assertRaises(ValueError):
                linked.source_function_start(function, {self.start: aliases}, {}, "Pool.ltcg.obj", [table])
        with self.assertRaises(ValueError):
            linked.source_function_start(function, functions, {"_alias": self.start}, "Pool.ltcg.obj", [table])

    def canonical(self, code, bindings=None, resolve=None):
        return linked.canonicalize(code, self.start, self.target, bindings or [],
            resolve or (lambda address: (_ for _ in ()).throw(ValueError("unknown call"))), self.image, self.game)

    def test_preserved_members_need_distinct_public_normal_abis(self):
        symbol = "?lookup@Pool@game@@QAEPAPAXI@Z"
        unit = {"profile": linked.PROFILE, "object": "build/test.dll", "link_data_targets": [],
                "functions": [{"address": "0x00401000", "symbol_base": "?root@Pool@game@@QAEXXZ"}],
                "preserve_public_members": [symbol]}
        linked.validate_contract(unit, set())
        for preserved in [[symbol, symbol], ["_cdecl"], ["??_GPool@@UAEPAXI@Z"],
                          ["?private@Pool@@AAEXXZ"], [{}], {}, [unit["functions"][0]["symbol_base"]]]:
            with self.subTest(preserved=preserved), self.assertRaises(ValueError):
                linked.validate_contract({**unit, "preserve_public_members": preserved}, set())

    def test_preserved_member_witness_requires_a_real_owned_export(self):
        symbol = "?lookup@Pool@game@@QAEPAPAXI@Z"
        unit = {"preserve_public_members": [symbol]}
        pe = VTablePe(); pe.data[0x1000:0x1010] = b"\xc2\x04\x00" + b"\xcc" * 13
        functions = {self.start: [(symbol, "Ctx.ltcg.obj")], self.start + 16: [("_next", "Ctx.ltcg.obj")]}
        exports = {symbol: self.start}
        result = linked.preserved_member_witnesses(unit, pe, functions, exports, "Ctx.ltcg.obj")
        self.assertEqual(result[0]["source_address"], self.start)
        for bad_functions, bad_exports in [(functions, {}), (functions, {symbol: self.start + 1}),
                ({**functions, self.start: [(symbol, "Other.obj")]}, exports),
                ({**functions, self.start: [(symbol, "Ctx.ltcg.obj"), ("_alias", "Ctx.ltcg.obj")]}, exports)]:
            with self.assertRaises(ValueError):
                linked.preserved_member_witnesses(unit, pe, bad_functions, bad_exports, "Ctx.ltcg.obj")
        pe.sections[0].Characteristics = 0x40000040
        with self.assertRaises(ValueError):
            linked.preserved_member_witnesses(unit, pe, functions, exports, "Ctx.ltcg.obj")

    def binding(self, data="00000000"):
        return {"key": "app", "symbol": "_app", "address": 0x702820,
                "addends": [0, 0x90], "data_hex": data}

    def private_fixture(self):
        root, child = self.start, self.start + 0x20
        pe = VTablePe()
        pe.data[0x1000:0x1030] = b"\xcc" * 0x30
        pe.data[0x1000:0x1006] = b"\xe8" + struct.pack("<i", child - root - 5) + b"\xc3"
        pe.data[0x1020:0x1023] = b"\xc2\x04\x00"
        parent = {"address": "0x00401000", "symbol_base": "_root@4",
                  "rel32_targets": ["_child@4=0x00402000"]}
        function = {"address": "0x00402000", "symbol_base": "_child@4",
                    "private_from": {"caller": "0x00401000", "site": "0x00401000"}}
        unit = {"source": "src/owner.cpp", "functions": [parent, function]}
        functions = {root: [("_root@4", "i root.ltcg.obj")],
                     child: [("_child@4", "root.ltcg.obj")], root + 0x30: [("_next", "root.ltcg.obj")]}
        target = b"\xe8" + struct.pack("<i", 0x402000 - 0x401000 - 5) + b"\xc3"
        return {"function": function, "unit": unit, "pe": pe, "functions": functions,
                "exports": {"_root@4": root}, "cil_owner": "root.ltcg.obj",
                "ledger": {"0x00401000": {"size": "6", "status": "implemented",
                                          "source_file": "src/owner.cpp"}},
                "read_target": lambda address, size: target if (address, size) == (0x401000, 6) else b""}

    def test_private_contract_requires_a_distinct_exported_source_root(self):
        fixture = self.private_fixture()
        unit = {**fixture["unit"], "profile": linked.PROFILE, "object": "build/test.dll",
                "link_data_targets": ["_app=app"]}
        linked.validate_contract(unit, {"app"})
        changes = [lambda u: u["functions"][1].update(export_name="_child@4"),
                   lambda u: u["functions"][1].update(private_from=True),
                   lambda u: u["functions"][1]["private_from"].update(extra="waive"),
                   lambda u: u["functions"][1]["private_from"].update(site="not_an_address"),
                   lambda u: u["functions"][1]["private_from"].update(caller="0x00402000"),
                   lambda u: u["functions"][1]["private_from"].update(caller="0x00403000"),
                   lambda u: u["functions"][0].update(private_from={"caller": "0x00402000", "site": "0x00402000"}),
                   lambda u: u["functions"][1].update(symbol_base="_root@4"),
                   lambda u: u["functions"].append(None)]
        for change in changes:
            bad = copy.deepcopy(unit); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError):
                linked.validate_contract(bad, {"app"})

    def test_private_map_entry_requires_unique_cil_ownership_and_no_export_alias(self):
        f = self.private_fixture()
        def locate():
            return linked.source_function_start(f["function"], f["functions"], f["exports"], f["cil_owner"])
        self.assertEqual(locate(), self.start + 0x20)
        for export in ["_alias", "#1"]:
            f["exports"][export] = self.start + 0x20
            with self.assertRaises(ValueError): locate()
            f["exports"].pop(export)
        for aliases in [[("_child@4", "other.obj")], [("_child@4", "fake_root.ltcg.obj")],
                        [("_child@4", "root.ltcg.obj"), ("_alias", "root.ltcg.obj")], []]:
            f["functions"][self.start + 0x20] = aliases
            with self.subTest(aliases=aliases), self.assertRaises(ValueError): locate()
        f["functions"][self.start + 0x20] = [("_child@4", "root.ltcg.obj")]
        f["functions"][self.start + 0x10] = [("_child@4", "root.ltcg.obj")]
        with self.assertRaises(ValueError): locate()

    def test_private_witness_requires_unique_reachable_e8_edges_in_both_complete_bodies(self):
        f = self.private_fixture()
        witness = linked.private_caller_witness(**f)
        self.assertEqual(witness["source_site"], f"0x{self.start:08X}")
        self.assertEqual(witness["target_site"], "0x00401000")
        f["function"]["private_from"]["site"] = "0x00401001"
        with self.assertRaises(ValueError): linked.private_caller_witness(**f)
        for raw in [b"\x90\xc3", b"\xc3\xe8" + struct.pack("<i", 0x1a) + b"\xc3",
                    b"\xe8" + struct.pack("<i", 0x1b) + b"\xe8" + struct.pack("<i", 0x16) + b"\xc3",
                    b"\xeb\x1e\xc3"]:
            bad = self.private_fixture(); bad["pe"].data[0x1000:0x1020] = raw + b"\xcc" * (0x20 - len(raw))
            with self.subTest(source=raw.hex()), self.assertRaises(ValueError):
                linked.private_caller_witness(**bad)
        for raw in [b"\x90\xc3", b"\xe8" + struct.pack("<i", 0x2000 - 5) + b"\xc3",
                    b"\xe8" + struct.pack("<i", 0x1000 - 5) + b"\xe8" + struct.pack("<i", 0x1000 - 10) + b"\xc3"]:
            bad = self.private_fixture(); bad["ledger"]["0x00401000"]["size"] = str(len(raw))
            bad["read_target"] = lambda address, size, raw=raw: raw
            with self.subTest(target=raw.hex()), self.assertRaises(ValueError):
                linked.private_caller_witness(**bad)

    def test_private_witness_does_not_accept_unreviewed_parents_bad_bindings_or_internal_relocations(self):
        changes = [lambda f: f["ledger"]["0x00401000"].update(status="unclassified"),
                   lambda f: f["ledger"]["0x00401000"].update(source_file="src/other.cpp"),
                   lambda f: f["unit"]["functions"][0].update(rel32_targets=[]),
                   lambda f: f["unit"]["functions"][0].update(rel32_targets=["_child@4=0x00403000"]),
                   lambda f: f["functions"].update({self.start: [("_root@4", "other.obj")]}),
                   lambda f: f["exports"].update({"_root@4": self.start + 1}),
                   lambda f: setattr(f["pe"].sections[0], "Characteristics", 0x40000040),
                   lambda f: setattr(f["pe"], "DIRECTORY_ENTRY_BASERELOC", [SimpleNamespace(entries=[
                       SimpleNamespace(type=3, rva=0x1001)])])]
        for change in changes:
            bad = self.private_fixture(); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError):
                linked.private_caller_witness(**bad)

    def test_rel32_replay_preserves_opcode_and_argument_cleanup(self):
        destination = self.start + 0x800
        code = b"\xe8" + struct.pack("<i", destination - self.start - 5) + b"\xc2\x04\x00"
        seen = []
        def resolve(address):
            seen.append(address)
            return "__invalid_parameter_noinfo", 0x68a143
        canonical, calls, refs = self.canonical(code, resolve=resolve)
        self.assertEqual(canonical, b"\xe8" + struct.pack("<i", 0x68a143 - self.target - 5) + code[5:])
        self.assertEqual(seen, [destination])
        self.assertEqual(calls[0]["offset"], 1)
        self.assertEqual(refs, [])
        with self.assertRaisesRegex(ValueError, "unknown call"):
            self.canonical(code)

    def test_explicit_empty_data_contract_still_rejects_unbound_game_addresses(self):
        unit = {"profile": linked.PROFILE, "object": "build/test.dll",
                "link_data_targets": [], "functions": [{"symbol_base": "_render"}]}
        linked.validate_contract(unit, set())
        missing = dict(unit)
        missing.pop("link_data_targets")
        with self.assertRaises(ValueError):
            linked.validate_contract(missing, set())
        # An ordinary virtual dispatch needs no absolute game-data binding.
        code = b"\x8b\x01\xff\x50\x14\xc3"
        canonical, calls, refs = self.canonical(code)
        self.assertEqual(canonical, code)
        self.assertEqual((calls, refs), ([], []))
        with self.assertRaises(ValueError):
            self.canonical(b"\xa1" + struct.pack("<I", 0x702820) + b"\xc3")

    def test_absolute_data_identity_and_width_are_required(self):
        code = b"\xa1" + struct.pack("<I", 0x702820) + b"\xc3"
        self.assertEqual(self.canonical(code, [self.binding()])[0], code)
        with self.assertRaisesRegex(ValueError, "unattested"):
            self.canonical(code)
        with self.assertRaisesRegex(ValueError, "exceeds"):
            self.canonical(code, [self.binding("00")])
        pointer = b"\x68" + struct.pack("<I", 0x7028b0) + b"\xc3"
        self.assertEqual(self.canonical(pointer, [self.binding()])[0], pointer)
        with self.assertRaisesRegex(ValueError, "unattested linked game address"):
            self.canonical(pointer)

    def test_internal_literal_addresses_are_never_waived(self):
        with self.assertRaisesRegex(ValueError, "internal linked address"):
            self.canonical(b"\x68" + struct.pack("<I", self.start + 0x100) + b"\xc3")

    def test_native_vptr_replay_requires_a_member_store_and_preserves_every_other_byte(self):
        source, target = linked.IMAGE_BASE + 0x2010, 0x6d6c64
        table = {"source_address": source, "target_address": target,
                 "symbol": "??_7Pool@@6B@", "target_key": "pool"}
        code = b"\xc7\x46\x48" + struct.pack("<I", source) + b"\xc3"
        canonical, calls, refs = linked.canonicalize(code, self.start, self.target, [], None,
            self.image, self.game, [table])
        self.assertEqual(canonical, code[:3] + struct.pack("<I", target) + code[7:])
        self.assertEqual(calls, [])
        self.assertEqual(refs[0]["field_offset"], 3)
        self.assertEqual(refs[0]["kind"], "vptr")
        for bad in [b"\x68" + struct.pack("<I", source) + b"\xc3",
                    b"\xb8" + struct.pack("<I", source) + b"\xc3",
                    b"\xc7\x06" + struct.pack("<I", target) + b"\xc3"]:
            with self.subTest(code=bad.hex()), self.assertRaises(ValueError):
                linked.canonicalize(bad, self.start, self.target, [], None, self.image, self.game, [table])

    def test_vptr_fields_need_exact_highlow_coverage_without_extra_relocations(self):
        refs = [{"kind": "vptr", "field_offset": 3}]
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=linked.IMAGE_BASE))
        def relocations(entries):
            pe.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[
                SimpleNamespace(rva=self.start - linked.IMAGE_BASE + off, type=kind)
                for off, kind in entries])]
        relocations([(3, 3)])
        linked.validate_body_relocations(pe, self.start, 8, refs)
        for entries in [[], [(3, 1)], [(4, 3)], [(3, 3), (3, 3)], [(3, 3), (7, 3)]]:
            relocations(entries)
            with self.subTest(entries=entries), self.assertRaises(ValueError):
                linked.validate_body_relocations(pe, self.start, 8, refs)
        relocations([])
        linked.validate_body_relocations(pe, self.start, 8, [])

    def test_native_vtable_owner_rtti_slot_and_readonly_storage_are_independent(self):
        pe = VTablePe()
        vt, col, descriptor, entry = [linked.IMAGE_BASE + v for v in (0x2010, 0x2040, 0x3020, 0x1010)]
        symbol, destructor = "??_7Pool@game@@6B@", "??_GPool@game@@UAEPAXI@Z"
        struct.pack_into("<II", pe.data, 0x200c, col, entry)
        struct.pack_into("<5I", pe.data, 0x2040, 0, 0, 0, descriptor, col + 20)
        name = b".?AVPool@game@@\0"
        pe.data[0x3028:0x3028 + len(name)] = name
        symbols = {symbol: [(vt, "Pool.ltcg.obj")]}
        functions = {entry: [(destructor, "i Pool.ltcg.obj")]}
        tables = [{"symbol": symbol, "entry_symbol": destructor,
                   "target_address": 0x6d6c64, "target_key": "pool"}]
        self.assertEqual(linked.source_vtables(pe, symbols, functions, tables, "Pool.ltcg.obj")[0]["source_address"], vt)
        bad_models = []
        bad = copy.deepcopy(pe); bad.sections[1].Characteristics |= 0x80000000; bad_models.append(bad)
        bad = copy.deepcopy(pe); struct.pack_into("<I", bad.data, 0x2044, 4); bad_models.append(bad)
        bad = copy.deepcopy(pe); bad.data[0x302c] = ord("X"); bad_models.append(bad)
        bad = copy.deepcopy(pe); struct.pack_into("<I", bad.data, 0x2014, entry); bad_models.append(bad)
        bad = copy.deepcopy(pe); struct.pack_into("<I", bad.data, 0x2010, entry + 4); bad_models.append(bad)
        for bad in bad_models:
            with self.assertRaises(ValueError):
                linked.source_vtables(bad, symbols, functions, tables, "Pool.ltcg.obj")
        for bad_symbols, bad_functions in [({symbol: [(vt, "Other.obj")]}, functions),
                ({symbol: [(vt, "Pool.ltcg.obj"), (vt, "Pool.ltcg.obj")]}, functions),
                (symbols, {entry: [(destructor, "Other.obj")]})]:
            with self.assertRaises(ValueError):
                linked.source_vtables(pe, bad_symbols, bad_functions, tables, "Pool.ltcg.obj")

    def test_target_vtable_cannot_be_rebound_by_prefix_or_wrong_target_type(self):
        pe = VTablePe(0x400000)
        pe.sections[0].VirtualAddress = 0x13000
        base = 0x400000
        struct.pack_into("<II", pe.data, 0x200c, base + 0x2040, 0x4138b0)
        struct.pack_into("<5I", pe.data, 0x2040, 0, 0, 0, base + 0x3020, base + 0x2054)
        name = b".?AVOriginalPool@@\0"; pe.data[0x3028:0x3028 + len(name)] = name
        table = {"symbol": "??_7Pool@game@@6B@", "target": "pool",
                 "entry": "??_GPool@game@@UAEPAXI@Z=0x004138B0", "target_type_name": ".?AVOriginalPool@@"}
        known = {"pool": (base + 0x2010, struct.pack("<I", 0x4138b0), frozenset({0}), "address")}
        fake = SimpleNamespace(verify_target=lambda: "target", TARGET=Path("unused"), known_data_targets=lambda: known)
        with patch.object(linked, "comparator", return_value=fake), patch.object(linked.pefile, "PE", return_value=pe):
            self.assertEqual(linked.target_vtables({"link_vtables": [table]})[0]["entry_target"], 0x4138b0)
            for field, value in [("entry", "??_GPool@game@@UAEPAXI@Z=0x00412C80"),
                                 ("target_type_name", ".?AVOtherPool@@")]:
                with self.subTest(field=field), self.assertRaises(ValueError):
                    linked.target_vtables({"link_vtables": [{**table, field: value}]})
            known["pool"] = (base + 0x2010, struct.pack("<II", 0x4138b0, 0), frozenset({0}), "address")
            with self.assertRaises(ValueError):
                linked.target_vtables({"link_vtables": [table]})

    def test_complete_cfg_rejects_partial_or_unowned_tails(self):
        for code in [b"\xeb\x7f\xc3", b"\xeb\xff\xc3", b"\xe2\x7f\xc3", b"\xff\xe0\xc3",
                     b"\xc3\x90\xc3", b"\xe8\x01", b"\xcc\xc3"]:
            with self.subTest(code=code.hex()), self.assertRaises(ValueError):
                linked.decode_closed_body(code, self.start)
        # Both return paths must be decoded and owned, not just the first RET.
        self.assertEqual(len(linked.decode_closed_body(b"\x74\x01\xc3\xc3", self.start)), 3)
        self.assertEqual(len(linked.decode_closed_body(b"\xe2\xfe\xc3", self.start)), 2)

    def test_runtime_identity_requires_named_pinned_dll_and_mapping(self):
        slot = linked.IMAGE_BASE + 0x3000
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x5000),
                             get_data=lambda rva, size: b"\xff\x25" + struct.pack("<I", slot))
        destination = self.start + 0x800
        targets = {"__invalid_parameter_noinfo": 0x68a143}
        imports = {slot: ("msvcr80.dll", "_invalid_parameter_noinfo")}
        self.assertEqual(linked.resolve_linked_call(destination, pe, {}, imports, targets),
                         ("__invalid_parameter_noinfo", 0x68a143))
        for bad in [{slot: ("msvcr90.dll", "_invalid_parameter_noinfo")},
                    {slot: ("msvcr80.dll", None)}, {}, {slot: ("msvcr80.dll", "different")}]:
            with self.subTest(imports=bad), self.assertRaises(ValueError):
                linked.resolve_linked_call(destination, pe, {}, bad, targets)
        with self.assertRaisesRegex(ValueError, "escapes"):
            linked.resolve_linked_call(0x68a143, pe, {}, imports, targets)

    def test_sdk_contract_accepts_only_explicit_pinned_imports(self):
        unit = {"profile": linked.PROFILE, "object": "build/test.dll",
                "link_data_targets": ["_app=app"], "functions": [{"symbol_base": "_worker@4"}],
                "link_import_targets": ["_sendto@24=0x006898CC"]}
        linked.validate_contract(unit, {"app"})
        for imports in [None, "_sendto@24=0x006898CC", ["_sendto@24=6898CC"],
                        ["_recvfrom@24=0x006898BA"], ["_sendto@24=0x006898CC"] * 2]:
            with self.subTest(imports=imports), self.assertRaises(ValueError):
                linked.validate_contract({**unit, "link_import_targets": imports}, {"app"})
        with self.assertRaises(ValueError):
            linked.validate_contract({**unit, "link_data_targets": ["_sendto@24=app"]}, {"app"})

    def test_import_identity_keeps_ordinals_despite_pefile_name_annotations(self):
        ordinal = SimpleNamespace(name=b"sendto", ordinal=20, import_by_ordinal=True)
        named = SimpleNamespace(name=b"sendto", ordinal=None, import_by_ordinal=False)
        self.assertEqual(linked.import_identity(ordinal), 20)
        self.assertEqual(linked.import_identity(named), "sendto")

    def test_sdk_call_needs_matching_import_map_owner_and_target_contract(self):
        slot, destination = linked.IMAGE_BASE + 0x3000, self.start + 0x800
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x5000),
                             get_data=lambda rva, size: b"\xff\x25" + struct.pack("<I", slot))
        contract = {**linked.SDK_IMPORTS["_sendto@24"], "symbol": "_sendto@24", "target": 0x6898cc}
        imports, targets = {slot: ("ws2_32.dll", 20)}, {"_sendto@24": 0x6898cc}
        functions = {destination: [("_sendto@24", "WS2_32:WS2_32.dll")]}
        def resolve(i=imports, t=targets, f=functions, contracts=None):
            return linked.resolve_linked_call(destination, pe, f, i, t,
                                              [contract] if contracts is None else contracts)
        self.assertEqual(resolve(), ("_sendto@24", 0x6898cc))
        for identity in [("ws2_32.dll", "sendto"), ("ws2_32.dll", 19), ("other.dll", 20)]:
            with self.subTest(identity=identity), self.assertRaises(ValueError): resolve(i={slot: identity})
        for bad in [{}, {"_sendto@24": 0x401000}]:
            with self.subTest(targets=bad), self.assertRaises(ValueError): resolve(t=bad)
        for aliases in [[], [("_sendto@24", "game.obj")], [("_recvfrom@24", "WS2_32:WS2_32.dll")],
                        functions[destination] * 2]:
            with self.subTest(aliases=aliases), self.assertRaises(ValueError): resolve(f={destination: aliases})
        for contracts in [[], [contract, contract]]:
            with self.assertRaises(ValueError): resolve(contracts=contracts)
        with self.assertRaises(ValueError):
            linked.resolve_linked_call(destination, pe, {}, {slot: ("msvcr80.dll", 20)}, targets)

    def test_sdk_target_attests_archive_abi_thunk_iat_and_excluded_origin(self):
        with tempfile.TemporaryDirectory() as folder:
            root, address, iat = Path(folder), 0x6898cc, 0x6c0274
            (root / "scripts").mkdir(); (root / "config").mkdir()
            (root / "scripts/extract-msvc-library-object.py").write_bytes(
                (linked.ROOT / "scripts/extract-msvc-library-object.py").read_bytes())
            library = root / "PlatformSDK/Lib/WS2_32.Lib"; library.parent.mkdir(parents=True)
            strings = b"_sendto@24\0WS2_32.dll\0"
            member = struct.pack("<HHHHIIHH", 0, 0xffff, 0, 0x14c, 0, len(strings), 20, 0) + strings
            contract = {**linked.SDK_IMPORTS["_sendto@24"],
                        "member_sha256": linked.hashlib.sha256(member).hexdigest()}
            def write_member(body):
                header = f"{'WS2_32.dll/':<16}{0:<12}{0:<6}{0:<6}{0:<8}{len(body):<10}`\n".encode()
                library.write_bytes(b"!<arch>\n" + header + body + (b"\n" if len(body) % 2 else b""))
            write_member(member)
            functions = root / "config/functions.csv"
            functions.write_text("address,size\n0x006898CC,6\n")
            origins = root / "config/function-origins.csv"
            origins.write_text("address,origin,disposition\n0x006898CC,import_thunk,exclude\n")
            raw = struct.pack("<I", 0x80000014)
            known = {"__imp__sendto@24": (iat, raw, frozenset({0}), "literal")}
            memory = {(iat, 4): raw, (address, 6): b"\xff\x25" + struct.pack("<I", iat)}
            entry = SimpleNamespace(address=iat, ordinal=20, name=b"sendto", import_by_ordinal=True)
            code, data = SimpleNamespace(Characteristics=0x60000020), SimpleNamespace(Characteristics=0xc0000040)
            pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),
                DIRECTORY_ENTRY_IMPORT=[SimpleNamespace(dll=b"WS2_32.dll", imports=[entry])],
                get_section_by_rva=lambda rva: code if rva == address - 0x400000 else data)
            c = SimpleNamespace(TARGET=root / "game.exe", verify_target=lambda: "target",
                                known_data_targets=lambda: known, target_bytes=lambda a, n: memory.get((a, n), b""))
            with patch.object(linked, "ROOT", root), patch.object(linked, "comparator", return_value=c), \
                 patch.object(linked.pefile, "PE", return_value=pe), \
                 patch.dict(linked.SDK_IMPORTS, {"_sendto@24": contract}, clear=True):
                unit = {"link_import_targets": ["_sendto@24=0x006898CC"]}
                check = lambda: linked.target_imports(unit, root)
                self.assertEqual(check()[0]["target_iat"], iat)
                mutations = [(memory, (address, 6), b"\xff\x25" + struct.pack("<I", iat + 4)),
                             (memory, (iat, 4), bytes(4)),
                             (known, "__imp__sendto@24", (iat, raw, frozenset({0, 4}), "literal")),
                             (known, "__imp__sendto@24", (iat, raw, frozenset({0}), "address"))]
                for mapping, key, value in mutations:
                    old = mapping[key]; mapping[key] = value
                    with self.subTest(value=value), self.assertRaises(ValueError): check()
                    mapping[key] = old
                for obj, key, value in [(entry, "ordinal", 19), (entry, "import_by_ordinal", False),
                                        (code, "Characteristics", 0x40000040), (data, "Characteristics", 0x60000020)]:
                    old = getattr(obj, key); setattr(obj, key, value)
                    with self.subTest(key=key), self.assertRaises(ValueError): check()
                    setattr(obj, key, old)
                for path, bad in [(functions, "address,size\n0x006898CC,5\n"),
                                  (origins, "address,origin,disposition\n0x006898CC,authored_game,authored\n")]:
                    old = path.read_text(); path.write_text(bad)
                    with self.assertRaises(ValueError): check()
                    path.write_text(old)
                write_member(member[:-1] + b"x")
                with self.assertRaisesRegex(ValueError, "member"): check()
                # Even an explicitly pinned member must describe code/ordinal20
                # with the exact stdcall symbol, not a data or named import.
                for offset, replacement in [(6, struct.pack("<H", 0x8664)), (16, struct.pack("<H", 19)),
                                             (18, struct.pack("<H", 1)), (20, b"X")]:
                    bad = member[:offset] + replacement + member[offset + len(replacement):]
                    write_member(bad); contract["member_sha256"] = linked.hashlib.sha256(bad).hexdigest()
                    with self.assertRaisesRegex(ValueError, "wrong symbol/DLL/ordinal/code"): check()

    def test_ambiguous_linker_function_aliases_fail(self):
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x5000), get_data=lambda rva, size: bytes(size))
        destination = self.start + 0x800
        functions = {destination: [("a", "source.obj"), ("b", "source.obj")]}
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            linked.resolve_linked_call(destination, pe, functions, {}, {"a": 0x401000, "b": 0x402000})
        self.assertEqual(linked.resolve_linked_call(destination, pe, functions, {}, {"a": 0x401000, "b": 0x401000})[1], 0x401000)

    def test_map_reader_does_not_treat_data_as_functions(self):
        text = " 0001:00000000 _worker@4 10001000 f source.ltcg.obj\n 0002:00000000 _data 10003000 source.ltcg.obj\n"
        self.assertEqual(linked.parse_map(text), {self.start: [("_worker@4", "source.ltcg.obj")]})
        with self.assertRaises(ValueError):
            linked.parse_map("no functions")

    def test_absolute_object_contains_symbols_only(self):
        data = linked.absolute_data_object([self.binding()])
        machine, sections, timestamp, table, count, optional, flags = struct.unpack_from("<HHIIIHH", data)
        self.assertEqual((machine, sections, timestamp, table, count, optional, flags), (0x14c, 0, 0, 20, 1, 0, 0))
        self.assertEqual(struct.unpack_from("<IhHBB", data, 28), (0x702820, -1, 0, 2, 0))

    def test_link_contract_cannot_forward_exports_or_waive_unsupported_surfaces(self):
        unit = {"profile": linked.PROFILE, "object": "build/test.dll",
                "link_data_targets": ["_app=app"],
                "functions": [{"symbol_base": "_worker@4", "export_name": "_worker@4"}]}
        linked.validate_contract(unit, {"app"})
        for field, value in [("export_name", "worker=OTHER.worker"), ("export_name", None),
                             ("symbol_base", None), ("contiguous_span", True), ("owned_extent", True),
                             ("dir32_targets", ["literal=untyped"] )]:
            bad = copy.deepcopy(unit)
            bad["functions"][0][field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                linked.validate_contract(bad, {"app"})

    def test_linked_vtable_and_library_contracts_cannot_waive_their_type_or_scope(self):
        table = {"symbol": "??_7Pool@game@@6B@", "target": "pool",
                 "entry": "??_GPool@game@@UAEPAXI@Z=0x004138B0", "target_type_name": ".?AVOriginalPool@@"}
        unit = {"profile": linked.PROFILE, "object": "build/test.dll", "source": "src/main.cpp",
                "link_data_targets": ["_app=app"], "link_vtables": [table],
                "functions": [{"symbol_base": "_worker@4"}]}
        linked.validate_contract(unit, {"app", "pool"})
        with self.assertRaisesRegex(ValueError, "typed RTTI"):
            linked.validate_contract({**unit, "link_data_targets": ["_fake=??_7Pool@game@@6B@"]},
                                     {"app", "pool", "??_7Pool@game@@6B@"})
        for field, value in [("symbol", "_arbitrary_data"), ("target", None),
                             ("entry", "??_GOther@game@@UAEPAXI@Z=0x004138B0"),
                             ("entry", None), ("target_type_name", None)]:
            bad = copy.deepcopy(unit); bad["link_vtables"][0][field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                linked.validate_contract(bad, {"app", "pool"})
        for sources in [None, ["src/network/Owner.cpp"], ["src/library/../Owner.cpp"],
                        ["src/library/UnsignedIntList.cpp"] * 2, ["src/library/missing.cpp"]]:
            with self.subTest(sources=sources), self.assertRaises(ValueError):
                linked.validate_contract({**unit, "linked_coff_sources": sources}, {"app", "pool"})

    def test_modified_build_artifacts_are_rejected_before_decoding(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            image, source = root / "probe.dll", root / "source.cpp"
            library, native_obj = root / "list.cpp", image.with_suffix(".coff0.obj")
            paths = [image, source, image.with_suffix(".map"), image.with_suffix(".ltcg.obj"), image.with_suffix(".bindings.obj"), library, native_obj]
            unit = {"source": str(source), "object": str(image), "linked_coff_sources": [str(library)]}
            for changed in paths:
                for path in paths:
                    path.write_bytes(b"original")
                metadata = {"schema": "th105-linked-pe-v1", "unit": "test", "profile": linked.PROFILE,
                    "target_sha256": "target", "input_digest": "digest", "tools": {}, "bindings": [],
                    "vtable_contracts": [], "sdk_imports": [], "layout_inputs": [], "coff_inputs": [{"source": str(library),
                        "source_sha256": linked.sha(library), "object": native_obj.name,
                        "object_sha256": linked.sha(native_obj)}],
                    "parsers": linked.parser_versions(), "source_sha256": linked.sha(source),
                    "image_sha256": linked.sha(image), "map_sha256": linked.sha(image.with_suffix(".map")),
                    "ltcg_object_sha256": linked.sha(image.with_suffix(".ltcg.obj")),
                    "bindings_object_sha256": linked.sha(image.with_suffix(".bindings.obj"))}
                image.with_suffix(".link.json").write_text(json.dumps(metadata))
                fake = SimpleNamespace(verify_target=lambda: "target")
                with self.subTest(changed=changed.name), patch.object(linked, "comparator", return_value=fake), \
                     patch.object(linked, "pinned_tools", return_value=(root, {})), \
                     patch.object(linked, "target_bindings", return_value=[]), \
                     patch("workflow_manifest.unit_input_digest", return_value=("digest", [])), \
                     patch("workflow_manifest.repository_path", side_effect=lambda path, **kwargs: Path(path)), \
                     patch.object(linked.pefile, "PE", side_effect=AssertionError("provenance accepted")):
                    with self.assertRaisesRegex(AssertionError, "provenance accepted"):
                        linked.compare_linked("test", unit, set(), image)
                    changed.write_bytes(b"changed")
                    with self.assertRaisesRegex(ValueError, "stale or modified"):
                        linked.compare_linked("test", unit, set(), image)


if __name__ == "__main__":
    unittest.main()
