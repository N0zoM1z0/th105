"""Complete original Boost error getter, pointer table and NUL-terminated strings."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
import rank_retained_exact as rank
import upstream_boost as upstream
import upstream_boost_sources as sources
from workflow_manifest import load_manifest
from coff_exception_rtti import Reader
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/boost-default-error-origin-anchors.toml'
UNIT='boost-regex-source-default-errors'
SYMBOL='?get_default_error_string@re_detail@boost@@YIPBDW4error_type@regex_constants@2@@Z'
TABLE='?s_default_error_messages@?1??get_default_error_string@re_detail@boost@@YIPBDW4error_type@regex_constants@3@@Z@4QBQBDB'
UNKNOWN='??_C@_0O@NIPGCINC@Unknown?5error?$AA@'
PROBE='scripts/probes/BoostRegexSourceDefaults.cpp'
PROBE_SHA='f68735333eeeb72aa29e18c9502417f66b404cb0e24e1f46a3988fb15c1b4479'
TABLE_VA=0x6d65e8
UNKNOWN_VA=0x6d32b4

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1
        and spec['target_sha256']==target_sha and spec['unit']==UNIT,'default errors schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'default errors requires one whole getter');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x006B4800'and type(a['size'])is int and a['size']==18
        and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==18
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'default errors typed whole anchor differs')
    u=units[UNIT]
    require(u.get('kind')=='probe'and u.get('source')==PROBE and u.get('profile')=='vc8-sp1-probe-o2'
        and u.get('enable_gs')is True and u.get('boost_regex_headers')is True
        and u.get('boost_regex_source_tu')=='regex_traits_defaults.cpp'and u.get('include_dirs')==[upstream.FOLDER,sources.INCLUDE],
        'default errors must use original verified source/profile')
    require(u['functions']==[dict(address='0x006B4800',symbol_base=SYMBOL,dir32_targets=[UNKNOWN+'='+UNKNOWN,TABLE+'='+TABLE])],
        'default errors formal binding/whole extent differs')
    return a,u

def readonly(reader,name,size):
    sec=reader.section(name)
    require(sec.name=='.rdata'and reader.symbol(name).value==0 and sec.raw_size==size
        and sec.characteristics&0x40000000 and not sec.characteristics&0xa0000000,'default errors source readonly extent differs')

def qualify(unit,anchor,rows,read,c,game):
    obj=ROOT/unit['object'];r=Reader(obj);readonly(r,TABLE,96)
    refs=r.refs(TABLE,96);require(len(refs)==24 and [x[:2]for x in refs]==[(i*4,6)for i in range(24)]and r.raw(TABLE,96)==bytes(96),
        'default errors full24-pointer source table differs')
    native=read(TABLE_VA,96);require(core.readonly_data(game,TABLE_VA,96)==native,'default errors native table storage differs')
    targets=struct.unpack('<24I',native);bindings={};strings=[];canonical=bytearray(96)
    for (off,kind,name),to in zip(refs,targets):
        require(name.startswith('??_C@')and (name not in bindings or bindings[name]==to),'default errors string identity/alias differs')
        sec=r.section(name);readonly(r,name,sec.raw_size);raw=r.raw(name,sec.raw_size)
        require(1<=len(raw)<=128 and raw[-1:]==b'\0'and b'\0'not in raw[:-1]and not r.refs(name,len(raw)),
            'default errors string is not one complete relocation-free literal')
        require(raw==read(to,len(raw))and core.readonly_data(game,to,len(raw))==raw,'default errors whole literal differs')
        if name not in bindings:strings.append(dict(symbol=name,address=hex(to),size=len(raw),sha256=digest(raw)))
        bindings[name]=to;struct.pack_into('<I',canonical,off,to)
    require(canonical==native and len(bindings)==22 and r.pointer(TABLE,80)==UNKNOWN and targets[20]==UNKNOWN_VA
        and refs[21][2]==refs[22][2]==refs[23][2]and r.raw(refs[21][2],1)==b'\0',
        'default errors full table/fallback/empty aliases differ')
    name,raw,_,rs=rank.read_coff_function(obj,SYMBOL,None)
    require(name==SYMBOL and len(raw)==18 and rs==[(4,6,UNKNOWN),(13,6,TABLE)],'default errors getter complete extent/relocations differ')
    data=c.known_data_targets();data[UNKNOWN]=(UNKNOWN_VA,read(UNKNOWN_VA,14),frozenset({0}),'address')
    data[TABLE]=(TABLE_VA,native,frozenset({0}),'address')
    body=c.coff_symbol_bytes(obj,SYMBOL,0x6b4800,0xffffffff,{},data)
    require(body==read(0x6b4800,18)and digest(body)==anchor['sha256'],'default errors whole getter differs')
    allowed=set(range(4,8))|set(range(13,17))
    require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'default errors changed nonrelocation byte')
    instructions=core.decode_closed_body(body,0x6b4800)
    hits=[x['address']for x in rows if int(x['size'],0)==18 and c.coff_symbol_bytes(obj,SYMBOL,int(x['address'],0),0xffffffff,{},data)==read(int(x['address'],0),18)]
    require(hits==['0x006B4800'],'default errors complete getter is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=18,symbol=SYMBOL,sha256=digest(body),relocations=rs,inventory_hits=hits,instructions=len(instructions),masked_bytes=0,unequal_bytes=0),
        table=dict(address=hex(TABLE_VA),size=96,symbol=TABLE,sha256=digest(native),entries=24),strings=strings)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['boost_default_error_anchor_file'])==ANCHORS,'unreviewed default errors anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        require(digest((ROOT/PROBE).read_bytes().replace(b'\r\n',b'\n'))==PROBE_SHA,'original defaults probe changed')
        tools,pins=core.pinned_tools(False);record=build.build_unit(UNIT,u,True,target_sha)
        c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','default errors formal root failed')
        proof.update(build=record,comparisons=results,tool_pins=pins,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (ROOT/'build/origin-anchors/boost-default-errors.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='boost-original-default-errors-106a',boost_default_error_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x006B4800'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
