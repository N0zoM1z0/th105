import importlib.util
from pathlib import Path
import sys
from types import SimpleNamespace
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
sp = importlib.util.spec_from_file_location('timeline_receiver_tests', Path(__file__).resolve().parents[1] / 'scripts/verify-scene-timeline-loader-payload.py')
g = importlib.util.module_from_spec(sp)
sp.loader.exec_module(g)

class TimelineReceiverTests(unittest.TestCase):
    def calls(self):
        return [(607, 20, '?set_texture@CSpriteEx@@QAEXIHHHH@Z'),
                (755, 20, '?set_texture_options@CSpriteEx@@QAEXIHHHHHH@Z')]
    def check(self, calls):
        return g.check_texture_calls(SimpleNamespace(refs=lambda symbol, size: calls), 'owner')
    def test_actual_members(self):
        self.assertEqual(self.check(self.calls()), self.calls())
    def test_facade_rejected(self):
        calls = self.calls()
        calls[1] = (755, 20, '?set_texture_options@TimelineSpriteOptionsView@th105@@QAEXIHHHHHH@Z')
        with self.assertRaises(ValueError): self.check(calls)
    def test_wrong_relocation_kind(self):
        calls = self.calls(); calls[1] = (755, 6, calls[1][2])
        with self.assertRaises(ValueError): self.check(calls)
    def test_wrong_signedness(self):
        calls = self.calls(); calls[1] = (755, 20, '?set_texture_options@CSpriteEx@@QAEXIIIIIII@Z')
        with self.assertRaises(ValueError): self.check(calls)
    def test_missing_or_extra_call(self):
        for calls in [self.calls()[:1], self.calls() + [self.calls()[1]]]:
            with self.assertRaises(ValueError): self.check(calls)

if __name__ == '__main__': unittest.main()
