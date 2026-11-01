"""Whole original log10 P4 owner, including its distinct noncallable tail."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import build
import vc8_sqrt_shared_origins as core
from linked_logic_error_origins import require,digest

ROOT=core.ROOT
UNIT='vc8-original-log10-p4-shared-body'
ANCHORS=ROOT/'config/vc8-log10-shared-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-log10-shared'
MEMBER_SHA='08cd9610e83d2fcba8cfe9af1c6125ec502a264e9e3dc10669aea2d36c201760'
LABELS={'emask':0,'CC':16,'Magic':32,'hi_mask':48,'LOG10_2':64,'place_L':80,'One':112,'Zero':128,'Two52':144,'Infs':160,'NaN':176,'coeff':192,'T_Tbl':256,'CB_Tbl':1296}
REFS=[(57,6,'emask'),(65,6,'CC'),(73,6,'One'),(81,6,'Magic'),(89,6,'hi_mask'),(119,6,'CB_Tbl'),(127,6,'T_Tbl'),(225,6,'coeff'),(237,6,'coeff'),(257,6,'coeff'),(269,6,'LOG10_2'),(281,6,'place_L'),(313,6,'coeff'),(384,6,'Zero'),(426,6,'emask'),(434,6,'One'),(463,6,'Infs'),(479,6,'One'),(491,6,'Infs'),(506,6,'Two52'),(587,20,'___libm_error_support')]
ADDENDS={237:16,257:32,313:48,463:8}
ROLES=list(dict.fromkeys((n,ADDENDS.get(off,0))for off,k,n in REFS if k==6))
BINDINGS=[n+'+0x'+format(a,'x')+'=vc8_log10_p4_'+n+'_'+str(a)for n,a in ROLES]
CALLS={'___libm_error_support':0x694a92}
RANGES=[(0,24,'__CIlog10_pentium4'),(24,30,'__log10_pentium4'),(30,644,'start')]
TAIL=bytes.fromhex('8da424000000000500000000')

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'log10 schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'log10 counts one shared body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00697C6E'and type(a['size'])is int and a['size']==614 and a['symbol']=='start'and selected[0]['address']==a['address']and int(selected[0]['size'],0)==614 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),'log10 whole shared extent differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')=='log10_pentium4.obj'and u.get('toolchain_archive_sha256')==core.ARCHIVE_SHA,'log10 original member differs')
    require(u['functions']==[dict(address=a['address'],symbol_base='start',rel32_targets=['___libm_error_support=0x00694A92'],dir32_targets=BINDINGS)],'log10 complete relocation contract differs')
    return a,u

def original_tail(body,address):
    # The ADD writes flags. This is exact original noncallable storage, not a
    # semantic neutral-instruction waiver and not part of the callable graph.
    require(body==TAIL,'log10 exact original noncallable tail differs')
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True;ins=list(md.disasm(body,address))
    require(len(ins)==2 and [i.size for i in ins]==[7,5]and [(i.mnemonic,i.op_str)for i in ins]==[('lea','esp, [esp]'),('add','eax, 0')],'log10 original trailing instruction forms differ')

def qualify(unit,anchor,rows,read,c,game):
    path=ROOT/unit['object'];require(digest(path.read_bytes())==MEMBER_SHA,'log10 original member hash differs');r=core.Reader(path)
    sec=r.section('__CIlog10_pentium4');require(sec.name=='.text'and sec.raw_size==656 and r.symbol('__CIlog10_pentium4').value==0 and r.refs('__CIlog10_pentium4',656)==REFS,'log10 full owner/relocation extent differs')
    raw=r.raw('__CIlog10_pentium4',656)
    for off,k,n in REFS:require(struct.unpack_from('<I',raw,off)[0]==(ADDENDS.get(off,0)if k==6 else 0),'log10 actual source relocation addend differs')
    ds=r.section('emask');require(ds.name=='.rdata'and ds.raw_size==2336 and ds.reloc_count==0 and ds.characteristics&0x40000000 and not ds.characteristics&0xa0000000,'log10 complete readonly coefficient section differs')
    data=r.raw('emask',2336);require(data==read(0x6cee70,2336)and core.core.readonly_data(game,0x6cee70,2336)==data,'log10 whole coefficient data differs')
    for n,pos in LABELS.items():require(r.symbol(n).value==pos and r.symbol(n).section_number==r.symbol('emask').section_number,'log10 actual data label differs')
    known=c.known_data_targets();ends=sorted(LABELS.values())+[2336]
    for n,add in ROLES:
        pos=LABELS[n];end=next(x for x in ends if x>pos);require(0<=add<end-pos,'log10 addend leaves original literal span')
        require(known.get('vc8_log10_p4_'+n+'_'+str(add))==(0x6cee70+pos,data[pos+add:end],frozenset({add}),'literal'),'log10 complete addend-specific literal mapping differs')
    by={x['address']:x for x in rows};origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,n,size in [(0x697c50,'__CIlog10_pentium4',24),(0x694a92,'___libm_error_support',634)]:
        key=f'0x{at:08X}';require(by[key]['current_name']==n and int(by[key]['size'],0)==size and origins[key]['disposition']=='exclude'and origins[key]['evidence_id']=='vc8-pinned-archive-symbols-106a','log10 existing public/provider ownership differs')
    b=c.coff_symbol_bytes(path,'__CIlog10_pentium4',0x697c50,0xffffffff,CALLS,known,dict(x.split('=',1)for x in BINDINGS))
    require(len(b)==656 and b==read(0x697c50,656),'log10 complete canonical owner differs')
    allowed={i for off,k,n in REFS for i in range(off,off+4)};require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'log10 altered nonrelocation byte')
    original_tail(raw[644:],0x697ed4);original_tail(b[644:],0x697ed4)
    text_symbols=[s for s in r.cf.symbols.values()if s.section_number==r.symbol('start').section_number]
    require(all(s.value<644 for s in text_symbols),'log10 source symbol enters trailing storage')
    regions=[]
    for lo,hi,n in RANGES:
        require(r.symbol(n).value==lo and r.symbol(n).section_number==r.symbol('start').section_number,'log10 actual public/shared entry differs');regions.append((0x697c50+lo,b[lo:hi],n))
    graph=core.closed_graph(regions,[0x697c50,0x697c68],{0x694a92})
    body=c.coff_symbol_bytes(path,'start',0x697c6e,0xffffffff,CALLS,known,dict(x.split('=',1)for x in BINDINGS))
    require(len(body)==626 and body==b[30:]and body[:614]==read(0x697c6e,614)and digest(body[:614])==anchor['sha256'],'log10 complete shared body differs')
    hits=[x['address']for x in rows if int(x['size'],0)==614 and c.coff_symbol_bytes(path,'start',int(x['address'],0),0xffffffff,CALLS,known,dict(y.split('=',1)for y in BINDINGS))[:614]==read(int(x['address'],0),614)]
    require(hits==['0x00697C6E'],'log10 shared body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=614,sha256=digest(body[:614]),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),owner=dict(address='0x00697C50',size=656,sha256=digest(b)),coefficient_section=dict(address='0x006CEE70',size=2336,sha256=digest(data)),graph=graph,noncallable_tail=dict(offset=644,size=12,hex=TAIL.hex(),add_writes_flags=True),scope='614 new shared runtime bytes only; no public-prefix/provider/data/tail or authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_log10_shared_anchor_file'])==ANCHORS,'unreviewed log10 anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,core.load_manifest()['units'],target_sha)
        record=build.build_unit(UNIT,u,True,target_sha);c=core.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','log10 formal shared comparison failed')
        proof.update(build=record,comparisons=results,member_sha256=MEMBER_SHA,validator_sha256=core.core.sha(Path(__file__)),anchor_sha256=core.core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-log10-shared-owner-106a',vc8_log10_shared_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00697C6E'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
