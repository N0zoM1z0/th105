"""Complete original CRT atof/fread/flushall forwarding bodies."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import build
import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest
ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-public-wrapper-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-public-wrappers'
ARCHIVE='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
CONTRACT={
 '0x0068B420':dict(size=14,symbol='_atof',unit='vc8-original-atof-wrapper',member='atof.obj',sha='5cc546a67742f332f8c1444152bc01f241dec0d749f1677a1a2150c5ec86bddd',field=7,callee='__atof_l',target=0x68b377,callee_size=169),
 '0x0068CEEF':dict(size=27,symbol='_fread',unit='vc8-original-fread-wrapper',member='fread.obj',sha='ce3e59fd30d7574daed5675a2c932e0aedf2c1069f9b2ccca06737f23b42d60a',field=19,callee='_fread_s',target=0x68ce59,callee_size=150),
 '0x0069A81E':dict(size=9,symbol='__flushall',unit='vc8-original-flushall-wrapper',member='fflush.obj',sha='5a8e4eb928eb6799550b44945111c046795f83bd6051f64051fe547bd586c74a',field=3,callee='_flsall',target=0x69a744,callee_size=218)}
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha,'CRT wrapper schema/target differs')
    aa=spec['anchors'];by={r['address']:r for r in selected};require(len(aa)==len(selected)==len(CONTRACT)and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'CRT wrapper selected complete bodies differ')
    for a in aa:
        k=CONTRACT[a['address']];require(set(a)=={'address','size','symbol','unit','sha256'}and type(a['size'])is int and a['size']==k['size']and int(by[a['address']]['size'],0)==k['size']and a['symbol']==k['symbol']and a['unit']==k['unit']and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'CRT wrapper complete member extent/hash differs')
        u=units[k['unit']];require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')==k['member']and u.get('toolchain_archive_sha256')==ARCHIVE,'CRT wrapper original member/archive differs')
        require(u['functions']==[dict(address=a['address'],symbol_base=k['symbol'],rel32_targets=[k['callee']+'='+f'0x{k["target"]:08X}'])],'CRT wrapper exact source/provider contract differs')
    return aa

def qualify(units,anchors,rows,read,c):
    by={r['address']:r for r in rows};origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())};out=[]
    for a in anchors:
        k=CONTRACT[a['address']];u=units[k['unit']];p=ROOT/u['object'];require(digest(p.read_bytes())==k['sha'],'CRT wrapper original object hash differs');r=Reader(p);s=k['symbol'];size=k['size'];at=int(a['address'],0)
        require(r.symbol(s).value==0 and r.section(s).name=='.text'and r.section(s).raw_size==size and r.refs(s,size)==[(k['field'],20,k['callee'])],'CRT wrapper complete extent/relocation inventory differs')
        raw=r.raw(s,size);require(struct.unpack_from('<I',raw,k['field'])[0]==0,'CRT wrapper actual call addend differs')
        key=f'0x{k["target"]:08X}';require(by[key]['current_name']==k['callee']and int(by[key]['size'],0)==k['callee_size']and origins[key]['disposition']=='exclude'and origins[key]['evidence_id']=='vc8-pinned-archive-symbols-106a','CRT wrapper existing native provider identity differs')
        require(r.symbol(k['callee']).value==0 and r.section(k['callee']).name=='.text'and r.section(k['callee']).raw_size==k['callee_size'],'CRT wrapper source provider declaration/extent differs')
        calls={k['callee']:k['target']};b=c.coff_symbol_bytes(p,s,at,size,calls,{});require(len(b)==size and b==read(at,size)and digest(b)==a['sha256'],'CRT wrapper whole canonical body differs');ins=core.decode_closed_body(b,at)
        allowed=set(range(k['field'],k['field']+4));require(all(x==y for i,(x,y)in enumerate(zip(raw,b))if i not in allowed),'CRT wrapper changed nonrelocation bytes')
        hits=[x['address']for x in rows if int(x['size'],0)==size and c.coff_symbol_bytes(p,s,int(x['address'],0),size,calls,{})==read(int(x['address'],0),size)];require(hits==[a['address']],'CRT wrapper is not inventory-unique')
        out.append(dict(address=a['address'],size=size,symbol=s,sha256=digest(b),source_member=k['member'],member_sha256=k['sha'],callee=k['callee'],callee_address=key,instructions=len(ins),inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    return dict(anchors=out,scope='50 new runtime forwarding bytes only; existing provider ownership reused, no new provider implementation/EH or authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_public_wrapper_anchor_file'])==ANCHORS,'unreviewed CRT wrapper anchor path');units=load_manifest()['units'];aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha);builds=[];reports=[]
        for a in aa:builds.append(build.build_unit(a['unit'],units[a['unit']],True,target_sha))
        c=core.comparator();c.verify_target();proof=qualify(units,aa,rows,read,c)
        for a in aa:
            code,results=build.compare_unit(units[a['unit']],True);require(code==0 and len(results)==1 and results[0]['result']=='exact','CRT wrapper formal comparison failed');reports+=results
        proof.update(builds=builds,comparisons=reports,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='vc8-original-public-wrappers-106a',vc8_public_wrapper_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
