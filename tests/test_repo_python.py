"""Reject interpreter/package drift before running a repository command."""
from __future__ import annotations

import importlib.util
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("repo_python_env", ROOT / "scripts/repo_python_env.py")
environment = importlib.util.module_from_spec(spec)
spec.loader.exec_module(environment)


class PythonEnvironmentTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        (self.root / "scripts").mkdir()
        (self.root / ".python-version").write_text("3.11.14\n")
        self.requirements = self.root / "scripts/requirements-ci.txt"
        self.requirements.write_text((ROOT / "scripts/requirements-ci.txt").read_text())
        self.pins = environment.load_pins(self.requirements)
        self.modules = {
            name: SimpleNamespace(__version__=version)
            for name, version in self.pins.items()
        }
        self.modules["capstone"].cs_version = lambda: (4, 0, 1024)
        self.modules["unicorn"].uc_version = lambda: (1, 0, 256)
        self.modules["pkg_resources"] = SimpleNamespace()
        for patch in (
            mock.patch.object(environment.platform, "python_version", return_value="3.11.14"),
            mock.patch.object(environment.platform, "python_implementation", return_value="CPython"),
            mock.patch.object(environment.metadata, "version", side_effect=self.pins.__getitem__),
            mock.patch.object(environment.importlib, "import_module", side_effect=self.modules.__getitem__),
        ):
            patch.start()
            self.addCleanup(patch.stop)

    def test_locked_interpreter_packages_and_native_apis_are_accepted(self):
        environment.check_environment(self.root)

    def test_wrong_python_stops_before_dependency_loading(self):
        with mock.patch.object(environment.platform, "python_version", return_value="3.13.5"):
            with self.assertRaisesRegex(ValueError, "need CPython 3.11.14"):
                environment.check_environment(self.root)
        environment.metadata.version.assert_not_called()

    def test_dependency_version_drift_is_rejected(self):
        self.pins["unicorn"] = "2.0.0"
        with self.assertRaisesRegex(ValueError, "need unicorn==1.0.2"):
            environment.check_environment(self.root)

    def test_missing_dependency_is_rejected(self):
        environment.metadata.version.side_effect = environment.metadata.PackageNotFoundError("unicorn")
        with self.assertRaisesRegex(ValueError, "missing locked dependency"):
            environment.check_environment(self.root)

    def test_imported_decoder_cannot_disagree_with_distribution_metadata(self):
        self.modules["capstone"].__version__ = "5.0.6"
        with self.assertRaisesRegex(ValueError, "imported capstone"):
            environment.check_environment(self.root)

    def test_native_library_cannot_disagree_with_wrapper(self):
        self.modules["capstone"].cs_version = lambda: (5, 0, 1280)
        with self.assertRaisesRegex(ValueError, "native library API"):
            environment.check_environment(self.root)

    def test_unpinned_or_duplicate_requirements_are_rejected(self):
        for requirements in ("capstone>=4\n", "capstone==4.0.2\ncapstone==5.0.6\n"):
            with self.subTest(requirements=requirements):
                self.requirements.write_text(requirements)
                with self.assertRaisesRegex(ValueError, "unique exact pins"):
                    environment.check_environment(self.root)


class PythonLauncherTests(unittest.TestCase):
    def launcher(self, root, checker):
        scripts = root / "scripts"
        scripts.mkdir()
        shutil.copy2(ROOT / "scripts/repo-python", scripts / "repo-python")
        (scripts / "repo_python_env.py").write_text(checker)
        return scripts / "repo-python"

    def test_arguments_cwd_and_sanitized_environment_reach_the_selected_python(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            launcher = self.launcher(root, "import os\nassert 'PYTHONPATH' not in os.environ\n")
            program = "import json,os,sys; print(json.dumps([sys.argv[1:],os.getcwd(),os.environ.get('PYTHONPATH'),os.environ.get('PYTHONHOME'),os.environ.get('PYTHONNOUSERSITE')]))"
            result = subprocess.run(
                [str(launcher), "-c", program, "with spaces", "$(literal)", "--json"],
                cwd=root, capture_output=True, text=True,
                env={**os.environ, "TH105_PYTHON": sys.executable,
                     "PYTHONPATH": "/unselected/packages", "PYTHONHOME": "/invalid/home"},
            )
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertEqual(json.loads(result.stdout), [
                ["with spaces", "$(literal)", "--json"], str(root), None, None, "1"])

    def test_failed_environment_check_prevents_command_execution(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            launcher = self.launcher(root, "raise SystemExit(19)\n")
            result = subprocess.run(
                [str(launcher), "-c", "from pathlib import Path; Path('executed').touch()"],
                cwd=root, capture_output=True, text=True,
                env={**os.environ, "TH105_PYTHON": sys.executable},
            )
            self.assertEqual(result.returncode, 19)
            self.assertFalse((root / "executed").exists())

    def test_missing_selected_interpreter_does_not_fall_back_to_ambient_python(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            launcher = self.launcher(root, "raise AssertionError('must not run')\n")
            result = subprocess.run(
                [str(launcher), "-c", "raise AssertionError('must not run')"],
                capture_output=True, text=True,
                env={**os.environ, "TH105_PYTHON": str(root / "missing")},
            )
            self.assertEqual(result.returncode, 1)
            self.assertIn("repository Python is missing", result.stderr)


if __name__ == "__main__":
    unittest.main()
