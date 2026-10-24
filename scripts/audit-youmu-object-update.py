#!/usr/bin/env python3
"""Compare the complete YoumuObject update hypothesis and its switch metadata.

Replay every relocation and compare every payload byte. Inventory diagnostics
neither mask differences nor promote the hypothesis into the tracking ledgers.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-youmu-object-update"
ADDRESS, CALLABLE_SIZE, PAYLOAD_SIZE = 0x53CEA0,25944,26576
PAYLOAD_SHA256 = "4cc99136a6fc0fc7238c89bde5509d3504be026086b5f35a97cf219973a5911b"


def load_candidate(object_path=None):
    spec = importlib.util.spec_from_file_location(
        "youmu_update_canonical_comparator",ROOT/"scripts/compare-function.py")
    if spec is None or spec.loader is None:
        raise RuntimeError("canonical comparator is unavailable")
    comparator = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(comparator)
    identity = comparator.verify_target()
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    if int(function["address"],0) != ADDRESS:
        raise ValueError("configured root address changed")
    if object_path is None:
        object_path = ROOT/unit["object"]
    targets = comparator.known_targets()
    for binding in function.get("rel32_targets",[]):
        name,address = binding.rsplit("=",1)
        targets[name] = int(address,0)
    candidate = comparator.coff_symbol_bytes(
        object_path,function["symbol_base"],ADDRESS,0xFFFFFFFF,
        targets,comparator.known_data_targets())
    target = comparator.target_bytes(ADDRESS,PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("reviewed complete target payload changed")
    return comparator,identity,candidate,target


def candidate_inventory(candidate,target):
    decoder = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail = True
    prefix = list(decoder.disasm(candidate[:64],ADDRESS))
    primary = next(i.operands[0].mem.disp for i in prefix
                   if i.mnemonic=="jmp" and i.operands[0].type==x86.X86_OP_MEM)
    remap_address = next(i.operands[1].mem.disp for i in prefix
                         if i.mnemonic=="movzx" and i.operands[1].type==x86.X86_OP_MEM)
    if not ADDRESS < primary <= ADDRESS+len(candidate):
        raise ValueError("candidate primary table outside emitted payload")
    if not primary <= remap_address <= ADDRESS+len(candidate)-200:
        raise ValueError("candidate remap outside emitted metadata")
    instructions = list(decoder.disasm(candidate[:primary-ADDRESS],ADDRESS))
    if sum(i.size for i in instructions) != primary-ADDRESS:
        raise ValueError("candidate callable/alignment decoding is incomplete")
    starts = sorted({i.operands[0].mem.disp for i in instructions
                     if i.mnemonic=="jmp" and i.operands[0].type==x86.X86_OP_MEM})
    tables = []
    for address in starts:
        limit = min([a for a in starts if a>address]+[ADDRESS+len(candidate)])
        if address < remap_address:
            limit = min(limit,remap_address)
        count = 0
        while address+count*4+4<=limit:
            destination = struct.unpack_from("<I",candidate,address+count*4-ADDRESS)[0]
            if not ADDRESS <= destination < primary:
                break
            count += 1
        tables.append(dict(address=hex(address),dwords=count))
    calls = Counter(i.operands[0].imm for i in instructions
                    if i.mnemonic=="call" and i.operands[0].type==x86.X86_OP_IMM)
    remap = candidate[remap_address-ADDRESS:remap_address-ADDRESS+200]
    return dict(
        diagnostic_only=True,code_and_alignment_to_first_table=primary-ADDRESS,
        instructions=len(instructions),returns=sum(i.mnemonic=="ret" for i in instructions),
        direct_calls={hex(a):n for a,n in sorted(calls.items())},
        virtual_calls=sum(i.mnemonic=="call" and i.operands[0].type!=x86.X86_OP_IMM
                          for i in instructions),
        table_extents=tables,remap_200_bytes_equal=remap==target[0x65CC:0x6694],
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object",type=Path,help="override the configured COFF object")
    args = parser.parse_args()
    try:
        comparator,identity,candidate,target = load_candidate(args.object)
        exact = len(candidate)==len(target) and candidate==target
        report = dict(
            result="exact" if exact else "mismatch",unit=UNIT,target_sha256=identity,
            callable_size=CALLABLE_SIZE,complete_payload_size=PAYLOAD_SIZE,
            object_section_tail_size=len(candidate),all_section_relocations_replayed=True,
            first_mismatch=comparator.first_mismatch(target,candidate,ADDRESS),
            unmasked_differing_bytes=sum(a!=b for a,b in zip(target,candidate))+abs(len(target)-len(candidate)),
            canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
            candidate_inventory=candidate_inventory(candidate,target),
        )
    except (OSError,ValueError,RuntimeError,StopIteration,struct.error) as error:
        print(json.dumps(dict(result="blocked",error=str(error)),indent=2))
        return 1
    print(json.dumps(report,indent=2))
    return 0 if exact else 1


if __name__ == "__main__":
    raise SystemExit(main())
