#!/usr/bin/env python3
"""Static finite-angle/counter contracts for the eight Reimu710/711 loops.

Expressions carry an unvalued atan2 result. No game callback is executed or
supplied a concrete result; this is not whole-volley/native/exact acceptance.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "?run_checked_action_dispatch@ReimuActionStatePreludeView@th105@@QAE_NXZ"
I, A, U = ("i",), ("angle32",), ("unknown",)
CONFIG = {710: ((3, 120, 0), (4, 90, 0), (6, 60, 0), (8, 45, 0)),
          711: ((3, 60, 60), (4, 60, 90), (5, 45, 90), (6, 36, 90))}


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def const(value):
    return ("c", struct.pack(">d", float(value)).hex())


def neg(value):
    if value == U:
        return U
    if value[0] == "neg":
        return value[1]
    if value[0] == "c":
        return ("c", f"{int(value[1], 16) ^ (1 << 63):016x}")
    return ("neg", value)


def expr(op, left, right):
    if U in (left, right):
        return U
    # Finite round-to-nearest sign symmetry, without addition reassociation.
    if op == "sub":
        if left[0] == "neg":
            return neg(expr("add", left[1], right))
        return expr("add", left, neg(right))
    if op in ("add", "mul"):
        left, right = sorted((left, right), key=repr)
    return (op, left, right)


def exact_integer_counter(value):
    # I is an integer in0..8. Only the observed I+1 and I*integer-step
    # intermediates are exact at both32 and64-bit stores.
    if value == I:
        return True
    if value[0] == "c":
        number = struct.unpack(">d", bytes.fromhex(value[1]))[0]
        return number.is_integer() and abs(number) <= 120
    if value[0] in ("add", "mul"):
        parts = value[1:]
        other = parts[1] if parts[0] == I else parts[0] if parts[1] == I else None
        if other is None or other[0] != "c":
            return False
        number = struct.unpack(">d", bytes.fromhex(other[1]))[0]
        return number.is_integer() and (number == 1 if value[0] == "add" else 0 < number <= 120)
    return False


def rounded(value, width):
    if value == U or exact_integer_counter(value):
        return value
    if value[0] == "f32" and width in (4, 8):
        return value
    return ("f32" if width == 4 else "f64", value)


class Flow:
    def __init__(self, view):
        self.view, self.sp = view, 0
        self.regs = {x.X86_REG_ESI: ("p", "self", 0)}
        self.mem, self.fp, self.reads = {}, [], Counter()
        self.calls, self.requests, self.comparison = [], [], None

    def reg(self, number):
        return ("p", "stack", self.sp) if number == x.X86_REG_ESP else self.regs.get(number)

    def address(self, operand):
        base = self.reg(operand.mem.base)
        if operand.mem.index or not isinstance(base, tuple) or base[0] != "p":
            return None
        return base[1], base[2]+operand.mem.disp

    def put(self, offset, size, value):
        for old, (width, _) in list(self.mem.items()):
            if old < offset+size and offset < old+width:
                del self.mem[old]
        self.mem[offset] = (size, value)

    def get(self, operand):
        if operand.type == x.X86_OP_IMM:
            return operand.imm & 0xFFFFFFFF
        if operand.type == x.X86_OP_REG:
            return self.reg(operand.reg)
        if operand.type == x.X86_OP_MEM:
            address = self.address(operand)
            if address == ("self", 0x170) and operand.size == 4:
                return ("p", "peer", 0)
            if address and address[0] == "stack":
                entry = self.mem.get(address[1])
                return entry[1] if entry and entry[0] == operand.size else None
        return None

    def write(self, operand, value):
        if operand.type == x.X86_OP_REG:
            if operand.reg == x.X86_REG_ESP:
                if not isinstance(value, tuple) or value[:2] != ("p", "stack"):
                    raise ValueError("unknown stack pointer")
                self.sp = value[2]
            else:
                self.regs[operand.reg] = value
        elif operand.type == x.X86_OP_MEM:
            address = self.address(operand)
            if address and address[0] == "stack":
                self.put(address[1], operand.size, value)

    def fp_index(self, operand):
        if operand.type != x.X86_OP_REG or not x.X86_REG_ST0 <= operand.reg <= x.X86_REG_ST7:
            raise ValueError("unsupported x87 register")
        return operand.reg-x.X86_REG_ST0

    def fget(self, insn, operand):
        if operand.type == x.X86_OP_REG:
            index = self.fp_index(operand)
            return self.fp[index] if index < len(self.fp) else U
        value = self.get(operand)
        if isinstance(value, tuple) and value[0] == "f":
            return value[1]
        if isinstance(value, int) and operand.size == 4:
            return const(struct.unpack("<f", struct.pack("<I", value))[0])
        raw = self.view.literal(insn, operand)
        return const(struct.unpack("<f" if operand.size == 4 else "<d", raw)[0]) if raw else U

    def call(self, insn):
        name = self.view.call_name(insn)
        if self.fp:
            raise ValueError(f"unproved live x87 values at {name} call")
        self.calls.append(name)
        if name == "spawn":
            args = [self.mem.get(self.sp+4*i, (4, None))[1] for i in range(7)]
            pointer = args[5]
            if not isinstance(pointer, tuple) or pointer[:2] != ("p", "stack"):
                raise ValueError("request pointer is not locally established")
            payload = [self.mem.get(pointer[2]+4*i, (4, None))[1] for i in range(3)]
            self.requests.append({"object": args[0], "count": args[6], "arg5": args[4], "buffer": pointer[2], "payload": payload})
            for index in range(3):
                self.put(pointer[2]+4*index, 4, None)
            self.sp += 28  # Observed RET1C ABI; no concrete return value.
        elif name in ("atan2", "sine", "cosine"):
            for index in range(2 if name == "atan2" else 1):
                self.put(self.sp+4*index, 4, None)
            self.fp.append(A if name == "atan2" else U)
        else:
            raise ValueError(f"unsupported loop call {name}")
        for reg in (x.X86_REG_EAX, x.X86_REG_ECX, x.X86_REG_EDX):
            self.regs[reg] = None

    def step(self, insn):
        name, ops = insn.mnemonic, insn.operands
        for op in ops:
            if op.type == x.X86_OP_MEM and op.access & capstone.CS_AC_READ and name != "lea":
                address = self.address(op)
                if address and address[0] in ("self", "peer"):
                    self.reads[(address[0], address[1], op.size, name)] += 1
        if name == "call":
            self.call(insn)
        elif name == "push":
            value = self.get(ops[0])
            self.sp -= 4
            self.put(self.sp, 4, value)
        elif name == "mov":
            self.write(ops[0], self.get(ops[1]))
        elif name in ("movsx", "movzx"):
            self.write(ops[0], None)
        elif name == "lea":
            address = self.address(ops[1])
            self.write(ops[0], ("p", *address) if address else None)
        elif name in ("add", "sub") and ops[0].type == x.X86_OP_REG and ops[0].reg == x.X86_REG_ESP:
            if ops[1].type != x.X86_OP_IMM:
                raise ValueError("nonconstant stack adjustment")
            self.sp += ops[1].imm if name == "add" else -ops[1].imm
        elif name in ("fldz", "fld1"):
            self.fp.insert(0, const(0 if name == "fldz" else 1))
        elif name == "fld":
            self.fp.insert(0, self.fget(insn, ops[0]))
        elif name == "fild":
            self.fp.insert(0, U)
        elif name in ("fst", "fstp"):
            if not self.fp:
                raise ValueError("unproved x87 store input")
            value = self.fp[0]
            if ops[0].type == x.X86_OP_REG:
                self.fp[self.fp_index(ops[0])] = value
            else:
                self.write(ops[0], ("f", rounded(value, ops[0].size)))
            if name == "fstp":
                self.fp.pop(0)
        elif name == "fchs":
            self.fp[0] = neg(self.fp[0])
        elif name == "fxch":
            index = self.fp_index(ops[0]) if ops else 1
            self.fp[0], self.fp[index] = self.fp[index], self.fp[0]
        elif name.startswith(("fadd", "fsub", "fmul", "fdiv")):
            operation = "add" if name.startswith("fadd") else "sub" if name.startswith("fsub") else "mul" if name.startswith("fmul") else "div"
            pop = name.endswith("p")
            if len(ops) == 2:
                dest, right = self.fp_index(ops[0]), self.fget(insn, ops[1])
            elif pop:
                dest, right = self.fp_index(ops[0]) if ops else 1, self.fp[0]
            else:
                dest, right = 0, self.fget(insn, ops[0])
            left = self.fp[dest]
            if "subr" in name or "divr" in name:
                left, right = right, left
            self.fp[dest] = expr(operation, left, right)
            if pop:
                self.fp.pop(0)
        elif name in ("fcom", "fcomp"):
            self.comparison = (self.fp[0], self.fget(insn, ops[0]))
            if name == "fcomp":
                self.fp.pop(0)
        elif name == "fnstsw":
            self.regs[x.X86_REG_EAX] = None
        elif name.startswith("f"):
            raise ValueError(f"unsupported x87 operation {name}")
        elif name.startswith("j") or name in ("cmp", "test", "nop"):
            pass
        else:
            for op in ops:
                if op.access & capstone.CS_AC_WRITE:
                    self.write(op, None)


class View:
    def __init__(self, canonical, obj=None):
        self.canonical, self.obj = canonical, obj

    def call_name(self, insn):
        names = {0x406540: "atan2", 0x406360: "sine", 0x4063D0: "cosine", 0x465190: "spawn"}
        if self.obj is None:
            return names.get(insn.operands[0].imm)
        pair = self.obj.relocations.get(insn.address+1)
        if not pair or pair[1] != 20:
            return None
        prefixes = {"atan2_degrees": "atan2", "lookup_orientation_sine_quantized_abs": "sine",
                    "lookup_orientation_cosine_quantized_abs": "cosine", "spawn_owned_object_via_manager": "spawn"}
        return next((name for prefix, name in prefixes.items() if pair[0].name.startswith("?"+prefix+"@")), None)

    def literal(self, insn, operand):
        if operand.type != x.X86_OP_MEM or operand.mem.base or operand.mem.index:
            return None
        if self.obj is None:
            return self.canonical.target_bytes(operand.mem.disp, operand.size)
        pair = self.obj.relocations.get(insn.address+insn.disp_offset)
        if not pair or pair[1] != 6 or not pair[0].name.startswith("__real@"):
            return None
        symbol = pair[0]
        section = self.obj.sections[symbol.section_number-1]
        offset = section.raw_offset+symbol.value+operand.mem.disp
        raw = self.obj.data[offset:offset+operand.size]
        if raw != bytes.fromhex(symbol.name.removeprefix("__real@"))[::-1]:
            raise ValueError("COFF numeric literal/symbol mismatch")
        return raw


def inspect(view, code, start, action):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, start))
    if sum(i.size for i in instructions) != len(code):
        raise ValueError("owner bytes did not decode completely")
    dispatches = [i for i in instructions if i.mnemonic == "jmp" and i.operands[0].type == x.X86_OP_MEM]
    if len(dispatches) != 1:
        raise ValueError(f"{action} needs one independent four-mode switch")
    jump = dispatches[0]
    table = jump.operands[0].mem.disp if view.obj is None else view.obj.relocated_text_value(jump.address+jump.disp_offset)
    entries = ([int.from_bytes(view.canonical.target_bytes(table+4*k, 4), "little") for k in range(4)]
               if view.obj is None else [view.obj.relocated_text_value(table+4*k) for k in range(4)])
    if len(set(entries)) != 4 or any(not start <= entry < start+len(code) for entry in entries):
        raise ValueError("mode table entries escape their owner or share a loop")
    rows = []
    for mode, entry in enumerate(entries):
        end = min((other for other in entries if other > entry), default=start+len(code))
        edges = [i for i in instructions if entry <= i.address < end and i.mnemonic.startswith("j") and i.mnemonic != "jmp"
                 and i.operands[0].type == x.X86_OP_IMM and entry <= i.operands[0].imm < i.address]
        if len(edges) != 1:
            raise ValueError("mode needs one bounded natural loop backedge")
        edge, flow = edges[0], Flow(view)
        header = edge.operands[0].imm
        for insn in instructions:
            if entry <= insn.address < header:
                flow.step(insn)
        counters = [offset for offset, (size, value) in flow.mem.items() if size == 4 and value == ("f", const(0))]
        if len(counters) != 1 or flow.fp not in ([], [const(0)]):
            raise ValueError("unproved loop-counter initialization")
        counter = counters[0]
        carried = bool(flow.fp)
        flow.mem[counter] = (4, ("f", I))
        flow.fp = [I] if carried else []
        body = [i for i in instructions if header <= i.address <= edge.address]
        if any(i.mnemonic.startswith("j") for i in body[:-1]):
            raise ValueError("conditional control inside the loop body is unreviewed")
        for insn in body:
            flow.step(insn)
        count, spacing, offset = CONFIG[action][mode]
        expected_angle = neg(A) if not offset else neg(expr("add", A, const(offset)))
        expected_angle = rounded(expr("add", expected_angle, expr("mul", I, const(spacing))), 4)
        updated = expr("add", I, const(1))
        request = flow.requests[0] if len(flow.requests) == 1 else None
        comparison = flow.comparison
        test = body[-2]
        mask = test.operands[1].imm if test.mnemonic == "test" and test.operands[0].type == x.X86_OP_REG and test.operands[0].reg == x.X86_REG_AH and test.operands[1].type == x.X86_OP_IMM else None
        predicate = ((comparison == (const(count), updated) and mask == 0x41 and edge.mnemonic == "je")
                     or (comparison == (updated, const(count)) and mask == 5 and edge.mnemonic == "jnp"))
        reads = Counter()
        for (role, field, width, _), amount in flow.reads.items():
            reads[(role, field, width)] += amount
        fresh = all(reads[key] >= amount for key, amount in {
            ("self", 0x170, 4): 1, ("peer", 0xEC, 4): 1, ("peer", 0xF0, 4): 1,
            ("self", 0xEC, 4): 2, ("self", 0xF0, 4): 2, ("self", 0x104, 1): 3}.items())
        success = (flow.calls == ["atan2", "sine", "cosine", "spawn"] and request is not None
                   and request["object"] == 900 and request["count"] == 3 and request["arg5"] == 1
                   and request["buffer"] % 4 == 0
                   and request["payload"] == [("f", expected_angle), ("f", const(4)), ("f", const(0))]
                   and not request["buffer"] <= counter < request["buffer"]+12
                   and flow.mem.get(counter) == (4, ("f", updated)) and predicate and fresh
                   and flow.sp == 0 and flow.fp == ([updated] if carried else [])
                   and flow.reads[("self", 0x104, 1, "movsx")] >= 2
                   and flow.reads[("self", 0x104, 1, "movzx")] >= 1)
        rows.append({"mode": mode, "entry": hex(entry), "header": hex(header), "backedge": hex(edge.address),
                     "counter_offset": counter, "counter_carried_in_x87": carried, "calls": flow.calls,
                     "request": request, "comparison": comparison, "expected_count": count,
                     "expected_spacing": spacing, "expected_offset": offset, "fresh_actor_reads": fresh,
                     "counter_predicate": predicate, "satisfied": success})
    return rows


def audit(path):
    canonical = load("reimu_aimed_loop_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = load("reimu_aimed_loop_mapper", "compare-giant-action-switches.py")
    tm = mapper.load_target_mapper()
    root = tm.select_root(tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()), "reimu-vslot28")
    target = tm.map_root(tm.PeImage(ROOT / "resources/th105.exe"), tm.load_function_rows(ROOT / "config/functions.csv"), root)
    obj = mapper.CoffObject(path, symbol_base=SYMBOL)
    comparison = mapper.compare_maps(target, mapper.build_candidate_map(obj, root))
    rows = []
    for row in comparison["rows"]:
        if row["cases"] not in ([710], [711]):
            continue
        action = row["cases"][0]
        address, source = int(root["address"], 0)+row["target_offset"], row["candidate_offsets"][0]
        wanted = inspect(View(canonical), canonical.target_bytes(address, row["target_span"]), address, action)
        actual = inspect(View(canonical, obj), obj.text[source:source+row["candidate_span"]], source, action)
        rows.append({"action": action, "target": wanted, "source": actual})
    if len(rows) != 2:
        raise ValueError("both aimed-action owners are required")
    failures = [{"action": row["action"], "side": side, "mode": mode["mode"]} for row in rows
                for side in ("target", "source") for mode in row[side] if not mode["satisfied"]]
    return {"schema": "th105-reimu-aimed-loop-static-v1", "target_sha256": target_sha,
            "object_sha256": hashlib.sha256(path.read_bytes()).hexdigest(), "failure_count": len(failures),
            "failures": failures, "rows": rows, "capstone_version": capstone.__version__,
            "support_sha256": {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__), ROOT / "scripts/compare-function.py", ROOT / "scripts/compare-giant-action-switches.py", ROOT / "config/giant-action-switches.toml", ROOT / "scripts/map-giant-action-switches.py", ROOT / "config/functions.csv")},
            "scope": "static finite-angle/PC53-PC64 nearest-mode expression, local counter and reload contracts only; unvalued helper result, no callback execution or whole-volley/canonical-exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except (KeyError, IndexError, OSError, ValueError) as error:
        parser.exit(2, f"Reimu aimed-loop audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["failure_count"] else 0)
