import importlib.util
from pathlib import Path
import unittest

path = Path(__file__).resolve().parents[1] / "scripts/audit-reimu-aimed-mode-loops.py"
spec = importlib.util.spec_from_file_location("aimed_facts", path)
facts = importlib.util.module_from_spec(spec)
spec.loader.exec_module(facts)


class AimedLoopFactsTests(unittest.TestCase):
    def test_signed_zero_survives_literal_and_store_model(self):
        self.assertNotEqual(facts.const(0.0), facts.const(-0.0))
        self.assertNotEqual(facts.rounded(facts.const(0.0), 4),
                            facts.rounded(facts.const(-0.0), 4))

    def test_only_bounded_counter_products_drop_store_rounding(self):
        step = facts.expr("mul", facts.I, facts.const(120))
        self.assertEqual(facts.rounded(step, 8), step)
        nonlinear = facts.expr("mul", step, step)
        self.assertNotEqual(facts.rounded(nonlinear, 4), nonlinear)

    def test_addition_grouping_is_preserved(self):
        first = facts.expr("add", facts.expr("add", facts.A, facts.const(90)), facts.I)
        second = facts.expr("add", facts.A, facts.expr("add", facts.const(90), facts.I))
        self.assertNotEqual(first, second)


if __name__ == "__main__":
    unittest.main()
