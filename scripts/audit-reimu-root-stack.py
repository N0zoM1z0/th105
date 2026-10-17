#!/usr/bin/env python3
"""Recover Reimu probe stack depths and request-buffer identities, without credit."""
from __future__ import annotations

from collections import Counter, defaultdict, deque
import csv
import hashlib
import json
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from reimu_740_mode_facts import load

ADDRESS, SIZE, SPAWN = 0x478FA0, 81550, 0x465190
VOLATILE = {x.X86_REG_EAX, x.X86_REG_ECX, x.X86_REG_EDX}
MATH_CALLS = {0x406360, 0x4063D0, 0x435D60}
ACTIONS = (400, 401, 404, 406, 525, 526, 545, 546, 669)


def require(condition, message):
    if not condition:
        raise ValueError(message)


def decode(code, address):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(code, address))
    require(sum(row.size for row in rows) == len(code), 'incomplete instruction decoding')
    return rows


def register_family(reg):
    for names in ((x.X86_REG_EAX, x.X86_REG_AX, x.X86_REG_AL, x.X86_REG_AH),
                  (x.X86_REG_EDX, x.X86_REG_DX, x.X86_REG_DL, x.X86_REG_DH),
                  (x.X86_REG_EBP, x.X86_REG_BP),
                  (x.X86_REG_ECX, x.X86_REG_CX, x.X86_REG_CL, x.X86_REG_CH),
                  (x.X86_REG_EBX, x.X86_REG_BX, x.X86_REG_BL, x.X86_REG_BH),
                  (x.X86_REG_ESI, x.X86_REG_SI), (x.X86_REG_EDI, x.X86_REG_DI)):
        if reg in names:
            return set(names)
    raise ValueError('unreviewed pointer register')


