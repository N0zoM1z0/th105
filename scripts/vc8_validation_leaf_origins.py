"""Three original validation aliases, one native body, and complete catch ownership."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import build
import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest
from vc8_control_entry_origins import common_word
ROOT=Path(__file__).resolve().parents[1]
UNIT='vc8-original-validation-leaf'
ANCHORS=ROOT/'config/vc8-validation-leaf-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-validation-leaf'
ARCHIVE='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
ALIASES=['?_ValidateRead@@YAHPBXI@Z','?_ValidateWrite@@YAHPAXI@Z','?_ValidateExecute@@YAHP6GHXZ@Z']
CATCH='___BuildCatchObjectHelper'
SCOPE='__sehtable$___BuildCatchObjectHelper'
HASHES={'validate.obj':'16324fba051485699579fcdfa3238702b40685b621a84de9ff9588101d9e733d','frame.obj':'76d9053819f37a2a4e47e342c11fd90be67177f8e051abc12027dd42b7d7738d','memmove.obj':'c27e83fcb703ecbc791089706b1a9893f5342d0ac9b90a779a9fb3c4bab3df96','cpu_disp.obj':'188965ae890a819307b7431044ed68da143c12c772b1352d32bc174c8d705533'}
CALLS={'__SEH_prolog4':0x6909a4,ALIASES[0]:0x69c4bf,ALIASES[1]:0x69c4bf,'___AdjustPointer':0x68f1cf,'_memmove':0x68d8b0,ALIASES[2]:0x69c4bf,'?_inconsistency@@YAXXZ':0x68fc5e,'?terminate@@YAXXZ':0x68fc12,'__SEH_epilog4':0x6909e9}
REFS=[(3,6,SCOPE),(8,20,'__SEH_prolog4'),(90,20,ALIASES[0]),(107,20,ALIASES[1]),(135,20,'___AdjustPointer'),(162,20,ALIASES[0]),(179,20,ALIASES[1]),(204,20,'_memmove'),(239,20,ALIASES[0]),(252,20,ALIASES[1]),(276,20,'___AdjustPointer'),(285,20,'_memmove'),(295,20,ALIASES[0]),(308,20,ALIASES[1]),(322,20,ALIASES[2]),(347,20,'?_inconsistency@@YAXXZ'),(371,20,'?terminate@@YAXXZ'),(378,20,'__SEH_epilog4')]
TABLES=[('LeadUpVec',140,3),('UnwindUpVec',264,8),('TrailUpVec',372,4),('LeadDownVec',536,3),('UnwindDownVec',676,8),('TrailDownVec',784,4)]

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'validation leaf schema/target/unit differs');require(len(spec['anchors'])==len(selected)==1,'validation leaf counts one physical body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x0069C4BF'and type(a['size'])is int and a['size']==13 and a['symbol']==ALIASES[0]and selected[0]['address']==a['address']and int(selected[0]['size'],0)==13 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'validation leaf complete identity/extent differs')
    u=units[UNIT];require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')=='validate.obj'and u.get('toolchain_archive_sha256')==ARCHIVE and u['functions']==[dict(address=a['address'],symbol_base=ALIASES[0])],'validation leaf original alias representative differs');return a,u

def catch_graph(body,base):
    require(base==0x68f452 and len(body)==383 and body[367:370]==bytes.fromhex('8b65e8'),'catch original handler stack restoration differs')
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;ins=list(md.disasm(body,base));require(sum(i.size for i in ins)==383,'catch body contains incomplete instructions');by={i.address:i for i in ins};tail=base+370;t=by.get(tail)
    require(t is not None and t.size==5 and t.bytes[0]==0xe9 and len(t.operands)==1 and t.operands[0].type==capstone.x86.X86_OP_IMM and t.operands[0].imm==0x68fc12,'catch only qualified EH tail must be exact E9 to terminate')
    entries=[base,base+363,base+367];pending=entries[:];seen=set()
    while pending:
        at=pending.pop()
        if at in seen:continue
        require(at in by,'catch graph escapes or enters mid-instruction');i=by[at];seen.add(at)
        if i.group(capstone.CS_GRP_RET):require(i.mnemonic=='ret'and not i.operands,'catch actual RET convention differs');continue
        require(not i.group(capstone.CS_GRP_INT)and i.mnemonic not in ['int3','ud2','hlt'],'catch unproved trap')
        if i.group(capstone.CS_GRP_CALL):require(i.size==5 and i.bytes[0]==0xe8 and len(i.operands)==1 and i.operands[0].type==capstone.x86.X86_OP_IMM and i.operands[0].imm in CALLS.values(),'catch unproved call')
        if i.group(capstone.CS_GRP_JUMP):
            require(len(i.operands)==1 and i.operands[0].type==capstone.x86.X86_OP_IMM,'catch unproved indirect jump')
            if at==tail:continue
            require(i.operands[0].imm in by,'catch unproved external branch');pending.append(i.operands[0].imm)
            if i.id==capstone.x86.X86_INS_JMP:continue
        pending.append(at+i.size)
    require(seen==set(by),'catch graph has unaccounted unreachable code');return dict(instructions=len(ins),entries=[hex(x)for x in entries],termination_tail=hex(tail),termination_target='0x0068FC12',unaccounted_bytes=0)

def scope_record(reader,read,game):
    sec=reader.section(SCOPE);require(reader.symbol(SCOPE).value==0 and sec.name=='.xdata$x'and sec.raw_size==28 and sec.reloc_count==2 and sec.characteristics&0x40000000 and not sec.characteristics&0xa0000000,'catch original full SEH4 scope section differs')
    raw=bytearray(reader.raw(SCOPE,28));require(list(struct.unpack('<7I',raw))==[0xfffffffe,0,0xffffffd4,0,0xfffffffe,0,0],'catch original SEH4 fields differ');seen={};details=[]
    for j in range(sec.reloc_count):
        off,idx,kind=struct.unpack('<IIH',reader.cf._read_raw(sec.reloc_offset+10*j,10));require(off in {20,24}and off not in seen and kind==6 and idx in reader.cf.symbols,'catch scope relocation shape differs');s=reader.cf.symbols[idx];expected=363 if off==20 else 367
        require(s.section_number==reader.symbol(CATCH).section_number and s.value==expected,'catch scope must resolve the actual symbol index/owner/offset, not a duplicate local name');seen[off]=idx;struct.pack_into('<I',raw,off,0x68f452+s.value);details.append(dict(field=off,symbol_index=idx,symbol=s.name,section=s.section_number,offset=s.value,target=hex(0x68f452+s.value)))
    require(set(seen)=={20,24}and bytes(raw)==read(0x6e23c0,28)and core.readonly_data(game,0x6e23c0,28)==bytes(raw),'catch complete canonical SEH4 record differs');return bytes(raw),details

def qualify(unit,anchor,rows,read,c,game):
    paths={'validate.obj':ROOT/unit['object'],**{n:OUTPUT/n for n in HASHES if n!='validate.obj'}};rr={}
    for n,p in paths.items():require(digest(p.read_bytes())==HASHES[n],'validation original member hash differs: '+n);rr[n]=Reader(p)
    bodies=[]
    for sym in ALIASES:
        r=rr['validate.obj'];require(r.symbol(sym).value==0 and r.section(sym).name=='.text'and r.section(sym).raw_size==13 and r.section(sym).reloc_count==0 and not r.refs(sym,13),'validation needs every whole original alias');b=r.raw(sym,13);require(b==read(0x69c4bf,13)and digest(b)==anchor['sha256'],'validation full alias differs');core.decode_closed_body(b,0x69c4bf);bodies.append(b)
    require(len(set(bodies))==1,'validation original alias bodies differ');hits=[r['address']for r in rows if int(r['size'],0)==13 and bodies[0]==read(int(r['address'],0),13)];require(hits==['0x0069C4BF'],'validation physical body is not inventory-unique')
    known=c.known_data_targets();require(known.get('vc8_sse2_available')==(0x7039c8,bytes(4),frozenset({0}),'address'),'validation memmove actual CPU-flag binding differs');common=common_word(paths['cpu_disp.obj'],rr['cpu_disp.obj'],'___sse2_available',0x7039c8,game)
    move=rr['memmove.obj'];require(move.symbol('_memmove').value==0 and move.section('_memmove').name=='.text'and move.section('_memmove').raw_size==869,'validation actual memmove provider extent differs')
    payload=c.coff_symbol_bytes(paths['memmove.obj'],'_memmove',0x68d8b0,869,{'__VEC_memcpy':0x69264f},known,{'___sse2_available':'vc8_sse2_available'});require(payload==read(0x68d8b0,869),'validation entire memmove payload differs')
    boundaries=set();segments=[];pos=0;md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for n,off,count in TABLES:
        require(move.symbol(n).value==off and move.symbol(n).section_number==move.symbol('_memmove').section_number,'validation memmove actual local table differs');segments.append((pos,off));pos=off+4*count
    segments.append((pos,869));ins_count=0
    for lo,hi in segments:
        ins=list(md.disasm(payload[lo:hi],0x68d8b0+lo));require(sum(i.size for i in ins)==hi-lo,'validation memmove code/data partition differs');boundaries.update(i.address for i in ins);ins_count+=len(ins)
    for n,off,count in TABLES:
        refs=move.refs('_memmove',count*4,off);require(len(refs)==count and [x[:2]for x in refs]==[(4*j,6)for j in range(count)],'validation complete source jump-table pointer fields differ')
        for j in range(count):require(struct.unpack_from('<I',payload,off+4*j)[0]in boundaries,'validation original jump-table entry is not a code boundary')
    source_raw=move.raw('_memmove',869);addends=[dict(field=off,symbol=n,addend=struct.unpack_from('<i',source_raw,off)[0])for off,k,n in move.refs('_memmove',869)if struct.unpack_from('<i',source_raw,off)[0]]
    require(addends==[dict(field=120,symbol='LeadUpVec',addend=-4),dict(field=127,symbol='TrailUpVec',addend=16),dict(field=497,symbol='UnwindDownVec',addend=28),dict(field=524,symbol='LeadDownVec',addend=-4)],'validation original biased table references differ')
    by={r['address']:r for r in rows};origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,name in [(0x68f452,CATCH),(0x68f1cf,'___AdjustPointer'),(0x68d8b0,'_memcpy_0'),(0x69264f,'__VEC_memcpy'),(0x68fc5e,'?_inconsistency@@YAXXZ'),(0x68fc12,'?terminate@@YAXXZ'),(0x6909a4,'__SEH_prolog4'),(0x6909e9,'__SEH_epilog4')]:
        key=f'0x{at:08X}';require(by[key]['current_name']==name and origins[key]['disposition']=='exclude'and origins[key]['origin']=='vc8_runtime','validation existing provider identity differs')
    frame=rr['frame.obj'];scope,scope_refs=scope_record(frame,read,game);require(frame.symbol(CATCH).value==0 and frame.section(CATCH).name=='.text'and frame.section(CATCH).raw_size==383 and frame.refs(CATCH,383)==REFS,'validation complete catch owner extent/fields differ')
    for off,k,n in REFS:require(struct.unpack_from('<I',frame.raw(CATCH,383),off)[0]==0,'validation catch source relocation addend differs')
    body=c.coff_symbol_bytes(paths['frame.obj'],CATCH,0x68f452,383,CALLS,{SCOPE:(0x6e23c0,scope,frozenset({0}),'address')});require(body==read(0x68f452,383),'validation whole catch owner differs');graph=catch_graph(body,0x68f452)
    sites=[dict(source_symbol=n,field=off,native_site=hex(0x68f452+off-1),target='0x0069C4BF')for off,k,n in REFS if n in ALIASES];require(len(sites)==9 and {x['source_symbol']for x in sites}==set(ALIASES),'validation original read/write/execute caller roles differ')
    return dict(anchor=dict(address=anchor['address'],size=13,sha256=digest(bodies[0]),inventory_hits=hits,aliases=ALIASES,masked_bytes=0,unequal_bytes=0),catch_owner=dict(address='0x0068F452',size=383,sha256=digest(body),calls=sites,graph=graph),scope=dict(address='0x006E23C0',size=28,sha256=digest(scope),exact_index_relocations=scope_refs),memmove_provider=dict(address='0x0068D8B0',payload_size=869,sha256=digest(payload),code_bytes=749,pointer_table_bytes=120,decoded_code_instructions=ins_count,tables=TABLES,biased_source_references=addends),cpu_flag=common,scope_limit='13 new physical runtime bytes only; aliases not counted separately; no exclusive original symbol/ICF choice, catch/provider/SEH/data/authored credit or generic exit relaxation')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_validation_leaf_anchor_file'])==ANCHORS,'unreviewed validation leaf anchor path');a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha);archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==ARCHIVE,'validation original archive differs');sp=importlib.util.spec_from_file_location('validate_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);members=m.archive_members(archive);OUTPUT.mkdir(parents=True,exist_ok=True)
        for n in HASHES:
            if n=='validate.obj':continue
            found=[b for name,b in members if Path(name).name==n];require(len(found)==1 and digest(found[0])==HASHES[n],'validation original support member differs');(OUTPUT/n).write_bytes(found[0])
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game);code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','validation formal physical body failed');proof.update(build=record,comparisons=results,member_sha256=HASHES,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='vc8-original-validation-leaf-106a',vc8_validation_leaf_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x0069C4BF'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
