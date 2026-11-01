"""Original VC8 invalid_argument copy with full RTTI and exact native base provider."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
import linked_logic_error_origins as logic
import rank_retained_exact as rank
from coff_exception_rtti import Reader,RttiGraph
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-invalid-copy-origin-anchors.toml'
UNIT='vc8-original-invalid-argument-copy'
SYMBOL='??0invalid_argument@std@@QAE@ABV01@@Z'
VTABLE='??_7invalid_argument@std@@6B@'
ARCHIVE_SHA='e1b17cb213bfcf77e3c0988f8cb33ec8be143872d1c52de62c5da07ea1eb8031'
OBJECT_SHA='b2c7c0bc31c4e276c1657300d954990d5766d0e18509b76692ca80d5689df521'

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int
        and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'invalid copy schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'invalid copy requires one root');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00665B72'and type(a['size'])is int and a['size']==24
        and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==24
        and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),
        'invalid copy typed whole anchor differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'
        and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcpmt'
        and u.get('toolchain_object')=='string.obj'and u.get('toolchain_archive_sha256')==ARCHIVE_SHA,
        'invalid copy requires original libcpmt string object')
    require(u['functions']==[dict(address='0x00665B72',symbol_base=SYMBOL,rel32_targets=[logic.COPY+'=0x004017A0'],dir32_targets=[VTABLE+'='+VTABLE])],
        'invalid copy formal whole source/callee/table contract differs')
    return a,u

def qualify(unit,anchor,rows,read,c,game):
    obj=ROOT/unit['object'];require(digest(obj.read_bytes())==OBJECT_SHA,'invalid copy original object differs')
    r=Reader(obj);graph=RttiGraph(r,game,read,{'.?AVinvalid_argument@std@@','.?AVlogic_error@std@@','.?AVexception@std@@'})
    graph.table(VTABLE,0x6c7548,0,'.?AVinvalid_argument@std@@')
    name,raw,_,refs=rank.read_coff_function(obj,SYMBOL,None)
    require(name==SYMBOL and len(raw)==24 and refs==[(8,20,logic.COPY),(14,6,VTABLE)],'invalid copy full extent/relocation inventory differs')
    known=c.known_data_targets();require(known[VTABLE][0]==0x6c7548 and known[VTABLE][3]=='address','invalid copy formal vtable identity differs')
    body=c.coff_symbol_bytes(obj,SYMBOL,0x665b72,0xffffffff,{logic.COPY:0x4017a0},known)
    require(body==read(0x665b72,24)and digest(body)==anchor['sha256'],'invalid copy complete canonical body differs')
    allowed=set(range(8,12))|set(range(14,18));require(all(x==y for i,(x,y)in enumerate(zip(raw,body))if i not in allowed),'invalid copy changed nonrelocation bytes')
    ins=core.decode_closed_body(body,0x665b72)
    hits=[x['address']for x in rows if int(x['size'],0)==24 and c.coff_symbol_bytes(obj,SYMBOL,int(x['address'],0),0xffffffff,{logic.COPY:0x4017a0},known)==read(int(x['address'],0),24)]
    require(hits==['0x00665B72'],'invalid copy complete body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=24,symbol=SYMBOL,sha256=digest(body),relocations=refs,instructions=len(ins),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),
        rtti=graph.records,vtables=graph.tables,
        provider_scope='Native logic_error copy113 and full EH independently rebuilt and proved; archive alternative58 is not claimed equal or counted')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_invalid_copy_anchor_file'])==ANCHORS,'unreviewed invalid copy anchor path')
        a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        archive=ROOT/'.tools/msvc80-sp1/lib/libcpmt.lib';require(digest(archive.read_bytes())==ARCHIVE_SHA,'invalid copy original archive differs')
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        provider_errors=logic.validate(dict(id='linked-original-logic-error-106a',linked_logic_error_anchor_file=str(logic.ANCHORS.relative_to(ROOT))),
            [x for x in rows if x['address']in logic.CONTRACT],rows,read,target_sha)
        require(not provider_errors,'invalid copy native base full proof failed: '+'; '.join(provider_errors))
        provider=json.loads((logic.OUTPUT/'proof.json').read_text());p=[x for x in provider['anchors']if x['address']=='0x004017A0']
        require(len(p)==1 and p[0]['size']==113 and p[0]['symbol']==logic.COPY and p[0]['unequal_bytes']==p[0]['masked_bytes']==0,'invalid copy selected native provider differs')
        code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','invalid copy formal root failed')
        proof.update(build=record,comparisons=results,native_provider=p[0],provider_proof_sha256=core.sha(logic.OUTPUT/'proof.json'),
            archive_sha256=ARCHIVE_SHA,object_sha256=OBJECT_SHA,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS),rtti_validator_sha256=core.sha(ROOT/'scripts/coff_exception_rtti.py'))
        (ROOT/'build/origin-anchors/vc8-invalid-copy.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()))
    result=validate(dict(id='vc8-original-invalid-argument-copy-106a',vc8_invalid_copy_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00665B72'],rows,c.target_bytes,sha)
    print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
