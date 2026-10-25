#!/usr/bin/env python3
"""Audit the complete JP1.06a YuyukoObject update and its sixteen tables and seven bounded remaps.

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
START,MAIN,FULL=0x56F700,34278,35060
UNIT="exact-first-yuyuko-object-update"
SYMBOL="?update_action_state@YuyukoObjectUpdateView@th105@@UAEXXZ"
MAIN_SHA="5c6d0bac072dda180fac2f0d65b1f444381257ec8940d330e781cbd906052e8d"
FULL_SHA="606cd3d61fb4798f134297a76237c045d28ee45f215f9be95bfdb1984b24d7de"
TABLE_WORDS=(29, 5, 6, 6, 6, 8, 12, 3, 5, 3, 4, 10, 7, 6, 6, 5)
TARGET_TABLES=(5733608, 5733924, 5733964, 5733988, 5734028, 5734052, 5734104, 5734152, 5734176, 5734196, 5734220, 5734236, 5734276, 5734320, 5734344, 5734368)
TARGET_CALLS={5600704: 19, 4411744: 29, 4220880: 80, 6606000: 52, 4219744: 41, 4411840: 7, 4809760: 3, 4809632: 20, 5114864: 1, 4571184: 7, 4220224: 5, 4414816: 1, 6857120: 14, 5228304: 3, 4220288: 2, 4689360: 1, 4411968: 4, 4219856: 15, 6606080: 5, 4220080: 2, 4809584: 1, 5229152: 4, 5964800: 12, 5491648: 1}
PADDING={5702618: '8d9b00000000', 5704888: '8da42400000000', 5704895: '90', 5705913: '8da42400000000', 5706917: '8da42400000000', 5706924: '8d642400', 5710647: '8da42400000000', 5710654: '8bff', 5711671: '8da42400000000', 5711678: '8bff', 5719469: '8d4900', 5723005: '8d4900', 5723517: '8d4900', 5730183: '8da42400000000', 5730190: '8bff'}
REMAP_LENGTHS=(199,20,15,17,12,12,16)


def load_compare():
    spec=importlib.util.spec_from_file_location("yuyuko_update_canonical",ROOT/"scripts/compare-function.py")
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def inventory(raw, expected_words=TABLE_WORDS):
    """Decode guarded remaps and destination tables; never assume one primary remap."""
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
    starts=sorted({i.operands[0].mem.disp for i in rows
                   if i.mnemonic=="jmp" and i.operands[0].type==x86.X86_OP_MEM})
    if (expected_words is not None and len(starts)!=len(expected_words)) or starts[0]!=primary:
        raise ValueError("expected sixteen complete destination tables")
    remaps=[]
    for index,row in enumerate(rows):
        if row.mnemonic!="movzx" or row.operands[1].type!=x86.X86_OP_MEM or row.operands[1].size!=1:
            continue
        operand=row.operands[1].mem
        if operand.disp<primary:
            continue
        guard=None
        for prior in reversed(rows[max(0,index-8):index]):
            if (prior.mnemonic=="cmp" and prior.operands[0].type==x86.X86_OP_REG
                    and prior.operands[0].reg in (operand.base,operand.index)
                    and prior.operands[1].type==x86.X86_OP_IMM):
                guard=prior
                break
        if guard is None or not 0<=guard.operands[1].imm<512:
            raise ValueError("remap lacks reviewed bounded index")
        between=[i for i in rows[max(0,index-8):index] if i.address>guard.address]
        if not any(i.mnemonic=="ja" and i.operands[0].type==x86.X86_OP_IMM
                   and i.operands[0].imm in row_addresses for i in between):
            raise ValueError("remap lacks unsigned out-of-range edge")
        following=rows[index+1:index+4]
        jump=next((i for i in following if i.mnemonic=="jmp" and i.operands[0].type==x86.X86_OP_MEM),None)
        if jump is None or jump.operands[0].mem.index!=row.operands[0].reg:
            raise ValueError("remap does not feed destination table")
        address=operand.disp
        size=guard.operands[1].imm+1
        if not primary<=address<address+size<=START+len(raw):
            raise ValueError("remap extent escapes payload")
        remaps.append(dict(address=address,size=size,table=jump.operands[0].mem.disp,
                           guard=guard.address,load=row.address))
    remaps.sort(key=lambda row:row["address"])
    if not remaps or len({r["address"]for r in remaps})!=len(remaps):
        raise ValueError("missing or duplicate remap")
    if expected_words is not None and tuple(r["size"]for r in remaps)!=REMAP_LENGTHS:
        raise ValueError("reviewed seven remap bounds changed")
    boundaries=sorted(starts+[r["address"]for r in remaps]+[START+len(raw)])
    tables={}
    spans=[]
    for index,address in enumerate(starts):
        limit=next((b for b in boundaries if b>address),START+len(raw))
        if not primary<=address<limit<=START+len(raw):
            raise ValueError("destination table extent escapes payload")
        destinations=[]
        while address+len(destinations)*4+4<=limit:
            value=struct.unpack_from("<I",raw,address-START+len(destinations)*4)[0]
            if value not in row_addresses:
                break
            destinations.append(value)
        if not destinations or (expected_words is not None and len(destinations)!=expected_words[index]):
            raise ValueError("reviewed destination count or code destination changed")
        tables[address]=destinations
        spans.append((address,address+len(destinations)*4))
    reports=[]
    for remap in remaps:
        address,size,table=(remap[k]for k in ("address","size","table"))
        indices=raw[address-START:address-START+size]
        if table not in tables or max(indices)>=len(tables[table]):
            raise ValueError("remap index outside destination table")
        spans.append((address,address+size))
        reports.append(dict(address=hex(address),size=size,table=hex(table),
                            guard=hex(remap["guard"]),load=hex(remap["load"]),
                            sha256=hashlib.sha256(indices).hexdigest()))
    spans.sort()
    gaps=[]
    cursor=primary
    for begin,end in spans:
        if begin<cursor:
            raise ValueError("metadata overlap")
        if begin>cursor:
            gap=bytes(raw[cursor-START:begin-START]).hex()
            if gap not in ("90","8bff","8d4900"):
                raise ValueError("metadata has an unreviewed gap or truncated table")
            gaps.append(dict(address=hex(cursor),bytes=gap))
        cursor=end
    if cursor!=START+len(raw):
        raise ValueError("metadata has a truncated or unowned tail")
    primary_remap=next((r for r in remaps if r["table"]==primary),None)
    if primary_remap is None:
        raise ValueError("primary table lacks action remap")
    indices=raw[primary_remap["address"]-START:primary_remap["address"]-START+primary_remap["size"]]
    calls=Counter(i.operands[0].imm for i in rows
                  if i.mnemonic=="call" and i.operands[0].type==x86.X86_OP_IMM)
    result=dict(main_and_alignment=primary-START,instructions=len(rows),
                returns=sum(i.mnemonic=="ret" for i in rows),
                virtual_calls=sum(i.mnemonic=="call" and i.operands[0].type!=x86.X86_OP_IMM for i in rows),
                direct_calls={hex(a):n for a,n in sorted(calls.items())},
                tables=[dict(address=hex(a),dwords=len(ds)) for a,ds in tables.items()],
                remaps=reports,metadata_gaps=gaps,remap_bytes=primary_remap["size"],
                total_remap_bytes=sum(r["size"]for r in remaps),
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
    if covered!=34210 or len(visited)!=8032:
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


def call_ownership(rows,tables,cases,default):
    """Static reachable call sites and their action owners, not execution counts."""
    by_address={row.address:row for row in rows}
    entries={action:int(entry,16) for action,entry in cases.items()
             if int(entry,16)!=default}
    entries["default"]=default
    sites={}
    per_action={}
    for action,entry in entries.items():
        visited,pending=set(),[entry]
        counts=Counter()
        while pending:
            address=pending.pop()
            if address in visited:
                continue
            if address not in by_address:
                raise ValueError("action CFG edge escapes instruction boundary")
            visited.add(address)
            row=by_address[address]
            if row.mnemonic=="call":
                callee=hex(row.operands[0].imm) if row.operands[0].type==x86.X86_OP_IMM else "virtual"
                counts[callee]+=1
                if address not in sites:
                    sites[address]=dict(callee=callee,owners=[])
                sites[address]["owners"].append(action)
            if row.mnemonic=="ret":
                continue
            if row.mnemonic=="jmp":
                pending.extend(tables[row.operands[0].mem.disp] if row.operands[0].type==x86.X86_OP_MEM else [row.operands[0].imm])
            elif row.group(capstone.CS_GRP_JUMP):
                pending.extend([row.operands[0].imm,row.address+row.size])
            else:
                pending.append(row.address+row.size)
        per_action[action]=dict(sorted(counts.items()))
    groups={}
    for address,site in sorted(sites.items()):
        key=(site["callee"],tuple(sorted(site["owners"])))
        groups.setdefault(key,[]).append(hex(address))
    return dict(per_action=per_action,
                groups=[dict(callee=callee,owners=list(owners),sites=addresses)
                        for (callee,owners),addresses in sorted(groups.items())])


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
    if operands[0].type!=x86.X86_OP_REG or operands[0].reg!=x86.X86_REG_ESP or operands[1].type!=x86.X86_OP_IMM or operands[1].imm!=0x238 or chain[6].op_str:
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
    if struct.unpack("<I",compare.target_bytes(0x6C55EC,4))[0]!=START:
        raise ValueError("YuyukoObject slot28 changed")
    if struct.unpack("<I",compare.target_bytes(0x6C5600,4))[0]!=0x578000:
        raise ValueError("following independent initializer entry changed")
    if compare.target_bytes(START-8,8)!=b"\xcc"*8 or compare.target_bytes(START+FULL,12)!=b"\xcc"*12:
        raise ValueError("reviewed separating INT3 bytes changed")
    rows,tables,facts=inventory(raw)
    if tuple(tables)!=TARGET_TABLES or facts["direct_calls"]!={hex(a):n for a,n in sorted(TARGET_CALLS.items())}:
        raise ValueError("reviewed target table/call inventory changed")
    if facts["returns"]!=62 or facts["virtual_calls"]!=15 or facts["stack_allocation"]!=[0x238]:
        raise ValueError("reviewed target return, virtual-call or frame inventory changed")
    facts["default_exit"]=check_default_exit(rows,tables[TARGET_TABLES[0]][-1])
    facts["quantized_return_providers"]=quantized_return_facts(compare)
    facts["call_ownership"]=call_ownership(rows,tables,facts["cases"],tables[TARGET_TABLES[0]][-1])
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
                          unmasked_differing_bytes=sum(a!=b for a,b in zip(target,candidate))+abs(len(target)-len(candidate)))
            try:
                rows,tables,facts=inventory(candidate,None)
                facts["call_ownership"]=call_ownership(rows,tables,facts["cases"],next(iter(tables.values()))[-1])
                report["candidate_inventory"]=facts
            except (ValueError,StopIteration,struct.error) as error:
                report["candidate_inventory_error"]=str(error)
            report["canonical_acceptance"]=candidate==target
    except (OSError,ValueError,RuntimeError,KeyError,StopIteration,struct.error) as error:
        print(json.dumps(dict(result="blocked",error=str(error)),indent=2))
        return 1
    print(json.dumps(report,indent=2))
    return 0 if args.target_only or report["result"]=="exact" else 1


if __name__=="__main__":
    raise SystemExit(main())
