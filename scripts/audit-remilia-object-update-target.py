#!/usr/bin/env python3
"""Attest the complete raw RemiliaObject slot28 target before source selection.

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
START, END, PAYLOAD_END = 0x557690, 0x55BC11, 0x55BE64
TABLES = (
    (0x55BC14,28),(0x55BD4C,4),(0x55BD5C,5),(0x55BD70,8),
    (0x55BD90,5),(0x55BDA4,5),(0x55BDB8,8),(0x55BDD8,5),
    (0x55BDEC,5),(0x55BE00,11),(0x55BE2C,6),(0x55BE44,8),
)
DIRECT_CALL_COUNTS = {
    0x5575C0:9,0x4067D0:9,0x64CCB0:29,0x4351C0:9,0x496420:4,
    0x64CD00:5,0x4E0BF0:2,0x435160:23,0x5B0400:19,0x45C030:4,
    0x406540:3,0x68A1A0:3,0x406360:13,0x4063D0:13,0x435D60:12,
    0x53CBC0:1,
}
VIRTUAL_SLOTS = {
    0x5585F6:0x20,0x559625:0x0C,0x559A59:0x0C,
    0x55A4BC:0x20,0x55A974:0x20,0x55B82F:0x0C,
}


def audit():
    spec = importlib.util.spec_from_file_location(
        "remilia_update_target_bytes",ROOT/"scripts/compare-function.py")
    if spec is None or spec.loader is None:
        raise ValueError("canonical comparator unavailable")
    target = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(target)
    identity = target.verify_target()
    body = target.target_bytes(START,END-START)
    payload = target.target_bytes(START,PAYLOAD_END-START)
    if hashlib.sha256(body).hexdigest() != "b53af50d6bfdf124d8c16098abfa56c043f8cd1bca9606cc8d73b892610d4fe2":
        raise ValueError("reviewed main target bytes changed")
    if hashlib.sha256(payload).hexdigest() != "793c1954983d385b07ead1e850f95b4c521448100500074eaa0b371e2f3b0cd6":
        raise ValueError("reviewed complete payload changed")
    if target.target_bytes(END,3).hex() != "8d4900" or target.target_bytes(0x55BD4B,1).hex() != "90":
        raise ValueError("metadata alignment changed")
    if target.target_bytes(PAYLOAD_END,12) != bytes([0xCC])*12:
        raise ValueError("following callable separator changed")
    if struct.unpack("<I",target.target_bytes(0x6C5364,4))[0] != START:
        raise ValueError("RTTI-owned RemiliaObject slot28 no longer points to root")

    decoder = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail = True
    instructions = {i.address:i for i in decoder.disasm(body,START)}
    if len(instructions) != 4239 or sum(i.size for i in instructions.values()) != len(body):
        raise ValueError("bounded instruction decoding changed")
    tables = {a:struct.unpack("<"+str(n)+"I",target.target_bytes(a,n*4)) for a,n in TABLES}
    remap = target.target_bytes(0x55BC84,199)
    if max(remap) != 27 or any(d not in instructions for ds in tables.values() for d in ds):
        raise ValueError("table destination outside the reviewed instruction set")
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
    if set(virtual) != set(VIRTUAL_SLOTS) or len(returns) != 28:
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
    if unreachable != {0x55777D} or instructions[0x55777D].bytes.hex() != "8d4900":
        raise ValueError("unreviewed unreachable bytes in the main extent")
    with (ROOT/"config/functions.csv").open(newline="") as stream:
        ledger = {int(r["address"],0):r for r in csv.DictReader(stream)}
    return dict(
        evidence_class="observed_target_bytes",source_claim=False,canonical_acceptance=False,
        target_sha256=identity,address=f"0x{START:08X}",main_size=len(body),
        main_sha256=hashlib.sha256(body).hexdigest(),payload_size=len(payload),
        payload_sha256=hashlib.sha256(payload).hexdigest(),instructions=len(instructions),
        reachable=len(visited),unreachable_alignment=["0x0055777D"],ret0_sites=[hex(a) for a in returns],
        table_extents=[dict(address=hex(a),dwords=n) for a,n in TABLES],
        cases={str(n+800):hex(tables[0x55BC14][k]) for n,k in enumerate(remap)},
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
