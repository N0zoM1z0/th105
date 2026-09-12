"""Source-contract guards; these assertions do not establish an exact match."""
from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]


class CpuPredicateTests(unittest.TestCase):
    def test_full_random_result_comparisons_are_unsigned(self):
        source = (ROOT / "src/characters/CpuActionPolicies.cpp").read_text()
        thresholds = re.findall(
            r"selector_random_roll\([^()]*\)\s*(?:<=|>=|<|>)\s*(\w+)", source
        )
        self.assertEqual(len(thresholds), 51)
        self.assertTrue(all(value.endswith("u") for value in thresholds))
        self.assertEqual(source.count("static_cast<unsigned>(selector_random_roll("), 3)

    def test_stored_random_and_resource_words_have_signed_comparisons(self):
        source = (ROOT / "src/characters/CpuActionPolicies.cpp").read_text()
        comparisons = re.findall(
            r"\*\(__int16 \*\)CPU_FIELD\(1902\)\s*(?:<=|>)\s*"
            r"\*\(__int16 \*\)CPU_FIELD\(1154\)", source
        )
        self.assertEqual(len(comparisons), 3)
        self.assertNotRegex(
            source, r"\*\(_WORD \*\)CPU_FIELD\(1902\).*CPU_FIELD\(1154\)"
        )


if __name__ == "__main__":
    unittest.main()
