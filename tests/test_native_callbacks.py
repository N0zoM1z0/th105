import sys
from pathlib import Path
import unittest
from unittest.mock import Mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from native_callbacks import guarded_callback


class NativeCallbackTests(unittest.TestCase):
    def test_failed_attestation_stops_and_survives_callback_boundary(self):
        engine, errors = Mock(), []
        callback = Mock(side_effect=ValueError('unreviewed native instruction'))
        guarded_callback(callback, errors)(engine, 0x401000, 3, None)
        engine.emu_stop.assert_called_once_with()
        self.assertEqual(errors, ['unreviewed native instruction'])

    def test_success_forwards_arguments_without_stopping(self):
        engine, callback, errors = Mock(), Mock(), []
        guarded_callback(callback, errors)(engine, 1, 2, None)
        callback.assert_called_once_with(engine, 1, 2, None)
        engine.emu_stop.assert_not_called()
        self.assertEqual(errors, [])


if __name__ == '__main__':
    unittest.main()
