#!/usr/bin/env python3
"""Pin Aya's three AL predicate consumers without changing the int-return callee ABI."""
from pathlib import Path
import argparse
import hashlib
import importlib.util
import json
import sys
import tomllib
import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
import linked_pe as lp
from predicate_return_range import prove_boolean_eax
from workflow_manifest import load_manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--previous-object', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/aya-predicate-widths.json')
    args = parser.parse_args()
    c = lp.comparator()
    target_sha = c.verify_target()
    unit = load_manifest()['units']['gpt-web-aya-object-vslot28-full-root']
    f = unit['functions'][0]
    spec = importlib.util.spec_from_file_location('aya_predicate_coff', ROOT / 'scripts/compare-giant-action-switches.py')
    mapper = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mapper
    spec.loader.exec_module(mapper)
    root = mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT / 'config/giant-action-switches.toml').read_text()), 'aya-object-vslot28')
    helpers = {0x435DC0: 42, 0x5F9310: 64}
    proofs = [prove_boolean_eax(c.target_bytes(a, n), a, (0x435D60,)) for a, n in helpers.items()]
    address = 0x61A290

    def packet(obj):
        co = mapper.CoffObject(obj, symbol_base=f['symbol_base'])
        meta = mapper.build_candidate_map(co, root)['metadata_start']
        code = c.coff_symbol_bytes(obj, f['symbol_base'], address, len(co.text),
                                  {a: int(b, 0) for a, b in (z.split('=', 1) for z in f['rel32_targets'])},
                                  c.known_data_targets(), dict(z.split('=', 1) for z in f.get('dir32_targets', [])))
        return code, meta

    def consumers(code, size):
        cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        cs.detail = True
        rows = list(cs.disasm(code[:size], address))
        assert sum(row.size for row in rows) == size
        result = []
        for i, row in enumerate(rows):
            if (row.mnemonic == 'call' and row.operands[0].type == x.X86_OP_IMM
                    and row.operands[0].imm in helpers):
                test, branch = rows[i + 1:i + 3]
                assert test.mnemonic == 'test' and test.op_str in ('al, al', 'eax, eax')
                assert branch.mnemonic == 'je'
                result.append(dict(call=hex(row.address), callee=hex(row.operands[0].imm),
                                   test=hex(test.address), bytes=test.bytes.hex(), operand=test.op_str))
        assert len(result) == 3
        return result

    target_sites = consumers(c.target_bytes(address, 19522), 19522)
    assert [site['call'] for site in target_sites] == ['0x61aa22', '0x61aaa4', '0x61bb35']
    assert all(site['bytes'] == '84c0' for site in target_sites)
    obj = ROOT / unit['object']
    code, size = packet(obj)
    sites = consumers(code, size)
    assert [site['callee'] for site in sites] == [site['callee'] for site in target_sites]
    assert all(site['bytes'] == '84c0' for site in sites), 'selected callers still consume full EAX'
    delta = None
    if args.previous_object:
        old, old_size = packet(args.previous_object)
        old_sites = consumers(old, old_size)
        assert old_size == size and len(old) == len(code)
        assert [site['call'] for site in old_sites] == [site['call'] for site in sites]
        assert all(site['bytes'] == '85c0' for site in old_sites)
        changed = [i for i, (a, b) in enumerate(zip(old, code)) if a != b]
        assert changed == [int(site['test'], 0) - address for site in sites]
        assert all(old[i] == 0x85 and code[i] == 0x84 for i in changed)
        delta = dict(previous_sha256=lp.sha(args.previous_object),
                     previous_canonical_sha256=hashlib.sha256(old).hexdigest(),
                     changed_offsets=[hex(i) for i in changed],
                     scope='complete canonical payload differs only at the three TEST opcode bytes')
    report = dict(target_sha256=target_sha, object_sha256=lp.sha(obj),
                  full_bytes=len(code), metadata_start=size, canonical_sha256=hashlib.sha256(code).hexdigest(),
                  helper_return_proofs=proofs, target_consumers=target_sites, selected_consumers=sites,
                  canonical_delta=delta,
                  conclusion='AL use matches target; real helpers return full EAX0/1 so the immediate JE decision is unchanged on normal returns; int ABI retained; no root exact credit')
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
