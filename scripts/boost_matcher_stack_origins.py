"""Original matcher recursion stopper and typed dot-repeat tail dispatcher."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import boost_matcher_leaf_origins as leaf
from linked_logic_error_origins import require,digest

ROOT=leaf.ROOT
ANCHORS=ROOT/'config/boost-matcher-stack-origin-anchors.toml'
UNIT=leaf.UNIT
STEM=leaf.STEM
FAST=leaf.method('dot_repeat_fast')
DISPATCH=leaf.method('dot_repeat_dispatch')
def unwind(name):return '?unwind_'+name+'@'+STEM+'AAE_N_N@Z'
STOP=unwind('recursion_stopper')
UNWIND='?unwind@'+STEM+'AAE_N_N@Z'
TABLE='?s_unwind_table@?1?'+UNWIND+'@4QBQ8234@AE_N0@ZB'
NAMES='end paren recursion_stopper assertion alt repeater_counter extra_block greedy_single_repeat slow_dot_repeat fast_dot_repeat char_repeat short_set_repeat long_set_repeat non_greedy_repeat recursion recursion_pop'.split()
CONTRACT={'0x006A2830':(19,STOP),'0x006B25B0':(5,DISPATCH)}
NATIVE_TABLE=0x6d6068
PROVIDER_FILES=['boost-narrow-library-origin-anchors.toml','vc8-boost-narrow-library-origin-anchors.toml','vc8-boost-regex-vc8-std-origin-anchors.toml']

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'matcher stack schema/target/unit differs')
    aa=spec['anchors'];by={r['address']:r for r in selected}
    require(len(aa)==len(selected)==2 and set(by)==set(CONTRACT) and {a['address']for a in aa}==set(CONTRACT),'matcher stack selection differs')
    # Reuse the already strict original release/search source contract.
    old=tomllib.loads(leaf.ANCHORS.read_text());leaf.validate_spec(old,[dict(address=a['address'],size=str(a['size']))for a in old['anchors']],units,target_sha)
    unit=units[UNIT]
    for a in aa:
        size,symbol=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size
            and a['symbol']==symbol and int(by[a['address']]['size'],0)==size and isinstance(a['sha256'],str)
            and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),'matcher stack whole typed anchor differs')
        expected=dict(address=a['address'],symbol_base=symbol)
        if symbol==DISPATCH:expected['rel32_targets']=[FAST+'=0x006B1930']
        require([f for f in unit['functions']if f['address']==a['address']]==[expected],'matcher stack formal whole body differs')
    return aa,unit

def qualify(unit,anchors,rows,read,c,game):
    obj=ROOT/unit['object'];r=leaf.Reader(obj)
    origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    named={a['symbol']:int(a['address'],0)for file in PROVIDER_FILES for a in tomllib.loads((ROOT/'config'/file).read_text())['anchors']}
    calls={};offsets=[18,48,147,209,272,314,332,365]
    rr=r.refs(FAST,397)
    require([o for o,k,n in rr]==offsets and all(k==20 for o,k,n in rr),'matcher fast complete call inventory differs')
    expected=[0x6af2d0,0x6af2d0,0x68a143,0x410360,0x6ac9e0,0x6ac9e0,0x442250,0x4421d0]
    for (off,kind,name),to in zip(rr,expected):
        require((name=='__invalid_parameter_noinfo'and to==0x68a143)or named.get(name)==to,'matcher fast call lacks independent named identity')
        require(origins[f'0x{to:08X}']['disposition']=='exclude','matcher fast provider ownership missing');calls[name]=to
    data=c.known_data_targets();data[TABLE]=(NATIVE_TABLE,read(NATIVE_TABLE,72),frozenset({0}),'address')
    def whole(name,to,size,refs,tail=False):
        actual,raw,_,rs=leaf.rank.read_coff_function(obj,name,None)
        require(actual==name and len(raw)==size and rs==refs,'matcher stack source whole extent/relocations differ')
        canonical=c.coff_symbol_bytes(obj,name,to,0xffffffff,{**calls,FAST:0x6b1930},data)
        require(len(canonical)==size and canonical==read(to,size),'matcher stack complete canonical body differs')
        leaf.core.decode_closed_body(canonical,to,tail=tail,external_exits={to+17:0x6af2d0,to+47:0x6af2d0}if name==FAST else None)
        allowed={i for off,k,s in rs for i in range(off,off+4)}
        require(all(x==y for i,(x,y)in enumerate(zip(raw,canonical))if i not in allowed),'matcher stack changed a nonrelocation byte')
        return dict(address=f'0x{to:08X}',size=size,symbol=name,sha256=digest(canonical),relocations=rs,masked_bytes=0,unequal_bytes=0)
    support=[whole(FAST,0x6b1930,397,rr),whole(UNWIND,0x6b1ac0,58,[(34,6,TABLE)]),
        whole(unwind('alt'),0x6a28b0,46,[]),whole(unwind('repeater_counter'),0x6a4160,34,[])]
    for a in support:require(origins[a['address']]['disposition']=='exclude','matcher stack whole support ownership missing')
    # Original declared extent includes two trailing null slots, not two extra methods.
    sec=r.section(TABLE);require(sec.name=='.rdata'and sec.raw_size==72 and r.symbol(TABLE).value==0
        and sec.characteristics&0x40000000 and not sec.characteristics&0xa0000000,'unwind table source storage differs')
    require(r.raw(TABLE,72)==bytes(72)and r.refs(TABLE,72)==[(4*i,6,unwind(n))for i,n in enumerate(NAMES)],'unwind complete symbolic table differs')
    native=read(NATIVE_TABLE,72);require(leaf.core.readonly_data(game,NATIVE_TABLE,72)==native and native[64:]==bytes(8),'unwind native table storage/null slots differ')
    require([struct.unpack_from('<I',native,4*i)[0]for i in [2,4,5]]==[0x6a2830,0x6a28b0,0x6a4160],'unwind selected native slots differ')
    old=leaf.dispatch(r,game,read)
    require(r.pointer(leaf.TABLE,22*4)==DISPATCH and struct.unpack('<I',read(leaf.NATIVE_TABLE+22*4,4))[0]==0x6b25b0,'dot-repeat actual dispatch slot differs')
    facts=[]
    for a in anchors:
        to=int(a['address'],0);size,name=CONTRACT[a['address']];refs=[(1,20,FAST)]if name==DISPATCH else[]
        fact=whole(name,to,size,refs,name==DISPATCH);require(fact['sha256']==a['sha256'],'matcher stack root hash differs')
        hits=[x['address']for x in rows if int(x['size'],0)==size and c.coff_symbol_bytes(obj,name,int(x['address'],0),0xffffffff,{FAST:0x6b1930},data)==read(int(x['address'],0),size)]
        require(hits==[a['address']],'matcher stack root is not inventory-unique');fact['inventory_hits']=hits;facts.append(fact)
    return dict(anchors=facts,support=support,match_table=old,unwind_table=dict(address=hex(NATIVE_TABLE),size=72,selected_slots={'2':'0x006A2830','4':'0x006A28B0','5':'0x006A4160'},null_slots=[16,17],scope='Selected roles only, not whole-table canonical credit'))

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['boost_matcher_stack_anchor_file'])==ANCHORS,'unreviewed matcher stack anchor path')
        units=leaf.load_manifest()['units'];aa,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        require(digest((ROOT/leaf.upstream.RELEASE_INSTANCE_PROBE).read_bytes().replace(b'\r\n',b'\n'))==leaf.PROBE_SHA,'original release probe changed')
        tools,pins=leaf.core.pinned_tools(False);record=leaf.build.build_unit(UNIT,u,True,target_sha)
        code,results=leaf.build.compare_unit(u,True);require(code==0 and results and all(x['result']=='exact'for x in results),'matcher stack full release regression failed')
        c=leaf.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,aa,rows,read,c,game)
        # The preceding accepted leaves stay covered by their own full source/ownership gate.
        old=tomllib.loads(leaf.ANCHORS.read_text());leaf.qualify(u,old['anchors'],rows,read,c,game)
        proof.update(build=record,comparisons=results,tool_pins=pins,validator_sha256=leaf.core.sha(Path(__file__)),anchor_sha256=leaf.core.sha(ANCHORS),leaf_validator_sha256=leaf.core.sha(Path(leaf.__file__)))
        (ROOT/'build/origin-anchors/boost-matcher-stack.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=leaf.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='boost-original-matcher-stack-dispatch-106a',boost_matcher_stack_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
