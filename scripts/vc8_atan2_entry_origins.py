"""Two original atan2 entries, with whole dispatch/table ownership witnesses."""
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
from linked_logic_error_origins import require,digest
from workflow_manifest import load_manifest
from vc8_sqrt_shared_origins import initialized
from xiph_owned_switch_origins import zero_initialized_counter
ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-atan2-entry-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-atan2-entries'
UNIT='vc8-original-atan2-entries'
ARCHIVE='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
HASHES={'87ctriga.obj':'0b4f6502370b54a55f3600918b4444390241a0c556ecd6492f3a103b37ff9334','87triga.obj':'0ea43aafef6468978ea71a90097e14b188ab40ec3626b763b47c853aaf150fb4','87cdisp.obj':'61f7a7fb123644abaa13a02960f396b323882bf4f4020a1d066598d6f4ecc844','87disp.obj':'13bddd0fbf55452b31a2c1871fd2115cdec386ca9a33ed7e5879503a8bdcc98e','matherr.obj':'0b97801c34412ce468e64539d90ee5ad711f0c5d39d99eb52dcf17adb6602f1b','fpinit.obj':'15a3c1d50003d0b7b3f44042c2164cc4b27f5c6983d03a6c71c66b2d0dd079b2'}
ENTRIES=[('0x0068BB70','_atan2','__ctrandisp2',0x6965ab),('0x0068BB7A','__CIatan2','__cintrindisp2',0x696530)]
CODE=[('87ctriga.obj','_atan2',0x68bb70,20),('87triga.obj','fFASN',0x696480,168),('87cdisp.obj','__cintrindisp2',0x696530,640),('87disp.obj','__trandisp1',0x690ba0,458)]
DATA=[('87triga.obj','__OP_ATAN2jmptab',0x6f8990,80),('87disp.obj','__indefinite',0x6f8080,44),('87cdisp.obj','DblMax',0x6ce590,48)]
TABLE=['fFATN2','_rtforatnby0','__tosnan2','_rtforatn20','_rtforatn20','_rtforatn20','__tosnan2','_rtforatn20','__nosnan2','__nosnan2','__nan2','__nosnan2','_rtforatnby0','_rtforatnby0','__tosnan2','__rtindfpop']
def formal(at,sym,callee,target):return dict(address=at,symbol_base=sym,rel32_targets=[callee+'='+f'0x{target:08X}'],dir32_targets=['__OP_ATAN2jmptab=vc8_atan2_dispatch_table'])
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'atan2 schema/target/unit differs')
    aa=spec['anchors'];require(len(aa)==len(selected)==2 and {r['address']for r in selected}=={e[0]for e in ENTRIES},'atan2 selects two distinct whole entries')
    for a,e in zip(aa,ENTRIES):
        require(set(a)=={'address','size','symbol','sha256'}and a['address']==e[0]and type(a['size'])is int and a['size']==10 and a['symbol']==e[1]and int(next(r['size']for r in selected if r['address']==e[0]),0)==10 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'atan2 complete extent/identity differs')
    u=units[UNIT];require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')=='87ctriga.obj'and u.get('toolchain_archive_sha256')==ARCHIVE and u['functions']==[formal(*e)for e in ENTRIES],'atan2 original unit/call/data contract differs');return aa,u

def replay(reader,sym,base,size,symbols,read):
    sec=reader.section(sym);require(reader.symbol(sym).value==0 and sec.raw_size==size,'atan2 complete original section extent differs');raw=bytearray(reader.raw(sym,size));refs=reader.refs(sym,size)
    for off,kind,name in refs:
        require(kind in [6,20]and name in symbols and 0<=off<=size-4,'atan2 unsupported original relocation');require(struct.unpack_from('<I',raw,off)[0]==0,'atan2 unexpected original addend');value=symbols[name]-(base+off+4)if kind==20 else symbols[name];struct.pack_into('<I',raw,off,value&0xffffffff)
    require(bytes(raw)==read(base,size),'atan2 whole canonical section differs');return bytes(raw)

def entry_shape(body,at,table,target):
    require(len(body)==10 and body[0]==0xba and body[5]==0xe9 and struct.unpack_from('<I',body,1)[0]==table and at+10+struct.unpack_from('<i',body,6)[0]==target,'atan2 actual MOV EDX/table and tail E9 differs')
    return core.decode_closed_body(body,at,tail=True,external_exits={at+5:target})

