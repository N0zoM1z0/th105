"""Two complete original checked-string matcher leaves with dispatch ownership."""
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
from workflow_manifest import load_manifest
from coff_exception_rtti import Reader
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/boost-matcher-leaf-origin-anchors.toml'
UNIT='boost-regex-release-library-origin'
CONTEXT='boost-regex-iterator-search'
PROBE_SHA='cd93324aca70667e74f39a8016d04e47996059cc04933d2b17539322284b459c'
STEM='?$perl_matcher@V?$_String_const_iterator@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@U?$sub_match@V?$_String_const_iterator@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@boost@@@2@U?$regex_traits@DV?$w32_regex_traits@D@boost@@@boost@@@re_detail@boost@@'
NAMES='startmark endmark literal start_line end_line wild match word_boundary within_word word_start word_end buffer_start buffer_end backref long_set set jump alt rep combining soft_buffer_end restart_continue dot_repeat_dispatch char_repeat set_repeat long_set_repeat backstep assert_backref toggle_case recursion'.split()
def method(name):return '?match_'+name+'@'+STEM+'AAE_NXZ'
TABLE='?s_match_vtable@?1??match_all_states@'+STEM+'AAE_NXZ@4QBQ8234@AE_NXZB'
CONTRACT={'0x006A0AA0':(12,16,method('jump')),'0x006A0AF0':(18,28,method('toggle_case'))}
WITNESSES={2:0x6a1ae0,15:0x6a24e0}
NATIVE_TABLE=0x6d60c0

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'matcher schema/target/unit differs')
    anchors=spec['anchors'];by={r['address']:r for r in selected}
    require(len(anchors)==len(selected)==2 and set(by)==set(CONTRACT) and {a['address']for a in anchors}==set(CONTRACT),'matcher selection differs')
    for a in anchors:
        size,slot,symbol=CONTRACT[a['address']]
        require(set(a)=={'address','size','symbol','sha256'}and type(a['size'])is int and a['size']==size and a['symbol']==symbol
            and int(by[a['address']]['size'],0)==size and isinstance(a['sha256'],str)and len(a['sha256'])==64
            and all(c in '0123456789abcdef'for c in a['sha256']),'matcher typed whole anchor differs')
    u=units[UNIT];context=units[CONTEXT]
    require(u.get('kind')=='probe'and u.get('source')==upstream.RELEASE_INSTANCE_PROBE
        and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True
        and u.get('boost_regex_instances')is True and u.get('boost_regex_headers')is True
        and u.get('include_dirs')==[upstream.FOLDER],'matcher must use unchanged original release instances')
    for a in anchors:
        fs=[f for f in u['functions']if f['address']==a['address']]
        require(fs==[dict(address=a['address'],symbol_base=a['symbol'])],'matcher formal root must be whole and relocation-free')
    require(context.get('source')==upstream.SEARCH_PROBE and context.get('profile')=='vc8-sp1-probe-o2'
        and context.get('enable_gs')is True and context.get('boost_regex_headers')is True,'matcher public search context differs')
    return anchors,u,context

