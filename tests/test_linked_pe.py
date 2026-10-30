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
        linked.validate_contract({**unit, "preserve_public_members": ["??1Owner@game@@QAE@XZ"]}, set())
        for preserved in [["??0Owner@game@@QAE@XZ"], ["??1Owner@game@@UAE@XZ"], [symbol, symbol], ["_cdecl"], ["??_GPool@@UAEPAXI@Z"],
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

    def test_source_only_single_caller_keeps_exact_edge_checks(self):
        f = self.private_fixture()
        f["function"]["private_from"]["source_only_caller"] = True
        witness = linked.private_caller_witness(**f)
        self.assertEqual(witness["source_only_address_fields"], [])
        self.assertIn("no caller byte or EH equality", witness["scope"])
        f["function"]["private_from"]["site"] = "0x00401001"
        with self.assertRaises(ValueError):
            linked.private_caller_witness(**f)

    def test_source_only_caller_requires_actual_included_source(self):
        f = self.private_fixture()
        f['function']['private_from']['source_only_caller'] = True
        f['ledger']['0x00401000']['source_file'] = 'src/assets/Included.cpp'
        path = linked.ROOT / 'src/assets/Included.cpp'
        with patch('workflow_manifest.source_dependencies', return_value={path}):
            self.assertIn('no caller byte or EH equality', linked.private_caller_witness(**f)['scope'])
        with patch('workflow_manifest.source_dependencies', return_value=set()), self.assertRaises(ValueError):
            linked.private_caller_witness(**f)

    def test_private_constructor_pair_requires_both_complete_edges(self):
        f = self.private_fixture()
        root, child = self.start, self.start + 0x20
        raw = (b"\xe8" + struct.pack("<i", child-root-5)
               + b"\xe8" + struct.pack("<i", child-root-10) + b"\xc3")
        f["pe"].data[0x1000:0x1020] = raw + b"\xcc" * (0x20-len(raw))
        target = (b"\xe8" + struct.pack("<i", 0x402000-0x401000-5)
                  + b"\xe8" + struct.pack("<i", 0x402000-0x401000-10) + b"\xc3")
        f["ledger"]["0x00401000"]["size"] = str(len(target))
        f["read_target"] = lambda address, size: target
        f["function"]["private_from"] = {"caller": "0x00401000", "sites": ["0x00401000", "0x00401005"]}
        witness = linked.private_caller_witness(**f)
        self.assertEqual(witness["target_sites"], ["0x00401000", "0x00401005"])
        self.assertEqual(witness["source_sites"], [f"0x{root:08X}", f"0x{root+5:08X}"])
        for sites in [["0x00401000"], ["0x00401005", "0x00401000"],
                      ["0x00401000", "0x00401000"], ["0x00401000", "0x00401006"]]:
            bad = copy.deepcopy(f); bad["function"]["private_from"]["sites"] = sites
            with self.subTest(sites=sites), self.assertRaises(ValueError):
                linked.private_caller_witness(**bad)
        bad = copy.deepcopy(f); bad["pe"].data[0x1005:0x100a] = b"\x90" * 5
        with self.assertRaises(ValueError): linked.private_caller_witness(**bad)

    def test_exact_private_parent_contract_requires_an_explicit_direct_ancestor(self):
        f = self.private_fixture()
        f['unit']['functions'].append({'address':'0x00403000','symbol_base':'_leaf@4',
            'private_from':{'caller':'0x00402000','site':'0x00402000','through_exact_caller':True}})
        u = {**f['unit'], 'profile':linked.PROFILE, 'object':'build/test.dll', 'link_data_targets':[]}
        linked.validate_contract(u,set())
        public_parent=copy.deepcopy(u);public_parent['functions'][1].pop('private_from')
        linked.validate_contract(public_parent,set())
        changes = [lambda u:u['functions'][2]['private_from'].update(through_exact_caller=False),
            lambda u:u['functions'][1].update(private_global={'object':'missing','role':'constructor'}),
            lambda u:u['functions'][1]['private_from'].update(through_exact_caller=True),
            lambda u:u['functions'][2]['private_from'].update(caller_eh={'handler':'0x00404000','info':'0x00405000'})]
        for change in changes:
            v=copy.deepcopy(u);change(v)
            with self.assertRaises(ValueError):linked.validate_contract(v,set())

    def test_exact_private_parent_witness_rejects_missing_or_stale_full_replay(self):
        import hashlib
        f=self.private_fixture();f['ledger']['0x00401000']['status']='matching'
        parent=f['unit']['functions'][0]
        parent['private_from']={'caller':'0x00400000','site':'0x00400000'}
        f['exports']={}
        f['function']['private_from']['through_exact_caller']=True
        raw=linked.linked_body(f['pe'],f['functions'],self.start)
        target=f['read_target'](0x401000,6);h=hashlib.sha256(target).hexdigest()
        report={'result':'exact','address':'0x00401000','linked_function_va':f'0x{self.start:08X}',
            'source_body_sha256':hashlib.sha256(raw).hexdigest(),'target_sha256':h,
            'object_compared_sha256':h,'validated_data_references':[],
            'private_caller_witness':{'caller':'0x00400000'}}
        f['exact_caller_replay']=report
        self.assertIn('exact_caller',linked.private_caller_witness(**f))
        for key,value in [('result','mismatch'),('address','0x00403000'),
                          ('source_body_sha256','bad'),('object_compared_sha256','bad'),
                          ('private_caller_witness',None)]:
            bad=copy.deepcopy(f);bad['exact_caller_replay'][key]=value
            with self.subTest(key=key),self.assertRaises(ValueError):linked.private_caller_witness(**bad)
        f.pop('exact_caller_replay')
        with self.assertRaises(ValueError):linked.private_caller_witness(**f)

    def eh_private_fixture(self):
        f = self.private_fixture()
        root, child, handler = self.start, self.start + 0x100, self.start + 0x120
        cookie, info = linked.IMAGE_BASE + 0x3000, linked.IMAGE_BASE + 0x2100
        check, unwind = self.start + 0x150, self.start + 0x160
        def body(at, h, ck, call):
            return (b'\x68' + struct.pack('<I', h) + b'\xa1' + struct.pack('<I', ck)
                    + b'\xe8' + struct.pack('<i', call - at - 15) + b'\x83\xc4\x04\xc3')
        def eh(at, ci, ch, uw):
            return (bytes.fromhex('8b5424088d42e48b4ae033c8e8')
                    + struct.pack('<i', ch-at-17) + b'\xb8' + struct.pack('<I', ci)
                    + b'\xe9' + struct.pack('<i', uw-at-27))
        raw = body(root, handler, cookie, child)
        f['pe'].data[0x1000:0x1140] = b'\xcc' * 0x140
        f['pe'].data[0x1000:0x1000+len(raw)] = raw
        f['pe'].data[0x1100:0x1101] = b'\xc3'
        f['pe'].data[0x1120:0x113b] = eh(handler, info, check, unwind)
        info_data = struct.pack('<9I', 0x19930522, 1, linked.IMAGE_BASE+0x2140, 0, 0, 0, 0, 0, 1)
        f['pe'].data[0x2100:0x2124] = info_data
        f['pe'].data[0x2140:0x2148] = struct.pack('<iI', -1, self.start+0x180)
        f['pe'].DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[
            SimpleNamespace(type=3, rva=0x1001), SimpleNamespace(type=3, rva=0x1006),
            SimpleNamespace(type=3, rva=0x1132), SimpleNamespace(type=3, rva=0x2108),
            SimpleNamespace(type=3, rva=0x2144)])]
        f['functions'] = {root: [('_root@4', 'root.ltcg.obj')],
            child: [('_child@4', 'root.ltcg.obj')],
            handler: [('__ehhandler$_root@4', 'CIL library: CIL module')],
            handler+27: [('_next', 'root.ltcg.obj')],
            check: [('@__security_check_cookie@4', 'libcmt:secchk.obj')],
            unwind: [('___CxxFrameHandler3', 'libcmt:ehhandler.obj')],
            self.start+0x180: [('__unwindfunclet$_root@4$0', 'CIL library: CIL module')]}
        native = body(0x401000, 0x403000, 0x6f7a88, 0x402000)
        native_eh = eh(0x403000, 0x404000, 0x689d25, 0x6899e7)
        f['ledger']['0x00401000']['size'] = str(len(native))
        def read(a, n):
            data = {0x401000: native, 0x403000: native_eh + b'\xcc'*101,
                    0x404000: struct.pack('<9I', 0x19930522, 1, 0x404040, 0, 0, 0, 0, 0, 1),
                    0x404040: struct.pack('<iI', -1, 0x403100)}
            return data.get(a, b'')[:n]
        f['read_target'] = read
        f['unit'].update(link_runtime='static', link_runtime_data=['___security_cookie'])
        f['function']['private_from'] = {'caller': '0x00401000', 'site': '0x0040100A',
            'caller_eh': {'handler': '0x00403000', 'info': '0x00404000'}}
        f['internal_refs'] = [{'kind': 'runtime', 'symbol': '___security_cookie', 'size': 4,
                               'source_address': cookie, 'address': 0x6f7a88}]
        f['game_range'] = self.game
        return f

    def test_private_eh_caller_records_roles_without_accepting_caller_bytes(self):
        f = self.eh_private_fixture()
        r = linked.private_caller_witness(**f)
        self.assertEqual(len(r['source_only_address_fields']), 2)
        self.assertFalse(r['caller_eh_identity']['caller_or_eh_exactness_claimed'])
        self.assertEqual(r['target_site'], '0x0040100A')

    def test_private_eh_caller_rejects_unqualified_cookie_handler_info_and_fields(self):
        changes = [lambda f: f.update(internal_refs=[]),
            lambda f: f['function']['private_from']['caller_eh'].update(handler='0x00403001'),
            lambda f: f['function']['private_from']['caller_eh'].update(info='0x00404001'),
            lambda f: f['pe'].data.__setitem__(slice(0x1006,0x100a),struct.pack('<I',linked.IMAGE_BASE+0x3004)),
            lambda f: f['pe'].DIRECTORY_ENTRY_BASERELOC.clear(),
            lambda f: f['pe'].data.__setitem__(0x2104,2),
            lambda f: f['functions'][self.start+0x120].append(('_alias','root.ltcg.obj')),
            lambda f: f['unit'].update(link_runtime='import')]
        for change in changes:
            f = self.eh_private_fixture(); change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):
                linked.private_caller_witness(**f)

    def test_private_eh_contract_does_not_relax_legacy_single_or_two_edge_forms(self):
        f = self.eh_private_fixture()
        unit = {**f['unit'], 'profile': linked.PROFILE, 'object': 'build/test.dll',
                'link_data_targets': []}
        linked.validate_contract(unit, set())
        for mutate in [lambda u: u['functions'][1]['private_from']['caller_eh'].update(extra='waive'),
                       lambda u: u.update(link_runtime_data=[]),
                       lambda u: u['functions'][1]['private_from'].update(sites=['0x0040100A'])]:
            bad = copy.deepcopy(unit); mutate(bad)
            with self.assertRaises(ValueError): linked.validate_contract(bad, set())
        del f['function']['private_from']['caller_eh']
        with self.assertRaises(ValueError): linked.private_caller_witness(**f)

    def literal_fixture(self):
        import linked_literals
        symbol='??_C@_02PCIJFNDE@?$AN?6?$AA@'
        source=VTablePe();target=VTablePe(base=0x400000)
        source.data[0x2000:0x2003]=target.data[0x2000:0x2003]=b'\r\n\0'
        return dict(unit={'link_literals':[{'symbol':symbol,'target':symbol,'read_offsets':[0,2]}]},
            source=source,target=target,symbols={symbol:[(linked.IMAGE_BASE+0x2000,'root.ltcg.obj')]},
            cil_owner='root.ltcg.obj',known={symbol:(0x402000,b'\r\n\0',frozenset({0,2}),'literal')})

    def test_cil_literal_requires_named_complete_readonly_objects_and_existing_offsets(self):
        import linked_literals
        f=self.literal_fixture();refs=linked_literals.witnesses(**f)
        self.assertEqual([(r['read_offset'],r['size']) for r in refs],[(0,3),(2,1)])
        symbol=f['unit']['link_literals'][0]['symbol']
        changes=[lambda f:f['source'].data.__setitem__(0x2000,0),
            lambda f:f['target'].data.__setitem__(0x2001,0),
            lambda f:setattr(f['source'].sections[1],'Characteristics',0xc0000040),
            lambda f:f['symbols'].update({symbol:[(linked.IMAGE_BASE+0x2000,'foreign.obj')]}),
            lambda f:f['unit']['link_literals'][0].update(read_offsets=[1]),
            lambda f:f['known'].update({symbol:(0x402000,b'\r\n',frozenset({0,2}),'literal')})]
        for change in changes:
            bad=self.literal_fixture();change(bad)
            with self.subTest(change=change),self.assertRaises(ValueError):linked_literals.witnesses(**bad)

    def test_cil_literal_pointer_requires_explicit_base_only_contract(self):
        import linked_literals
        f = self.literal_fixture()
        entry = f['unit']['link_literals'][0]
        entry.update(read_offsets=[0], allow_pointer_push=True)
        self.assertTrue(linked_literals.witnesses(**f)[0]['allow_pointer_push'])
        for value, offsets in ((False, [0]), (1, [0]), (True, [0, 2]), (True, [2])):
            entry.update(read_offsets=offsets, allow_pointer_push=value)
            with self.assertRaises(ValueError): linked_literals.witnesses(**f)

    def test_cil_literal_replays_only_declared_in_bounds_register_reads(self):
        import linked_literals
        f=self.literal_fixture();refs=linked_literals.witnesses(**f);base=linked.IMAGE_BASE+0x2000
        raw=b'\x66\xa1'+struct.pack('<I',base)+b'\x8a\x0d'+struct.pack('<I',base+2)+b'\xc3'
        canonical,_,data=linked.canonicalize(raw,self.start,self.target,[],lambda a:None,
            self.image,self.game,internal_refs=refs)
        self.assertEqual(canonical,b'\x66\xa1'+struct.pack('<I',0x402000)+b'\x8a\x0d'+struct.pack('<I',0x402002)+b'\xc3')
        self.assertEqual(len(data),2)
        for raw in [b'\xa1'+struct.pack('<I',base)+b'\xc3',
                    b'\x8a\x0d'+struct.pack('<I',base+1)+b'\xc3',
                    b'\x66\xa3'+struct.pack('<I',base)+b'\xc3',
                    b'\x68'+struct.pack('<I',base)+b'\xc3']:
            with self.subTest(raw=raw.hex()),self.assertRaises(ValueError):
                linked.canonicalize(raw,self.start,self.target,[],lambda a:None,
                                   self.image,self.game,internal_refs=refs)

    def test_cil_literal_contract_rejects_arbitrary_aliases_and_extent_waivers(self):
        import linked_literals
        f=self.literal_fixture();keys=set(f['known']);linked_literals.validate(f['unit'],keys)
        for change in [lambda u:u['link_literals'][0].update(symbol='_alias'),
                       lambda u:u['link_literals'][0].update(read_offsets=[0,3]),
                       lambda u:u['link_literals'][0].update(read_offsets=[2,0]),
                       lambda u:u['link_literals'][0].update(ignore_bytes=True),
                       lambda u:u['link_literals'].append(copy.deepcopy(u['link_literals'][0]))]:
            u=copy.deepcopy(f['unit']);change(u)
            with self.assertRaises(ValueError):linked_literals.validate(u,keys)

    def path_fixture(self):
        root, middle, child = self.start, self.start + 0x20, self.start + 0x40
        pe = VTablePe()
        pe.data[0x1000:0x1050] = b"\xcc" * 0x50
        pe.data[0x1000:0x1006] = b"\xe8" + struct.pack("<i", middle-root-5) + b"\xc3"
        pe.data[0x1020:0x102e] = (b"\x68" + struct.pack("<I", linked.IMAGE_BASE+0x2000)
            + b"\xe8" + struct.pack("<i", child-middle-10) + b"\x83\xc4\x04\xc3")
        pe.data[0x1040:0x1043] = b"\xc2\x04\x00"
        pe.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[SimpleNamespace(type=3, rva=0x1021)])]
        parent = {"address": "0x00401000", "symbol_base": "_root@4",
                  "rel32_targets": ["_middle=0x00402000"]}
        function = {"address": "0x00403000", "symbol_base": "_child@4", "private_from": {
            "caller": "0x00401000", "site": "0x00401000", "source_file": "src/owner.cpp",
            "via": [{"address": "0x00402000", "symbol_base": "_middle", "site": "0x00402005"}]}}
        targets = {0x401000: b"\xe8"+struct.pack("<i", 0x402000-0x401000-5)+b"\xc3",
                   0x402000: b"\x68\x00\x00\x6e\x00\xe8"+struct.pack("<i", 0x403000-0x402000-10)+b"\x83\xc4\x04\xc3"}
        return {"function": function, "unit": {"source": "src/aggregate.cpp", "functions": [parent, function]},
                "pe": pe, "functions": {root: [("_root@4", "root.ltcg.obj")],
                    middle: [("_middle", "CIL library: CIL module")], child: [("_child@4", "root.ltcg.obj")],
                    root+0x50: [("_next", "root.ltcg.obj")]}, "exports": {"_root@4": root},
                "cil_owner": "root.ltcg.obj", "ledger": {f"0x{a:08X}": {
                    "size": str(len(raw)), "status": "implemented", "source_file": "src/owner.cpp"}
                    for a, raw in targets.items()}, "read_target": lambda a,s: targets[a] if len(targets[a])==s else b"",
                "map_text": f" Static symbols\n 0001:00000020 _middle {middle:08x} f CIL library: CIL module\n",
                "bindings": [], "game_range": self.game}

    def path_witness(self, fixture):
        with patch("workflow_manifest.source_dependencies", return_value={linked.ROOT/"src/owner.cpp"}):
            return linked.private_caller_witness(**fixture)

    def test_static_private_path_records_both_complete_caller_edges_without_accepting_parents(self):
        f = self.path_fixture()
        result = self.path_witness(f)
        self.assertEqual([e["caller"] for e in result["edges"]], ["0x00401000", "0x00402000"])
        refs = result["edges"][1]["source_only_address_fields"]
        self.assertEqual([(r["kind"], r["field_offset"]) for r in refs], [("source_only", 1)])
        self.assertIn("no caller byte or EH equality", result["scope"])
        unit = {**f["unit"], "profile": linked.PROFILE, "object": "build/path.dll", "link_data_targets": []}
        linked.validate_contract(unit, set())

    def static_leaf_fixture(self, direct=False):
        f = self.path_fixture()
        f["function"]["private_static_leaf"] = True
        f["functions"][self.start+0x40] = [("_child@4", "CIL library: CIL module")]
        f["map_text"] += f" 0001:00000040 _child@4 {self.start+0x40:08x} f CIL library: CIL module\n"
        f["ledger"]["0x00403000"] = {
            "size": "3", "status": "implemented", "source_file": "src/owner.cpp"}
        if direct:
            f["function"]["private_from"]["via"] = []
            f["unit"]["functions"][0]["rel32_targets"] = ["_child@4=0x00403000"]
            f["pe"].data[0x1000:0x1006] = (
                b"\xe8"+struct.pack("<i", 0x40-5)+b"\xc3")
            target = b"\xe8"+struct.pack("<i", 0x403000-0x401000-5)+b"\xc3"
            f["read_target"] = lambda a,s: target if (a,s)==(0x401000,6) else b""
        return f

    def test_static_leaf_needs_full_direct_or_intermediate_path_without_relaxing_object_ownership(self):
        for direct in (False, True):
            f = self.static_leaf_fixture(direct)
            result = self.path_witness(f)
            self.assertEqual(result["static_leaf"]["source_va"], f"0x{self.start+0x40:08X}")
            self.assertEqual(len(result["edges"]), 1 if direct else 2)
            unit = {**f["unit"], "profile": linked.PROFILE, "object": "build/path.dll",
                    "link_data_targets": []}
            linked.validate_contract(unit, set())
            with self.assertRaises(ValueError):
                linked.source_function_start(f["function"], f["functions"], f["exports"], f["cil_owner"])

    def test_static_leaf_rejects_unreviewed_source_missing_calls_and_wrong_target_sites(self):
        changes = [lambda f: f["ledger"].pop("0x00403000"),
                   lambda f: f["ledger"]["0x00403000"].update(status="candidate"),
                   lambda f: f["ledger"]["0x00403000"].update(source_file="src/other.cpp"),
                   lambda f: f["function"]["private_from"].update(site="0x00401001"),
                   lambda f: f["pe"].data.__setitem__(slice(0x1001,0x1005), struct.pack("<i",0x20-5))]
        for change in changes:
            f = self.static_leaf_fixture(True);change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):self.path_witness(f)

    def test_static_leaf_rejects_foreign_duplicate_exported_or_missing_map_identity(self):
        changes = [lambda f: f["exports"].update(_alias=self.start+0x40),
                   lambda f: f["functions"].update({self.start+0x40: [("_child@4", "other.obj")]}),
                   lambda f: f["functions"][self.start+0x40].append(("_alias", "CIL library: CIL module")),
                   lambda f: f["functions"].update({self.start+0x60: [("_child@4", "CIL library: CIL module")]}),
                   lambda f: f.update(map_text=f["map_text"].replace("_child@4", "_other")),
                   lambda f: f.update(map_text="")]
        for change in changes:
            f = self.static_leaf_fixture(True);change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):self.path_witness(f)

    def test_static_leaf_contract_cannot_be_a_boolean_waiver_or_an_export(self):
        changes = [lambda f: f.update(private_static_leaf=False),
                   lambda f: f.update(private_static_leaf=1),
                   lambda f: f.update(private_static_leaf="true"),
                   lambda f: f.pop("private_from"),
                   lambda f: f["private_from"].pop("via"),
                   lambda f: f.update(export_name="_child@4")]
        for change in changes:
            f = self.static_leaf_fixture(True);change(f["function"])
            unit = {**f["unit"], "profile": linked.PROFILE, "object": "build/path.dll",
                    "link_data_targets": []}
            with self.subTest(change=change), self.assertRaises(ValueError):
                linked.validate_contract(unit, set())

    def test_static_path_contract_rejects_cycles_aliases_malformed_nodes_and_source_escape(self):
        changes = [lambda c: c.update(via=[]), lambda c: c.update(via=True),
                   lambda c: c.update(source_file="../src/owner.cpp"), lambda c: c.update(extra="waive"),
                   lambda c: c["via"][0].update(address="0x00401000"),
                   lambda c: c["via"][0].update(address="0x00403000"),
                   lambda c: c["via"][0].update(symbol_base="_child@4"),
                   lambda c: c["via"][0].update(site="wrong"),
                   lambda c: c["via"].append(copy.deepcopy(c["via"][0]))]
        for change in changes:
            f = self.path_fixture();change(f["function"]["private_from"])
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.path_witness(f)

    def test_static_path_requires_actual_included_reviewed_source_and_exported_anchor(self):
        f = self.path_fixture()
        with patch("workflow_manifest.source_dependencies", return_value=set()), self.assertRaises(ValueError):
            linked.private_caller_witness(**f)
        changes = [lambda f: f["ledger"]["0x00402000"].update(status="candidate"),
                   lambda f: f["ledger"]["0x00402000"].update(source_file="src/other.cpp"),
                   lambda f: f["exports"].clear(),
                   lambda f: f["unit"]["functions"][0].update(rel32_targets=[])]
        for change in changes:
            f = self.path_fixture();change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):self.path_witness(f)

    def test_static_path_rejects_exported_or_unowned_intermediates_and_missing_static_table(self):
        changes = [lambda f: f["exports"].update(_alias=self.start+0x20),
                   lambda f: f.update(map_text=""),
                   lambda f: f["functions"].update({self.start+0x20: [("_middle", "other.obj")]}),
                   lambda f: f["functions"][self.start+0x20].append(("_alias", "CIL library: CIL module")),
                   lambda f: f.update(map_text=f["map_text"].replace("_middle", "_other"))]
        for change in changes:
            f = self.path_fixture();change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):self.path_witness(f)

    def test_static_path_checks_both_edges_and_rejects_unreachable_or_cropped_callers(self):
        changes = [lambda f: f["function"]["private_from"].update(site="0x00401001"),
                   lambda f: f["function"]["private_from"]["via"][0].update(site="0x00402006"),
                   lambda f: f["pe"].data.__setitem__(slice(0x1020,0x1025), b"\xc3\x90\x90\x90\x90"),
                   lambda f: f["pe"].data.__setitem__(slice(0x1025,0x102a), b"\xe8\x00\x00\x00\x00"),
                   lambda f: f["pe"].data.__setitem__(slice(0x102a,0x102e), b"\x83\xc4\x04\x90")]
        for change in changes:
            f = self.path_fixture();change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):self.path_witness(f)

    def test_static_path_address_fields_require_exact_highlow_operand_coverage(self):
        changes = [lambda f: f["pe"].DIRECTORY_ENTRY_BASERELOC.clear(),
                   lambda f: setattr(f["pe"].DIRECTORY_ENTRY_BASERELOC[0].entries[0], "type", 2),
                   lambda f: setattr(f["pe"].DIRECTORY_ENTRY_BASERELOC[0].entries[0], "rva", 0x1026),
                   lambda f: f["pe"].DIRECTORY_ENTRY_BASERELOC[0].entries.append(SimpleNamespace(type=3,rva=0x1021)),
                   lambda f: f["pe"].data.__setitem__(slice(0x1021,0x1025),struct.pack("<I", self.start+1)),
                   lambda f: f["pe"].data.__setitem__(slice(0x1021,0x1025),struct.pack("<I", 0x6e0000))]
        for change in changes:
            f = self.path_fixture();change(f)
            with self.subTest(change=change), self.assertRaises(ValueError):self.path_witness(f)

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

    def test_numeric_literals_require_ieee_identity_and_full_x87_reads(self):
        import linked_numeric_literals as numbers
        symbol = "__real@41f0000000000000"
        raw = bytes.fromhex("000000000000f041")
        source, target = VTablePe(), VTablePe(0x400000)
        start, dst = linked.IMAGE_BASE + 0x2010, 0x402010
        source.data[0x2010:0x2018] = raw; target.data[0x2010:0x2018] = raw
        unit = {"link_numeric_literals": [{"symbol": symbol, "target": symbol}]}
        symbols = {symbol: [(start, "CIL library: CIL module")]}
        known = {symbol: (dst, raw, frozenset({0}), "literal")}
        refs = numbers.witnesses(unit, source, target, symbols, known)
        self.assertEqual(refs[0]["size"], 8)
        code = b"\xd9\xee\xdc\x05" + struct.pack("<I", start) + b"\xc3"
        canonical, _, _ = linked.canonicalize(code, self.start, self.target, [], None,
            self.image, self.game, internal_refs=refs)
        self.assertEqual(canonical[4:8], struct.pack("<I", dst))
        for bad in [b"\xdd\x1d" + struct.pack("<I", start) + b"\xc3",
                    b"\xd9\x05" + struct.pack("<I", start) + b"\xc3",
                    b"\x68" + struct.pack("<I", start) + b"\xc3"]:
            with self.assertRaises(ValueError):
                linked.canonicalize(bad, self.start, self.target, [], None,
                    self.image, self.game, internal_refs=refs)
        with self.assertRaises(ValueError):
            numbers.witnesses(unit, source, target,
                {symbol: [(start, "Other.obj")]}, known)
        source.data[0x2010] = 1
        with self.assertRaises(ValueError):
            numbers.witnesses(unit, source, target, symbols, known)
        with self.assertRaises(ValueError):
            numbers.encoded_bytes("__real@not_a_number")

    def test_xiph_sdk_requires_exact_archive_members_and_static_crt(self):
        import hashlib
        import io
        import zipfile
        import linked_xiph_sdk as xiph
        members = {name: b"!<arch>\n" + name.encode() for name in xiph.MEMBERS}
        stream = io.BytesIO()
        with zipfile.ZipFile(stream, "w") as archive:
            for name, data in members.items():
                archive.writestr("oggvorbis-win32sdk-1.0.1/lib/" + name + "_static.lib", data)
        raw = stream.getvalue()
        pins = {name: hashlib.sha256(data).hexdigest() for name, data in members.items()}
        with patch.object(xiph, "ARCHIVE_SHA256", hashlib.sha256(raw).hexdigest()), patch.object(xiph, "MEMBERS", pins):
            self.assertEqual(xiph.verified_members(raw), members)
            with self.assertRaises(ValueError): xiph.verified_members(raw + b"x")
            with patch.dict(pins, {"ogg": "0" * 64}):
                with self.assertRaises(ValueError): xiph.verified_members(raw)
        xiph.validate({"link_xiph_sdk": True, "link_runtime": "static"})
        for unit in [{"link_xiph_sdk": True, "link_runtime": "import"},
                     {"link_xiph_sdk": "yes", "link_runtime": "static"}]:
            with self.assertRaises(ValueError): xiph.validate(unit)

    def test_ogg_callback_slots_require_actual_functions_and_bounded_reads(self):
        import linked_ogg_callbacks as callbacks
        source, target = VTablePe(), VTablePe(0x400000)
        target.data = bytearray(0x300000)
        target.sections[0].VirtualAddress = 0x18000
        target.sections[2].VirtualAddress = 0x2fa000
        start, dst, owner = linked.IMAGE_BASE + 0x3010, 0x6fa194, "Bgm.ltcg.obj"
        source_entries = [linked.IMAGE_BASE + 0x1010 + 16 * i for i in range(4)]
        target_entries = [address for _, address in callbacks.SLOTS]
        struct.pack_into("<4I", source.data, 0x3010, *source_entries)
        struct.pack_into("<4I", target.data, dst - 0x400000, *target_entries)
        source.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[
            SimpleNamespace(rva=0x3010 + 4 * i, type=3) for i in range(4)])]
        symbols = {callbacks.SYMBOL: [(start, owner)]}
        functions = {}
        known = {}
        for i, ((name, address), key, entry) in enumerate(zip(callbacks.SLOTS, callbacks.KEYS, source_entries)):
            symbols[name] = [(entry, owner)]; functions[entry] = [(name, owner)]
            known[key] = (dst, struct.pack("<I", address), frozenset({4 * i}), "address")
        unit = {"link_ogg_callbacks": True, "link_xiph_sdk": True}
        refs = callbacks.witnesses(unit, source, target, symbols, functions, owner, known)
        self.assertEqual([r["slot"] for r in refs], [0, 1, 2, 3])
        bad = copy.deepcopy(source); struct.pack_into("<I", bad.data, 0x3014, source_entries[0])
        with self.assertRaises(ValueError):
            callbacks.witnesses(unit, bad, target, symbols, functions, owner, known)
        bad = copy.deepcopy(source); bad.DIRECTORY_ENTRY_BASERELOC[0].entries.pop()
        with self.assertRaises(ValueError):
            callbacks.witnesses(unit, bad, target, symbols, functions, owner, known)
        with self.assertRaises(ValueError):
            callbacks.witnesses(unit, source, target, symbols, functions, "Other.obj", known)
        code = b"\xa1" + struct.pack("<I", start) + b"\xc3"
        canonical, _, _ = linked.canonicalize(code, self.start, self.target, [], None,
            self.image, self.game, internal_refs=refs)
        self.assertEqual(canonical[1:5], struct.pack("<I", dst))
        for code in [b"\xa3" + struct.pack("<I", start) + b"\xc3",
                     b"\x68" + struct.pack("<I", start) + b"\xc3"]:
            with self.assertRaises(ValueError):
                linked.canonicalize(code, self.start, self.target, [], None,
                    self.image, self.game, internal_refs=refs)

    def test_reader_vtables_require_exact_family_and_five_slots(self):
        import linked_reader_vtables as reader
        key = "??_7CFileReader@th105@@6B@"
        table = {"family": "CFileReader", "target": key,
                 "entries": ["0x00401000"] * 5}
        reader.validate({"link_reader_vtables": [table]}, {key})
        for bad in [{**table, "family": "Other"},
                    {**table, "target": "other"},
                    {**table, "entries": table["entries"][:4]},
                    {**table, "entries": table["entries"] + ["0x00401000"]}]:
            with self.subTest(table=bad), self.assertRaises(ValueError):
                reader.validate({"link_reader_vtables": [bad]}, {key})
        with self.assertRaises(ValueError):
            reader.validate({"link_reader_vtables": [table, table]}, {key})
        self.assertEqual(reader.slot_symbols("CPackageFileReader")[2],
                         "?last_read_size@CFileReader@th105@@UBEKXZ")

    def test_reader_vtable_checks_all_slots_rtti_and_source_relocations(self):
        import linked_reader_vtables as reader
        pe = VTablePe()
        base = linked.IMAGE_BASE
        vt, col, descriptor = [base + v for v in (0x2010, 0x2050, 0x3020)]
        entries = [base + 0x1010 + 16 * i for i in range(5)]
        struct.pack_into("<I5I", pe.data, 0x200c, col, *entries)
        struct.pack_into("<5I", pe.data, 0x2050, 0, 0, 0, descriptor, col + 20)
        name = b".?AVCFileReader@th105@@\0"
        pe.data[0x3028:0x3028 + len(name)] = name
        pe.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[
            SimpleNamespace(rva=0x2010 + 4 * i, type=3) for i in range(5)])]
        reader.inspect_table(pe, vt, entries, ".?AVCFileReader@th105@@")
        for offset, value in [(0x2014, entries[2]), (0x2024, entries[0]),
                              (0x2054, 4)]:
            bad = copy.deepcopy(pe)
            struct.pack_into("<I", bad.data, offset, value)
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                reader.inspect_table(bad, vt, entries, ".?AVCFileReader@th105@@")
        bad = copy.deepcopy(pe); bad.DIRECTORY_ENTRY_BASERELOC[0].entries.pop()
        with self.assertRaises(ValueError):
            reader.inspect_table(bad, vt, entries, ".?AVCFileReader@th105@@")
        with self.assertRaises(ValueError):
            reader.inspect_table(pe, vt, entries, ".?AVCPackageFileReader@th105@@")

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
        adjacent_pe = copy.deepcopy(pe)
        crt_entry = entry + 0x20
        struct.pack_into("<I", adjacent_pe.data, 0x2014, crt_entry)
        adjacent_pe.DIRECTORY_ENTRY_BASERELOC = [SimpleNamespace(entries=[SimpleNamespace(type=3, rva=0x2014)])]
        adjacent_symbols = {**symbols, "__pDestructExceptionObject": [(vt + 4, "libcmt:frame.obj")]}
        adjacent_functions = {**functions, crt_entry: [("___DestructExceptionObject", "libcmt:frame.obj")]}
        linked.source_vtables(adjacent_pe, adjacent_symbols, adjacent_functions, tables, "Pool.ltcg.obj")
        for wrong in ("Other.obj", "libcmt:fake.obj"):
            bad_symbols = {**adjacent_symbols, "__pDestructExceptionObject": [(vt + 4, wrong)]}
            with self.assertRaises(ValueError):
                linked.source_vtables(adjacent_pe, bad_symbols, adjacent_functions, tables, "Pool.ltcg.obj")
        adjacent_pe.DIRECTORY_ENTRY_BASERELOC = []
        with self.assertRaises(ValueError):
            linked.source_vtables(adjacent_pe, adjacent_symbols, adjacent_functions, tables, "Pool.ltcg.obj")
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

    def test_two_slot_resource_vtable_checks_both_source_methods(self):
        pe = VTablePe()
        vt, col, descriptor = [linked.IMAGE_BASE + v for v in (0x2010, 0x2040, 0x3020)]
        init, delete = self.start + 0x10, self.start + 0x20
        symbol = "??_7Pool@game@@6B@"
        initializer = "?initialize@Pool@game@@UAE_NPBXI@Z"
        destructor = "??_GPool@game@@UAEPAXI@Z"
        struct.pack_into("<IIII", pe.data, 0x200c, col, init, delete, 0)
        struct.pack_into("<5I", pe.data, 0x2040, 0, 0, 0, descriptor, col+20)
        name = b".?AVPool@game@@\0"; pe.data[0x3028:0x3028+len(name)] = name
        table = {"symbol": symbol, "entry_symbol": destructor, "initializer_symbol": initializer}
        symbols = {symbol: [(vt, "Pool.ltcg.obj")]}
        functions = {init: [(initializer, "Pool.ltcg.obj")], delete: [(destructor, "Pool.ltcg.obj")]}
        got = linked.source_vtables(pe, symbols, functions, [table], "Pool.ltcg.obj")[0]
        self.assertEqual((got["source_initializer"], got["source_entry"]), (init, delete))
        for entries in [(delete, init, 0), (init, delete, init)]:
            bad = copy.deepcopy(pe); struct.pack_into("<III", bad.data, 0x2010, *entries)
            with self.subTest(entries=entries), self.assertRaises(ValueError):
                linked.source_vtables(bad, symbols, functions, [table], "Pool.ltcg.obj")
        bad_functions = {**functions, init: [(initializer, "Other.obj")]}
        with self.assertRaises(ValueError):
            linked.source_vtables(pe, symbols, bad_functions, [table], "Pool.ltcg.obj")

    def test_two_slot_target_resource_contract_keeps_rtti_and_slot_order(self):
        pe = VTablePe(0x400000); pe.sections[0].VirtualAddress = 0x18000
        struct.pack_into("<IIII", pe.data, 0x200c, 0x402040, 0x418310, 0x4182a0, 0)
        struct.pack_into("<5I", pe.data, 0x2040, 0, 0, 0, 0x403020, 0x402054)
        name = b".?AVOriginalBuffer@@\0"; pe.data[0x3028:0x3028+len(name)] = name
        table = {"symbol": "??_7Pool@game@@6B@", "target": "buffer",
                 "initializer": "?initialize@Pool@game@@UAE_NPBXI@Z=0x00418310",
                 "entry": "??_GPool@game@@UAEPAXI@Z=0x004182A0",
                 "target_type_name": ".?AVOriginalBuffer@@"}
        unit = {"profile": linked.PROFILE, "object": "build/test.dll", "link_data_targets": [],
                "link_vtables": [table], "functions": [{"address": "0x00402820", "symbol_base": "_root"}]}
        linked.validate_contract(unit, {"buffer"})
        bad = copy.deepcopy(unit); bad["link_vtables"][0]["initializer"] = "?initialize@Other@@UAE_NPBXI@Z=0x00418310"
        with self.assertRaises(ValueError): linked.validate_contract(bad, {"buffer"})
        known = {"buffer": (0x402010, struct.pack("<II", 0x418310, 0x4182a0), frozenset({0}), "address")}
        fake = SimpleNamespace(verify_target=lambda: "target", TARGET=Path("unused"), known_data_targets=lambda: known)
        with patch.object(linked, "comparator", return_value=fake), patch.object(linked.pefile, "PE", return_value=pe):
            got = linked.target_vtables(unit)[0]
            self.assertEqual((got["initializer_target"], got["entry_target"]), (0x418310, 0x4182a0))
            for entries in [(0x4182a0, 0x418310, 0), (0x418310, 0x418280, 0), (0x418310, 0x4182a0, 0x418280)]:
                struct.pack_into("<III", pe.data, 0x2010, *entries)
                with self.subTest(entries=entries), self.assertRaises(ValueError): linked.target_vtables(unit)

    def test_complete_cfg_rejects_partial_or_unowned_tails(self):
        for code in [b"\xeb\x7f\xc3", b"\xeb\xff\xc3", b"\xe2\x7f\xc3", b"\xff\xe0\xc3",
                     b"\xc3\x90\xc3", b"\xe8\x01", b"\xcc\xc3"]:
            with self.subTest(code=code.hex()), self.assertRaises(ValueError):
                linked.decode_closed_body(code, self.start)
        # Both return paths must be decoded and owned, not just the first RET.
        self.assertEqual(len(linked.decode_closed_body(b"\x74\x01\xc3\xc3", self.start)), 3)
        self.assertEqual(len(linked.decode_closed_body(b"\xe2\xfe\xc3", self.start)), 2)

    def test_png_callback_pointer_requires_exact_code_and_push_role(self):
        import linked_png_sdk
        pe = VTablePe(); pe.OPTIONAL_HEADER.SizeOfImage = 0x4000
        symbol = '?CBitmapData_png_read@th105@@YAXPAUPngStruct@1@PAEK@Z'
        code = b'\x90' * 32 + b'\xc3'
        pe.data[0x1000:0x1030] = code + b'\xcc' * 15
        functions = {self.start: [(symbol, 'Ctx.ltcg.obj')], self.start + 0x30: [('_next', 'Ctx.ltcg.obj')]}
        symbols = {symbol: [(self.start, 'Ctx.ltcg.obj')]}
        known = {symbol: (0x41a8e0, code[:16], frozenset({0}), 'address')}
        unit = {'link_png_sdk': True, 'link_runtime': 'static', 'link_png_read_callback': True}
        def witness():
            return linked_png_sdk.callback_witness(unit, pe, functions, symbols,
                'Ctx.ltcg.obj', {}, known, lambda a, n: code[:n])
        refs = witness()
        body = b'\x68' + struct.pack('<I', self.start) + b'\xc3'
        result = linked.canonicalize(body, self.start + 0x100, self.target, [], lambda a: None,
                                   self.image, self.game, internal_refs=refs)
        self.assertEqual(result[0], b'\x68' + struct.pack('<I', 0x41a8e0) + b'\xc3')
        with self.assertRaises(ValueError):
            linked.canonicalize(b'\xb8' + struct.pack('<I', self.start) + b'\xc3',
                self.start + 0x100, self.target, [], lambda a: None, self.image, self.game, internal_refs=refs)
        pe.data[0x1005] = 0x40
        with self.assertRaises(ValueError): witness()
        pe.data[0x1005] = 0x90
        symbols[symbol] = [(self.start, 'foreign.obj')]
        with self.assertRaises(ValueError): witness()
        symbols[symbol] = [(self.start, 'Ctx.ltcg.obj')]
        functions[self.start].append(('_alias', 'Ctx.ltcg.obj'))
        with self.assertRaises(ValueError): witness()
        for bad in ({'link_png_read_callback': True}, {'link_png_read_callback': 1}):
            with self.assertRaises(ValueError): linked_png_sdk.validate(bad)

    def test_literal_pointer_push_requires_whole_attested_string(self):
        src, dst = self.start + 0x1000, 0x006D6A08
        code = b"\x68" + struct.pack("<I", src) + b"\xc3"
        ref = {"kind": "literal", "source_address": src, "address": dst,
               "symbol": "text", "size": 8, "literal_size": 8, "read_offset": 0,
               "allow_pointer_push": True}
        def replay(reference, body=code):
            return linked.canonicalize(body, self.start, self.target, [], lambda a: None,
                                       self.image, self.game, internal_refs=[reference])
        self.assertEqual(replay(ref)[0], b"\x68" + struct.pack("<I", dst) + b"\xc3")
        for bad in ({**ref, "read_offset": 1}, {**ref, "size": 7}, {**ref, "allow_pointer_push": False},
                    {k: v for k, v in ref.items() if k != "literal_size"}):
            with self.assertRaises(ValueError): replay(bad)
        with self.assertRaises(ValueError): replay(ref, b"\xb8" + struct.pack("<I", src) + b"\xc3")

    def test_internal_terminal_jump_requires_complete_owned_return_graph(self):
        # DDS4094E0 has a remote failure block after RET, jumping to its epilogue.
        code = b"\x74\x01\xc3\xeb\xfd"
        self.assertEqual(len(linked.decode_closed_body(code, self.start)), 3)
        for bad in (b"\xeb\xfe", b"\xc3\xeb\xfd", b"\x74\x01\xc3\xeb\xfc",
                    b"\x74\x01\xc3\xeb\x7f", b"\x74\x01\xc3\xff\xe0"):
            with self.subTest(code=bad.hex()), self.assertRaises(ValueError):
                linked.decode_closed_body(bad, self.start)

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

    def test_named_import_call_requires_real_name_and_library_owner(self):
        from linked_named_imports import CONTRACTS, validate_contract
        symbol = "_D3DXCreateEffect@36"
        unit = {"link_named_import_targets": [symbol + "=0x006898A2"]}
        validate_contract(unit)
        with self.assertRaises(ValueError): validate_contract(unit, {symbol})
        with self.assertRaises(ValueError):
            validate_contract({"link_named_import_targets": [symbol + "=0x006898A3"]})
        slot, destination = linked.IMAGE_BASE + 0x3000, self.start + 0x800
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(SizeOfImage=0x5000),
                             get_data=lambda rva, size: b"\xff\x25" + struct.pack("<I", slot))
        contract = dict(CONTRACTS[symbol], symbol=symbol, map_owner="d3dx9_33_named:d3dx9_33.dll")
        funcs = {destination: [(symbol, contract["map_owner"])]}
        def resolve(identity, functions=funcs):
            return linked.resolve_linked_call(destination, pe, functions, {slot: identity},
                                              {symbol: contract["target"]}, [contract])
        self.assertEqual(resolve(("d3dx9_33.dll", "D3DXCreateEffect")), (symbol, 0x6898a2))
        for identity in [("d3dx9_33.dll", 1), ("d3dx9_33.dll", "D3DXCreateEffect@36"),
                         ("other.dll", "D3DXCreateEffect"), (None, None)]:
            with self.subTest(identity=identity), self.assertRaises(ValueError): resolve(identity)
        with self.assertRaises(ValueError):
            resolve(("d3dx9_33.dll", "D3DXCreateEffect"), {destination: [(symbol, "game.obj")]})

    def test_named_import_metadata_changes_only_standard_name_policy(self):
        from linked_named_imports import converted_archive
        symbol, dll = "_D3DXCreateEffect@36", "d3dx9_33.dll"
        def member(body):
            header = ("d3dx9_33.dll/".ljust(16) + "0".ljust(12) + "0".ljust(6)
                      + "0".ljust(6) + "0".ljust(8) + str(len(body)).ljust(10) + "`\n")
            return header.encode() + body + (b"\n" if len(body) & 1 else b"")
        def descriptor(names, executable=False):
            head = struct.pack("<HHIIIHH", 0x14c, len(names), 0, 20 + 40 * len(names), 0, 0, 0)
            return head + b"".join(struct.pack("<8sIIIIIIHHI", n, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0x20000000 if executable else 0x40000040) for n in names)
        def archive(name=symbol, policy=8, executable=False):
            strings = name.encode() + b"\0" + dll.encode() + b"\0"
            short = struct.pack("<HHHHIIHH", 0, 0xffff, 0, 0x14c, 0, len(strings), 0, policy) + strings
            return b"!<arch>\n" + b"".join(member(descriptor(names, executable)) for names in [
                [b".debug$S", b".idata$2", b".idata$6"], [b".debug$S", b".idata$3"],
                [b".debug$S", b".idata$5", b".idata$4"]]) + member(short)
        original = archive()
        result = converted_archive(original, symbol, dll)
        self.assertEqual(len(original), len(result))
        self.assertEqual([(a, b) for a, b in zip(original, result) if a != b], [(8, 12)])
        for bad in [archive(name="_Wrong@36"), archive(policy=12), archive(executable=True), original[:-2]]:
            with self.subTest(length=len(bad)), self.assertRaises(ValueError):
                converted_archive(bad, symbol, dll)

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
