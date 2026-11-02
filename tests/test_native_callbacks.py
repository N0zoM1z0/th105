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


class NativeCallbackBridgeTests(unittest.TestCase):
    def test_assertion_is_recorded_not_lost(self):
        engine, errors = Mock(), []
        def fail(u, *args):
            raise AssertionError('bad receiver')
        guarded_callback(fail, errors)(engine, 1, 2, None)
        engine.emu_stop.assert_called_once_with()
        self.assertEqual(errors, ['bad receiver'])

    def test_real_ctypes_bridge_stops_before_guest_write(self):
        from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
        engine = Uc(UC_ARCH_X86, UC_MODE_32)
        engine.mem_map(0x1000, 0x1000)
        engine.mem_map(0x2000, 0x1000)
        # Test-only MOV [2000],1 must not execute after a callback failure.
        engine.mem_write(0x1000, bytes.fromhex('c7050020000001000000'))
        errors = []
        def fail(u, address, size, data):
            raise ValueError('outside observed root')
        engine.hook_add(UC_HOOK_CODE, guarded_callback(fail, errors))
        engine.emu_start(0x1000, 0x100a, count=1)
        self.assertEqual(errors, ['outside observed root'])
        self.assertEqual(bytes(engine.mem_read(0x2000, 4)), bytes(4))


if __name__ == '__main__':
    unittest.main()
