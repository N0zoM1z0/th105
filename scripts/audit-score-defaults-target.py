#!/usr/bin/env python3
"""Pin ScoreData defaults/reset CFG and execute its native story-CSV policy."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x42ED70, 2428
SHA = 'edf6201796372e2afccac1e7d42589bf8c3a5c6014a4f35490b9c3f2b004ccc5'
UNIT = 'exact-first-score-defaults'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def observe_story_rows(image, code, values, names, expected):
    """Execute one character's native CSV region with external reader/STL observers.

    Entry is after the observed record-vector clear, exit before the character
    index increment. This does not execute game I/O, helper implementations,
    earlier card-count policy, or exception unwinding.
    """
    m = Uc(UC_ARCH_X86, UC_MODE_32)
    m.mem_map(0x400000, (len(image) + 4095) & ~4095)
    m.mem_write(0x400000, image)
    m.mem_write(ADDRESS, code)
    m.mem_map(0x800000, 0x20000)
    m.mem_map(0x1000000, 0x20000)
    w = lambda a, v: m.mem_write(a, struct.pack('<I', v & 0xffffffff))
    r = lambda a: struct.unpack('<I', m.mem_read(a, 4))[0]
    stack, vector, storage = 0x1010000, 0x801198, 0x810000
    w(stack + 0x18, 0)
    m.reg_write(UC_X86_REG_ESP, stack)
    m.reg_write(UC_X86_REG_ESI, vector)
    heap = [0x804000]
    ints, strings, paths, records = list(values), list(names), [], []
    counts = Counter()
    m.mem_write(0x803000, b'reimu\0')

    def cstr(a):
        data = bytearray()
        while m.mem_read(a, 1) != b'\0':
            data.extend(m.mem_read(a, 1)); a += 1
        return bytes(data)

    def string(a):
        return bytes(m.mem_read(r(a + 4) if r(a + 0x18) >= 16 else a + 4, r(a + 0x14)))

    def write_string(a, data):
        if len(data) < 16:
            m.mem_write(a + 4, data + b'\0'); capacity = 15
        else:
            dest = heap[0]; heap[0] += 0x100
            m.mem_write(dest, data + b'\0'); w(a + 4, dest); capacity = len(data)
        w(a + 0x14, len(data)); w(a + 0x18, capacity)

    cleanup = {0x4021C0: 8, 0x408A50: 8, 0x43BF80: 0, 0x40F150: 4,
               0x40F480: 0, 0x40F680: 0, 0x40F580: 4, 0x4020D0: 12,
               0x43BFD0: 0, 0x42DFC0: 4, 0x6898EA: 0, 0x40FDB0: 0,
               0x420A80: 0}

    def hook(u, address, size, data):
        if address == 0x42F61C:
            u.emu_stop(); return
        if address == 0x68A143:
            raise ValueError('native CSV fixture reached invalid-parameter guard')
        if address not in cleanup:
            return
        ss, receiver = u.reg_read(UC_X86_REG_ESP), u.reg_read(UC_X86_REG_ECX)
        result = 0
        counts[hex(address)] += 1
        if address in (0x4021C0, 0x408A50):
            text = bytes(u.mem_read(r(ss + 4), r(ss + 8)))
            write_string(receiver, (string(receiver) if address == 0x408A50 else b'') + text)
            result = receiver
        elif address == 0x43BF80:
            require(r(ss + 4) == 0, 'character fixture changed'); result = 0x803000
        elif address == 0x40F150:
            paths.append(cstr(r(ss + 4)).decode())
        elif address == 0x40F480:
            require(bool(ints), 'unexpected CSV integer read'); result = ints.pop(0)
        elif address == 0x40F580:
            require(bool(strings), 'unexpected CSV string read')
            result = r(ss + 4); write_string(result, strings.pop(0).encode())
        elif address == 0x4020D0:
            require(r(ss + 8) == 0 and r(ss + 12) == 0xffffffff, 'copy range changed')
            write_string(receiver, string(r(ss + 4))); result = receiver
        elif address == 0x43BFD0:
            result = {b'reimu': 0, b'alice': 6}[string(ss + 4)]
        elif address == 0x42DFC0:
            require(receiver == vector, 'append receiver changed')
            entry = bytes(u.mem_read(r(ss + 4), 24)); records.append(list(struct.unpack('<6i', entry)))
            u.mem_write(storage + 24 * (len(records) - 1), entry)
            w(vector + 4, storage); w(vector + 8, storage + 24 * len(records)); w(vector + 12, storage + 0x1000)
        u.reg_write(UC_X86_REG_EAX, result & 0xffffffff)
        u.reg_write(UC_X86_REG_ECX, 0xbad0c0de); u.reg_write(UC_X86_REG_EDX, 0xbad0dada)
        u.reg_write(UC_X86_REG_ESP, ss + 4 + cleanup[address]); u.reg_write(UC_X86_REG_EIP, r(ss))

    m.hook_add(UC_HOOK_CODE, hook)
    m.emu_start(0x42F306, 0, count=30000)
    require(m.reg_read(UC_X86_REG_EIP) == 0x42F61C, 'CSV region did not reach its reviewed exit')
    require(m.reg_read(UC_X86_REG_ESP) == stack, 'CSV region stack imbalance')
    require(not ints and not strings, 'CSV fixture not fully consumed')
    require(paths == ['data/csv/reimu/story.csv'], 'story CSV path changed')
    require(records == expected, 'threshold/dedup/difficulty/zero-statistics policy changed')
    require(counts['0x40f480'] == len(values) and counts['0x40f580'] == len(names), 'reader census changed')
    return dict(input_integers=values, input_names=names, records=records,
                paths=paths, calls=dict(counts), stack_preserved=True)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location('score_defaults_compare', ROOT / 'scripts/compare-function.py')
    compare = importlib.util.module_from_spec(spec); spec.loader.exec_module(compare)
    identity = compare.verify_target(); code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, 'complete body changed')
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(len(instructions) == 664 and sum(i.size for i in instructions) == SIZE, 'decode extent changed')
    by_address = {i.address: i for i in instructions}
    pending, reached, returns, calls = [ADDRESS], set(), [], Counter()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, 'escaping/noninstruction edge')
        reached.add(address); instruction = by_address[address]
        if instruction.mnemonic == 'ret':
            require(bytes(instruction.bytes) == b'\xc3', 'RET0 changed'); returns.append(address); continue
        if instruction.mnemonic == 'call':
            require(instruction.operands[0].type == x86.X86_OP_IMM, 'unexpected indirect call')
            calls[hex(instruction.operands[0].imm)] += 1
        if instruction.group(capstone.CS_GRP_JUMP):
            require(instruction.operands[0].type == x86.X86_OP_IMM, 'unexpected indirect jump')
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == 'jmp':
                continue
        pending.append(address + instruction.size)
    require(len(reached) == 661 and returns == [0x42F6EB], 'complete CFG changed')
    alignment = {hex(i.address): bytes(i.bytes).hex() for i in instructions if i.address not in reached}
    require(alignment == {'0x42ef69': '8da42400000000', '0x42eff6': '8da42400000000', '0x42effd': '8d4900'}, 'internal alignment changed')
    require(compare.target_bytes(ADDRESS + SIZE, 4) == b'\xcc' * 4, 'following separation changed')
    require(calls['0x68a143'] == 28 and calls['0x40f480'] == 4 and calls['0x40f680'] == 3, 'guard/reader census changed')
    require(calls['0x42db20'] == 2 and calls['0x42dfc0'] == 1 and calls['0x45c320'] == 2, 'set/vector/count calls changed')
    callers = []
    for site in (0x42F765, 0x42F82F):
        call = next(decoder.disasm(compare.target_bytes(site, 5), site))
        require(call.mnemonic == 'call' and call.operands[0].imm == ADDRESS, 'score-load caller changed')
        callers.append(hex(site))
    image = bytes(pefile.PE(str(ROOT / 'resources/th105.exe')).get_memory_mapped_image())
    cases = [([2, 77, 2, 100, 100, 200, -1, 199, 201, 100, 150, 99, 1, 100, 200, 100, 199],
              ['reimu', 'alice'], [[0,0,100,0,0,0],[0,3,-1,0,0,0],[0,0,199,0,0,0],
                                   [0,3,150,0,0,0],[6,0,100,0,0,0],[6,3,199,0,0,0]]),
             ([0], [], []), ([-1], [], []), ([1,77,0], ['reimu'], []), ([1,77,-1], ['reimu'], [])]
    native_cases = [observe_story_rows(image, code, *case) for case in cases]
    report = dict(result='target_cfg_closed', target_sha256=identity, address=hex(ADDRESS),
                  size=SIZE, code_sha256=SHA, instructions=664, reached=661,
                  internal_alignment=alignment, ret0_sites=[hex(a) for a in returns],
                  calls=dict(calls), score_load_caller_sites=callers, story_csv_cases=native_cases,
                  limitations='CSV region fixtures hook external services and STL providers; game I/O and EH unwinding are not executed. Nominal original type names/TU remain unknown.')
    if obj is not None:
        function = load_manifest()['units'][UNIT]['functions'][0]
        targets = compare.known_targets()
        targets.update({name: int(address, 0) for name, address in
                        (value.split('=', 1) for value in function['rel32_targets'])})
        candidate = compare.coff_symbol_bytes(obj, function['symbol_base'], ADDRESS, 0xffffffff,
                                              targets, compare.known_data_targets(), {})
        require(candidate == code, 'complete canonical candidate differs')
        require([observe_story_rows(image, candidate, *case) for case in cases] == native_cases,
                'candidate CSV observations differ')
        report['candidate'] = dict(object=str(obj), section_size=len(candidate),
                                   full_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
                                   all_relocations_replayed=True, unequal_positions=0, csv_cases_equal=5)
        report['result'] = 'candidate_exact'
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--object', type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (OSError, ValueError, KeyError, AssertionError) as error:
        print(json.dumps(dict(result='blocked', error=str(error)), indent=2)); return 1
    print(json.dumps(report, indent=2)); return 0


if __name__ == '__main__':
    raise SystemExit(main())
