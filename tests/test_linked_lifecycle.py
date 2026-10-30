"""Reject unsupported global/EH evidence without proprietary tools or game bytes."""
import copy
from pathlib import Path
import struct
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_pe as core
import linked_lifecycle as life
import workflow_manifest as workflow


class MemoryPE:
    def __init__(self, base=core.IMAGE_BASE):
        self.OPTIONAL_HEADER = SimpleNamespace(ImageBase=base, SizeOfImage=0x5000, AddressOfEntryPoint=0x1000)
        self.data = bytearray(0x5000)
        self.sections = [SimpleNamespace(VirtualAddress=rva, Misc_VirtualSize=0x1000,
            SizeOfRawData=0x1000, Characteristics=flags, Name=name)
            for rva, flags, name in [(0x1000, 0x60000020, b".text"),
                (0x2000, 0x40000040, b".rdata"), (0x3000, 0xc0000040, b".data")]]
        self.DIRECTORY_ENTRY_BASERELOC = []

    def get_section_by_rva(self, rva):
        return next((s for s in self.sections if s.VirtualAddress <= rva < s.VirtualAddress + s.Misc_VirtualSize), None)

    def get_data(self, rva, size):
        return bytes(self.data[rva:rva + size])

    def put(self, rva, data):
        self.data[rva:rva + len(data)] = data

    def relocations(self, *rvas):
        self.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[SimpleNamespace(type=3, rva=r) for r in rvas])]


