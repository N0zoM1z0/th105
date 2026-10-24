#!/usr/bin/env python3
"""Attest the complete raw YoumuObject slot28 target before source selection.

This is a read-only target/CFG packet, not a source, COFF or exact-match claim.
It requires the canonical private executable and does not use an analysis GUI.
"""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86

ROOT = Path(__file__).resolve().parents[1]
START, END, PAYLOAD_END = 0x53CEA0, 0x5433F8, 0x543670
TABLES = (
    (0x5433F8,29),(0x543534,5),(0x543548,6),(0x543560,5),
    (0x543574,13),(0x5435A8,4),(0x5435B8,4),(0x5435C8,6),
    (0x5435E0,9),(0x543604,11),(0x543630,8),(0x543650,8),
)
DIRECT_CALL_COUNTS = {
    0x435160:18,0x45C030:13,0x64CCB0:58,0x5575C0:8,0x4063D0:10,
    0x4351C0:16,0x68A1A0:8,0x4FC710:3,0x435240:1,0x5B0400:4,
    0x4963A0:10,0x4067D0:49,0x64CD00:4,0x406360:11,0x406540:3,
    0x53CDF0:1,0x4E0BF0:1,0x406580:3,0x53CBC0:1,0x435D60:2,
}
VIRTUAL_SLOTS = {
    0x53D09B:0x20,0x53D373:0x20,0x53D6E7:0x20,0x53D6FA:0x1C,
    0x53DCEF:0x0C,0x53DE09:0x0C,0x53F4B1:0x0C,0x53F791:0x0C,
    0x53F88E:0x0C,0x53F99A:0x0C,0x53F9D3:0x0C,0x53F9F5:0x0C,
    0x53FC48:0x0C,0x53FC9C:0x0C,0x53FD73:0x0C,0x53FFFE:0x0C,
    0x54005C:0x0C,0x540094:0x0C,0x540175:0x0C,0x5408B3:0x14,
    0x5409E4:0x0C,0x541352:0x20,0x54137D:0x20,0x541CA3:0x20,
    0x541CE7:0x20,0x5428A5:0x14,0x542C1C:0x14,0x542CFC:0x20,
    0x5432C4:0x0C,0x5432E4:0x14,
}
UNREACHABLE_ALIGNMENT = {
    0x53EE2A:"8d9b00000000",0x5420DA:"8d9b00000000",
    0x542F29:"8da42400000000",
}


