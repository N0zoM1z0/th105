#!/usr/bin/env python3
"""Trace Iku caller-stack payload identities under explicit ordinary-ABI contracts.

This is diagnostic address/lifetime evidence, never exact byte acceptance.
"""

from pathlib import Path
from collections import deque, defaultdict
import argparse, hashlib, importlib.util, json, sys, struct, tomllib

root = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(root / "scripts"))
import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG
from linked_pe import comparator
from typed_indirect_tails import receiver_tail_facts
from giant_owner_audit import decode


def load(name, path):
    s = importlib.util.spec_from_file_location(name, root / path)
    m = importlib.util.module_from_spec(s)
    sys.modules[name] = m
    s.loader.exec_module(m)
    return m


full = load("payload_full", "scripts/audit-iku-full-root.py")
coff = load("payload_coff", "scripts/compare-giant-action-switches.py")
c = comparator()
START = 0x620920
ROOT_SHA = "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea"
SURFACE_SHA = "8e948c42039b2fda3ef75fb7d40e120c8e128c44a2fd002412913911cf4d4dd6"
BELOW_SHA = "c2ee1b68bc5f44631a3cb5ec0538eae7a7280d08036bc4cf15ebaae9fd74fc12"
# Stack purge bytes from the established genuine dependency interfaces. Cdecl
# calls have zero implicit purge; the caller's ADD/POP remains in the graph.
# Receiver inference independently qualifies each virtual call/slot below.
purge = {
    0x406330: 0,
    0x478DF0: 4,
    0x46BF30: 8,
    0x4351C0: 0,
    0x473F90: 0,
    0x406540: 0,
    0x45B250: 0,
    0x45C030: 4,
    0x4359F0: 4,
    0x45DEB0: 12,
    0x435240: 20,
    0x478E60: 0,
    0x45D110: 4,
    0x5F9310: 0,
    0x435DC0: 0,
    0x4063D0: 0,
    0x406360: 0,
    0x4066B0: 0,
    0x45F560: 8,
    0x435110: 0,
    0x473DD0: 0,
    0x4067D0: 0,
    0x434E10: 8,
    0x476AB0: 8,
    0x476AD0: 8,
    0x476AF0: 8,
    0x465190: 28,
    0x435D60: 0,
    0x478EE0: 4,
    0x4740C0: 0,
    0x45AF40: 0,
    0x68A1A0: 0,
}


def get_code(path=None):
    if path is None:
        switches = {
            table: list(struct.unpack("<" + "I" * n, c.target_bytes(table, n * 4)))
            for table, n in ((0x62EFC0, 33), (0x62F128, 42), (0x62F2C8, 35))
        }
        code = c.target_bytes(START, 59038)
        if hashlib.sha256(code).hexdigest() != ROOT_SHA:
            raise ValueError("Iku root differs")
        return code, switches
    obj = coff.CoffObject(
        path,
        symbol_base="?dispatch_action_state_vslot28@IkuActionStateView@th105@@QAEXXZ",
    )
    unit = full.load_manifest()["units"]["gpt-web-iku-action-state"]["functions"][0]
    calls = {a: int(b, 0) for a, b in (x.split("=", 1) for x in unit["rel32_targets"])}
    data = dict(x.split("=", 1) for x in unit["dir32_targets"])
    code = c.coff_symbol_bytes(
        path,
        unit["symbol_base"],
        START,
        len(obj.text),
        calls,
        c.known_data_targets(),
        data,
    )
    config = load("payload_mapper", "scripts/map-giant-action-switches.py").select_root(
        tomllib.loads((root / "config/giant-action-switches.toml").read_text()),
        "iku-vslot28",
    )
    tables = coff.candidate_region_tables(obj, config)
    switches = {
        START + t["destination_table_offset"]: [START + d for d in t["groups"]]
        for t in tables
    }
    # Full CFG audit independently isolates callable from adjacent alignment/data.
    size = full.candidate_audit(c, path)["callable_span_bytes"]
    return code[:size], switches


def reg(name):
    for full, parts in {
        "eax": ("eax", "ax", "al", "ah"),
        "ebx": ("ebx", "bx", "bl", "bh"),
        "ecx": ("ecx", "cx", "cl", "ch"),
        "edx": ("edx", "dx", "dl", "dh"),
        "esi": ("esi", "si"),
        "edi": ("edi", "di"),
        "ebp": ("ebp", "bp"),
        "esp": ("esp", "sp"),
    }.items():
        if name in parts:
            return full
    return name


def merge_value(a, b):
    if a is None or b is None:
        return None
    u = a | b
    return u if len(u) <= 8 else None


