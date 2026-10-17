"""Keep the supplied native resource graph structurally valid and disjoint."""
from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
from reimu_animation_fixture import RESOURCE, TREE, HEAD, VECTOR, SLOT, resource_graph


class ReimuAnimationFixtureTests(unittest.TestCase):
    linked_terminal = False
    keys = tuple(range(11))

    def graph(self, transition="frame"):
        return resource_graph({"transition": transition, "frame": 0, "duration": 3}, self.keys, linked_terminal=self.linked_terminal)

    def read(self, image, address, fmt="<I"):
        return struct.unpack_from(fmt, image, address-RESOURCE)

    def test_tree_has_correct_owners_order_and_red_black_heights(self):
        image, blocks, _, _ = self.graph()
        root = self.read(image, HEAD+4)[0]
        self.assertEqual(self.read(image, TREE+4, "<II"), (HEAD, len(self.keys)))
        self.assertEqual(self.read(image, HEAD+0x14, "<BB"), (1, 1))
        keys = []
        def walk(node, parent, parent_red=False):
            if node == HEAD:
                return 1
            left, actual_parent, right, key, block = self.read(image, node, "<IIIiI")
            color, nil = self.read(image, node+0x14, "<BB")
            self.assertEqual(actual_parent, parent)
            self.assertEqual(nil, 0)
            self.assertEqual(block, blocks[key])
            self.assertFalse(parent_red and color == 0)
            before = walk(left, node, color == 0)
            keys.append(key)
            after = walk(right, node, color == 0)
            self.assertEqual(before, after)
            return before+color
        self.assertEqual(self.read(image, root+0x14, "<B"), (1,))
        walk(root, HEAD)
        self.assertEqual(keys, list(self.keys))

    def test_two_frame_arrays_do_not_overlap_nodes_vectors_or_each_other(self):
        image, blocks, _, frame_count = self.graph()
        self.assertEqual(frame_count, 2)
        root = self.read(image, HEAD+4)[0]
        spans = [(TREE, TREE+12), (HEAD, HEAD+24), (VECTOR, VECTOR+16), (SLOT, SLOT+4)]
        def nodes(node):
            if node != HEAD:
                spans.append((node, node+24))
                left, _, right = self.read(image, node, "<III")
                nodes(left)
                nodes(right)
        nodes(root)
        for first in blocks.values():
            for index in range(4):
                block = first+index*0x20
                begin, end = self.read(image, block+4, "<II")
                self.assertEqual(end-begin, frame_count*0x88)
                spans.extend(((block, block+0x20), (begin, end)))
        spans.sort()
        for (_, previous_end), (next_start, _) in zip(spans, spans[1:]):
            self.assertLessEqual(previous_end, next_start)

    def test_terminal_has_no_successor_and_block_profile_has_real_links(self):
        for transition in ("terminal", "block"):
            image, blocks, _, _ = self.graph(transition)
            for first in blocks.values():
                for index in range(4):
                    block = first+index*0x20
                    previous, following = self.read(image, block+0x18, "<II")
                    self.assertEqual(previous, block-0x20 if index else 0)
                    self.assertEqual(following, block+0x20 if (transition == "block" or self.linked_terminal) and index < 3 else 0)


class ReimuRecoveryAnimationFixtureTests(ReimuAnimationFixtureTests):
    linked_terminal = True
    keys = tuple(range(11)) + tuple(range(71, 79)) + (97,)


if __name__ == "__main__":
    unittest.main()
