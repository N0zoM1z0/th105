#!/usr/bin/env python3
"""Compare complete Aya root normal-return graphs without exact-match credit."""

from pathlib import Path
import argparse
import importlib.util
import json
import hashlib
import sys
import tomllib
import capstone
from capstone import x86_const as x

R = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(R / "scripts"))
import linked_pe as lp
from workflow_manifest import load_manifest

S = 0x800000


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, R / path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


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



# Optional normal-ABI equivalence, deliberately separate from exact label equality.
# These two target helpers have recovered thiscall ABIs; their incoming EAX/EDX
# are not arguments. This does not model callback/exception register observers.
CALL_ABIS = {0x435160: "oriented_components(this,float,float)",
             0x4351C0: "advance_frame(this)"}
VOLATILE = ("eax", "ecx", "edx")


def mask(name, family):
    aliases = {"eax": {"eax": 15, "ax": 3, "al": 1, "ah": 2},
               "ecx": {"ecx": 15, "cx": 3, "cl": 1, "ch": 2},
               "edx": {"edx": 15, "dx": 3, "dl": 1, "dh": 2}}
    return aliases[family].get(name, 0)


def dead_after(p, pc, family):
    pending, visited, calls = [(pc, 15)], set(), set()
    while pending:
        pc, live = pending.pop()
        pc = contract(p, pc)
        if (pc, live) in visited:
            continue
        visited.add((pc, live))
        r = p["by"][pc]
        if r.group(capstone.CS_GRP_RET):
            continue  # void root; volatile return registers have no output contract
        reads, writes = r.regs_access()
        read_mask = 0
        write_mask = 0
        for reg in reads:
            read_mask |= mask(r.reg_name(reg), family)
        for reg in writes:
            write_mask |= mask(r.reg_name(reg), family)
        assert not live & read_mask, ("carrier remains live", hex(pc), family, r.op_str)
        if r.group(capstone.CS_GRP_CALL):
            assert r.operands[0].type == x.X86_OP_IMM
            dest = r.operands[0].imm
            assert dest in CALL_ABIS, ("unqualified call", hex(pc), hex(dest))
            assert family != "ecx", ("this argument remains live", hex(pc))
            calls.add(dest)
            # A clobber is not a defined value. Continue checking the volatile
            # bytes after normal return; only the known unsigned-char return
            # defines AL. Do not silently treat all caller-saved registers as
            # equal just because a call occurred.
            write_mask = 1 if family == "eax" and dest == 0x4351C0 else 0
        live &= ~write_mask
        if live:
            successors = edges(p, r)
            assert successors, ("unqualified exit", hex(pc))
            pending.extend((dest, live) for dest in successors)
    return {"nodes": len(visited), "calls": [hex(v) for v in sorted(calls)]}


def carrier_window(old, new, a, b):
    import re
    left, right = old["by"][a], new["by"][b]
    assert left.mnemonic == right.mnemonic and left.mnemonic in ("mov", "movsx", "lea")
    assert left.operands[0].type == right.operands[0].type == x.X86_OP_REG
    src, dst = left.reg_name(left.operands[0].reg), right.reg_name(right.operands[0].reg)
    assert src in VOLATILE and dst in VOLATILE and src != dst
    def rename(value):
        return re.sub(r"\b" + dst + r"\b", src, value)
    assert not any(mask(left.reg_name(v), src) for v in left.regs_access()[0])
    assert not any(mask(right.reg_name(v), dst) for v in right.regs_access()[0])
    # Only the three observed semantic forms, never arbitrary volatile wildcards.
    templates = {"mov": ["mov", "cmp"], "movsx": ["movsx", "mov"],
                 "lea": ["lea", "add", "add", "add", "mov"]}
    pairs = []
    for mnemonic in templates[left.mnemonic]:
        l, r = old["by"][a], new["by"][b]
        assert l.mnemonic == r.mnemonic == mnemonic
        assert label(old, l) == rename(label(new, r))
        assert not l.group(capstone.CS_GRP_JUMP) and not l.group(capstone.CS_GRP_CALL)
        pairs.append((a, b))
        a, b = a + l.size, b + r.size
    # Validate actual templates, including consuming the final temporary value.
    if left.mnemonic == "mov":
        assert left.op_str == f"{src}, dword ptr [esi + 0x348]"
        assert l.op_str == f"word ptr [{src} + 0x174], 0"
    elif left.mnemonic == "movsx":
        assert left.op_str == f"{src}, byte ptr [esi + 0x104]"
        assert l.op_str == f"dword ptr [esp + 0x18], {src}"
    else:
        assert left.op_str == f"{src}, [eax + eax*4]" and src != "eax" and dst != "eax"
        assert all(old["by"][pc].op_str == f"{src}, {src}" for pc, _ in pairs[1:4])
        assert l.op_str == f"dword ptr [esp + 0x18], {src}"
    # No direct/switch edge may enter the middle of a contracted window.
    for p, column in ((old, 0), (new, 1)):
        interior = {pair[column] for pair in pairs[1:]}
        for row in p["by"].values():
            if row.group(capstone.CS_GRP_JUMP):
                assert not interior.intersection(edges(p, row)), "window has another entry"
    checks = {side: {reg: dead_after(p, end, reg) for reg in (src, dst)}
              for side, p, end in (("old", old, a), ("new", new, b))}
    return a, b, pairs, dict(start=[hex(pairs[0][0]), hex(pairs[0][1])],
                              registers=[src, dst], instructions=len(pairs), liveness=checks)


