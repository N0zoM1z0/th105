#!/usr/bin/env python3
"""Reusable compile, per-owner audit, and disassembly diff tool for giant roots.

Diagnostic helper only: canonical acceptance remains scripts/build.py --compare.
Works with any root defined in config/giant-action-switches.toml and any unit
defined in config/match-units.toml.
"""
from __future__ import annotations

import argparse
from collections import Counter
from difflib import SequenceMatcher
import importlib.util
import os
from pathlib import Path
import subprocess
import sys
import tomllib
from typing import Any

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]


def load_script(name: str, filename: str) -> Any:
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot load {filename}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def compile_source(source: Path, obj: Path) -> None:
    env = os.environ.copy()
    env["WINEDEBUG"] = "-all"
    env["DISPLAY"] = ""
    env["WAYLAND_DISPLAY"] = ""
    for key in ("WINEPREFIX", "WINEARCH"):
        env.pop(key, None)
    result = subprocess.run(
        ["bash", str(ROOT / "scripts/compile-unit.sh"), str(source), str(obj)],
        env=env,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        sys.stderr.write(result.stdout)
        sys.stderr.write(result.stderr)
        raise SystemExit(result.returncode)


def parse_kv(items: list[str]) -> dict[str, str]:
    out: dict[str, str] = {}
    for item in items:
        if "=" not in item:
            raise SystemExit(f"expected NAME=VALUE, got: {item}")
        key, value = item.split("=", 1)
        out[key] = value
    return out


def load_root_and_unit(root_name: str, unit_name: str) -> tuple[Any, Any, Any, dict[str, Any], dict[str, Any], dict[str, Any]]:
    canonical = load_script("th105_iter_canonical", "compare-function.py")
    canonical.verify_target()
    mapper = load_script("th105_iter_mapper", "compare-giant-action-switches.py")
    target_mapper = mapper.load_target_mapper()
    manifest = tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text())
    root = target_mapper.select_root(manifest, root_name)
    target = target_mapper.map_root(
        target_mapper.PeImage(ROOT / "resources/th105.exe"),
        target_mapper.load_function_rows(ROOT / "config/functions.csv"),
        root,
    )
    units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
    if unit_name not in units:
        raise SystemExit(f"unknown match unit: {unit_name}")
    unit = units[unit_name]
    address = target["address"]
    functions = [f for f in unit["functions"] if int(f["address"], 0) == address]
    if len(functions) != 1:
        raise SystemExit(f"unit {unit_name} must define exactly one function at {address:#x}")
    return canonical, mapper, target_mapper, root, target, functions[0]


def disasm_list(code: bytes, va: int) -> list[Any]:
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    return list(md.disasm(code, va))


def first_prologue_sub(code: bytes, va: int) -> str:
    for insn in disasm_list(code[:64], va):
        if insn.mnemonic == "sub" and insn.op_str.startswith("esp,"):
            return insn.op_str
    return "(none)"


def direct_call_counts(code: bytes, va: int) -> Counter[int]:
    counts: Counter[int] = Counter()
    for insn in disasm_list(code, va):
        if insn.mnemonic == "call" and insn.op_str.startswith("0x"):
            counts[int(insn.op_str, 16)] += 1
    return counts


def find_target_owner(target: dict[str, Any], name: str) -> tuple[int, int]:
    address = target["address"]
    groups: dict[int, tuple[str, int]] = {}
    for region in target["regions"]:
        rname = region["name"]
        for group in region["groups"]:
            off = group["destination"] - address
            label = f"{rname}:{group['cases'][0]}"
            groups.setdefault(off, (label, group["destination"]))
    starts = sorted(groups)
    starts.append(target["callable_size"])
    if name == "entry":
        return 0, starts[0]
    for idx, off in enumerate(starts[:-1]):
        label, _ = groups[off]
        if label == name or label.endswith(":" + name):
            return off, starts[idx + 1] - off
    raise SystemExit(f"unknown target owner: {name}")


def build_flexible_candidate_map(mapper: Any, obj: Any, root: dict[str, Any]) -> dict[str, Any]:
    """Fall back to looser table matching if an early draft splits/merges a case."""
    try:
        return mapper.build_candidate_map(obj, root)
    except Exception:
        # Retry with destination_count relaxed per region when switch topology differs.
        relaxed = dict(root)
        regions = []
        for region in root["regions"]:
            regions.append(dict(region))
        relaxed["regions"] = regions
        return mapper.build_candidate_map(obj, relaxed)


def dump_target_owners(canonical: Any, target: dict[str, Any], names: list[str]) -> None:
    address = target["address"]
    target_code = canonical.target_bytes(address, target["callable_size"])
    for name in names:
        off, span = find_target_owner(target, name)
        print(f"=== TARGET {name} va=0x{address + off:08x} (+0x{off:04x}, {span}B) ===")
        for insn in disasm_list(target_code[off : off + span], address + off):
            print(
                f"  0x{insn.address:08x} (+0x{insn.address - address:04X}) "
                f"{insn.bytes.hex():18s} {insn.mnemonic} {insn.op_str}"
            )


