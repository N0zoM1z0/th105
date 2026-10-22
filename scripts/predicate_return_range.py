"""Conservative normal-return EAX range proof for small decoded x86 predicates."""
from collections import defaultdict
import hashlib
import capstone
from capstone import x86_const as x


def prove_boolean_eax(code, address, allowed_calls=()):
    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cs.detail = True
    rows = list(cs.disasm(code, address))
    assert sum(row.size for row in rows) == len(code), 'incomplete decoding'
    by = {row.address: row for row in rows}
    pending, seen = [(address, None)], set()
    returns, definitions, calls = defaultdict(set), {}, set()
    aliases = {x.X86_REG_EAX, x.X86_REG_AX, x.X86_REG_AL, x.X86_REG_AH}
    while pending:
        pc, eax = pending.pop()
        assert pc in by, 'unqualified control-flow exit'
        if (pc, eax) in seen:
            continue
        seen.add((pc, eax))
        row = by[pc]
        if row.group(capstone.CS_GRP_RET):
            assert eax in (0, 1), 'normal RET lacks a proven full-EAX Boolean value'
            returns[pc].add(eax)
            continue
        if row.group(capstone.CS_GRP_CALL):
            assert row.operands[0].type == x.X86_OP_IMM, 'indirect call'
            callee = row.operands[0].imm
            assert callee in allowed_calls, 'unqualified call'
            calls.add(callee)
            eax = None  # A call clobber does not define a Boolean result.
        elif (row.mnemonic == 'mov' and row.operands[0].type == x.X86_OP_REG
              and row.operands[0].reg == x.X86_REG_EAX
              and row.operands[1].type == x.X86_OP_IMM):
            eax = row.operands[1].imm & 0xFFFFFFFF
            definitions[pc] = eax
        elif (row.mnemonic == 'xor' and len(row.operands) == 2
              and all(op.type == x.X86_OP_REG and op.reg == x.X86_REG_EAX for op in row.operands)):
            eax = 0
            definitions[pc] = 0
        elif aliases.intersection(row.regs_access()[1]):
            eax = None  # In particular, AL/AX writes do not define the high bytes.
        if row.group(capstone.CS_GRP_JUMP):
            assert row.operands[0].type == x.X86_OP_IMM, 'indirect branch'
            pending.append((row.operands[0].imm, eax))
            if row.mnemonic == 'jmp':
                continue
        pending.append((pc + row.size, eax))
    assert returns and {pc for pc, _ in seen} == set(by), 'unreviewed or unreachable instructions'
    return dict(address=hex(address), size=len(code), sha256=hashlib.sha256(code).hexdigest(),
                instructions=len(rows), returns={hex(pc): sorted(values) for pc, values in returns.items()},
                definitions={hex(pc): value for pc, value in definitions.items()},
                normal_calls=[hex(pc) for pc in sorted(calls)],
                scope='all decoded normal-return paths; allowed calls clobber EAX; no termination or exception claim')
