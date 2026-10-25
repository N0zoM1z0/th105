#!/usr/bin/env python3
"""Check bounded local request/publication order, without executing callbacks.

These are conservative intraprocedural traces from six mid-switch entries to
RET. Calls are opaque fallthroughs and predicates are unconstrained. This is a
static ordering diagnostic, not gameplay execution or whole-function equality.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "alice_complete_audit", ROOT / "scripts/audit-alice-fighter-update.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)

CALLS = {0x465190: "spawn", 0x45C030: "wave", 0x46BF30: "adjust", 0x478DF0: "scale"}
EXPECTED = {
    410: ("spawn", "wave", "adjust", "scale", "publish_180_dword"),
    411: ("spawn", "wave", "publish_180_dword", "adjust", "scale"),
    412: ("spawn", "wave", "publish_180_dword", "adjust", "scale"),
    414: ("spawn", "wave", "adjust", "publish_180_dword", "scale"),
    415: ("spawn", "wave", "publish_180_dword", "adjust", "scale"),
    416: ("spawn", "wave", "publish_180_dword", "adjust", "scale"),
}


def traces(raw):
    inventory = audit.inventory(raw)
    remaps = [r for r in inventory["remaps"] if r["size"] == 208]
    if len(remaps) != 1:
        raise ValueError("expected one 301..508 primary remap")
    remap = int(remaps[0]["address"], 0)
    table = max(int(t["address"], 0) for t in inventory["tables"]
                if int(t["address"], 0) < remap)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(raw[:inventory["code_to_first_table"]], audit.ADDRESS))
    by_address = {i.address: i for i in rows}
    if not any(i.mnemonic == "mov" and i.op_str == "esi, ecx" for i in rows[:12]):
        raise ValueError("reviewed ESI receiver home changed")
    results = {}
    for action in EXPECTED:
        index = raw[remap - audit.ADDRESS + action - 301]
        entry = struct.unpack_from("<I", raw, table - audit.ADDRESS + index * 4)[0]
        seen, pending, finished = set(), [(entry, ())], set()
        while pending:
            address, events = pending.pop()
            if (address, events) in seen:
                continue
            if address not in by_address or len(seen) >= 20000 or len(events) > 16:
                raise ValueError("bounded request CFG escaped or became cyclic")
            seen.add((address, events))
            row = by_address[address]
            if row.mnemonic == "call" and row.operands[0].type == x86.X86_OP_IMM:
                kind = CALLS.get(row.operands[0].imm)
                if kind:
                    events += ((kind, address),)
            if row.operands and row.operands[0].type == x86.X86_OP_MEM:
                operand = row.operands[0]
                memory = operand.mem
                if memory.base == x86.X86_REG_ESI and memory.index == 0 and memory.disp == 0x180:
                    if row.mnemonic != "mov" or operand.size != 4:
                        raise ValueError("reviewed dword publication instruction changed")
                    events += (("publish_180_dword", address),)
            if row.mnemonic == "ret":
                if row.op_str:
                    raise ValueError("expected root RET0")
                if any(kind == "spawn" for kind, _ in events):
                    finished.add(events)
                continue
            if row.mnemonic == "jmp":
                if row.operands[0].type != x86.X86_OP_IMM:
                    raise ValueError("unexpected indirect jump in bounded request arm")
                pending.append((row.operands[0].imm, events))
                continue
            if row.group(capstone.CS_GRP_JUMP):
                pending.append((row.operands[0].imm, events))
            pending.append((address + row.size, events))
        results[action] = dict(entry=hex(entry), traces=[
            dict(events=[kind for kind, _ in events], sites=[hex(a) for _, a in events])
            for events in sorted(finished)])
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path, help="override the complete caller COFF object")
    args = parser.parse_args()
    try:
        _, identity, candidate, target = audit.load_candidate(args.object)
        native, compiled = traces(target), traces(candidate)
        differences = []
        for action, expected in EXPECTED.items():
            target_orders = {tuple(t["events"]) for t in native[action]["traces"]}
            candidate_orders = {tuple(t["events"]) for t in compiled[action]["traces"]}
            if target_orders != {expected}:
                raise ValueError(f"target publication pin failed for action{action}")
            if candidate_orders != target_orders:
                differences.append(action)
        report = dict(diagnostic_only=True, target_sha256=identity,
                      canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                      scope="Static request/publication ordering only; opaque calls, unconstrained predicates. "
                            "Store value provenance, callback behavior and whole-function equivalence are unproved.",
                      actions=len(EXPECTED), mismatched_actions=differences,
                      native=native, candidate=compiled)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return 1 if differences else 0


if __name__ == "__main__":
    raise SystemExit(main())
