#!/usr/bin/env python3
"""Execute Aya852 non-spawning paths and observe the owner-facing product store."""
from pathlib import Path
from collections import Counter
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys
import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('aya852_math', ROOT / 'scripts/audit-aya-object-903-native.py')
math = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = math
spec.loader.exec_module(math)
base = math.base


def product_read_sites(code, address):
    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cs.detail = True
    rows = list(cs.disasm(code, address))
    stores = [i for i, r in enumerate(rows) if r.mnemonic == 'fstp'
              and r.operands[0].type == x.X86_OP_MEM and r.operands[0].size == 4
              and r.operands[0].mem.base == x.X86_REG_EAX and r.operands[0].mem.disp == 0x6AC]
    assert len(stores) == 1, 'owner product store must be unique'
    end = stores[0]
    guards = [i for i in range(max(0, end - 24), end) if rows[i].mnemonic == 'cmp'
              and rows[i].operands[0].type == x.X86_OP_MEM and rows[i].operands[0].size == 1
              and rows[i].operands[0].mem.base == x.X86_REG_ESI and rows[i].operands[0].mem.disp == 0x104
              and rows[i].operands[1].type == x.X86_OP_IMM and rows[i].operands[1].imm & 255 == 255]
    assert len(guards) == 1, 'product facing guard must be unique'
    window = rows[guards[0]:end + 1]
    decoded = {r.address for r in window}
    for r in window:
        assert not r.group(capstone.CS_GRP_CALL) and not r.group(capstone.CS_GRP_RET)
        if r.group(capstone.CS_GRP_JUMP):
            assert r.operands[0].type == x.X86_OP_IMM and r.operands[0].imm in decoded, 'product branch escapes window'
    speed = [r.address for r in window if r.mnemonic in ('fld', 'fmul')
             and any(o.type == x.X86_OP_MEM and o.size == 4 and o.mem.base == x.X86_REG_ESI
                     and o.mem.disp == 0x374 for o in r.operands)]
    nested = [r.address for r in window if r.mnemonic in ('mov', 'movsx')
              and len(r.operands) == 2 and r.operands[1].type == x.X86_OP_MEM
              and r.operands[1].size == 1 and r.operands[1].mem.base == x.X86_REG_ECX
              and r.operands[1].mem.disp == 0x104]
    assert speed and nested, 'product operand reads missing'
    return dict(start=hex(window[0].address), end=hex(window[-1].address + window[-1].size),
                speed_pcs=[hex(pc) for pc in speed], nested_pcs=[hex(pc) for pc in nested],
                sha256=hashlib.sha256(code[window[0].address-address:window[-1].address+window[-1].size-address]).hexdigest())


def live_x87(uc):
    tag = uc.reg_read(base.r.UC_X86_REG_FPTAG)
    return dict(status=uc.reg_read(base.r.UC_X86_REG_FPSW), tag=tag,
                live_registers=[None if (tag >> (2*i)) & 3 == 3
                                else uc.reg_read(getattr(base.r, 'UC_X86_REG_FP' + str(i))) for i in range(8)])