class StackGraph:
    def __init__(self, code, switches, return_pops, virtual_pops):
        self.rows = decode(code, ADDRESS)
        self.by = {row.address: row for row in self.rows}
        self.predecessors = defaultdict(set)
        self.successors = {}
        self.return_pops = return_pops
        for row in self.rows:
            if row.group(capstone.CS_GRP_RET):
                destinations = []
            elif row.group(capstone.CS_GRP_JUMP):
                op = row.operands[0]
                if op.type == x.X86_OP_IMM:
                    destinations = [op.imm]
                else:
                    require(row.mnemonic == 'jmp' and op.type == x.X86_OP_MEM
                            and op.mem.disp in switches, 'unqualified indirect edge')
                    destinations = list(switches[op.mem.disp])
                if row.mnemonic != 'jmp':
                    destinations.append(row.address + row.size)
            else:
                destinations = [row.address + row.size]
            self.successors[row.address] = set(destinations)
            for destination in destinations:
                self.predecessors[destination].add(row.address)
        self.reachable, pending = set(), [ADDRESS]
        while pending:
            address = pending.pop()
            if address in self.reachable:
                continue
            require(address in self.by, 'reachable edge escapes decoded code')
            self.reachable.add(address)
            pending.extend(self.successors[address])
        self.call_pops, self.virtual_definitions = {}, {}
        for row in self.rows:
            if row.mnemonic != 'call' or row.address not in self.reachable:
                continue
            op = row.operands[0]
            if op.type == x.X86_OP_IMM:
                require(op.imm in return_pops, 'unqualified direct-call cleanup')
                self.call_pops[row.address] = return_pops[op.imm]
            else:
                require(op.type == x.X86_OP_REG, 'unqualified indirect call')
                definitions = self.reaching_writes(row.address, op.reg)
                pops, slots = set(), {}
                for definition in definitions:
                    operands = definition.operands
                    require(definition.mnemonic == 'mov' and operands[0].reg == op.reg
                            and operands[0].size == 4 and operands[1].type == x.X86_OP_MEM,
                            'indirect target is not a full vtable-slot load')
                    mem = operands[1].mem
                    require(mem.base in (x.X86_REG_EAX, x.X86_REG_EDX)
                            and not mem.index and mem.disp in virtual_pops,
                            'unqualified virtual slot')
                    pops.add(virtual_pops[mem.disp])
                    slots[definition.address] = mem.disp
                require(len(pops) == 1, 'disagreeing indirect-call stack cleanup')
                self.call_pops[row.address] = next(iter(pops))
                self.virtual_definitions[row.address] = slots
        allocation = self.rows[3]
        require(allocation.address == ADDRESS + 6 and allocation.mnemonic == 'sub'
                and allocation.operands[0].reg == x.X86_REG_ESP
                and allocation.operands[1].type == x.X86_OP_IMM,
                'reviewed root stack prologue changed')
        self.frame = allocation.operands[1].imm
        self.depths = self.stack_depths()

    def reaching_writes(self, site, reg, context=None):
        context = self.reachable if context is None else context
        pending = list(self.predecessors[site] & context)
        require(pending, 'pointer reaches an unknown incoming register')
        seen, definitions = set(), {}
        family = register_family(reg)
        while pending:
            address = pending.pop()
            if address in seen:
                continue
            seen.add(address)
            row = self.by[address]
            if family & set(row.regs_access()[1]):
                definitions[address] = row
            elif row.mnemonic == 'call' and reg in VOLATILE:
                raise ValueError('caller-saved pointer provenance crosses a call')
            else:
                parents = self.predecessors[address] & context
                require(parents, 'pointer reaches an unknown incoming register')
                pending.extend(parents)
        require(definitions, 'pointer has no reaching definition')
        return list(definitions.values())

    def stack_depths(self):
        depths, pending = {ADDRESS: 0}, deque([ADDRESS])
        while pending:
            address = pending.popleft()
            row, before = self.by[address], depths[address]
            after = before
            operands = row.operands
            if row.mnemonic in ('push', 'pop'):
                after = None if before is None else before + (4 if row.mnemonic == 'pop' else -4)
            elif (row.mnemonic in ('add', 'sub') and operands[0].type == x.X86_OP_REG
                  and operands[0].reg == x.X86_REG_ESP):
                require(operands[1].type == x.X86_OP_IMM, 'nonconstant ESP adjustment')
                delta = operands[1].imm * (1 if row.mnemonic == 'add' else -1)
                after = None if before is None else before + delta
            elif (row.mnemonic == 'and' and operands[0].type == x.X86_OP_REG
                  and operands[0].reg == x.X86_REG_ESP):
                require(address == ADDRESS + 3 and operands[1].imm & 0xFFFFFFFF == 0xFFFFFFF8,
                        'unqualified stack alignment')
                after = 0
            elif (row.mnemonic == 'mov' and operands[0].type == x.X86_OP_REG
                  and operands[0].reg == x.X86_REG_ESP):
                require(operands[1].type == x.X86_OP_REG and operands[1].reg == x.X86_REG_EBP,
                        'unqualified ESP restoration')
                after = None
            elif row.mnemonic == 'lea' and operands[0].reg == x.X86_REG_ESP:
                mem = operands[1].mem
                require(mem.base == x.X86_REG_ESP and not mem.index, 'unqualified ESP LEA')
                after = None if before is None else before + mem.disp
            elif row.mnemonic == 'call':
                after = None if before is None else before + self.call_pops[address]
            elif not row.group(capstone.CS_GRP_RET):
                require(x.X86_REG_ESP not in row.regs_access()[1], 'unqualified ESP write')
            for destination in self.successors[address]:
                require(destination in self.by, 'reachable edge escapes decoded code')
                if destination in depths:
                    require(depths[destination] == after, 'inconsistent ESP at CFG merge')
                else:
                    depths[destination] = after
                    pending.append(destination)
        return depths

    def pointer_values(self, site, op, active=frozenset(), context=None):
        if op.type == x.X86_OP_IMM:
            require(op.imm == 0, 'nonzero immediate request pointer')
            return {('null', 0)}, set()
        require(op.type == x.X86_OP_REG and (site, op.reg) not in active,
                'unqualified or cyclic pointer definition')
        active = active | {(site, op.reg)}
        values, sites = set(), set()
        for row in self.reaching_writes(site, op.reg, context):
            operands = row.operands
            require(operands[0].type == x.X86_OP_REG and operands[0].reg == op.reg
                    and operands[0].size == 4, 'partial request-pointer write')
            sites.add(row.address)
            if row.mnemonic == 'lea' and operands[1].type == x.X86_OP_MEM:
                mem = operands[1].mem
                require(mem.base == x.X86_REG_ESP and not mem.index
                        and self.depths.get(row.address) is not None, 'nonstack request-pointer LEA')
                slot = self.depths[row.address] + mem.disp + self.frame + 16
                require(16 <= slot <= self.frame + 12, 'request buffer escapes local frame')
                values.add(('stack', slot))
            elif row.mnemonic == 'xor' and operands[1].type == x.X86_OP_REG and operands[1].reg == op.reg:
                values.add(('null', 0))
            elif row.mnemonic == 'mov':
                incoming, definitions = self.pointer_values(row.address, operands[1], active, context)
                values.update(incoming)
                sites.update(definitions)
            else:
                raise ValueError('unqualified request-pointer definition')
        return values, sites

    def reachable_from(self, entry):
        context, pending = set(), [entry]
        while pending:
            address = pending.pop()
            if address in context:
                continue
            require(address in self.reachable, 'action context escapes root CFG')
            context.add(address)
            pending.extend(self.successors[address])
        return context

    def argument_pushes(self, site, wanted, context):
        pending = list(self.predecessors[site] & context)
        seen, pushes = set(), {}
        while pending:
            address = pending.pop()
            if address in seen:
                continue
            seen.add(address)
            row = self.by[address]
            before = self.depths.get(address)
            require(before is not None, 'request-pointer push has unknown ESP')
            if row.mnemonic == 'push' and before - 4 == wanted:
                pushes[address] = row
                continue
            if row.mnemonic == 'call':
                require(row.operands[0].type == x.X86_OP_IMM
                        and row.operands[0].imm in MATH_CALLS and self.call_pops[address] == 0,
                        'request-pointer push crosses an unreviewed call')
            if row.mnemonic == 'add' and row.operands[0].type == x.X86_OP_REG and row.operands[0].reg == x.X86_REG_ESP:
                require(not before <= wanted < before + row.operands[1].imm,
                        'request pointer reaches a released stack slot')
            if row.mnemonic == 'pop':
                require(before != wanted, 'request pointer reaches a popped stack slot')
            for operand in row.operands:
                if (operand.type == x.X86_OP_MEM and operand.access & capstone.CS_AC_WRITE
                        and operand.mem.base == x.X86_REG_ESP and not operand.mem.index):
                    start = before + operand.mem.disp
                    require(not (start < wanted + 4 and wanted < start + operand.size),
                            'request pointer overwritten by an unqualified stack store')
            parents = self.predecessors[address] & context
            require(parents, 'request pointer reaches an unwritten incoming stack slot')
            pending.extend(parents)
        require(pushes, 'request-pointer push was not found')
        return list(pushes.values())

    def payloads(self, entry=None):
        context = self.reachable if entry is None else self.reachable_from(entry)
        requests = []
        for row in self.rows:
            if (row.address not in context or row.mnemonic != 'call'
                    or row.operands[0].type != x.X86_OP_IMM or row.operands[0].imm != SPAWN):
                continue
            require(self.depths.get(row.address) == -self.frame - 16 - 28,
                    'request call has an unexpected ESP depth')
            wanted = self.depths[row.address] + 20
            values, definitions = set(), set()
            pushes = self.argument_pushes(row.address, wanted, context)
            for push in pushes:
                incoming, sites = self.pointer_values(push.address, push.operands[0], context=context)
                values.update(incoming)
                definitions.update(sites)
            requests.append({'call': row.address, 'pushes': sorted(p.address for p in pushes),
                             'values': sorted(values), 'definitions': sorted(definitions)})
        return requests

    def report(self):
        last = max(self.by[a].address + self.by[a].size for a in self.depths)
        return {'frame': self.frame, 'reachable_instructions': len(self.depths),
                'last_reachable_end': last, 'bytes_after_reachable_end': ADDRESS + sum(r.size for r in self.rows) - last,
                'unreached': [{'address': r.address, 'bytes': bytes(r.bytes).hex(),
                              'instruction': r.mnemonic + ' ' + r.op_str}
                             for r in self.rows if r.address not in self.depths],
                'virtual_call_definitions': self.virtual_definitions, 'payloads': self.payloads()}


