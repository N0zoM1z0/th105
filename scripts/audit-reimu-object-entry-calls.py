"""Execute the two nonexact ReimuObject entry owners through real selectors."""
from pathlib import Path
from collections import Counter
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import tomllib

import argparse

import capstone
import pefile
import unicorn
from unicorn import x86_const as r
from unicorn import unicorn as unicorn_api

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))


def load(name, file):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / file)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


c = load('entry_residual_c', 'compare-function.py')
m = load('entry_residual_m', 'compare-giant-action-switches.py')
animation = load('entry_residual_animation', 'audit-common-fighter-animation-paths.py')
ADDRESS, SIZE, CANDIDATE = 0x4a1ce0, 4892, 0x800000
BODY_SHA = '1cda9c10ed7d9ab2225800db60a62f45099c7cd3d7adec15621bfa3a49b8e6c1'
OWNER, STACK, RETURN = 0x2000000, 0x2100000, 0x710000
RESOURCE = 0x3000000
TREE, HEAD, NODE = RESOURCE, RESOURCE+0x100, RESOURCE+0x200
VECTOR, SLOT, BLOCK, FRAME, PARAMETERS = [RESOURCE+x for x in (0x300, 0x400, 0x1000, 0x2000, 0x4000)]
HELPERS = {k: v for k, v in animation.HELPERS.items()
           if k in (0x68a1a0, 0x45c180, 0x45c110, 0x45c390, 0x45c320,
                    0x436760, 0x40c100, 0x407160, 0x407230, 0x4073a0, 0x4073c0)}


def cases(smoke=False):
    requests = (0, 0x80000000, 0x3f000000, 0xbf000000,
                0x3f800000, 0x3fe00000, 0x40200000, 0x40700000,
                0x40800000, 0x40b80000, 0x40c00000, 0x40e00000, 0x41000000, 0x41100000)
    if smoke:
        requests = (0, 0xbf000000, 0x40800000, 0x40b80000)
    for action, request, sequence, cw in itertools.product(
            (906, 999), requests, (-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), (0x27f, 0x37f)):
        yield dict(action=action, request=request, sequence=sequence, cw=cw)


def graph(case):
    image = bytearray(0x10000)
    def put(address, fmt, *values):
        struct.pack_into('<'+fmt, image, address-RESOURCE, *values)
    put(TREE+4, 'II', HEAD, 1)
    put(HEAD, 'III', NODE, NODE, NODE)
    put(HEAD+0x14, 'BB', 1, 1)
    put(NODE, 'IIIiI', HEAD, HEAD, HEAD, case['action'], BLOCK)
    put(NODE+0x14, 'BB', 1, 0)
    put(VECTOR+4, 'III', SLOT, SLOT+4, SLOT+4)
    for sequence in range(10):
        block, frame = BLOCK+sequence*0x20, FRAME+sequence*0x100
        put(block+4, 'II', frame, frame+0x88)
        put(block+0x14, 'B', sequence != 0)
        put(block+0x18, 'II', block-0x20 if sequence else 0,
            block+0x20 if sequence < 9 else 0)
        put(frame+8, 'hhhhhhb', 3, 0, sequence+1, sequence+2, 16, 24, -1)
    put(PARAMETERS, 'ffIf', 37.25, -12.5, case['request'], 0.0)
    return bytes(image)


