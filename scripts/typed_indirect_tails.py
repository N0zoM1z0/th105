"""Conservative receiver provenance for bounded x86 indirect tail exits.

This is an analysis aid, never a canonical byte comparator. CALL uses the
ordinary x86 callee-saved register contract; volatile registers lose provenance.
"""
from __future__ import annotations

from collections import deque

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP, CS_GRP_RET, CS_GRP_INT
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_GRP_BRANCH_RELATIVE


REGISTERS = ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp")
ALIASES = {
    alias: whole for whole, aliases in {
        "eax": ("eax", "ax", "ah", "al"), "ebx": ("ebx", "bx", "bh", "bl"),
        "ecx": ("ecx", "cx", "ch", "cl"), "edx": ("edx", "dx", "dh", "dl"),
        "esi": ("esi", "si"), "edi": ("edi", "di"), "ebp": ("ebp", "bp"),
    }.items() for alias in aliases
}


def receiver_tail_facts(code: bytes, address: int,
                        switches: dict[int, list[int]], *, include_calls=False,
                        allow_slot_unions=False) -> dict:
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    decoded = list(decoder.disasm(code, address))
    if not decoded or sum(i.size for i in decoded) != len(code):
        raise ValueError("incomplete bounded instruction decoding")
    instructions = {i.address: i for i in decoded}
    end = address + len(code)

    def register(instruction, number):
        return ALIASES.get(instruction.reg_name(number))

    def transfer(instruction, state):
        before = dict(zip(REGISTERS, state))
        after = dict(before)
        for written in instruction.regs_access()[1]:
            name = register(instruction, written)
            if name:
                after[name] = None
        operands = instruction.operands
        if (instruction.mnemonic in {"mov", "lea"} and len(operands) == 2
                and operands[0].type == X86_OP_REG and operands[0].size == 4):
            destination = register(instruction, operands[0].reg)
            source = operands[1]
            value = None
            if source.type == X86_OP_REG and source.size == 4 and instruction.mnemonic == "mov":
                value = before.get(register(instruction, source.reg))
            elif source.type == X86_OP_MEM and not source.mem.index and not source.mem.segment:
                base = before.get(register(instruction, source.mem.base))
                if instruction.mnemonic == "lea":
                    if base == "receiver" and source.mem.disp == 0:
                        value = "receiver"
                elif source.size == 4:
                    if base == "receiver" and source.mem.disp == 0:
                        value = "vtable(receiver)"
                    elif base == "vtable(receiver)" and source.mem.disp >= 0 and source.mem.disp % 4 == 0:
                        value = f"vslot:{source.mem.disp}"
            if destination:
                after[destination] = value
        if instruction.group(CS_GRP_CALL):
            for name in ("eax", "ecx", "edx"):
                after[name] = None
        return tuple(after[name] for name in REGISTERS)

    def successors(instruction):
        following = instruction.address + instruction.size
        branch = instruction.group(CS_GRP_JUMP) or instruction.mnemonic in {
            "loop", "loope", "loopne", "jcxz", "jecxz",
        }
        if instruction.group(X86_GRP_BRANCH_RELATIVE) and not (branch or instruction.group(CS_GRP_CALL)):
            raise ValueError("unsupported relative control flow")
        if instruction.group(CS_GRP_RET):
            return []
        if branch:
            operand = instruction.operands[0]
            if operand.type == X86_OP_IMM:
                destinations = [operand.imm]
                if instruction.mnemonic != "jmp":
                    destinations.append(following)
            elif (instruction.mnemonic == "jmp" and operand.type == X86_OP_MEM
                  and not operand.mem.base and operand.mem.index and operand.mem.scale == 4
                  and not operand.mem.segment and operand.mem.disp in switches):
                destinations = switches[operand.mem.disp]
            else:
                return []
        elif instruction.group(CS_GRP_INT) or instruction.mnemonic in {"int3", "ud2", "hlt"}:
            return []
        else:
            destinations = [following]
        for destination in destinations:
            if address <= destination < end and destination not in instructions:
                raise ValueError("edge enters the middle of an instruction")
        return [d for d in destinations if address <= d < end]

    def join(left, right):
        if left == right:
            return left
        if not allow_slot_unions:
            return None

        def slots(value):
            if isinstance(value, frozenset):
                return value
            if isinstance(value, str) and value.startswith("vslot:"):
                return frozenset((value,))
            return None

        first, second = slots(left), slots(right)
        # Unknown or non-method provenance never becomes a finite target set.
        return first | second if first is not None and second is not None else None

    initial = tuple("receiver" if name == "ecx" else None for name in REGISTERS)
    states = {address: initial}
    pending = deque([address])
    iterations = 0
    while pending:
        location = pending.popleft()
        iterations += 1
        if iterations > 100000:
            raise ValueError("receiver dataflow exceeded its bounded work limit")
        out = transfer(instructions[location], states[location])
        for destination in successors(instructions[location]):
            old = states.get(destination)
            merged = out if old is None else tuple(join(a, b) for a, b in zip(old, out))
            if old != merged:
                states[destination] = merged
                pending.append(destination)

    tails, calls = [], []
    for location, state in sorted(states.items()):
        instruction = instructions[location]
        if (instruction.mnemonic not in ({"jmp", "call"} if include_calls else {"jmp"})
                or instruction.operands[0].type != X86_OP_REG):
            continue
        values = dict(zip(REGISTERS, state))
        target_register = register(instruction, instruction.operands[0].reg)
        target = values.get(target_register)
        choices = target if isinstance(target, frozenset) else (target,)
        slots = sorted(int(value.split(":")[1]) for value in choices
                       if isinstance(value, str) and value.startswith("vslot:"))
        fact = {"address": location, "instruction": instruction.mnemonic + " " + instruction.op_str,
                "target_register": target_register, "slot_offset": slots[0] if len(slots) == 1 else None,
                "ecx_is_entry_receiver": values["ecx"] == "receiver",
                "register_state": {name: sorted(value) if isinstance(value, frozenset) else value
                                   for name, value in values.items()}}
        if include_calls or allow_slot_unions:
            fact["possible_vtable_slots"] = slots
        (calls if instruction.mnemonic == "call" else tails).append(fact)
    result = {"decoded_instructions": len(decoded), "reachable_instructions": len(states),
            "call_assumption": "ordinary x86 ABI preserves EBX/ESI/EDI/EBP; CALL kills EAX/ECX/EDX",
            "register_tail_exits": tails}
    if include_calls:
        result["register_indirect_calls"] = calls
    return result
