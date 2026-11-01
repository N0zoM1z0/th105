"""Complete original CRT bad_exception lifetimes and their full RTTI graph."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import linked_pe as core
import original_boost_link as original
from linked_logic_error_origins import require,named,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-bad-exception-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/linked-bad-exception'
OWNER='i libcmt:frame.obj'
VTABLE='??_7bad_exception@std@@6B@'
DTOR='??1bad_exception@std@@UAE@XZ'
SCALAR='??_Gbad_exception@std@@UAEPAXI@Z'
VECTOR='??_Ebad_exception@std@@UAEPAXI@Z'
COPY='??0bad_exception@std@@QAE@ABV01@@Z'
WHAT='?what@exception@std@@UBEPBDXZ'
CONTRACT={
 '0x0068EF88':(11,DTOR,[7],[2],True),
 '0x0068EF93':(34,SCALAR,[10,23],[5],False),
 '0x0068FB16':(24,COPY,[8],[14],False),
}
CALLEES={
 '??1exception@std@@UAE@XZ':(0x689fda,'libcmt:stdexcpt.obj','vc8-kb971090-short-and-data-runtime-106a'),
 '??0exception@std@@QAE@ABV01@@Z':(0x689f82,'libcmt:stdexcpt.obj','vc8-pinned-archive-symbols-106a'),
 '??3@YAXPAX@Z':(0x6898ea,'libcmt:delete.obj','vc8-runtime-tail-aliases-106a'),
 WHAT:(0x689ff0,'libcmt:stdexcpt.obj','vc8-kb971090-short-and-data-runtime-106a'),
}

def validate_spec(spec,selected,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha,'bad_exception schema/target differs')
    aa=spec['anchors'];by={r['address']:r for r in selected}
    require(len(aa)==len(selected)==len(CONTRACT)and set(by)=={a['address']for a in aa}==set(CONTRACT),'bad_exception selection differs')
    for a in aa:
        size,symbol,*_=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size
            and int(by[a['address']]['size'],0)==size and a['symbol']==symbol
            and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
            'bad_exception whole typed anchor differs')
    return aa

def rtti_graph(pe,game,symbols,read):
    source=named(symbols,VTABLE,'libcmt:frame.obj');target=0x6cd9b8
    sr=lambda a,n:core.pe_data(pe,a,n)
    words=lambda rd,a,n:list(struct.unpack('<'+'I'*n,rd(a,4*n)))
    typeinfo=named(symbols,'??_7type_info@@6B@','libcmt:typinfo.obj')
    visited={};records=[];addresses={}
    def record(sa,ta,size,fields,canonical):
        require(sa not in addresses or addresses[sa]==(ta,size),'bad_exception RTTI pointer identity is inconsistent')
        addresses[sa]=(ta,size)
        require(canonical==read(ta,size),'bad_exception complete canonical RTTI record differs')
        core.validate_body_relocations(pe,sa,size,[dict(field_offset=o)for o in fields])
        records.append(dict(address=hex(ta),size=size,sha256=digest(canonical)))
    def td(sa,ta,name):
        text=name.encode()+b'\0';sw=words(sr,sa,2);tw=words(read,ta,2)
        require(sw==[typeinfo,0]and tw[1]==0 and sr(sa+8,len(text))==read(ta+8,len(text))==text
            and core.primary_type_name(pe,typeinfo)==core.primary_type_name(game,tw[0])=='.?AVtype_info@@',
            'bad_exception whole typed descriptor differs')
        record(sa,ta,8+len(text),[0],struct.pack('<2I',*tw)+text)
    def hierarchy(sa,ta,kind):
        if sa in visited:
            require(visited[sa]==(ta,kind),'bad_exception RTTI alias/cycle differs');return
        visited[sa]=(ta,kind);sw=words(sr,sa,4);tw=words(read,ta,4)
        names=['bad_exception','exception']if kind=='bad_exception'else['exception']
        require(kind in {'bad_exception','exception'}and sw[:3]==tw[:3]==[0,0,len(names)],'bad_exception hierarchy flags/base count differ')
        sarray=sw[3];tarray=tw[3];sb=words(sr,sarray,len(names));tb=words(read,tarray,len(names))
        for i,name in enumerate(names):
            sd=words(sr,sb[i],7);tt=words(read,tb[i],7)
            require(sd[1:6]==tt[1:6]==[1 if name=='bad_exception'else 0,0,0xffffffff,0,0x40],
                'bad_exception base layout/attributes differ')
            if name==kind:require(sd[6]==sa and tt[6]==ta,'bad_exception own-class RTTI hierarchy must close locally')
            td(sd[0],tt[0],'.?AV'+name+'@std@@');hierarchy(sd[6],tt[6],name)
            sd[0]=tt[0];sd[6]=tt[6];record(sb[i],tb[i],28,[0,24],struct.pack('<7I',*sd))
        record(sarray,tarray,4*len(names),list(range(0,4*len(names),4)),struct.pack('<'+'I'*len(names),*tb))
        sw[3]=tw[3];record(sa,ta,16,[12],struct.pack('<4I',*sw))
    scol=words(sr,source-4,1)[0];tcol=words(read,target-4,1)[0];sc=words(sr,scol,5);tc=words(read,tcol,5)
    require(sc[:3]==tc[:3]==[0,0,0],'bad_exception needs its primary vtable')
    td(sc[3],tc[3],'.?AVbad_exception@std@@');hierarchy(sc[4],tc[4],'bad_exception')
    sc[3:]=tc[3:];record(scol,tcol,20,[12,16],struct.pack('<5I',*sc))
    record(source-4,target-4,4,[0],struct.pack('<I',tcol))
    ss=words(sr,source,2);ts=words(read,target,2)
    require(ss==[named(symbols,SCALAR,OWNER),named(symbols,WHAT,'libcmt:stdexcpt.obj')]
        and ts==[0x68ef93,0x689ff0],'bad_exception full vtable method identity differs')
    record(source,target,8,[0,4],struct.pack('<2I',*ts))
    return dict(source_address=source,target_address=target,symbol=VTABLE,target_key='native-bad-exception'),records

def qualify(pe,functions,symbols,anchor,rows,read,table,calls):
    size,symbol,offsets,fields,tail=CONTRACT[anchor['address']];target=int(anchor['address'],0)
    start=named(symbols,symbol,OWNER);aliases={(symbol,OWNER)}
    if symbol==SCALAR:aliases.add((VECTOR,OWNER))
    require(set(functions.get(start,[]))==aliases,'bad_exception original frame object aliases differ')
    require(all(core.IMAGE_BASE+e.address!=start for e in pe.DIRECTORY_ENTRY_EXPORT.symbols),'bad_exception may not be forced exported')
    raw=core.linked_body(pe,functions,start);require(len(raw)==size,'bad_exception complete source extent differs')
    def resolve(at):
        require(at in calls,'bad_exception unproved callee');return calls[at]
    def rebound(to):return core.canonicalize(raw,start,to,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000),vtables=[table],tail=tail)
    canonical,cs,rs=rebound(target)
    require(canonical==read(target,size)and digest(canonical)==anchor['sha256']and [r['offset']for r in cs]==offsets
        and [r['field_offset']for r in rs]==fields,'bad_exception whole canonical bytes or roles differ')
    core.validate_body_relocations(pe,start,size,rs);core.decode_closed_body(canonical,target,tail=tail)
    allowed={i for off in offsets+fields for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,canonical))if i not in allowed),'bad_exception changed nonrelocation byte')
    hits=[r['address']for r in rows if int(r['size'],0)==size and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
    require(hits==[anchor['address']],'bad_exception full canonical inventory identity is not unique')
    return dict(address=anchor['address'],size=size,symbol=symbol,sha256=digest(canonical),source_va=hex(start),
        calls=cs,references=rs,inventory_hits=hits,masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_bad_exception_anchor_file'])==ANCHORS,'bad_exception unreviewed anchor path')
        aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,target_sha)
        image,build=original.build(output=OUTPUT);pe=pefile.PE(str(image));game=pefile.PE(str(core.comparator().TARGET));maps=image.with_suffix('.map').read_text()
        functions=core.parse_map(maps);symbols=core.parse_map_symbols(maps)
        require(pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==core.IMAGE_BASE
            and [e.name.decode()for e in pe.DIRECTORY_ENTRY_EXPORT.symbols]==[original.PUBLIC_ROOT],'bad_exception original image/export differs')
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())};calls={}
        for n,(target,owner,evidence)in CALLEES.items():
            row=origins[f'0x{target:08X}'];require(row['disposition']=='exclude'and row['evidence_id']==evidence,'bad_exception independent runtime callee ownership differs')
            calls[named(symbols,n,owner)]=(n,target)
        table,rtti=rtti_graph(pe,game,symbols,read)
        facts=[qualify(pe,functions,symbols,a,rows,read,table,calls)for a in aa]
        proof=dict(build=build,anchors=facts,rtti=rtti,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
            dependency_sha256=core.sha(ROOT/'scripts/linked_logic_error_origins.py'),scope='three whole original CRT bad_exception routines; no authored or metadata byte credit')
        (OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='vc8-linked-bad-exception-106a',linked_bad_exception_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
