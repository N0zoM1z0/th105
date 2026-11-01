"""Complete original SDK static-book destroy and clear implementation."""
import csv
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
ANCHORS=ROOT/'config/xiph-staticbook-destroy-origin-anchors.toml'
UNIT='xiph-original-staticbook-destroy'
SYMBOL='_vorbis_staticbook_destroy'
CLEAR='_vorbis_staticbook_clear'
ARCHIVE_SHA='fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc'
OBJECT_SHA='0c98ab8712fbf5f287d563a925e7f407e3a0a67b469c0d1bd9a67c6677582704'
FREE_OFFSETS=[25,41,60,72,84,96,117,135,147,172]
CALLS={CLEAR:0x6810c0,'_free':0x68c686}

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'staticbook schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'staticbook requires one new whole body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00681190'and type(a['size'])is int and a['size']==29
        and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==29
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'staticbook typed whole anchor differs')
    u=units[UNIT]
    require(u.get('kind')=='upstream_prebuilt'and u.get('source')=='scripts/fetch-xiph-sdk-object.py'
        and u.get('profile')=='xiph-win32sdk-1.0.1'and u.get('enable_gs')is False and u.get('sdk_component')=='vorbis'
        and u.get('sdk_object')=='sharedbook.obj'and u.get('sdk_archive_sha256')==ARCHIVE_SHA,'staticbook original SDK member differs')
    require(u['functions']==[dict(address='0x00681190',symbol_base=SYMBOL,rel32_targets=[CLEAR+'=0x006810C0','_free=0x0068C686']),
        dict(address='0x006810C0',symbol_base=CLEAR,rel32_targets=['_free=0x0068C686'])],
        'staticbook formal whole roots/callees differ')
    return a,u

def qualify(unit,anchor,rows,read,c):
    obj=ROOT/unit['object'];require(digest(obj.read_bytes())==OBJECT_SHA,'staticbook original object differs')
    old=tomllib.loads((ROOT/'config/xiph-relocated-origin-anchors.toml').read_text())
    supports=[a for a in old['anchors']if a['symbol']==CLEAR]
    require(supports==[dict(address='0x006810C0',size=193,component='vorbis',object='sharedbook.obj',symbol=CLEAR,section_size=208)],
        'staticbook independent original clear identity differs')
    by={x['address']:x for x in rows};origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    require(origins['0x006810C0']['disposition']=='exclude'and origins['0x0068C686']['disposition']=='exclude'
        and by['0x0068C686']['current_name']=='_free','staticbook named provider ownership missing')
    def whole(symbol,to,size,extent,refs):
        name,raw,_,rs=rank.read_coff_function(obj,symbol,None)
        require(name==symbol and len(raw)==extent and raw[size:]==b'\x90'*(extent-size)and rs==refs,
            'staticbook whole source section/padding/relocations differ')
        b=c.coff_symbol_bytes(obj,symbol,to,0xffffffff,CALLS,{})
        require(len(b)==extent and b==read(to,extent),'staticbook complete native section differs')
        allowed={i for off,k,n in refs for i in range(off,off+4)}
        require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'staticbook changed nonrelocation bytes')
        instructions=core.decode_closed_body(b[:size],to)
        return b,dict(address=f'0x{to:08X}',size=size,section_size=extent,symbol=symbol,sha256=digest(b[:size]),section_sha256=digest(b),
            relocations=refs,instructions=len(instructions),masked_bytes=0,unequal_bytes=0)
    _,support=whole(CLEAR,0x6810c0,193,208,[(off,20,'_free')for off in FREE_OFFSETS])
    b,fact=whole(SYMBOL,0x681190,29,32,[(14,20,CLEAR),(20,20,'_free')])
    require(fact['sha256']==anchor['sha256']and b[5:10]==bytes.fromhex('8b463085c0'),'staticbook actual ownership-flag guard differs')
    hits=[x['address']for x in rows if int(x['size'],0)==29 and c.coff_symbol_bytes(obj,SYMBOL,int(x['address'],0),0xffffffff,CALLS,{})[:29]==read(int(x['address'],0),29)]
    require(hits==['0x00681190'],'staticbook whole callable is not inventory-unique');fact['inventory_hits']=hits
    return dict(anchor=fact,support=support,scope='29 new library code bytes only; no repeated provider or18 padding bytes credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['xiph_staticbook_destroy_anchor_file'])==ANCHORS,'unreviewed staticbook anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        require(core.sha(ROOT/'.tools/upstream/OggVorbis-win32sdk-1.0.1.zip')==ARCHIVE_SHA,'staticbook original archive differs')
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();proof=qualify(u,a,rows,read,c)
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==2 and all(r['result']=='exact'for r in results),'staticbook formal root/support failed')
        proof.update(build=record,comparisons=results,archive_sha256=ARCHIVE_SHA,object_sha256=OBJECT_SHA,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (ROOT/'build/origin-anchors/xiph-staticbook-destroy.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='xiph-original-staticbook-destroy-106a',xiph_staticbook_destroy_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00681190'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
