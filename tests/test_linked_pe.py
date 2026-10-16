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


class LinkedPeTests(unittest.TestCase):
    start = linked.IMAGE_BASE + 0x1000
    target = 0x401000
    game = (0x400000, 0x706000)
    image = (linked.IMAGE_BASE, linked.IMAGE_BASE + 0x5000)

    def canonical(self, code, bindings=None, resolve=None):
        return linked.canonicalize(code, self.start, self.target, bindings or [],
            resolve or (lambda address: (_ for _ in ()).throw(ValueError("unknown call"))), self.image, self.game)

    def binding(self, data="00000000"):
        return {"key": "app", "symbol": "_app", "address": 0x702820,
                "addends": [0, 0x90], "data_hex": data}

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
                             ("symbol_base", None), ("contiguous_span", True),
                             ("dir32_targets", ["literal=untyped"] )]:
            bad = copy.deepcopy(unit)
            bad["functions"][0][field] = value
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                linked.validate_contract(bad, {"app"})

    def test_modified_build_artifacts_are_rejected_before_decoding(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            image, source = root / "probe.dll", root / "source.cpp"
            paths = [image, source, image.with_suffix(".map"), image.with_suffix(".ltcg.obj"), image.with_suffix(".bindings.obj")]
            unit = {"source": str(source), "object": str(image)}
            for changed in paths:
                for path in paths:
                    path.write_bytes(b"original")
                metadata = {"schema": "th105-linked-pe-v1", "unit": "test", "profile": linked.PROFILE,
                    "target_sha256": "target", "input_digest": "digest", "tools": {}, "bindings": [],
                    "parsers": linked.parser_versions(), "source_sha256": linked.sha(source),
                    "image_sha256": linked.sha(image), "map_sha256": linked.sha(image.with_suffix(".map")),
                    "ltcg_object_sha256": linked.sha(image.with_suffix(".ltcg.obj")),
                    "bindings_object_sha256": linked.sha(image.with_suffix(".bindings.obj"))}
                image.with_suffix(".link.json").write_text(json.dumps(metadata))
                changed.write_bytes(b"changed")
                fake = SimpleNamespace(verify_target=lambda: "target")
                with self.subTest(changed=changed.name), patch.object(linked, "comparator", return_value=fake), \
                     patch.object(linked, "pinned_tools", return_value=(root, {})), \
                     patch.object(linked, "target_bindings", return_value=[]), \
                     patch("workflow_manifest.unit_input_digest", return_value=("digest", [])), \
                     patch("workflow_manifest.repository_path", side_effect=lambda path, **kwargs: Path(path)):
                    with self.assertRaisesRegex(ValueError, "stale or modified"):
                        linked.compare_linked("test", unit, set(), image)


if __name__ == "__main__":
    unittest.main()
