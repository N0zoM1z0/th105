"""Original VC8 float sine overload in the actual Tenshi source context.

No caller exactness or custom double-return game helper is inferred.
"""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import build
import linked_pe as core
import rank_retained_exact as rank
from workflow_manifest import load_manifest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-float-sine-origin-anchors.toml'
UNIT='exact-first-tenshi-action-state'
SYMBOL='?sin@@YAMM@Z'
SOURCES={'src/characters/TenshiActionState.cpp','src/characters/TenshiActionState.hpp'}
HEADER_PINS={
 'include/math.h':'3cdf840fdb5db5a4c98fb849b6247f0f74dbd3071620ab218634d2c9ab58b791',
 'include/cmath':'66f7a7e9da038ec07760f9aef087ef107311ed8474b36e7a64ae924f3d6e874e',
}
NATIVE_PARENT_SHA='83af98e2673c40b5ca2f3caac87ab7a8e4114a758ac65dfeebdae1ad0a14e5b3'
NATIVE_SHA='9e008d740e1b185cbc9a37ad9c9ad72e34f4e15e20a8ce869efc92bd38afef1c'

def require(ok,message):
    if not ok:raise ValueError(message)

def digest(raw):return hashlib.sha256(raw).hexdigest()

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'}
            and type(spec['schema_version'])is int and spec['schema_version']==1
            and spec['target_sha256']==target_sha and spec['unit']==UNIT,'float sine schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'float sine needs one complete helper')
    a=spec['anchors'][0];r=selected[0]
    require(a==dict(address='0x0063D3C0',size=18,symbol=SYMBOL,sha256=NATIVE_SHA)
            and r['address']==a['address']and int(r['size'],0)==18,'float sine typed whole anchor differs')
    require(set(spec['source_pins'])==SOURCES and all(isinstance(v,str)and len(v)==64
            and all(c in '0123456789abcdef'for c in v)for v in spec['source_pins'].values()),'float sine source pins differ')
    u=units[UNIT]
    require(u.get('kind')=='probe'and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is False
            and u.get('source')=='src/characters/TenshiActionState.cpp'
            and {f['address']for f in u['functions']}=={'0x0063D3E0','0x0063D3C0'}
            and len(u['functions'])==2,'float sine needs its actual unchanged-profile caller unit')
    f=next(f for f in u['functions']if f['address']=='0x0063D3C0')
    require(f['symbol_base']==SYMBOL and f['rel32_targets']==['__CIsin=0x0068B670'],
            'float sine cannot bind a different overload or intrinsic')
    return u

def verify_sources(spec,tools,root=ROOT):
    for name,sha in spec['source_pins'].items():
        p=(root/name).resolve();p.relative_to(root.resolve())
        require(digest(p.read_bytes().replace(b'\r\n',b'\n'))==sha,'float sine actual caller source changed')
    for name,sha in HEADER_PINS.items():
        require(digest((tools/name).read_bytes())==sha,'original VC8 math header changed')
    source=(root/'src/characters/TenshiActionState.cpp').read_text()
    header=(root/'src/characters/TenshiActionState.hpp').read_text()
    require(source.count('std::sin(p[0])')==1 and 'tenshi_sine_radians'not in source+header,
            'float sine must come from the original overload, not the old custom double facade')

def caller_window(code,start,offset):
    require(3<=offset<=len(code)-14 and code[offset-3:offset]==b'\xd9\x1c\x24'
            and code[offset]==0xe8,'float sine needs its actual float stack argument and direct call')
    require(start+offset+5+struct.unpack_from('<i',code,offset+1)[0]==0x63d3c0,
            'float sine caller points to another helper')
    require(code[offset+5:offset+11]==b'\xd8\x1d'+struct.pack('<I',0x6d6ea8),
            'float sine result must use the actual dword zero comparison')
    require(code[offset+11:offset+14]==b'\x83\xc4\x04','float sine caller cleanup differs')
    return dict(site=hex(start+offset),argument='float at stack top',comparison='FCOMP dword [0x006D6EA8]')

