"""Whole original get_default_syntax and all actual stack-array literal roles."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import boost_default_error_origins as errors
from linked_logic_error_origins import require,digest

ROOT=errors.ROOT
ANCHORS=ROOT/'config/boost-default-syntax-origin-anchors.toml'
UNIT=errors.UNIT
SYMBOL='?get_default_syntax@re_detail@boost@@YIPBDE@Z'

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors','literals'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'default syntax schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'default syntax requires one whole body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006B45D0'and type(a['size'])is int and a['size']==548
        and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==548
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'default syntax whole typed anchor differs')
    previous=tomllib.loads(errors.ANCHORS.read_text())
    errors.validate_spec(previous,[dict(address='0x006B4800',size='18')],units,target_sha)
    literals=spec['literals'];require(len(literals)==50,'default syntax needs every source literal role')
    for i,x in enumerate(literals):
        require(set(x)=={'field','symbol','key','address','size','sha256'}and type(x['field'])is int and 0<=x['field']<=544
            and isinstance(x['symbol'],str)and x['symbol'].startswith('??_C@')and x['key']==f'boost_default_syntax_literal_{i:02d}'
            and type(x['size'])is int and x['size']in (1,2,3,11) and isinstance(x['address'],str)and 0x400000<=int(x['address'],0)<0x706000
            and isinstance(x['sha256'],str)and len(x['sha256'])==64 and all(c in '0123456789abcdef'for c in x['sha256']),
            'default syntax typed literal contract differs')
    require(len({x['symbol']for x in literals})==len({x['field']for x in literals})==50
        and [x['field']for x in literals]==sorted(x['field']for x in literals),'default syntax literal roles duplicate or reorder')
    u=units[UNIT]
    expected=dict(address='0x006B45D0',symbol_base=SYMBOL,dir32_targets=[x['symbol']+'='+x['key']for x in literals])
    require([f for f in u['functions']if f['address']=='0x006B45D0']==[expected],'default syntax formal whole-body bindings differ')
    return a,literals,u

def qualify(unit,anchor,literals,rows,read,c,game):
    obj=ROOT/unit['object'];r=errors.Reader(obj);name,raw,_,refs=errors.rank.read_coff_function(obj,SYMBOL,None)
    require(name==SYMBOL and len(raw)==548 and refs==[(x['field'],6,x['symbol'])for x in literals],
        'default syntax full source extent/relocation inventory differs')
    known=c.known_data_targets();data=dict(known);facts=[]
    for x in literals:
        name=x['symbol'];size=x['size'];to=int(x['address'],0);errors.readonly(r,name,size);body=r.raw(name,size)
        require(body[-1:]==b'\0'and b'\0'not in body[:-1]and not r.refs(name,size),'default syntax literal is not complete')
        require(body==read(to,size)and errors.core.readonly_data(game,to,size)==body and digest(body)==x['sha256'],
            'default syntax whole source literal/terminator differs')
        require(x['key']in known and known[x['key']]==(to,body,frozenset({0}),'address'),'default syntax isolated data binding differs')
        data[name]=known[x['key']];facts.append(dict(x))
    body=c.coff_symbol_bytes(obj,SYMBOL,0x6b45d0,0xffffffff,{},data)
    require(len(body)==548 and body==read(0x6b45d0,548)and digest(body)==anchor['sha256'],'default syntax whole canonical body differs')
    allowed={i for x in literals for i in range(x['field'],x['field']+4)}
    require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'default syntax changed a nonrelocation byte')
    ins=errors.core.decode_closed_body(body,0x6b45d0)
    hits=[x['address']for x in rows if int(x['size'],0)==548 and c.coff_symbol_bytes(obj,SYMBOL,int(x['address'],0),0xffffffff,{},data)==read(int(x['address'],0),548)]
    require(hits==['0x006B45D0'],'default syntax body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=548,symbol=SYMBOL,sha256=digest(body),inventory_hits=hits,instructions=len(ins),masked_bytes=0,unequal_bytes=0),literals=facts)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['boost_default_syntax_anchor_file'])==ANCHORS,'unreviewed default syntax anchor path')
        a,literals,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,errors.load_manifest()['units'],target_sha)
        require(digest((ROOT/errors.PROBE).read_bytes().replace(b'\r\n',b'\n'))==errors.PROBE_SHA,'original defaults probe changed')
        tools,pins=errors.core.pinned_tools(False);record=errors.build.build_unit(UNIT,u,True,target_sha)
        c=errors.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,literals,rows,read,c,game)
        old=tomllib.loads(errors.ANCHORS.read_text());errors.qualify(u,old['anchors'][0],rows,read,c,game)
        code,results=errors.build.compare_unit(u,True);require(code==0 and results and all(x['result']=='exact'for x in results),'default syntax formal/context regression failed')
        proof.update(build=record,comparisons=results,tool_pins=pins,validator_sha256=errors.core.sha(Path(__file__)),anchor_sha256=errors.core.sha(ANCHORS),error_validator_sha256=errors.core.sha(Path(errors.__file__)))
        (ROOT/'build/origin-anchors/boost-default-syntax.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=errors.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='boost-original-default-syntax-106a',boost_default_syntax_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006B45D0'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
