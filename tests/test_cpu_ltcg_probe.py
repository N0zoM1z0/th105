"""A source-type control must refuse an unreviewed arithmetic temporary."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("cpu_ltcg_probe_test", ROOT / "scripts/probe-aya-cpu-ltcg.py")
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)


class CpuLtcgSourceControlTests(unittest.TestCase):
    def test_reviewed_source_with_logical_and_is_accepted(self):
        source = (ROOT / "src/characters/AyaCpuActionPolicy.cpp").read_text()
        self.assertIn("&& v95", source)
        prepared = probe.prepare_source(source, "all")
        self.assertIn("float v95;", prepared)

    def test_arithmetic_or_additional_assignment_blocks_narrowing(self):
        source = (ROOT / "src/characters/AyaCpuActionPolicy.cpp").read_text()
        for changed in (source.replace("v99 = v117;", "v99 = v117 + 0.1;"),
                        source.replace("v99 = v117;", "v99 = v117;\nv99 = v117 + 0.1;"),
                        source.replace("v99 = v117;", "v99 = v117;\nv99 += 0.1;"),
                        source.replace("v99 = v117;", "v99 = v117;\nconsume(&v99);")):
            with self.subTest(additional="v99 = v117;\n" in changed):
                with self.assertRaisesRegex(ValueError, "unreviewed value provenance for v99"):
                    probe.prepare_source(changed, "all")

    def test_preserve_mode_does_not_narrow_an_arithmetic_value(self):
        source = (ROOT / "src/characters/AyaCpuActionPolicy.cpp").read_text()
        changed = source.replace("v99 = v117;", "v99 = v117 + 0.1;")
        prepared = probe.prepare_source(changed, "preserve")
        self.assertIn("double v99;", prepared)
        self.assertIn("v99 = v117 + 0.1;", prepared)


if __name__ == "__main__":
    unittest.main()
