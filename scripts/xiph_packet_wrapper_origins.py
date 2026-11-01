"""Whole SDK packet wrappers, their provider and original section padding."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import build
import linked_pe as core
import rank_retained_exact as rank
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/xiph-packet-wrapper-origin-anchors.toml'
UNIT='xiph-original-ogg-packet-wrappers'
ARCHIVE_SHA='fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc'
OBJECT_SHA='6ab66ea08a2e48f01c89e90b4d0b816b6774f267a4cdd08f34a499abf9a14026'
CONTRACT={'0x006B6800':('_ogg_stream_packetout',1),'0x006B6950':('_ogg_stream_packetpeek',0)}
PROVIDER='__packetout'

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'packet wrappers schema/target/unit differs')
    aa=spec['anchors'];by={r['address']:r for r in selected}
    require(len(aa)==len(selected)==2 and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'packet wrappers selection differs')
    for a in aa:
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==21 and int(by[a['address']]['size'],0)==21
            and a['symbol']==CONTRACT[a['address']][0]and isinstance(a['sha256'],str)and len(a['sha256'])==64
            and all(c in '0123456789abcdef'for c in a['sha256']),'packet wrappers whole typed anchor differs')
    u=units[UNIT]
    require(u.get('kind')=='upstream_prebuilt'and u.get('source')=='scripts/fetch-xiph-sdk-object.py'
        and u.get('profile')=='xiph-win32sdk-1.0.1'and u.get('enable_gs')is False and u.get('sdk_component')=='ogg'
        and u.get('sdk_object')=='framing.obj'and u.get('sdk_archive_sha256')==ARCHIVE_SHA,'packet wrappers require original SDK framing object')
    expected=[dict(address=at,symbol_base=symbol,rel32_targets=['__packetout=0x006B6820'])for at,(symbol,arg)in CONTRACT.items()]
    expected.append(dict(address='0x006B6820',symbol_base=PROVIDER))
    require(u['functions']==expected,'packet wrappers formal providers/whole extents differ')
    return aa,u

def qualify(unit,anchors,rows,read,c):
    obj=ROOT/unit['object'];require(digest(obj.read_bytes())==OBJECT_SHA,'packet wrappers original object hash differs')
    old=tomllib.loads((ROOT/'config/xiph-origin-anchors.toml').read_text())
    selected=[a for a in old['anchors']if a['symbol']==PROVIDER]
    require(selected==[dict(address='0x006B6820',size=302,component='ogg',object='framing.obj',symbol=PROVIDER,section_size=304)]
        and old['sdk_sha256']==ARCHIVE_SHA,'packet wrappers independent named provider differs')
    origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    require(origins['0x006B6820']['disposition']=='exclude'and origins['0x006B6820']['evidence_id']=='xiph-sdk-relocation-free-anchors-106a',
        'packet wrappers independent provider ownership missing')
    def whole(symbol,to,size,extent,refs):
        name,raw,_,rs=rank.read_coff_function(obj,symbol,None)
        require(name==symbol and len(raw)==extent and rs==refs and raw[size:]==b'\x90'*(extent-size),'packet wrappers source full section/padding/relocations differ')
        canonical=c.coff_symbol_bytes(obj,symbol,to,0xffffffff,{PROVIDER:0x6b6820},{})
        require(len(canonical)==extent and canonical==read(to,extent),'packet wrappers full native section differs')
        allowed={i for off,k,n in refs for i in range(off,off+4)}
        require(all(x==y for i,(x,y)in enumerate(zip(raw,canonical))if i not in allowed),'packet wrappers changed a nonrelocation byte')
        instructions=core.decode_closed_body(canonical[:size],to)
        return canonical,dict(address=f'0x{to:08X}',size=size,section_size=extent,symbol=symbol,sha256=digest(canonical[:size]),
            section_sha256=digest(canonical),padding_bytes=extent-size,instructions=len(instructions),relocations=refs,masked_bytes=0,unequal_bytes=0)
    _,provider=whole(PROVIDER,0x6b6820,302,304,[]);facts=[]
    for a in anchors:
        to=int(a['address'],0);symbol,arg=CONTRACT[a['address']];body,fact=whole(symbol,to,21,32,[(13,20,PROVIDER)])
        require(body[8:10]==bytes([0x6a,arg])and body[10:13]==b'\x50\x51\xe8'and body[17:21]==b'\x83\xc4\x0c\xc3'
            and fact['sha256']==a['sha256'],'packet wrappers actual advance argument/cleanup/hash differs')
        hits=[r['address']for r in rows if int(r['size'],0)==21 and c.coff_symbol_bytes(obj,symbol,int(r['address'],0),0xffffffff,{PROVIDER:0x6b6820},{})[:21]==read(int(r['address'],0),21)]
        require(hits==[a['address']],'packet wrapper whole callable is not inventory-unique');fact['inventory_hits']=hits;fact['advance']=arg;facts.append(fact)
    return dict(anchors=facts,provider=provider,scope='42 new library code bytes only; no repeated provider or24 padding bytes credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['xiph_packet_wrapper_anchor_file'])==ANCHORS,'unreviewed packet wrapper anchor path')
        aa,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        cache=ROOT/'.tools/upstream/OggVorbis-win32sdk-1.0.1.zip';sdk=cache.read_bytes();require(digest(sdk)==ARCHIVE_SHA,'packet wrappers SDK archive hash differs')
        sp=importlib.util.spec_from_file_location('packet_sdk',ROOT/'scripts/fetch-xiph-sdk-object.py');module=importlib.util.module_from_spec(sp);sp.loader.exec_module(module)
        require(module.ARCHIVE_SHA256==ARCHIVE_SHA and digest(module.extract_object(sdk,'ogg','framing.obj'))==OBJECT_SHA,'packet wrappers original SDK member differs')
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();proof=qualify(u,aa,rows,read,c)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==3 and all(r['result']=='exact'for r in results),'packet wrappers formal replay failed')
        proof.update(build=record,comparisons=results,sdk_sha256=ARCHIVE_SHA,object_sha256=OBJECT_SHA,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (ROOT/'build/origin-anchors/xiph-packet-wrappers.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='xiph-original-packet-wrappers-106a',xiph_packet_wrapper_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
