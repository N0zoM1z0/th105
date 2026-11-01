"""One physical native member-call bridge, with all original compatible aliases."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
from capstone.x86 import X86_OP_REG,X86_OP_MEM,X86_REG_EAX,X86_REG_ECX,X86_REG_ESP
import build
import linked_pe as core
import rank_retained_exact as rank
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-member-call-bridge-origin-anchors.toml'
UNIT='vc8-original-member-call-bridge'
SYMBOLS=['?_CallMemberFunction0@@YGXPAX0@Z','?_CallMemberFunction1@@YGXPAX00@Z','?_CallMemberFunction2@@YGXPAX00H@Z']
ARCHIVE_SHA='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
OBJECT_SHA='a14106ba2d01aa5b86d80b3eee4e8c267af1dbabfec1a845a6bb5545d29de7d7'

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'member bridge schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'member bridge counts one physical body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x0068998E'and type(a['size'])is int and a['size']==7
        and a['symbol']==SYMBOLS[0]and selected[0]['address']==a['address']and int(selected[0]['size'],0)==7
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'member bridge whole representative anchor differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
        and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'
        and u.get('toolchain_object')=='trnsctrl.obj'and u.get('toolchain_archive_sha256')==ARCHIVE_SHA,'member bridge original archive identity differs')
    require(u['functions']==[dict(address='0x0068998E',symbol_base=SYMBOLS[0])],'member bridge formal extent/alias contract differs')
    return a,u

def bridge_cfg(body,start):
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;ins=list(md.disasm(body,start))
    require(len(body)==7 and len(ins)==4 and [i.size for i in ins]==[1,1,3,2]
        and [i.mnemonic for i in ins]==['pop','pop','xchg','jmp'],'member bridge must be the complete four-instruction transfer')
    def reg(op,wanted):return op.type==X86_OP_REG and op.reg==wanted and op.size==4
    require(len(ins[0].operands)==len(ins[1].operands)==len(ins[3].operands)==1
        and reg(ins[0].operands[0],X86_REG_EAX)and reg(ins[1].operands[0],X86_REG_ECX)
        and reg(ins[3].operands[0],X86_REG_EAX),'member bridge return/this/callee register roles differ')
    ops=ins[2].operands;require(len(ops)==2 and ops[0].type==X86_OP_MEM and ops[0].size==4 and reg(ops[1],X86_REG_EAX),
        'member bridge stack exchange roles differ')
    mem=ops[0].mem;require(mem.base==X86_REG_ESP and not mem.index and not mem.disp and not mem.segment,
        'member bridge must exchange precisely the top stack DWORD')
    return [dict(offset=i.address-start,size=i.size,mnemonic=i.mnemonic,operands=i.op_str)for i in ins]

def qualify(unit,anchor,rows,read):
    obj=ROOT/unit['object'];require(digest(obj.read_bytes())==OBJECT_SHA,'member bridge original member hash differs')
    native=read(0x68998e,7);instructions=bridge_cfg(native,0x68998e);aliases=[]
    for symbol in SYMBOLS:
        name,raw,wild,refs=rank.read_coff_function(obj,symbol,None)
        require(name==symbol and len(raw)==7 and not wild and not refs,'member bridge original complete COMDAT differs')
        bridge_cfg(raw,0x68998e);require(raw==native and digest(raw)==anchor['sha256'],'member bridge whole original alias differs')
        aliases.append(dict(symbol=symbol,size=7,sha256=digest(raw)))
    hits=[x['address']for x in rows if int(x['size'],0)==7 and read(int(x['address'],0),7)==native]
    require(hits==['0x0068998E'],'member bridge native physical body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=7,sha256=digest(native),inventory_hits=hits,instructions=instructions,masked_bytes=0,unequal_bytes=0),
        source_aliases=aliases,scope='One physical runtime body; bytes do not establish exclusive0 identity or which compatible aliases the shipped linker retained')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_member_call_bridge_anchor_file'])==ANCHORS,'unreviewed member bridge anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        require(core.sha(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib')==ARCHIVE_SHA,'member bridge original archive differs')
        record=build.build_unit(UNIT,u,True,target_sha);proof=qualify(u,a,rows,read)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','member bridge formal representative failed')
        proof.update(build=record,comparisons=results,archive_sha256=ARCHIVE_SHA,object_sha256=OBJECT_SHA,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (ROOT/'build/origin-anchors/vc8-member-call-bridge.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-member-call-bridge-106a',vc8_member_call_bridge_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x0068998E'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