def audit(path):
    relocations = load('reimu_stack_relocations', 'audit-reimu-root-relocations.py')
    qualification = relocations.audit(path)
    canonical = relocations.load('reimu_stack_canonical', 'compare-function.py')
    mapper = relocations.load('reimu_stack_mapper', 'compare-giant-action-switches.py')
    obj = mapper.CoffObject(path, symbol_base=relocations.SYMBOL)
    bindings = relocations.load_bindings(relocations.DEFAULT_BINDINGS)
    data = dict(canonical.known_data_targets())
    for table in ('root_literals', 'pool_literals'):
        for bits, address in bindings[table].items():
            data['__real@'+bits] = (int(address, 0), bytes.fromhex(bits)[::-1], frozenset({0}), 'literal')
    replay = canonical.coff_symbol_bytes(path, relocations.SYMBOL, ADDRESS, len(obj.text),
                                        {k: int(v, 0) for k, v in bindings['rel32'].items()}, data, {})
    code = {'target': canonical.target_bytes(ADDRESS, SIZE),
            'source': replay[:qualification['source_metadata_start']]}
    root = mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT/'config/giant-action-switches.toml').read_text()), 'reimu-vslot28')
    switches = {'target': {}, 'source': {}}
    for region in (*root['regions'], *root['auxiliary_switches']):
        address = int(region['destination_table'], 0)
        count = region.get('destination_count', len(region.get('destinations', [])))
        switches['target'][address] = struct.unpack('<'+'I'*count, canonical.target_bytes(address, 4*count))
    for row in decode(code['source'], ADDRESS):
        if row.mnemonic == 'jmp' and row.operands[0].type == x.X86_OP_MEM:
            address, destinations = row.operands[0].mem.disp, []
            offset = address - ADDRESS
            while offset in obj.relocations:
                symbol, kind = obj.relocations[offset]
                if kind != 6 or symbol.section_number != obj.text_section_number:
                    break
                destinations.append(struct.unpack_from('<I', replay, offset)[0])
                offset += 4
            require(destinations, 'empty source switch table')
            switches['source'][address] = destinations
    require(all(len(tables) == 11 for tables in switches.values()), 'switch count changed')
    with (ROOT/'config/functions.csv').open() as stream:
        ledger = {int(row['address'], 0): row for row in csv.DictReader(stream)}
    virtual_targets = {slot: struct.unpack('<I', canonical.target_bytes(0x6C412C+slot, 4))[0]
                       for slot in (8, 12, 20)}
    evidence, pops = {}, {}
    for address in sorted(set(int(v, 0) for v in bindings['rel32'].values()) | set(virtual_targets.values())):
        body = canonical.target_bytes(address, int(ledger[address]['size']))
        returns = [r for r in decode(body, address) if r.mnemonic == 'ret']
        amounts = {r.operands[0].imm if r.operands else 0 for r in returns}
        require(len(amounts) == 1, 'callee decoded RET cleanup is absent or inconsistent')
        pops[address] = next(iter(amounts))
        evidence[hex(address)] = {'candidate_size': len(body), 'body_sha256': hashlib.sha256(body).hexdigest(),
                                  'ret_sites': [r.address for r in returns], 'pop': pops[address]}
    virtual_pops = {slot: pops[address] for slot, address in virtual_targets.items()}
    require(virtual_pops == {8: 4, 12: 4, 20: 0}, 'reviewed member cleanup changed')
    graphs = {name: StackGraph(body, switches[name], pops, virtual_pops) for name, body in code.items()}
    reports = {name: graph.report() for name, graph in graphs.items()}
    tm = mapper.load_target_mapper()
    target_map = tm.map_root(tm.PeImage(ROOT/'resources/th105.exe'), tm.load_function_rows(ROOT/'config/functions.csv'), root)
    mapping = mapper.compare_maps(target_map, mapper.build_candidate_map(obj, root))
    contracts = []
    for action in ACTIONS:
        row = next(r for r in mapping['rows'] if r['cases'] == [action])
        groups = {}
        for name in ('target', 'source'):
            start = row['target_offset'] if name == 'target' else row['candidate_offsets'][0]
            requests = graphs[name].payloads(ADDRESS+start)
            identities, partition = [], []
            for request in requests:
                value = request['values']
                if value not in identities:
                    identities.append(value)
                partition.append(identities.index(value))
            groups[name] = {'requests': requests, 'partition': partition}
        contracts.append({'action': action, **groups,
                          'same_partition': groups['target']['partition'] == groups['source']['partition']})
    return {'schema': 'th105-reimu-root-stack-v1', 'target_sha256': qualification['target_sha256'],
            'object_sha256': qualification['object_sha256'], 'graphs': reports,
            'callee_cleanup_observations': evidence, 'buffer_contracts': contracts,
            'buffer_partition_mismatches': sum(not c['same_partition'] for c in contracts),
            'first_mismatch': qualification['first_mismatch'],
            'support_sha256': {**qualification['support_sha256'],
                              str(Path(__file__).relative_to(ROOT)): relocations.sha(Path(__file__)),
                              'scripts/reimu_740_mode_facts.py': relocations.sha(ROOT/'scripts/reimu_740_mode_facts.py')},
            'abi_assumptions': ['ordinary callees preserve EBX/ESI/EDI/EBP; calls clobber EAX/ECX/EDX',
                                'decoded RET consensus in tracked callee spans and reviewed virtual slots supplies cleanup',
                                'math calls between a pointer push and its request preserve the higher caller argument slot'],
            'scope': 'probe-only CFG/ESP and nine action-entry request-buffer partitions, including shared tails; '
                     'no returned-world semantics, arbitrary-stack, canonical exact or partial-byte credit'}


