#!/usr/bin/env python3
"""Audit the complete JP1.06a IkuObject update and its twenty-five switch tables.

Target observations and whole-section canonical comparison stay separate. No masking
or partial-function exact credit is supported.
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

ROOT=Path(__file__).resolve().parents[1]
START,MAIN,FULL=0x632C30,33617,34524
UNIT="exact-first-iku-object-update"
SYMBOL="?update_action_state@IkuObjectUpdateView@th105@@UAEXXZ"
MAIN_SHA="138baaf0eb38d0e9c40e3dbace9bf7c89ca77bcd520f01a01d79d5ba29368ddf"
FULL_SHA="7c578a068ac0dac2e594bcadcf05671ced799940e8c730f0998c9657bd04525a"
TABLE_WORDS=(30, 7, 6, 5, 6, 5, 7, 10, 5, 4, 6, 7, 5, 6, 9, 7, 8, 4, 9, 4, 4, 4, 9, 4, 5)
TARGET_TABLES=(6532996, 6533316, 6533344, 6533368, 6533388, 6533412, 6533432, 6533460, 6533500, 6533520, 6533536, 6533560, 6533588, 6533608, 6533632, 6533668, 6533696, 6533728, 6533744, 6533780, 6533796, 6533812, 6533828, 6533864, 6533880)
TARGET_CALLS={5600704: 19, 4411744: 36, 4411840: 16, 4220880: 70, 4809632: 28, 4571184: 7, 6606000: 56, 6606080: 18, 6499344: 2, 4809584: 2, 4220224: 5, 4414816: 15, 5964800: 9, 4219744: 7, 4411968: 1, 5114864: 1, 5229152: 6, 4219856: 4, 6857120: 8, 5228304: 3, 4689360: 1, 5491648: 1, 4412704: 1}
PADDING={6529021: '8d4900'}


def load_compare():
    spec=importlib.util.spec_from_file_location("iku_update_canonical",ROOT/"scripts/compare-function.py")
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def inventory(raw, expected_words=TABLE_WORDS):
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail=True
    prefix=list(decoder.disasm(raw[:256],START))
    primary=next(i.operands[0].mem.disp for i in prefix
                 if i.mnemonic=="jmp" and i.operands[0].type==x86.X86_OP_MEM)
    if not START<primary<START+len(raw):
        raise ValueError("primary table escapes complete payload")
    rows=list(decoder.disasm(raw[:primary-START],START))
    if sum(i.size for i in rows)!=primary-START:
        raise ValueError("incomplete instruction/alignment decoding")
    row_addresses={i.address for i in rows}
    remap=next(i.operands[1].mem.disp for i in prefix
               if i.mnemonic=="movzx" and i.operands[1].type==x86.X86_OP_MEM)
    starts=sorted({i.operands[0].mem.disp for i in rows
                   if i.mnemonic=="jmp" and i.operands[0].type==x86.X86_OP_MEM})
    if (expected_words is not None and len(starts)!=len(expected_words)) or starts[0]!=primary:
        raise ValueError("expected twenty-five complete destination tables")
    tables={}
    spans=[(remap,remap+200)]
    for index,address in enumerate(starts):
        limit=remap if index==0 else (starts[index+1] if index+1<len(starts) else START+len(raw))
        if not primary<=address<limit<=START+len(raw):
            raise ValueError("destination table extent escapes payload")
        destinations=[]
        while address+len(destinations)*4+4<=limit:
            value=struct.unpack_from("<I",raw,address-START+len(destinations)*4)[0]
            if value not in row_addresses:
                break
            destinations.append(value)
        if not destinations or address+len(destinations)*4!=limit or (expected_words is not None and len(destinations)!=expected_words[index]):
            raise ValueError("reviewed destination count or code destination changed")
        tables[address]=destinations
        spans.append((address,address+len(destinations)*4))
    if not primary<=remap<remap+200<=START+len(raw):
        raise ValueError("primary remap extent escapes payload")
    indices=raw[remap-START:remap-START+199]
    if max(indices)>=len(tables[primary]):
        raise ValueError("primary remap index outside destination table")
    spans.sort()
    if spans[0][0]!=primary or spans[-1][1]!=START+len(raw) or any(
            left[1]!=right[0] for left,right in zip(spans,spans[1:])):
        raise ValueError("metadata has a gap, overlap or truncated tail")
    calls=Counter(i.operands[0].imm for i in rows
                  if i.mnemonic=="call" and i.operands[0].type==x86.X86_OP_IMM)
    result=dict(main_and_alignment=primary-START,instructions=len(rows),
                returns=sum(i.mnemonic=="ret" for i in rows),
                virtual_calls=sum(i.mnemonic=="call" and i.operands[0].type!=x86.X86_OP_IMM for i in rows),
                direct_calls={hex(a):n for a,n in sorted(calls.items())},
                tables=[dict(address=hex(a),dwords=len(ds)) for a,ds in tables.items()],
                remap_address=hex(remap),remap_bytes=199,remap_alignment_hex=raw[remap-START+199:remap-START+200].hex(),
                remap_sha256=hashlib.sha256(indices).hexdigest(),
                cases={str(n+800):hex(tables[primary][k]) for n,k in enumerate(indices)},
                stack_allocation=[i.operands[1].imm for i in rows[:12]
                                  if i.mnemonic=="sub" and i.operands[0].reg==x86.X86_REG_ESP])
    return rows,tables,result


def closed_cfg(rows,tables):
    by_address={i.address:i for i in rows if i.address<START+MAIN}
    visited,pending=set(),[START]
    while pending:
        address=pending.pop()
        if address in visited:
            continue
        if address not in by_address:
            raise ValueError("CFG edge escapes callable instruction boundary")
        row=by_address[address]
        visited.add(address)
        after=address+row.size
        if row.mnemonic=="ret":
            if row.op_str:
                raise ValueError("expected RET0")
        elif row.mnemonic=="jmp":
            pending.extend(tables[row.operands[0].mem.disp] if row.operands[0].type==x86.X86_OP_MEM else [row.operands[0].imm])
        elif row.group(capstone.CS_GRP_JUMP):
            pending.extend([row.operands[0].imm,after])
        else:
            pending.append(after)
    covered=sum(by_address[a].size for a in visited)
    padding=check_unreachable(by_address,visited)
    if covered!=MAIN-3 or len(visited)!=7903:
        raise ValueError("reviewed reachable instruction/byte count changed")
    return dict(reachable_instructions=len(visited),reachable_bytes=covered,
                unreachable_bytes=MAIN-covered,reviewed_padding=padding,
                returns=sum(by_address[a].mnemonic=="ret" for a in visited))


def check_unreachable(by_address,visited,expected=None):
    expected=PADDING if expected is None else expected
    actual={address:bytes(row.bytes).hex() for address,row in by_address.items() if address not in visited}
    if actual!=expected:
        raise ValueError("unreviewed unreachable callable bytes")
    return {hex(address):value for address,value in sorted(actual.items())}


def target_facts(compare):
    identity=compare.verify_target()
    raw=compare.target_bytes(START,FULL)
    if hashlib.sha256(raw).hexdigest()!=FULL_SHA or hashlib.sha256(raw[:MAIN]).hexdigest()!=MAIN_SHA:
        raise ValueError("reviewed target span changed")
    if struct.unpack("<I",compare.target_bytes(0x6C64CC,4))[0]!=START:
        raise ValueError("IkuObject slot28 changed")
    if struct.unpack("<I",compare.target_bytes(0x6C64E0,4))[0]!=0x63B310:
        raise ValueError("following independent initializer entry changed")
    if compare.target_bytes(START-5,5)!=b"\xcc"*5 or compare.target_bytes(START+FULL,4)!=b"\xcc"*4:
        raise ValueError("reviewed separating INT3 bytes changed")
    rows,tables,facts=inventory(raw)
    if tuple(tables)!=TARGET_TABLES or facts["direct_calls"]!={hex(a):n for a,n in sorted(TARGET_CALLS.items())}:
        raise ValueError("reviewed target table/call inventory changed")
    if facts["returns"]!=44 or facts["virtual_calls"]!=15 or facts["stack_allocation"]!=[0x258]:
        raise ValueError("reviewed target return, virtual-call or frame inventory changed")
    if compare.target_bytes(0x63B0C3,1)!=b"\x90":
        raise ValueError("reviewed remap alignment changed")
    return identity,raw,facts,closed_cfg(rows,tables)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object",type=Path)
    parser.add_argument("--target-only",action="store_true")
    args=parser.parse_args()
    try:
        compare=load_compare()
        identity,target,observations,cfg=target_facts(compare)
        report=dict(target_sha256=identity,callable_size=MAIN,complete_payload_size=FULL,
                    target_payload_sha256=FULL_SHA,target_inventory=observations,target_cfg=cfg,
                    canonical_acceptance=False)
        if args.target_only:
            report["result"]="observed_target_bytes"
        else:
            unit=load_manifest()["units"][UNIT]
            function=unit["functions"][0]
            if int(function["address"],0)!=START or function["symbol_base"]!=SYMBOL:
                raise ValueError("configured root changed")
            targets=compare.known_targets()
            for binding in function["rel32_targets"]:
                name,address=binding.rsplit("=",1)
                targets[name]=int(address,0)
            overrides=dict(binding.split("=",1) for binding in function["dir32_targets"])
            candidate=compare.coff_symbol_bytes(args.object or ROOT/unit["object"],SYMBOL,
                        START,0xFFFFFFFF,targets,compare.known_data_targets(),overrides)
            report.update(result="exact" if candidate==target else "mismatch",
                          object_section_tail_size=len(candidate),all_section_relocations_replayed=True,
                          canonical_payload_sha256=hashlib.sha256(candidate).hexdigest(),
                          first_mismatch=compare.first_mismatch(target,candidate,START),
                          unmasked_differing_bytes=sum(a!=b for a,b in zip(target,candidate))+abs(len(target)-len(candidate)),
                          candidate_inventory=inventory(candidate,None)[2])
            report["canonical_acceptance"]=candidate==target
    except (OSError,ValueError,RuntimeError,KeyError,StopIteration,struct.error) as error:
        print(json.dumps(dict(result="blocked",error=str(error)),indent=2))
        return 1
    print(json.dumps(report,indent=2))
    return 0 if args.target_only or report["result"]=="exact" else 1


if __name__=="__main__":
    raise SystemExit(main())
