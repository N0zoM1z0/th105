#!/usr/bin/env python3
"""Audit the complete JP1.06a SakuyaObject update and its seven switch tables.

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
START,MAIN,FULL=0x4E0D30,28985,29476
UNIT="exact-first-sakuya-object-update"
SYMBOL="?update_action_state@SakuyaObjectUpdateView@th105@@UAEXXZ"
MAIN_SHA="592df4424de962d219caa2e73d62ab420ed0d0438ba009b20b94f4b9df51ca94"
FULL_SHA="453a7abb8a48642f5852078059893f8611d26b07c77ae67d8747c4fadcd42ce3"
TABLE_WORDS=(33,5,5,7,9,4,9)
TARGET_TABLES=(0x4E7E6C,0x4E7FB8,0x4E7FCC,0x4E7FE0,0x4E7FFC,0x4E8020,0x4E8030)
TARGET_CALLS={0x5575C0:12,0x435160:27,0x45C030:40,0x4067D0:34,0x496420:13,
              0x4963F0:13,0x4351C0:17,0x4963A0:9,0x4FCA60:6,0x496370:3,
              0x435D60:3,0x406540:23,0x4E0BF0:2,0x465190:3,0x4063D0:6,
              0x406360:6,0x64CCB0:8,0x406580:4,0x478DD0:2,0x53CBC0:1}


def load_compare():
    spec=importlib.util.spec_from_file_location("sakuya_update_canonical",ROOT/"scripts/compare-function.py")
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def inventory(raw):
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
    if len(starts)!=7 or starts[0]!=primary:
        raise ValueError("expected seven complete destination tables")
    tables={}
    spans=[(remap,remap+200)]
    for index,address in enumerate(starts):
        limit=starts[index+1] if index+1<len(starts) else START+len(raw)
        if not primary<=address<limit<=START+len(raw):
            raise ValueError("destination table extent escapes payload")
        destinations=[]
        while address+len(destinations)*4+4<=limit:
            value=struct.unpack_from("<I",raw,address-START+len(destinations)*4)[0]
            if value not in row_addresses:
                break
            destinations.append(value)
        if len(destinations)!=TABLE_WORDS[index]:
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
    if covered!=MAIN or len(visited)!=6774:
        raise ValueError("unreviewed unreachable callable bytes")
    return dict(reachable_instructions=len(visited),reachable_bytes=covered,
                unreachable_bytes=MAIN-covered,
                returns=sum(by_address[a].mnemonic=="ret" for a in visited))


def target_facts(compare):
    identity=compare.verify_target()
    raw=compare.target_bytes(START,FULL)
    if hashlib.sha256(raw).hexdigest()!=FULL_SHA or hashlib.sha256(raw[:MAIN]).hexdigest()!=MAIN_SHA:
        raise ValueError("reviewed target span changed")
    if struct.unpack("<I",compare.target_bytes(0x6C48B4,4))[0]!=START:
        raise ValueError("SakuyaObject slot28 changed")
    if struct.unpack("<I",compare.target_bytes(0x6C48C8,4))[0]!=0x4E8060:
        raise ValueError("following independent initializer entry changed")
    rows,tables,facts=inventory(raw)
    if tuple(tables)!=TARGET_TABLES or facts["direct_calls"]!={hex(a):n for a,n in sorted(TARGET_CALLS.items())}:
        raise ValueError("reviewed target table/call inventory changed")
    if facts["returns"]!=47 or facts["virtual_calls"]!=48 or facts["stack_allocation"]!=[0xD0]:
        raise ValueError("reviewed target return, virtual-call or frame inventory changed")
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
                          candidate_inventory=inventory(candidate)[2])
            report["canonical_acceptance"]=candidate==target
    except (OSError,ValueError,RuntimeError,KeyError,StopIteration,struct.error) as error:
        print(json.dumps(dict(result="blocked",error=str(error)),indent=2))
        return 1
    print(json.dumps(report,indent=2))
    return 0 if args.target_only or report["result"]=="exact" else 1


if __name__=="__main__":
    raise SystemExit(main())
