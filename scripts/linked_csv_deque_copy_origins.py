"""Typed whole-body deque<string> copy helpers in the CSV loading CIL graph.

Two emitted iterator specializations can fold to each physical native body;
this validates both witnesses but counts each native function only once.
"""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import pefile
import linked_pe as core
from linked_logic_error_origins import require, named, ASSIGN
from workflow_manifest import load_manifest, source_dependencies

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-csv-deque-copy-origin-anchors.toml'
UNIT='exact-first-csv-file-loading'
SYMBOL_HASHES=['33eab9d07d945fac1f7b3654b6297d136e17d811c4f9834285661f2df2bac6e2','ca07439b69e179bdb8fd14a30ff4e2036198e26e69af95effe3784cced9eadfd','990fbcb13bd5cf6579dbc16dafae94a2f76eab22e2a18b9a8bbde17f7780ccf4','75a8dd6ddf438d91f9d17546ea9983ca8b235962e23e19bb8d8aebb70789b9fd','5053ae6f8a73dbe4e0968529e738826788af761dbfc2865de72a1c680d28ad71','90c25bced6acaee177577e5e62156b953a7033d4ca5cc30a5cc2ff79b17c0fad','d4c1317654034a6b6d9260c5a527ed2eff5985a50921fc9c30649b626ae977e6']
CONTRACT=[('0x00410ED0',112,'ca5832a8eaa53dcbed501bb242e13093f16224b9ccd88f25a018d7a74476f5eb'),('0x00411040',188,'7eac764a7bf5c297b3889a796973aac4db3c3646b739a4e38d52434907ff11bf')]
FORWARD_SHA='6e7d14b5a03553631d6a3cd3175675e7b87de6689ca86b3a4214dfc6dd3a0240'
HEADERS={'include/deque':'2970afda6fd33a55bb0f3860124a28e5c9e532dda18a240ac5749fb0a8cc0fc7','include/xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b','include/xutility':'104560e2ad5e433eb62c06d70882534306ba345f5f74e6907a6b270df3bd7cea','include/xstring':'c1a068968165290d000d554340d9c4e7e123c47ea619ad05d1c8f4e719c05922'}

def digest(b):return hashlib.sha256(b).hexdigest()
def inputs(unit):
    paths=set(source_dependencies(unit))
    for s in unit.get('linked_coff_sources',[]):paths.update(source_dependencies(dict(source=s)))
    return paths

def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'} and type(spec['schema_version']) is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'CSV deque schema/target/unit differs')
    expected=[dict(address=a,size=n,sha256=h) for a,n,h in CONTRACT]
    require(spec['anchors']==expected and {r['address']:int(r['size'],0) for r in selected}=={a:n for a,n,_ in CONTRACT} and len(selected)==2,'CSV deque target extents differ')
    require(unit.get('kind')=='linked_candidate' and unit.get('profile')==core.PROFILE and unit.get('source')=='src/battle/ScriptFileLoading.cpp' and unit.get('enable_gs') is True and unit.get('link_runtime')=='static' and unit.get('link_png_sdk') is True and unit.get('link_png_read_callback') is True and {'0x00405810','0x0040CF40'}<={f['address'] for f in unit['functions']},'CSV deque real CIL context differs')
    pins=spec['source_pins']; expected_paths={str(p.relative_to(ROOT)) for p in inputs(unit)}
    require(isinstance(pins,dict) and set(pins)==expected_paths and all(isinstance(v,str) and len(v)==64 and all(c in '0123456789abcdef' for c in v) for v in pins.values()),'CSV deque source closure differs')
    return spec['anchors']