def audit():
    spec = importlib.util.spec_from_file_location(
        "youmu_update_target_bytes",ROOT/"scripts/compare-function.py")
    if spec is None or spec.loader is None:
        raise ValueError("canonical comparator unavailable")
    target = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(target)
    identity = target.verify_target()
    body = target.target_bytes(START,END-START)
    payload = target.target_bytes(START,PAYLOAD_END-START)
    if hashlib.sha256(body).hexdigest() != "c3334cf4f772931661dfddf7ffd6adb702b99aedf369809f11e8ec1d0171492e":
        raise ValueError("reviewed main target bytes changed")
    if hashlib.sha256(payload).hexdigest() != "4cc99136a6fc0fc7238c89bde5509d3504be026086b5f35a97cf219973a5911b":
        raise ValueError("reviewed complete payload changed")
    if struct.unpack("<I",target.target_bytes(0x6C50E4,4))[0] != START:
        raise ValueError("RTTI-owned YoumuObject slot28 no longer points to root")
    if struct.unpack("<I",target.target_bytes(0x6C50F8,4))[0] != PAYLOAD_END:
        raise ValueError("following independent slot3C initializer entry changed")

    decoder = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail = True
    instructions = {i.address:i for i in decoder.disasm(body,START)}
    if len(instructions) != 6236 or sum(i.size for i in instructions.values()) != len(body):
        raise ValueError("bounded instruction decoding changed")
    tables = {a:struct.unpack("<"+str(n)+"I",target.target_bytes(a,n*4)) for a,n in TABLES}
    remap = target.target_bytes(0x54346C,200)
    if max(remap) != 28 or any(d not in instructions for ds in tables.values() for d in ds):
        raise ValueError("table destination outside the reviewed instruction set")
    # Metadata partitions the entire tail: no guessed adjacency or padding.
    spans = sorted([(a,a+n*4) for a,n in TABLES]+[(0x54346C,0x543534)])
    if spans[0][0] != END or spans[-1][1] != PAYLOAD_END or any(
            left[1] != right[0] for left,right in zip(spans,spans[1:])):
        raise ValueError("reviewed metadata has a gap or overlap")
    jumps, calls, virtual, returns = set(), {}, [], []
    for i in instructions.values():
        if i.mnemonic == "jmp" and i.operands[0].type == x86.X86_OP_MEM:
            jumps.add(i.operands[0].mem.disp)
        if i.mnemonic == "call":
            if i.operands[0].type == x86.X86_OP_IMM:
                calls.setdefault(i.operands[0].imm,[]).append(i.address)
            else:
                virtual.append(i.address)
        if i.mnemonic == "ret":
            if i.op_str:
                raise ValueError("RET0 contract changed")
            returns.append(i.address)
    if jumps != set(tables) or {a:len(sites) for a,sites in calls.items()} != DIRECT_CALL_COUNTS:
        raise ValueError("physical jump/call inventory changed")
    if set(virtual) != set(VIRTUAL_SLOTS) or len(returns) != 49:
        raise ValueError("indirect-call/return inventory changed")

    visited, pending = set(), [START]
    while pending:
        address = pending.pop()
        if address in visited:
            continue
        if address not in instructions:
            raise ValueError(f"edge outside reviewed main instructions: {address:#x}")
        visited.add(address)
        i = instructions[address]
        if i.mnemonic == "ret":
            successors = []
        elif i.mnemonic == "jmp":
            successors = tables[i.operands[0].mem.disp] if i.operands[0].type == x86.X86_OP_MEM else [i.operands[0].imm]
        elif i.group(capstone.CS_GRP_JUMP):
            successors = [i.operands[0].imm,address+i.size]
        else:
            successors = [address+i.size]
        pending.extend(successors)
    unreachable = set(instructions)-visited
    if {a:instructions[a].bytes.hex() for a in unreachable} != UNREACHABLE_ALIGNMENT:
        raise ValueError("unreviewed unreachable bytes in the main extent")
    if len(visited) != 6233:
        raise ValueError("reviewed reachable instruction count changed")
    with (ROOT/"config/functions.csv").open(newline="") as stream:
        ledger = {int(r["address"],0):r for r in csv.DictReader(stream)}
    return dict(
        evidence_class="observed_target_bytes",source_claim=False,canonical_acceptance=False,
        target_sha256=identity,address=f"0x{START:08X}",main_size=len(body),
        main_sha256=hashlib.sha256(body).hexdigest(),payload_size=len(payload),
        payload_sha256=hashlib.sha256(payload).hexdigest(),instructions=len(instructions),
        reachable=len(visited),unreachable_alignment=[hex(a) for a in sorted(unreachable)],ret0_sites=[hex(a) for a in returns],
        table_extents=[dict(address=hex(a),dwords=n) for a,n in TABLES],
        cases={str(n+800):hex(tables[0x5433F8][k]) for n,k in enumerate(remap)},
        direct_calls=[dict(address=hex(a),sites=[hex(s) for s in sites],
                           ledger_name=ledger.get(a,{}).get("proposed_name",""),
                           ledger_status=ledger.get(a,{}).get("status","untracked"))
                      for a,sites in sorted(calls.items())],
        virtual_calls=[dict(site=hex(a),observed_slot=hex(VIRTUAL_SLOTS[a])) for a in virtual],
        unknowns=["original source and return type","complete owner layout",
                  "original TU/compiler boundary","full execution equivalence and compiler-context recovery"],
    )


def main():
    try:
        report = audit()
    except (OSError,ValueError,KeyError) as error:
        print(json.dumps(dict(result="blocked",error=str(error)),indent=2))
        return 1
    print(json.dumps(report,indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
