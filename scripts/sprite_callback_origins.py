"""Resolve one physical sprite cleanup by its real named array callback role."""
import csv
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import sprite_default_origins as owner
from linked_logic_error_origins import require,digest
ROOT=owner.ROOT
ANCHORS=ROOT/'config/sprite-callback-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/sprite-callback'
ADDRESS='0x00421D30'
def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==owner.UNIT,'sprite callback schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'sprite callback selects one physical cleanup');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']==ADDRESS and type(a['size'])is int and a['size']==7 and a['symbol']==owner.DTOR and selected[0]['address']==ADDRESS and int(selected[0]['size'],0)==7 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),'sprite callback complete identity/extent differs')
    old=tomllib.loads(owner.ANCHORS.read_text());owner.validate_spec(old,[dict(address='0x0041F6E0',size='16')],units,target_sha);u=units[owner.UNIT]
    require([f for f in u['functions']if f['address']==ADDRESS]==[dict(address=ADDRESS,symbol_base=owner.DTOR)],'sprite callback must retain actual emitted destructor');return a,u

def qualify(unit,anchor,rows,read,c,game):
    old=tomllib.loads(owner.ANCHORS.read_text());base=owner.qualify(unit,old['anchors'][0],rows,read,c,game)
    require(base['array_site']['destructor']==ADDRESS and base['array_site']['constructor']=='0x0041F6E0'and base['destructor_support']['address']==ADDRESS,'sprite callback physical target must come from the original constructor/destructor pair')
    b=c.coff_symbol_bytes(ROOT/unit['object'],owner.DTOR,0x421d30,7,{},c.known_data_targets());require(b==read(0x421d30,7)and digest(b)==anchor['sha256'],'sprite callback whole canonical body differs')
    hits=[r['address']for r in rows if int(r['size'],0)==7 and c.coff_symbol_bytes(ROOT/unit['object'],owner.DTOR,int(r['address'],0),7,{},c.known_data_targets())==read(int(r['address'],0),7)]
    require(hits==['0x0040AD50',ADDRESS],'sprite callback expected two equivalent byte bodies differ')
    return dict(anchor=dict(address=ADDRESS,size=7,sha256=digest(b),masked_bytes=0,unequal_bytes=0),inventory_hits=hits,selected_by='exact original array-site constructor/destructor pairing, not byte uniqueness',owner_proof=base,scope='One physical compiler cleanup7 only; no claim of exclusive original symbol spelling, second equivalent body or authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['sprite_callback_anchor_file'])==ANCHORS,'unreviewed sprite callback anchor path');units=owner.load_manifest()['units'];a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        errors=owner.validate(dict(id='implicit-sprite-default-constructor-106a',sprite_default_anchor_file=str(owner.ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x0041F6E0'],rows,read,target_sha);require(not errors,'sprite callback owner proof failed: '+'; '.join(errors))
        c=owner.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(u,a,rows,read,c,game)
        code,results=build.compare_unit(dict(u,functions=[f for f in u['functions']if f['address']==ADDRESS]),True);require(code==0 and len(results)==1 and results[0]['result']=='exact','sprite callback formal comparison failed')
        proof.update(comparisons=results,validator_sha256=owner.core.sha(Path(__file__)),anchor_sha256=owner.core.sha(ANCHORS),owner_validator_sha256=owner.core.sha(Path(owner.__file__)));OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=owner.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='implicit-sprite-array-callback-106a',sprite_callback_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']==ADDRESS],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