def native_audit(path):
    """Reuse only affected old-family inputs and their target-branch assertions."""
    oracle = load('reimu_stack_void_oracle', 'audit-reimu-void-root.py')
    base = next(oracle.cases(True))
    families, inputs, support = {}, [], []
    for filename in ('audit-reimu-mid-projectile-actions.py', 'audit-reimu-mid-520-actions.py',
                     'audit-reimu-mid-540-actions.py', 'audit-reimu-high-late-actions.py'):
        family = load('reimu_stack_family_'+str(len(families)), filename)
        families[filename] = family
        support.append(ROOT/'scripts'/filename)
        inputs.extend({**base, **case, 'buffer_family': filename} for case in family.cases()
                      if case['action'] in ACTIONS and case['cohort'] != 'integration')
    counts = Counter(case['action'] for case in inputs)
    require(counts == {400: 576, 401: 576, 404: 580, 406: 580, 525: 296, 526: 296,
                       545: 1366, 546: 1366, 669: 1086}, 'affected native input matrix changed')

    class VoidProbe(oracle.previous.Probe):
        candidate_return_kind = 'void'
        handled_action_max = 32767

    def cases(smoke=False):
        require(not smoke, 'affected-family adapter has no smoke subset')
        yield from inputs

    def check(case, result, sites):
        families[case['buffer_family']].check_target_case(case, result, sites)

    contract = SimpleNamespace(**vars(oracle))
    contract.Probe, contract.cases, contract.check_target_case = VoidProbe, cases, check
    contract.COHORT_COUNTS = dict(Counter(case['cohort'] for case in inputs))
    contract.SUPPORT_PATHS = (*oracle.SUPPORT_PATHS, Path(__file__), *support)
    contract.SCHEMA = 'th105-reimu-root-buffer-native-v1'
    contract.SCOPE = ('affected nine-action matrix, real helpers/RET and first world-request arguments; '
                      'no returning-world, complete-loop, arbitrary-stack or canonical-exact claim')
    result = oracle.low.audit(path, contract=contract)
    result['action_counts'] = dict(counts)
    return result


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('--require-partitions', action='store_true')
    parser.add_argument('--native', action='store_true', help='also replay the6722 affected-family inputs')
    args = parser.parse_args()
    try:
        result = audit(args.object)
        if args.native:
            result['native'] = native_audit(args.object)
    except (KeyError, OSError, TypeError, ValueError) as error:
        parser.exit(2, f'Reimu stack audit failed: {error}\n')
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if ((args.require_partitions and result['buffer_partition_mismatches'])
                          or result.get('native', {}).get('mismatch_count')) else 0)
