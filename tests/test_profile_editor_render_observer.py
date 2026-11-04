"""Bounded profile editor text/highlight/caret trace checks."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('profile_render_observer', ROOT / 'scripts/audit-profile-editor-render-observer.py')
observer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(observer)

class ProfileEditorRenderObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.native, cls.candidate, cls.image = observer.code_bodies()

    def test_bounded_render_traces(self):
        for case in observer.CASES:
            with self.subTest(case=case):
                target = observer.execute(self.native, self.image, *case)
                self.assertEqual(target, observer.execute(self.candidate, self.image, *case))
                self.assertEqual(target, observer.expected(case))

    def test_highlight_color_mutation_is_detected(self):
        body = bytearray(self.candidate)
        color = bytes.fromhex('d06060ff')
        self.assertEqual(body.count(color), 1)
        body[body.index(color)] ^= 1
        case = next(case for case in observer.CASES if case[4] == (1,))
        self.assertNotEqual(observer.execute(self.native, self.image, *case),
                            observer.execute(bytes(body), self.image, *case))

if __name__ == '__main__':
    unittest.main()
