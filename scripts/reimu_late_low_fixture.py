"""Read-only seven-sequence data and target-executed orientation initialization.

Supplied animation data is a fixture, not recovered game assets. The separate
orientation table is produced by unchanged canonical instructions through RET.
"""
import hashlib
import struct

import unicorn
from unicorn import x86_const as r

from reimu_animation_fixture import RESOURCE, TREE, HEAD, VECTOR, SLOT


def resource_graph(case, keys, *, frame_capacity=6, sequence_capacity=7):
    keys = tuple(sorted(keys))
    if (not keys or len(keys) != len(set(keys)) or len(keys) > 64
            or not 2 <= frame_capacity <= 14 or not 0 <= case["frame"] < frame_capacity
            or not 1 <= sequence_capacity <= 9):
        raise ValueError("late-low resource capacity exceeded")
    block_stride = (sequence_capacity*0x20+0xff) & ~0xff
    frame_base = (0x1000+len(keys)*block_stride+0xfff) & ~0xfff
    nodes = {key: RESOURCE+0x500+index*0x20 for index, key in enumerate(keys)}
    blocks = {key: RESOURCE+0x1000+index*block_stride for index, key in enumerate(keys)}
    frame_stride = (frame_capacity*0x88+0x3ff) & ~0x3ff
    frames = {key: RESOURCE+frame_base+index*sequence_capacity*frame_stride for index, key in enumerate(keys)}

    required = frame_base+len(keys)*sequence_capacity*frame_stride
    image = bytearray(max(0x40000 if len(keys) <= 24 else 0x100000, (required+0xfff) & ~0xfff))

    def put(address, fmt, *values):
        struct.pack_into(fmt, image, address-RESOURCE, *values)

    def tree(items, parent, depth=0):
        if not items:
            return HEAD
        middle = len(items)//2
        key, node = items[middle], nodes[items[middle]]
        left, right = tree(items[:middle], node, depth+1), tree(items[middle+1:], node, depth+1)
        put(node, "<IIIiI", left, parent, right, key, blocks[key])
        put(node+0x14, "<B", 0 if depth == len(keys).bit_length()-1 and depth else 1)
        return node

    root = tree(keys, HEAD)
    put(TREE+4, "<II", HEAD, len(keys))
    put(HEAD, "<III", nodes[keys[0]], root, nodes[keys[-1]])
    put(HEAD+0x14, "<BB", 1, 1)
    put(VECTOR+4, "<III", SLOT, SLOT+4, SLOT+4)
    frame_count = max(case["frame"]+1, 2 if case["transition"] == "frame" else 1)
    for key in keys:
        for index in range(sequence_capacity):
            block, frame = blocks[key]+index*0x20, frames[key]+index*frame_stride
            put(block+4, "<II", frame, frame+frame_count*0x88)
            put(block+0x14, "<B", 0 if index == 0 else 1)
            put(block+0x18, "<II", block-0x20 if index else 0,
                block+0x20 if index < sequence_capacity-1 and not case.get("single_sequence", False) else 0)
            for item in range(frame_count):
                put(frame+item*0x88+8, "<hhhhhhb", case["duration"], 0,
                    index+1, index+2, 16+item, 24, -1)
    return bytes(image), blocks, frames, frame_count


def native_orientation_table(image, control_word):
    """Run original4065B0, including original cosine code; replace no results."""
    body = bytes(image[0x65B0:0x6661])
    if hashlib.sha256(body).hexdigest() != "2ca8263dd81760f21b6d23ec8912f5a12a0bea3a5823dfce24605bafbacd5d05":
        raise ValueError("orientation initializer identity changed")
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, 0x311000)
    engine.mem_write(0x400000, bytes(image))
    stack, end, sp = 0x2500000, 0x710000, 0x250FF00
    engine.mem_map(stack, 0x10000)
    engine.mem_write(sp, struct.pack("<I", end))
    engine.reg_write(r.UC_X86_REG_ESP, sp)
    engine.reg_write(r.UC_X86_REG_FPCW, control_word)
    visited, writes, failure = {}, set(), []

    def code(uc, address, size, unused):
        if not 0x401000 <= address < address+size <= 0x6BF33A:
            failure.append(f"initializer left target text at {address:#x}")
            uc.emu_stop()
        visited[address] = bytes(uc.mem_read(address, size))

    def write(uc, access, address, size, value, unused):
        if not (stack <= address <= address+size <= stack+0x10000
                or 0x6FE8B0 <= address <= address+size <= 0x7020F0
                or 0x6FDEF0 <= address <= address+size <= 0x6FE8B0
                or address == 0x6FA1FC and size == 4):
            failure.append(f"initializer wrote outside reviewed globals at {address:#x}")
            uc.emu_stop()
        writes.add((address, size))

    engine.hook_add(unicorn.UC_HOOK_CODE, code)
    engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, write)
    engine.emu_start(0x4065B0, end, count=3000000)
    if (failure or engine.reg_read(r.UC_X86_REG_EIP) != end
            or engine.reg_read(r.UC_X86_REG_ESP) != sp+4
            or engine.reg_read(r.UC_X86_REG_FPCW) != control_word):
        raise ValueError(f"native table initialization failed: {failure}")
    table = bytes(engine.mem_read(0x6FE8B0, 14400))
    if tuple(struct.unpack_from("<f", table, index*4)[0] for index in (0, 900, 1800, 2700)) != (1.0, 0.0, -1.0, 0.0):
        raise ValueError("native table initialization did not publish its cardinal values")
    return table, {"initializer_address": "0x4065b0", "initializer_size": len(body),
                   "initializer_sha256": hashlib.sha256(body).hexdigest(),
                   "control_word": control_word, "table_sha256": hashlib.sha256(table).hexdigest(),
                   "visited_instructions": {hex(a): b.hex() for a, b in sorted(visited.items())},
                   "distinct_writes": len(writes), "scope": "original instructions/RET; supplied stack, no API/result hooks"}