class LifecycleTests(unittest.TestCase):
    symbol = "?g_package_archive_store@th105@@3UPackageArchiveStore@1@A"
    owner = "unit.ltcg.obj"
    start = core.IMAGE_BASE + 0x1000
    game = (0x400000, 0x800000)
    image = (core.IMAGE_BASE, core.IMAGE_BASE + 0x5000)

    def contract(self):
        obj = dict(symbol=self.symbol, target="global", size=60,
            layout_source="src/assets/PackageArchiveStore.cpp", initializer="0x006BE7B0",
            initializer_table="0x006C0374", atexit="0x0068AF1E", destructor_callback="0x006BEE60")
        return dict(profile=core.PROFILE, object="build/test.dll", link_runtime="static",
            link_runtime_data=["___security_cookie"], link_data_targets=["_external=external"],
            source="src/assets/PackageArchiveStoreLinked.cpp", link_objects=[obj],
            functions=[dict(address="0x0041B8C0", symbol_base="??0PackageArchiveStore@th105@@QAE@XZ",
                private_global=dict(object=self.symbol, role="constructor"),
                eh_cleanup=dict(handler="0x006BDBB3", info="0x006E4230")),
                dict(address="0x0041B980", symbol_base="??1PackageArchiveStore@th105@@QAE@XZ",
                private_global=dict(object=self.symbol, role="destructor"),
                eh_cleanup=dict(handler="0x006BE09E", info="0x006E477C"))])

    def test_public_lifetime_cleanup_requires_static_cookie_and_unrenamed_export(self):
        unit = dict(profile=core.PROFILE, object="build/test.dll", link_runtime="static",
            source="src/battle/ScriptLifecycle.cpp", link_runtime_data=["___security_cookie"],
            link_data_targets=[], functions=[dict(address="0x00405660",
                symbol_base="??1CScript@@QAE@XZ",
                eh_cleanup=dict(handler="0x006BE423", info="0x006E4C58"))])
        core.validate_contract(unit, set())
        member = copy.deepcopy(unit)
        member["functions"][0]["symbol_base"] = "?load@FileBuffer@@QAE_NPBD@Z"
        core.validate_contract(member, set())
        member["functions"][0]["symbol_base"] = "?load_from_file@CBitmapData@th105@@UAE_NPBD@Z"
        core.validate_contract(member, set())
        private = copy.deepcopy(unit)
        private["functions"][0]["private_from"] = dict(caller="0x00405600", site="0x00405633")
        private["functions"].append(dict(address="0x00405600", symbol_base="?release@Owner@@QAEXI@Z"))
        core.validate_contract(private, set())
        constructor = copy.deepcopy(private)
        constructor["functions"][0]["symbol_base"] = "??0CScript@@QAE@XZ"
        constructor["functions"][0]["private_from"]["source_only_caller"] = True
        core.validate_contract(constructor, set())
        for key in ["eh_cleanup", "private_from"]:
            bad_ctor = copy.deepcopy(constructor)
            if key == "private_from":
                bad_ctor["functions"][0][key]["source_only_caller"] = False
            else:
                bad_ctor["functions"][0].pop(key)
            with self.assertRaises(ValueError):
                core.validate_contract(bad_ctor, set())
        bad_private = copy.deepcopy(private)
        bad_private["functions"][0]["symbol_base"] = "?load@FileBuffer@@QAE_NPBD@Z"
        with self.assertRaises(ValueError):
            core.validate_contract(bad_private, set())
        changes = [lambda u: u.update(link_runtime="import"),
            lambda u: u.update(link_runtime_data=[]),
            lambda u: u["functions"][0].update(symbol_base="_free_function"),
            lambda u: u["functions"][0].update(export_name="_alias"),
            lambda u: u["functions"][0].update(private_from=dict(caller="0x00405600", site="0x00405633")),
            lambda u: u["functions"][0].update(private_static_leaf=True),
            lambda u: u["functions"][0]["eh_cleanup"].update(ignore_catches=True),
            lambda u: u["functions"][0]["eh_cleanup"].update(info="0x6E4C58")]
        for change in changes:
            bad = copy.deepcopy(unit); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError):
                core.validate_contract(bad, set())

    def test_global_contract_rejects_waivers_aliases_and_invented_layout_inputs(self):
        unit = self.contract()
        core.validate_contract(unit, {"global", "external"})
        changes = [lambda u: u.update(link_runtime="import"), lambda u: u.update(link_runtime="other"),
            lambda u: u.update(link_runtime_data=["_arbitrary"]),
            lambda u: u["link_objects"][0].update(size=True),
            lambda u: u["link_objects"][0].update(size=59),
            lambda u: u["link_objects"][0].update(layout_source="src/assets/PackageArchiveLoader.cpp"),
            lambda u: u["link_objects"][0].update(waive=True),
            lambda u: u["link_objects"][0].update(initializer="0x6be7b0"),
            lambda u: u["link_objects"].append(copy.deepcopy(u["link_objects"][0])),
            lambda u: u["functions"][0].update(export_name="_fake"),
            lambda u: u["functions"][0].update(private_from=dict(caller="0x0041B980", site="0x0041BA00")),
            lambda u: u["functions"][1]["private_global"].update(role="constructor"),
            lambda u: u["functions"][1].update(symbol_base="??1Other@th105@@QAE@XZ"),
            lambda u: u["functions"][0].pop("eh_cleanup"),
            lambda u: u["functions"][0]["eh_cleanup"].update(ignore_catches=True)]
        for change in changes:
            bad = copy.deepcopy(unit); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError):
                core.validate_contract(bad, {"global", "external"})

    def test_static_without_source_globals_retains_contract_guards(self):
        unit = dict(profile=core.PROFILE, object="build/test.dll", source="src/test.cpp",
                    link_runtime="static", link_data_targets=[],
                    functions=[dict(address="0x00401000", symbol_base="_root")])
        core.validate_contract(unit, set())
        bad = copy.deepcopy(unit)
        bad["functions"][0]["eh_cleanup"] = dict(handler="0x006B0000", info="0x006E0000")
        with self.assertRaises(ValueError):
            core.validate_contract(bad, set())
        bad = copy.deepcopy(unit); bad.update(link_runtime="import", link_runtime_data=["___security_cookie"])
        with self.assertRaises(ValueError):
            core.validate_contract(bad, set())

    def test_static_runtime_tables_reject_source_callbacks_and_missing_relocations(self):
        pe = MemoryPE(); base = core.IMAGE_BASE
        symbols = {name: [(base + offset, "libcmt:crt0init.obj")]
                   for name, offset in [("___xi_a", 0x2000), ("___xi_z", 0x2008),
                                        ("___xc_a", 0x2020), ("___xc_z", 0x2028)]}
        pe.put(0x2004, struct.pack("<I", base + 0x1000)); pe.relocations(0x2004)
        functions = {base + 0x1000: [("___sse2_available_init", "libcmt:cpu_disp.obj")]}
        self.assertEqual(len(life.validate_static_runtime_initializers(pe, functions, symbols)), 1)
        stdio = {base + 0x1000: [("___initstdio", "libcmt:_file.obj")]}
        with self.assertRaises(ValueError):
            life.validate_static_runtime_initializers(pe, stdio, symbols)
        self.assertEqual(len(life.validate_static_runtime_initializers(
            pe, stdio, symbols, allow_pinned_stdio=True)), 1)
        with self.assertRaises(ValueError):
            life.validate_static_runtime_initializers(pe,
                {base + 0x1000: [("___initstdio", "unit.ltcg.obj")]},
                symbols, allow_pinned_stdio=True)

        for owner in ["unit.ltcg.obj", "CIL library: CIL module", "untrusted:cpu_disp.obj"]:
            with self.subTest(owner=owner), self.assertRaises(ValueError):
                life.validate_static_runtime_initializers(pe,
                    {base + 0x1000: [("___sse2_available_init", owner)]}, symbols)
        with self.assertRaises(ValueError):
            life.validate_static_runtime_initializers(pe,
                {base + 0x1000: [("_unlisted_init", "libcmt:cpu_disp.obj")]}, symbols)
        pe.relocations()
        with self.assertRaises(ValueError):
            life.validate_static_runtime_initializers(pe, functions, symbols)
        pe.put(0x2024, struct.pack("<I", base + 0x1000)); pe.relocations(0x2004, 0x2024)
        with self.assertRaises(ValueError):
            life.validate_static_runtime_initializers(pe, functions, symbols)

    def native_coff(self):
        strings = self.symbol.encode() + b"\0"
        header = struct.pack("<HHIIIHH", 0x14c, 1, 0, 60, 1, 0, 0)
        section = b".bss\0\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 60, 0, 0, 0, 0, 0, 0xc0300080)
        symbol = struct.pack("<IIIhHBB", 0, 4, 0, 1, 0, 2, 0)
        return header + section + symbol + struct.pack("<I", len(strings) + 4) + strings

    def test_native_layout_requires_actual_strong_zero_bss_extent_and_alignment(self):
        raw = self.native_coff()
        self.assertEqual(life.native_zero_layout(raw, self.symbol, 60)["size"], 60)
        for offset, fmt, value in [(0, "H", 0x8664), (16, "H", 1), (36, "I", 64),
                (40, "I", 20), (44, "I", 60), (52, "H", 1), (56, "I", 0xc0400080),
                (68, "I", 4), (72, "h", -1), (76, "B", 105), (77, "B", 2)]:
            bad = bytearray(raw); struct.pack_into("<" + fmt, bad, offset, value)
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                life.native_zero_layout(bytes(bad), self.symbol, 60)
        for truncated in [raw[:10], raw[:61], raw[:-1]]:
            with self.assertRaises(ValueError): life.native_zero_layout(truncated, self.symbol, 60)

    def test_eight_aligned_native_zero_layout_keeps_exact_extent(self):
        raw = bytearray(self.native_coff())
        struct.pack_into("<I", raw, 36, 64)
        struct.pack_into("<I", raw, 56, 0xc0400080)
        self.assertEqual(life.native_zero_layout(bytes(raw), self.symbol, 64)["alignment"], 8)
        for flags in (0xc0200080, 0xc0500080, 0xc0400040):
            struct.pack_into("<I", raw, 56, flags)
            with self.assertRaises(ValueError):
                life.native_zero_layout(bytes(raw), self.symbol, 64)

    def test_local_cpp_dependencies_are_transitive_and_hashed(self):
        with tempfile.TemporaryDirectory(dir=workflow.ROOT / "build") as folder:
            root = Path(folder)
            (root / "main.cpp").write_text('#include "body.cpp"\n')
            (root / "body.cpp").write_text('#include "leaf.hpp"\n')
            (root / "leaf.hpp").write_text('#include "main.cpp"\n')
            unit = dict(source=str((root / "main.cpp").relative_to(workflow.ROOT)))
            self.assertEqual(workflow.source_dependencies(unit), set(root.iterdir()))
            unit.update(kind="probe", profile="vc8-sp1-probe-o2", enable_gs=True)
            with patch.object(workflow, "compiler_sha256", return_value="a" * 64):
                before, inputs = workflow.unit_input_digest("dependency-test", unit)
                self.assertIn(str((root / "body.cpp").relative_to(workflow.ROOT)), inputs)
                (root / "body.cpp").write_text('int changed;\n#include "leaf.hpp"\n')
                after, _ = workflow.unit_input_digest("dependency-test", unit)
                self.assertNotEqual(before, after)

    def typed(self, kind="object"):
        return dict(kind=kind, source_address=core.IMAGE_BASE + 0x3000, address=0x7028dc,
                    size=4, symbol="global")

    def canonical(self, code, refs, **kwargs):
        return core.canonicalize(code, self.start, 0x401000, [], None, self.image, self.game,
                                 internal_refs=refs, **kwargs)

    def test_internal_replay_is_operand_typed_and_requires_every_highlow(self):
        obj = self.typed()
        source, target = struct.pack("<I", obj["source_address"]), struct.pack("<I", obj["address"])
        for code, expected, offset in [(b"\xa1" + source + b"\xc3", b"\xa1" + target + b"\xc3", 1),
                (b"\xb9" + source + b"\xc3", b"\xb9" + target + b"\xc3", 1),
                (b"\x68" + source + b"\xc3", b"\x68" + target + b"\xc3", 1)]:
            canonical, _, refs = self.canonical(code, [obj])
            self.assertEqual(canonical, expected)
            pe = MemoryPE(); pe.relocations(0x1000 + offset)
            core.validate_body_relocations(pe, self.start, len(code), refs)
            for rvas in [[], [0x1000 + offset] * 2, [0x1000 + offset, 0x1000 + offset + 1]]:
                pe.relocations(*rvas)
                with self.assertRaises(ValueError): core.validate_body_relocations(pe, self.start, len(code), refs)
        for kind, codes in [("runtime", [b"\x68" + source + b"\xc3"]),
                ("eh_handler", [b"\xa1" + source + b"\xc3", b"\xb8" + source + b"\xc3"]),
                ("eh_info", [b"\x68" + source + b"\xc3", b"\xb9" + source + b"\xc3"])]:
            for code in codes:
                with self.subTest(kind=kind), self.assertRaises(ValueError): self.canonical(code, [self.typed(kind)])
        with self.assertRaises(ValueError): self.canonical(b"\xa1" + source + b"\xc3", [])

    def test_absolute_vptr_store_needs_the_real_object_destination_and_both_relocations(self):
        obj = self.typed()
        table = dict(source_address=core.IMAGE_BASE + 0x2004, target_address=0x6d6a14,
                     symbol="??_7Critical@@6B@", target_key="vtable")
        raw = b"\xc7\x05" + struct.pack("<II", obj["source_address"], table["source_address"]) + b"\xc3"
        code, _, refs = self.canonical(raw, [obj], vtables=[table])
        self.assertEqual(code, b"\xc7\x05" + struct.pack("<II", obj["address"], table["target_address"]) + b"\xc3")
        pe = MemoryPE(); pe.relocations(0x1002, 0x1006)
        core.validate_body_relocations(pe, self.start, len(raw), refs)
        with self.assertRaises(ValueError): self.canonical(raw, [], vtables=[table])
        with self.assertRaises(ValueError): self.canonical(raw, [self.typed("runtime")], vtables=[table])

    def test_tail_mode_does_not_waive_nonterminal_or_indirect_escaped_edges(self):
        raw = b"\x90\xe9" + struct.pack("<i", 0x1800 - 0x1001 - 5)
        resolve = lambda destination: ("_actual", 0x402000)
        out, calls, _ = core.canonicalize(raw, self.start, 0x401000, [], resolve, self.image, self.game, tail=True)
        self.assertEqual(out, b"\x90\xe9" + struct.pack("<i", 0x402000 - 0x401001 - 5))
        self.assertEqual(len(calls), 1)
        with self.assertRaises(ValueError): core.decode_closed_body(raw, self.start)
        for bad in [b"\xff\xe0", raw + b"\xc3", b"\xeb\x70" + raw, b"\xc3" + raw]:
            with self.subTest(raw=bad.hex()), self.assertRaises(ValueError):
                core.decode_closed_body(bad, self.start, tail=True)

    def test_static_entry_and_zero_storage_never_accept_fake_providers_or_overruns(self):
        pe = MemoryPE()
        life.validate_static_entry(pe, {self.start: [("__DllMainCRTStartup@12", "libcmt:dllcrt0.obj")]})
        for owner in [self.owner, "fake:libcmt:dllcrt0.obj", "libcmt:crt0.obj"]:
            with self.assertRaises(ValueError):
                life.validate_static_entry(pe, {self.start: [("__DllMainCRTStartup@12", owner)]})
        life.writable_zero(pe, core.IMAGE_BASE + 0x3000, 60)
        for address, size in [(core.IMAGE_BASE + 0x1000, 60), (core.IMAGE_BASE + 0x3001, 60),
                              (core.IMAGE_BASE + 0x3ffc, 60)]:
            with self.assertRaises(ValueError): life.writable_zero(pe, address, size)
        pe.put(0x3038, b"\x01")
        with self.assertRaises(ValueError): life.writable_zero(pe, core.IMAGE_BASE + 0x3000, 60)

    def eh_fixture(self):
        pe, target = MemoryPE(), MemoryPE(0x400000)
        for image in (pe, target): image.put(0x1000, b"\xcc" * 0x1000)
        symbol = "??0Owner@@QAE@XZ"
        functions = {self.start: [(symbol, self.owner)], self.start + 0x100:
            [("__unwindfunclet$" + symbol + "$0", "CIL library: CIL module")],
            self.start + 0x110: [("__ehhandler$" + symbol, "CIL library: CIL module")],
            self.start + 0x120: [("_next", self.owner)]}
        for image in (pe, target):
            base = image.OPTIONAL_HEADER.ImageBase
            image.put(0x1000, b"\x68" + struct.pack("<I", base + 0x1110) + b"\x59\xc3")
            image.put(0x1100, b"\x8b\x4d\xf0\xe9" + struct.pack("<i", 0x1800 - 0x1108))
            image.put(0x1110, b"\xb8" + struct.pack("<I", base + 0x2000)
                      + b"\xe9" + struct.pack("<i", 0x1900 - 0x111a))
            image.put(0x2000, struct.pack("<9I", 0x19930522, 1, base + 0x2030, 0, 0, 0, 0, 0, 1))
            image.put(0x2030, struct.pack("<iI", -1, base + 0x1100))
        pe.relocations(0x1001, 0x1111, 0x2008, 0x2034)
        return dict(function=dict(symbol_base=symbol, address="0x00401000",
                    eh_cleanup=dict(handler="0x00401110", info="0x00402000")),
            pe=pe, target=target, functions=functions, exports={}, cil_owner=self.owner,
            start=self.start, raw=pe.get_data(0x1000, 7), target_raw=target.get_data(0x1000, 7),
            refs=[], bindings=[], vtables=[], resolve=lambda at: ("_cleanup" if at % 0x1000 == 0x800 else "_handler",
                at - core.IMAGE_BASE + 0x400000), game_range=self.game,
            read_target=lambda at, size: target.get_data(at - 0x400000, size))

    def test_complete_cleanup_metadata_and_code_are_required_even_when_parent_matches(self):
        f = self.eh_fixture()
        refs, reports = life.cleanup_eh(**f)
        self.assertEqual([r["kind"] for r in reports], ["cleanup handler", "cleanup funclet 0", "FuncInfo", "unwind map"])
        self.assertEqual(sum(r["size"] for r in reports), 62)
        self.assertEqual(refs[0]["kind"], "eh_handler")
        # All failures retain the exact same parent code: no parent-only exact credit.
        changes = [lambda f: f["pe"].put(0x1102, b"\xec"),
            lambda f: f["pe"].put(0x2000, struct.pack("<I", 0x19930521)),
            lambda f: f["pe"].put(0x2004, struct.pack("<I", 0)),
            lambda f: f["pe"].put(0x2010, struct.pack("<I", 1)),
            lambda f: f["target"].put(0x2020, struct.pack("<I", 0)),
            lambda f: f["pe"].put(0x2030, struct.pack("<i", 0)),
            lambda f: f["pe"].put(0x2034, struct.pack("<I", core.IMAGE_BASE + 0x1101)),
            lambda f: f["pe"].relocations(0x1001, 0x1111, 0x2034),
            lambda f: f["pe"].relocations(0x1001, 0x1111, 0x2008, 0x2034, 0x200c),
            lambda f: f["functions"].update({self.start + 0x100: [("__unwindfunclet$??0Owner@@QAE@XZ$0", "fake.obj")]}),
            lambda f: f["exports"].update({"_alias": self.start + 0x110})]
        for change in changes:
            bad = self.eh_fixture(); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError): life.cleanup_eh(**bad)

    def test_eh_pointer_replay_rejects_missing_extra_and_straddling_highlow_fields(self):
        pe = MemoryPE(); start = core.IMAGE_BASE + 0x2000
        raw = struct.pack("<II", 7, core.IMAGE_BASE + 0x2030)
        pe.relocations(0x2004)
        self.assertEqual(life.rebase_data(pe, start, raw, {4: (core.IMAGE_BASE + 0x2030, 0x602000)}),
                         struct.pack("<II", 7, 0x602000))
        for rvas in [[], [0x2004, 0x2004], [0x2003], [0x2004, 0x2000], [0x1fff, 0x2004]]:
            pe.relocations(*rvas)
            with self.assertRaises(ValueError): life.rebase_data(pe, start, raw, {4: (core.IMAGE_BASE + 0x2030, 0x602000)})

    def object_fixture(self):
        unit = self.contract(); unit["link_runtime_data"] = []
        obj = unit["link_objects"][0]
        obj.update(initializer="0x00401300", initializer_table="0x00402004",
                   atexit="0x00401800", destructor_callback="0x00401320")
        unit["functions"][0]["address"] = "0x00401000"
        unit["functions"][1]["address"] = "0x00401020"
        pe, target = MemoryPE(), MemoryPE(0x400000)
        stem = self.symbol[1:].split("@@", 1)[0] + "@@YAXXZ"
        functions = {self.start: [(unit["functions"][0]["symbol_base"], self.owner)],
            self.start + 0x20: [(unit["functions"][1]["symbol_base"], self.owner)],
            self.start + 0x300: [("??__E" + stem, "CIL library: CIL module")],
            self.start + 0x320: [("??__F" + stem, "CIL library: CIL module")],
            self.start + 0x340: [("_next", self.owner)]}
        for image in (pe, target):
            base = image.OPTIONAL_HEADER.ImageBase
            image.put(0x1000, b"\xcc" * 0x1000)
            image.put(0x1300, b"\xe8" + struct.pack("<i", 0x1000 - 0x1305)
                + b"\x68" + struct.pack("<I", base + 0x1320)
                + b"\xe8" + struct.pack("<i", 0x1800 - 0x130f) + b"\x59\xc3")
            image.put(0x1320, b"\xe9" + struct.pack("<i", 0x1020 - 0x1325))
            image.put(0x1800, b"\xc3")
            image.put(0x2000, struct.pack("<III", 0, base + 0x1300, 0))
        pe.relocations(0x1306, 0x2004)
        symbols = {self.symbol: [(core.IMAGE_BASE + 0x3000, self.owner)],
            "_atexit": [(core.IMAGE_BASE + 0x1800, "f libcmt:onexit.obj")],
            "___xc_a": [(core.IMAGE_BASE + 0x2000, "libcmt:crt0init.obj")],
            "___xc_z": [(core.IMAGE_BASE + 0x2008, "libcmt:crt0init.obj")]}
        return dict(unit=unit, pe=pe, target=target, functions=functions, symbols=symbols,
            exports={}, cil_owner=self.owner,
            known={"global": (0x403000, bytes(4), frozenset({0, 4, 56}), "address")},
            read_target=lambda at, size: target.get_data(at - 0x400000, size))

    def object_witness(self, fixture):
        with patch.object(life.csv, "DictReader", side_effect=[
                [dict(address="0x00401800", current_name="_atexit", size="1")],
                [dict(address="0x00401800", origin="vc8_runtime", disposition="exclude")]]):
            return life.object_witnesses(**fixture)

    def test_global_reachability_requires_the_entire_native_startup_chain_and_zero_object(self):
        refs, witness = self.object_witness(self.object_fixture())
        self.assertEqual(len(refs), 3)
        self.assertEqual(witness[self.symbol]["source_initializer_slot"], core.IMAGE_BASE + 0x2004)
        changes = [lambda f: f["pe"].put(0x130f, b"\x58"),
            lambda f: f["pe"].put(0x1321, bytes(4)),
            lambda f: f["target"].put(0x1301, bytes(4)),
            lambda f: f["target"].put(0x1321, bytes(4)),
            lambda f: f["target"].put(0x2004, bytes(4)),
            lambda f: f["target"].put(0x303b, b"\x01"),
            lambda f: f["pe"].put(0x3004, b"\x01"),
            lambda f: f["pe"].put(0x2000, b"\x01"),
            lambda f: f["pe"].relocations(0x1306),
            lambda f: f["pe"].relocations(0x2004),
            lambda f: f["pe"].relocations(0x1306, 0x2004, 0x1321),
            lambda f: f["exports"].update({"_fake": self.start}),
            lambda f: f["symbols"].update({"_alias": [(core.IMAGE_BASE + 0x3038, self.owner)]}),
            lambda f: f["symbols"].update({"_atexit": [(core.IMAGE_BASE + 0x1800, self.owner)]}),
            lambda f: f["known"].update(global_ignored=None, **{"global": (0x403000, bytes(4), frozenset({60}), "address")})]
        for change in changes:
            bad = self.object_fixture(); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError): self.object_witness(bad)


if __name__ == "__main__":
    unittest.main()