def main():
    global c, f, mapper, world, root
    c = lp.comparator()
    c.verify_target()
    m = load_manifest()
    u = m["units"]["gpt-web-aya-object-vslot28-full-root"]
    f = u["functions"][0]
    parser = argparse.ArgumentParser(
        description="Compare two Aya root normal-return instruction graphs; not exact acceptance."
    )
    parser.add_argument("previous", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--exclude-action", type=int, choices=range(800, 999))
    parser.add_argument("--exclude-903-sequence", type=int, choices=range(10), action="append", default=[])
    parser.add_argument("--dead-carriers", action="store_true", help="Qualify short volatile-carrier renamings using checked templates and ABI liveness")
    parser.add_argument("--output", type=Path, default=R / "build/aya-flow.json")
    args = parser.parse_args()


    mapper = load("tail_mapper", "scripts/compare-giant-action-switches.py")
    world = load("tail_world", "scripts/audit-reimu-object-world-sharing.py")
    tm = mapper.load_target_mapper()
    root = tm.select_root(
        tomllib.loads((R / "config/giant-action-switches.toml").read_text()),
        "aya-object-vslot28",
    )


    oldpath = args.previous
    newpath = args.candidate
    old, new = packet(oldpath), packet(newpath)
    assert not (args.exclude_action is not None and args.exclude_903_sequence)
    excluded_entries = []
    if args.exclude_action is not None or args.exclude_903_sequence:
        by_side = []
        for packet_ in (old, new):
            primary = [sw for sw in packet_["switches"].values() if sw["checked_maximum"] == 198]
            assert len(primary) == 1
            sw = primary[0]
            offset = sw["index_table"] - S
            indices = packet_["code"][offset:offset + 199]
            action = args.exclude_action if args.exclude_action is not None else 903
            selected = indices[action - 800]
            assert indices.count(selected) == 1, "excluded action aliases another action"
            entry = sw["destinations"][selected]
            if args.exclude_903_sequence:
                # Qualify the actual signed WORD13E -> guarded dense0..9 switch.
                rows = []
                pc = entry
                for _ in range(4):
                    row = packet_["by"][pc]
                    rows.append(row)
                    pc += row.size
                assert rows[0].mnemonic == "movsx" and rows[0].op_str == "eax, word ptr [esi + 0x13e]"
                assert rows[1].mnemonic == "cmp" and rows[1].op_str == "eax, 9"
                assert rows[2].mnemonic == "ja"
                sw = packet_["switches"][rows[3].address]
                assert sw["checked_maximum"] == 9 and not sw.get("index_table")
                assert len(sw["destinations"]) == 10
                entries = [sw["destinations"][seq] for seq in args.exclude_903_sequence]
                assert all(sw["destinations"].count(dest) == 1 for dest in entries), "excluded sequence aliases another sequence"
            else:
                entries = [entry]
            by_side.append(entries)
        excluded_entries = list(zip(*by_side))
    pending = [(S, S)]
    seen = set()
    carrier_checks = []
    while pending:
        a, b = pending.pop()
        if any(a == left or b == right for left, right in excluded_entries):
            assert (a, b) in excluded_entries
            continue
        a = contract(old, a)
        b = contract(new, b)
        if (a, b) in seen:
            continue
        seen.add((a, b))
        ur, vr = old["by"][a], new["by"][b]
        if args.dead_carriers and label(old, ur) != label(new, vr):
            end_a, end_b, pairs, check = carrier_window(old, new, a, b)
            seen.update(pairs)
            carrier_checks.append(check)
            pending.append((end_a, end_b))
            continue
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
        result="normal_abi_equal_with_dead_carriers" if carrier_checks else "equal",
        carrier_checks=carrier_checks,
        normal_abi_helpers={
            hex(address): dict(signature=CALL_ABIS[address], size=size,
                               target_sha256=hashlib.sha256(c.target_bytes(address, size)).hexdigest())
            for address, size in ((0x435160, 57), (0x4351C0, 62))
        } if carrier_checks else {},
        paired_nodes=len(seen),
        excluded_action=args.exclude_action,
        excluded_903_sequences=args.exclude_903_sequence,
        scope="root instruction-labelled normal-return graph except the explicitly reported excluded action or903 sequence entries, if any; internal direct JMP contracted; optional reported carrier windows require template equality and dead-byte liveness through normal thiscall contracts435160/4351C0 and void RET; switch guards/index bytes and ordered edges checked; opaque calls assumed normal return, no callback/exception or canonical equivalence claim",
        previous_sha256=lp.sha(oldpath),
        candidate_sha256=lp.sha(newpath),
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