def qualify(unit,anchors,rows,read,c,game):
    paths={'87ctriga.obj':ROOT/unit['object'],**{n:OUTPUT/n for n in HASHES if n!='87ctriga.obj'}};rr={}
    for n,p in paths.items():require(digest(p.read_bytes())==HASHES[n],'atan2 pinned original member differs: '+n);rr[n]=Reader(p)
    symbols={}
    for n,sym,base,size in CODE+DATA:
        r=rr[n];sec=r.symbol(sym).section_number
        for s in r.cf.symbols.values():
            if s.section_number==sec and not s.name.startswith('.')and not s.name.startswith('$$'):
                # Duplicate cwdefault/setcw local labels are not relocation targets.
                if s.name in symbols and symbols[s.name]!=base+s.value:continue
                symbols[s.name]=base+s.value
    symbols.update({'__87except':0x69c9e5,'___fastflag':0x6fd3a4,'__matherr_flag':0x6f92fc})
    require({n:symbols[n]for n in ['_atan2','__CIatan2','__ctrandisp2','__cintrindisp2','__OP_ATAN2jmptab']}==dict(_atan2=0x68bb70,__CIatan2=0x68bb7a,__ctrandisp2=0x6965ab,__cintrindisp2=0x696530,__OP_ATAN2jmptab=0x6f8990),'atan2 original source entries differ')
    support=[];boundaries=set();bodies={};md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for n,sym,base,size in CODE+DATA:
        r=rr[n];sec=r.section(sym);is_code=(n,sym,base,size)in CODE;require(sec.name==('.text'if is_code else '.rdata'if n=='87cdisp.obj'else '.data'),'atan2 original code/data section differs');b=replay(r,sym,base,size,symbols,read);bodies[(n,sym)]=b
        if is_code:
            ins=list(md.disasm(b,base));require(sum(i.size for i in ins)==size,'atan2 support contains undecoded code bytes');boundaries.update(i.address for i in ins)
        else:require(initialized(game,base,size,n=='87cdisp.obj')==b,'atan2 actual initialized storage differs')
        support.append(dict(member=n,symbol=sym,address=hex(base),size=size,sha256=digest(b)))
    table=rr['87triga.obj'];require(table.refs('__OP_ATAN2jmptab',80)==[(16+4*i,6,n)for i,n in enumerate(TABLE)],'atan2 complete sixteen-slot dispatch roles differ');tb=bodies[('87triga.obj','__OP_ATAN2jmptab')];require(tb[:16]==bytes.fromhex('056174616e3200000000000000021000'),'atan2 table operation header differs')
    for i,n in enumerate(TABLE):require(struct.unpack_from('<I',tb,16+4*i)[0]==symbols[n]and symbols[n]in boundaries,'atan2 dispatch slot is not actual source instruction entry')
    math=rr['matherr.obj'];require(math.symbol('__matherr_flag').value==0 and math.section('__matherr_flag').name=='.data'and math.section('__matherr_flag').raw_size==4 and not math.refs('__matherr_flag',4),'atan2 actual initialized matherr definition differs');word=math.raw('__matherr_flag',4);require(word==bytes.fromhex('94260000')and word==read(0x6f92fc,4)and initialized(game,0x6f92fc,4,False)==word,'atan2 initialized matherr word differs; not zero-fill common')
    fp=rr['fpinit.obj'];sec=fp.section('___fastflag');require(fp.symbol('___fastflag').value==0 and sec.name=='.bss'and sec.raw_size==8 and sec.raw_offset==0 and sec.reloc_count==0 and sec.characteristics&0x80 and fp.symbol('__adjust_fdiv').section_number==fp.symbol('___fastflag').section_number and fp.symbol('__adjust_fdiv').value==4,'atan2 fastflag original BSS subobject differs');require(zero_initialized_counter(game,0x6fd3a4,4)==bytes(4),'atan2 fastflag native zero-fill differs')
    by={r['address']:r for r in rows};origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,name,size in [(0x696530,'__cintrindisp2',62),(0x6965ab,'__ctrandisp2',72),(0x690ba0,'__trandisp1',103),(0x690c07,'__trandisp2',140),(0x69c9e5,'__87except',252)]:
        k=f'0x{at:08X}';require(by[k]['current_name']==name and int(by[k]['size'],0)==size and origins[k]['origin']=='vc8_runtime'and origins[k]['disposition']=='exclude','atan2 existing dispatch provider identity differs')
    known=c.known_data_targets();require(known.get('vc8_atan2_dispatch_table')==(0x6f8990,tb,frozenset({0}),'address'),'atan2 full independently owned table binding differs');r=rr['87ctriga.obj'];facts=[]
    for a,(at,sym,callee,target)in zip(anchors,ENTRIES):
        address=int(at,0);require(r.symbol(sym).value==address-0x68bb70 and r.refs(sym,10)==[(1,6,'__OP_ATAN2jmptab'),(6,20,callee)],'atan2 original entry/relocation roles differ');b=c.coff_symbol_bytes(paths['87ctriga.obj'],sym,address,10,{callee:target},known,{'__OP_ATAN2jmptab':'vc8_atan2_dispatch_table'})[:10];require(b==read(address,10)and digest(b)==a['sha256'],'atan2 complete root differs');entry_shape(b,address,0x6f8990,target)
        hits=[row['address']for row in rows if int(row['size'],0)==10 and c.coff_symbol_bytes(paths['87ctriga.obj'],sym,int(row['address'],0),10,{callee:target},known,{'__OP_ATAN2jmptab':'vc8_atan2_dispatch_table'})[:10]==read(int(row['address'],0),10)];require(hits==[at],'atan2 root is not inventory-unique');facts.append(dict(address=at,size=10,symbol=sym,sha256=digest(b),inventory_hits=hits,tail_target=hex(target)))
    return dict(anchors=facts,whole_sections=support,dispatch_slots=TABLE,matherr_word=word.hex(),scope='20 runtime entry bytes only; full support canonical witnesses and instruction boundaries, not a claim of whole-support CFG reachability; no support/data/authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_atan2_entry_anchor_file'])==ANCHORS,'unreviewed atan2 anchor path');aa,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha);archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==ARCHIVE,'atan2 original archive differs');sp=importlib.util.spec_from_file_location('atan2_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);members=m.archive_members(archive);OUTPUT.mkdir(parents=True,exist_ok=True)
        for n in HASHES:
            if n=='87ctriga.obj':continue
            found=[b for name,b in members if Path(name).name==n];require(len(found)==1 and digest(found[0])==HASHES[n],'atan2 original support member differs');(OUTPUT/n).write_bytes(found[0])
        rec=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();proof=qualify(u,aa,rows,read,c,pefile.PE(str(c.TARGET)));code,results=build.compare_unit(u,True);require(code==0 and len(results)==2 and all(r['result']=='exact'for r in results),'atan2 formal whole entry comparison failed');proof.update(build=rec,comparisons=results,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]
def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));errors=validate(dict(id='vc8-original-atan2-entries-106a',vc8_atan2_entry_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in [e[0]for e in ENTRIES]],rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
