"""Read-only, nonoverlapping animation data for Reimu low-action probes.

This is supplied fixture data, not reconstructed game assets or authored code.
"""
import struct

RESOURCE = 0x3000000
TREE, HEAD, VECTOR, SLOT = RESOURCE, RESOURCE+0x100, RESOURCE+0x300, RESOURCE+0x400


def resource_graph(case):
    image = bytearray(0x10000)
    nodes = {key: RESOURCE + 0x500 + key * 0x20 for key in range(11)}
    blocks = {key: RESOURCE + 0x1000 + key * 0x80 for key in range(11)}
    frames = {key: RESOURCE + 0x2000 + key * 0x800 for key in range(11)}
    def put(address, fmt, *values):
        struct.pack_into(fmt, image, address - RESOURCE, *values)
    def tree(keys, parent, depth=0):
        if not keys:
            return HEAD
        key = keys[len(keys)//2]
        node = nodes[key]
        left = tree(keys[:len(keys)//2], node, depth+1)
        right = tree(keys[len(keys)//2+1:], node, depth+1)
        put(node, "<IIIiI", left, parent, right, key, blocks[key])
        put(node+0x14, "<B", 0 if depth == 3 else 1)
        return node
    root = tree(list(range(11)), HEAD)
    put(TREE+4, "<II", HEAD, 11)
    put(HEAD, "<III", nodes[0], root, nodes[10])
    put(HEAD+0x14, "<BB", 1, 1)
    put(VECTOR+4, "<III", SLOT, SLOT+4, SLOT+4)
    frame_count = max(case["frame"]+1, 2 if case["transition"] == "frame" else 1)
    for key in range(11):
        for index in range(4):
            block, frame = blocks[key]+index*0x20, frames[key]+index*0x200
            put(block+4, "<II", frame, frame+frame_count*0x88)
            put(block+0x14, "<B", 0 if index == 0 else 1)
            put(block+0x18, "<II", block-0x20 if index else 0,
                block+0x20 if index < 3 and case["transition"] != "terminal" else 0)
            for item in range(frame_count):
                put(frame+item*0x88+8, "<hhhhhhb", case["duration"], 0,
                    index+1, index+2, 16+item, 24, -1)
    return bytes(image), blocks, frames, frame_count