class Probe:
    def __init__(self, image, candidate=None):
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.uc.mem_write(0x400000, image)
        self.start = ADDRESS if candidate is None else CANDIDATE
        if candidate is not None:
            self.uc.mem_map(CANDIDATE, 0x2000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            self.uc.mem_write(CANDIDATE, candidate)
        for address in (OWNER, STACK):
            self.uc.mem_map(address, 0x10000)
        self.uc.mem_map(RESOURCE, 0x10000, unicorn.UC_PROT_READ)
        self.initial = self.uc.context_save()
        self.visited = set()
        self.counts = Counter()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        if not (OWNER <= address <= address+size <= OWNER+0x388
                or STACK <= address <= address+size <= STACK+0x10000):
            self.failure = f'unreviewed write at {address:#x}'
            uc.emu_stop()

    def instruction(self, uc, address, size, unused):
        if self.start <= address < self.start+SIZE:
            self.visited.add(address-self.start)
        elif not any(a <= address < a+n for a, (n, _) in HELPERS.items()):
            self.failure = f'unreviewed execution at {address:#x}'
            uc.emu_stop()
            return
        if address in HELPERS:
            self.counts[address] += 1
            self.trace.append(address)
        if address == 0x45c390:
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            value = struct.unpack('<I', uc.mem_read(sp+4, 4))[0]
            if uc.reg_read(r.UC_X86_REG_ECX) != OWNER or not 0 <= value < 10:
                self.failure = 'selector receiver/sequence outside fixture'
                uc.emu_stop()
                return
            self.arguments.append(value)
        raw = bytes(uc.mem_read(address, size))
        if raw[0] in (0xc2, 0xc3):
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack('<I', uc.mem_read(sp, 4))[0] == RETURN:
                self.saw_ret = True

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes([0xa5])*0x388)
        uc.mem_write(STACK+0xc000, bytes(0x4000))
        uc.mem_write(RESOURCE, graph(case))
        for offset, fmt, value in ((0, 'I', 0x6c40a4), (0xec, 'f', 640.0),
                (0xf0, 'f', 100.0), (0x104, 'b', -1), (0x130, 'I', VECTOR),
                (0x13c, 'h', case['action']), (0x13e, 'h', case['sequence']),
                (0x160, 'I', TREE), (0x340, 'I', PARAMETERS)):
            uc.mem_write(OWNER+offset, struct.pack('<'+fmt, value))
        sentinels = {r.UC_X86_REG_EBX: 0x11111111, r.UC_X86_REG_ESI: 0x22222222,
                     r.UC_X86_REG_EDI: 0x33333333, r.UC_X86_REG_EBP: 0x44444444}
        for register, value in sentinels.items():
            uc.reg_write(register, value)
        sp = STACK+0xff00
        uc.mem_write(sp, struct.pack('<I', RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case['cw'])
        self.failure, self.arguments, self.trace, self.saw_ret = None, [], [], False
        uc.emu_start(self.start, RETURN, count=20000)
        if self.failure:
            raise ValueError(f'{case}: {self.failure}')
        if (not self.saw_ret or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                or uc.reg_read(r.UC_X86_REG_ESP) != sp+4
                or any(uc.reg_read(k) != v for k, v in sentinels.items())):
            raise ValueError(f'{case}: native RET ABI failed')
        if (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError('unbalanced x87 stack')
        should_select = case['action'] == 999 or case['request'] not in (0, 0x80000000)
        if len(self.arguments) != should_select or (should_select and 0x4073c0 not in self.trace):
            raise ValueError('required real selector/commit execution missing')
        return {'object': bytes(uc.mem_read(OWNER, 0x388)).hex(),
                'calls': self.trace, 'selector_arguments': self.arguments,
                'control_word': uc.reg_read(r.UC_X86_REG_FPCW)}


def audit(path, smoke=False):
    object_sha = hashlib.sha256(path.read_bytes()).hexdigest()
    target_sha = c.verify_target()
    target = c.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(target).hexdigest() != BODY_SHA:
        raise ValueError('target callable changed')
    for slot, destination in ((0x6c40b0, 0x45c390), (0x6c40c0, 0x45c180)):
        if struct.unpack('<I', c.target_bytes(slot, 4))[0] != destination:
            raise ValueError('original ReimuObject vtable slot changed')
    unit = tomllib.loads((ROOT/'config/match-units.toml').read_text())['units']['gpt-web-reimu-object-action-entry']
    function = unit['functions'][0]
    obj = m.CoffObject(path, symbol_base=function['symbol_base'])
    known = c.known_targets()
    known.update({name: int(value, 0) for name, value in
                  (row.split('=', 1) for row in function['rel32_targets'])})
    data = dict(row.split('=', 1) for row in function['dir32_targets'])
    candidate = c.coff_symbol_bytes(path, function['symbol_base'], CANDIDATE,
                                    len(obj.text), known, c.known_data_targets(), data)
    canonical = c.coff_symbol_bytes(path, function['symbol_base'], ADDRESS,
                                    len(obj.text), known, c.known_data_targets(), data)
    if len(candidate) != 5440:
        raise ValueError('candidate envelope outside this fixture')
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    rows = list(decoder.disasm(candidate[:SIZE], CANDIDATE))
    if (len(rows) != 1325 or sum(len(i.bytes) for i in rows) != SIZE
            or sum(i.mnemonic == 'ret' for i in rows) != 39):
        raise ValueError('candidate callable shape differs')
    if canonical[SIZE:] != c.target_bytes(ADDRESS+SIZE, 548):
        raise ValueError('candidate metadata differs')
    image = pefile.PE(str(ROOT/'resources/th105.exe')).get_memory_mapped_image()
    probes = [Probe(image), Probe(image, candidate)]
    digest, examples, mismatches, cohorts = hashlib.sha256(), [], 0, Counter()
    all_cases = list(cases(smoke))
    if len(all_cases) != (192 if smoke else 672):
        raise ValueError('incomplete input matrix')
    for case in all_cases:
        digest.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = [probe.evaluate(case) for probe in probes]
        cohorts[case['action']] += 1
        if expected != actual:
            mismatches += 1
            if len(examples) < 4:
                examples.append({'case': case, 'target': expected, 'candidate': actual})
    if object_sha != hashlib.sha256(path.read_bytes()).hexdigest():
        raise ValueError('object changed during audit')
    return {'unicorn_version': unicorn.__version__,
            'unicorn_library_sha256': hashlib.sha256(Path(unicorn_api._uc._name).read_bytes()).hexdigest(),
            'python_version': sys.version.split()[0],
            'helper_sha256': {hex(a): hashlib.sha256(c.target_bytes(a, n)).hexdigest()
                              for a, (n, _) in HELPERS.items()},
            'schema': 'th105-reimu-object-entry-residual-native-v1',
            'target_sha256': target_sha, 'body_sha256': BODY_SHA,
            'object_sha256': object_sha,
            'canonical_payload_sha256': hashlib.sha256(canonical).hexdigest(),
            'cases': len(all_cases), 'mismatch_count': mismatches,
            'action_counts': dict(cohorts), 'input_sha256': digest.hexdigest(),
            'helper_counts': [{hex(k): v for k, v in p.counts.items()} for p in probes],
            'visited_root_instructions': [len(p.visited) for p in probes],
            'examples': examples, 'audit_source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
            'scope': '906/999 only; original native selector/frame/texture/commit code with read-only '
                     'ten-sequence zero-texture data; fresh candidate at a separate address; object bytes, '
                     'call traces, selector arguments, FPCW/TOP and native RET ABI; no helper replacement, '
                     'target byte patch, returning-world, whole-root or canonical-exact claim',
            'build_provenance_verified': False}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('--smoke', action='store_true')
    args = parser.parse_args()
    result = audit(args.object, args.smoke)
    print(json.dumps(result, indent=2))
    sys.exit(bool(result['mismatch_count']))