def qualify(pe,functions,symbols,owner,rows,origins,read):
    addresses=[]; names=[]
    for h in SYMBOL_HASHES:
        matches=[(a,n,o) for a,items in functions.items() for n,o in items if digest(n.encode())==h]
        require(len(matches)==1 and matches[0][2]=='i '+owner and functions[matches[0][0]]==[(matches[0][1],matches[0][2])],'CSV deque source symbol/owner differs')
        a,n,_=matches[0];addresses.append(a);names.append(n)
    parent,*src=addresses
    require(len(set(addresses))==7,'CSV deque source witnesses overlap')
    exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
    require(all(core.IMAGE_BASE+e.address not in src for e in exports),'CSV deque helpers must not be forced exports')
    invalid=named(symbols,'__invalid_parameter_noinfo','libcmt:invarg.obj')
    require(core.linked_body(pe,functions,invalid)==read(0x68a143,16) and digest(read(0x68a143,16))=='cd349dae43dbf63016fe6ea9339dab15c59041e3224e48cf8a53004224b45e77','CSV deque static CRT body differs')
    assign=named(symbols,ASSIGN,'i '+owner)
    for a,e in [('0x0068A143','vc8-pinned-archive-symbols-106a'),('0x004020D0','vc8-generated-fixed-slot-std-comdats-106a'),('0x00411280','vc8-generated-menu-connect-history-std-comdats-106a')]:
        require(origins.get(a,{}).get('evidence_id')==e and origins[a]['disposition']=='exclude','CSV deque independent callee origin differs')
    require(digest(read(0x410600,2071))=='ab747b87e56abc3f3a4a417f0cc6a95f53e6bae15ab8095d9b99574243fcd9d6','CSV deque native caller bytes differ')
    def call_at(raw,base,off,to):
        require(raw[off]==0xe8 and base+off+5+struct.unpack_from('<i',raw,off+1)[0]==to,'CSV deque actual caller edge differs')
    source_parent=core.linked_body(pe,functions,parent)
    for off,to in [(0x221,src[2]),(0x333,src[1]),(0x3b1,src[0])]:call_at(source_parent,parent,off,to)
    native_parent=read(0x410600,2071)
    for off,to in [(0x28b,0x411040),(0x42f,0x410ed0),(0x65d,0x411040)]:call_at(native_parent,0x410600,off,to)
    src_targets={invalid:('__invalid_parameter_noinfo',0x68a143),assign:(ASSIGN,0x4020d0),src[2]:('copy_opt_const',0x411040),src[3]:('copy_opt',0x411040),src[4]:('copy_forward_const',0x411280),src[5]:('copy_forward',0x411280)}
    def resolve(a):
        require(a in src_targets,'CSV deque unproved call target');return src_targets[a]
    proof=[]
    for index,(at,target,size,sha,offsets) in enumerate([(src[0],0x410ed0,112,CONTRACT[0][2],[100]),(src[1],0x410ed0,112,CONTRACT[0][2],[100]),(src[2],0x411040,188,CONTRACT[1][2],[27,58,172]),(src[3],0x411040,188,CONTRACT[1][2],[27,58,172]),(src[4],0x411280,170,FORWARD_SHA,[33,52,88,103,134]),(src[5],0x411280,170,FORWARD_SHA,[33,52,88,103,134])]):
        raw=core.linked_body(pe,functions,at);require(len(raw)==size,'CSV deque whole source extent differs')
        core.decode_closed_body(raw,at);core.decode_closed_body(read(target,size),target)
        expected_edge=[(99,src[2]),(99,src[3]),(171,src[4]),(171,src[5]),(133,assign),(133,assign)][index]
        call_at(raw,at,*expected_edge)
        def rebound(a):return core.canonicalize(raw,at,a,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
        body,calls,refs=rebound(target)
        require(body==read(target,size) and digest(body)==sha and not refs and [x['offset'] for x in calls]==offsets,'CSV deque whole canonical body differs')
        core.validate_body_relocations(pe,at,size,[])
        fields={i for off in offsets for i in range(off,off+4)}
        require(all(a==b for i,(a,b) in enumerate(zip(raw,body)) if i not in fields),'CSV deque changed non-call byte')
        hits=[r['address'] for r in rows if int(r['size'],0)==size and rebound(int(r['address'],0))[0]==read(int(r['address'],0),size)]
        require(hits==[f'0x{target:08X}'],'CSV deque complete inventory identity differs')
        proof.append(dict(source_symbol=names[index+1],source_va=hex(at),target=f'0x{target:08X}',size=size,sha256=sha,calls=calls,inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    return dict(witnesses=proof,source_parent=names[0],source_parent_exact=False,native_parent='0x00410600',native_parent_exact=False)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_csv_deque_copy_anchor_file'])==ANCHORS,'CSV deque anchor path differs')
        unit=load_manifest()['units'][UNIT];spec=tomllib.loads(ANCHORS.read_text());validate_spec(spec,selected,unit,target_sha)
        require(all(core.sha(ROOT/path)==sha for path,sha in spec['source_pins'].items()),'CSV deque source pin differs')
        tools,_=core.pinned_tools(False);require(all(core.sha(tools/n)==s for n,s in HEADERS.items()),'CSV deque standard header pin differs')
        core.build_linked(UNIT,unit);roots=core.compare_linked(UNIT,unit,{'0x00405810','0x0040CF40'})
        require(len(roots)==2 and all(r['result']=='exact' for r in roots),'CSV deque existing roots differ')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));maps=image.with_suffix('.map').read_text()
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,core.parse_map(maps),core.parse_map_symbols(maps),image.with_suffix('.ltcg.obj').name,rows,origins,read)
        out=ROOT/'build/origin-anchors/linked-csv-deque-copy';out.mkdir(parents=True,exist_ok=True)
        (out/'proof.json').write_text(json.dumps(dict(target_sha256=target_sha,proof=proof,roots=roots),indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError) as exc:return [str(rule['id'])+': '+str(exc)]
