"""Synthetic error edges and exception metadata; no original game bytes."""
from contextlib import ExitStack
import copy
import hashlib
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_pe as core
import linked_noreturn as error
from test_linked_pe import VTablePe


class LinkedNoreturnTests(unittest.TestCase):
    def test_only_the_qualified_middle_e9_is_a_terminal_edge(self):
        start, destination = core.IMAGE_BASE + 0x1000, core.IMAGE_BASE + 0x1100
        code = b"\x74\x05\xe9" + struct.pack("<i", destination - start - 7) + b"\xc3"
        with self.assertRaises(ValueError): core.decode_closed_body(code, start)
        self.assertEqual(len(core.decode_closed_body(code, start,
            external_exits={start + 2: destination})), 3)
        for exits in [{start + 3: destination}, {start + 2: destination + 1},
                      {start + 7: destination}, {start + 2: start},
                      {start + 2: destination, start + 1: destination}]:
            with self.subTest(exits=exits), self.assertRaises(ValueError):
                core.decode_closed_body(code, start, external_exits=exits)
        canonical, calls, _ = core.canonicalize(code, start, 0x401000, [],
            lambda _: ("_error", 0x402000), (core.IMAGE_BASE, core.IMAGE_BASE + 0x4000),
            (0x400000, 0x706000), external_exits={start + 2: destination})
        self.assertEqual(canonical, b"\x74\x05\xe9" + struct.pack("<i", 0x402000 - 0x401007) + b"\xc3")
        self.assertEqual(calls, [{"offset": 3, "symbol": "_error", "target": 0x402000}])
        with self.assertRaises(ValueError):
            core.decode_closed_body(b"\xeb\x10\xc3", start, external_exits={start: start + 18})

    def fixture(self):
        pe = VTablePe(); pe.OPTIONAL_HEADER.SizeOfImage = 0x4000
        start, helper, thunk = core.IMAGE_BASE + 0x1000, core.IMAGE_BASE + 0x1100, core.IMAGE_BASE + 0x1200
        symbol = "?_Xran@?$vector@UHandle@game@@V?$allocator@UHandle@game@@@std@@@std@@KAXXZ"
        root = b"\x74\x05\xe9" + struct.pack("<i", helper - start - 7) + b"\xc3"
        message, info, cell = core.IMAGE_BASE + 0x2100, core.IMAGE_BASE + 0x2200, core.IMAGE_BASE + 0x3000
        body = b"\x68" + struct.pack("<I", message) + b"\x68" + struct.pack("<I", info) + b"\x51\xe8"
        body += struct.pack("<i", thunk - (helper + len(body) + 4))
        pe.data[0x1000:0x1100] = root + b"\xcc" * (0x100 - len(root))
        pe.data[0x1100:0x1100 + len(body)] = body
        pe.data[0x1200:0x1206] = b"\xff\x25" + struct.pack("<I", cell)
        pe.data[0x2100:0x2100 + len(error.MESSAGE)] = error.MESSAGE
        pe.DIRECTORY_ENTRY_IMPORT = [SimpleNamespace(dll=b"MSVCR80.dll", imports=[
            SimpleNamespace(address=cell, name=b"_CxxThrowException")])]
        data = {}
        def put(address, value):
            data.update({address + index: byte for index, byte in enumerate(value)})
        def target_read(address, size): return bytes(data.get(address + index, 0) for index in range(size))
        def source_put(address, value): pe.data[address - core.IMAGE_BASE:address - core.IMAGE_BASE + len(value)] = value
        def metadata(write, at, storage):
            write(at, struct.pack("<4I", 0, 0, 0, storage))
            write(storage, struct.pack("<4I", 3, storage + 0x40, storage + 0x60, storage + 0x80))
            for index, (name, size) in enumerate([(b".?AVout_of_range@std@@", 40),
                    (b".?AVlogic_error@std@@", 40), (b".?AVexception@std@@", 12)]):
                td = storage + 0x100 + index * 0x80
                write(storage + 0x40 + index * 0x20, struct.pack("<7I", 0, td, 0, 0xFFFFFFFF, 0, size, 1))
                write(td, bytes(8) + name + b"\0")
        metadata(source_put, info, core.IMAGE_BASE + 0x2300)
        metadata(put, 0x6E3BA4, 0x6E4000)
        target_helper = b"\xe8" + struct.pack("<i", error.THROW - error.HELPER - 5)
        put(error.HELPER, target_helper); put(error.THROW, b"\xc3")
        put(error.RECORD, struct.pack("<8I", 0, 1, 0, 0, 0, 0, 0, 0)); put(0x6D694C, error.MESSAGE)
        target = b"\x74\x05\xe9" + struct.pack("<i", error.HELPER - 0x401007) + b"\xc3"
        function = dict(address="0x00401000", symbol_base="_root", rel32_targets=[symbol + "=0x0040C350"],
            error_tails=[dict(kind=error.KIND, symbol=symbol, site="0x00401002")])
        functions = {start: [("_root", "Ctx.ltcg.obj")], helper: [(symbol, "i Ctx.ltcg.obj")],
                     helper + len(body): [("_next", "Ctx.ltcg.obj")],
                     thunk: [("__CxxThrowException@8", "msvcrt:MSVCR80.dll")]}
        game = SimpleNamespace(DIRECTORY_ENTRY_IMPORT=[SimpleNamespace(dll=b"KERNEL32.dll", imports=[
            SimpleNamespace(address=0x6C015C, name=b"RaiseException")])])
        return dict(pe=pe, game=game, functions=functions, function=function, exports={"_root": start},
                    cil_owner="Ctx.ltcg.obj", start=start, raw=root, target=target, read_target=target_read,
                    helper=helper, info=info, body=body, put=put,
                    anchors=dict(HELPER_SIZE=len(target_helper), HELPER_SHA=hashlib.sha256(target_helper).hexdigest(),
                        THROW_SIZE=1, THROW_SHA=hashlib.sha256(b"\xc3").hexdigest(),
                        RECORD_SHA=hashlib.sha256(target_read(error.RECORD, 32)).hexdigest()))

    def run_witness(self, f):
        with ExitStack() as stack:
            for key, value in f["anchors"].items(): stack.enter_context(patch.object(error, key, value))
            return error.witness(core, **{key: f[key] for key in (
                "function", "pe", "game", "functions", "exports", "cil_owner", "start", "raw", "target", "read_target")})

    def test_native_throw_witness_qualifies_both_complete_caller_cfgs(self):
        f = self.fixture(); source, target, reports = self.run_witness(f)
        self.assertEqual(source, {f["start"] + 2: f["helper"]})
        self.assertEqual(target, {0x401002: error.HELPER})
        self.assertEqual(len(reports), 1)
        self.assertEqual(reports[0]["source_throw_info"], hex(f["info"]))

    def test_contract_rejects_unmapped_foreign_and_combined_entry_roles(self):
        f = self.fixture()["function"]; error.validate_contract(f)
        changes = [lambda x: x.update(error_tails={}),
            lambda x: x["error_tails"].append(copy.deepcopy(x["error_tails"][0])),
            lambda x: x["error_tails"][0].update(kind="arbitrary-noreturn"),
            lambda x: x["error_tails"][0].update(symbol="_fake"),
            lambda x: x["error_tails"][0].update(site="inside"),
            lambda x: x.update(rel32_targets=[]),
            lambda x: x.update(private_from={}), lambda x: x.update(eh_cleanup={})]
        for change in changes:
            bad = copy.deepcopy(f); change(bad)
            with self.subTest(change=change), self.assertRaises(ValueError): error.validate_contract(bad)

    def test_source_import_ownership_message_and_types_fail_closed(self):
        changes = [lambda f: f["exports"].update(helper=f["helper"]),
            lambda f: f["functions"][f["helper"]].append(("_alias", "Ctx.ltcg.obj")),
            lambda f: f["functions"].update({f["helper"]: [(f["function"]["error_tails"][0]["symbol"], "Other.obj")]}),
            lambda f: setattr(f["pe"].DIRECTORY_ENTRY_IMPORT[0], "dll", b"fake.dll"),
            lambda f: setattr(f["pe"].DIRECTORY_ENTRY_IMPORT[0].imports[0], "name", b"_FakeThrow"),
            lambda f: f["pe"].data.__setitem__(0x2100, ord("X")),
            lambda f: f["pe"].data.__setitem__(0x2408, ord("X")),
            lambda f: f["pe"].data.__setitem__(0x1100, 0xC3),
            lambda f: f["pe"].data.__setitem__(0x110A, 0x59),
            lambda f: setattr(f["pe"].sections[1], "Characteristics", 0xC0000040),
            lambda f: f.update(target=f["target"][:-1] + b"\x90")]
        for change in changes:
            f = self.fixture(); change(f)
            with self.subTest(change=change), self.assertRaises(ValueError): self.run_witness(f)

    def test_target_anchors_and_error_site_cannot_be_substituted(self):
        for change in [lambda f: f["put"](error.HELPER, b"\xc3"),
                lambda f: f["put"](error.THROW, b"\x90"),
                lambda f: f["put"](error.RECORD + 4, bytes(4)),
                lambda f: setattr(f["game"].DIRECTORY_ENTRY_IMPORT[0].imports[0], "name", b"FakeRaise"),
                lambda f: f["function"]["error_tails"][0].update(site="0x00401003")]:
            f = self.fixture(); change(f)
            with self.subTest(change=change), self.assertRaises(ValueError): self.run_witness(f)

    def test_error_helper_cannot_return_or_escape_before_throw(self):
        start, destination = 0x1000, 0x2000
        call = lambda offset: b"\xe8" + struct.pack("<i", destination - start - offset - 5)
        self.assertEqual(len(error.straight_throw(b"\x90" + call(1), start, destination)), 2)
        for code in [b"\xc3" + call(1), b"\xeb\x00" + call(2), b"\xe2\xfe" + call(2),
                     b"\xff\xd0" + call(2), b"\xcc" + call(1), b"\x90\xc3", b"\x68"]:
            with self.subTest(code=code), self.assertRaises(ValueError): error.straight_throw(code, start, destination)


if __name__ == "__main__": unittest.main()
