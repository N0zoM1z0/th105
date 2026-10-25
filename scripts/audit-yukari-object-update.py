#!/usr/bin/env python3
"""Audit the complete JP1.06a YukariObject update and its twenty switch tables.

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
START,MAIN,FULL=0x58DB80,33972,34800
UNIT="exact-first-yukari-object-update"
SYMBOL="?update_action_state@YukariObjectUpdateView@th105@@UAEXXZ"
MAIN_SHA="8b43493cedfa766b141c4834245b7a8c2d68a63900d0da6734657ba3dde5678e"
FULL_SHA="d809538c763402e688b3a7ebf53c58ab67ebec0ac5e552b745495947c334ee64"
TABLE_WORDS=(33, 4, 9, 5, 6, 9, 7, 12, 7, 5, 5, 5, 5, 6, 6, 14, 6, 4, 5, 4)
TARGET_TABLES=(5857332, 5857664, 5857680, 5857716, 5857736, 5857760, 5857796, 5857824, 5857872, 5857900, 5857920, 5857940, 5857960, 5857980, 5858004, 5858028, 5858084, 5858108, 5858124, 5858144)
TARGET_CALLS={5600704: 21, 5376096: 13, 4411744: 23, 5964800: 13, 4411840: 15, 4809760: 4, 4809632: 13, 4220880: 39, 6606000: 52, 4809712: 1, 4809584: 1, 4414816: 10, 4413904: 2, 4571184: 15, 4219856: 19, 4219744: 15, 5114864: 1, 5229152: 4, 4220224: 2, 4220288: 2, 4220320: 1, 4220032: 2, 6606080: 3, 5491648: 1}
PADDING={}


def load_compare():
    spec=importlib.util.spec_from_file_location("yukari_update_canonical",ROOT/"scripts/compare-function.py")
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
        raise ValueError("expected twenty complete destination tables")
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
    indices=raw[remap-START:remap-START+200]
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
                remap_address=hex(remap),remap_bytes=200,
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
    if covered!=MAIN or len(visited)!=7985:
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


def check_default_exit(rows,entry):
    """The native default advances once and ignores AL before a plain RET0."""
    by_address={row.address:row for row in rows}
    chain=[]
    address=entry
    for _ in range(7):
        if address not in by_address:
            raise ValueError("default exit escapes instruction boundary")
        row=by_address[address]
        chain.append(row)
        address+=row.size
    if [row.mnemonic for row in chain]!=["call","pop","pop","pop","pop","add","ret"]:
        raise ValueError("default must ignore frame result and retain its plain exit")
    if chain[0].operands[0].type!=x86.X86_OP_IMM or chain[0].operands[0].imm!=0x4351C0:
        raise ValueError("default frame callee changed")
    if [row.operands[0].reg for row in chain[1:5]]!=[x86.X86_REG_EDI,x86.X86_REG_ESI,x86.X86_REG_EBP,x86.X86_REG_EBX]:
        raise ValueError("default saved-register exit changed")
    operands=chain[5].operands
    if operands[0].type!=x86.X86_OP_REG or operands[0].reg!=x86.X86_REG_ESP or operands[1].type!=x86.X86_OP_IMM or operands[1].imm!=0x260 or chain[6].op_str:
        raise ValueError("default frame restoration or RET0 changed")
    return dict(entry=hex(entry),frame_callee="0x4351c0",ignores_frame_result=True)


def quantized_return_facts(compare):
    # Local call-view admission, not recovery of original nominal prototypes.
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail=True
    result=[]
    for address,size,digest in (
            (0x406360,100,"b03e5be2d5e7b36fd141594a76773e2ba1481ecc299f92b7178d41c7a7d2f9e5"),
            (0x4063D0,94,"85296bac92963c839b2258ecbc61b460a8244f84097f18ea18877f6d6c8e68fe")):
        raw=compare.target_bytes(address,size)
        if hashlib.sha256(raw).hexdigest()!=digest:
            raise ValueError("quantized return provider changed")
        rows=list(decoder.disasm(raw,address))
        if sum(row.size for row in rows)!=size or sum(row.mnemonic=="ret" for row in rows)!=1:
            raise ValueError("quantized return extent changed")
        tail=rows[-4:]
        if [row.mnemonic for row in tail]!=["fld","mov","pop","ret"]:
            raise ValueError("quantized return tail changed")
        operand=tail[0].operands[0]
        if operand.type!=x86.X86_OP_MEM or operand.size!=4 or operand.mem.disp!=0x6FE8B0 or operand.mem.index!=x86.X86_REG_EDX or operand.mem.scale!=4 or tail[-1].op_str:
            raise ValueError("quantized return must load a table float into ST0 and RET0")
        result.append(dict(address=hex(address),size=size,sha256=digest,
                           return_load=hex(tail[0].address),return_width=4,table="0x6fe8b0"))
    return result


def target_facts(compare):
    identity=compare.verify_target()
    raw=compare.target_bytes(START,FULL)
    if hashlib.sha256(raw).hexdigest()!=FULL_SHA or hashlib.sha256(raw[:MAIN]).hexdigest()!=MAIN_SHA:
        raise ValueError("reviewed target span changed")
    if struct.unpack("<I",compare.target_bytes(0x6C586C,4))[0]!=START:
        raise ValueError("YukariObject slot28 changed")
    if struct.unpack("<I",compare.target_bytes(0x6C5880,4))[0]!=0x5964C0:
        raise ValueError("following independent initializer entry changed")
    if compare.target_bytes(START-4,4)!=b"\xcc"*4:
        raise ValueError("reviewed leading separation changed")
    if hashlib.sha256(compare.target_bytes(START+FULL,323)).hexdigest()!="1ae566c8e8a9230cc7ce1ff75a2b472ef0b4886b1f63786506b2735dadecd7bc":
        raise ValueError("independent following980 helper changed")
    rows,tables,facts=inventory(raw)
    if tuple(tables)!=TARGET_TABLES or facts["direct_calls"]!={hex(a):n for a,n in sorted(TARGET_CALLS.items())}:
        raise ValueError("reviewed target table/call inventory changed")
    if facts["returns"]!=88 or facts["virtual_calls"]!=45 or facts["stack_allocation"]!=[0x260]:
        raise ValueError("reviewed target return, virtual-call or frame inventory changed")
    facts["default_exit"]=check_default_exit(rows,tables[TARGET_TABLES[0]][-1])
    facts["quantized_return_providers"]=quantized_return_facts(compare)
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
