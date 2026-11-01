"""Complete original sqrt owner and its real cross-region floating-point exits."""
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
from xiph_owned_switch_origins import zero_initialized_counter

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-sqrt-shared-origin-anchors.toml'
UNIT='vc8-original-sqrt-shared-body'
OUTPUT=ROOT/'build/origin-anchors/vc8-sqrt-shared'
ARCHIVE_SHA='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
HASHES={'sqrt.obj':'3952b216d461f3b0b2f77e4823a37e7fc8c3bfff157de7a6074c97f54f2ecf12',
 'common.obj':'7f534a917064dc829894fbcda0553e8b0df6ffebf294ff092709ad30f65cc8bd',
 '87disp.obj':'13bddd0fbf55452b31a2c1871fd2115cdec386ca9a33ed7e5879503a8bdcc98e',
 'fpinit.obj':'15a3c1d50003d0b7b3f44042c2164cc4b27f5c6983d03a6c71c66b2d0dd079b2'}
HELPERS=[('__load_CW',0x690de5,23,21,'__convertTOStoQNaN'),('__convertTOStoQNaN',0x690dfc,25,44,'__fload_withFB'),
 ('__fload_withFB',0x690e15,67,69,'__checkTOS_withFB'),('__checkTOS_withFB',0x690e58,22,136,'__fast_exit'),
 ('__fast_exit',0x690e6e,13,158,'__math_exit'),('__math_exit',0x690e7b,42,171,'__check_overflow_exit')]
CALLS={name:at for name,at,size,off,nxt in HELPERS}|{'__startOneArgErrorHandling':0x690d87}
ROOT_CALL_NAMES=['__load_CW','__fast_exit','__math_exit','__convertTOStoQNaN','__startOneArgErrorHandling']
BINDINGS=['___fastflag=vc8_sqrt_fastflag','_NAME_=vc8_sqrt_operation_name','__indefinite=vc8_sqrt_indefinite']
REFS=[(7,20,'__checkTOS_withFB'),(25,20,'__fload_withFB'),(49,20,'__load_CW'),(64,6,'___fastflag'),
 (71,20,'__fast_exit'),(82,6,'_NAME_'),(87,20,'__math_exit'),(115,20,'__convertTOStoQNaN'),
 (146,6,'__indefinite'),(157,6,'___fastflag'),(164,20,'__fast_exit'),(175,6,'_NAME_'),(180,20,'__startOneArgErrorHandling')]

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'sqrt owner schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'sqrt counts one new shared body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x0068A39D'and type(a['size'])is int and a['size']==157
        and a['symbol']=='start'and selected[0]['address']==a['address']and int(selected[0]['size'],0)==157
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'sqrt complete shared extent differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
        and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'
        and u.get('toolchain_object')=='sqrt.obj'and u.get('toolchain_archive_sha256')==ARCHIVE_SHA,'sqrt original member differs')
    require(u['functions']==[dict(address=a['address'],symbol_base='start',rel32_targets=[n+'='+f'0x{CALLS[n]:08X}'for n in ROOT_CALL_NAMES],dir32_targets=BINDINGS)],
        'sqrt formal shared-body bindings differ')
    return a,u

def closed_graph(regions,public_entries,external_calls):
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;instructions={};owners={};entries=set();region_names=set()
    for start,body,name in regions:
        require(start not in entries and name not in region_names and body,'sqrt graph regions must be distinct and nonempty');entries.add(start);region_names.add(name)
        ins=list(md.disasm(body,start));require(sum(i.size for i in ins)==len(body),'sqrt graph has incomplete instruction bytes')
        for i in ins:
            require(i.address not in instructions and not any(a<i.address<a+j.size or i.address<a<i.address+i.size for a,j in instructions.items()),'sqrt graph regions overlap')
            instructions[i.address]=i;owners[i.address]=name
    require(public_entries and len(set(public_entries))==len(public_entries)and all(a in instructions for a in public_entries),'sqrt graph public entries differ')
    pending=list(public_entries);reached=set();cross=[]
    while pending:
        at=pending.pop()
        if at in reached:continue
        require(at in instructions,'sqrt graph escapes or enters mid-instruction');i=instructions[at];reached.add(at)
        require(not i.group(capstone.CS_GRP_INT)and i.mnemonic not in {'int3','hlt','ud2'},'sqrt graph unproved trap')
        if i.group(capstone.CS_GRP_RET):require(i.mnemonic=='ret'and not i.operands,'sqrt exit must preserve its actual plain RET');continue
        is_call=i.group(capstone.CS_GRP_CALL);is_jump=i.group(capstone.CS_GRP_JUMP)
        if i.group(capstone.x86.X86_GRP_BRANCH_RELATIVE):require(is_call or is_jump,'sqrt graph unsupported relative transfer')
        if is_call or is_jump:
            require(len(i.operands)==1 and i.operands[0].type==capstone.x86.X86_OP_IMM,'sqrt graph does not permit indirect transfers');dest=i.operands[0].imm
            if dest in instructions:
                require(owners[dest]==owners[at]or dest in entries,'sqrt cross-region transfer must target an actual helper entry')
                pending.append(dest)
                if owners[dest]!=owners[at]:cross.append(dict(site=hex(at),target=hex(dest),kind=i.mnemonic))
            else:require(is_call and i.size==5 and i.bytes[0]==0xe8 and dest in external_calls,'sqrt graph unproved external edge')
            if i.id==capstone.x86.X86_INS_JMP:continue
        pending.append(at+i.size)
    require(reached==set(instructions),'sqrt complete owner graph has unaccounted unreachable bytes')
    return dict(instructions=len(instructions),reached=len(reached),public_entries=[hex(a)for a in public_entries],cross_region_edges=cross,unreachable_bytes=0)

