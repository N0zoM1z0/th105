#!/usr/bin/env python3
"""Check Reimu720's random-base conversion, counters and four-float requests.

This is static loop evidence with an unvalued uint32 draw, not callback
execution, a whole-volley comparison or canonical acceptance.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import tomllib

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu720_loop_facts", ROOT / "scripts/audit-reimu-aimed-mode-loops.py")
facts = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = facts
spec.loader.exec_module(facts)
BASE = ("round32_unsigned_random_draw",)
CONFIG = ((3, 120, 1), (4, 90, 2), (6, 60, 2), (8, 45, 3))


class View(facts.View):
    def call_name(self, insn):
        if self.obj is None and insn.operands[0].imm == 0x4067D0:
            return "random_roll"
        if self.obj is not None:
            pair = self.obj.relocations.get(insn.address+1)
            if pair and pair[1] == 20 and pair[0].name == "?selector_random_roll@th105@@YAHH@Z":
                return "random_roll"
        return super().call_name(insn)


class Flow(facts.Flow):
    def __init__(self, view):
        super().__init__(view, parameter_count=4)
        self.receivers = []

    def call(self, insn):
        self.receivers.append(self.reg(x.X86_REG_ECX))
        super().call(insn)


def stack_slot(operand):
    if (operand.type != x.X86_OP_MEM or operand.size != 4
            or operand.mem.base != x.X86_REG_ESP or operand.mem.index):
        raise ValueError("expected one local DWORD stack slot")
    return operand.mem.disp


def prepare(view, prefix):
    # Recognize both paths of the VC8 uint32-to-float32 conversion. The draw
    # stays symbolic: no concrete helper result or callback is supplied.
    names = [i.mnemonic for i in prefix]
    if names != ["push", "call", "add", "test", "mov", "fild", "jge", "fadd", "fstp", "fldz", "fstp", "fld"]:
        raise ValueError("unreviewed random-base/counter preparation")
    ops = [i.operands for i in prefix]
    if (ops[0][0].type != x.X86_OP_IMM or ops[0][0].imm != 360
            or view.call_name(prefix[1]) != "random_roll"
            or ops[2][0].type != x.X86_OP_REG or ops[2][0].reg != x.X86_REG_ESP
            or ops[2][1].type != x.X86_OP_IMM or ops[2][1].imm != 4
            or any(op.type != x.X86_OP_REG or op.reg != x.X86_REG_EAX for op in ops[3])
            or ops[4][1].type != x.X86_OP_REG or ops[4][1].reg != x.X86_REG_EAX
            or stack_slot(ops[4][0]) != stack_slot(ops[5][0])
            or ops[6][0].type != x.X86_OP_IMM or ops[6][0].imm != prefix[8].address
            or view.literal(prefix[7], ops[7][0]) != bytes.fromhex("0000804f")):
        raise ValueError("random draw/unsigned conversion is not locally proved")
    base, counter = stack_slot(ops[8][0]), stack_slot(ops[10][0])
    if base == counter or stack_slot(ops[11][0]) != counter:
        raise ValueError("base/counter storage is not independent")
    flow = Flow(view)
    flow.mem[base] = (4, ("f", BASE))
    for insn in prefix[9:]:
        flow.step(insn)
    if flow.mem.get(counter) != (4, ("f", facts.const(0))) or flow.fp != [facts.const(0)]:
        raise ValueError("counter does not start at positive zero")
    flow.mem[counter], flow.fp = (4, ("f", facts.I)), [facts.I]
    return flow, base, counter


def inspect(view, code, start):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, start))
    if sum(i.size for i in instructions) != len(code):
        raise ValueError("720 owner did not decode completely")
    dispatches = [i for i in instructions if i.mnemonic == "jmp" and i.operands[0].type == x.X86_OP_MEM]
    if len(dispatches) != 1:
        raise ValueError("720 needs one four-mode table")
    jump = dispatches[0]
    table = jump.operands[0].mem.disp if view.obj is None else view.obj.relocated_text_value(jump.address+jump.disp_offset)
    entries = ([int.from_bytes(view.canonical.target_bytes(table+4*k, 4), "little") for k in range(4)]
               if view.obj is None else [view.obj.relocated_text_value(table+4*k) for k in range(4)])
    if len(set(entries)) != 4 or any(not start <= entry < start+len(code) for entry in entries):
        raise ValueError("720 modes share a loop or escape their owner")
    rows = []
    for mode, entry in enumerate(entries):
        end = min((other for other in entries if other > entry), default=start+len(code))
        edges = [i for i in instructions if entry <= i.address < end and i.mnemonic.startswith("j")
                 and i.mnemonic != "jmp" and i.operands[0].type == x.X86_OP_IMM
                 and entry <= i.operands[0].imm < i.address]
        if len(edges) != 1:
            raise ValueError("720 mode needs one natural backedge")
        edge = edges[0]
        header = edge.operands[0].imm
        flow, base, counter = prepare(view, [i for i in instructions if entry <= i.address < header])
        body = [i for i in instructions if header <= i.address <= edge.address]
        if any(i.mnemonic.startswith("j") for i in body[:-1]):
            raise ValueError("720 loop has unreviewed internal control flow")
        for insn in body:
            flow.step(insn)
        count, spacing, variant = CONFIG[mode]
        angle = facts.rounded(facts.expr("add", facts.expr("mul", facts.I, facts.const(spacing)), BASE), 4)
        updated = facts.expr("add", facts.I, facts.const(1))
        request = flow.requests[0] if len(flow.requests) == 1 else None
        test = body[-2]
        predicate = (flow.comparison == (updated, facts.const(count)) and edge.mnemonic == "jnp"
                     and test.mnemonic == "test" and test.operands[0].type == x.X86_OP_REG
                     and test.operands[0].reg == x.X86_REG_AH and test.operands[1].type == x.X86_OP_IMM
                     and test.operands[1].imm == 5)
        fresh = all(sum(v for (role, field, width, _), v in flow.reads.items()
                        if (role, field, width) == ("self", offset, size)) >= 1
                    for offset, size in ((0xEC, 4), (0xF0, 4), (0x104, 1)))
        success = (flow.calls == ["spawn"] and flow.receivers == [("p", "self", 0)]
                   and request is not None and request["object"] == 901 and request["count"] == 4
                   and request["arg5"] == 1 and request["buffer"] % 4 == 0
                   and request["payload"] == [("f", angle), ("f", facts.const(10)),
                                               ("f", facts.const(0)), ("f", facts.const(variant))]
                   and all(not request["buffer"] <= slot < request["buffer"]+16 for slot in (base, counter))
                   and flow.mem.get(base) == (4, ("f", BASE))
                   and flow.mem.get(counter) == (4, ("f", updated)) and flow.fp == [updated]
                   and flow.sp == 0 and fresh and flow.reads[("self", 0x104, 1, "movzx")] >= 1 and predicate)
        rows.append({"mode": mode, "entry": hex(entry), "header": hex(header), "backedge": hex(edge.address),
                     "base_offset": base, "counter_offset": counter, "request": request,
                     "expected_count": count, "expected_spacing": spacing, "expected_variant": variant,
                     "unsigned_draw_conversion": True, "counter_predicate": predicate,
                     "fresh_actor_reads": fresh, "satisfied": success})
    return rows


def audit(path):
    canonical = facts.load("reimu720_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = facts.load("reimu720_mapper", "compare-giant-action-switches.py")
    tm = mapper.load_target_mapper()
    root = tm.select_root(tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()), "reimu-vslot28")
    target = tm.map_root(tm.PeImage(ROOT / "resources/th105.exe"), tm.load_function_rows(ROOT / "config/functions.csv"), root)
    obj = mapper.CoffObject(path, symbol_base=facts.SYMBOL)
    mapping = mapper.compare_maps(target, mapper.build_candidate_map(obj, root))
    owner = next(row for row in mapping["rows"] if row["cases"] == [720])
    address, source = int(root["address"], 0)+owner["target_offset"], owner["candidate_offsets"][0]
    rows = {"target": inspect(View(canonical), canonical.target_bytes(address, owner["target_span"]), address),
            "source": inspect(View(canonical, obj), obj.text[source:source+owner["candidate_span"]], source)}
    failures = [{"side": side, "mode": row["mode"]} for side in rows for row in rows[side] if not row["satisfied"]]
    return {"schema": "th105-reimu720-loop-static-v1", "target_sha256": target_sha,
            "object_sha256": hashlib.sha256(path.read_bytes()).hexdigest(), "rows": rows,
            "failure_count": len(failures), "failures": failures, "capstone_version": capstone.__version__,
            "support_sha256": {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__), Path(facts.__file__), ROOT / "scripts/compare-function.py",
                                ROOT / "scripts/compare-giant-action-switches.py", ROOT / "scripts/map-giant-action-switches.py",
                                ROOT / "config/giant-action-switches.toml", ROOT / "config/functions.csv")},
            "scope": "static uint32 conversion and finite nearest-PC53/PC64 loop/payload/reload contracts; "
                     "unvalued draw, no callback return, whole-volley or canonical-exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except (KeyError, IndexError, OSError, ValueError) as error:
        parser.exit(2, f"Reimu720 loop audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["failure_count"] else 0)
