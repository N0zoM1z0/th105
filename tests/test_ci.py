"""Exercise basic CI in real Git repositories without site packages."""
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class BasicCiTests(unittest.TestCase):
    def setUp(self):
        folder = tempfile.TemporaryDirectory()
        self.addCleanup(folder.cleanup)
        self.root = Path(folder.name)
        (self.root / "scripts").mkdir()
        shutil.copyfile(ROOT / "scripts/ci.py", self.root / "scripts/ci.py")
        (self.root / "scripts/validate-tracking.py").write_text(
            "import sys\nassert sys.argv[1:] == ['--portable']\n"
        )
        self.git("init", "--quiet")
        self.commit()

    def git(self, *args):
        return subprocess.run(
            ["git", *args], cwd=self.root, capture_output=True, text=True, check=True,
        )

    def commit(self):
        self.git("add", "--all")
        self.git("-c", "user.name=CI Test", "-c", "user.email=ci@example.invalid",
                 "commit", "--quiet", "-m", "fixture")

    def check(self, *args, ci=False):
        return subprocess.run(
            [sys.executable, "-S", "scripts/ci.py", *args], cwd=self.root,
            env={**os.environ, "CI": "true" if ci else ""},
            capture_output=True, text=True,
        )

    def test_valid_files_need_no_analysis_environment(self):
        for name, content in {"sample.py": "value = 1\n", "data.json": "{}\n",
                              "data.toml": "value = 1\n", "sample.sh": "echo ok\n"}.items():
            (self.root / name).write_text(content)
        result = self.check("--all")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertFalse((self.root / "build").exists())

    def test_untracked_syntax_errors_and_extensionless_launcher_fail(self):
        (self.root / "good.sh").write_text("echo ok\n")
        for name, content in {"bad.py": "def broken(\n", "bad.json": "{",
                              "bad.toml": "value = [", "bad.sh": "if true; then\n",
                              "scripts/repo-python": "if true; then\n"}.items():
            with self.subTest(name=name):
                path = self.root / name
                path.write_text(content)
                self.assertNotEqual(self.check().returncode, 0)
                path.unlink()

    def test_staged_whitespace_fails_even_if_worktree_copy_is_fixed(self):
        path = self.root / "note.md"
        path.write_text("trailing space \n")
        self.git("add", "note.md")
        path.write_text("fixed\n")
        result = self.check()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("note.md", result.stdout)

    def test_all_checks_an_earlier_commit_not_only_head_changes(self):
        (self.root / "earlier.py").write_text("def broken(\n")
        self.commit()
        (self.root / "note.md").write_text("later commit\n")
        self.commit()
        self.assertNotEqual(self.check().returncode, 0)
        self.assertNotEqual(self.check("--all", ci=True).returncode, 0)

    def test_private_artifacts_fail_including_forced_ignored_files(self):
        for name, data in {"build/probe.obj": b"object", "resources/th105.exe": b"MZ",
                           ".tools/tool": b"tool", ".env": b"secret", "renamed": b"\x7fELF"}.items():
            with self.subTest(name=name):
                path = self.root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(data)
                self.git("add", "--force", name)
                self.assertNotEqual(self.check().returncode, 0)
                self.git("rm", "--force", name)

    def test_tracking_failure_is_propagated(self):
        (self.root / "scripts/validate-tracking.py").write_text("raise SystemExit(1)\n")
        self.assertNotEqual(self.check().returncode, 0)

    def test_base_checks_whitespace_in_earlier_pr_commit(self):
        base = self.git("rev-parse", "HEAD").stdout.strip()
        (self.root / "earlier.md").write_text("trailing space \n")
        self.commit()
        (self.root / "later.md").write_text("clean\n")
        self.commit()
        self.assertNotEqual(self.check("--base", base).returncode, 0)

    def test_invalid_base_fails(self):
        self.assertNotEqual(self.check("--base", "missing-commit").returncode, 0)

    def test_base_checks_pr_commits_behind_checkout_merge(self):
        base = self.git("rev-parse", "HEAD").stdout.strip()
        self.git("checkout", "-q", "-b", "feature")
        (self.root / "feature.md").write_text("trailing space \n")
        self.commit()
        self.git("checkout", "-q", "--detach", base)
        (self.root / "base.md").write_text("clean\n")
        self.commit()
        self.git("-c", "user.name=CI Test", "-c", "user.email=ci@example.invalid",
                 "merge", "--quiet", "--no-ff", "feature", "-m", "PR merge")
        self.assertNotEqual(self.check("--base", base).returncode, 0)

    def test_ci_rejects_whitespace_already_in_the_commit(self):
        (self.root / "note.md").write_text("trailing space \n")
        self.commit()
        self.assertEqual(self.check().returncode, 0)
        self.assertNotEqual(self.check("--all", ci=True).returncode, 0)

    def test_shallow_checkout_does_not_recheck_old_whitespace(self):
        (self.root / "old.md").write_text("old trailing space \n")
        self.commit()
        (self.root / "new.md").write_text("clean new commit\n")
        self.commit()
        with tempfile.TemporaryDirectory() as folder:
            self.git("clone", "--quiet", "--depth", "2", self.root.as_uri(), folder)
            result = subprocess.run(
                [sys.executable, "-S", "scripts/ci.py", "--all"], cwd=folder,
                env={**os.environ, "CI": "true"}, capture_output=True, text=True,
            )
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_deleted_files_and_symlinks_are_skipped(self):
        path = self.root / "removed.py"
        path.write_text("def broken(\n")
        self.commit()
        path.unlink()
        (self.root / "link.py").symlink_to("missing-file")
        result = self.check()
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == "__main__":
    unittest.main()
