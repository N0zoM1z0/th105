"""Whole original short-deque pop_back and its independently owned insertion call."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import build
import linked_pe as core
from coff_exception_rtti import Reader
from workflow_manifest import load_manifest,compiler_sha256
from linked_logic_error_origins import require,digest
ROOT=Path(__file__).resolve().parents[1]
UNIT='vc8-original-short-deque-pop-back'
ANCHORS=ROOT/'config/deque-popback-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/deque-popback'
SYMBOL='?pop_back@?$deque@FV?$allocator@F@std@@@std@@QAEXXZ'
INSERT='?_Insert_n@?$deque@FV?$allocator@F@std@@@std@@IAEXV?$_Deque_iterator@FV?$allocator@F@std@@$00@2@IABF@Z'
SOURCE='scripts/probes/deque_short.cpp'
SOURCE_SHA='c0603c011712c3ed8370ca70bf8b569279d212c6c33cf5b09416925068ba4d08'
COMPILER='71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c'
VENDOR={'deque':'2970afda6fd33a55bb0f3860124a28e5c9e532dda18a240ac5749fb0a8cc0fc7','xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b','xutility':'104560e2ad5e433eb62c06d70882534306ba345f5f74e6907a6b270df3bd7cea'}
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','compiler_sha256','unit','source_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['compiler_sha256']==COMPILER and spec['unit']==UNIT and spec['source_sha256']==SOURCE_SHA,'deque pop schema/source/compiler differs');require(len(spec['anchors'])==len(selected)==1,'deque pop selects one whole member');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x00428680'and type(a['size'])is int and a['size']==23 and a['symbol']==SYMBOL and selected[0]['address']==a['address']and int(selected[0]['size'],0)==23 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'deque pop complete member differs');u=units[UNIT]
    require(u.get('kind')=='probe'and u.get('source')==SOURCE and u.get('profile')=='vc8-sp1-probe-o2'and u.get('enable_gs')is True and u['functions']==[dict(address=a['address'],symbol_base=SYMBOL)],'deque pop original header-only unit differs');return a,u

def caller_site(reader,read):
    require(reader.symbol(INSERT).value==0 and reader.section(INSERT).name=='.text'and reader.section(INSERT).raw_size==1404,'deque pop original insertion owner differs');require(reader.refs(INSERT,5,1093)==[(1,20,SYMBOL)]and reader.raw(INSERT,5,1093)==b'\xe8'+bytes(4),'deque pop actual insertion call role differs');site=b'\xe8'+struct.pack('<i',0x428680-(0x463d05+5));require(site==read(0x463d05,5),'deque pop complete named native caller differs');require(digest(read(0x4638c0,1404))=='d79e2baf0eb343544e0ed2bd7d6f2ef18cd20085623df4606805890367dac8c0','deque pop independently owned insertion body changed');return site

def qualify(unit,anchor,rows,read,c):
    require(digest((ROOT/SOURCE).read_bytes())==SOURCE_SHA,'deque pop original instantiation source differs')
    for n,sha in VENDOR.items():require(digest((ROOT/'.tools/msvc80-sp1/include'/n).read_bytes())==sha,'deque pop original vendor header differs')
    r=Reader(ROOT/unit['object']);require(r.symbol(SYMBOL).value==0 and r.section(SYMBOL).name=='.text'and r.section(SYMBOL).raw_size==23 and r.section(SYMBOL).reloc_count==0 and not r.refs(SYMBOL,23),'deque pop complete original emitted body differs');b=r.raw(SYMBOL,23);require(b==read(0x428680,23)and digest(b)==anchor['sha256'],'deque pop entire canonical member differs');core.decode_closed_body(b,0x428680);site=caller_site(r,read)
    hits=[row['address']for row in rows if int(row['size'],0)==23 and b==read(int(row['address'],0),23)];require(hits==['0x00413DF0','0x00428680'],'deque pop complete alias inventory differs; actual caller selects428680');return dict(anchor=dict(address=anchor['address'],size=23,sha256=digest(b),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),caller=dict(address='0x00463D05',size=5,owner='0x004638C0',sha256=digest(site)),scope='23 original compiler-library bytes only; insertion provider independently revalidated by unchanged strict provenance gate, not new canonical/EH/authored credit; original specialization spelling nonexclusive; byte-identical413DF0 is not counted by this short-deque proof')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['deque_popback_anchor_file'])==ANCHORS,'unreviewed deque pop anchor path');require(compiler_sha256()==COMPILER,'deque pop compiler differs');a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,load_manifest()['units'],target_sha)
        sp=importlib.util.spec_from_file_location('deque_pop_original_origins',ROOT/'scripts/function-origins.py');o=importlib.util.module_from_spec(sp);sp.loader.exec_module(o);rules=tomllib.loads(o.RULES.read_text())['rules'];old=next(r for r in rules if r['id']=='vc8-generated-short-deque-insert-106a');require(not o.validate_vc8_generated_anchor_evidence(old,[r for r in rows if r['address']=='0x004638C0'],rows,read),'deque pop original insertion provenance failed')
        record=build.build_unit(UNIT,u,True,target_sha);c=core.comparator();c.verify_target();proof=qualify(u,a,rows,read,c);code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','deque pop formal comparison failed');proof.update(build=record,comparisons=results,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]
def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));errors=validate(dict(id='original-deque-pop-back-106a',deque_popback_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x00428680'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