def run_audit(
    canonical: Any,
    mapper: Any,
    target_mapper: Any,
    root: dict[str, Any],
    target: dict[str, Any],
    function: dict[str, Any],
    obj_path: Path,
    extra_rel32: dict[str, str],
    extra_dir32: dict[str, str],
    diff_names: list[str],
    show_all: bool,
) -> None:
    from giant_owner_audit import compare_owner_instructions, paired_owners

    address = target["address"]
    symbol_base = function["symbol_base"]
    obj = mapper.CoffObject(obj_path, symbol_base=symbol_base)
    rel32 = canonical.known_targets()
    rel32.update({k: int(v, 0) for k, v in (item.split("=", 1) for item in function.get("rel32_targets", []))})
    rel32.update({k: int(v, 0) for k, v in extra_rel32.items()})
    dir32 = dict(item.split("=", 1) for item in function.get("dir32_targets", []))
    dir32.update(extra_dir32)

    relocated = canonical.coff_symbol_bytes(
        obj_path, symbol_base, address, len(obj.text), rel32, canonical.known_data_targets(), dir32
    )
    target_code = canonical.target_bytes(address, target["callable_size"])
    target_envelope = target["metadata_end"] - address

    print(f"=== GIANT ROOT AUDIT: {root['name']} ({obj_path}) ===")
    try:
        candidate = build_flexible_candidate_map(mapper, obj, root)
        comparison = mapper.compare_maps(target, candidate)
        pairs = paired_owners(comparison["rows"])
    except Exception as exc:
        print(f"Switch-topology mismatch (fix before per-owner diff): {exc}")
        print(f"Target callable : {len(target_code)} B | Candidate full section : {len(obj.text)} B (target envelope {target_envelope} B)")
        print(f"Prologue sub    : {first_prologue_sub(relocated, address)} (target: {first_prologue_sub(target_code, address)})")
        t_calls = direct_call_counts(target_code, address)
        c_calls = direct_call_counts(relocated[: len(target_code)], address)
        for dst in sorted(set(t_calls) | set(c_calls)):
            if t_calls[dst] != c_calls[dst]:
                print(f"  call 0x{dst:08x}: tgt={t_calls[dst]} cand={c_calls[dst]} ({c_calls[dst] - t_calls[dst]:+d})")
        return

    metadata_start = candidate["metadata_start"]
    cand_code = relocated[:metadata_start]
    payload = function.get("switch_payload")
    if payload:
        alignment = bytes.fromhex(payload["alignment_hex"])
        if alignment and cand_code == target_code + alignment:
            cand_code = cand_code[: len(target_code)]
            final_owner = max(pairs, key=lambda pair: pair["candidate_offset"])
            final_owner["candidate_span"] -= len(alignment)

    target_tables: list[tuple[int, int, str]] = []
    cand_tables: list[tuple[int, int, str]] = []
    for configured, built in zip(root["regions"], candidate["regions"]):
        rname = configured["name"]
        count = int(configured["destination_count"])
        cases = int(configured["case_max"]) - int(configured["case_min"]) + 1
        dt = target_mapper.parse_int(configured["destination_table"])
        it = target_mapper.parse_int(configured["index_table"])
        target_tables.extend([(dt, dt + 4 * count, rname + ".destinations"), (it, it + cases, rname + ".indices")])
        cd = address + built["destination_table_offset"]
        ci = address + built["index_table_offset"]
        cand_tables.extend(
            [(cd, cd + 4 * built["destination_count"], rname + ".destinations"), (ci, ci + cases, rname + ".indices")]
        )

    owners = compare_owner_instructions(target_code, cand_code, address, pairs, target_tables, cand_tables)
    exact_count = sum(1 for o in owners if o["instruction_edge_identical"])
    print(f"Target callable : {len(target_code)} B  | Candidate code : {len(cand_code)} B (delta {len(cand_code) - len(target_code):+d} B)")
    print(f"Full section    : {len(obj.text)} B  (target envelope {target_envelope} B)")
    print(f"Exact owners    : {exact_count}/{len(owners)}")
    print(f"Prologue sub    : {first_prologue_sub(cand_code, address)} (target: {first_prologue_sub(target_code, address)})")

    t_calls = direct_call_counts(target_code, address)
    c_calls = direct_call_counts(cand_code, address)
    call_deltas = [(dst, t_calls[dst], c_calls[dst]) for dst in sorted(set(t_calls) | set(c_calls)) if t_calls[dst] != c_calls[dst]]
    if not call_deltas:
        print(f"Direct call deltas: NONE (all {len(t_calls)} targets exact!)")
    else:
        print(f"Direct call deltas ({len(call_deltas)}):")
        for dst, tc, cc in call_deltas:
            print(f"  0x{dst:08x}: tgt={tc:3d} cand={cc:3d} ({cc - tc:+d})")

    by_name = {o["name"]: o for o in owners}
    non_exact = [o for o in owners if not o["instruction_edge_identical"]]
    if non_exact or show_all:
        print(f"Non-exact owners ({len(non_exact)}):")
        for o in owners if show_all else non_exact:
            tag = "EXACT" if o["instruction_edge_identical"] else ""
            toff, tspan = o["target_offset"], o["target_span"]
            coff, cspan = o["candidate_offset"], o["candidate_span"]
            t_ins = disasm_list(target_code[toff : toff + tspan], address + toff)
            c_ins = disasm_list(cand_code[coff : coff + cspan], address + coff)
            t_txt = [f"{x.mnemonic} {x.op_str}".strip() for x in t_ins]
            c_txt = [f"{x.mnemonic} {x.op_str}".strip() for x in c_ins]
            sm = SequenceMatcher(None, t_txt, c_txt)
            ops = [op for op in sm.get_opcodes() if op[0] != "equal"]
            first_t = first_c = ""
            if ops:
                _, i1, i2, j1, j2 = ops[0]
                if i1 < i2:
                    first_t = f"+0x{t_ins[i1].address - address:04X} {t_txt[i1]}"
                if j1 < j2:
                    first_c = f"+0x{c_ins[j1].address - address:04X} {c_txt[j1]}"
            print(
                f"  {o['name']:16s} tgt={tspan:4d}B cand={cspan:4d}B ({cspan - tspan:+4d}B) "
                f"ins={len(t_ins):3d}/{len(c_ins):3d} ndiff={len(ops):2d} {tag} t=`{first_t}` c=`{first_c}`"
            )

    for name in diff_names:
        o = by_name.get(name)
        if o is None:
            matches = [v for k, v in by_name.items() if k.endswith(":" + name)]
            if len(matches) == 1:
                o = matches[0]
            else:
                print(f"Unknown owner for --diff: {name}")
                continue
        toff, tspan = o["target_offset"], o["target_span"]
        coff, cspan = o["candidate_offset"], o["candidate_span"]
        t_ins = disasm_list(target_code[toff : toff + tspan], address + toff)
        c_ins = disasm_list(cand_code[coff : coff + cspan], address + coff)
        t_txt = [f"{x.mnemonic} {x.op_str}".strip() for x in t_ins]
        c_txt = [f"{x.mnemonic} {x.op_str}".strip() for x in c_ins]
        print(f"\n--- DIFF {o['name']} tgt=+0x{toff:04x}({tspan}B) cand=+0x{coff:04x}({cspan}B) ---")
        sm = SequenceMatcher(None, t_txt, c_txt)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                continue
            print(f"  [{tag}]")
            for k in range(i1, i2):
                print(f"    - +0x{t_ins[k].address - address:04X} {t_txt[k]}")
            for k in range(j1, j2):
                print(f"    + +0x{c_ins[k].address - address:04X} {c_txt[k]}")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Compile, audit, and diff a giant TH105 action-state root.")
    parser.add_argument("--root", required=True, help="Root name in config/giant-action-switches.toml")
    parser.add_argument("--unit", required=True, help="Unit name in config/match-units.toml")
    parser.add_argument("--compile", type=Path, help="Compile this C++ source into --obj before auditing")
    parser.add_argument("--obj", type=Path, help="COFF .obj file to audit")
    parser.add_argument("--diff", nargs="*", default=[], help="Owner names (e.g. low:214 mid:404) to diff")
    parser.add_argument("--target", nargs="*", default=[], help="Target owner names to disassemble")
    parser.add_argument("--all", action="store_true", help="Print all owners including exact ones")
    parser.add_argument("--rel32", action="append", default=[], help="Extra REL32 symbol=0xaddr override")
    parser.add_argument("--dir32", action="append", default=[], help="Extra DIR32 symbol=target override")
    args = parser.parse_args(argv)

    canonical, mapper, target_mapper, root, target, function = load_root_and_unit(args.root, args.unit)
    if args.target:
        dump_target_owners(canonical, target, args.target)
    if args.compile:
        if not args.obj:
            raise SystemExit("--compile requires --obj")
        compile_source(args.compile, args.obj)
    if args.obj:
        run_audit(
            canonical,
            mapper,
            target_mapper,
            root,
            target,
            function,
            args.obj,
            parse_kv(args.rel32),
            parse_kv(args.dir32),
            args.diff,
            args.all,
        )
    elif not args.target:
        raise SystemExit("provide --obj, --compile/--obj, or --target")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
