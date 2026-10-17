import importlib.util
from pathlib import Path
import struct
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('reimu_stack_tests', ROOT/'scripts/audit-reimu-root-stack.py')
stack = importlib.util.module_from_spec(spec)
spec.loader.exec_module(stack)

# Small analyzer fixtures, not reconstructed implementation or matching inputs.
PROLOGUE = bytes.fromhex('55 8b ec 83 e4 f8 81 ec 20 00 00 00 53 55 56 57')
EPILOGUE = bytes.fromhex('5f 5e 5d 5b 8b e5 5d c3')


def graph(body, pops=None):
    return stack.StackGraph(PROLOGUE + body + EPILOGUE, {}, pops or {}, {8: 4, 12: 4, 20: 0})


def shared_request(body):
    # Finish seven stack arguments and a real relative CALL encoding.
    body += bytes.fromhex('6a 01 6a 01 83 ec 08 68 20 03 00 00')
    next_address = stack.ADDRESS + len(PROLOGUE) + len(body) + 5
    body += b'\xe8' + struct.pack('<i', stack.SPAWN - next_address)
    return graph(body, {stack.SPAWN: 28})


class ReimuRootStackTests(unittest.TestCase):
    def test_branch_merge_rejects_disagreeing_esp(self):
        # One arm pushes EAX before both arms reach NOP.
        with self.assertRaisesRegex(ValueError, 'inconsistent ESP'):
            graph(bytes.fromhex('85 c0 74 01 50 90'))

    def test_two_virtual_slots_can_share_one_call_when_cleanup_agrees(self):
        # Conditional loads of slots8/12, followed by push0/callEAX.
        result = graph(bytes.fromhex('85 c9 74 05 8b 42 08 eb 03 8b 42 0c 6a 00 ff d0'))
        self.assertEqual(set(result.call_pops.values()), {4})
        definitions = next(iter(result.virtual_definitions.values()))
        self.assertEqual(set(definitions.values()), {8, 12})

    def test_two_virtual_slots_with_different_cleanup_are_rejected(self):
        with self.assertRaisesRegex(ValueError, 'disagreeing indirect-call'):
            graph(bytes.fromhex('85 c9 74 05 8b 42 08 eb 03 8b 42 14 6a 00 ff d0'))

    def test_pointer_provenance_does_not_survive_a_volatile_call_result(self):
        result = graph(bytes.fromhex('8b 42 08 6a 00 ff d0 50 58'))
        push = next(row for row in result.rows if row.mnemonic == 'push' and row.op_str == 'eax')
        with self.assertRaisesRegex(ValueError, 'caller-saved pointer'):
            result.pointer_values(push.address, push.operands[0])

    def test_partial_pointer_write_invalidates_the_previous_full_definition(self):
        result = graph(bytes.fromhex('8d 44 24 10 66 b8 00 00 50 58'))
        push = next(row for row in result.rows if row.mnemonic == 'push' and row.op_str == 'eax')
        with self.assertRaisesRegex(ValueError, 'partial request-pointer'):
            result.pointer_values(push.address, push.operands[0])

    def test_shared_call_traces_both_argument_pushes_and_keeps_action_context(self):
        result = shared_request(bytes.fromhex(
            '6a 03 85 c9 74 07 8d 44 24 14 50 eb 05 8d 44 24 18 50'))
        request, = result.payloads()
        self.assertEqual(request['values'], [('stack', 16), ('stack', 20)])
        self.assertEqual(len(request['pushes']), 2)
        first_path = stack.ADDRESS + len(PROLOGUE) + 6
        request, = result.payloads(first_path)
        self.assertEqual(request['values'], [('stack', 16)])

    def test_one_initialized_predecessor_cannot_hide_an_unwritten_argument(self):
        result = shared_request(bytes.fromhex(
            '6a 03 85 c9 74 07 8d 44 24 14 50 eb 03 83 ec 04'))
        with self.assertRaisesRegex(ValueError, 'unwritten incoming stack'):
            result.payloads()


if __name__ == '__main__':
    unittest.main()
