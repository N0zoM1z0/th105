#!/usr/bin/env python3
"""Audit the complete JP1.06a KomachiObject update and its fifteen switch tables.

Target observations and full canonical comparison remain separate. No masking
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
START,MAIN,FULL=0x5F9420,27874,28520
UNIT="exact-first-komachi-object-update"
SYMBOL="?update_action_state@KomachiObjectUpdateView@th105@@UAEXXZ"
MAIN_SHA="22f3ca6f2c23e5b1b9be280869a611f54930f55d447de2486e42367de76c48c2"
FULL_SHA="c5bed7baea5bbb97517f1bdebdaad6451db1491222180f16a705e767e8ae5b54"
TABLE_WORDS=(28, 5, 6, 5, 4, 6, 5, 6, 5, 5, 7, 14, 4, 4, 7)
TARGET_TABLES=(6291716, 6292028, 6292048, 6292072, 6292092, 6292108, 6292132, 6292152, 6292176, 6292196, 6292216, 6292244, 6292300, 6292316, 6292332)
TARGET_CALLS={5600704: 13, 4411744: 34, 4571184: 6, 4220880: 90, 4411840: 10, 6263632: 10, 4219744: 30, 4219856: 10, 4809632: 19, 6606000: 63, 6606080: 5, 4414816: 5, 4412704: 6, 4220224: 2, 4220288: 4, 6263568: 5, 4413904: 1, 5114864: 1, 5491648: 1}
PADDING={6268413: '8d4900', 6273341: '8d4900', 6285245: '8d4900', 6288295: 'eb07', 6288297: '8da42400000000', 6289231: '90', 6289677: '8d4900'}


def load_compare():
    spec=importlib.util.spec_from_file_location("komachi_update_canonical",ROOT/"scripts/compare-function.py")
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def height_call_captures(rows):
    """Report adjacent qword store/call/compare facts, not execution equivalence."""
    result=[]
    for store,call,compare in zip(rows,rows[1:],rows[2:]):
        if (store.mnemonic!="fstp" or call.mnemonic!="call" or compare.mnemonic!="fcomp"
                or call.operands[0].type!=x86.X86_OP_IMM or call.operands[0].imm!=0x435D60):
            continue
        before,after=store.operands[0],compare.operands[0]
        if (before.type!=x86.X86_OP_MEM or after.type!=x86.X86_OP_MEM
                or before.size!=8 or after.size!=8
                or before.mem.base!=x86.X86_REG_ESP or after.mem.base!=x86.X86_REG_ESP
                or before.mem.index or after.mem.index or before.mem.disp!=after.mem.disp
                or store.address+store.size!=call.address
                or call.address+call.size!=compare.address):
            continue
        result.append(dict(store=hex(store.address),call=hex(call.address),
                           compare=hex(compare.address),width=8,esp_displacement=before.mem.disp))
    return result


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
        raise ValueError("expected fifteen complete destination tables")
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
                height_call_captures=height_call_captures(rows),
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
    if covered!=MAIN-22 or len(visited)!=6773:
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
    if struct.unpack("<I",compare.target_bytes(0x6C6004,4))[0]!=START:
        raise ValueError("KomachiObject slot28 changed")
    if struct.unpack("<I",compare.target_bytes(0x6C6018,4))[0]!=0x600390:
        raise ValueError("following independent initializer entry changed")
    if compare.target_bytes(START-3,3)!=b"\xcc"*3 or compare.target_bytes(START+FULL,8)!=b"\xcc"*8:
        raise ValueError("reviewed separating INT3 bytes changed")
    rows,tables,facts=inventory(raw)
    if tuple(tables)!=TARGET_TABLES or facts["direct_calls"]!={hex(a):n for a,n in sorted(TARGET_CALLS.items())}:
        raise ValueError("reviewed target table/call inventory changed")
    if facts["returns"]!=37 or facts["virtual_calls"]!=6 or facts["stack_allocation"]!=[0x40]:
        raise ValueError("reviewed target return, virtual-call or frame inventory changed")
    if [int(item["call"],16) for item in facts["height_call_captures"]]!=[0x5F9F4E,0x5FAC3F,0x5FAEA7,0x5FFF81]:
        raise ValueError("reviewed pre-height-call qword captures changed")
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
