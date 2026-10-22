#!/usr/bin/env python3
"""Compare complete Aya root normal-return graphs without exact-match credit."""

from pathlib import Path
import argparse
import importlib.util
import json
import sys
import tomllib
import capstone
from capstone import x86_const as x

R = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(R / "scripts"))
import linked_pe as lp
from workflow_manifest import load_manifest

c = lp.comparator()
c.verify_target()
m = load_manifest()
u = m["units"]["gpt-web-aya-object-vslot28-full-root"]
f = u["functions"][0]
S = 0x800000
parser = argparse.ArgumentParser(
    description="Compare two Aya root normal-return instruction graphs; not exact acceptance."
)
parser.add_argument("previous", type=Path)
parser.add_argument("candidate", type=Path)
parser.add_argument("--output", type=Path, default=R / "build/aya-flow.json")
args = parser.parse_args()


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, R / path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


mapper = load("tail_mapper", "scripts/compare-giant-action-switches.py")
world = load("tail_world", "scripts/audit-reimu-object-world-sharing.py")
tm = mapper.load_target_mapper()
root = tm.select_root(
    tomllib.loads((R / "config/giant-action-switches.toml").read_text()),
    "aya-object-vslot28",
)


def packet(path):
    co = mapper.CoffObject(path, symbol_base=f["symbol_base"])
    meta = mapper.build_candidate_map(co, root)["metadata_start"]
    code = c.coff_symbol_bytes(
        path,
        f["symbol_base"],
        S,
        len(co.text),
        {a: int(b, 0) for a, b in (s.split("=", 1) for s in f["rel32_targets"])},
        c.known_data_targets(),
        dict(s.split("=", 1) for s in f.get("dir32_targets", [])),
    )
    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cs.detail = True
    rows = list(cs.disasm(code[:meta], S))
    assert sum(r.size for r in rows) == meta
    switches = world.reviewed_source_switches(rows, code, meta)
    assert len(switches) == 7
    return dict(
        code=code, meta=meta, by={r.address: r for r in rows}, switches=switches
    )


def contract(p, pc):
    seen = set()
    while True:
        assert pc not in seen
        seen.add(pc)
        r = p["by"][pc]
        if (
            r.mnemonic == "jmp"
            and r.operands[0].type == x.X86_OP_IMM
            and r.operands[0].imm in p["by"]
        ):
            pc = r.operands[0].imm
        else:
            return pc


def label(p, r):
    op = r.op_str
    if (
        r.group(capstone.CS_GRP_JUMP)
        and r.operands[0].type == x.X86_OP_IMM
        and r.operands[0].imm in p["by"]
    ):
        op = "<branch>"
    else:
        for operand in r.operands:
            if operand.type == x.X86_OP_MEM and S + p[
                "meta"
            ] <= operand.mem.disp < S + len(p["code"]):
                op = op.replace(
                    hex(operand.mem.disp), f"META+{operand.mem.disp - S - p['meta']:#x}"
                )
    return r.mnemonic + " " + op


def edges(p, r):
    if r.group(capstone.CS_GRP_RET):
        return []
    if r.group(capstone.CS_GRP_JUMP):
        if r.operands[0].type == x.X86_OP_IMM:
            if r.operands[0].imm not in p["by"]:
                assert r.mnemonic == "jmp"
                return []
            return [r.operands[0].imm, r.address + r.size]
        return list(p["switches"][r.address]["destinations"])
    return [r.address + r.size]


oldpath = args.previous
newpath = args.candidate
old, new = packet(oldpath), packet(newpath)
pending = [(S, S)]
seen = set()
while pending:
    a, b = pending.pop()
    a = contract(old, a)
    b = contract(new, b)
    if (a, b) in seen:
        continue
    seen.add((a, b))
    ur, vr = old["by"][a], new["by"][b]
    assert label(old, ur) == label(new, vr), (
        hex(a),
        hex(b),
        label(old, ur),
        label(new, vr),
    )
    if a in old["switches"] or b in new["switches"]:
        su, sv = old["switches"][a], new["switches"][b]
        assert su["checked_maximum"] == sv["checked_maximum"]
        assert bool(su.get("index_table")) == bool(sv.get("index_table"))
        if su.get("index_table"):
            count = su["checked_maximum"] + 1
            iu, iv = su["index_table"] - S, sv["index_table"] - S
            assert old["code"][iu : iu + count] == new["code"][iv : iv + count]
    eu, ev = edges(old, ur), edges(new, vr)
    assert len(eu) == len(ev)
    pending.extend(zip(eu, ev))
report = dict(
    result="equal",
    paired_nodes=len(seen),
    scope="whole root instruction-labelled normal-return graph, only internal direct JMP contracted; switch guards/index bytes and ordered edges checked; opaque calls assumed normal return, no callback/exception or canonical equivalence claim",
    previous_sha256=lp.sha(oldpath),
    candidate_sha256=lp.sha(newpath),
)
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps(report, indent=2))
