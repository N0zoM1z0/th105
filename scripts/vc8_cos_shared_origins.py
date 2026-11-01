"""Original P4 cosine shared body with its full x87 fallback owner."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import capstone
from capstone.x86 import X86_OP_REG,X86_OP_MEM,X86_REG_ECX
import pefile
import build
import vc8_sin_shared_origins as sin
from linked_logic_error_origins import require,digest

ROOT=sin.ROOT
ANCHORS=ROOT/'config/vc8-cos-shared-origin-anchors.toml'
UNIT='vc8-original-cos-p4-shared-body'
OUTPUT=ROOT/'build/origin-anchors/vc8-cos-shared'
HASHES={'cos.obj':'3a8530e2d58c019ef913db86e1d795e2a7a60bf1e975168d53514d0a66a6826b',
 'cos_pentium4.obj':'aa3a55ae1ac29df47d273068cfdd76f91ff7c0a36cc00ca79bdd6629d8106ad1'}
CALLS=sin.CALLS|{'__cos_pentium4':0x6967c8,'__CIcos_pentium4':0x6967b0,'__cos_default':0x68bc1f}
X87_REFS=[(off,k,name.replace('sin','cos'))for off,k,name in sin.SIN_REFS]
P4_REFS=sin.P4_REFS[:10]+[(398,6,'ONE'),(421,20,'__cos_default')]
LABELS=sin.P4_LABELS|{'SIGN_MASK':2208}
BINDINGS=[name+'=vc8_cos_p4_'+name for off,k,name in P4_REFS if k==6]
X87_BINDINGS=[s.replace('vc8_sin_operation_name','vc8_cos_operation_name')for s in sin.SIN_BINDINGS]+['___use_sse2_mathfcns=vc8_sin_use_sse2']
X87_RANGES=[(lo,hi,name.replace('sin','cos'))for lo,hi,name in sin.SIN_RANGES]
P4_RANGES=[(0,24,'__CIcos_pentium4'),(24,30,'__cos_pentium4'),(30,425,'start')]

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'cos schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'cos counts one new shared body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006967CE'and type(a['size'])is int and a['size']==395
        and a['symbol']=='start'and selected[0]['address']==a['address']and int(selected[0]['size'],0)==395
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'cos complete shared extent differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
        and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'
        and u.get('toolchain_object')=='cos_pentium4.obj'and u.get('toolchain_archive_sha256')==sin.sqrt.ARCHIVE_SHA,'cos original member differs')
    require(u['functions']==[dict(address=a['address'],symbol_base='start',rel32_targets=['__cos_default=0x0068BC1F'],dir32_targets=BINDINGS)],
        'cos formal fallback/coefficient contract differs')
    old=tomllib.loads(sin.ANCHORS.read_text());sin.validate_spec(old,[dict(address=x['address'],size=str(x['size']))for x in old['anchors']],units,target_sha)
    return a,u

def neutral_trailing_lea(body,address):
    require(body==bytes.fromhex('8d4900'),'cos original three-byte alignment differs')
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;ins=list(md.disasm(body,address))
    require(len(ins)==1 and ins[0].size==3 and ins[0].mnemonic=='lea'and len(ins[0].operands)==2,'cos alignment must be a complete neutral LEA')
    a,b=ins[0].operands;require(a.type==X86_OP_REG and a.reg==X86_REG_ECX and b.type==X86_OP_MEM and b.mem.base==X86_REG_ECX
        and not b.mem.index and not b.mem.disp and not b.mem.segment,'cos trailing alignment changes state')

def qualify(units,anchor,rows,read,c,game):
    old=tomllib.loads(sin.ANCHORS.read_text());shared=sin.qualify(units,old['anchors'],rows,read,c,game)
    paths={'cos.obj':OUTPUT/'cos.obj','cos_pentium4.obj':ROOT/units[UNIT]['object']}
    for name,path in paths.items():require(digest(path.read_bytes())==HASHES[name],'cos original owner hash differs')
    r=sin.sqrt.Reader(paths['cos.obj']);p=sin.sqrt.Reader(paths['cos_pentium4.obj']);known=c.known_data_targets()
    ns=r.section('_NAME_');name=r.raw('_NAME_',7)
    require(ns.name=='.data'and ns.raw_size==7 and ns.reloc_count==0 and r.symbol('_NAME_').value==0 and name==b'cos\0\0\0\0'
        and name==read(0x6f7ad0,7)and sin.sqrt.initialized(game,0x6f7ad0,7,False)==name,'cos complete operation-name data differs')
    require(known.get('vc8_cos_operation_name')==(0x6f7ad0,name,frozenset({0}),'literal'),'cos operation-name mapping differs')
    sec=p.section('Ctable');require(sec.name=='.rdata'and sec.raw_size==2224 and sec.reloc_count==0 and p.symbol('Ctable').value==0
        and sec.characteristics&0x40000000 and not sec.characteristics&0xa0000000,'cos complete coefficient source differs')
    data=p.raw('Ctable',2224);require(data==read(0x6ce5c0,2224)and sin.sqrt.core.readonly_data(game,0x6ce5c0,2224)==data,'cos full coefficient section differs')
    for name,offset in LABELS.items():require(p.symbol(name).value==offset and p.symbol(name).section_number==p.symbol('Ctable').section_number,'cos actual coefficient label differs')
    ends=sorted(LABELS.values())+[2224]
    for off,k,name in P4_REFS:
        if k!=6:continue
        pos=LABELS[name];end=next(x for x in ends if x>pos);require(known.get('vc8_cos_p4_'+name)==(0x6ce5c0+pos,data[pos:end],frozenset({0}),'literal'),'cos complete literal-span binding differs')
    by={x['address']:x for x in rows};origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,name,size in [(0x68bb90,'_cos',297),(0x6967b0,'__CIcos_pentium4',24)]:
        key=f'0x{at:08X}';require(by[key]['current_name']==name and int(by[key]['size'],0)==size and origins[key]['disposition']=='exclude','cos existing owner identity differs')
    owners=[];regions=[];p4_body=None
    for reader,entry,member,base,extent,refs,ranges,bindings in [(r,'_cos','cos.obj',0x68bb90,297,X87_REFS,X87_RANGES,X87_BINDINGS),
            (p,'__CIcos_pentium4','cos_pentium4.obj',0x6967b0,428,P4_REFS,P4_RANGES,BINDINGS)]:
        require(reader.symbol(entry).value==0 and reader.section(entry).name=='.text'and reader.section(entry).raw_size==extent
            and reader.refs(entry,extent)==refs,'cos complete original owner extent/relocations differ')
        raw=reader.raw(entry,extent);b=c.coff_symbol_bytes(paths[member],entry,base,0xffffffff,CALLS,known,dict(s.split('=',1)for s in bindings))
        require(len(b)==extent and b==read(base,extent),'cos complete coupled owner differs')
        allowed={i for off,k,n in refs for i in range(off,off+4)};require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'cos changed nonrelocation bytes')
        if member=='cos.obj':require(raw[63:64]==b[63:64]==b'\x90','cos original entry alignment differs')
        else:neutral_trailing_lea(raw[425:],base+425);neutral_trailing_lea(b[425:],base+425);p4_body=b
        for lo,hi,name in ranges:
            require(reader.symbol(name).value==lo and reader.symbol(name).section_number==reader.symbol(entry).section_number,'cos actual source entry position differs')
            regions.append((base+lo,b[lo:hi],member+':'+name))
        owners.append(dict(address=hex(base),size=extent,sha256=digest(b),entries={name:lo for lo,hi,name in ranges}))
    for name,to,size,off,nxt in sin.sqrt.HELPERS:
        if name!='__load_CW':regions.append((to,read(to,size),name))
    graph=sin.sqrt.closed_graph(regions,[0x68bb90,0x68bbd0],{0x690d87})
    body=c.coff_symbol_bytes(paths['cos_pentium4.obj'],'start',0x6967ce,0xffffffff,CALLS,known,dict(s.split('=',1)for s in BINDINGS))
    require(len(body)==398 and body==p4_body[30:]and body[:395]==read(0x6967ce,395)and digest(body[:395])==anchor['sha256'],'cos complete shared body differs')
    hits=[x['address']for x in rows if int(x['size'],0)==395 and c.coff_symbol_bytes(paths['cos_pentium4.obj'],'start',int(x['address'],0),0xffffffff,CALLS,known,dict(s.split('=',1)for s in BINDINGS))[:395]==read(int(x['address'],0),395)]
    require(hits==['0x006967CE'],'cos shared body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=395,sha256=digest(body[:395]),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),owners=owners,
        coefficient_section=dict(address='0x006CE5C0',size=2224,sha256=digest(data)),graph=graph,common_support=shared,
        alignment=dict(x87_nop_offset=63,p4_trailing_offset=425,p4_trailing_hex='8d4900'),scope='395 new shared runtime bytes only; no legacy owner/prefix/helper/data/alignment or authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_cos_shared_anchor_file'])==ANCHORS,'unreviewed cos anchor path')
        units=sin.sqrt.load_manifest()['units'];a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        errors=sin.validate(dict(id='vc8-original-sin-shared-owners-106a',vc8_sin_shared_anchor_file=str(sin.ANCHORS.relative_to(ROOT))),[x for x in rows if x['address']in sin.CONTRACT],rows,read,target_sha)
        require(not errors,'cos shared source/protocol dependency failed: '+'; '.join(errors))
        archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==sin.sqrt.ARCHIVE_SHA,'cos original archive differs')
        sp=importlib.util.spec_from_file_location('cos_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
        found=[b for n,b in m.archive_members(archive)if Path(n).name=='cos.obj'];require(len(found)==1 and digest(found[0])==HASHES['cos.obj'],'cos fallback archive identity differs');OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'cos.obj').write_bytes(found[0])
        record=build.build_unit(UNIT,u,True,target_sha);c=sin.sqrt.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(units,a,rows,read,c,game)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','cos formal shared body failed')
        proof.update(build=record,comparisons=results,member_sha256=HASHES,validator_sha256=sin.sqrt.core.sha(Path(__file__)),anchor_sha256=sin.sqrt.core.sha(ANCHORS),common_validator_sha256=sin.sqrt.core.sha(Path(sin.__file__)))
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=sin.sqrt.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-cos-shared-owner-106a',vc8_cos_shared_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006967CE'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