def initialized(pe,address,size,readonly):
    rva=address-pe.OPTIONAL_HEADER.ImageBase;ss=[s for s in pe.sections if s.VirtualAddress<=rva and rva+size<=s.VirtualAddress+s.SizeOfRawData]
    require(len(ss)==1 and ss[0].Characteristics&0x40000000 and not ss[0].Characteristics&0x20000000
        and bool(ss[0].Characteristics&0x80000000)==(not readonly),'sqrt data storage differs')
    return pe.get_data(rva,size)

def qualify(unit,anchor,rows,read,c,game):
    paths={'sqrt.obj':ROOT/unit['object'],**{n:OUTPUT/n for n in HASHES if n!='sqrt.obj'}}
    for n,p in paths.items():require(digest(p.read_bytes())==HASHES[n],'sqrt original member hash differs: '+n)
    readers={n:Reader(p)for n,p in paths.items()};r=readers['sqrt.obj'];common=readers['common.obj'];constants=readers['87disp.obj'];fp=readers['fpinit.obj']
    by={x['address']:x for x in rows};origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    named_targets={'__CIsqrt':0x68a380,'_sqrt':0x68a394,**{n:at for n,at,size,off,nxt in HELPERS if n not in {'__fast_exit','__math_exit'}},'__startOneArgErrorHandling':0x690d87}
    for n,at in named_targets.items():
        key=f'0x{at:08X}';require(by[key]['current_name']==n and origins[key]['disposition']=='exclude','sqrt named existing runtime ownership missing')
    sec=r.section('__CIsqrt');require(sec.name=='.text'and sec.raw_size==186 and r.symbol('__CIsqrt').value==0
        and r.symbol('_sqrt').section_number==r.symbol('start').section_number==r.symbol('__CIsqrt').section_number
        and r.symbol('_sqrt').value==20 and r.symbol('start').value==29 and r.symbol('_Error_handling').value==155
        and r.refs('__CIsqrt',186)==REFS,'sqrt full original owner/entry/relocation layout differs')
    metadata=[]
    for reader,name,size,target,ro in [(r,'_NAME_',8,0x6f7aa0,False),(constants,'__indefinite',44,0x6f8080,False),(common,'One',68,0x6cda20,True)]:
        s=reader.symbol(name);ss=reader.section(name);raw=reader.raw(name,size)
        require(s.value==0 and ss.raw_size==size and ss.reloc_count==0 and ss.name==('.rdata'if ro else'.data')
            and ss.characteristics&0x40000000 and not ss.characteristics&0x20000000 and bool(ss.characteristics&0x80000000)==(not ro),
            'sqrt complete source data section differs')
        require(raw==read(target,size)and initialized(game,target,size,ro)==raw,'sqrt whole source/native data differs')
        metadata.append(dict(symbol=name,address=hex(target),size=size,sha256=digest(raw)))
    require(r.raw('_NAME_',8)==b'sqrt\0\0\0\0'and constants.symbol('__piby2').value==10 and constants.symbol('One').value==20
        and constants.symbol('XAMtoTagTab').value==28 and common.symbol('__DEFAULT_CW_in_mem').value==8,'sqrt actual data roles differ')
    flag=fp.symbol('___fastflag');bs=fp.section('___fastflag')
    require(flag.value==0 and bs.name=='.bss'and bs.raw_size==8 and bs.raw_offset==0 and bs.reloc_count==0 and bs.characteristics&0x80
        and fp.symbol('__adjust_fdiv').section_number==flag.section_number and fp.symbol('__adjust_fdiv').value==4,'sqrt original flag subobject differs')
    require(zero_initialized_counter(game,0x6fd3a4,4)==bytes(4),'sqrt actual flag is not PE zero-fill')
    data=c.known_data_targets();expected={'vc8_sqrt_fastflag':(0x6fd3a4,bytes(4),frozenset({0}),'address'),
        'vc8_sqrt_operation_name':(0x6f7aa0,read(0x6f7aa0,8),frozenset({0}),'literal'),
        'vc8_sqrt_indefinite':(0x6f8080,read(0x6f8080,10),frozenset({0}),'address')}
    require(all(data.get(k)==v for k,v in expected.items()),'sqrt typed data binding differs');overrides=dict(x.split('=',1)for x in BINDINGS)
    owner=c.coff_symbol_bytes(paths['sqrt.obj'],'__CIsqrt',0x68a380,0xffffffff,CALLS,data,overrides)
    require(len(owner)==186 and owner==read(0x68a380,186),'sqrt entire public/shared owner differs')
    original=r.raw('__CIsqrt',186);allowed={i for off,k,n in REFS for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(original,owner))if i not in allowed),'sqrt owner changed nonrelocation bytes')
    regions=[(0x68a380,owner,'sqrt-owner')];support=[]
    for name,to,size,off,nxt in HELPERS:
        s=common.symbol(name);require(s.value==off and common.section(name).name=='.text'and common.section(name).raw_size==396
            and common.symbol(nxt).section_number==s.section_number and common.symbol(nxt).value==off+size,'sqrt helper complete original boundaries differ')
        raw=bytearray(common.raw(name,size));refs=common.refs(name,size)
        expected_refs=[(15,6,'One')]if name=='__convertTOStoQNaN'else[(31,20,'__startOneArgErrorHandling')]if name=='__math_exit'else[]
        require(refs==expected_refs,'sqrt helper full relocation inventory differs')
        for at,kind,symbol in refs:
            require(struct.unpack_from('<I',raw,at)[0]==0,'sqrt helper unexpected addend')
            if kind==6:struct.pack_into('<I',raw,at,0x6cda20)
            else:struct.pack_into('<i',raw,at,CALLS[symbol]-to-at-4)
        require(bytes(raw)==read(to,size),'sqrt complete helper body differs');core.decode_closed_body(bytes(raw),to)
        regions.append((to,bytes(raw),name));support.append(dict(symbol=name,address=hex(to),size=size,sha256=digest(raw),relocations=refs))
    graph=closed_graph(regions,[0x68a380,0x68a394],{0x690d87})
    shared=c.coff_symbol_bytes(paths['sqrt.obj'],'start',0x68a39d,0xffffffff,CALLS,data,overrides)
    require(len(shared)==157 and shared==owner[29:]and digest(shared)==anchor['sha256'],'sqrt complete shared tail differs')
    hits=[x['address']for x in rows if int(x['size'],0)==157 and c.coff_symbol_bytes(paths['sqrt.obj'],'start',int(x['address'],0),0xffffffff,CALLS,data,overrides)==read(int(x['address'],0),157)]
    require(hits==['0x0068A39D'],'sqrt complete shared body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=157,sha256=digest(shared),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),
        owner=dict(address='0x0068A380',size=186,sha256=digest(owner),entries={'__CIsqrt':0,'_sqrt':20,'start':29}),support=support,data=metadata,
        zero_fill_flag=dict(address='0x006FD3A4',size=4),graph=graph,scope='One complete shared physical CRT body; no standalone public ABI or extra prefix/helper/data credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_sqrt_shared_anchor_file'])==ANCHORS,'unreviewed sqrt anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==ARCHIVE_SHA,'sqrt original archive differs')
        sp=importlib.util.spec_from_file_location('sqrt_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);members=m.archive_members(archive);OUTPUT.mkdir(parents=True,exist_ok=True)
        for name,sha in HASHES.items():
            if name=='sqrt.obj':continue
            found=[b for n,b in members if Path(n).name==name];require(len(found)==1 and digest(found[0])==sha,'sqrt support archive identity differs');(OUTPUT/name).write_bytes(found[0])
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','sqrt formal shared body failed')
        proof.update(build=record,comparisons=results,archive_sha256=ARCHIVE_SHA,member_sha256=HASHES,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-sqrt-shared-owner-106a',vc8_sqrt_shared_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x0068A39D'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
