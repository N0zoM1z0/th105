#!/usr/bin/env python3
"""Decode the complete JP1.06a ReimuObject update root, including remote code.

This reports target instruction/edge facts. It does not compare source, prove
path feasibility, or award reconstruction credit.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct
import tomllib

import capstone
from capstone import x86_const as x
import pefile

ROOT = Path(__file__).resolve().parents[1]
TARGET_SHA = "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e"
ADDRESS = 0x496540
END = 0x4A197A
EXTENT_SHA = "399e56d3f1373e76381cafb17e4984845fdb1f680dc0737f864229b52f84e31d"
RANGES = ((ADDRESS, 0x49D169), (0x49D170, 0x4A00ED), (0x4A00F0, END))
# instruction, destination table, destination count, checked maximum,
# optional byte-index table. Register bounds are separately checked below.
SWITCHES = (
    (0x49656A, 0x4A197C, 42, 199, 0x4A1A24),
    (0x49694D, 0x4A1AEC, 4, 3, None),
    (0x497E9A, 0x4A1AFC, 5, 4, None),
    (0x4986C7, 0x4A1B10, 8, 7, None),
    (0x498CF6, 0x4A1B30, 10, 9, None),
    (0x499D45, 0x4A1B58, 7, 6, None),
    (0x49A638, 0x4A1B74, 5, 4, None),
    (0x49C34D, 0x4A1B88, 6, 5, None),
    (0x49CA05, 0x4A1BA0, 4, 3, None),
    (0x49CED5, 0x4A1BB0, 7, 6, None),
    (0x49D7E6, 0x4A1BCC, 4, 3, None),
    (0x49E3B0, 0x4A1BDC, 3, 8, 0x4A1BE8),
    (0x49E921, 0x4A1BF4, 6, 5, None),
    (0x49EBB2, 0x4A1C0C, 6, 5, None),
    (0x49ED75, 0x4A1C24, 4, 3, None),
    (0x49F289, 0x4A1C34, 6, 5, None),
    (0x49F44A, 0x4A1C4C, 4, 3, None),
    (0x49FB8A, 0x4A1C5C, 6, 5, None),
    (0x49FD3F, 0x4A1C74, 4, 3, None),
    (0x4A0530, 0x4A1C84, 10, 9, None),
    (0x4A0840, 0x4A1CAC, 4, 3, None),
    (0x4A1771, 0x4A1CBC, 9, 8, None),
)
REGISTER_BOUNDS = {
    0x49C34D: 0x49C32D,
    0x49E921: 0x49E901,
    0x49EBB2: 0x49EBA3,
    0x49F289: 0x49F27C,
    0x49FB8A: 0x49FB7B,
}


def decode(code, address):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(code, address))
    if sum(row.size for row in rows) != len(code):
        raise ValueError(f"incomplete instruction decoding at {address:#x}")
    return rows


def graph(rows, switches):
    by_address = {row.address: row for row in rows}
    edges = {}
    for row in rows:
        if row.group(capstone.CS_GRP_RET):
            edges[row.address] = []
            continue
        destinations = []
        if row.group(capstone.CS_GRP_JUMP):
            if row.operands[0].type == x.X86_OP_IMM:
                destinations.append(row.operands[0].imm)
            elif row.address in switches:
                destinations.extend(switches[row.address])
            else:
                raise ValueError(f"unreviewed indirect jump at {row.address:#x}")
        if row.mnemonic != "jmp":
            destinations.append(row.address + row.size)
        if any(target not in by_address for target in destinations):
            raise ValueError(
                f"edge does not enter an owned instruction at {row.address:#x}"
            )
        edges[row.address] = sorted(set(destinations))
    return edges


def reachable(edges, start):
    seen, pending = set(), [start]
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        if address not in edges:
            raise ValueError(f"missing instruction at {address:#x}")
        seen.add(address)
        pending.extend(edges[address])
    return seen


def direct_calls(rows):
    result = {}
    for row in rows:
        if row.mnemonic == "call" and row.operands[0].type == x.X86_OP_IMM:
            result.setdefault(row.operands[0].imm & 0xFFFFFFFF, []).append(row.address)
    return result


def audit():
    raw = (ROOT / "resources/th105.exe").read_bytes()
    if hashlib.sha256(raw).hexdigest() != TARGET_SHA:
        raise ValueError("target executable identity differs")
    pe = pefile.PE(data=raw)

    def read(address, size):
        data = pe.get_data(address - 0x400000, size)
        if len(data) != size:
            raise ValueError("short PE read")
        return data

    if (
        pe.OPTIONAL_HEADER.ImageBase != 0x400000
        or pe.OPTIONAL_HEADER.AddressOfEntryPoint != 0x28B9D2
        or struct.unpack("<I", read(0x6C40CC, 4))[0] != ADDRESS
    ):
        raise ValueError("target PE or primary vtable slot differs")
    extent = read(ADDRESS, END - ADDRESS)
    if hashlib.sha256(extent).hexdigest() != EXTENT_SHA:
        raise ValueError("complete root extent differs")
    ledger = tomllib.loads((ROOT / "config/function-byte-ownership.toml").read_text())
    owner = next(
        row for row in ledger["functions"] if int(row["address"], 0) == ADDRESS
    )
    if (
        ledger["target_sha256"] != TARGET_SHA
        or owner["owned_bytes"] != 46128
        or owner["main_size"] != 39853
        or owner["remote_bytes"] != 6282
    ):
        raise ValueError("root byte-ownership ledger differs")
    for row in owner["main_exclusions"] + owner["chunks"]:
        if (
            hashlib.sha256(read(int(row["start"], 0), row["size"])).hexdigest()
            != row["sha256"]
        ):
            raise ValueError("owned chunk or excluded alignment differs")
    rows = [
        row for start, end in RANGES for row in decode(read(start, end - start), start)
    ]
    by_address = {row.address: row for row in rows}
    switches, facts = {}, []
    for address, table, count, maximum, index_table in SWITCHES:
        row = by_address[address]
        op = row.operands[0]
        if (
            row.mnemonic != "jmp"
            or op.type != x.X86_OP_MEM
            or op.mem.base
            or op.mem.scale != 4
            or op.mem.disp != table
        ):
            raise ValueError(f"switch encoding differs at {address:#x}")
        position = rows.index(row)
        guard = next(
            (
                r
                for r in reversed(rows[max(0, position - 4) : position])
                if r.mnemonic == "ja"
            ),
            None,
        )
        if guard is None:
            raise ValueError("missing unsigned switch guard")
        guard_position = rows.index(guard)
        bound = next(
            (
                r
                for r in reversed(rows[max(0, guard_position - 4) : guard_position])
                if r.mnemonic == "cmp"
            ),
            None,
        )
        if bound is None or bound.operands[0].type != x.X86_OP_REG:
            raise ValueError("missing switch bound comparison")
        right = bound.operands[1]
        if right.type == x.X86_OP_IMM:
            if right.imm != maximum:
                raise ValueError("wrong immediate switch bound")
        elif right.type == x.X86_OP_REG and address in REGISTER_BOUNDS:
            definition = by_address[REGISTER_BOUNDS[address]]
            if (
                definition.mnemonic != "mov"
                or definition.operands[0].reg != right.reg
                or definition.operands[1].type != x.X86_OP_IMM
                or definition.operands[1].imm != maximum
            ):
                raise ValueError("wrong register switch bound")
            middle = rows[rows.index(definition) + 1 : rows.index(bound)]
            if any(right.reg in r.regs_access()[1] for r in middle):
                raise ValueError("switch bound register overwritten")
        else:
            raise ValueError("unreviewed switch bound")
        if index_table is not None:
            indices = read(index_table, maximum + 1)
            if max(indices) != count - 1 or set(indices) != set(range(count)):
                raise ValueError("sparse switch index range differs")
            load = next(
                (
                    r
                    for r in rows[guard_position + 1 : position]
                    if r.mnemonic == "movzx"
                ),
                None,
            )
            if (
                load is None
                or load.operands[0].reg != op.mem.index
                or load.operands[1].type != x.X86_OP_MEM
                or load.operands[1].size != 1
                or load.operands[1].mem.disp != index_table
                or load.operands[1].mem.base != bound.operands[0].reg
            ):
                raise ValueError("sparse index does not feed the destination table")
        elif op.mem.index != bound.operands[0].reg or count != maximum + 1:
            raise ValueError("checked index does not feed the destination table")
        destinations = list(struct.unpack("<" + "I" * count, read(table, count * 4)))
        switches[address] = destinations
        facts.append(
            {
                "instruction": hex(address),
                "guard": hex(guard.address),
                "table": hex(table),
                "count": count,
                "checked_maximum": maximum,
                "index_table": None if index_table is None else hex(index_table),
                "destinations": [hex(a) for a in destinations],
            }
        )
    edges = graph(rows, switches)
    visited = reachable(edges, ADDRESS)
    if visited != set(by_address):
        raise ValueError("owned code contains unreachable instructions")
    calls = direct_calls(rows)
    if (
        len(rows) != 10670
        or sum(row.size for row in rows) != 46128
        or sum(len(sites) for sites in calls.values()) != 404
        or len(calls) != 25
        or sum(row.group(capstone.CS_GRP_RET) for row in rows) != 68
    ):
        raise ValueError("complete instruction/call/return census differs")
    phantom = by_address[0x49C35A]
    if phantom.bytes != b"\xd9\xe8" or phantom.mnemonic != "fld1":
        raise ValueError("raw E8 counterexample differs")
    return {
        "schema": "th105-reimu-object-update-target-v1",
        "target_sha256": TARGET_SHA,
        "address": hex(ADDRESS),
        "extent_end": hex(END),
        "extent_sha256": EXTENT_SHA,
        "owned_bytes": 46128,
        "ranges": [[hex(a), hex(b)] for a, b in RANGES],
        "reachable_instructions": len(visited),
        "direct_call_sites": 404,
        "direct_call_targets": len(calls),
        "returns": 68,
        "switches": facts,
        "calls": [
            {"target": hex(a), "sites": [hex(s) for s in sites]}
            for a, sites in sorted(calls.items())
        ],
        "raw_e8_counterexample": {
            "byte_address": "0x49c35b",
            "raw_target": "0x4c611d",
            "instruction": "0x49c35a",
            "encoding": "d9e8",
            "mnemonic": "fld1",
        },
        "support_sha256": {
            str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in (Path(__file__), ROOT / "config/function-byte-ownership.toml")
        },
        "capstone_version": capstone.__version__,
        "scope": "complete target decoding and conservative CFG closure; no path feasibility, "
        "stack/ABI proof, source comparison, implementation or exact credit",
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = audit()
    except (OSError, ValueError, KeyError, StopIteration, struct.error) as exc:
        parser.exit(2, f"ReimuObject update target audit failed: {exc}\n")
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(
            "ReimuObject496540: 46128 owned bytes /10670 reachable instructions; "
            "22 switches /404 direct calls /25 callees /68 RETs"
        )
        print("Target-only evidence; no source or exact-match claim.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