class Probe(math.Probe):
    action_id = 852

    def __init__(self, table, obj=None, product_read_lifetimes=False):
        super().__init__(table, obj)
        self.product_read_lifetimes = product_read_lifetimes
        if product_read_lifetimes:
            self.product_sites = product_read_sites(bytes(self.uc.mem_read(self.start, self.size)), self.start)
            self.speed_read_pcs = {int(pc, 0) for pc in self.product_sites['speed_pcs']}
            self.nested_read_pcs = {int(pc, 0) for pc in self.product_sites['nested_pcs']}

    def prepare(self, case):
        seq, time, speed, facing, nested_facing, health, cw = self.settings
        for off, fmt, value in ((0x144, 'i', time), (0x374, 'I', speed), (0x104, 'b', facing),
                               (0x170, 'I', base.OWNER + 0x2000),
                               (0x2174, 'h', health), (0x1174, 'h', health),
                               (0x1170, 'I', base.OWNER + 0x3000), (0x3104, 'b', nested_facing)):
            self.uc.mem_write(base.OWNER + off, struct.pack('<' + fmt, value))
        self.product_stores = []
        self.product_speed_reads = []
        self.product_nested_reads = []

    def read(self, uc, access, address, size, value, data):
        if self.product_read_lifetimes:
            pc = uc.reg_read(base.r.UC_X86_REG_EIP)
            if pc in self.speed_read_pcs:
                assert address == base.OWNER + 0x374 and size == 4
                self.product_speed_reads.append(dict(
                    value=bytes(uc.mem_read(address, size)).hex(), writes=len(self.writes), **live_x87(uc)))
            elif pc in self.nested_read_pcs:
                assert address == base.OWNER + 0x3104 and size == 1
                self.product_nested_reads.append(dict(
                    value=bytes(uc.mem_read(address, size)).hex(), writes=len(self.writes), **live_x87(uc)))
        super().read(uc, access, address, size, value, data)

    def write(self, uc, access, address, size, value, data):
        if address == base.OWNER + 0x16AC and size == 4:
            self.writes.append((address - base.OWNER, size, value & 0xFFFFFFFF))
            self.product_stores.append(dict(
                value=value & 0xFFFFFFFF, status=uc.reg_read(base.r.UC_X86_REG_FPSW),
                tag=uc.reg_read(base.r.UC_X86_REG_FPTAG),
                live_registers=[None if (uc.reg_read(base.r.UC_X86_REG_FPTAG) >> (2*i)) & 3 == 3
                                else uc.reg_read(getattr(base.r, 'UC_X86_REG_FP' + str(i))) for i in range(8)],
            ))
            return
        super().write(uc, access, address, size, value, data)

    def evaluate(self, case):
        self.settings = case
        seq, time, speed, facing, nested_facing, health, cw = case
        assert all(time % divisor for divisor in (12, 40, 15)), 'matrix must avoid random/spawn paths'
        result = base.Probe.run(self, (seq, 0, health, cw, 20.0))
        assert result['stop'] == 'ret'
        expected = int(seq == 0 and time != 240 and health > 0)
        assert len(self.product_stores) == expected
        result['owner_product'] = bytes(self.uc.mem_read(base.OWNER + 0x16AC, 4)).hex()
        result['product_stores'] = self.product_stores
        if self.product_read_lifetimes:
            assert len(self.product_speed_reads) == len(self.product_nested_reads) == expected
            result.update(product_speed_reads=self.product_speed_reads, product_nested_reads=self.product_nested_reads)
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--object', type=Path, default=ROOT / base.unit['object'])
    parser.add_argument('--control-object', type=Path)
    parser.add_argument('--product-read-lifetimes', action='store_true',
                        help='Compare live x87 at actual nested-facing and speed reads; also cover PC24')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/aya852-native.json')
    args = parser.parse_args()
    table, receipt = math.lookup_fixture(base.c)
    cws = (0x27F, 0x67F, 0xA7F, 0xE7F, 0x37F, 0x77F, 0xB7F, 0xF7F)
    if args.product_read_lifetimes:
        cws = (0x7F, 0x47F, 0x87F, 0xC7F) + cws
    speeds = (0, 0x80000000, 1, 0x80000001, 0x3F000000, 0xBF000000,
              0x40D00000, 0x40E00000, 0x7F7FFFFF, 0xFF7FFFFF,
              0x7F800000, 0xFF800000, 0x7FC00123, 0xFFC00123, 0x7F800001, 0xFF800001)
    cases = list(itertools.product((0,), (239, 241), speeds, (-128,-1,0,1,127),
                                   (-128,-1,0,1,127), (100,), cws))
    cases += list(itertools.product((0,1,2,3), (239,241), (0x3F800000,), (-1,1), (-1,1),
                                   (-1,0), (0x27F,0x37F)))
    objects = [args.object] + ([args.control_object] if args.control_object else [])
    probes = [Probe(table, product_read_lifetimes=args.product_read_lifetimes)] + [
        Probe(table, obj, product_read_lifetimes=args.product_read_lifetimes) for obj in objects]
    differences = [Counter() for _ in objects]
    calls, stores = Counter(), 0
    examples = []
    for case in cases:
        values = [p.evaluate(case) for p in probes]
        calls.update(hex(a) for a in values[0]['calls'])
        stores += len(values[0]['product_stores'])
        for i, val in enumerate(values[1:]):
            fields = [k for k in values[0] if values[0][k] != val[k]]
            differences[i].update(fields)
            if fields and len(examples) < 3:
                examples.append(dict(case=case, object=i, fields=fields,
                                     target_product=values[0]['product_stores'], candidate_product=val['product_stores'],
                                     target_differences={key: values[0][key] for key in fields},
                                     candidate_differences={key: val[key] for key in fields}))
    helpers = {a:n for a,(n,_) in base.helpers.items()} | math.MATH
    report = dict(target_sha256=base.c.verify_target(), cases=len(cases), actual_returns=len(cases),
                  owner_product_stores=stores, target_calls=dict(calls),
                  objects=[dict(path=str(obj), sha256=base.lp.sha(obj), differing_fields=dict(diff),
                                mapped_code_sha256=hashlib.sha256(bytes(probe.uc.mem_read(probe.start,probe.size))).hexdigest(),
                                mapped_base=hex(probe.start), mapped_size=probe.size)
                           for obj,diff,probe in zip(objects,differences,probes[1:])], examples=examples,
                  lookup={k:v for k,v in receipt.items() if k!='trace'},
                  original_helpers={hex(a):dict(size=n,sha256=hashlib.sha256(base.c.target_bytes(a,n)).hexdigest())
                                    for a,n in helpers.items() if hex(a) in calls},
                  input_sha256=hashlib.sha256(json.dumps(cases).encode()).hexdigest(),
                  product_read_lifetimes=args.product_read_lifetimes,
                  x87_control_words=[hex(cw) for cw in cws],
                  auditor_inputs={path: base.lp.sha(ROOT / path) for path in (
                      'scripts/audit-aya-object-852-native.py', 'scripts/audit-aya-object-903-native.py',
                      'scripts/audit-aya-object-901-transition.py', 'scripts/iku_native_math.py')},
                  scope='852 original root and math/animation helpers to actual RET; non-spawning finite timer inputs, signed facing bytes and masked x87; owner product memory-write snapshots; no random/spawn, arbitrary resources, unmasked exceptions or whole-root proof')
    if args.product_read_lifetimes:
        report['product_read_sites'] = [probe.product_sites for probe in probes]
        report['scope'] += '; additionally compare live x87/value/write epochs at actual product operand reads'
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))
    if any(differences):
        raise SystemExit(1)


if __name__ == '__main__':
    main()
