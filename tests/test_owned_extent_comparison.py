"""A main-span match must not hide remote code or alignment differences."""

from __future__ import annotations

import contextlib
import csv
import importlib.util
import io
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_script(name):
    spec = importlib.util.spec_from_file_location(
        name.replace("-", "_"), ROOT / "scripts" / name
    )
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class OwnedExtentComparisonTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.compare = load_script("compare-function.py")
        import function_byte_ownership

        cls.ownership = function_byte_ownership

    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        self.address = 0x496540
        self.code = bytearray(b"\x90" * 16)
        self.code[8] = 0xE8
        self.code[9:13] = bytes(4)
        self.code[15] = 0xC3
        self.expected = bytearray(self.code)
        struct.pack_into("<i", self.expected, 9, 0x405000 - (self.address + 13))
        self.object = self.directory / "root.obj"
        # A real minimal i386 COFF fixture. Its sole REL32 is in the remote
        # chunk, beyond the four-byte provisional main comparison window.
        raw_pointer = 60
        reloc_pointer = raw_pointer + len(self.code)
        symbols = reloc_pointer + 10
        header = struct.pack("<HHIIIHH", 0x14C, 1, 0, symbols, 2, 0, 0)
        section = struct.pack(
            "<8sIIIIIIHHI",
            b".text",
            0,
            0,
            len(self.code),
            raw_pointer,
            reloc_pointer,
            0,
            1,
            0,
            0x60000020,
        )
        relocation = struct.pack("<IIH", 9, 1, 0x14)
        root = struct.pack("<8sIhHBB", b"root", 0, 1, 0x20, 2, 0)
        callee = struct.pack("<8sIhHBB", b"callee", 0, 0, 0x20, 2, 0)
        self.object.write_bytes(
            header
            + section
            + self.code
            + relocation
            + root
            + callee
            + struct.pack("<I", 4)
        )
        self.functions = self.directory / "functions.csv"
        with self.functions.open("w", newline="") as stream:
            writer = csv.DictWriter(
                stream,
                fieldnames=[
                    "address",
                    "size",
                    "span_end",
                    "proposed_name",
                    "current_name",
                ],
            )
            writer.writeheader()
            writer.writerow(
                dict(
                    address="0x00496540",
                    size=4,
                    span_end="0x00496543",
                    proposed_name="root",
                    current_name="root",
                )
            )
        self.known = self.directory / "known.csv"
        self.known.write_text("address,name\n")
        self.extent = {
            self.address: dict(
                extent_end=self.address + 15, owned_bytes=12, remote_bytes=8
            )
        }

    def run_comparison(self, source=None, *, owned=True, ownership=None):
        if source is not None:
            data = bytearray(self.object.read_bytes())
            data[60:76] = source
            self.object.write_bytes(data)
        arguments = ["compare-function.py", "--json", "--symbol-base", "root"]
        if owned:
            arguments.append("--owned-extent")
        arguments.extend(["0x00496540", str(self.object)])
        output = io.StringIO()
        with (
            mock.patch.object(sys, "argv", arguments),
            mock.patch.object(self.compare, "FUNCTIONS", self.functions),
            mock.patch.object(self.compare, "KNOWN_SYMBOLS", self.known),
            mock.patch.object(self.compare, "verify_target", return_value="target"),
            mock.patch.object(
                self.compare, "known_targets", return_value={"callee": 0x405000}
            ),
            mock.patch.object(self.compare, "known_data_targets", return_value={}),
            mock.patch.object(
                self.compare,
                "target_bytes",
                side_effect=lambda address, size: bytes(
                    self.expected[
                        address - self.address : address - self.address + size
                    ]
                ),
            ),
            mock.patch.object(
                self.ownership,
                "load",
                return_value=self.extent if ownership is None else ownership,
            ) as loader,
            contextlib.redirect_stdout(output),
        ):
            result = self.compare.main()
        if owned:
            self.assertTrue(loader.call_args.kwargs["require_bytes"])
        else:
            loader.assert_not_called()
        return result, json.loads(output.getvalue())

    def test_replays_remote_rel32_and_compares_full_extent(self):
        result, report = self.run_comparison()
        self.assertEqual(result, 0)
        self.assertEqual(report["result"], "exact")
        self.assertEqual(report["target_size"], 16)
        self.assertEqual(report["comparison"]["owned_bytes"], 12)
        self.assertEqual(report["comparison"]["non_owned_bytes_compared"], 4)
        self.assertEqual(report["comparison"]["boundary"], "owned_extent")

    def test_equal_main_cannot_hide_a_remote_mismatch(self):
        source = bytearray(self.code)
        source[14] = 0xCC
        result, report = self.run_comparison(source, owned=False)
        self.assertEqual(result, 0)
        result, report = self.run_comparison(owned=True)
        self.assertEqual(result, 1)
        self.assertEqual(report["first_mismatch"]["offset"], 14)

    def test_alignment_is_compared_instead_of_masked(self):
        source = bytearray(self.code)
        source[6] = 0xCC
        result, report = self.run_comparison(source)
        self.assertEqual(result, 1)
        self.assertEqual(report["first_mismatch"]["offset"], 6)

    def test_absent_ownership_does_not_fall_back_to_main(self):
        result, report = self.run_comparison(ownership={})
        self.assertEqual(result, 1)
        self.assertEqual(report["result"], "error")
        self.assertIn("requires reviewed", report["failure"]["message"])

    def test_boundary_options_are_mutually_exclusive(self):
        with (
            mock.patch.object(
                sys,
                "argv",
                [
                    "compare-function.py",
                    "--owned-extent",
                    "--contiguous-span",
                    "0x00496540",
                    "unused.obj",
                ],
            ),
            contextlib.redirect_stderr(io.StringIO()),
        ):
            with self.assertRaises(SystemExit) as raised:
                self.compare.main()
        self.assertEqual(raised.exception.code, 2)


class ManifestOwnedExtentTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.manifest = load_script("workflow_manifest.py")

    def manifest_file(self, directory, options, address="0x00496540"):
        path = Path(directory) / "units.toml"
        path.write_text(
            'schema_version = 1\ntarget_sha256 = "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e"\n'
            '[units.probe]\nkind = "probe"\nprofile = "vc8-sp1-probe-o2"\nenable_gs = false\n'
            'source = "src/characters/ReimuObjectActionStateStaging.cpp"\nobject = "build/test-owned-extent.obj"\n'
            '[[units.probe.functions]]\naddress = "' + address + '"\n' + options + "\n"
        )
        return path

    def test_owned_provenance_includes_boundary_ledger_and_validator(self):
        unit = dict(
            source="src/characters/ReimuObjectActionStateStaging.cpp",
            kind="probe",
            profile="vc8-sp1-probe-o2",
            enable_gs=False,
            functions=[dict(owned_extent=True)],
        )
        with mock.patch.object(
            self.manifest, "compiler_sha256", return_value="00" * 32
        ):
            _, paths = self.manifest.unit_input_digest("probe", unit)
            unit["functions"] = []
            _, ordinary = self.manifest.unit_input_digest("probe", unit)
        for path in (
            "config/functions.csv",
            "config/function-byte-ownership.toml",
            "scripts/function_byte_ownership.py",
        ):
            self.assertIn(path, paths)
            self.assertNotIn(path, ordinary)

    def test_owned_extent_requires_boolean_flag(self):
        with tempfile.TemporaryDirectory() as directory:
            path = self.manifest_file(directory, 'owned_extent = "yes"')
            with mock.patch.object(self.manifest, "MANIFEST", path):
                with self.assertRaisesRegex(ValueError, "owned_extent must be boolean"):
                    self.manifest.load_manifest()

    def test_owned_extent_rejects_an_unreviewed_function(self):
        with tempfile.TemporaryDirectory() as directory:
            path = self.manifest_file(directory, "owned_extent = true", "0x004351C0")
            with mock.patch.object(self.manifest, "MANIFEST", path):
                with self.assertRaisesRegex(
                    ValueError, "needs one reviewed owned extent"
                ):
                    self.manifest.load_manifest()

    def test_owned_extent_rejects_two_boundary_modes(self):
        with tempfile.TemporaryDirectory() as directory:
            path = self.manifest_file(
                directory, "owned_extent = true\ncontiguous_span = true"
            )
            with mock.patch.object(self.manifest, "MANIFEST", path):
                with self.assertRaisesRegex(
                    ValueError, "needs one reviewed owned extent"
                ):
                    self.manifest.load_manifest()


if __name__ == "__main__":
    unittest.main()