def qualify(unit,rows,read,c):
    obj=ROOT/unit['object'];actual,raw,_,rels=rank.read_coff_function(obj,SYMBOL,None)
    require(actual==SYMBOL and len(raw)==18 and rels==[(5,20,'__CIsin')],
            'original float sine emission has a different whole extent or call inventory')
    targets={'__CIsin':0x68b670};data=c.known_data_targets()
    def rebound(at):return c.coff_symbol_bytes(obj,SYMBOL,at,0xffffffff,targets,data)
    canonical=rebound(0x63d3c0)
    require(canonical==read(0x63d3c0,18)and digest(canonical)==NATIVE_SHA,'float sine complete canonical bytes differ')
    require(all(a==b for i,(a,b)in enumerate(zip(raw,canonical))if not 5<=i<9),
            'float sine changed a non-call byte')
    core.decode_closed_body(canonical,0x63d3c0)
    hits=[r['address']for r in rows if int(r['size'],0)==18 and rebound(int(r['address'],0))==read(int(r['address'],0),18)]
    require(hits==['0x0063D3C0'],'float sine is not full-inventory unique')
    # Original math.h emits both the C float adapter and its C++ overload.
    _,alias,_,alias_rels=rank.read_coff_function(obj,'_sinf',None)
    require(alias==raw and alias_rels==rels,'original C float adapter and C++ overload differ')
    parent=next(f for f in unit['functions']if f['address']=='0x0063D3E0')
    _,parent_raw,_,parent_rels=rank.read_coff_function(obj,parent['symbol_base'],None)
    sites=[off-1 for off,kind,name in parent_rels if name==SYMBOL and kind==20]
    require(len(sites)==1,'actual Tenshi caller needs one original float sine edge')
    parent_targets=c.known_targets()
    for binding in parent.get('rel32_targets',[]):
        name,address=binding.rsplit('=',1);parent_targets[name]=int(address,0)
    parent_canonical=c.coff_symbol_bytes(obj,parent['symbol_base'],0x63d3e0,0xffffffff,parent_targets,data)
    native_parent=read(0x63d3e0,47784)
    require(digest(native_parent)==NATIVE_PARENT_SHA,'native full Tenshi callable identity differs')
    require(read(0x6d6ea8,4)==core.readonly_data(core.pefile.PE(str(c.TARGET)),0x6d6ea8,4)==b'\0'*4,'native float comparison literal differs')
    source_site=caller_window(parent_canonical,0x63d3e0,sites[0])
    native_site=caller_window(native_parent,0x63d3e0,0x646930-0x63d3e0)
    return dict(address='0x0063D3C0',symbol=SYMBOL,size=18,sha256=digest(canonical),inventory_hits=hits,
        original_c_adapter='_sinf',intrinsic='__CIsin',intrinsic_target='0x0068B670',
        source_caller=source_site,native_caller=native_site,
        caller_source_payload_size=len(parent_canonical),caller_native_payload_size=48968,
        caller_source_sha256=digest(parent_canonical),caller_native_callable_sha256=NATIVE_PARENT_SHA,
        caller_exact=parent_canonical==read(0x63d3e0,48968),masked_bytes=0,unequal_bytes=0,
        scope='original float adapter/overload body and actual float argument/result use; no whole giant-root credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_float_sine_anchor_file'])==ANCHORS,'unreviewed float sine anchor path')
        spec=tomllib.loads(ANCHORS.read_text());unit=validate_spec(spec,selected,load_manifest()['units'],target_sha)
        tools,pins=core.pinned_tools(True);verify_sources(spec,tools)
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        require(origins.get('0x0068B670',{}).get('evidence_id')=='vc8-pinned-archive-symbols-106a'
                and origins['0x0068B670']['disposition']=='exclude','float sine intrinsic lacks original CRT ownership')
        record=build.build_unit(UNIT,unit,True,target_sha);c=core.comparator();c.verify_target()
        proof=qualify(unit,rows,read,c)
        proof.update(rule=rule['id'],build=record,header_pins=HEADER_PINS,tool_pins=pins,
                     validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),
                     source_pins=spec['source_pins'])
        output=ROOT/'build/origin-anchors/vc8-float-sine.json';output.parent.mkdir(parents=True,exist_ok=True)
        output.write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:
        return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='vc8-original-float-sine-106a',vc8_float_sine_anchor_file=str(ANCHORS.relative_to(ROOT))),
                    [r for r in rows if r['address']=='0x0063D3C0'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
