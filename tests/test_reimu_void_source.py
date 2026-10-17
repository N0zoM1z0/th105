import importlib.util
from pathlib import Path
import unittest

path = Path(__file__).resolve().parents[1] / 'scripts/probe-reimu-action-source-shape.py'
spec = importlib.util.spec_from_file_location('void_source_probe', path)
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)
HEADER = 'class ReimuActionStatePreludeView {\n    bool run_checked_action_dispatch();\n};\n'
SOURCE = '''// One source path for the checked entry and all actions<=798.
// Temporary bool interface.
bool ReimuActionStatePreludeView::run_checked_action_dispatch()
{
    const short selected_action = action_13c;
    if (selected_action > 798)
        return false;
    switch (selected_action) {
    case 1:
        const char *note = "return false;"; // return true;
        return true;
    default:
        update_common_action_state();
        return true;
    }
}
'''


class ReimuVoidSourceTests(unittest.TestCase):
    def test_private_void_declaration_and_default_are_preserved(self):
        source, header, count = probe.void_source(SOURCE, HEADER)
        self.assertEqual(count, 2)
        self.assertIn('void ReimuActionStatePreludeView::run_action_dispatch_root()', source)
        self.assertNotIn('if (selected_action > 798)', source)
        self.assertIn('update_common_action_state();\n        return;', source)
        self.assertIn('bool run_checked_action_dispatch();', header)
        self.assertIn('void run_action_dispatch_root();', header)

    def test_strings_and_comments_are_not_return_statements(self):
        source, _, _ = probe.void_source(SOURCE, HEADER)
        self.assertIn('"return false;"; // return true;', source)

    def test_another_pending_return_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.void_source(SOURCE.replace('        return true;\n    default:', '        return false;\n    default:'), HEADER)

    def test_changed_upper_guard_is_rejected(self):
        with self.assertRaises(ValueError):
            probe.void_source(SOURCE.replace('selected_action > 798', 'selected_action > 799'), HEADER)


if __name__ == '__main__':
    unittest.main()