def audit(code, switches, cleanup_contract=None, *, action_entries=None):
    cleanup_contract = purge if cleanup_contract is None else cleanup_contract
    rows = {r.address: r for r in decode(code, START)}
    if code[:8] != bytes.fromhex("558bec83e4f881ec"):
        raise ValueError("unsupported aligned root prologue")
    frame = rows[START + 6].operands[1].imm
    home = -frame - 16
    flow = receiver_tail_facts(
        code, START, switches, include_calls=True, allow_slot_unions=True
    )
    virtual = {}
    for site in flow["register_indirect_calls"]:
        slots = site["possible_vtable_slots"]
        if (
            not site["ecx_is_entry_receiver"]
            or not slots
            or not set(slots) <= {8, 12, 20, 28}
        ):
            raise ValueError("unqualified virtual call")
        widths = {0 if slot == 20 else 4 for slot in slots}
        if len(widths) != 1:
            raise ValueError("incompatible virtual-call stack purges")
        virtual[site["address"]] = next(iter(widths))

    def val(kind, number):
        return frozenset(((kind, number),))

    # SP is relative to the aligned prologue stack pointer. No control-flow or
    # register allocation normalization is applied to the actual comparisons.
    labels = defaultdict(set)
    for action, address in (action_entries or {}).items():
        if action is None or not isinstance(action, int) or address not in rows:
            raise ValueError("unqualified action entry for payload partition")
        labels[address].add(action)
    # Labels are assigned on the first action entry reached from the real
    # prologue. They never reset when that action enters another arm's tail.
    states = {(START, action): (0, {}, {}) for action in labels.get(START, {None})}
    queue = deque(states)
    queued = set(states)
    stack_at = {START: 0}
    visits = 0
    spawn = defaultdict(set)
    unknown = set()
    used = defaultdict(set)
    root_ends = set()
    action_spawn = {}
    while queue:
        key = queue.popleft()
        queued.remove(key)
        pc, action = key
        sp, regs, mem = states[key]
        regs = regs.copy()
        mem = mem.copy()
        row = rows[pc]
        visits += 1
        args = row.operands
        name = row.mnemonic
        edges = [pc + row.size]

        def memory(op):
            if op.type != X86_OP_MEM or op.mem.index:
                return None
            base = row.reg_name(op.mem.base)
            if base == "esp":
                return sp + op.mem.disp
            known = regs.get(reg(base))
            if known and len(known) == 1:
                k, v = next(iter(known))
                if k == "S":
                    return v + op.mem.disp
            return None

        def read(op):
            if op.type == X86_OP_IMM:
                return val("C", op.imm)
            if op.type == X86_OP_REG:
                n = row.reg_name(op.reg)
                if n == "esp":
                    return val("S", sp)
                return regs.get(reg(n)) if n.startswith("e") else None
            key = memory(op)
            return mem.get(key) if key is not None and op.size == 4 else None

        def store(key, width, value):
            for old in list(mem):
                if old < key + width and key < old + 4:
                    mem.pop(old)
            if value is not None and (key < home or any(k == "S" for k, n in value)):
                mem[key] = value

        written = {reg(row.reg_name(r)) for r in row.regs_access()[1]}
        if name == "push":
            value = read(args[0])
            sp -= 4
            store(sp, 4, value)
            written.discard("esp")
        elif name == "pop":
            value = mem.get(sp)
            mem.pop(sp, None)
            sp += 4
            if args[0].type == X86_OP_REG:
                regs[reg(row.reg_name(args[0].reg))] = value
                written.discard(reg(row.reg_name(args[0].reg)))
            written.discard("esp")
        elif (
            name == "and"
            and args[0].type == X86_OP_REG
            and row.reg_name(args[0].reg) == "esp"
        ):
            if pc != START + 3:
                raise ValueError("unexpected stack alignment")
            sp = 0
            mem = {}
            written.discard("esp")
        elif (
            name in ("sub", "add")
            and args[0].type == X86_OP_REG
            and row.reg_name(args[0].reg) == "esp"
        ):
            if args[1].type != X86_OP_IMM:
                raise ValueError("dynamic stack adjustment")
            sp += (1 if name == "add" else -1) * args[1].imm
            written.discard("esp")
            mem = {k: v for k, v in mem.items() if k >= sp}
        elif (
            name == "mov"
            and args[0].type == X86_OP_REG
            and row.reg_name(args[0].reg) == "esp"
        ):
            # Reviewed root epilogues restore the enclosing frame and immediately RET.
            after = rows.get(pc + row.size)
            if (
                args[1].type != X86_OP_REG
                or row.reg_name(args[1].reg) != "ebp"
                or after.mnemonic != "pop"
                or rows[after.address + after.size].mnemonic != "ret"
            ):
                raise ValueError("unqualified frame restore")
            if sp != -frame:
                raise ValueError(f"epilogue stack differs at {pc:x}: {sp} != {-frame}")
            root_ends.add(pc)
            continue
        elif name in ("mov", "lea") and args[0].type == X86_OP_REG:
            target = reg(row.reg_name(args[0].reg))
            value = (
                read(args[1])
                if name == "mov"
                else (
                    val("S", memory(args[1])) if memory(args[1]) is not None else None
                )
            )
            regs[target] = value
            written.discard(target)
        elif (
            name == "xor"
            and args[0].type == args[1].type == X86_OP_REG
            and args[0].reg == args[1].reg
        ):
            target = reg(row.reg_name(args[0].reg))
            regs[target] = val("C", 0)
            written.discard(target)
        elif (
            name in ("add", "sub")
            and args[0].type == X86_OP_REG
            and args[1].type == X86_OP_IMM
        ):
            target = reg(row.reg_name(args[0].reg))
            old = regs.get(target)
            if old:
                regs[target] = frozenset(
                    (k, n + (1 if name == "add" else -1) * args[1].imm) for k, n in old
                )
                written.discard(target)
        for op in args:
            if op.type == X86_OP_MEM and op.access & capstone.CS_AC_WRITE:
                key = memory(op)
                if key is not None:
                    store(
                        key,
                        op.size,
                        read(args[1])
                        if name == "mov"
                        and len(args) == 2
                        and args[0].type == X86_OP_MEM
                        else None,
                    )
        if name == "call":
            if args[0].type == X86_OP_IMM:
                destination = args[0].imm
                if destination not in cleanup_contract:
                    raise ValueError(f"unknown callee {destination:x}")
                cleanup = cleanup_contract[destination]
                if destination == 0x465190:
                    pointer = mem.get(sp + 20)
                    partition = action_spawn.setdefault(
                        (action, pc), {"homes": set(), "can_be_null": False, "unknown": False}
                    )
                    if pointer is None:
                        unknown.add(pc)
                        partition["unknown"] = True
                    else:
                        for k, n in pointer:
                            if k == "S":
                                spawn[pc].add(n - home)
                                used[n - home].add(pc)
                                partition["homes"].add(n - home)
                            elif k == "C" and n == 0:
                                partition["can_be_null"] = True
                            elif not (k == "C" and n == 0):
                                unknown.add(pc)
                                partition["unknown"] = True
            else:
                cleanup = virtual[pc]
            sp += cleanup
            mem = {k: v for k, v in mem.items() if k >= sp}
            written |= {"eax", "ecx", "edx"}
            written.discard("esp")
        if "esp" in written:
            raise ValueError(f"unmodeled stack write at {pc:x}")
        for r in written:
            regs.pop(r, None)
        if row.group(capstone.CS_GRP_RET):
            continue
        if row.group(capstone.CS_GRP_JUMP):
            op = args[0]
            if op.type == X86_OP_IMM:
                edges = [op.imm] + ([] if name == "jmp" else edges)
            elif op.type == X86_OP_MEM and op.mem.disp in switches:
                edges = switches[op.mem.disp]
            else:
                raise ValueError("unknown jump")
        state = sp, regs, mem
        for edge in edges:
            if edge not in rows:
                raise ValueError(f"edge {edge:x} escapes callable")
            if edge in stack_at and stack_at[edge] != sp:
                raise ValueError(f"stack disagreement at {edge:x}: {stack_at[edge]}, {sp} from{pc:x}")
            stack_at[edge] = sp
            actions = labels.get(edge, {action}) if action is None else {action}
            for next_action in actions:
                key = edge, next_action
                if key not in states:
                    new = state
                else:
                    oldsp, oldregs, oldmem = states[key]
                    newregs = {
                        k: merge_value(oldregs.get(k), regs.get(k))
                        for k in oldregs.keys() | regs.keys()
                    }
                    newregs = {k: v for k, v in newregs.items() if v is not None}
                    newmem = {
                        k: merge_value(oldmem.get(k), mem.get(k))
                        for k in oldmem.keys() | mem.keys()
                    }
                    newmem = {k: v for k, v in newmem.items() if v is not None}
                    new = sp, newregs, newmem
                if new != states.get(key):
                    states[key] = new
                    if key not in queued:
                        queue.append(key)
                        queued.add(key)
    covered = {pc for pc, action in states}
    for pc in root_ends:
        pop = rows[pc + rows[pc].size]
        ret = rows[pop.address + pop.size]
        covered.update((pop.address, ret.address))
    unreachable = sorted(set(rows) - covered)
    for pc in unreachable:
        row = rows[pc]
        before = rows.get(pc - 2)
        if (
            row.bytes != bytes.fromhex("8d4900")
            or (pc + row.size) % 16
            or before is None
            or before.mnemonic != "jmp"
            or before.operands[0].type != X86_OP_IMM
            or before.operands[0].imm != pc + row.size
        ):
            raise ValueError(f"unreviewed unreachable instruction at {pc:x}")
    homes = sorted(used)
    contiguous = homes == list(range(32, frame + 16, 12)) and frame == 16 + 12 * len(
        homes
    )
    consumer_groups = {0x5F9310: [], 0x435DC0: []}
    for pc, row in rows.items():
        if (
            row.mnemonic == "call"
            and row.operands[0].type == X86_OP_IMM
            and row.operands[0].imm in consumer_groups
        ):
            after = rows[pc + row.size]
            consumer_groups[row.operands[0].imm].append(
                {"site": pc, "mnemonic": after.mnemonic, "operands": after.op_str}
            )
    consumers = consumer_groups[0x5F9310]
    below = consumer_groups[0x435DC0]
    return {
        "code_sha256": hashlib.sha256(code).hexdigest(),
        "frame": frame,
        "contiguous_12_byte_payload_cells": contiguous,
        "epilogues": len(root_ends),
        "unreachable_compiler_alignment": unreachable,
        "unreachable_alignment_bytes": sum(rows[pc].size for pc in unreachable),
        "surface_consumers": consumers,
        "surface_consumer_count": len(consumers),
        "all_surface_consumers_test_AL": bool(consumers)
        and all(
            r["mnemonic"] == "test" and r["operands"] == "al, al" for r in consumers
        ),
        "below_consumers": below,
        "below_consumer_count": len(below),
        "all_below_consumers_test_AL": bool(below)
        and all(r["mnemonic"] == "test" and r["operands"] == "al, al" for r in below),
        "reachable_before_epilogue_restore": len({pc for pc, action in states}),
        "dataflow_states": len(states),
        "partitioned_by_incoming_action": action_entries is not None,
        "updates": visits,
        "unknown_spawn_payload_sites": sorted(unknown),
        "payload_sites": {hex(k): sorted(v) for k, v in sorted(spawn.items())},
        "distinct_payload_homes": len(used),
        "home_sites": {
            str(k): [hex(p) for p in sorted(v)] for k, v in sorted(used.items())
        },
        "register_calls": len(virtual),
        "action_payload_sites": [
            {"action": action, "site": pc, "homes": sorted(info["homes"]),
             "can_be_null": info["can_be_null"], "unknown": info["unknown"]}
            for (action, pc), info in sorted(
                action_spawn.items(), key=lambda item: (-2 if item[0][0] is None else item[0][0], item[0][1])
            )
        ] if action_entries is not None else [],
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--object",
        type=Path,
        help="audit the configured void root in this real VC8 COFF object",
    )
    args = parser.parse_args()
    target_sha = c.verify_target()
    if hashlib.sha256(c.target_bytes(0x5F9310, 64)).hexdigest() != SURFACE_SHA:
        raise ValueError("surface predicate differs")
    if hashlib.sha256(c.target_bytes(0x435DC0, 42)).hexdigest() != BELOW_SHA:
        raise ValueError("below-surface predicate differs")
    code, switches = get_code()
    target = audit(code, switches)
    if (
        target["distinct_payload_homes"] != 84
        or not target["contiguous_12_byte_payload_cells"]
        or target["unknown_spawn_payload_sites"]
    ):
        raise ValueError("target payload identity facts differ")
    if (
        len(target["surface_consumers"]) != 41
        or not target["all_surface_consumers_test_AL"]
    ):
        raise ValueError("target surface consumers differ")
    if (
        target["below_consumer_count"] != 10
        or not target["all_below_consumers_test_AL"]
    ):
        raise ValueError("target below-surface consumers differ")
    report = {
        "schema": "th105-iku-payload-homes-v1",
        "target_sha256": target_sha,
        "script_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        "target": target,
        "surface_callee_sha256": SURFACE_SHA,
        "below_callee_sha256": BELOW_SHA,
        "scope": "Caller-stack provenance under the explicit direct cleanup contract, qualified entry-receiver vslots and ordinary callee saves. "
        "Addresses are relative to the stack after four saved GPRs. All normal epilogues and stack joins close. "
        "Not original variable names, arbitrary callee behavior, backend execution, partial or exact byte credit.",
    }
    if args.object:
        code, switches = get_code(args.object.resolve())
        report["candidate"] = audit(code, switches)
        report["object_sha256"] = hashlib.sha256(args.object.read_bytes()).hexdigest()
    print(json.dumps(report, indent=2))
