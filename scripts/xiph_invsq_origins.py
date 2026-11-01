"""Whole original SDK inverse-square-root interpolation with exact legacy literals."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import xiph_table_getter_origins as tables
from match_literals import real_literal_bytes
from linked_logic_error_origins import require,digest

ROOT=tables.ROOT
ANCHORS=ROOT/'config/xiph-invsq-origin-anchors.toml'
UNIT='xiph-original-invsq2exp-lookup'
SYMBOL='_vorbis_invsqlook'
REALS=[('__real@4@40058000000000000000',0x6cd22c,bytes.fromhex('00008042')),
       ('__real@4@40048000000000000000',0x6cd228,bytes.fromhex('00000042')),
       ('__real@8@3ffe8000000000000000',0x6cd138,bytes.fromhex('000000000000e03f'))]
BINDINGS=[n+'='+n for n,a,b in REALS]+['_INVSQ_LOOKUP+0x0=_INVSQ_LOOKUP','_INVSQ_LOOKUP+0x4=xiph_invsq_lookup_next']
REFS=[(11,6,REALS[0][0]),(17,6,REALS[1][0]),(26,6,REALS[2][0]),(45,6,'_INVSQ_LOOKUP'),(52,6,'_INVSQ_LOOKUP'),(62,6,'_INVSQ_LOOKUP')]

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'invsq schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'invsq requires one whole body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006897D0'and type(a['size'])is int and a['size']==77
        and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==77
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'invsq complete typed anchor differs')
    old=tomllib.loads(tables.ANCHORS.read_text());tables.validate_spec(old,[dict(address=x['address'],size='12')for x in old['anchors']],units,target_sha)
    u=units[UNIT];require([f for f in u['functions']if f['address']==a['address']]==[dict(address=a['address'],symbol_base=SYMBOL,dir32_targets=BINDINGS)],
        'invsq formal complete literal/addend bindings differ')
    return a,u

def qualify(unit,anchor,rows,read,c,game):
    old=tomllib.loads(tables.ANCHORS.read_text());a=next(x for x in old['anchors']if x['address']=='0x00689820')
    data_proof=tables.qualify(unit,a,rows,read,c,game)
    obj=ROOT/unit['object'];r=tables.Reader(obj);known=c.known_data_targets();literals=[]
    for name,to,expected in REALS:
        require(real_literal_bytes(dict(type='DIR32',symbol=name,addend=0))==expected,'invsq legacy literal must decode exactly, without rounding')
        sec=r.section(name);s=r.symbol(name)
        require(s.value+len(expected)<=sec.raw_size and sec.name=='.rdata'and not sec.characteristics&0xa0000000
            and sec.characteristics&0x40000000 and not r.refs(name,len(expected)),'invsq literal source storage differs')
        require(r.raw(name,len(expected))==read(to,len(expected))==expected and tables.core.readonly_data(game,to,len(expected))==expected,
            'invsq complete original/native floating literal differs')
        require(known[name]==(to,expected,frozenset({0}),'literal'),'invsq floating binding must preserve exact encoded value')
        literals.append(dict(symbol=name,address=hex(to),bytes=expected.hex()))
    for key,add in [('_INVSQ_LOOKUP',0),('xiph_invsq_lookup_next',4)]:
        require(known[key]==(0x6f77d8,read(0x6f77d8+add,4),frozenset({add}),'literal'),'invsq resolved table-element binding differs')
    name,raw,_,refs=tables.rank.read_coff_function(obj,SYMBOL,None)
    require(name==SYMBOL and len(raw)==80 and raw[77:]==b'\x90'*3 and refs==REFS
        and [struct.unpack_from('<I',raw,o)[0]for o,k,n in refs]==[0,0,0,4,0,0],
        'invsq whole source extent/padding/relocation roles differ')
    overrides=dict(x.split('=',1)for x in BINDINGS)
    body=c.coff_symbol_bytes(obj,SYMBOL,0x6897d0,0xffffffff,{},known,overrides)
    require(len(body)==80 and body==read(0x6897d0,80)and digest(body[:77])==anchor['sha256'],'invsq complete native code and padding differ')
    allowed={i for off,k,n in refs for i in range(off,off+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'invsq changed a nonrelocation byte')
    ins=tables.core.decode_closed_body(body[:77],0x6897d0)
    hits=[x['address']for x in rows if int(x['size'],0)==77 and c.coff_symbol_bytes(obj,SYMBOL,int(x['address'],0),0xffffffff,{},known,overrides)[:77]==read(int(x['address'],0),77)]
    require(hits==['0x006897D0'],'invsq complete callable is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=77,section_size=80,symbol=SYMBOL,sha256=digest(body[:77]),section_sha256=digest(body),
        inventory_hits=hits,instructions=len(ins),relocations=refs,masked_bytes=0,unequal_bytes=0),literals=literals,data_dependency=data_proof)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['xiph_invsq_anchor_file'])==ANCHORS,'unreviewed invsq anchor path')
        units=tables.load_manifest()['units'];a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        require(tables.core.sha(ROOT/'.tools/upstream/OggVorbis-win32sdk-1.0.1.zip')==tables.ARCHIVE_SHA,'invsq original archive differs')
        record=tables.build.build_unit(UNIT,u,True,target_sha);c=tables.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        code,results=tables.build.compare_unit(u,True);require(code==0 and len(results)==2 and all(x['result']=='exact'for x in results),'invsq formal/getter regression failed')
        proof.update(build=record,comparisons=results,validator_sha256=tables.core.sha(Path(__file__)),anchor_sha256=tables.core.sha(ANCHORS),
            data_validator_sha256=tables.core.sha(Path(tables.__file__)),literal_validator_sha256=tables.core.sha(ROOT/'scripts/match_literals.py'))
        (ROOT/'build/origin-anchors/xiph-invsq.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=tables.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='xiph-original-inverse-square-lookup-106a',xiph_invsq_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006897D0'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
