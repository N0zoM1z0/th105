from __future__ import annotations

import importlib.util
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_builder():
    spec = importlib.util.spec_from_file_location("inline_profile_builder", ROOT / "scripts/build.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class ProbeInlineProfileTests(unittest.TestCase):
    def run_shell_profile(self, mode: str):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            binary = root / "bin"
            binary.mkdir()
            tools = root / "tools"
            (tools / "bin").mkdir(parents=True)
            (tools / "bin/cl.exe").write_bytes(b"test compiler sentinel")
            source = root / "test.cpp"
            source.write_text("void test() {}\n")
            capture = root / "arguments.json"
            recorder = root / "record.py"
            recorder.write_text(
                "import json,os,sys\n"
                "open(os.environ['TH105_TEST_ARGS'],'w').write(json.dumps(sys.argv[1:]))\n"
            )
            (binary / "wine").write_text(
                "#!/bin/sh\nexec " + shlex.quote(sys.executable) + " "
                + shlex.quote(str(recorder)) + ' "$@"\n'
            )
            (binary / "winepath").write_text('#!/bin/sh\nprintf \'%s\\n\' "$2"\n')
            for path in binary.iterdir():
                path.chmod(0o755)
            environment = dict(os.environ)
            environment.update(
                PATH=str(binary) + os.pathsep + environment.get("PATH", ""),
                TH105_MSVC8_ROOT=str(tools),
                TH105_WINEPREFIX=str(root / "wine-prefix"),
                TH105_TEST_ARGS=str(capture),
                TH105_INLINE_MODE=mode,
                TH105_FP_MODE="default",
                TH105_EXTRA_INCLUDE_DIRS="",
            )
            completed = subprocess.run(
                ["bash", str(ROOT / "scripts/compile-unit.sh"), str(source), str(root / "test.obj")],
                env=environment, capture_output=True, text=True,
            )
            arguments = json.loads(capture.read_text()) if capture.exists() else None
            return completed, arguments

    def test_default_probe_keeps_existing_compiler_flags(self):
        completed, arguments = self.run_shell_profile("default")
        self.assertEqual(completed.returncode, 0, completed.stderr)
        self.assertIn("/O2", arguments)
        self.assertFalse(any(argument.startswith("/Ob") for argument in arguments))

    def test_explicit_inline_policy_overrides_only_after_o2(self):
        completed, arguments = self.run_shell_profile("explicit")
        self.assertEqual(completed.returncode, 0, completed.stderr)
        self.assertEqual(arguments.count("/Ob1"), 1)
        self.assertLess(arguments.index("/O2"), arguments.index("/Ob1"))

    def test_unknown_inline_policy_never_invokes_compiler(self):
        completed, arguments = self.run_shell_profile("unsupported")
        self.assertEqual(completed.returncode, 2)
        self.assertIn("unsupported TH105_INLINE_MODE", completed.stderr)
        self.assertIsNone(arguments)

    def test_builder_resets_ambient_modes_and_records_selected_policy(self):
        builder = load_builder()
        profiles = (
            ("vc8-sp1-probe-o2", "default", "default"),
            ("vc8-sp1-probe-o2-fp-strict", "default", "strict"),
            ("vc8-sp1-probe-o2-ob1", "explicit", "default"),
        )
        for profile, inline_mode, fp_mode in profiles:
            with self.subTest(profile=profile), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                (root / "src").mkdir()
                (root / "src/test.cpp").write_text("void test() {}\n")
                unit = dict(kind="probe", profile=profile, enable_gs=True,
                            source="src/test.cpp", object="build/test.obj")
                observed = {}

                def compile_probe(command, **kwargs):
                    observed.update(kwargs["env"])
                    (root / "build/test.obj").write_bytes(b"compiler-output fixture")
                    return subprocess.CompletedProcess(command, 0, "", "")

                with (
                    mock.patch.object(builder, "ROOT", root),
                    mock.patch.object(builder, "repository_path", side_effect=lambda path, **_: root / path),
                    mock.patch.object(builder, "unit_input_digest", return_value=("a" * 64, [])),
                    mock.patch.object(builder, "compiler_sha256", return_value="b" * 64),
                    mock.patch.object(builder.subprocess, "run", side_effect=compile_probe),
                    mock.patch.dict(os.environ, {"TH105_INLINE_MODE": "explicit", "TH105_FP_MODE": "strict"}),
                ):
                    result = builder.build_unit("test", unit, True, "c" * 64)
                self.assertEqual(observed["TH105_INLINE_MODE"], inline_mode)
                self.assertEqual(observed["TH105_FP_MODE"], fp_mode)
                self.assertEqual(result["inline_mode"], inline_mode)
                self.assertEqual(result["fp_mode"], fp_mode)
                self.assertEqual(result["profile"], profile)

    def test_ob1_profile_is_explicit_and_local_to_the_font_unit(self):
        from workflow_manifest import load_manifest
        units = load_manifest()["units"]
        self.assertEqual(
            [name for name, unit in units.items() if unit["profile"] == "vc8-sp1-probe-o2-ob1"],
            ["gpt-web-text-font-render"],
        )


if __name__ == "__main__":
    unittest.main()
