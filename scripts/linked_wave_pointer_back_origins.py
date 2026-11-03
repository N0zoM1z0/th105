"""Full pointer deque back helper in the actual wave handle-manager graph."""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import linked_pe as core
from linked_logic_error_origins import require, named
from workflow_manifest import load_manifest, source_dependencies

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-wave-pointer-back-origin-anchors.toml'
UNIT='exact-first-wave-service-load'
SYMBOL='?back@?$deque@PAVBgmBufferRuntime@th105@@V?$allocator@PAVBgmBufferRuntime@th105@@@std@@@std@@QAEAAPAVBgmBufferRuntime@th105@@XZ'
PARENT='?acquire@WaveLoadManager64@th105@@QAEPAPAVBgmBufferRuntime@2@AAUResourceHandleToken@2@@Z'
ROOT_SYMBOL='?load_wave@WaveLoadService@th105@@QAE?AUBgmHandleResult@2@PBD@Z'
SHA='441225b23a8adf199f3af64f8d6f488b0269c7b71888543618d7877696ffdabd'
HEADERS={'include/deque':'2970afda6fd33a55bb0f3860124a28e5c9e532dda18a240ac5749fb0a8cc0fc7','include/xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b','include/xutility':'104560e2ad5e433eb62c06d70882534306ba345f5f74e6907a6b270df3bd7cea'}

def digest(b):return hashlib.sha256(b).hexdigest()
def inputs(unit):
    paths=set(source_dependencies(unit))
    for s in unit.get('linked_coff_sources',[]):paths.update(source_dependencies(dict(source=s)))
    return paths

def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'} and type(spec['schema_version']) is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'wave deque schema/target/unit differs')
    require(spec['anchors']==[dict(address='0x004052B0',size=91,symbol=SYMBOL,sha256=SHA)] and len(selected)==1 and selected[0]['address']=='0x004052B0' and int(selected[0]['size'],0)==91,'wave deque target differs')
    require(unit.get('kind')=='linked_candidate' and unit.get('profile')==core.PROFILE and unit.get('source')=='src/audio/WaveServiceLoad.cpp' and unit.get('enable_gs') is True and unit.get('link_runtime')=='static' and unit.get('link_xiph_sdk') is True and {f['address'] for f in unit['functions']}=={'0x00401AF0'},'wave deque real CIL context differs')
    pins=spec['source_pins']; paths={str(p.relative_to(ROOT)) for p in inputs(unit)}
    require(isinstance(pins,dict) and set(pins)==paths and all(isinstance(v,str) and len(v)==64 and all(c in '0123456789abcdef' for c in v) for v in pins.values()),'wave deque source closure differs')
    return spec['anchors'][0]

def qualify(pe,functions,symbols,owner,rows,origins,read):
    start=named(symbols,SYMBOL,'i '+owner);parent=named(symbols,PARENT,owner);root=named(symbols,ROOT_SYMBOL,owner)
    for a,n,o in [(start,SYMBOL,'i '+owner),(parent,PARENT,owner),(root,ROOT_SYMBOL,owner)]:require(functions.get(a)==[(n,o)],'wave deque source owner/alias differs')
    exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
    require(all(core.IMAGE_BASE+e.address!=start for e in exports),'wave deque helper must not be forced export')
    invalid=named(symbols,'__invalid_parameter_noinfo','libcmt:invarg.obj')
    require(origins.get('0x0068A143',{}).get('evidence_id')=='vc8-pinned-archive-symbols-106a' and origins['0x0068A143']['disposition']=='exclude' and core.linked_body(pe,functions,invalid)==read(0x68a143,16) and digest(read(0x68a143,16))=='cd349dae43dbf63016fe6ea9339dab15c59041e3224e48cf8a53004224b45e77','wave deque runtime differs')
    require(digest(read(0x401af0,224))=='4656d7b85447306152dcaac9d06591a317ba024485e32c0d6b1443540ec4ffa2' and digest(read(0x405090,364))=='aac3d820dee1b301e98df7278e7b63e6582a58c73da12ac9da91008f8907d5a8','wave deque native context differs')
    def direct(code,at,to):return [i.address for i in core.decode_closed_body(code,at) if i.group(capstone.CS_GRP_CALL) and i.operands[0].type==capstone.x86.X86_OP_IMM and i.operands[0].imm==to]
    require(direct(core.linked_body(pe,functions,root),root,parent)==[root+0x18] and direct(core.linked_body(pe,functions,parent),parent,start)==[parent+0x8a] and direct(read(0x401af0,224),0x401af0,0x405090)==[0x401b0e] and direct(read(0x405090,364),0x405090,0x4052b0)==[0x405111],'wave deque actual call graph differs')
    raw=core.linked_body(pe,functions,start);require(len(raw)==91,'wave deque whole extent differs')
    core.decode_closed_body(raw,start);core.decode_closed_body(read(0x4052b0,91),0x4052b0)
    def resolve(a):require(a==invalid,'wave deque unproved call');return '__invalid_parameter_noinfo',0x68a143
    def rebound(a):return core.canonicalize(raw,start,a,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
    body,calls,refs=rebound(0x4052b0);offsets=[16,40,65]
    require(body==read(0x4052b0,91) and digest(body)==SHA and not refs and [x['offset'] for x in calls]==offsets,'wave deque whole canonical body differs')
    core.validate_body_relocations(pe,start,91,[]);fields={i for off in offsets for i in range(off,off+4)}
    require(all(a==b for i,(a,b) in enumerate(zip(raw,body)) if i not in fields),'wave deque changed non-call byte')
    hits=[r['address'] for r in rows if int(r['size'],0)==91 and rebound(int(r['address'],0))[0]==read(int(r['address'],0),91)]
    require(hits==['0x004052B0'],'wave deque full inventory identity differs')
    return dict(target='0x004052B0',size=91,sha256=SHA,source_symbol=SYMBOL,source_va=hex(start),source_parent_exact=False,native_parent_exact=False,source_root_exact=False,native_root_exact=False,calls=calls,inventory_hits=hits,masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_wave_pointer_back_anchor_file'])==ANCHORS,'wave deque anchor path differs')
        unit=load_manifest()['units'][UNIT];spec=tomllib.loads(ANCHORS.read_text());validate_spec(spec,selected,unit,target_sha)
        require(all(core.sha(ROOT/path)==sha for path,sha in spec['source_pins'].items()),'wave deque source pin differs')
        tools,_=core.pinned_tools(False);require(all(core.sha(tools/n)==s for n,s in HEADERS.items()),'wave deque header pin differs')
        core.build_linked(UNIT,unit);roots=core.compare_linked(UNIT,unit,{'0x00401AF0'})
        require(len(roots)==1 and roots[0]['result']=='mismatch' and roots[0]['object_section_tail_size']==221,'wave deque real nonexact root differs')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));maps=image.with_suffix('.map').read_text();origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,core.parse_map(maps),core.parse_map_symbols(maps),image.with_suffix('.ltcg.obj').name,rows,origins,read)
        out=ROOT/'build/origin-anchors/linked-wave-pointer-back';out.mkdir(parents=True,exist_ok=True)
        (out/'proof.json').write_text(json.dumps(dict(target_sha256=target_sha,proof=proof,roots=roots),indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError) as exc:return [str(rule['id'])+': '+str(exc)]