def dispatch(reader,game,read):
    sec=reader.section(TABLE)
    require(sec.name=='.rdata'and sec.raw_size==120 and reader.symbol(TABLE).value==0
        and sec.characteristics&0x40000000 and not sec.characteristics&0xa0000000,'matcher table source extent/storage differs')
    refs=reader.refs(TABLE,120)
    require(refs==[(i*4,6,method(n))for i,n in enumerate(NAMES)]and reader.raw(TABLE,120)==bytes(120),
        'matcher complete symbolic dispatch layout differs')
    # Locate by independently proved literal/set members, not by the new tiny leaves.
    hits=[]
    for section in game.sections:
        if not section.Characteristics&0x40000000 or section.Characteristics&0xa0000000:continue
        data=section.get_data();base=game.OPTIONAL_HEADER.ImageBase+section.VirtualAddress
        for off in range(0,len(data)-119,4):
            if all(struct.unpack_from('<I',data,off+4*i)[0]==to for i,to in WITNESSES.items()):hits.append(base+off)
    require(hits==[NATIVE_TABLE],'matcher witness table is not unique')
    native=read(NATIVE_TABLE,120)
    require(core.readonly_data(game,NATIVE_TABLE,120)==native,'matcher native dispatch bytes/storage differ')
    roles={**WITNESSES,**{slot:int(at,0)for at,(size,slot,sym)in CONTRACT.items()}}
    for slot,to in roles.items():
        require(reader.pointer(TABLE,slot*4)==method(NAMES[slot])and struct.unpack_from('<I',native,slot*4)[0]==to,
            'matcher selected dispatch slot differs')
    return dict(address=hex(NATIVE_TABLE),size=120,source_symbol=TABLE,selected_slots={str(k):hex(v)for k,v in roles.items()},
        scope='Four typed slots only; no full-table canonical or other method credit',inventory_hits=[hex(x)for x in hits])

def qualify(unit,anchors,rows,read,c,game):
    obj=ROOT/unit['object'];reader=Reader(obj);support=[]
    by={r['address']:r for r in rows}
    for slot,to in WITNESSES.items():
        name=method(NAMES[slot]);fs=[f for f in unit['functions']if f['address']==f'0x{to:08X}']
        require(len(fs)==1 and fs[0]['symbol_base']==name,'matcher independent source witness missing')
        f=fs[0];calls={s.rsplit('=',1)[0]:int(s.rsplit('=',1)[1],0)for s in f.get('rel32_targets',[])}
        actual,raw,_,refs=rank.read_coff_function(obj,name,None);size=int(by[f['address']]['size'],0)
        canonical=c.coff_symbol_bytes(obj,name,to,0xffffffff,calls,c.known_data_targets())
        require(actual==name and len(raw)==size and len(canonical)==size and canonical==read(to,size),'matcher independent whole witness differs')
        core.decode_closed_body(canonical,to)
        support.append(dict(address=f['address'],size=size,symbol=name,sha256=digest(canonical)))
    table=dispatch(reader,game,read);facts=[]
    for a in anchors:
        to=int(a['address'],0);size,slot,symbol=CONTRACT[a['address']]
        name,raw,wild,refs=rank.read_coff_function(obj,symbol,None)
        require(name==symbol and len(raw)==size and not refs and not wild,'matcher leaf complete relocation-free extent differs')
        require(raw==read(to,size)and digest(raw)==a['sha256'],'matcher complete leaf differs')
        instructions=core.decode_closed_body(raw,to)
        hits=[r['address']for r in rows if int(r['size'],0)==size and raw==read(int(r['address'],0),size)]
        require(hits==[a['address']],'matcher leaf is not inventory-unique')
        facts.append(dict(address=a['address'],size=size,symbol=symbol,slot=slot,sha256=digest(raw),instructions=len(instructions),inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    return dict(anchors=facts,dispatch=table,support=support)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['boost_matcher_leaf_anchor_file'])==ANCHORS,'unreviewed matcher anchor path')
        anchors,u,context=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        require(digest((ROOT/upstream.RELEASE_INSTANCE_PROBE).read_bytes().replace(b'\r\n',b'\n'))==PROBE_SHA,'original release probe changed')
        tools,pins=core.pinned_tools(False);records=[];comparisons=[]
        for key,unit in [(UNIT,u),(CONTEXT,context)]:
            records.append(build.build_unit(key,unit,True,target_sha));code,results=build.compare_unit(unit,True)
            require(code==0 and results and all(r['result']=='exact'for r in results),'matcher affected context regression failed')
            comparisons.append(dict(unit=key,results=results))
        c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,anchors,rows,read,c,game)
        proof.update(builds=records,comparisons=comparisons,tool_pins=pins,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        (ROOT/'build/origin-anchors/boost-matcher-leaves.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    errors=validate(dict(id='boost-original-checked-matcher-leaves-106a',boost_matcher_leaf_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
