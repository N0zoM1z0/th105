"""Bounded static selector facts for Reimu740, including indeterminate spills."""
from __future__ import annotations

import hashlib
import importlib.util
from pathlib import Path
import sys

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "?run_checked_action_dispatch@ReimuActionStatePreludeView@th105@@QAE_NXZ"
ADDRESS = 0x478FA0


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def stack_load(insn):
    if insn.mnemonic != "mov" or len(insn.operands) != 2:
        return None
    dest, source = insn.operands
    if (dest.type == x.X86_OP_REG and dest.size == 4 and source.type == x.X86_OP_MEM
            and source.size == 4 and source.mem.base == x.X86_REG_ESP and not source.mem.index):
        return dest.reg, source.mem.disp
    return None


def inspect(code, start, table_value):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, start))
    by_address = {i.address: i for i in instructions}
    triples = []
    for index in range(len(instructions)-2):
        three = instructions[index:index+3]
        values = [stack_load(i) for i in three]
        if (all(v is not None for v in values) and len({v[0] for v in values}) == 3
                and len({v[1] for v in values}) == 1):
            triples.append((three, values))
    if len(triples) != 1:
        raise ValueError("740 needs one unique three-register indeterminate spill read")
    triple, values = triples[0]
    fallback, slot = triple[0].address, values[0][1]
    join = triple[-1].address+triple[-1].size
    registers = [v[0] for v in values]
    first_join = [by_address.get(join)]
    for _ in range(2):
        prev = first_join[-1]
        first_join.append(by_address.get(prev.address+prev.size) if prev else None)
    if (any(i is None for i in first_join) or [i.mnemonic for i in first_join] != ["mov", "cdq", "idiv"]
            or first_join[0].operands[0].type != x.X86_OP_REG
            or first_join[0].operands[0].reg != x.X86_REG_EAX
            or first_join[0].operands[1].type != x.X86_OP_MEM
            or first_join[0].operands[1].size != 4
            or first_join[0].operands[1].mem.base != x.X86_REG_ESI
            or first_join[0].operands[1].mem.index
            or first_join[0].operands[1].mem.disp != 0x144
            or first_join[2].operands[0].type != x.X86_OP_REG
            or first_join[2].operands[0].reg != registers[0]):
        raise ValueError("spill divisor does not feed the common signed division")

    def dispatch(destination):
        branches = [i for i in instructions if i.mnemonic == "ja" and i.operands[0].type == x.X86_OP_IMM
                    and i.operands[0].imm == destination]
        if len(branches) != 1:
            raise ValueError("indeterminate spill lacks one out-of-range edge")
        branch = branches[0]
        before = next((i for i in instructions if i.address+i.size == branch.address), None)
        jump = by_address.get(branch.address+branch.size)
        if (before is None or before.mnemonic != "cmp" or before.operands[0].type != x.X86_OP_REG
                or before.operands[1].type != x.X86_OP_IMM or before.operands[1].imm != 3
                or jump is None or jump.mnemonic != "jmp" or jump.operands[0].type != x.X86_OP_MEM):
            raise ValueError("mode dispatch is not bounded unsigned0..3")
        operand = jump.operands[0]
        if (operand.mem.base or operand.mem.scale != 4 or operand.mem.index != before.operands[0].reg):
            raise ValueError("mode table index does not use the checked register")
        entries = table_value(jump)
        if any(entry not in by_address for entry in entries):
            raise ValueError("mode table leaves decoded code")
        return entries

    def constants(entry, wanted_join):
        registers = {}
        address = entry
        for _ in range(8):
            insn = by_address.get(address)
            if insn is None:
                break
            ops = insn.operands
            if insn.mnemonic == "jmp" and ops[0].type == x.X86_OP_IMM:
                if ops[0].imm != wanted_join:
                    break
                return registers
            if len(ops) != 2 or ops[0].type != x.X86_OP_REG or ops[0].size != 4:
                break
            if insn.mnemonic == "mov":
                value = ops[1].imm if ops[1].type == x.X86_OP_IMM else registers.get(ops[1].reg) if ops[1].type == x.X86_OP_REG else None
            elif (insn.mnemonic == "lea" and ops[1].type == x.X86_OP_MEM
                  and not ops[1].mem.index and ops[1].mem.base in registers):
                value = registers[ops[1].mem.base]+ops[1].mem.disp
            else:
                break
            if value is None:
                break
            registers[ops[0].reg] = value
            address += insn.size
        raise ValueError("mode constants lack a bounded unconditional join")

    entries = dispatch(fallback)
    first = [[constants(entry, join).get(reg) for reg in registers] for entry in entries]
    if first != [[10, 6, 80], [8, 8, 80], [6, 11, 80], [5, 14, 80]]:
        raise ValueError(f"740 cadence/limit/duration constants differ: {first}")
    candidates = []
    for insn in instructions:
        value = stack_load(insn)
        if insn.address <= triple[-1].address or value is None or value[1] != slot:
            continue
        following = by_address.get(insn.address+insn.size)
        if (following is not None and following.mnemonic == "cmp"
                and following.operands[0].type == x.X86_OP_MEM and following.operands[0].size == 4
                and following.operands[0].mem.base == x.X86_REG_ESI
                and not following.operands[0].mem.index and following.operands[0].mem.disp == 0x144
                and following.operands[1].type == x.X86_OP_REG and following.operands[1].reg == value[0]):
            candidates.append(insn)
    if len(candidates) != 1:
        raise ValueError("740 cutoff needs one read of the same indeterminate spill")
    second = candidates[0]
    cutoff_join = second.address+second.size
    cutoff_entries = dispatch(second.address)
    cutoff_register = stack_load(second)[0]
    cutoffs = [constants(entry, cutoff_join).get(cutoff_register) for entry in cutoff_entries]
    if cutoffs != [60, 60, 50, 30]:
        raise ValueError(f"740 cutoff constants differ: {cutoffs}")
    return {"indeterminate_slot": slot, "pending_reads": [fallback, second.address],
            "first_mode_entries": entries, "cadence_limit_duration": first,
            "second_mode_entries": cutoff_entries, "cutoffs": cutoffs}


def packet(path):
    canonical = load("reimu740_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = load("reimu740_coff", "compare-giant-action-switches.py")
    obj = mapper.CoffObject(path, symbol_base=SYMBOL)

    def target_table(jump):
        table = jump.operands[0].mem.disp
        return [int.from_bytes(canonical.target_bytes(table+4*i, 4), "little") for i in range(4)]

    def source_table(jump):
        table = obj.relocated_text_value(jump.address+jump.disp_offset)
        return [obj.relocated_text_value(table+4*i) for i in range(4)]

    target_body = canonical.target_bytes(0x48C720, 535)
    if hashlib.sha256(target_body).hexdigest() != "b32f66936277d7426273bcd6d178f52e227779396d40fb399a267077fa525d56":
        raise ValueError("740 target owner changed")
    wanted = inspect(target_body, 0x48C720, target_table)
    source = inspect(obj.text, 0, source_table)
    return {"schema": "th105-reimu740-mode-facts-v1", "target_sha256": target_sha,
            "object_sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "target": wanted, "source": source, "capstone_version": capstone.__version__,
            "support_sha256": {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__), ROOT / "scripts/compare-function.py", ROOT / "scripts/compare-giant-action-switches.py")},
            "scope": "bounded switch constants and indeterminate-spill read boundaries; "
                     "not initialized-value provenance, callback returns, faults or canonical-exact acceptance"}
